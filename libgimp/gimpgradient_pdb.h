begin_unit|revision:0.9.5;language:C;cregit-version:0.0.1
begin_comment
comment|/* LIBGIMP - The GIMP Library  * Copyright (C) 1995-2003 Peter Mattis and Spencer Kimball  *  * gimpgradient_pdb.h  *  * This library is free software; you can redistribute it and/or  * modify it under the terms of the GNU Lesser General Public  * License as published by the Free Software Foundation; either  * version 2 of the License, or (at your option) any later version.  *  * This library is distributed in the hope that it will be useful,  * but WITHOUT ANY WARRANTY; without even the implied warranty of  * MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the GNU  * Lesser General Public License for more details.  *  * You should have received a copy of the GNU Lesser General Public  * License along with this library; if not, write to the  * Free Software Foundation, Inc., 59 Temple Place - Suite 330,  * Boston, MA 02111-1307, USA.  */
end_comment

begin_comment
comment|/* NOTE: This file is auto-generated by pdbgen.pl */
end_comment

begin_ifndef
ifndef|#
directive|ifndef
name|__GIMP_GRADIENT_PDB_H__
end_ifndef

begin_define
DECL|macro|__GIMP_GRADIENT_PDB_H__
define|#
directive|define
name|__GIMP_GRADIENT_PDB_H__
end_define

begin_function_decl
name|G_BEGIN_DECLS
comment|/* For information look into the C source or the html documentation */
name|gchar
modifier|*
name|gimp_gradient_new
parameter_list|(
specifier|const
name|gchar
modifier|*
name|name
parameter_list|)
function_decl|;
end_function_decl

begin_function_decl
name|gchar
modifier|*
name|gimp_gradient_duplicate
parameter_list|(
specifier|const
name|gchar
modifier|*
name|name
parameter_list|)
function_decl|;
end_function_decl

begin_function_decl
name|gboolean
name|gimp_gradient_is_editable
parameter_list|(
specifier|const
name|gchar
modifier|*
name|name
parameter_list|)
function_decl|;
end_function_decl

begin_function_decl
name|gchar
modifier|*
name|gimp_gradient_rename
parameter_list|(
specifier|const
name|gchar
modifier|*
name|name
parameter_list|,
specifier|const
name|gchar
modifier|*
name|new_name
parameter_list|)
function_decl|;
end_function_decl

begin_function_decl
name|gboolean
name|gimp_gradient_delete
parameter_list|(
specifier|const
name|gchar
modifier|*
name|name
parameter_list|)
function_decl|;
end_function_decl

begin_function_decl
name|gint
name|gimp_gradient_get_number_of_segments
parameter_list|(
specifier|const
name|gchar
modifier|*
name|name
parameter_list|)
function_decl|;
end_function_decl

begin_function_decl
name|gboolean
name|gimp_gradient_get_uniform_samples
parameter_list|(
specifier|const
name|gchar
modifier|*
name|name
parameter_list|,
name|gint
name|num_samples
parameter_list|,
name|gboolean
name|reverse
parameter_list|,
name|gint
modifier|*
name|num_color_samples
parameter_list|,
name|gdouble
modifier|*
modifier|*
name|color_samples
parameter_list|)
function_decl|;
end_function_decl

begin_function_decl
name|gboolean
name|gimp_gradient_get_custom_samples
parameter_list|(
specifier|const
name|gchar
modifier|*
name|name
parameter_list|,
name|gint
name|num_samples
parameter_list|,
specifier|const
name|gdouble
modifier|*
name|positions
parameter_list|,
name|gboolean
name|reverse
parameter_list|,
name|gint
modifier|*
name|num_color_samples
parameter_list|,
name|gdouble
modifier|*
modifier|*
name|color_samples
parameter_list|)
function_decl|;
end_function_decl

begin_function_decl
name|gboolean
name|gimp_gradient_segment_get_left_color
parameter_list|(
specifier|const
name|gchar
modifier|*
name|name
parameter_list|,
name|gint
name|segment
parameter_list|,
name|GimpRGB
modifier|*
name|color
parameter_list|,
name|gdouble
modifier|*
name|opacity
parameter_list|)
function_decl|;
end_function_decl

