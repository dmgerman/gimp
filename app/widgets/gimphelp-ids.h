begin_unit|revision:0.9.5;language:C;cregit-version:0.0.1
begin_comment
comment|/* The GIMP -- an image manipulation program  * Copyright (C) 1995 Spencer Kimball and Peter Mattis  *  * gimphelp-ids.h  * Copyright (C) 2003 Michael Natterer<mitch@gimp.org>  *  * This program is free software; you can redistribute it and/or modify  * it under the terms of the GNU General Public License as published by  * the Free Software Foundation; either version 2 of the License, or  * (at your option) any later version.  *  * This program is distributed in the hope that it will be useful,  * but WITHOUT ANY WARRANTY; without even the implied warranty of  * MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the  * GNU General Public License for more details.  *  * You should have received a copy of the GNU General Public License  * along with this program; if not, write to the Free Software  * Foundation, Inc., 59 Temple Place - Suite 330, Boston, MA 02111-1307, USA.  */
end_comment

begin_ifndef
ifndef|#
directive|ifndef
name|__GIMP_HELP_IDS_H__
end_ifndef

begin_define
DECL|macro|__GIMP_HELP_IDS_H__
define|#
directive|define
name|__GIMP_HELP_IDS_H__
end_define

begin_define
DECL|macro|GIMP_HELP_FILE_NEW
define|#
directive|define
name|GIMP_HELP_FILE_NEW
value|"file/dialogs/file_new.html"
end_define

begin_define
DECL|macro|GIMP_HELP_FILE_NEW_CONFIRM
define|#
directive|define
name|GIMP_HELP_FILE_NEW_CONFIRM
value|"file/dialogs/file_new.html#confirm_dialog"
end_define

begin_define
DECL|macro|GIMP_HELP_FILE_OPEN
define|#
directive|define
name|GIMP_HELP_FILE_OPEN
value|"file/dialogs/file_open.html"
end_define

begin_define
DECL|macro|GIMP_HELP_FILE_SAVE
define|#
directive|define
name|GIMP_HELP_FILE_SAVE
value|"file/dialogs/file_save.html"
end_define

begin_define
DECL|macro|GIMP_HELP_FILE_SAVE_AS
define|#
directive|define
name|GIMP_HELP_FILE_SAVE_AS
value|"file/dialogs/file_save.html"
end_define

begin_define
DECL|macro|GIMP_HELP_FILE_SAVE_A_COPY
define|#
directive|define
name|GIMP_HELP_FILE_SAVE_A_COPY
value|"file/dialogs/file_save.html"
end_define

begin_define
DECL|macro|GIMP_HELP_FILE_SAVE_AS_TEMPLATE
define|#
directive|define
name|GIMP_HELP_FILE_SAVE_AS_TEMPLATE
value|"file/dialogs/file_save.html"
end_define

begin_define
DECL|macro|GIMP_HELP_FILE_SAVE_OVERWRITE
define|#
directive|define
name|GIMP_HELP_FILE_SAVE_OVERWRITE
value|"file/dialogs/file_exists.html"
end_define

begin_define
DECL|macro|GIMP_HELP_FILE_REVERT
define|#
directive|define
name|GIMP_HELP_FILE_REVERT
value|"file/revert.html"
end_define

begin_define
DECL|macro|GIMP_HELP_FILE_CLOSE
define|#
directive|define
name|GIMP_HELP_FILE_CLOSE
value|"file/close.html"
end_define

begin_define
DECL|macro|GIMP_HELP_FILE_QUIT
define|#
directive|define
name|GIMP_HELP_FILE_QUIT
value|"file/quit.html"
end_define

begin_define
DECL|macro|GIMP_HELP_EDIT_UNDO
define|#
directive|define
name|GIMP_HELP_EDIT_UNDO
value|"edit/undo.html"
end_define

begin_define
DECL|macro|GIMP_HELP_EDIT_REDO
define|#
directive|define
name|GIMP_HELP_EDIT_REDO
value|"edit/redo.html"
end_define

begin_define
DECL|macro|GIMP_HELP_EDIT_CUT
define|#
directive|define
name|GIMP_HELP_EDIT_CUT
value|"edit/cut.html"
end_define

begin_define
DECL|macro|GIMP_HELP_EDIT_COPY
define|#
directive|define
name|GIMP_HELP_EDIT_COPY
value|"edit/copy.html"
end_define

begin_define
DECL|macro|GIMP_HELP_EDIT_PASTE
define|#
directive|define
name|GIMP_HELP_EDIT_PASTE
value|"edit/paste.html"
end_define

begin_define
DECL|macro|GIMP_HELP_EDIT_PASTE_INTO
define|#
directive|define
name|GIMP_HELP_EDIT_PASTE_INTO
value|"edit/paste_into.html"
end_define

begin_define
DECL|macro|GIMP_HELP_EDIT_PASTE_AS_NEW
define|#
directive|define
name|GIMP_HELP_EDIT_PASTE_AS_NEW
value|"edit/paste_as_new.html"
end_define

begin_define
DECL|macro|GIMP_HELP_EDIT_CLEAR
define|#
directive|define
name|GIMP_HELP_EDIT_CLEAR
value|"edit/clear.html"
end_define

begin_define
DECL|macro|GIMP_HELP_EDIT_FILL_FG
define|#
directive|define
name|GIMP_HELP_EDIT_FILL_FG
value|"edit/fill.html"
end_define

begin_define
DECL|macro|GIMP_HELP_EDIT_FILL_BG
define|#
directive|define
name|GIMP_HELP_EDIT_FILL_BG
value|"edit/fill.html"
end_define

begin_define
DECL|macro|GIMP_HELP_EDIT_FILL_PATTERN
define|#
directive|define
name|GIMP_HELP_EDIT_FILL_PATTERN
value|"edit/fill.html"
end_define

