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
file|"libgimpcolor/gimpcolor.h"
end_include

begin_include
include|#
directive|include
file|"libgimpwidgets/gimpwidgets.h"
end_include

begin_include
include|#
directive|include
file|"display-types.h"
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
file|"widgets/gimpactiongroup.h"
end_include

begin_include
include|#
directive|include
file|"widgets/gimpuimanager.h"
end_include

begin_include
include|#
directive|include
file|"widgets/gimpwidgets-utils.h"
end_include

begin_include
include|#
directive|include
file|"gimpcanvas.h"
end_include

begin_include
include|#
directive|include
file|"gimpdisplay.h"
end_include

begin_include
include|#
directive|include
file|"gimpdisplayoptions.h"
end_include

begin_include
include|#
directive|include
file|"gimpdisplayshell.h"
end_include

begin_include
include|#
directive|include
file|"gimpdisplayshell-appearance.h"
end_include

begin_include
include|#
directive|include
file|"gimpdisplayshell-callbacks.h"
end_include

begin_include
include|#
directive|include
file|"gimpdisplayshell-selection.h"
end_include

begin_include
include|#
directive|include
file|"gimpdisplayshell-render.h"
end_include

begin_define
DECL|macro|GET_OPTIONS (shell)
define|#
directive|define
name|GET_OPTIONS
parameter_list|(
name|shell
parameter_list|)
define|\
value|(gimp_display_shell_get_fullscreen (shell) ? \    shell->fullscreen_options : shell->options)
end_define

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
DECL|macro|SET_COLOR (manager,action_name,color)
define|#
directive|define
name|SET_COLOR
parameter_list|(
name|manager
parameter_list|,
name|action_name
parameter_list|,
name|color
parameter_list|)
define|\
value|{ GimpActionGroup *group = \       gimp_ui_manager_get_action_group (manager, "view"); \     gimp_action_group_set_action_color (group, action_name, color, FALSE); }
end_define

begin_define
DECL|macro|IS_ACTIVE_DISPLAY (shell)
define|#
directive|define
name|IS_ACTIVE_DISPLAY
parameter_list|(
name|shell
parameter_list|)
define|\
value|((shell)->gdisp == \    gimp_context_get_display (gimp_get_user_context \                              ((shell)->gdisp->gimage->gimp)))
end_define

begin_function
name|void
DECL|function|gimp_display_shell_set_fullscreen (GimpDisplayShell * shell,gboolean fullscreen)
name|gimp_display_shell_set_fullscreen
parameter_list|(
name|GimpDisplayShell
modifier|*
name|shell
parameter_list|,
name|gboolean
name|fullscreen
parameter_list|)
block|{
name|g_return_if_fail
argument_list|(
name|GIMP_IS_DISPLAY_SHELL
argument_list|(
name|shell
argument_list|)
argument_list|)
expr_stmt|;
if|if
condition|(
name|fullscreen
operator|!=
name|gimp_display_shell_get_fullscreen
argument_list|(
name|shell
argument_list|)
condition|)
block|{
if|if
condition|(
name|fullscreen
condition|)
name|gtk_window_fullscreen
argument_list|(
name|GTK_WINDOW
argument_list|(
name|shell
argument_list|)
argument_list|)
expr_stmt|;
else|else
name|gtk_window_unfullscreen
argument_list|(
name|GTK_WINDOW
argument_list|(
name|shell
argument_list|)
argument_list|)
expr_stmt|;
block|}
block|}
end_function

begin_function
name|gboolean
DECL|function|gimp_display_shell_get_fullscreen (GimpDisplayShell * shell)
name|gimp_display_shell_get_fullscreen
parameter_list|(
name|GimpDisplayShell
modifier|*
name|shell
parameter_list|)
block|{
name|g_return_val_if_fail
argument_list|(
name|GIMP_IS_DISPLAY_SHELL
argument_list|(
name|shell
argument_list|)
argument_list|,
name|FALSE
argument_list|)
expr_stmt|;
return|return
operator|(
name|shell
operator|->
name|window_state
operator|&
name|GDK_WINDOW_STATE_FULLSCREEN
operator|)
operator|!=
literal|0
return|;
block|}
end_function

begin_function
name|void
DECL|function|gimp_display_shell_set_show_menubar (GimpDisplayShell * shell,gboolean show)
name|gimp_display_shell_set_show_menubar
parameter_list|(
name|GimpDisplayShell
modifier|*
name|shell
parameter_list|,
name|gboolean
name|show
parameter_list|)
block|{
name|GimpDisplayOptions
modifier|*
name|options
decl_stmt|;
name|GtkContainer
modifier|*
name|vbox
decl_stmt|;
name|g_return_if_fail
argument_list|(
name|GIMP_IS_DISPLAY_SHELL
argument_list|(
name|shell
argument_list|)
argument_list|)
expr_stmt|;
name|options
operator|=
name|GET_OPTIONS
argument_list|(
name|shell
argument_list|)
expr_stmt|;
name|g_object_set
argument_list|(
name|options
argument_list|,
literal|"show-menubar"
argument_list|,
name|show
argument_list|,
name|NULL
argument_list|)
expr_stmt|;
name|vbox
operator|=
name|GTK_CONTAINER
argument_list|(
name|shell
operator|->
name|qmask_button
operator|->
name|parent
operator|->
name|parent
argument_list|)
expr_stmt|;
if|if
condition|(
name|shell
operator|->
name|menubar
condition|)
block|{
if|if
condition|(
name|show
condition|)
name|gtk_widget_show
argument_list|(
name|shell
operator|->
name|menubar
argument_list|)
expr_stmt|;
else|else
name|gtk_widget_hide
argument_list|(
name|shell
operator|->
name|menubar
argument_list|)
expr_stmt|;
block|}
if|if
condition|(
name|options
operator|->
name|show_menubar
operator|||
name|options
operator|->
name|show_statusbar
condition|)
name|gtk_container_set_border_width
argument_list|(
name|vbox
argument_list|,
literal|2
argument_list|)
expr_stmt|;
else|else
name|gtk_container_set_border_width
argument_list|(
name|vbox
argument_list|,
literal|0
argument_list|)
expr_stmt|;
name|SET_ACTIVE
argument_list|(
name|shell
operator|->
name|menubar_manager
argument_list|,
literal|"view-show-menubar"
argument_list|,
name|show
argument_list|)
expr_stmt|;
if|if
condition|(
name|IS_ACTIVE_DISPLAY
argument_list|(
name|shell
argument_list|)
condition|)
name|SET_ACTIVE
argument_list|(
name|shell
operator|->
name|popup_manager
argument_list|,
literal|"view-show-menubar"
argument_list|,
name|show
argument_list|)
expr_stmt|;
block|}
end_function

