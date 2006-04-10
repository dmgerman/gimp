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
file|"core/gimplayermask.h"
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
file|"actions.h"
end_include

begin_include
include|#
directive|include
file|"image-commands.h"
end_include

begin_include
include|#
directive|include
file|"layers-actions.h"
end_include

begin_include
include|#
directive|include
file|"layers-commands.h"
end_include

begin_include
include|#
directive|include
file|"gimp-intl.h"
end_include

begin_decl_stmt
DECL|variable|layers_actions
specifier|static
specifier|const
name|GimpActionEntry
name|layers_actions
index|[]
init|=
block|{
block|{
literal|"layers-popup"
block|,
name|GIMP_STOCK_LAYERS
block|,
name|N_
argument_list|(
literal|"Layers Menu"
argument_list|)
block|,
name|NULL
block|,
name|NULL
block|,
name|NULL
block|,
name|GIMP_HELP_LAYER_DIALOG
block|}
block|,
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
literal|"layers-properties-menu"
block|,
name|GTK_STOCK_PROPERTIES
block|,
name|N_
argument_list|(
literal|"_Properties"
argument_list|)
block|}
block|,
block|{
literal|"layers-opacity-menu"
block|,
name|GIMP_STOCK_TRANSPARENCY
block|,
name|N_
argument_list|(
literal|"_Opacity"
argument_list|)
block|}
block|,
block|{
literal|"layers-mode-menu"
block|,
name|GIMP_STOCK_TOOL_PENCIL
block|,
name|N_
argument_list|(
literal|"Layer _Mode"
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
name|N_
argument_list|(
literal|"Activate the text tool on this text layer"
argument_list|)
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
name|GTK_STOCK_EDIT
block|,
name|N_
argument_list|(
literal|"_Edit Layer Attributes..."
argument_list|)
block|,
name|NULL
block|,
name|N_
argument_list|(
literal|"Edit the layer's name"
argument_list|)
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
literal|"<control><shift>N"
block|,
name|N_
argument_list|(
literal|"Create a new layer and add it to the image"
argument_list|)
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
literal|"layers-new-last-values"
block|,
name|GTK_STOCK_NEW
block|,
name|N_
argument_list|(
literal|"_New Layer"
argument_list|)
block|,
literal|""
block|,
name|N_
argument_list|(
literal|"Create a new layer with last used values"
argument_list|)
block|,
name|G_CALLBACK
argument_list|(
name|layers_new_last_vals_cmd_callback
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
literal|"<control><shift>D"
block|,
name|N_
argument_list|(
literal|"Create a duplicate of the layer and add it to the image"
argument_list|)
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
name|N_
argument_list|(
literal|"Delete this layer"
argument_list|)
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
name|N_
argument_list|(
literal|"Raise this layer one step in the layer stack"
argument_list|)
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
name|N_
argument_list|(
literal|"Move this layer to the top of the layer stack"
argument_list|)
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
name|N_
argument_list|(
literal|"Lower this layer one step in the layer stack"
argument_list|)
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
name|N_
argument_list|(
literal|"Move this layer to the bottom of the layer stack"
argument_list|)
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
literal|"<control>H"
block|,
name|N_
argument_list|(
literal|"Anchor the floating layer"
argument_list|)
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
name|N_
argument_list|(
literal|"Merge this layer with the one below it"
argument_list|)
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
name|N_
argument_list|(
literal|"Merge all visible layers into one layer"
argument_list|)
block|,
name|G_CALLBACK
argument_list|(
name|image_merge_layers_cmd_callback
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
name|N_
argument_list|(
literal|"Merge all layers into one and remove transparency"
argument_list|)
block|,
name|G_CALLBACK
argument_list|(
name|image_flatten_image_cmd_callback
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
name|N_
argument_list|(
literal|"Turn this text layer into a normal layer"
argument_list|)
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
name|N_
argument_list|(
literal|"Adjust the layer dimensions"
argument_list|)
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
name|N_
argument_list|(
literal|"Resize the layer to the size of the image"
argument_list|)
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
name|N_
argument_list|(
literal|"Change the size of the layer content"
argument_list|)
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
literal|"layers-crop"
block|,
name|GIMP_STOCK_TOOL_CROP
block|,
name|N_
argument_list|(
literal|"Cr_op Layer"
argument_list|)
block|,
name|NULL
block|,
name|N_
argument_list|(
literal|"Crop the layer to the extents of the selection"
argument_list|)
block|,
name|G_CALLBACK
argument_list|(
name|layers_crop_cmd_callback
argument_list|)
block|,
name|GIMP_HELP_LAYER_CROP
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
name|N_
argument_list|(
literal|"Add a mask that allows non-destructive editing of transparency"
argument_list|)
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
name|N_
argument_list|(
literal|"Add transparency information to the layer"
argument_list|)
block|,
name|G_CALLBACK
argument_list|(
name|layers_alpha_add_cmd_callback
argument_list|)
block|,
name|GIMP_HELP_LAYER_ALPHA_ADD
block|}
block|,
block|{
literal|"layers-alpha-remove"
block|,
name|NULL
block|,
name|N_
argument_list|(
literal|"_Remove Alpha Channel"
argument_list|)
block|,
name|NULL
block|,
name|N_
argument_list|(
literal|"Remove transparency information from the layer"
argument_list|)
block|,
name|G_CALLBACK
argument_list|(
name|layers_alpha_remove_cmd_callback
argument_list|)
block|,
name|GIMP_HELP_LAYER_ALPHA_REMOVE
block|}
block|}
decl_stmt|;
end_decl_stmt

begin_decl_stmt
DECL|variable|layers_toggle_actions
specifier|static
specifier|const
name|GimpToggleActionEntry
name|layers_toggle_actions
index|[]
init|=
block|{
block|{
literal|"layers-lock-alpha"
block|,
name|GIMP_STOCK_TRANSPARENCY
block|,
name|N_
argument_list|(
literal|"Lock Alph_a Channel"
argument_list|)
block|,
name|NULL
block|,
name|N_
argument_list|(
literal|"Keep transparency information on this layer from being modified"
argument_list|)
block|,
name|G_CALLBACK
argument_list|(
name|layers_lock_alpha_cmd_callback
argument_list|)
block|,
name|FALSE
block|,
name|GIMP_HELP_LAYER_LOCK_ALPHA
block|}
block|,
block|{
literal|"layers-mask-edit"
block|,
name|GTK_STOCK_EDIT
block|,
name|N_
argument_list|(
literal|"_Edit Layer Mask"
argument_list|)
block|,
name|NULL
block|,
name|N_
argument_list|(
literal|"Work on the layer mask"
argument_list|)
block|,
name|G_CALLBACK
argument_list|(
name|layers_mask_edit_cmd_callback
argument_list|)
block|,
name|FALSE
block|,
name|GIMP_HELP_LAYER_MASK_EDIT
block|}
block|,
block|{
literal|"layers-mask-show"
block|,
name|GIMP_STOCK_VISIBLE
block|,
name|N_
argument_list|(
literal|"S_how Layer Mask"
argument_list|)
block|,
name|NULL
block|,
name|NULL
block|,
name|G_CALLBACK
argument_list|(
name|layers_mask_show_cmd_callback
argument_list|)
block|,
name|FALSE
block|,
name|GIMP_HELP_LAYER_MASK_SHOW
block|}
block|,
block|{
literal|"layers-mask-disable"
block|,
name|NULL
block|,
name|N_
argument_list|(
literal|"_Disable Layer Mask"
argument_list|)
block|,
name|NULL
block|,
name|N_
argument_list|(
literal|"Dismiss the effect of the layer mask"
argument_list|)
block|,
name|G_CALLBACK
argument_list|(
name|layers_mask_disable_cmd_callback
argument_list|)
block|,
name|FALSE
block|,
name|GIMP_HELP_LAYER_MASK_DISABLE
block|}
block|}
decl_stmt|;
end_decl_stmt

begin_decl_stmt
DECL|variable|layers_mask_apply_actions
specifier|static
specifier|const
name|GimpEnumActionEntry
name|layers_mask_apply_actions
index|[]
init|=
block|{
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
name|N_
argument_list|(
literal|"Apply the effect of the layer mask and remove it"
argument_list|)
block|,
name|GIMP_MASK_APPLY
block|,
name|FALSE
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
name|N_
argument_list|(
literal|"Remove the layer mask and its effect"
argument_list|)
block|,
name|GIMP_MASK_DISCARD
block|,
name|FALSE
block|,
name|GIMP_HELP_LAYER_MASK_DELETE
block|}
block|}
decl_stmt|;
end_decl_stmt

begin_decl_stmt
DECL|variable|layers_mask_to_selection_actions
specifier|static
specifier|const
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
name|N_
argument_list|(
literal|"Replace the selection with the layer mask"
argument_list|)
block|,
name|GIMP_CHANNEL_OP_REPLACE
block|,
name|FALSE
block|,
name|GIMP_HELP_LAYER_MASK_SELECTION_REPLACE
block|}
block|,
block|{
literal|"layers-mask-selection-add"
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
name|N_
argument_list|(
literal|"Add the layer mask to the current selection"
argument_list|)
block|,
name|GIMP_CHANNEL_OP_ADD
block|,
name|FALSE
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
name|N_
argument_list|(
literal|"Subtract the layer mask from the current selection"
argument_list|)
block|,
name|GIMP_CHANNEL_OP_SUBTRACT
block|,
name|FALSE
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
name|N_
argument_list|(
literal|"Intersect the layer mask with the current selection"
argument_list|)
block|,
name|GIMP_CHANNEL_OP_INTERSECT
block|,
name|FALSE
block|,
name|GIMP_HELP_LAYER_MASK_SELECTION_INTERSECT
block|}
block|}
decl_stmt|;
end_decl_stmt

