begin_unit|revision:0.9.5;language:C;cregit-version:0.0.1
begin_comment
comment|/* tiff loading for GIMP  *  -Peter Mattis  *  * The TIFF loading code has been completely revamped by Nick Lamb  * njl195@zepler.org.uk -- 18 May 1998  * And it now gains support for tiles (and doubtless a zillion bugs)  * njl195@zepler.org.uk -- 12 June 1999  * LZW patent fuss continues :(  * njl195@zepler.org.uk -- 20 April 2000  * The code for this filter is based on "tifftopnm" and "pnmtotiff",  *  2 programs that are a part of the netpbm package.  * khk@khk.net -- 13 May 2000  * Added support for ICCPROFILE tiff tag. If this tag is present in a  * TIFF file, then a parasite is created and vice versa.  * peter@kirchgessner.net -- 29 Oct 2002  * Progress bar only when run interactive  * Added support for layer offsets - pablo.dangelo@web.de -- 7 Jan 2004  * Honor EXTRASAMPLES tag while loading images with alphachannel  * pablo.dangelo@web.de -- 16 Jan 2004  */
end_comment

begin_comment
comment|/*  * tifftopnm.c - converts a Tagged Image File to a portable anymap  *  * Derived by Jef Poskanzer from tif2ras.c, which is:  *  * Copyright (c) 1990 by Sun Microsystems, Inc.  *  * Author: Patrick J. Naughton  * naughton@wind.sun.com  *  * Permission to use, copy, modify, and distribute this software and its  * documentation for any purpose and without fee is hereby granted,  * provided that the above copyright notice appear in all copies and that  * both that copyright notice and this permission notice appear in  * supporting documentation.  *  * This file is provided AS IS with no warranties of any kind.  The author  * shall have no liability with respect to the infringement of copyrights,  * trade secrets or any patents by this file or any part thereof.  In no  * event will the author be liable for any lost revenue or profits or  * other special, indirect and consequential damages.  */
end_comment

begin_include
include|#
directive|include
file|"config.h"
end_include

begin_include
include|#
directive|include
file|<tiffio.h>
end_include

begin_include
include|#
directive|include
file|<gexiv2/gexiv2.h>
end_include

begin_include
include|#
directive|include
file|<libgimp/gimp.h>
end_include

begin_include
include|#
directive|include
file|<libgimp/gimpui.h>
end_include

begin_include
include|#
directive|include
file|"file-tiff-io.h"
end_include

begin_include
include|#
directive|include
file|"file-tiff-load.h"
end_include

begin_include
include|#
directive|include
file|"file-tiff-save.h"
end_include

begin_include
include|#
directive|include
file|"libgimp/stdplugins-intl.h"
end_include

begin_define
DECL|macro|LOAD_PROC
define|#
directive|define
name|LOAD_PROC
value|"file-tiff-load"
end_define

begin_define
DECL|macro|SAVE_PROC
define|#
directive|define
name|SAVE_PROC
value|"file-tiff-save"
end_define

begin_define
DECL|macro|SAVE2_PROC
define|#
directive|define
name|SAVE2_PROC
value|"file-tiff-save2"
end_define

begin_define
DECL|macro|PLUG_IN_BINARY
define|#
directive|define
name|PLUG_IN_BINARY
value|"file-tiff"
end_define

begin_function_decl
specifier|static
name|void
name|query
parameter_list|(
name|void
parameter_list|)
function_decl|;
end_function_decl

begin_function_decl
specifier|static
name|void
name|run
parameter_list|(
specifier|const
name|gchar
modifier|*
name|name
parameter_list|,
name|gint
name|nparams
parameter_list|,
specifier|const
name|GimpParam
modifier|*
name|param
parameter_list|,
name|gint
modifier|*
name|nreturn_vals
parameter_list|,
name|GimpParam
modifier|*
modifier|*
name|return_vals
parameter_list|)
function_decl|;
end_function_decl

begin_function_decl
specifier|static
name|gboolean
name|image_is_monochrome
parameter_list|(
name|gint32
name|image
parameter_list|)
function_decl|;
end_function_decl

begin_decl_stmt
DECL|variable|PLUG_IN_INFO
specifier|const
name|GimpPlugInInfo
name|PLUG_IN_INFO
init|=
block|{
name|NULL
block|,
comment|/* init_proc  */
name|NULL
block|,
comment|/* quit_proc  */
name|query
block|,
comment|/* query_proc */
name|run
block|,
comment|/* run_proc   */
block|}
decl_stmt|;
end_decl_stmt

