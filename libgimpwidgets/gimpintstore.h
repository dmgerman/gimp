begin_unit|revision:0.9.5;language:C;cregit-version:0.0.1
begin_comment
comment|/* LIBGIMP - The GIMP Library  * Copyright (C) 1995-1997 Peter Mattis and Spencer Kimball  *  * gimpintstore.c  * Copyright (C) 2004  Sven Neumann<sven@gimp.org>  *  * This library is free software: you can redistribute it and/or  * modify it under the terms of the GNU Lesser General Public  * License as published by the Free Software Foundation; either  * version 3 of the License, or (at your option) any later version.  *  * This library is distributed in the hope that it will be useful,  * but WITHOUT ANY WARRANTY; without even the implied warranty of  * MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the GNU  * Lesser General Public License for more details.  *  * You should have received a copy of the GNU Lesser General Public  * License along with this library.  If not, see  *<http://www.gnu.org/licenses/>.  */
end_comment

begin_ifndef
ifndef|#
directive|ifndef
name|__GIMP_INT_STORE_H__
end_ifndef

begin_define
DECL|macro|__GIMP_INT_STORE_H__
define|#
directive|define
name|__GIMP_INT_STORE_H__
end_define

begin_macro
name|G_BEGIN_DECLS
end_macro

begin_comment
comment|/**  * GimpIntStoreColumns:  * @GIMP_INT_STORE_VALUE:       the integer value  * @GIMP_INT_STORE_LABEL:       a human-readable label  * @GIMP_INT_STORE_STOCK_ID:    a stock ID  * @GIMP_INT_STORE_PIXBUF:      a #GdkPixbuf  * @GIMP_INT_STORE_USER_DATA:   arbitrary user data  * @GIMP_INT_STORE_NUM_COLUMNS: the number of columns  *  * The column types of #GimpIntStore.  **/
end_comment

begin_typedef
typedef|typedef
enum|enum
DECL|enum|__anon2c8134590103
block|{
DECL|enumerator|GIMP_INT_STORE_VALUE
name|GIMP_INT_STORE_VALUE
block|,
DECL|enumerator|GIMP_INT_STORE_LABEL
name|GIMP_INT_STORE_LABEL
block|,
DECL|enumerator|GIMP_INT_STORE_STOCK_ID
name|GIMP_INT_STORE_STOCK_ID
block|,
DECL|enumerator|GIMP_INT_STORE_PIXBUF
name|GIMP_INT_STORE_PIXBUF
block|,
DECL|enumerator|GIMP_INT_STORE_USER_DATA
name|GIMP_INT_STORE_USER_DATA
block|,
DECL|enumerator|GIMP_INT_STORE_NUM_COLUMNS
name|GIMP_INT_STORE_NUM_COLUMNS
DECL|typedef|GimpIntStoreColumns
block|}
name|GimpIntStoreColumns
typedef|;
end_typedef

begin_define
DECL|macro|GIMP_TYPE_INT_STORE
define|#
directive|define
name|GIMP_TYPE_INT_STORE
value|(gimp_int_store_get_type ())
end_define

begin_define
DECL|macro|GIMP_INT_STORE (obj)
define|#
directive|define
name|GIMP_INT_STORE
parameter_list|(
name|obj
parameter_list|)
value|(G_TYPE_CHECK_INSTANCE_CAST ((obj), GIMP_TYPE_INT_STORE, GimpIntStore))
end_define

begin_define
DECL|macro|GIMP_INT_STORE_CLASS (klass)
define|#
directive|define
name|GIMP_INT_STORE_CLASS
parameter_list|(
name|klass
parameter_list|)
value|(G_TYPE_CHECK_CLASS_CAST ((klass), GIMP_TYPE_INT_STORE, GimpIntStoreClass))
end_define

begin_define
DECL|macro|GIMP_IS_INT_STORE (obj)
define|#
directive|define
name|GIMP_IS_INT_STORE
parameter_list|(
name|obj
parameter_list|)
value|(G_TYPE_CHECK_INSTANCE_TYPE ((obj), GIMP_TYPE_INT_STORE))
end_define

begin_define
DECL|macro|GIMP_IS_INT_STORE_CLASS (klass)
define|#
directive|define
name|GIMP_IS_INT_STORE_CLASS
parameter_list|(
name|klass
parameter_list|)
value|(G_TYPE_CHECK_CLASS_TYPE ((klass), GIMP_TYPE_INT_STORE))
end_define

begin_define
DECL|macro|GIMP_INT_STORE_GET_CLASS (obj)
define|#
directive|define
name|GIMP_INT_STORE_GET_CLASS
parameter_list|(
name|obj
parameter_list|)
value|(G_TYPE_INSTANCE_GET_CLASS ((obj), GIMP_TYPE_INT_STORE, GimpIntStoreClass))
end_define

begin_typedef
DECL|typedef|GimpIntStoreClass
typedef|typedef
name|struct
name|_GimpIntStoreClass
name|GimpIntStoreClass
typedef|;
end_typedef

begin_struct
DECL|struct|_GimpIntStore
struct|struct
name|_GimpIntStore
block|{
DECL|member|parent_instance
name|GtkListStore
name|parent_instance
decl_stmt|;
comment|/*< private>*/
DECL|member|empty_iter
name|GtkTreeIter
modifier|*
name|empty_iter
decl_stmt|;
block|}
struct|;
end_struct

begin_struct
DECL|struct|_GimpIntStoreClass
struct|struct
name|_GimpIntStoreClass
block|{
DECL|member|parent_class
name|GtkListStoreClass
name|parent_class
decl_stmt|;
comment|/* Padding for future expansion */
DECL|member|_gimp_reserved1
name|void
function_decl|(
modifier|*
name|_gimp_reserved1
function_decl|)
parameter_list|(
name|void
parameter_list|)
function_decl|;
DECL|member|_gimp_reserved2
name|void
function_decl|(
modifier|*
name|_gimp_reserved2
function_decl|)
parameter_list|(
name|void
parameter_list|)
function_decl|;
DECL|member|_gimp_reserved3
name|void
function_decl|(
modifier|*
name|_gimp_reserved3
function_decl|)
parameter_list|(
name|void
parameter_list|)
function_decl|;
DECL|member|_gimp_reserved4
name|void
function_decl|(
modifier|*
name|_gimp_reserved4
function_decl|)
parameter_list|(
name|void
parameter_list|)
function_decl|;
block|}
struct|;
end_struct

begin_decl_stmt
name|GType
name|gimp_int_store_get_type
argument_list|(
name|void
argument_list|)
name|G_GNUC_CONST
decl_stmt|;
end_decl_stmt

begin_function_decl
name|GtkListStore
modifier|*
name|gimp_int_store_new
parameter_list|(
name|void
parameter_list|)
function_decl|;
end_function_decl

begin_function_decl
name|gboolean
name|gimp_int_store_lookup_by_value
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

begin_macro
name|G_END_DECLS
end_macro

begin_endif
endif|#
directive|endif
end_endif

begin_comment
comment|/* __GIMP_INT_STORE_H__ */
end_comment

end_unit

