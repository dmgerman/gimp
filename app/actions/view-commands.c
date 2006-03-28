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
file|"display/gimpdisplayoptions.h"
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
file|"display/gimpdisplayshell-close.h"
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
file|"widgets/gimpcolordialog.h"
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
file|"view-commands.h"
end_include

begin_include
include|#
directive|include
file|"gimp-intl.h"
end_include

begin_define
DECL|macro|SET_ACTIVE (manager,action_name,active)
define|#
directive|define
name|SET_ACTIVE
parameter_list|(
name|manager
parameter_list|,
name|action_name
parameter_list|,
name|active
parameter_list|)
define|\
value|{ GimpActionGroup *group = \       gimp_ui_manager_get_action_group (manager, "view"); \     gimp_action_group_set_action_active (group, action_name, active); }
end_define

begin_define
DECL|macro|IS_ACTIVE_DISPLAY (display)
define|#
directive|define
name|IS_ACTIVE_DISPLAY
parameter_list|(
name|display
parameter_list|)
define|\
value|((display) == \    gimp_context_get_display (gimp_get_user_context ((display)->image->gimp)))
end_define

begin_comment
comment|/*  local function prototypes  */
end_comment

begin_function_decl
specifier|static
name|void
name|view_padding_color_dialog_update
parameter_list|(
name|GimpColorDialog
modifier|*
name|dialog
parameter_list|,
specifier|const
name|GimpRGB
modifier|*
name|color
parameter_list|,
name|GimpColorDialogState
name|state
parameter_list|,
name|GimpDisplayShell
modifier|*
name|shell
parameter_list|)
function_decl|;
end_function_decl

begin_comment
comment|/*  public functions  */
end_comment

begin_function
name|void
DECL|function|view_new_cmd_callback (GtkAction * action,gpointer data)
name|view_new_cmd_callback
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
name|GimpDisplayShell
modifier|*
name|shell
decl_stmt|;
name|return_if_no_display
argument_list|(
name|display
argument_list|,
name|data
argument_list|)
expr_stmt|;
name|shell
operator|=
name|GIMP_DISPLAY_SHELL
argument_list|(
name|display
operator|->
name|shell
argument_list|)
expr_stmt|;
name|gimp_create_display
argument_list|(
name|display
operator|->
name|image
operator|->
name|gimp
argument_list|,
name|display
operator|->
name|image
argument_list|,
name|shell
operator|->
name|unit
argument_list|,
name|gimp_zoom_model_get_factor
argument_list|(
name|shell
operator|->
name|zoom
argument_list|)
argument_list|)
expr_stmt|;
block|}
end_function

begin_function
name|void
DECL|function|view_zoom_fit_in_cmd_callback (GtkAction * action,gpointer data)
name|view_zoom_fit_in_cmd_callback
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
name|return_if_no_display
argument_list|(
name|display
argument_list|,
name|data
argument_list|)
expr_stmt|;
name|gimp_display_shell_scale_fit_in
argument_list|(
name|GIMP_DISPLAY_SHELL
argument_list|(
name|display
operator|->
name|shell
argument_list|)
argument_list|)
expr_stmt|;
block|}
end_function

begin_function
name|void
DECL|function|view_zoom_fit_to_cmd_callback (GtkAction * action,gpointer data)
name|view_zoom_fit_to_cmd_callback
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
name|return_if_no_display
argument_list|(
name|display
argument_list|,
name|data
argument_list|)
expr_stmt|;
name|gimp_display_shell_scale_fit_to
argument_list|(
name|GIMP_DISPLAY_SHELL
argument_list|(
name|display
operator|->
name|shell
argument_list|)
argument_list|)
expr_stmt|;
block|}
end_function

