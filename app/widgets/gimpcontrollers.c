begin_unit|revision:0.9.5;language:C;cregit-version:0.0.1
begin_comment
comment|/* GIMP - The GNU Image Manipulation Program  * Copyright (C) 1995 Spencer Kimball and Peter Mattis  *  * This program is free software: you can redistribute it and/or modify  * it under the terms of the GNU General Public License as published by  * the Free Software Foundation; either version 3 of the License, or  * (at your option) any later version.  *  * This program is distributed in the hope that it will be useful,  * but WITHOUT ANY WARRANTY; without even the implied warranty of  * MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the  * GNU General Public License for more details.  *  * You should have received a copy of the GNU General Public License  * along with this program.  If not, see<https://www.gnu.org/licenses/>.  */
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
file|"libgimpconfig/gimpconfig.h"
end_include

begin_include
include|#
directive|include
file|"libgimpwidgets/gimpwidgets.h"
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
file|"libgimpwidgets/gimpcontroller.h"
end_include

begin_include
include|#
directive|include
file|"widgets-types.h"
end_include

begin_include
include|#
directive|include
file|"core/gimp.h"
end_include

begin_include
include|#
directive|include
file|"core/gimplist.h"
end_include

begin_include
include|#
directive|include
file|"gimpaction.h"
end_include

begin_include
include|#
directive|include
file|"gimpactiongroup.h"
end_include

begin_include
include|#
directive|include
file|"gimpcontrollerinfo.h"
end_include

begin_include
include|#
directive|include
file|"gimpcontrollers.h"
end_include

begin_include
include|#
directive|include
file|"gimpcontrollerkeyboard.h"
end_include

begin_include
include|#
directive|include
file|"gimpcontrollermouse.h"
end_include

begin_include
include|#
directive|include
file|"gimpcontrollerwheel.h"
end_include

begin_include
include|#
directive|include
file|"gimpenumaction.h"
end_include

begin_include
include|#
directive|include
file|"gimpuimanager.h"
end_include

begin_include
include|#
directive|include
file|"gimp-intl.h"
end_include

begin_define
DECL|macro|GIMP_CONTROLLER_MANAGER_DATA_KEY
define|#
directive|define
name|GIMP_CONTROLLER_MANAGER_DATA_KEY
value|"gimp-controller-manager"
end_define

begin_typedef
DECL|typedef|GimpControllerManager
typedef|typedef
name|struct
name|_GimpControllerManager
name|GimpControllerManager
typedef|;
end_typedef

begin_struct
DECL|struct|_GimpControllerManager
struct|struct
name|_GimpControllerManager
block|{
DECL|member|controllers
name|GimpContainer
modifier|*
name|controllers
decl_stmt|;
DECL|member|event_mapped_id
name|GQuark
name|event_mapped_id
decl_stmt|;
DECL|member|mouse
name|GimpController
modifier|*
name|mouse
decl_stmt|;
DECL|member|wheel
name|GimpController
modifier|*
name|wheel
decl_stmt|;
DECL|member|keyboard
name|GimpController
modifier|*
name|keyboard
decl_stmt|;
DECL|member|ui_manager
name|GimpUIManager
modifier|*
name|ui_manager
decl_stmt|;
block|}
struct|;
end_struct

begin_comment
comment|/*  local function prototypes  */
end_comment

begin_function_decl
specifier|static
name|GimpControllerManager
modifier|*
name|gimp_controller_manager_get
parameter_list|(
name|Gimp
modifier|*
name|gimp
parameter_list|)
function_decl|;
end_function_decl

begin_function_decl
specifier|static
name|void
name|gimp_controller_manager_free
parameter_list|(
name|GimpControllerManager
modifier|*
name|manager
parameter_list|)
function_decl|;
end_function_decl

begin_function_decl
specifier|static
name|void
name|gimp_controllers_add
parameter_list|(
name|GimpContainer
modifier|*
name|container
parameter_list|,
name|GimpControllerInfo
modifier|*
name|info
parameter_list|,
name|GimpControllerManager
modifier|*
name|manager
parameter_list|)
function_decl|;
end_function_decl

begin_function_decl
specifier|static
name|void
name|gimp_controllers_remove
parameter_list|(
name|GimpContainer
modifier|*
name|container
parameter_list|,
name|GimpControllerInfo
modifier|*
name|info
parameter_list|,
name|GimpControllerManager
modifier|*
name|manager
parameter_list|)
function_decl|;
end_function_decl

