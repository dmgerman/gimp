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
file|"core/gimpcontext.h"
end_include

begin_include
include|#
directive|include
file|"core/gimpimage.h"
end_include

begin_include
include|#
directive|include
file|"display/gimpdisplay.h"
end_include

begin_include
include|#
directive|include
file|"display/gimpdisplay-foreach.h"
end_include

begin_include
include|#
directive|include
file|"display/gimpdisplayshell.h"
end_include

begin_include
include|#
directive|include
file|"display/gimpdisplayshell-appearance.h"
end_include

begin_include
include|#
directive|include
file|"display/gimpdisplayshell-filter-dialog.h"
end_include

begin_include
include|#
directive|include
file|"display/gimpdisplayshell-scale.h"
end_include

begin_include
include|#
directive|include
file|"widgets/gimpactiongroup.h"
end_include

begin_include
include|#
directive|include
file|"widgets/gimpdock.h"
end_include

begin_include
include|#
directive|include
file|"widgets/gimpdialogfactory.h"
end_include

begin_include
include|#
directive|include
file|"widgets/gimpuimanager.h"
end_include

begin_include
include|#
directive|include
file|"gui/dialogs.h"
end_include

begin_include
include|#
directive|include
file|"gui/info-dialog.h"
end_include

begin_include
include|#
directive|include
file|"gui/info-window.h"
end_include

begin_include
include|#
directive|include
file|"actions.h"
end_include

begin_include
include|#
directive|include
file|"view-commands.h"
end_include

begin_define
DECL|macro|return_if_no_display (gdisp,data)
define|#
directive|define
name|return_if_no_display
parameter_list|(
name|gdisp
parameter_list|,
name|data
parameter_list|)
define|\
value|gdisp = action_data_get_display (data); \   if (! gdisp) \     return
end_define

begin_define
DECL|macro|SET_ACTIVE (manager,group_name,action_name,active)
define|#
directive|define
name|SET_ACTIVE
parameter_list|(
name|manager
parameter_list|,
name|group_name
parameter_list|,
name|action_name
parameter_list|,
name|active
parameter_list|)
define|\
value|{ GimpActionGroup *group = \       gimp_ui_manager_get_action_group (manager, group_name); \     gimp_action_group_set_action_active (group, action_name, active); }
end_define

begin_define
DECL|macro|IS_ACTIVE_DISPLAY (gdisp)
define|#
directive|define
name|IS_ACTIVE_DISPLAY
parameter_list|(
name|gdisp
parameter_list|)
define|\
value|((gdisp) == \    gimp_context_get_display (gimp_get_user_context ((gdisp)->gimage->gimp)))
end_define

begin_function
name|void
DECL|function|view_zoom_out_cmd_callback (GtkAction * action,gpointer data)
name|view_zoom_out_cmd_callback
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
name|gdisp
decl_stmt|;
name|return_if_no_display
argument_list|(
name|gdisp
argument_list|,
name|data
argument_list|)
expr_stmt|;
name|gimp_display_shell_scale
argument_list|(
name|GIMP_DISPLAY_SHELL
argument_list|(
name|gdisp
operator|->
name|shell
argument_list|)
argument_list|,
name|GIMP_ZOOM_OUT
argument_list|,
literal|0.0
argument_list|)
expr_stmt|;
block|}
end_function

begin_function
name|void
DECL|function|view_zoom_in_cmd_callback (GtkAction * action,gpointer data)
name|view_zoom_in_cmd_callback
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
name|gdisp
decl_stmt|;
name|return_if_no_display
argument_list|(
name|gdisp
argument_list|,
name|data
argument_list|)
expr_stmt|;
name|gimp_display_shell_scale
argument_list|(
name|GIMP_DISPLAY_SHELL
argument_list|(
name|gdisp
operator|->
name|shell
argument_list|)
argument_list|,
name|GIMP_ZOOM_IN
argument_list|,
literal|0.0
argument_list|)
expr_stmt|;
block|}
end_function

