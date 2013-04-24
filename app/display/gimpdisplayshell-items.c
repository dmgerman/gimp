begin_unit|revision:0.9.5;language:C;cregit-version:0.0.1
begin_comment
comment|/* GIMP - The GNU Image Manipulation Program  * Copyright (C) 1995 Spencer Kimball and Peter Mattis  *  * gimpdisplayshell-items.c  * Copyright (C) 2010  Michael Natterer<mitch@gimp.org>  *  * This program is free software: you can redistribute it and/or modify  * it under the terms of the GNU General Public License as published by  * the Free Software Foundation; either version 3 of the License, or  * (at your option) any later version.  *  * This program is distributed in the hope that it will be useful,  * but WITHOUT ANY WARRANTY; without even the implied warranty of  * MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the  * GNU General Public License for more details.  *  * You should have received a copy of the GNU General Public License  * along with this program.  If not, see<http://www.gnu.org/licenses/>.  */
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
file|<libgimpmath/gimpmath.h>
end_include

begin_include
include|#
directive|include
file|"display-types.h"
end_include

begin_include
include|#
directive|include
file|"gimpcanvascursor.h"
end_include

begin_include
include|#
directive|include
file|"gimpcanvasgrid.h"
end_include

begin_include
include|#
directive|include
file|"gimpcanvaslayerboundary.h"
end_include

begin_include
include|#
directive|include
file|"gimpcanvaspassepartout.h"
end_include

begin_include
include|#
directive|include
file|"gimpcanvasproxygroup.h"
end_include

begin_include
include|#
directive|include
file|"gimpdisplayshell.h"
end_include

begin_include
include|#
directive|include
file|"gimpdisplayshell-expose.h"
end_include

begin_include
include|#
directive|include
file|"gimpdisplayshell-items.h"
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
name|void
name|gimp_display_shell_item_update
parameter_list|(
name|GimpCanvasItem
modifier|*
name|item
parameter_list|,
name|cairo_region_t
modifier|*
name|region
parameter_list|,
name|GimpDisplayShell
modifier|*
name|shell
parameter_list|)
function_decl|;
end_function_decl

begin_function_decl
specifier|static
name|void
name|gimp_display_shell_unrotated_item_update
parameter_list|(
name|GimpCanvasItem
modifier|*
name|item
parameter_list|,
name|cairo_region_t
modifier|*
name|region
parameter_list|,
name|GimpDisplayShell
modifier|*
name|shell
parameter_list|)
function_decl|;
end_function_decl

begin_comment
comment|/*  public functions  */
end_comment

