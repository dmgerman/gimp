begin_unit|revision:0.9.5;language:C;cregit-version:0.0.1
begin_comment
comment|/* GIMP - The GNU Image Manipulation Program  * Copyright (C) 1995 Spencer Kimball and Peter Mattis  *  * gimpsettingseditor.c  * Copyright (C) 2008 Michael Natterer<mitch@gimp.org>  *  * This program is free software; you can redistribute it and/or modify  * it under the terms of the GNU General Public License as published by  * the Free Software Foundation; either version 2 of the License, or  * (at your option) any later version.  *  * This program is distributed in the hope that it will be useful,  * but WITHOUT ANY WARRANTY; without even the implied warranty of  * MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the  * GNU General Public License for more details.  *  * You should have received a copy of the GNU General Public License  * along with this program; if not, write to the Free Software  * Foundation, Inc., 59 Temple Place - Suite 330, Boston, MA 02111-1307, USA.  */
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
file|"libgimpbase/gimpbase.h"
end_include

begin_include
include|#
directive|include
file|"libgimpconfig/gimpconfig.h"
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
file|"gimpcontainertreeview.h"
end_include

begin_include
include|#
directive|include
file|"gimpcontainerview.h"
end_include

begin_include
include|#
directive|include
file|"gimpsettingseditor.h"
end_include

begin_include
include|#
directive|include
file|"gimpviewrenderer.h"
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

begin_enum
enum|enum
DECL|enum|__anon2954c0240103
block|{
DECL|enumerator|PROP_0
name|PROP_0
block|,
DECL|enumerator|PROP_GIMP
name|PROP_GIMP
block|,
DECL|enumerator|PROP_CONFIG
name|PROP_CONFIG
block|,
DECL|enumerator|PROP_CONTAINER
name|PROP_CONTAINER
block|,
DECL|enumerator|PROP_FILENAME
name|PROP_FILENAME
block|}
enum|;
end_enum

begin_function_decl
specifier|static
name|GObject
modifier|*
name|gimp_settings_editor_constructor
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
name|gimp_settings_editor_finalize
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
name|gimp_settings_editor_set_property
parameter_list|(
name|GObject
modifier|*
name|object
parameter_list|,
name|guint
name|property_id
parameter_list|,
specifier|const
name|GValue
modifier|*
name|value
parameter_list|,
name|GParamSpec
modifier|*
name|pspec
parameter_list|)
function_decl|;
end_function_decl

begin_function_decl
specifier|static
name|void
name|gimp_settings_editor_get_property
parameter_list|(
name|GObject
modifier|*
name|object
parameter_list|,
name|guint
name|property_id
parameter_list|,
name|GValue
modifier|*
name|value
parameter_list|,
name|GParamSpec
modifier|*
name|pspec
parameter_list|)
function_decl|;
end_function_decl

begin_function_decl
specifier|static
name|gboolean
name|gimp_settings_editor_row_separator_func
parameter_list|(
name|GtkTreeModel
modifier|*
name|model
parameter_list|,
name|GtkTreeIter
modifier|*
name|iter
parameter_list|,
name|gpointer
name|data
parameter_list|)
function_decl|;
end_function_decl

begin_function_decl
specifier|static
name|void
name|gimp_settings_editor_select_item
parameter_list|(
name|GimpContainerView
modifier|*
name|view
parameter_list|,
name|GimpViewable
modifier|*
name|viewable
parameter_list|,
name|gpointer
name|insert_data
parameter_list|,
name|GimpSettingsEditor
modifier|*
name|editor
parameter_list|)
function_decl|;
end_function_decl

begin_function_decl
specifier|static
name|void
name|gimp_settings_editor_delete_clicked
parameter_list|(
name|GtkWidget
modifier|*
name|widget
parameter_list|,
name|GimpSettingsEditor
modifier|*
name|editor
parameter_list|)
function_decl|;
end_function_decl

begin_function_decl
specifier|static
name|void
name|gimp_settings_editor_name_edited
parameter_list|(
name|GtkCellRendererText
modifier|*
name|cell
parameter_list|,
specifier|const
name|gchar
modifier|*
name|path_str
parameter_list|,
specifier|const
name|gchar
modifier|*
name|new_name
parameter_list|,
name|GimpSettingsEditor
modifier|*
name|editor
parameter_list|)
function_decl|;
end_function_decl