begin_function
name|void
DECL|function|view_zoom_fit_cmd_callback (GtkAction * action,gpointer data)
name|view_zoom_fit_cmd_callback
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
name|gdisp
decl_stmt|;
name|return_if_no_display
argument_list|(
name|gdisp
argument_list|,
name|data
argument_list|)
expr_stmt|;
name|gimp_display_shell_scale_fit
argument_list|(
name|GIMP_DISPLAY_SHELL
argument_list|(
name|gdisp
operator|->
name|shell
argument_list|)
argument_list|)
expr_stmt|;
block|}
end_function

begin_function
name|void
DECL|function|view_zoom_cmd_callback (GtkAction * action,GtkAction * current,gpointer data)
name|view_zoom_cmd_callback
parameter_list|(
name|GtkAction
modifier|*
name|action
parameter_list|,
name|GtkAction
modifier|*
name|current
parameter_list|,
name|gpointer
name|data
parameter_list|)
block|{
name|GimpDisplay
modifier|*
name|gdisp
decl_stmt|;
name|GimpDisplayShell
modifier|*
name|shell
decl_stmt|;
name|gint
name|value
decl_stmt|;
name|return_if_no_display
argument_list|(
name|gdisp
argument_list|,
name|data
argument_list|)
expr_stmt|;
name|shell
operator|=
name|GIMP_DISPLAY_SHELL
argument_list|(
name|gdisp
operator|->
name|shell
argument_list|)
expr_stmt|;
name|value
operator|=
name|gtk_radio_action_get_current_value
argument_list|(
name|GTK_RADIO_ACTION
argument_list|(
name|action
argument_list|)
argument_list|)
expr_stmt|;
if|if
condition|(
name|value
operator|==
literal|0
comment|/* Other... */
condition|)
block|{
comment|/* check if we are activated by the user        * or from view_actions_set_zoom()        */
if|if
condition|(
name|shell
operator|->
name|scale
operator|!=
name|shell
operator|->
name|other_scale
condition|)
name|gimp_display_shell_scale_dialog
argument_list|(
name|shell
argument_list|)
expr_stmt|;
block|}
else|else
block|{
if|if
condition|(
name|fabs
argument_list|(
name|value
operator|-
name|shell
operator|->
name|scale
argument_list|)
operator|>
literal|0.0001
condition|)
name|gimp_display_shell_scale
argument_list|(
name|shell
argument_list|,
name|GIMP_ZOOM_TO
argument_list|,
operator|(
name|gdouble
operator|)
name|value
operator|/
literal|10000
argument_list|)
expr_stmt|;
block|}
block|}
end_function

begin_function
name|void
DECL|function|view_dot_for_dot_cmd_callback (GtkAction * action,gpointer data)
name|view_dot_for_dot_cmd_callback
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
name|gdisp
decl_stmt|;
name|GimpDisplayShell
modifier|*
name|shell
decl_stmt|;
name|gboolean
name|active
decl_stmt|;
name|return_if_no_display
argument_list|(
name|gdisp
argument_list|,
name|data
argument_list|)
expr_stmt|;
name|shell
operator|=
name|GIMP_DISPLAY_SHELL
argument_list|(
name|gdisp
operator|->
name|shell
argument_list|)
expr_stmt|;
name|active
operator|=
name|gtk_toggle_action_get_active
argument_list|(
name|GTK_TOGGLE_ACTION
argument_list|(
name|action
argument_list|)
argument_list|)
expr_stmt|;
if|if
condition|(
name|active
operator|!=
name|shell
operator|->
name|dot_for_dot
condition|)
block|{
name|gimp_display_shell_scale_set_dot_for_dot
argument_list|(
name|shell
argument_list|,
name|active
argument_list|)
expr_stmt|;
name|SET_ACTIVE
argument_list|(
name|shell
operator|->
name|menubar_manager
argument_list|,
literal|"view"
argument_list|,
literal|"view-dot-for-dot"
argument_list|,
name|shell
operator|->
name|dot_for_dot
argument_list|)
expr_stmt|;
if|if
condition|(
name|IS_ACTIVE_DISPLAY
argument_list|(
name|gdisp
argument_list|)
condition|)
name|SET_ACTIVE
argument_list|(
name|shell
operator|->
name|popup_manager
argument_list|,
literal|"view"
argument_list|,
literal|"view-dot-for-dot"
argument_list|,
name|shell
operator|->
name|dot_for_dot
argument_list|)
expr_stmt|;
block|}
block|}
end_function

