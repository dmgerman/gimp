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
file|"base/pixel-region.h"
end_include

begin_include
include|#
directive|include
file|"base/temp-buf.h"
end_include

begin_include
include|#
directive|include
file|"base/tile-manager.h"
end_include

begin_include
include|#
directive|include
file|"paint-funcs/paint-funcs.h"
end_include

begin_include
include|#
directive|include
file|"gimp.h"
end_include

begin_include
include|#
directive|include
file|"gimpchannel.h"
end_include

begin_include
include|#
directive|include
file|"gimpcontext.h"
end_include

begin_include
include|#
directive|include
file|"gimpdrawable.h"
end_include

begin_include
include|#
directive|include
file|"gimpdrawable-bucket-fill.h"
end_include

begin_include
include|#
directive|include
file|"gimpimage.h"
end_include

begin_include
include|#
directive|include
file|"gimpimage-contiguous-region.h"
end_include

begin_include
include|#
directive|include
file|"gimpimage-mask.h"
end_include

begin_include
include|#
directive|include
file|"gimppattern.h"
end_include

begin_include
include|#
directive|include
file|"gimprc.h"
end_include

begin_include
include|#
directive|include
file|"undo.h"
end_include

begin_include
include|#
directive|include
file|"libgimp/gimpintl.h"
end_include

begin_comment
comment|/*  local function prototypes  */
end_comment

begin_function_decl
specifier|static
name|void
name|gimp_drawable_bucket_fill_region
parameter_list|(
name|BucketFillMode
name|fill_mode
parameter_list|,
name|PixelRegion
modifier|*
name|bufPR
parameter_list|,
name|PixelRegion
modifier|*
name|maskPR
parameter_list|,
name|guchar
modifier|*
name|col
parameter_list|,
name|TempBuf
modifier|*
name|pattern
parameter_list|,
name|gint
name|off_x
parameter_list|,
name|gint
name|off_y
parameter_list|,
name|gboolean
name|has_alpha
parameter_list|)
function_decl|;
end_function_decl

begin_function_decl
specifier|static
name|void
name|gimp_drawable_bucket_fill_line_color
parameter_list|(
name|guchar
modifier|*
name|buf
parameter_list|,
name|guchar
modifier|*
name|mask
parameter_list|,
name|guchar
modifier|*
name|col
parameter_list|,
name|gboolean
name|has_alpha
parameter_list|,
name|gint
name|bytes
parameter_list|,
name|gint
name|width
parameter_list|)
function_decl|;
end_function_decl

begin_function_decl
specifier|static
name|void
name|gimp_drawable_bucket_fill_line_pattern
parameter_list|(
name|guchar
modifier|*
name|buf
parameter_list|,
name|guchar
modifier|*
name|mask
parameter_list|,
name|TempBuf
modifier|*
name|pattern
parameter_list|,
name|gboolean
name|has_alpha
parameter_list|,
name|gint
name|bytes
parameter_list|,
name|gint
name|x
parameter_list|,
name|gint
name|y
parameter_list|,
name|gint
name|width
parameter_list|)
function_decl|;
end_function_decl

begin_comment
comment|/*  public functions  */
end_comment

