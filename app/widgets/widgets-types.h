begin_unit|revision:0.9.5;language:C;cregit-version:0.0.1
begin_comment
comment|/* The GIMP -- an image manipulation program  * Copyright (C) 1995 Spencer Kimball and Peter Mattis  *  * This program is free software; you can redistribute it and/or modify  * it under the terms of the GNU General Public License as published by  * the Free Software Foundation; either version 2 of the License, or  * (at your option) any later version.  *  * This program is distributed in the hope that it will be useful,  * but WITHOUT ANY WARRANTY; without even the implied warranty of  * MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the  * GNU General Public License for more details.  *  * You should have received a copy of the GNU General Public License  * along with this program; if not, write to the Free Software  * Foundation, Inc., 59 Temple Place - Suite 330, Boston, MA 02111-1307, USA.  */
end_comment

begin_ifndef
ifndef|#
directive|ifndef
name|__WIDGETS_TYPES_H__
end_ifndef

begin_define
DECL|macro|__WIDGETS_TYPES_H__
define|#
directive|define
name|__WIDGETS_TYPES_H__
end_define

begin_include
include|#
directive|include
file|"libgimpwidgets/gimpwidgetstypes.h"
end_include

begin_include
include|#
directive|include
file|"core/core-types.h"
end_include

begin_include
include|#
directive|include
file|"display/display-types.h"
end_include

begin_comment
comment|/*  enums  */
end_comment

begin_typedef
typedef|typedef
enum|enum
DECL|enum|__anon2bf028b80103
block|{
DECL|enumerator|GIMP_VIEW_TYPE_GRID
name|GIMP_VIEW_TYPE_GRID
block|,
DECL|enumerator|GIMP_VIEW_TYPE_LIST
name|GIMP_VIEW_TYPE_LIST
DECL|typedef|GimpViewType
block|}
name|GimpViewType
typedef|;
end_typedef

begin_typedef
typedef|typedef
enum|enum
DECL|enum|__anon2bf028b80203
block|{
DECL|enumerator|GIMP_DROP_NONE
name|GIMP_DROP_NONE
block|,
DECL|enumerator|GIMP_DROP_ABOVE
name|GIMP_DROP_ABOVE
block|,
DECL|enumerator|GIMP_DROP_BELOW
name|GIMP_DROP_BELOW
DECL|typedef|GimpDropType
block|}
name|GimpDropType
typedef|;
end_typedef

begin_typedef
typedef|typedef
enum|enum
DECL|enum|__anon2bf028b80303
block|{
DECL|enumerator|GIMP_ZOOM_IN
name|GIMP_ZOOM_IN
block|,
DECL|enumerator|GIMP_ZOOM_OUT
name|GIMP_ZOOM_OUT
DECL|typedef|GimpZoomType
block|}
name|GimpZoomType
typedef|;
end_typedef

begin_typedef
typedef|typedef
enum|enum
DECL|enum|__anon2bf028b80403
block|{
DECL|enumerator|GIMP_MOUSE_CURSOR
name|GIMP_MOUSE_CURSOR
init|=
operator|(
name|GDK_LAST_CURSOR
operator|+
literal|2
operator|)
block|,
DECL|enumerator|GIMP_CROSSHAIR_CURSOR
name|GIMP_CROSSHAIR_CURSOR
block|,
DECL|enumerator|GIMP_CROSSHAIR_SMALL_CURSOR
name|GIMP_CROSSHAIR_SMALL_CURSOR
block|,
DECL|enumerator|GIMP_BAD_CURSOR
name|GIMP_BAD_CURSOR
block|,
DECL|enumerator|GIMP_ZOOM_CURSOR
name|GIMP_ZOOM_CURSOR
block|,
DECL|enumerator|GIMP_COLOR_PICKER_CURSOR
name|GIMP_COLOR_PICKER_CURSOR
block|,
DECL|enumerator|GIMP_LAST_CURSOR_ENTRY
name|GIMP_LAST_CURSOR_ENTRY
DECL|typedef|GimpCursorType
block|}
name|GimpCursorType
typedef|;
end_typedef

