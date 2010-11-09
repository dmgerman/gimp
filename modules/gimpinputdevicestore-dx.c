begin_unit|revision:0.9.5;language:C;cregit-version:0.0.1
begin_comment
comment|/* GIMP - The GNU Image Manipulation Program  * Copyright (C) 1995 Spencer Kimball and Peter Mattis  *  * gimpinputdevicestore-dx.c  * Input device store based on DirectX.  * Copyright (C) 2007  Sven Neumann<sven@gimp.org>  * Copyright (C) 2007  Tor Lillqvist<tml@novell.com>  *  * This program is free software: you can redistribute it and/or modify  * it under the terms of the GNU General Public License as published by  * the Free Software Foundation; either version 3 of the License, or  * (at your option) any later version.  *  * This program is distributed in the hope that it will be useful,  * but WITHOUT ANY WARRANTY; without even the implied warranty of  * MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the  * GNU General Public License for more details.  *  * You should have received a copy of the GNU General Public License  * along with this program.  If not, see<http://www.gnu.org/licenses/>.  */
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
file|<gtk/gtk.h>
end_include

begin_ifdef
ifdef|#
directive|ifdef
name|HAVE_DX_DINPUT
end_ifdef

begin_define
DECL|macro|_WIN32_WINNT
define|#
directive|define
name|_WIN32_WINNT
value|0x0501
end_define

begin_include
include|#
directive|include
file|<windows.h>
end_include

begin_define
DECL|macro|DIRECTINPUT_VERSION
define|#
directive|define
name|DIRECTINPUT_VERSION
value|0x0800
end_define

begin_include
include|#
directive|include
file|<dinput.h>
end_include

begin_include
include|#
directive|include
file|<rpc.h>
end_include

begin_ifndef
ifndef|#
directive|ifndef
name|GET_MODULE_HANDLE_EX_FLAG_FROM_ADDRESS
end_ifndef

begin_define
DECL|macro|GET_MODULE_HANDLE_EX_FLAG_FROM_ADDRESS
define|#
directive|define
name|GET_MODULE_HANDLE_EX_FLAG_FROM_ADDRESS
value|0x00000004
end_define

begin_endif
endif|#
directive|endif
end_endif

begin_include
include|#
directive|include
file|<gdk/gdkwin32.h>
end_include

begin_include
include|#
directive|include
file|"libgimpmodule/gimpmodule.h"
end_include

begin_include
include|#
directive|include
file|"gimpinputdevicestore.h"
end_include

begin_enum
enum|enum
DECL|enum|__anon2c550c2e0103
block|{
DECL|enumerator|COLUMN_GUID
name|COLUMN_GUID
block|,
DECL|enumerator|COLUMN_LABEL
name|COLUMN_LABEL
block|,
DECL|enumerator|COLUMN_IDEVICE
name|COLUMN_IDEVICE
block|,
DECL|enumerator|NUM_COLUMNS
name|NUM_COLUMNS
block|}
enum|;
end_enum

begin_enum
enum|enum
DECL|enum|__anon2c550c2e0203
block|{
DECL|enumerator|DEVICE_ADDED
name|DEVICE_ADDED
block|,
DECL|enumerator|DEVICE_REMOVED
name|DEVICE_REMOVED
block|,
DECL|enumerator|LAST_SIGNAL
name|LAST_SIGNAL
block|}
enum|;
end_enum

begin_typedef
DECL|typedef|GimpInputDeviceStoreClass
typedef|typedef
name|struct
name|_GimpInputDeviceStoreClass
name|GimpInputDeviceStoreClass
typedef|;
end_typedef

begin_struct
DECL|struct|_GimpInputDeviceStore
struct|struct
name|_GimpInputDeviceStore
block|{
DECL|member|parent_instance
name|GtkListStore
name|parent_instance
decl_stmt|;
DECL|member|window
name|GdkWindow
modifier|*
name|window
decl_stmt|;
DECL|member|directinput8
name|LPDIRECTINPUT8W
name|directinput8
decl_stmt|;
DECL|member|error
name|GError
modifier|*
name|error
decl_stmt|;
block|}
struct|;
end_struct

