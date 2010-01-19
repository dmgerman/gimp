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
file|"windows-commands.h"
end_include

begin_function
name|void
DECL|function|windows_show_toolbox_cmd_callback (GtkAction * action,gpointer data)
name|windows_show_toolbox_cmd_callback
parameter_list|(
name|GtkAction
modifier|*
name|action
parameter_list|,
name|gpointer
name|data
parameter_list|)
block|{
name|windows_show_toolbox
argument_list|()
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
init|=
name|NULL
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
init|=
name|g_object_get_data
argument_list|(
name|G_OBJECT
argument_list|(
name|action
argument_list|)
argument_list|,
literal|"info"
argument_list|)
decl_stmt|;
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
name|global_dock_factory
argument_list|,
name|info
argument_list|)
expr_stmt|;
name|gimp_session_info_restore
argument_list|(
name|info
argument_list|,
name|global_dock_factory
argument_list|)
expr_stmt|;
name|gimp_session_info_clear_info
argument_list|(
name|info
argument_list|)
expr_stmt|;
block|}
end_function

begin_function
name|void
DECL|function|windows_show_toolbox (void)
name|windows_show_toolbox
parameter_list|(
name|void
parameter_list|)
block|{
name|GtkWidget
modifier|*
name|toolbox
init|=
name|NULL
decl_stmt|;
if|if
condition|(
operator|!
name|gimp_dialog_factory_get_open_dialogs
argument_list|(
name|global_toolbox_factory
argument_list|)
condition|)
block|{
name|toolbox
operator|=
name|gimp_dialog_factory_dock_with_window_new
argument_list|(
name|global_toolbox_factory
argument_list|,
name|gdk_screen_get_default
argument_list|()
argument_list|)
expr_stmt|;
name|gtk_widget_show
argument_list|(
name|toolbox
argument_list|)
expr_stmt|;
block|}
else|else
block|{
name|toolbox
operator|=
name|dialogs_get_toolbox
argument_list|()
expr_stmt|;
if|if
condition|(
name|toolbox
condition|)
name|gtk_window_present
argument_list|(
name|GTK_WINDOW
argument_list|(
name|toolbox
argument_list|)
argument_list|)
expr_stmt|;
block|}
block|}
end_function

end_unit

