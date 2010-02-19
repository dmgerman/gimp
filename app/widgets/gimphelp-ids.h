begin_unit|revision:0.9.5;language:C;cregit-version:0.0.1
begin_comment
comment|/* GIMP - The GNU Image Manipulation Program  * Copyright (C) 1995 Spencer Kimball and Peter Mattis  *  * gimphelp-ids.h  * Copyright (C) 2003 Michael Natterer<mitch@gimp.org>  *  * This program is free software: you can redistribute it and/or modify  * it under the terms of the GNU General Public License as published by  * the Free Software Foundation; either version 3 of the License, or  * (at your option) any later version.  *  * This program is distributed in the hope that it will be useful,  * but WITHOUT ANY WARRANTY; without even the implied warranty of  * MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the  * GNU General Public License for more details.  *  * You should have received a copy of the GNU General Public License  * along with this program.  If not, see<http://www.gnu.org/licenses/>.  */
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
value|"gimp-main"
end_define

begin_define
DECL|macro|GIMP_HELP_FILE_NEW
define|#
directive|define
name|GIMP_HELP_FILE_NEW
value|"gimp-file-new"
end_define

begin_define
DECL|macro|GIMP_HELP_FILE_OPEN
define|#
directive|define
name|GIMP_HELP_FILE_OPEN
value|"gimp-file-open"
end_define

begin_define
DECL|macro|GIMP_HELP_FILE_OPEN_AS_LAYER
define|#
directive|define
name|GIMP_HELP_FILE_OPEN_AS_LAYER
value|"gimp-file-open-as-layer"
end_define

begin_define
DECL|macro|GIMP_HELP_FILE_OPEN_LOCATION
define|#
directive|define
name|GIMP_HELP_FILE_OPEN_LOCATION
value|"gimp-file-open-location"
end_define

begin_define
DECL|macro|GIMP_HELP_FILE_OPEN_BY_EXTENSION
define|#
directive|define
name|GIMP_HELP_FILE_OPEN_BY_EXTENSION
value|"gimp-file-open-by-extension"
end_define

begin_define
DECL|macro|GIMP_HELP_FILE_OPEN_RECENT
define|#
directive|define
name|GIMP_HELP_FILE_OPEN_RECENT
value|"gimp-file-open-recent"
end_define

begin_define
DECL|macro|GIMP_HELP_FILE_SAVE
define|#
directive|define
name|GIMP_HELP_FILE_SAVE
value|"gimp-file-save"
end_define

begin_define
DECL|macro|GIMP_HELP_FILE_SAVE_AS
define|#
directive|define
name|GIMP_HELP_FILE_SAVE_AS
value|"gimp-file-save-as"
end_define

begin_define
DECL|macro|GIMP_HELP_FILE_SAVE_A_COPY
define|#
directive|define
name|GIMP_HELP_FILE_SAVE_A_COPY
value|"gimp-file-save-a-copy"
end_define

begin_define
DECL|macro|GIMP_HELP_FILE_SAVE_BY_EXTENSION
define|#
directive|define
name|GIMP_HELP_FILE_SAVE_BY_EXTENSION
value|"gimp-file-save-by-extension"
end_define

begin_define
DECL|macro|GIMP_HELP_FILE_EXPORT
define|#
directive|define
name|GIMP_HELP_FILE_EXPORT
value|"gimp-file-export"
end_define

begin_define
DECL|macro|GIMP_HELP_FILE_EXPORT_TO
define|#
directive|define
name|GIMP_HELP_FILE_EXPORT_TO
value|"gimp-file-export-to"
end_define

begin_define
DECL|macro|GIMP_HELP_FILE_OVERWRITE
define|#
directive|define
name|GIMP_HELP_FILE_OVERWRITE
value|"gimp-file-overwrite"
end_define

begin_define
DECL|macro|GIMP_HELP_FILE_SAVE_AS_TEMPLATE
define|#
directive|define
name|GIMP_HELP_FILE_SAVE_AS_TEMPLATE
value|"gimp-file-save-as-template"
end_define

begin_define
DECL|macro|GIMP_HELP_FILE_REVERT
define|#
directive|define
name|GIMP_HELP_FILE_REVERT
value|"gimp-file-revert"
end_define

begin_define
DECL|macro|GIMP_HELP_FILE_CLOSE
define|#
directive|define
name|GIMP_HELP_FILE_CLOSE
value|"gimp-file-close"
end_define

begin_define
DECL|macro|GIMP_HELP_FILE_CLOSE_ALL
define|#
directive|define
name|GIMP_HELP_FILE_CLOSE_ALL
value|"gimp-file-close-all"
end_define

begin_define
DECL|macro|GIMP_HELP_FILE_CREATE_TEMPLATE
define|#
directive|define
name|GIMP_HELP_FILE_CREATE_TEMPLATE
value|"gimp-file-save-as-template"
end_define

begin_comment
DECL|macro|GIMP_HELP_FILE_CREATE_TEMPLATE
comment|/* Update string along with gimp-help-2 */
end_comment

begin_define
DECL|macro|GIMP_HELP_FILE_QUIT
define|#
directive|define
name|GIMP_HELP_FILE_QUIT
value|"gimp-file-quit"
end_define

begin_define
DECL|macro|GIMP_HELP_EDIT_UNDO
define|#
directive|define
name|GIMP_HELP_EDIT_UNDO
value|"gimp-edit-undo"
end_define

begin_define
DECL|macro|GIMP_HELP_EDIT_REDO
define|#
directive|define
name|GIMP_HELP_EDIT_REDO
value|"gimp-edit-redo"
end_define

begin_define
DECL|macro|GIMP_HELP_EDIT_STRONG_UNDO
define|#
directive|define
name|GIMP_HELP_EDIT_STRONG_UNDO
value|"gimp-edit-strong-undo"
end_define

begin_define
DECL|macro|GIMP_HELP_EDIT_STRONG_REDO
define|#
directive|define
name|GIMP_HELP_EDIT_STRONG_REDO
value|"gimp-edit-strong-redo"
end_define

begin_define
DECL|macro|GIMP_HELP_EDIT_UNDO_CLEAR
define|#
directive|define
name|GIMP_HELP_EDIT_UNDO_CLEAR
value|"gimp-edit-undo-clear"
end_define

begin_define
DECL|macro|GIMP_HELP_EDIT_FADE
define|#
directive|define
name|GIMP_HELP_EDIT_FADE
value|"gimp-edit-fade"
end_define

begin_define
DECL|macro|GIMP_HELP_EDIT_CUT
define|#
directive|define
name|GIMP_HELP_EDIT_CUT
value|"gimp-edit-cut"
end_define

begin_define
DECL|macro|GIMP_HELP_EDIT_COPY
define|#
directive|define
name|GIMP_HELP_EDIT_COPY
value|"gimp-edit-copy"
end_define

begin_define
DECL|macro|GIMP_HELP_EDIT_COPY_VISIBLE
define|#
directive|define
name|GIMP_HELP_EDIT_COPY_VISIBLE
value|"gimp-edit-copy-visible"
end_define

begin_define
DECL|macro|GIMP_HELP_EDIT_PASTE
define|#
directive|define
name|GIMP_HELP_EDIT_PASTE
value|"gimp-edit-paste"
end_define

begin_define
DECL|macro|GIMP_HELP_EDIT_PASTE_INTO
define|#
directive|define
name|GIMP_HELP_EDIT_PASTE_INTO
value|"gimp-edit-paste-into"
end_define

begin_define
DECL|macro|GIMP_HELP_EDIT_PASTE_AS_NEW
define|#
directive|define
name|GIMP_HELP_EDIT_PASTE_AS_NEW
value|"gimp-edit-paste-as-new"
end_define

begin_define
DECL|macro|GIMP_HELP_EDIT_PASTE_AS_NEW_LAYER
define|#
directive|define
name|GIMP_HELP_EDIT_PASTE_AS_NEW_LAYER
value|"gimp-edit-paste-as-new-layer"
end_define

begin_define
DECL|macro|GIMP_HELP_EDIT_CLEAR
define|#
directive|define
name|GIMP_HELP_EDIT_CLEAR
value|"gimp-edit-clear"
end_define

begin_define
DECL|macro|GIMP_HELP_EDIT_FILL_FG
define|#
directive|define
name|GIMP_HELP_EDIT_FILL_FG
value|"gimp-edit-fill-fg"
end_define

begin_define
DECL|macro|GIMP_HELP_EDIT_FILL_BG
define|#
directive|define
name|GIMP_HELP_EDIT_FILL_BG
value|"gimp-edit-fill-bg"
end_define

begin_define
DECL|macro|GIMP_HELP_EDIT_FILL_PATTERN
define|#
directive|define
name|GIMP_HELP_EDIT_FILL_PATTERN
value|"gimp-edit-fill-pattern"
end_define

begin_define
DECL|macro|GIMP_HELP_SELECTION_DIALOG
define|#
directive|define
name|GIMP_HELP_SELECTION_DIALOG
value|"gimp-selection-dialog"
end_define

begin_define
DECL|macro|GIMP_HELP_SELECTION_ALL
define|#
directive|define
name|GIMP_HELP_SELECTION_ALL
value|"gimp-selection-all"
end_define

begin_define
DECL|macro|GIMP_HELP_SELECTION_NONE
define|#
directive|define
name|GIMP_HELP_SELECTION_NONE
value|"gimp-selection-none"
end_define

begin_define
DECL|macro|GIMP_HELP_SELECTION_INVERT
define|#
directive|define
name|GIMP_HELP_SELECTION_INVERT
value|"gimp-selection-invert"
end_define

begin_define
DECL|macro|GIMP_HELP_SELECTION_FLOAT
define|#
directive|define
name|GIMP_HELP_SELECTION_FLOAT
value|"gimp-selection-float"
end_define

begin_define
DECL|macro|GIMP_HELP_SELECTION_FEATHER
define|#
directive|define
name|GIMP_HELP_SELECTION_FEATHER
value|"gimp-selection-feather"
end_define

begin_define
DECL|macro|GIMP_HELP_SELECTION_SHARPEN
define|#
directive|define
name|GIMP_HELP_SELECTION_SHARPEN
value|"gimp-selection-sharpen"
end_define

begin_define
DECL|macro|GIMP_HELP_SELECTION_SHRINK
define|#
directive|define
name|GIMP_HELP_SELECTION_SHRINK
value|"gimp-selection-shrink"
end_define

begin_define
DECL|macro|GIMP_HELP_SELECTION_GROW
define|#
directive|define
name|GIMP_HELP_SELECTION_GROW
value|"gimp-selection-grow"
end_define

begin_define
DECL|macro|GIMP_HELP_SELECTION_BORDER
define|#
directive|define
name|GIMP_HELP_SELECTION_BORDER
value|"gimp-selection-border"
end_define

begin_define
DECL|macro|GIMP_HELP_SELECTION_STROKE
define|#
directive|define
name|GIMP_HELP_SELECTION_STROKE
value|"gimp-selection-stroke"
end_define

begin_define
DECL|macro|GIMP_HELP_SELECTION_TO_CHANNEL
define|#
directive|define
name|GIMP_HELP_SELECTION_TO_CHANNEL
value|"gimp-selection-to-channel"
end_define

begin_define
DECL|macro|GIMP_HELP_SELECTION_TO_PATH
define|#
directive|define
name|GIMP_HELP_SELECTION_TO_PATH
value|"gimp-selection-to-path"
end_define

begin_define
DECL|macro|GIMP_HELP_VIEW_NEW
define|#
directive|define
name|GIMP_HELP_VIEW_NEW
value|"gimp-view-new"
end_define

begin_define
DECL|macro|GIMP_HELP_VIEW_DOT_FOR_DOT
define|#
directive|define
name|GIMP_HELP_VIEW_DOT_FOR_DOT
value|"gimp-view-dot-for-dot"
end_define

begin_define
DECL|macro|GIMP_HELP_VIEW_ZOOM_REVERT
define|#
directive|define
name|GIMP_HELP_VIEW_ZOOM_REVERT
value|"gimp-view-zoom-revert"
end_define

begin_define
DECL|macro|GIMP_HELP_VIEW_ZOOM_OUT
define|#
directive|define
name|GIMP_HELP_VIEW_ZOOM_OUT
value|"gimp-view-zoom-out"
end_define

begin_define
DECL|macro|GIMP_HELP_VIEW_ZOOM_IN
define|#
directive|define
name|GIMP_HELP_VIEW_ZOOM_IN
value|"gimp-view-zoom-in"
end_define

begin_define
DECL|macro|GIMP_HELP_VIEW_ZOOM_100
define|#
directive|define
name|GIMP_HELP_VIEW_ZOOM_100
value|"gimp-view-zoom-100"
end_define

