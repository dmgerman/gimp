begin_unit|revision:0.9.5;language:C;cregit-version:0.0.1
begin_comment
comment|/* The GIMP -- an image manipulation program  * Copyright (C) 1995 Spencer Kimball and Peter Mattis  *  * This program is free software; you can redistribute it and/or modify  * it under the terms of the GNU General Public License as published by  * the Free Software Foundation; either version 2 of the License, or  * (at your option) any later version.  *  * This program is distributed in the hope that it will be useful,  * but WITHOUT ANY WARRANTY; without even the implied warranty of  * MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the  * GNU General Public License for more details.  *  * You should have received a copy of the GNU General Public License  * along with this program; if not, write to the Free Software  * Foundation, Inc., 59 Temple Place - Suite 330, Boston, MA 02111-1307, USA.  */
end_comment

begin_ifndef
ifndef|#
directive|ifndef
name|__APPTYPES_H__
end_ifndef

begin_define
DECL|macro|__APPTYPES_H__
define|#
directive|define
name|__APPTYPES_H__
end_define

begin_include
include|#
directive|include
file|"libgimpcolor/gimpcolortypes.h"
end_include

begin_include
include|#
directive|include
file|"libgimpmath/gimpmathtypes.h"
end_include

begin_include
include|#
directive|include
file|"libgimpwidgets/gimpwidgetstypes.h"
end_include

begin_include
include|#
directive|include
file|"undo_types.h"
end_include

begin_include
include|#
directive|include
file|"appenums.h"
end_include

begin_comment
comment|/*  base objects  */
end_comment

begin_typedef
DECL|typedef|GimpObject
typedef|typedef
name|struct
name|_GimpObject
name|GimpObject
typedef|;
end_typedef

begin_typedef
DECL|typedef|GimpContainer
typedef|typedef
name|struct
name|_GimpContainer
name|GimpContainer
typedef|;
end_typedef

begin_typedef
DECL|typedef|GimpList
typedef|typedef
name|struct
name|_GimpList
name|GimpList
typedef|;
end_typedef

begin_typedef
DECL|typedef|GimpDataList
typedef|typedef
name|struct
name|_GimpDataList
name|GimpDataList
typedef|;
end_typedef

begin_typedef
DECL|typedef|GimpDataFactory
typedef|typedef
name|struct
name|_GimpDataFactory
name|GimpDataFactory
typedef|;
end_typedef

begin_typedef
DECL|typedef|GimpContext
typedef|typedef
name|struct
name|_GimpContext
name|GimpContext
typedef|;
end_typedef

begin_typedef
DECL|typedef|GimpViewable
typedef|typedef
name|struct
name|_GimpViewable
name|GimpViewable
typedef|;
end_typedef

begin_comment
comment|/*  drawable objects  */
end_comment

begin_typedef
DECL|typedef|GimpDrawable
typedef|typedef
name|struct
name|_GimpDrawable
name|GimpDrawable
typedef|;
end_typedef

begin_typedef
DECL|typedef|GimpChannel
typedef|typedef
name|struct
name|_GimpChannel
name|GimpChannel
typedef|;
end_typedef

begin_typedef
DECL|typedef|GimpLayer
typedef|typedef
name|struct
name|_GimpLayer
name|GimpLayer
typedef|;
end_typedef

begin_typedef
DECL|typedef|GimpLayerMask
typedef|typedef
name|struct
name|_GimpLayerMask
name|GimpLayerMask
typedef|;
end_typedef

begin_typedef
DECL|typedef|GimpImage
typedef|typedef
name|struct
name|_GimpImage
name|GimpImage
typedef|;
end_typedef

begin_comment
comment|/*  data objects  */
end_comment

begin_typedef
DECL|typedef|GimpData
typedef|typedef
name|struct
name|_GimpData
name|GimpData
typedef|;
end_typedef

begin_typedef
DECL|typedef|GimpBrush
typedef|typedef
name|struct
name|_GimpBrush
name|GimpBrush
typedef|;
end_typedef

begin_typedef
DECL|typedef|GimpBrushGenerated
typedef|typedef
name|struct
name|_GimpBrushGenerated
name|GimpBrushGenerated
typedef|;
end_typedef