begin_macro
DECL|function|G_DEFINE_TYPE (GimpSettingsEditor,gimp_settings_editor,GTK_TYPE_VBOX)
name|G_DEFINE_TYPE
argument_list|(
argument|GimpSettingsEditor
argument_list|,
argument|gimp_settings_editor
argument_list|,
argument|GTK_TYPE_VBOX
argument_list|)
end_macro

begin_define
DECL|macro|parent_class
define|#
directive|define
name|parent_class
value|gimp_settings_editor_parent_class
end_define

begin_function
specifier|static
name|void
name|gimp_settings_editor_class_init
parameter_list|(
name|GimpSettingsEditorClass
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
name|object_class
operator|->
name|constructor
operator|=
name|gimp_settings_editor_constructor
expr_stmt|;
name|object_class
operator|->
name|finalize
operator|=
name|gimp_settings_editor_finalize
expr_stmt|;
name|object_class
operator|->
name|set_property
operator|=
name|gimp_settings_editor_set_property
expr_stmt|;
name|object_class
operator|->
name|get_property
operator|=
name|gimp_settings_editor_get_property
expr_stmt|;
name|g_object_class_install_property
argument_list|(
name|object_class
argument_list|,
name|PROP_GIMP
argument_list|,
name|g_param_spec_object
argument_list|(
literal|"gimp"
argument_list|,
name|NULL
argument_list|,
name|NULL
argument_list|,
name|GIMP_TYPE_GIMP
argument_list|,
name|GIMP_PARAM_READWRITE
operator||
name|G_PARAM_CONSTRUCT_ONLY
argument_list|)
argument_list|)
expr_stmt|;
name|g_object_class_install_property
argument_list|(
name|object_class
argument_list|,
name|PROP_CONFIG
argument_list|,
name|g_param_spec_object
argument_list|(
literal|"config"
argument_list|,
name|NULL
argument_list|,
name|NULL
argument_list|,
name|GIMP_TYPE_CONFIG
argument_list|,
name|GIMP_PARAM_READWRITE
operator||
name|G_PARAM_CONSTRUCT_ONLY
argument_list|)
argument_list|)
expr_stmt|;
name|g_object_class_install_property
argument_list|(
name|object_class
argument_list|,
name|PROP_CONTAINER
argument_list|,
name|g_param_spec_object
argument_list|(
literal|"container"
argument_list|,
name|NULL
argument_list|,
name|NULL
argument_list|,
name|GIMP_TYPE_CONTAINER
argument_list|,
name|GIMP_PARAM_READWRITE
operator||
name|G_PARAM_CONSTRUCT_ONLY
argument_list|)
argument_list|)
expr_stmt|;
block|}
end_function

begin_function
specifier|static
name|void
DECL|function|gimp_settings_editor_init (GimpSettingsEditor * editor)
name|gimp_settings_editor_init
parameter_list|(
name|GimpSettingsEditor
modifier|*
name|editor
parameter_list|)
block|{
name|gtk_box_set_spacing
argument_list|(
name|GTK_BOX
argument_list|(
name|editor
argument_list|)
argument_list|,
literal|6
argument_list|)
expr_stmt|;
block|}
end_function

