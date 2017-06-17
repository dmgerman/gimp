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
file|"widgets/gimpactiongroup.h"
end_include

begin_include
include|#
directive|include
file|"widgets/gimpcomponenteditor.h"
end_include

begin_include
include|#
directive|include
file|"widgets/gimphelp-ids.h"
end_include

begin_include
include|#
directive|include
file|"actions.h"
end_include

begin_include
include|#
directive|include
file|"channels-actions.h"
end_include

begin_include
include|#
directive|include
file|"channels-commands.h"
end_include

begin_include
include|#
directive|include
file|"items-actions.h"
end_include

begin_include
include|#
directive|include
file|"gimp-intl.h"
end_include

begin_decl_stmt
DECL|variable|channels_actions
specifier|static
specifier|const
name|GimpActionEntry
name|channels_actions
index|[]
init|=
block|{
block|{
literal|"channels-popup"
block|,
name|GIMP_ICON_DIALOG_CHANNELS
block|,
name|NC_
argument_list|(
literal|"channels-action"
argument_list|,
literal|"Channels Menu"
argument_list|)
block|,
name|NULL
block|,
name|NULL
block|,
name|NULL
block|,
name|GIMP_HELP_CHANNEL_DIALOG
block|}
block|,
block|{
literal|"channels-color-tag-menu"
block|,
name|GIMP_ICON_CLOSE
comment|/* abused */
block|,
name|NC_
argument_list|(
literal|"channels-action"
argument_list|,
literal|"Color Tag"
argument_list|)
block|,
name|NULL
block|,
name|NULL
block|,
name|NULL
block|,
name|GIMP_HELP_CHANNEL_COLOR_TAG
block|}
block|,
block|{
literal|"channels-edit-attributes"
block|,
name|GIMP_ICON_EDIT
block|,
name|NC_
argument_list|(
literal|"channels-action"
argument_list|,
literal|"_Edit Channel Attributes..."
argument_list|)
block|,
name|NULL
block|,
name|NC_
argument_list|(
literal|"channels-action"
argument_list|,
literal|"Edit the channel's name, color and opacity"
argument_list|)
block|,
name|G_CALLBACK
argument_list|(
name|channels_edit_attributes_cmd_callback
argument_list|)
block|,
name|GIMP_HELP_CHANNEL_EDIT
block|}
block|,
block|{
literal|"channels-new"
block|,
name|GIMP_ICON_DOCUMENT_NEW
block|,
name|NC_
argument_list|(
literal|"channels-action"
argument_list|,
literal|"_New Channel..."
argument_list|)
block|,
name|NULL
block|,
name|NC_
argument_list|(
literal|"channels-action"
argument_list|,
literal|"Create a new channel"
argument_list|)
block|,
name|G_CALLBACK
argument_list|(
name|channels_new_cmd_callback
argument_list|)
block|,
name|GIMP_HELP_CHANNEL_NEW
block|}
block|,
block|{
literal|"channels-new-last-values"
block|,
name|GIMP_ICON_DOCUMENT_NEW
block|,
name|NC_
argument_list|(
literal|"channels-action"
argument_list|,
literal|"_New Channel"
argument_list|)
block|,
name|NULL
block|,
name|NC_
argument_list|(
literal|"channels-action"
argument_list|,
literal|"Create a new channel with last used values"
argument_list|)
block|,
name|G_CALLBACK
argument_list|(
name|channels_new_last_vals_cmd_callback
argument_list|)
block|,
name|GIMP_HELP_CHANNEL_NEW
block|}
block|,
block|{
literal|"channels-duplicate"
block|,
name|GIMP_ICON_OBJECT_DUPLICATE
block|,
name|NC_
argument_list|(
literal|"channels-action"
argument_list|,
literal|"D_uplicate Channel"
argument_list|)
block|,
name|NULL
block|,
name|NC_
argument_list|(
literal|"channels-action"
argument_list|,
literal|"Create a duplicate of this channel and add it to the image"
argument_list|)
block|,
name|G_CALLBACK
argument_list|(
name|channels_duplicate_cmd_callback
argument_list|)
block|,
name|GIMP_HELP_CHANNEL_DUPLICATE
block|}
block|,
block|{
literal|"channels-delete"
block|,
name|GIMP_ICON_EDIT_DELETE
block|,
name|NC_
argument_list|(
literal|"channels-action"
argument_list|,
literal|"_Delete Channel"
argument_list|)
block|,
name|NULL
block|,
name|NC_
argument_list|(
literal|"channels-action"
argument_list|,
literal|"Delete this channel"
argument_list|)
block|,
name|G_CALLBACK
argument_list|(
name|channels_delete_cmd_callback
argument_list|)
block|,
name|GIMP_HELP_CHANNEL_DELETE
block|}
block|,
block|{
literal|"channels-raise"
block|,
name|GIMP_ICON_GO_UP
block|,
name|NC_
argument_list|(
literal|"channels-action"
argument_list|,
literal|"_Raise Channel"
argument_list|)
block|,
name|NULL
block|,
name|NC_
argument_list|(
literal|"channels-action"
argument_list|,
literal|"Raise this channel one step in the channel stack"
argument_list|)
block|,
name|G_CALLBACK
argument_list|(
name|channels_raise_cmd_callback
argument_list|)
block|,
name|GIMP_HELP_CHANNEL_RAISE
block|}
block|,
block|{
literal|"channels-raise-to-top"
block|,
name|GIMP_ICON_GO_TOP
block|,
name|NC_
argument_list|(
literal|"channels-action"
argument_list|,
literal|"Raise Channel to _Top"
argument_list|)
block|,
name|NULL
block|,
name|NC_
argument_list|(
literal|"channels-action"
argument_list|,
literal|"Raise this channel to the top of the channel stack"
argument_list|)
block|,
name|G_CALLBACK
argument_list|(
name|channels_raise_to_top_cmd_callback
argument_list|)
block|,
name|GIMP_HELP_CHANNEL_RAISE_TO_TOP
block|}
block|,
block|{
literal|"channels-lower"
block|,
name|GIMP_ICON_GO_DOWN
block|,
name|NC_
argument_list|(
literal|"channels-action"
argument_list|,
literal|"_Lower Channel"
argument_list|)
block|,
name|NULL
block|,
name|NC_
argument_list|(
literal|"channels-action"
argument_list|,
literal|"Lower this channel one step in the channel stack"
argument_list|)
block|,
name|G_CALLBACK
argument_list|(
name|channels_lower_cmd_callback
argument_list|)
block|,
name|GIMP_HELP_CHANNEL_LOWER
block|}
block|,
block|{
literal|"channels-lower-to-bottom"
block|,
name|GIMP_ICON_GO_BOTTOM
block|,
name|NC_
argument_list|(
literal|"channels-action"
argument_list|,
literal|"Lower Channel to _Bottom"
argument_list|)
block|,
name|NULL
block|,
name|NC_
argument_list|(
literal|"channels-action"
argument_list|,
literal|"Lower this channel to the bottom of the channel stack"
argument_list|)
block|,
name|G_CALLBACK
argument_list|(
name|channels_lower_to_bottom_cmd_callback
argument_list|)
block|,
name|GIMP_HELP_CHANNEL_LOWER_TO_BOTTOM
block|}
block|}
decl_stmt|;
end_decl_stmt