begin_typedef
DECL|typedef|GimpBrushPipe
typedef|typedef
name|struct
name|_GimpBrushPipe
name|GimpBrushPipe
typedef|;
end_typedef

begin_typedef
DECL|typedef|GimpGradient
typedef|typedef
name|struct
name|_GimpGradient
name|GimpGradient
typedef|;
end_typedef

begin_typedef
DECL|typedef|GimpPattern
typedef|typedef
name|struct
name|_GimpPattern
name|GimpPattern
typedef|;
end_typedef

begin_typedef
DECL|typedef|GimpPalette
typedef|typedef
name|struct
name|_GimpPalette
name|GimpPalette
typedef|;
end_typedef

begin_comment
comment|/*  tools  */
end_comment

begin_typedef
DECL|typedef|GimpToolInfo
typedef|typedef
name|struct
name|_GimpToolInfo
name|GimpToolInfo
typedef|;
end_typedef

begin_typedef
DECL|typedef|GimpTool
typedef|typedef
name|struct
name|_GimpTool
name|GimpTool
typedef|;
end_typedef

begin_typedef
DECL|typedef|GimpPaintTool
typedef|typedef
name|struct
name|_GimpPaintTool
name|GimpPaintTool
typedef|;
end_typedef

begin_typedef
DECL|typedef|GimpDrawTool
typedef|typedef
name|struct
name|_GimpDrawTool
name|GimpDrawTool
typedef|;
end_typedef

begin_typedef
DECL|typedef|GimpPathTool
typedef|typedef
name|struct
name|_GimpPathTool
name|GimpPathTool
typedef|;
end_typedef

begin_typedef
DECL|typedef|GimpTransformTool
typedef|typedef
name|struct
name|_GimpTransformTool
name|GimpTransformTool
typedef|;
end_typedef

begin_typedef
DECL|typedef|GimpBezierSelectPoint
typedef|typedef
name|struct
name|_GimpBezierSelectPoint
name|GimpBezierSelectPoint
typedef|;
end_typedef

begin_typedef
DECL|typedef|GimpBezierSelectTool
typedef|typedef
name|struct
name|_GimpBezierSelectTool
name|GimpBezierSelectTool
typedef|;
end_typedef

begin_comment
comment|/*  undo objects  */
end_comment

begin_typedef
DECL|typedef|GimpUndo
typedef|typedef
name|struct
name|_GimpUndo
name|GimpUndo
typedef|;
end_typedef

begin_typedef
DECL|typedef|GimpUndoStack
typedef|typedef
name|struct
name|_GimpUndoStack
name|GimpUndoStack
typedef|;
end_typedef

begin_comment
comment|/*  gui objects  */
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
DECL|typedef|GimpBrushPreview
typedef|typedef
name|struct
name|_GimpBrushPreview
name|GimpBrushPreview
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
DECL|typedef|GimpDataFactoryView
typedef|typedef
name|struct
name|_GimpDataFactoryView
name|GimpDataFactoryView
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
DECL|typedef|GimpListItem
typedef|typedef
name|struct
name|_GimpListItem
name|GimpListItem
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
DECL|typedef|GimpDock
typedef|typedef
name|struct
name|_GimpDock
name|GimpDock
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
DECL|typedef|HistogramWidget
typedef|typedef
name|struct
name|_HistogramWidget
name|HistogramWidget
typedef|;
end_typedef

begin_comment
comment|/*  other stuff  */
end_comment

begin_typedef
DECL|typedef|Argument
typedef|typedef
name|struct
name|_Argument
name|Argument
typedef|;
end_typedef

begin_typedef
DECL|typedef|GimpBitmapCursor
typedef|typedef
name|struct
name|_GimpBitmapCursor
name|GimpBitmapCursor
typedef|;
end_typedef

begin_typedef
DECL|typedef|BoundSeg
typedef|typedef
name|struct
name|_BoundSeg
name|BoundSeg
typedef|;
end_typedef

begin_typedef
DECL|typedef|ColorNotebook
typedef|typedef
name|struct
name|_ColorNotebook
name|ColorNotebook
typedef|;
end_typedef

