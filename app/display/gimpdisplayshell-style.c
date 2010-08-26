begin_unit|revision:0.9.5;language:C;cregit-version:0.0.1
begin_comment
comment|/* GIMP - The GNU Image Manipulation Program  * Copyright (C) 1995 Spencer Kimball and Peter Mattis  *  * gimpdisplayshell-style.c  * Copyright (C) 2010  Michael Natterer<mitch@gimp.org>  *  * This program is free software: you can redistribute it and/or modify  * it under the terms of the GNU General Public License as published by  * the Free Software Foundation; either version 3 of the License, or  * (at your option) any later version.  *  * This program is distributed in the hope that it will be useful,  * but WITHOUT ANY WARRANTY; without even the implied warranty of  * MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the  * GNU General Public License for more details.  *  * You should have received a copy of the GNU General Public License  * along with this program.  If not, see<http://www.gnu.org/licenses/>.  */
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
file|"libgimpwidgets/gimpwidgets.h"
end_include

begin_include
include|#
directive|include
file|"display-types.h"
end_include

begin_include
include|#
directive|include
file|"core/gimpcontext.h"
end_include

begin_include
include|#
directive|include
file|"core/gimpgrid.h"
end_include

begin_include
include|#
directive|include
file|"core/gimplayermask.h"
end_include

begin_include
include|#
directive|include
file|"gimpdisplayshell.h"
end_include

begin_include
include|#
directive|include
file|"gimpdisplayshell-style.h"
end_include

begin_decl_stmt
DECL|variable|guide_normal_fg
specifier|static
specifier|const
name|GimpRGB
name|guide_normal_fg
init|=
block|{
literal|0.0
block|,
literal|0.0
block|,
literal|0.0
block|,
literal|1.0
block|}
decl_stmt|;
end_decl_stmt

begin_decl_stmt
DECL|variable|guide_normal_bg
specifier|static
specifier|const
name|GimpRGB
name|guide_normal_bg
init|=
block|{
literal|0.0
block|,
literal|0.5
block|,
literal|1.0
block|,
literal|1.0
block|}
decl_stmt|;
end_decl_stmt

begin_decl_stmt
DECL|variable|guide_active_fg
specifier|static
specifier|const
name|GimpRGB
name|guide_active_fg
init|=
block|{
literal|0.0
block|,
literal|0.0
block|,
literal|0.0
block|,
literal|1.0
block|}
decl_stmt|;
end_decl_stmt

begin_decl_stmt
DECL|variable|guide_active_bg
specifier|static
specifier|const
name|GimpRGB
name|guide_active_bg
init|=
block|{
literal|1.0
block|,
literal|0.0
block|,
literal|0.0
block|,
literal|1.0
block|}
decl_stmt|;
end_decl_stmt

begin_decl_stmt
DECL|variable|sample_point_normal
specifier|static
specifier|const
name|GimpRGB
name|sample_point_normal
init|=
block|{
literal|0.0
block|,
literal|0.5
block|,
literal|1.0
block|,
literal|1.0
block|}
decl_stmt|;
end_decl_stmt

begin_decl_stmt
DECL|variable|sample_point_active
specifier|static
specifier|const
name|GimpRGB
name|sample_point_active
init|=
block|{
literal|1.0
block|,
literal|0.0
block|,
literal|0.0
block|,
literal|1.0
block|}
decl_stmt|;
end_decl_stmt

begin_decl_stmt
DECL|variable|layer_fg
specifier|static
specifier|const
name|GimpRGB
name|layer_fg
init|=
block|{
literal|0.0
block|,
literal|0.0
block|,
literal|0.0
block|,
literal|1.0
block|}
decl_stmt|;
end_decl_stmt

begin_decl_stmt
DECL|variable|layer_bg
specifier|static
specifier|const
name|GimpRGB
name|layer_bg
init|=
block|{
literal|1.0
block|,
literal|1.0
block|,
literal|0.0
block|,
literal|1.0
block|}
decl_stmt|;
end_decl_stmt

