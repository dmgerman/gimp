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
file|"libgimpthumb/gimpthumb.h"
end_include

begin_include
include|#
directive|include
file|"menus-types.h"
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
file|"core/gimpimage.h"
end_include

begin_include
include|#
directive|include
file|"core/gimplist.h"
end_include

begin_include
include|#
directive|include
file|"core/gimpviewable.h"
end_include

begin_include
include|#
directive|include
file|"widgets/gimpaction.h"
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
file|"widgets/gimpdockwindow.h"
end_include

begin_include
include|#
directive|include
file|"widgets/gimpsessioninfo.h"
end_include

begin_include
include|#
directive|include
file|"widgets/gimpuimanager.h"
end_include

begin_include
include|#
directive|include
file|"display/gimpdisplay.h"
end_include

begin_include
include|#
directive|include
file|"dialogs/dialogs.h"
end_include

begin_include
include|#
directive|include
file|"actions/windows-actions.h"
end_include

begin_include
include|#
directive|include
file|"windows-menu.h"
end_include

begin_function_decl
specifier|static
name|void
name|windows_menu_display_add
parameter_list|(
name|GimpContainer
modifier|*
name|container
parameter_list|,
name|GimpDisplay
modifier|*
name|display
parameter_list|,
name|GimpUIManager
modifier|*
name|manager
parameter_list|)
function_decl|;
end_function_decl

begin_function_decl
specifier|static
name|void
name|windows_menu_display_remove
parameter_list|(
name|GimpContainer
modifier|*
name|container
parameter_list|,
name|GimpDisplay
modifier|*
name|display
parameter_list|,
name|GimpUIManager
modifier|*
name|manager
parameter_list|)
function_decl|;
end_function_decl

begin_function_decl
specifier|static
name|void
name|windows_menu_display_reorder
parameter_list|(
name|GimpContainer
modifier|*
name|container
parameter_list|,
name|GimpDisplay
modifier|*
name|display
parameter_list|,
name|gint
name|new_index
parameter_list|,
name|GimpUIManager
modifier|*
name|manager
parameter_list|)
function_decl|;
end_function_decl

begin_function_decl
specifier|static
name|void
name|windows_menu_image_notify
parameter_list|(
name|GimpDisplay
modifier|*
name|display
parameter_list|,
specifier|const
name|GParamSpec
modifier|*
name|unused
parameter_list|,
name|GimpUIManager
modifier|*
name|manager
parameter_list|)
function_decl|;
end_function_decl

begin_function_decl
specifier|static
name|void
name|windows_menu_dock_window_added
parameter_list|(
name|GimpDialogFactory
modifier|*
name|factory
parameter_list|,
name|GimpDockWindow
modifier|*
name|dock_window
parameter_list|,
name|GimpUIManager
modifier|*
name|manager
parameter_list|)
function_decl|;
end_function_decl

begin_function_decl
specifier|static
name|void
name|windows_menu_dock_window_removed
parameter_list|(
name|GimpDialogFactory
modifier|*
name|factory
parameter_list|,
name|GimpDockWindow
modifier|*
name|dock_window
parameter_list|,
name|GimpUIManager
modifier|*
name|manager
parameter_list|)
function_decl|;
end_function_decl

begin_function_decl
specifier|static
name|gchar
modifier|*
name|windows_menu_dock_window_to_merge_id
parameter_list|(
name|GimpDockWindow
modifier|*
name|dock_window
parameter_list|)
function_decl|;
end_function_decl

begin_function_decl
specifier|static
name|void
name|windows_menu_recent_add
parameter_list|(
name|GimpContainer
modifier|*
name|container
parameter_list|,
name|GimpSessionInfo
modifier|*
name|info
parameter_list|,
name|GimpUIManager
modifier|*
name|manager
parameter_list|)
function_decl|;
end_function_decl

begin_function_decl
specifier|static
name|void
name|windows_menu_recent_remove
parameter_list|(
name|GimpContainer
modifier|*
name|container
parameter_list|,
name|GimpSessionInfo
modifier|*
name|info
parameter_list|,
name|GimpUIManager
modifier|*
name|manager
parameter_list|)
function_decl|;
end_function_decl

