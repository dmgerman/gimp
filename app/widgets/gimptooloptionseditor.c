begin_unit|revision:0.9.5;language:C;cregit-version:0.0.1
begin_comment
comment|/* The GIMP -- an image manipulation program  * Copyright (C) 1995 Spencer Kimball and Peter Mattis  *  * gimptooloptionseditor.c  * Copyright (C) 2003 Michael Natterer<mitch@gimp.org>  *  * This program is free software; you can redistribute it and/or modify  * it under the terms of the GNU General Public License as published by  * the Free Software Foundation; either version 2 of the License, or  * (at your option) any later version.  *  * This program is distributed in the hope that it will be useful,  * but WITHOUT ANY WARRANTY; without even the implied warranty of  * MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the  * GNU General Public License for more details.  *  * You should have received a copy of the GNU General Public License  * along with this program; if not, write to the Free Software  * Foundation, Inc., 59 Temple Place - Suite 330, Boston, MA 02111-1307, USA.  */
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
file|"widgets-types.h"
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
file|"core/gimplist.h"
end_include

begin_include
include|#
directive|include
file|"core/gimptoolinfo.h"
end_include

begin_include
include|#
directive|include
file|"core/gimptooloptions.h"
end_include

begin_include
include|#
directive|include
file|"gimpdnd.h"
end_include

begin_include
include|#
directive|include
file|"gimpdocked.h"
end_include

begin_include
include|#
directive|include
file|"gimphelp-ids.h"
end_include

begin_include
include|#
directive|include
file|"gimpmenufactory.h"
end_include

begin_include
include|#
directive|include
file|"gimpview.h"
end_include

begin_include
include|#
directive|include
file|"gimpviewrenderer.h"
end_include

begin_include
include|#
directive|include
file|"gimppropwidgets.h"
end_include

begin_include
include|#
directive|include
file|"gimptooloptionseditor.h"
end_include

begin_include
include|#
directive|include
file|"gimpuimanager.h"
end_include

begin_include
include|#
directive|include
file|"gimpwidgets-utils.h"
end_include

begin_include
include|#
directive|include
file|"gimp-intl.h"
end_include

begin_function_decl
specifier|static
name|void
name|gimp_tool_options_editor_class_init
parameter_list|(
name|GimpToolOptionsEditorClass
modifier|*
name|klass
parameter_list|)
function_decl|;
end_function_decl

begin_function_decl
specifier|static
name|void
name|gimp_tool_options_editor_init
parameter_list|(
name|GimpToolOptionsEditor
modifier|*
name|editor
parameter_list|)
function_decl|;
end_function_decl

begin_function_decl
specifier|static
name|void
name|gimp_tool_options_editor_docked_iface_init
parameter_list|(
name|GimpDockedInterface
modifier|*
name|docked_iface
parameter_list|)
function_decl|;
end_function_decl

begin_function_decl
specifier|static
name|GObject
modifier|*
name|gimp_tool_options_editor_constructor
parameter_list|(
name|GType
name|type
parameter_list|,
name|guint
name|n_params
parameter_list|,
name|GObjectConstructParam
modifier|*
name|params
parameter_list|)
function_decl|;
end_function_decl

begin_function_decl
specifier|static
name|void
name|gimp_tool_options_editor_destroy
parameter_list|(
name|GtkObject
modifier|*
name|object
parameter_list|)
function_decl|;
end_function_decl

begin_function_decl
specifier|static
name|GtkWidget
modifier|*
name|gimp_tool_options_editor_get_preview
parameter_list|(
name|GimpDocked
modifier|*
name|docked
parameter_list|,
name|GimpContext
modifier|*
name|context
parameter_list|,
name|GtkIconSize
name|size
parameter_list|)
function_decl|;
end_function_decl

begin_function_decl
specifier|static
name|gchar
modifier|*
name|gimp_tool_options_editor_get_title
parameter_list|(
name|GimpDocked
modifier|*
name|docked
parameter_list|)
function_decl|;
end_function_decl

begin_function_decl
specifier|static
name|void
name|gimp_tool_options_editor_save_clicked
parameter_list|(
name|GtkWidget
modifier|*
name|widget
parameter_list|,
name|GimpToolOptionsEditor
modifier|*
name|editor
parameter_list|)
function_decl|;
end_function_decl

begin_function_decl
specifier|static
name|void
name|gimp_tool_options_editor_restore_clicked
parameter_list|(
name|GtkWidget
modifier|*
name|widget
parameter_list|,
name|GimpToolOptionsEditor
modifier|*
name|editor
parameter_list|)
function_decl|;
end_function_decl