begin_define
DECL|macro|GIMP_HELP_EDIT_STROKE_SELECTION
define|#
directive|define
name|GIMP_HELP_EDIT_STROKE_SELECTION
value|"edit/stroke.html"
end_define

begin_define
DECL|macro|GIMP_HELP_EDIT_STROKE_PATH
define|#
directive|define
name|GIMP_HELP_EDIT_STROKE_PATH
value|"edit/stroke.html"
end_define

begin_define
DECL|macro|GIMP_HELP_SELECT_DIALOG
define|#
directive|define
name|GIMP_HELP_SELECT_DIALOG
value|"dialogs/selection_editor.html"
end_define

begin_define
DECL|macro|GIMP_HELP_SELECT_ALL
define|#
directive|define
name|GIMP_HELP_SELECT_ALL
value|"select/all.html"
end_define

begin_define
DECL|macro|GIMP_HELP_SELECT_NONE
define|#
directive|define
name|GIMP_HELP_SELECT_NONE
value|"select/none.html"
end_define

begin_define
DECL|macro|GIMP_HELP_SELECT_INVERT
define|#
directive|define
name|GIMP_HELP_SELECT_INVERT
value|"select/invert.html"
end_define

begin_define
DECL|macro|GIMP_HELP_SELECT_FLOAT
define|#
directive|define
name|GIMP_HELP_SELECT_FLOAT
value|"select/float.html"
end_define

begin_define
DECL|macro|GIMP_HELP_SELECT_FEATHER
define|#
directive|define
name|GIMP_HELP_SELECT_FEATHER
value|"select/dialogs/feather_selection.html"
end_define

begin_define
DECL|macro|GIMP_HELP_SELECT_SHARPEN
define|#
directive|define
name|GIMP_HELP_SELECT_SHARPEN
value|"select/sharpen.html"
end_define

begin_define
DECL|macro|GIMP_HELP_SELECT_SHRINK
define|#
directive|define
name|GIMP_HELP_SELECT_SHRINK
value|"select/dialogs/shrink_selection.html"
end_define

begin_define
DECL|macro|GIMP_HELP_SELECT_GROW
define|#
directive|define
name|GIMP_HELP_SELECT_GROW
value|"select/dialogs/grow_selection.html"
end_define

begin_define
DECL|macro|GIMP_HELP_SELECT_BORDER
define|#
directive|define
name|GIMP_HELP_SELECT_BORDER
value|"select/dialogs/border_selection.html"
end_define

begin_define
DECL|macro|GIMP_HELP_SELECT_QUICKMASK
define|#
directive|define
name|GIMP_HELP_SELECT_QUICKMASK
value|"select/quickmask.html"
end_define

begin_define
DECL|macro|GIMP_HELP_SELECT_SAVE_TO_CHANNEL
define|#
directive|define
name|GIMP_HELP_SELECT_SAVE_TO_CHANNEL
value|"select/save_to_channel.html"
end_define

begin_define
DECL|macro|GIMP_HELP_VIEW_NEW
define|#
directive|define
name|GIMP_HELP_VIEW_NEW
value|"view/new.html"
end_define

begin_define
DECL|macro|GIMP_HELP_VIEW_DOT_FOR_DOT
define|#
directive|define
name|GIMP_HELP_VIEW_DOT_FOR_DOT
value|"view/dot_for_dot.html"
end_define

begin_define
DECL|macro|GIMP_HELP_VIEW_ZOOM
define|#
directive|define
name|GIMP_HELP_VIEW_ZOOM
value|"view/zoom.html"
end_define

begin_define
DECL|macro|GIMP_HELP_VIEW_ZOOM_TO_FIT
define|#
directive|define
name|GIMP_HELP_VIEW_ZOOM_TO_FIT
value|"view/zoom.html"
end_define

begin_define
DECL|macro|GIMP_HELP_VIEW_SHOW_SELECTION
define|#
directive|define
name|GIMP_HELP_VIEW_SHOW_SELECTION
value|"view/toggle_selection.html"
end_define

begin_define
DECL|macro|GIMP_HELP_VIEW_SHOW_LAYER_BOUNDARY
define|#
directive|define
name|GIMP_HELP_VIEW_SHOW_LAYER_BOUNDARY
value|"view/toggle_selection.html"
end_define

begin_define
DECL|macro|GIMP_HELP_VIEW_SHOW_GUIDES
define|#
directive|define
name|GIMP_HELP_VIEW_SHOW_GUIDES
value|"view/toggle_guides.html"
end_define

begin_define
DECL|macro|GIMP_HELP_VIEW_SNAP_TO_GUIDES
define|#
directive|define
name|GIMP_HELP_VIEW_SNAP_TO_GUIDES
value|"view/gnap_to_guides.html"
end_define

begin_define
DECL|macro|GIMP_HELP_VIEW_SHOW_GRID
define|#
directive|define
name|GIMP_HELP_VIEW_SHOW_GRID
value|"view/toggle_grid.html"
end_define

begin_define
DECL|macro|GIMP_HELP_VIEW_SNAP_TO_GRID
define|#
directive|define
name|GIMP_HELP_VIEW_SNAP_TO_GRID
value|"view/snap_to_grid.html"
end_define

begin_define
DECL|macro|GIMP_HELP_VIEW_SHOW_MENUBAR
define|#
directive|define
name|GIMP_HELP_VIEW_SHOW_MENUBAR
value|"view/toggle_menubar.html"
end_define

begin_define
DECL|macro|GIMP_HELP_VIEW_SHOW_RULERS
define|#
directive|define
name|GIMP_HELP_VIEW_SHOW_RULERS
value|"view/toggle_rulers.html"
end_define

begin_define
DECL|macro|GIMP_HELP_VIEW_SHOW_SCROLLBARS
define|#
directive|define
name|GIMP_HELP_VIEW_SHOW_SCROLLBARS
value|"view/toggle_scrollbars.html"
end_define

