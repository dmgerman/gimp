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
file|"core/gimperror.h"
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
file|"gimpsourcecore.h"
end_include

begin_include
include|#
directive|include
file|"gimpsourceoptions.h"
end_include

begin_include
include|#
directive|include
file|"gimp-intl.h"
end_include

begin_enum
enum|enum
DECL|enum|__anon27b9024f0103
block|{
DECL|enumerator|PROP_0
name|PROP_0
block|,
DECL|enumerator|PROP_SRC_DRAWABLE
name|PROP_SRC_DRAWABLE
block|,
DECL|enumerator|PROP_SRC_X
name|PROP_SRC_X
block|,
DECL|enumerator|PROP_SRC_Y
name|PROP_SRC_Y
block|}
enum|;
end_enum

begin_function_decl
specifier|static
name|void
name|gimp_source_core_set_property
parameter_list|(
name|GObject
modifier|*
name|object
parameter_list|,
name|guint
name|property_id
parameter_list|,
specifier|const
name|GValue
modifier|*
name|value
parameter_list|,
name|GParamSpec
modifier|*
name|pspec
parameter_list|)
function_decl|;
end_function_decl

begin_function_decl
specifier|static
name|void
name|gimp_source_core_get_property
parameter_list|(
name|GObject
modifier|*
name|object
parameter_list|,
name|guint
name|property_id
parameter_list|,
name|GValue
modifier|*
name|value
parameter_list|,
name|GParamSpec
modifier|*
name|pspec
parameter_list|)
function_decl|;
end_function_decl

begin_function_decl
specifier|static
name|gboolean
name|gimp_source_core_start
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
name|gimp_source_core_paint
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

begin_if
if|#
directive|if
literal|0
end_if

begin_endif
unit|static void     gimp_source_core_motion          (GimpSourceCore    *source_core,                                                   GimpDrawable      *drawable,                                                   GimpPaintOptions  *paint_options,                                                   GimpSymmetry      *sym);
endif|#
directive|endif
end_endif

begin_function_decl
specifier|static
name|gboolean
name|gimp_source_core_real_use_source
parameter_list|(
name|GimpSourceCore
modifier|*
name|source_core
parameter_list|,
name|GimpSourceOptions
modifier|*
name|options
parameter_list|)
function_decl|;
end_function_decl

begin_function_decl
specifier|static
name|GeglBuffer
modifier|*
name|gimp_source_core_real_get_source
parameter_list|(
name|GimpSourceCore
modifier|*
name|source_core
parameter_list|,
name|GimpDrawable
modifier|*
name|drawable
parameter_list|,
name|GimpPaintOptions
modifier|*
name|paint_options
parameter_list|,
name|GimpPickable
modifier|*
name|src_pickable
parameter_list|,
name|gint
name|src_offset_x
parameter_list|,
name|gint
name|src_offset_y
parameter_list|,
name|GeglBuffer
modifier|*
name|paint_buffer
parameter_list|,
name|gint
name|paint_buffer_x
parameter_list|,
name|gint
name|paint_buffer_y
parameter_list|,
name|gint
modifier|*
name|paint_area_offset_x
parameter_list|,
name|gint
modifier|*
name|paint_area_offset_y
parameter_list|,
name|gint
modifier|*
name|paint_area_width
parameter_list|,
name|gint
modifier|*
name|paint_area_height
parameter_list|,
name|GeglRectangle
modifier|*
name|src_rect
parameter_list|)
function_decl|;
end_function_decl

begin_function_decl
specifier|static
name|void
name|gimp_source_core_set_src_drawable
parameter_list|(
name|GimpSourceCore
modifier|*
name|source_core
parameter_list|,
name|GimpDrawable
modifier|*
name|drawable
parameter_list|)
function_decl|;
end_function_decl

begin_macro
DECL|function|G_DEFINE_TYPE (GimpSourceCore,gimp_source_core,GIMP_TYPE_BRUSH_CORE)
name|G_DEFINE_TYPE
argument_list|(
argument|GimpSourceCore
argument_list|,
argument|gimp_source_core
argument_list|,
argument|GIMP_TYPE_BRUSH_CORE
argument_list|)
end_macro

begin_define
DECL|macro|parent_class
define|#
directive|define
name|parent_class
value|gimp_source_core_parent_class
end_define