begin_decl_stmt
DECL|variable|layer_group_fg
specifier|static
specifier|const
name|GimpRGB
name|layer_group_fg
init|=
block|{
literal|0.0
block|,
literal|0.0
block|,
literal|0.0
block|,
literal|1.0
block|}
decl_stmt|;
end_decl_stmt

begin_decl_stmt
DECL|variable|layer_group_bg
specifier|static
specifier|const
name|GimpRGB
name|layer_group_bg
init|=
block|{
literal|0.0
block|,
literal|1.0
block|,
literal|1.0
block|,
literal|1.0
block|}
decl_stmt|;
end_decl_stmt

begin_decl_stmt
DECL|variable|layer_mask_fg
specifier|static
specifier|const
name|GimpRGB
name|layer_mask_fg
init|=
block|{
literal|0.0
block|,
literal|0.0
block|,
literal|0.0
block|,
literal|1.0
block|}
decl_stmt|;
end_decl_stmt

begin_decl_stmt
DECL|variable|layer_mask_bg
specifier|static
specifier|const
name|GimpRGB
name|layer_mask_bg
init|=
block|{
literal|0.0
block|,
literal|1.0
block|,
literal|0.0
block|,
literal|1.0
block|}
decl_stmt|;
end_decl_stmt

begin_decl_stmt
DECL|variable|selection_out_fg
specifier|static
specifier|const
name|GimpRGB
name|selection_out_fg
init|=
block|{
literal|1.0
block|,
literal|1.0
block|,
literal|1.0
block|,
literal|1.0
block|}
decl_stmt|;
end_decl_stmt

begin_decl_stmt
DECL|variable|selection_out_bg
specifier|static
specifier|const
name|GimpRGB
name|selection_out_bg
init|=
block|{
literal|0.5
block|,
literal|0.5
block|,
literal|0.5
block|,
literal|1.0
block|}
decl_stmt|;
end_decl_stmt

begin_decl_stmt
DECL|variable|selection_in_fg
specifier|static
specifier|const
name|GimpRGB
name|selection_in_fg
init|=
block|{
literal|0.0
block|,
literal|0.0
block|,
literal|0.0
block|,
literal|1.0
block|}
decl_stmt|;
end_decl_stmt

begin_decl_stmt
DECL|variable|selection_in_bg
specifier|static
specifier|const
name|GimpRGB
name|selection_in_bg
init|=
block|{
literal|1.0
block|,
literal|1.0
block|,
literal|1.0
block|,
literal|1.0
block|}
decl_stmt|;
end_decl_stmt

begin_comment
comment|/*  local function prototypes  */
end_comment

begin_function_decl
specifier|static
name|void
name|gimp_display_shell_set_stipple_style
parameter_list|(
name|cairo_t
modifier|*
name|cr
parameter_list|,
specifier|const
name|GimpRGB
modifier|*
name|fg
parameter_list|,
specifier|const
name|GimpRGB
modifier|*
name|bg
parameter_list|,
name|gint
name|index
parameter_list|)
function_decl|;
end_function_decl

begin_comment
comment|/*  public functions  */
end_comment

begin_function
name|void
DECL|function|gimp_display_shell_set_guide_style (GimpDisplayShell * shell,cairo_t * cr,gboolean active)
name|gimp_display_shell_set_guide_style
parameter_list|(
name|GimpDisplayShell
modifier|*
name|shell
parameter_list|,
name|cairo_t
modifier|*
name|cr
parameter_list|,
name|gboolean
name|active
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
name|cr
operator|!=
name|NULL
argument_list|)
expr_stmt|;
name|cairo_set_line_width
argument_list|(
name|cr
argument_list|,
literal|1.0
argument_list|)
expr_stmt|;
if|if
condition|(
name|active
condition|)
name|gimp_display_shell_set_stipple_style
argument_list|(
name|cr
argument_list|,
operator|&
name|guide_active_fg
argument_list|,
operator|&
name|guide_active_bg
argument_list|,
literal|0
argument_list|)
expr_stmt|;
else|else
name|gimp_display_shell_set_stipple_style
argument_list|(
name|cr
argument_list|,
operator|&
name|guide_normal_fg
argument_list|,
operator|&
name|guide_normal_bg
argument_list|,
literal|0
argument_list|)
expr_stmt|;
block|}
end_function

