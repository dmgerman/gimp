begin_unit|revision:0.9.5;language:C;cregit-version:0.0.1
begin_comment
comment|/* The GIMP -- an image manipulation program  * Copyright (C) 1995-1997 Spencer Kimball and Peter Mattis  *  * GIMP Plug-in for Windows Icon files.  * Copyright (C) 2002 Christian Kreibich<christian@whoop.org>.  *  * This program is free software; you can redistribute it and/or modify  * it under the terms of the GNU General Public License as published by  * the Free Software Foundation; either version 2 of the License, or  * (at your option) any later version.  *  * This program is distributed in the hope that it will be useful,  * but WITHOUT ANY WARRANTY; without even the implied warranty of  * MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the  * GNU General Public License for more details.  *  * You should have received a copy of the GNU General Public License  * along with this program; if not, write to the Free Software  * Foundation, Inc., 59 Temple Place - Suite 330, Boston, MA 02111-1307, USA.  */
end_comment

begin_include
include|#
directive|include
file|<config.h>
end_include

begin_include
include|#
directive|include
file|<stdio.h>
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

begin_define
DECL|macro|ICO_DBG
define|#
directive|define
name|ICO_DBG
end_define

begin_include
include|#
directive|include
file|"icodialog.h"
end_include

begin_include
include|#
directive|include
file|"main.h"
end_include

begin_include
include|#
directive|include
file|"libgimp/stdplugins-intl.h"
end_include

begin_function_decl
specifier|static
name|GtkWidget
modifier|*
name|ico_preview_new
parameter_list|(
name|gint32
name|layer
parameter_list|)
function_decl|;
end_function_decl

begin_function_decl
specifier|static
name|void
name|ico_fill_preview_with_thumb
parameter_list|(
name|GtkWidget
modifier|*
name|widget
parameter_list|,
name|gint32
name|drawable_ID
parameter_list|)
function_decl|;
end_function_decl

begin_function_decl
specifier|static
name|void
name|combo_bpp_changed
parameter_list|(
name|GtkWidget
modifier|*
name|combo
parameter_list|,
name|GObject
modifier|*
name|hbox
parameter_list|)
function_decl|;
end_function_decl

begin_function
specifier|static
name|GtkWidget
modifier|*
DECL|function|ico_preview_new (gint32 layer)
name|ico_preview_new
parameter_list|(
name|gint32
name|layer
parameter_list|)
block|{
name|GtkWidget
modifier|*
name|icon_preview
decl_stmt|;
name|icon_preview
operator|=
name|gimp_preview_area_new
argument_list|()
expr_stmt|;
name|ico_fill_preview_with_thumb
argument_list|(
name|icon_preview
argument_list|,
name|layer
argument_list|)
expr_stmt|;
return|return
name|icon_preview
return|;
block|}
end_function

begin_function
specifier|static
name|void
DECL|function|ico_fill_preview_with_thumb (GtkWidget * widget,gint32 drawable_ID)
name|ico_fill_preview_with_thumb
parameter_list|(
name|GtkWidget
modifier|*
name|widget
parameter_list|,
name|gint32
name|drawable_ID
parameter_list|)
block|{
name|guchar
modifier|*
name|drawable_data
decl_stmt|;
name|gint
name|bpp
decl_stmt|;
name|gint
name|width
decl_stmt|;
name|gint
name|height
decl_stmt|;
name|width
operator|=
name|gimp_drawable_width
argument_list|(
name|drawable_ID
argument_list|)
expr_stmt|;
name|height
operator|=
name|gimp_drawable_height
argument_list|(
name|drawable_ID
argument_list|)
expr_stmt|;
name|bpp
operator|=
literal|0
expr_stmt|;
comment|/* Only returned */
if|if
condition|(
name|width
operator|>
literal|128
condition|)
name|width
operator|=
literal|128
expr_stmt|;
if|if
condition|(
name|height
operator|>
literal|128
condition|)
name|height
operator|=
literal|128
expr_stmt|;
name|drawable_data
operator|=
name|gimp_drawable_get_thumbnail_data
argument_list|(
name|drawable_ID
argument_list|,
operator|&
name|width
argument_list|,
operator|&
name|height
argument_list|,
operator|&
name|bpp
argument_list|)
expr_stmt|;
if|if
condition|(
name|width
operator|<
literal|1
operator|||
name|height
operator|<
literal|1
condition|)
return|return;
name|gtk_widget_set_size_request
argument_list|(
name|widget
argument_list|,
name|width
argument_list|,
name|height
argument_list|)
expr_stmt|;
name|GIMP_PREVIEW_AREA
argument_list|(
name|widget
argument_list|)
operator|->
name|width
operator|=
name|width
expr_stmt|;
name|GIMP_PREVIEW_AREA
argument_list|(
name|widget
argument_list|)
operator|->
name|height
operator|=
name|height
expr_stmt|;
name|gimp_preview_area_draw
argument_list|(
name|GIMP_PREVIEW_AREA
argument_list|(
name|widget
argument_list|)
argument_list|,
literal|0
argument_list|,
literal|0
argument_list|,
name|width
argument_list|,
name|height
argument_list|,
name|gimp_drawable_type
argument_list|(
name|drawable_ID
argument_list|)
argument_list|,
name|drawable_data
argument_list|,
name|bpp
operator|*
name|width
argument_list|)
expr_stmt|;
name|g_free
argument_list|(
name|drawable_data
argument_list|)
expr_stmt|;
block|}
end_function

