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
file|"gimp.h"
end_include

begin_include
include|#
directive|include
file|"gimpimage.h"
end_include

begin_include
include|#
directive|include
file|"gimppickable.h"
end_include

begin_include
include|#
directive|include
file|"gimppickable-auto-shrink.h"
end_include

begin_typedef
typedef|typedef
enum|enum
DECL|enum|__anon298caa6c0103
block|{
DECL|enumerator|AUTO_SHRINK_NOTHING
name|AUTO_SHRINK_NOTHING
init|=
literal|0
block|,
DECL|enumerator|AUTO_SHRINK_ALPHA
name|AUTO_SHRINK_ALPHA
init|=
literal|1
block|,
DECL|enumerator|AUTO_SHRINK_COLOR
name|AUTO_SHRINK_COLOR
init|=
literal|2
DECL|typedef|AutoShrinkType
block|}
name|AutoShrinkType
typedef|;
end_typedef

begin_typedef
DECL|typedef|ColorsEqualFunc
typedef|typedef
name|gboolean
function_decl|(
modifier|*
name|ColorsEqualFunc
function_decl|)
parameter_list|(
name|guchar
modifier|*
name|col1
parameter_list|,
name|guchar
modifier|*
name|col2
parameter_list|)
function_decl|;
end_typedef

begin_comment
comment|/*  local function prototypes  */
end_comment

begin_function_decl
specifier|static
name|AutoShrinkType
name|gimp_pickable_guess_bgcolor
parameter_list|(
name|GimpPickable
modifier|*
name|pickable
parameter_list|,
name|guchar
modifier|*
name|color
parameter_list|,
name|gint
name|x1
parameter_list|,
name|gint
name|x2
parameter_list|,
name|gint
name|y1
parameter_list|,
name|gint
name|y2
parameter_list|)
function_decl|;
end_function_decl

begin_function_decl
specifier|static
name|gboolean
name|gimp_pickable_colors_equal
parameter_list|(
name|guchar
modifier|*
name|col1
parameter_list|,
name|guchar
modifier|*
name|col2
parameter_list|)
function_decl|;
end_function_decl

begin_function_decl
specifier|static
name|gboolean
name|gimp_pickable_colors_alpha
parameter_list|(
name|guchar
modifier|*
name|col1
parameter_list|,
name|guchar
modifier|*
name|col2
parameter_list|)
function_decl|;
end_function_decl

begin_comment
comment|/*  public functions  */
end_comment

