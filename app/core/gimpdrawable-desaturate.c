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
file|"libgimpcolor/gimpcolor.h"
end_include

begin_include
include|#
directive|include
file|"core-types.h"
end_include

begin_include
include|#
directive|include
file|"base/pixel-processor.h"
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
file|"gimpdrawable-desaturate.h"
end_include

begin_include
include|#
directive|include
file|"gimpimage.h"
end_include

begin_include
include|#
directive|include
file|"gimp-intl.h"
end_include

begin_function_decl
specifier|static
name|void
name|desaturate_region_lightness
parameter_list|(
name|gpointer
name|data
parameter_list|,
name|PixelRegion
modifier|*
name|srcPR
parameter_list|,
name|PixelRegion
modifier|*
name|destPR
parameter_list|)
function_decl|;
end_function_decl

begin_function_decl
specifier|static
name|void
name|desaturate_region_luminosity
parameter_list|(
name|gpointer
name|data
parameter_list|,
name|PixelRegion
modifier|*
name|srcPR
parameter_list|,
name|PixelRegion
modifier|*
name|destPR
parameter_list|)
function_decl|;
end_function_decl

begin_function_decl
specifier|static
name|void
name|desaturate_region_average
parameter_list|(
name|gpointer
name|data
parameter_list|,
name|PixelRegion
modifier|*
name|srcPR
parameter_list|,
name|PixelRegion
modifier|*
name|destPR
parameter_list|)
function_decl|;
end_function_decl

begin_function
name|void
DECL|function|gimp_drawable_desaturate (GimpDrawable * drawable,GimpDesaturateMode mode)
name|gimp_drawable_desaturate
parameter_list|(
name|GimpDrawable
modifier|*
name|drawable
parameter_list|,
name|GimpDesaturateMode
name|mode
parameter_list|)
block|{
name|PixelRegion
name|srcPR
decl_stmt|,
name|destPR
decl_stmt|;
name|PixelProcessorFunc
name|function
decl_stmt|;
name|gint
name|x
decl_stmt|,
name|y
decl_stmt|;
name|gint
name|width
decl_stmt|,
name|height
decl_stmt|;
name|gboolean
name|has_alpha
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
name|gimp_drawable_is_rgb
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
if|if
condition|(
operator|!
name|gimp_drawable_mask_intersect
argument_list|(
name|drawable
argument_list|,
operator|&
name|x
argument_list|,
operator|&
name|y
argument_list|,
operator|&
name|width
argument_list|,
operator|&
name|height
argument_list|)
condition|)
return|return;
switch|switch
condition|(
name|mode
condition|)
block|{
case|case
name|GIMP_DESATURATE_LIGHTNESS
case|:
name|function
operator|=
operator|(
name|PixelProcessorFunc
operator|)
name|desaturate_region_lightness
expr_stmt|;
break|break;
break|break;
case|case
name|GIMP_DESATURATE_LUMINOSITY
case|:
name|function
operator|=
operator|(
name|PixelProcessorFunc
operator|)
name|desaturate_region_luminosity
expr_stmt|;
break|break;
case|case
name|GIMP_DESATURATE_AVERAGE
case|:
name|function
operator|=
operator|(
name|PixelProcessorFunc
operator|)
name|desaturate_region_average
expr_stmt|;
break|break;
default|default:
name|g_return_if_reached
argument_list|()
expr_stmt|;
return|return;
block|}
name|has_alpha
operator|=
name|gimp_drawable_has_alpha
argument_list|(
name|drawable
argument_list|)
expr_stmt|;
name|pixel_region_init
argument_list|(
operator|&
name|srcPR
argument_list|,
name|gimp_drawable_get_tiles
argument_list|(
name|drawable
argument_list|)
argument_list|,
name|x
argument_list|,
name|y
argument_list|,
name|width
argument_list|,
name|height
argument_list|,
name|FALSE
argument_list|)
expr_stmt|;
name|pixel_region_init
argument_list|(
operator|&
name|destPR
argument_list|,
name|gimp_drawable_shadow
argument_list|(
name|drawable
argument_list|)
argument_list|,
name|x
argument_list|,
name|y
argument_list|,
name|width
argument_list|,
name|height
argument_list|,
name|TRUE
argument_list|)
expr_stmt|;
name|pixel_regions_process_parallel
argument_list|(
name|function
argument_list|,
name|GINT_TO_POINTER
argument_list|(
name|has_alpha
argument_list|)
argument_list|,
literal|2
argument_list|,
operator|&
name|srcPR
argument_list|,
operator|&
name|destPR
argument_list|)
expr_stmt|;
name|gimp_drawable_merge_shadow
argument_list|(
name|drawable
argument_list|,
name|TRUE
argument_list|,
name|_
argument_list|(
literal|"Desaturate"
argument_list|)
argument_list|)
expr_stmt|;
name|gimp_drawable_update
argument_list|(
name|drawable
argument_list|,
name|x
argument_list|,
name|y
argument_list|,
name|width
argument_list|,
name|height
argument_list|)
expr_stmt|;
block|}
end_function

