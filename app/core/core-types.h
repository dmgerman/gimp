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
file|"libgimpbase/gimpbasetypes.h"
end_include

begin_include
include|#
directive|include
file|"libgimpmath/gimpmath.h"
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

begin_comment
comment|/*  enums  */
end_comment

begin_typedef
typedef|typedef
enum|enum
DECL|enum|__anon27680e050103
block|{
DECL|enumerator|HORIZONTAL
name|HORIZONTAL
block|,
DECL|enumerator|VERTICAL
name|VERTICAL
block|,
DECL|enumerator|UNKNOWN
name|UNKNOWN
DECL|typedef|OrientationType
block|}
name|OrientationType
typedef|;
end_typedef

begin_typedef
typedef|typedef
enum|enum
comment|/*< pdb-skip>*/
DECL|enum|__anon27680e050203
block|{
DECL|enumerator|ORIENTATION_UNKNOWN
name|ORIENTATION_UNKNOWN
block|,
DECL|enumerator|ORIENTATION_HORIZONTAL
name|ORIENTATION_HORIZONTAL
block|,
DECL|enumerator|ORIENTATION_VERTICAL
name|ORIENTATION_VERTICAL
DECL|typedef|InternalOrientationType
block|}
name|InternalOrientationType
typedef|;
end_typedef

begin_comment
comment|/*  Selection Boolean operations  */
end_comment

begin_typedef
typedef|typedef
enum|enum
DECL|enum|__anon27680e050303
block|{
DECL|enumerator|CHANNEL_OP_ADD
name|CHANNEL_OP_ADD
block|,
DECL|enumerator|CHANNEL_OP_SUBTRACT
name|CHANNEL_OP_SUBTRACT
block|,
DECL|enumerator|CHANNEL_OP_REPLACE
name|CHANNEL_OP_REPLACE
block|,
DECL|enumerator|CHANNEL_OP_INTERSECT
name|CHANNEL_OP_INTERSECT
DECL|typedef|ChannelOps
block|}
name|ChannelOps
typedef|;
end_typedef

begin_typedef
typedef|typedef
enum|enum
DECL|enum|__anon27680e050403
block|{
DECL|enumerator|OFFSET_BACKGROUND
name|OFFSET_BACKGROUND
block|,
DECL|enumerator|OFFSET_TRANSPARENT
name|OFFSET_TRANSPARENT
DECL|typedef|GimpOffsetType
block|}
name|GimpOffsetType
typedef|;
end_typedef

begin_typedef
typedef|typedef
enum|enum
DECL|enum|__anon27680e050503
block|{
DECL|enumerator|EXPAND_AS_NECESSARY
name|EXPAND_AS_NECESSARY
block|,
DECL|enumerator|CLIP_TO_IMAGE
name|CLIP_TO_IMAGE
block|,
DECL|enumerator|CLIP_TO_BOTTOM_LAYER
name|CLIP_TO_BOTTOM_LAYER
block|,
DECL|enumerator|FLATTEN_IMAGE
name|FLATTEN_IMAGE
DECL|typedef|MergeType
block|}
name|MergeType
typedef|;
end_typedef

begin_typedef
typedef|typedef
enum|enum
DECL|enum|__anon27680e050603
block|{
DECL|enumerator|MAKE_PALETTE
name|MAKE_PALETTE
init|=
literal|0
block|,
DECL|enumerator|REUSE_PALETTE
name|REUSE_PALETTE
init|=
literal|1
block|,
DECL|enumerator|WEB_PALETTE
name|WEB_PALETTE
init|=
literal|2
block|,
DECL|enumerator|MONO_PALETTE
name|MONO_PALETTE
init|=
literal|3
block|,
DECL|enumerator|CUSTOM_PALETTE
name|CUSTOM_PALETTE
init|=
literal|4
DECL|typedef|ConvertPaletteType
block|}
name|ConvertPaletteType
typedef|;
end_typedef

begin_typedef
typedef|typedef
enum|enum
DECL|enum|__anon27680e050703
block|{
DECL|enumerator|NO_DITHER
name|NO_DITHER
init|=
literal|0
block|,
DECL|enumerator|FS_DITHER
name|FS_DITHER
init|=
literal|1
block|,
DECL|enumerator|FSLOWBLEED_DITHER
name|FSLOWBLEED_DITHER
init|=
literal|2
block|,
DECL|enumerator|FIXED_DITHER
name|FIXED_DITHER
init|=
literal|3
block|,
DECL|enumerator|NODESTRUCT_DITHER
name|NODESTRUCT_DITHER
init|=
literal|4
comment|/* NEVER USE NODESTRUCT_DITHER EXPLICITLY */
DECL|typedef|ConvertDitherType
block|}
name|ConvertDitherType
typedef|;
end_typedef

