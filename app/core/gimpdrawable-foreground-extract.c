begin_unit|revision:0.9.5;language:C;cregit-version:0.0.1
begin_comment
comment|/* GIMP - The GNU Image Manipulation Program  * Copyright (C) 1995 Spencer Kimball and Peter Mattis  *  * This program is free software: you can redistribute it and/or modify  * it under the terms of the GNU General Public License as published by  * the Free Software Foundation; either version 3 of the License, or  * (at your option) any later version.  *  * This program is distributed in the hope that it will be useful,  * but WITHOUT ANY WARRANTY; without even the implied warranty of  * MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the  * GNU General Public License for more details.  *  * You should have received a copy of the GNU General Public License  * along with this program.  If not, see<http://www.gnu.org/licenses/>.  */
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
file|"libgimpbase/gimpbase.h"
end_include

begin_include
include|#
directive|include
file|"core-types.h"
end_include

begin_include
include|#
directive|include
file|"base/siox.h"
end_include

begin_include
include|#
directive|include
file|"base/tile-manager.h"
end_include

begin_include
include|#
directive|include
file|"gegl/gimp-gegl-utils.h"
end_include

begin_include
include|#
directive|include
file|"gimpchannel.h"
end_include

begin_include
include|#
directive|include
file|"gimpdrawable.h"
end_include

begin_include
include|#
directive|include
file|"gimpdrawable-foreground-extract.h"
end_include

begin_include
include|#
directive|include
file|"gimpimage.h"
end_include

begin_include
include|#
directive|include
file|"gimpprogress.h"
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
name|void
DECL|function|gimp_drawable_foreground_extract (GimpDrawable * drawable,GimpForegroundExtractMode mode,GimpDrawable * mask,GimpProgress * progress)
name|gimp_drawable_foreground_extract
parameter_list|(
name|GimpDrawable
modifier|*
name|drawable
parameter_list|,
name|GimpForegroundExtractMode
name|mode
parameter_list|,
name|GimpDrawable
modifier|*
name|mask
parameter_list|,
name|GimpProgress
modifier|*
name|progress
parameter_list|)
block|{
name|SioxState
modifier|*
name|state
decl_stmt|;
specifier|const
name|gdouble
name|sensitivity
index|[
literal|3
index|]
init|=
block|{
name|SIOX_DEFAULT_SENSITIVITY_L
block|,
name|SIOX_DEFAULT_SENSITIVITY_A
block|,
name|SIOX_DEFAULT_SENSITIVITY_B
block|}
decl_stmt|;
name|g_return_if_fail
argument_list|(
name|GIMP_IS_DRAWABLE
argument_list|(
name|mask
argument_list|)
argument_list|)
expr_stmt|;
name|g_return_if_fail
argument_list|(
name|mode
operator|==
name|GIMP_FOREGROUND_EXTRACT_SIOX
argument_list|)
expr_stmt|;
name|state
operator|=
name|gimp_drawable_foreground_extract_siox_init
argument_list|(
name|drawable
argument_list|,
literal|0
argument_list|,
literal|0
argument_list|,
name|gimp_item_get_width
argument_list|(
name|GIMP_ITEM
argument_list|(
name|mask
argument_list|)
argument_list|)
argument_list|,
name|gimp_item_get_height
argument_list|(
name|GIMP_ITEM
argument_list|(
name|mask
argument_list|)
argument_list|)
argument_list|)
expr_stmt|;
if|if
condition|(
name|state
condition|)
block|{
name|gimp_drawable_foreground_extract_siox
argument_list|(
name|mask
argument_list|,
name|state
argument_list|,
name|SIOX_REFINEMENT_RECALCULATE
argument_list|,
name|SIOX_DEFAULT_SMOOTHNESS
argument_list|,
name|sensitivity
argument_list|,
name|FALSE
argument_list|,
name|progress
argument_list|)
expr_stmt|;
name|gimp_drawable_foreground_extract_siox_done
argument_list|(
name|state
argument_list|)
expr_stmt|;
block|}
block|}
end_function

