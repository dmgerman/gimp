begin_unit|revision:0.9.5;language:C;cregit-version:0.0.1
begin_comment
comment|/* LIBGIMP - The GIMP Library  * Copyright (C) 1995-1997 Peter Mattis and Spencer Kimball  *  * controller_linux_input.c  * Copyright (C) 2004 Sven Neumann<sven@gimp.org>  *  * This library is free software; you can redistribute it and/or  * modify it under the terms of the GNU Lesser General Public  * License as published by the Free Software Foundation; either  * version 2 of the License, or (at your option) any later version.  *  * This library is distributed in the hope that it will be useful,  * but WITHOUT ANY WARRANTY; without even the implied warranty of  * MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the GNU  * Lesser General Public License for more details.  *  * You should have received a copy of the GNU Lesser General Public  * License along with this library; if not, write to the  * Free Software Foundation, Inc., 59 Temple Place - Suite 330,  * Boston, MA 02111-1307, USA.  */
end_comment

begin_include
include|#
directive|include
file|"config.h"
end_include

begin_include
include|#
directive|include
file|<errno.h>
end_include

begin_include
include|#
directive|include
file|<string.h>
end_include

begin_include
include|#
directive|include
file|<sys/types.h>
end_include

begin_include
include|#
directive|include
file|<sys/stat.h>
end_include

begin_include
include|#
directive|include
file|<fcntl.h>
end_include

begin_include
include|#
directive|include
file|<linux/input.h>
end_include

begin_include
include|#
directive|include
file|<gtk/gtk.h>
end_include

begin_include
include|#
directive|include
file|"libgimpmodule/gimpmodule.h"
end_include

begin_include
include|#
directive|include
file|"libgimpwidgets/gimpwidgets.h"
end_include

begin_include
include|#
directive|include
file|"libgimpwidgets/gimpcontroller.h"
end_include

begin_include
include|#
directive|include
file|"libgimp/libgimp-intl.h"
end_include

begin_typedef
typedef|typedef
struct|struct
DECL|struct|__anon2bfa6db70108
block|{
DECL|member|code
name|__u16
name|code
decl_stmt|;
DECL|member|name
specifier|const
name|gchar
modifier|*
name|name
decl_stmt|;
DECL|member|blurb
specifier|const
name|gchar
modifier|*
name|blurb
decl_stmt|;
DECL|typedef|LinuxInputEvent
block|}
name|LinuxInputEvent
typedef|;
end_typedef