begin_define
DECL|macro|GIMP_HELP_VIEW_SHOW_STATUSBAR
define|#
directive|define
name|GIMP_HELP_VIEW_SHOW_STATUSBAR
value|"view/toggle_statusbar.html"
end_define

begin_define
DECL|macro|GIMP_HELP_VIEW_SHRINK_WRAP
define|#
directive|define
name|GIMP_HELP_VIEW_SHRINK_WRAP
value|"view/shrink_wrap.html"
end_define

begin_define
DECL|macro|GIMP_HELP_VIEW_FULLSCREEN
define|#
directive|define
name|GIMP_HELP_VIEW_FULLSCREEN
value|"view/fullscreen.html"
end_define

begin_define
DECL|macro|GIMP_HELP_IMAGE_DIALOG
define|#
directive|define
name|GIMP_HELP_IMAGE_DIALOG
value|"dialogs/image_dialog.html"
end_define

begin_define
DECL|macro|GIMP_HELP_IMAGE_CONVERT_RGB
define|#
directive|define
name|GIMP_HELP_IMAGE_CONVERT_RGB
value|"image/mode/convert_to_rgb.html"
end_define

begin_define
DECL|macro|GIMP_HELP_IMAGE_CONVERT_GRAYSCALE
define|#
directive|define
name|GIMP_HELP_IMAGE_CONVERT_GRAYSCALE
value|"image/mode/convert_to_grayscale.html"
end_define

begin_define
DECL|macro|GIMP_HELP_IMAGE_CONVERT_INDEXED
define|#
directive|define
name|GIMP_HELP_IMAGE_CONVERT_INDEXED
value|"image/mode/convert_to_indexed.html"
end_define

begin_define
DECL|macro|GIMP_HELP_IMAGE_FLIP_HORIZONTAL
define|#
directive|define
name|GIMP_HELP_IMAGE_FLIP_HORIZONTAL
value|"image/dialogs/flip_image.html"
end_define

begin_define
DECL|macro|GIMP_HELP_IMAGE_FLIP_VERTICAL
define|#
directive|define
name|GIMP_HELP_IMAGE_FLIP_VERTICAL
value|"image/dialogs/flip_image.html"
end_define

begin_define
DECL|macro|GIMP_HELP_IMAGE_ROTATE_90
define|#
directive|define
name|GIMP_HELP_IMAGE_ROTATE_90
value|"image/dialogs/rotate_image.html"
end_define

begin_define
DECL|macro|GIMP_HELP_IMAGE_ROTATE_180
define|#
directive|define
name|GIMP_HELP_IMAGE_ROTATE_180
value|"image/dialogs/rotate_image.html"
end_define

begin_define
DECL|macro|GIMP_HELP_IMAGE_ROTATE_270
define|#
directive|define
name|GIMP_HELP_IMAGE_ROTATE_270
value|"image/dialogs/rotate_image.html"
end_define

begin_define
DECL|macro|GIMP_HELP_IMAGE_RESIZE
define|#
directive|define
name|GIMP_HELP_IMAGE_RESIZE
value|"image/dialogs/set_canvas_size.html"
end_define

begin_define
DECL|macro|GIMP_HELP_IMAGE_SCALE
define|#
directive|define
name|GIMP_HELP_IMAGE_SCALE
value|"image/dialogs/scale_image.html"
end_define

begin_define
DECL|macro|GIMP_HELP_IMAGE_CROP
define|#
directive|define
name|GIMP_HELP_IMAGE_CROP
value|"image/dialogs/crop_image.html"
end_define

begin_define
DECL|macro|GIMP_HELP_IMAGE_DUPLICATE
define|#
directive|define
name|GIMP_HELP_IMAGE_DUPLICATE
value|"image/duplicate.html"
end_define

begin_define
DECL|macro|GIMP_HELP_IMAGE_MERGE_LAYERS
define|#
directive|define
name|GIMP_HELP_IMAGE_MERGE_LAYERS
value|"layers/dialogs/merge_visible_layers.html"
end_define

begin_define
DECL|macro|GIMP_HELP_IMAGE_FLATTEN
define|#
directive|define
name|GIMP_HELP_IMAGE_FLATTEN
value|"layers/flatten_image.html"
end_define

begin_define
DECL|macro|GIMP_HELP_IMAGE_GRID
define|#
directive|define
name|GIMP_HELP_IMAGE_GRID
value|"image/dialogs/configure_grid.html"
end_define

begin_define
DECL|macro|GIMP_HELP_LAYER_DIALOG
define|#
directive|define
name|GIMP_HELP_LAYER_DIALOG
value|"layers/dialogs/layers_dialog.html"
end_define

begin_define
DECL|macro|GIMP_HELP_LAYER_NEW
define|#
directive|define
name|GIMP_HELP_LAYER_NEW
value|"layers/dialogs/new_layer.html"
end_define

begin_define
DECL|macro|GIMP_HELP_LAYER_DUPLICATE
define|#
directive|define
name|GIMP_HELP_LAYER_DUPLICATE
value|"layers/duplicate_layer.html"
end_define

begin_define
DECL|macro|GIMP_HELP_LAYER_ANCHOR
define|#
directive|define
name|GIMP_HELP_LAYER_ANCHOR
value|"layers/anchor_layer.html"
end_define

begin_define
DECL|macro|GIMP_HELP_LAYER_MERGE_DOWN
define|#
directive|define
name|GIMP_HELP_LAYER_MERGE_DOWN
value|"layers/merge_down.html"
end_define

begin_define
DECL|macro|GIMP_HELP_LAYER_DELETE
define|#
directive|define
name|GIMP_HELP_LAYER_DELETE
value|"layers/delete_layer.html"
end_define

begin_define
DECL|macro|GIMP_HELP_LAYER_PREVIOUS
define|#
directive|define
name|GIMP_HELP_LAYER_PREVIOUS
value|"layers/stack/stack.html#previous_layer"
end_define

begin_define
DECL|macro|GIMP_HELP_LAYER_NEXT
define|#
directive|define
name|GIMP_HELP_LAYER_NEXT
value|"layers/stack/stack.html#next_layer"
end_define

