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
file|"core/gimpchannel.h"
end_include

begin_include
include|#
directive|include
file|"core/gimpcontainer.h"
end_include

begin_include
include|#
directive|include
file|"core/gimpimage.h"
end_include

begin_include
include|#
directive|include
file|"widgets/gimpactiongroup.h"
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
file|"vectors-actions.h"
end_include

begin_include
include|#
directive|include
file|"vectors-commands.h"
end_include

begin_include
include|#
directive|include
file|"gimp-intl.h"
end_include

begin_decl_stmt
DECL|variable|vectors_actions
specifier|static
specifier|const
name|GimpActionEntry
name|vectors_actions
index|[]
init|=
block|{
block|{
literal|"vectors-popup"
block|,
name|GIMP_STOCK_PATHS
block|,
name|NC_
argument_list|(
literal|"vectors-action"
argument_list|,
literal|"Paths Menu"
argument_list|)
block|,
name|NULL
block|,
name|NULL
block|,
name|NULL
block|,
name|GIMP_HELP_PATH_DIALOG
block|}
block|,
block|{
literal|"vectors-path-tool"
block|,
name|GIMP_STOCK_TOOL_PATH
block|,
name|NC_
argument_list|(
literal|"vectors-action"
argument_list|,
literal|"Path _Tool"
argument_list|)
block|,
name|NULL
block|,
name|NULL
block|,
name|G_CALLBACK
argument_list|(
name|vectors_vectors_tool_cmd_callback
argument_list|)
block|,
name|GIMP_HELP_TOOL_VECTORS
block|}
block|,
block|{
literal|"vectors-edit-attributes"
block|,
literal|"gtk-edit"
block|,
name|NC_
argument_list|(
literal|"vectors-action"
argument_list|,
literal|"_Edit Path Attributes..."
argument_list|)
block|,
name|NULL
block|,
name|NC_
argument_list|(
literal|"vectors-action"
argument_list|,
literal|"Edit path attributes"
argument_list|)
block|,
name|G_CALLBACK
argument_list|(
name|vectors_edit_attributes_cmd_callback
argument_list|)
block|,
name|GIMP_HELP_PATH_EDIT
block|}
block|,
block|{
literal|"vectors-new"
block|,
literal|"document-new"
block|,
name|NC_
argument_list|(
literal|"vectors-action"
argument_list|,
literal|"_New Path..."
argument_list|)
block|,
name|NULL
block|,
name|NC_
argument_list|(
literal|"vectors-action"
argument_list|,
literal|"Create a new path..."
argument_list|)
block|,
name|G_CALLBACK
argument_list|(
name|vectors_new_cmd_callback
argument_list|)
block|,
name|GIMP_HELP_PATH_NEW
block|}
block|,
block|{
literal|"vectors-new-last-values"
block|,
literal|"document-new"
block|,
name|NC_
argument_list|(
literal|"vectors-action"
argument_list|,
literal|"_New Path with last values"
argument_list|)
block|,
name|NULL
block|,
name|NC_
argument_list|(
literal|"vectors-action"
argument_list|,
literal|"Create a new path with last used values"
argument_list|)
block|,
name|G_CALLBACK
argument_list|(
name|vectors_new_last_vals_cmd_callback
argument_list|)
block|,
name|GIMP_HELP_PATH_NEW
block|}
block|,
block|{
literal|"vectors-duplicate"
block|,
name|GIMP_STOCK_DUPLICATE
block|,
name|NC_
argument_list|(
literal|"vectors-action"
argument_list|,
literal|"D_uplicate Path"
argument_list|)
block|,
name|NULL
block|,
name|NC_
argument_list|(
literal|"vectors-action"
argument_list|,
literal|"Duplicate this path"
argument_list|)
block|,
name|G_CALLBACK
argument_list|(
name|vectors_duplicate_cmd_callback
argument_list|)
block|,
name|GIMP_HELP_PATH_DUPLICATE
block|}
block|,
block|{
literal|"vectors-delete"
block|,
literal|"edit-delete"
block|,
name|NC_
argument_list|(
literal|"vectors-action"
argument_list|,
literal|"_Delete Path"
argument_list|)
block|,
name|NULL
block|,
name|NC_
argument_list|(
literal|"vectors-action"
argument_list|,
literal|"Delete this path"
argument_list|)
block|,
name|G_CALLBACK
argument_list|(
name|vectors_delete_cmd_callback
argument_list|)
block|,
name|GIMP_HELP_PATH_DELETE
block|}
block|,
block|{
literal|"vectors-merge-visible"
block|,
name|NULL
block|,
name|NC_
argument_list|(
literal|"vectors-action"
argument_list|,
literal|"Merge _Visible Paths"
argument_list|)
block|,
name|NULL
block|,
name|NULL
block|,
name|G_CALLBACK
argument_list|(
name|vectors_merge_visible_cmd_callback
argument_list|)
block|,
name|GIMP_HELP_PATH_MERGE_VISIBLE
block|}
block|,
block|{
literal|"vectors-raise"
block|,
literal|"go-up"
block|,
name|NC_
argument_list|(
literal|"vectors-action"
argument_list|,
literal|"_Raise Path"
argument_list|)
block|,
name|NULL
block|,
name|NC_
argument_list|(
literal|"vectors-action"
argument_list|,
literal|"Raise this path"
argument_list|)
block|,
name|G_CALLBACK
argument_list|(
name|vectors_raise_cmd_callback
argument_list|)
block|,
name|GIMP_HELP_PATH_RAISE
block|}
block|,
block|{
literal|"vectors-raise-to-top"
block|,
literal|"go-top"
block|,
name|NC_
argument_list|(
literal|"vectors-action"
argument_list|,
literal|"Raise Path to _Top"
argument_list|)
block|,
name|NULL
block|,
name|NC_
argument_list|(
literal|"vectors-action"
argument_list|,
literal|"Raise this path to the top"
argument_list|)
block|,
name|G_CALLBACK
argument_list|(
name|vectors_raise_to_top_cmd_callback
argument_list|)
block|,
name|GIMP_HELP_PATH_RAISE_TO_TOP
block|}
block|,
block|{
literal|"vectors-lower"
block|,
literal|"go-down"
block|,
name|NC_
argument_list|(
literal|"vectors-action"
argument_list|,
literal|"_Lower Path"
argument_list|)
block|,
name|NULL
block|,
name|NC_
argument_list|(
literal|"vectors-action"
argument_list|,
literal|"Lower this path"
argument_list|)
block|,
name|G_CALLBACK
argument_list|(
name|vectors_lower_cmd_callback
argument_list|)
block|,
name|GIMP_HELP_PATH_LOWER
block|}
block|,
block|{
literal|"vectors-lower-to-bottom"
block|,
literal|"go-bottom"
block|,
name|NC_
argument_list|(
literal|"vectors-action"
argument_list|,
literal|"Lower Path to _Bottom"
argument_list|)
block|,
name|NULL
block|,
name|NC_
argument_list|(
literal|"vectors-action"
argument_list|,
literal|"Lower this path to the bottom"
argument_list|)
block|,
name|G_CALLBACK
argument_list|(
name|vectors_lower_to_bottom_cmd_callback
argument_list|)
block|,
name|GIMP_HELP_PATH_LOWER_TO_BOTTOM
block|}
block|,
block|{
literal|"vectors-stroke"
block|,
name|GIMP_STOCK_PATH_STROKE
block|,
name|NC_
argument_list|(
literal|"vectors-action"
argument_list|,
literal|"Stro_ke Path..."
argument_list|)
block|,
name|NULL
block|,
name|NC_
argument_list|(
literal|"vectors-action"
argument_list|,
literal|"Paint along the path"
argument_list|)
block|,
name|G_CALLBACK
argument_list|(
name|vectors_stroke_cmd_callback
argument_list|)
block|,
name|GIMP_HELP_PATH_STROKE
block|}
block|,
block|{
literal|"vectors-stroke-last-values"
block|,
name|GIMP_STOCK_PATH_STROKE
block|,
name|NC_
argument_list|(
literal|"vectors-action"
argument_list|,
literal|"Stro_ke Path"
argument_list|)
block|,
name|NULL
block|,
name|NC_
argument_list|(
literal|"vectors-action"
argument_list|,
literal|"Paint along the path with last values"
argument_list|)
block|,
name|G_CALLBACK
argument_list|(
name|vectors_stroke_last_vals_cmd_callback
argument_list|)
block|,
name|GIMP_HELP_PATH_STROKE
block|}
block|,
block|{
literal|"vectors-copy"
block|,
literal|"edit-copy"
block|,
name|NC_
argument_list|(
literal|"vectors-action"
argument_list|,
literal|"Co_py Path"
argument_list|)
block|,
literal|""
block|,
name|NULL
block|,
name|G_CALLBACK
argument_list|(
name|vectors_copy_cmd_callback
argument_list|)
block|,
name|GIMP_HELP_PATH_COPY
block|}
block|,
block|{
literal|"vectors-paste"
block|,
literal|"edit-paste"
block|,
name|NC_
argument_list|(
literal|"vectors-action"
argument_list|,
literal|"Paste Pat_h"
argument_list|)
block|,
literal|""
block|,
name|NULL
block|,
name|G_CALLBACK
argument_list|(
name|vectors_paste_cmd_callback
argument_list|)
block|,
name|GIMP_HELP_PATH_PASTE
block|}
block|,
block|{
literal|"vectors-export"
block|,
literal|"document-save"
block|,
name|NC_
argument_list|(
literal|"vectors-action"
argument_list|,
literal|"E_xport Path..."
argument_list|)
block|,
literal|""
block|,
name|NULL
block|,
name|G_CALLBACK
argument_list|(
name|vectors_export_cmd_callback
argument_list|)
block|,
name|GIMP_HELP_PATH_EXPORT
block|}
block|,
block|{
literal|"vectors-import"
block|,
literal|"document-open"
block|,
name|NC_
argument_list|(
literal|"vectors-action"
argument_list|,
literal|"I_mport Path..."
argument_list|)
block|,
literal|""
block|,
name|NULL
block|,
name|G_CALLBACK
argument_list|(
name|vectors_import_cmd_callback
argument_list|)
block|,
name|GIMP_HELP_PATH_IMPORT
block|}
block|}
decl_stmt|;
end_decl_stmt

