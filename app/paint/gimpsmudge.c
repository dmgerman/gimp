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
file|"libgimpmath/gimpmath.h"
end_include

begin_include
include|#
directive|include
file|"paint-types.h"
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
file|"core/gimpsymmetry.h"
end_include

begin_include
include|#
directive|include
file|"core/gimptempbuf.h"
end_include

begin_include
include|#
directive|include
file|"gimpsmudge.h"
end_include

begin_include
include|#
directive|include
file|"gimpsmudgeoptions.h"
end_include

begin_include
include|#
directive|include
file|"gimp-intl.h"
end_include

begin_function_decl
specifier|static
name|void
name|gimp_smudge_finalize
parameter_list|(
name|GObject
modifier|*
name|object
parameter_list|)
function_decl|;
end_function_decl

begin_function_decl
specifier|static
name|void
name|gimp_smudge_paint
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
name|GimpSymmetry
modifier|*
name|sym
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
name|gboolean
name|gimp_smudge_start
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
name|GimpSymmetry
modifier|*
name|sym
parameter_list|)
function_decl|;
end_function_decl

begin_function_decl
specifier|static
name|void
name|gimp_smudge_motion
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
name|GimpSymmetry
modifier|*
name|sym
parameter_list|)
function_decl|;
end_function_decl

begin_function_decl
specifier|static
name|void
name|gimp_smudge_accumulator_coords
parameter_list|(
name|GimpPaintCore
modifier|*
name|paint_core
parameter_list|,
specifier|const
name|GimpCoords
modifier|*
name|coords
parameter_list|,
name|gint
name|stroke
parameter_list|,
name|gint
modifier|*
name|x
parameter_list|,
name|gint
modifier|*
name|y
parameter_list|)
function_decl|;
end_function_decl

begin_function_decl
specifier|static
name|void
name|gimp_smudge_accumulator_size
parameter_list|(
name|GimpPaintOptions
modifier|*
name|paint_options
parameter_list|,
specifier|const
name|GimpCoords
modifier|*
name|coords
parameter_list|,
name|gint
modifier|*
name|accumulator_size
parameter_list|)
function_decl|;
end_function_decl

begin_macro
DECL|function|G_DEFINE_TYPE (GimpSmudge,gimp_smudge,GIMP_TYPE_BRUSH_CORE)
name|G_DEFINE_TYPE
argument_list|(
argument|GimpSmudge
argument_list|,
argument|gimp_smudge
argument_list|,
argument|GIMP_TYPE_BRUSH_CORE
argument_list|)
end_macro

begin_define
DECL|macro|parent_class
define|#
directive|define
name|parent_class
value|gimp_smudge_parent_class
end_define

begin_function
name|void
name|gimp_smudge_register
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
name|GIMP_TYPE_SMUDGE
argument_list|,
name|GIMP_TYPE_SMUDGE_OPTIONS
argument_list|,
literal|"gimp-smudge"
argument_list|,
name|_
argument_list|(
literal|"Smudge"
argument_list|)
argument_list|,
literal|"gimp-tool-smudge"
argument_list|)
expr_stmt|;
block|}
end_function

begin_function
specifier|static
name|void
DECL|function|gimp_smudge_class_init (GimpSmudgeClass * klass)
name|gimp_smudge_class_init
parameter_list|(
name|GimpSmudgeClass
modifier|*
name|klass
parameter_list|)
block|{
name|GObjectClass
modifier|*
name|object_class
init|=
name|G_OBJECT_CLASS
argument_list|(
name|klass
argument_list|)
decl_stmt|;
name|GimpPaintCoreClass
modifier|*
name|paint_core_class
init|=
name|GIMP_PAINT_CORE_CLASS
argument_list|(
name|klass
argument_list|)
decl_stmt|;
name|GimpBrushCoreClass
modifier|*
name|brush_core_class
init|=
name|GIMP_BRUSH_CORE_CLASS
argument_list|(
name|klass
argument_list|)
decl_stmt|;
name|object_class
operator|->
name|finalize
operator|=
name|gimp_smudge_finalize
expr_stmt|;
name|paint_core_class
operator|->
name|paint
operator|=
name|gimp_smudge_paint
expr_stmt|;
name|brush_core_class
operator|->
name|handles_changing_brush
operator|=
name|TRUE
expr_stmt|;
name|brush_core_class
operator|->
name|handles_transforming_brush
operator|=
name|TRUE
expr_stmt|;
name|brush_core_class
operator|->
name|handles_dynamic_transforming_brush
operator|=
name|TRUE
expr_stmt|;
block|}
end_function

