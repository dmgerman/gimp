begin_unit|revision:0.9.5;language:C;cregit-version:0.0.1
begin_comment
comment|/* The GIMP -- an image manipulation program  * Copyright (C) 1995 Spencer Kimball and Peter Mattis  *  * gimpdatafactory.c  * Copyright (C) 2001 Michael Natterer<mitch@gimp.org>  *  * This program is free software; you can redistribute it and/or modify  * it under the terms of the GNU General Public License as published by  * the Free Software Foundation; either version 2 of the License, or  * (at your option) any later version.  *  * This program is distributed in the hope that it will be useful,  * but WITHOUT ANY WARRANTY; without even the implied warranty of  * MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the  * GNU General Public License for more details.  *  * You should have received a copy of the GNU General Public License  * along with this program; if not, write to the Free Software  * Foundation, Inc., 59 Temple Place - Suite 330, Boston, MA 02111-1307, USA.  */
end_comment

begin_include
include|#
directive|include
file|"config.h"
end_include

begin_include
include|#
directive|include
file|<glib-object.h>
end_include

begin_include
include|#
directive|include
file|"libgimpbase/gimpbase.h"
end_include

begin_include
include|#
directive|include
file|"core-types.h"
end_include

begin_include
include|#
directive|include
file|"config/gimpbaseconfig.h"
end_include

begin_include
include|#
directive|include
file|"gimp.h"
end_include

begin_include
include|#
directive|include
file|"gimpcontext.h"
end_include

begin_include
include|#
directive|include
file|"gimpdata.h"
end_include

begin_include
include|#
directive|include
file|"gimpdatafactory.h"
end_include

begin_include
include|#
directive|include
file|"gimpdatalist.h"
end_include

begin_include
include|#
directive|include
file|"libgimp/gimpintl.h"
end_include

begin_function_decl
specifier|static
name|void
name|gimp_data_factory_class_init
parameter_list|(
name|GimpDataFactoryClass
modifier|*
name|klass
parameter_list|)
function_decl|;
end_function_decl

begin_function_decl
specifier|static
name|void
name|gimp_data_factory_init
parameter_list|(
name|GimpDataFactory
modifier|*
name|factory
parameter_list|)
function_decl|;
end_function_decl

begin_function_decl
specifier|static
name|void
name|gimp_data_factory_finalize
parameter_list|(
name|GObject
modifier|*
name|object
parameter_list|)
function_decl|;
end_function_decl

begin_function_decl
specifier|static
name|gsize
name|gimp_data_factory_get_memsize
parameter_list|(
name|GimpObject
modifier|*
name|object
parameter_list|)
function_decl|;
end_function_decl

