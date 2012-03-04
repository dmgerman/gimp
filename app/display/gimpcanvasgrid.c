begin_unit|revision:0.9.5;language:C;cregit-version:0.0.1
begin_comment
comment|/* GIMP - The GNU Image Manipulation Program  * Copyright (C) 1995 Spencer Kimball and Peter Mattis  *  * gimpcanvasgrid.c  * Copyright (C) 2010 Michael Natterer<mitch@gimp.org>  *  * This program is free software: you can redistribute it and/or modify  * it under the terms of the GNU General Public License as published by  * the Free Software Foundation; either version 3 of the License, or  * (at your option) any later version.  *  * This program is distributed in the hope that it will be useful,  * but WITHOUT ANY WARRANTY; without even the implied warranty of  * MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the  * GNU General Public License for more details.  *  * You should have received a copy of the GNU General Public License  * along with this program.  If not, see<http://www.gnu.org/licenses/>.  */
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
file|"libgimpbase/gimpbase.h"
end_include

begin_include
include|#
directive|include
file|"libgimpmath/gimpmath.h"
end_include

begin_include
include|#
directive|include
file|"libgimpconfig/gimpconfig.h"
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
file|"core/gimpimage.h"
end_include

begin_include
include|#
directive|include
file|"gimpcanvasgrid.h"
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
file|"gimpdisplayshell-style.h"
end_include

begin_include
include|#
directive|include
file|"gimpdisplayshell-transform.h"
end_include

begin_enum
enum|enum
DECL|enum|__anon2951483b0103
block|{
DECL|enumerator|PROP_0
name|PROP_0
block|,
DECL|enumerator|PROP_GRID
name|PROP_GRID
block|,
DECL|enumerator|PROP_GRID_STYLE
name|PROP_GRID_STYLE
block|}
enum|;
end_enum

begin_typedef
DECL|typedef|GimpCanvasGridPrivate
typedef|typedef
name|struct
name|_GimpCanvasGridPrivate
name|GimpCanvasGridPrivate
typedef|;
end_typedef

begin_struct
DECL|struct|_GimpCanvasGridPrivate
struct|struct
name|_GimpCanvasGridPrivate
block|{
DECL|member|grid
name|GimpGrid
modifier|*
name|grid
decl_stmt|;
DECL|member|grid_style
name|gboolean
name|grid_style
decl_stmt|;
block|}
struct|;
end_struct

begin_define
DECL|macro|GET_PRIVATE (grid)
define|#
directive|define
name|GET_PRIVATE
parameter_list|(
name|grid
parameter_list|)
define|\
value|G_TYPE_INSTANCE_GET_PRIVATE (grid, \                                      GIMP_TYPE_CANVAS_GRID, \                                      GimpCanvasGridPrivate)
end_define

begin_comment
comment|/*  local function prototypes  */
end_comment

begin_function_decl
specifier|static
name|void
name|gimp_canvas_grid_finalize
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
name|gimp_canvas_grid_set_property
parameter_list|(
name|GObject
modifier|*
name|object
parameter_list|,
name|guint
name|property_id
parameter_list|,
specifier|const
name|GValue
modifier|*
name|value
parameter_list|,
name|GParamSpec
modifier|*
name|pspec
parameter_list|)
function_decl|;
end_function_decl

begin_function_decl
specifier|static
name|void
name|gimp_canvas_grid_get_property
parameter_list|(
name|GObject
modifier|*
name|object
parameter_list|,
name|guint
name|property_id
parameter_list|,
name|GValue
modifier|*
name|value
parameter_list|,
name|GParamSpec
modifier|*
name|pspec
parameter_list|)
function_decl|;
end_function_decl

begin_function_decl
specifier|static
name|void
name|gimp_canvas_grid_draw
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
name|cairo_region_t
modifier|*
name|gimp_canvas_grid_get_extents
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

begin_function_decl
specifier|static
name|void
name|gimp_canvas_grid_stroke
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

begin_macro
DECL|function|G_DEFINE_TYPE (GimpCanvasGrid,gimp_canvas_grid,GIMP_TYPE_CANVAS_ITEM)
name|G_DEFINE_TYPE
argument_list|(
argument|GimpCanvasGrid
argument_list|,
argument|gimp_canvas_grid
argument_list|,
argument|GIMP_TYPE_CANVAS_ITEM
argument_list|)
end_macro