begin_define
DECL|macro|GIMP_HELP_LAYER_TOP
define|#
directive|define
name|GIMP_HELP_LAYER_TOP
value|"layers/stack/stack.html#previous_layer"
end_define

begin_define
DECL|macro|GIMP_HELP_LAYER_BOTTOM
define|#
directive|define
name|GIMP_HELP_LAYER_BOTTOM
value|"layers/stack/stack.html#next_layer"
end_define

begin_define
DECL|macro|GIMP_HELP_LAYER_RAISE
define|#
directive|define
name|GIMP_HELP_LAYER_RAISE
value|"layers/stack/stack.html#raise_layer"
end_define

begin_define
DECL|macro|GIMP_HELP_LAYER_LOWER
define|#
directive|define
name|GIMP_HELP_LAYER_LOWER
value|"layers/stack/stack.html#lower_layer"
end_define

begin_define
DECL|macro|GIMP_HELP_LAYER_RAISE_TO_TOP
define|#
directive|define
name|GIMP_HELP_LAYER_RAISE_TO_TOP
value|"layers/stack/stack.html#layer_to_top"
end_define

begin_define
DECL|macro|GIMP_HELP_LAYER_LOWER_TO_BOTTOM
define|#
directive|define
name|GIMP_HELP_LAYER_LOWER_TO_BOTTOM
value|"layers/stack/stack.html#layer_to_bottom"
end_define

begin_define
DECL|macro|GIMP_HELP_LAYER_DESATURATE
define|#
directive|define
name|GIMP_HELP_LAYER_DESATURATE
value|"layers/colors/desaturate.html"
end_define

begin_define
DECL|macro|GIMP_HELP_LAYER_INVERT
define|#
directive|define
name|GIMP_HELP_LAYER_INVERT
value|"layers/colors/invert.html"
end_define

begin_define
DECL|macro|GIMP_HELP_LAYER_EQUALIZE
define|#
directive|define
name|GIMP_HELP_LAYER_EQUALIZE
value|"layers/colors/auto/equalize.html"
end_define

begin_define
DECL|macro|GIMP_HELP_LAYER_MASK_ADD
define|#
directive|define
name|GIMP_HELP_LAYER_MASK_ADD
value|"layers/dialogs/add_layer_mask.html"
end_define

begin_define
DECL|macro|GIMP_HELP_LAYER_MASK_APPLY
define|#
directive|define
name|GIMP_HELP_LAYER_MASK_APPLY
value|"layers/apply_mask.html"
end_define

begin_define
DECL|macro|GIMP_HELP_LAYER_MASK_DELETE
define|#
directive|define
name|GIMP_HELP_LAYER_MASK_DELETE
value|"layers/delete_mask.html"
end_define

begin_define
DECL|macro|GIMP_HELP_LAYER_MASK_SEL_REPLACE
define|#
directive|define
name|GIMP_HELP_LAYER_MASK_SEL_REPLACE
value|"layers/mask_to_selection.html"
end_define

begin_define
DECL|macro|GIMP_HELP_LAYER_MASK_SEL_ADD
define|#
directive|define
name|GIMP_HELP_LAYER_MASK_SEL_ADD
value|"layers/mask_to_selection.html#add"
end_define

begin_define
DECL|macro|GIMP_HELP_LAYER_MASK_SEL_SUB
define|#
directive|define
name|GIMP_HELP_LAYER_MASK_SEL_SUB
value|"layers/mask_to_selection.html#subtract"
end_define

begin_define
DECL|macro|GIMP_HELP_LAYER_MASK_SEL_INTERSECT
define|#
directive|define
name|GIMP_HELP_LAYER_MASK_SEL_INTERSECT
value|"layers/mask_to_selection.html#intersect"
end_define

begin_define
DECL|macro|GIMP_HELP_LAYER_ALPHA_ADD
define|#
directive|define
name|GIMP_HELP_LAYER_ALPHA_ADD
value|"layers/add_alpha_channel.html"
end_define

begin_define
DECL|macro|GIMP_HELP_LAYER_ALPHA_SEL_REPLACE
define|#
directive|define
name|GIMP_HELP_LAYER_ALPHA_SEL_REPLACE
value|"layers/alpha_to_selection.html"
end_define

begin_define
DECL|macro|GIMP_HELP_LAYER_ALPHA_SEL_ADD
define|#
directive|define
name|GIMP_HELP_LAYER_ALPHA_SEL_ADD
value|"layers/alpha_to_selection.html#add"
end_define

begin_define
DECL|macro|GIMP_HELP_LAYER_ALPHA_SEL_SUB
define|#
directive|define
name|GIMP_HELP_LAYER_ALPHA_SEL_SUB
value|"layers/alpha_to_selection.html#subtract"
end_define

begin_define
DECL|macro|GIMP_HELP_LAYER_ALPHA_SEL_INTERSECT
define|#
directive|define
name|GIMP_HELP_LAYER_ALPHA_SEL_INTERSECT
value|"layers/alpha_to_selection.html#intersect"
end_define

begin_define
DECL|macro|GIMP_HELP_LAYER_FLIP_HORIZONTAL
define|#
directive|define
name|GIMP_HELP_LAYER_FLIP_HORIZONTAL
value|"layers/flip_layer.html"
end_define

begin_define
DECL|macro|GIMP_HELP_LAYER_FLIP_VERTICAL
define|#
directive|define
name|GIMP_HELP_LAYER_FLIP_VERTICAL
value|"layers/flip_layer.html"
end_define

begin_define
DECL|macro|GIMP_HELP_LAYER_ROTATE_90
define|#
directive|define
name|GIMP_HELP_LAYER_ROTATE_90
value|"layers/rotate_layer.html"
end_define

begin_define
DECL|macro|GIMP_HELP_LAYER_ROTATE_180
define|#
directive|define
name|GIMP_HELP_LAYER_ROTATE_180
value|"layers/rotate_layer.html"
end_define

