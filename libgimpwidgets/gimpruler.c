begin_unit|revision:0.9.5;language:C;cregit-version:0.0.1
begin_comment
comment|/* LIBGIMP - The GIMP Library  * Copyright (C) 1995-1997 Peter Mattis and Spencer Kimball  *  * This library is free software; you can redistribute it and/or  * modify it under the terms of the GNU Lesser General Public  * License as published by the Free Software Foundation; either  * version 2 of the License, or (at your option) any later version.  *  * This library is distributed in the hope that it will be useful,  * but WITHOUT ANY WARRANTY; without even the implied warranty of  * MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the GNU  * Lesser General Public License for more details.  *  * You should have received a copy of the GNU Lesser General Public  * License along with this library; if not, write to the  * Free Software Foundation, Inc., 59 Temple Place - Suite 330,  * Boston, MA 02111-1307, USA.  */
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
file|"libgimpbase/gimpbase.h"
end_include

begin_include
include|#
directive|include
file|"gimpwidgetstypes.h"
end_include

begin_include
include|#
directive|include
file|"gimpruler.h"
end_include

begin_comment
comment|/* All distances below are in 1/72nd's of an inch. (According to  * Adobe that's a point, but points are really 1/72.27 in.)  */
end_comment

begin_typedef
typedef|typedef
struct|struct
DECL|struct|__anon2a08e9e50108
block|{
DECL|member|unit
name|GimpUnit
name|unit
decl_stmt|;
DECL|member|lower
name|gdouble
name|lower
decl_stmt|;
DECL|member|upper
name|gdouble
name|upper
decl_stmt|;
DECL|member|position
name|gdouble
name|position
decl_stmt|;
DECL|member|max_size
name|gdouble
name|max_size
decl_stmt|;
DECL|member|backing_store
name|GdkPixmap
modifier|*
name|backing_store
decl_stmt|;
DECL|member|non_gr_exp_gc
name|GdkGC
modifier|*
name|non_gr_exp_gc
decl_stmt|;
DECL|typedef|GimpRulerPrivate
block|}
name|GimpRulerPrivate
typedef|;
end_typedef

begin_enum
enum|enum
DECL|enum|__anon2a08e9e50203
block|{
DECL|enumerator|PROP_0
name|PROP_0
block|,
DECL|enumerator|PROP_UNIT
name|PROP_UNIT
block|,
DECL|enumerator|PROP_LOWER
name|PROP_LOWER
block|,
DECL|enumerator|PROP_UPPER
name|PROP_UPPER
block|,
DECL|enumerator|PROP_POSITION
name|PROP_POSITION
block|,
DECL|enumerator|PROP_MAX_SIZE
name|PROP_MAX_SIZE
block|}
enum|;
end_enum

begin_function_decl
specifier|static
name|void
name|gimp_ruler_realize
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
name|gimp_ruler_unrealize
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
name|gimp_ruler_size_allocate
parameter_list|(
name|GtkWidget
modifier|*
name|widget
parameter_list|,
name|GtkAllocation
modifier|*
name|allocation
parameter_list|)
function_decl|;
end_function_decl

begin_function_decl
specifier|static
name|gint
name|gimp_ruler_expose
parameter_list|(
name|GtkWidget
modifier|*
name|widget
parameter_list|,
name|GdkEventExpose
modifier|*
name|event
parameter_list|)
function_decl|;
end_function_decl

begin_function_decl
specifier|static
name|void
name|gimp_ruler_draw_ticks
parameter_list|(
name|GimpRuler
modifier|*
name|ruler
parameter_list|)
function_decl|;
end_function_decl

begin_function_decl
specifier|static
name|void
name|gimp_ruler_draw_pos
parameter_list|(
name|GimpRuler
modifier|*
name|ruler
parameter_list|)
function_decl|;
end_function_decl

begin_function_decl
specifier|static
name|void
name|gimp_ruler_make_pixmap
parameter_list|(
name|GimpRuler
modifier|*
name|ruler
parameter_list|)
function_decl|;
end_function_decl

