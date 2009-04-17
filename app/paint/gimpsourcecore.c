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
file|"libgimpbase/gimpbase.h"
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
file|"base/tile-manager.h"
end_include

begin_include
include|#
directive|include
file|"base/pixel-region.h"
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
DECL|enum|__anon2b89ae780103
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
unit|static void     gimp_source_core_motion          (GimpSourceCore   *source_core,                                                   GimpDrawable     *drawable,                                                   GimpPaintOptions *paint_options);
endif|#
directive|endif
end_endif

begin_function_decl
specifier|static
name|gboolean
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
name|TempBuf
modifier|*
name|paint_area
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
name|PixelRegion
modifier|*
name|srcPR
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
name|g_param_spec_double
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
literal|0.0
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
name|g_param_spec_double
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
literal|0.0
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
literal|0.0
expr_stmt|;
name|source_core
operator|->
name|src_y
operator|=
literal|0.0
expr_stmt|;
name|source_core
operator|->
name|orig_src_x
operator|=
literal|0.0
expr_stmt|;
name|source_core
operator|->
name|orig_src_y
operator|=
literal|0.0
expr_stmt|;
name|source_core
operator|->
name|offset_x
operator|=
literal|0.0
expr_stmt|;
name|source_core
operator|->
name|offset_y
operator|=
literal|0.0
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
name|g_value_get_double
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
name|g_value_get_double
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
name|options
operator|->
name|use_source
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
DECL|function|gimp_source_core_paint (GimpPaintCore * paint_core,GimpDrawable * drawable,GimpPaintOptions * paint_options,GimpPaintState paint_state,guint32 time)
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
name|source_core
operator|->
name|src_x
operator|=
name|paint_core
operator|->
name|cur_coords
operator|.
name|x
expr_stmt|;
name|source_core
operator|->
name|src_y
operator|=
name|paint_core
operator|->
name|cur_coords
operator|.
name|y
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
name|paint_core
operator|->
name|cur_coords
operator|.
name|x
expr_stmt|;
name|source_core
operator|->
name|src_y
operator|=
name|paint_core
operator|->
name|cur_coords
operator|.
name|y
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
name|paint_core
operator|->
name|cur_coords
operator|.
name|x
expr_stmt|;
name|dest_y
operator|=
name|paint_core
operator|->
name|cur_coords
operator|.
name|y
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
DECL|function|gimp_source_core_motion (GimpSourceCore * source_core,GimpDrawable * drawable,GimpPaintOptions * paint_options)
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
name|PixelRegion
name|srcPR
decl_stmt|;
name|gint
name|src_offset_x
decl_stmt|;
name|gint
name|src_offset_y
decl_stmt|;
name|TempBuf
modifier|*
name|paint_area
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
name|opacity
decl_stmt|;
name|opacity
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
if|if
condition|(
name|opacity
operator|==
literal|0.0
condition|)
return|return;
name|src_offset_x
operator|=
name|source_core
operator|->
name|offset_x
expr_stmt|;
name|src_offset_y
operator|=
name|source_core
operator|->
name|offset_y
expr_stmt|;
if|if
condition|(
name|options
operator|->
name|use_source
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
name|gimp_image_get_projection
argument_list|(
name|src_image
argument_list|)
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
name|src_offset_x
operator|+=
name|off_x
expr_stmt|;
name|src_offset_y
operator|+=
name|off_y
expr_stmt|;
block|}
name|gimp_pickable_flush
argument_list|(
name|src_pickable
argument_list|)
expr_stmt|;
block|}
name|paint_area
operator|=
name|gimp_paint_core_get_paint_area
argument_list|(
name|paint_core
argument_list|,
name|drawable
argument_list|,
name|paint_options
argument_list|)
expr_stmt|;
if|if
condition|(
operator|!
name|paint_area
condition|)
return|return;
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
name|paint_area
operator|->
name|width
expr_stmt|;
name|paint_area_height
operator|=
name|paint_area
operator|->
name|height
expr_stmt|;
if|if
condition|(
name|options
operator|->
name|use_source
operator|&&
operator|!
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
name|paint_area
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
name|srcPR
argument_list|)
condition|)
block|{
return|return;
block|}
comment|/*  Set the paint area to transparent  */
name|temp_buf_data_clear
argument_list|(
name|paint_area
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
name|opacity
argument_list|,
name|src_pickable
argument_list|,
operator|&
name|srcPR
argument_list|,
name|src_offset_x
argument_list|,
name|src_offset_y
argument_list|,
name|paint_area
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
block|}
end_function