begin_function
name|SioxState
modifier|*
DECL|function|gimp_drawable_foreground_extract_siox_init (GimpDrawable * drawable,gint x,gint y,gint width,gint height)
name|gimp_drawable_foreground_extract_siox_init
parameter_list|(
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
name|gint
name|width
parameter_list|,
name|gint
name|height
parameter_list|)
block|{
name|GeglBuffer
modifier|*
name|buffer
decl_stmt|;
specifier|const
name|guchar
modifier|*
name|colormap
init|=
name|NULL
decl_stmt|;
name|gboolean
name|intersect
decl_stmt|;
name|gint
name|offset_x
decl_stmt|;
name|gint
name|offset_y
decl_stmt|;
name|g_return_val_if_fail
argument_list|(
name|GIMP_IS_DRAWABLE
argument_list|(
name|drawable
argument_list|)
argument_list|,
name|NULL
argument_list|)
expr_stmt|;
name|g_return_val_if_fail
argument_list|(
name|gimp_item_is_attached
argument_list|(
name|GIMP_ITEM
argument_list|(
name|drawable
argument_list|)
argument_list|)
argument_list|,
name|NULL
argument_list|)
expr_stmt|;
if|if
condition|(
name|gimp_drawable_is_indexed
argument_list|(
name|drawable
argument_list|)
condition|)
name|colormap
operator|=
name|gimp_drawable_get_colormap
argument_list|(
name|drawable
argument_list|)
expr_stmt|;
name|gimp_item_get_offset
argument_list|(
name|GIMP_ITEM
argument_list|(
name|drawable
argument_list|)
argument_list|,
operator|&
name|offset_x
argument_list|,
operator|&
name|offset_y
argument_list|)
expr_stmt|;
name|intersect
operator|=
name|gimp_rectangle_intersect
argument_list|(
name|offset_x
argument_list|,
name|offset_y
argument_list|,
name|gimp_item_get_width
argument_list|(
name|GIMP_ITEM
argument_list|(
name|drawable
argument_list|)
argument_list|)
argument_list|,
name|gimp_item_get_height
argument_list|(
name|GIMP_ITEM
argument_list|(
name|drawable
argument_list|)
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
expr_stmt|;
comment|/* FIXME:    * Clear the mask outside the rectangle that we are working on?    */
if|if
condition|(
operator|!
name|intersect
condition|)
return|return
name|NULL
return|;
name|buffer
operator|=
name|gimp_drawable_get_buffer
argument_list|(
name|drawable
argument_list|)
expr_stmt|;
return|return
name|siox_init
argument_list|(
name|gimp_gegl_buffer_get_tiles
argument_list|(
name|buffer
argument_list|)
argument_list|,
name|colormap
argument_list|,
name|offset_x
argument_list|,
name|offset_y
argument_list|,
name|x
argument_list|,
name|y
argument_list|,
name|width
argument_list|,
name|height
argument_list|)
return|;
block|}
end_function

begin_function
name|void
DECL|function|gimp_drawable_foreground_extract_siox (GimpDrawable * mask,SioxState * state,SioxRefinementType refinement,gint smoothness,const gdouble sensitivity[3],gboolean multiblob,GimpProgress * progress)
name|gimp_drawable_foreground_extract_siox
parameter_list|(
name|GimpDrawable
modifier|*
name|mask
parameter_list|,
name|SioxState
modifier|*
name|state
parameter_list|,
name|SioxRefinementType
name|refinement
parameter_list|,
name|gint
name|smoothness
parameter_list|,
specifier|const
name|gdouble
name|sensitivity
index|[
literal|3
index|]
parameter_list|,
name|gboolean
name|multiblob
parameter_list|,
name|GimpProgress
modifier|*
name|progress
parameter_list|)
block|{
name|GeglBuffer
modifier|*
name|buffer
decl_stmt|;
name|gint
name|x1
decl_stmt|,
name|y1
decl_stmt|;
name|gint
name|x2
decl_stmt|,
name|y2
decl_stmt|;
name|g_return_if_fail
argument_list|(
name|GIMP_IS_DRAWABLE
argument_list|(
name|mask
argument_list|)
argument_list|)
expr_stmt|;
name|g_return_if_fail
argument_list|(
name|babl_format_get_bytes_per_pixel
argument_list|(
name|gimp_drawable_get_format
argument_list|(
name|mask
argument_list|)
argument_list|)
operator|==
literal|1
argument_list|)
expr_stmt|;
name|g_return_if_fail
argument_list|(
name|state
operator|!=
name|NULL
argument_list|)
expr_stmt|;
name|g_return_if_fail
argument_list|(
name|progress
operator|==
name|NULL
operator|||
name|GIMP_IS_PROGRESS
argument_list|(
name|progress
argument_list|)
argument_list|)
expr_stmt|;
if|if
condition|(
name|progress
condition|)
name|gimp_progress_start
argument_list|(
name|progress
argument_list|,
name|_
argument_list|(
literal|"Foreground Extraction"
argument_list|)
argument_list|,
name|FALSE
argument_list|)
expr_stmt|;
if|if
condition|(
name|GIMP_IS_CHANNEL
argument_list|(
name|mask
argument_list|)
condition|)
block|{
name|gimp_channel_bounds
argument_list|(
name|GIMP_CHANNEL
argument_list|(
name|mask
argument_list|)
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
block|}
else|else
block|{
name|x1
operator|=
literal|0
expr_stmt|;
name|y1
operator|=
literal|0
expr_stmt|;
name|x2
operator|=
name|gimp_item_get_width
argument_list|(
name|GIMP_ITEM
argument_list|(
name|mask
argument_list|)
argument_list|)
expr_stmt|;
name|y2
operator|=
name|gimp_item_get_height
argument_list|(
name|GIMP_ITEM
argument_list|(
name|mask
argument_list|)
argument_list|)
expr_stmt|;
block|}
name|buffer
operator|=
name|gimp_drawable_get_buffer
argument_list|(
name|mask
argument_list|)
expr_stmt|;
name|siox_foreground_extract
argument_list|(
name|state
argument_list|,
name|refinement
argument_list|,
name|gimp_gegl_buffer_get_tiles
argument_list|(
name|buffer
argument_list|)
argument_list|,
name|x1
argument_list|,
name|y1
argument_list|,
name|x2
argument_list|,
name|y2
argument_list|,
name|smoothness
argument_list|,
name|sensitivity
argument_list|,
name|multiblob
argument_list|,
operator|(
name|SioxProgressFunc
operator|)
name|gimp_progress_set_value
argument_list|,
name|progress
argument_list|)
expr_stmt|;
if|if
condition|(
name|progress
condition|)
name|gimp_progress_end
argument_list|(
name|progress
argument_list|)
expr_stmt|;
name|gimp_drawable_update
argument_list|(
name|mask
argument_list|,
name|x1
argument_list|,
name|y1
argument_list|,
name|x2
argument_list|,
name|y2
argument_list|)
expr_stmt|;
block|}
end_function

begin_function
name|void
DECL|function|gimp_drawable_foreground_extract_siox_done (SioxState * state)
name|gimp_drawable_foreground_extract_siox_done
parameter_list|(
name|SioxState
modifier|*
name|state
parameter_list|)
block|{
name|g_return_if_fail
argument_list|(
name|state
operator|!=
name|NULL
argument_list|)
expr_stmt|;
name|siox_done
argument_list|(
name|state
argument_list|)
expr_stmt|;
block|}
end_function

end_unit