begin_function
name|void
DECL|function|view_zoom_cmd_callback (GtkAction * action,gint value,gpointer data)
name|view_zoom_cmd_callback
parameter_list|(
name|GtkAction
modifier|*
name|action
parameter_list|,
name|gint
name|value
parameter_list|,
name|gpointer
name|data
parameter_list|)
block|{
name|GimpDisplay
modifier|*
name|display
decl_stmt|;
name|GimpDisplayShell
modifier|*
name|shell
decl_stmt|;
name|return_if_no_display
argument_list|(
name|display
argument_list|,
name|data
argument_list|)
expr_stmt|;
name|shell
operator|=
name|GIMP_DISPLAY_SHELL
argument_list|(
name|display
operator|->
name|shell
argument_list|)
expr_stmt|;
switch|switch
condition|(
operator|(
name|GimpActionSelectType
operator|)
name|value
condition|)
block|{
case|case
name|GIMP_ACTION_SELECT_FIRST
case|:
name|gimp_display_shell_scale
argument_list|(
name|shell
argument_list|,
name|GIMP_ZOOM_OUT_MAX
argument_list|,
literal|0.0
argument_list|)
expr_stmt|;
break|break;
case|case
name|GIMP_ACTION_SELECT_LAST
case|:
name|gimp_display_shell_scale
argument_list|(
name|shell
argument_list|,
name|GIMP_ZOOM_IN_MAX
argument_list|,
literal|0.0
argument_list|)
expr_stmt|;
break|break;
case|case
name|GIMP_ACTION_SELECT_PREVIOUS
case|:
name|gimp_display_shell_scale
argument_list|(
name|shell
argument_list|,
name|GIMP_ZOOM_OUT
argument_list|,
literal|0.0
argument_list|)
expr_stmt|;
break|break;
case|case
name|GIMP_ACTION_SELECT_NEXT
case|:
name|gimp_display_shell_scale
argument_list|(
name|shell
argument_list|,
name|GIMP_ZOOM_IN
argument_list|,
literal|0.0
argument_list|)
expr_stmt|;
break|break;
case|case
name|GIMP_ACTION_SELECT_SKIP_PREVIOUS
case|:
name|gimp_display_shell_scale
argument_list|(
name|shell
argument_list|,
name|GIMP_ZOOM_OUT_MORE
argument_list|,
literal|0.0
argument_list|)
expr_stmt|;
break|break;
case|case
name|GIMP_ACTION_SELECT_SKIP_NEXT
case|:
name|gimp_display_shell_scale
argument_list|(
name|shell
argument_list|,
name|GIMP_ZOOM_IN_MORE
argument_list|,
literal|0.0
argument_list|)
expr_stmt|;
break|break;
default|default:
block|{
name|gdouble
name|scale
init|=
name|gimp_zoom_model_get_factor
argument_list|(
name|shell
operator|->
name|zoom
argument_list|)
decl_stmt|;
name|scale
operator|=
name|action_select_value
argument_list|(
operator|(
name|GimpActionSelectType
operator|)
name|value
argument_list|,
name|scale
argument_list|,
literal|0.0
argument_list|,
literal|512.0
argument_list|,
literal|1.0
argument_list|,
literal|16.0
argument_list|,
name|FALSE
argument_list|)
expr_stmt|;
comment|/* min = 1.0 / 256,  max = 256.0                */
comment|/* scale = min *  (max / min)**(i/n), i = 0..n  */
name|scale
operator|=
name|pow
argument_list|(
literal|65536.0
argument_list|,
name|scale
operator|/
literal|512.0
argument_list|)
operator|/
literal|256.0
expr_stmt|;
name|gimp_display_shell_scale
argument_list|(
name|shell
argument_list|,
name|GIMP_ZOOM_TO
argument_list|,
name|scale
argument_list|)
expr_stmt|;
break|break;
block|}
block|}
block|}
end_function

