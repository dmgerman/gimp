begin_unit|revision:0.9.5;language:C;cregit-version:0.0.1
begin_comment
comment|/* GIMP - The GNU Image Manipulation Program  * Copyright (C) 1995-1997 Spencer Kimball and Peter Mattis  *  * GIMP Plug-in for Windows Icon files.  * Copyright (C) 2002 Christian Kreibich<christian@whoop.org>.  *  * This program is free software: you can redistribute it and/or modify  * it under the terms of the GNU General Public License as published by  * the Free Software Foundation; either version 3 of the License, or  * (at your option) any later version.  *  * This program is distributed in the hope that it will be useful,  * but WITHOUT ANY WARRANTY; without even the implied warranty of  * MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the  * GNU General Public License for more details.  *  * You should have received a copy of the GNU General Public License  * along with this program.  If not, see<http://www.gnu.org/licenses/>.  */
end_comment

begin_include
include|#
directive|include
file|<config.h>
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

begin_comment
comment|/* #define ICO_DBG */
end_comment

begin_include
include|#
directive|include
file|"ico.h"
end_include

begin_include
include|#
directive|include
file|"ico-dialog.h"
end_include

begin_include
include|#
directive|include
file|"ico-save.h"
end_include

begin_include
include|#
directive|include
file|"libgimp/stdplugins-intl.h"
end_include

begin_function_decl
specifier|static
name|void
name|ico_dialog_bpp_changed
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

begin_function_decl
specifier|static
name|void
name|ico_dialog_toggle_compress
parameter_list|(
name|GtkWidget
modifier|*
name|checkbox
parameter_list|,
name|GObject
modifier|*
name|hbox
parameter_list|)
function_decl|;
end_function_decl

begin_function_decl
specifier|static
name|void
name|ico_dialog_check_compat
parameter_list|(
name|GtkWidget
modifier|*
name|dialog
parameter_list|,
name|IcoSaveInfo
modifier|*
name|info
parameter_list|)
function_decl|;
end_function_decl

