begin_unit|revision:0.9.5;language:C;cregit-version:0.0.1
begin_comment
comment|/* GIMP - The GNU Image Manipulation Program  * Copyright (C) 1995 Spencer Kimball and Peter Mattis  *  * gimpdataloaderfactory.c  * Copyright (C) 2001-2018 Michael Natterer<mitch@gimp.org>  *  * This program is free software: you can redistribute it and/or modify  * it under the terms of the GNU General Public License as published by  * the Free Software Foundation; either version 3 of the License, or  * (at your option) any later version.  *  * This program is distributed in the hope that it will be useful,  * but WITHOUT ANY WARRANTY; without even the implied warranty of  * MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the  * GNU General Public License for more details.  *  * You should have received a copy of the GNU General Public License  * along with this program.  If not, see<http://www.gnu.org/licenses/>.  */
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
file|<gdk-pixbuf/gdk-pixbuf.h>
end_include

begin_include
include|#
directive|include
file|<gegl.h>
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
file|"gimp.h"
end_include

begin_include
include|#
directive|include
file|"gimp-utils.h"
end_include

begin_include
include|#
directive|include
file|"gimpcontainer.h"
end_include

begin_include
include|#
directive|include
file|"gimpdata.h"
end_include

begin_include
include|#
directive|include
file|"gimpdataloaderfactory.h"
end_include

begin_include
include|#
directive|include
file|"gimp-intl.h"
end_include

begin_comment
comment|/* Data files that have this string in their path are considered  * obsolete and are only kept around for backwards compatibility  */
end_comment

begin_define
DECL|macro|GIMP_OBSOLETE_DATA_DIR_NAME
define|#
directive|define
name|GIMP_OBSOLETE_DATA_DIR_NAME
value|"gimp-obsolete-files"
end_define

begin_typedef
DECL|typedef|GimpDataLoader
typedef|typedef
name|struct
name|_GimpDataLoader
name|GimpDataLoader
typedef|;
end_typedef

begin_struct
DECL|struct|_GimpDataLoader
struct|struct
name|_GimpDataLoader
block|{
DECL|member|name
name|gchar
modifier|*
name|name
decl_stmt|;
DECL|member|load_func
name|GimpDataLoadFunc
name|load_func
decl_stmt|;
DECL|member|extension
name|gchar
modifier|*
name|extension
decl_stmt|;
DECL|member|writable
name|gboolean
name|writable
decl_stmt|;
block|}
struct|;
end_struct

