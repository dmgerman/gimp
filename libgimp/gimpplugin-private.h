begin_unit|revision:0.9.5;language:C;cregit-version:0.0.1
begin_comment
comment|/* LIBGIMP - The GIMP Library  * Copyright (C) 1995-2003 Peter Mattis and Spencer Kimball  *  * gimpplugin-private.h  * Copyright (C) 2019 Michael Natterer<mitch@gimp.org>  *  * This library is free software: you can redistribute it and/or  * modify it under the terms of the GNU Lesser General Public  * License as published by the Free Software Foundation; either  * version 3 of the License, or (at your option) any later version.  *  * This library is distributed in the hope that it will be useful,  * but WITHOUT ANY WARRANTY; without even the implied warranty of  * MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the GNU  * Lesser General Public License for more details.  *  * You should have received a copy of the GNU Lesser General Public  * License along with this library.  If not, see  *<https://www.gnu.org/licenses/>.  */
end_comment

begin_ifndef
ifndef|#
directive|ifndef
name|__GIMP_PLUG_IN_PRIVATE_H__
end_ifndef

begin_define
DECL|macro|__GIMP_PLUG_IN_PRIVATE_H__
define|#
directive|define
name|__GIMP_PLUG_IN_PRIVATE_H__
end_define

begin_macro
name|G_BEGIN_DECLS
end_macro

begin_typedef
DECL|typedef|GimpPlugInMenuBranch
typedef|typedef
name|struct
name|_GimpPlugInMenuBranch
name|GimpPlugInMenuBranch
typedef|;
end_typedef

begin_struct
DECL|struct|_GimpPlugInMenuBranch
struct|struct
name|_GimpPlugInMenuBranch
block|{
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

begin_struct
DECL|struct|_GimpPlugInPrivate
struct|struct
name|_GimpPlugInPrivate
block|{
DECL|member|translation_domain_name
name|gchar
modifier|*
name|translation_domain_name
decl_stmt|;
DECL|member|translation_domain_path
name|GFile
modifier|*
name|translation_domain_path
decl_stmt|;
DECL|member|help_domain_name
name|gchar
modifier|*
name|help_domain_name
decl_stmt|;
DECL|member|help_domain_uri
name|GFile
modifier|*
name|help_domain_uri
decl_stmt|;
DECL|member|menu_branches
name|GList
modifier|*
name|menu_branches
decl_stmt|;
DECL|member|temp_procedures
name|GList
modifier|*
name|temp_procedures
decl_stmt|;
DECL|member|extension_source_id
name|guint
name|extension_source_id
decl_stmt|;
block|}
struct|;
end_struct

begin_function_decl
name|void
name|_gimp_plug_in_query
parameter_list|(
name|GimpPlugIn
modifier|*
name|plug_in
parameter_list|)
function_decl|;
end_function_decl

begin_function_decl
name|void
name|_gimp_plug_in_init
parameter_list|(
name|GimpPlugIn
modifier|*
name|plug_in
parameter_list|)
function_decl|;
end_function_decl

begin_function_decl
name|void
name|_gimp_plug_in_run
parameter_list|(
name|GimpPlugIn
modifier|*
name|plug_in
parameter_list|)
function_decl|;
end_function_decl

begin_function_decl
name|void
name|_gimp_plug_in_quit
parameter_list|(
name|GimpPlugIn
modifier|*
name|plug_in
parameter_list|)
function_decl|;
end_function_decl

begin_function_decl
name|gboolean
name|_gimp_plug_in_extension_read
parameter_list|(
name|GIOChannel
modifier|*
name|channel
parameter_list|,
name|GIOCondition
name|condition
parameter_list|,
name|gpointer
name|data
parameter_list|)
function_decl|;
end_function_decl

begin_function_decl
name|void
name|_gimp_plug_in_single_message
parameter_list|(
name|GimpPlugIn
modifier|*
name|plug_in
parameter_list|)
function_decl|;
end_function_decl

begin_function_decl
name|void
name|_gimp_plug_in_process_message
parameter_list|(
name|GimpPlugIn
modifier|*
name|plug_in
parameter_list|,
name|GimpWireMessage
modifier|*
name|msg
parameter_list|)
function_decl|;
end_function_decl

begin_macro
name|G_END_DECLS
end_macro

begin_endif
endif|#
directive|endif
end_endif

begin_comment
comment|/* __GIMP_PLUG_IN_PRIVATE_H__ */
end_comment

end_unit

