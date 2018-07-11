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
file|"gimpimage-private.h"
end_include

begin_include
include|#
directive|include
file|"gimpimage-sample-points.h"
end_include

begin_include
include|#
directive|include
file|"gimpimage-undo-push.h"
end_include

begin_include
include|#
directive|include
file|"gimpsamplepoint.h"
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
name|GimpSamplePoint
modifier|*
DECL|function|gimp_image_add_sample_point_at_pos (GimpImage * image,gint x,gint y,gboolean push_undo)
name|gimp_image_add_sample_point_at_pos
parameter_list|(
name|GimpImage
modifier|*
name|image
parameter_list|,
name|gint
name|x
parameter_list|,
name|gint
name|y
parameter_list|,
name|gboolean
name|push_undo
parameter_list|)
block|{
name|GimpSamplePoint
modifier|*
name|sample_point
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
name|x
operator|>=
literal|0
operator|&&
name|x
operator|<
name|gimp_image_get_width
argument_list|(
name|image
argument_list|)
argument_list|,
name|NULL
argument_list|)
expr_stmt|;
name|g_return_val_if_fail
argument_list|(
name|y
operator|>=
literal|0
operator|&&
name|y
operator|<
name|gimp_image_get_height
argument_list|(
name|image
argument_list|)
argument_list|,
name|NULL
argument_list|)
expr_stmt|;
name|sample_point
operator|=
name|gimp_sample_point_new
argument_list|(
name|image
operator|->
name|gimp
operator|->
name|next_sample_point_ID
operator|++
argument_list|)
expr_stmt|;
if|if
condition|(
name|push_undo
condition|)
name|gimp_image_undo_push_sample_point
argument_list|(
name|image
argument_list|,
name|C_
argument_list|(
literal|"undo-type"
argument_list|,
literal|"Add Sample Point"
argument_list|)
argument_list|,
name|sample_point
argument_list|)
expr_stmt|;
name|gimp_image_add_sample_point
argument_list|(
name|image
argument_list|,
name|sample_point
argument_list|,
name|x
argument_list|,
name|y
argument_list|)
expr_stmt|;
name|gimp_sample_point_unref
argument_list|(
name|sample_point
argument_list|)
expr_stmt|;
return|return
name|sample_point
return|;
block|}
end_function

begin_function
name|void
DECL|function|gimp_image_add_sample_point (GimpImage * image,GimpSamplePoint * sample_point,gint x,gint y)
name|gimp_image_add_sample_point
parameter_list|(
name|GimpImage
modifier|*
name|image
parameter_list|,
name|GimpSamplePoint
modifier|*
name|sample_point
parameter_list|,
name|gint
name|x
parameter_list|,
name|gint
name|y
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
name|sample_point
operator|!=
name|NULL
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
name|sample_points
operator|=
name|g_list_append
argument_list|(
name|private
operator|->
name|sample_points
argument_list|,
name|sample_point
argument_list|)
expr_stmt|;
name|gimp_sample_point_set_position
argument_list|(
name|sample_point
argument_list|,
name|x
argument_list|,
name|y
argument_list|)
expr_stmt|;
name|gimp_sample_point_ref
argument_list|(
name|sample_point
argument_list|)
expr_stmt|;
name|gimp_image_sample_point_added
argument_list|(
name|image
argument_list|,
name|sample_point
argument_list|)
expr_stmt|;
block|}
end_function

begin_function
name|void
DECL|function|gimp_image_remove_sample_point (GimpImage * image,GimpSamplePoint * sample_point,gboolean push_undo)
name|gimp_image_remove_sample_point
parameter_list|(
name|GimpImage
modifier|*
name|image
parameter_list|,
name|GimpSamplePoint
modifier|*
name|sample_point
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
name|sample_point
operator|!=
name|NULL
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
name|push_undo
condition|)
name|gimp_image_undo_push_sample_point
argument_list|(
name|image
argument_list|,
name|C_
argument_list|(
literal|"undo-type"
argument_list|,
literal|"Remove Sample Point"
argument_list|)
argument_list|,
name|sample_point
argument_list|)
expr_stmt|;
name|private
operator|->
name|sample_points
operator|=
name|g_list_remove
argument_list|(
name|private
operator|->
name|sample_points
argument_list|,
name|sample_point
argument_list|)
expr_stmt|;
name|gimp_image_sample_point_removed
argument_list|(
name|image
argument_list|,
name|sample_point
argument_list|)
expr_stmt|;
name|gimp_sample_point_set_position
argument_list|(
name|sample_point
argument_list|,
operator|-
literal|1
argument_list|,
operator|-
literal|1
argument_list|)
expr_stmt|;
name|gimp_sample_point_unref
argument_list|(
name|sample_point
argument_list|)
expr_stmt|;
block|}
end_function

