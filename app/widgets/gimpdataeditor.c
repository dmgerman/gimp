begin_unit|revision:0.9.5;language:C;cregit-version:0.0.1
begin_comment
comment|/* The GIMP -- an image manipulation program  * Copyright (C) 1995 Spencer Kimball and Peter Mattis  *  * gimpdataeditor.c  * Copyright (C) 2001 Michael Natterer<mitch@gimp.org>  *  * This program is free software; you can redistribute it and/or modify  * it under the terms of the GNU General Public License as published by  * the Free Software Foundation; either version 2 of the License, or  * (at your option) any later version.  *  * This program is distributed in the hope that it will be useful,  * but WITHOUT ANY WARRANTY; without even the implied warranty of  * MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the  * GNU General Public License for more details.  *  * You should have received a copy of the GNU General Public License  * along with this program; if not, write to the Free Software  * Foundation, Inc., 59 Temple Place - Suite 330, Boston, MA 02111-1307, USA.  */
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
file|"core/gimpcontainer.h"
end_include

begin_include
include|#
directive|include
file|"core/gimpcontext.h"
end_include

begin_include
include|#
directive|include
file|"core/gimpdata.h"
end_include

begin_include
include|#
directive|include
file|"core/gimpdatafactory.h"
end_include

begin_include
include|#
directive|include
file|"gimpdataeditor.h"
end_include

begin_include
include|#
directive|include
file|"gimpdocked.h"
end_include

begin_include
include|#
directive|include
file|"gimpmenufactory.h"
end_include

begin_include
include|#
directive|include
file|"gimpsessioninfo.h"
end_include

begin_include
include|#
directive|include
file|"gimp-intl.h"
end_include

begin_function_decl
specifier|static
name|void
name|gimp_data_editor_class_init
parameter_list|(
name|GimpDataEditorClass
modifier|*
name|klass
parameter_list|)
function_decl|;
end_function_decl

begin_function_decl
specifier|static
name|void
name|gimp_data_editor_init
parameter_list|(
name|GimpDataEditor
modifier|*
name|view
parameter_list|)
function_decl|;
end_function_decl

begin_function_decl
specifier|static
name|void
name|gimp_data_editor_docked_iface_init
parameter_list|(
name|GimpDockedInterface
modifier|*
name|docked_iface
parameter_list|)
function_decl|;
end_function_decl

begin_function_decl
specifier|static
name|void
name|gimp_data_editor_set_aux_info
parameter_list|(
name|GimpDocked
modifier|*
name|docked
parameter_list|,
name|GList
modifier|*
name|aux_info
parameter_list|)
function_decl|;
end_function_decl

begin_function_decl
specifier|static
name|GList
modifier|*
name|gimp_data_editor_get_aux_info
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
name|gimp_data_editor_dispose
parameter_list|(
name|GObject
modifier|*
name|object
parameter_list|)
function_decl|;
end_function_decl

begin_function_decl
specifier|static
name|void
name|gimp_data_editor_real_set_data
parameter_list|(
name|GimpDataEditor
modifier|*
name|editor
parameter_list|,
name|GimpData
modifier|*
name|data
parameter_list|)
function_decl|;
end_function_decl

begin_function_decl
specifier|static
name|void
name|gimp_data_editor_name_activate
parameter_list|(
name|GtkWidget
modifier|*
name|widget
parameter_list|,
name|GimpDataEditor
modifier|*
name|editor
parameter_list|)
function_decl|;
end_function_decl

begin_function_decl
specifier|static
name|gboolean
name|gimp_data_editor_name_focus_out
parameter_list|(
name|GtkWidget
modifier|*
name|widget
parameter_list|,
name|GdkEvent
modifier|*
name|event
parameter_list|,
name|GimpDataEditor
modifier|*
name|editor
parameter_list|)
function_decl|;
end_function_decl

begin_function_decl
specifier|static
name|void
name|gimp_data_editor_data_name_changed
parameter_list|(
name|GimpObject
modifier|*
name|object
parameter_list|,
name|GimpDataEditor
modifier|*
name|editor
parameter_list|)
function_decl|;
end_function_decl

