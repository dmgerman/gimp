begin_unit|revision:0.9.5;language:C;cregit-version:0.0.1
begin_comment
comment|/* GIMP - The GNU Image Manipulation Program  * Copyright (C) 1995 Spencer Kimball and Peter Mattis  *  * This program is free software: you can redistribute it and/or modify  * it under the terms of the GNU General Public License as published by  * the Free Software Foundation; either version 3 of the License, or  * (at your option) any later version.  *  * This program is distributed in the hope that it will be useful,  * but WITHOUT ANY WARRANTY; without even the implied warranty of  * MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the  * GNU General Public License for more details.  *  * You should have received a copy of the GNU General Public License  * along with this program.  If not, see<http://www.gnu.org/licenses/>.  */
end_comment

begin_ifndef
ifndef|#
directive|ifndef
name|__CORE_TYPES_H__
end_ifndef

begin_define
DECL|macro|__CORE_TYPES_H__
define|#
directive|define
name|__CORE_TYPES_H__
end_define

begin_include
include|#
directive|include
file|"libgimpmodule/gimpmoduletypes.h"
end_include

begin_include
include|#
directive|include
file|"libgimpthumb/gimpthumb-types.h"
end_include

begin_include
include|#
directive|include
file|"base/base-types.h"
end_include

begin_include
include|#
directive|include
file|"core/core-enums.h"
end_include

begin_comment
comment|/*  defines  */
end_comment

begin_define
DECL|macro|GIMP_OPACITY_TRANSPARENT
define|#
directive|define
name|GIMP_OPACITY_TRANSPARENT
value|0.0
end_define

begin_define
DECL|macro|GIMP_OPACITY_OPAQUE
define|#
directive|define
name|GIMP_OPACITY_OPAQUE
value|1.0
end_define

begin_define
DECL|macro|GIMP_COORDS_MIN_PRESSURE
define|#
directive|define
name|GIMP_COORDS_MIN_PRESSURE
value|0.0
end_define

begin_define
DECL|macro|GIMP_COORDS_MAX_PRESSURE
define|#
directive|define
name|GIMP_COORDS_MAX_PRESSURE
value|1.0
end_define

begin_define
DECL|macro|GIMP_COORDS_DEFAULT_PRESSURE
define|#
directive|define
name|GIMP_COORDS_DEFAULT_PRESSURE
value|1.0
end_define

begin_define
DECL|macro|GIMP_COORDS_MIN_TILT
define|#
directive|define
name|GIMP_COORDS_MIN_TILT
value|-1.0
end_define

begin_define
DECL|macro|GIMP_COORDS_MAX_TILT
define|#
directive|define
name|GIMP_COORDS_MAX_TILT
value|1.0
end_define

begin_define
DECL|macro|GIMP_COORDS_DEFAULT_TILT
define|#
directive|define
name|GIMP_COORDS_DEFAULT_TILT
value|0.0
end_define

begin_define
DECL|macro|GIMP_COORDS_MIN_WHEEL
define|#
directive|define
name|GIMP_COORDS_MIN_WHEEL
value|0.0
end_define

begin_define
DECL|macro|GIMP_COORDS_MAX_WHEEL
define|#
directive|define
name|GIMP_COORDS_MAX_WHEEL
value|1.0
end_define

begin_define
DECL|macro|GIMP_COORDS_DEFAULT_WHEEL
define|#
directive|define
name|GIMP_COORDS_DEFAULT_WHEEL
value|0.5
end_define

begin_define
DECL|macro|GIMP_COORDS_DEFAULT_VELOCITY
define|#
directive|define
name|GIMP_COORDS_DEFAULT_VELOCITY
value|0.0
end_define

begin_define
DECL|macro|GIMP_COORDS_DEFAULT_DIRECTION
define|#
directive|define
name|GIMP_COORDS_DEFAULT_DIRECTION
value|0.0
end_define

