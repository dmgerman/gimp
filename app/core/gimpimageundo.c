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
file|"libgimpcolor/gimpcolor.h"
end_include

begin_include
include|#
directive|include
file|"libgimpconfig/gimpconfig.h"
end_include

begin_include
include|#
directive|include
file|"core-types.h"
end_include

begin_include
include|#
directive|include
file|"gimp-utils.h"
end_include

begin_include
include|#
directive|include
file|"gimpdrawable.h"
end_include

begin_include
include|#
directive|include
file|"gimpgrid.h"
end_include

begin_include
include|#
directive|include
file|"gimpimage.h"
end_include

begin_include
include|#
directive|include
file|"gimpimage-colormap.h"
end_include

begin_include
include|#
directive|include
file|"gimpimage-grid.h"
end_include

begin_include
include|#
directive|include
file|"gimpimage-private.h"
end_include

begin_include
include|#
directive|include
file|"gimpimageundo.h"
end_include

begin_include
include|#
directive|include
file|"gimpparasitelist.h"
end_include

begin_enum
enum|enum
DECL|enum|__anon278420c30103
block|{
DECL|enumerator|PROP_0
name|PROP_0
block|,
DECL|enumerator|PROP_PREVIOUS_ORIGIN_X
name|PROP_PREVIOUS_ORIGIN_X
block|,
DECL|enumerator|PROP_PREVIOUS_ORIGIN_Y
name|PROP_PREVIOUS_ORIGIN_Y
block|,
DECL|enumerator|PROP_PREVIOUS_WIDTH
name|PROP_PREVIOUS_WIDTH
block|,
DECL|enumerator|PROP_PREVIOUS_HEIGHT
name|PROP_PREVIOUS_HEIGHT
block|,
DECL|enumerator|PROP_GRID
name|PROP_GRID
block|,
DECL|enumerator|PROP_PARASITE_NAME
name|PROP_PARASITE_NAME
block|}
enum|;
end_enum

begin_function_decl
specifier|static
name|GObject
modifier|*
name|gimp_image_undo_constructor
parameter_list|(
name|GType
name|type
parameter_list|,
name|guint
name|n_params
parameter_list|,
name|GObjectConstructParam
modifier|*
name|params
parameter_list|)
function_decl|;
end_function_decl

begin_function_decl
specifier|static
name|void
name|gimp_image_undo_set_property
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
name|gimp_image_undo_get_property
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
name|gint64
name|gimp_image_undo_get_memsize
parameter_list|(
name|GimpObject
modifier|*
name|object
parameter_list|,
name|gint64
modifier|*
name|gui_size
parameter_list|)
function_decl|;
end_function_decl

begin_function_decl
specifier|static
name|void
name|gimp_image_undo_pop
parameter_list|(
name|GimpUndo
modifier|*
name|undo
parameter_list|,
name|GimpUndoMode
name|undo_mode
parameter_list|,
name|GimpUndoAccumulator
modifier|*
name|accum
parameter_list|)
function_decl|;
end_function_decl

begin_function_decl
specifier|static
name|void
name|gimp_image_undo_free
parameter_list|(
name|GimpUndo
modifier|*
name|undo
parameter_list|,
name|GimpUndoMode
name|undo_mode
parameter_list|)
function_decl|;
end_function_decl

begin_macro
DECL|function|G_DEFINE_TYPE (GimpImageUndo,gimp_image_undo,GIMP_TYPE_UNDO)
name|G_DEFINE_TYPE
argument_list|(
argument|GimpImageUndo
argument_list|,
argument|gimp_image_undo
argument_list|,
argument|GIMP_TYPE_UNDO
argument_list|)
end_macro

begin_define
DECL|macro|parent_class
define|#
directive|define
name|parent_class
value|gimp_image_undo_parent_class
end_define

