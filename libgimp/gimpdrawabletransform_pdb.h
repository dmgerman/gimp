begin_unit|revision:0.9.5;language:C;cregit-version:0.0.1
begin_comment
comment|/* LIBGIMP - The GIMP Library  * Copyright (C) 1995-2003 Peter Mattis and Spencer Kimball  *  * gimpdrawabletransform_pdb.h  *  * This library is free software; you can redistribute it and/or  * modify it under the terms of the GNU Lesser General Public  * License as published by the Free Software Foundation; either  * version 2 of the License, or (at your option) any later version.  *  * This library is distributed in the hope that it will be useful,  * but WITHOUT ANY WARRANTY; without even the implied warranty of  * MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the GNU  * Lesser General Public License for more details.  *  * You should have received a copy of the GNU Lesser General Public  * License along with this library; if not, write to the  * Free Software Foundation, Inc., 59 Temple Place - Suite 330,  * Boston, MA 02111-1307, USA.  */
end_comment

begin_comment
comment|/* NOTE: This file is autogenerated by pdbgen.pl */
end_comment

begin_ifndef
ifndef|#
directive|ifndef
name|__GIMP_DRAWABLE_TRANSFORM_PDB_H__
end_ifndef

begin_define
DECL|macro|__GIMP_DRAWABLE_TRANSFORM_PDB_H__
define|#
directive|define
name|__GIMP_DRAWABLE_TRANSFORM_PDB_H__
end_define

begin_function_decl
name|G_BEGIN_DECLS
comment|/* For information look into the C source or the html documentation */
name|gint32
name|gimp_drawable_transform_flip
parameter_list|(
name|gint32
name|drawable_ID
parameter_list|,
name|GimpOrientationType
name|flip_type
parameter_list|,
name|gboolean
name|center
parameter_list|,
name|gdouble
name|axis
parameter_list|,
name|GimpTransformDirection
name|transform_direction
parameter_list|,
name|GimpInterpolationType
name|interpolation
parameter_list|,
name|gboolean
name|supersample
parameter_list|,
name|gint
name|recursion_level
parameter_list|,
name|gboolean
name|clip_result
parameter_list|)
function_decl|;
end_function_decl

begin_function_decl
name|gint32
name|gimp_drawable_transform_flip_free
parameter_list|(
name|gint32
name|drawable_ID
parameter_list|,
name|gdouble
name|x1
parameter_list|,
name|gdouble
name|y1
parameter_list|,
name|gdouble
name|x2
parameter_list|,
name|gdouble
name|y2
parameter_list|,
name|GimpTransformDirection
name|transform_direction
parameter_list|,
name|GimpInterpolationType
name|interpolation
parameter_list|,
name|gboolean
name|supersample
parameter_list|,
name|gint
name|recursion_level
parameter_list|,
name|gboolean
name|clip_result
parameter_list|)
function_decl|;
end_function_decl

begin_function_decl
name|gint32
name|gimp_drawable_transform_perspective
parameter_list|(
name|gint32
name|drawable_ID
parameter_list|,
name|gdouble
name|x0
parameter_list|,
name|gdouble
name|y0
parameter_list|,
name|gdouble
name|x1
parameter_list|,
name|gdouble
name|y1
parameter_list|,
name|gdouble
name|x2
parameter_list|,
name|gdouble
name|y2
parameter_list|,
name|gdouble
name|x3
parameter_list|,
name|gdouble
name|y3
parameter_list|,
name|GimpTransformDirection
name|transform_direction
parameter_list|,
name|GimpInterpolationType
name|interpolation
parameter_list|,
name|gboolean
name|supersample
parameter_list|,
name|gint
name|recursion_level
parameter_list|,
name|gboolean
name|clip_result
parameter_list|)
function_decl|;
end_function_decl

begin_function_decl
name|gint32
name|gimp_drawable_transform_rotate
parameter_list|(
name|gint32
name|drawable_ID
parameter_list|,
name|gdouble
name|angle
parameter_list|,
name|gint
name|cx
parameter_list|,
name|gint
name|cy
parameter_list|,
name|GimpTransformDirection
name|transform_direction
parameter_list|,
name|GimpInterpolationType
name|interpolation
parameter_list|,
name|gboolean
name|supersample
parameter_list|,
name|gint
name|recursion_level
parameter_list|,
name|gboolean
name|clip_result
parameter_list|)
function_decl|;
end_function_decl

begin_function_decl
name|gint32
name|gimp_drawable_transform_scale
parameter_list|(
name|gint32
name|drawable_ID
parameter_list|,
name|gdouble
name|x0
parameter_list|,
name|gdouble
name|y0
parameter_list|,
name|gdouble
name|x1
parameter_list|,
name|gdouble
name|y1
parameter_list|,
name|GimpTransformDirection
name|transform_direction
parameter_list|,
name|GimpInterpolationType
name|interpolation
parameter_list|,
name|gboolean
name|supersample
parameter_list|,
name|gint
name|recursion_level
parameter_list|,
name|gboolean
name|clip_result
parameter_list|)
function_decl|;
end_function_decl

begin_function_decl
name|gint32
name|gimp_drawable_transform_shear
parameter_list|(
name|gint32
name|drawable_ID
parameter_list|,
name|GimpOrientationType
name|shear_type
parameter_list|,
name|gdouble
name|magnitude
parameter_list|,
name|GimpTransformDirection
name|transform_direction
parameter_list|,
name|GimpInterpolationType
name|interpolation
parameter_list|,
name|gboolean
name|supersample
parameter_list|,
name|gint
name|recursion_level
parameter_list|,
name|gboolean
name|clip_result
parameter_list|)
function_decl|;
end_function_decl

begin_function_decl
name|gint32
name|gimp_drawable_transform_2d
parameter_list|(
name|gint32
name|drawable_ID
parameter_list|,
name|gdouble
name|source_x
parameter_list|,
name|gdouble
name|source_y
parameter_list|,
name|gdouble
name|scale_x
parameter_list|,
name|gdouble
name|scale_y
parameter_list|,
name|gdouble
name|angle
parameter_list|,
name|gdouble
name|dest_x
parameter_list|,
name|gdouble
name|dest_y
parameter_list|,
name|GimpTransformDirection
name|transform_direction
parameter_list|,
name|GimpInterpolationType
name|interpolation
parameter_list|,
name|gboolean
name|supersample
parameter_list|,
name|gint
name|recursion_level
parameter_list|,
name|gboolean
name|clip_result
parameter_list|)
function_decl|;
end_function_decl

begin_macro
name|G_END_DECLS
end_macro

begin_endif
endif|#
directive|endif
end_endif

begin_comment
comment|/* __GIMP_DRAWABLE_TRANSFORM_PDB_H__ */
end_comment

end_unit

