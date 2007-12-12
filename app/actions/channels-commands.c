begin_unit|revision:0.9.5;language:C;cregit-version:0.0.1
begin_comment
comment|/* GIMP - The GNU Image Manipulation Program  * Copyright (C) 1995 Spencer Kimball and Peter Mattis  *  * This program is free software; you can redistribute it and/or modify  * it under the terms of the GNU General Public License as published by  * the Free Software Foundation; either version 2 of the License, or  * (at your option) any later version.  *  * This program is distributed in the hope that it will be useful,  * but WITHOUT ANY WARRANTY; without even the implied warranty of  * MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the  * GNU General Public License for more details.  *  * You should have received a copy of the GNU General Public License  * along with this program; if not, write to the Free Software  * Foundation, Inc., 59 Temple Place - Suite 330, Boston, MA 02111-1307, USA.  */
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
file|"libgimpcolor/gimpcolor.h"
end_include

begin_include
include|#
directive|include
file|"libgimpwidgets/gimpwidgets.h"
end_include

begin_include
include|#
directive|include
file|"actions-types.h"
end_include

begin_include
include|#
directive|include
file|"core/gimpchannel.h"
end_include

begin_include
include|#
directive|include
file|"core/gimpchannel-select.h"
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
file|"core/gimpimage-undo.h"
end_include

begin_include
include|#
directive|include
file|"widgets/gimpaction.h"
end_include

begin_include
include|#
directive|include
file|"widgets/gimpcolorpanel.h"
end_include

begin_include
include|#
directive|include
file|"widgets/gimpcomponenteditor.h"
end_include

begin_include
include|#
directive|include
file|"widgets/gimpdock.h"
end_include

begin_include
include|#
directive|include
file|"widgets/gimphelp-ids.h"
end_include

begin_include
include|#
directive|include
file|"dialogs/channel-options-dialog.h"
end_include

begin_include
include|#
directive|include
file|"actions.h"
end_include

begin_include
include|#
directive|include
file|"channels-commands.h"
end_include

begin_include
include|#
directive|include
file|"gimp-intl.h"
end_include

begin_comment
comment|/*  local function prototypes  */
end_comment

begin_function_decl
specifier|static
name|void
name|channels_new_channel_response
parameter_list|(
name|GtkWidget
modifier|*
name|widget
parameter_list|,
name|gint
name|response_id
parameter_list|,
name|ChannelOptionsDialog
modifier|*
name|options
parameter_list|)
function_decl|;
end_function_decl

begin_function_decl
specifier|static
name|void
name|channels_edit_channel_response
parameter_list|(
name|GtkWidget
modifier|*
name|widget
parameter_list|,
name|gint
name|response_id
parameter_list|,
name|ChannelOptionsDialog
modifier|*
name|options
parameter_list|)
function_decl|;
end_function_decl

begin_comment
comment|/*  private variables  */
end_comment

begin_decl_stmt
DECL|variable|channel_name
specifier|static
name|gchar
modifier|*
name|channel_name
init|=
name|NULL
decl_stmt|;
end_decl_stmt

begin_decl_stmt
DECL|variable|channel_color
specifier|static
name|GimpRGB
name|channel_color
init|=
block|{
literal|0.0
block|,
literal|0.0
block|,
literal|0.0
block|,
literal|0.5
block|}
decl_stmt|;
end_decl_stmt

begin_comment
comment|/*  public functions  */
end_comment

