begin_unit|revision:0.9.5;language:C;cregit-version:0.0.1
begin_comment
comment|/* GIMP - The GNU Image Manipulation Program  * Copyright (C) 1995 Spencer Kimball and Peter Mattis  *  * This program is free software; you can redistribute it and/or modify  * it under the terms of the GNU General Public License as published by  * the Free Software Foundation; either version 2 of the License, or  * (at your option) any later version.  *  * This program is distributed in the hope that it will be useful,  * but WITHOUT ANY WARRANTY; without even the implied warranty of  * MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the  * GNU General Public License for more details.  *  * You should have received a copy of the GNU General Public License  * along with this program; if not, write to the Free Software  * Foundation, Inc., 59 Temple Place - Suite 330, Boston, MA 02111-1307, USA.  */
end_comment

begin_include
include|#
directive|include
file|"config.h"
end_include

begin_include
include|#
directive|include
file|<glib-object.h>
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
file|"paint-funcs/paint-funcs.h"
end_include

begin_include
include|#
directive|include
file|"base/pixel-processor.h"
end_include

begin_include
include|#
directive|include
file|"base/pixel-region.h"
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
DECL|function|gimp_channel_add_segment (GimpChannel * mask,gint x,gint y,gint width,gint value)
name|gimp_channel_add_segment
parameter_list|(
name|GimpChannel
modifier|*
name|mask
parameter_list|,
name|gint
name|x
parameter_list|,
name|gint
name|y
parameter_list|,
name|gint
name|width
parameter_list|,
name|gint
name|value
parameter_list|)
block|{
name|PixelRegion
name|maskPR
decl_stmt|;
name|guchar
modifier|*
name|data
decl_stmt|;
name|gint
name|val
decl_stmt|;
name|gint
name|x2
decl_stmt|;
name|gpointer
name|pr
decl_stmt|;
name|g_return_if_fail
argument_list|(
name|GIMP_IS_CHANNEL
argument_list|(
name|mask
argument_list|)
argument_list|)
expr_stmt|;
comment|/*  check horizontal extents...  */
name|x2
operator|=
name|x
operator|+
name|width
expr_stmt|;
name|x2
operator|=
name|CLAMP
argument_list|(
name|x2
argument_list|,
literal|0
argument_list|,
name|GIMP_ITEM
argument_list|(
name|mask
argument_list|)
operator|->
name|width
argument_list|)
expr_stmt|;
name|x
operator|=
name|CLAMP
argument_list|(
name|x
argument_list|,
literal|0
argument_list|,
name|GIMP_ITEM
argument_list|(
name|mask
argument_list|)
operator|->
name|width
argument_list|)
expr_stmt|;
name|width
operator|=
name|x2
operator|-
name|x
expr_stmt|;
if|if
condition|(
operator|!
name|width
condition|)
return|return;
if|if
condition|(
name|y
operator|<
literal|0
operator|||
name|y
operator|>=
name|GIMP_ITEM
argument_list|(
name|mask
argument_list|)
operator|->
name|height
condition|)
return|return;
name|pixel_region_init
argument_list|(
operator|&
name|maskPR
argument_list|,
name|GIMP_DRAWABLE
argument_list|(
name|mask
argument_list|)
operator|->
name|tiles
argument_list|,
name|x
argument_list|,
name|y
argument_list|,
name|width
argument_list|,
literal|1
argument_list|,
name|TRUE
argument_list|)
expr_stmt|;
for|for
control|(
name|pr
operator|=
name|pixel_regions_register
argument_list|(
literal|1
argument_list|,
operator|&
name|maskPR
argument_list|)
init|;
name|pr
operator|!=
name|NULL
condition|;
name|pr
operator|=
name|pixel_regions_process
argument_list|(
name|pr
argument_list|)
control|)
block|{
name|data
operator|=
name|maskPR
operator|.
name|data
expr_stmt|;
name|width
operator|=
name|maskPR
operator|.
name|w
expr_stmt|;
while|while
condition|(
name|width
operator|--
condition|)
block|{
name|val
operator|=
operator|*
name|data
operator|+
name|value
expr_stmt|;
if|if
condition|(
name|val
operator|>
literal|255
condition|)
name|val
operator|=
literal|255
expr_stmt|;
operator|*
name|data
operator|++
operator|=
name|val
expr_stmt|;
block|}
block|}
block|}
end_function

