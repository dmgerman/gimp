begin_unit|revision:0.9.5;language:C;cregit-version:0.0.1
begin_comment
comment|/* Plugin-helper.h   * Copyright (C) 2000 Nathan Summers  *  * This library is free software; you can redistribute it and/or  * modify it under the terms of the GNU Lesser General Public  * License as published by the Free Software Foundation; either  * version 2 of the License, or (at your option) any later version.  *  * This library is distributed in the hope that it will be useful,  * but WITHOUT ANY WARRANTY; without even the implied warranty of  * MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the GNU  * Lesser General Public License for more details.  *  * You should have received a copy of the GNU Lesser General Public  * License along with this library; if not, write to the  * Free Software Foundation, Inc., 59 Temple Place - Suite 330,  * Boston, MA 02111-1307, USA.  */
end_comment

begin_ifndef
ifndef|#
directive|ifndef
name|__PLUGIN_HELPER_H__
end_ifndef

begin_define
DECL|macro|__PLUGIN_HELPER_H__
define|#
directive|define
name|__PLUGIN_HELPER_H__
end_define

begin_function_decl
specifier|extern
name|void
name|plugin_module_install_procedure
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
name|menu_path
parameter_list|,
name|gchar
modifier|*
name|image_types
parameter_list|,
name|gint
name|nparams
parameter_list|,
name|gint
name|nreturn_vals
parameter_list|,
name|GimpParamDef
modifier|*
name|params
parameter_list|,
name|GimpParamDef
modifier|*
name|return_vals
parameter_list|,
name|GimpRunProc
name|run_proc
parameter_list|)
function_decl|;
end_function_decl

begin_endif
endif|#
directive|endif
end_endif

begin_comment
comment|/* __PLUGIN_HELPER_H__ */
end_comment

end_unit