begin_function
name|void
DECL|function|channels_edit_attributes_cmd_callback (GtkAction * action,gpointer data)
name|channels_edit_attributes_cmd_callback
parameter_list|(
name|GtkAction
modifier|*
name|action
parameter_list|,
name|gpointer
name|data
parameter_list|)
block|{
name|ChannelOptionsDialog
modifier|*
name|options
decl_stmt|;
name|GimpImage
modifier|*
name|image
decl_stmt|;
name|GimpChannel
modifier|*
name|channel
decl_stmt|;
name|GtkWidget
modifier|*
name|widget
decl_stmt|;
name|return_if_no_channel
argument_list|(
name|image
argument_list|,
name|channel
argument_list|,
name|data
argument_list|)
expr_stmt|;
name|return_if_no_widget
argument_list|(
name|widget
argument_list|,
name|data
argument_list|)
expr_stmt|;
name|options
operator|=
name|channel_options_dialog_new
argument_list|(
name|image
argument_list|,
name|channel
argument_list|,
name|action_data_get_context
argument_list|(
name|data
argument_list|)
argument_list|,
name|widget
argument_list|,
operator|&
name|channel
operator|->
name|color
argument_list|,
name|gimp_object_get_name
argument_list|(
name|GIMP_OBJECT
argument_list|(
name|channel
argument_list|)
argument_list|)
argument_list|,
name|_
argument_list|(
literal|"Channel Attributes"
argument_list|)
argument_list|,
literal|"gimp-channel-edit"
argument_list|,
name|GTK_STOCK_EDIT
argument_list|,
name|_
argument_list|(
literal|"Edit Channel Attributes"
argument_list|)
argument_list|,
name|GIMP_HELP_CHANNEL_EDIT
argument_list|,
name|_
argument_list|(
literal|"Edit Channel Color"
argument_list|)
argument_list|,
name|_
argument_list|(
literal|"_Fill opacity:"
argument_list|)
argument_list|,
name|FALSE
argument_list|)
expr_stmt|;
name|g_signal_connect
argument_list|(
name|options
operator|->
name|dialog
argument_list|,
literal|"response"
argument_list|,
name|G_CALLBACK
argument_list|(
name|channels_edit_channel_response
argument_list|)
argument_list|,
name|options
argument_list|)
expr_stmt|;
name|gtk_widget_show
argument_list|(
name|options
operator|->
name|dialog
argument_list|)
expr_stmt|;
block|}
end_function

begin_function
name|void
DECL|function|channels_new_cmd_callback (GtkAction * action,gpointer data)
name|channels_new_cmd_callback
parameter_list|(
name|GtkAction
modifier|*
name|action
parameter_list|,
name|gpointer
name|data
parameter_list|)
block|{
name|ChannelOptionsDialog
modifier|*
name|options
decl_stmt|;
name|GimpImage
modifier|*
name|image
decl_stmt|;
name|GtkWidget
modifier|*
name|widget
decl_stmt|;
name|return_if_no_image
argument_list|(
name|image
argument_list|,
name|data
argument_list|)
expr_stmt|;
name|return_if_no_widget
argument_list|(
name|widget
argument_list|,
name|data
argument_list|)
expr_stmt|;
name|options
operator|=
name|channel_options_dialog_new
argument_list|(
name|image
argument_list|,
name|NULL
argument_list|,
name|action_data_get_context
argument_list|(
name|data
argument_list|)
argument_list|,
name|widget
argument_list|,
operator|&
name|channel_color
argument_list|,
name|channel_name
condition|?
name|channel_name
else|:
name|_
argument_list|(
literal|"New Channel"
argument_list|)
argument_list|,
name|_
argument_list|(
literal|"New Channel"
argument_list|)
argument_list|,
literal|"gimp-channel-new"
argument_list|,
name|GIMP_STOCK_CHANNEL
argument_list|,
name|_
argument_list|(
literal|"New Channel Options"
argument_list|)
argument_list|,
name|GIMP_HELP_CHANNEL_NEW
argument_list|,
name|_
argument_list|(
literal|"New Channel Color"
argument_list|)
argument_list|,
name|_
argument_list|(
literal|"_Fill opacity:"
argument_list|)
argument_list|,
name|TRUE
argument_list|)
expr_stmt|;
name|g_signal_connect
argument_list|(
name|options
operator|->
name|dialog
argument_list|,
literal|"response"
argument_list|,
name|G_CALLBACK
argument_list|(
name|channels_new_channel_response
argument_list|)
argument_list|,
name|options
argument_list|)
expr_stmt|;
name|gtk_widget_show
argument_list|(
name|options
operator|->
name|dialog
argument_list|)
expr_stmt|;
block|}
end_function

