begin_unit|revision:0.9.5;language:C;cregit-version:0.0.1
begin_comment
comment|/* GIMP - The GNU Image Manipulation Program  * Copyright (C) 1995 Spencer Kimball and Peter Mattis  *  * This program is free software; you can redistribute it and/or modify  * it under the terms of the GNU General Public License as published by  * the Free Software Foundation; either version 2 of the License, or  * (at your option) any later version.  *  * This program is distributed in the hope that it will be useful,  * but WITHOUT ANY WARRANTY; without even the implied warranty of  * MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the  * GNU General Public License for more details.  *  * You should have received a copy of the GNU General Public License  * along with this program; if not, write to the Free Software  * Foundation, Inc., 59 Temple Place - Suite 330, Boston, MA 02111-1307, USA.  */
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
file|"gimpimage.h"
end_include

begin_include
include|#
directive|include
file|"gimpimage-colormap.h"
end_include

begin_include
include|#
directive|include
file|"gimplayer.h"
end_include

begin_include
include|#
directive|include
file|"gimplayer-floating-sel.h"
end_include

begin_include
include|#
directive|include
file|"gimplayermask.h"
end_include

begin_include
include|#
directive|include
file|"gimppickable.h"
end_include

begin_include
include|#
directive|include
file|"gimpprojectable.h"
end_include

begin_include
include|#
directive|include
file|"gimpprojection.h"
end_include

begin_include
include|#
directive|include
file|"gimpprojection-construct.h"
end_include

begin_comment
comment|/*  local function prototypes  */
end_comment

begin_function_decl
specifier|static
name|void
name|gimp_projection_construct_gegl
parameter_list|(
name|GimpProjection
modifier|*
name|proj
parameter_list|,
name|gint
name|x
parameter_list|,
name|gint
name|y
parameter_list|,
name|gint
name|w
parameter_list|,
name|gint
name|h
parameter_list|)
function_decl|;
end_function_decl

begin_function_decl
specifier|static
name|void
name|gimp_projection_construct_layers
parameter_list|(
name|GimpProjection
modifier|*
name|proj
parameter_list|,
name|gint
name|x
parameter_list|,
name|gint
name|y
parameter_list|,
name|gint
name|w
parameter_list|,
name|gint
name|h
parameter_list|)
function_decl|;
end_function_decl

begin_function_decl
specifier|static
name|void
name|gimp_projection_construct_channels
parameter_list|(
name|GimpProjection
modifier|*
name|proj
parameter_list|,
name|gint
name|x
parameter_list|,
name|gint
name|y
parameter_list|,
name|gint
name|w
parameter_list|,
name|gint
name|h
parameter_list|)
function_decl|;
end_function_decl

begin_function_decl
specifier|static
name|void
name|gimp_projection_initialize
parameter_list|(
name|GimpProjection
modifier|*
name|proj
parameter_list|,
name|gint
name|x
parameter_list|,
name|gint
name|y
parameter_list|,
name|gint
name|w
parameter_list|,
name|gint
name|h
parameter_list|)
function_decl|;
end_function_decl

begin_function_decl
specifier|static
name|void
name|project_intensity
parameter_list|(
name|GimpProjection
modifier|*
name|proj
parameter_list|,
name|GimpLayer
modifier|*
name|layer
parameter_list|,
name|PixelRegion
modifier|*
name|src
parameter_list|,
name|PixelRegion
modifier|*
name|dest
parameter_list|,
name|PixelRegion
modifier|*
name|mask
parameter_list|)
function_decl|;
end_function_decl

begin_function_decl
specifier|static
name|void
name|project_intensity_alpha
parameter_list|(
name|GimpProjection
modifier|*
name|proj
parameter_list|,
name|GimpLayer
modifier|*
name|layer
parameter_list|,
name|PixelRegion
modifier|*
name|src
parameter_list|,
name|PixelRegion
modifier|*
name|dest
parameter_list|,
name|PixelRegion
modifier|*
name|mask
parameter_list|)
function_decl|;
end_function_decl

begin_function_decl
specifier|static
name|void
name|project_indexed
parameter_list|(
name|GimpProjection
modifier|*
name|proj
parameter_list|,
name|GimpLayer
modifier|*
name|layer
parameter_list|,
name|PixelRegion
modifier|*
name|src
parameter_list|,
name|PixelRegion
modifier|*
name|dest
parameter_list|,
name|PixelRegion
modifier|*
name|mask
parameter_list|)
function_decl|;
end_function_decl

