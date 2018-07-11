begin_unit|revision:0.9.5;language:C;cregit-version:0.0.1
begin_comment
comment|/*  * This is a plug-in for GIMP.  *  * Generates clickable image maps.  *  * Copyright (C) 1998-2005 Maurits Rijk  m.rijk@chello.nl  *  * This program is free software: you can redistribute it and/or modify  * it under the terms of the GNU General Public License as published by  * the Free Software Foundation; either version 3 of the License, or  * (at your option) any later version.  *  * This program is distributed in the hope that it will be useful,  * but WITHOUT ANY WARRANTY; without even the implied warranty of  * MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the  * GNU General Public License for more details.  *  * You should have received a copy of the GNU General Public License  * along with this program.  If not, see<https://www.gnu.org/licenses/>.  *  */
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
DECL|struct|__anon27e59cce0108
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
DECL|member|open_recent
name|GtkWidget
modifier|*
name|open_recent
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
DECL|member|arrow
name|GtkWidget
modifier|*
name|arrow
decl_stmt|;
DECL|member|fuzzy_select
name|GtkWidget
modifier|*
name|fuzzy_select
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
DECL|typedef|Menu_t
block|}
name|Menu_t
typedef|;
end_typedef

begin_function_decl
name|GtkWidget
modifier|*
name|menu_get_widget
parameter_list|(
specifier|const
name|gchar
modifier|*
name|path
parameter_list|)
function_decl|;
end_function_decl

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
name|GtkWidget
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
name|GtkWidget
modifier|*
name|make_tools
parameter_list|(
name|GtkWidget
modifier|*
name|window
parameter_list|)
function_decl|;
end_function_decl

begin_function_decl
name|GtkWidget
modifier|*
name|make_selection_toolbar
parameter_list|(
name|void
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