begin_struct
DECL|struct|_GimpDataLoaderFactoryPrivate
struct|struct
name|_GimpDataLoaderFactoryPrivate
block|{
DECL|member|loaders
name|GList
modifier|*
name|loaders
decl_stmt|;
DECL|member|fallback
name|GimpDataLoader
modifier|*
name|fallback
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
value|(((GimpDataLoaderFactory *) (obj))->priv)
end_define

begin_function_decl
specifier|static
name|void
name|gimp_data_loader_factory_finalize
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
name|gimp_data_loader_factory_data_init
parameter_list|(
name|GimpDataFactory
modifier|*
name|factory
parameter_list|,
name|GimpContext
modifier|*
name|context
parameter_list|)
function_decl|;
end_function_decl

begin_function_decl
specifier|static
name|void
name|gimp_data_loader_factory_data_refresh
parameter_list|(
name|GimpDataFactory
modifier|*
name|factory
parameter_list|,
name|GimpContext
modifier|*
name|context
parameter_list|)
function_decl|;
end_function_decl

begin_function_decl
specifier|static
name|GimpDataLoader
modifier|*
name|gimp_data_loader_factory_get_loader
parameter_list|(
name|GimpDataFactory
modifier|*
name|factory
parameter_list|,
name|GFile
modifier|*
name|file
parameter_list|)
function_decl|;
end_function_decl

begin_function_decl
specifier|static
name|void
name|gimp_data_loader_factory_load
parameter_list|(
name|GimpDataFactory
modifier|*
name|factory
parameter_list|,
name|GimpContext
modifier|*
name|context
parameter_list|,
name|GHashTable
modifier|*
name|cache
parameter_list|)
function_decl|;
end_function_decl

begin_function_decl
specifier|static
name|void
name|gimp_data_loader_factory_load_directory
parameter_list|(
name|GimpDataFactory
modifier|*
name|factory
parameter_list|,
name|GimpContext
modifier|*
name|context
parameter_list|,
name|GHashTable
modifier|*
name|cache
parameter_list|,
name|gboolean
name|dir_writable
parameter_list|,
name|GFile
modifier|*
name|directory
parameter_list|,
name|GFile
modifier|*
name|top_directory
parameter_list|)
function_decl|;
end_function_decl

begin_function_decl
specifier|static
name|void
name|gimp_data_loader_factory_load_data
parameter_list|(
name|GimpDataFactory
modifier|*
name|factory
parameter_list|,
name|GimpContext
modifier|*
name|context
parameter_list|,
name|GHashTable
modifier|*
name|cache
parameter_list|,
name|gboolean
name|dir_writable
parameter_list|,
name|GFile
modifier|*
name|file
parameter_list|,
name|GFileInfo
modifier|*
name|info
parameter_list|,
name|GFile
modifier|*
name|top_directory
parameter_list|)
function_decl|;
end_function_decl

begin_function_decl
specifier|static
name|GimpDataLoader
modifier|*
name|gimp_data_loader_new
parameter_list|(
specifier|const
name|gchar
modifier|*
name|name
parameter_list|,
name|GimpDataLoadFunc
name|load_func
parameter_list|,
specifier|const
name|gchar
modifier|*
name|extension
parameter_list|,
name|gboolean
name|writable
parameter_list|)
function_decl|;
end_function_decl

begin_function_decl
specifier|static
name|void
name|gimp_data_loader_free
parameter_list|(
name|GimpDataLoader
modifier|*
name|loader
parameter_list|)
function_decl|;
end_function_decl

begin_macro
DECL|function|G_DEFINE_TYPE (GimpDataLoaderFactory,gimp_data_loader_factory,GIMP_TYPE_DATA_FACTORY)
name|G_DEFINE_TYPE
argument_list|(
argument|GimpDataLoaderFactory
argument_list|,
argument|gimp_data_loader_factory
argument_list|,
argument|GIMP_TYPE_DATA_FACTORY
argument_list|)
end_macro

begin_define
DECL|macro|parent_class
define|#
directive|define
name|parent_class
value|gimp_data_loader_factory_parent_class
end_define

begin_function
specifier|static
name|void
name|gimp_data_loader_factory_class_init
parameter_list|(
name|GimpDataLoaderFactoryClass
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
name|GimpDataFactoryClass
modifier|*
name|factory_class
init|=
name|GIMP_DATA_FACTORY_CLASS
argument_list|(
name|klass
argument_list|)
decl_stmt|;
name|object_class
operator|->
name|finalize
operator|=
name|gimp_data_loader_factory_finalize
expr_stmt|;
name|factory_class
operator|->
name|data_init
operator|=
name|gimp_data_loader_factory_data_init
expr_stmt|;
name|factory_class
operator|->
name|data_refresh
operator|=
name|gimp_data_loader_factory_data_refresh
expr_stmt|;
name|g_type_class_add_private
argument_list|(
name|klass
argument_list|,
sizeof|sizeof
argument_list|(
name|GimpDataLoaderFactoryPrivate
argument_list|)
argument_list|)
expr_stmt|;
block|}
end_function

begin_function
specifier|static
name|void
DECL|function|gimp_data_loader_factory_init (GimpDataLoaderFactory * factory)
name|gimp_data_loader_factory_init
parameter_list|(
name|GimpDataLoaderFactory
modifier|*
name|factory
parameter_list|)
block|{
name|factory
operator|->
name|priv
operator|=
name|G_TYPE_INSTANCE_GET_PRIVATE
argument_list|(
name|factory
argument_list|,
name|GIMP_TYPE_DATA_LOADER_FACTORY
argument_list|,
name|GimpDataLoaderFactoryPrivate
argument_list|)
expr_stmt|;
block|}
end_function

begin_function
specifier|static
name|void
DECL|function|gimp_data_loader_factory_finalize (GObject * object)
name|gimp_data_loader_factory_finalize
parameter_list|(
name|GObject
modifier|*
name|object
parameter_list|)
block|{
name|GimpDataLoaderFactoryPrivate
modifier|*
name|priv
init|=
name|GET_PRIVATE
argument_list|(
name|object
argument_list|)
decl_stmt|;
name|g_list_free_full
argument_list|(
name|priv
operator|->
name|loaders
argument_list|,
operator|(
name|GDestroyNotify
operator|)
name|gimp_data_loader_free
argument_list|)
expr_stmt|;
name|priv
operator|->
name|loaders
operator|=
name|NULL
expr_stmt|;
name|g_clear_pointer
argument_list|(
operator|&
name|priv
operator|->
name|fallback
argument_list|,
name|gimp_data_loader_free
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
DECL|function|gimp_data_loader_factory_data_init (GimpDataFactory * factory,GimpContext * context)
name|gimp_data_loader_factory_data_init
parameter_list|(
name|GimpDataFactory
modifier|*
name|factory
parameter_list|,
name|GimpContext
modifier|*
name|context
parameter_list|)
block|{
name|gimp_data_loader_factory_load
argument_list|(
name|factory
argument_list|,
name|context
argument_list|,
name|NULL
argument_list|)
expr_stmt|;
block|}
end_function

begin_function
specifier|static
name|void
DECL|function|gimp_data_loader_factory_refresh_cache_add (GimpDataFactory * factory,GimpData * data,gpointer user_data)
name|gimp_data_loader_factory_refresh_cache_add
parameter_list|(
name|GimpDataFactory
modifier|*
name|factory
parameter_list|,
name|GimpData
modifier|*
name|data
parameter_list|,
name|gpointer
name|user_data
parameter_list|)
block|{
name|GFile
modifier|*
name|file
init|=
name|gimp_data_get_file
argument_list|(
name|data
argument_list|)
decl_stmt|;
if|if
condition|(
name|file
condition|)
block|{
name|GimpContainer
modifier|*
name|container
init|=
name|gimp_data_factory_get_container
argument_list|(
name|factory
argument_list|)
decl_stmt|;
name|GHashTable
modifier|*
name|cache
init|=
name|user_data
decl_stmt|;
name|GList
modifier|*
name|list
decl_stmt|;
name|g_object_ref
argument_list|(
name|data
argument_list|)
expr_stmt|;
name|gimp_container_remove
argument_list|(
name|container
argument_list|,
name|GIMP_OBJECT
argument_list|(
name|data
argument_list|)
argument_list|)
expr_stmt|;
name|list
operator|=
name|g_hash_table_lookup
argument_list|(
name|cache
argument_list|,
name|file
argument_list|)
expr_stmt|;
name|list
operator|=
name|g_list_prepend
argument_list|(
name|list
argument_list|,
name|data
argument_list|)
expr_stmt|;
name|g_hash_table_insert
argument_list|(
name|cache
argument_list|,
name|file
argument_list|,
name|list
argument_list|)
expr_stmt|;
block|}
block|}
end_function

begin_function
specifier|static
name|gboolean
DECL|function|gimp_data_loader_factory_refresh_cache_remove (gpointer key,gpointer value,gpointer user_data)
name|gimp_data_loader_factory_refresh_cache_remove
parameter_list|(
name|gpointer
name|key
parameter_list|,
name|gpointer
name|value
parameter_list|,
name|gpointer
name|user_data
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
name|value
init|;
name|list
condition|;
name|list
operator|=
name|list
operator|->
name|next
control|)
name|g_object_unref
argument_list|(
name|list
operator|->
name|data
argument_list|)
expr_stmt|;
name|g_list_free
argument_list|(
name|value
argument_list|)
expr_stmt|;
return|return
name|TRUE
return|;
block|}
end_function

begin_function
specifier|static
name|void
DECL|function|gimp_data_loader_factory_data_refresh (GimpDataFactory * factory,GimpContext * context)
name|gimp_data_loader_factory_data_refresh
parameter_list|(
name|GimpDataFactory
modifier|*
name|factory
parameter_list|,
name|GimpContext
modifier|*
name|context
parameter_list|)
block|{
name|GimpContainer
modifier|*
name|container
init|=
name|gimp_data_factory_get_container
argument_list|(
name|factory
argument_list|)
decl_stmt|;
name|GHashTable
modifier|*
name|cache
decl_stmt|;
name|gimp_container_freeze
argument_list|(
name|container
argument_list|)
expr_stmt|;
comment|/*  First, save all dirty data objects  */
name|gimp_data_factory_data_save
argument_list|(
name|factory
argument_list|)
expr_stmt|;
name|cache
operator|=
name|g_hash_table_new
argument_list|(
name|g_file_hash
argument_list|,
operator|(
name|GEqualFunc
operator|)
name|g_file_equal
argument_list|)
expr_stmt|;
name|gimp_data_factory_data_foreach
argument_list|(
name|factory
argument_list|,
name|TRUE
argument_list|,
name|gimp_data_loader_factory_refresh_cache_add
argument_list|,
name|cache
argument_list|)
expr_stmt|;
comment|/*  Now the cache contains a GFile => list-of-objects mapping of    *  the old objects. So we should now traverse the directory and for    *  each file load it only if its mtime is newer.    *    *  Once a file was added, it is removed from the cache, so the only    *  objects remaining there will be those that are not present on    *  the disk (that have to be destroyed)    */
name|gimp_data_loader_factory_load
argument_list|(
name|factory
argument_list|,
name|context
argument_list|,
name|cache
argument_list|)
expr_stmt|;
comment|/*  Now all the data is loaded. Free what remains in the cache  */
name|g_hash_table_foreach_remove
argument_list|(
name|cache
argument_list|,
name|gimp_data_loader_factory_refresh_cache_remove
argument_list|,
name|NULL
argument_list|)
expr_stmt|;
name|g_hash_table_destroy
argument_list|(
name|cache
argument_list|)
expr_stmt|;
name|gimp_container_thaw
argument_list|(
name|container
argument_list|)
expr_stmt|;
block|}
end_function

begin_comment
comment|/*  public functions  */
end_comment

begin_function
name|GimpDataFactory
modifier|*
DECL|function|gimp_data_loader_factory_new (Gimp * gimp,GType data_type,const gchar * path_property_name,const gchar * writable_property_name,GimpDataNewFunc new_func,GimpDataGetStandardFunc get_standard_func)
name|gimp_data_loader_factory_new
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
name|path_property_name
parameter_list|,
specifier|const
name|gchar
modifier|*
name|writable_property_name
parameter_list|,
name|GimpDataNewFunc
name|new_func
parameter_list|,
name|GimpDataGetStandardFunc
name|get_standard_func
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
name|path_property_name
operator|!=
name|NULL
argument_list|,
name|NULL
argument_list|)
expr_stmt|;
name|g_return_val_if_fail
argument_list|(
name|writable_property_name
operator|!=
name|NULL
argument_list|,
name|NULL
argument_list|)
expr_stmt|;
return|return
name|g_object_new
argument_list|(
name|GIMP_TYPE_DATA_LOADER_FACTORY
argument_list|,
literal|"gimp"
argument_list|,
name|gimp
argument_list|,
literal|"data-type"
argument_list|,
name|data_type
argument_list|,
literal|"path-property-name"
argument_list|,
name|path_property_name
argument_list|,
literal|"writable-property-name"
argument_list|,
name|writable_property_name
argument_list|,
literal|"new-func"
argument_list|,
name|new_func
argument_list|,
literal|"get-standard-func"
argument_list|,
name|get_standard_func
argument_list|,
name|NULL
argument_list|)
return|;
block|}
end_function

