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
file|"widgets/gimpactiongroup.h"
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
file|"widgets/gimpmenudock.h"
end_include

begin_include
include|#
directive|include
file|"display/gimpimagewindow.h"
end_include

begin_include
include|#
directive|include
file|"actions.h"
end_include

begin_include
include|#
directive|include
file|"dock-actions.h"
end_include

begin_include
include|#
directive|include
file|"dock-commands.h"
end_include

begin_include
include|#
directive|include
file|"window-actions.h"
end_include

begin_include
include|#
directive|include
file|"window-commands.h"
end_include

begin_include
include|#
directive|include
file|"gimp-intl.h"
end_include

begin_decl_stmt
DECL|variable|dock_actions
specifier|static
specifier|const
name|GimpActionEntry
name|dock_actions
index|[]
init|=
block|{
block|{
literal|"dock-move-to-screen-menu"
block|,
name|GIMP_STOCK_MOVE_TO_SCREEN
block|,
name|NC_
argument_list|(
literal|"dock-action"
argument_list|,
literal|"M_ove to Screen"
argument_list|)
block|,
name|NULL
block|,
name|NULL
block|,
name|NULL
block|,
name|GIMP_HELP_DOCK_CHANGE_SCREEN
block|}
block|,
block|{
literal|"dock-close"
block|,
name|GTK_STOCK_CLOSE
block|,
name|NC_
argument_list|(
literal|"dock-action"
argument_list|,
literal|"Close Dock"
argument_list|)
block|,
literal|""
block|,
name|NULL
block|,
name|G_CALLBACK
argument_list|(
name|window_close_cmd_callback
argument_list|)
block|,
name|GIMP_HELP_DOCK_CLOSE
block|}
block|,
block|{
literal|"dock-open-display"
block|,
name|NULL
block|,
name|NC_
argument_list|(
literal|"dock-action"
argument_list|,
literal|"_Open Display..."
argument_list|)
block|,
name|NULL
block|,
name|NC_
argument_list|(
literal|"dock-action"
argument_list|,
literal|"Connect to another display"
argument_list|)
block|,
name|G_CALLBACK
argument_list|(
name|window_open_display_cmd_callback
argument_list|)
block|,
name|NULL
block|}
block|}
decl_stmt|;
end_decl_stmt

begin_decl_stmt
DECL|variable|dock_toggle_actions
specifier|static
specifier|const
name|GimpToggleActionEntry
name|dock_toggle_actions
index|[]
init|=
block|{
block|{
literal|"dock-show-image-menu"
block|,
name|NULL
block|,
name|NC_
argument_list|(
literal|"dock-action"
argument_list|,
literal|"_Show Image Selection"
argument_list|)
block|,
name|NULL
block|,
name|NULL
block|,
name|G_CALLBACK
argument_list|(
name|dock_toggle_image_menu_cmd_callback
argument_list|)
block|,
name|TRUE
block|,
name|GIMP_HELP_DOCK_IMAGE_MENU
block|}
block|,
block|{
literal|"dock-auto-follow-active"
block|,
name|NULL
block|,
name|NC_
argument_list|(
literal|"dock-action"
argument_list|,
literal|"Auto _Follow Active Image"
argument_list|)
block|,
name|NULL
block|,
name|NULL
block|,
name|G_CALLBACK
argument_list|(
name|dock_toggle_auto_cmd_callback
argument_list|)
block|,
name|TRUE
block|,
name|GIMP_HELP_DOCK_AUTO_BUTTON
block|}
block|}
decl_stmt|;
end_decl_stmt

begin_function
name|void
DECL|function|dock_actions_setup (GimpActionGroup * group)
name|dock_actions_setup
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
literal|"dock-action"
argument_list|,
name|dock_actions
argument_list|,
name|G_N_ELEMENTS
argument_list|(
name|dock_actions
argument_list|)
argument_list|)
expr_stmt|;
name|gimp_action_group_add_toggle_actions
argument_list|(
name|group
argument_list|,
literal|"dock-action"
argument_list|,
name|dock_toggle_actions
argument_list|,
name|G_N_ELEMENTS
argument_list|(
name|dock_toggle_actions
argument_list|)
argument_list|)
expr_stmt|;
name|window_actions_setup
argument_list|(
name|group
argument_list|,
name|GIMP_HELP_DOCK_CHANGE_SCREEN
argument_list|)
expr_stmt|;
block|}
end_function