begin_decl_stmt
DECL|variable|key_events
specifier|static
specifier|const
name|LinuxInputEvent
name|key_events
index|[]
init|=
block|{
block|{
name|BTN_0
block|,
literal|"button-0"
block|,
name|N_
argument_list|(
literal|"Button 0"
argument_list|)
block|}
block|,
block|{
name|BTN_1
block|,
literal|"button-1"
block|,
name|N_
argument_list|(
literal|"Button 1"
argument_list|)
block|}
block|,
block|{
name|BTN_2
block|,
literal|"button-2"
block|,
name|N_
argument_list|(
literal|"Button 2"
argument_list|)
block|}
block|,
block|{
name|BTN_3
block|,
literal|"button-3"
block|,
name|N_
argument_list|(
literal|"Button 3"
argument_list|)
block|}
block|,
block|{
name|BTN_4
block|,
literal|"button-4"
block|,
name|N_
argument_list|(
literal|"Button 4"
argument_list|)
block|}
block|,
block|{
name|BTN_5
block|,
literal|"button-5"
block|,
name|N_
argument_list|(
literal|"Button 5"
argument_list|)
block|}
block|,
block|{
name|BTN_6
block|,
literal|"button-6"
block|,
name|N_
argument_list|(
literal|"Button 6"
argument_list|)
block|}
block|,
block|{
name|BTN_7
block|,
literal|"button-7"
block|,
name|N_
argument_list|(
literal|"Button 7"
argument_list|)
block|}
block|,
block|{
name|BTN_8
block|,
literal|"button-8"
block|,
name|N_
argument_list|(
literal|"Button 8"
argument_list|)
block|}
block|,
block|{
name|BTN_9
block|,
literal|"button-9"
block|,
name|N_
argument_list|(
literal|"Button 9"
argument_list|)
block|}
block|,
block|{
name|BTN_MOUSE
block|,
literal|"button-mouse"
block|,
name|N_
argument_list|(
literal|"Button Mouse"
argument_list|)
block|}
block|,
block|{
name|BTN_LEFT
block|,
literal|"button-left"
block|,
name|N_
argument_list|(
literal|"Button Left"
argument_list|)
block|}
block|,
block|{
name|BTN_RIGHT
block|,
literal|"button-right"
block|,
name|N_
argument_list|(
literal|"Button Right"
argument_list|)
block|}
block|,
block|{
name|BTN_MIDDLE
block|,
literal|"button-middle"
block|,
name|N_
argument_list|(
literal|"Button Middle"
argument_list|)
block|}
block|,
block|{
name|BTN_SIDE
block|,
literal|"button-side"
block|,
name|N_
argument_list|(
literal|"Button Side"
argument_list|)
block|}
block|,
block|{
name|BTN_EXTRA
block|,
literal|"button-extra"
block|,
name|N_
argument_list|(
literal|"Button Extra"
argument_list|)
block|}
block|,
block|{
name|BTN_FORWARD
block|,
literal|"button-forward"
block|,
name|N_
argument_list|(
literal|"Button Forward"
argument_list|)
block|}
block|,
block|{
name|BTN_BACK
block|,
literal|"button-back"
block|,
name|N_
argument_list|(
literal|"Button Forward"
argument_list|)
block|}
block|,
ifdef|#
directive|ifdef
name|BTN_WHEEL
block|{
name|BTN_WHEEL
block|,
literal|"button-wheel"
block|,
name|N_
argument_list|(
literal|"Button Wheel"
argument_list|)
block|}
block|,
endif|#
directive|endif
ifdef|#
directive|ifdef
name|BTN_GEAR_DOWN
block|{
name|BTN_GEAR_DOWN
block|,
literal|"button-gear-down"
block|,
name|N_
argument_list|(
literal|"Button Gear Down"
argument_list|)
block|}
block|,
endif|#
directive|endif
ifdef|#
directive|ifdef
name|BTN_GEAR_UP
block|{
name|BTN_GEAR_UP
block|,
literal|"button-gear-up"
block|,
name|N_
argument_list|(
literal|"Button Gear Up"
argument_list|)
block|}
endif|#
directive|endif
block|}
decl_stmt|;
end_decl_stmt

begin_decl_stmt
DECL|variable|rel_events
specifier|static
specifier|const
name|LinuxInputEvent
name|rel_events
index|[]
init|=
block|{
block|{
name|REL_WHEEL
block|,
literal|"wheel-turn-left"
block|,
name|N_
argument_list|(
literal|"Wheel Turn Left"
argument_list|)
block|}
block|,
block|{
name|REL_WHEEL
block|,
literal|"wheel-turn-right"
block|,
name|N_
argument_list|(
literal|"Wheel Turn Right"
argument_list|)
block|}
block|,
block|{
name|REL_DIAL
block|,
literal|"dial-turn-left"
block|,
name|N_
argument_list|(
literal|"Dial Turn Left"
argument_list|)
block|}
block|,
block|{
name|REL_DIAL
block|,
literal|"dial-turn-right"
block|,
name|N_
argument_list|(
literal|"Dial Turn Right"
argument_list|)
block|}
block|, }
decl_stmt|;
end_decl_stmt

begin_enum
enum|enum
DECL|enum|__anon2bfa6db70203
block|{
DECL|enumerator|PROP_0
name|PROP_0
block|,
DECL|enumerator|PROP_DEVICE
name|PROP_DEVICE
block|}
enum|;
end_enum

