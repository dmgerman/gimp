begin_unit|revision:0.9.5;language:C;cregit-version:0.0.1
begin_comment
comment|/* GIMP - The GNU Image Manipulation Program  * Copyright (C) 1995 Spencer Kimball and Peter Mattis  *  * gimptagcache.c  * Copyright (C) 2008 Aurimas JuÅ¡ka<aurisj@svn.gnome.org>  *  * This program is free software: you can redistribute it and/or modify  * it under the terms of the GNU General Public License as published by  * the Free Software Foundation; either version 3 of the License, or  * (at your option) any later version.  *  * This program is distributed in the hope that it will be useful,  * but WITHOUT ANY WARRANTY; without even the implied warranty of  * MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the  * GNU General Public License for more details.  *  * You should have received a copy of the GNU General Public License  * along with this program.  If not, see<http://www.gnu.org/licenses/>.  */
end_comment

begin_include
include|#
directive|include
file|"config.h"
end_include

begin_include
include|#
directive|include
file|<stdlib.h>
end_include

begin_include
include|#
directive|include
file|<string.h>
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
file|"libgimpmath/gimpmath.h"
end_include

begin_include
include|#
directive|include
file|"libgimpconfig/gimpconfig.h"
end_include

begin_include
include|#
directive|include
file|"core-types.h"
end_include

begin_include
include|#
directive|include
file|"config/gimpxmlparser.h"
end_include

begin_include
include|#
directive|include
file|"gimp-utils.h"
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
file|"gimplist.h"
end_include

begin_include
include|#
directive|include
file|"gimptag.h"
end_include

begin_include
include|#
directive|include
file|"gimptagcache.h"
end_include

begin_include
include|#
directive|include
file|"gimptagged.h"
end_include

begin_include
include|#
directive|include
file|"gimp-intl.h"
end_include

begin_define
DECL|macro|GIMP_TAG_CACHE_FILE
define|#
directive|define
name|GIMP_TAG_CACHE_FILE
value|"tags.xml"
end_define

begin_enum
enum|enum
DECL|enum|__anon29bb184a0103
block|{
DECL|enumerator|PROP_0
name|PROP_0
block|,
DECL|enumerator|PROP_GIMP
name|PROP_GIMP
block|}
enum|;
end_enum

begin_typedef
typedef|typedef
struct|struct
DECL|struct|__anon29bb184a0208
block|{
DECL|member|identifier
name|GQuark
name|identifier
decl_stmt|;
DECL|member|checksum
name|GQuark
name|checksum
decl_stmt|;
DECL|member|tags
name|GList
modifier|*
name|tags
decl_stmt|;
DECL|member|referenced
name|guint
name|referenced
range|:
literal|1
decl_stmt|;
DECL|typedef|GimpTagCacheRecord
block|}
name|GimpTagCacheRecord
typedef|;
end_typedef

begin_typedef
typedef|typedef
struct|struct
DECL|struct|__anon29bb184a0308
block|{
DECL|member|records
name|GArray
modifier|*
name|records
decl_stmt|;
DECL|member|current_record
name|GimpTagCacheRecord
name|current_record
decl_stmt|;
DECL|typedef|GimpTagCacheParseData
block|}
name|GimpTagCacheParseData
typedef|;
end_typedef

begin_struct
DECL|struct|_GimpTagCachePriv
struct|struct
name|_GimpTagCachePriv
block|{
DECL|member|records
name|GArray
modifier|*
name|records
decl_stmt|;
DECL|member|containers
name|GList
modifier|*
name|containers
decl_stmt|;
block|}
struct|;
end_struct

begin_function_decl
specifier|static
name|void
name|gimp_tag_cache_finalize
parameter_list|(
name|GObject
modifier|*
name|object
parameter_list|)
function_decl|;
end_function_decl

begin_function_decl
specifier|static
name|gint64
name|gimp_tag_cache_get_memsize
parameter_list|(
name|GimpObject
modifier|*
name|object
parameter_list|,
name|gint64
modifier|*
name|gui_size
parameter_list|)
function_decl|;
end_function_decl

begin_function_decl
specifier|static
name|void
name|gimp_tag_cache_object_initialize
parameter_list|(
name|GimpTagged
modifier|*
name|tagged
parameter_list|,
name|GimpTagCache
modifier|*
name|cache
parameter_list|)
function_decl|;
end_function_decl

begin_function_decl
specifier|static
name|void
name|gimp_tag_cache_add_object
parameter_list|(
name|GimpTagCache
modifier|*
name|cache
parameter_list|,
name|GimpTagged
modifier|*
name|tagged
parameter_list|)
function_decl|;
end_function_decl

begin_function_decl
specifier|static
name|void
name|gimp_tag_cache_load_start_element
parameter_list|(
name|GMarkupParseContext
modifier|*
name|context
parameter_list|,
specifier|const
name|gchar
modifier|*
name|element_name
parameter_list|,
specifier|const
name|gchar
modifier|*
modifier|*
name|attribute_names
parameter_list|,
specifier|const
name|gchar
modifier|*
modifier|*
name|attribute_values
parameter_list|,
name|gpointer
name|user_data
parameter_list|,
name|GError
modifier|*
modifier|*
name|error
parameter_list|)
function_decl|;
end_function_decl