begin_struct
DECL|struct|_GimpInputDeviceStoreClass
struct|struct
name|_GimpInputDeviceStoreClass
block|{
DECL|member|parent_class
name|GtkListStoreClass
name|parent_class
decl_stmt|;
DECL|member|device_added
name|void
function_decl|(
modifier|*
name|device_added
function_decl|)
parameter_list|(
name|GimpInputDeviceStore
modifier|*
name|store
parameter_list|,
specifier|const
name|gchar
modifier|*
name|udi
parameter_list|)
function_decl|;
DECL|member|device_removed
name|void
function_decl|(
modifier|*
name|device_removed
function_decl|)
parameter_list|(
name|GimpInputDeviceStore
modifier|*
name|store
parameter_list|,
specifier|const
name|gchar
modifier|*
name|udi
parameter_list|)
function_decl|;
block|}
struct|;
end_struct

begin_function_decl
specifier|static
name|void
name|gimp_input_device_store_finalize
parameter_list|(
name|GObject
modifier|*
name|object
parameter_list|)
function_decl|;
end_function_decl

begin_function_decl
specifier|static
name|gboolean
name|gimp_input_device_store_add
parameter_list|(
name|GimpInputDeviceStore
modifier|*
name|store
parameter_list|,
specifier|const
name|GUID
modifier|*
name|guid
parameter_list|)
function_decl|;
end_function_decl

begin_function_decl
specifier|static
name|gboolean
name|gimp_input_device_store_remove
parameter_list|(
name|GimpInputDeviceStore
modifier|*
name|store
parameter_list|,
specifier|const
name|gchar
modifier|*
name|udi
parameter_list|)
function_decl|;
end_function_decl

begin_macro
name|G_DEFINE_DYNAMIC_TYPE
argument_list|(
argument|GimpInputDeviceStore
argument_list|,
argument|gimp_input_device_store
argument_list|,
argument|GTK_TYPE_LIST_STORE
argument_list|)
end_macro

begin_decl_stmt
specifier|static
name|guint
name|store_signals
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
name|void
DECL|function|gimp_input_device_store_register_types (GTypeModule * module)
name|gimp_input_device_store_register_types
parameter_list|(
name|GTypeModule
modifier|*
name|module
parameter_list|)
block|{
name|gimp_input_device_store_register_type
argument_list|(
name|module
argument_list|)
expr_stmt|;
block|}
end_function

begin_function
specifier|static
name|void
DECL|function|gimp_input_device_store_class_init (GimpInputDeviceStoreClass * klass)
name|gimp_input_device_store_class_init
parameter_list|(
name|GimpInputDeviceStoreClass
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
name|store_signals
index|[
name|DEVICE_ADDED
index|]
operator|=
name|g_signal_new
argument_list|(
literal|"device-added"
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
name|GimpInputDeviceStoreClass
argument_list|,
name|device_added
argument_list|)
argument_list|,
name|NULL
argument_list|,
name|NULL
argument_list|,
name|g_cclosure_marshal_VOID__STRING
argument_list|,
name|G_TYPE_NONE
argument_list|,
literal|1
argument_list|,
name|G_TYPE_STRING
argument_list|)
expr_stmt|;
name|store_signals
index|[
name|DEVICE_REMOVED
index|]
operator|=
name|g_signal_new
argument_list|(
literal|"device-removed"
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
name|GimpInputDeviceStoreClass
argument_list|,
name|device_removed
argument_list|)
argument_list|,
name|NULL
argument_list|,
name|NULL
argument_list|,
name|g_cclosure_marshal_VOID__STRING
argument_list|,
name|G_TYPE_NONE
argument_list|,
literal|1
argument_list|,
name|G_TYPE_STRING
argument_list|)
expr_stmt|;
name|object_class
operator|->
name|finalize
operator|=
name|gimp_input_device_store_finalize
expr_stmt|;
name|klass
operator|->
name|device_added
operator|=
name|NULL
expr_stmt|;
name|klass
operator|->
name|device_removed
operator|=
name|NULL
expr_stmt|;
block|}
end_function

