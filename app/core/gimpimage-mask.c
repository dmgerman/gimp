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
file|<gtk/gtk.h>
end_include

begin_include
include|#
directive|include
file|"apptypes.h"
end_include

begin_include
include|#
directive|include
file|"appenv.h"
end_include

begin_include
include|#
directive|include
file|"boundary.h"
end_include

begin_include
include|#
directive|include
file|"drawable.h"
end_include

begin_include
include|#
directive|include
file|"floating_sel.h"
end_include

begin_include
include|#
directive|include
file|"gdisplay.h"
end_include

begin_include
include|#
directive|include
file|"gimpimage.h"
end_include

begin_include
include|#
directive|include
file|"gimage_mask.h"
end_include

begin_include
include|#
directive|include
file|"gimprc.h"
end_include

begin_include
include|#
directive|include
file|"layer.h"
end_include

begin_include
include|#
directive|include
file|"paint_core.h"
end_include

begin_include
include|#
directive|include
file|"paint_funcs.h"
end_include

begin_include
include|#
directive|include
file|"paint_options.h"
end_include

begin_include
include|#
directive|include
file|"pixel_region.h"
end_include

begin_include
include|#
directive|include
file|"procedural_db.h"
end_include

begin_include
include|#
directive|include
file|"tile_manager.h"
end_include

begin_include
include|#
directive|include
file|"tile_manager_pvt.h"
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
comment|/*  local variables  */
end_comment

begin_decl_stmt
DECL|variable|gimage_mask_stroking
specifier|static
name|int
name|gimage_mask_stroking
init|=
name|FALSE
decl_stmt|;
end_decl_stmt

begin_comment
comment|/*  functions  */
end_comment

begin_function
name|gboolean
DECL|function|gimage_mask_boundary (GImage * gimage,BoundSeg ** segs_in,BoundSeg ** segs_out,gint * num_segs_in,gint * num_segs_out)
name|gimage_mask_boundary
parameter_list|(
name|GImage
modifier|*
name|gimage
parameter_list|,
name|BoundSeg
modifier|*
modifier|*
name|segs_in
parameter_list|,
name|BoundSeg
modifier|*
modifier|*
name|segs_out
parameter_list|,
name|gint
modifier|*
name|num_segs_in
parameter_list|,
name|gint
modifier|*
name|num_segs_out
parameter_list|)
block|{
name|GimpDrawable
modifier|*
name|d
decl_stmt|;
name|Layer
modifier|*
name|layer
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
if|if
condition|(
operator|(
name|layer
operator|=
name|gimp_image_floating_sel
argument_list|(
name|gimage
argument_list|)
operator|)
condition|)
block|{
comment|/*  If there is a floating selection, then        *  we need to do some slightly different boundaries.        *  Instead of inside and outside boundaries being defined        *  by the extents of the layer, the inside boundary (the one        *  that actually marches and is black/white) is the boundary of        *  the floating selection.  The outside boundary (doesn't move,        *  is black/gray) is defined as the normal selection mask        */
comment|/*  Find the selection mask boundary  */
name|channel_boundary
argument_list|(
name|gimp_image_get_mask
argument_list|(
name|gimage
argument_list|)
argument_list|,
name|segs_in
argument_list|,
name|segs_out
argument_list|,
name|num_segs_in
argument_list|,
name|num_segs_out
argument_list|,
literal|0
argument_list|,
literal|0
argument_list|,
literal|0
argument_list|,
literal|0
argument_list|)
expr_stmt|;
comment|/*  Find the floating selection boundary  */
operator|*
name|segs_in
operator|=
name|floating_sel_boundary
argument_list|(
name|layer
argument_list|,
name|num_segs_in
argument_list|)
expr_stmt|;
return|return
name|TRUE
return|;
block|}
comment|/*  Otherwise, return the boundary...if a channel is active  */
elseif|else
if|if
condition|(
operator|(
name|d
operator|=
name|gimp_image_active_drawable
argument_list|(
name|gimage
argument_list|)
operator|)
operator|&&
name|GIMP_IS_CHANNEL
argument_list|(
name|d
argument_list|)
condition|)
block|{
return|return
name|channel_boundary
argument_list|(
name|gimp_image_get_mask
argument_list|(
name|gimage
argument_list|)
argument_list|,
name|segs_in
argument_list|,
name|segs_out
argument_list|,
name|num_segs_in
argument_list|,
name|num_segs_out
argument_list|,
literal|0
argument_list|,
literal|0
argument_list|,
name|gimage
operator|->
name|width
argument_list|,
name|gimage
operator|->
name|height
argument_list|)
return|;
block|}
comment|/* if a layer is active, we return multiple boundaries based on the extents */
elseif|else
if|if
condition|(
operator|(
name|layer
operator|=
name|gimp_image_get_active_layer
argument_list|(
name|gimage
argument_list|)
operator|)
condition|)
block|{
name|gint
name|off_x
decl_stmt|,
name|off_y
decl_stmt|;
name|gimp_drawable_offsets
argument_list|(
name|GIMP_DRAWABLE
argument_list|(
name|layer
argument_list|)
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
name|off_x
argument_list|,
literal|0
argument_list|,
name|gimage
operator|->
name|width
argument_list|)
expr_stmt|;
name|y1
operator|=
name|CLAMP
argument_list|(
name|off_y
argument_list|,
literal|0
argument_list|,
name|gimage
operator|->
name|height
argument_list|)
expr_stmt|;
name|x2
operator|=
name|CLAMP
argument_list|(
name|off_x
operator|+
name|gimp_drawable_width
argument_list|(
name|GIMP_DRAWABLE
argument_list|(
name|layer
argument_list|)
argument_list|)
argument_list|,
literal|0
argument_list|,
name|gimage
operator|->
name|width
argument_list|)
expr_stmt|;
name|y2
operator|=
name|CLAMP
argument_list|(
name|off_y
operator|+
name|gimp_drawable_height
argument_list|(
name|GIMP_DRAWABLE
argument_list|(
name|layer
argument_list|)
argument_list|)
argument_list|,
literal|0
argument_list|,
name|gimage
operator|->
name|height
argument_list|)
expr_stmt|;
return|return
name|channel_boundary
argument_list|(
name|gimp_image_get_mask
argument_list|(
name|gimage
argument_list|)
argument_list|,
name|segs_in
argument_list|,
name|segs_out
argument_list|,
name|num_segs_in
argument_list|,
name|num_segs_out
argument_list|,
name|x1
argument_list|,
name|y1
argument_list|,
name|x2
argument_list|,
name|y2
argument_list|)
return|;
block|}
else|else
block|{
operator|*
name|segs_in
operator|=
name|NULL
expr_stmt|;
operator|*
name|segs_out
operator|=
name|NULL
expr_stmt|;
operator|*
name|num_segs_in
operator|=
literal|0
expr_stmt|;
operator|*
name|num_segs_out
operator|=
literal|0
expr_stmt|;
return|return
name|FALSE
return|;
block|}
block|}
end_function