begin_function_decl
specifier|static
name|gboolean
name|windows_menu_display_query_tooltip
parameter_list|(
name|GtkWidget
modifier|*
name|widget
parameter_list|,
name|gint
name|x
parameter_list|,
name|gint
name|y
parameter_list|,
name|gboolean
name|keyboard_mode
parameter_list|,
name|GtkTooltip
modifier|*
name|tooltip
parameter_list|,
name|GimpAction
modifier|*
name|action
parameter_list|)
function_decl|;
end_function_decl

begin_function
name|void
DECL|function|windows_menu_setup (GimpUIManager * manager,const gchar * ui_path)
name|windows_menu_setup
parameter_list|(
name|GimpUIManager
modifier|*
name|manager
parameter_list|,
specifier|const
name|gchar
modifier|*
name|ui_path
parameter_list|)
block|{
name|GList
modifier|*
name|list
decl_stmt|;
name|g_return_if_fail
argument_list|(
name|GIMP_IS_UI_MANAGER
argument_list|(
name|manager
argument_list|)
argument_list|)
expr_stmt|;
name|g_return_if_fail
argument_list|(
name|ui_path
operator|!=
name|NULL
argument_list|)
expr_stmt|;
name|g_object_set_data
argument_list|(
name|G_OBJECT
argument_list|(
name|manager
argument_list|)
argument_list|,
literal|"image-menu-ui-path"
argument_list|,
operator|(
name|gpointer
operator|)
name|ui_path
argument_list|)
expr_stmt|;
name|g_signal_connect_object
argument_list|(
name|manager
operator|->
name|gimp
operator|->
name|displays
argument_list|,
literal|"add"
argument_list|,
name|G_CALLBACK
argument_list|(
name|windows_menu_display_add
argument_list|)
argument_list|,
name|manager
argument_list|,
literal|0
argument_list|)
expr_stmt|;
name|g_signal_connect_object
argument_list|(
name|manager
operator|->
name|gimp
operator|->
name|displays
argument_list|,
literal|"remove"
argument_list|,
name|G_CALLBACK
argument_list|(
name|windows_menu_display_remove
argument_list|)
argument_list|,
name|manager
argument_list|,
literal|0
argument_list|)
expr_stmt|;
name|g_signal_connect_object
argument_list|(
name|manager
operator|->
name|gimp
operator|->
name|displays
argument_list|,
literal|"reorder"
argument_list|,
name|G_CALLBACK
argument_list|(
name|windows_menu_display_reorder
argument_list|)
argument_list|,
name|manager
argument_list|,
literal|0
argument_list|)
expr_stmt|;
for|for
control|(
name|list
operator|=
name|gimp_get_display_iter
argument_list|(
name|manager
operator|->
name|gimp
argument_list|)
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
name|GimpDisplay
modifier|*
name|display
init|=
name|list
operator|->
name|data
decl_stmt|;
name|windows_menu_display_add
argument_list|(
name|manager
operator|->
name|gimp
operator|->
name|displays
argument_list|,
name|display
argument_list|,
name|manager
argument_list|)
expr_stmt|;
block|}
name|g_signal_connect_object
argument_list|(
name|gimp_dialog_factory_get_singleton
argument_list|()
argument_list|,
literal|"dock-window-added"
argument_list|,
name|G_CALLBACK
argument_list|(
name|windows_menu_dock_window_added
argument_list|)
argument_list|,
name|manager
argument_list|,
literal|0
argument_list|)
expr_stmt|;
name|g_signal_connect_object
argument_list|(
name|gimp_dialog_factory_get_singleton
argument_list|()
argument_list|,
literal|"dock-window-removed"
argument_list|,
name|G_CALLBACK
argument_list|(
name|windows_menu_dock_window_removed
argument_list|)
argument_list|,
name|manager
argument_list|,
literal|0
argument_list|)
expr_stmt|;
for|for
control|(
name|list
operator|=
name|gimp_dialog_factory_get_open_dialogs
argument_list|(
name|gimp_dialog_factory_get_singleton
argument_list|()
argument_list|)
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
name|GimpDockWindow
modifier|*
name|dock_window
init|=
name|list
operator|->
name|data
decl_stmt|;
if|if
condition|(
name|GIMP_IS_DOCK_WINDOW
argument_list|(
name|dock_window
argument_list|)
condition|)
name|windows_menu_dock_window_added
argument_list|(
name|gimp_dialog_factory_get_singleton
argument_list|()
argument_list|,
name|dock_window
argument_list|,
name|manager
argument_list|)
expr_stmt|;
block|}
name|g_signal_connect_object
argument_list|(
name|global_recent_docks
argument_list|,
literal|"add"
argument_list|,
name|G_CALLBACK
argument_list|(
name|windows_menu_recent_add
argument_list|)
argument_list|,
name|manager
argument_list|,
literal|0
argument_list|)
expr_stmt|;
name|g_signal_connect_object
argument_list|(
name|global_recent_docks
argument_list|,
literal|"remove"
argument_list|,
name|G_CALLBACK
argument_list|(
name|windows_menu_recent_remove
argument_list|)
argument_list|,
name|manager
argument_list|,
literal|0
argument_list|)
expr_stmt|;
for|for
control|(
name|list
operator|=
name|g_list_last
argument_list|(
name|GIMP_LIST
argument_list|(
name|global_recent_docks
argument_list|)
operator|->
name|list
argument_list|)
init|;
name|list
condition|;
name|list
operator|=
name|g_list_previous
argument_list|(
name|list
argument_list|)
control|)
block|{
name|GimpSessionInfo
modifier|*
name|info
init|=
name|list
operator|->
name|data
decl_stmt|;
name|windows_menu_recent_add
argument_list|(
name|global_recent_docks
argument_list|,
name|info
argument_list|,
name|manager
argument_list|)
expr_stmt|;
block|}
block|}
end_function