begin_typedef
typedef|typedef
enum|enum
DECL|enum|__anon2bf028b80503
block|{
DECL|enumerator|GIMP_TOOL_CURSOR_NONE
name|GIMP_TOOL_CURSOR_NONE
block|,
DECL|enumerator|GIMP_RECT_SELECT_TOOL_CURSOR
name|GIMP_RECT_SELECT_TOOL_CURSOR
block|,
DECL|enumerator|GIMP_ELLIPSE_SELECT_TOOL_CURSOR
name|GIMP_ELLIPSE_SELECT_TOOL_CURSOR
block|,
DECL|enumerator|GIMP_FREE_SELECT_TOOL_CURSOR
name|GIMP_FREE_SELECT_TOOL_CURSOR
block|,
DECL|enumerator|GIMP_FUZZY_SELECT_TOOL_CURSOR
name|GIMP_FUZZY_SELECT_TOOL_CURSOR
block|,
DECL|enumerator|GIMP_BEZIER_SELECT_TOOL_CURSOR
name|GIMP_BEZIER_SELECT_TOOL_CURSOR
block|,
DECL|enumerator|GIMP_SCISSORS_TOOL_CURSOR
name|GIMP_SCISSORS_TOOL_CURSOR
block|,
DECL|enumerator|GIMP_MOVE_TOOL_CURSOR
name|GIMP_MOVE_TOOL_CURSOR
block|,
DECL|enumerator|GIMP_ZOOM_TOOL_CURSOR
name|GIMP_ZOOM_TOOL_CURSOR
block|,
DECL|enumerator|GIMP_CROP_TOOL_CURSOR
name|GIMP_CROP_TOOL_CURSOR
block|,
DECL|enumerator|GIMP_RESIZE_TOOL_CURSOR
name|GIMP_RESIZE_TOOL_CURSOR
block|,
DECL|enumerator|GIMP_ROTATE_TOOL_CURSOR
name|GIMP_ROTATE_TOOL_CURSOR
block|,
DECL|enumerator|GIMP_SHEAR_TOOL_CURSOR
name|GIMP_SHEAR_TOOL_CURSOR
block|,
DECL|enumerator|GIMP_PERSPECTIVE_TOOL_CURSOR
name|GIMP_PERSPECTIVE_TOOL_CURSOR
block|,
DECL|enumerator|GIMP_FLIP_HORIZONTAL_TOOL_CURSOR
name|GIMP_FLIP_HORIZONTAL_TOOL_CURSOR
block|,
DECL|enumerator|GIMP_FLIP_VERTICAL_TOOL_CURSOR
name|GIMP_FLIP_VERTICAL_TOOL_CURSOR
block|,
DECL|enumerator|GIMP_TEXT_TOOL_CURSOR
name|GIMP_TEXT_TOOL_CURSOR
block|,
DECL|enumerator|GIMP_COLOR_PICKER_TOOL_CURSOR
name|GIMP_COLOR_PICKER_TOOL_CURSOR
block|,
DECL|enumerator|GIMP_BUCKET_FILL_TOOL_CURSOR
name|GIMP_BUCKET_FILL_TOOL_CURSOR
block|,
DECL|enumerator|GIMP_BLEND_TOOL_CURSOR
name|GIMP_BLEND_TOOL_CURSOR
block|,
DECL|enumerator|GIMP_PENCIL_TOOL_CURSOR
name|GIMP_PENCIL_TOOL_CURSOR
block|,
DECL|enumerator|GIMP_PAINTBRUSH_TOOL_CURSOR
name|GIMP_PAINTBRUSH_TOOL_CURSOR
block|,
DECL|enumerator|GIMP_AIRBRUSH_TOOL_CURSOR
name|GIMP_AIRBRUSH_TOOL_CURSOR
block|,
DECL|enumerator|GIMP_INK_TOOL_CURSOR
name|GIMP_INK_TOOL_CURSOR
block|,
DECL|enumerator|GIMP_CLONE_TOOL_CURSOR
name|GIMP_CLONE_TOOL_CURSOR
block|,
DECL|enumerator|GIMP_ERASER_TOOL_CURSOR
name|GIMP_ERASER_TOOL_CURSOR
block|,
DECL|enumerator|GIMP_SMUDGE_TOOL_CURSOR
name|GIMP_SMUDGE_TOOL_CURSOR
block|,
DECL|enumerator|GIMP_BLUR_TOOL_CURSOR
name|GIMP_BLUR_TOOL_CURSOR
block|,
DECL|enumerator|GIMP_DODGE_TOOL_CURSOR
name|GIMP_DODGE_TOOL_CURSOR
block|,
DECL|enumerator|GIMP_BURN_TOOL_CURSOR
name|GIMP_BURN_TOOL_CURSOR
block|,
DECL|enumerator|GIMP_MEASURE_TOOL_CURSOR
name|GIMP_MEASURE_TOOL_CURSOR
block|,
DECL|enumerator|GIMP_LAST_STOCK_TOOL_CURSOR_ENTRY
name|GIMP_LAST_STOCK_TOOL_CURSOR_ENTRY
DECL|typedef|GimpToolCursorType
block|}
name|GimpToolCursorType
typedef|;
end_typedef