begin_function
name|gboolean
DECL|function|gimp_display_shell_get_show_menubar (GimpDisplayShell * shell)
name|gimp_display_shell_get_show_menubar
parameter_list|(
name|GimpDisplayShell
modifier|*
name|shell
parameter_list|)
block|{
name|g_return_val_if_fail
argument_list|(
name|GIMP_IS_DISPLAY_SHELL
argument_list|(
name|shell
argument_list|)
argument_list|,
name|FALSE
argument_list|)
expr_stmt|;
return|return
name|GET_OPTIONS
argument_list|(
name|shell
argument_list|)
operator|->
name|show_menubar
return|;
block|}
end_function

begin_function
name|void
DECL|function|gimp_display_shell_set_show_rulers (GimpDisplayShell * shell,gboolean show)
name|gimp_display_shell_set_show_rulers
parameter_list|(
name|GimpDisplayShell
modifier|*
name|shell
parameter_list|,
name|gboolean
name|show
parameter_list|)
block|{
name|GimpDisplayOptions
modifier|*
name|options
decl_stmt|;
name|GtkTable
modifier|*
name|table
decl_stmt|;
name|g_return_if_fail
argument_list|(
name|GIMP_IS_DISPLAY_SHELL
argument_list|(
name|shell
argument_list|)
argument_list|)
expr_stmt|;
name|options
operator|=
name|GET_OPTIONS
argument_list|(
name|shell
argument_list|)
expr_stmt|;
name|g_object_set
argument_list|(
name|options
argument_list|,
literal|"show-rulers"
argument_list|,
name|show
argument_list|,
name|NULL
argument_list|)
expr_stmt|;
name|table
operator|=
name|GTK_TABLE
argument_list|(
name|GTK_WIDGET
argument_list|(
name|shell
operator|->
name|canvas
argument_list|)
operator|->
name|parent
argument_list|)
expr_stmt|;
if|if
condition|(
name|show
condition|)
block|{
name|gtk_widget_show
argument_list|(
name|shell
operator|->
name|origin_button
argument_list|)
expr_stmt|;
name|gtk_widget_show
argument_list|(
name|shell
operator|->
name|hrule
argument_list|)
expr_stmt|;
name|gtk_widget_show
argument_list|(
name|shell
operator|->
name|vrule
argument_list|)
expr_stmt|;
name|gtk_table_set_col_spacing
argument_list|(
name|table
argument_list|,
literal|0
argument_list|,
literal|1
argument_list|)
expr_stmt|;
name|gtk_table_set_row_spacing
argument_list|(
name|table
argument_list|,
literal|0
argument_list|,
literal|1
argument_list|)
expr_stmt|;
block|}
else|else
block|{
name|gtk_widget_hide
argument_list|(
name|shell
operator|->
name|origin_button
argument_list|)
expr_stmt|;
name|gtk_widget_hide
argument_list|(
name|shell
operator|->
name|hrule
argument_list|)
expr_stmt|;
name|gtk_widget_hide
argument_list|(
name|shell
operator|->
name|vrule
argument_list|)
expr_stmt|;
name|gtk_table_set_col_spacing
argument_list|(
name|table
argument_list|,
literal|0
argument_list|,
literal|0
argument_list|)
expr_stmt|;
name|gtk_table_set_row_spacing
argument_list|(
name|table
argument_list|,
literal|0
argument_list|,
literal|0
argument_list|)
expr_stmt|;
block|}
name|SET_ACTIVE
argument_list|(
name|shell
operator|->
name|menubar_manager
argument_list|,
literal|"view-show-rulers"
argument_list|,
name|show
argument_list|)
expr_stmt|;
if|if
condition|(
name|IS_ACTIVE_DISPLAY
argument_list|(
name|shell
argument_list|)
condition|)
name|SET_ACTIVE
argument_list|(
name|shell
operator|->
name|popup_manager
argument_list|,
literal|"view-show-rulers"
argument_list|,
name|show
argument_list|)
expr_stmt|;
block|}
end_function