begin_function
specifier|static
name|void
name|gimp_source_core_class_init
parameter_list|(
name|GimpSourceCoreClass
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
name|set_property
operator|=
name|gimp_source_core_set_property
expr_stmt|;
name|object_class
operator|->
name|get_property
operator|=
name|gimp_source_core_get_property
expr_stmt|;
name|paint_core_class
operator|->
name|start
operator|=
name|gimp_source_core_start
expr_stmt|;
name|paint_core_class
operator|->
name|paint
operator|=
name|gimp_source_core_paint
expr_stmt|;
name|brush_core_class
operator|->
name|handles_changing_brush
operator|=
name|TRUE
expr_stmt|;
name|klass
operator|->
name|use_source
operator|=
name|gimp_source_core_real_use_source
expr_stmt|;
name|klass
operator|->
name|get_source
operator|=
name|gimp_source_core_real_get_source
expr_stmt|;
name|klass
operator|->
name|motion
operator|=
name|NULL
expr_stmt|;
name|g_object_class_install_property
argument_list|(
name|object_class
argument_list|,
name|PROP_SRC_DRAWABLE
argument_list|,
name|g_param_spec_object
argument_list|(
literal|"src-drawable"
argument_list|,
name|NULL
argument_list|,
name|NULL
argument_list|,
name|GIMP_TYPE_DRAWABLE
argument_list|,
name|GIMP_PARAM_READWRITE
argument_list|)
argument_list|)
expr_stmt|;
name|g_object_class_install_property
argument_list|(
name|object_class
argument_list|,
name|PROP_SRC_X
argument_list|,
name|g_param_spec_int
argument_list|(
literal|"src-x"
argument_list|,
name|NULL
argument_list|,
name|NULL
argument_list|,
literal|0
argument_list|,
name|GIMP_MAX_IMAGE_SIZE
argument_list|,
literal|0
argument_list|,
name|GIMP_PARAM_READWRITE
argument_list|)
argument_list|)
expr_stmt|;
name|g_object_class_install_property
argument_list|(
name|object_class
argument_list|,
name|PROP_SRC_Y
argument_list|,
name|g_param_spec_int
argument_list|(
literal|"src-y"
argument_list|,
name|NULL
argument_list|,
name|NULL
argument_list|,
literal|0
argument_list|,
name|GIMP_MAX_IMAGE_SIZE
argument_list|,
literal|0
argument_list|,
name|GIMP_PARAM_READWRITE
argument_list|)
argument_list|)
expr_stmt|;
block|}
end_function

begin_function
specifier|static
name|void
DECL|function|gimp_source_core_init (GimpSourceCore * source_core)
name|gimp_source_core_init
parameter_list|(
name|GimpSourceCore
modifier|*
name|source_core
parameter_list|)
block|{
name|source_core
operator|->
name|set_source
operator|=
name|FALSE
expr_stmt|;
name|source_core
operator|->
name|src_drawable
operator|=
name|NULL
expr_stmt|;
name|source_core
operator|->
name|src_x
operator|=
literal|0
expr_stmt|;
name|source_core
operator|->
name|src_y
operator|=
literal|0
expr_stmt|;
name|source_core
operator|->
name|orig_src_x
operator|=
literal|0
expr_stmt|;
name|source_core
operator|->
name|orig_src_y
operator|=
literal|0
expr_stmt|;
name|source_core
operator|->
name|offset_x
operator|=
literal|0
expr_stmt|;
name|source_core
operator|->
name|offset_y
operator|=
literal|0
expr_stmt|;
name|source_core
operator|->
name|first_stroke
operator|=
name|TRUE
expr_stmt|;
block|}
end_function

begin_function
specifier|static
name|void
DECL|function|gimp_source_core_set_property (GObject * object,guint property_id,const GValue * value,GParamSpec * pspec)
name|gimp_source_core_set_property
parameter_list|(
name|GObject
modifier|*
name|object
parameter_list|,
name|guint
name|property_id
parameter_list|,
specifier|const
name|GValue
modifier|*
name|value
parameter_list|,
name|GParamSpec
modifier|*
name|pspec
parameter_list|)
block|{
name|GimpSourceCore
modifier|*
name|source_core
init|=
name|GIMP_SOURCE_CORE
argument_list|(
name|object
argument_list|)
decl_stmt|;
switch|switch
condition|(
name|property_id
condition|)
block|{
case|case
name|PROP_SRC_DRAWABLE
case|:
name|gimp_source_core_set_src_drawable
argument_list|(
name|source_core
argument_list|,
name|g_value_get_object
argument_list|(
name|value
argument_list|)
argument_list|)
expr_stmt|;
break|break;
case|case
name|PROP_SRC_X
case|:
name|source_core
operator|->
name|src_x
operator|=
name|g_value_get_int
argument_list|(
name|value
argument_list|)
expr_stmt|;
break|break;
case|case
name|PROP_SRC_Y
case|:
name|source_core
operator|->
name|src_y
operator|=
name|g_value_get_int
argument_list|(
name|value
argument_list|)
expr_stmt|;
break|break;
default|default:
name|G_OBJECT_WARN_INVALID_PROPERTY_ID
argument_list|(
name|object
argument_list|,
name|property_id
argument_list|,
name|pspec
argument_list|)
expr_stmt|;
break|break;
block|}
block|}
end_function

