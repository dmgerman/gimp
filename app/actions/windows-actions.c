begin_unit|revision:0.9.5;language:C;cregit-version:0.0.1
begin_comment
comment|/* GIMP - The GNU Image Manipulation Program  * Copyright (C) 1995 Spencer Kimball and Peter Mattis  *  * This program is free software: you can redistribute it and/or modify  * it under the terms of the GNU General Public License as published by  * the Free Software Foundation; either version 3 of the License, or  * (at your option) any later version.  *  * This program is distributed in the hope that it will be useful,  * but WITHOUT ANY WARRANTY; without even the implied warranty of  * MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the  * GNU General Public License for more details.  *  * You should have received a copy of the GNU General Public License  * along with this program.  If not, see<http://www.gnu.org/licenses/>.  */
end_comment

begin_include
include|#
directive|include
file|"config.h"
end_include

begin_include
include|#
directive|include
file|<gegl.h>
end_include

begin_include
include|#
directive|include
file|<gtk/gtk.h>
end_include

begin_include
include|#
directive|include
file|<gdk/gdkkeysyms.h>
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
file|"config/gimpdisplayconfig.h"
end_include

begin_include
include|#
directive|include
file|"config/gimpguiconfig.h"
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
file|"widgets/gimpdockwindow.h"
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
file|"display/gimpdisplay-utils.h"
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
name|windows_actions_update_display_accels
parameter_list|(
name|GimpActionGroup
modifier|*
name|group
parameter_list|)
function_decl|;
end_function_decl

