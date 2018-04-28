begin_unit|revision:0.9.5;language:C;cregit-version:0.0.1
begin_comment
comment|/* LIBGIMP - The GIMP Library  * Copyright (C) 1995-1997 Peter Mattis and Spencer Kimball  *  * gimpicons.h  * Copyright (C) 2001-2015 Michael Natterer<mitch@gimp.org>  *  * This library is free software: you can redistribute it and/or  * modify it under the terms of the GNU Lesser General Public  * License as published by the Free Software Foundation; either  * version 3 of the License, or (at your option) any later version.  *  * This library is distributed in the hope that it will be useful,  * but WITHOUT ANY WARRANTY; without even the implied warranty of  * MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the GNU  * Lesser General Public License for more details.  *  * You should have received a copy of the GNU Lesser General Public  * License along with this library.  If not, see  *<http://www.gnu.org/licenses/>.  */
end_comment

begin_if
if|#
directive|if
operator|!
name|defined
argument_list|(
name|__GIMP_WIDGETS_H_INSIDE__
argument_list|)
operator|&&
operator|!
name|defined
argument_list|(
name|GIMP_WIDGETS_COMPILATION
argument_list|)
end_if

begin_error
error|#
directive|error
literal|"Only<libgimpwidgets/gimpwidgets.h> can be included directly."
end_error

begin_endif
endif|#
directive|endif
end_endif

begin_ifndef
ifndef|#
directive|ifndef
name|__GIMP_ICONS_H__
end_ifndef

begin_define
DECL|macro|__GIMP_ICONS_H__
define|#
directive|define
name|__GIMP_ICONS_H__
end_define

