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
file|<freetype/ftglyph.h>
end_include

begin_include
include|#
directive|include
file|<freetype/ftoutln.h>
end_include

begin_include
include|#
directive|include
file|"text/text-types.h"
end_include

begin_include
include|#
directive|include
file|"core/gimpimage.h"
end_include

begin_include
include|#
directive|include
file|"vectors/gimpbezierstroke.h"
end_include

begin_include
include|#
directive|include
file|"vectors/gimpvectors.h"
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
file|"gimptext-vectors.h"
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
name|FT_GLYPH_FORMAT_OUTLINE
end_ifndef

begin_define
DECL|macro|FT_GLYPH_FORMAT_OUTLINE
define|#
directive|define
name|FT_GLYPH_FORMAT_OUTLINE
value|ft_glyph_format_outline
end_define

begin_endif
endif|#
directive|endif
end_endif

begin_typedef
DECL|typedef|RenderContext
typedef|typedef
name|struct
name|_RenderContext
name|RenderContext
typedef|;
end_typedef

begin_struct
DECL|struct|_RenderContext
struct|struct
name|_RenderContext
block|{
DECL|member|vectors
name|GimpVectors
modifier|*
name|vectors
decl_stmt|;
DECL|member|stroke
name|GimpStroke
modifier|*
name|stroke
decl_stmt|;
DECL|member|anchor
name|GimpAnchor
modifier|*
name|anchor
decl_stmt|;
DECL|member|offset_x
name|gdouble
name|offset_x
decl_stmt|;
DECL|member|offset_y
name|gdouble
name|offset_y
decl_stmt|;
block|}
struct|;
end_struct

begin_function_decl
specifier|static
name|void
name|gimp_text_render_vectors
parameter_list|(
name|PangoFont
modifier|*
name|font
parameter_list|,
name|PangoGlyph
modifier|*
name|glyph
parameter_list|,
name|FT_Int32
name|flags
parameter_list|,
name|FT_Matrix
modifier|*
name|matrix
parameter_list|,
name|gint
name|x
parameter_list|,
name|gint
name|y
parameter_list|,
name|RenderContext
modifier|*
name|context
parameter_list|)
function_decl|;
end_function_decl

begin_function
name|GimpVectors
modifier|*
DECL|function|gimp_text_vectors_new (GimpImage * image,GimpText * text)
name|gimp_text_vectors_new
parameter_list|(
name|GimpImage
modifier|*
name|image
parameter_list|,
name|GimpText
modifier|*
name|text
parameter_list|)
block|{
name|GimpVectors
modifier|*
name|vectors
decl_stmt|;
name|GimpTextLayout
modifier|*
name|layout
decl_stmt|;
name|RenderContext
name|context
init|=
block|{
literal|0
block|, }
decl_stmt|;
name|g_return_val_if_fail
argument_list|(
name|GIMP_IS_IMAGE
argument_list|(
name|image
argument_list|)
argument_list|,
name|NULL
argument_list|)
expr_stmt|;
name|g_return_val_if_fail
argument_list|(
name|GIMP_IS_TEXT
argument_list|(
name|text
argument_list|)
argument_list|,
name|NULL
argument_list|)
expr_stmt|;
name|vectors
operator|=
name|gimp_vectors_new
argument_list|(
name|image
argument_list|,
name|NULL
argument_list|)
expr_stmt|;
if|if
condition|(
name|text
operator|->
name|text
condition|)
block|{
name|gimp_object_set_name_safe
argument_list|(
name|GIMP_OBJECT
argument_list|(
name|vectors
argument_list|)
argument_list|,
name|text
operator|->
name|text
argument_list|)
expr_stmt|;
name|layout
operator|=
name|gimp_text_layout_new
argument_list|(
name|text
argument_list|,
name|image
argument_list|)
expr_stmt|;
name|context
operator|.
name|vectors
operator|=
name|vectors
expr_stmt|;
name|gimp_text_layout_render
argument_list|(
name|layout
argument_list|,
operator|(
name|GimpTextRenderFunc
operator|)
name|gimp_text_render_vectors
argument_list|,
operator|&
name|context
argument_list|)
expr_stmt|;
name|g_object_unref
argument_list|(
name|layout
argument_list|)
expr_stmt|;
block|}
return|return
name|vectors
return|;
block|}
end_function

