begin_unit|revision:0.9.5;language:C;cregit-version:0.0.1
begin_comment
comment|/*  * This is a plug-in for the GIMP.  *  * Generates clickable image maps.  *  * Copyright (C) 1998-1999 Maurits Rijk  lpeek.mrijk@consunet.nl  *  * This program is free software; you can redistribute it and/or modify  * it under the terms of the GNU General Public License as published by  * the Free Software Foundation; either version 2 of the License, or  * (at your option) any later version.  *  * This program is distributed in the hope that it will be useful,  * but WITHOUT ANY WARRANTY; without even the implied warranty of  * MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the  * GNU General Public License for more details.  *  * You should have received a copy of the GNU General Public License  * along with this program; if not, write to the Free Software  * Foundation, Inc., 59 Temple Place - Suite 330, Boston, MA 02111-1307, USA.  *  */
end_comment

begin_include
include|#
directive|include
file|"imap_cmd_clear.h"
end_include

begin_include
include|#
directive|include
file|"imap_cmd_delete.h"
end_include

begin_include
include|#
directive|include
file|"imap_main.h"
end_include

begin_function_decl
specifier|static
name|gboolean
name|clear_command_execute
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
name|clear_command_undo
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
name|clear_command_redo
parameter_list|(
name|Command_t
modifier|*
name|parent
parameter_list|)
function_decl|;
end_function_decl

begin_decl_stmt
DECL|variable|clear_command_class
specifier|static
name|CommandClass_t
name|clear_command_class
init|=
block|{
name|NULL
block|,
comment|/* clear_command_destruct */
name|clear_command_execute
block|,
name|clear_command_undo
block|,
name|clear_command_redo
block|}
decl_stmt|;
end_decl_stmt

begin_typedef
DECL|struct|__anon296f72a50108
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
DECL|typedef|ClearCommand_t
block|}
name|ClearCommand_t
typedef|;
end_typedef

begin_function
name|Command_t
modifier|*
DECL|function|clear_command_new (ObjectList_t * list)
name|clear_command_new
parameter_list|(
name|ObjectList_t
modifier|*
name|list
parameter_list|)
block|{
name|ClearCommand_t
modifier|*
name|command
init|=
name|g_new
argument_list|(
name|ClearCommand_t
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
return|return
name|command_init
argument_list|(
operator|&
name|command
operator|->
name|parent
argument_list|,
literal|"Clear"
argument_list|,
operator|&
name|clear_command_class
argument_list|)
return|;
block|}
end_function

begin_function
specifier|static
name|void
DECL|function|remove_one_object (Object_t * obj,gpointer data)
name|remove_one_object
parameter_list|(
name|Object_t
modifier|*
name|obj
parameter_list|,
name|gpointer
name|data
parameter_list|)
block|{
name|ClearCommand_t
modifier|*
name|command
init|=
operator|(
name|ClearCommand_t
operator|*
operator|)
name|data
decl_stmt|;
name|command_add_subcommand
argument_list|(
operator|&
name|command
operator|->
name|parent
argument_list|,
name|delete_command_new
argument_list|(
name|command
operator|->
name|list
argument_list|,
name|obj
argument_list|)
argument_list|)
expr_stmt|;
block|}
end_function

begin_function
specifier|static
name|gboolean
DECL|function|clear_command_execute (Command_t * parent)
name|clear_command_execute
parameter_list|(
name|Command_t
modifier|*
name|parent
parameter_list|)
block|{
name|ClearCommand_t
modifier|*
name|command
init|=
operator|(
name|ClearCommand_t
operator|*
operator|)
name|parent
decl_stmt|;
name|gpointer
name|id
decl_stmt|;
name|id
operator|=
name|object_list_add_remove_cb
argument_list|(
name|command
operator|->
name|list
argument_list|,
name|remove_one_object
argument_list|,
name|command
argument_list|)
expr_stmt|;
name|object_list_delete_selected
argument_list|(
name|command
operator|->
name|list
argument_list|)
expr_stmt|;
name|object_list_remove_remove_cb
argument_list|(
name|command
operator|->
name|list
argument_list|,
name|id
argument_list|)
expr_stmt|;
name|redraw_preview
argument_list|()
expr_stmt|;
comment|/* Fix me! */
return|return
name|TRUE
return|;
block|}
end_function

begin_function
specifier|static
name|void
DECL|function|clear_command_undo (Command_t * parent)
name|clear_command_undo
parameter_list|(
name|Command_t
modifier|*
name|parent
parameter_list|)
block|{
name|redraw_preview
argument_list|()
expr_stmt|;
comment|/* Fix me! */
block|}
end_function

begin_function
specifier|static
name|void
DECL|function|clear_command_redo (Command_t * parent)
name|clear_command_redo
parameter_list|(
name|Command_t
modifier|*
name|parent
parameter_list|)
block|{
name|redraw_preview
argument_list|()
expr_stmt|;
comment|/* Fix me! */
block|}
end_function

end_unit