begin_function_decl
specifier|static
name|void
name|gimp_data_editor_save_clicked
parameter_list|(
name|GtkWidget
modifier|*
name|widget
parameter_list|,
name|GimpDataEditor
modifier|*
name|editor
parameter_list|)
function_decl|;
end_function_decl

begin_function_decl
specifier|static
name|void
name|gimp_data_editor_revert_clicked
parameter_list|(
name|GtkWidget
modifier|*
name|widget
parameter_list|,
name|GimpDataEditor
modifier|*
name|editor
parameter_list|)
function_decl|;
end_function_decl

begin_function_decl
specifier|static
name|void
name|gimp_data_editor_save_dirty
parameter_list|(
name|GimpDataEditor
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
DECL|function|gimp_data_editor_get_type (void)
name|gimp_data_editor_get_type
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
name|view_info
init|=
block|{
sizeof|sizeof
argument_list|(
name|GimpDataEditorClass
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
name|gimp_data_editor_class_init
block|,
name|NULL
block|,
comment|/* class_finalize */
name|NULL
block|,
comment|/* class_data */
sizeof|sizeof
argument_list|(
name|GimpDataEditor
argument_list|)
block|,
literal|0
block|,
comment|/* n_preallocs */
operator|(
name|GInstanceInitFunc
operator|)
name|gimp_data_editor_init
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
name|gimp_data_editor_docked_iface_init
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
literal|"GimpDataEditor"
argument_list|,
operator|&
name|view_info
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
DECL|function|gimp_data_editor_class_init (GimpDataEditorClass * klass)
name|gimp_data_editor_class_init
parameter_list|(
name|GimpDataEditorClass
modifier|*
name|klass
parameter_list|)
block|{
name|GObjectClass
modifier|*
name|object_class
decl_stmt|;
name|object_class
operator|=
name|G_OBJECT_CLASS
argument_list|(
name|klass
argument_list|)
expr_stmt|;
name|parent_class
operator|=
name|g_type_class_peek_parent
argument_list|(
name|klass
argument_list|)
expr_stmt|;
name|object_class
operator|->
name|dispose
operator|=
name|gimp_data_editor_dispose
expr_stmt|;
name|klass
operator|->
name|set_data
operator|=
name|gimp_data_editor_real_set_data
expr_stmt|;
block|}
end_function

begin_function
specifier|static
name|void
DECL|function|gimp_data_editor_init (GimpDataEditor * editor)
name|gimp_data_editor_init
parameter_list|(
name|GimpDataEditor
modifier|*
name|editor
parameter_list|)
block|{
name|editor
operator|->
name|data_factory
operator|=
name|NULL
expr_stmt|;
name|editor
operator|->
name|data
operator|=
name|NULL
expr_stmt|;
name|editor
operator|->
name|data_editable
operator|=
name|FALSE
expr_stmt|;
name|editor
operator|->
name|name_entry
operator|=
name|gtk_entry_new
argument_list|()
expr_stmt|;
name|gtk_box_pack_start
argument_list|(
name|GTK_BOX
argument_list|(
name|editor
argument_list|)
argument_list|,
name|editor
operator|->
name|name_entry
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
name|editor
operator|->
name|name_entry
argument_list|)
expr_stmt|;
name|g_signal_connect
argument_list|(
name|editor
operator|->
name|name_entry
argument_list|,
literal|"activate"
argument_list|,
name|G_CALLBACK
argument_list|(
name|gimp_data_editor_name_activate
argument_list|)
argument_list|,
name|editor
argument_list|)
expr_stmt|;
name|g_signal_connect
argument_list|(
name|editor
operator|->
name|name_entry
argument_list|,
literal|"focus_out_event"
argument_list|,
name|G_CALLBACK
argument_list|(
name|gimp_data_editor_name_focus_out
argument_list|)
argument_list|,
name|editor
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
literal|"Save"
argument_list|)
argument_list|,
name|NULL
argument_list|,
name|G_CALLBACK
argument_list|(
name|gimp_data_editor_save_clicked
argument_list|)
argument_list|,
name|NULL
argument_list|,
name|editor
argument_list|)
expr_stmt|;
name|editor
operator|->
name|revert_button
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
literal|"Revert"
argument_list|)
argument_list|,
name|NULL
argument_list|,
name|G_CALLBACK
argument_list|(
name|gimp_data_editor_revert_clicked
argument_list|)
argument_list|,
name|NULL
argument_list|,
name|editor
argument_list|)
expr_stmt|;
block|}
end_function

