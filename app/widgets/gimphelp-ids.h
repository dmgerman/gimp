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
DECL|macro|GIMP_HELP_MAIN
define|#
directive|define
name|GIMP_HELP_MAIN
value|"index.html"
end_define

begin_define
DECL|macro|GIMP_HELP_FILE_NEW
define|#
directive|define
name|GIMP_HELP_FILE_NEW
value|"dialogs/file_new.html"
end_define

begin_define
DECL|macro|GIMP_HELP_FILE_NEW_CONFIRM
define|#
directive|define
name|GIMP_HELP_FILE_NEW_CONFIRM
value|"dialogs/file_new.html#confirm_dialog"
end_define

begin_define
DECL|macro|GIMP_HELP_FILE_OPEN
define|#
directive|define
name|GIMP_HELP_FILE_OPEN
value|"dialogs/file_open.html"
end_define

begin_define
DECL|macro|GIMP_HELP_FILE_OPEN_BY_EXTENSION
define|#
directive|define
name|GIMP_HELP_FILE_OPEN_BY_EXTENSION
value|"file/open_by_extension.html"
end_define

begin_define
DECL|macro|GIMP_HELP_FILE_OPEN_RECENT
define|#
directive|define
name|GIMP_HELP_FILE_OPEN_RECENT
value|"file/last_opened.html"
end_define

begin_define
DECL|macro|GIMP_HELP_FILE_SAVE
define|#
directive|define
name|GIMP_HELP_FILE_SAVE
value|"dialogs/file_save.html"
end_define

begin_define
DECL|macro|GIMP_HELP_FILE_SAVE_AS
define|#
directive|define
name|GIMP_HELP_FILE_SAVE_AS
value|"dialogs/file_save.html"
end_define

begin_define
DECL|macro|GIMP_HELP_FILE_SAVE_A_COPY
define|#
directive|define
name|GIMP_HELP_FILE_SAVE_A_COPY
value|"dialogs/file_save.html"
end_define

begin_define
DECL|macro|GIMP_HELP_FILE_SAVE_AS_TEMPLATE
define|#
directive|define
name|GIMP_HELP_FILE_SAVE_AS_TEMPLATE
value|"dialogs/file_save.html"
end_define

begin_define
DECL|macro|GIMP_HELP_FILE_SAVE_BY_EXTENSION
define|#
directive|define
name|GIMP_HELP_FILE_SAVE_BY_EXTENSION
value|"file/save_by_extension.html"
end_define

begin_define
DECL|macro|GIMP_HELP_FILE_SAVE_OVERWRITE
define|#
directive|define
name|GIMP_HELP_FILE_SAVE_OVERWRITE
value|"dialogs/file_exists.html"
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
DECL|macro|GIMP_HELP_FILE_CLOSE_CONFIRM
define|#
directive|define
name|GIMP_HELP_FILE_CLOSE_CONFIRM
value|"dialogs/really_close.html"
end_define

begin_define
DECL|macro|GIMP_HELP_FILE_QUIT
define|#
directive|define
name|GIMP_HELP_FILE_QUIT
value|"file/quit.html"
end_define

begin_define
DECL|macro|GIMP_HELP_FILE_QUIT_CONFIRM
define|#
directive|define
name|GIMP_HELP_FILE_QUIT_CONFIRM
value|"dialogs/really_quit.html"
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
DECL|macro|GIMP_HELP_SELECTION_DIALOG
define|#
directive|define
name|GIMP_HELP_SELECTION_DIALOG
value|"dialogs/selection_editor.html"
end_define

begin_define
DECL|macro|GIMP_HELP_SELECTION_ALL
define|#
directive|define
name|GIMP_HELP_SELECTION_ALL
value|"select/all.html"
end_define

begin_define
DECL|macro|GIMP_HELP_SELECTION_NONE
define|#
directive|define
name|GIMP_HELP_SELECTION_NONE
value|"select/none.html"
end_define

begin_define
DECL|macro|GIMP_HELP_SELECTION_INVERT
define|#
directive|define
name|GIMP_HELP_SELECTION_INVERT
value|"select/invert.html"
end_define

begin_define
DECL|macro|GIMP_HELP_SELECTION_FLOAT
define|#
directive|define
name|GIMP_HELP_SELECTION_FLOAT
value|"select/float.html"
end_define

begin_define
DECL|macro|GIMP_HELP_SELECTION_FEATHER
define|#
directive|define
name|GIMP_HELP_SELECTION_FEATHER
value|"dialogs/feather_selection.html"
end_define

begin_define
DECL|macro|GIMP_HELP_SELECTION_SHARPEN
define|#
directive|define
name|GIMP_HELP_SELECTION_SHARPEN
value|"select/sharpen.html"
end_define

begin_define
DECL|macro|GIMP_HELP_SELECTION_SHRINK
define|#
directive|define
name|GIMP_HELP_SELECTION_SHRINK
value|"dialogs/shrink_selection.html"
end_define

begin_define
DECL|macro|GIMP_HELP_SELECTION_GROW
define|#
directive|define
name|GIMP_HELP_SELECTION_GROW
value|"dialogs/grow_selection.html"
end_define

begin_define
DECL|macro|GIMP_HELP_SELECTION_BORDER
define|#
directive|define
name|GIMP_HELP_SELECTION_BORDER
value|"dialogs/border_selection.html"
end_define