begin_function
name|void
DECL|function|gimp_display_shell_items_init (GimpDisplayShell * shell)
name|gimp_display_shell_items_init
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
name|shell
operator|->
name|canvas_item
operator|=
name|gimp_canvas_group_new
argument_list|(
name|shell
argument_list|)
expr_stmt|;
name|shell
operator|->
name|passe_partout
operator|=
name|gimp_canvas_passe_partout_new
argument_list|(
name|shell
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
name|gimp_canvas_item_set_visible
argument_list|(
name|shell
operator|->
name|passe_partout
argument_list|,
name|FALSE
argument_list|)
expr_stmt|;
name|gimp_display_shell_add_item
argument_list|(
name|shell
argument_list|,
name|shell
operator|->
name|passe_partout
argument_list|)
expr_stmt|;
name|g_object_unref
argument_list|(
name|shell
operator|->
name|passe_partout
argument_list|)
expr_stmt|;
name|shell
operator|->
name|preview_items
operator|=
name|gimp_canvas_group_new
argument_list|(
name|shell
argument_list|)
expr_stmt|;
name|gimp_display_shell_add_item
argument_list|(
name|shell
argument_list|,
name|shell
operator|->
name|preview_items
argument_list|)
expr_stmt|;
name|g_object_unref
argument_list|(
name|shell
operator|->
name|preview_items
argument_list|)
expr_stmt|;
name|shell
operator|->
name|vectors
operator|=
name|gimp_canvas_proxy_group_new
argument_list|(
name|shell
argument_list|)
expr_stmt|;
name|gimp_display_shell_add_item
argument_list|(
name|shell
argument_list|,
name|shell
operator|->
name|vectors
argument_list|)
expr_stmt|;
name|g_object_unref
argument_list|(
name|shell
operator|->
name|vectors
argument_list|)
expr_stmt|;
name|shell
operator|->
name|grid
operator|=
name|gimp_canvas_grid_new
argument_list|(
name|shell
argument_list|,
name|NULL
argument_list|)
expr_stmt|;
name|gimp_canvas_item_set_visible
argument_list|(
name|shell
operator|->
name|grid
argument_list|,
name|FALSE
argument_list|)
expr_stmt|;
name|g_object_set
argument_list|(
name|shell
operator|->
name|grid
argument_list|,
literal|"grid-style"
argument_list|,
name|TRUE
argument_list|,
name|NULL
argument_list|)
expr_stmt|;
name|gimp_display_shell_add_item
argument_list|(
name|shell
argument_list|,
name|shell
operator|->
name|grid
argument_list|)
expr_stmt|;
name|g_object_unref
argument_list|(
name|shell
operator|->
name|grid
argument_list|)
expr_stmt|;
name|shell
operator|->
name|guides
operator|=
name|gimp_canvas_proxy_group_new
argument_list|(
name|shell
argument_list|)
expr_stmt|;
name|gimp_display_shell_add_item
argument_list|(
name|shell
argument_list|,
name|shell
operator|->
name|guides
argument_list|)
expr_stmt|;
name|g_object_unref
argument_list|(
name|shell
operator|->
name|guides
argument_list|)
expr_stmt|;
name|shell
operator|->
name|sample_points
operator|=
name|gimp_canvas_proxy_group_new
argument_list|(
name|shell
argument_list|)
expr_stmt|;
name|gimp_display_shell_add_item
argument_list|(
name|shell
argument_list|,
name|shell
operator|->
name|sample_points
argument_list|)
expr_stmt|;
name|g_object_unref
argument_list|(
name|shell
operator|->
name|sample_points
argument_list|)
expr_stmt|;
name|shell
operator|->
name|layer_boundary
operator|=
name|gimp_canvas_layer_boundary_new
argument_list|(
name|shell
argument_list|)
expr_stmt|;
name|gimp_canvas_item_set_visible
argument_list|(
name|shell
operator|->
name|layer_boundary
argument_list|,
name|FALSE
argument_list|)
expr_stmt|;
name|gimp_display_shell_add_item
argument_list|(
name|shell
argument_list|,
name|shell
operator|->
name|layer_boundary
argument_list|)
expr_stmt|;
name|g_object_unref
argument_list|(
name|shell
operator|->
name|layer_boundary
argument_list|)
expr_stmt|;
name|shell
operator|->
name|tool_items
operator|=
name|gimp_canvas_group_new
argument_list|(
name|shell
argument_list|)
expr_stmt|;
name|gimp_display_shell_add_item
argument_list|(
name|shell
argument_list|,
name|shell
operator|->
name|tool_items
argument_list|)
expr_stmt|;
name|g_object_unref
argument_list|(
name|shell
operator|->
name|tool_items
argument_list|)
expr_stmt|;
name|g_signal_connect
argument_list|(
name|shell
operator|->
name|canvas_item
argument_list|,
literal|"update"
argument_list|,
name|G_CALLBACK
argument_list|(
name|gimp_display_shell_item_update
argument_list|)
argument_list|,
name|shell
argument_list|)
expr_stmt|;
name|shell
operator|->
name|unrotated_item
operator|=
name|gimp_canvas_group_new
argument_list|(
name|shell
argument_list|)
expr_stmt|;
name|shell
operator|->
name|cursor
operator|=
name|gimp_canvas_cursor_new
argument_list|(
name|shell
argument_list|)
expr_stmt|;
name|gimp_canvas_item_set_visible
argument_list|(
name|shell
operator|->
name|cursor
argument_list|,
name|FALSE
argument_list|)
expr_stmt|;
name|gimp_display_shell_add_unrotated_item
argument_list|(
name|shell
argument_list|,
name|shell
operator|->
name|cursor
argument_list|)
expr_stmt|;
name|g_object_unref
argument_list|(
name|shell
operator|->
name|cursor
argument_list|)
expr_stmt|;
name|g_signal_connect
argument_list|(
name|shell
operator|->
name|unrotated_item
argument_list|,
literal|"update"
argument_list|,
name|G_CALLBACK
argument_list|(
name|gimp_display_shell_unrotated_item_update
argument_list|)
argument_list|,
name|shell
argument_list|)
expr_stmt|;
block|}
end_function

