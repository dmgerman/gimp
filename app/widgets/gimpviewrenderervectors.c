begin_unit|revision:0.9.5;language:C;cregit-version:0.0.1
begin_comment
comment|/* The GIMP -- an image manipulation program  * Copyright (C) 1995 Spencer Kimball and Peter Mattis  *  * gimpviewrenderervectors.c  * Copyright (C) 2003 Michael Natterer<mitch@gimp.org>  *                    Simon Budig<simon@gimp.org>  *  * This program is free software; you can redistribute it and/or modify  * it under the terms of the GNU General Public License as published by  * the Free Software Foundation; either version 2 of the License, or  * (at your option) any later version.  *  * This program is distributed in the hope that it will be useful,  * but WITHOUT ANY WARRANTY; without even the implied warranty of  * MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the  * GNU General Public License for more details.  *  * You should have received a copy of the GNU General Public License  * along with this program; if not, write to the Free Software  * Foundation, Inc., 59 Temple Place - Suite 330, Boston, MA 02111-1307, USA.  */
end_comment

begin_include
include|#
directive|include
file|"config.h"
end_include

begin_include
include|#
directive|include
file|<gtk/gtk.h>
end_include

begin_include
include|#
directive|include
file|"libgimpwidgets/gimpwidgets.h"
end_include

begin_include
include|#
directive|include
file|"widgets-types.h"
end_include

begin_include
include|#
directive|include
file|"core/gimpimage.h"
end_include

begin_include
include|#
directive|include
file|"core/gimpitem.h"
end_include

begin_include
include|#
directive|include
file|"vectors/gimpstroke.h"
end_include

begin_include
include|#
directive|include
file|"vectors/gimpvectors.h"
end_include

begin_include
include|#
directive|include
file|"gimpviewrenderervectors.h"
end_include

begin_function_decl
specifier|static
name|void
name|gimp_view_renderer_vectors_draw
parameter_list|(
name|GimpViewRenderer
modifier|*
name|renderer
parameter_list|,
name|GdkWindow
modifier|*
name|window
parameter_list|,
name|GtkWidget
modifier|*
name|widget
parameter_list|,
specifier|const
name|GdkRectangle
modifier|*
name|draw_area
parameter_list|,
specifier|const
name|GdkRectangle
modifier|*
name|expose_area
parameter_list|)
function_decl|;
end_function_decl

begin_expr_stmt
name|G_DEFINE_TYPE
argument_list|(
name|GimpViewRendererVectors
argument_list|,
name|gimp_view_renderer_vectors
argument_list|,
name|GIMP_TYPE_VIEW_RENDERER
argument_list|)
expr_stmt|;
end_expr_stmt

begin_define
DECL|macro|parent_class
define|#
directive|define
name|parent_class
value|gimp_view_renderer_vectors_parent_class
end_define

begin_function
specifier|static
name|void
DECL|function|gimp_view_renderer_vectors_class_init (GimpViewRendererVectorsClass * klass)
name|gimp_view_renderer_vectors_class_init
parameter_list|(
name|GimpViewRendererVectorsClass
modifier|*
name|klass
parameter_list|)
block|{
name|GimpViewRendererClass
modifier|*
name|renderer_class
init|=
name|GIMP_VIEW_RENDERER_CLASS
argument_list|(
name|klass
argument_list|)
decl_stmt|;
name|renderer_class
operator|->
name|draw
operator|=
name|gimp_view_renderer_vectors_draw
expr_stmt|;
block|}
end_function

begin_function
specifier|static
name|void
DECL|function|gimp_view_renderer_vectors_init (GimpViewRendererVectors * renderer)
name|gimp_view_renderer_vectors_init
parameter_list|(
name|GimpViewRendererVectors
modifier|*
name|renderer
parameter_list|)
block|{ }
end_function

