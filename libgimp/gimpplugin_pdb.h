begin_unit|revision:0.9.5;language:C;cregit-version:0.0.1
begin_comment
comment|/* LIBGIMP - The GIMP Library  * Copyright (C) 1995-1997 Peter Mattis and Spencer Kimball  *  * gimpplugin_pdb.h  *  * This library is free software; you can redistribute it and/or  * modify it under the terms of the GNU Lesser General Public  * License as published by the Free Software Foundation; either  * version 2 of the License, or (at your option) any later version.  *   * This library is distributed in the hope that it will be useful,  * but WITHOUT ANY WARRANTY; without even the implied warranty of   * MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the GNU   * Lesser General Public License for more details.  *  * You should have received a copy of the GNU Lesser General Public  * License along with this library; if not, write to the  * Free Software Foundation, Inc., 59 Temple Place - Suite 330,  * Boston, MA 02111-1307, USA.  */
end_comment

begin_ifndef
ifndef|#
directive|ifndef
name|__GIMP_PLUG_IN_PDB_H__
end_ifndef

begin_define
DECL|macro|__GIMP_PLUG_IN_PDB_H__
define|#
directive|define
name|__GIMP_PLUG_IN_PDB_H__
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
comment|/* Initialize the progress bar with "message". If "message"  *  is NULL, the message displayed in the progress window will  *  be the name of the plug-in.  */
name|void
name|gimp_progress_init
parameter_list|(
name|gchar
modifier|*
name|message
parameter_list|)
function_decl|;
comment|/* Update the progress bar. If the progress bar has not been  *  initialized then it will be automatically initialized as if  *  "gimp_progress_init (NULL)" were called. "percentage" is a  *  value between 0 and 1.  */
name|void
name|gimp_progress_update
parameter_list|(
name|gdouble
name|percentage
parameter_list|)
function_decl|;
name|void
name|gimp_plugin_domain_register
parameter_list|(
name|gchar
modifier|*
name|domain_name
parameter_list|,
name|gchar
modifier|*
name|domain_path
parameter_list|)
function_decl|;
name|void
name|gimp_plugin_help_register
parameter_list|(
name|gchar
modifier|*
name|help_path
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
comment|/* __GIMP_PLUG_IN_PDB_H__ */
end_comment

end_unit

