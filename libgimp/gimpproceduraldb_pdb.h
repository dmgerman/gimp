begin_unit|revision:0.9.5;language:C;cregit-version:0.0.1
begin_comment
comment|/* LIBGIMP - The GIMP Library  * Copyright (C) 1995-1997 Peter Mattis and Spencer Kimball  *  * gimpproceduraldb_pdb.h  *  * This library is free software; you can redistribute it and/or  * modify it under the terms of the GNU Lesser General Public  * License as published by the Free Software Foundation; either  * version 2 of the License, or (at your option) any later version.  *   * This library is distributed in the hope that it will be useful,  * but WITHOUT ANY WARRANTY; without even the implied warranty of   * MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the GNU   * Lesser General Public License for more details.  *  * You should have received a copy of the GNU Lesser General Public  * License along with this library; if not, write to the  * Free Software Foundation, Inc., 59 Temple Place - Suite 330,  * Boston, MA 02111-1307, USA.  */
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
comment|/* Specify a range of data to be associated with 'id'.  *  The data will exist for as long as the main gimp  *  application is running.  */
name|void
name|gimp_procedural_db_set_data
parameter_list|(
name|gchar
modifier|*
name|id
parameter_list|,
name|gpointer
name|data
parameter_list|,
name|guint32
name|length
parameter_list|)
function_decl|;
comment|/* Retrieve the piece of data stored within the main  *  gimp application specified by 'id'. The data is  *  stored in the supplied buffer.  Make sure enough  *  space is allocated.  */
name|void
name|gimp_procedural_db_get_data
parameter_list|(
name|gchar
modifier|*
name|id
parameter_list|,
name|gpointer
name|data
parameter_list|)
function_decl|;
comment|/* Get the size in bytes of the data stored by a gimp_get_data  * id. As size of zero may indicate that there is no such  * identifier in the database.  */
name|guint32
name|gimp_procedural_db_get_data_size
parameter_list|(
name|gchar
modifier|*
name|id
parameter_list|)
function_decl|;
comment|/* Query the gimp application's procedural database.  *  The arguments are regular expressions which select  *  which procedure names will be returned in 'proc_names'.  */
name|void
name|gimp_procedural_db_query
parameter_list|(
name|gchar
modifier|*
name|name_regexp
parameter_list|,
name|gchar
modifier|*
name|blurb_regexp
parameter_list|,
name|gchar
modifier|*
name|help_regexp
parameter_list|,
name|gchar
modifier|*
name|author_regexp
parameter_list|,
name|gchar
modifier|*
name|copyright_regexp
parameter_list|,
name|gchar
modifier|*
name|date_regexp
parameter_list|,
name|gchar
modifier|*
name|proc_type_regexp
parameter_list|,
name|gint
modifier|*
name|nprocs
parameter_list|,
name|gchar
modifier|*
modifier|*
modifier|*
name|proc_names
parameter_list|)
function_decl|;
comment|/* Query the gimp application's procedural database  *  regarding a particular procedure.  */
name|gboolean
name|gimp_procedural_db_query_proc
parameter_list|(
name|gchar
modifier|*
name|proc_name
parameter_list|,
name|gchar
modifier|*
modifier|*
name|proc_blurb
parameter_list|,
name|gchar
modifier|*
modifier|*
name|proc_help
parameter_list|,
name|gchar
modifier|*
modifier|*
name|proc_author
parameter_list|,
name|gchar
modifier|*
modifier|*
name|proc_copyright
parameter_list|,
name|gchar
modifier|*
modifier|*
name|proc_date
parameter_list|,
name|gint
modifier|*
name|proc_type
parameter_list|,
name|gint
modifier|*
name|nparams
parameter_list|,
name|gint
modifier|*
name|nreturn_vals
parameter_list|,
name|GimpParamDef
modifier|*
modifier|*
name|params
parameter_list|,
name|GimpParamDef
modifier|*
modifier|*
name|return_vals
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