begin_function
specifier|static
name|void
DECL|function|gimp_input_device_store_class_finalize (GimpInputDeviceStoreClass * klass)
name|gimp_input_device_store_class_finalize
parameter_list|(
name|GimpInputDeviceStoreClass
modifier|*
name|klass
parameter_list|)
block|{ }
end_function

begin_function
specifier|static
name|GdkFilterReturn
DECL|function|aux_window_filter (GdkXEvent * xevent,GdkEvent * event,gpointer data)
name|aux_window_filter
parameter_list|(
name|GdkXEvent
modifier|*
name|xevent
parameter_list|,
name|GdkEvent
modifier|*
name|event
parameter_list|,
name|gpointer
name|data
parameter_list|)
block|{
name|GimpInputDeviceStore
modifier|*
name|store
init|=
operator|(
name|GimpInputDeviceStore
operator|*
operator|)
name|data
decl_stmt|;
specifier|const
name|MSG
modifier|*
name|msg
init|=
operator|(
name|MSG
operator|*
operator|)
name|xevent
decl_stmt|;
comment|/* Look for deviced being added or removed */
switch|switch
condition|(
name|msg
operator|->
name|message
condition|)
block|{     }
return|return
name|GDK_FILTER_REMOVE
return|;
block|}
end_function

begin_function
specifier|static
name|GdkWindow
modifier|*
DECL|function|create_aux_window (GimpInputDeviceStore * store)
name|create_aux_window
parameter_list|(
name|GimpInputDeviceStore
modifier|*
name|store
parameter_list|)
block|{
name|GdkWindowAttr
name|wa
decl_stmt|;
name|GdkWindow
modifier|*
name|retval
decl_stmt|;
comment|/* Create a dummy window to be associated with DirectInput devices */
name|wa
operator|.
name|wclass
operator|=
name|GDK_INPUT_OUTPUT
expr_stmt|;
name|wa
operator|.
name|event_mask
operator|=
name|GDK_ALL_EVENTS_MASK
expr_stmt|;
name|wa
operator|.
name|width
operator|=
literal|2
expr_stmt|;
name|wa
operator|.
name|height
operator|=
literal|2
expr_stmt|;
name|wa
operator|.
name|x
operator|=
operator|-
literal|100
expr_stmt|;
name|wa
operator|.
name|y
operator|=
operator|-
literal|100
expr_stmt|;
name|wa
operator|.
name|window_type
operator|=
name|GDK_WINDOW_TOPLEVEL
expr_stmt|;
if|if
condition|(
operator|(
name|retval
operator|=
name|gdk_window_new
argument_list|(
name|NULL
argument_list|,
operator|&
name|wa
argument_list|,
name|GDK_WA_X
operator||
name|GDK_WA_Y
argument_list|)
operator|)
operator|==
name|NULL
condition|)
return|return
name|NULL
return|;
name|g_object_ref
argument_list|(
name|retval
argument_list|)
expr_stmt|;
name|gdk_window_add_filter
argument_list|(
name|retval
argument_list|,
name|aux_window_filter
argument_list|,
name|store
argument_list|)
expr_stmt|;
return|return
name|retval
return|;
block|}
end_function

begin_function
specifier|static
name|BOOL
name|CALLBACK
DECL|function|enum_devices (const DIDEVICEINSTANCEW * di,void * user_data)
name|enum_devices
parameter_list|(
specifier|const
name|DIDEVICEINSTANCEW
modifier|*
name|di
parameter_list|,
name|void
modifier|*
name|user_data
parameter_list|)
block|{
name|GimpInputDeviceStore
modifier|*
name|store
init|=
operator|(
name|GimpInputDeviceStore
operator|*
operator|)
name|user_data
decl_stmt|;
name|gimp_input_device_store_add
argument_list|(
name|store
argument_list|,
operator|&
name|di
operator|->
name|guidInstance
argument_list|)
expr_stmt|;
return|return
name|DIENUM_CONTINUE
return|;
block|}
end_function

