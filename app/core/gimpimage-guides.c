begin_unit|revision:0.9.5;language:C;cregit-version:0.0.1
begin_comment
comment|/* GIMP - The GNU Image Manipulation Program  * Copyright (C) 1995 Spencer Kimball and Peter Mattis  *  * This program is free software: you can redistribute it and/or modify  * it under the terms of the GNU General Public License as published by  * the Free Software Foundation; either version 3 of the License, or  * (at your option) any later version.  *  * This program is distributed in the hope that it will be useful,  * but WITHOUT ANY WARRANTY; without even the implied warranty of  * MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the  * GNU General Public License for more details.  *  * You should have received a copy of the GNU General Public License  * along with this program.  If not, see<https://www.gnu.org/licenses/>.  */
end_comment

begin_include
include|#
directive|include
file|"config.h"
end_include

begin_include
include|#
directive|include
file|<gdk-pixbuf/gdk-pixbuf.h>
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
file|"gimpguide.h"
end_include

begin_include
include|#
directive|include
file|"gimpimage-guides.h"
end_include

begin_include
include|#
directive|include
file|"gimpimage-private.h"
end_include

begin_include
include|#
directive|include
file|"gimpimage-undo-push.h"
end_include

begin_include
include|#
directive|include
file|"gimp-intl.h"
end_include

begin_comment
comment|/*  public functions  */
end_comment

begin_function
name|GimpGuide
modifier|*
DECL|function|gimp_image_add_hguide (GimpImage * image,gint position,gboolean push_undo)
name|gimp_image_add_hguide
parameter_list|(
name|GimpImage
modifier|*
name|image
parameter_list|,
name|gint
name|position
parameter_list|,
name|gboolean
name|push_undo
parameter_list|)
block|{
name|GimpGuide
modifier|*
name|guide
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
name|position
operator|>=
literal|0
operator|&&
name|position
operator|<=
name|gimp_image_get_height
argument_list|(
name|image
argument_list|)
argument_list|,
name|NULL
argument_list|)
expr_stmt|;
name|guide
operator|=
name|gimp_guide_new
argument_list|(
name|GIMP_ORIENTATION_HORIZONTAL
argument_list|,
name|image
operator|->
name|gimp
operator|->
name|next_guide_ID
operator|++
argument_list|)
expr_stmt|;
if|if
condition|(
name|push_undo
condition|)
name|gimp_image_undo_push_guide
argument_list|(
name|image
argument_list|,
name|C_
argument_list|(
literal|"undo-type"
argument_list|,
literal|"Add Horizontal Guide"
argument_list|)
argument_list|,
name|guide
argument_list|)
expr_stmt|;
name|gimp_image_add_guide
argument_list|(
name|image
argument_list|,
name|guide
argument_list|,
name|position
argument_list|)
expr_stmt|;
name|g_object_unref
argument_list|(
name|G_OBJECT
argument_list|(
name|guide
argument_list|)
argument_list|)
expr_stmt|;
return|return
name|guide
return|;
block|}
end_function

begin_function
name|GimpGuide
modifier|*
DECL|function|gimp_image_add_vguide (GimpImage * image,gint position,gboolean push_undo)
name|gimp_image_add_vguide
parameter_list|(
name|GimpImage
modifier|*
name|image
parameter_list|,
name|gint
name|position
parameter_list|,
name|gboolean
name|push_undo
parameter_list|)
block|{
name|GimpGuide
modifier|*
name|guide
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
name|position
operator|>=
literal|0
operator|&&
name|position
operator|<=
name|gimp_image_get_width
argument_list|(
name|image
argument_list|)
argument_list|,
name|NULL
argument_list|)
expr_stmt|;
name|guide
operator|=
name|gimp_guide_new
argument_list|(
name|GIMP_ORIENTATION_VERTICAL
argument_list|,
name|image
operator|->
name|gimp
operator|->
name|next_guide_ID
operator|++
argument_list|)
expr_stmt|;
if|if
condition|(
name|push_undo
condition|)
name|gimp_image_undo_push_guide
argument_list|(
name|image
argument_list|,
name|C_
argument_list|(
literal|"undo-type"
argument_list|,
literal|"Add Vertical Guide"
argument_list|)
argument_list|,
name|guide
argument_list|)
expr_stmt|;
name|gimp_image_add_guide
argument_list|(
name|image
argument_list|,
name|guide
argument_list|,
name|position
argument_list|)
expr_stmt|;
name|g_object_unref
argument_list|(
name|G_OBJECT
argument_list|(
name|guide
argument_list|)
argument_list|)
expr_stmt|;
return|return
name|guide
return|;
block|}
end_function

