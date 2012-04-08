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
file|<string.h>
end_include

begin_include
include|#
directive|include
file|<gegl.h>
end_include

begin_include
include|#
directive|include
file|"vectors-types.h"
end_include

begin_include
include|#
directive|include
file|"libgimpmath/gimpmath.h"
end_include

begin_include
include|#
directive|include
file|"base/temp-buf.h"
end_include

begin_include
include|#
directive|include
file|"core/gimpimage.h"
end_include

begin_include
include|#
directive|include
file|"gimpstroke.h"
end_include

begin_include
include|#
directive|include
file|"gimpvectors.h"
end_include

begin_include
include|#
directive|include
file|"gimpvectors-preview.h"
end_include

begin_comment
comment|/*  public functions  */
end_comment

begin_function
name|TempBuf
modifier|*
DECL|function|gimp_vectors_get_new_preview (GimpViewable * viewable,GimpContext * context,gint width,gint height)
name|gimp_vectors_get_new_preview
parameter_list|(
name|GimpViewable
modifier|*
name|viewable
parameter_list|,
name|GimpContext
modifier|*
name|context
parameter_list|,
name|gint
name|width
parameter_list|,
name|gint
name|height
parameter_list|)
block|{
name|GimpVectors
modifier|*
name|vectors
decl_stmt|;
name|GimpItem
modifier|*
name|item
decl_stmt|;
name|GimpStroke
modifier|*
name|cur_stroke
decl_stmt|;
name|gdouble
name|xscale
decl_stmt|,
name|yscale
decl_stmt|;
name|guchar
modifier|*
name|data
decl_stmt|;
name|TempBuf
modifier|*
name|temp_buf
decl_stmt|;
name|vectors
operator|=
name|GIMP_VECTORS
argument_list|(
name|viewable
argument_list|)
expr_stmt|;
name|item
operator|=
name|GIMP_ITEM
argument_list|(
name|viewable
argument_list|)
expr_stmt|;
name|xscale
operator|=
operator|(
operator|(
name|gdouble
operator|)
name|width
operator|)
operator|/
name|gimp_image_get_width
argument_list|(
name|gimp_item_get_image
argument_list|(
name|item
argument_list|)
argument_list|)
expr_stmt|;
name|yscale
operator|=
operator|(
operator|(
name|gdouble
operator|)
name|height
operator|)
operator|/
name|gimp_image_get_height
argument_list|(
name|gimp_item_get_image
argument_list|(
name|item
argument_list|)
argument_list|)
expr_stmt|;
name|temp_buf
operator|=
name|temp_buf_new
argument_list|(
name|width
argument_list|,
name|height
argument_list|,
name|babl_format
argument_list|(
literal|"Y' u8"
argument_list|)
argument_list|)
expr_stmt|;
name|data
operator|=
name|temp_buf_get_data
argument_list|(
name|temp_buf
argument_list|)
expr_stmt|;
name|memset
argument_list|(
name|data
argument_list|,
literal|255
argument_list|,
name|width
operator|*
name|height
argument_list|)
expr_stmt|;
for|for
control|(
name|cur_stroke
operator|=
name|gimp_vectors_stroke_get_next
argument_list|(
name|vectors
argument_list|,
name|NULL
argument_list|)
init|;
name|cur_stroke
condition|;
name|cur_stroke
operator|=
name|gimp_vectors_stroke_get_next
argument_list|(
name|vectors
argument_list|,
name|cur_stroke
argument_list|)
control|)
block|{
name|GArray
modifier|*
name|coords
decl_stmt|;
name|gboolean
name|closed
decl_stmt|;
name|gint
name|i
decl_stmt|;
name|coords
operator|=
name|gimp_stroke_interpolate
argument_list|(
name|cur_stroke
argument_list|,
literal|0.5
argument_list|,
operator|&
name|closed
argument_list|)
expr_stmt|;
if|if
condition|(
name|coords
condition|)
block|{
for|for
control|(
name|i
operator|=
literal|0
init|;
name|i
operator|<
name|coords
operator|->
name|len
condition|;
name|i
operator|++
control|)
block|{
name|GimpCoords
name|point
decl_stmt|;
name|gint
name|x
decl_stmt|,
name|y
decl_stmt|;
name|point
operator|=
name|g_array_index
argument_list|(
name|coords
argument_list|,
name|GimpCoords
argument_list|,
name|i
argument_list|)
expr_stmt|;
name|x
operator|=
name|ROUND
argument_list|(
name|point
operator|.
name|x
operator|*
name|xscale
argument_list|)
expr_stmt|;
name|y
operator|=
name|ROUND
argument_list|(
name|point
operator|.
name|y
operator|*
name|yscale
argument_list|)
expr_stmt|;
if|if
condition|(
name|x
operator|>=
literal|0
operator|&&
name|y
operator|>=
literal|0
operator|&&
name|x
operator|<
name|width
operator|&&
name|y
operator|<
name|height
condition|)
name|data
index|[
name|y
operator|*
name|width
operator|+
name|x
index|]
operator|=
literal|0
expr_stmt|;
block|}
name|g_array_free
argument_list|(
name|coords
argument_list|,
name|TRUE
argument_list|)
expr_stmt|;
block|}
block|}
return|return
name|temp_buf
return|;
block|}
end_function

end_unit