begin_function
name|gboolean
DECL|function|gimp_display_shell_get_show_rulers (GimpDisplayShell * shell)
name|gimp_display_shell_get_show_rulers
parameter_list|(
name|GimpDisplayShell
modifier|*
name|shell
parameter_list|)
block|{
name|g_return_val_if_fail
argument_list|(
name|GIMP_IS_DISPLAY_SHELL
argument_list|(
name|shell
argument_list|)
argument_list|,
name|FALSE
argument_list|)
expr_stmt|;
return|return
name|GET_OPTIONS
argument_list|(
name|shell
argument_list|)
operator|->
name|show_rulers
return|;
block|}
end_function

begin_function
name|void
DECL|function|gimp_display_shell_set_show_scrollbars (GimpDisplayShell * shell,gboolean show)
name|gimp_display_shell_set_show_scrollbars
parameter_list|(
name|GimpDisplayShell
modifier|*
name|shell
parameter_list|,
name|gboolean
name|show
parameter_list|)
block|{
name|GimpDisplayOptions
modifier|*
name|options
decl_stmt|;
name|GtkBox
modifier|*
name|hbox
decl_stmt|;
name|GtkBox
modifier|*
name|vbox
decl_stmt|;
name|g_return_if_fail
argument_list|(
name|GIMP_IS_DISPLAY_SHELL
argument_list|(
name|shell
argument_list|)
argument_list|)
expr_stmt|;
name|options
operator|=
name|GET_OPTIONS
argument_list|(
name|shell
argument_list|)
expr_stmt|;
name|g_object_set
argument_list|(
name|options
argument_list|,
literal|"show-scrollbars"
argument_list|,
name|show
argument_list|,
name|NULL
argument_list|)
expr_stmt|;
name|hbox
operator|=
name|GTK_BOX
argument_list|(
name|shell
operator|->
name|vsb
operator|->
name|parent
operator|->
name|parent
argument_list|)
expr_stmt|;
name|vbox
operator|=
name|GTK_BOX
argument_list|(
name|shell
operator|->
name|hsb
operator|->
name|parent
operator|->
name|parent
argument_list|)
expr_stmt|;
if|if
condition|(
name|show
condition|)
block|{
name|gtk_widget_show
argument_list|(
name|shell
operator|->
name|nav_ebox
argument_list|)
expr_stmt|;
name|gtk_widget_show
argument_list|(
name|shell
operator|->
name|hsb
argument_list|)
expr_stmt|;
name|gtk_widget_show
argument_list|(
name|shell
operator|->
name|vsb
argument_list|)
expr_stmt|;
name|gtk_widget_show
argument_list|(
name|shell
operator|->
name|qmask_button
argument_list|)
expr_stmt|;
name|gtk_widget_show
argument_list|(
name|shell
operator|->
name|zoom_button
argument_list|)
expr_stmt|;
name|gtk_box_set_spacing
argument_list|(
name|hbox
argument_list|,
literal|1
argument_list|)
expr_stmt|;
name|gtk_box_set_spacing
argument_list|(
name|vbox
argument_list|,
literal|1
argument_list|)
expr_stmt|;
block|}
else|else
block|{
name|gtk_widget_hide
argument_list|(
name|shell
operator|->
name|nav_ebox
argument_list|)
expr_stmt|;
name|gtk_widget_hide
argument_list|(
name|shell
operator|->
name|hsb
argument_list|)
expr_stmt|;
name|gtk_widget_hide
argument_list|(
name|shell
operator|->
name|vsb
argument_list|)
expr_stmt|;
name|gtk_widget_hide
argument_list|(
name|shell
operator|->
name|qmask_button
argument_list|)
expr_stmt|;
name|gtk_widget_hide
argument_list|(
name|shell
operator|->
name|zoom_button
argument_list|)
expr_stmt|;
name|gtk_box_set_spacing
argument_list|(
name|hbox
argument_list|,
literal|0
argument_list|)
expr_stmt|;
name|gtk_box_set_spacing
argument_list|(
name|vbox
argument_list|,
literal|0
argument_list|)
expr_stmt|;
block|}
name|SET_ACTIVE
argument_list|(
name|shell
operator|->
name|menubar_manager
argument_list|,
literal|"view-show-scrollbars"
argument_list|,
name|show
argument_list|)
expr_stmt|;
if|if
condition|(
name|IS_ACTIVE_DISPLAY
argument_list|(
name|shell
argument_list|)
condition|)
name|SET_ACTIVE
argument_list|(
name|shell
operator|->
name|popup_manager
argument_list|,
literal|"view-show-scrollbars"
argument_list|,
name|show
argument_list|)
expr_stmt|;
block|}
end_function

begin_function
name|gboolean
DECL|function|gimp_display_shell_get_show_scrollbars (GimpDisplayShell * shell)
name|gimp_display_shell_get_show_scrollbars
parameter_list|(
name|GimpDisplayShell
modifier|*
name|shell
parameter_list|)
block|{
name|g_return_val_if_fail
argument_list|(
name|GIMP_IS_DISPLAY_SHELL
argument_list|(
name|shell
argument_list|)
argument_list|,
name|FALSE
argument_list|)
expr_stmt|;
return|return
name|GET_OPTIONS
argument_list|(
name|shell
argument_list|)
operator|->
name|show_scrollbars
return|;
block|}
end_function

