begin_unit|revision:0.9.5;language:C;cregit-version:0.0.1
begin_comment
comment|/*  * This is a plug-in for the GIMP.  *  * Generates clickable image maps.  *  * Copyright (C) 1998-2003 Maurits Rijk  lpeek.mrijk@consunet.nl  *  * This program is free software; you can redistribute it and/or modify  * it under the terms of the GNU General Public License as published by  * the Free Software Foundation; either version 2 of the License, or  * (at your option) any later version.  *  * This program is distributed in the hope that it will be useful,  * but WITHOUT ANY WARRANTY; without even the implied warranty of  * MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the  * GNU General Public License for more details.i  *  * You should have received a copy of the GNU General Public License  * along with this program; if not, write to the Free Software  * Foundation, Inc., 59 Temple Place - Suite 330, Boston, MA 02111-1307, USA.  *  */
end_comment

begin_ifndef
ifndef|#
directive|ifndef
name|_IMAP_COMMANDS_H
end_ifndef

begin_define
DECL|macro|_IMAP_COMMANDS_H
define|#
directive|define
name|_IMAP_COMMANDS_H
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

begin_include
include|#
directive|include
file|"imap_preview.h"
end_include

begin_function_decl
name|Command_t
modifier|*
name|clear_command_new
parameter_list|(
name|ObjectList_t
modifier|*
name|list
parameter_list|)
function_decl|;
end_function_decl

begin_function_decl
name|Command_t
modifier|*
name|copy_command_new
parameter_list|(
name|ObjectList_t
modifier|*
name|list
parameter_list|)
function_decl|;
end_function_decl

begin_function_decl
name|Command_t
modifier|*
name|copy_object_command_new
parameter_list|(
name|Object_t
modifier|*
name|obj
parameter_list|)
function_decl|;
end_function_decl

begin_function_decl
name|Command_t
modifier|*
name|create_command_new
parameter_list|(
name|ObjectList_t
modifier|*
name|list
parameter_list|,
name|Object_t
modifier|*
name|obj
parameter_list|)
function_decl|;
end_function_decl

begin_function_decl
name|Command_t
modifier|*
name|cut_command_new
parameter_list|(
name|ObjectList_t
modifier|*
name|list
parameter_list|)
function_decl|;
end_function_decl

begin_function_decl
name|Command_t
modifier|*
name|cut_object_command_new
parameter_list|(
name|Object_t
modifier|*
name|obj
parameter_list|)
function_decl|;
end_function_decl

begin_function_decl
name|Command_t
modifier|*
name|delete_command_new
parameter_list|(
name|ObjectList_t
modifier|*
name|list
parameter_list|,
name|Object_t
modifier|*
name|obj
parameter_list|)
function_decl|;
end_function_decl

begin_function_decl
name|Command_t
modifier|*
name|delete_point_command_new
parameter_list|(
name|Object_t
modifier|*
name|obj
parameter_list|,
name|GdkPoint
modifier|*
name|point
parameter_list|)
function_decl|;
end_function_decl

begin_function_decl
name|Command_t
modifier|*
name|edit_object_command_new
parameter_list|(
name|Object_t
modifier|*
name|obj
parameter_list|)
function_decl|;
end_function_decl

begin_function_decl
name|Command_t
modifier|*
name|gimp_guides_command_new
parameter_list|(
name|ObjectList_t
modifier|*
name|list
parameter_list|,
name|GimpDrawable
modifier|*
name|_drawable
parameter_list|)
function_decl|;
end_function_decl

begin_function_decl
name|Command_t
modifier|*
name|guides_command_new
parameter_list|(
name|ObjectList_t
modifier|*
name|list
parameter_list|)
function_decl|;
end_function_decl

begin_function_decl
name|Command_t
modifier|*
name|insert_point_command_new
parameter_list|(
name|Object_t
modifier|*
name|obj
parameter_list|,
name|gint
name|x
parameter_list|,
name|gint
name|y
parameter_list|,
name|gint
name|edge
parameter_list|)
function_decl|;
end_function_decl

begin_function_decl
name|Command_t
modifier|*
name|move_down_command_new
parameter_list|(
name|ObjectList_t
modifier|*
name|list
parameter_list|)
function_decl|;
end_function_decl