begin_function
specifier|static
name|void
DECL|function|gimp_input_device_store_init (GimpInputDeviceStore * store)
name|gimp_input_device_store_init
parameter_list|(
name|GimpInputDeviceStore
modifier|*
name|store
parameter_list|)
block|{
name|GType
name|types
index|[]
init|=
block|{
name|G_TYPE_STRING
block|,
name|G_TYPE_STRING
block|,
name|G_TYPE_POINTER
block|}
decl_stmt|;
name|HRESULT
name|hresult
decl_stmt|;
name|HMODULE
name|thismodule
decl_stmt|;
name|HMODULE
name|dinput8
decl_stmt|;
DECL|typedef|t_DirectInput8Create
typedef|typedef
name|HRESULT
function_decl|(
name|WINAPI
modifier|*
name|t_DirectInput8Create
function_decl|)
parameter_list|(
name|HINSTANCE
parameter_list|,
name|DWORD
parameter_list|,
name|REFIID
parameter_list|,
name|LPVOID
modifier|*
parameter_list|,
name|LPUNKNOWN
parameter_list|)
function_decl|;
name|t_DirectInput8Create
name|p_DirectInput8Create
decl_stmt|;
name|g_assert
argument_list|(
name|G_N_ELEMENTS
argument_list|(
name|types
argument_list|)
operator|==
name|NUM_COLUMNS
argument_list|)
expr_stmt|;
name|gtk_list_store_set_column_types
argument_list|(
name|GTK_LIST_STORE
argument_list|(
name|store
argument_list|)
argument_list|,
name|G_N_ELEMENTS
argument_list|(
name|types
argument_list|)
argument_list|,
name|types
argument_list|)
expr_stmt|;
if|if
condition|(
operator|!
name|GetModuleHandleEx
argument_list|(
name|GET_MODULE_HANDLE_EX_FLAG_FROM_ADDRESS
argument_list|,
operator|(
name|LPCTSTR
operator|)
operator|&
name|gimp_input_device_store_init
argument_list|,
operator|&
name|thismodule
argument_list|)
condition|)
return|return;
if|if
condition|(
operator|(
name|store
operator|->
name|window
operator|=
name|create_aux_window
argument_list|(
name|store
argument_list|)
operator|)
operator|==
name|NULL
condition|)
block|{
name|g_set_error_literal
argument_list|(
operator|&
name|store
operator|->
name|error
argument_list|,
name|GIMP_MODULE_ERROR
argument_list|,
name|GIMP_MODULE_FAILED
argument_list|,
literal|"Could not create aux window"
argument_list|)
expr_stmt|;
return|return;
block|}
if|if
condition|(
operator|(
name|dinput8
operator|=
name|LoadLibrary
argument_list|(
literal|"dinput8.dll"
argument_list|)
operator|)
operator|==
name|NULL
condition|)
block|{
name|g_set_error_literal
argument_list|(
operator|&
name|store
operator|->
name|error
argument_list|,
name|GIMP_MODULE_ERROR
argument_list|,
name|GIMP_MODULE_FAILED
argument_list|,
literal|"Could not load dinput8.dll"
argument_list|)
expr_stmt|;
return|return;
block|}
if|if
condition|(
operator|(
name|p_DirectInput8Create
operator|=
operator|(
name|t_DirectInput8Create
operator|)
name|GetProcAddress
argument_list|(
name|dinput8
argument_list|,
literal|"DirectInput8Create"
argument_list|)
operator|)
operator|==
name|NULL
condition|)
block|{
name|g_set_error_literal
argument_list|(
operator|&
name|store
operator|->
name|error
argument_list|,
name|GIMP_MODULE_ERROR
argument_list|,
name|GIMP_MODULE_FAILED
argument_list|,
literal|"Could not find DirectInput8Create in dinput8.dll"
argument_list|)
expr_stmt|;
return|return;
block|}
if|if
condition|(
name|FAILED
argument_list|(
operator|(
name|hresult
operator|=
call|(
modifier|*
name|p_DirectInput8Create
call|)
argument_list|(
name|thismodule
argument_list|,
name|DIRECTINPUT_VERSION
argument_list|,
operator|&
name|IID_IDirectInput8W
argument_list|,
operator|(
name|LPVOID
operator|*
operator|)
operator|&
name|store
operator|->
name|directinput8
argument_list|,
name|NULL
argument_list|)
operator|)
argument_list|)
condition|)
block|{
name|g_set_error
argument_list|(
operator|&
name|store
operator|->
name|error
argument_list|,
name|GIMP_MODULE_ERROR
argument_list|,
name|GIMP_MODULE_FAILED
argument_list|,
literal|"DirectInput8Create failed: %s"
argument_list|,
name|g_win32_error_message
argument_list|(
name|hresult
argument_list|)
argument_list|)
expr_stmt|;
return|return;
block|}
if|if
condition|(
name|FAILED
argument_list|(
operator|(
name|hresult
operator|=
name|IDirectInput8_EnumDevices
argument_list|(
name|store
operator|->
name|directinput8
argument_list|,
name|DI8DEVCLASS_GAMECTRL
argument_list|,
name|enum_devices
argument_list|,
name|store
argument_list|,
name|DIEDFL_ATTACHEDONLY
argument_list|)
operator|)
argument_list|)
condition|)
block|{
name|g_set_error
argument_list|(
operator|&
name|store
operator|->
name|error
argument_list|,
name|GIMP_MODULE_ERROR
argument_list|,
name|GIMP_MODULE_FAILED
argument_list|,
literal|"IDirectInput8::EnumDevices failed: %s"
argument_list|,
name|g_win32_error_message
argument_list|(
name|hresult
argument_list|)
argument_list|)
expr_stmt|;
return|return;
block|}
block|}
end_function

