begin_unit|revision:0.9.5;language:C;cregit-version:0.0.1
begin_comment
comment|/* The GIMP -- an image manipulation program  * Copyright (C) 1995 Spencer Kimball and Peter Mattis  *  * This program is free software; you can redistribute it and/or modify  * it under the terms of the GNU General Public License as published by  * the Free Software Foundation; either version 2 of the License, or  * (at your option) any later version.  *  * This program is distributed in the hope that it will be useful,  * but WITHOUT ANY WARRANTY; without even the implied warranty of  * MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the  * GNU General Public License for more details.  *  * You should have received a copy of the GNU General Public License  * along with this program; if not, write to the Free Software  * Foundation, Inc., 59 Temple Place - Suite 330, Boston, MA 02111-1307, USA.  */
end_comment

begin_comment
comment|/*  * dbbrowser_utils.h  * 0.08  26th sept 97  by Thomas NOEL<thomas@minet.net>  */
end_comment

begin_ifndef
ifndef|#
directive|ifndef
name|__GIMP_PROC_BROWSER_H__
end_ifndef

begin_define
DECL|macro|__GIMP_PROC_BROWSER_H__
define|#
directive|define
name|__GIMP_PROC_BROWSER_H__
end_define

begin_typedef
DECL|typedef|GimpProcBrowserApplyCallback
typedef|typedef
name|void
function_decl|(
modifier|*
name|GimpProcBrowserApplyCallback
function_decl|)
parameter_list|(
specifier|const
name|gchar
modifier|*
name|proc_name
parameter_list|,
specifier|const
name|gchar
modifier|*
name|proc_blurb
parameter_list|,
specifier|const
name|gchar
modifier|*
name|proc_help
parameter_list|,
specifier|const
name|gchar
modifier|*
name|proc_author
parameter_list|,
specifier|const
name|gchar
modifier|*
name|proc_copyright
parameter_list|,
specifier|const
name|gchar
modifier|*
name|proc_date
parameter_list|,
name|GimpPDBProcType
name|proc_type
parameter_list|,
name|gint
name|n_params
parameter_list|,
name|gint
name|n_return_vals
parameter_list|,
specifier|const
name|GimpParamDef
modifier|*
name|params
parameter_list|,
specifier|const
name|GimpParamDef
modifier|*
name|return_vals
parameter_list|,
name|gpointer
name|user_data
parameter_list|)
function_decl|;
end_typedef

begin_function_decl
name|GtkWidget
modifier|*
name|gimp_proc_browser_dialog_new
parameter_list|(
name|gboolean
name|scheme_names
parameter_list|,
name|GimpProcBrowserApplyCallback
name|apply_callback
parameter_list|,
name|gpointer
name|user_data
parameter_list|)
function_decl|;
end_function_decl

begin_endif
endif|#
directive|endif
end_endif

begin_comment
comment|/* __GIMP_PROC_BROWSER_H__ */
end_comment

end_unit

