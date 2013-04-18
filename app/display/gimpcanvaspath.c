begin_unit|revision:0.9.5;language:C;cregit-version:0.0.1
begin_comment
comment|/* GIMP - The GNU Image Manipulation Program  * Copyright (C) 1995 Spencer Kimball and Peter Mattis  *  * gimpcanvaspath.c  * Copyright (C) 2010 Michael Natterer<mitch@gimp.org>  *  * This program is free software: you can redistribute it and/or modify  * it under the terms of the GNU General Public License as published by  * the Free Software Foundation; either version 3 of the License, or  * (at your option) any later version.  *  * This program is distributed in the hope that it will be useful,  * but WITHOUT ANY WARRANTY; without even the implied warranty of  * MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the  * GNU General Public License for more details.  *  * You should have received a copy of the GNU General Public License  * along with this program.  If not, see<http://www.gnu.org/licenses/>.  */
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
file|"display-types.h"
end_include

begin_include
include|#
directive|include
file|"core/gimpbezierdesc.h"
end_include

begin_include
include|#
directive|include
file|"core/gimpparamspecs.h"
end_include

begin_include
include|#
directive|include
file|"gimpcanvaspath.h"
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

begin_enum
enum|enum
DECL|enum|__anon2b7a80660103
block|{
DECL|enumerator|PROP_0
name|PROP_0
block|,
DECL|enumerator|PROP_PATH
name|PROP_PATH
block|,
DECL|enumerator|PROP_X
name|PROP_X
block|,
DECL|enumerator|PROP_Y
name|PROP_Y
block|,
DECL|enumerator|PROP_FILLED
name|PROP_FILLED
block|,
DECL|enumerator|PROP_PATH_STYLE
name|PROP_PATH_STYLE
block|}
enum|;
end_enum

begin_typedef
DECL|typedef|GimpCanvasPathPrivate
typedef|typedef
name|struct
name|_GimpCanvasPathPrivate
name|GimpCanvasPathPrivate
typedef|;
end_typedef

begin_struct
DECL|struct|_GimpCanvasPathPrivate
struct|struct
name|_GimpCanvasPathPrivate
block|{
DECL|member|path
name|cairo_path_t
modifier|*
name|path
decl_stmt|;
DECL|member|x
name|gdouble
name|x
decl_stmt|;
DECL|member|y
name|gdouble
name|y
decl_stmt|;
DECL|member|filled
name|gboolean
name|filled
decl_stmt|;
DECL|member|path_style
name|GimpPathStyle
name|path_style
decl_stmt|;
block|}
struct|;
end_struct

begin_define
DECL|macro|GET_PRIVATE (path)
define|#
directive|define
name|GET_PRIVATE
parameter_list|(
name|path
parameter_list|)
define|\
value|G_TYPE_INSTANCE_GET_PRIVATE (path, \                                      GIMP_TYPE_CANVAS_PATH, \                                      GimpCanvasPathPrivate)
end_define

begin_comment
comment|/*  local function prototypes  */
end_comment

begin_function_decl
specifier|static
name|void
name|gimp_canvas_path_finalize
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
name|gimp_canvas_path_set_property
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
name|gimp_canvas_path_get_property
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
name|gimp_canvas_path_draw
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
name|gimp_canvas_path_get_extents
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
name|gimp_canvas_path_stroke
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
DECL|function|G_DEFINE_TYPE (GimpCanvasPath,gimp_canvas_path,GIMP_TYPE_CANVAS_ITEM)
name|G_DEFINE_TYPE
argument_list|(
argument|GimpCanvasPath
argument_list|,
argument|gimp_canvas_path
argument_list|,
argument|GIMP_TYPE_CANVAS_ITEM
argument_list|)
end_macro

begin_define
DECL|macro|parent_class
define|#
directive|define
name|parent_class
value|gimp_canvas_path_parent_class
end_define

