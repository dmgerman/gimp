begin_unit|revision:0.9.5;language:C;cregit-version:0.0.1
begin_comment
comment|/* The GIMP -- an image manipulation program  * Copyright (C) 1995 Spencer Kimball and Peter Mattis  *  * gimpsessioninfo.h  * Copyright (C) 2001-2003 Michael Natterer<mitch@gimp.org>  *  * This program is free software; you can redistribute it and/or modify  * it under the terms of the GNU General Public License as published by  * the Free Software Foundation; either version 2 of the License, or  * (at your option) any later version.  *  * This program is distributed in the hope that it will be useful,  * but WITHOUT ANY WARRANTY; without even the implied warranty of  * MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the  * GNU General Public License for more details.  *  * You should have received a copy of the GNU General Public License  * along with this program; if not, write to the Free Software  * Foundation, Inc., 59 Temple Place - Suite 330, Boston, MA 02111-1307, USA.  */
end_comment

begin_ifndef
ifndef|#
directive|ifndef
name|__GIMP_SESSION_INFO_H__
end_ifndef

begin_define
DECL|macro|__GIMP_SESSION_INFO_H__
define|#
directive|define
name|__GIMP_SESSION_INFO_H__
end_define

begin_struct
DECL|struct|_GimpSessionInfo
struct|struct
name|_GimpSessionInfo
block|{
DECL|member|x
name|gint
name|x
decl_stmt|;
DECL|member|y
name|gint
name|y
decl_stmt|;
DECL|member|width
name|gint
name|width
decl_stmt|;
DECL|member|height
name|gint
name|height
decl_stmt|;
DECL|member|widget
name|GtkWidget
modifier|*
name|widget
decl_stmt|;
comment|/*  only valid while restoring and saving the session  */
DECL|member|open
name|gboolean
name|open
decl_stmt|;
comment|/*  GList of gchar* of optional additional dialog specific info  */
DECL|member|aux_info
name|GList
modifier|*
name|aux_info
decl_stmt|;
comment|/*  only one of these is valid  */
DECL|member|toplevel_entry
name|GimpDialogFactoryEntry
modifier|*
name|toplevel_entry
decl_stmt|;
DECL|member|dockable_entry
name|GimpDialogFactoryEntry
modifier|*
name|dockable_entry
decl_stmt|;
DECL|member|books
name|GList
modifier|*
name|books
decl_stmt|;
comment|/*  GList of GimpSessionInfoBook  */
block|}
struct|;
end_struct

begin_struct
DECL|struct|_GimpSessionInfoBook
struct|struct
name|_GimpSessionInfoBook
block|{
DECL|member|position
name|gint
name|position
decl_stmt|;
DECL|member|dockables
name|GList
modifier|*
name|dockables
decl_stmt|;
comment|/*  GList of GimpSessionInfoDockable  */
DECL|member|widget
name|GtkWidget
modifier|*
name|widget
decl_stmt|;
comment|/*  only used while restoring the session  */
block|}
struct|;
end_struct

begin_struct
DECL|struct|_GimpSessionInfoDockable
struct|struct
name|_GimpSessionInfoDockable
block|{
DECL|member|identifier
name|gchar
modifier|*
name|identifier
decl_stmt|;
DECL|member|tab_style
name|GimpTabStyle
name|tab_style
decl_stmt|;
DECL|member|preview_size
name|gint
name|preview_size
decl_stmt|;
comment|/*  GList of gchar* of optional additional dockable specific info  */
DECL|member|aux_info
name|GList
modifier|*
name|aux_info
decl_stmt|;
block|}
struct|;
end_struct

begin_function_decl
name|void
name|gimp_session_info_free
parameter_list|(
name|GimpSessionInfo
modifier|*
name|info
parameter_list|)
function_decl|;
end_function_decl

begin_function_decl
name|void
name|gimp_session_info_book_free
parameter_list|(
name|GimpSessionInfoBook
modifier|*
name|book
parameter_list|)
function_decl|;
end_function_decl

begin_function_decl
name|void
name|gimp_session_info_dockable_free
parameter_list|(
name|GimpSessionInfoDockable
modifier|*
name|dockable
parameter_list|)
function_decl|;
end_function_decl

begin_function_decl
name|void
name|gimp_session_info_save
parameter_list|(
name|GimpSessionInfo
modifier|*
name|info
parameter_list|,
specifier|const
name|gchar
modifier|*
name|factory_name
parameter_list|,
name|GimpConfigWriter
modifier|*
name|writer
parameter_list|)
function_decl|;
end_function_decl

begin_function_decl
name|GTokenType
name|gimp_session_info_deserialize
parameter_list|(
name|GScanner
modifier|*
name|scanner
parameter_list|,
name|gint
name|old_scope
parameter_list|)
function_decl|;
end_function_decl

begin_function_decl
name|void
name|gimp_session_info_restore
parameter_list|(
name|GimpSessionInfo
modifier|*
name|info
parameter_list|,
name|GimpDialogFactory
modifier|*
name|factory
parameter_list|)
function_decl|;
end_function_decl

begin_function_decl
name|void
name|gimp_session_info_set_geometry
parameter_list|(
name|GimpSessionInfo
modifier|*
name|info
parameter_list|)
function_decl|;
end_function_decl

begin_function_decl
name|void
name|gimp_session_info_get_geometry
parameter_list|(
name|GimpSessionInfo
modifier|*
name|info
parameter_list|)
function_decl|;
end_function_decl

begin_endif
endif|#
directive|endif
end_endif

begin_comment
comment|/*  __GIMP_SESSION_INFO_H__  */
end_comment

end_unit