begin_define
DECL|macro|GIMP_HELP_VIEW_ZOOM_FIT_IN
define|#
directive|define
name|GIMP_HELP_VIEW_ZOOM_FIT_IN
value|"gimp-view-zoom-fit-in"
end_define

begin_define
DECL|macro|GIMP_HELP_VIEW_ZOOM_FILL
define|#
directive|define
name|GIMP_HELP_VIEW_ZOOM_FILL
value|"gimp-view-zoom-fill"
end_define

begin_define
DECL|macro|GIMP_HELP_VIEW_ZOOM_OTHER
define|#
directive|define
name|GIMP_HELP_VIEW_ZOOM_OTHER
value|"gimp-view-zoom-other"
end_define

begin_define
DECL|macro|GIMP_HELP_VIEW_SHOW_SELECTION
define|#
directive|define
name|GIMP_HELP_VIEW_SHOW_SELECTION
value|"gimp-view-show-selection"
end_define

begin_define
DECL|macro|GIMP_HELP_VIEW_SHOW_LAYER_BOUNDARY
define|#
directive|define
name|GIMP_HELP_VIEW_SHOW_LAYER_BOUNDARY
value|"gimp-view-show-layer-boundary"
end_define

begin_define
DECL|macro|GIMP_HELP_VIEW_SHOW_GUIDES
define|#
directive|define
name|GIMP_HELP_VIEW_SHOW_GUIDES
value|"gimp-view-show-guides"
end_define

begin_define
DECL|macro|GIMP_HELP_VIEW_SHOW_GRID
define|#
directive|define
name|GIMP_HELP_VIEW_SHOW_GRID
value|"gimp-view-show-grid"
end_define

begin_define
DECL|macro|GIMP_HELP_VIEW_SHOW_SAMPLE_POINTS
define|#
directive|define
name|GIMP_HELP_VIEW_SHOW_SAMPLE_POINTS
value|"gimp-view-show-sample-points"
end_define

begin_define
DECL|macro|GIMP_HELP_VIEW_SNAP_TO_GUIDES
define|#
directive|define
name|GIMP_HELP_VIEW_SNAP_TO_GUIDES
value|"gimp-view-snap-to-guides"
end_define

begin_define
DECL|macro|GIMP_HELP_VIEW_SNAP_TO_GRID
define|#
directive|define
name|GIMP_HELP_VIEW_SNAP_TO_GRID
value|"gimp-view-snap-to-grid"
end_define

begin_define
DECL|macro|GIMP_HELP_VIEW_SNAP_TO_CANVAS
define|#
directive|define
name|GIMP_HELP_VIEW_SNAP_TO_CANVAS
value|"gimp-view-snap-to-canvas"
end_define

begin_define
DECL|macro|GIMP_HELP_VIEW_SNAP_TO_VECTORS
define|#
directive|define
name|GIMP_HELP_VIEW_SNAP_TO_VECTORS
value|"gimp-view-snap-to-vectors"
end_define

begin_define
DECL|macro|GIMP_HELP_VIEW_SHOW_MENUBAR
define|#
directive|define
name|GIMP_HELP_VIEW_SHOW_MENUBAR
value|"gimp-view-show-menubar"
end_define

begin_define
DECL|macro|GIMP_HELP_VIEW_SHOW_RULERS
define|#
directive|define
name|GIMP_HELP_VIEW_SHOW_RULERS
value|"gimp-view-show-rulers"
end_define

begin_define
DECL|macro|GIMP_HELP_VIEW_SHOW_SCROLLBARS
define|#
directive|define
name|GIMP_HELP_VIEW_SHOW_SCROLLBARS
value|"gimp-view-show-scrollbars"
end_define

begin_define
DECL|macro|GIMP_HELP_VIEW_SHOW_STATUSBAR
define|#
directive|define
name|GIMP_HELP_VIEW_SHOW_STATUSBAR
value|"gimp-view-show-statusbar"
end_define

begin_define
DECL|macro|GIMP_HELP_VIEW_PADDING_COLOR
define|#
directive|define
name|GIMP_HELP_VIEW_PADDING_COLOR
value|"gimp-view-padding-color"
end_define

begin_define
DECL|macro|GIMP_HELP_VIEW_SHRINK_WRAP
define|#
directive|define
name|GIMP_HELP_VIEW_SHRINK_WRAP
value|"gimp-view-shrink-wrap"
end_define

begin_define
DECL|macro|GIMP_HELP_VIEW_FULLSCREEN
define|#
directive|define
name|GIMP_HELP_VIEW_FULLSCREEN
value|"gimp-view-fullscreen"
end_define

begin_define
DECL|macro|GIMP_HELP_VIEW_CHANGE_SCREEN
define|#
directive|define
name|GIMP_HELP_VIEW_CHANGE_SCREEN
value|"gimp-view-change-screen"
end_define

begin_define
DECL|macro|GIMP_HELP_IMAGE_WINDOW
define|#
directive|define
name|GIMP_HELP_IMAGE_WINDOW
value|"gimp-image-window"
end_define

begin_define
DECL|macro|GIMP_HELP_IMAGE_WINDOW_ORIGIN
define|#
directive|define
name|GIMP_HELP_IMAGE_WINDOW_ORIGIN
value|"gimp-image-window-origin"
end_define

begin_define
DECL|macro|GIMP_HELP_IMAGE_WINDOW_ZOOM_FOLLOW_BUTTON
define|#
directive|define
name|GIMP_HELP_IMAGE_WINDOW_ZOOM_FOLLOW_BUTTON
value|"gimp-image-window-zoom-follow-button"
end_define

begin_define
DECL|macro|GIMP_HELP_IMAGE_WINDOW_QUICK_MASK_BUTTON
define|#
directive|define
name|GIMP_HELP_IMAGE_WINDOW_QUICK_MASK_BUTTON
value|"gimp-image-window-quick-mask-button"
end_define

begin_define
DECL|macro|GIMP_HELP_IMAGE_WINDOW_NAV_BUTTON
define|#
directive|define
name|GIMP_HELP_IMAGE_WINDOW_NAV_BUTTON
value|"gimp-image-window-nav-button"
end_define

begin_define
DECL|macro|GIMP_HELP_IMAGE_WINDOW_RULER
define|#
directive|define
name|GIMP_HELP_IMAGE_WINDOW_RULER
value|"gimp-image-window-ruler"
end_define

begin_define
DECL|macro|GIMP_HELP_IMAGE_WINDOW_STATUS_BAR
define|#
directive|define
name|GIMP_HELP_IMAGE_WINDOW_STATUS_BAR
value|"gimp-image-window-status-bar"
end_define

begin_define
DECL|macro|GIMP_HELP_IMAGE_DIALOG
define|#
directive|define
name|GIMP_HELP_IMAGE_DIALOG
value|"gimp-image-dialog"
end_define

begin_define
DECL|macro|GIMP_HELP_IMAGE_CONVERT_RGB
define|#
directive|define
name|GIMP_HELP_IMAGE_CONVERT_RGB
value|"gimp-image-convert-rgb"
end_define

begin_define
DECL|macro|GIMP_HELP_IMAGE_CONVERT_GRAYSCALE
define|#
directive|define
name|GIMP_HELP_IMAGE_CONVERT_GRAYSCALE
value|"gimp-image-convert-grayscale"
end_define

begin_define
DECL|macro|GIMP_HELP_IMAGE_CONVERT_INDEXED
define|#
directive|define
name|GIMP_HELP_IMAGE_CONVERT_INDEXED
value|"gimp-image-convert-indexed"
end_define

begin_define
DECL|macro|GIMP_HELP_IMAGE_FLIP_HORIZONTAL
define|#
directive|define
name|GIMP_HELP_IMAGE_FLIP_HORIZONTAL
value|"gimp-image-flip-horizontal"
end_define

begin_define
DECL|macro|GIMP_HELP_IMAGE_FLIP_VERTICAL
define|#
directive|define
name|GIMP_HELP_IMAGE_FLIP_VERTICAL
value|"gimp-image-flip-vertical"
end_define

begin_define
DECL|macro|GIMP_HELP_IMAGE_ROTATE_90
define|#
directive|define
name|GIMP_HELP_IMAGE_ROTATE_90
value|"gimp-image-rotate-90"
end_define

begin_define
DECL|macro|GIMP_HELP_IMAGE_ROTATE_180
define|#
directive|define
name|GIMP_HELP_IMAGE_ROTATE_180
value|"gimp-image-rotate-180"
end_define

begin_define
DECL|macro|GIMP_HELP_IMAGE_ROTATE_270
define|#
directive|define
name|GIMP_HELP_IMAGE_ROTATE_270
value|"gimp-image-rotate-270"
end_define

begin_define
DECL|macro|GIMP_HELP_IMAGE_RESIZE
define|#
directive|define
name|GIMP_HELP_IMAGE_RESIZE
value|"gimp-image-resize"
end_define

begin_define
DECL|macro|GIMP_HELP_IMAGE_RESIZE_TO_LAYERS
define|#
directive|define
name|GIMP_HELP_IMAGE_RESIZE_TO_LAYERS
value|"gimp-image-resize-to-layers"
end_define

begin_define
DECL|macro|GIMP_HELP_IMAGE_RESIZE_TO_SELECTION
define|#
directive|define
name|GIMP_HELP_IMAGE_RESIZE_TO_SELECTION
value|"gimp-image-resize-to-selection"
end_define

begin_define
DECL|macro|GIMP_HELP_IMAGE_PRINT_SIZE
define|#
directive|define
name|GIMP_HELP_IMAGE_PRINT_SIZE
value|"gimp-image-print-size"
end_define

begin_define
DECL|macro|GIMP_HELP_IMAGE_SCALE
define|#
directive|define
name|GIMP_HELP_IMAGE_SCALE
value|"gimp-image-scale"
end_define

begin_define
DECL|macro|GIMP_HELP_IMAGE_SCALE_WARNING
define|#
directive|define
name|GIMP_HELP_IMAGE_SCALE_WARNING
value|"gimp-image-scale-warning"
end_define

begin_define
DECL|macro|GIMP_HELP_IMAGE_CROP
define|#
directive|define
name|GIMP_HELP_IMAGE_CROP
value|"gimp-image-crop"
end_define

begin_define
DECL|macro|GIMP_HELP_IMAGE_DUPLICATE
define|#
directive|define
name|GIMP_HELP_IMAGE_DUPLICATE
value|"gimp-image-duplicate"
end_define

begin_define
DECL|macro|GIMP_HELP_IMAGE_MERGE_LAYERS
define|#
directive|define
name|GIMP_HELP_IMAGE_MERGE_LAYERS
value|"gimp-image-merge-layers"
end_define

begin_define
DECL|macro|GIMP_HELP_IMAGE_FLATTEN
define|#
directive|define
name|GIMP_HELP_IMAGE_FLATTEN
value|"gimp-image-flatten"
end_define

begin_define
DECL|macro|GIMP_HELP_IMAGE_GRID
define|#
directive|define
name|GIMP_HELP_IMAGE_GRID
value|"gimp-image-grid"
end_define

begin_define
DECL|macro|GIMP_HELP_IMAGE_PROPERTIES
define|#
directive|define
name|GIMP_HELP_IMAGE_PROPERTIES
value|"gimp-image-properties"
end_define

begin_define
DECL|macro|GIMP_HELP_LAYER_DIALOG
define|#
directive|define
name|GIMP_HELP_LAYER_DIALOG
value|"gimp-layer-dialog"
end_define

begin_define
DECL|macro|GIMP_HELP_LAYER_DIALOG_PAINT_MODE_MENU
define|#
directive|define
name|GIMP_HELP_LAYER_DIALOG_PAINT_MODE_MENU
value|"gimp-layer-dialog-paint-mode-menu"
end_define

begin_define
DECL|macro|GIMP_HELP_LAYER_DIALOG_OPACITY_SCALE
define|#
directive|define
name|GIMP_HELP_LAYER_DIALOG_OPACITY_SCALE
value|"gimp-layer-dialog-opacity-scale"
end_define

begin_define
DECL|macro|GIMP_HELP_LAYER_DIALOG_LOCK_ALPHA_BUTTON
define|#
directive|define
name|GIMP_HELP_LAYER_DIALOG_LOCK_ALPHA_BUTTON
value|"gimp-layer-dialog-lock-alpha-button"
end_define

begin_define
DECL|macro|GIMP_HELP_LAYER_NEW
define|#
directive|define
name|GIMP_HELP_LAYER_NEW
value|"gimp-layer-new"
end_define

begin_define
DECL|macro|GIMP_HELP_LAYER_NEW_FROM_VISIBLE
define|#
directive|define
name|GIMP_HELP_LAYER_NEW_FROM_VISIBLE
value|"gimp-layer-new-from-visible"
end_define

