begin_unit|revision:0.9.5;language:C;cregit-version:0.0.1
begin_comment
comment|/* The GIMP -- an image manipulation program  * Copyright (C) 1995 Spencer Kimball and Peter Mattis  *  * brush_generated module Copyright 1998 Jay Cox<jaycox@earthlink.net>  *  * This program is free software; you can redistribute it and/or modify  * it under the terms of the GNU General Public License as published by  * the Free Software Foundation; either version 2 of the License, or  * (at your option) any later version.  *  * This program is distributed in the hope that it will be useful,  * but WITHOUT ANY WARRANTY; without even the implied warranty of  * MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the  * GNU General Public License for more details.  *  * You should have received a copy of the GNU General Public License  * along with this program; if not, write to the Free Software  * Foundation, Inc., 59 Temple Place - Suite 330, Boston, MA 02111-1307, USA.  */
end_comment

begin_ifndef
ifndef|#
directive|ifndef
name|__GIMP_BRUSH_GENERATED_H__
end_ifndef

begin_define
DECL|macro|__GIMP_BRUSH_GENERATED_H__
define|#
directive|define
name|__GIMP_BRUSH_GENERATED_H__
end_define

begin_include
include|#
directive|include
file|"gimpbrush.h"
end_include

begin_typedef
DECL|struct|_GimpBrushGenerated
typedef|typedef
struct|struct
name|_GimpBrushGenerated
block|{
DECL|member|gbrush
name|GimpBrush
name|gbrush
decl_stmt|;
DECL|member|radius
name|float
name|radius
decl_stmt|;
DECL|member|hardness
name|float
name|hardness
decl_stmt|;
comment|/* 0.0 - 1.0  */
DECL|member|angle
name|float
name|angle
decl_stmt|;
comment|/* in degrees */
DECL|member|aspect_ratio
name|float
name|aspect_ratio
decl_stmt|;
comment|/* y/x        */
DECL|member|freeze
name|int
name|freeze
decl_stmt|;
comment|/*GSpline *profile_curve */
comment|/* Some lazy day...  */
DECL|typedef|GimpBrushGenerated
block|}
name|GimpBrushGenerated
typedef|;
end_typedef

begin_typedef
DECL|struct|_GimpBrushGeneratedClass
typedef|typedef
struct|struct
name|_GimpBrushGeneratedClass
block|{
DECL|member|parent_class
name|GimpBrushClass
name|parent_class
decl_stmt|;
DECL|member|generate
name|void
function_decl|(
modifier|*
name|generate
function_decl|)
parameter_list|(
name|GimpBrushGenerated
modifier|*
name|brush
parameter_list|)
function_decl|;
DECL|typedef|GimpBrushGeneratedClass
block|}
name|GimpBrushGeneratedClass
typedef|;
end_typedef

begin_comment
comment|/* object stuff */
end_comment

begin_define
DECL|macro|GIMP_TYPE_BRUSH_GENERATED
define|#
directive|define
name|GIMP_TYPE_BRUSH_GENERATED
value|(gimp_brush_generated_get_type ())
end_define

begin_define
DECL|macro|GIMP_BRUSH_GENERATED (obj)
define|#
directive|define
name|GIMP_BRUSH_GENERATED
parameter_list|(
name|obj
parameter_list|)
value|(GIMP_CHECK_CAST ((obj), GIMP_TYPE_BRUSH_GENERATED, GimpBrushGenerated))
end_define

begin_define
DECL|macro|GIMP_IS_BRUSH_GENERATED (obj)
define|#
directive|define
name|GIMP_IS_BRUSH_GENERATED
parameter_list|(
name|obj
parameter_list|)
value|(GIMP_CHECK_TYPE ((obj), GIMP_TYPE_BRUSH_GENERATED))
end_define

begin_function_decl
name|guint
name|gimp_brush_generated_get_type
parameter_list|(
name|void
parameter_list|)
function_decl|;
end_function_decl

begin_comment
comment|/* normal stuff */
end_comment

begin_function_decl
name|GimpBrushGenerated
modifier|*
name|gimp_brush_generated_new
parameter_list|(
name|float
name|radius
parameter_list|,
name|float
name|hardness
parameter_list|,
name|float
name|angle
parameter_list|,
name|float
name|aspect_ratio
parameter_list|)
function_decl|;
end_function_decl

begin_function_decl
name|GimpBrushGenerated
modifier|*
name|gimp_brush_generated_load
parameter_list|(
name|char
modifier|*
name|file_name
parameter_list|)
function_decl|;
end_function_decl

begin_function_decl
name|void
name|gimp_brush_generated_save
parameter_list|(
name|GimpBrushGenerated
modifier|*
name|brush
parameter_list|,
name|char
modifier|*
name|file_name
parameter_list|)
function_decl|;
end_function_decl

begin_function_decl
name|void
name|gimp_brush_generated_freeze
parameter_list|(
name|GimpBrushGenerated
modifier|*
name|brush
parameter_list|)
function_decl|;
end_function_decl

begin_function_decl
name|void
name|gimp_brush_generated_thaw
parameter_list|(
name|GimpBrushGenerated
modifier|*
name|brush
parameter_list|)
function_decl|;
end_function_decl

begin_function_decl
name|float
name|gimp_brush_generated_set_radius
parameter_list|(
name|GimpBrushGenerated
modifier|*
name|brush
parameter_list|,
name|float
name|radius
parameter_list|)
function_decl|;
end_function_decl

begin_function_decl
name|float
name|gimp_brush_generated_set_hardness
parameter_list|(
name|GimpBrushGenerated
modifier|*
name|brush
parameter_list|,
name|float
name|hardness
parameter_list|)
function_decl|;
end_function_decl

begin_function_decl
name|float
name|gimp_brush_generated_set_angle
parameter_list|(
name|GimpBrushGenerated
modifier|*
name|brush
parameter_list|,
name|float
name|angle
parameter_list|)
function_decl|;
end_function_decl

begin_function_decl
name|float
name|gimp_brush_generated_set_aspect_ratio
parameter_list|(
name|GimpBrushGenerated
modifier|*
name|brush
parameter_list|,
name|float
name|ratio
parameter_list|)
function_decl|;
end_function_decl

begin_function_decl
name|float
name|gimp_brush_generated_get_radius
parameter_list|(
name|GimpBrushGenerated
modifier|*
name|brush
parameter_list|)
function_decl|;
end_function_decl

begin_function_decl
name|float
name|gimp_brush_generated_get_hardness
parameter_list|(
name|GimpBrushGenerated
modifier|*
name|brush
parameter_list|)
function_decl|;
end_function_decl

begin_function_decl
name|float
name|gimp_brush_generated_get_angle
parameter_list|(
name|GimpBrushGenerated
modifier|*
name|brush
parameter_list|)
function_decl|;
end_function_decl

begin_function_decl
name|float
name|gimp_brush_generated_get_aspect_ratio
parameter_list|(
name|GimpBrushGenerated
modifier|*
name|brush
parameter_list|)
function_decl|;
end_function_decl

begin_endif
endif|#
directive|endif
end_endif

begin_comment
comment|/*  __GIMP_BRUSH_GENERATED_H__  */
end_comment

end_unit