begin_function
specifier|static
name|void
DECL|function|gimp_text_vector_coords (RenderContext * context,const FT_Vector * vector,GimpCoords * coords)
name|gimp_text_vector_coords
parameter_list|(
name|RenderContext
modifier|*
name|context
parameter_list|,
specifier|const
name|FT_Vector
modifier|*
name|vector
parameter_list|,
name|GimpCoords
modifier|*
name|coords
parameter_list|)
block|{
name|coords
operator|->
name|x
operator|=
name|context
operator|->
name|offset_x
operator|+
operator|(
name|gdouble
operator|)
name|vector
operator|->
name|x
operator|/
literal|64.0
expr_stmt|;
name|coords
operator|->
name|y
operator|=
name|context
operator|->
name|offset_y
operator|-
operator|(
name|gdouble
operator|)
name|vector
operator|->
name|y
operator|/
literal|64.0
expr_stmt|;
name|coords
operator|->
name|pressure
operator|=
literal|1.0
expr_stmt|;
name|coords
operator|->
name|xtilt
operator|=
literal|0.5
expr_stmt|;
name|coords
operator|->
name|ytilt
operator|=
literal|0.5
expr_stmt|;
name|coords
operator|->
name|wheel
operator|=
literal|0.5
expr_stmt|;
block|}
end_function

begin_function
specifier|static
name|gint
DECL|function|moveto (FT_Vector * to,gpointer data)
name|moveto
parameter_list|(
name|FT_Vector
modifier|*
name|to
parameter_list|,
name|gpointer
name|data
parameter_list|)
block|{
name|RenderContext
modifier|*
name|context
init|=
operator|(
name|RenderContext
operator|*
operator|)
name|data
decl_stmt|;
name|GimpCoords
name|coords
decl_stmt|;
if|#
directive|if
name|TEXT_DEBUG
name|g_printerr
argument_list|(
literal|"moveto  %f, %f\n"
argument_list|,
name|to
operator|->
name|x
operator|/
literal|64.0
argument_list|,
name|to
operator|->
name|y
operator|/
literal|64.0
argument_list|)
expr_stmt|;
endif|#
directive|endif
name|gimp_text_vector_coords
argument_list|(
name|context
argument_list|,
name|to
argument_list|,
operator|&
name|coords
argument_list|)
expr_stmt|;
name|context
operator|->
name|stroke
operator|=
name|gimp_bezier_stroke_new
argument_list|()
expr_stmt|;
name|gimp_vectors_stroke_add
argument_list|(
name|context
operator|->
name|vectors
argument_list|,
name|context
operator|->
name|stroke
argument_list|)
expr_stmt|;
name|g_object_unref
argument_list|(
name|context
operator|->
name|stroke
argument_list|)
expr_stmt|;
name|context
operator|->
name|anchor
operator|=
name|gimp_bezier_stroke_extend
argument_list|(
name|GIMP_BEZIER_STROKE
argument_list|(
name|context
operator|->
name|stroke
argument_list|)
argument_list|,
operator|&
name|coords
argument_list|,
name|NULL
argument_list|,
name|EXTEND_SIMPLE
argument_list|)
expr_stmt|;
name|context
operator|->
name|anchor
operator|=
name|gimp_bezier_stroke_extend
argument_list|(
name|GIMP_BEZIER_STROKE
argument_list|(
name|context
operator|->
name|stroke
argument_list|)
argument_list|,
operator|&
name|coords
argument_list|,
name|context
operator|->
name|anchor
argument_list|,
name|EXTEND_SIMPLE
argument_list|)
expr_stmt|;
name|context
operator|->
name|anchor
operator|=
name|gimp_bezier_stroke_extend
argument_list|(
name|GIMP_BEZIER_STROKE
argument_list|(
name|context
operator|->
name|stroke
argument_list|)
argument_list|,
operator|&
name|coords
argument_list|,
name|context
operator|->
name|anchor
argument_list|,
name|EXTEND_SIMPLE
argument_list|)
expr_stmt|;
return|return
literal|0
return|;
block|}
end_function