begin_define
DECL|macro|parent_class
define|#
directive|define
name|parent_class
value|gimp_canvas_grid_parent_class
end_define

begin_function
specifier|static
name|void
name|gimp_canvas_grid_class_init
parameter_list|(
name|GimpCanvasGridClass
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
name|GimpCanvasItemClass
modifier|*
name|item_class
init|=
name|GIMP_CANVAS_ITEM_CLASS
argument_list|(
name|klass
argument_list|)
decl_stmt|;
name|object_class
operator|->
name|finalize
operator|=
name|gimp_canvas_grid_finalize
expr_stmt|;
name|object_class
operator|->
name|set_property
operator|=
name|gimp_canvas_grid_set_property
expr_stmt|;
name|object_class
operator|->
name|get_property
operator|=
name|gimp_canvas_grid_get_property
expr_stmt|;
name|item_class
operator|->
name|draw
operator|=
name|gimp_canvas_grid_draw
expr_stmt|;
name|item_class
operator|->
name|get_extents
operator|=
name|gimp_canvas_grid_get_extents
expr_stmt|;
name|item_class
operator|->
name|stroke
operator|=
name|gimp_canvas_grid_stroke
expr_stmt|;
name|g_object_class_install_property
argument_list|(
name|object_class
argument_list|,
name|PROP_GRID
argument_list|,
name|g_param_spec_object
argument_list|(
literal|"grid"
argument_list|,
name|NULL
argument_list|,
name|NULL
argument_list|,
name|GIMP_TYPE_GRID
argument_list|,
name|GIMP_PARAM_READWRITE
argument_list|)
argument_list|)
expr_stmt|;
name|g_object_class_install_property
argument_list|(
name|object_class
argument_list|,
name|PROP_GRID_STYLE
argument_list|,
name|g_param_spec_boolean
argument_list|(
literal|"grid-style"
argument_list|,
name|NULL
argument_list|,
name|NULL
argument_list|,
name|FALSE
argument_list|,
name|GIMP_PARAM_READWRITE
argument_list|)
argument_list|)
expr_stmt|;
name|g_type_class_add_private
argument_list|(
name|klass
argument_list|,
sizeof|sizeof
argument_list|(
name|GimpCanvasGridPrivate
argument_list|)
argument_list|)
expr_stmt|;
block|}
end_function

begin_function
specifier|static
name|void
DECL|function|gimp_canvas_grid_init (GimpCanvasGrid * grid)
name|gimp_canvas_grid_init
parameter_list|(
name|GimpCanvasGrid
modifier|*
name|grid
parameter_list|)
block|{
name|GimpCanvasGridPrivate
modifier|*
name|private
init|=
name|GET_PRIVATE
argument_list|(
name|grid
argument_list|)
decl_stmt|;
name|private
operator|->
name|grid
operator|=
name|g_object_new
argument_list|(
name|GIMP_TYPE_GRID
argument_list|,
name|NULL
argument_list|)
expr_stmt|;
block|}
end_function

