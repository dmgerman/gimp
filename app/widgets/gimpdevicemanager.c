begin_unit|revision:0.9.5;language:C;cregit-version:0.0.1
begin_comment
comment|/* GIMP - The GNU Image Manipulation Program  * Copyright (C) 1995 Spencer Kimball and Peter Mattis  *  * gimpdevicemanager.c  * Copyright (C) 2011 Michael Natterer  *  * This program is free software: you can redistribute it and/or modify  * it under the terms of the GNU General Public License as published by  * the Free Software Foundation; either version 3 of the License, or  * (at your option) any later version.  *  * This program is distributed in the hope that it will be useful,  * but WITHOUT ANY WARRANTY; without even the implied warranty of  * MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the  * GNU General Public License for more details.  *  * You should have received a copy of the GNU General Public License  * along with this program.  If not, see<http://www.gnu.org/licenses/>.  */
end_comment

begin_include
include|#
directive|include
file|"config.h"
end_include

begin_undef
undef|#
directive|undef
name|GSEAL_ENABLE
end_undef

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
file|"widgets-types.h"
end_include

begin_include
include|#
directive|include
file|"config/gimpconfig-utils.h"
end_include

begin_include
include|#
directive|include
file|"config/gimpguiconfig.h"
end_include

begin_include
include|#
directive|include
file|"core/gimp.h"
end_include

begin_include
include|#
directive|include
file|"core/gimpcontext.h"
end_include

begin_include
include|#
directive|include
file|"core/gimpmarshal.h"
end_include

begin_include
include|#
directive|include
file|"core/gimptoolinfo.h"
end_include

begin_include
include|#
directive|include
file|"gimpdeviceinfo.h"
end_include

begin_include
include|#
directive|include
file|"gimpdevicemanager.h"
end_include

begin_enum
enum|enum
DECL|enum|__anon2b62e3a90103
block|{
DECL|enumerator|PROP_0
name|PROP_0
block|,
DECL|enumerator|PROP_GIMP
name|PROP_GIMP
block|,
DECL|enumerator|PROP_CURRENT_DEVICE
name|PROP_CURRENT_DEVICE
block|}
enum|;
end_enum

