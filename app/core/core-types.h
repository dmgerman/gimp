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
file|"pdb/pdb-types.h"
end_include

begin_include
include|#
directive|include
file|"plug-in/plug-in-types.h"
end_include

begin_include
include|#
directive|include
file|"undo_types.h"
end_include

begin_comment
comment|/* EEK */
end_comment

begin_include
include|#
directive|include
file|"core/core-enums.h"
end_include

begin_comment
comment|/*  enums  */
end_comment

begin_typedef
typedef|typedef
enum|enum
DECL|enum|__anon2c6fe1b50103
block|{
DECL|enumerator|RGB
name|RGB
block|,
DECL|enumerator|GRAY
name|GRAY
block|,
DECL|enumerator|INDEXED
name|INDEXED
DECL|typedef|GimpImageBaseType
block|}
name|GimpImageBaseType
typedef|;
end_typedef

begin_typedef
typedef|typedef
enum|enum
DECL|enum|__anon2c6fe1b50203
block|{
DECL|enumerator|RGB_GIMAGE
name|RGB_GIMAGE
block|,
comment|/*< nick=RGB_IMAGE>*/
DECL|enumerator|RGBA_GIMAGE
name|RGBA_GIMAGE
block|,
comment|/*< nick=RGBA_IMAGE>*/
DECL|enumerator|GRAY_GIMAGE
name|GRAY_GIMAGE
block|,
comment|/*< nick=GRAY_IMAGE>*/
DECL|enumerator|GRAYA_GIMAGE
name|GRAYA_GIMAGE
block|,
comment|/*< nick=GRAYA_IMAGE>*/
DECL|enumerator|INDEXED_GIMAGE
name|INDEXED_GIMAGE
block|,
comment|/*< nick=INDEXED_IMAGE>*/
DECL|enumerator|INDEXEDA_GIMAGE
name|INDEXEDA_GIMAGE
comment|/*< nick=INDEXEDA_IMAGE>*/
DECL|typedef|GimpImageType
block|}
name|GimpImageType
typedef|;
end_typedef

begin_typedef
typedef|typedef
enum|enum
DECL|enum|__anon2c6fe1b50303
block|{
DECL|enumerator|RED_CHANNEL
name|RED_CHANNEL
block|,
DECL|enumerator|GREEN_CHANNEL
name|GREEN_CHANNEL
block|,
DECL|enumerator|BLUE_CHANNEL
name|BLUE_CHANNEL
block|,
DECL|enumerator|GRAY_CHANNEL
name|GRAY_CHANNEL
block|,
DECL|enumerator|INDEXED_CHANNEL
name|INDEXED_CHANNEL
block|,
DECL|enumerator|ALPHA_CHANNEL
name|ALPHA_CHANNEL
DECL|typedef|ChannelType
block|}
name|ChannelType
typedef|;
end_typedef

begin_typedef
typedef|typedef
enum|enum
comment|/*< chop=ADD_>*/
DECL|enum|__anon2c6fe1b50403
block|{
DECL|enumerator|ADD_WHITE_MASK
name|ADD_WHITE_MASK
block|,
DECL|enumerator|ADD_BLACK_MASK
name|ADD_BLACK_MASK
block|,
DECL|enumerator|ADD_ALPHA_MASK
name|ADD_ALPHA_MASK
block|,
DECL|enumerator|ADD_SELECTION_MASK
name|ADD_SELECTION_MASK
block|,
DECL|enumerator|ADD_INV_SELECTION_MASK
name|ADD_INV_SELECTION_MASK
DECL|typedef|AddMaskType
block|}
name|AddMaskType
typedef|;
end_typedef

begin_typedef
typedef|typedef
enum|enum
DECL|enum|__anon2c6fe1b50503
block|{
DECL|enumerator|APPLY
name|APPLY
block|,
DECL|enumerator|DISCARD
name|DISCARD
DECL|typedef|MaskApplyMode
block|}
name|MaskApplyMode
typedef|;
end_typedef

