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
file|"core/gimplist.h"
end_include

begin_include
include|#
directive|include
file|"text/gimptextlayer.h"
end_include

begin_include
include|#
directive|include
file|"widgets/gimphelp-ids.h"
end_include

begin_include
include|#
directive|include
file|"widgets/gimpactiongroup.h"
end_include

begin_include
include|#
directive|include
file|"widgets/gimpitemtreeview.h"
end_include

begin_include
include|#
directive|include
file|"display/gimpdisplay.h"
end_include

begin_include
include|#
directive|include
file|"display/gimpdisplayshell.h"
end_include

begin_include
include|#
directive|include
file|"layers-actions.h"
end_include

begin_include
include|#
directive|include
file|"gui/layers-commands.h"
end_include

begin_include
include|#
directive|include
file|"gimp-intl.h"
end_include

begin_decl_stmt
DECL|variable|layers_actions
specifier|static
name|GimpActionEntry
name|layers_actions
index|[]
init|=
block|{
block|{
literal|"layers-menu"
block|,
name|NULL
block|,
name|N_
argument_list|(
literal|"_Layer"
argument_list|)
block|}
block|,
block|{
literal|"layers-stack-menu"
block|,
name|NULL
block|,
name|N_
argument_list|(
literal|"Stac_k"
argument_list|)
block|}
block|,
block|{
literal|"layers-colors-menu"
block|,
name|NULL
block|,
name|N_
argument_list|(
literal|"_Colors"
argument_list|)
block|}
block|,
block|{
literal|"layers-colors-auto-menu"
block|,
name|NULL
block|,
name|N_
argument_list|(
literal|"_Auto"
argument_list|)
block|}
block|,
block|{
literal|"layers-mask-menu"
block|,
name|NULL
block|,
name|N_
argument_list|(
literal|"_Mask"
argument_list|)
block|}
block|,
block|{
literal|"layers-transparency-menu"
block|,
name|NULL
block|,
name|N_
argument_list|(
literal|"Tr_ansparency"
argument_list|)
block|}
block|,
block|{
literal|"layers-transform-menu"
block|,
name|NULL
block|,
name|N_
argument_list|(
literal|"_Transform"
argument_list|)
block|}
block|,
block|{
literal|"layers-text-tool"
block|,
name|GIMP_STOCK_TOOL_TEXT
block|,
name|N_
argument_list|(
literal|"Te_xt Tool"
argument_list|)
block|,
name|NULL
block|,
name|NULL
block|,
name|G_CALLBACK
argument_list|(
name|layers_text_tool_cmd_callback
argument_list|)
block|,
name|GIMP_HELP_TOOL_TEXT
block|}
block|,
block|{
literal|"layers-edit-attributes"
block|,
name|GIMP_STOCK_EDIT
block|,
name|N_
argument_list|(
literal|"_Edit Layer Attributes..."
argument_list|)
block|,
name|NULL
block|,
name|NULL
block|,
name|G_CALLBACK
argument_list|(
name|layers_edit_attributes_cmd_callback
argument_list|)
block|,
name|GIMP_HELP_LAYER_EDIT
block|}
block|,
block|{
literal|"layers-new"
block|,
name|GTK_STOCK_NEW
block|,
name|N_
argument_list|(
literal|"_New Layer..."
argument_list|)
block|,
literal|""
block|,
name|NULL
block|,
name|G_CALLBACK
argument_list|(
name|layers_new_cmd_callback
argument_list|)
block|,
name|GIMP_HELP_LAYER_NEW
block|}
block|,
block|{
literal|"layers-duplicate"
block|,
name|GIMP_STOCK_DUPLICATE
block|,
name|N_
argument_list|(
literal|"D_uplicate Layer"
argument_list|)
block|,
name|NULL
block|,
name|NULL
block|,
name|G_CALLBACK
argument_list|(
name|layers_duplicate_cmd_callback
argument_list|)
block|,
name|GIMP_HELP_LAYER_DUPLICATE
block|}
block|,
block|{
literal|"layers-delete"
block|,
name|GTK_STOCK_DELETE
block|,
name|N_
argument_list|(
literal|"_Delete Layer"
argument_list|)
block|,
literal|""
block|,
name|NULL
block|,
name|G_CALLBACK
argument_list|(
name|layers_delete_cmd_callback
argument_list|)
block|,
name|GIMP_HELP_LAYER_DELETE
block|}
block|,
block|{
literal|"layers-select-previous"
block|,
name|NULL
block|,
name|N_
argument_list|(
literal|"Select _Previous Layer"
argument_list|)
block|,
literal|"Prior"
block|,
name|NULL
block|,
name|G_CALLBACK
argument_list|(
name|layers_select_previous_cmd_callback
argument_list|)
block|,
name|GIMP_HELP_LAYER_PREVIOUS
block|}
block|,
block|{
literal|"layers-select-top"
block|,
name|NULL
block|,
name|N_
argument_list|(
literal|"Select _Top Layer"
argument_list|)
block|,
literal|"Home"
block|,
name|NULL
block|,
name|G_CALLBACK
argument_list|(
name|layers_select_top_cmd_callback
argument_list|)
block|,
name|GIMP_HELP_LAYER_TOP
block|}
block|,
block|{
literal|"layers-select-next"
block|,
name|NULL
block|,
name|N_
argument_list|(
literal|"Select _Next Layer"
argument_list|)
block|,
literal|"Next"
block|,
name|NULL
block|,
name|G_CALLBACK
argument_list|(
name|layers_select_next_cmd_callback
argument_list|)
block|,
name|GIMP_HELP_LAYER_NEXT
block|}
block|,
block|{
literal|"layer-select-bottom"
block|,
name|NULL
block|,
name|N_
argument_list|(
literal|"Select _Bottom Layer"
argument_list|)
block|,
literal|"End"
block|,
name|NULL
block|,
name|G_CALLBACK
argument_list|(
name|layers_select_bottom_cmd_callback
argument_list|)
block|,
name|GIMP_HELP_LAYER_BOTTOM
block|}
block|,
block|{
literal|"layers-raise"
block|,
name|GTK_STOCK_GO_UP
block|,
name|N_
argument_list|(
literal|"_Raise Layer"
argument_list|)
block|,
literal|""
block|,
name|NULL
block|,
name|G_CALLBACK
argument_list|(
name|layers_raise_cmd_callback
argument_list|)
block|,
name|GIMP_HELP_LAYER_RAISE
block|}
block|,
block|{
literal|"layers-raise-to-top"
block|,
name|GTK_STOCK_GOTO_TOP
block|,
name|N_
argument_list|(
literal|"Layer to _Top"
argument_list|)
block|,
literal|""
block|,
name|NULL
block|,
name|G_CALLBACK
argument_list|(
name|layers_raise_to_top_cmd_callback
argument_list|)
block|,
name|GIMP_HELP_LAYER_RAISE_TO_TOP
block|}
block|,
block|{
literal|"layers-lower"
block|,
name|GTK_STOCK_GO_DOWN
block|,
name|N_
argument_list|(
literal|"_Lower Layer"
argument_list|)
block|,
literal|""
block|,
name|NULL
block|,
name|G_CALLBACK
argument_list|(
name|layers_lower_cmd_callback
argument_list|)
block|,
name|GIMP_HELP_LAYER_LOWER
block|}
block|,
block|{
literal|"layers-lower-to-bottom"
block|,
name|GTK_STOCK_GOTO_BOTTOM
block|,
name|N_
argument_list|(
literal|"Layer to _Bottom"
argument_list|)
block|,
literal|""
block|,
name|NULL
block|,
name|G_CALLBACK
argument_list|(
name|layers_lower_to_bottom_cmd_callback
argument_list|)
block|,
name|GIMP_HELP_LAYER_LOWER_TO_BOTTOM
block|}
block|,
block|{
literal|"layers-anchor"
block|,
name|GIMP_STOCK_ANCHOR
block|,
name|N_
argument_list|(
literal|"_Anchor Layer"
argument_list|)
block|,
name|NULL
block|,
name|NULL
block|,
name|G_CALLBACK
argument_list|(
name|layers_anchor_cmd_callback
argument_list|)
block|,
name|GIMP_HELP_LAYER_ANCHOR
block|}
block|,
block|{
literal|"layers-merge-down"
block|,
name|GIMP_STOCK_MERGE_DOWN
block|,
name|N_
argument_list|(
literal|"Merge Do_wn"
argument_list|)
block|,
name|NULL
block|,
name|NULL
block|,
name|G_CALLBACK
argument_list|(
name|layers_merge_down_cmd_callback
argument_list|)
block|,
name|GIMP_HELP_LAYER_MERGE_DOWN
block|}
block|,
block|{
literal|"layers-merge-layers"
block|,
name|NULL
block|,
name|N_
argument_list|(
literal|"Merge _Visible Layers..."
argument_list|)
block|,
name|NULL
block|,
name|NULL
block|,
name|G_CALLBACK
argument_list|(
name|layers_merge_layers_cmd_callback
argument_list|)
block|,
name|GIMP_HELP_IMAGE_MERGE_LAYERS
block|}
block|,
block|{
literal|"layers-flatten-image"
block|,
name|NULL
block|,
name|N_
argument_list|(
literal|"_Flatten Image"
argument_list|)
block|,
name|NULL
block|,
name|NULL
block|,
name|G_CALLBACK
argument_list|(
name|layers_flatten_image_cmd_callback
argument_list|)
block|,
name|GIMP_HELP_IMAGE_FLATTEN
block|}
block|,
block|{
literal|"layers-text-discard"
block|,
name|GIMP_STOCK_TOOL_TEXT
block|,
name|N_
argument_list|(
literal|"_Discard Text Information"
argument_list|)
block|,
name|NULL
block|,
name|NULL
block|,
name|G_CALLBACK
argument_list|(
name|layers_text_discard_cmd_callback
argument_list|)
block|,
name|GIMP_HELP_LAYER_TEXT_DISCARD
block|}
block|,
block|{
literal|"layers-resize"
block|,
name|GIMP_STOCK_RESIZE
block|,
name|N_
argument_list|(
literal|"Layer B_oundary Size..."
argument_list|)
block|,
name|NULL
block|,
name|NULL
block|,
name|G_CALLBACK
argument_list|(
name|layers_resize_cmd_callback
argument_list|)
block|,
name|GIMP_HELP_LAYER_RESIZE
block|}
block|,
block|{
literal|"layers-resize-to-image"
block|,
name|GIMP_STOCK_LAYER_TO_IMAGESIZE
block|,
name|N_
argument_list|(
literal|"Layer to _Image Size"
argument_list|)
block|,
name|NULL
block|,
name|NULL
block|,
name|G_CALLBACK
argument_list|(
name|layers_resize_to_image_cmd_callback
argument_list|)
block|,
name|GIMP_HELP_LAYER_RESIZE_TO_IMAGE
block|}
block|,
block|{
literal|"layers-scale"
block|,
name|GIMP_STOCK_SCALE
block|,
name|N_
argument_list|(
literal|"_Scale Layer..."
argument_list|)
block|,
name|NULL
block|,
name|NULL
block|,
name|G_CALLBACK
argument_list|(
name|layers_scale_cmd_callback
argument_list|)
block|,
name|GIMP_HELP_LAYER_SCALE
block|}
block|,
block|{
literal|"layers-mask-add"
block|,
name|GIMP_STOCK_LAYER_MASK
block|,
name|N_
argument_list|(
literal|"Add La_yer Mask..."
argument_list|)
block|,
name|NULL
block|,
name|NULL
block|,
name|G_CALLBACK
argument_list|(
name|layers_mask_add_cmd_callback
argument_list|)
block|,
name|GIMP_HELP_LAYER_MASK_ADD
block|}
block|,
block|{
literal|"layers-mask-apply"
block|,
name|NULL
block|,
name|N_
argument_list|(
literal|"Apply Layer _Mask"
argument_list|)
block|,
name|NULL
block|,
name|NULL
block|,
name|G_CALLBACK
argument_list|(
name|layers_mask_apply_cmd_callback
argument_list|)
block|,
name|GIMP_HELP_LAYER_MASK_APPLY
block|}
block|,
block|{
literal|"layers-mask-delete"
block|,
name|GTK_STOCK_DELETE
block|,
name|N_
argument_list|(
literal|"Delete Layer Mas_k"
argument_list|)
block|,
literal|""
block|,
name|NULL
block|,
name|G_CALLBACK
argument_list|(
name|layers_mask_delete_cmd_callback
argument_list|)
block|,
name|GIMP_HELP_LAYER_MASK_DELETE
block|}
block|,
block|{
literal|"layers-alpha-add"
block|,
name|GIMP_STOCK_TRANSPARENCY
block|,
name|N_
argument_list|(
literal|"Add Alpha C_hannel"
argument_list|)
block|,
name|NULL
block|,
name|NULL
block|,
name|G_CALLBACK
argument_list|(
name|layers_alpha_add_cmd_callback
argument_list|)
block|,
name|GIMP_HELP_LAYER_ALPHA_ADD
block|}
block|}
decl_stmt|;
end_decl_stmt