begin_function_decl
specifier|static
name|void
name|gimp_tool_options_editor_delete_clicked
parameter_list|(
name|GtkWidget
modifier|*
name|widget
parameter_list|,
name|GimpToolOptionsEditor
modifier|*
name|editor
parameter_list|)
function_decl|;
end_function_decl

begin_function_decl
specifier|static
name|void
name|gimp_tool_options_editor_drop_tool
parameter_list|(
name|GtkWidget
modifier|*
name|widget
parameter_list|,
name|GimpViewable
modifier|*
name|viewable
parameter_list|,
name|gpointer
name|data
parameter_list|)
function_decl|;
end_function_decl

begin_function_decl
specifier|static
name|void
name|gimp_tool_options_editor_tool_changed
parameter_list|(
name|GimpContext
modifier|*
name|context
parameter_list|,
name|GimpToolInfo
modifier|*
name|tool_info
parameter_list|,
name|GimpToolOptionsEditor
modifier|*
name|editor
parameter_list|)
function_decl|;
end_function_decl

begin_function_decl
specifier|static
name|void
name|gimp_tool_options_editor_presets_changed
parameter_list|(
name|GimpContainer
modifier|*
name|container
parameter_list|,
name|GimpToolOptions
modifier|*
name|options
parameter_list|,
name|GimpToolOptionsEditor
modifier|*
name|editor
parameter_list|)
function_decl|;
end_function_decl

begin_decl_stmt
DECL|variable|parent_class
specifier|static
name|GimpEditorClass
modifier|*
name|parent_class
init|=
name|NULL
decl_stmt|;
end_decl_stmt

begin_function
name|GType
DECL|function|gimp_tool_options_editor_get_type (void)
name|gimp_tool_options_editor_get_type
parameter_list|(
name|void
parameter_list|)
block|{
specifier|static
name|GType
name|type
init|=
literal|0
decl_stmt|;
if|if
condition|(
operator|!
name|type
condition|)
block|{
specifier|static
specifier|const
name|GTypeInfo
name|editor_info
init|=
block|{
sizeof|sizeof
argument_list|(
name|GimpToolOptionsEditorClass
argument_list|)
block|,
name|NULL
block|,
comment|/* base_init */
name|NULL
block|,
comment|/* base_finalize */
operator|(
name|GClassInitFunc
operator|)
name|gimp_tool_options_editor_class_init
block|,
name|NULL
block|,
comment|/* class_finalize */
name|NULL
block|,
comment|/* class_tool */
sizeof|sizeof
argument_list|(
name|GimpToolOptionsEditor
argument_list|)
block|,
literal|0
block|,
comment|/* n_preallocs */
operator|(
name|GInstanceInitFunc
operator|)
name|gimp_tool_options_editor_init
block|,       }
decl_stmt|;
specifier|static
specifier|const
name|GInterfaceInfo
name|docked_iface_info
init|=
block|{
operator|(
name|GInterfaceInitFunc
operator|)
name|gimp_tool_options_editor_docked_iface_init
block|,
name|NULL
block|,
comment|/* iface_finalize */
name|NULL
comment|/* iface_data     */
block|}
decl_stmt|;
name|type
operator|=
name|g_type_register_static
argument_list|(
name|GIMP_TYPE_EDITOR
argument_list|,
literal|"GimpToolOptionsEditor"
argument_list|,
operator|&
name|editor_info
argument_list|,
literal|0
argument_list|)
expr_stmt|;
name|g_type_add_interface_static
argument_list|(
name|type
argument_list|,
name|GIMP_TYPE_DOCKED
argument_list|,
operator|&
name|docked_iface_info
argument_list|)
expr_stmt|;
block|}
return|return
name|type
return|;
block|}
end_function

begin_function
specifier|static
name|void
DECL|function|gimp_tool_options_editor_class_init (GimpToolOptionsEditorClass * klass)
name|gimp_tool_options_editor_class_init
parameter_list|(
name|GimpToolOptionsEditorClass
modifier|*
name|klass
parameter_list|)
block|{
name|GObjectClass
modifier|*
name|object_class
init|=
name|G_OBJECT_CLASS
argument_list|(
name|klass
argument_list|)
decl_stmt|;
name|GtkObjectClass
modifier|*
name|gtk_object_class
init|=
name|GTK_OBJECT_CLASS
argument_list|(
name|klass
argument_list|)
decl_stmt|;
name|parent_class
operator|=
name|g_type_class_peek_parent
argument_list|(
name|klass
argument_list|)
expr_stmt|;
name|object_class
operator|->
name|constructor
operator|=
name|gimp_tool_options_editor_constructor
expr_stmt|;
name|gtk_object_class
operator|->
name|destroy
operator|=
name|gimp_tool_options_editor_destroy
expr_stmt|;
block|}
end_function