begin_function
specifier|static
name|void
DECL|function|gimp_smudge_init (GimpSmudge * smudge)
name|gimp_smudge_init
parameter_list|(
name|GimpSmudge
modifier|*
name|smudge
parameter_list|)
block|{ }
end_function

begin_function
specifier|static
name|void
DECL|function|gimp_smudge_finalize (GObject * object)
name|gimp_smudge_finalize
parameter_list|(
name|GObject
modifier|*
name|object
parameter_list|)
block|{
name|GimpSmudge
modifier|*
name|smudge
init|=
name|GIMP_SMUDGE
argument_list|(
name|object
argument_list|)
decl_stmt|;
if|if
condition|(
name|smudge
operator|->
name|accum_buffers
condition|)
block|{
name|GList
modifier|*
name|iter
decl_stmt|;
for|for
control|(
name|iter
operator|=
name|smudge
operator|->
name|accum_buffers
init|;
name|iter
condition|;
name|iter
operator|=
name|g_list_next
argument_list|(
name|iter
argument_list|)
control|)
block|{
if|if
condition|(
name|iter
operator|->
name|data
condition|)
name|g_object_unref
argument_list|(
name|iter
operator|->
name|data
argument_list|)
expr_stmt|;
block|}
name|g_list_free
argument_list|(
name|smudge
operator|->
name|accum_buffers
argument_list|)
expr_stmt|;
name|smudge
operator|->
name|accum_buffers
operator|=
name|NULL
expr_stmt|;
block|}
name|G_OBJECT_CLASS
argument_list|(
name|parent_class
argument_list|)
operator|->
name|finalize
argument_list|(
name|object
argument_list|)
expr_stmt|;
block|}
end_function

begin_function
specifier|static
name|void
DECL|function|gimp_smudge_paint (GimpPaintCore * paint_core,GimpDrawable * drawable,GimpPaintOptions * paint_options,GimpSymmetry * sym,GimpPaintState paint_state,guint32 time)
name|gimp_smudge_paint
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
name|GimpSymmetry
modifier|*
name|sym
parameter_list|,
name|GimpPaintState
name|paint_state
parameter_list|,
name|guint32
name|time
parameter_list|)
block|{
name|GimpSmudge
modifier|*
name|smudge
init|=
name|GIMP_SMUDGE
argument_list|(
name|paint_core
argument_list|)
decl_stmt|;
switch|switch
condition|(
name|paint_state
condition|)
block|{
case|case
name|GIMP_PAINT_STATE_MOTION
case|:
comment|/* initialization fails if the user starts outside the drawable */
if|if
condition|(
operator|!
name|smudge
operator|->
name|initialized
condition|)
name|smudge
operator|->
name|initialized
operator|=
name|gimp_smudge_start
argument_list|(
name|paint_core
argument_list|,
name|drawable
argument_list|,
name|paint_options
argument_list|,
name|sym
argument_list|)
expr_stmt|;
if|if
condition|(
name|smudge
operator|->
name|initialized
condition|)
name|gimp_smudge_motion
argument_list|(
name|paint_core
argument_list|,
name|drawable
argument_list|,
name|paint_options
argument_list|,
name|sym
argument_list|)
expr_stmt|;
break|break;
case|case
name|GIMP_PAINT_STATE_FINISH
case|:
if|if
condition|(
name|smudge
operator|->
name|accum_buffers
condition|)
block|{
name|GList
modifier|*
name|iter
decl_stmt|;
for|for
control|(
name|iter
operator|=
name|smudge
operator|->
name|accum_buffers
init|;
name|iter
condition|;
name|iter
operator|=
name|g_list_next
argument_list|(
name|iter
argument_list|)
control|)
block|{
if|if
condition|(
name|iter
operator|->
name|data
condition|)
name|g_object_unref
argument_list|(
name|iter
operator|->
name|data
argument_list|)
expr_stmt|;
block|}
name|g_list_free
argument_list|(
name|smudge
operator|->
name|accum_buffers
argument_list|)
expr_stmt|;
name|smudge
operator|->
name|accum_buffers
operator|=
name|NULL
expr_stmt|;
block|}
name|smudge
operator|->
name|initialized
operator|=
name|FALSE
expr_stmt|;
break|break;
default|default:
break|break;
block|}
block|}
end_function