begin_decl_stmt
DECL|variable|channels_toggle_actions
specifier|static
specifier|const
name|GimpToggleActionEntry
name|channels_toggle_actions
index|[]
init|=
block|{
block|{
literal|"channels-visible"
block|,
name|GIMP_ICON_VISIBLE
block|,
name|NC_
argument_list|(
literal|"channels-action"
argument_list|,
literal|"_Visible"
argument_list|)
block|,
name|NULL
block|,
name|NULL
block|,
name|G_CALLBACK
argument_list|(
name|channels_visible_cmd_callback
argument_list|)
block|,
name|FALSE
block|,
name|GIMP_HELP_CHANNEL_VISIBLE
block|}
block|,
block|{
literal|"channels-linked"
block|,
name|GIMP_ICON_LINKED
block|,
name|NC_
argument_list|(
literal|"channels-action"
argument_list|,
literal|"_Linked"
argument_list|)
block|,
name|NULL
block|,
name|NULL
block|,
name|G_CALLBACK
argument_list|(
name|channels_linked_cmd_callback
argument_list|)
block|,
name|FALSE
block|,
name|GIMP_HELP_CHANNEL_LINKED
block|}
block|,
block|{
literal|"channels-lock-content"
block|,
name|NULL
comment|/* GIMP_ICON_LOCK */
block|,
name|NC_
argument_list|(
literal|"channels-action"
argument_list|,
literal|"L_ock pixels"
argument_list|)
block|,
name|NULL
block|,
name|NULL
block|,
name|G_CALLBACK
argument_list|(
name|channels_lock_content_cmd_callback
argument_list|)
block|,
name|FALSE
block|,
name|GIMP_HELP_CHANNEL_LOCK_PIXELS
block|}
block|,
block|{
literal|"channels-lock-position"
block|,
name|GIMP_ICON_TOOL_MOVE
block|,
name|NC_
argument_list|(
literal|"channels-action"
argument_list|,
literal|"L_ock position"
argument_list|)
block|,
name|NULL
block|,
name|NULL
block|,
name|G_CALLBACK
argument_list|(
name|channels_lock_position_cmd_callback
argument_list|)
block|,
name|FALSE
block|,
name|GIMP_HELP_CHANNEL_LOCK_POSITION
block|}
block|}
decl_stmt|;
end_decl_stmt

