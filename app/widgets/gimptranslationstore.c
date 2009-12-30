begin_unit|revision:0.9.5;language:C;cregit-version:0.0.1
begin_comment
comment|/* GIMP - The GNU Image Manipulation Program  * Copyright (C) 1995 Spencer Kimball and Peter Mattis  *  * gimptranslationstore.c  * Copyright (C) 2008, 2009  Sven Neumann<sven@gimp.org>  *  * This program is free software: you can redistribute it and/or modify  * it under the terms of the GNU General Public License as published by  * the Free Software Foundation; either version 3 of the License, or  * (at your option) any later version.  *  * This program is distributed in the hope that it will be useful,  * but WITHOUT ANY WARRANTY; without even the implied warranty of  * MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the  * GNU General Public License for more details.  *  * You should have received a copy of the GNU General Public License  * along with this program.  If not, see<http://www.gnu.org/licenses/>.  */
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
file|"libgimpbase/gimpbase.h"
end_include

begin_include
include|#
directive|include
file|"widgets-types.h"
end_include

begin_include
include|#
directive|include
file|"gimptranslationstore.h"
end_include

begin_include
include|#
directive|include
file|"gimp-intl.h"
end_include

begin_struct
DECL|struct|_GimpTranslationStoreClass
struct|struct
name|_GimpTranslationStoreClass
block|{
DECL|member|parent_class
name|GimpLanguageStoreClass
name|parent_class
decl_stmt|;
block|}
struct|;
end_struct

begin_struct
DECL|struct|_GimpTranslationStore
struct|struct
name|_GimpTranslationStore
block|{
DECL|member|parent_instance
name|GimpLanguageStore
name|parent_instance
decl_stmt|;
DECL|member|map
name|GHashTable
modifier|*
name|map
decl_stmt|;
block|}
struct|;
end_struct

begin_function_decl
specifier|static
name|GObject
modifier|*
name|gimp_translation_store_constructor
parameter_list|(
name|GType
name|type
parameter_list|,
name|guint
name|n_params
parameter_list|,
name|GObjectConstructParam
modifier|*
name|params
parameter_list|)
function_decl|;
end_function_decl

begin_function_decl
specifier|static
name|void
name|gimp_translation_store_add
parameter_list|(
name|GimpLanguageStore
modifier|*
name|store
parameter_list|,
specifier|const
name|gchar
modifier|*
name|lang
parameter_list|,
specifier|const
name|gchar
modifier|*
name|code
parameter_list|)
function_decl|;
end_function_decl

begin_function_decl
specifier|static
name|void
name|gimp_translation_store_populate
parameter_list|(
name|GimpTranslationStore
modifier|*
name|store
parameter_list|)
function_decl|;
end_function_decl

begin_macro
DECL|function|G_DEFINE_TYPE (GimpTranslationStore,gimp_translation_store,GIMP_TYPE_LANGUAGE_STORE)
name|G_DEFINE_TYPE
argument_list|(
argument|GimpTranslationStore
argument_list|,
argument|gimp_translation_store
argument_list|,
argument|GIMP_TYPE_LANGUAGE_STORE
argument_list|)
end_macro

begin_define
DECL|macro|parent_class
define|#
directive|define
name|parent_class
value|gimp_translation_store_parent_class
end_define

begin_function
specifier|static
name|void
name|gimp_translation_store_class_init
parameter_list|(
name|GimpTranslationStoreClass
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
name|GimpLanguageStoreClass
modifier|*
name|store_class
init|=
name|GIMP_LANGUAGE_STORE_CLASS
argument_list|(
name|klass
argument_list|)
decl_stmt|;
name|object_class
operator|->
name|constructor
operator|=
name|gimp_translation_store_constructor
expr_stmt|;
name|store_class
operator|->
name|add
operator|=
name|gimp_translation_store_add
expr_stmt|;
block|}
end_function

begin_function
specifier|static
name|void
DECL|function|gimp_translation_store_init (GimpTranslationStore * store)
name|gimp_translation_store_init
parameter_list|(
name|GimpTranslationStore
modifier|*
name|store
parameter_list|)
block|{
name|store
operator|->
name|map
operator|=
name|g_hash_table_new_full
argument_list|(
name|g_str_hash
argument_list|,
name|g_str_equal
argument_list|,
operator|(
name|GDestroyNotify
operator|)
name|g_free
argument_list|,
operator|(
name|GDestroyNotify
operator|)
name|g_free
argument_list|)
expr_stmt|;
block|}
end_function