begin_function
specifier|static
name|void
DECL|function|gimp_data_editor_docked_iface_init (GimpDockedInterface * docked_iface)
name|gimp_data_editor_docked_iface_init
parameter_list|(
name|GimpDockedInterface
modifier|*
name|docked_iface
parameter_list|)
block|{
name|docked_iface
operator|->
name|set_aux_info
operator|=
name|gimp_data_editor_set_aux_info
expr_stmt|;
name|docked_iface
operator|->
name|get_aux_info
operator|=
name|gimp_data_editor_get_aux_info
expr_stmt|;
block|}
end_function

begin_define
DECL|macro|AUX_INFO_CURRENT_DATA
define|#
directive|define
name|AUX_INFO_CURRENT_DATA
value|"current-data"
end_define

begin_function
specifier|static
name|void
DECL|function|gimp_data_editor_set_aux_info (GimpDocked * docked,GList * aux_info)
name|gimp_data_editor_set_aux_info
parameter_list|(
name|GimpDocked
modifier|*
name|docked
parameter_list|,
name|GList
modifier|*
name|aux_info
parameter_list|)
block|{
name|GimpDataEditor
modifier|*
name|editor
init|=
name|GIMP_DATA_EDITOR
argument_list|(
name|docked
argument_list|)
decl_stmt|;
name|GList
modifier|*
name|list
decl_stmt|;
for|for
control|(
name|list
operator|=
name|aux_info
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
name|GimpSessionInfoAux
modifier|*
name|aux
init|=
name|list
operator|->
name|data
decl_stmt|;
if|if
condition|(
operator|!
name|strcmp
argument_list|(
name|aux
operator|->
name|name
argument_list|,
name|AUX_INFO_CURRENT_DATA
argument_list|)
condition|)
block|{
name|GimpData
modifier|*
name|data
decl_stmt|;
name|data
operator|=
operator|(
name|GimpData
operator|*
operator|)
name|gimp_container_get_child_by_name
argument_list|(
name|editor
operator|->
name|data_factory
operator|->
name|container
argument_list|,
name|aux
operator|->
name|value
argument_list|)
expr_stmt|;
if|if
condition|(
name|data
condition|)
name|gimp_data_editor_set_data
argument_list|(
name|editor
argument_list|,
name|data
argument_list|)
expr_stmt|;
block|}
block|}
block|}
end_function

begin_function
specifier|static
name|GList
modifier|*
DECL|function|gimp_data_editor_get_aux_info (GimpDocked * docked)
name|gimp_data_editor_get_aux_info
parameter_list|(
name|GimpDocked
modifier|*
name|docked
parameter_list|)
block|{
name|GimpDataEditor
modifier|*
name|editor
init|=
name|GIMP_DATA_EDITOR
argument_list|(
name|docked
argument_list|)
decl_stmt|;
name|GList
modifier|*
name|aux_info
init|=
name|NULL
decl_stmt|;
if|if
condition|(
name|editor
operator|->
name|data
condition|)
block|{
name|GimpSessionInfoAux
modifier|*
name|aux
decl_stmt|;
specifier|const
name|gchar
modifier|*
name|value
decl_stmt|;
name|value
operator|=
name|gimp_object_get_name
argument_list|(
name|GIMP_OBJECT
argument_list|(
name|editor
operator|->
name|data
argument_list|)
argument_list|)
expr_stmt|;
name|aux
operator|=
name|gimp_session_info_aux_new
argument_list|(
name|AUX_INFO_CURRENT_DATA
argument_list|,
name|value
argument_list|)
expr_stmt|;
name|aux_info
operator|=
name|g_list_append
argument_list|(
name|aux_info
argument_list|,
name|aux
argument_list|)
expr_stmt|;
block|}
return|return
name|aux_info
return|;
block|}
end_function

