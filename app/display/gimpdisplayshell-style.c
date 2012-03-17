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
file|"core/gimpgrid.h"
end_include

begin_include
include|#
directive|include
file|"core/gimplayer.h"
end_include

begin_include
include|#
directive|include
file|"widgets/gimpcairo.h"
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

begin_decl_stmt
DECL|variable|vectors_normal_bg
specifier|static
specifier|const
name|GimpRGB
name|vectors_normal_bg
init|=
block|{
literal|1.0
block|,
literal|1.0
block|,
literal|1.0
block|,
literal|0.6
block|}
decl_stmt|;
end_decl_stmt

begin_decl_stmt
DECL|variable|vectors_normal_fg
specifier|static
specifier|const
name|GimpRGB
name|vectors_normal_fg
init|=
block|{
literal|0.0
block|,
literal|0.0
block|,
literal|1.0
block|,
literal|0.8
block|}
decl_stmt|;
end_decl_stmt

begin_decl_stmt
DECL|variable|vectors_active_bg
specifier|static
specifier|const
name|GimpRGB
name|vectors_active_bg
init|=
block|{
literal|1.0
block|,
literal|1.0
block|,
literal|1.0
block|,
literal|0.6
block|}
decl_stmt|;
end_decl_stmt

begin_decl_stmt
DECL|variable|vectors_active_fg
specifier|static
specifier|const
name|GimpRGB
name|vectors_active_fg
init|=
block|{
literal|1.0
block|,
literal|0.0
block|,
literal|0.0
block|,
literal|0.8
block|}
decl_stmt|;
end_decl_stmt

begin_decl_stmt
DECL|variable|outline_bg
specifier|static
specifier|const
name|GimpRGB
name|outline_bg
init|=
block|{
literal|1.0
block|,
literal|1.0
block|,
literal|1.0
block|,
literal|0.6
block|}
decl_stmt|;
end_decl_stmt

begin_decl_stmt
DECL|variable|outline_fg
specifier|static
specifier|const
name|GimpRGB
name|outline_fg
init|=
block|{
literal|0.0
block|,
literal|0.0
block|,
literal|0.0
block|,
literal|0.8
block|}
decl_stmt|;
end_decl_stmt

begin_decl_stmt
DECL|variable|passe_partout
specifier|static
specifier|const
name|GimpRGB
name|passe_partout
init|=
block|{
literal|0.0
block|,
literal|0.0
block|,
literal|0.0
block|,
literal|0.5
block|}
decl_stmt|;
end_decl_stmt

begin_decl_stmt
DECL|variable|tool_bg
specifier|static
specifier|const
name|GimpRGB
name|tool_bg
init|=
block|{
literal|0.0
block|,
literal|0.0
block|,
literal|0.0
block|,
literal|0.4
block|}
decl_stmt|;
end_decl_stmt

begin_decl_stmt
DECL|variable|tool_fg
specifier|static
specifier|const
name|GimpRGB
name|tool_fg
init|=
block|{
literal|1.0
block|,
literal|1.0
block|,
literal|1.0
block|,
literal|0.8
block|}
decl_stmt|;
end_decl_stmt