begin_function
name|void
DECL|function|gimp_channel_sub_segment (GimpChannel * mask,gint x,gint y,gint width,gint value)
name|gimp_channel_sub_segment
parameter_list|(
name|GimpChannel
modifier|*
name|mask
parameter_list|,
name|gint
name|x
parameter_list|,
name|gint
name|y
parameter_list|,
name|gint
name|width
parameter_list|,
name|gint
name|value
parameter_list|)
block|{
name|PixelRegion
name|maskPR
decl_stmt|;
name|guchar
modifier|*
name|data
decl_stmt|;
name|gint
name|val
decl_stmt|;
name|gint
name|x2
decl_stmt|;
name|gpointer
name|pr
decl_stmt|;
name|g_return_if_fail
argument_list|(
name|GIMP_IS_CHANNEL
argument_list|(
name|mask
argument_list|)
argument_list|)
expr_stmt|;
comment|/*  check horizontal extents...  */
name|x2
operator|=
name|x
operator|+
name|width
expr_stmt|;
name|x2
operator|=
name|CLAMP
argument_list|(
name|x2
argument_list|,
literal|0
argument_list|,
name|GIMP_ITEM
argument_list|(
name|mask
argument_list|)
operator|->
name|width
argument_list|)
expr_stmt|;
name|x
operator|=
name|CLAMP
argument_list|(
name|x
argument_list|,
literal|0
argument_list|,
name|GIMP_ITEM
argument_list|(
name|mask
argument_list|)
operator|->
name|width
argument_list|)
expr_stmt|;
name|width
operator|=
name|x2
operator|-
name|x
expr_stmt|;
if|if
condition|(
operator|!
name|width
condition|)
return|return;
if|if
condition|(
name|y
operator|<
literal|0
operator|||
name|y
operator|>
name|GIMP_ITEM
argument_list|(
name|mask
argument_list|)
operator|->
name|height
condition|)
return|return;
name|pixel_region_init
argument_list|(
operator|&
name|maskPR
argument_list|,
name|GIMP_DRAWABLE
argument_list|(
name|mask
argument_list|)
operator|->
name|tiles
argument_list|,
name|x
argument_list|,
name|y
argument_list|,
name|width
argument_list|,
literal|1
argument_list|,
name|TRUE
argument_list|)
expr_stmt|;
for|for
control|(
name|pr
operator|=
name|pixel_regions_register
argument_list|(
literal|1
argument_list|,
operator|&
name|maskPR
argument_list|)
init|;
name|pr
operator|!=
name|NULL
condition|;
name|pr
operator|=
name|pixel_regions_process
argument_list|(
name|pr
argument_list|)
control|)
block|{
name|data
operator|=
name|maskPR
operator|.
name|data
expr_stmt|;
name|width
operator|=
name|maskPR
operator|.
name|w
expr_stmt|;
while|while
condition|(
name|width
operator|--
condition|)
block|{
name|val
operator|=
operator|*
name|data
operator|-
name|value
expr_stmt|;
if|if
condition|(
name|val
operator|<
literal|0
condition|)
name|val
operator|=
literal|0
expr_stmt|;
operator|*
name|data
operator|++
operator|=
name|val
expr_stmt|;
block|}
block|}
block|}
end_function

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
name|PixelRegion
name|maskPR
decl_stmt|;
name|guchar
name|color
decl_stmt|;
name|g_return_if_fail
argument_list|(
name|GIMP_IS_CHANNEL
argument_list|(
name|mask
argument_list|)
argument_list|)
expr_stmt|;
if|if
condition|(
operator|!
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
name|GIMP_ITEM
argument_list|(
name|mask
argument_list|)
operator|->
name|width
argument_list|,
name|GIMP_ITEM
argument_list|(
name|mask
argument_list|)
operator|->
name|height
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
condition|)
return|return;
name|pixel_region_init
argument_list|(
operator|&
name|maskPR
argument_list|,
name|GIMP_DRAWABLE
argument_list|(
name|mask
argument_list|)
operator|->
name|tiles
argument_list|,
name|x
argument_list|,
name|y
argument_list|,
name|w
argument_list|,
name|h
argument_list|,
name|TRUE
argument_list|)
expr_stmt|;
if|if
condition|(
name|op
operator|==
name|GIMP_CHANNEL_OP_ADD
operator|||
name|op
operator|==
name|GIMP_CHANNEL_OP_REPLACE
condition|)
name|color
operator|=
name|OPAQUE_OPACITY
expr_stmt|;
else|else
name|color
operator|=
name|TRANSPARENT_OPACITY
expr_stmt|;
name|color_region
argument_list|(
operator|&
name|maskPR
argument_list|,
operator|&
name|color
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
name|mask
operator|->
name|bounds_known
operator|=
name|FALSE
expr_stmt|;
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
name|GIMP_ITEM
argument_list|(
name|mask
argument_list|)
operator|->
name|width
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
name|GIMP_ITEM
argument_list|(
name|mask
argument_list|)
operator|->
name|height
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
name|GIMP_ITEM
argument_list|(
name|mask
argument_list|)
operator|->
name|width
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
name|GIMP_ITEM
argument_list|(
name|mask
argument_list|)
operator|->
name|height
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

begin_comment
comment|/**  * gimp_channel_combine_ellipse:  * @mask:      the channel with which to combine the ellipse  * @op:        whether to replace, add to, or subtract from the current  *             contents  * @x:         x coordinate of upper left corner of ellipse  * @y:         y coordinate of upper left corner of ellipse  * @w:         width of ellipse bounding box  * @h:         height of ellipse bounding box  * @antialias: if %TRUE, antialias the ellipse  *  * Mainly used for elliptical selections.  If @op is  * %GIMP_CHANNEL_OP_REPLACE or %GIMP_CHANNEL_OP_ADD, sets pixels  * within the ellipse to 255.  If @op is %GIMP_CHANNEL_OP_SUBTRACT,  * sets pixels within to zero.  If @antialias is %TRUE, pixels that  * impinge on the edge of the ellipse are set to intermediate values,  * depending on how much they overlap.  **/
end_comment

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
specifier|static
specifier|inline
name|void
DECL|function|gimp_channel_combine_segment (GimpChannel * mask,GimpChannelOps op,gint start,gint row,gint width,gint value)
name|gimp_channel_combine_segment
parameter_list|(
name|GimpChannel
modifier|*
name|mask
parameter_list|,
name|GimpChannelOps
name|op
parameter_list|,
name|gint
name|start
parameter_list|,
name|gint
name|row
parameter_list|,
name|gint
name|width
parameter_list|,
name|gint
name|value
parameter_list|)
block|{
switch|switch
condition|(
name|op
condition|)
block|{
case|case
name|GIMP_CHANNEL_OP_ADD
case|:
case|case
name|GIMP_CHANNEL_OP_REPLACE
case|:
name|gimp_channel_add_segment
argument_list|(
name|mask
argument_list|,
name|start
argument_list|,
name|row
argument_list|,
name|width
argument_list|,
name|value
argument_list|)
expr_stmt|;
break|break;
case|case
name|GIMP_CHANNEL_OP_SUBTRACT
case|:
name|gimp_channel_sub_segment
argument_list|(
name|mask
argument_list|,
name|start
argument_list|,
name|row
argument_list|,
name|width
argument_list|,
name|value
argument_list|)
expr_stmt|;
break|break;
case|case
name|GIMP_CHANNEL_OP_INTERSECT
case|:
comment|/* Should not happend */
break|break;
block|}
block|}
end_function

begin_comment
comment|/**  * gimp_channel_combine_ellipse_rect:  * @mask:      the channel with which to combine the elliptic rect  * @op:        whether to replace, add to, or subtract from the current  *             contents  * @x:         x coordinate of upper left corner of bounding rect  * @y:         y coordinate of upper left corner of bounding rect  * @w:         width of bounding rect  * @h:         height of bounding rect  * @a:         elliptic a-constant applied to corners  * @b:         elliptic b-constant applied to corners  * @antialias: if %TRUE, antialias the elliptic corners  *  * Used for rounded cornered rectangles and ellipses.  If @op is  * %GIMP_CHANNEL_OP_REPLACE or %GIMP_CHANNEL_OP_ADD, sets pixels  * within the ellipse to 255.  If @op is %GIMP_CHANNEL_OP_SUBTRACT,  * sets pixels within to zero.  If @antialias is %TRUE, pixels that  * impinge on the edge of the ellipse are set to intermediate values,  * depending on how much they overlap.  **/
end_comment

begin_function
name|void
DECL|function|gimp_channel_combine_ellipse_rect (GimpChannel * mask,GimpChannelOps op,gint x,gint y,gint w,gint h,gdouble a,gdouble b,gboolean antialias)
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
name|a
parameter_list|,
name|gdouble
name|b
parameter_list|,
name|gboolean
name|antialias
parameter_list|)
block|{
name|gint
name|cur_y
decl_stmt|;
name|gdouble
name|a_sqr
decl_stmt|;
name|gdouble
name|b_sqr
decl_stmt|;
name|gdouble
name|straight_width
decl_stmt|;
name|gdouble
name|straight_height
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
name|a
operator|>=
literal|0.0
operator|&&
name|b
operator|>=
literal|0.0
argument_list|)
expr_stmt|;
if|if
condition|(
operator|!
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
name|GIMP_ITEM
argument_list|(
name|mask
argument_list|)
operator|->
name|width
argument_list|,
name|GIMP_ITEM
argument_list|(
name|mask
argument_list|)
operator|->
name|height
argument_list|,
name|NULL
argument_list|,
name|NULL
argument_list|,
name|NULL
argument_list|,
name|NULL
argument_list|)
condition|)
block|{
return|return;
block|}
comment|/*  Allow us to use gimp_channel_combine_segment without breaking    *  previous logic    */
if|if
condition|(
name|op
operator|==
name|GIMP_CHANNEL_OP_INTERSECT
condition|)
return|return;
comment|/* Make sure the elliptic corners fit into the rect */
name|a
operator|=
name|MIN
argument_list|(
name|a
argument_list|,
name|w
operator|/
literal|2.0
argument_list|)
expr_stmt|;
name|b
operator|=
name|MIN
argument_list|(
name|b
argument_list|,
name|h
operator|/
literal|2.0
argument_list|)
expr_stmt|;
name|a_sqr
operator|=
name|SQR
argument_list|(
name|a
argument_list|)
expr_stmt|;
name|b_sqr
operator|=
name|SQR
argument_list|(
name|b
argument_list|)
expr_stmt|;
name|straight_width
operator|=
name|w
operator|-
literal|2
operator|*
name|a
expr_stmt|;
name|straight_height
operator|=
name|h
operator|-
literal|2
operator|*
name|b
expr_stmt|;
for|for
control|(
name|cur_y
operator|=
name|y
init|;
name|cur_y
operator|<
operator|(
name|y
operator|+
name|h
operator|)
condition|;
name|cur_y
operator|++
control|)
block|{
name|gdouble
name|x_start
decl_stmt|;
name|gdouble
name|x_end
decl_stmt|;
name|gdouble
name|ellipse_center_x
decl_stmt|;
name|gdouble
name|ellipse_center_y
decl_stmt|;
name|gdouble
name|half_ellipse_width_at_y
decl_stmt|;
comment|/* If this row is not part of the mask, continue with the next row */
if|if
condition|(
name|cur_y
operator|<
literal|0
operator|||
name|cur_y
operator|>=
name|GIMP_ITEM
argument_list|(
name|mask
argument_list|)
operator|->
name|height
condition|)
block|{
continue|continue;
block|}
comment|/* If we are on a row not affected by rounded corners, simply combine the        * whole row.        */
if|if
condition|(
name|cur_y
operator|>=
name|y
operator|+
name|b
operator|&&
name|cur_y
operator|<
name|y
operator|+
name|b
operator|+
name|straight_height
condition|)
block|{
name|x_start
operator|=
name|x
expr_stmt|;
name|x_end
operator|=
name|x
operator|+
name|w
expr_stmt|;
name|gimp_channel_combine_segment
argument_list|(
name|mask
argument_list|,
name|op
argument_list|,
name|x_start
argument_list|,
name|cur_y
argument_list|,
name|x_end
operator|-
name|x_start
argument_list|,
literal|255
argument_list|)
expr_stmt|;
continue|continue;
block|}
comment|/* Match the ellipse center y with our current y */
if|if
condition|(
name|cur_y
operator|<
name|y
operator|+
name|b
condition|)
block|{
name|ellipse_center_y
operator|=
name|y
operator|+
name|b
expr_stmt|;
block|}
else|else
block|{
name|ellipse_center_y
operator|=
name|y
operator|+
name|b
operator|+
name|straight_height
expr_stmt|;
block|}
comment|/* For a non-antialiased ellipse, use the normal equation for an ellipse        * with an arbitrary center (ellipse_center_x, ellipse_center_y).        */
if|if
condition|(
operator|!
name|antialias
condition|)
block|{
name|ellipse_center_x
operator|=
name|x
operator|+
name|a
expr_stmt|;
name|half_ellipse_width_at_y
operator|=
name|sqrt
argument_list|(
name|a_sqr
operator|-
name|a_sqr
operator|*
name|SQR
argument_list|(
name|cur_y
operator|+
literal|0.5f
operator|-
name|ellipse_center_y
argument_list|)
operator|/
name|b_sqr
argument_list|)
expr_stmt|;
name|x_start
operator|=
name|ROUND
argument_list|(
name|ellipse_center_x
operator|-
name|half_ellipse_width_at_y
argument_list|)
expr_stmt|;
name|x_end
operator|=
name|ROUND
argument_list|(
name|ellipse_center_x
operator|+
name|straight_width
operator|+
name|half_ellipse_width_at_y
argument_list|)
expr_stmt|;
name|gimp_channel_combine_segment
argument_list|(
name|mask
argument_list|,
name|op
argument_list|,
name|x_start
argument_list|,
name|cur_y
argument_list|,
name|x_end
operator|-
name|x_start
argument_list|,
literal|255
argument_list|)
expr_stmt|;
block|}
else|else
comment|/* use antialiasing */
block|{
comment|/* algorithm changed 7-18-04, because the previous one did not            * work well for eccentric ellipses.  The new algorithm            * measures the distance to the ellipse in the X and Y directions,            * and uses trigonometry to approximate the distance to the            * ellipse as the distance to the hypotenuse of a right triangle            * whose legs are the X and Y distances.  (WES)            */
name|gint
name|val
decl_stmt|;
name|gint
name|last_val
decl_stmt|;
name|gint
name|x_start
decl_stmt|;
name|gint
name|cur_x
decl_stmt|;
name|gfloat
name|xj
decl_stmt|,
name|yi
decl_stmt|;
name|gfloat
name|xdist
decl_stmt|,
name|ydist
decl_stmt|;
name|gfloat
name|r
decl_stmt|;
name|gfloat
name|dist
decl_stmt|;
name|x_start
operator|=
name|x
expr_stmt|;
name|yi
operator|=
name|ABS
argument_list|(
name|cur_y
operator|+
literal|0.5
operator|-
name|ellipse_center_y
argument_list|)
expr_stmt|;
name|last_val
operator|=
literal|0
expr_stmt|;
name|ellipse_center_x
operator|=
name|x
operator|+
name|a
expr_stmt|;
for|for
control|(
name|cur_x
operator|=
name|x
init|;
name|cur_x
operator|<
operator|(
name|x
operator|+
name|w
operator|)
condition|;
name|cur_x
operator|++
control|)
block|{
name|xj
operator|=
name|ABS
argument_list|(
name|cur_x
operator|+
literal|0.5
operator|-
name|ellipse_center_x
argument_list|)
expr_stmt|;
if|if
condition|(
name|yi
operator|<
name|b
condition|)
name|xdist
operator|=
name|xj
operator|-
name|a
operator|*
name|sqrt
argument_list|(
literal|1
operator|-
name|yi
operator|*
name|yi
operator|/
name|b_sqr
argument_list|)
expr_stmt|;
else|else
name|xdist
operator|=
literal|100.0
expr_stmt|;
comment|/* anything large will work */
if|if
condition|(
name|xj
operator|<
name|a
condition|)
name|ydist
operator|=
name|yi
operator|-
name|b
operator|*
name|sqrt
argument_list|(
literal|1
operator|-
name|xj
operator|*
name|xj
operator|/
name|a_sqr
argument_list|)
expr_stmt|;
else|else
name|ydist
operator|=
literal|100.0
expr_stmt|;
comment|/* anything large will work */
name|r
operator|=
name|hypot
argument_list|(
name|xdist
argument_list|,
name|ydist
argument_list|)
expr_stmt|;
if|if
condition|(
name|r
operator|<
literal|0.001
condition|)
name|dist
operator|=
literal|0.
expr_stmt|;
else|else
name|dist
operator|=
name|xdist
operator|*
name|ydist
operator|/
name|r
expr_stmt|;
comment|/* trig formula for distance to                                            * hypotenuse                                            */
if|if
condition|(
name|xdist
operator|<
literal|0.0
condition|)
name|dist
operator|*=
operator|-
literal|1
expr_stmt|;
if|if
condition|(
name|dist
operator|<
operator|-
literal|0.5
condition|)
name|val
operator|=
literal|255
expr_stmt|;
elseif|else
if|if
condition|(
name|dist
operator|<
literal|0.5
condition|)
name|val
operator|=
call|(
name|gint
call|)
argument_list|(
literal|255
operator|*
operator|(
literal|1
operator|-
operator|(
name|dist
operator|+
literal|0.5
operator|)
operator|)
argument_list|)
expr_stmt|;
else|else
name|val
operator|=
literal|0
expr_stmt|;
name|gimp_channel_combine_segment
argument_list|(
name|mask
argument_list|,
name|op
argument_list|,
name|x_start
argument_list|,
name|cur_y
argument_list|,
name|cur_x
operator|-
name|x_start
argument_list|,
name|last_val
argument_list|)
expr_stmt|;
if|if
condition|(
name|last_val
operator|!=
name|val
condition|)
block|{
name|x_start
operator|=
name|cur_x
expr_stmt|;
name|last_val
operator|=
name|val
expr_stmt|;
comment|/*  because we are symetric accross the y axis we can                    *  skip ahead a bit if we are inside. Do this if we                    *  have reached a value of 255 OR if we have passed                    *  the center of the leftmost ellipse.                    */
if|if
condition|(
operator|(
name|val
operator|==
literal|255
operator|||
name|cur_x
operator|>=
name|x
operator|+
name|a
operator|)
operator|&&
name|cur_x
operator|<
name|x
operator|+
name|w
operator|/
literal|2
condition|)
block|{
name|last_val
operator|=
name|val
operator|=
literal|255
expr_stmt|;
name|cur_x
operator|=
operator|(
name|ellipse_center_x
operator|+
operator|(
name|ellipse_center_x
operator|-
name|cur_x
operator|)
operator|-
literal|1
operator|+
name|floor
argument_list|(
name|straight_width
argument_list|)
operator|)
expr_stmt|;
block|}
block|}
comment|/* Time to change center? */
if|if
condition|(
name|cur_x
operator|>=
name|x
operator|+
name|w
operator|/
literal|2
condition|)
block|{
name|ellipse_center_x
operator|=
name|x
operator|+
name|a
operator|+
name|straight_width
expr_stmt|;
block|}
block|}
name|gimp_channel_combine_segment
argument_list|(
name|mask
argument_list|,
name|op
argument_list|,
name|x_start
argument_list|,
name|cur_y
argument_list|,
name|cur_x
operator|-
name|x_start
argument_list|,
name|last_val
argument_list|)
expr_stmt|;
block|}
block|}
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
name|GIMP_ITEM
argument_list|(
name|mask
argument_list|)
operator|->
name|width
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
name|GIMP_ITEM
argument_list|(
name|mask
argument_list|)
operator|->
name|height
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
name|GIMP_ITEM
argument_list|(
name|mask
argument_list|)
operator|->
name|width
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
name|GIMP_ITEM
argument_list|(
name|mask
argument_list|)
operator|->
name|height
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
specifier|static
name|void
DECL|function|gimp_channel_combine_sub_region_add (gpointer unused,PixelRegion * srcPR,PixelRegion * destPR)
name|gimp_channel_combine_sub_region_add
parameter_list|(
name|gpointer
name|unused
parameter_list|,
name|PixelRegion
modifier|*
name|srcPR
parameter_list|,
name|PixelRegion
modifier|*
name|destPR
parameter_list|)
block|{
name|guchar
modifier|*
name|src
decl_stmt|,
modifier|*
name|dest
decl_stmt|;
name|gint
name|x
decl_stmt|,
name|y
decl_stmt|,
name|val
decl_stmt|;
name|src
operator|=
name|srcPR
operator|->
name|data
expr_stmt|;
name|dest
operator|=
name|destPR
operator|->
name|data
expr_stmt|;
for|for
control|(
name|y
operator|=
literal|0
init|;
name|y
operator|<
name|srcPR
operator|->
name|h
condition|;
name|y
operator|++
control|)
block|{
for|for
control|(
name|x
operator|=
literal|0
init|;
name|x
operator|<
name|srcPR
operator|->
name|w
condition|;
name|x
operator|++
control|)
block|{
name|val
operator|=
name|dest
index|[
name|x
index|]
operator|+
name|src
index|[
name|x
index|]
expr_stmt|;
if|if
condition|(
name|val
operator|>
literal|255
condition|)
name|dest
index|[
name|x
index|]
operator|=
literal|255
expr_stmt|;
else|else
name|dest
index|[
name|x
index|]
operator|=
name|val
expr_stmt|;
block|}
name|src
operator|+=
name|srcPR
operator|->
name|rowstride
expr_stmt|;
name|dest
operator|+=
name|destPR
operator|->
name|rowstride
expr_stmt|;
block|}
block|}
end_function