begin_function
name|GimpAutoShrink
DECL|function|gimp_pickable_auto_shrink (GimpPickable * pickable,gint start_x1,gint start_y1,gint start_x2,gint start_y2,gint * shrunk_x1,gint * shrunk_y1,gint * shrunk_x2,gint * shrunk_y2)
name|gimp_pickable_auto_shrink
parameter_list|(
name|GimpPickable
modifier|*
name|pickable
parameter_list|,
name|gint
name|start_x1
parameter_list|,
name|gint
name|start_y1
parameter_list|,
name|gint
name|start_x2
parameter_list|,
name|gint
name|start_y2
parameter_list|,
name|gint
modifier|*
name|shrunk_x1
parameter_list|,
name|gint
modifier|*
name|shrunk_y1
parameter_list|,
name|gint
modifier|*
name|shrunk_x2
parameter_list|,
name|gint
modifier|*
name|shrunk_y2
parameter_list|)
block|{
name|GeglBuffer
modifier|*
name|buffer
decl_stmt|;
name|GeglRectangle
name|rect
decl_stmt|;
name|ColorsEqualFunc
name|colors_equal_func
decl_stmt|;
name|guchar
name|bgcolor
index|[
name|MAX_CHANNELS
index|]
init|=
block|{
literal|0
block|,
literal|0
block|,
literal|0
block|,
literal|0
block|}
decl_stmt|;
name|guchar
modifier|*
name|buf
init|=
name|NULL
decl_stmt|;
name|gint
name|x1
decl_stmt|,
name|y1
decl_stmt|,
name|x2
decl_stmt|,
name|y2
decl_stmt|;
name|gint
name|width
decl_stmt|,
name|height
decl_stmt|;
specifier|const
name|Babl
modifier|*
name|format
decl_stmt|;
name|gint
name|x
decl_stmt|,
name|y
decl_stmt|,
name|abort
decl_stmt|;
name|GimpAutoShrink
name|retval
init|=
name|GIMP_AUTO_SHRINK_UNSHRINKABLE
decl_stmt|;
name|g_return_val_if_fail
argument_list|(
name|GIMP_IS_PICKABLE
argument_list|(
name|pickable
argument_list|)
argument_list|,
name|FALSE
argument_list|)
expr_stmt|;
name|g_return_val_if_fail
argument_list|(
name|shrunk_x1
operator|!=
name|NULL
argument_list|,
name|FALSE
argument_list|)
expr_stmt|;
name|g_return_val_if_fail
argument_list|(
name|shrunk_y1
operator|!=
name|NULL
argument_list|,
name|FALSE
argument_list|)
expr_stmt|;
name|g_return_val_if_fail
argument_list|(
name|shrunk_x2
operator|!=
name|NULL
argument_list|,
name|FALSE
argument_list|)
expr_stmt|;
name|g_return_val_if_fail
argument_list|(
name|shrunk_y2
operator|!=
name|NULL
argument_list|,
name|FALSE
argument_list|)
expr_stmt|;
name|gimp_set_busy
argument_list|(
name|gimp_pickable_get_image
argument_list|(
name|pickable
argument_list|)
operator|->
name|gimp
argument_list|)
expr_stmt|;
comment|/* You should always keep in mind that x2 and y2 are the NOT the    * coordinates of the bottomright corner of the area to be    * cropped. They point at the pixel located one to the right and one    * to the bottom.    */
name|gimp_pickable_flush
argument_list|(
name|pickable
argument_list|)
expr_stmt|;
name|buffer
operator|=
name|gimp_pickable_get_buffer
argument_list|(
name|pickable
argument_list|)
expr_stmt|;
name|x1
operator|=
name|MAX
argument_list|(
name|start_x1
argument_list|,
literal|0
argument_list|)
expr_stmt|;
name|y1
operator|=
name|MAX
argument_list|(
name|start_y1
argument_list|,
literal|0
argument_list|)
expr_stmt|;
name|x2
operator|=
name|MIN
argument_list|(
name|start_x2
argument_list|,
name|gegl_buffer_get_width
argument_list|(
name|buffer
argument_list|)
argument_list|)
expr_stmt|;
name|y2
operator|=
name|MIN
argument_list|(
name|start_y2
argument_list|,
name|gegl_buffer_get_height
argument_list|(
name|buffer
argument_list|)
argument_list|)
expr_stmt|;
comment|/* By default, return the start values */
operator|*
name|shrunk_x1
operator|=
name|x1
expr_stmt|;
operator|*
name|shrunk_y1
operator|=
name|y1
expr_stmt|;
operator|*
name|shrunk_x2
operator|=
name|x2
expr_stmt|;
operator|*
name|shrunk_y2
operator|=
name|y2
expr_stmt|;
name|format
operator|=
name|babl_format
argument_list|(
literal|"R'G'B'A u8"
argument_list|)
expr_stmt|;
switch|switch
condition|(
name|gimp_pickable_guess_bgcolor
argument_list|(
name|pickable
argument_list|,
name|bgcolor
argument_list|,
name|x1
argument_list|,
name|x2
operator|-
literal|1
argument_list|,
name|y1
argument_list|,
name|y2
operator|-
literal|1
argument_list|)
condition|)
block|{
case|case
name|AUTO_SHRINK_ALPHA
case|:
name|colors_equal_func
operator|=
name|gimp_pickable_colors_alpha
expr_stmt|;
break|break;
case|case
name|AUTO_SHRINK_COLOR
case|:
name|colors_equal_func
operator|=
name|gimp_pickable_colors_equal
expr_stmt|;
break|break;
default|default:
goto|goto
name|FINISH
goto|;
break|break;
block|}
name|width
operator|=
name|x2
operator|-
name|x1
expr_stmt|;
name|height
operator|=
name|y2
operator|-
name|y1
expr_stmt|;
comment|/* The following could be optimized further by processing    * the smaller side first instead of defaulting to width    --Sven    */
name|buf
operator|=
name|g_malloc
argument_list|(
name|MAX
argument_list|(
name|width
argument_list|,
name|height
argument_list|)
operator|*
literal|4
argument_list|)
expr_stmt|;
comment|/* Check how many of the top lines are uniform/transparent. */
name|rect
operator|.
name|x
operator|=
name|x1
expr_stmt|;
name|rect
operator|.
name|y
operator|=
literal|0
expr_stmt|;
name|rect
operator|.
name|width
operator|=
name|width
expr_stmt|;
name|rect
operator|.
name|height
operator|=
literal|1
expr_stmt|;
name|abort
operator|=
name|FALSE
expr_stmt|;
for|for
control|(
name|y
operator|=
name|y1
init|;
name|y
operator|<
name|y2
operator|&&
operator|!
name|abort
condition|;
name|y
operator|++
control|)
block|{
name|rect
operator|.
name|y
operator|=
name|y
expr_stmt|;
name|gegl_buffer_get
argument_list|(
name|buffer
argument_list|,
operator|&
name|rect
argument_list|,
literal|1.0
argument_list|,
name|format
argument_list|,
name|buf
argument_list|,
name|GEGL_AUTO_ROWSTRIDE
argument_list|,
name|GEGL_ABYSS_NONE
argument_list|)
expr_stmt|;
for|for
control|(
name|x
operator|=
literal|0
init|;
name|x
operator|<
name|width
operator|&&
operator|!
name|abort
condition|;
name|x
operator|++
control|)
name|abort
operator|=
operator|!
name|colors_equal_func
argument_list|(
name|bgcolor
argument_list|,
name|buf
operator|+
name|x
operator|*
literal|4
argument_list|)
expr_stmt|;
block|}
if|if
condition|(
name|y
operator|==
name|y2
operator|&&
operator|!
name|abort
condition|)
block|{
name|retval
operator|=
name|GIMP_AUTO_SHRINK_EMPTY
expr_stmt|;
goto|goto
name|FINISH
goto|;
block|}
name|y1
operator|=
name|y
operator|-
literal|1
expr_stmt|;
comment|/* Check how many of the bottom lines are uniform/transparent. */
name|rect
operator|.
name|x
operator|=
name|x1
expr_stmt|;
name|rect
operator|.
name|y
operator|=
literal|0
expr_stmt|;
name|rect
operator|.
name|width
operator|=
name|width
expr_stmt|;
name|rect
operator|.
name|height
operator|=
literal|1
expr_stmt|;
name|abort
operator|=
name|FALSE
expr_stmt|;
for|for
control|(
name|y
operator|=
name|y2
init|;
name|y
operator|>
name|y1
operator|&&
operator|!
name|abort
condition|;
name|y
operator|--
control|)
block|{
name|rect
operator|.
name|y
operator|=
name|y
operator|-
literal|1
expr_stmt|;
name|gegl_buffer_get
argument_list|(
name|buffer
argument_list|,
operator|&
name|rect
argument_list|,
literal|1.0
argument_list|,
name|format
argument_list|,
name|buf
argument_list|,
name|GEGL_AUTO_ROWSTRIDE
argument_list|,
name|GEGL_ABYSS_NONE
argument_list|)
expr_stmt|;
for|for
control|(
name|x
operator|=
literal|0
init|;
name|x
operator|<
name|width
operator|&&
operator|!
name|abort
condition|;
name|x
operator|++
control|)
name|abort
operator|=
operator|!
name|colors_equal_func
argument_list|(
name|bgcolor
argument_list|,
name|buf
operator|+
name|x
operator|*
literal|4
argument_list|)
expr_stmt|;
block|}
name|y2
operator|=
name|y
operator|+
literal|1
expr_stmt|;
comment|/* compute a new height for the next operations */
name|height
operator|=
name|y2
operator|-
name|y1
expr_stmt|;
comment|/* Check how many of the left lines are uniform/transparent. */
name|rect
operator|.
name|x
operator|=
literal|0
expr_stmt|;
name|rect
operator|.
name|y
operator|=
name|y1
expr_stmt|;
name|rect
operator|.
name|width
operator|=
literal|1
expr_stmt|;
name|rect
operator|.
name|height
operator|=
name|height
expr_stmt|;
name|abort
operator|=
name|FALSE
expr_stmt|;
for|for
control|(
name|x
operator|=
name|x1
init|;
name|x
operator|<
name|x2
operator|&&
operator|!
name|abort
condition|;
name|x
operator|++
control|)
block|{
name|rect
operator|.
name|x
operator|=
name|x
expr_stmt|;
name|gegl_buffer_get
argument_list|(
name|buffer
argument_list|,
operator|&
name|rect
argument_list|,
literal|1.0
argument_list|,
name|format
argument_list|,
name|buf
argument_list|,
name|GEGL_AUTO_ROWSTRIDE
argument_list|,
name|GEGL_ABYSS_NONE
argument_list|)
expr_stmt|;
for|for
control|(
name|y
operator|=
literal|0
init|;
name|y
operator|<
name|height
operator|&&
operator|!
name|abort
condition|;
name|y
operator|++
control|)
name|abort
operator|=
operator|!
name|colors_equal_func
argument_list|(
name|bgcolor
argument_list|,
name|buf
operator|+
name|y
operator|*
literal|4
argument_list|)
expr_stmt|;
block|}
name|x1
operator|=
name|x
operator|-
literal|1
expr_stmt|;
comment|/* Check how many of the right lines are uniform/transparent. */
name|rect
operator|.
name|x
operator|=
literal|0
expr_stmt|;
name|rect
operator|.
name|y
operator|=
name|y1
expr_stmt|;
name|rect
operator|.
name|width
operator|=
literal|1
expr_stmt|;
name|rect
operator|.
name|height
operator|=
name|height
expr_stmt|;
name|abort
operator|=
name|FALSE
expr_stmt|;
for|for
control|(
name|x
operator|=
name|x2
init|;
name|x
operator|>
name|x1
operator|&&
operator|!
name|abort
condition|;
name|x
operator|--
control|)
block|{
name|rect
operator|.
name|x
operator|=
name|x
operator|-
literal|1
expr_stmt|;
name|gegl_buffer_get
argument_list|(
name|buffer
argument_list|,
operator|&
name|rect
argument_list|,
literal|1.0
argument_list|,
name|format
argument_list|,
name|buf
argument_list|,
name|GEGL_AUTO_ROWSTRIDE
argument_list|,
name|GEGL_ABYSS_NONE
argument_list|)
expr_stmt|;
for|for
control|(
name|y
operator|=
literal|0
init|;
name|y
operator|<
name|height
operator|&&
operator|!
name|abort
condition|;
name|y
operator|++
control|)
name|abort
operator|=
operator|!
name|colors_equal_func
argument_list|(
name|bgcolor
argument_list|,
name|buf
operator|+
name|y
operator|*
literal|4
argument_list|)
expr_stmt|;
block|}
name|x2
operator|=
name|x
operator|+
literal|1
expr_stmt|;
if|if
condition|(
name|x1
operator|!=
name|start_x1
operator|||
name|y1
operator|!=
name|start_y1
operator|||
name|x2
operator|!=
name|start_x2
operator|||
name|y2
operator|!=
name|start_y2
condition|)
block|{
operator|*
name|shrunk_x1
operator|=
name|x1
expr_stmt|;
operator|*
name|shrunk_y1
operator|=
name|y1
expr_stmt|;
operator|*
name|shrunk_x2
operator|=
name|x2
expr_stmt|;
operator|*
name|shrunk_y2
operator|=
name|y2
expr_stmt|;
name|retval
operator|=
name|GIMP_AUTO_SHRINK_SHRINK
expr_stmt|;
block|}
name|FINISH
label|:
name|g_free
argument_list|(
name|buf
argument_list|)
expr_stmt|;
name|gimp_unset_busy
argument_list|(
name|gimp_pickable_get_image
argument_list|(
name|pickable
argument_list|)
operator|->
name|gimp
argument_list|)
expr_stmt|;
return|return
name|retval
return|;
block|}
end_function