begin_function
name|void
DECL|function|gimp_display_shell_set_show_statusbar (GimpDisplayShell * shell,gboolean show)
name|gimp_display_shell_set_show_statusbar
parameter_list|(
name|GimpDisplayShell
modifier|*
name|shell
parameter_list|,
name|gboolean
name|show
parameter_list|)
block|{
name|GimpDisplayOptions
modifier|*
name|options
decl_stmt|;
name|GtkContainer
modifier|*
name|vbox
decl_stmt|;
name|g_return_if_fail
argument_list|(
name|GIMP_IS_DISPLAY_SHELL
argument_list|(
name|shell
argument_list|)
argument_list|)
expr_stmt|;
name|options
operator|=
name|GET_OPTIONS
argument_list|(
name|shell
argument_list|)
expr_stmt|;
name|g_object_set
argument_list|(
name|options
argument_list|,
literal|"show-statusbar"
argument_list|,
name|show
argument_list|,
name|NULL
argument_list|)
expr_stmt|;
name|vbox
operator|=
name|GTK_CONTAINER
argument_list|(
name|shell
operator|->
name|qmask_button
operator|->
name|parent
operator|->
name|parent
argument_list|)
expr_stmt|;
if|if
condition|(
name|show
condition|)
name|gtk_widget_show
argument_list|(
name|shell
operator|->
name|statusbar
argument_list|)
expr_stmt|;
else|else
name|gtk_widget_hide
argument_list|(
name|shell
operator|->
name|statusbar
argument_list|)
expr_stmt|;
if|if
condition|(
name|options
operator|->
name|show_menubar
operator|||
name|options
operator|->
name|show_statusbar
condition|)
name|gtk_container_set_border_width
argument_list|(
name|vbox
argument_list|,
literal|2
argument_list|)
expr_stmt|;
else|else
name|gtk_container_set_border_width
argument_list|(
name|vbox
argument_list|,
literal|0
argument_list|)
expr_stmt|;
name|SET_ACTIVE
argument_list|(
name|shell
operator|->
name|menubar_manager
argument_list|,
literal|"view-show-statusbar"
argument_list|,
name|show
argument_list|)
expr_stmt|;
if|if
condition|(
name|IS_ACTIVE_DISPLAY
argument_list|(
name|shell
argument_list|)
condition|)
name|SET_ACTIVE
argument_list|(
name|shell
operator|->
name|popup_manager
argument_list|,
literal|"view-show-statusbar"
argument_list|,
name|show
argument_list|)
expr_stmt|;
block|}
end_function

begin_function
name|gboolean
DECL|function|gimp_display_shell_get_show_statusbar (GimpDisplayShell * shell)
name|gimp_display_shell_get_show_statusbar
parameter_list|(
name|GimpDisplayShell
modifier|*
name|shell
parameter_list|)
block|{
name|g_return_val_if_fail
argument_list|(
name|GIMP_IS_DISPLAY_SHELL
argument_list|(
name|shell
argument_list|)
argument_list|,
name|FALSE
argument_list|)
expr_stmt|;
return|return
name|GET_OPTIONS
argument_list|(
name|shell
argument_list|)
operator|->
name|show_statusbar
return|;
block|}
end_function

begin_function
name|void
DECL|function|gimp_display_shell_set_show_selection (GimpDisplayShell * shell,gboolean show)
name|gimp_display_shell_set_show_selection
parameter_list|(
name|GimpDisplayShell
modifier|*
name|shell
parameter_list|,
name|gboolean
name|show
parameter_list|)
block|{
name|GimpDisplayOptions
modifier|*
name|options
decl_stmt|;
name|g_return_if_fail
argument_list|(
name|GIMP_IS_DISPLAY_SHELL
argument_list|(
name|shell
argument_list|)
argument_list|)
expr_stmt|;
name|options
operator|=
name|GET_OPTIONS
argument_list|(
name|shell
argument_list|)
expr_stmt|;
name|g_object_set
argument_list|(
name|options
argument_list|,
literal|"show-selection"
argument_list|,
name|show
argument_list|,
name|NULL
argument_list|)
expr_stmt|;
if|if
condition|(
name|shell
operator|->
name|select
condition|)
name|gimp_display_shell_selection_set_hidden
argument_list|(
name|shell
operator|->
name|select
argument_list|,
operator|!
name|show
argument_list|)
expr_stmt|;
name|SET_ACTIVE
argument_list|(
name|shell
operator|->
name|menubar_manager
argument_list|,
literal|"view-show-selection"
argument_list|,
name|show
argument_list|)
expr_stmt|;
if|if
condition|(
name|IS_ACTIVE_DISPLAY
argument_list|(
name|shell
argument_list|)
condition|)
name|SET_ACTIVE
argument_list|(
name|shell
operator|->
name|popup_manager
argument_list|,
literal|"view-show-selection"
argument_list|,
name|show
argument_list|)
expr_stmt|;
block|}
end_function

begin_function
name|gboolean
DECL|function|gimp_display_shell_get_show_selection (GimpDisplayShell * shell)
name|gimp_display_shell_get_show_selection
parameter_list|(
name|GimpDisplayShell
modifier|*
name|shell
parameter_list|)
block|{
name|g_return_val_if_fail
argument_list|(
name|GIMP_IS_DISPLAY_SHELL
argument_list|(
name|shell
argument_list|)
argument_list|,
name|FALSE
argument_list|)
expr_stmt|;
return|return
name|GET_OPTIONS
argument_list|(
name|shell
argument_list|)
operator|->
name|show_selection
return|;
block|}
end_function