begin_define
DECL|macro|GIMP_HELP_SELECTION_STROKE
define|#
directive|define
name|GIMP_HELP_SELECTION_STROKE
value|"edit/stroke.html"
end_define

begin_define
DECL|macro|GIMP_HELP_SELECTION_TO_CHANNEL
define|#
directive|define
name|GIMP_HELP_SELECTION_TO_CHANNEL
value|"select/save_to_channel.html"
end_define

begin_define
DECL|macro|GIMP_HELP_SELECTION_TO_PATH
define|#
directive|define
name|GIMP_HELP_SELECTION_TO_PATH
value|"select/to_path.html"
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
DECL|macro|GIMP_HELP_VIEW_ZOOM_OUT
define|#
directive|define
name|GIMP_HELP_VIEW_ZOOM_OUT
value|"view/zoom.html"
end_define

begin_define
DECL|macro|GIMP_HELP_VIEW_ZOOM_IN
define|#
directive|define
name|GIMP_HELP_VIEW_ZOOM_IN
value|"view/zoom.html"
end_define

begin_define
DECL|macro|GIMP_HELP_VIEW_ZOOM_100
define|#
directive|define
name|GIMP_HELP_VIEW_ZOOM_100
value|"view/zoom.html"
end_define

begin_define
DECL|macro|GIMP_HELP_VIEW_ZOOM_FIT
define|#
directive|define
name|GIMP_HELP_VIEW_ZOOM_FIT
value|"view/zoom.html"
end_define

begin_define
DECL|macro|GIMP_HELP_VIEW_ZOOM_OTHER
define|#
directive|define
name|GIMP_HELP_VIEW_ZOOM_OTHER
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
value|"dialogs/flip_image.html"
end_define

begin_define
DECL|macro|GIMP_HELP_IMAGE_FLIP_VERTICAL
define|#
directive|define
name|GIMP_HELP_IMAGE_FLIP_VERTICAL
value|"dialogs/flip_image.html"
end_define

begin_define
DECL|macro|GIMP_HELP_IMAGE_ROTATE_90
define|#
directive|define
name|GIMP_HELP_IMAGE_ROTATE_90
value|"dialogs/rotate_image.html"
end_define

begin_define
DECL|macro|GIMP_HELP_IMAGE_ROTATE_180
define|#
directive|define
name|GIMP_HELP_IMAGE_ROTATE_180
value|"dialogs/rotate_image.html"
end_define

begin_define
DECL|macro|GIMP_HELP_IMAGE_ROTATE_270
define|#
directive|define
name|GIMP_HELP_IMAGE_ROTATE_270
value|"dialogs/rotate_image.html"
end_define

begin_define
DECL|macro|GIMP_HELP_IMAGE_RESIZE
define|#
directive|define
name|GIMP_HELP_IMAGE_RESIZE
value|"dialogs/set_canvas_size.html"
end_define

begin_define
DECL|macro|GIMP_HELP_IMAGE_SCALE
define|#
directive|define
name|GIMP_HELP_IMAGE_SCALE
value|"dialogs/scale_image.html"
end_define

begin_define
DECL|macro|GIMP_HELP_IMAGE_SCALE_WARNING
define|#
directive|define
name|GIMP_HELP_IMAGE_SCALE_WARNING
value|"dialogs/scale_image.html"
end_define

begin_define
DECL|macro|GIMP_HELP_IMAGE_CROP
define|#
directive|define
name|GIMP_HELP_IMAGE_CROP
value|"dialogs/crop_image.html"
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
value|"/dialogs/merge_visible_layers.html"
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
value|"dialogs/configure_grid.html"
end_define

begin_define
DECL|macro|GIMP_HELP_LAYER_DIALOG
define|#
directive|define
name|GIMP_HELP_LAYER_DIALOG
value|"/dialogs/layers_dialog.html"
end_define

begin_define
DECL|macro|GIMP_HELP_LAYER_NEW
define|#
directive|define
name|GIMP_HELP_LAYER_NEW
value|"/dialogs/new_layer.html"
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
DECL|macro|GIMP_HELP_LAYER_RAISE_TO_TOP
define|#
directive|define
name|GIMP_HELP_LAYER_RAISE_TO_TOP
value|"layers/stack/stack.html#layer_to_top"
end_define

begin_define
DECL|macro|GIMP_HELP_LAYER_LOWER
define|#
directive|define
name|GIMP_HELP_LAYER_LOWER
value|"layers/stack/stack.html#lower_layer"
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
value|"dialogs/add_layer_mask.html"
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
DECL|macro|GIMP_HELP_LAYER_MASK_SELECTION_REPLACE
define|#
directive|define
name|GIMP_HELP_LAYER_MASK_SELECTION_REPLACE
value|"layers/mask_to_selection.html"
end_define

begin_define
DECL|macro|GIMP_HELP_LAYER_MASK_SELECTION_ADD
define|#
directive|define
name|GIMP_HELP_LAYER_MASK_SELECTION_ADD
value|"layers/mask_to_selection.html#add"
end_define

begin_define
DECL|macro|GIMP_HELP_LAYER_MASK_SELECTION_SUBTRACT
define|#
directive|define
name|GIMP_HELP_LAYER_MASK_SELECTION_SUBTRACT
value|"layers/mask_to_selection.html#subtract"
end_define

