begin_unit|revision:0.9.5;language:C;cregit-version:0.0.1
begin_comment
comment|/* GIMP - The GNU Image Manipulation Program  * Copyright (C) 1995 Spencer Kimball and Peter Mattis  *  * gimpidtable.h  * Copyright (C) 2011 Martin Nordholts<martinn@src.gnome.org>  *  * This program is free software: you can redistribute it and/or modify  * it under the terms of the GNU General Public License as published by  * the Free Software Foundation; either version 3 of the License, or  * (at your option) any later version.  *  * This program is distributed in the hope that it will be useful,  * but WITHOUT ANY WARRANTY; without even the implied warranty of  * MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the  * GNU General Public License for more details.  *  * You should have received a copy of the GNU General Public License  * along with this program.  If not, see<http://www.gnu.org/licenses/>.  */
end_comment

begin_ifndef
ifndef|#
directive|ifndef
name|__GIMP_ID_TABLE_H__
end_ifndef

begin_define
DECL|macro|__GIMP_ID_TABLE_H__
define|#
directive|define
name|__GIMP_ID_TABLE_H__
end_define

begin_include
include|#
directive|include
file|"gimpobject.h"
end_include

begin_define
DECL|macro|GIMP_TYPE_ID_TABLE
define|#
directive|define
name|GIMP_TYPE_ID_TABLE
value|(gimp_id_table_get_type ())
end_define

begin_define
DECL|macro|GIMP_ID_TABLE (obj)
define|#
directive|define
name|GIMP_ID_TABLE
parameter_list|(
name|obj
parameter_list|)
value|(G_TYPE_CHECK_INSTANCE_CAST ((obj), GIMP_TYPE_ID_TABLE, GimpIdTable))
end_define

begin_define
DECL|macro|GIMP_ID_TABLE_CLASS (klass)
define|#
directive|define
name|GIMP_ID_TABLE_CLASS
parameter_list|(
name|klass
parameter_list|)
value|(G_TYPE_CHECK_CLASS_CAST ((klass), GIMP_TYPE_ID_TABLE, GimpIdTableClass))
end_define

begin_define
DECL|macro|GIMP_IS_ID_TABLE (obj)
define|#
directive|define
name|GIMP_IS_ID_TABLE
parameter_list|(
name|obj
parameter_list|)
value|(G_TYPE_CHECK_INSTANCE_TYPE ((obj), GIMP_TYPE_ID_TABLE))
end_define

begin_define
DECL|macro|GIMP_IS_ID_TABLE_CLASS (klass)
define|#
directive|define
name|GIMP_IS_ID_TABLE_CLASS
parameter_list|(
name|klass
parameter_list|)
value|(G_TYPE_CHECK_CLASS_TYPE ((klass), GIMP_TYPE_ID_TABLE))
end_define

begin_define
DECL|macro|GIMP_ID_TABLE_GET_CLASS (obj)
define|#
directive|define
name|GIMP_ID_TABLE_GET_CLASS
parameter_list|(
name|obj
parameter_list|)
value|(G_TYPE_INSTANCE_GET_CLASS ((obj), GIMP_TYPE_ID_TABLE, GimpIdTableClass))
end_define

begin_typedef
DECL|typedef|GimpIdTableClass
typedef|typedef
name|struct
name|_GimpIdTableClass
name|GimpIdTableClass
typedef|;
end_typedef

begin_typedef
DECL|typedef|GimpIdTablePriv
typedef|typedef
name|struct
name|_GimpIdTablePriv
name|GimpIdTablePriv
typedef|;
end_typedef

begin_struct
DECL|struct|_GimpIdTable
struct|struct
name|_GimpIdTable
block|{
DECL|member|parent_instance
name|GimpObject
name|parent_instance
decl_stmt|;
DECL|member|priv
name|GimpIdTablePriv
modifier|*
name|priv
decl_stmt|;
block|}
struct|;
end_struct

begin_struct
DECL|struct|_GimpIdTableClass
struct|struct
name|_GimpIdTableClass
block|{
DECL|member|parent_class
name|GimpObjectClass
name|parent_class
decl_stmt|;
block|}
struct|;
end_struct

begin_decl_stmt
name|GType
name|gimp_id_table_get_type
argument_list|(
name|void
argument_list|)
name|G_GNUC_CONST
decl_stmt|;
end_decl_stmt

begin_function_decl
name|GimpIdTable
modifier|*
name|gimp_id_table_new
parameter_list|(
name|void
parameter_list|)
function_decl|;
end_function_decl

begin_function_decl
name|gint
name|gimp_id_table_insert
parameter_list|(
name|GimpIdTable
modifier|*
name|id_table
parameter_list|,
name|gpointer
name|data
parameter_list|)
function_decl|;
end_function_decl

begin_function_decl
name|gint
name|gimp_id_table_insert_with_id
parameter_list|(
name|GimpIdTable
modifier|*
name|id_table
parameter_list|,
name|gint
name|id
parameter_list|,
name|gpointer
name|data
parameter_list|)
function_decl|;
end_function_decl

begin_function_decl
name|void
name|gimp_id_table_replace
parameter_list|(
name|GimpIdTable
modifier|*
name|id_table
parameter_list|,
name|gint
name|id
parameter_list|,
name|gpointer
name|data
parameter_list|)
function_decl|;
end_function_decl

begin_function_decl
name|gpointer
name|gimp_id_table_lookup
parameter_list|(
name|GimpIdTable
modifier|*
name|id_table
parameter_list|,
name|gint
name|id
parameter_list|)
function_decl|;
end_function_decl

begin_function_decl
name|gboolean
name|gimp_id_table_remove
parameter_list|(
name|GimpIdTable
modifier|*
name|id_table
parameter_list|,
name|gint
name|id
parameter_list|)
function_decl|;
end_function_decl

begin_endif
endif|#
directive|endif
end_endif

begin_comment
comment|/*  __GIMP_ID_TABLE_H__  */
end_comment

end_unit

