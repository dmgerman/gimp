begin_unit|revision:0.9.5;language:C;cregit-version:0.0.1
begin_comment
comment|/* GIMP - The GNU Image Manipulation Program  * Copyright (C) 1995 Spencer Kimball and Peter Mattis  *  * This program is free software; you can redistribute it and/or modify  * it under the terms of the GNU General Public License as published by  * the Free Software Foundation; either version 2 of the License, or  * (at your option) any later version.  *  * This program is distributed in the hope that it will be useful,  * but WITHOUT ANY WARRANTY; without even the implied warranty of  * MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the  * GNU General Public License for more details.  *  * You should have received a copy of the GNU General Public License  * along with this program; if not, write to the Free Software  * Foundation, Inc., 59 Temple Place - Suite 330, Boston, MA 02111-1307, USA.  */
end_comment

begin_include
include|#
directive|include
file|"config.h"
end_include

begin_include
include|#
directive|include
file|<gegl.h>
end_include

begin_include
include|#
directive|include
file|"core-types.h"
end_include

begin_include
include|#
directive|include
file|"config/gimpcoreconfig.h"
end_include

begin_include
include|#
directive|include
file|"gimp.h"
end_include

begin_include
include|#
directive|include
file|"gimp-utils.h"
end_include

begin_include
include|#
directive|include
file|"gimpdrawableundo.h"
end_include

begin_include
include|#
directive|include
file|"gimpimage.h"
end_include

begin_include
include|#
directive|include
file|"gimpimage-undo.h"
end_include

begin_include
include|#
directive|include
file|"gimpitem.h"
end_include

begin_include
include|#
directive|include
file|"gimplist.h"
end_include

begin_include
include|#
directive|include
file|"gimpundostack.h"
end_include

begin_comment
comment|/*  local function prototypes  */
end_comment

begin_function_decl
specifier|static
name|void
name|gimp_image_undo_pop_stack
parameter_list|(
name|GimpImage
modifier|*
name|image
parameter_list|,
name|GimpUndoStack
modifier|*
name|undo_stack
parameter_list|,
name|GimpUndoStack
modifier|*
name|redo_stack
parameter_list|,
name|GimpUndoMode
name|undo_mode
parameter_list|)
function_decl|;
end_function_decl

begin_function_decl
specifier|static
name|void
name|gimp_image_undo_free_space
parameter_list|(
name|GimpImage
modifier|*
name|image
parameter_list|)
function_decl|;
end_function_decl

begin_function_decl
specifier|static
name|void
name|gimp_image_undo_free_redo
parameter_list|(
name|GimpImage
modifier|*
name|image
parameter_list|)
function_decl|;
end_function_decl

begin_function_decl
specifier|static
name|GimpDirtyMask
name|gimp_image_undo_dirty_from_type
parameter_list|(
name|GimpUndoType
name|undo_type
parameter_list|)
function_decl|;
end_function_decl

begin_comment
comment|/*  public functions  */
end_comment

begin_function
name|gboolean
DECL|function|gimp_image_undo (GimpImage * image)
name|gimp_image_undo
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
name|FALSE
argument_list|)
expr_stmt|;
name|g_return_val_if_fail
argument_list|(
name|image
operator|->
name|pushing_undo_group
operator|==
name|GIMP_UNDO_GROUP_NONE
argument_list|,
name|FALSE
argument_list|)
expr_stmt|;
name|gimp_image_undo_pop_stack
argument_list|(
name|image
argument_list|,
name|image
operator|->
name|undo_stack
argument_list|,
name|image
operator|->
name|redo_stack
argument_list|,
name|GIMP_UNDO_MODE_UNDO
argument_list|)
expr_stmt|;
return|return
name|TRUE
return|;
block|}
end_function

begin_comment
comment|/*  * this function continues to undo as long as it only sees certain  * undo types, in particular visibility changes.  */
end_comment

begin_function
name|gboolean
DECL|function|gimp_image_strong_undo (GimpImage * image)
name|gimp_image_strong_undo
parameter_list|(
name|GimpImage
modifier|*
name|image
parameter_list|)
block|{
name|GimpUndo
modifier|*
name|undo
decl_stmt|;
name|g_return_val_if_fail
argument_list|(
name|GIMP_IS_IMAGE
argument_list|(
name|image
argument_list|)
argument_list|,
name|FALSE
argument_list|)
expr_stmt|;
name|g_return_val_if_fail
argument_list|(
name|image
operator|->
name|pushing_undo_group
operator|==
name|GIMP_UNDO_GROUP_NONE
argument_list|,
name|FALSE
argument_list|)
expr_stmt|;
name|undo
operator|=
name|gimp_undo_stack_peek
argument_list|(
name|image
operator|->
name|undo_stack
argument_list|)
expr_stmt|;
name|gimp_image_undo
argument_list|(
name|image
argument_list|)
expr_stmt|;
while|while
condition|(
name|gimp_undo_is_weak
argument_list|(
name|undo
argument_list|)
condition|)
block|{
name|undo
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
name|gimp_undo_is_weak
argument_list|(
name|undo
argument_list|)
condition|)
name|gimp_image_undo
argument_list|(
name|image
argument_list|)
expr_stmt|;
block|}
return|return
name|TRUE
return|;
block|}
end_function

