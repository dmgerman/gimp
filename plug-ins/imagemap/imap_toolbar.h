begin_unit|revision:0.9.5;language:C;cregit-version:0.0.1
begin_comment
comment|/*  * This is a plug-in for the GIMP.  *  * Generates clickable image maps.  *  * Copyright (C) 1998-1999 Maurits Rijk  lpeek.mrijk@consunet.nl  *  * This program is free software; you can redistribute it and/or modify  * it under the terms of the GNU General Public License as published by  * the Free Software Foundation; either version 2 of the License, or  * (at your option) any later version.  *  * This program is distributed in the hope that it will be useful,  * but WITHOUT ANY WARRANTY; without even the implied warranty of  * MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the  * GNU General Public License for more details.  *  * You should have received a copy of the GNU General Public License  * along with this program; if not, write to the Free Software  * Foundation, Inc., 59 Temple Place - Suite 330, Boston, MA 02111-1307, USA.  *  */
end_comment

begin_ifndef
ifndef|#
directive|ifndef
name|_IMAP_TOOLBAR_H
end_ifndef

begin_define
DECL|macro|_IMAP_TOOLBAR_H
define|#
directive|define
name|_IMAP_TOOLBAR_H
end_define

begin_include
include|#
directive|include
file|"gtk/gtk.h"
end_include

begin_include
include|#
directive|include
file|"imap_command.h"
end_include

begin_typedef
DECL|struct|__anon28ffbda80108
typedef|typedef
struct|struct
block|{
DECL|member|toolbar
name|GtkWidget
modifier|*
name|toolbar
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
DECL|member|to_front
name|GtkWidget
modifier|*
name|to_front
decl_stmt|;
DECL|member|to_back
name|GtkWidget
modifier|*
name|to_back
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
DECL|member|grid
name|GtkWidget
modifier|*
name|grid
decl_stmt|;
DECL|member|cmd_open
name|CommandFactory_t
name|cmd_open
decl_stmt|;
DECL|member|cmd_save
name|CommandFactory_t
name|cmd_save
decl_stmt|;
DECL|member|cmd_preferences
name|CommandFactory_t
name|cmd_preferences
decl_stmt|;
DECL|member|cmd_redo
name|CommandFactory_t
name|cmd_redo
decl_stmt|;
DECL|member|cmd_undo
name|CommandFactory_t
name|cmd_undo
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
DECL|member|cmd_move_to_front
name|CommandFactory_t
name|cmd_move_to_front
decl_stmt|;
DECL|member|cmd_send_to_back
name|CommandFactory_t
name|cmd_send_to_back
decl_stmt|;
DECL|member|cmd_grid
name|CommandFactory_t
name|cmd_grid
decl_stmt|;
DECL|typedef|ToolBar_t
block|}
name|ToolBar_t
typedef|;
end_typedef

begin_function_decl
name|ToolBar_t
modifier|*
name|make_toolbar
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
name|toolbar_set_zoom_sensitivity
parameter_list|(
name|ToolBar_t
modifier|*
name|toolbar
parameter_list|,
name|gint
name|factor
parameter_list|)
function_decl|;
end_function_decl

begin_function_decl
name|void
name|toolbar_set_grid
parameter_list|(
name|ToolBar_t
modifier|*
name|toolbar
parameter_list|,
name|gboolean
name|active
parameter_list|)
function_decl|;
end_function_decl

begin_function_decl
name|void
name|toolbar_shapes_selected
parameter_list|(
name|ToolBar_t
modifier|*
name|toolbar
parameter_list|,
name|gint
name|count
parameter_list|)
function_decl|;
end_function_decl

begin_define
DECL|macro|toolbar_set_open_command (toolbar,command)
define|#
directive|define
name|toolbar_set_open_command
parameter_list|(
name|toolbar
parameter_list|,
name|command
parameter_list|)
define|\
value|((toolbar)->cmd_open = (command))
end_define