begin_function
specifier|static
name|void
DECL|function|gimp_tool_options_editor_init (GimpToolOptionsEditor * editor)
name|gimp_tool_options_editor_init
parameter_list|(
name|GimpToolOptionsEditor
modifier|*
name|editor
parameter_list|)
block|{
name|GtkWidget
modifier|*
name|sw
decl_stmt|;
name|gtk_widget_set_size_request
argument_list|(
name|GTK_WIDGET
argument_list|(
name|editor
argument_list|)
argument_list|,
operator|-
literal|1
argument_list|,
literal|200
argument_list|)
expr_stmt|;
name|gimp_dnd_viewable_dest_add
argument_list|(
name|GTK_WIDGET
argument_list|(
name|editor
argument_list|)
argument_list|,
name|GIMP_TYPE_TOOL_INFO
argument_list|,
name|gimp_tool_options_editor_drop_tool
argument_list|,
name|editor
argument_list|)
expr_stmt|;
name|editor
operator|->
name|scrolled_window
operator|=
name|sw
operator|=
name|gtk_scrolled_window_new
argument_list|(
name|NULL
argument_list|,
name|NULL
argument_list|)
expr_stmt|;
name|gtk_scrolled_window_set_policy
argument_list|(
name|GTK_SCROLLED_WINDOW
argument_list|(
name|sw
argument_list|)
argument_list|,
name|GTK_POLICY_AUTOMATIC
argument_list|,
name|GTK_POLICY_AUTOMATIC
argument_list|)
expr_stmt|;
name|gtk_container_add
argument_list|(
name|GTK_CONTAINER
argument_list|(
name|editor
argument_list|)
argument_list|,
name|sw
argument_list|)
expr_stmt|;
name|gtk_widget_show
argument_list|(
name|sw
argument_list|)
expr_stmt|;
comment|/*  The vbox containing the tool options  */
name|editor
operator|->
name|options_vbox
operator|=
name|gtk_vbox_new
argument_list|(
name|FALSE
argument_list|,
literal|0
argument_list|)
expr_stmt|;
name|gtk_container_set_border_width
argument_list|(
name|GTK_CONTAINER
argument_list|(
name|editor
operator|->
name|options_vbox
argument_list|)
argument_list|,
literal|2
argument_list|)
expr_stmt|;
name|gtk_scrolled_window_add_with_viewport
argument_list|(
name|GTK_SCROLLED_WINDOW
argument_list|(
name|sw
argument_list|)
argument_list|,
name|editor
operator|->
name|options_vbox
argument_list|)
expr_stmt|;
name|gtk_widget_show
argument_list|(
name|editor
operator|->
name|options_vbox
argument_list|)
expr_stmt|;
block|}
end_function

begin_function
specifier|static
name|void
DECL|function|gimp_tool_options_editor_docked_iface_init (GimpDockedInterface * docked_iface)
name|gimp_tool_options_editor_docked_iface_init
parameter_list|(
name|GimpDockedInterface
modifier|*
name|docked_iface
parameter_list|)
block|{
name|docked_iface
operator|->
name|get_preview
operator|=
name|gimp_tool_options_editor_get_preview
expr_stmt|;
name|docked_iface
operator|->
name|get_title
operator|=
name|gimp_tool_options_editor_get_title
expr_stmt|;
block|}
end_function