begin_function
name|void
DECL|function|channels_new_last_vals_cmd_callback (GtkAction * action,gpointer data)
name|channels_new_last_vals_cmd_callback
parameter_list|(
name|GtkAction
modifier|*
name|action
parameter_list|,
name|gpointer
name|data
parameter_list|)
block|{
name|GimpImage
modifier|*
name|image
decl_stmt|;
name|GimpChannel
modifier|*
name|new_channel
decl_stmt|;
name|gint
name|width
decl_stmt|,
name|height
decl_stmt|;
name|GimpRGB
name|color
decl_stmt|;
name|return_if_no_image
argument_list|(
name|image
argument_list|,
name|data
argument_list|)
expr_stmt|;
if|if
condition|(
name|GIMP_IS_CHANNEL
argument_list|(
name|GIMP_ACTION
argument_list|(
name|action
argument_list|)
operator|->
name|viewable
argument_list|)
condition|)
block|{
name|GimpChannel
modifier|*
name|template
init|=
name|GIMP_CHANNEL
argument_list|(
name|GIMP_ACTION
argument_list|(
name|action
argument_list|)
operator|->
name|viewable
argument_list|)
decl_stmt|;
name|width
operator|=
name|gimp_item_width
argument_list|(
name|GIMP_ITEM
argument_list|(
name|template
argument_list|)
argument_list|)
expr_stmt|;
name|height
operator|=
name|gimp_item_height
argument_list|(
name|GIMP_ITEM
argument_list|(
name|template
argument_list|)
argument_list|)
expr_stmt|;
name|color
operator|=
name|template
operator|->
name|color
expr_stmt|;
block|}
else|else
block|{
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
name|color
operator|=
name|channel_color
expr_stmt|;
block|}
name|gimp_image_undo_group_start
argument_list|(
name|image
argument_list|,
name|GIMP_UNDO_GROUP_EDIT_PASTE
argument_list|,
name|_
argument_list|(
literal|"New Channel"
argument_list|)
argument_list|)
expr_stmt|;
name|new_channel
operator|=
name|gimp_channel_new
argument_list|(
name|image
argument_list|,
name|width
argument_list|,
name|height
argument_list|,
name|channel_name
condition|?
name|channel_name
else|:
name|_
argument_list|(
literal|"New Channel"
argument_list|)
argument_list|,
operator|&
name|color
argument_list|)
expr_stmt|;
name|gimp_drawable_fill_by_type
argument_list|(
name|GIMP_DRAWABLE
argument_list|(
name|new_channel
argument_list|)
argument_list|,
name|action_data_get_context
argument_list|(
name|data
argument_list|)
argument_list|,
name|GIMP_TRANSPARENT_FILL
argument_list|)
expr_stmt|;
name|gimp_image_add_channel
argument_list|(
name|image
argument_list|,
name|new_channel
argument_list|,
operator|-
literal|1
argument_list|)
expr_stmt|;
name|gimp_image_undo_group_end
argument_list|(
name|image
argument_list|)
expr_stmt|;
name|gimp_image_flush
argument_list|(
name|image
argument_list|)
expr_stmt|;
block|}
end_function

begin_function
name|void
DECL|function|channels_raise_cmd_callback (GtkAction * action,gpointer data)
name|channels_raise_cmd_callback
parameter_list|(
name|GtkAction
modifier|*
name|action
parameter_list|,
name|gpointer
name|data
parameter_list|)
block|{
name|GimpImage
modifier|*
name|image
decl_stmt|;
name|GimpChannel
modifier|*
name|channel
decl_stmt|;
name|return_if_no_channel
argument_list|(
name|image
argument_list|,
name|channel
argument_list|,
name|data
argument_list|)
expr_stmt|;
name|gimp_image_raise_channel
argument_list|(
name|image
argument_list|,
name|channel
argument_list|)
expr_stmt|;
name|gimp_image_flush
argument_list|(
name|image
argument_list|)
expr_stmt|;
block|}
end_function

