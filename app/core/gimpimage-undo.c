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
name|gimage
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
name|gimage
parameter_list|)
function_decl|;
end_function_decl

begin_function_decl
specifier|static
specifier|const
name|gchar
modifier|*
name|gimp_image_undo_type_to_name
parameter_list|(
name|GimpUndoType
name|type
parameter_list|)
function_decl|;
end_function_decl

begin_comment
comment|/*  public functions  */
end_comment

begin_function
name|gboolean
DECL|function|gimp_image_undo (GimpImage * gimage)
name|gimp_image_undo
parameter_list|(
name|GimpImage
modifier|*
name|gimage
parameter_list|)
block|{
name|g_return_val_if_fail
argument_list|(
name|GIMP_IS_IMAGE
argument_list|(
name|gimage
argument_list|)
argument_list|,
name|FALSE
argument_list|)
expr_stmt|;
name|g_return_val_if_fail
argument_list|(
name|gimage
operator|->
name|pushing_undo_group
operator|==
name|NO_UNDO_GROUP
argument_list|,
name|FALSE
argument_list|)
expr_stmt|;
name|gimp_image_undo_pop_stack
argument_list|(
name|gimage
argument_list|,
name|gimage
operator|->
name|undo_stack
argument_list|,
name|gimage
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

begin_function
name|gboolean
DECL|function|gimp_image_redo (GimpImage * gimage)
name|gimp_image_redo
parameter_list|(
name|GimpImage
modifier|*
name|gimage
parameter_list|)
block|{
name|g_return_val_if_fail
argument_list|(
name|GIMP_IS_IMAGE
argument_list|(
name|gimage
argument_list|)
argument_list|,
name|FALSE
argument_list|)
expr_stmt|;
name|g_return_val_if_fail
argument_list|(
name|gimage
operator|->
name|pushing_undo_group
operator|==
name|NO_UNDO_GROUP
argument_list|,
name|FALSE
argument_list|)
expr_stmt|;
name|gimp_image_undo_pop_stack
argument_list|(
name|gimage
argument_list|,
name|gimage
operator|->
name|redo_stack
argument_list|,
name|gimage
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

begin_function
name|void
DECL|function|gimp_image_undo_free (GimpImage * gimage)
name|gimp_image_undo_free
parameter_list|(
name|GimpImage
modifier|*
name|gimage
parameter_list|)
block|{
name|g_return_if_fail
argument_list|(
name|GIMP_IS_IMAGE
argument_list|(
name|gimage
argument_list|)
argument_list|)
expr_stmt|;
name|gimp_undo_free
argument_list|(
name|GIMP_UNDO
argument_list|(
name|gimage
operator|->
name|undo_stack
argument_list|)
argument_list|,
name|gimage
argument_list|,
name|GIMP_UNDO_MODE_UNDO
argument_list|)
expr_stmt|;
name|gimp_undo_free
argument_list|(
name|GIMP_UNDO
argument_list|(
name|gimage
operator|->
name|redo_stack
argument_list|)
argument_list|,
name|gimage
argument_list|,
name|GIMP_UNDO_MODE_REDO
argument_list|)
expr_stmt|;
comment|/* If the image was dirty, but could become clean by redo-ing    * some actions, then it should now become 'infinitely' dirty.    * This is because we've just nuked the actions that would allow    * the image to become clean again.  The only hope for salvation    * is to save the image now!  -- austin    */
if|if
condition|(
name|gimage
operator|->
name|dirty
operator|<
literal|0
condition|)
name|gimage
operator|->
name|dirty
operator|=
literal|10000
expr_stmt|;
comment|/* The same applies to the case where the image would become clean    * due to undo actions, but since user can't undo without an undo    * stack, that's not so much a problem.    */
name|gimp_image_undo_event
argument_list|(
name|gimage
argument_list|,
name|UNDO_FREE
argument_list|)
expr_stmt|;
block|}
end_function

begin_function
name|gboolean
DECL|function|gimp_image_undo_group_start (GimpImage * gimage,GimpUndoType type,const gchar * name)
name|gimp_image_undo_group_start
parameter_list|(
name|GimpImage
modifier|*
name|gimage
parameter_list|,
name|GimpUndoType
name|type
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
name|g_return_val_if_fail
argument_list|(
name|GIMP_IS_IMAGE
argument_list|(
name|gimage
argument_list|)
argument_list|,
name|FALSE
argument_list|)
expr_stmt|;
name|g_return_val_if_fail
argument_list|(
name|type
operator|>
name|FIRST_UNDO_GROUP
operator|&&
name|type
operator|<=
name|LAST_UNDO_GROUP
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
name|gimp_image_undo_type_to_name
argument_list|(
name|type
argument_list|)
expr_stmt|;
comment|/* Notify listeners that the image will be modified */
name|gimp_image_undo_start
argument_list|(
name|gimage
argument_list|)
expr_stmt|;
if|if
condition|(
operator|!
name|gimage
operator|->
name|undo_on
condition|)
return|return
name|FALSE
return|;
name|gimage
operator|->
name|group_count
operator|++
expr_stmt|;
comment|/*  If we're already in a group...ignore  */
if|if
condition|(
name|gimage
operator|->
name|group_count
operator|>
literal|1
condition|)
return|return
name|TRUE
return|;
comment|/*  nuke the redo stack  */
name|gimp_undo_free
argument_list|(
name|GIMP_UNDO
argument_list|(
name|gimage
operator|->
name|redo_stack
argument_list|)
argument_list|,
name|gimage
argument_list|,
name|GIMP_UNDO_MODE_REDO
argument_list|)
expr_stmt|;
comment|/* If the image was dirty, but could become clean by redo-ing    * some actions, then it should now become 'infinitely' dirty.    * This is because we've just nuked the actions that would allow    * the image to become clean again.  The only hope for salvation    * is to save the image now!  -- austin    */
if|if
condition|(
name|gimage
operator|->
name|dirty
operator|<
literal|0
condition|)
name|gimage
operator|->
name|dirty
operator|=
literal|10000
expr_stmt|;
name|undo_group
operator|=
name|gimp_undo_stack_new
argument_list|(
name|gimage
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
name|type
expr_stmt|;
name|gimp_undo_stack_push_undo
argument_list|(
name|gimage
operator|->
name|undo_stack
argument_list|,
name|GIMP_UNDO
argument_list|(
name|undo_group
argument_list|)
argument_list|)
expr_stmt|;
name|gimage
operator|->
name|pushing_undo_group
operator|=
name|type
expr_stmt|;
return|return
name|TRUE
return|;
block|}
end_function

begin_function
name|gboolean
DECL|function|gimp_image_undo_group_end (GimpImage * gimage)
name|gimp_image_undo_group_end
parameter_list|(
name|GimpImage
modifier|*
name|gimage
parameter_list|)
block|{
name|g_return_val_if_fail
argument_list|(
name|GIMP_IS_IMAGE
argument_list|(
name|gimage
argument_list|)
argument_list|,
name|FALSE
argument_list|)
expr_stmt|;
name|g_return_val_if_fail
argument_list|(
name|gimage
operator|->
name|group_count
operator|>
literal|0
argument_list|,
name|FALSE
argument_list|)
expr_stmt|;
if|if
condition|(
operator|!
name|gimage
operator|->
name|undo_on
condition|)
return|return
name|FALSE
return|;
name|gimage
operator|->
name|group_count
operator|--
expr_stmt|;
if|if
condition|(
name|gimage
operator|->
name|group_count
operator|==
literal|0
condition|)
block|{
name|gimage
operator|->
name|pushing_undo_group
operator|=
name|NO_UNDO_GROUP
expr_stmt|;
name|gimp_image_undo_free_space
argument_list|(
name|gimage
argument_list|)
expr_stmt|;
comment|/* Do it here, since undo_push doesn't emit this event while in        * the middle of a group        */
name|gimp_image_undo_event
argument_list|(
name|gimage
argument_list|,
name|UNDO_PUSHED
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
DECL|function|gimp_image_undo_push (GimpImage * gimage,gsize size,gsize struct_size,GimpUndoType type,const gchar * name,gboolean dirties_image,GimpUndoPopFunc pop_func,GimpUndoFreeFunc free_func)
name|gimp_image_undo_push
parameter_list|(
name|GimpImage
modifier|*
name|gimage
parameter_list|,
name|gsize
name|size
parameter_list|,
name|gsize
name|struct_size
parameter_list|,
name|GimpUndoType
name|type
parameter_list|,
specifier|const
name|gchar
modifier|*
name|name
parameter_list|,
name|gboolean
name|dirties_image
parameter_list|,
name|GimpUndoPopFunc
name|pop_func
parameter_list|,
name|GimpUndoFreeFunc
name|free_func
parameter_list|)
block|{
name|GimpUndo
modifier|*
name|new
decl_stmt|;
name|gpointer
name|undo_struct
init|=
name|NULL
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
name|g_return_val_if_fail
argument_list|(
name|type
operator|>
name|LAST_UNDO_GROUP
argument_list|,
name|NULL
argument_list|)
expr_stmt|;
if|if
condition|(
operator|!
name|name
condition|)
name|name
operator|=
name|gimp_image_undo_type_to_name
argument_list|(
name|type
argument_list|)
expr_stmt|;
comment|/* Does this undo dirty the image?  If so, we always want to mark    * image dirty, even if we can't actually push the undo.    */
if|if
condition|(
name|dirties_image
condition|)
name|gimp_image_dirty
argument_list|(
name|gimage
argument_list|)
expr_stmt|;
if|if
condition|(
operator|!
name|gimage
operator|->
name|undo_on
condition|)
return|return
name|NULL
return|;
comment|/*  nuke the redo stack  */
name|gimp_undo_free
argument_list|(
name|GIMP_UNDO
argument_list|(
name|gimage
operator|->
name|redo_stack
argument_list|)
argument_list|,
name|gimage
argument_list|,
name|GIMP_UNDO_MODE_REDO
argument_list|)
expr_stmt|;
comment|/* If the image was dirty, but could become clean by redo-ing    * some actions, then it should now become 'infinitely' dirty.    * This is because we've just nuked the actions that would allow    * the image to become clean again.  The only hope for salvation    * is to save the image now!  -- austin    */
if|if
condition|(
name|gimage
operator|->
name|dirty
operator|<
literal|0
condition|)
name|gimage
operator|->
name|dirty
operator|=
literal|10000
expr_stmt|;
if|if
condition|(
name|struct_size
operator|>
literal|0
condition|)
name|undo_struct
operator|=
name|g_malloc0
argument_list|(
name|struct_size
argument_list|)
expr_stmt|;
name|new
operator|=
name|gimp_undo_new
argument_list|(
name|type
argument_list|,
name|name
argument_list|,
name|undo_struct
argument_list|,
name|size
argument_list|,
name|dirties_image
argument_list|,
name|pop_func
argument_list|,
name|free_func
argument_list|)
expr_stmt|;
if|if
condition|(
name|gimage
operator|->
name|pushing_undo_group
operator|==
name|NO_UNDO_GROUP
condition|)
block|{
name|gimp_undo_stack_push_undo
argument_list|(
name|gimage
operator|->
name|undo_stack
argument_list|,
name|new
argument_list|)
expr_stmt|;
name|gimp_image_undo_free_space
argument_list|(
name|gimage
argument_list|)
expr_stmt|;
name|gimp_image_undo_event
argument_list|(
name|gimage
argument_list|,
name|UNDO_PUSHED
argument_list|)
expr_stmt|;
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
name|gimage
operator|->
name|undo_stack
argument_list|)
argument_list|)
expr_stmt|;
name|gimp_undo_stack_push_undo
argument_list|(
name|undo_group
argument_list|,
name|new
argument_list|)
expr_stmt|;
block|}
return|return
name|new
return|;
block|}
end_function

begin_comment
comment|/*  private functions  */
end_comment

begin_function
specifier|static
name|void
DECL|function|gimp_image_undo_pop_stack (GimpImage * gimage,GimpUndoStack * undo_stack,GimpUndoStack * redo_stack,GimpUndoMode undo_mode)
name|gimp_image_undo_pop_stack
parameter_list|(
name|GimpImage
modifier|*
name|gimage
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
operator|!
name|undo
condition|)
return|return;
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
name|gimage
argument_list|)
expr_stmt|;
if|if
condition|(
name|accum
operator|.
name|size_changed
condition|)
name|gimp_viewable_size_changed
argument_list|(
name|GIMP_VIEWABLE
argument_list|(
name|gimage
argument_list|)
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
name|gimage
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
name|gimage
argument_list|)
expr_stmt|;
if|if
condition|(
name|accum
operator|.
name|mask_changed
condition|)
name|gimp_image_mask_changed
argument_list|(
name|gimage
argument_list|)
expr_stmt|;
if|if
condition|(
name|accum
operator|.
name|qmask_changed
condition|)
name|gimp_image_qmask_changed
argument_list|(
name|gimage
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
name|gimage
argument_list|)
expr_stmt|;
comment|/* let others know that we just popped an action */
name|gimp_image_undo_event
argument_list|(
name|gimage
argument_list|,
operator|(
name|undo_mode
operator|==
name|GIMP_UNDO_MODE_UNDO
operator|)
condition|?
name|UNDO_POPPED
else|:
name|UNDO_REDO
argument_list|)
expr_stmt|;
block|}
end_function

begin_function
specifier|static
name|void
DECL|function|gimp_image_undo_free_space (GimpImage * gimage)
name|gimp_image_undo_free_space
parameter_list|(
name|GimpImage
modifier|*
name|gimage
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
name|gulong
name|undo_size
decl_stmt|;
name|container
operator|=
name|gimage
operator|->
name|undo_stack
operator|->
name|undos
expr_stmt|;
name|min_undo_levels
operator|=
name|gimage
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
name|gimage
operator|->
name|gimp
operator|->
name|config
operator|->
name|undo_size
expr_stmt|;
comment|/*  keep at least undo_levels undo steps  */
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
name|gimp_undo_stack_free_bottom
argument_list|(
name|gimage
operator|->
name|undo_stack
argument_list|,
name|GIMP_UNDO_MODE_UNDO
argument_list|)
expr_stmt|;
name|gimp_image_undo_event
argument_list|(
name|gimage
argument_list|,
name|UNDO_EXPIRED
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
specifier|const
name|gchar
modifier|*
DECL|function|gimp_image_undo_type_to_name (GimpUndoType type)
name|gimp_image_undo_type_to_name
parameter_list|(
name|GimpUndoType
name|type
parameter_list|)
block|{
specifier|static
name|GEnumClass
modifier|*
name|enum_class
init|=
name|NULL
decl_stmt|;
name|GEnumValue
modifier|*
name|value
decl_stmt|;
if|if
condition|(
operator|!
name|enum_class
condition|)
name|enum_class
operator|=
name|g_type_class_ref
argument_list|(
name|GIMP_TYPE_UNDO_TYPE
argument_list|)
expr_stmt|;
name|value
operator|=
name|g_enum_get_value
argument_list|(
name|enum_class
argument_list|,
name|type
argument_list|)
expr_stmt|;
if|if
condition|(
name|value
condition|)
return|return
name|value
operator|->
name|value_name
return|;
return|return
literal|""
return|;
block|}
end_function

end_unit

