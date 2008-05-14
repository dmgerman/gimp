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
file|"libgimpbase/gimpbase.h"
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
file|"core/gimpimage.h"
end_include

begin_include
include|#
directive|include
file|"core/gimplist.h"
end_include

begin_include
include|#
directive|include
file|"file/file-utils.h"
end_include

begin_include
include|#
directive|include
file|"widgets/gimpactiongroup.h"
end_include

begin_include
include|#
directive|include
file|"widgets/gimpdialogfactory.h"
end_include

begin_include
include|#
directive|include
file|"widgets/gimpdock.h"
end_include

begin_include
include|#
directive|include
file|"widgets/gimphelp-ids.h"
end_include

begin_include
include|#
directive|include
file|"display/gimpdisplay.h"
end_include

begin_include
include|#
directive|include
file|"dialogs/dialogs.h"
end_include

begin_include
include|#
directive|include
file|"windows-actions.h"
end_include

begin_include
include|#
directive|include
file|"windows-commands.h"
end_include

begin_include
include|#
directive|include
file|"gimp-intl.h"
end_include

begin_function_decl
specifier|static
name|void
name|windows_actions_display_add
parameter_list|(
name|GimpContainer
modifier|*
name|container
parameter_list|,
name|GimpDisplay
modifier|*
name|display
parameter_list|,
name|GimpActionGroup
modifier|*
name|group
parameter_list|)
function_decl|;
end_function_decl

begin_function_decl
specifier|static
name|void
name|windows_actions_display_remove
parameter_list|(
name|GimpContainer
modifier|*
name|container
parameter_list|,
name|GimpDisplay
modifier|*
name|display
parameter_list|,
name|GimpActionGroup
modifier|*
name|group
parameter_list|)
function_decl|;
end_function_decl

begin_function_decl
specifier|static
name|void
name|windows_actions_image_notify
parameter_list|(
name|GimpDisplay
modifier|*
name|display
parameter_list|,
specifier|const
name|GParamSpec
modifier|*
name|unused
parameter_list|,
name|GimpActionGroup
modifier|*
name|group
parameter_list|)
function_decl|;
end_function_decl

begin_function_decl
specifier|static
name|void
name|windows_actions_dock_added
parameter_list|(
name|GimpDialogFactory
modifier|*
name|factory
parameter_list|,
name|GimpDock
modifier|*
name|dock
parameter_list|,
name|GimpActionGroup
modifier|*
name|group
parameter_list|)
function_decl|;
end_function_decl

begin_function_decl
specifier|static
name|void
name|windows_actions_dock_removed
parameter_list|(
name|GimpDialogFactory
modifier|*
name|factory
parameter_list|,
name|GimpDock
modifier|*
name|dock
parameter_list|,
name|GimpActionGroup
modifier|*
name|group
parameter_list|)
function_decl|;
end_function_decl

begin_function_decl
specifier|static
name|void
name|windows_actions_dock_notify
parameter_list|(
name|GimpDock
modifier|*
name|dock
parameter_list|,
specifier|const
name|GParamSpec
modifier|*
name|pspec
parameter_list|,
name|GimpActionGroup
modifier|*
name|group
parameter_list|)
function_decl|;
end_function_decl

begin_decl_stmt
DECL|variable|windows_actions
specifier|static
specifier|const
name|GimpActionEntry
name|windows_actions
index|[]
init|=
block|{
block|{
literal|"windows-menu"
block|,
name|NULL
block|,
name|N_
argument_list|(
literal|"_Windows"
argument_list|)
block|}
block|,
block|{
literal|"windows-docks-menu"
block|,
name|NULL
block|,
name|N_
argument_list|(
literal|"_Recently Closed Docks"
argument_list|)
block|}
block|,
block|{
literal|"windows-dialogs-menu"
block|,
name|NULL
block|,
name|N_
argument_list|(
literal|"_Dockable Dialogs"
argument_list|)
block|}
block|,
block|{
literal|"windows-show-toolbox"
block|,
name|NULL
block|,
name|N_
argument_list|(
literal|"Tool_box"
argument_list|)
block|,
literal|"<control>B"
block|,
name|N_
argument_list|(
literal|"Raise the toolbox"
argument_list|)
block|,
name|G_CALLBACK
argument_list|(
name|windows_show_toolbox_cmd_callback
argument_list|)
block|,
name|GIMP_HELP_TOOLBOX
block|}
block|}
decl_stmt|;
end_decl_stmt