begin_function
name|void
DECL|function|channels_raise_to_top_cmd_callback (GtkAction * action,gpointer data)
name|channels_raise_to_top_cmd_callback
parameter_list|(
name|GtkAction
modifier|*
name|action
parameter_list|,
name|gpointer
name|data
parameter_list|)
block|{
name|GimpImage
modifier|*
name|image
decl_stmt|;
name|GimpChannel
modifier|*
name|channel
decl_stmt|;
name|return_if_no_channel
argument_list|(
name|image
argument_list|,
name|channel
argument_list|,
name|data
argument_list|)
expr_stmt|;
name|gimp_image_raise_channel_to_top
argument_list|(
name|image
argument_list|,
name|channel
argument_list|)
expr_stmt|;
name|gimp_image_flush
argument_list|(
name|image
argument_list|)
expr_stmt|;
block|}
end_function

begin_function
name|void
DECL|function|channels_lower_cmd_callback (GtkAction * action,gpointer data)
name|channels_lower_cmd_callback
parameter_list|(
name|GtkAction
modifier|*
name|action
parameter_list|,
name|gpointer
name|data
parameter_list|)
block|{
name|GimpImage
modifier|*
name|image
decl_stmt|;
name|GimpChannel
modifier|*
name|channel
decl_stmt|;
name|return_if_no_channel
argument_list|(
name|image
argument_list|,
name|channel
argument_list|,
name|data
argument_list|)
expr_stmt|;
name|gimp_image_lower_channel
argument_list|(
name|image
argument_list|,
name|channel
argument_list|)
expr_stmt|;
name|gimp_image_flush
argument_list|(
name|image
argument_list|)
expr_stmt|;
block|}
end_function

begin_function
name|void
DECL|function|channels_lower_to_bottom_cmd_callback (GtkAction * action,gpointer data)
name|channels_lower_to_bottom_cmd_callback
parameter_list|(
name|GtkAction
modifier|*
name|action
parameter_list|,
name|gpointer
name|data
parameter_list|)
block|{
name|GimpImage
modifier|*
name|image
decl_stmt|;
name|GimpChannel
modifier|*
name|channel
decl_stmt|;
name|return_if_no_channel
argument_list|(
name|image
argument_list|,
name|channel
argument_list|,
name|data
argument_list|)
expr_stmt|;
name|gimp_image_lower_channel_to_bottom
argument_list|(
name|image
argument_list|,
name|channel
argument_list|)
expr_stmt|;
name|gimp_image_flush
argument_list|(
name|image
argument_list|)
expr_stmt|;
block|}
end_function