begin_define
DECL|macro|GIMP_COORDS_DEFAULT_VALUES
define|#
directive|define
name|GIMP_COORDS_DEFAULT_VALUES
value|{ 0.0, 0.0, \                                         GIMP_COORDS_DEFAULT_PRESSURE, \                                         GIMP_COORDS_DEFAULT_TILT,     \                                         GIMP_COORDS_DEFAULT_TILT,     \                                         GIMP_COORDS_DEFAULT_WHEEL,    \                                         GIMP_COORDS_DEFAULT_VELOCITY, \                                         GIMP_COORDS_DEFAULT_DIRECTION }
end_define

begin_comment
comment|/*  base classes  */
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
DECL|typedef|GimpViewable
typedef|typedef
name|struct
name|_GimpViewable
name|GimpViewable
typedef|;
end_typedef

begin_typedef
DECL|typedef|GimpItem
typedef|typedef
name|struct
name|_GimpItem
name|GimpItem
typedef|;
end_typedef

begin_typedef
DECL|typedef|Gimp
typedef|typedef
name|struct
name|_Gimp
name|Gimp
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
comment|/*  containers  */
end_comment

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
DECL|typedef|GimpDocumentList
typedef|typedef
name|struct
name|_GimpDocumentList
name|GimpDocumentList
typedef|;
end_typedef

begin_typedef
DECL|typedef|GimpDrawableStack
typedef|typedef
name|struct
name|_GimpDrawableStack
name|GimpDrawableStack
typedef|;
end_typedef

begin_typedef
DECL|typedef|GimpFilteredContainer
typedef|typedef
name|struct
name|_GimpFilteredContainer
name|GimpFilteredContainer
typedef|;
end_typedef

begin_typedef
DECL|typedef|GimpItemStack
typedef|typedef
name|struct
name|_GimpItemStack
name|GimpItemStack
typedef|;
end_typedef

begin_typedef
DECL|typedef|GimpToolPresets
typedef|typedef
name|struct
name|_GimpToolPresets
name|GimpToolPresets
typedef|;
end_typedef

begin_comment
comment|/*  context objects  */
end_comment

begin_typedef
DECL|typedef|GimpContext
typedef|typedef
name|struct
name|_GimpContext
name|GimpContext
typedef|;
end_typedef

begin_typedef
DECL|typedef|GimpFillOptions
typedef|typedef
name|struct
name|_GimpFillOptions
name|GimpFillOptions
typedef|;
end_typedef

begin_typedef
DECL|typedef|GimpStrokeOptions
typedef|typedef
name|struct
name|_GimpStrokeOptions
name|GimpStrokeOptions
typedef|;
end_typedef

begin_typedef
DECL|typedef|GimpToolOptions
typedef|typedef
name|struct
name|_GimpToolOptions
name|GimpToolOptions
typedef|;
end_typedef

begin_comment
comment|/*  info objects  */
end_comment

begin_typedef
DECL|typedef|GimpPaintInfo
typedef|typedef
name|struct
name|_GimpPaintInfo
name|GimpPaintInfo
typedef|;
end_typedef

begin_typedef
DECL|typedef|GimpToolInfo
typedef|typedef
name|struct
name|_GimpToolInfo
name|GimpToolInfo
typedef|;
end_typedef

begin_comment
comment|/*  data objects  */
end_comment

begin_typedef
DECL|typedef|GimpDataFactory
typedef|typedef
name|struct
name|_GimpDataFactory
name|GimpDataFactory
typedef|;
end_typedef

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
DECL|typedef|GimpBrushClipboard
typedef|typedef
name|struct
name|_GimpBrushClipboard
name|GimpBrushClipboard
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
DECL|typedef|GimpCurve
typedef|typedef
name|struct
name|_GimpCurve
name|GimpCurve
typedef|;
end_typedef

begin_typedef
DECL|typedef|GimpDynamics
typedef|typedef
name|struct
name|_GimpDynamics
name|GimpDynamics
typedef|;
end_typedef

begin_typedef
DECL|typedef|GimpDynamicsOutput
typedef|typedef
name|struct
name|_GimpDynamicsOutput
name|GimpDynamicsOutput
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
DECL|typedef|GimpPalette
typedef|typedef
name|struct
name|_GimpPalette
name|GimpPalette
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
DECL|typedef|GimpPatternClipboard
typedef|typedef
name|struct
name|_GimpPatternClipboard
name|GimpPatternClipboard
typedef|;
end_typedef

