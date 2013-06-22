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
file|<string.h>
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
file|"core/gimpcontainer.h"
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
file|"widgets/gimpsessioninfo.h"
end_include

begin_include
include|#
directive|include
file|"widgets/gimpwidgets-utils.h"
end_include

begin_include
include|#
directive|include
file|"display/gimpdisplay.h"
end_include

begin_include
include|#
directive|include
file|"display/gimpdisplayshell.h"
end_include

begin_include
include|#
directive|include
file|"dialogs/dialogs.h"
end_include

begin_include
include|#
directive|include
file|"actions.h"
end_include

begin_include
include|#
directive|include
file|"dialogs-actions.h"
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

begin_function
name|void
DECL|function|windows_hide_docks_cmd_callback (GtkAction * action,gpointer data)
name|windows_hide_docks_cmd_callback
parameter_list|(
name|GtkAction
modifier|*
name|action
parameter_list|,
name|gpointer
name|data
parameter_list|)
block|{
name|gboolean
name|active
init|=
name|gtk_toggle_action_get_active
argument_list|(
name|GTK_TOGGLE_ACTION
argument_list|(
name|action
argument_list|)
argument_list|)
decl_stmt|;
name|Gimp
modifier|*
name|gimp
decl_stmt|;
name|return_if_no_gimp
argument_list|(
name|gimp
argument_list|,
name|data
argument_list|)
expr_stmt|;
if|if
condition|(
name|GIMP_GUI_CONFIG
argument_list|(
name|gimp
operator|->
name|config
argument_list|)
operator|->
name|hide_docks
operator|==
name|active
condition|)
return|return;
name|g_object_set
argument_list|(
name|gimp
operator|->
name|config
argument_list|,
literal|"hide-docks"
argument_list|,
name|active
argument_list|,
name|NULL
argument_list|)
expr_stmt|;
block|}
end_function

begin_function
name|void
DECL|function|windows_use_single_window_mode_cmd_callback (GtkAction * action,gpointer data)
name|windows_use_single_window_mode_cmd_callback
parameter_list|(
name|GtkAction
modifier|*
name|action
parameter_list|,
name|gpointer
name|data
parameter_list|)
block|{
name|gboolean
name|active
init|=
name|gtk_toggle_action_get_active
argument_list|(
name|GTK_TOGGLE_ACTION
argument_list|(
name|action
argument_list|)
argument_list|)
decl_stmt|;
name|Gimp
modifier|*
name|gimp
decl_stmt|;
name|return_if_no_gimp
argument_list|(
name|gimp
argument_list|,
name|data
argument_list|)
expr_stmt|;
if|if
condition|(
name|GIMP_GUI_CONFIG
argument_list|(
name|gimp
operator|->
name|config
argument_list|)
operator|->
name|single_window_mode
operator|==
name|active
condition|)
return|return;
name|g_object_set
argument_list|(
name|gimp
operator|->
name|config
argument_list|,
literal|"single-window-mode"
argument_list|,
name|active
argument_list|,
name|NULL
argument_list|)
expr_stmt|;
block|}
end_function

begin_function
name|void
DECL|function|windows_show_display_next_cmd_callback (GtkAction * action,gpointer data)
name|windows_show_display_next_cmd_callback
parameter_list|(
name|GtkAction
modifier|*
name|action
parameter_list|,
name|gpointer
name|data
parameter_list|)
block|{
name|GimpDisplay
modifier|*
name|display
decl_stmt|;
name|Gimp
modifier|*
name|gimp
decl_stmt|;
name|gint
name|index
decl_stmt|;
name|return_if_no_display
argument_list|(
name|display
argument_list|,
name|data
argument_list|)
expr_stmt|;
name|return_if_no_gimp
argument_list|(
name|gimp
argument_list|,
name|data
argument_list|)
expr_stmt|;
name|index
operator|=
name|gimp_container_get_child_index
argument_list|(
name|gimp
operator|->
name|displays
argument_list|,
name|GIMP_OBJECT
argument_list|(
name|display
argument_list|)
argument_list|)
expr_stmt|;
name|index
operator|++
expr_stmt|;
if|if
condition|(
name|index
operator|>=
name|gimp_container_get_n_children
argument_list|(
name|gimp
operator|->
name|displays
argument_list|)
condition|)
name|index
operator|=
literal|0
expr_stmt|;
name|display
operator|=
name|GIMP_DISPLAY
argument_list|(
name|gimp_container_get_child_by_index
argument_list|(
name|gimp
operator|->
name|displays
argument_list|,
name|index
argument_list|)
argument_list|)
expr_stmt|;
name|gimp_display_shell_present
argument_list|(
name|gimp_display_get_shell
argument_list|(
name|display
argument_list|)
argument_list|)
expr_stmt|;
block|}
end_function

