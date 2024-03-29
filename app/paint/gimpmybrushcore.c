begin_unit|revision:0.9.5;language:C;cregit-version:0.0.1
begin_comment
comment|/* GIMP - The GNU Image Manipulation Program  * Copyright (C) 1995 Spencer Kimball and Peter Mattis  *  * This program is free software: you can redistribute it and/or modify  * it under the terms of the GNU General Public License as published by  * the Free Software Foundation; either version 3 of the License, or  * (at your option) any later version.  *  * This program is distributed in the hope that it will be useful,  * but WITHOUT ANY WARRANTY; without even the implied warranty of  * MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the  * GNU General Public License for more details.  *  * You should have received a copy of the GNU General Public License  * along with this program.  If not, see<https://www.gnu.org/licenses/>.  */
end_comment

begin_include
include|#
directive|include
file|"config.h"
end_include

begin_include
include|#
directive|include
file|<string.h>
end_include

begin_include
include|#
directive|include
file|<cairo.h>
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
file|<mypaint-brush.h>
end_include

begin_include
include|#
directive|include
file|"libgimpmath/gimpmath.h"
end_include

begin_include
include|#
directive|include
file|"libgimpcolor/gimpcolor.h"
end_include

begin_include
include|#
directive|include
file|"paint-types.h"
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
file|"core/gimp-palettes.h"
end_include

begin_include
include|#
directive|include
file|"core/gimpdrawable.h"
end_include

begin_include
include|#
directive|include
file|"core/gimperror.h"
end_include

begin_include
include|#
directive|include
file|"core/gimpmybrush.h"
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
file|"gimpmybrushcore.h"
end_include

begin_include
include|#
directive|include
file|"gimpmybrushsurface.h"
end_include

begin_include
include|#
directive|include
file|"gimpmybrushoptions.h"
end_include

begin_include
include|#
directive|include
file|"gimp-intl.h"
end_include

begin_struct
DECL|struct|_GimpMybrushCorePrivate
struct|struct
name|_GimpMybrushCorePrivate
block|{
DECL|member|mybrush
name|GimpMybrush
modifier|*
name|mybrush
decl_stmt|;
DECL|member|surface
name|GimpMybrushSurface
modifier|*
name|surface
decl_stmt|;
DECL|member|brushes
name|GList
modifier|*
name|brushes
decl_stmt|;
DECL|member|synthetic
name|gboolean
name|synthetic
decl_stmt|;
DECL|member|last_time
name|gint64
name|last_time
decl_stmt|;
block|}
struct|;
end_struct

begin_comment
comment|/*  local function prototypes  */
end_comment

begin_function_decl
specifier|static
name|void
name|gimp_mybrush_core_finalize
parameter_list|(
name|GObject
modifier|*
name|object
parameter_list|)
function_decl|;
end_function_decl

begin_function_decl
specifier|static
name|gboolean
name|gimp_mybrush_core_start
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
name|GError
modifier|*
modifier|*
name|error
parameter_list|)
function_decl|;
end_function_decl

begin_function_decl
specifier|static
name|void
name|gimp_mybrush_core_interpolate
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
name|guint32
name|time
parameter_list|)
function_decl|;
end_function_decl

begin_function_decl
specifier|static
name|void
name|gimp_mybrush_core_paint
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
name|void
name|gimp_mybrush_core_motion
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
name|guint32
name|time
parameter_list|)
function_decl|;
end_function_decl

begin_function_decl
specifier|static
name|void
name|gimp_mybrush_core_create_brushes
parameter_list|(
name|GimpMybrushCore
modifier|*
name|mybrush
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

begin_macro
DECL|function|G_DEFINE_TYPE_WITH_PRIVATE (GimpMybrushCore,gimp_mybrush_core,GIMP_TYPE_PAINT_CORE)
name|G_DEFINE_TYPE_WITH_PRIVATE
argument_list|(
argument|GimpMybrushCore
argument_list|,
argument|gimp_mybrush_core
argument_list|,
argument|GIMP_TYPE_PAINT_CORE
argument_list|)
end_macro

begin_define
DECL|macro|parent_class
define|#
directive|define
name|parent_class
value|gimp_mybrush_core_parent_class
end_define

begin_function
name|void
name|gimp_mybrush_core_register
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
name|GIMP_TYPE_MYBRUSH_CORE
argument_list|,
name|GIMP_TYPE_MYBRUSH_OPTIONS
argument_list|,
literal|"gimp-mybrush"
argument_list|,
name|_
argument_list|(
literal|"Mybrush"
argument_list|)
argument_list|,
literal|"gimp-tool-mypaint-brush"
argument_list|)
expr_stmt|;
block|}
end_function