begin_typedef
typedef|typedef
enum|enum
comment|/*< pdb-skip>*/
comment|/*< skip>*/
DECL|enum|__anon27680e050803
block|{
comment|/* NOTE: If you change this list, please update the textual mapping at    *  the bottom of undo.c as well.    */
comment|/* Type NO_UNDO_GROUP (0) is special - in the gimpimage structure it    * means there is no undo group currently being added to.    */
DECL|enumerator|NO_UNDO_GROUP
name|NO_UNDO_GROUP
init|=
literal|0
block|,
DECL|enumerator|FIRST_UNDO_GROUP
name|FIRST_UNDO_GROUP
init|=
name|NO_UNDO_GROUP
block|,
DECL|enumerator|IMAGE_SCALE_UNDO_GROUP
name|IMAGE_SCALE_UNDO_GROUP
block|,
DECL|enumerator|IMAGE_RESIZE_UNDO_GROUP
name|IMAGE_RESIZE_UNDO_GROUP
block|,
DECL|enumerator|IMAGE_CONVERT_UNDO_GROUP
name|IMAGE_CONVERT_UNDO_GROUP
block|,
DECL|enumerator|IMAGE_CROP_UNDO_GROUP
name|IMAGE_CROP_UNDO_GROUP
block|,
DECL|enumerator|IMAGE_LAYERS_MERGE_UNDO_GROUP
name|IMAGE_LAYERS_MERGE_UNDO_GROUP
block|,
DECL|enumerator|IMAGE_QMASK_UNDO_GROUP
name|IMAGE_QMASK_UNDO_GROUP
block|,
DECL|enumerator|IMAGE_GUIDE_UNDO_GROUP
name|IMAGE_GUIDE_UNDO_GROUP
block|,
DECL|enumerator|LAYER_PROPERTIES_UNDO_GROUP
name|LAYER_PROPERTIES_UNDO_GROUP
block|,
DECL|enumerator|LAYER_SCALE_UNDO_GROUP
name|LAYER_SCALE_UNDO_GROUP
block|,
DECL|enumerator|LAYER_RESIZE_UNDO_GROUP
name|LAYER_RESIZE_UNDO_GROUP
block|,
DECL|enumerator|LAYER_DISPLACE_UNDO_GROUP
name|LAYER_DISPLACE_UNDO_GROUP
block|,
DECL|enumerator|LAYER_LINKED_UNDO_GROUP
name|LAYER_LINKED_UNDO_GROUP
block|,
DECL|enumerator|LAYER_APPLY_MASK_UNDO_GROUP
name|LAYER_APPLY_MASK_UNDO_GROUP
block|,
DECL|enumerator|FS_FLOAT_UNDO_GROUP
name|FS_FLOAT_UNDO_GROUP
block|,
DECL|enumerator|FS_ANCHOR_UNDO_GROUP
name|FS_ANCHOR_UNDO_GROUP
block|,
DECL|enumerator|EDIT_PASTE_UNDO_GROUP
name|EDIT_PASTE_UNDO_GROUP
block|,
DECL|enumerator|EDIT_CUT_UNDO_GROUP
name|EDIT_CUT_UNDO_GROUP
block|,
DECL|enumerator|TEXT_UNDO_GROUP
name|TEXT_UNDO_GROUP
block|,
DECL|enumerator|TRANSFORM_UNDO_GROUP
name|TRANSFORM_UNDO_GROUP
block|,
DECL|enumerator|PAINT_UNDO_GROUP
name|PAINT_UNDO_GROUP
block|,
DECL|enumerator|PARASITE_ATTACH_UNDO_GROUP
name|PARASITE_ATTACH_UNDO_GROUP
block|,
DECL|enumerator|PARASITE_REMOVE_UNDO_GROUP
name|PARASITE_REMOVE_UNDO_GROUP
block|,
DECL|enumerator|MISC_UNDO_GROUP
name|MISC_UNDO_GROUP
block|,
DECL|enumerator|LAST_UNDO_GROUP
name|LAST_UNDO_GROUP
init|=
name|MISC_UNDO_GROUP
DECL|typedef|UndoType
block|}
name|UndoType
typedef|;
end_typedef

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
DECL|typedef|Gimp
typedef|typedef
name|struct
name|_Gimp
name|Gimp
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
DECL|typedef|GimpModuleInfoObj
typedef|typedef
name|struct
name|_GimpModuleInfoObj
name|GimpModuleInfoObj
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

begin_typedef
DECL|typedef|GimpItem
typedef|typedef
name|struct
name|_GimpItem
name|GimpItem
typedef|;
end_typedef

begin_typedef
DECL|typedef|GimpBuffer
typedef|typedef
name|struct
name|_GimpBuffer
name|GimpBuffer
typedef|;
end_typedef

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

begin_typedef
DECL|typedef|GimpImagefile
typedef|typedef
name|struct
name|_GimpImagefile
name|GimpImagefile
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
comment|/*  other objects  */
end_comment

begin_typedef
DECL|typedef|ImageMap
typedef|typedef
name|struct
name|_ImageMap
name|ImageMap
typedef|;
end_typedef

begin_comment
DECL|typedef|ImageMap
comment|/* temp_hack, will be an object */
end_comment

begin_comment
comment|/*  non-object types  */
end_comment

begin_typedef
DECL|typedef|GimpCoords
typedef|typedef
name|struct
name|_GimpCoords
name|GimpCoords
typedef|;
end_typedef

begin_typedef
DECL|typedef|GimpCoreConfig
typedef|typedef
name|struct
name|_GimpCoreConfig
name|GimpCoreConfig
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
DECL|typedef|GimpImageNewValues
typedef|typedef
name|struct
name|_GimpImageNewValues
name|GimpImageNewValues
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

begin_comment
comment|/*  EEK stuff  */
end_comment

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

begin_comment
comment|/*  stuff which is forward declared here so we don't need to cross-include it  */
end_comment

begin_typedef
DECL|typedef|GimpToolOptions
typedef|typedef
name|struct
name|_GimpToolOptions
name|GimpToolOptions
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