begin_comment
comment|/*  private functions  */
end_comment

begin_function
specifier|static
name|void
DECL|function|windows_menu_display_add (GimpContainer * container,GimpDisplay * display,GimpUIManager * manager)
name|windows_menu_display_add
parameter_list|(
name|GimpContainer
modifier|*
name|container
parameter_list|,
name|GimpDisplay
modifier|*
name|display
parameter_list|,
name|GimpUIManager
modifier|*
name|manager
parameter_list|)
block|{
name|g_signal_connect_object
argument_list|(
name|display
argument_list|,
literal|"notify::image"
argument_list|,
name|G_CALLBACK
argument_list|(
name|windows_menu_image_notify
argument_list|)
argument_list|,
name|manager
argument_list|,
literal|0
argument_list|)
expr_stmt|;
if|if
condition|(
name|gimp_display_get_image
argument_list|(
name|display
argument_list|)
condition|)
name|windows_menu_image_notify
argument_list|(
name|display
argument_list|,
name|NULL
argument_list|,
name|manager
argument_list|)
expr_stmt|;
block|}
end_function

begin_function
specifier|static
name|void
DECL|function|windows_menu_display_remove (GimpContainer * container,GimpDisplay * display,GimpUIManager * manager)
name|windows_menu_display_remove
parameter_list|(
name|GimpContainer
modifier|*
name|container
parameter_list|,
name|GimpDisplay
modifier|*
name|display
parameter_list|,
name|GimpUIManager
modifier|*
name|manager
parameter_list|)
block|{
name|gchar
modifier|*
name|merge_key
init|=
name|g_strdup_printf
argument_list|(
literal|"windows-display-%04d-merge-id"
argument_list|,
name|gimp_display_get_ID
argument_list|(
name|display
argument_list|)
argument_list|)
decl_stmt|;
name|guint
name|merge_id
decl_stmt|;
name|merge_id
operator|=
name|GPOINTER_TO_UINT
argument_list|(
name|g_object_get_data
argument_list|(
name|G_OBJECT
argument_list|(
name|manager
argument_list|)
argument_list|,
name|merge_key
argument_list|)
argument_list|)
expr_stmt|;
if|if
condition|(
name|merge_id
condition|)
name|gtk_ui_manager_remove_ui
argument_list|(
name|GTK_UI_MANAGER
argument_list|(
name|manager
argument_list|)
argument_list|,
name|merge_id
argument_list|)
expr_stmt|;
name|g_object_set_data
argument_list|(
name|G_OBJECT
argument_list|(
name|manager
argument_list|)
argument_list|,
name|merge_key
argument_list|,
name|NULL
argument_list|)
expr_stmt|;
name|g_free
argument_list|(
name|merge_key
argument_list|)
expr_stmt|;
block|}
end_function