begin_decl_stmt
DECL|variable|channels_color_tag_actions
specifier|static
specifier|const
name|GimpEnumActionEntry
name|channels_color_tag_actions
index|[]
init|=
block|{
block|{
literal|"channels-color-tag-none"
block|,
name|GIMP_ICON_CLOSE
comment|/* abused */
block|,
name|NC_
argument_list|(
literal|"channels-action"
argument_list|,
literal|"None"
argument_list|)
block|,
name|NULL
block|,
name|NC_
argument_list|(
literal|"channels-action"
argument_list|,
literal|"Color Tag: Clear"
argument_list|)
block|,
name|GIMP_COLOR_TAG_NONE
block|,
name|FALSE
block|,
name|GIMP_HELP_CHANNEL_COLOR_TAG
block|}
block|,
block|{
literal|"channels-color-tag-blue"
block|,
name|NULL
block|,
name|NC_
argument_list|(
literal|"channels-action"
argument_list|,
literal|"Blue"
argument_list|)
block|,
name|NULL
block|,
name|NC_
argument_list|(
literal|"channels-action"
argument_list|,
literal|"Color Tag: Set to Blue"
argument_list|)
block|,
name|GIMP_COLOR_TAG_BLUE
block|,
name|FALSE
block|,
name|GIMP_HELP_CHANNEL_COLOR_TAG
block|}
block|,
block|{
literal|"channels-color-tag-green"
block|,
name|NULL
block|,
name|NC_
argument_list|(
literal|"channels-action"
argument_list|,
literal|"Green"
argument_list|)
block|,
name|NULL
block|,
name|NC_
argument_list|(
literal|"channels-action"
argument_list|,
literal|"Color Tag: Set to Green"
argument_list|)
block|,
name|GIMP_COLOR_TAG_GREEN
block|,
name|FALSE
block|,
name|GIMP_HELP_CHANNEL_COLOR_TAG
block|}
block|,
block|{
literal|"channels-color-tag-yellow"
block|,
name|NULL
block|,
name|NC_
argument_list|(
literal|"channels-action"
argument_list|,
literal|"Yellow"
argument_list|)
block|,
name|NULL
block|,
name|NC_
argument_list|(
literal|"channels-action"
argument_list|,
literal|"Color Tag: Set to Yellow"
argument_list|)
block|,
name|GIMP_COLOR_TAG_YELLOW
block|,
name|FALSE
block|,
name|GIMP_HELP_CHANNEL_COLOR_TAG
block|}
block|,
block|{
literal|"channels-color-tag-orange"
block|,
name|NULL
block|,
name|NC_
argument_list|(
literal|"channels-action"
argument_list|,
literal|"Orange"
argument_list|)
block|,
name|NULL
block|,
name|NC_
argument_list|(
literal|"channels-action"
argument_list|,
literal|"Color Tag: Set to Orange"
argument_list|)
block|,
name|GIMP_COLOR_TAG_ORANGE
block|,
name|FALSE
block|,
name|GIMP_HELP_CHANNEL_COLOR_TAG
block|}
block|,
block|{
literal|"channels-color-tag-brown"
block|,
name|NULL
block|,
name|NC_
argument_list|(
literal|"channels-action"
argument_list|,
literal|"Brown"
argument_list|)
block|,
name|NULL
block|,
name|NC_
argument_list|(
literal|"channels-action"
argument_list|,
literal|"Color Tag: Set to Brown"
argument_list|)
block|,
name|GIMP_COLOR_TAG_BROWN
block|,
name|FALSE
block|,
name|GIMP_HELP_CHANNEL_COLOR_TAG
block|}
block|,
block|{
literal|"channels-color-tag-red"
block|,
name|NULL
block|,
name|NC_
argument_list|(
literal|"channels-action"
argument_list|,
literal|"Red"
argument_list|)
block|,
name|NULL
block|,
name|NC_
argument_list|(
literal|"channels-action"
argument_list|,
literal|"Color Tag: Set to  Red"
argument_list|)
block|,
name|GIMP_COLOR_TAG_RED
block|,
name|FALSE
block|,
name|GIMP_HELP_CHANNEL_COLOR_TAG
block|}
block|,
block|{
literal|"channels-color-tag-violet"
block|,
name|NULL
block|,
name|NC_
argument_list|(
literal|"channels-action"
argument_list|,
literal|"Violet"
argument_list|)
block|,
name|NULL
block|,
name|NC_
argument_list|(
literal|"channels-action"
argument_list|,
literal|"Color Tag: Set to Violet"
argument_list|)
block|,
name|GIMP_COLOR_TAG_VIOLET
block|,
name|FALSE
block|,
name|GIMP_HELP_CHANNEL_COLOR_TAG
block|}
block|,
block|{
literal|"channels-color-tag-gray"
block|,
name|NULL
block|,
name|NC_
argument_list|(
literal|"channels-action"
argument_list|,
literal|"Gray"
argument_list|)
block|,
name|NULL
block|,
name|NC_
argument_list|(
literal|"channels-action"
argument_list|,
literal|"Color Tag: Set to Gray"
argument_list|)
block|,
name|GIMP_COLOR_TAG_GRAY
block|,
name|FALSE
block|,
name|GIMP_HELP_CHANNEL_COLOR_TAG
block|}
block|}
decl_stmt|;
end_decl_stmt