begin_define
DECL|macro|GIMP_HELP_LAYER_MASK_SELECTION_INTERSECT
define|#
directive|define
name|GIMP_HELP_LAYER_MASK_SELECTION_INTERSECT
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
DECL|macro|GIMP_HELP_LAYER_ALPHA_SELECTION_REPLACE
define|#
directive|define
name|GIMP_HELP_LAYER_ALPHA_SELECTION_REPLACE
value|"layers/alpha_to_selection.html"
end_define

begin_define
DECL|macro|GIMP_HELP_LAYER_ALPHA_SELECTION_ADD
define|#
directive|define
name|GIMP_HELP_LAYER_ALPHA_SELECTION_ADD
value|"layers/alpha_to_selection.html#add"
end_define

begin_define
DECL|macro|GIMP_HELP_LAYER_ALPHA_SELECTION_SUBTRACT
define|#
directive|define
name|GIMP_HELP_LAYER_ALPHA_SELECTION_SUBTRACT
value|"layers/alpha_to_selection.html#subtract"
end_define

begin_define
DECL|macro|GIMP_HELP_LAYER_ALPHA_SELECTION_INTERSECT
define|#
directive|define
name|GIMP_HELP_LAYER_ALPHA_SELECTION_INTERSECT
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
value|"dialogs/offset.html"
end_define

begin_define
DECL|macro|GIMP_HELP_LAYER_RESIZE
define|#
directive|define
name|GIMP_HELP_LAYER_RESIZE
value|"dialogs/layer_boundary_size.html"
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
value|"dialogs/scale_layer.html"
end_define

begin_define
DECL|macro|GIMP_HELP_LAYER_CROP
define|#
directive|define
name|GIMP_HELP_LAYER_CROP
value|"dialogs/crop_layer.html"
end_define

begin_define
DECL|macro|GIMP_HELP_LAYER_EDIT
define|#
directive|define
name|GIMP_HELP_LAYER_EDIT
value|"dialogs/edit_layer_attributes.html"
end_define

begin_define
DECL|macro|GIMP_HELP_CHANNEL_DIALOG
define|#
directive|define
name|GIMP_HELP_CHANNEL_DIALOG
value|"dialogs/channels_dialog.html"
end_define

begin_define
DECL|macro|GIMP_HELP_CHANNEL_NEW
define|#
directive|define
name|GIMP_HELP_CHANNEL_NEW
value|"dialogs/new_channel.html"
end_define

begin_define
DECL|macro|GIMP_HELP_CHANNEL_RAISE
define|#
directive|define
name|GIMP_HELP_CHANNEL_RAISE
value|"channels/raise_channel.html"
end_define

begin_define
DECL|macro|GIMP_HELP_CHANNEL_RAISE_TO_TOP
define|#
directive|define
name|GIMP_HELP_CHANNEL_RAISE_TO_TOP
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
DECL|macro|GIMP_HELP_CHANNEL_LOWER_TO_BOTTOM
define|#
directive|define
name|GIMP_HELP_CHANNEL_LOWER_TO_BOTTOM
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
DECL|macro|GIMP_HELP_CHANNEL_SELECTION_REPLACE
define|#
directive|define
name|GIMP_HELP_CHANNEL_SELECTION_REPLACE
value|"channels/channel_to_selection.html"
end_define

begin_define
DECL|macro|GIMP_HELP_CHANNEL_SELECTION_ADD
define|#
directive|define
name|GIMP_HELP_CHANNEL_SELECTION_ADD
value|"channels/channel_to_selection.html#add"
end_define

begin_define
DECL|macro|GIMP_HELP_CHANNEL_SELECTION_SUBTRACT
define|#
directive|define
name|GIMP_HELP_CHANNEL_SELECTION_SUBTRACT
value|"channels/channel_to_selection.html#subtract"
end_define

begin_define
DECL|macro|GIMP_HELP_CHANNEL_SELECTION_INTERSECT
define|#
directive|define
name|GIMP_HELP_CHANNEL_SELECTION_INTERSECT
value|"channels/channel_to_selection.html#intersect"
end_define

begin_define
DECL|macro|GIMP_HELP_CHANNEL_EDIT
define|#
directive|define
name|GIMP_HELP_CHANNEL_EDIT
value|"dialogs/edit_channel_attributes.html"
end_define

begin_define
DECL|macro|GIMP_HELP_QMASK_TOGGLE
define|#
directive|define
name|GIMP_HELP_QMASK_TOGGLE
value|"select/quickmask.html"
end_define

begin_define
DECL|macro|GIMP_HELP_QMASK_INVERT
define|#
directive|define
name|GIMP_HELP_QMASK_INVERT
value|"select/quickmask.html"
end_define

begin_define
DECL|macro|GIMP_HELP_QMASK_EDIT
define|#
directive|define
name|GIMP_HELP_QMASK_EDIT
value|"dialogs/edit_qmask_attributes.html"
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
DECL|macro|GIMP_HELP_PATH_RAISE_TO_TOP
define|#
directive|define
name|GIMP_HELP_PATH_RAISE_TO_TOP
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
DECL|macro|GIMP_HELP_PATH_LOWER_TO_BOTTOM
define|#
directive|define
name|GIMP_HELP_PATH_LOWER_TO_BOTTOM
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
DECL|macro|GIMP_HELP_PATH_SELECTION_REPLACE
define|#
directive|define
name|GIMP_HELP_PATH_SELECTION_REPLACE
value|"paths/path_to_selection.html"
end_define