begin_decl_stmt
DECL|variable|vectors_toggle_actions
specifier|static
specifier|const
name|GimpToggleActionEntry
name|vectors_toggle_actions
index|[]
init|=
block|{
block|{
literal|"vectors-visible"
block|,
name|GIMP_STOCK_VISIBLE
block|,
name|NC_
argument_list|(
literal|"vectors-action"
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
name|vectors_visible_cmd_callback
argument_list|)
block|,
name|FALSE
block|,
name|GIMP_HELP_PATH_VISIBLE
block|}
block|,
block|{
literal|"vectors-linked"
block|,
name|GIMP_STOCK_LINKED
block|,
name|NC_
argument_list|(
literal|"vectors-action"
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
name|vectors_linked_cmd_callback
argument_list|)
block|,
name|FALSE
block|,
name|GIMP_HELP_PATH_LINKED
block|}
block|,
block|{
literal|"vectors-lock-content"
block|,
name|NULL
comment|/* GIMP_STOCK_LOCK */
block|,
name|NC_
argument_list|(
literal|"vectors-action"
argument_list|,
literal|"L_ock strokes"
argument_list|)
block|,
name|NULL
block|,
name|NULL
block|,
name|G_CALLBACK
argument_list|(
name|vectors_lock_content_cmd_callback
argument_list|)
block|,
name|FALSE
block|,
name|GIMP_HELP_PATH_LOCK_STROKES
block|}
block|,
block|{
literal|"vectors-lock-position"
block|,
name|GIMP_STOCK_TOOL_MOVE
block|,
name|NC_
argument_list|(
literal|"vectors-action"
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
name|vectors_lock_position_cmd_callback
argument_list|)
block|,
name|FALSE
block|,
name|GIMP_HELP_PATH_LOCK_POSITION
block|}
block|}
decl_stmt|;
end_decl_stmt

