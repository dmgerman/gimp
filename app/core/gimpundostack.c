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
file|<glib-object.h>
end_include

begin_include
include|#
directive|include
file|"core-types.h"
end_include

begin_include
include|#
directive|include
file|"gimpimage.h"
end_include

begin_include
include|#
directive|include
file|"gimplist.h"
end_include

begin_include
include|#
directive|include
file|"gimpundo.h"
end_include

begin_include
include|#
directive|include
file|"gimpundostack.h"
end_include

begin_function_decl
specifier|static
name|void
name|gimp_undo_stack_class_init
parameter_list|(
name|GimpUndoStackClass
modifier|*
name|klass
parameter_list|)
function_decl|;
end_function_decl

begin_function_decl
specifier|static
name|void
name|gimp_undo_stack_init
parameter_list|(
name|GimpUndoStack
modifier|*
name|stack
parameter_list|)
function_decl|;
end_function_decl

begin_function_decl
specifier|static
name|void
name|gimp_undo_stack_finalize
parameter_list|(
name|GObject
modifier|*
name|object
parameter_list|)
function_decl|;
end_function_decl

begin_function_decl
specifier|static
name|gsize
name|gimp_undo_stack_get_memsize
parameter_list|(
name|GimpObject
modifier|*
name|object
parameter_list|)
function_decl|;
end_function_decl

begin_function_decl
specifier|static
name|void
name|gimp_undo_stack_pop
parameter_list|(
name|GimpUndo
modifier|*
name|undo
parameter_list|,
name|GimpImage
modifier|*
name|gimage
parameter_list|,
name|GimpUndoMode
name|undo_mode
parameter_list|,
name|GimpUndoAccumulator
modifier|*
name|accum
parameter_list|)
function_decl|;
end_function_decl

begin_function_decl
specifier|static
name|void
name|gimp_undo_stack_free
parameter_list|(
name|GimpUndo
modifier|*
name|undo
parameter_list|,
name|GimpImage
modifier|*
name|gimage
parameter_list|,
name|GimpUndoMode
name|undo_mode
parameter_list|)
function_decl|;
end_function_decl

begin_function_decl
specifier|static
name|void
name|gimp_undo_stack_add_callback
parameter_list|(
name|GimpContainer
modifier|*
name|container
parameter_list|,
name|GimpObject
modifier|*
name|object
parameter_list|,
name|gpointer
name|data
parameter_list|)
function_decl|;
end_function_decl

begin_function_decl
specifier|static
name|void
name|gimp_undo_stack_remove_callback
parameter_list|(
name|GimpContainer
modifier|*
name|container
parameter_list|,
name|GimpObject
modifier|*
name|object
parameter_list|,
name|gpointer
name|data
parameter_list|)
function_decl|;
end_function_decl

begin_decl_stmt
DECL|variable|parent_class
specifier|static
name|GimpUndoClass
modifier|*
name|parent_class
init|=
name|NULL
decl_stmt|;
end_decl_stmt

