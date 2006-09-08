begin_unit|revision:0.9.5;language:C;cregit-version:0.0.1
begin_comment
comment|/* The GIMP -- an image manipulation program  * Copyright (C) 1995 Spencer Kimball and Peter Mattis  *  * GimpText  * Copyright (C) 2002-2003  Sven Neumann<sven@gimp.org>  *  * This program is free software; you can redistribute it and/or modify  * it under the terms of the GNU General Public License as published by  * the Free Software Foundation; either version 2 of the License, or  * (at your option) any later version.  *  * This program is distributed in the hope that it will be useful,  * but WITHOUT ANY WARRANTY; without even the implied warranty of  * MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the  * GNU General Public License for more details.  *  * You should have received a copy of the GNU General Public License  * along with this program; if not, write to the Free Software  * Foundation, Inc., 59 Temple Place - Suite 330, Boston, MA 02111-1307, USA.  */
end_comment

begin_define
DECL|macro|PANGO_ENABLE_ENGINE
define|#
directive|define
name|PANGO_ENABLE_ENGINE
value|1
end_define

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
file|<pango/pango-font.h>
end_include

begin_include
include|#
directive|include
file|"text-types.h"
end_include

begin_include
include|#
directive|include
file|"base/pixel-region.h"
end_include

begin_include
include|#
directive|include
file|"base/tile-manager.h"
end_include

begin_include
include|#
directive|include
file|"gimptext.h"
end_include

begin_include
include|#
directive|include
file|"gimptext-private.h"
end_include

begin_include
include|#
directive|include
file|"gimptextlayout.h"
end_include

begin_include
include|#
directive|include
file|"gimptextlayout-render.h"
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

begin_comment
comment|/*  This file duplicates quite a lot of code from pangoft2.c.  *  At some point all this should be folded back into Pango.  */
end_comment

begin_function_decl
specifier|static
name|void
name|gimp_text_layout_render_line
parameter_list|(
name|GimpTextLayout
modifier|*
name|layout
parameter_list|,
name|PangoLayoutLine
modifier|*
name|line
parameter_list|,
name|GimpTextRenderFunc
name|render_func
parameter_list|,
name|gint
name|x
parameter_list|,
name|gint
name|y
parameter_list|,
name|gpointer
name|render_data
parameter_list|)
function_decl|;
end_function_decl

begin_function_decl
specifier|static
name|void
name|gimp_text_layout_render_glyphs
parameter_list|(
name|GimpTextLayout
modifier|*
name|layout
parameter_list|,
name|PangoFont
modifier|*
name|font
parameter_list|,
name|PangoGlyphString
modifier|*
name|glyphs
parameter_list|,
name|GimpTextRenderFunc
name|render_func
parameter_list|,
name|gint
name|x
parameter_list|,
name|gint
name|y
parameter_list|,
name|gpointer
name|render_data
parameter_list|)
function_decl|;
end_function_decl

begin_function_decl
specifier|static
name|FT_Int32
name|gimp_text_layout_render_flags
parameter_list|(
name|GimpTextLayout
modifier|*
name|layout
parameter_list|)
function_decl|;
end_function_decl

begin_function_decl
specifier|static
name|void
name|gimp_text_layout_render_trafo
parameter_list|(
name|GimpTextLayout
modifier|*
name|layout
parameter_list|,
name|FT_Matrix
modifier|*
name|trafo
parameter_list|)
function_decl|;
end_function_decl