begin_function
name|void
DECL|function|view_zoom_explicit_cmd_callback (GtkAction * action,GtkAction * current,gpointer data)
name|view_zoom_explicit_cmd_callback
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
name|display
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
name|display
argument_list|,
name|data
argument_list|)
expr_stmt|;
name|shell
operator|=
name|GIMP_DISPLAY_SHELL
argument_list|(
name|display
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
operator|!=
literal|0
comment|/* not Other... */
condition|)
block|{
if|if
condition|(
name|fabs
argument_list|(
name|value
operator|-
name|gimp_zoom_model_get_factor
argument_list|(
name|shell
operator|->
name|zoom
argument_list|)
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
DECL|function|view_zoom_other_cmd_callback (GtkAction * action,gpointer data)
name|view_zoom_other_cmd_callback
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
name|GimpDisplayShell
modifier|*
name|shell
decl_stmt|;
name|return_if_no_display
argument_list|(
name|display
argument_list|,
name|data
argument_list|)
expr_stmt|;
name|shell
operator|=
name|GIMP_DISPLAY_SHELL
argument_list|(
name|display
operator|->
name|shell
argument_list|)
expr_stmt|;
comment|/* check if we are activated by the user or from    * view_actions_set_zoom()    */
if|if
condition|(
name|gtk_toggle_action_get_active
argument_list|(
name|GTK_TOGGLE_ACTION
argument_list|(
name|action
argument_list|)
argument_list|)
operator|&&
name|shell
operator|->
name|other_scale
operator|!=
name|gimp_zoom_model_get_factor
argument_list|(
name|shell
operator|->
name|zoom
argument_list|)
condition|)
block|{
name|gimp_display_shell_scale_dialog
argument_list|(
name|shell
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
name|display
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
name|display
argument_list|,
name|data
argument_list|)
expr_stmt|;
name|shell
operator|=
name|GIMP_DISPLAY_SHELL
argument_list|(
name|display
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
name|display
argument_list|)
condition|)
name|SET_ACTIVE
argument_list|(
name|shell
operator|->
name|popup_manager
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
DECL|function|view_scroll_horizontal_cmd_callback (GtkAction * action,gint value,gpointer data)
name|view_scroll_horizontal_cmd_callback
parameter_list|(
name|GtkAction
modifier|*
name|action
parameter_list|,
name|gint
name|value
parameter_list|,
name|gpointer
name|data
parameter_list|)
block|{
name|GimpDisplay
modifier|*
name|display
decl_stmt|;
name|GimpDisplayShell
modifier|*
name|shell
decl_stmt|;
name|gdouble
name|offset
decl_stmt|;
name|return_if_no_display
argument_list|(
name|display
argument_list|,
name|data
argument_list|)
expr_stmt|;
name|shell
operator|=
name|GIMP_DISPLAY_SHELL
argument_list|(
name|display
operator|->
name|shell
argument_list|)
expr_stmt|;
name|offset
operator|=
name|action_select_value
argument_list|(
operator|(
name|GimpActionSelectType
operator|)
name|value
argument_list|,
name|shell
operator|->
name|hsbdata
operator|->
name|value
argument_list|,
name|shell
operator|->
name|hsbdata
operator|->
name|lower
argument_list|,
name|shell
operator|->
name|hsbdata
operator|->
name|upper
operator|-
name|shell
operator|->
name|hsbdata
operator|->
name|page_size
argument_list|,
name|shell
operator|->
name|hsbdata
operator|->
name|step_increment
argument_list|,
name|shell
operator|->
name|hsbdata
operator|->
name|page_increment
argument_list|,
name|FALSE
argument_list|)
expr_stmt|;
name|gtk_adjustment_set_value
argument_list|(
name|shell
operator|->
name|hsbdata
argument_list|,
name|offset
argument_list|)
expr_stmt|;
block|}
end_function

begin_function
name|void
DECL|function|view_scroll_vertical_cmd_callback (GtkAction * action,gint value,gpointer data)
name|view_scroll_vertical_cmd_callback
parameter_list|(
name|GtkAction
modifier|*
name|action
parameter_list|,
name|gint
name|value
parameter_list|,
name|gpointer
name|data
parameter_list|)
block|{
name|GimpDisplay
modifier|*
name|display
decl_stmt|;
name|GimpDisplayShell
modifier|*
name|shell
decl_stmt|;
name|gdouble
name|offset
decl_stmt|;
name|return_if_no_display
argument_list|(
name|display
argument_list|,
name|data
argument_list|)
expr_stmt|;
name|shell
operator|=
name|GIMP_DISPLAY_SHELL
argument_list|(
name|display
operator|->
name|shell
argument_list|)
expr_stmt|;
name|offset
operator|=
name|action_select_value
argument_list|(
operator|(
name|GimpActionSelectType
operator|)
name|value
argument_list|,
name|shell
operator|->
name|vsbdata
operator|->
name|value
argument_list|,
name|shell
operator|->
name|vsbdata
operator|->
name|lower
argument_list|,
name|shell
operator|->
name|vsbdata
operator|->
name|upper
operator|-
name|shell
operator|->
name|vsbdata
operator|->
name|page_size
argument_list|,
name|shell
operator|->
name|vsbdata
operator|->
name|step_increment
argument_list|,
name|shell
operator|->
name|vsbdata
operator|->
name|page_increment
argument_list|,
name|FALSE
argument_list|)
expr_stmt|;
name|gtk_adjustment_set_value
argument_list|(
name|shell
operator|->
name|vsbdata
argument_list|,
name|offset
argument_list|)
expr_stmt|;
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
name|display
decl_stmt|;
name|GimpDisplayShell
modifier|*
name|shell
decl_stmt|;
name|return_if_no_display
argument_list|(
name|display
argument_list|,
name|data
argument_list|)
expr_stmt|;
name|shell
operator|=
name|GIMP_DISPLAY_SHELL
argument_list|(
name|display
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
name|display
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
name|display
decl_stmt|;
name|GimpDisplayShell
modifier|*
name|shell
decl_stmt|;
name|return_if_no_display
argument_list|(
name|display
argument_list|,
name|data
argument_list|)
expr_stmt|;
name|shell
operator|=
name|GIMP_DISPLAY_SHELL
argument_list|(
name|display
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
name|display
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
name|display
argument_list|,
name|data
argument_list|)
expr_stmt|;
name|shell
operator|=
name|GIMP_DISPLAY_SHELL
argument_list|(
name|display
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
name|display
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
name|display
argument_list|,
name|data
argument_list|)
expr_stmt|;
name|shell
operator|=
name|GIMP_DISPLAY_SHELL
argument_list|(
name|display
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
name|display
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
name|display
argument_list|,
name|data
argument_list|)
expr_stmt|;
name|shell
operator|=
name|GIMP_DISPLAY_SHELL
argument_list|(
name|display
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
name|display
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
name|display
argument_list|,
name|data
argument_list|)
expr_stmt|;
name|shell
operator|=
name|GIMP_DISPLAY_SHELL
argument_list|(
name|display
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
name|display
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
name|display
argument_list|,
name|data
argument_list|)
expr_stmt|;
name|shell
operator|=
name|GIMP_DISPLAY_SHELL
argument_list|(
name|display
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
name|display
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
name|display
argument_list|,
name|data
argument_list|)
expr_stmt|;
name|shell
operator|=
name|GIMP_DISPLAY_SHELL
argument_list|(
name|display
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
name|display
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
name|display
argument_list|,
name|data
argument_list|)
expr_stmt|;
name|shell
operator|=
name|GIMP_DISPLAY_SHELL
argument_list|(
name|display
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
name|display
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
name|display
argument_list|,
name|data
argument_list|)
expr_stmt|;
name|shell
operator|=
name|GIMP_DISPLAY_SHELL
argument_list|(
name|display
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
DECL|function|view_toggle_sample_points_cmd_callback (GtkAction * action,gpointer data)
name|view_toggle_sample_points_cmd_callback
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
name|GimpDisplayShell
modifier|*
name|shell
decl_stmt|;
name|gboolean
name|active
decl_stmt|;
name|return_if_no_display
argument_list|(
name|display
argument_list|,
name|data
argument_list|)
expr_stmt|;
name|shell
operator|=
name|GIMP_DISPLAY_SHELL
argument_list|(
name|display
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
name|gimp_display_shell_set_show_sample_points
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
name|display
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
name|display
argument_list|,
name|data
argument_list|)
expr_stmt|;
name|shell
operator|=
name|GIMP_DISPLAY_SHELL
argument_list|(
name|display
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
name|display
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
name|display
argument_list|,
name|data
argument_list|)
expr_stmt|;
name|shell
operator|=
name|GIMP_DISPLAY_SHELL
argument_list|(
name|display
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
DECL|function|view_snap_to_canvas_cmd_callback (GtkAction * action,gpointer data)
name|view_snap_to_canvas_cmd_callback
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
name|GimpDisplayShell
modifier|*
name|shell
decl_stmt|;
name|gboolean
name|active
decl_stmt|;
name|return_if_no_display
argument_list|(
name|display
argument_list|,
name|data
argument_list|)
expr_stmt|;
name|shell
operator|=
name|GIMP_DISPLAY_SHELL
argument_list|(
name|display
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
name|gimp_display_shell_set_snap_to_canvas
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
DECL|function|view_snap_to_vectors_cmd_callback (GtkAction * action,gpointer data)
name|view_snap_to_vectors_cmd_callback
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
name|GimpDisplayShell
modifier|*
name|shell
decl_stmt|;
name|gboolean
name|active
decl_stmt|;
name|return_if_no_display
argument_list|(
name|display
argument_list|,
name|data
argument_list|)
expr_stmt|;
name|shell
operator|=
name|GIMP_DISPLAY_SHELL
argument_list|(
name|display
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
name|gimp_display_shell_set_snap_to_vectors
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
DECL|function|view_padding_color_cmd_callback (GtkAction * action,gint value,gpointer data)
name|view_padding_color_cmd_callback
parameter_list|(
name|GtkAction
modifier|*
name|action
parameter_list|,
name|gint
name|value
parameter_list|,
name|gpointer
name|data
parameter_list|)
block|{
name|GimpDisplay
modifier|*
name|display
decl_stmt|;
name|GimpDisplayShell
modifier|*
name|shell
decl_stmt|;
name|GimpDisplayOptions
modifier|*
name|options
decl_stmt|;
name|gboolean
name|fullscreen
decl_stmt|;
name|return_if_no_display
argument_list|(
name|display
argument_list|,
name|data
argument_list|)
expr_stmt|;
name|shell
operator|=
name|GIMP_DISPLAY_SHELL
argument_list|(
name|display
operator|->
name|shell
argument_list|)
expr_stmt|;
name|fullscreen
operator|=
name|gimp_display_shell_get_fullscreen
argument_list|(
name|shell
argument_list|)
expr_stmt|;
if|if
condition|(
name|fullscreen
condition|)
name|options
operator|=
name|shell
operator|->
name|fullscreen_options
expr_stmt|;
else|else
name|options
operator|=
name|shell
operator|->
name|options
expr_stmt|;
switch|switch
condition|(
operator|(
name|GimpCanvasPaddingMode
operator|)
name|value
condition|)
block|{
case|case
name|GIMP_CANVAS_PADDING_MODE_DEFAULT
case|:
case|case
name|GIMP_CANVAS_PADDING_MODE_LIGHT_CHECK
case|:
case|case
name|GIMP_CANVAS_PADDING_MODE_DARK_CHECK
case|:
name|g_object_set_data
argument_list|(
name|G_OBJECT
argument_list|(
name|shell
argument_list|)
argument_list|,
literal|"padding-color-dialog"
argument_list|,
name|NULL
argument_list|)
expr_stmt|;
name|options
operator|->
name|padding_mode_set
operator|=
name|TRUE
expr_stmt|;
name|gimp_display_shell_set_padding
argument_list|(
name|shell
argument_list|,
operator|(
name|GimpCanvasPaddingMode
operator|)
name|value
argument_list|,
operator|&
name|options
operator|->
name|padding_color
argument_list|)
expr_stmt|;
break|break;
case|case
name|GIMP_CANVAS_PADDING_MODE_CUSTOM
case|:
block|{
name|GtkWidget
modifier|*
name|color_dialog
decl_stmt|;
name|color_dialog
operator|=
name|g_object_get_data
argument_list|(
name|G_OBJECT
argument_list|(
name|shell
argument_list|)
argument_list|,
literal|"padding-color-dialog"
argument_list|)
expr_stmt|;
if|if
condition|(
operator|!
name|color_dialog
condition|)
block|{
name|color_dialog
operator|=
name|gimp_color_dialog_new
argument_list|(
name|GIMP_VIEWABLE
argument_list|(
name|display
operator|->
name|image
argument_list|)
argument_list|,
name|_
argument_list|(
literal|"Set Canvas Padding Color"
argument_list|)
argument_list|,
name|GTK_STOCK_SELECT_COLOR
argument_list|,
name|_
argument_list|(
literal|"Set Custom Canvas Padding Color"
argument_list|)
argument_list|,
name|display
operator|->
name|shell
argument_list|,
name|NULL
argument_list|,
name|NULL
argument_list|,
operator|&
name|options
operator|->
name|padding_color
argument_list|,
name|FALSE
argument_list|,
name|FALSE
argument_list|)
expr_stmt|;
name|g_signal_connect
argument_list|(
name|color_dialog
argument_list|,
literal|"update"
argument_list|,
name|G_CALLBACK
argument_list|(
name|view_padding_color_dialog_update
argument_list|)
argument_list|,
name|display
operator|->
name|shell
argument_list|)
expr_stmt|;
name|g_object_set_data_full
argument_list|(
name|G_OBJECT
argument_list|(
name|shell
argument_list|)
argument_list|,
literal|"padding-color-dialog"
argument_list|,
name|color_dialog
argument_list|,
operator|(
name|GDestroyNotify
operator|)
name|gtk_widget_destroy
argument_list|)
expr_stmt|;
block|}
name|gtk_window_present
argument_list|(
name|GTK_WINDOW
argument_list|(
name|color_dialog
argument_list|)
argument_list|)
expr_stmt|;
block|}
break|break;
case|case
name|GIMP_CANVAS_PADDING_MODE_RESET
case|:
name|g_object_set_data
argument_list|(
name|G_OBJECT
argument_list|(
name|shell
argument_list|)
argument_list|,
literal|"padding-color-dialog"
argument_list|,
name|NULL
argument_list|)
expr_stmt|;
block|{
name|GimpDisplayConfig
modifier|*
name|config
decl_stmt|;
name|GimpDisplayOptions
modifier|*
name|default_options
decl_stmt|;
name|config
operator|=
name|GIMP_DISPLAY_CONFIG
argument_list|(
name|display
operator|->
name|image
operator|->
name|gimp
operator|->
name|config
argument_list|)
expr_stmt|;
name|options
operator|->
name|padding_mode_set
operator|=
name|FALSE
expr_stmt|;
if|if
condition|(
name|fullscreen
condition|)
name|default_options
operator|=
name|config
operator|->
name|default_fullscreen_view
expr_stmt|;
else|else
name|default_options
operator|=
name|config
operator|->
name|default_view
expr_stmt|;
name|gimp_display_shell_set_padding
argument_list|(
name|shell
argument_list|,
name|default_options
operator|->
name|padding_mode
argument_list|,
operator|&
name|default_options
operator|->
name|padding_color
argument_list|)
expr_stmt|;
block|}
break|break;
block|}
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
name|display
decl_stmt|;
name|return_if_no_display
argument_list|(
name|display
argument_list|,
name|data
argument_list|)
expr_stmt|;
name|gimp_display_shell_scale_shrink_wrap
argument_list|(
name|GIMP_DISPLAY_SHELL
argument_list|(
name|display
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
name|display
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
name|display
argument_list|,
name|data
argument_list|)
expr_stmt|;
name|shell
operator|=
name|GIMP_DISPLAY_SHELL
argument_list|(
name|display
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
block|}
end_function

begin_comment
comment|/*  private functions  */
end_comment

begin_function
specifier|static
name|void
DECL|function|view_padding_color_dialog_update (GimpColorDialog * dialog,const GimpRGB * color,GimpColorDialogState state,GimpDisplayShell * shell)
name|view_padding_color_dialog_update
parameter_list|(
name|GimpColorDialog
modifier|*
name|dialog
parameter_list|,
specifier|const
name|GimpRGB
modifier|*
name|color
parameter_list|,
name|GimpColorDialogState
name|state
parameter_list|,
name|GimpDisplayShell
modifier|*
name|shell
parameter_list|)
block|{
name|GimpDisplayOptions
modifier|*
name|options
decl_stmt|;
name|gboolean
name|fullscreen
decl_stmt|;
name|fullscreen
operator|=
name|gimp_display_shell_get_fullscreen
argument_list|(
name|shell
argument_list|)
expr_stmt|;
if|if
condition|(
name|fullscreen
condition|)
name|options
operator|=
name|shell
operator|->
name|fullscreen_options
expr_stmt|;
else|else
name|options
operator|=
name|shell
operator|->
name|options
expr_stmt|;
switch|switch
condition|(
name|state
condition|)
block|{
case|case
name|GIMP_COLOR_DIALOG_OK
case|:
name|options
operator|->
name|padding_mode_set
operator|=
name|TRUE
expr_stmt|;
name|gimp_display_shell_set_padding
argument_list|(
name|shell
argument_list|,
name|GIMP_CANVAS_PADDING_MODE_CUSTOM
argument_list|,
name|color
argument_list|)
expr_stmt|;
comment|/* fallthru */
case|case
name|GIMP_COLOR_DIALOG_CANCEL
case|:
name|g_object_set_data
argument_list|(
name|G_OBJECT
argument_list|(
name|shell
argument_list|)
argument_list|,
literal|"padding-color-dialog"
argument_list|,
name|NULL
argument_list|)
expr_stmt|;
break|break;
default|default:
break|break;
block|}
block|}
end_function

end_unit

