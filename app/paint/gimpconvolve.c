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
file|"paint-types.h"
end_include

begin_include
include|#
directive|include
file|"base/temp-buf.h"
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
file|"core/gimp.h"
end_include

begin_include
include|#
directive|include
file|"core/gimpbrush.h"
end_include

begin_include
include|#
directive|include
file|"core/gimpdrawable.h"
end_include

begin_include
include|#
directive|include
file|"core/gimpdynamics.h"
end_include

begin_include
include|#
directive|include
file|"core/gimpdynamicsoutput.h"
end_include

begin_include
include|#
directive|include
file|"core/gimpimage.h"
end_include

begin_include
include|#
directive|include
file|"core/gimppickable.h"
end_include

begin_include
include|#
directive|include
file|"gimpconvolve.h"
end_include

begin_include
include|#
directive|include
file|"gimpconvolveoptions.h"
end_include

begin_include
include|#
directive|include
file|"gimp-intl.h"
end_include

begin_define
DECL|macro|FIELD_COLS
define|#
directive|define
name|FIELD_COLS
value|4
end_define

begin_define
DECL|macro|MIN_BLUR
define|#
directive|define
name|MIN_BLUR
value|64
end_define

begin_comment
DECL|macro|MIN_BLUR
comment|/*  (8/9 original pixel)   */
end_comment

begin_define
DECL|macro|MAX_BLUR
define|#
directive|define
name|MAX_BLUR
value|0.25
end_define

begin_comment
DECL|macro|MAX_BLUR
comment|/*  (1/33 original pixel)  */
end_comment

begin_define
DECL|macro|MIN_SHARPEN
define|#
directive|define
name|MIN_SHARPEN
value|-512
end_define

begin_define
DECL|macro|MAX_SHARPEN
define|#
directive|define
name|MAX_SHARPEN
value|-64
end_define

begin_function_decl
specifier|static
name|void
name|gimp_convolve_paint
parameter_list|(
name|GimpPaintCore
modifier|*
name|paint_core
parameter_list|,
name|GimpDrawable
modifier|*
name|drawable
parameter_list|,
name|GimpPaintOptions
modifier|*
name|paint_options
parameter_list|,
specifier|const
name|GimpCoords
modifier|*
name|coords
parameter_list|,
name|GimpPaintState
name|paint_state
parameter_list|,
name|guint32
name|time
parameter_list|)
function_decl|;
end_function_decl

begin_function_decl
specifier|static
name|void
name|gimp_convolve_motion
parameter_list|(
name|GimpPaintCore
modifier|*
name|paint_core
parameter_list|,
name|GimpDrawable
modifier|*
name|drawable
parameter_list|,
name|GimpPaintOptions
modifier|*
name|paint_options
parameter_list|,
specifier|const
name|GimpCoords
modifier|*
name|coords
parameter_list|)
function_decl|;
end_function_decl

begin_function_decl
specifier|static
name|void
name|gimp_convolve_calculate_matrix
parameter_list|(
name|GimpConvolve
modifier|*
name|convolve
parameter_list|,
name|GimpConvolveType
name|type
parameter_list|,
name|gint
name|radius_x
parameter_list|,
name|gint
name|radius_y
parameter_list|,
name|gdouble
name|rate
parameter_list|)
function_decl|;
end_function_decl

begin_function_decl
specifier|static
name|gdouble
name|gimp_convolve_sum_matrix
parameter_list|(
specifier|const
name|gfloat
modifier|*
name|matrix
parameter_list|)
function_decl|;
end_function_decl

begin_macro
DECL|function|G_DEFINE_TYPE (GimpConvolve,gimp_convolve,GIMP_TYPE_BRUSH_CORE)
name|G_DEFINE_TYPE
argument_list|(
argument|GimpConvolve
argument_list|,
argument|gimp_convolve
argument_list|,
argument|GIMP_TYPE_BRUSH_CORE
argument_list|)
end_macro