begin_function
name|void
DECL|function|gimp_text_layout_render (GimpTextLayout * layout,GimpTextRenderFunc render_func,gpointer render_data)
name|gimp_text_layout_render
parameter_list|(
name|GimpTextLayout
modifier|*
name|layout
parameter_list|,
name|GimpTextRenderFunc
name|render_func
parameter_list|,
name|gpointer
name|render_data
parameter_list|)
block|{
name|PangoLayoutIter
modifier|*
name|iter
decl_stmt|;
name|gint
name|x
decl_stmt|,
name|y
decl_stmt|;
name|g_return_if_fail
argument_list|(
name|GIMP_IS_TEXT_LAYOUT
argument_list|(
name|layout
argument_list|)
argument_list|)
expr_stmt|;
name|g_return_if_fail
argument_list|(
name|render_func
operator|!=
name|NULL
argument_list|)
expr_stmt|;
name|gimp_text_layout_get_offsets
argument_list|(
name|layout
argument_list|,
operator|&
name|x
argument_list|,
operator|&
name|y
argument_list|)
expr_stmt|;
name|x
operator|*=
name|PANGO_SCALE
expr_stmt|;
name|y
operator|*=
name|PANGO_SCALE
expr_stmt|;
name|iter
operator|=
name|pango_layout_get_iter
argument_list|(
name|layout
operator|->
name|layout
argument_list|)
expr_stmt|;
do|do
block|{
name|PangoRectangle
name|rect
decl_stmt|;
name|PangoLayoutLine
modifier|*
name|line
decl_stmt|;
name|gint
name|baseline
decl_stmt|;
name|line
operator|=
name|pango_layout_iter_get_line
argument_list|(
name|iter
argument_list|)
expr_stmt|;
name|pango_layout_iter_get_line_extents
argument_list|(
name|iter
argument_list|,
name|NULL
argument_list|,
operator|&
name|rect
argument_list|)
expr_stmt|;
name|baseline
operator|=
name|pango_layout_iter_get_baseline
argument_list|(
name|iter
argument_list|)
expr_stmt|;
name|gimp_text_layout_render_line
argument_list|(
name|layout
argument_list|,
name|line
argument_list|,
name|render_func
argument_list|,
name|x
operator|+
name|rect
operator|.
name|x
argument_list|,
name|y
operator|+
name|baseline
argument_list|,
name|render_data
argument_list|)
expr_stmt|;
block|}
do|while
condition|(
name|pango_layout_iter_next_line
argument_list|(
name|iter
argument_list|)
condition|)
do|;
name|pango_layout_iter_free
argument_list|(
name|iter
argument_list|)
expr_stmt|;
block|}
end_function

begin_function
specifier|static
name|void
DECL|function|gimp_text_layout_render_line (GimpTextLayout * layout,PangoLayoutLine * line,GimpTextRenderFunc render_func,gint x,gint y,gpointer render_data)
name|gimp_text_layout_render_line
parameter_list|(
name|GimpTextLayout
modifier|*
name|layout
parameter_list|,
name|PangoLayoutLine
modifier|*
name|line
parameter_list|,
name|GimpTextRenderFunc
name|render_func
parameter_list|,
name|gint
name|x
parameter_list|,
name|gint
name|y
parameter_list|,
name|gpointer
name|render_data
parameter_list|)
block|{
name|PangoRectangle
name|rect
decl_stmt|;
name|GSList
modifier|*
name|list
decl_stmt|;
name|gint
name|x_off
init|=
literal|0
decl_stmt|;
for|for
control|(
name|list
operator|=
name|line
operator|->
name|runs
init|;
name|list
condition|;
name|list
operator|=
name|list
operator|->
name|next
control|)
block|{
name|PangoLayoutRun
modifier|*
name|run
init|=
name|list
operator|->
name|data
decl_stmt|;
name|pango_glyph_string_extents
argument_list|(
name|run
operator|->
name|glyphs
argument_list|,
name|run
operator|->
name|item
operator|->
name|analysis
operator|.
name|font
argument_list|,
name|NULL
argument_list|,
operator|&
name|rect
argument_list|)
expr_stmt|;
name|gimp_text_layout_render_glyphs
argument_list|(
name|layout
argument_list|,
name|run
operator|->
name|item
operator|->
name|analysis
operator|.
name|font
argument_list|,
name|run
operator|->
name|glyphs
argument_list|,
name|render_func
argument_list|,
name|x
operator|+
name|x_off
argument_list|,
name|y
argument_list|,
name|render_data
argument_list|)
expr_stmt|;
name|x_off
operator|+=
name|rect
operator|.
name|width
expr_stmt|;
block|}
block|}
end_function

