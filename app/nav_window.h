begin_unit|revision:0.9.5;language:C;cregit-version:0.0.1
begin_comment
comment|/* The GIMP -- an image manipulation program  * Copyright (C) 1995 Spencer Kimball and Peter Mattis  * Copyright (C) 1999 Andy Thomas alt@gimp.org  *  * This program is free software; you can redistribute it and/or modify  * it under the terms of the GNU General Public License as published by  * the Free Software Foundation; either version 2 of the License, or  * (at your option) any later version.  *  * This program is distributed in the hope that it will be useful,  * but WITHOUT ANY WARRANTY; without even the implied warranty of  * MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the  * GNU General Public License for more details.  *  * You should have received a copy of the GNU General Public License  * along with this program; if not, write to the Free Software  * Foundation, Inc., 59 Temple Place - Suite 330, Boston, MA 02111-1307, USA.  */
end_comment

begin_ifndef
ifndef|#
directive|ifndef
name|__NAV_WINDOW_H__
end_ifndef

begin_define
DECL|macro|__NAV_WINDOW_H__
define|#
directive|define
name|__NAV_WINDOW_H__
end_define

begin_function_decl
name|NavigationDialog
modifier|*
name|nav_dialog_create
parameter_list|(
name|GimpDisplay
modifier|*
name|gdisp
parameter_list|)
function_decl|;
end_function_decl

begin_function_decl
name|void
name|nav_dialog_free
parameter_list|(
name|GimpDisplay
modifier|*
name|gdisp
parameter_list|,
name|NavigationDialog
modifier|*
name|nav_dialog
parameter_list|)
function_decl|;
end_function_decl

begin_function_decl
name|void
name|nav_dialog_popup
parameter_list|(
name|NavigationDialog
modifier|*
name|nav_dialog
parameter_list|)
function_decl|;
end_function_decl

begin_function_decl
name|void
name|nav_dialog_follow_auto
parameter_list|(
name|void
parameter_list|)
function_decl|;
end_function_decl

begin_function_decl
name|void
name|nav_dialog_update_window_marker
parameter_list|(
name|NavigationDialog
modifier|*
name|nav_dialog
parameter_list|)
function_decl|;
end_function_decl

begin_function_decl
name|void
name|nav_dialog_preview_resized
parameter_list|(
name|NavigationDialog
modifier|*
name|nav_dialog
parameter_list|)
function_decl|;
end_function_decl

begin_function_decl
name|void
name|nav_popup_click_handler
parameter_list|(
name|GtkWidget
modifier|*
name|widget
parameter_list|,
name|GdkEventButton
modifier|*
name|event
parameter_list|,
name|gpointer
name|data
parameter_list|)
function_decl|;
end_function_decl

begin_endif
endif|#
directive|endif
end_endif

begin_comment
comment|/*  __NAV_WINDOW_H__  */
end_comment

end_unit

