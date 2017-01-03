begin_unit|revision:0.9.5;language:C;cregit-version:0.0.1
begin_comment
comment|/* tiff loading for GIMP  *  -Peter Mattis  *  * The TIFF loading code has been completely revamped by Nick Lamb  * njl195@zepler.org.uk -- 18 May 1998  * And it now gains support for tiles (and doubtless a zillion bugs)  * njl195@zepler.org.uk -- 12 June 1999  * LZW patent fuss continues :(  * njl195@zepler.org.uk -- 20 April 2000  * The code for this filter is based on "tifftopnm" and "pnmtotiff",  *  2 programs that are a part of the netpbm package.  * khk@khk.net -- 13 May 2000  * Added support for ICCPROFILE tiff tag. If this tag is present in a  * TIFF file, then a parasite is created and vice versa.  * peter@kirchgessner.net -- 29 Oct 2002  * Progress bar only when run interactive  * Added support for layer offsets - pablo.dangelo@web.de -- 7 Jan 2004  * Honor EXTRASAMPLES tag while loading images with alphachannel  * pablo.dangelo@web.de -- 16 Jan 2004  */
end_comment

begin_ifndef
ifndef|#
directive|ifndef
name|__FILE_TIFF_LOAD_H__
end_ifndef

begin_define
DECL|macro|__FILE_TIFF_LOAD_H__
define|#
directive|define
name|__FILE_TIFF_LOAD_H__
end_define

begin_typedef
typedef|typedef
struct|struct
DECL|struct|__anon2968cae30108
block|{
DECL|member|o_pages
name|gint
name|o_pages
decl_stmt|;
DECL|member|n_pages
name|gint
name|n_pages
decl_stmt|;
DECL|member|pages
name|gint
modifier|*
name|pages
decl_stmt|;
DECL|member|target
name|GimpPageSelectorTarget
name|target
decl_stmt|;
DECL|typedef|TiffSelectedPages
block|}
name|TiffSelectedPages
typedef|;
end_typedef

begin_function_decl
name|gboolean
name|load_dialog
parameter_list|(
name|TIFF
modifier|*
name|tif
parameter_list|,
specifier|const
name|gchar
modifier|*
name|help_id
parameter_list|,
name|TiffSelectedPages
modifier|*
name|pages
parameter_list|)
function_decl|;
end_function_decl

begin_function_decl
name|gint32
name|load_image
parameter_list|(
name|GFile
modifier|*
name|file
parameter_list|,
name|TIFF
modifier|*
name|tif
parameter_list|,
name|TiffSelectedPages
modifier|*
name|pages
parameter_list|,
name|gboolean
modifier|*
name|resolution_loaded
parameter_list|,
name|GError
modifier|*
modifier|*
name|error
parameter_list|)
function_decl|;
end_function_decl

begin_endif
endif|#
directive|endif
end_endif

begin_comment
comment|/* __FILE_TIFF_LOAD_H__ */
end_comment

end_unit

