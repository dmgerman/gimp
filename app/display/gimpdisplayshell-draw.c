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
file|<gtk/gtk.h>
end_include

begin_include
include|#
directive|include
file|"display-types.h"
end_include

begin_include
include|#
directive|include
file|"core/gimp-utils.h"
end_include

begin_include
include|#
directive|include
file|"core/gimpgrid.h"
end_include

begin_include
include|#
directive|include
file|"core/gimpimage.h"
end_include

begin_include
include|#
directive|include
file|"core/gimpimage-guides.h"
end_include

begin_include
include|#
directive|include
file|"core/gimplist.h"
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
file|"widgets/gimpwidgets-utils.h"
end_include

begin_include
include|#
directive|include
file|"gimpcanvas.h"
end_include

begin_include
include|#
directive|include
file|"gimpdisplay.h"
end_include

begin_include
include|#
directive|include
file|"gimpdisplayshell.h"
end_include

begin_include
include|#
directive|include
file|"gimpdisplayshell-appearance.h"
end_include

begin_include
include|#
directive|include
file|"gimpdisplayshell-draw.h"
end_include

begin_include
include|#
directive|include
file|"gimpdisplayshell-render.h"
end_include

begin_include
include|#
directive|include
file|"gimpdisplayshell-transform.h"
end_include

begin_comment
comment|/*  local function prototypes  */
end_comment

begin_function_decl
specifier|static
name|GdkGC
modifier|*
name|gimp_display_shell_get_grid_gc
parameter_list|(
name|GimpDisplayShell
modifier|*
name|shell
parameter_list|,
name|GimpGrid
modifier|*
name|grid
parameter_list|)
function_decl|;
end_function_decl

begin_comment
comment|/*  public functions  */
end_comment

begin_function
name|void
DECL|function|gimp_display_shell_draw_guide (GimpDisplayShell * shell,GimpGuide * guide,gboolean active)
name|gimp_display_shell_draw_guide
parameter_list|(
name|GimpDisplayShell
modifier|*
name|shell
parameter_list|,
name|GimpGuide
modifier|*
name|guide
parameter_list|,
name|gboolean
name|active
parameter_list|)
block|{
name|gint
name|x1
decl_stmt|,
name|x2
decl_stmt|;
name|gint
name|y1
decl_stmt|,
name|y2
decl_stmt|;
name|gint
name|x
decl_stmt|,
name|y
decl_stmt|;
name|gint
name|w
decl_stmt|,
name|h
decl_stmt|;
name|g_return_if_fail
argument_list|(
name|GIMP_IS_DISPLAY_SHELL
argument_list|(
name|shell
argument_list|)
argument_list|)
expr_stmt|;
name|g_return_if_fail
argument_list|(
name|guide
operator|!=
name|NULL
argument_list|)
expr_stmt|;
if|if
condition|(
name|guide
operator|->
name|position
operator|<
literal|0
condition|)
return|return;
name|gimp_display_shell_transform_xy
argument_list|(
name|shell
argument_list|,
literal|0
argument_list|,
literal|0
argument_list|,
operator|&
name|x1
argument_list|,
operator|&
name|y1
argument_list|,
name|FALSE
argument_list|)
expr_stmt|;
name|gimp_display_shell_transform_xy
argument_list|(
name|shell
argument_list|,
name|shell
operator|->
name|gdisp
operator|->
name|gimage
operator|->
name|width
argument_list|,
name|shell
operator|->
name|gdisp
operator|->
name|gimage
operator|->
name|height
argument_list|,
operator|&
name|x2
argument_list|,
operator|&
name|y2
argument_list|,
name|FALSE
argument_list|)
expr_stmt|;
name|gdk_drawable_get_size
argument_list|(
name|shell
operator|->
name|canvas
operator|->
name|window
argument_list|,
operator|&
name|w
argument_list|,
operator|&
name|h
argument_list|)
expr_stmt|;
if|if
condition|(
name|x1
operator|<
literal|0
condition|)
name|x1
operator|=
literal|0
expr_stmt|;
if|if
condition|(
name|y1
operator|<
literal|0
condition|)
name|y1
operator|=
literal|0
expr_stmt|;
if|if
condition|(
name|x2
operator|>
name|w
condition|)
name|x2
operator|=
name|w
expr_stmt|;
if|if
condition|(
name|y2
operator|>
name|h
condition|)
name|y2
operator|=
name|h
expr_stmt|;
switch|switch
condition|(
name|guide
operator|->
name|orientation
condition|)
block|{
case|case
name|GIMP_ORIENTATION_HORIZONTAL
case|:
name|gimp_display_shell_transform_xy
argument_list|(
name|shell
argument_list|,
literal|0
argument_list|,
name|guide
operator|->
name|position
argument_list|,
operator|&
name|x
argument_list|,
operator|&
name|y
argument_list|,
name|FALSE
argument_list|)
expr_stmt|;
name|y1
operator|=
name|y2
operator|=
name|y
expr_stmt|;
break|break;
case|case
name|GIMP_ORIENTATION_VERTICAL
case|:
name|gimp_display_shell_transform_xy
argument_list|(
name|shell
argument_list|,
name|guide
operator|->
name|position
argument_list|,
literal|0
argument_list|,
operator|&
name|x
argument_list|,
operator|&
name|y
argument_list|,
name|FALSE
argument_list|)
expr_stmt|;
name|x1
operator|=
name|x2
operator|=
name|x
expr_stmt|;
break|break;
case|case
name|GIMP_ORIENTATION_UNKNOWN
case|:
return|return;
block|}
name|gimp_canvas_draw_line
argument_list|(
name|GIMP_CANVAS
argument_list|(
name|shell
operator|->
name|canvas
argument_list|)
argument_list|,
operator|(
name|active
condition|?
name|GIMP_CANVAS_STYLE_GUIDE_ACTIVE
else|:
name|GIMP_CANVAS_STYLE_GUIDE_NORMAL
operator|)
argument_list|,
name|x1
argument_list|,
name|y1
argument_list|,
name|x2
argument_list|,
name|y2
argument_list|)
expr_stmt|;
block|}
end_function

