begin_unit|revision:0.9.5;language:C;cregit-version:0.0.1
begin_comment
comment|/* The GIMP -- an image manipulation program  * Copyright (C) 1995 Spencer Kimball and Peter Mattis  *  * plug-ins.h  *  * This program is free software; you can redistribute it and/or modify  * it under the terms of the GNU General Public License as published by  * the Free Software Foundation; either version 2 of the License, or  * (at your option) any later version.  *  * This program is distributed in the hope that it will be useful,  * but WITHOUT ANY WARRANTY; without even the implied warranty of  * MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the  * GNU General Public License for more details.  *  * You should have received a copy of the GNU General Public License  * along with this program; if not, write to the Free Software  * Foundation, Inc., 59 Temple Place - Suite 330, Boston, MA 02111-1307, USA.  */
end_comment

begin_ifndef
ifndef|#
directive|ifndef
name|__PLUG_INS_H__
end_ifndef

begin_define
DECL|macro|__PLUG_INS_H__
define|#
directive|define
name|__PLUG_INS_H__
end_define

begin_struct
DECL|struct|_PlugInMenuBranch
struct|struct
name|_PlugInMenuBranch
block|{
DECL|member|prog_name
name|gchar
modifier|*
name|prog_name
decl_stmt|;
DECL|member|menu_path
name|gchar
modifier|*
name|menu_path
decl_stmt|;
DECL|member|menu_label
name|gchar
modifier|*
name|menu_label
decl_stmt|;
block|}
struct|;
end_struct

begin_function_decl
name|void
name|plug_ins_init
parameter_list|(
name|Gimp
modifier|*
name|gimp
parameter_list|,
name|GimpContext
modifier|*
name|context
parameter_list|,
name|GimpInitStatusFunc
name|status_callback
parameter_list|)
function_decl|;
end_function_decl

begin_function_decl
name|void
name|plug_ins_exit
parameter_list|(
name|Gimp
modifier|*
name|gimp
parameter_list|)
function_decl|;
end_function_decl

begin_comment
comment|/* Register an internal plug-in.  This is for file load-save  * handlers, which are organized around the plug-in data structure.  * This could all be done a little better, but oh well.  -josh  */
end_comment

begin_function_decl
name|void
name|plug_ins_add_internal
parameter_list|(
name|Gimp
modifier|*
name|gimp
parameter_list|,
name|GimpPlugInProcedure
modifier|*
name|proc
parameter_list|)
function_decl|;
end_function_decl

begin_comment
comment|/* Add in the file load/save handler fields procedure. */
end_comment

begin_function_decl
name|GimpPlugInProcedure
modifier|*
name|plug_ins_file_register_magic
parameter_list|(
name|Gimp
modifier|*
name|gimp
parameter_list|,
specifier|const
name|gchar
modifier|*
name|name
parameter_list|,
specifier|const
name|gchar
modifier|*
name|extensions
parameter_list|,
specifier|const
name|gchar
modifier|*
name|prefixes
parameter_list|,
specifier|const
name|gchar
modifier|*
name|magics
parameter_list|)
function_decl|;
end_function_decl

begin_function_decl
name|GimpPlugInProcedure
modifier|*
name|plug_ins_file_register_mime
parameter_list|(
name|Gimp
modifier|*
name|gimp
parameter_list|,
specifier|const
name|gchar
modifier|*
name|name
parameter_list|,
specifier|const
name|gchar
modifier|*
name|mime_type
parameter_list|)
function_decl|;
end_function_decl

begin_function_decl
name|GimpPlugInProcedure
modifier|*
name|plug_ins_file_register_thumb_loader
parameter_list|(
name|Gimp
modifier|*
name|gimp
parameter_list|,
specifier|const
name|gchar
modifier|*
name|load_proc
parameter_list|,
specifier|const
name|gchar
modifier|*
name|thumb_proc
parameter_list|)
function_decl|;
end_function_decl

begin_comment
comment|/* Add/Remove temporary procedures. */
end_comment

begin_function_decl
name|void
name|plug_ins_temp_procedure_add
parameter_list|(
name|Gimp
modifier|*
name|gimp
parameter_list|,
name|GimpTemporaryProcedure
modifier|*
name|proc
parameter_list|)
function_decl|;
end_function_decl

begin_function_decl
name|void
name|plug_ins_temp_procedure_remove
parameter_list|(
name|Gimp
modifier|*
name|gimp
parameter_list|,
name|GimpTemporaryProcedure
modifier|*
name|proc
parameter_list|)
function_decl|;
end_function_decl

begin_comment
comment|/* Add a menu branch */
end_comment

begin_function_decl
name|void
name|plug_ins_menu_branch_add
parameter_list|(
name|Gimp
modifier|*
name|gimp
parameter_list|,
specifier|const
name|gchar
modifier|*
name|prog_name
parameter_list|,
specifier|const
name|gchar
modifier|*
name|menu_path
parameter_list|,
specifier|const
name|gchar
modifier|*
name|menu_label
parameter_list|)
function_decl|;
end_function_decl

begin_comment
comment|/* Add a locale domain */
end_comment

begin_function_decl
name|void
name|plug_ins_locale_domain_add
parameter_list|(
name|Gimp
modifier|*
name|gimp
parameter_list|,
specifier|const
name|gchar
modifier|*
name|prog_name
parameter_list|,
specifier|const
name|gchar
modifier|*
name|domain_name
parameter_list|,
specifier|const
name|gchar
modifier|*
name|domain_path
parameter_list|)
function_decl|;
end_function_decl

begin_comment
comment|/* Retrieve a plug-ins locale domain */
end_comment

begin_function_decl
specifier|const
name|gchar
modifier|*
name|plug_ins_locale_domain
parameter_list|(
name|Gimp
modifier|*
name|gimp
parameter_list|,
specifier|const
name|gchar
modifier|*
name|prog_name
parameter_list|,
specifier|const
name|gchar
modifier|*
modifier|*
name|locale_path
parameter_list|)
function_decl|;
end_function_decl

begin_comment
comment|/* Add a help domain */
end_comment

begin_function_decl
name|void
name|plug_ins_help_domain_add
parameter_list|(
name|Gimp
modifier|*
name|gimp
parameter_list|,
specifier|const
name|gchar
modifier|*
name|prog_name
parameter_list|,
specifier|const
name|gchar
modifier|*
name|domain_name
parameter_list|,
specifier|const
name|gchar
modifier|*
name|domain_uri
parameter_list|)
function_decl|;
end_function_decl

begin_comment
comment|/* Retrieve a plug-ins help domain */
end_comment

begin_function_decl
specifier|const
name|gchar
modifier|*
name|plug_ins_help_domain
parameter_list|(
name|Gimp
modifier|*
name|gimp
parameter_list|,
specifier|const
name|gchar
modifier|*
name|prog_name
parameter_list|,
specifier|const
name|gchar
modifier|*
modifier|*
name|help_uri
parameter_list|)
function_decl|;
end_function_decl

begin_comment
comment|/* Retrieve all help domains */
end_comment

begin_function_decl
name|gint
name|plug_ins_help_domains
parameter_list|(
name|Gimp
modifier|*
name|gimp
parameter_list|,
name|gchar
modifier|*
modifier|*
modifier|*
name|help_domains
parameter_list|,
name|gchar
modifier|*
modifier|*
modifier|*
name|help_uris
parameter_list|)
function_decl|;
end_function_decl

begin_endif
endif|#
directive|endif
end_endif

begin_comment
comment|/* __PLUG_INS_H__ */
end_comment

end_unit

