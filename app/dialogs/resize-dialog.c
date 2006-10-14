begin_unit|revision:0.9.5;language:C;cregit-version:0.0.1
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
file|<gtk/gtk.h>
end_include

begin_include
include|#
directive|include
file|"libgimpbase/gimpbase.h"
end_include

begin_include
include|#
directive|include
file|"libgimpwidgets/gimpwidgets.h"
end_include

begin_include
include|#
directive|include
file|"dialogs-types.h"
end_include

begin_include
include|#
directive|include
file|"core/gimpcontext.h"
end_include

begin_include
include|#
directive|include
file|"core/gimpimage.h"
end_include

begin_include
include|#
directive|include
file|"core/gimplayer.h"
end_include

begin_include
include|#
directive|include
file|"widgets/gimphelp-ids.h"
end_include

begin_include
include|#
directive|include
file|"widgets/gimpsizebox.h"
end_include

begin_include
include|#
directive|include
file|"widgets/gimpviewabledialog.h"
end_include

begin_include
include|#
directive|include
file|"resize-dialog.h"
end_include

begin_include
include|#
directive|include
file|"gimp-intl.h"
end_include

begin_define
DECL|macro|RESPONSE_RESET
define|#
directive|define
name|RESPONSE_RESET
value|1
end_define

begin_define
DECL|macro|SB_WIDTH
define|#
directive|define
name|SB_WIDTH
value|8
end_define

begin_typedef
DECL|typedef|ResizeDialog
typedef|typedef
name|struct
name|_ResizeDialog
name|ResizeDialog
typedef|;
end_typedef

begin_struct
DECL|struct|_ResizeDialog
struct|struct
name|_ResizeDialog
block|{
DECL|member|viewable
name|GimpViewable
modifier|*
name|viewable
decl_stmt|;
DECL|member|old_width
name|gint
name|old_width
decl_stmt|;
DECL|member|old_height
name|gint
name|old_height
decl_stmt|;
DECL|member|old_unit
name|GimpUnit
name|old_unit
decl_stmt|;
DECL|member|box
name|GtkWidget
modifier|*
name|box
decl_stmt|;
DECL|member|offset
name|GtkWidget
modifier|*
name|offset
decl_stmt|;
DECL|member|area
name|GtkWidget
modifier|*
name|area
decl_stmt|;
DECL|member|layer_set
name|GimpItemSet
name|layer_set
decl_stmt|;
DECL|member|callback
name|GimpResizeCallback
name|callback
decl_stmt|;
DECL|member|user_data
name|gpointer
name|user_data
decl_stmt|;
block|}
struct|;
end_struct

begin_function_decl
specifier|static
name|void
name|resize_dialog_response
parameter_list|(
name|GtkWidget
modifier|*
name|dialog
parameter_list|,
name|gint
name|response_id
parameter_list|,
name|ResizeDialog
modifier|*
name|private
parameter_list|)
function_decl|;
end_function_decl

begin_function_decl
specifier|static
name|void
name|resize_dialog_reset
parameter_list|(
name|ResizeDialog
modifier|*
name|private
parameter_list|)
function_decl|;
end_function_decl

begin_function_decl
specifier|static
name|void
name|size_notify
parameter_list|(
name|GimpSizeBox
modifier|*
name|box
parameter_list|,
name|GParamSpec
modifier|*
name|pspec
parameter_list|,
name|ResizeDialog
modifier|*
name|private
parameter_list|)
function_decl|;
end_function_decl

begin_function_decl
specifier|static
name|void
name|offset_update
parameter_list|(
name|GtkWidget
modifier|*
name|widget
parameter_list|,
name|ResizeDialog
modifier|*
name|private
parameter_list|)
function_decl|;
end_function_decl

begin_function_decl
specifier|static
name|void
name|offsets_changed
parameter_list|(
name|GtkWidget
modifier|*
name|area
parameter_list|,
name|gint
name|off_x
parameter_list|,
name|gint
name|off_y
parameter_list|,
name|ResizeDialog
modifier|*
name|private
parameter_list|)
function_decl|;
end_function_decl

begin_function_decl
specifier|static
name|void
name|offset_center_clicked
parameter_list|(
name|GtkWidget
modifier|*
name|widget
parameter_list|,
name|ResizeDialog
modifier|*
name|private
parameter_list|)
function_decl|;
end_function_decl

