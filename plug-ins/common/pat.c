begin_unit|revision:0.9.5;language:C;cregit-version:0.0.1
begin_comment
comment|/*  * pat plug-in version 1.01  * Loads/saves version 1 GIMP .pat files, by Tim Newsome<drz@frody.bloke.com>  * Some bits stolen from the .99.7 source tree.  * Updated to fix various outstanding problems, brief help -- Nick Lamb  * njl195@zepler.org.uk, April 2000  */
end_comment

begin_include
include|#
directive|include
file|"config.h"
end_include

begin_include
include|#
directive|include
file|<setjmp.h>
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
file|"libgimp/stdplugins-intl.h"
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
file|"app/pattern_header.h"
end_include

begin_comment
comment|/* Declare local data types  */
end_comment

begin_decl_stmt
DECL|variable|description
name|gchar
name|description
index|[
literal|256
index|]
init|=
literal|"GIMP Pattern"
decl_stmt|;
end_decl_stmt

begin_decl_stmt
DECL|variable|run_flag
name|gboolean
name|run_flag
init|=
name|FALSE
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
name|gint
name|save_image
parameter_list|(
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
name|ok_callback
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
name|gint
name|nload_args
init|=
sizeof|sizeof
argument_list|(
name|load_args
argument_list|)
operator|/
sizeof|sizeof
argument_list|(
name|load_args
index|[
literal|0
index|]
argument_list|)
decl_stmt|;
specifier|static
name|gint
name|nload_return_vals
init|=
operator|(
sizeof|sizeof
argument_list|(
name|load_return_vals
argument_list|)
operator|/
sizeof|sizeof
argument_list|(
name|load_return_vals
index|[
literal|0
index|]
argument_list|)
operator|)
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
name|GIMP_PDB_STRING
block|,
literal|"description"
block|,
literal|"Short description of the pattern"
block|}
block|,   }
decl_stmt|;
specifier|static
name|gint
name|nsave_args
init|=
sizeof|sizeof
argument_list|(
name|save_args
argument_list|)
operator|/
sizeof|sizeof
argument_list|(
name|save_args
index|[
literal|0
index|]
argument_list|)
decl_stmt|;
name|gimp_install_procedure
argument_list|(
literal|"file_pat_load"
argument_list|,
literal|"Loads Gimp's .PAT pattern files"
argument_list|,
literal|"The images in the pattern dialog can be loaded directly with this plug-in"
argument_list|,
literal|"Tim Newsome"
argument_list|,
literal|"Tim Newsome"
argument_list|,
literal|"1997"
argument_list|,
literal|"<Load>/PAT"
argument_list|,
name|NULL
argument_list|,
name|GIMP_PLUGIN
argument_list|,
name|nload_args
argument_list|,
name|nload_return_vals
argument_list|,
name|load_args
argument_list|,
name|load_return_vals
argument_list|)
expr_stmt|;
name|gimp_install_procedure
argument_list|(
literal|"file_pat_save"
argument_list|,
literal|"Saves Gimp pattern file (.PAT)"
argument_list|,
literal|"New Gimp patterns can be created by saving them in the appropriate place with this plug-in."
argument_list|,
literal|"Tim Newsome"
argument_list|,
literal|"Tim Newsome"
argument_list|,
literal|"1997"
argument_list|,
literal|"<Save>/PAT"
argument_list|,
literal|"RGB, GRAY"
argument_list|,
name|GIMP_PLUGIN
argument_list|,
name|nsave_args
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
literal|"file_pat_load"
argument_list|,
literal|"pat"
argument_list|,
literal|""
argument_list|,
literal|"20,string,GPAT"
argument_list|)
expr_stmt|;
name|gimp_register_save_handler
argument_list|(
literal|"file_pat_save"
argument_list|,
literal|"pat"
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
name|GimpRunModeType
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
literal|"file_pat_load"
argument_list|)
operator|==
literal|0
condition|)
block|{
name|INIT_I18N
argument_list|()
expr_stmt|;
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
literal|"file_pat_save"
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
name|INIT_I18N_UI
argument_list|()
expr_stmt|;
name|gimp_ui_init
argument_list|(
literal|"pat"
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
literal|"PAT"
argument_list|,
operator|(
name|GIMP_EXPORT_CAN_HANDLE_RGB
operator||
name|GIMP_EXPORT_CAN_HANDLE_GRAY
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
name|INIT_I18N
argument_list|()
expr_stmt|;
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
name|gimp_get_data
argument_list|(
literal|"file_pat_save"
argument_list|,
name|description
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
name|strcpy
argument_list|(
name|description
argument_list|,
name|param
index|[
literal|5
index|]
operator|.
name|data
operator|.
name|d_string
argument_list|)
expr_stmt|;
block|}
break|break;
case|case
name|GIMP_RUN_WITH_LAST_VALS
case|:
name|gimp_get_data
argument_list|(
literal|"file_pat_save"
argument_list|,
name|description
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
literal|"file_pat_save"
argument_list|,
name|description
argument_list|,
literal|256
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
DECL|function|load_image (gchar * filename)
name|load_image
parameter_list|(
name|gchar
modifier|*
name|filename
parameter_list|)
block|{
name|char
modifier|*
name|temp
decl_stmt|;
name|int
name|fd
decl_stmt|;
name|PatternHeader
name|ph
decl_stmt|;
name|guchar
modifier|*
name|buffer
decl_stmt|;
name|gint32
name|image_ID
decl_stmt|,
name|layer_ID
decl_stmt|;
name|GimpDrawable
modifier|*
name|drawable
decl_stmt|;
name|gint
name|line
decl_stmt|;
name|GimpPixelRgn
name|pixel_rgn
decl_stmt|;
name|temp
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
name|temp
argument_list|)
expr_stmt|;
name|g_free
argument_list|(
name|temp
argument_list|)
expr_stmt|;
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
return|return
operator|-
literal|1
return|;
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
operator|!=
sizeof|sizeof
argument_list|(
name|ph
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
operator|!=
name|GPATTERN_MAGIC
operator|||
name|ph
operator|.
name|version
operator|!=
literal|1
operator|||
name|ph
operator|.
name|header_size
operator|<=
sizeof|sizeof
argument_list|(
name|ph
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
if|if
condition|(
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
operator|!=
name|ph
operator|.
name|header_size
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
comment|/* Now there's just raw data left. */
comment|/*    * Create a new image of the proper size and associate the filename with it.    */
name|image_ID
operator|=
name|gimp_image_new
argument_list|(
name|ph
operator|.
name|width
argument_list|,
name|ph
operator|.
name|height
argument_list|,
operator|(
name|ph
operator|.
name|bytes
operator|>=
literal|3
operator|)
condition|?
name|GIMP_RGB
else|:
name|GIMP_GRAY
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
name|_
argument_list|(
literal|"Background"
argument_list|)
argument_list|,
name|ph
operator|.
name|width
argument_list|,
name|ph
operator|.
name|height
argument_list|,
operator|(
name|ph
operator|.
name|bytes
operator|>=
literal|3
operator|)
condition|?
name|GIMP_RGB_IMAGE
else|:
name|GIMP_GRAY_IMAGE
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
name|buffer
operator|=
name|g_malloc
argument_list|(
name|ph
operator|.
name|width
operator|*
name|ph
operator|.
name|bytes
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
name|ph
operator|.
name|height
condition|;
name|line
operator|++
control|)
block|{
if|if
condition|(
name|read
argument_list|(
name|fd
argument_list|,
name|buffer
argument_list|,
name|ph
operator|.
name|width
operator|*
name|ph
operator|.
name|bytes
argument_list|)
operator|!=
name|ph
operator|.
name|width
operator|*
name|ph
operator|.
name|bytes
condition|)
block|{
name|close
argument_list|(
name|fd
argument_list|)
expr_stmt|;
name|g_free
argument_list|(
name|buffer
argument_list|)
expr_stmt|;
return|return
operator|-
literal|1
return|;
block|}
name|gimp_pixel_rgn_set_row
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
name|ph
operator|.
name|width
argument_list|)
expr_stmt|;
name|gimp_progress_update
argument_list|(
operator|(
name|double
operator|)
name|line
operator|/
operator|(
name|double
operator|)
name|ph
operator|.
name|height
argument_list|)
expr_stmt|;
block|}
name|gimp_drawable_flush
argument_list|(
name|drawable
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
DECL|function|save_image (gchar * filename,gint32 image_ID,gint32 drawable_ID)
name|save_image
parameter_list|(
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
name|int
name|fd
decl_stmt|;
name|PatternHeader
name|ph
decl_stmt|;
name|unsigned
name|char
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
name|GimpPixelRgn
name|pixel_rgn
decl_stmt|;
name|char
modifier|*
name|temp
decl_stmt|;
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
return|return
literal|0
return|;
name|ph
operator|.
name|header_size
operator|=
name|g_htonl
argument_list|(
sizeof|sizeof
argument_list|(
name|ph
argument_list|)
operator|+
name|strlen
argument_list|(
name|description
argument_list|)
operator|+
literal|1
argument_list|)
expr_stmt|;
name|ph
operator|.
name|version
operator|=
name|g_htonl
argument_list|(
literal|1
argument_list|)
expr_stmt|;
name|ph
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
name|ph
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
name|ph
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
name|ph
operator|.
name|magic_number
operator|=
name|g_htonl
argument_list|(
name|GPATTERN_MAGIC
argument_list|)
expr_stmt|;
if|if
condition|(
name|write
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
operator|!=
sizeof|sizeof
argument_list|(
name|ph
argument_list|)
condition|)
block|{
name|close
argument_list|(
name|fd
argument_list|)
expr_stmt|;
return|return
literal|0
return|;
block|}
if|if
condition|(
name|write
argument_list|(
name|fd
argument_list|,
name|description
argument_list|,
name|strlen
argument_list|(
name|description
argument_list|)
operator|+
literal|1
argument_list|)
operator|!=
name|strlen
argument_list|(
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
literal|0
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
if|if
condition|(
name|buffer
operator|==
name|NULL
condition|)
block|{
name|close
argument_list|(
name|fd
argument_list|)
expr_stmt|;
return|return
literal|0
return|;
block|}
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
name|close
argument_list|(
name|fd
argument_list|)
expr_stmt|;
return|return
literal|0
return|;
block|}
name|gimp_progress_update
argument_list|(
operator|(
name|double
operator|)
name|line
operator|/
operator|(
name|double
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
literal|1
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
name|dlg
operator|=
name|gimp_dialog_new
argument_list|(
name|_
argument_list|(
literal|"Save as Pattern"
argument_list|)
argument_list|,
literal|"pat"
argument_list|,
name|gimp_standard_help_func
argument_list|,
literal|"filters/pat.html"
argument_list|,
name|GTK_WIN_POS_MOUSE
argument_list|,
name|FALSE
argument_list|,
name|TRUE
argument_list|,
name|FALSE
argument_list|,
name|_
argument_list|(
literal|"OK"
argument_list|)
argument_list|,
name|ok_callback
argument_list|,
name|NULL
argument_list|,
name|NULL
argument_list|,
name|NULL
argument_list|,
name|TRUE
argument_list|,
name|FALSE
argument_list|,
name|_
argument_list|(
literal|"Cancel"
argument_list|)
argument_list|,
name|gtk_widget_destroy
argument_list|,
name|NULL
argument_list|,
literal|1
argument_list|,
name|NULL
argument_list|,
name|FALSE
argument_list|,
name|TRUE
argument_list|,
name|NULL
argument_list|)
expr_stmt|;
name|gtk_signal_connect
argument_list|(
name|GTK_OBJECT
argument_list|(
name|dlg
argument_list|)
argument_list|,
literal|"destroy"
argument_list|,
name|GTK_SIGNAL_FUNC
argument_list|(
name|gtk_main_quit
argument_list|)
argument_list|,
name|NULL
argument_list|)
expr_stmt|;
comment|/* The main table */
name|table
operator|=
name|gtk_table_new
argument_list|(
literal|1
argument_list|,
literal|2
argument_list|,
name|FALSE
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
name|gtk_container_border_width
argument_list|(
name|GTK_CONTAINER
argument_list|(
name|table
argument_list|)
argument_list|,
literal|6
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
name|entry
operator|=
name|gtk_entry_new
argument_list|()
expr_stmt|;
name|gtk_widget_set_usize
argument_list|(
name|entry
argument_list|,
literal|200
argument_list|,
literal|0
argument_list|)
expr_stmt|;
name|gtk_entry_set_text
argument_list|(
name|GTK_ENTRY
argument_list|(
name|entry
argument_list|)
argument_list|,
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
literal|0
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
name|gtk_signal_connect
argument_list|(
name|GTK_OBJECT
argument_list|(
name|entry
argument_list|)
argument_list|,
literal|"changed"
argument_list|,
name|GTK_SIGNAL_FUNC
argument_list|(
name|entry_callback
argument_list|)
argument_list|,
name|description
argument_list|)
expr_stmt|;
name|gtk_widget_show
argument_list|(
name|entry
argument_list|)
expr_stmt|;
name|gtk_widget_show
argument_list|(
name|dlg
argument_list|)
expr_stmt|;
name|gtk_main
argument_list|()
expr_stmt|;
name|gdk_flush
argument_list|()
expr_stmt|;
return|return
name|run_flag
return|;
block|}
end_function

begin_function
specifier|static
name|void
DECL|function|ok_callback (GtkWidget * widget,gpointer data)
name|ok_callback
parameter_list|(
name|GtkWidget
modifier|*
name|widget
parameter_list|,
name|gpointer
name|data
parameter_list|)
block|{
name|run_flag
operator|=
name|TRUE
expr_stmt|;
name|gtk_widget_destroy
argument_list|(
name|GTK_WIDGET
argument_list|(
name|data
argument_list|)
argument_list|)
expr_stmt|;
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
if|if
condition|(
name|data
operator|==
name|description
condition|)
name|strncpy
argument_list|(
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

