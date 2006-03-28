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
name|gint64
name|gimp_undo_stack_get_memsize
parameter_list|(
name|GimpObject
modifier|*
name|object
parameter_list|,
name|gint64
modifier|*
name|gui_size
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
name|GimpUndoMode
name|undo_mode
parameter_list|)
function_decl|;
end_function_decl

begin_expr_stmt
name|G_DEFINE_TYPE
argument_list|(
name|GimpUndoStack
argument_list|,
name|gimp_undo_stack
argument_list|,
name|GIMP_TYPE_UNDO
argument_list|)
expr_stmt|;
end_expr_stmt

begin_define
DECL|macro|parent_class
define|#
directive|define
name|parent_class
value|gimp_undo_stack_parent_class
end_define

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
init|=
name|G_OBJECT_CLASS
argument_list|(
name|klass
argument_list|)
decl_stmt|;
name|GimpObjectClass
modifier|*
name|gimp_object_class
init|=
name|GIMP_OBJECT_CLASS
argument_list|(
name|klass
argument_list|)
decl_stmt|;
name|GimpUndoClass
modifier|*
name|undo_class
init|=
name|GIMP_UNDO_CLASS
argument_list|(
name|klass
argument_list|)
decl_stmt|;
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
name|stack
operator|->
name|undos
operator|=
name|gimp_list_new
argument_list|(
name|GIMP_TYPE_UNDO
argument_list|,
name|FALSE
argument_list|)
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
init|=
name|GIMP_UNDO_STACK
argument_list|(
name|object
argument_list|)
decl_stmt|;
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
name|gint64
DECL|function|gimp_undo_stack_get_memsize (GimpObject * object,gint64 * gui_size)
name|gimp_undo_stack_get_memsize
parameter_list|(
name|GimpObject
modifier|*
name|object
parameter_list|,
name|gint64
modifier|*
name|gui_size
parameter_list|)
block|{
name|GimpUndoStack
modifier|*
name|stack
init|=
name|GIMP_UNDO_STACK
argument_list|(
name|object
argument_list|)
decl_stmt|;
name|gint64
name|memsize
init|=
literal|0
decl_stmt|;
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
argument_list|,
name|gui_size
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
argument_list|,
name|gui_size
argument_list|)
return|;
block|}
end_function

begin_function
specifier|static
name|void
DECL|function|gimp_undo_stack_pop (GimpUndo * undo,GimpUndoMode undo_mode,GimpUndoAccumulator * accum)
name|gimp_undo_stack_pop
parameter_list|(
name|GimpUndo
modifier|*
name|undo
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
init|=
name|GIMP_UNDO_STACK
argument_list|(
name|undo
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
init|=
name|list
operator|->
name|data
decl_stmt|;
name|gimp_undo_pop
argument_list|(
name|child
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
DECL|function|gimp_undo_stack_free (GimpUndo * undo,GimpUndoMode undo_mode)
name|gimp_undo_stack_free
parameter_list|(
name|GimpUndo
modifier|*
name|undo
parameter_list|,
name|GimpUndoMode
name|undo_mode
parameter_list|)
block|{
name|GimpUndoStack
modifier|*
name|stack
init|=
name|GIMP_UNDO_STACK
argument_list|(
name|undo
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
init|=
name|list
operator|->
name|data
decl_stmt|;
name|gimp_undo_free
argument_list|(
name|child
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
expr_stmt|;
block|}
end_function

begin_function
name|GimpUndoStack
modifier|*
DECL|function|gimp_undo_stack_new (GimpImage * image)
name|gimp_undo_stack_new
parameter_list|(
name|GimpImage
modifier|*
name|image
parameter_list|)
block|{
name|g_return_val_if_fail
argument_list|(
name|GIMP_IS_IMAGE
argument_list|(
name|image
argument_list|)
argument_list|,
name|NULL
argument_list|)
expr_stmt|;
return|return
name|g_object_new
argument_list|(
name|GIMP_TYPE_UNDO_STACK
argument_list|,
literal|"image"
argument_list|,
name|image
argument_list|,
name|NULL
argument_list|)
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
name|GimpUndo
modifier|*
name|undo
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
name|undo
operator|=
operator|(
name|GimpUndo
operator|*
operator|)
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
name|undo
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
name|GIMP_OBJECT
argument_list|(
name|undo
argument_list|)
argument_list|)
expr_stmt|;
name|gimp_undo_pop
argument_list|(
name|undo
argument_list|,
name|undo_mode
argument_list|,
name|accum
argument_list|)
expr_stmt|;
return|return
name|undo
return|;
block|}
return|return
name|NULL
return|;
block|}
end_function

begin_function
name|GimpUndo
modifier|*
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
name|GimpUndo
modifier|*
name|undo
decl_stmt|;
name|gint
name|n_children
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
name|undo
operator|=
operator|(
name|GimpUndo
operator|*
operator|)
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
name|undo
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
name|GIMP_OBJECT
argument_list|(
name|undo
argument_list|)
argument_list|)
expr_stmt|;
name|gimp_undo_free
argument_list|(
name|undo
argument_list|,
name|undo_mode
argument_list|)
expr_stmt|;
return|return
name|undo
return|;
block|}
return|return
name|NULL
return|;
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
name|gint
DECL|function|gimp_undo_stack_get_depth (GimpUndoStack * stack)
name|gimp_undo_stack_get_depth
parameter_list|(
name|GimpUndoStack
modifier|*
name|stack
parameter_list|)
block|{
name|g_return_val_if_fail
argument_list|(
name|GIMP_IS_UNDO_STACK
argument_list|(
name|stack
argument_list|)
argument_list|,
literal|0
argument_list|)
expr_stmt|;
return|return
name|gimp_container_num_children
argument_list|(
name|stack
operator|->
name|undos
argument_list|)
return|;
block|}
end_function

end_unit