begin_function_decl
specifier|static
name|void
name|gimp_tag_cache_load_end_element
parameter_list|(
name|GMarkupParseContext
modifier|*
name|context
parameter_list|,
specifier|const
name|gchar
modifier|*
name|element_name
parameter_list|,
name|gpointer
name|user_data
parameter_list|,
name|GError
modifier|*
modifier|*
name|error
parameter_list|)
function_decl|;
end_function_decl

begin_function_decl
specifier|static
name|void
name|gimp_tag_cache_load_text
parameter_list|(
name|GMarkupParseContext
modifier|*
name|context
parameter_list|,
specifier|const
name|gchar
modifier|*
name|text
parameter_list|,
name|gsize
name|text_len
parameter_list|,
name|gpointer
name|user_data
parameter_list|,
name|GError
modifier|*
modifier|*
name|error
parameter_list|)
function_decl|;
end_function_decl

begin_function_decl
specifier|static
name|void
name|gimp_tag_cache_load_error
parameter_list|(
name|GMarkupParseContext
modifier|*
name|context
parameter_list|,
name|GError
modifier|*
name|error
parameter_list|,
name|gpointer
name|user_data
parameter_list|)
function_decl|;
end_function_decl

begin_function_decl
specifier|static
specifier|const
name|gchar
modifier|*
name|gimp_tag_cache_attribute_name_to_value
parameter_list|(
specifier|const
name|gchar
modifier|*
modifier|*
name|attribute_names
parameter_list|,
specifier|const
name|gchar
modifier|*
modifier|*
name|attribute_values
parameter_list|,
specifier|const
name|gchar
modifier|*
name|name
parameter_list|)
function_decl|;
end_function_decl

begin_function_decl
specifier|static
name|GQuark
name|gimp_tag_cache_get_error_domain
parameter_list|(
name|void
parameter_list|)
function_decl|;
end_function_decl

begin_macro
DECL|function|G_DEFINE_TYPE (GimpTagCache,gimp_tag_cache,GIMP_TYPE_OBJECT)
name|G_DEFINE_TYPE
argument_list|(
argument|GimpTagCache
argument_list|,
argument|gimp_tag_cache
argument_list|,
argument|GIMP_TYPE_OBJECT
argument_list|)
end_macro

begin_define
DECL|macro|parent_class
define|#
directive|define
name|parent_class
value|gimp_tag_cache_parent_class
end_define

begin_function
specifier|static
name|void
name|gimp_tag_cache_class_init
parameter_list|(
name|GimpTagCacheClass
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
name|GimpObjectClass
modifier|*
name|gimp_object_class
init|=
name|GIMP_OBJECT_CLASS
argument_list|(
name|klass
argument_list|)
decl_stmt|;
name|GimpTagCacheClass
modifier|*
name|gimp_tag_cache_class
init|=
name|GIMP_TAG_CACHE_CLASS
argument_list|(
name|klass
argument_list|)
decl_stmt|;
name|object_class
operator|->
name|finalize
operator|=
name|gimp_tag_cache_finalize
expr_stmt|;
name|gimp_object_class
operator|->
name|get_memsize
operator|=
name|gimp_tag_cache_get_memsize
expr_stmt|;
name|g_type_class_add_private
argument_list|(
name|gimp_tag_cache_class
argument_list|,
sizeof|sizeof
argument_list|(
name|GimpTagCachePriv
argument_list|)
argument_list|)
expr_stmt|;
block|}
end_function

begin_function
specifier|static
name|void
DECL|function|gimp_tag_cache_init (GimpTagCache * cache)
name|gimp_tag_cache_init
parameter_list|(
name|GimpTagCache
modifier|*
name|cache
parameter_list|)
block|{
name|cache
operator|->
name|priv
operator|=
name|G_TYPE_INSTANCE_GET_PRIVATE
argument_list|(
name|cache
argument_list|,
name|GIMP_TYPE_TAG_CACHE
argument_list|,
name|GimpTagCachePriv
argument_list|)
expr_stmt|;
name|cache
operator|->
name|priv
operator|->
name|records
operator|=
name|g_array_new
argument_list|(
name|FALSE
argument_list|,
name|FALSE
argument_list|,
sizeof|sizeof
argument_list|(
name|GimpTagCacheRecord
argument_list|)
argument_list|)
expr_stmt|;
name|cache
operator|->
name|priv
operator|->
name|containers
operator|=
name|NULL
expr_stmt|;
block|}
end_function