begin_function
name|void
DECL|function|gimp_data_loader_factory_add_loader (GimpDataFactory * factory,const gchar * name,GimpDataLoadFunc load_func,const gchar * extension,gboolean writable)
name|gimp_data_loader_factory_add_loader
parameter_list|(
name|GimpDataFactory
modifier|*
name|factory
parameter_list|,
specifier|const
name|gchar
modifier|*
name|name
parameter_list|,
name|GimpDataLoadFunc
name|load_func
parameter_list|,
specifier|const
name|gchar
modifier|*
name|extension
parameter_list|,
name|gboolean
name|writable
parameter_list|)
block|{
name|GimpDataLoaderFactoryPrivate
modifier|*
name|priv
decl_stmt|;
name|GimpDataLoader
modifier|*
name|loader
decl_stmt|;
name|g_return_if_fail
argument_list|(
name|GIMP_IS_DATA_LOADER_FACTORY
argument_list|(
name|factory
argument_list|)
argument_list|)
expr_stmt|;
name|g_return_if_fail
argument_list|(
name|name
operator|!=
name|NULL
argument_list|)
expr_stmt|;
name|g_return_if_fail
argument_list|(
name|load_func
operator|!=
name|NULL
argument_list|)
expr_stmt|;
name|g_return_if_fail
argument_list|(
name|extension
operator|!=
name|NULL
argument_list|)
expr_stmt|;
name|priv
operator|=
name|GET_PRIVATE
argument_list|(
name|factory
argument_list|)
expr_stmt|;
name|loader
operator|=
name|gimp_data_loader_new
argument_list|(
name|name
argument_list|,
name|load_func
argument_list|,
name|extension
argument_list|,
name|writable
argument_list|)
expr_stmt|;
name|priv
operator|->
name|loaders
operator|=
name|g_list_append
argument_list|(
name|priv
operator|->
name|loaders
argument_list|,
name|loader
argument_list|)
expr_stmt|;
block|}
end_function

