begin_unit|revision:0.9.5;language:C;cregit-version:0.0.1
begin_comment
comment|/**  * aa.c version 1.0  * A plugin that uses libaa (ftp://ftp.ta.jcu.cz/pub/aa) to save images as  * ASCII.  * NOTE: This plugin *requires* aalib 1.2 or later. Earlier versions will  * not work.  * Code copied from all over the GIMP source.  * Tim Newsome<nuisance@cmu.edu>  */
end_comment

begin_comment
comment|/* The GIMP -- an image manipulation program  * Copyright (C) 1995 Spencer Kimball and Peter Mattis  *  * This program is free software; you can redistribute it and/or modify  * it under the terms of the GNU General Public License as published by  * the Free Software Foundation; either version 2 of the License, or  * (at your option) any later version.  *  * This program is distributed in the hope that it will be useful,  * but WITHOUT ANY WARRANTY; without even the implied warranty of  * MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the  * GNU General Public License for more details.  *  * You should have received a copy of the GNU General Public License  * along with this program; if not, write to the Free Software  * Foundation, Inc., 59 Temple Place - Suite 330, Boston, MA 02111-1307, USA.  */
end_comment

begin_include
include|#
directive|include
file|"config.h"
end_include

begin_include
include|#
directive|include
file|<string.h>
end_include

begin_include
include|#
directive|include
file|<aalib.h>
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

begin_comment
comment|/*  * Declare some local functions.  */
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
name|gboolean
name|save_aa
parameter_list|(
name|gint32
name|drawable_ID
parameter_list|,
name|gchar
modifier|*
name|filename
parameter_list|,
name|gint
name|output_type
parameter_list|)
function_decl|;
end_function_decl

begin_function_decl
specifier|static
name|void
name|gimp2aa
parameter_list|(
name|gint32
name|drawable_ID
parameter_list|,
name|aa_context
modifier|*
name|context
parameter_list|)
function_decl|;
end_function_decl

begin_function_decl
specifier|static
name|gint
name|type_dialog
parameter_list|(
name|gint
name|selected
parameter_list|)
function_decl|;
end_function_decl

begin_function_decl
specifier|static
name|void
name|type_dialog_toggle_update
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

begin_comment
comment|/*  * Some global variables.  */
end_comment

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

begin_comment
comment|/**  * Type the user selected. (Global for easier UI coding.)  */
end_comment

begin_decl_stmt
DECL|variable|selected_type
specifier|static
name|gint
name|selected_type
init|=
literal|0
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
literal|"The name entered"
block|}
block|,
block|{
name|GIMP_PDB_STRING
block|,
literal|"file_type"
block|,
literal|"File type to use"
block|}
block|}
decl_stmt|;
name|gimp_install_procedure
argument_list|(
literal|"file_aa_save"
argument_list|,
literal|"Saves grayscale image in various text formats"
argument_list|,
literal|"This plug-in uses aalib to save grayscale image "
literal|"as ascii art into a variety of text formats"
argument_list|,
literal|"Tim Newsome<nuisance@cmu.edu>"
argument_list|,
literal|"Tim Newsome<nuisance@cmu.edu>"
argument_list|,
literal|"1997"
argument_list|,
name|N_
argument_list|(
literal|"ASCII art"
argument_list|)
argument_list|,
literal|"RGB*, GRAY*"
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
name|gimp_plugin_menu_register
argument_list|(
literal|"file_aa_save"
argument_list|,
literal|"<Save>"
argument_list|)
expr_stmt|;
name|gimp_register_file_handler_mime
argument_list|(
literal|"file_aa_save"
argument_list|,
literal|"text/plain"
argument_list|)
expr_stmt|;
name|gimp_register_save_handler
argument_list|(
literal|"file_aa_save"
argument_list|,
literal|"txt,ansi,text"
argument_list|,
literal|""
argument_list|)
expr_stmt|;
block|}
end_function

begin_comment
comment|/**  * Searches aa_formats defined by aalib to find the index of the type  * specified by string.  * -1 means it wasn't found.  */
end_comment