begin_function_decl
specifier|static
name|void
name|gimp_ruler_set_property
parameter_list|(
name|GObject
modifier|*
name|object
parameter_list|,
name|guint
name|prop_id
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
name|gimp_ruler_get_property
parameter_list|(
name|GObject
modifier|*
name|object
parameter_list|,
name|guint
name|prop_id
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

begin_macro
DECL|function|G_DEFINE_TYPE (GimpRuler,gimp_ruler,GTK_TYPE_WIDGET)
name|G_DEFINE_TYPE
argument_list|(
argument|GimpRuler
argument_list|,
argument|gimp_ruler
argument_list|,
argument|GTK_TYPE_WIDGET
argument_list|)
end_macro

begin_define
DECL|macro|GIMP_RULER_GET_PRIVATE (ruler)
define|#
directive|define
name|GIMP_RULER_GET_PRIVATE
parameter_list|(
name|ruler
parameter_list|)
define|\
value|G_TYPE_INSTANCE_GET_PRIVATE (ruler, GIMP_TYPE_RULER, GimpRulerPrivate)
end_define

begin_function
specifier|static
name|void
name|gimp_ruler_class_init
parameter_list|(
name|GimpRulerClass
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
name|gimp_ruler_set_property
expr_stmt|;
name|object_class
operator|->
name|get_property
operator|=
name|gimp_ruler_get_property
expr_stmt|;
name|widget_class
operator|->
name|realize
operator|=
name|gimp_ruler_realize
expr_stmt|;
name|widget_class
operator|->
name|unrealize
operator|=
name|gimp_ruler_unrealize
expr_stmt|;
name|widget_class
operator|->
name|size_allocate
operator|=
name|gimp_ruler_size_allocate
expr_stmt|;
name|widget_class
operator|->
name|expose_event
operator|=
name|gimp_ruler_expose
expr_stmt|;
name|klass
operator|->
name|draw_ticks
operator|=
name|NULL
expr_stmt|;
name|klass
operator|->
name|draw_pos
operator|=
name|NULL
expr_stmt|;
name|g_type_class_add_private
argument_list|(
name|object_class
argument_list|,
sizeof|sizeof
argument_list|(
name|GimpRulerPrivate
argument_list|)
argument_list|)
expr_stmt|;
name|g_object_class_install_property
argument_list|(
name|object_class
argument_list|,
name|PROP_LOWER
argument_list|,
name|gimp_param_spec_unit
argument_list|(
literal|"unit"
argument_list|,
literal|"Unit"
argument_list|,
literal|"Unit of ruler"
argument_list|,
name|TRUE
argument_list|,
name|TRUE
argument_list|,
name|GIMP_UNIT_PIXEL
argument_list|,
name|GIMP_PARAM_READWRITE
argument_list|)
argument_list|)
expr_stmt|;
name|g_object_class_install_property
argument_list|(
name|object_class
argument_list|,
name|PROP_LOWER
argument_list|,
name|g_param_spec_double
argument_list|(
literal|"lower"
argument_list|,
literal|"Lower"
argument_list|,
literal|"Lower limit of ruler"
argument_list|,
operator|-
name|G_MAXDOUBLE
argument_list|,
name|G_MAXDOUBLE
argument_list|,
literal|0.0
argument_list|,
name|GIMP_PARAM_READWRITE
argument_list|)
argument_list|)
expr_stmt|;
name|g_object_class_install_property
argument_list|(
name|object_class
argument_list|,
name|PROP_UPPER
argument_list|,
name|g_param_spec_double
argument_list|(
literal|"upper"
argument_list|,
literal|"Upper"
argument_list|,
literal|"Upper limit of ruler"
argument_list|,
operator|-
name|G_MAXDOUBLE
argument_list|,
name|G_MAXDOUBLE
argument_list|,
literal|0.0
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
name|g_param_spec_double
argument_list|(
literal|"position"
argument_list|,
literal|"Position"
argument_list|,
literal|"Position of mark on the ruler"
argument_list|,
operator|-
name|G_MAXDOUBLE
argument_list|,
name|G_MAXDOUBLE
argument_list|,
literal|0.0
argument_list|,
name|GIMP_PARAM_READWRITE
argument_list|)
argument_list|)
expr_stmt|;
name|g_object_class_install_property
argument_list|(
name|object_class
argument_list|,
name|PROP_MAX_SIZE
argument_list|,
name|g_param_spec_double
argument_list|(
literal|"max-size"
argument_list|,
literal|"Max Size"
argument_list|,
literal|"Maximum size of the ruler"
argument_list|,
operator|-
name|G_MAXDOUBLE
argument_list|,
name|G_MAXDOUBLE
argument_list|,
literal|0.0
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
DECL|function|gimp_ruler_init (GimpRuler * ruler)
name|gimp_ruler_init
parameter_list|(
name|GimpRuler
modifier|*
name|ruler
parameter_list|)
block|{
name|GimpRulerPrivate
modifier|*
name|priv
init|=
name|GIMP_RULER_GET_PRIVATE
argument_list|(
name|ruler
argument_list|)
decl_stmt|;
name|priv
operator|->
name|unit
operator|=
name|GIMP_PIXELS
expr_stmt|;
name|priv
operator|->
name|lower
operator|=
literal|0
expr_stmt|;
name|priv
operator|->
name|upper
operator|=
literal|0
expr_stmt|;
name|priv
operator|->
name|position
operator|=
literal|0
expr_stmt|;
name|priv
operator|->
name|max_size
operator|=
literal|0
expr_stmt|;
name|priv
operator|->
name|backing_store
operator|=
name|NULL
expr_stmt|;
name|priv
operator|->
name|non_gr_exp_gc
operator|=
name|NULL
expr_stmt|;
block|}
end_function

begin_function
specifier|static
name|void
DECL|function|gimp_ruler_set_property (GObject * object,guint prop_id,const GValue * value,GParamSpec * pspec)
name|gimp_ruler_set_property
parameter_list|(
name|GObject
modifier|*
name|object
parameter_list|,
name|guint
name|prop_id
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
name|GimpRuler
modifier|*
name|ruler
init|=
name|GIMP_RULER
argument_list|(
name|object
argument_list|)
decl_stmt|;
name|GimpRulerPrivate
modifier|*
name|priv
init|=
name|GIMP_RULER_GET_PRIVATE
argument_list|(
name|ruler
argument_list|)
decl_stmt|;
switch|switch
condition|(
name|prop_id
condition|)
block|{
case|case
name|PROP_UNIT
case|:
name|gimp_ruler_set_unit
argument_list|(
name|ruler
argument_list|,
name|g_value_get_int
argument_list|(
name|value
argument_list|)
argument_list|)
expr_stmt|;
break|break;
case|case
name|PROP_LOWER
case|:
name|gimp_ruler_set_range
argument_list|(
name|ruler
argument_list|,
name|g_value_get_double
argument_list|(
name|value
argument_list|)
argument_list|,
name|priv
operator|->
name|upper
argument_list|,
name|priv
operator|->
name|max_size
argument_list|)
expr_stmt|;
break|break;
case|case
name|PROP_UPPER
case|:
name|gimp_ruler_set_range
argument_list|(
name|ruler
argument_list|,
name|priv
operator|->
name|lower
argument_list|,
name|g_value_get_double
argument_list|(
name|value
argument_list|)
argument_list|,
name|priv
operator|->
name|max_size
argument_list|)
expr_stmt|;
break|break;
case|case
name|PROP_POSITION
case|:
name|gimp_ruler_set_position
argument_list|(
name|ruler
argument_list|,
name|g_value_get_double
argument_list|(
name|value
argument_list|)
argument_list|)
expr_stmt|;
break|break;
case|case
name|PROP_MAX_SIZE
case|:
name|gimp_ruler_set_range
argument_list|(
name|ruler
argument_list|,
name|priv
operator|->
name|lower
argument_list|,
name|priv
operator|->
name|upper
argument_list|,
name|g_value_get_double
argument_list|(
name|value
argument_list|)
argument_list|)
expr_stmt|;
break|break;
default|default:
name|G_OBJECT_WARN_INVALID_PROPERTY_ID
argument_list|(
name|object
argument_list|,
name|prop_id
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
DECL|function|gimp_ruler_get_property (GObject * object,guint prop_id,GValue * value,GParamSpec * pspec)
name|gimp_ruler_get_property
parameter_list|(
name|GObject
modifier|*
name|object
parameter_list|,
name|guint
name|prop_id
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
name|GimpRuler
modifier|*
name|ruler
init|=
name|GIMP_RULER
argument_list|(
name|object
argument_list|)
decl_stmt|;
name|GimpRulerPrivate
modifier|*
name|priv
init|=
name|GIMP_RULER_GET_PRIVATE
argument_list|(
name|ruler
argument_list|)
decl_stmt|;
switch|switch
condition|(
name|prop_id
condition|)
block|{
case|case
name|PROP_UNIT
case|:
name|g_value_set_int
argument_list|(
name|value
argument_list|,
name|priv
operator|->
name|unit
argument_list|)
expr_stmt|;
break|break;
case|case
name|PROP_LOWER
case|:
name|g_value_set_double
argument_list|(
name|value
argument_list|,
name|priv
operator|->
name|lower
argument_list|)
expr_stmt|;
break|break;
case|case
name|PROP_UPPER
case|:
name|g_value_set_double
argument_list|(
name|value
argument_list|,
name|priv
operator|->
name|upper
argument_list|)
expr_stmt|;
break|break;
case|case
name|PROP_POSITION
case|:
name|g_value_set_double
argument_list|(
name|value
argument_list|,
name|priv
operator|->
name|position
argument_list|)
expr_stmt|;
break|break;
case|case
name|PROP_MAX_SIZE
case|:
name|g_value_set_double
argument_list|(
name|value
argument_list|,
name|priv
operator|->
name|max_size
argument_list|)
expr_stmt|;
break|break;
default|default:
name|G_OBJECT_WARN_INVALID_PROPERTY_ID
argument_list|(
name|object
argument_list|,
name|prop_id
argument_list|,
name|pspec
argument_list|)
expr_stmt|;
break|break;
block|}
block|}
end_function

begin_comment
comment|/**  * gimp_ruler_set_position:  * @ruler: a #GimpRuler  * @unit:  the #GimpUnit to set the ruler to  *  * This sets the unit of the ruler.  *  * Since: GIMP 2.8  */
end_comment

begin_function
name|void
DECL|function|gimp_ruler_set_unit (GimpRuler * ruler,GimpUnit unit)
name|gimp_ruler_set_unit
parameter_list|(
name|GimpRuler
modifier|*
name|ruler
parameter_list|,
name|GimpUnit
name|unit
parameter_list|)
block|{
name|GimpRulerPrivate
modifier|*
name|priv
decl_stmt|;
name|g_return_if_fail
argument_list|(
name|GIMP_IS_RULER
argument_list|(
name|ruler
argument_list|)
argument_list|)
expr_stmt|;
name|priv
operator|=
name|GIMP_RULER_GET_PRIVATE
argument_list|(
name|ruler
argument_list|)
expr_stmt|;
if|if
condition|(
name|priv
operator|->
name|unit
operator|!=
name|unit
condition|)
block|{
name|priv
operator|->
name|unit
operator|=
name|unit
expr_stmt|;
name|g_object_notify
argument_list|(
name|G_OBJECT
argument_list|(
name|ruler
argument_list|)
argument_list|,
literal|"unit"
argument_list|)
expr_stmt|;
name|gtk_widget_queue_draw
argument_list|(
name|GTK_WIDGET
argument_list|(
name|ruler
argument_list|)
argument_list|)
expr_stmt|;
block|}
block|}
end_function

begin_comment
comment|/**  * gimp_ruler_get_unit:  * @ruler: a #GimpRuler  *  * Return value: the unit currently used in the @ruler widget.  *  * Since: GIMP 2.8  **/
end_comment

begin_function
name|GimpUnit
DECL|function|gimp_ruler_get_unit (GimpRuler * ruler)
name|gimp_ruler_get_unit
parameter_list|(
name|GimpRuler
modifier|*
name|ruler
parameter_list|)
block|{
name|g_return_val_if_fail
argument_list|(
name|GIMP_IS_RULER
argument_list|(
name|ruler
argument_list|)
argument_list|,
literal|0
argument_list|)
expr_stmt|;
return|return
name|GIMP_RULER_GET_PRIVATE
argument_list|(
name|ruler
argument_list|)
operator|->
name|unit
return|;
block|}
end_function

begin_comment
comment|/**  * gimp_ruler_set_position:  * @ruler: a #GimpRuler  * @position: the position to set the ruler to  *  * This sets the position of the ruler.  *  * Since: GIMP 2.8  */
end_comment

begin_function
name|void
DECL|function|gimp_ruler_set_position (GimpRuler * ruler,gdouble position)
name|gimp_ruler_set_position
parameter_list|(
name|GimpRuler
modifier|*
name|ruler
parameter_list|,
name|gdouble
name|position
parameter_list|)
block|{
name|GimpRulerPrivate
modifier|*
name|priv
decl_stmt|;
name|g_return_if_fail
argument_list|(
name|GIMP_IS_RULER
argument_list|(
name|ruler
argument_list|)
argument_list|)
expr_stmt|;
name|priv
operator|=
name|GIMP_RULER_GET_PRIVATE
argument_list|(
name|ruler
argument_list|)
expr_stmt|;
if|if
condition|(
name|priv
operator|->
name|position
operator|!=
name|position
condition|)
block|{
name|priv
operator|->
name|position
operator|=
name|position
expr_stmt|;
name|g_object_notify
argument_list|(
name|G_OBJECT
argument_list|(
name|ruler
argument_list|)
argument_list|,
literal|"position"
argument_list|)
expr_stmt|;
name|gimp_ruler_draw_pos
argument_list|(
name|ruler
argument_list|)
expr_stmt|;
block|}
block|}
end_function

begin_comment
comment|/**  * gimp_ruler_get_position:  * @ruler: a #GimpRuler  *  * Return value: the current position of the @ruler widget.  *  * Since: GIMP 2.8  **/
end_comment

begin_function
name|gdouble
DECL|function|gimp_ruler_get_position (GimpRuler * ruler)
name|gimp_ruler_get_position
parameter_list|(
name|GimpRuler
modifier|*
name|ruler
parameter_list|)
block|{
name|g_return_val_if_fail
argument_list|(
name|GIMP_IS_RULER
argument_list|(
name|ruler
argument_list|)
argument_list|,
literal|0.0
argument_list|)
expr_stmt|;
return|return
name|GIMP_RULER_GET_PRIVATE
argument_list|(
name|ruler
argument_list|)
operator|->
name|position
return|;
block|}
end_function

begin_comment
comment|/**  * gimp_ruler_set_range:  * @ruler: a #GimpRuler  * @lower: the lower limit of the ruler  * @upper: the upper limit of the ruler  * @max_size: the maximum size of the ruler used when calculating the space to  * leave for the text  *  * This sets the range of the ruler.  *  * Since: GIMP 2.8  */
end_comment

begin_function
name|void
DECL|function|gimp_ruler_set_range (GimpRuler * ruler,gdouble lower,gdouble upper,gdouble max_size)
name|gimp_ruler_set_range
parameter_list|(
name|GimpRuler
modifier|*
name|ruler
parameter_list|,
name|gdouble
name|lower
parameter_list|,
name|gdouble
name|upper
parameter_list|,
name|gdouble
name|max_size
parameter_list|)
block|{
name|GimpRulerPrivate
modifier|*
name|priv
decl_stmt|;
name|g_return_if_fail
argument_list|(
name|GIMP_IS_RULER
argument_list|(
name|ruler
argument_list|)
argument_list|)
expr_stmt|;
name|priv
operator|=
name|GIMP_RULER_GET_PRIVATE
argument_list|(
name|ruler
argument_list|)
expr_stmt|;
name|g_object_freeze_notify
argument_list|(
name|G_OBJECT
argument_list|(
name|ruler
argument_list|)
argument_list|)
expr_stmt|;
if|if
condition|(
name|priv
operator|->
name|lower
operator|!=
name|lower
condition|)
block|{
name|priv
operator|->
name|lower
operator|=
name|lower
expr_stmt|;
name|g_object_notify
argument_list|(
name|G_OBJECT
argument_list|(
name|ruler
argument_list|)
argument_list|,
literal|"lower"
argument_list|)
expr_stmt|;
block|}
if|if
condition|(
name|priv
operator|->
name|upper
operator|!=
name|upper
condition|)
block|{
name|priv
operator|->
name|upper
operator|=
name|upper
expr_stmt|;
name|g_object_notify
argument_list|(
name|G_OBJECT
argument_list|(
name|ruler
argument_list|)
argument_list|,
literal|"upper"
argument_list|)
expr_stmt|;
block|}
if|if
condition|(
name|priv
operator|->
name|max_size
operator|!=
name|max_size
condition|)
block|{
name|priv
operator|->
name|max_size
operator|=
name|max_size
expr_stmt|;
name|g_object_notify
argument_list|(
name|G_OBJECT
argument_list|(
name|ruler
argument_list|)
argument_list|,
literal|"max-size"
argument_list|)
expr_stmt|;
block|}
name|g_object_thaw_notify
argument_list|(
name|G_OBJECT
argument_list|(
name|ruler
argument_list|)
argument_list|)
expr_stmt|;
name|gtk_widget_queue_draw
argument_list|(
name|GTK_WIDGET
argument_list|(
name|ruler
argument_list|)
argument_list|)
expr_stmt|;
block|}
end_function

begin_comment
comment|/**  * gimp_ruler_get_range:  * @ruler: a #GimpRuler  * @lower: location to store lower limit of the ruler, or %NULL  * @upper: location to store upper limit of the ruler, or %NULL  * @max_size: location to store the maximum size of the ruler used when  *            calculating the space to leave for the text, or %NULL.  *  * Retrieves values indicating the range and current position of a #GimpRuler.  * See gimp_ruler_set_range().  *  * Since: GIMP 2.8  **/
end_comment

begin_function
name|void
DECL|function|gimp_ruler_get_range (GimpRuler * ruler,gdouble * lower,gdouble * upper,gdouble * max_size)
name|gimp_ruler_get_range
parameter_list|(
name|GimpRuler
modifier|*
name|ruler
parameter_list|,
name|gdouble
modifier|*
name|lower
parameter_list|,
name|gdouble
modifier|*
name|upper
parameter_list|,
name|gdouble
modifier|*
name|max_size
parameter_list|)
block|{
name|GimpRulerPrivate
modifier|*
name|priv
decl_stmt|;
name|g_return_if_fail
argument_list|(
name|GIMP_IS_RULER
argument_list|(
name|ruler
argument_list|)
argument_list|)
expr_stmt|;
name|priv
operator|=
name|GIMP_RULER_GET_PRIVATE
argument_list|(
name|ruler
argument_list|)
expr_stmt|;
if|if
condition|(
name|lower
condition|)
operator|*
name|lower
operator|=
name|priv
operator|->
name|lower
expr_stmt|;
if|if
condition|(
name|upper
condition|)
operator|*
name|upper
operator|=
name|priv
operator|->
name|upper
expr_stmt|;
if|if
condition|(
name|max_size
condition|)
operator|*
name|max_size
operator|=
name|priv
operator|->
name|max_size
expr_stmt|;
block|}
end_function

begin_function
name|GdkDrawable
modifier|*
DECL|function|_gimp_ruler_get_backing_store (GimpRuler * ruler)
name|_gimp_ruler_get_backing_store
parameter_list|(
name|GimpRuler
modifier|*
name|ruler
parameter_list|)
block|{
return|return
name|GIMP_RULER_GET_PRIVATE
argument_list|(
name|ruler
argument_list|)
operator|->
name|backing_store
return|;
block|}
end_function

begin_function
name|PangoLayout
modifier|*
DECL|function|_gimp_ruler_create_pango_layout (GtkWidget * widget,const gchar * text)
name|_gimp_ruler_create_pango_layout
parameter_list|(
name|GtkWidget
modifier|*
name|widget
parameter_list|,
specifier|const
name|gchar
modifier|*
name|text
parameter_list|)
block|{
name|PangoLayout
modifier|*
name|layout
decl_stmt|;
name|PangoAttrList
modifier|*
name|attrs
decl_stmt|;
name|PangoAttribute
modifier|*
name|attr
decl_stmt|;
name|layout
operator|=
name|gtk_widget_create_pango_layout
argument_list|(
name|widget
argument_list|,
name|text
argument_list|)
expr_stmt|;
name|attrs
operator|=
name|pango_attr_list_new
argument_list|()
expr_stmt|;
name|attr
operator|=
name|pango_attr_scale_new
argument_list|(
name|PANGO_SCALE_X_SMALL
argument_list|)
expr_stmt|;
name|attr
operator|->
name|start_index
operator|=
literal|0
expr_stmt|;
name|attr
operator|->
name|end_index
operator|=
operator|-
literal|1
expr_stmt|;
name|pango_attr_list_insert
argument_list|(
name|attrs
argument_list|,
name|attr
argument_list|)
expr_stmt|;
name|pango_layout_set_attributes
argument_list|(
name|layout
argument_list|,
name|attrs
argument_list|)
expr_stmt|;
name|pango_attr_list_unref
argument_list|(
name|attrs
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
DECL|function|gimp_ruler_realize (GtkWidget * widget)
name|gimp_ruler_realize
parameter_list|(
name|GtkWidget
modifier|*
name|widget
parameter_list|)
block|{
name|GimpRuler
modifier|*
name|ruler
init|=
name|GIMP_RULER
argument_list|(
name|widget
argument_list|)
decl_stmt|;
name|GdkWindowAttr
name|attributes
decl_stmt|;
name|gint
name|attributes_mask
decl_stmt|;
name|GTK_WIDGET_SET_FLAGS
argument_list|(
name|ruler
argument_list|,
name|GTK_REALIZED
argument_list|)
expr_stmt|;
name|attributes
operator|.
name|window_type
operator|=
name|GDK_WINDOW_CHILD
expr_stmt|;
name|attributes
operator|.
name|x
operator|=
name|widget
operator|->
name|allocation
operator|.
name|x
expr_stmt|;
name|attributes
operator|.
name|y
operator|=
name|widget
operator|->
name|allocation
operator|.
name|y
expr_stmt|;
name|attributes
operator|.
name|width
operator|=
name|widget
operator|->
name|allocation
operator|.
name|width
expr_stmt|;
name|attributes
operator|.
name|height
operator|=
name|widget
operator|->
name|allocation
operator|.
name|height
expr_stmt|;
name|attributes
operator|.
name|wclass
operator|=
name|GDK_INPUT_OUTPUT
expr_stmt|;
name|attributes
operator|.
name|visual
operator|=
name|gtk_widget_get_visual
argument_list|(
name|widget
argument_list|)
expr_stmt|;
name|attributes
operator|.
name|colormap
operator|=
name|gtk_widget_get_colormap
argument_list|(
name|widget
argument_list|)
expr_stmt|;
name|attributes
operator|.
name|event_mask
operator|=
name|gtk_widget_get_events
argument_list|(
name|widget
argument_list|)
expr_stmt|;
name|attributes
operator|.
name|event_mask
operator||=
operator|(
name|GDK_EXPOSURE_MASK
operator||
name|GDK_POINTER_MOTION_MASK
operator||
name|GDK_POINTER_MOTION_HINT_MASK
operator|)
expr_stmt|;
name|attributes_mask
operator|=
name|GDK_WA_X
operator||
name|GDK_WA_Y
operator||
name|GDK_WA_VISUAL
operator||
name|GDK_WA_COLORMAP
expr_stmt|;
name|widget
operator|->
name|window
operator|=
name|gdk_window_new
argument_list|(
name|gtk_widget_get_parent_window
argument_list|(
name|widget
argument_list|)
argument_list|,
operator|&
name|attributes
argument_list|,
name|attributes_mask
argument_list|)
expr_stmt|;
name|gdk_window_set_user_data
argument_list|(
name|widget
operator|->
name|window
argument_list|,
name|ruler
argument_list|)
expr_stmt|;
name|widget
operator|->
name|style
operator|=
name|gtk_style_attach
argument_list|(
name|widget
operator|->
name|style
argument_list|,
name|widget
operator|->
name|window
argument_list|)
expr_stmt|;
name|gtk_style_set_background
argument_list|(
name|widget
operator|->
name|style
argument_list|,
name|widget
operator|->
name|window
argument_list|,
name|GTK_STATE_ACTIVE
argument_list|)
expr_stmt|;
name|gimp_ruler_make_pixmap
argument_list|(
name|ruler
argument_list|)
expr_stmt|;
block|}
end_function

begin_function
specifier|static
name|void
DECL|function|gimp_ruler_unrealize (GtkWidget * widget)
name|gimp_ruler_unrealize
parameter_list|(
name|GtkWidget
modifier|*
name|widget
parameter_list|)
block|{
name|GimpRuler
modifier|*
name|ruler
init|=
name|GIMP_RULER
argument_list|(
name|widget
argument_list|)
decl_stmt|;
name|GimpRulerPrivate
modifier|*
name|priv
init|=
name|GIMP_RULER_GET_PRIVATE
argument_list|(
name|ruler
argument_list|)
decl_stmt|;
if|if
condition|(
name|priv
operator|->
name|backing_store
condition|)
block|{
name|g_object_unref
argument_list|(
name|priv
operator|->
name|backing_store
argument_list|)
expr_stmt|;
name|priv
operator|->
name|backing_store
operator|=
name|NULL
expr_stmt|;
block|}
if|if
condition|(
name|priv
operator|->
name|non_gr_exp_gc
condition|)
block|{
name|g_object_unref
argument_list|(
name|priv
operator|->
name|non_gr_exp_gc
argument_list|)
expr_stmt|;
name|priv
operator|->
name|non_gr_exp_gc
operator|=
name|NULL
expr_stmt|;
block|}
if|if
condition|(
name|GTK_WIDGET_CLASS
argument_list|(
name|gimp_ruler_parent_class
argument_list|)
operator|->
name|unrealize
condition|)
operator|(
operator|*
name|GTK_WIDGET_CLASS
argument_list|(
name|gimp_ruler_parent_class
argument_list|)
operator|->
name|unrealize
operator|)
operator|(
name|widget
operator|)
expr_stmt|;
block|}
end_function

begin_function
specifier|static
name|void
DECL|function|gimp_ruler_size_allocate (GtkWidget * widget,GtkAllocation * allocation)
name|gimp_ruler_size_allocate
parameter_list|(
name|GtkWidget
modifier|*
name|widget
parameter_list|,
name|GtkAllocation
modifier|*
name|allocation
parameter_list|)
block|{
name|GimpRuler
modifier|*
name|ruler
init|=
name|GIMP_RULER
argument_list|(
name|widget
argument_list|)
decl_stmt|;
name|widget
operator|->
name|allocation
operator|=
operator|*
name|allocation
expr_stmt|;
if|if
condition|(
name|GTK_WIDGET_REALIZED
argument_list|(
name|widget
argument_list|)
condition|)
block|{
name|gdk_window_move_resize
argument_list|(
name|widget
operator|->
name|window
argument_list|,
name|allocation
operator|->
name|x
argument_list|,
name|allocation
operator|->
name|y
argument_list|,
name|allocation
operator|->
name|width
argument_list|,
name|allocation
operator|->
name|height
argument_list|)
expr_stmt|;
name|gimp_ruler_make_pixmap
argument_list|(
name|ruler
argument_list|)
expr_stmt|;
block|}
block|}
end_function

begin_function
specifier|static
name|gint
DECL|function|gimp_ruler_expose (GtkWidget * widget,GdkEventExpose * event)
name|gimp_ruler_expose
parameter_list|(
name|GtkWidget
modifier|*
name|widget
parameter_list|,
name|GdkEventExpose
modifier|*
name|event
parameter_list|)
block|{
if|if
condition|(
name|GTK_WIDGET_DRAWABLE
argument_list|(
name|widget
argument_list|)
condition|)
block|{
name|GimpRuler
modifier|*
name|ruler
init|=
name|GIMP_RULER
argument_list|(
name|widget
argument_list|)
decl_stmt|;
name|GimpRulerPrivate
modifier|*
name|priv
init|=
name|GIMP_RULER_GET_PRIVATE
argument_list|(
name|ruler
argument_list|)
decl_stmt|;
name|gimp_ruler_draw_ticks
argument_list|(
name|ruler
argument_list|)
expr_stmt|;
name|gdk_draw_drawable
argument_list|(
name|widget
operator|->
name|window
argument_list|,
name|priv
operator|->
name|non_gr_exp_gc
argument_list|,
name|priv
operator|->
name|backing_store
argument_list|,
literal|0
argument_list|,
literal|0
argument_list|,
literal|0
argument_list|,
literal|0
argument_list|,
name|widget
operator|->
name|allocation
operator|.
name|width
argument_list|,
name|widget
operator|->
name|allocation
operator|.
name|height
argument_list|)
expr_stmt|;
name|gimp_ruler_draw_pos
argument_list|(
name|ruler
argument_list|)
expr_stmt|;
block|}
return|return
name|FALSE
return|;
block|}
end_function

begin_function
specifier|static
name|void
DECL|function|gimp_ruler_draw_ticks (GimpRuler * ruler)
name|gimp_ruler_draw_ticks
parameter_list|(
name|GimpRuler
modifier|*
name|ruler
parameter_list|)
block|{
name|g_return_if_fail
argument_list|(
name|GIMP_IS_RULER
argument_list|(
name|ruler
argument_list|)
argument_list|)
expr_stmt|;
if|if
condition|(
name|GIMP_RULER_GET_CLASS
argument_list|(
name|ruler
argument_list|)
operator|->
name|draw_ticks
condition|)
name|GIMP_RULER_GET_CLASS
argument_list|(
name|ruler
argument_list|)
operator|->
name|draw_ticks
argument_list|(
name|ruler
argument_list|)
expr_stmt|;
block|}
end_function

begin_function
specifier|static
name|void
DECL|function|gimp_ruler_draw_pos (GimpRuler * ruler)
name|gimp_ruler_draw_pos
parameter_list|(
name|GimpRuler
modifier|*
name|ruler
parameter_list|)
block|{
name|g_return_if_fail
argument_list|(
name|GIMP_IS_RULER
argument_list|(
name|ruler
argument_list|)
argument_list|)
expr_stmt|;
if|if
condition|(
name|GIMP_RULER_GET_CLASS
argument_list|(
name|ruler
argument_list|)
operator|->
name|draw_pos
condition|)
name|GIMP_RULER_GET_CLASS
argument_list|(
name|ruler
argument_list|)
operator|->
name|draw_pos
argument_list|(
name|ruler
argument_list|)
expr_stmt|;
block|}
end_function

begin_function
specifier|static
name|void
DECL|function|gimp_ruler_make_pixmap (GimpRuler * ruler)
name|gimp_ruler_make_pixmap
parameter_list|(
name|GimpRuler
modifier|*
name|ruler
parameter_list|)
block|{
name|GimpRulerPrivate
modifier|*
name|priv
init|=
name|GIMP_RULER_GET_PRIVATE
argument_list|(
name|ruler
argument_list|)
decl_stmt|;
name|GtkWidget
modifier|*
name|widget
init|=
name|GTK_WIDGET
argument_list|(
name|ruler
argument_list|)
decl_stmt|;
name|gint
name|width
decl_stmt|;
name|gint
name|height
decl_stmt|;
if|if
condition|(
name|priv
operator|->
name|backing_store
condition|)
block|{
name|gdk_drawable_get_size
argument_list|(
name|priv
operator|->
name|backing_store
argument_list|,
operator|&
name|width
argument_list|,
operator|&
name|height
argument_list|)
expr_stmt|;
if|if
condition|(
operator|(
name|width
operator|==
name|widget
operator|->
name|allocation
operator|.
name|width
operator|)
operator|&&
operator|(
name|height
operator|==
name|widget
operator|->
name|allocation
operator|.
name|height
operator|)
condition|)
return|return;
name|g_object_unref
argument_list|(
name|priv
operator|->
name|backing_store
argument_list|)
expr_stmt|;
block|}
name|priv
operator|->
name|backing_store
operator|=
name|gdk_pixmap_new
argument_list|(
name|widget
operator|->
name|window
argument_list|,
name|widget
operator|->
name|allocation
operator|.
name|width
argument_list|,
name|widget
operator|->
name|allocation
operator|.
name|height
argument_list|,
operator|-
literal|1
argument_list|)
expr_stmt|;
if|if
condition|(
operator|!
name|priv
operator|->
name|non_gr_exp_gc
condition|)
block|{
name|priv
operator|->
name|non_gr_exp_gc
operator|=
name|gdk_gc_new
argument_list|(
name|widget
operator|->
name|window
argument_list|)
expr_stmt|;
name|gdk_gc_set_exposures
argument_list|(
name|priv
operator|->
name|non_gr_exp_gc
argument_list|,
name|FALSE
argument_list|)
expr_stmt|;
block|}
block|}
end_function

end_unit

