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
file|"widgets/gimpcontainerview.h"
end_include

begin_include
include|#
directive|include
file|"widgets/gimpcontainerview-utils.h"
end_include

begin_include
include|#
directive|include
file|"widgets/gimpdialogfactory.h"
end_include

begin_include
include|#
directive|include
file|"widgets/gimpdockable.h"
end_include

begin_include
include|#
directive|include
file|"widgets/gimpdockbook.h"
end_include

begin_include
include|#
directive|include
file|"widgets/gimpimagedock.h"
end_include

begin_include
include|#
directive|include
file|"widgets/gimpsessioninfo.h"
end_include

begin_include
include|#
directive|include
file|"gui/dialogs.h"
end_include

begin_include
include|#
directive|include
file|"dockable-commands.h"
end_include

begin_comment
comment|/*  public functions  */
end_comment

begin_function
name|void
DECL|function|dockable_add_tab_cmd_callback (GtkAction * action,const gchar * value,gpointer data)
name|dockable_add_tab_cmd_callback
parameter_list|(
name|GtkAction
modifier|*
name|action
parameter_list|,
specifier|const
name|gchar
modifier|*
name|value
parameter_list|,
name|gpointer
name|data
parameter_list|)
block|{
name|GimpDockbook
modifier|*
name|dockbook
init|=
name|GIMP_DOCKBOOK
argument_list|(
name|data
argument_list|)
decl_stmt|;
if|if
condition|(
name|value
condition|)
block|{
name|GtkWidget
modifier|*
name|dockable
decl_stmt|;
name|dockable
operator|=
name|gimp_dialog_factory_dockable_new
argument_list|(
name|dockbook
operator|->
name|dock
operator|->
name|dialog_factory
argument_list|,
name|dockbook
operator|->
name|dock
argument_list|,
name|value
argument_list|,
operator|-
literal|1
argument_list|)
expr_stmt|;
comment|/*  Maybe gimp_dialog_factory_dockable_new() returned an already        *  existing singleton dockable, so check if it already is        *  attached to a dockbook.        */
if|if
condition|(
name|dockable
operator|&&
operator|!
name|GIMP_DOCKABLE
argument_list|(
name|dockable
argument_list|)
operator|->
name|dockbook
condition|)
name|gimp_dockbook_add
argument_list|(
name|dockbook
argument_list|,
name|GIMP_DOCKABLE
argument_list|(
name|dockable
argument_list|)
argument_list|,
operator|-
literal|1
argument_list|)
expr_stmt|;
block|}
block|}
end_function

begin_function
name|void
DECL|function|dockable_close_tab_cmd_callback (GtkAction * action,gpointer data)
name|dockable_close_tab_cmd_callback
parameter_list|(
name|GtkAction
modifier|*
name|action
parameter_list|,
name|gpointer
name|data
parameter_list|)
block|{
name|GimpDockbook
modifier|*
name|dockbook
init|=
name|GIMP_DOCKBOOK
argument_list|(
name|data
argument_list|)
decl_stmt|;
name|GimpDockable
modifier|*
name|dockable
decl_stmt|;
name|gint
name|page_num
decl_stmt|;
name|page_num
operator|=
name|gtk_notebook_get_current_page
argument_list|(
name|GTK_NOTEBOOK
argument_list|(
name|dockbook
argument_list|)
argument_list|)
expr_stmt|;
name|dockable
operator|=
operator|(
name|GimpDockable
operator|*
operator|)
name|gtk_notebook_get_nth_page
argument_list|(
name|GTK_NOTEBOOK
argument_list|(
name|dockbook
argument_list|)
argument_list|,
name|page_num
argument_list|)
expr_stmt|;
if|if
condition|(
name|dockable
condition|)
name|gimp_dockbook_remove
argument_list|(
name|dockbook
argument_list|,
name|dockable
argument_list|)
expr_stmt|;
block|}
end_function

begin_function
name|void
DECL|function|dockable_detach_tab_cmd_callback (GtkAction * action,gpointer data)
name|dockable_detach_tab_cmd_callback
parameter_list|(
name|GtkAction
modifier|*
name|action
parameter_list|,
name|gpointer
name|data
parameter_list|)
block|{
name|GimpDockbook
modifier|*
name|dockbook
init|=
name|GIMP_DOCKBOOK
argument_list|(
name|data
argument_list|)
decl_stmt|;
name|GimpDockable
modifier|*
name|dockable
decl_stmt|;
name|gint
name|page_num
decl_stmt|;
name|page_num
operator|=
name|gtk_notebook_get_current_page
argument_list|(
name|GTK_NOTEBOOK
argument_list|(
name|dockbook
argument_list|)
argument_list|)
expr_stmt|;
name|dockable
operator|=
operator|(
name|GimpDockable
operator|*
operator|)
name|gtk_notebook_get_nth_page
argument_list|(
name|GTK_NOTEBOOK
argument_list|(
name|dockbook
argument_list|)
argument_list|,
name|page_num
argument_list|)
expr_stmt|;
if|if
condition|(
name|dockable
condition|)
name|gimp_dockable_detach
argument_list|(
name|dockable
argument_list|)
expr_stmt|;
block|}
end_function