begin_typedef
typedef|typedef
enum|enum
DECL|enum|__anon2bf028b80603
block|{
DECL|enumerator|GIMP_CURSOR_MODIFIER_NONE
name|GIMP_CURSOR_MODIFIER_NONE
block|,
DECL|enumerator|GIMP_CURSOR_MODIFIER_PLUS
name|GIMP_CURSOR_MODIFIER_PLUS
block|,
DECL|enumerator|GIMP_CURSOR_MODIFIER_MINUS
name|GIMP_CURSOR_MODIFIER_MINUS
block|,
DECL|enumerator|GIMP_CURSOR_MODIFIER_INTERSECT
name|GIMP_CURSOR_MODIFIER_INTERSECT
block|,
DECL|enumerator|GIMP_CURSOR_MODIFIER_MOVE
name|GIMP_CURSOR_MODIFIER_MOVE
block|,
DECL|enumerator|GIMP_CURSOR_MODIFIER_RESIZE
name|GIMP_CURSOR_MODIFIER_RESIZE
block|,
DECL|enumerator|GIMP_CURSOR_MODIFIER_CONTROL
name|GIMP_CURSOR_MODIFIER_CONTROL
block|,
DECL|enumerator|GIMP_CURSOR_MODIFIER_ANCHOR
name|GIMP_CURSOR_MODIFIER_ANCHOR
block|,
DECL|enumerator|GIMP_CURSOR_MODIFIER_FOREGROUND
name|GIMP_CURSOR_MODIFIER_FOREGROUND
block|,
DECL|enumerator|GIMP_CURSOR_MODIFIER_BACKGROUND
name|GIMP_CURSOR_MODIFIER_BACKGROUND
block|,
DECL|enumerator|GIMP_CURSOR_MODIFIER_PATTERN
name|GIMP_CURSOR_MODIFIER_PATTERN
block|,
DECL|enumerator|GIMP_CURSOR_MODIFIER_HAND
name|GIMP_CURSOR_MODIFIER_HAND
block|,
DECL|enumerator|GIMP_LAST_CURSOR_MODIFIER_ENTRY
name|GIMP_LAST_CURSOR_MODIFIER_ENTRY
DECL|typedef|GimpCursorModifier
block|}
name|GimpCursorModifier
typedef|;
end_typedef

begin_comment
comment|/*  non-widget objects  */
end_comment