begin_define
DECL|macro|GIMP_HELP_LAYER_ROTATE_270
define|#
directive|define
name|GIMP_HELP_LAYER_ROTATE_270
value|"layers/rotate_layer.html"
end_define

begin_define
DECL|macro|GIMP_HELP_LAYER_OFFSET
define|#
directive|define
name|GIMP_HELP_LAYER_OFFSET
value|"layers/dialogs/offset.html"
end_define

begin_define
DECL|macro|GIMP_HELP_LAYER_RESIZE
define|#
directive|define
name|GIMP_HELP_LAYER_RESIZE
value|"layers/dialogs/layer_boundary_size.html"
end_define

begin_define
DECL|macro|GIMP_HELP_LAYER_RESIZE_TO_IMAGE
define|#
directive|define
name|GIMP_HELP_LAYER_RESIZE_TO_IMAGE
value|"layers/layer_to_image_size.html"
end_define

begin_define
DECL|macro|GIMP_HELP_LAYER_SCALE
define|#
directive|define
name|GIMP_HELP_LAYER_SCALE
value|"layers/dialogs/scale_layer.html"
end_define

begin_define
DECL|macro|GIMP_HELP_LAYER_CROP
define|#
directive|define
name|GIMP_HELP_LAYER_CROP
value|"layers/dialogs/crop_layer.html"
end_define

begin_define
DECL|macro|GIMP_HELP_LAYER_EDIT
define|#
directive|define
name|GIMP_HELP_LAYER_EDIT
value|"layers/dialogs/edit_layer_attributes.html"
end_define

begin_define
DECL|macro|GIMP_HELP_CHANNEL_DIALOG
define|#
directive|define
name|GIMP_HELP_CHANNEL_DIALOG
value|"channels/dialogs/channels_dialog.html"
end_define

begin_define
DECL|macro|GIMP_HELP_CHANNEL_NEW
define|#
directive|define
name|GIMP_HELP_CHANNEL_NEW
value|"channels/dialogs/new_channel.html"
end_define

begin_define
DECL|macro|GIMP_HELP_CHANNEL_RAISE
define|#
directive|define
name|GIMP_HELP_CHANNEL_RAISE
value|"channels/raise_channel.html"
end_define

begin_define
DECL|macro|GIMP_HELP_CHANNEL_LOWER
define|#
directive|define
name|GIMP_HELP_CHANNEL_LOWER
value|"channels/lower_channel.html"
end_define

begin_define
DECL|macro|GIMP_HELP_CHANNEL_DUPLICATE
define|#
directive|define
name|GIMP_HELP_CHANNEL_DUPLICATE
value|"channels/duplicate_channel.html"
end_define

begin_define
DECL|macro|GIMP_HELP_CHANNEL_DELETE
define|#
directive|define
name|GIMP_HELP_CHANNEL_DELETE
value|"channels/delete_channel.html"
end_define

begin_define
DECL|macro|GIMP_HELP_CHANNEL_SEL_REPLACE
define|#
directive|define
name|GIMP_HELP_CHANNEL_SEL_REPLACE
value|"channels/channel_to_selection.html"
end_define

begin_define
DECL|macro|GIMP_HELP_CHANNEL_SEL_ADD
define|#
directive|define
name|GIMP_HELP_CHANNEL_SEL_ADD
value|"channels/channel_to_selection.html#add"
end_define

begin_define
DECL|macro|GIMP_HELP_CHANNEL_SEL_SUB
define|#
directive|define
name|GIMP_HELP_CHANNEL_SEL_SUB
value|"channels/channel_to_selection.html#subtract"
end_define

begin_define
DECL|macro|GIMP_HELP_CHANNEL_SEL_INTERSECT
define|#
directive|define
name|GIMP_HELP_CHANNEL_SEL_INTERSECT
value|"channels/channel_to_selection.html#intersect"
end_define

begin_define
DECL|macro|GIMP_HELP_CHANNEL_EDIT
define|#
directive|define
name|GIMP_HELP_CHANNEL_EDIT
value|"channels/dialogs/edit_channel_attributes.html"
end_define

begin_define
DECL|macro|GIMP_HELP_PATH_DIALOG
define|#
directive|define
name|GIMP_HELP_PATH_DIALOG
value|"paths/dislogs/paths_dialog.html"
end_define

begin_define
DECL|macro|GIMP_HELP_PATH_NEW
define|#
directive|define
name|GIMP_HELP_PATH_NEW
value|"paths/new_path.html"
end_define

begin_define
DECL|macro|GIMP_HELP_PATH_RAISE
define|#
directive|define
name|GIMP_HELP_PATH_RAISE
value|"paths/raise_path.html"
end_define

begin_define
DECL|macro|GIMP_HELP_PATH_LOWER
define|#
directive|define
name|GIMP_HELP_PATH_LOWER
value|"paths/lower_path.html"
end_define

begin_define
DECL|macro|GIMP_HELP_PATH_DUPLICATE
define|#
directive|define
name|GIMP_HELP_PATH_DUPLICATE
value|"paths/duplicate_path.html"
end_define

begin_define
DECL|macro|GIMP_HELP_PATH_DELETE
define|#
directive|define
name|GIMP_HELP_PATH_DELETE
value|"paths/delete_path.html"
end_define

begin_define
DECL|macro|GIMP_HELP_PATH_SEL_REPLACE
define|#
directive|define
name|GIMP_HELP_PATH_SEL_REPLACE
value|"paths/path_to_selection.html"
end_define

begin_define
DECL|macro|GIMP_HELP_PATH_SEL_ADD
define|#
directive|define
name|GIMP_HELP_PATH_SEL_ADD
value|"paths/path_to_selection.html#add"
end_define

begin_define
DECL|macro|GIMP_HELP_PATH_SEL_SUB
define|#
directive|define
name|GIMP_HELP_PATH_SEL_SUB
value|"paths/path_to_selection.html#subtract"
end_define