begin_function
specifier|static
name|gint
DECL|function|lineto (FT_Vector * to,gpointer data)
name|lineto
parameter_list|(
name|FT_Vector
modifier|*
name|to
parameter_list|,
name|gpointer
name|data
parameter_list|)
block|{
name|RenderContext
modifier|*
name|context
init|=
operator|(
name|RenderContext
operator|*
operator|)
name|data
decl_stmt|;
name|GimpCoords
name|coords
decl_stmt|;
if|#
directive|if
name|TEXT_DEBUG
name|g_printerr
argument_list|(
literal|"lineto  %f, %f\n"
argument_list|,
name|to
operator|->
name|x
operator|/
literal|64.0
argument_list|,
name|to
operator|->
name|y
operator|/
literal|64.0
argument_list|)
expr_stmt|;
endif|#
directive|endif
if|if
condition|(
operator|!
name|context
operator|->
name|stroke
condition|)
return|return
literal|0
return|;
name|gimp_text_vector_coords
argument_list|(
name|context
argument_list|,
name|to
argument_list|,
operator|&
name|coords
argument_list|)
expr_stmt|;
name|context
operator|->
name|anchor
operator|=
name|gimp_bezier_stroke_extend
argument_list|(
name|GIMP_BEZIER_STROKE
argument_list|(
name|context
operator|->
name|stroke
argument_list|)
argument_list|,
operator|&
name|coords
argument_list|,
name|context
operator|->
name|anchor
argument_list|,
name|EXTEND_SIMPLE
argument_list|)
expr_stmt|;
name|context
operator|->
name|anchor
operator|=
name|gimp_bezier_stroke_extend
argument_list|(
name|GIMP_BEZIER_STROKE
argument_list|(
name|context
operator|->
name|stroke
argument_list|)
argument_list|,
operator|&
name|coords
argument_list|,
name|context
operator|->
name|anchor
argument_list|,
name|EXTEND_SIMPLE
argument_list|)
expr_stmt|;
name|context
operator|->
name|anchor
operator|=
name|gimp_bezier_stroke_extend
argument_list|(
name|GIMP_BEZIER_STROKE
argument_list|(
name|context
operator|->
name|stroke
argument_list|)
argument_list|,
operator|&
name|coords
argument_list|,
name|context
operator|->
name|anchor
argument_list|,
name|EXTEND_SIMPLE
argument_list|)
expr_stmt|;
return|return
literal|0
return|;
block|}
end_function

begin_function
specifier|static
name|gint
DECL|function|conicto (FT_Vector * control,FT_Vector * to,gpointer data)
name|conicto
parameter_list|(
name|FT_Vector
modifier|*
name|control
parameter_list|,
name|FT_Vector
modifier|*
name|to
parameter_list|,
name|gpointer
name|data
parameter_list|)
block|{
name|RenderContext
modifier|*
name|context
init|=
operator|(
name|RenderContext
operator|*
operator|)
name|data
decl_stmt|;
name|GimpCoords
name|coords
decl_stmt|;
if|#
directive|if
name|TEXT_DEBUG
name|g_printerr
argument_list|(
literal|"conicto %f, %f\n"
argument_list|,
name|to
operator|->
name|x
operator|/
literal|64.0
argument_list|,
name|to
operator|->
name|y
operator|/
literal|64.0
argument_list|)
expr_stmt|;
endif|#
directive|endif
if|if
condition|(
operator|!
name|context
operator|->
name|stroke
condition|)
return|return
literal|0
return|;
name|gimp_text_vector_coords
argument_list|(
name|context
argument_list|,
name|control
argument_list|,
operator|&
name|coords
argument_list|)
expr_stmt|;
name|context
operator|->
name|anchor
operator|=
name|gimp_bezier_stroke_extend
argument_list|(
name|GIMP_BEZIER_STROKE
argument_list|(
name|context
operator|->
name|stroke
argument_list|)
argument_list|,
operator|&
name|coords
argument_list|,
name|context
operator|->
name|anchor
argument_list|,
name|EXTEND_SIMPLE
argument_list|)
expr_stmt|;
name|gimp_text_vector_coords
argument_list|(
name|context
argument_list|,
name|to
argument_list|,
operator|&
name|coords
argument_list|)
expr_stmt|;
name|context
operator|->
name|anchor
operator|=
name|gimp_bezier_stroke_extend
argument_list|(
name|GIMP_BEZIER_STROKE
argument_list|(
name|context
operator|->
name|stroke
argument_list|)
argument_list|,
operator|&
name|coords
argument_list|,
name|context
operator|->
name|anchor
argument_list|,
name|EXTEND_SIMPLE
argument_list|)
expr_stmt|;
name|context
operator|->
name|anchor
operator|=
name|gimp_bezier_stroke_extend
argument_list|(
name|GIMP_BEZIER_STROKE
argument_list|(
name|context
operator|->
name|stroke
argument_list|)
argument_list|,
operator|&
name|coords
argument_list|,
name|context
operator|->
name|anchor
argument_list|,
name|EXTEND_SIMPLE
argument_list|)
expr_stmt|;
return|return
literal|0
return|;
block|}
end_function