begin_function_decl
specifier|static
name|gboolean
name|gimp_controllers_event_mapped
parameter_list|(
name|GimpControllerInfo
modifier|*
name|info
parameter_list|,
name|GimpController
modifier|*
name|controller
parameter_list|,
specifier|const
name|GimpControllerEvent
modifier|*
name|event
parameter_list|,
specifier|const
name|gchar
modifier|*
name|action_name
parameter_list|,
name|GimpControllerManager
modifier|*
name|manager
parameter_list|)
function_decl|;
end_function_decl

begin_comment
comment|/*  public functions  */
end_comment

begin_function
name|void
DECL|function|gimp_controllers_init (Gimp * gimp)
name|gimp_controllers_init
parameter_list|(
name|Gimp
modifier|*
name|gimp
parameter_list|)
block|{
name|GimpControllerManager
modifier|*
name|manager
decl_stmt|;
name|g_return_if_fail
argument_list|(
name|GIMP_IS_GIMP
argument_list|(
name|gimp
argument_list|)
argument_list|)
expr_stmt|;
name|g_return_if_fail
argument_list|(
name|gimp_controller_manager_get
argument_list|(
name|gimp
argument_list|)
operator|==
name|NULL
argument_list|)
expr_stmt|;
name|manager
operator|=
name|g_slice_new0
argument_list|(
name|GimpControllerManager
argument_list|)
expr_stmt|;
name|g_object_set_data_full
argument_list|(
name|G_OBJECT
argument_list|(
name|gimp
argument_list|)
argument_list|,
name|GIMP_CONTROLLER_MANAGER_DATA_KEY
argument_list|,
name|manager
argument_list|,
operator|(
name|GDestroyNotify
operator|)
name|gimp_controller_manager_free
argument_list|)
expr_stmt|;
name|manager
operator|->
name|controllers
operator|=
name|gimp_list_new
argument_list|(
name|GIMP_TYPE_CONTROLLER_INFO
argument_list|,
name|TRUE
argument_list|)
expr_stmt|;
name|g_signal_connect
argument_list|(
name|manager
operator|->
name|controllers
argument_list|,
literal|"add"
argument_list|,
name|G_CALLBACK
argument_list|(
name|gimp_controllers_add
argument_list|)
argument_list|,
name|manager
argument_list|)
expr_stmt|;
name|g_signal_connect
argument_list|(
name|manager
operator|->
name|controllers
argument_list|,
literal|"remove"
argument_list|,
name|G_CALLBACK
argument_list|(
name|gimp_controllers_remove
argument_list|)
argument_list|,
name|manager
argument_list|)
expr_stmt|;
name|manager
operator|->
name|event_mapped_id
operator|=
name|gimp_container_add_handler
argument_list|(
name|manager
operator|->
name|controllers
argument_list|,
literal|"event-mapped"
argument_list|,
name|G_CALLBACK
argument_list|(
name|gimp_controllers_event_mapped
argument_list|)
argument_list|,
name|manager
argument_list|)
expr_stmt|;
name|g_type_class_ref
argument_list|(
name|GIMP_TYPE_CONTROLLER_MOUSE
argument_list|)
expr_stmt|;
name|g_type_class_ref
argument_list|(
name|GIMP_TYPE_CONTROLLER_WHEEL
argument_list|)
expr_stmt|;
name|g_type_class_ref
argument_list|(
name|GIMP_TYPE_CONTROLLER_KEYBOARD
argument_list|)
expr_stmt|;
block|}
end_function

begin_function
name|void
DECL|function|gimp_controllers_exit (Gimp * gimp)
name|gimp_controllers_exit
parameter_list|(
name|Gimp
modifier|*
name|gimp
parameter_list|)
block|{
name|g_return_if_fail
argument_list|(
name|GIMP_IS_GIMP
argument_list|(
name|gimp
argument_list|)
argument_list|)
expr_stmt|;
name|g_return_if_fail
argument_list|(
name|gimp_controller_manager_get
argument_list|(
name|gimp
argument_list|)
operator|!=
name|NULL
argument_list|)
expr_stmt|;
name|g_object_set_data
argument_list|(
name|G_OBJECT
argument_list|(
name|gimp
argument_list|)
argument_list|,
name|GIMP_CONTROLLER_MANAGER_DATA_KEY
argument_list|,
name|NULL
argument_list|)
expr_stmt|;
name|g_type_class_unref
argument_list|(
name|g_type_class_peek
argument_list|(
name|GIMP_TYPE_CONTROLLER_WHEEL
argument_list|)
argument_list|)
expr_stmt|;
name|g_type_class_unref
argument_list|(
name|g_type_class_peek
argument_list|(
name|GIMP_TYPE_CONTROLLER_KEYBOARD
argument_list|)
argument_list|)
expr_stmt|;
block|}
end_function

