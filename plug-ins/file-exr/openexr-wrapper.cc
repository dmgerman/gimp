#include "config.h"

/*  These libgimp includes are not needed here at all, but this is a
 *  convenient place to make sure the public libgimp headers are
 *  C++-clean. The C++ compiler will choke on stuff like naming
 *  a struct member or parameter "private".
 */
#include "libgimp/gimp.h"
#include "libgimp/gimpui.h"

#include "openexr-wrapper.h"

#include <ImfInputFile.h>
#include <ImfChannelList.h>
#include <ImfRgbaFile.h>
#include <ImfRgbaYca.h>
#include <ImfStandardAttributes.h>

#include <string>

#include "exr-attribute-blob.h"

using namespace Imf;
using namespace Imf::RgbaYca;
using namespace Imath;

struct _EXRLoader
{
  _EXRLoader(const char* filename) :
    refcount_(1),
    file_(filename),
    data_window_(file_.header().dataWindow()),
    channels_(file_.header().channels())
  {
    const Channel* chan;

    if (channels_.findChannel("R") ||
        channels_.findChannel("G") ||
        channels_.findChannel("B"))
      {
        format_string_ = "RGB";
        image_type_ = IMAGE_TYPE_RGB;

        if ((chan = channels_.findChannel("R")))
          pt_ = chan->type;
        else if ((chan = channels_.findChannel("G")))
          pt_ = chan->type;
        else
          pt_ = channels_.findChannel("B")->type;
      }
    else if (channels_.findChannel("Y") &&
             (channels_.findChannel("RY") ||
              channels_.findChannel("BY")))
      {
        format_string_ = "RGB";
        image_type_ = IMAGE_TYPE_RGB;

        pt_ = channels_.findChannel("Y")->type;

        // FIXME: no chroma handling for now.
        throw;
      }
    else if (channels_.findChannel("Y"))
      {
        format_string_ = "Y";
        image_type_ = IMAGE_TYPE_GRAY;

        pt_ = channels_.findChannel("Y")->type;
      }
    else
      {
        throw;
      }

    if (channels_.findChannel("A"))
      {
        format_string_.append("A");
        has_alpha_ = true;
      }
    else
      {
        has_alpha_ = false;
      }

    switch (pt_)
      {
      case UINT:
        format_string_.append(" u32");
        bpc_ = 4;
        break;
      case HALF:
        format_string_.append(" half");
        bpc_ = 2;
        break;
      case FLOAT:
      default:
        format_string_.append(" float");
        bpc_ = 4;
      }
  }

  int readPixelRow(char* pixels,
                   int bpp,
                   int row)
  {
    const int actual_row = data_window_.min.y + row;
    FrameBuffer fb;
    // This is necessary because OpenEXR expects the buffer to begin at
    // (0, 0). Though it probably results in some unmapped address,
    // hopefully OpenEXR will not make use of it. :/
    char* base = pixels - (data_window_.min.x * bpp);

    switch (image_type_)
      {
      case IMAGE_TYPE_GRAY:
        fb.insert("Y", Slice(pt_, base, bpp, 0, 1, 1, 0.5));
        if (hasAlpha())
          {
            fb.insert("A", Slice(pt_, base + bpc_, bpp, 0, 1, 1, 1.0));
          }
        break;

      case IMAGE_TYPE_RGB:
      default:
        fb.insert("R", Slice(pt_, base + (bpc_ * 0), bpp, 0, 1, 1, 0.0));
        fb.insert("G", Slice(pt_, base + (bpc_ * 1), bpp, 0, 1, 1, 0.0));
        fb.insert("B", Slice(pt_, base + (bpc_ * 2), bpp, 0, 1, 1, 0.0));
        if (hasAlpha())
          {
            fb.insert("A", Slice(pt_, base + (bpc_ * 3), bpp, 0, 1, 1, 1.0));
          }
      }

    file_.setFrameBuffer(fb);
    file_.readPixels(actual_row);

    return 0;
  }

  int getWidth() const {
    return data_window_.max.x - data_window_.min.x + 1;
  }

  int getHeight() const {
    return data_window_.max.y - data_window_.min.y + 1;
  }

  EXRPrecision getPrecision() const {
    EXRPrecision prec;

    switch (pt_)
      {
      case UINT:
        prec = PREC_UINT;
        break;
      case HALF:
        prec = PREC_HALF;
        break;
      case FLOAT:
      default:
        prec = PREC_FLOAT;
      }

    return prec;
  }

  EXRImageType getImageType() const {
    return image_type_;
  }

  int hasAlpha() const {
    return has_alpha_ ? 1 : 0;
  }

