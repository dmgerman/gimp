begin_unit|revision:0.9.5;language:C;cregit-version:0.0.1
begin_comment
comment|/* GIMP - The GNU Image Manipulation Program  * Copyright (C) 1995 Spencer Kimball and Peter Mattis  *  * brush_generated module Copyright 1998 Jay Cox<jaycox@earthlink.net>  *  * This program is free software; you can redistribute it and/or modify  * it under the terms of the GNU General Public License as published by  * the Free Software Foundation; either version 2 of the License, or  * (at your option) any later version.  *  * This program is distributed in the hope that it will be useful,  * but WITHOUT ANY WARRANTY; without even the implied warranty of  * MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the  * GNU General Public License for more details.  *  * You should have received a copy of the GNU General Public License  * along with this program; if not, write to the Free Software  * Foundation, Inc., 59 Temple Place - Suite 330, Boston, MA 02111-1307, USA.  */
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
value|(G_TYPE_CHECK_INSTANCE_CAST ((obj), GIMP_TYPE_BRUSH_GENERATED, GimpBrushGenerated))
end_define

begin_define
DECL|macro|GIMP_BRUSH_GENERATED_CLASS (klass)
define|#
directive|define
name|GIMP_BRUSH_GENERATED_CLASS
parameter_list|(
name|klass
parameter_list|)
value|(G_TYPE_CHECK_CLASS_CAST ((klass), GIMP_TYPE_BRUSH_GENERATED, GimpBrushGeneratedClass))
end_define

begin_define
DECL|macro|GIMP_IS_BRUSH_GENERATED (obj)
define|#
directive|define
name|GIMP_IS_BRUSH_GENERATED
parameter_list|(
name|obj
parameter_list|)
value|(G_TYPE_CHECK_INSTANCE_TYPE ((obj), GIMP_TYPE_BRUSH_GENERATED))
end_define

begin_define
DECL|macro|GIMP_IS_BRUSH_GENERATED_CLASS (klass)
define|#
directive|define
name|GIMP_IS_BRUSH_GENERATED_CLASS
parameter_list|(
name|klass
parameter_list|)
value|(G_TYPE_CHECK_CLASS_TYPE ((klass), GIMP_TYPE_BRUSH_GENERATED))
end_define

begin_define
DECL|macro|GIMP_BRUSH_GENERATED_GET_CLASS (obj)
define|#
directive|define
name|GIMP_BRUSH_GENERATED_GET_CLASS
parameter_list|(
name|obj
parameter_list|)
value|(G_TYPE_INSTANCE_GET_CLASS ((obj), GIMP_TYPE_BRUSH_GENERATED, GimpBrushGeneratedClass))
end_define

begin_typedef
DECL|typedef|GimpBrushGeneratedClass
typedef|typedef
name|struct
name|_GimpBrushGeneratedClass
name|GimpBrushGeneratedClass
typedef|;
end_typedef

begin_struct
DECL|struct|_GimpBrushGenerated
struct|struct
name|_GimpBrushGenerated
block|{
DECL|member|parent_instance
name|GimpBrush
name|parent_instance
decl_stmt|;
DECL|member|shape
name|GimpBrushGeneratedShape
name|shape
decl_stmt|;
DECL|member|radius
name|gfloat
name|radius
decl_stmt|;
DECL|member|spikes
name|gint
name|spikes
decl_stmt|;
comment|/* 2 - 20     */
DECL|member|hardness
name|gfloat
name|hardness
decl_stmt|;
comment|/* 0.0 - 1.0  */
DECL|member|aspect_ratio
name|gfloat
name|aspect_ratio
decl_stmt|;
comment|/* y/x        */
DECL|member|angle
name|gfloat
name|angle
decl_stmt|;
comment|/* in degrees */
block|}
struct|;
end_struct