begin_decl_stmt
DECL|variable|layers_mask_to_selection_actions
specifier|static
name|GimpEnumActionEntry
name|layers_mask_to_selection_actions
index|[]
init|=
block|{
block|{
literal|"layers-mask-selection-replace"
block|,
name|GIMP_STOCK_SELECTION_REPLACE
block|,
name|N_
argument_list|(
literal|"_Mask to Selection"
argument_list|)
block|,
name|NULL
block|,
name|NULL
block|,
name|GIMP_CHANNEL_OP_REPLACE
block|,
name|GIMP_HELP_LAYER_MASK_SELECTION_REPLACE
block|}
block|,
block|{
literal|"layer-mask-selection-add"
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
name|GIMP_HELP_LAYER_MASK_SELECTION_ADD
block|}
block|,
block|{
literal|"layers-mask-selection-subtract"
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
name|GIMP_HELP_LAYER_MASK_SELECTION_SUBTRACT
block|}
block|,
block|{
literal|"layers-mask-selection-intersect"
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
name|GIMP_HELP_LAYER_MASK_SELECTION_INTERSECT
block|}
block|}
decl_stmt|;
end_decl_stmt

begin_decl_stmt
DECL|variable|layers_alpha_to_selection_actions
specifier|static
name|GimpEnumActionEntry
name|layers_alpha_to_selection_actions
index|[]
init|=
block|{
block|{
literal|"layers-alpha-selection-replace"
block|,
name|GIMP_STOCK_SELECTION_REPLACE
block|,
name|N_
argument_list|(
literal|"Al_pha to Selection"
argument_list|)
block|,
name|NULL
block|,
name|NULL
block|,
name|GIMP_CHANNEL_OP_REPLACE
block|,
name|GIMP_HELP_LAYER_ALPHA_SELECTION_REPLACE
block|}
block|,
block|{
literal|"layers-alpha-selection-add"
block|,
name|GIMP_STOCK_SELECTION_ADD
block|,
name|N_
argument_list|(
literal|"A_dd to Selection"
argument_list|)
block|,
name|NULL
block|,
name|NULL
block|,
name|GIMP_CHANNEL_OP_ADD
block|,
name|GIMP_HELP_LAYER_ALPHA_SELECTION_ADD
block|}
block|,
block|{
literal|"layers-alpha-selection-subtract"
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
name|GIMP_HELP_LAYER_ALPHA_SELECTION_SUBTRACT
block|}
block|,
block|{
literal|"layer-alpha-selection-intersect"
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
name|GIMP_HELP_LAYER_ALPHA_SELECTION_INTERSECT
block|}
block|}
decl_stmt|;
end_decl_stmt