begin_comment
comment|/* This function creates and returns an hbox for an icon,    which then gets added to the dialog's main vbox. */
end_comment

begin_function
specifier|static
name|GtkWidget
modifier|*
DECL|function|ico_create_icon_hbox (GtkWidget * icon_preview,gint32 layer,gint layer_num)
name|ico_create_icon_hbox
parameter_list|(
name|GtkWidget
modifier|*
name|icon_preview
parameter_list|,
name|gint32
name|layer
parameter_list|,
name|gint
name|layer_num
parameter_list|)
block|{
name|GtkWidget
modifier|*
name|hbox
decl_stmt|;
name|GtkWidget
modifier|*
name|alignment
decl_stmt|;
name|GtkWidget
modifier|*
name|combo
decl_stmt|;
name|hbox
operator|=
name|gtk_hbox_new
argument_list|(
name|FALSE
argument_list|,
literal|6
argument_list|)
expr_stmt|;
name|alignment
operator|=
name|gtk_alignment_new
argument_list|(
literal|0.5
argument_list|,
literal|0.5
argument_list|,
literal|0
argument_list|,
literal|0
argument_list|)
expr_stmt|;
name|gtk_box_pack_start
argument_list|(
name|GTK_BOX
argument_list|(
name|hbox
argument_list|)
argument_list|,
name|alignment
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
name|alignment
argument_list|)
expr_stmt|;
comment|/* To make life easier for the callbacks, we store the      layer's ID and stacking number with the hbox. */
name|g_object_set_data
argument_list|(
name|G_OBJECT
argument_list|(
name|hbox
argument_list|)
argument_list|,
literal|"icon_layer"
argument_list|,
name|GINT_TO_POINTER
argument_list|(
name|layer
argument_list|)
argument_list|)
expr_stmt|;
name|g_object_set_data
argument_list|(
name|G_OBJECT
argument_list|(
name|hbox
argument_list|)
argument_list|,
literal|"icon_layer_num"
argument_list|,
name|GINT_TO_POINTER
argument_list|(
name|layer_num
argument_list|)
argument_list|)
expr_stmt|;
name|g_object_set_data
argument_list|(
name|G_OBJECT
argument_list|(
name|hbox
argument_list|)
argument_list|,
literal|"icon_preview"
argument_list|,
name|icon_preview
argument_list|)
expr_stmt|;
name|gtk_container_add
argument_list|(
name|GTK_CONTAINER
argument_list|(
name|alignment
argument_list|)
argument_list|,
name|icon_preview
argument_list|)
expr_stmt|;
name|gtk_widget_show
argument_list|(
name|icon_preview
argument_list|)
expr_stmt|;
name|combo
operator|=
name|gimp_int_combo_box_new
argument_list|(
name|_
argument_list|(
literal|"1 bpp, 1-bit alpha, 2-slot palette"
argument_list|)
argument_list|,
literal|1
argument_list|,
name|_
argument_list|(
literal|"4 bpp, 1-bit alpha, 16-slot palette"
argument_list|)
argument_list|,
literal|4
argument_list|,
name|_
argument_list|(
literal|"8 bpp, 1-bit alpha, 256-slot palette"
argument_list|)
argument_list|,
literal|8
argument_list|,
name|_
argument_list|(
literal|"32 bpp, 8-bit alpha, no palette"
argument_list|)
argument_list|,
literal|32
argument_list|,
name|NULL
argument_list|)
expr_stmt|;
name|gimp_int_combo_box_set_active
argument_list|(
name|GIMP_INT_COMBO_BOX
argument_list|(
name|combo
argument_list|)
argument_list|,
literal|32
argument_list|)
expr_stmt|;
name|g_signal_connect
argument_list|(
name|combo
argument_list|,
literal|"changed"
argument_list|,
name|G_CALLBACK
argument_list|(
name|combo_bpp_changed
argument_list|)
argument_list|,
name|hbox
argument_list|)
expr_stmt|;
name|g_object_set_data
argument_list|(
name|G_OBJECT
argument_list|(
name|hbox
argument_list|)
argument_list|,
literal|"icon_menu"
argument_list|,
name|combo
argument_list|)
expr_stmt|;
name|gtk_box_pack_start
argument_list|(
name|GTK_BOX
argument_list|(
name|hbox
argument_list|)
argument_list|,
name|combo
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
name|combo
argument_list|)
expr_stmt|;
return|return
name|hbox
return|;
block|}
end_function

