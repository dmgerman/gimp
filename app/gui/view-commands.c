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
file|"gui-types.h"
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
file|"display/gimpdisplayshell-scale.h"
end_include

begin_include
include|#
directive|include
file|"widgets/gimpdialogfactory.h"
end_include

begin_include
include|#
directive|include
file|"widgets/gimpitemfactory.h"
end_include

begin_include
include|#
directive|include
file|"dialogs.h"
end_include

begin_include
include|#
directive|include
file|"info-dialog.h"
end_include

begin_include
include|#
directive|include
file|"info-window.h"
end_include

begin_include
include|#
directive|include
file|"grid-dialog.h"
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
value|if (GIMP_IS_DISPLAY (data)) \     gdisp = data; \   else if (GIMP_IS_GIMP (data)) \     gdisp = gimp_context_get_display (gimp_get_user_context (GIMP (data))); \   else \     gdisp = NULL; \   if (! gdisp) \     return
end_define

begin_function
name|void
DECL|function|view_zoom_out_cmd_callback (GtkWidget * widget,gpointer data)
name|view_zoom_out_cmd_callback
parameter_list|(
name|GtkWidget
modifier|*
name|widget
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
argument_list|)
expr_stmt|;
block|}
end_function

begin_function
name|void
DECL|function|view_zoom_in_cmd_callback (GtkWidget * widget,gpointer data)
name|view_zoom_in_cmd_callback
parameter_list|(
name|GtkWidget
modifier|*
name|widget
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
argument_list|)
expr_stmt|;
block|}
end_function