begin_function
name|void
DECL|function|channels_duplicate_cmd_callback (GtkAction * action,gpointer data)
name|channels_duplicate_cmd_callback
parameter_list|(
name|GtkAction
modifier|*
name|action
parameter_list|,
name|gpointer
name|data
parameter_list|)
block|{
name|GimpImage
modifier|*
name|image
decl_stmt|;
name|GimpChannel
modifier|*
name|new_channel
decl_stmt|;
if|if
condition|(
name|GIMP_IS_COMPONENT_EDITOR
argument_list|(
name|data
argument_list|)
condition|)
block|{
name|GimpChannelType
name|component
decl_stmt|;
specifier|const
name|gchar
modifier|*
name|desc
decl_stmt|;
name|gchar
modifier|*
name|name
decl_stmt|;
name|return_if_no_image
argument_list|(
name|image
argument_list|,
name|data
argument_list|)
expr_stmt|;
name|component
operator|=
name|GIMP_COMPONENT_EDITOR
argument_list|(
name|data
argument_list|)
operator|->
name|clicked_component
expr_stmt|;
name|gimp_enum_get_value
argument_list|(
name|GIMP_TYPE_CHANNEL_TYPE
argument_list|,
name|component
argument_list|,
name|NULL
argument_list|,
name|NULL
argument_list|,
operator|&
name|desc
argument_list|,
name|NULL
argument_list|)
expr_stmt|;
name|name
operator|=
name|g_strdup_printf
argument_list|(
name|_
argument_list|(
literal|"%s Channel Copy"
argument_list|)
argument_list|,
name|desc
argument_list|)
expr_stmt|;
name|new_channel
operator|=
name|gimp_channel_new_from_component
argument_list|(
name|image
argument_list|,
name|component
argument_list|,
name|name
argument_list|,
name|NULL
argument_list|)
expr_stmt|;
comment|/*  copied components are invisible by default so subsequent copies        *  of components don't affect each other        */
name|gimp_item_set_visible
argument_list|(
name|GIMP_ITEM
argument_list|(
name|new_channel
argument_list|)
argument_list|,
name|FALSE
argument_list|,
name|FALSE
argument_list|)
expr_stmt|;
name|g_free
argument_list|(
name|name
argument_list|)
expr_stmt|;
block|}
else|else
block|{
name|GimpChannel
modifier|*
name|channel
decl_stmt|;
name|return_if_no_channel
argument_list|(
name|image
argument_list|,
name|channel
argument_list|,
name|data
argument_list|)
expr_stmt|;
name|new_channel
operator|=
name|GIMP_CHANNEL
argument_list|(
name|gimp_item_duplicate
argument_list|(
name|GIMP_ITEM
argument_list|(
name|channel
argument_list|)
argument_list|,
name|G_TYPE_FROM_INSTANCE
argument_list|(
name|channel
argument_list|)
argument_list|,
name|TRUE
argument_list|)
argument_list|)
expr_stmt|;
block|}
name|gimp_image_add_channel
argument_list|(
name|image
argument_list|,
name|new_channel
argument_list|,
operator|-
literal|1
argument_list|)
expr_stmt|;
name|gimp_image_flush
argument_list|(
name|image
argument_list|)
expr_stmt|;
block|}
end_function

begin_function
name|void
DECL|function|channels_delete_cmd_callback (GtkAction * action,gpointer data)
name|channels_delete_cmd_callback
parameter_list|(
name|GtkAction
modifier|*
name|action
parameter_list|,
name|gpointer
name|data
parameter_list|)
block|{
name|GimpImage
modifier|*
name|image
decl_stmt|;
name|GimpChannel
modifier|*
name|channel
decl_stmt|;
name|return_if_no_channel
argument_list|(
name|image
argument_list|,
name|channel
argument_list|,
name|data
argument_list|)
expr_stmt|;
name|gimp_image_remove_channel
argument_list|(
name|image
argument_list|,
name|channel
argument_list|)
expr_stmt|;
name|gimp_image_flush
argument_list|(
name|image
argument_list|)
expr_stmt|;
block|}
end_function

