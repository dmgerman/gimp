begin_unit|revision:0.9.5;language:C;cregit-version:0.0.1
begin_comment
comment|/* 	DDS GIMP plugin  	Copyright (C) 2004-2012 Shawn Kirst<skirst@gmail.com>,    with parts (C) 2003 Arne Reuter<homepage@arnereuter.de> where specified.  	This program is free software; you can redistribute it and/or 	modify it under the terms of the GNU General Public 	License as published by the Free Software Foundation; either 	version 2 of the License, or (at your option) any later version.  	This program is distributed in the hope that it will be useful, 	but WITHOUT ANY WARRANTY; without even the implied warranty of 	MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the GNU 	General Public License for more details.  	You should have received a copy of the GNU General Public License 	along with this program; see the file COPYING.  If not, write to 	the Free Software Foundation, 51 Franklin Street, Fifth Floor 	Boston, MA 02110-1301, USA. */
end_comment

begin_include
include|#
directive|include
file|<libgimp/gimp.h>
end_include

begin_include
include|#
directive|include
file|"misc.h"
end_include

begin_function
DECL|function|saturate (float a)
specifier|static
specifier|inline
name|float
name|saturate
parameter_list|(
name|float
name|a
parameter_list|)
block|{
if|if
condition|(
name|a
operator|<
literal|0
condition|)
name|a
operator|=
literal|0
expr_stmt|;
if|if
condition|(
name|a
operator|>
literal|1
condition|)
name|a
operator|=
literal|1
expr_stmt|;
return|return
operator|(
name|a
operator|)
return|;
block|}
end_function

