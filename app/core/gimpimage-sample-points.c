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
file|"gimp-intl.h"
end_include

begin_comment
comment|/*  public functions  */
end_comment

begin_function
name|GimpSamplePoint
modifier|*
DECL|function|gimp_image_add_sample_point_at_pos (GimpImage * gimage,gint x,gint y,gboolean push_undo)
name|gimp_image_add_sample_point_at_pos
parameter_list|(
name|GimpImage
modifier|*
name|gimage
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
name|gimage
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
name|gimage
operator|->
name|width
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
name|gimage
operator|->
name|height
argument_list|,
name|NULL
argument_list|)
expr_stmt|;
name|sample_point
operator|=
name|g_new0
argument_list|(
name|GimpSamplePoint
argument_list|,
literal|1
argument_list|)
expr_stmt|;
name|sample_point
operator|->
name|ref_count
operator|=
literal|1
expr_stmt|;
name|sample_point
operator|->
name|x
operator|=
operator|-
literal|1
expr_stmt|;
name|sample_point
operator|->
name|y
operator|=
operator|-
literal|1
expr_stmt|;
name|sample_point
operator|->
name|sample_point_ID
operator|=
name|gimage
operator|->
name|gimp
operator|->
name|next_sample_point_ID
operator|++
expr_stmt|;
if|if
condition|(
name|push_undo
condition|)
name|gimp_image_undo_push_image_sample_point
argument_list|(
name|gimage
argument_list|,
name|_
argument_list|(
literal|"Add Sample_Point"
argument_list|)
argument_list|,
name|sample_point
argument_list|)
expr_stmt|;
name|gimp_image_add_sample_point
argument_list|(
name|gimage
argument_list|,
name|sample_point
argument_list|,
name|x
argument_list|,
name|y
argument_list|)
expr_stmt|;
name|gimp_image_sample_point_unref
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
name|GimpSamplePoint
modifier|*
DECL|function|gimp_image_sample_point_ref (GimpSamplePoint * sample_point)
name|gimp_image_sample_point_ref
parameter_list|(
name|GimpSamplePoint
modifier|*
name|sample_point
parameter_list|)
block|{
name|g_return_val_if_fail
argument_list|(
name|sample_point
operator|!=
name|NULL
argument_list|,
name|NULL
argument_list|)
expr_stmt|;
name|sample_point
operator|->
name|ref_count
operator|++
expr_stmt|;
return|return
name|sample_point
return|;
block|}
end_function

begin_function
name|void
DECL|function|gimp_image_sample_point_unref (GimpSamplePoint * sample_point)
name|gimp_image_sample_point_unref
parameter_list|(
name|GimpSamplePoint
modifier|*
name|sample_point
parameter_list|)
block|{
name|g_return_if_fail
argument_list|(
name|sample_point
operator|!=
name|NULL
argument_list|)
expr_stmt|;
name|sample_point
operator|->
name|ref_count
operator|--
expr_stmt|;
if|if
condition|(
name|sample_point
operator|->
name|ref_count
operator|<
literal|1
condition|)
name|g_free
argument_list|(
name|sample_point
argument_list|)
expr_stmt|;
block|}
end_function