begin_function
name|void
DECL|function|layers_actions_setup (GimpActionGroup * group,gpointer data)
name|layers_actions_setup
parameter_list|(
name|GimpActionGroup
modifier|*
name|group
parameter_list|,
name|gpointer
name|data
parameter_list|)
block|{
name|gimp_action_group_add_actions
argument_list|(
name|group
argument_list|,
name|layers_actions
argument_list|,
name|G_N_ELEMENTS
argument_list|(
name|layers_actions
argument_list|)
argument_list|,
name|data
argument_list|)
expr_stmt|;
name|gimp_action_group_add_enum_actions
argument_list|(
name|group
argument_list|,
name|layers_mask_to_selection_actions
argument_list|,
name|G_N_ELEMENTS
argument_list|(
name|layers_mask_to_selection_actions
argument_list|)
argument_list|,
name|G_CALLBACK
argument_list|(
name|layers_mask_to_selection_cmd_callback
argument_list|)
argument_list|,
name|data
argument_list|)
expr_stmt|;
name|gimp_action_group_add_enum_actions
argument_list|(
name|group
argument_list|,
name|layers_alpha_to_selection_actions
argument_list|,
name|G_N_ELEMENTS
argument_list|(
name|layers_alpha_to_selection_actions
argument_list|)
argument_list|,
name|G_CALLBACK
argument_list|(
name|layers_alpha_to_selection_cmd_callback
argument_list|)
argument_list|,
name|data
argument_list|)
expr_stmt|;
block|}
end_function