begin_function
name|void
DECL|function|gimp_controllers_restore (Gimp * gimp,GimpUIManager * ui_manager)
name|gimp_controllers_restore
parameter_list|(
name|Gimp
modifier|*
name|gimp
parameter_list|,
name|GimpUIManager
modifier|*
name|ui_manager
parameter_list|)
block|{
name|GimpControllerManager
modifier|*
name|manager
decl_stmt|;
name|GFile
modifier|*
name|file
decl_stmt|;
name|GError
modifier|*
name|error
init|=
name|NULL
decl_stmt|;
name|g_return_if_fail
argument_list|(
name|GIMP_IS_GIMP
argument_list|(
name|gimp
argument_list|)
argument_list|)
expr_stmt|;
name|g_return_if_fail
argument_list|(
name|GIMP_IS_UI_MANAGER
argument_list|(
name|ui_manager
argument_list|)
argument_list|)
expr_stmt|;
name|manager
operator|=
name|gimp_controller_manager_get
argument_list|(
name|gimp
argument_list|)
expr_stmt|;
name|g_return_if_fail
argument_list|(
name|manager
operator|!=
name|NULL
argument_list|)
expr_stmt|;
name|g_return_if_fail
argument_list|(
name|manager
operator|->
name|ui_manager
operator|==
name|NULL
argument_list|)
expr_stmt|;
name|manager
operator|->
name|ui_manager
operator|=
name|g_object_ref
argument_list|(
name|ui_manager
argument_list|)
expr_stmt|;
name|file
operator|=
name|gimp_directory_file
argument_list|(
literal|"controllerrc"
argument_list|,
name|NULL
argument_list|)
expr_stmt|;
if|if
condition|(
name|gimp
operator|->
name|be_verbose
condition|)
name|g_print
argument_list|(
literal|"Parsing '%s'\n"
argument_list|,
name|gimp_file_get_utf8_name
argument_list|(
name|file
argument_list|)
argument_list|)
expr_stmt|;
if|if
condition|(
operator|!
name|gimp_config_deserialize_gfile
argument_list|(
name|GIMP_CONFIG
argument_list|(
name|manager
operator|->
name|controllers
argument_list|)
argument_list|,
name|file
argument_list|,
name|NULL
argument_list|,
operator|&
name|error
argument_list|)
condition|)
block|{
if|if
condition|(
name|error
operator|->
name|code
operator|==
name|GIMP_CONFIG_ERROR_OPEN_ENOENT
condition|)
block|{
name|g_clear_error
argument_list|(
operator|&
name|error
argument_list|)
expr_stmt|;
name|g_object_unref
argument_list|(
name|file
argument_list|)
expr_stmt|;
name|file
operator|=
name|gimp_sysconf_directory_file
argument_list|(
literal|"controllerrc"
argument_list|,
name|NULL
argument_list|)
expr_stmt|;
if|if
condition|(
operator|!
name|gimp_config_deserialize_gfile
argument_list|(
name|GIMP_CONFIG
argument_list|(
name|manager
operator|->
name|controllers
argument_list|)
argument_list|,
name|file
argument_list|,
name|NULL
argument_list|,
operator|&
name|error
argument_list|)
condition|)
block|{
name|gimp_message_literal
argument_list|(
name|gimp
argument_list|,
name|NULL
argument_list|,
name|GIMP_MESSAGE_ERROR
argument_list|,
name|error
operator|->
name|message
argument_list|)
expr_stmt|;
block|}
block|}
else|else
block|{
name|gimp_message_literal
argument_list|(
name|gimp
argument_list|,
name|NULL
argument_list|,
name|GIMP_MESSAGE_ERROR
argument_list|,
name|error
operator|->
name|message
argument_list|)
expr_stmt|;
block|}
name|g_clear_error
argument_list|(
operator|&
name|error
argument_list|)
expr_stmt|;
block|}
name|gimp_list_reverse
argument_list|(
name|GIMP_LIST
argument_list|(
name|manager
operator|->
name|controllers
argument_list|)
argument_list|)
expr_stmt|;
name|g_object_unref
argument_list|(
name|file
argument_list|)
expr_stmt|;
block|}
end_function

