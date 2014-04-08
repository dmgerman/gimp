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
file|"libmypaint/mypaint-brush.h"
end_include

begin_include
include|#
directive|include
file|"libmypaint/mypaint-tiled-surface.h"
end_include

begin_include
include|#
directive|include
file|"libmypaint/gegl/mypaint-gegl-surface.h"
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
file|"core/gimpdrawable.h"
end_include

begin_include
include|#
directive|include
file|"core/gimpimage.h"
end_include

begin_include
include|#
directive|include
file|"core/gimpimage-undo.h"
end_include

begin_include
include|#
directive|include
file|"core/gimptempbuf.h"
end_include

begin_include
include|#
directive|include
file|"gimpmybrushoptions.h"
end_include

begin_include
include|#
directive|include
file|"gimpmybrush.h"
end_include

begin_include
include|#
directive|include
file|"gimp-intl.h"
end_include

begin_struct
DECL|struct|_GimpMybrushPrivate
struct|struct
name|_GimpMybrushPrivate
block|{
DECL|member|surface
name|MyPaintGeglTiledSurface
modifier|*
name|surface
decl_stmt|;
DECL|member|brush
name|MyPaintBrush
modifier|*
name|brush
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
name|gimp_mybrush_paint
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
name|gimp_mybrush_motion
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
name|guint32
name|time
parameter_list|)
function_decl|;
end_function_decl

begin_macro
DECL|function|G_DEFINE_TYPE (GimpMybrush,gimp_mybrush,GIMP_TYPE_PAINT_CORE)
name|G_DEFINE_TYPE
argument_list|(
argument|GimpMybrush
argument_list|,
argument|gimp_mybrush
argument_list|,
argument|GIMP_TYPE_PAINT_CORE
argument_list|)
end_macro

begin_define
DECL|macro|parent_class
define|#
directive|define
name|parent_class
value|gimp_mybrush_parent_class
end_define

begin_function
name|void
name|gimp_mybrush_register
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
name|GIMP_TYPE_MYBRUSH
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
literal|"gimp-tool-mybrush"
argument_list|)
expr_stmt|;
block|}
end_function

begin_function
specifier|static
name|void
DECL|function|gimp_mybrush_class_init (GimpMybrushClass * klass)
name|gimp_mybrush_class_init
parameter_list|(
name|GimpMybrushClass
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
name|gimp_mybrush_paint
expr_stmt|;
name|g_type_class_add_private
argument_list|(
name|klass
argument_list|,
sizeof|sizeof
argument_list|(
name|GimpMybrushPrivate
argument_list|)
argument_list|)
expr_stmt|;
block|}
end_function

begin_function
specifier|static
name|void
DECL|function|gimp_mybrush_init (GimpMybrush * mybrush)
name|gimp_mybrush_init
parameter_list|(
name|GimpMybrush
modifier|*
name|mybrush
parameter_list|)
block|{
name|mybrush
operator|->
name|private
operator|=
name|G_TYPE_INSTANCE_GET_PRIVATE
argument_list|(
name|mybrush
argument_list|,
name|GIMP_TYPE_MYBRUSH
argument_list|,
name|GimpMybrushPrivate
argument_list|)
expr_stmt|;
block|}
end_function