begin_function
name|gboolean
DECL|function|gimage_mask_bounds (GImage * gimage,gint * x1,gint * y1,gint * x2,gint * y2)
name|gimage_mask_bounds
parameter_list|(
name|GImage
modifier|*
name|gimage
parameter_list|,
name|gint
modifier|*
name|x1
parameter_list|,
name|gint
modifier|*
name|y1
parameter_list|,
name|gint
modifier|*
name|x2
parameter_list|,
name|gint
modifier|*
name|y2
parameter_list|)
block|{
return|return
name|channel_bounds
argument_list|(
name|gimp_image_get_mask
argument_list|(
name|gimage
argument_list|)
argument_list|,
name|x1
argument_list|,
name|y1
argument_list|,
name|x2
argument_list|,
name|y2
argument_list|)
return|;
block|}
end_function

begin_function
name|void
DECL|function|gimage_mask_invalidate (GImage * gimage)
name|gimage_mask_invalidate
parameter_list|(
name|GImage
modifier|*
name|gimage
parameter_list|)
block|{
name|Layer
modifier|*
name|layer
decl_stmt|;
name|Channel
modifier|*
name|mask
decl_stmt|;
comment|/*  Turn the current selection off  */
name|gdisplays_selection_visibility
argument_list|(
name|gimage
argument_list|,
name|SelectionOff
argument_list|)
expr_stmt|;
name|mask
operator|=
name|gimp_image_get_mask
argument_list|(
name|gimage
argument_list|)
expr_stmt|;
name|mask
operator|->
name|boundary_known
operator|=
name|FALSE
expr_stmt|;
comment|/*  If there is a floating selection, update it's area...    *  we need to do this since this selection mask can act as an additional    *  mask in the composition of the floating selection    */
name|layer
operator|=
name|gimp_image_get_active_layer
argument_list|(
name|gimage
argument_list|)
expr_stmt|;
if|if
condition|(
name|layer
operator|&&
name|layer_is_floating_sel
argument_list|(
name|layer
argument_list|)
condition|)
name|drawable_update
argument_list|(
name|GIMP_DRAWABLE
argument_list|(
name|layer
argument_list|)
argument_list|,
literal|0
argument_list|,
literal|0
argument_list|,
name|GIMP_DRAWABLE
argument_list|(
name|layer
argument_list|)
operator|->
name|width
argument_list|,
name|GIMP_DRAWABLE
argument_list|(
name|layer
argument_list|)
operator|->
name|height
argument_list|)
expr_stmt|;
block|}
end_function

begin_function
name|gint
DECL|function|gimage_mask_value (GImage * gimage,int x,int y)
name|gimage_mask_value
parameter_list|(
name|GImage
modifier|*
name|gimage
parameter_list|,
name|int
name|x
parameter_list|,
name|int
name|y
parameter_list|)
block|{
return|return
name|channel_value
argument_list|(
name|gimp_image_get_mask
argument_list|(
name|gimage
argument_list|)
argument_list|,
name|x
argument_list|,
name|y
argument_list|)
return|;
block|}
end_function

begin_function
name|gboolean
DECL|function|gimage_mask_is_empty (GImage * gimage)
name|gimage_mask_is_empty
parameter_list|(
name|GImage
modifier|*
name|gimage
parameter_list|)
block|{
comment|/*  in order to allow stroking of selections, we need to pretend here    *  that the selection mask is empty so that it doesn't mask the paint    *  during the stroke operation.    */
if|if
condition|(
name|gimage_mask_stroking
condition|)
return|return
name|TRUE
return|;
else|else
return|return
name|channel_is_empty
argument_list|(
name|gimp_image_get_mask
argument_list|(
name|gimage
argument_list|)
argument_list|)
return|;
block|}
end_function