begin_function
specifier|static
name|void
DECL|function|gimp_source_core_get_property (GObject * object,guint property_id,GValue * value,GParamSpec * pspec)
name|gimp_source_core_get_property
parameter_list|(
name|GObject
modifier|*
name|object
parameter_list|,
name|guint
name|property_id
parameter_list|,
name|GValue
modifier|*
name|value
parameter_list|,
name|GParamSpec
modifier|*
name|pspec
parameter_list|)
block|{
name|GimpSourceCore
modifier|*
name|source_core
init|=
name|GIMP_SOURCE_CORE
argument_list|(
name|object
argument_list|)
decl_stmt|;
switch|switch
condition|(
name|property_id
condition|)
block|{
case|case
name|PROP_SRC_DRAWABLE
case|:
name|g_value_set_object
argument_list|(
name|value
argument_list|,
name|source_core
operator|->
name|src_drawable
argument_list|)
expr_stmt|;
break|break;
case|case
name|PROP_SRC_X
case|:
name|g_value_set_int
argument_list|(
name|value
argument_list|,
name|source_core
operator|->
name|src_x
argument_list|)
expr_stmt|;
break|break;
case|case
name|PROP_SRC_Y
case|:
name|g_value_set_int
argument_list|(
name|value
argument_list|,
name|source_core
operator|->
name|src_y
argument_list|)
expr_stmt|;
break|break;
default|default:
name|G_OBJECT_WARN_INVALID_PROPERTY_ID
argument_list|(
name|object
argument_list|,
name|property_id
argument_list|,
name|pspec
argument_list|)
expr_stmt|;
break|break;
block|}
block|}
end_function

begin_function
specifier|static
name|gboolean
DECL|function|gimp_source_core_start (GimpPaintCore * paint_core,GimpDrawable * drawable,GimpPaintOptions * paint_options,const GimpCoords * coords,GError ** error)
name|gimp_source_core_start
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
name|GimpSourceCore
modifier|*
name|source_core
init|=
name|GIMP_SOURCE_CORE
argument_list|(
name|paint_core
argument_list|)
decl_stmt|;
name|GimpSourceOptions
modifier|*
name|options
init|=
name|GIMP_SOURCE_OPTIONS
argument_list|(
name|paint_options
argument_list|)
decl_stmt|;
if|if
condition|(
operator|!
name|GIMP_PAINT_CORE_CLASS
argument_list|(
name|parent_class
argument_list|)
operator|->
name|start
argument_list|(
name|paint_core
argument_list|,
name|drawable
argument_list|,
name|paint_options
argument_list|,
name|coords
argument_list|,
name|error
argument_list|)
condition|)
block|{
return|return
name|FALSE
return|;
block|}
name|paint_core
operator|->
name|use_saved_proj
operator|=
name|FALSE
expr_stmt|;
if|if
condition|(
operator|!
name|source_core
operator|->
name|set_source
operator|&&
name|gimp_source_core_use_source
argument_list|(
name|source_core
argument_list|,
name|options
argument_list|)
condition|)
block|{
if|if
condition|(
operator|!
name|source_core
operator|->
name|src_drawable
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
literal|"Set a source image first."
argument_list|)
argument_list|)
expr_stmt|;
return|return
name|FALSE
return|;
block|}
if|if
condition|(
name|options
operator|->
name|sample_merged
operator|&&
name|gimp_item_get_image
argument_list|(
name|GIMP_ITEM
argument_list|(
name|source_core
operator|->
name|src_drawable
argument_list|)
argument_list|)
operator|==
name|gimp_item_get_image
argument_list|(
name|GIMP_ITEM
argument_list|(
name|drawable
argument_list|)
argument_list|)
condition|)
block|{
name|paint_core
operator|->
name|use_saved_proj
operator|=
name|TRUE
expr_stmt|;
block|}
block|}
return|return
name|TRUE
return|;
block|}
end_function

