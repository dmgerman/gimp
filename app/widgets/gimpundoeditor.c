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
file|"gimpundoeditor.h"
end_include

begin_include
include|#
directive|include
file|"libgimp/gimpintl.h"
end_include

begin_function_decl
specifier|static
name|void
name|gimp_undo_editor_class_init
parameter_list|(
name|GimpUndoEditorClass
modifier|*
name|klass
parameter_list|)
function_decl|;
end_function_decl

begin_function_decl
specifier|static
name|void
name|gimp_undo_editor_init
parameter_list|(
name|GimpUndoEditor
modifier|*
name|undo_editor
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
name|gimage
parameter_list|)
function_decl|;
end_function_decl

begin_function_decl
specifier|static
name|void
name|gimp_undo_editor_undo_clicked
parameter_list|(
name|GtkWidget
modifier|*
name|widget
parameter_list|,
name|GimpImageEditor
modifier|*
name|editor
parameter_list|)
function_decl|;
end_function_decl

begin_function_decl
specifier|static
name|void
name|gimp_undo_editor_redo_clicked
parameter_list|(
name|GtkWidget
modifier|*
name|widget
parameter_list|,
name|GimpImageEditor
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
name|gimage
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

begin_decl_stmt
DECL|variable|parent_class
specifier|static
name|GimpImageEditorClass
modifier|*
name|parent_class
init|=
name|NULL
decl_stmt|;
end_decl_stmt

begin_function
name|GType
DECL|function|gimp_undo_editor_get_type (void)
name|gimp_undo_editor_get_type
parameter_list|(
name|void
parameter_list|)
block|{
specifier|static
name|GType
name|editor_type
init|=
literal|0
decl_stmt|;
if|if
condition|(
operator|!
name|editor_type
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
name|GimpUndoEditorClass
argument_list|)
block|,
operator|(
name|GBaseInitFunc
operator|)
name|NULL
block|,
operator|(
name|GBaseFinalizeFunc
operator|)
name|NULL
block|,
operator|(
name|GClassInitFunc
operator|)
name|gimp_undo_editor_class_init
block|,
name|NULL
block|,
comment|/* class_finalize */
name|NULL
block|,
comment|/* class_data     */
sizeof|sizeof
argument_list|(
name|GimpUndoEditor
argument_list|)
block|,
literal|0
block|,
comment|/* n_preallocs    */
operator|(
name|GInstanceInitFunc
operator|)
name|gimp_undo_editor_init
block|,       }
decl_stmt|;
name|editor_type
operator|=
name|g_type_register_static
argument_list|(
name|GIMP_TYPE_IMAGE_EDITOR
argument_list|,
literal|"GimpUndoEditor"
argument_list|,
operator|&
name|editor_info
argument_list|,
literal|0
argument_list|)
expr_stmt|;
block|}
return|return
name|editor_type
return|;
block|}
end_function

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
name|GimpImageEditorClass
modifier|*
name|image_editor_class
decl_stmt|;
name|image_editor_class
operator|=
name|GIMP_IMAGE_EDITOR_CLASS
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
name|image_editor_class
operator|->
name|set_image
operator|=
name|gimp_undo_editor_set_image
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
block|{
name|undo_editor
operator|->
name|container
operator|=
name|NULL
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
name|GIMP_PREVIEW_SIZE_MEDIUM
argument_list|,
name|FALSE
argument_list|,
literal|3
argument_list|,
literal|3
argument_list|)
expr_stmt|;
name|gtk_box_pack_start
argument_list|(
name|GTK_BOX
argument_list|(
name|undo_editor
argument_list|)
argument_list|,
name|undo_editor
operator|->
name|view
argument_list|,
name|TRUE
argument_list|,
name|TRUE
argument_list|,
literal|0
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
literal|"select_item"
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
name|gimp_editor_add_button
argument_list|(
name|GIMP_EDITOR
argument_list|(
name|undo_editor
argument_list|)
argument_list|,
name|GTK_STOCK_UNDO
argument_list|,
name|_
argument_list|(
literal|"Undo"
argument_list|)
argument_list|,
name|NULL
argument_list|,
name|G_CALLBACK
argument_list|(
name|gimp_undo_editor_undo_clicked
argument_list|)
argument_list|,
name|NULL
argument_list|,
name|undo_editor
argument_list|)
expr_stmt|;
name|undo_editor
operator|->
name|redo_button
operator|=
name|gimp_editor_add_button
argument_list|(
name|GIMP_EDITOR
argument_list|(
name|undo_editor
argument_list|)
argument_list|,
name|GTK_STOCK_REDO
argument_list|,
name|_
argument_list|(
literal|"Redo"
argument_list|)
argument_list|,
name|NULL
argument_list|,
name|G_CALLBACK
argument_list|(
name|gimp_undo_editor_redo_clicked
argument_list|)
argument_list|,
name|NULL
argument_list|,
name|undo_editor
argument_list|)
expr_stmt|;
name|gtk_widget_set_sensitive
argument_list|(
name|GTK_WIDGET
argument_list|(
name|undo_editor
argument_list|)
argument_list|,
name|FALSE
argument_list|)
expr_stmt|;
block|}
end_function