begin_function
specifier|static
name|void
DECL|function|gimp_mybrush_core_class_init (GimpMybrushCoreClass * klass)
name|gimp_mybrush_core_class_init
parameter_list|(
name|GimpMybrushCoreClass
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
name|object_class
operator|->
name|finalize
operator|=
name|gimp_mybrush_core_finalize
expr_stmt|;
name|paint_core_class
operator|->
name|start
operator|=
name|gimp_mybrush_core_start
expr_stmt|;
name|paint_core_class
operator|->
name|paint
operator|=
name|gimp_mybrush_core_paint
expr_stmt|;
name|paint_core_class
operator|->
name|interpolate
operator|=
name|gimp_mybrush_core_interpolate
expr_stmt|;
block|}
end_function

begin_function
specifier|static
name|void
DECL|function|gimp_mybrush_core_init (GimpMybrushCore * mybrush)
name|gimp_mybrush_core_init
parameter_list|(
name|GimpMybrushCore
modifier|*
name|mybrush
parameter_list|)
block|{
name|mybrush
operator|->
name|private
operator|=
name|gimp_mybrush_core_get_instance_private
argument_list|(
name|mybrush
argument_list|)
expr_stmt|;
block|}
end_function

begin_function
specifier|static
name|void
DECL|function|gimp_mybrush_core_finalize (GObject * object)
name|gimp_mybrush_core_finalize
parameter_list|(
name|GObject
modifier|*
name|object
parameter_list|)
block|{
name|GimpMybrushCore
modifier|*
name|core
init|=
name|GIMP_MYBRUSH_CORE
argument_list|(
name|object
argument_list|)
decl_stmt|;
if|if
condition|(
name|core
operator|->
name|private
operator|->
name|brushes
condition|)
block|{
name|g_list_free_full
argument_list|(
name|core
operator|->
name|private
operator|->
name|brushes
argument_list|,
operator|(
name|GDestroyNotify
operator|)
name|mypaint_brush_unref
argument_list|)
expr_stmt|;
name|core
operator|->
name|private
operator|->
name|brushes
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
name|gboolean
DECL|function|gimp_mybrush_core_start (GimpPaintCore * paint_core,GimpDrawable * drawable,GimpPaintOptions * paint_options,const GimpCoords * coords,GError ** error)
name|gimp_mybrush_core_start
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
name|GError
modifier|*
modifier|*
name|error
parameter_list|)
block|{
name|GimpMybrushCore
modifier|*
name|core
init|=
name|GIMP_MYBRUSH_CORE
argument_list|(
name|paint_core
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
name|core
operator|->
name|private
operator|->
name|mybrush
operator|=
name|gimp_context_get_mybrush
argument_list|(
name|context
argument_list|)
expr_stmt|;
if|if
condition|(
operator|!
name|core
operator|->
name|private
operator|->
name|mybrush
condition|)
block|{
name|g_set_error_literal
argument_list|(
name|error
argument_list|,
name|GIMP_ERROR
argument_list|,
name|GIMP_FAILED
argument_list|,
name|_
argument_list|(
literal|"No MyPaint brushes available for use with this tool."
argument_list|)
argument_list|)
expr_stmt|;
return|return
name|FALSE
return|;
block|}
return|return
name|TRUE
return|;
block|}
end_function

begin_function
specifier|static
name|void
DECL|function|gimp_mybrush_core_interpolate (GimpPaintCore * paint_core,GimpDrawable * drawable,GimpPaintOptions * paint_options,guint32 time)
name|gimp_mybrush_core_interpolate
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
name|guint32
name|time
parameter_list|)
block|{
name|GimpMybrushCore
modifier|*
name|mybrush
init|=
name|GIMP_MYBRUSH_CORE
argument_list|(
name|paint_core
argument_list|)
decl_stmt|;
comment|/* If this is the first motion the brush has received then    * we're being asked to draw a synthetic stroke in line mode    */
if|if
condition|(
name|mybrush
operator|->
name|private
operator|->
name|last_time
operator|<
literal|0
condition|)
block|{
name|GimpCoords
name|saved_coords
init|=
name|paint_core
operator|->
name|cur_coords
decl_stmt|;
name|paint_core
operator|->
name|cur_coords
operator|=
name|paint_core
operator|->
name|last_coords
expr_stmt|;
name|mybrush
operator|->
name|private
operator|->
name|synthetic
operator|=
name|TRUE
expr_stmt|;
name|gimp_paint_core_paint
argument_list|(
name|paint_core
argument_list|,
name|drawable
argument_list|,
name|paint_options
argument_list|,
name|GIMP_PAINT_STATE_MOTION
argument_list|,
name|time
argument_list|)
expr_stmt|;
name|paint_core
operator|->
name|cur_coords
operator|=
name|saved_coords
expr_stmt|;
block|}
name|gimp_paint_core_paint
argument_list|(
name|paint_core
argument_list|,
name|drawable
argument_list|,
name|paint_options
argument_list|,
name|GIMP_PAINT_STATE_MOTION
argument_list|,
name|time
argument_list|)
expr_stmt|;
name|paint_core
operator|->
name|last_coords
operator|=
name|paint_core
operator|->
name|cur_coords
expr_stmt|;
block|}
end_function

begin_function
specifier|static
name|void
DECL|function|gimp_mybrush_core_paint (GimpPaintCore * paint_core,GimpDrawable * drawable,GimpPaintOptions * paint_options,GimpSymmetry * sym,GimpPaintState paint_state,guint32 time)
name|gimp_mybrush_core_paint
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
name|GimpMybrushCore
modifier|*
name|mybrush
init|=
name|GIMP_MYBRUSH_CORE
argument_list|(
name|paint_core
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
name|GimpRGB
name|fg
decl_stmt|;
switch|switch
condition|(
name|paint_state
condition|)
block|{
case|case
name|GIMP_PAINT_STATE_INIT
case|:
name|gimp_context_get_foreground
argument_list|(
name|context
argument_list|,
operator|&
name|fg
argument_list|)
expr_stmt|;
name|gimp_palettes_add_color_history
argument_list|(
name|context
operator|->
name|gimp
argument_list|,
operator|&
name|fg
argument_list|)
expr_stmt|;
name|gimp_symmetry_set_stateful
argument_list|(
name|sym
argument_list|,
name|TRUE
argument_list|)
expr_stmt|;
name|mybrush
operator|->
name|private
operator|->
name|surface
operator|=
name|gimp_mypaint_surface_new
argument_list|(
name|gimp_drawable_get_buffer
argument_list|(
name|drawable
argument_list|)
argument_list|,
name|gimp_drawable_get_active_mask
argument_list|(
name|drawable
argument_list|)
argument_list|,
name|paint_core
operator|->
name|mask_buffer
argument_list|,
name|paint_core
operator|->
name|mask_x_offset
argument_list|,
name|paint_core
operator|->
name|mask_y_offset
argument_list|,
name|GIMP_MYBRUSH_OPTIONS
argument_list|(
name|paint_options
argument_list|)
argument_list|)
expr_stmt|;
name|gimp_mybrush_core_create_brushes
argument_list|(
name|mybrush
argument_list|,
name|drawable
argument_list|,
name|paint_options
argument_list|,
name|sym
argument_list|)
expr_stmt|;
name|mybrush
operator|->
name|private
operator|->
name|last_time
operator|=
operator|-
literal|1
expr_stmt|;
name|mybrush
operator|->
name|private
operator|->
name|synthetic
operator|=
name|FALSE
expr_stmt|;
break|break;
case|case
name|GIMP_PAINT_STATE_MOTION
case|:
name|gimp_mybrush_core_motion
argument_list|(
name|paint_core
argument_list|,
name|drawable
argument_list|,
name|paint_options
argument_list|,
name|sym
argument_list|,
name|time
argument_list|)
expr_stmt|;
break|break;
case|case
name|GIMP_PAINT_STATE_FINISH
case|:
name|gimp_symmetry_set_stateful
argument_list|(
name|sym
argument_list|,
name|FALSE
argument_list|)
expr_stmt|;
name|mypaint_surface_unref
argument_list|(
operator|(
name|MyPaintSurface
operator|*
operator|)
name|mybrush
operator|->
name|private
operator|->
name|surface
argument_list|)
expr_stmt|;
name|mybrush
operator|->
name|private
operator|->
name|surface
operator|=
name|NULL
expr_stmt|;
name|g_list_free_full
argument_list|(
name|mybrush
operator|->
name|private
operator|->
name|brushes
argument_list|,
operator|(
name|GDestroyNotify
operator|)
name|mypaint_brush_unref
argument_list|)
expr_stmt|;
name|mybrush
operator|->
name|private
operator|->
name|brushes
operator|=
name|NULL
expr_stmt|;
break|break;
block|}
block|}
end_function

begin_function
specifier|static
name|void
DECL|function|gimp_mybrush_core_motion (GimpPaintCore * paint_core,GimpDrawable * drawable,GimpPaintOptions * paint_options,GimpSymmetry * sym,guint32 time)
name|gimp_mybrush_core_motion
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
name|guint32
name|time
parameter_list|)
block|{
name|GimpMybrushCore
modifier|*
name|mybrush
init|=
name|GIMP_MYBRUSH_CORE
argument_list|(
name|paint_core
argument_list|)
decl_stmt|;
name|MyPaintRectangle
name|rect
decl_stmt|;
name|GList
modifier|*
name|iter
decl_stmt|;
name|gdouble
name|dt
init|=
literal|0.0
decl_stmt|;
name|gint
name|n_strokes
decl_stmt|;
name|gint
name|i
decl_stmt|;
name|n_strokes
operator|=
name|gimp_symmetry_get_size
argument_list|(
name|sym
argument_list|)
expr_stmt|;
comment|/* The number of strokes may change during a motion, depending on    * the type of symmetry. When that happens, reset the brushes.    */
if|if
condition|(
name|g_list_length
argument_list|(
name|mybrush
operator|->
name|private
operator|->
name|brushes
argument_list|)
operator|!=
name|n_strokes
condition|)
block|{
name|gimp_mybrush_core_create_brushes
argument_list|(
name|mybrush
argument_list|,
name|drawable
argument_list|,
name|paint_options
argument_list|,
name|sym
argument_list|)
expr_stmt|;
block|}
name|mypaint_surface_begin_atomic
argument_list|(
operator|(
name|MyPaintSurface
operator|*
operator|)
name|mybrush
operator|->
name|private
operator|->
name|surface
argument_list|)
expr_stmt|;
if|if
condition|(
name|mybrush
operator|->
name|private
operator|->
name|last_time
operator|<
literal|0
condition|)
block|{
comment|/* First motion, so we need zero pressure events to start the strokes */
for|for
control|(
name|iter
operator|=
name|mybrush
operator|->
name|private
operator|->
name|brushes
operator|,
name|i
operator|=
literal|0
init|;
name|iter
condition|;
name|iter
operator|=
name|g_list_next
argument_list|(
name|iter
argument_list|)
operator|,
name|i
operator|++
control|)
block|{
name|MyPaintBrush
modifier|*
name|brush
init|=
name|iter
operator|->
name|data
decl_stmt|;
name|GimpCoords
modifier|*
name|coords
init|=
name|gimp_symmetry_get_coords
argument_list|(
name|sym
argument_list|,
name|i
argument_list|)
decl_stmt|;
name|mypaint_brush_stroke_to
argument_list|(
name|brush
argument_list|,
operator|(
name|MyPaintSurface
operator|*
operator|)
name|mybrush
operator|->
name|private
operator|->
name|surface
argument_list|,
name|coords
operator|->
name|x
argument_list|,
name|coords
operator|->
name|y
argument_list|,
literal|0.0f
argument_list|,
name|coords
operator|->
name|xtilt
argument_list|,
name|coords
operator|->
name|ytilt
argument_list|,
literal|1.0f
comment|/* Pretend the cursor hasn't moved in a while */
argument_list|)
expr_stmt|;
block|}
name|dt
operator|=
literal|0.015
expr_stmt|;
block|}
elseif|else
if|if
condition|(
name|mybrush
operator|->
name|private
operator|->
name|synthetic
condition|)
block|{
name|GimpVector2
name|v
init|=
block|{
name|paint_core
operator|->
name|cur_coords
operator|.
name|x
operator|-
name|paint_core
operator|->
name|last_coords
operator|.
name|x
block|,
name|paint_core
operator|->
name|cur_coords
operator|.
name|y
operator|-
name|paint_core
operator|->
name|last_coords
operator|.
name|y
block|}
decl_stmt|;
name|dt
operator|=
literal|0.0005
operator|*
name|gimp_vector2_length_val
argument_list|(
name|v
argument_list|)
expr_stmt|;
block|}
else|else
block|{
name|dt
operator|=
operator|(
name|time
operator|-
name|mybrush
operator|->
name|private
operator|->
name|last_time
operator|)
operator|*
literal|0.001
expr_stmt|;
block|}
for|for
control|(
name|iter
operator|=
name|mybrush
operator|->
name|private
operator|->
name|brushes
operator|,
name|i
operator|=
literal|0
init|;
name|iter
condition|;
name|iter
operator|=
name|g_list_next
argument_list|(
name|iter
argument_list|)
operator|,
name|i
operator|++
control|)
block|{
name|MyPaintBrush
modifier|*
name|brush
init|=
name|iter
operator|->
name|data
decl_stmt|;
name|GimpCoords
modifier|*
name|coords
init|=
name|gimp_symmetry_get_coords
argument_list|(
name|sym
argument_list|,
name|i
argument_list|)
decl_stmt|;
name|gdouble
name|pressure
init|=
name|coords
operator|->
name|pressure
decl_stmt|;
name|mypaint_brush_stroke_to
argument_list|(
name|brush
argument_list|,
operator|(
name|MyPaintSurface
operator|*
operator|)
name|mybrush
operator|->
name|private
operator|->
name|surface
argument_list|,
name|coords
operator|->
name|x
argument_list|,
name|coords
operator|->
name|y
argument_list|,
name|pressure
argument_list|,
name|coords
operator|->
name|xtilt
argument_list|,
name|coords
operator|->
name|ytilt
argument_list|,
name|dt
argument_list|)
expr_stmt|;
block|}
name|mybrush
operator|->
name|private
operator|->
name|last_time
operator|=
name|time
expr_stmt|;
name|mypaint_surface_end_atomic
argument_list|(
operator|(
name|MyPaintSurface
operator|*
operator|)
name|mybrush
operator|->
name|private
operator|->
name|surface
argument_list|,
operator|&
name|rect
argument_list|)
expr_stmt|;
if|if
condition|(
name|rect
operator|.
name|width
operator|>
literal|0
operator|&&
name|rect
operator|.
name|height
operator|>
literal|0
condition|)
block|{
name|paint_core
operator|->
name|x1
operator|=
name|MIN
argument_list|(
name|paint_core
operator|->
name|x1
argument_list|,
name|rect
operator|.
name|x
argument_list|)
expr_stmt|;
name|paint_core
operator|->
name|y1
operator|=
name|MIN
argument_list|(
name|paint_core
operator|->
name|y1
argument_list|,
name|rect
operator|.
name|y
argument_list|)
expr_stmt|;
name|paint_core
operator|->
name|x2
operator|=
name|MAX
argument_list|(
name|paint_core
operator|->
name|x2
argument_list|,
name|rect
operator|.
name|x
operator|+
name|rect
operator|.
name|width
argument_list|)
expr_stmt|;
name|paint_core
operator|->
name|y2
operator|=
name|MAX
argument_list|(
name|paint_core
operator|->
name|y2
argument_list|,
name|rect
operator|.
name|y
operator|+
name|rect
operator|.
name|height
argument_list|)
expr_stmt|;
name|gimp_drawable_update
argument_list|(
name|drawable
argument_list|,
name|rect
operator|.
name|x
argument_list|,
name|rect
operator|.
name|y
argument_list|,
name|rect
operator|.
name|width
argument_list|,
name|rect
operator|.
name|height
argument_list|)
expr_stmt|;
block|}
block|}
end_function