begin_define
DECL|macro|GIMP_HELP_PATH_SEL_INTERSECT
define|#
directive|define
name|GIMP_HELP_PATH_SEL_INTERSECT
value|"paths/path_to_selection.html#intersect"
end_define

begin_define
DECL|macro|GIMP_HELP_PATH_STROKE
define|#
directive|define
name|GIMP_HELP_PATH_STROKE
value|"paths/stroke_path.html"
end_define

begin_define
DECL|macro|GIMP_HELP_PATH_COPY
define|#
directive|define
name|GIMP_HELP_PATH_COPY
value|"paths/copy_path.html"
end_define

begin_define
DECL|macro|GIMP_HELP_PATH_PASTE
define|#
directive|define
name|GIMP_HELP_PATH_PASTE
value|"paths/paste_path.html"
end_define

begin_define
DECL|macro|GIMP_HELP_PATH_IMPORT
define|#
directive|define
name|GIMP_HELP_PATH_IMPORT
value|"paths/dialogs/import_path.html"
end_define

begin_define
DECL|macro|GIMP_HELP_PATH_EXPORT
define|#
directive|define
name|GIMP_HELP_PATH_EXPORT
value|"paths/dialogs/export_path.html"
end_define

begin_define
DECL|macro|GIMP_HELP_PATH_EDIT
define|#
directive|define
name|GIMP_HELP_PATH_EDIT
value|"paths/dialogs/edit_path_attributes.html"
end_define

begin_define
DECL|macro|GIMP_HELP_TOOL_BY_COLOR_SELECT
define|#
directive|define
name|GIMP_HELP_TOOL_BY_COLOR_SELECT
value|"tools/by_color_select.html"
end_define

begin_define
DECL|macro|GIMP_HELP_TOOL_COLOR_BALANCE
define|#
directive|define
name|GIMP_HELP_TOOL_COLOR_BALANCE
value|"tools/color_balance.html"
end_define

begin_define
DECL|macro|GIMP_HELP_TOOL_HUE_SATURATION
define|#
directive|define
name|GIMP_HELP_TOOL_HUE_SATURATION
value|"tools/hue_saturation.html"
end_define

begin_define
DECL|macro|GIMP_HELP_TOOL_COLORIZE
define|#
directive|define
name|GIMP_HELP_TOOL_COLORIZE
value|"tools/colorize.html"
end_define

begin_define
DECL|macro|GIMP_HELP_TOOL_BRIGHTNESS_CONTRAST
define|#
directive|define
name|GIMP_HELP_TOOL_BRIGHTNESS_CONTRAST
value|"tools/brightness-contrast.html"
end_define

begin_define
DECL|macro|GIMP_HELP_TOOL_THRESHOLD
define|#
directive|define
name|GIMP_HELP_TOOL_THRESHOLD
value|"tools/threshold.html"
end_define

begin_define
DECL|macro|GIMP_HELP_TOOL_LEVELS
define|#
directive|define
name|GIMP_HELP_TOOL_LEVELS
value|"tools/levels.html"
end_define

begin_define
DECL|macro|GIMP_HELP_TOOL_CURVES
define|#
directive|define
name|GIMP_HELP_TOOL_CURVES
value|"tools/curves.html"
end_define

begin_define
DECL|macro|GIMP_HELP_TOOL_POSTERIZE
define|#
directive|define
name|GIMP_HELP_TOOL_POSTERIZE
value|"tools/posterize.html"
end_define

begin_define
DECL|macro|GIMP_HELP_TOOL_HISTOGRAM
define|#
directive|define
name|GIMP_HELP_TOOL_HISTOGRAM
value|"tools/histogram.html"
end_define

begin_define
DECL|macro|GIMP_HELP_TOOL_ROTATE
define|#
directive|define
name|GIMP_HELP_TOOL_ROTATE
value|"tools/rotate.html"
end_define

begin_define
DECL|macro|GIMP_HELP_TOOL_VECTORS
define|#
directive|define
name|GIMP_HELP_TOOL_VECTORS
value|"tools/vectors.html"
end_define

begin_define
DECL|macro|GIMP_HELP_FILTER_REPEAT
define|#
directive|define
name|GIMP_HELP_FILTER_REPEAT
value|"filters/repeat_last.html"
end_define

begin_define
DECL|macro|GIMP_HELP_FILTER_RESHOW
define|#
directive|define
name|GIMP_HELP_FILTER_RESHOW
value|"filters/reshow_last.html"
end_define

begin_define
DECL|macro|GIMP_HELP_TOOLBOX
define|#
directive|define
name|GIMP_HELP_TOOLBOX
value|"toolbox/toolbox.html"
end_define

begin_define
DECL|macro|GIMP_HELP_TOOLBOX_DEFAULT_COLORS
define|#
directive|define
name|GIMP_HELP_TOOLBOX_DEFAULT_COLORS
value|"toolbox/toolbox.html#default_colors"
end_define

begin_define
DECL|macro|GIMP_HELP_TOOLBOX_SWAP_COLORS
define|#
directive|define
name|GIMP_HELP_TOOLBOX_SWAP_COLORS
value|"toolbox/toolbox.html#swap_colors"
end_define

begin_define
DECL|macro|GIMP_HELP_BRUSH_DIALOG
define|#
directive|define
name|GIMP_HELP_BRUSH_DIALOG
value|"dialogs/brush_selection.html"
end_define

begin_define
DECL|macro|GIMP_HELP_BRUSH_NEW
define|#
directive|define
name|GIMP_HELP_BRUSH_NEW
value|"dialogs/brush_selection.html"
end_define

begin_define
DECL|macro|GIMP_HELP_BRUSH_DUPLICATE
define|#
directive|define
name|GIMP_HELP_BRUSH_DUPLICATE
value|"dialogs/brush_selection.html"
end_define