begin_define
DECL|macro|GIMP_HELP_LAYER_DUPLICATE
define|#
directive|define
name|GIMP_HELP_LAYER_DUPLICATE
value|"gimp-layer-duplicate"
end_define

begin_define
DECL|macro|GIMP_HELP_LAYER_ANCHOR
define|#
directive|define
name|GIMP_HELP_LAYER_ANCHOR
value|"gimp-layer-anchor"
end_define

begin_define
DECL|macro|GIMP_HELP_LAYER_MERGE_DOWN
define|#
directive|define
name|GIMP_HELP_LAYER_MERGE_DOWN
value|"gimp-layer-merge-down"
end_define

begin_define
DECL|macro|GIMP_HELP_LAYER_MERGE_GROUP
define|#
directive|define
name|GIMP_HELP_LAYER_MERGE_GROUP
value|"gimp-layer-merge-group"
end_define

begin_define
DECL|macro|GIMP_HELP_LAYER_DELETE
define|#
directive|define
name|GIMP_HELP_LAYER_DELETE
value|"gimp-layer-delete"
end_define

begin_define
DECL|macro|GIMP_HELP_LAYER_TEXT_DISCARD
define|#
directive|define
name|GIMP_HELP_LAYER_TEXT_DISCARD
value|"gimp-layer-text-discard"
end_define

begin_define
DECL|macro|GIMP_HELP_LAYER_TEXT_TO_PATH
define|#
directive|define
name|GIMP_HELP_LAYER_TEXT_TO_PATH
value|"gimp-layer-text-to-path"
end_define

begin_define
DECL|macro|GIMP_HELP_LAYER_TEXT_ALONG_PATH
define|#
directive|define
name|GIMP_HELP_LAYER_TEXT_ALONG_PATH
value|"gimp-layer-text-along-path"
end_define

begin_define
DECL|macro|GIMP_HELP_LAYER_TEXT_SELECTION_REPLACE
define|#
directive|define
name|GIMP_HELP_LAYER_TEXT_SELECTION_REPLACE
value|"gimp-layer-text-selection-replace"
end_define

begin_define
DECL|macro|GIMP_HELP_LAYER_TEXT_SELECTION_ADD
define|#
directive|define
name|GIMP_HELP_LAYER_TEXT_SELECTION_ADD
value|"gimp-layer-text-selection-add"
end_define

begin_define
DECL|macro|GIMP_HELP_LAYER_TEXT_SELECTION_SUBTRACT
define|#
directive|define
name|GIMP_HELP_LAYER_TEXT_SELECTION_SUBTRACT
value|"gimp-layer-text-selection-subtract"
end_define

begin_define
DECL|macro|GIMP_HELP_LAYER_TEXT_SELECTION_INTERSECT
define|#
directive|define
name|GIMP_HELP_LAYER_TEXT_SELECTION_INTERSECT
value|"gimp-layer-text-selection-intersect"
end_define

begin_define
DECL|macro|GIMP_HELP_LAYER_PREVIOUS
define|#
directive|define
name|GIMP_HELP_LAYER_PREVIOUS
value|"gimp-layer-previous"
end_define

begin_define
DECL|macro|GIMP_HELP_LAYER_NEXT
define|#
directive|define
name|GIMP_HELP_LAYER_NEXT
value|"gimp-layer-next"
end_define

begin_define
DECL|macro|GIMP_HELP_LAYER_TOP
define|#
directive|define
name|GIMP_HELP_LAYER_TOP
value|"gimp-layer-top"
end_define

begin_define
DECL|macro|GIMP_HELP_LAYER_BOTTOM
define|#
directive|define
name|GIMP_HELP_LAYER_BOTTOM
value|"gimp-layer-bottom"
end_define

begin_define
DECL|macro|GIMP_HELP_LAYER_RAISE
define|#
directive|define
name|GIMP_HELP_LAYER_RAISE
value|"gimp-layer-raise"
end_define

begin_define
DECL|macro|GIMP_HELP_LAYER_RAISE_TO_TOP
define|#
directive|define
name|GIMP_HELP_LAYER_RAISE_TO_TOP
value|"gimp-layer-raise-to-top"
end_define

begin_define
DECL|macro|GIMP_HELP_LAYER_LOWER
define|#
directive|define
name|GIMP_HELP_LAYER_LOWER
value|"gimp-layer-lower"
end_define

begin_define
DECL|macro|GIMP_HELP_LAYER_LOWER_TO_BOTTOM
define|#
directive|define
name|GIMP_HELP_LAYER_LOWER_TO_BOTTOM
value|"gimp-layer-lower-to-bottom"
end_define

begin_define
DECL|macro|GIMP_HELP_LAYER_INVERT
define|#
directive|define
name|GIMP_HELP_LAYER_INVERT
value|"gimp-layer-invert"
end_define

begin_define
DECL|macro|GIMP_HELP_LAYER_WHITE_BALANCE
define|#
directive|define
name|GIMP_HELP_LAYER_WHITE_BALANCE
value|"gimp-layer-white-balance"
end_define

begin_define
DECL|macro|GIMP_HELP_LAYER_EQUALIZE
define|#
directive|define
name|GIMP_HELP_LAYER_EQUALIZE
value|"gimp-layer-equalize"
end_define

begin_define
DECL|macro|GIMP_HELP_LAYER_VISIBLE
define|#
directive|define
name|GIMP_HELP_LAYER_VISIBLE
value|"gimp-layer-visible"
end_define

begin_define
DECL|macro|GIMP_HELP_LAYER_LINKED
define|#
directive|define
name|GIMP_HELP_LAYER_LINKED
value|"gimp-layer-linked"
end_define

begin_define
DECL|macro|GIMP_HELP_LAYER_OPACITY
define|#
directive|define
name|GIMP_HELP_LAYER_OPACITY
value|"gimp-layer-opacity"
end_define

begin_define
DECL|macro|GIMP_HELP_LAYER_MODE
define|#
directive|define
name|GIMP_HELP_LAYER_MODE
value|"gimp-layer-mode"
end_define

begin_define
DECL|macro|GIMP_HELP_LAYER_LOCK_ALPHA
define|#
directive|define
name|GIMP_HELP_LAYER_LOCK_ALPHA
value|"gimp-layer-lock-alpha"
end_define

begin_define
DECL|macro|GIMP_HELP_LAYER_MASK_ADD
define|#
directive|define
name|GIMP_HELP_LAYER_MASK_ADD
value|"gimp-layer-mask-add"
end_define

begin_define
DECL|macro|GIMP_HELP_LAYER_MASK_APPLY
define|#
directive|define
name|GIMP_HELP_LAYER_MASK_APPLY
value|"gimp-layer-mask-apply"
end_define

begin_define
DECL|macro|GIMP_HELP_LAYER_MASK_DELETE
define|#
directive|define
name|GIMP_HELP_LAYER_MASK_DELETE
value|"gimp-layer-mask-delete"
end_define

begin_define
DECL|macro|GIMP_HELP_LAYER_MASK_EDIT
define|#
directive|define
name|GIMP_HELP_LAYER_MASK_EDIT
value|"gimp-layer-mask-edit"
end_define

begin_define
DECL|macro|GIMP_HELP_LAYER_MASK_SHOW
define|#
directive|define
name|GIMP_HELP_LAYER_MASK_SHOW
value|"gimp-layer-mask-show"
end_define

begin_define
DECL|macro|GIMP_HELP_LAYER_MASK_DISABLE
define|#
directive|define
name|GIMP_HELP_LAYER_MASK_DISABLE
value|"gimp-layer-mask-disable"
end_define

begin_define
DECL|macro|GIMP_HELP_LAYER_MASK_SELECTION_REPLACE
define|#
directive|define
name|GIMP_HELP_LAYER_MASK_SELECTION_REPLACE
value|"gimp-layer-mask-selection-replace"
end_define

begin_define
DECL|macro|GIMP_HELP_LAYER_MASK_SELECTION_ADD
define|#
directive|define
name|GIMP_HELP_LAYER_MASK_SELECTION_ADD
value|"gimp-layer-mask-selection-add"
end_define

begin_define
DECL|macro|GIMP_HELP_LAYER_MASK_SELECTION_SUBTRACT
define|#
directive|define
name|GIMP_HELP_LAYER_MASK_SELECTION_SUBTRACT
value|"gimp-layer-mask-selection-subtract"
end_define

begin_define
DECL|macro|GIMP_HELP_LAYER_MASK_SELECTION_INTERSECT
define|#
directive|define
name|GIMP_HELP_LAYER_MASK_SELECTION_INTERSECT
value|"gimp-layer-mask-selection-intersect"
end_define

begin_define
DECL|macro|GIMP_HELP_LAYER_ALPHA_ADD
define|#
directive|define
name|GIMP_HELP_LAYER_ALPHA_ADD
value|"gimp-layer-alpha-add"
end_define

begin_define
DECL|macro|GIMP_HELP_LAYER_ALPHA_REMOVE
define|#
directive|define
name|GIMP_HELP_LAYER_ALPHA_REMOVE
value|"gimp-layer-alpha-remove"
end_define

begin_define
DECL|macro|GIMP_HELP_LAYER_ALPHA_SELECTION_REPLACE
define|#
directive|define
name|GIMP_HELP_LAYER_ALPHA_SELECTION_REPLACE
value|"gimp-layer-alpha-selection-replace"
end_define

begin_define
DECL|macro|GIMP_HELP_LAYER_ALPHA_SELECTION_ADD
define|#
directive|define
name|GIMP_HELP_LAYER_ALPHA_SELECTION_ADD
value|"gimp-layer-alpha-selection-add"
end_define

begin_define
DECL|macro|GIMP_HELP_LAYER_ALPHA_SELECTION_SUBTRACT
define|#
directive|define
name|GIMP_HELP_LAYER_ALPHA_SELECTION_SUBTRACT
value|"gimp-layer-alpha-selection-subtract"
end_define

begin_define
DECL|macro|GIMP_HELP_LAYER_ALPHA_SELECTION_INTERSECT
define|#
directive|define
name|GIMP_HELP_LAYER_ALPHA_SELECTION_INTERSECT
value|"gimp-layer-alpha-selection-intersect"
end_define

begin_define
DECL|macro|GIMP_HELP_LAYER_FLIP_HORIZONTAL
define|#
directive|define
name|GIMP_HELP_LAYER_FLIP_HORIZONTAL
value|"gimp-layer-flip-horizontal"
end_define

begin_define
DECL|macro|GIMP_HELP_LAYER_FLIP_VERTICAL
define|#
directive|define
name|GIMP_HELP_LAYER_FLIP_VERTICAL
value|"gimp-layer-flip-vertical"
end_define

begin_define
DECL|macro|GIMP_HELP_LAYER_ROTATE_90
define|#
directive|define
name|GIMP_HELP_LAYER_ROTATE_90
value|"gimp-layer-rotate-90"
end_define

begin_define
DECL|macro|GIMP_HELP_LAYER_ROTATE_180
define|#
directive|define
name|GIMP_HELP_LAYER_ROTATE_180
value|"gimp-layer-rotate-180"
end_define

begin_define
DECL|macro|GIMP_HELP_LAYER_ROTATE_270
define|#
directive|define
name|GIMP_HELP_LAYER_ROTATE_270
value|"gimp-layer-rotate-270"
end_define

begin_define
DECL|macro|GIMP_HELP_LAYER_OFFSET
define|#
directive|define
name|GIMP_HELP_LAYER_OFFSET
value|"gimp-layer-offset"
end_define

begin_define
DECL|macro|GIMP_HELP_LAYER_RESIZE
define|#
directive|define
name|GIMP_HELP_LAYER_RESIZE
value|"gimp-layer-resize"
end_define

begin_define
DECL|macro|GIMP_HELP_LAYER_RESIZE_TO_IMAGE
define|#
directive|define
name|GIMP_HELP_LAYER_RESIZE_TO_IMAGE
value|"gimp-layer-resize-to-image"
end_define

begin_define
DECL|macro|GIMP_HELP_LAYER_SCALE
define|#
directive|define
name|GIMP_HELP_LAYER_SCALE
value|"gimp-layer-scale"
end_define

begin_define
DECL|macro|GIMP_HELP_LAYER_CROP
define|#
directive|define
name|GIMP_HELP_LAYER_CROP
value|"gimp-layer-crop"
end_define

begin_define
DECL|macro|GIMP_HELP_LAYER_EDIT
define|#
directive|define
name|GIMP_HELP_LAYER_EDIT
value|"gimp-layer-edit"
end_define

begin_define
DECL|macro|GIMP_HELP_CHANNEL_DIALOG
define|#
directive|define
name|GIMP_HELP_CHANNEL_DIALOG
value|"gimp-channel-dialog"
end_define

begin_define
DECL|macro|GIMP_HELP_CHANNEL_NEW
define|#
directive|define
name|GIMP_HELP_CHANNEL_NEW
value|"gimp-channel-new"
end_define