begin_function
name|GtkWidget
modifier|*
DECL|function|ico_dialog_new (IcoSaveInfo * info)
name|ico_dialog_new
parameter_list|(
name|IcoSaveInfo
modifier|*
name|info
parameter_list|)
block|{
name|GtkWidget
modifier|*
name|dialog
decl_stmt|;
name|GtkWidget
modifier|*
name|main_vbox
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
name|scrolled_window
decl_stmt|;
name|GtkWidget
modifier|*
name|viewport
decl_stmt|;
name|GtkWidget
modifier|*
name|warning
decl_stmt|;
name|dialog
operator|=
name|gimp_export_dialog_new
argument_list|(
name|_
argument_list|(
literal|"Windows Icon"
argument_list|)
argument_list|,
name|PLUG_IN_BINARY
argument_list|,
literal|"plug-in-winicon"
argument_list|)
expr_stmt|;
comment|/* We store an array that holds each icon's requested bit depth      with the dialog. It's queried when the dialog is closed so the      save routine knows what colormaps etc to generate in the saved      file. We store twice the number necessary because in the second      set, the color depths that are automatically suggested are stored      for later comparison.   */
name|g_object_set_data
argument_list|(
name|G_OBJECT
argument_list|(
name|dialog
argument_list|)
argument_list|,
literal|"save_info"
argument_list|,
name|info
argument_list|)
expr_stmt|;
name|main_vbox
operator|=
name|gtk_box_new
argument_list|(
name|GTK_ORIENTATION_VERTICAL
argument_list|,
literal|12
argument_list|)
expr_stmt|;
name|gtk_container_set_border_width
argument_list|(
name|GTK_CONTAINER
argument_list|(
name|main_vbox
argument_list|)
argument_list|,
literal|12
argument_list|)
expr_stmt|;
name|gtk_box_pack_start
argument_list|(
name|GTK_BOX
argument_list|(
name|gimp_export_dialog_get_content_area
argument_list|(
name|dialog
argument_list|)
argument_list|)
argument_list|,
name|main_vbox
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
name|main_vbox
argument_list|)
expr_stmt|;
name|frame
operator|=
name|gimp_frame_new
argument_list|(
name|_
argument_list|(
literal|"Icon Details"
argument_list|)
argument_list|)
expr_stmt|;
name|gtk_box_pack_start
argument_list|(
name|GTK_BOX
argument_list|(
name|main_vbox
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
name|scrolled_window
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
name|scrolled_window
argument_list|)
argument_list|,
name|GTK_POLICY_NEVER
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
name|scrolled_window
argument_list|)
expr_stmt|;
name|gtk_widget_show
argument_list|(
name|scrolled_window
argument_list|)
expr_stmt|;
name|viewport
operator|=
name|gtk_viewport_new
argument_list|(
name|NULL
argument_list|,
name|NULL
argument_list|)
expr_stmt|;
name|gtk_container_add
argument_list|(
name|GTK_CONTAINER
argument_list|(
name|scrolled_window
argument_list|)
argument_list|,
name|viewport
argument_list|)
expr_stmt|;
name|gtk_widget_show
argument_list|(
name|viewport
argument_list|)
expr_stmt|;
name|vbox
operator|=
name|gtk_box_new
argument_list|(
name|GTK_ORIENTATION_VERTICAL
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
name|gtk_container_add
argument_list|(
name|GTK_CONTAINER
argument_list|(
name|viewport
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
name|warning
operator|=
name|g_object_new
argument_list|(
name|GIMP_TYPE_HINT_BOX
argument_list|,
literal|"stock-id"
argument_list|,
name|GIMP_STOCK_WARNING
argument_list|,
literal|"hint"
argument_list|,
name|_
argument_list|(
literal|"Large icons and compression are not supported "
literal|"by all programs. Older applications may not "
literal|"open this file correctly."
argument_list|)
argument_list|,
name|NULL
argument_list|)
expr_stmt|;
name|gtk_box_pack_end
argument_list|(
name|GTK_BOX
argument_list|(
name|main_vbox
argument_list|)
argument_list|,
name|warning
argument_list|,
name|FALSE
argument_list|,
name|FALSE
argument_list|,
literal|0
argument_list|)
expr_stmt|;
comment|/* don't show the warning here */
name|g_object_set_data
argument_list|(
name|G_OBJECT
argument_list|(
name|dialog
argument_list|)
argument_list|,
literal|"warning"
argument_list|,
name|warning
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
DECL|function|ico_preview_new (gint32 layer)
name|ico_preview_new
parameter_list|(
name|gint32
name|layer
parameter_list|)
block|{
name|GtkWidget
modifier|*
name|image
decl_stmt|;
name|GdkPixbuf
modifier|*
name|pixbuf
decl_stmt|;
name|gint
name|width
init|=
name|gimp_drawable_width
argument_list|(
name|layer
argument_list|)
decl_stmt|;
name|gint
name|height
init|=
name|gimp_drawable_height
argument_list|(
name|layer
argument_list|)
decl_stmt|;
name|pixbuf
operator|=
name|gimp_drawable_get_thumbnail
argument_list|(
name|layer
argument_list|,
name|MIN
argument_list|(
name|width
argument_list|,
literal|128
argument_list|)
argument_list|,
name|MIN
argument_list|(
name|height
argument_list|,
literal|128
argument_list|)
argument_list|,
name|GIMP_PIXBUF_SMALL_CHECKS
argument_list|)
expr_stmt|;
name|image
operator|=
name|gtk_image_new_from_pixbuf
argument_list|(
name|pixbuf
argument_list|)
expr_stmt|;
name|g_object_unref
argument_list|(
name|pixbuf
argument_list|)
expr_stmt|;
return|return
name|image
return|;
block|}
end_function

begin_comment
comment|/* This function creates and returns an hbox for an icon,    which then gets added to the dialog's main vbox. */
end_comment

begin_function
specifier|static
name|GtkWidget
modifier|*
DECL|function|ico_create_icon_hbox (GtkWidget * icon_preview,gint32 layer,gint layer_num,IcoSaveInfo * info)
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
parameter_list|,
name|IcoSaveInfo
modifier|*
name|info
parameter_list|)
block|{
specifier|static
name|GtkSizeGroup
modifier|*
name|size
init|=
name|NULL
decl_stmt|;
name|GtkWidget
modifier|*
name|hbox
decl_stmt|;
name|GtkWidget
modifier|*
name|vbox
decl_stmt|;
name|GtkWidget
modifier|*
name|alignment
decl_stmt|;
name|GtkWidget
modifier|*
name|combo
decl_stmt|;
name|GtkWidget
modifier|*
name|checkbox
decl_stmt|;
name|hbox
operator|=
name|gtk_box_new
argument_list|(
name|GTK_ORIENTATION_HORIZONTAL
argument_list|,
literal|6
argument_list|)
expr_stmt|;
name|alignment
operator|=
name|gtk_alignment_new
argument_list|(
literal|1.0
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
if|if
condition|(
operator|!
name|size
condition|)
name|size
operator|=
name|gtk_size_group_new
argument_list|(
name|GTK_SIZE_GROUP_HORIZONTAL
argument_list|)
expr_stmt|;
name|gtk_size_group_add_widget
argument_list|(
name|size
argument_list|,
name|alignment
argument_list|)
expr_stmt|;
name|vbox
operator|=
name|gtk_box_new
argument_list|(
name|GTK_ORIENTATION_VERTICAL
argument_list|,
literal|2
argument_list|)
expr_stmt|;
name|gtk_box_pack_start
argument_list|(
name|GTK_BOX
argument_list|(
name|hbox
argument_list|)
argument_list|,
name|vbox
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
name|vbox
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
literal|"24 bpp, 1-bit alpha, no palette"
argument_list|)
argument_list|,
literal|24
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
name|info
operator|->
name|depths
index|[
name|layer_num
index|]
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
name|ico_dialog_bpp_changed
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
name|vbox
argument_list|)
argument_list|,
name|combo
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
name|combo
argument_list|)
expr_stmt|;
name|checkbox
operator|=
name|gtk_check_button_new_with_label
argument_list|(
name|_
argument_list|(
literal|"Compressed (PNG)"
argument_list|)
argument_list|)
expr_stmt|;
name|gtk_toggle_button_set_active
argument_list|(
name|GTK_TOGGLE_BUTTON
argument_list|(
name|checkbox
argument_list|)
argument_list|,
name|info
operator|->
name|compress
index|[
name|layer_num
index|]
argument_list|)
expr_stmt|;
name|g_signal_connect
argument_list|(
name|checkbox
argument_list|,
literal|"toggled"
argument_list|,
name|G_CALLBACK
argument_list|(
name|ico_dialog_toggle_compress
argument_list|)
argument_list|,
name|hbox
argument_list|)
expr_stmt|;
name|gtk_box_pack_start
argument_list|(
name|GTK_BOX
argument_list|(
name|vbox
argument_list|)
argument_list|,
name|checkbox
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
name|checkbox
argument_list|)
expr_stmt|;
return|return
name|hbox
return|;
block|}
end_function

begin_function
specifier|static
name|GtkWidget
modifier|*
DECL|function|ico_dialog_get_layer_preview (GtkWidget * dialog,gint32 layer)
name|ico_dialog_get_layer_preview
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
name|ICO_MAXBUF
index|]
decl_stmt|;
name|g_snprintf
argument_list|(
name|key
argument_list|,
sizeof|sizeof
argument_list|(
name|key
argument_list|)
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
specifier|static
name|void
DECL|function|ico_dialog_update_icon_preview (GtkWidget * dialog,gint32 layer,gint bpp)
name|ico_dialog_update_icon_preview
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
init|=
name|ico_dialog_get_layer_preview
argument_list|(
name|dialog
argument_list|,
name|layer
argument_list|)
decl_stmt|;
name|GdkPixbuf
modifier|*
name|pixbuf
decl_stmt|;
specifier|const
name|Babl
modifier|*
name|format
decl_stmt|;
name|gint
name|w
init|=
name|gimp_drawable_width
argument_list|(
name|layer
argument_list|)
decl_stmt|;
name|gint
name|h
init|=
name|gimp_drawable_height
argument_list|(
name|layer
argument_list|)
decl_stmt|;
if|if
condition|(
operator|!
name|preview
condition|)
return|return;
switch|switch
condition|(
name|gimp_drawable_type
argument_list|(
name|layer
argument_list|)
condition|)
block|{
case|case
name|GIMP_RGB_IMAGE
case|:
name|format
operator|=
name|babl_format
argument_list|(
literal|"R'G'B' u8"
argument_list|)
expr_stmt|;
break|break;
case|case
name|GIMP_RGBA_IMAGE
case|:
name|format
operator|=
name|babl_format
argument_list|(
literal|"R'G'B'A u8"
argument_list|)
expr_stmt|;
break|break;
case|case
name|GIMP_GRAY_IMAGE
case|:
name|format
operator|=
name|babl_format
argument_list|(
literal|"Y' u8"
argument_list|)
expr_stmt|;
break|break;
case|case
name|GIMP_GRAYA_IMAGE
case|:
name|format
operator|=
name|babl_format
argument_list|(
literal|"Y'A u8"
argument_list|)
expr_stmt|;
break|break;
case|case
name|GIMP_INDEXED_IMAGE
case|:
case|case
name|GIMP_INDEXEDA_IMAGE
case|:
name|format
operator|=
name|gimp_drawable_get_format
argument_list|(
name|layer
argument_list|)
expr_stmt|;
default|default:
name|g_return_if_reached
argument_list|()
expr_stmt|;
block|}
if|if
condition|(
name|bpp
operator|<=
literal|8
condition|)
block|{
name|GeglBuffer
modifier|*
name|buffer
decl_stmt|;
name|GeglBuffer
modifier|*
name|tmp
decl_stmt|;
name|gint32
name|image
decl_stmt|;
name|gint32
name|tmp_image
decl_stmt|;
name|gint32
name|tmp_layer
decl_stmt|;
name|guchar
modifier|*
name|buf
decl_stmt|;
name|guchar
modifier|*
name|cmap
decl_stmt|;
name|gint
name|num_colors
decl_stmt|;
name|image
operator|=
name|gimp_item_get_image
argument_list|(
name|layer
argument_list|)
expr_stmt|;
name|tmp_image
operator|=
name|gimp_image_new
argument_list|(
name|w
argument_list|,
name|h
argument_list|,
name|gimp_image_base_type
argument_list|(
name|image
argument_list|)
argument_list|)
expr_stmt|;
name|gimp_image_undo_disable
argument_list|(
name|tmp_image
argument_list|)
expr_stmt|;
if|if
condition|(
name|gimp_drawable_is_indexed
argument_list|(
name|layer
argument_list|)
condition|)
block|{
name|cmap
operator|=
name|gimp_image_get_colormap
argument_list|(
name|image
argument_list|,
operator|&
name|num_colors
argument_list|)
expr_stmt|;
name|gimp_image_set_colormap
argument_list|(
name|tmp_image
argument_list|,
name|cmap
argument_list|,
name|num_colors
argument_list|)
expr_stmt|;
name|g_free
argument_list|(
name|cmap
argument_list|)
expr_stmt|;
block|}
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
name|gimp_drawable_type
argument_list|(
name|layer
argument_list|)
argument_list|,
literal|100
argument_list|,
name|GIMP_LAYER_MODE_NORMAL
argument_list|)
expr_stmt|;
name|gimp_image_insert_layer
argument_list|(
name|tmp_image
argument_list|,
name|tmp_layer
argument_list|,
operator|-
literal|1
argument_list|,
literal|0
argument_list|)
expr_stmt|;
name|buffer
operator|=
name|gimp_drawable_get_buffer
argument_list|(
name|layer
argument_list|)
expr_stmt|;
name|tmp
operator|=
name|gimp_drawable_get_buffer
argument_list|(
name|tmp_layer
argument_list|)
expr_stmt|;
name|buf
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
name|gegl_buffer_get
argument_list|(
name|buffer
argument_list|,
name|GEGL_RECTANGLE
argument_list|(
literal|0
argument_list|,
literal|0
argument_list|,
name|w
argument_list|,
name|h
argument_list|)
argument_list|,
literal|1.0
argument_list|,
name|format
argument_list|,
name|buf
argument_list|,
name|GEGL_AUTO_ROWSTRIDE
argument_list|,
name|GEGL_ABYSS_NONE
argument_list|)
expr_stmt|;
name|gegl_buffer_copy
argument_list|(
name|buffer
argument_list|,
name|NULL
argument_list|,
name|GEGL_ABYSS_NONE
argument_list|,
name|tmp
argument_list|,
name|NULL
argument_list|)
expr_stmt|;
name|g_object_unref
argument_list|(
name|tmp
argument_list|)
expr_stmt|;
name|g_object_unref
argument_list|(
name|buffer
argument_list|)
expr_stmt|;
if|if
condition|(
name|gimp_drawable_is_indexed
argument_list|(
name|layer
argument_list|)
condition|)
name|gimp_image_convert_rgb
argument_list|(
name|tmp_image
argument_list|)
expr_stmt|;
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
name|cmap
operator|=
name|gimp_image_get_colormap
argument_list|(
name|tmp_image
argument_list|,
operator|&
name|num_colors
argument_list|)
expr_stmt|;
if|if
condition|(
name|num_colors
operator|==
operator|(
literal|1
operator|<<
name|bpp
operator|)
operator|&&
operator|!
name|ico_cmap_contains_black
argument_list|(
name|cmap
argument_list|,
name|num_colors
argument_list|)
condition|)
block|{
comment|/* Windows icons with color maps need the color black.            * We need to eliminate one more color to make room for black.            */
if|if
condition|(
name|gimp_drawable_is_indexed
argument_list|(
name|layer
argument_list|)
condition|)
block|{
name|g_free
argument_list|(
name|cmap
argument_list|)
expr_stmt|;
name|cmap
operator|=
name|gimp_image_get_colormap
argument_list|(
name|image
argument_list|,
operator|&
name|num_colors
argument_list|)
expr_stmt|;
name|gimp_image_set_colormap
argument_list|(
name|tmp_image
argument_list|,
name|cmap
argument_list|,
name|num_colors
argument_list|)
expr_stmt|;
block|}
elseif|else
if|if
condition|(
name|gimp_drawable_is_gray
argument_list|(
name|layer
argument_list|)
condition|)
block|{
name|gimp_image_convert_grayscale
argument_list|(
name|tmp_image
argument_list|)
expr_stmt|;
block|}
else|else
block|{
name|gimp_image_convert_rgb
argument_list|(
name|tmp_image
argument_list|)
expr_stmt|;
block|}
name|tmp
operator|=
name|gimp_drawable_get_buffer
argument_list|(
name|tmp_layer
argument_list|)
expr_stmt|;
name|gegl_buffer_set
argument_list|(
name|tmp
argument_list|,
name|GEGL_RECTANGLE
argument_list|(
literal|0
argument_list|,
literal|0
argument_list|,
name|w
argument_list|,
name|h
argument_list|)
argument_list|,
literal|0
argument_list|,
name|format
argument_list|,
name|buf
argument_list|,
name|GEGL_AUTO_ROWSTRIDE
argument_list|)
expr_stmt|;
name|g_object_unref
argument_list|(
name|tmp
argument_list|)
expr_stmt|;
if|if
condition|(
operator|!
name|gimp_drawable_is_rgb
argument_list|(
name|layer
argument_list|)
condition|)
name|gimp_image_convert_rgb
argument_list|(
name|tmp_image
argument_list|)
expr_stmt|;
name|gimp_image_convert_indexed
argument_list|(
name|tmp_image
argument_list|,
name|GIMP_FS_DITHER
argument_list|,
name|GIMP_MAKE_PALETTE
argument_list|,
operator|(
literal|1
operator|<<
name|bpp
operator|)
operator|-
literal|1
argument_list|,
name|TRUE
argument_list|,
name|FALSE
argument_list|,
literal|"dummy"
argument_list|)
expr_stmt|;
block|}
name|g_free
argument_list|(
name|cmap
argument_list|)
expr_stmt|;
name|g_free
argument_list|(
name|buf
argument_list|)
expr_stmt|;
name|pixbuf
operator|=
name|gimp_drawable_get_thumbnail
argument_list|(
name|tmp_layer
argument_list|,
name|MIN
argument_list|(
name|w
argument_list|,
literal|128
argument_list|)
argument_list|,
name|MIN
argument_list|(
name|h
argument_list|,
literal|128
argument_list|)
argument_list|,
name|GIMP_PIXBUF_SMALL_CHECKS
argument_list|)
expr_stmt|;
name|gimp_image_delete
argument_list|(
name|tmp_image
argument_list|)
expr_stmt|;
block|}
elseif|else
if|if
condition|(
name|bpp
operator|==
literal|24
condition|)
block|{
name|GeglBuffer
modifier|*
name|buffer
decl_stmt|;
name|GeglBuffer
modifier|*
name|tmp
decl_stmt|;
name|gint32
name|image
decl_stmt|;
name|gint32
name|tmp_image
decl_stmt|;
name|gint32
name|tmp_layer
decl_stmt|;
name|GimpParam
modifier|*
name|return_vals
decl_stmt|;
name|gint
name|n_return_vals
decl_stmt|;
name|image
operator|=
name|gimp_item_get_image
argument_list|(
name|layer
argument_list|)
expr_stmt|;
name|tmp_image
operator|=
name|gimp_image_new
argument_list|(
name|w
argument_list|,
name|h
argument_list|,
name|gimp_image_base_type
argument_list|(
name|image
argument_list|)
argument_list|)
expr_stmt|;
name|gimp_image_undo_disable
argument_list|(
name|tmp_image
argument_list|)
expr_stmt|;
if|if
condition|(
name|gimp_drawable_is_indexed
argument_list|(
name|layer
argument_list|)
condition|)
block|{
name|guchar
modifier|*
name|cmap
decl_stmt|;
name|gint
name|num_colors
decl_stmt|;
name|cmap
operator|=
name|gimp_image_get_colormap
argument_list|(
name|image
argument_list|,
operator|&
name|num_colors
argument_list|)
expr_stmt|;
name|gimp_image_set_colormap
argument_list|(
name|tmp_image
argument_list|,
name|cmap
argument_list|,
name|num_colors
argument_list|)
expr_stmt|;
name|g_free
argument_list|(
name|cmap
argument_list|)
expr_stmt|;
block|}
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
name|gimp_drawable_type
argument_list|(
name|layer
argument_list|)
argument_list|,
literal|100
argument_list|,
name|GIMP_LAYER_MODE_NORMAL
argument_list|)
expr_stmt|;
name|gimp_image_insert_layer
argument_list|(
name|tmp_image
argument_list|,
name|tmp_layer
argument_list|,
operator|-
literal|1
argument_list|,
literal|0
argument_list|)
expr_stmt|;
name|buffer
operator|=
name|gimp_drawable_get_buffer
argument_list|(
name|layer
argument_list|)
expr_stmt|;
name|tmp
operator|=
name|gimp_drawable_get_buffer
argument_list|(
name|tmp_layer
argument_list|)
expr_stmt|;
name|gegl_buffer_copy
argument_list|(
name|buffer
argument_list|,
name|NULL
argument_list|,
name|GEGL_ABYSS_NONE
argument_list|,
name|tmp
argument_list|,
name|NULL
argument_list|)
expr_stmt|;
name|g_object_unref
argument_list|(
name|tmp
argument_list|)
expr_stmt|;
name|g_object_unref
argument_list|(
name|buffer
argument_list|)
expr_stmt|;
if|if
condition|(
name|gimp_drawable_is_indexed
argument_list|(
name|layer
argument_list|)
condition|)
name|gimp_image_convert_rgb
argument_list|(
name|tmp_image
argument_list|)
expr_stmt|;
name|return_vals
operator|=
name|gimp_run_procedure
argument_list|(
literal|"plug-in-threshold-alpha"
argument_list|,
operator|&
name|n_return_vals
argument_list|,
name|GIMP_PDB_INT32
argument_list|,
name|GIMP_RUN_NONINTERACTIVE
argument_list|,
name|GIMP_PDB_IMAGE
argument_list|,
name|tmp_image
argument_list|,
name|GIMP_PDB_DRAWABLE
argument_list|,
name|tmp_layer
argument_list|,
name|GIMP_PDB_INT32
argument_list|,
name|ICO_ALPHA_THRESHOLD
argument_list|,
name|GIMP_PDB_END
argument_list|)
expr_stmt|;
name|gimp_destroy_params
argument_list|(
name|return_vals
argument_list|,
name|n_return_vals
argument_list|)
expr_stmt|;
name|pixbuf
operator|=
name|gimp_drawable_get_thumbnail
argument_list|(
name|tmp_layer
argument_list|,
name|MIN
argument_list|(
name|w
argument_list|,
literal|128
argument_list|)
argument_list|,
name|MIN
argument_list|(
name|h
argument_list|,
literal|128
argument_list|)
argument_list|,
name|GIMP_PIXBUF_SMALL_CHECKS
argument_list|)
expr_stmt|;
name|gimp_image_delete
argument_list|(
name|tmp_image
argument_list|)
expr_stmt|;
block|}
else|else
block|{
name|pixbuf
operator|=
name|gimp_drawable_get_thumbnail
argument_list|(
name|layer
argument_list|,
name|MIN
argument_list|(
name|w
argument_list|,
literal|128
argument_list|)
argument_list|,
name|MIN
argument_list|(
name|h
argument_list|,
literal|128
argument_list|)
argument_list|,
name|GIMP_PIXBUF_SMALL_CHECKS
argument_list|)
expr_stmt|;
block|}
name|gtk_image_set_from_pixbuf
argument_list|(
name|GTK_IMAGE
argument_list|(
name|preview
argument_list|)
argument_list|,
name|pixbuf
argument_list|)
expr_stmt|;
name|g_object_unref
argument_list|(
name|pixbuf
argument_list|)
expr_stmt|;
block|}
end_function