begin_decl_stmt
DECL|variable|channels_to_selection_actions
specifier|static
specifier|const
name|GimpEnumActionEntry
name|channels_to_selection_actions
index|[]
init|=
block|{
block|{
literal|"channels-selection-replace"
block|,
name|GIMP_ICON_SELECTION_REPLACE
block|,
name|NC_
argument_list|(
literal|"channels-action"
argument_list|,
literal|"Channel to Sele_ction"
argument_list|)
block|,
name|NULL
block|,
name|NC_
argument_list|(
literal|"channels-action"
argument_list|,
literal|"Replace the selection with this channel"
argument_list|)
block|,
name|GIMP_CHANNEL_OP_REPLACE
block|,
name|FALSE
block|,
name|GIMP_HELP_CHANNEL_SELECTION_REPLACE
block|}
block|,
block|{
literal|"channels-selection-add"
block|,
name|GIMP_ICON_SELECTION_ADD
block|,
name|NC_
argument_list|(
literal|"channels-action"
argument_list|,
literal|"_Add to Selection"
argument_list|)
block|,
name|NULL
block|,
name|NC_
argument_list|(
literal|"channels-action"
argument_list|,
literal|"Add this channel to the current selection"
argument_list|)
block|,
name|GIMP_CHANNEL_OP_ADD
block|,
name|FALSE
block|,
name|GIMP_HELP_CHANNEL_SELECTION_ADD
block|}
block|,
block|{
literal|"channels-selection-subtract"
block|,
name|GIMP_ICON_SELECTION_SUBTRACT
block|,
name|NC_
argument_list|(
literal|"channels-action"
argument_list|,
literal|"_Subtract from Selection"
argument_list|)
block|,
name|NULL
block|,
name|NC_
argument_list|(
literal|"channels-action"
argument_list|,
literal|"Subtract this channel from the current selection"
argument_list|)
block|,
name|GIMP_CHANNEL_OP_SUBTRACT
block|,
name|FALSE
block|,
name|GIMP_HELP_CHANNEL_SELECTION_SUBTRACT
block|}
block|,
block|{
literal|"channels-selection-intersect"
block|,
name|GIMP_ICON_SELECTION_INTERSECT
block|,
name|NC_
argument_list|(
literal|"channels-action"
argument_list|,
literal|"_Intersect with Selection"
argument_list|)
block|,
name|NULL
block|,
name|NC_
argument_list|(
literal|"channels-action"
argument_list|,
literal|"Intersect this channel with the current selection"
argument_list|)
block|,
name|GIMP_CHANNEL_OP_INTERSECT
block|,
name|FALSE
block|,
name|GIMP_HELP_CHANNEL_SELECTION_INTERSECT
block|}
block|}
decl_stmt|;
end_decl_stmt