begin_function
name|void
DECL|function|gimp_display_shell_draw_guides (GimpDisplayShell * shell)
name|gimp_display_shell_draw_guides
parameter_list|(
name|GimpDisplayShell
modifier|*
name|shell
parameter_list|)
block|{
name|g_return_if_fail
argument_list|(
name|GIMP_IS_DISPLAY_SHELL
argument_list|(
name|shell
argument_list|)
argument_list|)
expr_stmt|;
if|if
condition|(
name|gimp_display_shell_get_show_guides
argument_list|(
name|shell
argument_list|)
condition|)
block|{
name|GList
modifier|*
name|list
decl_stmt|;
for|for
control|(
name|list
operator|=
name|shell
operator|->
name|gdisp
operator|->
name|gimage
operator|->
name|guides
init|;
name|list
condition|;
name|list
operator|=
name|g_list_next
argument_list|(
name|list
argument_list|)
control|)
block|{
name|gimp_display_shell_draw_guide
argument_list|(
name|shell
argument_list|,
operator|(
name|GimpGuide
operator|*
operator|)
name|list
operator|->
name|data
argument_list|,
name|FALSE
argument_list|)
expr_stmt|;
block|}
block|}
block|}
end_function

begin_function
name|void
DECL|function|gimp_display_shell_draw_grid (GimpDisplayShell * shell,const GdkRectangle * area)
name|gimp_display_shell_draw_grid
parameter_list|(
name|GimpDisplayShell
modifier|*
name|shell
parameter_list|,
specifier|const
name|GdkRectangle
modifier|*
name|area
parameter_list|)
block|{
name|g_return_if_fail
argument_list|(
name|GIMP_IS_DISPLAY_SHELL
argument_list|(
name|shell
argument_list|)
argument_list|)
expr_stmt|;
name|g_return_if_fail
argument_list|(
name|area
operator|!=
name|NULL
argument_list|)
expr_stmt|;
if|if
condition|(
name|gimp_display_shell_get_show_grid
argument_list|(
name|shell
argument_list|)
condition|)
block|{
name|GimpGrid
modifier|*
name|grid
decl_stmt|;
name|GimpCanvas
modifier|*
name|canvas
decl_stmt|;
name|gdouble
name|x
decl_stmt|,
name|y
decl_stmt|;
name|gint
name|x0
decl_stmt|,
name|x1
decl_stmt|,
name|x2
decl_stmt|,
name|x3
decl_stmt|;
name|gint
name|y0
decl_stmt|,
name|y1
decl_stmt|,
name|y2
decl_stmt|,
name|y3
decl_stmt|;
name|gint
name|x_real
decl_stmt|,
name|y_real
decl_stmt|;
name|gint
name|x_offset
decl_stmt|,
name|y_offset
decl_stmt|;
name|gint
name|width
decl_stmt|,
name|height
decl_stmt|;
DECL|macro|CROSSHAIR
define|#
directive|define
name|CROSSHAIR
value|2
name|grid
operator|=
name|GIMP_GRID
argument_list|(
name|shell
operator|->
name|gdisp
operator|->
name|gimage
operator|->
name|grid
argument_list|)
expr_stmt|;
if|if
condition|(
operator|!
name|grid
condition|)
return|return;
name|g_return_if_fail
argument_list|(
name|grid
operator|->
name|xspacing
operator|>
literal|0
operator|&&
name|grid
operator|->
name|yspacing
operator|>
literal|0
argument_list|)
expr_stmt|;
name|x1
operator|=
name|area
operator|->
name|x
expr_stmt|;
name|y1
operator|=
name|area
operator|->
name|y
expr_stmt|;
name|x2
operator|=
name|area
operator|->
name|x
operator|+
name|area
operator|->
name|width
expr_stmt|;
name|y2
operator|=
name|area
operator|->
name|y
operator|+
name|area
operator|->
name|height
expr_stmt|;
name|width
operator|=
name|shell
operator|->
name|gdisp
operator|->
name|gimage
operator|->
name|width
expr_stmt|;
name|height
operator|=
name|shell
operator|->
name|gdisp
operator|->
name|gimage
operator|->
name|height
expr_stmt|;
name|x_offset
operator|=
name|grid
operator|->
name|xoffset
expr_stmt|;
while|while
condition|(
name|x_offset
operator|>
literal|0
condition|)
name|x_offset
operator|-=
name|grid
operator|->
name|xspacing
expr_stmt|;
name|y_offset
operator|=
name|grid
operator|->
name|yoffset
expr_stmt|;
while|while
condition|(
name|y_offset
operator|>
literal|0
condition|)
name|y_offset
operator|-=
name|grid
operator|->
name|yspacing
expr_stmt|;
name|canvas
operator|=
name|GIMP_CANVAS
argument_list|(
name|shell
operator|->
name|canvas
argument_list|)
expr_stmt|;
name|gimp_canvas_set_custom_gc
argument_list|(
name|canvas
argument_list|,
name|gimp_display_shell_get_grid_gc
argument_list|(
name|shell
argument_list|,
name|grid
argument_list|)
argument_list|)
expr_stmt|;
switch|switch
condition|(
name|grid
operator|->
name|style
condition|)
block|{
case|case
name|GIMP_GRID_DOTS
case|:
for|for
control|(
name|x
operator|=
name|x_offset
init|;
name|x
operator|<=
name|width
condition|;
name|x
operator|+=
name|grid
operator|->
name|xspacing
control|)
block|{
if|if
condition|(
name|x
operator|<
literal|0
condition|)
continue|continue;
name|gimp_display_shell_transform_xy
argument_list|(
name|shell
argument_list|,
name|x
argument_list|,
literal|0
argument_list|,
operator|&
name|x_real
argument_list|,
operator|&
name|y_real
argument_list|,
name|FALSE
argument_list|)
expr_stmt|;
if|if
condition|(
name|x_real
operator|<
name|x1
operator|||
name|x_real
operator|>=
name|x2
condition|)
continue|continue;
for|for
control|(
name|y
operator|=
name|y_offset
init|;
name|y
operator|<=
name|height
condition|;
name|y
operator|+=
name|grid
operator|->
name|yspacing
control|)
block|{
if|if
condition|(
name|y
operator|<
literal|0
condition|)
continue|continue;
name|gimp_display_shell_transform_xy
argument_list|(
name|shell
argument_list|,
name|x
argument_list|,
name|y
argument_list|,
operator|&
name|x_real
argument_list|,
operator|&
name|y_real
argument_list|,
name|FALSE
argument_list|)
expr_stmt|;
if|if
condition|(
name|y_real
operator|>=
name|y1
operator|&&
name|y_real
operator|<
name|y2
condition|)
name|gimp_canvas_draw_point
argument_list|(
name|GIMP_CANVAS
argument_list|(
name|shell
operator|->
name|canvas
argument_list|)
argument_list|,
name|GIMP_CANVAS_STYLE_CUSTOM
argument_list|,
name|x_real
argument_list|,
name|y_real
argument_list|)
expr_stmt|;
block|}
block|}
break|break;
case|case
name|GIMP_GRID_INTERSECTIONS
case|:
for|for
control|(
name|x
operator|=
name|x_offset
init|;
name|x
operator|<=
name|width
condition|;
name|x
operator|+=
name|grid
operator|->
name|xspacing
control|)
block|{
if|if
condition|(
name|x
operator|<
literal|0
condition|)
continue|continue;
name|gimp_display_shell_transform_xy
argument_list|(
name|shell
argument_list|,
name|x
argument_list|,
literal|0
argument_list|,
operator|&
name|x_real
argument_list|,
operator|&
name|y_real
argument_list|,
name|FALSE
argument_list|)
expr_stmt|;
if|if
condition|(
name|x_real
operator|+
name|CROSSHAIR
operator|<
name|x1
operator|||
name|x_real
operator|-
name|CROSSHAIR
operator|>=
name|x2
condition|)
continue|continue;
for|for
control|(
name|y
operator|=
name|y_offset
init|;
name|y
operator|<=
name|height
condition|;
name|y
operator|+=
name|grid
operator|->
name|yspacing
control|)
block|{
if|if
condition|(
name|y
operator|<
literal|0
condition|)
continue|continue;
name|gimp_display_shell_transform_xy
argument_list|(
name|shell
argument_list|,
name|x
argument_list|,
name|y
argument_list|,
operator|&
name|x_real
argument_list|,
operator|&
name|y_real
argument_list|,
name|FALSE
argument_list|)
expr_stmt|;
if|if
condition|(
name|y_real
operator|+
name|CROSSHAIR
operator|<
name|y1
operator|||
name|y_real
operator|-
name|CROSSHAIR
operator|>=
name|y2
condition|)
continue|continue;
if|if
condition|(
name|x_real
operator|>=
name|x1
operator|&&
name|x_real
operator|<
name|x2
condition|)
name|gimp_canvas_draw_line
argument_list|(
name|canvas
argument_list|,
name|GIMP_CANVAS_STYLE_CUSTOM
argument_list|,
name|x_real
argument_list|,
name|CLAMP
argument_list|(
name|y_real
operator|-
name|CROSSHAIR
argument_list|,
name|y1
argument_list|,
name|y2
operator|-
literal|1
argument_list|)
argument_list|,
name|x_real
argument_list|,
name|CLAMP
argument_list|(
name|y_real
operator|+
name|CROSSHAIR
argument_list|,
name|y1
argument_list|,
name|y2
operator|-
literal|1
argument_list|)
argument_list|)
expr_stmt|;
if|if
condition|(
name|y_real
operator|>=
name|y1
operator|&&
name|y_real
operator|<
name|y2
condition|)
name|gimp_canvas_draw_line
argument_list|(
name|canvas
argument_list|,
name|GIMP_CANVAS_STYLE_CUSTOM
argument_list|,
name|CLAMP
argument_list|(
name|x_real
operator|-
name|CROSSHAIR
argument_list|,
name|x1
argument_list|,
name|x2
operator|-
literal|1
argument_list|)
argument_list|,
name|y_real
argument_list|,
name|CLAMP
argument_list|(
name|x_real
operator|+
name|CROSSHAIR
argument_list|,
name|x1
argument_list|,
name|x2
operator|-
literal|1
argument_list|)
argument_list|,
name|y_real
argument_list|)
expr_stmt|;
block|}
block|}
break|break;
case|case
name|GIMP_GRID_ON_OFF_DASH
case|:
case|case
name|GIMP_GRID_DOUBLE_DASH
case|:
case|case
name|GIMP_GRID_SOLID
case|:
name|gimp_display_shell_transform_xy
argument_list|(
name|shell
argument_list|,
literal|0
argument_list|,
literal|0
argument_list|,
operator|&
name|x0
argument_list|,
operator|&
name|y0
argument_list|,
name|FALSE
argument_list|)
expr_stmt|;
name|gimp_display_shell_transform_xy
argument_list|(
name|shell
argument_list|,
name|width
argument_list|,
name|height
argument_list|,
operator|&
name|x3
argument_list|,
operator|&
name|y3
argument_list|,
name|FALSE
argument_list|)
expr_stmt|;
for|for
control|(
name|x
operator|=
name|x_offset
init|;
name|x
operator|<
name|width
condition|;
name|x
operator|+=
name|grid
operator|->
name|xspacing
control|)
block|{
if|if
condition|(
name|x
operator|<
literal|0
condition|)
continue|continue;
name|gimp_display_shell_transform_xy
argument_list|(
name|shell
argument_list|,
name|x
argument_list|,
literal|0
argument_list|,
operator|&
name|x_real
argument_list|,
operator|&
name|y_real
argument_list|,
name|FALSE
argument_list|)
expr_stmt|;
if|if
condition|(
name|x_real
operator|>=
name|x1
operator|&&
name|x_real
operator|<
name|x2
condition|)
name|gimp_canvas_draw_line
argument_list|(
name|canvas
argument_list|,
name|GIMP_CANVAS_STYLE_CUSTOM
argument_list|,
name|x_real
argument_list|,
name|y0
argument_list|,
name|x_real
argument_list|,
name|y3
operator|-
literal|1
argument_list|)
expr_stmt|;
block|}
for|for
control|(
name|y
operator|=
name|y_offset
init|;
name|y
operator|<
name|height
condition|;
name|y
operator|+=
name|grid
operator|->
name|yspacing
control|)
block|{
if|if
condition|(
name|y
operator|<
literal|0
condition|)
continue|continue;
name|gimp_display_shell_transform_xy
argument_list|(
name|shell
argument_list|,
literal|0
argument_list|,
name|y
argument_list|,
operator|&
name|x_real
argument_list|,
operator|&
name|y_real
argument_list|,
name|FALSE
argument_list|)
expr_stmt|;
if|if
condition|(
name|y_real
operator|>=
name|y1
operator|&&
name|y_real
operator|<
name|y2
condition|)
name|gimp_canvas_draw_line
argument_list|(
name|canvas
argument_list|,
name|GIMP_CANVAS_STYLE_CUSTOM
argument_list|,
name|x0
argument_list|,
name|y_real
argument_list|,
name|x3
operator|-
literal|1
argument_list|,
name|y_real
argument_list|)
expr_stmt|;
block|}
break|break;
block|}
name|gimp_canvas_set_custom_gc
argument_list|(
name|canvas
argument_list|,
name|NULL
argument_list|)
expr_stmt|;
block|}
block|}
end_function

