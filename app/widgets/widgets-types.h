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
DECL|typedef|GimpMenuFactory
typedef|typedef
name|struct
name|_GimpMenuFactory
name|GimpMenuFactory
typedef|;
end_typedef

begin_typedef
DECL|typedef|GimpActionFactory
typedef|typedef
name|struct
name|_GimpActionFactory
name|GimpActionFactory
typedef|;
end_typedef

begin_typedef
DECL|typedef|GimpActionGroup
typedef|typedef
name|struct
name|_GimpActionGroup
name|GimpActionGroup
typedef|;
end_typedef

begin_typedef
DECL|typedef|GimpEnumAction
typedef|typedef
name|struct
name|_GimpEnumAction
name|GimpEnumAction
typedef|;
end_typedef

begin_typedef
DECL|typedef|GimpPlugInAction
typedef|typedef
name|struct
name|_GimpPlugInAction
name|GimpPlugInAction
typedef|;
end_typedef

begin_typedef
DECL|typedef|GimpStringAction
typedef|typedef
name|struct
name|_GimpStringAction
name|GimpStringAction
typedef|;
end_typedef

begin_typedef
DECL|typedef|GimpUIManager
typedef|typedef
name|struct
name|_GimpUIManager
name|GimpUIManager
typedef|;
end_typedef

begin_typedef
DECL|typedef|GimpEnumStore
typedef|typedef
name|struct
name|_GimpEnumStore
name|GimpEnumStore
typedef|;
end_typedef

begin_typedef
DECL|typedef|GimpUnitStore
typedef|typedef
name|struct
name|_GimpUnitStore
name|GimpUnitStore
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
DECL|typedef|GimpPreviewRendererLayer
typedef|typedef
name|struct
name|_GimpPreviewRendererLayer
name|GimpPreviewRendererLayer
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

begin_typedef
DECL|typedef|GimpPreviewRendererImagefile
typedef|typedef
name|struct
name|_GimpPreviewRendererImagefile
name|GimpPreviewRendererImagefile
typedef|;
end_typedef

begin_typedef
DECL|typedef|GimpPreviewRendererVectors
typedef|typedef
name|struct
name|_GimpPreviewRendererVectors
name|GimpPreviewRendererVectors
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
DECL|typedef|GimpEnumComboBox
typedef|typedef
name|struct
name|_GimpEnumComboBox
name|GimpEnumComboBox
typedef|;
end_typedef

begin_typedef
DECL|typedef|GimpUnitComboBox
typedef|typedef
name|struct
name|_GimpUnitComboBox
name|GimpUnitComboBox
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
DECL|typedef|GimpColorBar
typedef|typedef
name|struct
name|_GimpColorBar
name|GimpColorBar
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
DECL|typedef|GimpGridEditor
typedef|typedef
name|struct
name|_GimpGridEditor
name|GimpGridEditor
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
DECL|typedef|GimpStrokeEditor
typedef|typedef
name|struct
name|_GimpStrokeEditor
name|GimpStrokeEditor
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
DECL|typedef|GimpToolOptionsEditor
typedef|typedef
name|struct
name|_GimpToolOptionsEditor
name|GimpToolOptionsEditor
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

begin_comment
DECL|typedef|GimpContainerView
comment|/* dummy typedef */
end_comment

begin_typedef
DECL|typedef|GimpContainerBox
typedef|typedef
name|struct
name|_GimpContainerBox
name|GimpContainerBox
typedef|;
end_typedef

begin_typedef
DECL|typedef|GimpContainerComboBox
typedef|typedef
name|struct
name|_GimpContainerComboBox
name|GimpContainerComboBox
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
DECL|typedef|GimpFontView
typedef|typedef
name|struct
name|_GimpFontView
name|GimpFontView
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
DECL|typedef|GimpToolView
typedef|typedef
name|struct
name|_GimpToolView
name|GimpToolView
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
DECL|typedef|GimpPatternFactoryView
typedef|typedef
name|struct
name|_GimpPatternFactoryView
name|GimpPatternFactoryView
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
DECL|typedef|GimpDocked
typedef|typedef
name|struct
name|_GimpDocked
name|GimpDocked
typedef|;
end_typedef

begin_comment
DECL|typedef|GimpDocked
comment|/* dummy typedef */
end_comment

