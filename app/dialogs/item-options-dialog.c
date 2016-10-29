begin_unit|revision:0.9.5;language:C;cregit-version:0.0.1
begin_comment
comment|/* GIMP - The GNU Image Manipulation Program  * Copyright (C) 1995 Spencer Kimball and Peter Mattis  *  * This program is free software: you can redistribute it and/or modify  * it under the terms of the GNU General Public License as published by  * the Free Software Foundation; either version 3 of the License, or  * (at your option) any later version.  *  * This program is distributed in the hope that it will be useful,  * but WITHOUT ANY WARRANTY; without even the implied warranty of  * MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the  * GNU General Public License for more details.  *  * You should have received a copy of the GNU General Public License  * along with this program.  If not, see<http://www.gnu.org/licenses/>.  */
end_comment

begin_include
include|#
directive|include
file|"config.h"
end_include

begin_include
include|#
directive|include
file|<gegl.h>
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
file|"core/gimpitem.h"
end_include

begin_include
include|#
directive|include
file|"widgets/gimpviewabledialog.h"
end_include

begin_include
include|#
directive|include
file|"widgets/gimpwidgets-utils.h"
end_include

begin_include
include|#
directive|include
file|"item-options-dialog.h"
end_include

begin_include
include|#
directive|include
file|"gimp-intl.h"
end_include

begin_typedef
DECL|typedef|ItemOptionsDialog
typedef|typedef
name|struct
name|_ItemOptionsDialog
name|ItemOptionsDialog
typedef|;
end_typedef

begin_struct
DECL|struct|_ItemOptionsDialog
struct|struct
name|_ItemOptionsDialog
block|{
DECL|member|image
name|GimpImage
modifier|*
name|image
decl_stmt|;
DECL|member|item
name|GimpItem
modifier|*
name|item
decl_stmt|;
DECL|member|context
name|GimpContext
modifier|*
name|context
decl_stmt|;
DECL|member|visible
name|gboolean
name|visible
decl_stmt|;
DECL|member|linked
name|gboolean
name|linked
decl_stmt|;
DECL|member|color_tag
name|GimpColorTag
name|color_tag
decl_stmt|;
DECL|member|lock_content
name|gboolean
name|lock_content
decl_stmt|;
DECL|member|lock_position
name|gboolean
name|lock_position
decl_stmt|;
DECL|member|callback
name|GimpItemOptionsCallback
name|callback
decl_stmt|;
DECL|member|user_data
name|gpointer
name|user_data
decl_stmt|;
DECL|member|left_vbox
name|GtkWidget
modifier|*
name|left_vbox
decl_stmt|;
DECL|member|left_table
name|GtkWidget
modifier|*
name|left_table
decl_stmt|;
DECL|member|table_row
name|gint
name|table_row
decl_stmt|;
DECL|member|name_entry
name|GtkWidget
modifier|*
name|name_entry
decl_stmt|;
DECL|member|right_frame
name|GtkWidget
modifier|*
name|right_frame
decl_stmt|;
DECL|member|right_vbox
name|GtkWidget
modifier|*
name|right_vbox
decl_stmt|;
DECL|member|lock_position_toggle
name|GtkWidget
modifier|*
name|lock_position_toggle
decl_stmt|;
block|}
struct|;
end_struct

begin_comment
comment|/*  local function prototypes  */
end_comment

begin_function_decl
specifier|static
name|void
name|item_options_dialog_free
parameter_list|(
name|ItemOptionsDialog
modifier|*
name|private
parameter_list|)
function_decl|;
end_function_decl

begin_function_decl
specifier|static
name|void
name|item_options_dialog_response
parameter_list|(
name|GtkWidget
modifier|*
name|dialog
parameter_list|,
name|gint
name|response_id
parameter_list|,
name|ItemOptionsDialog
modifier|*
name|private
parameter_list|)
function_decl|;
end_function_decl

begin_function_decl
specifier|static
name|GtkWidget
modifier|*
name|check_button_with_icon_new
parameter_list|(
specifier|const
name|gchar
modifier|*
name|label
parameter_list|,
specifier|const
name|gchar
modifier|*
name|icon_name
parameter_list|,
name|GtkBox
modifier|*
name|vbox
parameter_list|)
function_decl|;
end_function_decl

begin_comment
comment|/*  public functions  */
end_comment