begin_define
DECL|macro|GIMP_HELP_PATH_SELECTION_ADD
define|#
directive|define
name|GIMP_HELP_PATH_SELECTION_ADD
value|"paths/path_to_selection.html#add"
end_define

begin_define
DECL|macro|GIMP_HELP_PATH_SELECTION_SUBTRACT
define|#
directive|define
name|GIMP_HELP_PATH_SELECTION_SUBTRACT
value|"paths/path_to_selection.html#subtract"
end_define

begin_define
DECL|macro|GIMP_HELP_PATH_SELECTION_INTERSECT
define|#
directive|define
name|GIMP_HELP_PATH_SELECTION_INTERSECT
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
value|"dialogs/import_path.html"
end_define

begin_define
DECL|macro|GIMP_HELP_PATH_EXPORT
define|#
directive|define
name|GIMP_HELP_PATH_EXPORT
value|"dialogs/export_path.html"
end_define

begin_define
DECL|macro|GIMP_HELP_PATH_EDIT
define|#
directive|define
name|GIMP_HELP_PATH_EDIT
value|"dialogs/edit_path_attributes.html"
end_define

begin_define
DECL|macro|GIMP_HELP_TOOL_DIALOG
define|#
directive|define
name|GIMP_HELP_TOOL_DIALOG
value|"dialogs/tools.html"
end_define

begin_define
DECL|macro|GIMP_HELP_TOOL_AIRBRUSH
define|#
directive|define
name|GIMP_HELP_TOOL_AIRBRUSH
value|"tools/airbrush.html"
end_define

begin_define
DECL|macro|GIMP_HELP_TOOL_BLEND
define|#
directive|define
name|GIMP_HELP_TOOL_BLEND
value|"tools/blend.html"
end_define

begin_define
DECL|macro|GIMP_HELP_TOOL_BRIGHTNESS_CONTRAST
define|#
directive|define
name|GIMP_HELP_TOOL_BRIGHTNESS_CONTRAST
value|"tools/brightness-contrast.html"
end_define

begin_define
DECL|macro|GIMP_HELP_TOOL_BUCKET_FILL
define|#
directive|define
name|GIMP_HELP_TOOL_BUCKET_FILL
value|"tools/bucket_fill.html"
end_define

begin_define
DECL|macro|GIMP_HELP_TOOL_BY_COLOR_SELECT
define|#
directive|define
name|GIMP_HELP_TOOL_BY_COLOR_SELECT
value|"tools/by_color_select.html"
end_define

begin_define
DECL|macro|GIMP_HELP_TOOL_CLONE
define|#
directive|define
name|GIMP_HELP_TOOL_CLONE
value|"tools/clone.html"
end_define

begin_define
DECL|macro|GIMP_HELP_TOOL_COLORIZE
define|#
directive|define
name|GIMP_HELP_TOOL_COLORIZE
value|"tools/colorize.html"
end_define

begin_define
DECL|macro|GIMP_HELP_TOOL_COLOR_BALANCE
define|#
directive|define
name|GIMP_HELP_TOOL_COLOR_BALANCE
value|"tools/color_balance.html"
end_define

begin_define
DECL|macro|GIMP_HELP_TOOL_COLOR_PICKER
define|#
directive|define
name|GIMP_HELP_TOOL_COLOR_PICKER
value|"tools/color_picker.html"
end_define

begin_define
DECL|macro|GIMP_HELP_TOOL_CONVOLVE
define|#
directive|define
name|GIMP_HELP_TOOL_CONVOLVE
value|"tools/convolve.html"
end_define

begin_define
DECL|macro|GIMP_HELP_TOOL_CROP
define|#
directive|define
name|GIMP_HELP_TOOL_CROP
value|"tools/crop.html"
end_define

begin_define
DECL|macro|GIMP_HELP_TOOL_CURVES
define|#
directive|define
name|GIMP_HELP_TOOL_CURVES
value|"tools/curves.html"
end_define

begin_define
DECL|macro|GIMP_HELP_TOOL_CURVES
define|#
directive|define
name|GIMP_HELP_TOOL_CURVES
value|"tools/curves.html"
end_define

begin_define
DECL|macro|GIMP_HELP_TOOL_DODGE_BURN
define|#
directive|define
name|GIMP_HELP_TOOL_DODGE_BURN
value|"tools/dodge_burn.html"
end_define

begin_define
DECL|macro|GIMP_HELP_TOOL_ELLIPSE_SELECT
define|#
directive|define
name|GIMP_HELP_TOOL_ELLIPSE_SELECT
value|"tools/ellipse_select.html"
end_define

begin_define
DECL|macro|GIMP_HELP_TOOL_ERASER
define|#
directive|define
name|GIMP_HELP_TOOL_ERASER
value|"tools/eraser.html"
end_define

begin_define
DECL|macro|GIMP_HELP_TOOL_FLIP
define|#
directive|define
name|GIMP_HELP_TOOL_FLIP
value|"tools/flip.html"
end_define

begin_define
DECL|macro|GIMP_HELP_TOOL_FREE_SELECT
define|#
directive|define
name|GIMP_HELP_TOOL_FREE_SELECT
value|"tools/free_select.html"
end_define

begin_define
DECL|macro|GIMP_HELP_TOOL_FUZZY_SELECT
define|#
directive|define
name|GIMP_HELP_TOOL_FUZZY_SELECT
value|"tools/fuzzy_select.html"
end_define

