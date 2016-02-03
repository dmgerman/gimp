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
file|<cairo.h>
end_include

begin_include
include|#
directive|include
file|<gegl.h>
end_include

begin_include
include|#
directive|include
file|<gdk-pixbuf/gdk-pixbuf.h>
end_include

begin_include
include|#
directive|include
file|"core-types.h"
end_include

begin_include
include|#
directive|include
file|"gegl/gimp-gegl-apply-operation.h"
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
file|"gimpcontext.h"
end_include

begin_include
include|#
directive|include
file|"gimpdrawable-blend.h"
end_include

begin_include
include|#
directive|include
file|"gimpgradient.h"
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

begin_typedef
typedef|typedef
struct|struct
DECL|struct|__anon2c1e1a8a0108
block|{
DECL|member|gradient
name|GimpGradient
modifier|*
name|gradient
decl_stmt|;
DECL|member|context
name|GimpContext
modifier|*
name|context
decl_stmt|;
DECL|member|reverse
name|gboolean
name|reverse
decl_stmt|;
ifdef|#
directive|ifdef
name|USE_GRADIENT_CACHE
DECL|member|gradient_cache
name|GimpRGB
modifier|*
name|gradient_cache
decl_stmt|;
DECL|member|gradient_cache_size
name|gint
name|gradient_cache_size
decl_stmt|;
endif|#
directive|endif
DECL|member|offset
name|gdouble
name|offset
decl_stmt|;
DECL|member|sx
DECL|member|sy
name|gdouble
name|sx
decl_stmt|,
name|sy
decl_stmt|;
DECL|member|gradient_type
name|GimpGradientType
name|gradient_type
decl_stmt|;
DECL|member|dist
name|gdouble
name|dist
decl_stmt|;
DECL|member|vec
name|gdouble
name|vec
index|[
literal|2
index|]
decl_stmt|;
DECL|member|repeat
name|GimpRepeatMode
name|repeat
decl_stmt|;
DECL|member|seed
name|GRand
modifier|*
name|seed
decl_stmt|;
DECL|member|dist_buffer
name|GeglBuffer
modifier|*
name|dist_buffer
decl_stmt|;
DECL|typedef|RenderBlendData
block|}
name|RenderBlendData
typedef|;
end_typedef

begin_typedef
typedef|typedef
struct|struct
DECL|struct|__anon2c1e1a8a0208
block|{
DECL|member|buffer
name|GeglBuffer
modifier|*
name|buffer
decl_stmt|;
DECL|member|row_data
name|gfloat
modifier|*
name|row_data
decl_stmt|;
DECL|member|width
name|gint
name|width
decl_stmt|;
DECL|member|dither_rand
name|GRand
modifier|*
name|dither_rand
decl_stmt|;
DECL|typedef|PutPixelData
block|}
name|PutPixelData
typedef|;
end_typedef

begin_comment
comment|/*  public functions  */
end_comment