begin_function
specifier|static
name|GObject
modifier|*
DECL|function|gimp_tool_options_editor_constructor (GType type,guint n_params,GObjectConstructParam * params)
name|gimp_tool_options_editor_constructor
parameter_list|(
name|GType
name|type
parameter_list|,
name|guint
name|n_params
parameter_list|,
name|GObjectConstructParam
modifier|*
name|params
parameter_list|)
block|{
name|GObject
modifier|*
name|object
decl_stmt|;
name|GimpToolOptionsEditor
modifier|*
name|editor
decl_stmt|;
name|object
operator|=
name|G_OBJECT_CLASS
argument_list|(
name|parent_class
argument_list|)
operator|->
name|constructor
argument_list|(
name|type
argument_list|,
name|n_params
argument_list|,
name|params
argument_list|)
expr_stmt|;
name|editor
operator|=
name|GIMP_TOOL_OPTIONS_EDITOR
argument_list|(
name|object
argument_list|)
expr_stmt|;
name|editor
operator|->
name|save_button
operator|=
name|gimp_editor_add_button
argument_list|(
name|GIMP_EDITOR
argument_list|(
name|editor
argument_list|)
argument_list|,
name|GTK_STOCK_SAVE
argument_list|,
name|_
argument_list|(
literal|"Save options to..."
argument_list|)
argument_list|,
name|GIMP_HELP_TOOL_OPTIONS_SAVE
argument_list|,
name|G_CALLBACK
argument_list|(
name|gimp_tool_options_editor_save_clicked
argument_list|)
argument_list|,
name|NULL
argument_list|,
name|editor
argument_list|)
expr_stmt|;
name|editor
operator|->
name|restore_button
operator|=
name|gimp_editor_add_button
argument_list|(
name|GIMP_EDITOR
argument_list|(
name|editor
argument_list|)
argument_list|,
name|GTK_STOCK_REVERT_TO_SAVED
argument_list|,
name|_
argument_list|(
literal|"Restore options from..."
argument_list|)
argument_list|,
name|GIMP_HELP_TOOL_OPTIONS_RESTORE
argument_list|,
name|G_CALLBACK
argument_list|(
name|gimp_tool_options_editor_restore_clicked
argument_list|)
argument_list|,
name|NULL
argument_list|,
name|editor
argument_list|)
expr_stmt|;
name|editor
operator|->
name|delete_button
operator|=
name|gimp_editor_add_button
argument_list|(
name|GIMP_EDITOR
argument_list|(
name|editor
argument_list|)
argument_list|,
name|GTK_STOCK_DELETE
argument_list|,
name|_
argument_list|(
literal|"Delete saved options..."
argument_list|)
argument_list|,
name|GIMP_HELP_TOOL_OPTIONS_DELETE
argument_list|,
name|G_CALLBACK
argument_list|(
name|gimp_tool_options_editor_delete_clicked
argument_list|)
argument_list|,
name|NULL
argument_list|,
name|editor
argument_list|)
expr_stmt|;
name|editor
operator|->
name|reset_button
operator|=
name|gimp_editor_add_action_button
argument_list|(
name|GIMP_EDITOR
argument_list|(
name|editor
argument_list|)
argument_list|,
literal|"tool-options"
argument_list|,
literal|"tool-options-reset"
argument_list|,
literal|"tool-options-reset-all"
argument_list|,
name|GDK_SHIFT_MASK
argument_list|,
name|NULL
argument_list|)
expr_stmt|;
return|return
name|object
return|;
block|}
end_function

begin_function
specifier|static
name|void
DECL|function|gimp_tool_options_editor_destroy (GtkObject * object)
name|gimp_tool_options_editor_destroy
parameter_list|(
name|GtkObject
modifier|*
name|object
parameter_list|)
block|{
name|GimpToolOptionsEditor
modifier|*
name|editor
init|=
name|GIMP_TOOL_OPTIONS_EDITOR
argument_list|(
name|object
argument_list|)
decl_stmt|;
if|if
condition|(
name|editor
operator|->
name|options_vbox
condition|)
block|{
name|GList
modifier|*
name|options
decl_stmt|;
name|GList
modifier|*
name|list
decl_stmt|;
name|options
operator|=
name|gtk_container_get_children
argument_list|(
name|GTK_CONTAINER
argument_list|(
name|editor
operator|->
name|options_vbox
argument_list|)
argument_list|)
expr_stmt|;
for|for
control|(
name|list
operator|=
name|options
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
name|g_object_ref
argument_list|(
name|list
operator|->
name|data
argument_list|)
expr_stmt|;
name|gtk_container_remove
argument_list|(
name|GTK_CONTAINER
argument_list|(
name|editor
operator|->
name|options_vbox
argument_list|)
argument_list|,
name|GTK_WIDGET
argument_list|(
name|list
operator|->
name|data
argument_list|)
argument_list|)
expr_stmt|;
block|}
name|g_list_free
argument_list|(
name|options
argument_list|)
expr_stmt|;
name|editor
operator|->
name|options_vbox
operator|=
name|NULL
expr_stmt|;
block|}
name|GTK_OBJECT_CLASS
argument_list|(
name|parent_class
argument_list|)
operator|->
name|destroy
argument_list|(
name|object
argument_list|)
expr_stmt|;
block|}
end_function