begin_typedef
DECL|typedef|GDisplay
typedef|typedef
name|struct
name|_GDisplay
name|GDisplay
typedef|;
end_typedef

begin_typedef
DECL|typedef|GimpHistogram
typedef|typedef
name|struct
name|_GimpHistogram
name|GimpHistogram
typedef|;
end_typedef

begin_typedef
DECL|typedef|GimpImageNewValues
typedef|typedef
name|struct
name|_GimpImageNewValues
name|GimpImageNewValues
typedef|;
end_typedef

begin_typedef
DECL|typedef|GimpLut
typedef|typedef
name|struct
name|_GimpLut
name|GimpLut
typedef|;
end_typedef

begin_typedef
DECL|typedef|GimpParasite
typedef|typedef
name|struct
name|_GimpParasite
name|GimpParasite
typedef|;
end_typedef

begin_typedef
DECL|typedef|GimpProgress
typedef|typedef
name|struct
name|_GimpProgress
name|GimpProgress
typedef|;
end_typedef

begin_typedef
DECL|typedef|Guide
typedef|typedef
name|struct
name|_Guide
name|Guide
typedef|;
end_typedef

begin_typedef
DECL|typedef|ImageMap
typedef|typedef
name|gpointer
name|ImageMap
typedef|;
end_typedef

begin_typedef
DECL|typedef|InfoDialog
typedef|typedef
name|struct
name|_InfoDialog
name|InfoDialog
typedef|;
end_typedef

begin_typedef
DECL|typedef|Path
typedef|typedef
name|struct
name|_Path
name|Path
typedef|;
end_typedef

begin_typedef
DECL|typedef|PathPoint
typedef|typedef
name|struct
name|_PathPoint
name|PathPoint
typedef|;
end_typedef

begin_typedef
DECL|typedef|PathList
typedef|typedef
name|struct
name|_PathList
name|PathList
typedef|;
end_typedef

begin_typedef
DECL|typedef|PlugIn
typedef|typedef
name|struct
name|_PlugIn
name|PlugIn
typedef|;
end_typedef

begin_typedef
DECL|typedef|PlugInDef
typedef|typedef
name|struct
name|_PlugInDef
name|PlugInDef
typedef|;
end_typedef

begin_typedef
DECL|typedef|PlugInProcDef
typedef|typedef
name|struct
name|_PlugInProcDef
name|PlugInProcDef
typedef|;
end_typedef

begin_typedef
DECL|typedef|ParasiteList
typedef|typedef
name|struct
name|_ParasiteList
name|ParasiteList
typedef|;
end_typedef

begin_typedef
DECL|typedef|PixelRegionIterator
typedef|typedef
name|struct
name|_PixelRegionIterator
name|PixelRegionIterator
typedef|;
end_typedef

begin_typedef
DECL|typedef|PixelRegion
typedef|typedef
name|struct
name|_PixelRegion
name|PixelRegion
typedef|;
end_typedef

begin_typedef
DECL|typedef|PixelRegionHolder
typedef|typedef
name|struct
name|_PixelRegionHolder
name|PixelRegionHolder
typedef|;
end_typedef

begin_typedef
DECL|typedef|ProcArg
typedef|typedef
name|struct
name|_ProcArg
name|ProcArg
typedef|;
end_typedef

begin_typedef
DECL|typedef|ProcRecord
typedef|typedef
name|struct
name|_ProcRecord
name|ProcRecord
typedef|;
end_typedef

begin_typedef
DECL|typedef|Tattoo
typedef|typedef
name|guint32
name|Tattoo
typedef|;
end_typedef

begin_typedef
DECL|typedef|TempBuf
typedef|typedef
name|struct
name|_TempBuf
name|TempBuf
typedef|;
end_typedef

begin_typedef
DECL|typedef|MaskBuf
typedef|typedef
name|struct
name|_TempBuf
name|MaskBuf
typedef|;
end_typedef

begin_typedef
DECL|typedef|Tile
typedef|typedef
name|struct
name|_Tile
name|Tile
typedef|;
end_typedef

begin_typedef
DECL|typedef|TileManager
typedef|typedef
name|struct
name|_TileManager
name|TileManager
typedef|;
end_typedef

