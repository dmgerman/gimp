begin_unit|revision:0.9.5;language:C;cregit-version:0.0.1
begin_comment
comment|/* The GIMP -- an image manipulation program  * Copyright (C) 1995 Spencer Kimball and Peter Mattis  *  * This program is free software; you can redistribute it and/or modify  * it under the terms of the GNU General Public License as published by  * the Free Software Foundation; either version 2 of the License, or  * (at your option) any later version.  *  * This program is distributed in the hope that it will be useful,  * but WITHOUT ANY WARRANTY; without even the implied warranty of  * MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the  * GNU General Public License for more details.  *  * You should have received a copy of the GNU General Public License  * along with this program; if not, write to the Free Software  * Foundation, Inc., 59 Temple Place - Suite 330, Boston, MA 02111-1307, USA.  */
end_comment

begin_include
include|#
directive|include
file|"appenv.h"
end_include

begin_include
include|#
directive|include
file|"drawable.h"
end_include

begin_include
include|#
directive|include
file|"desaturate.h"
end_include

begin_include
include|#
directive|include
file|"paint_funcs.h"
end_include

begin_include
include|#
directive|include
file|"gimage.h"
end_include

begin_include
include|#
directive|include
file|"config.h"
end_include

begin_include
include|#
directive|include
file|"libgimp/gimpintl.h"
end_include

begin_function
name|void
DECL|function|image_desaturate (GimpImage * gimage)
name|image_desaturate
parameter_list|(
name|GimpImage
modifier|*
name|gimage
parameter_list|)
block|{
name|GimpDrawable
modifier|*
name|drawable
decl_stmt|;
name|drawable
operator|=
name|gimage_active_drawable
argument_list|(
name|gimage
argument_list|)
expr_stmt|;
if|if
condition|(
operator|!
name|drawable_color
argument_list|(
name|drawable
argument_list|)
condition|)
block|{
name|g_message
argument_list|(
name|_
argument_list|(
literal|"Desaturate operates only on RGB color drawables."
argument_list|)
argument_list|)
expr_stmt|;
return|return;
block|}
name|desaturate
argument_list|(
name|drawable
argument_list|)
expr_stmt|;
block|}
end_function

begin_comment
comment|/*  Desaturater  */
end_comment

begin_function
name|void
DECL|function|desaturate (GimpDrawable * drawable)
name|desaturate
parameter_list|(
name|GimpDrawable
modifier|*
name|drawable
parameter_list|)
block|{
name|PixelRegion
name|srcPR
decl_stmt|,
name|destPR
decl_stmt|;
name|unsigned
name|char
modifier|*
name|src
decl_stmt|,
modifier|*
name|s
decl_stmt|;
name|unsigned
name|char
modifier|*
name|dest
decl_stmt|,
modifier|*
name|d
decl_stmt|;
name|int
name|h
decl_stmt|,
name|j
decl_stmt|;
name|int
name|lightness
decl_stmt|,
name|min
decl_stmt|,
name|max
decl_stmt|;
name|int
name|has_alpha
decl_stmt|;
name|void
modifier|*
name|pr
decl_stmt|;
name|int
name|x1
decl_stmt|,
name|y1
decl_stmt|,
name|x2
decl_stmt|,
name|y2
decl_stmt|;
if|if
condition|(
operator|!
name|drawable
condition|)
return|return;
name|has_alpha
operator|=
name|drawable_has_alpha
argument_list|(
name|drawable
argument_list|)
expr_stmt|;
name|drawable_mask_bounds
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
name|pixel_region_init
argument_list|(
operator|&
name|srcPR
argument_list|,
name|drawable_data
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
name|pixel_region_init
argument_list|(
operator|&
name|destPR
argument_list|,
name|drawable_shadow
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
name|TRUE
argument_list|)
expr_stmt|;
for|for
control|(
name|pr
operator|=
name|pixel_regions_register
argument_list|(
literal|2
argument_list|,
operator|&
name|srcPR
argument_list|,
operator|&
name|destPR
argument_list|)
init|;
name|pr
operator|!=
name|NULL
condition|;
name|pr
operator|=
name|pixel_regions_process
argument_list|(
name|pr
argument_list|)
control|)
block|{
name|src
operator|=
name|srcPR
operator|.
name|data
expr_stmt|;
name|dest
operator|=
name|destPR
operator|.
name|data
expr_stmt|;
name|h
operator|=
name|srcPR
operator|.
name|h
expr_stmt|;
while|while
condition|(
name|h
operator|--
condition|)
block|{
name|s
operator|=
name|src
expr_stmt|;
name|d
operator|=
name|dest
expr_stmt|;
for|for
control|(
name|j
operator|=
literal|0
init|;
name|j
operator|<
name|srcPR
operator|.
name|w
condition|;
name|j
operator|++
control|)
block|{
name|max
operator|=
name|MAX
argument_list|(
name|s
index|[
name|RED_PIX
index|]
argument_list|,
name|s
index|[
name|GREEN_PIX
index|]
argument_list|)
expr_stmt|;
name|max
operator|=
name|MAX
argument_list|(
name|max
argument_list|,
name|s
index|[
name|BLUE_PIX
index|]
argument_list|)
expr_stmt|;
name|min
operator|=
name|MIN
argument_list|(
name|s
index|[
name|RED_PIX
index|]
argument_list|,
name|s
index|[
name|GREEN_PIX
index|]
argument_list|)
expr_stmt|;
name|min
operator|=
name|MIN
argument_list|(
name|min
argument_list|,
name|s
index|[
name|BLUE_PIX
index|]
argument_list|)
expr_stmt|;
name|lightness
operator|=
operator|(
name|max
operator|+
name|min
operator|)
operator|/
literal|2
expr_stmt|;
name|d
index|[
name|RED_PIX
index|]
operator|=
name|lightness
expr_stmt|;
name|d
index|[
name|GREEN_PIX
index|]
operator|=
name|lightness
expr_stmt|;
name|d
index|[
name|BLUE_PIX
index|]
operator|=
name|lightness
expr_stmt|;
if|if
condition|(
name|has_alpha
condition|)
name|d
index|[
name|ALPHA_PIX
index|]
operator|=
name|s
index|[
name|ALPHA_PIX
index|]
expr_stmt|;
name|d
operator|+=
name|destPR
operator|.
name|bytes
expr_stmt|;
name|s
operator|+=
name|srcPR
operator|.
name|bytes
expr_stmt|;
block|}
name|src
operator|+=
name|srcPR
operator|.
name|rowstride
expr_stmt|;
name|dest
operator|+=
name|destPR
operator|.
name|rowstride
expr_stmt|;
block|}
block|}
name|drawable_merge_shadow
argument_list|(
name|drawable
argument_list|,
name|TRUE
argument_list|)
expr_stmt|;
name|drawable_update
argument_list|(
name|drawable
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
argument_list|)
expr_stmt|;
block|}
end_function

end_unit