begin_function
name|void
DECL|function|gimp_image_add_guide (GimpImage * image,GimpGuide * guide,gint position)
name|gimp_image_add_guide
parameter_list|(
name|GimpImage
modifier|*
name|image
parameter_list|,
name|GimpGuide
modifier|*
name|guide
parameter_list|,
name|gint
name|position
parameter_list|)
block|{
name|GimpImagePrivate
modifier|*
name|private
decl_stmt|;
name|g_return_if_fail
argument_list|(
name|GIMP_IS_IMAGE
argument_list|(
name|image
argument_list|)
argument_list|)
expr_stmt|;
name|g_return_if_fail
argument_list|(
name|GIMP_IS_GUIDE
argument_list|(
name|guide
argument_list|)
argument_list|)
expr_stmt|;
name|private
operator|=
name|GIMP_IMAGE_GET_PRIVATE
argument_list|(
name|image
argument_list|)
expr_stmt|;
name|private
operator|->
name|guides
operator|=
name|g_list_prepend
argument_list|(
name|private
operator|->
name|guides
argument_list|,
name|guide
argument_list|)
expr_stmt|;
name|gimp_guide_set_position
argument_list|(
name|guide
argument_list|,
name|position
argument_list|)
expr_stmt|;
name|g_object_ref
argument_list|(
name|G_OBJECT
argument_list|(
name|guide
argument_list|)
argument_list|)
expr_stmt|;
name|gimp_image_guide_added
argument_list|(
name|image
argument_list|,
name|guide
argument_list|)
expr_stmt|;
block|}
end_function

begin_function
name|void
DECL|function|gimp_image_remove_guide (GimpImage * image,GimpGuide * guide,gboolean push_undo)
name|gimp_image_remove_guide
parameter_list|(
name|GimpImage
modifier|*
name|image
parameter_list|,
name|GimpGuide
modifier|*
name|guide
parameter_list|,
name|gboolean
name|push_undo
parameter_list|)
block|{
name|GimpImagePrivate
modifier|*
name|private
decl_stmt|;
name|g_return_if_fail
argument_list|(
name|GIMP_IS_IMAGE
argument_list|(
name|image
argument_list|)
argument_list|)
expr_stmt|;
name|g_return_if_fail
argument_list|(
name|GIMP_IS_GUIDE
argument_list|(
name|guide
argument_list|)
argument_list|)
expr_stmt|;
name|private
operator|=
name|GIMP_IMAGE_GET_PRIVATE
argument_list|(
name|image
argument_list|)
expr_stmt|;
if|if
condition|(
name|gimp_guide_is_custom
argument_list|(
name|guide
argument_list|)
condition|)
name|push_undo
operator|=
name|FALSE
expr_stmt|;
if|if
condition|(
name|push_undo
condition|)
name|gimp_image_undo_push_guide
argument_list|(
name|image
argument_list|,
name|C_
argument_list|(
literal|"undo-type"
argument_list|,
literal|"Remove Guide"
argument_list|)
argument_list|,
name|guide
argument_list|)
expr_stmt|;
name|private
operator|->
name|guides
operator|=
name|g_list_remove
argument_list|(
name|private
operator|->
name|guides
argument_list|,
name|guide
argument_list|)
expr_stmt|;
name|gimp_guide_removed
argument_list|(
name|guide
argument_list|)
expr_stmt|;
name|gimp_image_guide_removed
argument_list|(
name|image
argument_list|,
name|guide
argument_list|)
expr_stmt|;
name|gimp_guide_set_position
argument_list|(
name|guide
argument_list|,
name|GIMP_GUIDE_POSITION_UNDEFINED
argument_list|)
expr_stmt|;
name|g_object_unref
argument_list|(
name|G_OBJECT
argument_list|(
name|guide
argument_list|)
argument_list|)
expr_stmt|;
block|}
end_function

