begin_unit|revision:0.9.5;language:C;cregit-version:0.0.1
begin_comment
comment|/* The GIMP -- an image manipulation program  * Copyright (C) 1995-2001 Spencer Kimball, Peter Mattis, and others  *  * This program is free software; you can redistribute it and/or modify  * it under the terms of the GNU General Public License as published by  * the Free Software Foundation; either version 2 of the License, or  * (at your option) any later version.  *  * This program is distributed in the hope that it will be useful,  * but WITHOUT ANY WARRANTY; without even the implied warranty of  * MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the  * GNU General Public License for more details.  *  * You should have received a copy of the GNU General Public License  * along with this program; if not, write to the Free Software  * Foundation, Inc., 59 Temple Place - Suite 330, Boston, MA 02111-1307, USA.  */
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
file|"core/gimpdrawable.h"
end_include

begin_include
include|#
directive|include
file|"core/gimpimage.h"
end_include

begin_include
include|#
directive|include
file|"core/gimpimage-pick-color.h"
end_include

begin_include
include|#
directive|include
file|"core/gimppickable.h"
end_include

begin_function
name|gboolean
DECL|function|gimp_image_pick_color (GimpImage * gimage,GimpDrawable * drawable,gint x,gint y,gboolean sample_merged,gboolean sample_average,gdouble average_radius,GimpImageType * sample_type,GimpRGB * color,gint * color_index)
name|gimp_image_pick_color
parameter_list|(
name|GimpImage
modifier|*
name|gimage
parameter_list|,
name|GimpDrawable
modifier|*
name|drawable
parameter_list|,
name|gint
name|x
parameter_list|,
name|gint
name|y
parameter_list|,
name|gboolean
name|sample_merged
parameter_list|,
name|gboolean
name|sample_average
parameter_list|,
name|gdouble
name|average_radius
parameter_list|,
name|GimpImageType
modifier|*
name|sample_type
parameter_list|,
name|GimpRGB
modifier|*
name|color
parameter_list|,
name|gint
modifier|*
name|color_index
parameter_list|)
block|{
name|GimpPickable
modifier|*
name|pickable
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
name|drawable
operator|==
name|NULL
operator|||
name|GIMP_IS_DRAWABLE
argument_list|(
name|drawable
argument_list|)
argument_list|,
name|FALSE
argument_list|)
expr_stmt|;
name|g_return_val_if_fail
argument_list|(
name|drawable
operator|==
name|NULL
operator|||
name|gimp_item_get_image
argument_list|(
name|GIMP_ITEM
argument_list|(
name|drawable
argument_list|)
argument_list|)
operator|==
name|gimage
argument_list|,
name|FALSE
argument_list|)
expr_stmt|;
if|if
condition|(
operator|!
name|sample_merged
condition|)
block|{
if|if
condition|(
operator|!
name|drawable
condition|)
name|drawable
operator|=
name|gimp_image_active_drawable
argument_list|(
name|gimage
argument_list|)
expr_stmt|;
if|if
condition|(
operator|!
name|drawable
condition|)
return|return
name|FALSE
return|;
block|}
if|if
condition|(
name|sample_merged
condition|)
block|{
name|pickable
operator|=
name|GIMP_PICKABLE
argument_list|(
name|gimage
operator|->
name|projection
argument_list|)
expr_stmt|;
block|}
else|else
block|{
name|gint
name|off_x
decl_stmt|,
name|off_y
decl_stmt|;
name|gimp_item_offsets
argument_list|(
name|GIMP_ITEM
argument_list|(
name|drawable
argument_list|)
argument_list|,
operator|&
name|off_x
argument_list|,
operator|&
name|off_y
argument_list|)
expr_stmt|;
name|x
operator|-=
name|off_x
expr_stmt|;
name|y
operator|-=
name|off_y
expr_stmt|;
name|pickable
operator|=
name|GIMP_PICKABLE
argument_list|(
name|drawable
argument_list|)
expr_stmt|;
block|}
if|if
condition|(
name|sample_type
condition|)
operator|*
name|sample_type
operator|=
name|gimp_pickable_get_image_type
argument_list|(
name|pickable
argument_list|)
expr_stmt|;
return|return
name|gimp_pickable_pick_color
argument_list|(
name|pickable
argument_list|,
name|x
argument_list|,
name|y
argument_list|,
name|sample_average
argument_list|,
name|average_radius
argument_list|,
name|color
argument_list|,
name|color_index
argument_list|)
return|;
block|}
end_function

end_unit

