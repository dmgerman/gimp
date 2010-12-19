begin_unit|revision:0.9.5;language:C;cregit-version:0.0.1
begin_comment
comment|/* GIMP - The GNU Image Manipulation Program  * Copyright (C) 1995 Spencer Kimball and Peter Mattis  *  * This program is free software: you can redistribute it and/or modify  * it under the terms of the GNU General Public License as published by  * the Free Software Foundation; either version 3 of the License, or  * (at your option) any later version.  *  * This program is distributed in the hope that it will be useful,  * but WITHOUT ANY WARRANTY; without even the implied warranty of  * MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the  * GNU General Public License for more details.  *  * You should have received a copy of the GNU General Public License  * along with this program.  If not, see<http://www.gnu.org/licenses/>.  */
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
file|"config/gimpdisplayconfig.h"
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
file|"gimp-intl.h"
end_include

begin_define
DECL|macro|MAX_BATCH_SIZE
define|#
directive|define
name|MAX_BATCH_SIZE
value|32000
end_define

begin_enum
enum|enum
DECL|enum|__anon2b444c140103
block|{
DECL|enumerator|PROP_0
name|PROP_0
block|,
DECL|enumerator|PROP_CONFIG
name|PROP_CONFIG
block|}
enum|;
end_enum

begin_comment
comment|/*  local function prototypes  */
end_comment

begin_function_decl
specifier|static
name|void
name|gimp_canvas_set_property
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
name|gimp_canvas_get_property
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
name|gimp_canvas_unrealize
parameter_list|(
name|GtkWidget
modifier|*
name|widget
parameter_list|)
function_decl|;
end_function_decl

begin_function_decl
specifier|static
name|void
name|gimp_canvas_style_set
parameter_list|(
name|GtkWidget
modifier|*
name|widget
parameter_list|,
name|GtkStyle
modifier|*
name|prev_style
parameter_list|)
function_decl|;
end_function_decl

begin_function_decl
specifier|static
name|gboolean
name|gimp_canvas_focus_in_event
parameter_list|(
name|GtkWidget
modifier|*
name|widget
parameter_list|,
name|GdkEventFocus
modifier|*
name|event
parameter_list|)
function_decl|;
end_function_decl

begin_function_decl
specifier|static
name|gboolean
name|gimp_canvas_focus_out_event
parameter_list|(
name|GtkWidget
modifier|*
name|widget
parameter_list|,
name|GdkEventFocus
modifier|*
name|event
parameter_list|)
function_decl|;
end_function_decl

begin_function_decl
specifier|static
name|gboolean
name|gimp_canvas_focus
parameter_list|(
name|GtkWidget
modifier|*
name|widget
parameter_list|,
name|GtkDirectionType
name|direction
parameter_list|)
function_decl|;
end_function_decl

begin_macro
DECL|function|G_DEFINE_TYPE (GimpCanvas,gimp_canvas,GIMP_TYPE_OVERLAY_BOX)
name|G_DEFINE_TYPE
argument_list|(
argument|GimpCanvas
argument_list|,
argument|gimp_canvas
argument_list|,
argument|GIMP_TYPE_OVERLAY_BOX
argument_list|)
end_macro

begin_define
DECL|macro|parent_class
define|#
directive|define
name|parent_class
value|gimp_canvas_parent_class
end_define