begin_function
name|void
DECL|function|channels_actions_setup (GimpActionGroup * group)
name|channels_actions_setup
parameter_list|(
name|GimpActionGroup
modifier|*
name|group
parameter_list|)
block|{
name|gimp_action_group_add_actions
argument_list|(
name|group
argument_list|,
literal|"channels-action"
argument_list|,
name|channels_actions
argument_list|,
name|G_N_ELEMENTS
argument_list|(
name|channels_actions
argument_list|)
argument_list|)
expr_stmt|;
name|gimp_action_group_add_toggle_actions
argument_list|(
name|group
argument_list|,
literal|"channels-action"
argument_list|,
name|channels_toggle_actions
argument_list|,
name|G_N_ELEMENTS
argument_list|(
name|channels_toggle_actions
argument_list|)
argument_list|)
expr_stmt|;
name|gimp_action_group_add_enum_actions
argument_list|(
name|group
argument_list|,
literal|"channels-action"
argument_list|,
name|channels_color_tag_actions
argument_list|,
name|G_N_ELEMENTS
argument_list|(
name|channels_color_tag_actions
argument_list|)
argument_list|,
name|G_CALLBACK
argument_list|(
name|channels_color_tag_cmd_callback
argument_list|)
argument_list|)
expr_stmt|;
name|gimp_action_group_add_enum_actions
argument_list|(
name|group
argument_list|,
literal|"channels-action"
argument_list|,
name|channels_to_selection_actions
argument_list|,
name|G_N_ELEMENTS
argument_list|(
name|channels_to_selection_actions
argument_list|)
argument_list|,
name|G_CALLBACK
argument_list|(
name|channels_to_selection_cmd_callback
argument_list|)
argument_list|)
expr_stmt|;
name|items_actions_setup
argument_list|(
name|group
argument_list|,
literal|"channels"
argument_list|)
expr_stmt|;
block|}
end_function