begin_function
name|void
DECL|function|gimp_display_shell_draw_vector (GimpDisplayShell * shell,GimpVectors * vectors)
name|gimp_display_shell_draw_vector
parameter_list|(
name|GimpDisplayShell
modifier|*
name|shell
parameter_list|,
name|GimpVectors
modifier|*
name|vectors
parameter_list|)
block|{
name|GimpStroke
modifier|*
name|stroke
init|=
name|NULL
decl_stmt|;
name|g_return_if_fail
argument_list|(
name|GIMP_IS_DISPLAY_SHELL
argument_list|(
name|shell
argument_list|)
argument_list|)
expr_stmt|;
name|g_return_if_fail
argument_list|(
name|GIMP_IS_VECTORS
argument_list|(
name|vectors
argument_list|)
argument_list|)
expr_stmt|;
while|while
condition|(
operator|(
name|stroke
operator|=
name|gimp_vectors_stroke_get_next
argument_list|(
name|vectors
argument_list|,
name|stroke
argument_list|)
operator|)
condition|)
block|{
name|GArray
modifier|*
name|coords
decl_stmt|;
name|gboolean
name|closed
decl_stmt|;
name|coords
operator|=
name|gimp_stroke_interpolate
argument_list|(
name|stroke
argument_list|,
literal|1.0
argument_list|,
operator|&
name|closed
argument_list|)
expr_stmt|;
if|if
condition|(
name|coords
operator|&&
name|coords
operator|->
name|len
condition|)
block|{
name|GimpCoords
modifier|*
name|coord
decl_stmt|;
name|GdkPoint
modifier|*
name|gdk_coords
decl_stmt|;
name|gint
name|i
decl_stmt|;
name|gint
name|sx
decl_stmt|,
name|sy
decl_stmt|;
name|gdk_coords
operator|=
name|g_new
argument_list|(
name|GdkPoint
argument_list|,
name|coords
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
name|coords
operator|->
name|len
condition|;
name|i
operator|++
control|)
block|{
name|coord
operator|=
operator|&
name|g_array_index
argument_list|(
name|coords
argument_list|,
name|GimpCoords
argument_list|,
name|i
argument_list|)
expr_stmt|;
name|gimp_display_shell_transform_xy
argument_list|(
name|shell
argument_list|,
name|coord
operator|->
name|x
argument_list|,
name|coord
operator|->
name|y
argument_list|,
operator|&
name|sx
argument_list|,
operator|&
name|sy
argument_list|,
name|FALSE
argument_list|)
expr_stmt|;
name|gdk_coords
index|[
name|i
index|]
operator|.
name|x
operator|=
name|sx
expr_stmt|;
name|gdk_coords
index|[
name|i
index|]
operator|.
name|y
operator|=
name|sy
expr_stmt|;
block|}
name|gimp_canvas_draw_lines
argument_list|(
name|GIMP_CANVAS
argument_list|(
name|shell
operator|->
name|canvas
argument_list|)
argument_list|,
name|GIMP_CANVAS_STYLE_XOR
argument_list|,
name|gdk_coords
argument_list|,
name|coords
operator|->
name|len
argument_list|)
expr_stmt|;
name|g_free
argument_list|(
name|gdk_coords
argument_list|)
expr_stmt|;
block|}
if|if
condition|(
name|coords
condition|)
name|g_array_free
argument_list|(
name|coords
argument_list|,
name|TRUE
argument_list|)
expr_stmt|;
block|}
block|}
end_function