begin_function
name|gboolean
DECL|function|gimp_image_redo (GimpImage * image)
name|gimp_image_redo
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
name|FALSE
argument_list|)
expr_stmt|;
name|g_return_val_if_fail
argument_list|(
name|image
operator|->
name|pushing_undo_group
operator|==
name|GIMP_UNDO_GROUP_NONE
argument_list|,
name|FALSE
argument_list|)
expr_stmt|;
name|gimp_image_undo_pop_stack
argument_list|(
name|image
argument_list|,
name|image
operator|->
name|redo_stack
argument_list|,
name|image
operator|->
name|undo_stack
argument_list|,
name|GIMP_UNDO_MODE_REDO
argument_list|)
expr_stmt|;
return|return
name|TRUE
return|;
block|}
end_function

begin_comment
comment|/*  * this function continues to redo as long as it only sees certain  * undo types, in particular visibility changes.  Note that the  * order of events is set up to make it exactly reverse  * gimp_image_strong_undo().  */
end_comment

begin_function
name|gboolean
DECL|function|gimp_image_strong_redo (GimpImage * image)
name|gimp_image_strong_redo
parameter_list|(
name|GimpImage
modifier|*
name|image
parameter_list|)
block|{
name|GimpUndo
modifier|*
name|undo
decl_stmt|;
name|g_return_val_if_fail
argument_list|(
name|GIMP_IS_IMAGE
argument_list|(
name|image
argument_list|)
argument_list|,
name|FALSE
argument_list|)
expr_stmt|;
name|g_return_val_if_fail
argument_list|(
name|image
operator|->
name|pushing_undo_group
operator|==
name|GIMP_UNDO_GROUP_NONE
argument_list|,
name|FALSE
argument_list|)
expr_stmt|;
name|undo
operator|=
name|gimp_undo_stack_peek
argument_list|(
name|image
operator|->
name|redo_stack
argument_list|)
expr_stmt|;
name|gimp_image_redo
argument_list|(
name|image
argument_list|)
expr_stmt|;
while|while
condition|(
name|gimp_undo_is_weak
argument_list|(
name|undo
argument_list|)
condition|)
block|{
name|undo
operator|=
name|gimp_undo_stack_peek
argument_list|(
name|image
operator|->
name|redo_stack
argument_list|)
expr_stmt|;
if|if
condition|(
name|gimp_undo_is_weak
argument_list|(
name|undo
argument_list|)
condition|)
name|gimp_image_redo
argument_list|(
name|image
argument_list|)
expr_stmt|;
block|}
return|return
name|TRUE
return|;
block|}
end_function

begin_function
name|void
DECL|function|gimp_image_undo_free (GimpImage * image)
name|gimp_image_undo_free
parameter_list|(
name|GimpImage
modifier|*
name|image
parameter_list|)
block|{
name|g_return_if_fail
argument_list|(
name|GIMP_IS_IMAGE
argument_list|(
name|image
argument_list|)
argument_list|)
expr_stmt|;
comment|/*  Emit the UNDO_FREE event before actually freeing everything    *  so the views can properly detach from the undo items    */
name|gimp_image_undo_event
argument_list|(
name|image
argument_list|,
name|GIMP_UNDO_EVENT_UNDO_FREE
argument_list|,
name|NULL
argument_list|)
expr_stmt|;
name|gimp_undo_free
argument_list|(
name|GIMP_UNDO
argument_list|(
name|image
operator|->
name|undo_stack
argument_list|)
argument_list|,
name|GIMP_UNDO_MODE_UNDO
argument_list|)
expr_stmt|;
name|gimp_undo_free
argument_list|(
name|GIMP_UNDO
argument_list|(
name|image
operator|->
name|redo_stack
argument_list|)
argument_list|,
name|GIMP_UNDO_MODE_REDO
argument_list|)
expr_stmt|;
comment|/* If the image was dirty, but could become clean by redo-ing    * some actions, then it should now become 'infinitely' dirty.    * This is because we've just nuked the actions that would allow    * the image to become clean again.    */
if|if
condition|(
name|image
operator|->
name|dirty
operator|<
literal|0
condition|)
name|image
operator|->
name|dirty
operator|=
literal|100000
expr_stmt|;
comment|/* The same applies to the case where the image would become clean    * due to undo actions, but since user can't undo without an undo    * stack, that's not so much a problem.    */
block|}
end_function

