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
file|"gegl/gimp-gegl-utils.h"
end_include

begin_include
include|#
directive|include
file|"gimplayer.h"
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
name|gimp_projection_construct_legacy
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
name|gimp_projection_construct_legacy
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
name|GeglRectangle
name|rect
init|=
block|{
name|x
block|,
name|y
block|,
name|w
block|,
name|h
block|}
decl_stmt|;
if|if
condition|(
operator|!
name|proj
operator|->
name|processor
condition|)
block|{
name|GeglNode
modifier|*
name|sink
init|=
name|gimp_projection_get_sink_node
argument_list|(
name|proj
argument_list|)
decl_stmt|;
name|proj
operator|->
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
block|}
else|else
block|{
name|gegl_processor_set_rectangle
argument_list|(
name|proj
operator|->
name|processor
argument_list|,
operator|&
name|rect
argument_list|)
expr_stmt|;
block|}
while|while
condition|(
name|gegl_processor_work
argument_list|(
name|proj
operator|->
name|processor
argument_list|,
name|NULL
argument_list|)
condition|)
empty_stmt|;
block|}
end_function

begin_function
specifier|static
name|void
DECL|function|gimp_projection_construct_legacy (GimpProjection * proj,gint x,gint y,gint w,gint h)
name|gimp_projection_construct_legacy
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
name|gint
name|proj_off_x
decl_stmt|;
name|gint
name|proj_off_y
decl_stmt|;
for|for
control|(
name|list
operator|=
name|gimp_projectable_get_channels
argument_list|(
name|proj
operator|->
name|projectable
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
if|if
condition|(
name|gimp_item_get_visible
argument_list|(
name|GIMP_ITEM
argument_list|(
name|list
operator|->
name|data
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
name|list
operator|->
name|data
argument_list|)
expr_stmt|;
block|}
block|}
for|for
control|(
name|list
operator|=
name|gimp_projectable_get_layers
argument_list|(
name|proj
operator|->
name|projectable
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
name|GimpLayer
modifier|*
name|layer
init|=
name|list
operator|->
name|data
decl_stmt|;
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
comment|/*  only add layers that are visible and not floating selections            *  to the list            */
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
name|gimp_projectable_get_offset
argument_list|(
name|proj
operator|->
name|projectable
argument_list|,
operator|&
name|proj_off_x
argument_list|,
operator|&
name|proj_off_y
argument_list|)
expr_stmt|;
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
name|GimpItem
modifier|*
name|item
init|=
name|list
operator|->
name|data
decl_stmt|;
name|PixelRegion
name|projPR
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
decl_stmt|;
name|gint
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
comment|/*  subtract the projectable's offsets because the list of        *  update areas is in tile-pyramid coordinates, but our        *  external API is always in terms of image coordinates.        */
name|off_x
operator|-=
name|proj_off_x
expr_stmt|;
name|off_y
operator|-=
name|proj_off_y
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
name|item
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
name|item
argument_list|)
argument_list|,
name|y
argument_list|,
name|y
operator|+
name|h
argument_list|)
expr_stmt|;
name|pixel_region_init
argument_list|(
operator|&
name|projPR
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
name|x2
operator|-
name|x1
argument_list|,
name|y2
operator|-
name|y1
argument_list|,
name|TRUE
argument_list|)
expr_stmt|;
name|gimp_drawable_project_region
argument_list|(
name|GIMP_DRAWABLE
argument_list|(
name|item
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
operator|&
name|projPR
argument_list|,
name|proj
operator|->
name|construct_flag
argument_list|)
expr_stmt|;
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
name|GList
modifier|*
name|list
decl_stmt|;
name|gint
name|proj_off_x
decl_stmt|;
name|gint
name|proj_off_y
decl_stmt|;
name|gboolean
name|coverage
init|=
name|FALSE
decl_stmt|;
name|gimp_projectable_get_offset
argument_list|(
name|proj
operator|->
name|projectable
argument_list|,
operator|&
name|proj_off_x
argument_list|,
operator|&
name|proj_off_y
argument_list|)
expr_stmt|;
for|for
control|(
name|list
operator|=
name|gimp_projectable_get_layers
argument_list|(
name|proj
operator|->
name|projectable
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
name|GimpLayer
modifier|*
name|layer
init|=
name|list
operator|->
name|data
decl_stmt|;
name|GimpDrawable
modifier|*
name|drawable
init|=
name|GIMP_DRAWABLE
argument_list|(
name|layer
argument_list|)
decl_stmt|;
name|GimpItem
modifier|*
name|item
init|=
name|GIMP_ITEM
argument_list|(
name|layer
argument_list|)
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
comment|/*  subtract the projectable's offsets because the list of        *  update areas is in tile-pyramid coordinates, but our        *  external API is always in terms of image coordinates.        */
name|off_x
operator|-=
name|proj_off_x
expr_stmt|;
name|off_y
operator|-=
name|proj_off_y
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
name|drawable
argument_list|)
operator|&&
operator|!
name|gimp_layer_get_mask
argument_list|(
name|layer
argument_list|)
operator|&&
name|gimp_layer_get_mode
argument_list|(
name|layer
argument_list|)
operator|==
name|GIMP_NORMAL_MODE
operator|&&
name|gimp_layer_get_opacity
argument_list|(
name|layer
argument_list|)
operator|==
name|GIMP_OPACITY_OPAQUE
operator|&&
name|off_x
operator|<=
name|x
operator|&&
name|off_y
operator|<=
name|y
operator|&&
operator|(
name|off_x
operator|+
name|gimp_item_get_width
argument_list|(
name|item
argument_list|)
operator|)
operator|>=
operator|(
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
operator|)
operator|>=
operator|(
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
name|GeglBuffer
modifier|*
name|buffer
decl_stmt|;
name|GeglRectangle
name|rect
init|=
block|{
name|x
block|,
name|y
block|,
name|w
block|,
name|h
block|}
decl_stmt|;
if|if
condition|(
name|proj
operator|->
name|use_gegl
condition|)
block|{
comment|/* GEGL should really do this for us... */
name|gegl_node_get
argument_list|(
name|gimp_projection_get_sink_node
argument_list|(
name|proj
argument_list|)
argument_list|,
literal|"buffer"
argument_list|,
operator|&
name|buffer
argument_list|,
name|NULL
argument_list|)
expr_stmt|;
block|}
else|else
block|{
name|TileManager
modifier|*
name|tiles
init|=
name|gimp_pickable_get_tiles
argument_list|(
name|GIMP_PICKABLE
argument_list|(
name|proj
argument_list|)
argument_list|)
decl_stmt|;
name|buffer
operator|=
name|gimp_tile_manager_create_buffer
argument_list|(
name|tiles
argument_list|,
name|NULL
argument_list|)
expr_stmt|;
block|}
name|gegl_buffer_clear
argument_list|(
name|buffer
argument_list|,
operator|&
name|rect
argument_list|)
expr_stmt|;
name|g_object_unref
argument_list|(
name|buffer
argument_list|)
expr_stmt|;
block|}
block|}
end_function

end_unit