begin_function
name|void
DECL|function|view_zoom_fit_cmd_callback (GtkWidget * widget,gpointer data)
name|view_zoom_fit_cmd_callback
parameter_list|(
name|GtkWidget
modifier|*
name|widget
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
DECL|function|view_zoom_cmd_callback (GtkWidget * widget,gpointer data,guint action)
name|view_zoom_cmd_callback
parameter_list|(
name|GtkWidget
modifier|*
name|widget
parameter_list|,
name|gpointer
name|data
parameter_list|,
name|guint
name|action
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
name|guchar
name|scalesrc
decl_stmt|;
name|guchar
name|scaledest
decl_stmt|;
name|return_if_no_display
argument_list|(
name|gdisp
argument_list|,
name|data
argument_list|)
expr_stmt|;
if|if
condition|(
operator|!
name|GTK_CHECK_MENU_ITEM
argument_list|(
name|widget
argument_list|)
operator|->
name|active
condition|)
return|return;
name|shell
operator|=
name|GIMP_DISPLAY_SHELL
argument_list|(
name|gdisp
operator|->
name|shell
argument_list|)
expr_stmt|;
name|scalesrc
operator|=
name|CLAMP
argument_list|(
name|action
operator|%
literal|100
argument_list|,
literal|1
argument_list|,
literal|0xFF
argument_list|)
expr_stmt|;
name|scaledest
operator|=
name|CLAMP
argument_list|(
name|action
operator|/
literal|100
argument_list|,
literal|1
argument_list|,
literal|0xFF
argument_list|)
expr_stmt|;
if|if
condition|(
name|scalesrc
operator|!=
name|SCALESRC
argument_list|(
name|shell
argument_list|)
operator|||
name|scaledest
operator|!=
name|SCALEDEST
argument_list|(
name|shell
argument_list|)
condition|)
name|gimp_display_shell_scale
argument_list|(
name|shell
argument_list|,
name|action
argument_list|)
expr_stmt|;
block|}
end_function

begin_function
name|void
DECL|function|view_zoom_other_cmd_callback (GtkWidget * widget,gpointer data)
name|view_zoom_other_cmd_callback
parameter_list|(
name|GtkWidget
modifier|*
name|widget
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
if|if
condition|(
operator|!
name|GTK_CHECK_MENU_ITEM
argument_list|(
name|widget
argument_list|)
operator|->
name|active
condition|)
return|return;
name|shell
operator|=
name|GIMP_DISPLAY_SHELL
argument_list|(
name|gdisp
operator|->
name|shell
argument_list|)
expr_stmt|;
comment|/*  check if we are activated by the user or from image_menu_set_zoom()  */
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
end_function

begin_function
name|void
DECL|function|view_dot_for_dot_cmd_callback (GtkWidget * widget,gpointer data)
name|view_dot_for_dot_cmd_callback
parameter_list|(
name|GtkWidget
modifier|*
name|widget
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
name|shell
operator|->
name|dot_for_dot
operator|!=
name|GTK_CHECK_MENU_ITEM
argument_list|(
name|widget
argument_list|)
operator|->
name|active
condition|)
block|{
name|gimp_display_shell_scale_set_dot_for_dot
argument_list|(
name|shell
argument_list|,
name|GTK_CHECK_MENU_ITEM
argument_list|(
name|widget
argument_list|)
operator|->
name|active
argument_list|)
expr_stmt|;
name|gimp_item_factory_set_active
argument_list|(
name|GTK_ITEM_FACTORY
argument_list|(
name|shell
operator|->
name|menubar_factory
argument_list|)
argument_list|,
literal|"/View/Dot for Dot"
argument_list|,
name|shell
operator|->
name|dot_for_dot
argument_list|)
expr_stmt|;
name|gimp_item_factory_set_active
argument_list|(
name|GTK_ITEM_FACTORY
argument_list|(
name|shell
operator|->
name|popup_factory
argument_list|)
argument_list|,
literal|"/View/Dot for Dot"
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
DECL|function|view_fullscreen_cmd_callback (GtkWidget * widget,gpointer data)
name|view_fullscreen_cmd_callback
parameter_list|(
name|GtkWidget
modifier|*
name|widget
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
name|gimp_display_shell_set_fullscreen
argument_list|(
name|shell
argument_list|,
name|GTK_CHECK_MENU_ITEM
argument_list|(
name|widget
argument_list|)
operator|->
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
name|fullscreen
operator|!=
name|GTK_CHECK_MENU_ITEM
argument_list|(
name|widget
argument_list|)
operator|->
name|active
condition|)
block|{
name|gimp_item_factory_set_active
argument_list|(
name|GTK_ITEM_FACTORY
argument_list|(
name|shell
operator|->
name|menubar_factory
argument_list|)
argument_list|,
literal|"/View/Fullscreen"
argument_list|,
name|fullscreen
argument_list|)
expr_stmt|;
name|gimp_item_factory_set_active
argument_list|(
name|GTK_ITEM_FACTORY
argument_list|(
name|shell
operator|->
name|popup_factory
argument_list|)
argument_list|,
literal|"/View/Fullscreen"
argument_list|,
name|fullscreen
argument_list|)
expr_stmt|;
block|}
block|}
end_function

begin_function
name|void
DECL|function|view_info_window_cmd_callback (GtkWidget * widget,gpointer data)
name|view_info_window_cmd_callback
parameter_list|(
name|GtkWidget
modifier|*
name|widget
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
name|info_dialog_popup
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
DECL|function|view_navigation_window_cmd_callback (GtkWidget * widget,gpointer data)
name|view_navigation_window_cmd_callback
parameter_list|(
name|GtkWidget
modifier|*
name|widget
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
DECL|function|view_display_filters_cmd_callback (GtkWidget * widget,gpointer data)
name|view_display_filters_cmd_callback
parameter_list|(
name|GtkWidget
modifier|*
name|widget
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
name|gimp_dialog_factory_dialog_new
argument_list|(
name|global_dialog_factory
argument_list|,
literal|"gimp-display-filters-dialog"
argument_list|,
operator|-
literal|1
argument_list|)
expr_stmt|;
block|}
end_function

begin_function
name|void
DECL|function|view_toggle_selection_cmd_callback (GtkWidget * widget,gpointer data)
name|view_toggle_selection_cmd_callback
parameter_list|(
name|GtkWidget
modifier|*
name|widget
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
name|gimp_display_shell_set_show_selection
argument_list|(
name|shell
argument_list|,
name|GTK_CHECK_MENU_ITEM
argument_list|(
name|widget
argument_list|)
operator|->
name|active
argument_list|)
expr_stmt|;
block|}
end_function

begin_function
name|void
DECL|function|view_toggle_layer_boundary_cmd_callback (GtkWidget * widget,gpointer data)
name|view_toggle_layer_boundary_cmd_callback
parameter_list|(
name|GtkWidget
modifier|*
name|widget
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
name|gimp_display_shell_set_show_layer
argument_list|(
name|shell
argument_list|,
name|GTK_CHECK_MENU_ITEM
argument_list|(
name|widget
argument_list|)
operator|->
name|active
argument_list|)
expr_stmt|;
block|}
end_function

begin_function
name|void
DECL|function|view_toggle_menubar_cmd_callback (GtkWidget * widget,gpointer data)
name|view_toggle_menubar_cmd_callback
parameter_list|(
name|GtkWidget
modifier|*
name|widget
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
name|gimp_display_shell_set_show_menubar
argument_list|(
name|shell
argument_list|,
name|GTK_CHECK_MENU_ITEM
argument_list|(
name|widget
argument_list|)
operator|->
name|active
argument_list|)
expr_stmt|;
block|}
end_function

begin_function
name|void
DECL|function|view_toggle_rulers_cmd_callback (GtkWidget * widget,gpointer data)
name|view_toggle_rulers_cmd_callback
parameter_list|(
name|GtkWidget
modifier|*
name|widget
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
name|gimp_display_shell_set_show_rulers
argument_list|(
name|shell
argument_list|,
name|GTK_CHECK_MENU_ITEM
argument_list|(
name|widget
argument_list|)
operator|->
name|active
argument_list|)
expr_stmt|;
block|}
end_function

begin_function
name|void
DECL|function|view_toggle_scrollbars_cmd_callback (GtkWidget * widget,gpointer data)
name|view_toggle_scrollbars_cmd_callback
parameter_list|(
name|GtkWidget
modifier|*
name|widget
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
name|gimp_display_shell_set_show_scrollbars
argument_list|(
name|shell
argument_list|,
name|GTK_CHECK_MENU_ITEM
argument_list|(
name|widget
argument_list|)
operator|->
name|active
argument_list|)
expr_stmt|;
block|}
end_function

begin_function
name|void
DECL|function|view_toggle_statusbar_cmd_callback (GtkWidget * widget,gpointer data)
name|view_toggle_statusbar_cmd_callback
parameter_list|(
name|GtkWidget
modifier|*
name|widget
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
name|gimp_display_shell_set_show_statusbar
argument_list|(
name|shell
argument_list|,
name|GTK_CHECK_MENU_ITEM
argument_list|(
name|widget
argument_list|)
operator|->
name|active
argument_list|)
expr_stmt|;
block|}
end_function

begin_function
name|void
DECL|function|view_toggle_guides_cmd_callback (GtkWidget * widget,gpointer data)
name|view_toggle_guides_cmd_callback
parameter_list|(
name|GtkWidget
modifier|*
name|widget
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
name|gimp_display_shell_set_show_guides
argument_list|(
name|shell
argument_list|,
name|GTK_CHECK_MENU_ITEM
argument_list|(
name|widget
argument_list|)
operator|->
name|active
argument_list|)
expr_stmt|;
block|}
end_function

begin_function
name|void
DECL|function|view_snap_to_guides_cmd_callback (GtkWidget * widget,gpointer data)
name|view_snap_to_guides_cmd_callback
parameter_list|(
name|GtkWidget
modifier|*
name|widget
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
name|shell
operator|->
name|snap_to_guides
operator|!=
name|GTK_CHECK_MENU_ITEM
argument_list|(
name|widget
argument_list|)
operator|->
name|active
condition|)
block|{
name|shell
operator|->
name|snap_to_guides
operator|=
name|GTK_CHECK_MENU_ITEM
argument_list|(
name|widget
argument_list|)
operator|->
name|active
expr_stmt|;
name|gimp_item_factory_set_active
argument_list|(
name|GTK_ITEM_FACTORY
argument_list|(
name|shell
operator|->
name|menubar_factory
argument_list|)
argument_list|,
literal|"/View/Snap to Guides"
argument_list|,
name|shell
operator|->
name|snap_to_guides
argument_list|)
expr_stmt|;
name|gimp_item_factory_set_active
argument_list|(
name|GTK_ITEM_FACTORY
argument_list|(
name|shell
operator|->
name|popup_factory
argument_list|)
argument_list|,
literal|"/View/Snap to Guides"
argument_list|,
name|shell
operator|->
name|snap_to_guides
argument_list|)
expr_stmt|;
block|}
block|}
end_function

begin_function
name|void
DECL|function|view_configure_grid_cmd_callback (GtkWidget * widget,gpointer data)
name|view_configure_grid_cmd_callback
parameter_list|(
name|GtkWidget
modifier|*
name|widget
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
name|grid_dialog
condition|)
block|{
name|shell
operator|->
name|grid_dialog
operator|=
name|grid_dialog_new
argument_list|(
name|GIMP_DISPLAY
argument_list|(
name|gdisp
argument_list|)
argument_list|)
expr_stmt|;
name|gtk_window_set_transient_for
argument_list|(
name|GTK_WINDOW
argument_list|(
name|shell
operator|->
name|grid_dialog
argument_list|)
argument_list|,
name|GTK_WINDOW
argument_list|(
name|shell
argument_list|)
argument_list|)
expr_stmt|;
name|gtk_window_set_destroy_with_parent
argument_list|(
name|GTK_WINDOW
argument_list|(
name|shell
operator|->
name|grid_dialog
argument_list|)
argument_list|,
name|TRUE
argument_list|)
expr_stmt|;
name|g_object_add_weak_pointer
argument_list|(
name|G_OBJECT
argument_list|(
name|shell
operator|->
name|grid_dialog
argument_list|)
argument_list|,
operator|(
name|gpointer
operator|*
operator|)
operator|&
name|shell
operator|->
name|grid_dialog
argument_list|)
expr_stmt|;
block|}
name|gtk_window_present
argument_list|(
name|GTK_WINDOW
argument_list|(
name|shell
operator|->
name|grid_dialog
argument_list|)
argument_list|)
expr_stmt|;
block|}
end_function

begin_function
name|void
DECL|function|view_toggle_grid_cmd_callback (GtkWidget * widget,gpointer data)
name|view_toggle_grid_cmd_callback
parameter_list|(
name|GtkWidget
modifier|*
name|widget
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
name|gimp_display_shell_set_show_grid
argument_list|(
name|shell
argument_list|,
name|GTK_CHECK_MENU_ITEM
argument_list|(
name|widget
argument_list|)
operator|->
name|active
argument_list|)
expr_stmt|;
block|}
end_function

begin_function
name|void
DECL|function|view_snap_to_grid_cmd_callback (GtkWidget * widget,gpointer data)
name|view_snap_to_grid_cmd_callback
parameter_list|(
name|GtkWidget
modifier|*
name|widget
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
name|shell
operator|->
name|snap_to_grid
operator|!=
name|GTK_CHECK_MENU_ITEM
argument_list|(
name|widget
argument_list|)
operator|->
name|active
condition|)
block|{
name|shell
operator|->
name|snap_to_grid
operator|=
name|GTK_CHECK_MENU_ITEM
argument_list|(
name|widget
argument_list|)
operator|->
name|active
expr_stmt|;
name|gimp_item_factory_set_active
argument_list|(
name|GTK_ITEM_FACTORY
argument_list|(
name|shell
operator|->
name|menubar_factory
argument_list|)
argument_list|,
literal|"/View/Snap to Grid"
argument_list|,
name|shell
operator|->
name|snap_to_grid
argument_list|)
expr_stmt|;
name|gimp_item_factory_set_active
argument_list|(
name|GTK_ITEM_FACTORY
argument_list|(
name|shell
operator|->
name|popup_factory
argument_list|)
argument_list|,
literal|"/View/Snap to Grid"
argument_list|,
name|shell
operator|->
name|snap_to_grid
argument_list|)
expr_stmt|;
block|}
block|}
end_function

begin_function
name|void
DECL|function|view_new_view_cmd_callback (GtkWidget * widget,gpointer data)
name|view_new_view_cmd_callback
parameter_list|(
name|GtkWidget
modifier|*
name|widget
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
DECL|function|view_shrink_wrap_cmd_callback (GtkWidget * widget,gpointer data)
name|view_shrink_wrap_cmd_callback
parameter_list|(
name|GtkWidget
modifier|*
name|widget
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

end_unit

