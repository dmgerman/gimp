begin_unit|revision:0.9.5;language:C;cregit-version:0.0.1
begin_comment
comment|/* tiff saving for GIMP  *  -Peter Mattis  *  * The TIFF loading code has been completely revamped by Nick Lamb  * njl195@zepler.org.uk -- 18 May 1998  * And it now gains support for tiles (and doubtless a zillion bugs)  * njl195@zepler.org.uk -- 12 June 1999  * LZW patent fuss continues :(  * njl195@zepler.org.uk -- 20 April 2000  * The code for this filter is based on "tifftopnm" and "pnmtotiff",  *  2 programs that are a part of the netpbm package.  * khk@khk.net -- 13 May 2000  * Added support for ICCPROFILE tiff tag. If this tag is present in a  * TIFF file, then a parasite is created and vice versa.  * peter@kirchgessner.net -- 29 Oct 2002  * Progress bar only when run interactive  * Added support for layer offsets - pablo.dangelo@web.de -- 7 Jan 2004  * Honor EXTRASAMPLES tag while loading images with alphachannel  * pablo.dangelo@web.de -- 16 Jan 2004  */
end_comment

begin_ifndef
ifndef|#
directive|ifndef
name|__FILE_TIFF_SAVE_H__
end_ifndef

begin_define
DECL|macro|__FILE_TIFF_SAVE_H__
define|#
directive|define
name|__FILE_TIFF_SAVE_H__
end_define

begin_typedef
typedef|typedef
struct|struct
DECL|struct|__anon2759d7ed0108
block|{
DECL|member|compression
name|gint
name|compression
decl_stmt|;
DECL|member|fillorder
name|gint
name|fillorder
decl_stmt|;
DECL|member|save_transp_pixels
name|gboolean
name|save_transp_pixels
decl_stmt|;
DECL|member|save_exif
name|gboolean
name|save_exif
decl_stmt|;
DECL|member|save_xmp
name|gboolean
name|save_xmp
decl_stmt|;
DECL|member|save_iptc
name|gboolean
name|save_iptc
decl_stmt|;
DECL|member|save_thumbnail
name|gboolean
name|save_thumbnail
decl_stmt|;
DECL|member|save_profile
name|gboolean
name|save_profile
decl_stmt|;
DECL|member|save_layers
name|gboolean
name|save_layers
decl_stmt|;
DECL|typedef|TiffSaveVals
block|}
name|TiffSaveVals
typedef|;
end_typedef

begin_function_decl
name|gboolean
name|save_image
parameter_list|(
name|GFile
modifier|*
name|file
parameter_list|,
name|TiffSaveVals
modifier|*
name|tsvals
parameter_list|,
name|gint32
name|image
parameter_list|,
name|gint32
name|orig_image
parameter_list|,
specifier|const
name|gchar
modifier|*
name|image_comment
parameter_list|,
name|gint
modifier|*
name|saved_bpp
parameter_list|,
name|GimpMetadata
modifier|*
name|metadata
parameter_list|,
name|GimpMetadataSaveFlags
name|metadata_flags
parameter_list|,
name|GError
modifier|*
modifier|*
name|error
parameter_list|)
function_decl|;
end_function_decl

begin_function_decl
name|gboolean
name|save_dialog
parameter_list|(
name|TiffSaveVals
modifier|*
name|tsvals
parameter_list|,
specifier|const
name|gchar
modifier|*
name|help_id
parameter_list|,
name|gboolean
name|has_alpha
parameter_list|,
name|gboolean
name|is_monochrome
parameter_list|,
name|gboolean
name|is_indexed
parameter_list|,
name|gchar
modifier|*
modifier|*
name|image_comment
parameter_list|)
function_decl|;
end_function_decl

begin_endif
endif|#
directive|endif
end_endif

begin_comment
comment|/* __FILE_TIFF_SAVE_H__ */
end_comment

end_unit

