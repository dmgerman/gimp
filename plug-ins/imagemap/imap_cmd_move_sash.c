begin_unit|revision:0.9.5;language:C;cregit-version:0.0.1
begin_comment
comment|/*  * This is a plug-in for the GIMP.  *  * Generates clickable image maps.  *  * Copyright (C) 1998-2003 Maurits Rijk  lpeek.mrijk@consunet.nl  *  * This program is free software; you can redistribute it and/or modify  * it under the terms of the GNU General Public License as published by  * the Free Software Foundation; either version 2 of the License, or  * (at your option) any later version.  *  * This program is distributed in the hope that it will be useful,  * but WITHOUT ANY WARRANTY; without even the implied warranty of  * MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the  * GNU General Public License for more details.  *  * You should have received a copy of the GNU General Public License  * along with this program; if not, write to the Free Software  * Foundation, Inc., 59 Temple Place - Suite 330, Boston, MA 02111-1307, USA.  *  */
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
file|"imap_main.h"
end_include

begin_include
include|#
directive|include
file|"libgimp/stdplugins-intl.h"
end_include

begin_expr_stmt
name|COMMAND_PROTO
argument_list|(
name|move_sash_command
argument_list|)
expr_stmt|;
end_expr_stmt

begin_decl_stmt
DECL|variable|move_sash_command_class
name|CommandClass_t
name|move_sash_command_class
init|=
block|{
name|move_sash_command_destruct
block|,
name|move_sash_command_execute
block|,
name|NULL
block|,
comment|/* move_sash_command_undo */
name|NULL
comment|/* move_sash_command_redo */
block|}
decl_stmt|;
end_decl_stmt

begin_typedef
DECL|struct|__anon2c2b548c0108
typedef|typedef
struct|struct
block|{
DECL|member|parent
name|Command_t
name|parent
decl_stmt|;
DECL|member|widget
name|GtkWidget
modifier|*
name|widget
decl_stmt|;
DECL|member|obj
name|Object_t
modifier|*
name|obj
decl_stmt|;
DECL|member|x
name|gint
name|x
decl_stmt|;
DECL|member|y
name|gint
name|y
decl_stmt|;
DECL|member|image_width
name|gint
name|image_width
decl_stmt|;
DECL|member|image_height
name|gint
name|image_height
decl_stmt|;
DECL|member|sash_func
name|MoveSashFunc_t
name|sash_func
decl_stmt|;
DECL|typedef|MoveSashCommand_t
block|}
name|MoveSashCommand_t
typedef|;
end_typedef

begin_function
name|Command_t
modifier|*
DECL|function|move_sash_command_new (GtkWidget * widget,Object_t * obj,gint x,gint y,MoveSashFunc_t sash_func)
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
block|{
name|MoveSashCommand_t
modifier|*
name|command
init|=
name|g_new
argument_list|(
name|MoveSashCommand_t
argument_list|,
literal|1
argument_list|)
decl_stmt|;
name|Command_t
modifier|*
name|parent
decl_stmt|;
name|command
operator|->
name|widget
operator|=
name|widget
expr_stmt|;
name|command
operator|->
name|obj
operator|=
name|object_ref
argument_list|(
name|obj
argument_list|)
expr_stmt|;
name|command
operator|->
name|x
operator|=
name|x
expr_stmt|;
name|command
operator|->
name|y
operator|=
name|y
expr_stmt|;
name|command
operator|->
name|image_width
operator|=
name|get_image_width
argument_list|()
expr_stmt|;
name|command
operator|->
name|image_height
operator|=
name|get_image_height
argument_list|()
expr_stmt|;
name|command
operator|->
name|sash_func
operator|=
name|sash_func
expr_stmt|;
name|parent
operator|=
name|command_init
argument_list|(
operator|&
name|command
operator|->
name|parent
argument_list|,
name|_
argument_list|(
literal|"Move Sash"
argument_list|)
argument_list|,
operator|&
name|move_sash_command_class
argument_list|)
expr_stmt|;
name|command_add_subcommand
argument_list|(
name|parent
argument_list|,
name|edit_object_command_new
argument_list|(
name|obj
argument_list|)
argument_list|)
expr_stmt|;
return|return
name|parent
return|;
block|}
end_function

begin_function
specifier|static
name|void
DECL|function|move_sash_command_destruct (Command_t * parent)
name|move_sash_command_destruct
parameter_list|(
name|Command_t
modifier|*
name|parent
parameter_list|)
block|{
name|MoveSashCommand_t
modifier|*
name|command
init|=
operator|(
name|MoveSashCommand_t
operator|*
operator|)
name|parent
decl_stmt|;
name|object_unref
argument_list|(
name|command
operator|->
name|obj
argument_list|)
expr_stmt|;
block|}
end_function

