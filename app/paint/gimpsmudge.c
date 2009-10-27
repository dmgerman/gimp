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
file|"base/pixel-region.h"
end_include

begin_include
include|#
directive|include
file|"base/temp-buf.h"
end_include

begin_include
include|#
directive|include
file|"paint-funcs/paint-funcs.h"
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
name|gimp_smudge_brush_coords
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
modifier|*
name|x
parameter_list|,
name|gint
modifier|*
name|y
parameter_list|,
name|gint
modifier|*
name|w
parameter_list|,
name|gint
modifier|*
name|h
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
name|handles_transforming_brush
operator|=
name|TRUE
expr_stmt|;
name|brush_core_class
operator|->
name|handles_dynamic_transforming_brush
operator|=
name|FALSE
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
block|{
name|smudge
operator|->
name|initialized
operator|=
name|FALSE
expr_stmt|;
name|smudge
operator|->
name|accum_data
operator|=
name|NULL
expr_stmt|;
block|}
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
name|accum_data
condition|)
block|{
name|g_free
argument_list|(
name|smudge
operator|->
name|accum_data
argument_list|)
expr_stmt|;
name|smudge
operator|->
name|accum_data
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
DECL|function|gimp_smudge_paint (GimpPaintCore * paint_core,GimpDrawable * drawable,GimpPaintOptions * paint_options,const GimpCoords * coords,GimpPaintState paint_state,guint32 time)
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
name|coords
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
name|coords
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
name|accum_data
condition|)
block|{
name|g_free
argument_list|(
name|smudge
operator|->
name|accum_data
argument_list|)
expr_stmt|;
name|smudge
operator|->
name|accum_data
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
DECL|function|gimp_smudge_start (GimpPaintCore * paint_core,GimpDrawable * drawable,GimpPaintOptions * paint_options,const GimpCoords * coords)
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
specifier|const
name|GimpCoords
modifier|*
name|coords
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
name|GimpImage
modifier|*
name|image
decl_stmt|;
name|TempBuf
modifier|*
name|area
decl_stmt|;
name|PixelRegion
name|srcPR
decl_stmt|;
name|gint
name|bytes
decl_stmt|;
name|gint
name|x
decl_stmt|,
name|y
decl_stmt|,
name|w
decl_stmt|,
name|h
decl_stmt|;
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
name|gimp_drawable_is_indexed
argument_list|(
name|drawable
argument_list|)
condition|)
return|return
name|FALSE
return|;
name|area
operator|=
name|gimp_paint_core_get_paint_area
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
if|if
condition|(
operator|!
name|area
condition|)
return|return
name|FALSE
return|;
comment|/*  adjust the x and y coordinates to the upper left corner of the brush  */
name|gimp_smudge_brush_coords
argument_list|(
name|paint_core
argument_list|,
name|coords
argument_list|,
operator|&
name|x
argument_list|,
operator|&
name|y
argument_list|,
operator|&
name|w
argument_list|,
operator|&
name|h
argument_list|)
expr_stmt|;
comment|/*  Allocate the accumulation buffer */
name|bytes
operator|=
name|gimp_drawable_bytes
argument_list|(
name|drawable
argument_list|)
expr_stmt|;
name|smudge
operator|->
name|accum_data
operator|=
name|g_malloc
argument_list|(
name|w
operator|*
name|h
operator|*
name|bytes
argument_list|)
expr_stmt|;
comment|/*  If clipped, prefill the smudge buffer with the color at the    *  brush position.    */
if|if
condition|(
name|x
operator|!=
name|area
operator|->
name|x
operator|||
name|y
operator|!=
name|area
operator|->
name|y
operator|||
name|w
operator|!=
name|area
operator|->
name|width
operator|||
name|h
operator|!=
name|area
operator|->
name|height
condition|)
block|{
name|guchar
name|fill
index|[
literal|4
index|]
decl_stmt|;
name|gimp_pickable_get_pixel_at
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
name|fill
argument_list|)
expr_stmt|;
name|pixel_region_init_data
argument_list|(
operator|&
name|srcPR
argument_list|,
name|smudge
operator|->
name|accum_data
argument_list|,
name|bytes
argument_list|,
name|bytes
operator|*
name|w
argument_list|,
literal|0
argument_list|,
literal|0
argument_list|,
name|w
argument_list|,
name|h
argument_list|)
expr_stmt|;
name|color_region
argument_list|(
operator|&
name|srcPR
argument_list|,
name|fill
argument_list|)
expr_stmt|;
block|}
name|pixel_region_init
argument_list|(
operator|&
name|srcPR
argument_list|,
name|gimp_drawable_get_tiles
argument_list|(
name|drawable
argument_list|)
argument_list|,
name|area
operator|->
name|x
argument_list|,
name|area
operator|->
name|y
argument_list|,
name|area
operator|->
name|width
argument_list|,
name|area
operator|->
name|height
argument_list|,
name|FALSE
argument_list|)
expr_stmt|;
name|pixel_region_init_data
argument_list|(
operator|&
name|smudge
operator|->
name|accumPR
argument_list|,
name|smudge
operator|->
name|accum_data
argument_list|,
name|bytes
argument_list|,
name|bytes
operator|*
name|w
argument_list|,
name|area
operator|->
name|x
operator|-
name|x
argument_list|,
name|area
operator|->
name|y
operator|-
name|y
argument_list|,
name|area
operator|->
name|width
argument_list|,
name|area
operator|->
name|height
argument_list|)
expr_stmt|;
comment|/* copy the region under the original painthit. */
name|copy_region
argument_list|(
operator|&
name|srcPR
argument_list|,
operator|&
name|smudge
operator|->
name|accumPR
argument_list|)
expr_stmt|;
name|pixel_region_init_data
argument_list|(
operator|&
name|smudge
operator|->
name|accumPR
argument_list|,
name|smudge
operator|->
name|accum_data
argument_list|,
name|bytes
argument_list|,
name|bytes
operator|*
name|w
argument_list|,
name|area
operator|->
name|x
operator|-
name|x
argument_list|,
name|area
operator|->
name|y
operator|-
name|y
argument_list|,
name|area
operator|->
name|width
argument_list|,
name|area
operator|->
name|height
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
DECL|function|gimp_smudge_motion (GimpPaintCore * paint_core,GimpDrawable * drawable,GimpPaintOptions * paint_options,const GimpCoords * coords)
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
specifier|const
name|GimpCoords
modifier|*
name|coords
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
decl_stmt|;
name|TempBuf
modifier|*
name|area
decl_stmt|;
name|PixelRegion
name|srcPR
decl_stmt|,
name|destPR
decl_stmt|,
name|tempPR
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
name|gdouble
name|dynamic_rate
decl_stmt|;
name|gint
name|x
decl_stmt|,
name|y
decl_stmt|,
name|w
decl_stmt|,
name|h
decl_stmt|;
name|gdouble
name|hardness
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
name|dynamics
operator|->
name|opacity_output
argument_list|,
name|coords
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
name|area
operator|=
name|gimp_paint_core_get_paint_area
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
if|if
condition|(
operator|!
name|area
condition|)
return|return;
comment|/*  Get the unclipped brush coordinates  */
name|gimp_smudge_brush_coords
argument_list|(
name|paint_core
argument_list|,
name|coords
argument_list|,
operator|&
name|x
argument_list|,
operator|&
name|y
argument_list|,
operator|&
name|w
argument_list|,
operator|&
name|h
argument_list|)
expr_stmt|;
comment|/* srcPR will be the pixels under the current painthit from the drawable */
name|pixel_region_init
argument_list|(
operator|&
name|srcPR
argument_list|,
name|gimp_drawable_get_tiles
argument_list|(
name|drawable
argument_list|)
argument_list|,
name|area
operator|->
name|x
argument_list|,
name|area
operator|->
name|y
argument_list|,
name|area
operator|->
name|width
argument_list|,
name|area
operator|->
name|height
argument_list|,
name|FALSE
argument_list|)
expr_stmt|;
comment|/* Enable dynamic rate */
name|dynamic_rate
operator|=
name|gimp_dynamics_output_get_linear_value
argument_list|(
name|dynamics
operator|->
name|rate_output
argument_list|,
name|coords
argument_list|,
name|fade_point
argument_list|)
expr_stmt|;
name|rate
operator|=
operator|(
name|options
operator|->
name|rate
operator|/
literal|100.0
operator|)
operator|*
name|dynamic_rate
expr_stmt|;
comment|/* The tempPR will be the built up buffer (for smudge) */
name|pixel_region_init_data
argument_list|(
operator|&
name|tempPR
argument_list|,
name|smudge
operator|->
name|accum_data
argument_list|,
name|smudge
operator|->
name|accumPR
operator|.
name|bytes
argument_list|,
name|smudge
operator|->
name|accumPR
operator|.
name|rowstride
argument_list|,
name|area
operator|->
name|x
operator|-
name|x
argument_list|,
name|area
operator|->
name|y
operator|-
name|y
argument_list|,
name|area
operator|->
name|width
argument_list|,
name|area
operator|->
name|height
argument_list|)
expr_stmt|;
comment|/* The dest will be the paint area we got above (= canvas_buf) */
name|pixel_region_init_temp_buf
argument_list|(
operator|&
name|destPR
argument_list|,
name|area
argument_list|,
literal|0
argument_list|,
literal|0
argument_list|,
name|area
operator|->
name|width
argument_list|,
name|area
operator|->
name|height
argument_list|)
expr_stmt|;
comment|/*  Smudge uses the buffer Accum.    *  For each successive painthit Accum is built like this    *    Accum =  rate*Accum  + (1-rate)*I.    *  where I is the pixels under the current painthit.    *  Then the paint area (canvas_buf) is built as    *    (Accum,1) (if no alpha),    */
name|blend_region
argument_list|(
operator|&
name|srcPR
argument_list|,
operator|&
name|tempPR
argument_list|,
operator|&
name|tempPR
argument_list|,
name|ROUND
argument_list|(
name|rate
operator|*
literal|255.0
argument_list|)
argument_list|)
expr_stmt|;
comment|/* re-init the tempPR */
name|pixel_region_init_data
argument_list|(
operator|&
name|tempPR
argument_list|,
name|smudge
operator|->
name|accum_data
argument_list|,
name|smudge
operator|->
name|accumPR
operator|.
name|bytes
argument_list|,
name|smudge
operator|->
name|accumPR
operator|.
name|rowstride
argument_list|,
name|area
operator|->
name|x
operator|-
name|x
argument_list|,
name|area
operator|->
name|y
operator|-
name|y
argument_list|,
name|area
operator|->
name|width
argument_list|,
name|area
operator|->
name|height
argument_list|)
expr_stmt|;
if|if
condition|(
operator|!
name|gimp_drawable_has_alpha
argument_list|(
name|drawable
argument_list|)
condition|)
name|add_alpha_region
argument_list|(
operator|&
name|tempPR
argument_list|,
operator|&
name|destPR
argument_list|)
expr_stmt|;
else|else
name|copy_region
argument_list|(
operator|&
name|tempPR
argument_list|,
operator|&
name|destPR
argument_list|)
expr_stmt|;
name|hardness
operator|=
name|gimp_dynamics_output_get_linear_value
argument_list|(
name|dynamics
operator|->
name|hardness_output
argument_list|,
name|coords
argument_list|,
name|fade_point
argument_list|)
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
name|hardness
argument_list|,
name|GIMP_PAINT_INCREMENTAL
argument_list|)
expr_stmt|;
block|}
end_function