begin_function
specifier|static
name|GtkWidget
modifier|*
DECL|function|gimp_tool_options_editor_get_preview (GimpDocked * docked,GimpContext * context,GtkIconSize size)
name|gimp_tool_options_editor_get_preview
parameter_list|(
name|GimpDocked
modifier|*
name|docked
parameter_list|,
name|GimpContext
modifier|*
name|context
parameter_list|,
name|GtkIconSize
name|size
parameter_list|)
block|{
name|GdkScreen
modifier|*
name|screen
decl_stmt|;
name|GtkWidget
modifier|*
name|view
decl_stmt|;
name|gint
name|width
decl_stmt|;
name|gint
name|height
decl_stmt|;
name|screen
operator|=
name|gtk_widget_get_screen
argument_list|(
name|GTK_WIDGET
argument_list|(
name|docked
argument_list|)
argument_list|)
expr_stmt|;
name|gtk_icon_size_lookup_for_settings
argument_list|(
name|gtk_settings_get_for_screen
argument_list|(
name|screen
argument_list|)
argument_list|,
name|size
argument_list|,
operator|&
name|width
argument_list|,
operator|&
name|height
argument_list|)
expr_stmt|;
name|view
operator|=
name|gimp_prop_preview_new
argument_list|(
name|G_OBJECT
argument_list|(
name|context
argument_list|)
argument_list|,
literal|"tool"
argument_list|,
name|height
argument_list|)
expr_stmt|;
name|GIMP_VIEW
argument_list|(
name|view
argument_list|)
operator|->
name|renderer
operator|->
name|size
operator|=
operator|-
literal|1
expr_stmt|;
name|gimp_view_renderer_set_size_full
argument_list|(
name|GIMP_VIEW
argument_list|(
name|view
argument_list|)
operator|->
name|renderer
argument_list|,
name|width
argument_list|,
name|height
argument_list|,
literal|0
argument_list|)
expr_stmt|;
return|return
name|view
return|;
block|}
end_function

begin_function
specifier|static
name|gchar
modifier|*
DECL|function|gimp_tool_options_editor_get_title (GimpDocked * docked)
name|gimp_tool_options_editor_get_title
parameter_list|(
name|GimpDocked
modifier|*
name|docked
parameter_list|)
block|{
name|GimpToolOptionsEditor
modifier|*
name|editor
init|=
name|GIMP_TOOL_OPTIONS_EDITOR
argument_list|(
name|docked
argument_list|)
decl_stmt|;
name|GimpContext
modifier|*
name|context
decl_stmt|;
name|GimpToolInfo
modifier|*
name|tool_info
decl_stmt|;
name|context
operator|=
name|gimp_get_user_context
argument_list|(
name|editor
operator|->
name|gimp
argument_list|)
expr_stmt|;
name|tool_info
operator|=
name|gimp_context_get_tool
argument_list|(
name|context
argument_list|)
expr_stmt|;
return|return
name|g_strdup
argument_list|(
name|tool_info
operator|->
name|blurb
argument_list|)
return|;
block|}
end_function

begin_comment
comment|/*  public functions  */
end_comment

begin_function
name|GtkWidget
modifier|*
DECL|function|gimp_tool_options_editor_new (Gimp * gimp,GimpMenuFactory * menu_factory)
name|gimp_tool_options_editor_new
parameter_list|(
name|Gimp
modifier|*
name|gimp
parameter_list|,
name|GimpMenuFactory
modifier|*
name|menu_factory
parameter_list|)
block|{
name|GimpToolOptionsEditor
modifier|*
name|editor
decl_stmt|;
name|GimpContext
modifier|*
name|user_context
decl_stmt|;
name|g_return_val_if_fail
argument_list|(
name|GIMP_IS_GIMP
argument_list|(
name|gimp
argument_list|)
argument_list|,
name|NULL
argument_list|)
expr_stmt|;
name|g_return_val_if_fail
argument_list|(
name|GIMP_IS_MENU_FACTORY
argument_list|(
name|menu_factory
argument_list|)
argument_list|,
name|NULL
argument_list|)
expr_stmt|;
name|editor
operator|=
name|g_object_new
argument_list|(
name|GIMP_TYPE_TOOL_OPTIONS_EDITOR
argument_list|,
literal|"menu-factory"
argument_list|,
name|menu_factory
argument_list|,
literal|"menu-identifier"
argument_list|,
literal|"<ToolOptions>"
argument_list|,
literal|"ui-path"
argument_list|,
literal|"/tool-options-popup"
argument_list|,
name|NULL
argument_list|)
expr_stmt|;
name|editor
operator|->
name|gimp
operator|=
name|gimp
expr_stmt|;
name|user_context
operator|=
name|gimp_get_user_context
argument_list|(
name|gimp
argument_list|)
expr_stmt|;
name|g_signal_connect_object
argument_list|(
name|user_context
argument_list|,
literal|"tool_changed"
argument_list|,
name|G_CALLBACK
argument_list|(
name|gimp_tool_options_editor_tool_changed
argument_list|)
argument_list|,
name|editor
argument_list|,
literal|0
argument_list|)
expr_stmt|;
name|gimp_tool_options_editor_tool_changed
argument_list|(
name|user_context
argument_list|,
name|gimp_context_get_tool
argument_list|(
name|user_context
argument_list|)
argument_list|,
name|editor
argument_list|)
expr_stmt|;
return|return
name|GTK_WIDGET
argument_list|(
name|editor
argument_list|)
return|;
block|}
end_function