begin_function
specifier|static
name|gint
DECL|function|get_type_from_string (const gchar * string)
name|get_type_from_string
parameter_list|(
specifier|const
name|gchar
modifier|*
name|string
parameter_list|)
block|{
name|gint
name|type
init|=
literal|0
decl_stmt|;
name|aa_format
modifier|*
modifier|*
name|p
init|=
operator|(
name|aa_format
operator|*
operator|*
operator|)
name|aa_formats
decl_stmt|;
while|while
condition|(
operator|*
name|p
operator|&&
name|strcmp
argument_list|(
operator|(
operator|*
name|p
operator|)
operator|->
name|formatname
argument_list|,
name|string
argument_list|)
condition|)
block|{
name|p
operator|++
expr_stmt|;
name|type
operator|++
expr_stmt|;
block|}
if|if
condition|(
operator|*
name|p
operator|==
name|NULL
condition|)
return|return
operator|-
literal|1
return|;
return|return
name|type
return|;
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
name|gint
name|output_type
init|=
literal|0
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
name|INIT_I18N
argument_list|()
expr_stmt|;
comment|/* Set us up to return a status. */
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
literal|"aa"
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
literal|"AA"
argument_list|,
operator|(
name|GIMP_EXPORT_CAN_HANDLE_RGB
operator||
name|GIMP_EXPORT_CAN_HANDLE_GRAY
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
if|if
condition|(
operator|!
operator|(
name|gimp_drawable_is_rgb
argument_list|(
name|drawable_ID
argument_list|)
operator|||
name|gimp_drawable_is_gray
argument_list|(
name|drawable_ID
argument_list|)
operator|)
condition|)
block|{
name|status
operator|=
name|GIMP_PDB_CALLING_ERROR
expr_stmt|;
block|}
if|if
condition|(
name|status
operator|==
name|GIMP_PDB_SUCCESS
condition|)
block|{
switch|switch
condition|(
name|run_mode
condition|)
block|{
case|case
name|GIMP_RUN_INTERACTIVE
case|:
name|gimp_get_data
argument_list|(
literal|"file_aa_save"
argument_list|,
operator|&
name|output_type
argument_list|)
expr_stmt|;
name|output_type
operator|=
name|type_dialog
argument_list|(
name|output_type
argument_list|)
expr_stmt|;
if|if
condition|(
name|output_type
operator|<
literal|0
condition|)
name|status
operator|=
name|GIMP_PDB_CANCEL
expr_stmt|;
break|break;
case|case
name|GIMP_RUN_NONINTERACTIVE
case|:
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
name|output_type
operator|=
name|get_type_from_string
argument_list|(
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
if|if
condition|(
name|output_type
operator|<
literal|0
condition|)
name|status
operator|=
name|GIMP_PDB_CALLING_ERROR
expr_stmt|;
block|}
break|break;
case|case
name|GIMP_RUN_WITH_LAST_VALS
case|:
name|gimp_get_data
argument_list|(
literal|"file_aa_save"
argument_list|,
operator|&
name|output_type
argument_list|)
expr_stmt|;
break|break;
default|default:
break|break;
block|}
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
name|save_aa
argument_list|(
name|drawable_ID
argument_list|,
name|param
index|[
literal|3
index|]
operator|.
name|data
operator|.
name|d_string
argument_list|,
name|output_type
argument_list|)
condition|)
block|{
name|gimp_set_data
argument_list|(
literal|"file_aa_save"
argument_list|,
operator|&
name|output_type
argument_list|,
sizeof|sizeof
argument_list|(
name|output_type
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

begin_comment
comment|/**  * The actual save function. What it's all about.  * The image type has to be GRAY.  */
end_comment

begin_function
specifier|static
name|gboolean
DECL|function|save_aa (gint32 drawable_ID,gchar * filename,gint output_type)
name|save_aa
parameter_list|(
name|gint32
name|drawable_ID
parameter_list|,
name|gchar
modifier|*
name|filename
parameter_list|,
name|gint
name|output_type
parameter_list|)
block|{
name|aa_savedata
name|savedata
decl_stmt|;
name|aa_context
modifier|*
name|context
decl_stmt|;
name|aa_format
name|format
init|=
operator|*
name|aa_formats
index|[
name|output_type
index|]
decl_stmt|;
name|format
operator|.
name|width
operator|=
name|gimp_drawable_width
argument_list|(
name|drawable_ID
argument_list|)
operator|/
literal|2
expr_stmt|;
name|format
operator|.
name|height
operator|=
name|gimp_drawable_height
argument_list|(
name|drawable_ID
argument_list|)
operator|/
literal|2
expr_stmt|;
comment|/* Get a libaa context which will save its output to filename. */
name|savedata
operator|.
name|name
operator|=
name|filename
expr_stmt|;
name|savedata
operator|.
name|format
operator|=
operator|&
name|format
expr_stmt|;
name|context
operator|=
name|aa_init
argument_list|(
operator|&
name|save_d
argument_list|,
operator|&
name|aa_defparams
argument_list|,
operator|&
name|savedata
argument_list|)
expr_stmt|;
if|if
condition|(
operator|!
name|context
condition|)
return|return
name|FALSE
return|;
name|gimp2aa
argument_list|(
name|drawable_ID
argument_list|,
name|context
argument_list|)
expr_stmt|;
name|aa_flush
argument_list|(
name|context
argument_list|)
expr_stmt|;
name|aa_close
argument_list|(
name|context
argument_list|)
expr_stmt|;
return|return
name|TRUE
return|;
block|}
end_function

begin_function
specifier|static
name|void
DECL|function|gimp2aa (gint32 drawable_ID,aa_context * context)
name|gimp2aa
parameter_list|(
name|gint32
name|drawable_ID
parameter_list|,
name|aa_context
modifier|*
name|context
parameter_list|)
block|{
name|GimpDrawable
modifier|*
name|drawable
decl_stmt|;
name|GimpPixelRgn
name|pixel_rgn
decl_stmt|;
name|aa_renderparams
modifier|*
name|renderparams
decl_stmt|;
name|gint
name|width
decl_stmt|;
name|gint
name|height
decl_stmt|;
name|gint
name|x
decl_stmt|,
name|y
decl_stmt|;
name|gint
name|bpp
decl_stmt|;
name|guchar
modifier|*
name|buffer
decl_stmt|;
name|guchar
modifier|*
name|p
decl_stmt|;
name|drawable
operator|=
name|gimp_drawable_get
argument_list|(
name|drawable_ID
argument_list|)
expr_stmt|;
name|width
operator|=
name|aa_imgwidth
argument_list|(
name|context
argument_list|)
expr_stmt|;
name|height
operator|=
name|aa_imgheight
argument_list|(
name|context
argument_list|)
expr_stmt|;
name|bpp
operator|=
name|drawable
operator|->
name|bpp
expr_stmt|;
name|gimp_tile_cache_ntiles
argument_list|(
operator|(
name|width
operator|/
name|gimp_tile_width
argument_list|()
operator|)
operator|+
literal|1
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
name|width
argument_list|,
name|height
argument_list|,
name|FALSE
argument_list|,
name|FALSE
argument_list|)
expr_stmt|;
name|buffer
operator|=
name|g_new
argument_list|(
name|guchar
argument_list|,
name|width
operator|*
name|bpp
argument_list|)
expr_stmt|;
for|for
control|(
name|y
operator|=
literal|0
init|;
name|y
operator|<
name|height
condition|;
name|y
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
name|y
argument_list|,
name|width
argument_list|)
expr_stmt|;
switch|switch
condition|(
name|bpp
condition|)
block|{
case|case
literal|1
case|:
comment|/* GRAY */
for|for
control|(
name|x
operator|=
literal|0
operator|,
name|p
operator|=
name|buffer
init|;
name|x
operator|<
name|width
condition|;
name|x
operator|++
operator|,
name|p
operator|++
control|)
name|aa_putpixel
argument_list|(
name|context
argument_list|,
name|x
argument_list|,
name|y
argument_list|,
operator|*
name|p
argument_list|)
expr_stmt|;
break|break;
case|case
literal|2
case|:
comment|/* GRAYA, blend over black */
for|for
control|(
name|x
operator|=
literal|0
operator|,
name|p
operator|=
name|buffer
init|;
name|x
operator|<
name|width
condition|;
name|x
operator|++
operator|,
name|p
operator|+=
literal|2
control|)
name|aa_putpixel
argument_list|(
name|context
argument_list|,
name|x
argument_list|,
name|y
argument_list|,
operator|(
name|p
index|[
literal|0
index|]
operator|*
operator|(
name|p
index|[
literal|1
index|]
operator|+
literal|1
operator|)
operator|)
operator|>>
literal|8
argument_list|)
expr_stmt|;
break|break;
case|case
literal|3
case|:
comment|/* RGB */
for|for
control|(
name|x
operator|=
literal|0
operator|,
name|p
operator|=
name|buffer
init|;
name|x
operator|<
name|width
condition|;
name|x
operator|++
operator|,
name|p
operator|+=
literal|3
control|)
name|aa_putpixel
argument_list|(
name|context
argument_list|,
name|x
argument_list|,
name|y
argument_list|,
name|GIMP_RGB_INTENSITY
argument_list|(
name|p
index|[
literal|0
index|]
argument_list|,
name|p
index|[
literal|1
index|]
argument_list|,
name|p
index|[
literal|2
index|]
argument_list|)
operator|+
literal|0.5
argument_list|)
expr_stmt|;
break|break;
case|case
literal|4
case|:
comment|/* RGBA, blend over black */
for|for
control|(
name|x
operator|=
literal|0
operator|,
name|p
operator|=
name|buffer
init|;
name|x
operator|<
name|width
condition|;
name|x
operator|++
operator|,
name|p
operator|+=
literal|4
control|)
name|aa_putpixel
argument_list|(
name|context
argument_list|,
name|x
argument_list|,
name|y
argument_list|,
operator|(
call|(
name|guchar
call|)
argument_list|(
name|GIMP_RGB_INTENSITY
argument_list|(
name|p
index|[
literal|0
index|]
argument_list|,
name|p
index|[
literal|1
index|]
argument_list|,
name|p
index|[
literal|2
index|]
argument_list|)
operator|+
literal|0.5
argument_list|)
operator|*
operator|(
name|p
index|[
literal|3
index|]
operator|+
literal|1
operator|)
operator|)
operator|>>
literal|8
argument_list|)
expr_stmt|;
break|break;
default|default:
name|g_assert_not_reached
argument_list|()
expr_stmt|;
break|break;
block|}
block|}
name|g_free
argument_list|(
name|buffer
argument_list|)
expr_stmt|;
name|renderparams
operator|=
name|aa_getrenderparams
argument_list|()
expr_stmt|;
name|renderparams
operator|->
name|dither
operator|=
name|AA_FLOYD_S
expr_stmt|;
name|aa_render
argument_list|(
name|context
argument_list|,
name|renderparams
argument_list|,
literal|0
argument_list|,
literal|0
argument_list|,
name|aa_scrwidth
argument_list|(
name|context
argument_list|)
argument_list|,
name|aa_scrheight
argument_list|(
name|context
argument_list|)
argument_list|)
expr_stmt|;
block|}
end_function

begin_function
specifier|static
name|gint
DECL|function|type_dialog (gint selected)
name|type_dialog
parameter_list|(
name|gint
name|selected
parameter_list|)
block|{
name|GtkWidget
modifier|*
name|dlg
decl_stmt|;
name|GtkWidget
modifier|*
name|toggle
decl_stmt|;
name|GtkWidget
modifier|*
name|frame
decl_stmt|;
name|GtkWidget
modifier|*
name|toggle_vbox
decl_stmt|;
name|GSList
modifier|*
name|group
decl_stmt|;
comment|/* Create the actual window. */
name|dlg
operator|=
name|gimp_dialog_new
argument_list|(
name|_
argument_list|(
literal|"Save as Text"
argument_list|)
argument_list|,
literal|"aa"
argument_list|,
name|NULL
argument_list|,
literal|0
argument_list|,
name|gimp_standard_help_func
argument_list|,
literal|"file-aa-save"
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
comment|/*  file save type  */
name|frame
operator|=
name|gimp_frame_new
argument_list|(
name|_
argument_list|(
literal|"Data Formatting"
argument_list|)
argument_list|)
expr_stmt|;
name|gtk_container_set_border_width
argument_list|(
name|GTK_CONTAINER
argument_list|(
name|frame
argument_list|)
argument_list|,
literal|12
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
name|frame
argument_list|,
name|TRUE
argument_list|,
name|TRUE
argument_list|,
literal|0
argument_list|)
expr_stmt|;
name|toggle_vbox
operator|=
name|gtk_vbox_new
argument_list|(
name|FALSE
argument_list|,
literal|2
argument_list|)
expr_stmt|;
name|gtk_container_set_border_width
argument_list|(
name|GTK_CONTAINER
argument_list|(
name|toggle_vbox
argument_list|)
argument_list|,
literal|4
argument_list|)
expr_stmt|;
name|gtk_container_add
argument_list|(
name|GTK_CONTAINER
argument_list|(
name|frame
argument_list|)
argument_list|,
name|toggle_vbox
argument_list|)
expr_stmt|;
name|group
operator|=
name|NULL
expr_stmt|;
block|{
name|aa_format
modifier|*
modifier|*
name|p
init|=
operator|(
name|aa_format
operator|*
operator|*
operator|)
name|aa_formats
decl_stmt|;
name|gint
name|current
init|=
literal|0
decl_stmt|;
while|while
condition|(
operator|*
name|p
operator|!=
name|NULL
condition|)
block|{
name|toggle
operator|=
name|gtk_radio_button_new_with_label
argument_list|(
name|group
argument_list|,
operator|(
operator|*
name|p
operator|)
operator|->
name|formatname
argument_list|)
expr_stmt|;
name|group
operator|=
name|gtk_radio_button_get_group
argument_list|(
name|GTK_RADIO_BUTTON
argument_list|(
name|toggle
argument_list|)
argument_list|)
expr_stmt|;
name|gtk_box_pack_start
argument_list|(
name|GTK_BOX
argument_list|(
name|toggle_vbox
argument_list|)
argument_list|,
name|toggle
argument_list|,
name|FALSE
argument_list|,
name|FALSE
argument_list|,
literal|0
argument_list|)
expr_stmt|;
name|gtk_widget_show
argument_list|(
name|toggle
argument_list|)
expr_stmt|;
name|g_signal_connect
argument_list|(
name|toggle
argument_list|,
literal|"toggled"
argument_list|,
name|G_CALLBACK
argument_list|(
name|type_dialog_toggle_update
argument_list|)
argument_list|,
call|(
name|gpointer
call|)
argument_list|(
operator|*
name|p
argument_list|)
operator|->
name|formatname
argument_list|)
expr_stmt|;
if|if
condition|(
name|current
operator|==
name|selected
condition|)
name|gtk_toggle_button_set_active
argument_list|(
name|GTK_TOGGLE_BUTTON
argument_list|(
name|toggle
argument_list|)
argument_list|,
name|TRUE
argument_list|)
expr_stmt|;
name|p
operator|++
expr_stmt|;
name|current
operator|++
expr_stmt|;
block|}
block|}
name|gtk_widget_show
argument_list|(
name|toggle_vbox
argument_list|)
expr_stmt|;
name|gtk_widget_show
argument_list|(
name|frame
argument_list|)
expr_stmt|;
name|gtk_widget_show
argument_list|(
name|dlg
argument_list|)
expr_stmt|;
if|if
condition|(
name|gimp_dialog_run
argument_list|(
name|GIMP_DIALOG
argument_list|(
name|dlg
argument_list|)
argument_list|)
operator|!=
name|GTK_RESPONSE_OK
condition|)
name|selected_type
operator|=
operator|-
literal|1
expr_stmt|;
name|gtk_widget_destroy
argument_list|(
name|dlg
argument_list|)
expr_stmt|;
return|return
name|selected_type
return|;
block|}
end_function

begin_function
specifier|static
name|void
DECL|function|type_dialog_toggle_update (GtkWidget * widget,gpointer data)
name|type_dialog_toggle_update
parameter_list|(
name|GtkWidget
modifier|*
name|widget
parameter_list|,
name|gpointer
name|data
parameter_list|)
block|{
name|selected_type
operator|=
name|get_type_from_string
argument_list|(
operator|(
specifier|const
name|gchar
operator|*
operator|)
name|data
argument_list|)
expr_stmt|;
block|}
end_function

end_unit

