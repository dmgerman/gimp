begin_unit|revision:0.9.5;language:C;cregit-version:0.0.1
begin_comment
comment|/* The GIMP -- an image manipulation program  * Copyright (C) 1995 Spencer Kimball and Peter Mattis  *  * This program is free software; you can redistribute it and/or modify  * it under the terms of the GNU General Public License as published by  * the Free Software Foundation; either version 2 of the License, or  * (at your option) any later version.  *  * This program is distributed in the hope that it will be useful,  * but WITHOUT ANY WARRANTY; without even the implied warranty of  * MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the  * GNU General Public License for more details.  *  * You should have received a copy of the GNU General Public License  * along with this program; if not, write to the Free Software  * Foundation, Inc., 59 Temple Place - Suite 330, Boston, MA 02111-1307, USA.  */
end_comment

begin_comment
comment|/*  saves and loads gimp icon files (For toolbox, etc)...  */
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
file|"libgimp/gimp.h"
end_include

begin_include
include|#
directive|include
file|"libgimp/gimpui.h"
end_include

begin_include
include|#
directive|include
file|"libgimp/stdplugins-intl.h"
end_include

begin_typedef
typedef|typedef
struct|struct
DECL|struct|__anon29d837110108
block|{
DECL|member|icon_name
name|gchar
name|icon_name
index|[
literal|256
index|]
decl_stmt|;
DECL|typedef|GIconSaveVals
block|}
name|GIconSaveVals
typedef|;
end_typedef

