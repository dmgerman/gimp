begin_unit|revision:0.9.5;language:C;cregit-version:0.0.1
begin_comment
comment|/*  * This is a plug-in for the GIMP.  *  * Generates clickable image maps.  *  * Copyright (C) 1998-1999 Maurits Rijk  lpeek.mrijk@consunet.nl  *  * This program is free software; you can redistribute it and/or modify  * it under the terms of the GNU General Public License as published by  * the Free Software Foundation; either version 2 of the License, or  * (at your option) any later version.  *  * This program is distributed in the hope that it will be useful,  * but WITHOUT ANY WARRANTY; without even the implied warranty of  * MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the  * GNU General Public License for more details.  *  * You should have received a copy of the GNU General Public License  * along with this program; if not, write to the Free Software  * Foundation, Inc., 59 Temple Place - Suite 330, Boston, MA 02111-1307, USA.  *  */
end_comment

begin_ifndef
ifndef|#
directive|ifndef
name|_IMAP_MENU_H
end_ifndef

begin_define
DECL|macro|_IMAP_MENU_H
define|#
directive|define
name|_IMAP_MENU_H
end_define

begin_include
include|#
directive|include
file|"imap_command.h"
end_include

begin_include
include|#
directive|include
file|"imap_mru.h"
end_include

begin_typedef
DECL|struct|__anon2887eea10108
typedef|typedef
struct|struct
block|{
DECL|member|file_menu
name|GtkWidget
modifier|*
name|file_menu
decl_stmt|;
DECL|member|edit_menu
name|GtkWidget
modifier|*
name|edit_menu
decl_stmt|;
DECL|member|undo
name|GtkWidget
modifier|*
name|undo
decl_stmt|;
DECL|member|redo
name|GtkWidget
modifier|*
name|redo
decl_stmt|;
DECL|member|cut
name|GtkWidget
modifier|*
name|cut
decl_stmt|;
DECL|member|copy
name|GtkWidget
modifier|*
name|copy
decl_stmt|;
DECL|member|clear
name|GtkWidget
modifier|*
name|clear
decl_stmt|;
DECL|member|edit
name|GtkWidget
modifier|*
name|edit
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
DECL|member|gray
name|GtkWidget
modifier|*
name|gray
decl_stmt|;
DECL|member|color
name|GtkWidget
modifier|*
name|color
decl_stmt|;
DECL|member|zoom
name|GtkWidget
modifier|*
name|zoom
index|[
literal|8
index|]
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
DECL|member|nr_off_mru_items
name|gint
name|nr_off_mru_items
decl_stmt|;
DECL|member|cmd_open
name|CommandFactory_t
name|cmd_open
decl_stmt|;
DECL|member|cmd_save
name|CommandFactory_t
name|cmd_save
decl_stmt|;
DECL|member|cmd_save_as
name|CommandFactory_t
name|cmd_save_as
decl_stmt|;
DECL|member|cmd_preferences
name|CommandFactory_t
name|cmd_preferences
decl_stmt|;
DECL|member|cmd_close
name|CommandFactory_t
name|cmd_close
decl_stmt|;
DECL|member|cmd_quit
name|CommandFactory_t
name|cmd_quit
decl_stmt|;
DECL|member|cmd_undo
name|CommandFactory_t
name|cmd_undo
decl_stmt|;
DECL|member|cmd_redo
name|CommandFactory_t
name|cmd_redo
decl_stmt|;
DECL|member|cmd_cut
name|CommandFactory_t
name|cmd_cut
decl_stmt|;
DECL|member|cmd_copy
name|CommandFactory_t
name|cmd_copy
decl_stmt|;
DECL|member|cmd_paste
name|CommandFactory_t
name|cmd_paste
decl_stmt|;
DECL|member|cmd_select_all
name|CommandFactory_t
name|cmd_select_all
decl_stmt|;
DECL|member|cmd_clear
name|CommandFactory_t
name|cmd_clear
decl_stmt|;
DECL|member|cmd_edit_area_info
name|CommandFactory_t
name|cmd_edit_area_info
decl_stmt|;
DECL|member|cmd_area_list
name|CommandFactory_t
name|cmd_area_list
decl_stmt|;
DECL|member|cmd_source
name|CommandFactory_t
name|cmd_source
decl_stmt|;
DECL|member|cmd_color
name|CommandFactory_t
name|cmd_color
decl_stmt|;
DECL|member|cmd_gray
name|CommandFactory_t
name|cmd_gray
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
DECL|member|cmd_about
name|CommandFactory_t
name|cmd_about
decl_stmt|;
DECL|typedef|Menu_t
block|}
name|Menu_t
typedef|;
end_typedef

