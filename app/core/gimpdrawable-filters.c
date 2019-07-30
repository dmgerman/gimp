begin_unit|revision:0.9.5;language:C;cregit-version:0.0.1
begin_comment
comment|/* GIMP - The GNU Image Manipulation Program  * Copyright (C) 1995 Spencer Kimball and Peter Mattis  *  * gimpdrawable-filters.c  *  * This program is free software: you can redistribute it and/or modify  * it under the terms of the GNU General Public License as published by  * the Free Software Foundation; either version 3 of the License, or  * (at your option) any later version.  *  * This program is distributed in the hope that it will be useful,  * but WITHOUT ANY WARRANTY; without even the implied warranty of  * MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the  * GNU General Public License for more details.  *  * You should have received a copy of the GNU General Public License  * along with this program.  If not, see<https://www.gnu.org/licenses/>.  */
end_comment

begin_include
include|#
directive|include
file|"config.h"
end_include

begin_include
include|#
directive|include
file|<gdk-pixbuf/gdk-pixbuf.h>
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
file|"gegl/gimpapplicator.h"
end_include

begin_include
include|#
directive|include
file|"gegl/gimp-gegl-apply-operation.h"
end_include

begin_include
include|#
directive|include
file|"gegl/gimp-gegl-loops.h"
end_include

begin_include
include|#
directive|include
file|"gimp-utils.h"
end_include

begin_include
include|#
directive|include
file|"gimpdrawable.h"
end_include

begin_include
include|#
directive|include
file|"gimpdrawable-filters.h"
end_include

begin_include
include|#
directive|include
file|"gimpdrawable-private.h"
end_include

begin_include
include|#
directive|include
file|"gimpfilter.h"
end_include

begin_include
include|#
directive|include
file|"gimpfilterstack.h"
end_include

begin_include
include|#
directive|include
file|"gimpimage.h"
end_include

begin_include
include|#
directive|include
file|"gimpprogress.h"
end_include

begin_include
include|#
directive|include
file|"gimpprojection.h"
end_include

begin_function
name|GimpContainer
modifier|*
DECL|function|gimp_drawable_get_filters (GimpDrawable * drawable)
name|gimp_drawable_get_filters
parameter_list|(
name|GimpDrawable
modifier|*
name|drawable
parameter_list|)
block|{
name|g_return_val_if_fail
argument_list|(
name|GIMP_IS_DRAWABLE
argument_list|(
name|drawable
argument_list|)
argument_list|,
name|NULL
argument_list|)
expr_stmt|;
return|return
name|drawable
operator|->
name|private
operator|->
name|filter_stack
return|;
block|}
end_function

begin_function
name|gboolean
DECL|function|gimp_drawable_has_filters (GimpDrawable * drawable)
name|gimp_drawable_has_filters
parameter_list|(
name|GimpDrawable
modifier|*
name|drawable
parameter_list|)
block|{
name|GList
modifier|*
name|list
decl_stmt|;
name|g_return_val_if_fail
argument_list|(
name|GIMP_IS_DRAWABLE
argument_list|(
name|drawable
argument_list|)
argument_list|,
name|FALSE
argument_list|)
expr_stmt|;
for|for
control|(
name|list
operator|=
name|GIMP_LIST
argument_list|(
name|drawable
operator|->
name|private
operator|->
name|filter_stack
argument_list|)
operator|->
name|queue
operator|->
name|head
init|;
name|list
condition|;
name|list
operator|=
name|g_list_next
argument_list|(
name|list
argument_list|)
control|)
block|{
name|GimpFilter
modifier|*
name|filter
init|=
name|list
operator|->
name|data
decl_stmt|;
if|if
condition|(
name|gimp_filter_get_active
argument_list|(
name|filter
argument_list|)
condition|)
return|return
name|TRUE
return|;
block|}
return|return
name|FALSE
return|;
block|}
end_function