begin_function
name|GtkWidget
modifier|*
DECL|function|ico_specs_dialog_new (gint num_layers)
name|ico_specs_dialog_new
parameter_list|(
name|gint
name|num_layers
parameter_list|)
block|{
name|GtkWidget
modifier|*
name|dialog
decl_stmt|;
name|GtkWidget
modifier|*
name|vbox
decl_stmt|;
name|GtkWidget
modifier|*
name|frame
decl_stmt|;
name|GtkWidget
modifier|*
name|scrolledwindow
decl_stmt|;
name|gint
modifier|*
name|icon_depths
decl_stmt|,
name|i
decl_stmt|;
name|dialog
operator|=
name|gimp_dialog_new
argument_list|(
name|_
argument_list|(
literal|"GIMP Windows Icon Plugin"
argument_list|)
argument_list|,
literal|"winicon"
argument_list|,
name|NULL
argument_list|,
literal|0
argument_list|,
name|gimp_standard_help_func
argument_list|,
literal|"plug-in-winicon"
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
name|gtk_dialog_set_alternative_button_order
argument_list|(
name|GTK_DIALOG
argument_list|(
name|dialog
argument_list|)
argument_list|,
name|GTK_RESPONSE_OK
argument_list|,
name|GTK_RESPONSE_CANCEL
argument_list|,
operator|-
literal|1
argument_list|)
expr_stmt|;
comment|/* We store an array that holds each icon's requested bit depth      with the dialog. It's queried when the dialog is closed so the      save routine knows what colormaps etc to generate in the saved      file. We store twice the number necessary because in the second      set, the color depths that are automatically suggested are stored      for later comparison.   */
name|icon_depths
operator|=
name|g_new
argument_list|(
name|gint
argument_list|,
literal|2
operator|*
name|num_layers
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
literal|2
operator|*
name|num_layers
condition|;
name|i
operator|++
control|)
name|icon_depths
index|[
name|i
index|]
operator|=
literal|32
expr_stmt|;
name|g_object_set_data
argument_list|(
name|G_OBJECT
argument_list|(
name|dialog
argument_list|)
argument_list|,
literal|"icon_depths"
argument_list|,
name|icon_depths
argument_list|)
expr_stmt|;
name|frame
operator|=
name|gimp_frame_new
argument_list|(
name|_
argument_list|(
literal|"Icon details"
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
name|gtk_widget_show
argument_list|(
name|frame
argument_list|)
expr_stmt|;
name|scrolledwindow
operator|=
name|gtk_scrolled_window_new
argument_list|(
name|NULL
argument_list|,
name|NULL
argument_list|)
expr_stmt|;
name|gtk_scrolled_window_set_policy
argument_list|(
name|GTK_SCROLLED_WINDOW
argument_list|(
name|scrolledwindow
argument_list|)
argument_list|,
name|GTK_POLICY_AUTOMATIC
argument_list|,
name|GTK_POLICY_AUTOMATIC
argument_list|)
expr_stmt|;
name|gtk_container_add
argument_list|(
name|GTK_CONTAINER
argument_list|(
name|frame
argument_list|)
argument_list|,
name|scrolledwindow
argument_list|)
expr_stmt|;
name|gtk_widget_show
argument_list|(
name|scrolledwindow
argument_list|)
expr_stmt|;
name|vbox
operator|=
name|gtk_vbox_new
argument_list|(
name|FALSE
argument_list|,
literal|6
argument_list|)
expr_stmt|;
name|gtk_container_set_border_width
argument_list|(
name|GTK_CONTAINER
argument_list|(
name|vbox
argument_list|)
argument_list|,
literal|6
argument_list|)
expr_stmt|;
name|g_object_set_data
argument_list|(
name|G_OBJECT
argument_list|(
name|dialog
argument_list|)
argument_list|,
literal|"icons_vbox"
argument_list|,
name|vbox
argument_list|)
expr_stmt|;
name|gtk_scrolled_window_add_with_viewport
argument_list|(
name|GTK_SCROLLED_WINDOW
argument_list|(
name|scrolledwindow
argument_list|)
argument_list|,
name|vbox
argument_list|)
expr_stmt|;
name|gtk_widget_show
argument_list|(
name|vbox
argument_list|)
expr_stmt|;
return|return
name|dialog
return|;
block|}
end_function

begin_function
specifier|static
name|GtkWidget
modifier|*
DECL|function|ico_specs_dialog_get_layer_preview (GtkWidget * dialog,gint32 layer)
name|ico_specs_dialog_get_layer_preview
parameter_list|(
name|GtkWidget
modifier|*
name|dialog
parameter_list|,
name|gint32
name|layer
parameter_list|)
block|{
name|GtkWidget
modifier|*
name|preview
decl_stmt|;
name|GtkWidget
modifier|*
name|icon_hbox
decl_stmt|;
name|gchar
name|key
index|[
name|MAXLEN
index|]
decl_stmt|;
name|g_snprintf
argument_list|(
name|key
argument_list|,
name|MAXLEN
argument_list|,
literal|"layer_%i_hbox"
argument_list|,
name|layer
argument_list|)
expr_stmt|;
name|icon_hbox
operator|=
name|g_object_get_data
argument_list|(
name|G_OBJECT
argument_list|(
name|dialog
argument_list|)
argument_list|,
name|key
argument_list|)
expr_stmt|;
if|if
condition|(
operator|!
name|icon_hbox
condition|)
block|{
name|D
argument_list|(
operator|(
literal|"Something's wrong -- couldn't look up hbox by layer ID\n"
operator|)
argument_list|)
expr_stmt|;
return|return
name|NULL
return|;
block|}
name|preview
operator|=
name|g_object_get_data
argument_list|(
name|G_OBJECT
argument_list|(
name|icon_hbox
argument_list|)
argument_list|,
literal|"icon_preview"
argument_list|)
expr_stmt|;
if|if
condition|(
operator|!
name|icon_hbox
condition|)
block|{
name|D
argument_list|(
operator|(
literal|"Something's wrong -- couldn't look up preview from hbox\n"
operator|)
argument_list|)
expr_stmt|;
return|return
name|NULL
return|;
block|}
return|return
name|preview
return|;
block|}
end_function

begin_function
name|void
DECL|function|ico_specs_dialog_add_icon (GtkWidget * dialog,gint32 layer,gint layer_num)
name|ico_specs_dialog_add_icon
parameter_list|(
name|GtkWidget
modifier|*
name|dialog
parameter_list|,
name|gint32
name|layer
parameter_list|,
name|gint
name|layer_num
parameter_list|)
block|{
name|GtkWidget
modifier|*
name|vbox
decl_stmt|;
name|GtkWidget
modifier|*
name|hbox
decl_stmt|;
name|GtkWidget
modifier|*
name|preview
decl_stmt|;
name|gchar
name|key
index|[
name|MAXLEN
index|]
decl_stmt|;
name|vbox
operator|=
name|g_object_get_data
argument_list|(
name|G_OBJECT
argument_list|(
name|dialog
argument_list|)
argument_list|,
literal|"icons_vbox"
argument_list|)
expr_stmt|;
name|preview
operator|=
name|ico_preview_new
argument_list|(
name|layer
argument_list|)
expr_stmt|;
name|hbox
operator|=
name|ico_create_icon_hbox
argument_list|(
name|preview
argument_list|,
name|layer
argument_list|,
name|layer_num
argument_list|)
expr_stmt|;
name|gtk_box_pack_start
argument_list|(
name|GTK_BOX
argument_list|(
name|vbox
argument_list|)
argument_list|,
name|hbox
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
name|hbox
argument_list|)
expr_stmt|;
comment|/* Let's make the hbox accessible through the layer ID */
name|g_snprintf
argument_list|(
name|key
argument_list|,
name|MAXLEN
argument_list|,
literal|"layer_%i_hbox"
argument_list|,
name|layer
argument_list|)
expr_stmt|;
name|g_object_set_data
argument_list|(
name|G_OBJECT
argument_list|(
name|dialog
argument_list|)
argument_list|,
name|key
argument_list|,
name|hbox
argument_list|)
expr_stmt|;
block|}
end_function

begin_function
name|void
DECL|function|ico_specs_dialog_update_icon_preview (GtkWidget * dialog,gint32 layer,gint bpp)
name|ico_specs_dialog_update_icon_preview
parameter_list|(
name|GtkWidget
modifier|*
name|dialog
parameter_list|,
name|gint32
name|layer
parameter_list|,
name|gint
name|bpp
parameter_list|)
block|{
name|GtkWidget
modifier|*
name|preview
decl_stmt|;
name|GimpPixelRgn
name|src_pixel_rgn
decl_stmt|,
name|dst_pixel_rgn
decl_stmt|;
name|gint32
name|tmp_image
decl_stmt|;
name|gint32
name|tmp_layer
decl_stmt|;
name|gint
name|w
decl_stmt|,
name|h
decl_stmt|;
name|guchar
modifier|*
name|buffer
decl_stmt|;
name|gboolean
name|result
decl_stmt|;
name|GimpDrawable
modifier|*
name|drawable
init|=
name|gimp_drawable_get
argument_list|(
name|layer
argument_list|)
decl_stmt|;
name|GimpDrawable
modifier|*
name|tmp
decl_stmt|;
name|tmp_image
operator|=
name|gimp_image_new
argument_list|(
name|gimp_drawable_width
argument_list|(
name|layer
argument_list|)
argument_list|,
name|gimp_drawable_height
argument_list|(
name|layer
argument_list|)
argument_list|,
name|GIMP_RGB
argument_list|)
expr_stmt|;
name|w
operator|=
name|gimp_drawable_width
argument_list|(
name|layer
argument_list|)
expr_stmt|;
name|h
operator|=
name|gimp_drawable_height
argument_list|(
name|layer
argument_list|)
expr_stmt|;
name|tmp_layer
operator|=
name|gimp_layer_new
argument_list|(
name|tmp_image
argument_list|,
literal|"temporary"
argument_list|,
name|w
argument_list|,
name|h
argument_list|,
name|GIMP_RGBA_IMAGE
argument_list|,
literal|100
argument_list|,
name|GIMP_NORMAL_MODE
argument_list|)
expr_stmt|;
name|gimp_image_add_layer
argument_list|(
name|tmp_image
argument_list|,
name|tmp_layer
argument_list|,
literal|0
argument_list|)
expr_stmt|;
name|tmp
operator|=
name|gimp_drawable_get
argument_list|(
name|tmp_layer
argument_list|)
expr_stmt|;
name|gimp_pixel_rgn_init
argument_list|(
operator|&
name|src_pixel_rgn
argument_list|,
name|drawable
argument_list|,
literal|0
argument_list|,
literal|0
argument_list|,
name|w
argument_list|,
name|h
argument_list|,
name|FALSE
argument_list|,
name|FALSE
argument_list|)
expr_stmt|;
name|gimp_pixel_rgn_init
argument_list|(
operator|&
name|dst_pixel_rgn
argument_list|,
name|tmp
argument_list|,
literal|0
argument_list|,
literal|0
argument_list|,
name|w
argument_list|,
name|h
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
name|w
operator|*
name|h
operator|*
literal|4
argument_list|)
expr_stmt|;
name|gimp_pixel_rgn_get_rect
argument_list|(
operator|&
name|src_pixel_rgn
argument_list|,
name|buffer
argument_list|,
literal|0
argument_list|,
literal|0
argument_list|,
name|w
argument_list|,
name|h
argument_list|)
expr_stmt|;
name|gimp_pixel_rgn_set_rect
argument_list|(
operator|&
name|dst_pixel_rgn
argument_list|,
name|buffer
argument_list|,
literal|0
argument_list|,
literal|0
argument_list|,
name|w
argument_list|,
name|h
argument_list|)
expr_stmt|;
name|gimp_drawable_detach
argument_list|(
name|tmp
argument_list|)
expr_stmt|;
name|gimp_drawable_detach
argument_list|(
name|drawable
argument_list|)
expr_stmt|;
if|if
condition|(
name|bpp
operator|<
literal|32
condition|)
block|{
name|result
operator|=
name|gimp_image_convert_indexed
argument_list|(
name|tmp_image
argument_list|,
name|GIMP_FS_DITHER
argument_list|,
name|GIMP_MAKE_PALETTE
argument_list|,
literal|1
operator|<<
name|bpp
argument_list|,
name|TRUE
argument_list|,
name|FALSE
argument_list|,
literal|"dummy"
argument_list|)
expr_stmt|;
block|}
name|gimp_image_delete
argument_list|(
name|tmp_image
argument_list|)
expr_stmt|;
name|preview
operator|=
name|ico_specs_dialog_get_layer_preview
argument_list|(
name|dialog
argument_list|,
name|layer
argument_list|)
expr_stmt|;
name|ico_fill_preview_with_thumb
argument_list|(
name|preview
argument_list|,
name|tmp_layer
argument_list|)
expr_stmt|;
name|gtk_widget_queue_draw
argument_list|(
name|preview
argument_list|)
expr_stmt|;
name|g_free
argument_list|(
name|buffer
argument_list|)
expr_stmt|;
block|}
end_function

begin_function
specifier|static
name|void
DECL|function|combo_bpp_changed (GtkWidget * combo,GObject * hbox)
name|combo_bpp_changed
parameter_list|(
name|GtkWidget
modifier|*
name|combo
parameter_list|,
name|GObject
modifier|*
name|hbox
parameter_list|)
block|{
name|GtkWidget
modifier|*
name|dialog
init|=
name|gtk_widget_get_toplevel
argument_list|(
name|combo
argument_list|)
decl_stmt|;
name|gint32
name|layer
decl_stmt|;
name|gint
name|layer_num
decl_stmt|;
name|gint
name|bpp
decl_stmt|;
name|gint
modifier|*
name|icon_depths
decl_stmt|;
name|gimp_int_combo_box_get_active
argument_list|(
name|GIMP_INT_COMBO_BOX
argument_list|(
name|combo
argument_list|)
argument_list|,
operator|&
name|bpp
argument_list|)
expr_stmt|;
name|icon_depths
operator|=
name|g_object_get_data
argument_list|(
name|G_OBJECT
argument_list|(
name|dialog
argument_list|)
argument_list|,
literal|"icon_depths"
argument_list|)
expr_stmt|;
if|if
condition|(
operator|!
name|icon_depths
condition|)
block|{
name|D
argument_list|(
operator|(
literal|"Something's wrong -- can't get icon_depths array from dialog\n"
operator|)
argument_list|)
expr_stmt|;
return|return;
block|}
name|layer
operator|=
name|GPOINTER_TO_INT
argument_list|(
name|g_object_get_data
argument_list|(
name|hbox
argument_list|,
literal|"icon_layer"
argument_list|)
argument_list|)
expr_stmt|;
name|layer_num
operator|=
name|GPOINTER_TO_INT
argument_list|(
name|g_object_get_data
argument_list|(
name|hbox
argument_list|,
literal|"icon_layer_num"
argument_list|)
argument_list|)
expr_stmt|;
comment|/* Update vector entry for later when we're actually saving,      and update the preview right away ... */
name|icon_depths
index|[
name|layer_num
index|]
operator|=
name|bpp
expr_stmt|;
name|ico_specs_dialog_update_icon_preview
argument_list|(
name|dialog
argument_list|,
name|layer
argument_list|,
name|bpp
argument_list|)
expr_stmt|;
block|}
end_function

end_unit