begin_function
name|void
DECL|function|windows_actions_setup (GimpActionGroup * group)
name|windows_actions_setup
parameter_list|(
name|GimpActionGroup
modifier|*
name|group
parameter_list|)
block|{
name|GList
modifier|*
name|list
decl_stmt|;
name|gimp_action_group_add_actions
argument_list|(
name|group
argument_list|,
name|windows_actions
argument_list|,
name|G_N_ELEMENTS
argument_list|(
name|windows_actions
argument_list|)
argument_list|)
expr_stmt|;
name|g_signal_connect_object
argument_list|(
name|group
operator|->
name|gimp
operator|->
name|displays
argument_list|,
literal|"add"
argument_list|,
name|G_CALLBACK
argument_list|(
name|windows_actions_display_add
argument_list|)
argument_list|,
name|group
argument_list|,
literal|0
argument_list|)
expr_stmt|;
name|g_signal_connect_object
argument_list|(
name|group
operator|->
name|gimp
operator|->
name|displays
argument_list|,
literal|"remove"
argument_list|,
name|G_CALLBACK
argument_list|(
name|windows_actions_display_remove
argument_list|)
argument_list|,
name|group
argument_list|,
literal|0
argument_list|)
expr_stmt|;
for|for
control|(
name|list
operator|=
name|GIMP_LIST
argument_list|(
name|group
operator|->
name|gimp
operator|->
name|displays
argument_list|)
operator|->
name|list
init|;
name|list
condition|;
name|list
operator|=
name|g_list_next
argument_list|(
name|list
argument_list|)
control|)
block|{
name|GimpDisplay
modifier|*
name|display
init|=
name|list
operator|->
name|data
decl_stmt|;
name|windows_actions_display_add
argument_list|(
name|group
operator|->
name|gimp
operator|->
name|displays
argument_list|,
name|display
argument_list|,
name|group
argument_list|)
expr_stmt|;
block|}
name|g_signal_connect_object
argument_list|(
name|global_dock_factory
argument_list|,
literal|"dock-added"
argument_list|,
name|G_CALLBACK
argument_list|(
name|windows_actions_dock_added
argument_list|)
argument_list|,
name|group
argument_list|,
literal|0
argument_list|)
expr_stmt|;
name|g_signal_connect_object
argument_list|(
name|global_dock_factory
argument_list|,
literal|"dock-removed"
argument_list|,
name|G_CALLBACK
argument_list|(
name|windows_actions_dock_removed
argument_list|)
argument_list|,
name|group
argument_list|,
literal|0
argument_list|)
expr_stmt|;
for|for
control|(
name|list
operator|=
name|global_dock_factory
operator|->
name|open_dialogs
init|;
name|list
condition|;
name|list
operator|=
name|g_list_next
argument_list|(
name|list
argument_list|)
control|)
block|{
name|GimpDock
modifier|*
name|dock
init|=
name|list
operator|->
name|data
decl_stmt|;
if|if
condition|(
name|GIMP_IS_DOCK
argument_list|(
name|dock
argument_list|)
condition|)
name|windows_actions_dock_added
argument_list|(
name|global_dock_factory
argument_list|,
name|dock
argument_list|,
name|group
argument_list|)
expr_stmt|;
block|}
block|}
end_function

begin_function
name|void
DECL|function|windows_actions_update (GimpActionGroup * group,gpointer data)
name|windows_actions_update
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

begin_comment
comment|/*  private functions  */
end_comment