begin_define
DECL|macro|menu_set_open_command (menu,command)
define|#
directive|define
name|menu_set_open_command
parameter_list|(
name|menu
parameter_list|,
name|command
parameter_list|)
define|\
value|((menu)->cmd_open = (command))
end_define

begin_define
DECL|macro|menu_set_save_command (menu,command)
define|#
directive|define
name|menu_set_save_command
parameter_list|(
name|menu
parameter_list|,
name|command
parameter_list|)
define|\
value|((menu)->cmd_save = (command))
end_define

begin_define
DECL|macro|menu_set_save_as_command (menu,command)
define|#
directive|define
name|menu_set_save_as_command
parameter_list|(
name|menu
parameter_list|,
name|command
parameter_list|)
define|\
value|((menu)->cmd_save_as = (command))
end_define

begin_define
DECL|macro|menu_set_preferences_command (menu,command)
define|#
directive|define
name|menu_set_preferences_command
parameter_list|(
name|menu
parameter_list|,
name|command
parameter_list|)
define|\
value|((menu)->cmd_preferences = (command))
end_define

begin_define
DECL|macro|menu_set_close_command (menu,command)
define|#
directive|define
name|menu_set_close_command
parameter_list|(
name|menu
parameter_list|,
name|command
parameter_list|)
define|\
value|((menu)->cmd_close = (command))
end_define

begin_define
DECL|macro|menu_set_quit_command (menu,command)
define|#
directive|define
name|menu_set_quit_command
parameter_list|(
name|menu
parameter_list|,
name|command
parameter_list|)
define|\
value|((menu)->cmd_quit = (command))
end_define

begin_define
DECL|macro|menu_set_undo_command (menu,command)
define|#
directive|define
name|menu_set_undo_command
parameter_list|(
name|menu
parameter_list|,
name|command
parameter_list|)
define|\
value|((menu)->cmd_undo = (command))
end_define

begin_define
DECL|macro|menu_set_redo_command (menu,command)
define|#
directive|define
name|menu_set_redo_command
parameter_list|(
name|menu
parameter_list|,
name|command
parameter_list|)
define|\
value|((menu)->cmd_redo = (command))
end_define

begin_define
DECL|macro|menu_set_cut_command (menu,command)
define|#
directive|define
name|menu_set_cut_command
parameter_list|(
name|menu
parameter_list|,
name|command
parameter_list|)
define|\
value|((menu)->cmd_cut = (command))
end_define

begin_define
DECL|macro|menu_set_copy_command (menu,command)
define|#
directive|define
name|menu_set_copy_command
parameter_list|(
name|menu
parameter_list|,
name|command
parameter_list|)
define|\
value|((menu)->cmd_copy = (command))
end_define

begin_define
DECL|macro|menu_set_paste_command (menu,command)
define|#
directive|define
name|menu_set_paste_command
parameter_list|(
name|menu
parameter_list|,
name|command
parameter_list|)
define|\
value|((menu)->cmd_paste = (command))
end_define

begin_define
DECL|macro|menu_set_select_all_command (menu,command)
define|#
directive|define
name|menu_set_select_all_command
parameter_list|(
name|menu
parameter_list|,
name|command
parameter_list|)
define|\
value|((menu)->cmd_select_all = (command))
end_define

begin_define
DECL|macro|menu_set_clear_command (menu,command)
define|#
directive|define
name|menu_set_clear_command
parameter_list|(
name|menu
parameter_list|,
name|command
parameter_list|)
define|\
value|((menu)->cmd_clear = (command))
end_define

begin_define
DECL|macro|menu_set_edit_erea_info_command (menu,command)
define|#
directive|define
name|menu_set_edit_erea_info_command
parameter_list|(
name|menu
parameter_list|,
name|command
parameter_list|)
define|\
value|((menu)->cmd_edit_area_info = (command))
end_define

begin_define
DECL|macro|menu_set_area_list_command (menu,command)
define|#
directive|define
name|menu_set_area_list_command
parameter_list|(
name|menu
parameter_list|,
name|command
parameter_list|)
define|\
value|((menu)->cmd_area_list = (command))
end_define