begin_function
name|void
DECL|function|gimp_display_shell_set_show_layer (GimpDisplayShell * shell,gboolean show)
name|gimp_display_shell_set_show_layer
parameter_list|(
name|GimpDisplayShell
modifier|*
name|shell
parameter_list|,
name|gboolean
name|show
parameter_list|)
block|{
name|GimpDisplayOptions
modifier|*
name|options
decl_stmt|;
name|g_return_if_fail
argument_list|(
name|GIMP_IS_DISPLAY_SHELL
argument_list|(
name|shell
argument_list|)
argument_list|)
expr_stmt|;
name|options
operator|=
name|GET_OPTIONS
argument_list|(
name|shell
argument_list|)
expr_stmt|;
name|g_object_set
argument_list|(
name|options
argument_list|,
literal|"show-layer-boundary"
argument_list|,
name|show
argument_list|,
name|NULL
argument_list|)
expr_stmt|;
if|if
condition|(
name|shell
operator|->
name|select
condition|)
name|gimp_display_shell_selection_layer_set_hidden
argument_list|(
name|shell
operator|->
name|select
argument_list|,
operator|!
name|show
argument_list|)
expr_stmt|;
name|SET_ACTIVE
argument_list|(
name|shell
operator|->
name|menubar_manager
argument_list|,
literal|"view-show-layer-boundary"
argument_list|,
name|show
argument_list|)
expr_stmt|;
if|if
condition|(
name|IS_ACTIVE_DISPLAY
argument_list|(
name|shell
argument_list|)
condition|)
name|SET_ACTIVE
argument_list|(
name|shell
operator|->
name|popup_manager
argument_list|,
literal|"view-show-layer-boundary"
argument_list|,
name|show
argument_list|)
expr_stmt|;
block|}
end_function

begin_function
name|gboolean
DECL|function|gimp_display_shell_get_show_layer (GimpDisplayShell * shell)
name|gimp_display_shell_get_show_layer
parameter_list|(
name|GimpDisplayShell
modifier|*
name|shell
parameter_list|)
block|{
name|g_return_val_if_fail
argument_list|(
name|GIMP_IS_DISPLAY_SHELL
argument_list|(
name|shell
argument_list|)
argument_list|,
name|FALSE
argument_list|)
expr_stmt|;
return|return
name|GET_OPTIONS
argument_list|(
name|shell
argument_list|)
operator|->
name|show_layer_boundary
return|;
block|}
end_function

begin_function
name|void
DECL|function|gimp_display_shell_set_show_transform (GimpDisplayShell * shell,gboolean show)
name|gimp_display_shell_set_show_transform
parameter_list|(
name|GimpDisplayShell
modifier|*
name|shell
parameter_list|,
name|gboolean
name|show
parameter_list|)
block|{
name|g_return_if_fail
argument_list|(
name|GIMP_IS_DISPLAY_SHELL
argument_list|(
name|shell
argument_list|)
argument_list|)
expr_stmt|;
name|shell
operator|->
name|show_transform_preview
operator|=
name|show
expr_stmt|;
block|}
end_function

begin_function
name|gboolean
DECL|function|gimp_display_shell_get_show_transform (GimpDisplayShell * shell)
name|gimp_display_shell_get_show_transform
parameter_list|(
name|GimpDisplayShell
modifier|*
name|shell
parameter_list|)
block|{
name|g_return_val_if_fail
argument_list|(
name|GIMP_IS_DISPLAY_SHELL
argument_list|(
name|shell
argument_list|)
argument_list|,
name|FALSE
argument_list|)
expr_stmt|;
return|return
name|shell
operator|->
name|show_transform_preview
return|;
block|}
end_function

begin_function
name|void
DECL|function|gimp_display_shell_set_show_grid (GimpDisplayShell * shell,gboolean show)
name|gimp_display_shell_set_show_grid
parameter_list|(
name|GimpDisplayShell
modifier|*
name|shell
parameter_list|,
name|gboolean
name|show
parameter_list|)
block|{
name|GimpDisplayOptions
modifier|*
name|options
decl_stmt|;
name|g_return_if_fail
argument_list|(
name|GIMP_IS_DISPLAY_SHELL
argument_list|(
name|shell
argument_list|)
argument_list|)
expr_stmt|;
name|options
operator|=
name|GET_OPTIONS
argument_list|(
name|shell
argument_list|)
expr_stmt|;
name|g_object_set
argument_list|(
name|options
argument_list|,
literal|"show-grid"
argument_list|,
name|show
argument_list|,
name|NULL
argument_list|)
expr_stmt|;
if|if
condition|(
name|shell
operator|->
name|gdisp
operator|->
name|gimage
operator|->
name|grid
condition|)
name|gimp_display_shell_expose_full
argument_list|(
name|shell
argument_list|)
expr_stmt|;
name|SET_ACTIVE
argument_list|(
name|shell
operator|->
name|menubar_manager
argument_list|,
literal|"view-show-grid"
argument_list|,
name|show
argument_list|)
expr_stmt|;
if|if
condition|(
name|IS_ACTIVE_DISPLAY
argument_list|(
name|shell
argument_list|)
condition|)
name|SET_ACTIVE
argument_list|(
name|shell
operator|->
name|popup_manager
argument_list|,
literal|"view-show-grid"
argument_list|,
name|show
argument_list|)
expr_stmt|;
block|}
end_function