begin_function
name|void
DECL|function|view_info_window_cmd_callback (GtkAction * action,gpointer data)
name|view_info_window_cmd_callback
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
name|gdisp
decl_stmt|;
name|GimpDisplayShell
modifier|*
name|shell
decl_stmt|;
name|return_if_no_display
argument_list|(
name|gdisp
argument_list|,
name|data
argument_list|)
expr_stmt|;
name|shell
operator|=
name|GIMP_DISPLAY_SHELL
argument_list|(
name|gdisp
operator|->
name|shell
argument_list|)
expr_stmt|;
if|if
condition|(
name|GIMP_GUI_CONFIG
argument_list|(
name|gdisp
operator|->
name|gimage
operator|->
name|gimp
operator|->
name|config
argument_list|)
operator|->
name|info_window_per_display
condition|)
block|{
if|if
condition|(
operator|!
name|shell
operator|->
name|info_dialog
condition|)
name|shell
operator|->
name|info_dialog
operator|=
name|info_window_create
argument_list|(
name|gdisp
argument_list|)
expr_stmt|;
comment|/* To update the fields of the info window for the first time. *        * It's no use updating it in info_window_create() because the *        * pointer of the info window is not present in the shell yet. */
name|info_window_update
argument_list|(
name|gdisp
argument_list|)
expr_stmt|;
name|info_dialog_present
argument_list|(
name|shell
operator|->
name|info_dialog
argument_list|)
expr_stmt|;
block|}
else|else
block|{
name|info_window_follow_auto
argument_list|(
name|gdisp
operator|->
name|gimage
operator|->
name|gimp
argument_list|)
expr_stmt|;
block|}
block|}
end_function

begin_function
name|void
DECL|function|view_navigation_window_cmd_callback (GtkAction * action,gpointer data)
name|view_navigation_window_cmd_callback
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
name|gdisp
decl_stmt|;
name|GimpDisplayShell
modifier|*
name|shell
decl_stmt|;
name|return_if_no_display
argument_list|(
name|gdisp
argument_list|,
name|data
argument_list|)
expr_stmt|;
name|shell
operator|=
name|GIMP_DISPLAY_SHELL
argument_list|(
name|gdisp
operator|->
name|shell
argument_list|)
expr_stmt|;
name|gimp_dialog_factory_dialog_raise
argument_list|(
name|global_dock_factory
argument_list|,
name|gtk_widget_get_screen
argument_list|(
name|gdisp
operator|->
name|shell
argument_list|)
argument_list|,
literal|"gimp-navigation-view"
argument_list|,
operator|-
literal|1
argument_list|)
expr_stmt|;
block|}
end_function