begin_function
specifier|static
name|void
DECL|function|desaturate_region_lightness (gpointer data,PixelRegion * srcPR,PixelRegion * destPR)
name|desaturate_region_lightness
parameter_list|(
name|gpointer
name|data
parameter_list|,
name|PixelRegion
modifier|*
name|srcPR
parameter_list|,
name|PixelRegion
modifier|*
name|destPR
parameter_list|)
block|{
specifier|const
name|guchar
modifier|*
name|src
init|=
name|srcPR
operator|->
name|data
decl_stmt|;
name|guchar
modifier|*
name|dest
init|=
name|destPR
operator|->
name|data
decl_stmt|;
name|gint
name|h
init|=
name|srcPR
operator|->
name|h
decl_stmt|;
name|gboolean
name|has_alpha
init|=
name|GPOINTER_TO_INT
argument_list|(
name|data
argument_list|)
decl_stmt|;
while|while
condition|(
name|h
operator|--
condition|)
block|{
specifier|const
name|guchar
modifier|*
name|s
init|=
name|src
decl_stmt|;
name|guchar
modifier|*
name|d
init|=
name|dest
decl_stmt|;
name|gint
name|j
decl_stmt|;
for|for
control|(
name|j
operator|=
literal|0
init|;
name|j
operator|<
name|srcPR
operator|->
name|w
condition|;
name|j
operator|++
control|)
block|{
name|gint
name|min
decl_stmt|,
name|max
decl_stmt|;
name|gint
name|lightness
decl_stmt|;
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
operator|->
name|bytes
expr_stmt|;
name|s
operator|+=
name|srcPR
operator|->
name|bytes
expr_stmt|;
block|}
name|src
operator|+=
name|srcPR
operator|->
name|rowstride
expr_stmt|;
name|dest
operator|+=
name|destPR
operator|->
name|rowstride
expr_stmt|;
block|}
block|}
end_function

