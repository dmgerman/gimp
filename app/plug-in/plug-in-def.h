begin_unit|revision:0.9.5;language:C;cregit-version:0.0.1
begin_comment
comment|/* The GIMP -- an image manipulation program  * Copyright (C) 1995 Spencer Kimball and Peter Mattis  *  * This program is free software; you can redistribute it and/or modify  * it under the terms of the GNU General Public License as published by  * the Free Software Foundation; either version 2 of the License, or  * (at your option) any later version.  *  * This program is distributed in the hope that it will be useful,  * but WITHOUT ANY WARRANTY; without even the implied warranty of  * MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the  * GNU General Public License for more details.  *  * You should have received a copy of the GNU General Public License  * along with this program; if not, write to the Free Software  * Foundation, Inc., 59 Temple Place - Suite 330, Boston, MA 02111-1307, USA.  */
end_comment

begin_ifndef
ifndef|#
directive|ifndef
name|__PLUG_IN_DEF_H__
end_ifndef

begin_define
DECL|macro|__PLUG_IN_DEF_H__
define|#
directive|define
name|__PLUG_IN_DEF_H__
end_define

begin_include
include|#
directive|include
file|<time.h>
end_include

begin_struct
DECL|struct|_PlugInDef
struct|struct
name|_PlugInDef
block|{
DECL|member|prog
name|gchar
modifier|*
name|prog
decl_stmt|;
DECL|member|proc_defs
name|GSList
modifier|*
name|proc_defs
decl_stmt|;
DECL|member|locale_domain
name|gchar
modifier|*
name|locale_domain
decl_stmt|;
DECL|member|locale_path
name|gchar
modifier|*
name|locale_path
decl_stmt|;
DECL|member|help_path
name|gchar
modifier|*
name|help_path
decl_stmt|;
DECL|member|mtime
name|time_t
name|mtime
decl_stmt|;
DECL|member|needs_query
name|gboolean
name|needs_query
decl_stmt|;
comment|/* Does the plug-in need to be queried ?     */
DECL|member|has_init
name|gboolean
name|has_init
decl_stmt|;
comment|/* Does the plug-in need to be initialized ? */
block|}
struct|;
end_struct

begin_function_decl
name|PlugInDef
modifier|*
name|plug_in_def_new
parameter_list|(
specifier|const
name|gchar
modifier|*
name|prog
parameter_list|)
function_decl|;
end_function_decl

begin_function_decl
name|void
name|plug_in_def_free
parameter_list|(
name|PlugInDef
modifier|*
name|plug_in_def
parameter_list|,
name|gboolean
name|free_proc_defs
parameter_list|)
function_decl|;
end_function_decl

begin_function_decl
name|void
name|plug_in_def_add_proc_def
parameter_list|(
name|PlugInDef
modifier|*
name|plug_in_def
parameter_list|,
name|PlugInProcDef
modifier|*
name|proc_def
parameter_list|)
function_decl|;
end_function_decl

begin_function_decl
name|void
name|plug_in_def_set_locale_domain_name
parameter_list|(
name|PlugInDef
modifier|*
name|plug_in_def
parameter_list|,
specifier|const
name|gchar
modifier|*
name|domain_name
parameter_list|)
function_decl|;
end_function_decl

begin_function_decl
name|void
name|plug_in_def_set_locale_domain_path
parameter_list|(
name|PlugInDef
modifier|*
name|plug_in_def
parameter_list|,
specifier|const
name|gchar
modifier|*
name|domain_path
parameter_list|)
function_decl|;
end_function_decl

begin_function_decl
name|void
name|plug_in_def_set_help_path
parameter_list|(
name|PlugInDef
modifier|*
name|plug_in_def
parameter_list|,
specifier|const
name|gchar
modifier|*
name|help_path
parameter_list|)
function_decl|;
end_function_decl

begin_function_decl
name|void
name|plug_in_def_set_mtime
parameter_list|(
name|PlugInDef
modifier|*
name|plug_in_def
parameter_list|,
name|time_t
name|mtime
parameter_list|)
function_decl|;
end_function_decl

begin_function_decl
name|void
name|plug_in_def_set_needs_query
parameter_list|(
name|PlugInDef
modifier|*
name|plug_in_def
parameter_list|,
name|gboolean
name|needs_query
parameter_list|)
function_decl|;
end_function_decl

begin_function_decl
name|void
name|plug_in_def_set_has_init
parameter_list|(
name|PlugInDef
modifier|*
name|plug_in_def
parameter_list|,
name|gboolean
name|has_init
parameter_list|)
function_decl|;
end_function_decl

begin_endif
endif|#
directive|endif
end_endif

begin_comment
comment|/* __PLUG_IN_DEF_H__ */
end_comment

end_unit

