begin_unit|revision:0.9.5;language:C;cregit-version:0.0.1
begin_comment
comment|/* GIMP - The GNU Image Manipulation Program  * Copyright (C) 1995 Spencer Kimball and Peter Mattis  *  * gimpdrawable-operation.c  * Copyright (C) 2007 Ãyvind KolÃ¥s<pippin@gimp.org>  *                    Sven Neumann<sven@gimp.org>  *                    Michael Natterer<mitch@gimp.org>  *  * This program is free software; you can redistribute it and/or modify  * it under the terms of the GNU General Public License as published by  * the Free Software Foundation; either version 2 of the License, or  * (at your option) any later version.  *  * This program is distributed in the hope that it will be useful,  * but WITHOUT ANY WARRANTY; without even the implied warranty of  * MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the  * GNU General Public License for more details.  *  * You should have received a copy of the GNU General Public License  * along with this program; if not, write to the Free Software  * Foundation, Inc., 59 Temple Place - Suite 330, Boston, MA 02111-1307, USA.  */
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
file|"gimpdrawable.h"
end_include

begin_include
include|#
directive|include
file|"gimpdrawable-operation.h"
end_include

begin_include
include|#
directive|include
file|"gimpprogress.h"
end_include

begin_function
name|void
DECL|function|gimp_drawable_apply_operation (GimpDrawable * drawable,GeglNode * operation,gboolean linear,GimpProgress * progress,const gchar * undo_desc)
name|gimp_drawable_apply_operation
parameter_list|(
name|GimpDrawable
modifier|*
name|drawable
parameter_list|,
name|GeglNode
modifier|*
name|operation
parameter_list|,
name|gboolean
name|linear
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
name|GeglNode
modifier|*
name|gegl
decl_stmt|;
name|GeglNode
modifier|*
name|input
decl_stmt|;
name|GeglNode
modifier|*
name|output
decl_stmt|;
name|GeglProcessor
modifier|*
name|processor
decl_stmt|;
name|GeglRectangle
name|rect
decl_stmt|;
name|gdouble
name|value
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
name|GEGL_IS_NODE
argument_list|(
name|operation
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
name|g_return_if_fail
argument_list|(
name|undo_desc
operator|!=
name|NULL
argument_list|)
expr_stmt|;
if|if
condition|(
operator|!
name|gimp_drawable_mask_intersect
argument_list|(
name|drawable
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
return|return;
name|gegl
operator|=
name|gegl_node_new
argument_list|()
expr_stmt|;
name|input
operator|=
name|gegl_node_new_child
argument_list|(
name|gegl
argument_list|,
literal|"operation"
argument_list|,
literal|"gimp-tilemanager-source"
argument_list|,
literal|"tile-manager"
argument_list|,
name|gimp_drawable_get_tiles
argument_list|(
name|drawable
argument_list|)
argument_list|,
literal|"linear"
argument_list|,
name|linear
argument_list|,
name|NULL
argument_list|)
expr_stmt|;
name|output
operator|=
name|gegl_node_new_child
argument_list|(
name|gegl
argument_list|,
literal|"operation"
argument_list|,
literal|"gimp-tilemanager-sink"
argument_list|,
literal|"tile-manager"
argument_list|,
name|gimp_drawable_get_shadow_tiles
argument_list|(
name|drawable
argument_list|)
argument_list|,
literal|"linear"
argument_list|,
name|linear
argument_list|,
name|NULL
argument_list|)
expr_stmt|;
name|gegl_node_add_child
argument_list|(
name|gegl
argument_list|,
name|operation
argument_list|)
expr_stmt|;
name|gegl_node_link_many
argument_list|(
name|input
argument_list|,
name|operation
argument_list|,
name|output
argument_list|,
name|NULL
argument_list|)
expr_stmt|;
name|processor
operator|=
name|gegl_node_new_processor
argument_list|(
name|output
argument_list|,
operator|&
name|rect
argument_list|)
expr_stmt|;
if|if
condition|(
name|progress
condition|)
name|gimp_progress_start
argument_list|(
name|progress
argument_list|,
name|undo_desc
argument_list|,
name|FALSE
argument_list|)
expr_stmt|;
while|while
condition|(
name|gegl_processor_work
argument_list|(
name|processor
argument_list|,
operator|&
name|value
argument_list|)
condition|)
if|if
condition|(
name|progress
condition|)
name|gimp_progress_set_value
argument_list|(
name|progress
argument_list|,
name|value
argument_list|)
expr_stmt|;
name|g_object_unref
argument_list|(
name|processor
argument_list|)
expr_stmt|;
name|gimp_drawable_merge_shadow
argument_list|(
name|drawable
argument_list|,
name|TRUE
argument_list|,
name|undo_desc
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
if|if
condition|(
name|progress
condition|)
name|gimp_progress_end
argument_list|(
name|progress
argument_list|)
expr_stmt|;
name|g_object_unref
argument_list|(
name|gegl
argument_list|)
expr_stmt|;
block|}
end_function

end_unit