begin_function
specifier|static
name|void
DECL|function|gimp_tag_cache_finalize (GObject * object)
name|gimp_tag_cache_finalize
parameter_list|(
name|GObject
modifier|*
name|object
parameter_list|)
block|{
name|GimpTagCache
modifier|*
name|cache
init|=
name|GIMP_TAG_CACHE
argument_list|(
name|object
argument_list|)
decl_stmt|;
name|gint
name|i
decl_stmt|;
if|if
condition|(
name|cache
operator|->
name|priv
operator|->
name|records
condition|)
block|{
for|for
control|(
name|i
operator|=
literal|0
init|;
name|i
operator|<
name|cache
operator|->
name|priv
operator|->
name|records
operator|->
name|len
condition|;
name|i
operator|++
control|)
block|{
name|GimpTagCacheRecord
modifier|*
name|rec
init|=
operator|&
name|g_array_index
argument_list|(
name|cache
operator|->
name|priv
operator|->
name|records
argument_list|,
name|GimpTagCacheRecord
argument_list|,
name|i
argument_list|)
decl_stmt|;
name|g_list_foreach
argument_list|(
name|rec
operator|->
name|tags
argument_list|,
operator|(
name|GFunc
operator|)
name|g_object_unref
argument_list|,
name|NULL
argument_list|)
expr_stmt|;
name|g_list_free
argument_list|(
name|rec
operator|->
name|tags
argument_list|)
expr_stmt|;
block|}
name|g_array_free
argument_list|(
name|cache
operator|->
name|priv
operator|->
name|records
argument_list|,
name|TRUE
argument_list|)
expr_stmt|;
name|cache
operator|->
name|priv
operator|->
name|records
operator|=
name|NULL
expr_stmt|;
block|}
if|if
condition|(
name|cache
operator|->
name|priv
operator|->
name|containers
condition|)
block|{
name|g_list_free
argument_list|(
name|cache
operator|->
name|priv
operator|->
name|containers
argument_list|)
expr_stmt|;
name|cache
operator|->
name|priv
operator|->
name|containers
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
name|gint64
DECL|function|gimp_tag_cache_get_memsize (GimpObject * object,gint64 * gui_size)
name|gimp_tag_cache_get_memsize
parameter_list|(
name|GimpObject
modifier|*
name|object
parameter_list|,
name|gint64
modifier|*
name|gui_size
parameter_list|)
block|{
name|GimpTagCache
modifier|*
name|cache
init|=
name|GIMP_TAG_CACHE
argument_list|(
name|object
argument_list|)
decl_stmt|;
name|gint64
name|memsize
init|=
literal|0
decl_stmt|;
name|memsize
operator|+=
name|gimp_g_list_get_memsize
argument_list|(
name|cache
operator|->
name|priv
operator|->
name|containers
argument_list|,
literal|0
argument_list|)
expr_stmt|;
name|memsize
operator|+=
name|cache
operator|->
name|priv
operator|->
name|records
operator|->
name|len
operator|*
sizeof|sizeof
argument_list|(
name|GimpTagCacheRecord
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
argument_list|,
name|gui_size
argument_list|)
return|;
block|}
end_function

begin_comment
comment|/**  * gimp_tag_cache_new:  *  * Return value: creates new GimpTagCache object.  **/
end_comment

begin_function
name|GimpTagCache
modifier|*
DECL|function|gimp_tag_cache_new (void)
name|gimp_tag_cache_new
parameter_list|(
name|void
parameter_list|)
block|{
return|return
name|g_object_new
argument_list|(
name|GIMP_TYPE_TAG_CACHE
argument_list|,
name|NULL
argument_list|)
return|;
block|}
end_function

begin_function
specifier|static
name|void
DECL|function|gimp_tag_cache_container_add_callback (GimpTagCache * cache,GimpTagged * tagged,GimpContainer * not_used)
name|gimp_tag_cache_container_add_callback
parameter_list|(
name|GimpTagCache
modifier|*
name|cache
parameter_list|,
name|GimpTagged
modifier|*
name|tagged
parameter_list|,
name|GimpContainer
modifier|*
name|not_used
parameter_list|)
block|{
name|gimp_tag_cache_add_object
argument_list|(
name|cache
argument_list|,
name|tagged
argument_list|)
expr_stmt|;
block|}
end_function

begin_comment
comment|/**  * gimp_tag_cache_add_container:  * @cache:      a GimpTagCache object.  * @container:  container containing GimpTagged objects.  *  * Adds container of GimpTagged objects to tag cache. Before calling this  * function tag cache must be loaded using gimp_tag_cache_load(). When tag  * cache is saved to file, tags are collected from objects in priv->containers.  **/
end_comment

begin_function
name|void
DECL|function|gimp_tag_cache_add_container (GimpTagCache * cache,GimpContainer * container)
name|gimp_tag_cache_add_container
parameter_list|(
name|GimpTagCache
modifier|*
name|cache
parameter_list|,
name|GimpContainer
modifier|*
name|container
parameter_list|)
block|{
name|g_return_if_fail
argument_list|(
name|GIMP_IS_TAG_CACHE
argument_list|(
name|cache
argument_list|)
argument_list|)
expr_stmt|;
name|g_return_if_fail
argument_list|(
name|GIMP_IS_CONTAINER
argument_list|(
name|container
argument_list|)
argument_list|)
expr_stmt|;
name|cache
operator|->
name|priv
operator|->
name|containers
operator|=
name|g_list_append
argument_list|(
name|cache
operator|->
name|priv
operator|->
name|containers
argument_list|,
name|container
argument_list|)
expr_stmt|;
name|gimp_container_foreach
argument_list|(
name|container
argument_list|,
operator|(
name|GFunc
operator|)
name|gimp_tag_cache_object_initialize
argument_list|,
name|cache
argument_list|)
expr_stmt|;
name|g_signal_connect_swapped
argument_list|(
name|container
argument_list|,
literal|"add"
argument_list|,
name|G_CALLBACK
argument_list|(
name|gimp_tag_cache_container_add_callback
argument_list|)
argument_list|,
name|cache
argument_list|)
expr_stmt|;
block|}
end_function

begin_function
specifier|static
name|void
DECL|function|gimp_tag_cache_add_object (GimpTagCache * cache,GimpTagged * tagged)
name|gimp_tag_cache_add_object
parameter_list|(
name|GimpTagCache
modifier|*
name|cache
parameter_list|,
name|GimpTagged
modifier|*
name|tagged
parameter_list|)
block|{
name|gchar
modifier|*
name|identifier
decl_stmt|;
name|GQuark
name|identifier_quark
init|=
literal|0
decl_stmt|;
name|gchar
modifier|*
name|checksum_string
decl_stmt|;
name|GQuark
name|checksum_quark
decl_stmt|;
name|GList
modifier|*
name|list
decl_stmt|;
name|gint
name|i
decl_stmt|;
name|identifier
operator|=
name|gimp_tagged_get_identifier
argument_list|(
name|tagged
argument_list|)
expr_stmt|;
name|identifier_quark
operator|=
name|g_quark_try_string
argument_list|(
name|identifier
argument_list|)
expr_stmt|;
name|g_free
argument_list|(
name|identifier
argument_list|)
expr_stmt|;
if|if
condition|(
operator|!
name|gimp_tagged_get_tags
argument_list|(
name|tagged
argument_list|)
condition|)
block|{
if|if
condition|(
name|identifier_quark
condition|)
block|{
for|for
control|(
name|i
operator|=
literal|0
init|;
name|i
operator|<
name|cache
operator|->
name|priv
operator|->
name|records
operator|->
name|len
condition|;
name|i
operator|++
control|)
block|{
name|GimpTagCacheRecord
modifier|*
name|rec
init|=
operator|&
name|g_array_index
argument_list|(
name|cache
operator|->
name|priv
operator|->
name|records
argument_list|,
name|GimpTagCacheRecord
argument_list|,
name|i
argument_list|)
decl_stmt|;
if|if
condition|(
name|rec
operator|->
name|identifier
operator|==
name|identifier_quark
condition|)
block|{
for|for
control|(
name|list
operator|=
name|rec
operator|->
name|tags
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
name|gimp_tagged_add_tag
argument_list|(
name|tagged
argument_list|,
name|GIMP_TAG
argument_list|(
name|list
operator|->
name|data
argument_list|)
argument_list|)
expr_stmt|;
block|}
name|rec
operator|->
name|referenced
operator|=
name|TRUE
expr_stmt|;
return|return;
block|}
block|}
block|}
name|checksum_string
operator|=
name|gimp_tagged_get_checksum
argument_list|(
name|tagged
argument_list|)
expr_stmt|;
name|checksum_quark
operator|=
name|g_quark_try_string
argument_list|(
name|checksum_string
argument_list|)
expr_stmt|;
name|g_free
argument_list|(
name|checksum_string
argument_list|)
expr_stmt|;
if|if
condition|(
name|checksum_quark
condition|)
block|{
for|for
control|(
name|i
operator|=
literal|0
init|;
name|i
operator|<
name|cache
operator|->
name|priv
operator|->
name|records
operator|->
name|len
condition|;
name|i
operator|++
control|)
block|{
name|GimpTagCacheRecord
modifier|*
name|rec
init|=
operator|&
name|g_array_index
argument_list|(
name|cache
operator|->
name|priv
operator|->
name|records
argument_list|,
name|GimpTagCacheRecord
argument_list|,
name|i
argument_list|)
decl_stmt|;
if|if
condition|(
name|rec
operator|->
name|checksum
operator|==
name|checksum_quark
condition|)
block|{
name|g_printerr
argument_list|(
literal|"remapping identifier: %s ==> %s\n"
argument_list|,
name|g_quark_to_string
argument_list|(
name|rec
operator|->
name|identifier
argument_list|)
argument_list|,
name|g_quark_to_string
argument_list|(
name|identifier_quark
argument_list|)
argument_list|)
expr_stmt|;
name|rec
operator|->
name|identifier
operator|=
name|identifier_quark
expr_stmt|;
for|for
control|(
name|list
operator|=
name|rec
operator|->
name|tags
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
name|gimp_tagged_add_tag
argument_list|(
name|tagged
argument_list|,
name|GIMP_TAG
argument_list|(
name|list
operator|->
name|data
argument_list|)
argument_list|)
expr_stmt|;
block|}
name|rec
operator|->
name|referenced
operator|=
name|TRUE
expr_stmt|;
return|return;
block|}
block|}
block|}
block|}
block|}
end_function

begin_function
specifier|static
name|void
DECL|function|gimp_tag_cache_object_initialize (GimpTagged * tagged,GimpTagCache * cache)
name|gimp_tag_cache_object_initialize
parameter_list|(
name|GimpTagged
modifier|*
name|tagged
parameter_list|,
name|GimpTagCache
modifier|*
name|cache
parameter_list|)
block|{
name|gimp_tag_cache_add_object
argument_list|(
name|cache
argument_list|,
name|tagged
argument_list|)
expr_stmt|;
block|}
end_function

begin_function
specifier|static
name|void
DECL|function|gimp_tag_cache_tagged_to_cache_record_foreach (GimpTagged * tagged,GList ** cache_records)
name|gimp_tag_cache_tagged_to_cache_record_foreach
parameter_list|(
name|GimpTagged
modifier|*
name|tagged
parameter_list|,
name|GList
modifier|*
modifier|*
name|cache_records
parameter_list|)
block|{
name|gchar
modifier|*
name|identifier
decl_stmt|;
name|identifier
operator|=
name|gimp_tagged_get_identifier
argument_list|(
name|tagged
argument_list|)
expr_stmt|;
if|if
condition|(
name|identifier
condition|)
block|{
name|GimpTagCacheRecord
modifier|*
name|cache_rec
init|=
name|g_new
argument_list|(
name|GimpTagCacheRecord
argument_list|,
literal|1
argument_list|)
decl_stmt|;
name|gchar
modifier|*
name|checksum
decl_stmt|;
name|checksum
operator|=
name|gimp_tagged_get_checksum
argument_list|(
name|tagged
argument_list|)
expr_stmt|;
name|cache_rec
operator|->
name|identifier
operator|=
name|g_quark_from_string
argument_list|(
name|identifier
argument_list|)
expr_stmt|;
name|cache_rec
operator|->
name|checksum
operator|=
name|g_quark_from_string
argument_list|(
name|checksum
argument_list|)
expr_stmt|;
name|cache_rec
operator|->
name|tags
operator|=
name|g_list_copy
argument_list|(
name|gimp_tagged_get_tags
argument_list|(
name|tagged
argument_list|)
argument_list|)
expr_stmt|;
name|g_free
argument_list|(
name|checksum
argument_list|)
expr_stmt|;
operator|*
name|cache_records
operator|=
name|g_list_append
argument_list|(
operator|*
name|cache_records
argument_list|,
name|cache_rec
argument_list|)
expr_stmt|;
block|}
name|g_free
argument_list|(
name|identifier
argument_list|)
expr_stmt|;
block|}
end_function

begin_comment
comment|/**  * gimp_tag_cache_save:  * @cache:      a GimpTagCache object.  *  * Saves tag cache to cache file.  **/
end_comment

begin_function
name|void
DECL|function|gimp_tag_cache_save (GimpTagCache * cache)
name|gimp_tag_cache_save
parameter_list|(
name|GimpTagCache
modifier|*
name|cache
parameter_list|)
block|{
name|GString
modifier|*
name|buf
decl_stmt|;
name|GList
modifier|*
name|saved_records
decl_stmt|;
name|GList
modifier|*
name|iterator
decl_stmt|;
name|gchar
modifier|*
name|filename
decl_stmt|;
name|GError
modifier|*
name|error
init|=
name|NULL
decl_stmt|;
name|gint
name|i
decl_stmt|;
name|g_return_if_fail
argument_list|(
name|GIMP_IS_TAG_CACHE
argument_list|(
name|cache
argument_list|)
argument_list|)
expr_stmt|;
name|saved_records
operator|=
name|NULL
expr_stmt|;
for|for
control|(
name|i
operator|=
literal|0
init|;
name|i
operator|<
name|cache
operator|->
name|priv
operator|->
name|records
operator|->
name|len
condition|;
name|i
operator|++
control|)
block|{
name|GimpTagCacheRecord
modifier|*
name|current_record
init|=
operator|&
name|g_array_index
argument_list|(
name|cache
operator|->
name|priv
operator|->
name|records
argument_list|,
name|GimpTagCacheRecord
argument_list|,
name|i
argument_list|)
decl_stmt|;
if|if
condition|(
operator|!
name|current_record
operator|->
name|referenced
operator|&&
name|current_record
operator|->
name|tags
condition|)
block|{
comment|/* keep tagged objects which have tags assigned            * but were not loaded.            */
name|GimpTagCacheRecord
modifier|*
name|record_copy
init|=
name|g_new
argument_list|(
name|GimpTagCacheRecord
argument_list|,
literal|1
argument_list|)
decl_stmt|;
name|record_copy
operator|->
name|identifier
operator|=
name|current_record
operator|->
name|identifier
expr_stmt|;
name|record_copy
operator|->
name|checksum
operator|=
name|current_record
operator|->
name|checksum
expr_stmt|;
name|record_copy
operator|->
name|tags
operator|=
name|g_list_copy
argument_list|(
name|current_record
operator|->
name|tags
argument_list|)
expr_stmt|;
name|saved_records
operator|=
name|g_list_append
argument_list|(
name|saved_records
argument_list|,
name|record_copy
argument_list|)
expr_stmt|;
block|}
block|}
for|for
control|(
name|iterator
operator|=
name|cache
operator|->
name|priv
operator|->
name|containers
init|;
name|iterator
condition|;
name|iterator
operator|=
name|g_list_next
argument_list|(
name|iterator
argument_list|)
control|)
block|{
name|gimp_container_foreach
argument_list|(
name|GIMP_CONTAINER
argument_list|(
name|iterator
operator|->
name|data
argument_list|)
argument_list|,
operator|(
name|GFunc
operator|)
name|gimp_tag_cache_tagged_to_cache_record_foreach
argument_list|,
operator|&
name|saved_records
argument_list|)
expr_stmt|;
block|}
name|buf
operator|=
name|g_string_new
argument_list|(
literal|""
argument_list|)
expr_stmt|;
name|g_string_append
argument_list|(
name|buf
argument_list|,
literal|"<?xml version='1.0' encoding='UTF-8'?>\n"
argument_list|)
expr_stmt|;
name|g_string_append
argument_list|(
name|buf
argument_list|,
literal|"<tags>\n"
argument_list|)
expr_stmt|;
for|for
control|(
name|iterator
operator|=
name|saved_records
init|;
name|iterator
condition|;
name|iterator
operator|=
name|g_list_next
argument_list|(
name|iterator
argument_list|)
control|)
block|{
name|GimpTagCacheRecord
modifier|*
name|cache_rec
init|=
name|iterator
operator|->
name|data
decl_stmt|;
name|GList
modifier|*
name|tag_iterator
decl_stmt|;
name|gchar
modifier|*
name|identifier_string
decl_stmt|;
name|gchar
modifier|*
name|tag_string
decl_stmt|;
name|identifier_string
operator|=
name|g_markup_escape_text
argument_list|(
name|g_quark_to_string
argument_list|(
name|cache_rec
operator|->
name|identifier
argument_list|)
argument_list|,
operator|-
literal|1
argument_list|)
expr_stmt|;
name|g_string_append_printf
argument_list|(
name|buf
argument_list|,
literal|"\n<resource identifier=\"%s\" checksum=\"%s\">\n"
argument_list|,
name|identifier_string
argument_list|,
name|g_quark_to_string
argument_list|(
name|cache_rec
operator|->
name|checksum
argument_list|)
argument_list|)
expr_stmt|;
name|g_free
argument_list|(
name|identifier_string
argument_list|)
expr_stmt|;
for|for
control|(
name|tag_iterator
operator|=
name|cache_rec
operator|->
name|tags
init|;
name|tag_iterator
condition|;
name|tag_iterator
operator|=
name|g_list_next
argument_list|(
name|tag_iterator
argument_list|)
control|)
block|{
name|tag_string
operator|=
name|g_markup_escape_text
argument_list|(
name|gimp_tag_get_name
argument_list|(
name|GIMP_TAG
argument_list|(
name|tag_iterator
operator|->
name|data
argument_list|)
argument_list|)
argument_list|,
operator|-
literal|1
argument_list|)
expr_stmt|;
name|g_string_append_printf
argument_list|(
name|buf
argument_list|,
literal|"<tag>%s</tag>\n"
argument_list|,
name|tag_string
argument_list|)
expr_stmt|;
name|g_free
argument_list|(
name|tag_string
argument_list|)
expr_stmt|;
block|}
name|g_string_append
argument_list|(
name|buf
argument_list|,
literal|"</resource>\n"
argument_list|)
expr_stmt|;
block|}
name|g_string_append
argument_list|(
name|buf
argument_list|,
literal|"</tags>\n"
argument_list|)
expr_stmt|;
name|filename
operator|=
name|g_build_filename
argument_list|(
name|gimp_directory
argument_list|()
argument_list|,
name|GIMP_TAG_CACHE_FILE
argument_list|,
name|NULL
argument_list|)
expr_stmt|;
if|if
condition|(
operator|!
name|g_file_set_contents
argument_list|(
name|filename
argument_list|,
name|buf
operator|->
name|str
argument_list|,
name|buf
operator|->
name|len
argument_list|,
operator|&
name|error
argument_list|)
condition|)
block|{
name|g_printerr
argument_list|(
literal|"Error while saving tag cache: %s\n"
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
name|g_free
argument_list|(
name|filename
argument_list|)
expr_stmt|;
name|g_string_free
argument_list|(
name|buf
argument_list|,
name|TRUE
argument_list|)
expr_stmt|;
for|for
control|(
name|iterator
operator|=
name|saved_records
init|;
name|iterator
condition|;
name|iterator
operator|=
name|g_list_next
argument_list|(
name|iterator
argument_list|)
control|)
block|{
name|GimpTagCacheRecord
modifier|*
name|cache_rec
init|=
name|iterator
operator|->
name|data
decl_stmt|;
name|g_list_free
argument_list|(
name|cache_rec
operator|->
name|tags
argument_list|)
expr_stmt|;
name|g_free
argument_list|(
name|cache_rec
argument_list|)
expr_stmt|;
block|}
name|g_list_free
argument_list|(
name|saved_records
argument_list|)
expr_stmt|;
block|}
end_function

begin_comment
comment|/**  * gimp_tag_cache_load:  * @cache:      a GimpTagCache object.  *  * Loads tag cache from file.  **/
end_comment

begin_function
name|void
DECL|function|gimp_tag_cache_load (GimpTagCache * cache)
name|gimp_tag_cache_load
parameter_list|(
name|GimpTagCache
modifier|*
name|cache
parameter_list|)
block|{
name|gchar
modifier|*
name|filename
decl_stmt|;
name|GError
modifier|*
name|error
init|=
name|NULL
decl_stmt|;
name|GMarkupParser
name|markup_parser
decl_stmt|;
name|GimpXmlParser
modifier|*
name|xml_parser
decl_stmt|;
name|GimpTagCacheParseData
name|parse_data
decl_stmt|;
name|g_return_if_fail
argument_list|(
name|GIMP_IS_TAG_CACHE
argument_list|(
name|cache
argument_list|)
argument_list|)
expr_stmt|;
comment|/* clear any previous priv->records */
name|cache
operator|->
name|priv
operator|->
name|records
operator|=
name|g_array_set_size
argument_list|(
name|cache
operator|->
name|priv
operator|->
name|records
argument_list|,
literal|0
argument_list|)
expr_stmt|;
name|filename
operator|=
name|g_build_filename
argument_list|(
name|gimp_directory
argument_list|()
argument_list|,
name|GIMP_TAG_CACHE_FILE
argument_list|,
name|NULL
argument_list|)
expr_stmt|;
name|parse_data
operator|.
name|records
operator|=
name|g_array_new
argument_list|(
name|FALSE
argument_list|,
name|FALSE
argument_list|,
sizeof|sizeof
argument_list|(
name|GimpTagCacheRecord
argument_list|)
argument_list|)
expr_stmt|;
name|memset
argument_list|(
operator|&
name|parse_data
operator|.
name|current_record
argument_list|,
literal|0
argument_list|,
sizeof|sizeof
argument_list|(
name|GimpTagCacheRecord
argument_list|)
argument_list|)
expr_stmt|;
name|markup_parser
operator|.
name|start_element
operator|=
name|gimp_tag_cache_load_start_element
expr_stmt|;
name|markup_parser
operator|.
name|end_element
operator|=
name|gimp_tag_cache_load_end_element
expr_stmt|;
name|markup_parser
operator|.
name|text
operator|=
name|gimp_tag_cache_load_text
expr_stmt|;
name|markup_parser
operator|.
name|passthrough
operator|=
name|NULL
expr_stmt|;
name|markup_parser
operator|.
name|error
operator|=
name|gimp_tag_cache_load_error
expr_stmt|;
name|xml_parser
operator|=
name|gimp_xml_parser_new
argument_list|(
operator|&
name|markup_parser
argument_list|,
operator|&
name|parse_data
argument_list|)
expr_stmt|;
if|if
condition|(
operator|!
name|gimp_xml_parser_parse_file
argument_list|(
name|xml_parser
argument_list|,
name|filename
argument_list|,
operator|&
name|error
argument_list|)
condition|)
block|{
name|g_printerr
argument_list|(
literal|"Failed to parse tag cache.\n"
argument_list|)
expr_stmt|;
block|}
else|else
block|{
name|cache
operator|->
name|priv
operator|->
name|records
operator|=
name|g_array_append_vals
argument_list|(
name|cache
operator|->
name|priv
operator|->
name|records
argument_list|,
name|parse_data
operator|.
name|records
operator|->
name|data
argument_list|,
name|parse_data
operator|.
name|records
operator|->
name|len
argument_list|)
expr_stmt|;
block|}
name|g_free
argument_list|(
name|filename
argument_list|)
expr_stmt|;
name|gimp_xml_parser_free
argument_list|(
name|xml_parser
argument_list|)
expr_stmt|;
name|g_array_free
argument_list|(
name|parse_data
operator|.
name|records
argument_list|,
name|TRUE
argument_list|)
expr_stmt|;
block|}
end_function

begin_function
specifier|static
name|void
DECL|function|gimp_tag_cache_load_start_element (GMarkupParseContext * context,const gchar * element_name,const gchar ** attribute_names,const gchar ** attribute_values,gpointer user_data,GError ** error)
name|gimp_tag_cache_load_start_element
parameter_list|(
name|GMarkupParseContext
modifier|*
name|context
parameter_list|,
specifier|const
name|gchar
modifier|*
name|element_name
parameter_list|,
specifier|const
name|gchar
modifier|*
modifier|*
name|attribute_names
parameter_list|,
specifier|const
name|gchar
modifier|*
modifier|*
name|attribute_values
parameter_list|,
name|gpointer
name|user_data
parameter_list|,
name|GError
modifier|*
modifier|*
name|error
parameter_list|)
block|{
name|GimpTagCacheParseData
modifier|*
name|parse_data
init|=
name|user_data
decl_stmt|;
if|if
condition|(
operator|!
name|strcmp
argument_list|(
name|element_name
argument_list|,
literal|"resource"
argument_list|)
condition|)
block|{
specifier|const
name|gchar
modifier|*
name|identifier
decl_stmt|;
specifier|const
name|gchar
modifier|*
name|checksum
decl_stmt|;
name|identifier
operator|=
name|gimp_tag_cache_attribute_name_to_value
argument_list|(
name|attribute_names
argument_list|,
name|attribute_values
argument_list|,
literal|"identifier"
argument_list|)
expr_stmt|;
name|checksum
operator|=
name|gimp_tag_cache_attribute_name_to_value
argument_list|(
name|attribute_names
argument_list|,
name|attribute_values
argument_list|,
literal|"checksum"
argument_list|)
expr_stmt|;
if|if
condition|(
operator|!
name|identifier
condition|)
block|{
name|g_set_error
argument_list|(
name|error
argument_list|,
name|gimp_tag_cache_get_error_domain
argument_list|()
argument_list|,
literal|1001
argument_list|,
literal|"Resource tag does not contain required attribute identifier."
argument_list|)
expr_stmt|;
return|return;
block|}
name|memset
argument_list|(
operator|&
name|parse_data
operator|->
name|current_record
argument_list|,
literal|0
argument_list|,
sizeof|sizeof
argument_list|(
name|GimpTagCacheRecord
argument_list|)
argument_list|)
expr_stmt|;
name|parse_data
operator|->
name|current_record
operator|.
name|identifier
operator|=
name|g_quark_from_string
argument_list|(
name|identifier
argument_list|)
expr_stmt|;
name|parse_data
operator|->
name|current_record
operator|.
name|checksum
operator|=
name|g_quark_from_string
argument_list|(
name|checksum
argument_list|)
expr_stmt|;
block|}
block|}
end_function

begin_function
specifier|static
name|void
DECL|function|gimp_tag_cache_load_end_element (GMarkupParseContext * context,const gchar * element_name,gpointer user_data,GError ** error)
name|gimp_tag_cache_load_end_element
parameter_list|(
name|GMarkupParseContext
modifier|*
name|context
parameter_list|,
specifier|const
name|gchar
modifier|*
name|element_name
parameter_list|,
name|gpointer
name|user_data
parameter_list|,
name|GError
modifier|*
modifier|*
name|error
parameter_list|)
block|{
name|GimpTagCacheParseData
modifier|*
name|parse_data
init|=
name|user_data
decl_stmt|;
if|if
condition|(
name|strcmp
argument_list|(
name|element_name
argument_list|,
literal|"resource"
argument_list|)
operator|==
literal|0
condition|)
block|{
name|parse_data
operator|->
name|records
operator|=
name|g_array_append_val
argument_list|(
name|parse_data
operator|->
name|records
argument_list|,
name|parse_data
operator|->
name|current_record
argument_list|)
expr_stmt|;
name|memset
argument_list|(
operator|&
name|parse_data
operator|->
name|current_record
argument_list|,
literal|0
argument_list|,
sizeof|sizeof
argument_list|(
name|GimpTagCacheRecord
argument_list|)
argument_list|)
expr_stmt|;
block|}
block|}
end_function

begin_function
specifier|static
name|void
DECL|function|gimp_tag_cache_load_text (GMarkupParseContext * context,const gchar * text,gsize text_len,gpointer user_data,GError ** error)
name|gimp_tag_cache_load_text
parameter_list|(
name|GMarkupParseContext
modifier|*
name|context
parameter_list|,
specifier|const
name|gchar
modifier|*
name|text
parameter_list|,
name|gsize
name|text_len
parameter_list|,
name|gpointer
name|user_data
parameter_list|,
name|GError
modifier|*
modifier|*
name|error
parameter_list|)
block|{
name|GimpTagCacheParseData
modifier|*
name|parse_data
init|=
name|user_data
decl_stmt|;
specifier|const
name|gchar
modifier|*
name|current_element
decl_stmt|;
name|gchar
name|buffer
index|[
literal|2048
index|]
decl_stmt|;
name|GimpTag
modifier|*
name|tag
decl_stmt|;
name|current_element
operator|=
name|g_markup_parse_context_get_element
argument_list|(
name|context
argument_list|)
expr_stmt|;
if|if
condition|(
name|current_element
operator|&&
name|strcmp
argument_list|(
name|current_element
argument_list|,
literal|"tag"
argument_list|)
operator|==
literal|0
condition|)
block|{
if|if
condition|(
name|text_len
operator|>=
sizeof|sizeof
argument_list|(
name|buffer
argument_list|)
condition|)
block|{
name|g_set_error
argument_list|(
name|error
argument_list|,
name|gimp_tag_cache_get_error_domain
argument_list|()
argument_list|,
literal|1002
argument_list|,
literal|"Tag value is too long."
argument_list|)
expr_stmt|;
return|return;
block|}
name|memcpy
argument_list|(
name|buffer
argument_list|,
name|text
argument_list|,
name|text_len
argument_list|)
expr_stmt|;
name|buffer
index|[
name|text_len
index|]
operator|=
literal|'\0'
expr_stmt|;
name|tag
operator|=
name|gimp_tag_new
argument_list|(
name|buffer
argument_list|)
expr_stmt|;
if|if
condition|(
name|tag
condition|)
block|{
name|parse_data
operator|->
name|current_record
operator|.
name|tags
operator|=
name|g_list_append
argument_list|(
name|parse_data
operator|->
name|current_record
operator|.
name|tags
argument_list|,
name|tag
argument_list|)
expr_stmt|;
block|}
else|else
block|{
name|g_warning
argument_list|(
literal|"dropping invalid tag '%s' from '%s'\n"
argument_list|,
name|buffer
argument_list|,
name|g_quark_to_string
argument_list|(
name|parse_data
operator|->
name|current_record
operator|.
name|identifier
argument_list|)
argument_list|)
expr_stmt|;
block|}
block|}
block|}
end_function

begin_function
specifier|static
name|void
DECL|function|gimp_tag_cache_load_error (GMarkupParseContext * context,GError * error,gpointer user_data)
name|gimp_tag_cache_load_error
parameter_list|(
name|GMarkupParseContext
modifier|*
name|context
parameter_list|,
name|GError
modifier|*
name|error
parameter_list|,
name|gpointer
name|user_data
parameter_list|)
block|{
name|printf
argument_list|(
literal|"Tag cache parse error: %s\n"
argument_list|,
name|error
operator|->
name|message
argument_list|)
expr_stmt|;
block|}
end_function

begin_function
specifier|static
specifier|const
name|gchar
modifier|*
DECL|function|gimp_tag_cache_attribute_name_to_value (const gchar ** attribute_names,const gchar ** attribute_values,const gchar * name)
name|gimp_tag_cache_attribute_name_to_value
parameter_list|(
specifier|const
name|gchar
modifier|*
modifier|*
name|attribute_names
parameter_list|,
specifier|const
name|gchar
modifier|*
modifier|*
name|attribute_values
parameter_list|,
specifier|const
name|gchar
modifier|*
name|name
parameter_list|)
block|{
while|while
condition|(
operator|*
name|attribute_names
condition|)
block|{
if|if
condition|(
operator|!
name|strcmp
argument_list|(
operator|*
name|attribute_names
argument_list|,
name|name
argument_list|)
condition|)
block|{
return|return
operator|*
name|attribute_values
return|;
block|}
name|attribute_names
operator|++
expr_stmt|;
name|attribute_values
operator|++
expr_stmt|;
block|}
return|return
name|NULL
return|;
block|}
end_function

begin_function
specifier|static
name|GQuark
DECL|function|gimp_tag_cache_get_error_domain (void)
name|gimp_tag_cache_get_error_domain
parameter_list|(
name|void
parameter_list|)
block|{
return|return
name|g_quark_from_static_string
argument_list|(
literal|"gimp-tag-cache-error-quark"
argument_list|)
return|;
block|}
end_function

end_unit