begin_decl_stmt
DECL|variable|tsvals
specifier|static
name|TiffSaveVals
name|tsvals
init|=
block|{
name|COMPRESSION_NONE
block|,
comment|/*  compression         */
name|TRUE
block|,
comment|/*  alpha handling      */
name|TRUE
block|,
comment|/*  save transp. pixels */
name|TRUE
block|,
comment|/*  save exif           */
name|TRUE
block|,
comment|/*  save xmp            */
name|TRUE
block|,
comment|/*  save iptc           */
name|TRUE
comment|/*  save thumbnail      */
block|}
decl_stmt|;
end_decl_stmt

begin_decl_stmt
DECL|variable|image_comment
specifier|static
name|gchar
modifier|*
name|image_comment
init|=
name|NULL
decl_stmt|;
end_decl_stmt

begin_macro
DECL|function|MAIN ()
name|MAIN
argument_list|()
end_macro

begin_function
specifier|static
name|void
name|query
parameter_list|(
name|void
parameter_list|)
block|{
specifier|static
specifier|const
name|GimpParamDef
name|load_args
index|[]
init|=
block|{
block|{
name|GIMP_PDB_INT32
block|,
literal|"run-mode"
block|,
literal|"The run mode { RUN-INTERACTIVE (0), RUN-NONINTERACTIVE (1) }"
block|}
block|,
block|{
name|GIMP_PDB_STRING
block|,
literal|"filename"
block|,
literal|"The name of the file to load"
block|}
block|,
block|{
name|GIMP_PDB_STRING
block|,
literal|"raw-filename"
block|,
literal|"The name of the file to load"
block|}
block|}
decl_stmt|;
specifier|static
specifier|const
name|GimpParamDef
name|load_return_vals
index|[]
init|=
block|{
block|{
name|GIMP_PDB_IMAGE
block|,
literal|"image"
block|,
literal|"Output image"
block|}
block|}
decl_stmt|;
DECL|macro|COMMON_SAVE_ARGS
define|#
directive|define
name|COMMON_SAVE_ARGS
define|\
value|{ GIMP_PDB_INT32,    "run-mode",     "The run mode { RUN-INTERACTIVE (0), RUN-NONINTERACTIVE (1) }" },\     { GIMP_PDB_IMAGE,    "image",        "Input image" },\     { GIMP_PDB_DRAWABLE, "drawable",     "Drawable to save" },\     { GIMP_PDB_STRING,   "filename",     "The name of the file to save the image in" },\     { GIMP_PDB_STRING,   "raw-filename", "The name of the file to save the image in" },\     { GIMP_PDB_INT32,    "compression",  "Compression type: { NONE (0), LZW (1), PACKBITS (2), DEFLATE (3), JPEG (4), CCITT G3 Fax (5), CCITT G4 Fax (6) }" }
specifier|static
specifier|const
name|GimpParamDef
name|save_args_old
index|[]
init|=
block|{
name|COMMON_SAVE_ARGS
block|}
decl_stmt|;
specifier|static
specifier|const
name|GimpParamDef
name|save_args
index|[]
init|=
block|{
name|COMMON_SAVE_ARGS
block|,
block|{
name|GIMP_PDB_INT32
block|,
literal|"save-transp-pixels"
block|,
literal|"Keep the color data masked by an alpha channel intact"
block|}
block|}
decl_stmt|;
name|gimp_install_procedure
argument_list|(
name|LOAD_PROC
argument_list|,
literal|"loads files of the tiff file format"
argument_list|,
literal|"FIXME: write help for tiff_load"
argument_list|,
literal|"Spencer Kimball, Peter Mattis& Nick Lamb"
argument_list|,
literal|"Nick Lamb<njl195@zepler.org.uk>"
argument_list|,
literal|"1995-1996,1998-2003"
argument_list|,
name|N_
argument_list|(
literal|"TIFF image"
argument_list|)
argument_list|,
name|NULL
argument_list|,
name|GIMP_PLUGIN
argument_list|,
name|G_N_ELEMENTS
argument_list|(
name|load_args
argument_list|)
argument_list|,
name|G_N_ELEMENTS
argument_list|(
name|load_return_vals
argument_list|)
argument_list|,
name|load_args
argument_list|,
name|load_return_vals
argument_list|)
expr_stmt|;
name|gimp_register_file_handler_mime
argument_list|(
name|LOAD_PROC
argument_list|,
literal|"image/tiff"
argument_list|)
expr_stmt|;
name|gimp_register_magic_load_handler
argument_list|(
name|LOAD_PROC
argument_list|,
literal|"tif,tiff"
argument_list|,
literal|""
argument_list|,
literal|"0,string,II*\\0,0,string,MM\\0*"
argument_list|)
expr_stmt|;
name|gimp_install_procedure
argument_list|(
name|SAVE_PROC
argument_list|,
literal|"saves files in the tiff file format"
argument_list|,
literal|"Saves files in the Tagged Image File Format.  "
literal|"The value for the saved comment is taken "
literal|"from the 'gimp-comment' parasite."
argument_list|,
literal|"Spencer Kimball& Peter Mattis"
argument_list|,
literal|"Spencer Kimball& Peter Mattis"
argument_list|,
literal|"1995-1996,2000-2003"
argument_list|,
name|N_
argument_list|(
literal|"TIFF image"
argument_list|)
argument_list|,
literal|"RGB*, GRAY*, INDEXED"
argument_list|,
name|GIMP_PLUGIN
argument_list|,
name|G_N_ELEMENTS
argument_list|(
name|save_args_old
argument_list|)
argument_list|,
literal|0
argument_list|,
name|save_args_old
argument_list|,
name|NULL
argument_list|)
expr_stmt|;
name|gimp_register_file_handler_mime
argument_list|(
name|SAVE_PROC
argument_list|,
literal|"image/tiff"
argument_list|)
expr_stmt|;
name|gimp_register_save_handler
argument_list|(
name|SAVE_PROC
argument_list|,
literal|"tif,tiff"
argument_list|,
literal|""
argument_list|)
expr_stmt|;
name|gimp_install_procedure
argument_list|(
name|SAVE2_PROC
argument_list|,
literal|"saves files in the tiff file format"
argument_list|,
literal|"Saves files in the Tagged Image File Format.  "
literal|"The value for the saved comment is taken "
literal|"from the 'gimp-comment' parasite."
argument_list|,
literal|"Spencer Kimball& Peter Mattis"
argument_list|,
literal|"Spencer Kimball& Peter Mattis"
argument_list|,
literal|"1995-1996,2000-2003"
argument_list|,
name|N_
argument_list|(
literal|"TIFF image"
argument_list|)
argument_list|,
literal|"RGB*, GRAY*, INDEXED"
argument_list|,
name|GIMP_PLUGIN
argument_list|,
name|G_N_ELEMENTS
argument_list|(
name|save_args
argument_list|)
argument_list|,
literal|0
argument_list|,
name|save_args
argument_list|,
name|NULL
argument_list|)
expr_stmt|;
block|}
end_function