begin_function
name|void
DECL|function|gimp_display_shell_set_sample_point_style (GimpDisplayShell * shell,cairo_t * cr,gboolean active)
name|gimp_display_shell_set_sample_point_style
parameter_list|(
name|GimpDisplayShell
modifier|*
name|shell
parameter_list|,
name|cairo_t
modifier|*
name|cr
parameter_list|,
name|gboolean
name|active
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
name|cr
operator|!=
name|NULL
argument_list|)
expr_stmt|;
name|cairo_set_line_width
argument_list|(
name|cr
argument_list|,
literal|1.0
argument_list|)
expr_stmt|;
if|if
condition|(
name|active
condition|)
name|cairo_set_source_rgb
argument_list|(
name|cr
argument_list|,
name|sample_point_active
operator|.
name|r
argument_list|,
name|sample_point_active
operator|.
name|g
argument_list|,
name|sample_point_active
operator|.
name|b
argument_list|)
expr_stmt|;
else|else
name|cairo_set_source_rgb
argument_list|(
name|cr
argument_list|,
name|sample_point_normal
operator|.
name|r
argument_list|,
name|sample_point_normal
operator|.
name|g
argument_list|,
name|sample_point_normal
operator|.
name|b
argument_list|)
expr_stmt|;
block|}
end_function

begin_function
name|void
DECL|function|gimp_display_shell_set_grid_style (GimpDisplayShell * shell,cairo_t * cr,GimpGrid * grid)
name|gimp_display_shell_set_grid_style
parameter_list|(
name|GimpDisplayShell
modifier|*
name|shell
parameter_list|,
name|cairo_t
modifier|*
name|cr
parameter_list|,
name|GimpGrid
modifier|*
name|grid
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
name|cr
operator|!=
name|NULL
argument_list|)
expr_stmt|;
name|g_return_if_fail
argument_list|(
name|GIMP_IS_GRID
argument_list|(
name|grid
argument_list|)
argument_list|)
expr_stmt|;
name|cairo_set_line_width
argument_list|(
name|cr
argument_list|,
literal|1.0
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
name|GIMP_GRID_ON_OFF_DASH
case|:
case|case
name|GIMP_GRID_DOUBLE_DASH
case|:
if|if
condition|(
name|grid
operator|->
name|style
operator|==
name|GIMP_GRID_DOUBLE_DASH
condition|)
block|{
name|gimp_display_shell_set_stipple_style
argument_list|(
name|cr
argument_list|,
operator|&
name|grid
operator|->
name|fgcolor
argument_list|,
operator|&
name|grid
operator|->
name|bgcolor
argument_list|,
literal|0
argument_list|)
expr_stmt|;
block|}
else|else
block|{
name|GimpRGB
name|bg
init|=
block|{
literal|0.0
block|,
literal|0.0
block|,
literal|0.0
block|,
literal|0.0
block|}
decl_stmt|;
name|gimp_display_shell_set_stipple_style
argument_list|(
name|cr
argument_list|,
operator|&
name|grid
operator|->
name|fgcolor
argument_list|,
operator|&
name|bg
argument_list|,
literal|0
argument_list|)
expr_stmt|;
block|}
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
name|cairo_set_source_rgb
argument_list|(
name|cr
argument_list|,
name|grid
operator|->
name|fgcolor
operator|.
name|r
argument_list|,
name|grid
operator|->
name|fgcolor
operator|.
name|g
argument_list|,
name|grid
operator|->
name|fgcolor
operator|.
name|b
argument_list|)
expr_stmt|;
break|break;
block|}
block|}
end_function

