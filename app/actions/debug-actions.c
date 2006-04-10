begin_unit|revision:0.9.5;language:C;cregit-version:0.0.1
begin_comment
comment|/* The GIMP -- an image manipulation program  * Copyright (C) 1995 Spencer Kimball and Peter Mattis  *  * This program is free software; you can redistribute it and/or modify  * it under the terms of the GNU General Public License as published by  * the Free Software Foundation; either version 2 of the License, or  * (at your option) any later version.  *  * This program is distributed in the hope that it will be useful,  * but WITHOUT ANY WARRANTY; without even the implied warranty of  * MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the  * GNU General Public License for more details.  *  * You should have received a copy of the GNU General Public License  * along with this program; if not, write to the Free Software  * Foundation, Inc., 59 Temple Place - Suite 330, Boston, MA 02111-1307, USA.  */
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
file|"widgets/gimpactiongroup.h"
end_include

begin_include
include|#
directive|include
file|"debug-actions.h"
end_include

begin_include
include|#
directive|include
file|"debug-commands.h"
end_include

begin_ifdef
ifdef|#
directive|ifdef
name|ENABLE_DEBUG_MENU
end_ifdef

begin_decl_stmt
DECL|variable|debug_actions
specifier|static
specifier|const
name|GimpActionEntry
name|debug_actions
index|[]
init|=
block|{
block|{
literal|"debug-menu"
block|,
name|NULL
block|,
literal|"D_ebug"
block|}
block|,
block|{
literal|"debug-mem-profile"
block|,
name|NULL
block|,
literal|"_Mem Profile"
block|,
name|NULL
block|,
name|NULL
block|,
name|G_CALLBACK
argument_list|(
name|debug_mem_profile_cmd_callback
argument_list|)
block|,
name|NULL
block|}
block|,
block|{
literal|"debug-dump-items"
block|,
name|NULL
block|,
literal|"_Dump Items"
block|,
name|NULL
block|,
name|NULL
block|,
name|G_CALLBACK
argument_list|(
name|debug_dump_menus_cmd_callback
argument_list|)
block|,
name|NULL
block|}
block|,
block|{
literal|"debug-dump-managers"
block|,
name|NULL
block|,
literal|"Dump _UI Managers"
block|,
name|NULL
block|,
name|NULL
block|,
name|G_CALLBACK
argument_list|(
name|debug_dump_managers_cmd_callback
argument_list|)
block|,
name|NULL
block|}
block|}
decl_stmt|;
end_decl_stmt

begin_endif
endif|#
directive|endif
end_endif

begin_function
name|void
DECL|function|debug_actions_setup (GimpActionGroup * group)
name|debug_actions_setup
parameter_list|(
name|GimpActionGroup
modifier|*
name|group
parameter_list|)
block|{
ifdef|#
directive|ifdef
name|ENABLE_DEBUG_MENU
name|gimp_action_group_add_actions
argument_list|(
name|group
argument_list|,
name|debug_actions
argument_list|,
name|G_N_ELEMENTS
argument_list|(
name|debug_actions
argument_list|)
argument_list|)
expr_stmt|;
endif|#
directive|endif
block|}
end_function

begin_function
name|void
DECL|function|debug_actions_update (GimpActionGroup * group,gpointer data)
name|debug_actions_update
parameter_list|(
name|GimpActionGroup
modifier|*
name|group
parameter_list|,
name|gpointer
name|data
parameter_list|)
block|{ }
end_function

end_unit

