begin_unit|revision:0.9.5;language:C;cregit-version:0.0.1
begin_comment
comment|/* The GIMP -- an image manipulation program  * Copyright (C) 1995 Spencer Kimball and Peter Mattis  *  * GimpText  * Copyright (C) 2003  Sven Neumann<sven@gimp.org>  *  * This program is free software; you can redistribute it and/or modify  * it under the terms of the GNU General Public License as published by  * the Free Software Foundation; either version 2 of the License, or  * (at your option) any later version.  *  * This program is distributed in the hope that it will be useful,  * but WITHOUT ANY WARRANTY; without even the implied warranty of  * MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the  * GNU General Public License for more details.  *  * You should have received a copy of the GNU General Public License  * along with this program; if not, write to the Free Software  * Foundation, Inc., 59 Temple Place - Suite 330, Boston, MA 02111-1307, USA.  */
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
file|<pango/pangoft2.h>
end_include

begin_include
include|#
directive|include
file|"text/text-types.h"
end_include

begin_include
include|#
directive|include
file|"gimptext-bitmap.h"
end_include

begin_comment
comment|/* for compatibility with older freetype versions */
end_comment

begin_ifndef
ifndef|#
directive|ifndef
name|FT_LOAD_TARGET_MONO
end_ifndef

begin_define
DECL|macro|FT_LOAD_TARGET_MONO
define|#
directive|define
name|FT_LOAD_TARGET_MONO
value|FT_LOAD_MONOCHROME
end_define

begin_endif
endif|#
directive|endif
end_endif