begin_function
name|void
DECL|function|gimp_image_add_sample_point (GimpImage * gimage,GimpSamplePoint * sample_point,gint x,gint y)
name|gimp_image_add_sample_point
parameter_list|(
name|GimpImage
modifier|*
name|gimage
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
name|g_return_if_fail
argument_list|(
name|GIMP_IS_IMAGE
argument_list|(
name|gimage
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
name|gimage
operator|->
name|width
argument_list|)
expr_stmt|;
name|g_return_if_fail
argument_list|(
name|y
operator|<
name|gimage
operator|->
name|height
argument_list|)
expr_stmt|;
name|gimage
operator|->
name|sample_points
operator|=
name|g_list_append
argument_list|(
name|gimage
operator|->
name|sample_points
argument_list|,
name|sample_point
argument_list|)
expr_stmt|;
name|sample_point
operator|->
name|x
operator|=
name|x
expr_stmt|;
name|sample_point
operator|->
name|y
operator|=
name|y
expr_stmt|;
name|gimp_image_sample_point_ref
argument_list|(
name|sample_point
argument_list|)
expr_stmt|;
name|gimp_image_update_sample_point
argument_list|(
name|gimage
argument_list|,
name|sample_point
argument_list|)
expr_stmt|;
block|}
end_function

begin_function
name|void
DECL|function|gimp_image_remove_sample_point (GimpImage * gimage,GimpSamplePoint * sample_point,gboolean push_undo)
name|gimp_image_remove_sample_point
parameter_list|(
name|GimpImage
modifier|*
name|gimage
parameter_list|,
name|GimpSamplePoint
modifier|*
name|sample_point
parameter_list|,
name|gboolean
name|push_undo
parameter_list|)
block|{
name|GList
modifier|*
name|list
decl_stmt|;
name|g_return_if_fail
argument_list|(
name|GIMP_IS_IMAGE
argument_list|(
name|gimage
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
name|gimp_image_update_sample_point
argument_list|(
name|gimage
argument_list|,
name|sample_point
argument_list|)
expr_stmt|;
if|if
condition|(
name|push_undo
condition|)
name|gimp_image_undo_push_image_sample_point
argument_list|(
name|gimage
argument_list|,
name|_
argument_list|(
literal|"Remove Sample Point"
argument_list|)
argument_list|,
name|sample_point
argument_list|)
expr_stmt|;
name|list
operator|=
name|g_list_find
argument_list|(
name|gimage
operator|->
name|sample_points
argument_list|,
name|sample_point
argument_list|)
expr_stmt|;
if|if
condition|(
name|list
condition|)
name|list
operator|=
name|g_list_next
argument_list|(
name|list
argument_list|)
expr_stmt|;
name|gimage
operator|->
name|sample_points
operator|=
name|g_list_remove
argument_list|(
name|gimage
operator|->
name|sample_points
argument_list|,
name|sample_point
argument_list|)
expr_stmt|;
name|sample_point
operator|->
name|x
operator|=
operator|-
literal|1
expr_stmt|;
name|sample_point
operator|->
name|y
operator|=
operator|-
literal|1
expr_stmt|;
name|gimp_image_sample_point_unref
argument_list|(
name|sample_point
argument_list|)
expr_stmt|;
while|while
condition|(
name|list
condition|)
block|{
name|gimp_image_update_sample_point
argument_list|(
name|gimage
argument_list|,
name|list
operator|->
name|data
argument_list|)
expr_stmt|;
name|list
operator|=
name|g_list_next
argument_list|(
name|list
argument_list|)
expr_stmt|;
block|}
block|}
end_function

begin_function
name|void
DECL|function|gimp_image_move_sample_point (GimpImage * gimage,GimpSamplePoint * sample_point,gint x,gint y,gboolean push_undo)
name|gimp_image_move_sample_point
parameter_list|(
name|GimpImage
modifier|*
name|gimage
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
name|gimage
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
name|gimage
operator|->
name|width
argument_list|)
expr_stmt|;
name|g_return_if_fail
argument_list|(
name|y
operator|<
name|gimage
operator|->
name|height
argument_list|)
expr_stmt|;
if|if
condition|(
name|push_undo
condition|)
name|gimp_image_undo_push_image_sample_point
argument_list|(
name|gimage
argument_list|,
name|_
argument_list|(
literal|"Move Sample Point"
argument_list|)
argument_list|,
name|sample_point
argument_list|)
expr_stmt|;
name|gimp_image_update_sample_point
argument_list|(
name|gimage
argument_list|,
name|sample_point
argument_list|)
expr_stmt|;
name|sample_point
operator|->
name|x
operator|=
name|x
expr_stmt|;
name|sample_point
operator|->
name|y
operator|=
name|y
expr_stmt|;
name|gimp_image_update_sample_point
argument_list|(
name|gimage
argument_list|,
name|sample_point
argument_list|)
expr_stmt|;
block|}
end_function

begin_function
name|GimpSamplePoint
modifier|*
DECL|function|gimp_image_find_sample_point (GimpImage * gimage,gdouble x,gdouble y,gdouble epsilon_x,gdouble epsilon_y)
name|gimp_image_find_sample_point
parameter_list|(
name|GimpImage
modifier|*
name|gimage
parameter_list|,
name|gdouble
name|x
parameter_list|,
name|gdouble
name|y
parameter_list|,
name|gdouble
name|epsilon_x
parameter_list|,
name|gdouble
name|epsilon_y
parameter_list|)
block|{
name|GList
modifier|*
name|list
decl_stmt|;
name|GimpSamplePoint
modifier|*
name|ret
init|=
name|NULL
decl_stmt|;
name|gdouble
name|mindist
init|=
name|G_MAXDOUBLE
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
name|epsilon_x
operator|>
literal|0
operator|&&
name|epsilon_y
operator|>
literal|0
argument_list|,
name|NULL
argument_list|)
expr_stmt|;
if|if
condition|(
name|x
operator|<
literal|0
operator|||
name|x
operator|>=
name|gimage
operator|->
name|width
operator|||
name|y
operator|<
literal|0
operator|||
name|y
operator|>=
name|gimage
operator|->
name|height
condition|)
block|{
return|return
name|NULL
return|;
block|}
for|for
control|(
name|list
operator|=
name|gimage
operator|->
name|sample_points
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
name|GimpSamplePoint
modifier|*
name|sample_point
init|=
name|list
operator|->
name|data
decl_stmt|;
name|gdouble
name|dist
decl_stmt|;
if|if
condition|(
name|sample_point
operator|->
name|x
operator|<
literal|0
operator|||
name|sample_point
operator|->
name|y
operator|<
literal|0
condition|)
continue|continue;
name|dist
operator|=
name|hypot
argument_list|(
operator|(
name|sample_point
operator|->
name|x
operator|+
literal|0.5
operator|)
operator|-
name|x
argument_list|,
operator|(
name|sample_point
operator|->
name|y
operator|+
literal|0.5
operator|)
operator|-
name|y
argument_list|)
expr_stmt|;
if|if
condition|(
name|dist
operator|<
name|MIN
argument_list|(
name|epsilon_y
argument_list|,
name|mindist
argument_list|)
condition|)
block|{
name|mindist
operator|=
name|dist
expr_stmt|;
name|ret
operator|=
name|sample_point
expr_stmt|;
block|}
block|}
return|return
name|ret
return|;
block|}
end_function

end_unit