begin_define
DECL|macro|CONTROLLER_TYPE_LINUX_INPUT
define|#
directive|define
name|CONTROLLER_TYPE_LINUX_INPUT
value|(controller_type)
end_define

begin_define
DECL|macro|CONTROLLER_LINUX_INPUT (obj)
define|#
directive|define
name|CONTROLLER_LINUX_INPUT
parameter_list|(
name|obj
parameter_list|)
value|(G_TYPE_CHECK_INSTANCE_CAST ((obj), CONTROLLER_TYPE_LINUX_INPUT, ControllerLinuxInput))
end_define

begin_define
DECL|macro|CONTROLLER_LINUX_INPUT_CLASS (klass)
define|#
directive|define
name|CONTROLLER_LINUX_INPUT_CLASS
parameter_list|(
name|klass
parameter_list|)
value|(G_TYPE_CHECK_CLASS_CAST ((klass), CONTROLLER_TYPE_LINUX_INPUT, ControllerLinuxInputClass))
end_define

begin_define
DECL|macro|CONTROLLER_IS_LINUX_INPUT (obj)
define|#
directive|define
name|CONTROLLER_IS_LINUX_INPUT
parameter_list|(
name|obj
parameter_list|)
value|(G_TYPE_CHECK_INSTANCE_TYPE ((obj), CONTROLLER_TYPE_LINUX_INPUT))
end_define

begin_define
DECL|macro|CONTROLLER_IS_LINUX_INPUT_CLASS (klass)
define|#
directive|define
name|CONTROLLER_IS_LINUX_INPUT_CLASS
parameter_list|(
name|klass
parameter_list|)
value|(G_TYPE_CHECK_CLASS_TYPE ((klass), CONTROLLER_TYPE_LINUX_INPUT))
end_define

begin_typedef
DECL|typedef|ControllerLinuxInput
typedef|typedef
name|struct
name|_ControllerLinuxInput
name|ControllerLinuxInput
typedef|;
end_typedef

begin_typedef
DECL|typedef|ControllerLinuxInputClass
typedef|typedef
name|struct
name|_ControllerLinuxInputClass
name|ControllerLinuxInputClass
typedef|;
end_typedef

begin_struct
DECL|struct|_ControllerLinuxInput
struct|struct
name|_ControllerLinuxInput
block|{
DECL|member|parent_instance
name|GimpController
name|parent_instance
decl_stmt|;
DECL|member|device
name|gchar
modifier|*
name|device
decl_stmt|;
DECL|member|io
name|GIOChannel
modifier|*
name|io
decl_stmt|;
DECL|member|io_id
name|guint
name|io_id
decl_stmt|;
block|}
struct|;
end_struct

begin_struct
DECL|struct|_ControllerLinuxInputClass
struct|struct
name|_ControllerLinuxInputClass
block|{
DECL|member|parent_class
name|GimpControllerClass
name|parent_class
decl_stmt|;
block|}
struct|;
end_struct

begin_function_decl
name|GType
name|linux_input_get_type
parameter_list|(
name|GTypeModule
modifier|*
name|module
parameter_list|)
function_decl|;
end_function_decl

begin_function_decl
specifier|static
name|void
name|linux_input_class_init
parameter_list|(
name|ControllerLinuxInputClass
modifier|*
name|klass
parameter_list|)
function_decl|;
end_function_decl

begin_function_decl
specifier|static
name|void
name|linux_input_dispose
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
name|linux_input_set_property
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
name|linux_input_get_property
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
name|gint
name|linux_input_get_n_events
parameter_list|(
name|GimpController
modifier|*
name|controller
parameter_list|)
function_decl|;
end_function_decl

begin_function_decl
specifier|static
specifier|const
name|gchar
modifier|*
name|linux_input_get_event_name
parameter_list|(
name|GimpController
modifier|*
name|controller
parameter_list|,
name|gint
name|event_id
parameter_list|)
function_decl|;
end_function_decl