begin_function
specifier|static
name|void
DECL|function|gimp_view_renderer_vectors_draw (GimpViewRenderer * renderer,GdkWindow * window,GtkWidget * widget,const GdkRectangle * draw_area,const GdkRectangle * expose_area)
name|gimp_view_renderer_vectors_draw
parameter_list|(
name|GimpViewRenderer
modifier|*
name|renderer
parameter_list|,
name|GdkWindow
modifier|*
name|window
parameter_list|,
name|GtkWidget
modifier|*
name|widget
parameter_list|,
specifier|const
name|GdkRectangle
modifier|*
name|draw_area
parameter_list|,
specifier|const
name|GdkRectangle
modifier|*
name|expose_area
parameter_list|)
block|{
name|GimpVectors
modifier|*
name|vectors
decl_stmt|;
name|GimpStroke
modifier|*
name|stroke
decl_stmt|;
name|GdkRectangle
name|rect
decl_stmt|,
name|area
decl_stmt|;
name|gdouble
name|xscale
decl_stmt|,
name|yscale
decl_stmt|;
name|rect
operator|.
name|width
operator|=
name|renderer
operator|->
name|width
expr_stmt|;
name|rect
operator|.
name|height
operator|=
name|renderer
operator|->
name|height
expr_stmt|;
name|rect
operator|.
name|x
operator|=
name|draw_area
operator|->
name|x
operator|+
operator|(
name|draw_area
operator|->
name|width
operator|-
name|rect
operator|.
name|width
operator|)
operator|/
literal|2
expr_stmt|;
name|rect
operator|.
name|y
operator|=
name|draw_area
operator|->
name|y
operator|+
operator|(
name|draw_area
operator|->
name|height
operator|-
name|rect
operator|.
name|height
operator|)
operator|/
literal|2
expr_stmt|;
if|if
condition|(
operator|!
name|gdk_rectangle_intersect
argument_list|(
operator|&
name|rect
argument_list|,
operator|(
name|GdkRectangle
operator|*
operator|)
name|expose_area
argument_list|,
operator|&
name|area
argument_list|)
condition|)
return|return;
name|gdk_draw_rectangle
argument_list|(
name|window
argument_list|,
name|widget
operator|->
name|style
operator|->
name|white_gc
argument_list|,
name|TRUE
argument_list|,
name|area
operator|.
name|x
argument_list|,
name|area
operator|.
name|y
argument_list|,
name|area
operator|.
name|width
argument_list|,
name|area
operator|.
name|height
argument_list|)
expr_stmt|;
name|vectors
operator|=
name|GIMP_VECTORS
argument_list|(
name|renderer
operator|->
name|viewable
argument_list|)
expr_stmt|;
name|xscale
operator|=
operator|(
name|gdouble
operator|)
name|GIMP_ITEM
argument_list|(
name|vectors
argument_list|)
operator|->
name|width
operator|/
operator|(
name|gdouble
operator|)
name|rect
operator|.
name|width
expr_stmt|;
name|yscale
operator|=
operator|(
name|gdouble
operator|)
name|GIMP_ITEM
argument_list|(
name|vectors
argument_list|)
operator|->
name|height
operator|/
operator|(
name|gdouble
operator|)
name|rect
operator|.
name|height
expr_stmt|;
name|gdk_gc_set_clip_rectangle
argument_list|(
name|widget
operator|->
name|style
operator|->
name|black_gc
argument_list|,
operator|&
name|area
argument_list|)
expr_stmt|;
for|for
control|(
name|stroke
operator|=
name|gimp_vectors_stroke_get_next
argument_list|(
name|vectors
argument_list|,
name|NULL
argument_list|)
init|;
name|stroke
operator|!=
name|NULL
condition|;
name|stroke
operator|=
name|gimp_vectors_stroke_get_next
argument_list|(
name|vectors
argument_list|,
name|stroke
argument_list|)
control|)
block|{
name|GArray
modifier|*
name|coordinates
decl_stmt|;
name|GdkPoint
modifier|*
name|points
decl_stmt|;
name|gint
name|i
decl_stmt|;
name|coordinates
operator|=
name|gimp_stroke_interpolate
argument_list|(
name|stroke
argument_list|,
name|MIN
argument_list|(
name|xscale
argument_list|,
name|yscale
argument_list|)
operator|/
literal|2
argument_list|,
name|NULL
argument_list|)
expr_stmt|;
if|if
condition|(
operator|!
name|coordinates
condition|)
continue|continue;
if|if
condition|(
name|coordinates
operator|->
name|len
operator|>
literal|0
condition|)
block|{
name|points
operator|=
name|g_new
argument_list|(
name|GdkPoint
argument_list|,
name|coordinates
operator|->
name|len
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
name|coordinates
operator|->
name|len
condition|;
name|i
operator|++
control|)
block|{
name|GimpCoords
modifier|*
name|coords
decl_stmt|;
name|coords
operator|=
operator|&
operator|(
name|g_array_index
argument_list|(
name|coordinates
argument_list|,
name|GimpCoords
argument_list|,
name|i
argument_list|)
operator|)
expr_stmt|;
name|points
index|[
name|i
index|]
operator|.
name|x
operator|=
name|rect
operator|.
name|x
operator|+
name|ROUND
argument_list|(
name|coords
operator|->
name|x
operator|/
name|xscale
argument_list|)
expr_stmt|;
name|points
index|[
name|i
index|]
operator|.
name|y
operator|=
name|rect
operator|.
name|y
operator|+
name|ROUND
argument_list|(
name|coords
operator|->
name|y
operator|/
name|yscale
argument_list|)
expr_stmt|;
block|}
name|gdk_draw_lines
argument_list|(
name|window
argument_list|,
name|widget
operator|->
name|style
operator|->
name|black_gc
argument_list|,
name|points
argument_list|,
name|coordinates
operator|->
name|len
argument_list|)
expr_stmt|;
name|g_free
argument_list|(
name|points
argument_list|)
expr_stmt|;
block|}
name|g_array_free
argument_list|(
name|coordinates
argument_list|,
name|TRUE
argument_list|)
expr_stmt|;
block|}
name|gdk_gc_set_clip_rectangle
argument_list|(
name|widget
operator|->
name|style
operator|->
name|black_gc
argument_list|,
name|NULL
argument_list|)
expr_stmt|;
block|}
end_function

end_unit

