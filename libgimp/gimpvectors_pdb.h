begin_unit|revision:0.9.5;language:C;cregit-version:0.0.1
begin_comment
comment|/* LIBGIMP - The GIMP Library  * Copyright (C) 1995-2003 Peter Mattis and Spencer Kimball  *  * gimpvectors_pdb.h  *  * This library is free software; you can redistribute it and/or  * modify it under the terms of the GNU Lesser General Public  * License as published by the Free Software Foundation; either  * version 2 of the License, or (at your option) any later version.  *  * This library is distributed in the hope that it will be useful,  * but WITHOUT ANY WARRANTY; without even the implied warranty of  * MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the GNU  * Lesser General Public License for more details.  *  * You should have received a copy of the GNU Lesser General Public  * License along with this library; if not, write to the  * Free Software Foundation, Inc., 59 Temple Place - Suite 330,  * Boston, MA 02111-1307, USA.  */
end_comment

begin_comment
comment|/* NOTE: This file is auto-generated by pdbgen.pl */
end_comment

begin_ifndef
ifndef|#
directive|ifndef
name|__GIMP_VECTORS_PDB_H__
end_ifndef

begin_define
DECL|macro|__GIMP_VECTORS_PDB_H__
define|#
directive|define
name|__GIMP_VECTORS_PDB_H__
end_define

begin_function_decl
name|G_BEGIN_DECLS
comment|/* For information look into the C source or the html documentation */
name|gboolean
name|gimp_vectors_is_valid
parameter_list|(
name|gint32
name|vectors_ID
parameter_list|)
function_decl|;
end_function_decl

begin_function_decl
name|gint32
name|gimp_vectors_new
parameter_list|(
name|gint32
name|image_ID
parameter_list|,
specifier|const
name|gchar
modifier|*
name|name
parameter_list|)
function_decl|;
end_function_decl

begin_function_decl
name|gint32
name|gimp_vectors_new_from_text_layer
parameter_list|(
name|gint32
name|image_ID
parameter_list|,
name|gint32
name|layer_ID
parameter_list|)
function_decl|;
end_function_decl

begin_function_decl
name|gint32
name|gimp_vectors_get_image
parameter_list|(
name|gint32
name|vectors_ID
parameter_list|)
function_decl|;
end_function_decl

begin_function_decl
name|gchar
modifier|*
name|gimp_vectors_get_name
parameter_list|(
name|gint32
name|vectors_ID
parameter_list|)
function_decl|;
end_function_decl

begin_function_decl
name|gboolean
name|gimp_vectors_set_name
parameter_list|(
name|gint32
name|vectors_ID
parameter_list|,
specifier|const
name|gchar
modifier|*
name|name
parameter_list|)
function_decl|;
end_function_decl

begin_function_decl
name|gboolean
name|gimp_vectors_get_visible
parameter_list|(
name|gint32
name|vectors_ID
parameter_list|)
function_decl|;
end_function_decl

begin_function_decl
name|gboolean
name|gimp_vectors_set_visible
parameter_list|(
name|gint32
name|vectors_ID
parameter_list|,
name|gboolean
name|visible
parameter_list|)
function_decl|;
end_function_decl

begin_function_decl
name|gboolean
name|gimp_vectors_get_linked
parameter_list|(
name|gint32
name|vectors_ID
parameter_list|)
function_decl|;
end_function_decl

begin_function_decl
name|gboolean
name|gimp_vectors_set_linked
parameter_list|(
name|gint32
name|vectors_ID
parameter_list|,
name|gboolean
name|linked
parameter_list|)
function_decl|;
end_function_decl

begin_function_decl
name|gint
name|gimp_vectors_get_tattoo
parameter_list|(
name|gint32
name|vectors_ID
parameter_list|)
function_decl|;
end_function_decl

begin_function_decl
name|gboolean
name|gimp_vectors_set_tattoo
parameter_list|(
name|gint32
name|vectors_ID
parameter_list|,
name|gint
name|tattoo
parameter_list|)
function_decl|;
end_function_decl

begin_function_decl
name|gint
modifier|*
name|gimp_vectors_get_strokes
parameter_list|(
name|gint32
name|vectors_ID
parameter_list|,
name|gint
modifier|*
name|num_strokes
parameter_list|)
function_decl|;
end_function_decl

