begin_unit|revision:0.9.5;language:C;cregit-version:0.0.1
begin_comment
comment|/* GIMP - The GNU Image Manipulation Program  * Copyright (C) 1995 Spencer Kimball and Peter Mattis  *  * gimpviewrendererpalette.c  * Copyright (C) 2005 Michael Natterer<mitch@gimp.org>  *  * This program is free software: you can redistribute it and/or modify  * it under the terms of the GNU General Public License as published by  * the Free Software Foundation; either version 3 of the License, or  * (at your option) any later version.  *  * This program is distributed in the hope that it will be useful,  * but WITHOUT ANY WARRANTY; without even the implied warranty of  * MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the  * GNU General Public License for more details.  *  * You should have received a copy of the GNU General Public License  * along with this program.  If not, see<http://www.gnu.org/licenses/>.  */
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
file|<gtk/gtk.h>
end_include

begin_include
include|#
directive|include
file|"libgimpcolor/gimpcolor.h"
end_include

begin_include
include|#
directive|include
file|"libgimpmath/gimpmath.h"
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
file|"core/gimppalette.h"
end_include

begin_include
include|#
directive|include
file|"gimpviewrendererpalette.h"
end_include

begin_define
DECL|macro|COLUMNS
define|#
directive|define
name|COLUMNS
value|16
end_define

begin_function_decl
specifier|static
name|void
name|gimp_view_renderer_palette_finalize
parameter_list|(
name|GObject
modifier|*
name|object
parameter_list|)
function_decl|;
end_function_decl

begin_function_decl
specifier|static
name|void
name|gimp_view_renderer_palette_render
parameter_list|(
name|GimpViewRenderer
modifier|*
name|renderer
parameter_list|,
name|GtkWidget
modifier|*
name|widget
parameter_list|)
function_decl|;
end_function_decl

begin_macro
DECL|function|G_DEFINE_TYPE (GimpViewRendererPalette,gimp_view_renderer_palette,GIMP_TYPE_VIEW_RENDERER)
name|G_DEFINE_TYPE
argument_list|(
argument|GimpViewRendererPalette
argument_list|,
argument|gimp_view_renderer_palette
argument_list|,
argument|GIMP_TYPE_VIEW_RENDERER
argument_list|)
end_macro

begin_define
DECL|macro|parent_class
define|#
directive|define
name|parent_class
value|gimp_view_renderer_palette_parent_class
end_define

begin_function
specifier|static
name|void
name|gimp_view_renderer_palette_class_init
parameter_list|(
name|GimpViewRendererPaletteClass
modifier|*
name|klass
parameter_list|)
block|{
name|GObjectClass
modifier|*
name|object_class
init|=
name|G_OBJECT_CLASS
argument_list|(
name|klass
argument_list|)
decl_stmt|;
name|GimpViewRendererClass
modifier|*
name|renderer_class
init|=
name|GIMP_VIEW_RENDERER_CLASS
argument_list|(
name|klass
argument_list|)
decl_stmt|;
name|object_class
operator|->
name|finalize
operator|=
name|gimp_view_renderer_palette_finalize
expr_stmt|;
name|renderer_class
operator|->
name|render
operator|=
name|gimp_view_renderer_palette_render
expr_stmt|;
block|}
end_function

begin_function
specifier|static
name|void
DECL|function|gimp_view_renderer_palette_init (GimpViewRendererPalette * renderer)
name|gimp_view_renderer_palette_init
parameter_list|(
name|GimpViewRendererPalette
modifier|*
name|renderer
parameter_list|)
block|{
name|renderer
operator|->
name|cell_size
operator|=
literal|4
expr_stmt|;
name|renderer
operator|->
name|draw_grid
operator|=
name|FALSE
expr_stmt|;
name|renderer
operator|->
name|columns
operator|=
name|COLUMNS
expr_stmt|;
block|}
end_function

begin_function
specifier|static
name|void
DECL|function|gimp_view_renderer_palette_finalize (GObject * object)
name|gimp_view_renderer_palette_finalize
parameter_list|(
name|GObject
modifier|*
name|object
parameter_list|)
block|{
name|G_OBJECT_CLASS
argument_list|(
name|parent_class
argument_list|)
operator|->
name|finalize
argument_list|(
name|object
argument_list|)
expr_stmt|;
block|}
end_function

