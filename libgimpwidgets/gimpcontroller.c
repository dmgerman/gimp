begin_unit|revision:0.9.5;language:C;cregit-version:0.0.1
begin_comment
comment|/* LIBGIMP - The GIMP Library  * Copyright (C) 1995-1997 Peter Mattis and Spencer Kimball  *  * gimpcontroller.c  * Copyright (C) 2004 Michael Natterer<mitch@gimp.org>  *  * This library is free software; you can redistribute it and/or  * modify it under the terms of the GNU Lesser General Public  * License as published by the Free Software Foundation; either  * version 2 of the License, or (at your option) any later version.  *  * This library is distributed in the hope that it will be useful,  * but WITHOUT ANY WARRANTY; without even the implied warranty of  * MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the GNU  * Lesser General Public License for more details.  *  * You should have received a copy of the GNU Lesser General Public  * License along with this library; if not, write to the  * Free Software Foundation, Inc., 59 Temple Place - Suite 330,  * Boston, MA 02111-1307, USA.  */
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
file|"libgimpcolor/gimpcolor.h"
end_include

begin_include
include|#
directive|include
file|"libgimpconfig/gimpconfig.h"
end_include

begin_include
include|#
directive|include
file|"gimpwidgetstypes.h"
end_include

begin_include
include|#
directive|include
file|"gimpwidgetsmarshal.h"
end_include

begin_define
DECL|macro|GIMP_ENABLE_CONTROLLER_UNDER_CONSTRUCTION
define|#
directive|define
name|GIMP_ENABLE_CONTROLLER_UNDER_CONSTRUCTION
end_define

begin_include
include|#
directive|include
file|"gimpcontroller.h"
end_include

begin_enum
enum|enum
DECL|enum|__anon27f153820103
block|{
DECL|enumerator|PROP_0
name|PROP_0
block|,
DECL|enumerator|PROP_NAME
name|PROP_NAME
block|,
DECL|enumerator|PROP_STATE
name|PROP_STATE
block|}
enum|;
end_enum

begin_enum
enum|enum
DECL|enum|__anon27f153820203
block|{
DECL|enumerator|EVENT
name|EVENT
block|,
DECL|enumerator|LAST_SIGNAL
name|LAST_SIGNAL
block|}
enum|;
end_enum

begin_function_decl
specifier|static
name|void
name|gimp_controller_class_init
parameter_list|(
name|GimpControllerClass
modifier|*
name|klass
parameter_list|)
function_decl|;
end_function_decl

begin_function_decl
specifier|static
name|void
name|gimp_controller_set_property
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
name|gimp_controller_get_property
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

begin_decl_stmt
DECL|variable|parent_class
specifier|static
name|GObjectClass
modifier|*
name|parent_class
init|=
name|NULL
decl_stmt|;
end_decl_stmt

begin_decl_stmt
DECL|variable|controller_signals
specifier|static
name|guint
name|controller_signals
index|[
name|LAST_SIGNAL
index|]
init|=
block|{
literal|0
block|}
decl_stmt|;
end_decl_stmt

