begin_unit|revision:0.9.5;language:C;cregit-version:0.0.1
begin_comment
comment|/* GIMP - The GNU Image Manipulation Program  * Copyright (C) 1995 Spencer Kimball and Peter Mattis  *  * This program is free software: you can redistribute it and/or modify  * it under the terms of the GNU General Public License as published by  * the Free Software Foundation; either version 3 of the License, or  * (at your option) any later version.  *  * This program is distributed in the hope that it will be useful,  * but WITHOUT ANY WARRANTY; without even the implied warranty of  * MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the  * GNU General Public License for more details.  *  * You should have received a copy of the GNU General Public License  * along with this program.  If not, see<https://www.gnu.org/licenses/>.  */
end_comment

begin_include
include|#
directive|include
file|"config.h"
end_include

begin_include
include|#
directive|include
file|<string.h>
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
file|"libgimpbase/gimpbase.h"
end_include

begin_include
include|#
directive|include
file|"libgimpmath/gimpmath.h"
end_include

begin_include
include|#
directive|include
file|"core-types.h"
end_include

begin_include
include|#
directive|include
file|"gegl/gimp-gegl-mask-combine.h"
end_include

begin_include
include|#
directive|include
file|"gimpchannel.h"
end_include

begin_include
include|#
directive|include
file|"gimpchannel-combine.h"
end_include

begin_function
name|void
DECL|function|gimp_channel_combine_rect (GimpChannel * mask,GimpChannelOps op,gint x,gint y,gint w,gint h)
name|gimp_channel_combine_rect
parameter_list|(
name|GimpChannel
modifier|*
name|mask
parameter_list|,
name|GimpChannelOps
name|op
parameter_list|,
name|gint
name|x
parameter_list|,
name|gint
name|y
parameter_list|,
name|gint
name|w
parameter_list|,
name|gint
name|h
parameter_list|)
block|{
name|GeglBuffer
modifier|*
name|buffer
decl_stmt|;
name|g_return_if_fail
argument_list|(
name|GIMP_IS_CHANNEL
argument_list|(
name|mask
argument_list|)
argument_list|)
expr_stmt|;
name|buffer
operator|=
name|gimp_drawable_get_buffer
argument_list|(
name|GIMP_DRAWABLE
argument_list|(
name|mask
argument_list|)
argument_list|)
expr_stmt|;
if|if
condition|(
operator|!
name|gimp_gegl_mask_combine_rect
argument_list|(
name|buffer
argument_list|,
name|op
argument_list|,
name|x
argument_list|,
name|y
argument_list|,
name|w
argument_list|,
name|h
argument_list|)
condition|)
return|return;
name|gimp_rectangle_intersect
argument_list|(
name|x
argument_list|,
name|y
argument_list|,
name|w
argument_list|,
name|h
argument_list|,
literal|0
argument_list|,
literal|0
argument_list|,
name|gimp_item_get_width
argument_list|(
name|GIMP_ITEM
argument_list|(
name|mask
argument_list|)
argument_list|)
argument_list|,
name|gimp_item_get_height
argument_list|(
name|GIMP_ITEM
argument_list|(
name|mask
argument_list|)
argument_list|)
argument_list|,
operator|&
name|x
argument_list|,
operator|&
name|y
argument_list|,
operator|&
name|w
argument_list|,
operator|&
name|h
argument_list|)
expr_stmt|;
comment|/*  Determine new boundary  */
if|if
condition|(
name|mask
operator|->
name|bounds_known
operator|&&
operator|(
name|op
operator|==
name|GIMP_CHANNEL_OP_ADD
operator|)
operator|&&
operator|!
name|mask
operator|->
name|empty
condition|)
block|{
if|if
condition|(
name|x
operator|<
name|mask
operator|->
name|x1
condition|)
name|mask
operator|->
name|x1
operator|=
name|x
expr_stmt|;
if|if
condition|(
name|y
operator|<
name|mask
operator|->
name|y1
condition|)
name|mask
operator|->
name|y1
operator|=
name|y
expr_stmt|;
if|if
condition|(
operator|(
name|x
operator|+
name|w
operator|)
operator|>
name|mask
operator|->
name|x2
condition|)
name|mask
operator|->
name|x2
operator|=
operator|(
name|x
operator|+
name|w
operator|)
expr_stmt|;
if|if
condition|(
operator|(
name|y
operator|+
name|h
operator|)
operator|>
name|mask
operator|->
name|y2
condition|)
name|mask
operator|->
name|y2
operator|=
operator|(
name|y
operator|+
name|h
operator|)
expr_stmt|;
block|}
elseif|else
if|if
condition|(
name|op
operator|==
name|GIMP_CHANNEL_OP_REPLACE
operator|||
name|mask
operator|->
name|empty
condition|)
block|{
name|mask
operator|->
name|empty
operator|=
name|FALSE
expr_stmt|;
name|mask
operator|->
name|x1
operator|=
name|x
expr_stmt|;
name|mask
operator|->
name|y1
operator|=
name|y
expr_stmt|;
name|mask
operator|->
name|x2
operator|=
name|x
operator|+
name|w
expr_stmt|;
name|mask
operator|->
name|y2
operator|=
name|y
operator|+
name|h
expr_stmt|;
block|}
else|else
block|{
name|mask
operator|->
name|bounds_known
operator|=
name|FALSE
expr_stmt|;
block|}
name|mask
operator|->
name|x1
operator|=
name|CLAMP
argument_list|(
name|mask
operator|->
name|x1
argument_list|,
literal|0
argument_list|,
name|gimp_item_get_width
argument_list|(
name|GIMP_ITEM
argument_list|(
name|mask
argument_list|)
argument_list|)
argument_list|)
expr_stmt|;
name|mask
operator|->
name|y1
operator|=
name|CLAMP
argument_list|(
name|mask
operator|->
name|y1
argument_list|,
literal|0
argument_list|,
name|gimp_item_get_height
argument_list|(
name|GIMP_ITEM
argument_list|(
name|mask
argument_list|)
argument_list|)
argument_list|)
expr_stmt|;
name|mask
operator|->
name|x2
operator|=
name|CLAMP
argument_list|(
name|mask
operator|->
name|x2
argument_list|,
literal|0
argument_list|,
name|gimp_item_get_width
argument_list|(
name|GIMP_ITEM
argument_list|(
name|mask
argument_list|)
argument_list|)
argument_list|)
expr_stmt|;
name|mask
operator|->
name|y2
operator|=
name|CLAMP
argument_list|(
name|mask
operator|->
name|y2
argument_list|,
literal|0
argument_list|,
name|gimp_item_get_height
argument_list|(
name|GIMP_ITEM
argument_list|(
name|mask
argument_list|)
argument_list|)
argument_list|)
expr_stmt|;
name|gimp_drawable_update
argument_list|(
name|GIMP_DRAWABLE
argument_list|(
name|mask
argument_list|)
argument_list|,
name|x
argument_list|,
name|y
argument_list|,
name|w
argument_list|,
name|h
argument_list|)
expr_stmt|;
block|}
end_function