  cmsHPROFILE getICCProfile() const {
    Chromaticities chromaticities;
    float whiteLuminance = 1.0;

    cmsHPROFILE profile = NULL;

    if (hasChromaticities (file_.header ()))
      chromaticities = Imf::chromaticities (file_.header ());
    else
      return NULL;

    if (Imf::hasWhiteLuminance (file_.header ()))
      whiteLuminance = Imf::whiteLuminance (file_.header ());
    else
      return NULL;

#if 0
    std::cout << "hasChromaticities: "
              << hasChromaticities (file_.header ())
              << std::endl;
    std::cout << "hasWhiteLuminance: "
              << hasWhiteLuminance (file_.header ())
              << std::endl;
    std::cout << chromaticities.red << std::endl;
    std::cout << chromaticities.green << std::endl;
    std::cout << chromaticities.blue << std::endl;
    std::cout << chromaticities.white << std::endl;
    std::cout << std::endl;
#endif

    // TODO: maybe factor this out into libgimpcolor/gimpcolorprofile.h ?
    cmsCIExyY whitePoint = { chromaticities.white.x,
                             chromaticities.white.y,
                             whiteLuminance };
    cmsCIExyYTRIPLE CameraPrimaries = { { chromaticities.red.x,
                                          chromaticities.red.y,
                                          whiteLuminance },
                                        { chromaticities.green.x,
                                          chromaticities.green.y,
                                          whiteLuminance },
                                        { chromaticities.blue.x,
                                          chromaticities.blue.y,
                                          whiteLuminance } };

    double Parameters[2] = { 1.0, 0.0 };
    cmsToneCurve *Gamma[3];
    Gamma[0] = Gamma[1] = Gamma[2] = cmsBuildParametricToneCurve(0,
                                                                 1,
                                                                 Parameters);
    profile = cmsCreateRGBProfile (&whitePoint, &CameraPrimaries, Gamma);
    cmsFreeToneCurve (Gamma[0]);
    if (profile == NULL) return NULL;

    cmsSetProfileVersion (profile, 2.1);
    cmsMLU *mlu0 = cmsMLUalloc (NULL, 1);
    cmsMLUsetASCII (mlu0, "en", "US", "(GIMP internal)");
    cmsMLU *mlu1 = cmsMLUalloc(NULL, 1);
    cmsMLUsetASCII (mlu1, "en", "US", "color profile from EXR chromaticities");
    cmsMLU *mlu2 = cmsMLUalloc(NULL, 1);
    cmsMLUsetASCII (mlu2, "en", "US", "color profile from EXR chromaticities");
    cmsWriteTag (profile, cmsSigDeviceMfgDescTag, mlu0);
    cmsWriteTag (profile, cmsSigDeviceModelDescTag, mlu1);
    cmsWriteTag (profile, cmsSigProfileDescriptionTag, mlu2);
    cmsMLUfree (mlu0);
    cmsMLUfree (mlu1);
    cmsMLUfree (mlu2);

    return profile;
  }

  gchar *getComment() const {
    char *result = NULL;
    const Imf::StringAttribute *comment = file_.header().findTypedAttribute<Imf::StringAttribute>("comment");
    if (comment)
      result = g_strdup (comment->value().c_str());
    return result;
  }

  guchar *getExif(guint *size) const {
    guchar jpeg_exif[] = "Exif\0\0";
    guchar *exif_data = NULL;
    *size = 0;

    const Imf::BlobAttribute *exif = file_.header().findTypedAttribute<Imf::BlobAttribute>("exif");

    if (exif)
      {
        exif_data = (guchar *)(exif->value().data.get());
        *size = exif->value().size;
        // darktable appends a jpg-compatible exif00 string, so get rid of that again:
        if ( ! memcmp (jpeg_exif, exif_data, sizeof(jpeg_exif)))
          {
            *size -= 6;
            exif_data += 6;
          }
      }

    return (guchar *)g_memdup (exif_data, *size);
  }

  size_t refcount_;
  InputFile file_;
  const Box2i data_window_;
  const ChannelList& channels_;
  PixelType pt_;
  int bpc_;
  EXRImageType image_type_;
  bool has_alpha_;
  std::string format_string_;
};

EXRLoader*
exr_loader_new (const char *filename)
{
  EXRLoader* file;

  // Don't let any exceptions propagate to the C layer.
  try
    {
      Imf::BlobAttribute::registerAttributeType();
      file = new EXRLoader(filename);
    }
  catch (...)
    {
      file = NULL;
    }

  return file;
}

EXRLoader*
exr_loader_ref (EXRLoader *loader)
{
  ++loader->refcount_;
  return loader;
}

void
exr_loader_unref (EXRLoader *loader)
{
  if (--loader->refcount_ == 0)
    {
      delete loader;
    }
}

int
exr_loader_get_width (EXRLoader *loader)
{
  int width;
  // Don't let any exceptions propagate to the C layer.
  try
    {
      width = loader->getWidth();
    }
  catch (...)
    {
      width = -1;
    }

  return width;
}

int
exr_loader_get_height (EXRLoader *loader)
{
  int height;
  // Don't let any exceptions propagate to the C layer.
  try
    {
      height = loader->getHeight();
    }
  catch (...)
    {
      height = -1;
    }

  return height;
}

EXRImageType
exr_loader_get_image_type (EXRLoader *loader)
{
  // This does not throw.
  return loader->getImageType();
}

EXRPrecision
exr_loader_get_precision (EXRLoader *loader)
{
  // This does not throw.
  return loader->getPrecision();
}

int
exr_loader_has_alpha (EXRLoader *loader)
{
  // This does not throw.
  return loader->hasAlpha();
}

cmsHPROFILE
exr_loader_get_icc_profile (EXRLoader *loader)
{
  return loader->getICCProfile ();
}

gchar *
exr_loader_get_comment (EXRLoader *loader)
{
  return loader->getComment ();
}

guchar *
exr_loader_get_exif (EXRLoader *loader,
                     guint *size)
{
  return loader->getExif (size);
}

int
exr_loader_read_pixel_row (EXRLoader *loader,
                           char *pixels,
                           int bpp,
                           int row)
{
  int retval = -1;
  // Don't let any exceptions propagate to the C layer.
  try
    {
      retval = loader->readPixelRow(pixels, bpp, row);
    }
  catch (...)
    {
      retval = -1;
    }

  return retval;
}