begin_function
specifier|static
name|void
name|gimp_image_undo_class_init
parameter_list|(
name|GimpImageUndoClass
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
name|GimpObjectClass
modifier|*
name|gimp_object_class
init|=
name|GIMP_OBJECT_CLASS
argument_list|(
name|klass
argument_list|)
decl_stmt|;
name|GimpUndoClass
modifier|*
name|undo_class
init|=
name|GIMP_UNDO_CLASS
argument_list|(
name|klass
argument_list|)
decl_stmt|;
name|object_class
operator|->
name|constructor
operator|=
name|gimp_image_undo_constructor
expr_stmt|;
name|object_class
operator|->
name|set_property
operator|=
name|gimp_image_undo_set_property
expr_stmt|;
name|object_class
operator|->
name|get_property
operator|=
name|gimp_image_undo_get_property
expr_stmt|;
name|gimp_object_class
operator|->
name|get_memsize
operator|=
name|gimp_image_undo_get_memsize
expr_stmt|;
name|undo_class
operator|->
name|pop
operator|=
name|gimp_image_undo_pop
expr_stmt|;
name|undo_class
operator|->
name|free
operator|=
name|gimp_image_undo_free
expr_stmt|;
name|g_object_class_install_property
argument_list|(
name|object_class
argument_list|,
name|PROP_PREVIOUS_ORIGIN_X
argument_list|,
name|g_param_spec_int
argument_list|(
literal|"previous-origin-x"
argument_list|,
name|NULL
argument_list|,
name|NULL
argument_list|,
operator|-
name|GIMP_MAX_IMAGE_SIZE
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
name|PROP_PREVIOUS_ORIGIN_Y
argument_list|,
name|g_param_spec_int
argument_list|(
literal|"previous-origin-y"
argument_list|,
name|NULL
argument_list|,
name|NULL
argument_list|,
operator|-
name|GIMP_MAX_IMAGE_SIZE
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
name|PROP_PREVIOUS_WIDTH
argument_list|,
name|g_param_spec_int
argument_list|(
literal|"previous-width"
argument_list|,
name|NULL
argument_list|,
name|NULL
argument_list|,
operator|-
name|GIMP_MAX_IMAGE_SIZE
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
name|PROP_PREVIOUS_HEIGHT
argument_list|,
name|g_param_spec_int
argument_list|(
literal|"previous-height"
argument_list|,
name|NULL
argument_list|,
name|NULL
argument_list|,
operator|-
name|GIMP_MAX_IMAGE_SIZE
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
name|PROP_GRID
argument_list|,
name|g_param_spec_object
argument_list|(
literal|"grid"
argument_list|,
name|NULL
argument_list|,
name|NULL
argument_list|,
name|GIMP_TYPE_GRID
argument_list|,
name|GIMP_PARAM_READWRITE
operator||
name|G_PARAM_CONSTRUCT_ONLY
argument_list|)
argument_list|)
expr_stmt|;
name|g_object_class_install_property
argument_list|(
name|object_class
argument_list|,
name|PROP_PARASITE_NAME
argument_list|,
name|g_param_spec_string
argument_list|(
literal|"parasite-name"
argument_list|,
name|NULL
argument_list|,
name|NULL
argument_list|,
name|NULL
argument_list|,
name|GIMP_PARAM_READWRITE
operator||
name|G_PARAM_CONSTRUCT_ONLY
argument_list|)
argument_list|)
expr_stmt|;
block|}
end_function

begin_function
specifier|static
name|void
DECL|function|gimp_image_undo_init (GimpImageUndo * undo)
name|gimp_image_undo_init
parameter_list|(
name|GimpImageUndo
modifier|*
name|undo
parameter_list|)
block|{ }
end_function

begin_function
specifier|static
name|GObject
modifier|*
DECL|function|gimp_image_undo_constructor (GType type,guint n_params,GObjectConstructParam * params)
name|gimp_image_undo_constructor
parameter_list|(
name|GType
name|type
parameter_list|,
name|guint
name|n_params
parameter_list|,
name|GObjectConstructParam
modifier|*
name|params
parameter_list|)
block|{
name|GObject
modifier|*
name|object
decl_stmt|;
name|GimpImageUndo
modifier|*
name|image_undo
decl_stmt|;
name|GimpImage
modifier|*
name|image
decl_stmt|;
name|object
operator|=
name|G_OBJECT_CLASS
argument_list|(
name|parent_class
argument_list|)
operator|->
name|constructor
argument_list|(
name|type
argument_list|,
name|n_params
argument_list|,
name|params
argument_list|)
expr_stmt|;
name|image_undo
operator|=
name|GIMP_IMAGE_UNDO
argument_list|(
name|object
argument_list|)
expr_stmt|;
name|image
operator|=
name|GIMP_UNDO
argument_list|(
name|object
argument_list|)
operator|->
name|image
expr_stmt|;
switch|switch
condition|(
name|GIMP_UNDO
argument_list|(
name|object
argument_list|)
operator|->
name|undo_type
condition|)
block|{
case|case
name|GIMP_UNDO_IMAGE_TYPE
case|:
name|image_undo
operator|->
name|base_type
operator|=
name|gimp_image_base_type
argument_list|(
name|image
argument_list|)
expr_stmt|;
break|break;
case|case
name|GIMP_UNDO_IMAGE_SIZE
case|:
name|image_undo
operator|->
name|width
operator|=
name|gimp_image_get_width
argument_list|(
name|image
argument_list|)
expr_stmt|;
name|image_undo
operator|->
name|height
operator|=
name|gimp_image_get_height
argument_list|(
name|image
argument_list|)
expr_stmt|;
break|break;
case|case
name|GIMP_UNDO_IMAGE_RESOLUTION
case|:
name|gimp_image_get_resolution
argument_list|(
name|image
argument_list|,
operator|&
name|image_undo
operator|->
name|xresolution
argument_list|,
operator|&
name|image_undo
operator|->
name|yresolution
argument_list|)
expr_stmt|;
name|image_undo
operator|->
name|resolution_unit
operator|=
name|gimp_image_get_unit
argument_list|(
name|image
argument_list|)
expr_stmt|;
break|break;
case|case
name|GIMP_UNDO_IMAGE_GRID
case|:
name|g_assert
argument_list|(
name|GIMP_IS_GRID
argument_list|(
name|image_undo
operator|->
name|grid
argument_list|)
argument_list|)
expr_stmt|;
break|break;
case|case
name|GIMP_UNDO_IMAGE_COLORMAP
case|:
name|image_undo
operator|->
name|num_colors
operator|=
name|gimp_image_get_colormap_size
argument_list|(
name|image
argument_list|)
expr_stmt|;
name|image_undo
operator|->
name|colormap
operator|=
name|g_memdup
argument_list|(
name|gimp_image_get_colormap
argument_list|(
name|image
argument_list|)
argument_list|,
name|GIMP_IMAGE_COLORMAP_SIZE
argument_list|)
expr_stmt|;
break|break;
case|case
name|GIMP_UNDO_PARASITE_ATTACH
case|:
case|case
name|GIMP_UNDO_PARASITE_REMOVE
case|:
name|g_assert
argument_list|(
name|image_undo
operator|->
name|parasite_name
operator|!=
name|NULL
argument_list|)
expr_stmt|;
name|image_undo
operator|->
name|parasite
operator|=
name|gimp_parasite_copy
argument_list|(
name|gimp_image_parasite_find
argument_list|(
name|image
argument_list|,
name|image_undo
operator|->
name|parasite_name
argument_list|)
argument_list|)
expr_stmt|;
break|break;
default|default:
name|g_assert_not_reached
argument_list|()
expr_stmt|;
block|}
return|return
name|object
return|;
block|}
end_function

begin_function
specifier|static
name|void
DECL|function|gimp_image_undo_set_property (GObject * object,guint property_id,const GValue * value,GParamSpec * pspec)
name|gimp_image_undo_set_property
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
name|GimpImageUndo
modifier|*
name|image_undo
init|=
name|GIMP_IMAGE_UNDO
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
name|PROP_PREVIOUS_ORIGIN_X
case|:
name|image_undo
operator|->
name|previous_origin_x
operator|=
name|g_value_get_int
argument_list|(
name|value
argument_list|)
expr_stmt|;
break|break;
case|case
name|PROP_PREVIOUS_ORIGIN_Y
case|:
name|image_undo
operator|->
name|previous_origin_y
operator|=
name|g_value_get_int
argument_list|(
name|value
argument_list|)
expr_stmt|;
break|break;
case|case
name|PROP_PREVIOUS_WIDTH
case|:
name|image_undo
operator|->
name|previous_width
operator|=
name|g_value_get_int
argument_list|(
name|value
argument_list|)
expr_stmt|;
break|break;
case|case
name|PROP_PREVIOUS_HEIGHT
case|:
name|image_undo
operator|->
name|previous_height
operator|=
name|g_value_get_int
argument_list|(
name|value
argument_list|)
expr_stmt|;
break|break;
case|case
name|PROP_GRID
case|:
block|{
name|GimpGrid
modifier|*
name|grid
init|=
name|g_value_get_object
argument_list|(
name|value
argument_list|)
decl_stmt|;
if|if
condition|(
name|grid
condition|)
name|image_undo
operator|->
name|grid
operator|=
name|gimp_config_duplicate
argument_list|(
name|GIMP_CONFIG
argument_list|(
name|grid
argument_list|)
argument_list|)
expr_stmt|;
block|}
break|break;
case|case
name|PROP_PARASITE_NAME
case|:
name|image_undo
operator|->
name|parasite_name
operator|=
name|g_value_dup_string
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
DECL|function|gimp_image_undo_get_property (GObject * object,guint property_id,GValue * value,GParamSpec * pspec)
name|gimp_image_undo_get_property
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
name|GimpImageUndo
modifier|*
name|image_undo
init|=
name|GIMP_IMAGE_UNDO
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
name|PROP_PREVIOUS_ORIGIN_X
case|:
name|g_value_set_int
argument_list|(
name|value
argument_list|,
name|image_undo
operator|->
name|previous_origin_x
argument_list|)
expr_stmt|;
break|break;
case|case
name|PROP_PREVIOUS_ORIGIN_Y
case|:
name|g_value_set_int
argument_list|(
name|value
argument_list|,
name|image_undo
operator|->
name|previous_origin_y
argument_list|)
expr_stmt|;
break|break;
case|case
name|PROP_PREVIOUS_WIDTH
case|:
name|g_value_set_int
argument_list|(
name|value
argument_list|,
name|image_undo
operator|->
name|previous_width
argument_list|)
expr_stmt|;
break|break;
case|case
name|PROP_PREVIOUS_HEIGHT
case|:
name|g_value_set_int
argument_list|(
name|value
argument_list|,
name|image_undo
operator|->
name|previous_height
argument_list|)
expr_stmt|;
break|break;
case|case
name|PROP_GRID
case|:
name|g_value_set_object
argument_list|(
name|value
argument_list|,
name|image_undo
operator|->
name|grid
argument_list|)
expr_stmt|;
break|break;
case|case
name|PROP_PARASITE_NAME
case|:
name|g_value_set_string
argument_list|(
name|value
argument_list|,
name|image_undo
operator|->
name|parasite_name
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
name|gint64
DECL|function|gimp_image_undo_get_memsize (GimpObject * object,gint64 * gui_size)
name|gimp_image_undo_get_memsize
parameter_list|(
name|GimpObject
modifier|*
name|object
parameter_list|,
name|gint64
modifier|*
name|gui_size
parameter_list|)
block|{
name|GimpImageUndo
modifier|*
name|image_undo
init|=
name|GIMP_IMAGE_UNDO
argument_list|(
name|object
argument_list|)
decl_stmt|;
name|gint64
name|memsize
init|=
literal|0
decl_stmt|;
if|if
condition|(
name|image_undo
operator|->
name|colormap
condition|)
name|memsize
operator|+=
name|GIMP_IMAGE_COLORMAP_SIZE
expr_stmt|;
name|memsize
operator|+=
name|gimp_object_get_memsize
argument_list|(
name|GIMP_OBJECT
argument_list|(
name|image_undo
operator|->
name|grid
argument_list|)
argument_list|,
name|gui_size
argument_list|)
expr_stmt|;
name|memsize
operator|+=
name|gimp_string_get_memsize
argument_list|(
name|image_undo
operator|->
name|parasite_name
argument_list|)
expr_stmt|;
name|memsize
operator|+=
name|gimp_parasite_get_memsize
argument_list|(
name|image_undo
operator|->
name|parasite
argument_list|,
name|gui_size
argument_list|)
expr_stmt|;
return|return
name|memsize
operator|+
name|GIMP_OBJECT_CLASS
argument_list|(
name|parent_class
argument_list|)
operator|->
name|get_memsize
argument_list|(
name|object
argument_list|,
name|gui_size
argument_list|)
return|;
block|}
end_function

begin_function
specifier|static
name|void
DECL|function|gimp_image_undo_pop (GimpUndo * undo,GimpUndoMode undo_mode,GimpUndoAccumulator * accum)
name|gimp_image_undo_pop
parameter_list|(
name|GimpUndo
modifier|*
name|undo
parameter_list|,
name|GimpUndoMode
name|undo_mode
parameter_list|,
name|GimpUndoAccumulator
modifier|*
name|accum
parameter_list|)
block|{
name|GimpImageUndo
modifier|*
name|image_undo
init|=
name|GIMP_IMAGE_UNDO
argument_list|(
name|undo
argument_list|)
decl_stmt|;
name|GimpImage
modifier|*
name|image
init|=
name|undo
operator|->
name|image
decl_stmt|;
name|GimpImagePrivate
modifier|*
name|private
init|=
name|GIMP_IMAGE_GET_PRIVATE
argument_list|(
name|image
argument_list|)
decl_stmt|;
name|GIMP_UNDO_CLASS
argument_list|(
name|parent_class
argument_list|)
operator|->
name|pop
argument_list|(
name|undo
argument_list|,
name|undo_mode
argument_list|,
name|accum
argument_list|)
expr_stmt|;
switch|switch
condition|(
name|undo
operator|->
name|undo_type
condition|)
block|{
case|case
name|GIMP_UNDO_IMAGE_TYPE
case|:
block|{
name|GimpImageBaseType
name|base_type
decl_stmt|;
name|base_type
operator|=
name|image_undo
operator|->
name|base_type
expr_stmt|;
name|image_undo
operator|->
name|base_type
operator|=
name|gimp_image_base_type
argument_list|(
name|image
argument_list|)
expr_stmt|;
name|g_object_set
argument_list|(
name|image
argument_list|,
literal|"base-type"
argument_list|,
name|base_type
argument_list|,
name|NULL
argument_list|)
expr_stmt|;
name|gimp_image_colormap_changed
argument_list|(
name|image
argument_list|,
operator|-
literal|1
argument_list|)
expr_stmt|;
if|if
condition|(
name|image_undo
operator|->
name|base_type
operator|!=
name|gimp_image_base_type
argument_list|(
name|image
argument_list|)
condition|)
name|accum
operator|->
name|mode_changed
operator|=
name|TRUE
expr_stmt|;
block|}
break|break;
case|case
name|GIMP_UNDO_IMAGE_SIZE
case|:
block|{
name|gint
name|width
decl_stmt|;
name|gint
name|height
decl_stmt|;
name|gint
name|previous_origin_x
decl_stmt|;
name|gint
name|previous_origin_y
decl_stmt|;
name|gint
name|previous_width
decl_stmt|;
name|gint
name|previous_height
decl_stmt|;
name|width
operator|=
name|image_undo
operator|->
name|width
expr_stmt|;
name|height
operator|=
name|image_undo
operator|->
name|height
expr_stmt|;
name|previous_origin_x
operator|=
name|image_undo
operator|->
name|previous_origin_x
expr_stmt|;
name|previous_origin_y
operator|=
name|image_undo
operator|->
name|previous_origin_y
expr_stmt|;
name|previous_width
operator|=
name|image_undo
operator|->
name|previous_width
expr_stmt|;
name|previous_height
operator|=
name|image_undo
operator|->
name|previous_height
expr_stmt|;
comment|/* Transform to a redo */
name|image_undo
operator|->
name|width
operator|=
name|gimp_image_get_width
argument_list|(
name|image
argument_list|)
expr_stmt|;
name|image_undo
operator|->
name|height
operator|=
name|gimp_image_get_height
argument_list|(
name|image
argument_list|)
expr_stmt|;
name|image_undo
operator|->
name|previous_origin_x
operator|=
operator|-
name|previous_origin_x
expr_stmt|;
name|image_undo
operator|->
name|previous_origin_y
operator|=
operator|-
name|previous_origin_y
expr_stmt|;
name|image_undo
operator|->
name|previous_width
operator|=
name|width
expr_stmt|;
name|image_undo
operator|->
name|previous_height
operator|=
name|height
expr_stmt|;
name|g_object_set
argument_list|(
name|image
argument_list|,
literal|"width"
argument_list|,
name|width
argument_list|,
literal|"height"
argument_list|,
name|height
argument_list|,
name|NULL
argument_list|)
expr_stmt|;
name|gimp_drawable_invalidate_boundary
argument_list|(
name|GIMP_DRAWABLE
argument_list|(
name|gimp_image_get_mask
argument_list|(
name|image
argument_list|)
argument_list|)
argument_list|)
expr_stmt|;
if|if
condition|(
name|gimp_image_get_width
argument_list|(
name|image
argument_list|)
operator|!=
name|image_undo
operator|->
name|width
operator|||
name|gimp_image_get_height
argument_list|(
name|image
argument_list|)
operator|!=
name|image_undo
operator|->
name|height
condition|)
block|{
name|accum
operator|->
name|size_changed
operator|=
name|TRUE
expr_stmt|;
name|accum
operator|->
name|previous_origin_x
operator|=
name|previous_origin_x
expr_stmt|;
name|accum
operator|->
name|previous_origin_y
operator|=
name|previous_origin_y
expr_stmt|;
name|accum
operator|->
name|previous_width
operator|=
name|previous_width
expr_stmt|;
name|accum
operator|->
name|previous_height
operator|=
name|previous_height
expr_stmt|;
block|}
block|}
break|break;
case|case
name|GIMP_UNDO_IMAGE_RESOLUTION
case|:
block|{
name|gdouble
name|xres
decl_stmt|;
name|gdouble
name|yres
decl_stmt|;
name|gimp_image_get_resolution
argument_list|(
name|image
argument_list|,
operator|&
name|xres
argument_list|,
operator|&
name|yres
argument_list|)
expr_stmt|;
if|if
condition|(
name|ABS
argument_list|(
name|image_undo
operator|->
name|xresolution
operator|-
name|xres
argument_list|)
operator|>=
literal|1e-5
operator|||
name|ABS
argument_list|(
name|image_undo
operator|->
name|yresolution
operator|-
name|yres
argument_list|)
operator|>=
literal|1e-5
condition|)
block|{
name|private
operator|->
name|xresolution
operator|=
name|image_undo
operator|->
name|xresolution
expr_stmt|;
name|private
operator|->
name|yresolution
operator|=
name|image_undo
operator|->
name|yresolution
expr_stmt|;
name|image_undo
operator|->
name|xresolution
operator|=
name|xres
expr_stmt|;
name|image_undo
operator|->
name|yresolution
operator|=
name|yres
expr_stmt|;
name|accum
operator|->
name|resolution_changed
operator|=
name|TRUE
expr_stmt|;
block|}
block|}
if|if
condition|(
name|image_undo
operator|->
name|resolution_unit
operator|!=
name|gimp_image_get_unit
argument_list|(
name|image
argument_list|)
condition|)
block|{
name|GimpUnit
name|unit
decl_stmt|;
name|unit
operator|=
name|gimp_image_get_unit
argument_list|(
name|image
argument_list|)
expr_stmt|;
name|private
operator|->
name|resolution_unit
operator|=
name|image_undo
operator|->
name|resolution_unit
expr_stmt|;
name|image_undo
operator|->
name|resolution_unit
operator|=
name|unit
expr_stmt|;
name|accum
operator|->
name|unit_changed
operator|=
name|TRUE
expr_stmt|;
block|}
break|break;
case|case
name|GIMP_UNDO_IMAGE_GRID
case|:
block|{
name|GimpGrid
modifier|*
name|grid
decl_stmt|;
name|grid
operator|=
name|gimp_config_duplicate
argument_list|(
name|GIMP_CONFIG
argument_list|(
name|image
operator|->
name|grid
argument_list|)
argument_list|)
expr_stmt|;
name|gimp_image_set_grid
argument_list|(
name|image
argument_list|,
name|image_undo
operator|->
name|grid
argument_list|,
name|FALSE
argument_list|)
expr_stmt|;
name|g_object_unref
argument_list|(
name|image_undo
operator|->
name|grid
argument_list|)
expr_stmt|;
name|image_undo
operator|->
name|grid
operator|=
name|grid
expr_stmt|;
block|}
break|break;
case|case
name|GIMP_UNDO_IMAGE_COLORMAP
case|:
block|{
name|guchar
modifier|*
name|colormap
decl_stmt|;
name|gint
name|num_colors
decl_stmt|;
name|num_colors
operator|=
name|gimp_image_get_colormap_size
argument_list|(
name|image
argument_list|)
expr_stmt|;
name|colormap
operator|=
name|g_memdup
argument_list|(
name|gimp_image_get_colormap
argument_list|(
name|image
argument_list|)
argument_list|,
name|GIMP_IMAGE_COLORMAP_SIZE
argument_list|)
expr_stmt|;
name|gimp_image_set_colormap
argument_list|(
name|image
argument_list|,
name|image_undo
operator|->
name|colormap
argument_list|,
name|image_undo
operator|->
name|num_colors
argument_list|,
name|FALSE
argument_list|)
expr_stmt|;
if|if
condition|(
name|image_undo
operator|->
name|colormap
condition|)
name|g_free
argument_list|(
name|image_undo
operator|->
name|colormap
argument_list|)
expr_stmt|;
name|image_undo
operator|->
name|num_colors
operator|=
name|num_colors
expr_stmt|;
name|image_undo
operator|->
name|colormap
operator|=
name|colormap
expr_stmt|;
block|}
break|break;
case|case
name|GIMP_UNDO_PARASITE_ATTACH
case|:
case|case
name|GIMP_UNDO_PARASITE_REMOVE
case|:
block|{
name|GimpParasite
modifier|*
name|parasite
init|=
name|image_undo
operator|->
name|parasite
decl_stmt|;
specifier|const
name|gchar
modifier|*
name|name
decl_stmt|;
name|image_undo
operator|->
name|parasite
operator|=
name|gimp_parasite_copy
argument_list|(
name|gimp_image_parasite_find
argument_list|(
name|image
argument_list|,
name|image_undo
operator|->
name|parasite_name
argument_list|)
argument_list|)
expr_stmt|;
if|if
condition|(
name|parasite
condition|)
name|gimp_parasite_list_add
argument_list|(
name|image
operator|->
name|parasites
argument_list|,
name|parasite
argument_list|)
expr_stmt|;
else|else
name|gimp_parasite_list_remove
argument_list|(
name|image
operator|->
name|parasites
argument_list|,
name|image_undo
operator|->
name|parasite_name
argument_list|)
expr_stmt|;
name|name
operator|=
name|parasite
condition|?
name|parasite
operator|->
name|name
else|:
name|image_undo
operator|->
name|parasite_name
expr_stmt|;
if|if
condition|(
name|strcmp
argument_list|(
name|name
argument_list|,
literal|"icc-profile"
argument_list|)
operator|==
literal|0
condition|)
name|gimp_color_managed_profile_changed
argument_list|(
name|GIMP_COLOR_MANAGED
argument_list|(
name|image
argument_list|)
argument_list|)
expr_stmt|;
if|if
condition|(
name|parasite
condition|)
name|gimp_parasite_free
argument_list|(
name|parasite
argument_list|)
expr_stmt|;
block|}
break|break;
default|default:
name|g_assert_not_reached
argument_list|()
expr_stmt|;
block|}
block|}
end_function

begin_function
specifier|static
name|void
DECL|function|gimp_image_undo_free (GimpUndo * undo,GimpUndoMode undo_mode)
name|gimp_image_undo_free
parameter_list|(
name|GimpUndo
modifier|*
name|undo
parameter_list|,
name|GimpUndoMode
name|undo_mode
parameter_list|)
block|{
name|GimpImageUndo
modifier|*
name|image_undo
init|=
name|GIMP_IMAGE_UNDO
argument_list|(
name|undo
argument_list|)
decl_stmt|;
if|if
condition|(
name|image_undo
operator|->
name|grid
condition|)
block|{
name|g_object_unref
argument_list|(
name|image_undo
operator|->
name|grid
argument_list|)
expr_stmt|;
name|image_undo
operator|->
name|grid
operator|=
name|NULL
expr_stmt|;
block|}
if|if
condition|(
name|image_undo
operator|->
name|colormap
condition|)
block|{
name|g_free
argument_list|(
name|image_undo
operator|->
name|colormap
argument_list|)
expr_stmt|;
name|image_undo
operator|->
name|colormap
operator|=
name|NULL
expr_stmt|;
block|}
if|if
condition|(
name|image_undo
operator|->
name|parasite_name
condition|)
block|{
name|g_free
argument_list|(
name|image_undo
operator|->
name|parasite_name
argument_list|)
expr_stmt|;
name|image_undo
operator|->
name|parasite_name
operator|=
name|NULL
expr_stmt|;
block|}
if|if
condition|(
name|image_undo
operator|->
name|parasite
condition|)
block|{
name|gimp_parasite_free
argument_list|(
name|image_undo
operator|->
name|parasite
argument_list|)
expr_stmt|;
name|image_undo
operator|->
name|parasite
operator|=
name|NULL
expr_stmt|;
block|}
name|GIMP_UNDO_CLASS
argument_list|(
name|parent_class
argument_list|)
operator|->
name|free
argument_list|(
name|undo
argument_list|,
name|undo_mode
argument_list|)
expr_stmt|;
block|}
end_function

end_unit

