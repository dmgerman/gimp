begin_unit|revision:0.9.5;language:C;cregit-version:0.0.1
begin_comment
comment|/*  * gbr plug-in version 1.00  * Loads/saves version 2 GIMP .gbr files, by Tim Newsome<drz@frody.bloke.com>  * Some bits stolen from the .99.7 source tree.  */
end_comment

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

begin_include
include|#
directive|include
file|<unistd.h>
end_include

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
file|"gtk/gtk.h"
end_include

begin_include
include|#
directive|include
file|"libgimp/gimp.h"
end_include

begin_include
include|#
directive|include
file|"app/brush_header.h"
end_include

begin_include
include|#
directive|include
file|<netinet/in.h>
end_include

begin_comment
comment|/* Declare local data types  */
end_comment

begin_typedef
DECL|struct|__anon27c2d9a60108
typedef|typedef
struct|struct
block|{
DECL|member|description
name|char
name|description
index|[
literal|256
index|]
decl_stmt|;
DECL|member|spacing
name|unsigned
name|int
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

begin_decl_stmt
DECL|variable|run_flag
name|int
name|run_flag
init|=
literal|0
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
name|char
modifier|*
name|name
parameter_list|,
name|int
name|nparams
parameter_list|,
name|GParam
modifier|*
name|param
parameter_list|,
name|int
modifier|*
name|nreturn_vals
parameter_list|,
name|GParam
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
name|char
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
name|char
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
parameter_list|()
function_decl|;
end_function_decl

begin_function_decl
specifier|static
name|void
name|close_callback
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
name|GPlugInInfo
name|PLUG_IN_INFO
init|=
block|{
name|NULL
block|,
comment|/* init_proc */
name|NULL
block|,
comment|/* quit_proc */
name|query
block|,
comment|/* query_proc */
name|run
block|,
comment|/* run_proc */
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
parameter_list|()
block|{
specifier|static
name|GParamDef
name|load_args
index|[]
init|=
block|{
block|{
name|PARAM_INT32
block|,
literal|"run_mode"
block|,
literal|"Interactive, non-interactive"
block|}
block|,
block|{
name|PARAM_STRING
block|,
literal|"filename"
block|,
literal|"The name of the file to load"
block|}
block|,
block|{
name|PARAM_STRING
block|,
literal|"raw_filename"
block|,
literal|"The name of the file to load"
block|}
block|,   }
decl_stmt|;
specifier|static
name|GParamDef
name|load_return_vals
index|[]
init|=
block|{
block|{
name|PARAM_IMAGE
block|,
literal|"image"
block|,
literal|"Output image"
block|}
block|,   }
decl_stmt|;
specifier|static
name|int
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
name|int
name|nload_return_vals
init|=
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
decl_stmt|;
specifier|static
name|GParamDef
name|save_args
index|[]
init|=
block|{
block|{
name|PARAM_INT32
block|,
literal|"run_mode"
block|,
literal|"Interactive, non-interactive"
block|}
block|,
block|{
name|PARAM_IMAGE
block|,
literal|"image"
block|,
literal|"Input image"
block|}
block|,
block|{
name|PARAM_DRAWABLE
block|,
literal|"drawable"
block|,
literal|"Drawable to save"
block|}
block|,
block|{
name|PARAM_STRING
block|,
literal|"filename"
block|,
literal|"The name of the file to save the image in"
block|}
block|,
block|{
name|PARAM_STRING
block|,
literal|"raw_filename"
block|,
literal|"The name of the file to save the image in"
block|}
block|,
block|{
name|PARAM_INT32
block|,
literal|"spacing"
block|,
literal|"Spacing of the brush"
block|}
block|,
block|{
name|PARAM_STRING
block|,
literal|"description"
block|,
literal|"Short description of the brush"
block|}
block|,   }
decl_stmt|;
specifier|static
name|int
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
literal|"file_gbr_load"
argument_list|,
literal|"loads files of the .gbr file format"
argument_list|,
literal|"FIXME: write help"
argument_list|,
literal|"Tim Newsome"
argument_list|,
literal|"Tim Newsome"
argument_list|,
literal|"1997"
argument_list|,
literal|"<Load>/GBR"
argument_list|,
name|NULL
argument_list|,
name|PROC_PLUG_IN
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
literal|"file_gbr_save"
argument_list|,
literal|"saves files in the .gbr file format"
argument_list|,
literal|"Yeah!"
argument_list|,
literal|"Tim Newsome"
argument_list|,
literal|"Tim Newsome"
argument_list|,
literal|"1997"
argument_list|,
literal|"<Save>/GBR"
argument_list|,
literal|"RGB*, GRAY*"
argument_list|,
name|PROC_PLUG_IN
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
literal|"file_gbr_load"
argument_list|,
literal|"gbr"
argument_list|,
literal|""
argument_list|,
literal|"20,string,GIMP"
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
DECL|function|run (char * name,int nparams,GParam * param,int * nreturn_vals,GParam ** return_vals)
name|run
parameter_list|(
name|char
modifier|*
name|name
parameter_list|,
name|int
name|nparams
parameter_list|,
name|GParam
modifier|*
name|param
parameter_list|,
name|int
modifier|*
name|nreturn_vals
parameter_list|,
name|GParam
modifier|*
modifier|*
name|return_vals
parameter_list|)
block|{
specifier|static
name|GParam
name|values
index|[
literal|2
index|]
decl_stmt|;
name|GRunModeType
name|run_mode
decl_stmt|;
name|gint32
name|image_ID
decl_stmt|;
name|GStatusType
name|status
init|=
name|STATUS_SUCCESS
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
name|PARAM_STATUS
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
name|STATUS_CALLING_ERROR
expr_stmt|;
name|values
index|[
literal|1
index|]
operator|.
name|type
operator|=
name|PARAM_IMAGE
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
operator|-
literal|1
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
name|values
index|[
literal|0
index|]
operator|.
name|data
operator|.
name|d_status
operator|=
name|STATUS_SUCCESS
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
name|values
index|[
literal|0
index|]
operator|.
name|data
operator|.
name|d_status
operator|=
name|STATUS_EXECUTION_ERROR
expr_stmt|;
block|}
operator|*
name|nreturn_vals
operator|=
literal|2
expr_stmt|;
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
switch|switch
condition|(
name|run_mode
condition|)
block|{
case|case
name|RUN_INTERACTIVE
case|:
comment|/*  Possibly retrieve data  */
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
return|return;
break|break;
case|case
name|RUN_NONINTERACTIVE
case|:
comment|/* FIXME - need a real RUN_NONINTERACTIVE */
if|if
condition|(
name|nparams
operator|!=
literal|7
condition|)
name|status
operator|=
name|STATUS_CALLING_ERROR
expr_stmt|;
if|if
condition|(
name|status
operator|==
name|STATUS_SUCCESS
condition|)
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
name|RUN_WITH_LAST_VALS
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
name|param
index|[
literal|1
index|]
operator|.
name|data
operator|.
name|d_int32
argument_list|,
name|param
index|[
literal|2
index|]
operator|.
name|data
operator|.
name|d_int32
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
name|values
index|[
literal|0
index|]
operator|.
name|data
operator|.
name|d_status
operator|=
name|STATUS_SUCCESS
expr_stmt|;
block|}
else|else
name|values
index|[
literal|0
index|]
operator|.
name|data
operator|.
name|d_status
operator|=
name|STATUS_EXECUTION_ERROR
expr_stmt|;
operator|*
name|nreturn_vals
operator|=
literal|1
expr_stmt|;
block|}
block|}
end_function

begin_function
DECL|function|load_image (char * filename)
specifier|static
name|gint32
name|load_image
parameter_list|(
name|char
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
name|BrushHeader
name|ph
decl_stmt|;
name|gchar
modifier|*
name|buffer
decl_stmt|;
name|gint32
name|image_ID
decl_stmt|,
name|layer_ID
decl_stmt|;
name|GDrawable
modifier|*
name|drawable
decl_stmt|;
name|gint
name|line
decl_stmt|;
name|GPixelRgn
name|pixel_rgn
decl_stmt|;
name|temp
operator|=
name|g_malloc
argument_list|(
name|strlen
argument_list|(
name|filename
argument_list|)
operator|+
literal|11
argument_list|)
expr_stmt|;
name|sprintf
argument_list|(
name|temp
argument_list|,
literal|"Loading %s:"
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
return|return
operator|-
literal|1
return|;
block|}
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
name|ntohl
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
name|ntohl
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
name|ntohl
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
name|ntohl
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
name|ntohl
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
name|ntohl
argument_list|(
name|ph
operator|.
name|magic_number
argument_list|)
expr_stmt|;
name|ph
operator|.
name|spacing
operator|=
name|ntohl
argument_list|(
name|ph
operator|.
name|spacing
argument_list|)
expr_stmt|;
if|if
condition|(
name|ph
operator|.
name|magic_number
operator|!=
name|GBRUSH_MAGIC
operator|||
name|ph
operator|.
name|version
operator|!=
literal|2
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
comment|/* 	 * Create a new image of the proper size and associate the filename with it.    */
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
name|RGB
else|:
name|GRAY
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
literal|"Background"
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
name|RGB_IMAGE
else|:
name|GRAY_IMAGE
argument_list|,
literal|100
argument_list|,
name|NORMAL_MODE
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
DECL|function|save_image (char * filename,gint32 image_ID,gint32 drawable_ID)
specifier|static
name|gint
name|save_image
parameter_list|(
name|char
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
name|BrushHeader
name|ph
decl_stmt|;
name|unsigned
name|char
modifier|*
name|buffer
decl_stmt|;
name|GDrawable
modifier|*
name|drawable
decl_stmt|;
name|gint
name|line
decl_stmt|;
name|GPixelRgn
name|pixel_rgn
decl_stmt|;
name|char
modifier|*
name|temp
decl_stmt|;
name|temp
operator|=
name|g_malloc
argument_list|(
name|strlen
argument_list|(
name|filename
argument_list|)
operator|+
literal|10
argument_list|)
expr_stmt|;
name|sprintf
argument_list|(
name|temp
argument_list|,
literal|"Saving %s:"
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
name|printf
argument_list|(
literal|"Unable to open %s\n"
argument_list|,
name|filename
argument_list|)
expr_stmt|;
return|return
literal|0
return|;
block|}
name|ph
operator|.
name|header_size
operator|=
name|htonl
argument_list|(
sizeof|sizeof
argument_list|(
name|ph
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
name|ph
operator|.
name|version
operator|=
name|htonl
argument_list|(
literal|2
argument_list|)
expr_stmt|;
name|ph
operator|.
name|width
operator|=
name|htonl
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
name|htonl
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
name|htonl
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
name|htonl
argument_list|(
name|GBRUSH_MAGIC
argument_list|)
expr_stmt|;
name|ph
operator|.
name|spacing
operator|=
name|htonl
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
DECL|function|save_dialog ()
specifier|static
name|gint
name|save_dialog
parameter_list|()
block|{
name|GtkWidget
modifier|*
name|dlg
decl_stmt|;
name|GtkWidget
modifier|*
name|button
decl_stmt|;
name|GtkWidget
modifier|*
name|label
decl_stmt|;
name|GtkWidget
modifier|*
name|entry
decl_stmt|;
name|GtkWidget
modifier|*
name|table
decl_stmt|;
name|gchar
modifier|*
modifier|*
name|argv
decl_stmt|;
name|gint
name|argc
decl_stmt|;
name|gchar
name|buffer
index|[
literal|12
index|]
decl_stmt|;
name|argc
operator|=
literal|1
expr_stmt|;
name|argv
operator|=
name|g_new
argument_list|(
name|gchar
operator|*
argument_list|,
literal|1
argument_list|)
expr_stmt|;
name|argv
index|[
literal|0
index|]
operator|=
name|g_strdup
argument_list|(
literal|"plasma"
argument_list|)
expr_stmt|;
name|gtk_init
argument_list|(
operator|&
name|argc
argument_list|,
operator|&
name|argv
argument_list|)
expr_stmt|;
name|gtk_rc_parse
argument_list|(
name|gimp_gtkrc
argument_list|()
argument_list|)
expr_stmt|;
name|dlg
operator|=
name|gtk_dialog_new
argument_list|()
expr_stmt|;
name|gtk_window_set_title
argument_list|(
name|GTK_WINDOW
argument_list|(
name|dlg
argument_list|)
argument_list|,
literal|"Save As Brush"
argument_list|)
expr_stmt|;
name|gtk_window_position
argument_list|(
name|GTK_WINDOW
argument_list|(
name|dlg
argument_list|)
argument_list|,
name|GTK_WIN_POS_MOUSE
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
operator|(
name|GtkSignalFunc
operator|)
name|close_callback
argument_list|,
name|NULL
argument_list|)
expr_stmt|;
comment|/*  Action area  */
name|button
operator|=
name|gtk_button_new_with_label
argument_list|(
literal|"OK"
argument_list|)
expr_stmt|;
name|GTK_WIDGET_SET_FLAGS
argument_list|(
name|button
argument_list|,
name|GTK_CAN_DEFAULT
argument_list|)
expr_stmt|;
name|gtk_signal_connect
argument_list|(
name|GTK_OBJECT
argument_list|(
name|button
argument_list|)
argument_list|,
literal|"clicked"
argument_list|,
operator|(
name|GtkSignalFunc
operator|)
name|ok_callback
argument_list|,
name|dlg
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
name|action_area
argument_list|)
argument_list|,
name|button
argument_list|,
name|TRUE
argument_list|,
name|TRUE
argument_list|,
literal|0
argument_list|)
expr_stmt|;
name|gtk_widget_grab_default
argument_list|(
name|button
argument_list|)
expr_stmt|;
name|gtk_widget_show
argument_list|(
name|button
argument_list|)
expr_stmt|;
name|button
operator|=
name|gtk_button_new_with_label
argument_list|(
literal|"Cancel"
argument_list|)
expr_stmt|;
name|GTK_WIDGET_SET_FLAGS
argument_list|(
name|button
argument_list|,
name|GTK_CAN_DEFAULT
argument_list|)
expr_stmt|;
name|gtk_signal_connect_object
argument_list|(
name|GTK_OBJECT
argument_list|(
name|button
argument_list|)
argument_list|,
literal|"clicked"
argument_list|,
operator|(
name|GtkSignalFunc
operator|)
name|gtk_widget_destroy
argument_list|,
name|GTK_OBJECT
argument_list|(
name|dlg
argument_list|)
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
name|action_area
argument_list|)
argument_list|,
name|button
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
name|button
argument_list|)
expr_stmt|;
comment|/* The main table */
comment|/* Set its size (y, x) */
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
name|gtk_container_border_width
argument_list|(
name|GTK_CONTAINER
argument_list|(
name|table
argument_list|)
argument_list|,
literal|10
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
name|gtk_table_set_row_spacings
argument_list|(
name|GTK_TABLE
argument_list|(
name|table
argument_list|)
argument_list|,
literal|10
argument_list|)
expr_stmt|;
name|gtk_table_set_col_spacings
argument_list|(
name|GTK_TABLE
argument_list|(
name|table
argument_list|)
argument_list|,
literal|10
argument_list|)
expr_stmt|;
comment|/********************** 	 * label 	 **********************/
name|label
operator|=
name|gtk_label_new
argument_list|(
literal|"Spacing:"
argument_list|)
expr_stmt|;
name|gtk_misc_set_alignment
argument_list|(
name|GTK_MISC
argument_list|(
name|label
argument_list|)
argument_list|,
literal|0.0
argument_list|,
literal|0.5
argument_list|)
expr_stmt|;
name|gtk_table_attach
argument_list|(
name|GTK_TABLE
argument_list|(
name|table
argument_list|)
argument_list|,
name|label
argument_list|,
literal|0
argument_list|,
literal|1
argument_list|,
literal|0
argument_list|,
literal|1
argument_list|,
name|GTK_FILL
argument_list|,
name|GTK_FILL
argument_list|,
literal|0
argument_list|,
literal|0
argument_list|)
expr_stmt|;
name|gtk_widget_show
argument_list|(
name|label
argument_list|)
expr_stmt|;
comment|/************************ 	 * The entry 	 ************************/
name|entry
operator|=
name|gtk_entry_new
argument_list|()
expr_stmt|;
name|gtk_table_attach
argument_list|(
name|GTK_TABLE
argument_list|(
name|table
argument_list|)
argument_list|,
name|entry
argument_list|,
literal|1
argument_list|,
literal|2
argument_list|,
literal|0
argument_list|,
literal|1
argument_list|,
name|GTK_EXPAND
operator||
name|GTK_FILL
argument_list|,
name|GTK_EXPAND
operator||
name|GTK_FILL
argument_list|,
literal|0
argument_list|,
literal|0
argument_list|)
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
name|sprintf
argument_list|(
name|buffer
argument_list|,
literal|"%i"
argument_list|,
name|info
operator|.
name|spacing
argument_list|)
expr_stmt|;
name|gtk_entry_set_text
argument_list|(
name|GTK_ENTRY
argument_list|(
name|entry
argument_list|)
argument_list|,
name|buffer
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
operator|(
name|GtkSignalFunc
operator|)
name|entry_callback
argument_list|,
operator|&
name|info
operator|.
name|spacing
argument_list|)
expr_stmt|;
name|gtk_widget_show
argument_list|(
name|entry
argument_list|)
expr_stmt|;
comment|/********************** 	 * label 	 **********************/
name|label
operator|=
name|gtk_label_new
argument_list|(
literal|"Description:"
argument_list|)
expr_stmt|;
name|gtk_misc_set_alignment
argument_list|(
name|GTK_MISC
argument_list|(
name|label
argument_list|)
argument_list|,
literal|0.0
argument_list|,
literal|0.5
argument_list|)
expr_stmt|;
name|gtk_table_attach
argument_list|(
name|GTK_TABLE
argument_list|(
name|table
argument_list|)
argument_list|,
name|label
argument_list|,
literal|0
argument_list|,
literal|1
argument_list|,
literal|1
argument_list|,
literal|2
argument_list|,
name|GTK_FILL
argument_list|,
name|GTK_FILL
argument_list|,
literal|0
argument_list|,
literal|0
argument_list|)
expr_stmt|;
name|gtk_widget_show
argument_list|(
name|label
argument_list|)
expr_stmt|;
comment|/************************ 	 * The entry 	 ************************/
name|entry
operator|=
name|gtk_entry_new
argument_list|()
expr_stmt|;
name|gtk_table_attach
argument_list|(
name|GTK_TABLE
argument_list|(
name|table
argument_list|)
argument_list|,
name|entry
argument_list|,
literal|1
argument_list|,
literal|2
argument_list|,
literal|1
argument_list|,
literal|2
argument_list|,
name|GTK_EXPAND
operator||
name|GTK_FILL
argument_list|,
name|GTK_EXPAND
operator||
name|GTK_FILL
argument_list|,
literal|0
argument_list|,
literal|0
argument_list|)
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
name|info
operator|.
name|description
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
operator|(
name|GtkSignalFunc
operator|)
name|entry_callback
argument_list|,
name|info
operator|.
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
DECL|function|close_callback (GtkWidget * widget,gpointer data)
specifier|static
name|void
name|close_callback
parameter_list|(
name|GtkWidget
modifier|*
name|widget
parameter_list|,
name|gpointer
name|data
parameter_list|)
block|{
name|gtk_main_quit
argument_list|()
expr_stmt|;
block|}
end_function

begin_function
DECL|function|ok_callback (GtkWidget * widget,gpointer data)
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
block|{
name|run_flag
operator|=
literal|1
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
DECL|function|entry_callback (GtkWidget * widget,gpointer data)
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
block|{
if|if
condition|(
name|data
operator|==
name|info
operator|.
name|description
condition|)
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
elseif|else
if|if
condition|(
name|data
operator|==
operator|&
name|info
operator|.
name|spacing
condition|)
name|info
operator|.
name|spacing
operator|=
name|atoi
argument_list|(
name|gtk_entry_get_text
argument_list|(
name|GTK_ENTRY
argument_list|(
name|widget
argument_list|)
argument_list|)
argument_list|)
expr_stmt|;
block|}
end_function

end_unit