begin_function
DECL|function|decode_ycocg_image (gint32 drawableID,gboolean shadow)
name|void
name|decode_ycocg_image
parameter_list|(
name|gint32
name|drawableID
parameter_list|,
name|gboolean
name|shadow
parameter_list|)
block|{
name|GeglBuffer
modifier|*
name|buffer
decl_stmt|,
modifier|*
name|sbuffer
decl_stmt|;
specifier|const
name|Babl
modifier|*
name|format
decl_stmt|;
name|unsigned
name|char
modifier|*
name|data
decl_stmt|;
name|unsigned
name|int
name|i
decl_stmt|,
name|w
decl_stmt|,
name|h
decl_stmt|,
name|num_pixels
decl_stmt|;
specifier|const
name|float
name|offset
init|=
literal|0.5f
operator|*
literal|256.0f
operator|/
literal|255.0f
decl_stmt|;
name|float
name|Y
decl_stmt|,
name|Co
decl_stmt|,
name|Cg
decl_stmt|,
name|R
decl_stmt|,
name|G
decl_stmt|,
name|B
decl_stmt|;
name|buffer
operator|=
name|gimp_drawable_get_buffer
argument_list|(
name|drawableID
argument_list|)
expr_stmt|;
if|if
condition|(
name|shadow
condition|)
block|{
name|sbuffer
operator|=
name|gimp_drawable_get_shadow_buffer
argument_list|(
name|drawableID
argument_list|)
expr_stmt|;
name|gegl_buffer_copy
argument_list|(
name|buffer
argument_list|,
name|NULL
argument_list|,
name|GEGL_ABYSS_NONE
argument_list|,
name|sbuffer
argument_list|,
name|NULL
argument_list|)
expr_stmt|;
name|g_object_unref
argument_list|(
name|buffer
argument_list|)
expr_stmt|;
name|buffer
operator|=
name|sbuffer
expr_stmt|;
block|}
name|format
operator|=
name|babl_format
argument_list|(
literal|"R'G'B'A u8"
argument_list|)
expr_stmt|;
name|w
operator|=
name|gegl_buffer_get_width
argument_list|(
name|buffer
argument_list|)
expr_stmt|;
name|h
operator|=
name|gegl_buffer_get_height
argument_list|(
name|buffer
argument_list|)
expr_stmt|;
name|num_pixels
operator|=
name|w
operator|*
name|h
expr_stmt|;
name|data
operator|=
name|g_malloc
argument_list|(
name|num_pixels
operator|*
literal|4
argument_list|)
expr_stmt|;
name|gegl_buffer_get
argument_list|(
name|buffer
argument_list|,
name|GEGL_RECTANGLE
argument_list|(
literal|0
argument_list|,
literal|0
argument_list|,
name|w
argument_list|,
name|h
argument_list|)
argument_list|,
literal|1.0
argument_list|,
name|format
argument_list|,
name|data
argument_list|,
name|GEGL_AUTO_ROWSTRIDE
argument_list|,
name|GEGL_ABYSS_NONE
argument_list|)
expr_stmt|;
name|gimp_progress_init
argument_list|(
literal|"Decoding YCoCg pixels..."
argument_list|)
expr_stmt|;
for|for
control|(
name|i
operator|=
literal|0
init|;
name|i
operator|<
name|num_pixels
condition|;
operator|++
name|i
control|)
block|{
name|Y
operator|=
operator|(
name|float
operator|)
name|data
index|[
literal|4
operator|*
name|i
operator|+
literal|3
index|]
operator|/
literal|255.0f
expr_stmt|;
name|Co
operator|=
operator|(
name|float
operator|)
name|data
index|[
literal|4
operator|*
name|i
operator|+
literal|0
index|]
operator|/
literal|255.0f
expr_stmt|;
name|Cg
operator|=
operator|(
name|float
operator|)
name|data
index|[
literal|4
operator|*
name|i
operator|+
literal|1
index|]
operator|/
literal|255.0f
expr_stmt|;
comment|/* convert YCoCg to RGB */
name|Co
operator|-=
name|offset
expr_stmt|;
name|Cg
operator|-=
name|offset
expr_stmt|;
name|R
operator|=
name|saturate
argument_list|(
name|Y
operator|+
name|Co
operator|-
name|Cg
argument_list|)
expr_stmt|;
name|G
operator|=
name|saturate
argument_list|(
name|Y
operator|+
name|Cg
argument_list|)
expr_stmt|;
name|B
operator|=
name|saturate
argument_list|(
name|Y
operator|-
name|Co
operator|-
name|Cg
argument_list|)
expr_stmt|;
comment|/* copy new alpha from blue */
name|data
index|[
literal|4
operator|*
name|i
operator|+
literal|3
index|]
operator|=
name|data
index|[
literal|4
operator|*
name|i
operator|+
literal|2
index|]
expr_stmt|;
name|data
index|[
literal|4
operator|*
name|i
operator|+
literal|0
index|]
operator|=
call|(
name|unsigned
name|char
call|)
argument_list|(
name|R
operator|*
literal|255.0f
argument_list|)
expr_stmt|;
name|data
index|[
literal|4
operator|*
name|i
operator|+
literal|1
index|]
operator|=
call|(
name|unsigned
name|char
call|)
argument_list|(
name|G
operator|*
literal|255.0f
argument_list|)
expr_stmt|;
name|data
index|[
literal|4
operator|*
name|i
operator|+
literal|2
index|]
operator|=
call|(
name|unsigned
name|char
call|)
argument_list|(
name|B
operator|*
literal|255.0f
argument_list|)
expr_stmt|;
if|if
condition|(
operator|(
name|i
operator|&
literal|0x7fff
operator|)
operator|==
literal|0
condition|)
name|gimp_progress_update
argument_list|(
operator|(
name|float
operator|)
name|i
operator|/
operator|(
name|float
operator|)
name|num_pixels
argument_list|)
expr_stmt|;
block|}
name|gegl_buffer_set
argument_list|(
name|buffer
argument_list|,
name|GEGL_RECTANGLE
argument_list|(
literal|0
argument_list|,
literal|0
argument_list|,
name|w
argument_list|,
name|h
argument_list|)
argument_list|,
literal|0
argument_list|,
name|format
argument_list|,
name|data
argument_list|,
name|GEGL_AUTO_ROWSTRIDE
argument_list|)
expr_stmt|;
name|gimp_progress_update
argument_list|(
literal|1.0
argument_list|)
expr_stmt|;
name|gegl_buffer_flush
argument_list|(
name|buffer
argument_list|)
expr_stmt|;
if|if
condition|(
name|shadow
condition|)
name|gimp_drawable_merge_shadow
argument_list|(
name|drawableID
argument_list|,
name|TRUE
argument_list|)
expr_stmt|;
name|gimp_drawable_update
argument_list|(
name|drawableID
argument_list|,
literal|0
argument_list|,
literal|0
argument_list|,
name|w
argument_list|,
name|h
argument_list|)
expr_stmt|;
name|g_free
argument_list|(
name|data
argument_list|)
expr_stmt|;
name|g_object_unref
argument_list|(
name|buffer
argument_list|)
expr_stmt|;
block|}
end_function