begin_define
DECL|macro|GIMP_HELP_TOOL_HISTOGRAM
define|#
directive|define
name|GIMP_HELP_TOOL_HISTOGRAM
value|"tools/histogram.html"
end_define

begin_define
DECL|macro|GIMP_HELP_TOOL_HUE_SATURATION
define|#
directive|define
name|GIMP_HELP_TOOL_HUE_SATURATION
value|"tools/hue_saturation.html"
end_define

begin_define
DECL|macro|GIMP_HELP_TOOL_INK
define|#
directive|define
name|GIMP_HELP_TOOL_INK
value|"tools/ink.html"
end_define

begin_define
DECL|macro|GIMP_HELP_TOOL_ISCISSORS
define|#
directive|define
name|GIMP_HELP_TOOL_ISCISSORS
value|"tools/iscissors.html"
end_define

begin_define
DECL|macro|GIMP_HELP_TOOL_LEVELS
define|#
directive|define
name|GIMP_HELP_TOOL_LEVELS
value|"tools/levels.html"
end_define

begin_define
DECL|macro|GIMP_HELP_TOOL_MEASURE
define|#
directive|define
name|GIMP_HELP_TOOL_MEASURE
value|"tools/measure.html"
end_define

begin_define
DECL|macro|GIMP_HELP_TOOL_MOVE
define|#
directive|define
name|GIMP_HELP_TOOL_MOVE
value|"tools/move.html"
end_define

begin_define
DECL|macro|GIMP_HELP_TOOL_PATH
define|#
directive|define
name|GIMP_HELP_TOOL_PATH
value|"tools/path.html"
end_define

begin_define
DECL|macro|GIMP_HELP_TOOL_PAINTBRUSH
define|#
directive|define
name|GIMP_HELP_TOOL_PAINTBRUSH
value|"tools/paintbrush.html"
end_define

begin_define
DECL|macro|GIMP_HELP_TOOL_PENCIL
define|#
directive|define
name|GIMP_HELP_TOOL_PENCIL
value|"tools/pencil.html"
end_define

begin_define
DECL|macro|GIMP_HELP_TOOL_PERSPECTIVE
define|#
directive|define
name|GIMP_HELP_TOOL_PERSPECTIVE
value|"tools/perspective.html"
end_define

begin_define
DECL|macro|GIMP_HELP_TOOL_POSTERIZE
define|#
directive|define
name|GIMP_HELP_TOOL_POSTERIZE
value|"tools/posterize.html"
end_define

begin_define
DECL|macro|GIMP_HELP_TOOL_RECT_SELECT
define|#
directive|define
name|GIMP_HELP_TOOL_RECT_SELECT
value|"tools/rect_select.html"
end_define

begin_define
DECL|macro|GIMP_HELP_TOOL_ROTATE
define|#
directive|define
name|GIMP_HELP_TOOL_ROTATE
value|"tools/rotate.html"
end_define

begin_define
DECL|macro|GIMP_HELP_TOOL_SCALE
define|#
directive|define
name|GIMP_HELP_TOOL_SCALE
value|"tools/scale.html"
end_define

begin_define
DECL|macro|GIMP_HELP_TOOL_SHEAR
define|#
directive|define
name|GIMP_HELP_TOOL_SHEAR
value|"tools/shear.html"
end_define

begin_define
DECL|macro|GIMP_HELP_TOOL_SMUDGE
define|#
directive|define
name|GIMP_HELP_TOOL_SMUDGE
value|"tools/smudge.html"
end_define

begin_define
DECL|macro|GIMP_HELP_TOOL_TEXT
define|#
directive|define
name|GIMP_HELP_TOOL_TEXT
value|"tools/text.html"
end_define

begin_define
DECL|macro|GIMP_HELP_TOOL_THRESHOLD
define|#
directive|define
name|GIMP_HELP_TOOL_THRESHOLD
value|"tools/threshold.html"
end_define

begin_define
DECL|macro|GIMP_HELP_TOOL_VECTORS
define|#
directive|define
name|GIMP_HELP_TOOL_VECTORS
value|"tools/vectors.html"
end_define

begin_define
DECL|macro|GIMP_HELP_TOOL_ZOOM
define|#
directive|define
name|GIMP_HELP_TOOL_ZOOM
value|"tools/zoom.html"
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
DECL|macro|GIMP_HELP_BRUSH_EDITOR_DIALOG
define|#
directive|define
name|GIMP_HELP_BRUSH_EDITOR_DIALOG
value|"dialogs/brush_editor.html"
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
DECL|macro|GIMP_HELP_GRADIENT_EDITOR_DIALOG
define|#
directive|define
name|GIMP_HELP_GRADIENT_EDITOR_DIALOG
value|"dialogs/gradient_editor/gradient_editor.html"
end_define

begin_define
DECL|macro|GIMP_HELP_GRADIENT_EDITOR_LEFT_COLOR
define|#
directive|define
name|GIMP_HELP_GRADIENT_EDITOR_LEFT_COLOR
value|"dialogs/gradient_editor/gradient_editor.html"
end_define

begin_define
DECL|macro|GIMP_HELP_GRADIENT_EDITOR_LEFT_LOAD
define|#
directive|define
name|GIMP_HELP_GRADIENT_EDITOR_LEFT_LOAD
value|"dialogs/gradient_editor/gradient_editor.html"
end_define