begin_comment
comment|/*  private functions  */
end_comment

begin_function
specifier|static
name|void
DECL|function|gimp_tool_options_editor_menu_pos (GtkMenu * menu,gint * x,gint * y,gpointer data)
name|gimp_tool_options_editor_menu_pos
parameter_list|(
name|GtkMenu
modifier|*
name|menu
parameter_list|,
name|gint
modifier|*
name|x
parameter_list|,
name|gint
modifier|*
name|y
parameter_list|,
name|gpointer
name|data
parameter_list|)
block|{
name|gimp_button_menu_position
argument_list|(
name|GTK_WIDGET
argument_list|(
name|data
argument_list|)
argument_list|,
name|menu
argument_list|,
name|GTK_POS_RIGHT
argument_list|,
name|x
argument_list|,
name|y
argument_list|)
expr_stmt|;
block|}
end_function

begin_function
specifier|static
name|void
DECL|function|gimp_tool_options_editor_menu_popup (GimpToolOptionsEditor * editor,GtkWidget * button,const gchar * path)
name|gimp_tool_options_editor_menu_popup
parameter_list|(
name|GimpToolOptionsEditor
modifier|*
name|editor
parameter_list|,
name|GtkWidget
modifier|*
name|button
parameter_list|,
specifier|const
name|gchar
modifier|*
name|path
parameter_list|)
block|{
name|GimpEditor
modifier|*
name|gimp_editor
init|=
name|GIMP_EDITOR
argument_list|(
name|editor
argument_list|)
decl_stmt|;
name|gimp_ui_manager_ui_get
argument_list|(
name|gimp_editor
operator|->
name|ui_manager
argument_list|,
name|gimp_editor
operator|->
name|ui_path
argument_list|)
expr_stmt|;
name|gimp_ui_manager_update
argument_list|(
name|gimp_editor
operator|->
name|ui_manager
argument_list|,
name|gimp_editor
operator|->
name|popup_data
argument_list|)
expr_stmt|;
name|gimp_ui_manager_ui_popup
argument_list|(
name|gimp_editor
operator|->
name|ui_manager
argument_list|,
name|path
argument_list|,
name|button
argument_list|,
name|gimp_tool_options_editor_menu_pos
argument_list|,
name|button
argument_list|,
name|NULL
argument_list|,
name|NULL
argument_list|)
expr_stmt|;
block|}
end_function

begin_function
specifier|static
name|void
DECL|function|gimp_tool_options_editor_save_clicked (GtkWidget * widget,GimpToolOptionsEditor * editor)
name|gimp_tool_options_editor_save_clicked
parameter_list|(
name|GtkWidget
modifier|*
name|widget
parameter_list|,
name|GimpToolOptionsEditor
modifier|*
name|editor
parameter_list|)
block|{
if|if
condition|(
name|GTK_WIDGET_SENSITIVE
argument_list|(
name|editor
operator|->
name|restore_button
argument_list|)
comment|/* evil but correct */
condition|)
block|{
name|gimp_tool_options_editor_menu_popup
argument_list|(
name|editor
argument_list|,
name|widget
argument_list|,
literal|"/tool-options-popup/Save"
argument_list|)
expr_stmt|;
block|}
else|else
block|{
name|GtkAction
modifier|*
name|action
decl_stmt|;
name|action
operator|=
name|gimp_ui_manager_get_action
argument_list|(
name|GIMP_EDITOR
argument_list|(
name|editor
argument_list|)
operator|->
name|ui_manager
argument_list|,
literal|"tool-options"
argument_list|,
literal|"tool-options-save-new"
argument_list|)
expr_stmt|;
if|if
condition|(
name|action
condition|)
name|gtk_action_activate
argument_list|(
name|action
argument_list|)
expr_stmt|;
block|}
block|}
end_function