begin_function
specifier|static
name|void
DECL|function|run (const gchar * name,gint nparams,const GimpParam * param,gint * nreturn_vals,GimpParam ** return_vals)
name|run
parameter_list|(
specifier|const
name|gchar
modifier|*
name|name
parameter_list|,
name|gint
name|nparams
parameter_list|,
specifier|const
name|GimpParam
modifier|*
name|param
parameter_list|,
name|gint
modifier|*
name|nreturn_vals
parameter_list|,
name|GimpParam
modifier|*
modifier|*
name|return_vals
parameter_list|)
block|{
specifier|static
name|GimpParam
name|values
index|[
literal|2
index|]
decl_stmt|;
name|GimpRunMode
name|run_mode
decl_stmt|;
name|GimpPDBStatusType
name|status
init|=
name|GIMP_PDB_SUCCESS
decl_stmt|;
name|GError
modifier|*
name|error
init|=
name|NULL
decl_stmt|;
name|INIT_I18N
argument_list|()
expr_stmt|;
name|gegl_init
argument_list|(
name|NULL
argument_list|,
name|NULL
argument_list|)
expr_stmt|;
name|run_mode
operator|=
name|param
index|[
literal|0
index|]
operator|.
name|data
operator|.
name|d_int32
expr_stmt|;
operator|*
name|nreturn_vals
operator|=
literal|1
expr_stmt|;
operator|*
name|return_vals
operator|=
name|values
expr_stmt|;
name|values
index|[
literal|0
index|]
operator|.
name|type
operator|=
name|GIMP_PDB_STATUS
expr_stmt|;
name|values
index|[
literal|0
index|]
operator|.
name|data
operator|.
name|d_status
operator|=
name|GIMP_PDB_EXECUTION_ERROR
expr_stmt|;
if|if
condition|(
name|strcmp
argument_list|(
name|name
argument_list|,
name|LOAD_PROC
argument_list|)
operator|==
literal|0
condition|)
block|{
specifier|const
name|gchar
modifier|*
name|filename
init|=
name|param
index|[
literal|1
index|]
operator|.
name|data
operator|.
name|d_string
decl_stmt|;
name|TIFF
modifier|*
name|tif
decl_stmt|;
name|tif
operator|=
name|tiff_open
argument_list|(
name|filename
argument_list|,
literal|"r"
argument_list|,
operator|&
name|error
argument_list|)
expr_stmt|;
if|if
condition|(
name|tif
condition|)
block|{
name|TiffSelectedPages
name|pages
decl_stmt|;
name|pages
operator|.
name|target
operator|=
name|GIMP_PAGE_SELECTOR_TARGET_LAYERS
expr_stmt|;
name|gimp_get_data
argument_list|(
name|LOAD_PROC
argument_list|,
operator|&
name|pages
operator|.
name|target
argument_list|)
expr_stmt|;
name|pages
operator|.
name|n_pages
operator|=
name|pages
operator|.
name|o_pages
operator|=
name|TIFFNumberOfDirectories
argument_list|(
name|tif
argument_list|)
expr_stmt|;
if|if
condition|(
name|pages
operator|.
name|n_pages
operator|==
literal|0
condition|)
block|{
name|g_set_error
argument_list|(
operator|&
name|error
argument_list|,
name|G_FILE_ERROR
argument_list|,
name|G_FILE_ERROR_FAILED
argument_list|,
name|_
argument_list|(
literal|"TIFF '%s' does not contain any directories"
argument_list|)
argument_list|,
name|gimp_filename_to_utf8
argument_list|(
name|filename
argument_list|)
argument_list|)
expr_stmt|;
name|status
operator|=
name|GIMP_PDB_EXECUTION_ERROR
expr_stmt|;
block|}
else|else
block|{
name|gboolean
name|run_it
init|=
name|FALSE
decl_stmt|;
name|gint
name|i
decl_stmt|;
if|if
condition|(
name|run_mode
operator|!=
name|GIMP_RUN_INTERACTIVE
condition|)
block|{
name|pages
operator|.
name|pages
operator|=
name|g_new
argument_list|(
name|gint
argument_list|,
name|pages
operator|.
name|n_pages
argument_list|)
expr_stmt|;
for|for
control|(
name|i
operator|=
literal|0
init|;
name|i
operator|<
name|pages
operator|.
name|n_pages
condition|;
name|i
operator|++
control|)
name|pages
operator|.
name|pages
index|[
name|i
index|]
operator|=
name|i
expr_stmt|;
name|run_it
operator|=
name|TRUE
expr_stmt|;
block|}
else|else
block|{
name|gimp_ui_init
argument_list|(
name|PLUG_IN_BINARY
argument_list|,
name|FALSE
argument_list|)
expr_stmt|;
block|}
if|if
condition|(
name|pages
operator|.
name|n_pages
operator|==
literal|1
condition|)
block|{
name|pages
operator|.
name|pages
operator|=
name|g_new0
argument_list|(
name|gint
argument_list|,
name|pages
operator|.
name|n_pages
argument_list|)
expr_stmt|;
name|pages
operator|.
name|target
operator|=
name|GIMP_PAGE_SELECTOR_TARGET_LAYERS
expr_stmt|;
name|run_it
operator|=
name|TRUE
expr_stmt|;
block|}
if|if
condition|(
operator|(
operator|!
name|run_it
operator|)
operator|&&
operator|(
name|run_mode
operator|==
name|GIMP_RUN_INTERACTIVE
operator|)
condition|)
name|run_it
operator|=
name|load_dialog
argument_list|(
name|tif
argument_list|,
name|LOAD_PROC
argument_list|,
operator|&
name|pages
argument_list|)
expr_stmt|;
if|if
condition|(
name|run_it
condition|)
block|{
name|gint32
name|image
decl_stmt|;
name|gboolean
name|resolution_loaded
init|=
name|FALSE
decl_stmt|;
name|gimp_set_data
argument_list|(
name|LOAD_PROC
argument_list|,
operator|&
name|pages
operator|.
name|target
argument_list|,
sizeof|sizeof
argument_list|(
name|pages
operator|.
name|target
argument_list|)
argument_list|)
expr_stmt|;
name|image
operator|=
name|load_image
argument_list|(
name|param
index|[
literal|1
index|]
operator|.
name|data
operator|.
name|d_string
argument_list|,
name|tif
argument_list|,
operator|&
name|pages
argument_list|,
operator|&
name|resolution_loaded
argument_list|,
operator|&
name|error
argument_list|)
expr_stmt|;
name|g_free
argument_list|(
name|pages
operator|.
name|pages
argument_list|)
expr_stmt|;
if|if
condition|(
name|image
operator|>
literal|0
condition|)
block|{
name|GFile
modifier|*
name|file
decl_stmt|;
name|GimpMetadata
modifier|*
name|metadata
decl_stmt|;
name|file
operator|=
name|g_file_new_for_path
argument_list|(
name|param
index|[
literal|1
index|]
operator|.
name|data
operator|.
name|d_string
argument_list|)
expr_stmt|;
name|metadata
operator|=
name|gimp_image_metadata_load_prepare
argument_list|(
name|image
argument_list|,
literal|"image/tiff"
argument_list|,
name|file
argument_list|,
name|NULL
argument_list|)
expr_stmt|;
if|if
condition|(
name|metadata
condition|)
block|{
name|GimpMetadataLoadFlags
name|flags
init|=
name|GIMP_METADATA_LOAD_ALL
decl_stmt|;
if|if
condition|(
name|resolution_loaded
condition|)
name|flags
operator|&=
operator|~
name|GIMP_METADATA_LOAD_RESOLUTION
expr_stmt|;
name|gimp_image_metadata_load_finish
argument_list|(
name|image
argument_list|,
literal|"image/tiff"
argument_list|,
name|metadata
argument_list|,
name|flags
argument_list|,
name|run_mode
operator|==
name|GIMP_RUN_INTERACTIVE
argument_list|)
expr_stmt|;
name|g_object_unref
argument_list|(
name|metadata
argument_list|)
expr_stmt|;
block|}
name|g_object_unref
argument_list|(
name|file
argument_list|)
expr_stmt|;
operator|*
name|nreturn_vals
operator|=
literal|2
expr_stmt|;
name|values
index|[
literal|1
index|]
operator|.
name|type
operator|=
name|GIMP_PDB_IMAGE
expr_stmt|;
name|values
index|[
literal|1
index|]
operator|.
name|data
operator|.
name|d_image
operator|=
name|image
expr_stmt|;
block|}
else|else
block|{
name|status
operator|=
name|GIMP_PDB_EXECUTION_ERROR
expr_stmt|;
block|}
block|}
else|else
block|{
name|status
operator|=
name|GIMP_PDB_CANCEL
expr_stmt|;
block|}
block|}
name|TIFFClose
argument_list|(
name|tif
argument_list|)
expr_stmt|;
block|}
else|else
block|{
name|status
operator|=
name|GIMP_PDB_EXECUTION_ERROR
expr_stmt|;
block|}
block|}
elseif|else
if|if
condition|(
operator|(
name|strcmp
argument_list|(
name|name
argument_list|,
name|SAVE_PROC
argument_list|)
operator|==
literal|0
operator|)
operator|||
operator|(
name|strcmp
argument_list|(
name|name
argument_list|,
name|SAVE2_PROC
argument_list|)
operator|==
literal|0
operator|)
condition|)
block|{
comment|/* Plug-in is either file_tiff_save or file_tiff_save2 */
name|GimpMetadata
modifier|*
name|metadata
decl_stmt|;
name|GimpMetadataSaveFlags
name|metadata_flags
decl_stmt|;
name|GimpParasite
modifier|*
name|parasite
decl_stmt|;
name|gint32
name|image
init|=
name|param
index|[
literal|1
index|]
operator|.
name|data
operator|.
name|d_int32
decl_stmt|;
name|gint32
name|drawable
init|=
name|param
index|[
literal|2
index|]
operator|.
name|data
operator|.
name|d_int32
decl_stmt|;
name|gint32
name|orig_image
init|=
name|image
decl_stmt|;
name|GimpExportReturn
name|export
init|=
name|GIMP_EXPORT_CANCEL
decl_stmt|;
switch|switch
condition|(
name|run_mode
condition|)
block|{
case|case
name|GIMP_RUN_INTERACTIVE
case|:
case|case
name|GIMP_RUN_WITH_LAST_VALS
case|:
name|gimp_ui_init
argument_list|(
name|PLUG_IN_BINARY
argument_list|,
name|FALSE
argument_list|)
expr_stmt|;
name|export
operator|=
name|gimp_export_image
argument_list|(
operator|&
name|image
argument_list|,
operator|&
name|drawable
argument_list|,
literal|"TIFF"
argument_list|,
name|GIMP_EXPORT_CAN_HANDLE_RGB
operator||
name|GIMP_EXPORT_CAN_HANDLE_GRAY
operator||
name|GIMP_EXPORT_CAN_HANDLE_INDEXED
operator||
name|GIMP_EXPORT_CAN_HANDLE_ALPHA
argument_list|)
expr_stmt|;
if|if
condition|(
name|export
operator|==
name|GIMP_EXPORT_CANCEL
condition|)
block|{
name|values
index|[
literal|0
index|]
operator|.
name|data
operator|.
name|d_status
operator|=
name|GIMP_PDB_CANCEL
expr_stmt|;
return|return;
block|}
break|break;
default|default:
break|break;
block|}
name|metadata
operator|=
name|gimp_image_metadata_save_prepare
argument_list|(
name|orig_image
argument_list|,
literal|"image/tiff"
argument_list|,
operator|&
name|metadata_flags
argument_list|)
expr_stmt|;
name|tsvals
operator|.
name|save_exif
operator|=
operator|(
name|metadata_flags
operator|&
name|GIMP_METADATA_SAVE_EXIF
operator|)
operator|!=
literal|0
expr_stmt|;
name|tsvals
operator|.
name|save_xmp
operator|=
operator|(
name|metadata_flags
operator|&
name|GIMP_METADATA_SAVE_XMP
operator|)
operator|!=
literal|0
expr_stmt|;
name|tsvals
operator|.
name|save_iptc
operator|=
operator|(
name|metadata_flags
operator|&
name|GIMP_METADATA_SAVE_IPTC
operator|)
operator|!=
literal|0
expr_stmt|;
name|tsvals
operator|.
name|save_thumbnail
operator|=
operator|(
name|metadata_flags
operator|&
name|GIMP_METADATA_SAVE_THUMBNAIL
operator|)
operator|!=
literal|0
expr_stmt|;
name|parasite
operator|=
name|gimp_image_get_parasite
argument_list|(
name|orig_image
argument_list|,
literal|"gimp-comment"
argument_list|)
expr_stmt|;
if|if
condition|(
name|parasite
condition|)
block|{
name|image_comment
operator|=
name|g_strndup
argument_list|(
name|gimp_parasite_data
argument_list|(
name|parasite
argument_list|)
argument_list|,
name|gimp_parasite_data_size
argument_list|(
name|parasite
argument_list|)
argument_list|)
expr_stmt|;
name|gimp_parasite_free
argument_list|(
name|parasite
argument_list|)
expr_stmt|;
block|}
switch|switch
condition|(
name|run_mode
condition|)
block|{
case|case
name|GIMP_RUN_INTERACTIVE
case|:
comment|/*  Possibly retrieve data  */
name|gimp_get_data
argument_list|(
name|SAVE_PROC
argument_list|,
operator|&
name|tsvals
argument_list|)
expr_stmt|;
name|parasite
operator|=
name|gimp_image_get_parasite
argument_list|(
name|orig_image
argument_list|,
literal|"tiff-save-options"
argument_list|)
expr_stmt|;
if|if
condition|(
name|parasite
condition|)
block|{
specifier|const
name|TiffSaveVals
modifier|*
name|pvals
init|=
name|gimp_parasite_data
argument_list|(
name|parasite
argument_list|)
decl_stmt|;
if|if
condition|(
name|pvals
operator|->
name|compression
operator|==
name|COMPRESSION_DEFLATE
condition|)
name|tsvals
operator|.
name|compression
operator|=
name|COMPRESSION_ADOBE_DEFLATE
expr_stmt|;
else|else
name|tsvals
operator|.
name|compression
operator|=
name|pvals
operator|->
name|compression
expr_stmt|;
name|tsvals
operator|.
name|save_transp_pixels
operator|=
name|pvals
operator|->
name|save_transp_pixels
expr_stmt|;
block|}
name|gimp_parasite_free
argument_list|(
name|parasite
argument_list|)
expr_stmt|;
comment|/*  First acquire information with a dialog  */
if|if
condition|(
operator|!
name|save_dialog
argument_list|(
operator|&
name|tsvals
argument_list|,
name|SAVE_PROC
argument_list|,
name|gimp_drawable_has_alpha
argument_list|(
name|drawable
argument_list|)
argument_list|,
name|image_is_monochrome
argument_list|(
name|image
argument_list|)
argument_list|,
name|gimp_image_base_type
argument_list|(
name|image
argument_list|)
operator|==
name|GIMP_INDEXED
argument_list|,
operator|&
name|image_comment
argument_list|)
condition|)
block|{
name|status
operator|=
name|GIMP_PDB_CANCEL
expr_stmt|;
block|}
break|break;
case|case
name|GIMP_RUN_NONINTERACTIVE
case|:
comment|/*  Make sure all the arguments are there!  */
if|if
condition|(
name|nparams
operator|==
literal|6
operator|||
name|nparams
operator|==
literal|7
condition|)
block|{
switch|switch
condition|(
name|param
index|[
literal|5
index|]
operator|.
name|data
operator|.
name|d_int32
condition|)
block|{
case|case
literal|0
case|:
name|tsvals
operator|.
name|compression
operator|=
name|COMPRESSION_NONE
expr_stmt|;
break|break;
case|case
literal|1
case|:
name|tsvals
operator|.
name|compression
operator|=
name|COMPRESSION_LZW
expr_stmt|;
break|break;
case|case
literal|2
case|:
name|tsvals
operator|.
name|compression
operator|=
name|COMPRESSION_PACKBITS
expr_stmt|;
break|break;
case|case
literal|3
case|:
name|tsvals
operator|.
name|compression
operator|=
name|COMPRESSION_ADOBE_DEFLATE
expr_stmt|;
break|break;
case|case
literal|4
case|:
name|tsvals
operator|.
name|compression
operator|=
name|COMPRESSION_JPEG
expr_stmt|;
break|break;
case|case
literal|5
case|:
name|tsvals
operator|.
name|compression
operator|=
name|COMPRESSION_CCITTFAX3
expr_stmt|;
break|break;
case|case
literal|6
case|:
name|tsvals
operator|.
name|compression
operator|=
name|COMPRESSION_CCITTFAX4
expr_stmt|;
break|break;
default|default:
name|status
operator|=
name|GIMP_PDB_CALLING_ERROR
expr_stmt|;
break|break;
block|}
if|if
condition|(
name|nparams
operator|==
literal|7
condition|)
name|tsvals
operator|.
name|save_transp_pixels
operator|=
name|param
index|[
literal|6
index|]
operator|.
name|data
operator|.
name|d_int32
expr_stmt|;
else|else
name|tsvals
operator|.
name|save_transp_pixels
operator|=
name|TRUE
expr_stmt|;
block|}
else|else
block|{
name|status
operator|=
name|GIMP_PDB_CALLING_ERROR
expr_stmt|;
block|}
break|break;
case|case
name|GIMP_RUN_WITH_LAST_VALS
case|:
comment|/*  Possibly retrieve data  */
name|gimp_get_data
argument_list|(
name|SAVE_PROC
argument_list|,
operator|&
name|tsvals
argument_list|)
expr_stmt|;
name|parasite
operator|=
name|gimp_image_get_parasite
argument_list|(
name|orig_image
argument_list|,
literal|"tiff-save-options"
argument_list|)
expr_stmt|;
if|if
condition|(
name|parasite
condition|)
block|{
specifier|const
name|TiffSaveVals
modifier|*
name|pvals
init|=
name|gimp_parasite_data
argument_list|(
name|parasite
argument_list|)
decl_stmt|;
name|tsvals
operator|.
name|compression
operator|=
name|pvals
operator|->
name|compression
expr_stmt|;
name|tsvals
operator|.
name|save_transp_pixels
operator|=
name|pvals
operator|->
name|save_transp_pixels
expr_stmt|;
block|}
name|gimp_parasite_free
argument_list|(
name|parasite
argument_list|)
expr_stmt|;
break|break;
default|default:
break|break;
block|}
if|if
condition|(
name|status
operator|==
name|GIMP_PDB_SUCCESS
condition|)
block|{
name|gint
name|saved_bpp
decl_stmt|;
if|if
condition|(
name|save_image
argument_list|(
name|param
index|[
literal|3
index|]
operator|.
name|data
operator|.
name|d_string
argument_list|,
operator|&
name|tsvals
argument_list|,
name|image
argument_list|,
name|drawable
argument_list|,
name|orig_image
argument_list|,
name|image_comment
argument_list|,
operator|&
name|saved_bpp
argument_list|,
operator|&
name|error
argument_list|)
condition|)
block|{
if|if
condition|(
name|metadata
condition|)
block|{
name|GFile
modifier|*
name|file
decl_stmt|;
comment|/* See bug 758909: clear TIFFTAG_MIN/MAXSAMPLEVALUE because                    * exiv2 saves them with wrong type and the original values                    * could be invalid                    */
name|gexiv2_metadata_clear_tag
argument_list|(
name|metadata
argument_list|,
literal|"Exif.Image.0x0118"
argument_list|)
expr_stmt|;
name|gexiv2_metadata_clear_tag
argument_list|(
name|metadata
argument_list|,
literal|"Exif.Image.0x0119"
argument_list|)
expr_stmt|;
name|gimp_metadata_set_bits_per_sample
argument_list|(
name|metadata
argument_list|,
name|saved_bpp
argument_list|)
expr_stmt|;
if|if
condition|(
name|tsvals
operator|.
name|save_exif
condition|)
name|metadata_flags
operator||=
name|GIMP_METADATA_SAVE_EXIF
expr_stmt|;
else|else
name|metadata_flags
operator|&=
operator|~
name|GIMP_METADATA_SAVE_EXIF
expr_stmt|;
if|if
condition|(
name|tsvals
operator|.
name|save_xmp
condition|)
name|metadata_flags
operator||=
name|GIMP_METADATA_SAVE_XMP
expr_stmt|;
else|else
name|metadata_flags
operator|&=
operator|~
name|GIMP_METADATA_SAVE_XMP
expr_stmt|;
if|if
condition|(
name|tsvals
operator|.
name|save_iptc
condition|)
name|metadata_flags
operator||=
name|GIMP_METADATA_SAVE_IPTC
expr_stmt|;
else|else
name|metadata_flags
operator|&=
operator|~
name|GIMP_METADATA_SAVE_IPTC
expr_stmt|;
comment|/* never save metadata thumbnails for TIFF, see bug #729952 */
name|metadata_flags
operator|&=
operator|~
name|GIMP_METADATA_SAVE_THUMBNAIL
expr_stmt|;
name|file
operator|=
name|g_file_new_for_path
argument_list|(
name|param
index|[
literal|3
index|]
operator|.
name|data
operator|.
name|d_string
argument_list|)
expr_stmt|;
name|gimp_image_metadata_save_finish
argument_list|(
name|image
argument_list|,
literal|"image/tiff"
argument_list|,
name|metadata
argument_list|,
name|metadata_flags
argument_list|,
name|file
argument_list|,
name|NULL
argument_list|)
expr_stmt|;
name|g_object_unref
argument_list|(
name|file
argument_list|)
expr_stmt|;
block|}
comment|/*  Store mvals data  */
name|gimp_set_data
argument_list|(
name|SAVE_PROC
argument_list|,
operator|&
name|tsvals
argument_list|,
sizeof|sizeof
argument_list|(
name|TiffSaveVals
argument_list|)
argument_list|)
expr_stmt|;
block|}
else|else
block|{
name|status
operator|=
name|GIMP_PDB_EXECUTION_ERROR
expr_stmt|;
block|}
block|}
if|if
condition|(
name|export
operator|==
name|GIMP_EXPORT_EXPORT
condition|)
name|gimp_image_delete
argument_list|(
name|image
argument_list|)
expr_stmt|;
if|if
condition|(
name|metadata
condition|)
name|g_object_unref
argument_list|(
name|metadata
argument_list|)
expr_stmt|;
block|}
else|else
block|{
name|status
operator|=
name|GIMP_PDB_CALLING_ERROR
expr_stmt|;
block|}
if|if
condition|(
name|status
operator|!=
name|GIMP_PDB_SUCCESS
operator|&&
name|error
condition|)
block|{
operator|*
name|nreturn_vals
operator|=
literal|2
expr_stmt|;
name|values
index|[
literal|1
index|]
operator|.
name|type
operator|=
name|GIMP_PDB_STRING
expr_stmt|;
name|values
index|[
literal|1
index|]
operator|.
name|data
operator|.
name|d_string
operator|=
name|error
operator|->
name|message
expr_stmt|;
block|}
name|values
index|[
literal|0
index|]
operator|.
name|data
operator|.
name|d_status
operator|=
name|status
expr_stmt|;
block|}
end_function