begin_function
specifier|static
name|void
DECL|function|windows_menu_display_reorder (GimpContainer * container,GimpDisplay * display,gint new_index,GimpUIManager * manager)
name|windows_menu_display_reorder
parameter_list|(
name|GimpContainer
modifier|*
name|container
parameter_list|,
name|GimpDisplay
modifier|*
name|display
parameter_list|,
name|gint
name|new_index
parameter_list|,
name|GimpUIManager
modifier|*
name|manager
parameter_list|)
block|{
name|gint
name|n_display
init|=
name|gimp_container_get_n_children
argument_list|(
name|container
argument_list|)
decl_stmt|;
name|gint
name|i
decl_stmt|;
for|for
control|(
name|i
operator|=
name|new_index
init|;
name|i
operator|<
name|n_display
condition|;
name|i
operator|++
control|)
block|{
name|GimpObject
modifier|*
name|d
init|=
name|gimp_container_get_child_by_index
argument_list|(
name|container
argument_list|,
name|i
argument_list|)
decl_stmt|;
name|windows_menu_display_remove
argument_list|(
name|container
argument_list|,
name|GIMP_DISPLAY
argument_list|(
name|d
argument_list|)
argument_list|,
name|manager
argument_list|)
expr_stmt|;
block|}
comment|/* If I don't ensure the menu items are effectively removed, adding      * the same ones may simply cancel the effect of the removal, hence      * losing the menu reordering. */
name|gtk_ui_manager_ensure_update
argument_list|(
name|manager
argument_list|)
expr_stmt|;
for|for
control|(
name|i
operator|=
name|new_index
init|;
name|i
operator|<
name|n_display
condition|;
name|i
operator|++
control|)
block|{
name|GimpObject
modifier|*
name|d
init|=
name|gimp_container_get_child_by_index
argument_list|(
name|container
argument_list|,
name|i
argument_list|)
decl_stmt|;
name|windows_menu_display_add
argument_list|(
name|container
argument_list|,
name|GIMP_DISPLAY
argument_list|(
name|d
argument_list|)
argument_list|,
name|manager
argument_list|)
expr_stmt|;
block|}
block|}
end_function

