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
file|"core/gimpimage.h"
end_include

begin_include
include|#
directive|include
file|"core/gimplist.h"
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
file|"widgets/gimpitemtreeview.h"
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
name|N_
argument_list|(
literal|"Paths Menu"
argument_list|)
block|}
block|,
block|{
literal|"vectors-path-tool"
block|,
name|GIMP_STOCK_TOOL_PATH
block|,
name|N_
argument_list|(
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
name|GIMP_STOCK_EDIT
block|,
name|N_
argument_list|(
literal|"_Edit Path Attributes..."
argument_list|)
block|,
name|NULL
block|,
name|NULL
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
name|GTK_STOCK_NEW
block|,
name|N_
argument_list|(
literal|"_New Path..."
argument_list|)
block|,
literal|""
block|,
name|NULL
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
literal|"vectors-duplicate"
block|,
name|GIMP_STOCK_DUPLICATE
block|,
name|N_
argument_list|(
literal|"D_uplicate Path"
argument_list|)
block|,
name|NULL
block|,
name|NULL
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
name|GTK_STOCK_DELETE
block|,
name|N_
argument_list|(
literal|"_Delete Path"
argument_list|)
block|,
literal|""
block|,
name|NULL
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
name|N_
argument_list|(
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
name|GTK_STOCK_GO_UP
block|,
name|N_
argument_list|(
literal|"_Raise Path"
argument_list|)
block|,
literal|""
block|,
name|NULL
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
name|GTK_STOCK_GOTO_TOP
block|,
name|N_
argument_list|(
literal|"Raise Path to _Top"
argument_list|)
block|,
literal|""
block|,
name|NULL
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
name|GTK_STOCK_GO_DOWN
block|,
name|N_
argument_list|(
literal|"_Lower Path"
argument_list|)
block|,
literal|""
block|,
name|NULL
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
name|GTK_STOCK_GOTO_BOTTOM
block|,
name|N_
argument_list|(
literal|"Lower Path to _Bottom"
argument_list|)
block|,
literal|""
block|,
name|NULL
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
literal|"vectors-selection-to-vectors"
block|,
name|GIMP_STOCK_SELECTION_TO_PATH
block|,
name|N_
argument_list|(
literal|"Selecti_on to Path"
argument_list|)
block|,
name|NULL
block|,
name|NULL
block|,
name|G_CALLBACK
argument_list|(
name|vectors_selection_to_vectors_cmd_callback
argument_list|)
block|,
name|GIMP_HELP_SELECTION_TO_PATH
block|}
block|,
block|{
literal|"vectors-stroke"
block|,
name|GIMP_STOCK_PATH_STROKE
block|,
name|N_
argument_list|(
literal|"Stro_ke Path..."
argument_list|)
block|,
name|NULL
block|,
name|NULL
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
literal|"vectors-copy"
block|,
name|GTK_STOCK_COPY
block|,
name|N_
argument_list|(
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
name|GTK_STOCK_PASTE
block|,
name|N_
argument_list|(
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
literal|"vectors-import"
block|,
name|GTK_STOCK_OPEN
block|,
name|N_
argument_list|(
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
block|,
block|{
literal|"vectors-export"
block|,
name|GTK_STOCK_SAVE
block|,
name|N_
argument_list|(
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
block|}
decl_stmt|;
end_decl_stmt

begin_decl_stmt
DECL|variable|vectors_to_selection_actions
specifier|static
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
name|N_
argument_list|(
literal|"Path to Sele_ction"
argument_list|)
block|,
name|NULL
block|,
name|NULL
block|,
name|GIMP_CHANNEL_OP_REPLACE
block|,
name|GIMP_HELP_PATH_SELECTION_REPLACE
block|}
block|,
block|{
literal|"vectors-selection-add"
block|,
name|GIMP_STOCK_SELECTION_ADD
block|,
name|N_
argument_list|(
literal|"_Add to Selection"
argument_list|)
block|,
name|NULL
block|,
name|NULL
block|,
name|GIMP_CHANNEL_OP_ADD
block|,
name|GIMP_HELP_PATH_SELECTION_ADD
block|}
block|,
block|{
literal|"vectors-selection-subtract"
block|,
name|GIMP_STOCK_SELECTION_SUBTRACT
block|,
name|N_
argument_list|(
literal|"_Subtract from Selection"
argument_list|)
block|,
name|NULL
block|,
name|NULL
block|,
name|GIMP_CHANNEL_OP_SUBTRACT
block|,
name|GIMP_HELP_PATH_SELECTION_SUBTRACT
block|}
block|,
block|{
literal|"vectors-selection-intersect"
block|,
name|GIMP_STOCK_SELECTION_INTERSECT
block|,
name|N_
argument_list|(
literal|"_Intersect with Selection"
argument_list|)
block|,
name|NULL
block|,
name|NULL
block|,
name|GIMP_CHANNEL_OP_INTERSECT
block|,
name|GIMP_HELP_PATH_SELECTION_INTERSECT
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
name|vectors_actions
argument_list|,
name|G_N_ELEMENTS
argument_list|(
name|vectors_actions
argument_list|)
argument_list|)
expr_stmt|;
name|gimp_action_group_add_enum_actions
argument_list|(
name|group
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
name|gimage
init|=
name|NULL
decl_stmt|;
name|GimpVectors
modifier|*
name|vectors
init|=
name|NULL
decl_stmt|;
name|gboolean
name|mask_empty
init|=
name|TRUE
decl_stmt|;
name|gboolean
name|global_buf
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
name|GIMP_IS_ITEM_TREE_VIEW
argument_list|(
name|data
argument_list|)
condition|)
name|gimage
operator|=
name|GIMP_ITEM_TREE_VIEW
argument_list|(
name|data
argument_list|)
operator|->
name|gimage
expr_stmt|;
if|if
condition|(
name|gimage
condition|)
block|{
name|GList
modifier|*
name|list
decl_stmt|;
name|vectors
operator|=
name|gimp_image_get_active_vectors
argument_list|(
name|gimage
argument_list|)
expr_stmt|;
name|mask_empty
operator|=
name|gimp_channel_is_empty
argument_list|(
name|gimp_image_get_mask
argument_list|(
name|gimage
argument_list|)
argument_list|)
expr_stmt|;
name|global_buf
operator|=
name|FALSE
expr_stmt|;
for|for
control|(
name|list
operator|=
name|GIMP_LIST
argument_list|(
name|gimage
operator|->
name|vectors
argument_list|)
operator|->
name|list
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
if|if
condition|(
name|vectors
operator|==
operator|(
name|GimpVectors
operator|*
operator|)
name|list
operator|->
name|data
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
break|break;
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
name|gimage
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
literal|"vectors-selection-to-vectors"
argument_list|,
operator|!
name|mask_empty
argument_list|)
expr_stmt|;
name|SET_SENSITIVE
argument_list|(
literal|"vectors-stroke"
argument_list|,
name|vectors
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
name|global_buf
argument_list|)
expr_stmt|;
name|SET_SENSITIVE
argument_list|(
literal|"vectors-import"
argument_list|,
name|gimage
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
literal|"vectors-selection-replace"
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
block|}
end_function

end_unit

