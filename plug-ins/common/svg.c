begin_unit|revision:0.9.5;language:C;cregit-version:0.0.1
begin_comment
comment|/* The GIMP -- an image manipulation program  * Copyright (C) 1995 Spencer Kimball and Peter Mattis  *  * This program is free software; you can redistribute it and/or modify  * it under the terms of the GNU General Public License as published by  * the Free Software Foundation; either version 2 of the License, or  * (at your option) any later version.  *  * This program is distributed in the hope that it will be useful,  * but WITHOUT ANY WARRANTY; without even the implied warranty of  * MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the  * GNU General Public License for more details.  *  * You should have received a copy of the GNU General Public License  * along with this program; if not, write to the Free Software  * Foundation, Inc., 59 Temple Place - Suite 330, Boston, MA 02111-1307, USA.  */
end_comment

begin_comment
comment|/* SVG loading file filter for the GIMP  * -Dom Lachowicz<cinamod@hotmail.com> 2003  *  * TODO:  *  image preview  */
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
file|<librsvg/rsvg.h>
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

begin_define
DECL|macro|VERSION
define|#
directive|define
name|VERSION
value|"2.4.0"
end_define

begin_typedef
typedef|typedef
struct|struct
DECL|struct|__anon29149a990108
block|{
DECL|member|scale
name|gdouble
name|scale
decl_stmt|;
DECL|typedef|SvgLoadVals
block|}
name|SvgLoadVals
typedef|;
end_typedef

begin_decl_stmt
DECL|variable|load_vals
specifier|static
name|SvgLoadVals
name|load_vals
init|=
block|{
literal|1.0
comment|/* scale */
block|}
decl_stmt|;
end_decl_stmt

begin_typedef
typedef|typedef
struct|struct
DECL|struct|__anon29149a990208
block|{
DECL|member|run
name|gboolean
name|run
decl_stmt|;
DECL|typedef|SvgLoadInterface
block|}
name|SvgLoadInterface
typedef|;
end_typedef