begin_function
specifier|static
name|void
DECL|function|windows_actions_display_add (GimpContainer * container,GimpDisplay * display,GimpActionGroup * group)
name|windows_actions_display_add
parameter_list|(
name|GimpContainer
modifier|*
name|container
parameter_list|,
name|GimpDisplay
modifier|*
name|display
parameter_list|,
name|GimpActionGroup
modifier|*
name|group
parameter_list|)
block|{
name|g_signal_connect_object
argument_list|(
name|display
argument_list|,
literal|"notify::image"
argument_list|,
name|G_CALLBACK
argument_list|(
name|windows_actions_image_notify
argument_list|)
argument_list|,
name|group
argument_list|,
literal|0
argument_list|)
expr_stmt|;
if|if
condition|(
name|display
operator|->
name|image
condition|)
name|windows_actions_image_notify
argument_list|(
name|display
argument_list|,
name|NULL
argument_list|,
name|group
argument_list|)
expr_stmt|;
block|}
end_function

begin_function
specifier|static
name|void
DECL|function|windows_actions_display_remove (GimpContainer * container,GimpDisplay * display,GimpActionGroup * group)
name|windows_actions_display_remove
parameter_list|(
name|GimpContainer
modifier|*
name|container
parameter_list|,
name|GimpDisplay
modifier|*
name|display
parameter_list|,
name|GimpActionGroup
modifier|*
name|group
parameter_list|)
block|{
name|GtkAction
modifier|*
name|action
decl_stmt|;
name|gchar
modifier|*
name|action_name
init|=
name|g_strdup_printf
argument_list|(
literal|"windows-display-%04d"
argument_list|,
name|gimp_display_get_ID
argument_list|(
name|display
argument_list|)
argument_list|)
decl_stmt|;
name|action
operator|=
name|gtk_action_group_get_action
argument_list|(
name|GTK_ACTION_GROUP
argument_list|(
name|group
argument_list|)
argument_list|,
name|action_name
argument_list|)
expr_stmt|;
if|if
condition|(
name|action
condition|)
name|gtk_action_group_remove_action
argument_list|(
name|GTK_ACTION_GROUP
argument_list|(
name|group
argument_list|)
argument_list|,
name|action
argument_list|)
expr_stmt|;
name|g_free
argument_list|(
name|action_name
argument_list|)
expr_stmt|;
block|}
end_function