begin_comment
comment|/*  private functions  */
end_comment

begin_function
specifier|static
name|AutoShrinkType
DECL|function|gimp_pickable_guess_bgcolor (GimpPickable * pickable,guchar * color,gint x1,gint x2,gint y1,gint y2)
name|gimp_pickable_guess_bgcolor
parameter_list|(
name|GimpPickable
modifier|*
name|pickable
parameter_list|,
name|guchar
modifier|*
name|color
parameter_list|,
name|gint
name|x1
parameter_list|,
name|gint
name|x2
parameter_list|,
name|gint
name|y1
parameter_list|,
name|gint
name|y2
parameter_list|)
block|{
specifier|const
name|Babl
modifier|*
name|format
init|=
name|babl_format
argument_list|(
literal|"R'G'B'A u8"
argument_list|)
decl_stmt|;
name|guchar
name|tl
index|[
literal|4
index|]
decl_stmt|;
name|guchar
name|tr
index|[
literal|4
index|]
decl_stmt|;
name|guchar
name|bl
index|[
literal|4
index|]
decl_stmt|;
name|guchar
name|br
index|[
literal|4
index|]
decl_stmt|;
name|gint
name|i
decl_stmt|;
for|for
control|(
name|i
operator|=
literal|0
init|;
name|i
operator|<
literal|4
condition|;
name|i
operator|++
control|)
name|color
index|[
name|i
index|]
operator|=
literal|0
expr_stmt|;
comment|/* First check if there's transparency to crop. If not, guess the    * background-color to see if at least 2 corners are equal.    */
if|if
condition|(
operator|!
name|gimp_pickable_get_pixel_at
argument_list|(
name|pickable
argument_list|,
name|x1
argument_list|,
name|y1
argument_list|,
name|format
argument_list|,
name|tl
argument_list|)
operator|||
operator|!
name|gimp_pickable_get_pixel_at
argument_list|(
name|pickable
argument_list|,
name|x1
argument_list|,
name|y2
argument_list|,
name|format
argument_list|,
name|tr
argument_list|)
operator|||
operator|!
name|gimp_pickable_get_pixel_at
argument_list|(
name|pickable
argument_list|,
name|x2
argument_list|,
name|y1
argument_list|,
name|format
argument_list|,
name|bl
argument_list|)
operator|||
operator|!
name|gimp_pickable_get_pixel_at
argument_list|(
name|pickable
argument_list|,
name|x2
argument_list|,
name|y2
argument_list|,
name|format
argument_list|,
name|br
argument_list|)
condition|)
block|{
return|return
name|AUTO_SHRINK_NOTHING
return|;
block|}
if|if
condition|(
operator|(
name|tl
index|[
name|ALPHA
index|]
operator|==
literal|0
operator|&&
name|tr
index|[
name|ALPHA
index|]
operator|==
literal|0
operator|)
operator|||
operator|(
name|tl
index|[
name|ALPHA
index|]
operator|==
literal|0
operator|&&
name|bl
index|[
name|ALPHA
index|]
operator|==
literal|0
operator|)
operator|||
operator|(
name|tr
index|[
name|ALPHA
index|]
operator|==
literal|0
operator|&&
name|br
index|[
name|ALPHA
index|]
operator|==
literal|0
operator|)
operator|||
operator|(
name|bl
index|[
name|ALPHA
index|]
operator|==
literal|0
operator|&&
name|br
index|[
name|ALPHA
index|]
operator|==
literal|0
operator|)
condition|)
block|{
return|return
name|AUTO_SHRINK_ALPHA
return|;
block|}
if|if
condition|(
name|gimp_pickable_colors_equal
argument_list|(
name|tl
argument_list|,
name|tr
argument_list|)
operator|||
name|gimp_pickable_colors_equal
argument_list|(
name|tl
argument_list|,
name|bl
argument_list|)
condition|)
block|{
name|memcpy
argument_list|(
name|color
argument_list|,
name|tl
argument_list|,
literal|4
argument_list|)
expr_stmt|;
return|return
name|AUTO_SHRINK_COLOR
return|;
block|}
if|if
condition|(
name|gimp_pickable_colors_equal
argument_list|(
name|br
argument_list|,
name|bl
argument_list|)
operator|||
name|gimp_pickable_colors_equal
argument_list|(
name|br
argument_list|,
name|tr
argument_list|)
condition|)
block|{
name|memcpy
argument_list|(
name|color
argument_list|,
name|br
argument_list|,
literal|4
argument_list|)
expr_stmt|;
return|return
name|AUTO_SHRINK_COLOR
return|;
block|}
return|return
name|AUTO_SHRINK_NOTHING
return|;
block|}
end_function

begin_function
specifier|static
name|gboolean
DECL|function|gimp_pickable_colors_equal (guchar * col1,guchar * col2)
name|gimp_pickable_colors_equal
parameter_list|(
name|guchar
modifier|*
name|col1
parameter_list|,
name|guchar
modifier|*
name|col2
parameter_list|)
block|{
name|gint
name|b
decl_stmt|;
for|for
control|(
name|b
operator|=
literal|0
init|;
name|b
operator|<
literal|4
condition|;
name|b
operator|++
control|)
block|{
if|if
condition|(
name|col1
index|[
name|b
index|]
operator|!=
name|col2
index|[
name|b
index|]
condition|)
return|return
name|FALSE
return|;
block|}
return|return
name|TRUE
return|;
block|}
end_function

begin_function
specifier|static
name|gboolean
DECL|function|gimp_pickable_colors_alpha (guchar * dummy,guchar * col)
name|gimp_pickable_colors_alpha
parameter_list|(
name|guchar
modifier|*
name|dummy
parameter_list|,
name|guchar
modifier|*
name|col
parameter_list|)
block|{
return|return
operator|(
name|col
index|[
name|ALPHA
index|]
operator|==
literal|0
operator|)
return|;
block|}
end_function

end_unit

