begin_unit|revision:0.9.5;language:C;cregit-version:0.0.1
begin_comment
comment|/* LIBGIMP - The GIMP Library  * Copyright (C) 1995-1997 Peter Mattis and Spencer Kimball  *  * gimpcolordisplay.c  * Copyright (C) 2002 Michael Natterer<mitch@gimp.org>  *  * This library is free software: you can redistribute it and/or  * modify it under the terms of the GNU Lesser General Public  * License as published by the Free Software Foundation; either  * version 3 of the License, or (at your option) any later version.  *  * This library is distributed in the hope that it will be useful,  * but WITHOUT ANY WARRANTY; without even the implied warranty of  * MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the GNU  * Lesser General Public License for more details.  *  * You should have received a copy of the GNU Lesser General Public  * License along with this library.  If not, see  *<https://www.gnu.org/licenses/>.  */
end_comment

begin_include
include|#
directive|include
file|"config.h"
end_include

begin_include
include|#
directive|include
file|<string.h>
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
file|"gimpcolordisplay.h"
end_include

begin_include
include|#
directive|include
file|"gimpicons.h"
end_include

begin_comment
comment|/**  * SECTION: gimpcolordisplay  * @title: GimpColorDisplay  * @short_description: Pluggable GIMP display color correction modules.  * @see_also: #GModule, #GTypeModule, #GimpModule  *  * Functions and definitions for creating pluggable GIMP  * display color correction modules.  **/
end_comment

begin_enum
enum|enum
DECL|enum|__anon275d2b090103
block|{
DECL|enumerator|PROP_0
name|PROP_0
block|,
DECL|enumerator|PROP_ENABLED
name|PROP_ENABLED
block|,
DECL|enumerator|PROP_COLOR_CONFIG
name|PROP_COLOR_CONFIG
block|,
DECL|enumerator|PROP_COLOR_MANAGED
name|PROP_COLOR_MANAGED
block|}
enum|;
end_enum

begin_enum
enum|enum
DECL|enum|__anon275d2b090203
block|{
DECL|enumerator|CHANGED
name|CHANGED
block|,
DECL|enumerator|LAST_SIGNAL
name|LAST_SIGNAL
block|}
enum|;
end_enum

begin_struct
DECL|struct|_GimpColorDisplayPrivate
struct|struct
name|_GimpColorDisplayPrivate
block|{
DECL|member|enabled
name|gboolean
name|enabled
decl_stmt|;
DECL|member|config
name|GimpColorConfig
modifier|*
name|config
decl_stmt|;
DECL|member|managed
name|GimpColorManaged
modifier|*
name|managed
decl_stmt|;
block|}
struct|;
end_struct

begin_define
DECL|macro|GET_PRIVATE (obj)
define|#
directive|define
name|GET_PRIVATE
parameter_list|(
name|obj
parameter_list|)
value|(((GimpColorDisplay *) (obj))->priv)
end_define

begin_function_decl
specifier|static
name|void
name|gimp_color_display_constructed
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
name|gimp_color_display_dispose
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
name|gimp_color_display_set_property
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
name|gimp_color_display_get_property
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
name|gimp_color_display_set_color_config
parameter_list|(
name|GimpColorDisplay
modifier|*
name|display
parameter_list|,
name|GimpColorConfig
modifier|*
name|config
parameter_list|)
function_decl|;
end_function_decl

begin_function_decl
specifier|static
name|void
name|gimp_color_display_set_color_managed
parameter_list|(
name|GimpColorDisplay
modifier|*
name|display
parameter_list|,
name|GimpColorManaged
modifier|*
name|managed
parameter_list|)
function_decl|;
end_function_decl

begin_macro
name|G_DEFINE_TYPE_WITH_CODE
argument_list|(
argument|GimpColorDisplay
argument_list|,
argument|gimp_color_display
argument_list|,
argument|G_TYPE_OBJECT
argument_list|,
argument|G_ADD_PRIVATE (GimpColorDisplay)                          G_ADD_PRIVATE (GimpColorDisplay)                          G_IMPLEMENT_INTERFACE (GIMP_TYPE_CONFIG, NULL)
argument_list|)
end_macro