begin_function
name|void
DECL|function|gimp_drawable_add_filter (GimpDrawable * drawable,GimpFilter * filter)
name|gimp_drawable_add_filter
parameter_list|(
name|GimpDrawable
modifier|*
name|drawable
parameter_list|,
name|GimpFilter
modifier|*
name|filter
parameter_list|)
block|{
name|g_return_if_fail
argument_list|(
name|GIMP_IS_DRAWABLE
argument_list|(
name|drawable
argument_list|)
argument_list|)
expr_stmt|;
name|g_return_if_fail
argument_list|(
name|GIMP_IS_FILTER
argument_list|(
name|filter
argument_list|)
argument_list|)
expr_stmt|;
name|g_return_if_fail
argument_list|(
name|gimp_drawable_has_filter
argument_list|(
name|drawable
argument_list|,
name|filter
argument_list|)
operator|==
name|FALSE
argument_list|)
expr_stmt|;
name|gimp_container_add
argument_list|(
name|drawable
operator|->
name|private
operator|->
name|filter_stack
argument_list|,
name|GIMP_OBJECT
argument_list|(
name|filter
argument_list|)
argument_list|)
expr_stmt|;
block|}
end_function

begin_function
name|void
DECL|function|gimp_drawable_remove_filter (GimpDrawable * drawable,GimpFilter * filter)
name|gimp_drawable_remove_filter
parameter_list|(
name|GimpDrawable
modifier|*
name|drawable
parameter_list|,
name|GimpFilter
modifier|*
name|filter
parameter_list|)
block|{
name|g_return_if_fail
argument_list|(
name|GIMP_IS_DRAWABLE
argument_list|(
name|drawable
argument_list|)
argument_list|)
expr_stmt|;
name|g_return_if_fail
argument_list|(
name|GIMP_IS_FILTER
argument_list|(
name|filter
argument_list|)
argument_list|)
expr_stmt|;
name|g_return_if_fail
argument_list|(
name|gimp_drawable_has_filter
argument_list|(
name|drawable
argument_list|,
name|filter
argument_list|)
operator|==
name|TRUE
argument_list|)
expr_stmt|;
name|gimp_container_remove
argument_list|(
name|drawable
operator|->
name|private
operator|->
name|filter_stack
argument_list|,
name|GIMP_OBJECT
argument_list|(
name|filter
argument_list|)
argument_list|)
expr_stmt|;
block|}
end_function

begin_function
name|gboolean
DECL|function|gimp_drawable_has_filter (GimpDrawable * drawable,GimpFilter * filter)
name|gimp_drawable_has_filter
parameter_list|(
name|GimpDrawable
modifier|*
name|drawable
parameter_list|,
name|GimpFilter
modifier|*
name|filter
parameter_list|)
block|{
name|g_return_val_if_fail
argument_list|(
name|GIMP_IS_DRAWABLE
argument_list|(
name|drawable
argument_list|)
argument_list|,
name|FALSE
argument_list|)
expr_stmt|;
name|g_return_val_if_fail
argument_list|(
name|GIMP_IS_FILTER
argument_list|(
name|filter
argument_list|)
argument_list|,
name|FALSE
argument_list|)
expr_stmt|;
return|return
name|gimp_container_have
argument_list|(
name|drawable
operator|->
name|private
operator|->
name|filter_stack
argument_list|,
name|GIMP_OBJECT
argument_list|(
name|filter
argument_list|)
argument_list|)
return|;
block|}
end_function