begin_function
specifier|static
name|void
DECL|function|gimp_channel_combine_sub_region_sub (gpointer unused,PixelRegion * srcPR,PixelRegion * destPR)
name|gimp_channel_combine_sub_region_sub
parameter_list|(
name|gpointer
name|unused
parameter_list|,
name|PixelRegion
modifier|*
name|srcPR
parameter_list|,
name|PixelRegion
modifier|*
name|destPR
parameter_list|)
block|{
name|guchar
modifier|*
name|src
decl_stmt|,
modifier|*
name|dest
decl_stmt|;
name|gint
name|x
decl_stmt|,
name|y
decl_stmt|;
name|src
operator|=
name|srcPR
operator|->
name|data
expr_stmt|;
name|dest
operator|=
name|destPR
operator|->
name|data
expr_stmt|;
for|for
control|(
name|y
operator|=
literal|0
init|;
name|y
operator|<
name|srcPR
operator|->
name|h
condition|;
name|y
operator|++
control|)
block|{
for|for
control|(
name|x
operator|=
literal|0
init|;
name|x
operator|<
name|srcPR
operator|->
name|w
condition|;
name|x
operator|++
control|)
block|{
if|if
condition|(
name|src
index|[
name|x
index|]
operator|>
name|dest
index|[
name|x
index|]
condition|)
name|dest
index|[
name|x
index|]
operator|=
literal|0
expr_stmt|;
else|else
name|dest
index|[
name|x
index|]
operator|-=
name|src
index|[
name|x
index|]
expr_stmt|;
block|}
name|src
operator|+=
name|srcPR
operator|->
name|rowstride
expr_stmt|;
name|dest
operator|+=
name|destPR
operator|->
name|rowstride
expr_stmt|;
block|}
block|}
end_function