begin_typedef
DECL|typedef|GimpDockedInterface
typedef|typedef
name|struct
name|_GimpDockedInterface
name|GimpDockedInterface
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
DECL|typedef|GimpFileDialog
typedef|typedef
name|struct
name|_GimpFileDialog
name|GimpFileDialog
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
DECL|typedef|GimpHistogramEditor
typedef|typedef
name|struct
name|_GimpHistogramEditor
name|GimpHistogramEditor
typedef|;
end_typedef

begin_typedef
DECL|typedef|GimpDashEditor
typedef|typedef
name|struct
name|_GimpDashEditor
name|GimpDashEditor
typedef|;
end_typedef

begin_typedef
DECL|typedef|GimpThumbBox
typedef|typedef
name|struct
name|_GimpThumbBox
name|GimpThumbBox
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

begin_typedef
DECL|typedef|GimpColorDisplayEditor
typedef|typedef
name|struct
name|_GimpColorDisplayEditor
name|GimpColorDisplayEditor
typedef|;
end_typedef

begin_comment
comment|/*  structs  */
end_comment

begin_typedef
DECL|typedef|GimpActionEntry
typedef|typedef
name|struct
name|_GimpActionEntry
name|GimpActionEntry
typedef|;
end_typedef

begin_typedef
DECL|typedef|GimpToggleActionEntry
typedef|typedef
name|struct
name|_GimpToggleActionEntry
name|GimpToggleActionEntry
typedef|;
end_typedef

begin_typedef
DECL|typedef|GimpRadioActionEntry
typedef|typedef
name|struct
name|_GimpRadioActionEntry
name|GimpRadioActionEntry
typedef|;
end_typedef

begin_typedef
DECL|typedef|GimpEnumActionEntry
typedef|typedef
name|struct
name|_GimpEnumActionEntry
name|GimpEnumActionEntry
typedef|;
end_typedef

begin_typedef
DECL|typedef|GimpStringActionEntry
typedef|typedef
name|struct
name|_GimpStringActionEntry
name|GimpStringActionEntry
typedef|;
end_typedef

begin_typedef
DECL|typedef|GimpPlugInActionEntry
typedef|typedef
name|struct
name|_GimpPlugInActionEntry
name|GimpPlugInActionEntry
typedef|;
end_typedef

begin_typedef
DECL|typedef|GimpDialogFactoryEntry
typedef|typedef
name|struct
name|_GimpDialogFactoryEntry
name|GimpDialogFactoryEntry
typedef|;
end_typedef

begin_typedef
DECL|typedef|GimpSessionInfo
typedef|typedef
name|struct
name|_GimpSessionInfo
name|GimpSessionInfo
typedef|;
end_typedef

begin_typedef
DECL|typedef|GimpSessionInfoBook
typedef|typedef
name|struct
name|_GimpSessionInfoBook
name|GimpSessionInfoBook
typedef|;
end_typedef

begin_typedef
DECL|typedef|GimpSessionInfoDockable
typedef|typedef
name|struct
name|_GimpSessionInfoDockable
name|GimpSessionInfoDockable
typedef|;
end_typedef

begin_typedef
DECL|typedef|GimpSessionInfoAux
typedef|typedef
name|struct
name|_GimpSessionInfoAux
name|GimpSessionInfoAux
typedef|;
end_typedef

begin_comment
comment|/*  function types  */
end_comment

begin_typedef
DECL|typedef|GimpActionGroupSetupFunc
typedef|typedef
name|void
function_decl|(
modifier|*
name|GimpActionGroupSetupFunc
function_decl|)
parameter_list|(
name|GimpActionGroup
modifier|*
name|group
parameter_list|)
function_decl|;
end_typedef

begin_typedef
DECL|typedef|GimpActionGroupUpdateFunc
typedef|typedef
name|void
function_decl|(
modifier|*
name|GimpActionGroupUpdateFunc
function_decl|)
parameter_list|(
name|GimpActionGroup
modifier|*
name|group
parameter_list|,
name|gpointer
name|data
parameter_list|)
function_decl|;
end_typedef

begin_typedef
DECL|typedef|GimpUIManagerSetupFunc
typedef|typedef
name|void
function_decl|(
modifier|*
name|GimpUIManagerSetupFunc
function_decl|)
parameter_list|(
name|GimpUIManager
modifier|*
name|manager
parameter_list|,
specifier|const
name|gchar
modifier|*
name|ui_path
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
DECL|typedef|GimpStrokeItemFunc
typedef|typedef
name|void
function_decl|(
modifier|*
name|GimpStrokeItemFunc
function_decl|)
parameter_list|(
name|GimpItem
modifier|*
name|item
parameter_list|,
name|GtkWidget
modifier|*
name|parent
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