begin_function
name|void
DECL|function|dockable_toggle_view_cmd_callback (GtkAction * action,GtkAction * current,gpointer data)
name|dockable_toggle_view_cmd_callback
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
name|GimpDockbook
modifier|*
name|dockbook
init|=
name|GIMP_DOCKBOOK
argument_list|(
name|data
argument_list|)
decl_stmt|;
name|GimpDockable
modifier|*
name|dockable
decl_stmt|;
name|GimpViewType
name|view_type
decl_stmt|;
name|gint
name|page_num
decl_stmt|;
name|view_type
operator|=
operator|(
name|GimpViewType
operator|)
name|gtk_radio_action_get_current_value
argument_list|(
name|GTK_RADIO_ACTION
argument_list|(
name|action
argument_list|)
argument_list|)
expr_stmt|;
name|page_num
operator|=
name|gtk_notebook_get_current_page
argument_list|(
name|GTK_NOTEBOOK
argument_list|(
name|dockbook
argument_list|)
argument_list|)
expr_stmt|;
name|dockable
operator|=
operator|(
name|GimpDockable
operator|*
operator|)
name|gtk_notebook_get_nth_page
argument_list|(
name|GTK_NOTEBOOK
argument_list|(
name|dockbook
argument_list|)
argument_list|,
name|page_num
argument_list|)
expr_stmt|;
if|if
condition|(
name|dockable
condition|)
block|{
name|GimpDialogFactoryEntry
modifier|*
name|entry
decl_stmt|;
name|gimp_dialog_factory_from_widget
argument_list|(
name|GTK_WIDGET
argument_list|(
name|dockable
argument_list|)
argument_list|,
operator|&
name|entry
argument_list|)
expr_stmt|;
if|if
condition|(
name|entry
condition|)
block|{
name|gchar
modifier|*
name|identifier
decl_stmt|;
name|gchar
modifier|*
name|substring
init|=
name|NULL
decl_stmt|;
name|identifier
operator|=
name|g_strdup
argument_list|(
name|entry
operator|->
name|identifier
argument_list|)
expr_stmt|;
name|substring
operator|=
name|strstr
argument_list|(
name|identifier
argument_list|,
literal|"grid"
argument_list|)
expr_stmt|;
if|if
condition|(
name|substring
operator|&&
name|view_type
operator|==
name|GIMP_VIEW_TYPE_GRID
condition|)
return|return;
if|if
condition|(
operator|!
name|substring
condition|)
block|{
name|substring
operator|=
name|strstr
argument_list|(
name|identifier
argument_list|,
literal|"list"
argument_list|)
expr_stmt|;
if|if
condition|(
name|substring
operator|&&
name|view_type
operator|==
name|GIMP_VIEW_TYPE_LIST
condition|)
return|return;
block|}
if|if
condition|(
name|substring
condition|)
block|{
name|GimpContainerView
modifier|*
name|old_view
decl_stmt|;
name|GtkWidget
modifier|*
name|new_dockable
decl_stmt|;
name|gint
name|preview_size
init|=
operator|-
literal|1
decl_stmt|;
if|if
condition|(
name|view_type
operator|==
name|GIMP_VIEW_TYPE_LIST
condition|)
name|memcpy
argument_list|(
name|substring
argument_list|,
literal|"list"
argument_list|,
literal|4
argument_list|)
expr_stmt|;
elseif|else
if|if
condition|(
name|view_type
operator|==
name|GIMP_VIEW_TYPE_GRID
condition|)
name|memcpy
argument_list|(
name|substring
argument_list|,
literal|"grid"
argument_list|,
literal|4
argument_list|)
expr_stmt|;
name|old_view
operator|=
name|gimp_container_view_get_by_dockable
argument_list|(
name|dockable
argument_list|)
expr_stmt|;
if|if
condition|(
name|old_view
condition|)
name|preview_size
operator|=
name|old_view
operator|->
name|preview_size
expr_stmt|;
name|new_dockable
operator|=
name|gimp_dialog_factory_dockable_new
argument_list|(
name|dockbook
operator|->
name|dock
operator|->
name|dialog_factory
argument_list|,
name|dockbook
operator|->
name|dock
argument_list|,
name|identifier
argument_list|,
name|preview_size
argument_list|)
expr_stmt|;
comment|/*  Maybe gimp_dialog_factory_dockable_new() returned                *  an already existing singleton dockable, so check                *  if it already is attached to a dockbook.                */
if|if
condition|(
name|new_dockable
operator|&&
operator|!
name|GIMP_DOCKABLE
argument_list|(
name|new_dockable
argument_list|)
operator|->
name|dockbook
condition|)
block|{
name|gimp_dockbook_add
argument_list|(
name|dockbook
argument_list|,
name|GIMP_DOCKABLE
argument_list|(
name|new_dockable
argument_list|)
argument_list|,
name|page_num
argument_list|)
expr_stmt|;
name|gimp_dockbook_remove
argument_list|(
name|dockbook
argument_list|,
name|dockable
argument_list|)
expr_stmt|;
name|gtk_notebook_set_current_page
argument_list|(
name|GTK_NOTEBOOK
argument_list|(
name|dockbook
argument_list|)
argument_list|,
name|page_num
argument_list|)
expr_stmt|;
block|}
block|}
name|g_free
argument_list|(
name|identifier
argument_list|)
expr_stmt|;
block|}
block|}
block|}
end_function