begin_function
name|void
DECL|function|gimp_display_shell_items_free (GimpDisplayShell * shell)
name|gimp_display_shell_items_free
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
name|canvas_item
condition|)
block|{
name|g_signal_handlers_disconnect_by_func
argument_list|(
name|shell
operator|->
name|canvas_item
argument_list|,
name|gimp_display_shell_item_update
argument_list|,
name|shell
argument_list|)
expr_stmt|;
name|g_object_unref
argument_list|(
name|shell
operator|->
name|canvas_item
argument_list|)
expr_stmt|;
name|shell
operator|->
name|canvas_item
operator|=
name|NULL
expr_stmt|;
name|shell
operator|->
name|passe_partout
operator|=
name|NULL
expr_stmt|;
name|shell
operator|->
name|preview_items
operator|=
name|NULL
expr_stmt|;
name|shell
operator|->
name|vectors
operator|=
name|NULL
expr_stmt|;
name|shell
operator|->
name|grid
operator|=
name|NULL
expr_stmt|;
name|shell
operator|->
name|guides
operator|=
name|NULL
expr_stmt|;
name|shell
operator|->
name|sample_points
operator|=
name|NULL
expr_stmt|;
name|shell
operator|->
name|layer_boundary
operator|=
name|NULL
expr_stmt|;
name|shell
operator|->
name|tool_items
operator|=
name|NULL
expr_stmt|;
block|}
if|if
condition|(
name|shell
operator|->
name|unrotated_item
condition|)
block|{
name|g_signal_handlers_disconnect_by_func
argument_list|(
name|shell
operator|->
name|unrotated_item
argument_list|,
name|gimp_display_shell_unrotated_item_update
argument_list|,
name|shell
argument_list|)
expr_stmt|;
name|g_object_unref
argument_list|(
name|shell
operator|->
name|unrotated_item
argument_list|)
expr_stmt|;
name|shell
operator|->
name|unrotated_item
operator|=
name|NULL
expr_stmt|;
name|shell
operator|->
name|cursor
operator|=
name|NULL
expr_stmt|;
block|}
block|}
end_function

begin_function
name|void
DECL|function|gimp_display_shell_add_item (GimpDisplayShell * shell,GimpCanvasItem * item)
name|gimp_display_shell_add_item
parameter_list|(
name|GimpDisplayShell
modifier|*
name|shell
parameter_list|,
name|GimpCanvasItem
modifier|*
name|item
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
name|GIMP_IS_CANVAS_ITEM
argument_list|(
name|item
argument_list|)
argument_list|)
expr_stmt|;
name|gimp_canvas_group_add_item
argument_list|(
name|GIMP_CANVAS_GROUP
argument_list|(
name|shell
operator|->
name|canvas_item
argument_list|)
argument_list|,
name|item
argument_list|)
expr_stmt|;
block|}
end_function

begin_function
name|void
DECL|function|gimp_display_shell_remove_item (GimpDisplayShell * shell,GimpCanvasItem * item)
name|gimp_display_shell_remove_item
parameter_list|(
name|GimpDisplayShell
modifier|*
name|shell
parameter_list|,
name|GimpCanvasItem
modifier|*
name|item
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
name|GIMP_IS_CANVAS_ITEM
argument_list|(
name|item
argument_list|)
argument_list|)
expr_stmt|;
name|gimp_canvas_group_remove_item
argument_list|(
name|GIMP_CANVAS_GROUP
argument_list|(
name|shell
operator|->
name|canvas_item
argument_list|)
argument_list|,
name|item
argument_list|)
expr_stmt|;
block|}
end_function