begin_function
specifier|static
name|void
name|gimp_canvas_class_init
parameter_list|(
name|GimpCanvasClass
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
name|GtkWidgetClass
modifier|*
name|widget_class
init|=
name|GTK_WIDGET_CLASS
argument_list|(
name|klass
argument_list|)
decl_stmt|;
name|object_class
operator|->
name|set_property
operator|=
name|gimp_canvas_set_property
expr_stmt|;
name|object_class
operator|->
name|get_property
operator|=
name|gimp_canvas_get_property
expr_stmt|;
name|widget_class
operator|->
name|unrealize
operator|=
name|gimp_canvas_unrealize
expr_stmt|;
name|widget_class
operator|->
name|style_set
operator|=
name|gimp_canvas_style_set
expr_stmt|;
name|widget_class
operator|->
name|focus_in_event
operator|=
name|gimp_canvas_focus_in_event
expr_stmt|;
name|widget_class
operator|->
name|focus_out_event
operator|=
name|gimp_canvas_focus_out_event
expr_stmt|;
name|widget_class
operator|->
name|focus
operator|=
name|gimp_canvas_focus
expr_stmt|;
name|g_object_class_install_property
argument_list|(
name|object_class
argument_list|,
name|PROP_CONFIG
argument_list|,
name|g_param_spec_object
argument_list|(
literal|"config"
argument_list|,
name|NULL
argument_list|,
name|NULL
argument_list|,
name|GIMP_TYPE_DISPLAY_CONFIG
argument_list|,
name|GIMP_PARAM_READWRITE
operator||
name|G_PARAM_CONSTRUCT_ONLY
argument_list|)
argument_list|)
expr_stmt|;
block|}
end_function

begin_function
specifier|static
name|void
DECL|function|gimp_canvas_init (GimpCanvas * canvas)
name|gimp_canvas_init
parameter_list|(
name|GimpCanvas
modifier|*
name|canvas
parameter_list|)
block|{
name|GtkWidget
modifier|*
name|widget
init|=
name|GTK_WIDGET
argument_list|(
name|canvas
argument_list|)
decl_stmt|;
name|gtk_widget_set_can_focus
argument_list|(
name|widget
argument_list|,
name|TRUE
argument_list|)
expr_stmt|;
name|gtk_widget_add_events
argument_list|(
name|widget
argument_list|,
name|GIMP_CANVAS_EVENT_MASK
argument_list|)
expr_stmt|;
block|}
end_function

