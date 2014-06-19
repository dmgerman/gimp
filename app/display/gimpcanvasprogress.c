begin_unit|revision:0.9.5;language:C;cregit-version:0.0.1
begin_comment
comment|/* GIMP - The GNU Image Manipulation Program  * Copyright (C) 1995 Spencer Kimball and Peter Mattis  *  * gimpcanvasprogress.c  * Copyright (C) 2010 Michael Natterer<mitch@gimp.org>  *  * This program is free software: you can redistribute it and/or modify  * it under the terms of the GNU General Public License as published by  * the Free Software Foundation; either version 3 of the License, or  * (at your option) any later version.  *  * This program is distributed in the hope that it will be useful,  * but WITHOUT ANY WARRANTY; without even the implied warranty of  * MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the  * GNU General Public License for more details.  *  * You should have received a copy of the GNU General Public License  * along with this program.  If not, see<http://www.gnu.org/licenses/>.  */
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
file|"core/gimpprogress.h"
end_include

begin_include
include|#
directive|include
file|"gimpcanvas.h"
end_include

begin_include
include|#
directive|include
file|"gimpcanvas-style.h"
end_include

begin_include
include|#
directive|include
file|"gimpcanvasitem-utils.h"
end_include

begin_include
include|#
directive|include
file|"gimpcanvasprogress.h"
end_include

begin_include
include|#
directive|include
file|"gimpdisplayshell.h"
end_include

begin_define
DECL|macro|BORDER
define|#
directive|define
name|BORDER
value|5
end_define

begin_define
DECL|macro|RADIUS
define|#
directive|define
name|RADIUS
value|20
end_define

begin_enum
enum|enum
DECL|enum|__anon2c5f82070103
block|{
DECL|enumerator|PROP_0
name|PROP_0
block|,
DECL|enumerator|PROP_ANCHOR
name|PROP_ANCHOR
block|,
DECL|enumerator|PROP_X
name|PROP_X
block|,
DECL|enumerator|PROP_Y
name|PROP_Y
block|}
enum|;
end_enum

begin_typedef
DECL|typedef|GimpCanvasProgressPrivate
typedef|typedef
name|struct
name|_GimpCanvasProgressPrivate
name|GimpCanvasProgressPrivate
typedef|;
end_typedef

begin_struct
DECL|struct|_GimpCanvasProgressPrivate
struct|struct
name|_GimpCanvasProgressPrivate
block|{
DECL|member|anchor
name|GimpHandleAnchor
name|anchor
decl_stmt|;
DECL|member|x
name|gdouble
name|x
decl_stmt|;
DECL|member|y
name|gdouble
name|y
decl_stmt|;
DECL|member|text
name|gchar
modifier|*
name|text
decl_stmt|;
DECL|member|value
name|gdouble
name|value
decl_stmt|;
block|}
struct|;
end_struct

begin_define
DECL|macro|GET_PRIVATE (progress)
define|#
directive|define
name|GET_PRIVATE
parameter_list|(
name|progress
parameter_list|)
define|\
value|G_TYPE_INSTANCE_GET_PRIVATE (progress, \                                      GIMP_TYPE_CANVAS_PROGRESS, \                                      GimpCanvasProgressPrivate)
end_define

begin_comment
comment|/*  local function prototypes  */
end_comment

begin_function_decl
specifier|static
name|void
name|gimp_canvas_progress_iface_init
parameter_list|(
name|GimpProgressInterface
modifier|*
name|iface
parameter_list|)
function_decl|;
end_function_decl

begin_function_decl
specifier|static
name|void
name|gimp_canvas_progress_finalize
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
name|gimp_canvas_progress_set_property
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
name|gimp_canvas_progress_get_property
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
name|gimp_canvas_progress_draw
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
name|gimp_canvas_progress_get_extents
parameter_list|(
name|GimpCanvasItem
modifier|*
name|item
parameter_list|)
function_decl|;
end_function_decl