begin_function
specifier|static
name|void
DECL|function|gimp_canvas_grid_finalize (GObject * object)
name|gimp_canvas_grid_finalize
parameter_list|(
name|GObject
modifier|*
name|object
parameter_list|)
block|{
name|GimpCanvasGridPrivate
modifier|*
name|private
init|=
name|GET_PRIVATE
argument_list|(
name|object
argument_list|)
decl_stmt|;
if|if
condition|(
name|private
operator|->
name|grid
condition|)
block|{
name|g_object_unref
argument_list|(
name|private
operator|->
name|grid
argument_list|)
expr_stmt|;
name|private
operator|->
name|grid
operator|=
name|NULL
expr_stmt|;
block|}
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
DECL|function|gimp_canvas_grid_set_property (GObject * object,guint property_id,const GValue * value,GParamSpec * pspec)
name|gimp_canvas_grid_set_property
parameter_list|(
name|GObject
modifier|*
name|object
parameter_list|,
name|guint
name|property_id
parameter_list|,
specifier|const
name|GValue
modifier|*
name|value
parameter_list|,
name|GParamSpec
modifier|*
name|pspec
parameter_list|)
block|{
name|GimpCanvasGridPrivate
modifier|*
name|private
init|=
name|GET_PRIVATE
argument_list|(
name|object
argument_list|)
decl_stmt|;
switch|switch
condition|(
name|property_id
condition|)
block|{
case|case
name|PROP_GRID
case|:
block|{
name|GimpGrid
modifier|*
name|grid
init|=
name|g_value_get_object
argument_list|(
name|value
argument_list|)
decl_stmt|;
if|if
condition|(
name|grid
condition|)
name|gimp_config_sync
argument_list|(
name|G_OBJECT
argument_list|(
name|grid
argument_list|)
argument_list|,
name|G_OBJECT
argument_list|(
name|private
operator|->
name|grid
argument_list|)
argument_list|,
literal|0
argument_list|)
expr_stmt|;
block|}
break|break;
case|case
name|PROP_GRID_STYLE
case|:
name|private
operator|->
name|grid_style
operator|=
name|g_value_get_boolean
argument_list|(
name|value
argument_list|)
expr_stmt|;
break|break;
default|default:
name|G_OBJECT_WARN_INVALID_PROPERTY_ID
argument_list|(
name|object
argument_list|,
name|property_id
argument_list|,
name|pspec
argument_list|)
expr_stmt|;
break|break;
block|}
block|}
end_function

begin_function
specifier|static
name|void
DECL|function|gimp_canvas_grid_get_property (GObject * object,guint property_id,GValue * value,GParamSpec * pspec)
name|gimp_canvas_grid_get_property
parameter_list|(
name|GObject
modifier|*
name|object
parameter_list|,
name|guint
name|property_id
parameter_list|,
name|GValue
modifier|*
name|value
parameter_list|,
name|GParamSpec
modifier|*
name|pspec
parameter_list|)
block|{
name|GimpCanvasGridPrivate
modifier|*
name|private
init|=
name|GET_PRIVATE
argument_list|(
name|object
argument_list|)
decl_stmt|;
switch|switch
condition|(
name|property_id
condition|)
block|{
case|case
name|PROP_GRID
case|:
name|g_value_set_object
argument_list|(
name|value
argument_list|,
name|private
operator|->
name|grid
argument_list|)
expr_stmt|;
break|break;
case|case
name|PROP_GRID_STYLE
case|:
name|g_value_set_boolean
argument_list|(
name|value
argument_list|,
name|private
operator|->
name|grid_style
argument_list|)
expr_stmt|;
break|break;
default|default:
name|G_OBJECT_WARN_INVALID_PROPERTY_ID
argument_list|(
name|object
argument_list|,
name|property_id
argument_list|,
name|pspec
argument_list|)
expr_stmt|;
break|break;
block|}
block|}
end_function

begin_function
specifier|static
name|void
DECL|function|gimp_canvas_grid_draw (GimpCanvasItem * item,GimpDisplayShell * shell,cairo_t * cr)
name|gimp_canvas_grid_draw
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
name|GimpCanvasGridPrivate
modifier|*
name|private
init|=
name|GET_PRIVATE
argument_list|(
name|item
argument_list|)
decl_stmt|;
name|GimpImage
modifier|*
name|image
init|=
name|gimp_display_get_image
argument_list|(
name|shell
operator|->
name|display
argument_list|)
decl_stmt|;
name|gdouble
name|x
decl_stmt|,
name|y
decl_stmt|;
name|gdouble
name|dx1
decl_stmt|,
name|dy1
decl_stmt|,
name|dx2
decl_stmt|,
name|dy2
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
name|gdouble
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
name|g_return_if_fail
argument_list|(
name|private
operator|->
name|grid
operator|->
name|xspacing
operator|>
literal|0
operator|&&
name|private
operator|->
name|grid
operator|->
name|yspacing
operator|>
literal|0
argument_list|)
expr_stmt|;
comment|/*  skip grid drawing when the space between grid lines starts    *  disappearing, see bug #599267.    */
if|if
condition|(
name|private
operator|->
name|grid
operator|->
name|xspacing
operator|*
name|shell
operator|->
name|scale_x
operator|<
literal|2.0
operator|||
name|private
operator|->
name|grid
operator|->
name|yspacing
operator|*
name|shell
operator|->
name|scale_y
operator|<
literal|2.0
condition|)
return|return;
name|cairo_clip_extents
argument_list|(
name|cr
argument_list|,
operator|&
name|dx1
argument_list|,
operator|&
name|dy1
argument_list|,
operator|&
name|dx2
argument_list|,
operator|&
name|dy2
argument_list|)
expr_stmt|;
name|x1
operator|=
name|floor
argument_list|(
name|dx1
argument_list|)
expr_stmt|;
name|y1
operator|=
name|floor
argument_list|(
name|dy1
argument_list|)
expr_stmt|;
name|x2
operator|=
name|ceil
argument_list|(
name|dx2
argument_list|)
expr_stmt|;
name|y2
operator|=
name|ceil
argument_list|(
name|dy2
argument_list|)
expr_stmt|;
name|width
operator|=
name|gimp_image_get_width
argument_list|(
name|image
argument_list|)
expr_stmt|;
name|height
operator|=
name|gimp_image_get_height
argument_list|(
name|image
argument_list|)
expr_stmt|;
name|x_offset
operator|=
name|private
operator|->
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
name|private
operator|->
name|grid
operator|->
name|xspacing
expr_stmt|;
name|y_offset
operator|=
name|private
operator|->
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
name|private
operator|->
name|grid
operator|->
name|yspacing
expr_stmt|;
switch|switch
condition|(
name|private
operator|->
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
name|private
operator|->
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
name|private
operator|->
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
block|{
name|cairo_move_to
argument_list|(
name|cr
argument_list|,
name|x_real
argument_list|,
name|y_real
operator|+
literal|0.5
argument_list|)
expr_stmt|;
name|cairo_line_to
argument_list|(
name|cr
argument_list|,
name|x_real
operator|+
literal|1
argument_list|,
name|y_real
operator|+
literal|0.5
argument_list|)
expr_stmt|;
block|}
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
name|private
operator|->
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
name|private
operator|->
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
block|{
name|cairo_move_to
argument_list|(
name|cr
argument_list|,
name|x_real
operator|+
literal|0.5
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
argument_list|)
expr_stmt|;
name|cairo_line_to
argument_list|(
name|cr
argument_list|,
name|x_real
operator|+
literal|0.5
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
operator|+
literal|1
argument_list|)
expr_stmt|;
block|}
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
block|{
name|cairo_move_to
argument_list|(
name|cr
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
operator|+
literal|0.5
argument_list|)
expr_stmt|;
name|cairo_line_to
argument_list|(
name|cr
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
operator|+
literal|1
argument_list|,
name|y_real
operator|+
literal|0.5
argument_list|)
expr_stmt|;
block|}
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
name|private
operator|->
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
block|{
name|cairo_move_to
argument_list|(
name|cr
argument_list|,
name|x_real
operator|+
literal|0.5
argument_list|,
name|y0
argument_list|)
expr_stmt|;
name|cairo_line_to
argument_list|(
name|cr
argument_list|,
name|x_real
operator|+
literal|0.5
argument_list|,
name|y3
operator|+
literal|1
argument_list|)
expr_stmt|;
block|}
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
name|private
operator|->
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
block|{
name|cairo_move_to
argument_list|(
name|cr
argument_list|,
name|x0
argument_list|,
name|y_real
operator|+
literal|0.5
argument_list|)
expr_stmt|;
name|cairo_line_to
argument_list|(
name|cr
argument_list|,
name|x3
operator|+
literal|1
argument_list|,
name|y_real
operator|+
literal|0.5
argument_list|)
expr_stmt|;
block|}
block|}
break|break;
block|}
name|_gimp_canvas_item_stroke
argument_list|(
name|item
argument_list|,
name|cr
argument_list|)
expr_stmt|;
block|}
end_function