begin_function
name|void
DECL|function|gimp_display_shell_add_preview_item (GimpDisplayShell * shell,GimpCanvasItem * item)
name|gimp_display_shell_add_preview_item
parameter_list|(
name|GimpDisplayShell
modifier|*
name|shell
parameter_list|,
name|GimpCanvasItem
modifier|*
name|item
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
name|GIMP_IS_CANVAS_ITEM
argument_list|(
name|item
argument_list|)
argument_list|)
expr_stmt|;
name|gimp_canvas_group_add_item
argument_list|(
name|GIMP_CANVAS_GROUP
argument_list|(
name|shell
operator|->
name|preview_items
argument_list|)
argument_list|,
name|item
argument_list|)
expr_stmt|;
block|}
end_function

begin_function
name|void
DECL|function|gimp_display_shell_remove_preview_item (GimpDisplayShell * shell,GimpCanvasItem * item)
name|gimp_display_shell_remove_preview_item
parameter_list|(
name|GimpDisplayShell
modifier|*
name|shell
parameter_list|,
name|GimpCanvasItem
modifier|*
name|item
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
name|GIMP_IS_CANVAS_ITEM
argument_list|(
name|item
argument_list|)
argument_list|)
expr_stmt|;
name|gimp_canvas_group_remove_item
argument_list|(
name|GIMP_CANVAS_GROUP
argument_list|(
name|shell
operator|->
name|preview_items
argument_list|)
argument_list|,
name|item
argument_list|)
expr_stmt|;
block|}
end_function

begin_function
name|void
DECL|function|gimp_display_shell_add_unrotated_item (GimpDisplayShell * shell,GimpCanvasItem * item)
name|gimp_display_shell_add_unrotated_item
parameter_list|(
name|GimpDisplayShell
modifier|*
name|shell
parameter_list|,
name|GimpCanvasItem
modifier|*
name|item
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
name|GIMP_IS_CANVAS_ITEM
argument_list|(
name|item
argument_list|)
argument_list|)
expr_stmt|;
name|gimp_canvas_group_add_item
argument_list|(
name|GIMP_CANVAS_GROUP
argument_list|(
name|shell
operator|->
name|unrotated_item
argument_list|)
argument_list|,
name|item
argument_list|)
expr_stmt|;
block|}
end_function

begin_function
name|void
DECL|function|gimp_display_shell_remove_unrotated_item (GimpDisplayShell * shell,GimpCanvasItem * item)
name|gimp_display_shell_remove_unrotated_item
parameter_list|(
name|GimpDisplayShell
modifier|*
name|shell
parameter_list|,
name|GimpCanvasItem
modifier|*
name|item
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
name|GIMP_IS_CANVAS_ITEM
argument_list|(
name|item
argument_list|)
argument_list|)
expr_stmt|;
name|gimp_canvas_group_remove_item
argument_list|(
name|GIMP_CANVAS_GROUP
argument_list|(
name|shell
operator|->
name|unrotated_item
argument_list|)
argument_list|,
name|item
argument_list|)
expr_stmt|;
block|}
end_function

begin_function
name|void
DECL|function|gimp_display_shell_add_tool_item (GimpDisplayShell * shell,GimpCanvasItem * item)
name|gimp_display_shell_add_tool_item
parameter_list|(
name|GimpDisplayShell
modifier|*
name|shell
parameter_list|,
name|GimpCanvasItem
modifier|*
name|item
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
name|GIMP_IS_CANVAS_ITEM
argument_list|(
name|item
argument_list|)
argument_list|)
expr_stmt|;
name|gimp_canvas_group_add_item
argument_list|(
name|GIMP_CANVAS_GROUP
argument_list|(
name|shell
operator|->
name|tool_items
argument_list|)
argument_list|,
name|item
argument_list|)
expr_stmt|;
block|}
end_function