begin_function
specifier|static
name|void
DECL|function|windows_menu_image_notify (GimpDisplay * display,const GParamSpec * unused,GimpUIManager * manager)
name|windows_menu_image_notify
parameter_list|(
name|GimpDisplay
modifier|*
name|display
parameter_list|,
specifier|const
name|GParamSpec
modifier|*
name|unused
parameter_list|,
name|GimpUIManager
modifier|*
name|manager
parameter_list|)
block|{
if|if
condition|(
name|gimp_display_get_image
argument_list|(
name|display
argument_list|)
condition|)
block|{
name|gchar
modifier|*
name|merge_key
init|=
name|g_strdup_printf
argument_list|(
literal|"windows-display-%04d-merge-id"
argument_list|,
name|gimp_display_get_ID
argument_list|(
name|display
argument_list|)
argument_list|)
decl_stmt|;
name|guint
name|merge_id
decl_stmt|;
name|merge_id
operator|=
name|GPOINTER_TO_UINT
argument_list|(
name|g_object_get_data
argument_list|(
name|G_OBJECT
argument_list|(
name|manager
argument_list|)
argument_list|,
name|merge_key
argument_list|)
argument_list|)
expr_stmt|;
if|if
condition|(
operator|!
name|merge_id
condition|)
block|{
name|GtkWidget
modifier|*
name|widget
decl_stmt|;
specifier|const
name|gchar
modifier|*
name|ui_path
decl_stmt|;
name|gchar
modifier|*
name|action_name
decl_stmt|;
name|gchar
modifier|*
name|action_path
decl_stmt|;
name|gchar
modifier|*
name|full_path
decl_stmt|;
name|ui_path
operator|=
name|g_object_get_data
argument_list|(
name|G_OBJECT
argument_list|(
name|manager
argument_list|)
argument_list|,
literal|"image-menu-ui-path"
argument_list|)
expr_stmt|;
name|action_name
operator|=
name|gimp_display_get_action_name
argument_list|(
name|display
argument_list|)
expr_stmt|;
name|action_path
operator|=
name|g_strdup_printf
argument_list|(
literal|"%s/Windows/Images"
argument_list|,
name|ui_path
argument_list|)
expr_stmt|;
name|merge_id
operator|=
name|gtk_ui_manager_new_merge_id
argument_list|(
name|GTK_UI_MANAGER
argument_list|(
name|manager
argument_list|)
argument_list|)
expr_stmt|;
name|g_object_set_data
argument_list|(
name|G_OBJECT
argument_list|(
name|manager
argument_list|)
argument_list|,
name|merge_key
argument_list|,
name|GUINT_TO_POINTER
argument_list|(
name|merge_id
argument_list|)
argument_list|)
expr_stmt|;
name|gtk_ui_manager_add_ui
argument_list|(
name|GTK_UI_MANAGER
argument_list|(
name|manager
argument_list|)
argument_list|,
name|merge_id
argument_list|,
name|action_path
argument_list|,
name|action_name
argument_list|,
name|action_name
argument_list|,
name|GTK_UI_MANAGER_MENUITEM
argument_list|,
name|FALSE
argument_list|)
expr_stmt|;
name|full_path
operator|=
name|g_strconcat
argument_list|(
name|action_path
argument_list|,
literal|"/"
argument_list|,
name|action_name
argument_list|,
name|NULL
argument_list|)
expr_stmt|;
name|widget
operator|=
name|gtk_ui_manager_get_widget
argument_list|(
name|GTK_UI_MANAGER
argument_list|(
name|manager
argument_list|)
argument_list|,
name|full_path
argument_list|)
expr_stmt|;
if|if
condition|(
name|widget
condition|)
block|{
name|GtkAction
modifier|*
name|action
decl_stmt|;
name|action
operator|=
name|gimp_ui_manager_find_action
argument_list|(
name|manager
argument_list|,
literal|"windows"
argument_list|,
name|action_name
argument_list|)
expr_stmt|;
name|g_signal_connect_object
argument_list|(
name|widget
argument_list|,
literal|"query-tooltip"
argument_list|,
name|G_CALLBACK
argument_list|(
name|windows_menu_display_query_tooltip
argument_list|)
argument_list|,
name|action
argument_list|,
literal|0
argument_list|)
expr_stmt|;
block|}
name|g_free
argument_list|(
name|action_name
argument_list|)
expr_stmt|;
name|g_free
argument_list|(
name|action_path
argument_list|)
expr_stmt|;
name|g_free
argument_list|(
name|full_path
argument_list|)
expr_stmt|;
block|}
name|g_free
argument_list|(
name|merge_key
argument_list|)
expr_stmt|;
block|}
else|else
block|{
name|windows_menu_display_remove
argument_list|(
name|manager
operator|->
name|gimp
operator|->
name|displays
argument_list|,
name|display
argument_list|,
name|manager
argument_list|)
expr_stmt|;
block|}
block|}
end_function

