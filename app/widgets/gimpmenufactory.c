begin_unit|revision:0.9.5;language:C;cregit-version:0.0.1
begin_comment
comment|/* GIMP - The GNU Image Manipulation Program  * Copyright (C) 1995 Spencer Kimball and Peter Mattis  *  * gimpmenufactory.c  * Copyright (C) 2001-2004 Michael Natterer<mitch@gimp.org>  *  * This program is free software: you can redistribute it and/or modify  * it under the terms of the GNU General Public License as published by  * the Free Software Foundation; either version 3 of the License, or  * (at your option) any later version.  *  * This program is distributed in the hope that it will be useful,  * but WITHOUT ANY WARRANTY; without even the implied warranty of  * MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the  * GNU General Public License for more details.  *  * You should have received a copy of the GNU General Public License  * along with this program.  If not, see<https://www.gnu.org/licenses/>.  */
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
file|"libgimpwidgets/gimpwidgets.h"
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
file|"gimpaction.h"
end_include

begin_include
include|#
directive|include
file|"gimpactionfactory.h"
end_include

begin_include
include|#
directive|include
file|"gimpactiongroup.h"
end_include

begin_include
include|#
directive|include
file|"gimpmenufactory.h"
end_include

begin_include
include|#
directive|include
file|"gimpuimanager.h"
end_include

begin_struct
DECL|struct|_GimpMenuFactoryPrivate
struct|struct
name|_GimpMenuFactoryPrivate
block|{
DECL|member|gimp
name|Gimp
modifier|*
name|gimp
decl_stmt|;
DECL|member|action_factory
name|GimpActionFactory
modifier|*
name|action_factory
decl_stmt|;
DECL|member|registered_menus
name|GList
modifier|*
name|registered_menus
decl_stmt|;
block|}
struct|;
end_struct

begin_function_decl
specifier|static
name|void
name|gimp_menu_factory_finalize
parameter_list|(
name|GObject
modifier|*
name|object
parameter_list|)
function_decl|;
end_function_decl

begin_macro
DECL|function|G_DEFINE_TYPE_WITH_PRIVATE (GimpMenuFactory,gimp_menu_factory,GIMP_TYPE_OBJECT)
name|G_DEFINE_TYPE_WITH_PRIVATE
argument_list|(
argument|GimpMenuFactory
argument_list|,
argument|gimp_menu_factory
argument_list|,
argument|GIMP_TYPE_OBJECT
argument_list|)
end_macro

begin_define
DECL|macro|parent_class
define|#
directive|define
name|parent_class
value|gimp_menu_factory_parent_class
end_define

begin_function
specifier|static
name|void
name|gimp_menu_factory_class_init
parameter_list|(
name|GimpMenuFactoryClass
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
name|finalize
operator|=
name|gimp_menu_factory_finalize
expr_stmt|;
block|}
end_function

begin_function
specifier|static
name|void
DECL|function|gimp_menu_factory_init (GimpMenuFactory * factory)
name|gimp_menu_factory_init
parameter_list|(
name|GimpMenuFactory
modifier|*
name|factory
parameter_list|)
block|{
name|factory
operator|->
name|p
operator|=
name|gimp_menu_factory_get_instance_private
argument_list|(
name|factory
argument_list|)
expr_stmt|;
block|}
end_function