begin_function
specifier|static
name|void
DECL|function|gimp_undo_editor_set_image (GimpImageEditor * image_editor,GimpImage * gimage)
name|gimp_undo_editor_set_image
parameter_list|(
name|GimpImageEditor
modifier|*
name|image_editor
parameter_list|,
name|GimpImage
modifier|*
name|gimage
parameter_list|)
block|{
name|GimpUndoEditor
modifier|*
name|editor
decl_stmt|;
name|editor
operator|=
name|GIMP_UNDO_EDITOR
argument_list|(
name|image_editor
argument_list|)
expr_stmt|;
if|if
condition|(
name|image_editor
operator|->
name|gimage
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
name|g_signal_handlers_disconnect_by_func
argument_list|(
name|image_editor
operator|->
name|gimage
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
name|gimage
argument_list|)
expr_stmt|;
if|if
condition|(
name|gimage
condition|)
block|{
name|GimpUndo
modifier|*
name|top_undo_item
decl_stmt|;
name|GimpUndo
modifier|*
name|top_redo_item
decl_stmt|;
name|GList
modifier|*
name|list
decl_stmt|;
comment|/*  create a container as model for the undo history list  */
name|editor
operator|->
name|container
operator|=
name|gimp_list_new
argument_list|(
name|GIMP_TYPE_UNDO
argument_list|,
name|GIMP_CONTAINER_POLICY_STRONG
argument_list|)
expr_stmt|;
name|editor
operator|->
name|base_item
operator|=
name|gimp_undo_new
argument_list|(
name|gimage
argument_list|,
name|GIMP_UNDO_GROUP_NONE
argument_list|,
name|_
argument_list|(
literal|"[ Base Image ]"
argument_list|)
argument_list|,
name|NULL
argument_list|,
literal|0
argument_list|,
name|FALSE
argument_list|,
name|NULL
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
name|gimage
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
name|gimage
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
comment|/*  ...finally, the first item is the special "base_item" which stands        *  for the image with no more undos available to pop        */
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
comment|/*  get the top item of both stacks  */
name|top_undo_item
operator|=
name|gimp_undo_stack_peek
argument_list|(
name|gimage
operator|->
name|undo_stack
argument_list|)
expr_stmt|;
name|top_redo_item
operator|=
name|gimp_undo_stack_peek
argument_list|(
name|gimage
operator|->
name|redo_stack
argument_list|)
expr_stmt|;
name|gtk_widget_set_sensitive
argument_list|(
name|editor
operator|->
name|undo_button
argument_list|,
name|top_undo_item
operator|!=
name|NULL
argument_list|)
expr_stmt|;
name|gtk_widget_set_sensitive
argument_list|(
name|editor
operator|->
name|redo_button
argument_list|,
name|top_redo_item
operator|!=
name|NULL
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
name|g_signal_connect
argument_list|(
name|gimage
argument_list|,
literal|"undo_event"
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

begin_comment
comment|/*  public functions  */
end_comment

begin_function
name|GtkWidget
modifier|*
DECL|function|gimp_undo_editor_new (GimpImage * gimage)
name|gimp_undo_editor_new
parameter_list|(
name|GimpImage
modifier|*
name|gimage
parameter_list|)
block|{
name|GimpUndoEditor
modifier|*
name|editor
decl_stmt|;
name|g_return_val_if_fail
argument_list|(
operator|!
name|gimage
operator|||
name|GIMP_IS_IMAGE
argument_list|(
name|gimage
argument_list|)
argument_list|,
name|NULL
argument_list|)
expr_stmt|;
name|editor
operator|=
name|g_object_new
argument_list|(
name|GIMP_TYPE_UNDO_EDITOR
argument_list|,
name|NULL
argument_list|)
expr_stmt|;
if|if
condition|(
name|gimage
condition|)
name|gimp_image_editor_set_image
argument_list|(
name|GIMP_IMAGE_EDITOR
argument_list|(
name|editor
argument_list|)
argument_list|,
name|gimage
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
DECL|function|gimp_undo_editor_undo_clicked (GtkWidget * widget,GimpImageEditor * editor)
name|gimp_undo_editor_undo_clicked
parameter_list|(
name|GtkWidget
modifier|*
name|widget
parameter_list|,
name|GimpImageEditor
modifier|*
name|editor
parameter_list|)
block|{
if|if
condition|(
name|editor
operator|->
name|gimage
condition|)
block|{
if|if
condition|(
name|gimp_image_undo
argument_list|(
name|editor
operator|->
name|gimage
argument_list|)
condition|)
name|gimp_image_flush
argument_list|(
name|editor
operator|->
name|gimage
argument_list|)
expr_stmt|;
block|}
block|}
end_function

begin_function
specifier|static
name|void
DECL|function|gimp_undo_editor_redo_clicked (GtkWidget * widget,GimpImageEditor * editor)
name|gimp_undo_editor_redo_clicked
parameter_list|(
name|GtkWidget
modifier|*
name|widget
parameter_list|,
name|GimpImageEditor
modifier|*
name|editor
parameter_list|)
block|{
if|if
condition|(
name|editor
operator|->
name|gimage
condition|)
block|{
if|if
condition|(
name|gimp_image_redo
argument_list|(
name|editor
operator|->
name|gimage
argument_list|)
condition|)
name|gimp_image_flush
argument_list|(
name|editor
operator|->
name|gimage
argument_list|)
expr_stmt|;
block|}
block|}
end_function

begin_function
specifier|static
name|void
DECL|function|gimp_undo_editor_undo_event (GimpImage * gimage,GimpUndoEvent event,GimpUndo * undo,GimpUndoEditor * editor)
name|gimp_undo_editor_undo_event
parameter_list|(
name|GimpImage
modifier|*
name|gimage
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
decl_stmt|;
name|GimpUndo
modifier|*
name|top_redo_item
decl_stmt|;
name|top_undo_item
operator|=
name|gimp_undo_stack_peek
argument_list|(
name|gimage
operator|->
name|undo_stack
argument_list|)
expr_stmt|;
name|top_redo_item
operator|=
name|gimp_undo_stack_peek
argument_list|(
name|gimage
operator|->
name|redo_stack
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
switch|switch
condition|(
name|event
condition|)
block|{
case|case
name|GIMP_UNDO_EVENT_UNDO_PUSHED
case|:
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
name|FALSE
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
name|TRUE
argument_list|)
expr_stmt|;
block|}
break|break;
case|case
name|GIMP_UNDO_EVENT_UNDO_FREE
case|:
name|gimp_image_editor_set_image
argument_list|(
name|GIMP_IMAGE_EDITOR
argument_list|(
name|editor
argument_list|)
argument_list|,
name|NULL
argument_list|)
expr_stmt|;
break|break;
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
name|gtk_widget_set_sensitive
argument_list|(
name|editor
operator|->
name|undo_button
argument_list|,
name|top_undo_item
operator|!=
name|NULL
argument_list|)
expr_stmt|;
name|gtk_widget_set_sensitive
argument_list|(
name|editor
operator|->
name|redo_button
argument_list|,
name|top_redo_item
operator|!=
name|NULL
argument_list|)
expr_stmt|;
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
name|gimage
decl_stmt|;
name|GimpUndo
modifier|*
name|top_undo_item
decl_stmt|;
name|GimpUndo
modifier|*
name|top_redo_item
decl_stmt|;
if|if
condition|(
operator|!
name|undo
condition|)
return|return;
name|gimage
operator|=
name|GIMP_IMAGE_EDITOR
argument_list|(
name|editor
argument_list|)
operator|->
name|gimage
expr_stmt|;
name|top_undo_item
operator|=
name|gimp_undo_stack_peek
argument_list|(
name|gimage
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
name|gimage
argument_list|)
expr_stmt|;
name|top_undo_item
operator|=
name|gimp_undo_stack_peek
argument_list|(
name|gimage
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
name|gimage
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
name|gimage
argument_list|)
expr_stmt|;
name|top_undo_item
operator|=
name|gimp_undo_stack_peek
argument_list|(
name|gimage
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
name|gimage
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
name|gimage
argument_list|)
expr_stmt|;
name|top_undo_item
operator|=
name|gimp_undo_stack_peek
argument_list|(
name|gimage
operator|->
name|undo_stack
argument_list|)
expr_stmt|;
block|}
block|}
name|gimp_image_flush
argument_list|(
name|gimage
argument_list|)
expr_stmt|;
name|top_redo_item
operator|=
name|gimp_undo_stack_peek
argument_list|(
name|gimage
operator|->
name|redo_stack
argument_list|)
expr_stmt|;
name|gtk_widget_set_sensitive
argument_list|(
name|editor
operator|->
name|undo_button
argument_list|,
name|top_undo_item
operator|!=
name|NULL
argument_list|)
expr_stmt|;
name|gtk_widget_set_sensitive
argument_list|(
name|editor
operator|->
name|redo_button
argument_list|,
name|top_redo_item
operator|!=
name|NULL
argument_list|)
expr_stmt|;
block|}
end_function

end_unit