begin_function
specifier|static
name|void
DECL|function|desaturate_region_luminosity (gpointer data,PixelRegion * srcPR,PixelRegion * destPR)
name|desaturate_region_luminosity
parameter_list|(
name|gpointer
name|data
parameter_list|,
name|PixelRegion
modifier|*
name|srcPR
parameter_list|,
name|PixelRegion
modifier|*
name|destPR
parameter_list|)
block|{
specifier|const
name|guchar
modifier|*
name|src
init|=
name|srcPR
operator|->
name|data
decl_stmt|;
name|guchar
modifier|*
name|dest
init|=
name|destPR
operator|->
name|data
decl_stmt|;
name|gint
name|h
init|=
name|srcPR
operator|->
name|h
decl_stmt|;
name|gboolean
name|has_alpha
init|=
name|GPOINTER_TO_INT
argument_list|(
name|data
argument_list|)
decl_stmt|;
while|while
condition|(
name|h
operator|--
condition|)
block|{
specifier|const
name|guchar
modifier|*
name|s
init|=
name|src
decl_stmt|;
name|guchar
modifier|*
name|d
init|=
name|dest
decl_stmt|;
name|gint
name|j
decl_stmt|;
for|for
control|(
name|j
operator|=
literal|0
init|;
name|j
operator|<
name|srcPR
operator|->
name|w
condition|;
name|j
operator|++
control|)
block|{
name|gint
name|luminosity
init|=
name|GIMP_RGB_LUMINANCE
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
argument_list|,
name|s
index|[
name|BLUE_PIX
index|]
argument_list|)
operator|+
literal|0.5
decl_stmt|;
name|d
index|[
name|RED_PIX
index|]
operator|=
name|luminosity
expr_stmt|;
name|d
index|[
name|GREEN_PIX
index|]
operator|=
name|luminosity
expr_stmt|;
name|d
index|[
name|BLUE_PIX
index|]
operator|=
name|luminosity
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
operator|->
name|bytes
expr_stmt|;
name|s
operator|+=
name|srcPR
operator|->
name|bytes
expr_stmt|;
block|}
name|src
operator|+=
name|srcPR
operator|->
name|rowstride
expr_stmt|;
name|dest
operator|+=
name|destPR
operator|->
name|rowstride
expr_stmt|;
block|}
block|}
end_function

begin_function
specifier|static
name|void
DECL|function|desaturate_region_average (gpointer data,PixelRegion * srcPR,PixelRegion * destPR)
name|desaturate_region_average
parameter_list|(
name|gpointer
name|data
parameter_list|,
name|PixelRegion
modifier|*
name|srcPR
parameter_list|,
name|PixelRegion
modifier|*
name|destPR
parameter_list|)
block|{
specifier|const
name|guchar
modifier|*
name|src
init|=
name|srcPR
operator|->
name|data
decl_stmt|;
name|guchar
modifier|*
name|dest
init|=
name|destPR
operator|->
name|data
decl_stmt|;
name|gint
name|h
init|=
name|srcPR
operator|->
name|h
decl_stmt|;
name|gboolean
name|has_alpha
init|=
name|GPOINTER_TO_INT
argument_list|(
name|data
argument_list|)
decl_stmt|;
while|while
condition|(
name|h
operator|--
condition|)
block|{
specifier|const
name|guchar
modifier|*
name|s
init|=
name|src
decl_stmt|;
name|guchar
modifier|*
name|d
init|=
name|dest
decl_stmt|;
name|gint
name|j
decl_stmt|;
for|for
control|(
name|j
operator|=
literal|0
init|;
name|j
operator|<
name|srcPR
operator|->
name|w
condition|;
name|j
operator|++
control|)
block|{
name|gint
name|average
init|=
operator|(
name|s
index|[
name|RED_PIX
index|]
operator|+
name|s
index|[
name|GREEN_PIX
index|]
operator|+
name|s
index|[
name|BLUE_PIX
index|]
operator|+
literal|1
operator|)
operator|/
literal|3
decl_stmt|;
name|d
index|[
name|RED_PIX
index|]
operator|=
name|average
expr_stmt|;
name|d
index|[
name|GREEN_PIX
index|]
operator|=
name|average
expr_stmt|;
name|d
index|[
name|BLUE_PIX
index|]
operator|=
name|average
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
operator|->
name|bytes
expr_stmt|;
name|s
operator|+=
name|srcPR
operator|->
name|bytes
expr_stmt|;
block|}
name|src
operator|+=
name|srcPR
operator|->
name|rowstride
expr_stmt|;
name|dest
operator|+=
name|destPR
operator|->
name|rowstride
expr_stmt|;
block|}
block|}
end_function

end_unit