begin_function_decl
name|gdouble
name|gimp_vectors_stroke_get_length
parameter_list|(
name|gint32
name|vectors_ID
parameter_list|,
name|gint
name|stroke_id
parameter_list|,
name|gdouble
name|precision
parameter_list|)
function_decl|;
end_function_decl

begin_function_decl
name|gboolean
name|gimp_vectors_stroke_get_point_at_dist
parameter_list|(
name|gint32
name|vectors_ID
parameter_list|,
name|gint
name|stroke_id
parameter_list|,
name|gdouble
name|dist
parameter_list|,
name|gdouble
name|precision
parameter_list|,
name|gdouble
modifier|*
name|x_point
parameter_list|,
name|gdouble
modifier|*
name|y_point
parameter_list|,
name|gdouble
modifier|*
name|slope
parameter_list|,
name|gboolean
modifier|*
name|valid
parameter_list|)
function_decl|;
end_function_decl

begin_function_decl
name|gboolean
name|gimp_vectors_remove_stroke
parameter_list|(
name|gint32
name|vectors_ID
parameter_list|,
name|gint
name|stroke_id
parameter_list|)
function_decl|;
end_function_decl

begin_function_decl
name|gboolean
name|gimp_vectors_stroke_close
parameter_list|(
name|gint32
name|vectors_ID
parameter_list|,
name|gint
name|stroke_id
parameter_list|)
function_decl|;
end_function_decl

begin_function_decl
name|gboolean
name|gimp_vectors_stroke_translate
parameter_list|(
name|gint32
name|vectors_ID
parameter_list|,
name|gint
name|stroke_id
parameter_list|,
name|gint
name|off_x
parameter_list|,
name|gint
name|off_y
parameter_list|)
function_decl|;
end_function_decl

begin_function_decl
name|gboolean
name|gimp_vectors_stroke_scale
parameter_list|(
name|gint32
name|vectors_ID
parameter_list|,
name|gint
name|stroke_id
parameter_list|,
name|gdouble
name|scale_x
parameter_list|,
name|gdouble
name|scale_y
parameter_list|)
function_decl|;
end_function_decl

begin_function_decl
name|gboolean
name|gimp_vectors_stroke_rotate
parameter_list|(
name|gint32
name|vectors_ID
parameter_list|,
name|gint
name|stroke_id
parameter_list|,
name|gdouble
name|center_x
parameter_list|,
name|gdouble
name|center_y
parameter_list|,
name|gdouble
name|angle
parameter_list|)
function_decl|;
end_function_decl

begin_function_decl
name|gboolean
name|gimp_vectors_stroke_flip
parameter_list|(
name|gint32
name|vectors_ID
parameter_list|,
name|gint
name|stroke_id
parameter_list|,
name|GimpOrientationType
name|flip_type
parameter_list|,
name|gdouble
name|axis
parameter_list|)
function_decl|;
end_function_decl

begin_function_decl
name|gboolean
name|gimp_vectors_stroke_flip_free
parameter_list|(
name|gint32
name|vectors_ID
parameter_list|,
name|gint
name|stroke_id
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
parameter_list|)
function_decl|;
end_function_decl

begin_function_decl
name|GimpVectorsStrokeType
name|gimp_vectors_stroke_get_points
parameter_list|(
name|gint32
name|vectors_ID
parameter_list|,
name|gint
name|stroke_id
parameter_list|,
name|gint
modifier|*
name|num_points
parameter_list|,
name|gdouble
modifier|*
modifier|*
name|controlpoints
parameter_list|,
name|gboolean
modifier|*
name|closed
parameter_list|)
function_decl|;
end_function_decl

begin_function_decl
name|gint
name|gimp_vectors_stroke_new_from_points
parameter_list|(
name|gint32
name|vectors_ID
parameter_list|,
name|GimpVectorsStrokeType
name|type
parameter_list|,
name|gint
name|num_points
parameter_list|,
specifier|const
name|gdouble
modifier|*
name|controlpoints
parameter_list|,
name|gboolean
name|closed
parameter_list|)
function_decl|;
end_function_decl

