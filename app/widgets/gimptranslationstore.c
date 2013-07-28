begin_unit|revision:0.9.5;language:C;cregit-version:0.0.1
begin_comment
comment|/* GIMP - The GNU Image Manipulation Program  * Copyright (C) 1995 Spencer Kimball and Peter Mattis  *  * gimptranslationstore.c  * Copyright (C) 2008, 2009  Sven Neumann<sven@gimp.org>  *  * This program is free software: you can redistribute it and/or modify  * it under the terms of the GNU General Public License as published by  * the Free Software Foundation; either version 3 of the License, or  * (at your option) any later version.  *  * This program is distributed in the hope that it will be useful,  * but WITHOUT ANY WARRANTY; without even the implied warranty of  * MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the  * GNU General Public License for more details.  *  * You should have received a copy of the GNU General Public License  * along with this program.  If not, see<http://www.gnu.org/licenses/>.  */
end_comment

begin_include
include|#
directive|include
file|<locale.h>
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
file|"gimplanguagestore-parser.h"
end_include

begin_include
include|#
directive|include
file|"gimptranslationstore.h"
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
block|}
struct|;
end_struct

begin_function_decl
specifier|static
name|void
name|gimp_translation_store_constructed
parameter_list|(
name|GObject
modifier|*
name|object
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
name|object_class
operator|->
name|constructed
operator|=
name|gimp_translation_store_constructed
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
block|{ }
end_function

begin_function
specifier|static
name|void
DECL|function|gimp_translation_store_constructed (GObject * object)
name|gimp_translation_store_constructed
parameter_list|(
name|GObject
modifier|*
name|object
parameter_list|)
block|{
name|GHashTable
modifier|*
name|lang_list
decl_stmt|;
name|GHashTableIter
name|lang_iter
decl_stmt|;
name|gpointer
name|code
decl_stmt|;
name|gpointer
name|name
decl_stmt|;
name|lang_list
operator|=
name|gimp_language_store_parser_get_languages
argument_list|(
name|TRUE
argument_list|)
expr_stmt|;
name|g_return_if_fail
argument_list|(
name|lang_list
operator|!=
name|NULL
argument_list|)
expr_stmt|;
name|g_hash_table_iter_init
argument_list|(
operator|&
name|lang_iter
argument_list|,
name|lang_list
argument_list|)
expr_stmt|;
while|while
condition|(
name|g_hash_table_iter_next
argument_list|(
operator|&
name|lang_iter
argument_list|,
operator|&
name|code
argument_list|,
operator|&
name|name
argument_list|)
condition|)
name|GIMP_LANGUAGE_STORE_GET_CLASS
argument_list|(
name|object
argument_list|)
operator|->
name|add
argument_list|(
name|GIMP_LANGUAGE_STORE
argument_list|(
name|object
argument_list|)
argument_list|,
name|name
argument_list|,
name|code
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