begin_typedef
DECL|typedef|GimpTagCache
typedef|typedef
name|struct
name|_GimpTagCache
name|GimpTagCache
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
DECL|typedef|GimpLayerMask
typedef|typedef
name|struct
name|_GimpLayerMask
name|GimpLayerMask
typedef|;
end_typedef

begin_typedef
DECL|typedef|GimpSelection
typedef|typedef
name|struct
name|_GimpSelection
name|GimpSelection
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
DECL|typedef|GimpGroupLayer
typedef|typedef
name|struct
name|_GimpGroupLayer
name|GimpGroupLayer
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
DECL|typedef|GimpImageUndo
typedef|typedef
name|struct
name|_GimpImageUndo
name|GimpImageUndo
typedef|;
end_typedef

begin_typedef
DECL|typedef|GimpItemUndo
typedef|typedef
name|struct
name|_GimpItemUndo
name|GimpItemUndo
typedef|;
end_typedef

begin_typedef
DECL|typedef|GimpItemPropUndo
typedef|typedef
name|struct
name|_GimpItemPropUndo
name|GimpItemPropUndo
typedef|;
end_typedef

begin_typedef
DECL|typedef|GimpChannelUndo
typedef|typedef
name|struct
name|_GimpChannelUndo
name|GimpChannelUndo
typedef|;
end_typedef

begin_typedef
DECL|typedef|GimpChannelPropUndo
typedef|typedef
name|struct
name|_GimpChannelPropUndo
name|GimpChannelPropUndo
typedef|;
end_typedef

begin_typedef
DECL|typedef|GimpDrawableUndo
typedef|typedef
name|struct
name|_GimpDrawableUndo
name|GimpDrawableUndo
typedef|;
end_typedef

begin_typedef
DECL|typedef|GimpDrawableModUndo
typedef|typedef
name|struct
name|_GimpDrawableModUndo
name|GimpDrawableModUndo
typedef|;
end_typedef

begin_typedef
DECL|typedef|GimpLayerMaskUndo
typedef|typedef
name|struct
name|_GimpLayerMaskUndo
name|GimpLayerMaskUndo
typedef|;
end_typedef

begin_typedef
DECL|typedef|GimpLayerMaskPropUndo
typedef|typedef
name|struct
name|_GimpLayerMaskPropUndo
name|GimpLayerMaskPropUndo
typedef|;
end_typedef

begin_typedef
DECL|typedef|GimpLayerUndo
typedef|typedef
name|struct
name|_GimpLayerUndo
name|GimpLayerUndo
typedef|;
end_typedef

begin_typedef
DECL|typedef|GimpLayerPropUndo
typedef|typedef
name|struct
name|_GimpLayerPropUndo
name|GimpLayerPropUndo
typedef|;
end_typedef

begin_typedef
DECL|typedef|GimpGroupLayerUndo
typedef|typedef
name|struct
name|_GimpGroupLayerUndo
name|GimpGroupLayerUndo
typedef|;
end_typedef

begin_typedef
DECL|typedef|GimpMaskUndo
typedef|typedef
name|struct
name|_GimpMaskUndo
name|GimpMaskUndo
typedef|;
end_typedef

begin_typedef
DECL|typedef|GimpGuideUndo
typedef|typedef
name|struct
name|_GimpGuideUndo
name|GimpGuideUndo
typedef|;
end_typedef

begin_typedef
DECL|typedef|GimpSamplePointUndo
typedef|typedef
name|struct
name|_GimpSamplePointUndo
name|GimpSamplePointUndo
typedef|;
end_typedef

begin_typedef
DECL|typedef|GimpFloatingSelUndo
typedef|typedef
name|struct
name|_GimpFloatingSelUndo
name|GimpFloatingSelUndo
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