begin_function
specifier|static
name|void
name|gimp_canvas_path_class_init
parameter_list|(
name|GimpCanvasPathClass
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
name|gimp_canvas_path_finalize
expr_stmt|;
name|object_class
operator|->
name|set_property
operator|=
name|gimp_canvas_path_set_property
expr_stmt|;
name|object_class
operator|->
name|get_property
operator|=
name|gimp_canvas_path_get_property
expr_stmt|;
name|item_class
operator|->
name|draw
operator|=
name|gimp_canvas_path_draw
expr_stmt|;
name|item_class
operator|->
name|get_extents
operator|=
name|gimp_canvas_path_get_extents
expr_stmt|;
name|item_class
operator|->
name|stroke
operator|=
name|gimp_canvas_path_stroke
expr_stmt|;
name|g_object_class_install_property
argument_list|(
name|object_class
argument_list|,
name|PROP_PATH
argument_list|,
name|g_param_spec_boxed
argument_list|(
literal|"path"
argument_list|,
name|NULL
argument_list|,
name|NULL
argument_list|,
name|GIMP_TYPE_BEZIER_DESC
argument_list|,
name|GIMP_PARAM_READWRITE
argument_list|)
argument_list|)
expr_stmt|;
name|g_object_class_install_property
argument_list|(
name|object_class
argument_list|,
name|PROP_X
argument_list|,
name|g_param_spec_double
argument_list|(
literal|"x"
argument_list|,
name|NULL
argument_list|,
name|NULL
argument_list|,
operator|-
name|GIMP_MAX_IMAGE_SIZE
argument_list|,
name|GIMP_MAX_IMAGE_SIZE
argument_list|,
literal|0
argument_list|,
name|GIMP_PARAM_READWRITE
argument_list|)
argument_list|)
expr_stmt|;
name|g_object_class_install_property
argument_list|(
name|object_class
argument_list|,
name|PROP_Y
argument_list|,
name|g_param_spec_double
argument_list|(
literal|"y"
argument_list|,
name|NULL
argument_list|,
name|NULL
argument_list|,
operator|-
name|GIMP_MAX_IMAGE_SIZE
argument_list|,
name|GIMP_MAX_IMAGE_SIZE
argument_list|,
literal|0
argument_list|,
name|GIMP_PARAM_READWRITE
argument_list|)
argument_list|)
expr_stmt|;
name|g_object_class_install_property
argument_list|(
name|object_class
argument_list|,
name|PROP_FILLED
argument_list|,
name|g_param_spec_boolean
argument_list|(
literal|"filled"
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
name|g_object_class_install_property
argument_list|(
name|object_class
argument_list|,
name|PROP_PATH_STYLE
argument_list|,
name|g_param_spec_enum
argument_list|(
literal|"path-style"
argument_list|,
name|NULL
argument_list|,
name|NULL
argument_list|,
name|GIMP_TYPE_PATH_STYLE
argument_list|,
name|GIMP_PATH_STYLE_DEFAULT
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
name|GimpCanvasPathPrivate
argument_list|)
argument_list|)
expr_stmt|;
block|}
end_function

begin_function
specifier|static
name|void
DECL|function|gimp_canvas_path_init (GimpCanvasPath * path)
name|gimp_canvas_path_init
parameter_list|(
name|GimpCanvasPath
modifier|*
name|path
parameter_list|)
block|{ }
end_function

begin_function
specifier|static
name|void
DECL|function|gimp_canvas_path_finalize (GObject * object)
name|gimp_canvas_path_finalize
parameter_list|(
name|GObject
modifier|*
name|object
parameter_list|)
block|{
name|GimpCanvasPathPrivate
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
name|path
condition|)
block|{
name|gimp_bezier_desc_free
argument_list|(
name|private
operator|->
name|path
argument_list|)
expr_stmt|;
name|private
operator|->
name|path
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
DECL|function|gimp_canvas_path_set_property (GObject * object,guint property_id,const GValue * value,GParamSpec * pspec)
name|gimp_canvas_path_set_property
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
name|GimpCanvasPathPrivate
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
name|PROP_PATH
case|:
if|if
condition|(
name|private
operator|->
name|path
condition|)
name|gimp_bezier_desc_free
argument_list|(
name|private
operator|->
name|path
argument_list|)
expr_stmt|;
name|private
operator|->
name|path
operator|=
name|g_value_dup_boxed
argument_list|(
name|value
argument_list|)
expr_stmt|;
break|break;
case|case
name|PROP_X
case|:
name|private
operator|->
name|x
operator|=
name|g_value_get_double
argument_list|(
name|value
argument_list|)
expr_stmt|;
break|break;
case|case
name|PROP_Y
case|:
name|private
operator|->
name|y
operator|=
name|g_value_get_double
argument_list|(
name|value
argument_list|)
expr_stmt|;
break|break;
case|case
name|PROP_FILLED
case|:
name|private
operator|->
name|filled
operator|=
name|g_value_get_boolean
argument_list|(
name|value
argument_list|)
expr_stmt|;
break|break;
case|case
name|PROP_PATH_STYLE
case|:
name|private
operator|->
name|path_style
operator|=
name|g_value_get_enum
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
DECL|function|gimp_canvas_path_get_property (GObject * object,guint property_id,GValue * value,GParamSpec * pspec)
name|gimp_canvas_path_get_property
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
name|GimpCanvasPathPrivate
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
name|PROP_PATH
case|:
name|g_value_set_boxed
argument_list|(
name|value
argument_list|,
name|private
operator|->
name|path
argument_list|)
expr_stmt|;
break|break;
case|case
name|PROP_X
case|:
name|g_value_set_double
argument_list|(
name|value
argument_list|,
name|private
operator|->
name|x
argument_list|)
expr_stmt|;
break|break;
case|case
name|PROP_Y
case|:
name|g_value_set_double
argument_list|(
name|value
argument_list|,
name|private
operator|->
name|y
argument_list|)
expr_stmt|;
break|break;
case|case
name|PROP_FILLED
case|:
name|g_value_set_boolean
argument_list|(
name|value
argument_list|,
name|private
operator|->
name|filled
argument_list|)
expr_stmt|;
break|break;
case|case
name|PROP_PATH_STYLE
case|:
name|g_value_set_enum
argument_list|(
name|value
argument_list|,
name|private
operator|->
name|path_style
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
DECL|function|gimp_canvas_path_draw (GimpCanvasItem * item,GimpDisplayShell * shell,cairo_t * cr)
name|gimp_canvas_path_draw
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
name|GimpCanvasPathPrivate
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
name|path
condition|)
block|{
name|cairo_save
argument_list|(
name|cr
argument_list|)
expr_stmt|;
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
name|cairo_scale
argument_list|(
name|cr
argument_list|,
name|shell
operator|->
name|scale_x
argument_list|,
name|shell
operator|->
name|scale_y
argument_list|)
expr_stmt|;
name|cairo_translate
argument_list|(
name|cr
argument_list|,
name|private
operator|->
name|x
argument_list|,
name|private
operator|->
name|y
argument_list|)
expr_stmt|;
name|cairo_append_path
argument_list|(
name|cr
argument_list|,
name|private
operator|->
name|path
argument_list|)
expr_stmt|;
name|cairo_restore
argument_list|(
name|cr
argument_list|)
expr_stmt|;
if|if
condition|(
name|private
operator|->
name|filled
condition|)
name|_gimp_canvas_item_fill
argument_list|(
name|item
argument_list|,
name|cr
argument_list|)
expr_stmt|;
else|else
name|_gimp_canvas_item_stroke
argument_list|(
name|item
argument_list|,
name|cr
argument_list|)
expr_stmt|;
block|}
block|}
end_function

begin_function
specifier|static
name|cairo_region_t
modifier|*
DECL|function|gimp_canvas_path_get_extents (GimpCanvasItem * item,GimpDisplayShell * shell)
name|gimp_canvas_path_get_extents
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
name|GimpCanvasPathPrivate
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
name|path
operator|&&
name|gtk_widget_get_realized
argument_list|(
name|shell
operator|->
name|canvas
argument_list|)
condition|)
block|{
name|cairo_t
modifier|*
name|cr
decl_stmt|;
name|cairo_rectangle_int_t
name|rectangle
decl_stmt|;
name|gdouble
name|x1
decl_stmt|,
name|y1
decl_stmt|,
name|x2
decl_stmt|,
name|y2
decl_stmt|;
name|cr
operator|=
name|gdk_cairo_create
argument_list|(
name|gtk_widget_get_window
argument_list|(
name|shell
operator|->
name|canvas
argument_list|)
argument_list|)
expr_stmt|;
name|cairo_save
argument_list|(
name|cr
argument_list|)
expr_stmt|;
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
name|cairo_scale
argument_list|(
name|cr
argument_list|,
name|shell
operator|->
name|scale_x
argument_list|,
name|shell
operator|->
name|scale_y
argument_list|)
expr_stmt|;
name|cairo_translate
argument_list|(
name|cr
argument_list|,
name|private
operator|->
name|x
argument_list|,
name|private
operator|->
name|y
argument_list|)
expr_stmt|;
name|cairo_append_path
argument_list|(
name|cr
argument_list|,
name|private
operator|->
name|path
argument_list|)
expr_stmt|;
name|cairo_restore
argument_list|(
name|cr
argument_list|)
expr_stmt|;
name|cairo_path_extents
argument_list|(
name|cr
argument_list|,
operator|&
name|x1
argument_list|,
operator|&
name|y1
argument_list|,
operator|&
name|x2
argument_list|,
operator|&
name|y2
argument_list|)
expr_stmt|;
name|cairo_destroy
argument_list|(
name|cr
argument_list|)
expr_stmt|;
if|if
condition|(
name|private
operator|->
name|filled
condition|)
block|{
name|rectangle
operator|.
name|x
operator|=
name|floor
argument_list|(
name|x1
operator|-
literal|1.0
argument_list|)
expr_stmt|;
name|rectangle
operator|.
name|y
operator|=
name|floor
argument_list|(
name|y1
operator|-
literal|1.0
argument_list|)
expr_stmt|;
name|rectangle
operator|.
name|width
operator|=
name|ceil
argument_list|(
name|x2
operator|+
literal|1.0
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
operator|+
literal|1.0
argument_list|)
operator|-
name|rectangle
operator|.
name|y
expr_stmt|;
block|}
else|else
block|{
name|rectangle
operator|.
name|x
operator|=
name|floor
argument_list|(
name|x1
operator|-
literal|1.5
argument_list|)
expr_stmt|;
name|rectangle
operator|.
name|y
operator|=
name|floor
argument_list|(
name|y1
operator|-
literal|1.5
argument_list|)
expr_stmt|;
name|rectangle
operator|.
name|width
operator|=
name|ceil
argument_list|(
name|x2
operator|+
literal|1.5
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
operator|+
literal|1.5
argument_list|)
operator|-
name|rectangle
operator|.
name|y
expr_stmt|;
block|}
return|return
name|cairo_region_create_rectangle
argument_list|(
operator|&
name|rectangle
argument_list|)
return|;
block|}
return|return
name|NULL
return|;
block|}
end_function