begin_function
DECL|function|decode_ycocg_scaled_image (gint32 drawableID,gboolean shadow)
name|void
name|decode_ycocg_scaled_image
parameter_list|(
name|gint32
name|drawableID
parameter_list|,
name|gboolean
name|shadow
parameter_list|)
block|{
name|GeglBuffer
modifier|*
name|buffer
decl_stmt|,
modifier|*
name|sbuffer
decl_stmt|;
specifier|const
name|Babl
modifier|*
name|format
decl_stmt|;
name|unsigned
name|char
modifier|*
name|data
decl_stmt|;
name|unsigned
name|int
name|i
decl_stmt|,
name|w
decl_stmt|,
name|h
decl_stmt|,
name|num_pixels
decl_stmt|;
specifier|const
name|float
name|offset
init|=
literal|0.5f
operator|*
literal|256.0f
operator|/
literal|255.0f
decl_stmt|;
name|float
name|Y
decl_stmt|,
name|Co
decl_stmt|,
name|Cg
decl_stmt|,
name|R
decl_stmt|,
name|G
decl_stmt|,
name|B
decl_stmt|,
name|s
decl_stmt|;
name|buffer
operator|=
name|gimp_drawable_get_buffer
argument_list|(
name|drawableID
argument_list|)
expr_stmt|;
if|if
condition|(
name|shadow
condition|)
block|{
name|sbuffer
operator|=
name|gimp_drawable_get_shadow_buffer
argument_list|(
name|drawableID
argument_list|)
expr_stmt|;
name|gegl_buffer_copy
argument_list|(
name|buffer
argument_list|,
name|NULL
argument_list|,
name|GEGL_ABYSS_NONE
argument_list|,
name|sbuffer
argument_list|,
name|NULL
argument_list|)
expr_stmt|;
name|g_object_unref
argument_list|(
name|buffer
argument_list|)
expr_stmt|;
name|buffer
operator|=
name|sbuffer
expr_stmt|;
block|}
name|format
operator|=
name|babl_format
argument_list|(
literal|"R'G'B'A u8"
argument_list|)
expr_stmt|;
name|w
operator|=
name|gegl_buffer_get_width
argument_list|(
name|buffer
argument_list|)
expr_stmt|;
name|h
operator|=
name|gegl_buffer_get_height
argument_list|(
name|buffer
argument_list|)
expr_stmt|;
name|num_pixels
operator|=
name|w
operator|*
name|h
expr_stmt|;
name|data
operator|=
name|g_malloc
argument_list|(
name|num_pixels
operator|*
literal|4
argument_list|)
expr_stmt|;
name|gegl_buffer_get
argument_list|(
name|buffer
argument_list|,
name|GEGL_RECTANGLE
argument_list|(
literal|0
argument_list|,
literal|0
argument_list|,
name|w
argument_list|,
name|h
argument_list|)
argument_list|,
literal|1.0
argument_list|,
name|format
argument_list|,
name|data
argument_list|,
name|GEGL_AUTO_ROWSTRIDE
argument_list|,
name|GEGL_ABYSS_NONE
argument_list|)
expr_stmt|;
name|gimp_progress_init
argument_list|(
literal|"Decoding YCoCg (scaled) pixels..."
argument_list|)
expr_stmt|;
for|for
control|(
name|i
operator|=
literal|0
init|;
name|i
operator|<
name|num_pixels
condition|;
operator|++
name|i
control|)
block|{
name|Y
operator|=
operator|(
name|float
operator|)
name|data
index|[
literal|4
operator|*
name|i
operator|+
literal|3
index|]
operator|/
literal|255.0f
expr_stmt|;
name|Co
operator|=
operator|(
name|float
operator|)
name|data
index|[
literal|4
operator|*
name|i
operator|+
literal|0
index|]
operator|/
literal|255.0f
expr_stmt|;
name|Cg
operator|=
operator|(
name|float
operator|)
name|data
index|[
literal|4
operator|*
name|i
operator|+
literal|1
index|]
operator|/
literal|255.0f
expr_stmt|;
name|s
operator|=
operator|(
name|float
operator|)
name|data
index|[
literal|4
operator|*
name|i
operator|+
literal|2
index|]
operator|/
literal|255.0f
expr_stmt|;
comment|/* convert YCoCg to RGB */
name|s
operator|=
literal|1.0f
operator|/
operator|(
operator|(
literal|255.0f
operator|/
literal|8.0f
operator|)
operator|*
name|s
operator|+
literal|1.0f
operator|)
expr_stmt|;
name|Co
operator|=
operator|(
name|Co
operator|-
name|offset
operator|)
operator|*
name|s
expr_stmt|;
name|Cg
operator|=
operator|(
name|Cg
operator|-
name|offset
operator|)
operator|*
name|s
expr_stmt|;
name|R
operator|=
name|saturate
argument_list|(
name|Y
operator|+
name|Co
operator|-
name|Cg
argument_list|)
expr_stmt|;
name|G
operator|=
name|saturate
argument_list|(
name|Y
operator|+
name|Cg
argument_list|)
expr_stmt|;
name|B
operator|=
name|saturate
argument_list|(
name|Y
operator|-
name|Co
operator|-
name|Cg
argument_list|)
expr_stmt|;
name|data
index|[
literal|4
operator|*
name|i
operator|+
literal|0
index|]
operator|=
call|(
name|unsigned
name|char
call|)
argument_list|(
name|R
operator|*
literal|255.0f
argument_list|)
expr_stmt|;
name|data
index|[
literal|4
operator|*
name|i
operator|+
literal|1
index|]
operator|=
call|(
name|unsigned
name|char
call|)
argument_list|(
name|G
operator|*
literal|255.0f
argument_list|)
expr_stmt|;
name|data
index|[
literal|4
operator|*
name|i
operator|+
literal|2
index|]
operator|=
call|(
name|unsigned
name|char
call|)
argument_list|(
name|B
operator|*
literal|255.0f
argument_list|)
expr_stmt|;
comment|/* set alpha to 1 */
name|data
index|[
literal|4
operator|*
name|i
operator|+
literal|3
index|]
operator|=
literal|255
expr_stmt|;
if|if
condition|(
operator|(
name|i
operator|&
literal|0x7fff
operator|)
operator|==
literal|0
condition|)
name|gimp_progress_update
argument_list|(
operator|(
name|float
operator|)
name|i
operator|/
operator|(
name|float
operator|)
name|num_pixels
argument_list|)
expr_stmt|;
block|}
name|gegl_buffer_set
argument_list|(
name|buffer
argument_list|,
name|GEGL_RECTANGLE
argument_list|(
literal|0
argument_list|,
literal|0
argument_list|,
name|w
argument_list|,
name|h
argument_list|)
argument_list|,
literal|0
argument_list|,
name|format
argument_list|,
name|data
argument_list|,
name|GEGL_AUTO_ROWSTRIDE
argument_list|)
expr_stmt|;
name|gimp_progress_update
argument_list|(
literal|1.0
argument_list|)
expr_stmt|;
name|gegl_buffer_flush
argument_list|(
name|buffer
argument_list|)
expr_stmt|;
if|if
condition|(
name|shadow
condition|)
name|gimp_drawable_merge_shadow
argument_list|(
name|drawableID
argument_list|,
name|TRUE
argument_list|)
expr_stmt|;
name|gimp_drawable_update
argument_list|(
name|drawableID
argument_list|,
literal|0
argument_list|,
literal|0
argument_list|,
name|w
argument_list|,
name|h
argument_list|)
expr_stmt|;
name|g_free
argument_list|(
name|data
argument_list|)
expr_stmt|;
name|g_object_unref
argument_list|(
name|buffer
argument_list|)
expr_stmt|;
block|}
end_function

