begin_unit|revision:0.9.5;language:C;cregit-version:0.0.1
begin_comment
comment|/* The GIMP -- an image manipulation program  * Copyright (C) 1995 Spencer Kimball and Peter Mattis  *  * This program is free software; you can redistribute it and/or modify  * it under the terms of the GNU General Public License as published by  * the Free Software Foundation; either version 2 of the License, or  * (at your option) any later version.  *  * This program is distributed in the hope that it will be useful,  * but WITHOUT ANY WARRANTY; without even the implied warranty of  * MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the  * GNU General Public License for more details.  *  * You should have received a copy of the GNU General Public License  * along with this program; if not, write to the Free Software  * Foundation, Inc., 59 Temple Place - Suite 330, Boston, MA 02111-1307, USA.  */
end_comment

begin_ifndef
ifndef|#
directive|ifndef
name|__PAINT_TYPES_H__
end_ifndef

begin_define
DECL|macro|__PAINT_TYPES_H__
define|#
directive|define
name|__PAINT_TYPES_H__
end_define

begin_include
include|#
directive|include
file|"core/core-types.h"
end_include

begin_comment
comment|/*  objects  */
end_comment

begin_typedef
DECL|typedef|GimpPaintCore
typedef|typedef
name|struct
name|_GimpPaintCore
name|GimpPaintCore
typedef|;
end_typedef

begin_typedef
DECL|typedef|GimpPaintOptions
typedef|typedef
name|struct
name|_GimpPaintOptions
name|GimpPaintOptions
typedef|;
end_typedef

begin_comment
comment|/*  functions  */
end_comment

begin_typedef
DECL|typedef|GimpPaintRegisterCallback
typedef|typedef
name|void
function_decl|(
modifier|*
name|GimpPaintRegisterCallback
function_decl|)
parameter_list|(
name|Gimp
modifier|*
name|gimp
parameter_list|,
name|GType
name|tool_type
parameter_list|)
function_decl|;
end_typedef

begin_typedef
DECL|typedef|GimpPaintRegisterFunc
typedef|typedef
name|void
function_decl|(
modifier|*
name|GimpPaintRegisterFunc
function_decl|)
parameter_list|(
name|Gimp
modifier|*
name|gimp
parameter_list|,
name|GimpPaintRegisterCallback
name|callback
parameter_list|)
function_decl|;
end_typedef

begin_comment
comment|/*  enums  */
end_comment

begin_comment
comment|/* Brush application types  */
end_comment

begin_typedef
typedef|typedef
enum|enum
DECL|enum|__anon29934e550103
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
DECL|enum|__anon29934e550203
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

begin_comment
comment|/* gradient paint modes */
end_comment

begin_typedef
typedef|typedef
enum|enum
DECL|enum|__anon29934e550303
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
comment|/* paint once, but keep painting with the end color */
DECL|typedef|GradientPaintMode
block|}
name|GradientPaintMode
typedef|;
end_typedef

begin_typedef
typedef|typedef
enum|enum
DECL|enum|__anon29934e550403
block|{
DECL|enumerator|DODGE
name|DODGE
block|,
DECL|enumerator|BURN
name|BURN
DECL|typedef|DodgeBurnType
block|}
name|DodgeBurnType
typedef|;
end_typedef

begin_typedef
typedef|typedef
enum|enum
DECL|enum|__anon29934e550503
block|{
DECL|enumerator|BLUR_CONVOLVE
name|BLUR_CONVOLVE
block|,
DECL|enumerator|SHARPEN_CONVOLVE
name|SHARPEN_CONVOLVE
block|,
DECL|enumerator|CUSTOM_CONVOLVE
name|CUSTOM_CONVOLVE
DECL|typedef|ConvolveType
block|}
name|ConvolveType
typedef|;
end_typedef

begin_typedef
typedef|typedef
enum|enum
DECL|enum|__anon29934e550603
block|{
DECL|enumerator|IMAGE_CLONE
name|IMAGE_CLONE
block|,
DECL|enumerator|PATTERN_CLONE
name|PATTERN_CLONE
DECL|typedef|CloneType
block|}
name|CloneType
typedef|;
end_typedef

begin_endif
endif|#
directive|endif
end_endif

begin_comment
comment|/* __PAINT_TYPES_H__ */
end_comment

end_unit