begin_function
name|void
DECL|function|gimp_drawable_blend (GimpDrawable * drawable,GimpContext * context,GimpGradient * gradient,GimpLayerModeEffects paint_mode,GimpGradientType gradient_type,gdouble opacity,gdouble offset,GimpRepeatMode repeat,gboolean reverse,gboolean supersample,gint max_depth,gdouble threshold,gboolean dither,gdouble startx,gdouble starty,gdouble endx,gdouble endy,GimpProgress * progress)
name|gimp_drawable_blend
parameter_list|(
name|GimpDrawable
modifier|*
name|drawable
parameter_list|,
name|GimpContext
modifier|*
name|context
parameter_list|,
name|GimpGradient
modifier|*
name|gradient
parameter_list|,
name|GimpLayerModeEffects
name|paint_mode
parameter_list|,
name|GimpGradientType
name|gradient_type
parameter_list|,
name|gdouble
name|opacity
parameter_list|,
name|gdouble
name|offset
parameter_list|,
name|GimpRepeatMode
name|repeat
parameter_list|,
name|gboolean
name|reverse
parameter_list|,
name|gboolean
name|supersample
parameter_list|,
name|gint
name|max_depth
parameter_list|,
name|gdouble
name|threshold
parameter_list|,
name|gboolean
name|dither
parameter_list|,
name|gdouble
name|startx
parameter_list|,
name|gdouble
name|starty
parameter_list|,
name|gdouble
name|endx
parameter_list|,
name|gdouble
name|endy
parameter_list|,
name|GimpProgress
modifier|*
name|progress
parameter_list|)
block|{
name|GimpImage
modifier|*
name|image
decl_stmt|;
name|GeglBuffer
modifier|*
name|buffer
decl_stmt|;
name|GeglBuffer
modifier|*
name|shapeburst
init|=
name|NULL
decl_stmt|;
name|GeglNode
modifier|*
name|render
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
name|gimp_item_is_attached
argument_list|(
name|GIMP_ITEM
argument_list|(
name|drawable
argument_list|)
argument_list|)
argument_list|)
expr_stmt|;
name|g_return_if_fail
argument_list|(
name|GIMP_IS_CONTEXT
argument_list|(
name|context
argument_list|)
argument_list|)
expr_stmt|;
name|g_return_if_fail
argument_list|(
name|GIMP_IS_GRADIENT
argument_list|(
name|gradient
argument_list|)
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
name|image
operator|=
name|gimp_item_get_image
argument_list|(
name|GIMP_ITEM
argument_list|(
name|drawable
argument_list|)
argument_list|)
expr_stmt|;
if|if
condition|(
operator|!
name|gimp_item_mask_intersect
argument_list|(
name|GIMP_ITEM
argument_list|(
name|drawable
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
condition|)
return|return;
name|gimp_set_busy
argument_list|(
name|image
operator|->
name|gimp
argument_list|)
expr_stmt|;
comment|/*  Always create an alpha temp buf (for generality) */
name|buffer
operator|=
name|gegl_buffer_new
argument_list|(
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
name|gimp_drawable_get_format_with_alpha
argument_list|(
name|drawable
argument_list|)
argument_list|)
expr_stmt|;
if|if
condition|(
name|gradient_type
operator|>=
name|GIMP_GRADIENT_SHAPEBURST_ANGULAR
operator|&&
name|gradient_type
operator|<=
name|GIMP_GRADIENT_SHAPEBURST_DIMPLED
condition|)
block|{
name|shapeburst
operator|=
name|gimp_drawable_blend_shapeburst_distmap
argument_list|(
name|drawable
argument_list|,
name|TRUE
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
name|progress
argument_list|)
expr_stmt|;
block|}
name|render
operator|=
name|gegl_node_new_child
argument_list|(
name|NULL
argument_list|,
literal|"operation"
argument_list|,
literal|"gimp:blend"
argument_list|,
literal|"context"
argument_list|,
name|context
argument_list|,
literal|"gradient"
argument_list|,
name|gradient
argument_list|,
literal|"start-x"
argument_list|,
name|startx
argument_list|,
literal|"start-y"
argument_list|,
name|starty
argument_list|,
literal|"end-x"
argument_list|,
name|endx
argument_list|,
literal|"end-y"
argument_list|,
name|endy
argument_list|,
literal|"gradient-type"
argument_list|,
name|gradient_type
argument_list|,
literal|"gradient-repeat"
argument_list|,
name|repeat
argument_list|,
literal|"offset"
argument_list|,
name|offset
argument_list|,
literal|"gradient-reverse"
argument_list|,
name|reverse
argument_list|,
literal|"supersample"
argument_list|,
name|supersample
argument_list|,
literal|"supersample-depth"
argument_list|,
name|max_depth
argument_list|,
literal|"supersample-threshold"
argument_list|,
name|threshold
argument_list|,
literal|"dither"
argument_list|,
name|dither
argument_list|,
name|NULL
argument_list|)
expr_stmt|;
name|gimp_gegl_apply_operation
argument_list|(
name|shapeburst
argument_list|,
name|progress
argument_list|,
name|NULL
argument_list|,
name|render
argument_list|,
name|buffer
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
name|render
argument_list|)
expr_stmt|;
if|if
condition|(
name|shapeburst
condition|)
name|g_object_unref
argument_list|(
name|shapeburst
argument_list|)
expr_stmt|;
name|gimp_drawable_apply_buffer
argument_list|(
name|drawable
argument_list|,
name|buffer
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
name|TRUE
argument_list|,
name|C_
argument_list|(
literal|"undo-type"
argument_list|,
literal|"Blend"
argument_list|)
argument_list|,
name|opacity
argument_list|,
name|paint_mode
argument_list|,
name|NULL
argument_list|,
name|x
argument_list|,
name|y
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
name|g_object_unref
argument_list|(
name|buffer
argument_list|)
expr_stmt|;
name|gimp_unset_busy
argument_list|(
name|image
operator|->
name|gimp
argument_list|)
expr_stmt|;
block|}
end_function

begin_function
name|GeglBuffer
modifier|*
DECL|function|gimp_drawable_blend_shapeburst_distmap (GimpDrawable * drawable,gboolean legacy_shapeburst,const GeglRectangle * region,GimpProgress * progress)
name|gimp_drawable_blend_shapeburst_distmap
parameter_list|(
name|GimpDrawable
modifier|*
name|drawable
parameter_list|,
name|gboolean
name|legacy_shapeburst
parameter_list|,
specifier|const
name|GeglRectangle
modifier|*
name|region
parameter_list|,
name|GimpProgress
modifier|*
name|progress
parameter_list|)
block|{
name|GimpChannel
modifier|*
name|mask
decl_stmt|;
name|GimpImage
modifier|*
name|image
decl_stmt|;
name|GeglBuffer
modifier|*
name|dist_buffer
decl_stmt|;
name|GeglBuffer
modifier|*
name|temp_buffer
decl_stmt|;
name|GeglNode
modifier|*
name|shapeburst
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
name|g_return_val_if_fail
argument_list|(
name|progress
operator|==
name|NULL
operator|||
name|GIMP_IS_PROGRESS
argument_list|(
name|progress
argument_list|)
argument_list|,
name|NULL
argument_list|)
expr_stmt|;
name|image
operator|=
name|gimp_item_get_image
argument_list|(
name|GIMP_ITEM
argument_list|(
name|drawable
argument_list|)
argument_list|)
expr_stmt|;
if|if
condition|(
name|progress
condition|)
name|gimp_progress_set_text_literal
argument_list|(
name|progress
argument_list|,
name|_
argument_list|(
literal|"Calculating distance map"
argument_list|)
argument_list|)
expr_stmt|;
comment|/*  allocate the distance map  */
name|dist_buffer
operator|=
name|gegl_buffer_new
argument_list|(
name|region
argument_list|,
name|babl_format
argument_list|(
literal|"Y float"
argument_list|)
argument_list|)
expr_stmt|;
comment|/*  allocate the selection mask copy  */
name|temp_buffer
operator|=
name|gegl_buffer_new
argument_list|(
name|region
argument_list|,
name|babl_format
argument_list|(
literal|"Y float"
argument_list|)
argument_list|)
expr_stmt|;
name|mask
operator|=
name|gimp_image_get_mask
argument_list|(
name|image
argument_list|)
expr_stmt|;
comment|/*  If the image mask is not empty, use it as the shape burst source  */
if|if
condition|(
operator|!
name|gimp_channel_is_empty
argument_list|(
name|mask
argument_list|)
condition|)
block|{
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
name|off_x
decl_stmt|,
name|off_y
decl_stmt|;
name|gimp_item_mask_intersect
argument_list|(
name|GIMP_ITEM
argument_list|(
name|drawable
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
name|gimp_item_get_offset
argument_list|(
name|GIMP_ITEM
argument_list|(
name|drawable
argument_list|)
argument_list|,
operator|&
name|off_x
argument_list|,
operator|&
name|off_y
argument_list|)
expr_stmt|;
comment|/*  copy the mask to the temp mask  */
name|gegl_buffer_copy
argument_list|(
name|gimp_drawable_get_buffer
argument_list|(
name|GIMP_DRAWABLE
argument_list|(
name|mask
argument_list|)
argument_list|)
argument_list|,
name|GEGL_RECTANGLE
argument_list|(
name|x
operator|+
name|off_x
argument_list|,
name|y
operator|+
name|off_y
argument_list|,
name|width
argument_list|,
name|height
argument_list|)
argument_list|,
name|GEGL_ABYSS_NONE
argument_list|,
name|temp_buffer
argument_list|,
name|region
argument_list|)
expr_stmt|;
block|}
else|else
block|{
comment|/*  If the intended drawable has an alpha channel, use that  */
if|if
condition|(
name|gimp_drawable_has_alpha
argument_list|(
name|drawable
argument_list|)
condition|)
block|{
specifier|const
name|Babl
modifier|*
name|component_format
decl_stmt|;
name|component_format
operator|=
name|babl_format
argument_list|(
literal|"A float"
argument_list|)
expr_stmt|;
comment|/*  extract the aplha into the temp mask  */
name|gegl_buffer_set_format
argument_list|(
name|temp_buffer
argument_list|,
name|component_format
argument_list|)
expr_stmt|;
name|gegl_buffer_copy
argument_list|(
name|gimp_drawable_get_buffer
argument_list|(
name|drawable
argument_list|)
argument_list|,
name|region
argument_list|,
name|GEGL_ABYSS_NONE
argument_list|,
name|temp_buffer
argument_list|,
name|region
argument_list|)
expr_stmt|;
name|gegl_buffer_set_format
argument_list|(
name|temp_buffer
argument_list|,
name|NULL
argument_list|)
expr_stmt|;
block|}
else|else
block|{
name|GeglColor
modifier|*
name|white
init|=
name|gegl_color_new
argument_list|(
literal|"white"
argument_list|)
decl_stmt|;
comment|/*  Otherwise, just fill the shapeburst to white  */
name|gegl_buffer_set_color
argument_list|(
name|temp_buffer
argument_list|,
name|NULL
argument_list|,
name|white
argument_list|)
expr_stmt|;
name|g_object_unref
argument_list|(
name|white
argument_list|)
expr_stmt|;
block|}
block|}
if|if
condition|(
name|legacy_shapeburst
condition|)
name|shapeburst
operator|=
name|gegl_node_new_child
argument_list|(
name|NULL
argument_list|,
literal|"operation"
argument_list|,
literal|"gimp:shapeburst"
argument_list|,
literal|"normalize"
argument_list|,
name|TRUE
argument_list|,
name|NULL
argument_list|)
expr_stmt|;
else|else
name|shapeburst
operator|=
name|gegl_node_new_child
argument_list|(
name|NULL
argument_list|,
literal|"operation"
argument_list|,
literal|"gegl:distance-transform"
argument_list|,
literal|"normalize"
argument_list|,
name|FALSE
argument_list|,
name|NULL
argument_list|)
expr_stmt|;
if|if
condition|(
name|progress
condition|)
name|gimp_gegl_progress_connect
argument_list|(
name|shapeburst
argument_list|,
name|progress
argument_list|,
name|NULL
argument_list|)
expr_stmt|;
name|gimp_gegl_apply_operation
argument_list|(
name|temp_buffer
argument_list|,
name|NULL
argument_list|,
name|NULL
argument_list|,
name|shapeburst
argument_list|,
name|dist_buffer
argument_list|,
name|region
argument_list|)
expr_stmt|;
name|g_object_unref
argument_list|(
name|shapeburst
argument_list|)
expr_stmt|;
name|g_object_unref
argument_list|(
name|temp_buffer
argument_list|)
expr_stmt|;
return|return
name|dist_buffer
return|;
block|}
end_function

end_unit