begin_function
name|void
DECL|function|view_display_filters_cmd_callback (GtkAction * action,gpointer data)
name|view_display_filters_cmd_callback
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
name|gdisp
decl_stmt|;
name|GimpDisplayShell
modifier|*
name|shell
decl_stmt|;
name|return_if_no_display
argument_list|(
name|gdisp
argument_list|,
name|data
argument_list|)
expr_stmt|;
name|shell
operator|=
name|GIMP_DISPLAY_SHELL
argument_list|(
name|gdisp
operator|->
name|shell
argument_list|)
expr_stmt|;
if|if
condition|(
operator|!
name|shell
operator|->
name|filters_dialog
condition|)
block|{
name|shell
operator|->
name|filters_dialog
operator|=
name|gimp_display_shell_filter_dialog_new
argument_list|(
name|shell
argument_list|)
expr_stmt|;
name|g_signal_connect
argument_list|(
name|shell
operator|->
name|filters_dialog
argument_list|,
literal|"destroy"
argument_list|,
name|G_CALLBACK
argument_list|(
name|gtk_widget_destroyed
argument_list|)
argument_list|,
operator|&
name|shell
operator|->
name|filters_dialog
argument_list|)
expr_stmt|;
block|}
name|gtk_window_present
argument_list|(
name|GTK_WINDOW
argument_list|(
name|shell
operator|->
name|filters_dialog
argument_list|)
argument_list|)
expr_stmt|;
block|}
end_function

begin_function
name|void
DECL|function|view_toggle_selection_cmd_callback (GtkAction * action,gpointer data)
name|view_toggle_selection_cmd_callback
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
name|gdisp
decl_stmt|;
name|GimpDisplayShell
modifier|*
name|shell
decl_stmt|;
name|gboolean
name|active
decl_stmt|;
name|return_if_no_display
argument_list|(
name|gdisp
argument_list|,
name|data
argument_list|)
expr_stmt|;
name|shell
operator|=
name|GIMP_DISPLAY_SHELL
argument_list|(
name|gdisp
operator|->
name|shell
argument_list|)
expr_stmt|;
name|active
operator|=
name|gtk_toggle_action_get_active
argument_list|(
name|GTK_TOGGLE_ACTION
argument_list|(
name|action
argument_list|)
argument_list|)
expr_stmt|;
name|gimp_display_shell_set_show_selection
argument_list|(
name|shell
argument_list|,
name|active
argument_list|)
expr_stmt|;
block|}
end_function

begin_function
name|void
DECL|function|view_toggle_layer_boundary_cmd_callback (GtkAction * action,gpointer data)
name|view_toggle_layer_boundary_cmd_callback
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
name|gdisp
decl_stmt|;
name|GimpDisplayShell
modifier|*
name|shell
decl_stmt|;
name|gboolean
name|active
decl_stmt|;
name|return_if_no_display
argument_list|(
name|gdisp
argument_list|,
name|data
argument_list|)
expr_stmt|;
name|shell
operator|=
name|GIMP_DISPLAY_SHELL
argument_list|(
name|gdisp
operator|->
name|shell
argument_list|)
expr_stmt|;
name|active
operator|=
name|gtk_toggle_action_get_active
argument_list|(
name|GTK_TOGGLE_ACTION
argument_list|(
name|action
argument_list|)
argument_list|)
expr_stmt|;
name|gimp_display_shell_set_show_layer
argument_list|(
name|shell
argument_list|,
name|active
argument_list|)
expr_stmt|;
block|}
end_function

begin_function
name|void
DECL|function|view_toggle_menubar_cmd_callback (GtkAction * action,gpointer data)
name|view_toggle_menubar_cmd_callback
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
name|gdisp
decl_stmt|;
name|GimpDisplayShell
modifier|*
name|shell
decl_stmt|;
name|gboolean
name|active
decl_stmt|;
name|return_if_no_display
argument_list|(
name|gdisp
argument_list|,
name|data
argument_list|)
expr_stmt|;
name|shell
operator|=
name|GIMP_DISPLAY_SHELL
argument_list|(
name|gdisp
operator|->
name|shell
argument_list|)
expr_stmt|;
name|active
operator|=
name|gtk_toggle_action_get_active
argument_list|(
name|GTK_TOGGLE_ACTION
argument_list|(
name|action
argument_list|)
argument_list|)
expr_stmt|;
name|gimp_display_shell_set_show_menubar
argument_list|(
name|shell
argument_list|,
name|active
argument_list|)
expr_stmt|;
block|}
end_function