begin_function
specifier|static
name|void
DECL|function|sash_move (GtkWidget * widget,GdkEventMotion * event,gpointer data)
name|sash_move
parameter_list|(
name|GtkWidget
modifier|*
name|widget
parameter_list|,
name|GdkEventMotion
modifier|*
name|event
parameter_list|,
name|gpointer
name|data
parameter_list|)
block|{
name|MoveSashCommand_t
modifier|*
name|command
init|=
operator|(
name|MoveSashCommand_t
operator|*
operator|)
name|data
decl_stmt|;
name|Object_t
modifier|*
name|obj
init|=
name|command
operator|->
name|obj
decl_stmt|;
name|gint
name|x
decl_stmt|,
name|y
decl_stmt|,
name|dx
decl_stmt|,
name|dy
decl_stmt|;
name|x
operator|=
operator|(
name|gint
operator|)
name|event
operator|->
name|x
expr_stmt|;
name|y
operator|=
operator|(
name|gint
operator|)
name|event
operator|->
name|y
expr_stmt|;
if|if
condition|(
name|x
operator|<
literal|0
condition|)
name|x
operator|=
literal|0
expr_stmt|;
if|if
condition|(
name|x
operator|>
name|command
operator|->
name|image_width
condition|)
name|x
operator|=
name|command
operator|->
name|image_width
expr_stmt|;
if|if
condition|(
name|y
operator|<
literal|0
condition|)
name|y
operator|=
literal|0
expr_stmt|;
if|if
condition|(
name|y
operator|>
name|command
operator|->
name|image_height
condition|)
name|y
operator|=
name|command
operator|->
name|image_height
expr_stmt|;
name|x
operator|=
name|get_real_coord
argument_list|(
name|x
argument_list|)
expr_stmt|;
name|y
operator|=
name|get_real_coord
argument_list|(
name|y
argument_list|)
expr_stmt|;
name|dx
operator|=
name|x
operator|-
name|command
operator|->
name|x
expr_stmt|;
name|dy
operator|=
name|y
operator|-
name|command
operator|->
name|y
expr_stmt|;
name|command
operator|->
name|x
operator|=
name|x
expr_stmt|;
name|command
operator|->
name|y
operator|=
name|y
expr_stmt|;
name|object_draw
argument_list|(
name|obj
argument_list|,
name|widget
operator|->
name|window
argument_list|)
expr_stmt|;
name|command
operator|->
name|sash_func
argument_list|(
name|obj
argument_list|,
name|dx
argument_list|,
name|dy
argument_list|)
expr_stmt|;
name|object_emit_geometry_signal
argument_list|(
name|obj
argument_list|)
expr_stmt|;
name|object_draw
argument_list|(
name|obj
argument_list|,
name|widget
operator|->
name|window
argument_list|)
expr_stmt|;
block|}
end_function

begin_function
specifier|static
name|void
DECL|function|sash_end (GtkWidget * widget,GdkEventButton * event,gpointer data)
name|sash_end
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
block|{
name|MoveSashCommand_t
modifier|*
name|command
init|=
operator|(
name|MoveSashCommand_t
operator|*
operator|)
name|data
decl_stmt|;
name|Object_t
modifier|*
name|obj
init|=
name|command
operator|->
name|obj
decl_stmt|;
name|g_signal_handlers_disconnect_by_func
argument_list|(
name|widget
argument_list|,
name|sash_move
argument_list|,
name|data
argument_list|)
expr_stmt|;
name|g_signal_handlers_disconnect_by_func
argument_list|(
name|widget
argument_list|,
name|sash_end
argument_list|,
name|data
argument_list|)
expr_stmt|;
if|if
condition|(
name|obj
operator|->
name|class
operator|->
name|normalize
condition|)
name|object_normalize
argument_list|(
name|obj
argument_list|)
expr_stmt|;
name|gdk_gc_set_function
argument_list|(
name|get_preferences
argument_list|()
operator|->
name|selected_gc
argument_list|,
name|GDK_COPY
argument_list|)
expr_stmt|;
name|preview_thaw
argument_list|()
expr_stmt|;
name|show_url
argument_list|()
expr_stmt|;
block|}
end_function

begin_function
specifier|static
name|CmdExecuteValue_t
DECL|function|move_sash_command_execute (Command_t * parent)
name|move_sash_command_execute
parameter_list|(
name|Command_t
modifier|*
name|parent
parameter_list|)
block|{
name|MoveSashCommand_t
modifier|*
name|command
init|=
operator|(
name|MoveSashCommand_t
operator|*
operator|)
name|parent
decl_stmt|;
name|hide_url
argument_list|()
expr_stmt|;
name|preview_freeze
argument_list|()
expr_stmt|;
name|g_signal_connect
argument_list|(
name|command
operator|->
name|widget
argument_list|,
literal|"button_release_event"
argument_list|,
name|G_CALLBACK
argument_list|(
name|sash_end
argument_list|)
argument_list|,
name|command
argument_list|)
expr_stmt|;
name|g_signal_connect
argument_list|(
name|command
operator|->
name|widget
argument_list|,
literal|"motion_notify_event"
argument_list|,
name|G_CALLBACK
argument_list|(
name|sash_move
argument_list|)
argument_list|,
name|command
argument_list|)
expr_stmt|;
name|gdk_gc_set_function
argument_list|(
name|get_preferences
argument_list|()
operator|->
name|selected_gc
argument_list|,
name|GDK_EQUIV
argument_list|)
expr_stmt|;
return|return
name|CMD_APPEND
return|;
block|}
end_function

end_unit

