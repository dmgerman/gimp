begin_unit|revision:0.9.5;language:C;cregit-version:0.0.1
begin_comment
comment|/* The GIMP -- an image manipulation program  * Copyright (C) 1995 Spencer Kimball and Peter Mattis  *  * This program is free software; you can redistribute it and/or modify  * it under the terms of the GNU General Public License as published by  * the Free Software Foundation; either version 2 of the License, or  * (at your option) any later version.  *  * This program is distributed in the hope that it will be useful,  * but WITHOUT ANY WARRANTY; without even the implied warranty of  * MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the  * GNU General Public License for more details.  *  * You should have received a copy of the GNU General Public License  * along with this program; if not, write to the Free Software  * Foundation, Inc., 59 Temple Place - Suite 330, Boston, MA 02111-1307, USA.  */
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
file|"core-types.h"
end_include

begin_include
include|#
directive|include
file|"gimp-utils.h"
end_include

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

end_unit

