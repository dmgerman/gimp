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
file|"base/pixel-region.h"
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
file|"gegl/gimp-gegl-nodes.h"
end_include

begin_include
include|#
directive|include
file|"gegl/gimp-gegl-utils.h"
end_include

begin_include
include|#
directive|include
file|"gimp.h"
end_include

begin_include
include|#
directive|include
file|"gimp-apply-operation.h"
end_include

begin_include
include|#
directive|include
file|"gimpchannel.h"
end_include

begin_include
include|#
directive|include
file|"gimpdrawable-combine.h"
end_include

begin_include
include|#
directive|include
file|"gimpdrawableundo.h"
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
file|"gimptempbuf.h"
end_include

begin_function
name|void
DECL|function|gimp_drawable_real_apply_buffer (GimpDrawable * drawable,GeglBuffer * buffer,const GeglRectangle * buffer_region,gboolean push_undo,const gchar * undo_desc,gdouble opacity,GimpLayerModeEffects mode,GeglBuffer * base_buffer,gint base_x,gint base_y,GeglBuffer * dest_buffer,gint dest_x,gint dest_y)
name|gimp_drawable_real_apply_buffer
parameter_list|(
name|GimpDrawable
modifier|*
name|drawable
parameter_list|,
name|GeglBuffer
modifier|*
name|buffer
parameter_list|,
specifier|const
name|GeglRectangle
modifier|*
name|buffer_region
parameter_list|,
name|gboolean
name|push_undo
parameter_list|,
specifier|const
name|gchar
modifier|*
name|undo_desc
parameter_list|,
name|gdouble
name|opacity
parameter_list|,
name|GimpLayerModeEffects
name|mode
parameter_list|,
name|GeglBuffer
modifier|*
name|base_buffer
parameter_list|,
name|gint
name|base_x
parameter_list|,
name|gint
name|base_y
parameter_list|,
name|GeglBuffer
modifier|*
name|dest_buffer
parameter_list|,
name|gint
name|dest_x
parameter_list|,
name|gint
name|dest_y
parameter_list|)
block|{
name|GimpItem
modifier|*
name|item
init|=
name|GIMP_ITEM
argument_list|(
name|drawable
argument_list|)
decl_stmt|;
name|GimpImage
modifier|*
name|image
init|=
name|gimp_item_get_image
argument_list|(
name|item
argument_list|)
decl_stmt|;
name|GimpChannel
modifier|*
name|mask
init|=
name|gimp_image_get_mask
argument_list|(
name|image
argument_list|)
decl_stmt|;
name|gint
name|x
decl_stmt|,
name|y
decl_stmt|,
name|width
decl_stmt|,
name|height
decl_stmt|;
name|gint
name|offset_x
decl_stmt|,
name|offset_y
decl_stmt|;
comment|/*  don't apply the mask to itself and don't apply an empty mask  */
if|if
condition|(
name|GIMP_DRAWABLE
argument_list|(
name|mask
argument_list|)
operator|==
name|drawable
operator|||
name|gimp_channel_is_empty
argument_list|(
name|mask
argument_list|)
condition|)
name|mask
operator|=
name|NULL
expr_stmt|;
if|if
condition|(
operator|!
name|base_buffer
condition|)
name|base_buffer
operator|=
name|gimp_drawable_get_buffer
argument_list|(
name|drawable
argument_list|)
expr_stmt|;
comment|/*  get the layer offsets  */
name|gimp_item_get_offset
argument_list|(
name|item
argument_list|,
operator|&
name|offset_x
argument_list|,
operator|&
name|offset_y
argument_list|)
expr_stmt|;
comment|/*  make sure the image application coordinates are within drawable bounds  */
name|gimp_rectangle_intersect
argument_list|(
name|base_x
argument_list|,
name|base_y
argument_list|,
name|buffer_region
operator|->
name|width
argument_list|,
name|buffer_region
operator|->
name|height
argument_list|,
literal|0
argument_list|,
literal|0
argument_list|,
name|gimp_item_get_width
argument_list|(
name|item
argument_list|)
argument_list|,
name|gimp_item_get_height
argument_list|(
name|item
argument_list|)
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
if|if
condition|(
name|mask
condition|)
block|{
name|GimpItem
modifier|*
name|mask_item
init|=
name|GIMP_ITEM
argument_list|(
name|mask
argument_list|)
decl_stmt|;
comment|/*  make sure coordinates are in mask bounds ...        *  we need to add the layer offset to transform coords        *  into the mask coordinate system        */
name|gimp_rectangle_intersect
argument_list|(
name|x
argument_list|,
name|y
argument_list|,
name|width
argument_list|,
name|height
argument_list|,
operator|-
name|offset_x
argument_list|,
operator|-
name|offset_y
argument_list|,
name|gimp_item_get_width
argument_list|(
name|mask_item
argument_list|)
argument_list|,
name|gimp_item_get_height
argument_list|(
name|mask_item
argument_list|)
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
block|}
if|if
condition|(
name|push_undo
condition|)
block|{
name|GimpDrawableUndo
modifier|*
name|undo
decl_stmt|;
name|gimp_drawable_push_undo
argument_list|(
name|drawable
argument_list|,
name|undo_desc
argument_list|,
name|NULL
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
name|undo
operator|=
name|GIMP_DRAWABLE_UNDO
argument_list|(
name|gimp_image_undo_get_fadeable
argument_list|(
name|image
argument_list|)
argument_list|)
expr_stmt|;
if|if
condition|(
name|undo
condition|)
block|{
name|undo
operator|->
name|paint_mode
operator|=
name|mode
expr_stmt|;
name|undo
operator|->
name|opacity
operator|=
name|opacity
expr_stmt|;
name|undo
operator|->
name|applied_buffer
operator|=
name|gimp_gegl_buffer_new
argument_list|(
name|GEGL_RECTANGLE
argument_list|(
literal|0
argument_list|,
literal|0
argument_list|,
name|width
argument_list|,
name|height
argument_list|)
argument_list|,
name|gegl_buffer_get_format
argument_list|(
name|buffer
argument_list|)
argument_list|)
expr_stmt|;
name|gegl_buffer_copy
argument_list|(
name|buffer
argument_list|,
name|GEGL_RECTANGLE
argument_list|(
name|buffer_region
operator|->
name|x
operator|+
operator|(
name|x
operator|-
name|base_x
operator|)
argument_list|,
name|buffer_region
operator|->
name|y
operator|+
operator|(
name|y
operator|-
name|base_y
operator|)
argument_list|,
name|width
argument_list|,
name|height
argument_list|)
argument_list|,
name|undo
operator|->
name|applied_buffer
argument_list|,
name|GEGL_RECTANGLE
argument_list|(
literal|0
argument_list|,
literal|0
argument_list|,
name|width
argument_list|,
name|height
argument_list|)
argument_list|)
expr_stmt|;
block|}
block|}
if|if
condition|(
name|FALSE
comment|/* XXX gimp_use_gegl (image->gimp)&& ! dest_buffer */
condition|)
block|{
name|GeglBuffer
modifier|*
name|mask_buffer
init|=
name|NULL
decl_stmt|;
name|GeglNode
modifier|*
name|apply
decl_stmt|;
if|if
condition|(
name|mask
condition|)
name|mask_buffer
operator|=
name|gimp_drawable_get_buffer
argument_list|(
name|GIMP_DRAWABLE
argument_list|(
name|mask
argument_list|)
argument_list|)
expr_stmt|;
name|dest_buffer
operator|=
name|gimp_drawable_get_buffer
argument_list|(
name|drawable
argument_list|)
expr_stmt|;
name|apply
operator|=
name|gimp_gegl_create_apply_buffer_node
argument_list|(
name|buffer
argument_list|,
name|base_x
operator|-
name|buffer_region
operator|->
name|x
argument_list|,
name|base_y
operator|-
name|buffer_region
operator|->
name|y
argument_list|,
literal|0
argument_list|,
literal|0
argument_list|,
literal|0
argument_list|,
literal|0
argument_list|,
name|mask_buffer
argument_list|,
operator|-
name|offset_x
argument_list|,
operator|-
name|offset_y
argument_list|,
name|opacity
argument_list|,
name|mode
argument_list|)
expr_stmt|;
name|gimp_apply_operation
argument_list|(
name|base_buffer
argument_list|,
name|NULL
argument_list|,
name|NULL
argument_list|,
name|apply
argument_list|,
name|dest_buffer
argument_list|,
name|GEGL_RECTANGLE
argument_list|(
name|x
argument_list|,
name|y
argument_list|,
name|width
argument_list|,
name|height
argument_list|)
argument_list|)
expr_stmt|;
name|g_object_unref
argument_list|(
name|apply
argument_list|)
expr_stmt|;
block|}
else|else
block|{
name|PixelRegion
name|src1PR
decl_stmt|,
name|src2PR
decl_stmt|,
name|destPR
decl_stmt|;
name|CombinationMode
name|operation
decl_stmt|;
name|gboolean
name|active_components
index|[
name|MAX_CHANNELS
index|]
decl_stmt|;
if|if
condition|(
name|gimp_gegl_buffer_get_temp_buf
argument_list|(
name|buffer
argument_list|)
condition|)
block|{
name|pixel_region_init_temp_buf
argument_list|(
operator|&
name|src2PR
argument_list|,
name|gimp_gegl_buffer_get_temp_buf
argument_list|(
name|buffer
argument_list|)
argument_list|,
name|buffer_region
operator|->
name|x
argument_list|,
name|buffer_region
operator|->
name|y
argument_list|,
name|buffer_region
operator|->
name|width
argument_list|,
name|buffer_region
operator|->
name|height
argument_list|)
expr_stmt|;
block|}
else|else
block|{
name|pixel_region_init
argument_list|(
operator|&
name|src2PR
argument_list|,
name|gimp_gegl_buffer_get_tiles
argument_list|(
name|buffer
argument_list|)
argument_list|,
name|buffer_region
operator|->
name|x
argument_list|,
name|buffer_region
operator|->
name|y
argument_list|,
name|buffer_region
operator|->
name|width
argument_list|,
name|buffer_region
operator|->
name|height
argument_list|,
name|FALSE
argument_list|)
expr_stmt|;
block|}
comment|/*  configure the active channel array  */
name|gimp_drawable_get_active_components
argument_list|(
name|drawable
argument_list|,
name|active_components
argument_list|)
expr_stmt|;
comment|/*  determine what sort of operation is being attempted and        *  if it's actually legal...        */
name|operation
operator|=
name|gimp_image_get_combination_mode
argument_list|(
name|gimp_drawable_type
argument_list|(
name|drawable
argument_list|)
argument_list|,
name|src2PR
operator|.
name|bytes
argument_list|)
expr_stmt|;
if|if
condition|(
name|operation
operator|==
operator|-
literal|1
condition|)
block|{
name|g_warning
argument_list|(
literal|"%s: illegal parameters."
argument_list|,
name|G_STRFUNC
argument_list|)
expr_stmt|;
return|return;
block|}
comment|/* configure the pixel regions */
name|pixel_region_init
argument_list|(
operator|&
name|src1PR
argument_list|,
name|gimp_gegl_buffer_get_tiles
argument_list|(
name|base_buffer
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
name|pixel_region_resize
argument_list|(
operator|&
name|src2PR
argument_list|,
name|src2PR
operator|.
name|x
operator|+
operator|(
name|x
operator|-
name|base_x
operator|)
argument_list|,
name|src2PR
operator|.
name|y
operator|+
operator|(
name|y
operator|-
name|base_y
operator|)
argument_list|,
name|width
argument_list|,
name|height
argument_list|)
expr_stmt|;
if|if
condition|(
name|dest_buffer
condition|)
block|{
name|pixel_region_init
argument_list|(
operator|&
name|destPR
argument_list|,
name|gimp_gegl_buffer_get_tiles
argument_list|(
name|dest_buffer
argument_list|)
argument_list|,
name|dest_x
argument_list|,
name|dest_y
argument_list|,
name|buffer_region
operator|->
name|width
argument_list|,
name|buffer_region
operator|->
name|height
argument_list|,
name|TRUE
argument_list|)
expr_stmt|;
block|}
else|else
block|{
name|pixel_region_init
argument_list|(
operator|&
name|destPR
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
name|TRUE
argument_list|)
expr_stmt|;
block|}
if|if
condition|(
name|mask
condition|)
block|{
name|PixelRegion
name|maskPR
decl_stmt|;
name|pixel_region_init
argument_list|(
operator|&
name|maskPR
argument_list|,
name|gimp_drawable_get_tiles
argument_list|(
name|GIMP_DRAWABLE
argument_list|(
name|mask
argument_list|)
argument_list|)
argument_list|,
name|x
operator|+
name|offset_x
argument_list|,
name|y
operator|+
name|offset_y
argument_list|,
name|width
argument_list|,
name|height
argument_list|,
name|FALSE
argument_list|)
expr_stmt|;
name|combine_regions
argument_list|(
operator|&
name|src1PR
argument_list|,
operator|&
name|src2PR
argument_list|,
operator|&
name|destPR
argument_list|,
operator|&
name|maskPR
argument_list|,
name|NULL
argument_list|,
name|opacity
operator|*
literal|255.999
argument_list|,
name|mode
argument_list|,
name|active_components
argument_list|,
name|operation
argument_list|)
expr_stmt|;
block|}
else|else
block|{
name|combine_regions
argument_list|(
operator|&
name|src1PR
argument_list|,
operator|&
name|src2PR
argument_list|,
operator|&
name|destPR
argument_list|,
name|NULL
argument_list|,
name|NULL
argument_list|,
name|opacity
operator|*
literal|255.999
argument_list|,
name|mode
argument_list|,
name|active_components
argument_list|,
name|operation
argument_list|)
expr_stmt|;
block|}
block|}
block|}
end_function

begin_comment
comment|/*  Similar to gimp_drawable_apply_region but works in "replace" mode (i.e.  *  transparent pixels in src2 make the result transparent rather than  *  opaque.  *  * Takes an additional mask pixel region as well.  */
end_comment

begin_function
name|void
DECL|function|gimp_drawable_real_replace_buffer (GimpDrawable * drawable,GeglBuffer * buffer,const GeglRectangle * buffer_region,gboolean push_undo,const gchar * undo_desc,gdouble opacity,PixelRegion * maskPR,gint dest_x,gint dest_y)
name|gimp_drawable_real_replace_buffer
parameter_list|(
name|GimpDrawable
modifier|*
name|drawable
parameter_list|,
name|GeglBuffer
modifier|*
name|buffer
parameter_list|,
specifier|const
name|GeglRectangle
modifier|*
name|buffer_region
parameter_list|,
name|gboolean
name|push_undo
parameter_list|,
specifier|const
name|gchar
modifier|*
name|undo_desc
parameter_list|,
name|gdouble
name|opacity
parameter_list|,
name|PixelRegion
modifier|*
name|maskPR
parameter_list|,
name|gint
name|dest_x
parameter_list|,
name|gint
name|dest_y
parameter_list|)
block|{
name|GimpItem
modifier|*
name|item
init|=
name|GIMP_ITEM
argument_list|(
name|drawable
argument_list|)
decl_stmt|;
name|GimpImage
modifier|*
name|image
init|=
name|gimp_item_get_image
argument_list|(
name|item
argument_list|)
decl_stmt|;
name|GimpChannel
modifier|*
name|mask
init|=
name|gimp_image_get_mask
argument_list|(
name|image
argument_list|)
decl_stmt|;
name|GimpTempBuf
modifier|*
name|temp_buf
decl_stmt|;
name|PixelRegion
name|src2PR
decl_stmt|;
name|gint
name|x
decl_stmt|,
name|y
decl_stmt|,
name|width
decl_stmt|,
name|height
decl_stmt|;
name|gint
name|offset_x
decl_stmt|,
name|offset_y
decl_stmt|;
name|PixelRegion
name|src1PR
decl_stmt|,
name|destPR
decl_stmt|;
name|CombinationMode
name|operation
decl_stmt|;
name|gboolean
name|active_components
index|[
name|MAX_CHANNELS
index|]
decl_stmt|;
name|temp_buf
operator|=
name|gimp_gegl_buffer_get_temp_buf
argument_list|(
name|buffer
argument_list|)
expr_stmt|;
if|if
condition|(
name|temp_buf
condition|)
block|{
name|pixel_region_init_temp_buf
argument_list|(
operator|&
name|src2PR
argument_list|,
name|temp_buf
argument_list|,
name|buffer_region
operator|->
name|x
argument_list|,
name|buffer_region
operator|->
name|y
argument_list|,
name|buffer_region
operator|->
name|width
argument_list|,
name|buffer_region
operator|->
name|height
argument_list|)
expr_stmt|;
block|}
else|else
block|{
name|pixel_region_init
argument_list|(
operator|&
name|src2PR
argument_list|,
name|gimp_gegl_buffer_get_tiles
argument_list|(
name|buffer
argument_list|)
argument_list|,
name|buffer_region
operator|->
name|x
argument_list|,
name|buffer_region
operator|->
name|y
argument_list|,
name|buffer_region
operator|->
name|width
argument_list|,
name|buffer_region
operator|->
name|height
argument_list|,
name|FALSE
argument_list|)
expr_stmt|;
block|}
comment|/*  don't apply the mask to itself and don't apply an empty mask  */
if|if
condition|(
name|GIMP_DRAWABLE
argument_list|(
name|mask
argument_list|)
operator|==
name|drawable
operator|||
name|gimp_channel_is_empty
argument_list|(
name|mask
argument_list|)
condition|)
name|mask
operator|=
name|NULL
expr_stmt|;
comment|/*  configure the active channel array  */
name|gimp_drawable_get_active_components
argument_list|(
name|drawable
argument_list|,
name|active_components
argument_list|)
expr_stmt|;
comment|/*  determine what sort of operation is being attempted and    *  if it's actually legal...    */
name|operation
operator|=
name|gimp_image_get_combination_mode
argument_list|(
name|gimp_drawable_type
argument_list|(
name|drawable
argument_list|)
argument_list|,
name|src2PR
operator|.
name|bytes
argument_list|)
expr_stmt|;
if|if
condition|(
name|operation
operator|==
operator|-
literal|1
condition|)
block|{
name|g_warning
argument_list|(
literal|"%s: illegal parameters."
argument_list|,
name|G_STRFUNC
argument_list|)
expr_stmt|;
return|return;
block|}
comment|/*  get the layer offsets  */
name|gimp_item_get_offset
argument_list|(
name|item
argument_list|,
operator|&
name|offset_x
argument_list|,
operator|&
name|offset_y
argument_list|)
expr_stmt|;
comment|/*  make sure the image application coordinates are within drawable bounds  */
name|gimp_rectangle_intersect
argument_list|(
name|dest_x
argument_list|,
name|dest_y
argument_list|,
name|src2PR
operator|.
name|w
argument_list|,
name|src2PR
operator|.
name|h
argument_list|,
literal|0
argument_list|,
literal|0
argument_list|,
name|gimp_item_get_width
argument_list|(
name|item
argument_list|)
argument_list|,
name|gimp_item_get_height
argument_list|(
name|item
argument_list|)
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
if|if
condition|(
name|mask
condition|)
block|{
name|GimpItem
modifier|*
name|mask_item
init|=
name|GIMP_ITEM
argument_list|(
name|mask
argument_list|)
decl_stmt|;
comment|/*  make sure coordinates are in mask bounds ...        *  we need to add the layer offset to transform coords        *  into the mask coordinate system        */
name|gimp_rectangle_intersect
argument_list|(
name|x
argument_list|,
name|y
argument_list|,
name|width
argument_list|,
name|height
argument_list|,
operator|-
name|offset_x
argument_list|,
operator|-
name|offset_y
argument_list|,
name|gimp_item_get_width
argument_list|(
name|mask_item
argument_list|)
argument_list|,
name|gimp_item_get_height
argument_list|(
name|mask_item
argument_list|)
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
block|}
comment|/*  If the calling procedure specified an undo step...  */
if|if
condition|(
name|push_undo
condition|)
name|gimp_drawable_push_undo
argument_list|(
name|drawable
argument_list|,
name|undo_desc
argument_list|,
name|NULL
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
comment|/* configure the pixel regions */
name|pixel_region_init
argument_list|(
operator|&
name|src1PR
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
name|TRUE
argument_list|)
expr_stmt|;
name|pixel_region_resize
argument_list|(
operator|&
name|src2PR
argument_list|,
name|src2PR
operator|.
name|x
operator|+
operator|(
name|x
operator|-
name|dest_x
operator|)
argument_list|,
name|src2PR
operator|.
name|y
operator|+
operator|(
name|y
operator|-
name|dest_y
operator|)
argument_list|,
name|width
argument_list|,
name|height
argument_list|)
expr_stmt|;
if|if
condition|(
name|mask
condition|)
block|{
name|PixelRegion
name|tempPR
decl_stmt|;
name|GimpTempBuf
modifier|*
name|temp_buf
decl_stmt|;
name|GeglBuffer
modifier|*
name|src_buffer
decl_stmt|;
name|GeglBuffer
modifier|*
name|dest_buffer
decl_stmt|;
name|src_buffer
operator|=
name|gimp_drawable_get_buffer
argument_list|(
name|GIMP_DRAWABLE
argument_list|(
name|mask
argument_list|)
argument_list|)
expr_stmt|;
name|temp_buf
operator|=
name|gimp_temp_buf_new
argument_list|(
name|width
argument_list|,
name|height
argument_list|,
name|gegl_buffer_get_format
argument_list|(
name|src_buffer
argument_list|)
argument_list|)
expr_stmt|;
name|dest_buffer
operator|=
name|gimp_temp_buf_create_buffer
argument_list|(
name|temp_buf
argument_list|)
expr_stmt|;
name|gegl_buffer_copy
argument_list|(
name|src_buffer
argument_list|,
name|GEGL_RECTANGLE
argument_list|(
name|x
operator|+
name|offset_x
argument_list|,
name|y
operator|+
name|offset_y
argument_list|,
name|width
argument_list|,
name|height
argument_list|)
argument_list|,
name|dest_buffer
argument_list|,
name|GEGL_RECTANGLE
argument_list|(
literal|0
argument_list|,
literal|0
argument_list|,
literal|0
argument_list|,
literal|0
argument_list|)
argument_list|)
expr_stmt|;
name|g_object_unref
argument_list|(
name|dest_buffer
argument_list|)
expr_stmt|;
name|pixel_region_init_temp_buf
argument_list|(
operator|&
name|tempPR
argument_list|,
name|temp_buf
argument_list|,
literal|0
argument_list|,
literal|0
argument_list|,
name|width
argument_list|,
name|height
argument_list|)
expr_stmt|;
name|apply_mask_to_region
argument_list|(
operator|&
name|tempPR
argument_list|,
name|maskPR
argument_list|,
name|OPAQUE_OPACITY
argument_list|)
expr_stmt|;
name|pixel_region_init_temp_buf
argument_list|(
operator|&
name|tempPR
argument_list|,
name|temp_buf
argument_list|,
literal|0
argument_list|,
literal|0
argument_list|,
name|width
argument_list|,
name|height
argument_list|)
expr_stmt|;
name|combine_regions_replace
argument_list|(
operator|&
name|src1PR
argument_list|,
operator|&
name|src2PR
argument_list|,
operator|&
name|destPR
argument_list|,
operator|&
name|tempPR
argument_list|,
name|NULL
argument_list|,
name|opacity
operator|*
literal|255.999
argument_list|,
name|active_components
argument_list|,
name|operation
argument_list|)
expr_stmt|;
name|gimp_temp_buf_unref
argument_list|(
name|temp_buf
argument_list|)
expr_stmt|;
block|}
else|else
block|{
name|combine_regions_replace
argument_list|(
operator|&
name|src1PR
argument_list|,
operator|&
name|src2PR
argument_list|,
operator|&
name|destPR
argument_list|,
name|maskPR
argument_list|,
name|NULL
argument_list|,
name|opacity
operator|*
literal|255.999
argument_list|,
name|active_components
argument_list|,
name|operation
argument_list|)
expr_stmt|;
block|}
block|}
end_function

end_unit