begin_function
name|void
DECL|function|gimp_data_loader_factory_add_fallback (GimpDataFactory * factory,const gchar * name,GimpDataLoadFunc load_func)
name|gimp_data_loader_factory_add_fallback
parameter_list|(
name|GimpDataFactory
modifier|*
name|factory
parameter_list|,
specifier|const
name|gchar
modifier|*
name|name
parameter_list|,
name|GimpDataLoadFunc
name|load_func
parameter_list|)
block|{
name|GimpDataLoaderFactoryPrivate
modifier|*
name|priv
decl_stmt|;
name|g_return_if_fail
argument_list|(
name|GIMP_IS_DATA_LOADER_FACTORY
argument_list|(
name|factory
argument_list|)
argument_list|)
expr_stmt|;
name|g_return_if_fail
argument_list|(
name|name
operator|!=
name|NULL
argument_list|)
expr_stmt|;
name|g_return_if_fail
argument_list|(
name|load_func
operator|!=
name|NULL
argument_list|)
expr_stmt|;
name|priv
operator|=
name|GET_PRIVATE
argument_list|(
name|factory
argument_list|)
expr_stmt|;
name|g_clear_pointer
argument_list|(
operator|&
name|priv
operator|->
name|fallback
argument_list|,
name|gimp_data_loader_free
argument_list|)
expr_stmt|;
name|priv
operator|->
name|fallback
operator|=
name|gimp_data_loader_new
argument_list|(
name|name
argument_list|,
name|load_func
argument_list|,
name|NULL
argument_list|,
name|FALSE
argument_list|)
expr_stmt|;
block|}
end_function

