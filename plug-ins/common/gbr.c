begin_unit|revision:0.9.5;language:C;cregit-version:0.0.1
begin_comment
comment|/*  * gbr plug-in version 1.00  * Loads/saves version 2 GIMP .gbr files, by Tim Newsome<drz@frody.bloke.com>  * Some bits stolen from the .99.7 source tree.  *  * Added in GBR version 1 support after learning that there wasn't a  * tool to read them.  * July 6, 1998 by Seth Burgess<sjburges@gimp.org>  *  * Dec 17, 2000  * Load and save GIMP brushes in GRAY or RGBA.  jtl + neo  *  *  * TODO: Give some better error reporting on not opening files/bad headers  *       etc.  */
end_comment

begin_include
include|#
directive|include
file|"config.h"
end_include

begin_include
include|#
directive|include
file|<glib.h>
end_include

begin_comment
comment|/* Include early for G_OS_WIN32 */
end_comment

begin_include
include|#
directive|include
file|<errno.h>
end_include

begin_include
include|#
directive|include
file|<sys/types.h>
end_include

begin_include
include|#
directive|include
file|<sys/stat.h>
end_include

begin_include
include|#
directive|include
file|<fcntl.h>
end_include

begin_ifdef
ifdef|#
directive|ifdef
name|HAVE_UNISTD_H
end_ifdef

begin_include
include|#
directive|include
file|<unistd.h>
end_include

begin_endif
endif|#
directive|endif
end_endif

begin_include
include|#
directive|include
file|<ctype.h>
end_include

begin_include
include|#
directive|include
file|<stdio.h>
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
file|<math.h>
end_include

begin_ifdef
ifdef|#
directive|ifdef
name|G_OS_WIN32
end_ifdef

begin_include
include|#
directive|include
file|<io.h>
end_include

begin_endif
endif|#
directive|endif
end_endif

begin_ifndef
ifndef|#
directive|ifndef
name|_O_BINARY
end_ifndef

begin_define
DECL|macro|_O_BINARY
define|#
directive|define
name|_O_BINARY
value|0
end_define

begin_endif
endif|#
directive|endif
end_endif

begin_include
include|#
directive|include
file|<gtk/gtk.h>
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
file|"app/core/gimpbrush-header.h"
end_include

begin_include
include|#
directive|include
file|"app/core/gimppattern-header.h"
end_include

begin_include
include|#
directive|include
file|"libgimp/stdplugins-intl.h"
end_include

begin_comment
comment|/* Declare local data types  */
end_comment

begin_typedef
typedef|typedef
struct|struct
DECL|struct|__anon2b289fb70108
block|{
DECL|member|description
name|gchar
name|description
index|[
literal|256
index|]
decl_stmt|;
DECL|member|spacing
name|gint
name|spacing
decl_stmt|;
DECL|typedef|t_info
block|}
name|t_info
typedef|;
end_typedef

begin_decl_stmt
DECL|variable|info
name|t_info
name|info
init|=
block|{
comment|/* Initialize to this, change if non-interactive later */
literal|"GIMP Brush"
block|,
literal|10
block|}
decl_stmt|;
end_decl_stmt

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
name|gint32
name|load_image
parameter_list|(
specifier|const
name|gchar
modifier|*
name|filename
parameter_list|)
function_decl|;
end_function_decl