begin_function
name|void
DECL|function|view_toggle_rulers_cmd_callback (GtkAction * action,gpointer data)
name|view_toggle_rulers_cmd_callback
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
name|gdisp
decl_stmt|;
name|GimpDisplayShell
modifier|*
name|shell
decl_stmt|;
name|gboolean
name|active
decl_stmt|;
name|return_if_no_display
argument_list|(
name|gdisp
argument_list|,
name|data
argument_list|)
expr_stmt|;
name|shell
operator|=
name|GIMP_DISPLAY_SHELL
argument_list|(
name|gdisp
operator|->
name|shell
argument_list|)
expr_stmt|;
name|active
operator|=
name|gtk_toggle_action_get_active
argument_list|(
name|GTK_TOGGLE_ACTION
argument_list|(
name|action
argument_list|)
argument_list|)
expr_stmt|;
name|gimp_display_shell_set_show_rulers
argument_list|(
name|shell
argument_list|,
name|active
argument_list|)
expr_stmt|;
block|}
end_function

begin_function
name|void
DECL|function|view_toggle_scrollbars_cmd_callback (GtkAction * action,gpointer data)
name|view_toggle_scrollbars_cmd_callback
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
name|gdisp
decl_stmt|;
name|GimpDisplayShell
modifier|*
name|shell
decl_stmt|;
name|gboolean
name|active
decl_stmt|;
name|return_if_no_display
argument_list|(
name|gdisp
argument_list|,
name|data
argument_list|)
expr_stmt|;
name|shell
operator|=
name|GIMP_DISPLAY_SHELL
argument_list|(
name|gdisp
operator|->
name|shell
argument_list|)
expr_stmt|;
name|active
operator|=
name|gtk_toggle_action_get_active
argument_list|(
name|GTK_TOGGLE_ACTION
argument_list|(
name|action
argument_list|)
argument_list|)
expr_stmt|;
name|gimp_display_shell_set_show_scrollbars
argument_list|(
name|shell
argument_list|,
name|active
argument_list|)
expr_stmt|;
block|}
end_function

begin_function
name|void
DECL|function|view_toggle_statusbar_cmd_callback (GtkAction * action,gpointer data)
name|view_toggle_statusbar_cmd_callback
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
name|gdisp
decl_stmt|;
name|GimpDisplayShell
modifier|*
name|shell
decl_stmt|;
name|gboolean
name|active
decl_stmt|;
name|return_if_no_display
argument_list|(
name|gdisp
argument_list|,
name|data
argument_list|)
expr_stmt|;
name|shell
operator|=
name|GIMP_DISPLAY_SHELL
argument_list|(
name|gdisp
operator|->
name|shell
argument_list|)
expr_stmt|;
name|active
operator|=
name|gtk_toggle_action_get_active
argument_list|(
name|GTK_TOGGLE_ACTION
argument_list|(
name|action
argument_list|)
argument_list|)
expr_stmt|;
name|gimp_display_shell_set_show_statusbar
argument_list|(
name|shell
argument_list|,
name|active
argument_list|)
expr_stmt|;
block|}
end_function

begin_function
name|void
DECL|function|view_toggle_guides_cmd_callback (GtkAction * action,gpointer data)
name|view_toggle_guides_cmd_callback
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
name|gdisp
decl_stmt|;
name|GimpDisplayShell
modifier|*
name|shell
decl_stmt|;
name|gboolean
name|active
decl_stmt|;
name|return_if_no_display
argument_list|(
name|gdisp
argument_list|,
name|data
argument_list|)
expr_stmt|;
name|shell
operator|=
name|GIMP_DISPLAY_SHELL
argument_list|(
name|gdisp
operator|->
name|shell
argument_list|)
expr_stmt|;
name|active
operator|=
name|gtk_toggle_action_get_active
argument_list|(
name|GTK_TOGGLE_ACTION
argument_list|(
name|action
argument_list|)
argument_list|)
expr_stmt|;
name|gimp_display_shell_set_show_guides
argument_list|(
name|shell
argument_list|,
name|active
argument_list|)
expr_stmt|;
block|}
end_function

