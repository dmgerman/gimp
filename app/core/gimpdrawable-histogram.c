begin_unit|revision:0.9.5;language:C;cregit-version:0.0.1
begin_comment
comment|/* GIMP - The GNU Image Manipulation Program  * Copyright (C) 1995 Spencer Kimball and Peter Mattis  *  * gimphistogram module Copyright (C) 1999 Jay Cox<jaycox@gimp.org>  *  * This program is free software; you can redistribute it and/or modify  * it under the terms of the GNU General Public License as published by  * the Free Software Foundation; either version 2 of the License, or  * (at your option) any later version.  *  * This program is distributed in the hope that it will be useful,  * but WITHOUT ANY WARRANTY; without even the implied warranty of  * MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the  * GNU General Public License for more details.  *  * You should have received a copy of the GNU General Public License  * along with this program; if not, write to the Free Software  * Foundation, Inc., 59 Temple Place - Suite 330, Boston, MA 02111-1307, USA.  */
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
file|"base/gimphistogram.h"
end_include

begin_include
include|#
directive|include
file|"base/pixel-region.h"
end_include

begin_include
include|#
directive|include
file|"gimpdrawable.h"
end_include

begin_include
include|#
directive|include
file|"gimpdrawable-histogram.h"
end_include

begin_include
include|#
directive|include
file|"gimpimage.h"
end_include

begin_function
name|void
DECL|function|gimp_drawable_calculate_histogram (GimpDrawable * drawable,GimpHistogram * histogram)
name|gimp_drawable_calculate_histogram
parameter_list|(
name|GimpDrawable
modifier|*
name|drawable
parameter_list|,
name|GimpHistogram
modifier|*
name|histogram
parameter_list|)
block|{
name|PixelRegion
name|region
decl_stmt|;
name|PixelRegion
name|mask
decl_stmt|;
name|gint
name|x1
decl_stmt|,
name|y1
decl_stmt|,
name|x2
decl_stmt|,
name|y2
decl_stmt|;
name|gboolean
name|have_mask
decl_stmt|;
name|g_return_if_fail
argument_list|(
name|GIMP_IS_DRAWABLE
argument_list|(
name|drawable
argument_list|)
argument_list|)
expr_stmt|;
name|g_return_if_fail
argument_list|(
name|gimp_item_is_attached
argument_list|(
name|GIMP_ITEM
argument_list|(
name|drawable
argument_list|)
argument_list|)
argument_list|)
expr_stmt|;
name|g_return_if_fail
argument_list|(
name|histogram
operator|!=
name|NULL
argument_list|)
expr_stmt|;
name|have_mask
operator|=
name|gimp_drawable_mask_bounds
argument_list|(
name|drawable
argument_list|,
operator|&
name|x1
argument_list|,
operator|&
name|y1
argument_list|,
operator|&
name|x2
argument_list|,
operator|&
name|y2
argument_list|)
expr_stmt|;
if|if
condition|(
operator|(
name|x1
operator|==
name|x2
operator|)
operator|||
operator|(
name|y1
operator|==
name|y2
operator|)
condition|)
return|return;
name|pixel_region_init
argument_list|(
operator|&
name|region
argument_list|,
name|gimp_drawable_get_tiles
argument_list|(
name|drawable
argument_list|)
argument_list|,
name|x1
argument_list|,
name|y1
argument_list|,
operator|(
name|x2
operator|-
name|x1
operator|)
argument_list|,
operator|(
name|y2
operator|-
name|y1
operator|)
argument_list|,
name|FALSE
argument_list|)
expr_stmt|;
if|if
condition|(
name|have_mask
condition|)
block|{
name|GimpChannel
modifier|*
name|sel_mask
decl_stmt|;
name|GimpImage
modifier|*
name|image
decl_stmt|;
name|gint
name|off_x
decl_stmt|,
name|off_y
decl_stmt|;
name|image
operator|=
name|gimp_item_get_image
argument_list|(
name|GIMP_ITEM
argument_list|(
name|drawable
argument_list|)
argument_list|)
expr_stmt|;
name|sel_mask
operator|=
name|gimp_image_get_mask
argument_list|(
name|image
argument_list|)
expr_stmt|;
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
name|pixel_region_init
argument_list|(
operator|&
name|mask
argument_list|,
name|gimp_drawable_get_tiles
argument_list|(
name|GIMP_DRAWABLE
argument_list|(
name|sel_mask
argument_list|)
argument_list|)
argument_list|,
name|x1
operator|+
name|off_x
argument_list|,
name|y1
operator|+
name|off_y
argument_list|,
operator|(
name|x2
operator|-
name|x1
operator|)
argument_list|,
operator|(
name|y2
operator|-
name|y1
operator|)
argument_list|,
name|FALSE
argument_list|)
expr_stmt|;
name|gimp_histogram_calculate
argument_list|(
name|histogram
argument_list|,
operator|&
name|region
argument_list|,
operator|&
name|mask
argument_list|)
expr_stmt|;
block|}
else|else
block|{
name|gimp_histogram_calculate
argument_list|(
name|histogram
argument_list|,
operator|&
name|region
argument_list|,
name|NULL
argument_list|)
expr_stmt|;
block|}
block|}
end_function

end_unit