begin_typedef
DECL|typedef|GimpDialogFactory
typedef|typedef
name|struct
name|_GimpDialogFactory
name|GimpDialogFactory
typedef|;
end_typedef

begin_comment
comment|/*  widgets  */
end_comment

begin_typedef
DECL|typedef|GimpPreview
typedef|typedef
name|struct
name|_GimpPreview
name|GimpPreview
typedef|;
end_typedef

begin_typedef
DECL|typedef|GimpImagePreview
typedef|typedef
name|struct
name|_GimpImagePreview
name|GimpImagePreview
typedef|;
end_typedef

begin_typedef
DECL|typedef|GimpDrawablePreview
typedef|typedef
name|struct
name|_GimpDrawablePreview
name|GimpDrawablePreview
typedef|;
end_typedef

begin_typedef
DECL|typedef|GimpImagefilePreview
typedef|typedef
name|struct
name|_GimpImagefilePreview
name|GimpImagefilePreview
typedef|;
end_typedef

begin_typedef
DECL|typedef|GimpBrushPreview
typedef|typedef
name|struct
name|_GimpBrushPreview
name|GimpBrushPreview
typedef|;
end_typedef

begin_typedef
DECL|typedef|GimpNavigationPreview
typedef|typedef
name|struct
name|_GimpNavigationPreview
name|GimpNavigationPreview
typedef|;
end_typedef

begin_typedef
DECL|typedef|GimpPatternPreview
typedef|typedef
name|struct
name|_GimpPatternPreview
name|GimpPatternPreview
typedef|;
end_typedef

begin_typedef
DECL|typedef|GimpPalettePreview
typedef|typedef
name|struct
name|_GimpPalettePreview
name|GimpPalettePreview
typedef|;
end_typedef

begin_typedef
DECL|typedef|GimpGradientPreview
typedef|typedef
name|struct
name|_GimpGradientPreview
name|GimpGradientPreview
typedef|;
end_typedef

begin_typedef
DECL|typedef|GimpToolInfoPreview
typedef|typedef
name|struct
name|_GimpToolInfoPreview
name|GimpToolInfoPreview
typedef|;
end_typedef

begin_typedef
DECL|typedef|GimpBufferPreview
typedef|typedef
name|struct
name|_GimpBufferPreview
name|GimpBufferPreview
typedef|;
end_typedef

begin_typedef
DECL|typedef|GimpContainerMenu
typedef|typedef
name|struct
name|_GimpContainerMenu
name|GimpContainerMenu
typedef|;
end_typedef

begin_typedef
DECL|typedef|GimpContainerMenuImpl
typedef|typedef
name|struct
name|_GimpContainerMenuImpl
name|GimpContainerMenuImpl
typedef|;
end_typedef

begin_typedef
DECL|typedef|GimpMenuItem
typedef|typedef
name|struct
name|_GimpMenuItem
name|GimpMenuItem
typedef|;
end_typedef

begin_typedef
DECL|typedef|GimpContainerView
typedef|typedef
name|struct
name|_GimpContainerView
name|GimpContainerView
typedef|;
end_typedef

begin_typedef
DECL|typedef|GimpContainerListView
typedef|typedef
name|struct
name|_GimpContainerListView
name|GimpContainerListView
typedef|;
end_typedef

begin_typedef
DECL|typedef|GimpContainerGridView
typedef|typedef
name|struct
name|_GimpContainerGridView
name|GimpContainerGridView
typedef|;
end_typedef

begin_typedef
DECL|typedef|GimpDrawableListView
typedef|typedef
name|struct
name|_GimpDrawableListView
name|GimpDrawableListView
typedef|;
end_typedef

begin_typedef
DECL|typedef|GimpLayerListView
typedef|typedef
name|struct
name|_GimpLayerListView
name|GimpLayerListView
typedef|;
end_typedef