begin_define
DECL|macro|GIMP_HELP_BRUSH_EDIT
define|#
directive|define
name|GIMP_HELP_BRUSH_EDIT
value|"dialogs/brush_selection.html"
end_define

begin_define
DECL|macro|GIMP_HELP_BRUSH_DELETE
define|#
directive|define
name|GIMP_HELP_BRUSH_DELETE
value|"dialogs/brush_selection.html"
end_define

begin_define
DECL|macro|GIMP_HELP_BRUSH_REFRESH
define|#
directive|define
name|GIMP_HELP_BRUSH_REFRESH
value|"dialogs/brush_selection.html"
end_define

begin_define
DECL|macro|GIMP_HELP_PATTERN_DIALOG
define|#
directive|define
name|GIMP_HELP_PATTERN_DIALOG
value|"dialogs/pattern_selection.html"
end_define

begin_define
DECL|macro|GIMP_HELP_PATTERN_NEW
define|#
directive|define
name|GIMP_HELP_PATTERN_NEW
value|"dialogs/pattern_selection.html"
end_define

begin_define
DECL|macro|GIMP_HELP_PATTERN_DUPLICATE
define|#
directive|define
name|GIMP_HELP_PATTERN_DUPLICATE
value|"dialogs/pattern_selection.html"
end_define

begin_define
DECL|macro|GIMP_HELP_PATTERN_EDIT
define|#
directive|define
name|GIMP_HELP_PATTERN_EDIT
value|"dialogs/pattern_selection.html"
end_define

begin_define
DECL|macro|GIMP_HELP_PATTERN_DELETE
define|#
directive|define
name|GIMP_HELP_PATTERN_DELETE
value|"dialogs/pattern_selection.html"
end_define

begin_define
DECL|macro|GIMP_HELP_PATTERN_REFRESH
define|#
directive|define
name|GIMP_HELP_PATTERN_REFRESH
value|"dialogs/pattern_selection.html"
end_define

begin_define
DECL|macro|GIMP_HELP_GRADIENT_DIALOG
define|#
directive|define
name|GIMP_HELP_GRADIENT_DIALOG
value|"dialogs/gradient_selection.html"
end_define

begin_define
DECL|macro|GIMP_HELP_GRADIENT_NEW
define|#
directive|define
name|GIMP_HELP_GRADIENT_NEW
value|"dialogs/gradient_selection.html"
end_define

begin_define
DECL|macro|GIMP_HELP_GRADIENT_DUPLICATE
define|#
directive|define
name|GIMP_HELP_GRADIENT_DUPLICATE
value|"dialogs/gradient_selection.html"
end_define

begin_define
DECL|macro|GIMP_HELP_GRADIENT_EDIT
define|#
directive|define
name|GIMP_HELP_GRADIENT_EDIT
value|"dialogs/gradient_selection.html"
end_define

begin_define
DECL|macro|GIMP_HELP_GRADIENT_DELETE
define|#
directive|define
name|GIMP_HELP_GRADIENT_DELETE
value|"dialogs/gradient_selection.html"
end_define

begin_define
DECL|macro|GIMP_HELP_GRADIENT_REFRESH
define|#
directive|define
name|GIMP_HELP_GRADIENT_REFRESH
value|"dialogs/gradient_selection.html"
end_define

begin_define
DECL|macro|GIMP_HELP_GRADIENT_SAVE_AS_POV
define|#
directive|define
name|GIMP_HELP_GRADIENT_SAVE_AS_POV
value|"dialogs/gradient_selection.html"
end_define

begin_define
DECL|macro|GIMP_HELP_PALETTE_DIALOG
define|#
directive|define
name|GIMP_HELP_PALETTE_DIALOG
value|"dialogs/palette_selection.html"
end_define

begin_define
DECL|macro|GIMP_HELP_PALETTE_NEW
define|#
directive|define
name|GIMP_HELP_PALETTE_NEW
value|"dialogs/palette_selection.html"
end_define

begin_define
DECL|macro|GIMP_HELP_PALETTE_DUPLICATE
define|#
directive|define
name|GIMP_HELP_PALETTE_DUPLICATE
value|"dialogs/palette_selection.html"
end_define

begin_define
DECL|macro|GIMP_HELP_PALETTE_EDIT
define|#
directive|define
name|GIMP_HELP_PALETTE_EDIT
value|"dialogs/palette_selection.html"
end_define

begin_define
DECL|macro|GIMP_HELP_PALETTE_DELETE
define|#
directive|define
name|GIMP_HELP_PALETTE_DELETE
value|"dialogs/palette_selection.html"
end_define

begin_define
DECL|macro|GIMP_HELP_PALETTE_REFRESH
define|#
directive|define
name|GIMP_HELP_PALETTE_REFRESH
value|"dialogs/palette_selection.html"
end_define

begin_define
DECL|macro|GIMP_HELP_PALETTE_IMPORT
define|#
directive|define
name|GIMP_HELP_PALETTE_IMPORT
value|"dialogs/palette_selection.html"
end_define

begin_define
DECL|macro|GIMP_HELP_PALETTE_MERGE
define|#
directive|define
name|GIMP_HELP_PALETTE_MERGE
value|"dialogs/palette_selection.html"
end_define

begin_define
DECL|macro|GIMP_HELP_FONT_DIALOG
define|#
directive|define
name|GIMP_HELP_FONT_DIALOG
value|"dialogs/font_selection.html"
end_define

begin_define
DECL|macro|GIMP_HELP_BUFFER_DIALOG
define|#
directive|define
name|GIMP_HELP_BUFFER_DIALOG
value|"dialogs/named_buffers.html"
end_define

begin_define
DECL|macro|GIMP_HELP_BUFFER_CUT
define|#
directive|define
name|GIMP_HELP_BUFFER_CUT
value|"dialogs/cut_named.html"
end_define

begin_define
DECL|macro|GIMP_HELP_BUFFER_COPY
define|#
directive|define
name|GIMP_HELP_BUFFER_COPY
value|"dialogs/copy_named.html"
end_define