begin_function_decl
specifier|static
specifier|const
name|gchar
modifier|*
name|linux_input_get_event_blurb
parameter_list|(
name|GimpController
modifier|*
name|controller
parameter_list|,
name|gint
name|event_id
parameter_list|)
function_decl|;
end_function_decl

begin_function_decl
specifier|static
name|gboolean
name|linux_input_set_device
parameter_list|(
name|ControllerLinuxInput
modifier|*
name|controller
parameter_list|,
specifier|const
name|gchar
modifier|*
name|device
parameter_list|)
function_decl|;
end_function_decl

begin_function_decl
specifier|static
name|gboolean
name|linux_input_read_event
parameter_list|(
name|GIOChannel
modifier|*
name|io
parameter_list|,
name|GIOCondition
name|cond
parameter_list|,
name|gpointer
name|data
parameter_list|)
function_decl|;
end_function_decl

begin_decl_stmt
DECL|variable|linux_input_info
specifier|static
specifier|const
name|GimpModuleInfo
name|linux_input_info
init|=
block|{
name|GIMP_MODULE_ABI_VERSION
block|,
name|N_
argument_list|(
literal|"Linux input event controller"
argument_list|)
block|,
literal|"Sven Neumann<sven@gimp.org>"
block|,
literal|"v0.1"
block|,
literal|"(c) 2004, released under the GPL"
block|,
literal|"June 2004"
block|}
decl_stmt|;
end_decl_stmt

begin_decl_stmt
DECL|variable|controller_type
specifier|static
name|GType
name|controller_type
init|=
literal|0
decl_stmt|;
end_decl_stmt

begin_decl_stmt
DECL|variable|parent_class
specifier|static
name|GimpControllerClass
modifier|*
name|parent_class
init|=
name|NULL
decl_stmt|;
end_decl_stmt

begin_function
name|G_MODULE_EXPORT
specifier|const
name|GimpModuleInfo
modifier|*
DECL|function|gimp_module_query (GTypeModule * module)
name|gimp_module_query
parameter_list|(
name|GTypeModule
modifier|*
name|module
parameter_list|)
block|{
return|return
operator|&
name|linux_input_info
return|;
block|}
end_function

begin_function
name|G_MODULE_EXPORT
name|gboolean
DECL|function|gimp_module_register (GTypeModule * module)
name|gimp_module_register
parameter_list|(
name|GTypeModule
modifier|*
name|module
parameter_list|)
block|{
name|linux_input_get_type
argument_list|(
name|module
argument_list|)
expr_stmt|;
return|return
name|TRUE
return|;
block|}
end_function

begin_function
name|GType
DECL|function|linux_input_get_type (GTypeModule * module)
name|linux_input_get_type
parameter_list|(
name|GTypeModule
modifier|*
name|module
parameter_list|)
block|{
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
name|ControllerLinuxInputClass
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
name|linux_input_class_init
block|,
name|NULL
block|,
comment|/* class_finalize */
name|NULL
block|,
comment|/* class_data     */
sizeof|sizeof
argument_list|(
name|ControllerLinuxInput
argument_list|)
block|,
literal|0
block|,
comment|/* n_preallocs    */
name|NULL
comment|/* instance_init  */
block|}
decl_stmt|;
name|controller_type
operator|=
name|g_type_module_register_type
argument_list|(
name|module
argument_list|,
name|GIMP_TYPE_CONTROLLER
argument_list|,
literal|"ControllerLinuxInput"
argument_list|,
operator|&
name|controller_info
argument_list|,
literal|0
argument_list|)
expr_stmt|;
block|}
return|return
name|controller_type
return|;
block|}
end_function