begin_function
specifier|static
name|void
DECL|function|gimp_tool_options_editor_restore_clicked (GtkWidget * widget,GimpToolOptionsEditor * editor)
name|gimp_tool_options_editor_restore_clicked
parameter_list|(
name|GtkWidget
modifier|*
name|widget
parameter_list|,
name|GimpToolOptionsEditor
modifier|*
name|editor
parameter_list|)
block|{
name|gimp_tool_options_editor_menu_popup
argument_list|(
name|editor
argument_list|,
name|widget
argument_list|,
literal|"/tool-options-popup/Restore"
argument_list|)
expr_stmt|;
block|}
end_function

begin_function
specifier|static
name|void
DECL|function|gimp_tool_options_editor_delete_clicked (GtkWidget * widget,GimpToolOptionsEditor * editor)
name|gimp_tool_options_editor_delete_clicked
parameter_list|(
name|GtkWidget
modifier|*
name|widget
parameter_list|,
name|GimpToolOptionsEditor
modifier|*
name|editor
parameter_list|)
block|{
name|gimp_tool_options_editor_menu_popup
argument_list|(
name|editor
argument_list|,
name|widget
argument_list|,
literal|"/tool-options-popup/Delete"
argument_list|)
expr_stmt|;
block|}
end_function

begin_function
specifier|static
name|void
DECL|function|gimp_tool_options_editor_drop_tool (GtkWidget * widget,GimpViewable * viewable,gpointer data)
name|gimp_tool_options_editor_drop_tool
parameter_list|(
name|GtkWidget
modifier|*
name|widget
parameter_list|,
name|GimpViewable
modifier|*
name|viewable
parameter_list|,
name|gpointer
name|data
parameter_list|)
block|{
name|GimpToolOptionsEditor
modifier|*
name|editor
init|=
name|GIMP_TOOL_OPTIONS_EDITOR
argument_list|(
name|data
argument_list|)
decl_stmt|;
name|GimpContext
modifier|*
name|context
decl_stmt|;
name|context
operator|=
name|gimp_get_user_context
argument_list|(
name|editor
operator|->
name|gimp
argument_list|)
expr_stmt|;
name|gimp_context_set_tool
argument_list|(
name|context
argument_list|,
name|GIMP_TOOL_INFO
argument_list|(
name|viewable
argument_list|)
argument_list|)
expr_stmt|;
block|}
end_function

