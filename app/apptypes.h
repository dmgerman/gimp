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

begin_comment
comment|/* To avoid problems with headers including each others like spaghetti  * (even recursively), and various types not being defined when they  * are needed depending on the order you happen to include headers,  * this file defines those enumeration and opaque struct types that  * don't depend on any other header. These problems began creeping up  * when we started to actually use these enums in function prototypes. */
end_comment

begin_comment
comment|/* Should we instead use the enums in libgimp/gimpenums.h? */
end_comment

begin_comment
comment|/* Base image types */
end_comment

begin_typedef
typedef|typedef
enum|enum
DECL|enum|__anon2ba374320103
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

begin_comment
comment|/* Image types */
end_comment

begin_typedef
typedef|typedef
enum|enum
DECL|enum|__anon2ba374320203
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

begin_comment
comment|/* Fill types */
end_comment

begin_typedef
typedef|typedef
enum|enum
DECL|enum|__anon2ba374320303
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

begin_comment
comment|/* Layer modes  */
end_comment

begin_typedef
typedef|typedef
enum|enum
DECL|enum|__anon2ba374320403
block|{
DECL|enumerator|NORMAL_MODE
name|NORMAL_MODE
block|,
DECL|enumerator|DISSOLVE_MODE
name|DISSOLVE_MODE
block|,
DECL|enumerator|BEHIND_MODE
name|BEHIND_MODE
block|,
DECL|enumerator|MULTIPLY_MODE
name|MULTIPLY_MODE
block|,
DECL|enumerator|SCREEN_MODE
name|SCREEN_MODE
block|,
DECL|enumerator|OVERLAY_MODE
name|OVERLAY_MODE
block|,
DECL|enumerator|DIFFERENCE_MODE
name|DIFFERENCE_MODE
block|,
DECL|enumerator|ADDITION_MODE
name|ADDITION_MODE
block|,
DECL|enumerator|SUBTRACT_MODE
name|SUBTRACT_MODE
block|,
DECL|enumerator|DARKEN_ONLY_MODE
name|DARKEN_ONLY_MODE
block|,
DECL|enumerator|LIGHTEN_ONLY_MODE
name|LIGHTEN_ONLY_MODE
block|,
DECL|enumerator|HUE_MODE
name|HUE_MODE
block|,
DECL|enumerator|SATURATION_MODE
name|SATURATION_MODE
block|,
DECL|enumerator|COLOR_MODE
name|COLOR_MODE
block|,
DECL|enumerator|VALUE_MODE
name|VALUE_MODE
block|,
DECL|enumerator|DIVIDE_MODE
name|DIVIDE_MODE
block|,
DECL|enumerator|ERASE_MODE
name|ERASE_MODE
block|,
comment|/*< skip>*/
DECL|enumerator|REPLACE_MODE
name|REPLACE_MODE
block|,
comment|/*< skip>*/
DECL|enumerator|ANTI_ERASE_MODE
name|ANTI_ERASE_MODE
block|,
comment|/*< skip>*/
DECL|typedef|LayerModeEffects
block|}
name|LayerModeEffects
typedef|;
end_typedef

begin_comment
comment|/* Types of convolutions  */
end_comment

begin_typedef
typedef|typedef
enum|enum
DECL|enum|__anon2ba374320503
block|{
DECL|enumerator|NORMAL_CONVOL
name|NORMAL_CONVOL
block|,
comment|/*  Negative numbers truncated  */
DECL|enumerator|ABSOLUTE_CONVOL
name|ABSOLUTE_CONVOL
block|,
comment|/*  Absolute value              */
DECL|enumerator|NEGATIVE_CONVOL
name|NEGATIVE_CONVOL
comment|/*  add 127 to values           */
DECL|typedef|ConvolutionType
block|}
name|ConvolutionType
typedef|;
end_typedef

begin_comment
comment|/* Brush application types  */
end_comment

begin_typedef
typedef|typedef
enum|enum
DECL|enum|__anon2ba374320603
block|{
DECL|enumerator|HARD
name|HARD
block|,
comment|/* pencil */
DECL|enumerator|SOFT
name|SOFT
block|,
comment|/* paintbrush */
DECL|enumerator|PRESSURE
name|PRESSURE
comment|/* paintbrush with variable pressure */
DECL|typedef|BrushApplicationMode
block|}
name|BrushApplicationMode
typedef|;
end_typedef

begin_comment
comment|/* Paint application modes  */
end_comment