begin_function
specifier|static
name|gboolean
DECL|function|gimp_source_core_real_get_source (GimpSourceCore * source_core,GimpDrawable * drawable,GimpPaintOptions * paint_options,GimpPickable * src_pickable,gint src_offset_x,gint src_offset_y,TempBuf * paint_area,gint * paint_area_offset_x,gint * paint_area_offset_y,gint * paint_area_width,gint * paint_area_height,PixelRegion * srcPR)
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
name|TempBuf
modifier|*
name|paint_area
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
name|PixelRegion
modifier|*
name|srcPR
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
name|TileManager
modifier|*
name|src_tiles
init|=
name|gimp_pickable_get_tiles
argument_list|(
name|src_pickable
argument_list|)
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
name|x1
operator|=
name|CLAMP
argument_list|(
name|paint_area
operator|->
name|x
operator|+
name|src_offset_x
argument_list|,
literal|0
argument_list|,
name|tile_manager_width
argument_list|(
name|src_tiles
argument_list|)
argument_list|)
expr_stmt|;
name|y1
operator|=
name|CLAMP
argument_list|(
name|paint_area
operator|->
name|y
operator|+
name|src_offset_y
argument_list|,
literal|0
argument_list|,
name|tile_manager_height
argument_list|(
name|src_tiles
argument_list|)
argument_list|)
expr_stmt|;
name|x2
operator|=
name|CLAMP
argument_list|(
name|paint_area
operator|->
name|x
operator|+
name|src_offset_x
operator|+
name|paint_area
operator|->
name|width
argument_list|,
literal|0
argument_list|,
name|tile_manager_width
argument_list|(
name|src_tiles
argument_list|)
argument_list|)
expr_stmt|;
name|y2
operator|=
name|CLAMP
argument_list|(
name|paint_area
operator|->
name|y
operator|+
name|src_offset_y
operator|+
name|paint_area
operator|->
name|height
argument_list|,
literal|0
argument_list|,
name|tile_manager_height
argument_list|(
name|src_tiles
argument_list|)
argument_list|)
expr_stmt|;
if|if
condition|(
operator|!
operator|(
name|x2
operator|-
name|x1
operator|)
operator|||
operator|!
operator|(
name|y2
operator|-
name|y1
operator|)
condition|)
return|return
name|FALSE
return|;
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
name|pixel_region_init
argument_list|(
name|srcPR
argument_list|,
name|src_tiles
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
name|FALSE
argument_list|)
expr_stmt|;
block|}
else|else
block|{
name|TempBuf
modifier|*
name|orig
decl_stmt|;
comment|/*  get the original image  */
if|if
condition|(
name|options
operator|->
name|sample_merged
condition|)
name|orig
operator|=
name|gimp_paint_core_get_orig_proj
argument_list|(
name|GIMP_PAINT_CORE
argument_list|(
name|source_core
argument_list|)
argument_list|,
name|src_pickable
argument_list|,
name|x1
argument_list|,
name|y1
argument_list|,
name|x2
argument_list|,
name|y2
argument_list|)
expr_stmt|;
else|else
name|orig
operator|=
name|gimp_paint_core_get_orig_image
argument_list|(
name|GIMP_PAINT_CORE
argument_list|(
name|source_core
argument_list|)
argument_list|,
name|GIMP_DRAWABLE
argument_list|(
name|src_pickable
argument_list|)
argument_list|,
name|x1
argument_list|,
name|y1
argument_list|,
name|x2
argument_list|,
name|y2
argument_list|)
expr_stmt|;
name|pixel_region_init_temp_buf
argument_list|(
name|srcPR
argument_list|,
name|orig
argument_list|,
literal|0
argument_list|,
literal|0
argument_list|,
name|x2
operator|-
name|x1
argument_list|,
name|y2
operator|-
name|y1
argument_list|)
expr_stmt|;
block|}
operator|*
name|paint_area_offset_x
operator|=
name|x1
operator|-
operator|(
name|paint_area
operator|->
name|x
operator|+
name|src_offset_x
operator|)
expr_stmt|;
operator|*
name|paint_area_offset_y
operator|=
name|y1
operator|-
operator|(
name|paint_area
operator|->
name|y
operator|+
name|src_offset_y
operator|)
expr_stmt|;
operator|*
name|paint_area_width
operator|=
name|x2
operator|-
name|x1
expr_stmt|;
operator|*
name|paint_area_height
operator|=
name|y2
operator|-
name|y1
expr_stmt|;
return|return
name|TRUE
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

