begin_unit|revision:0.9.5;language:C;cregit-version:0.0.1
begin_comment
comment|/* GIMP - The GNU Image Manipulation Program  * Copyright (C) 1995 Spencer Kimball and Peter Mattis  *  * gimpcanvasitem.c  * Copyright (C) 2010 Michael Natterer<mitch@gimp.org>  *  * This program is free software: you can redistribute it and/or modify  * it under the terms of the GNU General Public License as published by  * the Free Software Foundation; either version 3 of the License, or  * (at your option) any later version.  *  * This program is distributed in the hope that it will be useful,  * but WITHOUT ANY WARRANTY; without even the implied warranty of  * MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the  * GNU General Public License for more details.  *  * You should have received a copy of the GNU General Public License  * along with this program.  If not, see<http://www.gnu.org/licenses/>.  */
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
file|"display-types.h"
end_include

begin_include
include|#
directive|include
file|"libgimpmath/gimpmath.h"
end_include

begin_include
include|#
directive|include
file|"gimpcanvasitem.h"
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

begin_typedef
DECL|typedef|GimpCanvasItemPrivate
typedef|typedef
name|struct
name|_GimpCanvasItemPrivate
name|GimpCanvasItemPrivate
typedef|;
end_typedef

begin_struct
DECL|struct|_GimpCanvasItemPrivate
struct|struct
name|_GimpCanvasItemPrivate
block|{ }
struct|;
end_struct

begin_define
DECL|macro|GET_PRIVATE (item)
define|#
directive|define
name|GET_PRIVATE
parameter_list|(
name|item
parameter_list|)
define|\
value|G_TYPE_INSTANCE_GET_PRIVATE (item, \                                      GIMP_TYPE_CANVAS_ITEM, \                                      GimpCanvasItemPrivate)
end_define

begin_comment
comment|/*  local function prototypes  */
end_comment

begin_function_decl
specifier|static
name|void
name|gimp_canvas_item_real_draw
parameter_list|(
name|GimpCanvasItem
modifier|*
name|item
parameter_list|,
name|GimpDisplayShell
modifier|*
name|shell
parameter_list|,
name|cairo_t
modifier|*
name|cr
parameter_list|)
function_decl|;
end_function_decl

begin_function_decl
specifier|static
name|GdkRegion
modifier|*
name|gimp_canvas_item_real_get_extents
parameter_list|(
name|GimpCanvasItem
modifier|*
name|item
parameter_list|,
name|GimpDisplayShell
modifier|*
name|shell
parameter_list|)
function_decl|;
end_function_decl

begin_macro
DECL|function|G_DEFINE_TYPE (GimpCanvasItem,gimp_canvas_item,GIMP_TYPE_OBJECT)
name|G_DEFINE_TYPE
argument_list|(
argument|GimpCanvasItem
argument_list|,
argument|gimp_canvas_item
argument_list|,
argument|GIMP_TYPE_OBJECT
argument_list|)
end_macro

begin_define
DECL|macro|parent_class
define|#
directive|define
name|parent_class
value|gimp_canvas_item_parent_class
end_define

begin_function
specifier|static
name|void
name|gimp_canvas_item_class_init
parameter_list|(
name|GimpCanvasItemClass
modifier|*
name|klass
parameter_list|)
block|{
name|klass
operator|->
name|draw
operator|=
name|gimp_canvas_item_real_draw
expr_stmt|;
name|klass
operator|->
name|get_extents
operator|=
name|gimp_canvas_item_real_get_extents
expr_stmt|;
name|g_type_class_add_private
argument_list|(
name|klass
argument_list|,
sizeof|sizeof
argument_list|(
name|GimpCanvasItemPrivate
argument_list|)
argument_list|)
expr_stmt|;
block|}
end_function

begin_function
specifier|static
name|void
DECL|function|gimp_canvas_item_init (GimpCanvasItem * item)
name|gimp_canvas_item_init
parameter_list|(
name|GimpCanvasItem
modifier|*
name|item
parameter_list|)
block|{ }
end_function

begin_function
specifier|static
name|void
DECL|function|gimp_canvas_item_real_draw (GimpCanvasItem * item,GimpDisplayShell * shell,cairo_t * cr)
name|gimp_canvas_item_real_draw
parameter_list|(
name|GimpCanvasItem
modifier|*
name|item
parameter_list|,
name|GimpDisplayShell
modifier|*
name|shell
parameter_list|,
name|cairo_t
modifier|*
name|cr
parameter_list|)
block|{
name|g_warn_if_reached
argument_list|()
expr_stmt|;
block|}
end_function