begin_function
name|void
DECL|function|dock_actions_update (GimpActionGroup * group,gpointer data)
name|dock_actions_update
parameter_list|(
name|GimpActionGroup
modifier|*
name|group
parameter_list|,
name|gpointer
name|data
parameter_list|)
block|{
name|GtkWidget
modifier|*
name|widget
init|=
name|action_data_get_widget
argument_list|(
name|data
argument_list|)
decl_stmt|;
name|GtkWidget
modifier|*
name|toplevel
init|=
name|NULL
decl_stmt|;
if|if
condition|(
name|widget
condition|)
name|toplevel
operator|=
name|gtk_widget_get_toplevel
argument_list|(
name|widget
argument_list|)
expr_stmt|;
DECL|macro|SET_ACTIVE (action,active)
define|#
directive|define
name|SET_ACTIVE
parameter_list|(
name|action
parameter_list|,
name|active
parameter_list|)
define|\
value|gimp_action_group_set_action_active (group, action, (active) != 0)
DECL|macro|SET_VISIBLE (action,active)
define|#
directive|define
name|SET_VISIBLE
parameter_list|(
name|action
parameter_list|,
name|active
parameter_list|)
define|\
value|gimp_action_group_set_action_visible (group, action, (active) != 0)
if|if
condition|(
name|GIMP_IS_DOCK_WINDOW
argument_list|(
name|toplevel
argument_list|)
condition|)
block|{
name|GimpDockWindow
modifier|*
name|dock_window
init|=
name|GIMP_DOCK_WINDOW
argument_list|(
name|toplevel
argument_list|)
decl_stmt|;
name|gboolean
name|show_image_menu
init|=
operator|!
name|gimp_dock_window_has_toolbox
argument_list|(
name|dock_window
argument_list|)
decl_stmt|;
if|if
condition|(
name|show_image_menu
condition|)
block|{
name|SET_VISIBLE
argument_list|(
literal|"dock-show-image-menu"
argument_list|,
name|TRUE
argument_list|)
expr_stmt|;
name|SET_VISIBLE
argument_list|(
literal|"dock-auto-follow-active"
argument_list|,
name|TRUE
argument_list|)
expr_stmt|;
name|SET_ACTIVE
argument_list|(
literal|"dock-show-image-menu"
argument_list|,
name|gimp_dock_window_get_show_image_menu
argument_list|(
name|dock_window
argument_list|)
argument_list|)
expr_stmt|;
name|SET_ACTIVE
argument_list|(
literal|"dock-auto-follow-active"
argument_list|,
name|gimp_dock_window_get_auto_follow_active
argument_list|(
name|dock_window
argument_list|)
argument_list|)
expr_stmt|;
block|}
else|else
block|{
name|SET_VISIBLE
argument_list|(
literal|"dock-show-image-menu"
argument_list|,
name|FALSE
argument_list|)
expr_stmt|;
name|SET_VISIBLE
argument_list|(
literal|"dock-auto-follow-active"
argument_list|,
name|FALSE
argument_list|)
expr_stmt|;
block|}
comment|/*  update the window actions only in the context of their        *  own window (not in the context of some display or NULL)        *  (see view-actions.c)        */
name|window_actions_update
argument_list|(
name|group
argument_list|,
name|toplevel
argument_list|)
expr_stmt|;
block|}
elseif|else
if|if
condition|(
name|GIMP_IS_IMAGE_WINDOW
argument_list|(
name|toplevel
argument_list|)
condition|)
block|{
name|SET_VISIBLE
argument_list|(
literal|"dock-show-image-menu"
argument_list|,
name|FALSE
argument_list|)
expr_stmt|;
name|SET_VISIBLE
argument_list|(
literal|"dock-auto-follow-active"
argument_list|,
name|FALSE
argument_list|)
expr_stmt|;
block|}
undef|#
directive|undef
name|SET_ACTIVE
undef|#
directive|undef
name|SET_VISIBLE
block|}
end_function

end_unit