begin_function
name|void
DECL|function|gimp_drawable_bucket_fill (GimpDrawable * drawable,BucketFillMode fill_mode,gint paint_mode,gdouble opacity,gboolean fill_transparent,gdouble threshold,gboolean sample_merged,gdouble x,gdouble y)
name|gimp_drawable_bucket_fill
parameter_list|(
name|GimpDrawable
modifier|*
name|drawable
parameter_list|,
name|BucketFillMode
name|fill_mode
parameter_list|,
name|gint
name|paint_mode
parameter_list|,
name|gdouble
name|opacity
parameter_list|,
name|gboolean
name|fill_transparent
parameter_list|,
name|gdouble
name|threshold
parameter_list|,
name|gboolean
name|sample_merged
parameter_list|,
name|gdouble
name|x
parameter_list|,
name|gdouble
name|y
parameter_list|)
block|{
name|GimpImage
modifier|*
name|gimage
decl_stmt|;
name|GimpRGB
name|color
decl_stmt|;
name|GimpPattern
modifier|*
name|pattern
init|=
name|NULL
decl_stmt|;
name|g_return_if_fail
argument_list|(
name|GIMP_IS_DRAWABLE
argument_list|(
name|drawable
argument_list|)
argument_list|)
expr_stmt|;
name|gimage
operator|=
name|gimp_drawable_gimage
argument_list|(
name|drawable
argument_list|)
expr_stmt|;
name|g_return_if_fail
argument_list|(
name|GIMP_IS_IMAGE
argument_list|(
name|gimage
argument_list|)
argument_list|)
expr_stmt|;
if|if
condition|(
name|fill_mode
operator|==
name|FG_BUCKET_FILL
condition|)
block|{
name|gimp_context_get_foreground
argument_list|(
name|gimp_get_current_context
argument_list|(
name|gimage
operator|->
name|gimp
argument_list|)
argument_list|,
operator|&
name|color
argument_list|)
expr_stmt|;
block|}
elseif|else
if|if
condition|(
name|fill_mode
operator|==
name|BG_BUCKET_FILL
condition|)
block|{
name|gimp_context_get_background
argument_list|(
name|gimp_get_current_context
argument_list|(
name|gimage
operator|->
name|gimp
argument_list|)
argument_list|,
operator|&
name|color
argument_list|)
expr_stmt|;
block|}
elseif|else
if|if
condition|(
name|fill_mode
operator|==
name|PATTERN_BUCKET_FILL
condition|)
block|{
name|pattern
operator|=
name|gimp_context_get_pattern
argument_list|(
name|gimp_get_current_context
argument_list|(
name|gimage
operator|->
name|gimp
argument_list|)
argument_list|)
expr_stmt|;
if|if
condition|(
operator|!
name|pattern
condition|)
block|{
name|g_message
argument_list|(
name|_
argument_list|(
literal|"No patterns available for this operation."
argument_list|)
argument_list|)
expr_stmt|;
return|return;
block|}
block|}
else|else
block|{
name|g_warning
argument_list|(
literal|"%s: invalid fill_mode passed"
argument_list|,
name|G_GNUC_PRETTY_FUNCTION
argument_list|)
expr_stmt|;
return|return;
block|}
name|gimp_drawable_bucket_fill_full
argument_list|(
name|drawable
argument_list|,
name|fill_mode
argument_list|,
operator|&
name|color
argument_list|,
name|pattern
argument_list|,
name|paint_mode
argument_list|,
name|opacity
argument_list|,
name|TRUE
comment|/* do seed fill */
argument_list|,
name|fill_transparent
argument_list|,
name|threshold
argument_list|,
name|sample_merged
argument_list|,
name|x
argument_list|,
name|y
argument_list|)
expr_stmt|;
block|}
end_function