begin_decl_stmt
DECL|variable|tool_fg_highlight
specifier|static
specifier|const
name|GimpRGB
name|tool_fg_highlight
init|=
block|{
literal|1.0
block|,
literal|0.8
block|,
literal|0.2
block|,
literal|0.8
block|}
decl_stmt|;
end_decl_stmt

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
name|cairo_pattern_t
modifier|*
name|pattern
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
name|pattern
operator|=
name|gimp_cairo_stipple_pattern_create
argument_list|(
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
name|pattern
operator|=
name|gimp_cairo_stipple_pattern_create
argument_list|(
operator|&
name|guide_normal_fg
argument_list|,
operator|&
name|guide_normal_bg
argument_list|,
literal|0
argument_list|)
expr_stmt|;
name|cairo_set_source
argument_list|(
name|cr
argument_list|,
name|pattern
argument_list|)
expr_stmt|;
name|cairo_pattern_destroy
argument_list|(
name|pattern
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
name|gimp_cairo_set_source_rgb
argument_list|(
name|cr
argument_list|,
operator|&
name|sample_point_active
argument_list|)
expr_stmt|;
else|else
name|gimp_cairo_set_source_rgb
argument_list|(
name|cr
argument_list|,
operator|&
name|sample_point_normal
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
name|cairo_pattern_t
modifier|*
name|pattern
decl_stmt|;
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
name|pattern
operator|=
name|gimp_cairo_stipple_pattern_create
argument_list|(
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
name|pattern
operator|=
name|gimp_cairo_stipple_pattern_create
argument_list|(
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
name|cairo_set_source
argument_list|(
name|cr
argument_list|,
name|pattern
argument_list|)
expr_stmt|;
name|cairo_pattern_destroy
argument_list|(
name|pattern
argument_list|)
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
name|gimp_cairo_set_source_rgb
argument_list|(
name|cr
argument_list|,
operator|&
name|grid
operator|->
name|fgcolor
argument_list|)
expr_stmt|;
break|break;
block|}
block|}
end_function

begin_function
name|void
DECL|function|gimp_display_shell_set_pen_style (GimpDisplayShell * shell,cairo_t * cr,const GimpRGB * color,gint width)
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
specifier|const
name|GimpRGB
modifier|*
name|color
parameter_list|,
name|gint
name|width
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
name|color
operator|!=
name|NULL
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
name|gimp_cairo_set_source_rgb
argument_list|(
name|cr
argument_list|,
name|color
argument_list|)
expr_stmt|;
block|}
end_function

begin_function
name|void
DECL|function|gimp_display_shell_set_layer_style (GimpDisplayShell * shell,cairo_t * cr,GimpLayer * layer)
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
name|GimpLayer
modifier|*
name|layer
parameter_list|)
block|{
name|cairo_pattern_t
modifier|*
name|pattern
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
name|GIMP_IS_LAYER
argument_list|(
name|layer
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
name|cairo_set_line_cap
argument_list|(
name|cr
argument_list|,
name|CAIRO_LINE_CAP_SQUARE
argument_list|)
expr_stmt|;
if|if
condition|(
name|gimp_layer_get_mask
argument_list|(
name|layer
argument_list|)
operator|&&
name|gimp_layer_get_edit_mask
argument_list|(
name|layer
argument_list|)
condition|)
block|{
name|pattern
operator|=
name|gimp_cairo_stipple_pattern_create
argument_list|(
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
name|layer
argument_list|)
argument_list|)
condition|)
block|{
name|pattern
operator|=
name|gimp_cairo_stipple_pattern_create
argument_list|(
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
name|pattern
operator|=
name|gimp_cairo_stipple_pattern_create
argument_list|(
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
name|cairo_set_source
argument_list|(
name|cr
argument_list|,
name|pattern
argument_list|)
expr_stmt|;
name|cairo_pattern_destroy
argument_list|(
name|pattern
argument_list|)
expr_stmt|;
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
name|cairo_pattern_t
modifier|*
name|pattern
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
name|pattern
operator|=
name|gimp_cairo_stipple_pattern_create
argument_list|(
operator|&
name|selection_out_fg
argument_list|,
operator|&
name|selection_out_bg
argument_list|,
literal|0
argument_list|)
expr_stmt|;
name|cairo_set_source
argument_list|(
name|cr
argument_list|,
name|pattern
argument_list|)
expr_stmt|;
name|cairo_pattern_destroy
argument_list|(
name|pattern
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
name|cairo_pattern_t
modifier|*
name|pattern
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
name|pattern
operator|=
name|gimp_cairo_stipple_pattern_create
argument_list|(
operator|&
name|selection_in_fg
argument_list|,
operator|&
name|selection_in_bg
argument_list|,
name|index
argument_list|)
expr_stmt|;
name|cairo_set_source
argument_list|(
name|cr
argument_list|,
name|pattern
argument_list|)
expr_stmt|;
name|cairo_pattern_destroy
argument_list|(
name|pattern
argument_list|)
expr_stmt|;
block|}
end_function

begin_function
name|void
DECL|function|gimp_display_shell_set_vectors_bg_style (GimpDisplayShell * shell,cairo_t * cr,gboolean active)
name|gimp_display_shell_set_vectors_bg_style
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
literal|3.0
argument_list|)
expr_stmt|;
if|if
condition|(
name|active
condition|)
name|gimp_cairo_set_source_rgba
argument_list|(
name|cr
argument_list|,
operator|&
name|vectors_active_bg
argument_list|)
expr_stmt|;
else|else
name|gimp_cairo_set_source_rgba
argument_list|(
name|cr
argument_list|,
operator|&
name|vectors_normal_bg
argument_list|)
expr_stmt|;
block|}
end_function

begin_function
name|void
DECL|function|gimp_display_shell_set_vectors_fg_style (GimpDisplayShell * shell,cairo_t * cr,gboolean active)
name|gimp_display_shell_set_vectors_fg_style
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
name|gimp_cairo_set_source_rgba
argument_list|(
name|cr
argument_list|,
operator|&
name|vectors_active_fg
argument_list|)
expr_stmt|;
else|else
name|gimp_cairo_set_source_rgba
argument_list|(
name|cr
argument_list|,
operator|&
name|vectors_normal_fg
argument_list|)
expr_stmt|;
block|}
end_function

begin_function
name|void
DECL|function|gimp_display_shell_set_outline_bg_style (GimpDisplayShell * shell,cairo_t * cr)
name|gimp_display_shell_set_outline_bg_style
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
name|gimp_cairo_set_source_rgba
argument_list|(
name|cr
argument_list|,
operator|&
name|outline_bg
argument_list|)
expr_stmt|;
block|}
end_function

begin_function
name|void
DECL|function|gimp_display_shell_set_outline_fg_style (GimpDisplayShell * shell,cairo_t * cr)
name|gimp_display_shell_set_outline_fg_style
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
specifier|static
specifier|const
name|double
name|dashes
index|[]
init|=
block|{
literal|4.0
block|,
literal|4.0
block|}
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
name|cairo_set_line_width
argument_list|(
name|cr
argument_list|,
literal|1.0
argument_list|)
expr_stmt|;
name|gimp_cairo_set_source_rgba
argument_list|(
name|cr
argument_list|,
operator|&
name|outline_fg
argument_list|)
expr_stmt|;
name|cairo_set_dash
argument_list|(
name|cr
argument_list|,
name|dashes
argument_list|,
name|G_N_ELEMENTS
argument_list|(
name|dashes
argument_list|)
argument_list|,
literal|0
argument_list|)
expr_stmt|;
block|}
end_function