begin_function
specifier|static
name|gboolean
DECL|function|image_is_monochrome (gint32 image)
name|image_is_monochrome
parameter_list|(
name|gint32
name|image
parameter_list|)
block|{
name|guchar
modifier|*
name|colors
decl_stmt|;
name|gint
name|num_colors
decl_stmt|;
name|gboolean
name|monochrome
init|=
name|FALSE
decl_stmt|;
name|g_return_val_if_fail
argument_list|(
name|image
operator|!=
operator|-
literal|1
argument_list|,
name|FALSE
argument_list|)
expr_stmt|;
name|colors
operator|=
name|gimp_image_get_colormap
argument_list|(
name|image
argument_list|,
operator|&
name|num_colors
argument_list|)
expr_stmt|;
if|if
condition|(
name|colors
condition|)
block|{
if|if
condition|(
name|num_colors
operator|==
literal|2
operator|||
name|num_colors
operator|==
literal|1
condition|)
block|{
specifier|const
name|guchar
name|bw_map
index|[]
init|=
block|{
literal|0
block|,
literal|0
block|,
literal|0
block|,
literal|255
block|,
literal|255
block|,
literal|255
block|}
decl_stmt|;
specifier|const
name|guchar
name|wb_map
index|[]
init|=
block|{
literal|255
block|,
literal|255
block|,
literal|255
block|,
literal|0
block|,
literal|0
block|,
literal|0
block|}
decl_stmt|;
if|if
condition|(
name|memcmp
argument_list|(
name|colors
argument_list|,
name|bw_map
argument_list|,
literal|3
operator|*
name|num_colors
argument_list|)
operator|==
literal|0
operator|||
name|memcmp
argument_list|(
name|colors
argument_list|,
name|wb_map
argument_list|,
literal|3
operator|*
name|num_colors
argument_list|)
operator|==
literal|0
condition|)
block|{
name|monochrome
operator|=
name|TRUE
expr_stmt|;
block|}
block|}
name|g_free
argument_list|(
name|colors
argument_list|)
expr_stmt|;
block|}
return|return
name|monochrome
return|;
block|}
end_function

end_unit

