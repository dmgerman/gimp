begin_unit|revision:0.9.5;language:C;cregit-version:0.0.1
begin_comment
comment|/* LIBGIMP - The GIMP Library  * Copyright (C) 1995-1997 Peter Mattis and Spencer Kimball  *  * controller_midi.c  * Copyright (C) 2004 Michael Natterer<mitch@gimp.org>  *  * This library is free software; you can redistribute it and/or  * modify it under the terms of the GNU Lesser General Public  * License as published by the Free Software Foundation; either  * version 2 of the License, or (at your option) any later version.  *  * This library is distributed in the hope that it will be useful,  * but WITHOUT ANY WARRANTY; without even the implied warranty of  * MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the GNU  * Lesser General Public License for more details.  *  * You should have received a copy of the GNU Lesser General Public  * License along with this library; if not, write to the  * Free Software Foundation, Inc., 59 Temple Place - Suite 330,  * Boston, MA 02111-1307, USA.  */
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
file|<fcntl.h>
end_include

begin_include
include|#
directive|include
file|<string.h>
end_include

begin_include
include|#
directive|include
file|<sys/stat.h>
end_include

begin_include
include|#
directive|include
file|<sys/types.h>
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
DECL|struct|__anon289941490108
block|{
DECL|member|name
name|gchar
modifier|*
name|name
decl_stmt|;
DECL|member|blurb
name|gchar
modifier|*
name|blurb
decl_stmt|;
DECL|typedef|MidiEvent
block|}
name|MidiEvent
typedef|;
end_typedef

begin_enum
enum|enum
DECL|enum|__anon289941490203
block|{
DECL|enumerator|PROP_0
name|PROP_0
block|,
DECL|enumerator|PROP_DEVICE
name|PROP_DEVICE
block|,
DECL|enumerator|PROP_CHANNEL
name|PROP_CHANNEL
block|}
enum|;
end_enum

begin_define
DECL|macro|CONTROLLER_TYPE_MIDI
define|#
directive|define
name|CONTROLLER_TYPE_MIDI
value|(controller_type)
end_define

begin_define
DECL|macro|CONTROLLER_MIDI (obj)
define|#
directive|define
name|CONTROLLER_MIDI
parameter_list|(
name|obj
parameter_list|)
value|(G_TYPE_CHECK_INSTANCE_CAST ((obj), CONTROLLER_TYPE_MIDI, ControllerMidi))
end_define

begin_define
DECL|macro|CONTROLLER_MIDI_CLASS (klass)
define|#
directive|define
name|CONTROLLER_MIDI_CLASS
parameter_list|(
name|klass
parameter_list|)
value|(G_TYPE_CHECK_CLASS_CAST ((klass), CONTROLLER_TYPE_MIDI, ControllerMidiClass))
end_define

begin_define
DECL|macro|CONTROLLER_IS_MIDI (obj)
define|#
directive|define
name|CONTROLLER_IS_MIDI
parameter_list|(
name|obj
parameter_list|)
value|(G_TYPE_CHECK_INSTANCE_TYPE ((obj), CONTROLLER_TYPE_MIDI))
end_define

begin_define
DECL|macro|CONTROLLER_IS_MIDI_CLASS (klass)
define|#
directive|define
name|CONTROLLER_IS_MIDI_CLASS
parameter_list|(
name|klass
parameter_list|)
value|(G_TYPE_CHECK_CLASS_TYPE ((klass), CONTROLLER_TYPE_MIDI))
end_define

begin_typedef
DECL|typedef|ControllerMidi
typedef|typedef
name|struct
name|_ControllerMidi
name|ControllerMidi
typedef|;
end_typedef

begin_typedef
DECL|typedef|ControllerMidiClass
typedef|typedef
name|struct
name|_ControllerMidiClass
name|ControllerMidiClass
typedef|;
end_typedef

begin_struct
DECL|struct|_ControllerMidi
struct|struct
name|_ControllerMidi
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
DECL|member|midi_channel
name|gint
name|midi_channel
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
comment|/* midi status */
DECL|member|swallow
name|gboolean
name|swallow
decl_stmt|;
DECL|member|command
name|gint
name|command
decl_stmt|;
DECL|member|channel
name|gint
name|channel
decl_stmt|;
DECL|member|key
name|gint
name|key
decl_stmt|;
DECL|member|velocity
name|gint
name|velocity
decl_stmt|;
DECL|member|msb
name|gint
name|msb
decl_stmt|;
DECL|member|lsb
name|gint
name|lsb
decl_stmt|;
block|}
struct|;
end_struct