begin_function_decl
name|gboolean
name|gimp_gradient_segment_set_left_color
parameter_list|(
specifier|const
name|gchar
modifier|*
name|name
parameter_list|,
name|gint
name|segment
parameter_list|,
specifier|const
name|GimpRGB
modifier|*
name|color
parameter_list|,
name|gdouble
name|opacity
parameter_list|)
function_decl|;
end_function_decl

begin_function_decl
name|gboolean
name|gimp_gradient_segment_get_right_color
parameter_list|(
specifier|const
name|gchar
modifier|*
name|name
parameter_list|,
name|gint
name|segment
parameter_list|,
name|GimpRGB
modifier|*
name|color
parameter_list|,
name|gdouble
modifier|*
name|opacity
parameter_list|)
function_decl|;
end_function_decl

begin_function_decl
name|gboolean
name|gimp_gradient_segment_set_right_color
parameter_list|(
specifier|const
name|gchar
modifier|*
name|name
parameter_list|,
name|gint
name|segment
parameter_list|,
specifier|const
name|GimpRGB
modifier|*
name|color
parameter_list|,
name|gdouble
name|opacity
parameter_list|)
function_decl|;
end_function_decl

begin_function_decl
name|gboolean
name|gimp_gradient_segment_get_left_pos
parameter_list|(
specifier|const
name|gchar
modifier|*
name|name
parameter_list|,
name|gint
name|segment
parameter_list|,
name|gdouble
modifier|*
name|pos
parameter_list|)
function_decl|;
end_function_decl

begin_function_decl
name|gboolean
name|gimp_gradient_segment_set_left_pos
parameter_list|(
specifier|const
name|gchar
modifier|*
name|name
parameter_list|,
name|gint
name|segment
parameter_list|,
name|gdouble
name|pos
parameter_list|,
name|gdouble
modifier|*
name|final_pos
parameter_list|)
function_decl|;
end_function_decl

begin_function_decl
name|gboolean
name|gimp_gradient_segment_get_middle_pos
parameter_list|(
specifier|const
name|gchar
modifier|*
name|name
parameter_list|,
name|gint
name|segment
parameter_list|,
name|gdouble
modifier|*
name|pos
parameter_list|)
function_decl|;
end_function_decl

begin_function_decl
name|gboolean
name|gimp_gradient_segment_set_middle_pos
parameter_list|(
specifier|const
name|gchar
modifier|*
name|name
parameter_list|,
name|gint
name|segment
parameter_list|,
name|gdouble
name|pos
parameter_list|,
name|gdouble
modifier|*
name|final_pos
parameter_list|)
function_decl|;
end_function_decl

begin_function_decl
name|gboolean
name|gimp_gradient_segment_get_right_pos
parameter_list|(
specifier|const
name|gchar
modifier|*
name|name
parameter_list|,
name|gint
name|segment
parameter_list|,
name|gdouble
modifier|*
name|pos
parameter_list|)
function_decl|;
end_function_decl

begin_function_decl
name|gboolean
name|gimp_gradient_segment_set_right_pos
parameter_list|(
specifier|const
name|gchar
modifier|*
name|name
parameter_list|,
name|gint
name|segment
parameter_list|,
name|gdouble
name|pos
parameter_list|,
name|gdouble
modifier|*
name|final_pos
parameter_list|)
function_decl|;
end_function_decl

begin_function_decl
name|gboolean
name|gimp_gradient_segment_get_blending_function
parameter_list|(
specifier|const
name|gchar
modifier|*
name|name
parameter_list|,
name|gint
name|segment
parameter_list|,
name|GimpGradientSegmentType
modifier|*
name|blend_func
parameter_list|)
function_decl|;
end_function_decl

begin_function_decl
name|gboolean
name|gimp_gradient_segment_get_coloring_type
parameter_list|(
specifier|const
name|gchar
modifier|*
name|name
parameter_list|,
name|gint
name|segment
parameter_list|,
name|GimpGradientSegmentColor
modifier|*
name|coloring_type
parameter_list|)
function_decl|;
end_function_decl