begin_function
specifier|static
name|GObject
modifier|*
DECL|function|gimp_translation_store_constructor (GType type,guint n_params,GObjectConstructParam * params)
name|gimp_translation_store_constructor
parameter_list|(
name|GType
name|type
parameter_list|,
name|guint
name|n_params
parameter_list|,
name|GObjectConstructParam
modifier|*
name|params
parameter_list|)
block|{
name|GimpTranslationStore
modifier|*
name|store
decl_stmt|;
name|GObject
modifier|*
name|object
decl_stmt|;
name|gchar
modifier|*
name|label
decl_stmt|;
name|object
operator|=
name|G_OBJECT_CLASS
argument_list|(
name|parent_class
argument_list|)
operator|->
name|constructor
argument_list|(
name|type
argument_list|,
name|n_params
argument_list|,
name|params
argument_list|)
expr_stmt|;
name|store
operator|=
name|GIMP_TRANSLATION_STORE
argument_list|(
name|object
argument_list|)
expr_stmt|;
name|gimp_translation_store_populate
argument_list|(
name|store
argument_list|)
expr_stmt|;
comment|/*  we don't need the map any longer  */
name|g_hash_table_unref
argument_list|(
name|store
operator|->
name|map
argument_list|)
expr_stmt|;
name|store
operator|->
name|map
operator|=
name|NULL
expr_stmt|;
comment|/*  add special entries for system locale and for "C"  */
name|GIMP_LANGUAGE_STORE_CLASS
argument_list|(
name|parent_class
argument_list|)
operator|->
name|add
argument_list|(
name|GIMP_LANGUAGE_STORE
argument_list|(
name|store
argument_list|)
argument_list|,
name|_
argument_list|(
literal|"System Language"
argument_list|)
argument_list|,
name|NULL
argument_list|)
expr_stmt|;
name|label
operator|=
name|g_strdup_printf
argument_list|(
literal|"%s [%s]"
argument_list|,
name|_
argument_list|(
literal|"English"
argument_list|)
argument_list|,
literal|"en_US"
argument_list|)
expr_stmt|;
name|GIMP_LANGUAGE_STORE_CLASS
argument_list|(
name|parent_class
argument_list|)
operator|->
name|add
argument_list|(
name|GIMP_LANGUAGE_STORE
argument_list|(
name|store
argument_list|)
argument_list|,
name|label
argument_list|,
literal|"en_US"
argument_list|)
expr_stmt|;
name|g_free
argument_list|(
name|label
argument_list|)
expr_stmt|;
return|return
name|object
return|;
block|}
end_function

begin_function
specifier|static
specifier|const
name|gchar
modifier|*
DECL|function|gimp_translation_store_map (GimpTranslationStore * store,const gchar * locale)
name|gimp_translation_store_map
parameter_list|(
name|GimpTranslationStore
modifier|*
name|store
parameter_list|,
specifier|const
name|gchar
modifier|*
name|locale
parameter_list|)
block|{
specifier|const
name|gchar
modifier|*
name|lang
decl_stmt|;
comment|/*  A locale directory name is typically of the form language[_territory]  */
name|lang
operator|=
name|g_hash_table_lookup
argument_list|(
name|store
operator|->
name|map
argument_list|,
name|locale
argument_list|)
expr_stmt|;
if|if
condition|(
operator|!
name|lang
condition|)
block|{
comment|/*  strip off the territory suffix  */
specifier|const
name|gchar
modifier|*
name|delimiter
init|=
name|strchr
argument_list|(
name|locale
argument_list|,
literal|'_'
argument_list|)
decl_stmt|;
if|if
condition|(
name|delimiter
condition|)
block|{
name|gchar
modifier|*
name|copy
decl_stmt|;
name|copy
operator|=
name|g_strndup
argument_list|(
name|locale
argument_list|,
name|delimiter
operator|-
name|locale
argument_list|)
expr_stmt|;
name|lang
operator|=
name|g_hash_table_lookup
argument_list|(
name|store
operator|->
name|map
argument_list|,
name|copy
argument_list|)
expr_stmt|;
name|g_free
argument_list|(
name|copy
argument_list|)
expr_stmt|;
block|}
block|}
return|return
name|lang
return|;
block|}
end_function