begin_function
name|void
DECL|function|view_snap_to_guides_cmd_callback (GtkAction * action,gpointer data)
name|view_snap_to_guides_cmd_callback
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
name|gdisp
decl_stmt|;
name|GimpDisplayShell
modifier|*
name|shell
decl_stmt|;
name|gboolean
name|active
decl_stmt|;
name|return_if_no_display
argument_list|(
name|gdisp
argument_list|,
name|data
argument_list|)
expr_stmt|;
name|shell
operator|=
name|GIMP_DISPLAY_SHELL
argument_list|(
name|gdisp
operator|->
name|shell
argument_list|)
expr_stmt|;
name|active
operator|=
name|gtk_toggle_action_get_active
argument_list|(
name|GTK_TOGGLE_ACTION
argument_list|(
name|action
argument_list|)
argument_list|)
expr_stmt|;
name|gimp_display_shell_set_snap_to_guides
argument_list|(
name|shell
argument_list|,
name|active
argument_list|)
expr_stmt|;
block|}
end_function

begin_function
name|void
DECL|function|view_toggle_grid_cmd_callback (GtkAction * action,gpointer data)
name|view_toggle_grid_cmd_callback
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
name|gdisp
decl_stmt|;
name|GimpDisplayShell
modifier|*
name|shell
decl_stmt|;
name|gboolean
name|active
decl_stmt|;
name|return_if_no_display
argument_list|(
name|gdisp
argument_list|,
name|data
argument_list|)
expr_stmt|;
name|shell
operator|=
name|GIMP_DISPLAY_SHELL
argument_list|(
name|gdisp
operator|->
name|shell
argument_list|)
expr_stmt|;
name|active
operator|=
name|gtk_toggle_action_get_active
argument_list|(
name|GTK_TOGGLE_ACTION
argument_list|(
name|action
argument_list|)
argument_list|)
expr_stmt|;
name|gimp_display_shell_set_show_grid
argument_list|(
name|shell
argument_list|,
name|active
argument_list|)
expr_stmt|;
block|}
end_function

begin_function
name|void
DECL|function|view_snap_to_grid_cmd_callback (GtkAction * action,gpointer data)
name|view_snap_to_grid_cmd_callback
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
name|gdisp
decl_stmt|;
name|GimpDisplayShell
modifier|*
name|shell
decl_stmt|;
name|gboolean
name|active
decl_stmt|;
name|return_if_no_display
argument_list|(
name|gdisp
argument_list|,
name|data
argument_list|)
expr_stmt|;
name|shell
operator|=
name|GIMP_DISPLAY_SHELL
argument_list|(
name|gdisp
operator|->
name|shell
argument_list|)
expr_stmt|;
name|active
operator|=
name|gtk_toggle_action_get_active
argument_list|(
name|GTK_TOGGLE_ACTION
argument_list|(
name|action
argument_list|)
argument_list|)
expr_stmt|;
name|gimp_display_shell_set_snap_to_grid
argument_list|(
name|shell
argument_list|,
name|active
argument_list|)
expr_stmt|;
block|}
end_function

begin_function
name|void
DECL|function|view_new_view_cmd_callback (GtkAction * action,gpointer data)
name|view_new_view_cmd_callback
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
name|gdisp
decl_stmt|;
name|return_if_no_display
argument_list|(
name|gdisp
argument_list|,
name|data
argument_list|)
expr_stmt|;
name|gimp_create_display
argument_list|(
name|gdisp
operator|->
name|gimage
operator|->
name|gimp
argument_list|,
name|gdisp
operator|->
name|gimage
argument_list|,
name|GIMP_DISPLAY_SHELL
argument_list|(
name|gdisp
operator|->
name|shell
argument_list|)
operator|->
name|scale
argument_list|)
expr_stmt|;
block|}
end_function