begin_function
name|gboolean
DECL|function|gimp_image_undo_group_start (GimpImage * image,GimpUndoType undo_type,const gchar * name)
name|gimp_image_undo_group_start
parameter_list|(
name|GimpImage
modifier|*
name|image
parameter_list|,
name|GimpUndoType
name|undo_type
parameter_list|,
specifier|const
name|gchar
modifier|*
name|name
parameter_list|)
block|{
name|GimpUndoStack
modifier|*
name|undo_group
decl_stmt|;
name|GimpDirtyMask
name|dirty_mask
decl_stmt|;
name|g_return_val_if_fail
argument_list|(
name|GIMP_IS_IMAGE
argument_list|(
name|image
argument_list|)
argument_list|,
name|FALSE
argument_list|)
expr_stmt|;
name|g_return_val_if_fail
argument_list|(
name|undo_type
operator|>
name|GIMP_UNDO_GROUP_FIRST
operator|&&
name|undo_type
operator|<=
name|GIMP_UNDO_GROUP_LAST
argument_list|,
name|FALSE
argument_list|)
expr_stmt|;
if|if
condition|(
operator|!
name|name
condition|)
name|name
operator|=
name|gimp_undo_type_to_name
argument_list|(
name|undo_type
argument_list|)
expr_stmt|;
name|dirty_mask
operator|=
name|gimp_image_undo_dirty_from_type
argument_list|(
name|undo_type
argument_list|)
expr_stmt|;
comment|/* Notify listeners that the image will be modified */
if|if
condition|(
name|image
operator|->
name|group_count
operator|==
literal|0
operator|&&
name|dirty_mask
operator|!=
name|GIMP_DIRTY_NONE
condition|)
name|gimp_image_dirty
argument_list|(
name|image
argument_list|,
name|dirty_mask
argument_list|)
expr_stmt|;
if|if
condition|(
name|image
operator|->
name|undo_freeze_count
operator|>
literal|0
condition|)
return|return
name|FALSE
return|;
name|image
operator|->
name|group_count
operator|++
expr_stmt|;
comment|/*  If we're already in a group...ignore  */
if|if
condition|(
name|image
operator|->
name|group_count
operator|>
literal|1
condition|)
return|return
name|TRUE
return|;
comment|/*  nuke the redo stack  */
name|gimp_image_undo_free_redo
argument_list|(
name|image
argument_list|)
expr_stmt|;
name|undo_group
operator|=
name|gimp_undo_stack_new
argument_list|(
name|image
argument_list|)
expr_stmt|;
name|gimp_object_set_name
argument_list|(
name|GIMP_OBJECT
argument_list|(
name|undo_group
argument_list|)
argument_list|,
name|name
argument_list|)
expr_stmt|;
name|GIMP_UNDO
argument_list|(
name|undo_group
argument_list|)
operator|->
name|undo_type
operator|=
name|undo_type
expr_stmt|;
name|GIMP_UNDO
argument_list|(
name|undo_group
argument_list|)
operator|->
name|dirty_mask
operator|=
name|dirty_mask
expr_stmt|;
name|gimp_undo_stack_push_undo
argument_list|(
name|image
operator|->
name|undo_stack
argument_list|,
name|GIMP_UNDO
argument_list|(
name|undo_group
argument_list|)
argument_list|)
expr_stmt|;
name|image
operator|->
name|pushing_undo_group
operator|=
name|undo_type
expr_stmt|;
return|return
name|TRUE
return|;
block|}
end_function

begin_function
name|gboolean
DECL|function|gimp_image_undo_group_end (GimpImage * image)
name|gimp_image_undo_group_end
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
name|FALSE
argument_list|)
expr_stmt|;
if|if
condition|(
name|image
operator|->
name|undo_freeze_count
operator|>
literal|0
condition|)
return|return
name|FALSE
return|;
name|g_return_val_if_fail
argument_list|(
name|image
operator|->
name|group_count
operator|>
literal|0
argument_list|,
name|FALSE
argument_list|)
expr_stmt|;
name|image
operator|->
name|group_count
operator|--
expr_stmt|;
if|if
condition|(
name|image
operator|->
name|group_count
operator|==
literal|0
condition|)
block|{
name|image
operator|->
name|pushing_undo_group
operator|=
name|GIMP_UNDO_GROUP_NONE
expr_stmt|;
comment|/* Do it here, since undo_push doesn't emit this event while in        * the middle of a group        */
name|gimp_image_undo_event
argument_list|(
name|image
argument_list|,
name|GIMP_UNDO_EVENT_UNDO_PUSHED
argument_list|,
name|gimp_undo_stack_peek
argument_list|(
name|image
operator|->
name|undo_stack
argument_list|)
argument_list|)
expr_stmt|;
name|gimp_image_undo_free_space
argument_list|(
name|image
argument_list|)
expr_stmt|;
block|}
return|return
name|TRUE
return|;
block|}
end_function

