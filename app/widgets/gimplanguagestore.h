begin_unit|revision:0.9.5;language:C;cregit-version:0.0.1
begin_comment
comment|/* GIMP - The GNU Image Manipulation Program  * Copyright (C) 1995 Spencer Kimball and Peter Mattis  *  * gimplanguagestore.h  * Copyright (C) 2008  Sven Neumann<sven@gimp.org>  *  * This program is free software; you can redistribute it and/or modify  * it under the terms of the GNU General Public License as published by  * the Free Software Foundation; either version 2 of the License, or  * (at your option) any later version.  *  * This program is distributed in the hope that it will be useful,  * but WITHOUT ANY WARRANTY; without even the implied warranty of  * MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the  * GNU General Public License for more details.  *  * You should have received a copy of the GNU General Public License  * along with this program; if not, write to the Free Software  * Foundation, Inc., 59 Temple Place - Suite 330, Boston, MA 02111-1307, USA.  */
end_comment

begin_ifndef
ifndef|#
directive|ifndef
name|__GIMP_LANGUAGE_STORE_H__
end_ifndef

begin_define
DECL|macro|__GIMP_LANGUAGE_STORE_H__
define|#
directive|define
name|__GIMP_LANGUAGE_STORE_H__
end_define

begin_enum
enum|enum
DECL|enum|__anon2a0de7840103
block|{
DECL|enumerator|GIMP_LANGUAGE_STORE_LANGUAGE
name|GIMP_LANGUAGE_STORE_LANGUAGE
block|,
DECL|enumerator|GIMP_LANGUAGE_STORE_ISO_639_1
name|GIMP_LANGUAGE_STORE_ISO_639_1
block|}
enum|;
end_enum

begin_define
DECL|macro|GIMP_TYPE_LANGUAGE_STORE
define|#
directive|define
name|GIMP_TYPE_LANGUAGE_STORE
value|(gimp_language_store_get_type ())
end_define

begin_define
DECL|macro|GIMP_LANGUAGE_STORE (obj)
define|#
directive|define
name|GIMP_LANGUAGE_STORE
parameter_list|(
name|obj
parameter_list|)
value|(G_TYPE_CHECK_INSTANCE_CAST ((obj), GIMP_TYPE_LANGUAGE_STORE, GimpLanguageStore))
end_define

begin_define
DECL|macro|GIMP_LANGUAGE_STORE_CLASS (klass)
define|#
directive|define
name|GIMP_LANGUAGE_STORE_CLASS
parameter_list|(
name|klass
parameter_list|)
value|(G_TYPE_CHECK_CLASS_CAST ((klass), GIMP_TYPE_LANGUAGE_STORE, GimpLanguageStoreClass))
end_define

begin_define
DECL|macro|GIMP_IS_LANGUAGE_STORE (obj)
define|#
directive|define
name|GIMP_IS_LANGUAGE_STORE
parameter_list|(
name|obj
parameter_list|)
value|(G_TYPE_CHECK_INSTANCE_TYPE ((obj), GIMP_TYPE_LANGUAGE_STORE))
end_define

begin_define
DECL|macro|GIMP_IS_LANGUAGE_STORE_CLASS (klass)
define|#
directive|define
name|GIMP_IS_LANGUAGE_STORE_CLASS
parameter_list|(
name|klass
parameter_list|)
value|(G_TYPE_CHECK_CLASS_TYPE ((klass), GIMP_TYPE_LANGUAGE_STORE))
end_define

begin_define
DECL|macro|GIMP_LANGUAGE_STORE_GET_CLASS (obj)
define|#
directive|define
name|GIMP_LANGUAGE_STORE_GET_CLASS
parameter_list|(
name|obj
parameter_list|)
value|(G_TYPE_INSTANCE_GET_CLASS ((obj), GIMP_TYPE_LANGUAGE_STORE, GimpLanguageStoreClass))
end_define

begin_typedef
DECL|typedef|GimpLanguageStoreClass
typedef|typedef
name|struct
name|_GimpLanguageStoreClass
name|GimpLanguageStoreClass
typedef|;
end_typedef

begin_struct
DECL|struct|_GimpLanguageStoreClass
struct|struct
name|_GimpLanguageStoreClass
block|{
DECL|member|parent_class
name|GtkListStoreClass
name|parent_class
decl_stmt|;
block|}
struct|;
end_struct

begin_struct
DECL|struct|_GimpLanguageStore
struct|struct
name|_GimpLanguageStore
block|{
DECL|member|parent_instance
name|GtkListStore
name|parent_instance
decl_stmt|;
DECL|member|translations
name|gboolean
name|translations
decl_stmt|;
block|}
struct|;
end_struct

begin_decl_stmt
name|GType
name|gimp_language_store_get_type
argument_list|(
name|void
argument_list|)
name|G_GNUC_CONST
decl_stmt|;
end_decl_stmt

begin_function_decl
name|GtkListStore
modifier|*
name|gimp_language_store_new
parameter_list|(
name|gboolean
name|translations
parameter_list|)
function_decl|;
end_function_decl

begin_endif
endif|#
directive|endif
end_endif

begin_comment
comment|/* __GIMP_LANGUAGE_STORE_H__ */
end_comment

end_unit