begin_function
name|void
DECL|function|gimp_channel_combine_ellipse (GimpChannel * mask,GimpChannelOps op,gint x,gint y,gint w,gint h,gboolean antialias)
name|gimp_channel_combine_ellipse
parameter_list|(
name|GimpChannel
modifier|*
name|mask
parameter_list|,
name|GimpChannelOps
name|op
parameter_list|,
name|gint
name|x
parameter_list|,
name|gint
name|y
parameter_list|,
name|gint
name|w
parameter_list|,
name|gint
name|h
parameter_list|,
name|gboolean
name|antialias
parameter_list|)
block|{
name|gimp_channel_combine_ellipse_rect
argument_list|(
name|mask
argument_list|,
name|op
argument_list|,
name|x
argument_list|,
name|y
argument_list|,
name|w
argument_list|,
name|h
argument_list|,
name|w
operator|/
literal|2.0
argument_list|,
name|h
operator|/
literal|2.0
argument_list|,
name|antialias
argument_list|)
expr_stmt|;
block|}
end_function

begin_function
name|void
DECL|function|gimp_channel_combine_ellipse_rect (GimpChannel * mask,GimpChannelOps op,gint x,gint y,gint w,gint h,gdouble rx,gdouble ry,gboolean antialias)
name|gimp_channel_combine_ellipse_rect
parameter_list|(
name|GimpChannel
modifier|*
name|mask
parameter_list|,
name|GimpChannelOps
name|op
parameter_list|,
name|gint
name|x
parameter_list|,
name|gint
name|y
parameter_list|,
name|gint
name|w
parameter_list|,
name|gint
name|h
parameter_list|,
name|gdouble
name|rx
parameter_list|,
name|gdouble
name|ry
parameter_list|,
name|gboolean
name|antialias
parameter_list|)
block|{
name|GeglBuffer
modifier|*
name|buffer
decl_stmt|;
name|g_return_if_fail
argument_list|(
name|GIMP_IS_CHANNEL
argument_list|(
name|mask
argument_list|)
argument_list|)
expr_stmt|;
name|g_return_if_fail
argument_list|(
name|op
operator|!=
name|GIMP_CHANNEL_OP_INTERSECT
argument_list|)
expr_stmt|;
name|buffer
operator|=
name|gimp_drawable_get_buffer
argument_list|(
name|GIMP_DRAWABLE
argument_list|(
name|mask
argument_list|)
argument_list|)
expr_stmt|;
if|if
condition|(
operator|!
name|gimp_gegl_mask_combine_ellipse_rect
argument_list|(
name|buffer
argument_list|,
name|op
argument_list|,
name|x
argument_list|,
name|y
argument_list|,
name|w
argument_list|,
name|h
argument_list|,
name|rx
argument_list|,
name|ry
argument_list|,
name|antialias
argument_list|)
condition|)
return|return;
name|gimp_rectangle_intersect
argument_list|(
name|x
argument_list|,
name|y
argument_list|,
name|w
argument_list|,
name|h
argument_list|,
literal|0
argument_list|,
literal|0
argument_list|,
name|gimp_item_get_width
argument_list|(
name|GIMP_ITEM
argument_list|(
name|mask
argument_list|)
argument_list|)
argument_list|,
name|gimp_item_get_height
argument_list|(
name|GIMP_ITEM
argument_list|(
name|mask
argument_list|)
argument_list|)
argument_list|,
operator|&
name|x
argument_list|,
operator|&
name|y
argument_list|,
operator|&
name|w
argument_list|,
operator|&
name|h
argument_list|)
expr_stmt|;
comment|/*  determine new boundary  */
if|if
condition|(
name|mask
operator|->
name|bounds_known
operator|&&
operator|(
name|op
operator|==
name|GIMP_CHANNEL_OP_ADD
operator|)
operator|&&
operator|!
name|mask
operator|->
name|empty
condition|)
block|{
if|if
condition|(
name|x
operator|<
name|mask
operator|->
name|x1
condition|)
name|mask
operator|->
name|x1
operator|=
name|x
expr_stmt|;
if|if
condition|(
name|y
operator|<
name|mask
operator|->
name|y1
condition|)
name|mask
operator|->
name|y1
operator|=
name|y
expr_stmt|;
if|if
condition|(
operator|(
name|x
operator|+
name|w
operator|)
operator|>
name|mask
operator|->
name|x2
condition|)
name|mask
operator|->
name|x2
operator|=
operator|(
name|x
operator|+
name|w
operator|)
expr_stmt|;
if|if
condition|(
operator|(
name|y
operator|+
name|h
operator|)
operator|>
name|mask
operator|->
name|y2
condition|)
name|mask
operator|->
name|y2
operator|=
operator|(
name|y
operator|+
name|h
operator|)
expr_stmt|;
block|}
elseif|else
if|if
condition|(
name|op
operator|==
name|GIMP_CHANNEL_OP_REPLACE
operator|||
name|mask
operator|->
name|empty
condition|)
block|{
name|mask
operator|->
name|empty
operator|=
name|FALSE
expr_stmt|;
name|mask
operator|->
name|x1
operator|=
name|x
expr_stmt|;
name|mask
operator|->
name|y1
operator|=
name|y
expr_stmt|;
name|mask
operator|->
name|x2
operator|=
name|x
operator|+
name|w
expr_stmt|;
name|mask
operator|->
name|y2
operator|=
name|y
operator|+
name|h
expr_stmt|;
block|}
else|else
block|{
name|mask
operator|->
name|bounds_known
operator|=
name|FALSE
expr_stmt|;
block|}
name|gimp_drawable_update
argument_list|(
name|GIMP_DRAWABLE
argument_list|(
name|mask
argument_list|)
argument_list|,
name|x
argument_list|,
name|y
argument_list|,
name|w
argument_list|,
name|h
argument_list|)
expr_stmt|;
block|}
end_function

