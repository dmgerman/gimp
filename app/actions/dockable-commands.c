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
file|"widgets/gimpdock.h"
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
file|"widgets/gimpdocked.h"
end_include

begin_include
include|#
directive|include
file|"widgets/gimpsessioninfo.h"
end_include

begin_include
include|#
directive|include
file|"dialogs/dialogs.h"
end_include

begin_include
include|#
directive|include
file|"dockable-commands.h"
end_include

begin_function_decl
specifier|static
name|GimpDockable
modifier|*
name|dockable_get_current
parameter_list|(
name|GimpDockbook
modifier|*
name|dockbook
parameter_list|)
function_decl|;
end_function_decl

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
name|gchar
modifier|*
name|identifier
decl_stmt|;
name|gchar
modifier|*
name|p
decl_stmt|;
name|identifier
operator|=
name|g_strdup
argument_list|(
name|value
argument_list|)
expr_stmt|;
name|p
operator|=
name|strchr
argument_list|(
name|identifier
argument_list|,
literal|'|'
argument_list|)
expr_stmt|;
if|if
condition|(
name|p
condition|)
operator|*
name|p
operator|=
literal|'\0'
expr_stmt|;
name|dockable
operator|=
name|gimp_dialog_factory_dockable_new
argument_list|(
name|gimp_dock_get_dialog_factory
argument_list|(
name|dockbook
operator|->
name|dock
argument_list|)
argument_list|,
name|dockbook
operator|->
name|dock
argument_list|,
name|identifier
argument_list|,
operator|-
literal|1
argument_list|)
expr_stmt|;
name|g_free
argument_list|(
name|identifier
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
init|=
name|dockable_get_current
argument_list|(
name|dockbook
argument_list|)
decl_stmt|;
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
init|=
name|dockable_get_current
argument_list|(
name|dockbook
argument_list|)
decl_stmt|;
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
DECL|function|dockable_lock_tab_cmd_callback (GtkAction * action,gpointer data)
name|dockable_lock_tab_cmd_callback
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
init|=
name|dockable_get_current
argument_list|(
name|dockbook
argument_list|)
decl_stmt|;
if|if
condition|(
name|dockable
condition|)
block|{
name|gboolean
name|lock
init|=
name|gtk_toggle_action_get_active
argument_list|(
name|GTK_TOGGLE_ACTION
argument_list|(
name|action
argument_list|)
argument_list|)
decl_stmt|;
name|gimp_dockable_set_locked
argument_list|(
name|dockable
argument_list|,
name|lock
argument_list|)
expr_stmt|;
block|}
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
name|view_size
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
name|view_size
operator|=
name|gimp_container_view_get_view_size
argument_list|(
name|old_view
argument_list|,
name|NULL
argument_list|)
expr_stmt|;
name|new_dockable
operator|=
name|gimp_dialog_factory_dockable_new
argument_list|(
name|gimp_dock_get_dialog_factory
argument_list|(
name|dockbook
operator|->
name|dock
argument_list|)
argument_list|,
name|dockbook
operator|->
name|dock
argument_list|,
name|identifier
argument_list|,
name|view_size
argument_list|)
expr_stmt|;
if|if
condition|(
name|new_dockable
condition|)
block|{
name|GimpDocked
modifier|*
name|old
decl_stmt|;
name|GimpDocked
modifier|*
name|new
decl_stmt|;
name|gboolean
name|show
decl_stmt|;
name|gimp_dockable_set_locked
argument_list|(
name|GIMP_DOCKABLE
argument_list|(
name|new_dockable
argument_list|)
argument_list|,
name|gimp_dockable_is_locked
argument_list|(
name|dockable
argument_list|)
argument_list|)
expr_stmt|;
name|old
operator|=
name|GIMP_DOCKED
argument_list|(
name|gtk_bin_get_child
argument_list|(
name|GTK_BIN
argument_list|(
name|dockable
argument_list|)
argument_list|)
argument_list|)
expr_stmt|;
name|new
operator|=
name|GIMP_DOCKED
argument_list|(
name|gtk_bin_get_child
argument_list|(
name|GTK_BIN
argument_list|(
name|new_dockable
argument_list|)
argument_list|)
argument_list|)
expr_stmt|;
name|show
operator|=
name|gimp_docked_get_show_button_bar
argument_list|(
name|old
argument_list|)
expr_stmt|;
name|gimp_docked_set_show_button_bar
argument_list|(
name|new
argument_list|,
name|show
argument_list|)
expr_stmt|;
block|}
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
DECL|function|dockable_view_size_cmd_callback (GtkAction * action,GtkAction * current,gpointer data)
name|dockable_view_size_cmd_callback
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
init|=
name|dockable_get_current
argument_list|(
name|dockbook
argument_list|)
decl_stmt|;
name|gint
name|view_size
decl_stmt|;
name|view_size
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
name|dockable
condition|)
block|{
name|GimpContainerView
modifier|*
name|view
init|=
name|gimp_container_view_get_by_dockable
argument_list|(
name|dockable
argument_list|)
decl_stmt|;
if|if
condition|(
name|view
condition|)
block|{
name|gint
name|old_size
decl_stmt|;
name|gint
name|border_width
decl_stmt|;
name|old_size
operator|=
name|gimp_container_view_get_view_size
argument_list|(
name|view
argument_list|,
operator|&
name|border_width
argument_list|)
expr_stmt|;
if|if
condition|(
name|old_size
operator|!=
name|view_size
condition|)
name|gimp_container_view_set_view_size
argument_list|(
name|view
argument_list|,
name|view_size
argument_list|,
name|border_width
argument_list|)
expr_stmt|;
block|}
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
init|=
name|dockable_get_current
argument_list|(
name|dockbook
argument_list|)
decl_stmt|;
name|GimpTabStyle
name|tab_style
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
name|gimp_dockable_set_tab_style
argument_list|(
name|dockable
argument_list|,
name|tab_style
argument_list|)
expr_stmt|;
name|tab_widget
operator|=
name|gimp_dockbook_create_tab_widget
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
DECL|function|dockable_show_button_bar_cmd_callback (GtkAction * action,gpointer data)
name|dockable_show_button_bar_cmd_callback
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
init|=
name|dockable_get_current
argument_list|(
name|dockbook
argument_list|)
decl_stmt|;
if|if
condition|(
name|dockable
condition|)
block|{
name|GimpDocked
modifier|*
name|docked
decl_stmt|;
name|gboolean
name|show
decl_stmt|;
name|docked
operator|=
name|GIMP_DOCKED
argument_list|(
name|gtk_bin_get_child
argument_list|(
name|GTK_BIN
argument_list|(
name|dockable
argument_list|)
argument_list|)
argument_list|)
expr_stmt|;
name|show
operator|=
name|gtk_toggle_action_get_active
argument_list|(
name|GTK_TOGGLE_ACTION
argument_list|(
name|action
argument_list|)
argument_list|)
expr_stmt|;
name|gimp_docked_set_show_button_bar
argument_list|(
name|docked
argument_list|,
name|show
argument_list|)
expr_stmt|;
block|}
block|}
end_function

begin_function
specifier|static
name|GimpDockable
modifier|*
DECL|function|dockable_get_current (GimpDockbook * dockbook)
name|dockable_get_current
parameter_list|(
name|GimpDockbook
modifier|*
name|dockbook
parameter_list|)
block|{
name|gint
name|page_num
init|=
name|gtk_notebook_get_current_page
argument_list|(
name|GTK_NOTEBOOK
argument_list|(
name|dockbook
argument_list|)
argument_list|)
decl_stmt|;
return|return
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
return|;
block|}
end_function

end_unit

