begin_unit|revision:0.9.5;language:C;cregit-version:0.0.1
begin_comment
comment|/* The GIMP -- an image manipulation program  * Copyright (C) 1995 Spencer Kimball and Peter Mattis  *  * This program is free software; you can redistribute it and/or modify  * it under the terms of the GNU General Public License as published by  * the Free Software Foundation; either version 2 of the License, or  * (at your option) any later version.  *  * This program is distributed in the hope that it will be useful,  * but WITHOUT ANY WARRANTY; without even the implied warranty of  * MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the  * GNU General Public License for more details.  *  * You should have received a copy of the GNU General Public License  * along with this program; if not, write to the Free Software  * Foundation, Inc., 59 Temple Place - Suite 330, Boston, MA 02111-1307, USA.  */
end_comment

begin_ifndef
ifndef|#
directive|ifndef
name|__BLEND_H__
end_ifndef

begin_define
DECL|macro|__BLEND_H__
define|#
directive|define
name|__BLEND_H__
end_define

begin_include
include|#
directive|include
file|"tools.h"
end_include

begin_include
include|#
directive|include
file|"procedural_db.h"
end_include

begin_typedef
typedef|typedef
enum|enum
DECL|enum|__anon27c860560103
block|{
DECL|enumerator|Linear
name|Linear
block|,
DECL|enumerator|BiLinear
name|BiLinear
block|,
DECL|enumerator|Radial
name|Radial
block|,
DECL|enumerator|Square
name|Square
block|,
DECL|enumerator|ConicalSymmetric
name|ConicalSymmetric
block|,
DECL|enumerator|ConicalAsymmetric
name|ConicalAsymmetric
block|,
DECL|enumerator|ShapeburstAngular
name|ShapeburstAngular
block|,
DECL|enumerator|ShapeburstSpherical
name|ShapeburstSpherical
block|,
DECL|enumerator|ShapeburstDimpled
name|ShapeburstDimpled
block|,
DECL|enumerator|SpiralClockwise
name|SpiralClockwise
block|,
DECL|enumerator|SpiralAntiClockwise
name|SpiralAntiClockwise
block|,
DECL|enumerator|GradientTypeLast
name|GradientTypeLast
comment|/*< skip>*/
DECL|typedef|GradientType
block|}
name|GradientType
typedef|;
end_typedef

begin_typedef
typedef|typedef
enum|enum
DECL|enum|__anon27c860560203
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
block|,
DECL|enumerator|BLEND_MODE_LAST
name|BLEND_MODE_LAST
comment|/*< skip>*/
DECL|typedef|BlendMode
block|}
name|BlendMode
typedef|;
end_typedef

begin_typedef
typedef|typedef
enum|enum
DECL|enum|__anon27c860560303
block|{
DECL|enumerator|REPEAT_NONE
name|REPEAT_NONE
block|,
DECL|enumerator|REPEAT_SAWTOOTH
name|REPEAT_SAWTOOTH
block|,
DECL|enumerator|REPEAT_TRIANGULAR
name|REPEAT_TRIANGULAR
block|,
DECL|enumerator|REPEAT_LAST
name|REPEAT_LAST
comment|/*< skip>*/
DECL|typedef|RepeatMode
block|}
name|RepeatMode
typedef|;
end_typedef

begin_function_decl
name|Tool
modifier|*
name|tools_new_blend
parameter_list|(
name|void
parameter_list|)
function_decl|;
end_function_decl

begin_function_decl
name|void
name|tools_free_blend
parameter_list|(
name|Tool
modifier|*
parameter_list|)
function_decl|;
end_function_decl

begin_comment
comment|/*  Procedure definition and marshalling function  */
end_comment

begin_decl_stmt
specifier|extern
name|ProcRecord
name|blend_proc
decl_stmt|;
end_decl_stmt

begin_endif
endif|#
directive|endif
end_endif

begin_comment
comment|/*  __BLEND_H__  */
end_comment

end_unit