begin_function
specifier|static
name|void
DECL|function|gimp_translation_store_populate (GimpTranslationStore * store)
name|gimp_translation_store_populate
parameter_list|(
name|GimpTranslationStore
modifier|*
name|store
parameter_list|)
block|{
comment|/*  FIXME: this should better be done asynchronously  */
name|GDir
modifier|*
name|dir
init|=
name|g_dir_open
argument_list|(
name|gimp_locale_directory
argument_list|()
argument_list|,
literal|0
argument_list|,
name|NULL
argument_list|)
decl_stmt|;
specifier|const
name|gchar
modifier|*
name|dirname
decl_stmt|;
if|if
condition|(
operator|!
name|dir
condition|)
return|return;
while|while
condition|(
operator|(
name|dirname
operator|=
name|g_dir_read_name
argument_list|(
name|dir
argument_list|)
operator|)
operator|!=
name|NULL
condition|)
block|{
name|gchar
modifier|*
name|filename
init|=
name|g_build_filename
argument_list|(
name|gimp_locale_directory
argument_list|()
argument_list|,
name|dirname
argument_list|,
literal|"LC_MESSAGES"
argument_list|,
name|GETTEXT_PACKAGE
literal|".mo"
argument_list|,
name|NULL
argument_list|)
decl_stmt|;
if|if
condition|(
name|g_file_test
argument_list|(
name|filename
argument_list|,
name|G_FILE_TEST_EXISTS
argument_list|)
condition|)
block|{
specifier|const
name|gchar
modifier|*
name|lang
init|=
name|gimp_translation_store_map
argument_list|(
name|store
argument_list|,
name|dirname
argument_list|)
decl_stmt|;
if|if
condition|(
name|lang
condition|)
block|{
name|GimpLanguageStore
modifier|*
name|language_store
init|=
name|GIMP_LANGUAGE_STORE
argument_list|(
name|store
argument_list|)
decl_stmt|;
name|gchar
modifier|*
name|label
decl_stmt|;
name|label
operator|=
name|g_strdup_printf
argument_list|(
literal|"%s [%s]"
argument_list|,
name|lang
argument_list|,
name|dirname
argument_list|)
expr_stmt|;
name|GIMP_LANGUAGE_STORE_CLASS
argument_list|(
name|parent_class
argument_list|)
operator|->
name|add
argument_list|(
name|language_store
argument_list|,
name|label
argument_list|,
name|dirname
argument_list|)
expr_stmt|;
name|g_free
argument_list|(
name|label
argument_list|)
expr_stmt|;
block|}
block|}
name|g_free
argument_list|(
name|filename
argument_list|)
expr_stmt|;
block|}
name|g_dir_close
argument_list|(
name|dir
argument_list|)
expr_stmt|;
block|}
end_function

begin_function
specifier|static
name|void
DECL|function|gimp_translation_store_add (GimpLanguageStore * store,const gchar * lang,const gchar * code)
name|gimp_translation_store_add
parameter_list|(
name|GimpLanguageStore
modifier|*
name|store
parameter_list|,
specifier|const
name|gchar
modifier|*
name|lang
parameter_list|,
specifier|const
name|gchar
modifier|*
name|code
parameter_list|)
block|{
name|g_hash_table_replace
argument_list|(
name|GIMP_TRANSLATION_STORE
argument_list|(
name|store
argument_list|)
operator|->
name|map
argument_list|,
name|g_strdup
argument_list|(
name|code
argument_list|)
argument_list|,
name|g_strdup
argument_list|(
name|lang
argument_list|)
argument_list|)
expr_stmt|;
block|}
end_function

begin_function
name|GtkListStore
modifier|*
DECL|function|gimp_translation_store_new (void)
name|gimp_translation_store_new
parameter_list|(
name|void
parameter_list|)
block|{
return|return
name|g_object_new
argument_list|(
name|GIMP_TYPE_TRANSLATION_STORE
argument_list|,
name|NULL
argument_list|)
return|;
block|}
end_function

end_unit