begin_function_decl
specifier|static
name|GimpProgress
modifier|*
name|gimp_canvas_progress_start
parameter_list|(
name|GimpProgress
modifier|*
name|progress
parameter_list|,
specifier|const
name|gchar
modifier|*
name|message
parameter_list|,
name|gboolean
name|cancelable
parameter_list|)
function_decl|;
end_function_decl

begin_function_decl
specifier|static
name|void
name|gimp_canvas_progress_end
parameter_list|(
name|GimpProgress
modifier|*
name|progress
parameter_list|)
function_decl|;
end_function_decl

begin_function_decl
specifier|static
name|gboolean
name|gimp_canvas_progress_is_active
parameter_list|(
name|GimpProgress
modifier|*
name|progress
parameter_list|)
function_decl|;
end_function_decl

begin_function_decl
specifier|static
name|void
name|gimp_canvas_progress_set_text
parameter_list|(
name|GimpProgress
modifier|*
name|progress
parameter_list|,
specifier|const
name|gchar
modifier|*
name|message
parameter_list|)
function_decl|;
end_function_decl

begin_function_decl
specifier|static
name|void
name|gimp_canvas_progress_set_value
parameter_list|(
name|GimpProgress
modifier|*
name|progress
parameter_list|,
name|gdouble
name|percentage
parameter_list|)
function_decl|;
end_function_decl

begin_function_decl
specifier|static
name|gdouble
name|gimp_canvas_progress_get_value
parameter_list|(
name|GimpProgress
modifier|*
name|progress
parameter_list|)
function_decl|;
end_function_decl

begin_function_decl
specifier|static
name|void
name|gimp_canvas_progress_pulse
parameter_list|(
name|GimpProgress
modifier|*
name|progress
parameter_list|)
function_decl|;
end_function_decl

begin_function_decl
specifier|static
name|gboolean
name|gimp_canvas_progress_message
parameter_list|(
name|GimpProgress
modifier|*
name|progress
parameter_list|,
name|Gimp
modifier|*
name|gimp
parameter_list|,
name|GimpMessageSeverity
name|severity
parameter_list|,
specifier|const
name|gchar
modifier|*
name|domain
parameter_list|,
specifier|const
name|gchar
modifier|*
name|message
parameter_list|)
function_decl|;
end_function_decl

begin_macro
DECL|function|G_DEFINE_TYPE_WITH_CODE (GimpCanvasProgress,gimp_canvas_progress,GIMP_TYPE_CANVAS_ITEM,G_IMPLEMENT_INTERFACE (GIMP_TYPE_PROGRESS,gimp_canvas_progress_iface_init))
name|G_DEFINE_TYPE_WITH_CODE
argument_list|(
argument|GimpCanvasProgress
argument_list|,
argument|gimp_canvas_progress
argument_list|,
argument|GIMP_TYPE_CANVAS_ITEM
argument_list|,
argument|G_IMPLEMENT_INTERFACE (GIMP_TYPE_PROGRESS,                                                 gimp_canvas_progress_iface_init)
argument_list|)
end_macro

begin_define
DECL|macro|parent_class
define|#
directive|define
name|parent_class
value|gimp_canvas_progress_parent_class
end_define