begin_function
specifier|static
name|void
DECL|function|gimp_canvas_set_property (GObject * object,guint property_id,const GValue * value,GParamSpec * pspec)
name|gimp_canvas_set_property
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
name|GimpCanvas
modifier|*
name|canvas
init|=
name|GIMP_CANVAS
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
name|PROP_CONFIG
case|:
name|canvas
operator|->
name|config
operator|=
name|g_value_get_object
argument_list|(
name|value
argument_list|)
expr_stmt|;
comment|/* don't dup */
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
DECL|function|gimp_canvas_get_property (GObject * object,guint property_id,GValue * value,GParamSpec * pspec)
name|gimp_canvas_get_property
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
name|GimpCanvas
modifier|*
name|canvas
init|=
name|GIMP_CANVAS
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
name|PROP_CONFIG
case|:
name|g_value_set_object
argument_list|(
name|value
argument_list|,
name|canvas
operator|->
name|config
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
DECL|function|gimp_canvas_unrealize (GtkWidget * widget)
name|gimp_canvas_unrealize
parameter_list|(
name|GtkWidget
modifier|*
name|widget
parameter_list|)
block|{
name|GimpCanvas
modifier|*
name|canvas
init|=
name|GIMP_CANVAS
argument_list|(
name|widget
argument_list|)
decl_stmt|;
name|g_clear_object
argument_list|(
operator|&
name|canvas
operator|->
name|layout
argument_list|)
expr_stmt|;
name|GTK_WIDGET_CLASS
argument_list|(
name|parent_class
argument_list|)
operator|->
name|unrealize
argument_list|(
name|widget
argument_list|)
expr_stmt|;
block|}
end_function

begin_function
specifier|static
name|void
DECL|function|gimp_canvas_style_set (GtkWidget * widget,GtkStyle * prev_style)
name|gimp_canvas_style_set
parameter_list|(
name|GtkWidget
modifier|*
name|widget
parameter_list|,
name|GtkStyle
modifier|*
name|prev_style
parameter_list|)
block|{
name|GimpCanvas
modifier|*
name|canvas
init|=
name|GIMP_CANVAS
argument_list|(
name|widget
argument_list|)
decl_stmt|;
name|GTK_WIDGET_CLASS
argument_list|(
name|parent_class
argument_list|)
operator|->
name|style_set
argument_list|(
name|widget
argument_list|,
name|prev_style
argument_list|)
expr_stmt|;
name|g_clear_object
argument_list|(
operator|&
name|canvas
operator|->
name|layout
argument_list|)
expr_stmt|;
block|}
end_function

begin_function
specifier|static
name|gboolean
DECL|function|gimp_canvas_focus_in_event (GtkWidget * widget,GdkEventFocus * event)
name|gimp_canvas_focus_in_event
parameter_list|(
name|GtkWidget
modifier|*
name|widget
parameter_list|,
name|GdkEventFocus
modifier|*
name|event
parameter_list|)
block|{
comment|/*  don't allow the default impl to invalidate the whole widget,    *  we don't draw a focus indicator anyway.    */
return|return
name|FALSE
return|;
block|}
end_function

begin_function
specifier|static
name|gboolean
DECL|function|gimp_canvas_focus_out_event (GtkWidget * widget,GdkEventFocus * event)
name|gimp_canvas_focus_out_event
parameter_list|(
name|GtkWidget
modifier|*
name|widget
parameter_list|,
name|GdkEventFocus
modifier|*
name|event
parameter_list|)
block|{
comment|/*  see focus-in-event    */
return|return
name|FALSE
return|;
block|}
end_function

begin_function
specifier|static
name|gboolean
DECL|function|gimp_canvas_focus (GtkWidget * widget,GtkDirectionType direction)
name|gimp_canvas_focus
parameter_list|(
name|GtkWidget
modifier|*
name|widget
parameter_list|,
name|GtkDirectionType
name|direction
parameter_list|)
block|{
name|GtkWidget
modifier|*
name|focus
init|=
name|gtk_container_get_focus_child
argument_list|(
name|GTK_CONTAINER
argument_list|(
name|widget
argument_list|)
argument_list|)
decl_stmt|;
comment|/* override GtkContainer's focus() implementation which would always    * give focus to the canvas because it is focussable. Instead, try    * navigating in the focused overlay child first, and use    * GtkContainer's default implementation only if that fails (which    * happens when focus navigation leaves the overlay child).    */
if|if
condition|(
name|focus
operator|&&
name|gtk_widget_child_focus
argument_list|(
name|focus
argument_list|,
name|direction
argument_list|)
condition|)
return|return
name|TRUE
return|;
return|return
name|GTK_WIDGET_CLASS
argument_list|(
name|parent_class
argument_list|)
operator|->
name|focus
argument_list|(
name|widget
argument_list|,
name|direction
argument_list|)
return|;
block|}
end_function

begin_comment
comment|/*  public functions  */
end_comment

begin_comment
comment|/**  * gimp_canvas_new:  *  * Creates a new #GimpCanvas widget.  *  * The #GimpCanvas widget is a #GtkDrawingArea abstraction. It manages  * a set of graphic contexts for drawing on a GIMP display. If you  * draw using a #GimpCanvasStyle, #GimpCanvas makes sure that the  * associated #GdkGC is created. All drawing on the canvas needs to  * happen by means of the #GimpCanvas drawing functions. Besides from  * not needing a #GdkGC pointer, the #GimpCanvas drawing functions  * look and work like their #GdkDrawable counterparts. #GimpCanvas  * gracefully handles attempts to draw on the unrealized widget.  *  * Return value: a new #GimpCanvas widget  **/
end_comment

begin_function
name|GtkWidget
modifier|*
DECL|function|gimp_canvas_new (GimpDisplayConfig * config)
name|gimp_canvas_new
parameter_list|(
name|GimpDisplayConfig
modifier|*
name|config
parameter_list|)
block|{
name|g_return_val_if_fail
argument_list|(
name|GIMP_IS_DISPLAY_CONFIG
argument_list|(
name|config
argument_list|)
argument_list|,
name|NULL
argument_list|)
expr_stmt|;
return|return
name|g_object_new
argument_list|(
name|GIMP_TYPE_CANVAS
argument_list|,
literal|"name"
argument_list|,
literal|"gimp-canvas"
argument_list|,
literal|"config"
argument_list|,
name|config
argument_list|,
name|NULL
argument_list|)
return|;
block|}
end_function

begin_comment
comment|/**  * gimp_canvas_get_layout:  * @canvas:  a #GimpCanvas widget  * @format:  a standard printf() format string.  * @Varargs: the parameters to insert into the format string.  *  * Returns a layout which can be used for  * pango_cairo_show_layout(). The layout belongs to the canvas and  * should not be freed, not should a pointer to it be kept around  * after drawing.  *  * Returns: a #PangoLayout owned by the canvas.  **/
end_comment

begin_function
name|PangoLayout
modifier|*
DECL|function|gimp_canvas_get_layout (GimpCanvas * canvas,const gchar * format,...)
name|gimp_canvas_get_layout
parameter_list|(
name|GimpCanvas
modifier|*
name|canvas
parameter_list|,
specifier|const
name|gchar
modifier|*
name|format
parameter_list|,
modifier|...
parameter_list|)
block|{
name|va_list
name|args
decl_stmt|;
name|gchar
modifier|*
name|text
decl_stmt|;
if|if
condition|(
operator|!
name|canvas
operator|->
name|layout
condition|)
name|canvas
operator|->
name|layout
operator|=
name|gtk_widget_create_pango_layout
argument_list|(
name|GTK_WIDGET
argument_list|(
name|canvas
argument_list|)
argument_list|,
name|NULL
argument_list|)
expr_stmt|;
name|va_start
argument_list|(
name|args
argument_list|,
name|format
argument_list|)
expr_stmt|;
name|text
operator|=
name|g_strdup_vprintf
argument_list|(
name|format
argument_list|,
name|args
argument_list|)
expr_stmt|;
name|va_end
argument_list|(
name|args
argument_list|)
expr_stmt|;
name|pango_layout_set_text
argument_list|(
name|canvas
operator|->
name|layout
argument_list|,
name|text
argument_list|,
operator|-
literal|1
argument_list|)
expr_stmt|;
name|g_free
argument_list|(
name|text
argument_list|)
expr_stmt|;
return|return
name|canvas
operator|->
name|layout
return|;
block|}
end_function

begin_comment
comment|/**  * gimp_canvas_set_bg_color:  * @canvas:   a #GimpCanvas widget  * @color:    a color in #GimpRGB format  *  * Sets the background color of the canvas's window.  This  * is the color the canvas is set to if it is cleared.  **/
end_comment

begin_function
name|void
DECL|function|gimp_canvas_set_bg_color (GimpCanvas * canvas,GimpRGB * color)
name|gimp_canvas_set_bg_color
parameter_list|(
name|GimpCanvas
modifier|*
name|canvas
parameter_list|,
name|GimpRGB
modifier|*
name|color
parameter_list|)
block|{
name|GtkWidget
modifier|*
name|widget
init|=
name|GTK_WIDGET
argument_list|(
name|canvas
argument_list|)
decl_stmt|;
name|GdkColor
name|gdk_color
decl_stmt|;
if|if
condition|(
operator|!
name|gtk_widget_get_realized
argument_list|(
name|widget
argument_list|)
condition|)
return|return;
name|gimp_rgb_get_gdk_color
argument_list|(
name|color
argument_list|,
operator|&
name|gdk_color
argument_list|)
expr_stmt|;
name|gdk_window_set_background
argument_list|(
name|gtk_widget_get_window
argument_list|(
name|widget
argument_list|)
argument_list|,
operator|&
name|gdk_color
argument_list|)
expr_stmt|;
name|gtk_widget_queue_draw
argument_list|(
name|GTK_WIDGET
argument_list|(
name|canvas
argument_list|)
argument_list|)
expr_stmt|;
block|}
end_function

end_unit