begin_function
name|GtkWidget
modifier|*
DECL|function|resize_dialog_new (GimpViewable * viewable,GimpContext * context,const gchar * title,const gchar * role,GtkWidget * parent,GimpHelpFunc help_func,const gchar * help_id,GimpUnit unit,GimpResizeCallback callback,gpointer user_data)
name|resize_dialog_new
parameter_list|(
name|GimpViewable
modifier|*
name|viewable
parameter_list|,
name|GimpContext
modifier|*
name|context
parameter_list|,
specifier|const
name|gchar
modifier|*
name|title
parameter_list|,
specifier|const
name|gchar
modifier|*
name|role
parameter_list|,
name|GtkWidget
modifier|*
name|parent
parameter_list|,
name|GimpHelpFunc
name|help_func
parameter_list|,
specifier|const
name|gchar
modifier|*
name|help_id
parameter_list|,
name|GimpUnit
name|unit
parameter_list|,
name|GimpResizeCallback
name|callback
parameter_list|,
name|gpointer
name|user_data
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
name|abox
decl_stmt|;
name|GtkWidget
modifier|*
name|frame
decl_stmt|;
name|GtkWidget
modifier|*
name|button
decl_stmt|;
name|GtkWidget
modifier|*
name|spinbutton
decl_stmt|;
name|GtkWidget
modifier|*
name|entry
decl_stmt|;
name|GtkObject
modifier|*
name|adjustment
decl_stmt|;
name|GdkPixbuf
modifier|*
name|pixbuf
decl_stmt|;
name|ResizeDialog
modifier|*
name|private
decl_stmt|;
name|GimpImage
modifier|*
name|image
init|=
name|NULL
decl_stmt|;
specifier|const
name|gchar
modifier|*
name|text
init|=
name|NULL
decl_stmt|;
name|gint
name|width
decl_stmt|,
name|height
decl_stmt|;
name|gdouble
name|xres
decl_stmt|,
name|yres
decl_stmt|;
name|g_return_val_if_fail
argument_list|(
name|GIMP_IS_VIEWABLE
argument_list|(
name|viewable
argument_list|)
argument_list|,
name|NULL
argument_list|)
expr_stmt|;
name|g_return_val_if_fail
argument_list|(
name|GIMP_IS_CONTEXT
argument_list|(
name|context
argument_list|)
argument_list|,
name|NULL
argument_list|)
expr_stmt|;
name|g_return_val_if_fail
argument_list|(
name|callback
operator|!=
name|NULL
argument_list|,
name|NULL
argument_list|)
expr_stmt|;
if|if
condition|(
name|GIMP_IS_IMAGE
argument_list|(
name|viewable
argument_list|)
condition|)
block|{
name|image
operator|=
name|GIMP_IMAGE
argument_list|(
name|viewable
argument_list|)
expr_stmt|;
name|width
operator|=
name|gimp_image_get_width
argument_list|(
name|image
argument_list|)
expr_stmt|;
name|height
operator|=
name|gimp_image_get_height
argument_list|(
name|image
argument_list|)
expr_stmt|;
name|text
operator|=
name|_
argument_list|(
literal|"Canvas Size"
argument_list|)
expr_stmt|;
block|}
elseif|else
if|if
condition|(
name|GIMP_IS_ITEM
argument_list|(
name|viewable
argument_list|)
condition|)
block|{
name|GimpItem
modifier|*
name|item
init|=
name|GIMP_ITEM
argument_list|(
name|viewable
argument_list|)
decl_stmt|;
name|image
operator|=
name|gimp_item_get_image
argument_list|(
name|item
argument_list|)
expr_stmt|;
name|width
operator|=
name|gimp_item_width
argument_list|(
name|item
argument_list|)
expr_stmt|;
name|height
operator|=
name|gimp_item_height
argument_list|(
name|item
argument_list|)
expr_stmt|;
name|text
operator|=
name|_
argument_list|(
literal|"Layer Size"
argument_list|)
expr_stmt|;
block|}
else|else
block|{
name|g_return_val_if_reached
argument_list|(
name|NULL
argument_list|)
expr_stmt|;
block|}
name|dialog
operator|=
name|gimp_viewable_dialog_new
argument_list|(
name|viewable
argument_list|,
name|context
argument_list|,
name|title
argument_list|,
name|role
argument_list|,
name|GIMP_STOCK_RESIZE
argument_list|,
name|title
argument_list|,
name|parent
argument_list|,
name|help_func
argument_list|,
name|help_id
argument_list|,
name|GIMP_STOCK_RESET
argument_list|,
name|RESPONSE_RESET
argument_list|,
name|GTK_STOCK_CANCEL
argument_list|,
name|GTK_RESPONSE_CANCEL
argument_list|,
name|GIMP_STOCK_RESIZE
argument_list|,
name|GTK_RESPONSE_OK
argument_list|,
name|NULL
argument_list|)
expr_stmt|;
name|gtk_window_set_resizable
argument_list|(
name|GTK_WINDOW
argument_list|(
name|dialog
argument_list|)
argument_list|,
name|FALSE
argument_list|)
expr_stmt|;
name|gtk_dialog_set_alternative_button_order
argument_list|(
name|GTK_DIALOG
argument_list|(
name|dialog
argument_list|)
argument_list|,
name|RESPONSE_RESET
argument_list|,
name|GTK_RESPONSE_OK
argument_list|,
name|GTK_RESPONSE_CANCEL
argument_list|,
operator|-
literal|1
argument_list|)
expr_stmt|;
name|private
operator|=
name|g_new0
argument_list|(
name|ResizeDialog
argument_list|,
literal|1
argument_list|)
expr_stmt|;
name|g_object_weak_ref
argument_list|(
name|G_OBJECT
argument_list|(
name|dialog
argument_list|)
argument_list|,
operator|(
name|GWeakNotify
operator|)
name|g_free
argument_list|,
name|private
argument_list|)
expr_stmt|;
name|private
operator|->
name|viewable
operator|=
name|viewable
expr_stmt|;
name|private
operator|->
name|old_width
operator|=
name|width
expr_stmt|;
name|private
operator|->
name|old_height
operator|=
name|height
expr_stmt|;
name|private
operator|->
name|old_unit
operator|=
name|unit
expr_stmt|;
name|private
operator|->
name|layer_set
operator|=
name|GIMP_ITEM_SET_NONE
expr_stmt|;
name|private
operator|->
name|callback
operator|=
name|callback
expr_stmt|;
name|private
operator|->
name|user_data
operator|=
name|user_data
expr_stmt|;
name|gimp_image_get_resolution
argument_list|(
name|image
argument_list|,
operator|&
name|xres
argument_list|,
operator|&
name|yres
argument_list|)
expr_stmt|;
name|private
operator|->
name|box
operator|=
name|g_object_new
argument_list|(
name|GIMP_TYPE_SIZE_BOX
argument_list|,
literal|"width"
argument_list|,
name|width
argument_list|,
literal|"height"
argument_list|,
name|height
argument_list|,
literal|"unit"
argument_list|,
name|unit
argument_list|,
literal|"xresolution"
argument_list|,
name|xres
argument_list|,
literal|"yresolution"
argument_list|,
name|yres
argument_list|,
literal|"keep-aspect"
argument_list|,
name|TRUE
argument_list|,
literal|"edit-resolution"
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
literal|"response"
argument_list|,
name|G_CALLBACK
argument_list|(
name|resize_dialog_response
argument_list|)
argument_list|,
name|private
argument_list|)
expr_stmt|;
name|main_vbox
operator|=
name|gtk_vbox_new
argument_list|(
name|FALSE
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
name|gtk_container_add
argument_list|(
name|GTK_CONTAINER
argument_list|(
name|GTK_DIALOG
argument_list|(
name|dialog
argument_list|)
operator|->
name|vbox
argument_list|)
argument_list|,
name|main_vbox
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
name|text
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
name|FALSE
argument_list|,
name|FALSE
argument_list|,
literal|0
argument_list|)
expr_stmt|;
name|gtk_widget_show
argument_list|(
name|frame
argument_list|)
expr_stmt|;
name|gtk_container_add
argument_list|(
name|GTK_CONTAINER
argument_list|(
name|frame
argument_list|)
argument_list|,
name|private
operator|->
name|box
argument_list|)
expr_stmt|;
name|gtk_widget_show
argument_list|(
name|private
operator|->
name|box
argument_list|)
expr_stmt|;
name|frame
operator|=
name|gimp_frame_new
argument_list|(
name|_
argument_list|(
literal|"Offset"
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
name|FALSE
argument_list|,
name|FALSE
argument_list|,
literal|0
argument_list|)
expr_stmt|;
name|gtk_widget_show
argument_list|(
name|frame
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
name|gtk_widget_show
argument_list|(
name|vbox
argument_list|)
expr_stmt|;
comment|/*  the offset sizeentry  */
name|spinbutton
operator|=
name|gimp_spin_button_new
argument_list|(
operator|&
name|adjustment
argument_list|,
literal|1
argument_list|,
literal|1
argument_list|,
literal|1
argument_list|,
literal|1
argument_list|,
literal|10
argument_list|,
literal|1
argument_list|,
literal|1
argument_list|,
literal|2
argument_list|)
expr_stmt|;
name|gtk_entry_set_width_chars
argument_list|(
name|GTK_ENTRY
argument_list|(
name|spinbutton
argument_list|)
argument_list|,
name|SB_WIDTH
argument_list|)
expr_stmt|;
name|private
operator|->
name|offset
operator|=
name|entry
operator|=
name|gimp_size_entry_new
argument_list|(
literal|1
argument_list|,
name|unit
argument_list|,
literal|"%p"
argument_list|,
name|TRUE
argument_list|,
name|FALSE
argument_list|,
name|FALSE
argument_list|,
name|SB_WIDTH
argument_list|,
name|GIMP_SIZE_ENTRY_UPDATE_SIZE
argument_list|)
expr_stmt|;
name|gtk_table_set_col_spacing
argument_list|(
name|GTK_TABLE
argument_list|(
name|entry
argument_list|)
argument_list|,
literal|0
argument_list|,
literal|6
argument_list|)
expr_stmt|;
name|gtk_table_set_col_spacing
argument_list|(
name|GTK_TABLE
argument_list|(
name|entry
argument_list|)
argument_list|,
literal|1
argument_list|,
literal|6
argument_list|)
expr_stmt|;
name|gtk_table_set_col_spacing
argument_list|(
name|GTK_TABLE
argument_list|(
name|entry
argument_list|)
argument_list|,
literal|3
argument_list|,
literal|12
argument_list|)
expr_stmt|;
name|gtk_table_set_row_spacing
argument_list|(
name|GTK_TABLE
argument_list|(
name|entry
argument_list|)
argument_list|,
literal|0
argument_list|,
literal|2
argument_list|)
expr_stmt|;
name|gimp_size_entry_add_field
argument_list|(
name|GIMP_SIZE_ENTRY
argument_list|(
name|entry
argument_list|)
argument_list|,
name|GTK_SPIN_BUTTON
argument_list|(
name|spinbutton
argument_list|)
argument_list|,
name|NULL
argument_list|)
expr_stmt|;
name|gtk_table_attach_defaults
argument_list|(
name|GTK_TABLE
argument_list|(
name|entry
argument_list|)
argument_list|,
name|spinbutton
argument_list|,
literal|1
argument_list|,
literal|2
argument_list|,
literal|0
argument_list|,
literal|1
argument_list|)
expr_stmt|;
name|gtk_widget_show
argument_list|(
name|spinbutton
argument_list|)
expr_stmt|;
name|gimp_size_entry_attach_label
argument_list|(
name|GIMP_SIZE_ENTRY
argument_list|(
name|entry
argument_list|)
argument_list|,
name|_
argument_list|(
literal|"_X:"
argument_list|)
argument_list|,
literal|0
argument_list|,
literal|0
argument_list|,
literal|0.0
argument_list|)
expr_stmt|;
name|gimp_size_entry_attach_label
argument_list|(
name|GIMP_SIZE_ENTRY
argument_list|(
name|entry
argument_list|)
argument_list|,
name|_
argument_list|(
literal|"_Y:"
argument_list|)
argument_list|,
literal|1
argument_list|,
literal|0
argument_list|,
literal|0.0
argument_list|)
expr_stmt|;
name|gtk_box_pack_start
argument_list|(
name|GTK_BOX
argument_list|(
name|vbox
argument_list|)
argument_list|,
name|entry
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
name|entry
argument_list|)
expr_stmt|;
name|gimp_size_entry_set_resolution
argument_list|(
name|GIMP_SIZE_ENTRY
argument_list|(
name|entry
argument_list|)
argument_list|,
literal|0
argument_list|,
name|xres
argument_list|,
name|FALSE
argument_list|)
expr_stmt|;
name|gimp_size_entry_set_resolution
argument_list|(
name|GIMP_SIZE_ENTRY
argument_list|(
name|entry
argument_list|)
argument_list|,
literal|1
argument_list|,
name|yres
argument_list|,
name|FALSE
argument_list|)
expr_stmt|;
name|gimp_size_entry_set_refval_boundaries
argument_list|(
name|GIMP_SIZE_ENTRY
argument_list|(
name|entry
argument_list|)
argument_list|,
literal|0
argument_list|,
literal|0
argument_list|,
literal|0
argument_list|)
expr_stmt|;
name|gimp_size_entry_set_refval_boundaries
argument_list|(
name|GIMP_SIZE_ENTRY
argument_list|(
name|entry
argument_list|)
argument_list|,
literal|1
argument_list|,
literal|0
argument_list|,
literal|0
argument_list|)
expr_stmt|;
name|gimp_size_entry_set_refval
argument_list|(
name|GIMP_SIZE_ENTRY
argument_list|(
name|entry
argument_list|)
argument_list|,
literal|0
argument_list|,
literal|0
argument_list|)
expr_stmt|;
name|gimp_size_entry_set_refval
argument_list|(
name|GIMP_SIZE_ENTRY
argument_list|(
name|entry
argument_list|)
argument_list|,
literal|1
argument_list|,
literal|0
argument_list|)
expr_stmt|;
name|g_signal_connect
argument_list|(
name|entry
argument_list|,
literal|"value-changed"
argument_list|,
name|G_CALLBACK
argument_list|(
name|offset_update
argument_list|)
argument_list|,
name|private
argument_list|)
expr_stmt|;
name|button
operator|=
name|gtk_button_new_from_stock
argument_list|(
name|GIMP_STOCK_CENTER
argument_list|)
expr_stmt|;
name|gtk_table_attach_defaults
argument_list|(
name|GTK_TABLE
argument_list|(
name|entry
argument_list|)
argument_list|,
name|button
argument_list|,
literal|4
argument_list|,
literal|5
argument_list|,
literal|1
argument_list|,
literal|2
argument_list|)
expr_stmt|;
name|gtk_widget_show
argument_list|(
name|button
argument_list|)
expr_stmt|;
name|g_signal_connect
argument_list|(
name|button
argument_list|,
literal|"clicked"
argument_list|,
name|G_CALLBACK
argument_list|(
name|offset_center_clicked
argument_list|)
argument_list|,
name|private
argument_list|)
expr_stmt|;
name|abox
operator|=
name|gtk_alignment_new
argument_list|(
literal|0.5
argument_list|,
literal|0.5
argument_list|,
literal|0.0
argument_list|,
literal|0.0
argument_list|)
expr_stmt|;
name|gtk_box_pack_start
argument_list|(
name|GTK_BOX
argument_list|(
name|vbox
argument_list|)
argument_list|,
name|abox
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
name|abox
argument_list|)
expr_stmt|;
name|frame
operator|=
name|gtk_frame_new
argument_list|(
name|NULL
argument_list|)
expr_stmt|;
name|gtk_frame_set_shadow_type
argument_list|(
name|GTK_FRAME
argument_list|(
name|frame
argument_list|)
argument_list|,
name|GTK_SHADOW_IN
argument_list|)
expr_stmt|;
name|gtk_container_add
argument_list|(
name|GTK_CONTAINER
argument_list|(
name|abox
argument_list|)
argument_list|,
name|frame
argument_list|)
expr_stmt|;
name|gtk_widget_show
argument_list|(
name|frame
argument_list|)
expr_stmt|;
name|private
operator|->
name|area
operator|=
name|gimp_offset_area_new
argument_list|(
name|width
argument_list|,
name|height
argument_list|)
expr_stmt|;
name|gtk_container_add
argument_list|(
name|GTK_CONTAINER
argument_list|(
name|frame
argument_list|)
argument_list|,
name|private
operator|->
name|area
argument_list|)
expr_stmt|;
name|gtk_widget_show
argument_list|(
name|private
operator|->
name|area
argument_list|)
expr_stmt|;
name|gimp_viewable_get_preview_size
argument_list|(
name|viewable
argument_list|,
literal|200
argument_list|,
name|FALSE
argument_list|,
name|TRUE
argument_list|,
operator|&
name|width
argument_list|,
operator|&
name|height
argument_list|)
expr_stmt|;
name|pixbuf
operator|=
name|gimp_viewable_get_pixbuf
argument_list|(
name|viewable
argument_list|,
name|context
argument_list|,
name|width
argument_list|,
name|height
argument_list|)
expr_stmt|;
if|if
condition|(
name|pixbuf
condition|)
name|gimp_offset_area_set_pixbuf
argument_list|(
name|GIMP_OFFSET_AREA
argument_list|(
name|private
operator|->
name|area
argument_list|)
argument_list|,
name|pixbuf
argument_list|)
expr_stmt|;
name|g_signal_connect
argument_list|(
name|private
operator|->
name|area
argument_list|,
literal|"offsets-changed"
argument_list|,
name|G_CALLBACK
argument_list|(
name|offsets_changed
argument_list|)
argument_list|,
name|private
argument_list|)
expr_stmt|;
name|g_signal_connect
argument_list|(
name|private
operator|->
name|box
argument_list|,
literal|"notify"
argument_list|,
name|G_CALLBACK
argument_list|(
name|size_notify
argument_list|)
argument_list|,
name|private
argument_list|)
expr_stmt|;
if|if
condition|(
name|GIMP_IS_IMAGE
argument_list|(
name|viewable
argument_list|)
condition|)
block|{
name|GtkWidget
modifier|*
name|hbox
decl_stmt|;
name|GtkWidget
modifier|*
name|label
decl_stmt|;
name|GtkWidget
modifier|*
name|combo
decl_stmt|;
name|frame
operator|=
name|gimp_frame_new
argument_list|(
name|_
argument_list|(
literal|"Layers"
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
name|FALSE
argument_list|,
name|FALSE
argument_list|,
literal|0
argument_list|)
expr_stmt|;
name|gtk_widget_show
argument_list|(
name|frame
argument_list|)
expr_stmt|;
name|hbox
operator|=
name|gtk_hbox_new
argument_list|(
name|FALSE
argument_list|,
literal|6
argument_list|)
expr_stmt|;
name|gtk_container_add
argument_list|(
name|GTK_CONTAINER
argument_list|(
name|frame
argument_list|)
argument_list|,
name|hbox
argument_list|)
expr_stmt|;
name|gtk_widget_show
argument_list|(
name|hbox
argument_list|)
expr_stmt|;
name|label
operator|=
name|gtk_label_new_with_mnemonic
argument_list|(
name|_
argument_list|(
literal|"Resize _layers:"
argument_list|)
argument_list|)
expr_stmt|;
name|gtk_box_pack_start
argument_list|(
name|GTK_BOX
argument_list|(
name|hbox
argument_list|)
argument_list|,
name|label
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
name|label
argument_list|)
expr_stmt|;
name|combo
operator|=
name|gimp_enum_combo_box_new
argument_list|(
name|GIMP_TYPE_ITEM_SET
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
name|gtk_label_set_mnemonic_widget
argument_list|(
name|GTK_LABEL
argument_list|(
name|label
argument_list|)
argument_list|,
name|combo
argument_list|)
expr_stmt|;
name|gimp_int_combo_box_connect
argument_list|(
name|GIMP_INT_COMBO_BOX
argument_list|(
name|combo
argument_list|)
argument_list|,
name|private
operator|->
name|layer_set
argument_list|,
name|G_CALLBACK
argument_list|(
name|gimp_int_combo_box_get_active
argument_list|)
argument_list|,
operator|&
name|private
operator|->
name|layer_set
argument_list|)
expr_stmt|;
block|}
return|return
name|dialog
return|;
block|}
end_function

begin_function
specifier|static
name|void
DECL|function|resize_dialog_response (GtkWidget * dialog,gint response_id,ResizeDialog * private)
name|resize_dialog_response
parameter_list|(
name|GtkWidget
modifier|*
name|dialog
parameter_list|,
name|gint
name|response_id
parameter_list|,
name|ResizeDialog
modifier|*
name|private
parameter_list|)
block|{
name|GimpSizeEntry
modifier|*
name|entry
init|=
name|GIMP_SIZE_ENTRY
argument_list|(
name|private
operator|->
name|offset
argument_list|)
decl_stmt|;
name|GimpUnit
name|unit
decl_stmt|;
name|gint
name|width
decl_stmt|;
name|gint
name|height
decl_stmt|;
switch|switch
condition|(
name|response_id
condition|)
block|{
case|case
name|RESPONSE_RESET
case|:
name|resize_dialog_reset
argument_list|(
name|private
argument_list|)
expr_stmt|;
break|break;
case|case
name|GTK_RESPONSE_OK
case|:
name|g_object_get
argument_list|(
name|private
operator|->
name|box
argument_list|,
literal|"width"
argument_list|,
operator|&
name|width
argument_list|,
literal|"height"
argument_list|,
operator|&
name|height
argument_list|,
literal|"unit"
argument_list|,
operator|&
name|unit
argument_list|,
name|NULL
argument_list|)
expr_stmt|;
name|private
operator|->
name|callback
argument_list|(
name|dialog
argument_list|,
name|private
operator|->
name|viewable
argument_list|,
name|width
argument_list|,
name|height
argument_list|,
name|unit
argument_list|,
name|gimp_size_entry_get_refval
argument_list|(
name|entry
argument_list|,
literal|0
argument_list|)
argument_list|,
name|gimp_size_entry_get_refval
argument_list|(
name|entry
argument_list|,
literal|1
argument_list|)
argument_list|,
name|private
operator|->
name|layer_set
argument_list|,
name|private
operator|->
name|user_data
argument_list|)
expr_stmt|;
break|break;
default|default:
name|gtk_widget_destroy
argument_list|(
name|dialog
argument_list|)
expr_stmt|;
break|break;
block|}
block|}
end_function

begin_function
specifier|static
name|void
DECL|function|resize_dialog_reset (ResizeDialog * private)
name|resize_dialog_reset
parameter_list|(
name|ResizeDialog
modifier|*
name|private
parameter_list|)
block|{
name|g_object_set
argument_list|(
name|private
operator|->
name|box
argument_list|,
literal|"keep-aspect"
argument_list|,
name|FALSE
argument_list|,
name|NULL
argument_list|)
expr_stmt|;
name|g_object_set
argument_list|(
name|private
operator|->
name|box
argument_list|,
literal|"width"
argument_list|,
name|private
operator|->
name|old_width
argument_list|,
literal|"height"
argument_list|,
name|private
operator|->
name|old_height
argument_list|,
literal|"unit"
argument_list|,
name|private
operator|->
name|old_unit
argument_list|,
name|NULL
argument_list|)
expr_stmt|;
name|g_object_set
argument_list|(
name|private
operator|->
name|box
argument_list|,
literal|"keep-aspect"
argument_list|,
name|TRUE
argument_list|,
name|NULL
argument_list|)
expr_stmt|;
block|}
end_function

begin_function
specifier|static
name|void
DECL|function|size_notify (GimpSizeBox * box,GParamSpec * pspec,ResizeDialog * private)
name|size_notify
parameter_list|(
name|GimpSizeBox
modifier|*
name|box
parameter_list|,
name|GParamSpec
modifier|*
name|pspec
parameter_list|,
name|ResizeDialog
modifier|*
name|private
parameter_list|)
block|{
name|gint
name|diff_x
init|=
name|box
operator|->
name|width
operator|-
name|private
operator|->
name|old_width
decl_stmt|;
name|gint
name|diff_y
init|=
name|box
operator|->
name|height
operator|-
name|private
operator|->
name|old_height
decl_stmt|;
name|gimp_offset_area_set_size
argument_list|(
name|GIMP_OFFSET_AREA
argument_list|(
name|private
operator|->
name|area
argument_list|)
argument_list|,
name|box
operator|->
name|width
argument_list|,
name|box
operator|->
name|height
argument_list|)
expr_stmt|;
name|gimp_size_entry_set_refval_boundaries
argument_list|(
name|GIMP_SIZE_ENTRY
argument_list|(
name|private
operator|->
name|offset
argument_list|)
argument_list|,
literal|0
argument_list|,
name|MIN
argument_list|(
literal|0
argument_list|,
name|diff_x
argument_list|)
argument_list|,
name|MAX
argument_list|(
literal|0
argument_list|,
name|diff_x
argument_list|)
argument_list|)
expr_stmt|;
name|gimp_size_entry_set_refval_boundaries
argument_list|(
name|GIMP_SIZE_ENTRY
argument_list|(
name|private
operator|->
name|offset
argument_list|)
argument_list|,
literal|1
argument_list|,
name|MIN
argument_list|(
literal|0
argument_list|,
name|diff_y
argument_list|)
argument_list|,
name|MAX
argument_list|(
literal|0
argument_list|,
name|diff_y
argument_list|)
argument_list|)
expr_stmt|;
block|}
end_function

begin_function
specifier|static
name|gint
DECL|function|resize_bound_off_x (ResizeDialog * private,gint offset_x)
name|resize_bound_off_x
parameter_list|(
name|ResizeDialog
modifier|*
name|private
parameter_list|,
name|gint
name|offset_x
parameter_list|)
block|{
name|GimpSizeBox
modifier|*
name|box
init|=
name|GIMP_SIZE_BOX
argument_list|(
name|private
operator|->
name|box
argument_list|)
decl_stmt|;
if|if
condition|(
name|private
operator|->
name|old_width
operator|<=
name|box
operator|->
name|width
condition|)
return|return
name|CLAMP
argument_list|(
name|offset_x
argument_list|,
literal|0
argument_list|,
operator|(
name|box
operator|->
name|width
operator|-
name|private
operator|->
name|old_width
operator|)
argument_list|)
return|;
else|else
return|return
name|CLAMP
argument_list|(
name|offset_x
argument_list|,
operator|(
name|box
operator|->
name|width
operator|-
name|private
operator|->
name|old_width
operator|)
argument_list|,
literal|0
argument_list|)
return|;
block|}
end_function

begin_function
specifier|static
name|gint
DECL|function|resize_bound_off_y (ResizeDialog * private,gint off_y)
name|resize_bound_off_y
parameter_list|(
name|ResizeDialog
modifier|*
name|private
parameter_list|,
name|gint
name|off_y
parameter_list|)
block|{
name|GimpSizeBox
modifier|*
name|box
init|=
name|GIMP_SIZE_BOX
argument_list|(
name|private
operator|->
name|box
argument_list|)
decl_stmt|;
if|if
condition|(
name|private
operator|->
name|old_height
operator|<=
name|box
operator|->
name|height
condition|)
return|return
name|CLAMP
argument_list|(
name|off_y
argument_list|,
literal|0
argument_list|,
operator|(
name|box
operator|->
name|height
operator|-
name|private
operator|->
name|old_height
operator|)
argument_list|)
return|;
else|else
return|return
name|CLAMP
argument_list|(
name|off_y
argument_list|,
operator|(
name|box
operator|->
name|height
operator|-
name|private
operator|->
name|old_height
operator|)
argument_list|,
literal|0
argument_list|)
return|;
block|}
end_function

begin_function
specifier|static
name|void
DECL|function|offset_update (GtkWidget * widget,ResizeDialog * private)
name|offset_update
parameter_list|(
name|GtkWidget
modifier|*
name|widget
parameter_list|,
name|ResizeDialog
modifier|*
name|private
parameter_list|)
block|{
name|GimpSizeEntry
modifier|*
name|entry
init|=
name|GIMP_SIZE_ENTRY
argument_list|(
name|private
operator|->
name|offset
argument_list|)
decl_stmt|;
name|gint
name|off_x
decl_stmt|;
name|gint
name|off_y
decl_stmt|;
name|off_x
operator|=
name|resize_bound_off_x
argument_list|(
name|private
argument_list|,
name|RINT
argument_list|(
name|gimp_size_entry_get_refval
argument_list|(
name|entry
argument_list|,
literal|0
argument_list|)
argument_list|)
argument_list|)
expr_stmt|;
name|off_y
operator|=
name|resize_bound_off_y
argument_list|(
name|private
argument_list|,
name|RINT
argument_list|(
name|gimp_size_entry_get_refval
argument_list|(
name|entry
argument_list|,
literal|1
argument_list|)
argument_list|)
argument_list|)
expr_stmt|;
name|gimp_offset_area_set_offsets
argument_list|(
name|GIMP_OFFSET_AREA
argument_list|(
name|private
operator|->
name|area
argument_list|)
argument_list|,
name|off_x
argument_list|,
name|off_y
argument_list|)
expr_stmt|;
block|}
end_function

begin_function
specifier|static
name|void
DECL|function|offsets_changed (GtkWidget * area,gint off_x,gint off_y,ResizeDialog * private)
name|offsets_changed
parameter_list|(
name|GtkWidget
modifier|*
name|area
parameter_list|,
name|gint
name|off_x
parameter_list|,
name|gint
name|off_y
parameter_list|,
name|ResizeDialog
modifier|*
name|private
parameter_list|)
block|{
name|gimp_size_entry_set_refval
argument_list|(
name|GIMP_SIZE_ENTRY
argument_list|(
name|private
operator|->
name|offset
argument_list|)
argument_list|,
literal|0
argument_list|,
name|off_x
argument_list|)
expr_stmt|;
name|gimp_size_entry_set_refval
argument_list|(
name|GIMP_SIZE_ENTRY
argument_list|(
name|private
operator|->
name|offset
argument_list|)
argument_list|,
literal|1
argument_list|,
name|off_y
argument_list|)
expr_stmt|;
block|}
end_function

begin_function
specifier|static
name|void
DECL|function|offset_center_clicked (GtkWidget * widget,ResizeDialog * private)
name|offset_center_clicked
parameter_list|(
name|GtkWidget
modifier|*
name|widget
parameter_list|,
name|ResizeDialog
modifier|*
name|private
parameter_list|)
block|{
name|GimpSizeBox
modifier|*
name|box
init|=
name|GIMP_SIZE_BOX
argument_list|(
name|private
operator|->
name|box
argument_list|)
decl_stmt|;
name|gint
name|off_x
decl_stmt|;
name|gint
name|off_y
decl_stmt|;
name|off_x
operator|=
name|resize_bound_off_x
argument_list|(
name|private
argument_list|,
operator|(
name|box
operator|->
name|width
operator|-
name|private
operator|->
name|old_width
operator|)
operator|/
literal|2
argument_list|)
expr_stmt|;
name|off_y
operator|=
name|resize_bound_off_y
argument_list|(
name|private
argument_list|,
operator|(
name|box
operator|->
name|height
operator|-
name|private
operator|->
name|old_height
operator|)
operator|/
literal|2
argument_list|)
expr_stmt|;
name|gimp_size_entry_set_refval
argument_list|(
name|GIMP_SIZE_ENTRY
argument_list|(
name|private
operator|->
name|offset
argument_list|)
argument_list|,
literal|0
argument_list|,
name|off_x
argument_list|)
expr_stmt|;
name|gimp_size_entry_set_refval
argument_list|(
name|GIMP_SIZE_ENTRY
argument_list|(
name|private
operator|->
name|offset
argument_list|)
argument_list|,
literal|1
argument_list|,
name|off_y
argument_list|)
expr_stmt|;
name|g_signal_emit_by_name
argument_list|(
name|private
operator|->
name|offset
argument_list|,
literal|"value-changed"
argument_list|,
literal|0
argument_list|)
expr_stmt|;
block|}
end_function

end_unit