begin_decl_stmt
DECL|variable|vectors_to_selection_actions
specifier|static
specifier|const
name|GimpEnumActionEntry
name|vectors_to_selection_actions
index|[]
init|=
block|{
block|{
literal|"vectors-selection-replace"
block|,
name|GIMP_STOCK_SELECTION_REPLACE
block|,
name|NC_
argument_list|(
literal|"vectors-action"
argument_list|,
literal|"Path to Sele_ction"
argument_list|)
block|,
name|NULL
block|,
name|NC_
argument_list|(
literal|"vectors-action"
argument_list|,
literal|"Path to selection"
argument_list|)
block|,
name|GIMP_CHANNEL_OP_REPLACE
block|,
name|FALSE
block|,
name|GIMP_HELP_PATH_SELECTION_REPLACE
block|}
block|,
block|{
literal|"vectors-selection-from-vectors"
block|,
name|GIMP_STOCK_SELECTION_REPLACE
block|,
name|NC_
argument_list|(
literal|"vectors-action"
argument_list|,
literal|"Fr_om Path"
argument_list|)
block|,
literal|"<shift>V"
block|,
name|NC_
argument_list|(
literal|"vectors-action"
argument_list|,
literal|"Replace selection with path"
argument_list|)
block|,
name|GIMP_CHANNEL_OP_REPLACE
block|,
name|FALSE
block|,
name|GIMP_HELP_PATH_SELECTION_REPLACE
block|}
block|,
block|{
literal|"vectors-selection-add"
block|,
name|GIMP_STOCK_SELECTION_ADD
block|,
name|NC_
argument_list|(
literal|"vectors-action"
argument_list|,
literal|"_Add to Selection"
argument_list|)
block|,
name|NULL
block|,
name|NC_
argument_list|(
literal|"vectors-action"
argument_list|,
literal|"Add path to selection"
argument_list|)
block|,
name|GIMP_CHANNEL_OP_ADD
block|,
name|FALSE
block|,
name|GIMP_HELP_PATH_SELECTION_ADD
block|}
block|,
block|{
literal|"vectors-selection-subtract"
block|,
name|GIMP_STOCK_SELECTION_SUBTRACT
block|,
name|NC_
argument_list|(
literal|"vectors-action"
argument_list|,
literal|"_Subtract from Selection"
argument_list|)
block|,
name|NULL
block|,
name|NC_
argument_list|(
literal|"vectors-action"
argument_list|,
literal|"Subtract path from selection"
argument_list|)
block|,
name|GIMP_CHANNEL_OP_SUBTRACT
block|,
name|FALSE
block|,
name|GIMP_HELP_PATH_SELECTION_SUBTRACT
block|}
block|,
block|{
literal|"vectors-selection-intersect"
block|,
name|GIMP_STOCK_SELECTION_INTERSECT
block|,
name|NC_
argument_list|(
literal|"vectors-action"
argument_list|,
literal|"_Intersect with Selection"
argument_list|)
block|,
name|NULL
block|,
name|NC_
argument_list|(
literal|"vectors-action"
argument_list|,
literal|"Intersect path with selection"
argument_list|)
block|,
name|GIMP_CHANNEL_OP_INTERSECT
block|,
name|FALSE
block|,
name|GIMP_HELP_PATH_SELECTION_INTERSECT
block|}
block|}
decl_stmt|;
end_decl_stmt