begin_typedef
DECL|typedef|GimpUndoAccumulator
typedef|typedef
name|struct
name|_GimpUndoAccumulator
name|GimpUndoAccumulator
typedef|;
end_typedef

begin_comment
comment|/*  misc objects  */
end_comment

begin_typedef
DECL|typedef|GimpBuffer
typedef|typedef
name|struct
name|_GimpBuffer
name|GimpBuffer
typedef|;
end_typedef

begin_typedef
DECL|typedef|GimpEnvironTable
typedef|typedef
name|struct
name|_GimpEnvironTable
name|GimpEnvironTable
typedef|;
end_typedef

begin_typedef
DECL|typedef|GimpGuide
typedef|typedef
name|struct
name|_GimpGuide
name|GimpGuide
typedef|;
end_typedef

begin_typedef
DECL|typedef|GimpImageMap
typedef|typedef
name|struct
name|_GimpImageMap
name|GimpImageMap
typedef|;
end_typedef

begin_typedef
DECL|typedef|GimpImageMapConfig
typedef|typedef
name|struct
name|_GimpImageMapConfig
name|GimpImageMapConfig
typedef|;
end_typedef

begin_typedef
DECL|typedef|GimpImagefile
typedef|typedef
name|struct
name|_GimpImagefile
name|GimpImagefile
typedef|;
end_typedef

begin_typedef
DECL|typedef|GimpInterpreterDB
typedef|typedef
name|struct
name|_GimpInterpreterDB
name|GimpInterpreterDB
typedef|;
end_typedef

begin_typedef
DECL|typedef|GimpParasiteList
typedef|typedef
name|struct
name|_GimpParasiteList
name|GimpParasiteList
typedef|;
end_typedef

begin_typedef
DECL|typedef|GimpPdbProgress
typedef|typedef
name|struct
name|_GimpPdbProgress
name|GimpPdbProgress
typedef|;
end_typedef

begin_typedef
DECL|typedef|GimpProjection
typedef|typedef
name|struct
name|_GimpProjection
name|GimpProjection
typedef|;
end_typedef

begin_typedef
DECL|typedef|GimpSubProgress
typedef|typedef
name|struct
name|_GimpSubProgress
name|GimpSubProgress
typedef|;
end_typedef

begin_typedef
DECL|typedef|GimpTag
typedef|typedef
name|struct
name|_GimpTag
name|GimpTag
typedef|;
end_typedef

begin_typedef
DECL|typedef|GimpTreeHandler
typedef|typedef
name|struct
name|_GimpTreeHandler
name|GimpTreeHandler
typedef|;
end_typedef

begin_comment
comment|/*  interfaces  */
end_comment

begin_typedef
DECL|typedef|GimpPickable
typedef|typedef
name|struct
name|_GimpPickable
name|GimpPickable
typedef|;
end_typedef

begin_comment
DECL|typedef|GimpPickable
comment|/* dummy typedef */
end_comment

begin_typedef
DECL|typedef|GimpProgress
typedef|typedef
name|struct
name|_GimpProgress
name|GimpProgress
typedef|;
end_typedef

begin_comment
DECL|typedef|GimpProgress
comment|/* dummy typedef */
end_comment

begin_typedef
DECL|typedef|GimpProjectable
typedef|typedef
name|struct
name|_GimpProjectable
name|GimpProjectable
typedef|;
end_typedef

begin_comment
DECL|typedef|GimpProjectable
comment|/* dummy typedef */
end_comment

begin_typedef
DECL|typedef|GimpTagged
typedef|typedef
name|struct
name|_GimpTagged
name|GimpTagged
typedef|;
end_typedef

begin_comment
DECL|typedef|GimpTagged
comment|/* dummy typedef */
end_comment

begin_comment
comment|/*  non-object types  */
end_comment

begin_typedef
DECL|typedef|GimpArea
typedef|typedef
name|struct
name|_GimpArea
name|GimpArea
typedef|;
end_typedef

begin_typedef
DECL|typedef|GimpCoords
typedef|typedef
name|struct
name|_GimpCoords
name|GimpCoords
typedef|;
end_typedef