begin_function
specifier|static
name|void
DECL|function|windows_menu_dock_window_added (GimpDialogFactory * factory,GimpDockWindow * dock_window,GimpUIManager * manager)
name|windows_menu_dock_window_added
parameter_list|(
name|GimpDialogFactory
modifier|*
name|factory
parameter_list|,
name|GimpDockWindow
modifier|*
name|dock_window
parameter_list|,
name|GimpUIManager
modifier|*
name|manager
parameter_list|)
block|{
specifier|const
name|gchar
modifier|*
name|ui_path
decl_stmt|;
name|gchar
modifier|*
name|action_name
decl_stmt|;
name|gchar
modifier|*
name|action_path
decl_stmt|;
name|gchar
modifier|*
name|merge_key
decl_stmt|;
name|guint
name|merge_id
decl_stmt|;
name|ui_path
operator|=
name|g_object_get_data
argument_list|(
name|G_OBJECT
argument_list|(
name|manager
argument_list|)
argument_list|,
literal|"image-menu-ui-path"
argument_list|)
expr_stmt|;
name|action_name
operator|=
name|windows_actions_dock_window_to_action_name
argument_list|(
name|dock_window
argument_list|)
expr_stmt|;
name|action_path
operator|=
name|g_strdup_printf
argument_list|(
literal|"%s/Windows/Docks"
argument_list|,
name|ui_path
argument_list|)
expr_stmt|;
name|merge_key
operator|=
name|windows_menu_dock_window_to_merge_id
argument_list|(
name|dock_window
argument_list|)
expr_stmt|;
name|merge_id
operator|=
name|gtk_ui_manager_new_merge_id
argument_list|(
name|GTK_UI_MANAGER
argument_list|(
name|manager
argument_list|)
argument_list|)
expr_stmt|;
name|g_object_set_data
argument_list|(
name|G_OBJECT
argument_list|(
name|manager
argument_list|)
argument_list|,
name|merge_key
argument_list|,
name|GUINT_TO_POINTER
argument_list|(
name|merge_id
argument_list|)
argument_list|)
expr_stmt|;
name|gtk_ui_manager_add_ui
argument_list|(
name|GTK_UI_MANAGER
argument_list|(
name|manager
argument_list|)
argument_list|,
name|merge_id
argument_list|,
name|action_path
argument_list|,
name|action_name
argument_list|,
name|action_name
argument_list|,
name|GTK_UI_MANAGER_MENUITEM
argument_list|,
name|FALSE
argument_list|)
expr_stmt|;
name|g_free
argument_list|(
name|merge_key
argument_list|)
expr_stmt|;
name|g_free
argument_list|(
name|action_path
argument_list|)
expr_stmt|;
name|g_free
argument_list|(
name|action_name
argument_list|)
expr_stmt|;
block|}
end_function

begin_function
specifier|static
name|void
DECL|function|windows_menu_dock_window_removed (GimpDialogFactory * factory,GimpDockWindow * dock_window,GimpUIManager * manager)
name|windows_menu_dock_window_removed
parameter_list|(
name|GimpDialogFactory
modifier|*
name|factory
parameter_list|,
name|GimpDockWindow
modifier|*
name|dock_window
parameter_list|,
name|GimpUIManager
modifier|*
name|manager
parameter_list|)
block|{
name|gchar
modifier|*
name|merge_key
init|=
name|windows_menu_dock_window_to_merge_id
argument_list|(
name|dock_window
argument_list|)
decl_stmt|;
name|guint
name|merge_id
init|=
name|GPOINTER_TO_UINT
argument_list|(
name|g_object_get_data
argument_list|(
name|G_OBJECT
argument_list|(
name|manager
argument_list|)
argument_list|,
name|merge_key
argument_list|)
argument_list|)
decl_stmt|;
if|if
condition|(
name|merge_id
condition|)
name|gtk_ui_manager_remove_ui
argument_list|(
name|GTK_UI_MANAGER
argument_list|(
name|manager
argument_list|)
argument_list|,
name|merge_id
argument_list|)
expr_stmt|;
name|g_object_set_data
argument_list|(
name|G_OBJECT
argument_list|(
name|manager
argument_list|)
argument_list|,
name|merge_key
argument_list|,
name|NULL
argument_list|)
expr_stmt|;
name|g_free
argument_list|(
name|merge_key
argument_list|)
expr_stmt|;
block|}
end_function

begin_function
specifier|static
name|gchar
modifier|*
DECL|function|windows_menu_dock_window_to_merge_id (GimpDockWindow * dock_window)
name|windows_menu_dock_window_to_merge_id
parameter_list|(
name|GimpDockWindow
modifier|*
name|dock_window
parameter_list|)
block|{
return|return
name|g_strdup_printf
argument_list|(
literal|"windows-dock-%04d-merge-id"
argument_list|,
name|gimp_dock_window_get_id
argument_list|(
name|dock_window
argument_list|)
argument_list|)
return|;
block|}
end_function