begin_function
name|void
DECL|function|gimage_mask_translate (GImage * gimage,gint off_x,gint off_y)
name|gimage_mask_translate
parameter_list|(
name|GImage
modifier|*
name|gimage
parameter_list|,
name|gint
name|off_x
parameter_list|,
name|gint
name|off_y
parameter_list|)
block|{
name|channel_translate
argument_list|(
name|gimp_image_get_mask
argument_list|(
name|gimage
argument_list|)
argument_list|,
name|off_x
argument_list|,
name|off_y
argument_list|)
expr_stmt|;
block|}
end_function

begin_function
name|TileManager
modifier|*
DECL|function|gimage_mask_extract (GImage * gimage,GimpDrawable * drawable,gboolean cut_gimage,gboolean keep_indexed,gboolean add_alpha)
name|gimage_mask_extract
parameter_list|(
name|GImage
modifier|*
name|gimage
parameter_list|,
name|GimpDrawable
modifier|*
name|drawable
parameter_list|,
name|gboolean
name|cut_gimage
parameter_list|,
name|gboolean
name|keep_indexed
parameter_list|,
name|gboolean
name|add_alpha
parameter_list|)
block|{
name|TileManager
modifier|*
name|tiles
decl_stmt|;
name|Channel
modifier|*
name|sel_mask
decl_stmt|;
name|PixelRegion
name|srcPR
decl_stmt|,
name|destPR
decl_stmt|,
name|maskPR
decl_stmt|;
name|guchar
name|bg
index|[
name|MAX_CHANNELS
index|]
decl_stmt|;
name|gint
name|bytes
decl_stmt|,
name|type
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
name|gint
name|off_x
decl_stmt|,
name|off_y
decl_stmt|;
name|gboolean
name|non_empty
decl_stmt|;
if|if
condition|(
operator|!
name|drawable
condition|)
return|return
name|NULL
return|;
comment|/*  If there are no bounds, then just extract the entire image    *  This may not be the correct behavior, but after getting rid    *  of floating selections, it's still tempting to "cut" or "copy"    *  a small layer and expect it to work, even though there is no    *  actual selection mask    */
name|non_empty
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
name|non_empty
operator|&&
operator|(
operator|!
operator|(
name|x2
operator|-
name|x1
operator|)
operator|||
operator|!
operator|(
name|y2
operator|-
name|y1
operator|)
operator|)
condition|)
block|{
name|g_message
argument_list|(
name|_
argument_list|(
literal|"Unable to cut/copy because the selected\n"
literal|"region is empty."
argument_list|)
argument_list|)
expr_stmt|;
return|return
name|NULL
return|;
block|}
comment|/*  How many bytes in the temp buffer?  */
switch|switch
condition|(
name|gimp_drawable_type
argument_list|(
name|drawable
argument_list|)
condition|)
block|{
case|case
name|RGB_GIMAGE
case|:
case|case
name|RGBA_GIMAGE
case|:
name|bytes
operator|=
name|add_alpha
condition|?
literal|4
else|:
name|drawable
operator|->
name|bytes
expr_stmt|;
name|type
operator|=
name|RGB
expr_stmt|;
break|break;
case|case
name|GRAY_GIMAGE
case|:
case|case
name|GRAYA_GIMAGE
case|:
name|bytes
operator|=
name|add_alpha
condition|?
literal|2
else|:
name|drawable
operator|->
name|bytes
expr_stmt|;
name|type
operator|=
name|GRAY
expr_stmt|;
break|break;
case|case
name|INDEXED_GIMAGE
case|:
case|case
name|INDEXEDA_GIMAGE
case|:
if|if
condition|(
name|keep_indexed
condition|)
block|{
name|bytes
operator|=
name|add_alpha
condition|?
literal|2
else|:
name|drawable
operator|->
name|bytes
expr_stmt|;
name|type
operator|=
name|GRAY
expr_stmt|;
block|}
else|else
block|{
name|bytes
operator|=
name|add_alpha
condition|?
literal|4
else|:
name|drawable
operator|->
name|bytes
expr_stmt|;
name|type
operator|=
name|INDEXED
expr_stmt|;
block|}
break|break;
default|default:
name|bytes
operator|=
literal|3
expr_stmt|;
name|type
operator|=
name|RGB
expr_stmt|;
break|break;
block|}
comment|/*  get the selection mask */
if|if
condition|(
name|non_empty
condition|)
name|sel_mask
operator|=
name|gimp_image_get_mask
argument_list|(
name|gimage
argument_list|)
expr_stmt|;
else|else
name|sel_mask
operator|=
name|NULL
expr_stmt|;
name|gimp_image_get_background
argument_list|(
name|gimage
argument_list|,
name|drawable
argument_list|,
name|bg
argument_list|)
expr_stmt|;
comment|/*  If a cut was specified, and the selection mask is not empty,    *  push an undo    */
if|if
condition|(
name|cut_gimage
operator|&&
name|non_empty
condition|)
name|drawable_apply_image
argument_list|(
name|drawable
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
comment|/*  Allocate the temp buffer  */
name|tiles
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
name|tiles
operator|->
name|x
operator|=
name|x1
operator|+
name|off_x
expr_stmt|;
name|tiles
operator|->
name|y
operator|=
name|y1
operator|+
name|off_y
expr_stmt|;
comment|/* configure the pixel regions  */
name|pixel_region_init
argument_list|(
operator|&
name|srcPR
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
name|cut_gimage
argument_list|)
expr_stmt|;
name|pixel_region_init
argument_list|(
operator|&
name|destPR
argument_list|,
name|tiles
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
comment|/*  If there is a selection, extract from it  */
if|if
condition|(
name|non_empty
condition|)
block|{
name|pixel_region_init
argument_list|(
operator|&
name|maskPR
argument_list|,
name|GIMP_DRAWABLE
argument_list|(
name|sel_mask
argument_list|)
operator|->
name|tiles
argument_list|,
operator|(
name|x1
operator|+
name|off_x
operator|)
argument_list|,
operator|(
name|y1
operator|+
name|off_y
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
argument_list|,
name|FALSE
argument_list|)
expr_stmt|;
name|extract_from_region
argument_list|(
operator|&
name|srcPR
argument_list|,
operator|&
name|destPR
argument_list|,
operator|&
name|maskPR
argument_list|,
name|gimp_drawable_cmap
argument_list|(
name|drawable
argument_list|)
argument_list|,
name|bg
argument_list|,
name|type
argument_list|,
name|gimp_drawable_has_alpha
argument_list|(
name|drawable
argument_list|)
argument_list|,
name|cut_gimage
argument_list|)
expr_stmt|;
if|if
condition|(
name|cut_gimage
condition|)
block|{
comment|/*  Clear the region  */
name|channel_clear
argument_list|(
name|gimp_image_get_mask
argument_list|(
name|gimage
argument_list|)
argument_list|)
expr_stmt|;
comment|/*  Update the region  */
name|gdisplays_update_area
argument_list|(
name|gimage
argument_list|,
name|tiles
operator|->
name|x
argument_list|,
name|tiles
operator|->
name|y
argument_list|,
name|tiles
operator|->
name|width
argument_list|,
name|tiles
operator|->
name|height
argument_list|)
expr_stmt|;
comment|/*  Invalidate the preview  */
name|gimp_drawable_invalidate_preview
argument_list|(
name|drawable
argument_list|,
name|TRUE
argument_list|)
expr_stmt|;
block|}
block|}
comment|/*  Otherwise, get the entire active layer  */
else|else
block|{
comment|/*  If the layer is indexed...we need to extract pixels  */
if|if
condition|(
name|type
operator|==
name|INDEXED
operator|&&
operator|!
name|keep_indexed
condition|)
name|extract_from_region
argument_list|(
operator|&
name|srcPR
argument_list|,
operator|&
name|destPR
argument_list|,
name|NULL
argument_list|,
name|gimp_drawable_cmap
argument_list|(
name|drawable
argument_list|)
argument_list|,
name|bg
argument_list|,
name|type
argument_list|,
name|gimp_drawable_has_alpha
argument_list|(
name|drawable
argument_list|)
argument_list|,
name|FALSE
argument_list|)
expr_stmt|;
comment|/*  If the layer doesn't have an alpha channel, add one  */
elseif|else
if|if
condition|(
name|bytes
operator|>
name|srcPR
operator|.
name|bytes
condition|)
name|add_alpha_region
argument_list|(
operator|&
name|srcPR
argument_list|,
operator|&
name|destPR
argument_list|)
expr_stmt|;
comment|/*  Otherwise, do a straight copy  */
else|else
name|copy_region
argument_list|(
operator|&
name|srcPR
argument_list|,
operator|&
name|destPR
argument_list|)
expr_stmt|;
comment|/*  If we're cutting, remove either the layer (or floating selection),        *  the layer mask, or the channel        */
if|if
condition|(
name|cut_gimage
operator|&&
name|GIMP_IS_LAYER
argument_list|(
name|drawable
argument_list|)
condition|)
block|{
if|if
condition|(
name|layer_is_floating_sel
argument_list|(
name|GIMP_LAYER
argument_list|(
name|drawable
argument_list|)
argument_list|)
condition|)
name|floating_sel_remove
argument_list|(
name|GIMP_LAYER
argument_list|(
name|drawable
argument_list|)
argument_list|)
expr_stmt|;
else|else
name|gimp_image_remove_layer
argument_list|(
name|gimage
argument_list|,
name|GIMP_LAYER
argument_list|(
name|drawable
argument_list|)
argument_list|)
expr_stmt|;
block|}
elseif|else
if|if
condition|(
name|cut_gimage
operator|&&
name|GIMP_IS_LAYER_MASK
argument_list|(
name|drawable
argument_list|)
condition|)
block|{
name|gimp_image_remove_layer_mask
argument_list|(
name|gimage
argument_list|,
name|layer_mask_get_layer
argument_list|(
name|GIMP_LAYER_MASK
argument_list|(
name|drawable
argument_list|)
argument_list|)
argument_list|,
name|DISCARD
argument_list|)
expr_stmt|;
block|}
elseif|else
if|if
condition|(
name|cut_gimage
operator|&&
name|GIMP_IS_CHANNEL
argument_list|(
name|drawable
argument_list|)
condition|)
name|gimp_image_remove_channel
argument_list|(
name|gimage
argument_list|,
name|GIMP_CHANNEL
argument_list|(
name|drawable
argument_list|)
argument_list|)
expr_stmt|;
block|}
return|return
name|tiles
return|;
block|}
end_function

begin_function
name|Layer
modifier|*
DECL|function|gimage_mask_float (GImage * gimage,GimpDrawable * drawable,gint off_x,gint off_y)
name|gimage_mask_float
parameter_list|(
name|GImage
modifier|*
name|gimage
parameter_list|,
name|GimpDrawable
modifier|*
name|drawable
parameter_list|,
name|gint
name|off_x
parameter_list|,
comment|/* optional offset */
name|gint
name|off_y
parameter_list|)
block|{
name|Layer
modifier|*
name|layer
decl_stmt|;
name|Channel
modifier|*
name|mask
init|=
name|gimp_image_get_mask
argument_list|(
name|gimage
argument_list|)
decl_stmt|;
name|TileManager
modifier|*
name|tiles
decl_stmt|;
name|gboolean
name|non_empty
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
comment|/*  Make sure there is a region to float...  */
name|non_empty
operator|=
name|gimp_drawable_mask_bounds
argument_list|(
operator|(
name|drawable
operator|)
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
operator|!
name|non_empty
operator|||
operator|(
name|x2
operator|-
name|x1
operator|)
operator|==
literal|0
operator|||
operator|(
name|y2
operator|-
name|y1
operator|)
operator|==
literal|0
condition|)
block|{
name|g_message
argument_list|(
name|_
argument_list|(
literal|"Float Selection: No selection to float."
argument_list|)
argument_list|)
expr_stmt|;
return|return
name|NULL
return|;
block|}
comment|/*  Start an undo group  */
name|undo_push_group_start
argument_list|(
name|gimage
argument_list|,
name|FLOAT_MASK_UNDO
argument_list|)
expr_stmt|;
comment|/*  Cut the selected region  */
name|tiles
operator|=
name|gimage_mask_extract
argument_list|(
name|gimage
argument_list|,
name|drawable
argument_list|,
name|TRUE
argument_list|,
name|FALSE
argument_list|,
name|TRUE
argument_list|)
expr_stmt|;
comment|/*  Create a new layer from the buffer  */
name|layer
operator|=
name|layer_new_from_tiles
argument_list|(
name|gimage
argument_list|,
name|gimp_drawable_type_with_alpha
argument_list|(
name|drawable
argument_list|)
argument_list|,
name|tiles
argument_list|,
name|_
argument_list|(
literal|"Floated Layer"
argument_list|)
argument_list|,
name|OPAQUE_OPACITY
argument_list|,
name|NORMAL_MODE
argument_list|)
expr_stmt|;
comment|/*  Set the offsets  */
name|GIMP_DRAWABLE
argument_list|(
name|layer
argument_list|)
operator|->
name|offset_x
operator|=
name|tiles
operator|->
name|x
operator|+
name|off_x
expr_stmt|;
name|GIMP_DRAWABLE
argument_list|(
name|layer
argument_list|)
operator|->
name|offset_y
operator|=
name|tiles
operator|->
name|y
operator|+
name|off_y
expr_stmt|;
comment|/*  Free the temp buffer  */
name|tile_manager_destroy
argument_list|(
name|tiles
argument_list|)
expr_stmt|;
comment|/*  Add the floating layer to the gimage  */
name|floating_sel_attach
argument_list|(
name|layer
argument_list|,
name|drawable
argument_list|)
expr_stmt|;
comment|/*  End an undo group  */
name|undo_push_group_end
argument_list|(
name|gimage
argument_list|)
expr_stmt|;
comment|/*  invalidate the gimage's boundary variables  */
name|mask
operator|->
name|boundary_known
operator|=
name|FALSE
expr_stmt|;
return|return
name|layer
return|;
block|}
end_function

begin_function
name|void
DECL|function|gimage_mask_clear (GImage * gimage)
name|gimage_mask_clear
parameter_list|(
name|GImage
modifier|*
name|gimage
parameter_list|)
block|{
name|channel_clear
argument_list|(
name|gimp_image_get_mask
argument_list|(
name|gimage
argument_list|)
argument_list|)
expr_stmt|;
block|}
end_function

begin_function
name|void
DECL|function|gimage_mask_undo (GImage * gimage)
name|gimage_mask_undo
parameter_list|(
name|GImage
modifier|*
name|gimage
parameter_list|)
block|{
name|channel_push_undo
argument_list|(
name|gimp_image_get_mask
argument_list|(
name|gimage
argument_list|)
argument_list|)
expr_stmt|;
block|}
end_function

begin_function
name|void
DECL|function|gimage_mask_invert (GImage * gimage)
name|gimage_mask_invert
parameter_list|(
name|GImage
modifier|*
name|gimage
parameter_list|)
block|{
name|channel_invert
argument_list|(
name|gimp_image_get_mask
argument_list|(
name|gimage
argument_list|)
argument_list|)
expr_stmt|;
block|}
end_function

begin_function
name|void
DECL|function|gimage_mask_sharpen (GImage * gimage)
name|gimage_mask_sharpen
parameter_list|(
name|GImage
modifier|*
name|gimage
parameter_list|)
block|{
comment|/*  No need to play with the selection visibility    *  because sharpen will not change the outline    */
name|channel_sharpen
argument_list|(
name|gimp_image_get_mask
argument_list|(
name|gimage
argument_list|)
argument_list|)
expr_stmt|;
block|}
end_function

begin_function
name|void
DECL|function|gimage_mask_all (GImage * gimage)
name|gimage_mask_all
parameter_list|(
name|GImage
modifier|*
name|gimage
parameter_list|)
block|{
name|channel_all
argument_list|(
name|gimp_image_get_mask
argument_list|(
name|gimage
argument_list|)
argument_list|)
expr_stmt|;
block|}
end_function

begin_function
name|void
DECL|function|gimage_mask_none (GImage * gimage)
name|gimage_mask_none
parameter_list|(
name|GImage
modifier|*
name|gimage
parameter_list|)
block|{
name|channel_clear
argument_list|(
name|gimp_image_get_mask
argument_list|(
name|gimage
argument_list|)
argument_list|)
expr_stmt|;
block|}
end_function

begin_function
name|void
DECL|function|gimage_mask_feather (GImage * gimage,gdouble feather_radius_x,gdouble feather_radius_y)
name|gimage_mask_feather
parameter_list|(
name|GImage
modifier|*
name|gimage
parameter_list|,
name|gdouble
name|feather_radius_x
parameter_list|,
name|gdouble
name|feather_radius_y
parameter_list|)
block|{
comment|/*  push the current mask onto the undo stack--need to do this here because    *  channel_feather doesn't do it    */
name|channel_push_undo
argument_list|(
name|gimp_image_get_mask
argument_list|(
name|gimage
argument_list|)
argument_list|)
expr_stmt|;
comment|/*  feather the region  */
name|channel_feather
argument_list|(
name|gimp_image_get_mask
argument_list|(
name|gimage
argument_list|)
argument_list|,
name|gimp_image_get_mask
argument_list|(
name|gimage
argument_list|)
argument_list|,
name|feather_radius_x
argument_list|,
name|feather_radius_y
argument_list|,
name|CHANNEL_OP_REPLACE
argument_list|,
literal|0
argument_list|,
literal|0
argument_list|)
expr_stmt|;
block|}
end_function

begin_function
name|void
DECL|function|gimage_mask_border (GImage * gimage,gint border_radius_x,gint border_radius_y)
name|gimage_mask_border
parameter_list|(
name|GImage
modifier|*
name|gimage
parameter_list|,
name|gint
name|border_radius_x
parameter_list|,
name|gint
name|border_radius_y
parameter_list|)
block|{
comment|/*  feather the region  */
name|channel_border
argument_list|(
name|gimp_image_get_mask
argument_list|(
name|gimage
argument_list|)
argument_list|,
name|border_radius_x
argument_list|,
name|border_radius_y
argument_list|)
expr_stmt|;
block|}
end_function

begin_function
name|void
DECL|function|gimage_mask_grow (GImage * gimage,int grow_pixels_x,int grow_pixels_y)
name|gimage_mask_grow
parameter_list|(
name|GImage
modifier|*
name|gimage
parameter_list|,
name|int
name|grow_pixels_x
parameter_list|,
name|int
name|grow_pixels_y
parameter_list|)
block|{
comment|/*  feather the region  */
name|channel_grow
argument_list|(
name|gimp_image_get_mask
argument_list|(
name|gimage
argument_list|)
argument_list|,
name|grow_pixels_x
argument_list|,
name|grow_pixels_y
argument_list|)
expr_stmt|;
block|}
end_function

begin_function
name|void
DECL|function|gimage_mask_shrink (GImage * gimage,gint shrink_pixels_x,gint shrink_pixels_y,gboolean edge_lock)
name|gimage_mask_shrink
parameter_list|(
name|GImage
modifier|*
name|gimage
parameter_list|,
name|gint
name|shrink_pixels_x
parameter_list|,
name|gint
name|shrink_pixels_y
parameter_list|,
name|gboolean
name|edge_lock
parameter_list|)
block|{
comment|/*  feather the region  */
name|channel_shrink
argument_list|(
name|gimp_image_get_mask
argument_list|(
name|gimage
argument_list|)
argument_list|,
name|shrink_pixels_x
argument_list|,
name|shrink_pixels_y
argument_list|,
name|edge_lock
argument_list|)
expr_stmt|;
block|}
end_function

begin_function
name|void
DECL|function|gimage_mask_layer_alpha (GImage * gimage,Layer * layer)
name|gimage_mask_layer_alpha
parameter_list|(
name|GImage
modifier|*
name|gimage
parameter_list|,
name|Layer
modifier|*
name|layer
parameter_list|)
block|{
comment|/*  extract the layer's alpha channel  */
if|if
condition|(
name|gimp_drawable_has_alpha
argument_list|(
name|GIMP_DRAWABLE
argument_list|(
name|layer
argument_list|)
argument_list|)
condition|)
block|{
comment|/*  load the mask with the given layer's alpha channel  */
name|channel_layer_alpha
argument_list|(
name|gimp_image_get_mask
argument_list|(
name|gimage
argument_list|)
argument_list|,
name|layer
argument_list|)
expr_stmt|;
block|}
else|else
block|{
name|g_message
argument_list|(
name|_
argument_list|(
literal|"The active layer has no alpha channel\n"
literal|"to convert to a selection."
argument_list|)
argument_list|)
expr_stmt|;
return|return;
block|}
block|}
end_function

begin_function
name|void
DECL|function|gimage_mask_layer_mask (GImage * gimage,Layer * layer)
name|gimage_mask_layer_mask
parameter_list|(
name|GImage
modifier|*
name|gimage
parameter_list|,
name|Layer
modifier|*
name|layer
parameter_list|)
block|{
comment|/*  extract the layer's alpha channel  */
if|if
condition|(
name|layer_get_mask
argument_list|(
name|layer
argument_list|)
condition|)
block|{
comment|/*  load the mask with the given layer's alpha channel  */
name|channel_layer_mask
argument_list|(
name|gimp_image_get_mask
argument_list|(
name|gimage
argument_list|)
argument_list|,
name|layer
argument_list|)
expr_stmt|;
block|}
else|else
block|{
name|g_message
argument_list|(
name|_
argument_list|(
literal|"The active layer has no mask\n"
literal|"to convert to a selection."
argument_list|)
argument_list|)
expr_stmt|;
return|return;
block|}
block|}
end_function

begin_function
name|void
DECL|function|gimage_mask_load (GImage * gimage,Channel * channel)
name|gimage_mask_load
parameter_list|(
name|GImage
modifier|*
name|gimage
parameter_list|,
name|Channel
modifier|*
name|channel
parameter_list|)
block|{
comment|/*  Load the specified channel to the gimage mask  */
name|channel_load
argument_list|(
name|gimp_image_get_mask
argument_list|(
name|gimage
argument_list|)
argument_list|,
operator|(
name|channel
operator|)
argument_list|)
expr_stmt|;
block|}
end_function

begin_function
name|Channel
modifier|*
DECL|function|gimage_mask_save (GImage * gimage)
name|gimage_mask_save
parameter_list|(
name|GImage
modifier|*
name|gimage
parameter_list|)
block|{
name|Channel
modifier|*
name|new_channel
decl_stmt|;
name|new_channel
operator|=
name|channel_copy
argument_list|(
name|gimp_image_get_mask
argument_list|(
name|gimage
argument_list|)
argument_list|)
expr_stmt|;
comment|/*  saved selections are not visible by default  */
name|GIMP_DRAWABLE
argument_list|(
name|new_channel
argument_list|)
operator|->
name|visible
operator|=
name|FALSE
expr_stmt|;
name|gimp_image_add_channel
argument_list|(
name|gimage
argument_list|,
name|new_channel
argument_list|,
operator|-
literal|1
argument_list|)
expr_stmt|;
return|return
name|new_channel
return|;
block|}
end_function

begin_function
name|gboolean
DECL|function|gimage_mask_stroke (GImage * gimage,GimpDrawable * drawable)
name|gimage_mask_stroke
parameter_list|(
name|GImage
modifier|*
name|gimage
parameter_list|,
name|GimpDrawable
modifier|*
name|drawable
parameter_list|)
block|{
name|BoundSeg
modifier|*
name|bs_in
decl_stmt|;
name|BoundSeg
modifier|*
name|bs_out
decl_stmt|;
name|gint
name|num_segs_in
decl_stmt|;
name|gint
name|num_segs_out
decl_stmt|;
name|BoundSeg
modifier|*
name|stroke_segs
decl_stmt|;
name|gint
name|num_strokes
decl_stmt|;
name|gint
name|seg
decl_stmt|;
name|gint
name|offx
decl_stmt|,
name|offy
decl_stmt|;
name|gint
name|i
decl_stmt|;
name|gdouble
modifier|*
name|stroke_points
decl_stmt|;
name|gint
name|cpnt
decl_stmt|;
name|Argument
modifier|*
name|return_vals
decl_stmt|;
name|gint
name|nreturn_vals
decl_stmt|;
if|if
condition|(
operator|!
name|gimage_mask_boundary
argument_list|(
name|gimage
argument_list|,
operator|&
name|bs_in
argument_list|,
operator|&
name|bs_out
argument_list|,
operator|&
name|num_segs_in
argument_list|,
operator|&
name|num_segs_out
argument_list|)
condition|)
block|{
name|g_message
argument_list|(
name|_
argument_list|(
literal|"No selection to stroke!"
argument_list|)
argument_list|)
expr_stmt|;
return|return
name|FALSE
return|;
block|}
name|stroke_segs
operator|=
name|sort_boundary
argument_list|(
name|bs_in
argument_list|,
name|num_segs_in
argument_list|,
operator|&
name|num_strokes
argument_list|)
expr_stmt|;
if|if
condition|(
name|num_strokes
operator|==
literal|0
condition|)
return|return
name|TRUE
return|;
comment|/*  find the drawable offsets  */
name|gimp_drawable_offsets
argument_list|(
name|drawable
argument_list|,
operator|&
name|offx
argument_list|,
operator|&
name|offy
argument_list|)
expr_stmt|;
name|gimage_mask_stroking
operator|=
name|TRUE
expr_stmt|;
comment|/*  Start an undo group  */
name|undo_push_group_start
argument_list|(
name|gimage
argument_list|,
name|PAINT_CORE_UNDO
argument_list|)
expr_stmt|;
name|seg
operator|=
literal|0
expr_stmt|;
name|cpnt
operator|=
literal|0
expr_stmt|;
comment|/* Largest array required (may be used in segments!) */
name|stroke_points
operator|=
name|g_malloc
argument_list|(
sizeof|sizeof
argument_list|(
name|gdouble
argument_list|)
operator|*
literal|2
operator|*
operator|(
name|num_segs_in
operator|+
literal|4
operator|)
argument_list|)
expr_stmt|;
comment|/* we offset all coordinates by 0.5 to align the brush with the path */
name|stroke_points
index|[
name|cpnt
operator|++
index|]
operator|=
call|(
name|gdouble
call|)
argument_list|(
name|stroke_segs
index|[
literal|0
index|]
operator|.
name|x1
operator|-
name|offx
operator|+
literal|0.5
argument_list|)
expr_stmt|;
name|stroke_points
index|[
name|cpnt
operator|++
index|]
operator|=
call|(
name|gdouble
call|)
argument_list|(
name|stroke_segs
index|[
literal|0
index|]
operator|.
name|y1
operator|-
name|offy
operator|+
literal|0.5
argument_list|)
expr_stmt|;
for|for
control|(
name|i
operator|=
literal|0
init|;
name|i
operator|<
name|num_strokes
condition|;
name|i
operator|++
control|)
block|{
while|while
condition|(
operator|(
name|stroke_segs
index|[
name|seg
index|]
operator|.
name|x1
operator|!=
operator|-
literal|1
operator|||
name|stroke_segs
index|[
name|seg
index|]
operator|.
name|x2
operator|!=
operator|-
literal|1
operator|||
name|stroke_segs
index|[
name|seg
index|]
operator|.
name|y1
operator|!=
operator|-
literal|1
operator|||
name|stroke_segs
index|[
name|seg
index|]
operator|.
name|y2
operator|!=
operator|-
literal|1
operator|)
condition|)
block|{
name|stroke_points
index|[
name|cpnt
operator|++
index|]
operator|=
call|(
name|gdouble
call|)
argument_list|(
name|stroke_segs
index|[
name|seg
index|]
operator|.
name|x2
operator|-
name|offx
operator|+
literal|0.5
argument_list|)
expr_stmt|;
name|stroke_points
index|[
name|cpnt
operator|++
index|]
operator|=
call|(
name|gdouble
call|)
argument_list|(
name|stroke_segs
index|[
name|seg
index|]
operator|.
name|y2
operator|-
name|offy
operator|+
literal|0.5
argument_list|)
expr_stmt|;
name|seg
operator|++
expr_stmt|;
block|}
comment|/* Close the stroke points up */
name|stroke_points
index|[
name|cpnt
operator|++
index|]
operator|=
name|stroke_points
index|[
literal|0
index|]
expr_stmt|;
name|stroke_points
index|[
name|cpnt
operator|++
index|]
operator|=
name|stroke_points
index|[
literal|1
index|]
expr_stmt|;
comment|/* Stroke with the correct tool */
name|return_vals
operator|=
name|procedural_db_run_proc
argument_list|(
name|tool_active_PDB_string
argument_list|()
argument_list|,
operator|&
name|nreturn_vals
argument_list|,
name|PDB_DRAWABLE
argument_list|,
name|gimp_drawable_get_ID
argument_list|(
name|drawable
argument_list|)
argument_list|,
name|PDB_INT32
argument_list|,
operator|(
name|gint32
operator|)
name|cpnt
argument_list|,
name|PDB_FLOATARRAY
argument_list|,
name|stroke_points
argument_list|,
name|PDB_END
argument_list|)
expr_stmt|;
if|if
condition|(
name|return_vals
operator|&&
name|return_vals
index|[
literal|0
index|]
operator|.
name|value
operator|.
name|pdb_int
operator|==
name|PDB_SUCCESS
condition|)
block|{
comment|/* Not required */
comment|/*gdisplays_flush ();*/
block|}
else|else
name|g_message
argument_list|(
name|_
argument_list|(
literal|"Paintbrush operation failed."
argument_list|)
argument_list|)
expr_stmt|;
name|procedural_db_destroy_args
argument_list|(
name|return_vals
argument_list|,
name|nreturn_vals
argument_list|)
expr_stmt|;
name|cpnt
operator|=
literal|0
expr_stmt|;
name|seg
operator|++
expr_stmt|;
name|stroke_points
index|[
name|cpnt
operator|++
index|]
operator|=
call|(
name|gdouble
call|)
argument_list|(
name|stroke_segs
index|[
name|seg
index|]
operator|.
name|x1
operator|-
name|offx
operator|+
literal|0.5
argument_list|)
expr_stmt|;
name|stroke_points
index|[
name|cpnt
operator|++
index|]
operator|=
call|(
name|gdouble
call|)
argument_list|(
name|stroke_segs
index|[
name|seg
index|]
operator|.
name|y1
operator|-
name|offy
operator|+
literal|0.5
argument_list|)
expr_stmt|;
block|}
comment|/*  cleanup  */
name|gimage_mask_stroking
operator|=
name|FALSE
expr_stmt|;
name|g_free
argument_list|(
name|stroke_points
argument_list|)
expr_stmt|;
name|g_free
argument_list|(
name|stroke_segs
argument_list|)
expr_stmt|;
comment|/*  End an undo group  */
name|undo_push_group_end
argument_list|(
name|gimage
argument_list|)
expr_stmt|;
return|return
name|TRUE
return|;
block|}
end_function

end_unit

