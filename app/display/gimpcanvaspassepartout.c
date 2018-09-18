begin_unit|revision:0.9.5;language:C;cregit-version:0.0.1
begin_comment
comment|/* GIMP - The GNU Image Manipulation Program  * Copyright (C) 1995 Spencer Kimball and Peter Mattis  *  * gimpcanvaspassepartout.c  * Copyright (C) 2010 Sven Neumann<sven@gimp.org>  *  * This program is free software: you can redistribute it and/or modify  * it under the terms of the GNU General Public License as published by  * the Free Software Foundation; either version 3 of the License, or  * (at your option) any later version.  *  * This program is distributed in the hope that it will be useful,  * but WITHOUT ANY WARRANTY; without even the implied warranty of  * MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the  * GNU General Public License for more details.  *  * You should have received a copy of the GNU General Public License  * along with this program.  If not, see<https://www.gnu.org/licenses/>.  */
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
file|"gimpcanvas-style.h"
end_include

begin_include
include|#
directive|include
file|"gimpcanvaspassepartout.h"
end_include

begin_include
include|#
directive|include
file|"gimpdisplayshell.h"
end_include

begin_include
include|#
directive|include
file|"gimpdisplayshell-scale.h"
end_include

begin_enum
enum|enum
DECL|enum|__anon2920a6930103
block|{
DECL|enumerator|PROP_0
name|PROP_0
block|,
DECL|enumerator|PROP_OPACITY
name|PROP_OPACITY
block|, }
enum|;
end_enum

begin_typedef
DECL|typedef|GimpCanvasPassePartoutPrivate
typedef|typedef
name|struct
name|_GimpCanvasPassePartoutPrivate
name|GimpCanvasPassePartoutPrivate
typedef|;
end_typedef

begin_struct
DECL|struct|_GimpCanvasPassePartoutPrivate
struct|struct
name|_GimpCanvasPassePartoutPrivate
block|{
DECL|member|opacity
name|gdouble
name|opacity
decl_stmt|;
block|}
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
value|((GimpCanvasPassePartoutPrivate *) gimp_canvas_passe_partout_get_instance_private ((GimpCanvasPassePartout *) (item)))
end_define

begin_comment
comment|/*  local function prototypes  */
end_comment