begin_function
specifier|static
name|void
DECL|function|windows_menu_recent_add (GimpContainer * container,GimpSessionInfo * info,GimpUIManager * manager)
name|windows_menu_recent_add
parameter_list|(
name|GimpContainer
modifier|*
name|container
parameter_list|,
name|GimpSessionInfo
modifier|*
name|info
parameter_list|,
name|GimpUIManager
modifier|*
name|manager
parameter_list|)
block|{
specifier|const
name|gchar
modifier|*
name|ui_path
decl_stmt|;
name|gchar
modifier|*
name|action_name
decl_stmt|;
name|gchar
modifier|*
name|action_path
decl_stmt|;
name|gint
name|info_id
decl_stmt|;
name|gchar
modifier|*
name|merge_key
decl_stmt|;
name|guint
name|merge_id
decl_stmt|;
name|ui_path
operator|=
name|g_object_get_data
argument_list|(
name|G_OBJECT
argument_list|(
name|manager
argument_list|)
argument_list|,
literal|"image-menu-ui-path"
argument_list|)
expr_stmt|;
name|info_id
operator|=
name|GPOINTER_TO_INT
argument_list|(
name|g_object_get_data
argument_list|(
name|G_OBJECT
argument_list|(
name|info
argument_list|)
argument_list|,
literal|"recent-action-id"
argument_list|)
argument_list|)
expr_stmt|;
name|action_name
operator|=
name|g_strdup_printf
argument_list|(
literal|"windows-recent-%04d"
argument_list|,
name|info_id
argument_list|)
expr_stmt|;
name|action_path
operator|=
name|g_strdup_printf
argument_list|(
literal|"%s/Windows/Recently Closed Docks"
argument_list|,
name|ui_path
argument_list|)
expr_stmt|;
name|merge_key
operator|=
name|g_strdup_printf
argument_list|(
literal|"windows-recent-%04d-merge-id"
argument_list|,
name|info_id
argument_list|)
expr_stmt|;
name|merge_id
operator|=
name|gtk_ui_manager_new_merge_id
argument_list|(
name|GTK_UI_MANAGER
argument_list|(
name|manager
argument_list|)
argument_list|)
expr_stmt|;
name|g_object_set_data
argument_list|(
name|G_OBJECT
argument_list|(
name|manager
argument_list|)
argument_list|,
name|merge_key
argument_list|,
name|GUINT_TO_POINTER
argument_list|(
name|merge_id
argument_list|)
argument_list|)
expr_stmt|;
name|gtk_ui_manager_add_ui
argument_list|(
name|GTK_UI_MANAGER
argument_list|(
name|manager
argument_list|)
argument_list|,
name|merge_id
argument_list|,
name|action_path
argument_list|,
name|action_name
argument_list|,
name|action_name
argument_list|,
name|GTK_UI_MANAGER_MENUITEM
argument_list|,
name|TRUE
argument_list|)
expr_stmt|;
name|g_free
argument_list|(
name|merge_key
argument_list|)
expr_stmt|;
name|g_free
argument_list|(
name|action_path
argument_list|)
expr_stmt|;
name|g_free
argument_list|(
name|action_name
argument_list|)
expr_stmt|;
block|}
end_function