begin_function
name|void
DECL|function|ico_dialog_add_icon (GtkWidget * dialog,gint32 layer,gint layer_num)
name|ico_dialog_add_icon
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
name|ICO_MAXBUF
index|]
decl_stmt|;
name|IcoSaveInfo
modifier|*
name|info
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
name|info
operator|=
name|g_object_get_data
argument_list|(
name|G_OBJECT
argument_list|(
name|dialog
argument_list|)
argument_list|,
literal|"save_info"
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
argument_list|,
name|info
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
sizeof|sizeof
argument_list|(
name|key
argument_list|)
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
name|ico_dialog_update_icon_preview
argument_list|(
name|dialog
argument_list|,
name|layer
argument_list|,
name|info
operator|->
name|depths
index|[
name|layer_num
index|]
argument_list|)
expr_stmt|;
name|ico_dialog_check_compat
argument_list|(
name|dialog
argument_list|,
name|info
argument_list|)
expr_stmt|;
block|}
end_function

begin_function
specifier|static
name|void
DECL|function|ico_dialog_bpp_changed (GtkWidget * combo,GObject * hbox)
name|ico_dialog_bpp_changed
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
name|IcoSaveInfo
modifier|*
name|info
decl_stmt|;
name|dialog
operator|=
name|gtk_widget_get_toplevel
argument_list|(
name|combo
argument_list|)
expr_stmt|;
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
name|info
operator|=
name|g_object_get_data
argument_list|(
name|G_OBJECT
argument_list|(
name|dialog
argument_list|)
argument_list|,
literal|"save_info"
argument_list|)
expr_stmt|;
name|g_assert
argument_list|(
name|info
argument_list|)
expr_stmt|;
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
name|info
operator|->
name|depths
index|[
name|layer_num
index|]
operator|=
name|bpp
expr_stmt|;
name|ico_dialog_update_icon_preview
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