begin_function
specifier|static
name|void
DECL|function|windows_actions_image_notify (GimpDisplay * display,const GParamSpec * unused,GimpActionGroup * group)
name|windows_actions_image_notify
parameter_list|(
name|GimpDisplay
modifier|*
name|display
parameter_list|,
specifier|const
name|GParamSpec
modifier|*
name|unused
parameter_list|,
name|GimpActionGroup
modifier|*
name|group
parameter_list|)
block|{
if|if
condition|(
name|display
operator|->
name|image
condition|)
block|{
name|GtkAction
modifier|*
name|action
decl_stmt|;
name|gchar
modifier|*
name|action_name
init|=
name|g_strdup_printf
argument_list|(
literal|"windows-display-%04d"
argument_list|,
name|gimp_display_get_ID
argument_list|(
name|display
argument_list|)
argument_list|)
decl_stmt|;
name|action
operator|=
name|gtk_action_group_get_action
argument_list|(
name|GTK_ACTION_GROUP
argument_list|(
name|group
argument_list|)
argument_list|,
name|action_name
argument_list|)
expr_stmt|;
if|if
condition|(
operator|!
name|action
condition|)
block|{
name|GimpActionEntry
name|entry
decl_stmt|;
name|entry
operator|.
name|name
operator|=
name|action_name
expr_stmt|;
name|entry
operator|.
name|stock_id
operator|=
name|GIMP_STOCK_IMAGE
expr_stmt|;
name|entry
operator|.
name|label
operator|=
literal|""
expr_stmt|;
name|entry
operator|.
name|accelerator
operator|=
name|NULL
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
name|windows_show_display_cmd_callback
argument_list|)
expr_stmt|;
name|entry
operator|.
name|help_id
operator|=
name|NULL
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
name|action
operator|=
name|gtk_action_group_get_action
argument_list|(
name|GTK_ACTION_GROUP
argument_list|(
name|group
argument_list|)
argument_list|,
name|action_name
argument_list|)
expr_stmt|;
name|g_object_set_data
argument_list|(
name|G_OBJECT
argument_list|(
name|action
argument_list|)
argument_list|,
literal|"display"
argument_list|,
name|display
argument_list|)
expr_stmt|;
block|}
block|{
specifier|const
name|gchar
modifier|*
name|uri
decl_stmt|;
name|gchar
modifier|*
name|filename
decl_stmt|;
name|gchar
modifier|*
name|basename
decl_stmt|;
name|gchar
modifier|*
name|escaped
decl_stmt|;
name|gchar
modifier|*
name|title
decl_stmt|;
name|uri
operator|=
name|gimp_image_get_uri
argument_list|(
name|display
operator|->
name|image
argument_list|)
expr_stmt|;
name|filename
operator|=
name|file_utils_uri_display_name
argument_list|(
name|uri
argument_list|)
expr_stmt|;
name|basename
operator|=
name|file_utils_uri_display_basename
argument_list|(
name|uri
argument_list|)
expr_stmt|;
name|escaped
operator|=
name|gimp_escape_uline
argument_list|(
name|basename
argument_list|)
expr_stmt|;
name|g_free
argument_list|(
name|basename
argument_list|)
expr_stmt|;
name|title
operator|=
name|g_strdup_printf
argument_list|(
literal|"%s-%d.%d"
argument_list|,
name|escaped
argument_list|,
name|gimp_image_get_ID
argument_list|(
name|display
operator|->
name|image
argument_list|)
argument_list|,
name|display
operator|->
name|instance
argument_list|)
expr_stmt|;
name|g_free
argument_list|(
name|escaped
argument_list|)
expr_stmt|;
name|g_object_set
argument_list|(
name|action
argument_list|,
literal|"label"
argument_list|,
name|title
argument_list|,
literal|"tooltip"
argument_list|,
name|filename
argument_list|,
literal|"viewable"
argument_list|,
name|display
operator|->
name|image
argument_list|,
literal|"context"
argument_list|,
name|gimp_get_user_context
argument_list|(
name|group
operator|->
name|gimp
argument_list|)
argument_list|,
name|NULL
argument_list|)
expr_stmt|;
name|g_free
argument_list|(
name|filename
argument_list|)
expr_stmt|;
name|g_free
argument_list|(
name|title
argument_list|)
expr_stmt|;
block|}
name|g_free
argument_list|(
name|action_name
argument_list|)
expr_stmt|;
block|}
else|else
block|{
name|windows_actions_display_remove
argument_list|(
name|group
operator|->
name|gimp
operator|->
name|displays
argument_list|,
name|display
argument_list|,
name|group
argument_list|)
expr_stmt|;
block|}
block|}
end_function

begin_function
specifier|static
name|void
DECL|function|windows_actions_dock_added (GimpDialogFactory * factory,GimpDock * dock,GimpActionGroup * group)
name|windows_actions_dock_added
parameter_list|(
name|GimpDialogFactory
modifier|*
name|factory
parameter_list|,
name|GimpDock
modifier|*
name|dock
parameter_list|,
name|GimpActionGroup
modifier|*
name|group
parameter_list|)
block|{
name|GtkAction
modifier|*
name|action
decl_stmt|;
name|GimpActionEntry
name|entry
decl_stmt|;
name|gchar
modifier|*
name|action_name
init|=
name|g_strdup_printf
argument_list|(
literal|"windows-dock-%04d"
argument_list|,
name|dock
operator|->
name|ID
argument_list|)
decl_stmt|;
name|entry
operator|.
name|name
operator|=
name|action_name
expr_stmt|;
name|entry
operator|.
name|stock_id
operator|=
name|NULL
expr_stmt|;
name|entry
operator|.
name|label
operator|=
literal|""
expr_stmt|;
name|entry
operator|.
name|accelerator
operator|=
name|NULL
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
name|windows_show_dock_cmd_callback
argument_list|)
expr_stmt|;
name|entry
operator|.
name|help_id
operator|=
name|NULL
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
name|action
operator|=
name|gtk_action_group_get_action
argument_list|(
name|GTK_ACTION_GROUP
argument_list|(
name|group
argument_list|)
argument_list|,
name|action_name
argument_list|)
expr_stmt|;
name|g_object_set
argument_list|(
name|action
argument_list|,
literal|"ellipsize"
argument_list|,
name|PANGO_ELLIPSIZE_END
argument_list|,
name|NULL
argument_list|)
expr_stmt|;
name|g_object_set_data
argument_list|(
name|G_OBJECT
argument_list|(
name|action
argument_list|)
argument_list|,
literal|"dock"
argument_list|,
name|dock
argument_list|)
expr_stmt|;
name|g_free
argument_list|(
name|action_name
argument_list|)
expr_stmt|;
name|g_signal_connect_object
argument_list|(
name|dock
argument_list|,
literal|"notify::title"
argument_list|,
name|G_CALLBACK
argument_list|(
name|windows_actions_dock_notify
argument_list|)
argument_list|,
name|group
argument_list|,
literal|0
argument_list|)
expr_stmt|;
if|if
condition|(
name|gtk_window_get_title
argument_list|(
name|GTK_WINDOW
argument_list|(
name|dock
argument_list|)
argument_list|)
condition|)
name|windows_actions_dock_notify
argument_list|(
name|dock
argument_list|,
name|NULL
argument_list|,
name|group
argument_list|)
expr_stmt|;
block|}
end_function