begin_function_decl
specifier|static
name|void
name|project_indexed_alpha
parameter_list|(
name|GimpProjection
modifier|*
name|proj
parameter_list|,
name|GimpLayer
modifier|*
name|layer
parameter_list|,
name|PixelRegion
modifier|*
name|src
parameter_list|,
name|PixelRegion
modifier|*
name|dest
parameter_list|,
name|PixelRegion
modifier|*
name|mask
parameter_list|)
function_decl|;
end_function_decl

begin_function_decl
specifier|static
name|void
name|project_channel
parameter_list|(
name|GimpProjection
modifier|*
name|proj
parameter_list|,
name|GimpChannel
modifier|*
name|channel
parameter_list|,
name|PixelRegion
modifier|*
name|src
parameter_list|,
name|PixelRegion
modifier|*
name|src2
parameter_list|)
function_decl|;
end_function_decl

begin_comment
comment|/*  public functions  */
end_comment

begin_function
name|void
DECL|function|gimp_projection_construct (GimpProjection * proj,gint x,gint y,gint w,gint h)
name|gimp_projection_construct
parameter_list|(
name|GimpProjection
modifier|*
name|proj
parameter_list|,
name|gint
name|x
parameter_list|,
name|gint
name|y
parameter_list|,
name|gint
name|w
parameter_list|,
name|gint
name|h
parameter_list|)
block|{
name|g_return_if_fail
argument_list|(
name|GIMP_IS_PROJECTION
argument_list|(
name|proj
argument_list|)
argument_list|)
expr_stmt|;
if|#
directive|if
literal|0
block|GimpImage *image = gimp_projectable_get_image (proj->projectable);    if (gimp_container_num_children (image->layers) == 1)
comment|/* a single layer */
block|{       GimpDrawable *layer;       gint          off_x, off_y;        layer = GIMP_DRAWABLE (gimp_image_get_layer_by_index (image, 0));        gimp_item_get_offset (GIMP_ITEM (layer),&off_x,&off_y);        if (gimp_drawable_has_alpha (layer)&&           gimp_item_get_visible (GIMP_ITEM (layer))&&           gimp_item_get_width  (GIMP_ITEM (layer)) == image->width&&           gimp_item_get_height (GIMP_ITEM (layer)) == image->height&&           ! gimp_drawable_is_indexed (layer)&&           gimp_layer_get_opacity (GIMP_LAYER (layer)) == GIMP_OPACITY_OPAQUE&&           off_x == 0&&           off_y == 0)         {           PixelRegion srcPR, destPR;            g_printerr ("cow-projection!");            pixel_region_init (&srcPR,                              gimp_drawable_get_tiles (layer),                              x, y, w,h, FALSE);           pixel_region_init (&destPR,                              gimp_pickable_get_tiles (GIMP_PICKABLE (proj)),                              x, y, w,h, TRUE);            copy_region (&srcPR,&destPR);            proj->construct_flag = TRUE;            gimp_projection_construct_channels (proj, x, y, w, h);            return;         }     }
endif|#
directive|endif
comment|/*  First, determine if the projection image needs to be    *  initialized--this is the case when there are no visible    *  layers that cover the entire canvas--either because layers    *  are offset or only a floating selection is visible    */
name|gimp_projection_initialize
argument_list|(
name|proj
argument_list|,
name|x
argument_list|,
name|y
argument_list|,
name|w
argument_list|,
name|h
argument_list|)
expr_stmt|;
comment|/*  call functions which process the list of layers and    *  the list of channels    */
if|if
condition|(
name|proj
operator|->
name|use_gegl
condition|)
block|{
name|gimp_projection_construct_gegl
argument_list|(
name|proj
argument_list|,
name|x
argument_list|,
name|y
argument_list|,
name|w
argument_list|,
name|h
argument_list|)
expr_stmt|;
block|}
else|else
block|{
name|proj
operator|->
name|construct_flag
operator|=
name|FALSE
expr_stmt|;
name|gimp_projection_construct_layers
argument_list|(
name|proj
argument_list|,
name|x
argument_list|,
name|y
argument_list|,
name|w
argument_list|,
name|h
argument_list|)
expr_stmt|;
name|gimp_projection_construct_channels
argument_list|(
name|proj
argument_list|,
name|x
argument_list|,
name|y
argument_list|,
name|w
argument_list|,
name|h
argument_list|)
expr_stmt|;
block|}
block|}
end_function

begin_comment
comment|/*  private functions  */
end_comment