begin_function
name|void
name|gimp_convolve_register
parameter_list|(
name|Gimp
modifier|*
name|gimp
parameter_list|,
name|GimpPaintRegisterCallback
name|callback
parameter_list|)
block|{
call|(
modifier|*
name|callback
call|)
argument_list|(
name|gimp
argument_list|,
name|GIMP_TYPE_CONVOLVE
argument_list|,
name|GIMP_TYPE_CONVOLVE_OPTIONS
argument_list|,
literal|"gimp-convolve"
argument_list|,
name|_
argument_list|(
literal|"Convolve"
argument_list|)
argument_list|,
literal|"gimp-tool-blur"
argument_list|)
expr_stmt|;
block|}
end_function

begin_function
specifier|static
name|void
DECL|function|gimp_convolve_class_init (GimpConvolveClass * klass)
name|gimp_convolve_class_init
parameter_list|(
name|GimpConvolveClass
modifier|*
name|klass
parameter_list|)
block|{
name|GimpPaintCoreClass
modifier|*
name|paint_core_class
init|=
name|GIMP_PAINT_CORE_CLASS
argument_list|(
name|klass
argument_list|)
decl_stmt|;
name|paint_core_class
operator|->
name|paint
operator|=
name|gimp_convolve_paint
expr_stmt|;
block|}
end_function

begin_function
specifier|static
name|void
DECL|function|gimp_convolve_init (GimpConvolve * convolve)
name|gimp_convolve_init
parameter_list|(
name|GimpConvolve
modifier|*
name|convolve
parameter_list|)
block|{
name|gint
name|i
decl_stmt|;
for|for
control|(
name|i
operator|=
literal|0
init|;
name|i
operator|<
literal|9
condition|;
name|i
operator|++
control|)
name|convolve
operator|->
name|matrix
index|[
name|i
index|]
operator|=
literal|1.0
expr_stmt|;
name|convolve
operator|->
name|matrix_divisor
operator|=
literal|9.0
expr_stmt|;
block|}
end_function

begin_function
specifier|static
name|void
DECL|function|gimp_convolve_paint (GimpPaintCore * paint_core,GimpDrawable * drawable,GimpPaintOptions * paint_options,const GimpCoords * coords,GimpPaintState paint_state,guint32 time)
name|gimp_convolve_paint
parameter_list|(
name|GimpPaintCore
modifier|*
name|paint_core
parameter_list|,
name|GimpDrawable
modifier|*
name|drawable
parameter_list|,
name|GimpPaintOptions
modifier|*
name|paint_options
parameter_list|,
specifier|const
name|GimpCoords
modifier|*
name|coords
parameter_list|,
name|GimpPaintState
name|paint_state
parameter_list|,
name|guint32
name|time
parameter_list|)
block|{
switch|switch
condition|(
name|paint_state
condition|)
block|{
case|case
name|GIMP_PAINT_STATE_MOTION
case|:
name|gimp_convolve_motion
argument_list|(
name|paint_core
argument_list|,
name|drawable
argument_list|,
name|paint_options
argument_list|,
name|coords
argument_list|)
expr_stmt|;
break|break;
default|default:
break|break;
block|}
block|}
end_function

