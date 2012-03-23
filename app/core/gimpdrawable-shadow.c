begin_unit|revision:0.9.5;language:C;cregit-version:0.0.1
begin_comment
comment|/* GIMP - The GNU Image Manipulation Program  * Copyright (C) 1995 Spencer Kimball and Peter Mattis  *  * This program is free software: you can redistribute it and/or modify  * it under the terms of the GNU General Public License as published by  * the Free Software Foundation; either version 3 of the License, or  * (at your option) any later version.  *  * This program is distributed in the hope that it will be useful,  * but WITHOUT ANY WARRANTY; without even the implied warranty of  * MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the  * GNU General Public License for more details.  *  * You should have received a copy of the GNU General Public License  * along with this program.  If not, see<http://www.gnu.org/licenses/>.  */
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
file|"core-types.h"
end_include

begin_include
include|#
directive|include
file|"gegl/gimp-gegl-utils.h"
end_include

begin_include
include|#
directive|include
file|"gimpdrawable.h"
end_include

begin_include
include|#
directive|include
file|"gimpdrawable-private.h"
end_include

begin_include
include|#
directive|include
file|"gimpdrawable-shadow.h"
end_include

begin_function
name|GeglBuffer
modifier|*
DECL|function|gimp_drawable_get_shadow_buffer (GimpDrawable * drawable)
name|gimp_drawable_get_shadow_buffer
parameter_list|(
name|GimpDrawable
modifier|*
name|drawable
parameter_list|)
block|{
name|GimpItem
modifier|*
name|item
decl_stmt|;
name|gint
name|width
decl_stmt|;
name|gint
name|height
decl_stmt|;
specifier|const
name|Babl
modifier|*
name|format
decl_stmt|;
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
name|item
operator|=
name|GIMP_ITEM
argument_list|(
name|drawable
argument_list|)
expr_stmt|;
name|width
operator|=
name|gimp_item_get_width
argument_list|(
name|item
argument_list|)
expr_stmt|;
name|height
operator|=
name|gimp_item_get_height
argument_list|(
name|item
argument_list|)
expr_stmt|;
name|format
operator|=
name|gimp_drawable_get_format
argument_list|(
name|drawable
argument_list|)
expr_stmt|;
if|if
condition|(
name|drawable
operator|->
name|private
operator|->
name|shadow
condition|)
block|{
if|if
condition|(
operator|(
name|width
operator|!=
name|gegl_buffer_get_width
argument_list|(
name|drawable
operator|->
name|private
operator|->
name|shadow
argument_list|)
operator|)
operator|||
operator|(
name|height
operator|!=
name|gegl_buffer_get_height
argument_list|(
name|drawable
operator|->
name|private
operator|->
name|shadow
argument_list|)
operator|)
operator|||
operator|(
name|format
operator|!=
name|gegl_buffer_get_format
argument_list|(
name|drawable
operator|->
name|private
operator|->
name|shadow
argument_list|)
operator|)
condition|)
block|{
name|gimp_drawable_free_shadow_buffer
argument_list|(
name|drawable
argument_list|)
expr_stmt|;
block|}
else|else
block|{
name|gegl_buffer_flush
argument_list|(
name|drawable
operator|->
name|private
operator|->
name|shadow
argument_list|)
expr_stmt|;
name|gimp_gegl_buffer_refetch_tiles
argument_list|(
name|drawable
operator|->
name|private
operator|->
name|shadow
argument_list|)
expr_stmt|;
return|return
name|drawable
operator|->
name|private
operator|->
name|shadow
return|;
block|}
block|}
name|drawable
operator|->
name|private
operator|->
name|shadow
operator|=
name|gimp_gegl_buffer_new
argument_list|(
name|GIMP_GEGL_RECT
argument_list|(
literal|0
argument_list|,
literal|0
argument_list|,
name|width
argument_list|,
name|height
argument_list|)
argument_list|,
name|format
argument_list|)
expr_stmt|;
return|return
name|drawable
operator|->
name|private
operator|->
name|shadow
return|;
block|}
end_function

begin_function
name|void
DECL|function|gimp_drawable_free_shadow_buffer (GimpDrawable * drawable)
name|gimp_drawable_free_shadow_buffer
parameter_list|(
name|GimpDrawable
modifier|*
name|drawable
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
if|if
condition|(
name|drawable
operator|->
name|private
operator|->
name|shadow
condition|)
block|{
name|g_object_unref
argument_list|(
name|drawable
operator|->
name|private
operator|->
name|shadow
argument_list|)
expr_stmt|;
name|drawable
operator|->
name|private
operator|->
name|shadow
operator|=
name|NULL
expr_stmt|;
block|}
block|}
end_function

begin_function
name|void
DECL|function|gimp_drawable_merge_shadow_buffer (GimpDrawable * drawable,gboolean push_undo,const gchar * undo_desc)
name|gimp_drawable_merge_shadow_buffer
parameter_list|(
name|GimpDrawable
modifier|*
name|drawable
parameter_list|,
name|gboolean
name|push_undo
parameter_list|,
specifier|const
name|gchar
modifier|*
name|undo_desc
parameter_list|)
block|{
name|gint
name|x
decl_stmt|,
name|y
decl_stmt|;
name|gint
name|width
decl_stmt|,
name|height
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
name|gimp_item_is_attached
argument_list|(
name|GIMP_ITEM
argument_list|(
name|drawable
argument_list|)
argument_list|)
argument_list|)
expr_stmt|;
name|g_return_if_fail
argument_list|(
name|GEGL_IS_BUFFER
argument_list|(
name|drawable
operator|->
name|private
operator|->
name|shadow
argument_list|)
argument_list|)
expr_stmt|;
comment|/*  A useful optimization here is to limit the update to the    *  extents of the selection mask, as it cannot extend beyond    *  them.    */
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
name|x
argument_list|,
operator|&
name|y
argument_list|,
operator|&
name|width
argument_list|,
operator|&
name|height
argument_list|)
condition|)
block|{
name|GeglBuffer
modifier|*
name|buffer
init|=
name|g_object_ref
argument_list|(
name|drawable
operator|->
name|private
operator|->
name|shadow
argument_list|)
decl_stmt|;
name|gimp_drawable_apply_buffer
argument_list|(
name|drawable
argument_list|,
name|buffer
argument_list|,
name|GIMP_GEGL_RECT
argument_list|(
name|x
argument_list|,
name|y
argument_list|,
name|width
argument_list|,
name|height
argument_list|)
argument_list|,
name|push_undo
argument_list|,
name|undo_desc
argument_list|,
name|GIMP_OPACITY_OPAQUE
argument_list|,
name|GIMP_REPLACE_MODE
argument_list|,
name|NULL
argument_list|,
name|x
argument_list|,
name|y
argument_list|,
name|NULL
argument_list|,
name|x
argument_list|,
name|y
argument_list|)
expr_stmt|;
name|g_object_unref
argument_list|(
name|buffer
argument_list|)
expr_stmt|;
block|}
block|}
end_function

end_unit