begin_function
specifier|static
name|void
DECL|function|gimp_view_renderer_palette_render (GimpViewRenderer * renderer,GtkWidget * widget)
name|gimp_view_renderer_palette_render
parameter_list|(
name|GimpViewRenderer
modifier|*
name|renderer
parameter_list|,
name|GtkWidget
modifier|*
name|widget
parameter_list|)
block|{
name|GimpViewRendererPalette
modifier|*
name|renderpal
init|=
name|GIMP_VIEW_RENDERER_PALETTE
argument_list|(
name|renderer
argument_list|)
decl_stmt|;
name|GimpPalette
modifier|*
name|palette
decl_stmt|;
name|guchar
modifier|*
name|row
decl_stmt|;
name|guchar
modifier|*
name|dest
decl_stmt|;
name|GList
modifier|*
name|list
decl_stmt|;
name|gdouble
name|cell_width
decl_stmt|;
name|gint
name|grid_width
decl_stmt|;
name|gint
name|dest_stride
decl_stmt|;
name|gint
name|y
decl_stmt|;
name|palette
operator|=
name|GIMP_PALETTE
argument_list|(
name|renderer
operator|->
name|viewable
argument_list|)
expr_stmt|;
if|if
condition|(
name|gimp_palette_get_n_colors
argument_list|(
name|palette
argument_list|)
operator|==
literal|0
condition|)
return|return;
name|grid_width
operator|=
name|renderpal
operator|->
name|draw_grid
condition|?
literal|1
else|:
literal|0
expr_stmt|;
if|if
condition|(
name|renderpal
operator|->
name|cell_size
operator|>
literal|0
condition|)
block|{
name|gint
name|n_columns
init|=
name|gimp_palette_get_columns
argument_list|(
name|palette
argument_list|)
decl_stmt|;
if|if
condition|(
name|n_columns
operator|>
literal|0
condition|)
name|cell_width
operator|=
name|MAX
argument_list|(
operator|(
name|gdouble
operator|)
name|renderpal
operator|->
name|cell_size
argument_list|,
call|(
name|gdouble
call|)
argument_list|(
name|renderer
operator|->
name|width
operator|-
name|grid_width
argument_list|)
operator|/
operator|(
name|gdouble
operator|)
name|n_columns
argument_list|)
expr_stmt|;
else|else
name|cell_width
operator|=
name|renderpal
operator|->
name|cell_size
expr_stmt|;
block|}
else|else
block|{
name|gint
name|n_columns
init|=
name|gimp_palette_get_columns
argument_list|(
name|palette
argument_list|)
decl_stmt|;
if|if
condition|(
name|n_columns
operator|>
literal|0
condition|)
name|cell_width
operator|=
operator|(
call|(
name|gdouble
call|)
argument_list|(
name|renderer
operator|->
name|width
operator|-
name|grid_width
argument_list|)
operator|/
operator|(
name|gdouble
operator|)
name|n_columns
operator|)
expr_stmt|;
else|else
name|cell_width
operator|=
call|(
name|gdouble
call|)
argument_list|(
name|renderer
operator|->
name|width
operator|-
name|grid_width
argument_list|)
operator|/
literal|16.0
expr_stmt|;
block|}
name|cell_width
operator|=
name|MAX
argument_list|(
literal|4.0
argument_list|,
name|cell_width
argument_list|)
expr_stmt|;
name|renderpal
operator|->
name|cell_width
operator|=
name|cell_width
expr_stmt|;
name|renderpal
operator|->
name|columns
operator|=
call|(
name|gdouble
call|)
argument_list|(
name|renderer
operator|->
name|width
operator|-
name|grid_width
argument_list|)
operator|/
name|cell_width
expr_stmt|;
name|renderpal
operator|->
name|rows
operator|=
name|gimp_palette_get_n_colors
argument_list|(
name|palette
argument_list|)
operator|/
name|renderpal
operator|->
name|columns
expr_stmt|;
if|if
condition|(
name|gimp_palette_get_n_colors
argument_list|(
name|palette
argument_list|)
operator|%
name|renderpal
operator|->
name|columns
condition|)
name|renderpal
operator|->
name|rows
operator|+=
literal|1
expr_stmt|;
name|renderpal
operator|->
name|cell_height
operator|=
name|MAX
argument_list|(
literal|4
argument_list|,
operator|(
operator|(
name|renderer
operator|->
name|height
operator|-
name|grid_width
operator|)
operator|/
name|renderpal
operator|->
name|rows
operator|)
argument_list|)
expr_stmt|;
if|if
condition|(
operator|!
name|renderpal
operator|->
name|draw_grid
condition|)
name|renderpal
operator|->
name|cell_height
operator|=
name|MIN
argument_list|(
name|renderpal
operator|->
name|cell_height
argument_list|,
name|renderpal
operator|->
name|cell_width
argument_list|)
expr_stmt|;
name|list
operator|=
name|gimp_palette_get_colors
argument_list|(
name|palette
argument_list|)
expr_stmt|;
if|if
condition|(
operator|!
name|renderer
operator|->
name|surface
condition|)
name|renderer
operator|->
name|surface
operator|=
name|cairo_image_surface_create
argument_list|(
name|CAIRO_FORMAT_RGB24
argument_list|,
name|renderer
operator|->
name|width
argument_list|,
name|renderer
operator|->
name|height
argument_list|)
expr_stmt|;
name|cairo_surface_flush
argument_list|(
name|renderer
operator|->
name|surface
argument_list|)
expr_stmt|;
name|row
operator|=
name|g_new
argument_list|(
name|guchar
argument_list|,
name|renderer
operator|->
name|width
operator|*
literal|4
argument_list|)
expr_stmt|;
name|dest
operator|=
name|cairo_image_surface_get_data
argument_list|(
name|renderer
operator|->
name|surface
argument_list|)
expr_stmt|;
name|dest_stride
operator|=
name|cairo_image_surface_get_stride
argument_list|(
name|renderer
operator|->
name|surface
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
name|renderer
operator|->
name|height
condition|;
name|y
operator|++
control|)
block|{
if|if
condition|(
operator|(
name|y
operator|%
name|renderpal
operator|->
name|cell_height
operator|)
operator|==
literal|0
condition|)
block|{
name|guchar
name|r
decl_stmt|,
name|g
decl_stmt|,
name|b
decl_stmt|;
name|gint
name|x
decl_stmt|;
name|gint
name|n
init|=
literal|0
decl_stmt|;
name|guchar
modifier|*
name|d
init|=
name|row
decl_stmt|;
name|memset
argument_list|(
name|row
argument_list|,
name|renderpal
operator|->
name|draw_grid
condition|?
literal|0
else|:
literal|255
argument_list|,
name|renderer
operator|->
name|width
operator|*
literal|4
argument_list|)
expr_stmt|;
name|r
operator|=
name|g
operator|=
name|b
operator|=
operator|(
name|renderpal
operator|->
name|draw_grid
condition|?
literal|0
else|:
literal|255
operator|)
expr_stmt|;
for|for
control|(
name|x
operator|=
literal|0
init|;
name|x
operator|<
name|renderer
operator|->
name|width
condition|;
name|x
operator|++
operator|,
name|d
operator|+=
literal|4
control|)
block|{
if|if
condition|(
operator|(
name|x
operator|%
name|renderpal
operator|->
name|cell_width
operator|)
operator|==
literal|0
condition|)
block|{
if|if
condition|(
name|list
operator|&&
name|n
operator|<
name|renderpal
operator|->
name|columns
operator|&&
name|renderer
operator|->
name|width
operator|-
name|x
operator|>=
name|renderpal
operator|->
name|cell_width
condition|)
block|{
name|GimpPaletteEntry
modifier|*
name|entry
init|=
name|list
operator|->
name|data
decl_stmt|;
name|list
operator|=
name|g_list_next
argument_list|(
name|list
argument_list|)
expr_stmt|;
name|n
operator|++
expr_stmt|;
name|gimp_rgb_get_uchar
argument_list|(
operator|&
name|entry
operator|->
name|color
argument_list|,
operator|&
name|r
argument_list|,
operator|&
name|g
argument_list|,
operator|&
name|b
argument_list|)
expr_stmt|;
block|}
else|else
block|{
name|r
operator|=
name|g
operator|=
name|b
operator|=
operator|(
name|renderpal
operator|->
name|draw_grid
condition|?
literal|0
else|:
literal|255
operator|)
expr_stmt|;
block|}
block|}
if|if
condition|(
name|renderpal
operator|->
name|draw_grid
operator|&&
operator|(
name|x
operator|%
name|renderpal
operator|->
name|cell_width
operator|)
operator|==
literal|0
condition|)
block|{
name|GIMP_CAIRO_RGB24_SET_PIXEL
argument_list|(
name|d
argument_list|,
literal|0
argument_list|,
literal|0
argument_list|,
literal|0
argument_list|)
expr_stmt|;
block|}
else|else
block|{
name|GIMP_CAIRO_RGB24_SET_PIXEL
argument_list|(
name|d
argument_list|,
name|r
argument_list|,
name|g
argument_list|,
name|b
argument_list|)
expr_stmt|;
block|}
block|}
block|}
if|if
condition|(
name|renderpal
operator|->
name|draw_grid
operator|&&
operator|(
name|y
operator|%
name|renderpal
operator|->
name|cell_height
operator|)
operator|==
literal|0
condition|)
block|{
name|memset
argument_list|(
name|dest
argument_list|,
literal|0
argument_list|,
name|renderer
operator|->
name|width
operator|*
literal|4
argument_list|)
expr_stmt|;
block|}
else|else
block|{
name|memcpy
argument_list|(
name|dest
argument_list|,
name|row
argument_list|,
name|renderer
operator|->
name|width
operator|*
literal|4
argument_list|)
expr_stmt|;
block|}
name|dest
operator|+=
name|dest_stride
expr_stmt|;
block|}
name|g_free
argument_list|(
name|row
argument_list|)
expr_stmt|;
name|cairo_surface_mark_dirty
argument_list|(
name|renderer
operator|->
name|surface
argument_list|)
expr_stmt|;
name|renderer
operator|->
name|needs_render
operator|=
name|FALSE
expr_stmt|;
block|}
end_function