begin_function
specifier|static
name|void
DECL|function|gimp_convolve_motion (GimpPaintCore * paint_core,GimpDrawable * drawable,GimpPaintOptions * paint_options,const GimpCoords * coords)
name|gimp_convolve_motion
parameter_list|(
name|GimpPaintCore
modifier|*
name|paint_core
parameter_list|,
name|GimpDrawable
modifier|*
name|drawable
parameter_list|,
name|GimpPaintOptions
modifier|*
name|paint_options
parameter_list|,
specifier|const
name|GimpCoords
modifier|*
name|coords
parameter_list|)
block|{
name|GimpConvolve
modifier|*
name|convolve
init|=
name|GIMP_CONVOLVE
argument_list|(
name|paint_core
argument_list|)
decl_stmt|;
name|GimpBrushCore
modifier|*
name|brush_core
init|=
name|GIMP_BRUSH_CORE
argument_list|(
name|paint_core
argument_list|)
decl_stmt|;
name|GimpConvolveOptions
modifier|*
name|options
init|=
name|GIMP_CONVOLVE_OPTIONS
argument_list|(
name|paint_options
argument_list|)
decl_stmt|;
name|GimpContext
modifier|*
name|context
init|=
name|GIMP_CONTEXT
argument_list|(
name|paint_options
argument_list|)
decl_stmt|;
name|GimpDynamics
modifier|*
name|dynamics
init|=
name|GIMP_BRUSH_CORE
argument_list|(
name|paint_core
argument_list|)
operator|->
name|dynamics
decl_stmt|;
name|GimpDynamicsOutput
modifier|*
name|opacity_output
decl_stmt|;
name|GimpDynamicsOutput
modifier|*
name|rate_output
decl_stmt|;
name|GimpImage
modifier|*
name|image
decl_stmt|;
name|GeglBuffer
modifier|*
name|paint_buffer
decl_stmt|;
name|gint
name|paint_buffer_x
decl_stmt|;
name|gint
name|paint_buffer_y
decl_stmt|;
specifier|const
name|Babl
modifier|*
name|format
decl_stmt|;
name|TempBuf
modifier|*
name|convolve_temp
decl_stmt|;
name|GeglBuffer
modifier|*
name|convolve_buffer
decl_stmt|;
name|gdouble
name|fade_point
decl_stmt|;
name|gdouble
name|opacity
decl_stmt|;
name|gdouble
name|rate
decl_stmt|;
if|if
condition|(
name|gimp_drawable_is_indexed
argument_list|(
name|drawable
argument_list|)
condition|)
return|return;
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
name|opacity_output
operator|=
name|gimp_dynamics_get_output
argument_list|(
name|dynamics
argument_list|,
name|GIMP_DYNAMICS_OUTPUT_OPACITY
argument_list|)
expr_stmt|;
name|fade_point
operator|=
name|gimp_paint_options_get_fade
argument_list|(
name|paint_options
argument_list|,
name|image
argument_list|,
name|paint_core
operator|->
name|pixel_dist
argument_list|)
expr_stmt|;
name|opacity
operator|=
name|gimp_dynamics_output_get_linear_value
argument_list|(
name|opacity_output
argument_list|,
name|coords
argument_list|,
name|paint_options
argument_list|,
name|fade_point
argument_list|)
expr_stmt|;
if|if
condition|(
name|opacity
operator|==
literal|0.0
condition|)
return|return;
name|paint_buffer
operator|=
name|gimp_paint_core_get_paint_buffer
argument_list|(
name|paint_core
argument_list|,
name|drawable
argument_list|,
name|paint_options
argument_list|,
name|coords
argument_list|,
operator|&
name|paint_buffer_x
argument_list|,
operator|&
name|paint_buffer_y
argument_list|)
expr_stmt|;
if|if
condition|(
operator|!
name|paint_buffer
condition|)
return|return;
name|rate_output
operator|=
name|gimp_dynamics_get_output
argument_list|(
name|dynamics
argument_list|,
name|GIMP_DYNAMICS_OUTPUT_RATE
argument_list|)
expr_stmt|;
name|rate
operator|=
operator|(
name|options
operator|->
name|rate
operator|*
name|gimp_dynamics_output_get_linear_value
argument_list|(
name|rate_output
argument_list|,
name|coords
argument_list|,
name|paint_options
argument_list|,
name|fade_point
argument_list|)
operator|)
expr_stmt|;
name|gimp_convolve_calculate_matrix
argument_list|(
name|convolve
argument_list|,
name|options
operator|->
name|type
argument_list|,
name|brush_core
operator|->
name|brush
operator|->
name|mask
operator|->
name|width
operator|/
literal|2
argument_list|,
name|brush_core
operator|->
name|brush
operator|->
name|mask
operator|->
name|height
operator|/
literal|2
argument_list|,
name|rate
argument_list|)
expr_stmt|;
name|format
operator|=
name|gegl_buffer_get_format
argument_list|(
name|paint_buffer
argument_list|)
expr_stmt|;
name|convolve_temp
operator|=
name|temp_buf_new
argument_list|(
name|gegl_buffer_get_width
argument_list|(
name|paint_buffer
argument_list|)
argument_list|,
name|gegl_buffer_get_height
argument_list|(
name|paint_buffer
argument_list|)
argument_list|,
name|babl_format_get_bytes_per_pixel
argument_list|(
name|format
argument_list|)
argument_list|)
expr_stmt|;
name|convolve_buffer
operator|=
name|gimp_temp_buf_create_buffer
argument_list|(
name|convolve_temp
argument_list|,
name|format
argument_list|,
name|TRUE
argument_list|)
expr_stmt|;
name|gegl_buffer_copy
argument_list|(
name|gimp_drawable_get_buffer
argument_list|(
name|drawable
argument_list|)
argument_list|,
name|GEGL_RECTANGLE
argument_list|(
name|paint_buffer_x
argument_list|,
name|paint_buffer_y
argument_list|,
name|gegl_buffer_get_width
argument_list|(
name|paint_buffer
argument_list|)
argument_list|,
name|gegl_buffer_get_height
argument_list|(
name|paint_buffer
argument_list|)
argument_list|)
argument_list|,
name|convolve_buffer
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
name|gimp_gegl_convolve
argument_list|(
name|convolve_buffer
argument_list|,
name|GEGL_RECTANGLE
argument_list|(
literal|0
argument_list|,
literal|0
argument_list|,
name|convolve_temp
operator|->
name|width
argument_list|,
name|convolve_temp
operator|->
name|height
argument_list|)
argument_list|,
name|paint_buffer
argument_list|,
name|GEGL_RECTANGLE
argument_list|(
literal|0
argument_list|,
literal|0
argument_list|,
name|gegl_buffer_get_width
argument_list|(
name|paint_buffer
argument_list|)
argument_list|,
name|gegl_buffer_get_height
argument_list|(
name|paint_buffer
argument_list|)
argument_list|)
argument_list|,
name|convolve
operator|->
name|matrix
argument_list|,
literal|3
argument_list|,
name|convolve
operator|->
name|matrix_divisor
argument_list|,
name|GIMP_NORMAL_CONVOL
argument_list|,
name|TRUE
argument_list|)
expr_stmt|;
name|gimp_brush_core_replace_canvas
argument_list|(
name|brush_core
argument_list|,
name|drawable
argument_list|,
name|coords
argument_list|,
name|MIN
argument_list|(
name|opacity
argument_list|,
name|GIMP_OPACITY_OPAQUE
argument_list|)
argument_list|,
name|gimp_context_get_opacity
argument_list|(
name|context
argument_list|)
argument_list|,
name|gimp_paint_options_get_brush_mode
argument_list|(
name|paint_options
argument_list|)
argument_list|,
literal|1.0
argument_list|,
name|GIMP_PAINT_INCREMENTAL
argument_list|)
expr_stmt|;
block|}
end_function

begin_function
specifier|static
name|void
DECL|function|gimp_convolve_calculate_matrix (GimpConvolve * convolve,GimpConvolveType type,gint radius_x,gint radius_y,gdouble rate)
name|gimp_convolve_calculate_matrix
parameter_list|(
name|GimpConvolve
modifier|*
name|convolve
parameter_list|,
name|GimpConvolveType
name|type
parameter_list|,
name|gint
name|radius_x
parameter_list|,
name|gint
name|radius_y
parameter_list|,
name|gdouble
name|rate
parameter_list|)
block|{
comment|/*  find percent of tool pressure  */
specifier|const
name|gdouble
name|percent
init|=
name|MIN
argument_list|(
name|rate
operator|/
literal|100.0
argument_list|,
literal|1.0
argument_list|)
decl_stmt|;
name|convolve
operator|->
name|matrix
index|[
literal|0
index|]
operator|=
operator|(
name|radius_x
operator|&&
name|radius_y
operator|)
condition|?
literal|1.0
else|:
literal|0.0
expr_stmt|;
name|convolve
operator|->
name|matrix
index|[
literal|1
index|]
operator|=
operator|(
name|radius_y
operator|)
condition|?
literal|1.0
else|:
literal|0.0
expr_stmt|;
name|convolve
operator|->
name|matrix
index|[
literal|2
index|]
operator|=
operator|(
name|radius_x
operator|&&
name|radius_y
operator|)
condition|?
literal|1.0
else|:
literal|0.0
expr_stmt|;
name|convolve
operator|->
name|matrix
index|[
literal|3
index|]
operator|=
operator|(
name|radius_x
operator|)
condition|?
literal|1.0
else|:
literal|0.0
expr_stmt|;
comment|/*  get the appropriate convolution matrix and size and divisor  */
switch|switch
condition|(
name|type
condition|)
block|{
case|case
name|GIMP_BLUR_CONVOLVE
case|:
name|convolve
operator|->
name|matrix
index|[
literal|4
index|]
operator|=
name|MIN_BLUR
operator|+
name|percent
operator|*
operator|(
name|MAX_BLUR
operator|-
name|MIN_BLUR
operator|)
expr_stmt|;
break|break;
case|case
name|GIMP_SHARPEN_CONVOLVE
case|:
name|convolve
operator|->
name|matrix
index|[
literal|4
index|]
operator|=
name|MIN_SHARPEN
operator|+
name|percent
operator|*
operator|(
name|MAX_SHARPEN
operator|-
name|MIN_SHARPEN
operator|)
expr_stmt|;
break|break;
case|case
name|GIMP_CUSTOM_CONVOLVE
case|:
break|break;
block|}
name|convolve
operator|->
name|matrix
index|[
literal|5
index|]
operator|=
operator|(
name|radius_x
operator|)
condition|?
literal|1.0
else|:
literal|0.0
expr_stmt|;
name|convolve
operator|->
name|matrix
index|[
literal|6
index|]
operator|=
operator|(
name|radius_x
operator|&&
name|radius_y
operator|)
condition|?
literal|1.0
else|:
literal|0.0
expr_stmt|;
name|convolve
operator|->
name|matrix
index|[
literal|7
index|]
operator|=
operator|(
name|radius_y
operator|)
condition|?
literal|1.0
else|:
literal|0.0
expr_stmt|;
name|convolve
operator|->
name|matrix
index|[
literal|8
index|]
operator|=
operator|(
name|radius_x
operator|&&
name|radius_y
operator|)
condition|?
literal|1.0
else|:
literal|0.0
expr_stmt|;
name|convolve
operator|->
name|matrix_divisor
operator|=
name|gimp_convolve_sum_matrix
argument_list|(
name|convolve
operator|->
name|matrix
argument_list|)
expr_stmt|;
block|}
end_function

begin_function
specifier|static
name|gdouble
DECL|function|gimp_convolve_sum_matrix (const gfloat * matrix)
name|gimp_convolve_sum_matrix
parameter_list|(
specifier|const
name|gfloat
modifier|*
name|matrix
parameter_list|)
block|{
name|gdouble
name|sum
init|=
literal|0.0
decl_stmt|;
name|gint
name|i
decl_stmt|;
for|for
control|(
name|i
operator|=
literal|0
init|;
name|i
operator|<
literal|9
condition|;
name|i
operator|++
control|)
name|sum
operator|+=
name|matrix
index|[
name|i
index|]
expr_stmt|;
return|return
name|sum
return|;
block|}
end_function

end_unit