begin_function
specifier|static
name|void
DECL|function|gimp_channel_combine_sub_region_intersect (gpointer unused,PixelRegion * srcPR,PixelRegion * destPR)
name|gimp_channel_combine_sub_region_intersect
parameter_list|(
name|gpointer
name|unused
parameter_list|,
name|PixelRegion
modifier|*
name|srcPR
parameter_list|,
name|PixelRegion
modifier|*
name|destPR
parameter_list|)
block|{
name|guchar
modifier|*
name|src
decl_stmt|,
modifier|*
name|dest
decl_stmt|;
name|gint
name|x
decl_stmt|,
name|y
decl_stmt|;
name|src
operator|=
name|srcPR
operator|->
name|data
expr_stmt|;
name|dest
operator|=
name|destPR
operator|->
name|data
expr_stmt|;
for|for
control|(
name|y
operator|=
literal|0
init|;
name|y
operator|<
name|srcPR
operator|->
name|h
condition|;
name|y
operator|++
control|)
block|{
for|for
control|(
name|x
operator|=
literal|0
init|;
name|x
operator|<
name|srcPR
operator|->
name|w
condition|;
name|x
operator|++
control|)
block|{
name|dest
index|[
name|x
index|]
operator|=
name|MIN
argument_list|(
name|dest
index|[
name|x
index|]
argument_list|,
name|src
index|[
name|x
index|]
argument_list|)
expr_stmt|;
block|}
name|src
operator|+=
name|srcPR
operator|->
name|rowstride
expr_stmt|;
name|dest
operator|+=
name|destPR
operator|->
name|rowstride
expr_stmt|;
block|}
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
name|PixelRegion
name|srcPR
decl_stmt|,
name|destPR
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
name|GIMP_IS_CHANNEL
argument_list|(
name|add_on
argument_list|)
argument_list|)
expr_stmt|;
if|if
condition|(
operator|!
name|gimp_rectangle_intersect
argument_list|(
name|off_x
argument_list|,
name|off_y
argument_list|,
name|GIMP_ITEM
argument_list|(
name|add_on
argument_list|)
operator|->
name|width
argument_list|,
name|GIMP_ITEM
argument_list|(
name|add_on
argument_list|)
operator|->
name|height
argument_list|,
literal|0
argument_list|,
literal|0
argument_list|,
name|GIMP_ITEM
argument_list|(
name|mask
argument_list|)
operator|->
name|width
argument_list|,
name|GIMP_ITEM
argument_list|(
name|mask
argument_list|)
operator|->
name|height
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
condition|)
return|return;
name|pixel_region_init
argument_list|(
operator|&
name|srcPR
argument_list|,
name|GIMP_DRAWABLE
argument_list|(
name|add_on
argument_list|)
operator|->
name|tiles
argument_list|,
name|x
operator|-
name|off_x
argument_list|,
name|y
operator|-
name|off_y
argument_list|,
name|w
argument_list|,
name|h
argument_list|,
name|FALSE
argument_list|)
expr_stmt|;
name|pixel_region_init
argument_list|(
operator|&
name|destPR
argument_list|,
name|GIMP_DRAWABLE
argument_list|(
name|mask
argument_list|)
operator|->
name|tiles
argument_list|,
name|x
argument_list|,
name|y
argument_list|,
name|w
argument_list|,
name|h
argument_list|,
name|TRUE
argument_list|)
expr_stmt|;
switch|switch
condition|(
name|op
condition|)
block|{
case|case
name|GIMP_CHANNEL_OP_ADD
case|:
case|case
name|GIMP_CHANNEL_OP_REPLACE
case|:
name|pixel_regions_process_parallel
argument_list|(
operator|(
name|PixelProcessorFunc
operator|)
name|gimp_channel_combine_sub_region_add
argument_list|,
name|NULL
argument_list|,
literal|2
argument_list|,
operator|&
name|srcPR
argument_list|,
operator|&
name|destPR
argument_list|)
expr_stmt|;
break|break;
case|case
name|GIMP_CHANNEL_OP_SUBTRACT
case|:
name|pixel_regions_process_parallel
argument_list|(
operator|(
name|PixelProcessorFunc
operator|)
name|gimp_channel_combine_sub_region_sub
argument_list|,
name|NULL
argument_list|,
literal|2
argument_list|,
operator|&
name|srcPR
argument_list|,
operator|&
name|destPR
argument_list|)
expr_stmt|;
break|break;
case|case
name|GIMP_CHANNEL_OP_INTERSECT
case|:
name|pixel_regions_process_parallel
argument_list|(
operator|(
name|PixelProcessorFunc
operator|)
name|gimp_channel_combine_sub_region_intersect
argument_list|,
name|NULL
argument_list|,
literal|2
argument_list|,
operator|&
name|srcPR
argument_list|,
operator|&
name|destPR
argument_list|)
expr_stmt|;
break|break;
default|default:
name|g_warning
argument_list|(
literal|"%s: unknown operation type"
argument_list|,
name|G_STRFUNC
argument_list|)
expr_stmt|;
break|break;
block|}
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