begin_function_decl
name|G_BEGIN_DECLS
comment|/* For information look into the C source or the html documentation */
comment|/*  random actions that don't fit in any category  */
DECL|macro|GIMP_ICON_ATTACH
define|#
directive|define
name|GIMP_ICON_ATTACH
value|"gimp-attach"
DECL|macro|GIMP_ICON_DETACH
define|#
directive|define
name|GIMP_ICON_DETACH
value|"gimp-detach"
DECL|macro|GIMP_ICON_INVERT
define|#
directive|define
name|GIMP_ICON_INVERT
value|"gimp-invert"
DECL|macro|GIMP_ICON_RESET
define|#
directive|define
name|GIMP_ICON_RESET
value|"gimp-reset"
DECL|macro|GIMP_ICON_SHRED
define|#
directive|define
name|GIMP_ICON_SHRED
value|"gimp-shred"
comment|/*  random states/things that don't fit in any category  */
DECL|macro|GIMP_ICON_BUSINESS_CARD
define|#
directive|define
name|GIMP_ICON_BUSINESS_CARD
value|"gimp-business-card"
DECL|macro|GIMP_ICON_CHAR_PICKER
define|#
directive|define
name|GIMP_ICON_CHAR_PICKER
value|"gimp-char-picker"
DECL|macro|GIMP_ICON_CURSOR
define|#
directive|define
name|GIMP_ICON_CURSOR
value|"gimp-cursor"
DECL|macro|GIMP_ICON_DISPLAY
define|#
directive|define
name|GIMP_ICON_DISPLAY
value|"gimp-display"
DECL|macro|GIMP_ICON_GEGL
define|#
directive|define
name|GIMP_ICON_GEGL
value|"gimp-gegl"
DECL|macro|GIMP_ICON_LINKED
define|#
directive|define
name|GIMP_ICON_LINKED
value|"gimp-linked"
DECL|macro|GIMP_ICON_SMARTPHONE
define|#
directive|define
name|GIMP_ICON_SMARTPHONE
value|"gimp-smartphone"
DECL|macro|GIMP_ICON_TRANSPARENCY
define|#
directive|define
name|GIMP_ICON_TRANSPARENCY
value|"gimp-transparency"
DECL|macro|GIMP_ICON_VIDEO
define|#
directive|define
name|GIMP_ICON_VIDEO
value|"gimp-video"
DECL|macro|GIMP_ICON_VISIBLE
define|#
directive|define
name|GIMP_ICON_VISIBLE
value|"gimp-visible"
DECL|macro|GIMP_ICON_WEB
define|#
directive|define
name|GIMP_ICON_WEB
value|"gimp-web"
comment|/*  random objects/entities that don't fit in any category  */
DECL|macro|GIMP_ICON_BRUSH
define|#
directive|define
name|GIMP_ICON_BRUSH
value|GIMP_ICON_TOOL_PAINTBRUSH
DECL|macro|GIMP_ICON_BUFFER
define|#
directive|define
name|GIMP_ICON_BUFFER
value|GIMP_ICON_EDIT_PASTE
DECL|macro|GIMP_ICON_COLORMAP
define|#
directive|define
name|GIMP_ICON_COLORMAP
value|"gimp-colormap"
DECL|macro|GIMP_ICON_DYNAMICS
define|#
directive|define
name|GIMP_ICON_DYNAMICS
value|"gimp-dynamics"
DECL|macro|GIMP_ICON_FILE_MANAGER
define|#
directive|define
name|GIMP_ICON_FILE_MANAGER
value|"gimp-file-manager"
DECL|macro|GIMP_ICON_FONT
define|#
directive|define
name|GIMP_ICON_FONT
value|"gtk-select-font"
DECL|macro|GIMP_ICON_GRADIENT
define|#
directive|define
name|GIMP_ICON_GRADIENT
value|GIMP_ICON_TOOL_GRADIENT
DECL|macro|GIMP_ICON_GRID
define|#
directive|define
name|GIMP_ICON_GRID
value|"gimp-grid"
DECL|macro|GIMP_ICON_INPUT_DEVICE
define|#
directive|define
name|GIMP_ICON_INPUT_DEVICE
value|"gimp-input-device"
DECL|macro|GIMP_ICON_MYPAINT_BRUSH
define|#
directive|define
name|GIMP_ICON_MYPAINT_BRUSH
value|GIMP_ICON_TOOL_MYPAINT_BRUSH
DECL|macro|GIMP_ICON_PALETTE
define|#
directive|define
name|GIMP_ICON_PALETTE
value|"gtk-select-color"
DECL|macro|GIMP_ICON_PATTERN
define|#
directive|define
name|GIMP_ICON_PATTERN
value|"gimp-pattern"
DECL|macro|GIMP_ICON_PLUGIN
define|#
directive|define
name|GIMP_ICON_PLUGIN
value|"gimp-plugin"
DECL|macro|GIMP_ICON_SAMPLE_POINT
define|#
directive|define
name|GIMP_ICON_SAMPLE_POINT
value|"gimp-sample-point"
DECL|macro|GIMP_ICON_SYMMETRY
define|#
directive|define
name|GIMP_ICON_SYMMETRY
value|"gimp-symmetry"
DECL|macro|GIMP_ICON_TEMPLATE
define|#
directive|define
name|GIMP_ICON_TEMPLATE
value|"gimp-template"
DECL|macro|GIMP_ICON_TOOL_PRESET
define|#
directive|define
name|GIMP_ICON_TOOL_PRESET
value|"gimp-tool-preset"
comment|/*  not really icons  */
DECL|macro|GIMP_ICON_FRAME
define|#
directive|define
name|GIMP_ICON_FRAME
value|"gimp-frame"
DECL|macro|GIMP_ICON_TEXTURE
define|#
directive|define
name|GIMP_ICON_TEXTURE
value|"gimp-texture"
comment|/*  icons that follow, or at least try to follow the FDO naming and  *  category conventions; and groups of icons with a common prefix;  *  all sorted alphabetically  *  *  see also:  *  https://specifications.freedesktop.org/icon-naming-spec/latest/ar01s04.html  *  *  some icons are marked with "use FDO", these shall be renamed in 3.0  *  because we duplicated FDO standard icon names  */
DECL|macro|GIMP_ICON_APPLICATION_EXIT
define|#
directive|define
name|GIMP_ICON_APPLICATION_EXIT
value|"application-exit"
DECL|macro|GIMP_ICON_ASPECT_PORTRAIT
define|#
directive|define
name|GIMP_ICON_ASPECT_PORTRAIT
value|"gimp-portrait"
DECL|macro|GIMP_ICON_ASPECT_LANDSCAPE
define|#
directive|define
name|GIMP_ICON_ASPECT_LANDSCAPE
value|"gimp-landscape"
DECL|macro|GIMP_ICON_CAP_BUTT
define|#
directive|define
name|GIMP_ICON_CAP_BUTT
value|"gimp-cap-butt"
DECL|macro|GIMP_ICON_CAP_ROUND
define|#
directive|define
name|GIMP_ICON_CAP_ROUND
value|"gimp-cap-round"
DECL|macro|GIMP_ICON_CAP_SQUARE
define|#
directive|define
name|GIMP_ICON_CAP_SQUARE
value|"gimp-cap-square"
DECL|macro|GIMP_ICON_CENTER
define|#
directive|define
name|GIMP_ICON_CENTER
value|"gimp-center"
DECL|macro|GIMP_ICON_CENTER_HORIZONTAL
define|#
directive|define
name|GIMP_ICON_CENTER_HORIZONTAL
value|"gimp-hcenter"
DECL|macro|GIMP_ICON_CENTER_VERTICAL
define|#
directive|define
name|GIMP_ICON_CENTER_VERTICAL
value|"gimp-vcenter"
DECL|macro|GIMP_ICON_CHAIN_HORIZONTAL
define|#
directive|define
name|GIMP_ICON_CHAIN_HORIZONTAL
value|"gimp-hchain"
DECL|macro|GIMP_ICON_CHAIN_HORIZONTAL_BROKEN
define|#
directive|define
name|GIMP_ICON_CHAIN_HORIZONTAL_BROKEN
value|"gimp-hchain-broken"
DECL|macro|GIMP_ICON_CHAIN_VERTICAL
define|#
directive|define
name|GIMP_ICON_CHAIN_VERTICAL
value|"gimp-vchain"
DECL|macro|GIMP_ICON_CHAIN_VERTICAL_BROKEN
define|#
directive|define
name|GIMP_ICON_CHAIN_VERTICAL_BROKEN
value|"gimp-vchain-broken"
DECL|macro|GIMP_ICON_CHANNEL
define|#
directive|define
name|GIMP_ICON_CHANNEL
value|"gimp-channel"
DECL|macro|GIMP_ICON_CHANNEL_ALPHA
define|#
directive|define
name|GIMP_ICON_CHANNEL_ALPHA
value|"gimp-channel-alpha"
DECL|macro|GIMP_ICON_CHANNEL_BLUE
define|#
directive|define
name|GIMP_ICON_CHANNEL_BLUE
value|"gimp-channel-blue"
DECL|macro|GIMP_ICON_CHANNEL_GRAY
define|#
directive|define
name|GIMP_ICON_CHANNEL_GRAY
value|"gimp-channel-gray"
DECL|macro|GIMP_ICON_CHANNEL_GREEN
define|#
directive|define
name|GIMP_ICON_CHANNEL_GREEN
value|"gimp-channel-green"
DECL|macro|GIMP_ICON_CHANNEL_INDEXED
define|#
directive|define
name|GIMP_ICON_CHANNEL_INDEXED
value|"gimp-channel-indexed"
DECL|macro|GIMP_ICON_CHANNEL_RED
define|#
directive|define
name|GIMP_ICON_CHANNEL_RED
value|"gimp-channel-red"
DECL|macro|GIMP_ICON_CLOSE
define|#
directive|define
name|GIMP_ICON_CLOSE
value|"gimp-close"
DECL|macro|GIMP_ICON_CLOSE_ALL
define|#
directive|define
name|GIMP_ICON_CLOSE_ALL
value|"gimp-close-all"
DECL|macro|GIMP_ICON_COLOR_PICKER_BLACK
define|#
directive|define
name|GIMP_ICON_COLOR_PICKER_BLACK
value|"gimp-color-picker-black"
DECL|macro|GIMP_ICON_COLOR_PICKER_GRAY
define|#
directive|define
name|GIMP_ICON_COLOR_PICKER_GRAY
value|"gimp-color-picker-gray"
DECL|macro|GIMP_ICON_COLOR_PICKER_WHITE
define|#
directive|define
name|GIMP_ICON_COLOR_PICKER_WHITE
value|"gimp-color-picker-white"
DECL|macro|GIMP_ICON_COLOR_PICK_FROM_SCREEN
define|#
directive|define
name|GIMP_ICON_COLOR_PICK_FROM_SCREEN
value|"gimp-color-pick-from-screen"
DECL|macro|GIMP_ICON_COLOR_SELECTOR_CMYK
define|#
directive|define
name|GIMP_ICON_COLOR_SELECTOR_CMYK
value|"gimp-color-cmyk"
DECL|macro|GIMP_ICON_COLOR_SELECTOR_TRIANGLE
define|#
directive|define
name|GIMP_ICON_COLOR_SELECTOR_TRIANGLE
value|"gimp-color-triangle"
DECL|macro|GIMP_ICON_COLOR_SELECTOR_WATER
define|#
directive|define
name|GIMP_ICON_COLOR_SELECTOR_WATER
value|"gimp-color-water"
DECL|macro|GIMP_ICON_COLOR_SPACE_LINEAR
define|#
directive|define
name|GIMP_ICON_COLOR_SPACE_LINEAR
value|"gimp-color-space-linear"
DECL|macro|GIMP_ICON_COLOR_SPACE_PERCEPTUAL
define|#
directive|define
name|GIMP_ICON_COLOR_SPACE_PERCEPTUAL
value|"gimp-color-space-perceptual"
DECL|macro|GIMP_ICON_COLORS_DEFAULT
define|#
directive|define
name|GIMP_ICON_COLORS_DEFAULT
value|"gimp-default-colors"
DECL|macro|GIMP_ICON_COLORS_SWAP
define|#
directive|define
name|GIMP_ICON_COLORS_SWAP
value|"gimp-swap-colors"
DECL|macro|GIMP_ICON_CONTROLLER
define|#
directive|define
name|GIMP_ICON_CONTROLLER
value|"gimp-controller"
DECL|macro|GIMP_ICON_CONTROLLER_KEYBOARD
define|#
directive|define
name|GIMP_ICON_CONTROLLER_KEYBOARD
value|"gimp-controller-keyboard"
DECL|macro|GIMP_ICON_CONTROLLER_LINUX_INPUT
define|#
directive|define
name|GIMP_ICON_CONTROLLER_LINUX_INPUT
value|"gimp-controller-linux-input"
DECL|macro|GIMP_ICON_CONTROLLER_MIDI
define|#
directive|define
name|GIMP_ICON_CONTROLLER_MIDI
value|"gimp-controller-midi"
DECL|macro|GIMP_ICON_CONTROLLER_MOUSE
define|#
directive|define
name|GIMP_ICON_CONTROLLER_MOUSE
value|GIMP_ICON_CURSOR
DECL|macro|GIMP_ICON_CONTROLLER_WHEEL
define|#
directive|define
name|GIMP_ICON_CONTROLLER_WHEEL
value|"gimp-controller-wheel"
DECL|macro|GIMP_ICON_CONVERT_RGB
define|#
directive|define
name|GIMP_ICON_CONVERT_RGB
value|"gimp-convert-rgb"
DECL|macro|GIMP_ICON_CONVERT_GRAYSCALE
define|#
directive|define
name|GIMP_ICON_CONVERT_GRAYSCALE
value|"gimp-convert-grayscale"
DECL|macro|GIMP_ICON_CONVERT_INDEXED
define|#
directive|define
name|GIMP_ICON_CONVERT_INDEXED
value|"gimp-convert-indexed"
DECL|macro|GIMP_ICON_CONVERT_PRECISION
define|#
directive|define
name|GIMP_ICON_CONVERT_PRECISION
value|GIMP_ICON_CONVERT_RGB
DECL|macro|GIMP_ICON_CURVE_FREE
define|#
directive|define
name|GIMP_ICON_CURVE_FREE
value|"gimp-curve-free"
DECL|macro|GIMP_ICON_CURVE_SMOOTH
define|#
directive|define
name|GIMP_ICON_CURVE_SMOOTH
value|"gimp-curve-smooth"
DECL|macro|GIMP_ICON_DIALOG_CHANNELS
define|#
directive|define
name|GIMP_ICON_DIALOG_CHANNELS
value|"gimp-channels"
DECL|macro|GIMP_ICON_DIALOG_DASHBOARD
define|#
directive|define
name|GIMP_ICON_DIALOG_DASHBOARD
value|"gimp-dashboard"
DECL|macro|GIMP_ICON_DIALOG_DEVICE_STATUS
define|#
directive|define
name|GIMP_ICON_DIALOG_DEVICE_STATUS
value|"gimp-device-status"
DECL|macro|GIMP_ICON_DIALOG_ERROR
define|#
directive|define
name|GIMP_ICON_DIALOG_ERROR
value|"gimp-error"
comment|/* use FDO */
DECL|macro|GIMP_ICON_DIALOG_IMAGES
define|#
directive|define
name|GIMP_ICON_DIALOG_IMAGES
value|"gimp-images"
DECL|macro|GIMP_ICON_DIALOG_INFORMATION
define|#
directive|define
name|GIMP_ICON_DIALOG_INFORMATION
value|"gimp-info"
comment|/* use FDO */
DECL|macro|GIMP_ICON_DIALOG_LAYERS
define|#
directive|define
name|GIMP_ICON_DIALOG_LAYERS
value|"gimp-layers"
DECL|macro|GIMP_ICON_DIALOG_NAVIGATION
define|#
directive|define
name|GIMP_ICON_DIALOG_NAVIGATION
value|"gimp-navigation"
DECL|macro|GIMP_ICON_DIALOG_PATHS
define|#
directive|define
name|GIMP_ICON_DIALOG_PATHS
value|"gimp-paths"
DECL|macro|GIMP_ICON_DIALOG_QUESTION
define|#
directive|define
name|GIMP_ICON_DIALOG_QUESTION
value|"gimp-question"
comment|/* use FDO */
DECL|macro|GIMP_ICON_DIALOG_RESHOW_FILTER
define|#
directive|define
name|GIMP_ICON_DIALOG_RESHOW_FILTER
value|"gimp-reshow-filter"
DECL|macro|GIMP_ICON_DIALOG_TOOLS
define|#
directive|define
name|GIMP_ICON_DIALOG_TOOLS
value|"gimp-tools"
DECL|macro|GIMP_ICON_DIALOG_TOOL_OPTIONS
define|#
directive|define
name|GIMP_ICON_DIALOG_TOOL_OPTIONS
value|"gimp-tool-options"
DECL|macro|GIMP_ICON_DIALOG_UNDO_HISTORY
define|#
directive|define
name|GIMP_ICON_DIALOG_UNDO_HISTORY
value|"gimp-undo-history"
DECL|macro|GIMP_ICON_DIALOG_WARNING
define|#
directive|define
name|GIMP_ICON_DIALOG_WARNING
value|"gimp-warning"
comment|/* use FDO */
DECL|macro|GIMP_ICON_DISPLAY_FILTER
define|#
directive|define
name|GIMP_ICON_DISPLAY_FILTER
value|"gimp-display-filter"
DECL|macro|GIMP_ICON_DISPLAY_FILTER_CLIP_WARNING
define|#
directive|define
name|GIMP_ICON_DISPLAY_FILTER_CLIP_WARNING
value|"gimp-display-filter-clip-warning"
DECL|macro|GIMP_ICON_DISPLAY_FILTER_COLORBLIND
define|#
directive|define
name|GIMP_ICON_DISPLAY_FILTER_COLORBLIND
value|"gimp-display-filter-colorblind"
DECL|macro|GIMP_ICON_DISPLAY_FILTER_CONTRAST
define|#
directive|define
name|GIMP_ICON_DISPLAY_FILTER_CONTRAST
value|"gimp-display-filter-contrast"
DECL|macro|GIMP_ICON_DISPLAY_FILTER_GAMMA
define|#
directive|define
name|GIMP_ICON_DISPLAY_FILTER_GAMMA
value|"gimp-display-filter-gamma"
DECL|macro|GIMP_ICON_DISPLAY_FILTER_LCMS
define|#
directive|define
name|GIMP_ICON_DISPLAY_FILTER_LCMS
value|"gimp-display-filter-lcms"
DECL|macro|GIMP_ICON_DISPLAY_FILTER_PROOF
define|#
directive|define
name|GIMP_ICON_DISPLAY_FILTER_PROOF
value|"gimp-display-filter-proof"
DECL|macro|GIMP_ICON_DOCUMENT_NEW
define|#
directive|define
name|GIMP_ICON_DOCUMENT_NEW
value|"document-new"
DECL|macro|GIMP_ICON_DOCUMENT_OPEN
define|#
directive|define
name|GIMP_ICON_DOCUMENT_OPEN
value|"document-open"
DECL|macro|GIMP_ICON_DOCUMENT_OPEN_RECENT
define|#
directive|define
name|GIMP_ICON_DOCUMENT_OPEN_RECENT
value|"document-open-recent"
DECL|macro|GIMP_ICON_DOCUMENT_PAGE_SETUP
define|#
directive|define
name|GIMP_ICON_DOCUMENT_PAGE_SETUP
value|"document-page-setup"
DECL|macro|GIMP_ICON_DOCUMENT_PRINT
define|#
directive|define
name|GIMP_ICON_DOCUMENT_PRINT
value|"document-print"
DECL|macro|GIMP_ICON_DOCUMENT_PRINT_RESOLUTION
define|#
directive|define
name|GIMP_ICON_DOCUMENT_PRINT_RESOLUTION
value|"document-print"
DECL|macro|GIMP_ICON_DOCUMENT_PROPERTIES
define|#
directive|define
name|GIMP_ICON_DOCUMENT_PROPERTIES
value|"document-properties"
DECL|macro|GIMP_ICON_DOCUMENT_REVERT
define|#
directive|define
name|GIMP_ICON_DOCUMENT_REVERT
value|"document-revert"
DECL|macro|GIMP_ICON_DOCUMENT_SAVE
define|#
directive|define
name|GIMP_ICON_DOCUMENT_SAVE
value|"document-save"
DECL|macro|GIMP_ICON_DOCUMENT_SAVE_AS
define|#
directive|define
name|GIMP_ICON_DOCUMENT_SAVE_AS
value|"document-save-as"
DECL|macro|GIMP_ICON_EDIT
define|#
directive|define
name|GIMP_ICON_EDIT
value|"gtk-edit"
DECL|macro|GIMP_ICON_EDIT_CLEAR
define|#
directive|define
name|GIMP_ICON_EDIT_CLEAR
value|"edit-clear"
DECL|macro|GIMP_ICON_EDIT_COPY
define|#
directive|define
name|GIMP_ICON_EDIT_COPY
value|"edit-copy"
DECL|macro|GIMP_ICON_EDIT_CUT
define|#
directive|define
name|GIMP_ICON_EDIT_CUT
value|"edit-cut"
DECL|macro|GIMP_ICON_EDIT_DELETE
define|#
directive|define
name|GIMP_ICON_EDIT_DELETE
value|"edit-delete"
DECL|macro|GIMP_ICON_EDIT_FIND
define|#
directive|define
name|GIMP_ICON_EDIT_FIND
value|"edit-find"
DECL|macro|GIMP_ICON_EDIT_PASTE
define|#
directive|define
name|GIMP_ICON_EDIT_PASTE
value|"edit-paste"
DECL|macro|GIMP_ICON_EDIT_PASTE_AS_NEW
define|#
directive|define
name|GIMP_ICON_EDIT_PASTE_AS_NEW
value|"gimp-paste-as-new"
DECL|macro|GIMP_ICON_EDIT_PASTE_INTO
define|#
directive|define
name|GIMP_ICON_EDIT_PASTE_INTO
value|"gimp-paste-into"
DECL|macro|GIMP_ICON_EDIT_REDO
define|#
directive|define
name|GIMP_ICON_EDIT_REDO
value|"edit-redo"
DECL|macro|GIMP_ICON_EDIT_UNDO
define|#
directive|define
name|GIMP_ICON_EDIT_UNDO
value|"edit-undo"
DECL|macro|GIMP_ICON_FILL_HORIZONTAL
define|#
directive|define
name|GIMP_ICON_FILL_HORIZONTAL
value|"gimp-hfill"
DECL|macro|GIMP_ICON_FILL_VERTICAL
define|#
directive|define
name|GIMP_ICON_FILL_VERTICAL
value|"gimp-vfill"
DECL|macro|GIMP_ICON_FOLDER_NEW
define|#
directive|define
name|GIMP_ICON_FOLDER_NEW
value|"folder-new"
DECL|macro|GIMP_ICON_FORMAT_INDENT_MORE
define|#
directive|define
name|GIMP_ICON_FORMAT_INDENT_MORE
value|"format-indent-more"
DECL|macro|GIMP_ICON_FORMAT_INDENT_LESS
define|#
directive|define
name|GIMP_ICON_FORMAT_INDENT_LESS
value|"format-indent-less"
DECL|macro|GIMP_ICON_FORMAT_JUSTIFY_CENTER
define|#
directive|define
name|GIMP_ICON_FORMAT_JUSTIFY_CENTER
value|"format-justify-center"
DECL|macro|GIMP_ICON_FORMAT_JUSTIFY_FILL
define|#
directive|define
name|GIMP_ICON_FORMAT_JUSTIFY_FILL
value|"format-justify-fill"
DECL|macro|GIMP_ICON_FORMAT_JUSTIFY_LEFT
define|#
directive|define
name|GIMP_ICON_FORMAT_JUSTIFY_LEFT
value|"format-justify-left"
DECL|macro|GIMP_ICON_FORMAT_JUSTIFY_RIGHT
define|#
directive|define
name|GIMP_ICON_FORMAT_JUSTIFY_RIGHT
value|"format-justify-right"
DECL|macro|GIMP_ICON_FORMAT_TEXT_BOLD
define|#
directive|define
name|GIMP_ICON_FORMAT_TEXT_BOLD
value|"format-text-bold"
DECL|macro|GIMP_ICON_FORMAT_TEXT_ITALIC
define|#
directive|define
name|GIMP_ICON_FORMAT_TEXT_ITALIC
value|"format-text-italic"
DECL|macro|GIMP_ICON_FORMAT_TEXT_STRIKETHROUGH
define|#
directive|define
name|GIMP_ICON_FORMAT_TEXT_STRIKETHROUGH
value|"format-text-strikethrough"
DECL|macro|GIMP_ICON_FORMAT_TEXT_UNDERLINE
define|#
directive|define
name|GIMP_ICON_FORMAT_TEXT_UNDERLINE
value|"format-text-underline"
DECL|macro|GIMP_ICON_FORMAT_TEXT_DIRECTION_LTR
define|#
directive|define
name|GIMP_ICON_FORMAT_TEXT_DIRECTION_LTR
value|"gimp-text-dir-ltr"
comment|/* use FDO */
DECL|macro|GIMP_ICON_FORMAT_TEXT_DIRECTION_RTL
define|#
directive|define
name|GIMP_ICON_FORMAT_TEXT_DIRECTION_RTL
value|"gimp-text-dir-rtl"
comment|/* use FDO */
DECL|macro|GIMP_ICON_FORMAT_TEXT_SPACING_LETTER
define|#
directive|define
name|GIMP_ICON_FORMAT_TEXT_SPACING_LETTER
value|"gimp-letter-spacing"
DECL|macro|GIMP_ICON_FORMAT_TEXT_SPACING_LINE
define|#
directive|define
name|GIMP_ICON_FORMAT_TEXT_SPACING_LINE
value|"gimp-line-spacing"
DECL|macro|GIMP_ICON_GRADIENT_LINEAR
define|#
directive|define
name|GIMP_ICON_GRADIENT_LINEAR
value|"gimp-gradient-linear"
DECL|macro|GIMP_ICON_GRADIENT_BILINEAR
define|#
directive|define
name|GIMP_ICON_GRADIENT_BILINEAR
value|"gimp-gradient-bilinear"
DECL|macro|GIMP_ICON_GRADIENT_RADIAL
define|#
directive|define
name|GIMP_ICON_GRADIENT_RADIAL
value|"gimp-gradient-radial"
DECL|macro|GIMP_ICON_GRADIENT_SQUARE
define|#
directive|define
name|GIMP_ICON_GRADIENT_SQUARE
value|"gimp-gradient-square"
DECL|macro|GIMP_ICON_GRADIENT_CONICAL_SYMMETRIC
define|#
directive|define
name|GIMP_ICON_GRADIENT_CONICAL_SYMMETRIC
value|"gimp-gradient-conical-symmetric"
DECL|macro|GIMP_ICON_GRADIENT_CONICAL_ASYMMETRIC
define|#
directive|define
name|GIMP_ICON_GRADIENT_CONICAL_ASYMMETRIC
value|"gimp-gradient-conical-asymmetric"
DECL|macro|GIMP_ICON_GRADIENT_SHAPEBURST_ANGULAR
define|#
directive|define
name|GIMP_ICON_GRADIENT_SHAPEBURST_ANGULAR
value|"gimp-gradient-shapeburst-angular"
DECL|macro|GIMP_ICON_GRADIENT_SHAPEBURST_SPHERICAL
define|#
directive|define
name|GIMP_ICON_GRADIENT_SHAPEBURST_SPHERICAL
value|"gimp-gradient-shapeburst-spherical"
DECL|macro|GIMP_ICON_GRADIENT_SHAPEBURST_DIMPLED
define|#
directive|define
name|GIMP_ICON_GRADIENT_SHAPEBURST_DIMPLED
value|"gimp-gradient-shapeburst-dimpled"
DECL|macro|GIMP_ICON_GRADIENT_SPIRAL_CLOCKWISE
define|#
directive|define
name|GIMP_ICON_GRADIENT_SPIRAL_CLOCKWISE
value|"gimp-gradient-spiral-clockwise"
DECL|macro|GIMP_ICON_GRADIENT_SPIRAL_ANTICLOCKWISE
define|#
directive|define
name|GIMP_ICON_GRADIENT_SPIRAL_ANTICLOCKWISE
value|"gimp-gradient-spiral-anticlockwise"
DECL|macro|GIMP_ICON_GRAVITY_EAST
define|#
directive|define
name|GIMP_ICON_GRAVITY_EAST
value|"gimp-gravity-east"
DECL|macro|GIMP_ICON_GRAVITY_NORTH
define|#
directive|define
name|GIMP_ICON_GRAVITY_NORTH
value|"gimp-gravity-north"
DECL|macro|GIMP_ICON_GRAVITY_NORTH_EAST
define|#
directive|define
name|GIMP_ICON_GRAVITY_NORTH_EAST
value|"gimp-gravity-north-east"
DECL|macro|GIMP_ICON_GRAVITY_NORTH_WEST
define|#
directive|define
name|GIMP_ICON_GRAVITY_NORTH_WEST
value|"gimp-gravity-north-west"
DECL|macro|GIMP_ICON_GRAVITY_SOUTH
define|#
directive|define
name|GIMP_ICON_GRAVITY_SOUTH
value|"gimp-gravity-south"
DECL|macro|GIMP_ICON_GRAVITY_SOUTH_EAST
define|#
directive|define
name|GIMP_ICON_GRAVITY_SOUTH_EAST
value|"gimp-gravity-south-east"
DECL|macro|GIMP_ICON_GRAVITY_SOUTH_WEST
define|#
directive|define
name|GIMP_ICON_GRAVITY_SOUTH_WEST
value|"gimp-gravity-south-west"
DECL|macro|GIMP_ICON_GRAVITY_WEST
define|#
directive|define
name|GIMP_ICON_GRAVITY_WEST
value|"gimp-gravity-west"
DECL|macro|GIMP_ICON_GO_BOTTOM
define|#
directive|define
name|GIMP_ICON_GO_BOTTOM
value|"go-bottom"
DECL|macro|GIMP_ICON_GO_DOWN
define|#
directive|define
name|GIMP_ICON_GO_DOWN
value|"go-down"
DECL|macro|GIMP_ICON_GO_FIRST
define|#
directive|define
name|GIMP_ICON_GO_FIRST
value|"go-first"
DECL|macro|GIMP_ICON_GO_HOME
define|#
directive|define
name|GIMP_ICON_GO_HOME
value|"go-home"
DECL|macro|GIMP_ICON_GO_LAST
define|#
directive|define
name|GIMP_ICON_GO_LAST
value|"go-last"
DECL|macro|GIMP_ICON_GO_TOP
define|#
directive|define
name|GIMP_ICON_GO_TOP
value|"go-top"
DECL|macro|GIMP_ICON_GO_UP
define|#
directive|define
name|GIMP_ICON_GO_UP
value|"go-up"
DECL|macro|GIMP_ICON_GO_PREVIOUS
define|#
directive|define
name|GIMP_ICON_GO_PREVIOUS
value|"go-previous"
DECL|macro|GIMP_ICON_GO_NEXT
define|#
directive|define
name|GIMP_ICON_GO_NEXT
value|"go-next"
DECL|macro|GIMP_ICON_HELP
define|#
directive|define
name|GIMP_ICON_HELP
value|"help"
DECL|macro|GIMP_ICON_HELP_ABOUT
define|#
directive|define
name|GIMP_ICON_HELP_ABOUT
value|"help-about"
DECL|macro|GIMP_ICON_HELP_USER_MANUAL
define|#
directive|define
name|GIMP_ICON_HELP_USER_MANUAL
value|"gimp-user-manual"
DECL|macro|GIMP_ICON_HISTOGRAM
define|#
directive|define
name|GIMP_ICON_HISTOGRAM
value|"gimp-histogram"
DECL|macro|GIMP_ICON_HISTOGRAM_LINEAR
define|#
directive|define
name|GIMP_ICON_HISTOGRAM_LINEAR
value|"gimp-histogram-linear"
DECL|macro|GIMP_ICON_HISTOGRAM_LOGARITHMIC
define|#
directive|define
name|GIMP_ICON_HISTOGRAM_LOGARITHMIC
value|"gimp-histogram-logarithmic"
DECL|macro|GIMP_ICON_IMAGE
define|#
directive|define
name|GIMP_ICON_IMAGE
value|"gimp-image"
DECL|macro|GIMP_ICON_IMAGE_OPEN
define|#
directive|define
name|GIMP_ICON_IMAGE_OPEN
value|"gimp-image-open"
DECL|macro|GIMP_ICON_IMAGE_RELOAD
define|#
directive|define
name|GIMP_ICON_IMAGE_RELOAD
value|"gimp-image-reload"
DECL|macro|GIMP_ICON_JOIN_MITER
define|#
directive|define
name|GIMP_ICON_JOIN_MITER
value|"gimp-join-miter"
DECL|macro|GIMP_ICON_JOIN_ROUND
define|#
directive|define
name|GIMP_ICON_JOIN_ROUND
value|"gimp-join-round"
DECL|macro|GIMP_ICON_JOIN_BEVEL
define|#
directive|define
name|GIMP_ICON_JOIN_BEVEL
value|"gimp-join-bevel"
DECL|macro|GIMP_ICON_LAYER
define|#
directive|define
name|GIMP_ICON_LAYER
value|"gimp-layer"
DECL|macro|GIMP_ICON_LAYER_ANCHOR
define|#
directive|define
name|GIMP_ICON_LAYER_ANCHOR
value|"gimp-anchor"
DECL|macro|GIMP_ICON_LAYER_FLOATING_SELECTION
define|#
directive|define
name|GIMP_ICON_LAYER_FLOATING_SELECTION
value|"gimp-floating-selection"
DECL|macro|GIMP_ICON_LAYER_MASK
define|#
directive|define
name|GIMP_ICON_LAYER_MASK
value|"gimp-layer-mask"
DECL|macro|GIMP_ICON_LAYER_MERGE_DOWN
define|#
directive|define
name|GIMP_ICON_LAYER_MERGE_DOWN
value|"gimp-merge-down"
DECL|macro|GIMP_ICON_LAYER_TEXT_LAYER
define|#
directive|define
name|GIMP_ICON_LAYER_TEXT_LAYER
value|"gimp-text-layer"
DECL|macro|GIMP_ICON_LAYER_TO_IMAGESIZE
define|#
directive|define
name|GIMP_ICON_LAYER_TO_IMAGESIZE
value|"gimp-layer-to-imagesize"
DECL|macro|GIMP_ICON_LIST
define|#
directive|define
name|GIMP_ICON_LIST
value|"gimp-list"
DECL|macro|GIMP_ICON_LIST_ADD
define|#
directive|define
name|GIMP_ICON_LIST_ADD
value|"list-add"
DECL|macro|GIMP_ICON_LIST_REMOVE
define|#
directive|define
name|GIMP_ICON_LIST_REMOVE
value|"list-remove"
DECL|macro|GIMP_ICON_MENU_LEFT
define|#
directive|define
name|GIMP_ICON_MENU_LEFT
value|"gimp-menu-left"
DECL|macro|GIMP_ICON_MENU_RIGHT
define|#
directive|define
name|GIMP_ICON_MENU_RIGHT
value|"gimp-menu-right"
DECL|macro|GIMP_ICON_OBJECT_DUPLICATE
define|#
directive|define
name|GIMP_ICON_OBJECT_DUPLICATE
value|"gimp-duplicate"
DECL|macro|GIMP_ICON_OBJECT_FLIP_HORIZONTAL
define|#
directive|define
name|GIMP_ICON_OBJECT_FLIP_HORIZONTAL
value|"gimp-flip-horizontal"
comment|/* use FDO */
DECL|macro|GIMP_ICON_OBJECT_FLIP_VERTICAL
define|#
directive|define
name|GIMP_ICON_OBJECT_FLIP_VERTICAL
value|"gimp-flip-vertical"
comment|/* use FDO */
DECL|macro|GIMP_ICON_OBJECT_RESIZE
define|#
directive|define
name|GIMP_ICON_OBJECT_RESIZE
value|"gimp-resize"
DECL|macro|GIMP_ICON_OBJECT_ROTATE_180
define|#
directive|define
name|GIMP_ICON_OBJECT_ROTATE_180
value|"gimp-rotate-180"
DECL|macro|GIMP_ICON_OBJECT_ROTATE_270
define|#
directive|define
name|GIMP_ICON_OBJECT_ROTATE_270
value|"gimp-rotate-270"
comment|/* use FDO */
DECL|macro|GIMP_ICON_OBJECT_ROTATE_90
define|#
directive|define
name|GIMP_ICON_OBJECT_ROTATE_90
value|"gimp-rotate-90"
comment|/* use FDO */
DECL|macro|GIMP_ICON_OBJECT_SCALE
define|#
directive|define
name|GIMP_ICON_OBJECT_SCALE
value|"gimp-scale"
DECL|macro|GIMP_ICON_PATH
define|#
directive|define
name|GIMP_ICON_PATH
value|"gimp-path"
DECL|macro|GIMP_ICON_PATH_STROKE
define|#
directive|define
name|GIMP_ICON_PATH_STROKE
value|"gimp-path-stroke"
DECL|macro|GIMP_ICON_PREFERENCES_SYSTEM
define|#
directive|define
name|GIMP_ICON_PREFERENCES_SYSTEM
value|"preferences-system"
DECL|macro|GIMP_ICON_PROCESS_STOP
define|#
directive|define
name|GIMP_ICON_PROCESS_STOP
value|"process-stop"
DECL|macro|GIMP_ICON_QUICK_MASK_OFF
define|#
directive|define
name|GIMP_ICON_QUICK_MASK_OFF
value|"gimp-quick-mask-off"
DECL|macro|GIMP_ICON_QUICK_MASK_ON
define|#
directive|define
name|GIMP_ICON_QUICK_MASK_ON
value|"gimp-quick-mask-on"
DECL|macro|GIMP_ICON_SELECTION
define|#
directive|define
name|GIMP_ICON_SELECTION
value|"gimp-selection"
DECL|macro|GIMP_ICON_SELECTION_ADD
define|#
directive|define
name|GIMP_ICON_SELECTION_ADD
value|"gimp-selection-add"
DECL|macro|GIMP_ICON_SELECTION_ALL
define|#
directive|define
name|GIMP_ICON_SELECTION_ALL
value|"gimp-selection-all"
DECL|macro|GIMP_ICON_SELECTION_BORDER
define|#
directive|define
name|GIMP_ICON_SELECTION_BORDER
value|"gimp-selection-border"
DECL|macro|GIMP_ICON_SELECTION_GROW
define|#
directive|define
name|GIMP_ICON_SELECTION_GROW
value|"gimp-selection-grow"
DECL|macro|GIMP_ICON_SELECTION_INTERSECT
define|#
directive|define
name|GIMP_ICON_SELECTION_INTERSECT
value|"gimp-selection-intersect"
DECL|macro|GIMP_ICON_SELECTION_NONE
define|#
directive|define
name|GIMP_ICON_SELECTION_NONE
value|"gimp-selection-none"
DECL|macro|GIMP_ICON_SELECTION_REPLACE
define|#
directive|define
name|GIMP_ICON_SELECTION_REPLACE
value|"gimp-selection-replace"
DECL|macro|GIMP_ICON_SELECTION_SHRINK
define|#
directive|define
name|GIMP_ICON_SELECTION_SHRINK
value|"gimp-selection-shrink"
DECL|macro|GIMP_ICON_SELECTION_STROKE
define|#
directive|define
name|GIMP_ICON_SELECTION_STROKE
value|"gimp-selection-stroke"
DECL|macro|GIMP_ICON_SELECTION_SUBTRACT
define|#
directive|define
name|GIMP_ICON_SELECTION_SUBTRACT
value|"gimp-selection-subtract"
DECL|macro|GIMP_ICON_SELECTION_TO_CHANNEL
define|#
directive|define
name|GIMP_ICON_SELECTION_TO_CHANNEL
value|"gimp-selection-to-channel"
DECL|macro|GIMP_ICON_SELECTION_TO_PATH
define|#
directive|define
name|GIMP_ICON_SELECTION_TO_PATH
value|"gimp-selection-to-path"
DECL|macro|GIMP_ICON_SHAPE_CIRCLE
define|#
directive|define
name|GIMP_ICON_SHAPE_CIRCLE
value|"gimp-shape-circle"
DECL|macro|GIMP_ICON_SHAPE_DIAMOND
define|#
directive|define
name|GIMP_ICON_SHAPE_DIAMOND
value|"gimp-shape-diamond"
DECL|macro|GIMP_ICON_SHAPE_SQUARE
define|#
directive|define
name|GIMP_ICON_SHAPE_SQUARE
value|"gimp-shape-square"
DECL|macro|GIMP_ICON_SYSTEM_RUN
define|#
directive|define
name|GIMP_ICON_SYSTEM_RUN
value|"system-run"
DECL|macro|GIMP_ICON_TOOL_AIRBRUSH
define|#
directive|define
name|GIMP_ICON_TOOL_AIRBRUSH
value|"gimp-tool-airbrush"
DECL|macro|GIMP_ICON_TOOL_ALIGN
define|#
directive|define
name|GIMP_ICON_TOOL_ALIGN
value|"gimp-tool-align"
DECL|macro|GIMP_ICON_TOOL_BLUR
define|#
directive|define
name|GIMP_ICON_TOOL_BLUR
value|"gimp-tool-blur"
DECL|macro|GIMP_ICON_TOOL_BRIGHTNESS_CONTRAST
define|#
directive|define
name|GIMP_ICON_TOOL_BRIGHTNESS_CONTRAST
value|"gimp-tool-brightness-contrast"
DECL|macro|GIMP_ICON_TOOL_BUCKET_FILL
define|#
directive|define
name|GIMP_ICON_TOOL_BUCKET_FILL
value|"gimp-tool-bucket-fill"
DECL|macro|GIMP_ICON_TOOL_BY_COLOR_SELECT
define|#
directive|define
name|GIMP_ICON_TOOL_BY_COLOR_SELECT
value|"gimp-tool-by-color-select"
DECL|macro|GIMP_ICON_TOOL_CAGE
define|#
directive|define
name|GIMP_ICON_TOOL_CAGE
value|"gimp-tool-cage"
DECL|macro|GIMP_ICON_TOOL_CLONE
define|#
directive|define
name|GIMP_ICON_TOOL_CLONE
value|"gimp-tool-clone"
DECL|macro|GIMP_ICON_TOOL_COLORIZE
define|#
directive|define
name|GIMP_ICON_TOOL_COLORIZE
value|"gimp-tool-colorize"
DECL|macro|GIMP_ICON_TOOL_COLOR_BALANCE
define|#
directive|define
name|GIMP_ICON_TOOL_COLOR_BALANCE
value|"gimp-tool-color-balance"
DECL|macro|GIMP_ICON_TOOL_COLOR_PICKER
define|#
directive|define
name|GIMP_ICON_TOOL_COLOR_PICKER
value|"gimp-tool-color-picker"
DECL|macro|GIMP_ICON_TOOL_COLOR_TEMPERATURE
define|#
directive|define
name|GIMP_ICON_TOOL_COLOR_TEMPERATURE
value|"gimp-tool-color-temperature"
DECL|macro|GIMP_ICON_TOOL_CROP
define|#
directive|define
name|GIMP_ICON_TOOL_CROP
value|"gimp-tool-crop"
DECL|macro|GIMP_ICON_TOOL_CURVES
define|#
directive|define
name|GIMP_ICON_TOOL_CURVES
value|"gimp-tool-curves"
DECL|macro|GIMP_ICON_TOOL_DESATURATE
define|#
directive|define
name|GIMP_ICON_TOOL_DESATURATE
value|"gimp-tool-desaturate"
DECL|macro|GIMP_ICON_TOOL_DODGE
define|#
directive|define
name|GIMP_ICON_TOOL_DODGE
value|"gimp-tool-dodge"
DECL|macro|GIMP_ICON_TOOL_ELLIPSE_SELECT
define|#
directive|define
name|GIMP_ICON_TOOL_ELLIPSE_SELECT
value|"gimp-tool-ellipse-select"
DECL|macro|GIMP_ICON_TOOL_ERASER
define|#
directive|define
name|GIMP_ICON_TOOL_ERASER
value|"gimp-tool-eraser"
DECL|macro|GIMP_ICON_TOOL_EXPOSURE
define|#
directive|define
name|GIMP_ICON_TOOL_EXPOSURE
value|"gimp-tool-exposure"
DECL|macro|GIMP_ICON_TOOL_FLIP
define|#
directive|define
name|GIMP_ICON_TOOL_FLIP
value|"gimp-tool-flip"
DECL|macro|GIMP_ICON_TOOL_FOREGROUND_SELECT
define|#
directive|define
name|GIMP_ICON_TOOL_FOREGROUND_SELECT
value|"gimp-tool-foreground-select"
DECL|macro|GIMP_ICON_TOOL_FREE_SELECT
define|#
directive|define
name|GIMP_ICON_TOOL_FREE_SELECT
value|"gimp-tool-free-select"
DECL|macro|GIMP_ICON_TOOL_FUZZY_SELECT
define|#
directive|define
name|GIMP_ICON_TOOL_FUZZY_SELECT
value|"gimp-tool-fuzzy-select"
DECL|macro|GIMP_ICON_TOOL_GRADIENT
define|#
directive|define
name|GIMP_ICON_TOOL_GRADIENT
value|"gimp-tool-gradient"
DECL|macro|GIMP_ICON_TOOL_HANDLE_TRANSFORM
define|#
directive|define
name|GIMP_ICON_TOOL_HANDLE_TRANSFORM
value|"gimp-tool-handle-transform"
DECL|macro|GIMP_ICON_TOOL_HEAL
define|#
directive|define
name|GIMP_ICON_TOOL_HEAL
value|"gimp-tool-heal"
DECL|macro|GIMP_ICON_TOOL_HUE_SATURATION
define|#
directive|define
name|GIMP_ICON_TOOL_HUE_SATURATION
value|"gimp-tool-hue-saturation"
DECL|macro|GIMP_ICON_TOOL_INK
define|#
directive|define
name|GIMP_ICON_TOOL_INK
value|"gimp-tool-ink"
DECL|macro|GIMP_ICON_TOOL_ISCISSORS
define|#
directive|define
name|GIMP_ICON_TOOL_ISCISSORS
value|"gimp-tool-iscissors"
DECL|macro|GIMP_ICON_TOOL_LEVELS
define|#
directive|define
name|GIMP_ICON_TOOL_LEVELS
value|"gimp-tool-levels"
DECL|macro|GIMP_ICON_TOOL_MEASURE
define|#
directive|define
name|GIMP_ICON_TOOL_MEASURE
value|"gimp-tool-measure"
DECL|macro|GIMP_ICON_TOOL_MOVE
define|#
directive|define
name|GIMP_ICON_TOOL_MOVE
value|"gimp-tool-move"
DECL|macro|GIMP_ICON_TOOL_MYPAINT_BRUSH
define|#
directive|define
name|GIMP_ICON_TOOL_MYPAINT_BRUSH
value|"gimp-tool-mypaint-brush"
DECL|macro|GIMP_ICON_TOOL_N_POINT_DEFORMATION
define|#
directive|define
name|GIMP_ICON_TOOL_N_POINT_DEFORMATION
value|"gimp-tool-n-point-deformation"
DECL|macro|GIMP_ICON_TOOL_PAINTBRUSH
define|#
directive|define
name|GIMP_ICON_TOOL_PAINTBRUSH
value|"gimp-tool-paintbrush"
DECL|macro|GIMP_ICON_TOOL_PATH
define|#
directive|define
name|GIMP_ICON_TOOL_PATH
value|"gimp-tool-path"
DECL|macro|GIMP_ICON_TOOL_PENCIL
define|#
directive|define
name|GIMP_ICON_TOOL_PENCIL
value|"gimp-tool-pencil"
DECL|macro|GIMP_ICON_TOOL_PERSPECTIVE
define|#
directive|define
name|GIMP_ICON_TOOL_PERSPECTIVE
value|"gimp-tool-perspective"
DECL|macro|GIMP_ICON_TOOL_PERSPECTIVE_CLONE
define|#
directive|define
name|GIMP_ICON_TOOL_PERSPECTIVE_CLONE
value|"gimp-tool-perspective-clone"
DECL|macro|GIMP_ICON_TOOL_POSTERIZE
define|#
directive|define
name|GIMP_ICON_TOOL_POSTERIZE
value|"gimp-tool-posterize"
DECL|macro|GIMP_ICON_TOOL_RECT_SELECT
define|#
directive|define
name|GIMP_ICON_TOOL_RECT_SELECT
value|"gimp-tool-rect-select"
DECL|macro|GIMP_ICON_TOOL_ROTATE
define|#
directive|define
name|GIMP_ICON_TOOL_ROTATE
value|"gimp-tool-rotate"
DECL|macro|GIMP_ICON_TOOL_SCALE
define|#
directive|define
name|GIMP_ICON_TOOL_SCALE
value|"gimp-tool-scale"
DECL|macro|GIMP_ICON_TOOL_SEAMLESS_CLONE
define|#
directive|define
name|GIMP_ICON_TOOL_SEAMLESS_CLONE
value|"gimp-tool-seamless-clone"
DECL|macro|GIMP_ICON_TOOL_SHADOWS_HIGHLIGHTS
define|#
directive|define
name|GIMP_ICON_TOOL_SHADOWS_HIGHLIGHTS
value|"gimp-tool-shadows-highlights"
DECL|macro|GIMP_ICON_TOOL_SHEAR
define|#
directive|define
name|GIMP_ICON_TOOL_SHEAR
value|"gimp-tool-shear"
DECL|macro|GIMP_ICON_TOOL_SMUDGE
define|#
directive|define
name|GIMP_ICON_TOOL_SMUDGE
value|"gimp-tool-smudge"
DECL|macro|GIMP_ICON_TOOL_TEXT
define|#
directive|define
name|GIMP_ICON_TOOL_TEXT
value|"gimp-tool-text"
DECL|macro|GIMP_ICON_TOOL_THRESHOLD
define|#
directive|define
name|GIMP_ICON_TOOL_THRESHOLD
value|"gimp-tool-threshold"
DECL|macro|GIMP_ICON_TOOL_UNIFIED_TRANSFORM
define|#
directive|define
name|GIMP_ICON_TOOL_UNIFIED_TRANSFORM
value|"gimp-tool-unified-transform"
DECL|macro|GIMP_ICON_TOOL_WARP
define|#
directive|define
name|GIMP_ICON_TOOL_WARP
value|"gimp-tool-warp"
DECL|macro|GIMP_ICON_TOOL_ZOOM
define|#
directive|define
name|GIMP_ICON_TOOL_ZOOM
value|"gimp-tool-zoom"
DECL|macro|GIMP_ICON_VIEW_REFRESH
define|#
directive|define
name|GIMP_ICON_VIEW_REFRESH
value|"view-refresh"
DECL|macro|GIMP_ICON_VIEW_FULLSCREEN
define|#
directive|define
name|GIMP_ICON_VIEW_FULLSCREEN
value|"view-fullscreen"
DECL|macro|GIMP_ICON_WILBER
define|#
directive|define
name|GIMP_ICON_WILBER
value|"gimp-wilber"
DECL|macro|GIMP_ICON_WILBER_EEK
define|#
directive|define
name|GIMP_ICON_WILBER_EEK
value|"gimp-wilber-eek"
DECL|macro|GIMP_ICON_WINDOW_CLOSE
define|#
directive|define
name|GIMP_ICON_WINDOW_CLOSE
value|"window-close"
DECL|macro|GIMP_ICON_WINDOW_MOVE_TO_SCREEN
define|#
directive|define
name|GIMP_ICON_WINDOW_MOVE_TO_SCREEN
value|"gimp-move-to-screen"
DECL|macro|GIMP_ICON_WINDOW_NEW
define|#
directive|define
name|GIMP_ICON_WINDOW_NEW
value|"window-new"
DECL|macro|GIMP_ICON_ZOOM_IN
define|#
directive|define
name|GIMP_ICON_ZOOM_IN
value|"zoom-in"
DECL|macro|GIMP_ICON_ZOOM_ORIGINAL
define|#
directive|define
name|GIMP_ICON_ZOOM_ORIGINAL
value|"zoom-original"
DECL|macro|GIMP_ICON_ZOOM_OUT
define|#
directive|define
name|GIMP_ICON_ZOOM_OUT
value|"zoom-out"
DECL|macro|GIMP_ICON_ZOOM_FIT_BEST
define|#
directive|define
name|GIMP_ICON_ZOOM_FIT_BEST
value|"zoom-fit-best"
DECL|macro|GIMP_ICON_ZOOM_FOLLOW_WINDOW
define|#
directive|define
name|GIMP_ICON_ZOOM_FOLLOW_WINDOW
value|"gimp-zoom-follow-window"
name|void
name|gimp_icons_init
parameter_list|(
name|void
parameter_list|)
function_decl|;
end_function_decl

begin_function_decl
name|void
name|gimp_icons_set_icon_theme
parameter_list|(
name|GFile
modifier|*
name|path
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
comment|/* __GIMP_ICONS_H__ */
end_comment

end_unit