begin_define
DECL|macro|GIMP_HELP_CHANNEL_RAISE
define|#
directive|define
name|GIMP_HELP_CHANNEL_RAISE
value|"gimp-channel-raise"
end_define

begin_define
DECL|macro|GIMP_HELP_CHANNEL_RAISE_TO_TOP
define|#
directive|define
name|GIMP_HELP_CHANNEL_RAISE_TO_TOP
value|"gimp-channel-raise-to-top"
end_define

begin_define
DECL|macro|GIMP_HELP_CHANNEL_LOWER
define|#
directive|define
name|GIMP_HELP_CHANNEL_LOWER
value|"gimp-channel-lower"
end_define

begin_define
DECL|macro|GIMP_HELP_CHANNEL_LOWER_TO_BOTTOM
define|#
directive|define
name|GIMP_HELP_CHANNEL_LOWER_TO_BOTTOM
value|"gimp-channel-lower-to-bottom"
end_define

begin_define
DECL|macro|GIMP_HELP_CHANNEL_DUPLICATE
define|#
directive|define
name|GIMP_HELP_CHANNEL_DUPLICATE
value|"gimp-channel-duplicate"
end_define

begin_define
DECL|macro|GIMP_HELP_CHANNEL_DELETE
define|#
directive|define
name|GIMP_HELP_CHANNEL_DELETE
value|"gimp-channel-delete"
end_define

begin_define
DECL|macro|GIMP_HELP_CHANNEL_SELECTION_REPLACE
define|#
directive|define
name|GIMP_HELP_CHANNEL_SELECTION_REPLACE
value|"gimp-channel-selection-replace"
end_define

begin_define
DECL|macro|GIMP_HELP_CHANNEL_SELECTION_ADD
define|#
directive|define
name|GIMP_HELP_CHANNEL_SELECTION_ADD
value|"gimp-channel-selection-add"
end_define

begin_define
DECL|macro|GIMP_HELP_CHANNEL_SELECTION_SUBTRACT
define|#
directive|define
name|GIMP_HELP_CHANNEL_SELECTION_SUBTRACT
value|"gimp-channel-selection-subtract"
end_define

begin_define
DECL|macro|GIMP_HELP_CHANNEL_SELECTION_INTERSECT
define|#
directive|define
name|GIMP_HELP_CHANNEL_SELECTION_INTERSECT
value|"gimp-channel-selection-intersect"
end_define

begin_define
DECL|macro|GIMP_HELP_CHANNEL_EDIT
define|#
directive|define
name|GIMP_HELP_CHANNEL_EDIT
value|"gimp-channel-edit"
end_define

begin_define
DECL|macro|GIMP_HELP_QUICK_MASK
define|#
directive|define
name|GIMP_HELP_QUICK_MASK
value|"gimp-quick-mask"
end_define

begin_define
DECL|macro|GIMP_HELP_QUICK_MASK_TOGGLE
define|#
directive|define
name|GIMP_HELP_QUICK_MASK_TOGGLE
value|"gimp-quick-mask-toggle"
end_define

begin_define
DECL|macro|GIMP_HELP_QUICK_MASK_INVERT
define|#
directive|define
name|GIMP_HELP_QUICK_MASK_INVERT
value|"gimp-quick-mask-invert"
end_define

begin_define
DECL|macro|GIMP_HELP_QUICK_MASK_EDIT
define|#
directive|define
name|GIMP_HELP_QUICK_MASK_EDIT
value|"gimp-quick-mask-edit"
end_define

begin_define
DECL|macro|GIMP_HELP_PATH_DIALOG
define|#
directive|define
name|GIMP_HELP_PATH_DIALOG
value|"gimp-path-dialog"
end_define

begin_define
DECL|macro|GIMP_HELP_PATH_NEW
define|#
directive|define
name|GIMP_HELP_PATH_NEW
value|"gimp-path-new"
end_define

begin_define
DECL|macro|GIMP_HELP_PATH_RAISE
define|#
directive|define
name|GIMP_HELP_PATH_RAISE
value|"gimp-path-raise"
end_define

begin_define
DECL|macro|GIMP_HELP_PATH_RAISE_TO_TOP
define|#
directive|define
name|GIMP_HELP_PATH_RAISE_TO_TOP
value|"gimp-path-raise-to-top"
end_define

begin_define
DECL|macro|GIMP_HELP_PATH_LOWER
define|#
directive|define
name|GIMP_HELP_PATH_LOWER
value|"gimp-path-lower"
end_define

begin_define
DECL|macro|GIMP_HELP_PATH_LOWER_TO_BOTTOM
define|#
directive|define
name|GIMP_HELP_PATH_LOWER_TO_BOTTOM
value|"gimp-path-lower-to-bottom"
end_define

begin_define
DECL|macro|GIMP_HELP_PATH_DUPLICATE
define|#
directive|define
name|GIMP_HELP_PATH_DUPLICATE
value|"gimp-path-duplicate"
end_define

begin_define
DECL|macro|GIMP_HELP_PATH_DELETE
define|#
directive|define
name|GIMP_HELP_PATH_DELETE
value|"gimp-path-delete"
end_define

begin_define
DECL|macro|GIMP_HELP_PATH_MERGE_VISIBLE
define|#
directive|define
name|GIMP_HELP_PATH_MERGE_VISIBLE
value|"gimp-path-merge-visible"
end_define

begin_define
DECL|macro|GIMP_HELP_PATH_VISIBLE
define|#
directive|define
name|GIMP_HELP_PATH_VISIBLE
value|"gimp-path-visible"
end_define

begin_define
DECL|macro|GIMP_HELP_PATH_LINKED
define|#
directive|define
name|GIMP_HELP_PATH_LINKED
value|"gimp-path-linked"
end_define

begin_define
DECL|macro|GIMP_HELP_PATH_SELECTION_REPLACE
define|#
directive|define
name|GIMP_HELP_PATH_SELECTION_REPLACE
value|"gimp-path-selection-replace"
end_define

begin_define
DECL|macro|GIMP_HELP_PATH_SELECTION_ADD
define|#
directive|define
name|GIMP_HELP_PATH_SELECTION_ADD
value|"gimp-path-selection-add"
end_define

begin_define
DECL|macro|GIMP_HELP_PATH_SELECTION_SUBTRACT
define|#
directive|define
name|GIMP_HELP_PATH_SELECTION_SUBTRACT
value|"gimp-path-selection-subtract"
end_define

begin_define
DECL|macro|GIMP_HELP_PATH_SELECTION_INTERSECT
define|#
directive|define
name|GIMP_HELP_PATH_SELECTION_INTERSECT
value|"gimp-path-selection-intersect"
end_define

begin_define
DECL|macro|GIMP_HELP_PATH_STROKE
define|#
directive|define
name|GIMP_HELP_PATH_STROKE
value|"gimp-path-stroke"
end_define

begin_define
DECL|macro|GIMP_HELP_PATH_COPY
define|#
directive|define
name|GIMP_HELP_PATH_COPY
value|"gimp-path-copy"
end_define

begin_define
DECL|macro|GIMP_HELP_PATH_PASTE
define|#
directive|define
name|GIMP_HELP_PATH_PASTE
value|"gimp-path-paste"
end_define

begin_define
DECL|macro|GIMP_HELP_PATH_IMPORT
define|#
directive|define
name|GIMP_HELP_PATH_IMPORT
value|"gimp-path-import"
end_define

begin_define
DECL|macro|GIMP_HELP_PATH_EXPORT
define|#
directive|define
name|GIMP_HELP_PATH_EXPORT
value|"gimp-path-export"
end_define

begin_define
DECL|macro|GIMP_HELP_PATH_EDIT
define|#
directive|define
name|GIMP_HELP_PATH_EDIT
value|"gimp-path-edit"
end_define

begin_define
DECL|macro|GIMP_HELP_TOOLS_DIALOG
define|#
directive|define
name|GIMP_HELP_TOOLS_DIALOG
value|"gimp-tools-dialog"
end_define

begin_define
DECL|macro|GIMP_HELP_TOOL_AIRBRUSH
define|#
directive|define
name|GIMP_HELP_TOOL_AIRBRUSH
value|"gimp-tool-airbrush"
end_define

begin_define
DECL|macro|GIMP_HELP_TOOL_ALIGN
define|#
directive|define
name|GIMP_HELP_TOOL_ALIGN
value|"gimp-tool-align"
end_define

begin_define
DECL|macro|GIMP_HELP_TOOL_BLEND
define|#
directive|define
name|GIMP_HELP_TOOL_BLEND
value|"gimp-tool-blend"
end_define

begin_define
DECL|macro|GIMP_HELP_TOOL_BRIGHTNESS_CONTRAST
define|#
directive|define
name|GIMP_HELP_TOOL_BRIGHTNESS_CONTRAST
value|"gimp-tool-brightness-contrast"
end_define

begin_define
DECL|macro|GIMP_HELP_TOOL_BUCKET_FILL
define|#
directive|define
name|GIMP_HELP_TOOL_BUCKET_FILL
value|"gimp-tool-bucket-fill"
end_define

begin_define
DECL|macro|GIMP_HELP_TOOL_BY_COLOR_SELECT
define|#
directive|define
name|GIMP_HELP_TOOL_BY_COLOR_SELECT
value|"gimp-tool-by-color-select"
end_define

begin_define
DECL|macro|GIMP_HELP_TOOL_CLONE
define|#
directive|define
name|GIMP_HELP_TOOL_CLONE
value|"gimp-tool-clone"
end_define

begin_define
DECL|macro|GIMP_HELP_TOOL_COLORIZE
define|#
directive|define
name|GIMP_HELP_TOOL_COLORIZE
value|"gimp-tool-colorize"
end_define

begin_define
DECL|macro|GIMP_HELP_TOOL_COLOR_BALANCE
define|#
directive|define
name|GIMP_HELP_TOOL_COLOR_BALANCE
value|"gimp-tool-color-balance"
end_define

begin_define
DECL|macro|GIMP_HELP_TOOL_COLOR_PICKER
define|#
directive|define
name|GIMP_HELP_TOOL_COLOR_PICKER
value|"gimp-tool-color-picker"
end_define

begin_define
DECL|macro|GIMP_HELP_TOOL_CONVOLVE
define|#
directive|define
name|GIMP_HELP_TOOL_CONVOLVE
value|"gimp-tool-convolve"
end_define

begin_define
DECL|macro|GIMP_HELP_TOOL_CROP
define|#
directive|define
name|GIMP_HELP_TOOL_CROP
value|"gimp-tool-crop"
end_define

begin_define
DECL|macro|GIMP_HELP_TOOL_CURVES
define|#
directive|define
name|GIMP_HELP_TOOL_CURVES
value|"gimp-tool-curves"
end_define

begin_define
DECL|macro|GIMP_HELP_TOOL_CURVES
define|#
directive|define
name|GIMP_HELP_TOOL_CURVES
value|"gimp-tool-curves"
end_define

begin_define
DECL|macro|GIMP_HELP_TOOL_DESATURATE
define|#
directive|define
name|GIMP_HELP_TOOL_DESATURATE
value|"gimp-tool-desaturate"
end_define

begin_define
DECL|macro|GIMP_HELP_TOOL_DODGE_BURN
define|#
directive|define
name|GIMP_HELP_TOOL_DODGE_BURN
value|"gimp-tool-dodge-burn"
end_define

begin_define
DECL|macro|GIMP_HELP_TOOL_ELLIPSE_SELECT
define|#
directive|define
name|GIMP_HELP_TOOL_ELLIPSE_SELECT
value|"gimp-tool-ellipse-select"
end_define

begin_define
DECL|macro|GIMP_HELP_TOOL_ERASER
define|#
directive|define
name|GIMP_HELP_TOOL_ERASER
value|"gimp-tool-eraser"
end_define

begin_define
DECL|macro|GIMP_HELP_TOOL_FLIP
define|#
directive|define
name|GIMP_HELP_TOOL_FLIP
value|"gimp-tool-flip"
end_define

begin_define
DECL|macro|GIMP_HELP_TOOL_FREE_SELECT
define|#
directive|define
name|GIMP_HELP_TOOL_FREE_SELECT
value|"gimp-tool-free-select"
end_define

begin_define
DECL|macro|GIMP_HELP_TOOL_FOREGROUND_SELECT
define|#
directive|define
name|GIMP_HELP_TOOL_FOREGROUND_SELECT
value|"gimp-tool-foreground-select"
end_define

begin_define
DECL|macro|GIMP_HELP_TOOL_FUZZY_SELECT
define|#
directive|define
name|GIMP_HELP_TOOL_FUZZY_SELECT
value|"gimp-tool-fuzzy-select"
end_define