begin_function
specifier|static
name|GdkRegion
modifier|*
DECL|function|gimp_canvas_item_real_get_extents (GimpCanvasItem * item,GimpDisplayShell * shell)
name|gimp_canvas_item_real_get_extents
parameter_list|(
name|GimpCanvasItem
modifier|*
name|item
parameter_list|,
name|GimpDisplayShell
modifier|*
name|shell
parameter_list|)
block|{
return|return
name|NULL
return|;
block|}
end_function

begin_comment
comment|/*  public functions  */
end_comment

begin_function
name|void
DECL|function|gimp_canvas_item_draw (GimpCanvasItem * item,GimpDisplayShell * shell,cairo_t * cr)
name|gimp_canvas_item_draw
parameter_list|(
name|GimpCanvasItem
modifier|*
name|item
parameter_list|,
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
name|GIMP_IS_CANVAS_ITEM
argument_list|(
name|item
argument_list|)
argument_list|)
expr_stmt|;
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
name|cairo_save
argument_list|(
name|cr
argument_list|)
expr_stmt|;
name|GIMP_CANVAS_ITEM_GET_CLASS
argument_list|(
name|item
argument_list|)
operator|->
name|draw
argument_list|(
name|item
argument_list|,
name|shell
argument_list|,
name|cr
argument_list|)
expr_stmt|;
name|cairo_restore
argument_list|(
name|cr
argument_list|)
expr_stmt|;
block|}
end_function

begin_function
name|GdkRegion
modifier|*
DECL|function|gimp_canvas_item_get_extents (GimpCanvasItem * item,GimpDisplayShell * shell)
name|gimp_canvas_item_get_extents
parameter_list|(
name|GimpCanvasItem
modifier|*
name|item
parameter_list|,
name|GimpDisplayShell
modifier|*
name|shell
parameter_list|)
block|{
name|g_return_val_if_fail
argument_list|(
name|GIMP_IS_CANVAS_ITEM
argument_list|(
name|item
argument_list|)
argument_list|,
name|NULL
argument_list|)
expr_stmt|;
name|g_return_val_if_fail
argument_list|(
name|GIMP_IS_DISPLAY_SHELL
argument_list|(
name|shell
argument_list|)
argument_list|,
name|NULL
argument_list|)
expr_stmt|;
return|return
name|GIMP_CANVAS_ITEM_GET_CLASS
argument_list|(
name|item
argument_list|)
operator|->
name|get_extents
argument_list|(
name|item
argument_list|,
name|shell
argument_list|)
return|;
block|}
end_function

begin_comment
comment|/*  protexted functions  */
end_comment

begin_function
name|void
DECL|function|_gimp_canvas_item_stroke (GimpCanvasItem * item,GimpDisplayShell * shell,cairo_t * cr)
name|_gimp_canvas_item_stroke
parameter_list|(
name|GimpCanvasItem
modifier|*
name|item
parameter_list|,
name|GimpDisplayShell
modifier|*
name|shell
parameter_list|,
name|cairo_t
modifier|*
name|cr
parameter_list|)
block|{
name|gimp_display_shell_set_tool_bg_style
argument_list|(
name|shell
argument_list|,
name|cr
argument_list|)
expr_stmt|;
name|cairo_stroke_preserve
argument_list|(
name|cr
argument_list|)
expr_stmt|;
name|gimp_display_shell_set_tool_fg_style
argument_list|(
name|shell
argument_list|,
name|cr
argument_list|)
expr_stmt|;
name|cairo_stroke
argument_list|(
name|cr
argument_list|)
expr_stmt|;
block|}
end_function

begin_function
name|void
DECL|function|_gimp_canvas_item_fill (GimpCanvasItem * item,GimpDisplayShell * shell,cairo_t * cr)
name|_gimp_canvas_item_fill
parameter_list|(
name|GimpCanvasItem
modifier|*
name|item
parameter_list|,
name|GimpDisplayShell
modifier|*
name|shell
parameter_list|,
name|cairo_t
modifier|*
name|cr
parameter_list|)
block|{
name|gimp_display_shell_set_tool_fg_style
argument_list|(
name|shell
argument_list|,
name|cr
argument_list|)
expr_stmt|;
name|cairo_fill
argument_list|(
name|cr
argument_list|)
expr_stmt|;
block|}
end_function

end_unit