begin_function
specifier|static
name|gint
DECL|function|cubicto (FT_Vector * control1,FT_Vector * control2,FT_Vector * to,gpointer data)
name|cubicto
parameter_list|(
name|FT_Vector
modifier|*
name|control1
parameter_list|,
name|FT_Vector
modifier|*
name|control2
parameter_list|,
name|FT_Vector
modifier|*
name|to
parameter_list|,
name|gpointer
name|data
parameter_list|)
block|{
name|RenderContext
modifier|*
name|context
init|=
operator|(
name|RenderContext
operator|*
operator|)
name|data
decl_stmt|;
name|GimpCoords
name|coords
decl_stmt|;
if|#
directive|if
name|TEXT_DEBUG
name|g_printerr
argument_list|(
literal|"cubicto %f, %f\n"
argument_list|,
name|to
operator|->
name|x
operator|/
literal|64.0
argument_list|,
name|to
operator|->
name|y
operator|/
literal|64.0
argument_list|)
expr_stmt|;
endif|#
directive|endif
if|if
condition|(
operator|!
name|context
operator|->
name|stroke
condition|)
return|return
literal|0
return|;
name|gimp_text_vector_coords
argument_list|(
name|context
argument_list|,
name|control1
argument_list|,
operator|&
name|coords
argument_list|)
expr_stmt|;
name|context
operator|->
name|anchor
operator|=
name|gimp_bezier_stroke_extend
argument_list|(
name|GIMP_BEZIER_STROKE
argument_list|(
name|context
operator|->
name|stroke
argument_list|)
argument_list|,
operator|&
name|coords
argument_list|,
name|context
operator|->
name|anchor
argument_list|,
name|EXTEND_SIMPLE
argument_list|)
expr_stmt|;
name|gimp_text_vector_coords
argument_list|(
name|context
argument_list|,
name|to
argument_list|,
operator|&
name|coords
argument_list|)
expr_stmt|;
name|context
operator|->
name|anchor
operator|=
name|gimp_bezier_stroke_extend
argument_list|(
name|GIMP_BEZIER_STROKE
argument_list|(
name|context
operator|->
name|stroke
argument_list|)
argument_list|,
operator|&
name|coords
argument_list|,
name|context
operator|->
name|anchor
argument_list|,
name|EXTEND_SIMPLE
argument_list|)
expr_stmt|;
name|gimp_text_vector_coords
argument_list|(
name|context
argument_list|,
name|control2
argument_list|,
operator|&
name|coords
argument_list|)
expr_stmt|;
name|context
operator|->
name|anchor
operator|=
name|gimp_bezier_stroke_extend
argument_list|(
name|GIMP_BEZIER_STROKE
argument_list|(
name|context
operator|->
name|stroke
argument_list|)
argument_list|,
operator|&
name|coords
argument_list|,
name|context
operator|->
name|anchor
argument_list|,
name|EXTEND_SIMPLE
argument_list|)
expr_stmt|;
return|return
literal|0
return|;
block|}
end_function

begin_function
specifier|static
name|void
DECL|function|gimp_text_render_vectors (PangoFont * font,PangoGlyph * pango_glyph,FT_Int32 flags,FT_Matrix * trafo,gint x,gint y,RenderContext * context)
name|gimp_text_render_vectors
parameter_list|(
name|PangoFont
modifier|*
name|font
parameter_list|,
name|PangoGlyph
modifier|*
name|pango_glyph
parameter_list|,
name|FT_Int32
name|flags
parameter_list|,
name|FT_Matrix
modifier|*
name|trafo
parameter_list|,
name|gint
name|x
parameter_list|,
name|gint
name|y
parameter_list|,
name|RenderContext
modifier|*
name|context
parameter_list|)
block|{
specifier|const
name|FT_Outline_Funcs
name|outline_funcs
init|=
block|{
name|moveto
block|,
name|lineto
block|,
name|conicto
block|,
name|cubicto
block|,
literal|0
block|,
literal|0
block|}
decl_stmt|;
name|FT_Face
name|face
decl_stmt|;
name|FT_Glyph
name|glyph
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
name|pango_glyph
argument_list|,
name|flags
argument_list|)
expr_stmt|;
name|FT_Get_Glyph
argument_list|(
name|face
operator|->
name|glyph
argument_list|,
operator|&
name|glyph
argument_list|)
expr_stmt|;
if|if
condition|(
name|face
operator|->
name|glyph
operator|->
name|format
operator|==
name|FT_GLYPH_FORMAT_OUTLINE
condition|)
block|{
name|FT_OutlineGlyph
name|outline_glyph
init|=
operator|(
name|FT_OutlineGlyph
operator|)
name|glyph
decl_stmt|;
name|context
operator|->
name|offset_x
operator|=
operator|(
name|gdouble
operator|)
name|x
operator|/
name|PANGO_SCALE
expr_stmt|;
name|context
operator|->
name|offset_y
operator|=
operator|(
name|gdouble
operator|)
name|y
operator|/
name|PANGO_SCALE
expr_stmt|;
name|FT_Outline_Decompose
argument_list|(
operator|&
name|outline_glyph
operator|->
name|outline
argument_list|,
operator|&
name|outline_funcs
argument_list|,
name|context
argument_list|)
expr_stmt|;
block|}
name|FT_Done_Glyph
argument_list|(
name|glyph
argument_list|)
expr_stmt|;
block|}
end_function

end_unit