begin_define
DECL|macro|GIMP_HELP_TOOL_GEGL
define|#
directive|define
name|GIMP_HELP_TOOL_GEGL
value|"gimp-tool-gegl"
end_define

begin_define
DECL|macro|GIMP_HELP_TOOL_HEAL
define|#
directive|define
name|GIMP_HELP_TOOL_HEAL
value|"gimp-tool-heal"
end_define

begin_define
DECL|macro|GIMP_HELP_TOOL_HUE_SATURATION
define|#
directive|define
name|GIMP_HELP_TOOL_HUE_SATURATION
value|"gimp-tool-hue-saturation"
end_define

begin_define
DECL|macro|GIMP_HELP_TOOL_INK
define|#
directive|define
name|GIMP_HELP_TOOL_INK
value|"gimp-tool-ink"
end_define

begin_define
DECL|macro|GIMP_HELP_TOOL_ISCISSORS
define|#
directive|define
name|GIMP_HELP_TOOL_ISCISSORS
value|"gimp-tool-iscissors"
end_define

begin_define
DECL|macro|GIMP_HELP_TOOL_LEVELS
define|#
directive|define
name|GIMP_HELP_TOOL_LEVELS
value|"gimp-tool-levels"
end_define

begin_define
DECL|macro|GIMP_HELP_TOOL_MEASURE
define|#
directive|define
name|GIMP_HELP_TOOL_MEASURE
value|"gimp-tool-measure"
end_define

begin_define
DECL|macro|GIMP_HELP_TOOL_MOVE
define|#
directive|define
name|GIMP_HELP_TOOL_MOVE
value|"gimp-tool-move"
end_define

begin_define
DECL|macro|GIMP_HELP_TOOL_PATH
define|#
directive|define
name|GIMP_HELP_TOOL_PATH
value|"gimp-tool-path"
end_define

begin_define
DECL|macro|GIMP_HELP_TOOL_PAINTBRUSH
define|#
directive|define
name|GIMP_HELP_TOOL_PAINTBRUSH
value|"gimp-tool-paintbrush"
end_define

begin_define
DECL|macro|GIMP_HELP_TOOL_PENCIL
define|#
directive|define
name|GIMP_HELP_TOOL_PENCIL
value|"gimp-tool-pencil"
end_define

begin_define
DECL|macro|GIMP_HELP_TOOL_PERSPECTIVE
define|#
directive|define
name|GIMP_HELP_TOOL_PERSPECTIVE
value|"gimp-tool-perspective"
end_define

begin_define
DECL|macro|GIMP_HELP_TOOL_PERSPECTIVE_CLONE
define|#
directive|define
name|GIMP_HELP_TOOL_PERSPECTIVE_CLONE
value|"gimp-tool-perspective-clone"
end_define

begin_define
DECL|macro|GIMP_HELP_TOOL_POSTERIZE
define|#
directive|define
name|GIMP_HELP_TOOL_POSTERIZE
value|"gimp-tool-posterize"
end_define

begin_define
DECL|macro|GIMP_HELP_TOOL_RECT_SELECT
define|#
directive|define
name|GIMP_HELP_TOOL_RECT_SELECT
value|"gimp-tool-rect-select"
end_define

begin_define
DECL|macro|GIMP_HELP_TOOL_ROTATE
define|#
directive|define
name|GIMP_HELP_TOOL_ROTATE
value|"gimp-tool-rotate"
end_define

begin_define
DECL|macro|GIMP_HELP_TOOL_SCALE
define|#
directive|define
name|GIMP_HELP_TOOL_SCALE
value|"gimp-tool-scale"
end_define

begin_define
DECL|macro|GIMP_HELP_TOOL_SHEAR
define|#
directive|define
name|GIMP_HELP_TOOL_SHEAR
value|"gimp-tool-shear"
end_define

begin_define
DECL|macro|GIMP_HELP_TOOL_SMUDGE
define|#
directive|define
name|GIMP_HELP_TOOL_SMUDGE
value|"gimp-tool-smudge"
end_define

begin_define
DECL|macro|GIMP_HELP_TOOL_TEXT
define|#
directive|define
name|GIMP_HELP_TOOL_TEXT
value|"gimp-tool-text"
end_define

begin_define
DECL|macro|GIMP_HELP_TOOL_THRESHOLD
define|#
directive|define
name|GIMP_HELP_TOOL_THRESHOLD
value|"gimp-tool-threshold"
end_define

begin_define
DECL|macro|GIMP_HELP_TOOL_VECTORS
define|#
directive|define
name|GIMP_HELP_TOOL_VECTORS
value|"gimp-tool-vectors"
end_define

begin_define
DECL|macro|GIMP_HELP_TOOL_ZOOM
define|#
directive|define
name|GIMP_HELP_TOOL_ZOOM
value|"gimp-tool-zoom"
end_define

begin_define
DECL|macro|GIMP_HELP_FILTER_REPEAT
define|#
directive|define
name|GIMP_HELP_FILTER_REPEAT
value|"gimp-filter-repeat"
end_define

begin_define
DECL|macro|GIMP_HELP_FILTER_RESHOW
define|#
directive|define
name|GIMP_HELP_FILTER_RESHOW
value|"gimp-filter-reshow"
end_define

begin_define
DECL|macro|GIMP_HELP_FILTER_RESET_ALL
define|#
directive|define
name|GIMP_HELP_FILTER_RESET_ALL
value|"gimp-filter-reset-all"
end_define

begin_define
DECL|macro|GIMP_HELP_TOOLBOX
define|#
directive|define
name|GIMP_HELP_TOOLBOX
value|"gimp-toolbox"
end_define

begin_define
DECL|macro|GIMP_HELP_TOOLBOX_COLOR_AREA
define|#
directive|define
name|GIMP_HELP_TOOLBOX_COLOR_AREA
value|"gimp-toolbox-color-area"
end_define

begin_define
DECL|macro|GIMP_HELP_TOOLBOX_IMAGE_AREA
define|#
directive|define
name|GIMP_HELP_TOOLBOX_IMAGE_AREA
value|"gimp-toolbox-image-area"
end_define

begin_define
DECL|macro|GIMP_HELP_TOOLBOX_INDICATOR_AREA
define|#
directive|define
name|GIMP_HELP_TOOLBOX_INDICATOR_AREA
value|"gimp-toolbox-indicator-area"
end_define

begin_define
DECL|macro|GIMP_HELP_TOOLBOX_DEFAULT_COLORS
define|#
directive|define
name|GIMP_HELP_TOOLBOX_DEFAULT_COLORS
value|"gimp-toolbox-default-colors"
end_define

begin_define
DECL|macro|GIMP_HELP_TOOLBOX_SWAP_COLORS
define|#
directive|define
name|GIMP_HELP_TOOLBOX_SWAP_COLORS
value|"gimp-toolbox-swap-colors"
end_define

begin_define
DECL|macro|GIMP_HELP_BRUSH_DIALOG
define|#
directive|define
name|GIMP_HELP_BRUSH_DIALOG
value|"gimp-brush-dialog"
end_define

begin_define
DECL|macro|GIMP_HELP_BRUSH_EDIT
define|#
directive|define
name|GIMP_HELP_BRUSH_EDIT
value|"gimp-brush-edit"
end_define

begin_define
DECL|macro|GIMP_HELP_BRUSH_OPEN_AS_IMAGE
define|#
directive|define
name|GIMP_HELP_BRUSH_OPEN_AS_IMAGE
value|"gimp-brush-open-as-image"
end_define

begin_define
DECL|macro|GIMP_HELP_BRUSH_NEW
define|#
directive|define
name|GIMP_HELP_BRUSH_NEW
value|"gimp-brush-new"
end_define

begin_define
DECL|macro|GIMP_HELP_BRUSH_DUPLICATE
define|#
directive|define
name|GIMP_HELP_BRUSH_DUPLICATE
value|"gimp-brush-duplicate"
end_define

begin_define
DECL|macro|GIMP_HELP_BRUSH_COPY_LOCATION
define|#
directive|define
name|GIMP_HELP_BRUSH_COPY_LOCATION
value|"gimp-brush-copy-location"
end_define

begin_define
DECL|macro|GIMP_HELP_BRUSH_DELETE
define|#
directive|define
name|GIMP_HELP_BRUSH_DELETE
value|"gimp-brush-delete"
end_define

begin_define
DECL|macro|GIMP_HELP_BRUSH_REFRESH
define|#
directive|define
name|GIMP_HELP_BRUSH_REFRESH
value|"gimp-brush-refresh"
end_define

begin_define
DECL|macro|GIMP_HELP_BRUSH_EDITOR_DIALOG
define|#
directive|define
name|GIMP_HELP_BRUSH_EDITOR_DIALOG
value|"gimp-brush-editor-dialog"
end_define

begin_define
DECL|macro|GIMP_HELP_BRUSH_EDITOR_EDIT_ACTIVE
define|#
directive|define
name|GIMP_HELP_BRUSH_EDITOR_EDIT_ACTIVE
value|"gimp-brush-editor-edit-active"
end_define

begin_define
DECL|macro|GIMP_HELP_DYNAMICS_EDITOR_DIALOG
define|#
directive|define
name|GIMP_HELP_DYNAMICS_EDITOR_DIALOG
value|"gimp-dynamics-editor-dialog"
end_define

begin_define
DECL|macro|GIMP_HELP_DYNAMICS_DIALOG
define|#
directive|define
name|GIMP_HELP_DYNAMICS_DIALOG
value|"gimp-dynamics-dialog"
end_define

begin_define
DECL|macro|GIMP_HELP_DYNAMICS_EDIT
define|#
directive|define
name|GIMP_HELP_DYNAMICS_EDIT
value|"gimp-dynamics-edit"
end_define

begin_define
DECL|macro|GIMP_HELP_DYNAMICS_NEW
define|#
directive|define
name|GIMP_HELP_DYNAMICS_NEW
value|"gimp-dynamics-new"
end_define

begin_define
DECL|macro|GIMP_HELP_DYNAMICS_DUPLICATE
define|#
directive|define
name|GIMP_HELP_DYNAMICS_DUPLICATE
value|"gimp-dynamics-duplicate"
end_define

begin_define
DECL|macro|GIMP_HELP_DYNAMICS_COPY_LOCATION
define|#
directive|define
name|GIMP_HELP_DYNAMICS_COPY_LOCATION
value|"gimp-dynamics-copy-location"
end_define

begin_define
DECL|macro|GIMP_HELP_DYNAMICS_DELETE
define|#
directive|define
name|GIMP_HELP_DYNAMICS_DELETE
value|"gimp-dynamics-delete"
end_define

begin_define
DECL|macro|GIMP_HELP_DYNAMICS_REFRESH
define|#
directive|define
name|GIMP_HELP_DYNAMICS_REFRESH
value|"gimp-dynamics-refresh"
end_define

begin_define
DECL|macro|GIMP_HELP_PATTERN_DIALOG
define|#
directive|define
name|GIMP_HELP_PATTERN_DIALOG
value|"gimp-pattern-dialog"
end_define

begin_define
DECL|macro|GIMP_HELP_PATTERN_EDIT
define|#
directive|define
name|GIMP_HELP_PATTERN_EDIT
value|"gimp-pattern-edit"
end_define

begin_define
DECL|macro|GIMP_HELP_PATTERN_OPEN_AS_IMAGE
define|#
directive|define
name|GIMP_HELP_PATTERN_OPEN_AS_IMAGE
value|"gimp-pattern-open-as-image"
end_define

begin_define
DECL|macro|GIMP_HELP_PATTERN_NEW
define|#
directive|define
name|GIMP_HELP_PATTERN_NEW
value|"gimp-pattern-new"
end_define

begin_define
DECL|macro|GIMP_HELP_PATTERN_DUPLICATE
define|#
directive|define
name|GIMP_HELP_PATTERN_DUPLICATE
value|"gimp-pattern-duplicate"
end_define

begin_define
DECL|macro|GIMP_HELP_PATTERN_COPY_LOCATION
define|#
directive|define
name|GIMP_HELP_PATTERN_COPY_LOCATION
value|"gimp-pattern-copy-location"
end_define

begin_define
DECL|macro|GIMP_HELP_PATTERN_DELETE
define|#
directive|define
name|GIMP_HELP_PATTERN_DELETE
value|"gimp-pattern-delete"
end_define

begin_define
DECL|macro|GIMP_HELP_PATTERN_REFRESH
define|#
directive|define
name|GIMP_HELP_PATTERN_REFRESH
value|"gimp-pattern-refresh"
end_define

begin_define
DECL|macro|GIMP_HELP_GRADIENT_DIALOG
define|#
directive|define
name|GIMP_HELP_GRADIENT_DIALOG
value|"gimp-gradient-dialog"
end_define

begin_define
DECL|macro|GIMP_HELP_GRADIENT_EDIT
define|#
directive|define
name|GIMP_HELP_GRADIENT_EDIT
value|"gimp-gradient-edit"
end_define

