begin_unit|revision:0.9.5;language:C;cregit-version:0.0.1
begin_comment
comment|/* The GIMP -- an image manipulation program  * Copyright (C) 1995 Spencer Kimball and Peter Mattis  *  * This program is free software; you can redistribute it and/or modify  * it under the terms of the GNU General Public License as published by  * the Free Software Foundation; either version 2 of the License, or  * (at your option) any later version.  *  * This program is distributed in the hope that it will be useful,  * but WITHOUT ANY WARRANTY; without even the implied warranty of  * MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the  * GNU General Public License for more details.  *  * You should have received a copy of the GNU General Public License  * along with this program; if not, write to the Free Software  * Foundation, Inc., 59 Temple Place - Suite 330, Boston, MA 02111-1307, USA.  */
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

begin_function_decl
name|void
name|plug_ins_init
parameter_list|(
name|Gimp
modifier|*
name|gimp
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
name|PlugInProcDef
modifier|*
name|proc_def
parameter_list|)
function_decl|;
end_function_decl

begin_comment
comment|/* Add in the file load/save handler fields procedure. */
end_comment

begin_function_decl
name|PlugInProcDef
modifier|*
name|plug_ins_file_handler
parameter_list|(
name|Gimp
modifier|*
name|gimp
parameter_list|,
name|gchar
modifier|*
name|name
parameter_list|,
name|gchar
modifier|*
name|extensions
parameter_list|,
name|gchar
modifier|*
name|prefixes
parameter_list|,
name|gchar
modifier|*
name|magics
parameter_list|)
function_decl|;
end_function_decl

begin_comment
comment|/* Add a plug-in definition. */
end_comment

begin_function_decl
name|void
name|plug_ins_def_add_from_rc
parameter_list|(
name|Gimp
modifier|*
name|gimp
parameter_list|,
name|PlugInDef
modifier|*
name|plug_in_def
parameter_list|)
function_decl|;
end_function_decl

begin_comment
comment|/* Add/Remove temporary procedures. */
end_comment

begin_function_decl
name|void
name|plug_ins_temp_proc_def_add
parameter_list|(
name|Gimp
modifier|*
name|gimp
parameter_list|,
name|PlugInProcDef
modifier|*
name|proc_def
parameter_list|)
function_decl|;
end_function_decl

begin_function_decl
name|void
name|plug_ins_temp_proc_def_remove
parameter_list|(
name|Gimp
modifier|*
name|gimp
parameter_list|,
name|PlugInProcDef
modifier|*
name|proc_def
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
comment|/* Retrieve a plug-ins help path */
end_comment

begin_function_decl
specifier|const
name|gchar
modifier|*
name|plug_ins_help_path
parameter_list|(
name|Gimp
modifier|*
name|gimp
parameter_list|,
specifier|const
name|gchar
modifier|*
name|prog_name
parameter_list|)
function_decl|;
end_function_decl

begin_comment
comment|/* Retreive a plug-ins proc_def from its ProcRecord */
end_comment

begin_function_decl
name|PlugInProcDef
modifier|*
name|plug_ins_proc_def_find
parameter_list|(
name|Gimp
modifier|*
name|gimp
parameter_list|,
name|ProcRecord
modifier|*
name|proc_rec
parameter_list|)
function_decl|;
end_function_decl

begin_function_decl
name|GSList
modifier|*
name|plug_ins_extensions_parse
parameter_list|(
name|gchar
modifier|*
name|extensions
parameter_list|)
function_decl|;
end_function_decl

begin_function_decl
name|PlugInImageType
name|plug_ins_image_types_parse
parameter_list|(
name|gchar
modifier|*
name|image_types
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