begin_function
name|void
DECL|function|gimp_display_shell_set_passe_partout_style (GimpDisplayShell * shell,cairo_t * cr)
name|gimp_display_shell_set_passe_partout_style
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
name|gimp_cairo_set_source_rgba
argument_list|(
name|cr
argument_list|,
operator|&
name|passe_partout
argument_list|)
expr_stmt|;
block|}
end_function

begin_function
name|void
DECL|function|gimp_display_shell_set_tool_bg_style (GimpDisplayShell * shell,cairo_t * cr)
name|gimp_display_shell_set_tool_bg_style
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
literal|3.0
argument_list|)
expr_stmt|;
name|cairo_set_line_join
argument_list|(
name|cr
argument_list|,
name|CAIRO_LINE_JOIN_ROUND
argument_list|)
expr_stmt|;
name|gimp_cairo_set_source_rgba
argument_list|(
name|cr
argument_list|,
operator|&
name|tool_bg
argument_list|)
expr_stmt|;
block|}
end_function

begin_function
name|void
DECL|function|gimp_display_shell_set_tool_fg_style (GimpDisplayShell * shell,cairo_t * cr,gboolean highlight)
name|gimp_display_shell_set_tool_fg_style
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
name|highlight
parameter_list|)
block|{
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
name|cairo_set_line_join
argument_list|(
name|cr
argument_list|,
name|CAIRO_LINE_JOIN_ROUND
argument_list|)
expr_stmt|;
if|if
condition|(
name|highlight
condition|)
name|gimp_cairo_set_source_rgba
argument_list|(
name|cr
argument_list|,
operator|&
name|tool_fg_highlight
argument_list|)
expr_stmt|;
else|else
name|gimp_cairo_set_source_rgba
argument_list|(
name|cr
argument_list|,
operator|&
name|tool_fg
argument_list|)
expr_stmt|;
block|}
end_function

end_unit