begin_define
DECL|macro|GIMP_HELP_GRADIENT_NEW
define|#
directive|define
name|GIMP_HELP_GRADIENT_NEW
value|"gimp-gradient-new"
end_define

begin_define
DECL|macro|GIMP_HELP_GRADIENT_DUPLICATE
define|#
directive|define
name|GIMP_HELP_GRADIENT_DUPLICATE
value|"gimp-gradient-duplicate"
end_define

begin_define
DECL|macro|GIMP_HELP_GRADIENT_COPY_LOCATION
define|#
directive|define
name|GIMP_HELP_GRADIENT_COPY_LOCATION
value|"gimp-gradient-copy-location"
end_define

begin_define
DECL|macro|GIMP_HELP_GRADIENT_DELETE
define|#
directive|define
name|GIMP_HELP_GRADIENT_DELETE
value|"gimp-gradient-delete"
end_define

begin_define
DECL|macro|GIMP_HELP_GRADIENT_REFRESH
define|#
directive|define
name|GIMP_HELP_GRADIENT_REFRESH
value|"gimp-gradient-refresh"
end_define

begin_define
DECL|macro|GIMP_HELP_GRADIENT_SAVE_AS_POV
define|#
directive|define
name|GIMP_HELP_GRADIENT_SAVE_AS_POV
value|"gimp-gradient-save-as-pov"
end_define

begin_define
DECL|macro|GIMP_HELP_GRADIENT_EDITOR_DIALOG
define|#
directive|define
name|GIMP_HELP_GRADIENT_EDITOR_DIALOG
value|"gimp-gradient-editor-dialog"
end_define

begin_define
DECL|macro|GIMP_HELP_GRADIENT_EDITOR_LEFT_COLOR
define|#
directive|define
name|GIMP_HELP_GRADIENT_EDITOR_LEFT_COLOR
value|"gimp-gradient-editor-left-color"
end_define

begin_define
DECL|macro|GIMP_HELP_GRADIENT_EDITOR_LEFT_LOAD
define|#
directive|define
name|GIMP_HELP_GRADIENT_EDITOR_LEFT_LOAD
value|"gimp-gradient-editor-left-load"
end_define

begin_define
DECL|macro|GIMP_HELP_GRADIENT_EDITOR_LEFT_SAVE
define|#
directive|define
name|GIMP_HELP_GRADIENT_EDITOR_LEFT_SAVE
value|"gimp-gradient-editor-left-save"
end_define

begin_define
DECL|macro|GIMP_HELP_GRADIENT_EDITOR_RIGHT_COLOR
define|#
directive|define
name|GIMP_HELP_GRADIENT_EDITOR_RIGHT_COLOR
value|"gimp-gradient-editor-right-color"
end_define

begin_define
DECL|macro|GIMP_HELP_GRADIENT_EDITOR_RIGHT_LOAD
define|#
directive|define
name|GIMP_HELP_GRADIENT_EDITOR_RIGHT_LOAD
value|"gimp-gradient-editor-right-load"
end_define

begin_define
DECL|macro|GIMP_HELP_GRADIENT_EDITOR_RIGHT_SAVE
define|#
directive|define
name|GIMP_HELP_GRADIENT_EDITOR_RIGHT_SAVE
value|"gimp-gradient-editor-right-save"
end_define

begin_define
DECL|macro|GIMP_HELP_GRADIENT_EDITOR_BLENDING
define|#
directive|define
name|GIMP_HELP_GRADIENT_EDITOR_BLENDING
value|"gimp-gradient-editor-blending"
end_define

begin_define
DECL|macro|GIMP_HELP_GRADIENT_EDITOR_COLORING
define|#
directive|define
name|GIMP_HELP_GRADIENT_EDITOR_COLORING
value|"gimp-gradient-editor-coloring"
end_define

begin_define
DECL|macro|GIMP_HELP_GRADIENT_EDITOR_FLIP
define|#
directive|define
name|GIMP_HELP_GRADIENT_EDITOR_FLIP
value|"gimp-gradient-editor-flip"
end_define

begin_define
DECL|macro|GIMP_HELP_GRADIENT_EDITOR_REPLICATE
define|#
directive|define
name|GIMP_HELP_GRADIENT_EDITOR_REPLICATE
value|"gimp-gradient-editor-replicate"
end_define

begin_define
DECL|macro|GIMP_HELP_GRADIENT_EDITOR_SPLIT_MIDPOINT
define|#
directive|define
name|GIMP_HELP_GRADIENT_EDITOR_SPLIT_MIDPOINT
value|"gimp-gradient-editor-split-midpoint"
end_define

begin_define
DECL|macro|GIMP_HELP_GRADIENT_EDITOR_SPLIT_UNIFORM
define|#
directive|define
name|GIMP_HELP_GRADIENT_EDITOR_SPLIT_UNIFORM
value|"gimp-gradient-editor-split-uniform"
end_define

begin_define
DECL|macro|GIMP_HELP_GRADIENT_EDITOR_DELETE
define|#
directive|define
name|GIMP_HELP_GRADIENT_EDITOR_DELETE
value|"gimp-gradient-editor-delete"
end_define

begin_define
DECL|macro|GIMP_HELP_GRADIENT_EDITOR_RECENTER
define|#
directive|define
name|GIMP_HELP_GRADIENT_EDITOR_RECENTER
value|"gimp-gradient-editor-recenter"
end_define

begin_define
DECL|macro|GIMP_HELP_GRADIENT_EDITOR_REDISTRIBUTE
define|#
directive|define
name|GIMP_HELP_GRADIENT_EDITOR_REDISTRIBUTE
value|"gimp-gradient-editor-redistribute"
end_define

begin_define
DECL|macro|GIMP_HELP_GRADIENT_EDITOR_BLEND_COLOR
define|#
directive|define
name|GIMP_HELP_GRADIENT_EDITOR_BLEND_COLOR
value|"gimp-gradient-editor-blend-color"
end_define

begin_define
DECL|macro|GIMP_HELP_GRADIENT_EDITOR_BLEND_OPACITY
define|#
directive|define
name|GIMP_HELP_GRADIENT_EDITOR_BLEND_OPACITY
value|"gimp-gradient-editor-blend-opacity"
end_define

begin_define
DECL|macro|GIMP_HELP_GRADIENT_EDITOR_ZOOM_OUT
define|#
directive|define
name|GIMP_HELP_GRADIENT_EDITOR_ZOOM_OUT
value|"gimp-gradient-editor-zoom-out"
end_define

begin_define
DECL|macro|GIMP_HELP_GRADIENT_EDITOR_ZOOM_IN
define|#
directive|define
name|GIMP_HELP_GRADIENT_EDITOR_ZOOM_IN
value|"gimp-gradient-editor-zoom-in"
end_define

begin_define
DECL|macro|GIMP_HELP_GRADIENT_EDITOR_ZOOM_ALL
define|#
directive|define
name|GIMP_HELP_GRADIENT_EDITOR_ZOOM_ALL
value|"gimp-gradient-editor-zoom-all"
end_define

begin_define
DECL|macro|GIMP_HELP_GRADIENT_EDITOR_EDIT_ACTIVE
define|#
directive|define
name|GIMP_HELP_GRADIENT_EDITOR_EDIT_ACTIVE
value|"gimp-gradient-editor-edit-active"
end_define

begin_define
DECL|macro|GIMP_HELP_PALETTE_DIALOG
define|#
directive|define
name|GIMP_HELP_PALETTE_DIALOG
value|"gimp-palette-dialog"
end_define

begin_define
DECL|macro|GIMP_HELP_PALETTE_EDIT
define|#
directive|define
name|GIMP_HELP_PALETTE_EDIT
value|"gimp-palette-edit"
end_define

begin_define
DECL|macro|GIMP_HELP_PALETTE_NEW
define|#
directive|define
name|GIMP_HELP_PALETTE_NEW
value|"gimp-palette-new"
end_define

begin_define
DECL|macro|GIMP_HELP_PALETTE_DUPLICATE
define|#
directive|define
name|GIMP_HELP_PALETTE_DUPLICATE
value|"gimp-palette-duplicate"
end_define

begin_define
DECL|macro|GIMP_HELP_PALETTE_COPY_LOCATION
define|#
directive|define
name|GIMP_HELP_PALETTE_COPY_LOCATION
value|"gimp-palette-copy-location"
end_define

begin_define
DECL|macro|GIMP_HELP_PALETTE_DELETE
define|#
directive|define
name|GIMP_HELP_PALETTE_DELETE
value|"gimp-palette-delete"
end_define

begin_define
DECL|macro|GIMP_HELP_PALETTE_REFRESH
define|#
directive|define
name|GIMP_HELP_PALETTE_REFRESH
value|"gimp-palette-refresh"
end_define

begin_define
DECL|macro|GIMP_HELP_PALETTE_IMPORT
define|#
directive|define
name|GIMP_HELP_PALETTE_IMPORT
value|"gimp-palette-import"
end_define

begin_define
DECL|macro|GIMP_HELP_PALETTE_MERGE
define|#
directive|define
name|GIMP_HELP_PALETTE_MERGE
value|"gimp-palette-merge"
end_define

begin_define
DECL|macro|GIMP_HELP_PALETTE_EDITOR_DIALOG
define|#
directive|define
name|GIMP_HELP_PALETTE_EDITOR_DIALOG
value|"gimp-palette-editor-dialog"
end_define

begin_define
DECL|macro|GIMP_HELP_PALETTE_EDITOR_NEW
define|#
directive|define
name|GIMP_HELP_PALETTE_EDITOR_NEW
value|"gimp-palette-editor-new"
end_define

begin_define
DECL|macro|GIMP_HELP_PALETTE_EDITOR_EDIT
define|#
directive|define
name|GIMP_HELP_PALETTE_EDITOR_EDIT
value|"gimp-palette-editor-edit"
end_define

begin_define
DECL|macro|GIMP_HELP_PALETTE_EDITOR_DELETE
define|#
directive|define
name|GIMP_HELP_PALETTE_EDITOR_DELETE
value|"gimp-palette-editor-delete"
end_define

begin_define
DECL|macro|GIMP_HELP_PALETTE_EDITOR_ZOOM_OUT
define|#
directive|define
name|GIMP_HELP_PALETTE_EDITOR_ZOOM_OUT
value|"gimp-palette-editor-zoom-out"
end_define

begin_define
DECL|macro|GIMP_HELP_PALETTE_EDITOR_ZOOM_IN
define|#
directive|define
name|GIMP_HELP_PALETTE_EDITOR_ZOOM_IN
value|"gimp-palette-editor-zoom-in"
end_define

begin_define
DECL|macro|GIMP_HELP_PALETTE_EDITOR_ZOOM_ALL
define|#
directive|define
name|GIMP_HELP_PALETTE_EDITOR_ZOOM_ALL
value|"gimp-palette-editor-zoom-all"
end_define

begin_define
DECL|macro|GIMP_HELP_PALETTE_EDITOR_EDIT_ACTIVE
define|#
directive|define
name|GIMP_HELP_PALETTE_EDITOR_EDIT_ACTIVE
value|"gimp-palette-editor-edit-active"
end_define

begin_define
DECL|macro|GIMP_HELP_FONT_DIALOG
define|#
directive|define
name|GIMP_HELP_FONT_DIALOG
value|"gimp-font-dialog"
end_define

begin_define
DECL|macro|GIMP_HELP_FONT_REFRESH
define|#
directive|define
name|GIMP_HELP_FONT_REFRESH
value|"gimp-font-refresh"
end_define

begin_define
DECL|macro|GIMP_HELP_BUFFER_DIALOG
define|#
directive|define
name|GIMP_HELP_BUFFER_DIALOG
value|"gimp-buffer-dialog"
end_define

begin_define
DECL|macro|GIMP_HELP_BUFFER_CUT
define|#
directive|define
name|GIMP_HELP_BUFFER_CUT
value|"gimp-buffer-cut"
end_define

begin_define
DECL|macro|GIMP_HELP_BUFFER_COPY
define|#
directive|define
name|GIMP_HELP_BUFFER_COPY
value|"gimp-buffer-copy"
end_define

begin_define
DECL|macro|GIMP_HELP_BUFFER_PASTE
define|#
directive|define
name|GIMP_HELP_BUFFER_PASTE
value|"gimp-buffer-paste"
end_define

begin_define
DECL|macro|GIMP_HELP_BUFFER_PASTE_INTO
define|#
directive|define
name|GIMP_HELP_BUFFER_PASTE_INTO
value|"gimp-buffer-paste-into"
end_define

begin_define
DECL|macro|GIMP_HELP_BUFFER_PASTE_AS_NEW
define|#
directive|define
name|GIMP_HELP_BUFFER_PASTE_AS_NEW
value|"gimp-buffer-paste-as-new"
end_define