begin_function
specifier|static
name|void
DECL|function|gimp_mybrush_paint (GimpPaintCore * paint_core,GimpDrawable * drawable,GimpPaintOptions * paint_options,const GimpCoords * coords,GimpPaintState paint_state,guint32 time)
name|gimp_mybrush_paint
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
name|GimpMybrush
modifier|*
name|mybrush
init|=
name|GIMP_MYBRUSH
argument_list|(
name|paint_core
argument_list|)
decl_stmt|;
name|GimpMybrushOptions
modifier|*
name|options
init|=
name|GIMP_MYBRUSH_OPTIONS
argument_list|(
name|paint_options
argument_list|)
decl_stmt|;
name|GeglBuffer
modifier|*
name|buffer
decl_stmt|;
switch|switch
condition|(
name|paint_state
condition|)
block|{
case|case
name|GIMP_PAINT_STATE_INIT
case|:
name|mybrush
operator|->
name|private
operator|->
name|surface
operator|=
name|mypaint_gegl_tiled_surface_new
argument_list|()
expr_stmt|;
name|buffer
operator|=
name|mypaint_gegl_tiled_surface_get_buffer
argument_list|(
name|mybrush
operator|->
name|private
operator|->
name|surface
argument_list|)
expr_stmt|;
name|buffer
operator|=
name|gegl_buffer_new
argument_list|(
name|GEGL_RECTANGLE
argument_list|(
literal|0
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
argument_list|,
name|gimp_item_get_height
argument_list|(
name|GIMP_ITEM
argument_list|(
name|drawable
argument_list|)
argument_list|)
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
name|gimp_drawable_get_buffer
argument_list|(
name|drawable
argument_list|)
argument_list|,
name|NULL
argument_list|,
name|buffer
argument_list|,
name|NULL
argument_list|)
expr_stmt|;
name|mypaint_gegl_tiled_surface_set_buffer
argument_list|(
name|mybrush
operator|->
name|private
operator|->
name|surface
argument_list|,
name|buffer
argument_list|)
expr_stmt|;
name|g_object_unref
argument_list|(
name|buffer
argument_list|)
expr_stmt|;
name|mybrush
operator|->
name|private
operator|->
name|brush
operator|=
name|mypaint_brush_new
argument_list|()
expr_stmt|;
name|mypaint_brush_from_defaults
argument_list|(
name|mybrush
operator|->
name|private
operator|->
name|brush
argument_list|)
expr_stmt|;
if|if
condition|(
name|options
operator|->
name|mybrush
condition|)
block|{
name|gchar
modifier|*
name|string
decl_stmt|;
name|gsize
name|length
decl_stmt|;
if|if
condition|(
name|g_file_get_contents
argument_list|(
name|options
operator|->
name|mybrush
argument_list|,
operator|&
name|string
argument_list|,
operator|&
name|length
argument_list|,
name|NULL
argument_list|)
condition|)
block|{
if|if
condition|(
operator|!
name|mypaint_brush_from_string
argument_list|(
name|mybrush
operator|->
name|private
operator|->
name|brush
argument_list|,
name|string
argument_list|)
condition|)
name|g_printerr
argument_list|(
literal|"Failed to deserialize MyPaint brush\n"
argument_list|)
expr_stmt|;
name|g_free
argument_list|(
name|string
argument_list|)
expr_stmt|;
block|}
block|}
name|mypaint_brush_new_stroke
argument_list|(
name|mybrush
operator|->
name|private
operator|->
name|brush
argument_list|)
expr_stmt|;
break|break;
case|case
name|GIMP_PAINT_STATE_MOTION
case|:
name|gimp_mybrush_motion
argument_list|(
name|paint_core
argument_list|,
name|drawable
argument_list|,
name|paint_options
argument_list|,
name|coords
argument_list|,
name|time
argument_list|)
expr_stmt|;
break|break;
case|case
name|GIMP_PAINT_STATE_FINISH
case|:
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
name|mypaint_brush_unref
argument_list|(
name|mybrush
operator|->
name|private
operator|->
name|brush
argument_list|)
expr_stmt|;
name|mybrush
operator|->
name|private
operator|->
name|brush
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
DECL|function|gimp_mybrush_motion (GimpPaintCore * paint_core,GimpDrawable * drawable,GimpPaintOptions * paint_options,const GimpCoords * coords,guint32 time)
name|gimp_mybrush_motion
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
name|guint32
name|time
parameter_list|)
block|{
name|GimpMybrush
modifier|*
name|mybrush
init|=
name|GIMP_MYBRUSH
argument_list|(
name|paint_core
argument_list|)
decl_stmt|;
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
name|GimpComponentMask
name|active_mask
decl_stmt|;
name|GimpRGB
name|fg
decl_stmt|;
name|GimpHSV
name|hsv
decl_stmt|;
name|MyPaintRectangle
name|rect
decl_stmt|;
name|active_mask
operator|=
name|gimp_drawable_get_active_mask
argument_list|(
name|drawable
argument_list|)
expr_stmt|;
name|mypaint_brush_set_base_value
argument_list|(
name|mybrush
operator|->
name|private
operator|->
name|brush
argument_list|,
name|MYPAINT_BRUSH_SETTING_LOCK_ALPHA
argument_list|,
operator|(
name|active_mask
operator|&
name|GIMP_COMPONENT_ALPHA
operator|)
condition|?
name|FALSE
else|:
name|TRUE
argument_list|)
expr_stmt|;
name|gimp_context_get_foreground
argument_list|(
name|context
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
name|mypaint_brush_set_base_value
argument_list|(
name|mybrush
operator|->
name|private
operator|->
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
name|mybrush
operator|->
name|private
operator|->
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
name|mybrush
operator|->
name|private
operator|->
name|brush
argument_list|,
name|MYPAINT_BRUSH_SETTING_COLOR_V
argument_list|,
name|hsv
operator|.
name|v
argument_list|)
expr_stmt|;
name|mypaint_brush_set_base_value
argument_list|(
name|mybrush
operator|->
name|private
operator|->
name|brush
argument_list|,
name|MYPAINT_BRUSH_SETTING_OPAQUE
argument_list|,
name|gimp_context_get_opacity
argument_list|(
name|context
argument_list|)
argument_list|)
expr_stmt|;
name|mypaint_brush_set_base_value
argument_list|(
name|mybrush
operator|->
name|private
operator|->
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
name|mybrush
operator|->
name|private
operator|->
name|brush
argument_list|,
name|MYPAINT_BRUSH_SETTING_HARDNESS
argument_list|,
name|options
operator|->
name|hardness
argument_list|)
expr_stmt|;
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
name|mypaint_brush_stroke_to
argument_list|(
name|mybrush
operator|->
name|private
operator|->
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
name|coords
operator|->
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
literal|1
argument_list|)
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
name|g_printerr
argument_list|(
literal|"painted rect: %d %d %d %d\n"
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
name|GeglBuffer
modifier|*
name|src
decl_stmt|;
name|src
operator|=
name|mypaint_gegl_tiled_surface_get_buffer
argument_list|(
name|mybrush
operator|->
name|private
operator|->
name|surface
argument_list|)
expr_stmt|;
name|gegl_buffer_copy
argument_list|(
name|src
argument_list|,
operator|(
name|GeglRectangle
operator|*
operator|)
operator|&
name|rect
argument_list|,
name|gimp_drawable_get_buffer
argument_list|(
name|drawable
argument_list|)
argument_list|,
name|NULL
argument_list|)
expr_stmt|;
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

end_unit