begin_function
name|void
DECL|function|gimp_display_shell_set_cursor_style (GimpDisplayShell * shell,cairo_t * cr)
name|gimp_display_shell_set_cursor_style
parameter_list|(
name|GimpDisplayShell
modifier|*
name|shell
parameter_list|,
name|cairo_t
modifier|*
name|cr
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
name|cr
operator|!=
name|NULL
argument_list|)
expr_stmt|;
name|cairo_set_line_width
argument_list|(
name|cr
argument_list|,
literal|1.0
argument_list|)
expr_stmt|;
name|cairo_set_line_cap
argument_list|(
name|cr
argument_list|,
name|CAIRO_LINE_CAP_SQUARE
argument_list|)
expr_stmt|;
block|}
end_function

begin_function
name|void
DECL|function|gimp_display_shell_set_pen_style (GimpDisplayShell * shell,cairo_t * cr,GimpContext * context,GimpActiveColor active,gint width)
name|gimp_display_shell_set_pen_style
parameter_list|(
name|GimpDisplayShell
modifier|*
name|shell
parameter_list|,
name|cairo_t
modifier|*
name|cr
parameter_list|,
name|GimpContext
modifier|*
name|context
parameter_list|,
name|GimpActiveColor
name|active
parameter_list|,
name|gint
name|width
parameter_list|)
block|{
name|GimpRGB
name|rgb
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
name|cr
operator|!=
name|NULL
argument_list|)
expr_stmt|;
name|g_return_if_fail
argument_list|(
name|GIMP_IS_CONTEXT
argument_list|(
name|context
argument_list|)
argument_list|)
expr_stmt|;
name|cairo_set_antialias
argument_list|(
name|cr
argument_list|,
name|CAIRO_ANTIALIAS_NONE
argument_list|)
expr_stmt|;
name|cairo_set_line_width
argument_list|(
name|cr
argument_list|,
name|width
argument_list|)
expr_stmt|;
name|cairo_set_line_cap
argument_list|(
name|cr
argument_list|,
name|CAIRO_LINE_CAP_ROUND
argument_list|)
expr_stmt|;
name|cairo_set_line_join
argument_list|(
name|cr
argument_list|,
name|CAIRO_LINE_JOIN_ROUND
argument_list|)
expr_stmt|;
switch|switch
condition|(
name|active
condition|)
block|{
case|case
name|GIMP_ACTIVE_COLOR_FOREGROUND
case|:
name|gimp_context_get_foreground
argument_list|(
name|context
argument_list|,
operator|&
name|rgb
argument_list|)
expr_stmt|;
break|break;
case|case
name|GIMP_ACTIVE_COLOR_BACKGROUND
case|:
name|gimp_context_get_background
argument_list|(
name|context
argument_list|,
operator|&
name|rgb
argument_list|)
expr_stmt|;
break|break;
block|}
name|cairo_set_source_rgb
argument_list|(
name|cr
argument_list|,
name|rgb
operator|.
name|r
argument_list|,
name|rgb
operator|.
name|g
argument_list|,
name|rgb
operator|.
name|b
argument_list|)
expr_stmt|;
block|}
end_function

begin_function
name|void
DECL|function|gimp_display_shell_set_layer_style (GimpDisplayShell * shell,cairo_t * cr,GimpDrawable * drawable)
name|gimp_display_shell_set_layer_style
parameter_list|(
name|GimpDisplayShell
modifier|*
name|shell
parameter_list|,
name|cairo_t
modifier|*
name|cr
parameter_list|,
name|GimpDrawable
modifier|*
name|drawable
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
name|cr
operator|!=
name|NULL
argument_list|)
expr_stmt|;
name|g_return_if_fail
argument_list|(
name|GIMP_IS_DRAWABLE
argument_list|(
name|drawable
argument_list|)
argument_list|)
expr_stmt|;
name|cairo_set_line_width
argument_list|(
name|cr
argument_list|,
literal|1.0
argument_list|)
expr_stmt|;
if|if
condition|(
name|GIMP_IS_LAYER_MASK
argument_list|(
name|drawable
argument_list|)
condition|)
block|{
name|gimp_display_shell_set_stipple_style
argument_list|(
name|cr
argument_list|,
operator|&
name|layer_mask_fg
argument_list|,
operator|&
name|layer_mask_bg
argument_list|,
literal|0
argument_list|)
expr_stmt|;
block|}
elseif|else
if|if
condition|(
name|gimp_viewable_get_children
argument_list|(
name|GIMP_VIEWABLE
argument_list|(
name|drawable
argument_list|)
argument_list|)
condition|)
block|{
name|gimp_display_shell_set_stipple_style
argument_list|(
name|cr
argument_list|,
operator|&
name|layer_group_fg
argument_list|,
operator|&
name|layer_group_bg
argument_list|,
literal|0
argument_list|)
expr_stmt|;
block|}
else|else
block|{
name|gimp_display_shell_set_stipple_style
argument_list|(
name|cr
argument_list|,
operator|&
name|layer_fg
argument_list|,
operator|&
name|layer_bg
argument_list|,
literal|0
argument_list|)
expr_stmt|;
block|}
block|}
end_function

