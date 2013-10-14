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
file|<gdk-pixbuf/gdk-pixbuf.h>
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
file|"gegl/gimpapplicator.h"
end_include

begin_include
include|#
directive|include
file|"gegl/gimp-babl-compat.h"
end_include

begin_include
include|#
directive|include
file|"gegl/gimp-gegl-apply-operation.h"
end_include

begin_include
include|#
directive|include
file|"gegl/gimp-gegl-loops.h"
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
DECL|function|gimp_drawable_real_apply_buffer (GimpDrawable * drawable,GeglBuffer * buffer,const GeglRectangle * buffer_region,gboolean push_undo,const gchar * undo_desc,gdouble opacity,GimpLayerModeEffects mode,GeglBuffer * base_buffer,gint base_x,gint base_y)
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
name|GimpApplicator
modifier|*
name|applicator
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
name|gegl_buffer_new
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
name|applicator
operator|=
name|gimp_applicator_new
argument_list|(
name|NULL
argument_list|,
name|gimp_drawable_get_linear
argument_list|(
name|drawable
argument_list|)
argument_list|)
expr_stmt|;
if|if
condition|(
name|mask
condition|)
block|{
name|GeglBuffer
modifier|*
name|mask_buffer
decl_stmt|;
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
name|gimp_applicator_set_mask_buffer
argument_list|(
name|applicator
argument_list|,
name|mask_buffer
argument_list|)
expr_stmt|;
name|gimp_applicator_set_mask_offset
argument_list|(
name|applicator
argument_list|,
operator|-
name|offset_x
argument_list|,
operator|-
name|offset_y
argument_list|)
expr_stmt|;
block|}
name|gimp_applicator_set_src_buffer
argument_list|(
name|applicator
argument_list|,
name|base_buffer
argument_list|)
expr_stmt|;
name|gimp_applicator_set_dest_buffer
argument_list|(
name|applicator
argument_list|,
name|gimp_drawable_get_buffer
argument_list|(
name|drawable
argument_list|)
argument_list|)
expr_stmt|;
name|gimp_applicator_set_apply_buffer
argument_list|(
name|applicator
argument_list|,
name|buffer
argument_list|)
expr_stmt|;
name|gimp_applicator_set_apply_offset
argument_list|(
name|applicator
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
argument_list|)
expr_stmt|;
name|gimp_applicator_set_mode
argument_list|(
name|applicator
argument_list|,
name|opacity
argument_list|,
name|mode
argument_list|)
expr_stmt|;
name|gimp_applicator_set_affect
argument_list|(
name|applicator
argument_list|,
name|gimp_drawable_get_active_mask
argument_list|(
name|drawable
argument_list|)
argument_list|)
expr_stmt|;
name|gimp_applicator_blit
argument_list|(
name|applicator
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
name|applicator
argument_list|)
expr_stmt|;
block|}
end_function

begin_comment
comment|/*  Similar to gimp_drawable_apply_region but works in "replace" mode (i.e.  *  transparent pixels in src2 make the result transparent rather than  *  opaque.  *  * Takes an additional mask pixel region as well.  */
end_comment

begin_function
name|void
DECL|function|gimp_drawable_real_replace_buffer (GimpDrawable * drawable,GeglBuffer * buffer,const GeglRectangle * buffer_region,gboolean push_undo,const gchar * undo_desc,gdouble opacity,GeglBuffer * mask_buffer,const GeglRectangle * mask_buffer_region,gint dest_x,gint dest_y)
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
name|GeglBuffer
modifier|*
name|mask_buffer
parameter_list|,
specifier|const
name|GeglRectangle
modifier|*
name|mask_buffer_region
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
name|GeglBuffer
modifier|*
name|drawable_buffer
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
name|gboolean
name|active_components
index|[
name|MAX_CHANNELS
index|]
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
comment|/*  configure the active channel array  */
name|gimp_drawable_get_active_components
argument_list|(
name|drawable
argument_list|,
name|active_components
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
name|drawable_buffer
operator|=
name|gimp_drawable_get_buffer
argument_list|(
name|drawable
argument_list|)
expr_stmt|;
if|if
condition|(
name|mask
condition|)
block|{
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
name|dest_buffer
operator|=
name|gegl_buffer_new
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
name|src_buffer
argument_list|)
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
name|gimp_gegl_combine_mask
argument_list|(
name|mask_buffer
argument_list|,
name|mask_buffer_region
argument_list|,
name|dest_buffer
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
argument_list|,
literal|1.0
argument_list|)
expr_stmt|;
name|gimp_gegl_replace
argument_list|(
name|buffer
argument_list|,
name|buffer_region
argument_list|,
name|drawable_buffer
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
argument_list|,
name|dest_buffer
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
argument_list|,
name|drawable_buffer
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
argument_list|,
name|opacity
argument_list|,
name|active_components
argument_list|)
expr_stmt|;
name|g_object_unref
argument_list|(
name|dest_buffer
argument_list|)
expr_stmt|;
block|}
else|else
block|{
name|gimp_gegl_replace
argument_list|(
name|buffer
argument_list|,
name|buffer_region
argument_list|,
name|drawable_buffer
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
argument_list|,
name|mask_buffer
argument_list|,
name|mask_buffer_region
argument_list|,
name|drawable_buffer
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
argument_list|,
name|opacity
argument_list|,
name|active_components
argument_list|)
expr_stmt|;
block|}
block|}
end_function

end_unit