begin_function
specifier|static
name|void
DECL|function|gimp_canvas_path_stroke (GimpCanvasItem * item,GimpDisplayShell * shell,cairo_t * cr)
name|gimp_canvas_path_stroke
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
name|GimpCanvasPathPrivate
modifier|*
name|private
init|=
name|GET_PRIVATE
argument_list|(
name|item
argument_list|)
decl_stmt|;
name|gboolean
name|active
decl_stmt|;
switch|switch
condition|(
name|private
operator|->
name|path_style
condition|)
block|{
case|case
name|GIMP_PATH_STYLE_VECTORS
case|:
name|active
operator|=
name|gimp_canvas_item_get_highlight
argument_list|(
name|item
argument_list|)
expr_stmt|;
name|gimp_display_shell_set_vectors_bg_style
argument_list|(
name|shell
argument_list|,
name|cr
argument_list|,
name|active
argument_list|)
expr_stmt|;
name|cairo_stroke_preserve
argument_list|(
name|cr
argument_list|)
expr_stmt|;
name|gimp_display_shell_set_vectors_fg_style
argument_list|(
name|shell
argument_list|,
name|cr
argument_list|,
name|active
argument_list|)
expr_stmt|;
name|cairo_stroke
argument_list|(
name|cr
argument_list|)
expr_stmt|;
break|break;
case|case
name|GIMP_PATH_STYLE_OUTLINE
case|:
name|gimp_display_shell_set_outline_bg_style
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
name|gimp_display_shell_set_outline_fg_style
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
break|break;
case|case
name|GIMP_PATH_STYLE_DEFAULT
case|:
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
break|break;
block|}
block|}
end_function