begin_function
specifier|static
name|void
DECL|function|gimp_text_layout_render_glyphs (GimpTextLayout * layout,PangoFont * font,PangoGlyphString * glyphs,GimpTextRenderFunc render_func,gint x,gint y,gpointer render_data)
name|gimp_text_layout_render_glyphs
parameter_list|(
name|GimpTextLayout
modifier|*
name|layout
parameter_list|,
name|PangoFont
modifier|*
name|font
parameter_list|,
name|PangoGlyphString
modifier|*
name|glyphs
parameter_list|,
name|GimpTextRenderFunc
name|render_func
parameter_list|,
name|gint
name|x
parameter_list|,
name|gint
name|y
parameter_list|,
name|gpointer
name|render_data
parameter_list|)
block|{
name|PangoGlyphInfo
modifier|*
name|gi
decl_stmt|;
name|FT_Int32
name|flags
decl_stmt|;
name|FT_Matrix
name|trafo
decl_stmt|;
name|FT_Vector
name|pos
decl_stmt|;
name|gint
name|i
decl_stmt|;
name|gint
name|x_position
init|=
literal|0
decl_stmt|;
name|flags
operator|=
name|gimp_text_layout_render_flags
argument_list|(
name|layout
argument_list|)
expr_stmt|;
name|gimp_text_layout_render_trafo
argument_list|(
name|layout
argument_list|,
operator|&
name|trafo
argument_list|)
expr_stmt|;
for|for
control|(
name|i
operator|=
literal|0
operator|,
name|gi
operator|=
name|glyphs
operator|->
name|glyphs
init|;
name|i
operator|<
name|glyphs
operator|->
name|num_glyphs
condition|;
name|i
operator|++
operator|,
name|gi
operator|++
control|)
block|{
if|if
condition|(
name|gi
operator|->
name|glyph
operator|!=
name|PANGO_GLYPH_EMPTY
condition|)
block|{
name|pos
operator|.
name|x
operator|=
name|x
operator|+
name|x_position
operator|+
name|gi
operator|->
name|geometry
operator|.
name|x_offset
expr_stmt|;
name|pos
operator|.
name|y
operator|=
name|y
operator|+
name|gi
operator|->
name|geometry
operator|.
name|y_offset
expr_stmt|;
name|FT_Vector_Transform
argument_list|(
operator|&
name|pos
argument_list|,
operator|&
name|trafo
argument_list|)
expr_stmt|;
name|render_func
argument_list|(
name|font
argument_list|,
name|gi
operator|->
name|glyph
argument_list|,
name|flags
argument_list|,
operator|&
name|trafo
argument_list|,
name|pos
operator|.
name|x
argument_list|,
name|pos
operator|.
name|y
argument_list|,
name|render_data
argument_list|)
expr_stmt|;
block|}
name|x_position
operator|+=
name|glyphs
operator|->
name|glyphs
index|[
name|i
index|]
operator|.
name|geometry
operator|.
name|width
expr_stmt|;
block|}
block|}
end_function

begin_function
specifier|static
name|FT_Int32
DECL|function|gimp_text_layout_render_flags (GimpTextLayout * layout)
name|gimp_text_layout_render_flags
parameter_list|(
name|GimpTextLayout
modifier|*
name|layout
parameter_list|)
block|{
name|GimpText
modifier|*
name|text
init|=
name|layout
operator|->
name|text
decl_stmt|;
name|gint
name|flags
decl_stmt|;
if|if
condition|(
name|text
operator|->
name|antialias
condition|)
name|flags
operator|=
name|FT_LOAD_NO_BITMAP
expr_stmt|;
else|else
name|flags
operator|=
name|FT_LOAD_TARGET_MONO
expr_stmt|;
if|if
condition|(
operator|!
name|text
operator|->
name|hinting
condition|)
name|flags
operator||=
name|FT_LOAD_NO_HINTING
expr_stmt|;
if|if
condition|(
name|text
operator|->
name|autohint
condition|)
name|flags
operator||=
name|FT_LOAD_FORCE_AUTOHINT
expr_stmt|;
return|return
name|flags
return|;
block|}
end_function

begin_function
specifier|static
name|void
DECL|function|gimp_text_layout_render_trafo (GimpTextLayout * layout,FT_Matrix * trafo)
name|gimp_text_layout_render_trafo
parameter_list|(
name|GimpTextLayout
modifier|*
name|layout
parameter_list|,
name|FT_Matrix
modifier|*
name|trafo
parameter_list|)
block|{
name|GimpText
modifier|*
name|text
init|=
name|layout
operator|->
name|text
decl_stmt|;
name|trafo
operator|->
name|xx
operator|=
name|text
operator|->
name|transformation
operator|.
name|coeff
index|[
literal|0
index|]
index|[
literal|0
index|]
operator|*
literal|65536.0
expr_stmt|;
name|trafo
operator|->
name|xy
operator|=
name|text
operator|->
name|transformation
operator|.
name|coeff
index|[
literal|0
index|]
index|[
literal|1
index|]
operator|*
literal|65536.0
expr_stmt|;
name|trafo
operator|->
name|yx
operator|=
name|text
operator|->
name|transformation
operator|.
name|coeff
index|[
literal|1
index|]
index|[
literal|0
index|]
operator|*
literal|65536.0
expr_stmt|;
name|trafo
operator|->
name|yy
operator|=
name|text
operator|->
name|transformation
operator|.
name|coeff
index|[
literal|1
index|]
index|[
literal|1
index|]
operator|*
literal|65536.0
expr_stmt|;
block|}
end_function

end_unit

