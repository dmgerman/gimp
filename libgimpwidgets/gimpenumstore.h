begin_unit|revision:0.9.5;language:C;cregit-version:0.0.1
begin_comment
comment|/* The GIMP -- an image manipulation program  * Copyright (C) 1995 Spencer Kimball and Peter Mattis  *  * gimpenumstore.h  * Copyright (C) 2004  Sven Neumann<sven@gimp.org>  *  * This program is free software; you can redistribute it and/or modify  * it under the terms of the GNU General Public License as published by  * the Free Software Foundation; either version 2 of the License, or  * (at your option) any later version.  *  * This program is distributed in the hope that it will be useful,  * but WITHOUT ANY WARRANTY; without even the implied warranty of  * MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the  * GNU General Public License for more details.  *  * You should have received a copy of the GNU General Public License  * along with this program; if not, write to the Free Software  * Foundation, Inc., 59 Temple Place - Suite 330, Boston, MA 02111-1307, USA.  */
end_comment

begin_ifndef
ifndef|#
directive|ifndef
name|__GIMP_ENUM_STORE_H__
end_ifndef

begin_define
DECL|macro|__GIMP_ENUM_STORE_H__
define|#
directive|define
name|__GIMP_ENUM_STORE_H__
end_define

begin_include
include|#
directive|include
file|<gtk/gtkliststore.h>
end_include

begin_typedef
typedef|typedef
enum|enum
DECL|enum|__anon2c0019980103
block|{
DECL|enumerator|GIMP_ENUM_STORE_VALUE
name|GIMP_ENUM_STORE_VALUE
block|,
DECL|enumerator|GIMP_ENUM_STORE_LABEL
name|GIMP_ENUM_STORE_LABEL
block|,
DECL|enumerator|GIMP_ENUM_STORE_ICON
name|GIMP_ENUM_STORE_ICON
block|,
DECL|enumerator|GIMP_ENUM_STORE_USER_DATA
name|GIMP_ENUM_STORE_USER_DATA
block|,
DECL|enumerator|GIMP_ENUM_STORE_NUM_COLUMNS
name|GIMP_ENUM_STORE_NUM_COLUMNS
DECL|typedef|GimpEnumStoreColumns
block|}
name|GimpEnumStoreColumns
typedef|;
end_typedef

begin_define
DECL|macro|GIMP_TYPE_ENUM_STORE
define|#
directive|define
name|GIMP_TYPE_ENUM_STORE
value|(gimp_enum_store_get_type ())
end_define

begin_define
DECL|macro|GIMP_ENUM_STORE (obj)
define|#
directive|define
name|GIMP_ENUM_STORE
parameter_list|(
name|obj
parameter_list|)
value|(G_TYPE_CHECK_INSTANCE_CAST ((obj), GIMP_TYPE_ENUM_STORE, GimpEnumStore))
end_define

begin_define
DECL|macro|GIMP_ENUM_STORE_CLASS (klass)
define|#
directive|define
name|GIMP_ENUM_STORE_CLASS
parameter_list|(
name|klass
parameter_list|)
value|(G_TYPE_CHECK_CLASS_CAST ((klass), GIMP_TYPE_ENUM_STORE, GimpEnumStoreClass))
end_define

begin_define
DECL|macro|GIMP_IS_ENUM_STORE (obj)
define|#
directive|define
name|GIMP_IS_ENUM_STORE
parameter_list|(
name|obj
parameter_list|)
value|(G_TYPE_CHECK_INSTANCE_TYPE ((obj), GIMP_TYPE_ENUM_STORE))
end_define

begin_define
DECL|macro|GIMP_IS_ENUM_STORE_CLASS (klass)
define|#
directive|define
name|GIMP_IS_ENUM_STORE_CLASS
parameter_list|(
name|klass
parameter_list|)
value|(G_TYPE_CHECK_CLASS_TYPE ((klass), GIMP_TYPE_ENUM_STORE))
end_define

begin_define
DECL|macro|GIMP_ENUM_STORE_GET_CLASS (obj)
define|#
directive|define
name|GIMP_ENUM_STORE_GET_CLASS
parameter_list|(
name|obj
parameter_list|)
value|(G_TYPE_INSTANCE_GET_CLASS ((obj), GIMP_TYPE_ENUM_STORE, GimpEnumStoreClass))
end_define

begin_typedef
DECL|typedef|GimpEnumStoreClass
typedef|typedef
name|struct
name|_GimpEnumStoreClass
name|GimpEnumStoreClass
typedef|;
end_typedef

begin_struct
DECL|struct|_GimpEnumStoreClass
struct|struct
name|_GimpEnumStoreClass
block|{
DECL|member|parent_instance
name|GtkListStoreClass
name|parent_instance
decl_stmt|;
block|}
struct|;
end_struct

begin_struct
DECL|struct|_GimpEnumStore
struct|struct
name|_GimpEnumStore
block|{
DECL|member|parent_instance
name|GtkListStore
name|parent_instance
decl_stmt|;
DECL|member|enum_class
name|GEnumClass
modifier|*
name|enum_class
decl_stmt|;
block|}
struct|;
end_struct

begin_decl_stmt
name|GType
name|gimp_enum_store_get_type
argument_list|(
name|void
argument_list|)
name|G_GNUC_CONST
decl_stmt|;
end_decl_stmt

begin_function_decl
name|GtkListStore
modifier|*
name|gimp_enum_store_new
parameter_list|(
name|GType
name|enum_type
parameter_list|)
function_decl|;
end_function_decl

begin_empty_stmt
empty_stmt|;
end_empty_stmt

begin_function_decl
name|GtkListStore
modifier|*
name|gimp_enum_store_new_with_range
parameter_list|(
name|GType
name|enum_type
parameter_list|,
name|gint
name|minimum
parameter_list|,
name|gint
name|maximum
parameter_list|)
function_decl|;
end_function_decl

begin_function_decl
name|GtkListStore
modifier|*
name|gimp_enum_store_new_with_values
parameter_list|(
name|GType
name|enum_type
parameter_list|,
name|gint
name|n_values
parameter_list|,
modifier|...
parameter_list|)
function_decl|;
end_function_decl

begin_function_decl
name|GtkListStore
modifier|*
name|gimp_enum_store_new_with_values_valist
parameter_list|(
name|GType
name|enum_type
parameter_list|,
name|gint
name|n_values
parameter_list|,
name|va_list
name|args
parameter_list|)
function_decl|;
end_function_decl

begin_function_decl
name|gboolean
name|gimp_enum_store_lookup_by_value
parameter_list|(
name|GtkTreeModel
modifier|*
name|model
parameter_list|,
name|gint
name|value
parameter_list|,
name|GtkTreeIter
modifier|*
name|iter
parameter_list|)
function_decl|;
end_function_decl

begin_function_decl
name|void
name|gimp_enum_store_set_stock_prefix
parameter_list|(
name|GimpEnumStore
modifier|*
name|store
parameter_list|,
specifier|const
name|gchar
modifier|*
name|stock_prefix
parameter_list|)
function_decl|;
end_function_decl

begin_endif
endif|#
directive|endif
end_endif

begin_comment
comment|/* __GIMP_ENUM_STORE_H__ */
end_comment

end_unit