begin_function
specifier|static
name|void
DECL|function|gimp_mybrush_core_create_brushes (GimpMybrushCore * mybrush,GimpDrawable * drawable,GimpPaintOptions * paint_options,GimpSymmetry * sym)
name|gimp_mybrush_core_create_brushes
parameter_list|(
name|GimpMybrushCore
modifier|*
name|mybrush
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
name|GimpMybrushOptions
modifier|*
name|options
init|=
name|GIMP_MYBRUSH_OPTIONS
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
name|GimpRGB
name|fg
decl_stmt|;
name|GimpHSV
name|hsv
decl_stmt|;
name|gint
name|n_strokes
decl_stmt|;
name|gint
name|i
decl_stmt|;
if|if
condition|(
name|mybrush
operator|->
name|private
operator|->
name|brushes
condition|)
block|{
name|g_list_free_full
argument_list|(
name|mybrush
operator|->
name|private
operator|->
name|brushes
argument_list|,
operator|(
name|GDestroyNotify
operator|)
name|mypaint_brush_unref
argument_list|)
expr_stmt|;
name|mybrush
operator|->
name|private
operator|->
name|brushes
operator|=
name|NULL
expr_stmt|;
block|}
if|if
condition|(
name|options
operator|->
name|eraser
condition|)
name|gimp_context_get_background
argument_list|(
name|context
argument_list|,
operator|&
name|fg
argument_list|)
expr_stmt|;
else|else
name|gimp_context_get_foreground
argument_list|(
name|context
argument_list|,
operator|&
name|fg
argument_list|)
expr_stmt|;
name|gimp_pickable_srgb_to_image_color
argument_list|(
name|GIMP_PICKABLE
argument_list|(
name|drawable
argument_list|)
argument_list|,
operator|&
name|fg
argument_list|,
operator|&
name|fg
argument_list|)
expr_stmt|;
name|gimp_rgb_to_hsv
argument_list|(
operator|&
name|fg
argument_list|,
operator|&
name|hsv
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
name|MyPaintBrush
modifier|*
name|brush
init|=
name|mypaint_brush_new
argument_list|()
decl_stmt|;
specifier|const
name|gchar
modifier|*
name|brush_data
decl_stmt|;
name|mypaint_brush_from_defaults
argument_list|(
name|brush
argument_list|)
expr_stmt|;
name|brush_data
operator|=
name|gimp_mybrush_get_brush_json
argument_list|(
name|mybrush
operator|->
name|private
operator|->
name|mybrush
argument_list|)
expr_stmt|;
if|if
condition|(
name|brush_data
condition|)
name|mypaint_brush_from_string
argument_list|(
name|brush
argument_list|,
name|brush_data
argument_list|)
expr_stmt|;
if|if
condition|(
operator|!
name|mypaint_brush_get_base_value
argument_list|(
name|brush
argument_list|,
name|MYPAINT_BRUSH_SETTING_RESTORE_COLOR
argument_list|)
condition|)
block|{
name|mypaint_brush_set_base_value
argument_list|(
name|brush
argument_list|,
name|MYPAINT_BRUSH_SETTING_COLOR_H
argument_list|,
name|hsv
operator|.
name|h
argument_list|)
expr_stmt|;
name|mypaint_brush_set_base_value
argument_list|(
name|brush
argument_list|,
name|MYPAINT_BRUSH_SETTING_COLOR_S
argument_list|,
name|hsv
operator|.
name|s
argument_list|)
expr_stmt|;
name|mypaint_brush_set_base_value
argument_list|(
name|brush
argument_list|,
name|MYPAINT_BRUSH_SETTING_COLOR_V
argument_list|,
name|hsv
operator|.
name|v
argument_list|)
expr_stmt|;
block|}
name|mypaint_brush_set_base_value
argument_list|(
name|brush
argument_list|,
name|MYPAINT_BRUSH_SETTING_RADIUS_LOGARITHMIC
argument_list|,
name|options
operator|->
name|radius
argument_list|)
expr_stmt|;
name|mypaint_brush_set_base_value
argument_list|(
name|brush
argument_list|,
name|MYPAINT_BRUSH_SETTING_OPAQUE
argument_list|,
name|options
operator|->
name|opaque
operator|*
name|gimp_context_get_opacity
argument_list|(
name|context
argument_list|)
argument_list|)
expr_stmt|;
name|mypaint_brush_set_base_value
argument_list|(
name|brush
argument_list|,
name|MYPAINT_BRUSH_SETTING_HARDNESS
argument_list|,
name|options
operator|->
name|hardness
argument_list|)
expr_stmt|;
name|mypaint_brush_set_base_value
argument_list|(
name|brush
argument_list|,
name|MYPAINT_BRUSH_SETTING_ERASER
argument_list|,
operator|(
name|options
operator|->
name|eraser
operator|&&
name|gimp_drawable_has_alpha
argument_list|(
name|drawable
argument_list|)
operator|)
condition|?
literal|1.0f
else|:
literal|0.0f
argument_list|)
expr_stmt|;
name|mypaint_brush_new_stroke
argument_list|(
name|brush
argument_list|)
expr_stmt|;
name|mybrush
operator|->
name|private
operator|->
name|brushes
operator|=
name|g_list_prepend
argument_list|(
name|mybrush
operator|->
name|private
operator|->
name|brushes
argument_list|,
name|brush
argument_list|)
expr_stmt|;
block|}
name|mybrush
operator|->
name|private
operator|->
name|brushes
operator|=
name|g_list_reverse
argument_list|(
name|mybrush
operator|->
name|private
operator|->
name|brushes
argument_list|)
expr_stmt|;
block|}
end_function

end_unit