begin_comment
comment|/*  private functions  */
end_comment

begin_function
specifier|static
name|GimpDataLoader
modifier|*
DECL|function|gimp_data_loader_factory_get_loader (GimpDataFactory * factory,GFile * file)
name|gimp_data_loader_factory_get_loader
parameter_list|(
name|GimpDataFactory
modifier|*
name|factory
parameter_list|,
name|GFile
modifier|*
name|file
parameter_list|)
block|{
name|GimpDataLoaderFactoryPrivate
modifier|*
name|priv
init|=
name|GET_PRIVATE
argument_list|(
name|factory
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
name|priv
operator|->
name|loaders
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
name|GimpDataLoader
modifier|*
name|loader
init|=
name|list
operator|->
name|data
decl_stmt|;
if|if
condition|(
name|gimp_file_has_extension
argument_list|(
name|file
argument_list|,
name|loader
operator|->
name|extension
argument_list|)
condition|)
return|return
name|loader
return|;
block|}
return|return
name|priv
operator|->
name|fallback
return|;
block|}
end_function

begin_function
specifier|static
name|void
DECL|function|gimp_data_loader_factory_load (GimpDataFactory * factory,GimpContext * context,GHashTable * cache)
name|gimp_data_loader_factory_load
parameter_list|(
name|GimpDataFactory
modifier|*
name|factory
parameter_list|,
name|GimpContext
modifier|*
name|context
parameter_list|,
name|GHashTable
modifier|*
name|cache
parameter_list|)
block|{
name|GList
modifier|*
name|path
decl_stmt|;
name|GList
modifier|*
name|writable_path
decl_stmt|;
name|GList
modifier|*
name|list
decl_stmt|;
name|path
operator|=
name|gimp_data_factory_get_data_path
argument_list|(
name|factory
argument_list|)
expr_stmt|;
name|writable_path
operator|=
name|gimp_data_factory_get_data_path_writable
argument_list|(
name|factory
argument_list|)
expr_stmt|;
for|for
control|(
name|list
operator|=
name|path
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
name|gboolean
name|dir_writable
init|=
name|FALSE
decl_stmt|;
if|if
condition|(
name|g_list_find_custom
argument_list|(
name|writable_path
argument_list|,
name|list
operator|->
name|data
argument_list|,
operator|(
name|GCompareFunc
operator|)
name|gimp_file_compare
argument_list|)
condition|)
name|dir_writable
operator|=
name|TRUE
expr_stmt|;
name|gimp_data_loader_factory_load_directory
argument_list|(
name|factory
argument_list|,
name|context
argument_list|,
name|cache
argument_list|,
name|dir_writable
argument_list|,
name|list
operator|->
name|data
argument_list|,
name|list
operator|->
name|data
argument_list|)
expr_stmt|;
block|}
name|g_list_free_full
argument_list|(
name|path
argument_list|,
operator|(
name|GDestroyNotify
operator|)
name|g_object_unref
argument_list|)
expr_stmt|;
name|g_list_free_full
argument_list|(
name|writable_path
argument_list|,
operator|(
name|GDestroyNotify
operator|)
name|g_object_unref
argument_list|)
expr_stmt|;
block|}
end_function

