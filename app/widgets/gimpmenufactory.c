begin_unit|revision:0.9.5;language:C;cregit-version:0.0.1
begin_comment
comment|/* The GIMP -- an image manipulation program  * Copyright (C) 1995 Spencer Kimball and Peter Mattis  *  * gimpmenufactory.c  * Copyright (C) 2001-2004 Michael Natterer<mitch@gimp.org>  *  * This program is free software; you can redistribute it and/or modify  * it under the terms of the GNU General Public License as published by  * the Free Software Foundation; either version 2 of the License, or  * (at your option) any later version.  *  * This program is distributed in the hope that it will be useful,  * but WITHOUT ANY WARRANTY; without even the implied warranty of  * MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the  * GNU General Public License for more details.  *  * You should have received a copy of the GNU General Public License  * along with this program; if not, write to the Free Software  * Foundation, Inc., 59 Temple Place - Suite 330, Boston, MA 02111-1307, USA.  */
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
file|"gimpactionfactory.h"
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

begin_function_decl
specifier|static
name|void
name|gimp_menu_factory_class_init
parameter_list|(
name|GimpMenuFactoryClass
modifier|*
name|klass
parameter_list|)
function_decl|;
end_function_decl

begin_function_decl
specifier|static
name|void
name|gimp_menu_factory_init
parameter_list|(
name|GimpMenuFactory
modifier|*
name|factory
parameter_list|)
function_decl|;
end_function_decl

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

begin_decl_stmt
DECL|variable|parent_class
specifier|static
name|GimpObjectClass
modifier|*
name|parent_class
init|=
name|NULL
decl_stmt|;
end_decl_stmt

begin_function
name|GType
DECL|function|gimp_menu_factory_get_type (void)
name|gimp_menu_factory_get_type
parameter_list|(
name|void
parameter_list|)
block|{
specifier|static
name|GType
name|factory_type
init|=
literal|0
decl_stmt|;
if|if
condition|(
operator|!
name|factory_type
condition|)
block|{
specifier|static
specifier|const
name|GTypeInfo
name|factory_info
init|=
block|{
sizeof|sizeof
argument_list|(
name|GimpMenuFactoryClass
argument_list|)
block|,
name|NULL
block|,
comment|/* base_init */
name|NULL
block|,
comment|/* base_finalize */
operator|(
name|GClassInitFunc
operator|)
name|gimp_menu_factory_class_init
block|,
name|NULL
block|,
comment|/* class_finalize */
name|NULL
block|,
comment|/* class_data */
sizeof|sizeof
argument_list|(
name|GimpMenuFactory
argument_list|)
block|,
literal|0
block|,
comment|/* n_preallocs */
operator|(
name|GInstanceInitFunc
operator|)
name|gimp_menu_factory_init
block|,       }
decl_stmt|;
name|factory_type
operator|=
name|g_type_register_static
argument_list|(
name|GIMP_TYPE_OBJECT
argument_list|,
literal|"GimpMenuFactory"
argument_list|,
operator|&
name|factory_info
argument_list|,
literal|0
argument_list|)
expr_stmt|;
block|}
return|return
name|factory_type
return|;
block|}
end_function

begin_function
specifier|static
name|void
DECL|function|gimp_menu_factory_class_init (GimpMenuFactoryClass * klass)
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
name|parent_class
operator|=
name|g_type_class_peek_parent
argument_list|(
name|klass
argument_list|)
expr_stmt|;
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
name|gimp
operator|=
name|NULL
expr_stmt|;
name|factory
operator|->
name|registered_menus
operator|=
name|NULL
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
name|g_list_foreach
argument_list|(
name|entry
operator|->
name|action_groups
argument_list|,
operator|(
name|GFunc
operator|)
name|g_free
argument_list|,
name|NULL
argument_list|)
expr_stmt|;
name|g_list_free
argument_list|(
name|entry
operator|->
name|action_groups
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
name|g_free
argument_list|(
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
name|g_free
argument_list|(
name|entry
argument_list|)
expr_stmt|;
block|}
name|g_list_free
argument_list|(
name|factory
operator|->
name|registered_menus
argument_list|)
expr_stmt|;
name|factory
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
name|gimp
operator|=
name|gimp
expr_stmt|;
name|factory
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
name|g_new0
argument_list|(
name|GimpMenuFactoryEntry
argument_list|,
literal|1
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
name|registered_menus
operator|=
name|g_list_prepend
argument_list|(
name|factory
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
name|g_new0
argument_list|(
name|GimpUIManagerUIEntry
argument_list|,
literal|1
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
name|GimpUIManager
modifier|*
DECL|function|gimp_menu_factory_manager_new (GimpMenuFactory * factory,const gchar * identifier,gpointer callback_data,gboolean create_tearoff)
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
parameter_list|,
name|gboolean
name|create_tearoff
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
name|gimp
argument_list|,
name|entry
operator|->
name|identifier
argument_list|)
expr_stmt|;
name|gtk_ui_manager_set_add_tearoffs
argument_list|(
name|GTK_UI_MANAGER
argument_list|(
name|manager
argument_list|)
argument_list|,
name|create_tearoff
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
name|group
operator|=
name|gimp_action_factory_group_new
argument_list|(
name|factory
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
name|gtk_ui_manager_insert_action_group
argument_list|(
name|GTK_UI_MANAGER
argument_list|(
name|manager
argument_list|)
argument_list|,
name|GTK_ACTION_GROUP
argument_list|(
name|group
argument_list|)
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