begin_decl_stmt
DECL|variable|layers_alpha_to_selection_actions
specifier|static
specifier|const
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
name|N_
argument_list|(
literal|"Replace the selection with the layer's alpha channel"
argument_list|)
block|,
name|GIMP_CHANNEL_OP_REPLACE
block|,
name|FALSE
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
name|N_
argument_list|(
literal|"Add the layer's alpha channel to the current selection"
argument_list|)
block|,
name|GIMP_CHANNEL_OP_ADD
block|,
name|FALSE
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
name|N_
argument_list|(
literal|"Subtract the layer's alpha channel from the current selection"
argument_list|)
block|,
name|GIMP_CHANNEL_OP_SUBTRACT
block|,
name|FALSE
block|,
name|GIMP_HELP_LAYER_ALPHA_SELECTION_SUBTRACT
block|}
block|,
block|{
literal|"layers-alpha-selection-intersect"
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
name|N_
argument_list|(
literal|"Intersect the layer's alpha channel with the current selection"
argument_list|)
block|,
name|GIMP_CHANNEL_OP_INTERSECT
block|,
name|FALSE
block|,
name|GIMP_HELP_LAYER_ALPHA_SELECTION_INTERSECT
block|}
block|}
decl_stmt|;
end_decl_stmt

begin_decl_stmt
DECL|variable|layers_select_actions
specifier|static
specifier|const
name|GimpEnumActionEntry
name|layers_select_actions
index|[]
init|=
block|{
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
name|GIMP_ACTION_SELECT_FIRST
block|,
name|FALSE
block|,
name|GIMP_HELP_LAYER_TOP
block|}
block|,
block|{
literal|"layers-select-bottom"
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
name|GIMP_ACTION_SELECT_LAST
block|,
name|FALSE
block|,
name|GIMP_HELP_LAYER_BOTTOM
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
name|GIMP_ACTION_SELECT_PREVIOUS
block|,
name|FALSE
block|,
name|GIMP_HELP_LAYER_PREVIOUS
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
name|GIMP_ACTION_SELECT_NEXT
block|,
name|FALSE
block|,
name|GIMP_HELP_LAYER_NEXT
block|}
block|}
decl_stmt|;
end_decl_stmt