begin_function
DECL|function|decode_alpha_exp_image (gint32 drawableID,gboolean shadow)
name|void
name|decode_alpha_exp_image
parameter_list|(
name|gint32
name|drawableID
parameter_list|,
name|gboolean
name|shadow
parameter_list|)
block|{
name|GeglBuffer
modifier|*
name|buffer
decl_stmt|,
modifier|*
name|sbuffer
decl_stmt|;
specifier|const
name|Babl
modifier|*
name|format
decl_stmt|;
name|unsigned
name|char
modifier|*
name|data
decl_stmt|;
name|unsigned
name|int
name|i
decl_stmt|,
name|w
decl_stmt|,
name|h
decl_stmt|,
name|num_pixels
decl_stmt|;
name|int
name|R
decl_stmt|,
name|G
decl_stmt|,
name|B
decl_stmt|,
name|A
decl_stmt|;
name|buffer
operator|=
name|gimp_drawable_get_buffer
argument_list|(
name|drawableID
argument_list|)
expr_stmt|;
if|if
condition|(
name|shadow
condition|)
block|{
name|sbuffer
operator|=
name|gimp_drawable_get_shadow_buffer
argument_list|(
name|drawableID
argument_list|)
expr_stmt|;
name|gegl_buffer_copy
argument_list|(
name|buffer
argument_list|,
name|NULL
argument_list|,
name|GEGL_ABYSS_NONE
argument_list|,
name|sbuffer
argument_list|,
name|NULL
argument_list|)
expr_stmt|;
name|g_object_unref
argument_list|(
name|buffer
argument_list|)
expr_stmt|;
name|buffer
operator|=
name|sbuffer
expr_stmt|;
block|}
name|format
operator|=
name|babl_format
argument_list|(
literal|"R'G'B'A u8"
argument_list|)
expr_stmt|;
name|w
operator|=
name|gegl_buffer_get_width
argument_list|(
name|buffer
argument_list|)
expr_stmt|;
name|h
operator|=
name|gegl_buffer_get_height
argument_list|(
name|buffer
argument_list|)
expr_stmt|;
name|num_pixels
operator|=
name|w
operator|*
name|h
expr_stmt|;
name|data
operator|=
name|g_malloc
argument_list|(
name|num_pixels
operator|*
literal|4
argument_list|)
expr_stmt|;
name|gegl_buffer_get
argument_list|(
name|buffer
argument_list|,
name|GEGL_RECTANGLE
argument_list|(
literal|0
argument_list|,
literal|0
argument_list|,
name|w
argument_list|,
name|h
argument_list|)
argument_list|,
literal|1.0
argument_list|,
name|format
argument_list|,
name|data
argument_list|,
name|GEGL_AUTO_ROWSTRIDE
argument_list|,
name|GEGL_ABYSS_NONE
argument_list|)
expr_stmt|;
name|gimp_progress_init
argument_list|(
literal|"Decoding Alpha-exponent pixels..."
argument_list|)
expr_stmt|;
for|for
control|(
name|i
operator|=
literal|0
init|;
name|i
operator|<
name|num_pixels
condition|;
operator|++
name|i
control|)
block|{
name|R
operator|=
name|data
index|[
literal|4
operator|*
name|i
operator|+
literal|0
index|]
expr_stmt|;
name|G
operator|=
name|data
index|[
literal|4
operator|*
name|i
operator|+
literal|1
index|]
expr_stmt|;
name|B
operator|=
name|data
index|[
literal|4
operator|*
name|i
operator|+
literal|2
index|]
expr_stmt|;
name|A
operator|=
name|data
index|[
literal|4
operator|*
name|i
operator|+
literal|3
index|]
expr_stmt|;
name|R
operator|=
operator|(
name|R
operator|*
name|A
operator|+
literal|1
operator|)
operator|>>
literal|8
expr_stmt|;
name|G
operator|=
operator|(
name|G
operator|*
name|A
operator|+
literal|1
operator|)
operator|>>
literal|8
expr_stmt|;
name|B
operator|=
operator|(
name|B
operator|*
name|A
operator|+
literal|1
operator|)
operator|>>
literal|8
expr_stmt|;
name|A
operator|=
literal|255
expr_stmt|;
name|data
index|[
literal|4
operator|*
name|i
operator|+
literal|0
index|]
operator|=
name|R
expr_stmt|;
name|data
index|[
literal|4
operator|*
name|i
operator|+
literal|1
index|]
operator|=
name|G
expr_stmt|;
name|data
index|[
literal|4
operator|*
name|i
operator|+
literal|2
index|]
operator|=
name|B
expr_stmt|;
name|data
index|[
literal|4
operator|*
name|i
operator|+
literal|3
index|]
operator|=
name|A
expr_stmt|;
if|if
condition|(
operator|(
name|i
operator|&
literal|0x7fff
operator|)
operator|==
literal|0
condition|)
name|gimp_progress_update
argument_list|(
operator|(
name|float
operator|)
name|i
operator|/
operator|(
name|float
operator|)
name|num_pixels
argument_list|)
expr_stmt|;
block|}
name|gegl_buffer_set
argument_list|(
name|buffer
argument_list|,
name|GEGL_RECTANGLE
argument_list|(
literal|0
argument_list|,
literal|0
argument_list|,
name|w
argument_list|,
name|h
argument_list|)
argument_list|,
literal|0
argument_list|,
name|format
argument_list|,
name|data
argument_list|,
name|GEGL_AUTO_ROWSTRIDE
argument_list|)
expr_stmt|;
name|gimp_progress_update
argument_list|(
literal|1.0
argument_list|)
expr_stmt|;
name|gegl_buffer_flush
argument_list|(
name|buffer
argument_list|)
expr_stmt|;
if|if
condition|(
name|shadow
condition|)
name|gimp_drawable_merge_shadow
argument_list|(
name|drawableID
argument_list|,
name|TRUE
argument_list|)
expr_stmt|;
name|gimp_drawable_update
argument_list|(
name|drawableID
argument_list|,
literal|0
argument_list|,
literal|0
argument_list|,
name|w
argument_list|,
name|h
argument_list|)
expr_stmt|;
name|g_free
argument_list|(
name|data
argument_list|)
expr_stmt|;
name|g_object_unref
argument_list|(
name|buffer
argument_list|)
expr_stmt|;
block|}
end_function

end_unit
