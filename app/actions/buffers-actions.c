begin_unit|revision:0.9.5;language:C;cregit-version:0.0.1
begin_comment
comment|/* GIMP - The GNU Image Manipulation Program  * Copyright (C) 1995 Spencer Kimball and Peter Mattis  *  * This program is free software; you can redistribute it and/or modify  * it under the terms of the GNU General Public License as published by  * the Free Software Foundation; either version 2 of the License, or  * (at your option) any later version.  *  * This program is distributed in the hope that it will be useful,  * but WITHOUT ANY WARRANTY; without even the implied warranty of  * MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the  * GNU General Public License for more details.  *  * You should have received a copy of the GNU General Public License  * along with this program; if not, write to the Free Software  * Foundation, Inc., 59 Temple Place - Suite 330, Boston, MA 02111-1307, USA.  */
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
file|"libgimpwidgets/gimpwidgets.h"
end_include

begin_include
include|#
directive|include
file|"actions-types.h"
end_include

begin_include
include|#
directive|include
file|"core/gimpcontext.h"
end_include

begin_include
include|#
directive|include
file|"widgets/gimpactiongroup.h"
end_include

begin_include
include|#
directive|include
file|"widgets/gimphelp-ids.h"
end_include

begin_include
include|#
directive|include
file|"actions.h"
end_include

begin_include
include|#
directive|include
file|"buffers-actions.h"
end_include

begin_include
include|#
directive|include
file|"buffers-commands.h"
end_include

begin_include
include|#
directive|include
file|"gimp-intl.h"
end_include

begin_decl_stmt
DECL|variable|buffers_actions
specifier|static
specifier|const
name|GimpActionEntry
name|buffers_actions
index|[]
init|=
block|{
block|{
literal|"buffers-popup"
block|,
name|GIMP_STOCK_BUFFER
block|,
name|NC_
argument_list|(
literal|"buffers-action"
argument_list|,
literal|"Buffers Menu"
argument_list|)
block|,
name|NULL
block|,
name|NULL
block|,
name|NULL
block|,
name|GIMP_HELP_BUFFER_DIALOG
block|}
block|,
block|{
literal|"buffers-paste"
block|,
name|GTK_STOCK_PASTE
block|,
name|NC_
argument_list|(
literal|"buffers-action"
argument_list|,
literal|"_Paste Buffer"
argument_list|)
block|,
literal|""
block|,
name|N_
argument_list|(
literal|"Paste the selected buffer"
argument_list|)
block|,
name|G_CALLBACK
argument_list|(
name|buffers_paste_cmd_callback
argument_list|)
block|,
name|GIMP_HELP_BUFFER_PASTE
block|}
block|,
block|{
literal|"buffers-paste-into"
block|,
name|GIMP_STOCK_PASTE_INTO
block|,
name|NC_
argument_list|(
literal|"buffers-action"
argument_list|,
literal|"Paste Buffer _Into"
argument_list|)
block|,
name|NULL
block|,
name|N_
argument_list|(
literal|"Paste the selected buffer into the selection"
argument_list|)
block|,
name|G_CALLBACK
argument_list|(
name|buffers_paste_into_cmd_callback
argument_list|)
block|,
name|GIMP_HELP_BUFFER_PASTE_INTO
block|}
block|,
block|{
literal|"buffers-paste-as-new"
block|,
name|GIMP_STOCK_PASTE_AS_NEW
block|,
name|NC_
argument_list|(
literal|"buffers-action"
argument_list|,
literal|"Paste Buffer as _New"
argument_list|)
block|,
name|NULL
block|,
name|N_
argument_list|(
literal|"Paste the selected buffer as new image"
argument_list|)
block|,
name|G_CALLBACK
argument_list|(
name|buffers_paste_as_new_cmd_callback
argument_list|)
block|,
name|GIMP_HELP_BUFFER_PASTE_AS_NEW
block|}
block|,
block|{
literal|"buffers-delete"
block|,
name|GTK_STOCK_DELETE
block|,
name|NC_
argument_list|(
literal|"buffers-action"
argument_list|,
literal|"_Delete Buffer"
argument_list|)
block|,
literal|""
block|,
name|N_
argument_list|(
literal|"Delete the selected buffer"
argument_list|)
block|,
name|G_CALLBACK
argument_list|(
name|buffers_delete_cmd_callback
argument_list|)
block|,
name|GIMP_HELP_BUFFER_DELETE
block|}
block|}
decl_stmt|;
end_decl_stmt

begin_function
name|void
DECL|function|buffers_actions_setup (GimpActionGroup * group)
name|buffers_actions_setup
parameter_list|(
name|GimpActionGroup
modifier|*
name|group
parameter_list|)
block|{
name|gimp_action_group_add_actions
argument_list|(
name|group
argument_list|,
literal|"buffers-action"
argument_list|,
name|buffers_actions
argument_list|,
name|G_N_ELEMENTS
argument_list|(
name|buffers_actions
argument_list|)
argument_list|)
expr_stmt|;
block|}
end_function

begin_function
name|void
DECL|function|buffers_actions_update (GimpActionGroup * group,gpointer data)
name|buffers_actions_update
parameter_list|(
name|GimpActionGroup
modifier|*
name|group
parameter_list|,
name|gpointer
name|data
parameter_list|)
block|{
name|GimpContext
modifier|*
name|context
init|=
name|action_data_get_context
argument_list|(
name|data
argument_list|)
decl_stmt|;
name|GimpBuffer
modifier|*
name|buffer
init|=
name|NULL
decl_stmt|;
if|if
condition|(
name|context
condition|)
name|buffer
operator|=
name|gimp_context_get_buffer
argument_list|(
name|context
argument_list|)
expr_stmt|;
DECL|macro|SET_SENSITIVE (action,condition)
define|#
directive|define
name|SET_SENSITIVE
parameter_list|(
name|action
parameter_list|,
name|condition
parameter_list|)
define|\
value|gimp_action_group_set_action_sensitive (group, action, (condition) != 0)
name|SET_SENSITIVE
argument_list|(
literal|"buffers-paste"
argument_list|,
name|buffer
argument_list|)
expr_stmt|;
name|SET_SENSITIVE
argument_list|(
literal|"buffers-paste-into"
argument_list|,
name|buffer
argument_list|)
expr_stmt|;
name|SET_SENSITIVE
argument_list|(
literal|"buffers-paste-as-new"
argument_list|,
name|buffer
argument_list|)
expr_stmt|;
name|SET_SENSITIVE
argument_list|(
literal|"buffers-delete"
argument_list|,
name|buffer
argument_list|)
expr_stmt|;
undef|#
directive|undef
name|SET_SENSITIVE
block|}
end_function

end_unit