begin_function
specifier|static
name|void
DECL|function|gimp_projection_construct_gegl (GimpProjection * proj,gint x,gint y,gint w,gint h)
name|gimp_projection_construct_gegl
parameter_list|(
name|GimpProjection
modifier|*
name|proj
parameter_list|,
name|gint
name|x
parameter_list|,
name|gint
name|y
parameter_list|,
name|gint
name|w
parameter_list|,
name|gint
name|h
parameter_list|)
block|{
name|GeglNode
modifier|*
name|sink
decl_stmt|;
name|GeglProcessor
modifier|*
name|processor
decl_stmt|;
name|GeglRectangle
name|rect
decl_stmt|;
name|sink
operator|=
name|gimp_projection_get_sink_node
argument_list|(
name|proj
argument_list|)
expr_stmt|;
name|rect
operator|.
name|x
operator|=
name|x
expr_stmt|;
name|rect
operator|.
name|y
operator|=
name|y
expr_stmt|;
name|rect
operator|.
name|width
operator|=
name|w
expr_stmt|;
name|rect
operator|.
name|height
operator|=
name|h
expr_stmt|;
name|processor
operator|=
name|gegl_node_new_processor
argument_list|(
name|sink
argument_list|,
operator|&
name|rect
argument_list|)
expr_stmt|;
while|while
condition|(
name|gegl_processor_work
argument_list|(
name|processor
argument_list|,
name|NULL
argument_list|)
condition|)
empty_stmt|;
name|g_object_unref
argument_list|(
name|processor
argument_list|)
expr_stmt|;
block|}
end_function