begin_function
name|gboolean
DECL|function|gimp_display_shell_get_show_grid (GimpDisplayShell * shell)
name|gimp_display_shell_get_show_grid
parameter_list|(
name|GimpDisplayShell
modifier|*
name|shell
parameter_list|)
block|{
name|g_return_val_if_fail
argument_list|(
name|GIMP_IS_DISPLAY_SHELL
argument_list|(
name|shell
argument_list|)
argument_list|,
name|FALSE
argument_list|)
expr_stmt|;
return|return
name|GET_OPTIONS
argument_list|(
name|shell
argument_list|)
operator|->
name|show_grid
return|;
block|}
end_function

begin_function
name|void
DECL|function|gimp_display_shell_set_show_guides (GimpDisplayShell * shell,gboolean show)
name|gimp_display_shell_set_show_guides
parameter_list|(
name|GimpDisplayShell
modifier|*
name|shell
parameter_list|,
name|gboolean
name|show
parameter_list|)
block|{
name|GimpDisplayOptions
modifier|*
name|options
decl_stmt|;
name|g_return_if_fail
argument_list|(
name|GIMP_IS_DISPLAY_SHELL
argument_list|(
name|shell
argument_list|)
argument_list|)
expr_stmt|;
name|options
operator|=
name|GET_OPTIONS
argument_list|(
name|shell
argument_list|)
expr_stmt|;
name|g_object_set
argument_list|(
name|options
argument_list|,
literal|"show-guides"
argument_list|,
name|show
argument_list|,
name|NULL
argument_list|)
expr_stmt|;
if|if
condition|(
name|shell
operator|->
name|gdisp
operator|->
name|gimage
operator|->
name|guides
condition|)
name|gimp_display_shell_expose_full
argument_list|(
name|shell
argument_list|)
expr_stmt|;
name|SET_ACTIVE
argument_list|(
name|shell
operator|->
name|menubar_manager
argument_list|,
literal|"view-show-guides"
argument_list|,
name|show
argument_list|)
expr_stmt|;
if|if
condition|(
name|IS_ACTIVE_DISPLAY
argument_list|(
name|shell
argument_list|)
condition|)
name|SET_ACTIVE
argument_list|(
name|shell
operator|->
name|popup_manager
argument_list|,
literal|"view-show-guides"
argument_list|,
name|show
argument_list|)
expr_stmt|;
block|}
end_function

begin_function
name|gboolean
DECL|function|gimp_display_shell_get_show_guides (GimpDisplayShell * shell)
name|gimp_display_shell_get_show_guides
parameter_list|(
name|GimpDisplayShell
modifier|*
name|shell
parameter_list|)
block|{
name|g_return_val_if_fail
argument_list|(
name|GIMP_IS_DISPLAY_SHELL
argument_list|(
name|shell
argument_list|)
argument_list|,
name|FALSE
argument_list|)
expr_stmt|;
return|return
name|GET_OPTIONS
argument_list|(
name|shell
argument_list|)
operator|->
name|show_guides
return|;
block|}
end_function

begin_function
name|void
DECL|function|gimp_display_shell_set_snap_to_grid (GimpDisplayShell * shell,gboolean snap)
name|gimp_display_shell_set_snap_to_grid
parameter_list|(
name|GimpDisplayShell
modifier|*
name|shell
parameter_list|,
name|gboolean
name|snap
parameter_list|)
block|{
name|g_return_if_fail
argument_list|(
name|GIMP_IS_DISPLAY_SHELL
argument_list|(
name|shell
argument_list|)
argument_list|)
expr_stmt|;
if|if
condition|(
name|snap
operator|!=
name|shell
operator|->
name|snap_to_grid
condition|)
block|{
name|shell
operator|->
name|snap_to_grid
operator|=
name|snap
condition|?
name|TRUE
else|:
name|FALSE
expr_stmt|;
name|SET_ACTIVE
argument_list|(
name|shell
operator|->
name|menubar_manager
argument_list|,
literal|"view-snap-to-grid"
argument_list|,
name|snap
argument_list|)
expr_stmt|;
if|if
condition|(
name|IS_ACTIVE_DISPLAY
argument_list|(
name|shell
argument_list|)
condition|)
name|SET_ACTIVE
argument_list|(
name|shell
operator|->
name|popup_manager
argument_list|,
literal|"view-snap-to-grid"
argument_list|,
name|snap
argument_list|)
expr_stmt|;
block|}
block|}
end_function

begin_function
name|gboolean
DECL|function|gimp_display_shell_get_snap_to_grid (GimpDisplayShell * shell)
name|gimp_display_shell_get_snap_to_grid
parameter_list|(
name|GimpDisplayShell
modifier|*
name|shell
parameter_list|)
block|{
name|g_return_val_if_fail
argument_list|(
name|GIMP_IS_DISPLAY_SHELL
argument_list|(
name|shell
argument_list|)
argument_list|,
name|FALSE
argument_list|)
expr_stmt|;
return|return
name|shell
operator|->
name|snap_to_grid
return|;
block|}
end_function

begin_function
name|void
DECL|function|gimp_display_shell_set_snap_to_guides (GimpDisplayShell * shell,gboolean snap)
name|gimp_display_shell_set_snap_to_guides
parameter_list|(
name|GimpDisplayShell
modifier|*
name|shell
parameter_list|,
name|gboolean
name|snap
parameter_list|)
block|{
name|g_return_if_fail
argument_list|(
name|GIMP_IS_DISPLAY_SHELL
argument_list|(
name|shell
argument_list|)
argument_list|)
expr_stmt|;
if|if
condition|(
name|snap
operator|!=
name|shell
operator|->
name|snap_to_guides
condition|)
block|{
name|shell
operator|->
name|snap_to_guides
operator|=
name|snap
condition|?
name|TRUE
else|:
name|FALSE
expr_stmt|;
name|SET_ACTIVE
argument_list|(
name|shell
operator|->
name|menubar_manager
argument_list|,
literal|"view-snap-to-guides"
argument_list|,
name|snap
argument_list|)
expr_stmt|;
if|if
condition|(
name|IS_ACTIVE_DISPLAY
argument_list|(
name|shell
argument_list|)
condition|)
name|SET_ACTIVE
argument_list|(
name|shell
operator|->
name|popup_manager
argument_list|,
literal|"view-snap-to-guides"
argument_list|,
name|snap
argument_list|)
expr_stmt|;
block|}
block|}
end_function