begin_function
name|void
DECL|function|gimp_display_shell_set_selection_out_style (GimpDisplayShell * shell,cairo_t * cr)
name|gimp_display_shell_set_selection_out_style
parameter_list|(
name|GimpDisplayShell
modifier|*
name|shell
parameter_list|,
name|cairo_t
modifier|*
name|cr
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
name|cr
operator|!=
name|NULL
argument_list|)
expr_stmt|;
name|cairo_set_line_width
argument_list|(
name|cr
argument_list|,
literal|1.0
argument_list|)
expr_stmt|;
name|gimp_display_shell_set_stipple_style
argument_list|(
name|cr
argument_list|,
operator|&
name|selection_out_fg
argument_list|,
operator|&
name|selection_out_bg
argument_list|,
literal|0
argument_list|)
expr_stmt|;
block|}
end_function

begin_function
name|void
DECL|function|gimp_display_shell_set_selection_in_style (GimpDisplayShell * shell,cairo_t * cr,gint index)
name|gimp_display_shell_set_selection_in_style
parameter_list|(
name|GimpDisplayShell
modifier|*
name|shell
parameter_list|,
name|cairo_t
modifier|*
name|cr
parameter_list|,
name|gint
name|index
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
name|cr
operator|!=
name|NULL
argument_list|)
expr_stmt|;
name|cairo_set_line_width
argument_list|(
name|cr
argument_list|,
literal|1.0
argument_list|)
expr_stmt|;
name|gimp_display_shell_set_stipple_style
argument_list|(
name|cr
argument_list|,
operator|&
name|selection_in_fg
argument_list|,
operator|&
name|selection_in_bg
argument_list|,
name|index
argument_list|)
expr_stmt|;
block|}
end_function

begin_comment
comment|/*  private functions  */
end_comment

begin_decl_stmt
DECL|variable|surface_data_key
specifier|static
name|cairo_user_data_key_t
name|surface_data_key
init|=
block|{
literal|0
block|, }
decl_stmt|;
end_decl_stmt