begin_function
name|void
DECL|function|gimp_controllers_save (Gimp * gimp)
name|gimp_controllers_save
parameter_list|(
name|Gimp
modifier|*
name|gimp
parameter_list|)
block|{
specifier|const
name|gchar
modifier|*
name|header
init|=
literal|"GIMP controllerrc\n"
literal|"\n"
literal|"This file will be entirely rewritten each time you exit."
decl_stmt|;
specifier|const
name|gchar
modifier|*
name|footer
init|=
literal|"end of controllerrc"
decl_stmt|;
name|GimpControllerManager
modifier|*
name|manager
decl_stmt|;
name|GFile
modifier|*
name|file
decl_stmt|;
name|GError
modifier|*
name|error
init|=
name|NULL
decl_stmt|;
name|g_return_if_fail
argument_list|(
name|GIMP_IS_GIMP
argument_list|(
name|gimp
argument_list|)
argument_list|)
expr_stmt|;
name|manager
operator|=
name|gimp_controller_manager_get
argument_list|(
name|gimp
argument_list|)
expr_stmt|;
name|g_return_if_fail
argument_list|(
name|manager
operator|!=
name|NULL
argument_list|)
expr_stmt|;
name|file
operator|=
name|gimp_directory_file
argument_list|(
literal|"controllerrc"
argument_list|,
name|NULL
argument_list|)
expr_stmt|;
if|if
condition|(
name|gimp
operator|->
name|be_verbose
condition|)
name|g_print
argument_list|(
literal|"Writing '%s'\n"
argument_list|,
name|gimp_file_get_utf8_name
argument_list|(
name|file
argument_list|)
argument_list|)
expr_stmt|;
if|if
condition|(
operator|!
name|gimp_config_serialize_to_gfile
argument_list|(
name|GIMP_CONFIG
argument_list|(
name|manager
operator|->
name|controllers
argument_list|)
argument_list|,
name|file
argument_list|,
name|header
argument_list|,
name|footer
argument_list|,
name|NULL
argument_list|,
operator|&
name|error
argument_list|)
condition|)
block|{
name|gimp_message_literal
argument_list|(
name|gimp
argument_list|,
name|NULL
argument_list|,
name|GIMP_MESSAGE_ERROR
argument_list|,
name|error
operator|->
name|message
argument_list|)
expr_stmt|;
name|g_error_free
argument_list|(
name|error
argument_list|)
expr_stmt|;
block|}
name|g_object_unref
argument_list|(
name|file
argument_list|)
expr_stmt|;
block|}
end_function

begin_function
name|GimpContainer
modifier|*
DECL|function|gimp_controllers_get_list (Gimp * gimp)
name|gimp_controllers_get_list
parameter_list|(
name|Gimp
modifier|*
name|gimp
parameter_list|)
block|{
name|GimpControllerManager
modifier|*
name|manager
decl_stmt|;
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
name|manager
operator|=
name|gimp_controller_manager_get
argument_list|(
name|gimp
argument_list|)
expr_stmt|;
name|g_return_val_if_fail
argument_list|(
name|manager
operator|!=
name|NULL
argument_list|,
name|NULL
argument_list|)
expr_stmt|;
return|return
name|manager
operator|->
name|controllers
return|;
block|}
end_function

begin_function
name|GimpUIManager
modifier|*
DECL|function|gimp_controllers_get_ui_manager (Gimp * gimp)
name|gimp_controllers_get_ui_manager
parameter_list|(
name|Gimp
modifier|*
name|gimp
parameter_list|)
block|{
name|GimpControllerManager
modifier|*
name|manager
decl_stmt|;
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
name|manager
operator|=
name|gimp_controller_manager_get
argument_list|(
name|gimp
argument_list|)
expr_stmt|;
name|g_return_val_if_fail
argument_list|(
name|manager
operator|!=
name|NULL
argument_list|,
name|NULL
argument_list|)
expr_stmt|;
return|return
name|manager
operator|->
name|ui_manager
return|;
block|}
end_function