begin_struct
DECL|struct|_GimpBrushGeneratedClass
struct|struct
name|_GimpBrushGeneratedClass
block|{
DECL|member|parent_class
name|GimpBrushClass
name|parent_class
decl_stmt|;
block|}
struct|;
end_struct

begin_decl_stmt
name|GType
name|gimp_brush_generated_get_type
argument_list|(
name|void
argument_list|)
name|G_GNUC_CONST
decl_stmt|;
end_decl_stmt

begin_function_decl
name|GimpData
modifier|*
name|gimp_brush_generated_new
parameter_list|(
specifier|const
name|gchar
modifier|*
name|name
parameter_list|,
name|GimpBrushGeneratedShape
name|shape
parameter_list|,
name|gfloat
name|radius
parameter_list|,
name|gint
name|spikes
parameter_list|,
name|gfloat
name|hardness
parameter_list|,
name|gfloat
name|aspect_ratio
parameter_list|,
name|gfloat
name|angle
parameter_list|)
function_decl|;
end_function_decl

begin_function_decl
name|GimpBrushGeneratedShape
name|gimp_brush_generated_set_shape
parameter_list|(
name|GimpBrushGenerated
modifier|*
name|brush
parameter_list|,
name|GimpBrushGeneratedShape
name|shape
parameter_list|)
function_decl|;
end_function_decl

begin_function_decl
name|gfloat
name|gimp_brush_generated_set_radius
parameter_list|(
name|GimpBrushGenerated
modifier|*
name|brush
parameter_list|,
name|gfloat
name|radius
parameter_list|)
function_decl|;
end_function_decl

begin_function_decl
name|gint
name|gimp_brush_generated_set_spikes
parameter_list|(
name|GimpBrushGenerated
modifier|*
name|brush
parameter_list|,
name|gint
name|spikes
parameter_list|)
function_decl|;
end_function_decl

begin_function_decl
name|gfloat
name|gimp_brush_generated_set_hardness
parameter_list|(
name|GimpBrushGenerated
modifier|*
name|brush
parameter_list|,
name|gfloat
name|hardness
parameter_list|)
function_decl|;
end_function_decl

begin_function_decl
name|gfloat
name|gimp_brush_generated_set_aspect_ratio
parameter_list|(
name|GimpBrushGenerated
modifier|*
name|brush
parameter_list|,
name|gfloat
name|ratio
parameter_list|)
function_decl|;
end_function_decl

begin_function_decl
name|gfloat
name|gimp_brush_generated_set_angle
parameter_list|(
name|GimpBrushGenerated
modifier|*
name|brush
parameter_list|,
name|gfloat
name|angle
parameter_list|)
function_decl|;
end_function_decl

begin_function_decl
name|GimpBrushGeneratedShape
name|gimp_brush_generated_get_shape
parameter_list|(
specifier|const
name|GimpBrushGenerated
modifier|*
name|brush
parameter_list|)
function_decl|;
end_function_decl

begin_function_decl
name|gfloat
name|gimp_brush_generated_get_radius
parameter_list|(
specifier|const
name|GimpBrushGenerated
modifier|*
name|brush
parameter_list|)
function_decl|;
end_function_decl

begin_function_decl
name|gint
name|gimp_brush_generated_get_spikes
parameter_list|(
specifier|const
name|GimpBrushGenerated
modifier|*
name|brush
parameter_list|)
function_decl|;
end_function_decl

begin_function_decl
name|gfloat
name|gimp_brush_generated_get_hardness
parameter_list|(
specifier|const
name|GimpBrushGenerated
modifier|*
name|brush
parameter_list|)
function_decl|;
end_function_decl

begin_function_decl
name|gfloat
name|gimp_brush_generated_get_aspect_ratio
parameter_list|(
specifier|const
name|GimpBrushGenerated
modifier|*
name|brush
parameter_list|)
function_decl|;
end_function_decl

begin_function_decl
name|gfloat
name|gimp_brush_generated_get_angle
parameter_list|(
specifier|const
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