begin_function
specifier|static
name|gboolean
DECL|function|gimp_smudge_start (GimpPaintCore * paint_core,GimpDrawable * drawable,GimpPaintOptions * paint_options,GimpSymmetry * sym)
name|gimp_smudge_start
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
name|GimpSymmetry
modifier|*
name|sym
parameter_list|)
block|{
name|GimpSmudge
modifier|*
name|smudge
init|=
name|GIMP_SMUDGE
argument_list|(
name|paint_core
argument_list|)
decl_stmt|;
name|GeglBuffer
modifier|*
name|paint_buffer
decl_stmt|;
name|GimpCoords
modifier|*
name|coords
decl_stmt|;
name|gint
name|paint_buffer_x
decl_stmt|;
name|gint
name|paint_buffer_y
decl_stmt|;
name|gint
name|accum_size
decl_stmt|;
name|gint
name|n_strokes
decl_stmt|;
name|gint
name|i
decl_stmt|;
name|gint
name|x
decl_stmt|,
name|y
decl_stmt|;
name|coords
operator|=
name|gimp_symmetry_get_origin
argument_list|(
name|sym
argument_list|)
expr_stmt|;
name|gimp_brush_core_eval_transform_dynamics
argument_list|(
name|GIMP_BRUSH_CORE
argument_list|(
name|paint_core
argument_list|)
argument_list|,
name|drawable
argument_list|,
name|paint_options
argument_list|,
name|coords
argument_list|)
expr_stmt|;
name|n_strokes
operator|=
name|gimp_symmetry_get_size
argument_list|(
name|sym
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
name|n_strokes
condition|;
name|i
operator|++
control|)
block|{
name|GeglBuffer
modifier|*
name|accum_buffer
decl_stmt|;
name|coords
operator|=
name|gimp_symmetry_get_coords
argument_list|(
name|sym
argument_list|,
name|i
argument_list|)
expr_stmt|;
name|gimp_smudge_accumulator_size
argument_list|(
name|paint_options
argument_list|,
name|coords
argument_list|,
operator|&
name|accum_size
argument_list|)
expr_stmt|;
comment|/*  Allocate the accumulation buffer */
name|accum_buffer
operator|=
name|gegl_buffer_new
argument_list|(
name|GEGL_RECTANGLE
argument_list|(
literal|0
argument_list|,
literal|0
argument_list|,
name|accum_size
argument_list|,
name|accum_size
argument_list|)
argument_list|,
name|babl_format
argument_list|(
literal|"RGBA float"
argument_list|)
argument_list|)
expr_stmt|;
name|smudge
operator|->
name|accum_buffers
operator|=
name|g_list_prepend
argument_list|(
name|smudge
operator|->
name|accum_buffers
argument_list|,
name|accum_buffer
argument_list|)
expr_stmt|;
comment|/*  adjust the x and y coordinates to the upper left corner of the        *  accumulator        */
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
name|GIMP_LAYER_MODE_NORMAL_LEGACY
argument_list|,
name|coords
argument_list|,
operator|&
name|paint_buffer_x
argument_list|,
operator|&
name|paint_buffer_y
argument_list|,
name|NULL
argument_list|,
name|NULL
argument_list|)
expr_stmt|;
if|if
condition|(
operator|!
name|paint_buffer
condition|)
continue|continue;
name|gimp_smudge_accumulator_coords
argument_list|(
name|paint_core
argument_list|,
name|coords
argument_list|,
literal|0
argument_list|,
operator|&
name|x
argument_list|,
operator|&
name|y
argument_list|)
expr_stmt|;
comment|/*  If clipped, prefill the smudge buffer with the color at the        *  brush position.        */
if|if
condition|(
name|x
operator|!=
name|paint_buffer_x
operator|||
name|y
operator|!=
name|paint_buffer_y
operator|||
name|accum_size
operator|!=
name|gegl_buffer_get_width
argument_list|(
name|paint_buffer
argument_list|)
operator|||
name|accum_size
operator|!=
name|gegl_buffer_get_height
argument_list|(
name|paint_buffer
argument_list|)
condition|)
block|{
name|GimpRGB
name|pixel
decl_stmt|;
name|GeglColor
modifier|*
name|color
decl_stmt|;
name|gimp_pickable_get_color_at
argument_list|(
name|GIMP_PICKABLE
argument_list|(
name|drawable
argument_list|)
argument_list|,
name|CLAMP
argument_list|(
operator|(
name|gint
operator|)
name|coords
operator|->
name|x
argument_list|,
literal|0
argument_list|,
name|gimp_item_get_width
argument_list|(
name|GIMP_ITEM
argument_list|(
name|drawable
argument_list|)
argument_list|)
operator|-
literal|1
argument_list|)
argument_list|,
name|CLAMP
argument_list|(
operator|(
name|gint
operator|)
name|coords
operator|->
name|y
argument_list|,
literal|0
argument_list|,
name|gimp_item_get_height
argument_list|(
name|GIMP_ITEM
argument_list|(
name|drawable
argument_list|)
argument_list|)
operator|-
literal|1
argument_list|)
argument_list|,
operator|&
name|pixel
argument_list|)
expr_stmt|;
name|color
operator|=
name|gimp_gegl_color_new
argument_list|(
operator|&
name|pixel
argument_list|)
expr_stmt|;
name|gegl_buffer_set_color
argument_list|(
name|accum_buffer
argument_list|,
name|NULL
argument_list|,
name|color
argument_list|)
expr_stmt|;
name|g_object_unref
argument_list|(
name|color
argument_list|)
expr_stmt|;
block|}
comment|/* copy the region under the original painthit. */
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
name|GEGL_ABYSS_NONE
argument_list|,
name|accum_buffer
argument_list|,
name|GEGL_RECTANGLE
argument_list|(
name|paint_buffer_x
operator|-
name|x
argument_list|,
name|paint_buffer_y
operator|-
name|y
argument_list|,
literal|0
argument_list|,
literal|0
argument_list|)
argument_list|)
expr_stmt|;
block|}
name|smudge
operator|->
name|accum_buffers
operator|=
name|g_list_reverse
argument_list|(
name|smudge
operator|->
name|accum_buffers
argument_list|)
expr_stmt|;
return|return
name|TRUE
return|;
block|}
end_function