begin_decl_stmt
DECL|variable|layers_opacity_actions
specifier|static
specifier|const
name|GimpEnumActionEntry
name|layers_opacity_actions
index|[]
init|=
block|{
block|{
literal|"layers-opacity-set"
block|,
name|GIMP_STOCK_TRANSPARENCY
block|,
name|N_
argument_list|(
literal|"Set Opacity"
argument_list|)
block|,
name|NULL
block|,
name|NULL
block|,
name|GIMP_ACTION_SELECT_SET
block|,
name|TRUE
block|,
name|GIMP_HELP_LAYER_OPACITY
block|}
block|,
block|{
literal|"layers-opacity-transparent"
block|,
name|GIMP_STOCK_TRANSPARENCY
block|,
literal|"Completely Transparent"
block|,
name|NULL
block|,
name|NULL
block|,
name|GIMP_ACTION_SELECT_FIRST
block|,
name|FALSE
block|,
name|GIMP_HELP_LAYER_OPACITY
block|}
block|,
block|{
literal|"layers-opacity-opaque"
block|,
name|GIMP_STOCK_TRANSPARENCY
block|,
literal|"Completely Opaque"
block|,
name|NULL
block|,
name|NULL
block|,
name|GIMP_ACTION_SELECT_LAST
block|,
name|FALSE
block|,
name|GIMP_HELP_LAYER_OPACITY
block|}
block|,
block|{
literal|"layers-opacity-decrease"
block|,
name|GIMP_STOCK_TRANSPARENCY
block|,
literal|"More Transparent"
block|,
name|NULL
block|,
name|NULL
block|,
name|GIMP_ACTION_SELECT_PREVIOUS
block|,
name|FALSE
block|,
name|GIMP_HELP_LAYER_OPACITY
block|}
block|,
block|{
literal|"layers-opacity-increase"
block|,
name|GIMP_STOCK_TRANSPARENCY
block|,
literal|"More Opaque"
block|,
name|NULL
block|,
name|NULL
block|,
name|GIMP_ACTION_SELECT_NEXT
block|,
name|FALSE
block|,
name|GIMP_HELP_LAYER_OPACITY
block|}
block|,
block|{
literal|"layers-opacity-decrease-skip"
block|,
name|GIMP_STOCK_TRANSPARENCY
block|,
literal|"10% More Transparent"
block|,
name|NULL
block|,
name|NULL
block|,
name|GIMP_ACTION_SELECT_SKIP_PREVIOUS
block|,
name|FALSE
block|,
name|GIMP_HELP_LAYER_OPACITY
block|}
block|,
block|{
literal|"layers-opacity-increase-skip"
block|,
name|GIMP_STOCK_TRANSPARENCY
block|,
literal|"10% More Opaque"
block|,
name|NULL
block|,
name|NULL
block|,
name|GIMP_ACTION_SELECT_SKIP_NEXT
block|,
name|FALSE
block|,
name|GIMP_HELP_LAYER_OPACITY
block|}
block|}
decl_stmt|;
end_decl_stmt