begin_function
specifier|static
name|void
DECL|function|windows_actions_dock_removed (GimpDialogFactory * factory,GimpDock * dock,GimpActionGroup * group)
name|windows_actions_dock_removed
parameter_list|(
name|GimpDialogFactory
modifier|*
name|factory
parameter_list|,
name|GimpDock
modifier|*
name|dock
parameter_list|,
name|GimpActionGroup
modifier|*
name|group
parameter_list|)
block|{
name|GtkAction
modifier|*
name|action
decl_stmt|;
name|gchar
modifier|*
name|action_name
init|=
name|g_strdup_printf
argument_list|(
literal|"windows-dock-%04d"
argument_list|,
name|dock
operator|->
name|ID
argument_list|)
decl_stmt|;
name|action
operator|=
name|gtk_action_group_get_action
argument_list|(
name|GTK_ACTION_GROUP
argument_list|(
name|group
argument_list|)
argument_list|,
name|action_name
argument_list|)
expr_stmt|;
if|if
condition|(
name|action
condition|)
name|gtk_action_group_remove_action
argument_list|(
name|GTK_ACTION_GROUP
argument_list|(
name|group
argument_list|)
argument_list|,
name|action
argument_list|)
expr_stmt|;
name|g_free
argument_list|(
name|action_name
argument_list|)
expr_stmt|;
block|}
end_function

begin_function
specifier|static
name|void
DECL|function|windows_actions_dock_notify (GimpDock * dock,const GParamSpec * pspec,GimpActionGroup * group)
name|windows_actions_dock_notify
parameter_list|(
name|GimpDock
modifier|*
name|dock
parameter_list|,
specifier|const
name|GParamSpec
modifier|*
name|pspec
parameter_list|,
name|GimpActionGroup
modifier|*
name|group
parameter_list|)
block|{
name|GtkAction
modifier|*
name|action
decl_stmt|;
name|gchar
modifier|*
name|action_name
init|=
name|g_strdup_printf
argument_list|(
literal|"windows-dock-%04d"
argument_list|,
name|dock
operator|->
name|ID
argument_list|)
decl_stmt|;
name|action
operator|=
name|gtk_action_group_get_action
argument_list|(
name|GTK_ACTION_GROUP
argument_list|(
name|group
argument_list|)
argument_list|,
name|action_name
argument_list|)
expr_stmt|;
if|if
condition|(
name|action
condition|)
name|g_object_set
argument_list|(
name|action
argument_list|,
literal|"label"
argument_list|,
name|gtk_window_get_title
argument_list|(
name|GTK_WINDOW
argument_list|(
name|dock
argument_list|)
argument_list|)
argument_list|,
name|NULL
argument_list|)
expr_stmt|;
block|}
end_function

end_unit