begin_function_decl
name|gboolean
name|gimp_gradient_segment_range_set_blending_function
parameter_list|(
specifier|const
name|gchar
modifier|*
name|name
parameter_list|,
name|gint
name|start_segment
parameter_list|,
name|gint
name|end_segment
parameter_list|,
name|GimpGradientSegmentType
name|blending_function
parameter_list|)
function_decl|;
end_function_decl

begin_function_decl
name|gboolean
name|gimp_gradient_segment_range_set_coloring_type
parameter_list|(
specifier|const
name|gchar
modifier|*
name|name
parameter_list|,
name|gint
name|start_segment
parameter_list|,
name|gint
name|end_segment
parameter_list|,
name|GimpGradientSegmentColor
name|coloring_type
parameter_list|)
function_decl|;
end_function_decl

begin_function_decl
name|gboolean
name|gimp_gradient_segment_range_flip
parameter_list|(
specifier|const
name|gchar
modifier|*
name|name
parameter_list|,
name|gint
name|start_segment
parameter_list|,
name|gint
name|end_segment
parameter_list|)
function_decl|;
end_function_decl

begin_function_decl
name|gboolean
name|gimp_gradient_segment_range_replicate
parameter_list|(
specifier|const
name|gchar
modifier|*
name|name
parameter_list|,
name|gint
name|start_segment
parameter_list|,
name|gint
name|end_segment
parameter_list|,
name|gint
name|replicate_times
parameter_list|)
function_decl|;
end_function_decl

begin_function_decl
name|gboolean
name|gimp_gradient_segment_range_split_midpoint
parameter_list|(
specifier|const
name|gchar
modifier|*
name|name
parameter_list|,
name|gint
name|start_segment
parameter_list|,
name|gint
name|end_segment
parameter_list|)
function_decl|;
end_function_decl

begin_function_decl
name|gboolean
name|gimp_gradient_segment_range_split_uniform
parameter_list|(
specifier|const
name|gchar
modifier|*
name|name
parameter_list|,
name|gint
name|start_segment
parameter_list|,
name|gint
name|end_segment
parameter_list|,
name|gint
name|split_parts
parameter_list|)
function_decl|;
end_function_decl

begin_function_decl
name|gboolean
name|gimp_gradient_segment_range_delete
parameter_list|(
specifier|const
name|gchar
modifier|*
name|name
parameter_list|,
name|gint
name|start_segment
parameter_list|,
name|gint
name|end_segment
parameter_list|)
function_decl|;
end_function_decl

begin_function_decl
name|gboolean
name|gimp_gradient_segment_range_redistribute_handles
parameter_list|(
specifier|const
name|gchar
modifier|*
name|name
parameter_list|,
name|gint
name|start_segment
parameter_list|,
name|gint
name|end_segment
parameter_list|)
function_decl|;
end_function_decl

begin_function_decl
name|gboolean
name|gimp_gradient_segment_range_blend_colors
parameter_list|(
specifier|const
name|gchar
modifier|*
name|name
parameter_list|,
name|gint
name|start_segment
parameter_list|,
name|gint
name|end_segment
parameter_list|)
function_decl|;
end_function_decl

begin_function_decl
name|gboolean
name|gimp_gradient_segment_range_blend_opacity
parameter_list|(
specifier|const
name|gchar
modifier|*
name|name
parameter_list|,
name|gint
name|start_segment
parameter_list|,
name|gint
name|end_segment
parameter_list|)
function_decl|;
end_function_decl

begin_function_decl
name|gdouble
name|gimp_gradient_segment_range_move
parameter_list|(
specifier|const
name|gchar
modifier|*
name|name
parameter_list|,
name|gint
name|start_segment
parameter_list|,
name|gint
name|end_segment
parameter_list|,
name|gdouble
name|delta
parameter_list|,
name|gboolean
name|control_compress
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
comment|/* __GIMP_GRADIENT_PDB_H__ */
end_comment

end_unit