begin_function
name|GimpUndo
modifier|*
DECL|function|gimp_image_undo_push (GimpImage * image,GType object_type,GimpUndoType undo_type,const gchar * name,GimpDirtyMask dirty_mask,...)
name|gimp_image_undo_push
parameter_list|(
name|GimpImage
modifier|*
name|image
parameter_list|,
name|GType
name|object_type
parameter_list|,
name|GimpUndoType
name|undo_type
parameter_list|,
specifier|const
name|gchar
modifier|*
name|name
parameter_list|,
name|GimpDirtyMask
name|dirty_mask
parameter_list|,
modifier|...
parameter_list|)
block|{
name|GParameter
modifier|*
name|params
init|=
name|NULL
decl_stmt|;
name|gint
name|n_params
init|=
literal|0
decl_stmt|;
name|va_list
name|args
decl_stmt|;
name|GimpUndo
modifier|*
name|undo
decl_stmt|;
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
name|g_return_val_if_fail
argument_list|(
name|g_type_is_a
argument_list|(
name|object_type
argument_list|,
name|GIMP_TYPE_UNDO
argument_list|)
argument_list|,
name|NULL
argument_list|)
expr_stmt|;
name|g_return_val_if_fail
argument_list|(
name|undo_type
operator|>
name|GIMP_UNDO_GROUP_LAST
argument_list|,
name|NULL
argument_list|)
expr_stmt|;
comment|/* Does this undo dirty the image?  If so, we always want to mark    * image dirty, even if we can't actually push the undo.    */
if|if
condition|(
name|dirty_mask
operator|!=
name|GIMP_DIRTY_NONE
condition|)
name|gimp_image_dirty
argument_list|(
name|image
argument_list|,
name|dirty_mask
argument_list|)
expr_stmt|;
if|if
condition|(
name|image
operator|->
name|undo_freeze_count
operator|>
literal|0
condition|)
return|return
name|NULL
return|;
if|if
condition|(
operator|!
name|name
condition|)
name|name
operator|=
name|gimp_undo_type_to_name
argument_list|(
name|undo_type
argument_list|)
expr_stmt|;
name|params
operator|=
name|gimp_parameters_append
argument_list|(
name|object_type
argument_list|,
name|params
argument_list|,
operator|&
name|n_params
argument_list|,
literal|"name"
argument_list|,
name|name
argument_list|,
literal|"image"
argument_list|,
name|image
argument_list|,
literal|"undo-type"
argument_list|,
name|undo_type
argument_list|,
literal|"dirty-mask"
argument_list|,
name|dirty_mask
argument_list|,
name|NULL
argument_list|)
expr_stmt|;
name|va_start
argument_list|(
name|args
argument_list|,
name|dirty_mask
argument_list|)
expr_stmt|;
name|params
operator|=
name|gimp_parameters_append_valist
argument_list|(
name|object_type
argument_list|,
name|params
argument_list|,
operator|&
name|n_params
argument_list|,
name|args
argument_list|)
expr_stmt|;
name|va_end
argument_list|(
name|args
argument_list|)
expr_stmt|;
name|undo
operator|=
name|g_object_newv
argument_list|(
name|object_type
argument_list|,
name|n_params
argument_list|,
name|params
argument_list|)
expr_stmt|;
name|gimp_parameters_free
argument_list|(
name|params
argument_list|,
name|n_params
argument_list|)
expr_stmt|;
comment|/*  nuke the redo stack  */
name|gimp_image_undo_free_redo
argument_list|(
name|image
argument_list|)
expr_stmt|;
if|if
condition|(
name|image
operator|->
name|pushing_undo_group
operator|==
name|GIMP_UNDO_GROUP_NONE
condition|)
block|{
name|gimp_undo_stack_push_undo
argument_list|(
name|image
operator|->
name|undo_stack
argument_list|,
name|undo
argument_list|)
expr_stmt|;
name|gimp_image_undo_event
argument_list|(
name|image
argument_list|,
name|GIMP_UNDO_EVENT_UNDO_PUSHED
argument_list|,
name|undo
argument_list|)
expr_stmt|;
name|gimp_image_undo_free_space
argument_list|(
name|image
argument_list|)
expr_stmt|;
comment|/*  freeing undo space may have freed the newly pushed undo  */
if|if
condition|(
name|gimp_undo_stack_peek
argument_list|(
name|image
operator|->
name|undo_stack
argument_list|)
operator|==
name|undo
condition|)
return|return
name|undo
return|;
block|}
else|else
block|{
name|GimpUndoStack
modifier|*
name|undo_group
decl_stmt|;
name|undo_group
operator|=
name|GIMP_UNDO_STACK
argument_list|(
name|gimp_undo_stack_peek
argument_list|(
name|image
operator|->
name|undo_stack
argument_list|)
argument_list|)
expr_stmt|;
name|gimp_undo_stack_push_undo
argument_list|(
name|undo_group
argument_list|,
name|undo
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
DECL|function|gimp_image_undo_can_compress (GimpImage * image,GType object_type,GimpUndoType undo_type)
name|gimp_image_undo_can_compress
parameter_list|(
name|GimpImage
modifier|*
name|image
parameter_list|,
name|GType
name|object_type
parameter_list|,
name|GimpUndoType
name|undo_type
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
if|if
condition|(
name|image
operator|->
name|dirty
operator|!=
literal|0
operator|&&
operator|!
name|gimp_undo_stack_peek
argument_list|(
name|image
operator|->
name|redo_stack
argument_list|)
condition|)
block|{
name|GimpUndo
modifier|*
name|undo
init|=
name|gimp_undo_stack_peek
argument_list|(
name|image
operator|->
name|undo_stack
argument_list|)
decl_stmt|;
if|if
condition|(
name|undo
operator|&&
name|undo
operator|->
name|undo_type
operator|==
name|undo_type
operator|&&
name|g_type_is_a
argument_list|(
name|G_TYPE_FROM_INSTANCE
argument_list|(
name|undo
argument_list|)
argument_list|,
name|object_type
argument_list|)
condition|)
block|{
return|return
name|undo
return|;
block|}
block|}
return|return
name|NULL
return|;
block|}
end_function

begin_function
name|GimpUndo
modifier|*
DECL|function|gimp_image_undo_get_fadeable (GimpImage * image)
name|gimp_image_undo_get_fadeable
parameter_list|(
name|GimpImage
modifier|*
name|image
parameter_list|)
block|{
name|GimpUndo
modifier|*
name|undo
decl_stmt|;
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
name|undo
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
name|GIMP_IS_UNDO_STACK
argument_list|(
name|undo
argument_list|)
operator|&&
name|undo
operator|->
name|undo_type
operator|==
name|GIMP_UNDO_GROUP_PAINT
condition|)
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
if|if
condition|(
name|gimp_undo_stack_get_depth
argument_list|(
name|stack
argument_list|)
operator|==
literal|2
condition|)
block|{
name|undo
operator|=
name|gimp_undo_stack_peek
argument_list|(
name|stack
argument_list|)
expr_stmt|;
block|}
block|}
if|if
condition|(
name|GIMP_IS_DRAWABLE_UNDO
argument_list|(
name|undo
argument_list|)
condition|)
return|return
name|undo
return|;
return|return
name|NULL
return|;
block|}
end_function

begin_comment
comment|/*  private functions  */
end_comment

begin_function
specifier|static
name|void
DECL|function|gimp_image_undo_pop_stack (GimpImage * image,GimpUndoStack * undo_stack,GimpUndoStack * redo_stack,GimpUndoMode undo_mode)
name|gimp_image_undo_pop_stack
parameter_list|(
name|GimpImage
modifier|*
name|image
parameter_list|,
name|GimpUndoStack
modifier|*
name|undo_stack
parameter_list|,
name|GimpUndoStack
modifier|*
name|redo_stack
parameter_list|,
name|GimpUndoMode
name|undo_mode
parameter_list|)
block|{
name|GimpUndo
modifier|*
name|undo
decl_stmt|;
name|GimpUndoAccumulator
name|accum
init|=
block|{
literal|0
block|, }
decl_stmt|;
name|g_object_freeze_notify
argument_list|(
name|G_OBJECT
argument_list|(
name|image
argument_list|)
argument_list|)
expr_stmt|;
name|undo
operator|=
name|gimp_undo_stack_pop_undo
argument_list|(
name|undo_stack
argument_list|,
name|undo_mode
argument_list|,
operator|&
name|accum
argument_list|)
expr_stmt|;
if|if
condition|(
name|undo
condition|)
block|{
if|if
condition|(
name|GIMP_IS_UNDO_STACK
argument_list|(
name|undo
argument_list|)
condition|)
name|gimp_list_reverse
argument_list|(
name|GIMP_LIST
argument_list|(
name|GIMP_UNDO_STACK
argument_list|(
name|undo
argument_list|)
operator|->
name|undos
argument_list|)
argument_list|)
expr_stmt|;
name|gimp_undo_stack_push_undo
argument_list|(
name|redo_stack
argument_list|,
name|undo
argument_list|)
expr_stmt|;
if|if
condition|(
name|accum
operator|.
name|mode_changed
condition|)
name|gimp_image_mode_changed
argument_list|(
name|image
argument_list|)
expr_stmt|;
if|if
condition|(
name|accum
operator|.
name|size_changed
condition|)
name|gimp_image_size_changed_detailed
argument_list|(
name|image
argument_list|,
name|accum
operator|.
name|previous_origin_x
argument_list|,
name|accum
operator|.
name|previous_origin_y
argument_list|,
name|accum
operator|.
name|previous_width
argument_list|,
name|accum
operator|.
name|previous_height
argument_list|)
expr_stmt|;
if|if
condition|(
name|accum
operator|.
name|resolution_changed
condition|)
name|gimp_image_resolution_changed
argument_list|(
name|image
argument_list|)
expr_stmt|;
if|if
condition|(
name|accum
operator|.
name|unit_changed
condition|)
name|gimp_image_unit_changed
argument_list|(
name|image
argument_list|)
expr_stmt|;
if|if
condition|(
name|accum
operator|.
name|quick_mask_changed
condition|)
name|gimp_image_quick_mask_changed
argument_list|(
name|image
argument_list|)
expr_stmt|;
if|if
condition|(
name|accum
operator|.
name|alpha_changed
condition|)
name|gimp_image_alpha_changed
argument_list|(
name|image
argument_list|)
expr_stmt|;
comment|/* let others know that we just popped an action */
name|gimp_image_undo_event
argument_list|(
name|image
argument_list|,
operator|(
name|undo_mode
operator|==
name|GIMP_UNDO_MODE_UNDO
operator|)
condition|?
name|GIMP_UNDO_EVENT_UNDO
else|:
name|GIMP_UNDO_EVENT_REDO
argument_list|,
name|undo
argument_list|)
expr_stmt|;
block|}
name|g_object_thaw_notify
argument_list|(
name|G_OBJECT
argument_list|(
name|image
argument_list|)
argument_list|)
expr_stmt|;
block|}
end_function

begin_function
specifier|static
name|void
DECL|function|gimp_image_undo_free_space (GimpImage * image)
name|gimp_image_undo_free_space
parameter_list|(
name|GimpImage
modifier|*
name|image
parameter_list|)
block|{
name|GimpContainer
modifier|*
name|container
decl_stmt|;
name|gint
name|min_undo_levels
decl_stmt|;
name|gint
name|max_undo_levels
decl_stmt|;
name|gint64
name|undo_size
decl_stmt|;
name|container
operator|=
name|image
operator|->
name|undo_stack
operator|->
name|undos
expr_stmt|;
name|min_undo_levels
operator|=
name|image
operator|->
name|gimp
operator|->
name|config
operator|->
name|levels_of_undo
expr_stmt|;
name|max_undo_levels
operator|=
literal|1024
expr_stmt|;
comment|/* FIXME */
name|undo_size
operator|=
name|image
operator|->
name|gimp
operator|->
name|config
operator|->
name|undo_size
expr_stmt|;
ifdef|#
directive|ifdef
name|DEBUG_IMAGE_UNDO
name|g_printerr
argument_list|(
literal|"undo_steps: %d    undo_bytes: %ld\n"
argument_list|,
name|gimp_container_num_children
argument_list|(
name|container
argument_list|)
argument_list|,
operator|(
name|glong
operator|)
name|gimp_object_get_memsize
argument_list|(
name|GIMP_OBJECT
argument_list|(
name|container
argument_list|)
argument_list|,
name|NULL
argument_list|)
argument_list|)
expr_stmt|;
endif|#
directive|endif
comment|/*  keep at least min_undo_levels undo steps  */
if|if
condition|(
name|gimp_container_num_children
argument_list|(
name|container
argument_list|)
operator|<=
name|min_undo_levels
condition|)
return|return;
while|while
condition|(
operator|(
name|gimp_object_get_memsize
argument_list|(
name|GIMP_OBJECT
argument_list|(
name|container
argument_list|)
argument_list|,
name|NULL
argument_list|)
operator|>
name|undo_size
operator|)
operator|||
operator|(
name|gimp_container_num_children
argument_list|(
name|container
argument_list|)
operator|>
name|max_undo_levels
operator|)
condition|)
block|{
name|GimpUndo
modifier|*
name|freed
init|=
name|gimp_undo_stack_free_bottom
argument_list|(
name|image
operator|->
name|undo_stack
argument_list|,
name|GIMP_UNDO_MODE_UNDO
argument_list|)
decl_stmt|;
ifdef|#
directive|ifdef
name|DEBUG_IMAGE_UNDO
name|g_printerr
argument_list|(
literal|"freed one step: undo_steps: %d    undo_bytes: %ld\n"
argument_list|,
name|gimp_container_num_children
argument_list|(
name|container
argument_list|)
argument_list|,
operator|(
name|glong
operator|)
name|gimp_object_get_memsize
argument_list|(
name|GIMP_OBJECT
argument_list|(
name|container
argument_list|)
argument_list|,
name|NULL
argument_list|)
argument_list|)
expr_stmt|;
endif|#
directive|endif
name|gimp_image_undo_event
argument_list|(
name|image
argument_list|,
name|GIMP_UNDO_EVENT_UNDO_EXPIRED
argument_list|,
name|freed
argument_list|)
expr_stmt|;
name|g_object_unref
argument_list|(
name|freed
argument_list|)
expr_stmt|;
if|if
condition|(
name|gimp_container_num_children
argument_list|(
name|container
argument_list|)
operator|<=
name|min_undo_levels
condition|)
return|return;
block|}
block|}
end_function

begin_function
specifier|static
name|void
DECL|function|gimp_image_undo_free_redo (GimpImage * image)
name|gimp_image_undo_free_redo
parameter_list|(
name|GimpImage
modifier|*
name|image
parameter_list|)
block|{
name|GimpContainer
modifier|*
name|container
init|=
name|image
operator|->
name|redo_stack
operator|->
name|undos
decl_stmt|;
ifdef|#
directive|ifdef
name|DEBUG_IMAGE_UNDO
name|g_printerr
argument_list|(
literal|"redo_steps: %d    redo_bytes: %ld\n"
argument_list|,
name|gimp_container_num_children
argument_list|(
name|container
argument_list|)
argument_list|,
operator|(
name|glong
operator|)
name|gimp_object_get_memsize
argument_list|(
name|GIMP_OBJECT
argument_list|(
name|container
argument_list|)
argument_list|,
name|NULL
argument_list|)
argument_list|)
expr_stmt|;
endif|#
directive|endif
if|if
condition|(
name|gimp_container_is_empty
argument_list|(
name|container
argument_list|)
condition|)
return|return;
while|while
condition|(
name|gimp_container_num_children
argument_list|(
name|container
argument_list|)
operator|>
literal|0
condition|)
block|{
name|GimpUndo
modifier|*
name|freed
init|=
name|gimp_undo_stack_free_bottom
argument_list|(
name|image
operator|->
name|redo_stack
argument_list|,
name|GIMP_UNDO_MODE_REDO
argument_list|)
decl_stmt|;
ifdef|#
directive|ifdef
name|DEBUG_IMAGE_UNDO
name|g_printerr
argument_list|(
literal|"freed one step: redo_steps: %d    redo_bytes: %ld\n"
argument_list|,
name|gimp_container_num_children
argument_list|(
name|container
argument_list|)
argument_list|,
operator|(
name|glong
operator|)
name|gimp_object_get_memsize
argument_list|(
name|GIMP_OBJECT
argument_list|(
name|container
argument_list|)
argument_list|,
name|NULL
argument_list|)
argument_list|)
expr_stmt|;
endif|#
directive|endif
name|gimp_image_undo_event
argument_list|(
name|image
argument_list|,
name|GIMP_UNDO_EVENT_REDO_EXPIRED
argument_list|,
name|freed
argument_list|)
expr_stmt|;
name|g_object_unref
argument_list|(
name|freed
argument_list|)
expr_stmt|;
block|}
comment|/* We need to use<= here because the undo counter has already been    * incremented at this point.    */
if|if
condition|(
name|image
operator|->
name|dirty
operator|<=
literal|0
condition|)
block|{
comment|/* If the image was dirty, but could become clean by redo-ing        * some actions, then it should now become 'infinitely' dirty.        * This is because we've just nuked the actions that would allow        * the image to become clean again.        */
name|image
operator|->
name|dirty
operator|=
literal|100000
expr_stmt|;
block|}
block|}
end_function

begin_function
specifier|static
name|GimpDirtyMask
DECL|function|gimp_image_undo_dirty_from_type (GimpUndoType undo_type)
name|gimp_image_undo_dirty_from_type
parameter_list|(
name|GimpUndoType
name|undo_type
parameter_list|)
block|{
switch|switch
condition|(
name|undo_type
condition|)
block|{
case|case
name|GIMP_UNDO_GROUP_IMAGE_SCALE
case|:
case|case
name|GIMP_UNDO_GROUP_IMAGE_RESIZE
case|:
case|case
name|GIMP_UNDO_GROUP_IMAGE_FLIP
case|:
case|case
name|GIMP_UNDO_GROUP_IMAGE_ROTATE
case|:
case|case
name|GIMP_UNDO_GROUP_IMAGE_CROP
case|:
return|return
name|GIMP_DIRTY_IMAGE
operator||
name|GIMP_DIRTY_IMAGE_SIZE
return|;
case|case
name|GIMP_UNDO_GROUP_IMAGE_CONVERT
case|:
return|return
name|GIMP_DIRTY_IMAGE
operator||
name|GIMP_DIRTY_DRAWABLE
return|;
case|case
name|GIMP_UNDO_GROUP_IMAGE_LAYERS_MERGE
case|:
return|return
name|GIMP_DIRTY_IMAGE_STRUCTURE
operator||
name|GIMP_DIRTY_DRAWABLE
return|;
case|case
name|GIMP_UNDO_GROUP_IMAGE_VECTORS_MERGE
case|:
return|return
name|GIMP_DIRTY_IMAGE_STRUCTURE
operator||
name|GIMP_DIRTY_VECTORS
return|;
case|case
name|GIMP_UNDO_GROUP_IMAGE_QUICK_MASK
case|:
comment|/* FIXME */
return|return
name|GIMP_DIRTY_IMAGE_STRUCTURE
operator||
name|GIMP_DIRTY_SELECTION
return|;
case|case
name|GIMP_UNDO_GROUP_IMAGE_GRID
case|:
case|case
name|GIMP_UNDO_GROUP_GUIDE
case|:
return|return
name|GIMP_DIRTY_IMAGE_META
return|;
case|case
name|GIMP_UNDO_GROUP_DRAWABLE
case|:
case|case
name|GIMP_UNDO_GROUP_DRAWABLE_MOD
case|:
return|return
name|GIMP_DIRTY_ITEM
operator||
name|GIMP_DIRTY_DRAWABLE
return|;
case|case
name|GIMP_UNDO_GROUP_MASK
case|:
comment|/* FIXME */
return|return
name|GIMP_DIRTY_SELECTION
return|;
case|case
name|GIMP_UNDO_GROUP_ITEM_VISIBILITY
case|:
case|case
name|GIMP_UNDO_GROUP_ITEM_LINKED
case|:
case|case
name|GIMP_UNDO_GROUP_ITEM_PROPERTIES
case|:
return|return
name|GIMP_DIRTY_ITEM_META
return|;
case|case
name|GIMP_UNDO_GROUP_ITEM_DISPLACE
case|:
comment|/* FIXME */
return|return
name|GIMP_DIRTY_ITEM
operator||
name|GIMP_DIRTY_DRAWABLE
operator||
name|GIMP_DIRTY_VECTORS
return|;
case|case
name|GIMP_UNDO_GROUP_ITEM_SCALE
case|:
comment|/* FIXME */
case|case
name|GIMP_UNDO_GROUP_ITEM_RESIZE
case|:
comment|/* FIXME */
return|return
name|GIMP_DIRTY_ITEM
operator||
name|GIMP_DIRTY_DRAWABLE
operator||
name|GIMP_DIRTY_VECTORS
return|;
case|case
name|GIMP_UNDO_GROUP_LAYER_ADD_MASK
case|:
case|case
name|GIMP_UNDO_GROUP_LAYER_APPLY_MASK
case|:
return|return
name|GIMP_DIRTY_IMAGE_STRUCTURE
return|;
case|case
name|GIMP_UNDO_GROUP_FS_TO_LAYER
case|:
case|case
name|GIMP_UNDO_GROUP_FS_FLOAT
case|:
case|case
name|GIMP_UNDO_GROUP_FS_ANCHOR
case|:
case|case
name|GIMP_UNDO_GROUP_FS_REMOVE
case|:
return|return
name|GIMP_DIRTY_IMAGE_STRUCTURE
return|;
case|case
name|GIMP_UNDO_GROUP_EDIT_PASTE
case|:
return|return
name|GIMP_DIRTY_IMAGE_STRUCTURE
return|;
case|case
name|GIMP_UNDO_GROUP_EDIT_CUT
case|:
return|return
name|GIMP_DIRTY_ITEM
operator||
name|GIMP_DIRTY_DRAWABLE
return|;
case|case
name|GIMP_UNDO_GROUP_TEXT
case|:
return|return
name|GIMP_DIRTY_ITEM
operator||
name|GIMP_DIRTY_DRAWABLE
return|;
case|case
name|GIMP_UNDO_GROUP_TRANSFORM
case|:
comment|/* FIXME */
return|return
name|GIMP_DIRTY_ITEM
operator||
name|GIMP_DIRTY_DRAWABLE
operator||
name|GIMP_DIRTY_VECTORS
return|;
case|case
name|GIMP_UNDO_GROUP_PAINT
case|:
return|return
name|GIMP_DIRTY_ITEM
operator||
name|GIMP_DIRTY_DRAWABLE
return|;
case|case
name|GIMP_UNDO_GROUP_PARASITE_ATTACH
case|:
case|case
name|GIMP_UNDO_GROUP_PARASITE_REMOVE
case|:
return|return
name|GIMP_DIRTY_IMAGE_META
operator||
name|GIMP_DIRTY_ITEM_META
return|;
case|case
name|GIMP_UNDO_GROUP_VECTORS_IMPORT
case|:
return|return
name|GIMP_DIRTY_IMAGE_STRUCTURE
operator||
name|GIMP_DIRTY_VECTORS
return|;
case|case
name|GIMP_UNDO_GROUP_MISC
case|:
return|return
name|GIMP_DIRTY_ALL
return|;
default|default:
break|break;
block|}
return|return
name|GIMP_DIRTY_ALL
return|;
block|}
end_function

end_unit