begin_function
specifier|static
name|void
DECL|function|linux_input_class_init (ControllerLinuxInputClass * klass)
name|linux_input_class_init
parameter_list|(
name|ControllerLinuxInputClass
modifier|*
name|klass
parameter_list|)
block|{
name|GimpControllerClass
modifier|*
name|controller_class
init|=
name|GIMP_CONTROLLER_CLASS
argument_list|(
name|klass
argument_list|)
decl_stmt|;
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
name|dispose
operator|=
name|linux_input_dispose
expr_stmt|;
name|object_class
operator|->
name|get_property
operator|=
name|linux_input_get_property
expr_stmt|;
name|object_class
operator|->
name|set_property
operator|=
name|linux_input_set_property
expr_stmt|;
name|g_object_class_install_property
argument_list|(
name|object_class
argument_list|,
name|PROP_DEVICE
argument_list|,
name|g_param_spec_string
argument_list|(
literal|"device"
argument_list|,
name|_
argument_list|(
literal|"Device:"
argument_list|)
argument_list|,
name|NULL
argument_list|,
name|NULL
argument_list|,
name|G_PARAM_READWRITE
operator||
name|G_PARAM_CONSTRUCT
operator||
name|GIMP_MODULE_PARAM_SERIALIZE
argument_list|)
argument_list|)
expr_stmt|;
name|controller_class
operator|->
name|name
operator|=
name|_
argument_list|(
literal|"Linux Input Events"
argument_list|)
expr_stmt|;
name|controller_class
operator|->
name|get_n_events
operator|=
name|linux_input_get_n_events
expr_stmt|;
name|controller_class
operator|->
name|get_event_name
operator|=
name|linux_input_get_event_name
expr_stmt|;
name|controller_class
operator|->
name|get_event_blurb
operator|=
name|linux_input_get_event_blurb
expr_stmt|;
block|}
end_function

begin_function
specifier|static
name|void
DECL|function|linux_input_dispose (GObject * object)
name|linux_input_dispose
parameter_list|(
name|GObject
modifier|*
name|object
parameter_list|)
block|{
name|ControllerLinuxInput
modifier|*
name|controller
init|=
name|CONTROLLER_LINUX_INPUT
argument_list|(
name|object
argument_list|)
decl_stmt|;
name|linux_input_set_device
argument_list|(
name|controller
argument_list|,
name|NULL
argument_list|)
expr_stmt|;
name|G_OBJECT_CLASS
argument_list|(
name|parent_class
argument_list|)
operator|->
name|dispose
argument_list|(
name|object
argument_list|)
expr_stmt|;
block|}
end_function