begin_function
specifier|static
name|void
DECL|function|gimp_projection_construct_layers (GimpProjection * proj,gint x,gint y,gint w,gint h)
name|gimp_projection_construct_layers
parameter_list|(
name|GimpProjection
modifier|*
name|proj
parameter_list|,
name|gint
name|x
parameter_list|,
name|gint
name|y
parameter_list|,
name|gint
name|w
parameter_list|,
name|gint
name|h
parameter_list|)
block|{
name|GimpImage
modifier|*
name|image
init|=
name|gimp_projectable_get_image
argument_list|(
name|proj
operator|->
name|projectable
argument_list|)
decl_stmt|;
name|GimpLayer
modifier|*
name|layer
decl_stmt|;
name|GList
modifier|*
name|list
decl_stmt|;
name|GList
modifier|*
name|reverse_list
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
name|off_x
decl_stmt|;
name|gint
name|off_y
decl_stmt|;
comment|/*  composite the floating selection if it exists  */
if|if
condition|(
operator|(
name|layer
operator|=
name|gimp_image_floating_sel
argument_list|(
name|image
argument_list|)
operator|)
condition|)
name|floating_sel_composite
argument_list|(
name|layer
argument_list|,
name|x
argument_list|,
name|y
argument_list|,
name|w
argument_list|,
name|h
argument_list|,
name|FALSE
argument_list|)
expr_stmt|;
name|reverse_list
operator|=
name|NULL
expr_stmt|;
for|for
control|(
name|list
operator|=
name|gimp_image_get_layer_iter
argument_list|(
name|image
argument_list|)
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
name|layer
operator|=
name|list
operator|->
name|data
expr_stmt|;
comment|/*  only add layers that are visible and not floating selections        *  to the list        */
if|if
condition|(
operator|!
name|gimp_layer_is_floating_sel
argument_list|(
name|layer
argument_list|)
operator|&&
name|gimp_item_get_visible
argument_list|(
name|GIMP_ITEM
argument_list|(
name|layer
argument_list|)
argument_list|)
condition|)
block|{
name|reverse_list
operator|=
name|g_list_prepend
argument_list|(
name|reverse_list
argument_list|,
name|layer
argument_list|)
expr_stmt|;
block|}
block|}
for|for
control|(
name|list
operator|=
name|reverse_list
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
name|GimpLayerMask
modifier|*
name|mask
decl_stmt|;
name|PixelRegion
name|src1PR
decl_stmt|;
name|PixelRegion
name|src2PR
decl_stmt|;
name|PixelRegion
name|maskPR
decl_stmt|;
name|layer
operator|=
name|list
operator|->
name|data
expr_stmt|;
name|mask
operator|=
name|gimp_layer_get_mask
argument_list|(
name|layer
argument_list|)
expr_stmt|;
name|gimp_item_get_offset
argument_list|(
name|GIMP_ITEM
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
name|x
argument_list|,
name|x
operator|+
name|w
argument_list|)
expr_stmt|;
name|y1
operator|=
name|CLAMP
argument_list|(
name|off_y
argument_list|,
name|y
argument_list|,
name|y
operator|+
name|h
argument_list|)
expr_stmt|;
name|x2
operator|=
name|CLAMP
argument_list|(
name|off_x
operator|+
name|gimp_item_get_width
argument_list|(
name|GIMP_ITEM
argument_list|(
name|layer
argument_list|)
argument_list|)
argument_list|,
name|x
argument_list|,
name|x
operator|+
name|w
argument_list|)
expr_stmt|;
name|y2
operator|=
name|CLAMP
argument_list|(
name|off_y
operator|+
name|gimp_item_get_height
argument_list|(
name|GIMP_ITEM
argument_list|(
name|layer
argument_list|)
argument_list|)
argument_list|,
name|y
argument_list|,
name|y
operator|+
name|h
argument_list|)
expr_stmt|;
comment|/* configure the pixel regions  */
name|pixel_region_init
argument_list|(
operator|&
name|src1PR
argument_list|,
name|gimp_pickable_get_tiles
argument_list|(
name|GIMP_PICKABLE
argument_list|(
name|proj
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
comment|/*  If we're showing the layer mask instead of the layer...  */
if|if
condition|(
name|mask
operator|&&
name|gimp_layer_mask_get_show
argument_list|(
name|mask
argument_list|)
condition|)
block|{
name|pixel_region_init
argument_list|(
operator|&
name|src2PR
argument_list|,
name|gimp_drawable_get_tiles
argument_list|(
name|GIMP_DRAWABLE
argument_list|(
name|mask
argument_list|)
argument_list|)
argument_list|,
name|x1
operator|-
name|off_x
argument_list|,
name|y1
operator|-
name|off_y
argument_list|,
name|x2
operator|-
name|x1
argument_list|,
name|y2
operator|-
name|y1
argument_list|,
name|FALSE
argument_list|)
expr_stmt|;
name|copy_gray_to_region
argument_list|(
operator|&
name|src2PR
argument_list|,
operator|&
name|src1PR
argument_list|)
expr_stmt|;
block|}
comment|/*  Otherwise, normal  */
else|else
block|{
name|PixelRegion
modifier|*
name|mask_pr
init|=
name|NULL
decl_stmt|;
name|pixel_region_init
argument_list|(
operator|&
name|src2PR
argument_list|,
name|gimp_drawable_get_tiles
argument_list|(
name|GIMP_DRAWABLE
argument_list|(
name|layer
argument_list|)
argument_list|)
argument_list|,
name|x1
operator|-
name|off_x
argument_list|,
name|y1
operator|-
name|off_y
argument_list|,
name|x2
operator|-
name|x1
argument_list|,
name|y2
operator|-
name|y1
argument_list|,
name|FALSE
argument_list|)
expr_stmt|;
if|if
condition|(
name|mask
operator|&&
name|gimp_layer_mask_get_apply
argument_list|(
name|mask
argument_list|)
condition|)
block|{
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
name|x1
operator|-
name|off_x
argument_list|,
name|y1
operator|-
name|off_y
argument_list|,
name|x2
operator|-
name|x1
argument_list|,
name|y2
operator|-
name|y1
argument_list|,
name|FALSE
argument_list|)
expr_stmt|;
name|mask_pr
operator|=
operator|&
name|maskPR
expr_stmt|;
block|}
comment|/*  Based on the type of the layer, project the layer onto the            *  projection image...            */
switch|switch
condition|(
name|gimp_drawable_type
argument_list|(
name|GIMP_DRAWABLE
argument_list|(
name|layer
argument_list|)
argument_list|)
condition|)
block|{
case|case
name|GIMP_RGB_IMAGE
case|:
case|case
name|GIMP_GRAY_IMAGE
case|:
name|project_intensity
argument_list|(
name|proj
argument_list|,
name|layer
argument_list|,
operator|&
name|src2PR
argument_list|,
operator|&
name|src1PR
argument_list|,
name|mask_pr
argument_list|)
expr_stmt|;
break|break;
case|case
name|GIMP_RGBA_IMAGE
case|:
case|case
name|GIMP_GRAYA_IMAGE
case|:
name|project_intensity_alpha
argument_list|(
name|proj
argument_list|,
name|layer
argument_list|,
operator|&
name|src2PR
argument_list|,
operator|&
name|src1PR
argument_list|,
name|mask_pr
argument_list|)
expr_stmt|;
break|break;
case|case
name|GIMP_INDEXED_IMAGE
case|:
name|project_indexed
argument_list|(
name|proj
argument_list|,
name|layer
argument_list|,
operator|&
name|src2PR
argument_list|,
operator|&
name|src1PR
argument_list|,
name|mask_pr
argument_list|)
expr_stmt|;
break|break;
case|case
name|GIMP_INDEXEDA_IMAGE
case|:
name|project_indexed_alpha
argument_list|(
name|proj
argument_list|,
name|layer
argument_list|,
operator|&
name|src2PR
argument_list|,
operator|&
name|src1PR
argument_list|,
name|mask_pr
argument_list|)
expr_stmt|;
break|break;
default|default:
break|break;
block|}
block|}
name|proj
operator|->
name|construct_flag
operator|=
name|TRUE
expr_stmt|;
comment|/*  something was projected  */
block|}
name|g_list_free
argument_list|(
name|reverse_list
argument_list|)
expr_stmt|;
block|}
end_function

begin_function
specifier|static
name|void
DECL|function|gimp_projection_construct_channels (GimpProjection * proj,gint x,gint y,gint w,gint h)
name|gimp_projection_construct_channels
parameter_list|(
name|GimpProjection
modifier|*
name|proj
parameter_list|,
name|gint
name|x
parameter_list|,
name|gint
name|y
parameter_list|,
name|gint
name|w
parameter_list|,
name|gint
name|h
parameter_list|)
block|{
name|GimpImage
modifier|*
name|image
init|=
name|gimp_projectable_get_image
argument_list|(
name|proj
operator|->
name|projectable
argument_list|)
decl_stmt|;
name|GList
modifier|*
name|list
decl_stmt|;
name|GList
modifier|*
name|reverse_list
init|=
name|NULL
decl_stmt|;
comment|/*  reverse the channel list  */
for|for
control|(
name|list
operator|=
name|gimp_image_get_channel_iter
argument_list|(
name|image
argument_list|)
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
name|reverse_list
operator|=
name|g_list_prepend
argument_list|(
name|reverse_list
argument_list|,
name|list
operator|->
name|data
argument_list|)
expr_stmt|;
block|}
for|for
control|(
name|list
operator|=
name|reverse_list
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
name|GimpChannel
modifier|*
name|channel
init|=
name|list
operator|->
name|data
decl_stmt|;
if|if
condition|(
name|gimp_item_get_visible
argument_list|(
name|GIMP_ITEM
argument_list|(
name|channel
argument_list|)
argument_list|)
condition|)
block|{
name|PixelRegion
name|src1PR
decl_stmt|;
name|PixelRegion
name|src2PR
decl_stmt|;
comment|/* configure the pixel regions  */
name|pixel_region_init
argument_list|(
operator|&
name|src1PR
argument_list|,
name|gimp_pickable_get_tiles
argument_list|(
name|GIMP_PICKABLE
argument_list|(
name|proj
argument_list|)
argument_list|)
argument_list|,
name|x
argument_list|,
name|y
argument_list|,
name|w
argument_list|,
name|h
argument_list|,
name|TRUE
argument_list|)
expr_stmt|;
name|pixel_region_init
argument_list|(
operator|&
name|src2PR
argument_list|,
name|gimp_drawable_get_tiles
argument_list|(
name|GIMP_DRAWABLE
argument_list|(
name|channel
argument_list|)
argument_list|)
argument_list|,
name|x
argument_list|,
name|y
argument_list|,
name|w
argument_list|,
name|h
argument_list|,
name|FALSE
argument_list|)
expr_stmt|;
name|project_channel
argument_list|(
name|proj
argument_list|,
name|channel
argument_list|,
operator|&
name|src1PR
argument_list|,
operator|&
name|src2PR
argument_list|)
expr_stmt|;
name|proj
operator|->
name|construct_flag
operator|=
name|TRUE
expr_stmt|;
block|}
block|}
name|g_list_free
argument_list|(
name|reverse_list
argument_list|)
expr_stmt|;
block|}
end_function

begin_comment
comment|/**  * gimp_projection_initialize:  * @proj: A #GimpProjection.  * @x:  * @y:  * @w:  * @h:  *  * This function determines whether a visible layer with combine mode  * Normal provides complete coverage over the specified area.  If not,  * the projection is initialized to transparent black.  */
end_comment

begin_function
specifier|static
name|void
DECL|function|gimp_projection_initialize (GimpProjection * proj,gint x,gint y,gint w,gint h)
name|gimp_projection_initialize
parameter_list|(
name|GimpProjection
modifier|*
name|proj
parameter_list|,
name|gint
name|x
parameter_list|,
name|gint
name|y
parameter_list|,
name|gint
name|w
parameter_list|,
name|gint
name|h
parameter_list|)
block|{
name|GimpImage
modifier|*
name|image
init|=
name|gimp_projectable_get_image
argument_list|(
name|proj
operator|->
name|projectable
argument_list|)
decl_stmt|;
name|GList
modifier|*
name|list
decl_stmt|;
name|gboolean
name|coverage
init|=
name|FALSE
decl_stmt|;
for|for
control|(
name|list
operator|=
name|gimp_image_get_layer_iter
argument_list|(
name|image
argument_list|)
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
name|GimpItem
modifier|*
name|item
init|=
name|list
operator|->
name|data
decl_stmt|;
name|gint
name|off_x
decl_stmt|,
name|off_y
decl_stmt|;
name|gimp_item_get_offset
argument_list|(
name|item
argument_list|,
operator|&
name|off_x
argument_list|,
operator|&
name|off_y
argument_list|)
expr_stmt|;
if|if
condition|(
name|gimp_item_get_visible
argument_list|(
name|item
argument_list|)
operator|&&
operator|!
name|gimp_drawable_has_alpha
argument_list|(
name|GIMP_DRAWABLE
argument_list|(
name|item
argument_list|)
argument_list|)
operator|&&
operator|!
name|gimp_layer_get_mask
argument_list|(
name|GIMP_LAYER
argument_list|(
name|item
argument_list|)
argument_list|)
operator|&&
name|gimp_layer_get_mode
argument_list|(
name|GIMP_LAYER
argument_list|(
name|item
argument_list|)
argument_list|)
operator|==
name|GIMP_NORMAL_MODE
operator|&&
name|gimp_layer_get_opacity
argument_list|(
name|GIMP_LAYER
argument_list|(
name|item
argument_list|)
argument_list|)
operator|==
name|GIMP_OPACITY_OPAQUE
operator|&&
operator|(
name|off_x
operator|<=
name|x
operator|)
operator|&&
operator|(
name|off_y
operator|<=
name|y
operator|)
operator|&&
operator|(
name|off_x
operator|+
name|gimp_item_get_width
argument_list|(
name|item
argument_list|)
operator|>=
name|x
operator|+
name|w
operator|)
operator|&&
operator|(
name|off_y
operator|+
name|gimp_item_get_height
argument_list|(
name|item
argument_list|)
operator|>=
name|y
operator|+
name|h
operator|)
condition|)
block|{
name|coverage
operator|=
name|TRUE
expr_stmt|;
break|break;
block|}
block|}
if|if
condition|(
operator|!
name|coverage
condition|)
block|{
name|PixelRegion
name|region
decl_stmt|;
name|pixel_region_init
argument_list|(
operator|&
name|region
argument_list|,
name|gimp_pickable_get_tiles
argument_list|(
name|GIMP_PICKABLE
argument_list|(
name|proj
argument_list|)
argument_list|)
argument_list|,
name|x
argument_list|,
name|y
argument_list|,
name|w
argument_list|,
name|h
argument_list|,
name|TRUE
argument_list|)
expr_stmt|;
name|clear_region
argument_list|(
operator|&
name|region
argument_list|)
expr_stmt|;
block|}
block|}
end_function

begin_function
specifier|static
name|void
DECL|function|project_intensity (GimpProjection * proj,GimpLayer * layer,PixelRegion * src,PixelRegion * dest,PixelRegion * mask)
name|project_intensity
parameter_list|(
name|GimpProjection
modifier|*
name|proj
parameter_list|,
name|GimpLayer
modifier|*
name|layer
parameter_list|,
name|PixelRegion
modifier|*
name|src
parameter_list|,
name|PixelRegion
modifier|*
name|dest
parameter_list|,
name|PixelRegion
modifier|*
name|mask
parameter_list|)
block|{
name|GimpImage
modifier|*
name|image
init|=
name|gimp_projectable_get_image
argument_list|(
name|proj
operator|->
name|projectable
argument_list|)
decl_stmt|;
if|if
condition|(
name|proj
operator|->
name|construct_flag
condition|)
block|{
name|combine_regions
argument_list|(
name|dest
argument_list|,
name|src
argument_list|,
name|dest
argument_list|,
name|mask
argument_list|,
name|NULL
argument_list|,
name|gimp_layer_get_opacity
argument_list|(
name|layer
argument_list|)
operator|*
literal|255.999
argument_list|,
name|gimp_layer_get_mode
argument_list|(
name|layer
argument_list|)
argument_list|,
name|image
operator|->
name|visible
argument_list|,
name|COMBINE_INTEN_A_INTEN
argument_list|)
expr_stmt|;
block|}
else|else
block|{
name|initial_region
argument_list|(
name|src
argument_list|,
name|dest
argument_list|,
name|mask
argument_list|,
name|NULL
argument_list|,
name|gimp_layer_get_opacity
argument_list|(
name|layer
argument_list|)
operator|*
literal|255.999
argument_list|,
name|gimp_layer_get_mode
argument_list|(
name|layer
argument_list|)
argument_list|,
name|image
operator|->
name|visible
argument_list|,
name|INITIAL_INTENSITY
argument_list|)
expr_stmt|;
block|}
block|}
end_function

begin_function
specifier|static
name|void
DECL|function|project_intensity_alpha (GimpProjection * proj,GimpLayer * layer,PixelRegion * src,PixelRegion * dest,PixelRegion * mask)
name|project_intensity_alpha
parameter_list|(
name|GimpProjection
modifier|*
name|proj
parameter_list|,
name|GimpLayer
modifier|*
name|layer
parameter_list|,
name|PixelRegion
modifier|*
name|src
parameter_list|,
name|PixelRegion
modifier|*
name|dest
parameter_list|,
name|PixelRegion
modifier|*
name|mask
parameter_list|)
block|{
name|GimpImage
modifier|*
name|image
init|=
name|gimp_projectable_get_image
argument_list|(
name|proj
operator|->
name|projectable
argument_list|)
decl_stmt|;
if|if
condition|(
name|proj
operator|->
name|construct_flag
condition|)
block|{
name|combine_regions
argument_list|(
name|dest
argument_list|,
name|src
argument_list|,
name|dest
argument_list|,
name|mask
argument_list|,
name|NULL
argument_list|,
name|gimp_layer_get_opacity
argument_list|(
name|layer
argument_list|)
operator|*
literal|255.999
argument_list|,
name|gimp_layer_get_mode
argument_list|(
name|layer
argument_list|)
argument_list|,
name|image
operator|->
name|visible
argument_list|,
name|COMBINE_INTEN_A_INTEN_A
argument_list|)
expr_stmt|;
block|}
else|else
block|{
name|initial_region
argument_list|(
name|src
argument_list|,
name|dest
argument_list|,
name|mask
argument_list|,
name|NULL
argument_list|,
name|gimp_layer_get_opacity
argument_list|(
name|layer
argument_list|)
operator|*
literal|255.999
argument_list|,
name|gimp_layer_get_mode
argument_list|(
name|layer
argument_list|)
argument_list|,
name|image
operator|->
name|visible
argument_list|,
name|INITIAL_INTENSITY_ALPHA
argument_list|)
expr_stmt|;
block|}
block|}
end_function

begin_function
specifier|static
name|void
DECL|function|project_indexed (GimpProjection * proj,GimpLayer * layer,PixelRegion * src,PixelRegion * dest,PixelRegion * mask)
name|project_indexed
parameter_list|(
name|GimpProjection
modifier|*
name|proj
parameter_list|,
name|GimpLayer
modifier|*
name|layer
parameter_list|,
name|PixelRegion
modifier|*
name|src
parameter_list|,
name|PixelRegion
modifier|*
name|dest
parameter_list|,
name|PixelRegion
modifier|*
name|mask
parameter_list|)
block|{
name|GimpImage
modifier|*
name|image
init|=
name|gimp_projectable_get_image
argument_list|(
name|proj
operator|->
name|projectable
argument_list|)
decl_stmt|;
specifier|const
name|guchar
modifier|*
name|colormap
init|=
name|gimp_image_get_colormap
argument_list|(
name|image
argument_list|)
decl_stmt|;
name|g_return_if_fail
argument_list|(
name|colormap
operator|!=
name|NULL
argument_list|)
expr_stmt|;
if|if
condition|(
name|proj
operator|->
name|construct_flag
condition|)
block|{
name|combine_regions
argument_list|(
name|dest
argument_list|,
name|src
argument_list|,
name|dest
argument_list|,
name|mask
argument_list|,
name|colormap
argument_list|,
name|gimp_layer_get_opacity
argument_list|(
name|layer
argument_list|)
operator|*
literal|255.999
argument_list|,
name|gimp_layer_get_mode
argument_list|(
name|layer
argument_list|)
argument_list|,
name|image
operator|->
name|visible
argument_list|,
name|COMBINE_INTEN_A_INDEXED
argument_list|)
expr_stmt|;
block|}
else|else
block|{
name|initial_region
argument_list|(
name|src
argument_list|,
name|dest
argument_list|,
name|mask
argument_list|,
name|colormap
argument_list|,
name|gimp_layer_get_opacity
argument_list|(
name|layer
argument_list|)
operator|*
literal|255.999
argument_list|,
name|gimp_layer_get_mode
argument_list|(
name|layer
argument_list|)
argument_list|,
name|image
operator|->
name|visible
argument_list|,
name|INITIAL_INDEXED
argument_list|)
expr_stmt|;
block|}
block|}
end_function

begin_function
specifier|static
name|void
DECL|function|project_indexed_alpha (GimpProjection * proj,GimpLayer * layer,PixelRegion * src,PixelRegion * dest,PixelRegion * mask)
name|project_indexed_alpha
parameter_list|(
name|GimpProjection
modifier|*
name|proj
parameter_list|,
name|GimpLayer
modifier|*
name|layer
parameter_list|,
name|PixelRegion
modifier|*
name|src
parameter_list|,
name|PixelRegion
modifier|*
name|dest
parameter_list|,
name|PixelRegion
modifier|*
name|mask
parameter_list|)
block|{
name|GimpImage
modifier|*
name|image
init|=
name|gimp_projectable_get_image
argument_list|(
name|proj
operator|->
name|projectable
argument_list|)
decl_stmt|;
specifier|const
name|guchar
modifier|*
name|colormap
init|=
name|gimp_image_get_colormap
argument_list|(
name|image
argument_list|)
decl_stmt|;
name|g_return_if_fail
argument_list|(
name|colormap
operator|!=
name|NULL
argument_list|)
expr_stmt|;
if|if
condition|(
name|proj
operator|->
name|construct_flag
condition|)
block|{
name|combine_regions
argument_list|(
name|dest
argument_list|,
name|src
argument_list|,
name|dest
argument_list|,
name|mask
argument_list|,
name|colormap
argument_list|,
name|gimp_layer_get_opacity
argument_list|(
name|layer
argument_list|)
operator|*
literal|255.999
argument_list|,
name|gimp_layer_get_mode
argument_list|(
name|layer
argument_list|)
argument_list|,
name|image
operator|->
name|visible
argument_list|,
name|COMBINE_INTEN_A_INDEXED_A
argument_list|)
expr_stmt|;
block|}
else|else
block|{
name|initial_region
argument_list|(
name|src
argument_list|,
name|dest
argument_list|,
name|mask
argument_list|,
name|colormap
argument_list|,
name|gimp_layer_get_opacity
argument_list|(
name|layer
argument_list|)
operator|*
literal|255.999
argument_list|,
name|gimp_layer_get_mode
argument_list|(
name|layer
argument_list|)
argument_list|,
name|image
operator|->
name|visible
argument_list|,
name|INITIAL_INDEXED_ALPHA
argument_list|)
expr_stmt|;
block|}
block|}
end_function

begin_function
specifier|static
name|void
DECL|function|project_channel (GimpProjection * proj,GimpChannel * channel,PixelRegion * src,PixelRegion * src2)
name|project_channel
parameter_list|(
name|GimpProjection
modifier|*
name|proj
parameter_list|,
name|GimpChannel
modifier|*
name|channel
parameter_list|,
name|PixelRegion
modifier|*
name|src
parameter_list|,
name|PixelRegion
modifier|*
name|src2
parameter_list|)
block|{
name|guchar
name|col
index|[
literal|3
index|]
decl_stmt|;
name|guchar
name|opacity
decl_stmt|;
name|gimp_rgba_get_uchar
argument_list|(
operator|&
name|channel
operator|->
name|color
argument_list|,
operator|&
name|col
index|[
literal|0
index|]
argument_list|,
operator|&
name|col
index|[
literal|1
index|]
argument_list|,
operator|&
name|col
index|[
literal|2
index|]
argument_list|,
operator|&
name|opacity
argument_list|)
expr_stmt|;
if|if
condition|(
name|proj
operator|->
name|construct_flag
condition|)
block|{
name|combine_regions
argument_list|(
name|src
argument_list|,
name|src2
argument_list|,
name|src
argument_list|,
name|NULL
argument_list|,
name|col
argument_list|,
name|opacity
argument_list|,
name|GIMP_NORMAL_MODE
argument_list|,
name|NULL
argument_list|,
operator|(
name|gimp_channel_get_show_masked
argument_list|(
name|channel
argument_list|)
condition|?
name|COMBINE_INTEN_A_CHANNEL_MASK
else|:
name|COMBINE_INTEN_A_CHANNEL_SELECTION
operator|)
argument_list|)
expr_stmt|;
block|}
else|else
block|{
name|initial_region
argument_list|(
name|src2
argument_list|,
name|src
argument_list|,
name|NULL
argument_list|,
name|col
argument_list|,
name|opacity
argument_list|,
name|GIMP_NORMAL_MODE
argument_list|,
name|NULL
argument_list|,
operator|(
name|gimp_channel_get_show_masked
argument_list|(
name|channel
argument_list|)
condition|?
name|INITIAL_CHANNEL_MASK
else|:
name|INITIAL_CHANNEL_SELECTION
operator|)
argument_list|)
expr_stmt|;
block|}
block|}
end_function

end_unit