begin_function
name|void
DECL|function|gimp_drawable_bucket_fill_full (GimpDrawable * drawable,BucketFillMode fill_mode,const GimpRGB * color,GimpPattern * pattern,gint paint_mode,gdouble opacity,gboolean do_seed_fill,gboolean fill_transparent,gdouble threshold,gboolean sample_merged,gdouble x,gdouble y)
name|gimp_drawable_bucket_fill_full
parameter_list|(
name|GimpDrawable
modifier|*
name|drawable
parameter_list|,
name|BucketFillMode
name|fill_mode
parameter_list|,
specifier|const
name|GimpRGB
modifier|*
name|color
parameter_list|,
name|GimpPattern
modifier|*
name|pattern
parameter_list|,
name|gint
name|paint_mode
parameter_list|,
name|gdouble
name|opacity
parameter_list|,
name|gboolean
name|do_seed_fill
parameter_list|,
name|gboolean
name|fill_transparent
parameter_list|,
name|gdouble
name|threshold
parameter_list|,
name|gboolean
name|sample_merged
parameter_list|,
name|gdouble
name|x
parameter_list|,
name|gdouble
name|y
parameter_list|)
block|{
name|GimpImage
modifier|*
name|gimage
decl_stmt|;
name|TileManager
modifier|*
name|buf_tiles
decl_stmt|;
name|PixelRegion
name|bufPR
decl_stmt|,
name|maskPR
decl_stmt|;
name|GimpChannel
modifier|*
name|mask
init|=
name|NULL
decl_stmt|;
name|gint
name|bytes
decl_stmt|;
name|gboolean
name|has_alpha
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
name|guchar
name|col
index|[
name|MAX_CHANNELS
index|]
decl_stmt|;
name|TempBuf
modifier|*
name|pat_buf
init|=
name|NULL
decl_stmt|;
name|gboolean
name|new_buf
init|=
name|FALSE
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
name|fill_mode
operator|!=
name|PATTERN_BUCKET_FILL
operator|||
name|GIMP_IS_PATTERN
argument_list|(
name|pattern
argument_list|)
argument_list|)
expr_stmt|;
name|g_return_if_fail
argument_list|(
operator|(
name|fill_mode
operator|!=
name|FG_BUCKET_FILL
operator|&&
name|fill_mode
operator|!=
name|BG_BUCKET_FILL
operator|)
operator|||
name|color
operator|!=
name|NULL
argument_list|)
expr_stmt|;
name|gimage
operator|=
name|gimp_drawable_gimage
argument_list|(
name|drawable
argument_list|)
expr_stmt|;
name|g_return_if_fail
argument_list|(
name|GIMP_IS_IMAGE
argument_list|(
name|gimage
argument_list|)
argument_list|)
expr_stmt|;
if|if
condition|(
name|fill_mode
operator|==
name|FG_BUCKET_FILL
operator|||
name|fill_mode
operator|==
name|BG_BUCKET_FILL
condition|)
block|{
name|guchar
name|tmp_col
index|[
name|MAX_CHANNELS
index|]
decl_stmt|;
name|gimp_rgb_get_uchar
argument_list|(
name|color
argument_list|,
operator|&
name|tmp_col
index|[
literal|0
index|]
argument_list|,
operator|&
name|tmp_col
index|[
literal|1
index|]
argument_list|,
operator|&
name|tmp_col
index|[
literal|2
index|]
argument_list|)
expr_stmt|;
name|gimp_image_transform_color
argument_list|(
name|gimage
argument_list|,
name|drawable
argument_list|,
name|tmp_col
argument_list|,
name|col
argument_list|,
name|GIMP_RGB
argument_list|)
expr_stmt|;
block|}
elseif|else
if|if
condition|(
name|fill_mode
operator|==
name|PATTERN_BUCKET_FILL
condition|)
block|{
comment|/*  If the pattern doesn't match the image in terms of color type,        *  transform it.  (ie  pattern is RGB, image is indexed)        */
if|if
condition|(
operator|(
operator|(
name|pattern
operator|->
name|mask
operator|->
name|bytes
operator|==
literal|3
operator|)
operator|&&
operator|!
name|gimp_drawable_is_rgb
argument_list|(
name|drawable
argument_list|)
operator|)
operator|||
operator|(
operator|(
name|pattern
operator|->
name|mask
operator|->
name|bytes
operator|==
literal|1
operator|)
operator|&&
operator|!
name|gimp_drawable_is_gray
argument_list|(
name|drawable
argument_list|)
operator|)
condition|)
block|{
name|guchar
modifier|*
name|d1
decl_stmt|,
modifier|*
name|d2
decl_stmt|;
name|gint
name|size
decl_stmt|;
if|if
condition|(
operator|(
name|pattern
operator|->
name|mask
operator|->
name|bytes
operator|==
literal|1
operator|)
operator|&&
name|gimp_drawable_is_rgb
argument_list|(
name|drawable
argument_list|)
condition|)
name|pat_buf
operator|=
name|temp_buf_new
argument_list|(
name|pattern
operator|->
name|mask
operator|->
name|width
argument_list|,
name|pattern
operator|->
name|mask
operator|->
name|height
argument_list|,
literal|3
argument_list|,
literal|0
argument_list|,
literal|0
argument_list|,
name|NULL
argument_list|)
expr_stmt|;
else|else
name|pat_buf
operator|=
name|temp_buf_new
argument_list|(
name|pattern
operator|->
name|mask
operator|->
name|width
argument_list|,
name|pattern
operator|->
name|mask
operator|->
name|height
argument_list|,
literal|1
argument_list|,
literal|0
argument_list|,
literal|0
argument_list|,
name|NULL
argument_list|)
expr_stmt|;
name|d1
operator|=
name|temp_buf_data
argument_list|(
name|pattern
operator|->
name|mask
argument_list|)
expr_stmt|;
name|d2
operator|=
name|temp_buf_data
argument_list|(
name|pat_buf
argument_list|)
expr_stmt|;
name|size
operator|=
name|pattern
operator|->
name|mask
operator|->
name|width
operator|*
name|pattern
operator|->
name|mask
operator|->
name|height
expr_stmt|;
while|while
condition|(
name|size
operator|--
condition|)
block|{
name|gimp_image_transform_color
argument_list|(
name|gimage
argument_list|,
name|drawable
argument_list|,
name|d1
argument_list|,
name|d2
argument_list|,
operator|(
name|pattern
operator|->
name|mask
operator|->
name|bytes
operator|==
literal|3
operator|)
condition|?
name|GIMP_RGB
else|:
name|GIMP_GRAY
argument_list|)
expr_stmt|;
name|d1
operator|+=
name|pattern
operator|->
name|mask
operator|->
name|bytes
expr_stmt|;
name|d2
operator|+=
name|pat_buf
operator|->
name|bytes
expr_stmt|;
block|}
name|new_buf
operator|=
name|TRUE
expr_stmt|;
block|}
else|else
block|{
name|pat_buf
operator|=
name|pattern
operator|->
name|mask
expr_stmt|;
block|}
block|}
else|else
block|{
name|g_warning
argument_list|(
literal|"%s: invalid fill_mode passed"
argument_list|,
name|G_GNUC_PRETTY_FUNCTION
argument_list|)
expr_stmt|;
return|return;
block|}
name|gimp_set_busy
argument_list|(
name|gimage
operator|->
name|gimp
argument_list|)
expr_stmt|;
name|bytes
operator|=
name|gimp_drawable_bytes
argument_list|(
name|drawable
argument_list|)
expr_stmt|;
name|has_alpha
operator|=
name|gimp_drawable_has_alpha
argument_list|(
name|drawable
argument_list|)
expr_stmt|;
comment|/*  If there is no selection mask, the do a seed bucket    *  fill...To do this, calculate a new contiguous region    */
if|if
condition|(
operator|!
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
operator|&&
name|do_seed_fill
condition|)
block|{
name|mask
operator|=
name|gimp_image_contiguous_region_by_seed
argument_list|(
name|gimage
argument_list|,
name|drawable
argument_list|,
name|sample_merged
argument_list|,
name|TRUE
argument_list|,
operator|(
name|gint
operator|)
name|threshold
argument_list|,
name|fill_transparent
argument_list|,
operator|(
name|gint
operator|)
name|x
argument_list|,
operator|(
name|gint
operator|)
name|y
argument_list|)
expr_stmt|;
name|gimp_channel_bounds
argument_list|(
name|mask
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
comment|/*  make sure we handle the mask correctly if it was sample-merged  */
if|if
condition|(
name|sample_merged
condition|)
block|{
name|gint
name|off_x
decl_stmt|,
name|off_y
decl_stmt|;
comment|/*  Limit the channel bounds to the drawable's extents  */
name|gimp_drawable_offsets
argument_list|(
name|drawable
argument_list|,
operator|&
name|off_x
argument_list|,
operator|&
name|off_y
argument_list|)
expr_stmt|;
name|x1
operator|=
name|CLAMP
argument_list|(
name|x1
argument_list|,
name|off_x
argument_list|,
operator|(
name|off_x
operator|+
name|gimp_drawable_width
argument_list|(
name|drawable
argument_list|)
operator|)
argument_list|)
expr_stmt|;
name|y1
operator|=
name|CLAMP
argument_list|(
name|y1
argument_list|,
name|off_y
argument_list|,
operator|(
name|off_y
operator|+
name|gimp_drawable_height
argument_list|(
name|drawable
argument_list|)
operator|)
argument_list|)
expr_stmt|;
name|x2
operator|=
name|CLAMP
argument_list|(
name|x2
argument_list|,
name|off_x
argument_list|,
operator|(
name|off_x
operator|+
name|gimp_drawable_width
argument_list|(
name|drawable
argument_list|)
operator|)
argument_list|)
expr_stmt|;
name|y2
operator|=
name|CLAMP
argument_list|(
name|y2
argument_list|,
name|off_y
argument_list|,
operator|(
name|off_y
operator|+
name|gimp_drawable_height
argument_list|(
name|drawable
argument_list|)
operator|)
argument_list|)
expr_stmt|;
name|pixel_region_init
argument_list|(
operator|&
name|maskPR
argument_list|,
name|gimp_drawable_data
argument_list|(
name|GIMP_DRAWABLE
argument_list|(
name|mask
argument_list|)
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
comment|/*  translate mask bounds to drawable coords  */
name|x1
operator|-=
name|off_x
expr_stmt|;
name|y1
operator|-=
name|off_y
expr_stmt|;
name|x2
operator|-=
name|off_x
expr_stmt|;
name|y2
operator|-=
name|off_y
expr_stmt|;
block|}
else|else
block|{
name|pixel_region_init
argument_list|(
operator|&
name|maskPR
argument_list|,
name|gimp_drawable_data
argument_list|(
name|GIMP_DRAWABLE
argument_list|(
name|mask
argument_list|)
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
block|}
comment|/*  if the gimage doesn't have an alpha channel,        *  make sure that the temp buf does.  We need the        *  alpha channel to fill with the region calculated above        */
if|if
condition|(
operator|!
name|has_alpha
condition|)
block|{
name|bytes
operator|++
expr_stmt|;
name|has_alpha
operator|=
name|TRUE
expr_stmt|;
block|}
block|}
name|buf_tiles
operator|=
name|tile_manager_new
argument_list|(
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
name|bytes
argument_list|)
expr_stmt|;
name|pixel_region_init
argument_list|(
operator|&
name|bufPR
argument_list|,
name|buf_tiles
argument_list|,
literal|0
argument_list|,
literal|0
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
if|if
condition|(
name|mask
condition|)
name|gimp_drawable_bucket_fill_region
argument_list|(
name|fill_mode
argument_list|,
operator|&
name|bufPR
argument_list|,
operator|&
name|maskPR
argument_list|,
name|col
argument_list|,
name|pat_buf
argument_list|,
name|x1
argument_list|,
name|y1
argument_list|,
name|has_alpha
argument_list|)
expr_stmt|;
else|else
name|gimp_drawable_bucket_fill_region
argument_list|(
name|fill_mode
argument_list|,
operator|&
name|bufPR
argument_list|,
name|NULL
argument_list|,
name|col
argument_list|,
name|pat_buf
argument_list|,
name|x1
argument_list|,
name|y1
argument_list|,
name|has_alpha
argument_list|)
expr_stmt|;
comment|/*  Apply it to the image  */
name|pixel_region_init
argument_list|(
operator|&
name|bufPR
argument_list|,
name|buf_tiles
argument_list|,
literal|0
argument_list|,
literal|0
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
name|gimp_image_apply_image
argument_list|(
name|gimage
argument_list|,
name|drawable
argument_list|,
operator|&
name|bufPR
argument_list|,
name|TRUE
argument_list|,
name|opacity
operator|*
literal|255
argument_list|,
name|paint_mode
argument_list|,
name|NULL
argument_list|,
name|x1
argument_list|,
name|y1
argument_list|)
expr_stmt|;
name|tile_manager_destroy
argument_list|(
name|buf_tiles
argument_list|)
expr_stmt|;
comment|/*  update the image  */
name|gimp_drawable_update
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
comment|/*  free the mask  */
if|if
condition|(
name|mask
condition|)
name|g_object_unref
argument_list|(
name|G_OBJECT
argument_list|(
name|mask
argument_list|)
argument_list|)
expr_stmt|;
if|if
condition|(
name|new_buf
condition|)
name|temp_buf_free
argument_list|(
name|pat_buf
argument_list|)
expr_stmt|;
name|gimp_unset_busy
argument_list|(
name|gimage
operator|->
name|gimp
argument_list|)
expr_stmt|;
block|}
end_function

begin_comment
comment|/*  private functions  */
end_comment

begin_function
specifier|static
name|void
DECL|function|gimp_drawable_bucket_fill_region (BucketFillMode fill_mode,PixelRegion * bufPR,PixelRegion * maskPR,guchar * col,TempBuf * pattern,gint off_x,gint off_y,gboolean has_alpha)
name|gimp_drawable_bucket_fill_region
parameter_list|(
name|BucketFillMode
name|fill_mode
parameter_list|,
name|PixelRegion
modifier|*
name|bufPR
parameter_list|,
name|PixelRegion
modifier|*
name|maskPR
parameter_list|,
name|guchar
modifier|*
name|col
parameter_list|,
name|TempBuf
modifier|*
name|pattern
parameter_list|,
name|gint
name|off_x
parameter_list|,
name|gint
name|off_y
parameter_list|,
name|gboolean
name|has_alpha
parameter_list|)
block|{
name|guchar
modifier|*
name|s
decl_stmt|,
modifier|*
name|m
decl_stmt|;
name|gint
name|y
decl_stmt|;
name|void
modifier|*
name|pr
decl_stmt|;
for|for
control|(
name|pr
operator|=
name|pixel_regions_register
argument_list|(
literal|2
argument_list|,
name|bufPR
argument_list|,
name|maskPR
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
name|s
operator|=
name|bufPR
operator|->
name|data
expr_stmt|;
if|if
condition|(
name|maskPR
condition|)
name|m
operator|=
name|maskPR
operator|->
name|data
expr_stmt|;
else|else
name|m
operator|=
name|NULL
expr_stmt|;
for|for
control|(
name|y
operator|=
literal|0
init|;
name|y
operator|<
name|bufPR
operator|->
name|h
condition|;
name|y
operator|++
control|)
block|{
switch|switch
condition|(
name|fill_mode
condition|)
block|{
case|case
name|FG_BUCKET_FILL
case|:
case|case
name|BG_BUCKET_FILL
case|:
name|gimp_drawable_bucket_fill_line_color
argument_list|(
name|s
argument_list|,
name|m
argument_list|,
name|col
argument_list|,
name|has_alpha
argument_list|,
name|bufPR
operator|->
name|bytes
argument_list|,
name|bufPR
operator|->
name|w
argument_list|)
expr_stmt|;
break|break;
case|case
name|PATTERN_BUCKET_FILL
case|:
name|gimp_drawable_bucket_fill_line_pattern
argument_list|(
name|s
argument_list|,
name|m
argument_list|,
name|pattern
argument_list|,
name|has_alpha
argument_list|,
name|bufPR
operator|->
name|bytes
argument_list|,
name|off_x
operator|+
name|bufPR
operator|->
name|x
argument_list|,
name|off_y
operator|+
name|y
operator|+
name|bufPR
operator|->
name|y
argument_list|,
name|bufPR
operator|->
name|w
argument_list|)
expr_stmt|;
break|break;
block|}
name|s
operator|+=
name|bufPR
operator|->
name|rowstride
expr_stmt|;
if|if
condition|(
name|maskPR
condition|)
name|m
operator|+=
name|maskPR
operator|->
name|rowstride
expr_stmt|;
block|}
block|}
block|}
end_function

begin_function
specifier|static
name|void
DECL|function|gimp_drawable_bucket_fill_line_color (guchar * buf,guchar * mask,guchar * col,gboolean has_alpha,gint bytes,gint width)
name|gimp_drawable_bucket_fill_line_color
parameter_list|(
name|guchar
modifier|*
name|buf
parameter_list|,
name|guchar
modifier|*
name|mask
parameter_list|,
name|guchar
modifier|*
name|col
parameter_list|,
name|gboolean
name|has_alpha
parameter_list|,
name|gint
name|bytes
parameter_list|,
name|gint
name|width
parameter_list|)
block|{
name|gint
name|alpha
decl_stmt|,
name|b
decl_stmt|;
name|alpha
operator|=
operator|(
name|has_alpha
operator|)
condition|?
name|bytes
operator|-
literal|1
else|:
name|bytes
expr_stmt|;
while|while
condition|(
name|width
operator|--
condition|)
block|{
for|for
control|(
name|b
operator|=
literal|0
init|;
name|b
operator|<
name|alpha
condition|;
name|b
operator|++
control|)
name|buf
index|[
name|b
index|]
operator|=
name|col
index|[
name|b
index|]
expr_stmt|;
if|if
condition|(
name|has_alpha
condition|)
block|{
if|if
condition|(
name|mask
condition|)
name|buf
index|[
name|alpha
index|]
operator|=
operator|*
name|mask
operator|++
expr_stmt|;
else|else
name|buf
index|[
name|alpha
index|]
operator|=
name|OPAQUE_OPACITY
expr_stmt|;
block|}
name|buf
operator|+=
name|bytes
expr_stmt|;
block|}
block|}
end_function

begin_function
specifier|static
name|void
DECL|function|gimp_drawable_bucket_fill_line_pattern (guchar * buf,guchar * mask,TempBuf * pattern,gboolean has_alpha,gint bytes,gint x,gint y,gint width)
name|gimp_drawable_bucket_fill_line_pattern
parameter_list|(
name|guchar
modifier|*
name|buf
parameter_list|,
name|guchar
modifier|*
name|mask
parameter_list|,
name|TempBuf
modifier|*
name|pattern
parameter_list|,
name|gboolean
name|has_alpha
parameter_list|,
name|gint
name|bytes
parameter_list|,
name|gint
name|x
parameter_list|,
name|gint
name|y
parameter_list|,
name|gint
name|width
parameter_list|)
block|{
name|guchar
modifier|*
name|pat
decl_stmt|,
modifier|*
name|p
decl_stmt|;
name|gint
name|alpha
decl_stmt|,
name|b
decl_stmt|;
name|gint
name|i
decl_stmt|;
comment|/*  Get a pointer to the appropriate scanline of the pattern buffer  */
name|pat
operator|=
name|temp_buf_data
argument_list|(
name|pattern
argument_list|)
operator|+
operator|(
name|y
operator|%
name|pattern
operator|->
name|height
operator|)
operator|*
name|pattern
operator|->
name|width
operator|*
name|pattern
operator|->
name|bytes
expr_stmt|;
name|alpha
operator|=
operator|(
name|has_alpha
operator|)
condition|?
name|bytes
operator|-
literal|1
else|:
name|bytes
expr_stmt|;
for|for
control|(
name|i
operator|=
literal|0
init|;
name|i
operator|<
name|width
condition|;
name|i
operator|++
control|)
block|{
name|p
operator|=
name|pat
operator|+
operator|(
operator|(
name|i
operator|+
name|x
operator|)
operator|%
name|pattern
operator|->
name|width
operator|)
operator|*
name|pattern
operator|->
name|bytes
expr_stmt|;
for|for
control|(
name|b
operator|=
literal|0
init|;
name|b
operator|<
name|alpha
condition|;
name|b
operator|++
control|)
name|buf
index|[
name|b
index|]
operator|=
name|p
index|[
name|b
index|]
expr_stmt|;
if|if
condition|(
name|has_alpha
condition|)
block|{
if|if
condition|(
name|mask
condition|)
name|buf
index|[
name|alpha
index|]
operator|=
operator|*
name|mask
operator|++
expr_stmt|;
else|else
name|buf
index|[
name|alpha
index|]
operator|=
name|OPAQUE_OPACITY
expr_stmt|;
block|}
name|buf
operator|+=
name|bytes
expr_stmt|;
block|}
block|}
end_function

end_unit

