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
file|<string.h>
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
file|"core/gimp.h"
end_include

begin_include
include|#
directive|include
file|"core/gimpdrawable.h"
end_include

begin_include
include|#
directive|include
file|"plug-in/plug-in-proc.h"
end_include

begin_include
include|#
directive|include
file|"plug-in/plug-ins.h"
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
file|"file-commands.h"
end_include

begin_include
include|#
directive|include
file|"file-open-actions.h"
end_include

begin_include
include|#
directive|include
file|"gimp-intl.h"
end_include

begin_decl_stmt
DECL|variable|file_open_actions
specifier|static
name|GimpActionEntry
name|file_open_actions
index|[]
init|=
block|{
block|{
literal|"file-open-popup"
block|,
name|NULL
block|,
name|N_
argument_list|(
literal|"File Open Menu"
argument_list|)
block|,
name|NULL
block|,
name|NULL
block|,
name|NULL
block|,
name|GIMP_HELP_FILE_OPEN
block|}
block|,
block|{
literal|"file-open-automatic"
block|,
name|NULL
block|,
name|N_
argument_list|(
literal|"Automatic"
argument_list|)
block|,
name|NULL
block|,
name|NULL
block|,
name|G_CALLBACK
argument_list|(
name|file_type_cmd_callback
argument_list|)
block|,
name|GIMP_HELP_FILE_OPEN_BY_EXTENSION
block|}
block|}
decl_stmt|;
end_decl_stmt

begin_function
name|void
DECL|function|file_open_actions_setup (GimpActionGroup * group)
name|file_open_actions_setup
parameter_list|(
name|GimpActionGroup
modifier|*
name|group
parameter_list|)
block|{
name|GSList
modifier|*
name|list
decl_stmt|;
name|gimp_action_group_add_actions
argument_list|(
name|group
argument_list|,
name|file_open_actions
argument_list|,
name|G_N_ELEMENTS
argument_list|(
name|file_open_actions
argument_list|)
argument_list|)
expr_stmt|;
for|for
control|(
name|list
operator|=
name|group
operator|->
name|gimp
operator|->
name|load_procs
init|;
name|list
condition|;
name|list
operator|=
name|g_slist_next
argument_list|(
name|list
argument_list|)
control|)
block|{
name|PlugInProcDef
modifier|*
name|file_proc
init|=
name|list
operator|->
name|data
decl_stmt|;
specifier|const
name|gchar
modifier|*
name|locale_domain
init|=
name|NULL
decl_stmt|;
specifier|const
name|gchar
modifier|*
name|stock_id
init|=
name|NULL
decl_stmt|;
name|gchar
modifier|*
name|help_id
decl_stmt|;
name|GimpActionEntry
name|entry
decl_stmt|;
name|gboolean
name|is_xcf
decl_stmt|;
name|GtkAction
modifier|*
name|action
decl_stmt|;
if|if
condition|(
operator|!
name|file_proc
operator|->
name|menu_path
condition|)
continue|continue;
name|is_xcf
operator|=
operator|(
name|strcmp
argument_list|(
name|file_proc
operator|->
name|db_info
operator|.
name|name
argument_list|,
literal|"gimp_xcf_load"
argument_list|)
operator|==
literal|0
operator|)
expr_stmt|;
if|if
condition|(
name|is_xcf
condition|)
block|{
name|stock_id
operator|=
name|GIMP_STOCK_WILBER
expr_stmt|;
name|help_id
operator|=
name|g_strdup
argument_list|(
name|GIMP_HELP_FILE_OPEN_XCF
argument_list|)
expr_stmt|;
block|}
else|else
block|{
specifier|const
name|gchar
modifier|*
name|progname
decl_stmt|;
specifier|const
name|gchar
modifier|*
name|help_domain
decl_stmt|;
name|progname
operator|=
name|plug_in_proc_def_get_progname
argument_list|(
name|file_proc
argument_list|)
expr_stmt|;
name|locale_domain
operator|=
name|plug_ins_locale_domain
argument_list|(
name|group
operator|->
name|gimp
argument_list|,
name|progname
argument_list|,
name|NULL
argument_list|)
expr_stmt|;
name|help_domain
operator|=
name|plug_ins_help_domain
argument_list|(
name|group
operator|->
name|gimp
argument_list|,
name|progname
argument_list|,
name|NULL
argument_list|)
expr_stmt|;
name|help_id
operator|=
name|plug_in_proc_def_get_help_id
argument_list|(
name|file_proc
argument_list|,
name|help_domain
argument_list|)
expr_stmt|;
block|}
name|entry
operator|.
name|name
operator|=
name|file_proc
operator|->
name|db_info
operator|.
name|name
expr_stmt|;
name|entry
operator|.
name|stock_id
operator|=
name|stock_id
expr_stmt|;
name|entry
operator|.
name|label
operator|=
name|strstr
argument_list|(
name|file_proc
operator|->
name|menu_path
argument_list|,
literal|"/"
argument_list|)
operator|+
literal|1
expr_stmt|;
name|entry
operator|.
name|tooltip
operator|=
name|NULL
expr_stmt|;
name|entry
operator|.
name|callback
operator|=
name|G_CALLBACK
argument_list|(
name|file_type_cmd_callback
argument_list|)
expr_stmt|;
name|entry
operator|.
name|help_id
operator|=
name|help_id
expr_stmt|;
name|gimp_action_group_add_actions
argument_list|(
name|group
argument_list|,
operator|&
name|entry
argument_list|,
literal|1
argument_list|)
expr_stmt|;
name|g_free
argument_list|(
name|help_id
argument_list|)
expr_stmt|;
name|action
operator|=
name|gtk_action_group_get_action
argument_list|(
name|GTK_ACTION_GROUP
argument_list|(
name|group
argument_list|)
argument_list|,
name|file_proc
operator|->
name|db_info
operator|.
name|name
argument_list|)
expr_stmt|;
name|g_object_set_data
argument_list|(
name|G_OBJECT
argument_list|(
name|action
argument_list|)
argument_list|,
literal|"file-proc"
argument_list|,
name|file_proc
argument_list|)
expr_stmt|;
block|}
block|}
end_function

begin_function
name|void
DECL|function|file_open_actions_update (GimpActionGroup * group,gpointer data)
name|file_open_actions_update
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