begin_function
name|GType
DECL|function|gimp_controller_get_type (void)
name|gimp_controller_get_type
parameter_list|(
name|void
parameter_list|)
block|{
specifier|static
name|GType
name|controller_type
init|=
literal|0
decl_stmt|;
if|if
condition|(
operator|!
name|controller_type
condition|)
block|{
specifier|static
specifier|const
name|GTypeInfo
name|controller_info
init|=
block|{
sizeof|sizeof
argument_list|(
name|GimpControllerClass
argument_list|)
block|,
operator|(
name|GBaseInitFunc
operator|)
name|NULL
block|,
operator|(
name|GBaseFinalizeFunc
operator|)
name|NULL
block|,
operator|(
name|GClassInitFunc
operator|)
name|gimp_controller_class_init
block|,
name|NULL
block|,
comment|/* class_finalize */
name|NULL
block|,
comment|/* class_data     */
sizeof|sizeof
argument_list|(
name|GimpController
argument_list|)
block|,
literal|0
block|,
comment|/* n_preallocs    */
name|NULL
comment|/* instance_init  */
block|}
decl_stmt|;
specifier|static
specifier|const
name|GInterfaceInfo
name|controller_iface_info
init|=
block|{
name|NULL
block|,
comment|/* iface_init     */
name|NULL
block|,
comment|/* iface_finalize */
name|NULL
comment|/* iface_data     */
block|}
decl_stmt|;
name|controller_type
operator|=
name|g_type_register_static
argument_list|(
name|G_TYPE_OBJECT
argument_list|,
literal|"GimpController"
argument_list|,
operator|&
name|controller_info
argument_list|,
literal|0
argument_list|)
expr_stmt|;
name|g_type_add_interface_static
argument_list|(
name|controller_type
argument_list|,
name|GIMP_TYPE_CONFIG
argument_list|,
operator|&
name|controller_iface_info
argument_list|)
expr_stmt|;
block|}
return|return
name|controller_type
return|;
block|}
end_function

begin_function
name|gboolean
DECL|function|gimp_controller_boolean_handled_accumulator (GSignalInvocationHint * ihint,GValue * return_accu,const GValue * handler_return,gpointer dummy)
name|gimp_controller_boolean_handled_accumulator
parameter_list|(
name|GSignalInvocationHint
modifier|*
name|ihint
parameter_list|,
name|GValue
modifier|*
name|return_accu
parameter_list|,
specifier|const
name|GValue
modifier|*
name|handler_return
parameter_list|,
name|gpointer
name|dummy
parameter_list|)
block|{
name|gboolean
name|continue_emission
decl_stmt|;
name|gboolean
name|signal_handled
decl_stmt|;
name|signal_handled
operator|=
name|g_value_get_boolean
argument_list|(
name|handler_return
argument_list|)
expr_stmt|;
name|g_value_set_boolean
argument_list|(
name|return_accu
argument_list|,
name|signal_handled
argument_list|)
expr_stmt|;
name|continue_emission
operator|=
operator|!
name|signal_handled
expr_stmt|;
return|return
name|continue_emission
return|;
block|}
end_function

begin_function
specifier|static
name|void
DECL|function|gimp_controller_class_init (GimpControllerClass * klass)
name|gimp_controller_class_init
parameter_list|(
name|GimpControllerClass
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
name|parent_class
operator|=
name|g_type_class_peek_parent
argument_list|(
name|klass
argument_list|)
expr_stmt|;
name|object_class
operator|->
name|set_property
operator|=
name|gimp_controller_set_property
expr_stmt|;
name|object_class
operator|->
name|get_property
operator|=
name|gimp_controller_get_property
expr_stmt|;
name|g_object_class_install_property
argument_list|(
name|object_class
argument_list|,
name|PROP_NAME
argument_list|,
name|g_param_spec_string
argument_list|(
literal|"name"
argument_list|,
name|NULL
argument_list|,
name|NULL
argument_list|,
literal|"Unnamed Controller"
argument_list|,
name|G_PARAM_READWRITE
operator||
name|G_PARAM_CONSTRUCT
argument_list|)
argument_list|)
expr_stmt|;
name|g_object_class_install_property
argument_list|(
name|object_class
argument_list|,
name|PROP_STATE
argument_list|,
name|g_param_spec_string
argument_list|(
literal|"state"
argument_list|,
name|NULL
argument_list|,
name|NULL
argument_list|,
literal|"Unknown"
argument_list|,
name|G_PARAM_READWRITE
operator||
name|G_PARAM_CONSTRUCT
argument_list|)
argument_list|)
expr_stmt|;
name|controller_signals
index|[
name|EVENT
index|]
operator|=
name|g_signal_new
argument_list|(
literal|"event"
argument_list|,
name|G_TYPE_FROM_CLASS
argument_list|(
name|klass
argument_list|)
argument_list|,
name|G_SIGNAL_RUN_LAST
argument_list|,
name|G_STRUCT_OFFSET
argument_list|(
name|GimpControllerClass
argument_list|,
name|event
argument_list|)
argument_list|,
name|gimp_controller_boolean_handled_accumulator
argument_list|,
name|NULL
argument_list|,
name|_gimp_widgets_marshal_BOOLEAN__POINTER
argument_list|,
name|G_TYPE_BOOLEAN
argument_list|,
literal|1
argument_list|,
name|G_TYPE_POINTER
argument_list|)
expr_stmt|;
name|klass
operator|->
name|name
operator|=
literal|"Unnamed"
expr_stmt|;
name|klass
operator|->
name|help_domain
operator|=
name|NULL
expr_stmt|;
name|klass
operator|->
name|help_id
operator|=
name|NULL
expr_stmt|;
name|klass
operator|->
name|get_n_events
operator|=
name|NULL
expr_stmt|;
name|klass
operator|->
name|get_event_name
operator|=
name|NULL
expr_stmt|;
name|klass
operator|->
name|event
operator|=
name|NULL
expr_stmt|;
block|}
end_function

