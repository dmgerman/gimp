begin_unit|revision:0.9.5;language:C;cregit-version:0.0.1
begin_comment
comment|/* The GIMP -- an image manipulation program  * Copyright (C) 1995 Spencer Kimball and Peter Mattis  *  * gimpmenufactory.c  * Copyright (C) 2001 Michael Natterer<mitch@gimp.org>  *  * This program is free software; you can redistribute it and/or modify  * it under the terms of the GNU General Public License as published by  * the Free Software Foundation; either version 2 of the License, or  * (at your option) any later version.  *  * This program is distributed in the hope that it will be useful,  * but WITHOUT ANY WARRANTY; without even the implied warranty of  * MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the  * GNU General Public License for more details.  *  * You should have received a copy of the GNU General Public License  * along with this program; if not, write to the Free Software  * Foundation, Inc., 59 Temple Place - Suite 330, Boston, MA 02111-1307, USA.  */
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
file|"gimpmenufactory.h"
end_include

begin_include
include|#
directive|include
file|"gimpitemfactory.h"
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
decl_stmt|;
name|object_class
operator|=
name|G_OBJECT_CLASS
argument_list|(
name|klass
argument_list|)
expr_stmt|;
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
decl_stmt|;
name|GList
modifier|*
name|list
decl_stmt|;
name|factory
operator|=
name|GIMP_MENU_FACTORY
argument_list|(
name|object
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
decl_stmt|;
name|entry
operator|=
operator|(
name|GimpMenuFactoryEntry
operator|*
operator|)
name|list
operator|->
name|data
expr_stmt|;
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
operator|->
name|title
argument_list|)
expr_stmt|;
name|g_free
argument_list|(
name|entry
operator|->
name|help_id
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
DECL|function|gimp_menu_factory_new (Gimp * gimp)
name|gimp_menu_factory_new
parameter_list|(
name|Gimp
modifier|*
name|gimp
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
return|return
name|factory
return|;
block|}
end_function

begin_function
name|void
DECL|function|gimp_menu_factory_menu_register (GimpMenuFactory * factory,const gchar * identifier,const gchar * title,const gchar * help_id,GimpItemFactorySetupFunc setup_func,GimpItemFactoryUpdateFunc update_func,gboolean update_on_popup,guint n_entries,GimpItemFactoryEntry * entries)
name|gimp_menu_factory_menu_register
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
name|title
parameter_list|,
specifier|const
name|gchar
modifier|*
name|help_id
parameter_list|,
name|GimpItemFactorySetupFunc
name|setup_func
parameter_list|,
name|GimpItemFactoryUpdateFunc
name|update_func
parameter_list|,
name|gboolean
name|update_on_popup
parameter_list|,
name|guint
name|n_entries
parameter_list|,
name|GimpItemFactoryEntry
modifier|*
name|entries
parameter_list|)
block|{
name|GimpMenuFactoryEntry
modifier|*
name|entry
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
name|title
operator|!=
name|NULL
argument_list|)
expr_stmt|;
name|g_return_if_fail
argument_list|(
name|help_id
operator|!=
name|NULL
argument_list|)
expr_stmt|;
name|g_return_if_fail
argument_list|(
name|n_entries
operator|>
literal|0
argument_list|)
expr_stmt|;
name|g_return_if_fail
argument_list|(
name|entries
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
name|entry
operator|->
name|title
operator|=
name|g_strdup
argument_list|(
name|title
argument_list|)
expr_stmt|;
name|entry
operator|->
name|help_id
operator|=
name|g_strdup
argument_list|(
name|help_id
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
name|entry
operator|->
name|update_on_popup
operator|=
name|update_on_popup
condition|?
name|TRUE
else|:
name|FALSE
expr_stmt|;
name|entry
operator|->
name|n_entries
operator|=
name|n_entries
expr_stmt|;
name|entry
operator|->
name|entries
operator|=
name|entries
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
block|}
end_function

begin_function
name|GimpItemFactory
modifier|*
DECL|function|gimp_menu_factory_menu_new (GimpMenuFactory * factory,const gchar * identifier,GType container_type,gpointer callback_data,gboolean create_tearoff)
name|gimp_menu_factory_menu_new
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
name|GType
name|container_type
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
name|GimpItemFactory
modifier|*
name|item_factory
decl_stmt|;
name|item_factory
operator|=
name|gimp_item_factory_new
argument_list|(
name|factory
operator|->
name|gimp
argument_list|,
name|container_type
argument_list|,
name|entry
operator|->
name|identifier
argument_list|,
name|entry
operator|->
name|title
argument_list|,
name|entry
operator|->
name|help_id
argument_list|,
name|entry
operator|->
name|update_func
argument_list|,
name|entry
operator|->
name|update_on_popup
argument_list|,
name|entry
operator|->
name|n_entries
argument_list|,
name|entry
operator|->
name|entries
argument_list|,
name|callback_data
argument_list|,
name|create_tearoff
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
name|item_factory
argument_list|,
name|callback_data
argument_list|)
expr_stmt|;
return|return
name|item_factory
return|;
block|}
block|}
name|g_warning
argument_list|(
literal|"%s: no entry registered for \"%s\""
argument_list|,
name|G_GNUC_FUNCTION
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

