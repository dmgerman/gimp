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
file|"base/pixel-region.h"
end_include

begin_include
include|#
directive|include
file|"paint-funcs/paint-funcs.h"
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
file|"gimpimage.h"
end_include

begin_function
name|void
DECL|function|gimp_drawable_real_apply_region (GimpDrawable * drawable,PixelRegion * src2PR,gboolean push_undo,const gchar * undo_desc,gdouble opacity,GimpLayerModeEffects mode,TileManager * src1_tiles,gint x,gint y)
name|gimp_drawable_real_apply_region
parameter_list|(
name|GimpDrawable
modifier|*
name|drawable
parameter_list|,
name|PixelRegion
modifier|*
name|src2PR
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
name|TileManager
modifier|*
name|src1_tiles
parameter_list|,
name|gint
name|x
parameter_list|,
name|gint
name|y
parameter_list|)
block|{
name|GimpImage
modifier|*
name|image
decl_stmt|;
name|GimpItem
modifier|*
name|item
decl_stmt|;
name|GimpChannel
modifier|*
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
name|gint
name|offset_x
decl_stmt|,
name|offset_y
decl_stmt|;
name|PixelRegion
name|src1PR
decl_stmt|,
name|destPR
decl_stmt|,
name|maskPR
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
name|item
operator|=
name|GIMP_ITEM
argument_list|(
name|drawable
argument_list|)
expr_stmt|;
name|image
operator|=
name|gimp_item_get_image
argument_list|(
name|item
argument_list|)
expr_stmt|;
name|mask
operator|=
name|gimp_image_get_mask
argument_list|(
name|image
argument_list|)
expr_stmt|;
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
operator|->
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
name|gimp_item_offsets
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
comment|/*  make sure the image application coordinates are within image bounds  */
name|x1
operator|=
name|CLAMP
argument_list|(
name|x
argument_list|,
literal|0
argument_list|,
name|gimp_item_width
argument_list|(
name|item
argument_list|)
argument_list|)
expr_stmt|;
name|y1
operator|=
name|CLAMP
argument_list|(
name|y
argument_list|,
literal|0
argument_list|,
name|gimp_item_height
argument_list|(
name|item
argument_list|)
argument_list|)
expr_stmt|;
name|x2
operator|=
name|CLAMP
argument_list|(
name|x
operator|+
name|src2PR
operator|->
name|w
argument_list|,
literal|0
argument_list|,
name|gimp_item_width
argument_list|(
name|item
argument_list|)
argument_list|)
expr_stmt|;
name|y2
operator|=
name|CLAMP
argument_list|(
name|y
operator|+
name|src2PR
operator|->
name|h
argument_list|,
literal|0
argument_list|,
name|gimp_item_height
argument_list|(
name|item
argument_list|)
argument_list|)
expr_stmt|;
if|if
condition|(
name|mask
condition|)
block|{
comment|/*  make sure coordinates are in mask bounds ...        *  we need to add the layer offset to transform coords        *  into the mask coordinate system        */
name|x1
operator|=
name|CLAMP
argument_list|(
name|x1
argument_list|,
operator|-
name|offset_x
argument_list|,
name|gimp_item_width
argument_list|(
name|GIMP_ITEM
argument_list|(
name|mask
argument_list|)
argument_list|)
operator|-
name|offset_x
argument_list|)
expr_stmt|;
name|y1
operator|=
name|CLAMP
argument_list|(
name|y1
argument_list|,
operator|-
name|offset_y
argument_list|,
name|gimp_item_height
argument_list|(
name|GIMP_ITEM
argument_list|(
name|mask
argument_list|)
argument_list|)
operator|-
name|offset_y
argument_list|)
expr_stmt|;
name|x2
operator|=
name|CLAMP
argument_list|(
name|x2
argument_list|,
operator|-
name|offset_x
argument_list|,
name|gimp_item_width
argument_list|(
name|GIMP_ITEM
argument_list|(
name|mask
argument_list|)
argument_list|)
operator|-
name|offset_x
argument_list|)
expr_stmt|;
name|y2
operator|=
name|CLAMP
argument_list|(
name|y2
argument_list|,
operator|-
name|offset_y
argument_list|,
name|gimp_item_height
argument_list|(
name|GIMP_ITEM
argument_list|(
name|mask
argument_list|)
argument_list|)
operator|-
name|offset_y
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
name|x1
argument_list|,
name|y1
argument_list|,
name|x2
argument_list|,
name|y2
argument_list|,
name|NULL
argument_list|,
name|FALSE
argument_list|)
expr_stmt|;
comment|/* configure the pixel regions    *  If an alternative to using the drawable's data as src1 was provided...    */
if|if
condition|(
name|src1_tiles
condition|)
name|pixel_region_init
argument_list|(
operator|&
name|src1PR
argument_list|,
name|src1_tiles
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
else|else
name|pixel_region_init
argument_list|(
operator|&
name|src1PR
argument_list|,
name|gimp_drawable_data
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
name|gimp_drawable_data
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
name|pixel_region_resize
argument_list|(
name|src2PR
argument_list|,
name|src2PR
operator|->
name|x
operator|+
operator|(
name|x1
operator|-
name|x
operator|)
argument_list|,
name|src2PR
operator|->
name|y
operator|+
operator|(
name|y1
operator|-
name|y
operator|)
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
if|if
condition|(
name|mask
condition|)
block|{
name|gint
name|mx
decl_stmt|,
name|my
decl_stmt|;
comment|/*  configure the mask pixel region        *  don't use x1 and y1 because they are in layer        *  coordinate system.  Need mask coordinate system        */
name|mx
operator|=
name|x1
operator|+
name|offset_x
expr_stmt|;
name|my
operator|=
name|y1
operator|+
name|offset_y
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
name|mx
argument_list|,
name|my
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
name|combine_regions
argument_list|(
operator|&
name|src1PR
argument_list|,
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
end_function

begin_comment
comment|/*  Similar to gimp_drawable_apply_region but works in "replace" mode (i.e.  *  transparent pixels in src2 make the result transparent rather than  *  opaque.  *  * Takes an additional mask pixel region as well.  */
end_comment

begin_function
name|void
DECL|function|gimp_drawable_real_replace_region (GimpDrawable * drawable,PixelRegion * src2PR,gboolean push_undo,const gchar * undo_desc,gdouble opacity,PixelRegion * maskPR,gint x,gint y)
name|gimp_drawable_real_replace_region
parameter_list|(
name|GimpDrawable
modifier|*
name|drawable
parameter_list|,
name|PixelRegion
modifier|*
name|src2PR
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
name|x
parameter_list|,
name|gint
name|y
parameter_list|)
block|{
name|GimpImage
modifier|*
name|image
decl_stmt|;
name|GimpItem
modifier|*
name|item
decl_stmt|;
name|GimpChannel
modifier|*
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
name|item
operator|=
name|GIMP_ITEM
argument_list|(
name|drawable
argument_list|)
expr_stmt|;
name|image
operator|=
name|gimp_item_get_image
argument_list|(
name|item
argument_list|)
expr_stmt|;
name|mask
operator|=
name|gimp_image_get_mask
argument_list|(
name|image
argument_list|)
expr_stmt|;
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
operator|->
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
name|gimp_item_offsets
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
comment|/*  make sure the image application coordinates are within image bounds  */
name|x1
operator|=
name|CLAMP
argument_list|(
name|x
argument_list|,
literal|0
argument_list|,
name|gimp_item_width
argument_list|(
name|item
argument_list|)
argument_list|)
expr_stmt|;
name|y1
operator|=
name|CLAMP
argument_list|(
name|y
argument_list|,
literal|0
argument_list|,
name|gimp_item_height
argument_list|(
name|item
argument_list|)
argument_list|)
expr_stmt|;
name|x2
operator|=
name|CLAMP
argument_list|(
name|x
operator|+
name|src2PR
operator|->
name|w
argument_list|,
literal|0
argument_list|,
name|gimp_item_width
argument_list|(
name|item
argument_list|)
argument_list|)
expr_stmt|;
name|y2
operator|=
name|CLAMP
argument_list|(
name|y
operator|+
name|src2PR
operator|->
name|h
argument_list|,
literal|0
argument_list|,
name|gimp_item_height
argument_list|(
name|item
argument_list|)
argument_list|)
expr_stmt|;
if|if
condition|(
name|mask
condition|)
block|{
comment|/*  make sure coordinates are in mask bounds ...        *  we need to add the layer offset to transform coords        *  into the mask coordinate system        */
name|x1
operator|=
name|CLAMP
argument_list|(
name|x1
argument_list|,
operator|-
name|offset_x
argument_list|,
name|gimp_item_width
argument_list|(
name|GIMP_ITEM
argument_list|(
name|mask
argument_list|)
argument_list|)
operator|-
name|offset_x
argument_list|)
expr_stmt|;
name|y1
operator|=
name|CLAMP
argument_list|(
name|y1
argument_list|,
operator|-
name|offset_y
argument_list|,
name|gimp_item_height
argument_list|(
name|GIMP_ITEM
argument_list|(
name|mask
argument_list|)
argument_list|)
operator|-
name|offset_y
argument_list|)
expr_stmt|;
name|x2
operator|=
name|CLAMP
argument_list|(
name|x2
argument_list|,
operator|-
name|offset_x
argument_list|,
name|gimp_item_width
argument_list|(
name|GIMP_ITEM
argument_list|(
name|mask
argument_list|)
argument_list|)
operator|-
name|offset_x
argument_list|)
expr_stmt|;
name|y2
operator|=
name|CLAMP
argument_list|(
name|y2
argument_list|,
operator|-
name|offset_y
argument_list|,
name|gimp_item_height
argument_list|(
name|GIMP_ITEM
argument_list|(
name|mask
argument_list|)
argument_list|)
operator|-
name|offset_y
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
name|x1
argument_list|,
name|y1
argument_list|,
name|x2
argument_list|,
name|y2
argument_list|,
name|NULL
argument_list|,
name|FALSE
argument_list|)
expr_stmt|;
comment|/* configure the pixel regions    *  If an alternative to using the drawable's data as src1 was provided...    */
name|pixel_region_init
argument_list|(
operator|&
name|src1PR
argument_list|,
name|gimp_drawable_data
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
name|gimp_drawable_data
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
name|pixel_region_resize
argument_list|(
name|src2PR
argument_list|,
name|src2PR
operator|->
name|x
operator|+
operator|(
name|x1
operator|-
name|x
operator|)
argument_list|,
name|src2PR
operator|->
name|y
operator|+
operator|(
name|y1
operator|-
name|y
operator|)
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
if|if
condition|(
name|mask
condition|)
block|{
name|PixelRegion
name|mask2PR
decl_stmt|,
name|tempPR
decl_stmt|;
name|guchar
modifier|*
name|temp_data
decl_stmt|;
name|gint
name|mx
decl_stmt|,
name|my
decl_stmt|;
comment|/*  configure the mask pixel region        *  don't use x1 and y1 because they are in layer        *  coordinate system.  Need mask coordinate system        */
name|mx
operator|=
name|x1
operator|+
name|offset_x
expr_stmt|;
name|my
operator|=
name|y1
operator|+
name|offset_y
expr_stmt|;
name|pixel_region_init
argument_list|(
operator|&
name|mask2PR
argument_list|,
name|gimp_drawable_data
argument_list|(
name|GIMP_DRAWABLE
argument_list|(
name|mask
argument_list|)
argument_list|)
argument_list|,
name|mx
argument_list|,
name|my
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
name|temp_data
operator|=
name|g_malloc
argument_list|(
operator|(
name|y2
operator|-
name|y1
operator|)
operator|*
operator|(
name|x2
operator|-
name|x1
operator|)
argument_list|)
expr_stmt|;
name|pixel_region_init_data
argument_list|(
operator|&
name|tempPR
argument_list|,
name|temp_data
argument_list|,
literal|1
argument_list|,
name|x2
operator|-
name|x1
argument_list|,
literal|0
argument_list|,
literal|0
argument_list|,
name|x2
operator|-
name|x1
argument_list|,
name|y2
operator|-
name|y1
argument_list|)
expr_stmt|;
name|copy_region
argument_list|(
operator|&
name|mask2PR
argument_list|,
operator|&
name|tempPR
argument_list|)
expr_stmt|;
name|pixel_region_init_data
argument_list|(
operator|&
name|tempPR
argument_list|,
name|temp_data
argument_list|,
literal|1
argument_list|,
name|x2
operator|-
name|x1
argument_list|,
literal|0
argument_list|,
literal|0
argument_list|,
name|x2
operator|-
name|x1
argument_list|,
name|y2
operator|-
name|y1
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
name|pixel_region_init_data
argument_list|(
operator|&
name|tempPR
argument_list|,
name|temp_data
argument_list|,
literal|1
argument_list|,
name|x2
operator|-
name|x1
argument_list|,
literal|0
argument_list|,
literal|0
argument_list|,
name|x2
operator|-
name|x1
argument_list|,
name|y2
operator|-
name|y1
argument_list|)
expr_stmt|;
name|combine_regions_replace
argument_list|(
operator|&
name|src1PR
argument_list|,
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
name|g_free
argument_list|(
name|temp_data
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

