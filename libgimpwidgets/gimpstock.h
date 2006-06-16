begin_unit|revision:0.9.5;language:C;cregit-version:0.0.1
begin_comment
comment|/* LIBGIMP - The GIMP Library  * Copyright (C) 1995-1997 Peter Mattis and Spencer Kimball  *  * gimpstock.h  * Copyright (C) 2001 Michael Natterer<mitch@gimp.org>  *  * This library is free software; you can redistribute it and/or  * modify it under the terms of the GNU Lesser General Public  * License as published by the Free Software Foundation; either  * version 2 of the License, or (at your option) any later version.  *  * This library is distributed in the hope that it will be useful,  * but WITHOUT ANY WARRANTY; without even the implied warranty of  * MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the GNU  * Lesser General Public License for more details.  *  * You should have received a copy of the GNU Lesser General Public  * License along with this library; if not, write to the  * Free Software Foundation, Inc., 59 Temple Place - Suite 330,  * Boston, MA 02111-1307, USA.  */
end_comment

begin_ifndef
ifndef|#
directive|ifndef
name|__GIMP_STOCK_H__
end_ifndef

begin_define
DECL|macro|__GIMP_STOCK_H__
define|#
directive|define
name|__GIMP_STOCK_H__
end_define

begin_function_decl
name|G_BEGIN_DECLS
comment|/* For information look into the C source or the html documentation */
comment|/*  in button size:  */
DECL|macro|GIMP_STOCK_ANCHOR
define|#
directive|define
name|GIMP_STOCK_ANCHOR
value|"gimp-anchor"
DECL|macro|GIMP_STOCK_CENTER
define|#
directive|define
name|GIMP_STOCK_CENTER
value|"gimp-center"
DECL|macro|GIMP_STOCK_DUPLICATE
define|#
directive|define
name|GIMP_STOCK_DUPLICATE
value|"gimp-duplicate"
DECL|macro|GIMP_STOCK_EDIT
define|#
directive|define
name|GIMP_STOCK_EDIT
value|"gimp-edit"
DECL|macro|GIMP_STOCK_LINKED
define|#
directive|define
name|GIMP_STOCK_LINKED
value|"gimp-linked"
DECL|macro|GIMP_STOCK_PASTE_AS_NEW
define|#
directive|define
name|GIMP_STOCK_PASTE_AS_NEW
value|"gimp-paste-as-new"
DECL|macro|GIMP_STOCK_PASTE_INTO
define|#
directive|define
name|GIMP_STOCK_PASTE_INTO
value|"gimp-paste-into"
DECL|macro|GIMP_STOCK_RESET
define|#
directive|define
name|GIMP_STOCK_RESET
value|"gimp-reset"
DECL|macro|GIMP_STOCK_VISIBLE
define|#
directive|define
name|GIMP_STOCK_VISIBLE
value|"gimp-visible"
DECL|macro|GIMP_STOCK_GRADIENT_LINEAR
define|#
directive|define
name|GIMP_STOCK_GRADIENT_LINEAR
value|"gimp-gradient-linear"
DECL|macro|GIMP_STOCK_GRADIENT_BILINEAR
define|#
directive|define
name|GIMP_STOCK_GRADIENT_BILINEAR
value|"gimp-gradient-bilinear"
DECL|macro|GIMP_STOCK_GRADIENT_RADIAL
define|#
directive|define
name|GIMP_STOCK_GRADIENT_RADIAL
value|"gimp-gradient-radial"
DECL|macro|GIMP_STOCK_GRADIENT_SQUARE
define|#
directive|define
name|GIMP_STOCK_GRADIENT_SQUARE
value|"gimp-gradient-square"
DECL|macro|GIMP_STOCK_GRADIENT_CONICAL_SYMMETRIC
define|#
directive|define
name|GIMP_STOCK_GRADIENT_CONICAL_SYMMETRIC
value|"gimp-gradient-conical-symmetric"
DECL|macro|GIMP_STOCK_GRADIENT_CONICAL_ASYMMETRIC
define|#
directive|define
name|GIMP_STOCK_GRADIENT_CONICAL_ASYMMETRIC
value|"gimp-gradient-conical-asymmetric"
DECL|macro|GIMP_STOCK_GRADIENT_SHAPEBURST_ANGULAR
define|#
directive|define
name|GIMP_STOCK_GRADIENT_SHAPEBURST_ANGULAR
value|"gimp-gradient-shapeburst-angular"
DECL|macro|GIMP_STOCK_GRADIENT_SHAPEBURST_SPHERICAL
define|#
directive|define
name|GIMP_STOCK_GRADIENT_SHAPEBURST_SPHERICAL
value|"gimp-gradient-shapeburst-spherical"
DECL|macro|GIMP_STOCK_GRADIENT_SHAPEBURST_DIMPLED
define|#
directive|define
name|GIMP_STOCK_GRADIENT_SHAPEBURST_DIMPLED
value|"gimp-gradient-shapeburst-dimpled"
DECL|macro|GIMP_STOCK_GRADIENT_SPIRAL_CLOCKWISE
define|#
directive|define
name|GIMP_STOCK_GRADIENT_SPIRAL_CLOCKWISE
value|"gimp-gradient-spiral-clockwise"
DECL|macro|GIMP_STOCK_GRADIENT_SPIRAL_ANTICLOCKWISE
define|#
directive|define
name|GIMP_STOCK_GRADIENT_SPIRAL_ANTICLOCKWISE
value|"gimp-gradient-spiral-anticlockwise"
DECL|macro|GIMP_STOCK_GRAVITY_EAST
define|#
directive|define
name|GIMP_STOCK_GRAVITY_EAST
value|"gimp-gravity-east"
DECL|macro|GIMP_STOCK_GRAVITY_NORTH
define|#
directive|define
name|GIMP_STOCK_GRAVITY_NORTH
value|"gimp-gravity-north"
DECL|macro|GIMP_STOCK_GRAVITY_NORTH_EAST
define|#
directive|define
name|GIMP_STOCK_GRAVITY_NORTH_EAST
value|"gimp-gravity-north-east"
DECL|macro|GIMP_STOCK_GRAVITY_NORTH_WEST
define|#
directive|define
name|GIMP_STOCK_GRAVITY_NORTH_WEST
value|"gimp-gravity-north-west"
DECL|macro|GIMP_STOCK_GRAVITY_SOUTH
define|#
directive|define
name|GIMP_STOCK_GRAVITY_SOUTH
value|"gimp-gravity-south"
DECL|macro|GIMP_STOCK_GRAVITY_SOUTH_EAST
define|#
directive|define
name|GIMP_STOCK_GRAVITY_SOUTH_EAST
value|"gimp-gravity-south-east"
DECL|macro|GIMP_STOCK_GRAVITY_SOUTH_WEST
define|#
directive|define
name|GIMP_STOCK_GRAVITY_SOUTH_WEST
value|"gimp-gravity-south-west"
DECL|macro|GIMP_STOCK_GRAVITY_WEST
define|#
directive|define
name|GIMP_STOCK_GRAVITY_WEST
value|"gimp-gravity-west"
DECL|macro|GIMP_STOCK_HCENTER
define|#
directive|define
name|GIMP_STOCK_HCENTER
value|"gimp-hcenter"
DECL|macro|GIMP_STOCK_VCENTER
define|#
directive|define
name|GIMP_STOCK_VCENTER
value|"gimp-vcenter"
DECL|macro|GIMP_STOCK_HCHAIN
define|#
directive|define
name|GIMP_STOCK_HCHAIN
value|"gimp-hchain"
DECL|macro|GIMP_STOCK_HCHAIN_BROKEN
define|#
directive|define
name|GIMP_STOCK_HCHAIN_BROKEN
value|"gimp-hchain-broken"
DECL|macro|GIMP_STOCK_VCHAIN
define|#
directive|define
name|GIMP_STOCK_VCHAIN
value|"gimp-vchain"
DECL|macro|GIMP_STOCK_VCHAIN_BROKEN
define|#
directive|define
name|GIMP_STOCK_VCHAIN_BROKEN
value|"gimp-vchain-broken"
DECL|macro|GIMP_STOCK_SELECTION
define|#
directive|define
name|GIMP_STOCK_SELECTION
value|"gimp-selection"
DECL|macro|GIMP_STOCK_SELECTION_REPLACE
define|#
directive|define
name|GIMP_STOCK_SELECTION_REPLACE
value|"gimp-selection-replace"
DECL|macro|GIMP_STOCK_SELECTION_ADD
define|#
directive|define
name|GIMP_STOCK_SELECTION_ADD
value|"gimp-selection-add"
DECL|macro|GIMP_STOCK_SELECTION_SUBTRACT
define|#
directive|define
name|GIMP_STOCK_SELECTION_SUBTRACT
value|"gimp-selection-subtract"
DECL|macro|GIMP_STOCK_SELECTION_INTERSECT
define|#
directive|define
name|GIMP_STOCK_SELECTION_INTERSECT
value|"gimp-selection-intersect"
DECL|macro|GIMP_STOCK_SELECTION_STROKE
define|#
directive|define
name|GIMP_STOCK_SELECTION_STROKE
value|"gimp-selection-stroke"
DECL|macro|GIMP_STOCK_SELECTION_TO_CHANNEL
define|#
directive|define
name|GIMP_STOCK_SELECTION_TO_CHANNEL
value|"gimp-selection-to-channel"
DECL|macro|GIMP_STOCK_SELECTION_TO_PATH
define|#
directive|define
name|GIMP_STOCK_SELECTION_TO_PATH
value|"gimp-selection-to-path"
DECL|macro|GIMP_STOCK_PATH_STROKE
define|#
directive|define
name|GIMP_STOCK_PATH_STROKE
value|"gimp-path-stroke"
DECL|macro|GIMP_STOCK_CURVE_FREE
define|#
directive|define
name|GIMP_STOCK_CURVE_FREE
value|"gimp-curve-free"
DECL|macro|GIMP_STOCK_CURVE_SMOOTH
define|#
directive|define
name|GIMP_STOCK_CURVE_SMOOTH
value|"gimp-curve-smooth"
DECL|macro|GIMP_STOCK_COLOR_PICKER_BLACK
define|#
directive|define
name|GIMP_STOCK_COLOR_PICKER_BLACK
value|"gimp-color-picker-black"
DECL|macro|GIMP_STOCK_COLOR_PICKER_GRAY
define|#
directive|define
name|GIMP_STOCK_COLOR_PICKER_GRAY
value|"gimp-color-picker-gray"
DECL|macro|GIMP_STOCK_COLOR_PICKER_WHITE
define|#
directive|define
name|GIMP_STOCK_COLOR_PICKER_WHITE
value|"gimp-color-picker-white"
DECL|macro|GIMP_STOCK_COLOR_TRIANGLE
define|#
directive|define
name|GIMP_STOCK_COLOR_TRIANGLE
value|"gimp-color-triangle"
DECL|macro|GIMP_STOCK_COLOR_PICK_FROM_SCREEN
define|#
directive|define
name|GIMP_STOCK_COLOR_PICK_FROM_SCREEN
value|"gimp-color-pick-from-screen"
DECL|macro|GIMP_STOCK_CHAR_PICKER
define|#
directive|define
name|GIMP_STOCK_CHAR_PICKER
value|"gimp-char-picker"
DECL|macro|GIMP_STOCK_LETTER_SPACING
define|#
directive|define
name|GIMP_STOCK_LETTER_SPACING
value|"gimp-letter-spacing"
DECL|macro|GIMP_STOCK_LINE_SPACING
define|#
directive|define
name|GIMP_STOCK_LINE_SPACING
value|"gimp-line-spacing"
DECL|macro|GIMP_STOCK_PRINT_RESOLUTION
define|#
directive|define
name|GIMP_STOCK_PRINT_RESOLUTION
value|"gimp-print-resolution"
DECL|macro|GIMP_STOCK_TEXT_DIR_LTR
define|#
directive|define
name|GIMP_STOCK_TEXT_DIR_LTR
value|"gimp-text-dir-ltr"
DECL|macro|GIMP_STOCK_TEXT_DIR_RTL
define|#
directive|define
name|GIMP_STOCK_TEXT_DIR_RTL
value|"gimp-text-dir-rtl"
DECL|macro|GIMP_STOCK_TOOL_AIRBRUSH
define|#
directive|define
name|GIMP_STOCK_TOOL_AIRBRUSH
value|"gimp-tool-airbrush"
DECL|macro|GIMP_STOCK_TOOL_ALIGN
define|#
directive|define
name|GIMP_STOCK_TOOL_ALIGN
value|"gimp-tool-align"
DECL|macro|GIMP_STOCK_TOOL_BLEND
define|#
directive|define
name|GIMP_STOCK_TOOL_BLEND
value|"gimp-tool-blend"
DECL|macro|GIMP_STOCK_TOOL_BLUR
define|#
directive|define
name|GIMP_STOCK_TOOL_BLUR
value|"gimp-tool-blur"
DECL|macro|GIMP_STOCK_TOOL_BRIGHTNESS_CONTRAST
define|#
directive|define
name|GIMP_STOCK_TOOL_BRIGHTNESS_CONTRAST
value|"gimp-tool-brightness-contrast"
DECL|macro|GIMP_STOCK_TOOL_BUCKET_FILL
define|#
directive|define
name|GIMP_STOCK_TOOL_BUCKET_FILL
value|"gimp-tool-bucket-fill"
DECL|macro|GIMP_STOCK_TOOL_BY_COLOR_SELECT
define|#
directive|define
name|GIMP_STOCK_TOOL_BY_COLOR_SELECT
value|"gimp-tool-by-color-select"
DECL|macro|GIMP_STOCK_TOOL_CLONE
define|#
directive|define
name|GIMP_STOCK_TOOL_CLONE
value|"gimp-tool-clone"
DECL|macro|GIMP_STOCK_TOOL_COLOR_BALANCE
define|#
directive|define
name|GIMP_STOCK_TOOL_COLOR_BALANCE
value|"gimp-tool-color-balance"
DECL|macro|GIMP_STOCK_TOOL_COLOR_PICKER
define|#
directive|define
name|GIMP_STOCK_TOOL_COLOR_PICKER
value|"gimp-tool-color-picker"
DECL|macro|GIMP_STOCK_TOOL_COLORIZE
define|#
directive|define
name|GIMP_STOCK_TOOL_COLORIZE
value|"gimp-tool-colorize"
DECL|macro|GIMP_STOCK_TOOL_CROP
define|#
directive|define
name|GIMP_STOCK_TOOL_CROP
value|"gimp-tool-crop"
DECL|macro|GIMP_STOCK_TOOL_CURVES
define|#
directive|define
name|GIMP_STOCK_TOOL_CURVES
value|"gimp-tool-curves"
DECL|macro|GIMP_STOCK_TOOL_DODGE
define|#
directive|define
name|GIMP_STOCK_TOOL_DODGE
value|"gimp-tool-dodge"
DECL|macro|GIMP_STOCK_TOOL_ELLIPSE_SELECT
define|#
directive|define
name|GIMP_STOCK_TOOL_ELLIPSE_SELECT
value|"gimp-tool-ellipse-select"
DECL|macro|GIMP_STOCK_TOOL_ERASER
define|#
directive|define
name|GIMP_STOCK_TOOL_ERASER
value|"gimp-tool-eraser"
DECL|macro|GIMP_STOCK_TOOL_FLIP
define|#
directive|define
name|GIMP_STOCK_TOOL_FLIP
value|"gimp-tool-flip"
DECL|macro|GIMP_STOCK_TOOL_FREE_SELECT
define|#
directive|define
name|GIMP_STOCK_TOOL_FREE_SELECT
value|"gimp-tool-free-select"
DECL|macro|GIMP_STOCK_TOOL_FOREGROUND_SELECT
define|#
directive|define
name|GIMP_STOCK_TOOL_FOREGROUND_SELECT
value|"gimp-tool-foreground-select"
DECL|macro|GIMP_STOCK_TOOL_FUZZY_SELECT
define|#
directive|define
name|GIMP_STOCK_TOOL_FUZZY_SELECT
value|"gimp-tool-fuzzy-select"
DECL|macro|GIMP_STOCK_TOOL_HUE_SATURATION
define|#
directive|define
name|GIMP_STOCK_TOOL_HUE_SATURATION
value|"gimp-tool-hue-saturation"
DECL|macro|GIMP_STOCK_TOOL_INK
define|#
directive|define
name|GIMP_STOCK_TOOL_INK
value|"gimp-tool-ink"
DECL|macro|GIMP_STOCK_TOOL_ISCISSORS
define|#
directive|define
name|GIMP_STOCK_TOOL_ISCISSORS
value|"gimp-tool-iscissors"
DECL|macro|GIMP_STOCK_TOOL_LEVELS
define|#
directive|define
name|GIMP_STOCK_TOOL_LEVELS
value|"gimp-tool-levels"
DECL|macro|GIMP_STOCK_TOOL_MEASURE
define|#
directive|define
name|GIMP_STOCK_TOOL_MEASURE
value|"gimp-tool-measure"
DECL|macro|GIMP_STOCK_TOOL_MOVE
define|#
directive|define
name|GIMP_STOCK_TOOL_MOVE
value|"gimp-tool-move"
DECL|macro|GIMP_STOCK_TOOL_PAINTBRUSH
define|#
directive|define
name|GIMP_STOCK_TOOL_PAINTBRUSH
value|"gimp-tool-paintbrush"
DECL|macro|GIMP_STOCK_TOOL_PATH
define|#
directive|define
name|GIMP_STOCK_TOOL_PATH
value|"gimp-tool-path"
DECL|macro|GIMP_STOCK_TOOL_PENCIL
define|#
directive|define
name|GIMP_STOCK_TOOL_PENCIL
value|"gimp-tool-pencil"
DECL|macro|GIMP_STOCK_TOOL_PERSPECTIVE
define|#
directive|define
name|GIMP_STOCK_TOOL_PERSPECTIVE
value|"gimp-tool-perspective"
DECL|macro|GIMP_STOCK_TOOL_POSTERIZE
define|#
directive|define
name|GIMP_STOCK_TOOL_POSTERIZE
value|"gimp-tool-posterize"
DECL|macro|GIMP_STOCK_TOOL_RECT_SELECT
define|#
directive|define
name|GIMP_STOCK_TOOL_RECT_SELECT
value|"gimp-tool-rect-select"
DECL|macro|GIMP_STOCK_TOOL_ROTATE
define|#
directive|define
name|GIMP_STOCK_TOOL_ROTATE
value|"gimp-tool-rotate"
DECL|macro|GIMP_STOCK_TOOL_SCALE
define|#
directive|define
name|GIMP_STOCK_TOOL_SCALE
value|"gimp-tool-scale"
DECL|macro|GIMP_STOCK_TOOL_SHEAR
define|#
directive|define
name|GIMP_STOCK_TOOL_SHEAR
value|"gimp-tool-shear"
DECL|macro|GIMP_STOCK_TOOL_SMUDGE
define|#
directive|define
name|GIMP_STOCK_TOOL_SMUDGE
value|"gimp-tool-smudge"
DECL|macro|GIMP_STOCK_TOOL_TEXT
define|#
directive|define
name|GIMP_STOCK_TOOL_TEXT
value|"gimp-tool-text"
DECL|macro|GIMP_STOCK_TOOL_THRESHOLD
define|#
directive|define
name|GIMP_STOCK_TOOL_THRESHOLD
value|"gimp-tool-threshold"
DECL|macro|GIMP_STOCK_TOOL_ZOOM
define|#
directive|define
name|GIMP_STOCK_TOOL_ZOOM
value|"gimp-tool-zoom"
comment|/*  in menu size:  */
DECL|macro|GIMP_STOCK_CONVERT_RGB
define|#
directive|define
name|GIMP_STOCK_CONVERT_RGB
value|"gimp-convert-rgb"
DECL|macro|GIMP_STOCK_CONVERT_GRAYSCALE
define|#
directive|define
name|GIMP_STOCK_CONVERT_GRAYSCALE
value|"gimp-convert-grayscale"
DECL|macro|GIMP_STOCK_CONVERT_INDEXED
define|#
directive|define
name|GIMP_STOCK_CONVERT_INDEXED
value|"gimp-convert-indexed"
DECL|macro|GIMP_STOCK_INVERT
define|#
directive|define
name|GIMP_STOCK_INVERT
value|"gimp-invert"
DECL|macro|GIMP_STOCK_MERGE_DOWN
define|#
directive|define
name|GIMP_STOCK_MERGE_DOWN
value|"gimp-merge-down"
DECL|macro|GIMP_STOCK_LAYER_TO_IMAGESIZE
define|#
directive|define
name|GIMP_STOCK_LAYER_TO_IMAGESIZE
value|"gimp-layer-to-imagesize"
DECL|macro|GIMP_STOCK_PLUGIN
define|#
directive|define
name|GIMP_STOCK_PLUGIN
value|"gimp-plugin"
DECL|macro|GIMP_STOCK_UNDO_HISTORY
define|#
directive|define
name|GIMP_STOCK_UNDO_HISTORY
value|"gimp-undo-history"
DECL|macro|GIMP_STOCK_RESHOW_FILTER
define|#
directive|define
name|GIMP_STOCK_RESHOW_FILTER
value|"gimp-reshow-filter"
DECL|macro|GIMP_STOCK_ROTATE_90
define|#
directive|define
name|GIMP_STOCK_ROTATE_90
value|"gimp-rotate-90"
DECL|macro|GIMP_STOCK_ROTATE_180
define|#
directive|define
name|GIMP_STOCK_ROTATE_180
value|"gimp-rotate-180"
DECL|macro|GIMP_STOCK_ROTATE_270
define|#
directive|define
name|GIMP_STOCK_ROTATE_270
value|"gimp-rotate-270"
DECL|macro|GIMP_STOCK_RESIZE
define|#
directive|define
name|GIMP_STOCK_RESIZE
value|"gimp-resize"
DECL|macro|GIMP_STOCK_SCALE
define|#
directive|define
name|GIMP_STOCK_SCALE
value|"gimp-scale"
DECL|macro|GIMP_STOCK_FLIP_HORIZONTAL
define|#
directive|define
name|GIMP_STOCK_FLIP_HORIZONTAL
value|"gimp-flip-horizontal"
DECL|macro|GIMP_STOCK_FLIP_VERTICAL
define|#
directive|define
name|GIMP_STOCK_FLIP_VERTICAL
value|"gimp-flip-vertical"
DECL|macro|GIMP_STOCK_IMAGE
define|#
directive|define
name|GIMP_STOCK_IMAGE
value|"gimp-image"
DECL|macro|GIMP_STOCK_LAYER
define|#
directive|define
name|GIMP_STOCK_LAYER
value|"gimp-layer"
DECL|macro|GIMP_STOCK_TEXT_LAYER
define|#
directive|define
name|GIMP_STOCK_TEXT_LAYER
value|"gimp-text-layer"
DECL|macro|GIMP_STOCK_FLOATING_SELECTION
define|#
directive|define
name|GIMP_STOCK_FLOATING_SELECTION
value|"gimp-floating-selection"
DECL|macro|GIMP_STOCK_CHANNEL
define|#
directive|define
name|GIMP_STOCK_CHANNEL
value|"gimp-channel"
DECL|macro|GIMP_STOCK_CHANNEL_RED
define|#
directive|define
name|GIMP_STOCK_CHANNEL_RED
value|"gimp-channel-red"
DECL|macro|GIMP_STOCK_CHANNEL_GREEN
define|#
directive|define
name|GIMP_STOCK_CHANNEL_GREEN
value|"gimp-channel-green"
DECL|macro|GIMP_STOCK_CHANNEL_BLUE
define|#
directive|define
name|GIMP_STOCK_CHANNEL_BLUE
value|"gimp-channel-blue"
DECL|macro|GIMP_STOCK_CHANNEL_GRAY
define|#
directive|define
name|GIMP_STOCK_CHANNEL_GRAY
value|"gimp-channel-gray"
DECL|macro|GIMP_STOCK_CHANNEL_INDEXED
define|#
directive|define
name|GIMP_STOCK_CHANNEL_INDEXED
value|"gimp-channel-indexed"
DECL|macro|GIMP_STOCK_CHANNEL_ALPHA
define|#
directive|define
name|GIMP_STOCK_CHANNEL_ALPHA
value|"gimp-channel-alpha"
DECL|macro|GIMP_STOCK_LAYER_MASK
define|#
directive|define
name|GIMP_STOCK_LAYER_MASK
value|"gimp-layer-mask"
DECL|macro|GIMP_STOCK_PATH
define|#
directive|define
name|GIMP_STOCK_PATH
value|"gimp-path"
DECL|macro|GIMP_STOCK_TEMPLATE
define|#
directive|define
name|GIMP_STOCK_TEMPLATE
value|"gimp-template"
DECL|macro|GIMP_STOCK_TRANSPARENCY
define|#
directive|define
name|GIMP_STOCK_TRANSPARENCY
value|"gimp-transparency"
DECL|macro|GIMP_STOCK_COLORMAP
define|#
directive|define
name|GIMP_STOCK_COLORMAP
value|"gimp-colormap"
ifndef|#
directive|ifndef
name|GIMP_DISABLE_DEPRECATED
DECL|macro|GIMP_STOCK_INDEXED_PALETTE
define|#
directive|define
name|GIMP_STOCK_INDEXED_PALETTE
value|"gimp-colormap"
endif|#
directive|endif
comment|/* GIMP_DISABLE_DEPRECATED */
DECL|macro|GIMP_STOCK_IMAGES
define|#
directive|define
name|GIMP_STOCK_IMAGES
value|"gimp-images"
DECL|macro|GIMP_STOCK_LAYERS
define|#
directive|define
name|GIMP_STOCK_LAYERS
value|"gimp-layers"
DECL|macro|GIMP_STOCK_CHANNELS
define|#
directive|define
name|GIMP_STOCK_CHANNELS
value|"gimp-channels"
DECL|macro|GIMP_STOCK_PATHS
define|#
directive|define
name|GIMP_STOCK_PATHS
value|"gimp-paths"
DECL|macro|GIMP_STOCK_SELECTION_ALL
define|#
directive|define
name|GIMP_STOCK_SELECTION_ALL
value|"gimp-selection-all"
DECL|macro|GIMP_STOCK_SELECTION_NONE
define|#
directive|define
name|GIMP_STOCK_SELECTION_NONE
value|"gimp-selection-none"
DECL|macro|GIMP_STOCK_SELECTION_GROW
define|#
directive|define
name|GIMP_STOCK_SELECTION_GROW
value|"gimp-selection-grow"
DECL|macro|GIMP_STOCK_SELECTION_SHRINK
define|#
directive|define
name|GIMP_STOCK_SELECTION_SHRINK
value|"gimp-selection-shrink"
DECL|macro|GIMP_STOCK_SELECTION_BORDER
define|#
directive|define
name|GIMP_STOCK_SELECTION_BORDER
value|"gimp-selection-border"
DECL|macro|GIMP_STOCK_NAVIGATION
define|#
directive|define
name|GIMP_STOCK_NAVIGATION
value|"gimp-navigation"
DECL|macro|GIMP_STOCK_QUICK_MASK_OFF
define|#
directive|define
name|GIMP_STOCK_QUICK_MASK_OFF
value|"gimp-quick-mask-off"
DECL|macro|GIMP_STOCK_QUICK_MASK_ON
define|#
directive|define
name|GIMP_STOCK_QUICK_MASK_ON
value|"gimp-quick-mask-on"
ifndef|#
directive|ifndef
name|GIMP_DISABLE_DEPRECATED
DECL|macro|GIMP_STOCK_QMASK_OFF
define|#
directive|define
name|GIMP_STOCK_QMASK_OFF
value|"gimp-quick-mask-off"
DECL|macro|GIMP_STOCK_QMASK_ON
define|#
directive|define
name|GIMP_STOCK_QMASK_ON
value|"gimp-quick-mask-on"
endif|#
directive|endif
comment|/* GIMP_DISABLE_DEPRECATED */
DECL|macro|GIMP_STOCK_HISTOGRAM
define|#
directive|define
name|GIMP_STOCK_HISTOGRAM
value|"gimp-histogram"
DECL|macro|GIMP_STOCK_HISTOGRAM_LINEAR
define|#
directive|define
name|GIMP_STOCK_HISTOGRAM_LINEAR
value|"gimp-histogram-linear"
DECL|macro|GIMP_STOCK_HISTOGRAM_LOGARITHMIC
define|#
directive|define
name|GIMP_STOCK_HISTOGRAM_LOGARITHMIC
value|"gimp-histogram-logarithmic"
DECL|macro|GIMP_STOCK_CLOSE
define|#
directive|define
name|GIMP_STOCK_CLOSE
value|"gimp-close"
DECL|macro|GIMP_STOCK_MENU_LEFT
define|#
directive|define
name|GIMP_STOCK_MENU_LEFT
value|"gimp-menu-left"
DECL|macro|GIMP_STOCK_MENU_RIGHT
define|#
directive|define
name|GIMP_STOCK_MENU_RIGHT
value|"gimp-menu-right"
DECL|macro|GIMP_STOCK_MOVE_TO_SCREEN
define|#
directive|define
name|GIMP_STOCK_MOVE_TO_SCREEN
value|"gimp_move-to-screen"
DECL|macro|GIMP_STOCK_DEFAULT_COLORS
define|#
directive|define
name|GIMP_STOCK_DEFAULT_COLORS
value|"gimp-default-colors"
DECL|macro|GIMP_STOCK_SWAP_COLORS
define|#
directive|define
name|GIMP_STOCK_SWAP_COLORS
value|"gimp-swap-colors"
DECL|macro|GIMP_STOCK_ZOOM_FOLLOW_WINDOW
define|#
directive|define
name|GIMP_STOCK_ZOOM_FOLLOW_WINDOW
value|"gimp-zoom-follow-window"
DECL|macro|GIMP_STOCK_TOOLS
define|#
directive|define
name|GIMP_STOCK_TOOLS
value|"gimp-tools"
DECL|macro|GIMP_STOCK_TOOL_OPTIONS
define|#
directive|define
name|GIMP_STOCK_TOOL_OPTIONS
value|"gimp-tool-options"
DECL|macro|GIMP_STOCK_DEVICE_STATUS
define|#
directive|define
name|GIMP_STOCK_DEVICE_STATUS
value|"gimp-device-status"
DECL|macro|GIMP_STOCK_DISPLAY_FILTER
define|#
directive|define
name|GIMP_STOCK_DISPLAY_FILTER
value|"gimp-display-filter"
DECL|macro|GIMP_STOCK_CURSOR
define|#
directive|define
name|GIMP_STOCK_CURSOR
value|"gimp-cursor"
DECL|macro|GIMP_STOCK_SAMPLE_POINT
define|#
directive|define
name|GIMP_STOCK_SAMPLE_POINT
value|"gimp-sample-point"
DECL|macro|GIMP_STOCK_LIST
define|#
directive|define
name|GIMP_STOCK_LIST
value|"gimp-list"
DECL|macro|GIMP_STOCK_GRID
define|#
directive|define
name|GIMP_STOCK_GRID
value|"gimp-grid"
DECL|macro|GIMP_STOCK_PORTRAIT
define|#
directive|define
name|GIMP_STOCK_PORTRAIT
value|"gimp-portrait"
DECL|macro|GIMP_STOCK_LANDSCAPE
define|#
directive|define
name|GIMP_STOCK_LANDSCAPE
value|"gimp-landscape"
DECL|macro|GIMP_STOCK_WEB
define|#
directive|define
name|GIMP_STOCK_WEB
value|"gimp-web"
DECL|macro|GIMP_STOCK_VIDEO
define|#
directive|define
name|GIMP_STOCK_VIDEO
value|"gimp-video"
DECL|macro|GIMP_STOCK_SHAPE_CIRCLE
define|#
directive|define
name|GIMP_STOCK_SHAPE_CIRCLE
value|"gimp-shape-circle"
DECL|macro|GIMP_STOCK_SHAPE_DIAMOND
define|#
directive|define
name|GIMP_STOCK_SHAPE_DIAMOND
value|"gimp-shape-diamond"
DECL|macro|GIMP_STOCK_SHAPE_SQUARE
define|#
directive|define
name|GIMP_STOCK_SHAPE_SQUARE
value|"gimp-shape-square"
DECL|macro|GIMP_STOCK_CAP_BUTT
define|#
directive|define
name|GIMP_STOCK_CAP_BUTT
value|"gimp-cap-butt"
DECL|macro|GIMP_STOCK_CAP_ROUND
define|#
directive|define
name|GIMP_STOCK_CAP_ROUND
value|"gimp-cap-round"
DECL|macro|GIMP_STOCK_CAP_SQUARE
define|#
directive|define
name|GIMP_STOCK_CAP_SQUARE
value|"gimp-cap-square"
DECL|macro|GIMP_STOCK_JOIN_MITER
define|#
directive|define
name|GIMP_STOCK_JOIN_MITER
value|"gimp-join-miter"
DECL|macro|GIMP_STOCK_JOIN_ROUND
define|#
directive|define
name|GIMP_STOCK_JOIN_ROUND
value|"gimp-join-round"
DECL|macro|GIMP_STOCK_JOIN_BEVEL
define|#
directive|define
name|GIMP_STOCK_JOIN_BEVEL
value|"gimp-join-bevel"
comment|/*  in dialog size:  */
DECL|macro|GIMP_STOCK_ERROR
define|#
directive|define
name|GIMP_STOCK_ERROR
value|"gimp-error"
DECL|macro|GIMP_STOCK_INFO
define|#
directive|define
name|GIMP_STOCK_INFO
value|"gimp-info"
DECL|macro|GIMP_STOCK_QUESTION
define|#
directive|define
name|GIMP_STOCK_QUESTION
value|"gimp-question"
DECL|macro|GIMP_STOCK_WARNING
define|#
directive|define
name|GIMP_STOCK_WARNING
value|"gimp-warning"
DECL|macro|GIMP_STOCK_WILBER
define|#
directive|define
name|GIMP_STOCK_WILBER
value|"gimp-wilber"
DECL|macro|GIMP_STOCK_WILBER_EEK
define|#
directive|define
name|GIMP_STOCK_WILBER_EEK
value|"gimp-wilber-eek"
DECL|macro|GIMP_STOCK_FRAME
define|#
directive|define
name|GIMP_STOCK_FRAME
value|"gimp-frame"
DECL|macro|GIMP_STOCK_TEXTURE
define|#
directive|define
name|GIMP_STOCK_TEXTURE
value|"gimp-texture"
comment|/*  missing icons:  */
DECL|macro|GIMP_STOCK_BRUSH
define|#
directive|define
name|GIMP_STOCK_BRUSH
value|GIMP_STOCK_TOOL_PAINTBRUSH
DECL|macro|GIMP_STOCK_BUFFER
define|#
directive|define
name|GIMP_STOCK_BUFFER
value|GTK_STOCK_PASTE
DECL|macro|GIMP_STOCK_DETACH
define|#
directive|define
name|GIMP_STOCK_DETACH
value|GTK_STOCK_CONVERT
DECL|macro|GIMP_STOCK_FONT
define|#
directive|define
name|GIMP_STOCK_FONT
value|GTK_STOCK_SELECT_FONT
DECL|macro|GIMP_STOCK_GRADIENT
define|#
directive|define
name|GIMP_STOCK_GRADIENT
value|GIMP_STOCK_TOOL_BLEND
DECL|macro|GIMP_STOCK_PALETTE
define|#
directive|define
name|GIMP_STOCK_PALETTE
value|GTK_STOCK_SELECT_COLOR
DECL|macro|GIMP_STOCK_PATTERN
define|#
directive|define
name|GIMP_STOCK_PATTERN
value|GIMP_STOCK_TOOL_BUCKET_FILL
name|void
name|gimp_stock_init
parameter_list|(
name|void
parameter_list|)
function_decl|;
end_function_decl

begin_macro
name|G_END_DECLS
end_macro

begin_endif
endif|#
directive|endif
end_endif

begin_comment
comment|/* __GIMP_STOCK_H__ */
end_comment

end_unit