begin_define
DECL|macro|GIMP_HELP_GRADIENT_EDITOR_LEFT_SAVE
define|#
directive|define
name|GIMP_HELP_GRADIENT_EDITOR_LEFT_SAVE
value|"dialogs/gradient_editor/gradient_editor.html"
end_define

begin_define
DECL|macro|GIMP_HELP_GRADIENT_EDITOR_RIGHT_COLOR
define|#
directive|define
name|GIMP_HELP_GRADIENT_EDITOR_RIGHT_COLOR
value|"dialogs/gradient_editor/gradient_editor.html"
end_define

begin_define
DECL|macro|GIMP_HELP_GRADIENT_EDITOR_RIGHT_LOAD
define|#
directive|define
name|GIMP_HELP_GRADIENT_EDITOR_RIGHT_LOAD
value|"dialogs/gradient_editor/gradient_editor.html"
end_define

begin_define
DECL|macro|GIMP_HELP_GRADIENT_EDITOR_RIGHT_SAVE
define|#
directive|define
name|GIMP_HELP_GRADIENT_EDITOR_RIGHT_SAVE
value|"dialogs/gradient_editor/gradient_editor.html"
end_define

begin_define
DECL|macro|GIMP_HELP_GRADIENT_EDITOR_BLENDING
define|#
directive|define
name|GIMP_HELP_GRADIENT_EDITOR_BLENDING
value|"dialogs/gradient_editor/gradient_editor.html"
end_define

begin_define
DECL|macro|GIMP_HELP_GRADIENT_EDITOR_COLORING
define|#
directive|define
name|GIMP_HELP_GRADIENT_EDITOR_COLORING
value|"dialogs/gradient_editor/gradient_editor.html"
end_define

begin_define
DECL|macro|GIMP_HELP_GRADIENT_EDITOR_FLIP
define|#
directive|define
name|GIMP_HELP_GRADIENT_EDITOR_FLIP
value|"dialogs/gradient_editor/gradient_editor.html"
end_define

begin_define
DECL|macro|GIMP_HELP_GRADIENT_EDITOR_REPLICATE
define|#
directive|define
name|GIMP_HELP_GRADIENT_EDITOR_REPLICATE
value|"dialogs/gradient_editor/replicate_segment.html"
end_define

begin_define
DECL|macro|GIMP_HELP_GRADIENT_EDITOR_SPLIT_MIDPOINT
define|#
directive|define
name|GIMP_HELP_GRADIENT_EDITOR_SPLIT_MIDPOINT
value|"dialogs/gradient_editor/gradient_editor.html"
end_define

begin_define
DECL|macro|GIMP_HELP_GRADIENT_EDITOR_SPLIT_UNIFORM
define|#
directive|define
name|GIMP_HELP_GRADIENT_EDITOR_SPLIT_UNIFORM
value|"dialogs/gradient_editor/split_segments_uniformly.html"
end_define

begin_define
DECL|macro|GIMP_HELP_GRADIENT_EDITOR_DELETE
define|#
directive|define
name|GIMP_HELP_GRADIENT_EDITOR_DELETE
value|"dialogs/gradient_editor/gradient_editor.html"
end_define

begin_define
DECL|macro|GIMP_HELP_GRADIENT_EDITOR_RECENTER
define|#
directive|define
name|GIMP_HELP_GRADIENT_EDITOR_RECENTER
value|"dialogs/gradient_editor/gradient_editor.html"
end_define

begin_define
DECL|macro|GIMP_HELP_GRADIENT_EDITOR_REDISTRIBUTE
define|#
directive|define
name|GIMP_HELP_GRADIENT_EDITOR_REDISTRIBUTE
value|"dialogs/gradient_editor/gradient_editor.html"
end_define

begin_define
DECL|macro|GIMP_HELP_GRADIENT_EDITOR_BLEND_COLOR
define|#
directive|define
name|GIMP_HELP_GRADIENT_EDITOR_BLEND_COLOR
value|"dialogs/gradient_editor/gradient_editor.html"
end_define

begin_define
DECL|macro|GIMP_HELP_GRADIENT_EDITOR_BLEND_OPACITY
define|#
directive|define
name|GIMP_HELP_GRADIENT_EDITOR_BLEND_OPACITY
value|"dialogs/gradient_editor/gradient_editor.html"
end_define

begin_define
DECL|macro|GIMP_HELP_GRADIENT_EDITOR_ZOOM_OUT
define|#
directive|define
name|GIMP_HELP_GRADIENT_EDITOR_ZOOM_OUT
value|"dialogs/gradient_editor/gradient_editor.html"
end_define

begin_define
DECL|macro|GIMP_HELP_GRADIENT_EDITOR_ZOOM_IN
define|#
directive|define
name|GIMP_HELP_GRADIENT_EDITOR_ZOOM_IN
value|"dialogs/gradient_editor/gradient_editor.html"
end_define

begin_define
DECL|macro|GIMP_HELP_GRADIENT_EDITOR_ZOOM_ALL
define|#
directive|define
name|GIMP_HELP_GRADIENT_EDITOR_ZOOM_ALL
value|"dialogs/gradient_editor/gradient_editor.html"
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
DECL|macro|GIMP_HELP_PALETTE_EDITOR_DIALOG
define|#
directive|define
name|GIMP_HELP_PALETTE_EDITOR_DIALOG
value|"dialogs/palette_selection.html"
end_define