begin_function
name|GtkWidget
modifier|*
DECL|function|item_options_dialog_new (GimpImage * image,GimpItem * item,GimpContext * context,GtkWidget * parent,const gchar * title,const gchar * role,const gchar * icon_name,const gchar * desc,const gchar * help_id,const gchar * name_label,const gchar * lock_content_icon_name,const gchar * lock_content_label,const gchar * lock_position_label,const gchar * item_name,gboolean item_visible,gboolean item_linked,GimpColorTag item_color_tag,gboolean item_lock_content,gboolean item_lock_position,GimpItemOptionsCallback callback,gpointer user_data)
name|item_options_dialog_new
parameter_list|(
name|GimpImage
modifier|*
name|image
parameter_list|,
name|GimpItem
modifier|*
name|item
parameter_list|,
name|GimpContext
modifier|*
name|context
parameter_list|,
name|GtkWidget
modifier|*
name|parent
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
specifier|const
name|gchar
modifier|*
name|icon_name
parameter_list|,
specifier|const
name|gchar
modifier|*
name|desc
parameter_list|,
specifier|const
name|gchar
modifier|*
name|help_id
parameter_list|,
specifier|const
name|gchar
modifier|*
name|name_label
parameter_list|,
specifier|const
name|gchar
modifier|*
name|lock_content_icon_name
parameter_list|,
specifier|const
name|gchar
modifier|*
name|lock_content_label
parameter_list|,
specifier|const
name|gchar
modifier|*
name|lock_position_label
parameter_list|,
specifier|const
name|gchar
modifier|*
name|item_name
parameter_list|,
name|gboolean
name|item_visible
parameter_list|,
name|gboolean
name|item_linked
parameter_list|,
name|GimpColorTag
name|item_color_tag
parameter_list|,
name|gboolean
name|item_lock_content
parameter_list|,
name|gboolean
name|item_lock_position
parameter_list|,
name|GimpItemOptionsCallback
name|callback
parameter_list|,
name|gpointer
name|user_data
parameter_list|)
block|{
name|ItemOptionsDialog
modifier|*
name|private
decl_stmt|;
name|GtkWidget
modifier|*
name|dialog
decl_stmt|;
name|GimpViewable
modifier|*
name|viewable
decl_stmt|;
name|GtkWidget
modifier|*
name|main_hbox
decl_stmt|;
name|GtkWidget
modifier|*
name|table
decl_stmt|;
name|GtkWidget
modifier|*
name|button
decl_stmt|;
name|g_return_val_if_fail
argument_list|(
name|GIMP_IS_IMAGE
argument_list|(
name|image
argument_list|)
argument_list|,
name|NULL
argument_list|)
expr_stmt|;
name|g_return_val_if_fail
argument_list|(
name|item
operator|==
name|NULL
operator|||
name|GIMP_IS_ITEM
argument_list|(
name|item
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
name|GTK_IS_WIDGET
argument_list|(
name|parent
argument_list|)
argument_list|,
name|NULL
argument_list|)
expr_stmt|;
name|g_return_val_if_fail
argument_list|(
name|title
operator|!=
name|NULL
argument_list|,
name|NULL
argument_list|)
expr_stmt|;
name|g_return_val_if_fail
argument_list|(
name|role
operator|!=
name|NULL
argument_list|,
name|NULL
argument_list|)
expr_stmt|;
name|g_return_val_if_fail
argument_list|(
name|icon_name
operator|!=
name|NULL
argument_list|,
name|NULL
argument_list|)
expr_stmt|;
name|g_return_val_if_fail
argument_list|(
name|desc
operator|!=
name|NULL
argument_list|,
name|NULL
argument_list|)
expr_stmt|;
name|g_return_val_if_fail
argument_list|(
name|help_id
operator|!=
name|NULL
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
name|private
operator|=
name|g_slice_new0
argument_list|(
name|ItemOptionsDialog
argument_list|)
expr_stmt|;
name|private
operator|->
name|image
operator|=
name|image
expr_stmt|;
name|private
operator|->
name|item
operator|=
name|item
expr_stmt|;
name|private
operator|->
name|context
operator|=
name|context
expr_stmt|;
name|private
operator|->
name|visible
operator|=
name|item_visible
expr_stmt|;
name|private
operator|->
name|linked
operator|=
name|item_linked
expr_stmt|;
name|private
operator|->
name|color_tag
operator|=
name|item_color_tag
expr_stmt|;
name|private
operator|->
name|lock_content
operator|=
name|item_lock_content
expr_stmt|;
name|private
operator|->
name|lock_position
operator|=
name|item_lock_position
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
if|if
condition|(
name|item
condition|)
name|viewable
operator|=
name|GIMP_VIEWABLE
argument_list|(
name|item
argument_list|)
expr_stmt|;
else|else
name|viewable
operator|=
name|GIMP_VIEWABLE
argument_list|(
name|image
argument_list|)
expr_stmt|;
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
name|icon_name
argument_list|,
name|desc
argument_list|,
name|parent
argument_list|,
name|gimp_standard_help_func
argument_list|,
name|help_id
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
name|g_signal_connect
argument_list|(
name|dialog
argument_list|,
literal|"response"
argument_list|,
name|G_CALLBACK
argument_list|(
name|item_options_dialog_response
argument_list|)
argument_list|,
name|private
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
name|item_options_dialog_free
argument_list|,
name|private
argument_list|)
expr_stmt|;
name|g_object_set_data
argument_list|(
name|G_OBJECT
argument_list|(
name|dialog
argument_list|)
argument_list|,
literal|"item-options-dialog-private"
argument_list|,
name|private
argument_list|)
expr_stmt|;
name|main_hbox
operator|=
name|gtk_box_new
argument_list|(
name|GTK_ORIENTATION_HORIZONTAL
argument_list|,
literal|12
argument_list|)
expr_stmt|;
name|gtk_container_set_border_width
argument_list|(
name|GTK_CONTAINER
argument_list|(
name|main_hbox
argument_list|)
argument_list|,
literal|12
argument_list|)
expr_stmt|;
name|gtk_box_pack_start
argument_list|(
name|GTK_BOX
argument_list|(
name|gtk_dialog_get_content_area
argument_list|(
name|GTK_DIALOG
argument_list|(
name|dialog
argument_list|)
argument_list|)
argument_list|)
argument_list|,
name|main_hbox
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
name|main_hbox
argument_list|)
expr_stmt|;
name|private
operator|->
name|left_vbox
operator|=
name|gtk_box_new
argument_list|(
name|GTK_ORIENTATION_VERTICAL
argument_list|,
literal|12
argument_list|)
expr_stmt|;
name|gtk_box_pack_start
argument_list|(
name|GTK_BOX
argument_list|(
name|main_hbox
argument_list|)
argument_list|,
name|private
operator|->
name|left_vbox
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
name|private
operator|->
name|left_vbox
argument_list|)
expr_stmt|;
name|private
operator|->
name|left_table
operator|=
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
name|gtk_table_set_col_spacings
argument_list|(
name|GTK_TABLE
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
literal|6
argument_list|)
expr_stmt|;
name|gtk_box_pack_start
argument_list|(
name|GTK_BOX
argument_list|(
name|private
operator|->
name|left_vbox
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
comment|/*  The name label and entry  */
if|if
condition|(
name|name_label
condition|)
block|{
name|GtkWidget
modifier|*
name|hbox
decl_stmt|;
name|GtkWidget
modifier|*
name|radio
decl_stmt|;
name|GtkWidget
modifier|*
name|radio_box
decl_stmt|;
name|GList
modifier|*
name|children
decl_stmt|;
name|GList
modifier|*
name|list
decl_stmt|;
name|private
operator|->
name|name_entry
operator|=
name|gtk_entry_new
argument_list|()
expr_stmt|;
name|gtk_entry_set_activates_default
argument_list|(
name|GTK_ENTRY
argument_list|(
name|private
operator|->
name|name_entry
argument_list|)
argument_list|,
name|TRUE
argument_list|)
expr_stmt|;
name|gtk_entry_set_text
argument_list|(
name|GTK_ENTRY
argument_list|(
name|private
operator|->
name|name_entry
argument_list|)
argument_list|,
name|item_name
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
name|private
operator|->
name|table_row
operator|++
argument_list|,
name|name_label
argument_list|,
literal|0.0
argument_list|,
literal|0.5
argument_list|,
name|private
operator|->
name|name_entry
argument_list|,
literal|1
argument_list|,
name|FALSE
argument_list|)
expr_stmt|;
name|hbox
operator|=
name|gtk_box_new
argument_list|(
name|GTK_ORIENTATION_HORIZONTAL
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
name|private
operator|->
name|table_row
operator|++
argument_list|,
name|_
argument_list|(
literal|"Color tag:"
argument_list|)
argument_list|,
literal|0.0
argument_list|,
literal|0.5
argument_list|,
name|hbox
argument_list|,
literal|1
argument_list|,
name|TRUE
argument_list|)
expr_stmt|;
name|radio_box
operator|=
name|gimp_enum_radio_box_new
argument_list|(
name|GIMP_TYPE_COLOR_TAG
argument_list|,
name|G_CALLBACK
argument_list|(
name|gimp_radio_button_update
argument_list|)
argument_list|,
operator|&
name|private
operator|->
name|color_tag
argument_list|,
operator|&
name|radio
argument_list|)
expr_stmt|;
name|gimp_int_radio_group_set_active
argument_list|(
name|GTK_RADIO_BUTTON
argument_list|(
name|radio
argument_list|)
argument_list|,
name|private
operator|->
name|color_tag
argument_list|)
expr_stmt|;
name|children
operator|=
name|gtk_container_get_children
argument_list|(
name|GTK_CONTAINER
argument_list|(
name|radio_box
argument_list|)
argument_list|)
expr_stmt|;
for|for
control|(
name|list
operator|=
name|children
init|;
name|list
condition|;
name|list
operator|=
name|g_list_next
argument_list|(
name|list
argument_list|)
control|)
block|{
name|GimpColorTag
name|color_tag
decl_stmt|;
name|GimpRGB
name|color
decl_stmt|;
name|GtkWidget
modifier|*
name|image
decl_stmt|;
name|radio
operator|=
name|list
operator|->
name|data
expr_stmt|;
name|g_object_ref
argument_list|(
name|radio
argument_list|)
expr_stmt|;
name|gtk_container_remove
argument_list|(
name|GTK_CONTAINER
argument_list|(
name|radio_box
argument_list|)
argument_list|,
name|radio
argument_list|)
expr_stmt|;
name|g_object_set
argument_list|(
name|radio
argument_list|,
literal|"draw-indicator"
argument_list|,
name|FALSE
argument_list|,
name|NULL
argument_list|)
expr_stmt|;
name|gtk_box_pack_start
argument_list|(
name|GTK_BOX
argument_list|(
name|hbox
argument_list|)
argument_list|,
name|radio
argument_list|,
name|FALSE
argument_list|,
name|FALSE
argument_list|,
literal|0
argument_list|)
expr_stmt|;
name|g_object_unref
argument_list|(
name|radio
argument_list|)
expr_stmt|;
name|gtk_widget_destroy
argument_list|(
name|gtk_bin_get_child
argument_list|(
name|GTK_BIN
argument_list|(
name|radio
argument_list|)
argument_list|)
argument_list|)
expr_stmt|;
name|color_tag
operator|=
name|GPOINTER_TO_INT
argument_list|(
name|g_object_get_data
argument_list|(
name|G_OBJECT
argument_list|(
name|radio
argument_list|)
argument_list|,
literal|"gimp-item-data"
argument_list|)
argument_list|)
expr_stmt|;
if|if
condition|(
name|gimp_get_color_tag_color
argument_list|(
name|color_tag
argument_list|,
operator|&
name|color
argument_list|)
condition|)
block|{
name|GtkSettings
modifier|*
name|settings
init|=
name|gtk_widget_get_settings
argument_list|(
name|dialog
argument_list|)
decl_stmt|;
name|gint
name|w
decl_stmt|,
name|h
decl_stmt|;
name|image
operator|=
name|gimp_color_area_new
argument_list|(
operator|&
name|color
argument_list|,
name|GIMP_COLOR_AREA_FLAT
argument_list|,
literal|0
argument_list|)
expr_stmt|;
name|gtk_icon_size_lookup_for_settings
argument_list|(
name|settings
argument_list|,
name|GTK_ICON_SIZE_MENU
argument_list|,
operator|&
name|w
argument_list|,
operator|&
name|h
argument_list|)
expr_stmt|;
name|gtk_widget_set_size_request
argument_list|(
name|image
argument_list|,
name|w
argument_list|,
name|h
argument_list|)
expr_stmt|;
block|}
else|else
block|{
name|image
operator|=
name|gtk_image_new_from_icon_name
argument_list|(
name|GIMP_STOCK_CLOSE
argument_list|,
name|GTK_ICON_SIZE_MENU
argument_list|)
expr_stmt|;
block|}
name|gtk_container_add
argument_list|(
name|GTK_CONTAINER
argument_list|(
name|radio
argument_list|)
argument_list|,
name|image
argument_list|)
expr_stmt|;
name|gtk_widget_show
argument_list|(
name|image
argument_list|)
expr_stmt|;
block|}
name|g_list_free
argument_list|(
name|children
argument_list|)
expr_stmt|;
name|gtk_widget_destroy
argument_list|(
name|radio_box
argument_list|)
expr_stmt|;
block|}
comment|/*  The switches frame& vbox  */
name|private
operator|->
name|right_frame
operator|=
name|gimp_frame_new
argument_list|(
name|_
argument_list|(
literal|"Switches"
argument_list|)
argument_list|)
expr_stmt|;
name|gtk_box_pack_start
argument_list|(
name|GTK_BOX
argument_list|(
name|main_hbox
argument_list|)
argument_list|,
name|private
operator|->
name|right_frame
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
name|private
operator|->
name|right_frame
argument_list|)
expr_stmt|;
name|private
operator|->
name|right_vbox
operator|=
name|gtk_box_new
argument_list|(
name|GTK_ORIENTATION_VERTICAL
argument_list|,
literal|6
argument_list|)
expr_stmt|;
name|gtk_container_add
argument_list|(
name|GTK_CONTAINER
argument_list|(
name|private
operator|->
name|right_frame
argument_list|)
argument_list|,
name|private
operator|->
name|right_vbox
argument_list|)
expr_stmt|;
name|gtk_widget_show
argument_list|(
name|private
operator|->
name|right_vbox
argument_list|)
expr_stmt|;
name|button
operator|=
name|check_button_with_icon_new
argument_list|(
name|_
argument_list|(
literal|"_Visible"
argument_list|)
argument_list|,
name|GIMP_STOCK_VISIBLE
argument_list|,
name|GTK_BOX
argument_list|(
name|private
operator|->
name|right_vbox
argument_list|)
argument_list|)
expr_stmt|;
name|gtk_toggle_button_set_active
argument_list|(
name|GTK_TOGGLE_BUTTON
argument_list|(
name|button
argument_list|)
argument_list|,
name|private
operator|->
name|visible
argument_list|)
expr_stmt|;
name|g_signal_connect
argument_list|(
name|button
argument_list|,
literal|"toggled"
argument_list|,
name|G_CALLBACK
argument_list|(
name|gimp_toggle_button_update
argument_list|)
argument_list|,
operator|&
name|private
operator|->
name|visible
argument_list|)
expr_stmt|;
name|button
operator|=
name|check_button_with_icon_new
argument_list|(
name|_
argument_list|(
literal|"_Linked"
argument_list|)
argument_list|,
name|GIMP_STOCK_LINKED
argument_list|,
name|GTK_BOX
argument_list|(
name|private
operator|->
name|right_vbox
argument_list|)
argument_list|)
expr_stmt|;
name|gtk_toggle_button_set_active
argument_list|(
name|GTK_TOGGLE_BUTTON
argument_list|(
name|button
argument_list|)
argument_list|,
name|private
operator|->
name|linked
argument_list|)
expr_stmt|;
name|g_signal_connect
argument_list|(
name|button
argument_list|,
literal|"toggled"
argument_list|,
name|G_CALLBACK
argument_list|(
name|gimp_toggle_button_update
argument_list|)
argument_list|,
operator|&
name|private
operator|->
name|linked
argument_list|)
expr_stmt|;
name|button
operator|=
name|check_button_with_icon_new
argument_list|(
name|lock_content_label
argument_list|,
name|lock_content_icon_name
argument_list|,
name|GTK_BOX
argument_list|(
name|private
operator|->
name|right_vbox
argument_list|)
argument_list|)
expr_stmt|;
name|gtk_toggle_button_set_active
argument_list|(
name|GTK_TOGGLE_BUTTON
argument_list|(
name|button
argument_list|)
argument_list|,
name|private
operator|->
name|lock_content
argument_list|)
expr_stmt|;
name|g_signal_connect
argument_list|(
name|button
argument_list|,
literal|"toggled"
argument_list|,
name|G_CALLBACK
argument_list|(
name|gimp_toggle_button_update
argument_list|)
argument_list|,
operator|&
name|private
operator|->
name|lock_content
argument_list|)
expr_stmt|;
name|button
operator|=
name|check_button_with_icon_new
argument_list|(
name|lock_position_label
argument_list|,
name|GIMP_STOCK_TOOL_MOVE
argument_list|,
name|GTK_BOX
argument_list|(
name|private
operator|->
name|right_vbox
argument_list|)
argument_list|)
expr_stmt|;
name|gtk_toggle_button_set_active
argument_list|(
name|GTK_TOGGLE_BUTTON
argument_list|(
name|button
argument_list|)
argument_list|,
name|private
operator|->
name|lock_position
argument_list|)
expr_stmt|;
name|g_signal_connect
argument_list|(
name|button
argument_list|,
literal|"toggled"
argument_list|,
name|G_CALLBACK
argument_list|(
name|gimp_toggle_button_update
argument_list|)
argument_list|,
operator|&
name|private
operator|->
name|lock_position
argument_list|)
expr_stmt|;
name|private
operator|->
name|lock_position_toggle
operator|=
name|button
expr_stmt|;
return|return
name|dialog
return|;
block|}
end_function

begin_function
name|GtkWidget
modifier|*
DECL|function|item_options_dialog_get_vbox (GtkWidget * dialog)
name|item_options_dialog_get_vbox
parameter_list|(
name|GtkWidget
modifier|*
name|dialog
parameter_list|)
block|{
name|ItemOptionsDialog
modifier|*
name|private
decl_stmt|;
name|g_return_val_if_fail
argument_list|(
name|GIMP_IS_VIEWABLE_DIALOG
argument_list|(
name|dialog
argument_list|)
argument_list|,
name|NULL
argument_list|)
expr_stmt|;
name|private
operator|=
name|g_object_get_data
argument_list|(
name|G_OBJECT
argument_list|(
name|dialog
argument_list|)
argument_list|,
literal|"item-options-dialog-private"
argument_list|)
expr_stmt|;
name|g_return_val_if_fail
argument_list|(
name|private
operator|!=
name|NULL
argument_list|,
name|NULL
argument_list|)
expr_stmt|;
return|return
name|private
operator|->
name|left_vbox
return|;
block|}
end_function

begin_function
name|GtkWidget
modifier|*
DECL|function|item_options_dialog_get_table (GtkWidget * dialog,gint * next_row)
name|item_options_dialog_get_table
parameter_list|(
name|GtkWidget
modifier|*
name|dialog
parameter_list|,
name|gint
modifier|*
name|next_row
parameter_list|)
block|{
name|ItemOptionsDialog
modifier|*
name|private
decl_stmt|;
name|g_return_val_if_fail
argument_list|(
name|GIMP_IS_VIEWABLE_DIALOG
argument_list|(
name|dialog
argument_list|)
argument_list|,
name|NULL
argument_list|)
expr_stmt|;
name|g_return_val_if_fail
argument_list|(
name|next_row
operator|!=
name|NULL
argument_list|,
name|NULL
argument_list|)
expr_stmt|;
name|private
operator|=
name|g_object_get_data
argument_list|(
name|G_OBJECT
argument_list|(
name|dialog
argument_list|)
argument_list|,
literal|"item-options-dialog-private"
argument_list|)
expr_stmt|;
name|g_return_val_if_fail
argument_list|(
name|private
operator|!=
name|NULL
argument_list|,
name|NULL
argument_list|)
expr_stmt|;
operator|*
name|next_row
operator|=
name|private
operator|->
name|table_row
expr_stmt|;
return|return
name|private
operator|->
name|left_table
return|;
block|}
end_function

begin_function
name|GtkWidget
modifier|*
DECL|function|item_options_dialog_get_name_entry (GtkWidget * dialog)
name|item_options_dialog_get_name_entry
parameter_list|(
name|GtkWidget
modifier|*
name|dialog
parameter_list|)
block|{
name|ItemOptionsDialog
modifier|*
name|private
decl_stmt|;
name|g_return_val_if_fail
argument_list|(
name|GIMP_IS_VIEWABLE_DIALOG
argument_list|(
name|dialog
argument_list|)
argument_list|,
name|NULL
argument_list|)
expr_stmt|;
name|private
operator|=
name|g_object_get_data
argument_list|(
name|G_OBJECT
argument_list|(
name|dialog
argument_list|)
argument_list|,
literal|"item-options-dialog-private"
argument_list|)
expr_stmt|;
name|g_return_val_if_fail
argument_list|(
name|private
operator|!=
name|NULL
argument_list|,
name|NULL
argument_list|)
expr_stmt|;
return|return
name|private
operator|->
name|name_entry
return|;
block|}
end_function

begin_function
name|GtkWidget
modifier|*
DECL|function|item_options_dialog_get_lock_position (GtkWidget * dialog)
name|item_options_dialog_get_lock_position
parameter_list|(
name|GtkWidget
modifier|*
name|dialog
parameter_list|)
block|{
name|ItemOptionsDialog
modifier|*
name|private
decl_stmt|;
name|g_return_val_if_fail
argument_list|(
name|GIMP_IS_VIEWABLE_DIALOG
argument_list|(
name|dialog
argument_list|)
argument_list|,
name|NULL
argument_list|)
expr_stmt|;
name|private
operator|=
name|g_object_get_data
argument_list|(
name|G_OBJECT
argument_list|(
name|dialog
argument_list|)
argument_list|,
literal|"item-options-dialog-private"
argument_list|)
expr_stmt|;
name|g_return_val_if_fail
argument_list|(
name|private
operator|!=
name|NULL
argument_list|,
name|NULL
argument_list|)
expr_stmt|;
return|return
name|private
operator|->
name|lock_position_toggle
return|;
block|}
end_function

begin_function
name|void
DECL|function|item_options_dialog_add_widget (GtkWidget * dialog,const gchar * label,GtkWidget * widget)
name|item_options_dialog_add_widget
parameter_list|(
name|GtkWidget
modifier|*
name|dialog
parameter_list|,
specifier|const
name|gchar
modifier|*
name|label
parameter_list|,
name|GtkWidget
modifier|*
name|widget
parameter_list|)
block|{
name|ItemOptionsDialog
modifier|*
name|private
decl_stmt|;
name|g_return_if_fail
argument_list|(
name|GIMP_IS_VIEWABLE_DIALOG
argument_list|(
name|dialog
argument_list|)
argument_list|)
expr_stmt|;
name|g_return_if_fail
argument_list|(
name|GTK_IS_WIDGET
argument_list|(
name|widget
argument_list|)
argument_list|)
expr_stmt|;
name|private
operator|=
name|g_object_get_data
argument_list|(
name|G_OBJECT
argument_list|(
name|dialog
argument_list|)
argument_list|,
literal|"item-options-dialog-private"
argument_list|)
expr_stmt|;
name|g_return_if_fail
argument_list|(
name|private
operator|!=
name|NULL
argument_list|)
expr_stmt|;
name|gimp_table_attach_aligned
argument_list|(
name|GTK_TABLE
argument_list|(
name|private
operator|->
name|left_table
argument_list|)
argument_list|,
literal|0
argument_list|,
name|private
operator|->
name|table_row
operator|++
argument_list|,
name|label
argument_list|,
literal|0.0
argument_list|,
literal|0.5
argument_list|,
name|widget
argument_list|,
literal|1
argument_list|,
name|FALSE
argument_list|)
expr_stmt|;
block|}
end_function

begin_function
name|GtkWidget
modifier|*
DECL|function|item_options_dialog_add_switch (GtkWidget * dialog,const gchar * icon_name,const gchar * label)
name|item_options_dialog_add_switch
parameter_list|(
name|GtkWidget
modifier|*
name|dialog
parameter_list|,
specifier|const
name|gchar
modifier|*
name|icon_name
parameter_list|,
specifier|const
name|gchar
modifier|*
name|label
parameter_list|)
block|{
name|ItemOptionsDialog
modifier|*
name|private
decl_stmt|;
name|g_return_val_if_fail
argument_list|(
name|GIMP_IS_VIEWABLE_DIALOG
argument_list|(
name|dialog
argument_list|)
argument_list|,
name|NULL
argument_list|)
expr_stmt|;
name|g_return_val_if_fail
argument_list|(
name|icon_name
operator|!=
name|NULL
argument_list|,
name|NULL
argument_list|)
expr_stmt|;
name|g_return_val_if_fail
argument_list|(
name|label
operator|!=
name|NULL
argument_list|,
name|NULL
argument_list|)
expr_stmt|;
name|private
operator|=
name|g_object_get_data
argument_list|(
name|G_OBJECT
argument_list|(
name|dialog
argument_list|)
argument_list|,
literal|"item-options-dialog-private"
argument_list|)
expr_stmt|;
name|g_return_val_if_fail
argument_list|(
name|private
operator|!=
name|NULL
argument_list|,
name|NULL
argument_list|)
expr_stmt|;
return|return
name|check_button_with_icon_new
argument_list|(
name|label
argument_list|,
name|icon_name
argument_list|,
name|GTK_BOX
argument_list|(
name|private
operator|->
name|right_vbox
argument_list|)
argument_list|)
return|;
block|}
end_function

begin_function
name|void
DECL|function|item_options_dialog_set_switches_visible (GtkWidget * dialog,gboolean visible)
name|item_options_dialog_set_switches_visible
parameter_list|(
name|GtkWidget
modifier|*
name|dialog
parameter_list|,
name|gboolean
name|visible
parameter_list|)
block|{
name|ItemOptionsDialog
modifier|*
name|private
decl_stmt|;
name|g_return_if_fail
argument_list|(
name|GIMP_IS_VIEWABLE_DIALOG
argument_list|(
name|dialog
argument_list|)
argument_list|)
expr_stmt|;
name|private
operator|=
name|g_object_get_data
argument_list|(
name|G_OBJECT
argument_list|(
name|dialog
argument_list|)
argument_list|,
literal|"item-options-dialog-private"
argument_list|)
expr_stmt|;
name|g_return_if_fail
argument_list|(
name|private
operator|!=
name|NULL
argument_list|)
expr_stmt|;
name|gtk_widget_set_visible
argument_list|(
name|private
operator|->
name|right_frame
argument_list|,
name|visible
argument_list|)
expr_stmt|;
block|}
end_function

begin_comment
comment|/*  private functions  */
end_comment

begin_function
specifier|static
name|void
DECL|function|item_options_dialog_free (ItemOptionsDialog * private)
name|item_options_dialog_free
parameter_list|(
name|ItemOptionsDialog
modifier|*
name|private
parameter_list|)
block|{
name|g_slice_free
argument_list|(
name|ItemOptionsDialog
argument_list|,
name|private
argument_list|)
expr_stmt|;
block|}
end_function

begin_function
specifier|static
name|void
DECL|function|item_options_dialog_response (GtkWidget * dialog,gint response_id,ItemOptionsDialog * private)
name|item_options_dialog_response
parameter_list|(
name|GtkWidget
modifier|*
name|dialog
parameter_list|,
name|gint
name|response_id
parameter_list|,
name|ItemOptionsDialog
modifier|*
name|private
parameter_list|)
block|{
if|if
condition|(
name|response_id
operator|==
name|GTK_RESPONSE_OK
condition|)
block|{
specifier|const
name|gchar
modifier|*
name|name
init|=
name|NULL
decl_stmt|;
if|if
condition|(
name|private
operator|->
name|name_entry
condition|)
name|name
operator|=
name|gtk_entry_get_text
argument_list|(
name|GTK_ENTRY
argument_list|(
name|private
operator|->
name|name_entry
argument_list|)
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
name|image
argument_list|,
name|private
operator|->
name|item
argument_list|,
name|private
operator|->
name|context
argument_list|,
name|name
argument_list|,
name|private
operator|->
name|visible
argument_list|,
name|private
operator|->
name|linked
argument_list|,
name|private
operator|->
name|color_tag
argument_list|,
name|private
operator|->
name|lock_content
argument_list|,
name|private
operator|->
name|lock_position
argument_list|,
name|private
operator|->
name|user_data
argument_list|)
expr_stmt|;
block|}
else|else
block|{
name|gtk_widget_destroy
argument_list|(
name|dialog
argument_list|)
expr_stmt|;
block|}
block|}
end_function

begin_function
specifier|static
name|GtkWidget
modifier|*
DECL|function|check_button_with_icon_new (const gchar * label,const gchar * icon_name,GtkBox * vbox)
name|check_button_with_icon_new
parameter_list|(
specifier|const
name|gchar
modifier|*
name|label
parameter_list|,
specifier|const
name|gchar
modifier|*
name|icon_name
parameter_list|,
name|GtkBox
modifier|*
name|vbox
parameter_list|)
block|{
name|GtkWidget
modifier|*
name|hbox
decl_stmt|;
name|GtkWidget
modifier|*
name|button
decl_stmt|;
name|GtkWidget
modifier|*
name|image
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
name|gtk_box_pack_start
argument_list|(
name|vbox
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
name|image
operator|=
name|gtk_image_new_from_icon_name
argument_list|(
name|icon_name
argument_list|,
name|GTK_ICON_SIZE_BUTTON
argument_list|)
expr_stmt|;
name|gtk_box_pack_start
argument_list|(
name|GTK_BOX
argument_list|(
name|hbox
argument_list|)
argument_list|,
name|image
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
name|image
argument_list|)
expr_stmt|;
name|button
operator|=
name|gtk_check_button_new_with_mnemonic
argument_list|(
name|label
argument_list|)
expr_stmt|;
name|gtk_box_pack_start
argument_list|(
name|GTK_BOX
argument_list|(
name|hbox
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
return|return
name|button
return|;
block|}
end_function

end_unit