begin_function
specifier|static
name|void
DECL|function|ico_dialog_toggle_compress (GtkWidget * checkbox,GObject * hbox)
name|ico_dialog_toggle_compress
parameter_list|(
name|GtkWidget
modifier|*
name|checkbox
parameter_list|,
name|GObject
modifier|*
name|hbox
parameter_list|)
block|{
name|GtkWidget
modifier|*
name|dialog
decl_stmt|;
name|gint
name|layer_num
decl_stmt|;
name|IcoSaveInfo
modifier|*
name|info
decl_stmt|;
name|dialog
operator|=
name|gtk_widget_get_toplevel
argument_list|(
name|checkbox
argument_list|)
expr_stmt|;
name|info
operator|=
name|g_object_get_data
argument_list|(
name|G_OBJECT
argument_list|(
name|dialog
argument_list|)
argument_list|,
literal|"save_info"
argument_list|)
expr_stmt|;
name|g_assert
argument_list|(
name|info
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
comment|/* Update vector entry for later when we're actually saving */
name|info
operator|->
name|compress
index|[
name|layer_num
index|]
operator|=
name|gtk_toggle_button_get_active
argument_list|(
name|GTK_TOGGLE_BUTTON
argument_list|(
name|checkbox
argument_list|)
argument_list|)
expr_stmt|;
name|ico_dialog_check_compat
argument_list|(
name|dialog
argument_list|,
name|info
argument_list|)
expr_stmt|;
block|}
end_function

begin_function
specifier|static
name|void
DECL|function|ico_dialog_check_compat (GtkWidget * dialog,IcoSaveInfo * info)
name|ico_dialog_check_compat
parameter_list|(
name|GtkWidget
modifier|*
name|dialog
parameter_list|,
name|IcoSaveInfo
modifier|*
name|info
parameter_list|)
block|{
name|GtkWidget
modifier|*
name|warning
decl_stmt|;
name|gboolean
name|warn
init|=
name|FALSE
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
name|info
operator|->
name|num_icons
condition|;
name|i
operator|++
control|)
block|{
if|if
condition|(
name|gimp_drawable_width
argument_list|(
name|info
operator|->
name|layers
index|[
name|i
index|]
argument_list|)
operator|>
literal|255
operator|||
name|gimp_drawable_height
argument_list|(
name|info
operator|->
name|layers
index|[
name|i
index|]
argument_list|)
operator|>
literal|255
operator|||
name|info
operator|->
name|compress
index|[
name|i
index|]
condition|)
block|{
name|warn
operator|=
name|TRUE
expr_stmt|;
break|break;
block|}
block|}
name|warning
operator|=
name|g_object_get_data
argument_list|(
name|G_OBJECT
argument_list|(
name|dialog
argument_list|)
argument_list|,
literal|"warning"
argument_list|)
expr_stmt|;
name|gtk_widget_set_visible
argument_list|(
name|warning
argument_list|,
name|warn
argument_list|)
expr_stmt|;
block|}
end_function

end_unit