begin_function
name|void
DECL|function|gimp_channel_combine_mask (GimpChannel * mask,GimpChannel * add_on,GimpChannelOps op,gint off_x,gint off_y)
name|gimp_channel_combine_mask
parameter_list|(
name|GimpChannel
modifier|*
name|mask
parameter_list|,
name|GimpChannel
modifier|*
name|add_on
parameter_list|,
name|GimpChannelOps
name|op
parameter_list|,
name|gint
name|off_x
parameter_list|,
name|gint
name|off_y
parameter_list|)
block|{
name|GeglBuffer
modifier|*
name|add_on_buffer
decl_stmt|;
name|g_return_if_fail
argument_list|(
name|GIMP_IS_CHANNEL
argument_list|(
name|mask
argument_list|)
argument_list|)
expr_stmt|;
name|g_return_if_fail
argument_list|(
name|GIMP_IS_CHANNEL
argument_list|(
name|add_on
argument_list|)
argument_list|)
expr_stmt|;
name|add_on_buffer
operator|=
name|gimp_drawable_get_buffer
argument_list|(
name|GIMP_DRAWABLE
argument_list|(
name|add_on
argument_list|)
argument_list|)
expr_stmt|;
name|gimp_channel_combine_buffer
argument_list|(
name|mask
argument_list|,
name|add_on_buffer
argument_list|,
name|op
argument_list|,
name|off_x
argument_list|,
name|off_y
argument_list|)
expr_stmt|;
block|}
end_function

