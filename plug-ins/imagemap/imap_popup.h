begin_unit|revision:0.9.5;language:C;cregit-version:0.0.1
begin_comment
comment|/*  * This is a plug-in for the GIMP.  *  * Generates clickable image maps.  *  * Copyright (C) 1998-1999 Maurits Rijk  lpeek.mrijk@consunet.nl  *  * This program is free software; you can redistribute it and/or modify  * it under the terms of the GNU General Public License as published by  * the Free Software Foundation; either version 2 of the License, or  * (at your option) any later version.  *  * This program is distributed in the hope that it will be useful,  * but WITHOUT ANY WARRANTY; without even the implied warranty of  * MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the  * GNU General Public License for more details.  *  * You should have received a copy of the GNU General Public License  * along with this program; if not, write to the Free Software  * Foundation, Inc., 59 Temple Place - Suite 330, Boston, MA 02111-1307, USA.  *  */
end_comment

begin_ifndef
ifndef|#
directive|ifndef
name|_IMAP_POPUP_H
end_ifndef

begin_define
DECL|macro|_IMAP_POPUP_H
define|#
directive|define
name|_IMAP_POPUP_H
end_define

begin_include
include|#
directive|include
file|"imap_command.h"
end_include

begin_typedef
DECL|struct|__anon2bd5c3190108
typedef|typedef
struct|struct
block|{
DECL|member|main
name|GtkWidget
modifier|*
decl|main
decl_stmt|;
DECL|member|arrow
name|GtkWidget
modifier|*
name|arrow
decl_stmt|;
DECL|member|rectangle
name|GtkWidget
modifier|*
name|rectangle
decl_stmt|;
DECL|member|circle
name|GtkWidget
modifier|*
name|circle
decl_stmt|;
DECL|member|polygon
name|GtkWidget
modifier|*
name|polygon
decl_stmt|;
DECL|member|grid
name|GtkWidget
modifier|*
name|grid
decl_stmt|;
DECL|member|zoom_in
name|GtkWidget
modifier|*
name|zoom_in
decl_stmt|;
DECL|member|zoom_out
name|GtkWidget
modifier|*
name|zoom_out
decl_stmt|;
DECL|member|cmd_zoom_in
name|CommandFactory_t
name|cmd_zoom_in
decl_stmt|;
DECL|member|cmd_zoom_out
name|CommandFactory_t
name|cmd_zoom_out
decl_stmt|;
DECL|member|cmd_edit_map_info
name|CommandFactory_t
name|cmd_edit_map_info
decl_stmt|;
DECL|member|cmd_grid_settings
name|CommandFactory_t
name|cmd_grid_settings
decl_stmt|;
DECL|member|cmd_create_guides
name|CommandFactory_t
name|cmd_create_guides
decl_stmt|;
DECL|member|cmd_paste
name|CommandFactory_t
name|cmd_paste
decl_stmt|;
DECL|typedef|PopupMenu_t
block|}
name|PopupMenu_t
typedef|;
end_typedef

begin_define
DECL|macro|popup_set_zoom_in_command (popup,command)
define|#
directive|define
name|popup_set_zoom_in_command
parameter_list|(
name|popup
parameter_list|,
name|command
parameter_list|)
define|\
value|((popup)->cmd_zoom_in = (command))
end_define

begin_define
DECL|macro|popup_set_zoom_out_command (popup,command)
define|#
directive|define
name|popup_set_zoom_out_command
parameter_list|(
name|popup
parameter_list|,
name|command
parameter_list|)
define|\
value|((popup)->cmd_zoom_out = (command))
end_define

begin_define
DECL|macro|popup_set_edit_map_info_command (popup,command)
define|#
directive|define
name|popup_set_edit_map_info_command
parameter_list|(
name|popup
parameter_list|,
name|command
parameter_list|)
define|\
value|((popup)->cmd_edit_map_info = (command))
end_define

begin_define
DECL|macro|popup_set_grid_settings_command (popup,command)
define|#
directive|define
name|popup_set_grid_settings_command
parameter_list|(
name|popup
parameter_list|,
name|command
parameter_list|)
define|\
value|((popup)->cmd_grid_settings = (command))
end_define

begin_define
DECL|macro|popup_set_create_guides_command (popup,command)
define|#
directive|define
name|popup_set_create_guides_command
parameter_list|(
name|popup
parameter_list|,
name|command
parameter_list|)
define|\
value|((popup)->cmd_create_guides = (command))
end_define

begin_define
DECL|macro|popup_set_paste_command (popup,command)
define|#
directive|define
name|popup_set_paste_command
parameter_list|(
name|popup
parameter_list|,
name|command
parameter_list|)
define|\
value|((popup)->cmd_paste = (command))
end_define

begin_function_decl
name|PopupMenu_t
modifier|*
name|create_main_popup_menu
parameter_list|(
name|void
parameter_list|)
function_decl|;
end_function_decl

begin_function_decl
name|void
name|do_main_popup_menu
parameter_list|(
name|GdkEventButton
modifier|*
name|event
parameter_list|)
function_decl|;
end_function_decl

begin_function_decl
name|void
name|popup_set_zoom_sensitivity
parameter_list|(
name|gint
name|factor
parameter_list|)
function_decl|;
end_function_decl

begin_function_decl
name|void
name|popup_select_arrow
parameter_list|(
name|void
parameter_list|)
function_decl|;
end_function_decl

begin_function_decl
name|void
name|popup_select_rectangle
parameter_list|(
name|void
parameter_list|)
function_decl|;
end_function_decl

begin_function_decl
name|void
name|popup_select_circle
parameter_list|(
name|void
parameter_list|)
function_decl|;
end_function_decl

begin_function_decl
name|void
name|popup_select_polygon
parameter_list|(
name|void
parameter_list|)
function_decl|;
end_function_decl

begin_function_decl
name|void
name|popup_check_grid
parameter_list|(
name|gint
name|check
parameter_list|)
function_decl|;
end_function_decl

begin_endif
endif|#
directive|endif
end_endif

begin_comment
comment|/* _IMAP_POPUP_H */
end_comment

end_unit