begin_function
name|GimpController
modifier|*
DECL|function|gimp_controllers_get_mouse (Gimp * gimp)
name|gimp_controllers_get_mouse
parameter_list|(
name|Gimp
modifier|*
name|gimp
parameter_list|)
block|{
name|GimpControllerManager
modifier|*
name|manager
decl_stmt|;
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
name|manager
operator|=
name|gimp_controller_manager_get
argument_list|(
name|gimp
argument_list|)
expr_stmt|;
name|g_return_val_if_fail
argument_list|(
name|manager
operator|!=
name|NULL
argument_list|,
name|NULL
argument_list|)
expr_stmt|;
return|return
name|manager
operator|->
name|mouse
return|;
block|}
end_function

begin_function
name|GimpController
modifier|*
DECL|function|gimp_controllers_get_wheel (Gimp * gimp)
name|gimp_controllers_get_wheel
parameter_list|(
name|Gimp
modifier|*
name|gimp
parameter_list|)
block|{
name|GimpControllerManager
modifier|*
name|manager
decl_stmt|;
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
name|manager
operator|=
name|gimp_controller_manager_get
argument_list|(
name|gimp
argument_list|)
expr_stmt|;
name|g_return_val_if_fail
argument_list|(
name|manager
operator|!=
name|NULL
argument_list|,
name|NULL
argument_list|)
expr_stmt|;
return|return
name|manager
operator|->
name|wheel
return|;
block|}
end_function

begin_function
name|GimpController
modifier|*
DECL|function|gimp_controllers_get_keyboard (Gimp * gimp)
name|gimp_controllers_get_keyboard
parameter_list|(
name|Gimp
modifier|*
name|gimp
parameter_list|)
block|{
name|GimpControllerManager
modifier|*
name|manager
decl_stmt|;
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
name|manager
operator|=
name|gimp_controller_manager_get
argument_list|(
name|gimp
argument_list|)
expr_stmt|;
name|g_return_val_if_fail
argument_list|(
name|manager
operator|!=
name|NULL
argument_list|,
name|NULL
argument_list|)
expr_stmt|;
return|return
name|manager
operator|->
name|keyboard
return|;
block|}
end_function

begin_comment
comment|/*  private functions  */
end_comment

begin_function
specifier|static
name|GimpControllerManager
modifier|*
DECL|function|gimp_controller_manager_get (Gimp * gimp)
name|gimp_controller_manager_get
parameter_list|(
name|Gimp
modifier|*
name|gimp
parameter_list|)
block|{
return|return
name|g_object_get_data
argument_list|(
name|G_OBJECT
argument_list|(
name|gimp
argument_list|)
argument_list|,
name|GIMP_CONTROLLER_MANAGER_DATA_KEY
argument_list|)
return|;
block|}
end_function

begin_function
specifier|static
name|void
DECL|function|gimp_controller_manager_free (GimpControllerManager * manager)
name|gimp_controller_manager_free
parameter_list|(
name|GimpControllerManager
modifier|*
name|manager
parameter_list|)
block|{
name|gimp_container_remove_handler
argument_list|(
name|manager
operator|->
name|controllers
argument_list|,
name|manager
operator|->
name|event_mapped_id
argument_list|)
expr_stmt|;
name|g_clear_object
argument_list|(
operator|&
name|manager
operator|->
name|controllers
argument_list|)
expr_stmt|;
name|g_clear_object
argument_list|(
operator|&
name|manager
operator|->
name|ui_manager
argument_list|)
expr_stmt|;
name|g_slice_free
argument_list|(
name|GimpControllerManager
argument_list|,
name|manager
argument_list|)
expr_stmt|;
block|}
end_function

begin_function
specifier|static
name|void
DECL|function|gimp_controllers_add (GimpContainer * container,GimpControllerInfo * info,GimpControllerManager * manager)
name|gimp_controllers_add
parameter_list|(
name|GimpContainer
modifier|*
name|container
parameter_list|,
name|GimpControllerInfo
modifier|*
name|info
parameter_list|,
name|GimpControllerManager
modifier|*
name|manager
parameter_list|)
block|{
if|if
condition|(
name|GIMP_IS_CONTROLLER_WHEEL
argument_list|(
name|info
operator|->
name|controller
argument_list|)
condition|)
name|manager
operator|->
name|wheel
operator|=
name|info
operator|->
name|controller
expr_stmt|;
elseif|else
if|if
condition|(
name|GIMP_IS_CONTROLLER_KEYBOARD
argument_list|(
name|info
operator|->
name|controller
argument_list|)
condition|)
name|manager
operator|->
name|keyboard
operator|=
name|info
operator|->
name|controller
expr_stmt|;
elseif|else
if|if
condition|(
name|GIMP_IS_CONTROLLER_MOUSE
argument_list|(
name|info
operator|->
name|controller
argument_list|)
condition|)
name|manager
operator|->
name|mouse
operator|=
name|info
operator|->
name|controller
expr_stmt|;
block|}
end_function