begin_function_decl
specifier|static
name|void
name|windows_actions_dock_window_added
parameter_list|(
name|GimpDialogFactory
modifier|*
name|factory
parameter_list|,
name|GimpDockWindow
modifier|*
name|dock_window
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
name|windows_actions_dock_window_removed
parameter_list|(
name|GimpDialogFactory
modifier|*
name|factory
parameter_list|,
name|GimpDockWindow
modifier|*
name|dock_window
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
name|windows_actions_dock_window_notify
parameter_list|(
name|GimpDockWindow
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

begin_function_decl
specifier|static
name|void
name|windows_actions_recent_add
parameter_list|(
name|GimpContainer
modifier|*
name|container
parameter_list|,
name|GimpSessionInfo
modifier|*
name|info
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
name|windows_actions_recent_remove
parameter_list|(
name|GimpContainer
modifier|*
name|container
parameter_list|,
name|GimpSessionInfo
modifier|*
name|info
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
name|windows_actions_single_window_mode_notify
parameter_list|(
name|GimpDisplayConfig
modifier|*
name|config
parameter_list|,
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

begin_comment
comment|/* The only reason we have "Tab" in the action entries below is to  * give away the hardcoded keyboard shortcut. If the user changes the  * shortcut to something else, both that shortcut and Tab will  * work. The reason we have the shortcut hardcoded is beccause  * gtk_accelerator_valid() returns FALSE for GDK_tab.  */
end_comment

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
name|NC_
argument_list|(
literal|"windows-action"
argument_list|,
literal|"_Windows"
argument_list|)
block|}
block|,
block|{
literal|"windows-docks-menu"
block|,
name|NULL
block|,
name|NC_
argument_list|(
literal|"windows-action"
argument_list|,
literal|"_Recently Closed Docks"
argument_list|)
block|}
block|,
block|{
literal|"windows-dialogs-menu"
block|,
name|NULL
block|,
name|NC_
argument_list|(
literal|"windows-action"
argument_list|,
literal|"_Dockable Dialogs"
argument_list|)
block|}
block|,
block|{
literal|"windows-show-display-next"
block|,
name|NULL
block|,
name|NC_
argument_list|(
literal|"windows-action"
argument_list|,
literal|"Next Image"
argument_list|)
block|,
literal|"<alt>Tab"
block|,
name|NC_
argument_list|(
literal|"windows-action"
argument_list|,
literal|"Switch to the next image"
argument_list|)
block|,
name|G_CALLBACK
argument_list|(
name|windows_show_display_next_cmd_callback
argument_list|)
block|,
name|NULL
block|}
block|,
block|{
literal|"windows-show-display-previous"
block|,
name|NULL
block|,
name|NC_
argument_list|(
literal|"windows-action"
argument_list|,
literal|"Previous Image"
argument_list|)
block|,
literal|"<alt><shift>Tab"
block|,
name|NC_
argument_list|(
literal|"windows-action"
argument_list|,
literal|"Switch to the previous image"
argument_list|)
block|,
name|G_CALLBACK
argument_list|(
name|windows_show_display_previous_cmd_callback
argument_list|)
block|,
name|NULL
block|}
block|}
decl_stmt|;
end_decl_stmt

begin_decl_stmt
DECL|variable|windows_toggle_actions
specifier|static
specifier|const
name|GimpToggleActionEntry
name|windows_toggle_actions
index|[]
init|=
block|{
block|{
literal|"windows-hide-docks"
block|,
name|NULL
block|,
name|NC_
argument_list|(
literal|"windows-action"
argument_list|,
literal|"Hide Docks"
argument_list|)
block|,
literal|"Tab"
block|,
name|NC_
argument_list|(
literal|"windows-action"
argument_list|,
literal|"When enabled docks and other dialogs are hidden, leaving only image windows."
argument_list|)
block|,
name|G_CALLBACK
argument_list|(
name|windows_hide_docks_cmd_callback
argument_list|)
block|,
name|FALSE
block|,
name|GIMP_HELP_WINDOWS_HIDE_DOCKS
block|}
block|,
block|{
literal|"windows-use-single-window-mode"
block|,
name|NULL
block|,
name|NC_
argument_list|(
literal|"windows-action"
argument_list|,
literal|"Single-Window Mode"
argument_list|)
block|,
name|NULL
block|,
name|NC_
argument_list|(
literal|"windows-action"
argument_list|,
literal|"When enabled GIMP is in a single-window mode. Far from completely implemented!"
argument_list|)
block|,
name|G_CALLBACK
argument_list|(
name|windows_use_single_window_mode_cmd_callback
argument_list|)
block|,
name|FALSE
block|,
name|GIMP_HELP_WINDOWS_USE_SINGLE_WINDOW_MODE
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
literal|"windows-action"
argument_list|,
name|windows_actions
argument_list|,
name|G_N_ELEMENTS
argument_list|(
name|windows_actions
argument_list|)
argument_list|)
expr_stmt|;
name|gimp_action_group_add_toggle_actions
argument_list|(
name|group
argument_list|,
literal|"windows-action"
argument_list|,
name|windows_toggle_actions
argument_list|,
name|G_N_ELEMENTS
argument_list|(
name|windows_toggle_actions
argument_list|)
argument_list|)
expr_stmt|;
name|gimp_action_group_set_action_hide_empty
argument_list|(
name|group
argument_list|,
literal|"windows-docks-menu"
argument_list|,
name|FALSE
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
name|gimp_get_display_iter
argument_list|(
name|group
operator|->
name|gimp
argument_list|)
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
name|gimp_dialog_factory_get_singleton
argument_list|()
argument_list|,
literal|"dock-window-added"
argument_list|,
name|G_CALLBACK
argument_list|(
name|windows_actions_dock_window_added
argument_list|)
argument_list|,
name|group
argument_list|,
literal|0
argument_list|)
expr_stmt|;
name|g_signal_connect_object
argument_list|(
name|gimp_dialog_factory_get_singleton
argument_list|()
argument_list|,
literal|"dock-window-removed"
argument_list|,
name|G_CALLBACK
argument_list|(
name|windows_actions_dock_window_removed
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
name|gimp_dialog_factory_get_open_dialogs
argument_list|(
name|gimp_dialog_factory_get_singleton
argument_list|()
argument_list|)
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
name|GimpDockWindow
modifier|*
name|dock_window
init|=
name|list
operator|->
name|data
decl_stmt|;
if|if
condition|(
name|GIMP_IS_DOCK_WINDOW
argument_list|(
name|dock_window
argument_list|)
condition|)
name|windows_actions_dock_window_added
argument_list|(
name|gimp_dialog_factory_get_singleton
argument_list|()
argument_list|,
name|dock_window
argument_list|,
name|group
argument_list|)
expr_stmt|;
block|}
name|g_signal_connect_object
argument_list|(
name|global_recent_docks
argument_list|,
literal|"add"
argument_list|,
name|G_CALLBACK
argument_list|(
name|windows_actions_recent_add
argument_list|)
argument_list|,
name|group
argument_list|,
literal|0
argument_list|)
expr_stmt|;
name|g_signal_connect_object
argument_list|(
name|global_recent_docks
argument_list|,
literal|"remove"
argument_list|,
name|G_CALLBACK
argument_list|(
name|windows_actions_recent_remove
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
name|global_recent_docks
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
name|GimpSessionInfo
modifier|*
name|info
init|=
name|list
operator|->
name|data
decl_stmt|;
name|windows_actions_recent_add
argument_list|(
name|global_recent_docks
argument_list|,
name|info
argument_list|,
name|group
argument_list|)
expr_stmt|;
block|}
name|g_signal_connect_object
argument_list|(
name|group
operator|->
name|gimp
operator|->
name|config
argument_list|,
literal|"notify::single-window-mode"
argument_list|,
name|G_CALLBACK
argument_list|(
name|windows_actions_single_window_mode_notify
argument_list|)
argument_list|,
name|group
argument_list|,
literal|0
argument_list|)
expr_stmt|;
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
block|{
name|GimpGuiConfig
modifier|*
name|config
init|=
name|GIMP_GUI_CONFIG
argument_list|(
name|group
operator|->
name|gimp
operator|->
name|config
argument_list|)
decl_stmt|;
DECL|macro|SET_ACTIVE (action,condition)
define|#
directive|define
name|SET_ACTIVE
parameter_list|(
name|action
parameter_list|,
name|condition
parameter_list|)
define|\
value|gimp_action_group_set_action_active (group, action, (condition) != 0)
name|SET_ACTIVE
argument_list|(
literal|"windows-use-single-window-mode"
argument_list|,
name|config
operator|->
name|single_window_mode
argument_list|)
expr_stmt|;
name|SET_ACTIVE
argument_list|(
literal|"windows-hide-docks"
argument_list|,
name|config
operator|->
name|hide_docks
argument_list|)
expr_stmt|;
undef|#
directive|undef
name|SET_ACTIVE
block|}
end_function

begin_function
name|gchar
modifier|*
DECL|function|windows_actions_dock_window_to_action_name (GimpDockWindow * dock_window)
name|windows_actions_dock_window_to_action_name
parameter_list|(
name|GimpDockWindow
modifier|*
name|dock_window
parameter_list|)
block|{
return|return
name|g_strdup_printf
argument_list|(
literal|"windows-dock-%04d"
argument_list|,
name|gimp_dock_window_get_id
argument_list|(
name|dock_window
argument_list|)
argument_list|)
return|;
block|}
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
name|gimp_display_get_image
argument_list|(
name|display
argument_list|)
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
name|gimp_display_get_action_name
argument_list|(
name|display
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
name|windows_actions_update_display_accels
argument_list|(
name|group
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
name|GimpImage
modifier|*
name|image
init|=
name|gimp_display_get_image
argument_list|(
name|display
argument_list|)
decl_stmt|;
if|if
condition|(
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
name|gimp_display_get_action_name
argument_list|(
name|display
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
name|NULL
argument_list|,
operator|&
name|entry
argument_list|,
literal|1
argument_list|)
expr_stmt|;
name|gimp_action_group_set_action_always_show_image
argument_list|(
name|group
argument_list|,
name|action_name
argument_list|,
name|TRUE
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
name|gimp_image_get_uri_or_untitled
argument_list|(
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
name|image
argument_list|)
argument_list|,
name|gimp_display_get_instance
argument_list|(
name|display
argument_list|)
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
name|windows_actions_update_display_accels
argument_list|(
name|group
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
DECL|function|windows_actions_update_display_accels (GimpActionGroup * group)
name|windows_actions_update_display_accels
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
name|gint
name|i
decl_stmt|;
for|for
control|(
name|list
operator|=
name|gimp_get_display_iter
argument_list|(
name|group
operator|->
name|gimp
argument_list|)
operator|,
name|i
operator|=
literal|0
init|;
name|list
operator|&&
name|i
operator|<
literal|10
condition|;
name|list
operator|=
name|g_list_next
argument_list|(
name|list
argument_list|)
operator|,
name|i
operator|++
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
name|GtkAction
modifier|*
name|action
decl_stmt|;
name|gchar
modifier|*
name|action_name
decl_stmt|;
if|if
condition|(
operator|!
name|gimp_display_get_image
argument_list|(
name|display
argument_list|)
condition|)
break|break;
name|action_name
operator|=
name|gimp_display_get_action_name
argument_list|(
name|display
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
name|g_free
argument_list|(
name|action_name
argument_list|)
expr_stmt|;
if|if
condition|(
name|action
condition|)
block|{
specifier|const
name|gchar
modifier|*
name|accel_path
decl_stmt|;
name|guint
name|accel_key
decl_stmt|;
name|accel_path
operator|=
name|gtk_action_get_accel_path
argument_list|(
name|action
argument_list|)
expr_stmt|;
if|if
condition|(
name|i
operator|<
literal|9
condition|)
name|accel_key
operator|=
name|GDK_KEY_1
operator|+
name|i
expr_stmt|;
else|else
name|accel_key
operator|=
name|GDK_KEY_0
expr_stmt|;
name|gtk_accel_map_change_entry
argument_list|(
name|accel_path
argument_list|,
name|accel_key
argument_list|,
name|GDK_MOD1_MASK
argument_list|,
name|TRUE
argument_list|)
expr_stmt|;
block|}
block|}
block|}
end_function

begin_function
specifier|static
name|void
DECL|function|windows_actions_dock_window_added (GimpDialogFactory * factory,GimpDockWindow * dock_window,GimpActionGroup * group)
name|windows_actions_dock_window_added
parameter_list|(
name|GimpDialogFactory
modifier|*
name|factory
parameter_list|,
name|GimpDockWindow
modifier|*
name|dock_window
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
name|windows_actions_dock_window_to_action_name
argument_list|(
name|dock_window
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
name|GIMP_HELP_WINDOWS_SHOW_DOCK
expr_stmt|;
name|gimp_action_group_add_actions
argument_list|(
name|group
argument_list|,
name|NULL
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
literal|"dock-window"
argument_list|,
name|dock_window
argument_list|)
expr_stmt|;
name|g_free
argument_list|(
name|action_name
argument_list|)
expr_stmt|;
name|g_signal_connect_object
argument_list|(
name|dock_window
argument_list|,
literal|"notify::title"
argument_list|,
name|G_CALLBACK
argument_list|(
name|windows_actions_dock_window_notify
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
name|dock_window
argument_list|)
argument_list|)
condition|)
name|windows_actions_dock_window_notify
argument_list|(
name|dock_window
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
DECL|function|windows_actions_dock_window_removed (GimpDialogFactory * factory,GimpDockWindow * dock_window,GimpActionGroup * group)
name|windows_actions_dock_window_removed
parameter_list|(
name|GimpDialogFactory
modifier|*
name|factory
parameter_list|,
name|GimpDockWindow
modifier|*
name|dock_window
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
name|windows_actions_dock_window_to_action_name
argument_list|(
name|dock_window
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
DECL|function|windows_actions_dock_window_notify (GimpDockWindow * dock_window,const GParamSpec * pspec,GimpActionGroup * group)
name|windows_actions_dock_window_notify
parameter_list|(
name|GimpDockWindow
modifier|*
name|dock_window
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
decl_stmt|;
name|action_name
operator|=
name|windows_actions_dock_window_to_action_name
argument_list|(
name|dock_window
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
name|g_free
argument_list|(
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
name|dock_window
argument_list|)
argument_list|)
argument_list|,
literal|"tooltip"
argument_list|,
name|gtk_window_get_title
argument_list|(
name|GTK_WINDOW
argument_list|(
name|dock_window
argument_list|)
argument_list|)
argument_list|,
name|NULL
argument_list|)
expr_stmt|;
block|}
end_function

begin_function
specifier|static
name|void
DECL|function|windows_actions_recent_add (GimpContainer * container,GimpSessionInfo * info,GimpActionGroup * group)
name|windows_actions_recent_add
parameter_list|(
name|GimpContainer
modifier|*
name|container
parameter_list|,
name|GimpSessionInfo
modifier|*
name|info
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
name|gint
name|info_id
decl_stmt|;
specifier|static
name|gint
name|info_id_counter
init|=
literal|1
decl_stmt|;
name|gchar
modifier|*
name|action_name
decl_stmt|;
name|info_id
operator|=
name|GPOINTER_TO_INT
argument_list|(
name|g_object_get_data
argument_list|(
name|G_OBJECT
argument_list|(
name|info
argument_list|)
argument_list|,
literal|"recent-action-id"
argument_list|)
argument_list|)
expr_stmt|;
if|if
condition|(
operator|!
name|info_id
condition|)
block|{
name|info_id
operator|=
name|info_id_counter
operator|++
expr_stmt|;
name|g_object_set_data
argument_list|(
name|G_OBJECT
argument_list|(
name|info
argument_list|)
argument_list|,
literal|"recent-action-id"
argument_list|,
name|GINT_TO_POINTER
argument_list|(
name|info_id
argument_list|)
argument_list|)
expr_stmt|;
block|}
name|action_name
operator|=
name|g_strdup_printf
argument_list|(
literal|"windows-recent-%04d"
argument_list|,
name|info_id
argument_list|)
expr_stmt|;
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
name|gimp_object_get_name
argument_list|(
name|info
argument_list|)
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
name|gimp_object_get_name
argument_list|(
name|info
argument_list|)
expr_stmt|;
name|entry
operator|.
name|callback
operator|=
name|G_CALLBACK
argument_list|(
name|windows_open_recent_cmd_callback
argument_list|)
expr_stmt|;
name|entry
operator|.
name|help_id
operator|=
name|GIMP_HELP_WINDOWS_OPEN_RECENT_DOCK
expr_stmt|;
name|gimp_action_group_add_actions
argument_list|(
name|group
argument_list|,
name|NULL
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
literal|"max-width-chars"
argument_list|,
literal|30
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
literal|"info"
argument_list|,
name|info
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
DECL|function|windows_actions_recent_remove (GimpContainer * container,GimpSessionInfo * info,GimpActionGroup * group)
name|windows_actions_recent_remove
parameter_list|(
name|GimpContainer
modifier|*
name|container
parameter_list|,
name|GimpSessionInfo
modifier|*
name|info
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
name|gint
name|info_id
decl_stmt|;
name|gchar
modifier|*
name|action_name
decl_stmt|;
name|info_id
operator|=
name|GPOINTER_TO_INT
argument_list|(
name|g_object_get_data
argument_list|(
name|G_OBJECT
argument_list|(
name|info
argument_list|)
argument_list|,
literal|"recent-action-id"
argument_list|)
argument_list|)
expr_stmt|;
name|action_name
operator|=
name|g_strdup_printf
argument_list|(
literal|"windows-recent-%04d"
argument_list|,
name|info_id
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
DECL|function|windows_actions_single_window_mode_notify (GimpDisplayConfig * config,GParamSpec * pspec,GimpActionGroup * group)
name|windows_actions_single_window_mode_notify
parameter_list|(
name|GimpDisplayConfig
modifier|*
name|config
parameter_list|,
name|GParamSpec
modifier|*
name|pspec
parameter_list|,
name|GimpActionGroup
modifier|*
name|group
parameter_list|)
block|{
name|gimp_action_group_set_action_active
argument_list|(
name|group
argument_list|,
literal|"windows-use-single-window-mode"
argument_list|,
name|GIMP_GUI_CONFIG
argument_list|(
name|config
argument_list|)
operator|->
name|single_window_mode
argument_list|)
expr_stmt|;
block|}
end_function

end_unit