begin_function_decl
specifier|static
name|void
name|gimp_data_factory_data_load_callback
parameter_list|(
name|GimpDatafileData
modifier|*
name|file_data
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
DECL|function|gimp_data_factory_get_type (void)
name|gimp_data_factory_get_type
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
name|GimpDataFactoryClass
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
name|gimp_data_factory_class_init
block|,
name|NULL
block|,
comment|/* class_finalize */
name|NULL
block|,
comment|/* class_data     */
sizeof|sizeof
argument_list|(
name|GimpDataFactory
argument_list|)
block|,
literal|0
block|,
comment|/* n_preallocs    */
operator|(
name|GInstanceInitFunc
operator|)
name|gimp_data_factory_init
block|,       }
decl_stmt|;
name|factory_type
operator|=
name|g_type_register_static
argument_list|(
name|GIMP_TYPE_OBJECT
argument_list|,
literal|"GimpDataFactory"
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
DECL|function|gimp_data_factory_class_init (GimpDataFactoryClass * klass)
name|gimp_data_factory_class_init
parameter_list|(
name|GimpDataFactoryClass
modifier|*
name|klass
parameter_list|)
block|{
name|GObjectClass
modifier|*
name|object_class
decl_stmt|;
name|GimpObjectClass
modifier|*
name|gimp_object_class
decl_stmt|;
name|object_class
operator|=
name|G_OBJECT_CLASS
argument_list|(
name|klass
argument_list|)
expr_stmt|;
name|gimp_object_class
operator|=
name|GIMP_OBJECT_CLASS
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
name|gimp_data_factory_finalize
expr_stmt|;
name|gimp_object_class
operator|->
name|get_memsize
operator|=
name|gimp_data_factory_get_memsize
expr_stmt|;
block|}
end_function

begin_function
specifier|static
name|void
DECL|function|gimp_data_factory_init (GimpDataFactory * factory)
name|gimp_data_factory_init
parameter_list|(
name|GimpDataFactory
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
name|container
operator|=
name|NULL
expr_stmt|;
name|factory
operator|->
name|data_path
operator|=
name|NULL
expr_stmt|;
name|factory
operator|->
name|loader_entries
operator|=
name|NULL
expr_stmt|;
name|factory
operator|->
name|n_loader_entries
operator|=
literal|0
expr_stmt|;
name|factory
operator|->
name|data_new_func
operator|=
name|NULL
expr_stmt|;
name|factory
operator|->
name|data_get_standard_func
operator|=
name|NULL
expr_stmt|;
block|}
end_function

begin_function
specifier|static
name|void
DECL|function|gimp_data_factory_finalize (GObject * object)
name|gimp_data_factory_finalize
parameter_list|(
name|GObject
modifier|*
name|object
parameter_list|)
block|{
name|GimpDataFactory
modifier|*
name|factory
decl_stmt|;
name|factory
operator|=
name|GIMP_DATA_FACTORY
argument_list|(
name|object
argument_list|)
expr_stmt|;
if|if
condition|(
name|factory
operator|->
name|container
condition|)
block|{
name|g_object_unref
argument_list|(
name|G_OBJECT
argument_list|(
name|factory
operator|->
name|container
argument_list|)
argument_list|)
expr_stmt|;
name|factory
operator|->
name|container
operator|=
name|NULL
expr_stmt|;
block|}
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
name|gsize
DECL|function|gimp_data_factory_get_memsize (GimpObject * object)
name|gimp_data_factory_get_memsize
parameter_list|(
name|GimpObject
modifier|*
name|object
parameter_list|)
block|{
name|GimpDataFactory
modifier|*
name|factory
decl_stmt|;
name|gsize
name|memsize
init|=
literal|0
decl_stmt|;
name|factory
operator|=
name|GIMP_DATA_FACTORY
argument_list|(
name|object
argument_list|)
expr_stmt|;
name|memsize
operator|+=
name|gimp_object_get_memsize
argument_list|(
name|GIMP_OBJECT
argument_list|(
name|factory
operator|->
name|container
argument_list|)
argument_list|)
expr_stmt|;
return|return
name|memsize
operator|+
name|GIMP_OBJECT_CLASS
argument_list|(
name|parent_class
argument_list|)
operator|->
name|get_memsize
argument_list|(
name|object
argument_list|)
return|;
block|}
end_function

begin_function
name|GimpDataFactory
modifier|*
DECL|function|gimp_data_factory_new (Gimp * gimp,GType data_type,const gchar ** data_path,const GimpDataFactoryLoaderEntry * loader_entries,gint n_loader_entries,GimpDataNewFunc new_func,GimpDataGetStandardFunc standard_func)
name|gimp_data_factory_new
parameter_list|(
name|Gimp
modifier|*
name|gimp
parameter_list|,
name|GType
name|data_type
parameter_list|,
specifier|const
name|gchar
modifier|*
modifier|*
name|data_path
parameter_list|,
specifier|const
name|GimpDataFactoryLoaderEntry
modifier|*
name|loader_entries
parameter_list|,
name|gint
name|n_loader_entries
parameter_list|,
name|GimpDataNewFunc
name|new_func
parameter_list|,
name|GimpDataGetStandardFunc
name|standard_func
parameter_list|)
block|{
name|GimpDataFactory
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
name|g_type_is_a
argument_list|(
name|data_type
argument_list|,
name|GIMP_TYPE_DATA
argument_list|)
argument_list|,
name|NULL
argument_list|)
expr_stmt|;
name|g_return_val_if_fail
argument_list|(
name|data_path
operator|!=
name|NULL
argument_list|,
name|NULL
argument_list|)
expr_stmt|;
name|g_return_val_if_fail
argument_list|(
name|loader_entries
operator|!=
name|NULL
argument_list|,
name|NULL
argument_list|)
expr_stmt|;
name|g_return_val_if_fail
argument_list|(
name|n_loader_entries
operator|>
literal|0
argument_list|,
name|NULL
argument_list|)
expr_stmt|;
name|factory
operator|=
name|g_object_new
argument_list|(
name|GIMP_TYPE_DATA_FACTORY
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
name|container
operator|=
name|gimp_data_list_new
argument_list|(
name|data_type
argument_list|)
expr_stmt|;
name|factory
operator|->
name|data_path
operator|=
name|data_path
expr_stmt|;
name|factory
operator|->
name|loader_entries
operator|=
name|loader_entries
expr_stmt|;
name|factory
operator|->
name|n_loader_entries
operator|=
name|n_loader_entries
expr_stmt|;
name|factory
operator|->
name|data_new_func
operator|=
name|new_func
expr_stmt|;
name|factory
operator|->
name|data_get_standard_func
operator|=
name|standard_func
expr_stmt|;
return|return
name|factory
return|;
block|}
end_function

begin_function
name|void
DECL|function|gimp_data_factory_data_init (GimpDataFactory * factory,gboolean no_data)
name|gimp_data_factory_data_init
parameter_list|(
name|GimpDataFactory
modifier|*
name|factory
parameter_list|,
name|gboolean
name|no_data
comment|/* FIXME */
parameter_list|)
block|{
name|g_return_if_fail
argument_list|(
name|GIMP_IS_DATA_FACTORY
argument_list|(
name|factory
argument_list|)
argument_list|)
expr_stmt|;
name|gimp_container_freeze
argument_list|(
name|factory
operator|->
name|container
argument_list|)
expr_stmt|;
name|gimp_data_factory_data_free
argument_list|(
name|factory
argument_list|)
expr_stmt|;
if|if
condition|(
name|factory
operator|->
name|data_path
operator|&&
operator|*
name|factory
operator|->
name|data_path
condition|)
block|{
name|gimp_datafiles_read_directories
argument_list|(
operator|*
name|factory
operator|->
name|data_path
argument_list|,
name|G_FILE_TEST_EXISTS
argument_list|,
name|gimp_data_factory_data_load_callback
argument_list|,
name|factory
argument_list|)
expr_stmt|;
block|}
name|gimp_container_thaw
argument_list|(
name|factory
operator|->
name|container
argument_list|)
expr_stmt|;
block|}
end_function

begin_function
name|void
DECL|function|gimp_data_factory_data_save (GimpDataFactory * factory)
name|gimp_data_factory_data_save
parameter_list|(
name|GimpDataFactory
modifier|*
name|factory
parameter_list|)
block|{
name|GimpList
modifier|*
name|gimp_list
decl_stmt|;
name|GList
modifier|*
name|list
decl_stmt|;
name|g_return_if_fail
argument_list|(
name|GIMP_IS_DATA_FACTORY
argument_list|(
name|factory
argument_list|)
argument_list|)
expr_stmt|;
if|if
condition|(
name|gimp_container_num_children
argument_list|(
name|factory
operator|->
name|container
argument_list|)
operator|==
literal|0
condition|)
return|return;
if|if
condition|(
operator|!
operator|(
name|factory
operator|->
name|data_path
operator|&&
operator|*
name|factory
operator|->
name|data_path
operator|)
condition|)
return|return;
name|gimp_list
operator|=
name|GIMP_LIST
argument_list|(
name|factory
operator|->
name|container
argument_list|)
expr_stmt|;
name|gimp_container_freeze
argument_list|(
name|factory
operator|->
name|container
argument_list|)
expr_stmt|;
for|for
control|(
name|list
operator|=
name|gimp_list
operator|->
name|list
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
name|GimpData
modifier|*
name|data
decl_stmt|;
name|data
operator|=
name|GIMP_DATA
argument_list|(
name|list
operator|->
name|data
argument_list|)
expr_stmt|;
if|if
condition|(
operator|!
name|data
operator|->
name|filename
condition|)
name|gimp_data_create_filename
argument_list|(
name|data
argument_list|,
name|GIMP_OBJECT
argument_list|(
name|data
argument_list|)
operator|->
name|name
argument_list|,
operator|*
name|factory
operator|->
name|data_path
argument_list|)
expr_stmt|;
if|if
condition|(
name|data
operator|->
name|dirty
condition|)
name|gimp_data_save
argument_list|(
name|data
argument_list|)
expr_stmt|;
block|}
name|gimp_container_thaw
argument_list|(
name|factory
operator|->
name|container
argument_list|)
expr_stmt|;
block|}
end_function

begin_function
name|void
DECL|function|gimp_data_factory_data_free (GimpDataFactory * factory)
name|gimp_data_factory_data_free
parameter_list|(
name|GimpDataFactory
modifier|*
name|factory
parameter_list|)
block|{
name|GimpList
modifier|*
name|list
decl_stmt|;
name|g_return_if_fail
argument_list|(
name|GIMP_IS_DATA_FACTORY
argument_list|(
name|factory
argument_list|)
argument_list|)
expr_stmt|;
if|if
condition|(
name|gimp_container_num_children
argument_list|(
name|factory
operator|->
name|container
argument_list|)
operator|==
literal|0
condition|)
return|return;
name|list
operator|=
name|GIMP_LIST
argument_list|(
name|factory
operator|->
name|container
argument_list|)
expr_stmt|;
name|gimp_container_freeze
argument_list|(
name|factory
operator|->
name|container
argument_list|)
expr_stmt|;
if|if
condition|(
name|list
operator|->
name|list
condition|)
block|{
if|if
condition|(
name|GIMP_DATA
argument_list|(
name|list
operator|->
name|list
operator|->
name|data
argument_list|)
operator|->
name|internal
condition|)
block|{
comment|/*  if there are internal objects in the list, skip them  */
name|GList
modifier|*
name|glist
decl_stmt|;
for|for
control|(
name|glist
operator|=
name|list
operator|->
name|list
init|;
name|glist
condition|;
name|glist
operator|=
name|g_list_next
argument_list|(
name|glist
argument_list|)
control|)
block|{
if|if
condition|(
name|glist
operator|->
name|next
operator|&&
operator|!
name|GIMP_DATA
argument_list|(
name|glist
operator|->
name|next
operator|->
name|data
argument_list|)
operator|->
name|internal
condition|)
block|{
while|while
condition|(
name|glist
operator|->
name|next
condition|)
block|{
name|gimp_container_remove
argument_list|(
name|factory
operator|->
name|container
argument_list|,
name|GIMP_OBJECT
argument_list|(
name|glist
operator|->
name|next
operator|->
name|data
argument_list|)
argument_list|)
expr_stmt|;
block|}
break|break;
block|}
block|}
block|}
else|else
block|{
comment|/*  otherwise delete everything  */
while|while
condition|(
name|list
operator|->
name|list
condition|)
block|{
name|gimp_container_remove
argument_list|(
name|factory
operator|->
name|container
argument_list|,
name|GIMP_OBJECT
argument_list|(
name|list
operator|->
name|list
operator|->
name|data
argument_list|)
argument_list|)
expr_stmt|;
block|}
block|}
block|}
name|gimp_container_thaw
argument_list|(
name|factory
operator|->
name|container
argument_list|)
expr_stmt|;
block|}
end_function

begin_function
name|GimpData
modifier|*
DECL|function|gimp_data_factory_data_new (GimpDataFactory * factory,const gchar * name)
name|gimp_data_factory_data_new
parameter_list|(
name|GimpDataFactory
modifier|*
name|factory
parameter_list|,
specifier|const
name|gchar
modifier|*
name|name
parameter_list|)
block|{
name|g_return_val_if_fail
argument_list|(
name|GIMP_IS_DATA_FACTORY
argument_list|(
name|factory
argument_list|)
argument_list|,
name|NULL
argument_list|)
expr_stmt|;
name|g_return_val_if_fail
argument_list|(
name|name
operator|!=
name|NULL
argument_list|,
name|NULL
argument_list|)
expr_stmt|;
if|if
condition|(
name|factory
operator|->
name|data_new_func
condition|)
block|{
name|GimpBaseConfig
modifier|*
name|base_config
decl_stmt|;
name|GimpData
modifier|*
name|data
decl_stmt|;
name|base_config
operator|=
name|GIMP_BASE_CONFIG
argument_list|(
name|factory
operator|->
name|gimp
operator|->
name|config
argument_list|)
expr_stmt|;
name|data
operator|=
name|factory
operator|->
name|data_new_func
argument_list|(
name|name
argument_list|,
name|base_config
operator|->
name|stingy_memory_use
argument_list|)
expr_stmt|;
name|gimp_container_add
argument_list|(
name|factory
operator|->
name|container
argument_list|,
name|GIMP_OBJECT
argument_list|(
name|data
argument_list|)
argument_list|)
expr_stmt|;
name|g_object_unref
argument_list|(
name|G_OBJECT
argument_list|(
name|data
argument_list|)
argument_list|)
expr_stmt|;
return|return
name|data
return|;
block|}
return|return
name|NULL
return|;
block|}
end_function

begin_function
name|GimpData
modifier|*
DECL|function|gimp_data_factory_data_get_standard (GimpDataFactory * factory)
name|gimp_data_factory_data_get_standard
parameter_list|(
name|GimpDataFactory
modifier|*
name|factory
parameter_list|)
block|{
name|g_return_val_if_fail
argument_list|(
name|GIMP_IS_DATA_FACTORY
argument_list|(
name|factory
argument_list|)
argument_list|,
name|NULL
argument_list|)
expr_stmt|;
if|if
condition|(
name|factory
operator|->
name|data_get_standard_func
condition|)
return|return
name|factory
operator|->
name|data_get_standard_func
argument_list|()
return|;
return|return
name|NULL
return|;
block|}
end_function

begin_function
specifier|static
name|void
DECL|function|gimp_data_factory_data_load_callback (GimpDatafileData * file_data)
name|gimp_data_factory_data_load_callback
parameter_list|(
name|GimpDatafileData
modifier|*
name|file_data
parameter_list|)
block|{
name|GimpDataFactory
modifier|*
name|factory
decl_stmt|;
name|gint
name|i
decl_stmt|;
name|factory
operator|=
operator|(
name|GimpDataFactory
operator|*
operator|)
name|file_data
operator|->
name|user_data
expr_stmt|;
for|for
control|(
name|i
operator|=
literal|0
init|;
name|i
operator|<
name|factory
operator|->
name|n_loader_entries
condition|;
name|i
operator|++
control|)
block|{
if|if
condition|(
name|factory
operator|->
name|loader_entries
index|[
name|i
index|]
operator|.
name|extension
condition|)
block|{
if|if
condition|(
name|gimp_datafiles_check_extension
argument_list|(
name|file_data
operator|->
name|filename
argument_list|,
name|factory
operator|->
name|loader_entries
index|[
name|i
index|]
operator|.
name|extension
argument_list|)
condition|)
block|{
goto|goto
name|insert
goto|;
block|}
block|}
else|else
block|{
name|g_message
argument_list|(
name|_
argument_list|(
literal|"Trying legacy loader on\n"
literal|"file '%s'\n"
literal|"with unknown extension."
argument_list|)
argument_list|,
name|file_data
operator|->
name|filename
argument_list|)
expr_stmt|;
goto|goto
name|insert
goto|;
block|}
block|}
return|return;
name|insert
label|:
block|{
name|GimpBaseConfig
modifier|*
name|base_config
decl_stmt|;
name|GimpData
modifier|*
name|data
decl_stmt|;
name|base_config
operator|=
name|GIMP_BASE_CONFIG
argument_list|(
name|factory
operator|->
name|gimp
operator|->
name|config
argument_list|)
expr_stmt|;
name|data
operator|=
operator|(
name|GimpData
operator|*
operator|)
operator|(
operator|*
name|factory
operator|->
name|loader_entries
index|[
name|i
index|]
operator|.
name|load_func
operator|)
operator|(
name|file_data
operator|->
name|filename
operator|,
name|base_config
operator|->
name|stingy_memory_use
operator|)
expr_stmt|;
if|if
condition|(
operator|!
name|data
condition|)
block|{
name|g_message
argument_list|(
name|_
argument_list|(
literal|"Warning: Failed to load data from\n'%s'"
argument_list|)
argument_list|,
name|file_data
operator|->
name|filename
argument_list|)
expr_stmt|;
block|}
else|else
block|{
name|gimp_container_add
argument_list|(
name|factory
operator|->
name|container
argument_list|,
name|GIMP_OBJECT
argument_list|(
name|data
argument_list|)
argument_list|)
expr_stmt|;
name|g_object_unref
argument_list|(
name|G_OBJECT
argument_list|(
name|data
argument_list|)
argument_list|)
expr_stmt|;
block|}
block|}
block|}
end_function

end_unit