begin_define
DECL|macro|GIMP_HELP_BUFFER_PASTE
define|#
directive|define
name|GIMP_HELP_BUFFER_PASTE
value|"dialogs/paste_named.html"
end_define

begin_define
DECL|macro|GIMP_HELP_BUFFER_PASTE_INTO
define|#
directive|define
name|GIMP_HELP_BUFFER_PASTE_INTO
value|"dialogs/paste_named.html"
end_define

begin_define
DECL|macro|GIMP_HELP_BUFFER_PASTE_AS_NEW
define|#
directive|define
name|GIMP_HELP_BUFFER_PASTE_AS_NEW
value|"dialogs/paste_named.html"
end_define

begin_define
DECL|macro|GIMP_HELP_BUFFER_DELETE
define|#
directive|define
name|GIMP_HELP_BUFFER_DELETE
value|"dialogs/delete_buffer.html"
end_define

begin_define
DECL|macro|GIMP_HELP_TEMPLATE_DIALOG
define|#
directive|define
name|GIMP_HELP_TEMPLATE_DIALOG
value|"dialogs/templates.html"
end_define

begin_define
DECL|macro|GIMP_HELP_TEMPLATE_NEW
define|#
directive|define
name|GIMP_HELP_TEMPLATE_NEW
value|"dialogs/templates.html"
end_define

begin_define
DECL|macro|GIMP_HELP_TEMPLATE_DUPLICATE
define|#
directive|define
name|GIMP_HELP_TEMPLATE_DUPLICATE
value|"dialogs/templates.html"
end_define

begin_define
DECL|macro|GIMP_HELP_TEMPLATE_EDIT
define|#
directive|define
name|GIMP_HELP_TEMPLATE_EDIT
value|"dialogs/templates.html"
end_define

begin_define
DECL|macro|GIMP_HELP_TEMPLATE_IMAGE_NEW
define|#
directive|define
name|GIMP_HELP_TEMPLATE_IMAGE_NEW
value|"dialogs/templates.html"
end_define

begin_define
DECL|macro|GIMP_HELP_TEMPLATE_DELETE
define|#
directive|define
name|GIMP_HELP_TEMPLATE_DELETE
value|"dialogs/templates.html"
end_define

begin_define
DECL|macro|GIMP_HELP_PREFERENCES_DIALOG
define|#
directive|define
name|GIMP_HELP_PREFERENCES_DIALOG
value|"file/dialogs/preferences/preferences.html"
end_define

begin_define
DECL|macro|GIMP_HELP_COLOR_DIALOG
define|#
directive|define
name|GIMP_HELP_COLOR_DIALOG
value|"dialogs/color.html"
end_define

begin_define
DECL|macro|GIMP_HELP_TOOL_OPTIONS_DIALOG
define|#
directive|define
name|GIMP_HELP_TOOL_OPTIONS_DIALOG
value|"dialogs/tool_options.html"
end_define

begin_define
DECL|macro|GIMP_HELP_DEVICE_STATUS_DIALOG
define|#
directive|define
name|GIMP_HELP_DEVICE_STATUS_DIALOG
value|"dialogs/device_status.html"
end_define

begin_define
DECL|macro|GIMP_HELP_DOCUMENT_DIALOG
define|#
directive|define
name|GIMP_HELP_DOCUMENT_DIALOG
value|"file/dialogs/document_index.html"
end_define

begin_define
DECL|macro|GIMP_HELP_MODULE_DIALOG
define|#
directive|define
name|GIMP_HELP_MODULE_DIALOG
value|"dialogs/module_manager.html"
end_define

begin_define
DECL|macro|GIMP_HELP_INFO_DIALOG
define|#
directive|define
name|GIMP_HELP_INFO_DIALOG
value|"view/dialogs/info_window.html"
end_define

begin_define
DECL|macro|GIMP_HELP_NAVIGATION_DIALOG
define|#
directive|define
name|GIMP_HELP_NAVIGATION_DIALOG
value|"view/dialogs/navigation_window.html"
end_define

begin_define
DECL|macro|GIMP_HELP_DISPLAY_FILTER_DIALOG
define|#
directive|define
name|GIMP_HELP_DISPLAY_FILTER_DIALOG
value|"dialogs/display_filters/display_filters.html"
end_define

begin_define
DECL|macro|GIMP_HELP_UNDO_DIALOG
define|#
directive|define
name|GIMP_HELP_UNDO_DIALOG
value|"dialogs/undo_history.html"
end_define

begin_define
DECL|macro|GIMP_HELP_INDEXED_PALETTE_DIALOG
define|#
directive|define
name|GIMP_HELP_INDEXED_PALETTE_DIALOG
value|"dialogs/indexed_palette.html"
end_define

begin_define
DECL|macro|GIMP_HELP_ERROR_DIALOG
define|#
directive|define
name|GIMP_HELP_ERROR_DIALOG
value|"dialogs/error_console.html"
end_define

begin_define
DECL|macro|GIMP_HELP_TIPS_DIALOG
define|#
directive|define
name|GIMP_HELP_TIPS_DIALOG
value|"help/dialogs/tip_of_the_day.html"
end_define

begin_define
DECL|macro|GIMP_HELP_ABOUT_DIALOG
define|#
directive|define
name|GIMP_HELP_ABOUT_DIALOG
value|"help/dialogs/about.html"
end_define

begin_define
DECL|macro|GIMP_HELP_HELP
define|#
directive|define
name|GIMP_HELP_HELP
value|"help/dialogs/help.html"
end_define

begin_define
DECL|macro|GIMP_HELP_HELP_CONTEXT
define|#
directive|define
name|GIMP_HELP_HELP_CONTEXT
value|"help/context_help.html"
end_define

begin_endif
endif|#
directive|endif
end_endif

begin_comment
comment|/* __GIMP_HELP_IDS_H__ */
end_comment

end_unit

