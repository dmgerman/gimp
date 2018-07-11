begin_unit|revision:0.9.5;language:C;cregit-version:0.0.1
begin_comment
comment|/*  * This is a plug-in for GIMP.  *  * Generates clickable image maps.  *  * Copyright (C) 1998-2003 Maurits Rijk  lpeek.mrijk@consunet.nl  *  * This program is free software: you can redistribute it and/or modify  * it under the terms of the GNU General Public License as published by  * the Free Software Foundation; either version 3 of the License, or  * (at your option) any later version.  *  * This program is distributed in the hope that it will be useful,  * but WITHOUT ANY WARRANTY; without even the implied warranty of  * MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the  * GNU General Public License for more details.  *  * You should have received a copy of the GNU General Public License  * along with this program.  If not, see<https://www.gnu.org/licenses/>.  *  */
end_comment

begin_include
include|#
directive|include
file|"config.h"
end_include

begin_include
include|#
directive|include
file|<gtk/gtk.h>
end_include

begin_include
include|#
directive|include
file|"imap_commands.h"
end_include

begin_include
include|#
directive|include
file|"libgimp/stdplugins-intl.h"
end_include

begin_function_decl
specifier|static
name|CmdExecuteValue_t
name|move_down_command_execute
parameter_list|(
name|Command_t
modifier|*
name|parent
parameter_list|)
function_decl|;
end_function_decl

begin_decl_stmt
DECL|variable|move_down_command_class
specifier|static
name|CommandClass_t
name|move_down_command_class
init|=
block|{
name|NULL
block|,
comment|/* move_down_command_destruct */
name|move_down_command_execute
block|,
name|NULL
block|,
comment|/* move_down_command_undo */
name|NULL
comment|/* move_down_command_redo */
block|}
decl_stmt|;
end_decl_stmt

begin_typedef
DECL|struct|__anon27c517020108
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
DECL|member|add
name|gboolean
name|add
decl_stmt|;
DECL|typedef|MoveDownCommand_t
block|}
name|MoveDownCommand_t
typedef|;
end_typedef

begin_function
name|Command_t
modifier|*
DECL|function|move_down_command_new (ObjectList_t * list)
name|move_down_command_new
parameter_list|(
name|ObjectList_t
modifier|*
name|list
parameter_list|)
block|{
name|MoveDownCommand_t
modifier|*
name|command
init|=
name|g_new
argument_list|(
name|MoveDownCommand_t
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
name|add
operator|=
name|FALSE
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
literal|"Move Down"
argument_list|)
argument_list|,
operator|&
name|move_down_command_class
argument_list|)
return|;
block|}
end_function

begin_function
specifier|static
name|void
DECL|function|move_down_one_object (Object_t * obj,gpointer data)
name|move_down_one_object
parameter_list|(
name|Object_t
modifier|*
name|obj
parameter_list|,
name|gpointer
name|data
parameter_list|)
block|{
name|MoveDownCommand_t
modifier|*
name|command
init|=
operator|(
name|MoveDownCommand_t
operator|*
operator|)
name|data
decl_stmt|;
if|if
condition|(
name|command
operator|->
name|add
condition|)
block|{
name|command_add_subcommand
argument_list|(
operator|&
name|command
operator|->
name|parent
argument_list|,
name|object_down_command_new
argument_list|(
name|command
operator|->
name|list
argument_list|,
name|obj
argument_list|)
argument_list|)
expr_stmt|;
name|command
operator|->
name|add
operator|=
name|FALSE
expr_stmt|;
block|}
else|else
block|{
name|command
operator|->
name|add
operator|=
name|TRUE
expr_stmt|;
block|}
block|}
end_function

begin_function
specifier|static
name|CmdExecuteValue_t
DECL|function|move_down_command_execute (Command_t * parent)
name|move_down_command_execute
parameter_list|(
name|Command_t
modifier|*
name|parent
parameter_list|)
block|{
name|MoveDownCommand_t
modifier|*
name|command
init|=
operator|(
name|MoveDownCommand_t
operator|*
operator|)
name|parent
decl_stmt|;
name|gpointer
name|id
decl_stmt|;
name|id
operator|=
name|object_list_add_move_cb
argument_list|(
name|command
operator|->
name|list
argument_list|,
name|move_down_one_object
argument_list|,
name|command
argument_list|)
expr_stmt|;
name|object_list_move_selected_down
argument_list|(
name|command
operator|->
name|list
argument_list|)
expr_stmt|;
name|object_list_remove_move_cb
argument_list|(
name|command
operator|->
name|list
argument_list|,
name|id
argument_list|)
expr_stmt|;
return|return
name|CMD_APPEND
return|;
block|}
end_function

end_unit