begin_define
DECL|macro|parent_class
define|#
directive|define
name|parent_class
value|gimp_color_display_parent_class
end_define

begin_decl_stmt
specifier|static
name|guint
name|display_signals
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
specifier|static
name|void
DECL|function|gimp_color_display_class_init (GimpColorDisplayClass * klass)
name|gimp_color_display_class_init
parameter_list|(
name|GimpColorDisplayClass
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
name|object_class
operator|->
name|constructed
operator|=
name|gimp_color_display_constructed
expr_stmt|;
name|object_class
operator|->
name|dispose
operator|=
name|gimp_color_display_dispose
expr_stmt|;
name|object_class
operator|->
name|set_property
operator|=
name|gimp_color_display_set_property
expr_stmt|;
name|object_class
operator|->
name|get_property
operator|=
name|gimp_color_display_get_property
expr_stmt|;
name|g_object_class_install_property
argument_list|(
name|object_class
argument_list|,
name|PROP_ENABLED
argument_list|,
name|g_param_spec_boolean
argument_list|(
literal|"enabled"
argument_list|,
literal|"Enabled"
argument_list|,
literal|"Whether this display filter is enabled"
argument_list|,
name|TRUE
argument_list|,
name|GIMP_PARAM_READWRITE
operator||
name|G_PARAM_CONSTRUCT
argument_list|)
argument_list|)
expr_stmt|;
name|g_object_class_install_property
argument_list|(
name|object_class
argument_list|,
name|PROP_COLOR_CONFIG
argument_list|,
name|g_param_spec_object
argument_list|(
literal|"color-config"
argument_list|,
literal|"Color Config"
argument_list|,
literal|"The color config used for this filter"
argument_list|,
name|GIMP_TYPE_COLOR_CONFIG
argument_list|,
name|GIMP_PARAM_READWRITE
operator||
name|G_PARAM_CONSTRUCT_ONLY
argument_list|)
argument_list|)
expr_stmt|;
name|g_object_class_install_property
argument_list|(
name|object_class
argument_list|,
name|PROP_COLOR_MANAGED
argument_list|,
name|g_param_spec_object
argument_list|(
literal|"color-managed"
argument_list|,
literal|"Color Managed"
argument_list|,
literal|"The color managed pixel source that is filtered"
argument_list|,
name|GIMP_TYPE_COLOR_MANAGED
argument_list|,
name|GIMP_PARAM_READWRITE
operator||
name|G_PARAM_CONSTRUCT_ONLY
argument_list|)
argument_list|)
expr_stmt|;
name|display_signals
index|[
name|CHANGED
index|]
operator|=
name|g_signal_new
argument_list|(
literal|"changed"
argument_list|,
name|G_TYPE_FROM_CLASS
argument_list|(
name|klass
argument_list|)
argument_list|,
name|G_SIGNAL_RUN_FIRST
argument_list|,
name|G_STRUCT_OFFSET
argument_list|(
name|GimpColorDisplayClass
argument_list|,
name|changed
argument_list|)
argument_list|,
name|NULL
argument_list|,
name|NULL
argument_list|,
name|g_cclosure_marshal_VOID__VOID
argument_list|,
name|G_TYPE_NONE
argument_list|,
literal|0
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
name|help_id
operator|=
name|NULL
expr_stmt|;
name|klass
operator|->
name|icon_name
operator|=
name|GIMP_ICON_DISPLAY_FILTER
expr_stmt|;
name|klass
operator|->
name|convert_buffer
operator|=
name|NULL
expr_stmt|;
name|klass
operator|->
name|configure
operator|=
name|NULL
expr_stmt|;
name|klass
operator|->
name|changed
operator|=
name|NULL
expr_stmt|;
block|}
end_function

begin_function
specifier|static
name|void
DECL|function|gimp_color_display_init (GimpColorDisplay * display)
name|gimp_color_display_init
parameter_list|(
name|GimpColorDisplay
modifier|*
name|display
parameter_list|)
block|{
name|display
operator|->
name|priv
operator|=
name|gimp_color_display_get_instance_private
argument_list|(
name|display
argument_list|)
expr_stmt|;
block|}
end_function

begin_function
specifier|static
name|void
DECL|function|gimp_color_display_constructed (GObject * object)
name|gimp_color_display_constructed
parameter_list|(
name|GObject
modifier|*
name|object
parameter_list|)
block|{
name|G_OBJECT_CLASS
argument_list|(
name|parent_class
argument_list|)
operator|->
name|constructed
argument_list|(
name|object
argument_list|)
expr_stmt|;
comment|/* emit an initial "changed" signal after all construct properties are set */
name|gimp_color_display_changed
argument_list|(
name|GIMP_COLOR_DISPLAY
argument_list|(
name|object
argument_list|)
argument_list|)
expr_stmt|;
block|}
end_function

begin_function
specifier|static
name|void
DECL|function|gimp_color_display_dispose (GObject * object)
name|gimp_color_display_dispose
parameter_list|(
name|GObject
modifier|*
name|object
parameter_list|)
block|{
name|GimpColorDisplayPrivate
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
name|config
condition|)
block|{
name|g_signal_handlers_disconnect_by_func
argument_list|(
name|private
operator|->
name|config
argument_list|,
name|gimp_color_display_changed
argument_list|,
name|object
argument_list|)
expr_stmt|;
name|g_object_unref
argument_list|(
name|private
operator|->
name|config
argument_list|)
expr_stmt|;
name|private
operator|->
name|config
operator|=
name|NULL
expr_stmt|;
block|}
if|if
condition|(
name|private
operator|->
name|managed
condition|)
block|{
name|g_signal_handlers_disconnect_by_func
argument_list|(
name|private
operator|->
name|managed
argument_list|,
name|gimp_color_display_changed
argument_list|,
name|object
argument_list|)
expr_stmt|;
name|g_object_unref
argument_list|(
name|private
operator|->
name|managed
argument_list|)
expr_stmt|;
name|private
operator|->
name|managed
operator|=
name|NULL
expr_stmt|;
block|}
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
DECL|function|gimp_color_display_set_property (GObject * object,guint property_id,const GValue * value,GParamSpec * pspec)
name|gimp_color_display_set_property
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
name|GimpColorDisplay
modifier|*
name|display
init|=
name|GIMP_COLOR_DISPLAY
argument_list|(
name|object
argument_list|)
decl_stmt|;
name|GimpColorDisplayPrivate
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
name|PROP_ENABLED
case|:
name|private
operator|->
name|enabled
operator|=
name|g_value_get_boolean
argument_list|(
name|value
argument_list|)
expr_stmt|;
break|break;
case|case
name|PROP_COLOR_CONFIG
case|:
name|gimp_color_display_set_color_config
argument_list|(
name|display
argument_list|,
name|g_value_get_object
argument_list|(
name|value
argument_list|)
argument_list|)
expr_stmt|;
break|break;
case|case
name|PROP_COLOR_MANAGED
case|:
name|gimp_color_display_set_color_managed
argument_list|(
name|display
argument_list|,
name|g_value_get_object
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
DECL|function|gimp_color_display_get_property (GObject * object,guint property_id,GValue * value,GParamSpec * pspec)
name|gimp_color_display_get_property
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
name|GimpColorDisplayPrivate
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
name|PROP_ENABLED
case|:
name|g_value_set_boolean
argument_list|(
name|value
argument_list|,
name|private
operator|->
name|enabled
argument_list|)
expr_stmt|;
break|break;
case|case
name|PROP_COLOR_CONFIG
case|:
name|g_value_set_object
argument_list|(
name|value
argument_list|,
name|private
operator|->
name|config
argument_list|)
expr_stmt|;
break|break;
case|case
name|PROP_COLOR_MANAGED
case|:
name|g_value_set_object
argument_list|(
name|value
argument_list|,
name|private
operator|->
name|managed
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
DECL|function|gimp_color_display_set_color_config (GimpColorDisplay * display,GimpColorConfig * config)
name|gimp_color_display_set_color_config
parameter_list|(
name|GimpColorDisplay
modifier|*
name|display
parameter_list|,
name|GimpColorConfig
modifier|*
name|config
parameter_list|)
block|{
name|GimpColorDisplayPrivate
modifier|*
name|private
init|=
name|GET_PRIVATE
argument_list|(
name|display
argument_list|)
decl_stmt|;
name|g_return_if_fail
argument_list|(
name|private
operator|->
name|config
operator|==
name|NULL
argument_list|)
expr_stmt|;
if|if
condition|(
name|config
condition|)
block|{
name|private
operator|->
name|config
operator|=
name|g_object_ref
argument_list|(
name|config
argument_list|)
expr_stmt|;
name|g_signal_connect_swapped
argument_list|(
name|private
operator|->
name|config
argument_list|,
literal|"notify"
argument_list|,
name|G_CALLBACK
argument_list|(
name|gimp_color_display_changed
argument_list|)
argument_list|,
name|display
argument_list|)
expr_stmt|;
block|}
block|}
end_function

begin_function
specifier|static
name|void
DECL|function|gimp_color_display_set_color_managed (GimpColorDisplay * display,GimpColorManaged * managed)
name|gimp_color_display_set_color_managed
parameter_list|(
name|GimpColorDisplay
modifier|*
name|display
parameter_list|,
name|GimpColorManaged
modifier|*
name|managed
parameter_list|)
block|{
name|GimpColorDisplayPrivate
modifier|*
name|private
init|=
name|GET_PRIVATE
argument_list|(
name|display
argument_list|)
decl_stmt|;
name|g_return_if_fail
argument_list|(
name|private
operator|->
name|managed
operator|==
name|NULL
argument_list|)
expr_stmt|;
if|if
condition|(
name|managed
condition|)
block|{
name|private
operator|->
name|managed
operator|=
name|g_object_ref
argument_list|(
name|managed
argument_list|)
expr_stmt|;
name|g_signal_connect_swapped
argument_list|(
name|private
operator|->
name|managed
argument_list|,
literal|"profile-changed"
argument_list|,
name|G_CALLBACK
argument_list|(
name|gimp_color_display_changed
argument_list|)
argument_list|,
name|display
argument_list|)
expr_stmt|;
block|}
block|}
end_function

begin_function
name|GimpColorDisplay
modifier|*
DECL|function|gimp_color_display_clone (GimpColorDisplay * display)
name|gimp_color_display_clone
parameter_list|(
name|GimpColorDisplay
modifier|*
name|display
parameter_list|)
block|{
name|g_return_val_if_fail
argument_list|(
name|GIMP_IS_COLOR_DISPLAY
argument_list|(
name|display
argument_list|)
argument_list|,
name|NULL
argument_list|)
expr_stmt|;
return|return
name|GIMP_COLOR_DISPLAY
argument_list|(
name|gimp_config_duplicate
argument_list|(
name|GIMP_CONFIG
argument_list|(
name|display
argument_list|)
argument_list|)
argument_list|)
return|;
block|}
end_function

begin_comment
comment|/**  * gimp_color_display_convert_buffer:  * @display: a #GimpColorDisplay  * @buffer:  a #GeglBuffer  * @area:    area in @buffer to convert  *  * Converts all pixels in @area of @buffer.  *  * Since: 2.10  **/
end_comment

begin_function
name|void
DECL|function|gimp_color_display_convert_buffer (GimpColorDisplay * display,GeglBuffer * buffer,GeglRectangle * area)
name|gimp_color_display_convert_buffer
parameter_list|(
name|GimpColorDisplay
modifier|*
name|display
parameter_list|,
name|GeglBuffer
modifier|*
name|buffer
parameter_list|,
name|GeglRectangle
modifier|*
name|area
parameter_list|)
block|{
name|GimpColorDisplayPrivate
modifier|*
name|private
decl_stmt|;
name|g_return_if_fail
argument_list|(
name|GIMP_IS_COLOR_DISPLAY
argument_list|(
name|display
argument_list|)
argument_list|)
expr_stmt|;
name|g_return_if_fail
argument_list|(
name|GEGL_IS_BUFFER
argument_list|(
name|buffer
argument_list|)
argument_list|)
expr_stmt|;
name|private
operator|=
name|GET_PRIVATE
argument_list|(
name|display
argument_list|)
expr_stmt|;
if|if
condition|(
name|private
operator|->
name|enabled
operator|&&
name|GIMP_COLOR_DISPLAY_GET_CLASS
argument_list|(
name|display
argument_list|)
operator|->
name|convert_buffer
condition|)
block|{
name|GIMP_COLOR_DISPLAY_GET_CLASS
argument_list|(
name|display
argument_list|)
operator|->
name|convert_buffer
argument_list|(
name|display
argument_list|,
name|buffer
argument_list|,
name|area
argument_list|)
expr_stmt|;
block|}
block|}
end_function

begin_function
name|void
DECL|function|gimp_color_display_load_state (GimpColorDisplay * display,GimpParasite * state)
name|gimp_color_display_load_state
parameter_list|(
name|GimpColorDisplay
modifier|*
name|display
parameter_list|,
name|GimpParasite
modifier|*
name|state
parameter_list|)
block|{
name|g_return_if_fail
argument_list|(
name|GIMP_IS_COLOR_DISPLAY
argument_list|(
name|display
argument_list|)
argument_list|)
expr_stmt|;
name|g_return_if_fail
argument_list|(
name|state
operator|!=
name|NULL
argument_list|)
expr_stmt|;
name|gimp_config_deserialize_string
argument_list|(
name|GIMP_CONFIG
argument_list|(
name|display
argument_list|)
argument_list|,
name|gimp_parasite_data
argument_list|(
name|state
argument_list|)
argument_list|,
name|gimp_parasite_data_size
argument_list|(
name|state
argument_list|)
argument_list|,
name|NULL
argument_list|,
name|NULL
argument_list|)
expr_stmt|;
block|}
end_function

begin_function
name|GimpParasite
modifier|*
DECL|function|gimp_color_display_save_state (GimpColorDisplay * display)
name|gimp_color_display_save_state
parameter_list|(
name|GimpColorDisplay
modifier|*
name|display
parameter_list|)
block|{
name|GimpParasite
modifier|*
name|parasite
decl_stmt|;
name|gchar
modifier|*
name|str
decl_stmt|;
name|g_return_val_if_fail
argument_list|(
name|GIMP_IS_COLOR_DISPLAY
argument_list|(
name|display
argument_list|)
argument_list|,
name|NULL
argument_list|)
expr_stmt|;
name|str
operator|=
name|gimp_config_serialize_to_string
argument_list|(
name|GIMP_CONFIG
argument_list|(
name|display
argument_list|)
argument_list|,
name|NULL
argument_list|)
expr_stmt|;
name|parasite
operator|=
name|gimp_parasite_new
argument_list|(
literal|"Display/Proof"
argument_list|,
name|GIMP_PARASITE_PERSISTENT
argument_list|,
name|strlen
argument_list|(
name|str
argument_list|)
operator|+
literal|1
argument_list|,
name|str
argument_list|)
expr_stmt|;
name|g_free
argument_list|(
name|str
argument_list|)
expr_stmt|;
return|return
name|parasite
return|;
block|}
end_function

begin_function
name|GtkWidget
modifier|*
DECL|function|gimp_color_display_configure (GimpColorDisplay * display)
name|gimp_color_display_configure
parameter_list|(
name|GimpColorDisplay
modifier|*
name|display
parameter_list|)
block|{
name|g_return_val_if_fail
argument_list|(
name|GIMP_IS_COLOR_DISPLAY
argument_list|(
name|display
argument_list|)
argument_list|,
name|NULL
argument_list|)
expr_stmt|;
if|if
condition|(
name|GIMP_COLOR_DISPLAY_GET_CLASS
argument_list|(
name|display
argument_list|)
operator|->
name|configure
condition|)
return|return
name|GIMP_COLOR_DISPLAY_GET_CLASS
argument_list|(
name|display
argument_list|)
operator|->
name|configure
argument_list|(
name|display
argument_list|)
return|;
return|return
name|NULL
return|;
block|}
end_function

begin_function
name|void
DECL|function|gimp_color_display_configure_reset (GimpColorDisplay * display)
name|gimp_color_display_configure_reset
parameter_list|(
name|GimpColorDisplay
modifier|*
name|display
parameter_list|)
block|{
name|g_return_if_fail
argument_list|(
name|GIMP_IS_COLOR_DISPLAY
argument_list|(
name|display
argument_list|)
argument_list|)
expr_stmt|;
name|gimp_config_reset
argument_list|(
name|GIMP_CONFIG
argument_list|(
name|display
argument_list|)
argument_list|)
expr_stmt|;
block|}
end_function

begin_function
name|void
DECL|function|gimp_color_display_changed (GimpColorDisplay * display)
name|gimp_color_display_changed
parameter_list|(
name|GimpColorDisplay
modifier|*
name|display
parameter_list|)
block|{
name|g_return_if_fail
argument_list|(
name|GIMP_IS_COLOR_DISPLAY
argument_list|(
name|display
argument_list|)
argument_list|)
expr_stmt|;
name|g_signal_emit
argument_list|(
name|display
argument_list|,
name|display_signals
index|[
name|CHANGED
index|]
argument_list|,
literal|0
argument_list|)
expr_stmt|;
block|}
end_function

begin_function
name|void
DECL|function|gimp_color_display_set_enabled (GimpColorDisplay * display,gboolean enabled)
name|gimp_color_display_set_enabled
parameter_list|(
name|GimpColorDisplay
modifier|*
name|display
parameter_list|,
name|gboolean
name|enabled
parameter_list|)
block|{
name|GimpColorDisplayPrivate
modifier|*
name|private
decl_stmt|;
name|g_return_if_fail
argument_list|(
name|GIMP_IS_COLOR_DISPLAY
argument_list|(
name|display
argument_list|)
argument_list|)
expr_stmt|;
name|private
operator|=
name|GET_PRIVATE
argument_list|(
name|display
argument_list|)
expr_stmt|;
if|if
condition|(
name|enabled
operator|!=
name|private
operator|->
name|enabled
condition|)
block|{
name|g_object_set
argument_list|(
name|display
argument_list|,
literal|"enabled"
argument_list|,
name|enabled
argument_list|,
name|NULL
argument_list|)
expr_stmt|;
block|}
block|}
end_function

begin_function
name|gboolean
DECL|function|gimp_color_display_get_enabled (GimpColorDisplay * display)
name|gimp_color_display_get_enabled
parameter_list|(
name|GimpColorDisplay
modifier|*
name|display
parameter_list|)
block|{
name|g_return_val_if_fail
argument_list|(
name|GIMP_IS_COLOR_DISPLAY
argument_list|(
name|display
argument_list|)
argument_list|,
name|FALSE
argument_list|)
expr_stmt|;
return|return
name|GET_PRIVATE
argument_list|(
name|display
argument_list|)
operator|->
name|enabled
return|;
block|}
end_function

begin_comment
comment|/**  * gimp_color_display_get_config:  * @display:  *  * Return value: a pointer to the #GimpColorConfig object or %NULL.  *  * Since: 2.4  **/
end_comment

begin_function
name|GimpColorConfig
modifier|*
DECL|function|gimp_color_display_get_config (GimpColorDisplay * display)
name|gimp_color_display_get_config
parameter_list|(
name|GimpColorDisplay
modifier|*
name|display
parameter_list|)
block|{
name|g_return_val_if_fail
argument_list|(
name|GIMP_IS_COLOR_DISPLAY
argument_list|(
name|display
argument_list|)
argument_list|,
name|NULL
argument_list|)
expr_stmt|;
return|return
name|GET_PRIVATE
argument_list|(
name|display
argument_list|)
operator|->
name|config
return|;
block|}
end_function

begin_comment
comment|/**  * gimp_color_display_get_managed:  * @display:  *  * Return value: a pointer to the #GimpColorManaged object or %NULL.  *  * Since: 2.4  **/
end_comment

begin_function
name|GimpColorManaged
modifier|*
DECL|function|gimp_color_display_get_managed (GimpColorDisplay * display)
name|gimp_color_display_get_managed
parameter_list|(
name|GimpColorDisplay
modifier|*
name|display
parameter_list|)
block|{
name|g_return_val_if_fail
argument_list|(
name|GIMP_IS_COLOR_DISPLAY
argument_list|(
name|display
argument_list|)
argument_list|,
name|NULL
argument_list|)
expr_stmt|;
return|return
name|GET_PRIVATE
argument_list|(
name|display
argument_list|)
operator|->
name|managed
return|;
block|}
end_function

end_unit