begin_struct
DECL|struct|_ControllerMidiClass
struct|struct
name|_ControllerMidiClass
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
name|midi_get_type
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
name|midi_class_init
parameter_list|(
name|ControllerMidiClass
modifier|*
name|klass
parameter_list|)
function_decl|;
end_function_decl

begin_function_decl
specifier|static
name|void
name|midi_init
parameter_list|(
name|ControllerMidi
modifier|*
name|midi
parameter_list|)
function_decl|;
end_function_decl

begin_function_decl
specifier|static
name|void
name|midi_dispose
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
name|midi_set_property
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
name|midi_get_property
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
name|midi_get_n_events
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
name|midi_get_event_name
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
name|midi_get_event_blurb
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
name|midi_set_device
parameter_list|(
name|ControllerMidi
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
name|void
name|midi_event
parameter_list|(
name|ControllerMidi
modifier|*
name|midi
parameter_list|,
name|gint
name|channel
parameter_list|,
name|gint
name|event_id
parameter_list|,
name|gdouble
name|value
parameter_list|)
function_decl|;
end_function_decl

begin_function_decl
specifier|static
name|gboolean
name|midi_read_event
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
DECL|variable|midi_info
specifier|static
specifier|const
name|GimpModuleInfo
name|midi_info
init|=
block|{
name|GIMP_MODULE_ABI_VERSION
block|,
name|N_
argument_list|(
literal|"Midi event controller"
argument_list|)
block|,
literal|"Michael Natterer<mitch@gimp.org>"
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

begin_decl_stmt
DECL|variable|midi_events
specifier|static
name|MidiEvent
name|midi_events
index|[
literal|128
operator|+
literal|128
operator|+
literal|128
index|]
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
name|midi_info
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
name|midi_get_type
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
DECL|function|midi_get_type (GTypeModule * module)
name|midi_get_type
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
name|ControllerMidiClass
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
name|midi_class_init
block|,
name|NULL
block|,
comment|/* class_finalize */
name|NULL
block|,
comment|/* class_data     */
sizeof|sizeof
argument_list|(
name|ControllerMidi
argument_list|)
block|,
literal|0
block|,
comment|/* n_preallocs    */
operator|(
name|GInstanceInitFunc
operator|)
name|midi_init
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
literal|"ControllerMidi"
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
DECL|function|midi_class_init (ControllerMidiClass * klass)
name|midi_class_init
parameter_list|(
name|ControllerMidiClass
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
name|midi_dispose
expr_stmt|;
name|object_class
operator|->
name|get_property
operator|=
name|midi_get_property
expr_stmt|;
name|object_class
operator|->
name|set_property
operator|=
name|midi_set_property
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
name|_
argument_list|(
literal|"The name of the device to read MIDI events from."
argument_list|)
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
name|g_object_class_install_property
argument_list|(
name|object_class
argument_list|,
name|PROP_CHANNEL
argument_list|,
name|g_param_spec_int
argument_list|(
literal|"channel"
argument_list|,
name|_
argument_list|(
literal|"Channel:"
argument_list|)
argument_list|,
name|_
argument_list|(
literal|"The MIDI channel to read events from. Set to -1 for reading from all MIDI channels."
argument_list|)
argument_list|,
operator|-
literal|1
argument_list|,
literal|15
argument_list|,
operator|-
literal|1
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
literal|"Midi Events"
argument_list|)
expr_stmt|;
name|controller_class
operator|->
name|get_n_events
operator|=
name|midi_get_n_events
expr_stmt|;
name|controller_class
operator|->
name|get_event_name
operator|=
name|midi_get_event_name
expr_stmt|;
name|controller_class
operator|->
name|get_event_blurb
operator|=
name|midi_get_event_blurb
expr_stmt|;
block|}
end_function

begin_function
specifier|static
name|void
DECL|function|midi_init (ControllerMidi * midi)
name|midi_init
parameter_list|(
name|ControllerMidi
modifier|*
name|midi
parameter_list|)
block|{
name|midi
operator|->
name|device
operator|=
name|NULL
expr_stmt|;
name|midi
operator|->
name|midi_channel
operator|=
operator|-
literal|1
expr_stmt|;
name|midi
operator|->
name|io
operator|=
name|NULL
expr_stmt|;
name|midi
operator|->
name|io_id
operator|=
literal|0
expr_stmt|;
name|midi
operator|->
name|swallow
operator|=
name|TRUE
expr_stmt|;
comment|/* get rid of data bytes at start of stream */
name|midi
operator|->
name|command
operator|=
literal|0x0
expr_stmt|;
name|midi
operator|->
name|channel
operator|=
literal|0x0
expr_stmt|;
name|midi
operator|->
name|key
operator|=
operator|-
literal|1
expr_stmt|;
name|midi
operator|->
name|velocity
operator|=
operator|-
literal|1
expr_stmt|;
name|midi
operator|->
name|msb
operator|=
operator|-
literal|1
expr_stmt|;
name|midi
operator|->
name|lsb
operator|=
operator|-
literal|1
expr_stmt|;
block|}
end_function

begin_function
specifier|static
name|void
DECL|function|midi_dispose (GObject * object)
name|midi_dispose
parameter_list|(
name|GObject
modifier|*
name|object
parameter_list|)
block|{
name|ControllerMidi
modifier|*
name|midi
init|=
name|CONTROLLER_MIDI
argument_list|(
name|object
argument_list|)
decl_stmt|;
name|midi_set_device
argument_list|(
name|midi
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
DECL|function|midi_set_property (GObject * object,guint property_id,const GValue * value,GParamSpec * pspec)
name|midi_set_property
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
name|ControllerMidi
modifier|*
name|midi
init|=
name|CONTROLLER_MIDI
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
name|midi_set_device
argument_list|(
name|midi
argument_list|,
name|g_value_get_string
argument_list|(
name|value
argument_list|)
argument_list|)
expr_stmt|;
break|break;
case|case
name|PROP_CHANNEL
case|:
name|midi
operator|->
name|midi_channel
operator|=
name|g_value_get_int
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
DECL|function|midi_get_property (GObject * object,guint property_id,GValue * value,GParamSpec * pspec)
name|midi_get_property
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
name|ControllerMidi
modifier|*
name|midi
init|=
name|CONTROLLER_MIDI
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
name|midi
operator|->
name|device
argument_list|)
expr_stmt|;
break|break;
case|case
name|PROP_CHANNEL
case|:
name|g_value_set_int
argument_list|(
name|value
argument_list|,
name|midi
operator|->
name|midi_channel
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
DECL|function|midi_get_n_events (GimpController * controller)
name|midi_get_n_events
parameter_list|(
name|GimpController
modifier|*
name|controller
parameter_list|)
block|{
return|return
literal|128
operator|+
literal|128
operator|+
literal|128
return|;
block|}
end_function

begin_function
specifier|static
specifier|const
name|gchar
modifier|*
DECL|function|midi_get_event_name (GimpController * controller,gint event_id)
name|midi_get_event_name
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
operator|(
literal|128
operator|+
literal|128
operator|+
literal|128
operator|)
condition|)
block|{
if|if
condition|(
operator|!
name|midi_events
index|[
name|event_id
index|]
operator|.
name|name
condition|)
block|{
if|if
condition|(
name|event_id
operator|<
literal|128
condition|)
name|midi_events
index|[
name|event_id
index|]
operator|.
name|name
operator|=
name|g_strdup_printf
argument_list|(
literal|"note-on-%02x"
argument_list|,
name|event_id
argument_list|)
expr_stmt|;
elseif|else
if|if
condition|(
name|event_id
operator|<
operator|(
literal|128
operator|+
literal|128
operator|)
condition|)
name|midi_events
index|[
name|event_id
index|]
operator|.
name|name
operator|=
name|g_strdup_printf
argument_list|(
literal|"note-off-%02x"
argument_list|,
name|event_id
operator|-
literal|128
argument_list|)
expr_stmt|;
elseif|else
if|if
condition|(
name|event_id
operator|<
operator|(
literal|128
operator|+
literal|128
operator|+
literal|128
operator|)
condition|)
name|midi_events
index|[
name|event_id
index|]
operator|.
name|name
operator|=
name|g_strdup_printf
argument_list|(
literal|"controller-%03d"
argument_list|,
name|event_id
operator|-
literal|256
argument_list|)
expr_stmt|;
block|}
return|return
name|midi_events
index|[
name|event_id
index|]
operator|.
name|name
return|;
block|}
return|return
name|NULL
return|;
block|}
end_function

begin_function
specifier|static
specifier|const
name|gchar
modifier|*
DECL|function|midi_get_event_blurb (GimpController * controller,gint event_id)
name|midi_get_event_blurb
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
operator|<=
literal|383
condition|)
block|{
if|if
condition|(
operator|!
name|midi_events
index|[
name|event_id
index|]
operator|.
name|blurb
condition|)
block|{
if|if
condition|(
name|event_id
operator|<=
literal|127
condition|)
name|midi_events
index|[
name|event_id
index|]
operator|.
name|blurb
operator|=
name|g_strdup_printf
argument_list|(
literal|"Note %02x on"
argument_list|,
name|event_id
argument_list|)
expr_stmt|;
elseif|else
if|if
condition|(
name|event_id
operator|<=
literal|255
condition|)
name|midi_events
index|[
name|event_id
index|]
operator|.
name|blurb
operator|=
name|g_strdup_printf
argument_list|(
literal|"Note %02x off"
argument_list|,
name|event_id
operator|-
literal|128
argument_list|)
expr_stmt|;
elseif|else
if|if
condition|(
name|event_id
operator|<=
literal|383
condition|)
name|midi_events
index|[
name|event_id
index|]
operator|.
name|blurb
operator|=
name|g_strdup_printf
argument_list|(
literal|"Controller %03d"
argument_list|,
name|event_id
operator|-
literal|256
argument_list|)
expr_stmt|;
block|}
return|return
name|midi_events
index|[
name|event_id
index|]
operator|.
name|blurb
return|;
block|}
return|return
name|NULL
return|;
block|}
end_function

begin_function
specifier|static
name|gboolean
DECL|function|midi_set_device (ControllerMidi * midi,const gchar * device)
name|midi_set_device
parameter_list|(
name|ControllerMidi
modifier|*
name|midi
parameter_list|,
specifier|const
name|gchar
modifier|*
name|device
parameter_list|)
block|{
name|midi
operator|->
name|swallow
operator|=
name|TRUE
expr_stmt|;
name|midi
operator|->
name|command
operator|=
literal|0x0
expr_stmt|;
name|midi
operator|->
name|channel
operator|=
literal|0x0
expr_stmt|;
name|midi
operator|->
name|key
operator|=
operator|-
literal|1
expr_stmt|;
name|midi
operator|->
name|velocity
operator|=
operator|-
literal|1
expr_stmt|;
name|midi
operator|->
name|msb
operator|=
operator|-
literal|1
expr_stmt|;
name|midi
operator|->
name|lsb
operator|=
operator|-
literal|1
expr_stmt|;
if|if
condition|(
name|midi
operator|->
name|io
condition|)
block|{
name|g_source_remove
argument_list|(
name|midi
operator|->
name|io_id
argument_list|)
expr_stmt|;
name|midi
operator|->
name|io_id
operator|=
literal|0
expr_stmt|;
name|g_io_channel_unref
argument_list|(
name|midi
operator|->
name|io
argument_list|)
expr_stmt|;
name|midi
operator|->
name|io
operator|=
name|NULL
expr_stmt|;
block|}
if|if
condition|(
name|midi
operator|->
name|device
condition|)
name|g_free
argument_list|(
name|midi
operator|->
name|device
argument_list|)
expr_stmt|;
name|midi
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
name|midi
operator|->
name|device
operator|&&
name|strlen
argument_list|(
name|midi
operator|->
name|device
argument_list|)
condition|)
block|{
name|gint
name|fd
decl_stmt|;
ifdef|#
directive|ifdef
name|G_OS_WIN32
name|fd
operator|=
name|open
argument_list|(
name|midi
operator|->
name|device
argument_list|,
name|O_RDONLY
argument_list|)
expr_stmt|;
else|#
directive|else
name|fd
operator|=
name|open
argument_list|(
name|midi
operator|->
name|device
argument_list|,
name|O_RDONLY
operator||
name|O_NONBLOCK
argument_list|)
expr_stmt|;
endif|#
directive|endif
if|if
condition|(
name|fd
operator|>=
literal|0
condition|)
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
name|midi
operator|->
name|device
argument_list|)
decl_stmt|;
name|g_object_set
argument_list|(
name|midi
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
name|midi
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
name|midi
operator|->
name|io
argument_list|,
name|TRUE
argument_list|)
expr_stmt|;
name|g_io_channel_set_encoding
argument_list|(
name|midi
operator|->
name|io
argument_list|,
name|NULL
argument_list|,
name|NULL
argument_list|)
expr_stmt|;
name|midi
operator|->
name|io_id
operator|=
name|g_io_add_watch
argument_list|(
name|midi
operator|->
name|io
argument_list|,
name|G_IO_IN
operator||
name|G_IO_ERR
operator||
name|G_IO_HUP
operator||
name|G_IO_NVAL
argument_list|,
name|midi_read_event
argument_list|,
name|midi
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
name|midi
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
name|midi
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
specifier|static
name|void
DECL|function|midi_event (ControllerMidi * midi,gint channel,gint event_id,gdouble value)
name|midi_event
parameter_list|(
name|ControllerMidi
modifier|*
name|midi
parameter_list|,
name|gint
name|channel
parameter_list|,
name|gint
name|event_id
parameter_list|,
name|gdouble
name|value
parameter_list|)
block|{
if|if
condition|(
name|channel
operator|==
operator|-
literal|1
operator|||
name|midi
operator|->
name|midi_channel
operator|==
operator|-
literal|1
operator|||
name|channel
operator|==
name|midi
operator|->
name|midi_channel
condition|)
block|{
name|GimpControllerEvent
name|event
init|=
block|{
literal|0
block|, }
decl_stmt|;
name|event
operator|.
name|any
operator|.
name|type
operator|=
name|GIMP_CONTROLLER_EVENT_VALUE
expr_stmt|;
name|event
operator|.
name|any
operator|.
name|source
operator|=
name|GIMP_CONTROLLER
argument_list|(
name|midi
argument_list|)
expr_stmt|;
name|event
operator|.
name|any
operator|.
name|event_id
operator|=
name|event_id
expr_stmt|;
name|g_value_init
argument_list|(
operator|&
name|event
operator|.
name|value
operator|.
name|value
argument_list|,
name|G_TYPE_DOUBLE
argument_list|)
expr_stmt|;
name|g_value_set_double
argument_list|(
operator|&
name|event
operator|.
name|value
operator|.
name|value
argument_list|,
name|value
argument_list|)
expr_stmt|;
name|gimp_controller_event
argument_list|(
name|GIMP_CONTROLLER
argument_list|(
name|midi
argument_list|)
argument_list|,
operator|&
name|event
argument_list|)
expr_stmt|;
name|g_value_unset
argument_list|(
operator|&
name|event
operator|.
name|value
operator|.
name|value
argument_list|)
expr_stmt|;
block|}
block|}
end_function

begin_define
DECL|macro|D (stmnt)
define|#
directive|define
name|D
parameter_list|(
name|stmnt
parameter_list|)
value|stmnt;
end_define

begin_function
name|gboolean
DECL|function|midi_read_event (GIOChannel * io,GIOCondition cond,gpointer data)
name|midi_read_event
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
name|ControllerMidi
modifier|*
name|midi
init|=
name|CONTROLLER_MIDI
argument_list|(
name|data
argument_list|)
decl_stmt|;
name|GIOStatus
name|status
decl_stmt|;
name|GError
modifier|*
name|error
init|=
name|NULL
decl_stmt|;
name|guchar
name|buf
index|[
literal|0xf
index|]
decl_stmt|;
name|gsize
name|size
decl_stmt|;
name|gint
name|pos
init|=
literal|0
decl_stmt|;
name|status
operator|=
name|g_io_channel_read_chars
argument_list|(
name|io
argument_list|,
operator|(
name|gchar
operator|*
operator|)
name|buf
argument_list|,
sizeof|sizeof
argument_list|(
name|buf
argument_list|)
argument_list|,
operator|&
name|size
argument_list|,
operator|&
name|error
argument_list|)
expr_stmt|;
switch|switch
condition|(
name|status
condition|)
block|{
case|case
name|G_IO_STATUS_ERROR
case|:
case|case
name|G_IO_STATUS_EOF
case|:
name|g_source_remove
argument_list|(
name|midi
operator|->
name|io_id
argument_list|)
expr_stmt|;
name|midi
operator|->
name|io_id
operator|=
literal|0
expr_stmt|;
name|g_io_channel_unref
argument_list|(
name|midi
operator|->
name|io
argument_list|)
expr_stmt|;
name|midi
operator|->
name|io
operator|=
name|NULL
expr_stmt|;
if|if
condition|(
name|error
condition|)
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
name|error
operator|->
name|message
argument_list|)
decl_stmt|;
name|g_object_set
argument_list|(
name|midi
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
name|g_clear_error
argument_list|(
operator|&
name|error
argument_list|)
expr_stmt|;
block|}
else|else
block|{
name|g_object_set
argument_list|(
name|midi
argument_list|,
literal|"name"
argument_list|,
name|_
argument_list|(
literal|"End of file"
argument_list|)
argument_list|,
name|NULL
argument_list|)
expr_stmt|;
block|}
return|return
name|FALSE
return|;
break|break;
case|case
name|G_IO_STATUS_AGAIN
case|:
return|return
name|TRUE
return|;
default|default:
break|break;
block|}
while|while
condition|(
name|pos
operator|<
name|size
condition|)
block|{
if|#
directive|if
literal|0
block|gint i;        g_print ("MIDI IN (%d bytes), command 0x%02x: ", size, midi->command);        for (i = 0; i< size; i++)         g_print ("%02x ", buf[i]);       g_print ("\n");
endif|#
directive|endif
if|if
condition|(
name|buf
index|[
name|pos
index|]
operator|&
literal|0x80
condition|)
comment|/* status byte */
block|{
if|if
condition|(
name|buf
index|[
name|pos
index|]
operator|>=
literal|0xf8
condition|)
comment|/* realtime messages */
block|{
switch|switch
condition|(
name|buf
index|[
name|pos
index|]
condition|)
block|{
case|case
literal|0xf8
case|:
comment|/* timing clock   */
case|case
literal|0xf9
case|:
comment|/* (undefined)    */
case|case
literal|0xfa
case|:
comment|/* start          */
case|case
literal|0xfb
case|:
comment|/* continue       */
case|case
literal|0xfc
case|:
comment|/* stop           */
case|case
literal|0xfd
case|:
comment|/* (undefined)    */
case|case
literal|0xfe
case|:
comment|/* active sensing */
case|case
literal|0xff
case|:
comment|/* system reset   */
comment|/* nop */
if|#
directive|if
literal|0
block|g_print ("MIDI: realtime message (%02x)\n", buf[pos]);
endif|#
directive|endif
break|break;
block|}
block|}
else|else
block|{
name|midi
operator|->
name|swallow
operator|=
name|FALSE
expr_stmt|;
comment|/* any status bytes ends swallowing */
if|if
condition|(
name|buf
index|[
name|pos
index|]
operator|>=
literal|0xf0
condition|)
comment|/* system messages */
block|{
switch|switch
condition|(
name|buf
index|[
name|pos
index|]
condition|)
block|{
case|case
literal|0xf0
case|:
comment|/* sysex start */
name|midi
operator|->
name|swallow
operator|=
name|TRUE
expr_stmt|;
name|D
argument_list|(
name|g_print
argument_list|(
literal|"MIDI: sysex start\n"
argument_list|)
argument_list|)
expr_stmt|;
break|break;
case|case
literal|0xf1
case|:
comment|/* time code   */
name|midi
operator|->
name|swallow
operator|=
name|TRUE
expr_stmt|;
comment|/* type + data */
name|D
argument_list|(
name|g_print
argument_list|(
literal|"MIDI: time code\n"
argument_list|)
argument_list|)
expr_stmt|;
break|break;
case|case
literal|0xf2
case|:
comment|/* song position */
name|midi
operator|->
name|swallow
operator|=
name|TRUE
expr_stmt|;
comment|/* lsb + msb     */
name|D
argument_list|(
name|g_print
argument_list|(
literal|"MIDI: song position\n"
argument_list|)
argument_list|)
expr_stmt|;
break|break;
case|case
literal|0xf3
case|:
comment|/* song select */
name|midi
operator|->
name|swallow
operator|=
name|TRUE
expr_stmt|;
comment|/* song number */
name|D
argument_list|(
name|g_print
argument_list|(
literal|"MIDI: song select\n"
argument_list|)
argument_list|)
expr_stmt|;
break|break;
case|case
literal|0xf4
case|:
comment|/* (undefined) */
case|case
literal|0xf5
case|:
comment|/* (undefined) */
name|D
argument_list|(
name|g_print
argument_list|(
literal|"MIDI: undefined system message\n"
argument_list|)
argument_list|)
expr_stmt|;
break|break;
case|case
literal|0xf6
case|:
comment|/* tune request */
name|D
argument_list|(
name|g_print
argument_list|(
literal|"MIDI: tune request\n"
argument_list|)
argument_list|)
expr_stmt|;
break|break;
case|case
literal|0xf7
case|:
comment|/* sysex end */
name|D
argument_list|(
name|g_print
argument_list|(
literal|"MIDI: sysex end\n"
argument_list|)
argument_list|)
expr_stmt|;
break|break;
block|}
block|}
else|else
comment|/* channel messages */
block|{
name|midi
operator|->
name|command
operator|=
name|buf
index|[
name|pos
index|]
operator|>>
literal|4
expr_stmt|;
name|midi
operator|->
name|channel
operator|=
name|buf
index|[
name|pos
index|]
operator|&
literal|0xf
expr_stmt|;
comment|/* reset running status */
name|midi
operator|->
name|key
operator|=
operator|-
literal|1
expr_stmt|;
name|midi
operator|->
name|velocity
operator|=
operator|-
literal|1
expr_stmt|;
name|midi
operator|->
name|msb
operator|=
operator|-
literal|1
expr_stmt|;
name|midi
operator|->
name|lsb
operator|=
operator|-
literal|1
expr_stmt|;
block|}
block|}
name|pos
operator|++
expr_stmt|;
comment|/* status byte consumed */
continue|continue;
block|}
if|if
condition|(
name|midi
operator|->
name|swallow
condition|)
block|{
name|pos
operator|++
expr_stmt|;
comment|/* consume any data byte */
continue|continue;
block|}
switch|switch
condition|(
name|midi
operator|->
name|command
condition|)
block|{
case|case
literal|0x8
case|:
comment|/* note off   */
case|case
literal|0x9
case|:
comment|/* note on    */
case|case
literal|0xa
case|:
comment|/* aftertouch */
if|if
condition|(
name|midi
operator|->
name|key
operator|==
operator|-
literal|1
condition|)
block|{
name|midi
operator|->
name|key
operator|=
name|buf
index|[
name|pos
operator|++
index|]
expr_stmt|;
comment|/* key byte consumed */
continue|continue;
block|}
if|if
condition|(
name|midi
operator|->
name|velocity
operator|==
operator|-
literal|1
condition|)
name|midi
operator|->
name|velocity
operator|=
name|buf
index|[
name|pos
operator|++
index|]
expr_stmt|;
comment|/* velocity byte consumed */
comment|/* note on with velocity = 0 means note off */
if|if
condition|(
name|midi
operator|->
name|command
operator|==
literal|0x9
operator|&&
name|midi
operator|->
name|velocity
operator|==
literal|0x0
condition|)
name|midi
operator|->
name|command
operator|=
literal|0x8
expr_stmt|;
if|if
condition|(
name|midi
operator|->
name|command
operator|==
literal|0x9
condition|)
block|{
name|D
argument_list|(
name|g_print
argument_list|(
literal|"MIDI (ch %02d): note on  (%02x vel %02x)\n"
argument_list|,
name|midi
operator|->
name|channel
argument_list|,
name|midi
operator|->
name|key
argument_list|,
name|midi
operator|->
name|velocity
argument_list|)
argument_list|)
expr_stmt|;
name|midi_event
argument_list|(
name|midi
argument_list|,
name|midi
operator|->
name|channel
argument_list|,
name|midi
operator|->
name|key
argument_list|,
operator|(
name|gdouble
operator|)
name|midi
operator|->
name|velocity
operator|/
literal|127.0
argument_list|)
expr_stmt|;
block|}
elseif|else
if|if
condition|(
name|midi
operator|->
name|command
operator|==
literal|0x8
condition|)
block|{
name|D
argument_list|(
name|g_print
argument_list|(
literal|"MIDI (ch %02d): note off (%02x vel %02x)\n"
argument_list|,
name|midi
operator|->
name|channel
argument_list|,
name|midi
operator|->
name|key
argument_list|,
name|midi
operator|->
name|velocity
argument_list|)
argument_list|)
expr_stmt|;
name|midi_event
argument_list|(
name|midi
argument_list|,
name|midi
operator|->
name|channel
argument_list|,
name|midi
operator|->
name|key
operator|+
literal|128
argument_list|,
operator|(
name|gdouble
operator|)
name|midi
operator|->
name|velocity
operator|/
literal|127.0
argument_list|)
expr_stmt|;
block|}
else|else
block|{
name|D
argument_list|(
name|g_print
argument_list|(
literal|"MIDI (ch %02d): polyphonic aftertouch (%02x pressure %02x)\n"
argument_list|,
name|midi
operator|->
name|channel
argument_list|,
name|midi
operator|->
name|key
argument_list|,
name|midi
operator|->
name|velocity
argument_list|)
argument_list|)
expr_stmt|;
block|}
name|midi
operator|->
name|key
operator|=
operator|-
literal|1
expr_stmt|;
name|midi
operator|->
name|velocity
operator|=
operator|-
literal|1
expr_stmt|;
break|break;
case|case
literal|0xb
case|:
comment|/* controllers, sustain */
if|if
condition|(
name|midi
operator|->
name|key
operator|==
operator|-
literal|1
condition|)
block|{
name|midi
operator|->
name|key
operator|=
name|buf
index|[
name|pos
operator|++
index|]
expr_stmt|;
continue|continue;
block|}
if|if
condition|(
name|midi
operator|->
name|velocity
operator|==
operator|-
literal|1
condition|)
name|midi
operator|->
name|velocity
operator|=
name|buf
index|[
name|pos
operator|++
index|]
expr_stmt|;
name|D
argument_list|(
name|g_print
argument_list|(
literal|"MIDI (ch %02d): controller %d (value %d)\n"
argument_list|,
name|midi
operator|->
name|channel
argument_list|,
name|midi
operator|->
name|key
argument_list|,
name|midi
operator|->
name|velocity
argument_list|)
argument_list|)
expr_stmt|;
name|midi_event
argument_list|(
name|midi
argument_list|,
name|midi
operator|->
name|channel
argument_list|,
name|midi
operator|->
name|key
operator|+
literal|128
operator|+
literal|128
argument_list|,
operator|(
name|gdouble
operator|)
name|midi
operator|->
name|velocity
operator|/
literal|127.0
argument_list|)
expr_stmt|;
name|midi
operator|->
name|key
operator|=
operator|-
literal|1
expr_stmt|;
name|midi
operator|->
name|velocity
operator|=
operator|-
literal|1
expr_stmt|;
break|break;
case|case
literal|0xc
case|:
comment|/* program change */
name|midi
operator|->
name|key
operator|=
name|buf
index|[
name|pos
operator|++
index|]
expr_stmt|;
name|D
argument_list|(
name|g_print
argument_list|(
literal|"MIDI (ch %02d): program change (%d)\n"
argument_list|,
name|midi
operator|->
name|channel
argument_list|,
name|midi
operator|->
name|key
argument_list|)
argument_list|)
expr_stmt|;
name|midi
operator|->
name|key
operator|=
operator|-
literal|1
expr_stmt|;
break|break;
case|case
literal|0xd
case|:
comment|/* channel key pressure */
name|midi
operator|->
name|velocity
operator|=
name|buf
index|[
name|pos
operator|++
index|]
expr_stmt|;
name|D
argument_list|(
name|g_print
argument_list|(
literal|"MIDI (ch %02d): channel aftertouch (%d)\n"
argument_list|,
name|midi
operator|->
name|channel
argument_list|,
name|midi
operator|->
name|velocity
argument_list|)
argument_list|)
expr_stmt|;
name|midi
operator|->
name|velocity
operator|=
operator|-
literal|1
expr_stmt|;
break|break;
case|case
literal|0xe
case|:
comment|/* pitch bend */
if|if
condition|(
name|midi
operator|->
name|lsb
operator|==
operator|-
literal|1
condition|)
block|{
name|midi
operator|->
name|lsb
operator|=
name|buf
index|[
name|pos
operator|++
index|]
expr_stmt|;
continue|continue;
block|}
if|if
condition|(
name|midi
operator|->
name|msb
operator|==
operator|-
literal|1
condition|)
name|midi
operator|->
name|msb
operator|=
name|buf
index|[
name|pos
operator|++
index|]
expr_stmt|;
name|midi
operator|->
name|velocity
operator|=
name|midi
operator|->
name|lsb
operator||
operator|(
name|midi
operator|->
name|msb
operator|<<
literal|7
operator|)
expr_stmt|;
name|D
argument_list|(
name|g_print
argument_list|(
literal|"MIDI (ch %02d): pitch (%d)\n"
argument_list|,
name|midi
operator|->
name|channel
argument_list|,
name|midi
operator|->
name|velocity
argument_list|)
argument_list|)
expr_stmt|;
name|midi
operator|->
name|msb
operator|=
operator|-
literal|1
expr_stmt|;
name|midi
operator|->
name|lsb
operator|=
operator|-
literal|1
expr_stmt|;
name|midi
operator|->
name|velocity
operator|=
operator|-
literal|1
expr_stmt|;
break|break;
block|}
block|}
return|return
name|TRUE
return|;
block|}
end_function

end_unit