begin_function
name|void
DECL|function|dockable_preview_size_cmd_callback (GtkAction * action,GtkAction * current,gpointer data)
name|dockable_preview_size_cmd_callback
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
name|GimpDockbook
modifier|*
name|dockbook
init|=
name|GIMP_DOCKBOOK
argument_list|(
name|data
argument_list|)
decl_stmt|;
name|GimpDockable
modifier|*
name|dockable
decl_stmt|;
name|gint
name|preview_size
decl_stmt|;
name|gint
name|page_num
decl_stmt|;
name|preview_size
operator|=
name|gtk_radio_action_get_current_value
argument_list|(
name|GTK_RADIO_ACTION
argument_list|(
name|action
argument_list|)
argument_list|)
expr_stmt|;
name|page_num
operator|=
name|gtk_notebook_get_current_page
argument_list|(
name|GTK_NOTEBOOK
argument_list|(
name|dockbook
argument_list|)
argument_list|)
expr_stmt|;
name|dockable
operator|=
operator|(
name|GimpDockable
operator|*
operator|)
name|gtk_notebook_get_nth_page
argument_list|(
name|GTK_NOTEBOOK
argument_list|(
name|dockbook
argument_list|)
argument_list|,
name|page_num
argument_list|)
expr_stmt|;
if|if
condition|(
name|dockable
condition|)
block|{
name|GimpContainerView
modifier|*
name|view
decl_stmt|;
name|view
operator|=
name|gimp_container_view_get_by_dockable
argument_list|(
name|dockable
argument_list|)
expr_stmt|;
if|if
condition|(
name|view
operator|&&
name|view
operator|->
name|preview_size
operator|!=
name|preview_size
condition|)
name|gimp_container_view_set_preview_size
argument_list|(
name|view
argument_list|,
name|preview_size
argument_list|,
name|view
operator|->
name|preview_border_width
argument_list|)
expr_stmt|;
block|}
block|}
end_function

begin_function
name|void
DECL|function|dockable_tab_style_cmd_callback (GtkAction * action,GtkAction * current,gpointer data)
name|dockable_tab_style_cmd_callback
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
name|GimpDockbook
modifier|*
name|dockbook
init|=
name|GIMP_DOCKBOOK
argument_list|(
name|data
argument_list|)
decl_stmt|;
name|GimpDockable
modifier|*
name|dockable
decl_stmt|;
name|GimpTabStyle
name|tab_style
decl_stmt|;
name|gint
name|page_num
decl_stmt|;
name|tab_style
operator|=
operator|(
name|GimpTabStyle
operator|)
name|gtk_radio_action_get_current_value
argument_list|(
name|GTK_RADIO_ACTION
argument_list|(
name|action
argument_list|)
argument_list|)
expr_stmt|;
name|page_num
operator|=
name|gtk_notebook_get_current_page
argument_list|(
name|GTK_NOTEBOOK
argument_list|(
name|dockbook
argument_list|)
argument_list|)
expr_stmt|;
name|dockable
operator|=
operator|(
name|GimpDockable
operator|*
operator|)
name|gtk_notebook_get_nth_page
argument_list|(
name|GTK_NOTEBOOK
argument_list|(
name|dockbook
argument_list|)
argument_list|,
name|page_num
argument_list|)
expr_stmt|;
if|if
condition|(
name|dockable
operator|&&
name|dockable
operator|->
name|tab_style
operator|!=
name|tab_style
condition|)
block|{
name|GtkWidget
modifier|*
name|tab_widget
decl_stmt|;
name|dockable
operator|->
name|tab_style
operator|=
name|tab_style
expr_stmt|;
name|tab_widget
operator|=
name|gimp_dockbook_get_tab_widget
argument_list|(
name|dockbook
argument_list|,
name|dockable
argument_list|)
expr_stmt|;
name|gtk_notebook_set_tab_label
argument_list|(
name|GTK_NOTEBOOK
argument_list|(
name|dockbook
argument_list|)
argument_list|,
name|GTK_WIDGET
argument_list|(
name|dockable
argument_list|)
argument_list|,
name|tab_widget
argument_list|)
expr_stmt|;
block|}
block|}
end_function