begin_define
DECL|macro|menu_set_source_command (menu,command)
define|#
directive|define
name|menu_set_source_command
parameter_list|(
name|menu
parameter_list|,
name|command
parameter_list|)
define|\
value|((menu)->cmd_source = (command))
end_define

begin_define
DECL|macro|menu_set_color_command (menu,command)
define|#
directive|define
name|menu_set_color_command
parameter_list|(
name|menu
parameter_list|,
name|command
parameter_list|)
define|\
value|((menu)->cmd_color = (command))
end_define

begin_define
DECL|macro|menu_set_gray_command (menu,command)
define|#
directive|define
name|menu_set_gray_command
parameter_list|(
name|menu
parameter_list|,
name|command
parameter_list|)
define|\
value|((menu)->cmd_gray = (command))
end_define

begin_define
DECL|macro|menu_set_zoom_in_command (menu,command)
define|#
directive|define
name|menu_set_zoom_in_command
parameter_list|(
name|menu
parameter_list|,
name|command
parameter_list|)
define|\
value|((menu)->cmd_zoom_in = (command))
end_define

begin_define
DECL|macro|menu_set_zoom_out_command (menu,command)
define|#
directive|define
name|menu_set_zoom_out_command
parameter_list|(
name|menu
parameter_list|,
name|command
parameter_list|)
define|\
value|((menu)->cmd_zoom_out = (command))
end_define

begin_define
DECL|macro|menu_set_edit_map_info_command (popup,command)
define|#
directive|define
name|menu_set_edit_map_info_command
parameter_list|(
name|popup
parameter_list|,
name|command
parameter_list|)
define|\
value|((menu)->cmd_edit_map_info = (command))
end_define

begin_define
DECL|macro|menu_set_grid_settings_command (menu,command)
define|#
directive|define
name|menu_set_grid_settings_command
parameter_list|(
name|menu
parameter_list|,
name|command
parameter_list|)
define|\
value|((menu)->cmd_grid_settings = (command))
end_define

begin_define
DECL|macro|menu_set_create_guides_command (menu,command)
define|#
directive|define
name|menu_set_create_guides_command
parameter_list|(
name|menu
parameter_list|,
name|command
parameter_list|)
define|\
value|((menu)->cmd_create_guides = (command))
end_define

begin_define
DECL|macro|menu_set_about_command (menu,command)
define|#
directive|define
name|menu_set_about_command
parameter_list|(
name|menu
parameter_list|,
name|command
parameter_list|)
define|\
value|((menu)->cmd_about = (command))
end_define

begin_function_decl
name|Menu_t
modifier|*
name|make_menu
parameter_list|(
name|GtkWidget
modifier|*
name|main_vbox
parameter_list|,
name|GtkWidget
modifier|*
name|window
parameter_list|)
function_decl|;
end_function_decl

begin_function_decl
name|void
name|menu_build_mru_items
parameter_list|(
name|MRU_t
modifier|*
name|mru
parameter_list|)
function_decl|;
end_function_decl

begin_function_decl
name|void
name|menu_set_zoom_sensitivity
parameter_list|(
name|gint
name|factor
parameter_list|)
function_decl|;
end_function_decl

begin_function_decl
name|void
name|menu_select_arrow
parameter_list|(
name|void
parameter_list|)
function_decl|;
end_function_decl

begin_function_decl
name|void
name|menu_select_rectangle
parameter_list|(
name|void
parameter_list|)
function_decl|;
end_function_decl

begin_function_decl
name|void
name|menu_select_circle
parameter_list|(
name|void
parameter_list|)
function_decl|;
end_function_decl

begin_function_decl
name|void
name|menu_select_polygon
parameter_list|(
name|void
parameter_list|)
function_decl|;
end_function_decl

begin_function_decl
name|void
name|menu_set_zoom
parameter_list|(
name|gint
name|factor
parameter_list|)
function_decl|;
end_function_decl

begin_function_decl
name|void
name|menu_check_grid
parameter_list|(
name|gboolean
name|check
parameter_list|)
function_decl|;
end_function_decl

begin_function_decl
name|void
name|menu_shapes_selected
parameter_list|(
name|gint
name|count
parameter_list|)
function_decl|;
end_function_decl

begin_endif
endif|#
directive|endif
end_endif

begin_comment
comment|/* _IMAP_MENU_H */
end_comment

end_unit

