begin_unit|revision:0.9.5;language:C;cregit-version:0.0.1
begin_comment
comment|/* The GIMP -- an image manipulation program  * Copyright (C) 1995 Spencer Kimball and Peter Mattis  *  * This program is free software; you can redistribute it and/or modify  * it under the terms of the GNU General Public License as published by  * the Free Software Foundation; either version 2 of the License, or  * (at your option) any later version.  *  * This program is distributed in the hope that it will be useful,  * but WITHOUT ANY WARRANTY; without even the implied warranty of  * MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the  * GNU General Public License for more details.  *  * You should have received a copy of the GNU General Public License  * along with this program; if not, write to the Free Software  * Foundation, Inc., 59 Temple Place - Suite 330, Boston, MA 02111-1307, USA.  */
end_comment

begin_comment
comment|/*     dbbrowser.h    0.08  26th sept 97  by Thomas NOEL<thomas@minet.net>  */
end_comment

begin_include
include|#
directive|include
file|"gtk/gtk.h"
end_include

begin_include
include|#
directive|include
file|"libgimp/gimp.h"
end_include

begin_function_decl
name|GtkWidget
modifier|*
name|gimp_db_browser
parameter_list|(
name|void
function_decl|(
modifier|*
name|apply_callback
function_decl|)
parameter_list|(
name|gchar
modifier|*
name|selected_proc_name
parameter_list|,
name|gchar
modifier|*
name|selected_scheme_proc_name
parameter_list|,
name|gchar
modifier|*
name|selected_proc_blurb
parameter_list|,
name|gchar
modifier|*
name|selected_proc_help
parameter_list|,
name|gchar
modifier|*
name|selected_proc_author
parameter_list|,
name|gchar
modifier|*
name|selected_proc_copyright
parameter_list|,
name|gchar
modifier|*
name|selected_proc_date
parameter_list|,
name|int
name|selected_proc_type
parameter_list|,
name|int
name|selected_nparams
parameter_list|,
name|int
name|selected_nreturn_vals
parameter_list|,
name|GParamDef
modifier|*
name|selected_params
parameter_list|,
name|GParamDef
modifier|*
name|selected_return_vals
parameter_list|)
parameter_list|)
function_decl|;
end_function_decl

end_unit