begin_function
specifier|static
name|void
DECL|function|gimp_data_loader_factory_load_directory (GimpDataFactory * factory,GimpContext * context,GHashTable * cache,gboolean dir_writable,GFile * directory,GFile * top_directory)
name|gimp_data_loader_factory_load_directory
parameter_list|(
name|GimpDataFactory
modifier|*
name|factory
parameter_list|,
name|GimpContext
modifier|*
name|context
parameter_list|,
name|GHashTable
modifier|*
name|cache
parameter_list|,
name|gboolean
name|dir_writable
parameter_list|,
name|GFile
modifier|*
name|directory
parameter_list|,
name|GFile
modifier|*
name|top_directory
parameter_list|)
block|{
name|GFileEnumerator
modifier|*
name|enumerator
decl_stmt|;
name|enumerator
operator|=
name|g_file_enumerate_children
argument_list|(
name|directory
argument_list|,
name|G_FILE_ATTRIBUTE_STANDARD_NAME
literal|","
name|G_FILE_ATTRIBUTE_STANDARD_IS_HIDDEN
literal|","
name|G_FILE_ATTRIBUTE_STANDARD_TYPE
literal|","
name|G_FILE_ATTRIBUTE_TIME_MODIFIED
argument_list|,
name|G_FILE_QUERY_INFO_NONE
argument_list|,
name|NULL
argument_list|,
name|NULL
argument_list|)
expr_stmt|;
if|if
condition|(
name|enumerator
condition|)
block|{
name|GFileInfo
modifier|*
name|info
decl_stmt|;
while|while
condition|(
operator|(
name|info
operator|=
name|g_file_enumerator_next_file
argument_list|(
name|enumerator
argument_list|,
name|NULL
argument_list|,
name|NULL
argument_list|)
operator|)
condition|)
block|{
name|GFileType
name|file_type
decl_stmt|;
name|GFile
modifier|*
name|child
decl_stmt|;
if|if
condition|(
name|g_file_info_get_is_hidden
argument_list|(
name|info
argument_list|)
condition|)
block|{
name|g_object_unref
argument_list|(
name|info
argument_list|)
expr_stmt|;
continue|continue;
block|}
name|file_type
operator|=
name|g_file_info_get_file_type
argument_list|(
name|info
argument_list|)
expr_stmt|;
name|child
operator|=
name|g_file_enumerator_get_child
argument_list|(
name|enumerator
argument_list|,
name|info
argument_list|)
expr_stmt|;
if|if
condition|(
name|file_type
operator|==
name|G_FILE_TYPE_DIRECTORY
condition|)
block|{
name|gimp_data_loader_factory_load_directory
argument_list|(
name|factory
argument_list|,
name|context
argument_list|,
name|cache
argument_list|,
name|dir_writable
argument_list|,
name|child
argument_list|,
name|top_directory
argument_list|)
expr_stmt|;
block|}
elseif|else
if|if
condition|(
name|file_type
operator|==
name|G_FILE_TYPE_REGULAR
condition|)
block|{
name|gimp_data_loader_factory_load_data
argument_list|(
name|factory
argument_list|,
name|context
argument_list|,
name|cache
argument_list|,
name|dir_writable
argument_list|,
name|child
argument_list|,
name|info
argument_list|,
name|top_directory
argument_list|)
expr_stmt|;
block|}
name|g_object_unref
argument_list|(
name|child
argument_list|)
expr_stmt|;
name|g_object_unref
argument_list|(
name|info
argument_list|)
expr_stmt|;
block|}
name|g_object_unref
argument_list|(
name|enumerator
argument_list|)
expr_stmt|;
block|}
block|}
end_function