begin_function
specifier|static
name|void
DECL|function|gimp_menu_factory_finalize (GObject * object)
name|gimp_menu_factory_finalize
parameter_list|(
name|GObject
modifier|*
name|object
parameter_list|)
block|{
name|GimpMenuFactory
modifier|*
name|factory
init|=
name|GIMP_MENU_FACTORY
argument_list|(
name|object
argument_list|)
decl_stmt|;
name|GList
modifier|*
name|list
decl_stmt|;
for|for
control|(
name|list
operator|=
name|factory
operator|->
name|p
operator|->
name|registered_menus
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
name|GimpMenuFactoryEntry
modifier|*
name|entry
init|=
name|list
operator|->
name|data
decl_stmt|;
name|GList
modifier|*
name|uis
decl_stmt|;
name|g_free
argument_list|(
name|entry
operator|->
name|identifier
argument_list|)
expr_stmt|;
name|g_list_free_full
argument_list|(
name|entry
operator|->
name|action_groups
argument_list|,
operator|(
name|GDestroyNotify
operator|)
name|g_free
argument_list|)
expr_stmt|;
for|for
control|(
name|uis
operator|=
name|entry
operator|->
name|managed_uis
init|;
name|uis
condition|;
name|uis
operator|=
name|g_list_next
argument_list|(
name|uis
argument_list|)
control|)
block|{
name|GimpUIManagerUIEntry
modifier|*
name|ui_entry
init|=
name|uis
operator|->
name|data
decl_stmt|;
name|g_free
argument_list|(
name|ui_entry
operator|->
name|ui_path
argument_list|)
expr_stmt|;
name|g_free
argument_list|(
name|ui_entry
operator|->
name|basename
argument_list|)
expr_stmt|;
name|g_slice_free
argument_list|(
name|GimpUIManagerUIEntry
argument_list|,
name|ui_entry
argument_list|)
expr_stmt|;
block|}
name|g_list_free
argument_list|(
name|entry
operator|->
name|managed_uis
argument_list|)
expr_stmt|;
name|g_slice_free
argument_list|(
name|GimpMenuFactoryEntry
argument_list|,
name|entry
argument_list|)
expr_stmt|;
block|}
name|g_list_free
argument_list|(
name|factory
operator|->
name|p
operator|->
name|registered_menus
argument_list|)
expr_stmt|;
name|factory
operator|->
name|p
operator|->
name|registered_menus
operator|=
name|NULL
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
name|GimpMenuFactory
modifier|*
DECL|function|gimp_menu_factory_new (Gimp * gimp,GimpActionFactory * action_factory)
name|gimp_menu_factory_new
parameter_list|(
name|Gimp
modifier|*
name|gimp
parameter_list|,
name|GimpActionFactory
modifier|*
name|action_factory
parameter_list|)
block|{
name|GimpMenuFactory
modifier|*
name|factory
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
name|g_return_val_if_fail
argument_list|(
name|GIMP_IS_ACTION_FACTORY
argument_list|(
name|action_factory
argument_list|)
argument_list|,
name|NULL
argument_list|)
expr_stmt|;
name|factory
operator|=
name|g_object_new
argument_list|(
name|GIMP_TYPE_MENU_FACTORY
argument_list|,
name|NULL
argument_list|)
expr_stmt|;
name|factory
operator|->
name|p
operator|->
name|gimp
operator|=
name|gimp
expr_stmt|;
name|factory
operator|->
name|p
operator|->
name|action_factory
operator|=
name|action_factory
expr_stmt|;
return|return
name|factory
return|;
block|}
end_function

begin_function
name|void
DECL|function|gimp_menu_factory_manager_register (GimpMenuFactory * factory,const gchar * identifier,const gchar * first_group,...)
name|gimp_menu_factory_manager_register
parameter_list|(
name|GimpMenuFactory
modifier|*
name|factory
parameter_list|,
specifier|const
name|gchar
modifier|*
name|identifier
parameter_list|,
specifier|const
name|gchar
modifier|*
name|first_group
parameter_list|,
modifier|...
parameter_list|)
block|{
name|GimpMenuFactoryEntry
modifier|*
name|entry
decl_stmt|;
specifier|const
name|gchar
modifier|*
name|group
decl_stmt|;
specifier|const
name|gchar
modifier|*
name|ui_path
decl_stmt|;
name|va_list
name|args
decl_stmt|;
name|g_return_if_fail
argument_list|(
name|GIMP_IS_MENU_FACTORY
argument_list|(
name|factory
argument_list|)
argument_list|)
expr_stmt|;
name|g_return_if_fail
argument_list|(
name|identifier
operator|!=
name|NULL
argument_list|)
expr_stmt|;
name|g_return_if_fail
argument_list|(
name|first_group
operator|!=
name|NULL
argument_list|)
expr_stmt|;
name|entry
operator|=
name|g_slice_new0
argument_list|(
name|GimpMenuFactoryEntry
argument_list|)
expr_stmt|;
name|entry
operator|->
name|identifier
operator|=
name|g_strdup
argument_list|(
name|identifier
argument_list|)
expr_stmt|;
name|factory
operator|->
name|p
operator|->
name|registered_menus
operator|=
name|g_list_prepend
argument_list|(
name|factory
operator|->
name|p
operator|->
name|registered_menus
argument_list|,
name|entry
argument_list|)
expr_stmt|;
name|va_start
argument_list|(
name|args
argument_list|,
name|first_group
argument_list|)
expr_stmt|;
for|for
control|(
name|group
operator|=
name|first_group
init|;
name|group
condition|;
name|group
operator|=
name|va_arg
argument_list|(
name|args
argument_list|,
specifier|const
name|gchar
operator|*
argument_list|)
control|)
block|{
name|entry
operator|->
name|action_groups
operator|=
name|g_list_prepend
argument_list|(
name|entry
operator|->
name|action_groups
argument_list|,
name|g_strdup
argument_list|(
name|group
argument_list|)
argument_list|)
expr_stmt|;
block|}
name|entry
operator|->
name|action_groups
operator|=
name|g_list_reverse
argument_list|(
name|entry
operator|->
name|action_groups
argument_list|)
expr_stmt|;
name|ui_path
operator|=
name|va_arg
argument_list|(
name|args
argument_list|,
specifier|const
name|gchar
operator|*
argument_list|)
expr_stmt|;
while|while
condition|(
name|ui_path
condition|)
block|{
specifier|const
name|gchar
modifier|*
name|ui_basename
decl_stmt|;
name|GimpUIManagerSetupFunc
name|setup_func
decl_stmt|;
name|GimpUIManagerUIEntry
modifier|*
name|ui_entry
decl_stmt|;
name|ui_basename
operator|=
name|va_arg
argument_list|(
name|args
argument_list|,
specifier|const
name|gchar
operator|*
argument_list|)
expr_stmt|;
name|setup_func
operator|=
name|va_arg
argument_list|(
name|args
argument_list|,
name|GimpUIManagerSetupFunc
argument_list|)
expr_stmt|;
name|ui_entry
operator|=
name|g_slice_new0
argument_list|(
name|GimpUIManagerUIEntry
argument_list|)
expr_stmt|;
name|ui_entry
operator|->
name|ui_path
operator|=
name|g_strdup
argument_list|(
name|ui_path
argument_list|)
expr_stmt|;
name|ui_entry
operator|->
name|basename
operator|=
name|g_strdup
argument_list|(
name|ui_basename
argument_list|)
expr_stmt|;
name|ui_entry
operator|->
name|setup_func
operator|=
name|setup_func
expr_stmt|;
name|entry
operator|->
name|managed_uis
operator|=
name|g_list_prepend
argument_list|(
name|entry
operator|->
name|managed_uis
argument_list|,
name|ui_entry
argument_list|)
expr_stmt|;
name|ui_path
operator|=
name|va_arg
argument_list|(
name|args
argument_list|,
specifier|const
name|gchar
operator|*
argument_list|)
expr_stmt|;
block|}
name|entry
operator|->
name|managed_uis
operator|=
name|g_list_reverse
argument_list|(
name|entry
operator|->
name|managed_uis
argument_list|)
expr_stmt|;
name|va_end
argument_list|(
name|args
argument_list|)
expr_stmt|;
block|}
end_function

begin_function
name|GList
modifier|*
DECL|function|gimp_menu_factory_get_registered_menus (GimpMenuFactory * factory)
name|gimp_menu_factory_get_registered_menus
parameter_list|(
name|GimpMenuFactory
modifier|*
name|factory
parameter_list|)
block|{
name|g_return_val_if_fail
argument_list|(
name|GIMP_IS_MENU_FACTORY
argument_list|(
name|factory
argument_list|)
argument_list|,
name|NULL
argument_list|)
expr_stmt|;
return|return
name|factory
operator|->
name|p
operator|->
name|registered_menus
return|;
block|}
end_function

begin_function
specifier|static
name|void
DECL|function|gimp_menu_factory_manager_action_added (GimpActionGroup * group,GimpAction * action,GtkAccelGroup * accel_group)
name|gimp_menu_factory_manager_action_added
parameter_list|(
name|GimpActionGroup
modifier|*
name|group
parameter_list|,
name|GimpAction
modifier|*
name|action
parameter_list|,
name|GtkAccelGroup
modifier|*
name|accel_group
parameter_list|)
block|{
name|gimp_action_set_accel_group
argument_list|(
name|action
argument_list|,
name|accel_group
argument_list|)
expr_stmt|;
name|gimp_action_connect_accelerator
argument_list|(
name|action
argument_list|)
expr_stmt|;
block|}
end_function

begin_function
name|GimpUIManager
modifier|*
DECL|function|gimp_menu_factory_manager_new (GimpMenuFactory * factory,const gchar * identifier,gpointer callback_data)
name|gimp_menu_factory_manager_new
parameter_list|(
name|GimpMenuFactory
modifier|*
name|factory
parameter_list|,
specifier|const
name|gchar
modifier|*
name|identifier
parameter_list|,
name|gpointer
name|callback_data
parameter_list|)
block|{
name|GList
modifier|*
name|list
decl_stmt|;
name|g_return_val_if_fail
argument_list|(
name|GIMP_IS_MENU_FACTORY
argument_list|(
name|factory
argument_list|)
argument_list|,
name|NULL
argument_list|)
expr_stmt|;
name|g_return_val_if_fail
argument_list|(
name|identifier
operator|!=
name|NULL
argument_list|,
name|NULL
argument_list|)
expr_stmt|;
for|for
control|(
name|list
operator|=
name|factory
operator|->
name|p
operator|->
name|registered_menus
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
name|GimpMenuFactoryEntry
modifier|*
name|entry
init|=
name|list
operator|->
name|data
decl_stmt|;
if|if
condition|(
operator|!
name|strcmp
argument_list|(
name|entry
operator|->
name|identifier
argument_list|,
name|identifier
argument_list|)
condition|)
block|{
name|GimpUIManager
modifier|*
name|manager
decl_stmt|;
name|GtkAccelGroup
modifier|*
name|accel_group
decl_stmt|;
name|GList
modifier|*
name|list
decl_stmt|;
name|manager
operator|=
name|gimp_ui_manager_new
argument_list|(
name|factory
operator|->
name|p
operator|->
name|gimp
argument_list|,
name|entry
operator|->
name|identifier
argument_list|)
expr_stmt|;
name|accel_group
operator|=
name|gimp_ui_manager_get_accel_group
argument_list|(
name|manager
argument_list|)
expr_stmt|;
for|for
control|(
name|list
operator|=
name|entry
operator|->
name|action_groups
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
decl_stmt|;
name|GList
modifier|*
name|actions
decl_stmt|;
name|GList
modifier|*
name|list2
decl_stmt|;
name|group
operator|=
name|gimp_action_factory_group_new
argument_list|(
name|factory
operator|->
name|p
operator|->
name|action_factory
argument_list|,
operator|(
specifier|const
name|gchar
operator|*
operator|)
name|list
operator|->
name|data
argument_list|,
name|callback_data
argument_list|)
expr_stmt|;
name|actions
operator|=
name|gimp_action_group_list_actions
argument_list|(
name|group
argument_list|)
expr_stmt|;
for|for
control|(
name|list2
operator|=
name|actions
init|;
name|list2
condition|;
name|list2
operator|=
name|g_list_next
argument_list|(
name|list2
argument_list|)
control|)
block|{
name|GimpAction
modifier|*
name|action
init|=
name|list2
operator|->
name|data
decl_stmt|;
name|gimp_action_set_accel_group
argument_list|(
name|action
argument_list|,
name|accel_group
argument_list|)
expr_stmt|;
name|gimp_action_connect_accelerator
argument_list|(
name|action
argument_list|)
expr_stmt|;
block|}
name|g_list_free
argument_list|(
name|actions
argument_list|)
expr_stmt|;
name|g_signal_connect_object
argument_list|(
name|group
argument_list|,
literal|"action-added"
argument_list|,
name|G_CALLBACK
argument_list|(
name|gimp_menu_factory_manager_action_added
argument_list|)
argument_list|,
name|accel_group
argument_list|,
literal|0
argument_list|)
expr_stmt|;
name|gimp_ui_manager_insert_action_group
argument_list|(
name|manager
argument_list|,
name|group
argument_list|,
operator|-
literal|1
argument_list|)
expr_stmt|;
name|g_object_unref
argument_list|(
name|group
argument_list|)
expr_stmt|;
block|}
for|for
control|(
name|list
operator|=
name|entry
operator|->
name|managed_uis
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
name|GimpUIManagerUIEntry
modifier|*
name|ui_entry
init|=
name|list
operator|->
name|data
decl_stmt|;
name|gimp_ui_manager_ui_register
argument_list|(
name|manager
argument_list|,
name|ui_entry
operator|->
name|ui_path
argument_list|,
name|ui_entry
operator|->
name|basename
argument_list|,
name|ui_entry
operator|->
name|setup_func
argument_list|)
expr_stmt|;
block|}
return|return
name|manager
return|;
block|}
block|}
name|g_warning
argument_list|(
literal|"%s: no entry registered for \"%s\""
argument_list|,
name|G_STRFUNC
argument_list|,
name|identifier
argument_list|)
expr_stmt|;
return|return
name|NULL
return|;
block|}
end_function

end_unit