begin_function
name|gboolean
DECL|function|gimp_display_shell_get_snap_to_guides (GimpDisplayShell * shell)
name|gimp_display_shell_get_snap_to_guides
parameter_list|(
name|GimpDisplayShell
modifier|*
name|shell
parameter_list|)
block|{
name|g_return_val_if_fail
argument_list|(
name|GIMP_IS_DISPLAY_SHELL
argument_list|(
name|shell
argument_list|)
argument_list|,
name|FALSE
argument_list|)
expr_stmt|;
return|return
name|shell
operator|->
name|snap_to_guides
return|;
block|}
end_function

begin_function
name|void
DECL|function|gimp_display_shell_set_snap_to_canvas (GimpDisplayShell * shell,gboolean snap)
name|gimp_display_shell_set_snap_to_canvas
parameter_list|(
name|GimpDisplayShell
modifier|*
name|shell
parameter_list|,
name|gboolean
name|snap
parameter_list|)
block|{
name|g_return_if_fail
argument_list|(
name|GIMP_IS_DISPLAY_SHELL
argument_list|(
name|shell
argument_list|)
argument_list|)
expr_stmt|;
if|if
condition|(
name|snap
operator|!=
name|shell
operator|->
name|snap_to_canvas
condition|)
block|{
name|shell
operator|->
name|snap_to_canvas
operator|=
name|snap
condition|?
name|TRUE
else|:
name|FALSE
expr_stmt|;
name|SET_ACTIVE
argument_list|(
name|shell
operator|->
name|menubar_manager
argument_list|,
literal|"view-snap-to-canvas"
argument_list|,
name|snap
argument_list|)
expr_stmt|;
if|if
condition|(
name|IS_ACTIVE_DISPLAY
argument_list|(
name|shell
argument_list|)
condition|)
name|SET_ACTIVE
argument_list|(
name|shell
operator|->
name|popup_manager
argument_list|,
literal|"view-snap-to-canvas"
argument_list|,
name|snap
argument_list|)
expr_stmt|;
block|}
block|}
end_function

begin_function
name|gboolean
DECL|function|gimp_display_shell_get_snap_to_canvas (GimpDisplayShell * shell)
name|gimp_display_shell_get_snap_to_canvas
parameter_list|(
name|GimpDisplayShell
modifier|*
name|shell
parameter_list|)
block|{
name|g_return_val_if_fail
argument_list|(
name|GIMP_IS_DISPLAY_SHELL
argument_list|(
name|shell
argument_list|)
argument_list|,
name|FALSE
argument_list|)
expr_stmt|;
return|return
name|shell
operator|->
name|snap_to_canvas
return|;
block|}
end_function

begin_function
name|void
DECL|function|gimp_display_shell_set_snap_to_vectors (GimpDisplayShell * shell,gboolean snap)
name|gimp_display_shell_set_snap_to_vectors
parameter_list|(
name|GimpDisplayShell
modifier|*
name|shell
parameter_list|,
name|gboolean
name|snap
parameter_list|)
block|{
name|g_return_if_fail
argument_list|(
name|GIMP_IS_DISPLAY_SHELL
argument_list|(
name|shell
argument_list|)
argument_list|)
expr_stmt|;
if|if
condition|(
name|snap
operator|!=
name|shell
operator|->
name|snap_to_vectors
condition|)
block|{
name|shell
operator|->
name|snap_to_vectors
operator|=
name|snap
condition|?
name|TRUE
else|:
name|FALSE
expr_stmt|;
name|SET_ACTIVE
argument_list|(
name|shell
operator|->
name|menubar_manager
argument_list|,
literal|"view-snap-to-vectors"
argument_list|,
name|snap
argument_list|)
expr_stmt|;
if|if
condition|(
name|IS_ACTIVE_DISPLAY
argument_list|(
name|shell
argument_list|)
condition|)
name|SET_ACTIVE
argument_list|(
name|shell
operator|->
name|popup_manager
argument_list|,
literal|"view-snap-to-vectors"
argument_list|,
name|snap
argument_list|)
expr_stmt|;
block|}
block|}
end_function

begin_function
name|gboolean
DECL|function|gimp_display_shell_get_snap_to_vectors (GimpDisplayShell * shell)
name|gimp_display_shell_get_snap_to_vectors
parameter_list|(
name|GimpDisplayShell
modifier|*
name|shell
parameter_list|)
block|{
name|g_return_val_if_fail
argument_list|(
name|GIMP_IS_DISPLAY_SHELL
argument_list|(
name|shell
argument_list|)
argument_list|,
name|FALSE
argument_list|)
expr_stmt|;
return|return
name|shell
operator|->
name|snap_to_vectors
return|;
block|}
end_function