begin_function_decl
name|Command_t
modifier|*
name|move_command_new
parameter_list|(
name|Preview_t
modifier|*
name|preview
parameter_list|,
name|Object_t
modifier|*
name|obj
parameter_list|,
name|gint
name|x
parameter_list|,
name|gint
name|y
parameter_list|)
function_decl|;
end_function_decl

begin_function_decl
name|Command_t
modifier|*
name|move_sash_command_new
parameter_list|(
name|GtkWidget
modifier|*
name|widget
parameter_list|,
name|Object_t
modifier|*
name|obj
parameter_list|,
name|gint
name|x
parameter_list|,
name|gint
name|y
parameter_list|,
name|MoveSashFunc_t
name|sash_func
parameter_list|)
function_decl|;
end_function_decl

begin_function_decl
name|Command_t
modifier|*
name|move_selected_command_new
parameter_list|(
name|ObjectList_t
modifier|*
name|list
parameter_list|,
name|gint
name|dx
parameter_list|,
name|gint
name|dy
parameter_list|)
function_decl|;
end_function_decl

begin_function_decl
name|Command_t
modifier|*
name|move_to_front_command_new
parameter_list|(
name|ObjectList_t
modifier|*
name|list
parameter_list|)
function_decl|;
end_function_decl

begin_function_decl
name|Command_t
modifier|*
name|move_up_command_new
parameter_list|(
name|ObjectList_t
modifier|*
name|list
parameter_list|)
function_decl|;
end_function_decl

begin_function_decl
name|Command_t
modifier|*
name|object_down_command_new
parameter_list|(
name|ObjectList_t
modifier|*
name|list
parameter_list|,
name|Object_t
modifier|*
name|obj
parameter_list|)
function_decl|;
end_function_decl

begin_function_decl
name|Command_t
modifier|*
name|object_move_command_new
parameter_list|(
name|Object_t
modifier|*
name|obj
parameter_list|,
name|gint
name|x
parameter_list|,
name|gint
name|y
parameter_list|)
function_decl|;
end_function_decl

begin_function_decl
name|Command_t
modifier|*
name|object_up_command_new
parameter_list|(
name|ObjectList_t
modifier|*
name|list
parameter_list|,
name|Object_t
modifier|*
name|obj
parameter_list|)
function_decl|;
end_function_decl

begin_function_decl
name|Command_t
modifier|*
name|paste_command_new
parameter_list|(
name|ObjectList_t
modifier|*
name|list
parameter_list|)
function_decl|;
end_function_decl

begin_function_decl
name|Command_t
modifier|*
name|select_all_command_new
parameter_list|(
name|ObjectList_t
modifier|*
name|list
parameter_list|)
function_decl|;
end_function_decl

begin_function_decl
name|Command_t
modifier|*
name|select_command_new
parameter_list|(
name|Object_t
modifier|*
name|obj
parameter_list|)
function_decl|;
end_function_decl

begin_function_decl
name|Command_t
modifier|*
name|select_next_command_new
parameter_list|(
name|ObjectList_t
modifier|*
name|list
parameter_list|)
function_decl|;
end_function_decl

begin_function_decl
name|Command_t
modifier|*
name|select_prev_command_new
parameter_list|(
name|ObjectList_t
modifier|*
name|list
parameter_list|)
function_decl|;
end_function_decl

begin_function_decl
name|Command_t
modifier|*
name|select_region_command_new
parameter_list|(
name|GtkWidget
modifier|*
name|widget
parameter_list|,
name|ObjectList_t
modifier|*
name|list
parameter_list|,
name|gint
name|x
parameter_list|,
name|gint
name|y
parameter_list|)
function_decl|;
end_function_decl

begin_function_decl
name|Command_t
modifier|*
name|send_to_back_command_new
parameter_list|(
name|ObjectList_t
modifier|*
name|list
parameter_list|)
function_decl|;
end_function_decl

begin_function_decl
name|Command_t
modifier|*
name|unselect_all_command_new
parameter_list|(
name|ObjectList_t
modifier|*
name|list
parameter_list|,
name|Object_t
modifier|*
name|exception
parameter_list|)
function_decl|;
end_function_decl

begin_function_decl
name|Command_t
modifier|*
name|unselect_command_new
parameter_list|(
name|Object_t
modifier|*
name|obj
parameter_list|)
function_decl|;
end_function_decl

begin_endif
endif|#
directive|endif
end_endif

begin_comment
comment|/* _IMAP_COMMANDS_H */
end_comment

end_unit