begin_decl_stmt
DECL|variable|vectors_selection_to_vectors_actions
specifier|static
specifier|const
name|GimpEnumActionEntry
name|vectors_selection_to_vectors_actions
index|[]
init|=
block|{
block|{
literal|"vectors-selection-to-vectors"
block|,
name|GIMP_STOCK_SELECTION_TO_PATH
block|,
name|NC_
argument_list|(
literal|"vectors-action"
argument_list|,
literal|"Selecti_on to Path"
argument_list|)
block|,
name|NULL
block|,
name|NC_
argument_list|(
literal|"vectors-action"
argument_list|,
literal|"Selection to path"
argument_list|)
block|,
name|FALSE
block|,
name|FALSE
block|,
name|GIMP_HELP_SELECTION_TO_PATH
block|}
block|,
block|{
literal|"vectors-selection-to-vectors-short"
block|,
name|GIMP_STOCK_SELECTION_TO_PATH
block|,
name|NC_
argument_list|(
literal|"vectors-action"
argument_list|,
literal|"To _Path"
argument_list|)
block|,
name|NULL
block|,
name|NC_
argument_list|(
literal|"vectors-action"
argument_list|,
literal|"Selection to path"
argument_list|)
block|,
name|FALSE
block|,
name|FALSE
block|,
name|GIMP_HELP_SELECTION_TO_PATH
block|}
block|,
block|{
literal|"vectors-selection-to-vectors-advanced"
block|,
name|GIMP_STOCK_SELECTION_TO_PATH
block|,
name|NC_
argument_list|(
literal|"vectors-action"
argument_list|,
literal|"Selection to Path (_Advanced)"
argument_list|)
block|,
name|NULL
block|,
name|NC_
argument_list|(
literal|"vectors-action"
argument_list|,
literal|"Advanced options"
argument_list|)
block|,
name|TRUE
block|,
name|FALSE
block|,
name|GIMP_HELP_SELECTION_TO_PATH
block|}
block|}
decl_stmt|;
end_decl_stmt