begin_function
name|void
DECL|function|gimp_display_shell_set_padding (GimpDisplayShell * shell,GimpCanvasPaddingMode padding_mode,const GimpRGB * padding_color)
name|gimp_display_shell_set_padding
parameter_list|(
name|GimpDisplayShell
modifier|*
name|shell
parameter_list|,
name|GimpCanvasPaddingMode
name|padding_mode
parameter_list|,
specifier|const
name|GimpRGB
modifier|*
name|padding_color
parameter_list|)
block|{
name|GimpDisplayOptions
modifier|*
name|options
decl_stmt|;
name|GimpRGB
name|color
decl_stmt|;
name|g_return_if_fail
argument_list|(
name|GIMP_IS_DISPLAY_SHELL
argument_list|(
name|shell
argument_list|)
argument_list|)
expr_stmt|;
name|g_return_if_fail
argument_list|(
name|padding_color
operator|!=
name|NULL
argument_list|)
expr_stmt|;
name|options
operator|=
name|GET_OPTIONS
argument_list|(
name|shell
argument_list|)
expr_stmt|;
name|color
operator|=
operator|*
name|padding_color
expr_stmt|;
switch|switch
condition|(
name|padding_mode
condition|)
block|{
case|case
name|GIMP_CANVAS_PADDING_MODE_DEFAULT
case|:
if|if
condition|(
name|shell
operator|->
name|canvas
condition|)
block|{
name|gtk_widget_ensure_style
argument_list|(
name|shell
operator|->
name|canvas
argument_list|)
expr_stmt|;
name|gimp_rgb_set_gdk_color
argument_list|(
operator|&
name|color
argument_list|,
name|shell
operator|->
name|canvas
operator|->
name|style
operator|->
name|bg
operator|+
name|GTK_STATE_NORMAL
argument_list|)
expr_stmt|;
block|}
break|break;
case|case
name|GIMP_CANVAS_PADDING_MODE_LIGHT_CHECK
case|:
name|gimp_rgb_set_uchar
argument_list|(
operator|&
name|color
argument_list|,
name|render_blend_light_check
index|[
literal|0
index|]
argument_list|,
name|render_blend_light_check
index|[
literal|1
index|]
argument_list|,
name|render_blend_light_check
index|[
literal|2
index|]
argument_list|)
expr_stmt|;
break|break;
case|case
name|GIMP_CANVAS_PADDING_MODE_DARK_CHECK
case|:
name|gimp_rgb_set_uchar
argument_list|(
operator|&
name|color
argument_list|,
name|render_blend_dark_check
index|[
literal|0
index|]
argument_list|,
name|render_blend_dark_check
index|[
literal|1
index|]
argument_list|,
name|render_blend_dark_check
index|[
literal|2
index|]
argument_list|)
expr_stmt|;
break|break;
case|case
name|GIMP_CANVAS_PADDING_MODE_CUSTOM
case|:
case|case
name|GIMP_CANVAS_PADDING_MODE_RESET
case|:
break|break;
block|}
name|g_object_set
argument_list|(
name|options
argument_list|,
literal|"padding-mode"
argument_list|,
name|padding_mode
argument_list|,
literal|"padding-color"
argument_list|,
operator|&
name|color
argument_list|,
name|NULL
argument_list|)
expr_stmt|;
name|gimp_canvas_set_bg_color
argument_list|(
name|GIMP_CANVAS
argument_list|(
name|shell
operator|->
name|canvas
argument_list|)
argument_list|,
operator|&
name|color
argument_list|)
expr_stmt|;
name|SET_COLOR
argument_list|(
name|shell
operator|->
name|menubar_manager
argument_list|,
literal|"view-padding-color-menu"
argument_list|,
operator|&
name|options
operator|->
name|padding_color
argument_list|)
expr_stmt|;
if|if
condition|(
name|IS_ACTIVE_DISPLAY
argument_list|(
name|shell
argument_list|)
condition|)
name|SET_COLOR
argument_list|(
name|shell
operator|->
name|popup_manager
argument_list|,
literal|"view-padding-color-menu"
argument_list|,
operator|&
name|options
operator|->
name|padding_color
argument_list|)
expr_stmt|;
name|gimp_display_shell_expose_full
argument_list|(
name|shell
argument_list|)
expr_stmt|;
block|}
end_function

begin_function
name|void
DECL|function|gimp_display_shell_get_padding (GimpDisplayShell * shell,GimpCanvasPaddingMode * padding_mode,GimpRGB * padding_color)
name|gimp_display_shell_get_padding
parameter_list|(
name|GimpDisplayShell
modifier|*
name|shell
parameter_list|,
name|GimpCanvasPaddingMode
modifier|*
name|padding_mode
parameter_list|,
name|GimpRGB
modifier|*
name|padding_color
parameter_list|)
block|{
name|GimpDisplayOptions
modifier|*
name|options
decl_stmt|;
name|g_return_if_fail
argument_list|(
name|GIMP_IS_DISPLAY_SHELL
argument_list|(
name|shell
argument_list|)
argument_list|)
expr_stmt|;
name|options
operator|=
name|GET_OPTIONS
argument_list|(
name|shell
argument_list|)
expr_stmt|;
if|if
condition|(
name|padding_mode
condition|)
operator|*
name|padding_mode
operator|=
name|options
operator|->
name|padding_mode
expr_stmt|;
if|if
condition|(
name|padding_color
condition|)
operator|*
name|padding_color
operator|=
name|options
operator|->
name|padding_color
expr_stmt|;
block|}
end_function

end_unit