begin_decl_stmt
DECL|variable|layers_mode_actions
specifier|static
specifier|const
name|GimpEnumActionEntry
name|layers_mode_actions
index|[]
init|=
block|{
block|{
literal|"layers-mode-first"
block|,
name|GIMP_STOCK_TOOL_PENCIL
block|,
literal|"First Layer Mode"
block|,
name|NULL
block|,
name|NULL
block|,
name|GIMP_ACTION_SELECT_FIRST
block|,
name|FALSE
block|,
name|GIMP_HELP_LAYER_MODE
block|}
block|,
block|{
literal|"layers-mode-last"
block|,
name|GIMP_STOCK_TOOL_PENCIL
block|,
literal|"Last Layer Mode"
block|,
name|NULL
block|,
name|NULL
block|,
name|GIMP_ACTION_SELECT_LAST
block|,
name|FALSE
block|,
name|GIMP_HELP_LAYER_MODE
block|}
block|,
block|{
literal|"layers-mode-previous"
block|,
name|GIMP_STOCK_TOOL_PENCIL
block|,
literal|"Previous Layer Mode"
block|,
name|NULL
block|,
name|NULL
block|,
name|GIMP_ACTION_SELECT_PREVIOUS
block|,
name|FALSE
block|,
name|GIMP_HELP_LAYER_MODE
block|}
block|,
block|{
literal|"layers-mode-next"
block|,
name|GIMP_STOCK_TOOL_PENCIL
block|,
literal|"Next Layer Mode"
block|,
name|NULL
block|,
name|NULL
block|,
name|GIMP_ACTION_SELECT_NEXT
block|,
name|FALSE
block|,
name|GIMP_HELP_LAYER_MODE
block|}
block|}
decl_stmt|;
end_decl_stmt

