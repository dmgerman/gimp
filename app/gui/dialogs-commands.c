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
file|"gui-types.h"
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
file|"dialogs.h"
end_include

begin_include
include|#
directive|include
file|"dialogs-commands.h"
end_include

begin_comment
comment|/*  local function prototypes  */
end_comment

begin_function_decl
specifier|static
name|void
name|dialogs_create_dock
parameter_list|(
specifier|const
name|gchar
modifier|*
name|tabs
index|[]
parameter_list|,
name|gint
name|n_tabs
parameter_list|)
function_decl|;
end_function_decl

begin_comment
comment|/*  public functions  */
end_comment

begin_function
name|void
DECL|function|dialogs_show_toolbox_cmd_callback (GtkWidget * widget,gpointer data,guint action)
name|dialogs_show_toolbox_cmd_callback
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
name|dialogs_show_toolbox
argument_list|()
expr_stmt|;
block|}
end_function

begin_function
name|void
DECL|function|dialogs_create_toplevel_cmd_callback (GtkWidget * widget,gpointer data,guint action)
name|dialogs_create_toplevel_cmd_callback
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
if|if
condition|(
name|action
condition|)
block|{
specifier|const
name|gchar
modifier|*
name|identifier
init|=
name|g_quark_to_string
argument_list|(
operator|(
name|GQuark
operator|)
name|action
argument_list|)
decl_stmt|;
if|if
condition|(
name|identifier
condition|)
name|gimp_dialog_factory_dialog_new
argument_list|(
name|global_dialog_factory
argument_list|,
name|identifier
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
DECL|function|dialogs_create_dockable_cmd_callback (GtkWidget * widget,gpointer data,guint action)
name|dialogs_create_dockable_cmd_callback
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
if|if
condition|(
name|action
condition|)
block|{
specifier|const
name|gchar
modifier|*
name|identifier
init|=
name|g_quark_to_string
argument_list|(
operator|(
name|GQuark
operator|)
name|action
argument_list|)
decl_stmt|;
if|if
condition|(
operator|!
name|identifier
condition|)
return|return;
comment|/*  If the identifier is a list, try to find a matching dialog and        *  raise it. If there's no match, use the first list item.        */
if|if
condition|(
name|strchr
argument_list|(
name|identifier
argument_list|,
literal|'|'
argument_list|)
condition|)
block|{
name|gchar
modifier|*
modifier|*
name|ids
init|=
name|g_strsplit
argument_list|(
name|identifier
argument_list|,
literal|"|"
argument_list|,
literal|0
argument_list|)
decl_stmt|;
name|gint
name|i
decl_stmt|;
for|for
control|(
name|i
operator|=
literal|0
init|;
name|ids
index|[
name|i
index|]
condition|;
name|i
operator|++
control|)
block|{
name|GimpSessionInfo
modifier|*
name|info
decl_stmt|;
name|info
operator|=
name|gimp_dialog_factory_find_session_info
argument_list|(
name|global_dock_factory
argument_list|,
name|ids
index|[
name|i
index|]
argument_list|)
expr_stmt|;
if|if
condition|(
name|info
operator|&&
name|info
operator|->
name|widget
condition|)
break|break;
block|}
name|gimp_dialog_factory_dialog_raise
argument_list|(
name|global_dock_factory
argument_list|,
name|ids
index|[
name|i
index|]
condition|?
name|ids
index|[
name|i
index|]
else|:
name|ids
index|[
literal|0
index|]
argument_list|,
operator|-
literal|1
argument_list|)
expr_stmt|;
name|g_strfreev
argument_list|(
name|ids
argument_list|)
expr_stmt|;
block|}
else|else
block|{
name|gimp_dialog_factory_dialog_raise
argument_list|(
name|global_dock_factory
argument_list|,
name|identifier
argument_list|,
operator|-
literal|1
argument_list|)
expr_stmt|;
block|}
block|}
block|}
end_function

begin_function
name|void
DECL|function|dialogs_add_tab_cmd_callback (GtkWidget * widget,gpointer data,guint action)
name|dialogs_add_tab_cmd_callback
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
name|action
condition|)
block|{
name|GtkWidget
modifier|*
name|dockable
decl_stmt|;
specifier|const
name|gchar
modifier|*
name|identifier
decl_stmt|;
name|identifier
operator|=
name|g_quark_to_string
argument_list|(
operator|(
name|GQuark
operator|)
name|action
argument_list|)
expr_stmt|;
if|if
condition|(
name|identifier
condition|)
block|{
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
name|identifier
argument_list|,
operator|-
literal|1
argument_list|)
expr_stmt|;
comment|/*  Maybe gimp_dialog_factory_dockable_new() returned an already 	   *  existing singleton dockable, so check if it already is 	   *  attached to a dockbook. 	   */
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
block|}
end_function