begin_function
specifier|static
name|void
DECL|function|gimp_source_core_paint (GimpPaintCore * paint_core,GimpDrawable * drawable,GimpPaintOptions * paint_options,GimpSymmetry * sym,GimpPaintState paint_state,guint32 time)
name|gimp_source_core_paint
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
name|GimpSourceCore
modifier|*
name|source_core
init|=
name|GIMP_SOURCE_CORE
argument_list|(
name|paint_core
argument_list|)
decl_stmt|;
name|GimpSourceOptions
modifier|*
name|options
init|=
name|GIMP_SOURCE_OPTIONS
argument_list|(
name|paint_options
argument_list|)
decl_stmt|;
specifier|const
name|GimpCoords
modifier|*
name|coords
decl_stmt|;
comment|/* The source is based on the original stroke */
name|coords
operator|=
name|gimp_symmetry_get_origin
argument_list|(
name|sym
argument_list|)
expr_stmt|;
switch|switch
condition|(
name|paint_state
condition|)
block|{
case|case
name|GIMP_PAINT_STATE_INIT
case|:
if|if
condition|(
name|source_core
operator|->
name|set_source
condition|)
block|{
name|gimp_source_core_set_src_drawable
argument_list|(
name|source_core
argument_list|,
name|drawable
argument_list|)
expr_stmt|;
comment|/* FIXME(?): subpixel source sampling */
name|source_core
operator|->
name|src_x
operator|=
name|floor
argument_list|(
name|coords
operator|->
name|x
argument_list|)
expr_stmt|;
name|source_core
operator|->
name|src_y
operator|=
name|floor
argument_list|(
name|coords
operator|->
name|y
argument_list|)
expr_stmt|;
name|source_core
operator|->
name|first_stroke
operator|=
name|TRUE
expr_stmt|;
block|}
elseif|else
if|if
condition|(
name|options
operator|->
name|align_mode
operator|==
name|GIMP_SOURCE_ALIGN_NO
condition|)
block|{
name|source_core
operator|->
name|orig_src_x
operator|=
name|source_core
operator|->
name|src_x
expr_stmt|;
name|source_core
operator|->
name|orig_src_y
operator|=
name|source_core
operator|->
name|src_y
expr_stmt|;
name|source_core
operator|->
name|first_stroke
operator|=
name|TRUE
expr_stmt|;
block|}
break|break;
case|case
name|GIMP_PAINT_STATE_MOTION
case|:
if|if
condition|(
name|source_core
operator|->
name|set_source
condition|)
block|{
comment|/*  If the control key is down, move the src target and return */
name|source_core
operator|->
name|src_x
operator|=
name|floor
argument_list|(
name|coords
operator|->
name|x
argument_list|)
expr_stmt|;
name|source_core
operator|->
name|src_y
operator|=
name|floor
argument_list|(
name|coords
operator|->
name|y
argument_list|)
expr_stmt|;
name|source_core
operator|->
name|first_stroke
operator|=
name|TRUE
expr_stmt|;
block|}
else|else
block|{
comment|/*  otherwise, update the target  */
name|gint
name|dest_x
decl_stmt|;
name|gint
name|dest_y
decl_stmt|;
name|dest_x
operator|=
name|floor
argument_list|(
name|coords
operator|->
name|x
argument_list|)
expr_stmt|;
name|dest_y
operator|=
name|floor
argument_list|(
name|coords
operator|->
name|y
argument_list|)
expr_stmt|;
if|if
condition|(
name|options
operator|->
name|align_mode
operator|==
name|GIMP_SOURCE_ALIGN_REGISTERED
condition|)
block|{
name|source_core
operator|->
name|offset_x
operator|=
literal|0
expr_stmt|;
name|source_core
operator|->
name|offset_y
operator|=
literal|0
expr_stmt|;
block|}
elseif|else
if|if
condition|(
name|options
operator|->
name|align_mode
operator|==
name|GIMP_SOURCE_ALIGN_FIXED
condition|)
block|{
name|source_core
operator|->
name|offset_x
operator|=
name|source_core
operator|->
name|src_x
operator|-
name|dest_x
expr_stmt|;
name|source_core
operator|->
name|offset_y
operator|=
name|source_core
operator|->
name|src_y
operator|-
name|dest_y
expr_stmt|;
block|}
elseif|else
if|if
condition|(
name|source_core
operator|->
name|first_stroke
condition|)
block|{
name|source_core
operator|->
name|offset_x
operator|=
name|source_core
operator|->
name|src_x
operator|-
name|dest_x
expr_stmt|;
name|source_core
operator|->
name|offset_y
operator|=
name|source_core
operator|->
name|src_y
operator|-
name|dest_y
expr_stmt|;
name|source_core
operator|->
name|first_stroke
operator|=
name|FALSE
expr_stmt|;
block|}
name|source_core
operator|->
name|src_x
operator|=
name|dest_x
operator|+
name|source_core
operator|->
name|offset_x
expr_stmt|;
name|source_core
operator|->
name|src_y
operator|=
name|dest_y
operator|+
name|source_core
operator|->
name|offset_y
expr_stmt|;
name|gimp_source_core_motion
argument_list|(
name|source_core
argument_list|,
name|drawable
argument_list|,
name|paint_options
argument_list|,
name|sym
argument_list|)
expr_stmt|;
block|}
break|break;
case|case
name|GIMP_PAINT_STATE_FINISH
case|:
if|if
condition|(
name|options
operator|->
name|align_mode
operator|==
name|GIMP_SOURCE_ALIGN_NO
operator|&&
operator|!
name|source_core
operator|->
name|first_stroke
condition|)
block|{
name|source_core
operator|->
name|src_x
operator|=
name|source_core
operator|->
name|orig_src_x
expr_stmt|;
name|source_core
operator|->
name|src_y
operator|=
name|source_core
operator|->
name|orig_src_y
expr_stmt|;
block|}
break|break;
default|default:
break|break;
block|}
name|g_object_notify
argument_list|(
name|G_OBJECT
argument_list|(
name|source_core
argument_list|)
argument_list|,
literal|"src-x"
argument_list|)
expr_stmt|;
name|g_object_notify
argument_list|(
name|G_OBJECT
argument_list|(
name|source_core
argument_list|)
argument_list|,
literal|"src-y"
argument_list|)
expr_stmt|;
block|}
end_function