begin_function
name|void
DECL|function|gimp_display_shell_draw_vectors (GimpDisplayShell * shell)
name|gimp_display_shell_draw_vectors
parameter_list|(
name|GimpDisplayShell
modifier|*
name|shell
parameter_list|)
block|{
name|g_return_if_fail
argument_list|(
name|GIMP_IS_DISPLAY_SHELL
argument_list|(
name|shell
argument_list|)
argument_list|)
expr_stmt|;
if|if
condition|(
name|TRUE
comment|/* gimp_display_shell_get_show_vectors (shell) */
condition|)
block|{
name|GList
modifier|*
name|list
decl_stmt|;
for|for
control|(
name|list
operator|=
name|GIMP_LIST
argument_list|(
name|shell
operator|->
name|gdisp
operator|->
name|gimage
operator|->
name|vectors
argument_list|)
operator|->
name|list
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
name|GimpVectors
modifier|*
name|vectors
init|=
name|list
operator|->
name|data
decl_stmt|;
if|if
condition|(
name|gimp_item_get_visible
argument_list|(
name|GIMP_ITEM
argument_list|(
name|vectors
argument_list|)
argument_list|)
condition|)
name|gimp_display_shell_draw_vector
argument_list|(
name|shell
argument_list|,
name|vectors
argument_list|)
expr_stmt|;
block|}
block|}
block|}
end_function

