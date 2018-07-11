begin_unit|revision:0.9.5;language:C;cregit-version:0.0.1
begin_comment
comment|/* GIMP - The GNU Image Manipulation Program  * Copyright (C) 1995 Spencer Kimball and Peter Mattis  *  * gimpbezierdesc.c  * Copyright (C) 2010 Michael Natterer<mitch@gimp.org>  *  * This program is free software: you can redistribute it and/or modify  * it under the terms of the GNU General Public License as published by  * the Free Software Foundation; either version 3 of the License, or  * (at your option) any later version.  *  * This program is distributed in the hope that it will be useful,  * but WITHOUT ANY WARRANTY; without even the implied warranty of  * MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the  * GNU General Public License for more details.  *  * You should have received a copy of the GNU General Public License  * along with this program.  If not, see<https://www.gnu.org/licenses/>.  */
end_comment

begin_include
include|#
directive|include
file|"config.h"
end_include

begin_include
include|#
directive|include
file|<gegl.h>
end_include

begin_include
include|#
directive|include
file|<cairo.h>
end_include

begin_include
include|#
directive|include
file|"core-types.h"
end_include

begin_include
include|#
directive|include
file|"gimpbezierdesc.h"
end_include

begin_include
include|#
directive|include
file|"gimpboundary.h"
end_include

begin_function
name|GType
DECL|function|gimp_bezier_desc_get_type (void)
name|gimp_bezier_desc_get_type
parameter_list|(
name|void
parameter_list|)
block|{
specifier|static
name|GType
name|type
init|=
literal|0
decl_stmt|;
if|if
condition|(
operator|!
name|type
condition|)
name|type
operator|=
name|g_boxed_type_register_static
argument_list|(
literal|"GimpBezierDesc"
argument_list|,
operator|(
name|GBoxedCopyFunc
operator|)
name|gimp_bezier_desc_copy
argument_list|,
operator|(
name|GBoxedFreeFunc
operator|)
name|gimp_bezier_desc_free
argument_list|)
expr_stmt|;
return|return
name|type
return|;
block|}
end_function

begin_function
name|GimpBezierDesc
modifier|*
DECL|function|gimp_bezier_desc_new (cairo_path_data_t * data,gint n_data)
name|gimp_bezier_desc_new
parameter_list|(
name|cairo_path_data_t
modifier|*
name|data
parameter_list|,
name|gint
name|n_data
parameter_list|)
block|{
name|GimpBezierDesc
modifier|*
name|desc
decl_stmt|;
name|g_return_val_if_fail
argument_list|(
name|n_data
operator|==
literal|0
operator|||
name|data
operator|!=
name|NULL
argument_list|,
name|NULL
argument_list|)
expr_stmt|;
name|desc
operator|=
name|g_slice_new
argument_list|(
name|GimpBezierDesc
argument_list|)
expr_stmt|;
name|desc
operator|->
name|status
operator|=
name|CAIRO_STATUS_SUCCESS
expr_stmt|;
name|desc
operator|->
name|num_data
operator|=
name|n_data
expr_stmt|;
name|desc
operator|->
name|data
operator|=
name|data
expr_stmt|;
return|return
name|desc
return|;
block|}
end_function

begin_function
specifier|static
name|void
DECL|function|add_polyline (GArray * path_data,const GimpVector2 * points,gint n_points,gboolean closed)
name|add_polyline
parameter_list|(
name|GArray
modifier|*
name|path_data
parameter_list|,
specifier|const
name|GimpVector2
modifier|*
name|points
parameter_list|,
name|gint
name|n_points
parameter_list|,
name|gboolean
name|closed
parameter_list|)
block|{
name|GimpVector2
name|prev
init|=
block|{
literal|0.0
block|,
literal|0.0
block|, }
decl_stmt|;
name|cairo_path_data_t
name|pd
decl_stmt|;
name|gint
name|i
decl_stmt|;
for|for
control|(
name|i
operator|=
literal|0
init|;
name|i
operator|<
name|n_points
condition|;
name|i
operator|++
control|)
block|{
comment|/* compress multiple identical coordinates */
if|if
condition|(
name|i
operator|==
literal|0
operator|||
name|prev
operator|.
name|x
operator|!=
name|points
index|[
name|i
index|]
operator|.
name|x
operator|||
name|prev
operator|.
name|y
operator|!=
name|points
index|[
name|i
index|]
operator|.
name|y
condition|)
block|{
name|pd
operator|.
name|header
operator|.
name|type
operator|=
operator|(
name|i
operator|==
literal|0
operator|)
condition|?
name|CAIRO_PATH_MOVE_TO
else|:
name|CAIRO_PATH_LINE_TO
expr_stmt|;
name|pd
operator|.
name|header
operator|.
name|length
operator|=
literal|2
expr_stmt|;
name|g_array_append_val
argument_list|(
name|path_data
argument_list|,
name|pd
argument_list|)
expr_stmt|;
name|pd
operator|.
name|point
operator|.
name|x
operator|=
name|points
index|[
name|i
index|]
operator|.
name|x
expr_stmt|;
name|pd
operator|.
name|point
operator|.
name|y
operator|=
name|points
index|[
name|i
index|]
operator|.
name|y
expr_stmt|;
name|g_array_append_val
argument_list|(
name|path_data
argument_list|,
name|pd
argument_list|)
expr_stmt|;
name|prev
operator|=
name|points
index|[
name|i
index|]
expr_stmt|;
block|}
block|}
comment|/* close the polyline when needed */
if|if
condition|(
name|closed
condition|)
block|{
name|pd
operator|.
name|header
operator|.
name|type
operator|=
name|CAIRO_PATH_CLOSE_PATH
expr_stmt|;
name|pd
operator|.
name|header
operator|.
name|length
operator|=
literal|1
expr_stmt|;
name|g_array_append_val
argument_list|(
name|path_data
argument_list|,
name|pd
argument_list|)
expr_stmt|;
block|}
block|}
end_function