begin_function_decl
name|gdouble
modifier|*
name|gimp_vectors_stroke_interpolate
parameter_list|(
name|gint32
name|vectors_ID
parameter_list|,
name|gint
name|stroke_id
parameter_list|,
name|gdouble
name|precision
parameter_list|,
name|gint
modifier|*
name|num_coords
parameter_list|,
name|gboolean
modifier|*
name|closed
parameter_list|)
function_decl|;
end_function_decl

begin_function_decl
name|gint
name|gimp_vectors_bezier_stroke_new_moveto
parameter_list|(
name|gint32
name|vectors_ID
parameter_list|,
name|gdouble
name|x0
parameter_list|,
name|gdouble
name|y0
parameter_list|)
function_decl|;
end_function_decl

begin_function_decl
name|gboolean
name|gimp_vectors_bezier_stroke_lineto
parameter_list|(
name|gint32
name|vectors_ID
parameter_list|,
name|gint
name|stroke_id
parameter_list|,
name|gdouble
name|x0
parameter_list|,
name|gdouble
name|y0
parameter_list|)
function_decl|;
end_function_decl

begin_function_decl
name|gboolean
name|gimp_vectors_bezier_stroke_conicto
parameter_list|(
name|gint32
name|vectors_ID
parameter_list|,
name|gint
name|stroke_id
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
parameter_list|)
function_decl|;
end_function_decl

begin_function_decl
name|gboolean
name|gimp_vectors_bezier_stroke_cubicto
parameter_list|(
name|gint32
name|vectors_ID
parameter_list|,
name|gint
name|stroke_id
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
parameter_list|)
function_decl|;
end_function_decl

begin_function_decl
name|gint
name|gimp_vectors_bezier_stroke_new_ellipse
parameter_list|(
name|gint32
name|vectors_ID
parameter_list|,
name|gdouble
name|x0
parameter_list|,
name|gdouble
name|y0
parameter_list|,
name|gdouble
name|radius_x
parameter_list|,
name|gdouble
name|radius_y
parameter_list|,
name|gdouble
name|angle
parameter_list|)
function_decl|;
end_function_decl

begin_function_decl
name|gboolean
name|gimp_vectors_to_selection
parameter_list|(
name|gint32
name|vectors_ID
parameter_list|,
name|GimpChannelOps
name|operation
parameter_list|,
name|gboolean
name|antialias
parameter_list|,
name|gboolean
name|feather
parameter_list|,
name|gdouble
name|feather_radius_x
parameter_list|,
name|gdouble
name|feather_radius_y
parameter_list|)
function_decl|;
end_function_decl

begin_function_decl
name|gboolean
name|gimp_vectors_import_from_file
parameter_list|(
name|gint32
name|image_ID
parameter_list|,
specifier|const
name|gchar
modifier|*
name|filename
parameter_list|,
name|gboolean
name|merge
parameter_list|,
name|gboolean
name|scale
parameter_list|,
name|gint
modifier|*
name|num_vectors
parameter_list|,
name|gint32
modifier|*
modifier|*
name|vectors_ids
parameter_list|)
function_decl|;
end_function_decl

begin_function_decl
name|gboolean
name|gimp_vectors_import_from_string
parameter_list|(
name|gint32
name|image_ID
parameter_list|,
specifier|const
name|gchar
modifier|*
name|string
parameter_list|,
name|gint
name|length
parameter_list|,
name|gboolean
name|merge
parameter_list|,
name|gboolean
name|scale
parameter_list|,
name|gint
modifier|*
name|num_vectors
parameter_list|,
name|gint32
modifier|*
modifier|*
name|vectors_ids
parameter_list|)
function_decl|;
end_function_decl

begin_function_decl
name|gboolean
name|gimp_vectors_export_to_file
parameter_list|(
name|gint32
name|image_ID
parameter_list|,
specifier|const
name|gchar
modifier|*
name|filename
parameter_list|,
name|gint32
name|vectors_ID
parameter_list|)
function_decl|;
end_function_decl

begin_function_decl
name|gchar
modifier|*
name|gimp_vectors_export_to_string
parameter_list|(
name|gint32
name|image_ID
parameter_list|,
name|gint32
name|vectors_ID
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
comment|/* __GIMP_VECTORS_PDB_H__ */
end_comment

end_unit