begin_function
name|void
DECL|function|dockable_toggle_image_menu_cmd_callback (GtkAction * action,gpointer data)
name|dockable_toggle_image_menu_cmd_callback
parameter_list|(
name|GtkAction
modifier|*
name|action
parameter_list|,
name|gpointer
name|data
parameter_list|)
block|{
name|GimpDockbook
modifier|*
name|dockbook
init|=
name|GIMP_DOCKBOOK
argument_list|(
name|data
argument_list|)
decl_stmt|;
name|gboolean
name|active
decl_stmt|;
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
name|GIMP_IS_IMAGE_DOCK
argument_list|(
name|dockbook
operator|->
name|dock
argument_list|)
condition|)
name|gimp_image_dock_set_show_image_menu
argument_list|(
name|GIMP_IMAGE_DOCK
argument_list|(
name|dockbook
operator|->
name|dock
argument_list|)
argument_list|,
name|active
argument_list|)
expr_stmt|;
block|}
end_function

begin_function
name|void
DECL|function|dockable_toggle_auto_cmd_callback (GtkAction * action,gpointer data)
name|dockable_toggle_auto_cmd_callback
parameter_list|(
name|GtkAction
modifier|*
name|action
parameter_list|,
name|gpointer
name|data
parameter_list|)
block|{
name|GimpDockbook
modifier|*
name|dockbook
init|=
name|GIMP_DOCKBOOK
argument_list|(
name|data
argument_list|)
decl_stmt|;
name|gboolean
name|active
decl_stmt|;
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
name|GIMP_IS_IMAGE_DOCK
argument_list|(
name|dockbook
operator|->
name|dock
argument_list|)
condition|)
name|gimp_image_dock_set_auto_follow_active
argument_list|(
name|GIMP_IMAGE_DOCK
argument_list|(
name|dockbook
operator|->
name|dock
argument_list|)
argument_list|,
name|active
argument_list|)
expr_stmt|;
block|}
end_function

begin_function
specifier|static
name|void
DECL|function|dockable_change_screen_confirm_callback (GtkWidget * query_box,gint value,gpointer data)
name|dockable_change_screen_confirm_callback
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
DECL|function|dockable_change_screen_destroy_callback (GtkWidget * query_box,GtkWidget * dock)
name|dockable_change_screen_destroy_callback
parameter_list|(
name|GtkWidget
modifier|*
name|query_box
parameter_list|,
name|GtkWidget
modifier|*
name|dock
parameter_list|)
block|{
name|g_object_set_data
argument_list|(
name|G_OBJECT
argument_list|(
name|dock
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
DECL|function|dockable_change_screen_cmd_callback (GtkAction * action,gpointer data)
name|dockable_change_screen_cmd_callback
parameter_list|(
name|GtkAction
modifier|*
name|action
parameter_list|,
name|gpointer
name|data
parameter_list|)
block|{
name|GimpDockbook
modifier|*
name|dockbook
init|=
name|GIMP_DOCKBOOK
argument_list|(
name|data
argument_list|)
decl_stmt|;
name|GtkWidget
modifier|*
name|dock
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
name|dock
operator|=
name|GTK_WIDGET
argument_list|(
name|dockbook
operator|->
name|dock
argument_list|)
expr_stmt|;
name|qbox
operator|=
name|g_object_get_data
argument_list|(
name|G_OBJECT
argument_list|(
name|dock
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
name|dock
argument_list|)
expr_stmt|;
name|display
operator|=
name|gtk_widget_get_display
argument_list|(
name|dock
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
literal|"Move Dock to Screen"
argument_list|,
name|dock
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
name|dock
argument_list|)
argument_list|,
literal|"destroy"
argument_list|,
name|dockable_change_screen_confirm_callback
argument_list|,
name|dock
argument_list|)
expr_stmt|;
name|g_object_set_data
argument_list|(
name|G_OBJECT
argument_list|(
name|dock
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
name|dockable_change_screen_destroy_callback
argument_list|)
argument_list|,
name|dock
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