begin_function
specifier|static
name|void
DECL|function|gimp_smudge_motion (GimpPaintCore * paint_core,GimpDrawable * drawable,GimpPaintOptions * paint_options,GimpSymmetry * sym)
name|gimp_smudge_motion
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
name|GimpSymmetry
modifier|*
name|sym
parameter_list|)
block|{
name|GimpSmudge
modifier|*
name|smudge
init|=
name|GIMP_SMUDGE
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
name|GimpSmudgeOptions
modifier|*
name|options
init|=
name|GIMP_SMUDGE_OPTIONS
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
name|GimpImage
modifier|*
name|image
init|=
name|gimp_item_get_image
argument_list|(
name|GIMP_ITEM
argument_list|(
name|drawable
argument_list|)
argument_list|)
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
name|gint
name|paint_buffer_width
decl_stmt|;
name|gint
name|paint_buffer_height
decl_stmt|;
comment|/* brush dynamics */
name|gdouble
name|fade_point
decl_stmt|;
name|gdouble
name|opacity
decl_stmt|;
name|gdouble
name|rate
decl_stmt|;
name|gdouble
name|flow
decl_stmt|;
name|gdouble
name|grad_point
decl_stmt|;
comment|/* brush color */
name|GimpRGB
name|brush_color
decl_stmt|;
name|GimpRGB
modifier|*
name|brush_color_ptr
decl_stmt|;
comment|/* whether use single color or pixmap */
comment|/* accum buffer */
name|gint
name|x
decl_stmt|,
name|y
decl_stmt|;
name|GeglBuffer
modifier|*
name|accum_buffer
decl_stmt|;
comment|/* other variables */
name|gdouble
name|force
decl_stmt|;
name|GimpCoords
modifier|*
name|coords
decl_stmt|;
name|GeglNode
modifier|*
name|op
decl_stmt|;
name|gint
name|paint_width
decl_stmt|,
name|paint_height
decl_stmt|;
name|gint
name|n_strokes
decl_stmt|;
name|gint
name|i
decl_stmt|;
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
name|coords
operator|=
name|gimp_symmetry_get_origin
argument_list|(
name|sym
argument_list|)
expr_stmt|;
name|opacity
operator|=
name|gimp_dynamics_get_linear_value
argument_list|(
name|dynamics
argument_list|,
name|GIMP_DYNAMICS_OUTPUT_OPACITY
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
name|gimp_brush_core_eval_transform_dynamics
argument_list|(
name|GIMP_BRUSH_CORE
argument_list|(
name|paint_core
argument_list|)
argument_list|,
name|drawable
argument_list|,
name|paint_options
argument_list|,
name|coords
argument_list|)
expr_stmt|;
comment|/* Get brush dynamic values other than opacity */
name|rate
operator|=
operator|(
operator|(
name|options
operator|->
name|rate
operator|/
literal|100.0
operator|)
operator|*
name|gimp_dynamics_get_linear_value
argument_list|(
name|dynamics
argument_list|,
name|GIMP_DYNAMICS_OUTPUT_RATE
argument_list|,
name|coords
argument_list|,
name|paint_options
argument_list|,
name|fade_point
argument_list|)
operator|)
expr_stmt|;
name|flow
operator|=
operator|(
operator|(
name|options
operator|->
name|flow
operator|/
literal|100.0
operator|)
operator|*
name|gimp_dynamics_get_linear_value
argument_list|(
name|dynamics
argument_list|,
name|GIMP_DYNAMICS_OUTPUT_FLOW
argument_list|,
name|coords
argument_list|,
name|paint_options
argument_list|,
name|fade_point
argument_list|)
operator|)
expr_stmt|;
name|grad_point
operator|=
name|gimp_dynamics_get_linear_value
argument_list|(
name|dynamics
argument_list|,
name|GIMP_DYNAMICS_OUTPUT_COLOR
argument_list|,
name|coords
argument_list|,
name|paint_options
argument_list|,
name|fade_point
argument_list|)
expr_stmt|;
comment|/* Get current gradient color, brush pixmap, or foreground color */
name|brush_color_ptr
operator|=
operator|&
name|brush_color
expr_stmt|;
if|if
condition|(
name|gimp_paint_options_get_gradient_color
argument_list|(
name|paint_options
argument_list|,
name|image
argument_list|,
name|grad_point
argument_list|,
name|paint_core
operator|->
name|pixel_dist
argument_list|,
operator|&
name|brush_color
argument_list|)
condition|)
block|{
comment|/* No more processing needed */
block|}
elseif|else
if|if
condition|(
name|brush_core
operator|->
name|brush
operator|&&
name|gimp_brush_get_pixmap
argument_list|(
name|brush_core
operator|->
name|brush
argument_list|)
condition|)
block|{
name|brush_color_ptr
operator|=
name|NULL
expr_stmt|;
block|}
else|else
block|{
name|gimp_context_get_foreground
argument_list|(
name|context
argument_list|,
operator|&
name|brush_color
argument_list|)
expr_stmt|;
block|}
comment|/* Convert to linear RGBA */
if|if
condition|(
name|brush_color_ptr
condition|)
name|gimp_pickable_srgb_to_pixel
argument_list|(
name|GIMP_PICKABLE
argument_list|(
name|drawable
argument_list|)
argument_list|,
operator|&
name|brush_color
argument_list|,
name|babl_format
argument_list|(
literal|"RGBA double"
argument_list|)
argument_list|,
operator|&
name|brush_color
argument_list|)
expr_stmt|;
name|n_strokes
operator|=
name|gimp_symmetry_get_size
argument_list|(
name|sym
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
name|n_strokes
condition|;
name|i
operator|++
control|)
block|{
name|coords
operator|=
name|gimp_symmetry_get_coords
argument_list|(
name|sym
argument_list|,
name|i
argument_list|)
expr_stmt|;
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
name|GIMP_LAYER_MODE_NORMAL_LEGACY
argument_list|,
name|coords
argument_list|,
operator|&
name|paint_buffer_x
argument_list|,
operator|&
name|paint_buffer_y
argument_list|,
operator|&
name|paint_width
argument_list|,
operator|&
name|paint_height
argument_list|)
expr_stmt|;
if|if
condition|(
operator|!
name|paint_buffer
condition|)
continue|continue;
name|op
operator|=
name|gimp_symmetry_get_operation
argument_list|(
name|sym
argument_list|,
name|i
argument_list|,
name|paint_width
argument_list|,
name|paint_height
argument_list|)
expr_stmt|;
name|paint_buffer_width
operator|=
name|gegl_buffer_get_width
argument_list|(
name|paint_buffer
argument_list|)
expr_stmt|;
name|paint_buffer_height
operator|=
name|gegl_buffer_get_height
argument_list|(
name|paint_buffer
argument_list|)
expr_stmt|;
comment|/*  Get the unclipped acumulator coordinates  */
name|gimp_smudge_accumulator_coords
argument_list|(
name|paint_core
argument_list|,
name|coords
argument_list|,
name|i
argument_list|,
operator|&
name|x
argument_list|,
operator|&
name|y
argument_list|)
expr_stmt|;
name|accum_buffer
operator|=
name|g_list_nth_data
argument_list|(
name|smudge
operator|->
name|accum_buffers
argument_list|,
name|i
argument_list|)
expr_stmt|;
comment|/* Old smudge tool:        *  Smudge uses the buffer Accum.        *  For each successive painthit Accum is built like this        *    Accum =  rate*Accum  + (1-rate)*I.        *  where I is the pixels under the current painthit.        *  Then the paint area (paint_area) is built as        *    (Accum,1) (if no alpha),        */
comment|/* 2017/4/22: New smudge painting tool:        * Accum=rate*Accum + (1-rate)*I        * if brush_color_ptr!=NULL        *   Paint=(1-flow)*Accum + flow*BrushColor        * else, draw brush pixmap on the paint_buffer and        *   Paint=(1-flow)*Accum + flow*Paint        *        * For non-pixmap brushes, calculate blending in        * gimp_gegl_smudge_with_paint() instead of calling        * gegl_buffer_set_color() to reduce gegl's internal processing.        */
if|if
condition|(
operator|!
name|brush_color_ptr
condition|)
block|{
name|gimp_brush_core_color_area_with_pixmap
argument_list|(
name|brush_core
argument_list|,
name|drawable
argument_list|,
name|coords
argument_list|,
name|op
argument_list|,
name|paint_buffer
argument_list|,
name|paint_buffer_x
argument_list|,
name|paint_buffer_y
argument_list|,
name|gimp_paint_options_get_brush_mode
argument_list|(
name|paint_options
argument_list|)
argument_list|)
expr_stmt|;
block|}
name|gimp_gegl_smudge_with_paint
argument_list|(
name|accum_buffer
argument_list|,
name|GEGL_RECTANGLE
argument_list|(
name|paint_buffer_x
operator|-
name|x
argument_list|,
name|paint_buffer_y
operator|-
name|y
argument_list|,
name|paint_buffer_width
argument_list|,
name|paint_buffer_height
argument_list|)
argument_list|,
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
name|paint_buffer_width
argument_list|,
name|paint_buffer_height
argument_list|)
argument_list|,
name|brush_color_ptr
argument_list|,
name|paint_buffer
argument_list|,
name|options
operator|->
name|no_erasing
argument_list|,
name|flow
argument_list|,
name|rate
argument_list|)
expr_stmt|;
if|if
condition|(
name|gimp_dynamics_is_output_enabled
argument_list|(
name|dynamics
argument_list|,
name|GIMP_DYNAMICS_OUTPUT_FORCE
argument_list|)
condition|)
name|force
operator|=
name|gimp_dynamics_get_linear_value
argument_list|(
name|dynamics
argument_list|,
name|GIMP_DYNAMICS_OUTPUT_FORCE
argument_list|,
name|coords
argument_list|,
name|paint_options
argument_list|,
name|fade_point
argument_list|)
expr_stmt|;
else|else
name|force
operator|=
name|paint_options
operator|->
name|brush_force
expr_stmt|;
name|gimp_brush_core_replace_canvas
argument_list|(
name|GIMP_BRUSH_CORE
argument_list|(
name|paint_core
argument_list|)
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
name|force
argument_list|,
name|GIMP_PAINT_INCREMENTAL
argument_list|,
name|op
argument_list|)
expr_stmt|;
block|}
block|}
end_function