begin_typedef
DECL|typedef|Tool
typedef|typedef
name|struct
name|_Tool
name|Tool
typedef|;
end_typedef

begin_typedef
DECL|typedef|ToolInfo
typedef|typedef
name|struct
name|_ToolInfo
name|ToolInfo
typedef|;
end_typedef

begin_typedef
DECL|typedef|ToolOptions
typedef|typedef
name|struct
name|_ToolOptions
name|ToolOptions
typedef|;
end_typedef

begin_typedef
DECL|typedef|ScanConvertPoint
typedef|typedef
name|struct
name|_ScanConvertPoint
name|ScanConvertPoint
typedef|;
end_typedef

begin_typedef
DECL|typedef|Selection
typedef|typedef
name|struct
name|_Selection
name|Selection
typedef|;
end_typedef

begin_typedef
DECL|typedef|SelectionOptions
typedef|typedef
name|struct
name|_SelectionOptions
name|SelectionOptions
typedef|;
end_typedef

begin_comment
comment|/*  some undo stuff  */
end_comment

begin_typedef
DECL|typedef|LayerUndo
typedef|typedef
name|struct
name|_LayerUndo
name|LayerUndo
typedef|;
end_typedef

begin_typedef
DECL|typedef|LayerMaskUndo
typedef|typedef
name|struct
name|_LayerMaskUndo
name|LayerMaskUndo
typedef|;
end_typedef

begin_typedef
DECL|typedef|FStoLayerUndo
typedef|typedef
name|struct
name|_FStoLayerUndo
name|FStoLayerUndo
typedef|;
end_typedef

begin_typedef
DECL|typedef|PathUndo
typedef|typedef
name|GSList
name|PathUndo
typedef|;
end_typedef

begin_comment
comment|/*  functions  */
end_comment

begin_typedef
DECL|typedef|TileValidateProc
typedef|typedef
name|void
function_decl|(
modifier|*
name|TileValidateProc
function_decl|)
parameter_list|(
name|TileManager
modifier|*
name|tm
parameter_list|,
name|Tile
modifier|*
name|tile
parameter_list|)
function_decl|;
end_typedef

begin_typedef
DECL|typedef|ToolOptionsResetFunc
typedef|typedef
name|void
function_decl|(
modifier|*
name|ToolOptionsResetFunc
function_decl|)
parameter_list|(
name|ToolOptions
modifier|*
name|tool_options
parameter_list|)
function_decl|;
end_typedef

begin_typedef
DECL|typedef|GimpProgressFunc
typedef|typedef
name|void
function_decl|(
modifier|*
name|GimpProgressFunc
function_decl|)
parameter_list|(
name|gint
name|min
parameter_list|,
name|gint
name|max
parameter_list|,
name|gint
name|current
parameter_list|,
name|gpointer
name|data
parameter_list|)
function_decl|;
end_typedef

begin_typedef
DECL|typedef|ImageMapApplyFunc
typedef|typedef
name|void
function_decl|(
modifier|*
name|ImageMapApplyFunc
function_decl|)
parameter_list|(
name|PixelRegion
modifier|*
name|srcPR
parameter_list|,
name|PixelRegion
modifier|*
name|destPR
parameter_list|,
name|gpointer
name|data
parameter_list|)
function_decl|;
end_typedef

begin_typedef
DECL|typedef|GimpDataFileLoaderFunc
typedef|typedef
name|void
function_decl|(
modifier|*
name|GimpDataFileLoaderFunc
function_decl|)
parameter_list|(
specifier|const
name|gchar
modifier|*
name|filename
parameter_list|,
name|gpointer
name|loader_data
parameter_list|)
function_decl|;
end_typedef

begin_typedef
DECL|typedef|GimpDataObjectLoaderFunc
typedef|typedef
name|GimpData
modifier|*
function_decl|(
modifier|*
name|GimpDataObjectLoaderFunc
function_decl|)
parameter_list|(
specifier|const
name|gchar
modifier|*
name|filename
parameter_list|)
function_decl|;
end_typedef

begin_endif
endif|#
directive|endif
end_endif

begin_comment
comment|/* __APPTYPES_H__ */
end_comment

end_unit