begin_typedef
DECL|typedef|GimpGradientSegment
typedef|typedef
name|struct
name|_GimpGradientSegment
name|GimpGradientSegment
typedef|;
end_typedef

begin_typedef
DECL|typedef|GimpPaletteEntry
typedef|typedef
name|struct
name|_GimpPaletteEntry
name|GimpPaletteEntry
typedef|;
end_typedef

begin_typedef
DECL|typedef|GimpSamplePoint
typedef|typedef
name|struct
name|_GimpSamplePoint
name|GimpSamplePoint
typedef|;
end_typedef

begin_typedef
DECL|typedef|GimpScanConvert
typedef|typedef
name|struct
name|_GimpScanConvert
name|GimpScanConvert
typedef|;
end_typedef

begin_typedef
DECL|typedef|GimpTattoo
typedef|typedef
name|guint32
name|GimpTattoo
typedef|;
end_typedef

begin_comment
comment|/*  functions  */
end_comment

begin_typedef
DECL|typedef|GimpInitStatusFunc
typedef|typedef
name|void
function_decl|(
modifier|*
name|GimpInitStatusFunc
function_decl|)
parameter_list|(
specifier|const
name|gchar
modifier|*
name|text1
parameter_list|,
specifier|const
name|gchar
modifier|*
name|text2
parameter_list|,
name|gdouble
name|percentage
parameter_list|)
function_decl|;
end_typedef

begin_typedef
DECL|typedef|GimpObjectFilterFunc
typedef|typedef
name|gboolean
function_decl|(
modifier|*
name|GimpObjectFilterFunc
function_decl|)
parameter_list|(
specifier|const
name|GimpObject
modifier|*
name|object
parameter_list|,
name|gpointer
name|user_data
parameter_list|)
function_decl|;
end_typedef

begin_typedef
DECL|typedef|GimpMemsizeFunc
typedef|typedef
name|gint64
function_decl|(
modifier|*
name|GimpMemsizeFunc
function_decl|)
parameter_list|(
name|gpointer
name|instance
parameter_list|,
name|gint64
modifier|*
name|gui_size
parameter_list|)
function_decl|;
end_typedef

begin_typedef
DECL|typedef|GimpImageMapApplyFunc
typedef|typedef
name|void
function_decl|(
modifier|*
name|GimpImageMapApplyFunc
function_decl|)
parameter_list|(
name|gpointer
name|apply_data
parameter_list|,
name|PixelRegion
modifier|*
name|srcPR
parameter_list|,
name|PixelRegion
modifier|*
name|destPR
parameter_list|)
function_decl|;
end_typedef

begin_comment
comment|/*  structs  */
end_comment

begin_struct
DECL|struct|_GimpCoords
struct|struct
name|_GimpCoords
block|{
DECL|member|x
name|gdouble
name|x
decl_stmt|;
DECL|member|y
name|gdouble
name|y
decl_stmt|;
DECL|member|pressure
name|gdouble
name|pressure
decl_stmt|;
DECL|member|xtilt
name|gdouble
name|xtilt
decl_stmt|;
DECL|member|ytilt
name|gdouble
name|ytilt
decl_stmt|;
DECL|member|wheel
name|gdouble
name|wheel
decl_stmt|;
DECL|member|velocity
name|gdouble
name|velocity
decl_stmt|;
DECL|member|direction
name|gdouble
name|direction
decl_stmt|;
block|}
struct|;
end_struct

begin_include
include|#
directive|include
file|"gegl/gimp-gegl-types.h"
end_include

begin_include
include|#
directive|include
file|"paint/paint-types.h"
end_include

begin_include
include|#
directive|include
file|"text/text-types.h"
end_include

begin_include
include|#
directive|include
file|"vectors/vectors-types.h"
end_include

begin_include
include|#
directive|include
file|"pdb/pdb-types.h"
end_include

begin_include
include|#
directive|include
file|"plug-in/plug-in-types.h"
end_include

begin_endif
endif|#
directive|endif
end_endif

begin_comment
comment|/* __CORE_TYPES_H__ */
end_comment

end_unit