begin_function
specifier|static
name|void
DECL|function|gimp_controllers_remove (GimpContainer * container,GimpControllerInfo * info,GimpControllerManager * manager)
name|gimp_controllers_remove
parameter_list|(
name|GimpContainer
modifier|*
name|container
parameter_list|,
name|GimpControllerInfo
modifier|*
name|info
parameter_list|,
name|GimpControllerManager
modifier|*
name|manager
parameter_list|)
block|{
if|if
condition|(
name|info
operator|->
name|controller
operator|==
name|manager
operator|->
name|wheel
condition|)
name|manager
operator|->
name|wheel
operator|=
name|NULL
expr_stmt|;
elseif|else
if|if
condition|(
name|info
operator|->
name|controller
operator|==
name|manager
operator|->
name|keyboard
condition|)
name|manager
operator|->
name|keyboard
operator|=
name|NULL
expr_stmt|;
block|}
end_function

begin_function
specifier|static
name|gboolean
DECL|function|gimp_controllers_event_mapped (GimpControllerInfo * info,GimpController * controller,const GimpControllerEvent * event,const gchar * action_name,GimpControllerManager * manager)
name|gimp_controllers_event_mapped
parameter_list|(
name|GimpControllerInfo
modifier|*
name|info
parameter_list|,
name|GimpController
modifier|*
name|controller
parameter_list|,
specifier|const
name|GimpControllerEvent
modifier|*
name|event
parameter_list|,
specifier|const
name|gchar
modifier|*
name|action_name
parameter_list|,
name|GimpControllerManager
modifier|*
name|manager
parameter_list|)
block|{
name|GList
modifier|*
name|list
decl_stmt|;
for|for
control|(
name|list
operator|=
name|gimp_ui_manager_get_action_groups
argument_list|(
name|manager
operator|->
name|ui_manager
argument_list|)
init|;
name|list
condition|;
name|list
operator|=
name|g_list_next
argument_list|(
name|list
argument_list|)
control|)
block|{
name|GimpActionGroup
modifier|*
name|group
init|=
name|list
operator|->
name|data
decl_stmt|;
name|GimpAction
modifier|*
name|action
decl_stmt|;
name|action
operator|=
name|gimp_action_group_get_action
argument_list|(
name|group
argument_list|,
name|action_name
argument_list|)
expr_stmt|;
if|if
condition|(
name|action
condition|)
block|{
switch|switch
condition|(
name|event
operator|->
name|type
condition|)
block|{
case|case
name|GIMP_CONTROLLER_EVENT_VALUE
case|:
if|if
condition|(
name|G_VALUE_HOLDS_DOUBLE
argument_list|(
operator|&
name|event
operator|->
name|value
operator|.
name|value
argument_list|)
operator|&&
name|GIMP_IS_ENUM_ACTION
argument_list|(
name|action
argument_list|)
operator|&&
name|GIMP_ENUM_ACTION
argument_list|(
name|action
argument_list|)
operator|->
name|value_variable
condition|)
block|{
name|gdouble
name|value
init|=
name|g_value_get_double
argument_list|(
operator|&
name|event
operator|->
name|value
operator|.
name|value
argument_list|)
decl_stmt|;
name|gimp_action_emit_activate
argument_list|(
name|GIMP_ACTION
argument_list|(
name|action
argument_list|)
argument_list|,
name|g_variant_new_int32
argument_list|(
name|value
operator|*
literal|1000
argument_list|)
argument_list|)
expr_stmt|;
break|break;
block|}
comment|/* else fallthru */
case|case
name|GIMP_CONTROLLER_EVENT_TRIGGER
case|:
default|default:
name|gimp_action_activate
argument_list|(
name|action
argument_list|)
expr_stmt|;
break|break;
block|}
return|return
name|TRUE
return|;
block|}
block|}
return|return
name|FALSE
return|;
block|}
end_function

end_unit

