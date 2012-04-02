begin_unit|revision:0.9.5;language:C;cregit-version:0.0.1
begin_comment
comment|/* GIMP - The GNU Image Manipulation Program  * Copyright (C) 1995 Spencer Kimball and Peter Mattis  *  * gimp-gegl-tile-compat.h  * Copyright (C) 2012 Michael Natterer<mitch@gimp.org>  *  * This program is free software: you can redistribute it and/or modify  * it under the terms of the GNU General Public License as published by  * the Free Software Foundation; either version 3 of the License, or  * (at your option) any later version.  *  * This program is distributed in the hope that it will be useful,  * but WITHOUT ANY WARRANTY; without even the implied warranty of  * MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the  * GNU General Public License for more details.  *  * You should have received a copy of the GNU General Public License  * along with this program.  If not, see<http://www.gnu.org/licenses/>.  */
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
file|"gimp-gegl-types.h"
end_include

begin_include
include|#
directive|include
file|"gimp-gegl-tile-compat.h"
end_include

begin_function
name|gint
DECL|function|gimp_gegl_buffer_get_n_tile_rows (GeglBuffer * buffer,gint tile_height)
name|gimp_gegl_buffer_get_n_tile_rows
parameter_list|(
name|GeglBuffer
modifier|*
name|buffer
parameter_list|,
name|gint
name|tile_height
parameter_list|)
block|{
return|return
operator|(
name|gegl_buffer_get_height
argument_list|(
name|buffer
argument_list|)
operator|+
name|tile_height
operator|-
literal|1
operator|)
operator|/
name|tile_height
return|;
block|}
end_function

begin_function
name|gint
DECL|function|gimp_gegl_buffer_get_n_tile_cols (GeglBuffer * buffer,gint tile_width)
name|gimp_gegl_buffer_get_n_tile_cols
parameter_list|(
name|GeglBuffer
modifier|*
name|buffer
parameter_list|,
name|gint
name|tile_width
parameter_list|)
block|{
return|return
operator|(
name|gegl_buffer_get_width
argument_list|(
name|buffer
argument_list|)
operator|+
name|tile_width
operator|-
literal|1
operator|)
operator|/
name|tile_width
return|;
block|}
end_function

begin_function
name|gboolean
DECL|function|gimp_gegl_buffer_get_tile_rect (GeglBuffer * buffer,gint tile_width,gint tile_height,gint tile_num,GeglRectangle * rect)
name|gimp_gegl_buffer_get_tile_rect
parameter_list|(
name|GeglBuffer
modifier|*
name|buffer
parameter_list|,
name|gint
name|tile_width
parameter_list|,
name|gint
name|tile_height
parameter_list|,
name|gint
name|tile_num
parameter_list|,
name|GeglRectangle
modifier|*
name|rect
parameter_list|)
block|{
name|gint
name|n_tile_rows
decl_stmt|;
name|gint
name|n_tile_columns
decl_stmt|;
name|gint
name|tile_row
decl_stmt|;
name|gint
name|tile_column
decl_stmt|;
name|n_tile_rows
operator|=
name|gimp_gegl_buffer_get_n_tile_rows
argument_list|(
name|buffer
argument_list|,
name|tile_height
argument_list|)
expr_stmt|;
name|n_tile_columns
operator|=
name|gimp_gegl_buffer_get_n_tile_cols
argument_list|(
name|buffer
argument_list|,
name|tile_width
argument_list|)
expr_stmt|;
if|if
condition|(
name|tile_num
operator|>
name|n_tile_rows
operator|*
name|n_tile_columns
operator|-
literal|1
condition|)
return|return
name|FALSE
return|;
name|tile_row
operator|=
name|tile_num
operator|/
name|n_tile_columns
expr_stmt|;
name|tile_column
operator|=
name|tile_num
operator|%
name|n_tile_columns
expr_stmt|;
name|rect
operator|->
name|x
operator|=
name|tile_column
operator|*
name|tile_width
expr_stmt|;
name|rect
operator|->
name|y
operator|=
name|tile_row
operator|*
name|tile_height
expr_stmt|;
if|if
condition|(
name|tile_column
operator|==
name|n_tile_columns
operator|-
literal|1
condition|)
name|rect
operator|->
name|width
operator|=
name|gegl_buffer_get_width
argument_list|(
name|buffer
argument_list|)
operator|-
name|rect
operator|->
name|x
expr_stmt|;
else|else
name|rect
operator|->
name|width
operator|=
name|tile_width
expr_stmt|;
if|if
condition|(
name|tile_row
operator|==
name|n_tile_rows
operator|-
literal|1
condition|)
name|rect
operator|->
name|height
operator|=
name|gegl_buffer_get_height
argument_list|(
name|buffer
argument_list|)
operator|-
name|rect
operator|->
name|y
expr_stmt|;
else|else
name|rect
operator|->
name|height
operator|=
name|tile_height
expr_stmt|;
return|return
name|TRUE
return|;
block|}
end_function

end_unit

