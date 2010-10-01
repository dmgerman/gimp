begin_unit|revision:0.9.5;language:C;cregit-version:0.0.1
begin_comment
comment|/* GIMP - The GNU Image Manipulation Program  * Copyright (C) 1995 Spencer Kimball and Peter Mattis  *  * gimpcanvasguide.c  * Copyright (C) 2010 Michael Natterer<mitch@gimp.org>  *  * This program is free software: you can redistribute it and/or modify  * it under the terms of the GNU General Public License as published by  * the Free Software Foundation; either version 3 of the License, or  * (at your option) any later version.  *  * This program is distributed in the hope that it will be useful,  * but WITHOUT ANY WARRANTY; without even the implied warranty of  * MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the  * GNU General Public License for more details.  *  * You should have received a copy of the GNU General Public License  * along with this program.  If not, see<http://www.gnu.org/licenses/>.  */
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
file|"gimpcanvasguide.h"
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
DECL|enum|__anon2c3e9d3e0103
block|{
DECL|enumerator|PROP_0
name|PROP_0
block|,
DECL|enumerator|PROP_ORIENTATION
name|PROP_ORIENTATION
block|,
DECL|enumerator|PROP_POSITION
name|PROP_POSITION
block|,
DECL|enumerator|PROP_GUIDE_STYLE
name|PROP_GUIDE_STYLE
block|}
enum|;
end_enum

begin_typedef
DECL|typedef|GimpCanvasGuidePrivate
typedef|typedef
name|struct
name|_GimpCanvasGuidePrivate
name|GimpCanvasGuidePrivate
typedef|;
end_typedef

begin_struct
DECL|struct|_GimpCanvasGuidePrivate
struct|struct
name|_GimpCanvasGuidePrivate
block|{
DECL|member|orientation
name|GimpOrientationType
name|orientation
decl_stmt|;
DECL|member|position
name|gint
name|position
decl_stmt|;
DECL|member|guide_style
name|gboolean
name|guide_style
decl_stmt|;
block|}
struct|;
end_struct

begin_define
DECL|macro|GET_PRIVATE (guide)
define|#
directive|define
name|GET_PRIVATE
parameter_list|(
name|guide
parameter_list|)
define|\
value|G_TYPE_INSTANCE_GET_PRIVATE (guide, \                                      GIMP_TYPE_CANVAS_GUIDE, \                                      GimpCanvasGuidePrivate)
end_define

begin_comment
comment|/*  local function prototypes  */
end_comment

begin_function_decl
specifier|static
name|void
name|gimp_canvas_guide_set_property
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
name|gimp_canvas_guide_get_property
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
name|gimp_canvas_guide_draw
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
name|gimp_canvas_guide_get_extents
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
name|gimp_canvas_guide_stroke
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
DECL|function|G_DEFINE_TYPE (GimpCanvasGuide,gimp_canvas_guide,GIMP_TYPE_CANVAS_ITEM)
name|G_DEFINE_TYPE
argument_list|(
argument|GimpCanvasGuide
argument_list|,
argument|gimp_canvas_guide
argument_list|,
argument|GIMP_TYPE_CANVAS_ITEM
argument_list|)
end_macro

begin_define
DECL|macro|parent_class
define|#
directive|define
name|parent_class
value|gimp_canvas_guide_parent_class
end_define