begin_function
specifier|static
name|void
DECL|function|gimp_smudge_accumulator_coords (GimpPaintCore * paint_core,const GimpCoords * coords,gint stroke,gint * x,gint * y)
name|gimp_smudge_accumulator_coords
parameter_list|(
name|GimpPaintCore
modifier|*
name|paint_core
parameter_list|,
specifier|const
name|GimpCoords
modifier|*
name|coords
parameter_list|,
name|gint
name|stroke
parameter_list|,
name|gint
modifier|*
name|x
parameter_list|,
name|gint
modifier|*
name|y
parameter_list|)
block|{
name|GimpSmudge
modifier|*
name|smudge
init|=
name|GIMP_SMUDGE
argument_list|(
name|paint_core
argument_list|)
decl_stmt|;
name|GeglBuffer
modifier|*
name|accum_buffer
decl_stmt|;
name|accum_buffer
operator|=
name|g_list_nth_data
argument_list|(
name|smudge
operator|->
name|accum_buffers
argument_list|,
name|stroke
argument_list|)
expr_stmt|;
operator|*
name|x
operator|=
operator|(
name|gint
operator|)
name|coords
operator|->
name|x
operator|-
name|gegl_buffer_get_width
argument_list|(
name|accum_buffer
argument_list|)
operator|/
literal|2
expr_stmt|;
operator|*
name|y
operator|=
operator|(
name|gint
operator|)
name|coords
operator|->
name|y
operator|-
name|gegl_buffer_get_height
argument_list|(
name|accum_buffer
argument_list|)
operator|/
literal|2
expr_stmt|;
block|}
end_function