begin_function
name|GType
DECL|function|gimp_undo_stack_get_type (void)
name|gimp_undo_stack_get_type
parameter_list|(
name|void
parameter_list|)
block|{
specifier|static
name|GType
name|undo_stack_type
init|=
literal|0
decl_stmt|;
if|if
condition|(
operator|!
name|undo_stack_type
condition|)
block|{
specifier|static
specifier|const
name|GTypeInfo
name|undo_stack_info
init|=
block|{
sizeof|sizeof
argument_list|(
name|GimpUndoStackClass
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
name|gimp_undo_stack_class_init
block|,
name|NULL
block|,
comment|/* class_finalize */
name|NULL
block|,
comment|/* class_data     */
sizeof|sizeof
argument_list|(
name|GimpUndoStack
argument_list|)
block|,
literal|0
block|,
comment|/* n_preallocs    */
operator|(
name|GInstanceInitFunc
operator|)
name|gimp_undo_stack_init
block|,       }
decl_stmt|;
name|undo_stack_type
operator|=
name|g_type_register_static
argument_list|(
name|GIMP_TYPE_UNDO
argument_list|,
literal|"GimpUndoStack"
argument_list|,
operator|&
name|undo_stack_info
argument_list|,
literal|0
argument_list|)
expr_stmt|;
block|}
return|return
name|undo_stack_type
return|;
block|}
end_function

begin_function
specifier|static
name|void
DECL|function|gimp_undo_stack_class_init (GimpUndoStackClass * klass)
name|gimp_undo_stack_class_init
parameter_list|(
name|GimpUndoStackClass
modifier|*
name|klass
parameter_list|)
block|{
name|GObjectClass
modifier|*
name|object_class
decl_stmt|;
name|GimpObjectClass
modifier|*
name|gimp_object_class
decl_stmt|;
name|GimpUndoClass
modifier|*
name|undo_class
decl_stmt|;
name|object_class
operator|=
name|G_OBJECT_CLASS
argument_list|(
name|klass
argument_list|)
expr_stmt|;
name|gimp_object_class
operator|=
name|GIMP_OBJECT_CLASS
argument_list|(
name|klass
argument_list|)
expr_stmt|;
name|undo_class
operator|=
name|GIMP_UNDO_CLASS
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
name|finalize
operator|=
name|gimp_undo_stack_finalize
expr_stmt|;
name|gimp_object_class
operator|->
name|get_memsize
operator|=
name|gimp_undo_stack_get_memsize
expr_stmt|;
name|undo_class
operator|->
name|pop
operator|=
name|gimp_undo_stack_pop
expr_stmt|;
name|undo_class
operator|->
name|free
operator|=
name|gimp_undo_stack_free
expr_stmt|;
block|}
end_function

begin_function
specifier|static
name|void
DECL|function|gimp_undo_stack_init (GimpUndoStack * stack)
name|gimp_undo_stack_init
parameter_list|(
name|GimpUndoStack
modifier|*
name|stack
parameter_list|)
block|{
name|GimpContainer
modifier|*
name|undos
decl_stmt|;
name|undos
operator|=
name|gimp_list_new
argument_list|(
name|GIMP_TYPE_UNDO
argument_list|,
name|GIMP_CONTAINER_POLICY_STRONG
argument_list|)
expr_stmt|;
name|stack
operator|->
name|undos
operator|=
name|undos
expr_stmt|;
name|g_signal_connect
argument_list|(
name|undos
argument_list|,
literal|"add"
argument_list|,
name|G_CALLBACK
argument_list|(
name|gimp_undo_stack_add_callback
argument_list|)
argument_list|,
name|stack
argument_list|)
expr_stmt|;
name|g_signal_connect
argument_list|(
name|undos
argument_list|,
literal|"remove"
argument_list|,
name|G_CALLBACK
argument_list|(
name|gimp_undo_stack_remove_callback
argument_list|)
argument_list|,
name|stack
argument_list|)
expr_stmt|;
name|stack
operator|->
name|gimage
operator|=
name|NULL
expr_stmt|;
block|}
end_function

begin_function
specifier|static
name|void
DECL|function|gimp_undo_stack_finalize (GObject * object)
name|gimp_undo_stack_finalize
parameter_list|(
name|GObject
modifier|*
name|object
parameter_list|)
block|{
name|GimpUndoStack
modifier|*
name|stack
decl_stmt|;
name|stack
operator|=
name|GIMP_UNDO_STACK
argument_list|(
name|object
argument_list|)
expr_stmt|;
if|if
condition|(
name|stack
operator|->
name|undos
condition|)
block|{
name|g_object_unref
argument_list|(
name|stack
operator|->
name|undos
argument_list|)
expr_stmt|;
name|stack
operator|->
name|undos
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
name|gsize
DECL|function|gimp_undo_stack_get_memsize (GimpObject * object)
name|gimp_undo_stack_get_memsize
parameter_list|(
name|GimpObject
modifier|*
name|object
parameter_list|)
block|{
name|GimpUndoStack
modifier|*
name|stack
decl_stmt|;
name|gsize
name|memsize
init|=
literal|0
decl_stmt|;
name|stack
operator|=
name|GIMP_UNDO_STACK
argument_list|(
name|object
argument_list|)
expr_stmt|;
if|if
condition|(
name|stack
operator|->
name|undos
condition|)
name|memsize
operator|+=
name|gimp_object_get_memsize
argument_list|(
name|GIMP_OBJECT
argument_list|(
name|stack
operator|->
name|undos
argument_list|)
argument_list|)
expr_stmt|;
return|return
name|memsize
operator|+
name|GIMP_OBJECT_CLASS
argument_list|(
name|parent_class
argument_list|)
operator|->
name|get_memsize
argument_list|(
name|object
argument_list|)
return|;
block|}
end_function

begin_function
specifier|static
name|void
DECL|function|gimp_undo_stack_pop (GimpUndo * undo,GimpImage * gimage,GimpUndoMode undo_mode,GimpUndoAccumulator * accum)
name|gimp_undo_stack_pop
parameter_list|(
name|GimpUndo
modifier|*
name|undo
parameter_list|,
name|GimpImage
modifier|*
name|gimage
parameter_list|,
name|GimpUndoMode
name|undo_mode
parameter_list|,
name|GimpUndoAccumulator
modifier|*
name|accum
parameter_list|)
block|{
name|GimpUndoStack
modifier|*
name|stack
decl_stmt|;
name|GList
modifier|*
name|list
decl_stmt|;
name|stack
operator|=
name|GIMP_UNDO_STACK
argument_list|(
name|undo
argument_list|)
expr_stmt|;
for|for
control|(
name|list
operator|=
name|GIMP_LIST
argument_list|(
name|stack
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
name|GimpUndo
modifier|*
name|child
decl_stmt|;
name|child
operator|=
name|GIMP_UNDO
argument_list|(
name|list
operator|->
name|data
argument_list|)
expr_stmt|;
name|gimp_undo_pop
argument_list|(
name|child
argument_list|,
name|gimage
argument_list|,
name|undo_mode
argument_list|,
name|accum
argument_list|)
expr_stmt|;
block|}
block|}
end_function

begin_function
specifier|static
name|void
DECL|function|gimp_undo_stack_free (GimpUndo * undo,GimpImage * gimage,GimpUndoMode undo_mode)
name|gimp_undo_stack_free
parameter_list|(
name|GimpUndo
modifier|*
name|undo
parameter_list|,
name|GimpImage
modifier|*
name|gimage
parameter_list|,
name|GimpUndoMode
name|undo_mode
parameter_list|)
block|{
name|GimpUndoStack
modifier|*
name|stack
decl_stmt|;
name|GList
modifier|*
name|list
decl_stmt|;
name|stack
operator|=
name|GIMP_UNDO_STACK
argument_list|(
name|undo
argument_list|)
expr_stmt|;
for|for
control|(
name|list
operator|=
name|GIMP_LIST
argument_list|(
name|stack
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
name|GimpUndo
modifier|*
name|child
decl_stmt|;
name|child
operator|=
name|GIMP_UNDO
argument_list|(
name|list
operator|->
name|data
argument_list|)
expr_stmt|;
name|gimp_undo_free
argument_list|(
name|child
argument_list|,
name|gimage
argument_list|,
name|undo_mode
argument_list|)
expr_stmt|;
name|g_object_unref
argument_list|(
name|child
argument_list|)
expr_stmt|;
block|}
while|while
condition|(
name|GIMP_LIST
argument_list|(
name|stack
operator|->
name|undos
argument_list|)
operator|->
name|list
condition|)
name|gimp_container_remove
argument_list|(
name|GIMP_CONTAINER
argument_list|(
name|stack
operator|->
name|undos
argument_list|)
argument_list|,
name|GIMP_OBJECT
argument_list|(
name|GIMP_LIST
argument_list|(
name|stack
operator|->
name|undos
argument_list|)
operator|->
name|list
operator|->
name|data
argument_list|)
argument_list|)
expr_stmt|;
block|}
end_function

begin_function
name|GimpUndoStack
modifier|*
DECL|function|gimp_undo_stack_new (GimpImage * gimage)
name|gimp_undo_stack_new
parameter_list|(
name|GimpImage
modifier|*
name|gimage
parameter_list|)
block|{
name|GimpUndoStack
modifier|*
name|stack
decl_stmt|;
name|g_return_val_if_fail
argument_list|(
name|GIMP_IS_IMAGE
argument_list|(
name|gimage
argument_list|)
argument_list|,
name|NULL
argument_list|)
expr_stmt|;
name|stack
operator|=
name|GIMP_UNDO_STACK
argument_list|(
name|g_object_new
argument_list|(
name|GIMP_TYPE_UNDO_STACK
argument_list|,
name|NULL
argument_list|)
argument_list|)
expr_stmt|;
name|stack
operator|->
name|gimage
operator|=
name|gimage
expr_stmt|;
return|return
name|stack
return|;
block|}
end_function

begin_function
name|void
DECL|function|gimp_undo_stack_push_undo (GimpUndoStack * stack,GimpUndo * undo)
name|gimp_undo_stack_push_undo
parameter_list|(
name|GimpUndoStack
modifier|*
name|stack
parameter_list|,
name|GimpUndo
modifier|*
name|undo
parameter_list|)
block|{
name|g_return_if_fail
argument_list|(
name|GIMP_IS_UNDO_STACK
argument_list|(
name|stack
argument_list|)
argument_list|)
expr_stmt|;
name|g_return_if_fail
argument_list|(
name|GIMP_IS_UNDO
argument_list|(
name|undo
argument_list|)
argument_list|)
expr_stmt|;
name|gimp_container_add
argument_list|(
name|GIMP_CONTAINER
argument_list|(
name|stack
operator|->
name|undos
argument_list|)
argument_list|,
name|GIMP_OBJECT
argument_list|(
name|undo
argument_list|)
argument_list|)
expr_stmt|;
block|}
end_function

begin_function
name|GimpUndo
modifier|*
DECL|function|gimp_undo_stack_pop_undo (GimpUndoStack * stack,GimpUndoMode undo_mode,GimpUndoAccumulator * accum)
name|gimp_undo_stack_pop_undo
parameter_list|(
name|GimpUndoStack
modifier|*
name|stack
parameter_list|,
name|GimpUndoMode
name|undo_mode
parameter_list|,
name|GimpUndoAccumulator
modifier|*
name|accum
parameter_list|)
block|{
name|GimpObject
modifier|*
name|object
decl_stmt|;
name|g_return_val_if_fail
argument_list|(
name|GIMP_IS_UNDO_STACK
argument_list|(
name|stack
argument_list|)
argument_list|,
name|NULL
argument_list|)
expr_stmt|;
name|g_return_val_if_fail
argument_list|(
name|accum
operator|!=
name|NULL
argument_list|,
name|NULL
argument_list|)
expr_stmt|;
name|object
operator|=
name|gimp_container_get_child_by_index
argument_list|(
name|GIMP_CONTAINER
argument_list|(
name|stack
operator|->
name|undos
argument_list|)
argument_list|,
literal|0
argument_list|)
expr_stmt|;
if|if
condition|(
name|object
condition|)
block|{
name|gimp_container_remove
argument_list|(
name|GIMP_CONTAINER
argument_list|(
name|stack
operator|->
name|undos
argument_list|)
argument_list|,
name|object
argument_list|)
expr_stmt|;
name|gimp_undo_pop
argument_list|(
name|GIMP_UNDO
argument_list|(
name|object
argument_list|)
argument_list|,
name|stack
operator|->
name|gimage
argument_list|,
name|undo_mode
argument_list|,
name|accum
argument_list|)
expr_stmt|;
return|return
name|GIMP_UNDO
argument_list|(
name|object
argument_list|)
return|;
block|}
return|return
name|NULL
return|;
block|}
end_function

begin_function
name|void
DECL|function|gimp_undo_stack_free_bottom (GimpUndoStack * stack,GimpUndoMode undo_mode)
name|gimp_undo_stack_free_bottom
parameter_list|(
name|GimpUndoStack
modifier|*
name|stack
parameter_list|,
name|GimpUndoMode
name|undo_mode
parameter_list|)
block|{
name|GimpObject
modifier|*
name|object
decl_stmt|;
name|gint
name|n_children
decl_stmt|;
name|g_return_if_fail
argument_list|(
name|GIMP_IS_UNDO_STACK
argument_list|(
name|stack
argument_list|)
argument_list|)
expr_stmt|;
name|n_children
operator|=
name|gimp_container_num_children
argument_list|(
name|GIMP_CONTAINER
argument_list|(
name|stack
operator|->
name|undos
argument_list|)
argument_list|)
expr_stmt|;
name|object
operator|=
name|gimp_container_get_child_by_index
argument_list|(
name|GIMP_CONTAINER
argument_list|(
name|stack
operator|->
name|undos
argument_list|)
argument_list|,
name|n_children
operator|-
literal|1
argument_list|)
expr_stmt|;
if|if
condition|(
name|object
condition|)
block|{
name|gimp_container_remove
argument_list|(
name|GIMP_CONTAINER
argument_list|(
name|stack
operator|->
name|undos
argument_list|)
argument_list|,
name|object
argument_list|)
expr_stmt|;
name|gimp_undo_free
argument_list|(
name|GIMP_UNDO
argument_list|(
name|object
argument_list|)
argument_list|,
name|stack
operator|->
name|gimage
argument_list|,
name|undo_mode
argument_list|)
expr_stmt|;
name|g_object_unref
argument_list|(
name|object
argument_list|)
expr_stmt|;
block|}
block|}
end_function

begin_function
name|GimpUndo
modifier|*
DECL|function|gimp_undo_stack_peek (GimpUndoStack * stack)
name|gimp_undo_stack_peek
parameter_list|(
name|GimpUndoStack
modifier|*
name|stack
parameter_list|)
block|{
name|GimpObject
modifier|*
name|object
decl_stmt|;
name|g_return_val_if_fail
argument_list|(
name|GIMP_IS_UNDO_STACK
argument_list|(
name|stack
argument_list|)
argument_list|,
name|NULL
argument_list|)
expr_stmt|;
name|object
operator|=
name|gimp_container_get_child_by_index
argument_list|(
name|GIMP_CONTAINER
argument_list|(
name|stack
operator|->
name|undos
argument_list|)
argument_list|,
literal|0
argument_list|)
expr_stmt|;
return|return
operator|(
name|object
condition|?
name|GIMP_UNDO
argument_list|(
name|object
argument_list|)
else|:
name|NULL
operator|)
return|;
block|}
end_function

begin_function
specifier|static
name|void
DECL|function|gimp_undo_stack_add_callback (GimpContainer * container,GimpObject * object,gpointer data)
name|gimp_undo_stack_add_callback
parameter_list|(
name|GimpContainer
modifier|*
name|container
parameter_list|,
name|GimpObject
modifier|*
name|object
parameter_list|,
name|gpointer
name|data
parameter_list|)
block|{
name|GimpUndo
modifier|*
name|undo
decl_stmt|;
name|GimpUndo
modifier|*
name|stack
decl_stmt|;
name|undo
operator|=
name|GIMP_UNDO
argument_list|(
name|object
argument_list|)
expr_stmt|;
name|stack
operator|=
name|GIMP_UNDO
argument_list|(
name|data
argument_list|)
expr_stmt|;
block|}
end_function

begin_function
specifier|static
name|void
DECL|function|gimp_undo_stack_remove_callback (GimpContainer * container,GimpObject * object,gpointer data)
name|gimp_undo_stack_remove_callback
parameter_list|(
name|GimpContainer
modifier|*
name|container
parameter_list|,
name|GimpObject
modifier|*
name|object
parameter_list|,
name|gpointer
name|data
parameter_list|)
block|{
name|GimpUndo
modifier|*
name|undo
decl_stmt|;
name|GimpUndo
modifier|*
name|stack
decl_stmt|;
name|undo
operator|=
name|GIMP_UNDO
argument_list|(
name|object
argument_list|)
expr_stmt|;
name|stack
operator|=
name|GIMP_UNDO
argument_list|(
name|data
argument_list|)
expr_stmt|;
block|}
end_function

end_unit