begin_function
specifier|static
name|GObject
modifier|*
DECL|function|gimp_settings_editor_constructor (GType type,guint n_params,GObjectConstructParam * params)
name|gimp_settings_editor_constructor
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
name|GimpSettingsEditor
modifier|*
name|editor
decl_stmt|;
name|GimpContainerTreeView
modifier|*
name|tree_view
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
name|GIMP_SETTINGS_EDITOR
argument_list|(
name|object
argument_list|)
expr_stmt|;
name|g_assert
argument_list|(
name|GIMP_IS_GIMP
argument_list|(
name|editor
operator|->
name|gimp
argument_list|)
argument_list|)
expr_stmt|;
name|g_assert
argument_list|(
name|GIMP_IS_CONFIG
argument_list|(
name|editor
operator|->
name|config
argument_list|)
argument_list|)
expr_stmt|;
name|g_assert
argument_list|(
name|GIMP_IS_CONTAINER
argument_list|(
name|editor
operator|->
name|container
argument_list|)
argument_list|)
expr_stmt|;
name|editor
operator|->
name|view
operator|=
name|gimp_container_tree_view_new
argument_list|(
name|editor
operator|->
name|container
argument_list|,
name|gimp_get_user_context
argument_list|(
name|editor
operator|->
name|gimp
argument_list|)
argument_list|,
literal|16
argument_list|,
literal|0
argument_list|)
expr_stmt|;
name|gtk_container_add
argument_list|(
name|GTK_CONTAINER
argument_list|(
name|editor
argument_list|)
argument_list|,
name|editor
operator|->
name|view
argument_list|)
expr_stmt|;
name|gtk_widget_show
argument_list|(
name|editor
operator|->
name|view
argument_list|)
expr_stmt|;
name|tree_view
operator|=
name|GIMP_CONTAINER_TREE_VIEW
argument_list|(
name|editor
operator|->
name|view
argument_list|)
expr_stmt|;
name|gtk_tree_view_set_row_separator_func
argument_list|(
name|tree_view
operator|->
name|view
argument_list|,
name|gimp_settings_editor_row_separator_func
argument_list|,
name|editor
operator|->
name|view
argument_list|,
name|NULL
argument_list|)
expr_stmt|;
name|g_signal_connect
argument_list|(
name|tree_view
argument_list|,
literal|"select-item"
argument_list|,
name|G_CALLBACK
argument_list|(
name|gimp_settings_editor_select_item
argument_list|)
argument_list|,
name|editor
argument_list|)
expr_stmt|;
name|tree_view
operator|->
name|name_cell
operator|->
name|mode
operator|=
name|GTK_CELL_RENDERER_MODE_EDITABLE
expr_stmt|;
name|GTK_CELL_RENDERER_TEXT
argument_list|(
name|tree_view
operator|->
name|name_cell
argument_list|)
operator|->
name|editable
operator|=
name|TRUE
expr_stmt|;
name|tree_view
operator|->
name|editable_cells
operator|=
name|g_list_prepend
argument_list|(
name|tree_view
operator|->
name|editable_cells
argument_list|,
name|tree_view
operator|->
name|name_cell
argument_list|)
expr_stmt|;
name|g_signal_connect
argument_list|(
name|tree_view
operator|->
name|name_cell
argument_list|,
literal|"edited"
argument_list|,
name|G_CALLBACK
argument_list|(
name|gimp_settings_editor_name_edited
argument_list|)
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
name|tree_view
argument_list|)
argument_list|,
name|GTK_STOCK_DELETE
argument_list|,
name|_
argument_list|(
literal|"Delete the selected setting"
argument_list|)
argument_list|,
name|NULL
argument_list|,
name|G_CALLBACK
argument_list|(
name|gimp_settings_editor_delete_clicked
argument_list|)
argument_list|,
name|NULL
argument_list|,
name|editor
argument_list|)
expr_stmt|;
name|gtk_widget_set_sensitive
argument_list|(
name|editor
operator|->
name|delete_button
argument_list|,
name|FALSE
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
DECL|function|gimp_settings_editor_finalize (GObject * object)
name|gimp_settings_editor_finalize
parameter_list|(
name|GObject
modifier|*
name|object
parameter_list|)
block|{
name|GimpSettingsEditor
modifier|*
name|editor
init|=
name|GIMP_SETTINGS_EDITOR
argument_list|(
name|object
argument_list|)
decl_stmt|;
if|if
condition|(
name|editor
operator|->
name|config
condition|)
block|{
name|g_object_unref
argument_list|(
name|editor
operator|->
name|config
argument_list|)
expr_stmt|;
name|editor
operator|->
name|config
operator|=
name|NULL
expr_stmt|;
block|}
if|if
condition|(
name|editor
operator|->
name|container
condition|)
block|{
name|g_object_unref
argument_list|(
name|editor
operator|->
name|container
argument_list|)
expr_stmt|;
name|editor
operator|->
name|container
operator|=
name|NULL
expr_stmt|;
block|}
name|G_OBJECT_CLASS
argument_list|(
name|parent_class
argument_list|)
operator|->
name|finalize
argument_list|(
name|object
argument_list|)
expr_stmt|;
block|}
end_function

begin_function
specifier|static
name|void
DECL|function|gimp_settings_editor_set_property (GObject * object,guint property_id,const GValue * value,GParamSpec * pspec)
name|gimp_settings_editor_set_property
parameter_list|(
name|GObject
modifier|*
name|object
parameter_list|,
name|guint
name|property_id
parameter_list|,
specifier|const
name|GValue
modifier|*
name|value
parameter_list|,
name|GParamSpec
modifier|*
name|pspec
parameter_list|)
block|{
name|GimpSettingsEditor
modifier|*
name|editor
init|=
name|GIMP_SETTINGS_EDITOR
argument_list|(
name|object
argument_list|)
decl_stmt|;
switch|switch
condition|(
name|property_id
condition|)
block|{
case|case
name|PROP_GIMP
case|:
name|editor
operator|->
name|gimp
operator|=
name|g_value_get_object
argument_list|(
name|value
argument_list|)
expr_stmt|;
comment|/* don't dup */
break|break;
case|case
name|PROP_CONFIG
case|:
name|editor
operator|->
name|config
operator|=
name|g_value_dup_object
argument_list|(
name|value
argument_list|)
expr_stmt|;
break|break;
case|case
name|PROP_CONTAINER
case|:
name|editor
operator|->
name|container
operator|=
name|g_value_dup_object
argument_list|(
name|value
argument_list|)
expr_stmt|;
break|break;
default|default:
name|G_OBJECT_WARN_INVALID_PROPERTY_ID
argument_list|(
name|object
argument_list|,
name|property_id
argument_list|,
name|pspec
argument_list|)
expr_stmt|;
break|break;
block|}
block|}
end_function

begin_function
specifier|static
name|void
DECL|function|gimp_settings_editor_get_property (GObject * object,guint property_id,GValue * value,GParamSpec * pspec)
name|gimp_settings_editor_get_property
parameter_list|(
name|GObject
modifier|*
name|object
parameter_list|,
name|guint
name|property_id
parameter_list|,
name|GValue
modifier|*
name|value
parameter_list|,
name|GParamSpec
modifier|*
name|pspec
parameter_list|)
block|{
name|GimpSettingsEditor
modifier|*
name|editor
init|=
name|GIMP_SETTINGS_EDITOR
argument_list|(
name|object
argument_list|)
decl_stmt|;
switch|switch
condition|(
name|property_id
condition|)
block|{
case|case
name|PROP_GIMP
case|:
name|g_value_set_object
argument_list|(
name|value
argument_list|,
name|editor
operator|->
name|gimp
argument_list|)
expr_stmt|;
break|break;
case|case
name|PROP_CONFIG
case|:
name|g_value_set_object
argument_list|(
name|value
argument_list|,
name|editor
operator|->
name|config
argument_list|)
expr_stmt|;
break|break;
case|case
name|PROP_CONTAINER
case|:
name|g_value_set_object
argument_list|(
name|value
argument_list|,
name|editor
operator|->
name|container
argument_list|)
expr_stmt|;
break|break;
default|default:
name|G_OBJECT_WARN_INVALID_PROPERTY_ID
argument_list|(
name|object
argument_list|,
name|property_id
argument_list|,
name|pspec
argument_list|)
expr_stmt|;
break|break;
block|}
block|}
end_function

begin_function
specifier|static
name|gboolean
DECL|function|gimp_settings_editor_row_separator_func (GtkTreeModel * model,GtkTreeIter * iter,gpointer data)
name|gimp_settings_editor_row_separator_func
parameter_list|(
name|GtkTreeModel
modifier|*
name|model
parameter_list|,
name|GtkTreeIter
modifier|*
name|iter
parameter_list|,
name|gpointer
name|data
parameter_list|)
block|{
name|GimpContainerTreeView
modifier|*
name|view
init|=
name|GIMP_CONTAINER_TREE_VIEW
argument_list|(
name|data
argument_list|)
decl_stmt|;
name|gchar
modifier|*
name|name
init|=
name|NULL
decl_stmt|;
name|gtk_tree_model_get
argument_list|(
name|model
argument_list|,
name|iter
argument_list|,
name|view
operator|->
name|model_column_name
argument_list|,
operator|&
name|name
argument_list|,
operator|-
literal|1
argument_list|)
expr_stmt|;
name|g_free
argument_list|(
name|name
argument_list|)
expr_stmt|;
return|return
name|name
operator|==
name|NULL
return|;
block|}
end_function

begin_function
specifier|static
name|void
DECL|function|gimp_settings_editor_select_item (GimpContainerView * view,GimpViewable * viewable,gpointer insert_data,GimpSettingsEditor * editor)
name|gimp_settings_editor_select_item
parameter_list|(
name|GimpContainerView
modifier|*
name|view
parameter_list|,
name|GimpViewable
modifier|*
name|viewable
parameter_list|,
name|gpointer
name|insert_data
parameter_list|,
name|GimpSettingsEditor
modifier|*
name|editor
parameter_list|)
block|{
name|editor
operator|->
name|selected_setting
operator|=
name|G_OBJECT
argument_list|(
name|viewable
argument_list|)
expr_stmt|;
name|gtk_widget_set_sensitive
argument_list|(
name|editor
operator|->
name|delete_button
argument_list|,
name|editor
operator|->
name|selected_setting
operator|!=
name|NULL
argument_list|)
expr_stmt|;
block|}
end_function

begin_function
specifier|static
name|void
DECL|function|gimp_settings_editor_delete_clicked (GtkWidget * widget,GimpSettingsEditor * editor)
name|gimp_settings_editor_delete_clicked
parameter_list|(
name|GtkWidget
modifier|*
name|widget
parameter_list|,
name|GimpSettingsEditor
modifier|*
name|editor
parameter_list|)
block|{
if|if
condition|(
name|editor
operator|->
name|selected_setting
condition|)
name|gimp_container_remove
argument_list|(
name|editor
operator|->
name|container
argument_list|,
name|GIMP_OBJECT
argument_list|(
name|editor
operator|->
name|selected_setting
argument_list|)
argument_list|)
expr_stmt|;
block|}
end_function

begin_function
specifier|static
name|void
DECL|function|gimp_settings_editor_name_edited (GtkCellRendererText * cell,const gchar * path_str,const gchar * new_name,GimpSettingsEditor * editor)
name|gimp_settings_editor_name_edited
parameter_list|(
name|GtkCellRendererText
modifier|*
name|cell
parameter_list|,
specifier|const
name|gchar
modifier|*
name|path_str
parameter_list|,
specifier|const
name|gchar
modifier|*
name|new_name
parameter_list|,
name|GimpSettingsEditor
modifier|*
name|editor
parameter_list|)
block|{
name|GimpContainerTreeView
modifier|*
name|tree_view
decl_stmt|;
name|GtkTreePath
modifier|*
name|path
decl_stmt|;
name|GtkTreeIter
name|iter
decl_stmt|;
name|tree_view
operator|=
name|GIMP_CONTAINER_TREE_VIEW
argument_list|(
name|editor
operator|->
name|view
argument_list|)
expr_stmt|;
name|path
operator|=
name|gtk_tree_path_new_from_string
argument_list|(
name|path_str
argument_list|)
expr_stmt|;
if|if
condition|(
name|gtk_tree_model_get_iter
argument_list|(
name|tree_view
operator|->
name|model
argument_list|,
operator|&
name|iter
argument_list|,
name|path
argument_list|)
condition|)
block|{
name|GimpViewRenderer
modifier|*
name|renderer
decl_stmt|;
name|GimpObject
modifier|*
name|object
decl_stmt|;
specifier|const
name|gchar
modifier|*
name|old_name
decl_stmt|;
name|gchar
modifier|*
name|name
decl_stmt|;
name|gtk_tree_model_get
argument_list|(
name|tree_view
operator|->
name|model
argument_list|,
operator|&
name|iter
argument_list|,
name|tree_view
operator|->
name|model_column_renderer
argument_list|,
operator|&
name|renderer
argument_list|,
operator|-
literal|1
argument_list|)
expr_stmt|;
name|object
operator|=
name|GIMP_OBJECT
argument_list|(
name|renderer
operator|->
name|viewable
argument_list|)
expr_stmt|;
name|old_name
operator|=
name|gimp_object_get_name
argument_list|(
name|object
argument_list|)
expr_stmt|;
if|if
condition|(
operator|!
name|old_name
condition|)
name|old_name
operator|=
literal|""
expr_stmt|;
if|if
condition|(
operator|!
name|new_name
condition|)
name|new_name
operator|=
literal|""
expr_stmt|;
name|name
operator|=
name|g_strstrip
argument_list|(
name|g_strdup
argument_list|(
name|new_name
argument_list|)
argument_list|)
expr_stmt|;
if|if
condition|(
name|strlen
argument_list|(
name|name
argument_list|)
operator|&&
name|strcmp
argument_list|(
name|old_name
argument_list|,
name|name
argument_list|)
condition|)
block|{
name|guint
name|t
decl_stmt|;
name|g_object_get
argument_list|(
name|object
argument_list|,
literal|"time"
argument_list|,
operator|&
name|t
argument_list|,
name|NULL
argument_list|)
expr_stmt|;
if|if
condition|(
name|t
operator|>
literal|0
condition|)
name|g_object_set
argument_list|(
name|object
argument_list|,
literal|"time"
argument_list|,
literal|0
argument_list|,
name|NULL
argument_list|)
expr_stmt|;
comment|/*  set name after time so the object is reordered correctly  */
name|gimp_object_take_name
argument_list|(
name|object
argument_list|,
name|name
argument_list|)
expr_stmt|;
block|}
else|else
block|{
name|g_free
argument_list|(
name|name
argument_list|)
expr_stmt|;
name|name
operator|=
name|gimp_viewable_get_description
argument_list|(
name|renderer
operator|->
name|viewable
argument_list|,
name|NULL
argument_list|)
expr_stmt|;
name|gtk_list_store_set
argument_list|(
name|GTK_LIST_STORE
argument_list|(
name|tree_view
operator|->
name|model
argument_list|)
argument_list|,
operator|&
name|iter
argument_list|,
name|tree_view
operator|->
name|model_column_name
argument_list|,
name|name
argument_list|,
operator|-
literal|1
argument_list|)
expr_stmt|;
name|g_free
argument_list|(
name|name
argument_list|)
expr_stmt|;
block|}
name|g_object_unref
argument_list|(
name|renderer
argument_list|)
expr_stmt|;
block|}
name|gtk_tree_path_free
argument_list|(
name|path
argument_list|)
expr_stmt|;
block|}
end_function

begin_comment
comment|/*  public functions  */
end_comment

begin_function
name|GtkWidget
modifier|*
DECL|function|gimp_settings_editor_new (Gimp * gimp,GObject * config,GimpContainer * container)
name|gimp_settings_editor_new
parameter_list|(
name|Gimp
modifier|*
name|gimp
parameter_list|,
name|GObject
modifier|*
name|config
parameter_list|,
name|GimpContainer
modifier|*
name|container
parameter_list|)
block|{
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
name|GIMP_IS_CONFIG
argument_list|(
name|config
argument_list|)
argument_list|,
name|NULL
argument_list|)
expr_stmt|;
name|g_return_val_if_fail
argument_list|(
name|GIMP_IS_CONTAINER
argument_list|(
name|container
argument_list|)
argument_list|,
name|NULL
argument_list|)
expr_stmt|;
return|return
name|g_object_new
argument_list|(
name|GIMP_TYPE_SETTINGS_EDITOR
argument_list|,
literal|"gimp"
argument_list|,
name|gimp
argument_list|,
literal|"config"
argument_list|,
name|config
argument_list|,
literal|"container"
argument_list|,
name|container
argument_list|,
name|NULL
argument_list|)
return|;
block|}
end_function

end_unit