begin_function
name|void
DECL|function|dialogs_close_tab_cmd_callback (GtkWidget * widget,gpointer data,guint action)
name|dialogs_close_tab_cmd_callback
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
DECL|function|dialogs_detach_tab_cmd_callback (GtkWidget * widget,gpointer data,guint action)
name|dialogs_detach_tab_cmd_callback
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
block|{
comment|/* TODO */
block|}
block|}
end_function

begin_function
name|void
DECL|function|dialogs_toggle_view_cmd_callback (GtkWidget * widget,gpointer data,guint action)
name|dialogs_toggle_view_cmd_callback
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
name|view_type
operator|=
operator|(
name|GimpViewType
operator|)
name|action
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
name|entry
operator|=
name|g_object_get_data
argument_list|(
name|G_OBJECT
argument_list|(
name|dockable
argument_list|)
argument_list|,
literal|"gimp-dialog-factory-entry"
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
DECL|function|dialogs_preview_size_cmd_callback (GtkWidget * widget,gpointer data,guint action)
name|dialogs_preview_size_cmd_callback
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
name|preview_size
operator|=
operator|(
name|gint
operator|)
name|action
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
condition|)
block|{
if|if
condition|(
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
block|}
end_function

begin_function
name|void
DECL|function|dialogs_tab_style_cmd_callback (GtkWidget * widget,gpointer data,guint action)
name|dialogs_tab_style_cmd_callback
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
name|tab_style
operator|=
operator|(
name|gint
operator|)
name|action
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
if|if
condition|(
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
block|}
end_function

begin_function
name|void
DECL|function|dialogs_toggle_image_menu_cmd_callback (GtkWidget * widget,gpointer data,guint action)
name|dialogs_toggle_image_menu_cmd_callback
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
name|GIMP_IS_IMAGE_DOCK
argument_list|(
name|dockbook
operator|->
name|dock
argument_list|)
condition|)
block|{
name|gimp_image_dock_set_show_image_menu
argument_list|(
name|GIMP_IMAGE_DOCK
argument_list|(
name|dockbook
operator|->
name|dock
argument_list|)
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
block|}
end_function

begin_function
name|void
DECL|function|dialogs_toggle_auto_cmd_callback (GtkWidget * widget,gpointer data,guint action)
name|dialogs_toggle_auto_cmd_callback
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
name|GIMP_IS_IMAGE_DOCK
argument_list|(
name|dockbook
operator|->
name|dock
argument_list|)
condition|)
block|{
name|gimp_image_dock_set_auto_follow_active
argument_list|(
name|GIMP_IMAGE_DOCK
argument_list|(
name|dockbook
operator|->
name|dock
argument_list|)
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
block|}
end_function

begin_function
name|void
DECL|function|dialogs_create_lc_cmd_callback (GtkWidget * widget,gpointer data,guint action)
name|dialogs_create_lc_cmd_callback
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
specifier|static
specifier|const
name|gchar
modifier|*
name|tabs
index|[]
init|=
block|{
literal|"gimp-layer-list"
block|,
literal|"gimp-channel-list"
block|,
literal|"gimp-vectors-list"
block|,
literal|"gimp-indexed-palette"
block|}
decl_stmt|;
name|dialogs_create_dock
argument_list|(
name|tabs
argument_list|,
name|G_N_ELEMENTS
argument_list|(
name|tabs
argument_list|)
argument_list|)
expr_stmt|;
block|}
end_function

begin_function
name|void
DECL|function|dialogs_create_data_cmd_callback (GtkWidget * widget,gpointer data,guint action)
name|dialogs_create_data_cmd_callback
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
specifier|static
specifier|const
name|gchar
modifier|*
name|tabs
index|[]
init|=
block|{
literal|"gimp-brush-grid"
block|,
literal|"gimp-pattern-grid"
block|,
literal|"gimp-gradient-list"
block|,
literal|"gimp-palette-list"
block|,
literal|"gimp-font-list"
block|}
decl_stmt|;
name|dialogs_create_dock
argument_list|(
name|tabs
argument_list|,
name|G_N_ELEMENTS
argument_list|(
name|tabs
argument_list|)
argument_list|)
expr_stmt|;
block|}
end_function

