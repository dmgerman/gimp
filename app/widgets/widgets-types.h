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

begin_typedef
DECL|typedef|GimpMenuFactory
typedef|typedef
name|struct
name|_GimpMenuFactory
name|GimpMenuFactory
typedef|;
end_typedef

begin_typedef
DECL|typedef|GimpCellRendererToggle
typedef|typedef
name|struct
name|_GimpCellRendererToggle
name|GimpCellRendererToggle
typedef|;
end_typedef

begin_typedef
DECL|typedef|GimpCellRendererViewable
typedef|typedef
name|struct
name|_GimpCellRendererViewable
name|GimpCellRendererViewable
typedef|;
end_typedef

begin_typedef
DECL|typedef|GimpPreviewRenderer
typedef|typedef
name|struct
name|_GimpPreviewRenderer
name|GimpPreviewRenderer
typedef|;
end_typedef

begin_typedef
DECL|typedef|GimpPreviewRendererBrush
typedef|typedef
name|struct
name|_GimpPreviewRendererBrush
name|GimpPreviewRendererBrush
typedef|;
end_typedef

begin_typedef
DECL|typedef|GimpPreviewRendererDrawable
typedef|typedef
name|struct
name|_GimpPreviewRendererDrawable
name|GimpPreviewRendererDrawable
typedef|;
end_typedef

begin_typedef
DECL|typedef|GimpPreviewRendererGradient
typedef|typedef
name|struct
name|_GimpPreviewRendererGradient
name|GimpPreviewRendererGradient
typedef|;
end_typedef

begin_typedef
DECL|typedef|GimpPreviewRendererTextLayer
typedef|typedef
name|struct
name|_GimpPreviewRendererTextLayer
name|GimpPreviewRendererTextLayer
typedef|;
end_typedef

begin_typedef
DECL|typedef|GimpPreviewRendererImage
typedef|typedef
name|struct
name|_GimpPreviewRendererImage
name|GimpPreviewRendererImage
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
DECL|typedef|GimpBrushPreview
typedef|typedef
name|struct
name|_GimpBrushPreview
name|GimpBrushPreview
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
DECL|typedef|GimpImagePreview
typedef|typedef
name|struct
name|_GimpImagePreview
name|GimpImagePreview
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
DECL|typedef|GimpDeviceStatus
typedef|typedef
name|struct
name|_GimpDeviceStatus
name|GimpDeviceStatus
typedef|;
end_typedef

begin_typedef
DECL|typedef|GimpErrorConsole
typedef|typedef
name|struct
name|_GimpErrorConsole
name|GimpErrorConsole
typedef|;
end_typedef

begin_typedef
DECL|typedef|GimpImageEditor
typedef|typedef
name|struct
name|_GimpImageEditor
name|GimpImageEditor
typedef|;
end_typedef

begin_typedef
DECL|typedef|GimpColorEditor
typedef|typedef
name|struct
name|_GimpColorEditor
name|GimpColorEditor
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
DECL|typedef|GimpComponentEditor
typedef|typedef
name|struct
name|_GimpComponentEditor
name|GimpComponentEditor
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
DECL|typedef|GimpTemplateEditor
typedef|typedef
name|struct
name|_GimpTemplateEditor
name|GimpTemplateEditor
typedef|;
end_typedef

begin_typedef
DECL|typedef|GimpUndoEditor
typedef|typedef
name|struct
name|_GimpUndoEditor
name|GimpUndoEditor
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
DECL|typedef|GimpContainerGridView
typedef|typedef
name|struct
name|_GimpContainerGridView
name|GimpContainerGridView
typedef|;
end_typedef

begin_typedef
DECL|typedef|GimpContainerTreeView
typedef|typedef
name|struct
name|_GimpContainerTreeView
name|GimpContainerTreeView
typedef|;
end_typedef

begin_typedef
DECL|typedef|GimpItemTreeView
typedef|typedef
name|struct
name|_GimpItemTreeView
name|GimpItemTreeView
typedef|;
end_typedef

begin_typedef
DECL|typedef|GimpDrawableTreeView
typedef|typedef
name|struct
name|_GimpDrawableTreeView
name|GimpDrawableTreeView
typedef|;
end_typedef

begin_typedef
DECL|typedef|GimpLayerTreeView
typedef|typedef
name|struct
name|_GimpLayerTreeView
name|GimpLayerTreeView
typedef|;
end_typedef

begin_typedef
DECL|typedef|GimpChannelTreeView
typedef|typedef
name|struct
name|_GimpChannelTreeView
name|GimpChannelTreeView
typedef|;
end_typedef

begin_typedef
DECL|typedef|GimpVectorsTreeView
typedef|typedef
name|struct
name|_GimpVectorsTreeView
name|GimpVectorsTreeView
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
DECL|typedef|GimpTemplateView
typedef|typedef
name|struct
name|_GimpTemplateView
name|GimpTemplateView
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
DECL|typedef|GimpContainerPopup
typedef|typedef
name|struct
name|_GimpContainerPopup
name|GimpContainerPopup
typedef|;
end_typedef

begin_typedef
DECL|typedef|GimpViewableButton
typedef|typedef
name|struct
name|_GimpViewableButton
name|GimpViewableButton
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

begin_typedef
DECL|typedef|GimpHistogramBox
typedef|typedef
name|struct
name|_GimpHistogramBox
name|GimpHistogramBox
typedef|;
end_typedef

begin_typedef
DECL|typedef|GimpTextEditor
typedef|typedef
name|struct
name|_GimpTextEditor
name|GimpTextEditor
typedef|;
end_typedef

begin_comment
comment|/*  structs  */
end_comment

begin_typedef
DECL|typedef|GimpItemFactoryEntry
typedef|typedef
name|struct
name|_GimpItemFactoryEntry
name|GimpItemFactoryEntry
typedef|;
end_typedef

begin_comment
comment|/*  function types  */
end_comment

begin_typedef
DECL|typedef|GimpItemFactorySetupFunc
typedef|typedef
name|void
function_decl|(
modifier|*
name|GimpItemFactorySetupFunc
function_decl|)
parameter_list|(
name|GimpItemFactory
modifier|*
name|factory
parameter_list|)
function_decl|;
end_typedef

begin_typedef
DECL|typedef|GimpItemFactoryUpdateFunc
typedef|typedef
name|void
function_decl|(
modifier|*
name|GimpItemFactoryUpdateFunc
function_decl|)
parameter_list|(
name|GtkItemFactory
modifier|*
name|factory
parameter_list|,
name|gpointer
name|data
parameter_list|)
function_decl|;
end_typedef

begin_typedef
DECL|typedef|GimpMenuPositionFunc
typedef|typedef
name|void
function_decl|(
modifier|*
name|GimpMenuPositionFunc
function_decl|)
parameter_list|(
name|GtkMenu
modifier|*
name|menu
parameter_list|,
name|gint
modifier|*
name|x
parameter_list|,
name|gint
modifier|*
name|y
parameter_list|,
name|gpointer
name|data
parameter_list|)
function_decl|;
end_typedef

begin_typedef
DECL|typedef|GimpSelectionToVectorsFunc
typedef|typedef
name|void
function_decl|(
modifier|*
name|GimpSelectionToVectorsFunc
function_decl|)
parameter_list|(
name|GimpImage
modifier|*
name|gimage
parameter_list|,
name|gboolean
name|advanced
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

