begin_unit|revision:0.9.5;language:C;cregit-version:0.0.1
begin_comment
comment|/* GIMP - The GNU Image Manipulation Program  * Copyright (C) 1995 Spencer Kimball and Peter Mattis  *  * gimpenvirontable.h  * (C) 2002 Manish Singh<yosh@gimp.org>  *  * This program is free software; you can redistribute it and/or modify  * it under the terms of the GNU General Public License as published by  * the Free Software Foundation; either version 2 of the License, or  * (at your option) any later version.  *  * This program is distributed in the hope that it will be useful,  * but WITHOUT ANY WARRANTY; without even the implied warranty of  * MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the  * GNU General Public License for more details.  *  * You should have received a copy of the GNU General Public License  * along with this program; if not, write to the Free Software  * Foundation, Inc., 59 Temple Place - Suite 330, Boston, MA 02111-1307, USA.  */
end_comment

begin_ifndef
ifndef|#
directive|ifndef
name|__GIMP_ENVIRON_TABLE_H__
end_ifndef

begin_define
DECL|macro|__GIMP_ENVIRON_TABLE_H__
define|#
directive|define
name|__GIMP_ENVIRON_TABLE_H__
end_define

begin_define
DECL|macro|GIMP_TYPE_ENVIRON_TABLE
define|#
directive|define
name|GIMP_TYPE_ENVIRON_TABLE
value|(gimp_environ_table_get_type ())
end_define

begin_define
DECL|macro|GIMP_ENVIRON_TABLE (obj)
define|#
directive|define
name|GIMP_ENVIRON_TABLE
parameter_list|(
name|obj
parameter_list|)
value|(G_TYPE_CHECK_INSTANCE_CAST ((obj), GIMP_TYPE_ENVIRON_TABLE, GimpEnvironTable))
end_define

begin_define
DECL|macro|GIMP_ENVIRON_TABLE_CLASS (klass)
define|#
directive|define
name|GIMP_ENVIRON_TABLE_CLASS
parameter_list|(
name|klass
parameter_list|)
value|(G_TYPE_CHECK_CLASS_CAST ((klass), GIMP_TYPE_ENVIRON_TABLE, GimpEnvironTableClass))
end_define

begin_define
DECL|macro|GIMP_IS_ENVIRON_TABLE (obj)
define|#
directive|define
name|GIMP_IS_ENVIRON_TABLE
parameter_list|(
name|obj
parameter_list|)
value|(G_TYPE_CHECK_INSTANCE_TYPE ((obj), GIMP_TYPE_ENVIRON_TABLE))
end_define

begin_define
DECL|macro|GIMP_IS_ENVIRON_TABLE_CLASS (klass)
define|#
directive|define
name|GIMP_IS_ENVIRON_TABLE_CLASS
parameter_list|(
name|klass
parameter_list|)
value|(G_TYPE_CHECK_CLASS_TYPE ((klass), GIMP_TYPE_ENVIRON_TABLE))
end_define

begin_define
DECL|macro|GIMP_ENVIRON_TABLE_GET_CLASS (obj)
define|#
directive|define
name|GIMP_ENVIRON_TABLE_GET_CLASS
parameter_list|(
name|obj
parameter_list|)
value|(G_TYPE_INSTANCE_GET_CLASS ((obj), GIMP_TYPE_ENVIRON_TABLE, GimpEnvironTableClass))
end_define

begin_typedef
DECL|typedef|GimpEnvironTableClass
typedef|typedef
name|struct
name|_GimpEnvironTableClass
name|GimpEnvironTableClass
typedef|;
end_typedef

begin_struct
DECL|struct|_GimpEnvironTable
struct|struct
name|_GimpEnvironTable
block|{
DECL|member|parent_instance
name|GObject
name|parent_instance
decl_stmt|;
DECL|member|vars
name|GHashTable
modifier|*
name|vars
decl_stmt|;
DECL|member|internal
name|GHashTable
modifier|*
name|internal
decl_stmt|;
DECL|member|envp
name|gchar
modifier|*
modifier|*
name|envp
decl_stmt|;
block|}
struct|;
end_struct

begin_struct
DECL|struct|_GimpEnvironTableClass
struct|struct
name|_GimpEnvironTableClass
block|{
DECL|member|parent_class
name|GObjectClass
name|parent_class
decl_stmt|;
block|}
struct|;
end_struct

begin_decl_stmt
name|GType
name|gimp_environ_table_get_type
argument_list|(
name|void
argument_list|)
name|G_GNUC_CONST
decl_stmt|;
end_decl_stmt

begin_function_decl
name|GimpEnvironTable
modifier|*
name|gimp_environ_table_new
parameter_list|(
name|void
parameter_list|)
function_decl|;
end_function_decl

begin_function_decl
name|void
name|gimp_environ_table_load
parameter_list|(
name|GimpEnvironTable
modifier|*
name|environ_table
parameter_list|,
specifier|const
name|gchar
modifier|*
name|env_path
parameter_list|)
function_decl|;
end_function_decl

begin_function_decl
name|void
name|gimp_environ_table_add
parameter_list|(
name|GimpEnvironTable
modifier|*
name|environ_table
parameter_list|,
specifier|const
name|gchar
modifier|*
name|name
parameter_list|,
specifier|const
name|gchar
modifier|*
name|value
parameter_list|,
specifier|const
name|gchar
modifier|*
name|separator
parameter_list|)
function_decl|;
end_function_decl

begin_function_decl
name|void
name|gimp_environ_table_remove
parameter_list|(
name|GimpEnvironTable
modifier|*
name|environ_table
parameter_list|,
specifier|const
name|gchar
modifier|*
name|name
parameter_list|)
function_decl|;
end_function_decl

begin_function_decl
name|void
name|gimp_environ_table_clear
parameter_list|(
name|GimpEnvironTable
modifier|*
name|environ_table
parameter_list|)
function_decl|;
end_function_decl

begin_function_decl
name|void
name|gimp_environ_table_clear_all
parameter_list|(
name|GimpEnvironTable
modifier|*
name|environ_table
parameter_list|)
function_decl|;
end_function_decl

begin_function_decl
name|gchar
modifier|*
modifier|*
name|gimp_environ_table_get_envp
parameter_list|(
name|GimpEnvironTable
modifier|*
name|environ_table
parameter_list|)
function_decl|;
end_function_decl

begin_endif
endif|#
directive|endif
end_endif

begin_comment
comment|/* __GIMP_ENVIRON_TABLE_H__ */
end_comment

end_unit

