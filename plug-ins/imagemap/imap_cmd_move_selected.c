begin_unit|revision:0.9.5;language:C;cregit-version:0.0.1
begin_comment
comment|/*  * This is a plug-in for the GIMP.  *  * Generates clickable image maps.  *  * Copyright (C) 1998-1999 Maurits Rijk  lpeek.mrijk@consunet.nl  *  * This program is free software; you can redistribute it and/or modify  * it under the terms of the GNU General Public License as published by  * the Free Software Foundation; either version 2 of the License, or  * (at your option) any later version.  *  * This program is distributed in the hope that it will be useful,  * but WITHOUT ANY WARRANTY; without even the implied warranty of  * MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the  * GNU General Public License for more details.  *  * You should have received a copy of the GNU General Public License  * along with this program; if not, write to the Free Software  * Foundation, Inc., 59 Temple Place - Suite 330, Boston, MA 02111-1307, USA.  *  */
end_comment

begin_include
include|#
directive|include
file|"imap_cmd_move_selected.h"
end_include

begin_include
include|#
directive|include
file|"libgimp/stdplugins-intl.h"
end_include

begin_include
include|#
directive|include
file|"imap_main.h"
end_include

begin_function_decl
specifier|static
name|CmdExecuteValue_t
name|move_selected_command_execute
parameter_list|(
name|Command_t
modifier|*
name|parent
parameter_list|)
function_decl|;
end_function_decl

begin_function_decl
specifier|static
name|void
name|move_selected_command_undo
parameter_list|(
name|Command_t
modifier|*
name|parent
parameter_list|)
function_decl|;
end_function_decl

begin_decl_stmt
DECL|variable|move_selected_command_class
name|CommandClass_t
name|move_selected_command_class
init|=
block|{
name|NULL
block|,
comment|/* move_selected_command_destruct */
name|move_selected_command_execute
block|,
name|move_selected_command_undo
block|,
name|NULL
comment|/* move_selected_command_redo */
block|}
decl_stmt|;
end_decl_stmt

begin_typedef
DECL|struct|__anon277129ac0108
typedef|typedef
struct|struct
block|{
DECL|member|parent
name|Command_t
name|parent
decl_stmt|;
DECL|member|list
name|ObjectList_t
modifier|*
name|list
decl_stmt|;
DECL|member|dx
name|gint
name|dx
decl_stmt|;
DECL|member|dy
name|gint
name|dy
decl_stmt|;
DECL|typedef|MoveSelectedCommand_t
block|}
name|MoveSelectedCommand_t
typedef|;
end_typedef

begin_function
name|Command_t
modifier|*
DECL|function|move_selected_command_new (ObjectList_t * list,gint dx,gint dy)
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
block|{
name|MoveSelectedCommand_t
modifier|*
name|command
init|=
name|g_new
argument_list|(
name|MoveSelectedCommand_t
argument_list|,
literal|1
argument_list|)
decl_stmt|;
name|command
operator|->
name|list
operator|=
name|list
expr_stmt|;
name|command
operator|->
name|dx
operator|=
name|dx
expr_stmt|;
name|command
operator|->
name|dy
operator|=
name|dy
expr_stmt|;
return|return
name|command_init
argument_list|(
operator|&
name|command
operator|->
name|parent
argument_list|,
name|_
argument_list|(
literal|"Move Selected Objects"
argument_list|)
argument_list|,
operator|&
name|move_selected_command_class
argument_list|)
return|;
block|}
end_function

begin_function
specifier|static
name|CmdExecuteValue_t
DECL|function|move_selected_command_execute (Command_t * parent)
name|move_selected_command_execute
parameter_list|(
name|Command_t
modifier|*
name|parent
parameter_list|)
block|{
name|MoveSelectedCommand_t
modifier|*
name|command
init|=
operator|(
name|MoveSelectedCommand_t
operator|*
operator|)
name|parent
decl_stmt|;
name|object_list_move_selected
argument_list|(
name|command
operator|->
name|list
argument_list|,
name|command
operator|->
name|dx
argument_list|,
name|command
operator|->
name|dy
argument_list|)
expr_stmt|;
ifdef|#
directive|ifdef
name|_OLD_
name|redraw_preview
argument_list|()
expr_stmt|;
comment|/* fix me! */
endif|#
directive|endif
return|return
name|CMD_APPEND
return|;
block|}
end_function

begin_function
specifier|static
name|void
DECL|function|move_selected_command_undo (Command_t * parent)
name|move_selected_command_undo
parameter_list|(
name|Command_t
modifier|*
name|parent
parameter_list|)
block|{
name|MoveSelectedCommand_t
modifier|*
name|command
init|=
operator|(
name|MoveSelectedCommand_t
operator|*
operator|)
name|parent
decl_stmt|;
name|object_list_move_selected
argument_list|(
name|command
operator|->
name|list
argument_list|,
operator|-
name|command
operator|->
name|dx
argument_list|,
operator|-
name|command
operator|->
name|dy
argument_list|)
expr_stmt|;
ifdef|#
directive|ifdef
name|_OLD_
name|redraw_preview
argument_list|()
expr_stmt|;
comment|/* fix me! */
endif|#
directive|endif
block|}
end_function

end_unit