begin_typedef
typedef|typedef
enum|enum
DECL|enum|__anon2c6fe1b50603
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
DECL|enum|__anon2c6fe1b50703
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
comment|/*< chop=CHANNEL_OP_>*/
DECL|enum|__anon2c6fe1b50803
block|{
DECL|enumerator|CHANNEL_OP_ADD
name|CHANNEL_OP_ADD
block|,
DECL|enumerator|CHANNEL_OP_SUB
name|CHANNEL_OP_SUB
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
comment|/*< pdb-skip>*/
DECL|enum|__anon2c6fe1b50903
block|{
DECL|enumerator|GIMP_SELECTION_OFF
name|GIMP_SELECTION_OFF
block|,
DECL|enumerator|GIMP_SELECTION_LAYER_OFF
name|GIMP_SELECTION_LAYER_OFF
block|,
DECL|enumerator|GIMP_SELECTION_ON
name|GIMP_SELECTION_ON
block|,
DECL|enumerator|GIMP_SELECTION_PAUSE
name|GIMP_SELECTION_PAUSE
block|,
DECL|enumerator|GIMP_SELECTION_RESUME
name|GIMP_SELECTION_RESUME
DECL|typedef|GimpSelectionControl
block|}
name|GimpSelectionControl
typedef|;
end_typedef

begin_typedef
typedef|typedef
enum|enum
DECL|enum|__anon2c6fe1b50a03
block|{
DECL|enumerator|FOREGROUND_FILL
name|FOREGROUND_FILL
block|,
comment|/*< nick=FG_IMAGE_FILL>*/
DECL|enumerator|BACKGROUND_FILL
name|BACKGROUND_FILL
block|,
comment|/*< nick=BG_IMAGE_FILL>*/
DECL|enumerator|WHITE_FILL
name|WHITE_FILL
block|,
comment|/*< nick=WHITE_IMAGE_FILL>*/
DECL|enumerator|TRANSPARENT_FILL
name|TRANSPARENT_FILL
block|,
comment|/*< nick=TRANS_IMAGE_FILL>*/
DECL|enumerator|NO_FILL
name|NO_FILL
comment|/*< nick=NO_IMAGE_FILL>*/
DECL|typedef|GimpFillType
block|}
name|GimpFillType
typedef|;
end_typedef

begin_typedef
typedef|typedef
enum|enum
DECL|enum|__anon2c6fe1b50b03
block|{
DECL|enumerator|GIMP_SHADOWS
name|GIMP_SHADOWS
block|,
DECL|enumerator|GIMP_MIDTONES
name|GIMP_MIDTONES
block|,
DECL|enumerator|GIMP_HIGHLIGHTS
name|GIMP_HIGHLIGHTS
DECL|typedef|GimpTransferMode
block|}
name|GimpTransferMode
typedef|;
end_typedef

begin_typedef
typedef|typedef
enum|enum
DECL|enum|__anon2c6fe1b50c03
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
DECL|enum|__anon2c6fe1b50d03
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
DECL|enum|__anon2c6fe1b50e03
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
DECL|enum|__anon2c6fe1b50f03
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
DECL|enum|__anon2c6fe1b51003
block|{
DECL|enumerator|FG_BUCKET_FILL
name|FG_BUCKET_FILL
block|,
DECL|enumerator|BG_BUCKET_FILL
name|BG_BUCKET_FILL
block|,
DECL|enumerator|PATTERN_BUCKET_FILL
name|PATTERN_BUCKET_FILL
DECL|typedef|BucketFillMode
block|}
name|BucketFillMode
typedef|;
end_typedef

begin_typedef
typedef|typedef
enum|enum
DECL|enum|__anon2c6fe1b51103
block|{
DECL|enumerator|LINEAR
name|LINEAR
block|,
DECL|enumerator|BILINEAR
name|BILINEAR
block|,
DECL|enumerator|RADIAL
name|RADIAL
block|,
DECL|enumerator|SQUARE
name|SQUARE
block|,
DECL|enumerator|CONICAL_SYMMETRIC
name|CONICAL_SYMMETRIC
block|,
DECL|enumerator|CONICAL_ASYMMETRIC
name|CONICAL_ASYMMETRIC
block|,
DECL|enumerator|SHAPEBURST_ANGULAR
name|SHAPEBURST_ANGULAR
block|,
DECL|enumerator|SHAPEBURST_SPHERICAL
name|SHAPEBURST_SPHERICAL
block|,
DECL|enumerator|SHAPEBURST_DIMPLED
name|SHAPEBURST_DIMPLED
block|,
DECL|enumerator|SPIRAL_CLOCKWISE
name|SPIRAL_CLOCKWISE
block|,
DECL|enumerator|SPIRAL_ANTICLOCKWISE
name|SPIRAL_ANTICLOCKWISE
DECL|typedef|GradientType
block|}
name|GradientType
typedef|;
end_typedef

begin_typedef
typedef|typedef
enum|enum
comment|/*< pdb-skip>*/
DECL|enum|__anon2c6fe1b51203
block|{
DECL|enumerator|GRAD_LINEAR
name|GRAD_LINEAR
init|=
literal|0
block|,
DECL|enumerator|GRAD_CURVED
name|GRAD_CURVED
block|,
DECL|enumerator|GRAD_SINE
name|GRAD_SINE
block|,
DECL|enumerator|GRAD_SPHERE_INCREASING
name|GRAD_SPHERE_INCREASING
block|,
DECL|enumerator|GRAD_SPHERE_DECREASING
name|GRAD_SPHERE_DECREASING
DECL|typedef|GimpGradientSegmentType
block|}
name|GimpGradientSegmentType
typedef|;
end_typedef

begin_typedef
typedef|typedef
enum|enum
comment|/*< pdb-skip>*/
DECL|enum|__anon2c6fe1b51303
block|{
DECL|enumerator|GRAD_RGB
name|GRAD_RGB
init|=
literal|0
block|,
comment|/* normal RGB */
DECL|enumerator|GRAD_HSV_CCW
name|GRAD_HSV_CCW
block|,
comment|/* counterclockwise hue */
DECL|enumerator|GRAD_HSV_CW
name|GRAD_HSV_CW
comment|/* clockwise hue */
DECL|typedef|GimpGradientSegmentColor
block|}
name|GimpGradientSegmentColor
typedef|;
end_typedef

begin_typedef
typedef|typedef
enum|enum
comment|/*< chop=_MODE>*/
DECL|enum|__anon2c6fe1b51403
block|{
DECL|enumerator|FG_BG_RGB_MODE
name|FG_BG_RGB_MODE
block|,
DECL|enumerator|FG_BG_HSV_MODE
name|FG_BG_HSV_MODE
block|,
DECL|enumerator|FG_TRANS_MODE
name|FG_TRANS_MODE
block|,
DECL|enumerator|CUSTOM_MODE
name|CUSTOM_MODE
DECL|typedef|BlendMode
block|}
name|BlendMode
typedef|;
end_typedef

begin_typedef
typedef|typedef
enum|enum
DECL|enum|__anon2c6fe1b51503
block|{
DECL|enumerator|REPEAT_NONE
name|REPEAT_NONE
block|,
DECL|enumerator|REPEAT_SAWTOOTH
name|REPEAT_SAWTOOTH
block|,
DECL|enumerator|REPEAT_TRIANGULAR
name|REPEAT_TRIANGULAR
DECL|typedef|RepeatMode
block|}
name|RepeatMode
typedef|;
end_typedef

begin_typedef
typedef|typedef
enum|enum
comment|/*< pdb-skip>*/
DECL|enum|__anon2c6fe1b51603
block|{
DECL|enumerator|GIMP_TRANSFORM_FORWARD
name|GIMP_TRANSFORM_FORWARD
block|,
DECL|enumerator|GIMP_TRANSFORM_BACKWARD
name|GIMP_TRANSFORM_BACKWARD
DECL|typedef|GimpTransformDirection
block|}
name|GimpTransformDirection
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
DECL|typedef|GimpBuffer
typedef|typedef
name|struct
name|_GimpBuffer
name|GimpBuffer
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

begin_endif
endif|#
directive|endif
end_endif

begin_comment
comment|/* __CORE_TYPES_H__ */
end_comment

end_unit