begin_function
specifier|static
name|void
DECL|function|gimp_smudge_accumulator_size (GimpPaintOptions * paint_options,const GimpCoords * coords,gint * accumulator_size)
name|gimp_smudge_accumulator_size
parameter_list|(
name|GimpPaintOptions
modifier|*
name|paint_options
parameter_list|,
specifier|const
name|GimpCoords
modifier|*
name|coords
parameter_list|,
name|gint
modifier|*
name|accumulator_size
parameter_list|)
block|{
name|gdouble
name|max_view_scale
init|=
literal|1.0
decl_stmt|;
name|gdouble
name|max_brush_size
decl_stmt|;
if|if
condition|(
name|paint_options
operator|->
name|brush_zoom
condition|)
name|max_view_scale
operator|=
name|MAX
argument_list|(
name|coords
operator|->
name|xscale
argument_list|,
name|coords
operator|->
name|yscale
argument_list|)
expr_stmt|;
name|max_brush_size
operator|=
name|MIN
argument_list|(
name|paint_options
operator|->
name|brush_size
operator|/
name|max_view_scale
argument_list|,
name|GIMP_BRUSH_MAX_SIZE
argument_list|)
expr_stmt|;
comment|/* Note: the max brush mask size plus a border of 1 pixel and a    * little headroom    */
operator|*
name|accumulator_size
operator|=
name|ceil
argument_list|(
name|sqrt
argument_list|(
literal|2
operator|*
name|SQR
argument_list|(
name|max_brush_size
operator|+
literal|1
argument_list|)
argument_list|)
operator|+
literal|2
argument_list|)
expr_stmt|;
block|}
end_function

end_unit

