begin_unit|revision:0.9.5;language:C;cregit-version:0.0.1
begin_comment
comment|/* LIBGIMP - The GIMP Library  * Copyright (C) 1995-2000 Peter Mattis and Spencer Kimball  *  * gimpproceduraldb_pdb.h  *  * This library is free software; you can redistribute it and/or  * modify it under the terms of the GNU Lesser General Public  * License as published by the Free Software Foundation; either  * version 2 of the License, or (at your option) any later version.  *  * This library is distributed in the hope that it will be useful,  * but WITHOUT ANY WARRANTY; without even the implied warranty of  * MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the GNU  * Lesser General Public License for more details.  *  * You should have received a copy of the GNU Lesser General Public  * License along with this library; if not, write to the  * Free Software Foundation, Inc., 59 Temple Place - Suite 330,  * Boston, MA 02111-1307, USA.  */
end_comment

begin_comment
comment|/* NOTE: This file is autogenerated by pdbgen.pl */
end_comment

begin_ifndef
ifndef|#
directive|ifndef
name|__GIMP_PROCEDURAL_DB_PDB_H__
end_ifndef

begin_define
DECL|macro|__GIMP_PROCEDURAL_DB_PDB_H__
define|#
directive|define
name|__GIMP_PROCEDURAL_DB_PDB_H__
end_define

begin_ifdef
ifdef|#
directive|ifdef
name|__cplusplus
end_ifdef

begin_extern
extern|extern
literal|"C"
block|{
endif|#
directive|endif
comment|/* __cplusplus */
comment|/* For information look into the C source or the html documentation */
name|void
name|gimp_procedural_db_dump
parameter_list|(
name|gchar
modifier|*
name|filename
parameter_list|)
function_decl|;
name|void
name|gimp_procedural_db_query
parameter_list|(
name|gchar
modifier|*
name|name
parameter_list|,
name|gchar
modifier|*
name|blurb
parameter_list|,
name|gchar
modifier|*
name|help
parameter_list|,
name|gchar
modifier|*
name|author
parameter_list|,
name|gchar
modifier|*
name|copyright
parameter_list|,
name|gchar
modifier|*
name|date
parameter_list|,
name|gchar
modifier|*
name|proc_type
parameter_list|,
name|gint
modifier|*
name|num_matches
parameter_list|,
name|gchar
modifier|*
modifier|*
modifier|*
name|proc_names
parameter_list|)
function_decl|;
name|gboolean
name|_gimp_procedural_db_proc_info
parameter_list|(
name|gchar
modifier|*
name|procedure
parameter_list|,
name|gchar
modifier|*
modifier|*
name|blurb
parameter_list|,
name|gchar
modifier|*
modifier|*
name|help
parameter_list|,
name|gchar
modifier|*
modifier|*
name|author
parameter_list|,
name|gchar
modifier|*
modifier|*
name|copyright
parameter_list|,
name|gchar
modifier|*
modifier|*
name|date
parameter_list|,
name|GimpPDBProcType
modifier|*
name|proc_type
parameter_list|,
name|gint
modifier|*
name|num_args
parameter_list|,
name|gint
modifier|*
name|num_values
parameter_list|)
function_decl|;
name|gboolean
name|gimp_procedural_db_proc_arg
parameter_list|(
name|gchar
modifier|*
name|procedure
parameter_list|,
name|gint
name|arg_num
parameter_list|,
name|GimpPDBArgType
modifier|*
name|arg_type
parameter_list|,
name|gchar
modifier|*
modifier|*
name|arg_name
parameter_list|,
name|gchar
modifier|*
modifier|*
name|arg_desc
parameter_list|)
function_decl|;
name|gboolean
name|gimp_procedural_db_proc_val
parameter_list|(
name|gchar
modifier|*
name|procedure
parameter_list|,
name|gint
name|val_num
parameter_list|,
name|GimpPDBArgType
modifier|*
name|val_type
parameter_list|,
name|gchar
modifier|*
modifier|*
name|val_name
parameter_list|,
name|gchar
modifier|*
modifier|*
name|val_desc
parameter_list|)
function_decl|;
name|void
name|_gimp_procedural_db_get_data
parameter_list|(
name|gchar
modifier|*
name|identifier
parameter_list|,
name|gint
modifier|*
name|bytes
parameter_list|,
name|guint8
modifier|*
modifier|*
name|data
parameter_list|)
function_decl|;
name|gint
name|gimp_procedural_db_get_data_size
parameter_list|(
name|gchar
modifier|*
name|identifier
parameter_list|)
function_decl|;
name|void
name|_gimp_procedural_db_set_data
parameter_list|(
name|gchar
modifier|*
name|identifier
parameter_list|,
name|gint
name|bytes
parameter_list|,
name|guint8
modifier|*
name|data
parameter_list|)
function_decl|;
ifdef|#
directive|ifdef
name|__cplusplus
block|}
end_extern

begin_endif
endif|#
directive|endif
end_endif

begin_comment
comment|/* __cplusplus */
end_comment

begin_endif
endif|#
directive|endif
end_endif

begin_comment
comment|/* __GIMP_PROCEDURAL_DB_PDB_H__ */
end_comment

end_unit

