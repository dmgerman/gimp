begin_unit|revision:0.9.5;language:C;cregit-version:0.0.1
begin_comment
comment|/* GIMP - The GNU Image Manipulation Program  * Copyright (C) 1995 Spencer Kimball and Peter Mattis  *  * gimpdrawable-filter.c  *  * This program is free software: you can redistribute it and/or modify  * it under the terms of the GNU General Public License as published by  * the Free Software Foundation; either version 3 of the License, or  * (at your option) any later version.  *  * This program is distributed in the hope that it will be useful,  * but WITHOUT ANY WARRANTY; without even the implied warranty of  * MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the  * GNU General Public License for more details.  *  * You should have received a copy of the GNU General Public License  * along with this program.  If not, see<http://www.gnu.org/licenses/>.  */
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
file|"gimpdrawable.h"
end_include

begin_include
include|#
directive|include
file|"gimpdrawable-filter.h"
end_include

begin_include
include|#
directive|include
file|"gimpdrawable-private.h"
end_include

begin_include
include|#
directive|include
file|"gimpdrawableundo.h"
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
file|"gimpimage-undo.h"
end_include

begin_include
include|#
directive|include
file|"gimpprogress.h"
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
name|void
DECL|function|gimp_drawable_merge_filter (GimpDrawable * drawable,GimpFilter * filter,GimpProgress * progress,const gchar * undo_desc)
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
parameter_list|)
block|{
name|GeglRectangle
name|rect
decl_stmt|;
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
name|progress
operator|==
name|NULL
operator|||
name|GIMP_IS_PROGRESS
argument_list|(
name|progress
argument_list|)
argument_list|)
expr_stmt|;
if|if
condition|(
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
name|GimpApplicator
modifier|*
name|applicator
decl_stmt|;
name|GeglNode
modifier|*
name|node
decl_stmt|;
name|gimp_drawable_push_undo
argument_list|(
name|drawable
argument_list|,
name|undo_desc
argument_list|,
name|NULL
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
name|node
operator|=
name|gimp_filter_get_node
argument_list|(
name|filter
argument_list|)
expr_stmt|;
name|applicator
operator|=
name|gimp_filter_get_applicator
argument_list|(
name|filter
argument_list|)
expr_stmt|;
comment|/* FIXME: disabled because it is unacceptable to run the        * filter twice, need to use whatever cached result        */
if|if
condition|(
name|FALSE
comment|/* applicator */
condition|)
block|{
name|GimpImage
modifier|*
name|image
init|=
name|gimp_item_get_image
argument_list|(
name|GIMP_ITEM
argument_list|(
name|drawable
argument_list|)
argument_list|)
decl_stmt|;
name|GimpDrawableUndo
modifier|*
name|undo
decl_stmt|;
name|undo
operator|=
name|GIMP_DRAWABLE_UNDO
argument_list|(
name|gimp_image_undo_get_fadeable
argument_list|(
name|image
argument_list|)
argument_list|)
expr_stmt|;
if|if
condition|(
name|undo
condition|)
block|{
name|undo
operator|->
name|paint_mode
operator|=
name|applicator
operator|->
name|paint_mode
expr_stmt|;
name|undo
operator|->
name|opacity
operator|=
name|applicator
operator|->
name|opacity
expr_stmt|;
name|undo
operator|->
name|applied_buffer
operator|=
name|gimp_applicator_dup_apply_buffer
argument_list|(
name|applicator
argument_list|,
operator|&
name|rect
argument_list|)
expr_stmt|;
block|}
block|}
name|gimp_gegl_apply_operation
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
name|node
argument_list|,
name|gimp_drawable_get_buffer
argument_list|(
name|drawable
argument_list|)
argument_list|,
operator|&
name|rect
argument_list|)
expr_stmt|;
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
block|}
end_function

end_unit

