begin_unit|revision:0.9.5;language:C;cregit-version:0.0.1
begin_comment
comment|/* The GIMP -- an image manipulation program  * Copyright (C) 1995 Spencer Kimball and Peter Mattis  *  * This program is free software; you can redistribute it and/or modify  * it under the terms of the GNU General Public License as published by  * the Free Software Foundation; either version 2 of the License, or  * (at your option) any later version.  *  * This program is distributed in the hope that it will be useful,  * but WITHOUT ANY WARRANTY; without even the implied warranty of  * MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the  * GNU General Public License for more details.  *  * You should have received a copy of the GNU General Public License  * along with this program; if not, write to the Free Software  * Foundation, Inc., 59 Temple Place - Suite 330, Boston, MA 02111-1307, USA.  */
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
file|"libgimpmath/gimpmath.h"
end_include

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
DECL|macro|GIMP_COORDS_DEFAULT_VALUES
define|#
directive|define
name|GIMP_COORDS_DEFAULT_VALUES
value|{ 0.0, 0.0, \                                       GIMP_COORDS_DEFAULT_PRESSURE, \                                       GIMP_COORDS_DEFAULT_TILT,     \                                       GIMP_COORDS_DEFAULT_TILT,     \                                       GIMP_COORDS_DEFAULT_WHEEL }
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
DECL|typedef|GimpPatternClipboard
typedef|typedef
name|struct
name|_GimpPatternClipboard
name|GimpPatternClipboard
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
DECL|typedef|GimpLayerMask
typedef|typedef
name|struct
name|_GimpLayerMask
name|GimpLayerMask
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
DECL|typedef|GimpItemUndo
typedef|typedef
name|struct
name|_GimpItemUndo
name|GimpItemUndo
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

begin_comment
comment|/* typedef struct _GimpGrid         GimpGrid; in config-types.h */
end_comment

begin_typedef
DECL|typedef|GimpGuide
typedef|typedef
name|struct
name|_GimpGuide
name|GimpGuide
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
DECL|typedef|GimpImageMap
typedef|typedef
name|struct
name|_GimpImageMap
name|GimpImageMap
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
DECL|typedef|GimpStrokeDesc
typedef|typedef
name|struct
name|_GimpStrokeDesc
name|GimpStrokeDesc
typedef|;
end_typedef

begin_comment
comment|/* typedef struct _GimpTemplate     GimpTemplate; in config-types.h */
end_comment

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
DECL|typedef|GimpSamplePoint
typedef|typedef
name|struct
name|_GimpSamplePoint
name|GimpSamplePoint
typedef|;
end_typedef

begin_typedef
DECL|typedef|GimpTattoo
typedef|typedef
name|guint32
name|GimpTattoo
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
DECL|typedef|GimpPlugInDebug
typedef|typedef
name|struct
name|_GimpPlugInDebug
name|GimpPlugInDebug
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
DECL|typedef|GimpUndoPopFunc
typedef|typedef
name|gboolean
function_decl|(
modifier|*
name|GimpUndoPopFunc
function_decl|)
parameter_list|(
name|GimpUndo
modifier|*
name|undo
parameter_list|,
name|GimpUndoMode
name|undo_mode
parameter_list|,
name|GimpUndoAccumulator
modifier|*
name|accum
parameter_list|)
function_decl|;
end_typedef

begin_typedef
DECL|typedef|GimpUndoFreeFunc
typedef|typedef
name|void
function_decl|(
modifier|*
name|GimpUndoFreeFunc
function_decl|)
parameter_list|(
name|GimpUndo
modifier|*
name|undo
parameter_list|,
name|GimpUndoMode
name|undo_mode
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
block|}
struct|;
end_struct

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