begin_function
specifier|static
name|void
DECL|function|gimp_display_shell_set_stipple_style (cairo_t * cr,const GimpRGB * fg,const GimpRGB * bg,gint index)
name|gimp_display_shell_set_stipple_style
parameter_list|(
name|cairo_t
modifier|*
name|cr
parameter_list|,
specifier|const
name|GimpRGB
modifier|*
name|fg
parameter_list|,
specifier|const
name|GimpRGB
modifier|*
name|bg
parameter_list|,
name|gint
name|index
parameter_list|)
block|{
name|cairo_surface_t
modifier|*
name|surface
decl_stmt|;
name|guchar
modifier|*
name|data
init|=
name|g_malloc0
argument_list|(
literal|8
operator|*
literal|8
operator|*
literal|4
argument_list|)
decl_stmt|;
name|guchar
name|fg_r
decl_stmt|,
name|fg_g
decl_stmt|,
name|fg_b
decl_stmt|,
name|fg_a
decl_stmt|;
name|guchar
name|bg_r
decl_stmt|,
name|bg_g
decl_stmt|,
name|bg_b
decl_stmt|,
name|bg_a
decl_stmt|;
name|gint
name|x
decl_stmt|,
name|y
decl_stmt|;
name|guchar
modifier|*
name|d
decl_stmt|;
name|gimp_rgba_get_uchar
argument_list|(
name|fg
argument_list|,
operator|&
name|fg_r
argument_list|,
operator|&
name|fg_g
argument_list|,
operator|&
name|fg_b
argument_list|,
operator|&
name|fg_a
argument_list|)
expr_stmt|;
name|gimp_rgba_get_uchar
argument_list|(
name|bg
argument_list|,
operator|&
name|bg_r
argument_list|,
operator|&
name|bg_g
argument_list|,
operator|&
name|bg_b
argument_list|,
operator|&
name|bg_a
argument_list|)
expr_stmt|;
name|d
operator|=
name|data
expr_stmt|;
for|for
control|(
name|y
operator|=
literal|0
init|;
name|y
operator|<
literal|8
condition|;
name|y
operator|++
control|)
block|{
for|for
control|(
name|x
operator|=
literal|0
init|;
name|x
operator|<
literal|8
condition|;
name|x
operator|++
control|)
block|{
if|if
condition|(
operator|(
name|x
operator|+
name|y
operator|+
name|index
operator|)
operator|%
literal|8
operator|>=
literal|4
condition|)
name|GIMP_CAIRO_ARGB32_SET_PIXEL
argument_list|(
name|d
argument_list|,
name|fg_r
argument_list|,
name|fg_g
argument_list|,
name|fg_b
argument_list|,
name|fg_a
argument_list|)
expr_stmt|;
else|else
name|GIMP_CAIRO_ARGB32_SET_PIXEL
argument_list|(
name|d
argument_list|,
name|bg_r
argument_list|,
name|bg_g
argument_list|,
name|bg_b
argument_list|,
name|bg_a
argument_list|)
expr_stmt|;
name|d
operator|+=
literal|4
expr_stmt|;
block|}
block|}
if|if
condition|(
name|FALSE
condition|)
comment|//index> 0)
block|{
name|gint
name|move
init|=
name|index
operator|*
literal|4
decl_stmt|;
name|guchar
modifier|*
name|buf
init|=
name|g_alloca
argument_list|(
literal|8
operator|*
literal|8
operator|*
literal|4
argument_list|)
decl_stmt|;
name|memcpy
argument_list|(
name|buf
argument_list|,
name|data
argument_list|,
literal|8
operator|*
literal|8
operator|*
literal|4
argument_list|)
expr_stmt|;
name|memcpy
argument_list|(
name|data
argument_list|,
name|buf
operator|+
literal|8
operator|*
literal|8
operator|*
literal|4
operator|-
name|move
argument_list|,
name|move
argument_list|)
expr_stmt|;
name|memcpy
argument_list|(
name|data
operator|+
name|move
argument_list|,
name|buf
argument_list|,
literal|8
operator|*
literal|8
operator|*
literal|4
operator|-
name|move
argument_list|)
expr_stmt|;
block|}
name|surface
operator|=
name|cairo_image_surface_create_for_data
argument_list|(
name|data
argument_list|,
name|CAIRO_FORMAT_ARGB32
argument_list|,
literal|8
argument_list|,
literal|8
argument_list|,
literal|8
operator|*
literal|4
argument_list|)
expr_stmt|;
name|cairo_surface_set_user_data
argument_list|(
name|surface
argument_list|,
operator|&
name|surface_data_key
argument_list|,
name|data
argument_list|,
operator|(
name|cairo_destroy_func_t
operator|)
name|g_free
argument_list|)
expr_stmt|;
name|cairo_set_source_surface
argument_list|(
name|cr
argument_list|,
name|surface
argument_list|,
literal|0
argument_list|,
literal|0
argument_list|)
expr_stmt|;
name|cairo_surface_destroy
argument_list|(
name|surface
argument_list|)
expr_stmt|;
name|cairo_pattern_set_extend
argument_list|(
name|cairo_get_source
argument_list|(
name|cr
argument_list|)
argument_list|,
name|CAIRO_EXTEND_REPEAT
argument_list|)
expr_stmt|;
block|}
end_function

end_unit

