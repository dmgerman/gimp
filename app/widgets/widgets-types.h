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
file|"widgets/widgets-enums.h"
end_include

begin_comment
comment|/*  non-widget objects  */
end_comment

begin_typedef
DECL|typedef|GimpDeviceInfo
typedef|typedef
name|struct
name|_GimpDeviceInfo
name|GimpDeviceInfo
typedef|;
end_typedef

begin_typedef
DECL|typedef|GimpDialogFactory
typedef|typedef
name|struct
name|_GimpDialogFactory
name|GimpDialogFactory
typedef|;
end_typedef

begin_typedef
DECL|typedef|GimpItemFactory
typedef|typedef
name|struct
name|_GimpItemFactory
name|GimpItemFactory
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
DECL|typedef|GimpEnumMenu
typedef|typedef
name|struct
name|_GimpEnumMenu
name|GimpEnumMenu
typedef|;
end_typedef

begin_typedef
DECL|typedef|GimpEditor
typedef|typedef
name|struct
name|_GimpEditor
name|GimpEditor
typedef|;
end_typedef

begin_typedef
DECL|typedef|GimpColormapEditor
typedef|typedef
name|struct
name|_GimpColormapEditor
name|GimpColormapEditor
typedef|;
end_typedef

begin_typedef
DECL|typedef|GimpDataEditor
typedef|typedef
name|struct
name|_GimpDataEditor
name|GimpDataEditor
typedef|;
end_typedef

begin_typedef
DECL|typedef|GimpBrushEditor
typedef|typedef
name|struct
name|_GimpBrushEditor
name|GimpBrushEditor
typedef|;
end_typedef

begin_typedef
DECL|typedef|GimpGradientEditor
typedef|typedef
name|struct
name|_GimpGradientEditor
name|GimpGradientEditor
typedef|;
end_typedef

begin_typedef
DECL|typedef|GimpPaletteEditor
typedef|typedef
name|struct
name|_GimpPaletteEditor
name|GimpPaletteEditor
typedef|;
end_typedef

begin_typedef
DECL|typedef|GimpSelectionEditor
typedef|typedef
name|struct
name|_GimpSelectionEditor
name|GimpSelectionEditor
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
DECL|typedef|GimpItemListView
typedef|typedef
name|struct
name|_GimpItemListView
name|GimpItemListView
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
DECL|typedef|GimpVectorsListView
typedef|typedef
name|struct
name|_GimpVectorsListView
name|GimpVectorsListView
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
DECL|typedef|GimpImageView
typedef|typedef
name|struct
name|_GimpImageView
name|GimpImageView
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
DECL|typedef|GimpItemListItem
typedef|typedef
name|struct
name|_GimpItemListItem
name|GimpItemListItem
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
DECL|typedef|GimpToolbox
typedef|typedef
name|struct
name|_GimpToolbox
name|GimpToolbox
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
DECL|typedef|GimpViewableDialog
typedef|typedef
name|struct
name|_GimpViewableDialog
name|GimpViewableDialog
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