begin_typedef
typedef|typedef
enum|enum
DECL|enum|__anon2ba374320703
block|{
DECL|enumerator|CONSTANT
name|CONSTANT
block|,
comment|/*< nick=CONTINUOUS>*/
comment|/* pencil, paintbrush, airbrush, clone */
DECL|enumerator|INCREMENTAL
name|INCREMENTAL
comment|/* convolve, smudge */
DECL|typedef|PaintApplicationMode
block|}
name|PaintApplicationMode
typedef|;
end_typedef

begin_typedef
typedef|typedef
enum|enum
DECL|enum|__anon2ba374320803
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
comment|/*< chop=ADD_>*/
DECL|enum|__anon2ba374320903
block|{
DECL|enumerator|ADD_WHITE_MASK
name|ADD_WHITE_MASK
block|,
DECL|enumerator|ADD_BLACK_MASK
name|ADD_BLACK_MASK
block|,
DECL|enumerator|ADD_ALPHA_MASK
name|ADD_ALPHA_MASK
DECL|typedef|AddMaskType
block|}
name|AddMaskType
typedef|;
end_typedef

begin_comment
comment|/* gradient paint modes */
end_comment

begin_typedef
DECL|enum|__anon2ba374320a03
typedef|typedef
enum|enum
block|{
DECL|enumerator|ONCE_FORWARD
name|ONCE_FORWARD
block|,
comment|/* paint through once, then stop */
DECL|enumerator|ONCE_BACKWARDS
name|ONCE_BACKWARDS
block|,
comment|/* paint once, then stop, but run the gradient the other way */
DECL|enumerator|LOOP_SAWTOOTH
name|LOOP_SAWTOOTH
block|,
comment|/* keep painting, looping through the grad start->end,start->end /|/|/| */
DECL|enumerator|LOOP_TRIANGLE
name|LOOP_TRIANGLE
block|,
comment|/* keep paiting, looping though the grad start->end,end->start /\/\/\/  */
DECL|enumerator|ONCE_END_COLOR
name|ONCE_END_COLOR
block|,
comment|/* paint once, but keep painting with the end color */
DECL|typedef|GradientPaintMode
block|}
name|GradientPaintMode
typedef|;
end_typedef

begin_comment
comment|/* gradient paint modes */
end_comment

begin_typedef
typedef|typedef
enum|enum
DECL|enum|__anon2ba374320b03
block|{
DECL|enumerator|LINEAR_INTERPOLATION
name|LINEAR_INTERPOLATION
block|,
DECL|enumerator|CUBIC_INTERPOLATION
name|CUBIC_INTERPOLATION
block|,
DECL|enumerator|NEAREST_NEIGHBOR_INTERPOLATION
name|NEAREST_NEIGHBOR_INTERPOLATION
DECL|typedef|InterpolationType
block|}
name|InterpolationType
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
DECL|typedef|GimpChannelClass
typedef|typedef
name|struct
name|_GimpChannelClass
name|GimpChannelClass
typedef|;
end_typedef

begin_typedef
DECL|typedef|Channel
typedef|typedef
name|GimpChannel
name|Channel
typedef|;
end_typedef

begin_comment
DECL|typedef|Channel
comment|/* convenience */
end_comment

begin_typedef
DECL|typedef|GimpLayer
typedef|typedef
name|struct
name|_GimpLayer
name|GimpLayer
typedef|;
end_typedef

begin_typedef
DECL|typedef|GimpLayerClass
typedef|typedef
name|struct
name|_GimpLayerClass
name|GimpLayerClass
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
DECL|typedef|GimpLayerMaskClass
typedef|typedef
name|struct
name|_GimpLayerMaskClass
name|GimpLayerMaskClass
typedef|;
end_typedef

begin_typedef
DECL|typedef|Layer
typedef|typedef
name|GimpLayer
name|Layer
typedef|;
end_typedef

begin_comment
DECL|typedef|Layer
comment|/* convenience */
end_comment

begin_typedef
DECL|typedef|LayerMask
typedef|typedef
name|GimpLayerMask
name|LayerMask
typedef|;
end_typedef

begin_comment
DECL|typedef|LayerMask
comment|/* convenience */
end_comment

begin_typedef
DECL|typedef|LayerUndo
typedef|typedef
name|struct
name|_layer_undo
name|LayerUndo
typedef|;
end_typedef

begin_typedef
DECL|typedef|LayerMaskUndo
typedef|typedef
name|struct
name|_layer_mask_undo
name|LayerMaskUndo
typedef|;
end_typedef

begin_typedef
DECL|typedef|FStoLayerUndo
typedef|typedef
name|struct
name|_fs_to_layer_undo
name|FStoLayerUndo
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

begin_endif
endif|#
directive|endif
end_endif

begin_comment
comment|/* __APPTYPES_H__ */
end_comment

end_unit

