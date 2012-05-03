begin_unit|revision:0.9.5;language:C;cregit-version:0.0.1
begin_comment
comment|/* GIMP - The GNU Image Manipulation Program  * Copyright (C) 1995 Spencer Kimball and Peter Mattis  *  * gimp-apply-operation.c  * Copyright (C) 2012 Ãyvind KolÃ¥s<pippin@gimp.org>  *                    Sven Neumann<sven@gimp.org>  *                    Michael Natterer<mitch@gimp.org>  *  * This program is free software: you can redistribute it and/or modify  * it under the terms of the GNU General Public License as published by  * the Free Software Foundation; either version 3 of the License, or  * (at your option) any later version.  *  * This program is distributed in the hope that it will be useful,  * but WITHOUT ANY WARRANTY; without even the implied warranty of  * MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the  * GNU General Public License for more details.  *  * You should have received a copy of the GNU General Public License  * along with this program.  If not, see<http://www.gnu.org/licenses/>.  */
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
file|"gimp-utils.h"
end_include

begin_include
include|#
directive|include
file|"gimp-apply-operation.h"
end_include

begin_include
include|#
directive|include
file|"gimpprogress.h"
end_include

begin_function
name|void
DECL|function|gimp_apply_operation (GeglBuffer * src_buffer,GimpProgress * progress,const gchar * undo_desc,GeglNode * operation,GeglBuffer * dest_buffer,const GeglRectangle * dest_rect)
name|gimp_apply_operation
parameter_list|(
name|GeglBuffer
modifier|*
name|src_buffer
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
name|GeglNode
modifier|*
name|operation
parameter_list|,
name|GeglBuffer
modifier|*
name|dest_buffer
parameter_list|,
specifier|const
name|GeglRectangle
modifier|*
name|dest_rect
parameter_list|)
block|{
name|GeglNode
modifier|*
name|gegl
decl_stmt|;
name|GeglNode
modifier|*
name|src_node
decl_stmt|;
name|GeglNode
modifier|*
name|dest_node
decl_stmt|;
name|GeglProcessor
modifier|*
name|processor
decl_stmt|;
name|GeglRectangle
name|rect
init|=
block|{
literal|0
block|, }
decl_stmt|;
name|gdouble
name|value
decl_stmt|;
name|g_return_if_fail
argument_list|(
name|GEGL_IS_BUFFER
argument_list|(
name|src_buffer
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
name|GEGL_IS_NODE
argument_list|(
name|operation
argument_list|)
argument_list|)
expr_stmt|;
name|g_return_if_fail
argument_list|(
name|GEGL_IS_BUFFER
argument_list|(
name|dest_buffer
argument_list|)
argument_list|)
expr_stmt|;
if|if
condition|(
name|dest_rect
condition|)
block|{
name|rect
operator|=
operator|*
name|dest_rect
expr_stmt|;
block|}
else|else
block|{
name|rect
operator|=
operator|*
name|GEGL_RECTANGLE
argument_list|(
literal|0
argument_list|,
literal|0
argument_list|,
name|gegl_buffer_get_width
argument_list|(
name|dest_buffer
argument_list|)
argument_list|,
name|gegl_buffer_get_height
argument_list|(
name|dest_buffer
argument_list|)
argument_list|)
expr_stmt|;
block|}
name|gegl
operator|=
name|gegl_node_new
argument_list|()
expr_stmt|;
name|src_node
operator|=
name|gegl_node_new_child
argument_list|(
name|gegl
argument_list|,
literal|"operation"
argument_list|,
literal|"gegl:buffer-source"
argument_list|,
literal|"buffer"
argument_list|,
name|src_buffer
argument_list|,
name|NULL
argument_list|)
expr_stmt|;
name|dest_node
operator|=
name|gegl_node_new_child
argument_list|(
name|gegl
argument_list|,
literal|"operation"
argument_list|,
literal|"gegl:write-buffer"
argument_list|,
literal|"buffer"
argument_list|,
name|dest_buffer
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
name|src_node
argument_list|,
name|operation
argument_list|,
name|dest_node
argument_list|,
name|NULL
argument_list|)
expr_stmt|;
name|processor
operator|=
name|gegl_node_new_processor
argument_list|(
name|dest_node
argument_list|,
operator|&
name|rect
argument_list|)
expr_stmt|;
if|if
condition|(
name|progress
condition|)
block|{
if|if
condition|(
name|gimp_progress_is_active
argument_list|(
name|progress
argument_list|)
condition|)
block|{
if|if
condition|(
name|undo_desc
condition|)
name|gimp_progress_set_text
argument_list|(
name|progress
argument_list|,
name|undo_desc
argument_list|)
expr_stmt|;
block|}
else|else
block|{
name|gimp_progress_start
argument_list|(
name|progress
argument_list|,
name|undo_desc
argument_list|,
name|FALSE
argument_list|)
expr_stmt|;
block|}
block|}
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
name|g_object_unref
argument_list|(
name|gegl
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
block|}
end_function

end_unit

