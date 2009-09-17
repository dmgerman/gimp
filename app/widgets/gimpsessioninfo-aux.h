begin_unit|revision:0.9.5;language:C;cregit-version:0.0.1
begin_comment
comment|/* GIMP - The GNU Image Manipulation Program  * Copyright (C) 1995 Spencer Kimball and Peter Mattis  *  * gimpsessioninfo-aux.h  * Copyright (C) 2001-2007 Michael Natterer<mitch@gimp.org>  *  * This program is free software: you can redistribute it and/or modify  * it under the terms of the GNU General Public License as published by  * the Free Software Foundation; either version 3 of the License, or  * (at your option) any later version.  *  * This program is distributed in the hope that it will be useful,  * but WITHOUT ANY WARRANTY; without even the implied warranty of  * MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the  * GNU General Public License for more details.  *  * You should have received a copy of the GNU General Public License  * along with this program.  If not, see<http://www.gnu.org/licenses/>.  */
end_comment

begin_ifndef
ifndef|#
directive|ifndef
name|__GIMP_SESSION_INFO_AUX_H__
end_ifndef

begin_define
DECL|macro|__GIMP_SESSION_INFO_AUX_H__
define|#
directive|define
name|__GIMP_SESSION_INFO_AUX_H__
end_define

begin_comment
comment|/**  * Contains arbitrary data in the session management system, used for  * example by dockables to manage dockable-specific data.  */
end_comment

begin_struct
DECL|struct|_GimpSessionInfoAux
struct|struct
name|_GimpSessionInfoAux
block|{
DECL|member|name
name|gchar
modifier|*
name|name
decl_stmt|;
DECL|member|value
name|gchar
modifier|*
name|value
decl_stmt|;
block|}
struct|;
end_struct

begin_function_decl
name|GimpSessionInfoAux
modifier|*
name|gimp_session_info_aux_new
parameter_list|(
specifier|const
name|gchar
modifier|*
name|name
parameter_list|,
specifier|const
name|gchar
modifier|*
name|value
parameter_list|)
function_decl|;
end_function_decl

begin_function_decl
name|void
name|gimp_session_info_aux_free
parameter_list|(
name|GimpSessionInfoAux
modifier|*
name|aux
parameter_list|)
function_decl|;
end_function_decl

begin_decl_stmt
name|GList
modifier|*
name|gimp_session_info_aux_new_from_props
argument_list|(
name|GObject
operator|*
name|object
argument_list|,
operator|...
argument_list|)
name|G_GNUC_NULL_TERMINATED
decl_stmt|;
end_decl_stmt

begin_decl_stmt
name|void
name|gimp_session_info_aux_set_props
argument_list|(
name|GObject
operator|*
name|object
argument_list|,
name|GList
operator|*
name|aux
argument_list|,
operator|...
argument_list|)
name|G_GNUC_NULL_TERMINATED
decl_stmt|;
end_decl_stmt

begin_function_decl
name|void
name|gimp_session_info_aux_serialize
parameter_list|(
name|GimpConfigWriter
modifier|*
name|writer
parameter_list|,
name|GList
modifier|*
name|aux_info
parameter_list|)
function_decl|;
end_function_decl

begin_function_decl
name|GTokenType
name|gimp_session_info_aux_deserialize
parameter_list|(
name|GScanner
modifier|*
name|scanner
parameter_list|,
name|GList
modifier|*
modifier|*
name|aux_list
parameter_list|)
function_decl|;
end_function_decl

begin_function_decl
name|void
name|gimp_session_info_aux_set_list
parameter_list|(
name|GtkWidget
modifier|*
name|dialog
parameter_list|,
name|GList
modifier|*
name|aux_info
parameter_list|)
function_decl|;
end_function_decl

begin_function_decl
name|GList
modifier|*
name|gimp_session_info_aux_get_list
parameter_list|(
name|GtkWidget
modifier|*
name|dialog
parameter_list|)
function_decl|;
end_function_decl

begin_endif
endif|#
directive|endif
end_endif

begin_comment
comment|/* __GIMP_SESSION_INFO_AUX_H__ */
end_comment

end_unit