begin_function
specifier|static
name|void
DECL|function|gimp_data_editor_dispose (GObject * object)
name|gimp_data_editor_dispose
parameter_list|(
name|GObject
modifier|*
name|object
parameter_list|)
block|{
name|GimpDataEditor
modifier|*
name|editor
init|=
name|GIMP_DATA_EDITOR
argument_list|(
name|object
argument_list|)
decl_stmt|;
if|if
condition|(
name|editor
operator|->
name|data
condition|)
block|{
comment|/* Save dirty data before we clear out */
name|gimp_data_editor_save_dirty
argument_list|(
name|editor
argument_list|)
expr_stmt|;
name|gimp_data_editor_set_data
argument_list|(
name|editor
argument_list|,
name|NULL
argument_list|)
expr_stmt|;
block|}
name|G_OBJECT_CLASS
argument_list|(
name|parent_class
argument_list|)
operator|->
name|dispose
argument_list|(
name|object
argument_list|)
expr_stmt|;
block|}
end_function

begin_function
specifier|static
name|void
DECL|function|gimp_data_editor_real_set_data (GimpDataEditor * editor,GimpData * data)
name|gimp_data_editor_real_set_data
parameter_list|(
name|GimpDataEditor
modifier|*
name|editor
parameter_list|,
name|GimpData
modifier|*
name|data
parameter_list|)
block|{
if|if
condition|(
name|editor
operator|->
name|data
condition|)
block|{
name|g_signal_handlers_disconnect_by_func
argument_list|(
name|editor
operator|->
name|data
argument_list|,
name|gimp_data_editor_data_name_changed
argument_list|,
name|editor
argument_list|)
expr_stmt|;
name|g_object_unref
argument_list|(
name|editor
operator|->
name|data
argument_list|)
expr_stmt|;
block|}
name|editor
operator|->
name|data
operator|=
name|data
expr_stmt|;
if|if
condition|(
name|editor
operator|->
name|data
condition|)
block|{
name|g_object_ref
argument_list|(
name|editor
operator|->
name|data
argument_list|)
expr_stmt|;
name|g_signal_connect
argument_list|(
name|editor
operator|->
name|data
argument_list|,
literal|"name_changed"
argument_list|,
name|G_CALLBACK
argument_list|(
name|gimp_data_editor_data_name_changed
argument_list|)
argument_list|,
name|editor
argument_list|)
expr_stmt|;
name|gtk_entry_set_text
argument_list|(
name|GTK_ENTRY
argument_list|(
name|editor
operator|->
name|name_entry
argument_list|)
argument_list|,
name|gimp_object_get_name
argument_list|(
name|GIMP_OBJECT
argument_list|(
name|editor
operator|->
name|data
argument_list|)
argument_list|)
argument_list|)
expr_stmt|;
block|}
else|else
block|{
name|gtk_entry_set_text
argument_list|(
name|GTK_ENTRY
argument_list|(
name|editor
operator|->
name|name_entry
argument_list|)
argument_list|,
literal|""
argument_list|)
expr_stmt|;
block|}
name|editor
operator|->
name|data_editable
operator|=
operator|(
name|editor
operator|->
name|data
operator|&&
name|editor
operator|->
name|data
operator|->
name|writable
operator|)
expr_stmt|;
name|gtk_widget_set_sensitive
argument_list|(
name|editor
operator|->
name|name_entry
argument_list|,
name|editor
operator|->
name|data_editable
argument_list|)
expr_stmt|;
block|}
end_function

