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
file|"imap_rectangle.h"
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

begin_function_decl
specifier|static
name|CmdExecuteValue_t
name|select_region_command_execute
parameter_list|(
name|Command_t
modifier|*
name|parent
parameter_list|)
function_decl|;
end_function_decl

begin_decl_stmt
DECL|variable|select_region_command_class
specifier|static
name|CommandClass_t
name|select_region_command_class
init|=
block|{
name|NULL
block|,
comment|/* select_region_command_destruct, */
name|select_region_command_execute
block|,
name|NULL
block|,
comment|/* select_region_command_undo */
name|NULL
comment|/* select_region_command_redo */
block|}
decl_stmt|;
end_decl_stmt

begin_typedef
DECL|struct|__anon295b68400108
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
DECL|member|list
name|ObjectList_t
modifier|*
name|list
decl_stmt|;
DECL|member|x
name|gint
name|x
decl_stmt|;
DECL|member|y
name|gint
name|y
decl_stmt|;
DECL|member|obj
name|Object_t
modifier|*
name|obj
decl_stmt|;
DECL|member|unselect_command
name|Command_t
modifier|*
name|unselect_command
decl_stmt|;
DECL|typedef|SelectRegionCommand_t
block|}
name|SelectRegionCommand_t
typedef|;
end_typedef

begin_function
name|Command_t
modifier|*
DECL|function|select_region_command_new (GtkWidget * widget,ObjectList_t * list,gint x,gint y)
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
block|{
name|SelectRegionCommand_t
modifier|*
name|command
init|=
name|g_new
argument_list|(
name|SelectRegionCommand_t
argument_list|,
literal|1
argument_list|)
decl_stmt|;
name|Command_t
modifier|*
name|sub_command
decl_stmt|;
name|command
operator|->
name|widget
operator|=
name|widget
expr_stmt|;
name|command
operator|->
name|list
operator|=
name|list
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
operator|(
name|void
operator|)
name|command_init
argument_list|(
operator|&
name|command
operator|->
name|parent
argument_list|,
name|_
argument_list|(
literal|"Select Region"
argument_list|)
argument_list|,
operator|&
name|select_region_command_class
argument_list|)
expr_stmt|;
name|sub_command
operator|=
name|unselect_all_command_new
argument_list|(
name|list
argument_list|,
name|NULL
argument_list|)
expr_stmt|;
name|command_add_subcommand
argument_list|(
operator|&
name|command
operator|->
name|parent
argument_list|,
name|sub_command
argument_list|)
expr_stmt|;
name|command
operator|->
name|unselect_command
operator|=
name|sub_command
expr_stmt|;
return|return
operator|&
name|command
operator|->
name|parent
return|;
block|}
end_function

begin_function
specifier|static
name|void
DECL|function|select_one_object (Object_t * obj,gpointer data)
name|select_one_object
parameter_list|(
name|Object_t
modifier|*
name|obj
parameter_list|,
name|gpointer
name|data
parameter_list|)
block|{
name|SelectRegionCommand_t
modifier|*
name|command
init|=
operator|(
name|SelectRegionCommand_t
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
name|select_command_new
argument_list|(
name|obj
argument_list|)
argument_list|)
expr_stmt|;
block|}
end_function

begin_function
specifier|static
name|void
DECL|function|select_motion (GtkWidget * widget,GdkEventMotion * event,gpointer data)
name|select_motion
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
name|SelectRegionCommand_t
modifier|*
name|command
init|=
operator|(
name|SelectRegionCommand_t
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
name|Rectangle_t
modifier|*
name|rectangle
init|=
name|ObjectToRectangle
argument_list|(
name|obj
argument_list|)
decl_stmt|;
name|gint
name|x
init|=
name|get_real_coord
argument_list|(
operator|(
name|gint
operator|)
name|event
operator|->
name|x
argument_list|)
decl_stmt|;
name|gint
name|y
init|=
name|get_real_coord
argument_list|(
operator|(
name|gint
operator|)
name|event
operator|->
name|y
argument_list|)
decl_stmt|;
name|object_draw
argument_list|(
name|obj
argument_list|,
name|widget
operator|->
name|window
argument_list|)
expr_stmt|;
name|rectangle
operator|->
name|width
operator|=
name|x
operator|-
name|rectangle
operator|->
name|x
expr_stmt|;
name|rectangle
operator|->
name|height
operator|=
name|y
operator|-
name|rectangle
operator|->
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
block|}
end_function