begin_function
name|void
DECL|function|view_shrink_wrap_cmd_callback (GtkAction * action,gpointer data)
name|view_shrink_wrap_cmd_callback
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
name|gdisp
decl_stmt|;
name|return_if_no_display
argument_list|(
name|gdisp
argument_list|,
name|data
argument_list|)
expr_stmt|;
name|gimp_display_shell_scale_shrink_wrap
argument_list|(
name|GIMP_DISPLAY_SHELL
argument_list|(
name|gdisp
operator|->
name|shell
argument_list|)
argument_list|)
expr_stmt|;
block|}
end_function

begin_function
name|void
DECL|function|view_fullscreen_cmd_callback (GtkAction * action,gpointer data)
name|view_fullscreen_cmd_callback
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
name|gdisp
decl_stmt|;
name|GimpDisplayShell
modifier|*
name|shell
decl_stmt|;
name|gboolean
name|active
decl_stmt|;
name|gboolean
name|fullscreen
decl_stmt|;
name|return_if_no_display
argument_list|(
name|gdisp
argument_list|,
name|data
argument_list|)
expr_stmt|;
name|shell
operator|=
name|GIMP_DISPLAY_SHELL
argument_list|(
name|gdisp
operator|->
name|shell
argument_list|)
expr_stmt|;
name|active
operator|=
name|gtk_toggle_action_get_active
argument_list|(
name|GTK_TOGGLE_ACTION
argument_list|(
name|action
argument_list|)
argument_list|)
expr_stmt|;
name|gimp_display_shell_set_fullscreen
argument_list|(
name|shell
argument_list|,
name|active
argument_list|)
expr_stmt|;
name|fullscreen
operator|=
operator|(
name|shell
operator|->
name|window_state
operator|&
name|GDK_WINDOW_STATE_FULLSCREEN
operator|)
operator|!=
literal|0
expr_stmt|;
if|if
condition|(
name|active
operator|!=
name|fullscreen
condition|)
block|{
name|SET_ACTIVE
argument_list|(
name|shell
operator|->
name|menubar_manager
argument_list|,
literal|"view"
argument_list|,
literal|"view-fullscreen"
argument_list|,
name|fullscreen
argument_list|)
expr_stmt|;
if|if
condition|(
name|IS_ACTIVE_DISPLAY
argument_list|(
name|gdisp
argument_list|)
condition|)
name|SET_ACTIVE
argument_list|(
name|shell
operator|->
name|popup_manager
argument_list|,
literal|"view"
argument_list|,
literal|"view-fullscreen"
argument_list|,
name|fullscreen
argument_list|)
expr_stmt|;
block|}
block|}
end_function

begin_function
specifier|static
name|void
DECL|function|view_change_screen_confirm_callback (GtkWidget * query_box,gint value,gpointer data)
name|view_change_screen_confirm_callback
parameter_list|(
name|GtkWidget
modifier|*
name|query_box
parameter_list|,
name|gint
name|value
parameter_list|,
name|gpointer
name|data
parameter_list|)
block|{
name|GdkScreen
modifier|*
name|screen
decl_stmt|;
name|screen
operator|=
name|gdk_display_get_screen
argument_list|(
name|gtk_widget_get_display
argument_list|(
name|GTK_WIDGET
argument_list|(
name|data
argument_list|)
argument_list|)
argument_list|,
name|value
argument_list|)
expr_stmt|;
if|if
condition|(
name|screen
condition|)
name|gtk_window_set_screen
argument_list|(
name|GTK_WINDOW
argument_list|(
name|data
argument_list|)
argument_list|,
name|screen
argument_list|)
expr_stmt|;
block|}
end_function