begin_function
name|void
DECL|function|gimp_display_shell_remove_tool_item (GimpDisplayShell * shell,GimpCanvasItem * item)
name|gimp_display_shell_remove_tool_item
parameter_list|(
name|GimpDisplayShell
modifier|*
name|shell
parameter_list|,
name|GimpCanvasItem
modifier|*
name|item
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
name|GIMP_IS_CANVAS_ITEM
argument_list|(
name|item
argument_list|)
argument_list|)
expr_stmt|;
name|gimp_canvas_group_remove_item
argument_list|(
name|GIMP_CANVAS_GROUP
argument_list|(
name|shell
operator|->
name|tool_items
argument_list|)
argument_list|,
name|item
argument_list|)
expr_stmt|;
block|}
end_function

begin_comment
comment|/*  private functions  */
end_comment

begin_function
specifier|static
name|void
DECL|function|gimp_display_shell_item_update (GimpCanvasItem * item,cairo_region_t * region,GimpDisplayShell * shell)
name|gimp_display_shell_item_update
parameter_list|(
name|GimpCanvasItem
modifier|*
name|item
parameter_list|,
name|cairo_region_t
modifier|*
name|region
parameter_list|,
name|GimpDisplayShell
modifier|*
name|shell
parameter_list|)
block|{
if|if
condition|(
name|shell
operator|->
name|rotate_transform
condition|)
block|{
name|gint
name|n_rects
decl_stmt|;
name|gint
name|i
decl_stmt|;
name|n_rects
operator|=
name|cairo_region_num_rectangles
argument_list|(
name|region
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
name|n_rects
condition|;
name|i
operator|++
control|)
block|{
name|cairo_rectangle_int_t
name|rect
decl_stmt|;
name|gdouble
name|tx1
decl_stmt|,
name|ty1
decl_stmt|;
name|gdouble
name|tx2
decl_stmt|,
name|ty2
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
name|cairo_region_get_rectangle
argument_list|(
name|region
argument_list|,
name|i
argument_list|,
operator|&
name|rect
argument_list|)
expr_stmt|;
name|gimp_display_shell_rotate_bounds
argument_list|(
name|shell
argument_list|,
name|rect
operator|.
name|x
argument_list|,
name|rect
operator|.
name|y
argument_list|,
name|rect
operator|.
name|x
operator|+
name|rect
operator|.
name|width
argument_list|,
name|rect
operator|.
name|y
operator|+
name|rect
operator|.
name|height
argument_list|,
operator|&
name|tx1
argument_list|,
operator|&
name|ty1
argument_list|,
operator|&
name|tx2
argument_list|,
operator|&
name|ty2
argument_list|)
expr_stmt|;
name|x1
operator|=
name|floor
argument_list|(
name|tx1
operator|-
literal|0.5
argument_list|)
expr_stmt|;
name|y1
operator|=
name|floor
argument_list|(
name|ty1
operator|-
literal|0.5
argument_list|)
expr_stmt|;
name|x2
operator|=
name|ceil
argument_list|(
name|tx2
operator|+
literal|0.5
argument_list|)
expr_stmt|;
name|y2
operator|=
name|ceil
argument_list|(
name|ty2
operator|+
literal|0.5
argument_list|)
expr_stmt|;
name|gimp_display_shell_expose_area
argument_list|(
name|shell
argument_list|,
name|x1
argument_list|,
name|y1
argument_list|,
name|x2
operator|-
name|x1
argument_list|,
name|y2
operator|-
name|y1
argument_list|)
expr_stmt|;
block|}
block|}
else|else
block|{
name|gimp_display_shell_expose_region
argument_list|(
name|shell
argument_list|,
name|region
argument_list|)
expr_stmt|;
block|}
block|}
end_function

begin_function
specifier|static
name|void
DECL|function|gimp_display_shell_unrotated_item_update (GimpCanvasItem * item,cairo_region_t * region,GimpDisplayShell * shell)
name|gimp_display_shell_unrotated_item_update
parameter_list|(
name|GimpCanvasItem
modifier|*
name|item
parameter_list|,
name|cairo_region_t
modifier|*
name|region
parameter_list|,
name|GimpDisplayShell
modifier|*
name|shell
parameter_list|)
block|{
name|gimp_display_shell_expose_region
argument_list|(
name|shell
argument_list|,
name|region
argument_list|)
expr_stmt|;
block|}
end_function

end_unit