begin_define
DECL|macro|toolbar_set_save_command (toolbar,command)
define|#
directive|define
name|toolbar_set_save_command
parameter_list|(
name|toolbar
parameter_list|,
name|command
parameter_list|)
define|\
value|((toolbar)->cmd_save = (command))
end_define

begin_define
DECL|macro|toolbar_set_preferences_command (toolbar,command)
define|#
directive|define
name|toolbar_set_preferences_command
parameter_list|(
name|toolbar
parameter_list|,
name|command
parameter_list|)
define|\
value|((toolbar)->cmd_preferences = (command))
end_define

begin_define
DECL|macro|toolbar_set_redo_command (toolbar,command)
define|#
directive|define
name|toolbar_set_redo_command
parameter_list|(
name|toolbar
parameter_list|,
name|command
parameter_list|)
define|\
value|((toolbar)->cmd_redo = (command))
end_define

begin_define
DECL|macro|toolbar_set_undo_command (toolbar,command)
define|#
directive|define
name|toolbar_set_undo_command
parameter_list|(
name|toolbar
parameter_list|,
name|command
parameter_list|)
define|\
value|((toolbar)->cmd_undo = (command))
end_define

begin_define
DECL|macro|toolbar_set_cut_command (toolbar,command)
define|#
directive|define
name|toolbar_set_cut_command
parameter_list|(
name|toolbar
parameter_list|,
name|command
parameter_list|)
define|\
value|((toolbar)->cmd_cut = (command))
end_define

begin_define
DECL|macro|toolbar_set_copy_command (toolbar,command)
define|#
directive|define
name|toolbar_set_copy_command
parameter_list|(
name|toolbar
parameter_list|,
name|command
parameter_list|)
define|\
value|((toolbar)->cmd_copy= (command))
end_define

begin_define
DECL|macro|toolbar_set_paste_command (toolbar,command)
define|#
directive|define
name|toolbar_set_paste_command
parameter_list|(
name|toolbar
parameter_list|,
name|command
parameter_list|)
define|\
value|((toolbar)->cmd_paste = (command))
end_define

begin_define
DECL|macro|toolbar_set_zoom_in_command (toolbar,command)
define|#
directive|define
name|toolbar_set_zoom_in_command
parameter_list|(
name|toolbar
parameter_list|,
name|command
parameter_list|)
define|\
value|((toolbar)->cmd_zoom_in = (command))
end_define

begin_define
DECL|macro|toolbar_set_zoom_out_command (toolbar,command)
define|#
directive|define
name|toolbar_set_zoom_out_command
parameter_list|(
name|toolbar
parameter_list|,
name|command
parameter_list|)
define|\
value|((toolbar)->cmd_zoom_out = (command))
end_define

begin_define
DECL|macro|toolbar_set_edit_map_info_command (toolbar,command)
define|#
directive|define
name|toolbar_set_edit_map_info_command
parameter_list|(
name|toolbar
parameter_list|,
name|command
parameter_list|)
define|\
value|((toolbar)->cmd_edit_map_info = (command))
end_define

begin_define
DECL|macro|toolbar_set_move_to_front_command (toolbar,command)
define|#
directive|define
name|toolbar_set_move_to_front_command
parameter_list|(
name|toolbar
parameter_list|,
name|command
parameter_list|)
define|\
value|((toolbar)->cmd_move_to_front = (command))
end_define

begin_define
DECL|macro|toolbar_set_send_to_back_command (toolbar,command)
define|#
directive|define
name|toolbar_set_send_to_back_command
parameter_list|(
name|toolbar
parameter_list|,
name|command
parameter_list|)
define|\
value|((toolbar)->cmd_send_to_back = (command))
end_define

begin_define
DECL|macro|toolbar_set_grid_command (toolbar,command)
define|#
directive|define
name|toolbar_set_grid_command
parameter_list|(
name|toolbar
parameter_list|,
name|command
parameter_list|)
define|\
value|((toolbar)->cmd_grid = (command))
end_define

begin_endif
endif|#
directive|endif
end_endif

begin_comment
comment|/* _IMAP_TOOLBAR_H */
end_comment

end_unit