begin_function
specifier|static
name|void
DECL|function|select_release (GtkWidget * widget,GdkEventButton * event,gpointer data)
name|select_release
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
name|SelectRegionCommand_t
modifier|*
name|command
init|=
operator|(
name|SelectRegionCommand_t
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
name|Rectangle_t
modifier|*
name|rectangle
init|=
name|ObjectToRectangle
argument_list|(
name|obj
argument_list|)
decl_stmt|;
name|gpointer
name|id
decl_stmt|;
name|gint
name|count
decl_stmt|;
name|g_signal_handlers_disconnect_by_func
argument_list|(
name|G_OBJECT
argument_list|(
name|widget
argument_list|)
argument_list|,
name|select_motion
argument_list|,
name|data
argument_list|)
expr_stmt|;
name|g_signal_handlers_disconnect_by_func
argument_list|(
name|G_OBJECT
argument_list|(
name|widget
argument_list|)
argument_list|,
name|select_release
argument_list|,
name|data
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
name|normal_gc
argument_list|,
name|GDK_COPY
argument_list|)
expr_stmt|;
name|id
operator|=
name|object_list_add_select_cb
argument_list|(
name|command
operator|->
name|list
argument_list|,
name|select_one_object
argument_list|,
name|command
argument_list|)
expr_stmt|;
name|count
operator|=
name|object_list_select_region
argument_list|(
name|command
operator|->
name|list
argument_list|,
name|rectangle
operator|->
name|x
argument_list|,
name|rectangle
operator|->
name|y
argument_list|,
name|rectangle
operator|->
name|width
argument_list|,
name|rectangle
operator|->
name|height
argument_list|)
expr_stmt|;
name|object_list_remove_select_cb
argument_list|(
name|command
operator|->
name|list
argument_list|,
name|id
argument_list|)
expr_stmt|;
if|if
condition|(
name|count
condition|)
block|{
name|command_list_add
argument_list|(
operator|&
name|command
operator|->
name|parent
argument_list|)
expr_stmt|;
block|}
else|else
block|{
comment|/* Nothing selected */
if|if
condition|(
name|command
operator|->
name|unselect_command
operator|->
name|sub_commands
condition|)
name|command_list_add
argument_list|(
operator|&
name|command
operator|->
name|parent
argument_list|)
expr_stmt|;
block|}
name|object_unref
argument_list|(
name|obj
argument_list|)
expr_stmt|;
block|}
end_function

begin_function
specifier|static
name|CmdExecuteValue_t
DECL|function|select_region_command_execute (Command_t * parent)
name|select_region_command_execute
parameter_list|(
name|Command_t
modifier|*
name|parent
parameter_list|)
block|{
name|SelectRegionCommand_t
modifier|*
name|command
init|=
operator|(
name|SelectRegionCommand_t
operator|*
operator|)
name|parent
decl_stmt|;
name|command
operator|->
name|obj
operator|=
name|create_rectangle
argument_list|(
name|command
operator|->
name|x
argument_list|,
name|command
operator|->
name|y
argument_list|,
literal|0
argument_list|,
literal|0
argument_list|)
expr_stmt|;
name|g_signal_connect
argument_list|(
name|G_OBJECT
argument_list|(
name|command
operator|->
name|widget
argument_list|)
argument_list|,
literal|"button_release_event"
argument_list|,
name|G_CALLBACK
argument_list|(
name|select_release
argument_list|)
argument_list|,
name|command
argument_list|)
expr_stmt|;
name|g_signal_connect
argument_list|(
name|G_OBJECT
argument_list|(
name|command
operator|->
name|widget
argument_list|)
argument_list|,
literal|"motion_notify_event"
argument_list|,
name|G_CALLBACK
argument_list|(
name|select_motion
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
name|normal_gc
argument_list|,
name|GDK_XOR
argument_list|)
expr_stmt|;
return|return
name|CMD_IGNORE
return|;
block|}
end_function

end_unit