begin_function
name|void
DECL|function|vectors_actions_setup (GimpActionGroup * group)
name|vectors_actions_setup
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
literal|"vectors-action"
argument_list|,
name|vectors_actions
argument_list|,
name|G_N_ELEMENTS
argument_list|(
name|vectors_actions
argument_list|)
argument_list|)
expr_stmt|;
name|gimp_action_group_add_toggle_actions
argument_list|(
name|group
argument_list|,
literal|"vectors-action"
argument_list|,
name|vectors_toggle_actions
argument_list|,
name|G_N_ELEMENTS
argument_list|(
name|vectors_toggle_actions
argument_list|)
argument_list|)
expr_stmt|;
name|gimp_action_group_add_enum_actions
argument_list|(
name|group
argument_list|,
literal|"vectors-action"
argument_list|,
name|vectors_to_selection_actions
argument_list|,
name|G_N_ELEMENTS
argument_list|(
name|vectors_to_selection_actions
argument_list|)
argument_list|,
name|G_CALLBACK
argument_list|(
name|vectors_to_selection_cmd_callback
argument_list|)
argument_list|)
expr_stmt|;
name|gimp_action_group_add_enum_actions
argument_list|(
name|group
argument_list|,
literal|"vectors-action"
argument_list|,
name|vectors_selection_to_vectors_actions
argument_list|,
name|G_N_ELEMENTS
argument_list|(
name|vectors_selection_to_vectors_actions
argument_list|)
argument_list|,
name|G_CALLBACK
argument_list|(
name|vectors_selection_to_vectors_cmd_callback
argument_list|)
argument_list|)
expr_stmt|;
block|}
end_function