begin_function
name|void
DECL|function|gimp_display_shell_draw_cursor (GimpDisplayShell * shell)
name|gimp_display_shell_draw_cursor
parameter_list|(
name|GimpDisplayShell
modifier|*
name|shell
parameter_list|)
block|{
name|g_return_if_fail
argument_list|(
name|GIMP_IS_DISPLAY_SHELL
argument_list|(
name|shell
argument_list|)
argument_list|)
expr_stmt|;
if|if
condition|(
name|shell
operator|->
name|have_cursor
condition|)
name|gimp_canvas_draw_cursor
argument_list|(
name|GIMP_CANVAS
argument_list|(
name|shell
operator|->
name|canvas
argument_list|)
argument_list|,
name|shell
operator|->
name|cursor_x
argument_list|,
name|shell
operator|->
name|cursor_y
argument_list|)
expr_stmt|;
block|}
end_function

begin_function
name|void
DECL|function|gimp_display_shell_draw_area (GimpDisplayShell * shell,gint x,gint y,gint w,gint h)
name|gimp_display_shell_draw_area
parameter_list|(
name|GimpDisplayShell
modifier|*
name|shell
parameter_list|,
name|gint
name|x
parameter_list|,
name|gint
name|y
parameter_list|,
name|gint
name|w
parameter_list|,
name|gint
name|h
parameter_list|)
block|{
name|gint
name|sx
decl_stmt|,
name|sy
decl_stmt|;
name|gint
name|sw
decl_stmt|,
name|sh
decl_stmt|;
name|g_return_if_fail
argument_list|(
name|GIMP_IS_DISPLAY_SHELL
argument_list|(
name|shell
argument_list|)
argument_list|)
expr_stmt|;
comment|/*  the image's size in display coordinates  */
name|sx
operator|=
name|shell
operator|->
name|disp_xoffset
operator|>
literal|0
condition|?
name|shell
operator|->
name|disp_xoffset
else|:
operator|-
name|shell
operator|->
name|offset_x
expr_stmt|;
name|sy
operator|=
name|shell
operator|->
name|disp_yoffset
operator|>
literal|0
condition|?
name|shell
operator|->
name|disp_yoffset
else|:
operator|-
name|shell
operator|->
name|offset_y
expr_stmt|;
name|sw
operator|=
name|SCALEX
argument_list|(
name|shell
argument_list|,
name|shell
operator|->
name|gdisp
operator|->
name|gimage
operator|->
name|width
argument_list|)
expr_stmt|;
name|sh
operator|=
name|SCALEY
argument_list|(
name|shell
argument_list|,
name|shell
operator|->
name|gdisp
operator|->
name|gimage
operator|->
name|height
argument_list|)
expr_stmt|;
comment|/*  check if the passed in area intersects with    *  both the display and the image    */
if|if
condition|(
name|gimp_rectangle_intersect
argument_list|(
name|x
argument_list|,
name|y
argument_list|,
name|w
argument_list|,
name|h
argument_list|,
literal|0
argument_list|,
literal|0
argument_list|,
name|shell
operator|->
name|disp_width
argument_list|,
name|shell
operator|->
name|disp_height
argument_list|,
operator|&
name|x
argument_list|,
operator|&
name|y
argument_list|,
operator|&
name|w
argument_list|,
operator|&
name|h
argument_list|)
operator|&&
name|gimp_rectangle_intersect
argument_list|(
name|x
argument_list|,
name|y
argument_list|,
name|w
argument_list|,
name|h
argument_list|,
name|sx
argument_list|,
name|sy
argument_list|,
name|sw
argument_list|,
name|sh
argument_list|,
operator|&
name|x
argument_list|,
operator|&
name|y
argument_list|,
operator|&
name|w
argument_list|,
operator|&
name|h
argument_list|)
condition|)
block|{
name|gint
name|x2
decl_stmt|,
name|y2
decl_stmt|;
name|gint
name|i
decl_stmt|,
name|j
decl_stmt|;
name|x2
operator|=
name|x
operator|+
name|w
expr_stmt|;
name|y2
operator|=
name|y
operator|+
name|h
expr_stmt|;
comment|/*  display the image in RENDER_BUF_WIDTH x RENDER_BUF_HEIGHT        *  sized chunks        */
for|for
control|(
name|i
operator|=
name|y
init|;
name|i
operator|<
name|y2
condition|;
name|i
operator|+=
name|GIMP_DISPLAY_SHELL_RENDER_BUF_HEIGHT
control|)
block|{
for|for
control|(
name|j
operator|=
name|x
init|;
name|j
operator|<
name|x2
condition|;
name|j
operator|+=
name|GIMP_DISPLAY_SHELL_RENDER_BUF_WIDTH
control|)
block|{
name|gint
name|dx
decl_stmt|,
name|dy
decl_stmt|;
name|dx
operator|=
name|MIN
argument_list|(
name|x2
operator|-
name|j
argument_list|,
name|GIMP_DISPLAY_SHELL_RENDER_BUF_WIDTH
argument_list|)
expr_stmt|;
name|dy
operator|=
name|MIN
argument_list|(
name|y2
operator|-
name|i
argument_list|,
name|GIMP_DISPLAY_SHELL_RENDER_BUF_HEIGHT
argument_list|)
expr_stmt|;
name|gimp_display_shell_render
argument_list|(
name|shell
argument_list|,
name|j
operator|-
name|shell
operator|->
name|disp_xoffset
argument_list|,
name|i
operator|-
name|shell
operator|->
name|disp_yoffset
argument_list|,
name|dx
argument_list|,
name|dy
argument_list|)
expr_stmt|;
ifdef|#
directive|ifdef
name|STRESS_TEST
comment|/* Invalidate the projection just after we render it! */
name|gimp_image_invalidate_without_render
argument_list|(
name|shell
operator|->
name|gdisp
operator|->
name|gimage
argument_list|,
name|j
operator|-
name|shell
operator|->
name|disp_xoffset
argument_list|,
name|i
operator|-
name|shell
operator|->
name|disp_yoffset
argument_list|,
name|dx
argument_list|,
name|dy
argument_list|,
literal|0
argument_list|,
literal|0
argument_list|,
literal|0
argument_list|,
literal|0
argument_list|)
expr_stmt|;
endif|#
directive|endif
block|}
block|}
block|}
block|}
end_function