begin_comment
comment|/*  public functions  */
end_comment

begin_function
name|void
DECL|function|gimp_view_renderer_palette_set_cell_size (GimpViewRendererPalette * renderer,gint cell_size)
name|gimp_view_renderer_palette_set_cell_size
parameter_list|(
name|GimpViewRendererPalette
modifier|*
name|renderer
parameter_list|,
name|gint
name|cell_size
parameter_list|)
block|{
name|g_return_if_fail
argument_list|(
name|GIMP_IS_VIEW_RENDERER_PALETTE
argument_list|(
name|renderer
argument_list|)
argument_list|)
expr_stmt|;
if|if
condition|(
name|cell_size
operator|!=
name|renderer
operator|->
name|cell_size
condition|)
block|{
name|renderer
operator|->
name|cell_size
operator|=
name|cell_size
expr_stmt|;
name|gimp_view_renderer_invalidate
argument_list|(
name|GIMP_VIEW_RENDERER
argument_list|(
name|renderer
argument_list|)
argument_list|)
expr_stmt|;
block|}
block|}
end_function

begin_function
name|void
DECL|function|gimp_view_renderer_palette_set_draw_grid (GimpViewRendererPalette * renderer,gboolean draw_grid)
name|gimp_view_renderer_palette_set_draw_grid
parameter_list|(
name|GimpViewRendererPalette
modifier|*
name|renderer
parameter_list|,
name|gboolean
name|draw_grid
parameter_list|)
block|{
name|g_return_if_fail
argument_list|(
name|GIMP_IS_VIEW_RENDERER_PALETTE
argument_list|(
name|renderer
argument_list|)
argument_list|)
expr_stmt|;
if|if
condition|(
name|draw_grid
operator|!=
name|renderer
operator|->
name|draw_grid
condition|)
block|{
name|renderer
operator|->
name|draw_grid
operator|=
name|draw_grid
condition|?
name|TRUE
else|:
name|FALSE
expr_stmt|;
name|gimp_view_renderer_invalidate
argument_list|(
name|GIMP_VIEW_RENDERER
argument_list|(
name|renderer
argument_list|)
argument_list|)
expr_stmt|;
block|}
block|}
end_function

end_unit