begin_function
specifier|static
name|void
DECL|function|gimp_controller_set_property (GObject * object,guint property_id,const GValue * value,GParamSpec * pspec)
name|gimp_controller_set_property
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
name|GimpController
modifier|*
name|controller
init|=
name|GIMP_CONTROLLER
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
name|PROP_NAME
case|:
if|if
condition|(
name|controller
operator|->
name|name
condition|)
name|g_free
argument_list|(
name|controller
operator|->
name|name
argument_list|)
expr_stmt|;
name|controller
operator|->
name|name
operator|=
name|g_value_dup_string
argument_list|(
name|value
argument_list|)
expr_stmt|;
break|break;
case|case
name|PROP_STATE
case|:
if|if
condition|(
name|controller
operator|->
name|state
condition|)
name|g_free
argument_list|(
name|controller
operator|->
name|state
argument_list|)
expr_stmt|;
name|controller
operator|->
name|state
operator|=
name|g_value_dup_string
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
DECL|function|gimp_controller_get_property (GObject * object,guint property_id,GValue * value,GParamSpec * pspec)
name|gimp_controller_get_property
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
name|GimpController
modifier|*
name|controller
init|=
name|GIMP_CONTROLLER
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
name|PROP_NAME
case|:
name|g_value_set_string
argument_list|(
name|value
argument_list|,
name|controller
operator|->
name|name
argument_list|)
expr_stmt|;
break|break;
case|case
name|PROP_STATE
case|:
name|g_value_set_string
argument_list|(
name|value
argument_list|,
name|controller
operator|->
name|state
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
name|GimpController
modifier|*
DECL|function|gimp_controller_new (GType controller_type)
name|gimp_controller_new
parameter_list|(
name|GType
name|controller_type
parameter_list|)
block|{
name|GimpController
modifier|*
name|controller
decl_stmt|;
name|g_return_val_if_fail
argument_list|(
name|g_type_is_a
argument_list|(
name|controller_type
argument_list|,
name|GIMP_TYPE_CONTROLLER
argument_list|)
argument_list|,
name|NULL
argument_list|)
expr_stmt|;
name|controller
operator|=
name|g_object_new
argument_list|(
name|controller_type
argument_list|,
name|NULL
argument_list|)
expr_stmt|;
return|return
name|controller
return|;
block|}
end_function

begin_function
name|gint
DECL|function|gimp_controller_get_n_events (GimpController * controller)
name|gimp_controller_get_n_events
parameter_list|(
name|GimpController
modifier|*
name|controller
parameter_list|)
block|{
name|g_return_val_if_fail
argument_list|(
name|GIMP_IS_CONTROLLER
argument_list|(
name|controller
argument_list|)
argument_list|,
literal|0
argument_list|)
expr_stmt|;
if|if
condition|(
name|GIMP_CONTROLLER_GET_CLASS
argument_list|(
name|controller
argument_list|)
operator|->
name|get_n_events
condition|)
return|return
name|GIMP_CONTROLLER_GET_CLASS
argument_list|(
name|controller
argument_list|)
operator|->
name|get_n_events
argument_list|(
name|controller
argument_list|)
return|;
return|return
literal|0
return|;
block|}
end_function

begin_function
specifier|const
name|gchar
modifier|*
DECL|function|gimp_controller_get_event_name (GimpController * controller,gint event_id)
name|gimp_controller_get_event_name
parameter_list|(
name|GimpController
modifier|*
name|controller
parameter_list|,
name|gint
name|event_id
parameter_list|)
block|{
specifier|const
name|gchar
modifier|*
name|name
init|=
name|NULL
decl_stmt|;
name|g_return_val_if_fail
argument_list|(
name|GIMP_IS_CONTROLLER
argument_list|(
name|controller
argument_list|)
argument_list|,
name|NULL
argument_list|)
expr_stmt|;
if|if
condition|(
name|GIMP_CONTROLLER_GET_CLASS
argument_list|(
name|controller
argument_list|)
operator|->
name|get_event_name
condition|)
name|name
operator|=
name|GIMP_CONTROLLER_GET_CLASS
argument_list|(
name|controller
argument_list|)
operator|->
name|get_event_name
argument_list|(
name|controller
argument_list|,
name|event_id
argument_list|)
expr_stmt|;
if|if
condition|(
operator|!
name|name
condition|)
name|name
operator|=
literal|"<invalid event id>"
expr_stmt|;
return|return
name|name
return|;
block|}
end_function

begin_function
specifier|const
name|gchar
modifier|*
DECL|function|gimp_controller_get_event_blurb (GimpController * controller,gint event_id)
name|gimp_controller_get_event_blurb
parameter_list|(
name|GimpController
modifier|*
name|controller
parameter_list|,
name|gint
name|event_id
parameter_list|)
block|{
specifier|const
name|gchar
modifier|*
name|blurb
init|=
name|NULL
decl_stmt|;
name|g_return_val_if_fail
argument_list|(
name|GIMP_IS_CONTROLLER
argument_list|(
name|controller
argument_list|)
argument_list|,
name|NULL
argument_list|)
expr_stmt|;
if|if
condition|(
name|GIMP_CONTROLLER_GET_CLASS
argument_list|(
name|controller
argument_list|)
operator|->
name|get_event_blurb
condition|)
name|blurb
operator|=
name|GIMP_CONTROLLER_GET_CLASS
argument_list|(
name|controller
argument_list|)
operator|->
name|get_event_blurb
argument_list|(
name|controller
argument_list|,
name|event_id
argument_list|)
expr_stmt|;
if|if
condition|(
operator|!
name|blurb
condition|)
name|blurb
operator|=
literal|"<invalid event id>"
expr_stmt|;
return|return
name|blurb
return|;
block|}
end_function

begin_function
name|gboolean
DECL|function|gimp_controller_event (GimpController * controller,const GimpControllerEvent * event)
name|gimp_controller_event
parameter_list|(
name|GimpController
modifier|*
name|controller
parameter_list|,
specifier|const
name|GimpControllerEvent
modifier|*
name|event
parameter_list|)
block|{
name|gboolean
name|retval
init|=
name|FALSE
decl_stmt|;
name|g_return_val_if_fail
argument_list|(
name|GIMP_IS_CONTROLLER
argument_list|(
name|controller
argument_list|)
argument_list|,
name|FALSE
argument_list|)
expr_stmt|;
name|g_return_val_if_fail
argument_list|(
name|event
operator|!=
name|NULL
argument_list|,
name|FALSE
argument_list|)
expr_stmt|;
name|g_signal_emit
argument_list|(
name|controller
argument_list|,
name|controller_signals
index|[
name|EVENT
index|]
argument_list|,
literal|0
argument_list|,
name|event
argument_list|,
operator|&
name|retval
argument_list|)
expr_stmt|;
return|return
name|retval
return|;
block|}
end_function

end_unit