begin_function
specifier|static
name|void
DECL|function|linux_input_set_property (GObject * object,guint property_id,const GValue * value,GParamSpec * pspec)
name|linux_input_set_property
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
name|ControllerLinuxInput
modifier|*
name|controller
init|=
name|CONTROLLER_LINUX_INPUT
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
name|PROP_DEVICE
case|:
name|linux_input_set_device
argument_list|(
name|controller
argument_list|,
name|g_value_get_string
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
DECL|function|linux_input_get_property (GObject * object,guint property_id,GValue * value,GParamSpec * pspec)
name|linux_input_get_property
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
name|ControllerLinuxInput
modifier|*
name|controller
init|=
name|CONTROLLER_LINUX_INPUT
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
name|PROP_DEVICE
case|:
name|g_value_set_string
argument_list|(
name|value
argument_list|,
name|controller
operator|->
name|device
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
name|gint
DECL|function|linux_input_get_n_events (GimpController * controller)
name|linux_input_get_n_events
parameter_list|(
name|GimpController
modifier|*
name|controller
parameter_list|)
block|{
return|return
name|G_N_ELEMENTS
argument_list|(
name|key_events
argument_list|)
operator|+
name|G_N_ELEMENTS
argument_list|(
name|rel_events
argument_list|)
return|;
block|}
end_function

begin_function
specifier|static
specifier|const
name|gchar
modifier|*
DECL|function|linux_input_get_event_name (GimpController * controller,gint event_id)
name|linux_input_get_event_name
parameter_list|(
name|GimpController
modifier|*
name|controller
parameter_list|,
name|gint
name|event_id
parameter_list|)
block|{
if|if
condition|(
name|event_id
operator|<
literal|0
condition|)
block|{
return|return
name|NULL
return|;
block|}
elseif|else
if|if
condition|(
name|event_id
operator|<
name|G_N_ELEMENTS
argument_list|(
name|key_events
argument_list|)
condition|)
block|{
return|return
name|key_events
index|[
name|event_id
index|]
operator|.
name|name
return|;
block|}
elseif|else
if|if
condition|(
name|event_id
operator|<
name|linux_input_get_n_events
argument_list|(
name|controller
argument_list|)
condition|)
block|{
return|return
name|rel_events
index|[
name|event_id
operator|-
name|G_N_ELEMENTS
argument_list|(
name|key_events
argument_list|)
index|]
operator|.
name|name
return|;
block|}
else|else
block|{
return|return
name|NULL
return|;
block|}
block|}
end_function

begin_function
specifier|static
specifier|const
name|gchar
modifier|*
DECL|function|linux_input_get_event_blurb (GimpController * controller,gint event_id)
name|linux_input_get_event_blurb
parameter_list|(
name|GimpController
modifier|*
name|controller
parameter_list|,
name|gint
name|event_id
parameter_list|)
block|{
if|if
condition|(
name|event_id
operator|<
literal|0
condition|)
block|{
return|return
name|NULL
return|;
block|}
elseif|else
if|if
condition|(
name|event_id
operator|<
name|G_N_ELEMENTS
argument_list|(
name|key_events
argument_list|)
condition|)
block|{
return|return
name|gettext
argument_list|(
name|key_events
index|[
name|event_id
index|]
operator|.
name|blurb
argument_list|)
return|;
block|}
elseif|else
if|if
condition|(
name|event_id
operator|<
name|linux_input_get_n_events
argument_list|(
name|controller
argument_list|)
condition|)
block|{
return|return
name|gettext
argument_list|(
name|rel_events
index|[
name|event_id
operator|-
name|G_N_ELEMENTS
argument_list|(
name|key_events
argument_list|)
index|]
operator|.
name|blurb
argument_list|)
return|;
block|}
else|else
block|{
return|return
name|NULL
return|;
block|}
block|}
end_function

begin_function
specifier|static
name|gboolean
DECL|function|linux_input_set_device (ControllerLinuxInput * controller,const gchar * device)
name|linux_input_set_device
parameter_list|(
name|ControllerLinuxInput
modifier|*
name|controller
parameter_list|,
specifier|const
name|gchar
modifier|*
name|device
parameter_list|)
block|{
if|if
condition|(
name|controller
operator|->
name|io
condition|)
block|{
name|g_source_remove
argument_list|(
name|controller
operator|->
name|io_id
argument_list|)
expr_stmt|;
name|controller
operator|->
name|io_id
operator|=
literal|0
expr_stmt|;
name|g_io_channel_unref
argument_list|(
name|controller
operator|->
name|io
argument_list|)
expr_stmt|;
name|controller
operator|->
name|io
operator|=
name|NULL
expr_stmt|;
block|}
if|if
condition|(
name|controller
operator|->
name|device
condition|)
name|g_free
argument_list|(
name|controller
operator|->
name|device
argument_list|)
expr_stmt|;
name|controller
operator|->
name|device
operator|=
name|g_strdup
argument_list|(
name|device
argument_list|)
expr_stmt|;
if|if
condition|(
name|controller
operator|->
name|device
operator|&&
name|strlen
argument_list|(
name|controller
operator|->
name|device
argument_list|)
condition|)
block|{
name|gint
name|fd
decl_stmt|;
name|fd
operator|=
name|open
argument_list|(
name|controller
operator|->
name|device
argument_list|,
name|O_RDONLY
argument_list|)
expr_stmt|;
if|if
condition|(
name|fd
operator|>=
literal|0
condition|)
block|{
name|gchar
name|name
index|[
literal|256
index|]
decl_stmt|;
name|name
index|[
literal|0
index|]
operator|=
literal|'\0'
expr_stmt|;
if|if
condition|(
name|ioctl
argument_list|(
name|fd
argument_list|,
name|EVIOCGNAME
argument_list|(
sizeof|sizeof
argument_list|(
name|name
argument_list|)
argument_list|)
argument_list|,
name|name
argument_list|)
operator|==
literal|0
operator|&&
name|strlen
argument_list|(
name|name
argument_list|)
operator|>
literal|0
operator|&&
name|g_utf8_validate
argument_list|(
name|name
argument_list|,
operator|-
literal|1
argument_list|,
name|NULL
argument_list|)
condition|)
block|{
name|g_object_set
argument_list|(
name|controller
argument_list|,
literal|"name"
argument_list|,
name|name
argument_list|,
name|NULL
argument_list|)
expr_stmt|;
block|}
else|else
block|{
name|gchar
modifier|*
name|name
init|=
name|g_strdup_printf
argument_list|(
name|_
argument_list|(
literal|"Reading from %s"
argument_list|)
argument_list|,
name|controller
operator|->
name|device
argument_list|)
decl_stmt|;
name|g_object_set
argument_list|(
name|controller
argument_list|,
literal|"name"
argument_list|,
name|name
argument_list|,
name|NULL
argument_list|)
expr_stmt|;
name|g_free
argument_list|(
name|name
argument_list|)
expr_stmt|;
block|}
name|controller
operator|->
name|io
operator|=
name|g_io_channel_unix_new
argument_list|(
name|fd
argument_list|)
expr_stmt|;
name|g_io_channel_set_close_on_unref
argument_list|(
name|controller
operator|->
name|io
argument_list|,
name|TRUE
argument_list|)
expr_stmt|;
name|g_io_channel_set_encoding
argument_list|(
name|controller
operator|->
name|io
argument_list|,
name|NULL
argument_list|,
name|NULL
argument_list|)
expr_stmt|;
name|controller
operator|->
name|io_id
operator|=
name|g_io_add_watch
argument_list|(
name|controller
operator|->
name|io
argument_list|,
name|G_IO_IN
argument_list|,
name|linux_input_read_event
argument_list|,
name|controller
argument_list|)
expr_stmt|;
return|return
name|TRUE
return|;
block|}
else|else
block|{
name|gchar
modifier|*
name|name
init|=
name|g_strdup_printf
argument_list|(
name|_
argument_list|(
literal|"Device not available: %s"
argument_list|)
argument_list|,
name|g_strerror
argument_list|(
name|errno
argument_list|)
argument_list|)
decl_stmt|;
name|g_object_set
argument_list|(
name|controller
argument_list|,
literal|"name"
argument_list|,
name|name
argument_list|,
name|NULL
argument_list|)
expr_stmt|;
name|g_free
argument_list|(
name|name
argument_list|)
expr_stmt|;
block|}
block|}
else|else
block|{
name|g_object_set
argument_list|(
name|controller
argument_list|,
literal|"name"
argument_list|,
name|_
argument_list|(
literal|"No device configured"
argument_list|)
argument_list|,
name|NULL
argument_list|)
expr_stmt|;
block|}
return|return
name|FALSE
return|;
block|}
end_function

begin_function
name|gboolean
DECL|function|linux_input_read_event (GIOChannel * io,GIOCondition cond,gpointer data)
name|linux_input_read_event
parameter_list|(
name|GIOChannel
modifier|*
name|io
parameter_list|,
name|GIOCondition
name|cond
parameter_list|,
name|gpointer
name|data
parameter_list|)
block|{
name|struct
name|input_event
name|ev
decl_stmt|;
name|gsize
name|n_bytes
decl_stmt|;
name|gint
name|i
decl_stmt|;
if|if
condition|(
name|g_io_channel_read_chars
argument_list|(
name|io
argument_list|,
operator|(
name|gchar
operator|*
operator|)
operator|&
name|ev
argument_list|,
sizeof|sizeof
argument_list|(
expr|struct
name|input_event
argument_list|)
argument_list|,
operator|&
name|n_bytes
argument_list|,
name|NULL
argument_list|)
operator|==
name|G_IO_STATUS_NORMAL
operator|&&
name|n_bytes
operator|==
sizeof|sizeof
argument_list|(
expr|struct
name|input_event
argument_list|)
condition|)
block|{
switch|switch
condition|(
name|ev
operator|.
name|type
condition|)
block|{
case|case
name|EV_KEY
case|:
for|for
control|(
name|i
operator|=
literal|0
init|;
name|i
operator|<
name|G_N_ELEMENTS
argument_list|(
name|key_events
argument_list|)
condition|;
name|i
operator|++
control|)
if|if
condition|(
name|ev
operator|.
name|code
operator|==
name|key_events
index|[
name|i
index|]
operator|.
name|code
condition|)
block|{
name|GimpController
modifier|*
name|controller
init|=
name|GIMP_CONTROLLER
argument_list|(
name|data
argument_list|)
decl_stmt|;
name|GimpControllerEvent
name|cevent
decl_stmt|;
name|cevent
operator|.
name|any
operator|.
name|type
operator|=
name|GIMP_CONTROLLER_EVENT_TRIGGER
expr_stmt|;
name|cevent
operator|.
name|any
operator|.
name|source
operator|=
name|GIMP_CONTROLLER
argument_list|(
name|data
argument_list|)
expr_stmt|;
name|cevent
operator|.
name|any
operator|.
name|event_id
operator|=
name|i
expr_stmt|;
name|gimp_controller_event
argument_list|(
name|controller
argument_list|,
operator|&
name|cevent
argument_list|)
expr_stmt|;
break|break;
block|}
break|break;
case|case
name|EV_REL
case|:
for|for
control|(
name|i
operator|=
literal|0
init|;
name|i
operator|<
name|G_N_ELEMENTS
argument_list|(
name|rel_events
argument_list|)
condition|;
name|i
operator|++
control|)
if|if
condition|(
name|ev
operator|.
name|code
operator|==
name|rel_events
index|[
name|i
index|]
operator|.
name|code
condition|)
block|{
name|GimpController
modifier|*
name|controller
init|=
name|GIMP_CONTROLLER
argument_list|(
name|data
argument_list|)
decl_stmt|;
name|GimpControllerEvent
name|cevent
decl_stmt|;
name|gint
name|count
decl_stmt|;
name|cevent
operator|.
name|any
operator|.
name|type
operator|=
name|GIMP_CONTROLLER_EVENT_TRIGGER
expr_stmt|;
name|cevent
operator|.
name|any
operator|.
name|source
operator|=
name|controller
expr_stmt|;
name|cevent
operator|.
name|any
operator|.
name|event_id
operator|=
name|G_N_ELEMENTS
argument_list|(
name|key_events
argument_list|)
operator|+
name|i
expr_stmt|;
for|for
control|(
name|count
operator|=
name|ev
operator|.
name|value
init|;
name|count
operator|<
literal|0
condition|;
name|count
operator|++
control|)
name|gimp_controller_event
argument_list|(
name|controller
argument_list|,
operator|&
name|cevent
argument_list|)
expr_stmt|;
name|cevent
operator|.
name|any
operator|.
name|event_id
operator|++
expr_stmt|;
for|for
control|(
name|count
operator|=
name|ev
operator|.
name|value
init|;
name|count
operator|>
literal|0
condition|;
name|count
operator|--
control|)
name|gimp_controller_event
argument_list|(
name|controller
argument_list|,
operator|&
name|cevent
argument_list|)
expr_stmt|;
break|break;
block|}
break|break;
default|default:
break|break;
block|}
block|}
return|return
name|TRUE
return|;
block|}
end_function

end_unit