begin_function
name|gboolean
DECL|function|gimp_data_editor_construct (GimpDataEditor * editor,GimpDataFactory * data_factory,GimpMenuFactory * menu_factory,const gchar * menu_identifier,const gchar * ui_identifier)
name|gimp_data_editor_construct
parameter_list|(
name|GimpDataEditor
modifier|*
name|editor
parameter_list|,
name|GimpDataFactory
modifier|*
name|data_factory
parameter_list|,
name|GimpMenuFactory
modifier|*
name|menu_factory
parameter_list|,
specifier|const
name|gchar
modifier|*
name|menu_identifier
parameter_list|,
specifier|const
name|gchar
modifier|*
name|ui_identifier
parameter_list|)
block|{
name|GimpData
modifier|*
name|data
decl_stmt|;
name|g_return_val_if_fail
argument_list|(
name|GIMP_IS_DATA_EDITOR
argument_list|(
name|editor
argument_list|)
argument_list|,
name|FALSE
argument_list|)
expr_stmt|;
name|g_return_val_if_fail
argument_list|(
name|GIMP_IS_DATA_FACTORY
argument_list|(
name|data_factory
argument_list|)
argument_list|,
name|FALSE
argument_list|)
expr_stmt|;
name|g_return_val_if_fail
argument_list|(
name|menu_factory
operator|==
name|NULL
operator|||
name|GIMP_IS_MENU_FACTORY
argument_list|(
name|menu_factory
argument_list|)
argument_list|,
name|FALSE
argument_list|)
expr_stmt|;
name|g_return_val_if_fail
argument_list|(
name|menu_factory
operator|==
name|NULL
operator|||
name|menu_identifier
operator|!=
name|NULL
argument_list|,
name|FALSE
argument_list|)
expr_stmt|;
name|editor
operator|->
name|data_factory
operator|=
name|data_factory
expr_stmt|;
if|if
condition|(
name|menu_factory
operator|&&
name|menu_identifier
operator|&&
name|ui_identifier
condition|)
name|gimp_editor_create_menu
argument_list|(
name|GIMP_EDITOR
argument_list|(
name|editor
argument_list|)
argument_list|,
name|menu_factory
argument_list|,
name|menu_identifier
argument_list|,
name|ui_identifier
argument_list|,
name|editor
argument_list|)
expr_stmt|;
name|data
operator|=
operator|(
name|GimpData
operator|*
operator|)
name|gimp_context_get_by_type
argument_list|(
name|gimp_get_user_context
argument_list|(
name|data_factory
operator|->
name|gimp
argument_list|)
argument_list|,
name|data_factory
operator|->
name|container
operator|->
name|children_type
argument_list|)
expr_stmt|;
name|gimp_data_editor_set_data
argument_list|(
name|editor
argument_list|,
name|data
argument_list|)
expr_stmt|;
return|return
name|TRUE
return|;
block|}
end_function

begin_function
name|void
DECL|function|gimp_data_editor_set_data (GimpDataEditor * editor,GimpData * data)
name|gimp_data_editor_set_data
parameter_list|(
name|GimpDataEditor
modifier|*
name|editor
parameter_list|,
name|GimpData
modifier|*
name|data
parameter_list|)
block|{
name|g_return_if_fail
argument_list|(
name|GIMP_IS_DATA_EDITOR
argument_list|(
name|editor
argument_list|)
argument_list|)
expr_stmt|;
name|g_return_if_fail
argument_list|(
name|data
operator|==
name|NULL
operator|||
name|GIMP_IS_DATA
argument_list|(
name|data
argument_list|)
argument_list|)
expr_stmt|;
name|g_return_if_fail
argument_list|(
name|data
operator|==
name|NULL
operator|||
name|g_type_is_a
argument_list|(
name|G_TYPE_FROM_INSTANCE
argument_list|(
name|data
argument_list|)
argument_list|,
name|editor
operator|->
name|data_factory
operator|->
name|container
operator|->
name|children_type
argument_list|)
argument_list|)
expr_stmt|;
if|if
condition|(
name|editor
operator|->
name|data
operator|!=
name|data
condition|)
name|GIMP_DATA_EDITOR_GET_CLASS
argument_list|(
name|editor
argument_list|)
operator|->
name|set_data
argument_list|(
name|editor
argument_list|,
name|data
argument_list|)
expr_stmt|;
block|}
end_function

begin_function
name|GimpData
modifier|*
DECL|function|gimp_data_editor_get_data (GimpDataEditor * editor)
name|gimp_data_editor_get_data
parameter_list|(
name|GimpDataEditor
modifier|*
name|editor
parameter_list|)
block|{
name|g_return_val_if_fail
argument_list|(
name|GIMP_IS_DATA_EDITOR
argument_list|(
name|editor
argument_list|)
argument_list|,
name|NULL
argument_list|)
expr_stmt|;
return|return
name|editor
operator|->
name|data
return|;
block|}
end_function

