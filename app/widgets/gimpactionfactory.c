begin_unit|revision:0.9.5;language:C;cregit-version:0.0.1
begin_comment
comment|/* The GIMP -- an image manipulation program  * Copyright (C) 1995 Spencer Kimball and Peter Mattis  *  * gimpactionfactory.c  * Copyright (C) 2004 Michael Natterer<mitch@gimp.org>  *  * This program is free software; you can redistribute it and/or modify  * it under the terms of the GNU General Public License as published by  * the Free Software Foundation; either version 2 of the License, or  * (at your option) any later version.  *  * This program is distributed in the hope that it will be useful,  * but WITHOUT ANY WARRANTY; without even the implied warranty of  * MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the  * GNU General Public License for more details.  *  * You should have received a copy of the GNU General Public License  * along with this program; if not, write to the Free Software  * Foundation, Inc., 59 Temple Place - Suite 330, Boston, MA 02111-1307, USA.  */
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
file|"gimpactiongroup.h"
end_include

begin_function_decl
specifier|static
name|void
name|gimp_action_factory_class_init
parameter_list|(
name|GimpActionFactoryClass
modifier|*
name|klass
parameter_list|)
function_decl|;
end_function_decl

begin_function_decl
specifier|static
name|void
name|gimp_action_factory_init
parameter_list|(
name|GimpActionFactory
modifier|*
name|factory
parameter_list|)
function_decl|;
end_function_decl

begin_function_decl
specifier|static
name|void
name|gimp_action_factory_finalize
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
DECL|function|gimp_action_factory_get_type (void)
name|gimp_action_factory_get_type
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
name|GimpActionFactoryClass
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
name|gimp_action_factory_class_init
block|,
name|NULL
block|,
comment|/* class_finalize */
name|NULL
block|,
comment|/* class_data */
sizeof|sizeof
argument_list|(
name|GimpActionFactory
argument_list|)
block|,
literal|0
block|,
comment|/* n_preallocs */
operator|(
name|GInstanceInitFunc
operator|)
name|gimp_action_factory_init
block|,       }
decl_stmt|;
name|factory_type
operator|=
name|g_type_register_static
argument_list|(
name|GIMP_TYPE_OBJECT
argument_list|,
literal|"GimpActionFactory"
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
DECL|function|gimp_action_factory_class_init (GimpActionFactoryClass * klass)
name|gimp_action_factory_class_init
parameter_list|(
name|GimpActionFactoryClass
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
name|gimp_action_factory_finalize
expr_stmt|;
block|}
end_function

begin_function
specifier|static
name|void
DECL|function|gimp_action_factory_init (GimpActionFactory * factory)
name|gimp_action_factory_init
parameter_list|(
name|GimpActionFactory
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
name|registered_groups
operator|=
name|NULL
expr_stmt|;
block|}
end_function

begin_function
specifier|static
name|void
DECL|function|gimp_action_factory_finalize (GObject * object)
name|gimp_action_factory_finalize
parameter_list|(
name|GObject
modifier|*
name|object
parameter_list|)
block|{
name|GimpActionFactory
modifier|*
name|factory
init|=
name|GIMP_ACTION_FACTORY
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
name|registered_groups
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
name|GimpActionFactoryEntry
modifier|*
name|entry
init|=
name|list
operator|->
name|data
decl_stmt|;
name|g_free
argument_list|(
name|entry
operator|->
name|identifier
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
name|registered_groups
argument_list|)
expr_stmt|;
name|factory
operator|->
name|registered_groups
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
name|GimpActionFactory
modifier|*
DECL|function|gimp_action_factory_new (Gimp * gimp)
name|gimp_action_factory_new
parameter_list|(
name|Gimp
modifier|*
name|gimp
parameter_list|)
block|{
name|GimpActionFactory
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
name|factory
operator|=
name|g_object_new
argument_list|(
name|GIMP_TYPE_ACTION_FACTORY
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
return|return
name|factory
return|;
block|}
end_function

begin_function
name|void
DECL|function|gimp_action_factory_group_register (GimpActionFactory * factory,const gchar * identifier,GimpActionGroupSetupFunc setup_func,GimpActionGroupUpdateFunc update_func)
name|gimp_action_factory_group_register
parameter_list|(
name|GimpActionFactory
modifier|*
name|factory
parameter_list|,
specifier|const
name|gchar
modifier|*
name|identifier
parameter_list|,
name|GimpActionGroupSetupFunc
name|setup_func
parameter_list|,
name|GimpActionGroupUpdateFunc
name|update_func
parameter_list|)
block|{
name|GimpActionFactoryEntry
modifier|*
name|entry
decl_stmt|;
name|g_return_if_fail
argument_list|(
name|GIMP_IS_ACTION_FACTORY
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
name|setup_func
operator|!=
name|NULL
argument_list|)
expr_stmt|;
name|g_return_if_fail
argument_list|(
name|update_func
operator|!=
name|NULL
argument_list|)
expr_stmt|;
name|entry
operator|=
name|g_new0
argument_list|(
name|GimpActionFactoryEntry
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
name|entry
operator|->
name|setup_func
operator|=
name|setup_func
expr_stmt|;
name|entry
operator|->
name|update_func
operator|=
name|update_func
expr_stmt|;
name|factory
operator|->
name|registered_groups
operator|=
name|g_list_prepend
argument_list|(
name|factory
operator|->
name|registered_groups
argument_list|,
name|entry
argument_list|)
expr_stmt|;
block|}
end_function

begin_function
name|GimpActionGroup
modifier|*
DECL|function|gimp_action_factory_group_new (GimpActionFactory * factory,const gchar * identifier,gpointer setup_data)
name|gimp_action_factory_group_new
parameter_list|(
name|GimpActionFactory
modifier|*
name|factory
parameter_list|,
specifier|const
name|gchar
modifier|*
name|identifier
parameter_list|,
name|gpointer
name|setup_data
parameter_list|)
block|{
name|GList
modifier|*
name|list
decl_stmt|;
name|g_return_val_if_fail
argument_list|(
name|GIMP_IS_ACTION_FACTORY
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
name|registered_groups
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
name|GimpActionFactoryEntry
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
name|GimpActionGroup
modifier|*
name|group
decl_stmt|;
name|group
operator|=
name|gimp_action_group_new
argument_list|(
name|factory
operator|->
name|gimp
argument_list|,
name|entry
operator|->
name|identifier
argument_list|,
name|entry
operator|->
name|update_func
argument_list|)
expr_stmt|;
if|if
condition|(
name|entry
operator|->
name|setup_func
condition|)
name|entry
operator|->
name|setup_func
argument_list|(
name|group
argument_list|,
name|setup_data
argument_list|)
expr_stmt|;
return|return
name|group
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

