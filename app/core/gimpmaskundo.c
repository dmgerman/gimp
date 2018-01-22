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
file|"core-types.h"
end_include

begin_include
include|#
directive|include
file|"gegl/gimp-gegl-utils.h"
end_include

begin_include
include|#
directive|include
file|"gimp-memsize.h"
end_include

begin_include
include|#
directive|include
file|"gimpchannel.h"
end_include

begin_include
include|#
directive|include
file|"gimpmaskundo.h"
end_include

begin_enum
enum|enum
DECL|enum|__anon2c869fd60103
block|{
DECL|enumerator|PROP_0
name|PROP_0
block|,
DECL|enumerator|PROP_CONVERT_FORMAT
name|PROP_CONVERT_FORMAT
block|}
enum|;
end_enum

begin_function_decl
specifier|static
name|void
name|gimp_mask_undo_constructed
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
name|gimp_mask_undo_set_property
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
name|gimp_mask_undo_get_property
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
name|gimp_mask_undo_get_memsize
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
name|gimp_mask_undo_pop
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
name|gimp_mask_undo_free
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
DECL|function|G_DEFINE_TYPE (GimpMaskUndo,gimp_mask_undo,GIMP_TYPE_ITEM_UNDO)
name|G_DEFINE_TYPE
argument_list|(
argument|GimpMaskUndo
argument_list|,
argument|gimp_mask_undo
argument_list|,
argument|GIMP_TYPE_ITEM_UNDO
argument_list|)
end_macro

begin_define
DECL|macro|parent_class
define|#
directive|define
name|parent_class
value|gimp_mask_undo_parent_class
end_define