begin_function
name|void
DECL|function|vectors_actions_update (GimpActionGroup * group,gpointer data)
name|vectors_actions_update
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
name|GimpVectors
modifier|*
name|vectors
init|=
name|NULL
decl_stmt|;
name|GimpDrawable
modifier|*
name|drawable
init|=
name|NULL
decl_stmt|;
name|gint
name|n_vectors
init|=
literal|0
decl_stmt|;
name|gboolean
name|mask_empty
init|=
name|TRUE
decl_stmt|;
name|gboolean
name|visible
init|=
name|FALSE
decl_stmt|;
name|gboolean
name|linked
init|=
name|FALSE
decl_stmt|;
name|gboolean
name|locked
init|=
name|FALSE
decl_stmt|;
name|gboolean
name|can_lock
init|=
name|FALSE
decl_stmt|;
name|gboolean
name|locked_pos
init|=
name|FALSE
decl_stmt|;
name|gboolean
name|can_lock_pos
init|=
name|FALSE
decl_stmt|;
name|gboolean
name|dr_writable
init|=
name|FALSE
decl_stmt|;
name|gboolean
name|dr_children
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
name|n_vectors
operator|=
name|gimp_image_get_n_vectors
argument_list|(
name|image
argument_list|)
expr_stmt|;
name|mask_empty
operator|=
name|gimp_channel_is_empty
argument_list|(
name|gimp_image_get_mask
argument_list|(
name|image
argument_list|)
argument_list|)
expr_stmt|;
name|vectors
operator|=
name|gimp_image_get_active_vectors
argument_list|(
name|image
argument_list|)
expr_stmt|;
if|if
condition|(
name|vectors
condition|)
block|{
name|GimpItem
modifier|*
name|item
init|=
name|GIMP_ITEM
argument_list|(
name|vectors
argument_list|)
decl_stmt|;
name|GList
modifier|*
name|vectors_list
decl_stmt|;
name|GList
modifier|*
name|list
decl_stmt|;
name|visible
operator|=
name|gimp_item_get_visible
argument_list|(
name|item
argument_list|)
expr_stmt|;
name|linked
operator|=
name|gimp_item_get_linked
argument_list|(
name|item
argument_list|)
expr_stmt|;
name|locked
operator|=
name|gimp_item_get_lock_content
argument_list|(
name|item
argument_list|)
expr_stmt|;
name|can_lock
operator|=
name|gimp_item_can_lock_content
argument_list|(
name|item
argument_list|)
expr_stmt|;
name|locked_pos
operator|=
name|gimp_item_get_lock_position
argument_list|(
name|item
argument_list|)
expr_stmt|;
name|can_lock_pos
operator|=
name|gimp_item_can_lock_position
argument_list|(
name|item
argument_list|)
expr_stmt|;
name|vectors_list
operator|=
name|gimp_item_get_container_iter
argument_list|(
name|item
argument_list|)
expr_stmt|;
name|list
operator|=
name|g_list_find
argument_list|(
name|vectors_list
argument_list|,
name|vectors
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
name|drawable
operator|=
name|gimp_image_get_active_drawable
argument_list|(
name|image
argument_list|)
expr_stmt|;
if|if
condition|(
name|drawable
condition|)
block|{
name|GimpItem
modifier|*
name|item
init|=
name|GIMP_ITEM
argument_list|(
name|drawable
argument_list|)
decl_stmt|;
name|dr_writable
operator|=
operator|!
name|gimp_item_is_content_locked
argument_list|(
name|item
argument_list|)
expr_stmt|;
if|if
condition|(
name|gimp_viewable_get_children
argument_list|(
name|GIMP_VIEWABLE
argument_list|(
name|item
argument_list|)
argument_list|)
condition|)
name|dr_children
operator|=
name|TRUE
expr_stmt|;
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
DECL|macro|SET_ACTIVE (action,condition)
define|#
directive|define
name|SET_ACTIVE
parameter_list|(
name|action
parameter_list|,
name|condition
parameter_list|)
define|\
value|gimp_action_group_set_action_active (group, action, (condition) != 0)
name|SET_SENSITIVE
argument_list|(
literal|"vectors-path-tool"
argument_list|,
name|vectors
argument_list|)
expr_stmt|;
name|SET_SENSITIVE
argument_list|(
literal|"vectors-edit-attributes"
argument_list|,
name|vectors
argument_list|)
expr_stmt|;
name|SET_SENSITIVE
argument_list|(
literal|"vectors-new"
argument_list|,
name|image
argument_list|)
expr_stmt|;
name|SET_SENSITIVE
argument_list|(
literal|"vectors-new-last-values"
argument_list|,
name|image
argument_list|)
expr_stmt|;
name|SET_SENSITIVE
argument_list|(
literal|"vectors-duplicate"
argument_list|,
name|vectors
argument_list|)
expr_stmt|;
name|SET_SENSITIVE
argument_list|(
literal|"vectors-delete"
argument_list|,
name|vectors
argument_list|)
expr_stmt|;
name|SET_SENSITIVE
argument_list|(
literal|"vectors-merge-visible"
argument_list|,
name|n_vectors
operator|>
literal|1
argument_list|)
expr_stmt|;
name|SET_SENSITIVE
argument_list|(
literal|"vectors-raise"
argument_list|,
name|vectors
operator|&&
name|prev
argument_list|)
expr_stmt|;
name|SET_SENSITIVE
argument_list|(
literal|"vectors-raise-to-top"
argument_list|,
name|vectors
operator|&&
name|prev
argument_list|)
expr_stmt|;
name|SET_SENSITIVE
argument_list|(
literal|"vectors-lower"
argument_list|,
name|vectors
operator|&&
name|next
argument_list|)
expr_stmt|;
name|SET_SENSITIVE
argument_list|(
literal|"vectors-lower-to-bottom"
argument_list|,
name|vectors
operator|&&
name|next
argument_list|)
expr_stmt|;
name|SET_SENSITIVE
argument_list|(
literal|"vectors-copy"
argument_list|,
name|vectors
argument_list|)
expr_stmt|;
name|SET_SENSITIVE
argument_list|(
literal|"vectors-paste"
argument_list|,
name|image
argument_list|)
expr_stmt|;
name|SET_SENSITIVE
argument_list|(
literal|"vectors-export"
argument_list|,
name|vectors
argument_list|)
expr_stmt|;
name|SET_SENSITIVE
argument_list|(
literal|"vectors-import"
argument_list|,
name|image
argument_list|)
expr_stmt|;
name|SET_SENSITIVE
argument_list|(
literal|"vectors-visible"
argument_list|,
name|vectors
argument_list|)
expr_stmt|;
name|SET_SENSITIVE
argument_list|(
literal|"vectors-linked"
argument_list|,
name|vectors
argument_list|)
expr_stmt|;
name|SET_SENSITIVE
argument_list|(
literal|"vectors-lock-content"
argument_list|,
name|can_lock
argument_list|)
expr_stmt|;
name|SET_SENSITIVE
argument_list|(
literal|"vectors-lock-position"
argument_list|,
name|can_lock_pos
argument_list|)
expr_stmt|;
name|SET_ACTIVE
argument_list|(
literal|"vectors-visible"
argument_list|,
name|visible
argument_list|)
expr_stmt|;
name|SET_ACTIVE
argument_list|(
literal|"vectors-linked"
argument_list|,
name|linked
argument_list|)
expr_stmt|;
name|SET_ACTIVE
argument_list|(
literal|"vectors-lock-content"
argument_list|,
name|locked
argument_list|)
expr_stmt|;
name|SET_ACTIVE
argument_list|(
literal|"vectors-lock-position"
argument_list|,
name|locked_pos
argument_list|)
expr_stmt|;
name|SET_SENSITIVE
argument_list|(
literal|"vectors-selection-to-vectors"
argument_list|,
name|image
operator|&&
operator|!
name|mask_empty
argument_list|)
expr_stmt|;
name|SET_SENSITIVE
argument_list|(
literal|"vectors-selection-to-vectors-short"
argument_list|,
name|image
operator|&&
operator|!
name|mask_empty
argument_list|)
expr_stmt|;
name|SET_SENSITIVE
argument_list|(
literal|"vectors-selection-to-vectors-advanced"
argument_list|,
name|image
operator|&&
operator|!
name|mask_empty
argument_list|)
expr_stmt|;
name|SET_SENSITIVE
argument_list|(
literal|"vectors-stroke"
argument_list|,
name|vectors
operator|&&
name|dr_writable
operator|&&
operator|!
name|dr_children
argument_list|)
expr_stmt|;
name|SET_SENSITIVE
argument_list|(
literal|"vectors-stroke-last-values"
argument_list|,
name|vectors
operator|&&
name|dr_writable
operator|&&
operator|!
name|dr_children
argument_list|)
expr_stmt|;
name|SET_SENSITIVE
argument_list|(
literal|"vectors-selection-replace"
argument_list|,
name|vectors
argument_list|)
expr_stmt|;
name|SET_SENSITIVE
argument_list|(
literal|"vectors-selection-from-vectors"
argument_list|,
name|vectors
argument_list|)
expr_stmt|;
name|SET_SENSITIVE
argument_list|(
literal|"vectors-selection-add"
argument_list|,
name|vectors
argument_list|)
expr_stmt|;
name|SET_SENSITIVE
argument_list|(
literal|"vectors-selection-subtract"
argument_list|,
name|vectors
argument_list|)
expr_stmt|;
name|SET_SENSITIVE
argument_list|(
literal|"vectors-selection-intersect"
argument_list|,
name|vectors
argument_list|)
expr_stmt|;
undef|#
directive|undef
name|SET_SENSITIVE
undef|#
directive|undef
name|SET_ACTIVE
block|}
end_function

end_unit