begin_decl_stmt
DECL|variable|load_interface
specifier|static
name|SvgLoadInterface
name|load_interface
init|=
block|{
name|FALSE
block|}
decl_stmt|;
end_decl_stmt

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
name|gboolean
name|load_dialog
parameter_list|(
specifier|const
name|gchar
modifier|*
name|filename
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
name|load_setargs_args
index|[]
init|=
block|{
block|{
name|GIMP_PDB_FLOAT
block|,
literal|"scale"
block|,
literal|"Scale in which to load image"
block|}
block|}
decl_stmt|;
name|gimp_install_procedure
argument_list|(
literal|"file_svg_load"
argument_list|,
literal|"Loads files in the SVG file format"
argument_list|,
literal|"Loads files in the SVG file format"
argument_list|,
literal|"Dom Lachowicz<cinamod@hotmail.com>"
argument_list|,
literal|"Dom Lachowicz<cinamod@hotmail.com>"
argument_list|,
literal|"(c) 2003 - "
name|VERSION
argument_list|,
literal|"<Load>/SVG"
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
literal|"file_svg_load_setargs"
argument_list|,
literal|"set additional parameters for the procedure file_svg_load"
argument_list|,
literal|"set additional parameters for the procedure file_svg_load"
argument_list|,
literal|"Dom Lachowicz<cinamod@hotmail.com>"
argument_list|,
literal|"Dom Lachowicz"
argument_list|,
literal|"2003"
argument_list|,
name|NULL
argument_list|,
name|NULL
argument_list|,
name|GIMP_PLUGIN
argument_list|,
name|G_N_ELEMENTS
argument_list|(
name|load_setargs_args
argument_list|)
argument_list|,
literal|0
argument_list|,
name|load_setargs_args
argument_list|,
name|NULL
argument_list|)
expr_stmt|;
name|gimp_register_magic_load_handler
argument_list|(
literal|"file_svg_load"
argument_list|,
literal|"svg"
argument_list|,
literal|""
argument_list|,
literal|"0,string,<?xml,0,string,<svg"
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
comment|/* MUST call this before any RSVG funcs */
name|g_type_init
argument_list|()
expr_stmt|;
if|if
condition|(
name|strcmp
argument_list|(
name|name
argument_list|,
literal|"file_svg_load"
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
name|GIMP_RUN_INTERACTIVE
case|:
name|gimp_get_data
argument_list|(
literal|"file_svg_load"
argument_list|,
operator|&
name|load_vals
argument_list|)
expr_stmt|;
if|if
condition|(
operator|!
name|load_dialog
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
condition|)
name|status
operator|=
name|GIMP_PDB_CANCEL
expr_stmt|;
break|break;
case|case
name|GIMP_RUN_NONINTERACTIVE
case|:
name|gimp_get_data
argument_list|(
literal|"file_svg_load"
argument_list|,
operator|&
name|load_vals
argument_list|)
expr_stmt|;
break|break;
case|case
name|GIMP_RUN_WITH_LAST_VALS
case|:
name|gimp_get_data
argument_list|(
literal|"file_svg_load"
argument_list|,
operator|&
name|load_vals
argument_list|)
expr_stmt|;
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
name|load_vals
operator|.
name|scale
operator|=
name|CLAMP
argument_list|(
name|load_vals
operator|.
name|scale
argument_list|,
literal|0.01
argument_list|,
literal|100.0
argument_list|)
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
name|gimp_set_data
argument_list|(
literal|"file_svg_load"
argument_list|,
operator|&
name|load_vals
argument_list|,
sizeof|sizeof
argument_list|(
name|load_vals
argument_list|)
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
name|GdkPixbuf
modifier|*
DECL|function|load_rsvg_pixbuf (const gchar * filename,GError ** error)
name|load_rsvg_pixbuf
parameter_list|(
specifier|const
name|gchar
modifier|*
name|filename
parameter_list|,
name|GError
modifier|*
modifier|*
name|error
parameter_list|)
block|{
name|RsvgHandle
modifier|*
name|handle
decl_stmt|;
name|GdkPixbuf
modifier|*
name|pixbuf
init|=
name|NULL
decl_stmt|;
name|GIOChannel
modifier|*
name|io
decl_stmt|;
name|GIOStatus
name|status
init|=
name|G_IO_STATUS_NORMAL
decl_stmt|;
name|gboolean
name|success
init|=
name|TRUE
decl_stmt|;
name|io
operator|=
name|g_io_channel_new_file
argument_list|(
name|filename
argument_list|,
literal|"r"
argument_list|,
name|error
argument_list|)
expr_stmt|;
if|if
condition|(
operator|!
name|io
condition|)
return|return
name|NULL
return|;
name|handle
operator|=
name|rsvg_handle_new
argument_list|()
expr_stmt|;
while|while
condition|(
name|success
operator|&&
name|status
operator|!=
name|G_IO_STATUS_EOF
condition|)
block|{
name|guchar
name|buf
index|[
literal|4096
index|]
decl_stmt|;
name|gsize
name|len
decl_stmt|;
name|status
operator|=
name|g_io_channel_read_chars
argument_list|(
name|io
argument_list|,
name|buf
argument_list|,
sizeof|sizeof
argument_list|(
name|buf
argument_list|)
argument_list|,
operator|&
name|len
argument_list|,
name|error
argument_list|)
expr_stmt|;
switch|switch
condition|(
name|status
condition|)
block|{
case|case
name|G_IO_STATUS_ERROR
case|:
name|success
operator|=
name|FALSE
expr_stmt|;
break|break;
case|case
name|G_IO_STATUS_EOF
case|:
name|success
operator|=
name|rsvg_handle_close
argument_list|(
name|handle
argument_list|,
name|error
argument_list|)
expr_stmt|;
break|break;
case|case
name|G_IO_STATUS_NORMAL
case|:
name|success
operator|=
name|rsvg_handle_write
argument_list|(
name|handle
argument_list|,
name|buf
argument_list|,
name|len
argument_list|,
name|error
argument_list|)
expr_stmt|;
break|break;
case|case
name|G_IO_STATUS_AGAIN
case|:
break|break;
block|}
block|}
name|g_io_channel_unref
argument_list|(
name|io
argument_list|)
expr_stmt|;
if|if
condition|(
name|success
condition|)
name|pixbuf
operator|=
name|rsvg_handle_get_pixbuf
argument_list|(
name|handle
argument_list|)
expr_stmt|;
name|rsvg_handle_free
argument_list|(
name|handle
argument_list|)
expr_stmt|;
return|return
name|pixbuf
return|;
block|}
end_function

begin_comment
comment|/*  * 'load_image()' - Load a SVG image into a new image window.  */
end_comment

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
name|gint32
name|image
decl_stmt|;
name|gint32
name|layer
decl_stmt|;
name|GimpDrawable
modifier|*
name|drawable
decl_stmt|;
name|GimpPixelRgn
name|rgn
decl_stmt|;
name|GdkPixbuf
modifier|*
name|pixbuf
decl_stmt|;
name|gchar
modifier|*
name|status
decl_stmt|;
name|gchar
modifier|*
name|pixels
decl_stmt|;
name|gint
name|width
decl_stmt|;
name|gint
name|height
decl_stmt|;
name|gint
name|rowstride
decl_stmt|;
name|gint
name|bpp
decl_stmt|;
name|gpointer
name|pr
decl_stmt|;
name|GError
modifier|*
name|error
init|=
name|NULL
decl_stmt|;
name|pixbuf
operator|=
name|load_rsvg_pixbuf
argument_list|(
name|filename
argument_list|,
operator|&
name|error
argument_list|)
expr_stmt|;
if|if
condition|(
operator|!
name|pixbuf
condition|)
block|{
name|g_message
argument_list|(
name|_
argument_list|(
literal|"Can't open '%s':\n"
literal|"%s"
argument_list|)
argument_list|,
name|filename
argument_list|,
name|error
operator|->
name|message
argument_list|)
expr_stmt|;
name|gimp_quit
argument_list|()
expr_stmt|;
block|}
name|status
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
name|status
argument_list|)
expr_stmt|;
name|g_free
argument_list|(
name|status
argument_list|)
expr_stmt|;
name|width
operator|=
name|gdk_pixbuf_get_width
argument_list|(
name|pixbuf
argument_list|)
expr_stmt|;
name|height
operator|=
name|gdk_pixbuf_get_height
argument_list|(
name|pixbuf
argument_list|)
expr_stmt|;
name|image
operator|=
name|gimp_image_new
argument_list|(
name|width
argument_list|,
name|height
argument_list|,
name|GIMP_RGB
argument_list|)
expr_stmt|;
name|gimp_image_set_filename
argument_list|(
name|image
argument_list|,
name|filename
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
literal|"Rendered SVG"
argument_list|)
argument_list|,
name|width
argument_list|,
name|height
argument_list|,
name|GIMP_RGBA_IMAGE
argument_list|,
literal|100
argument_list|,
name|GIMP_NORMAL_MODE
argument_list|)
expr_stmt|;
name|drawable
operator|=
name|gimp_drawable_get
argument_list|(
name|layer
argument_list|)
expr_stmt|;
name|gimp_pixel_rgn_init
argument_list|(
operator|&
name|rgn
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
name|TRUE
argument_list|,
name|FALSE
argument_list|)
expr_stmt|;
name|rowstride
operator|=
name|gdk_pixbuf_get_rowstride
argument_list|(
name|pixbuf
argument_list|)
expr_stmt|;
name|bpp
operator|=
name|gdk_pixbuf_get_n_channels
argument_list|(
name|pixbuf
argument_list|)
expr_stmt|;
name|pixels
operator|=
name|gdk_pixbuf_get_pixels
argument_list|(
name|pixbuf
argument_list|)
expr_stmt|;
name|g_assert
argument_list|(
name|bpp
operator|==
name|rgn
operator|.
name|bpp
argument_list|)
expr_stmt|;
for|for
control|(
name|pr
operator|=
name|gimp_pixel_rgns_register
argument_list|(
literal|1
argument_list|,
operator|&
name|rgn
argument_list|)
init|;
name|pr
operator|!=
name|NULL
condition|;
name|pr
operator|=
name|gimp_pixel_rgns_process
argument_list|(
name|pr
argument_list|)
control|)
block|{
specifier|const
name|guchar
modifier|*
name|src
decl_stmt|;
name|guchar
modifier|*
name|dest
decl_stmt|;
name|gint
name|y
decl_stmt|;
name|src
operator|=
name|pixels
operator|+
name|rgn
operator|.
name|y
operator|*
name|rowstride
operator|+
name|rgn
operator|.
name|x
operator|*
name|bpp
expr_stmt|;
name|dest
operator|=
name|rgn
operator|.
name|data
expr_stmt|;
for|for
control|(
name|y
operator|=
literal|0
init|;
name|y
operator|<
name|rgn
operator|.
name|h
condition|;
name|y
operator|++
control|)
block|{
name|memcpy
argument_list|(
name|dest
argument_list|,
name|src
argument_list|,
name|rgn
operator|.
name|w
operator|*
name|rgn
operator|.
name|bpp
argument_list|)
expr_stmt|;
name|src
operator|+=
name|rowstride
expr_stmt|;
name|dest
operator|+=
name|rgn
operator|.
name|rowstride
expr_stmt|;
block|}
block|}
name|gimp_drawable_detach
argument_list|(
name|drawable
argument_list|)
expr_stmt|;
name|g_object_unref
argument_list|(
name|pixbuf
argument_list|)
expr_stmt|;
name|gimp_progress_update
argument_list|(
literal|1.0
argument_list|)
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
return|return
name|image
return|;
block|}
end_function

begin_function
specifier|static
name|void
DECL|function|load_ok_callback (GtkWidget * widget,gpointer data)
name|load_ok_callback
parameter_list|(
name|GtkWidget
modifier|*
name|widget
parameter_list|,
name|gpointer
name|data
parameter_list|)
block|{
name|load_interface
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
name|gboolean
DECL|function|load_dialog (const gchar * filename)
name|load_dialog
parameter_list|(
specifier|const
name|gchar
modifier|*
name|filename
parameter_list|)
block|{
name|GtkWidget
modifier|*
name|dialog
decl_stmt|;
name|GtkWidget
modifier|*
name|frame
decl_stmt|;
name|GtkWidget
modifier|*
name|vbox
decl_stmt|;
name|GtkWidget
modifier|*
name|label
decl_stmt|;
name|GtkWidget
modifier|*
name|table
decl_stmt|;
name|GtkWidget
modifier|*
name|slider
decl_stmt|;
name|GtkObject
modifier|*
name|adj
decl_stmt|;
name|gimp_ui_init
argument_list|(
literal|"svg"
argument_list|,
name|FALSE
argument_list|)
expr_stmt|;
name|dialog
operator|=
name|gimp_dialog_new
argument_list|(
name|_
argument_list|(
literal|"Load SVG"
argument_list|)
argument_list|,
literal|"svg"
argument_list|,
name|NULL
argument_list|,
name|NULL
argument_list|,
name|GTK_WIN_POS_MOUSE
argument_list|,
name|FALSE
argument_list|,
name|TRUE
argument_list|,
name|FALSE
argument_list|,
name|GTK_STOCK_CANCEL
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
name|GTK_STOCK_OK
argument_list|,
name|load_ok_callback
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
name|NULL
argument_list|)
expr_stmt|;
name|g_signal_connect
argument_list|(
name|dialog
argument_list|,
literal|"destroy"
argument_list|,
name|G_CALLBACK
argument_list|(
name|gtk_main_quit
argument_list|)
argument_list|,
name|NULL
argument_list|)
expr_stmt|;
comment|/* Rendering */
name|frame
operator|=
name|gtk_frame_new
argument_list|(
name|g_strdup_printf
argument_list|(
name|_
argument_list|(
literal|"Rendering %s"
argument_list|)
argument_list|,
name|filename
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
literal|6
argument_list|)
expr_stmt|;
name|gtk_frame_set_shadow_type
argument_list|(
name|GTK_FRAME
argument_list|(
name|frame
argument_list|)
argument_list|,
name|GTK_SHADOW_ETCHED_IN
argument_list|)
expr_stmt|;
name|gtk_box_pack_start
argument_list|(
name|GTK_BOX
argument_list|(
name|GTK_DIALOG
argument_list|(
name|dialog
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
name|vbox
operator|=
name|gtk_vbox_new
argument_list|(
name|FALSE
argument_list|,
literal|4
argument_list|)
expr_stmt|;
name|gtk_container_set_border_width
argument_list|(
name|GTK_CONTAINER
argument_list|(
name|vbox
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
name|vbox
argument_list|)
expr_stmt|;
comment|/* Scale label */
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
name|gtk_box_pack_start
argument_list|(
name|GTK_BOX
argument_list|(
name|vbox
argument_list|)
argument_list|,
name|table
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
name|table
argument_list|)
expr_stmt|;
name|label
operator|=
name|gtk_label_new
argument_list|(
name|_
argument_list|(
literal|"Scale (log 2):"
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
literal|1.0
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
comment|/* Scale slider */
name|adj
operator|=
name|gtk_adjustment_new
argument_list|(
literal|0.0
argument_list|,
operator|-
literal|2.0
argument_list|,
literal|2.0
argument_list|,
literal|0.2
argument_list|,
literal|0.2
argument_list|,
literal|0.0
argument_list|)
expr_stmt|;
name|slider
operator|=
name|gtk_hscale_new
argument_list|(
name|GTK_ADJUSTMENT
argument_list|(
name|adj
argument_list|)
argument_list|)
expr_stmt|;
name|gtk_table_attach
argument_list|(
name|GTK_TABLE
argument_list|(
name|table
argument_list|)
argument_list|,
name|slider
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
name|gtk_scale_set_value_pos
argument_list|(
name|GTK_SCALE
argument_list|(
name|slider
argument_list|)
argument_list|,
name|GTK_POS_TOP
argument_list|)
expr_stmt|;
name|gtk_range_set_update_policy
argument_list|(
name|GTK_RANGE
argument_list|(
name|slider
argument_list|)
argument_list|,
name|GTK_UPDATE_DELAYED
argument_list|)
expr_stmt|;
name|gtk_widget_show
argument_list|(
name|slider
argument_list|)
expr_stmt|;
comment|/* Temporarily disabled */
name|gtk_widget_set_sensitive
argument_list|(
name|slider
argument_list|,
name|FALSE
argument_list|)
expr_stmt|;
name|gtk_widget_show
argument_list|(
name|vbox
argument_list|)
expr_stmt|;
name|gtk_widget_show
argument_list|(
name|frame
argument_list|)
expr_stmt|;
name|gtk_widget_show
argument_list|(
name|dialog
argument_list|)
expr_stmt|;
name|gtk_main
argument_list|()
expr_stmt|;
return|return
name|load_interface
operator|.
name|run
return|;
block|}
end_function

end_unit