begin_typedef
DECL|typedef|GimpChannelListView
typedef|typedef
name|struct
name|_GimpChannelListView
name|GimpChannelListView
typedef|;
end_typedef

begin_typedef
DECL|typedef|GimpContainerEditor
typedef|typedef
name|struct
name|_GimpContainerEditor
name|GimpContainerEditor
typedef|;
end_typedef

begin_typedef
DECL|typedef|GimpBufferView
typedef|typedef
name|struct
name|_GimpBufferView
name|GimpBufferView
typedef|;
end_typedef

begin_typedef
DECL|typedef|GimpDocumentView
typedef|typedef
name|struct
name|_GimpDocumentView
name|GimpDocumentView
typedef|;
end_typedef

begin_typedef
DECL|typedef|GimpDataFactoryView
typedef|typedef
name|struct
name|_GimpDataFactoryView
name|GimpDataFactoryView
typedef|;
end_typedef

begin_typedef
DECL|typedef|GimpBrushFactoryView
typedef|typedef
name|struct
name|_GimpBrushFactoryView
name|GimpBrushFactoryView
typedef|;
end_typedef

begin_typedef
DECL|typedef|GimpListItem
typedef|typedef
name|struct
name|_GimpListItem
name|GimpListItem
typedef|;
end_typedef

begin_typedef
DECL|typedef|GimpChannelListItem
typedef|typedef
name|struct
name|_GimpChannelListItem
name|GimpChannelListItem
typedef|;
end_typedef

begin_typedef
DECL|typedef|GimpDrawableListItem
typedef|typedef
name|struct
name|_GimpDrawableListItem
name|GimpDrawableListItem
typedef|;
end_typedef

begin_typedef
DECL|typedef|GimpLayerListItem
typedef|typedef
name|struct
name|_GimpLayerListItem
name|GimpLayerListItem
typedef|;
end_typedef

begin_typedef
DECL|typedef|GimpComponentListItem
typedef|typedef
name|struct
name|_GimpComponentListItem
name|GimpComponentListItem
typedef|;
end_typedef

begin_typedef
DECL|typedef|GimpDock
typedef|typedef
name|struct
name|_GimpDock
name|GimpDock
typedef|;
end_typedef

begin_typedef
DECL|typedef|GimpImageDock
typedef|typedef
name|struct
name|_GimpImageDock
name|GimpImageDock
typedef|;
end_typedef

begin_typedef
DECL|typedef|GimpDockable
typedef|typedef
name|struct
name|_GimpDockable
name|GimpDockable
typedef|;
end_typedef

begin_typedef
DECL|typedef|GimpDockbook
typedef|typedef
name|struct
name|_GimpDockbook
name|GimpDockbook
typedef|;
end_typedef

begin_typedef
DECL|typedef|GimpFontSelection
typedef|typedef
name|struct
name|_GimpFontSelection
name|GimpFontSelection
typedef|;
end_typedef

begin_typedef
DECL|typedef|GimpFontSelectionDialog
typedef|typedef
name|struct
name|_GimpFontSelectionDialog
name|GimpFontSelectionDialog
typedef|;
end_typedef

begin_typedef
DECL|typedef|GimpHistogramView
typedef|typedef
name|struct
name|_GimpHistogramView
name|GimpHistogramView
typedef|;
end_typedef

begin_comment
comment|/*  function types  */
end_comment

begin_typedef
DECL|typedef|GimpItemGetNameFunc
typedef|typedef
name|gchar
modifier|*
function_decl|(
modifier|*
name|GimpItemGetNameFunc
function_decl|)
parameter_list|(
name|GtkWidget
modifier|*
name|widget
parameter_list|,
name|gchar
modifier|*
modifier|*
name|tooltip
parameter_list|)
function_decl|;
end_typedef

begin_endif
endif|#
directive|endif
end_endif

begin_comment
comment|/* __WIDGETS_TYPES_H__ */
end_comment

end_unit