begin_function_decl
specifier|static
name|gint
name|save_image
parameter_list|(
specifier|const
name|gchar
modifier|*
name|filename
parameter_list|,
name|gint32
name|image_ID
parameter_list|,
name|gint32
name|drawable_ID
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
name|entry_callback
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
literal|"spacing"
block|,
literal|"Spacing of the brush"
block|}
block|,
block|{
name|GIMP_PDB_STRING
block|,
literal|"description"
block|,
literal|"Short description of the brush"
block|}
block|}
decl_stmt|;
name|gimp_install_procedure
argument_list|(
literal|"file_gbr_load"
argument_list|,
literal|"Loads GIMP brushes (1 or 4 bpp and old .gpb format)"
argument_list|,
literal|"FIXME: write help"
argument_list|,
literal|"Tim Newsome, Jens Lautenbacher, Sven Neumann"
argument_list|,
literal|"Tim Newsome, Jens Lautenbacher, Sven Neumann"
argument_list|,
literal|"1997-2000"
argument_list|,
literal|"<Load>/GBR"
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
literal|"file_gbr_save"
argument_list|,
literal|"saves files in the .gbr file format"
argument_list|,
literal|"Yeah!"
argument_list|,
literal|"Tim Newsome, Jens Lautenbacher, Sven Neumann"
argument_list|,
literal|"Tim Newsome, Jens Lautenbacher, Sven Neumann"
argument_list|,
literal|"1997-2000"
argument_list|,
literal|"<Save>/GBR"
argument_list|,
literal|"RGBA, GRAY"
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
literal|"file_gbr_load"
argument_list|,
literal|"gbr, gpb"
argument_list|,
literal|""
argument_list|,
literal|"20, string, GIMP"
argument_list|)
expr_stmt|;
name|gimp_register_save_handler
argument_list|(
literal|"file_gbr_save"
argument_list|,
literal|"gbr"
argument_list|,
literal|""
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
name|gint32
name|image_ID
decl_stmt|;
name|gint32
name|drawable_ID
decl_stmt|;
name|GimpExportReturn
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
name|INIT_I18N
argument_list|()
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
literal|"file_gbr_load"
argument_list|)
operator|==
literal|0
condition|)
block|{
name|image_ID
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
name|image_ID
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
name|image_ID
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
literal|"file_gbr_save"
argument_list|)
operator|==
literal|0
condition|)
block|{
name|image_ID
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
name|drawable_ID
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
name|gimp_ui_init
argument_list|(
literal|"gbr"
argument_list|,
name|FALSE
argument_list|)
expr_stmt|;
name|export
operator|=
name|gimp_export_image
argument_list|(
operator|&
name|image_ID
argument_list|,
operator|&
name|drawable_ID
argument_list|,
literal|"GBR"
argument_list|,
name|GIMP_EXPORT_CAN_HANDLE_GRAY
operator||
name|GIMP_EXPORT_CAN_HANDLE_RGB
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
switch|switch
condition|(
name|run_mode
condition|)
block|{
case|case
name|GIMP_RUN_INTERACTIVE
case|:
comment|/*  Possibly retrieve data  */
name|strncpy
argument_list|(
name|info
operator|.
name|description
argument_list|,
name|gimp_drawable_name
argument_list|(
name|drawable_ID
argument_list|)
argument_list|,
literal|256
argument_list|)
expr_stmt|;
name|gimp_get_data
argument_list|(
literal|"file_gbr_save"
argument_list|,
operator|&
name|info
argument_list|)
expr_stmt|;
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
comment|/* FIXME - need a real GIMP_RUN_NONINTERACTIVE */
if|if
condition|(
name|nparams
operator|!=
literal|7
condition|)
block|{
name|status
operator|=
name|GIMP_PDB_CALLING_ERROR
expr_stmt|;
block|}
else|else
block|{
name|info
operator|.
name|spacing
operator|=
operator|(
name|param
index|[
literal|5
index|]
operator|.
name|data
operator|.
name|d_int32
operator|)
expr_stmt|;
name|strncpy
argument_list|(
name|info
operator|.
name|description
argument_list|,
name|param
index|[
literal|6
index|]
operator|.
name|data
operator|.
name|d_string
argument_list|,
literal|256
argument_list|)
expr_stmt|;
block|}
break|break;
case|case
name|GIMP_RUN_WITH_LAST_VALS
case|:
name|gimp_get_data
argument_list|(
literal|"file_gbr_save"
argument_list|,
operator|&
name|info
argument_list|)
expr_stmt|;
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
name|image_ID
argument_list|,
name|drawable_ID
argument_list|)
condition|)
block|{
name|gimp_set_data
argument_list|(
literal|"file_gbr_save"
argument_list|,
operator|&
name|info
argument_list|,
sizeof|sizeof
argument_list|(
name|info
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
name|image_ID
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
name|gint32
DECL|function|load_image (const gchar * filename)
name|load_image
parameter_list|(
specifier|const
name|gchar
modifier|*
name|filename
parameter_list|)
block|{
name|gchar
modifier|*
name|temp
decl_stmt|;
name|gchar
modifier|*
name|name
init|=
name|NULL
decl_stmt|;
name|gint
name|fd
decl_stmt|;
name|BrushHeader
name|bh
decl_stmt|;
name|guchar
modifier|*
name|brush_buf
init|=
name|NULL
decl_stmt|;
name|gint32
name|image_ID
decl_stmt|;
name|gint32
name|layer_ID
decl_stmt|;
name|GimpDrawable
modifier|*
name|drawable
decl_stmt|;
name|GimpPixelRgn
name|pixel_rgn
decl_stmt|;
name|gint
name|bn_size
decl_stmt|;
name|GimpImageBaseType
name|base_type
decl_stmt|;
name|GimpImageType
name|image_type
decl_stmt|;
name|gssize
name|size
decl_stmt|;
name|fd
operator|=
name|open
argument_list|(
name|filename
argument_list|,
name|O_RDONLY
operator||
name|_O_BINARY
argument_list|)
expr_stmt|;
if|if
condition|(
name|fd
operator|==
operator|-
literal|1
condition|)
block|{
name|g_message
argument_list|(
name|_
argument_list|(
literal|"Can't open '%s':\n%s"
argument_list|)
argument_list|,
name|filename
argument_list|,
name|g_strerror
argument_list|(
name|errno
argument_list|)
argument_list|)
expr_stmt|;
return|return
operator|-
literal|1
return|;
block|}
name|temp
operator|=
name|g_strdup_printf
argument_list|(
name|_
argument_list|(
literal|"Opening '%s'..."
argument_list|)
argument_list|,
name|filename
argument_list|)
expr_stmt|;
name|gimp_progress_init
argument_list|(
name|temp
argument_list|)
expr_stmt|;
name|g_free
argument_list|(
name|temp
argument_list|)
expr_stmt|;
if|if
condition|(
name|read
argument_list|(
name|fd
argument_list|,
operator|&
name|bh
argument_list|,
sizeof|sizeof
argument_list|(
name|bh
argument_list|)
argument_list|)
operator|!=
sizeof|sizeof
argument_list|(
name|bh
argument_list|)
condition|)
block|{
name|close
argument_list|(
name|fd
argument_list|)
expr_stmt|;
return|return
operator|-
literal|1
return|;
block|}
comment|/*  rearrange the bytes in each unsigned int  */
name|bh
operator|.
name|header_size
operator|=
name|g_ntohl
argument_list|(
name|bh
operator|.
name|header_size
argument_list|)
expr_stmt|;
name|bh
operator|.
name|version
operator|=
name|g_ntohl
argument_list|(
name|bh
operator|.
name|version
argument_list|)
expr_stmt|;
name|bh
operator|.
name|width
operator|=
name|g_ntohl
argument_list|(
name|bh
operator|.
name|width
argument_list|)
expr_stmt|;
name|bh
operator|.
name|height
operator|=
name|g_ntohl
argument_list|(
name|bh
operator|.
name|height
argument_list|)
expr_stmt|;
name|bh
operator|.
name|bytes
operator|=
name|g_ntohl
argument_list|(
name|bh
operator|.
name|bytes
argument_list|)
expr_stmt|;
name|bh
operator|.
name|magic_number
operator|=
name|g_ntohl
argument_list|(
name|bh
operator|.
name|magic_number
argument_list|)
expr_stmt|;
name|bh
operator|.
name|spacing
operator|=
name|g_ntohl
argument_list|(
name|bh
operator|.
name|spacing
argument_list|)
expr_stmt|;
switch|switch
condition|(
name|bh
operator|.
name|version
condition|)
block|{
case|case
literal|1
case|:
comment|/* Version 1 didn't have a magic number and had no spacing  */
name|bh
operator|.
name|spacing
operator|=
literal|25
expr_stmt|;
comment|/* And we need to rewind the handle, 4 due spacing and 4 due magic */
name|lseek
argument_list|(
name|fd
argument_list|,
operator|-
literal|8
argument_list|,
name|SEEK_CUR
argument_list|)
expr_stmt|;
name|bh
operator|.
name|header_size
operator|+=
literal|8
expr_stmt|;
break|break;
case|case
literal|3
case|:
comment|/*  cinepaint brush  */
if|if
condition|(
name|bh
operator|.
name|bytes
operator|==
literal|18
comment|/* FLOAT16_GRAY_GIMAGE */
condition|)
block|{
name|bh
operator|.
name|bytes
operator|=
literal|2
expr_stmt|;
block|}
else|else
block|{
name|g_message
argument_list|(
name|_
argument_list|(
literal|"Unsupported brush format"
argument_list|)
argument_list|)
expr_stmt|;
name|close
argument_list|(
name|fd
argument_list|)
expr_stmt|;
return|return
operator|-
literal|1
return|;
block|}
comment|/*  fallthrough  */
case|case
literal|2
case|:
if|if
condition|(
name|bh
operator|.
name|magic_number
operator|==
name|GBRUSH_MAGIC
operator|&&
name|bh
operator|.
name|header_size
operator|>
sizeof|sizeof
argument_list|(
name|bh
argument_list|)
condition|)
break|break;
default|default:
name|g_message
argument_list|(
name|_
argument_list|(
literal|"Unsupported brush format"
argument_list|)
argument_list|)
expr_stmt|;
name|close
argument_list|(
name|fd
argument_list|)
expr_stmt|;
return|return
operator|-
literal|1
return|;
block|}
if|if
condition|(
operator|(
name|bn_size
operator|=
operator|(
name|bh
operator|.
name|header_size
operator|-
sizeof|sizeof
argument_list|(
name|bh
argument_list|)
operator|)
operator|)
operator|>
literal|0
condition|)
block|{
name|name
operator|=
name|g_new
argument_list|(
name|gchar
argument_list|,
name|bn_size
argument_list|)
expr_stmt|;
if|if
condition|(
operator|(
name|read
argument_list|(
name|fd
argument_list|,
name|name
argument_list|,
name|bn_size
argument_list|)
operator|)
operator|<
name|bn_size
condition|)
block|{
name|g_message
argument_list|(
name|_
argument_list|(
literal|"Error in GIMP brush file\n'%s'"
argument_list|)
argument_list|,
name|filename
argument_list|)
expr_stmt|;
name|close
argument_list|(
name|fd
argument_list|)
expr_stmt|;
name|g_free
argument_list|(
name|name
argument_list|)
expr_stmt|;
return|return
operator|-
literal|1
return|;
block|}
block|}
else|else
block|{
name|name
operator|=
name|g_strdup
argument_list|(
name|_
argument_list|(
literal|"Unnamed"
argument_list|)
argument_list|)
expr_stmt|;
block|}
comment|/* Now there's just raw data left. */
name|size
operator|=
name|bh
operator|.
name|width
operator|*
name|bh
operator|.
name|height
operator|*
name|bh
operator|.
name|bytes
expr_stmt|;
name|brush_buf
operator|=
name|g_malloc
argument_list|(
name|size
argument_list|)
expr_stmt|;
if|if
condition|(
name|read
argument_list|(
name|fd
argument_list|,
name|brush_buf
argument_list|,
name|size
argument_list|)
operator|!=
name|size
condition|)
block|{
name|close
argument_list|(
name|fd
argument_list|)
expr_stmt|;
name|g_free
argument_list|(
name|brush_buf
argument_list|)
expr_stmt|;
name|g_free
argument_list|(
name|name
argument_list|)
expr_stmt|;
return|return
operator|-
literal|1
return|;
block|}
switch|switch
condition|(
name|bh
operator|.
name|bytes
condition|)
block|{
case|case
literal|1
case|:
block|{
name|PatternHeader
name|ph
decl_stmt|;
comment|/*  For backwards-compatibility, check if a pattern follows.             The obsolete .gpb format did it this way.  */
if|if
condition|(
name|read
argument_list|(
name|fd
argument_list|,
operator|&
name|ph
argument_list|,
sizeof|sizeof
argument_list|(
name|ph
argument_list|)
argument_list|)
operator|==
sizeof|sizeof
argument_list|(
name|ph
argument_list|)
condition|)
block|{
comment|/*  rearrange the bytes in each unsigned int  */
name|ph
operator|.
name|header_size
operator|=
name|g_ntohl
argument_list|(
name|ph
operator|.
name|header_size
argument_list|)
expr_stmt|;
name|ph
operator|.
name|version
operator|=
name|g_ntohl
argument_list|(
name|ph
operator|.
name|version
argument_list|)
expr_stmt|;
name|ph
operator|.
name|width
operator|=
name|g_ntohl
argument_list|(
name|ph
operator|.
name|width
argument_list|)
expr_stmt|;
name|ph
operator|.
name|height
operator|=
name|g_ntohl
argument_list|(
name|ph
operator|.
name|height
argument_list|)
expr_stmt|;
name|ph
operator|.
name|bytes
operator|=
name|g_ntohl
argument_list|(
name|ph
operator|.
name|bytes
argument_list|)
expr_stmt|;
name|ph
operator|.
name|magic_number
operator|=
name|g_ntohl
argument_list|(
name|ph
operator|.
name|magic_number
argument_list|)
expr_stmt|;
if|if
condition|(
name|ph
operator|.
name|magic_number
operator|==
name|GPATTERN_MAGIC
operator|&&
name|ph
operator|.
name|version
operator|==
literal|1
operator|&&
name|ph
operator|.
name|header_size
operator|>
sizeof|sizeof
argument_list|(
name|ph
argument_list|)
operator|&&
name|ph
operator|.
name|bytes
operator|==
literal|3
operator|&&
name|ph
operator|.
name|width
operator|==
name|bh
operator|.
name|width
operator|&&
name|ph
operator|.
name|height
operator|==
name|bh
operator|.
name|height
operator|&&
name|lseek
argument_list|(
name|fd
argument_list|,
name|ph
operator|.
name|header_size
operator|-
sizeof|sizeof
argument_list|(
name|ph
argument_list|)
argument_list|,
name|SEEK_CUR
argument_list|)
operator|>
literal|0
condition|)
block|{
name|guchar
modifier|*
name|plain_brush
init|=
name|brush_buf
decl_stmt|;
name|gint
name|i
decl_stmt|;
name|bh
operator|.
name|bytes
operator|=
literal|4
expr_stmt|;
name|brush_buf
operator|=
name|g_malloc
argument_list|(
literal|4
operator|*
name|bh
operator|.
name|width
operator|*
name|bh
operator|.
name|height
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
name|ph
operator|.
name|width
operator|*
name|ph
operator|.
name|height
condition|;
name|i
operator|++
control|)
block|{
if|if
condition|(
name|read
argument_list|(
name|fd
argument_list|,
name|brush_buf
operator|+
name|i
operator|*
literal|4
argument_list|,
literal|3
argument_list|)
operator|!=
literal|3
condition|)
block|{
name|close
argument_list|(
name|fd
argument_list|)
expr_stmt|;
name|g_free
argument_list|(
name|name
argument_list|)
expr_stmt|;
name|g_free
argument_list|(
name|plain_brush
argument_list|)
expr_stmt|;
name|g_free
argument_list|(
name|brush_buf
argument_list|)
expr_stmt|;
return|return
operator|-
literal|1
return|;
block|}
name|brush_buf
index|[
name|i
operator|*
literal|4
operator|+
literal|3
index|]
operator|=
name|plain_brush
index|[
name|i
index|]
expr_stmt|;
block|}
name|g_free
argument_list|(
name|plain_brush
argument_list|)
expr_stmt|;
block|}
block|}
block|}
break|break;
case|case
literal|2
case|:
block|{
name|guint16
modifier|*
name|buf
init|=
operator|(
name|guint16
operator|*
operator|)
name|brush_buf
decl_stmt|;
name|gint
name|i
decl_stmt|;
for|for
control|(
name|i
operator|=
literal|0
init|;
name|i
operator|<
name|bh
operator|.
name|width
operator|*
name|bh
operator|.
name|height
condition|;
name|i
operator|++
operator|,
name|buf
operator|++
control|)
block|{
union|union
DECL|union|__anon2b289fb7020a
block|{
DECL|member|u
name|guint16
name|u
index|[
literal|2
index|]
decl_stmt|;
DECL|member|f
name|gfloat
name|f
decl_stmt|;
block|}
name|short_float
union|;
if|#
directive|if
name|G_BYTE_ORDER
operator|==
name|G_LITTLE_ENDIAN
name|short_float
operator|.
name|u
index|[
literal|0
index|]
operator|=
literal|0
expr_stmt|;
name|short_float
operator|.
name|u
index|[
literal|1
index|]
operator|=
name|GUINT16_FROM_BE
argument_list|(
operator|*
name|buf
argument_list|)
expr_stmt|;
else|#
directive|else
name|short_float
operator|.
name|u
index|[
literal|0
index|]
operator|=
name|GUINT16_FROM_BE
argument_list|(
operator|*
name|buf
argument_list|)
expr_stmt|;
name|short_float
operator|.
name|u
index|[
literal|1
index|]
operator|=
literal|0
expr_stmt|;
endif|#
directive|endif
name|brush_buf
index|[
name|i
index|]
operator|=
call|(
name|guchar
call|)
argument_list|(
name|short_float
operator|.
name|f
operator|*
literal|255.0
operator|+
literal|0.5
argument_list|)
expr_stmt|;
block|}
name|bh
operator|.
name|bytes
operator|=
literal|1
expr_stmt|;
block|}
break|break;
default|default:
break|break;
block|}
comment|/*    * Create a new image of the proper size and    * associate the filename with it.    */
switch|switch
condition|(
name|bh
operator|.
name|bytes
condition|)
block|{
case|case
literal|1
case|:
name|base_type
operator|=
name|GIMP_GRAY
expr_stmt|;
name|image_type
operator|=
name|GIMP_GRAY_IMAGE
expr_stmt|;
break|break;
case|case
literal|4
case|:
name|base_type
operator|=
name|GIMP_RGB
expr_stmt|;
name|image_type
operator|=
name|GIMP_RGBA_IMAGE
expr_stmt|;
break|break;
default|default:
name|g_message
argument_list|(
literal|"Unsupported brush depth: %d\n"
literal|"GIMP Brushes must be GRAY or RGBA\n"
argument_list|,
name|bh
operator|.
name|bytes
argument_list|)
expr_stmt|;
return|return
operator|-
literal|1
return|;
block|}
name|image_ID
operator|=
name|gimp_image_new
argument_list|(
name|bh
operator|.
name|width
argument_list|,
name|bh
operator|.
name|height
argument_list|,
name|base_type
argument_list|)
expr_stmt|;
name|gimp_image_set_filename
argument_list|(
name|image_ID
argument_list|,
name|filename
argument_list|)
expr_stmt|;
name|layer_ID
operator|=
name|gimp_layer_new
argument_list|(
name|image_ID
argument_list|,
name|name
argument_list|,
name|bh
operator|.
name|width
argument_list|,
name|bh
operator|.
name|height
argument_list|,
name|image_type
argument_list|,
literal|100
argument_list|,
name|GIMP_NORMAL_MODE
argument_list|)
expr_stmt|;
name|gimp_image_add_layer
argument_list|(
name|image_ID
argument_list|,
name|layer_ID
argument_list|,
literal|0
argument_list|)
expr_stmt|;
name|g_free
argument_list|(
name|name
argument_list|)
expr_stmt|;
name|drawable
operator|=
name|gimp_drawable_get
argument_list|(
name|layer_ID
argument_list|)
expr_stmt|;
name|gimp_pixel_rgn_init
argument_list|(
operator|&
name|pixel_rgn
argument_list|,
name|drawable
argument_list|,
literal|0
argument_list|,
literal|0
argument_list|,
name|drawable
operator|->
name|width
argument_list|,
name|drawable
operator|->
name|height
argument_list|,
name|TRUE
argument_list|,
name|FALSE
argument_list|)
expr_stmt|;
name|gimp_pixel_rgn_set_rect
argument_list|(
operator|&
name|pixel_rgn
argument_list|,
name|brush_buf
argument_list|,
literal|0
argument_list|,
literal|0
argument_list|,
name|bh
operator|.
name|width
argument_list|,
name|bh
operator|.
name|height
argument_list|)
expr_stmt|;
name|g_free
argument_list|(
name|brush_buf
argument_list|)
expr_stmt|;
if|if
condition|(
name|image_type
operator|==
name|GIMP_GRAY_IMAGE
condition|)
name|gimp_invert
argument_list|(
name|layer_ID
argument_list|)
expr_stmt|;
name|close
argument_list|(
name|fd
argument_list|)
expr_stmt|;
name|gimp_drawable_flush
argument_list|(
name|drawable
argument_list|)
expr_stmt|;
name|gimp_progress_update
argument_list|(
literal|1.0
argument_list|)
expr_stmt|;
return|return
name|image_ID
return|;
block|}
end_function

begin_function
specifier|static
name|gint
DECL|function|save_image (const gchar * filename,gint32 image_ID,gint32 drawable_ID)
name|save_image
parameter_list|(
specifier|const
name|gchar
modifier|*
name|filename
parameter_list|,
name|gint32
name|image_ID
parameter_list|,
name|gint32
name|drawable_ID
parameter_list|)
block|{
name|gint
name|fd
decl_stmt|;
name|BrushHeader
name|bh
decl_stmt|;
name|guchar
modifier|*
name|buffer
decl_stmt|;
name|GimpDrawable
modifier|*
name|drawable
decl_stmt|;
name|gint
name|line
decl_stmt|;
name|gint
name|x
decl_stmt|;
name|GimpPixelRgn
name|pixel_rgn
decl_stmt|;
name|gchar
modifier|*
name|temp
decl_stmt|;
if|if
condition|(
name|gimp_drawable_type
argument_list|(
name|drawable_ID
argument_list|)
operator|!=
name|GIMP_GRAY_IMAGE
operator|&&
name|gimp_drawable_type
argument_list|(
name|drawable_ID
argument_list|)
operator|!=
name|GIMP_RGBA_IMAGE
condition|)
block|{
name|g_message
argument_list|(
name|_
argument_list|(
literal|"GIMP brushes are either GRAYSCALE or RGBA\n"
argument_list|)
argument_list|)
expr_stmt|;
return|return
name|FALSE
return|;
block|}
name|fd
operator|=
name|open
argument_list|(
name|filename
argument_list|,
name|O_CREAT
operator||
name|O_TRUNC
operator||
name|O_WRONLY
operator||
name|_O_BINARY
argument_list|,
literal|0644
argument_list|)
expr_stmt|;
if|if
condition|(
name|fd
operator|==
operator|-
literal|1
condition|)
block|{
name|g_message
argument_list|(
name|_
argument_list|(
literal|"Can't open '%s' for writing:\n%s"
argument_list|)
argument_list|,
name|filename
argument_list|,
name|g_strerror
argument_list|(
name|errno
argument_list|)
argument_list|)
expr_stmt|;
return|return
name|FALSE
return|;
block|}
name|temp
operator|=
name|g_strdup_printf
argument_list|(
name|_
argument_list|(
literal|"Saving %s:"
argument_list|)
argument_list|,
name|filename
argument_list|)
expr_stmt|;
name|gimp_progress_init
argument_list|(
name|temp
argument_list|)
expr_stmt|;
name|g_free
argument_list|(
name|temp
argument_list|)
expr_stmt|;
name|drawable
operator|=
name|gimp_drawable_get
argument_list|(
name|drawable_ID
argument_list|)
expr_stmt|;
name|gimp_pixel_rgn_init
argument_list|(
operator|&
name|pixel_rgn
argument_list|,
name|drawable
argument_list|,
literal|0
argument_list|,
literal|0
argument_list|,
name|drawable
operator|->
name|width
argument_list|,
name|drawable
operator|->
name|height
argument_list|,
name|FALSE
argument_list|,
name|FALSE
argument_list|)
expr_stmt|;
name|bh
operator|.
name|header_size
operator|=
name|g_htonl
argument_list|(
sizeof|sizeof
argument_list|(
name|bh
argument_list|)
operator|+
name|strlen
argument_list|(
name|info
operator|.
name|description
argument_list|)
operator|+
literal|1
argument_list|)
expr_stmt|;
name|bh
operator|.
name|version
operator|=
name|g_htonl
argument_list|(
literal|2
argument_list|)
expr_stmt|;
name|bh
operator|.
name|width
operator|=
name|g_htonl
argument_list|(
name|drawable
operator|->
name|width
argument_list|)
expr_stmt|;
name|bh
operator|.
name|height
operator|=
name|g_htonl
argument_list|(
name|drawable
operator|->
name|height
argument_list|)
expr_stmt|;
name|bh
operator|.
name|bytes
operator|=
name|g_htonl
argument_list|(
name|drawable
operator|->
name|bpp
argument_list|)
expr_stmt|;
name|bh
operator|.
name|magic_number
operator|=
name|g_htonl
argument_list|(
name|GBRUSH_MAGIC
argument_list|)
expr_stmt|;
name|bh
operator|.
name|spacing
operator|=
name|g_htonl
argument_list|(
name|info
operator|.
name|spacing
argument_list|)
expr_stmt|;
if|if
condition|(
name|write
argument_list|(
name|fd
argument_list|,
operator|&
name|bh
argument_list|,
sizeof|sizeof
argument_list|(
name|bh
argument_list|)
argument_list|)
operator|!=
sizeof|sizeof
argument_list|(
name|bh
argument_list|)
condition|)
block|{
name|close
argument_list|(
name|fd
argument_list|)
expr_stmt|;
return|return
name|FALSE
return|;
block|}
if|if
condition|(
name|write
argument_list|(
name|fd
argument_list|,
name|info
operator|.
name|description
argument_list|,
name|strlen
argument_list|(
name|info
operator|.
name|description
argument_list|)
operator|+
literal|1
argument_list|)
operator|!=
name|strlen
argument_list|(
name|info
operator|.
name|description
argument_list|)
operator|+
literal|1
condition|)
block|{
name|close
argument_list|(
name|fd
argument_list|)
expr_stmt|;
return|return
name|FALSE
return|;
block|}
name|buffer
operator|=
name|g_malloc
argument_list|(
name|drawable
operator|->
name|width
operator|*
name|drawable
operator|->
name|bpp
argument_list|)
expr_stmt|;
for|for
control|(
name|line
operator|=
literal|0
init|;
name|line
operator|<
name|drawable
operator|->
name|height
condition|;
name|line
operator|++
control|)
block|{
name|gimp_pixel_rgn_get_row
argument_list|(
operator|&
name|pixel_rgn
argument_list|,
name|buffer
argument_list|,
literal|0
argument_list|,
name|line
argument_list|,
name|drawable
operator|->
name|width
argument_list|)
expr_stmt|;
if|if
condition|(
name|drawable
operator|->
name|bpp
operator|==
literal|1
condition|)
block|{
for|for
control|(
name|x
operator|=
literal|0
init|;
name|x
operator|<
name|drawable
operator|->
name|width
condition|;
name|x
operator|++
control|)
name|buffer
index|[
name|x
index|]
operator|=
literal|255
operator|-
name|buffer
index|[
name|x
index|]
expr_stmt|;
block|}
if|if
condition|(
name|write
argument_list|(
name|fd
argument_list|,
name|buffer
argument_list|,
name|drawable
operator|->
name|width
operator|*
name|drawable
operator|->
name|bpp
argument_list|)
operator|!=
name|drawable
operator|->
name|width
operator|*
name|drawable
operator|->
name|bpp
condition|)
block|{
name|g_free
argument_list|(
name|buffer
argument_list|)
expr_stmt|;
name|close
argument_list|(
name|fd
argument_list|)
expr_stmt|;
return|return
name|FALSE
return|;
block|}
name|gimp_progress_update
argument_list|(
operator|(
name|gdouble
operator|)
name|line
operator|/
operator|(
name|gdouble
operator|)
name|drawable
operator|->
name|height
argument_list|)
expr_stmt|;
block|}
name|g_free
argument_list|(
name|buffer
argument_list|)
expr_stmt|;
name|close
argument_list|(
name|fd
argument_list|)
expr_stmt|;
return|return
name|TRUE
return|;
block|}
end_function

begin_function
specifier|static
name|gint
DECL|function|save_dialog (void)
name|save_dialog
parameter_list|(
name|void
parameter_list|)
block|{
name|GtkWidget
modifier|*
name|dlg
decl_stmt|;
name|GtkWidget
modifier|*
name|table
decl_stmt|;
name|GtkWidget
modifier|*
name|entry
decl_stmt|;
name|GtkWidget
modifier|*
name|spinbutton
decl_stmt|;
name|GtkObject
modifier|*
name|adj
decl_stmt|;
name|gboolean
name|run
decl_stmt|;
name|dlg
operator|=
name|gimp_dialog_new
argument_list|(
name|_
argument_list|(
literal|"Save as Brush"
argument_list|)
argument_list|,
literal|"gbr"
argument_list|,
name|NULL
argument_list|,
literal|0
argument_list|,
name|gimp_standard_help_func
argument_list|,
literal|"filters/gbr.html"
argument_list|,
name|GTK_STOCK_CANCEL
argument_list|,
name|GTK_RESPONSE_CANCEL
argument_list|,
name|GTK_STOCK_OK
argument_list|,
name|GTK_RESPONSE_OK
argument_list|,
name|NULL
argument_list|)
expr_stmt|;
comment|/* The main table */
name|table
operator|=
name|gtk_table_new
argument_list|(
literal|2
argument_list|,
literal|2
argument_list|,
name|FALSE
argument_list|)
expr_stmt|;
name|gtk_container_set_border_width
argument_list|(
name|GTK_CONTAINER
argument_list|(
name|table
argument_list|)
argument_list|,
literal|6
argument_list|)
expr_stmt|;
name|gtk_table_set_row_spacings
argument_list|(
name|GTK_TABLE
argument_list|(
name|table
argument_list|)
argument_list|,
literal|2
argument_list|)
expr_stmt|;
name|gtk_table_set_col_spacings
argument_list|(
name|GTK_TABLE
argument_list|(
name|table
argument_list|)
argument_list|,
literal|4
argument_list|)
expr_stmt|;
name|gtk_box_pack_start
argument_list|(
name|GTK_BOX
argument_list|(
name|GTK_DIALOG
argument_list|(
name|dlg
argument_list|)
operator|->
name|vbox
argument_list|)
argument_list|,
name|table
argument_list|,
name|TRUE
argument_list|,
name|TRUE
argument_list|,
literal|0
argument_list|)
expr_stmt|;
name|gtk_widget_show
argument_list|(
name|table
argument_list|)
expr_stmt|;
name|spinbutton
operator|=
name|gimp_spin_button_new
argument_list|(
operator|&
name|adj
argument_list|,
name|info
operator|.
name|spacing
argument_list|,
literal|1
argument_list|,
literal|1000
argument_list|,
literal|1
argument_list|,
literal|10
argument_list|,
literal|0
argument_list|,
literal|1
argument_list|,
literal|0
argument_list|)
expr_stmt|;
name|gimp_table_attach_aligned
argument_list|(
name|GTK_TABLE
argument_list|(
name|table
argument_list|)
argument_list|,
literal|0
argument_list|,
literal|0
argument_list|,
name|_
argument_list|(
literal|"Spacing:"
argument_list|)
argument_list|,
literal|1.0
argument_list|,
literal|0.5
argument_list|,
name|spinbutton
argument_list|,
literal|1
argument_list|,
name|TRUE
argument_list|)
expr_stmt|;
name|g_signal_connect
argument_list|(
name|adj
argument_list|,
literal|"value_changed"
argument_list|,
name|G_CALLBACK
argument_list|(
name|gimp_int_adjustment_update
argument_list|)
argument_list|,
operator|&
name|info
operator|.
name|spacing
argument_list|)
expr_stmt|;
name|entry
operator|=
name|gtk_entry_new
argument_list|()
expr_stmt|;
name|gtk_widget_set_size_request
argument_list|(
name|entry
argument_list|,
literal|200
argument_list|,
operator|-
literal|1
argument_list|)
expr_stmt|;
name|gtk_entry_set_text
argument_list|(
name|GTK_ENTRY
argument_list|(
name|entry
argument_list|)
argument_list|,
name|info
operator|.
name|description
argument_list|)
expr_stmt|;
name|gimp_table_attach_aligned
argument_list|(
name|GTK_TABLE
argument_list|(
name|table
argument_list|)
argument_list|,
literal|0
argument_list|,
literal|1
argument_list|,
name|_
argument_list|(
literal|"Description:"
argument_list|)
argument_list|,
literal|1.0
argument_list|,
literal|0.5
argument_list|,
name|entry
argument_list|,
literal|1
argument_list|,
name|FALSE
argument_list|)
expr_stmt|;
name|g_signal_connect
argument_list|(
name|entry
argument_list|,
literal|"changed"
argument_list|,
name|G_CALLBACK
argument_list|(
name|entry_callback
argument_list|)
argument_list|,
name|info
operator|.
name|description
argument_list|)
expr_stmt|;
name|gtk_widget_show
argument_list|(
name|dlg
argument_list|)
expr_stmt|;
name|run
operator|=
operator|(
name|gimp_dialog_run
argument_list|(
name|GIMP_DIALOG
argument_list|(
name|dlg
argument_list|)
argument_list|)
operator|==
name|GTK_RESPONSE_OK
operator|)
expr_stmt|;
name|gtk_widget_destroy
argument_list|(
name|dlg
argument_list|)
expr_stmt|;
return|return
name|run
return|;
block|}
end_function

begin_function
specifier|static
name|void
DECL|function|entry_callback (GtkWidget * widget,gpointer data)
name|entry_callback
parameter_list|(
name|GtkWidget
modifier|*
name|widget
parameter_list|,
name|gpointer
name|data
parameter_list|)
block|{
name|strncpy
argument_list|(
name|info
operator|.
name|description
argument_list|,
name|gtk_entry_get_text
argument_list|(
name|GTK_ENTRY
argument_list|(
name|widget
argument_list|)
argument_list|)
argument_list|,
literal|256
argument_list|)
expr_stmt|;
block|}
end_function

end_unit