begin_function
name|void
DECL|function|layers_actions_setup (GimpActionGroup * group)
name|layers_actions_setup
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
name|layers_actions
argument_list|,
name|G_N_ELEMENTS
argument_list|(
name|layers_actions
argument_list|)
argument_list|)
expr_stmt|;
name|gimp_action_group_add_toggle_actions
argument_list|(
name|group
argument_list|,
name|layers_toggle_actions
argument_list|,
name|G_N_ELEMENTS
argument_list|(
name|layers_toggle_actions
argument_list|)
argument_list|)
expr_stmt|;
name|gimp_action_group_add_enum_actions
argument_list|(
name|group
argument_list|,
name|layers_mask_apply_actions
argument_list|,
name|G_N_ELEMENTS
argument_list|(
name|layers_mask_apply_actions
argument_list|)
argument_list|,
name|G_CALLBACK
argument_list|(
name|layers_mask_apply_cmd_callback
argument_list|)
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
argument_list|)
expr_stmt|;
name|gimp_action_group_add_enum_actions
argument_list|(
name|group
argument_list|,
name|layers_select_actions
argument_list|,
name|G_N_ELEMENTS
argument_list|(
name|layers_select_actions
argument_list|)
argument_list|,
name|G_CALLBACK
argument_list|(
name|layers_select_cmd_callback
argument_list|)
argument_list|)
expr_stmt|;
name|gimp_action_group_add_enum_actions
argument_list|(
name|group
argument_list|,
name|layers_opacity_actions
argument_list|,
name|G_N_ELEMENTS
argument_list|(
name|layers_opacity_actions
argument_list|)
argument_list|,
name|G_CALLBACK
argument_list|(
name|layers_opacity_cmd_callback
argument_list|)
argument_list|)
expr_stmt|;
name|gimp_action_group_add_enum_actions
argument_list|(
name|group
argument_list|,
name|layers_mode_actions
argument_list|,
name|G_N_ELEMENTS
argument_list|(
name|layers_mode_actions
argument_list|)
argument_list|,
name|G_CALLBACK
argument_list|(
name|layers_mode_cmd_callback
argument_list|)
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
name|image
init|=
name|action_data_get_image
argument_list|(
name|data
argument_list|)
decl_stmt|;
name|GimpLayer
modifier|*
name|layer
init|=
name|NULL
decl_stmt|;
name|GimpLayerMask
modifier|*
name|mask
init|=
name|NULL
decl_stmt|;
comment|/*  layer mask             */
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
name|sel
init|=
name|FALSE
decl_stmt|;
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
name|lock_alpha
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
name|image
condition|)
block|{
name|fs
operator|=
operator|(
name|gimp_image_floating_sel
argument_list|(
name|image
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
name|image
argument_list|)
operator|!=
name|NULL
operator|)
expr_stmt|;
name|sel
operator|=
operator|!
name|gimp_channel_is_empty
argument_list|(
name|gimp_image_get_mask
argument_list|(
name|image
argument_list|)
argument_list|)
expr_stmt|;
name|indexed
operator|=
operator|(
name|gimp_image_base_type
argument_list|(
name|image
argument_list|)
operator|==
name|GIMP_INDEXED
operator|)
expr_stmt|;
name|layer
operator|=
name|gimp_image_get_active_layer
argument_list|(
name|image
argument_list|)
expr_stmt|;
if|if
condition|(
name|layer
condition|)
block|{
name|GList
modifier|*
name|list
decl_stmt|;
name|mask
operator|=
name|gimp_layer_get_mask
argument_list|(
name|layer
argument_list|)
expr_stmt|;
name|lock_alpha
operator|=
name|gimp_layer_get_lock_alpha
argument_list|(
name|layer
argument_list|)
expr_stmt|;
name|alpha
operator|=
name|gimp_drawable_has_alpha
argument_list|(
name|GIMP_DRAWABLE
argument_list|(
name|layer
argument_list|)
argument_list|)
expr_stmt|;
name|list
operator|=
name|g_list_find
argument_list|(
name|GIMP_LIST
argument_list|(
name|image
operator|->
name|layers
argument_list|)
operator|->
name|list
argument_list|,
name|layer
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
if|if
condition|(
name|layer
condition|)
name|text_layer
operator|=
name|gimp_drawable_is_text_layer
argument_list|(
name|GIMP_DRAWABLE
argument_list|(
name|layer
argument_list|)
argument_list|)
expr_stmt|;
block|}
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
name|image
argument_list|)
expr_stmt|;
name|SET_SENSITIVE
argument_list|(
literal|"layers-new-last-values"
argument_list|,
name|image
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
literal|"layers-crop"
argument_list|,
name|layer
operator|&&
name|sel
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
literal|"layers-alpha-remove"
argument_list|,
name|layer
operator|&&
operator|!
name|fs
operator|&&
name|alpha
argument_list|)
expr_stmt|;
name|SET_SENSITIVE
argument_list|(
literal|"layers-lock-alpha"
argument_list|,
name|layer
argument_list|)
expr_stmt|;
name|SET_ACTIVE
argument_list|(
literal|"layers-lock-alpha"
argument_list|,
name|lock_alpha
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
name|mask
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
name|mask
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
name|mask
argument_list|)
expr_stmt|;
name|SET_SENSITIVE
argument_list|(
literal|"layers-mask-edit"
argument_list|,
name|layer
operator|&&
operator|!
name|fs
operator|&&
operator|!
name|ac
operator|&&
name|mask
argument_list|)
expr_stmt|;
name|SET_SENSITIVE
argument_list|(
literal|"layers-mask-show"
argument_list|,
name|layer
operator|&&
operator|!
name|fs
operator|&&
operator|!
name|ac
operator|&&
name|mask
argument_list|)
expr_stmt|;
name|SET_SENSITIVE
argument_list|(
literal|"layers-mask-disable"
argument_list|,
name|layer
operator|&&
operator|!
name|fs
operator|&&
operator|!
name|ac
operator|&&
name|mask
argument_list|)
expr_stmt|;
name|SET_ACTIVE
argument_list|(
literal|"layers-mask-edit"
argument_list|,
name|mask
operator|&&
name|gimp_layer_mask_get_edit
argument_list|(
name|mask
argument_list|)
argument_list|)
expr_stmt|;
name|SET_ACTIVE
argument_list|(
literal|"layers-mask-show"
argument_list|,
name|mask
operator|&&
name|gimp_layer_mask_get_show
argument_list|(
name|mask
argument_list|)
argument_list|)
expr_stmt|;
name|SET_ACTIVE
argument_list|(
literal|"layers-mask-disable"
argument_list|,
name|mask
operator|&&
operator|!
name|gimp_layer_mask_get_apply
argument_list|(
name|mask
argument_list|)
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
name|mask
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
name|mask
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
name|mask
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
name|mask
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
undef|#
directive|undef
name|SET_ACTIVE
block|}
end_function

end_unit