begin_function
name|void
DECL|function|windows_show_display_previous_cmd_callback (GtkAction * action,gpointer data)
name|windows_show_display_previous_cmd_callback
parameter_list|(
name|GtkAction
modifier|*
name|action
parameter_list|,
name|gpointer
name|data
parameter_list|)
block|{
name|GimpDisplay
modifier|*
name|display
decl_stmt|;
name|Gimp
modifier|*
name|gimp
decl_stmt|;
name|gint
name|index
decl_stmt|;
name|return_if_no_display
argument_list|(
name|display
argument_list|,
name|data
argument_list|)
expr_stmt|;
name|return_if_no_gimp
argument_list|(
name|gimp
argument_list|,
name|data
argument_list|)
expr_stmt|;
name|index
operator|=
name|gimp_container_get_child_index
argument_list|(
name|gimp
operator|->
name|displays
argument_list|,
name|GIMP_OBJECT
argument_list|(
name|display
argument_list|)
argument_list|)
expr_stmt|;
name|index
operator|--
expr_stmt|;
if|if
condition|(
name|index
operator|<
literal|0
condition|)
name|index
operator|=
name|gimp_container_get_n_children
argument_list|(
name|gimp
operator|->
name|displays
argument_list|)
operator|-
literal|1
expr_stmt|;
name|display
operator|=
name|GIMP_DISPLAY
argument_list|(
name|gimp_container_get_child_by_index
argument_list|(
name|gimp
operator|->
name|displays
argument_list|,
name|index
argument_list|)
argument_list|)
expr_stmt|;
name|gimp_display_shell_present
argument_list|(
name|gimp_display_get_shell
argument_list|(
name|display
argument_list|)
argument_list|)
expr_stmt|;
block|}
end_function

begin_function
name|void
DECL|function|windows_show_display_cmd_callback (GtkAction * action,gpointer data)
name|windows_show_display_cmd_callback
parameter_list|(
name|GtkAction
modifier|*
name|action
parameter_list|,
name|gpointer
name|data
parameter_list|)
block|{
name|GimpDisplay
modifier|*
name|display
init|=
name|g_object_get_data
argument_list|(
name|G_OBJECT
argument_list|(
name|action
argument_list|)
argument_list|,
literal|"display"
argument_list|)
decl_stmt|;
name|gimp_display_shell_present
argument_list|(
name|gimp_display_get_shell
argument_list|(
name|display
argument_list|)
argument_list|)
expr_stmt|;
block|}
end_function

begin_function
name|void
DECL|function|windows_show_dock_cmd_callback (GtkAction * action,gpointer data)
name|windows_show_dock_cmd_callback
parameter_list|(
name|GtkAction
modifier|*
name|action
parameter_list|,
name|gpointer
name|data
parameter_list|)
block|{
name|GtkWindow
modifier|*
name|dock_window
init|=
name|g_object_get_data
argument_list|(
name|G_OBJECT
argument_list|(
name|action
argument_list|)
argument_list|,
literal|"dock-window"
argument_list|)
decl_stmt|;
name|gtk_window_present
argument_list|(
name|dock_window
argument_list|)
expr_stmt|;
block|}
end_function

begin_function
name|void
DECL|function|windows_open_recent_cmd_callback (GtkAction * action,gpointer data)
name|windows_open_recent_cmd_callback
parameter_list|(
name|GtkAction
modifier|*
name|action
parameter_list|,
name|gpointer
name|data
parameter_list|)
block|{
name|GimpSessionInfo
modifier|*
name|info
decl_stmt|;
name|GimpDialogFactoryEntry
modifier|*
name|entry
decl_stmt|;
name|Gimp
modifier|*
name|gimp
decl_stmt|;
name|return_if_no_gimp
argument_list|(
name|gimp
argument_list|,
name|data
argument_list|)
expr_stmt|;
name|info
operator|=
name|g_object_get_data
argument_list|(
name|G_OBJECT
argument_list|(
name|action
argument_list|)
argument_list|,
literal|"info"
argument_list|)
expr_stmt|;
name|entry
operator|=
name|gimp_session_info_get_factory_entry
argument_list|(
name|info
argument_list|)
expr_stmt|;
if|if
condition|(
name|entry
operator|&&
name|strcmp
argument_list|(
literal|"gimp-toolbox-window"
argument_list|,
name|entry
operator|->
name|identifier
argument_list|)
operator|==
literal|0
operator|&&
name|dialogs_actions_toolbox_exists
argument_list|(
name|gimp
argument_list|)
condition|)
block|{
name|gimp_message
argument_list|(
name|gimp
argument_list|,
name|G_OBJECT
argument_list|(
name|action_data_get_widget
argument_list|(
name|data
argument_list|)
argument_list|)
argument_list|,
name|GIMP_MESSAGE_WARNING
argument_list|,
name|_
argument_list|(
literal|"The chosen recent dock contains a toolbox. Please "
literal|"close the currently open toolbox and try again."
argument_list|)
argument_list|)
expr_stmt|;
return|return;
block|}
name|g_object_ref
argument_list|(
name|info
argument_list|)
expr_stmt|;
name|gimp_container_remove
argument_list|(
name|global_recent_docks
argument_list|,
name|GIMP_OBJECT
argument_list|(
name|info
argument_list|)
argument_list|)
expr_stmt|;
name|gimp_dialog_factory_add_session_info
argument_list|(
name|gimp_dialog_factory_get_singleton
argument_list|()
argument_list|,
name|info
argument_list|)
expr_stmt|;
name|gimp_session_info_restore
argument_list|(
name|info
argument_list|,
name|gimp_dialog_factory_get_singleton
argument_list|()
argument_list|)
expr_stmt|;
name|g_object_unref
argument_list|(
name|info
argument_list|)
expr_stmt|;
block|}
end_function

end_unit