begin_function
specifier|static
name|void
DECL|function|gimp_data_loader_factory_load_data (GimpDataFactory * factory,GimpContext * context,GHashTable * cache,gboolean dir_writable,GFile * file,GFileInfo * info,GFile * top_directory)
name|gimp_data_loader_factory_load_data
parameter_list|(
name|GimpDataFactory
modifier|*
name|factory
parameter_list|,
name|GimpContext
modifier|*
name|context
parameter_list|,
name|GHashTable
modifier|*
name|cache
parameter_list|,
name|gboolean
name|dir_writable
parameter_list|,
name|GFile
modifier|*
name|file
parameter_list|,
name|GFileInfo
modifier|*
name|info
parameter_list|,
name|GFile
modifier|*
name|top_directory
parameter_list|)
block|{
name|GimpDataLoader
modifier|*
name|loader
decl_stmt|;
name|GimpContainer
modifier|*
name|container
decl_stmt|;
name|GimpContainer
modifier|*
name|container_obsolete
decl_stmt|;
name|GList
modifier|*
name|data_list
init|=
name|NULL
decl_stmt|;
name|GInputStream
modifier|*
name|input
decl_stmt|;
name|guint64
name|mtime
decl_stmt|;
name|GError
modifier|*
name|error
init|=
name|NULL
decl_stmt|;
name|loader
operator|=
name|gimp_data_loader_factory_get_loader
argument_list|(
name|factory
argument_list|,
name|file
argument_list|)
expr_stmt|;
if|if
condition|(
operator|!
name|loader
condition|)
return|return;
name|container
operator|=
name|gimp_data_factory_get_container
argument_list|(
name|factory
argument_list|)
expr_stmt|;
name|container_obsolete
operator|=
name|gimp_data_factory_get_container_obsolete
argument_list|(
name|factory
argument_list|)
expr_stmt|;
if|if
condition|(
name|gimp_data_factory_get_gimp
argument_list|(
name|factory
argument_list|)
operator|->
name|be_verbose
condition|)
name|g_print
argument_list|(
literal|"  Loading %s\n"
argument_list|,
name|gimp_file_get_utf8_name
argument_list|(
name|file
argument_list|)
argument_list|)
expr_stmt|;
name|mtime
operator|=
name|g_file_info_get_attribute_uint64
argument_list|(
name|info
argument_list|,
name|G_FILE_ATTRIBUTE_TIME_MODIFIED
argument_list|)
expr_stmt|;
if|if
condition|(
name|cache
condition|)
block|{
name|GList
modifier|*
name|cached_data
init|=
name|g_hash_table_lookup
argument_list|(
name|cache
argument_list|,
name|file
argument_list|)
decl_stmt|;
if|if
condition|(
name|cached_data
operator|&&
name|gimp_data_get_mtime
argument_list|(
name|cached_data
operator|->
name|data
argument_list|)
operator|!=
literal|0
operator|&&
name|gimp_data_get_mtime
argument_list|(
name|cached_data
operator|->
name|data
argument_list|)
operator|==
name|mtime
condition|)
block|{
name|GList
modifier|*
name|list
decl_stmt|;
for|for
control|(
name|list
operator|=
name|cached_data
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
name|gimp_container_add
argument_list|(
name|container
argument_list|,
name|list
operator|->
name|data
argument_list|)
expr_stmt|;
return|return;
block|}
block|}
name|input
operator|=
name|G_INPUT_STREAM
argument_list|(
name|g_file_read
argument_list|(
name|file
argument_list|,
name|NULL
argument_list|,
operator|&
name|error
argument_list|)
argument_list|)
expr_stmt|;
if|if
condition|(
name|input
condition|)
block|{
name|GInputStream
modifier|*
name|buffered
init|=
name|g_buffered_input_stream_new
argument_list|(
name|input
argument_list|)
decl_stmt|;
name|data_list
operator|=
name|loader
operator|->
name|load_func
argument_list|(
name|context
argument_list|,
name|file
argument_list|,
name|buffered
argument_list|,
operator|&
name|error
argument_list|)
expr_stmt|;
if|if
condition|(
name|error
condition|)
block|{
name|g_prefix_error
argument_list|(
operator|&
name|error
argument_list|,
name|_
argument_list|(
literal|"Error loading '%s': "
argument_list|)
argument_list|,
name|gimp_file_get_utf8_name
argument_list|(
name|file
argument_list|)
argument_list|)
expr_stmt|;
block|}
elseif|else
if|if
condition|(
operator|!
name|data_list
condition|)
block|{
name|g_set_error
argument_list|(
operator|&
name|error
argument_list|,
name|GIMP_DATA_ERROR
argument_list|,
name|GIMP_DATA_ERROR_READ
argument_list|,
name|_
argument_list|(
literal|"Error loading '%s'"
argument_list|)
argument_list|,
name|gimp_file_get_utf8_name
argument_list|(
name|file
argument_list|)
argument_list|)
expr_stmt|;
block|}
name|g_object_unref
argument_list|(
name|buffered
argument_list|)
expr_stmt|;
name|g_object_unref
argument_list|(
name|input
argument_list|)
expr_stmt|;
block|}
else|else
block|{
name|g_prefix_error
argument_list|(
operator|&
name|error
argument_list|,
name|_
argument_list|(
literal|"Could not open '%s' for reading: "
argument_list|)
argument_list|,
name|gimp_file_get_utf8_name
argument_list|(
name|file
argument_list|)
argument_list|)
expr_stmt|;
block|}
if|if
condition|(
name|G_LIKELY
argument_list|(
name|data_list
argument_list|)
condition|)
block|{
name|GList
modifier|*
name|list
decl_stmt|;
name|gchar
modifier|*
name|uri
decl_stmt|;
name|gboolean
name|obsolete
decl_stmt|;
name|gboolean
name|writable
init|=
name|FALSE
decl_stmt|;
name|gboolean
name|deletable
init|=
name|FALSE
decl_stmt|;
name|uri
operator|=
name|g_file_get_uri
argument_list|(
name|file
argument_list|)
expr_stmt|;
name|obsolete
operator|=
operator|(
name|strstr
argument_list|(
name|uri
argument_list|,
name|GIMP_OBSOLETE_DATA_DIR_NAME
argument_list|)
operator|!=
literal|0
operator|)
expr_stmt|;
name|g_free
argument_list|(
name|uri
argument_list|)
expr_stmt|;
comment|/* obsolete files are immutable, don't check their writability */
if|if
condition|(
operator|!
name|obsolete
condition|)
block|{
name|deletable
operator|=
operator|(
name|g_list_length
argument_list|(
name|data_list
argument_list|)
operator|==
literal|1
operator|&&
name|dir_writable
operator|)
expr_stmt|;
name|writable
operator|=
operator|(
name|deletable
operator|&&
name|loader
operator|->
name|writable
operator|)
expr_stmt|;
block|}
for|for
control|(
name|list
operator|=
name|data_list
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
init|=
name|list
operator|->
name|data
decl_stmt|;
name|gimp_data_set_file
argument_list|(
name|data
argument_list|,
name|file
argument_list|,
name|writable
argument_list|,
name|deletable
argument_list|)
expr_stmt|;
name|gimp_data_set_mtime
argument_list|(
name|data
argument_list|,
name|mtime
argument_list|)
expr_stmt|;
name|gimp_data_clean
argument_list|(
name|data
argument_list|)
expr_stmt|;
if|if
condition|(
name|obsolete
condition|)
block|{
name|gimp_container_add
argument_list|(
name|container_obsolete
argument_list|,
name|GIMP_OBJECT
argument_list|(
name|data
argument_list|)
argument_list|)
expr_stmt|;
block|}
else|else
block|{
name|gimp_data_set_folder_tags
argument_list|(
name|data
argument_list|,
name|top_directory
argument_list|)
expr_stmt|;
name|gimp_container_add
argument_list|(
name|container
argument_list|,
name|GIMP_OBJECT
argument_list|(
name|data
argument_list|)
argument_list|)
expr_stmt|;
block|}
name|g_object_unref
argument_list|(
name|data
argument_list|)
expr_stmt|;
block|}
name|g_list_free
argument_list|(
name|data_list
argument_list|)
expr_stmt|;
block|}
comment|/*  not else { ... } because loader->load_func() can return a list    *  of data objects *and* an error message if loading failed after    *  something was already loaded    */
if|if
condition|(
name|G_UNLIKELY
argument_list|(
name|error
argument_list|)
condition|)
block|{
name|gimp_message
argument_list|(
name|gimp_data_factory_get_gimp
argument_list|(
name|factory
argument_list|)
argument_list|,
name|NULL
argument_list|,
name|GIMP_MESSAGE_ERROR
argument_list|,
name|_
argument_list|(
literal|"Failed to load data:\n\n%s"
argument_list|)
argument_list|,
name|error
operator|->
name|message
argument_list|)
expr_stmt|;
name|g_clear_error
argument_list|(
operator|&
name|error
argument_list|)
expr_stmt|;
block|}
block|}
end_function

begin_function
specifier|static
name|GimpDataLoader
modifier|*
DECL|function|gimp_data_loader_new (const gchar * name,GimpDataLoadFunc load_func,const gchar * extension,gboolean writable)
name|gimp_data_loader_new
parameter_list|(
specifier|const
name|gchar
modifier|*
name|name
parameter_list|,
name|GimpDataLoadFunc
name|load_func
parameter_list|,
specifier|const
name|gchar
modifier|*
name|extension
parameter_list|,
name|gboolean
name|writable
parameter_list|)
block|{
name|GimpDataLoader
modifier|*
name|loader
init|=
name|g_slice_new
argument_list|(
name|GimpDataLoader
argument_list|)
decl_stmt|;
name|loader
operator|->
name|name
operator|=
name|g_strdup
argument_list|(
name|name
argument_list|)
expr_stmt|;
name|loader
operator|->
name|load_func
operator|=
name|load_func
expr_stmt|;
name|loader
operator|->
name|extension
operator|=
name|g_strdup
argument_list|(
name|extension
argument_list|)
expr_stmt|;
name|loader
operator|->
name|writable
operator|=
name|writable
condition|?
name|TRUE
else|:
name|FALSE
expr_stmt|;
return|return
name|loader
return|;
block|}
end_function

begin_function
specifier|static
name|void
DECL|function|gimp_data_loader_free (GimpDataLoader * loader)
name|gimp_data_loader_free
parameter_list|(
name|GimpDataLoader
modifier|*
name|loader
parameter_list|)
block|{
name|g_free
argument_list|(
name|loader
operator|->
name|name
argument_list|)
expr_stmt|;
name|g_free
argument_list|(
name|loader
operator|->
name|extension
argument_list|)
expr_stmt|;
name|g_slice_free
argument_list|(
name|GimpDataLoader
argument_list|,
name|loader
argument_list|)
expr_stmt|;
block|}
end_function

end_unit