begin_define
DECL|macro|GIMP_HELP_BUFFER_DELETE
define|#
directive|define
name|GIMP_HELP_BUFFER_DELETE
value|"gimp-buffer-delete"
end_define

begin_define
DECL|macro|GIMP_HELP_DOCUMENT_CLEAR
define|#
directive|define
name|GIMP_HELP_DOCUMENT_CLEAR
value|"gimp-document-clear"
end_define

begin_define
DECL|macro|GIMP_HELP_DOCUMENT_COPY_LOCATION
define|#
directive|define
name|GIMP_HELP_DOCUMENT_COPY_LOCATION
value|"gimp-document-copy-location"
end_define

begin_define
DECL|macro|GIMP_HELP_DOCUMENT_DIALOG
define|#
directive|define
name|GIMP_HELP_DOCUMENT_DIALOG
value|"gimp-document-dialog"
end_define

begin_define
DECL|macro|GIMP_HELP_DOCUMENT_OPEN
define|#
directive|define
name|GIMP_HELP_DOCUMENT_OPEN
value|"gimp-document-open"
end_define

begin_define
DECL|macro|GIMP_HELP_DOCUMENT_REMOVE
define|#
directive|define
name|GIMP_HELP_DOCUMENT_REMOVE
value|"gimp-document-remove"
end_define

begin_define
DECL|macro|GIMP_HELP_DOCUMENT_REFRESH
define|#
directive|define
name|GIMP_HELP_DOCUMENT_REFRESH
value|"gimp-document-refresh"
end_define

begin_define
DECL|macro|GIMP_HELP_TEMPLATE_DIALOG
define|#
directive|define
name|GIMP_HELP_TEMPLATE_DIALOG
value|"gimp-template-dialog"
end_define

begin_define
DECL|macro|GIMP_HELP_TEMPLATE_NEW
define|#
directive|define
name|GIMP_HELP_TEMPLATE_NEW
value|"gimp-template-new"
end_define

begin_define
DECL|macro|GIMP_HELP_TEMPLATE_DUPLICATE
define|#
directive|define
name|GIMP_HELP_TEMPLATE_DUPLICATE
value|"gimp-template-duplicate"
end_define

begin_define
DECL|macro|GIMP_HELP_TEMPLATE_EDIT
define|#
directive|define
name|GIMP_HELP_TEMPLATE_EDIT
value|"gimp-template-edit"
end_define

begin_define
DECL|macro|GIMP_HELP_TEMPLATE_IMAGE_NEW
define|#
directive|define
name|GIMP_HELP_TEMPLATE_IMAGE_NEW
value|"gimp-template-image-new"
end_define

begin_define
DECL|macro|GIMP_HELP_TEMPLATE_DELETE
define|#
directive|define
name|GIMP_HELP_TEMPLATE_DELETE
value|"gimp-template-delete"
end_define

begin_define
DECL|macro|GIMP_HELP_TOOL_OPTIONS_DIALOG
define|#
directive|define
name|GIMP_HELP_TOOL_OPTIONS_DIALOG
value|"gimp-tool-options-dialog"
end_define

begin_define
DECL|macro|GIMP_HELP_TOOL_OPTIONS_SAVE
define|#
directive|define
name|GIMP_HELP_TOOL_OPTIONS_SAVE
value|"gimp-tool-options-save"
end_define

begin_define
DECL|macro|GIMP_HELP_TOOL_OPTIONS_RESTORE
define|#
directive|define
name|GIMP_HELP_TOOL_OPTIONS_RESTORE
value|"gimp-tool-options-restore"
end_define

begin_define
DECL|macro|GIMP_HELP_TOOL_OPTIONS_RENAME
define|#
directive|define
name|GIMP_HELP_TOOL_OPTIONS_RENAME
value|"gimp-tool-options-rename"
end_define

begin_define
DECL|macro|GIMP_HELP_TOOL_OPTIONS_DELETE
define|#
directive|define
name|GIMP_HELP_TOOL_OPTIONS_DELETE
value|"gimp-tool-options-delete"
end_define

begin_define
DECL|macro|GIMP_HELP_TOOL_OPTIONS_RESET
define|#
directive|define
name|GIMP_HELP_TOOL_OPTIONS_RESET
value|"gimp-tool-options-reset"
end_define

begin_define
DECL|macro|GIMP_HELP_ERRORS_DIALOG
define|#
directive|define
name|GIMP_HELP_ERRORS_DIALOG
value|"gimp-errors-dialog"
end_define

begin_define
DECL|macro|GIMP_HELP_ERRORS_CLEAR
define|#
directive|define
name|GIMP_HELP_ERRORS_CLEAR
value|"gimp-errors-clear"
end_define

begin_define
DECL|macro|GIMP_HELP_ERRORS_SAVE
define|#
directive|define
name|GIMP_HELP_ERRORS_SAVE
value|"gimp-errors-save"
end_define

begin_define
DECL|macro|GIMP_HELP_ERRORS_SELECT_ALL
define|#
directive|define
name|GIMP_HELP_ERRORS_SELECT_ALL
value|"gimp-errors-select-all"
end_define

begin_define
DECL|macro|GIMP_HELP_PREFS_DIALOG
define|#
directive|define
name|GIMP_HELP_PREFS_DIALOG
value|"gimp-prefs-dialog"
end_define

begin_define
DECL|macro|GIMP_HELP_PREFS_NEW_IMAGE
define|#
directive|define
name|GIMP_HELP_PREFS_NEW_IMAGE
value|"gimp-prefs-new-image"
end_define

begin_define
DECL|macro|GIMP_HELP_PREFS_DEFAULT_GRID
define|#
directive|define
name|GIMP_HELP_PREFS_DEFAULT_GRID
value|"gimp-prefs-default-grid"
end_define

begin_define
DECL|macro|GIMP_HELP_PREFS_INTERFACE
define|#
directive|define
name|GIMP_HELP_PREFS_INTERFACE
value|"gimp-prefs-interface"
end_define

begin_define
DECL|macro|GIMP_HELP_PREFS_HELP
define|#
directive|define
name|GIMP_HELP_PREFS_HELP
value|"gimp-prefs-help"
end_define

begin_define
DECL|macro|GIMP_HELP_PREFS_THEME
define|#
directive|define
name|GIMP_HELP_PREFS_THEME
value|"gimp-prefs-theme"
end_define

begin_define
DECL|macro|GIMP_HELP_PREFS_TOOL_OPTIONS
define|#
directive|define
name|GIMP_HELP_PREFS_TOOL_OPTIONS
value|"gimp-prefs-tool-options"
end_define

begin_define
DECL|macro|GIMP_HELP_PREFS_TOOLBOX
define|#
directive|define
name|GIMP_HELP_PREFS_TOOLBOX
value|"gimp-prefs-toolbox"
end_define

begin_define
DECL|macro|GIMP_HELP_PREFS_INPUT_DEVICES
define|#
directive|define
name|GIMP_HELP_PREFS_INPUT_DEVICES
value|"gimp-prefs-input-devices"
end_define

begin_define
DECL|macro|GIMP_HELP_PREFS_INPUT_CONTROLLERS
define|#
directive|define
name|GIMP_HELP_PREFS_INPUT_CONTROLLERS
value|"gimp-prefs-input-controllers"
end_define

begin_define
DECL|macro|GIMP_HELP_PREFS_IMAGE_WINDOW
define|#
directive|define
name|GIMP_HELP_PREFS_IMAGE_WINDOW
value|"gimp-prefs-image-window"
end_define

begin_define
DECL|macro|GIMP_HELP_PREFS_IMAGE_WINDOW_APPEARANCE
define|#
directive|define
name|GIMP_HELP_PREFS_IMAGE_WINDOW_APPEARANCE
value|"gimp-prefs-image-window-appearance"
end_define

begin_define
DECL|macro|GIMP_HELP_PREFS_IMAGE_WINDOW_TITLE
define|#
directive|define
name|GIMP_HELP_PREFS_IMAGE_WINDOW_TITLE
value|"gimp-prefs-image-window-title"
end_define

begin_define
DECL|macro|GIMP_HELP_PREFS_DISPLAY
define|#
directive|define
name|GIMP_HELP_PREFS_DISPLAY
value|"gimp-prefs-display"
end_define

begin_define
DECL|macro|GIMP_HELP_PREFS_MONITOR
define|#
directive|define
name|GIMP_HELP_PREFS_MONITOR
value|"gimp-prefs-monitor"
end_define

begin_define
DECL|macro|GIMP_HELP_PREFS_COLOR_MANAGEMENT
define|#
directive|define
name|GIMP_HELP_PREFS_COLOR_MANAGEMENT
value|"gimp-prefs-color-management"
end_define

begin_define
DECL|macro|GIMP_HELP_PREFS_WINDOW_MANAGEMENT
define|#
directive|define
name|GIMP_HELP_PREFS_WINDOW_MANAGEMENT
value|"gimp-prefs-window-management"
end_define

begin_define
DECL|macro|GIMP_HELP_PREFS_ENVIRONMENT
define|#
directive|define
name|GIMP_HELP_PREFS_ENVIRONMENT
value|"gimp-prefs-environment"
end_define

begin_define
DECL|macro|GIMP_HELP_PREFS_SESSION
define|#
directive|define
name|GIMP_HELP_PREFS_SESSION
value|"gimp-prefs-session"
end_define

begin_define
DECL|macro|GIMP_HELP_PREFS_FOLDERS
define|#
directive|define
name|GIMP_HELP_PREFS_FOLDERS
value|"gimp-prefs-folders"
end_define

begin_define
DECL|macro|GIMP_HELP_PREFS_FOLDERS_BRUSHES
define|#
directive|define
name|GIMP_HELP_PREFS_FOLDERS_BRUSHES
value|"gimp-prefs-folders-brushes"
end_define

begin_define
DECL|macro|GIMP_HELP_PREFS_FOLDERS_DYNAMICS
define|#
directive|define
name|GIMP_HELP_PREFS_FOLDERS_DYNAMICS
value|"gimp-prefs-folders-dynamics"
end_define

begin_define
DECL|macro|GIMP_HELP_PREFS_FOLDERS_PATTERNS
define|#
directive|define
name|GIMP_HELP_PREFS_FOLDERS_PATTERNS
value|"gimp-prefs-folders-patterns"
end_define

begin_define
DECL|macro|GIMP_HELP_PREFS_FOLDERS_PALETTES
define|#
directive|define
name|GIMP_HELP_PREFS_FOLDERS_PALETTES
value|"gimp-prefs-folders-palettes"
end_define

begin_define
DECL|macro|GIMP_HELP_PREFS_FOLDERS_GRADIENTS
define|#
directive|define
name|GIMP_HELP_PREFS_FOLDERS_GRADIENTS
value|"gimp-prefs-folders-gradients"
end_define

begin_define
DECL|macro|GIMP_HELP_PREFS_FOLDERS_FONTS
define|#
directive|define
name|GIMP_HELP_PREFS_FOLDERS_FONTS
value|"gimp-prefs-folders-fonts"
end_define

begin_define
DECL|macro|GIMP_HELP_PREFS_FOLDERS_PLUG_INS
define|#
directive|define
name|GIMP_HELP_PREFS_FOLDERS_PLUG_INS
value|"gimp-prefs-folders-plug-ins"
end_define

begin_define
DECL|macro|GIMP_HELP_PREFS_FOLDERS_SCRIPTS
define|#
directive|define
name|GIMP_HELP_PREFS_FOLDERS_SCRIPTS
value|"gimp-prefs-folders-scripts"
end_define

begin_define
DECL|macro|GIMP_HELP_PREFS_FOLDERS_MODULES
define|#
directive|define
name|GIMP_HELP_PREFS_FOLDERS_MODULES
value|"gimp-prefs-folders-modules"
end_define

begin_define
DECL|macro|GIMP_HELP_PREFS_FOLDERS_INTERPRETERS
define|#
directive|define
name|GIMP_HELP_PREFS_FOLDERS_INTERPRETERS
value|"gimp-prefs-folders-interpreters"
end_define

begin_define
DECL|macro|GIMP_HELP_PREFS_FOLDERS_ENVIRONMENT
define|#
directive|define
name|GIMP_HELP_PREFS_FOLDERS_ENVIRONMENT
value|"gimp-prefs-folders-environment"
end_define

begin_define
DECL|macro|GIMP_HELP_PREFS_FOLDERS_THEMES
define|#
directive|define
name|GIMP_HELP_PREFS_FOLDERS_THEMES
value|"gimp-prefs-folders-themes"
end_define

begin_define
DECL|macro|GIMP_HELP_INPUT_DEVICES
define|#
directive|define
name|GIMP_HELP_INPUT_DEVICES
value|"gimp-help-input-devices"
end_define

