begin_unit|revision:0.9.5;language:C;cregit-version:0.0.1
begin_comment
comment|/*  * This is a plug-in for the GIMP.  *  * Generates clickable image maps.  *  * Copyright (C) 1998-1999 Maurits Rijk  lpeek.mrijk@consunet.nl  *  * This program is free software; you can redistribute it and/or modify  * it under the terms of the GNU General Public License as published by  * the Free Software Foundation; either version 2 of the License, or  * (at your option) any later version.  *  * This program is distributed in the hope that it will be useful,  * but WITHOUT ANY WARRANTY; without even the implied warranty of  * MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the  * GNU General Public License for more details.  *  * You should have received a copy of the GNU General Public License  * along with this program; if not, write to the Free Software  * Foundation, Inc., 59 Temple Place - Suite 330, Boston, MA 02111-1307, USA.  *  */
end_comment

begin_ifndef
ifndef|#
directive|ifndef
name|_IMAP_SELECTION_H
end_ifndef

begin_define
DECL|macro|_IMAP_SELECTION_H
define|#
directive|define
name|_IMAP_SELECTION_H
end_define

begin_include
include|#
directive|include
file|"imap_command.h"
end_include

begin_include
include|#
directive|include
file|"imap_object.h"
end_include

begin_typedef
DECL|struct|__anon2c3f1a1f0108
typedef|typedef
struct|struct
block|{
DECL|member|container
name|GtkWidget
modifier|*
name|container
decl_stmt|;
DECL|member|list
name|GtkWidget
modifier|*
name|list
decl_stmt|;
DECL|member|selected_child
name|GtkWidget
modifier|*
name|selected_child
decl_stmt|;
DECL|member|arrow_up
name|GtkWidget
modifier|*
name|arrow_up
decl_stmt|;
DECL|member|arrow_down
name|GtkWidget
modifier|*
name|arrow_down
decl_stmt|;
DECL|member|remove
name|GtkWidget
modifier|*
name|remove
decl_stmt|;
DECL|member|edit
name|GtkWidget
modifier|*
name|edit
decl_stmt|;
DECL|member|object_list
name|ObjectList_t
modifier|*
name|object_list
decl_stmt|;
DECL|member|selected_row
name|gint
name|selected_row
decl_stmt|;
DECL|member|is_visible
name|gint
name|is_visible
decl_stmt|;
DECL|member|nr_rows
name|gint
name|nr_rows
decl_stmt|;
DECL|member|select_lock
name|gint
name|select_lock
decl_stmt|;
DECL|member|unselect_lock
name|gint
name|unselect_lock
decl_stmt|;
DECL|member|cmd_move_up
name|CommandFactory_t
name|cmd_move_up
decl_stmt|;
DECL|member|cmd_move_down
name|CommandFactory_t
name|cmd_move_down
decl_stmt|;
DECL|member|cmd_delete
name|CommandFactory_t
name|cmd_delete
decl_stmt|;
DECL|member|cmd_edit
name|CommandFactory_t
name|cmd_edit
decl_stmt|;
DECL|typedef|Selection_t
block|}
name|Selection_t
typedef|;
end_typedef

begin_function_decl
name|Selection_t
modifier|*
name|make_selection
parameter_list|(
name|GtkWidget
modifier|*
name|window
parameter_list|,
name|ObjectList_t
modifier|*
name|list
parameter_list|)
function_decl|;
end_function_decl

begin_function_decl
name|void
name|selection_toggle_visibility
parameter_list|(
name|Selection_t
modifier|*
name|selection
parameter_list|)
function_decl|;
end_function_decl

begin_define
DECL|macro|selection_freeze (selection)
define|#
directive|define
name|selection_freeze
parameter_list|(
name|selection
parameter_list|)
define|\
value|gtk_clist_freeze(GTK_CLIST((selection)->list))
end_define

begin_define
DECL|macro|selection_thaw (selection)
define|#
directive|define
name|selection_thaw
parameter_list|(
name|selection
parameter_list|)
define|\
value|gtk_clist_thaw(GTK_CLIST((selection)->list))
end_define

begin_define
DECL|macro|selection_set_move_up_command (selection,command)
define|#
directive|define
name|selection_set_move_up_command
parameter_list|(
name|selection
parameter_list|,
name|command
parameter_list|)
define|\
value|((selection)->cmd_move_up = (command))
end_define

begin_define
DECL|macro|selection_set_move_down_command (selection,command)
define|#
directive|define
name|selection_set_move_down_command
parameter_list|(
name|selection
parameter_list|,
name|command
parameter_list|)
define|\
value|((selection)->cmd_move_down = (command))
end_define

begin_define
DECL|macro|selection_set_delete_command (selection,command)
define|#
directive|define
name|selection_set_delete_command
parameter_list|(
name|selection
parameter_list|,
name|command
parameter_list|)
define|\
value|((selection)->cmd_delete = (command))
end_define

begin_define
DECL|macro|selection_set_edit_command (selection,command)
define|#
directive|define
name|selection_set_edit_command
parameter_list|(
name|selection
parameter_list|,
name|command
parameter_list|)
define|\
value|((selection)->cmd_edit = (command))
end_define

begin_endif
endif|#
directive|endif
end_endif

begin_comment
comment|/* _IMAP_SELECTION_H */
end_comment

end_unit