begin_define
DECL|macro|GIMP_HELP_PALETTE_EDITOR_NEW
define|#
directive|define
name|GIMP_HELP_PALETTE_EDITOR_NEW
value|"dialogs/palette_selection.html"
end_define

begin_define
DECL|macro|GIMP_HELP_PALETTE_EDITOR_EDIT
define|#
directive|define
name|GIMP_HELP_PALETTE_EDITOR_EDIT
value|"dialogs/palette_selection.html"
end_define

begin_define
DECL|macro|GIMP_HELP_PALETTE_EDITOR_DELETE
define|#
directive|define
name|GIMP_HELP_PALETTE_EDITOR_DELETE
value|"dialogs/palette_selection.html"
end_define

begin_define
DECL|macro|GIMP_HELP_PALETTE_EDITOR_ZOOM_OUT
define|#
directive|define
name|GIMP_HELP_PALETTE_EDITOR_ZOOM_OUT
value|"dialogs/palette_selection.html"
end_define

begin_define
DECL|macro|GIMP_HELP_PALETTE_EDITOR_ZOOM_IN
define|#
directive|define
name|GIMP_HELP_PALETTE_EDITOR_ZOOM_IN
value|"dialogs/palette_selection.html"
end_define

begin_define
DECL|macro|GIMP_HELP_PALETTE_EDITOR_ZOOM_ALL
define|#
directive|define
name|GIMP_HELP_PALETTE_EDITOR_ZOOM_ALL
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
DECL|macro|GIMP_HELP_DOCUMENT_DIALOG
define|#
directive|define
name|GIMP_HELP_DOCUMENT_DIALOG
value|"dialogs/document_index.html"
end_define

begin_define
DECL|macro|GIMP_HELP_DOCUMENT_OPEN
define|#
directive|define
name|GIMP_HELP_DOCUMENT_OPEN
value|"dialogs/document_index.html"
end_define

begin_define
DECL|macro|GIMP_HELP_DOCUMENT_REMOVE
define|#
directive|define
name|GIMP_HELP_DOCUMENT_REMOVE
value|"dialogs/document_index.html"
end_define

begin_define
DECL|macro|GIMP_HELP_DOCUMENT_REFRESH
define|#
directive|define
name|GIMP_HELP_DOCUMENT_REFRESH
value|"dialogs/document_index.html"
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
DECL|macro|GIMP_HELP_TOOL_OPTIONS_DIALOG
define|#
directive|define
name|GIMP_HELP_TOOL_OPTIONS_DIALOG
value|"dialogs/tool_options.html"
end_define

begin_define
DECL|macro|GIMP_HELP_TOOL_OPTIONS_RESET
define|#
directive|define
name|GIMP_HELP_TOOL_OPTIONS_RESET
value|"dialogs/tool_options.html"
end_define

begin_define
DECL|macro|GIMP_HELP_ERRORS_DIALOG
define|#
directive|define
name|GIMP_HELP_ERRORS_DIALOG
value|"dialogs/error_console.html"
end_define

begin_define
DECL|macro|GIMP_HELP_ERRORS_CLEAR
define|#
directive|define
name|GIMP_HELP_ERRORS_CLEAR
value|"dialogs/error_console.html"
end_define

begin_define
DECL|macro|GIMP_HELP_ERRORS_SAVE
define|#
directive|define
name|GIMP_HELP_ERRORS_SAVE
value|"dialogs/error_console.html"
end_define

begin_define
DECL|macro|GIMP_HELP_PREFS_DIALOG
define|#
directive|define
name|GIMP_HELP_PREFS_DIALOG
value|"dialogs/preferences/preferences.html"
end_define

begin_define
DECL|macro|GIMP_HELP_PREFS_NEW_IMAGE
define|#
directive|define
name|GIMP_HELP_PREFS_NEW_IMAGE
value|"dialogs/preferences/new_file.html"
end_define

begin_define
DECL|macro|GIMP_HELP_PREFS_NEW_IMAGE_COMMENT
define|#
directive|define
name|GIMP_HELP_PREFS_NEW_IMAGE_COMMENT
value|"dialogs/preferences/new_file.html#default_comment"
end_define

begin_define
DECL|macro|GIMP_HELP_PREFS_INTERFACE
define|#
directive|define
name|GIMP_HELP_PREFS_INTERFACE
value|"dialogs/preferences/interface.html"
end_define

begin_define
DECL|macro|GIMP_HELP_PREFS_HELP
define|#
directive|define
name|GIMP_HELP_PREFS_HELP
value|"dialogs/preferences/interface.html#help_system"
end_define

begin_define
DECL|macro|GIMP_HELP_PREFS_TOOL_OPTIONS
define|#
directive|define
name|GIMP_HELP_PREFS_TOOL_OPTIONS
value|"dialogs/preferences/interface.html#tool_options"
end_define

begin_define
DECL|macro|GIMP_HELP_PREFS_INPUT_DEVICES
define|#
directive|define
name|GIMP_HELP_PREFS_INPUT_DEVICES
value|"dialogs/preferences/input_devices.html"
end_define

begin_define
DECL|macro|GIMP_HELP_PREFS_IMAGE_WINDOW
define|#
directive|define
name|GIMP_HELP_PREFS_IMAGE_WINDOW
value|"dialogs/preferences/interface.html#image_windows"
end_define