begin_function
name|GimpBezierDesc
modifier|*
DECL|function|gimp_bezier_desc_new_from_bound_segs (GimpBoundSeg * bound_segs,gint n_bound_segs,gint n_bound_groups)
name|gimp_bezier_desc_new_from_bound_segs
parameter_list|(
name|GimpBoundSeg
modifier|*
name|bound_segs
parameter_list|,
name|gint
name|n_bound_segs
parameter_list|,
name|gint
name|n_bound_groups
parameter_list|)
block|{
name|GArray
modifier|*
name|path_data
decl_stmt|;
name|GimpVector2
modifier|*
name|points
decl_stmt|;
name|gint
name|n_points
decl_stmt|;
name|gint
name|seg
decl_stmt|;
name|gint
name|i
decl_stmt|;
name|guint
name|path_data_len
decl_stmt|;
name|g_return_val_if_fail
argument_list|(
name|bound_segs
operator|!=
name|NULL
argument_list|,
name|NULL
argument_list|)
expr_stmt|;
name|g_return_val_if_fail
argument_list|(
name|n_bound_segs
operator|>
literal|0
argument_list|,
name|NULL
argument_list|)
expr_stmt|;
name|path_data
operator|=
name|g_array_new
argument_list|(
name|FALSE
argument_list|,
name|FALSE
argument_list|,
sizeof|sizeof
argument_list|(
name|cairo_path_data_t
argument_list|)
argument_list|)
expr_stmt|;
name|points
operator|=
name|g_new0
argument_list|(
name|GimpVector2
argument_list|,
name|n_bound_segs
operator|+
literal|4
argument_list|)
expr_stmt|;
name|seg
operator|=
literal|0
expr_stmt|;
name|n_points
operator|=
literal|0
expr_stmt|;
name|points
index|[
name|n_points
index|]
operator|.
name|x
operator|=
call|(
name|gdouble
call|)
argument_list|(
name|bound_segs
index|[
literal|0
index|]
operator|.
name|x1
argument_list|)
expr_stmt|;
name|points
index|[
name|n_points
index|]
operator|.
name|y
operator|=
call|(
name|gdouble
call|)
argument_list|(
name|bound_segs
index|[
literal|0
index|]
operator|.
name|y1
argument_list|)
expr_stmt|;
name|n_points
operator|++
expr_stmt|;
for|for
control|(
name|i
operator|=
literal|0
init|;
name|i
operator|<
name|n_bound_groups
condition|;
name|i
operator|++
control|)
block|{
while|while
condition|(
name|bound_segs
index|[
name|seg
index|]
operator|.
name|x1
operator|!=
operator|-
literal|1
operator|||
name|bound_segs
index|[
name|seg
index|]
operator|.
name|x2
operator|!=
operator|-
literal|1
operator|||
name|bound_segs
index|[
name|seg
index|]
operator|.
name|y1
operator|!=
operator|-
literal|1
operator|||
name|bound_segs
index|[
name|seg
index|]
operator|.
name|y2
operator|!=
operator|-
literal|1
condition|)
block|{
name|points
index|[
name|n_points
index|]
operator|.
name|x
operator|=
call|(
name|gdouble
call|)
argument_list|(
name|bound_segs
index|[
name|seg
index|]
operator|.
name|x1
argument_list|)
expr_stmt|;
name|points
index|[
name|n_points
index|]
operator|.
name|y
operator|=
call|(
name|gdouble
call|)
argument_list|(
name|bound_segs
index|[
name|seg
index|]
operator|.
name|y1
argument_list|)
expr_stmt|;
name|n_points
operator|++
expr_stmt|;
name|seg
operator|++
expr_stmt|;
block|}
comment|/* Close the stroke points up */
name|points
index|[
name|n_points
index|]
operator|=
name|points
index|[
literal|0
index|]
expr_stmt|;
name|n_points
operator|++
expr_stmt|;
name|add_polyline
argument_list|(
name|path_data
argument_list|,
name|points
argument_list|,
name|n_points
argument_list|,
name|TRUE
argument_list|)
expr_stmt|;
name|n_points
operator|=
literal|0
expr_stmt|;
name|seg
operator|++
expr_stmt|;
name|points
index|[
name|n_points
index|]
operator|.
name|x
operator|=
call|(
name|gdouble
call|)
argument_list|(
name|bound_segs
index|[
name|seg
index|]
operator|.
name|x1
argument_list|)
expr_stmt|;
name|points
index|[
name|n_points
index|]
operator|.
name|y
operator|=
call|(
name|gdouble
call|)
argument_list|(
name|bound_segs
index|[
name|seg
index|]
operator|.
name|y1
argument_list|)
expr_stmt|;
name|n_points
operator|++
expr_stmt|;
block|}
name|g_free
argument_list|(
name|points
argument_list|)
expr_stmt|;
name|path_data_len
operator|=
name|path_data
operator|->
name|len
expr_stmt|;
return|return
name|gimp_bezier_desc_new
argument_list|(
operator|(
name|cairo_path_data_t
operator|*
operator|)
name|g_array_free
argument_list|(
name|path_data
argument_list|,
name|FALSE
argument_list|)
argument_list|,
name|path_data_len
argument_list|)
return|;
block|}
end_function