begin_function
specifier|static
name|cairo_region_t
modifier|*
DECL|function|gimp_canvas_grid_get_extents (GimpCanvasItem * item,GimpDisplayShell * shell)
name|gimp_canvas_grid_get_extents
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
name|GimpImage
modifier|*
name|image
init|=
name|gimp_display_get_image
argument_list|(
name|shell
operator|->
name|display
argument_list|)
decl_stmt|;
name|cairo_rectangle_int_t
name|rectangle
decl_stmt|;
name|gdouble
name|x1
decl_stmt|,
name|y1
decl_stmt|;
name|gdouble
name|x2
decl_stmt|,
name|y2
decl_stmt|;
name|gint
name|w
decl_stmt|,
name|h
decl_stmt|;
if|if
condition|(
operator|!
name|image
condition|)
return|return
name|NULL
return|;
name|w
operator|=
name|gimp_image_get_width
argument_list|(
name|image
argument_list|)
expr_stmt|;
name|h
operator|=
name|gimp_image_get_height
argument_list|(
name|image
argument_list|)
expr_stmt|;
name|gimp_display_shell_transform_xy_f
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
argument_list|)
expr_stmt|;
name|gimp_display_shell_transform_xy_f
argument_list|(
name|shell
argument_list|,
name|w
argument_list|,
name|h
argument_list|,
operator|&
name|x2
argument_list|,
operator|&
name|y2
argument_list|)
expr_stmt|;
name|rectangle
operator|.
name|x
operator|=
name|floor
argument_list|(
name|x1
argument_list|)
expr_stmt|;
name|rectangle
operator|.
name|y
operator|=
name|floor
argument_list|(
name|y1
argument_list|)
expr_stmt|;
name|rectangle
operator|.
name|width
operator|=
name|ceil
argument_list|(
name|x2
argument_list|)
operator|-
name|rectangle
operator|.
name|x
expr_stmt|;
name|rectangle
operator|.
name|height
operator|=
name|ceil
argument_list|(
name|y2
argument_list|)
operator|-
name|rectangle
operator|.
name|y
expr_stmt|;
return|return
name|cairo_region_create_rectangle
argument_list|(
operator|&
name|rectangle
argument_list|)
return|;
block|}
end_function