begin_function
specifier|static
name|void
DECL|function|gimp_input_device_store_finalize (GObject * object)
name|gimp_input_device_store_finalize
parameter_list|(
name|GObject
modifier|*
name|object
parameter_list|)
block|{
name|GimpInputDeviceStore
modifier|*
name|store
init|=
name|GIMP_INPUT_DEVICE_STORE
argument_list|(
name|object
argument_list|)
decl_stmt|;
if|if
condition|(
name|store
operator|->
name|directinput8
condition|)
block|{
name|IDirectInput8_Release
argument_list|(
name|store
operator|->
name|directinput8
argument_list|)
expr_stmt|;
name|store
operator|->
name|directinput8
operator|=
name|NULL
expr_stmt|;
block|}
if|if
condition|(
name|store
operator|->
name|error
condition|)
block|{
name|g_error_free
argument_list|(
name|store
operator|->
name|error
argument_list|)
expr_stmt|;
name|store
operator|->
name|error
operator|=
name|NULL
expr_stmt|;
block|}
name|G_OBJECT_CLASS
argument_list|(
name|gimp_input_device_store_parent_class
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
name|gboolean
DECL|function|gimp_input_device_store_lookup (GimpInputDeviceStore * store,const gchar * guid,GtkTreeIter * iter)
name|gimp_input_device_store_lookup
parameter_list|(
name|GimpInputDeviceStore
modifier|*
name|store
parameter_list|,
specifier|const
name|gchar
modifier|*
name|guid
parameter_list|,
name|GtkTreeIter
modifier|*
name|iter
parameter_list|)
block|{
name|GtkTreeModel
modifier|*
name|model
init|=
name|GTK_TREE_MODEL
argument_list|(
name|store
argument_list|)
decl_stmt|;
name|GValue
name|value
init|=
block|{
literal|0
block|, }
decl_stmt|;
name|gboolean
name|iter_valid
decl_stmt|;
for|for
control|(
name|iter_valid
operator|=
name|gtk_tree_model_get_iter_first
argument_list|(
name|model
argument_list|,
name|iter
argument_list|)
init|;
name|iter_valid
condition|;
name|iter_valid
operator|=
name|gtk_tree_model_iter_next
argument_list|(
name|model
argument_list|,
name|iter
argument_list|)
control|)
block|{
specifier|const
name|gchar
modifier|*
name|str
decl_stmt|;
name|gtk_tree_model_get_value
argument_list|(
name|model
argument_list|,
name|iter
argument_list|,
name|COLUMN_GUID
argument_list|,
operator|&
name|value
argument_list|)
expr_stmt|;
name|str
operator|=
name|g_value_get_string
argument_list|(
operator|&
name|value
argument_list|)
expr_stmt|;
if|if
condition|(
name|strcmp
argument_list|(
name|str
argument_list|,
name|guid
argument_list|)
operator|==
literal|0
condition|)
block|{
name|g_value_unset
argument_list|(
operator|&
name|value
argument_list|)
expr_stmt|;
break|break;
block|}
name|g_value_unset
argument_list|(
operator|&
name|value
argument_list|)
expr_stmt|;
block|}
return|return
name|iter_valid
return|;
block|}
end_function

begin_comment
comment|/*  insert in alphabetic order  */
end_comment

begin_function
specifier|static
name|void
DECL|function|gimp_input_device_store_insert (GimpInputDeviceStore * store,const gchar * guid,const gchar * label,LPDIRECTINPUTDEVICE8W didevice8)
name|gimp_input_device_store_insert
parameter_list|(
name|GimpInputDeviceStore
modifier|*
name|store
parameter_list|,
specifier|const
name|gchar
modifier|*
name|guid
parameter_list|,
specifier|const
name|gchar
modifier|*
name|label
parameter_list|,
name|LPDIRECTINPUTDEVICE8W
name|didevice8
parameter_list|)
block|{
name|GtkTreeModel
modifier|*
name|model
init|=
name|GTK_TREE_MODEL
argument_list|(
name|store
argument_list|)
decl_stmt|;
name|GtkTreeIter
name|iter
decl_stmt|;
name|GValue
name|value
init|=
block|{
literal|0
block|, }
decl_stmt|;
name|gint
name|pos
init|=
literal|0
decl_stmt|;
name|gboolean
name|iter_valid
decl_stmt|;
for|for
control|(
name|iter_valid
operator|=
name|gtk_tree_model_get_iter_first
argument_list|(
name|model
argument_list|,
operator|&
name|iter
argument_list|)
init|;
name|iter_valid
condition|;
name|iter_valid
operator|=
name|gtk_tree_model_iter_next
argument_list|(
name|model
argument_list|,
operator|&
name|iter
argument_list|)
operator|,
name|pos
operator|++
control|)
block|{
specifier|const
name|gchar
modifier|*
name|str
decl_stmt|;
name|gtk_tree_model_get_value
argument_list|(
name|model
argument_list|,
operator|&
name|iter
argument_list|,
name|COLUMN_LABEL
argument_list|,
operator|&
name|value
argument_list|)
expr_stmt|;
name|str
operator|=
name|g_value_get_string
argument_list|(
operator|&
name|value
argument_list|)
expr_stmt|;
if|if
condition|(
name|g_utf8_collate
argument_list|(
name|label
argument_list|,
name|str
argument_list|)
operator|<
literal|0
condition|)
block|{
name|g_value_unset
argument_list|(
operator|&
name|value
argument_list|)
expr_stmt|;
break|break;
block|}
name|g_value_unset
argument_list|(
operator|&
name|value
argument_list|)
expr_stmt|;
block|}
name|gtk_list_store_insert_with_values
argument_list|(
name|GTK_LIST_STORE
argument_list|(
name|store
argument_list|)
argument_list|,
operator|&
name|iter
argument_list|,
name|pos
argument_list|,
name|COLUMN_GUID
argument_list|,
name|guid
argument_list|,
name|COLUMN_LABEL
argument_list|,
name|label
argument_list|,
name|COLUMN_IDEVICE
argument_list|,
name|didevice8
argument_list|,
operator|-
literal|1
argument_list|)
expr_stmt|;
block|}
end_function

begin_function
specifier|static
name|gboolean
DECL|function|gimp_input_device_store_add (GimpInputDeviceStore * store,const GUID * guid)
name|gimp_input_device_store_add
parameter_list|(
name|GimpInputDeviceStore
modifier|*
name|store
parameter_list|,
specifier|const
name|GUID
modifier|*
name|guid
parameter_list|)
block|{
name|HRESULT
name|hresult
decl_stmt|;
name|LPDIRECTINPUTDEVICE8W
name|didevice8
decl_stmt|;
name|DIDEVICEINSTANCEW
name|di
decl_stmt|;
name|gboolean
name|added
init|=
name|FALSE
decl_stmt|;
name|unsigned
name|char
modifier|*
name|s
decl_stmt|;
name|gchar
modifier|*
name|guidstring
decl_stmt|;
name|gchar
modifier|*
name|name
decl_stmt|;
if|if
condition|(
name|UuidToString
argument_list|(
name|guid
argument_list|,
operator|&
name|s
argument_list|)
operator|!=
name|S_OK
condition|)
return|return
name|FALSE
return|;
name|guidstring
operator|=
name|g_strdup
argument_list|(
name|s
argument_list|)
expr_stmt|;
name|RpcStringFree
argument_list|(
operator|&
name|s
argument_list|)
expr_stmt|;
if|if
condition|(
name|FAILED
argument_list|(
operator|(
name|hresult
operator|=
name|IDirectInput8_CreateDevice
argument_list|(
name|store
operator|->
name|directinput8
argument_list|,
name|guid
argument_list|,
operator|&
name|didevice8
argument_list|,
name|NULL
argument_list|)
operator|)
argument_list|)
condition|)
block|{
name|g_free
argument_list|(
name|guidstring
argument_list|)
expr_stmt|;
return|return
name|FALSE
return|;
block|}
if|if
condition|(
name|FAILED
argument_list|(
operator|(
name|hresult
operator|=
name|IDirectInputDevice8_SetCooperativeLevel
argument_list|(
name|didevice8
argument_list|,
operator|(
name|HWND
operator|)
name|gdk_win32_drawable_get_handle
argument_list|(
name|store
operator|->
name|window
argument_list|)
argument_list|,
name|DISCL_NONEXCLUSIVE
operator||
name|DISCL_BACKGROUND
argument_list|)
operator|)
argument_list|)
condition|)
block|{
name|g_warning
argument_list|(
literal|"IDirectInputDevice8::SetCooperativeLevel failed: %s"
argument_list|,
name|g_win32_error_message
argument_list|(
name|hresult
argument_list|)
argument_list|)
expr_stmt|;
name|g_free
argument_list|(
name|guidstring
argument_list|)
expr_stmt|;
return|return
name|FALSE
return|;
block|}
name|di
operator|.
name|dwSize
operator|=
sizeof|sizeof
argument_list|(
name|DIDEVICEINSTANCEW
argument_list|)
expr_stmt|;
if|if
condition|(
name|FAILED
argument_list|(
operator|(
name|hresult
operator|=
name|IDirectInputDevice8_GetDeviceInfo
argument_list|(
name|didevice8
argument_list|,
operator|&
name|di
argument_list|)
operator|)
argument_list|)
condition|)
block|{
name|g_warning
argument_list|(
literal|"IDirectInputDevice8::GetDeviceInfo failed: %s"
argument_list|,
name|g_win32_error_message
argument_list|(
name|hresult
argument_list|)
argument_list|)
expr_stmt|;
name|g_free
argument_list|(
name|guidstring
argument_list|)
expr_stmt|;
return|return
name|FALSE
return|;
block|}
name|name
operator|=
name|g_utf16_to_utf8
argument_list|(
name|di
operator|.
name|tszInstanceName
argument_list|,
operator|-
literal|1
argument_list|,
name|NULL
argument_list|,
name|NULL
argument_list|,
name|NULL
argument_list|)
expr_stmt|;
name|gimp_input_device_store_insert
argument_list|(
name|store
argument_list|,
name|guidstring
argument_list|,
name|name
argument_list|,
name|didevice8
argument_list|)
expr_stmt|;
return|return
name|added
return|;
block|}
end_function

begin_function
specifier|static
name|gboolean
DECL|function|gimp_input_device_store_remove (GimpInputDeviceStore * store,const gchar * guid)
name|gimp_input_device_store_remove
parameter_list|(
name|GimpInputDeviceStore
modifier|*
name|store
parameter_list|,
specifier|const
name|gchar
modifier|*
name|guid
parameter_list|)
block|{
name|GtkTreeIter
name|iter
decl_stmt|;
if|if
condition|(
name|gimp_input_device_store_lookup
argument_list|(
name|store
argument_list|,
name|guid
argument_list|,
operator|&
name|iter
argument_list|)
condition|)
block|{
name|gtk_list_store_remove
argument_list|(
name|GTK_LIST_STORE
argument_list|(
name|store
argument_list|)
argument_list|,
operator|&
name|iter
argument_list|)
expr_stmt|;
return|return
name|TRUE
return|;
block|}
return|return
name|FALSE
return|;
block|}
end_function

begin_if
if|#
directive|if
literal|0
end_if

begin_endif
unit|static void gimp_input_device_store_device_added (LibHalContext *ctx,                                       const char    *guid) {   GimpInputDeviceStore *store = libhal_ctx_get_user_data (ctx);    if (gimp_input_device_store_add (store, udi))     {       g_signal_emit (store, store_signals[DEVICE_ADDED], 0, udi);     } }  static void gimp_input_device_store_device_removed (LibHalContext *ctx,                                         const char    *udi) {   GimpInputDeviceStore *store = libhal_ctx_get_user_data (ctx);    if (gimp_input_device_store_remove (store, udi))     {       g_signal_emit (store, store_signals[DEVICE_REMOVED], 0, udi);     } }
endif|#
directive|endif
end_endif

begin_function
name|GimpInputDeviceStore
modifier|*
DECL|function|gimp_input_device_store_new (void)
name|gimp_input_device_store_new
parameter_list|(
name|void
parameter_list|)
block|{
return|return
name|g_object_new
argument_list|(
name|GIMP_TYPE_INPUT_DEVICE_STORE
argument_list|,
name|NULL
argument_list|)
return|;
block|}
end_function

begin_function
name|gchar
modifier|*
DECL|function|gimp_input_device_store_get_device_file (GimpInputDeviceStore * store,const gchar * udi)
name|gimp_input_device_store_get_device_file
parameter_list|(
name|GimpInputDeviceStore
modifier|*
name|store
parameter_list|,
specifier|const
name|gchar
modifier|*
name|udi
parameter_list|)
block|{
name|GtkTreeIter
name|iter
decl_stmt|;
name|GValue
name|value
init|=
block|{
literal|0
block|, }
decl_stmt|;
name|g_return_val_if_fail
argument_list|(
name|GIMP_IS_INPUT_DEVICE_STORE
argument_list|(
name|store
argument_list|)
argument_list|,
name|NULL
argument_list|)
expr_stmt|;
name|g_return_val_if_fail
argument_list|(
name|udi
operator|!=
name|NULL
argument_list|,
name|NULL
argument_list|)
expr_stmt|;
if|if
condition|(
operator|!
name|store
operator|->
name|directinput8
condition|)
return|return
name|NULL
return|;
if|if
condition|(
name|gimp_input_device_store_lookup
argument_list|(
name|store
argument_list|,
name|udi
argument_list|,
operator|&
name|iter
argument_list|)
condition|)
block|{
name|gtk_tree_model_get_value
argument_list|(
name|GTK_TREE_MODEL
argument_list|(
name|store
argument_list|)
argument_list|,
operator|&
name|iter
argument_list|,
name|COLUMN_IDEVICE
argument_list|,
operator|&
name|value
argument_list|)
expr_stmt|;
return|return
name|g_value_get_pointer
argument_list|(
operator|&
name|value
argument_list|)
return|;
block|}
return|return
name|NULL
return|;
block|}
end_function

begin_function
name|GError
modifier|*
DECL|function|gimp_input_device_store_get_error (GimpInputDeviceStore * store)
name|gimp_input_device_store_get_error
parameter_list|(
name|GimpInputDeviceStore
modifier|*
name|store
parameter_list|)
block|{
name|g_return_val_if_fail
argument_list|(
name|GIMP_IS_INPUT_DEVICE_STORE
argument_list|(
name|store
argument_list|)
argument_list|,
name|NULL
argument_list|)
expr_stmt|;
return|return
name|store
operator|->
name|error
condition|?
name|g_error_copy
argument_list|(
name|store
operator|->
name|error
argument_list|)
else|:
name|NULL
return|;
block|}
end_function

begin_endif
endif|#
directive|endif
end_endif

begin_comment
comment|/* HAVE_DX_DINPUT */
end_comment

end_unit