begin_function
name|void
DECL|function|gimp_bezier_desc_translate (GimpBezierDesc * desc,gdouble offset_x,gdouble offset_y)
name|gimp_bezier_desc_translate
parameter_list|(
name|GimpBezierDesc
modifier|*
name|desc
parameter_list|,
name|gdouble
name|offset_x
parameter_list|,
name|gdouble
name|offset_y
parameter_list|)
block|{
name|gint
name|i
decl_stmt|,
name|j
decl_stmt|;
name|g_return_if_fail
argument_list|(
name|desc
operator|!=
name|NULL
argument_list|)
expr_stmt|;
for|for
control|(
name|i
operator|=
literal|0
init|;
name|i
operator|<
name|desc
operator|->
name|num_data
condition|;
name|i
operator|+=
name|desc
operator|->
name|data
index|[
name|i
index|]
operator|.
name|header
operator|.
name|length
control|)
for|for
control|(
name|j
operator|=
literal|1
init|;
name|j
operator|<
name|desc
operator|->
name|data
index|[
name|i
index|]
operator|.
name|header
operator|.
name|length
condition|;
operator|++
name|j
control|)
block|{
name|desc
operator|->
name|data
index|[
name|i
operator|+
name|j
index|]
operator|.
name|point
operator|.
name|x
operator|+=
name|offset_x
expr_stmt|;
name|desc
operator|->
name|data
index|[
name|i
operator|+
name|j
index|]
operator|.
name|point
operator|.
name|y
operator|+=
name|offset_y
expr_stmt|;
block|}
block|}
end_function

begin_function
name|GimpBezierDesc
modifier|*
DECL|function|gimp_bezier_desc_copy (const GimpBezierDesc * desc)
name|gimp_bezier_desc_copy
parameter_list|(
specifier|const
name|GimpBezierDesc
modifier|*
name|desc
parameter_list|)
block|{
name|g_return_val_if_fail
argument_list|(
name|desc
operator|!=
name|NULL
argument_list|,
name|NULL
argument_list|)
expr_stmt|;
return|return
name|gimp_bezier_desc_new
argument_list|(
name|g_memdup
argument_list|(
name|desc
operator|->
name|data
argument_list|,
name|desc
operator|->
name|num_data
operator|*
sizeof|sizeof
argument_list|(
name|cairo_path_data_t
argument_list|)
argument_list|)
argument_list|,
name|desc
operator|->
name|num_data
argument_list|)
return|;
block|}
end_function

begin_function
name|void
DECL|function|gimp_bezier_desc_free (GimpBezierDesc * desc)
name|gimp_bezier_desc_free
parameter_list|(
name|GimpBezierDesc
modifier|*
name|desc
parameter_list|)
block|{
name|g_return_if_fail
argument_list|(
name|desc
operator|!=
name|NULL
argument_list|)
expr_stmt|;
name|g_free
argument_list|(
name|desc
operator|->
name|data
argument_list|)
expr_stmt|;
name|g_slice_free
argument_list|(
name|GimpBezierDesc
argument_list|,
name|desc
argument_list|)
expr_stmt|;
block|}
end_function

end_unit