begin_function
name|void
DECL|function|gimp_source_core_motion (GimpSourceCore * source_core,GimpDrawable * drawable,GimpPaintOptions * paint_options,GimpSymmetry * sym)
name|gimp_source_core_motion
parameter_list|(
name|GimpSourceCore
modifier|*
name|source_core
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
name|GimpPaintCore
modifier|*
name|paint_core
init|=
name|GIMP_PAINT_CORE
argument_list|(
name|source_core
argument_list|)
decl_stmt|;
name|GimpSourceOptions
modifier|*
name|options
init|=
name|GIMP_SOURCE_OPTIONS
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
name|GimpPickable
modifier|*
name|src_pickable
init|=
name|NULL
decl_stmt|;
name|GeglBuffer
modifier|*
name|src_buffer
init|=
name|NULL
decl_stmt|;
name|GeglRectangle
name|src_rect
decl_stmt|;
name|gint
name|base_src_offset_x
decl_stmt|;
name|gint
name|base_src_offset_y
decl_stmt|;
name|gint
name|src_offset_x
decl_stmt|;
name|gint
name|src_offset_y
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
name|paint_area_offset_x
decl_stmt|;
name|gint
name|paint_area_offset_y
decl_stmt|;
name|gint
name|paint_area_width
decl_stmt|;
name|gint
name|paint_area_height
decl_stmt|;
name|gdouble
name|fade_point
decl_stmt|;
name|gdouble
name|opacity
decl_stmt|;
name|GimpLayerMode
name|paint_mode
decl_stmt|;
name|GeglNode
modifier|*
name|op
decl_stmt|;
name|GimpCoords
modifier|*
name|origin
decl_stmt|;
name|GimpCoords
modifier|*
name|coords
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
name|origin
operator|=
name|gimp_symmetry_get_origin
argument_list|(
name|sym
argument_list|)
expr_stmt|;
comment|/* Some settings are based on the original stroke. */
name|opacity
operator|=
name|gimp_dynamics_get_linear_value
argument_list|(
name|dynamics
argument_list|,
name|GIMP_DYNAMICS_OUTPUT_OPACITY
argument_list|,
name|origin
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
name|base_src_offset_x
operator|=
name|source_core
operator|->
name|offset_x
expr_stmt|;
name|base_src_offset_y
operator|=
name|source_core
operator|->
name|offset_y
expr_stmt|;
if|if
condition|(
name|gimp_source_core_use_source
argument_list|(
name|source_core
argument_list|,
name|options
argument_list|)
condition|)
block|{
name|src_pickable
operator|=
name|GIMP_PICKABLE
argument_list|(
name|source_core
operator|->
name|src_drawable
argument_list|)
expr_stmt|;
if|if
condition|(
name|options
operator|->
name|sample_merged
condition|)
block|{
name|GimpImage
modifier|*
name|src_image
init|=
name|gimp_pickable_get_image
argument_list|(
name|src_pickable
argument_list|)
decl_stmt|;
name|gint
name|off_x
decl_stmt|,
name|off_y
decl_stmt|;
name|src_pickable
operator|=
name|GIMP_PICKABLE
argument_list|(
name|src_image
argument_list|)
expr_stmt|;
name|gimp_item_get_offset
argument_list|(
name|GIMP_ITEM
argument_list|(
name|source_core
operator|->
name|src_drawable
argument_list|)
argument_list|,
operator|&
name|off_x
argument_list|,
operator|&
name|off_y
argument_list|)
expr_stmt|;
name|base_src_offset_x
operator|+=
name|off_x
expr_stmt|;
name|base_src_offset_y
operator|+=
name|off_y
expr_stmt|;
block|}
block|}
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
name|origin
argument_list|)
expr_stmt|;
name|paint_mode
operator|=
name|gimp_context_get_paint_mode
argument_list|(
name|GIMP_CONTEXT
argument_list|(
name|paint_options
argument_list|)
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
name|paint_mode
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
name|paint_area_offset_x
operator|=
literal|0
expr_stmt|;
name|paint_area_offset_y
operator|=
literal|0
expr_stmt|;
name|paint_area_width
operator|=
name|gegl_buffer_get_width
argument_list|(
name|paint_buffer
argument_list|)
expr_stmt|;
name|paint_area_height
operator|=
name|gegl_buffer_get_height
argument_list|(
name|paint_buffer
argument_list|)
expr_stmt|;
name|src_offset_x
operator|=
name|base_src_offset_x
expr_stmt|;
name|src_offset_y
operator|=
name|base_src_offset_y
expr_stmt|;
if|if
condition|(
name|gimp_source_core_use_source
argument_list|(
name|source_core
argument_list|,
name|options
argument_list|)
condition|)
block|{
comment|/* When using a source, use the same for every stroke. */
name|src_offset_x
operator|+=
name|floor
argument_list|(
name|origin
operator|->
name|x
argument_list|)
operator|-
name|floor
argument_list|(
name|coords
operator|->
name|x
argument_list|)
expr_stmt|;
name|src_offset_y
operator|+=
name|floor
argument_list|(
name|origin
operator|->
name|y
argument_list|)
operator|-
name|floor
argument_list|(
name|coords
operator|->
name|y
argument_list|)
expr_stmt|;
name|src_buffer
operator|=
name|GIMP_SOURCE_CORE_GET_CLASS
argument_list|(
name|source_core
argument_list|)
operator|->
name|get_source
argument_list|(
name|source_core
argument_list|,
name|drawable
argument_list|,
name|paint_options
argument_list|,
name|src_pickable
argument_list|,
name|src_offset_x
argument_list|,
name|src_offset_y
argument_list|,
name|paint_buffer
argument_list|,
name|paint_buffer_x
argument_list|,
name|paint_buffer_y
argument_list|,
operator|&
name|paint_area_offset_x
argument_list|,
operator|&
name|paint_area_offset_y
argument_list|,
operator|&
name|paint_area_width
argument_list|,
operator|&
name|paint_area_height
argument_list|,
operator|&
name|src_rect
argument_list|)
expr_stmt|;
if|if
condition|(
operator|!
name|src_buffer
condition|)
continue|continue;
block|}
comment|/*  Set the paint buffer to transparent  */
name|gegl_buffer_clear
argument_list|(
name|paint_buffer
argument_list|,
name|NULL
argument_list|)
expr_stmt|;
name|op
operator|=
name|gimp_symmetry_get_operation
argument_list|(
name|sym
argument_list|,
name|i
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
expr_stmt|;
name|GIMP_SOURCE_CORE_GET_CLASS
argument_list|(
name|source_core
argument_list|)
operator|->
name|motion
argument_list|(
name|source_core
argument_list|,
name|drawable
argument_list|,
name|paint_options
argument_list|,
name|coords
argument_list|,
name|op
argument_list|,
name|opacity
argument_list|,
name|src_pickable
argument_list|,
name|src_buffer
argument_list|,
operator|&
name|src_rect
argument_list|,
name|src_offset_x
argument_list|,
name|src_offset_y
argument_list|,
name|paint_buffer
argument_list|,
name|paint_buffer_x
argument_list|,
name|paint_buffer_y
argument_list|,
name|paint_area_offset_x
argument_list|,
name|paint_area_offset_y
argument_list|,
name|paint_area_width
argument_list|,
name|paint_area_height
argument_list|)
expr_stmt|;
if|if
condition|(
name|src_buffer
condition|)
name|g_object_unref
argument_list|(
name|src_buffer
argument_list|)
expr_stmt|;
block|}
block|}
end_function

begin_function
name|gboolean
DECL|function|gimp_source_core_use_source (GimpSourceCore * source_core,GimpSourceOptions * options)
name|gimp_source_core_use_source
parameter_list|(
name|GimpSourceCore
modifier|*
name|source_core
parameter_list|,
name|GimpSourceOptions
modifier|*
name|options
parameter_list|)
block|{
return|return
name|GIMP_SOURCE_CORE_GET_CLASS
argument_list|(
name|source_core
argument_list|)
operator|->
name|use_source
argument_list|(
name|source_core
argument_list|,
name|options
argument_list|)
return|;
block|}
end_function

begin_function
specifier|static
name|gboolean
DECL|function|gimp_source_core_real_use_source (GimpSourceCore * source_core,GimpSourceOptions * options)
name|gimp_source_core_real_use_source
parameter_list|(
name|GimpSourceCore
modifier|*
name|source_core
parameter_list|,
name|GimpSourceOptions
modifier|*
name|options
parameter_list|)
block|{
return|return
name|TRUE
return|;
block|}
end_function

begin_function
specifier|static
name|GeglBuffer
modifier|*
DECL|function|gimp_source_core_real_get_source (GimpSourceCore * source_core,GimpDrawable * drawable,GimpPaintOptions * paint_options,GimpPickable * src_pickable,gint src_offset_x,gint src_offset_y,GeglBuffer * paint_buffer,gint paint_buffer_x,gint paint_buffer_y,gint * paint_area_offset_x,gint * paint_area_offset_y,gint * paint_area_width,gint * paint_area_height,GeglRectangle * src_rect)
name|gimp_source_core_real_get_source
parameter_list|(
name|GimpSourceCore
modifier|*
name|source_core
parameter_list|,
name|GimpDrawable
modifier|*
name|drawable
parameter_list|,
name|GimpPaintOptions
modifier|*
name|paint_options
parameter_list|,
name|GimpPickable
modifier|*
name|src_pickable
parameter_list|,
name|gint
name|src_offset_x
parameter_list|,
name|gint
name|src_offset_y
parameter_list|,
name|GeglBuffer
modifier|*
name|paint_buffer
parameter_list|,
name|gint
name|paint_buffer_x
parameter_list|,
name|gint
name|paint_buffer_y
parameter_list|,
name|gint
modifier|*
name|paint_area_offset_x
parameter_list|,
name|gint
modifier|*
name|paint_area_offset_y
parameter_list|,
name|gint
modifier|*
name|paint_area_width
parameter_list|,
name|gint
modifier|*
name|paint_area_height
parameter_list|,
name|GeglRectangle
modifier|*
name|src_rect
parameter_list|)
block|{
name|GimpSourceOptions
modifier|*
name|options
init|=
name|GIMP_SOURCE_OPTIONS
argument_list|(
name|paint_options
argument_list|)
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
name|GimpImage
modifier|*
name|src_image
init|=
name|gimp_pickable_get_image
argument_list|(
name|src_pickable
argument_list|)
decl_stmt|;
name|GeglBuffer
modifier|*
name|src_buffer
init|=
name|gimp_pickable_get_buffer
argument_list|(
name|src_pickable
argument_list|)
decl_stmt|;
name|GeglBuffer
modifier|*
name|dest_buffer
decl_stmt|;
name|gint
name|x
decl_stmt|,
name|y
decl_stmt|;
name|gint
name|width
decl_stmt|,
name|height
decl_stmt|;
if|if
condition|(
operator|!
name|gimp_rectangle_intersect
argument_list|(
name|paint_buffer_x
operator|+
name|src_offset_x
argument_list|,
name|paint_buffer_y
operator|+
name|src_offset_y
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
argument_list|,
literal|0
argument_list|,
literal|0
argument_list|,
name|gegl_buffer_get_width
argument_list|(
name|src_buffer
argument_list|)
argument_list|,
name|gegl_buffer_get_height
argument_list|(
name|src_buffer
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
block|{
return|return
name|FALSE
return|;
block|}
comment|/*  If the source image is different from the destination,    *  then we should copy straight from the source image    *  to the canvas.    *  Otherwise, we need a call to get_orig_image to make sure    *  we get a copy of the unblemished (offset) image    */
if|if
condition|(
operator|(
name|options
operator|->
name|sample_merged
operator|&&
operator|(
name|src_image
operator|!=
name|image
operator|)
operator|)
operator|||
operator|(
operator|!
name|options
operator|->
name|sample_merged
operator|&&
operator|(
name|source_core
operator|->
name|src_drawable
operator|!=
name|drawable
operator|)
operator|)
condition|)
block|{
name|dest_buffer
operator|=
name|src_buffer
expr_stmt|;
block|}
else|else
block|{
comment|/*  get the original image  */
if|if
condition|(
name|options
operator|->
name|sample_merged
condition|)
name|dest_buffer
operator|=
name|gimp_paint_core_get_orig_proj
argument_list|(
name|GIMP_PAINT_CORE
argument_list|(
name|source_core
argument_list|)
argument_list|)
expr_stmt|;
else|else
name|dest_buffer
operator|=
name|gimp_paint_core_get_orig_image
argument_list|(
name|GIMP_PAINT_CORE
argument_list|(
name|source_core
argument_list|)
argument_list|)
expr_stmt|;
block|}
operator|*
name|paint_area_offset_x
operator|=
name|x
operator|-
operator|(
name|paint_buffer_x
operator|+
name|src_offset_x
operator|)
expr_stmt|;
operator|*
name|paint_area_offset_y
operator|=
name|y
operator|-
operator|(
name|paint_buffer_y
operator|+
name|src_offset_y
operator|)
expr_stmt|;
operator|*
name|paint_area_width
operator|=
name|width
expr_stmt|;
operator|*
name|paint_area_height
operator|=
name|height
expr_stmt|;
operator|*
name|src_rect
operator|=
operator|*
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
expr_stmt|;
return|return
name|g_object_ref
argument_list|(
name|dest_buffer
argument_list|)
return|;
block|}
end_function

begin_function
specifier|static
name|void
DECL|function|gimp_source_core_src_drawable_removed (GimpDrawable * drawable,GimpSourceCore * source_core)
name|gimp_source_core_src_drawable_removed
parameter_list|(
name|GimpDrawable
modifier|*
name|drawable
parameter_list|,
name|GimpSourceCore
modifier|*
name|source_core
parameter_list|)
block|{
if|if
condition|(
name|drawable
operator|==
name|source_core
operator|->
name|src_drawable
condition|)
block|{
name|source_core
operator|->
name|src_drawable
operator|=
name|NULL
expr_stmt|;
block|}
name|g_signal_handlers_disconnect_by_func
argument_list|(
name|drawable
argument_list|,
name|gimp_source_core_src_drawable_removed
argument_list|,
name|source_core
argument_list|)
expr_stmt|;
block|}
end_function

begin_function
specifier|static
name|void
DECL|function|gimp_source_core_set_src_drawable (GimpSourceCore * source_core,GimpDrawable * drawable)
name|gimp_source_core_set_src_drawable
parameter_list|(
name|GimpSourceCore
modifier|*
name|source_core
parameter_list|,
name|GimpDrawable
modifier|*
name|drawable
parameter_list|)
block|{
if|if
condition|(
name|source_core
operator|->
name|src_drawable
operator|==
name|drawable
condition|)
return|return;
if|if
condition|(
name|source_core
operator|->
name|src_drawable
condition|)
name|g_signal_handlers_disconnect_by_func
argument_list|(
name|source_core
operator|->
name|src_drawable
argument_list|,
name|gimp_source_core_src_drawable_removed
argument_list|,
name|source_core
argument_list|)
expr_stmt|;
name|source_core
operator|->
name|src_drawable
operator|=
name|drawable
expr_stmt|;
if|if
condition|(
name|source_core
operator|->
name|src_drawable
condition|)
name|g_signal_connect
argument_list|(
name|source_core
operator|->
name|src_drawable
argument_list|,
literal|"removed"
argument_list|,
name|G_CALLBACK
argument_list|(
name|gimp_source_core_src_drawable_removed
argument_list|)
argument_list|,
name|source_core
argument_list|)
expr_stmt|;
name|g_object_notify
argument_list|(
name|G_OBJECT
argument_list|(
name|source_core
argument_list|)
argument_list|,
literal|"src-drawable"
argument_list|)
expr_stmt|;
block|}
end_function

end_unit