begin_comment
comment|/*  private functions  */
end_comment

begin_function
specifier|static
name|void
DECL|function|gimp_data_editor_name_activate (GtkWidget * widget,GimpDataEditor * editor)
name|gimp_data_editor_name_activate
parameter_list|(
name|GtkWidget
modifier|*
name|widget
parameter_list|,
name|GimpDataEditor
modifier|*
name|editor
parameter_list|)
block|{
if|if
condition|(
name|editor
operator|->
name|data
condition|)
block|{
specifier|const
name|gchar
modifier|*
name|entry_text
decl_stmt|;
name|entry_text
operator|=
name|gtk_entry_get_text
argument_list|(
name|GTK_ENTRY
argument_list|(
name|widget
argument_list|)
argument_list|)
expr_stmt|;
name|gimp_object_set_name
argument_list|(
name|GIMP_OBJECT
argument_list|(
name|editor
operator|->
name|data
argument_list|)
argument_list|,
name|entry_text
argument_list|)
expr_stmt|;
block|}
block|}
end_function

begin_function
specifier|static
name|gboolean
DECL|function|gimp_data_editor_name_focus_out (GtkWidget * widget,GdkEvent * event,GimpDataEditor * editor)
name|gimp_data_editor_name_focus_out
parameter_list|(
name|GtkWidget
modifier|*
name|widget
parameter_list|,
name|GdkEvent
modifier|*
name|event
parameter_list|,
name|GimpDataEditor
modifier|*
name|editor
parameter_list|)
block|{
name|gimp_data_editor_name_activate
argument_list|(
name|widget
argument_list|,
name|editor
argument_list|)
expr_stmt|;
return|return
name|FALSE
return|;
block|}
end_function

begin_function
specifier|static
name|void
DECL|function|gimp_data_editor_data_name_changed (GimpObject * object,GimpDataEditor * editor)
name|gimp_data_editor_data_name_changed
parameter_list|(
name|GimpObject
modifier|*
name|object
parameter_list|,
name|GimpDataEditor
modifier|*
name|editor
parameter_list|)
block|{
name|gtk_entry_set_text
argument_list|(
name|GTK_ENTRY
argument_list|(
name|editor
operator|->
name|name_entry
argument_list|)
argument_list|,
name|gimp_object_get_name
argument_list|(
name|object
argument_list|)
argument_list|)
expr_stmt|;
block|}
end_function

begin_function
specifier|static
name|void
DECL|function|gimp_data_editor_save_clicked (GtkWidget * widget,GimpDataEditor * editor)
name|gimp_data_editor_save_clicked
parameter_list|(
name|GtkWidget
modifier|*
name|widget
parameter_list|,
name|GimpDataEditor
modifier|*
name|editor
parameter_list|)
block|{
name|gimp_data_editor_save_dirty
argument_list|(
name|editor
argument_list|)
expr_stmt|;
block|}
end_function

begin_function
specifier|static
name|void
DECL|function|gimp_data_editor_revert_clicked (GtkWidget * widget,GimpDataEditor * editor)
name|gimp_data_editor_revert_clicked
parameter_list|(
name|GtkWidget
modifier|*
name|widget
parameter_list|,
name|GimpDataEditor
modifier|*
name|editor
parameter_list|)
block|{
name|g_print
argument_list|(
literal|"TODO: implement revert\n"
argument_list|)
expr_stmt|;
block|}
end_function

begin_function
specifier|static
name|void
DECL|function|gimp_data_editor_save_dirty (GimpDataEditor * editor)
name|gimp_data_editor_save_dirty
parameter_list|(
name|GimpDataEditor
modifier|*
name|editor
parameter_list|)
block|{
name|GimpData
modifier|*
name|data
init|=
name|editor
operator|->
name|data
decl_stmt|;
if|if
condition|(
name|data
operator|&&
name|data
operator|->
name|dirty
operator|&&
name|data
operator|->
name|writable
condition|)
name|gimp_data_factory_data_save_single
argument_list|(
name|editor
operator|->
name|data_factory
argument_list|,
name|data
argument_list|)
expr_stmt|;
block|}
end_function

end_unit

