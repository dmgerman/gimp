begin_unit|revision:0.9.5;language:C;cregit-version:0.0.1
begin_comment
comment|/* The GIMP -- an image manipulation program  * Copyright (C) 1995 Spencer Kimball and Peter Mattis  *  * gimpinterpreterdb.h  * (C) 2005 Manish Singh<yosh@gimp.org>  *  * This program is free software; you can redistribute it and/or modify  * it under the terms of the GNU General Public License as published by  * the Free Software Foundation; either version 2 of the License, or  * (at your option) any later version.  *  * This program is distributed in the hope that it will be useful,  * but WITHOUT ANY WARRANTY; without even the implied warranty of  * MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the  * GNU General Public License for more details.  *  * You should have received a copy of the GNU General Public License  * along with this program; if not, write to the Free Software  * Foundation, Inc., 59 Temple Place - Suite 330, Boston, MA 02111-1307, USA.  */
end_comment

begin_ifndef
ifndef|#
directive|ifndef
name|__GIMP_INTERPRETER_DB_H__
end_ifndef

begin_define
DECL|macro|__GIMP_INTERPRETER_DB_H__
define|#
directive|define
name|__GIMP_INTERPRETER_DB_H__
end_define

begin_define
DECL|macro|GIMP_TYPE_INTERPRETER_DB
define|#
directive|define
name|GIMP_TYPE_INTERPRETER_DB
value|(gimp_interpreter_db_get_type ())
end_define

begin_define
DECL|macro|GIMP_INTERPRETER_DB (obj)
define|#
directive|define
name|GIMP_INTERPRETER_DB
parameter_list|(
name|obj
parameter_list|)
value|(G_TYPE_CHECK_INSTANCE_CAST ((obj), GIMP_TYPE_INTERPRETER_DB, GimpInterpreterDB))
end_define

begin_define
DECL|macro|GIMP_INTERPRETER_DB_CLASS (klass)
define|#
directive|define
name|GIMP_INTERPRETER_DB_CLASS
parameter_list|(
name|klass
parameter_list|)
value|(G_TYPE_CHECK_CLASS_CAST ((klass), GIMP_TYPE_INTERPRETER_DB, GimpInterpreterDBClass))
end_define

begin_define
DECL|macro|GIMP_IS_INTERPRETER_DB (obj)
define|#
directive|define
name|GIMP_IS_INTERPRETER_DB
parameter_list|(
name|obj
parameter_list|)
value|(G_TYPE_CHECK_INSTANCE_TYPE ((obj), GIMP_TYPE_INTERPRETER_DB))
end_define

begin_define
DECL|macro|GIMP_IS_INTERPRETER_DB_CLASS (klass)
define|#
directive|define
name|GIMP_IS_INTERPRETER_DB_CLASS
parameter_list|(
name|klass
parameter_list|)
value|(G_TYPE_CHECK_CLASS_TYPE ((klass), GIMP_TYPE_INTERPRETER_DB))
end_define

begin_define
DECL|macro|GIMP_INTERPRETER_DB_GET_CLASS (obj)
define|#
directive|define
name|GIMP_INTERPRETER_DB_GET_CLASS
parameter_list|(
name|obj
parameter_list|)
value|(G_TYPE_INSTANCE_GET_CLASS ((obj), GIMP_TYPE_INTERPRETER_DB, GimpInterpreterDBClass))
end_define

begin_typedef
DECL|typedef|GimpInterpreterDBClass
typedef|typedef
name|struct
name|_GimpInterpreterDBClass
name|GimpInterpreterDBClass
typedef|;
end_typedef

begin_struct
DECL|struct|_GimpInterpreterDB
struct|struct
name|_GimpInterpreterDB
block|{
DECL|member|parent_instance
name|GObject
name|parent_instance
decl_stmt|;
DECL|member|programs
name|GHashTable
modifier|*
name|programs
decl_stmt|;
DECL|member|magics
name|GSList
modifier|*
name|magics
decl_stmt|;
DECL|member|magic_names
name|GHashTable
modifier|*
name|magic_names
decl_stmt|;
DECL|member|extensions
name|GHashTable
modifier|*
name|extensions
decl_stmt|;
DECL|member|extension_names
name|GHashTable
modifier|*
name|extension_names
decl_stmt|;
block|}
struct|;
end_struct

begin_struct
DECL|struct|_GimpInterpreterDBClass
struct|struct
name|_GimpInterpreterDBClass
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
name|gimp_interpreter_db_get_type
argument_list|(
name|void
argument_list|)
name|G_GNUC_CONST
decl_stmt|;
end_decl_stmt

begin_function_decl
name|GimpInterpreterDB
modifier|*
name|gimp_interpreter_db_new
parameter_list|(
name|void
parameter_list|)
function_decl|;
end_function_decl

begin_function_decl
name|void
name|gimp_interpreter_db_load
parameter_list|(
name|GimpInterpreterDB
modifier|*
name|db
parameter_list|,
specifier|const
name|gchar
modifier|*
name|interp_path
parameter_list|)
function_decl|;
end_function_decl

begin_function_decl
name|void
name|gimp_interpreter_db_clear
parameter_list|(
name|GimpInterpreterDB
modifier|*
name|db
parameter_list|)
function_decl|;
end_function_decl

begin_function_decl
name|gchar
modifier|*
name|gimp_interpreter_db_resolve
parameter_list|(
name|GimpInterpreterDB
modifier|*
name|db
parameter_list|,
specifier|const
name|gchar
modifier|*
name|program_path
parameter_list|,
name|gchar
modifier|*
modifier|*
name|interp_arg
parameter_list|)
function_decl|;
end_function_decl

begin_endif
endif|#
directive|endif
end_endif

begin_comment
comment|/* __GIMP_INTERPRETER_DB_H__ */
end_comment

end_unit