begin_function
name|void
DECL|function|channels_actions_update (GimpActionGroup * group,gpointer data)
name|channels_actions_update
parameter_list|(
name|GimpActionGroup
modifier|*
name|group
parameter_list|,
name|gpointer
name|data
parameter_list|)
block|{
name|GimpImage
modifier|*
name|image
init|=
name|action_data_get_image
argument_list|(
name|data
argument_list|)
decl_stmt|;
name|GimpChannel
modifier|*
name|channel
init|=
name|NULL
decl_stmt|;
name|gboolean
name|fs
init|=
name|FALSE
decl_stmt|;
name|gboolean
name|component
init|=
name|FALSE
decl_stmt|;
name|GList
modifier|*
name|next
init|=
name|NULL
decl_stmt|;
name|GList
modifier|*
name|prev
init|=
name|NULL
decl_stmt|;
if|if
condition|(
name|image
condition|)
block|{
name|fs
operator|=
operator|(
name|gimp_image_get_floating_selection
argument_list|(
name|image
argument_list|)
operator|!=
name|NULL
operator|)
expr_stmt|;
if|if
condition|(
name|GIMP_IS_COMPONENT_EDITOR
argument_list|(
name|data
argument_list|)
condition|)
block|{
if|if
condition|(
name|GIMP_COMPONENT_EDITOR
argument_list|(
name|data
argument_list|)
operator|->
name|clicked_component
operator|!=
operator|-
literal|1
condition|)
name|component
operator|=
name|TRUE
expr_stmt|;
block|}
else|else
block|{
name|channel
operator|=
name|gimp_image_get_active_channel
argument_list|(
name|image
argument_list|)
expr_stmt|;
if|if
condition|(
name|channel
condition|)
block|{
name|GList
modifier|*
name|channel_list
decl_stmt|;
name|GList
modifier|*
name|list
decl_stmt|;
name|channel_list
operator|=
name|gimp_item_get_container_iter
argument_list|(
name|GIMP_ITEM
argument_list|(
name|channel
argument_list|)
argument_list|)
expr_stmt|;
name|list
operator|=
name|g_list_find
argument_list|(
name|channel_list
argument_list|,
name|channel
argument_list|)
expr_stmt|;
if|if
condition|(
name|list
condition|)
block|{
name|prev
operator|=
name|g_list_previous
argument_list|(
name|list
argument_list|)
expr_stmt|;
name|next
operator|=
name|g_list_next
argument_list|(
name|list
argument_list|)
expr_stmt|;
block|}
block|}
block|}
block|}
DECL|macro|SET_SENSITIVE (action,condition)
define|#
directive|define
name|SET_SENSITIVE
parameter_list|(
name|action
parameter_list|,
name|condition
parameter_list|)
define|\
value|gimp_action_group_set_action_sensitive (group, action, (condition) != 0)
name|SET_SENSITIVE
argument_list|(
literal|"channels-edit-attributes"
argument_list|,
operator|!
name|fs
operator|&&
name|channel
argument_list|)
expr_stmt|;
name|SET_SENSITIVE
argument_list|(
literal|"channels-new"
argument_list|,
operator|!
name|fs
operator|&&
name|image
argument_list|)
expr_stmt|;
name|SET_SENSITIVE
argument_list|(
literal|"channels-new-last-values"
argument_list|,
operator|!
name|fs
operator|&&
name|image
argument_list|)
expr_stmt|;
name|SET_SENSITIVE
argument_list|(
literal|"channels-duplicate"
argument_list|,
operator|!
name|fs
operator|&&
operator|(
name|channel
operator|||
name|component
operator|)
argument_list|)
expr_stmt|;
name|SET_SENSITIVE
argument_list|(
literal|"channels-delete"
argument_list|,
operator|!
name|fs
operator|&&
name|channel
argument_list|)
expr_stmt|;
name|SET_SENSITIVE
argument_list|(
literal|"channels-raise"
argument_list|,
operator|!
name|fs
operator|&&
name|channel
operator|&&
name|prev
argument_list|)
expr_stmt|;
name|SET_SENSITIVE
argument_list|(
literal|"channels-raise-to-top"
argument_list|,
operator|!
name|fs
operator|&&
name|channel
operator|&&
name|prev
argument_list|)
expr_stmt|;
name|SET_SENSITIVE
argument_list|(
literal|"channels-lower"
argument_list|,
operator|!
name|fs
operator|&&
name|channel
operator|&&
name|next
argument_list|)
expr_stmt|;
name|SET_SENSITIVE
argument_list|(
literal|"channels-lower-to-bottom"
argument_list|,
operator|!
name|fs
operator|&&
name|channel
operator|&&
name|next
argument_list|)
expr_stmt|;
name|SET_SENSITIVE
argument_list|(
literal|"channels-selection-replace"
argument_list|,
operator|!
name|fs
operator|&&
operator|(
name|channel
operator|||
name|component
operator|)
argument_list|)
expr_stmt|;
name|SET_SENSITIVE
argument_list|(
literal|"channels-selection-add"
argument_list|,
operator|!
name|fs
operator|&&
operator|(
name|channel
operator|||
name|component
operator|)
argument_list|)
expr_stmt|;
name|SET_SENSITIVE
argument_list|(
literal|"channels-selection-subtract"
argument_list|,
operator|!
name|fs
operator|&&
operator|(
name|channel
operator|||
name|component
operator|)
argument_list|)
expr_stmt|;
name|SET_SENSITIVE
argument_list|(
literal|"channels-selection-intersect"
argument_list|,
operator|!
name|fs
operator|&&
operator|(
name|channel
operator|||
name|component
operator|)
argument_list|)
expr_stmt|;
undef|#
directive|undef
name|SET_SENSITIVE
name|items_actions_update
argument_list|(
name|group
argument_list|,
literal|"channels"
argument_list|,
name|GIMP_ITEM
argument_list|(
name|channel
argument_list|)
argument_list|)
expr_stmt|;
block|}
end_function

end_unit