begin_function_decl
specifier|static
name|void
name|gimp_canvas_passe_partout_set_property
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
name|gimp_canvas_passe_partout_get_property
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
name|gimp_canvas_passe_partout_draw
parameter_list|(
name|GimpCanvasItem
modifier|*
name|item
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
name|gimp_canvas_passe_partout_get_extents
parameter_list|(
name|GimpCanvasItem
modifier|*
name|item
parameter_list|)
function_decl|;
end_function_decl

begin_function_decl
specifier|static
name|void
name|gimp_canvas_passe_partout_fill
parameter_list|(
name|GimpCanvasItem
modifier|*
name|item
parameter_list|,
name|cairo_t
modifier|*
name|cr
parameter_list|)
function_decl|;
end_function_decl

begin_macro
DECL|function|G_DEFINE_TYPE_WITH_PRIVATE (GimpCanvasPassePartout,gimp_canvas_passe_partout,GIMP_TYPE_CANVAS_RECTANGLE)
name|G_DEFINE_TYPE_WITH_PRIVATE
argument_list|(
argument|GimpCanvasPassePartout
argument_list|,
argument|gimp_canvas_passe_partout
argument_list|,
argument|GIMP_TYPE_CANVAS_RECTANGLE
argument_list|)
end_macro

begin_define
DECL|macro|parent_class
define|#
directive|define
name|parent_class
value|gimp_canvas_passe_partout_parent_class
end_define

begin_function
specifier|static
name|void
name|gimp_canvas_passe_partout_class_init
parameter_list|(
name|GimpCanvasPassePartoutClass
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
name|set_property
operator|=
name|gimp_canvas_passe_partout_set_property
expr_stmt|;
name|object_class
operator|->
name|get_property
operator|=
name|gimp_canvas_passe_partout_get_property
expr_stmt|;
name|item_class
operator|->
name|draw
operator|=
name|gimp_canvas_passe_partout_draw
expr_stmt|;
name|item_class
operator|->
name|get_extents
operator|=
name|gimp_canvas_passe_partout_get_extents
expr_stmt|;
name|item_class
operator|->
name|fill
operator|=
name|gimp_canvas_passe_partout_fill
expr_stmt|;
name|g_object_class_install_property
argument_list|(
name|object_class
argument_list|,
name|PROP_OPACITY
argument_list|,
name|g_param_spec_double
argument_list|(
literal|"opacity"
argument_list|,
name|NULL
argument_list|,
name|NULL
argument_list|,
literal|0.0
argument_list|,
literal|1.0
argument_list|,
literal|0.5
argument_list|,
name|GIMP_PARAM_READWRITE
argument_list|)
argument_list|)
expr_stmt|;
block|}
end_function

begin_function
specifier|static
name|void
DECL|function|gimp_canvas_passe_partout_init (GimpCanvasPassePartout * passe_partout)
name|gimp_canvas_passe_partout_init
parameter_list|(
name|GimpCanvasPassePartout
modifier|*
name|passe_partout
parameter_list|)
block|{ }
end_function

begin_function
specifier|static
name|void
DECL|function|gimp_canvas_passe_partout_set_property (GObject * object,guint property_id,const GValue * value,GParamSpec * pspec)
name|gimp_canvas_passe_partout_set_property
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
name|GimpCanvasPassePartoutPrivate
modifier|*
name|priv
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
name|PROP_OPACITY
case|:
name|priv
operator|->
name|opacity
operator|=
name|g_value_get_double
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
DECL|function|gimp_canvas_passe_partout_get_property (GObject * object,guint property_id,GValue * value,GParamSpec * pspec)
name|gimp_canvas_passe_partout_get_property
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
name|GimpCanvasPassePartoutPrivate
modifier|*
name|priv
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
name|PROP_OPACITY
case|:
name|g_value_set_double
argument_list|(
name|value
argument_list|,
name|priv
operator|->
name|opacity
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
DECL|function|gimp_canvas_passe_partout_draw (GimpCanvasItem * item,cairo_t * cr)
name|gimp_canvas_passe_partout_draw
parameter_list|(
name|GimpCanvasItem
modifier|*
name|item
parameter_list|,
name|cairo_t
modifier|*
name|cr
parameter_list|)
block|{
name|GimpDisplayShell
modifier|*
name|shell
init|=
name|gimp_canvas_item_get_shell
argument_list|(
name|item
argument_list|)
decl_stmt|;
name|gint
name|w
decl_stmt|,
name|h
decl_stmt|;
name|gimp_display_shell_scale_get_image_size
argument_list|(
name|shell
argument_list|,
operator|&
name|w
argument_list|,
operator|&
name|h
argument_list|)
expr_stmt|;
name|cairo_rectangle
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
argument_list|,
name|w
argument_list|,
name|h
argument_list|)
expr_stmt|;
name|GIMP_CANVAS_ITEM_CLASS
argument_list|(
name|parent_class
argument_list|)
operator|->
name|draw
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
DECL|function|gimp_canvas_passe_partout_get_extents (GimpCanvasItem * item)
name|gimp_canvas_passe_partout_get_extents
parameter_list|(
name|GimpCanvasItem
modifier|*
name|item
parameter_list|)
block|{
name|GimpDisplayShell
modifier|*
name|shell
init|=
name|gimp_canvas_item_get_shell
argument_list|(
name|item
argument_list|)
decl_stmt|;
name|cairo_rectangle_int_t
name|rectangle
decl_stmt|;
name|cairo_region_t
modifier|*
name|inner
decl_stmt|;
name|cairo_region_t
modifier|*
name|outer
decl_stmt|;
name|rectangle
operator|.
name|x
operator|=
operator|-
name|shell
operator|->
name|offset_x
expr_stmt|;
name|rectangle
operator|.
name|y
operator|=
operator|-
name|shell
operator|->
name|offset_y
expr_stmt|;
name|gimp_display_shell_scale_get_image_size
argument_list|(
name|shell
argument_list|,
operator|&
name|rectangle
operator|.
name|width
argument_list|,
operator|&
name|rectangle
operator|.
name|height
argument_list|)
expr_stmt|;
name|outer
operator|=
name|cairo_region_create_rectangle
argument_list|(
operator|&
name|rectangle
argument_list|)
expr_stmt|;
name|inner
operator|=
name|GIMP_CANVAS_ITEM_CLASS
argument_list|(
name|parent_class
argument_list|)
operator|->
name|get_extents
argument_list|(
name|item
argument_list|)
expr_stmt|;
name|cairo_region_xor
argument_list|(
name|outer
argument_list|,
name|inner
argument_list|)
expr_stmt|;
return|return
name|outer
return|;
block|}
end_function

begin_function
specifier|static
name|void
DECL|function|gimp_canvas_passe_partout_fill (GimpCanvasItem * item,cairo_t * cr)
name|gimp_canvas_passe_partout_fill
parameter_list|(
name|GimpCanvasItem
modifier|*
name|item
parameter_list|,
name|cairo_t
modifier|*
name|cr
parameter_list|)
block|{
name|GimpCanvasPassePartoutPrivate
modifier|*
name|priv
init|=
name|GET_PRIVATE
argument_list|(
name|item
argument_list|)
decl_stmt|;
name|cairo_set_fill_rule
argument_list|(
name|cr
argument_list|,
name|CAIRO_FILL_RULE_EVEN_ODD
argument_list|)
expr_stmt|;
name|cairo_clip
argument_list|(
name|cr
argument_list|)
expr_stmt|;
name|gimp_canvas_set_passe_partout_style
argument_list|(
name|gimp_canvas_item_get_canvas
argument_list|(
name|item
argument_list|)
argument_list|,
name|cr
argument_list|)
expr_stmt|;
name|cairo_paint_with_alpha
argument_list|(
name|cr
argument_list|,
name|priv
operator|->
name|opacity
argument_list|)
expr_stmt|;
block|}
end_function

begin_function
name|GimpCanvasItem
modifier|*
DECL|function|gimp_canvas_passe_partout_new (GimpDisplayShell * shell,gdouble x,gdouble y,gdouble width,gdouble height)
name|gimp_canvas_passe_partout_new
parameter_list|(
name|GimpDisplayShell
modifier|*
name|shell
parameter_list|,
name|gdouble
name|x
parameter_list|,
name|gdouble
name|y
parameter_list|,
name|gdouble
name|width
parameter_list|,
name|gdouble
name|height
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
return|return
name|g_object_new
argument_list|(
name|GIMP_TYPE_CANVAS_PASSE_PARTOUT
argument_list|,
literal|"shell"
argument_list|,
name|shell
argument_list|,
literal|"x"
argument_list|,
name|x
argument_list|,
literal|"y"
argument_list|,
name|y
argument_list|,
literal|"width"
argument_list|,
name|width
argument_list|,
literal|"height"
argument_list|,
name|height
argument_list|,
literal|"filled"
argument_list|,
name|TRUE
argument_list|,
name|NULL
argument_list|)
return|;
block|}
end_function

end_unit