begin_comment
comment|/*  private functions  */
end_comment

begin_function
specifier|static
name|GdkGC
modifier|*
DECL|function|gimp_display_shell_get_grid_gc (GimpDisplayShell * shell,GimpGrid * grid)
name|gimp_display_shell_get_grid_gc
parameter_list|(
name|GimpDisplayShell
modifier|*
name|shell
parameter_list|,
name|GimpGrid
modifier|*
name|grid
parameter_list|)
block|{
name|GdkGCValues
name|values
decl_stmt|;
name|GdkColor
name|fg
decl_stmt|,
name|bg
decl_stmt|;
if|if
condition|(
name|shell
operator|->
name|grid_gc
condition|)
return|return
name|shell
operator|->
name|grid_gc
return|;
switch|switch
condition|(
name|grid
operator|->
name|style
condition|)
block|{
case|case
name|GIMP_GRID_ON_OFF_DASH
case|:
name|values
operator|.
name|line_style
operator|=
name|GDK_LINE_ON_OFF_DASH
expr_stmt|;
break|break;
case|case
name|GIMP_GRID_DOUBLE_DASH
case|:
name|values
operator|.
name|line_style
operator|=
name|GDK_LINE_DOUBLE_DASH
expr_stmt|;
break|break;
case|case
name|GIMP_GRID_DOTS
case|:
case|case
name|GIMP_GRID_INTERSECTIONS
case|:
case|case
name|GIMP_GRID_SOLID
case|:
name|values
operator|.
name|line_style
operator|=
name|GDK_LINE_SOLID
expr_stmt|;
break|break;
block|}
name|values
operator|.
name|join_style
operator|=
name|GDK_JOIN_MITER
expr_stmt|;
name|shell
operator|->
name|grid_gc
operator|=
name|gdk_gc_new_with_values
argument_list|(
name|shell
operator|->
name|canvas
operator|->
name|window
argument_list|,
operator|&
name|values
argument_list|,
operator|(
name|GDK_GC_LINE_STYLE
operator||
name|GDK_GC_JOIN_STYLE
operator|)
argument_list|)
expr_stmt|;
name|gimp_rgb_get_gdk_color
argument_list|(
operator|&
name|grid
operator|->
name|fgcolor
argument_list|,
operator|&
name|fg
argument_list|)
expr_stmt|;
name|gimp_rgb_get_gdk_color
argument_list|(
operator|&
name|grid
operator|->
name|bgcolor
argument_list|,
operator|&
name|bg
argument_list|)
expr_stmt|;
name|gdk_gc_set_rgb_fg_color
argument_list|(
name|shell
operator|->
name|grid_gc
argument_list|,
operator|&
name|fg
argument_list|)
expr_stmt|;
name|gdk_gc_set_rgb_bg_color
argument_list|(
name|shell
operator|->
name|grid_gc
argument_list|,
operator|&
name|bg
argument_list|)
expr_stmt|;
return|return
name|shell
operator|->
name|grid_gc
return|;
block|}
end_function

end_unit