begin_define
DECL|macro|GIMP_HELP_PREFS_IMAGE_WINDOW_APPEARANCE
define|#
directive|define
name|GIMP_HELP_PREFS_IMAGE_WINDOW_APPEARANCE
value|"dialogs/preferences/interface.html#image_windows"
end_define

begin_define
DECL|macro|GIMP_HELP_PREFS_IMAGE_WINDOW_TITLE
define|#
directive|define
name|GIMP_HELP_PREFS_IMAGE_WINDOW_TITLE
value|"dialogs/preferences/interface.html#image_windows"
end_define

begin_define
DECL|macro|GIMP_HELP_PREFS_DISPLAY
define|#
directive|define
name|GIMP_HELP_PREFS_DISPLAY
value|"dialogs/preferences/display.html"
end_define

begin_define
DECL|macro|GIMP_HELP_PREFS_MONITOR
define|#
directive|define
name|GIMP_HELP_PREFS_MONITOR
value|"dialogs/preferences/monitor.html"
end_define

begin_define
DECL|macro|GIMP_HELP_PREFS_ENVIRONMENT
define|#
directive|define
name|GIMP_HELP_PREFS_ENVIRONMENT
value|"dialogs/preferences/environment.html"
end_define

begin_define
DECL|macro|GIMP_HELP_PREFS_FOLDERS
define|#
directive|define
name|GIMP_HELP_PREFS_FOLDERS
value|"dialogs/preferences/folders.html"
end_define

begin_define
DECL|macro|GIMP_HELP_PREFS_FOLDERS_BRUSHES
define|#
directive|define
name|GIMP_HELP_PREFS_FOLDERS_BRUSHES
value|"dialogs/preferences/folders.html#brushes"
end_define

begin_define
DECL|macro|GIMP_HELP_PREFS_FOLDERS_PATTERNS
define|#
directive|define
name|GIMP_HELP_PREFS_FOLDERS_PATTERNS
value|"dialogs/preferences/folders.html#patterns"
end_define

begin_define
DECL|macro|GIMP_HELP_PREFS_FOLDERS_PALETTES
define|#
directive|define
name|GIMP_HELP_PREFS_FOLDERS_PALETTES
value|"dialogs/preferences/folders.html#palettes"
end_define

begin_define
DECL|macro|GIMP_HELP_PREFS_FOLDERS_GRADIENTS
define|#
directive|define
name|GIMP_HELP_PREFS_FOLDERS_GRADIENTS
value|"dialogs/preferences/folders.html#gradients"
end_define

begin_define
DECL|macro|GIMP_HELP_PREFS_FOLDERS_PLUG_INS
define|#
directive|define
name|GIMP_HELP_PREFS_FOLDERS_PLUG_INS
value|"dialogs/preferences/folders.html#plug_ins"
end_define

begin_define
DECL|macro|GIMP_HELP_PREFS_FOLDERS_SCRIPTS
define|#
directive|define
name|GIMP_HELP_PREFS_FOLDERS_SCRIPTS
value|"dialogs/preferences/folders.html#scripts"
end_define

begin_define
DECL|macro|GIMP_HELP_PREFS_FOLDERS_MODULES
define|#
directive|define
name|GIMP_HELP_PREFS_FOLDERS_MODULES
value|"dialogs/preferences/folders.html#modules"
end_define

begin_define
DECL|macro|GIMP_HELP_PREFS_FOLDERS_ENVIRONMENT
define|#
directive|define
name|GIMP_HELP_PREFS_FOLDERS_ENVIRONMENT
value|"dialogs/preferences/folders.html#environ"
end_define

begin_define
DECL|macro|GIMP_HELP_PREFS_FOLDERS_THEMES
define|#
directive|define
name|GIMP_HELP_PREFS_FOLDERS_THEMES
value|"dialogs/preferences/folders.html#themes"
end_define

begin_define
DECL|macro|GIMP_HELP_COLOR_DIALOG
define|#
directive|define
name|GIMP_HELP_COLOR_DIALOG
value|"dialogs/color.html"
end_define

begin_define
DECL|macro|GIMP_HELP_DEVICE_STATUS_DIALOG
define|#
directive|define
name|GIMP_HELP_DEVICE_STATUS_DIALOG
value|"dialogs/device_status.html"
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
value|"dialogs/info_window.html"
end_define

begin_define
DECL|macro|GIMP_HELP_NAVIGATION_DIALOG
define|#
directive|define
name|GIMP_HELP_NAVIGATION_DIALOG
value|"dialogs/navigation_window.html"
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
DECL|macro|GIMP_HELP_TEXT_EDITOR_DIALOG
define|#
directive|define
name|GIMP_HELP_TEXT_EDITOR_DIALOG
value|"dialogs/text_editor.html"
end_define

begin_define
DECL|macro|GIMP_HELP_TIPS_DIALOG
define|#
directive|define
name|GIMP_HELP_TIPS_DIALOG
value|"dialogs/tip_of_the_day.html"
end_define

begin_define
DECL|macro|GIMP_HELP_ABOUT_DIALOG
define|#
directive|define
name|GIMP_HELP_ABOUT_DIALOG
value|"dialogs/about.html"
end_define

begin_define
DECL|macro|GIMP_HELP_HELP
define|#
directive|define
name|GIMP_HELP_HELP
value|"dialogs/help.html"
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