begin_define
DECL|macro|GIMP_HELP_KEYBOARD_SHORTCUTS
define|#
directive|define
name|GIMP_HELP_KEYBOARD_SHORTCUTS
value|"gimp-help-keyboard-shortcuts"
end_define

begin_define
DECL|macro|GIMP_HELP_INDEXED_PALETTE_DIALOG
define|#
directive|define
name|GIMP_HELP_INDEXED_PALETTE_DIALOG
value|"gimp-indexed-palette-dialog"
end_define

begin_define
DECL|macro|GIMP_HELP_INDEXED_PALETTE_EDIT
define|#
directive|define
name|GIMP_HELP_INDEXED_PALETTE_EDIT
value|"gimp-indexed-palette-edit"
end_define

begin_define
DECL|macro|GIMP_HELP_INDEXED_PALETTE_ADD
define|#
directive|define
name|GIMP_HELP_INDEXED_PALETTE_ADD
value|"gimp-indexed-palette-add"
end_define

begin_define
DECL|macro|GIMP_HELP_POINTER_INFO_DIALOG
define|#
directive|define
name|GIMP_HELP_POINTER_INFO_DIALOG
value|"gimp-pointer-info-dialog"
end_define

begin_define
DECL|macro|GIMP_HELP_POINTER_INFO_SAMPLE_MERGED
define|#
directive|define
name|GIMP_HELP_POINTER_INFO_SAMPLE_MERGED
value|"gimp-pointer-info-sample-merged"
end_define

begin_define
DECL|macro|GIMP_HELP_SAMPLE_POINT_DIALOG
define|#
directive|define
name|GIMP_HELP_SAMPLE_POINT_DIALOG
value|"gimp-sample-point-dialog"
end_define

begin_define
DECL|macro|GIMP_HELP_SAMPLE_POINT_SAMPLE_MERGED
define|#
directive|define
name|GIMP_HELP_SAMPLE_POINT_SAMPLE_MERGED
value|"gimp-sample-point-sample-merged"
end_define

begin_define
DECL|macro|GIMP_HELP_DOCK
define|#
directive|define
name|GIMP_HELP_DOCK
value|"gimp-dock"
end_define

begin_define
DECL|macro|GIMP_HELP_DOCK_CLOSE
define|#
directive|define
name|GIMP_HELP_DOCK_CLOSE
value|"gimp-dock-close"
end_define

begin_define
DECL|macro|GIMP_HELP_DOCK_IMAGE_MENU
define|#
directive|define
name|GIMP_HELP_DOCK_IMAGE_MENU
value|"gimp-dock-image-menu"
end_define

begin_define
DECL|macro|GIMP_HELP_DOCK_AUTO_BUTTON
define|#
directive|define
name|GIMP_HELP_DOCK_AUTO_BUTTON
value|"gimp-dock-auto-button"
end_define

begin_define
DECL|macro|GIMP_HELP_DOCK_CHANGE_SCREEN
define|#
directive|define
name|GIMP_HELP_DOCK_CHANGE_SCREEN
value|"gimp-dock-change-screen"
end_define

begin_define
DECL|macro|GIMP_HELP_DOCK_SEPARATOR
define|#
directive|define
name|GIMP_HELP_DOCK_SEPARATOR
value|"gimp-dock-separator"
end_define

begin_define
DECL|macro|GIMP_HELP_DOCK_TAB_ADD
define|#
directive|define
name|GIMP_HELP_DOCK_TAB_ADD
value|"gimp-dock-tab-add"
end_define

begin_define
DECL|macro|GIMP_HELP_DOCK_TAB_CLOSE
define|#
directive|define
name|GIMP_HELP_DOCK_TAB_CLOSE
value|"gimp-dock-tab-close"
end_define

begin_define
DECL|macro|GIMP_HELP_DOCK_TAB_LOCK
define|#
directive|define
name|GIMP_HELP_DOCK_TAB_LOCK
value|"gimp-dock-tab-lock"
end_define

begin_define
DECL|macro|GIMP_HELP_DOCK_TAB_MENU
define|#
directive|define
name|GIMP_HELP_DOCK_TAB_MENU
value|"gimp-dock-tab-menu"
end_define

begin_define
DECL|macro|GIMP_HELP_DOCK_TAB_DETACH
define|#
directive|define
name|GIMP_HELP_DOCK_TAB_DETACH
value|"gimp-dock-tab-detach"
end_define

begin_define
DECL|macro|GIMP_HELP_DOCK_PREVIEW_SIZE
define|#
directive|define
name|GIMP_HELP_DOCK_PREVIEW_SIZE
value|"gimp-dock-preview-size"
end_define

begin_define
DECL|macro|GIMP_HELP_DOCK_TAB_STYLE
define|#
directive|define
name|GIMP_HELP_DOCK_TAB_STYLE
value|"gimp-dock-tab-style"
end_define

begin_define
DECL|macro|GIMP_HELP_DOCK_VIEW_AS_LIST
define|#
directive|define
name|GIMP_HELP_DOCK_VIEW_AS_LIST
value|"gimp-dock-view-as-list"
end_define

begin_define
DECL|macro|GIMP_HELP_DOCK_VIEW_AS_GRID
define|#
directive|define
name|GIMP_HELP_DOCK_VIEW_AS_GRID
value|"gimp-dock-view-as-grid"
end_define

begin_define
DECL|macro|GIMP_HELP_DOCK_SHOW_BUTTON_BAR
define|#
directive|define
name|GIMP_HELP_DOCK_SHOW_BUTTON_BAR
value|"gimp-dock-show-button-bar"
end_define

begin_define
DECL|macro|GIMP_HELP_ABOUT_DIALOG
define|#
directive|define
name|GIMP_HELP_ABOUT_DIALOG
value|"gimp-about-dialog"
end_define

begin_define
DECL|macro|GIMP_HELP_COLOR_DIALOG
define|#
directive|define
name|GIMP_HELP_COLOR_DIALOG
value|"gimp-color-dialog"
end_define

begin_define
DECL|macro|GIMP_HELP_DEVICE_STATUS_DIALOG
define|#
directive|define
name|GIMP_HELP_DEVICE_STATUS_DIALOG
value|"gimp-device-status-dialog"
end_define

begin_define
DECL|macro|GIMP_HELP_DISPLAY_FILTER_DIALOG
define|#
directive|define
name|GIMP_HELP_DISPLAY_FILTER_DIALOG
value|"gimp-display-filter-dialog"
end_define

begin_define
DECL|macro|GIMP_HELP_HISTOGRAM_DIALOG
define|#
directive|define
name|GIMP_HELP_HISTOGRAM_DIALOG
value|"gimp-histogram-dialog"
end_define

begin_define
DECL|macro|GIMP_HELP_INFO_DIALOG
define|#
directive|define
name|GIMP_HELP_INFO_DIALOG
value|"gimp-info-dialog"
end_define

begin_define
DECL|macro|GIMP_HELP_MODULE_DIALOG
define|#
directive|define
name|GIMP_HELP_MODULE_DIALOG
value|"gimp-module-dialog"
end_define

begin_define
DECL|macro|GIMP_HELP_NAVIGATION_DIALOG
define|#
directive|define
name|GIMP_HELP_NAVIGATION_DIALOG
value|"gimp-navigation-dialog"
end_define

begin_define
DECL|macro|GIMP_HELP_TEXT_EDITOR_DIALOG
define|#
directive|define
name|GIMP_HELP_TEXT_EDITOR_DIALOG
value|"gimp-text-editor-dialog"
end_define

begin_define
DECL|macro|GIMP_HELP_TIPS_DIALOG
define|#
directive|define
name|GIMP_HELP_TIPS_DIALOG
value|"gimp-tips-dialog"
end_define

begin_define
DECL|macro|GIMP_HELP_UNDO_DIALOG
define|#
directive|define
name|GIMP_HELP_UNDO_DIALOG
value|"gimp-undo-dialog"
end_define

begin_define
DECL|macro|GIMP_HELP_EXPORT_DIALOG
define|#
directive|define
name|GIMP_HELP_EXPORT_DIALOG
value|"gimp-export-dialog"
end_define

begin_define
DECL|macro|GIMP_HELP_EXPORT_CONFIRM_DIALOG
define|#
directive|define
name|GIMP_HELP_EXPORT_CONFIRM_DIALOG
value|"gimp-export-confirm-dialog"
end_define

begin_define
DECL|macro|GIMP_HELP_UNIT_DIALOG
define|#
directive|define
name|GIMP_HELP_UNIT_DIALOG
value|"gimp-unit-dialog"
end_define

begin_define
DECL|macro|GIMP_HELP_WINDOWS_SHOW_DOCK
define|#
directive|define
name|GIMP_HELP_WINDOWS_SHOW_DOCK
value|"gimp-windows-show-dock"
end_define

begin_define
DECL|macro|GIMP_HELP_WINDOWS_USE_SINGLE_WINDOW_MODE
define|#
directive|define
name|GIMP_HELP_WINDOWS_USE_SINGLE_WINDOW_MODE
value|"gimp-windows-use-single-window-mode"
end_define

begin_define
DECL|macro|GIMP_HELP_WINDOWS_OPEN_RECENT_DOCK
define|#
directive|define
name|GIMP_HELP_WINDOWS_OPEN_RECENT_DOCK
value|"gimp-windows-open-recent-dock"
end_define

begin_define
DECL|macro|GIMP_HELP_HELP
define|#
directive|define
name|GIMP_HELP_HELP
value|"gimp-help"
end_define

begin_define
DECL|macro|GIMP_HELP_HELP_CONTEXT
define|#
directive|define
name|GIMP_HELP_HELP_CONTEXT
value|"gimp-help-context"
end_define

begin_define
DECL|macro|GIMP_HELP_COLORDISPLAY_COLORBLIND
define|#
directive|define
name|GIMP_HELP_COLORDISPLAY_COLORBLIND
value|"gimp-colordisplay-colorblind"
end_define

begin_define
DECL|macro|GIMP_HELP_COLORDISPLAY_CONTRAST
define|#
directive|define
name|GIMP_HELP_COLORDISPLAY_CONTRAST
value|"gimp-colordisplay-contrast"
end_define

begin_define
DECL|macro|GIMP_HELP_COLORDISPLAY_GAMMA
define|#
directive|define
name|GIMP_HELP_COLORDISPLAY_GAMMA
value|"gimp-colordisplay-gamma"
end_define

begin_define
DECL|macro|GIMP_HELP_COLORDISPLAY_GIMP
define|#
directive|define
name|GIMP_HELP_COLORDISPLAY_GIMP
value|"gimp-colordisplay-gimp"
end_define

begin_define
DECL|macro|GIMP_HELP_COLORDISPLAY_PROOF
define|#
directive|define
name|GIMP_HELP_COLORDISPLAY_PROOF
value|"gimp-colordisplay-proof"
end_define

begin_define
DECL|macro|GIMP_HELP_COLORSELECTOR_CMYK
define|#
directive|define
name|GIMP_HELP_COLORSELECTOR_CMYK
value|"gimp-colorselector-cmyk"
end_define

begin_define
DECL|macro|GIMP_HELP_COLORSELECTOR_TRIANGLE
define|#
directive|define
name|GIMP_HELP_COLORSELECTOR_TRIANGLE
value|"gimp-colorselector-triangle"
end_define

begin_define
DECL|macro|GIMP_HELP_COLORSELECTOR_WATER
define|#
directive|define
name|GIMP_HELP_COLORSELECTOR_WATER
value|"gimp-colorselector-water"
end_define

begin_define
DECL|macro|GIMP_HELP_CONTROLLER_KEYBOARD
define|#
directive|define
name|GIMP_HELP_CONTROLLER_KEYBOARD
value|"gimp-controller-keyboard"
end_define

begin_define
DECL|macro|GIMP_HELP_CONTROLLER_LINUX_INPUT
define|#
directive|define
name|GIMP_HELP_CONTROLLER_LINUX_INPUT
value|"gimp-controller-linux-input"
end_define

begin_define
DECL|macro|GIMP_HELP_CONTROLLER_MIDI
define|#
directive|define
name|GIMP_HELP_CONTROLLER_MIDI
value|"gimp-controller-midi"
end_define

begin_define
DECL|macro|GIMP_HELP_CONTROLLER_WHEEL
define|#
directive|define
name|GIMP_HELP_CONTROLLER_WHEEL
value|"gimp-controller-wheel"
end_define

begin_define
DECL|macro|GIMP_HELP_CONFIG_USE_GEGL
define|#
directive|define
name|GIMP_HELP_CONFIG_USE_GEGL
value|"gimp-config-use-gegl"
end_define

begin_endif
endif|#
directive|endif
end_endif

begin_comment
comment|/* __GIMP_HELP_IDS_H__ */
end_comment

end_unit

