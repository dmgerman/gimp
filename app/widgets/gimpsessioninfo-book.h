begin_unit|revision:0.9.5;language:C;cregit-version:0.0.1
begin_comment
comment|/* GIMP - The GNU Image Manipulation Program  * Copyright (C) 1995 Spencer Kimball and Peter Mattis  *  * gimpsessioninfo-book.h  * Copyright (C) 2001-2007 Michael Natterer<mitch@gimp.org>  *  * This program is free software: you can redistribute it and/or modify  * it under the terms of the GNU General Public License as published by  * the Free Software Foundation; either version 3 of the License, or  * (at your option) any later version.  *  * This program is distributed in the hope that it will be useful,  * but WITHOUT ANY WARRANTY; without even the implied warranty of  * MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the  * GNU General Public License for more details.  *  * You should have received a copy of the GNU General Public License  * along with this program.  If not, see<http://www.gnu.org/licenses/>.  */
end_comment

begin_ifndef
ifndef|#
directive|ifndef
name|__GIMP_SESSION_INFO_BOOK_H__
end_ifndef

begin_define
DECL|macro|__GIMP_SESSION_INFO_BOOK_H__
define|#
directive|define
name|__GIMP_SESSION_INFO_BOOK_H__
end_define

begin_comment
comment|/**  * Contains information about a book (a GtkNotebook of dockables) in  * the interface.  */
end_comment

begin_struct
DECL|struct|_GimpSessionInfoBook
struct|struct
name|_GimpSessionInfoBook
block|{
DECL|member|position
name|gint
name|position
decl_stmt|;
DECL|member|current_page
name|gint
name|current_page
decl_stmt|;
comment|/*  list of GimpSessionInfoDockable  */
DECL|member|dockables
name|GList
modifier|*
name|dockables
decl_stmt|;
block|}
struct|;
end_struct

begin_function_decl
name|GimpSessionInfoBook
modifier|*
name|gimp_session_info_book_new
parameter_list|(
name|void
parameter_list|)
function_decl|;
end_function_decl

begin_function_decl
name|void
name|gimp_session_info_book_free
parameter_list|(
name|GimpSessionInfoBook
modifier|*
name|info
parameter_list|)
function_decl|;
end_function_decl

begin_function_decl
name|void
name|gimp_session_info_book_serialize
parameter_list|(
name|GimpConfigWriter
modifier|*
name|writer
parameter_list|,
name|GimpSessionInfoBook
modifier|*
name|book
parameter_list|)
function_decl|;
end_function_decl

begin_function_decl
name|GTokenType
name|gimp_session_info_book_deserialize
parameter_list|(
name|GScanner
modifier|*
name|scanner
parameter_list|,
name|gint
name|scope
parameter_list|,
name|GimpSessionInfoBook
modifier|*
modifier|*
name|book
parameter_list|)
function_decl|;
end_function_decl

begin_function_decl
name|GimpSessionInfoBook
modifier|*
name|gimp_session_info_book_from_widget
parameter_list|(
name|GimpDockbook
modifier|*
name|dockbook
parameter_list|)
function_decl|;
end_function_decl

begin_function_decl
name|GimpDockbook
modifier|*
name|gimp_session_info_book_restore
parameter_list|(
name|GimpSessionInfoBook
modifier|*
name|info
parameter_list|,
name|GimpDock
modifier|*
name|dock
parameter_list|)
function_decl|;
end_function_decl

begin_endif
endif|#
directive|endif
end_endif

begin_comment
comment|/* __GIMP_SESSION_INFO_BOOK_H__ */
end_comment

end_unit