begin_struct
DECL|struct|_GimpDeviceManagerPrivate
struct|struct
name|_GimpDeviceManagerPrivate
block|{
DECL|member|gimp
name|Gimp
modifier|*
name|gimp
decl_stmt|;
DECL|member|displays
name|GHashTable
modifier|*
name|displays
decl_stmt|;
DECL|member|current_device
name|GimpDeviceInfo
modifier|*
name|current_device
decl_stmt|;
DECL|member|active_tool
name|GimpToolInfo
modifier|*
name|active_tool
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
value|(((GimpDeviceManager *) (obj))->priv)
end_define

begin_function_decl
specifier|static
name|void
name|gimp_device_manager_constructed
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
name|gimp_device_manager_dispose
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
name|gimp_device_manager_finalize
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
name|gimp_device_manager_set_property
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
name|gimp_device_manager_get_property
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
name|gimp_device_manager_display_opened
parameter_list|(
name|GdkDisplayManager
modifier|*
name|disp_manager
parameter_list|,
name|GdkDisplay
modifier|*
name|display
parameter_list|,
name|GimpDeviceManager
modifier|*
name|manager
parameter_list|)
function_decl|;
end_function_decl

begin_function_decl
specifier|static
name|void
name|gimp_device_manager_display_closed
parameter_list|(
name|GdkDisplay
modifier|*
name|display
parameter_list|,
name|gboolean
name|is_error
parameter_list|,
name|GimpDeviceManager
modifier|*
name|manager
parameter_list|)
function_decl|;
end_function_decl

begin_function_decl
specifier|static
name|void
name|gimp_device_manager_device_added
parameter_list|(
name|GdkDisplay
modifier|*
name|gdk_display
parameter_list|,
name|GdkDevice
modifier|*
name|device
parameter_list|,
name|GimpDeviceManager
modifier|*
name|manager
parameter_list|)
function_decl|;
end_function_decl

begin_function_decl
specifier|static
name|void
name|gimp_device_manager_device_removed
parameter_list|(
name|GdkDisplay
modifier|*
name|gdk_display
parameter_list|,
name|GdkDevice
modifier|*
name|device
parameter_list|,
name|GimpDeviceManager
modifier|*
name|manager
parameter_list|)
function_decl|;
end_function_decl

begin_function_decl
specifier|static
name|void
name|gimp_device_manager_config_notify
parameter_list|(
name|GimpGuiConfig
modifier|*
name|config
parameter_list|,
specifier|const
name|GParamSpec
modifier|*
name|pspec
parameter_list|,
name|GimpDeviceManager
modifier|*
name|manager
parameter_list|)
function_decl|;
end_function_decl

begin_function_decl
specifier|static
name|void
name|gimp_device_manager_tool_changed
parameter_list|(
name|GimpContext
modifier|*
name|user_context
parameter_list|,
name|GimpToolInfo
modifier|*
name|tool_info
parameter_list|,
name|GimpDeviceManager
modifier|*
name|manager
parameter_list|)
function_decl|;
end_function_decl

begin_function_decl
specifier|static
name|void
name|gimp_device_manager_connect_tool
parameter_list|(
name|GimpDeviceManager
modifier|*
name|manager
parameter_list|)
function_decl|;
end_function_decl

begin_function_decl
specifier|static
name|void
name|gimp_device_manager_disconnect_tool
parameter_list|(
name|GimpDeviceManager
modifier|*
name|manager
parameter_list|)
function_decl|;
end_function_decl

begin_macro
DECL|function|G_DEFINE_TYPE (GimpDeviceManager,gimp_device_manager,GIMP_TYPE_LIST)
name|G_DEFINE_TYPE
argument_list|(
argument|GimpDeviceManager
argument_list|,
argument|gimp_device_manager
argument_list|,
argument|GIMP_TYPE_LIST
argument_list|)
end_macro

begin_define
DECL|macro|parent_class
define|#
directive|define
name|parent_class
value|gimp_device_manager_parent_class
end_define

begin_function
specifier|static
name|void
name|gimp_device_manager_class_init
parameter_list|(
name|GimpDeviceManagerClass
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
name|gimp_device_manager_constructed
expr_stmt|;
name|object_class
operator|->
name|dispose
operator|=
name|gimp_device_manager_dispose
expr_stmt|;
name|object_class
operator|->
name|finalize
operator|=
name|gimp_device_manager_finalize
expr_stmt|;
name|object_class
operator|->
name|set_property
operator|=
name|gimp_device_manager_set_property
expr_stmt|;
name|object_class
operator|->
name|get_property
operator|=
name|gimp_device_manager_get_property
expr_stmt|;
name|g_object_class_install_property
argument_list|(
name|object_class
argument_list|,
name|PROP_GIMP
argument_list|,
name|g_param_spec_object
argument_list|(
literal|"gimp"
argument_list|,
name|NULL
argument_list|,
name|NULL
argument_list|,
name|GIMP_TYPE_GIMP
argument_list|,
name|GIMP_PARAM_STATIC_STRINGS
operator||
name|G_PARAM_READWRITE
operator||
name|G_PARAM_CONSTRUCT_ONLY
argument_list|)
argument_list|)
expr_stmt|;
name|g_object_class_install_property
argument_list|(
name|object_class
argument_list|,
name|PROP_CURRENT_DEVICE
argument_list|,
name|g_param_spec_object
argument_list|(
literal|"current-device"
argument_list|,
name|NULL
argument_list|,
name|NULL
argument_list|,
name|GIMP_TYPE_DEVICE_INFO
argument_list|,
name|GIMP_PARAM_STATIC_STRINGS
operator||
name|G_PARAM_READABLE
argument_list|)
argument_list|)
expr_stmt|;
name|g_type_class_add_private
argument_list|(
name|object_class
argument_list|,
sizeof|sizeof
argument_list|(
name|GimpDeviceManagerPrivate
argument_list|)
argument_list|)
expr_stmt|;
block|}
end_function

begin_function
specifier|static
name|void
DECL|function|gimp_device_manager_init (GimpDeviceManager * manager)
name|gimp_device_manager_init
parameter_list|(
name|GimpDeviceManager
modifier|*
name|manager
parameter_list|)
block|{
name|manager
operator|->
name|priv
operator|=
name|G_TYPE_INSTANCE_GET_PRIVATE
argument_list|(
name|manager
argument_list|,
name|GIMP_TYPE_DEVICE_MANAGER
argument_list|,
name|GimpDeviceManagerPrivate
argument_list|)
expr_stmt|;
name|manager
operator|->
name|priv
operator|->
name|displays
operator|=
name|g_hash_table_new_full
argument_list|(
name|g_str_hash
argument_list|,
name|g_str_equal
argument_list|,
name|g_free
argument_list|,
name|NULL
argument_list|)
expr_stmt|;
block|}
end_function

begin_function
specifier|static
name|void
DECL|function|gimp_device_manager_constructed (GObject * object)
name|gimp_device_manager_constructed
parameter_list|(
name|GObject
modifier|*
name|object
parameter_list|)
block|{
name|GimpDeviceManager
modifier|*
name|manager
init|=
name|GIMP_DEVICE_MANAGER
argument_list|(
name|object
argument_list|)
decl_stmt|;
name|GimpDeviceManagerPrivate
modifier|*
name|private
init|=
name|GET_PRIVATE
argument_list|(
name|object
argument_list|)
decl_stmt|;
name|GdkDisplayManager
modifier|*
name|disp_manager
decl_stmt|;
name|GSList
modifier|*
name|displays
decl_stmt|;
name|GSList
modifier|*
name|list
decl_stmt|;
name|GdkDisplay
modifier|*
name|display
decl_stmt|;
name|GimpDeviceInfo
modifier|*
name|device_info
decl_stmt|;
name|GimpContext
modifier|*
name|user_context
decl_stmt|;
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
name|gimp_assert
argument_list|(
name|GIMP_IS_GIMP
argument_list|(
name|private
operator|->
name|gimp
argument_list|)
argument_list|)
expr_stmt|;
name|disp_manager
operator|=
name|gdk_display_manager_get
argument_list|()
expr_stmt|;
name|displays
operator|=
name|gdk_display_manager_list_displays
argument_list|(
name|disp_manager
argument_list|)
expr_stmt|;
comment|/*  present displays in the order in which they were opened  */
name|displays
operator|=
name|g_slist_reverse
argument_list|(
name|displays
argument_list|)
expr_stmt|;
for|for
control|(
name|list
operator|=
name|displays
init|;
name|list
condition|;
name|list
operator|=
name|g_slist_next
argument_list|(
name|list
argument_list|)
control|)
block|{
name|gimp_device_manager_display_opened
argument_list|(
name|disp_manager
argument_list|,
name|list
operator|->
name|data
argument_list|,
name|manager
argument_list|)
expr_stmt|;
block|}
name|g_slist_free
argument_list|(
name|displays
argument_list|)
expr_stmt|;
name|g_signal_connect
argument_list|(
name|disp_manager
argument_list|,
literal|"display-opened"
argument_list|,
name|G_CALLBACK
argument_list|(
name|gimp_device_manager_display_opened
argument_list|)
argument_list|,
name|manager
argument_list|)
expr_stmt|;
name|display
operator|=
name|gdk_display_get_default
argument_list|()
expr_stmt|;
name|device_info
operator|=
name|gimp_device_info_get_by_device
argument_list|(
name|gdk_display_get_core_pointer
argument_list|(
name|display
argument_list|)
argument_list|)
expr_stmt|;
name|gimp_device_manager_set_current_device
argument_list|(
name|manager
argument_list|,
name|device_info
argument_list|)
expr_stmt|;
name|g_signal_connect_object
argument_list|(
name|private
operator|->
name|gimp
operator|->
name|config
argument_list|,
literal|"notify::devices-share-tool"
argument_list|,
name|G_CALLBACK
argument_list|(
name|gimp_device_manager_config_notify
argument_list|)
argument_list|,
name|manager
argument_list|,
literal|0
argument_list|)
expr_stmt|;
name|user_context
operator|=
name|gimp_get_user_context
argument_list|(
name|private
operator|->
name|gimp
argument_list|)
expr_stmt|;
name|g_signal_connect_object
argument_list|(
name|user_context
argument_list|,
literal|"tool-changed"
argument_list|,
name|G_CALLBACK
argument_list|(
name|gimp_device_manager_tool_changed
argument_list|)
argument_list|,
name|manager
argument_list|,
literal|0
argument_list|)
expr_stmt|;
block|}
end_function

begin_function
specifier|static
name|void
DECL|function|gimp_device_manager_dispose (GObject * object)
name|gimp_device_manager_dispose
parameter_list|(
name|GObject
modifier|*
name|object
parameter_list|)
block|{
name|GimpDeviceManager
modifier|*
name|manager
init|=
name|GIMP_DEVICE_MANAGER
argument_list|(
name|object
argument_list|)
decl_stmt|;
name|gimp_device_manager_disconnect_tool
argument_list|(
name|manager
argument_list|)
expr_stmt|;
name|g_signal_handlers_disconnect_by_func
argument_list|(
name|gdk_display_manager_get
argument_list|()
argument_list|,
name|gimp_device_manager_display_opened
argument_list|,
name|object
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
DECL|function|gimp_device_manager_finalize (GObject * object)
name|gimp_device_manager_finalize
parameter_list|(
name|GObject
modifier|*
name|object
parameter_list|)
block|{
name|GimpDeviceManagerPrivate
modifier|*
name|private
init|=
name|GET_PRIVATE
argument_list|(
name|object
argument_list|)
decl_stmt|;
name|g_clear_pointer
argument_list|(
operator|&
name|private
operator|->
name|displays
argument_list|,
name|g_hash_table_unref
argument_list|)
expr_stmt|;
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
DECL|function|gimp_device_manager_set_property (GObject * object,guint property_id,const GValue * value,GParamSpec * pspec)
name|gimp_device_manager_set_property
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
name|GimpDeviceManagerPrivate
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
name|PROP_GIMP
case|:
name|private
operator|->
name|gimp
operator|=
name|g_value_get_object
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
DECL|function|gimp_device_manager_get_property (GObject * object,guint property_id,GValue * value,GParamSpec * pspec)
name|gimp_device_manager_get_property
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
name|GimpDeviceManagerPrivate
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
name|PROP_GIMP
case|:
name|g_value_set_object
argument_list|(
name|value
argument_list|,
name|private
operator|->
name|gimp
argument_list|)
expr_stmt|;
break|break;
case|case
name|PROP_CURRENT_DEVICE
case|:
name|g_value_set_object
argument_list|(
name|value
argument_list|,
name|private
operator|->
name|current_device
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

begin_comment
comment|/*  public functions  */
end_comment

begin_function
name|GimpDeviceManager
modifier|*
DECL|function|gimp_device_manager_new (Gimp * gimp)
name|gimp_device_manager_new
parameter_list|(
name|Gimp
modifier|*
name|gimp
parameter_list|)
block|{
name|g_return_val_if_fail
argument_list|(
name|GIMP_IS_GIMP
argument_list|(
name|gimp
argument_list|)
argument_list|,
name|NULL
argument_list|)
expr_stmt|;
return|return
name|g_object_new
argument_list|(
name|GIMP_TYPE_DEVICE_MANAGER
argument_list|,
literal|"gimp"
argument_list|,
name|gimp
argument_list|,
literal|"children-type"
argument_list|,
name|GIMP_TYPE_DEVICE_INFO
argument_list|,
literal|"policy"
argument_list|,
name|GIMP_CONTAINER_POLICY_STRONG
argument_list|,
literal|"unique-names"
argument_list|,
name|FALSE
argument_list|,
literal|"sort-func"
argument_list|,
name|gimp_device_info_compare
argument_list|,
name|NULL
argument_list|)
return|;
block|}
end_function

begin_function
name|GimpDeviceInfo
modifier|*
DECL|function|gimp_device_manager_get_current_device (GimpDeviceManager * manager)
name|gimp_device_manager_get_current_device
parameter_list|(
name|GimpDeviceManager
modifier|*
name|manager
parameter_list|)
block|{
name|g_return_val_if_fail
argument_list|(
name|GIMP_IS_DEVICE_MANAGER
argument_list|(
name|manager
argument_list|)
argument_list|,
name|NULL
argument_list|)
expr_stmt|;
return|return
name|GET_PRIVATE
argument_list|(
name|manager
argument_list|)
operator|->
name|current_device
return|;
block|}
end_function

begin_function
name|void
DECL|function|gimp_device_manager_set_current_device (GimpDeviceManager * manager,GimpDeviceInfo * info)
name|gimp_device_manager_set_current_device
parameter_list|(
name|GimpDeviceManager
modifier|*
name|manager
parameter_list|,
name|GimpDeviceInfo
modifier|*
name|info
parameter_list|)
block|{
name|GimpDeviceManagerPrivate
modifier|*
name|private
decl_stmt|;
name|GimpGuiConfig
modifier|*
name|config
decl_stmt|;
name|g_return_if_fail
argument_list|(
name|GIMP_IS_DEVICE_MANAGER
argument_list|(
name|manager
argument_list|)
argument_list|)
expr_stmt|;
name|g_return_if_fail
argument_list|(
name|GIMP_IS_DEVICE_INFO
argument_list|(
name|info
argument_list|)
argument_list|)
expr_stmt|;
name|private
operator|=
name|GET_PRIVATE
argument_list|(
name|manager
argument_list|)
expr_stmt|;
name|config
operator|=
name|GIMP_GUI_CONFIG
argument_list|(
name|private
operator|->
name|gimp
operator|->
name|config
argument_list|)
expr_stmt|;
if|if
condition|(
operator|!
name|config
operator|->
name|devices_share_tool
operator|&&
name|private
operator|->
name|current_device
condition|)
block|{
name|gimp_device_manager_disconnect_tool
argument_list|(
name|manager
argument_list|)
expr_stmt|;
block|}
name|private
operator|->
name|current_device
operator|=
name|info
expr_stmt|;
if|if
condition|(
operator|!
name|config
operator|->
name|devices_share_tool
operator|&&
name|private
operator|->
name|current_device
condition|)
block|{
name|GimpContext
modifier|*
name|user_context
init|=
name|gimp_get_user_context
argument_list|(
name|private
operator|->
name|gimp
argument_list|)
decl_stmt|;
name|g_signal_handlers_block_by_func
argument_list|(
name|user_context
argument_list|,
name|gimp_device_manager_tool_changed
argument_list|,
name|manager
argument_list|)
expr_stmt|;
name|gimp_device_info_restore_tool
argument_list|(
name|private
operator|->
name|current_device
argument_list|)
expr_stmt|;
name|g_signal_handlers_unblock_by_func
argument_list|(
name|user_context
argument_list|,
name|gimp_device_manager_tool_changed
argument_list|,
name|manager
argument_list|)
expr_stmt|;
name|private
operator|->
name|active_tool
operator|=
name|gimp_context_get_tool
argument_list|(
name|user_context
argument_list|)
expr_stmt|;
name|gimp_device_manager_connect_tool
argument_list|(
name|manager
argument_list|)
expr_stmt|;
block|}
name|g_object_notify
argument_list|(
name|G_OBJECT
argument_list|(
name|manager
argument_list|)
argument_list|,
literal|"current-device"
argument_list|)
expr_stmt|;
block|}
end_function

begin_comment
comment|/*  private functions  */
end_comment

begin_function
specifier|static
name|void
DECL|function|gimp_device_manager_display_opened (GdkDisplayManager * disp_manager,GdkDisplay * gdk_display,GimpDeviceManager * manager)
name|gimp_device_manager_display_opened
parameter_list|(
name|GdkDisplayManager
modifier|*
name|disp_manager
parameter_list|,
name|GdkDisplay
modifier|*
name|gdk_display
parameter_list|,
name|GimpDeviceManager
modifier|*
name|manager
parameter_list|)
block|{
name|GimpDeviceManagerPrivate
modifier|*
name|private
init|=
name|GET_PRIVATE
argument_list|(
name|manager
argument_list|)
decl_stmt|;
name|GList
modifier|*
name|list
decl_stmt|;
specifier|const
name|gchar
modifier|*
name|display_name
decl_stmt|;
name|gint
name|count
decl_stmt|;
name|display_name
operator|=
name|gdk_display_get_name
argument_list|(
name|gdk_display
argument_list|)
expr_stmt|;
name|count
operator|=
name|GPOINTER_TO_INT
argument_list|(
name|g_hash_table_lookup
argument_list|(
name|private
operator|->
name|displays
argument_list|,
name|display_name
argument_list|)
argument_list|)
expr_stmt|;
name|g_hash_table_insert
argument_list|(
name|private
operator|->
name|displays
argument_list|,
name|g_strdup
argument_list|(
name|display_name
argument_list|)
argument_list|,
name|GINT_TO_POINTER
argument_list|(
name|count
operator|+
literal|1
argument_list|)
argument_list|)
expr_stmt|;
comment|/*  don't add the same display twice  */
if|if
condition|(
name|count
operator|>
literal|0
condition|)
return|return;
comment|/*  create device info structures for present devices */
for|for
control|(
name|list
operator|=
name|gdk_display_list_devices
argument_list|(
name|gdk_display
argument_list|)
init|;
name|list
condition|;
name|list
operator|=
name|list
operator|->
name|next
control|)
block|{
name|GdkDevice
modifier|*
name|device
init|=
name|list
operator|->
name|data
decl_stmt|;
name|gimp_device_manager_device_added
argument_list|(
name|gdk_display
argument_list|,
name|device
argument_list|,
name|manager
argument_list|)
expr_stmt|;
block|}
name|g_signal_connect
argument_list|(
name|gdk_display
argument_list|,
literal|"closed"
argument_list|,
name|G_CALLBACK
argument_list|(
name|gimp_device_manager_display_closed
argument_list|)
argument_list|,
name|manager
argument_list|)
expr_stmt|;
block|}
end_function

begin_function
specifier|static
name|void
DECL|function|gimp_device_manager_display_closed (GdkDisplay * gdk_display,gboolean is_error,GimpDeviceManager * manager)
name|gimp_device_manager_display_closed
parameter_list|(
name|GdkDisplay
modifier|*
name|gdk_display
parameter_list|,
name|gboolean
name|is_error
parameter_list|,
name|GimpDeviceManager
modifier|*
name|manager
parameter_list|)
block|{
name|GimpDeviceManagerPrivate
modifier|*
name|private
init|=
name|GET_PRIVATE
argument_list|(
name|manager
argument_list|)
decl_stmt|;
name|GList
modifier|*
name|list
decl_stmt|;
specifier|const
name|gchar
modifier|*
name|display_name
decl_stmt|;
name|gint
name|count
decl_stmt|;
name|display_name
operator|=
name|gdk_display_get_name
argument_list|(
name|gdk_display
argument_list|)
expr_stmt|;
name|count
operator|=
name|GPOINTER_TO_INT
argument_list|(
name|g_hash_table_lookup
argument_list|(
name|private
operator|->
name|displays
argument_list|,
name|display_name
argument_list|)
argument_list|)
expr_stmt|;
comment|/*  don't remove the same display twice  */
if|if
condition|(
name|count
operator|>
literal|1
condition|)
block|{
name|g_hash_table_insert
argument_list|(
name|private
operator|->
name|displays
argument_list|,
name|g_strdup
argument_list|(
name|display_name
argument_list|)
argument_list|,
name|GINT_TO_POINTER
argument_list|(
name|count
operator|-
literal|1
argument_list|)
argument_list|)
expr_stmt|;
return|return;
block|}
name|g_hash_table_remove
argument_list|(
name|private
operator|->
name|displays
argument_list|,
name|display_name
argument_list|)
expr_stmt|;
for|for
control|(
name|list
operator|=
name|gdk_display_list_devices
argument_list|(
name|gdk_display
argument_list|)
init|;
name|list
condition|;
name|list
operator|=
name|list
operator|->
name|next
control|)
block|{
name|GdkDevice
modifier|*
name|device
init|=
name|list
operator|->
name|data
decl_stmt|;
name|gimp_device_manager_device_removed
argument_list|(
name|gdk_display
argument_list|,
name|device
argument_list|,
name|manager
argument_list|)
expr_stmt|;
block|}
block|}
end_function

begin_function
specifier|static
name|void
DECL|function|gimp_device_manager_device_added (GdkDisplay * gdk_display,GdkDevice * device,GimpDeviceManager * manager)
name|gimp_device_manager_device_added
parameter_list|(
name|GdkDisplay
modifier|*
name|gdk_display
parameter_list|,
name|GdkDevice
modifier|*
name|device
parameter_list|,
name|GimpDeviceManager
modifier|*
name|manager
parameter_list|)
block|{
name|GimpDeviceManagerPrivate
modifier|*
name|private
init|=
name|GET_PRIVATE
argument_list|(
name|manager
argument_list|)
decl_stmt|;
name|GimpDeviceInfo
modifier|*
name|device_info
decl_stmt|;
name|device_info
operator|=
name|GIMP_DEVICE_INFO
argument_list|(
name|gimp_container_get_child_by_name
argument_list|(
name|GIMP_CONTAINER
argument_list|(
name|manager
argument_list|)
argument_list|,
name|device
operator|->
name|name
argument_list|)
argument_list|)
expr_stmt|;
if|if
condition|(
name|device_info
condition|)
block|{
name|gimp_device_info_set_device
argument_list|(
name|device_info
argument_list|,
name|device
argument_list|,
name|gdk_display
argument_list|)
expr_stmt|;
block|}
else|else
block|{
name|device_info
operator|=
name|gimp_device_info_new
argument_list|(
name|private
operator|->
name|gimp
argument_list|,
name|device
argument_list|,
name|gdk_display
argument_list|)
expr_stmt|;
name|gimp_device_info_set_default_tool
argument_list|(
name|device_info
argument_list|)
expr_stmt|;
name|gimp_container_add
argument_list|(
name|GIMP_CONTAINER
argument_list|(
name|manager
argument_list|)
argument_list|,
name|GIMP_OBJECT
argument_list|(
name|device_info
argument_list|)
argument_list|)
expr_stmt|;
name|g_object_unref
argument_list|(
name|device_info
argument_list|)
expr_stmt|;
block|}
block|}
end_function

begin_function
specifier|static
name|void
DECL|function|gimp_device_manager_device_removed (GdkDisplay * gdk_display,GdkDevice * device,GimpDeviceManager * manager)
name|gimp_device_manager_device_removed
parameter_list|(
name|GdkDisplay
modifier|*
name|gdk_display
parameter_list|,
name|GdkDevice
modifier|*
name|device
parameter_list|,
name|GimpDeviceManager
modifier|*
name|manager
parameter_list|)
block|{
name|GimpDeviceManagerPrivate
modifier|*
name|private
init|=
name|GET_PRIVATE
argument_list|(
name|manager
argument_list|)
decl_stmt|;
name|GimpDeviceInfo
modifier|*
name|device_info
decl_stmt|;
name|device_info
operator|=
name|GIMP_DEVICE_INFO
argument_list|(
name|gimp_container_get_child_by_name
argument_list|(
name|GIMP_CONTAINER
argument_list|(
name|manager
argument_list|)
argument_list|,
name|device
operator|->
name|name
argument_list|)
argument_list|)
expr_stmt|;
if|if
condition|(
name|device_info
condition|)
block|{
name|gimp_device_info_set_device
argument_list|(
name|device_info
argument_list|,
name|NULL
argument_list|,
name|NULL
argument_list|)
expr_stmt|;
if|if
condition|(
name|device_info
operator|==
name|private
operator|->
name|current_device
condition|)
block|{
name|device
operator|=
name|gdk_display_get_core_pointer
argument_list|(
name|gdk_display
argument_list|)
expr_stmt|;
name|device_info
operator|=
name|gimp_device_info_get_by_device
argument_list|(
name|device
argument_list|)
expr_stmt|;
name|gimp_device_manager_set_current_device
argument_list|(
name|manager
argument_list|,
name|device_info
argument_list|)
expr_stmt|;
block|}
block|}
block|}
end_function

begin_function
specifier|static
name|void
DECL|function|gimp_device_manager_config_notify (GimpGuiConfig * config,const GParamSpec * pspec,GimpDeviceManager * manager)
name|gimp_device_manager_config_notify
parameter_list|(
name|GimpGuiConfig
modifier|*
name|config
parameter_list|,
specifier|const
name|GParamSpec
modifier|*
name|pspec
parameter_list|,
name|GimpDeviceManager
modifier|*
name|manager
parameter_list|)
block|{
name|GimpDeviceManagerPrivate
modifier|*
name|private
init|=
name|GET_PRIVATE
argument_list|(
name|manager
argument_list|)
decl_stmt|;
name|GimpDeviceInfo
modifier|*
name|current_device
decl_stmt|;
name|current_device
operator|=
name|gimp_device_manager_get_current_device
argument_list|(
name|manager
argument_list|)
expr_stmt|;
if|if
condition|(
name|config
operator|->
name|devices_share_tool
condition|)
block|{
name|gimp_device_manager_disconnect_tool
argument_list|(
name|manager
argument_list|)
expr_stmt|;
name|gimp_device_info_save_tool
argument_list|(
name|current_device
argument_list|)
expr_stmt|;
block|}
else|else
block|{
name|GimpContext
modifier|*
name|user_context
init|=
name|gimp_get_user_context
argument_list|(
name|private
operator|->
name|gimp
argument_list|)
decl_stmt|;
name|g_signal_handlers_block_by_func
argument_list|(
name|user_context
argument_list|,
name|gimp_device_manager_tool_changed
argument_list|,
name|manager
argument_list|)
expr_stmt|;
name|gimp_device_info_restore_tool
argument_list|(
name|private
operator|->
name|current_device
argument_list|)
expr_stmt|;
name|g_signal_handlers_unblock_by_func
argument_list|(
name|user_context
argument_list|,
name|gimp_device_manager_tool_changed
argument_list|,
name|manager
argument_list|)
expr_stmt|;
name|private
operator|->
name|active_tool
operator|=
name|gimp_context_get_tool
argument_list|(
name|user_context
argument_list|)
expr_stmt|;
name|gimp_device_manager_connect_tool
argument_list|(
name|manager
argument_list|)
expr_stmt|;
block|}
block|}
end_function

begin_function
specifier|static
name|void
DECL|function|gimp_device_manager_tool_changed (GimpContext * user_context,GimpToolInfo * tool_info,GimpDeviceManager * manager)
name|gimp_device_manager_tool_changed
parameter_list|(
name|GimpContext
modifier|*
name|user_context
parameter_list|,
name|GimpToolInfo
modifier|*
name|tool_info
parameter_list|,
name|GimpDeviceManager
modifier|*
name|manager
parameter_list|)
block|{
name|GimpDeviceManagerPrivate
modifier|*
name|private
init|=
name|GET_PRIVATE
argument_list|(
name|manager
argument_list|)
decl_stmt|;
name|GimpGuiConfig
modifier|*
name|config
decl_stmt|;
name|config
operator|=
name|GIMP_GUI_CONFIG
argument_list|(
name|private
operator|->
name|gimp
operator|->
name|config
argument_list|)
expr_stmt|;
if|if
condition|(
operator|!
name|config
operator|->
name|devices_share_tool
condition|)
block|{
name|gimp_device_manager_disconnect_tool
argument_list|(
name|manager
argument_list|)
expr_stmt|;
block|}
name|private
operator|->
name|active_tool
operator|=
name|tool_info
expr_stmt|;
if|if
condition|(
operator|!
name|config
operator|->
name|devices_share_tool
condition|)
block|{
name|gimp_device_info_save_tool
argument_list|(
name|private
operator|->
name|current_device
argument_list|)
expr_stmt|;
name|gimp_device_manager_connect_tool
argument_list|(
name|manager
argument_list|)
expr_stmt|;
block|}
block|}
end_function

begin_function
specifier|static
name|void
DECL|function|gimp_device_manager_connect_tool (GimpDeviceManager * manager)
name|gimp_device_manager_connect_tool
parameter_list|(
name|GimpDeviceManager
modifier|*
name|manager
parameter_list|)
block|{
name|GimpDeviceManagerPrivate
modifier|*
name|private
init|=
name|GET_PRIVATE
argument_list|(
name|manager
argument_list|)
decl_stmt|;
name|GimpGuiConfig
modifier|*
name|config
decl_stmt|;
name|config
operator|=
name|GIMP_GUI_CONFIG
argument_list|(
name|private
operator|->
name|gimp
operator|->
name|config
argument_list|)
expr_stmt|;
if|if
condition|(
operator|!
name|config
operator|->
name|devices_share_tool
operator|&&
name|private
operator|->
name|active_tool
operator|&&
name|private
operator|->
name|current_device
condition|)
block|{
name|GimpToolPreset
modifier|*
name|preset
init|=
name|GIMP_TOOL_PRESET
argument_list|(
name|private
operator|->
name|current_device
argument_list|)
decl_stmt|;
name|gimp_config_connect
argument_list|(
name|G_OBJECT
argument_list|(
name|private
operator|->
name|active_tool
operator|->
name|tool_options
argument_list|)
argument_list|,
name|G_OBJECT
argument_list|(
name|preset
operator|->
name|tool_options
argument_list|)
argument_list|,
name|NULL
argument_list|)
expr_stmt|;
block|}
block|}
end_function

begin_function
specifier|static
name|void
DECL|function|gimp_device_manager_disconnect_tool (GimpDeviceManager * manager)
name|gimp_device_manager_disconnect_tool
parameter_list|(
name|GimpDeviceManager
modifier|*
name|manager
parameter_list|)
block|{
name|GimpDeviceManagerPrivate
modifier|*
name|private
init|=
name|GET_PRIVATE
argument_list|(
name|manager
argument_list|)
decl_stmt|;
name|GimpGuiConfig
modifier|*
name|config
decl_stmt|;
name|config
operator|=
name|GIMP_GUI_CONFIG
argument_list|(
name|private
operator|->
name|gimp
operator|->
name|config
argument_list|)
expr_stmt|;
if|if
condition|(
operator|!
name|config
operator|->
name|devices_share_tool
operator|&&
name|private
operator|->
name|active_tool
operator|&&
name|private
operator|->
name|current_device
condition|)
block|{
name|GimpToolPreset
modifier|*
name|preset
init|=
name|GIMP_TOOL_PRESET
argument_list|(
name|private
operator|->
name|current_device
argument_list|)
decl_stmt|;
name|gimp_config_disconnect
argument_list|(
name|G_OBJECT
argument_list|(
name|private
operator|->
name|active_tool
operator|->
name|tool_options
argument_list|)
argument_list|,
name|G_OBJECT
argument_list|(
name|preset
operator|->
name|tool_options
argument_list|)
argument_list|)
expr_stmt|;
block|}
block|}
end_function

end_unit