begin_function
specifier|static
name|void
name|gimp_canvas_progress_class_init
parameter_list|(
name|GimpCanvasProgressClass
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
name|gimp_canvas_progress_finalize
expr_stmt|;
name|object_class
operator|->
name|set_property
operator|=
name|gimp_canvas_progress_set_property
expr_stmt|;
name|object_class
operator|->
name|get_property
operator|=
name|gimp_canvas_progress_get_property
expr_stmt|;
name|item_class
operator|->
name|draw
operator|=
name|gimp_canvas_progress_draw
expr_stmt|;
name|item_class
operator|->
name|get_extents
operator|=
name|gimp_canvas_progress_get_extents
expr_stmt|;
name|g_object_class_install_property
argument_list|(
name|object_class
argument_list|,
name|PROP_ANCHOR
argument_list|,
name|g_param_spec_enum
argument_list|(
literal|"anchor"
argument_list|,
name|NULL
argument_list|,
name|NULL
argument_list|,
name|GIMP_TYPE_HANDLE_ANCHOR
argument_list|,
name|GIMP_HANDLE_ANCHOR_CENTER
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
name|g_type_class_add_private
argument_list|(
name|klass
argument_list|,
sizeof|sizeof
argument_list|(
name|GimpCanvasProgressPrivate
argument_list|)
argument_list|)
expr_stmt|;
block|}
end_function

begin_function
specifier|static
name|void
DECL|function|gimp_canvas_progress_iface_init (GimpProgressInterface * iface)
name|gimp_canvas_progress_iface_init
parameter_list|(
name|GimpProgressInterface
modifier|*
name|iface
parameter_list|)
block|{
name|iface
operator|->
name|start
operator|=
name|gimp_canvas_progress_start
expr_stmt|;
name|iface
operator|->
name|end
operator|=
name|gimp_canvas_progress_end
expr_stmt|;
name|iface
operator|->
name|is_active
operator|=
name|gimp_canvas_progress_is_active
expr_stmt|;
name|iface
operator|->
name|set_text
operator|=
name|gimp_canvas_progress_set_text
expr_stmt|;
name|iface
operator|->
name|set_value
operator|=
name|gimp_canvas_progress_set_value
expr_stmt|;
name|iface
operator|->
name|get_value
operator|=
name|gimp_canvas_progress_get_value
expr_stmt|;
name|iface
operator|->
name|pulse
operator|=
name|gimp_canvas_progress_pulse
expr_stmt|;
name|iface
operator|->
name|message
operator|=
name|gimp_canvas_progress_message
expr_stmt|;
block|}
end_function

begin_function
specifier|static
name|void
DECL|function|gimp_canvas_progress_init (GimpCanvasProgress * progress)
name|gimp_canvas_progress_init
parameter_list|(
name|GimpCanvasProgress
modifier|*
name|progress
parameter_list|)
block|{ }
end_function

begin_function
specifier|static
name|void
DECL|function|gimp_canvas_progress_finalize (GObject * object)
name|gimp_canvas_progress_finalize
parameter_list|(
name|GObject
modifier|*
name|object
parameter_list|)
block|{
name|GimpCanvasProgressPrivate
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
name|text
condition|)
block|{
name|g_free
argument_list|(
name|private
operator|->
name|text
argument_list|)
expr_stmt|;
name|private
operator|->
name|text
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
DECL|function|gimp_canvas_progress_set_property (GObject * object,guint property_id,const GValue * value,GParamSpec * pspec)
name|gimp_canvas_progress_set_property
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
name|GimpCanvasProgressPrivate
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
name|PROP_ANCHOR
case|:
name|private
operator|->
name|anchor
operator|=
name|g_value_get_enum
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
DECL|function|gimp_canvas_progress_get_property (GObject * object,guint property_id,GValue * value,GParamSpec * pspec)
name|gimp_canvas_progress_get_property
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
name|GimpCanvasProgressPrivate
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
name|PROP_ANCHOR
case|:
name|g_value_set_enum
argument_list|(
name|value
argument_list|,
name|private
operator|->
name|anchor
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
name|PangoLayout
modifier|*
DECL|function|gimp_canvas_progress_transform (GimpCanvasItem * item,gdouble * x,gdouble * y,gint * width,gint * height)
name|gimp_canvas_progress_transform
parameter_list|(
name|GimpCanvasItem
modifier|*
name|item
parameter_list|,
name|gdouble
modifier|*
name|x
parameter_list|,
name|gdouble
modifier|*
name|y
parameter_list|,
name|gint
modifier|*
name|width
parameter_list|,
name|gint
modifier|*
name|height
parameter_list|)
block|{
name|GimpCanvasProgressPrivate
modifier|*
name|private
init|=
name|GET_PRIVATE
argument_list|(
name|item
argument_list|)
decl_stmt|;
name|GtkWidget
modifier|*
name|canvas
init|=
name|gimp_canvas_item_get_canvas
argument_list|(
name|item
argument_list|)
decl_stmt|;
name|PangoLayout
modifier|*
name|layout
decl_stmt|;
name|layout
operator|=
name|gimp_canvas_get_layout
argument_list|(
name|GIMP_CANVAS
argument_list|(
name|canvas
argument_list|)
argument_list|,
literal|"%s"
argument_list|,
name|private
operator|->
name|text
argument_list|)
expr_stmt|;
name|pango_layout_get_pixel_size
argument_list|(
name|layout
argument_list|,
name|width
argument_list|,
name|height
argument_list|)
expr_stmt|;
operator|*
name|width
operator|=
name|MAX
argument_list|(
operator|*
name|width
argument_list|,
literal|2
operator|*
name|RADIUS
argument_list|)
expr_stmt|;
operator|*
name|width
operator|+=
literal|2
operator|*
name|BORDER
expr_stmt|;
operator|*
name|height
operator|+=
literal|3
operator|*
name|BORDER
operator|+
literal|2
operator|*
name|RADIUS
expr_stmt|;
name|gimp_canvas_item_transform_xy_f
argument_list|(
name|item
argument_list|,
name|private
operator|->
name|x
argument_list|,
name|private
operator|->
name|y
argument_list|,
name|x
argument_list|,
name|y
argument_list|)
expr_stmt|;
name|gimp_canvas_item_shift_to_north_west
argument_list|(
name|private
operator|->
name|anchor
argument_list|,
operator|*
name|x
argument_list|,
operator|*
name|y
argument_list|,
operator|*
name|width
argument_list|,
operator|*
name|height
argument_list|,
name|x
argument_list|,
name|y
argument_list|)
expr_stmt|;
operator|*
name|x
operator|=
name|floor
argument_list|(
operator|*
name|x
argument_list|)
expr_stmt|;
operator|*
name|y
operator|=
name|floor
argument_list|(
operator|*
name|y
argument_list|)
expr_stmt|;
return|return
name|layout
return|;
block|}
end_function

begin_function
specifier|static
name|void
DECL|function|gimp_canvas_progress_draw (GimpCanvasItem * item,cairo_t * cr)
name|gimp_canvas_progress_draw
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
name|GimpCanvasProgressPrivate
modifier|*
name|private
init|=
name|GET_PRIVATE
argument_list|(
name|item
argument_list|)
decl_stmt|;
name|GtkWidget
modifier|*
name|canvas
init|=
name|gimp_canvas_item_get_canvas
argument_list|(
name|item
argument_list|)
decl_stmt|;
name|gdouble
name|x
decl_stmt|,
name|y
decl_stmt|;
name|gint
name|width
decl_stmt|,
name|height
decl_stmt|;
name|gimp_canvas_progress_transform
argument_list|(
name|item
argument_list|,
operator|&
name|x
argument_list|,
operator|&
name|y
argument_list|,
operator|&
name|width
argument_list|,
operator|&
name|height
argument_list|)
expr_stmt|;
name|cairo_move_to
argument_list|(
name|cr
argument_list|,
name|x
argument_list|,
name|y
argument_list|)
expr_stmt|;
name|cairo_line_to
argument_list|(
name|cr
argument_list|,
name|x
operator|+
name|width
argument_list|,
name|y
argument_list|)
expr_stmt|;
name|cairo_line_to
argument_list|(
name|cr
argument_list|,
name|x
operator|+
name|width
argument_list|,
name|y
operator|+
name|height
operator|-
name|BORDER
operator|-
literal|2
operator|*
name|RADIUS
argument_list|)
expr_stmt|;
name|cairo_line_to
argument_list|(
name|cr
argument_list|,
name|x
operator|+
literal|2
operator|*
name|BORDER
operator|+
literal|2
operator|*
name|RADIUS
argument_list|,
name|y
operator|+
name|height
operator|-
name|BORDER
operator|-
literal|2
operator|*
name|RADIUS
argument_list|)
expr_stmt|;
name|cairo_arc
argument_list|(
name|cr
argument_list|,
name|x
operator|+
name|BORDER
operator|+
name|RADIUS
argument_list|,
name|y
operator|+
name|height
operator|-
name|BORDER
operator|-
name|RADIUS
argument_list|,
name|BORDER
operator|+
name|RADIUS
argument_list|,
literal|0
argument_list|,
name|G_PI
argument_list|)
expr_stmt|;
name|cairo_close_path
argument_list|(
name|cr
argument_list|)
expr_stmt|;
name|_gimp_canvas_item_fill
argument_list|(
name|item
argument_list|,
name|cr
argument_list|)
expr_stmt|;
name|cairo_move_to
argument_list|(
name|cr
argument_list|,
name|x
operator|+
name|BORDER
argument_list|,
name|y
operator|+
name|BORDER
argument_list|)
expr_stmt|;
name|cairo_set_source_rgba
argument_list|(
name|cr
argument_list|,
literal|0.0
argument_list|,
literal|0.0
argument_list|,
literal|0.0
argument_list|,
literal|1.0
argument_list|)
expr_stmt|;
name|pango_cairo_show_layout
argument_list|(
name|cr
argument_list|,
name|gimp_canvas_get_layout
argument_list|(
name|GIMP_CANVAS
argument_list|(
name|canvas
argument_list|)
argument_list|,
literal|"%s"
argument_list|,
name|private
operator|->
name|text
argument_list|)
argument_list|)
expr_stmt|;
name|gimp_canvas_set_tool_bg_style
argument_list|(
name|gimp_canvas_item_get_canvas
argument_list|(
name|item
argument_list|)
argument_list|,
name|cr
argument_list|)
expr_stmt|;
name|cairo_arc
argument_list|(
name|cr
argument_list|,
name|x
operator|+
name|BORDER
operator|+
name|RADIUS
argument_list|,
name|y
operator|+
name|height
operator|-
name|BORDER
operator|-
name|RADIUS
argument_list|,
name|RADIUS
argument_list|,
operator|-
name|G_PI
operator|/
literal|2.0
argument_list|,
literal|2
operator|*
name|G_PI
operator|-
name|G_PI
operator|/
literal|2.0
argument_list|)
expr_stmt|;
name|cairo_fill
argument_list|(
name|cr
argument_list|)
expr_stmt|;
name|cairo_set_source_rgba
argument_list|(
name|cr
argument_list|,
literal|0.0
argument_list|,
literal|1.0
argument_list|,
literal|0.0
argument_list|,
literal|1.0
argument_list|)
expr_stmt|;
name|cairo_move_to
argument_list|(
name|cr
argument_list|,
name|x
operator|+
name|BORDER
operator|+
name|RADIUS
argument_list|,
name|y
operator|+
name|height
operator|-
name|BORDER
operator|-
name|RADIUS
argument_list|)
expr_stmt|;
name|cairo_arc
argument_list|(
name|cr
argument_list|,
name|x
operator|+
name|BORDER
operator|+
name|RADIUS
argument_list|,
name|y
operator|+
name|height
operator|-
name|BORDER
operator|-
name|RADIUS
argument_list|,
name|RADIUS
argument_list|,
operator|-
name|G_PI
operator|/
literal|2.0
argument_list|,
literal|2
operator|*
name|G_PI
operator|*
name|private
operator|->
name|value
operator|-
name|G_PI
operator|/
literal|2.0
argument_list|)
expr_stmt|;
name|cairo_fill
argument_list|(
name|cr
argument_list|)
expr_stmt|;
block|}
end_function

begin_function
specifier|static
name|cairo_region_t
modifier|*
DECL|function|gimp_canvas_progress_get_extents (GimpCanvasItem * item)
name|gimp_canvas_progress_get_extents
parameter_list|(
name|GimpCanvasItem
modifier|*
name|item
parameter_list|)
block|{
name|cairo_rectangle_int_t
name|rectangle
decl_stmt|;
name|gdouble
name|x
decl_stmt|,
name|y
decl_stmt|;
name|gint
name|width
decl_stmt|,
name|height
decl_stmt|;
name|gimp_canvas_progress_transform
argument_list|(
name|item
argument_list|,
operator|&
name|x
argument_list|,
operator|&
name|y
argument_list|,
operator|&
name|width
argument_list|,
operator|&
name|height
argument_list|)
expr_stmt|;
comment|/*  add 1px on each side because fill()'s default impl does the same  */
name|rectangle
operator|.
name|x
operator|=
operator|(
name|gint
operator|)
name|x
operator|-
literal|1
expr_stmt|;
name|rectangle
operator|.
name|y
operator|=
operator|(
name|gint
operator|)
name|y
operator|-
literal|1
expr_stmt|;
name|rectangle
operator|.
name|width
operator|=
name|width
operator|+
literal|2
expr_stmt|;
name|rectangle
operator|.
name|height
operator|=
name|height
operator|+
literal|2
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
name|GimpProgress
modifier|*
DECL|function|gimp_canvas_progress_start (GimpProgress * progress,const gchar * message,gboolean cancelable)
name|gimp_canvas_progress_start
parameter_list|(
name|GimpProgress
modifier|*
name|progress
parameter_list|,
specifier|const
name|gchar
modifier|*
name|message
parameter_list|,
name|gboolean
name|cancelable
parameter_list|)
block|{
name|gimp_canvas_progress_set_text
argument_list|(
name|progress
argument_list|,
name|message
argument_list|)
expr_stmt|;
return|return
name|progress
return|;
block|}
end_function

begin_function
specifier|static
name|void
DECL|function|gimp_canvas_progress_end (GimpProgress * progress)
name|gimp_canvas_progress_end
parameter_list|(
name|GimpProgress
modifier|*
name|progress
parameter_list|)
block|{ }
end_function

begin_function
specifier|static
name|gboolean
DECL|function|gimp_canvas_progress_is_active (GimpProgress * progress)
name|gimp_canvas_progress_is_active
parameter_list|(
name|GimpProgress
modifier|*
name|progress
parameter_list|)
block|{
return|return
name|TRUE
return|;
block|}
end_function

begin_function
specifier|static
name|void
DECL|function|gimp_canvas_progress_set_text (GimpProgress * progress,const gchar * message)
name|gimp_canvas_progress_set_text
parameter_list|(
name|GimpProgress
modifier|*
name|progress
parameter_list|,
specifier|const
name|gchar
modifier|*
name|message
parameter_list|)
block|{
name|GimpCanvasProgressPrivate
modifier|*
name|private
init|=
name|GET_PRIVATE
argument_list|(
name|progress
argument_list|)
decl_stmt|;
name|cairo_region_t
modifier|*
name|old_region
decl_stmt|;
name|cairo_region_t
modifier|*
name|new_region
decl_stmt|;
name|old_region
operator|=
name|gimp_canvas_item_get_extents
argument_list|(
name|GIMP_CANVAS_ITEM
argument_list|(
name|progress
argument_list|)
argument_list|)
expr_stmt|;
if|if
condition|(
name|private
operator|->
name|text
condition|)
name|g_free
argument_list|(
name|private
operator|->
name|text
argument_list|)
expr_stmt|;
name|private
operator|->
name|text
operator|=
name|g_strdup
argument_list|(
name|message
argument_list|)
expr_stmt|;
name|new_region
operator|=
name|gimp_canvas_item_get_extents
argument_list|(
name|GIMP_CANVAS_ITEM
argument_list|(
name|progress
argument_list|)
argument_list|)
expr_stmt|;
name|cairo_region_union
argument_list|(
name|new_region
argument_list|,
name|old_region
argument_list|)
expr_stmt|;
name|cairo_region_destroy
argument_list|(
name|old_region
argument_list|)
expr_stmt|;
name|_gimp_canvas_item_update
argument_list|(
name|GIMP_CANVAS_ITEM
argument_list|(
name|progress
argument_list|)
argument_list|,
name|new_region
argument_list|)
expr_stmt|;
name|cairo_region_destroy
argument_list|(
name|new_region
argument_list|)
expr_stmt|;
block|}
end_function

begin_function
specifier|static
name|void
DECL|function|gimp_canvas_progress_set_value (GimpProgress * progress,gdouble percentage)
name|gimp_canvas_progress_set_value
parameter_list|(
name|GimpProgress
modifier|*
name|progress
parameter_list|,
name|gdouble
name|percentage
parameter_list|)
block|{
name|GimpCanvasProgressPrivate
modifier|*
name|private
init|=
name|GET_PRIVATE
argument_list|(
name|progress
argument_list|)
decl_stmt|;
if|if
condition|(
name|percentage
operator|!=
name|private
operator|->
name|value
condition|)
block|{
name|cairo_region_t
modifier|*
name|region
decl_stmt|;
name|private
operator|->
name|value
operator|=
name|percentage
expr_stmt|;
name|region
operator|=
name|gimp_canvas_item_get_extents
argument_list|(
name|GIMP_CANVAS_ITEM
argument_list|(
name|progress
argument_list|)
argument_list|)
expr_stmt|;
name|_gimp_canvas_item_update
argument_list|(
name|GIMP_CANVAS_ITEM
argument_list|(
name|progress
argument_list|)
argument_list|,
name|region
argument_list|)
expr_stmt|;
name|cairo_region_destroy
argument_list|(
name|region
argument_list|)
expr_stmt|;
block|}
block|}
end_function

begin_function
specifier|static
name|gdouble
DECL|function|gimp_canvas_progress_get_value (GimpProgress * progress)
name|gimp_canvas_progress_get_value
parameter_list|(
name|GimpProgress
modifier|*
name|progress
parameter_list|)
block|{
name|GimpCanvasProgressPrivate
modifier|*
name|private
init|=
name|GET_PRIVATE
argument_list|(
name|progress
argument_list|)
decl_stmt|;
return|return
name|private
operator|->
name|value
return|;
block|}
end_function

begin_function
specifier|static
name|void
DECL|function|gimp_canvas_progress_pulse (GimpProgress * progress)
name|gimp_canvas_progress_pulse
parameter_list|(
name|GimpProgress
modifier|*
name|progress
parameter_list|)
block|{ }
end_function

begin_function
specifier|static
name|gboolean
DECL|function|gimp_canvas_progress_message (GimpProgress * progress,Gimp * gimp,GimpMessageSeverity severity,const gchar * domain,const gchar * message)
name|gimp_canvas_progress_message
parameter_list|(
name|GimpProgress
modifier|*
name|progress
parameter_list|,
name|Gimp
modifier|*
name|gimp
parameter_list|,
name|GimpMessageSeverity
name|severity
parameter_list|,
specifier|const
name|gchar
modifier|*
name|domain
parameter_list|,
specifier|const
name|gchar
modifier|*
name|message
parameter_list|)
block|{
return|return
name|FALSE
return|;
block|}
end_function

begin_function
name|GimpCanvasItem
modifier|*
DECL|function|gimp_canvas_progress_new (GimpDisplayShell * shell,GimpHandleAnchor anchor,gdouble x,gdouble y)
name|gimp_canvas_progress_new
parameter_list|(
name|GimpDisplayShell
modifier|*
name|shell
parameter_list|,
name|GimpHandleAnchor
name|anchor
parameter_list|,
name|gdouble
name|x
parameter_list|,
name|gdouble
name|y
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
name|GIMP_TYPE_CANVAS_PROGRESS
argument_list|,
literal|"shell"
argument_list|,
name|shell
argument_list|,
literal|"anchor"
argument_list|,
name|anchor
argument_list|,
literal|"x"
argument_list|,
name|x
argument_list|,
literal|"y"
argument_list|,
name|y
argument_list|,
name|NULL
argument_list|)
return|;
block|}
end_function

end_unit