begin_function
specifier|static
name|void
DECL|function|gimp_tool_options_editor_tool_changed (GimpContext * context,GimpToolInfo * tool_info,GimpToolOptionsEditor * editor)
name|gimp_tool_options_editor_tool_changed
parameter_list|(
name|GimpContext
modifier|*
name|context
parameter_list|,
name|GimpToolInfo
modifier|*
name|tool_info
parameter_list|,
name|GimpToolOptionsEditor
modifier|*
name|editor
parameter_list|)
block|{
name|GimpContainer
modifier|*
name|presets
decl_stmt|;
name|GtkWidget
modifier|*
name|options_gui
decl_stmt|;
if|if
condition|(
name|tool_info
operator|&&
name|tool_info
operator|->
name|tool_options
operator|==
name|editor
operator|->
name|visible_tool_options
condition|)
return|return;
if|if
condition|(
name|editor
operator|->
name|visible_tool_options
condition|)
block|{
name|presets
operator|=
name|editor
operator|->
name|visible_tool_options
operator|->
name|tool_info
operator|->
name|options_presets
expr_stmt|;
if|if
condition|(
name|presets
condition|)
name|g_signal_handlers_disconnect_by_func
argument_list|(
name|presets
argument_list|,
name|gimp_tool_options_editor_presets_changed
argument_list|,
name|editor
argument_list|)
expr_stmt|;
name|options_gui
operator|=
name|g_object_get_data
argument_list|(
name|G_OBJECT
argument_list|(
name|editor
operator|->
name|visible_tool_options
argument_list|)
argument_list|,
literal|"gimp-tool-options-gui"
argument_list|)
expr_stmt|;
if|if
condition|(
name|options_gui
condition|)
name|gtk_widget_hide
argument_list|(
name|options_gui
argument_list|)
expr_stmt|;
name|editor
operator|->
name|visible_tool_options
operator|=
name|NULL
expr_stmt|;
block|}
if|if
condition|(
name|tool_info
operator|&&
name|tool_info
operator|->
name|tool_options
condition|)
block|{
name|presets
operator|=
name|tool_info
operator|->
name|options_presets
expr_stmt|;
if|if
condition|(
name|presets
condition|)
block|{
name|g_signal_connect_object
argument_list|(
name|presets
argument_list|,
literal|"add"
argument_list|,
name|G_CALLBACK
argument_list|(
name|gimp_tool_options_editor_presets_changed
argument_list|)
argument_list|,
name|G_OBJECT
argument_list|(
name|editor
argument_list|)
argument_list|,
literal|0
argument_list|)
expr_stmt|;
name|g_signal_connect_object
argument_list|(
name|presets
argument_list|,
literal|"remove"
argument_list|,
name|G_CALLBACK
argument_list|(
name|gimp_tool_options_editor_presets_changed
argument_list|)
argument_list|,
name|G_OBJECT
argument_list|(
name|editor
argument_list|)
argument_list|,
literal|0
argument_list|)
expr_stmt|;
block|}
name|options_gui
operator|=
name|g_object_get_data
argument_list|(
name|G_OBJECT
argument_list|(
name|tool_info
operator|->
name|tool_options
argument_list|)
argument_list|,
literal|"gimp-tool-options-gui"
argument_list|)
expr_stmt|;
if|if
condition|(
operator|!
name|options_gui
operator|->
name|parent
condition|)
name|gtk_box_pack_start
argument_list|(
name|GTK_BOX
argument_list|(
name|editor
operator|->
name|options_vbox
argument_list|)
argument_list|,
name|options_gui
argument_list|,
name|FALSE
argument_list|,
name|FALSE
argument_list|,
literal|0
argument_list|)
expr_stmt|;
name|gtk_widget_show
argument_list|(
name|options_gui
argument_list|)
expr_stmt|;
name|editor
operator|->
name|visible_tool_options
operator|=
name|tool_info
operator|->
name|tool_options
expr_stmt|;
name|gimp_help_set_help_data
argument_list|(
name|editor
operator|->
name|scrolled_window
argument_list|,
name|NULL
argument_list|,
name|tool_info
operator|->
name|help_id
argument_list|)
expr_stmt|;
block|}
else|else
block|{
name|presets
operator|=
name|NULL
expr_stmt|;
block|}
name|gimp_tool_options_editor_presets_changed
argument_list|(
name|presets
argument_list|,
name|NULL
argument_list|,
name|editor
argument_list|)
expr_stmt|;
name|gimp_docked_title_changed
argument_list|(
name|GIMP_DOCKED
argument_list|(
name|editor
argument_list|)
argument_list|)
expr_stmt|;
block|}
end_function

begin_function
specifier|static
name|void
DECL|function|gimp_tool_options_editor_presets_changed (GimpContainer * container,GimpToolOptions * options,GimpToolOptionsEditor * editor)
name|gimp_tool_options_editor_presets_changed
parameter_list|(
name|GimpContainer
modifier|*
name|container
parameter_list|,
name|GimpToolOptions
modifier|*
name|options
parameter_list|,
name|GimpToolOptionsEditor
modifier|*
name|editor
parameter_list|)
block|{
name|gboolean
name|save_sensitive
init|=
name|FALSE
decl_stmt|;
name|gboolean
name|restore_sensitive
init|=
name|FALSE
decl_stmt|;
name|gboolean
name|delete_sensitive
init|=
name|FALSE
decl_stmt|;
name|gboolean
name|reset_sensitive
init|=
name|FALSE
decl_stmt|;
if|if
condition|(
name|container
condition|)
block|{
name|save_sensitive
operator|=
name|TRUE
expr_stmt|;
name|reset_sensitive
operator|=
name|TRUE
expr_stmt|;
if|if
condition|(
name|gimp_container_num_children
argument_list|(
name|container
argument_list|)
condition|)
block|{
name|restore_sensitive
operator|=
name|TRUE
expr_stmt|;
name|delete_sensitive
operator|=
name|TRUE
expr_stmt|;
block|}
block|}
name|gtk_widget_set_sensitive
argument_list|(
name|editor
operator|->
name|save_button
argument_list|,
name|save_sensitive
argument_list|)
expr_stmt|;
name|gtk_widget_set_sensitive
argument_list|(
name|editor
operator|->
name|restore_button
argument_list|,
name|restore_sensitive
argument_list|)
expr_stmt|;
name|gtk_widget_set_sensitive
argument_list|(
name|editor
operator|->
name|delete_button
argument_list|,
name|delete_sensitive
argument_list|)
expr_stmt|;
name|gtk_widget_set_sensitive
argument_list|(
name|editor
operator|->
name|reset_button
argument_list|,
name|reset_sensitive
argument_list|)
expr_stmt|;
block|}
end_function

end_unit