begin_function
specifier|static
name|void
DECL|function|gimp_canvas_grid_stroke (GimpCanvasItem * item,GimpDisplayShell * shell,cairo_t * cr)
name|gimp_canvas_grid_stroke
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
name|GimpCanvasGridPrivate
modifier|*
name|private
init|=
name|GET_PRIVATE
argument_list|(
name|item
argument_list|)
decl_stmt|;
if|if
condition|(
name|private
operator|->
name|grid_style
condition|)
block|{
name|cairo_translate
argument_list|(
name|cr
argument_list|,
operator|-
name|shell
operator|->
name|offset_x
argument_list|,
operator|-
name|shell
operator|->
name|offset_y
argument_list|)
expr_stmt|;
name|gimp_display_shell_set_grid_style
argument_list|(
name|shell
argument_list|,
name|cr
argument_list|,
name|private
operator|->
name|grid
argument_list|)
expr_stmt|;
name|cairo_stroke
argument_list|(
name|cr
argument_list|)
expr_stmt|;
block|}
else|else
block|{
name|GIMP_CANVAS_ITEM_CLASS
argument_list|(
name|parent_class
argument_list|)
operator|->
name|stroke
argument_list|(
name|item
argument_list|,
name|shell
argument_list|,
name|cr
argument_list|)
expr_stmt|;
block|}
block|}
end_function

begin_function
name|GimpCanvasItem
modifier|*
DECL|function|gimp_canvas_grid_new (GimpDisplayShell * shell,GimpGrid * grid)
name|gimp_canvas_grid_new
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
name|g_return_val_if_fail
argument_list|(
name|grid
operator|==
name|NULL
operator|||
name|GIMP_IS_GRID
argument_list|(
name|grid
argument_list|)
argument_list|,
name|NULL
argument_list|)
expr_stmt|;
return|return
name|g_object_new
argument_list|(
name|GIMP_TYPE_CANVAS_GRID
argument_list|,
literal|"shell"
argument_list|,
name|shell
argument_list|,
literal|"grid"
argument_list|,
name|grid
argument_list|,
name|NULL
argument_list|)
return|;
block|}
end_function

end_unit

