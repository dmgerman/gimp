begin_unit|revision:0.9.5;language:C;cregit-version:0.0.1
begin_comment
comment|/* The GIMP -- an image manipulation program  * Copyright (C) 1995-2001 Spencer Kimball, Peter Mattis, and others  *  * This program is free software; you can redistribute it and/or modify  * it under the terms of the GNU General Public License as published by  * the Free Software Foundation; either version 2 of the License, or  * (at your option) any later version.  *  * This program is distributed in the hope that it will be useful,  * but WITHOUT ANY WARRANTY; without even the implied warranty of  * MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the  * GNU General Public License for more details.  *  * You should have received a copy of the GNU General Public License  * along with this program; if not, write to the Free Software  * Foundation, Inc., 59 Temple Place - Suite 330, Boston, MA 02111-1307, USA.  */
end_comment

begin_ifndef
ifndef|#
directive|ifndef
name|__GIMP_DRAWABLE_TRANSFORM_UTILS_H__
end_ifndef

begin_define
DECL|macro|__GIMP_DRAWABLE_TRANSFORM_UTILS_H__
define|#
directive|define
name|__GIMP_DRAWABLE_TRANSFORM_UTILS_H__
end_define

begin_function_decl
name|void
name|gimp_drawable_transform_matrix_rotate
parameter_list|(
name|gint
name|x1
parameter_list|,
name|gint
name|y1
parameter_list|,
name|gint
name|x2
parameter_list|,
name|gint
name|y2
parameter_list|,
name|gdouble
name|angle
parameter_list|,
name|GimpMatrix3
name|result
parameter_list|)
function_decl|;
end_function_decl

begin_function_decl
name|void
name|gimp_drawable_transform_matrix_rotate_center
parameter_list|(
name|gdouble
name|cx
parameter_list|,
name|gdouble
name|cy
parameter_list|,
name|gdouble
name|angle
parameter_list|,
name|GimpMatrix3
name|result
parameter_list|)
function_decl|;
end_function_decl

begin_function_decl
name|void
name|gimp_drawable_transform_matrix_scale
parameter_list|(
name|gint
name|x1
parameter_list|,
name|gint
name|y1
parameter_list|,
name|gint
name|x2
parameter_list|,
name|gint
name|y2
parameter_list|,
name|gdouble
name|tx1
parameter_list|,
name|gdouble
name|ty1
parameter_list|,
name|gdouble
name|tx2
parameter_list|,
name|gdouble
name|ty2
parameter_list|,
name|GimpMatrix3
name|result
parameter_list|)
function_decl|;
end_function_decl

begin_function_decl
name|void
name|gimp_drawable_transform_matrix_shear
parameter_list|(
name|gint
name|x1
parameter_list|,
name|gint
name|y1
parameter_list|,
name|gint
name|x2
parameter_list|,
name|gint
name|y2
parameter_list|,
name|GimpOrientationType
name|orientation
parameter_list|,
name|gdouble
name|amount
parameter_list|,
name|GimpMatrix3
name|result
parameter_list|)
function_decl|;
end_function_decl

begin_function_decl
name|void
name|gimp_drawable_transform_matrix_perspective
parameter_list|(
name|gint
name|x1
parameter_list|,
name|gint
name|y1
parameter_list|,
name|gint
name|x2
parameter_list|,
name|gint
name|y2
parameter_list|,
name|gdouble
name|tx1
parameter_list|,
name|gdouble
name|ty1
parameter_list|,
name|gdouble
name|tx2
parameter_list|,
name|gdouble
name|ty2
parameter_list|,
name|gdouble
name|tx3
parameter_list|,
name|gdouble
name|ty3
parameter_list|,
name|gdouble
name|tx4
parameter_list|,
name|gdouble
name|ty5
parameter_list|,
name|GimpMatrix3
name|result
parameter_list|)
function_decl|;
end_function_decl

begin_endif
endif|#
directive|endif
end_endif

begin_comment
comment|/*  __GIMP_DRAWABLE_TRANSFORM_SHEAR_H__  */
end_comment

end_unit

