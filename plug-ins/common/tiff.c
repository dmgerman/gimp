begin_unit|revision:0.9.5;language:C;cregit-version:0.0.1
begin_comment
comment|/* tiff loading and saving for the GIMP  *  -Peter Mattis  * The TIFF loading code has been completely revamped by Nick Lamb  * njl195@zepler.org.uk -- 18 May 1998  * And it now gains support for tiles (and doubtless a zillion bugs)  * njl195@zepler.org.uk -- 12 June 1999  * LZW patent fuss continues :(  * njl195@zepler.org.uk -- 20 April 2000  * The code for this filter is based on "tifftopnm" and "pnmtotiff",  *  2 programs that are a part of the netpbm package.  * khk@khk.net -- 13 May 2000  * Added support for ICCPROFILE tiff tag. If this tag is present in a   * TIFF file, then a parasite is created and vice versa.  * peter@kirchgessner.net -- 29 Oct 2002  * Progress bar only when run interactive  */
end_comment

begin_comment
comment|/* ** tifftopnm.c - converts a Tagged Image File to a portable anymap ** ** Derived by Jef Poskanzer from tif2ras.c, which is: ** ** Copyright (c) 1990 by Sun Microsystems, Inc. ** ** Author: Patrick J. Naughton ** naughton@wind.sun.com ** ** Permission to use, copy, modify, and distribute this software and its ** documentation for any purpose and without fee is hereby granted, ** provided that the above copyright notice appear in all copies and that ** both that copyright notice and this permission notice appear in ** supporting documentation. ** ** This file is provided AS IS with no warranties of any kind.  The author ** shall have no liability with respect to the infringement of copyrights, ** trade secrets or any patents by this file or any part thereof.  In no ** event will the author be liable for any lost revenue or profits or ** other special, indirect and consequential damages. */
end_comment

begin_include
include|#
directive|include
file|"config.h"
end_include

begin_include
include|#
directive|include
file|<stdlib.h>
end_include

begin_include
include|#
directive|include
file|<string.h>
end_include

begin_include
include|#
directive|include
file|<tiffio.h>
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
file|"libgimp/stdplugins-intl.h"
end_include

begin_typedef
typedef|typedef
struct|struct
DECL|struct|__anon279522f70108
DECL|struct|__anon279522f70408
block|{
DECL|member|compression
DECL|member|compression
name|gint
name|compression
decl_stmt|;
DECL|member|fillorder
DECL|member|fillorder
name|gint
name|fillorder
decl_stmt|;
DECL|typedef|TiffSaveVals
DECL|typedef|TiffSaveVals
block|}
name|TiffSaveVals
typedef|;
end_typedef

begin_typedef
typedef|typedef
struct|struct
DECL|struct|__anon279522f70208
DECL|struct|__anon279522f70508
block|{
DECL|member|run
DECL|member|run
name|gint
name|run
decl_stmt|;
DECL|typedef|TiffSaveInterface
DECL|typedef|TiffSaveInterface
block|}
name|TiffSaveInterface
typedef|;
end_typedef

begin_typedef
typedef|typedef
struct|struct
DECL|struct|__anon279522f70308
DECL|struct|__anon279522f70608
block|{
DECL|member|ID
DECL|member|ID
name|gint32
name|ID
decl_stmt|;
DECL|member|drawable
DECL|member|drawable
name|GimpDrawable
modifier|*
name|drawable
decl_stmt|;
DECL|member|pixel_rgn
DECL|member|pixel_rgn
name|GimpPixelRgn
name|pixel_rgn
decl_stmt|;
DECL|member|pixels
DECL|member|pixels
name|guchar
modifier|*
name|pixels
decl_stmt|;
DECL|member|pixel
DECL|member|pixel
name|guchar
modifier|*
name|pixel
decl_stmt|;
DECL|typedef|channel_data
DECL|typedef|channel_data
block|}
name|channel_data
typedef|;
end_typedef

begin_comment
comment|/* Declare some local functions.  */
end_comment

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
name|gchar
modifier|*
name|name
parameter_list|,
name|gint
name|nparams
parameter_list|,
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
name|gint32
name|load_image
parameter_list|(
name|gchar
modifier|*
name|filename
parameter_list|)
function_decl|;
end_function_decl

begin_function_decl
specifier|static
name|void
name|load_rgba
parameter_list|(
name|TIFF
modifier|*
name|tif
parameter_list|,
name|channel_data
modifier|*
name|channel
parameter_list|)
function_decl|;
end_function_decl

begin_function_decl
specifier|static
name|void
name|load_lines
parameter_list|(
name|TIFF
modifier|*
name|tif
parameter_list|,
name|channel_data
modifier|*
name|channel
parameter_list|,
name|gushort
name|bps
parameter_list|,
name|gushort
name|photomet
parameter_list|,
name|gint
name|alpha
parameter_list|,
name|gint
name|extra
parameter_list|)
function_decl|;
end_function_decl

begin_function_decl
specifier|static
name|void
name|load_tiles
parameter_list|(
name|TIFF
modifier|*
name|tif
parameter_list|,
name|channel_data
modifier|*
name|channel
parameter_list|,
name|gushort
name|bps
parameter_list|,
name|gushort
name|photomet
parameter_list|,
name|gint
name|alpha
parameter_list|,
name|gint
name|extra
parameter_list|)
function_decl|;
end_function_decl

begin_function_decl
specifier|static
name|void
name|read_separate
parameter_list|(
name|guchar
modifier|*
name|source
parameter_list|,
name|channel_data
modifier|*
name|channel
parameter_list|,
name|gushort
name|bps
parameter_list|,
name|gushort
name|photomet
parameter_list|,
name|gint
name|startcol
parameter_list|,
name|gint
name|startrow
parameter_list|,
name|gint
name|rows
parameter_list|,
name|gint
name|cols
parameter_list|,
name|gint
name|alpha
parameter_list|,
name|gint
name|extra
parameter_list|,
name|gint
name|sample
parameter_list|)
function_decl|;
end_function_decl

begin_function_decl
specifier|static
name|void
name|read_16bit
parameter_list|(
name|guchar
modifier|*
name|source
parameter_list|,
name|channel_data
modifier|*
name|channel
parameter_list|,
name|gushort
name|photomet
parameter_list|,
name|gint
name|startcol
parameter_list|,
name|gint
name|startrow
parameter_list|,
name|gint
name|rows
parameter_list|,
name|gint
name|cols
parameter_list|,
name|gint
name|alpha
parameter_list|,
name|gint
name|extra
parameter_list|,
name|gint
name|align
parameter_list|)
function_decl|;
end_function_decl

begin_function_decl
specifier|static
name|void
name|read_8bit
parameter_list|(
name|guchar
modifier|*
name|source
parameter_list|,
name|channel_data
modifier|*
name|channel
parameter_list|,
name|gushort
name|photomet
parameter_list|,
name|gint
name|startcol
parameter_list|,
name|gint
name|startrow
parameter_list|,
name|gint
name|rows
parameter_list|,
name|gint
name|cols
parameter_list|,
name|gint
name|alpha
parameter_list|,
name|gint
name|extra
parameter_list|,
name|gint
name|align
parameter_list|)
function_decl|;
end_function_decl

begin_function_decl
specifier|static
name|void
name|read_default
parameter_list|(
name|guchar
modifier|*
name|source
parameter_list|,
name|channel_data
modifier|*
name|channel
parameter_list|,
name|gushort
name|bps
parameter_list|,
name|gushort
name|photomet
parameter_list|,
name|gint
name|startcol
parameter_list|,
name|gint
name|startrow
parameter_list|,
name|gint
name|rows
parameter_list|,
name|gint
name|cols
parameter_list|,
name|gint
name|alpha
parameter_list|,
name|gint
name|extra
parameter_list|,
name|gint
name|align
parameter_list|)
function_decl|;
end_function_decl

begin_function_decl
specifier|static
name|gint
name|save_image
parameter_list|(
name|gchar
modifier|*
name|filename
parameter_list|,
name|gint32
name|image
parameter_list|,
name|gint32
name|drawable
parameter_list|,
name|gint32
name|orig_image
parameter_list|)
function_decl|;
end_function_decl

begin_function_decl
specifier|static
name|gint
name|save_dialog
parameter_list|(
name|void
parameter_list|)
function_decl|;
end_function_decl

begin_function_decl
specifier|static
name|void
name|save_ok_callback
parameter_list|(
name|GtkWidget
modifier|*
name|widget
parameter_list|,
name|gpointer
name|data
parameter_list|)
function_decl|;
end_function_decl

begin_function_decl
specifier|static
name|void
name|comment_entry_callback
parameter_list|(
name|GtkWidget
modifier|*
name|widget
parameter_list|,
name|gpointer
name|data
parameter_list|)
function_decl|;
end_function_decl

begin_decl_stmt
DECL|variable|PLUG_IN_INFO
DECL|variable|PLUG_IN_INFO
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
DECL|variable|tsvals
specifier|static
name|TiffSaveVals
name|tsvals
init|=
block|{
name|COMPRESSION_NONE
block|,
comment|/*  compression  */
block|}
decl_stmt|;
end_decl_stmt

begin_decl_stmt
DECL|variable|tsint
DECL|variable|tsint
specifier|static
name|TiffSaveInterface
name|tsint
init|=
block|{
name|FALSE
comment|/*  run  */
block|}
decl_stmt|;
end_decl_stmt

begin_decl_stmt
DECL|variable|image_comment
DECL|variable|image_comment
specifier|static
name|gchar
modifier|*
name|image_comment
init|=
name|NULL
decl_stmt|;
end_decl_stmt

begin_decl_stmt
DECL|variable|run_mode
DECL|variable|run_mode
specifier|static
name|GimpRunMode
name|run_mode
init|=
name|GIMP_RUN_INTERACTIVE
decl_stmt|;
end_decl_stmt