begin_function
name|void
DECL|function|layers_actions_update (GimpActionGroup * group,gpointer data)
name|layers_actions_update
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
name|GimpLayer
modifier|*
name|layer
init|=
name|NULL
decl_stmt|;
name|gboolean
name|fs
init|=
name|FALSE
decl_stmt|;
comment|/*  floating sel           */
name|gboolean
name|ac
init|=
name|FALSE
decl_stmt|;
comment|/*  active channel         */
name|gboolean
name|lm
init|=
name|FALSE
decl_stmt|;
comment|/*  layer mask             */
name|gboolean
name|alpha
init|=
name|FALSE
decl_stmt|;
comment|/*  alpha channel present  */
name|gboolean
name|indexed
init|=
name|FALSE
decl_stmt|;
comment|/*  is indexed             */
name|gboolean
name|next_alpha
init|=
name|FALSE
decl_stmt|;
name|gboolean
name|text_layer
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
elseif|else
if|if
condition|(
name|GIMP_IS_DISPLAY_SHELL
argument_list|(
name|data
argument_list|)
condition|)
name|gimage
operator|=
name|GIMP_DISPLAY_SHELL
argument_list|(
name|data
argument_list|)
operator|->
name|gdisp
operator|->
name|gimage
expr_stmt|;
elseif|else
if|if
condition|(
name|GIMP_IS_DISPLAY
argument_list|(
name|data
argument_list|)
condition|)
name|gimage
operator|=
name|GIMP_DISPLAY
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
name|layer
operator|=
name|gimp_image_get_active_layer
argument_list|(
name|gimage
argument_list|)
expr_stmt|;
if|if
condition|(
name|layer
condition|)
name|lm
operator|=
operator|(
name|gimp_layer_get_mask
argument_list|(
name|layer
argument_list|)
operator|)
condition|?
name|TRUE
else|:
name|FALSE
expr_stmt|;
name|fs
operator|=
operator|(
name|gimp_image_floating_sel
argument_list|(
name|gimage
argument_list|)
operator|!=
name|NULL
operator|)
expr_stmt|;
name|ac
operator|=
operator|(
name|gimp_image_get_active_channel
argument_list|(
name|gimage
argument_list|)
operator|!=
name|NULL
operator|)
expr_stmt|;
name|alpha
operator|=
name|layer
operator|&&
name|gimp_drawable_has_alpha
argument_list|(
name|GIMP_DRAWABLE
argument_list|(
name|layer
argument_list|)
argument_list|)
expr_stmt|;
name|indexed
operator|=
operator|(
name|gimp_image_base_type
argument_list|(
name|gimage
argument_list|)
operator|==
name|GIMP_INDEXED
operator|)
expr_stmt|;
for|for
control|(
name|list
operator|=
name|GIMP_LIST
argument_list|(
name|gimage
operator|->
name|layers
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
name|layer
operator|==
operator|(
name|GimpLayer
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
if|if
condition|(
name|next
condition|)
name|next_alpha
operator|=
name|gimp_drawable_has_alpha
argument_list|(
name|GIMP_DRAWABLE
argument_list|(
name|next
operator|->
name|data
argument_list|)
argument_list|)
expr_stmt|;
else|else
name|next_alpha
operator|=
name|FALSE
expr_stmt|;
name|text_layer
operator|=
operator|(
name|layer
operator|&&
name|gimp_drawable_is_text_layer
argument_list|(
name|GIMP_DRAWABLE
argument_list|(
name|layer
argument_list|)
argument_list|)
operator|)
expr_stmt|;
block|}
DECL|macro|SET_VISIBLE (action,condition)
define|#
directive|define
name|SET_VISIBLE
parameter_list|(
name|action
parameter_list|,
name|condition
parameter_list|)
define|\
value|gimp_action_group_set_action_visible (group, action, (condition) != 0)
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
name|SET_VISIBLE
argument_list|(
literal|"layers-text-tool"
argument_list|,
name|text_layer
operator|&&
operator|!
name|ac
argument_list|)
expr_stmt|;
name|SET_SENSITIVE
argument_list|(
literal|"layers-edit-attributes"
argument_list|,
name|layer
operator|&&
operator|!
name|fs
operator|&&
operator|!
name|ac
argument_list|)
expr_stmt|;
name|SET_SENSITIVE
argument_list|(
literal|"layers-new"
argument_list|,
name|gimage
argument_list|)
expr_stmt|;
name|SET_SENSITIVE
argument_list|(
literal|"layers-duplicate"
argument_list|,
name|layer
operator|&&
operator|!
name|fs
operator|&&
operator|!
name|ac
argument_list|)
expr_stmt|;
name|SET_SENSITIVE
argument_list|(
literal|"layers-delete"
argument_list|,
name|layer
operator|&&
operator|!
name|ac
argument_list|)
expr_stmt|;
name|SET_SENSITIVE
argument_list|(
literal|"layers-select-previous"
argument_list|,
name|layer
operator|&&
operator|!
name|fs
operator|&&
operator|!
name|ac
operator|&&
name|prev
argument_list|)
expr_stmt|;
name|SET_SENSITIVE
argument_list|(
literal|"layers-select-top"
argument_list|,
name|layer
operator|&&
operator|!
name|fs
operator|&&
operator|!
name|ac
operator|&&
name|prev
argument_list|)
expr_stmt|;
name|SET_SENSITIVE
argument_list|(
literal|"layers-select-next"
argument_list|,
name|layer
operator|&&
operator|!
name|fs
operator|&&
operator|!
name|ac
operator|&&
name|next
argument_list|)
expr_stmt|;
name|SET_SENSITIVE
argument_list|(
literal|"layers-select-bottom"
argument_list|,
name|layer
operator|&&
operator|!
name|fs
operator|&&
operator|!
name|ac
operator|&&
name|next
argument_list|)
expr_stmt|;
name|SET_SENSITIVE
argument_list|(
literal|"layers-raise"
argument_list|,
name|layer
operator|&&
operator|!
name|fs
operator|&&
operator|!
name|ac
operator|&&
name|alpha
operator|&&
name|prev
argument_list|)
expr_stmt|;
name|SET_SENSITIVE
argument_list|(
literal|"layers-raise-to-top"
argument_list|,
name|layer
operator|&&
operator|!
name|fs
operator|&&
operator|!
name|ac
operator|&&
name|alpha
operator|&&
name|prev
argument_list|)
expr_stmt|;
name|SET_SENSITIVE
argument_list|(
literal|"layers-lower"
argument_list|,
name|layer
operator|&&
operator|!
name|fs
operator|&&
operator|!
name|ac
operator|&&
name|next
operator|&&
name|next_alpha
argument_list|)
expr_stmt|;
name|SET_SENSITIVE
argument_list|(
literal|"layers-lower-to-bottom"
argument_list|,
name|layer
operator|&&
operator|!
name|fs
operator|&&
operator|!
name|ac
operator|&&
name|next
operator|&&
name|next_alpha
argument_list|)
expr_stmt|;
name|SET_SENSITIVE
argument_list|(
literal|"layers-anchor"
argument_list|,
name|layer
operator|&&
name|fs
operator|&&
operator|!
name|ac
argument_list|)
expr_stmt|;
name|SET_SENSITIVE
argument_list|(
literal|"layers-merge-down"
argument_list|,
name|layer
operator|&&
operator|!
name|fs
operator|&&
operator|!
name|ac
operator|&&
name|next
argument_list|)
expr_stmt|;
name|SET_SENSITIVE
argument_list|(
literal|"layers-merge-layers"
argument_list|,
name|layer
operator|&&
operator|!
name|fs
operator|&&
operator|!
name|ac
argument_list|)
expr_stmt|;
name|SET_SENSITIVE
argument_list|(
literal|"layers-flatten-image"
argument_list|,
name|layer
operator|&&
operator|!
name|fs
operator|&&
operator|!
name|ac
argument_list|)
expr_stmt|;
name|SET_VISIBLE
argument_list|(
literal|"layers-text-discard"
argument_list|,
name|text_layer
operator|&&
operator|!
name|ac
argument_list|)
expr_stmt|;
name|SET_SENSITIVE
argument_list|(
literal|"layers-resize"
argument_list|,
name|layer
operator|&&
operator|!
name|ac
argument_list|)
expr_stmt|;
name|SET_SENSITIVE
argument_list|(
literal|"layers-resize-to-image"
argument_list|,
name|layer
operator|&&
operator|!
name|ac
argument_list|)
expr_stmt|;
name|SET_SENSITIVE
argument_list|(
literal|"layers-scale"
argument_list|,
name|layer
operator|&&
operator|!
name|ac
argument_list|)
expr_stmt|;
name|SET_SENSITIVE
argument_list|(
literal|"layers-mask-add"
argument_list|,
name|layer
operator|&&
operator|!
name|fs
operator|&&
operator|!
name|ac
operator|&&
operator|!
name|lm
operator|&&
name|alpha
argument_list|)
expr_stmt|;
name|SET_SENSITIVE
argument_list|(
literal|"layers-mask-apply"
argument_list|,
name|layer
operator|&&
operator|!
name|fs
operator|&&
operator|!
name|ac
operator|&&
name|lm
argument_list|)
expr_stmt|;
name|SET_SENSITIVE
argument_list|(
literal|"layers-mask-delete"
argument_list|,
name|layer
operator|&&
operator|!
name|fs
operator|&&
operator|!
name|ac
operator|&&
name|lm
argument_list|)
expr_stmt|;
name|SET_SENSITIVE
argument_list|(
literal|"layers-alpha-add"
argument_list|,
name|layer
operator|&&
operator|!
name|fs
operator|&&
operator|!
name|alpha
argument_list|)
expr_stmt|;
name|SET_SENSITIVE
argument_list|(
literal|"layers-mask-selection-replace"
argument_list|,
name|layer
operator|&&
operator|!
name|fs
operator|&&
operator|!
name|ac
operator|&&
name|lm
argument_list|)
expr_stmt|;
name|SET_SENSITIVE
argument_list|(
literal|"layers-mask-selection-add"
argument_list|,
name|layer
operator|&&
operator|!
name|fs
operator|&&
operator|!
name|ac
operator|&&
name|lm
argument_list|)
expr_stmt|;
name|SET_SENSITIVE
argument_list|(
literal|"layers-mask-selection-subtract"
argument_list|,
name|layer
operator|&&
operator|!
name|fs
operator|&&
operator|!
name|ac
operator|&&
name|lm
argument_list|)
expr_stmt|;
name|SET_SENSITIVE
argument_list|(
literal|"layers-mask-selection-intersect"
argument_list|,
name|layer
operator|&&
operator|!
name|fs
operator|&&
operator|!
name|ac
operator|&&
name|lm
argument_list|)
expr_stmt|;
name|SET_SENSITIVE
argument_list|(
literal|"layers-alpha-selection-replace"
argument_list|,
name|layer
operator|&&
operator|!
name|fs
operator|&&
operator|!
name|ac
argument_list|)
expr_stmt|;
name|SET_SENSITIVE
argument_list|(
literal|"layers-alpha-selection-add"
argument_list|,
name|layer
operator|&&
operator|!
name|fs
operator|&&
operator|!
name|ac
argument_list|)
expr_stmt|;
name|SET_SENSITIVE
argument_list|(
literal|"layers-alpha-selection-subtract"
argument_list|,
name|layer
operator|&&
operator|!
name|fs
operator|&&
operator|!
name|ac
argument_list|)
expr_stmt|;
name|SET_SENSITIVE
argument_list|(
literal|"layers-alpha-selection-intersect"
argument_list|,
name|layer
operator|&&
operator|!
name|fs
operator|&&
operator|!
name|ac
argument_list|)
expr_stmt|;
undef|#
directive|undef
name|SET_VISIBLE
undef|#
directive|undef
name|SET_SENSITIVE
block|}
end_function

end_unit