begin_function
name|void
DECL|function|gimp_text_render_bitmap (PangoFont * font,PangoGlyph glyph,gint flags,gint x,gint y,FT_Bitmap * bitmap)
name|gimp_text_render_bitmap
parameter_list|(
name|PangoFont
modifier|*
name|font
parameter_list|,
name|PangoGlyph
name|glyph
parameter_list|,
name|gint
name|flags
parameter_list|,
name|gint
name|x
parameter_list|,
name|gint
name|y
parameter_list|,
name|FT_Bitmap
modifier|*
name|bitmap
parameter_list|)
block|{
name|FT_Face
name|face
decl_stmt|;
name|gint
name|y_start
decl_stmt|,
name|y_limit
decl_stmt|,
name|x_start
decl_stmt|,
name|x_limit
decl_stmt|;
name|gint
name|ix
decl_stmt|,
name|iy
decl_stmt|;
specifier|const
name|guchar
modifier|*
name|src
decl_stmt|;
name|guchar
modifier|*
name|dest
decl_stmt|;
name|face
operator|=
name|pango_ft2_font_get_face
argument_list|(
name|font
argument_list|)
expr_stmt|;
name|FT_Load_Glyph
argument_list|(
name|face
argument_list|,
operator|(
name|FT_UInt
operator|)
name|glyph
argument_list|,
name|flags
argument_list|)
expr_stmt|;
name|FT_Render_Glyph
argument_list|(
name|face
operator|->
name|glyph
argument_list|,
operator|(
name|flags
operator|&
name|FT_LOAD_TARGET_MONO
condition|?
name|ft_render_mode_mono
else|:
name|ft_render_mode_normal
operator|)
argument_list|)
expr_stmt|;
name|x_start
operator|=
name|MAX
argument_list|(
literal|0
argument_list|,
operator|-
operator|(
name|x
operator|+
name|face
operator|->
name|glyph
operator|->
name|bitmap_left
operator|)
argument_list|)
expr_stmt|;
name|x_limit
operator|=
name|MIN
argument_list|(
name|face
operator|->
name|glyph
operator|->
name|bitmap
operator|.
name|width
argument_list|,
name|bitmap
operator|->
name|width
operator|-
operator|(
name|x
operator|+
name|face
operator|->
name|glyph
operator|->
name|bitmap_left
operator|)
argument_list|)
expr_stmt|;
name|y_start
operator|=
name|MAX
argument_list|(
literal|0
argument_list|,
operator|-
operator|(
name|y
operator|-
name|face
operator|->
name|glyph
operator|->
name|bitmap_top
operator|)
argument_list|)
expr_stmt|;
name|y_limit
operator|=
name|MIN
argument_list|(
name|face
operator|->
name|glyph
operator|->
name|bitmap
operator|.
name|rows
argument_list|,
name|bitmap
operator|->
name|rows
operator|-
operator|(
name|y
operator|-
name|face
operator|->
name|glyph
operator|->
name|bitmap_top
operator|)
argument_list|)
expr_stmt|;
name|src
operator|=
name|face
operator|->
name|glyph
operator|->
name|bitmap
operator|.
name|buffer
operator|+
name|y_start
operator|*
name|face
operator|->
name|glyph
operator|->
name|bitmap
operator|.
name|pitch
expr_stmt|;
name|dest
operator|=
name|bitmap
operator|->
name|buffer
operator|+
operator|(
name|y_start
operator|+
name|y
operator|-
name|face
operator|->
name|glyph
operator|->
name|bitmap_top
operator|)
operator|*
name|bitmap
operator|->
name|pitch
operator|+
name|x_start
operator|+
name|x
operator|+
name|face
operator|->
name|glyph
operator|->
name|bitmap_left
expr_stmt|;
switch|switch
condition|(
name|face
operator|->
name|glyph
operator|->
name|bitmap
operator|.
name|pixel_mode
condition|)
block|{
case|case
name|ft_pixel_mode_grays
case|:
name|src
operator|+=
name|x_start
expr_stmt|;
for|for
control|(
name|iy
operator|=
name|y_start
init|;
name|iy
operator|<
name|y_limit
condition|;
name|iy
operator|++
control|)
block|{
specifier|const
name|guchar
modifier|*
name|s
init|=
name|src
decl_stmt|;
name|guchar
modifier|*
name|d
init|=
name|dest
decl_stmt|;
for|for
control|(
name|ix
operator|=
name|x_start
init|;
name|ix
operator|<
name|x_limit
condition|;
name|ix
operator|++
control|)
block|{
switch|switch
condition|(
operator|*
name|s
condition|)
block|{
case|case
literal|0
case|:
break|break;
case|case
literal|0xff
case|:
operator|*
name|d
operator|=
literal|0xff
expr_stmt|;
default|default:
operator|*
name|d
operator|=
name|MIN
argument_list|(
operator|(
name|gushort
operator|)
operator|*
name|d
operator|+
operator|(
specifier|const
name|gushort
operator|)
operator|*
name|s
argument_list|,
literal|0xff
argument_list|)
expr_stmt|;
break|break;
block|}
name|s
operator|++
expr_stmt|;
name|d
operator|++
expr_stmt|;
block|}
name|dest
operator|+=
name|bitmap
operator|->
name|pitch
expr_stmt|;
name|src
operator|+=
name|face
operator|->
name|glyph
operator|->
name|bitmap
operator|.
name|pitch
expr_stmt|;
block|}
break|break;
case|case
name|ft_pixel_mode_mono
case|:
name|src
operator|+=
name|x_start
operator|/
literal|8
expr_stmt|;
for|for
control|(
name|iy
operator|=
name|y_start
init|;
name|iy
operator|<
name|y_limit
condition|;
name|iy
operator|++
control|)
block|{
specifier|const
name|guchar
modifier|*
name|s
init|=
name|src
decl_stmt|;
name|guchar
modifier|*
name|d
init|=
name|dest
decl_stmt|;
for|for
control|(
name|ix
operator|=
name|x_start
init|;
name|ix
operator|<
name|x_limit
condition|;
name|ix
operator|++
control|)
block|{
if|if
condition|(
operator|(
operator|*
name|s
operator|)
operator|&
operator|(
literal|1
operator|<<
operator|(
literal|7
operator|-
operator|(
name|ix
operator|%
literal|8
operator|)
operator|)
operator|)
condition|)
operator|*
name|d
operator||=
literal|0xff
expr_stmt|;
if|if
condition|(
operator|(
name|ix
operator|%
literal|8
operator|)
operator|==
literal|7
condition|)
name|s
operator|++
expr_stmt|;
name|d
operator|++
expr_stmt|;
block|}
name|dest
operator|+=
name|bitmap
operator|->
name|pitch
expr_stmt|;
name|src
operator|+=
name|face
operator|->
name|glyph
operator|->
name|bitmap
operator|.
name|pitch
expr_stmt|;
block|}
break|break;
default|default:
break|break;
block|}
block|}
end_function

end_unit