begin_function
name|void
DECL|function|channels_to_selection_cmd_callback (GtkAction * action,gint value,gpointer data)
name|channels_to_selection_cmd_callback
parameter_list|(
name|GtkAction
modifier|*
name|action
parameter_list|,
name|gint
name|value
parameter_list|,
name|gpointer
name|data
parameter_list|)
block|{
name|GimpChannelOps
name|op
decl_stmt|;
name|GimpImage
modifier|*
name|image
decl_stmt|;
name|op
operator|=
operator|(
name|GimpChannelOps
operator|)
name|value
expr_stmt|;
if|if
condition|(
name|GIMP_IS_COMPONENT_EDITOR
argument_list|(
name|data
argument_list|)
condition|)
block|{
name|GimpChannelType
name|component
decl_stmt|;
name|return_if_no_image
argument_list|(
name|image
argument_list|,
name|data
argument_list|)
expr_stmt|;
name|component
operator|=
name|GIMP_COMPONENT_EDITOR
argument_list|(
name|data
argument_list|)
operator|->
name|clicked_component
expr_stmt|;
name|gimp_channel_select_component
argument_list|(
name|gimp_image_get_mask
argument_list|(
name|image
argument_list|)
argument_list|,
name|component
argument_list|,
name|op
argument_list|,
name|FALSE
argument_list|,
literal|0.0
argument_list|,
literal|0.0
argument_list|)
expr_stmt|;
block|}
else|else
block|{
name|GimpChannel
modifier|*
name|channel
decl_stmt|;
name|return_if_no_channel
argument_list|(
name|image
argument_list|,
name|channel
argument_list|,
name|data
argument_list|)
expr_stmt|;
name|gimp_channel_select_channel
argument_list|(
name|gimp_image_get_mask
argument_list|(
name|image
argument_list|)
argument_list|,
name|_
argument_list|(
literal|"Channel to Selection"
argument_list|)
argument_list|,
name|channel
argument_list|,
literal|0
argument_list|,
literal|0
argument_list|,
name|op
argument_list|,
name|FALSE
argument_list|,
literal|0.0
argument_list|,
literal|0.0
argument_list|)
expr_stmt|;
block|}
name|gimp_image_flush
argument_list|(
name|image
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
DECL|function|channels_new_channel_response (GtkWidget * widget,gint response_id,ChannelOptionsDialog * options)
name|channels_new_channel_response
parameter_list|(
name|GtkWidget
modifier|*
name|widget
parameter_list|,
name|gint
name|response_id
parameter_list|,
name|ChannelOptionsDialog
modifier|*
name|options
parameter_list|)
block|{
if|if
condition|(
name|response_id
operator|==
name|GTK_RESPONSE_OK
condition|)
block|{
name|GimpChannel
modifier|*
name|new_channel
decl_stmt|;
if|if
condition|(
name|channel_name
condition|)
name|g_free
argument_list|(
name|channel_name
argument_list|)
expr_stmt|;
name|channel_name
operator|=
name|g_strdup
argument_list|(
name|gtk_entry_get_text
argument_list|(
name|GTK_ENTRY
argument_list|(
name|options
operator|->
name|name_entry
argument_list|)
argument_list|)
argument_list|)
expr_stmt|;
name|gimp_color_button_get_color
argument_list|(
name|GIMP_COLOR_BUTTON
argument_list|(
name|options
operator|->
name|color_panel
argument_list|)
argument_list|,
operator|&
name|channel_color
argument_list|)
expr_stmt|;
if|if
condition|(
name|gtk_toggle_button_get_active
argument_list|(
name|GTK_TOGGLE_BUTTON
argument_list|(
name|options
operator|->
name|save_sel_checkbutton
argument_list|)
argument_list|)
condition|)
block|{
name|GimpChannel
modifier|*
name|selection
init|=
name|gimp_image_get_mask
argument_list|(
name|options
operator|->
name|image
argument_list|)
decl_stmt|;
name|new_channel
operator|=
name|GIMP_CHANNEL
argument_list|(
name|gimp_item_duplicate
argument_list|(
name|GIMP_ITEM
argument_list|(
name|selection
argument_list|)
argument_list|,
name|GIMP_TYPE_CHANNEL
argument_list|,
name|FALSE
argument_list|)
argument_list|)
expr_stmt|;
name|gimp_object_set_name
argument_list|(
name|GIMP_OBJECT
argument_list|(
name|new_channel
argument_list|)
argument_list|,
name|channel_name
argument_list|)
expr_stmt|;
name|gimp_channel_set_color
argument_list|(
name|new_channel
argument_list|,
operator|&
name|channel_color
argument_list|,
name|FALSE
argument_list|)
expr_stmt|;
block|}
else|else
block|{
name|new_channel
operator|=
name|gimp_channel_new
argument_list|(
name|options
operator|->
name|image
argument_list|,
name|options
operator|->
name|image
operator|->
name|width
argument_list|,
name|options
operator|->
name|image
operator|->
name|height
argument_list|,
name|channel_name
argument_list|,
operator|&
name|channel_color
argument_list|)
expr_stmt|;
name|gimp_drawable_fill_by_type
argument_list|(
name|GIMP_DRAWABLE
argument_list|(
name|new_channel
argument_list|)
argument_list|,
name|options
operator|->
name|context
argument_list|,
name|GIMP_TRANSPARENT_FILL
argument_list|)
expr_stmt|;
block|}
name|gimp_image_add_channel
argument_list|(
name|options
operator|->
name|image
argument_list|,
name|new_channel
argument_list|,
operator|-
literal|1
argument_list|)
expr_stmt|;
name|gimp_image_flush
argument_list|(
name|options
operator|->
name|image
argument_list|)
expr_stmt|;
block|}
name|gtk_widget_destroy
argument_list|(
name|options
operator|->
name|dialog
argument_list|)
expr_stmt|;
block|}
end_function

begin_function
specifier|static
name|void
DECL|function|channels_edit_channel_response (GtkWidget * widget,gint response_id,ChannelOptionsDialog * options)
name|channels_edit_channel_response
parameter_list|(
name|GtkWidget
modifier|*
name|widget
parameter_list|,
name|gint
name|response_id
parameter_list|,
name|ChannelOptionsDialog
modifier|*
name|options
parameter_list|)
block|{
if|if
condition|(
name|response_id
operator|==
name|GTK_RESPONSE_OK
condition|)
block|{
name|GimpChannel
modifier|*
name|channel
init|=
name|options
operator|->
name|channel
decl_stmt|;
specifier|const
name|gchar
modifier|*
name|new_name
decl_stmt|;
name|GimpRGB
name|color
decl_stmt|;
name|gboolean
name|name_changed
init|=
name|FALSE
decl_stmt|;
name|gboolean
name|color_changed
init|=
name|FALSE
decl_stmt|;
name|new_name
operator|=
name|gtk_entry_get_text
argument_list|(
name|GTK_ENTRY
argument_list|(
name|options
operator|->
name|name_entry
argument_list|)
argument_list|)
expr_stmt|;
name|gimp_color_button_get_color
argument_list|(
name|GIMP_COLOR_BUTTON
argument_list|(
name|options
operator|->
name|color_panel
argument_list|)
argument_list|,
operator|&
name|color
argument_list|)
expr_stmt|;
if|if
condition|(
name|strcmp
argument_list|(
name|new_name
argument_list|,
name|gimp_object_get_name
argument_list|(
name|GIMP_OBJECT
argument_list|(
name|channel
argument_list|)
argument_list|)
argument_list|)
condition|)
name|name_changed
operator|=
name|TRUE
expr_stmt|;
if|if
condition|(
name|gimp_rgba_distance
argument_list|(
operator|&
name|color
argument_list|,
operator|&
name|channel
operator|->
name|color
argument_list|)
operator|>
literal|0.0001
condition|)
name|color_changed
operator|=
name|TRUE
expr_stmt|;
if|if
condition|(
name|name_changed
operator|&&
name|color_changed
condition|)
name|gimp_image_undo_group_start
argument_list|(
name|options
operator|->
name|image
argument_list|,
name|GIMP_UNDO_GROUP_ITEM_PROPERTIES
argument_list|,
name|_
argument_list|(
literal|"Channel Attributes"
argument_list|)
argument_list|)
expr_stmt|;
if|if
condition|(
name|name_changed
condition|)
name|gimp_item_rename
argument_list|(
name|GIMP_ITEM
argument_list|(
name|channel
argument_list|)
argument_list|,
name|new_name
argument_list|,
name|NULL
argument_list|)
expr_stmt|;
if|if
condition|(
name|color_changed
condition|)
name|gimp_channel_set_color
argument_list|(
name|channel
argument_list|,
operator|&
name|color
argument_list|,
name|TRUE
argument_list|)
expr_stmt|;
if|if
condition|(
name|name_changed
operator|&&
name|color_changed
condition|)
name|gimp_image_undo_group_end
argument_list|(
name|options
operator|->
name|image
argument_list|)
expr_stmt|;
if|if
condition|(
name|name_changed
operator|||
name|color_changed
condition|)
name|gimp_image_flush
argument_list|(
name|options
operator|->
name|image
argument_list|)
expr_stmt|;
block|}
name|gtk_widget_destroy
argument_list|(
name|options
operator|->
name|dialog
argument_list|)
expr_stmt|;
block|}
end_function

end_unit

