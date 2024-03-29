begin_unit|revision:0.9.5;language:C;cregit-version:0.0.1
begin_comment
comment|/* LIBGIMP - The GIMP Library  * Copyright (C) 1995-1997 Spencer Kimball and Peter Mattis  *  * gimprectangle.c  *  * This library is free software: you can redistribute it and/or  * modify it under the terms of the GNU Lesser General Public  * License as published by the Free Software Foundation; either  * version 3 of the License, or (at your option) any later version.  *  * This library is distributed in the hope that it will be useful,  * but WITHOUT ANY WARRANTY; without even the implied warranty of  * MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the GNU  * Lesser General Public License for more details.  *  * You should have received a copy of the GNU Lesser General Public  * License along with this library.  If not, see  *<https://www.gnu.org/licenses/>.  */
end_comment

begin_include
include|#
directive|include
file|"config.h"
end_include

begin_include
include|#
directive|include
file|<glib.h>
end_include

begin_include
include|#
directive|include
file|"gimprectangle.h"
end_include

begin_comment
comment|/**  * SECTION: gimprectangle  * @title: gimprectangle  * @short_description: Utility functions dealing with rectangle extents.  *  * Utility functions dealing with rectangle extents.  **/
end_comment

begin_comment
comment|/**  * gimp_rectangle_intersect:  * @x1:          origin of first rectangle  * @y1:          origin of first rectangle  * @width1:      width of first rectangle  * @height1:     height of first rectangle  * @x2:          origin of second rectangle  * @y2:          origin of second rectangle  * @width2:      width of second rectangle  * @height2:     height of second rectangle  * @dest_x:      return location for origin of intersection (may be %NULL)  * @dest_y:      return location for origin of intersection (may be %NULL)  * @dest_width:  return location for width of intersection (may be %NULL)  * @dest_height: return location for height of intersection (may be %NULL)  *  * Calculates the intersection of two rectangles.  *  * Returns: %TRUE if the intersection is non-empty, %FALSE otherwise  *  * Since: 2.4  **/
end_comment

begin_function
name|gboolean
DECL|function|gimp_rectangle_intersect (gint x1,gint y1,gint width1,gint height1,gint x2,gint y2,gint width2,gint height2,gint * dest_x,gint * dest_y,gint * dest_width,gint * dest_height)
name|gimp_rectangle_intersect
parameter_list|(
name|gint
name|x1
parameter_list|,
name|gint
name|y1
parameter_list|,
name|gint
name|width1
parameter_list|,
name|gint
name|height1
parameter_list|,
name|gint
name|x2
parameter_list|,
name|gint
name|y2
parameter_list|,
name|gint
name|width2
parameter_list|,
name|gint
name|height2
parameter_list|,
name|gint
modifier|*
name|dest_x
parameter_list|,
name|gint
modifier|*
name|dest_y
parameter_list|,
name|gint
modifier|*
name|dest_width
parameter_list|,
name|gint
modifier|*
name|dest_height
parameter_list|)
block|{
name|gint
name|d_x
decl_stmt|,
name|d_y
decl_stmt|;
name|gint
name|d_w
decl_stmt|,
name|d_h
decl_stmt|;
name|d_x
operator|=
name|MAX
argument_list|(
name|x1
argument_list|,
name|x2
argument_list|)
expr_stmt|;
name|d_y
operator|=
name|MAX
argument_list|(
name|y1
argument_list|,
name|y2
argument_list|)
expr_stmt|;
name|d_w
operator|=
name|MIN
argument_list|(
name|x1
operator|+
name|width1
argument_list|,
name|x2
operator|+
name|width2
argument_list|)
operator|-
name|d_x
expr_stmt|;
name|d_h
operator|=
name|MIN
argument_list|(
name|y1
operator|+
name|height1
argument_list|,
name|y2
operator|+
name|height2
argument_list|)
operator|-
name|d_y
expr_stmt|;
if|if
condition|(
name|dest_x
condition|)
operator|*
name|dest_x
operator|=
name|d_x
expr_stmt|;
if|if
condition|(
name|dest_y
condition|)
operator|*
name|dest_y
operator|=
name|d_y
expr_stmt|;
if|if
condition|(
name|dest_width
condition|)
operator|*
name|dest_width
operator|=
name|d_w
expr_stmt|;
if|if
condition|(
name|dest_height
condition|)
operator|*
name|dest_height
operator|=
name|d_h
expr_stmt|;
return|return
operator|(
name|d_w
operator|>
literal|0
operator|&&
name|d_h
operator|>
literal|0
operator|)
return|;
block|}
end_function

begin_comment
comment|/**  * gimp_rectangle_union:  * @x1:          origin of first rectangle  * @y1:          origin of first rectangle  * @width1:      width of first rectangle  * @height1:     height of first rectangle  * @x2:          origin of second rectangle  * @y2:          origin of second rectangle  * @width2:      width of second rectangle  * @height2:     height of second rectangle  * @dest_x:      return location for origin of union (may be %NULL)  * @dest_y:      return location for origin of union (may be %NULL)  * @dest_width:  return location for width of union (may be %NULL)  * @dest_height: return location for height of union (may be %NULL)  *  * Calculates the union of two rectangles.  *  * Since: 2.8  **/
end_comment

begin_function
name|void
DECL|function|gimp_rectangle_union (gint x1,gint y1,gint width1,gint height1,gint x2,gint y2,gint width2,gint height2,gint * dest_x,gint * dest_y,gint * dest_width,gint * dest_height)
name|gimp_rectangle_union
parameter_list|(
name|gint
name|x1
parameter_list|,
name|gint
name|y1
parameter_list|,
name|gint
name|width1
parameter_list|,
name|gint
name|height1
parameter_list|,
name|gint
name|x2
parameter_list|,
name|gint
name|y2
parameter_list|,
name|gint
name|width2
parameter_list|,
name|gint
name|height2
parameter_list|,
name|gint
modifier|*
name|dest_x
parameter_list|,
name|gint
modifier|*
name|dest_y
parameter_list|,
name|gint
modifier|*
name|dest_width
parameter_list|,
name|gint
modifier|*
name|dest_height
parameter_list|)
block|{
name|gint
name|d_x
decl_stmt|,
name|d_y
decl_stmt|;
name|gint
name|d_w
decl_stmt|,
name|d_h
decl_stmt|;
name|d_x
operator|=
name|MIN
argument_list|(
name|x1
argument_list|,
name|x2
argument_list|)
expr_stmt|;
name|d_y
operator|=
name|MIN
argument_list|(
name|y1
argument_list|,
name|y2
argument_list|)
expr_stmt|;
name|d_w
operator|=
name|MAX
argument_list|(
name|x1
operator|+
name|width1
argument_list|,
name|x2
operator|+
name|width2
argument_list|)
operator|-
name|d_x
expr_stmt|;
name|d_h
operator|=
name|MAX
argument_list|(
name|y1
operator|+
name|height1
argument_list|,
name|y2
operator|+
name|height2
argument_list|)
operator|-
name|d_y
expr_stmt|;
if|if
condition|(
name|dest_x
condition|)
operator|*
name|dest_x
operator|=
name|d_x
expr_stmt|;
if|if
condition|(
name|dest_y
condition|)
operator|*
name|dest_y
operator|=
name|d_y
expr_stmt|;
if|if
condition|(
name|dest_width
condition|)
operator|*
name|dest_width
operator|=
name|d_w
expr_stmt|;
if|if
condition|(
name|dest_height
condition|)
operator|*
name|dest_height
operator|=
name|d_h
expr_stmt|;
block|}
end_function

end_unit