begin_macro
DECL|function|MAIN ()
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
name|GimpParamDef
name|load_args
index|[]
init|=
block|{
block|{
name|GIMP_PDB_INT32
block|,
literal|"run_mode"
block|,
literal|"Interactive, non-interactive"
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
literal|"raw_filename"
block|,
literal|"The name of the file to load"
block|}
block|}
decl_stmt|;
specifier|static
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
specifier|static
name|GimpParamDef
name|save_args
index|[]
init|=
block|{
block|{
name|GIMP_PDB_INT32
block|,
literal|"run_mode"
block|,
literal|"Interactive, non-interactive"
block|}
block|,
block|{
name|GIMP_PDB_IMAGE
block|,
literal|"image"
block|,
literal|"Input image"
block|}
block|,
block|{
name|GIMP_PDB_DRAWABLE
block|,
literal|"drawable"
block|,
literal|"Drawable to save"
block|}
block|,
block|{
name|GIMP_PDB_STRING
block|,
literal|"filename"
block|,
literal|"The name of the file to save the image in"
block|}
block|,
block|{
name|GIMP_PDB_STRING
block|,
literal|"raw_filename"
block|,
literal|"The name of the file to save the image in"
block|}
block|,
block|{
name|GIMP_PDB_INT32
block|,
literal|"compression"
block|,
literal|"Compression type: { NONE (0), LZW (1), PACKBITS (2), DEFLATE (3), JPEG (4)"
block|}
block|}
decl_stmt|;
name|gimp_install_procedure
argument_list|(
literal|"file_tiff_load"
argument_list|,
literal|"loads files of the tiff file format"
argument_list|,
literal|"FIXME: write help for tiff_load"
argument_list|,
literal|"Spencer Kimball, Peter Mattis& Nick Lamb"
argument_list|,
literal|"Nick Lamb<njl195@zepler.org.uk>"
argument_list|,
literal|"1995-1996,1998-2000"
argument_list|,
literal|"<Load>/Tiff"
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
name|gimp_install_procedure
argument_list|(
literal|"file_tiff_save"
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
literal|"1995-1996,2000"
argument_list|,
literal|"<Save>/Tiff"
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
name|gimp_register_magic_load_handler
argument_list|(
literal|"file_tiff_load"
argument_list|,
literal|"tif,tiff"
argument_list|,
literal|""
argument_list|,
literal|"0,string,II*\\0,0,string,MM\\0*"
argument_list|)
expr_stmt|;
name|gimp_register_save_handler
argument_list|(
literal|"file_tiff_save"
argument_list|,
literal|"tif,tiff"
argument_list|,
literal|""
argument_list|)
expr_stmt|;
block|}
end_function

begin_function
specifier|static
name|void
DECL|function|run (gchar * name,gint nparams,GimpParam * param,gint * nreturn_vals,GimpParam ** return_vals)
DECL|function|run (gchar * name,gint nparams,GimpParam * param,gint * nreturn_vals,GimpParam ** return_vals)
name|run
parameter_list|(
name|gchar
modifier|*
name|name
parameter_list|,
name|gint
name|nparams
parameter_list|,
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
name|GimpPDBStatusType
name|status
init|=
name|GIMP_PDB_SUCCESS
decl_stmt|;
name|GimpParasite
modifier|*
name|parasite
decl_stmt|;
name|gint32
name|image
decl_stmt|;
name|gint32
name|drawable
decl_stmt|;
name|gint32
name|orig_image
decl_stmt|;
name|GimpExportReturnType
name|export
init|=
name|GIMP_EXPORT_CANCEL
decl_stmt|;
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
literal|"file_tiff_load"
argument_list|)
operator|==
literal|0
condition|)
block|{
name|INIT_I18N_UI
argument_list|()
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
argument_list|)
expr_stmt|;
if|if
condition|(
name|image
operator|!=
operator|-
literal|1
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
elseif|else
if|if
condition|(
name|strcmp
argument_list|(
name|name
argument_list|,
literal|"file_tiff_save"
argument_list|)
operator|==
literal|0
condition|)
block|{
name|image
operator|=
name|orig_image
operator|=
name|param
index|[
literal|1
index|]
operator|.
name|data
operator|.
name|d_int32
expr_stmt|;
name|drawable
operator|=
name|param
index|[
literal|2
index|]
operator|.
name|data
operator|.
name|d_int32
expr_stmt|;
comment|/* Do this right this time, if POSSIBLE query for parasites, otherwise 	 or if there isn't one, choose the default comment from the gimprc. */
comment|/*  eventually export the image */
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
name|INIT_I18N_UI
argument_list|()
expr_stmt|;
name|gimp_ui_init
argument_list|(
literal|"tiff"
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
operator|(
name|GIMP_EXPORT_CAN_HANDLE_RGB
operator||
name|GIMP_EXPORT_CAN_HANDLE_GRAY
operator||
name|GIMP_EXPORT_CAN_HANDLE_INDEXED
operator||
name|GIMP_EXPORT_CAN_HANDLE_ALPHA
operator|)
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
name|parasite
operator|=
name|gimp_image_parasite_find
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
name|image_comment
operator|=
name|g_strdup
argument_list|(
name|parasite
operator|->
name|data
argument_list|)
expr_stmt|;
name|gimp_parasite_free
argument_list|(
name|parasite
argument_list|)
expr_stmt|;
if|if
condition|(
operator|!
name|image_comment
condition|)
name|image_comment
operator|=
name|gimp_get_default_comment
argument_list|()
expr_stmt|;
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
literal|"file_tiff_save"
argument_list|,
operator|&
name|tsvals
argument_list|)
expr_stmt|;
name|parasite
operator|=
name|gimp_image_parasite_find
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
name|tsvals
operator|.
name|compression
operator|=
operator|(
operator|(
name|TiffSaveVals
operator|*
operator|)
name|parasite
operator|->
name|data
operator|)
operator|->
name|compression
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
argument_list|()
condition|)
name|status
operator|=
name|GIMP_PDB_CANCEL
expr_stmt|;
break|break;
case|case
name|GIMP_RUN_NONINTERACTIVE
case|:
name|INIT_I18N
argument_list|()
expr_stmt|;
comment|/*  Make sure all the arguments are there!  */
if|if
condition|(
name|nparams
operator|!=
literal|6
condition|)
block|{
name|status
operator|=
name|GIMP_PDB_CALLING_ERROR
expr_stmt|;
block|}
else|else
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
name|COMPRESSION_DEFLATE
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
default|default:
name|status
operator|=
name|GIMP_PDB_CALLING_ERROR
expr_stmt|;
break|break;
block|}
block|}
break|break;
case|case
name|GIMP_RUN_WITH_LAST_VALS
case|:
comment|/*  Possibly retrieve data  */
name|gimp_get_data
argument_list|(
literal|"file_tiff_save"
argument_list|,
operator|&
name|tsvals
argument_list|)
expr_stmt|;
name|parasite
operator|=
name|gimp_image_parasite_find
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
name|tsvals
operator|.
name|compression
operator|=
operator|(
operator|(
name|TiffSaveVals
operator|*
operator|)
name|parasite
operator|->
name|data
operator|)
operator|->
name|compression
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
name|image
argument_list|,
name|drawable
argument_list|,
name|orig_image
argument_list|)
condition|)
block|{
comment|/*  Store mvals data  */
name|gimp_set_data
argument_list|(
literal|"file_tiff_save"
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
block|}
else|else
block|{
name|status
operator|=
name|GIMP_PDB_CALLING_ERROR
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
name|void
DECL|function|tiff_warning (const char * module,const char * fmt,va_list ap)
DECL|function|tiff_warning (const char * module,const char * fmt,va_list ap)
name|tiff_warning
parameter_list|(
specifier|const
name|char
modifier|*
name|module
parameter_list|,
specifier|const
name|char
modifier|*
name|fmt
parameter_list|,
name|va_list
name|ap
parameter_list|)
block|{
name|g_logv
argument_list|(
name|G_LOG_DOMAIN
argument_list|,
name|G_LOG_LEVEL_MESSAGE
argument_list|,
name|fmt
argument_list|,
name|ap
argument_list|)
expr_stmt|;
block|}
end_function

begin_function
specifier|static
name|void
DECL|function|tiff_error (const char * module,const char * fmt,va_list ap)
DECL|function|tiff_error (const char * module,const char * fmt,va_list ap)
name|tiff_error
parameter_list|(
specifier|const
name|char
modifier|*
name|module
parameter_list|,
specifier|const
name|char
modifier|*
name|fmt
parameter_list|,
name|va_list
name|ap
parameter_list|)
block|{
name|g_logv
argument_list|(
name|G_LOG_DOMAIN
argument_list|,
name|G_LOG_LEVEL_MESSAGE
argument_list|,
name|fmt
argument_list|,
name|ap
argument_list|)
expr_stmt|;
block|}
end_function

begin_function
specifier|static
name|gint32
DECL|function|load_image (gchar * filename)
DECL|function|load_image (gchar * filename)
name|load_image
parameter_list|(
name|gchar
modifier|*
name|filename
parameter_list|)
block|{
name|TIFF
modifier|*
name|tif
decl_stmt|;
name|gushort
name|bps
decl_stmt|,
name|spp
decl_stmt|,
name|photomet
decl_stmt|;
name|guint16
name|orientation
decl_stmt|;
name|gint
name|cols
decl_stmt|,
name|rows
decl_stmt|,
name|alpha
decl_stmt|;
name|gint
name|image
decl_stmt|,
name|image_type
init|=
name|GIMP_RGB
decl_stmt|;
name|gint
name|layer
decl_stmt|,
name|layer_type
init|=
name|GIMP_RGB_IMAGE
decl_stmt|;
name|gushort
name|extra
decl_stmt|,
modifier|*
name|extra_types
decl_stmt|;
name|channel_data
modifier|*
name|channel
init|=
name|NULL
decl_stmt|;
name|gushort
modifier|*
name|redmap
decl_stmt|,
modifier|*
name|greenmap
decl_stmt|,
modifier|*
name|bluemap
decl_stmt|;
name|GimpRGB
name|color
decl_stmt|;
name|guchar
name|cmap
index|[
literal|768
index|]
decl_stmt|;
name|gint
name|i
decl_stmt|,
name|j
decl_stmt|,
name|worst_case
init|=
literal|0
decl_stmt|;
name|gchar
modifier|*
name|name
decl_stmt|;
name|TiffSaveVals
name|save_vals
decl_stmt|;
name|GimpParasite
modifier|*
name|parasite
decl_stmt|;
name|guint16
name|tmp
decl_stmt|;
ifdef|#
directive|ifdef
name|TIFFTAG_ICCPROFILE
name|uint32
name|profile_size
decl_stmt|;
name|guchar
modifier|*
name|icc_profile
decl_stmt|;
endif|#
directive|endif
name|gboolean
name|flip_horizontal
init|=
name|FALSE
decl_stmt|;
name|gboolean
name|flip_vertical
init|=
name|FALSE
decl_stmt|;
name|gimp_rgb_set
argument_list|(
operator|&
name|color
argument_list|,
literal|0.0
argument_list|,
literal|0.0
argument_list|,
literal|0.0
argument_list|)
expr_stmt|;
name|TIFFSetWarningHandler
argument_list|(
name|tiff_warning
argument_list|)
expr_stmt|;
name|TIFFSetErrorHandler
argument_list|(
name|tiff_error
argument_list|)
expr_stmt|;
name|tif
operator|=
name|TIFFOpen
argument_list|(
name|filename
argument_list|,
literal|"r"
argument_list|)
expr_stmt|;
if|if
condition|(
operator|!
name|tif
condition|)
block|{
name|g_message
argument_list|(
literal|"TIFF Can't open %s\n"
argument_list|,
name|filename
argument_list|)
expr_stmt|;
name|gimp_quit
argument_list|()
expr_stmt|;
block|}
if|if
condition|(
name|run_mode
operator|==
name|GIMP_RUN_INTERACTIVE
condition|)
block|{
name|name
operator|=
name|g_strdup_printf
argument_list|(
name|_
argument_list|(
literal|"Loading %s:"
argument_list|)
argument_list|,
name|filename
argument_list|)
expr_stmt|;
name|gimp_progress_init
argument_list|(
name|name
argument_list|)
expr_stmt|;
name|g_free
argument_list|(
name|name
argument_list|)
expr_stmt|;
block|}
name|TIFFGetFieldDefaulted
argument_list|(
name|tif
argument_list|,
name|TIFFTAG_BITSPERSAMPLE
argument_list|,
operator|&
name|bps
argument_list|)
expr_stmt|;
if|if
condition|(
name|bps
operator|>
literal|8
operator|&&
name|bps
operator|!=
literal|16
condition|)
block|{
name|worst_case
operator|=
literal|1
expr_stmt|;
comment|/* Wrong sample width => RGBA */
block|}
name|TIFFGetFieldDefaulted
argument_list|(
name|tif
argument_list|,
name|TIFFTAG_SAMPLESPERPIXEL
argument_list|,
operator|&
name|spp
argument_list|)
expr_stmt|;
if|if
condition|(
operator|!
name|TIFFGetField
argument_list|(
name|tif
argument_list|,
name|TIFFTAG_EXTRASAMPLES
argument_list|,
operator|&
name|extra
argument_list|,
operator|&
name|extra_types
argument_list|)
condition|)
name|extra
operator|=
literal|0
expr_stmt|;
if|if
condition|(
operator|!
name|TIFFGetField
argument_list|(
name|tif
argument_list|,
name|TIFFTAG_IMAGEWIDTH
argument_list|,
operator|&
name|cols
argument_list|)
condition|)
block|{
name|g_message
argument_list|(
literal|"TIFF Can't get image width\n"
argument_list|)
expr_stmt|;
name|gimp_quit
argument_list|()
expr_stmt|;
block|}
if|if
condition|(
operator|!
name|TIFFGetField
argument_list|(
name|tif
argument_list|,
name|TIFFTAG_IMAGELENGTH
argument_list|,
operator|&
name|rows
argument_list|)
condition|)
block|{
name|g_message
argument_list|(
literal|"TIFF Can't get image length\n"
argument_list|)
expr_stmt|;
name|gimp_quit
argument_list|()
expr_stmt|;
block|}
if|if
condition|(
operator|!
name|TIFFGetField
argument_list|(
name|tif
argument_list|,
name|TIFFTAG_PHOTOMETRIC
argument_list|,
operator|&
name|photomet
argument_list|)
condition|)
block|{
name|g_message
argument_list|(
literal|"TIFF Can't get photometric\nAssuming min-is-black\n"
argument_list|)
expr_stmt|;
comment|/* old AppleScan software misses out the photometric tag (and      * incidentally assumes min-is-white, but xv assumes min-is-black,      * so we follow xv's lead.  It's not much hardship to invert the      * image later). */
name|photomet
operator|=
name|PHOTOMETRIC_MINISBLACK
expr_stmt|;
block|}
comment|/* test if the extrasample represents an associated alpha channel... */
if|if
condition|(
name|extra
operator|>
literal|0
operator|&&
operator|(
name|extra_types
index|[
literal|0
index|]
operator|==
name|EXTRASAMPLE_ASSOCALPHA
operator|)
condition|)
block|{
name|alpha
operator|=
literal|1
expr_stmt|;
operator|--
name|extra
expr_stmt|;
block|}
else|else
block|{
name|alpha
operator|=
literal|0
expr_stmt|;
block|}
if|if
condition|(
name|photomet
operator|==
name|PHOTOMETRIC_RGB
operator|&&
name|spp
operator|>
literal|3
operator|+
name|extra
condition|)
block|{
name|alpha
operator|=
literal|1
expr_stmt|;
name|extra
operator|=
name|spp
operator|-
literal|4
expr_stmt|;
block|}
elseif|else
if|if
condition|(
name|photomet
operator|!=
name|PHOTOMETRIC_RGB
operator|&&
name|spp
operator|>
literal|1
operator|+
name|extra
condition|)
block|{
name|alpha
operator|=
literal|1
expr_stmt|;
name|extra
operator|=
name|spp
operator|-
literal|2
expr_stmt|;
block|}
switch|switch
condition|(
name|photomet
condition|)
block|{
case|case
name|PHOTOMETRIC_MINISBLACK
case|:
case|case
name|PHOTOMETRIC_MINISWHITE
case|:
name|image_type
operator|=
name|GIMP_GRAY
expr_stmt|;
name|layer_type
operator|=
operator|(
name|alpha
operator|)
condition|?
name|GIMP_GRAYA_IMAGE
else|:
name|GIMP_GRAY_IMAGE
expr_stmt|;
break|break;
case|case
name|PHOTOMETRIC_RGB
case|:
name|image_type
operator|=
name|GIMP_RGB
expr_stmt|;
name|layer_type
operator|=
operator|(
name|alpha
operator|)
condition|?
name|GIMP_RGBA_IMAGE
else|:
name|GIMP_RGB_IMAGE
expr_stmt|;
break|break;
case|case
name|PHOTOMETRIC_PALETTE
case|:
name|image_type
operator|=
name|GIMP_INDEXED
expr_stmt|;
name|layer_type
operator|=
operator|(
name|alpha
operator|)
condition|?
name|GIMP_INDEXEDA_IMAGE
else|:
name|GIMP_INDEXED_IMAGE
expr_stmt|;
break|break;
default|default:
name|worst_case
operator|=
literal|1
expr_stmt|;
block|}
if|if
condition|(
name|worst_case
condition|)
block|{
name|image_type
operator|=
name|GIMP_RGB
expr_stmt|;
name|layer_type
operator|=
name|GIMP_RGBA_IMAGE
expr_stmt|;
block|}
if|if
condition|(
operator|(
name|image
operator|=
name|gimp_image_new
argument_list|(
name|cols
argument_list|,
name|rows
argument_list|,
name|image_type
argument_list|)
operator|)
operator|==
operator|-
literal|1
condition|)
block|{
name|g_message
argument_list|(
literal|"TIFF Can't create a new image\n"
argument_list|)
expr_stmt|;
name|gimp_quit
argument_list|()
expr_stmt|;
block|}
name|gimp_image_set_filename
argument_list|(
name|image
argument_list|,
name|filename
argument_list|)
expr_stmt|;
comment|/* attach a parasite containing an ICC profile - if found in the TIFF file */
ifdef|#
directive|ifdef
name|TIFFTAG_ICCPROFILE
comment|/* If TIFFTAG_ICCPROFILE is defined we are dealing with a libtiff version           * that can handle ICC profiles. Otherwise just ignore this section. */
if|if
condition|(
name|TIFFGetField
argument_list|(
name|tif
argument_list|,
name|TIFFTAG_ICCPROFILE
argument_list|,
operator|&
name|profile_size
argument_list|,
operator|&
name|icc_profile
argument_list|)
condition|)
block|{
name|parasite
operator|=
name|gimp_parasite_new
argument_list|(
literal|"icc-profile"
argument_list|,
literal|0
argument_list|,
name|profile_size
argument_list|,
name|icc_profile
argument_list|)
expr_stmt|;
name|gimp_image_parasite_attach
argument_list|(
name|image
argument_list|,
name|parasite
argument_list|)
expr_stmt|;
name|gimp_parasite_free
argument_list|(
name|parasite
argument_list|)
expr_stmt|;
block|}
endif|#
directive|endif
comment|/* attach a parasite containing the compression */
if|if
condition|(
operator|!
name|TIFFGetField
argument_list|(
name|tif
argument_list|,
name|TIFFTAG_COMPRESSION
argument_list|,
operator|&
name|tmp
argument_list|)
condition|)
name|save_vals
operator|.
name|compression
operator|=
name|COMPRESSION_NONE
expr_stmt|;
else|else
name|save_vals
operator|.
name|compression
operator|=
name|tmp
expr_stmt|;
name|parasite
operator|=
name|gimp_parasite_new
argument_list|(
literal|"tiff-save-options"
argument_list|,
literal|0
argument_list|,
sizeof|sizeof
argument_list|(
name|save_vals
argument_list|)
argument_list|,
operator|&
name|save_vals
argument_list|)
expr_stmt|;
name|gimp_image_parasite_attach
argument_list|(
name|image
argument_list|,
name|parasite
argument_list|)
expr_stmt|;
name|gimp_parasite_free
argument_list|(
name|parasite
argument_list|)
expr_stmt|;
comment|/* Attach a parasite containing the image description.  Pretend to    * be a gimp comment so other plugins will use this description as    * an image comment where appropriate. */
block|{
name|char
modifier|*
name|img_desc
decl_stmt|;
if|if
condition|(
name|TIFFGetField
argument_list|(
name|tif
argument_list|,
name|TIFFTAG_IMAGEDESCRIPTION
argument_list|,
operator|&
name|img_desc
argument_list|)
condition|)
block|{
name|int
name|len
decl_stmt|;
name|len
operator|=
name|strlen
argument_list|(
name|img_desc
argument_list|)
operator|+
literal|1
expr_stmt|;
name|len
operator|=
name|MIN
argument_list|(
name|len
argument_list|,
literal|241
argument_list|)
expr_stmt|;
name|img_desc
index|[
name|len
operator|-
literal|1
index|]
operator|=
literal|'\000'
expr_stmt|;
name|parasite
operator|=
name|gimp_parasite_new
argument_list|(
literal|"gimp-comment"
argument_list|,
name|GIMP_PARASITE_PERSISTENT
argument_list|,
name|len
argument_list|,
name|img_desc
argument_list|)
expr_stmt|;
name|gimp_image_parasite_attach
argument_list|(
name|image
argument_list|,
name|parasite
argument_list|)
expr_stmt|;
name|gimp_parasite_free
argument_list|(
name|parasite
argument_list|)
expr_stmt|;
block|}
block|}
comment|/* any resolution info in the file? */
block|{
name|gfloat
name|xres
init|=
literal|72.0
decl_stmt|,
name|yres
init|=
literal|72.0
decl_stmt|;
name|gushort
name|read_unit
decl_stmt|;
name|GimpUnit
name|unit
init|=
name|GIMP_UNIT_PIXEL
decl_stmt|;
comment|/* invalid unit */
if|if
condition|(
name|TIFFGetField
argument_list|(
name|tif
argument_list|,
name|TIFFTAG_XRESOLUTION
argument_list|,
operator|&
name|xres
argument_list|)
condition|)
block|{
if|if
condition|(
name|TIFFGetField
argument_list|(
name|tif
argument_list|,
name|TIFFTAG_YRESOLUTION
argument_list|,
operator|&
name|yres
argument_list|)
condition|)
block|{
if|if
condition|(
name|TIFFGetFieldDefaulted
argument_list|(
name|tif
argument_list|,
name|TIFFTAG_RESOLUTIONUNIT
argument_list|,
operator|&
name|read_unit
argument_list|)
condition|)
block|{
switch|switch
condition|(
name|read_unit
condition|)
block|{
case|case
name|RESUNIT_NONE
case|:
comment|/* ImageMagick writes files with this silly resunit */
name|g_message
argument_list|(
literal|"TIFF warning: resolution units meaningless\n"
argument_list|)
expr_stmt|;
break|break;
case|case
name|RESUNIT_INCH
case|:
name|unit
operator|=
name|GIMP_UNIT_INCH
expr_stmt|;
break|break;
case|case
name|RESUNIT_CENTIMETER
case|:
name|xres
operator|*=
literal|2.54
expr_stmt|;
name|yres
operator|*=
literal|2.54
expr_stmt|;
name|unit
operator|=
name|GIMP_UNIT_MM
expr_stmt|;
comment|/* as this is our default metric unit */
break|break;
default|default:
name|g_message
argument_list|(
literal|"TIFF file error: unknown resolution unit type %d, "
literal|"assuming dpi\n"
argument_list|,
name|read_unit
argument_list|)
expr_stmt|;
break|break;
block|}
block|}
else|else
block|{
comment|/* no res unit tag */
comment|/* old AppleScan software produces these */
name|g_message
argument_list|(
literal|"TIFF warning: resolution specified without\n"
literal|"any units tag, assuming dpi\n"
argument_list|)
expr_stmt|;
block|}
block|}
else|else
block|{
comment|/* xres but no yres */
name|g_message
argument_list|(
literal|"TIFF warning: no y resolution info, assuming same as x\n"
argument_list|)
expr_stmt|;
name|yres
operator|=
name|xres
expr_stmt|;
block|}
comment|/* now set the new image's resolution info */
comment|/* If it is invalid, instead of forcing 72dpi, do not set the resolution  	 at all. Gimp will then use the default set by the user */
if|if
condition|(
name|read_unit
operator|!=
name|RESUNIT_NONE
condition|)
block|{
name|gimp_image_set_resolution
argument_list|(
name|image
argument_list|,
name|xres
argument_list|,
name|yres
argument_list|)
expr_stmt|;
if|if
condition|(
name|unit
operator|!=
name|GIMP_UNIT_PIXEL
condition|)
name|gimp_image_set_unit
argument_list|(
name|image
argument_list|,
name|unit
argument_list|)
expr_stmt|;
block|}
block|}
comment|/* no x res tag => we assume we have no resolution info, so we      * don't care.  Older versions of this plugin used to write files      * with no resolution tags at all. */
comment|/* TODO: haven't caught the case where yres tag is present, but        not xres.  This is left as an exercise for the reader - they        should feel free to shoot the author of the broken program        that produced the damaged TIFF file in the first place. */
block|}
comment|/* Install colormap for INDEXED images only */
if|if
condition|(
name|image_type
operator|==
name|GIMP_INDEXED
condition|)
block|{
if|if
condition|(
operator|!
name|TIFFGetField
argument_list|(
name|tif
argument_list|,
name|TIFFTAG_COLORMAP
argument_list|,
operator|&
name|redmap
argument_list|,
operator|&
name|greenmap
argument_list|,
operator|&
name|bluemap
argument_list|)
condition|)
block|{
name|g_message
argument_list|(
literal|"TIFF Can't get colormaps\n"
argument_list|)
expr_stmt|;
name|gimp_quit
argument_list|()
expr_stmt|;
block|}
for|for
control|(
name|i
operator|=
literal|0
operator|,
name|j
operator|=
literal|0
init|;
name|i
operator|<
operator|(
literal|1
operator|<<
name|bps
operator|)
condition|;
name|i
operator|++
control|)
block|{
name|cmap
index|[
name|j
operator|++
index|]
operator|=
name|redmap
index|[
name|i
index|]
operator|>>
literal|8
expr_stmt|;
name|cmap
index|[
name|j
operator|++
index|]
operator|=
name|greenmap
index|[
name|i
index|]
operator|>>
literal|8
expr_stmt|;
name|cmap
index|[
name|j
operator|++
index|]
operator|=
name|bluemap
index|[
name|i
index|]
operator|>>
literal|8
expr_stmt|;
block|}
name|gimp_image_set_cmap
argument_list|(
name|image
argument_list|,
name|cmap
argument_list|,
operator|(
literal|1
operator|<<
name|bps
operator|)
argument_list|)
expr_stmt|;
block|}
comment|/* Allocate channel_data for all channels, even the background layer */
name|channel
operator|=
name|g_new
argument_list|(
name|channel_data
argument_list|,
name|extra
operator|+
literal|1
argument_list|)
expr_stmt|;
name|layer
operator|=
name|gimp_layer_new
argument_list|(
name|image
argument_list|,
name|_
argument_list|(
literal|"Background"
argument_list|)
argument_list|,
name|cols
argument_list|,
name|rows
argument_list|,
name|layer_type
argument_list|,
literal|100
argument_list|,
name|GIMP_NORMAL_MODE
argument_list|)
expr_stmt|;
name|channel
index|[
literal|0
index|]
operator|.
name|ID
operator|=
name|layer
expr_stmt|;
name|gimp_image_add_layer
argument_list|(
name|image
argument_list|,
name|layer
argument_list|,
literal|0
argument_list|)
expr_stmt|;
name|channel
index|[
literal|0
index|]
operator|.
name|drawable
operator|=
name|gimp_drawable_get
argument_list|(
name|layer
argument_list|)
expr_stmt|;
if|if
condition|(
name|extra
operator|>
literal|0
operator|&&
operator|!
name|worst_case
condition|)
block|{
comment|/* Add alpha channels as appropriate */
for|for
control|(
name|i
operator|=
literal|1
init|;
name|i
operator|<=
name|extra
condition|;
operator|++
name|i
control|)
block|{
name|channel
index|[
name|i
index|]
operator|.
name|ID
operator|=
name|gimp_channel_new
argument_list|(
name|image
argument_list|,
name|_
argument_list|(
literal|"TIFF Channel"
argument_list|)
argument_list|,
name|cols
argument_list|,
name|rows
argument_list|,
literal|100.0
argument_list|,
operator|&
name|color
argument_list|)
expr_stmt|;
name|gimp_image_add_channel
argument_list|(
name|image
argument_list|,
name|channel
index|[
name|i
index|]
operator|.
name|ID
argument_list|,
literal|0
argument_list|)
expr_stmt|;
name|channel
index|[
name|i
index|]
operator|.
name|drawable
operator|=
name|gimp_drawable_get
argument_list|(
name|channel
index|[
name|i
index|]
operator|.
name|ID
argument_list|)
expr_stmt|;
block|}
block|}
if|if
condition|(
name|bps
operator|==
literal|16
condition|)
name|g_message
argument_list|(
argument|_(
literal|"TIFF warning: the image you are loading has 16 bits per channel.\nGIMP can only handle 8 bit, so it will be converted for you.\nInformation will be lost because of this conversion."
argument|if (worst_case) {     load_rgba (tif, channel);   } else if (TIFFIsTiled(tif)) {     load_tiles (tif, channel, bps, photomet, alpha, extra);   } else {
comment|/* Load scanlines in tile_height chunks */
argument|load_lines (tif, channel, bps, photomet, alpha, extra);   }    if (TIFFGetField (tif, TIFFTAG_ORIENTATION,&orientation)) {     GimpParam *return_vals;     int nreturn_vals;      switch (orientation)       {       case ORIENTATION_TOPLEFT: 	flip_horizontal = FALSE; 	flip_vertical = FALSE; 	break;       case ORIENTATION_TOPRIGHT: 	flip_horizontal = TRUE; 	flip_vertical = FALSE;	 	break;       case ORIENTATION_BOTRIGHT: 	flip_horizontal = TRUE; 	flip_vertical = TRUE; 	break;       case ORIENTATION_BOTLEFT: 	flip_horizontal = FALSE; 	flip_vertical = TRUE; 	break;       default: 	flip_horizontal = FALSE; 	flip_vertical = FALSE;	 	printf(
literal|"Orientation %d not handled yet!\n"
argument|, orientation); 	break;       }      if (flip_horizontal || flip_vertical)       gimp_image_undo_disable (image);          if (flip_horizontal)       { 	return_vals = gimp_run_procedure (
literal|"gimp_flip"
argument|,&nreturn_vals, 					  GIMP_PDB_DRAWABLE,  					  layer, 					  GIMP_PDB_INT32,
literal|0
argument|, 					  GIMP_PDB_END); 	gimp_destroy_params (return_vals, nreturn_vals);       }     if (flip_vertical)       { 	return_vals = gimp_run_procedure (
literal|"gimp_flip"
argument|,&nreturn_vals, 					  GIMP_PDB_DRAWABLE, 					  layer, 					  GIMP_PDB_INT32,
literal|1
argument|, 					  GIMP_PDB_END); 	gimp_destroy_params (return_vals, nreturn_vals);       }      if (flip_horizontal || flip_vertical)       gimp_image_undo_enable (image);   }    for (i=
literal|0
argument|; !worst_case&& i< extra; ++i) {     gimp_drawable_flush (channel[i].drawable);     gimp_drawable_detach (channel[i].drawable);   }    return image; }  static void load_rgba (TIFF *tif, channel_data *channel) {   uint32 imageWidth, imageLength;   uint32 row;   uint32 *buffer;    TIFFGetField(tif, TIFFTAG_IMAGEWIDTH,&imageWidth);   TIFFGetField(tif, TIFFTAG_IMAGELENGTH,&imageLength);   gimp_pixel_rgn_init (&(channel[
literal|0
argument|].pixel_rgn), channel[
literal|0
argument|].drawable,
literal|0
argument|,
literal|0
argument|, imageWidth, imageLength, TRUE, FALSE);   buffer = g_new(uint32, imageWidth * imageLength);   channel[
literal|0
argument|].pixels = (guchar*) buffer;   if (buffer == NULL) {     g_message(
literal|"TIFF Unable to allocate temporary buffer\n"
argument|);   }   if (!TIFFReadRGBAImage(tif, imageWidth, imageLength, buffer,
literal|0
argument|))     g_message(
literal|"TIFF Unsupported layout, no RGBA loader\n"
argument|);    for (row =
literal|0
argument|; row< imageLength; ++row) {     gimp_pixel_rgn_set_rect(&(channel[
literal|0
argument|].pixel_rgn),                               channel[
literal|0
argument|].pixels + row * imageWidth *
literal|4
argument|,
literal|0
argument|, imageLength -row -
literal|1
argument|, imageWidth,
literal|1
argument|);     if (run_mode == GIMP_RUN_INTERACTIVE)       gimp_progress_update ((double) row / (double) imageLength);   } }  static void load_tiles (TIFF *tif, channel_data *channel, 	   unsigned short bps, unsigned short photomet, 	   int alpha, int extra) {   uint16 planar= PLANARCONFIG_CONTIG;   uint32 imageWidth, imageLength;   uint32 tileWidth, tileLength;   uint32 x, y, rows, cols;   guchar *buffer;   double progress=
literal|0.0
argument|, one_row;   int i;    TIFFGetField(tif, TIFFTAG_PLANARCONFIG,&planar);   TIFFGetField(tif, TIFFTAG_IMAGEWIDTH,&imageWidth);   TIFFGetField(tif, TIFFTAG_IMAGELENGTH,&imageLength);   TIFFGetField(tif, TIFFTAG_TILEWIDTH,&tileWidth);   TIFFGetField(tif, TIFFTAG_TILELENGTH,&tileLength);   one_row = (double) tileLength / (double) imageLength;   buffer = g_malloc(TIFFTileSize(tif));    for (i=
literal|0
argument|; i<= extra; ++i) {     channel[i].pixels= g_new(guchar, tileWidth * tileLength *                                       channel[i].drawable->bpp);   }    for (y =
literal|0
argument|; y< imageLength; y += tileLength) {     for (x =
literal|0
argument|; x< imageWidth; x += tileWidth) {       if (run_mode == GIMP_RUN_INTERACTIVE)         gimp_progress_update (progress + one_row *                               ( (double) x / (double) imageWidth));       TIFFReadTile(tif, buffer, x, y,
literal|0
argument|,
literal|0
argument|);       cols= MIN(imageWidth - x, tileWidth);       rows= MIN(imageLength - y, tileLength);       if (bps ==
literal|16
argument|) {         read_16bit(buffer, channel, photomet, y, x, rows, cols, alpha,                    extra, tileWidth - cols);       } else if (bps ==
literal|8
argument|) {         read_8bit(buffer, channel, photomet, y, x, rows, cols, alpha,                   extra, tileWidth - cols);       } else {         read_default(buffer, channel, bps, photomet, y, x, rows, cols,                      alpha, extra, tileWidth - cols);       }     }     progress+= one_row;   }   for (i=
literal|0
argument|; i<= extra; ++i) {     g_free(channel[i].pixels);   }   g_free(buffer); }  static void load_lines (TIFF *tif, channel_data *channel, 	    unsigned short bps, unsigned short photomet, 	    int alpha, int extra) {   uint16 planar= PLANARCONFIG_CONTIG;   uint32 imageLength, lineSize, cols, rows;   guchar *buffer;   int i, y, tile_height = gimp_tile_height ();    TIFFGetField(tif, TIFFTAG_PLANARCONFIG,&planar);   TIFFGetField(tif, TIFFTAG_IMAGELENGTH,&imageLength);   TIFFGetField(tif, TIFFTAG_IMAGEWIDTH,&cols);   lineSize= TIFFScanlineSize(tif);    for (i=
literal|0
argument|; i<= extra; ++i) {     channel[i].pixels= g_new(guchar, tile_height * cols                                           * channel[i].drawable->bpp);   }    buffer = g_malloc(lineSize * tile_height);   if (planar == PLANARCONFIG_CONTIG) {     for (y =
literal|0
argument|; y< imageLength; y+= tile_height ) {       if (run_mode == GIMP_RUN_INTERACTIVE)         gimp_progress_update ( (double) y / (double) imageLength);       rows = MIN(tile_height, imageLength - y);       for (i =
literal|0
argument|; i< rows; ++i) 	TIFFReadScanline(tif, buffer + i * lineSize, y + i,
literal|0
argument|);       if (bps ==
literal|16
argument|) { 	read_16bit(buffer, channel, photomet, y,
literal|0
argument|, rows, cols,                    alpha, extra,
literal|0
argument|);       } else if (bps ==
literal|8
argument|) { 	read_8bit(buffer, channel, photomet, y,
literal|0
argument|, rows, cols,                   alpha, extra,
literal|0
argument|);       } else { 	read_default(buffer, channel, bps, photomet, y,
literal|0
argument|, rows, cols,                      alpha, extra,
literal|0
argument|);       }     }   } else {
comment|/* PLANARCONFIG_SEPARATE  -- Just say "No" */
argument|uint16 s, samples;     TIFFGetField(tif, TIFFTAG_SAMPLESPERPIXEL,&samples);     for (s =
literal|0
argument|; s< samples; ++s) {       for (y =
literal|0
argument|; y< imageLength; y+= tile_height ) {         if (run_mode == GIMP_RUN_INTERACTIVE) 	  gimp_progress_update ( (double) y / (double) imageLength); 	rows = MIN(tile_height, imageLength - y); 	for (i =
literal|0
argument|; i< rows; ++i) 	  TIFFReadScanline(tif, buffer + i * lineSize, y + i, s); 	read_separate (buffer, channel, bps, photomet, 		         y,
literal|0
argument|, rows, cols, alpha, extra, s);       }     }   }   for (i=
literal|0
argument|; i<= extra; ++i) {     g_free(channel[i].pixels);   }   g_free(buffer); }  static void read_16bit (guchar       *source, 	    channel_data *channel, 	    gushort       photomet, 	    gint          startrow, 	    gint          startcol, 	    gint          rows, 	    gint          cols, 	    gint          alpha,             gint          extra,             gint          align) {   guchar *dest;   gint    gray_val, red_val, green_val, blue_val, alpha_val;   gint    col, row, i;    for (i=
literal|0
argument|; i<= extra; ++i) {     gimp_pixel_rgn_init (&(channel[i].pixel_rgn), channel[i].drawable,                           startcol, startrow, cols, rows, TRUE, FALSE);   }
if|#
directive|if
name|G_BYTE_ORDER
operator|==
name|G_LITTLE_ENDIAN
argument|source++;
comment|/* offset source once, to look at the high byte */
endif|#
directive|endif
argument|for (row =
literal|0
argument|; row< rows; ++row) {     dest= channel[
literal|0
argument|].pixels + row * cols * channel[
literal|0
argument|].drawable->bpp;      for (i=
literal|1
argument|; i<= extra; ++i) {       channel[i].pixel= channel[i].pixels + row * cols;     }      for (col =
literal|0
argument|; col< cols; col++) {       switch (photomet) {         case PHOTOMETRIC_MINISBLACK:           if (alpha) {             gray_val= *source; source+=
literal|2
argument|;             alpha_val= *source; source+=
literal|2
argument|;             gray_val= MIN(gray_val, alpha_val);             if (alpha_val)               *dest++ = gray_val *
literal|255
argument|/ alpha_val;             else               *dest++ =
literal|0
argument|;             *dest++ = alpha_val;           } else {             *dest++ = *source; source+=
literal|2
argument|;           }           break;          case PHOTOMETRIC_MINISWHITE:           if (alpha) {             gray_val= *source; source+=
literal|2
argument|;             alpha_val= *source; source+=
literal|2
argument|;             gray_val= MIN(gray_val, alpha_val);             if (alpha_val)               *dest++ = ((alpha_val - gray_val) *
literal|255
argument|) / alpha_val;             else               *dest++ =
literal|0
argument|;             *dest++ = alpha_val;           } else {             *dest++ = ~(*source); source+=
literal|2
argument|;           }           break;          case PHOTOMETRIC_PALETTE:           *dest++= *source; source+=
literal|2
argument|;           if (alpha) *dest++= *source; source+=
literal|2
argument|;           break;            case PHOTOMETRIC_RGB:           if (alpha) {             red_val= *source; source+=
literal|2
argument|;             green_val= *source; source+=
literal|2
argument|;             blue_val= *source; source+=
literal|2
argument|;             alpha_val= *source; source+=
literal|2
argument|;             red_val= MIN(red_val, alpha_val);             green_val= MIN(green_val, alpha_val);             blue_val= MIN(blue_val, alpha_val);             if (alpha_val) {               *dest++ = (red_val *
literal|255
argument|) / alpha_val;               *dest++ = (green_val *
literal|255
argument|) / alpha_val;               *dest++ = (blue_val *
literal|255
argument|) / alpha_val;             } else {               *dest++ =
literal|0
argument|;               *dest++ =
literal|0
argument|;               *dest++ =
literal|0
argument|; 	    } 	    *dest++ = alpha_val; 	  } else { 	    *dest++ = *source; source+=
literal|2
argument|; 	    *dest++ = *source; source+=
literal|2
argument|; 	    *dest++ = *source; source+=
literal|2
argument|; 	  }           break;          default:
comment|/* This case was handled earlier */
argument|g_assert_not_reached();       }       for (i=
literal|1
argument|; i<= extra; ++i) {         *channel[i].pixel++ = *source; source+=
literal|2
argument|;       }     }     if (align) {       switch (photomet) {         case PHOTOMETRIC_MINISBLACK:         case PHOTOMETRIC_MINISWHITE:         case PHOTOMETRIC_PALETTE:           source+= align * (
literal|1
argument|+ alpha + extra) *
literal|2
argument|;           break;         case PHOTOMETRIC_RGB:           source+= align * (
literal|3
argument|+ alpha + extra) *
literal|2
argument|;           break;       }     }   }   for (i=
literal|0
argument|; i<= extra; ++i) {     gimp_pixel_rgn_set_rect(&(channel[i].pixel_rgn), channel[i].pixels,                               startcol, startrow, cols, rows);   } }  static void read_8bit (guchar       *source, 	   channel_data *channel, 	   gushort       photomet, 	   gint          startrow, 	   gint          startcol, 	   gint          rows, 	   gint          cols, 	   gint          alpha, 	   gint          extra, 	   gint          align) {   guchar *dest;   gint    gray_val, red_val, green_val, blue_val, alpha_val;   gint    col, row, i;    for (i=
literal|0
argument|; i<= extra; ++i) {     gimp_pixel_rgn_init (&(channel[i].pixel_rgn), channel[i].drawable,                           startcol, startrow, cols, rows, TRUE, FALSE);   }    for (row =
literal|0
argument|; row< rows; ++row) {     dest= channel[
literal|0
argument|].pixels + row * cols * channel[
literal|0
argument|].drawable->bpp;      for (i=
literal|1
argument|; i<= extra; ++i) {       channel[i].pixel= channel[i].pixels + row * cols;     }      for (col =
literal|0
argument|; col< cols; col++) {       switch (photomet) {         case PHOTOMETRIC_MINISBLACK:           if (alpha) {             gray_val= *source++;             alpha_val= *source++;             gray_val= MIN(gray_val, alpha_val);             if (alpha_val)               *dest++ = gray_val *
literal|255
argument|/ alpha_val;             else               *dest++ =
literal|0
argument|;             *dest++ = alpha_val;           } else {             *dest++ = *source++;           }           break;          case PHOTOMETRIC_MINISWHITE:           if (alpha) {             gray_val= *source++;             alpha_val= *source++;             gray_val= MIN(gray_val, alpha_val);             if (alpha_val)               *dest++ = ((alpha_val - gray_val) *
literal|255
argument|) / alpha_val;             else               *dest++ =
literal|0
argument|;             *dest++ = alpha_val;           } else {             *dest++ = ~(*source++);           }           break;          case PHOTOMETRIC_PALETTE:           *dest++= *source++;           if (alpha) *dest++= *source++;           break;            case PHOTOMETRIC_RGB:           if (alpha) {             red_val= *source++;             green_val= *source++;             blue_val= *source++;             alpha_val= *source++;             red_val= MIN(red_val, alpha_val);             blue_val= MIN(blue_val, alpha_val);             green_val= MIN(green_val, alpha_val);             if (alpha_val) {               *dest++ = (red_val *
literal|255
argument|) / alpha_val;               *dest++ = (green_val *
literal|255
argument|) / alpha_val;               *dest++ = (blue_val *
literal|255
argument|) / alpha_val;             } else {               *dest++ =
literal|0
argument|;               *dest++ =
literal|0
argument|;               *dest++ =
literal|0
argument|; 	    } 	    *dest++ = alpha_val; 	  } else { 	    *dest++ = *source++; 	    *dest++ = *source++; 	    *dest++ = *source++; 	  }           break;          default:
comment|/* This case was handled earlier */
argument|g_assert_not_reached();       }       for (i=
literal|1
argument|; i<= extra; ++i) {         *channel[i].pixel++ = *source++;       }     }     if (align) {       switch (photomet) {         case PHOTOMETRIC_MINISBLACK:         case PHOTOMETRIC_MINISWHITE:         case PHOTOMETRIC_PALETTE:           source+= align * (
literal|1
argument|+ alpha + extra);           break;         case PHOTOMETRIC_RGB:           source+= align * (
literal|3
argument|+ alpha + extra);           break;       }     }   }   for (i=
literal|0
argument|; i<= extra; ++i) {     gimp_pixel_rgn_set_rect(&(channel[i].pixel_rgn), channel[i].pixels,                               startcol, startrow, cols, rows);   } }
comment|/* Step through all<= 8-bit samples in an image */
define|#
directive|define
name|NEXTSAMPLE
parameter_list|(
name|var
parameter_list|)
define|\
value|{                                           \       if (bitsleft == 0)                      \       {                                       \ 	  source++;                           \ 	  bitsleft = 8;                       \       }                                       \       bitsleft -= bps;                        \       var = ( *source>> bitsleft )& maxval; \   }
argument|static void read_default (guchar       *source, 	      channel_data *channel, 	      gushort       bps, 	      gushort       photomet, 	      gint          startrow, 	      gint          startcol, 	      gint          rows, 	      gint          cols, 	      gint          alpha, 	      gint          extra,               gint          align) {   guchar *dest;   gint    gray_val, red_val, green_val, blue_val, alpha_val;   gint    col, row, i;   gint    bitsleft =
literal|8
argument|, maxval = (
literal|1
argument|<< bps) -
literal|1
argument|;    for (i=
literal|0
argument|; i<= extra; ++i) {     gimp_pixel_rgn_init (&(channel[i].pixel_rgn), channel[i].drawable, 		startcol, startrow, cols, rows, TRUE, FALSE);   }    for (row =
literal|0
argument|; row< rows; ++row) {     dest= channel[
literal|0
argument|].pixels + row * cols * channel[
literal|0
argument|].drawable->bpp;      for (i=
literal|1
argument|; i<= extra; ++i) {       channel[i].pixel= channel[i].pixels + row * cols;     }      for (col =
literal|0
argument|; col< cols; col++) {       switch (photomet) {         case PHOTOMETRIC_MINISBLACK:           NEXTSAMPLE(gray_val);           if (alpha) {             NEXTSAMPLE(alpha_val);             gray_val= MIN(gray_val, alpha_val);             if (alpha_val)               *dest++ = (gray_val *
literal|65025
argument|) / (alpha_val * maxval);             else               *dest++ =
literal|0
argument|;             *dest++ = alpha_val;           } else {             *dest++ = (gray_val *
literal|255
argument|) / maxval;           }           break;          case PHOTOMETRIC_MINISWHITE:           NEXTSAMPLE(gray_val);           if (alpha) {             NEXTSAMPLE(alpha_val);             gray_val= MIN(gray_val, alpha_val);             if (alpha_val)               *dest++ = ((maxval - gray_val) *
literal|65025
argument|) / (alpha_val * maxval);             else               *dest++ =
literal|0
argument|;             *dest++ = alpha_val;           } else {             *dest++ = ((maxval - gray_val) *
literal|255
argument|) / maxval;           }           break;          case PHOTOMETRIC_PALETTE:           NEXTSAMPLE(*dest++);           if (alpha) {             NEXTSAMPLE(*dest++);           }           break;            case PHOTOMETRIC_RGB:           NEXTSAMPLE(red_val)           NEXTSAMPLE(green_val)           NEXTSAMPLE(blue_val)           if (alpha) {             NEXTSAMPLE(alpha_val)             red_val= MIN(red_val, alpha_val);             blue_val= MIN(blue_val, alpha_val);             green_val= MIN(green_val, alpha_val);             if (alpha_val) {               *dest++ = (red_val *
literal|255
argument|) / alpha_val;               *dest++ = (green_val *
literal|255
argument|) / alpha_val;               *dest++ = (blue_val *
literal|255
argument|) / alpha_val;             } else {               *dest++ =
literal|0
argument|;               *dest++ =
literal|0
argument|;               *dest++ =
literal|0
argument|; 	    } 	    *dest++ = alpha_val; 	  } else { 	    *dest++ = red_val; 	    *dest++ = green_val; 	    *dest++ = blue_val; 	  }           break;          default:
comment|/* This case was handled earlier */
argument|g_assert_not_reached();       }       for (i=
literal|1
argument|; i<= extra; ++i) {         NEXTSAMPLE(alpha_val);         *channel[i].pixel++ = alpha_val;       }     }     if (align) {       switch (photomet) {         case PHOTOMETRIC_MINISBLACK:         case PHOTOMETRIC_MINISWHITE:         case PHOTOMETRIC_PALETTE:           for (i=
literal|0
argument|; i< align * (
literal|1
argument|+ alpha + extra); ++i) {             NEXTSAMPLE(alpha_val);           }           break;         case PHOTOMETRIC_RGB:           for (i=
literal|0
argument|; i< align * (
literal|3
argument|+ alpha + extra); ++i) {             NEXTSAMPLE(alpha_val);           }           break;       }     }     bitsleft=
literal|0
argument|;   }   for (i=
literal|0
argument|; i<= extra; ++i) {     gimp_pixel_rgn_set_rect(&(channel[i].pixel_rgn), channel[i].pixels,                               startcol, startrow, cols, rows);   } }  static void read_separate (guchar       *source, 	       channel_data *channel,                gushort       bps, 	       gushort       photomet,                gint          startrow, 	       gint          startcol, 	       gint          rows, 	       gint          cols,                gint          alpha, 	       gint          extra, 	       gint          sample) {   guchar *dest;   gint    col, row, c;   gint    bitsleft =
literal|8
argument|, maxval = (
literal|1
argument|<< bps) -
literal|1
argument|;    if (bps>
literal|8
argument|) {     g_message(
literal|"TIFF Unsupported layout\n"
argument|);     gimp_quit();   }    if (sample< channel[
literal|0
argument|].drawable->bpp) {     c =
literal|0
argument|;   } else {     c = (sample - channel[
literal|0
argument|].drawable->bpp) +
literal|4
argument|;     photomet = PHOTOMETRIC_MINISBLACK;   }    gimp_pixel_rgn_init (&(channel[c].pixel_rgn), channel[c].drawable,                          startcol, startrow, cols, rows, TRUE, FALSE);    gimp_pixel_rgn_get_rect(&(channel[c].pixel_rgn), channel[c].pixels,                             startcol, startrow, cols, rows);   for (row =
literal|0
argument|; row< rows; ++row) {     dest = channel[c].pixels + row * cols * channel[c].drawable->bpp;     if (c ==
literal|0
argument|) {       for (col =
literal|0
argument|; col< cols; ++col) {         NEXTSAMPLE(dest[col * channel[
literal|0
argument|].drawable->bpp + sample]);       }     } else {       for (col =
literal|0
argument|; col< cols; ++col)         NEXTSAMPLE(dest[col]);     }   }   gimp_pixel_rgn_set_rect(&(channel[c].pixel_rgn), channel[c].pixels,                             startcol, startrow, cols, rows); }
comment|/* ** pnmtotiff.c - converts a portable anymap to a Tagged Image File ** ** Derived by Jef Poskanzer from ras2tif.c, which is: ** ** Copyright (c) 1990 by Sun Microsystems, Inc. ** ** Author: Patrick J. Naughton ** naughton@wind.sun.com ** ** Permission to use, copy, modify, and distribute this software and its ** documentation for any purpose and without fee is hereby granted, ** provided that the above copyright notice appear in all copies and that ** both that copyright notice and this permission notice appear in ** supporting documentation. ** ** This file is provided AS IS with no warranties of any kind.  The author ** shall have no liability with respect to the infringement of copyrights, ** trade secrets or any patents by this file or any part thereof.  In no ** event will the author be liable for any lost revenue or profits or ** other special, indirect and consequential damages. */
argument|static gint save_image (gchar   *filename,  	    gint32   image,  	    gint32   layer, 	    gint32   orig_image)
comment|/* the export function might have created a duplicate */
argument|{   TIFF          *tif;   gushort        red[
literal|256
argument|];   gushort        grn[
literal|256
argument|];   gushort        blu[
literal|256
argument|];   gint           cols, col, rows, row, i;   glong          rowsperstrip;   gushort        compression;   gushort        extra_samples[
literal|1
argument|];   gint           alpha;   gshort         predictor;   gshort         photometric;   gshort         samplesperpixel;   gshort         bitspersample;   gint           bytesperrow;   guchar        *t, *src, *data;   guchar        *cmap;   gint           colors;   gint           success;   GimpDrawable     *drawable;   GimpImageType  drawable_type;   GimpPixelRgn      pixel_rgn;   gint           tile_height;   gint           y, yend;   gchar         *name;    compression = tsvals.compression;
comment|/* Disabled because this isn't in older releases of libtiff, and it      wasn't helping much anyway */
if|#
directive|if
literal|0
argument|if (TIFFFindCODEC((uint16) compression) == NULL)     compression = COMPRESSION_NONE;
comment|/* CODEC not available */
endif|#
directive|endif
argument|predictor =
literal|0
argument|;   tile_height = gimp_tile_height ();   rowsperstrip = tile_height;    TIFFSetWarningHandler (tiff_warning);   TIFFSetErrorHandler (tiff_error);    tif = TIFFOpen (filename,
literal|"w"
argument|);   if (!tif)      {       g_print (
literal|"Can't write image to\n%s"
argument|, filename);       return
literal|0
argument|;     }    if (run_mode == GIMP_RUN_INTERACTIVE) {     name = g_strdup_printf( _(
literal|"Saving %s:"
argument|), filename);     gimp_progress_init (name);     g_free (name);   }    drawable = gimp_drawable_get (layer);   drawable_type = gimp_drawable_type (layer);   gimp_pixel_rgn_init (&pixel_rgn, drawable,
literal|0
argument|,
literal|0
argument|, drawable->width, drawable->height, FALSE, FALSE);    cols = drawable->width;   rows = drawable->height;    switch (drawable_type)     {     case GIMP_RGB_IMAGE:       predictor =
literal|2
argument|;       samplesperpixel =
literal|3
argument|;       bitspersample =
literal|8
argument|;       photometric = PHOTOMETRIC_RGB;       bytesperrow = cols *
literal|3
argument|;       alpha =
literal|0
argument|;       break;     case GIMP_GRAY_IMAGE:       samplesperpixel =
literal|1
argument|;       bitspersample =
literal|8
argument|;       photometric = PHOTOMETRIC_MINISBLACK;       bytesperrow = cols;       alpha =
literal|0
argument|;       break;     case GIMP_RGBA_IMAGE:       predictor =
literal|2
argument|;       samplesperpixel =
literal|4
argument|;       bitspersample =
literal|8
argument|;       photometric = PHOTOMETRIC_RGB;       bytesperrow = cols *
literal|4
argument|;       alpha =
literal|1
argument|;       break;     case GIMP_GRAYA_IMAGE:       samplesperpixel =
literal|2
argument|;       bitspersample =
literal|8
argument|;       photometric = PHOTOMETRIC_MINISBLACK;       bytesperrow = cols *
literal|2
argument|;       alpha =
literal|1
argument|;       break;     case GIMP_INDEXED_IMAGE:       samplesperpixel =
literal|1
argument|;       bitspersample =
literal|8
argument|;       photometric = PHOTOMETRIC_PALETTE;       bytesperrow = cols;       alpha =
literal|0
argument|;        cmap = gimp_image_get_cmap (image,&colors);        for (i =
literal|0
argument|; i< colors; i++) 	{ 	  red[i] = *cmap++ *
literal|65535
argument|/
literal|255
argument|; 	  grn[i] = *cmap++ *
literal|65535
argument|/
literal|255
argument|; 	  blu[i] = *cmap++ *
literal|65535
argument|/
literal|255
argument|; 	}       break;     case GIMP_INDEXEDA_IMAGE:       return
literal|0
argument|;      default:       return
literal|0
argument|;     }
comment|/* Set TIFF parameters. */
argument|TIFFSetField (tif, TIFFTAG_SUBFILETYPE,
literal|0
argument|);   TIFFSetField (tif, TIFFTAG_IMAGEWIDTH, cols);   TIFFSetField (tif, TIFFTAG_IMAGELENGTH, rows);   TIFFSetField (tif, TIFFTAG_BITSPERSAMPLE, bitspersample);   TIFFSetField (tif, TIFFTAG_ORIENTATION, ORIENTATION_TOPLEFT);   TIFFSetField (tif, TIFFTAG_COMPRESSION, compression);   if ((compression == COMPRESSION_LZW || compression == COMPRESSION_DEFLATE)&& (predictor !=
literal|0
argument|)) {     TIFFSetField (tif, TIFFTAG_PREDICTOR, predictor);   }   if (alpha) {       extra_samples [
literal|0
argument|] = EXTRASAMPLE_ASSOCALPHA;       TIFFSetField (tif, TIFFTAG_EXTRASAMPLES,
literal|1
argument|, extra_samples);   }   TIFFSetField (tif, TIFFTAG_PHOTOMETRIC, photometric);   TIFFSetField (tif, TIFFTAG_DOCUMENTNAME, filename);   TIFFSetField (tif, TIFFTAG_SAMPLESPERPIXEL, samplesperpixel);   TIFFSetField (tif, TIFFTAG_ROWSPERSTRIP, rowsperstrip);
comment|/* TIFFSetField( tif, TIFFTAG_STRIPBYTECOUNTS, rows / rowsperstrip ); */
argument|TIFFSetField (tif, TIFFTAG_PLANARCONFIG, PLANARCONFIG_CONTIG);
comment|/* resolution fields */
argument|{     gdouble  xresolution;     gdouble  yresolution;     gushort  save_unit = RESUNIT_INCH;     GimpUnit unit;     gfloat   factor;      gimp_image_get_resolution (orig_image,&xresolution,&yresolution);     unit = gimp_image_get_unit (orig_image);     factor = gimp_unit_get_factor (unit);
comment|/*  if we have a metric unit, save the resolution as centimeters      */
argument|if ((ABS (factor -
literal|0.0254
argument|)<
literal|1e-5
argument|) ||
comment|/* m  */
argument|(ABS (factor -
literal|0.254
argument|)<
literal|1e-5
argument|) ||
comment|/* dm */
argument|(ABS (factor -
literal|2.54
argument|)<
literal|1e-5
argument|) ||
comment|/* cm */
argument|(ABS (factor -
literal|25.4
argument|)<
literal|1e-5
argument|))
comment|/* mm */
argument|{ 	save_unit = RESUNIT_CENTIMETER; 	xresolution /=
literal|2.54
argument|; 	yresolution /=
literal|2.54
argument|;       }      if (xresolution>
literal|1e-5
argument|&& yresolution>
literal|1e-5
argument|)       { 	TIFFSetField (tif, TIFFTAG_XRESOLUTION, xresolution); 	TIFFSetField (tif, TIFFTAG_YRESOLUTION, yresolution); 	TIFFSetField (tif, TIFFTAG_RESOLUTIONUNIT, save_unit);       }   }
comment|/* do we have a comment?  If so, create a new parasite to hold it,    * and attach it to the image. The attach function automatically    * detaches a previous incarnation of the parasite. */
argument|if (image_comment&& *image_comment)     {       GimpParasite *parasite;              TIFFSetField (tif, TIFFTAG_IMAGEDESCRIPTION, image_comment);       parasite = gimp_parasite_new (
literal|"gimp-comment"
argument|, 				    GIMP_PARASITE_PERSISTENT, 				    strlen (image_comment) +
literal|1
argument|, image_comment);       gimp_image_parasite_attach (orig_image, parasite);       gimp_parasite_free (parasite);     }
comment|/* do we have an ICC profile? If so, write it to the TIFF file */
ifdef|#
directive|ifdef
name|TIFFTAG_ICCPROFILE
argument|{     GimpParasite *parasite;     uint32 profile_size;     guchar *icc_profile;      parasite = gimp_image_parasite_find (orig_image,
literal|"icc-profile"
argument|);     if (parasite)       {         profile_size = gimp_parasite_data_size(parasite); 	icc_profile = gimp_parasite_data(parasite);  	TIFFSetField(tif, TIFFTAG_ICCPROFILE, profile_size, icc_profile);         gimp_parasite_free(parasite);       }   }
endif|#
directive|endif
argument|if (drawable_type == GIMP_INDEXED_IMAGE)     TIFFSetField (tif, TIFFTAG_COLORMAP, red, grn, blu);
comment|/* array to rearrange data */
argument|src = g_new (guchar, bytesperrow * tile_height);   data = g_new (guchar, bytesperrow);
comment|/* Now write the TIFF data. */
argument|for (y =
literal|0
argument|; y< rows; y = yend)     {       yend = y + tile_height;       yend = MIN (yend, rows);        gimp_pixel_rgn_get_rect (&pixel_rgn, src,
literal|0
argument|, y, cols, yend - y);        for (row = y; row< yend; row++) 	{ 	  t = src + bytesperrow * (row - y);  	  switch (drawable_type) 	    { 	    case GIMP_INDEXED_IMAGE: 	      success = (TIFFWriteScanline (tif, t, row,
literal|0
argument|)>=
literal|0
argument|); 	      break; 	    case GIMP_GRAY_IMAGE: 	      success = (TIFFWriteScanline (tif, t, row,
literal|0
argument|)>=
literal|0
argument|); 	      break; 	    case GIMP_GRAYA_IMAGE: 	      for (col =
literal|0
argument|; col< cols*samplesperpixel; col+=samplesperpixel) 		{
comment|/* pre-multiply gray by alpha */
argument|data[col +
literal|0
argument|] = (t[col +
literal|0
argument|] * t[col +
literal|1
argument|]) /
literal|255
argument|; 		  data[col +
literal|1
argument|] = t[col +
literal|1
argument|];
comment|/* alpha channel */
argument|} 	      success = (TIFFWriteScanline (tif, data, row,
literal|0
argument|)>=
literal|0
argument|); 	      break; 	    case GIMP_RGB_IMAGE: 	      success = (TIFFWriteScanline (tif, t, row,
literal|0
argument|)>=
literal|0
argument|); 	      break; 	    case GIMP_RGBA_IMAGE: 	      for (col =
literal|0
argument|; col< cols*samplesperpixel; col+=samplesperpixel) 		{
comment|/* pre-multiply rgb by alpha */
argument|data[col+
literal|0
argument|] = t[col +
literal|0
argument|] * t[col +
literal|3
argument|] /
literal|255
argument|; 		  data[col+
literal|1
argument|] = t[col +
literal|1
argument|] * t[col +
literal|3
argument|] /
literal|255
argument|; 		  data[col+
literal|2
argument|] = t[col +
literal|2
argument|] * t[col +
literal|3
argument|] /
literal|255
argument|; 		  data[col+
literal|3
argument|] = t[col +
literal|3
argument|];
comment|/* alpha channel */
argument|} 	      success = (TIFFWriteScanline (tif, data, row,
literal|0
argument|)>=
literal|0
argument|); 	      break; 	    default: 	      success = FALSE; 	      break; 	    }  	  if (!success) { 	    g_message (
literal|"TIFF Failed a scanline write on row %d"
argument|, row); 	    return
literal|0
argument|; 	  } 	}        if (run_mode == GIMP_RUN_INTERACTIVE)         gimp_progress_update ((double) row / (double) rows);     }    TIFFFlushData (tif);   TIFFClose (tif);    gimp_drawable_detach (drawable);   g_free (data);    return
literal|1
argument|; }  static gint save_dialog (void) {   GtkWidget *dlg;   GtkWidget *vbox;   GtkWidget *frame;   GtkWidget *hbox;   GtkWidget *label;   GtkWidget *entry;    dlg = gimp_dialog_new ( _(
literal|"Save as TIFF"
argument|),
literal|"tiff"
argument|, 			 gimp_standard_help_func,
literal|"filters/tiff.html"
argument|, 			 GTK_WIN_POS_MOUSE, 			 FALSE, TRUE, FALSE,  			 GTK_STOCK_CANCEL, gtk_widget_destroy, 			 NULL,
literal|1
argument|, NULL, FALSE, TRUE, 			 GTK_STOCK_OK, save_ok_callback, 			 NULL, NULL, NULL, TRUE, FALSE,  			 NULL);    g_signal_connect (dlg,
literal|"destroy"
argument|,                     G_CALLBACK (gtk_main_quit),                     NULL);    vbox = gtk_vbox_new (FALSE,
literal|4
argument|);   gtk_container_set_border_width (GTK_CONTAINER (vbox),
literal|6
argument|);   gtk_box_pack_start (GTK_BOX (GTK_DIALOG (dlg)->vbox), vbox, FALSE, TRUE,
literal|0
argument|);
comment|/*  compression  */
argument|frame = gimp_radio_group_new2 (TRUE, _(
literal|"Compression"
argument|),                                  G_CALLBACK (gimp_radio_button_update),&tsvals.compression,                                  GINT_TO_POINTER (tsvals.compression),                                   _(
literal|"_None"
argument|),                                  GINT_TO_POINTER (COMPRESSION_NONE), NULL,                                   _(
literal|"_LZW"
argument|),                                  GINT_TO_POINTER (COMPRESSION_LZW), NULL,                                   _(
literal|"_Pack Bits"
argument|),                                  GINT_TO_POINTER (COMPRESSION_PACKBITS), NULL,                                   _(
literal|"_Deflate"
argument|),                                  GINT_TO_POINTER (COMPRESSION_DEFLATE), NULL,                                   _(
literal|"_JPEG"
argument|),                                  GINT_TO_POINTER (COMPRESSION_JPEG), NULL,                                   NULL);    gtk_box_pack_start (GTK_BOX (vbox), frame, FALSE, FALSE,
literal|0
argument|);   gtk_widget_show (frame);
comment|/* comment entry */
argument|hbox = gtk_hbox_new (FALSE,
literal|4
argument|);   gtk_box_pack_start (GTK_BOX (vbox), hbox, FALSE, FALSE,
literal|0
argument|);   gtk_widget_show (hbox);    label = gtk_label_new ( _(
literal|"Comment:"
argument|));   gtk_box_pack_start (GTK_BOX (hbox), label, FALSE, FALSE,
literal|0
argument|);   gtk_widget_show (label);    entry = gtk_entry_new ();   gtk_widget_show (entry);   gtk_box_pack_start (GTK_BOX (hbox), entry, TRUE, TRUE,
literal|0
argument|);   gtk_entry_set_text (GTK_ENTRY (entry), image_comment);    g_signal_connect (entry,
literal|"changed"
argument|,                     G_CALLBACK (comment_entry_callback),                     NULL);    gtk_widget_show (frame);    gtk_widget_show (vbox);   gtk_widget_show (dlg);    gtk_main ();   gdk_flush ();    return tsint.run; }  static void save_ok_callback (GtkWidget *widget, 		  gpointer   data) {   tsint.run = TRUE;   gtk_widget_destroy (GTK_WIDGET (data)); }  static void comment_entry_callback (GtkWidget *widget, 			gpointer   data) {   const gchar *text;   gint         len;    text = gtk_entry_get_text (GTK_ENTRY (widget));   len = strlen (text);
comment|/* Temporary kludge for overlength strings - just return */
argument|if (len>
literal|240
argument|)     {       g_message (
literal|"TIFF save: Your comment string is too long.\n"
argument|);       return;     }    g_free (image_comment);   image_comment = g_strdup (text);
comment|/* g_print ("COMMENT: %s\n", image_comment); */
argument|}
end_function

end_unit