begin_function
name|GimpCanvasItem
modifier|*
DECL|function|gimp_canvas_path_new (GimpDisplayShell * shell,const GimpBezierDesc * bezier,gdouble x,gdouble y,gboolean filled,GimpPathStyle style)
name|gimp_canvas_path_new
parameter_list|(
name|GimpDisplayShell
modifier|*
name|shell
parameter_list|,
specifier|const
name|GimpBezierDesc
modifier|*
name|bezier
parameter_list|,
name|gdouble
name|x
parameter_list|,
name|gdouble
name|y
parameter_list|,
name|gboolean
name|filled
parameter_list|,
name|GimpPathStyle
name|style
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
name|GIMP_TYPE_CANVAS_PATH
argument_list|,
literal|"shell"
argument_list|,
name|shell
argument_list|,
literal|"path"
argument_list|,
name|bezier
argument_list|,
literal|"x"
argument_list|,
name|x
argument_list|,
literal|"y"
argument_list|,
name|y
argument_list|,
literal|"filled"
argument_list|,
name|filled
argument_list|,
literal|"path-style"
argument_list|,
name|style
argument_list|,
name|NULL
argument_list|)
return|;
block|}
end_function

begin_function
name|void
DECL|function|gimp_canvas_path_set (GimpCanvasItem * path,const GimpBezierDesc * bezier)
name|gimp_canvas_path_set
parameter_list|(
name|GimpCanvasItem
modifier|*
name|path
parameter_list|,
specifier|const
name|GimpBezierDesc
modifier|*
name|bezier
parameter_list|)
block|{
name|g_return_if_fail
argument_list|(
name|GIMP_IS_CANVAS_PATH
argument_list|(
name|path
argument_list|)
argument_list|)
expr_stmt|;
name|gimp_canvas_item_begin_change
argument_list|(
name|path
argument_list|)
expr_stmt|;
name|g_object_set
argument_list|(
name|path
argument_list|,
literal|"path"
argument_list|,
name|bezier
argument_list|,
name|NULL
argument_list|)
expr_stmt|;
name|gimp_canvas_item_end_change
argument_list|(
name|path
argument_list|)
expr_stmt|;
block|}
end_function

end_unit