begin_function
name|void
DECL|function|gimp_image_move_guide (GimpImage * image,GimpGuide * guide,gint position,gboolean push_undo)
name|gimp_image_move_guide
parameter_list|(
name|GimpImage
modifier|*
name|image
parameter_list|,
name|GimpGuide
modifier|*
name|guide
parameter_list|,
name|gint
name|position
parameter_list|,
name|gboolean
name|push_undo
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
name|g_return_if_fail
argument_list|(
name|GIMP_IS_GUIDE
argument_list|(
name|guide
argument_list|)
argument_list|)
expr_stmt|;
name|g_return_if_fail
argument_list|(
name|position
operator|>=
literal|0
argument_list|)
expr_stmt|;
if|if
condition|(
name|gimp_guide_get_orientation
argument_list|(
name|guide
argument_list|)
operator|==
name|GIMP_ORIENTATION_HORIZONTAL
condition|)
name|g_return_if_fail
argument_list|(
name|position
operator|<=
name|gimp_image_get_height
argument_list|(
name|image
argument_list|)
argument_list|)
expr_stmt|;
else|else
name|g_return_if_fail
argument_list|(
name|position
operator|<=
name|gimp_image_get_width
argument_list|(
name|image
argument_list|)
argument_list|)
expr_stmt|;
if|if
condition|(
name|gimp_guide_is_custom
argument_list|(
name|guide
argument_list|)
condition|)
name|push_undo
operator|=
name|FALSE
expr_stmt|;
if|if
condition|(
name|push_undo
condition|)
name|gimp_image_undo_push_guide
argument_list|(
name|image
argument_list|,
name|C_
argument_list|(
literal|"undo-type"
argument_list|,
literal|"Move Guide"
argument_list|)
argument_list|,
name|guide
argument_list|)
expr_stmt|;
name|gimp_guide_set_position
argument_list|(
name|guide
argument_list|,
name|position
argument_list|)
expr_stmt|;
name|gimp_image_guide_moved
argument_list|(
name|image
argument_list|,
name|guide
argument_list|)
expr_stmt|;
block|}
end_function

begin_function
name|GList
modifier|*
DECL|function|gimp_image_get_guides (GimpImage * image)
name|gimp_image_get_guides
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
name|GIMP_IMAGE_GET_PRIVATE
argument_list|(
name|image
argument_list|)
operator|->
name|guides
return|;
block|}
end_function

begin_function
name|GimpGuide
modifier|*
DECL|function|gimp_image_get_guide (GimpImage * image,guint32 id)
name|gimp_image_get_guide
parameter_list|(
name|GimpImage
modifier|*
name|image
parameter_list|,
name|guint32
name|id
parameter_list|)
block|{
name|GList
modifier|*
name|guides
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
for|for
control|(
name|guides
operator|=
name|GIMP_IMAGE_GET_PRIVATE
argument_list|(
name|image
argument_list|)
operator|->
name|guides
init|;
name|guides
condition|;
name|guides
operator|=
name|g_list_next
argument_list|(
name|guides
argument_list|)
control|)
block|{
name|GimpGuide
modifier|*
name|guide
init|=
name|guides
operator|->
name|data
decl_stmt|;
if|if
condition|(
name|gimp_guide_get_ID
argument_list|(
name|guide
argument_list|)
operator|==
name|id
condition|)
return|return
name|guide
return|;
block|}
return|return
name|NULL
return|;
block|}
end_function

begin_function
name|GimpGuide
modifier|*
DECL|function|gimp_image_get_next_guide (GimpImage * image,guint32 id,gboolean * guide_found)
name|gimp_image_get_next_guide
parameter_list|(
name|GimpImage
modifier|*
name|image
parameter_list|,
name|guint32
name|id
parameter_list|,
name|gboolean
modifier|*
name|guide_found
parameter_list|)
block|{
name|GList
modifier|*
name|guides
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
name|guide_found
operator|!=
name|NULL
argument_list|,
name|NULL
argument_list|)
expr_stmt|;
if|if
condition|(
name|id
operator|==
literal|0
condition|)
operator|*
name|guide_found
operator|=
name|TRUE
expr_stmt|;
else|else
operator|*
name|guide_found
operator|=
name|FALSE
expr_stmt|;
for|for
control|(
name|guides
operator|=
name|GIMP_IMAGE_GET_PRIVATE
argument_list|(
name|image
argument_list|)
operator|->
name|guides
init|;
name|guides
condition|;
name|guides
operator|=
name|g_list_next
argument_list|(
name|guides
argument_list|)
control|)
block|{
name|GimpGuide
modifier|*
name|guide
init|=
name|guides
operator|->
name|data
decl_stmt|;
if|if
condition|(
operator|*
name|guide_found
condition|)
comment|/* this is the first guide after the found one */
return|return
name|guide
return|;
if|if
condition|(
name|gimp_guide_get_ID
argument_list|(
name|guide
argument_list|)
operator|==
name|id
condition|)
comment|/* found it, next one will be returned */
operator|*
name|guide_found
operator|=
name|TRUE
expr_stmt|;
block|}
return|return
name|NULL
return|;
block|}
end_function

end_unit