begin_function
name|gboolean
DECL|function|gimp_drawable_merge_filter (GimpDrawable * drawable,GimpFilter * filter,GimpProgress * progress,const gchar * undo_desc,gboolean cancellable,gboolean update)
name|gimp_drawable_merge_filter
parameter_list|(
name|GimpDrawable
modifier|*
name|drawable
parameter_list|,
name|GimpFilter
modifier|*
name|filter
parameter_list|,
name|GimpProgress
modifier|*
name|progress
parameter_list|,
specifier|const
name|gchar
modifier|*
name|undo_desc
parameter_list|,
name|gboolean
name|cancellable
parameter_list|,
name|gboolean
name|update
parameter_list|)
block|{
name|GimpImage
modifier|*
name|image
decl_stmt|;
name|GimpApplicator
modifier|*
name|applicator
decl_stmt|;
name|gboolean
name|applicator_cache
init|=
name|FALSE
decl_stmt|;
specifier|const
name|Babl
modifier|*
name|applicator_output_format
init|=
name|NULL
decl_stmt|;
name|GeglBuffer
modifier|*
name|undo_buffer
decl_stmt|;
name|GeglRectangle
name|undo_rect
decl_stmt|;
name|GeglBuffer
modifier|*
name|cache
init|=
name|NULL
decl_stmt|;
name|GeglRectangle
modifier|*
name|rects
init|=
name|NULL
decl_stmt|;
name|gint
name|n_rects
init|=
literal|0
decl_stmt|;
name|GeglRectangle
name|rect
decl_stmt|;
name|gboolean
name|success
init|=
name|TRUE
decl_stmt|;
name|g_return_val_if_fail
argument_list|(
name|GIMP_IS_DRAWABLE
argument_list|(
name|drawable
argument_list|)
argument_list|,
name|FALSE
argument_list|)
expr_stmt|;
name|g_return_val_if_fail
argument_list|(
name|GIMP_IS_FILTER
argument_list|(
name|filter
argument_list|)
argument_list|,
name|FALSE
argument_list|)
expr_stmt|;
name|g_return_val_if_fail
argument_list|(
name|progress
operator|==
name|NULL
operator|||
name|GIMP_IS_PROGRESS
argument_list|(
name|progress
argument_list|)
argument_list|,
name|FALSE
argument_list|)
expr_stmt|;
name|image
operator|=
name|gimp_item_get_image
argument_list|(
name|GIMP_ITEM
argument_list|(
name|drawable
argument_list|)
argument_list|)
expr_stmt|;
name|applicator
operator|=
name|gimp_filter_get_applicator
argument_list|(
name|filter
argument_list|)
expr_stmt|;
if|if
condition|(
operator|!
name|gimp_item_mask_intersect
argument_list|(
name|GIMP_ITEM
argument_list|(
name|drawable
argument_list|)
argument_list|,
operator|&
name|rect
operator|.
name|x
argument_list|,
operator|&
name|rect
operator|.
name|y
argument_list|,
operator|&
name|rect
operator|.
name|width
argument_list|,
operator|&
name|rect
operator|.
name|height
argument_list|)
condition|)
block|{
return|return
name|TRUE
return|;
block|}
if|if
condition|(
name|applicator
condition|)
block|{
specifier|const
name|GeglRectangle
modifier|*
name|crop_rect
decl_stmt|;
name|crop_rect
operator|=
name|gimp_applicator_get_crop
argument_list|(
name|applicator
argument_list|)
expr_stmt|;
if|if
condition|(
name|crop_rect
operator|&&
operator|!
name|gegl_rectangle_intersect
argument_list|(
operator|&
name|rect
argument_list|,
operator|&
name|rect
argument_list|,
name|crop_rect
argument_list|)
condition|)
return|return
name|TRUE
return|;
comment|/*  the cache and its valid rectangles are the region that        *  has already been processed by this applicator.        */
name|cache
operator|=
name|gimp_applicator_get_cache_buffer
argument_list|(
name|applicator
argument_list|,
operator|&
name|rects
argument_list|,
operator|&
name|n_rects
argument_list|)
expr_stmt|;
comment|/*  skip the cache and output-format conversion while processing        *  the remaining area, so that the result is written directly to        *  the drawable's buffer.        */
name|applicator_cache
operator|=
name|gimp_applicator_get_cache
argument_list|(
name|applicator
argument_list|)
expr_stmt|;
name|applicator_output_format
operator|=
name|gimp_applicator_get_output_format
argument_list|(
name|applicator
argument_list|)
expr_stmt|;
name|gimp_applicator_set_cache
argument_list|(
name|applicator
argument_list|,
name|FALSE
argument_list|)
expr_stmt|;
if|if
condition|(
name|applicator_output_format
operator|==
name|gimp_drawable_get_format
argument_list|(
name|drawable
argument_list|)
condition|)
name|gimp_applicator_set_output_format
argument_list|(
name|applicator
argument_list|,
name|NULL
argument_list|)
expr_stmt|;
block|}
name|gegl_rectangle_align_to_buffer
argument_list|(
operator|&
name|undo_rect
argument_list|,
operator|&
name|rect
argument_list|,
name|gimp_drawable_get_buffer
argument_list|(
name|drawable
argument_list|)
argument_list|,
name|GEGL_RECTANGLE_ALIGNMENT_SUPERSET
argument_list|)
expr_stmt|;
name|undo_buffer
operator|=
name|gegl_buffer_new
argument_list|(
name|GEGL_RECTANGLE
argument_list|(
literal|0
argument_list|,
literal|0
argument_list|,
name|undo_rect
operator|.
name|width
argument_list|,
name|undo_rect
operator|.
name|height
argument_list|)
argument_list|,
name|gimp_drawable_get_format
argument_list|(
name|drawable
argument_list|)
argument_list|)
expr_stmt|;
name|gimp_gegl_buffer_copy
argument_list|(
name|gimp_drawable_get_buffer
argument_list|(
name|drawable
argument_list|)
argument_list|,
operator|&
name|undo_rect
argument_list|,
name|GEGL_ABYSS_NONE
argument_list|,
name|undo_buffer
argument_list|,
name|GEGL_RECTANGLE
argument_list|(
literal|0
argument_list|,
literal|0
argument_list|,
literal|0
argument_list|,
literal|0
argument_list|)
argument_list|)
expr_stmt|;
name|gimp_projection_stop_rendering
argument_list|(
name|gimp_image_get_projection
argument_list|(
name|image
argument_list|)
argument_list|)
expr_stmt|;
if|if
condition|(
name|gimp_gegl_apply_cached_operation
argument_list|(
name|gimp_drawable_get_buffer
argument_list|(
name|drawable
argument_list|)
argument_list|,
name|progress
argument_list|,
name|undo_desc
argument_list|,
name|gimp_filter_get_node
argument_list|(
name|filter
argument_list|)
argument_list|,
name|gimp_drawable_get_buffer
argument_list|(
name|drawable
argument_list|)
argument_list|,
operator|&
name|rect
argument_list|,
name|FALSE
argument_list|,
name|cache
argument_list|,
name|rects
argument_list|,
name|n_rects
argument_list|,
name|cancellable
argument_list|)
condition|)
block|{
comment|/*  finished successfully  */
name|gimp_drawable_push_undo
argument_list|(
name|drawable
argument_list|,
name|undo_desc
argument_list|,
name|undo_buffer
argument_list|,
name|undo_rect
operator|.
name|x
argument_list|,
name|undo_rect
operator|.
name|y
argument_list|,
name|undo_rect
operator|.
name|width
argument_list|,
name|undo_rect
operator|.
name|height
argument_list|)
expr_stmt|;
block|}
else|else
block|{
comment|/*  canceled by the user  */
name|gimp_gegl_buffer_copy
argument_list|(
name|undo_buffer
argument_list|,
name|GEGL_RECTANGLE
argument_list|(
literal|0
argument_list|,
literal|0
argument_list|,
name|undo_rect
operator|.
name|width
argument_list|,
name|undo_rect
operator|.
name|height
argument_list|)
argument_list|,
name|GEGL_ABYSS_NONE
argument_list|,
name|gimp_drawable_get_buffer
argument_list|(
name|drawable
argument_list|)
argument_list|,
operator|&
name|undo_rect
argument_list|)
expr_stmt|;
name|success
operator|=
name|FALSE
expr_stmt|;
block|}
name|g_object_unref
argument_list|(
name|undo_buffer
argument_list|)
expr_stmt|;
if|if
condition|(
name|cache
condition|)
block|{
name|g_object_unref
argument_list|(
name|cache
argument_list|)
expr_stmt|;
name|g_free
argument_list|(
name|rects
argument_list|)
expr_stmt|;
block|}
if|if
condition|(
name|applicator
condition|)
block|{
name|gimp_applicator_set_cache
argument_list|(
name|applicator
argument_list|,
name|applicator_cache
argument_list|)
expr_stmt|;
name|gimp_applicator_set_output_format
argument_list|(
name|applicator
argument_list|,
name|applicator_output_format
argument_list|)
expr_stmt|;
block|}
if|if
condition|(
name|update
condition|)
block|{
name|gimp_drawable_update
argument_list|(
name|drawable
argument_list|,
name|rect
operator|.
name|x
argument_list|,
name|rect
operator|.
name|y
argument_list|,
name|rect
operator|.
name|width
argument_list|,
name|rect
operator|.
name|height
argument_list|)
expr_stmt|;
block|}
return|return
name|success
return|;
block|}
end_function

end_unit