begin_typedef
typedef|typedef
struct|struct
DECL|struct|__anon29d837110208
block|{
DECL|member|run
name|gint
name|run
decl_stmt|;
DECL|typedef|GIconSaveInterface
block|}
name|GIconSaveInterface
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
name|void
name|init_gtk
parameter_list|(
name|void
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

begin_decl_stmt
DECL|variable|givals
specifier|static
name|GIconSaveVals
name|givals
init|=
block|{
literal|"gicon"
comment|/*  icon_name  */
block|}
decl_stmt|;
end_decl_stmt

begin_decl_stmt
DECL|variable|giint
specifier|static
name|GIconSaveInterface
name|giint
init|=
block|{
name|FALSE
comment|/*  run  */
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
name|PARAM_STRING
block|,
literal|"icon_name"
block|,
literal|"The name of the icon"
block|}
block|}
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
name|INIT_I18N
argument_list|()
expr_stmt|;
name|gimp_install_procedure
argument_list|(
literal|"file_gicon_load"
argument_list|,
name|_
argument_list|(
literal|"loads files of the .ico file format"
argument_list|)
argument_list|,
name|_
argument_list|(
literal|"FIXME: write help"
argument_list|)
argument_list|,
literal|"Spencer Kimball"
argument_list|,
literal|"Spencer Kimball"
argument_list|,
literal|"1997"
argument_list|,
literal|"<Load>/GIcon"
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
literal|"file_gicon_save"
argument_list|,
name|_
argument_list|(
literal|"saves files in the .ico file format"
argument_list|)
argument_list|,
name|_
argument_list|(
literal|"FIXME: write help"
argument_list|)
argument_list|,
literal|"Spencer Kimball"
argument_list|,
literal|"Spencer Kimball"
argument_list|,
literal|"1997"
argument_list|,
literal|"<Save>/GIcon"
argument_list|,
literal|"GRAY*"
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
name|gimp_register_load_handler
argument_list|(
literal|"file_gicon_load"
argument_list|,
literal|"ico"
argument_list|,
literal|""
argument_list|)
expr_stmt|;
name|gimp_register_save_handler
argument_list|(
literal|"file_gicon_save"
argument_list|,
literal|"ico"
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
name|gint32
name|drawable_ID
decl_stmt|;
name|GStatusType
name|status
init|=
name|STATUS_SUCCESS
decl_stmt|;
name|GimpExportReturnType
name|export
init|=
name|EXPORT_CANCEL
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
literal|"file_gicon_load"
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
literal|"file_gicon_save"
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
name|RUN_INTERACTIVE
case|:
case|case
name|RUN_WITH_LAST_VALS
case|:
name|INIT_I18N_UI
argument_list|()
expr_stmt|;
name|init_gtk
argument_list|()
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
literal|"GIcon"
argument_list|,
operator|(
name|CAN_HANDLE_GRAY
operator||
name|CAN_HANDLE_ALPHA
operator|)
argument_list|)
expr_stmt|;
if|if
condition|(
name|export
operator|==
name|EXPORT_CANCEL
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
name|STATUS_EXECUTION_ERROR
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
name|RUN_INTERACTIVE
case|:
comment|/*  Possibly retrieve data  */
name|gimp_get_data
argument_list|(
literal|"file_gicon_save"
argument_list|,
operator|&
name|givals
argument_list|)
expr_stmt|;
comment|/*  First acquire information with a dialog  */
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
comment|/*  Make sure all the arguments are there!  */
if|if
condition|(
name|nparams
operator|!=
literal|6
condition|)
name|status
operator|=
name|STATUS_CALLING_ERROR
expr_stmt|;
else|else
name|strncpy
argument_list|(
name|givals
operator|.
name|icon_name
argument_list|,
name|param
index|[
literal|5
index|]
operator|.
name|data
operator|.
name|d_string
argument_list|,
literal|256
argument_list|)
expr_stmt|;
break|break;
case|case
name|RUN_WITH_LAST_VALS
case|:
comment|/*  Possibly retrieve data  */
name|gimp_get_data
argument_list|(
literal|"file_gicon_save"
argument_list|,
operator|&
name|givals
argument_list|)
expr_stmt|;
break|break;
default|default:
break|break;
block|}
operator|*
name|nreturn_vals
operator|=
literal|1
expr_stmt|;
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
comment|/*  Store persistent data  */
name|gimp_set_data
argument_list|(
literal|"file_gicon_save"
argument_list|,
operator|&
name|givals
argument_list|,
sizeof|sizeof
argument_list|(
name|GIconSaveVals
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
if|if
condition|(
name|export
operator|==
name|EXPORT_EXPORT
condition|)
name|gimp_image_delete
argument_list|(
name|image_ID
argument_list|)
expr_stmt|;
block|}
block|}
end_function

begin_function
specifier|static
name|gint32
DECL|function|load_image (char * filename)
name|load_image
parameter_list|(
name|char
modifier|*
name|filename
parameter_list|)
block|{
name|GDrawable
modifier|*
name|drawable
decl_stmt|;
name|GPixelRgn
name|pixel_rgn
decl_stmt|;
name|FILE
modifier|*
name|fp
decl_stmt|;
name|gint32
name|image_ID
decl_stmt|;
name|gint32
name|layer_ID
decl_stmt|;
name|char
name|name_buf
index|[
literal|256
index|]
decl_stmt|;
name|char
modifier|*
name|data_buf
decl_stmt|;
name|unsigned
name|char
modifier|*
name|dest
decl_stmt|;
name|int
name|val
decl_stmt|;
name|int
name|width
decl_stmt|,
name|height
decl_stmt|;
name|int
name|i
decl_stmt|,
name|j
decl_stmt|;
comment|/*  Open the requested file  */
if|if
condition|(
operator|!
operator|(
name|fp
operator|=
name|fopen
argument_list|(
name|filename
argument_list|,
literal|"r"
argument_list|)
operator|)
condition|)
block|{
name|fprintf
argument_list|(
name|stderr
argument_list|,
literal|"gicon: can't open \"%s\"\n"
argument_list|,
name|filename
argument_list|)
expr_stmt|;
return|return
operator|-
literal|1
return|;
block|}
comment|/*  Check the identifier string  */
name|fscanf
argument_list|(
name|fp
argument_list|,
literal|"/*  %s icon image format -- S. Kimball, P. Mattis  */\n"
argument_list|,
name|name_buf
argument_list|)
expr_stmt|;
if|if
condition|(
name|strcmp
argument_list|(
literal|"GIMP"
argument_list|,
name|name_buf
argument_list|)
condition|)
block|{
name|fprintf
argument_list|(
name|stderr
argument_list|,
literal|"Not a GIcon file: %s!\n"
argument_list|,
name|filename
argument_list|)
expr_stmt|;
return|return
operator|-
literal|1
return|;
block|}
comment|/*  Parse the icon name  */
name|fscanf
argument_list|(
name|fp
argument_list|,
literal|"/*  Image name: %s  */\n"
argument_list|,
name|name_buf
argument_list|)
expr_stmt|;
comment|/*  Get the width and height  */
name|fscanf
argument_list|(
name|fp
argument_list|,
literal|"#define %s %d\n"
argument_list|,
name|name_buf
argument_list|,
operator|&
name|width
argument_list|)
expr_stmt|;
name|fscanf
argument_list|(
name|fp
argument_list|,
literal|"#define %s %d\n"
argument_list|,
name|name_buf
argument_list|,
operator|&
name|height
argument_list|)
expr_stmt|;
name|fscanf
argument_list|(
name|fp
argument_list|,
literal|"static char *%s [] = \n{\n"
argument_list|,
name|name_buf
argument_list|)
expr_stmt|;
comment|/*  Get a new image structure  */
name|image_ID
operator|=
name|gimp_image_new
argument_list|(
name|width
argument_list|,
name|height
argument_list|,
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
name|width
argument_list|,
name|height
argument_list|,
name|GRAYA_IMAGE
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
name|data_buf
operator|=
name|g_new
argument_list|(
name|char
argument_list|,
name|width
argument_list|)
expr_stmt|;
name|dest
operator|=
name|g_new
argument_list|(
name|guchar
argument_list|,
name|width
operator|*
literal|2
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
name|height
condition|;
name|i
operator|++
control|)
block|{
name|fscanf
argument_list|(
name|fp
argument_list|,
literal|"  \"%s\",\n"
argument_list|,
name|data_buf
argument_list|)
expr_stmt|;
for|for
control|(
name|j
operator|=
literal|0
init|;
name|j
operator|<
name|width
condition|;
name|j
operator|++
control|)
block|{
name|val
operator|=
name|data_buf
index|[
name|j
index|]
expr_stmt|;
if|if
condition|(
name|val
operator|==
literal|'.'
condition|)
block|{
name|dest
index|[
name|j
operator|*
literal|2
operator|+
literal|0
index|]
operator|=
literal|0
expr_stmt|;
name|dest
index|[
name|j
operator|*
literal|2
operator|+
literal|1
index|]
operator|=
literal|0
expr_stmt|;
comment|/*  set alpha channel to transparent  */
block|}
else|else
block|{
name|dest
index|[
name|j
operator|*
literal|2
operator|+
literal|0
index|]
operator|=
operator|(
literal|255
operator|*
operator|(
name|val
operator|-
literal|'a'
operator|)
operator|)
operator|/
literal|7
expr_stmt|;
name|dest
index|[
name|j
operator|*
literal|2
operator|+
literal|1
index|]
operator|=
literal|255
expr_stmt|;
comment|/*  set alpha channel to opaque  */
block|}
block|}
name|gimp_pixel_rgn_set_row
argument_list|(
operator|&
name|pixel_rgn
argument_list|,
name|dest
argument_list|,
literal|0
argument_list|,
name|i
argument_list|,
name|width
argument_list|)
expr_stmt|;
block|}
comment|/*  Clean up  */
name|fclose
argument_list|(
name|fp
argument_list|)
expr_stmt|;
name|gimp_drawable_flush
argument_list|(
name|drawable
argument_list|)
expr_stmt|;
name|g_free
argument_list|(
name|data_buf
argument_list|)
expr_stmt|;
name|g_free
argument_list|(
name|dest
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
DECL|function|save_image (char * filename,gint32 image_ID,gint32 drawable_ID)
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
name|GDrawable
modifier|*
name|drawable
decl_stmt|;
name|GPixelRgn
name|pixel_rgn
decl_stmt|;
name|FILE
modifier|*
name|fp
decl_stmt|;
name|int
name|i
decl_stmt|,
name|j
decl_stmt|;
name|int
name|w
decl_stmt|,
name|h
decl_stmt|;
name|int
name|has_alpha
decl_stmt|;
name|int
name|val
decl_stmt|;
name|char
name|ch
decl_stmt|;
name|unsigned
name|char
modifier|*
name|src_buf
decl_stmt|,
modifier|*
name|src
decl_stmt|;
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
name|w
operator|=
name|drawable
operator|->
name|width
expr_stmt|;
name|h
operator|=
name|drawable
operator|->
name|height
expr_stmt|;
name|has_alpha
operator|=
name|gimp_drawable_has_alpha
argument_list|(
name|drawable_ID
argument_list|)
expr_stmt|;
comment|/*  open the file for writing  */
if|if
condition|(
operator|(
name|fp
operator|=
name|fopen
argument_list|(
name|filename
argument_list|,
literal|"w"
argument_list|)
operator|)
condition|)
block|{
name|fprintf
argument_list|(
name|fp
argument_list|,
literal|"/*  GIMP icon image format -- S. Kimball, P. Mattis  */\n"
argument_list|)
expr_stmt|;
name|fprintf
argument_list|(
name|fp
argument_list|,
literal|"/*  Image name: %s  */\n"
argument_list|,
name|givals
operator|.
name|icon_name
argument_list|)
expr_stmt|;
name|fprintf
argument_list|(
name|fp
argument_list|,
literal|"\n\n"
argument_list|)
expr_stmt|;
name|fprintf
argument_list|(
name|fp
argument_list|,
literal|"#define %s_width %d\n"
argument_list|,
name|givals
operator|.
name|icon_name
argument_list|,
name|w
argument_list|)
expr_stmt|;
name|fprintf
argument_list|(
name|fp
argument_list|,
literal|"#define %s_height %d\n"
argument_list|,
name|givals
operator|.
name|icon_name
argument_list|,
name|h
argument_list|)
expr_stmt|;
name|fprintf
argument_list|(
name|fp
argument_list|,
literal|"static char *%s_bits [] = \n{\n"
argument_list|,
name|givals
operator|.
name|icon_name
argument_list|)
expr_stmt|;
comment|/*  write the brush data to the file  */
name|src_buf
operator|=
name|g_new
argument_list|(
name|guchar
argument_list|,
name|w
operator|*
name|drawable
operator|->
name|bpp
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
name|h
condition|;
name|i
operator|++
control|)
block|{
name|gimp_pixel_rgn_get_row
argument_list|(
operator|&
name|pixel_rgn
argument_list|,
name|src_buf
argument_list|,
literal|0
argument_list|,
name|i
argument_list|,
name|w
argument_list|)
expr_stmt|;
name|src
operator|=
name|src_buf
expr_stmt|;
name|fprintf
argument_list|(
name|fp
argument_list|,
literal|"  \""
argument_list|)
expr_stmt|;
for|for
control|(
name|j
operator|=
literal|0
init|;
name|j
operator|<
name|w
condition|;
name|j
operator|++
control|)
block|{
if|if
condition|(
name|has_alpha
operator|&&
operator|!
name|src
index|[
literal|1
index|]
condition|)
block|{
name|ch
operator|=
literal|'.'
expr_stmt|;
block|}
else|else
block|{
name|val
operator|=
call|(
name|int
call|)
argument_list|(
operator|(
name|double
operator|)
name|src
index|[
literal|0
index|]
operator|*
literal|7.0
operator|/
literal|255.0
operator|+
literal|0.5
argument_list|)
expr_stmt|;
name|ch
operator|=
literal|'a'
operator|+
name|val
expr_stmt|;
block|}
name|fputc
argument_list|(
name|ch
argument_list|,
name|fp
argument_list|)
expr_stmt|;
name|src
operator|+=
name|drawable
operator|->
name|bpp
expr_stmt|;
block|}
name|fprintf
argument_list|(
name|fp
argument_list|,
operator|(
name|i
operator|==
operator|(
name|h
operator|-
literal|1
operator|)
operator|)
condition|?
literal|"\"\n};\n"
else|:
literal|"\",\n"
argument_list|)
expr_stmt|;
block|}
comment|/*  Clean up  */
name|g_free
argument_list|(
name|src_buf
argument_list|)
expr_stmt|;
name|fclose
argument_list|(
name|fp
argument_list|)
expr_stmt|;
block|}
return|return
name|TRUE
return|;
block|}
end_function

begin_function
specifier|static
name|void
DECL|function|init_gtk (void)
name|init_gtk
parameter_list|(
name|void
parameter_list|)
block|{
name|gchar
modifier|*
modifier|*
name|argv
decl_stmt|;
name|gint
name|argc
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
literal|"gicon"
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
name|dlg
operator|=
name|gimp_dialog_new
argument_list|(
name|_
argument_list|(
literal|"Save as GIcon"
argument_list|)
argument_list|,
literal|"gicon"
argument_list|,
name|gimp_plugin_help_func
argument_list|,
literal|"filters/gicon.html"
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
comment|/**********************    * label    **********************/
name|label
operator|=
name|gtk_label_new
argument_list|(
name|_
argument_list|(
literal|"Icon Name:"
argument_list|)
argument_list|)
expr_stmt|;
name|gtk_misc_set_alignment
argument_list|(
name|GTK_MISC
argument_list|(
name|label
argument_list|)
argument_list|,
literal|1.0
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
comment|/************************    * The entry    ************************/
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
name|gtk_entry_set_text
argument_list|(
name|GTK_ENTRY
argument_list|(
name|entry
argument_list|)
argument_list|,
name|givals
operator|.
name|icon_name
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
name|givals
operator|.
name|icon_name
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
name|giint
operator|.
name|run
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
name|giint
operator|.
name|run
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
name|strncpy
argument_list|(
name|givals
operator|.
name|icon_name
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