begin_function
specifier|static
name|void
DECL|function|view_change_screen_destroy_callback (GtkWidget * query_box,GtkWidget * shell)
name|view_change_screen_destroy_callback
parameter_list|(
name|GtkWidget
modifier|*
name|query_box
parameter_list|,
name|GtkWidget
modifier|*
name|shell
parameter_list|)
block|{
name|g_object_set_data
argument_list|(
name|G_OBJECT
argument_list|(
name|shell
argument_list|)
argument_list|,
literal|"gimp-change-screen-dialog"
argument_list|,
name|NULL
argument_list|)
expr_stmt|;
block|}
end_function

begin_function
name|void
DECL|function|view_change_screen_cmd_callback (GtkAction * action,gpointer data)
name|view_change_screen_cmd_callback
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
name|gdisp
decl_stmt|;
name|GdkScreen
modifier|*
name|screen
decl_stmt|;
name|GdkDisplay
modifier|*
name|display
decl_stmt|;
name|gint
name|cur_screen
decl_stmt|;
name|gint
name|num_screens
decl_stmt|;
name|GtkWidget
modifier|*
name|qbox
decl_stmt|;
name|return_if_no_display
argument_list|(
name|gdisp
argument_list|,
name|data
argument_list|)
expr_stmt|;
name|qbox
operator|=
name|g_object_get_data
argument_list|(
name|G_OBJECT
argument_list|(
name|gdisp
operator|->
name|shell
argument_list|)
argument_list|,
literal|"gimp-change-screen-dialog"
argument_list|)
expr_stmt|;
if|if
condition|(
name|qbox
condition|)
block|{
name|gtk_window_present
argument_list|(
name|GTK_WINDOW
argument_list|(
name|qbox
argument_list|)
argument_list|)
expr_stmt|;
return|return;
block|}
name|screen
operator|=
name|gtk_widget_get_screen
argument_list|(
name|gdisp
operator|->
name|shell
argument_list|)
expr_stmt|;
name|display
operator|=
name|gtk_widget_get_display
argument_list|(
name|gdisp
operator|->
name|shell
argument_list|)
expr_stmt|;
name|cur_screen
operator|=
name|gdk_screen_get_number
argument_list|(
name|screen
argument_list|)
expr_stmt|;
name|num_screens
operator|=
name|gdk_display_get_n_screens
argument_list|(
name|display
argument_list|)
expr_stmt|;
name|qbox
operator|=
name|gimp_query_int_box
argument_list|(
literal|"Move Display to Screen"
argument_list|,
name|gdisp
operator|->
name|shell
argument_list|,
name|NULL
argument_list|,
literal|0
argument_list|,
literal|"Enter destination screen"
argument_list|,
name|cur_screen
argument_list|,
literal|0
argument_list|,
name|num_screens
operator|-
literal|1
argument_list|,
name|G_OBJECT
argument_list|(
name|gdisp
operator|->
name|shell
argument_list|)
argument_list|,
literal|"destroy"
argument_list|,
name|view_change_screen_confirm_callback
argument_list|,
name|gdisp
operator|->
name|shell
argument_list|)
expr_stmt|;
name|g_object_set_data
argument_list|(
name|G_OBJECT
argument_list|(
name|gdisp
operator|->
name|shell
argument_list|)
argument_list|,
literal|"gimp-change-screen-dialog"
argument_list|,
name|qbox
argument_list|)
expr_stmt|;
name|g_signal_connect
argument_list|(
name|qbox
argument_list|,
literal|"destroy"
argument_list|,
name|G_CALLBACK
argument_list|(
name|view_change_screen_destroy_callback
argument_list|)
argument_list|,
name|gdisp
operator|->
name|shell
argument_list|)
expr_stmt|;
name|gtk_widget_show
argument_list|(
name|qbox
argument_list|)
expr_stmt|;
block|}
end_function

end_unit