begin_function
specifier|static
name|void
name|gimp_mask_undo_class_init
parameter_list|(
name|GimpMaskUndoClass
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
name|constructed
operator|=
name|gimp_mask_undo_constructed
expr_stmt|;
name|object_class
operator|->
name|set_property
operator|=
name|gimp_mask_undo_set_property
expr_stmt|;
name|object_class
operator|->
name|get_property
operator|=
name|gimp_mask_undo_get_property
expr_stmt|;
name|gimp_object_class
operator|->
name|get_memsize
operator|=
name|gimp_mask_undo_get_memsize
expr_stmt|;
name|undo_class
operator|->
name|pop
operator|=
name|gimp_mask_undo_pop
expr_stmt|;
name|undo_class
operator|->
name|free
operator|=
name|gimp_mask_undo_free
expr_stmt|;
name|g_object_class_install_property
argument_list|(
name|object_class
argument_list|,
name|PROP_CONVERT_FORMAT
argument_list|,
name|g_param_spec_boolean
argument_list|(
literal|"convert-format"
argument_list|,
name|NULL
argument_list|,
name|NULL
argument_list|,
name|FALSE
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
DECL|function|gimp_mask_undo_init (GimpMaskUndo * undo)
name|gimp_mask_undo_init
parameter_list|(
name|GimpMaskUndo
modifier|*
name|undo
parameter_list|)
block|{ }
end_function

begin_function
specifier|static
name|void
DECL|function|gimp_mask_undo_constructed (GObject * object)
name|gimp_mask_undo_constructed
parameter_list|(
name|GObject
modifier|*
name|object
parameter_list|)
block|{
name|GimpMaskUndo
modifier|*
name|mask_undo
init|=
name|GIMP_MASK_UNDO
argument_list|(
name|object
argument_list|)
decl_stmt|;
name|GimpItem
modifier|*
name|item
decl_stmt|;
name|GimpDrawable
modifier|*
name|drawable
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
name|G_OBJECT_CLASS
argument_list|(
name|parent_class
argument_list|)
operator|->
name|constructed
argument_list|(
name|object
argument_list|)
expr_stmt|;
name|g_return_if_fail
argument_list|(
name|GIMP_IS_CHANNEL
argument_list|(
name|GIMP_ITEM_UNDO
argument_list|(
name|object
argument_list|)
operator|->
name|item
argument_list|)
argument_list|)
expr_stmt|;
name|item
operator|=
name|GIMP_ITEM_UNDO
argument_list|(
name|object
argument_list|)
operator|->
name|item
expr_stmt|;
name|drawable
operator|=
name|GIMP_DRAWABLE
argument_list|(
name|item
argument_list|)
expr_stmt|;
if|if
condition|(
name|gimp_item_bounds
argument_list|(
name|item
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
condition|)
block|{
name|mask_undo
operator|->
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
name|w
argument_list|,
name|h
argument_list|)
argument_list|,
name|gimp_drawable_get_format
argument_list|(
name|drawable
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
name|GEGL_RECTANGLE
argument_list|(
name|x
argument_list|,
name|y
argument_list|,
name|w
argument_list|,
name|h
argument_list|)
argument_list|,
name|GEGL_ABYSS_NONE
argument_list|,
name|mask_undo
operator|->
name|buffer
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
name|mask_undo
operator|->
name|x
operator|=
name|x
expr_stmt|;
name|mask_undo
operator|->
name|y
operator|=
name|y
expr_stmt|;
block|}
name|mask_undo
operator|->
name|format
operator|=
name|gimp_drawable_get_format
argument_list|(
name|drawable
argument_list|)
expr_stmt|;
block|}
end_function

begin_function
specifier|static
name|void
DECL|function|gimp_mask_undo_set_property (GObject * object,guint property_id,const GValue * value,GParamSpec * pspec)
name|gimp_mask_undo_set_property
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
name|GimpMaskUndo
modifier|*
name|mask_undo
init|=
name|GIMP_MASK_UNDO
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
name|PROP_CONVERT_FORMAT
case|:
name|mask_undo
operator|->
name|convert_format
operator|=
name|g_value_get_boolean
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
DECL|function|gimp_mask_undo_get_property (GObject * object,guint property_id,GValue * value,GParamSpec * pspec)
name|gimp_mask_undo_get_property
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
name|GimpMaskUndo
modifier|*
name|mask_undo
init|=
name|GIMP_MASK_UNDO
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
name|PROP_CONVERT_FORMAT
case|:
name|g_value_set_boolean
argument_list|(
name|value
argument_list|,
name|mask_undo
operator|->
name|convert_format
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
DECL|function|gimp_mask_undo_get_memsize (GimpObject * object,gint64 * gui_size)
name|gimp_mask_undo_get_memsize
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
name|GimpMaskUndo
modifier|*
name|mask_undo
init|=
name|GIMP_MASK_UNDO
argument_list|(
name|object
argument_list|)
decl_stmt|;
name|gint64
name|memsize
init|=
literal|0
decl_stmt|;
name|memsize
operator|+=
name|gimp_gegl_buffer_get_memsize
argument_list|(
name|mask_undo
operator|->
name|buffer
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
DECL|function|gimp_mask_undo_pop (GimpUndo * undo,GimpUndoMode undo_mode,GimpUndoAccumulator * accum)
name|gimp_mask_undo_pop
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
name|GimpMaskUndo
modifier|*
name|mask_undo
init|=
name|GIMP_MASK_UNDO
argument_list|(
name|undo
argument_list|)
decl_stmt|;
name|GimpItem
modifier|*
name|item
init|=
name|GIMP_ITEM_UNDO
argument_list|(
name|undo
argument_list|)
operator|->
name|item
decl_stmt|;
name|GimpDrawable
modifier|*
name|drawable
init|=
name|GIMP_DRAWABLE
argument_list|(
name|item
argument_list|)
decl_stmt|;
name|GimpChannel
modifier|*
name|channel
init|=
name|GIMP_CHANNEL
argument_list|(
name|item
argument_list|)
decl_stmt|;
name|GeglBuffer
modifier|*
name|new_buffer
decl_stmt|;
specifier|const
name|Babl
modifier|*
name|format
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
name|gint
name|width
init|=
literal|0
decl_stmt|;
name|gint
name|height
init|=
literal|0
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
if|if
condition|(
name|gimp_item_bounds
argument_list|(
name|item
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
condition|)
block|{
name|new_buffer
operator|=
name|gegl_buffer_new
argument_list|(
name|GEGL_RECTANGLE
argument_list|(
literal|0
argument_list|,
literal|0
argument_list|,
name|w
argument_list|,
name|h
argument_list|)
argument_list|,
name|gimp_drawable_get_format
argument_list|(
name|drawable
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
name|GEGL_RECTANGLE
argument_list|(
name|x
argument_list|,
name|y
argument_list|,
name|w
argument_list|,
name|h
argument_list|)
argument_list|,
name|GEGL_ABYSS_NONE
argument_list|,
name|new_buffer
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
name|gegl_buffer_clear
argument_list|(
name|gimp_drawable_get_buffer
argument_list|(
name|drawable
argument_list|)
argument_list|,
name|GEGL_RECTANGLE
argument_list|(
name|x
argument_list|,
name|y
argument_list|,
name|w
argument_list|,
name|h
argument_list|)
argument_list|)
expr_stmt|;
block|}
else|else
block|{
name|new_buffer
operator|=
name|NULL
expr_stmt|;
block|}
name|format
operator|=
name|gimp_drawable_get_format
argument_list|(
name|drawable
argument_list|)
expr_stmt|;
if|if
condition|(
name|mask_undo
operator|->
name|convert_format
condition|)
block|{
name|GeglBuffer
modifier|*
name|buffer
decl_stmt|;
name|gint
name|width
init|=
name|gimp_item_get_width
argument_list|(
name|item
argument_list|)
decl_stmt|;
name|gint
name|height
init|=
name|gimp_item_get_height
argument_list|(
name|item
argument_list|)
decl_stmt|;
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
name|width
argument_list|,
name|height
argument_list|)
argument_list|,
name|mask_undo
operator|->
name|format
argument_list|)
expr_stmt|;
name|gegl_buffer_clear
argument_list|(
name|buffer
argument_list|,
name|NULL
argument_list|)
expr_stmt|;
name|gimp_drawable_set_buffer
argument_list|(
name|drawable
argument_list|,
name|FALSE
argument_list|,
name|NULL
argument_list|,
name|buffer
argument_list|)
expr_stmt|;
name|g_object_unref
argument_list|(
name|buffer
argument_list|)
expr_stmt|;
block|}
if|if
condition|(
name|mask_undo
operator|->
name|buffer
condition|)
block|{
name|width
operator|=
name|gegl_buffer_get_width
argument_list|(
name|mask_undo
operator|->
name|buffer
argument_list|)
expr_stmt|;
name|height
operator|=
name|gegl_buffer_get_height
argument_list|(
name|mask_undo
operator|->
name|buffer
argument_list|)
expr_stmt|;
name|gegl_buffer_copy
argument_list|(
name|mask_undo
operator|->
name|buffer
argument_list|,
name|NULL
argument_list|,
name|GEGL_ABYSS_NONE
argument_list|,
name|gimp_drawable_get_buffer
argument_list|(
name|drawable
argument_list|)
argument_list|,
name|GEGL_RECTANGLE
argument_list|(
name|mask_undo
operator|->
name|x
argument_list|,
name|mask_undo
operator|->
name|y
argument_list|,
literal|0
argument_list|,
literal|0
argument_list|)
argument_list|)
expr_stmt|;
name|g_object_unref
argument_list|(
name|mask_undo
operator|->
name|buffer
argument_list|)
expr_stmt|;
block|}
comment|/* invalidate the current bounds and boundary of the mask */
name|gimp_drawable_invalidate_boundary
argument_list|(
name|drawable
argument_list|)
expr_stmt|;
if|if
condition|(
name|mask_undo
operator|->
name|buffer
condition|)
block|{
name|channel
operator|->
name|empty
operator|=
name|FALSE
expr_stmt|;
name|channel
operator|->
name|x1
operator|=
name|mask_undo
operator|->
name|x
expr_stmt|;
name|channel
operator|->
name|y1
operator|=
name|mask_undo
operator|->
name|y
expr_stmt|;
name|channel
operator|->
name|x2
operator|=
name|mask_undo
operator|->
name|x
operator|+
name|width
expr_stmt|;
name|channel
operator|->
name|y2
operator|=
name|mask_undo
operator|->
name|y
operator|+
name|height
expr_stmt|;
block|}
else|else
block|{
name|channel
operator|->
name|empty
operator|=
name|TRUE
expr_stmt|;
name|channel
operator|->
name|x1
operator|=
literal|0
expr_stmt|;
name|channel
operator|->
name|y1
operator|=
literal|0
expr_stmt|;
name|channel
operator|->
name|x2
operator|=
name|gimp_item_get_width
argument_list|(
name|item
argument_list|)
expr_stmt|;
name|channel
operator|->
name|y2
operator|=
name|gimp_item_get_height
argument_list|(
name|item
argument_list|)
expr_stmt|;
block|}
comment|/* we know the bounds */
name|channel
operator|->
name|bounds_known
operator|=
name|TRUE
expr_stmt|;
comment|/*  set the new mask undo parameters  */
name|mask_undo
operator|->
name|buffer
operator|=
name|new_buffer
expr_stmt|;
name|mask_undo
operator|->
name|x
operator|=
name|x
expr_stmt|;
name|mask_undo
operator|->
name|y
operator|=
name|y
expr_stmt|;
name|mask_undo
operator|->
name|format
operator|=
name|format
expr_stmt|;
name|gimp_drawable_update
argument_list|(
name|drawable
argument_list|,
literal|0
argument_list|,
literal|0
argument_list|,
operator|-
literal|1
argument_list|,
operator|-
literal|1
argument_list|)
expr_stmt|;
block|}
end_function

begin_function
specifier|static
name|void
DECL|function|gimp_mask_undo_free (GimpUndo * undo,GimpUndoMode undo_mode)
name|gimp_mask_undo_free
parameter_list|(
name|GimpUndo
modifier|*
name|undo
parameter_list|,
name|GimpUndoMode
name|undo_mode
parameter_list|)
block|{
name|GimpMaskUndo
modifier|*
name|mask_undo
init|=
name|GIMP_MASK_UNDO
argument_list|(
name|undo
argument_list|)
decl_stmt|;
name|g_clear_object
argument_list|(
operator|&
name|mask_undo
operator|->
name|buffer
argument_list|)
expr_stmt|;
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