begin_function
name|void
DECL|function|gimp_image_move_sample_point (GimpImage * image,GimpSamplePoint * sample_point,gint x,gint y,gboolean push_undo)
name|gimp_image_move_sample_point
parameter_list|(
name|GimpImage
modifier|*
name|image
parameter_list|,
name|GimpSamplePoint
modifier|*
name|sample_point
parameter_list|,
name|gint
name|x
parameter_list|,
name|gint
name|y
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
name|sample_point
operator|!=
name|NULL
argument_list|)
expr_stmt|;
name|g_return_if_fail
argument_list|(
name|x
operator|>=
literal|0
argument_list|)
expr_stmt|;
name|g_return_if_fail
argument_list|(
name|y
operator|>=
literal|0
argument_list|)
expr_stmt|;
name|g_return_if_fail
argument_list|(
name|x
operator|<
name|gimp_image_get_width
argument_list|(
name|image
argument_list|)
argument_list|)
expr_stmt|;
name|g_return_if_fail
argument_list|(
name|y
operator|<
name|gimp_image_get_height
argument_list|(
name|image
argument_list|)
argument_list|)
expr_stmt|;
if|if
condition|(
name|push_undo
condition|)
name|gimp_image_undo_push_sample_point
argument_list|(
name|image
argument_list|,
name|C_
argument_list|(
literal|"undo-type"
argument_list|,
literal|"Move Sample Point"
argument_list|)
argument_list|,
name|sample_point
argument_list|)
expr_stmt|;
name|gimp_sample_point_set_position
argument_list|(
name|sample_point
argument_list|,
name|x
argument_list|,
name|y
argument_list|)
expr_stmt|;
name|gimp_image_sample_point_moved
argument_list|(
name|image
argument_list|,
name|sample_point
argument_list|)
expr_stmt|;
block|}
end_function

begin_function
name|GList
modifier|*
DECL|function|gimp_image_get_sample_points (GimpImage * image)
name|gimp_image_get_sample_points
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
name|sample_points
return|;
block|}
end_function

begin_function
name|GimpSamplePoint
modifier|*
DECL|function|gimp_image_get_sample_point (GimpImage * image,guint32 id)
name|gimp_image_get_sample_point
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
name|sample_points
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
name|sample_points
operator|=
name|GIMP_IMAGE_GET_PRIVATE
argument_list|(
name|image
argument_list|)
operator|->
name|sample_points
init|;
name|sample_points
condition|;
name|sample_points
operator|=
name|g_list_next
argument_list|(
name|sample_points
argument_list|)
control|)
block|{
name|GimpSamplePoint
modifier|*
name|sample_point
init|=
name|sample_points
operator|->
name|data
decl_stmt|;
if|if
condition|(
name|gimp_sample_point_get_ID
argument_list|(
name|sample_point
argument_list|)
operator|==
name|id
condition|)
return|return
name|sample_point
return|;
block|}
return|return
name|NULL
return|;
block|}
end_function

begin_function
name|GimpSamplePoint
modifier|*
DECL|function|gimp_image_get_next_sample_point (GimpImage * image,guint32 id,gboolean * sample_point_found)
name|gimp_image_get_next_sample_point
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
name|sample_point_found
parameter_list|)
block|{
name|GList
modifier|*
name|sample_points
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
name|sample_point_found
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
name|sample_point_found
operator|=
name|TRUE
expr_stmt|;
else|else
operator|*
name|sample_point_found
operator|=
name|FALSE
expr_stmt|;
for|for
control|(
name|sample_points
operator|=
name|GIMP_IMAGE_GET_PRIVATE
argument_list|(
name|image
argument_list|)
operator|->
name|sample_points
init|;
name|sample_points
condition|;
name|sample_points
operator|=
name|g_list_next
argument_list|(
name|sample_points
argument_list|)
control|)
block|{
name|GimpSamplePoint
modifier|*
name|sample_point
init|=
name|sample_points
operator|->
name|data
decl_stmt|;
if|if
condition|(
operator|*
name|sample_point_found
condition|)
comment|/* this is the first guide after the found one */
return|return
name|sample_point
return|;
if|if
condition|(
name|gimp_sample_point_get_ID
argument_list|(
name|sample_point
argument_list|)
operator|==
name|id
condition|)
comment|/* found it, next one will be returned */
operator|*
name|sample_point_found
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

