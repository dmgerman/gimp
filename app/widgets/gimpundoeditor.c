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
file|"widgets-types.h"
end_include

begin_include
include|#
directive|include
file|"config/gimpcoreconfig.h"
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
file|"core/gimpimage.h"
end_include

begin_include
include|#
directive|include
file|"core/gimpimage-undo.h"
end_include

begin_include
include|#
directive|include
file|"core/gimpundostack.h"
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
file|"gimpundoeditor.h"
end_include

begin_include
include|#
directive|include
file|"gimp-intl.h"
end_include

begin_enum
enum|enum
DECL|enum|__anon28e771b20103
block|{
DECL|enumerator|PROP_0
name|PROP_0
block|,
DECL|enumerator|PROP_VIEW_SIZE
name|PROP_VIEW_SIZE
block|}
enum|;
end_enum

begin_function_decl
specifier|static
name|void
name|gimp_undo_editor_docked_iface_init
parameter_list|(
name|GimpDockedInterface
modifier|*
name|iface
parameter_list|)
function_decl|;
end_function_decl

begin_function_decl
specifier|static
name|GObject
modifier|*
name|gimp_undo_editor_constructor
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
name|gimp_undo_editor_set_property
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
name|gimp_undo_editor_set_image
parameter_list|(
name|GimpImageEditor
modifier|*
name|editor
parameter_list|,
name|GimpImage
modifier|*
name|image
parameter_list|)
function_decl|;
end_function_decl

begin_function_decl
specifier|static
name|void
name|gimp_undo_editor_set_context
parameter_list|(
name|GimpDocked
modifier|*
name|docked
parameter_list|,
name|GimpContext
modifier|*
name|context
parameter_list|)
function_decl|;
end_function_decl

begin_function_decl
specifier|static
name|void
name|gimp_undo_editor_fill
parameter_list|(
name|GimpUndoEditor
modifier|*
name|editor
parameter_list|)
function_decl|;
end_function_decl

begin_function_decl
specifier|static
name|void
name|gimp_undo_editor_clear
parameter_list|(
name|GimpUndoEditor
modifier|*
name|editor
parameter_list|)
function_decl|;
end_function_decl

begin_function_decl
specifier|static
name|void
name|gimp_undo_editor_undo_event
parameter_list|(
name|GimpImage
modifier|*
name|image
parameter_list|,
name|GimpUndoEvent
name|event
parameter_list|,
name|GimpUndo
modifier|*
name|undo
parameter_list|,
name|GimpUndoEditor
modifier|*
name|editor
parameter_list|)
function_decl|;
end_function_decl

begin_function_decl
specifier|static
name|void
name|gimp_undo_editor_select_item
parameter_list|(
name|GimpContainerView
modifier|*
name|view
parameter_list|,
name|GimpUndo
modifier|*
name|undo
parameter_list|,
name|gpointer
name|insert_data
parameter_list|,
name|GimpUndoEditor
modifier|*
name|editor
parameter_list|)
function_decl|;
end_function_decl

begin_macro
name|G_DEFINE_TYPE_WITH_CODE
argument_list|(
argument|GimpUndoEditor
argument_list|,
argument|gimp_undo_editor
argument_list|,
argument|GIMP_TYPE_IMAGE_EDITOR
argument_list|,
argument|G_IMPLEMENT_INTERFACE (GIMP_TYPE_DOCKED,                                                 gimp_undo_editor_docked_iface_init)
argument_list|)
end_macro

begin_define
DECL|macro|parent_class
define|#
directive|define
name|parent_class
value|gimp_undo_editor_parent_class
end_define

begin_decl_stmt
specifier|static
name|GimpDockedInterface
modifier|*
name|parent_docked_iface
init|=
name|NULL
decl_stmt|;
end_decl_stmt