begin_function
specifier|static
name|void
DECL|function|gimp_smudge_brush_coords (GimpPaintCore * paint_core,const GimpCoords * coords,gint * x,gint * y,gint * w,gint * h)
name|gimp_smudge_brush_coords
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
modifier|*
name|x
parameter_list|,
name|gint
modifier|*
name|y
parameter_list|,
name|gint
modifier|*
name|w
parameter_list|,
name|gint
modifier|*
name|h
parameter_list|)
block|{
name|GimpBrushCore
modifier|*
name|brush_core
init|=
name|GIMP_BRUSH_CORE
argument_list|(
name|paint_core
argument_list|)
decl_stmt|;
name|gint
name|width
decl_stmt|;
name|gint
name|height
decl_stmt|;
name|gimp_brush_transform_size
argument_list|(
name|brush_core
operator|->
name|brush
argument_list|,
name|brush_core
operator|->
name|scale
argument_list|,
name|brush_core
operator|->
name|aspect_ratio
argument_list|,
name|brush_core
operator|->
name|angle
argument_list|,
operator|&
name|width
argument_list|,
operator|&
name|height
argument_list|)
expr_stmt|;
comment|/* Note: these are the brush mask size plus a border of 1 pixel */
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
name|width
operator|/
literal|2
operator|-
literal|1
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
name|height
operator|/
literal|2
operator|-
literal|1
expr_stmt|;
operator|*
name|w
operator|=
name|width
operator|+
literal|2
expr_stmt|;
operator|*
name|h
operator|=
name|height
operator|+
literal|2
expr_stmt|;
block|}
end_function

end_unit