begin_function
specifier|static
name|void
name|gimp_canvas_guide_class_init
parameter_list|(
name|GimpCanvasGuideClass
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
name|gimp_canvas_guide_set_property
expr_stmt|;
name|object_class
operator|->
name|get_property
operator|=
name|gimp_canvas_guide_get_property
expr_stmt|;
name|item_class
operator|->
name|draw
operator|=
name|gimp_canvas_guide_draw
expr_stmt|;
name|item_class
operator|->
name|get_extents
operator|=
name|gimp_canvas_guide_get_extents
expr_stmt|;
name|item_class
operator|->
name|stroke
operator|=
name|gimp_canvas_guide_stroke
expr_stmt|;
name|g_object_class_install_property
argument_list|(
name|object_class
argument_list|,
name|PROP_ORIENTATION
argument_list|,
name|g_param_spec_enum
argument_list|(
literal|"orientation"
argument_list|,
name|NULL
argument_list|,
name|NULL
argument_list|,
name|GIMP_TYPE_ORIENTATION_TYPE
argument_list|,
name|GIMP_ORIENTATION_HORIZONTAL
argument_list|,
name|GIMP_PARAM_READWRITE
argument_list|)
argument_list|)
expr_stmt|;
name|g_object_class_install_property
argument_list|(
name|object_class
argument_list|,
name|PROP_POSITION
argument_list|,
name|g_param_spec_int
argument_list|(
literal|"position"
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
name|PROP_GUIDE_STYLE
argument_list|,
name|g_param_spec_boolean
argument_list|(
literal|"guide-style"
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
name|GimpCanvasGuidePrivate
argument_list|)
argument_list|)
expr_stmt|;
block|}
end_function

begin_function
specifier|static
name|void
DECL|function|gimp_canvas_guide_init (GimpCanvasGuide * guide)
name|gimp_canvas_guide_init
parameter_list|(
name|GimpCanvasGuide
modifier|*
name|guide
parameter_list|)
block|{ }
end_function

begin_function
specifier|static
name|void
DECL|function|gimp_canvas_guide_set_property (GObject * object,guint property_id,const GValue * value,GParamSpec * pspec)
name|gimp_canvas_guide_set_property
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
name|GimpCanvasGuidePrivate
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
name|PROP_ORIENTATION
case|:
name|private
operator|->
name|orientation
operator|=
name|g_value_get_enum
argument_list|(
name|value
argument_list|)
expr_stmt|;
break|break;
case|case
name|PROP_POSITION
case|:
name|private
operator|->
name|position
operator|=
name|g_value_get_int
argument_list|(
name|value
argument_list|)
expr_stmt|;
break|break;
case|case
name|PROP_GUIDE_STYLE
case|:
name|private
operator|->
name|guide_style
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
DECL|function|gimp_canvas_guide_get_property (GObject * object,guint property_id,GValue * value,GParamSpec * pspec)
name|gimp_canvas_guide_get_property
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
name|GimpCanvasGuidePrivate
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
name|PROP_ORIENTATION
case|:
name|g_value_set_enum
argument_list|(
name|value
argument_list|,
name|private
operator|->
name|orientation
argument_list|)
expr_stmt|;
break|break;
case|case
name|PROP_POSITION
case|:
name|g_value_set_int
argument_list|(
name|value
argument_list|,
name|private
operator|->
name|position
argument_list|)
expr_stmt|;
break|break;
case|case
name|PROP_GUIDE_STYLE
case|:
name|g_value_set_boolean
argument_list|(
name|value
argument_list|,
name|private
operator|->
name|guide_style
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
DECL|function|gimp_canvas_guide_transform (GimpCanvasItem * item,GimpDisplayShell * shell,gdouble * x1,gdouble * y1,gdouble * x2,gdouble * y2)
name|gimp_canvas_guide_transform
parameter_list|(
name|GimpCanvasItem
modifier|*
name|item
parameter_list|,
name|GimpDisplayShell
modifier|*
name|shell
parameter_list|,
name|gdouble
modifier|*
name|x1
parameter_list|,
name|gdouble
modifier|*
name|y1
parameter_list|,
name|gdouble
modifier|*
name|x2
parameter_list|,
name|gdouble
modifier|*
name|y2
parameter_list|)
block|{
name|GimpCanvasGuidePrivate
modifier|*
name|private
init|=
name|GET_PRIVATE
argument_list|(
name|item
argument_list|)
decl_stmt|;
name|GtkAllocation
name|allocation
decl_stmt|;
name|gint
name|x
decl_stmt|,
name|y
decl_stmt|;
name|gtk_widget_get_allocation
argument_list|(
name|shell
operator|->
name|canvas
argument_list|,
operator|&
name|allocation
argument_list|)
expr_stmt|;
operator|*
name|x1
operator|=
literal|0
expr_stmt|;
operator|*
name|y1
operator|=
literal|0
expr_stmt|;
operator|*
name|x2
operator|=
name|allocation
operator|.
name|width
expr_stmt|;
operator|*
name|y2
operator|=
name|allocation
operator|.
name|height
expr_stmt|;
switch|switch
condition|(
name|private
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
name|private
operator|->
name|position
argument_list|,
operator|&
name|x
argument_list|,
operator|&
name|y
argument_list|)
expr_stmt|;
operator|*
name|y1
operator|=
operator|*
name|y2
operator|=
name|y
operator|+
literal|0.5
expr_stmt|;
break|break;
case|case
name|GIMP_ORIENTATION_VERTICAL
case|:
name|gimp_display_shell_transform_xy
argument_list|(
name|shell
argument_list|,
name|private
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
argument_list|)
expr_stmt|;
operator|*
name|x1
operator|=
operator|*
name|x2
operator|=
name|x
operator|+
literal|0.5
expr_stmt|;
break|break;
case|case
name|GIMP_ORIENTATION_UNKNOWN
case|:
return|return;
block|}
block|}
end_function

begin_function
specifier|static
name|void
DECL|function|gimp_canvas_guide_draw (GimpCanvasItem * item,GimpDisplayShell * shell,cairo_t * cr)
name|gimp_canvas_guide_draw
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
name|gimp_canvas_guide_transform
argument_list|(
name|item
argument_list|,
name|shell
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
name|cairo_move_to
argument_list|(
name|cr
argument_list|,
name|x1
argument_list|,
name|y1
argument_list|)
expr_stmt|;
name|cairo_line_to
argument_list|(
name|cr
argument_list|,
name|x2
argument_list|,
name|y2
argument_list|)
expr_stmt|;
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
name|GdkRegion
modifier|*
DECL|function|gimp_canvas_guide_get_extents (GimpCanvasItem * item,GimpDisplayShell * shell)
name|gimp_canvas_guide_get_extents
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
name|GdkRectangle
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
name|gimp_canvas_guide_transform
argument_list|(
name|item
argument_list|,
name|shell
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
name|rectangle
operator|.
name|x
operator|=
name|MIN
argument_list|(
name|x1
argument_list|,
name|x2
argument_list|)
operator|-
literal|1.5
expr_stmt|;
name|rectangle
operator|.
name|y
operator|=
name|MIN
argument_list|(
name|y1
argument_list|,
name|y2
argument_list|)
operator|-
literal|1.5
expr_stmt|;
name|rectangle
operator|.
name|width
operator|=
name|ABS
argument_list|(
name|x2
operator|-
name|x1
argument_list|)
operator|+
literal|3.0
expr_stmt|;
name|rectangle
operator|.
name|height
operator|=
name|ABS
argument_list|(
name|y2
operator|-
name|y1
argument_list|)
operator|+
literal|3.0
expr_stmt|;
return|return
name|gdk_region_rectangle
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
DECL|function|gimp_canvas_guide_stroke (GimpCanvasItem * item,GimpDisplayShell * shell,cairo_t * cr)
name|gimp_canvas_guide_stroke
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
name|GimpCanvasGuidePrivate
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
name|guide_style
condition|)
block|{
name|gimp_display_shell_set_guide_style
argument_list|(
name|shell
argument_list|,
name|cr
argument_list|,
name|gimp_canvas_item_get_highlight
argument_list|(
name|item
argument_list|)
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
DECL|function|gimp_canvas_guide_new (GimpDisplayShell * shell,GimpOrientationType orientation,gint position)
name|gimp_canvas_guide_new
parameter_list|(
name|GimpDisplayShell
modifier|*
name|shell
parameter_list|,
name|GimpOrientationType
name|orientation
parameter_list|,
name|gint
name|position
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
name|GIMP_TYPE_CANVAS_GUIDE
argument_list|,
literal|"shell"
argument_list|,
name|shell
argument_list|,
literal|"orientation"
argument_list|,
name|orientation
argument_list|,
literal|"position"
argument_list|,
name|position
argument_list|,
name|NULL
argument_list|)
return|;
block|}
end_function

end_unit