begin_function
specifier|static
name|void
DECL|function|gimp_undo_editor_class_init (GimpUndoEditorClass * klass)
name|gimp_undo_editor_class_init
parameter_list|(
name|GimpUndoEditorClass
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
name|GimpImageEditorClass
modifier|*
name|image_editor_class
init|=
name|GIMP_IMAGE_EDITOR_CLASS
argument_list|(
name|klass
argument_list|)
decl_stmt|;
name|object_class
operator|->
name|constructor
operator|=
name|gimp_undo_editor_constructor
expr_stmt|;
name|object_class
operator|->
name|set_property
operator|=
name|gimp_undo_editor_set_property
expr_stmt|;
name|image_editor_class
operator|->
name|set_image
operator|=
name|gimp_undo_editor_set_image
expr_stmt|;
name|g_object_class_install_property
argument_list|(
name|object_class
argument_list|,
name|PROP_VIEW_SIZE
argument_list|,
name|g_param_spec_enum
argument_list|(
literal|"view-size"
argument_list|,
name|NULL
argument_list|,
name|NULL
argument_list|,
name|GIMP_TYPE_VIEW_SIZE
argument_list|,
name|GIMP_VIEW_SIZE_LARGE
argument_list|,
name|GIMP_PARAM_WRITABLE
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
DECL|function|gimp_undo_editor_docked_iface_init (GimpDockedInterface * iface)
name|gimp_undo_editor_docked_iface_init
parameter_list|(
name|GimpDockedInterface
modifier|*
name|iface
parameter_list|)
block|{
name|parent_docked_iface
operator|=
name|g_type_interface_peek_parent
argument_list|(
name|iface
argument_list|)
expr_stmt|;
if|if
condition|(
operator|!
name|parent_docked_iface
condition|)
name|parent_docked_iface
operator|=
name|g_type_default_interface_peek
argument_list|(
name|GIMP_TYPE_DOCKED
argument_list|)
expr_stmt|;
name|iface
operator|->
name|set_context
operator|=
name|gimp_undo_editor_set_context
expr_stmt|;
block|}
end_function

begin_function
specifier|static
name|void
DECL|function|gimp_undo_editor_init (GimpUndoEditor * undo_editor)
name|gimp_undo_editor_init
parameter_list|(
name|GimpUndoEditor
modifier|*
name|undo_editor
parameter_list|)
block|{ }
end_function

begin_function
specifier|static
name|GObject
modifier|*
DECL|function|gimp_undo_editor_constructor (GType type,guint n_params,GObjectConstructParam * params)
name|gimp_undo_editor_constructor
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
name|GimpUndoEditor
modifier|*
name|undo_editor
decl_stmt|;
name|GObject
modifier|*
name|object
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
name|undo_editor
operator|=
name|GIMP_UNDO_EDITOR
argument_list|(
name|object
argument_list|)
expr_stmt|;
name|undo_editor
operator|->
name|view
operator|=
name|gimp_container_tree_view_new
argument_list|(
name|NULL
argument_list|,
name|NULL
argument_list|,
name|undo_editor
operator|->
name|view_size
argument_list|,
literal|1
argument_list|)
expr_stmt|;
name|gtk_container_add
argument_list|(
name|GTK_CONTAINER
argument_list|(
name|undo_editor
argument_list|)
argument_list|,
name|undo_editor
operator|->
name|view
argument_list|)
expr_stmt|;
name|gtk_widget_show
argument_list|(
name|undo_editor
operator|->
name|view
argument_list|)
expr_stmt|;
name|g_signal_connect
argument_list|(
name|undo_editor
operator|->
name|view
argument_list|,
literal|"select-item"
argument_list|,
name|G_CALLBACK
argument_list|(
name|gimp_undo_editor_select_item
argument_list|)
argument_list|,
name|undo_editor
argument_list|)
expr_stmt|;
name|undo_editor
operator|->
name|undo_button
operator|=
name|gimp_editor_add_action_button
argument_list|(
name|GIMP_EDITOR
argument_list|(
name|undo_editor
argument_list|)
argument_list|,
literal|"edit"
argument_list|,
literal|"edit-undo"
argument_list|,
name|NULL
argument_list|)
expr_stmt|;
name|undo_editor
operator|->
name|redo_button
operator|=
name|gimp_editor_add_action_button
argument_list|(
name|GIMP_EDITOR
argument_list|(
name|undo_editor
argument_list|)
argument_list|,
literal|"edit"
argument_list|,
literal|"edit-redo"
argument_list|,
name|NULL
argument_list|)
expr_stmt|;
name|undo_editor
operator|->
name|clear_button
operator|=
name|gimp_editor_add_action_button
argument_list|(
name|GIMP_EDITOR
argument_list|(
name|undo_editor
argument_list|)
argument_list|,
literal|"edit"
argument_list|,
literal|"edit-undo-clear"
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
DECL|function|gimp_undo_editor_set_property (GObject * object,guint property_id,const GValue * value,GParamSpec * pspec)
name|gimp_undo_editor_set_property
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
name|GimpUndoEditor
modifier|*
name|undo_editor
init|=
name|GIMP_UNDO_EDITOR
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
name|PROP_VIEW_SIZE
case|:
name|undo_editor
operator|->
name|view_size
operator|=
name|g_value_get_enum
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
DECL|function|gimp_undo_editor_set_image (GimpImageEditor * image_editor,GimpImage * image)
name|gimp_undo_editor_set_image
parameter_list|(
name|GimpImageEditor
modifier|*
name|image_editor
parameter_list|,
name|GimpImage
modifier|*
name|image
parameter_list|)
block|{
name|GimpUndoEditor
modifier|*
name|editor
init|=
name|GIMP_UNDO_EDITOR
argument_list|(
name|image_editor
argument_list|)
decl_stmt|;
if|if
condition|(
name|image_editor
operator|->
name|image
condition|)
block|{
name|gimp_undo_editor_clear
argument_list|(
name|editor
argument_list|)
expr_stmt|;
name|g_signal_handlers_disconnect_by_func
argument_list|(
name|image_editor
operator|->
name|image
argument_list|,
name|gimp_undo_editor_undo_event
argument_list|,
name|editor
argument_list|)
expr_stmt|;
block|}
name|GIMP_IMAGE_EDITOR_CLASS
argument_list|(
name|parent_class
argument_list|)
operator|->
name|set_image
argument_list|(
name|image_editor
argument_list|,
name|image
argument_list|)
expr_stmt|;
if|if
condition|(
name|image_editor
operator|->
name|image
condition|)
block|{
if|if
condition|(
name|gimp_image_undo_is_enabled
argument_list|(
name|image_editor
operator|->
name|image
argument_list|)
condition|)
name|gimp_undo_editor_fill
argument_list|(
name|editor
argument_list|)
expr_stmt|;
name|g_signal_connect
argument_list|(
name|image_editor
operator|->
name|image
argument_list|,
literal|"undo-event"
argument_list|,
name|G_CALLBACK
argument_list|(
name|gimp_undo_editor_undo_event
argument_list|)
argument_list|,
name|editor
argument_list|)
expr_stmt|;
block|}
block|}
end_function

begin_function
specifier|static
name|void
DECL|function|gimp_undo_editor_set_context (GimpDocked * docked,GimpContext * context)
name|gimp_undo_editor_set_context
parameter_list|(
name|GimpDocked
modifier|*
name|docked
parameter_list|,
name|GimpContext
modifier|*
name|context
parameter_list|)
block|{
name|GimpUndoEditor
modifier|*
name|editor
init|=
name|GIMP_UNDO_EDITOR
argument_list|(
name|docked
argument_list|)
decl_stmt|;
name|parent_docked_iface
operator|->
name|set_context
argument_list|(
name|docked
argument_list|,
name|context
argument_list|)
expr_stmt|;
if|if
condition|(
name|editor
operator|->
name|context
condition|)
name|g_object_unref
argument_list|(
name|editor
operator|->
name|context
argument_list|)
expr_stmt|;
name|editor
operator|->
name|context
operator|=
name|context
expr_stmt|;
if|if
condition|(
name|editor
operator|->
name|context
condition|)
name|g_object_ref
argument_list|(
name|editor
operator|->
name|context
argument_list|)
expr_stmt|;
name|gimp_container_view_set_context
argument_list|(
name|GIMP_CONTAINER_VIEW
argument_list|(
name|editor
operator|->
name|view
argument_list|)
argument_list|,
name|context
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
DECL|function|gimp_undo_editor_new (GimpCoreConfig * config,GimpMenuFactory * menu_factory)
name|gimp_undo_editor_new
parameter_list|(
name|GimpCoreConfig
modifier|*
name|config
parameter_list|,
name|GimpMenuFactory
modifier|*
name|menu_factory
parameter_list|)
block|{
name|g_return_val_if_fail
argument_list|(
name|GIMP_IS_CORE_CONFIG
argument_list|(
name|config
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
return|return
name|g_object_new
argument_list|(
name|GIMP_TYPE_UNDO_EDITOR
argument_list|,
literal|"menu-factory"
argument_list|,
name|menu_factory
argument_list|,
literal|"menu-identifier"
argument_list|,
literal|"<Undo>"
argument_list|,
literal|"ui-path"
argument_list|,
literal|"/undo-popup"
argument_list|,
literal|"view-size"
argument_list|,
name|config
operator|->
name|undo_preview_size
argument_list|,
name|NULL
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
DECL|function|gimp_undo_editor_fill (GimpUndoEditor * editor)
name|gimp_undo_editor_fill
parameter_list|(
name|GimpUndoEditor
modifier|*
name|editor
parameter_list|)
block|{
name|GimpImage
modifier|*
name|image
decl_stmt|;
name|GimpUndo
modifier|*
name|top_undo_item
decl_stmt|;
name|GList
modifier|*
name|list
decl_stmt|;
name|image
operator|=
name|GIMP_IMAGE_EDITOR
argument_list|(
name|editor
argument_list|)
operator|->
name|image
expr_stmt|;
comment|/*  create a container as model for the undo history list  */
name|editor
operator|->
name|container
operator|=
name|gimp_list_new
argument_list|(
name|GIMP_TYPE_UNDO
argument_list|,
name|FALSE
argument_list|)
expr_stmt|;
name|editor
operator|->
name|base_item
operator|=
name|g_object_new
argument_list|(
name|GIMP_TYPE_UNDO
argument_list|,
literal|"image"
argument_list|,
name|image
argument_list|,
literal|"name"
argument_list|,
name|_
argument_list|(
literal|"[ Base Image ]"
argument_list|)
argument_list|,
name|NULL
argument_list|)
expr_stmt|;
comment|/*  the list prepends its items, so first add the redo items...  */
for|for
control|(
name|list
operator|=
name|GIMP_LIST
argument_list|(
name|image
operator|->
name|redo_stack
operator|->
name|undos
argument_list|)
operator|->
name|list
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
name|gimp_container_add
argument_list|(
name|editor
operator|->
name|container
argument_list|,
name|GIMP_OBJECT
argument_list|(
name|list
operator|->
name|data
argument_list|)
argument_list|)
expr_stmt|;
block|}
comment|/*  ...reverse the list so the redo items are in ascending order...  */
name|gimp_list_reverse
argument_list|(
name|GIMP_LIST
argument_list|(
name|editor
operator|->
name|container
argument_list|)
argument_list|)
expr_stmt|;
comment|/*  ...then add the undo items in descending order...  */
for|for
control|(
name|list
operator|=
name|GIMP_LIST
argument_list|(
name|image
operator|->
name|undo_stack
operator|->
name|undos
argument_list|)
operator|->
name|list
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
comment|/*  Don't add the topmost item if it is an open undo group,        *  it will be added upon closing of the group.        */
if|if
condition|(
name|list
operator|->
name|prev
operator|||
operator|!
name|GIMP_IS_UNDO_STACK
argument_list|(
name|list
operator|->
name|data
argument_list|)
operator|||
name|image
operator|->
name|pushing_undo_group
operator|==
name|GIMP_UNDO_GROUP_NONE
condition|)
block|{
name|gimp_container_add
argument_list|(
name|editor
operator|->
name|container
argument_list|,
name|GIMP_OBJECT
argument_list|(
name|list
operator|->
name|data
argument_list|)
argument_list|)
expr_stmt|;
block|}
block|}
comment|/*  ...finally, the first item is the special "base_item" which stands    *  for the image with no more undos available to pop    */
name|gimp_container_add
argument_list|(
name|editor
operator|->
name|container
argument_list|,
name|GIMP_OBJECT
argument_list|(
name|editor
operator|->
name|base_item
argument_list|)
argument_list|)
expr_stmt|;
comment|/*  display the container  */
name|gimp_container_view_set_container
argument_list|(
name|GIMP_CONTAINER_VIEW
argument_list|(
name|editor
operator|->
name|view
argument_list|)
argument_list|,
name|editor
operator|->
name|container
argument_list|)
expr_stmt|;
name|top_undo_item
operator|=
name|gimp_undo_stack_peek
argument_list|(
name|image
operator|->
name|undo_stack
argument_list|)
expr_stmt|;
name|g_signal_handlers_block_by_func
argument_list|(
name|editor
operator|->
name|view
argument_list|,
name|gimp_undo_editor_select_item
argument_list|,
name|editor
argument_list|)
expr_stmt|;
comment|/*  select the current state of the image  */
if|if
condition|(
name|top_undo_item
condition|)
block|{
name|gimp_container_view_select_item
argument_list|(
name|GIMP_CONTAINER_VIEW
argument_list|(
name|editor
operator|->
name|view
argument_list|)
argument_list|,
name|GIMP_VIEWABLE
argument_list|(
name|top_undo_item
argument_list|)
argument_list|)
expr_stmt|;
name|gimp_undo_create_preview
argument_list|(
name|top_undo_item
argument_list|,
name|editor
operator|->
name|context
argument_list|,
name|FALSE
argument_list|)
expr_stmt|;
block|}
else|else
block|{
name|gimp_container_view_select_item
argument_list|(
name|GIMP_CONTAINER_VIEW
argument_list|(
name|editor
operator|->
name|view
argument_list|)
argument_list|,
name|GIMP_VIEWABLE
argument_list|(
name|editor
operator|->
name|base_item
argument_list|)
argument_list|)
expr_stmt|;
name|gimp_undo_create_preview
argument_list|(
name|editor
operator|->
name|base_item
argument_list|,
name|editor
operator|->
name|context
argument_list|,
name|TRUE
argument_list|)
expr_stmt|;
block|}
name|g_signal_handlers_unblock_by_func
argument_list|(
name|editor
operator|->
name|view
argument_list|,
name|gimp_undo_editor_select_item
argument_list|,
name|editor
argument_list|)
expr_stmt|;
block|}
end_function

begin_function
specifier|static
name|void
DECL|function|gimp_undo_editor_clear (GimpUndoEditor * editor)
name|gimp_undo_editor_clear
parameter_list|(
name|GimpUndoEditor
modifier|*
name|editor
parameter_list|)
block|{
if|if
condition|(
name|editor
operator|->
name|container
condition|)
block|{
name|gimp_container_view_set_container
argument_list|(
name|GIMP_CONTAINER_VIEW
argument_list|(
name|editor
operator|->
name|view
argument_list|)
argument_list|,
name|NULL
argument_list|)
expr_stmt|;
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
if|if
condition|(
name|editor
operator|->
name|base_item
condition|)
block|{
name|g_object_unref
argument_list|(
name|editor
operator|->
name|base_item
argument_list|)
expr_stmt|;
name|editor
operator|->
name|base_item
operator|=
name|NULL
expr_stmt|;
block|}
block|}
end_function

begin_function
specifier|static
name|void
DECL|function|gimp_undo_editor_undo_event (GimpImage * image,GimpUndoEvent event,GimpUndo * undo,GimpUndoEditor * editor)
name|gimp_undo_editor_undo_event
parameter_list|(
name|GimpImage
modifier|*
name|image
parameter_list|,
name|GimpUndoEvent
name|event
parameter_list|,
name|GimpUndo
modifier|*
name|undo
parameter_list|,
name|GimpUndoEditor
modifier|*
name|editor
parameter_list|)
block|{
name|GimpUndo
modifier|*
name|top_undo_item
init|=
name|gimp_undo_stack_peek
argument_list|(
name|image
operator|->
name|undo_stack
argument_list|)
decl_stmt|;
switch|switch
condition|(
name|event
condition|)
block|{
case|case
name|GIMP_UNDO_EVENT_UNDO_PUSHED
case|:
name|g_signal_handlers_block_by_func
argument_list|(
name|editor
operator|->
name|view
argument_list|,
name|gimp_undo_editor_select_item
argument_list|,
name|editor
argument_list|)
expr_stmt|;
name|gimp_container_insert
argument_list|(
name|editor
operator|->
name|container
argument_list|,
name|GIMP_OBJECT
argument_list|(
name|undo
argument_list|)
argument_list|,
operator|-
literal|1
argument_list|)
expr_stmt|;
name|gimp_container_view_select_item
argument_list|(
name|GIMP_CONTAINER_VIEW
argument_list|(
name|editor
operator|->
name|view
argument_list|)
argument_list|,
name|GIMP_VIEWABLE
argument_list|(
name|undo
argument_list|)
argument_list|)
expr_stmt|;
name|gimp_undo_create_preview
argument_list|(
name|undo
argument_list|,
name|editor
operator|->
name|context
argument_list|,
name|FALSE
argument_list|)
expr_stmt|;
name|g_signal_handlers_unblock_by_func
argument_list|(
name|editor
operator|->
name|view
argument_list|,
name|gimp_undo_editor_select_item
argument_list|,
name|editor
argument_list|)
expr_stmt|;
break|break;
case|case
name|GIMP_UNDO_EVENT_UNDO_EXPIRED
case|:
case|case
name|GIMP_UNDO_EVENT_REDO_EXPIRED
case|:
name|gimp_container_remove
argument_list|(
name|editor
operator|->
name|container
argument_list|,
name|GIMP_OBJECT
argument_list|(
name|undo
argument_list|)
argument_list|)
expr_stmt|;
break|break;
case|case
name|GIMP_UNDO_EVENT_UNDO
case|:
case|case
name|GIMP_UNDO_EVENT_REDO
case|:
name|g_signal_handlers_block_by_func
argument_list|(
name|editor
operator|->
name|view
argument_list|,
name|gimp_undo_editor_select_item
argument_list|,
name|editor
argument_list|)
expr_stmt|;
if|if
condition|(
name|top_undo_item
condition|)
block|{
name|gimp_container_view_select_item
argument_list|(
name|GIMP_CONTAINER_VIEW
argument_list|(
name|editor
operator|->
name|view
argument_list|)
argument_list|,
name|GIMP_VIEWABLE
argument_list|(
name|top_undo_item
argument_list|)
argument_list|)
expr_stmt|;
name|gimp_undo_create_preview
argument_list|(
name|top_undo_item
argument_list|,
name|editor
operator|->
name|context
argument_list|,
name|FALSE
argument_list|)
expr_stmt|;
block|}
else|else
block|{
name|gimp_container_view_select_item
argument_list|(
name|GIMP_CONTAINER_VIEW
argument_list|(
name|editor
operator|->
name|view
argument_list|)
argument_list|,
name|GIMP_VIEWABLE
argument_list|(
name|editor
operator|->
name|base_item
argument_list|)
argument_list|)
expr_stmt|;
name|gimp_undo_create_preview
argument_list|(
name|editor
operator|->
name|base_item
argument_list|,
name|editor
operator|->
name|context
argument_list|,
name|TRUE
argument_list|)
expr_stmt|;
block|}
name|g_signal_handlers_unblock_by_func
argument_list|(
name|editor
operator|->
name|view
argument_list|,
name|gimp_undo_editor_select_item
argument_list|,
name|editor
argument_list|)
expr_stmt|;
break|break;
case|case
name|GIMP_UNDO_EVENT_UNDO_FREE
case|:
if|if
condition|(
name|gimp_image_undo_is_enabled
argument_list|(
name|image
argument_list|)
condition|)
name|gimp_undo_editor_clear
argument_list|(
name|editor
argument_list|)
expr_stmt|;
break|break;
case|case
name|GIMP_UNDO_EVENT_UNDO_FREEZE
case|:
name|gimp_undo_editor_clear
argument_list|(
name|editor
argument_list|)
expr_stmt|;
break|break;
case|case
name|GIMP_UNDO_EVENT_UNDO_THAW
case|:
name|gimp_undo_editor_fill
argument_list|(
name|editor
argument_list|)
expr_stmt|;
break|break;
block|}
block|}
end_function

begin_function
specifier|static
name|void
DECL|function|gimp_undo_editor_select_item (GimpContainerView * view,GimpUndo * undo,gpointer insert_data,GimpUndoEditor * editor)
name|gimp_undo_editor_select_item
parameter_list|(
name|GimpContainerView
modifier|*
name|view
parameter_list|,
name|GimpUndo
modifier|*
name|undo
parameter_list|,
name|gpointer
name|insert_data
parameter_list|,
name|GimpUndoEditor
modifier|*
name|editor
parameter_list|)
block|{
name|GimpImage
modifier|*
name|image
decl_stmt|;
name|GimpUndo
modifier|*
name|top_undo_item
decl_stmt|;
if|if
condition|(
operator|!
name|undo
condition|)
return|return;
name|image
operator|=
name|GIMP_IMAGE_EDITOR
argument_list|(
name|editor
argument_list|)
operator|->
name|image
expr_stmt|;
name|top_undo_item
operator|=
name|gimp_undo_stack_peek
argument_list|(
name|image
operator|->
name|undo_stack
argument_list|)
expr_stmt|;
if|if
condition|(
name|undo
operator|==
name|editor
operator|->
name|base_item
condition|)
block|{
comment|/*  the base_item was selected, pop all available undo items        */
while|while
condition|(
name|top_undo_item
operator|!=
name|NULL
condition|)
block|{
name|gimp_image_undo
argument_list|(
name|image
argument_list|)
expr_stmt|;
name|top_undo_item
operator|=
name|gimp_undo_stack_peek
argument_list|(
name|image
operator|->
name|undo_stack
argument_list|)
expr_stmt|;
block|}
block|}
elseif|else
if|if
condition|(
name|gimp_container_have
argument_list|(
name|image
operator|->
name|undo_stack
operator|->
name|undos
argument_list|,
name|GIMP_OBJECT
argument_list|(
name|undo
argument_list|)
argument_list|)
condition|)
block|{
comment|/*  the selected item is on the undo stack, pop undos until it        *  is on top of the undo stack        */
while|while
condition|(
name|top_undo_item
operator|!=
name|undo
condition|)
block|{
name|gimp_image_undo
argument_list|(
name|image
argument_list|)
expr_stmt|;
name|top_undo_item
operator|=
name|gimp_undo_stack_peek
argument_list|(
name|image
operator|->
name|undo_stack
argument_list|)
expr_stmt|;
block|}
block|}
elseif|else
if|if
condition|(
name|gimp_container_have
argument_list|(
name|image
operator|->
name|redo_stack
operator|->
name|undos
argument_list|,
name|GIMP_OBJECT
argument_list|(
name|undo
argument_list|)
argument_list|)
condition|)
block|{
comment|/*  the selected item is on the redo stack, pop redos until it        *  is on top of the undo stack        */
while|while
condition|(
name|top_undo_item
operator|!=
name|undo
condition|)
block|{
name|gimp_image_redo
argument_list|(
name|image
argument_list|)
expr_stmt|;
name|top_undo_item
operator|=
name|gimp_undo_stack_peek
argument_list|(
name|image
operator|->
name|undo_stack
argument_list|)
expr_stmt|;
block|}
block|}
name|gimp_image_flush
argument_list|(
name|image
argument_list|)
expr_stmt|;
block|}
end_function

end_unit