begin_function
name|void
DECL|function|dialogs_create_stuff_cmd_callback (GtkWidget * widget,gpointer data,guint action)
name|dialogs_create_stuff_cmd_callback
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
specifier|static
specifier|const
name|gchar
modifier|*
name|tabs
index|[]
init|=
block|{
literal|"gimp-buffer-list"
block|,
literal|"gimp-image-list"
block|,
literal|"gimp-document-list"
block|,
literal|"gimp-template-list"
block|}
decl_stmt|;
name|dialogs_create_dock
argument_list|(
name|tabs
argument_list|,
name|G_N_ELEMENTS
argument_list|(
name|tabs
argument_list|)
argument_list|)
expr_stmt|;
block|}
end_function

begin_function
name|void
DECL|function|dialogs_show_toolbox (void)
name|dialogs_show_toolbox
parameter_list|(
name|void
parameter_list|)
block|{
if|if
condition|(
operator|!
name|global_toolbox_factory
operator|->
name|open_dialogs
condition|)
block|{
name|GtkWidget
modifier|*
name|toolbox
decl_stmt|;
name|toolbox
operator|=
name|gimp_dialog_factory_dock_new
argument_list|(
name|global_toolbox_factory
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
name|GList
modifier|*
name|list
decl_stmt|;
for|for
control|(
name|list
operator|=
name|global_toolbox_factory
operator|->
name|open_dialogs
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
if|if
condition|(
name|GTK_WIDGET_TOPLEVEL
argument_list|(
name|list
operator|->
name|data
argument_list|)
condition|)
block|{
name|gtk_window_present
argument_list|(
name|GTK_WINDOW
argument_list|(
name|list
operator|->
name|data
argument_list|)
argument_list|)
expr_stmt|;
break|break;
block|}
block|}
block|}
block|}
end_function

begin_comment
comment|/*  private functions  */
end_comment

begin_function
specifier|static
name|void
DECL|function|dialogs_create_dock (const gchar * tabs[],gint n_tabs)
name|dialogs_create_dock
parameter_list|(
specifier|const
name|gchar
modifier|*
name|tabs
index|[]
parameter_list|,
name|gint
name|n_tabs
parameter_list|)
block|{
name|GtkWidget
modifier|*
name|dock
decl_stmt|;
name|GtkWidget
modifier|*
name|dockbook
decl_stmt|;
name|GtkWidget
modifier|*
name|dockable
decl_stmt|;
name|gint
name|i
decl_stmt|;
name|dock
operator|=
name|gimp_dialog_factory_dock_new
argument_list|(
name|global_dock_factory
argument_list|)
expr_stmt|;
name|dockbook
operator|=
name|gimp_dockbook_new
argument_list|(
name|global_dock_factory
operator|->
name|menu_factory
argument_list|)
expr_stmt|;
name|gimp_dock_add_book
argument_list|(
name|GIMP_DOCK
argument_list|(
name|dock
argument_list|)
argument_list|,
name|GIMP_DOCKBOOK
argument_list|(
name|dockbook
argument_list|)
argument_list|,
literal|0
argument_list|)
expr_stmt|;
for|for
control|(
name|i
operator|=
literal|0
init|;
name|i
operator|<
name|n_tabs
condition|;
name|i
operator|++
control|)
block|{
name|dockable
operator|=
name|gimp_dialog_factory_dialog_new
argument_list|(
name|global_dock_factory
argument_list|,
name|tabs
index|[
name|i
index|]
argument_list|,
operator|-
literal|1
argument_list|)
expr_stmt|;
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
name|gimp_dock_add
argument_list|(
name|GIMP_DOCK
argument_list|(
name|dock
argument_list|)
argument_list|,
name|GIMP_DOCKABLE
argument_list|(
name|dockable
argument_list|)
argument_list|,
operator|-
literal|1
argument_list|,
operator|-
literal|1
argument_list|)
expr_stmt|;
block|}
name|gtk_widget_show
argument_list|(
name|dock
argument_list|)
expr_stmt|;
block|}
end_function

end_unit

