begin_unit|revision:0.9.5;language:C;cregit-version:0.0.1
begin_comment
comment|/* GIMP - The GNU Image Manipulation Program  * Copyright (C) 1995 Spencer Kimball and Peter Mattis  *  * gimpsessioninfo-dock.h  * Copyright (C) 2001-2007 Michael Natterer<mitch@gimp.org>  *  * This program is free software: you can redistribute it and/or modify  * it under the terms of the GNU General Public License as published by  * the Free Software Foundation; either version 3 of the License, or  * (at your option) any later version.  *  * This program is distributed in the hope that it will be useful,  * but WITHOUT ANY WARRANTY; without even the implied warranty of  * MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the  * GNU General Public License for more details.  *  * You should have received a copy of the GNU General Public License  * along with this program.  If not, see<http://www.gnu.org/licenses/>.  */
end_comment

begin_ifndef
ifndef|#
directive|ifndef
name|__GIMP_SESSION_INFO_DOCK_H__
end_ifndef

begin_define
DECL|macro|__GIMP_SESSION_INFO_DOCK_H__
define|#
directive|define
name|__GIMP_SESSION_INFO_DOCK_H__
end_define

begin_comment
comment|/**  * GimpSessionInfoDock:  *  * Contains information about a dock in the interface.  */
end_comment

begin_struct
DECL|struct|_GimpSessionInfoDock
struct|struct
name|_GimpSessionInfoDock
block|{
comment|/* Type of dock, written to/read from sessionrc. E.g. 'gimp-dock' or    * 'gimp-toolbox'    */
DECL|member|dock_type
name|gchar
modifier|*
name|dock_type
decl_stmt|;
comment|/*  list of GimpSessionInfoBook  */
DECL|member|books
name|GList
modifier|*
name|books
decl_stmt|;
block|}
struct|;
end_struct

begin_function_decl
name|GimpSessionInfoDock
modifier|*
name|gimp_session_info_dock_new
parameter_list|(
specifier|const
name|gchar
modifier|*
name|dock_type
parameter_list|)
function_decl|;
end_function_decl

begin_function_decl
name|void
name|gimp_session_info_dock_free
parameter_list|(
name|GimpSessionInfoDock
modifier|*
name|dock_info
parameter_list|)
function_decl|;
end_function_decl

begin_function_decl
name|void
name|gimp_session_info_dock_serialize
parameter_list|(
name|GimpConfigWriter
modifier|*
name|writer
parameter_list|,
name|GimpSessionInfoDock
modifier|*
name|dock
parameter_list|)
function_decl|;
end_function_decl

begin_function_decl
name|GTokenType
name|gimp_session_info_dock_deserialize
parameter_list|(
name|GScanner
modifier|*
name|scanner
parameter_list|,
name|gint
name|scope
parameter_list|,
name|GimpSessionInfoDock
modifier|*
modifier|*
name|info
parameter_list|,
specifier|const
name|gchar
modifier|*
name|dock_type
parameter_list|)
function_decl|;
end_function_decl

begin_function_decl
name|GimpSessionInfoDock
modifier|*
name|gimp_session_info_dock_from_widget
parameter_list|(
name|GimpDock
modifier|*
name|dock
parameter_list|)
function_decl|;
end_function_decl

begin_function_decl
name|GimpDock
modifier|*
name|gimp_session_info_dock_restore
parameter_list|(
name|GimpSessionInfoDock
modifier|*
name|dock_info
parameter_list|,
name|GimpDialogFactory
modifier|*
name|factory
parameter_list|,
name|GdkScreen
modifier|*
name|screen
parameter_list|,
name|GimpDockContainer
modifier|*
name|dock_container
parameter_list|)
function_decl|;
end_function_decl

begin_endif
endif|#
directive|endif
end_endif

begin_comment
comment|/* __GIMP_SESSION_INFO_DOCK_H__ */
end_comment

end_unit