begin_function
specifier|static
name|void
DECL|function|windows_menu_recent_remove (GimpContainer * container,GimpSessionInfo * info,GimpUIManager * manager)
name|windows_menu_recent_remove
parameter_list|(
name|GimpContainer
modifier|*
name|container
parameter_list|,
name|GimpSessionInfo
modifier|*
name|info
parameter_list|,
name|GimpUIManager
modifier|*
name|manager
parameter_list|)
block|{
name|gint
name|info_id
decl_stmt|;
name|gchar
modifier|*
name|merge_key
decl_stmt|;
name|guint
name|merge_id
decl_stmt|;
name|info_id
operator|=
name|GPOINTER_TO_INT
argument_list|(
name|g_object_get_data
argument_list|(
name|G_OBJECT
argument_list|(
name|info
argument_list|)
argument_list|,
literal|"recent-action-id"
argument_list|)
argument_list|)
expr_stmt|;
name|merge_key
operator|=
name|g_strdup_printf
argument_list|(
literal|"windows-recent-%04d-merge-id"
argument_list|,
name|info_id
argument_list|)
expr_stmt|;
name|merge_id
operator|=
name|GPOINTER_TO_UINT
argument_list|(
name|g_object_get_data
argument_list|(
name|G_OBJECT
argument_list|(
name|manager
argument_list|)
argument_list|,
name|merge_key
argument_list|)
argument_list|)
expr_stmt|;
if|if
condition|(
name|merge_id
condition|)
name|gtk_ui_manager_remove_ui
argument_list|(
name|GTK_UI_MANAGER
argument_list|(
name|manager
argument_list|)
argument_list|,
name|merge_id
argument_list|)
expr_stmt|;
name|g_object_set_data
argument_list|(
name|G_OBJECT
argument_list|(
name|manager
argument_list|)
argument_list|,
name|merge_key
argument_list|,
name|NULL
argument_list|)
expr_stmt|;
name|g_free
argument_list|(
name|merge_key
argument_list|)
expr_stmt|;
block|}
end_function

begin_function
specifier|static
name|gboolean
DECL|function|windows_menu_display_query_tooltip (GtkWidget * widget,gint x,gint y,gboolean keyboard_mode,GtkTooltip * tooltip,GimpAction * action)
name|windows_menu_display_query_tooltip
parameter_list|(
name|GtkWidget
modifier|*
name|widget
parameter_list|,
name|gint
name|x
parameter_list|,
name|gint
name|y
parameter_list|,
name|gboolean
name|keyboard_mode
parameter_list|,
name|GtkTooltip
modifier|*
name|tooltip
parameter_list|,
name|GimpAction
modifier|*
name|action
parameter_list|)
block|{
name|GimpImage
modifier|*
name|image
init|=
name|GIMP_IMAGE
argument_list|(
name|action
operator|->
name|viewable
argument_list|)
decl_stmt|;
name|gchar
modifier|*
name|text
decl_stmt|;
name|gdouble
name|xres
decl_stmt|;
name|gdouble
name|yres
decl_stmt|;
name|gint
name|width
decl_stmt|;
name|gint
name|height
decl_stmt|;
name|text
operator|=
name|gtk_widget_get_tooltip_text
argument_list|(
name|widget
argument_list|)
expr_stmt|;
name|gtk_tooltip_set_text
argument_list|(
name|tooltip
argument_list|,
name|text
argument_list|)
expr_stmt|;
name|g_free
argument_list|(
name|text
argument_list|)
expr_stmt|;
name|gimp_image_get_resolution
argument_list|(
name|image
argument_list|,
operator|&
name|xres
argument_list|,
operator|&
name|yres
argument_list|)
expr_stmt|;
name|gimp_viewable_calc_preview_size
argument_list|(
name|gimp_image_get_width
argument_list|(
name|image
argument_list|)
argument_list|,
name|gimp_image_get_height
argument_list|(
name|image
argument_list|)
argument_list|,
name|GIMP_VIEW_SIZE_HUGE
argument_list|,
name|GIMP_VIEW_SIZE_HUGE
argument_list|,
name|FALSE
argument_list|,
name|xres
argument_list|,
name|yres
argument_list|,
operator|&
name|width
argument_list|,
operator|&
name|height
argument_list|,
name|NULL
argument_list|)
expr_stmt|;
name|gtk_tooltip_set_icon
argument_list|(
name|tooltip
argument_list|,
name|gimp_viewable_get_pixbuf
argument_list|(
name|action
operator|->
name|viewable
argument_list|,
name|action
operator|->
name|context
argument_list|,
name|width
argument_list|,
name|height
argument_list|)
argument_list|)
expr_stmt|;
return|return
name|TRUE
return|;
block|}
end_function

end_unit