begin_function
name|void
DECL|function|gimp_channel_combine_buffer (GimpChannel * mask,GeglBuffer * add_on_buffer,GimpChannelOps op,gint off_x,gint off_y)
name|gimp_channel_combine_buffer
parameter_list|(
name|GimpChannel
modifier|*
name|mask
parameter_list|,
name|GeglBuffer
modifier|*
name|add_on_buffer
parameter_list|,
name|GimpChannelOps
name|op
parameter_list|,
name|gint
name|off_x
parameter_list|,
name|gint
name|off_y
parameter_list|)
block|{
name|GeglBuffer
modifier|*
name|buffer
decl_stmt|;
name|gint
name|x
decl_stmt|,
name|y
decl_stmt|,
name|w
decl_stmt|,
name|h
decl_stmt|;
name|g_return_if_fail
argument_list|(
name|GIMP_IS_CHANNEL
argument_list|(
name|mask
argument_list|)
argument_list|)
expr_stmt|;
name|g_return_if_fail
argument_list|(
name|GEGL_IS_BUFFER
argument_list|(
name|add_on_buffer
argument_list|)
argument_list|)
expr_stmt|;
name|buffer
operator|=
name|gimp_drawable_get_buffer
argument_list|(
name|GIMP_DRAWABLE
argument_list|(
name|mask
argument_list|)
argument_list|)
expr_stmt|;
if|if
condition|(
operator|!
name|gimp_gegl_mask_combine_buffer
argument_list|(
name|buffer
argument_list|,
name|add_on_buffer
argument_list|,
name|op
argument_list|,
name|off_x
argument_list|,
name|off_y
argument_list|)
condition|)
return|return;
name|gimp_rectangle_intersect
argument_list|(
name|off_x
argument_list|,
name|off_y
argument_list|,
name|gegl_buffer_get_width
argument_list|(
name|add_on_buffer
argument_list|)
argument_list|,
name|gegl_buffer_get_height
argument_list|(
name|add_on_buffer
argument_list|)
argument_list|,
literal|0
argument_list|,
literal|0
argument_list|,
name|gimp_item_get_width
argument_list|(
name|GIMP_ITEM
argument_list|(
name|mask
argument_list|)
argument_list|)
argument_list|,
name|gimp_item_get_height
argument_list|(
name|GIMP_ITEM
argument_list|(
name|mask
argument_list|)
argument_list|)
argument_list|,
operator|&
name|x
argument_list|,
operator|&
name|y
argument_list|,
operator|&
name|w
argument_list|,
operator|&
name|h
argument_list|)
expr_stmt|;
name|mask
operator|->
name|bounds_known
operator|=
name|FALSE
expr_stmt|;
name|gimp_drawable_update
argument_list|(
name|GIMP_DRAWABLE
argument_list|(
name|mask
argument_list|)
argument_list|,
name|x
argument_list|,
name|y
argument_list|,
name|w
argument_list|,
name|h
argument_list|)
expr_stmt|;
block|}
end_function

end_unit

