begin_unit|revision:0.9.5;language:C;cregit-version:0.0.1
begin_comment
comment|/* GIMP - The GNU Image Manipulation Program  * Copyright (C) 1995 Spencer Kimball and Peter Mattis  *  * This program is free software; you can redistribute it and/or modify  * it under the terms of the GNU General Public License as published by  * the Free Software Foundation; either version 2 of the License, or  * (at your option) any later version.  *  * This program is distributed in the hope that it will be useful,  * but WITHOUT ANY WARRANTY; without even the implied warranty of  * MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the  * GNU General Public License for more details.  *  * You should have received a copy of the GNU General Public License  * along with this program; if not, write to the Free Software  * Foundation, Inc., 59 Temple Place - Suite 330, Boston, MA 02111-1307, USA.  */
end_comment

begin_include
include|#
directive|include
file|"config.h"
end_include

begin_include
include|#
directive|include
file|<glib-object.h>
end_include

begin_include
include|#
directive|include
file|"libgimpbase/gimpbase.h"
end_include

begin_include
include|#
directive|include
file|"core-types.h"
end_include

begin_include
include|#
directive|include
file|"base/tile-manager.h"
end_include

begin_include
include|#
directive|include
file|"gimpimage.h"
end_include

begin_include
include|#
directive|include
file|"gimpdrawable.h"
end_include

begin_include
include|#
directive|include
file|"gimpdrawableundo.h"
end_include

begin_enum
enum|enum
DECL|enum|__anon2bf5f4f50103
block|{
DECL|enumerator|PROP_0
name|PROP_0
block|,
DECL|enumerator|PROP_TILES
name|PROP_TILES
block|,
DECL|enumerator|PROP_SPARSE
name|PROP_SPARSE
block|,
DECL|enumerator|PROP_X
name|PROP_X
block|,
DECL|enumerator|PROP_Y
name|PROP_Y
block|,
DECL|enumerator|PROP_WIDTH
name|PROP_WIDTH
block|,
DECL|enumerator|PROP_HEIGHT
name|PROP_HEIGHT
block|}
enum|;
end_enum

begin_function_decl
specifier|static
name|GObject
modifier|*
name|gimp_drawable_undo_constructor
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
name|gimp_drawable_undo_set_property
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
name|gimp_drawable_undo_get_property
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
name|void
name|gimp_drawable_undo_pop
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
name|gimp_drawable_undo_free
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
DECL|function|G_DEFINE_TYPE (GimpDrawableUndo,gimp_drawable_undo,GIMP_TYPE_ITEM_UNDO)
name|G_DEFINE_TYPE
argument_list|(
argument|GimpDrawableUndo
argument_list|,
argument|gimp_drawable_undo
argument_list|,
argument|GIMP_TYPE_ITEM_UNDO
argument_list|)
end_macro

begin_define
DECL|macro|parent_class
define|#
directive|define
name|parent_class
value|gimp_drawable_undo_parent_class
end_define

begin_function
specifier|static
name|void
name|gimp_drawable_undo_class_init
parameter_list|(
name|GimpDrawableUndoClass
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
name|gimp_drawable_undo_constructor
expr_stmt|;
name|object_class
operator|->
name|set_property
operator|=
name|gimp_drawable_undo_set_property
expr_stmt|;
name|object_class
operator|->
name|get_property
operator|=
name|gimp_drawable_undo_get_property
expr_stmt|;
name|undo_class
operator|->
name|pop
operator|=
name|gimp_drawable_undo_pop
expr_stmt|;
name|undo_class
operator|->
name|free
operator|=
name|gimp_drawable_undo_free
expr_stmt|;
name|g_object_class_install_property
argument_list|(
name|object_class
argument_list|,
name|PROP_TILES
argument_list|,
name|g_param_spec_pointer
argument_list|(
literal|"tiles"
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
name|g_object_class_install_property
argument_list|(
name|object_class
argument_list|,
name|PROP_SPARSE
argument_list|,
name|g_param_spec_boolean
argument_list|(
literal|"sparse"
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
name|g_object_class_install_property
argument_list|(
name|object_class
argument_list|,
name|PROP_X
argument_list|,
name|g_param_spec_int
argument_list|(
literal|"x"
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
operator||
name|G_PARAM_CONSTRUCT_ONLY
argument_list|)
argument_list|)
expr_stmt|;
name|g_object_class_install_property
argument_list|(
name|object_class
argument_list|,
name|PROP_Y
argument_list|,
name|g_param_spec_int
argument_list|(
literal|"y"
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
operator||
name|G_PARAM_CONSTRUCT_ONLY
argument_list|)
argument_list|)
expr_stmt|;
name|g_object_class_install_property
argument_list|(
name|object_class
argument_list|,
name|PROP_WIDTH
argument_list|,
name|g_param_spec_int
argument_list|(
literal|"width"
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
operator||
name|G_PARAM_CONSTRUCT_ONLY
argument_list|)
argument_list|)
expr_stmt|;
name|g_object_class_install_property
argument_list|(
name|object_class
argument_list|,
name|PROP_HEIGHT
argument_list|,
name|g_param_spec_int
argument_list|(
literal|"height"
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
DECL|function|gimp_drawable_undo_init (GimpDrawableUndo * undo)
name|gimp_drawable_undo_init
parameter_list|(
name|GimpDrawableUndo
modifier|*
name|undo
parameter_list|)
block|{ }
end_function

begin_function
specifier|static
name|GObject
modifier|*
DECL|function|gimp_drawable_undo_constructor (GType type,guint n_params,GObjectConstructParam * params)
name|gimp_drawable_undo_constructor
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
name|GimpDrawableUndo
modifier|*
name|drawable_undo
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
name|drawable_undo
operator|=
name|GIMP_DRAWABLE_UNDO
argument_list|(
name|object
argument_list|)
expr_stmt|;
name|g_assert
argument_list|(
name|GIMP_IS_DRAWABLE
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
name|g_assert
argument_list|(
name|drawable_undo
operator|->
name|tiles
operator|!=
name|NULL
argument_list|)
expr_stmt|;
name|GIMP_UNDO
argument_list|(
name|object
argument_list|)
operator|->
name|size
operator|+=
name|tile_manager_get_memsize
argument_list|(
name|drawable_undo
operator|->
name|tiles
argument_list|,
name|drawable_undo
operator|->
name|sparse
argument_list|)
expr_stmt|;
return|return
name|object
return|;
block|}
end_function

begin_function
specifier|static
name|void
DECL|function|gimp_drawable_undo_set_property (GObject * object,guint property_id,const GValue * value,GParamSpec * pspec)
name|gimp_drawable_undo_set_property
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
name|GimpDrawableUndo
modifier|*
name|drawable_undo
init|=
name|GIMP_DRAWABLE_UNDO
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
name|PROP_TILES
case|:
name|drawable_undo
operator|->
name|tiles
operator|=
name|tile_manager_ref
argument_list|(
name|g_value_get_pointer
argument_list|(
name|value
argument_list|)
argument_list|)
expr_stmt|;
break|break;
case|case
name|PROP_SPARSE
case|:
name|drawable_undo
operator|->
name|sparse
operator|=
name|g_value_get_boolean
argument_list|(
name|value
argument_list|)
expr_stmt|;
break|break;
case|case
name|PROP_X
case|:
name|drawable_undo
operator|->
name|x
operator|=
name|g_value_get_int
argument_list|(
name|value
argument_list|)
expr_stmt|;
break|break;
case|case
name|PROP_Y
case|:
name|drawable_undo
operator|->
name|y
operator|=
name|g_value_get_int
argument_list|(
name|value
argument_list|)
expr_stmt|;
break|break;
case|case
name|PROP_WIDTH
case|:
name|drawable_undo
operator|->
name|width
operator|=
name|g_value_get_int
argument_list|(
name|value
argument_list|)
expr_stmt|;
break|break;
case|case
name|PROP_HEIGHT
case|:
name|drawable_undo
operator|->
name|height
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
DECL|function|gimp_drawable_undo_get_property (GObject * object,guint property_id,GValue * value,GParamSpec * pspec)
name|gimp_drawable_undo_get_property
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
name|GimpDrawableUndo
modifier|*
name|drawable_undo
init|=
name|GIMP_DRAWABLE_UNDO
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
name|PROP_TILES
case|:
name|g_value_set_pointer
argument_list|(
name|value
argument_list|,
name|drawable_undo
operator|->
name|tiles
argument_list|)
expr_stmt|;
break|break;
case|case
name|PROP_SPARSE
case|:
name|g_value_set_boolean
argument_list|(
name|value
argument_list|,
name|drawable_undo
operator|->
name|sparse
argument_list|)
expr_stmt|;
break|break;
case|case
name|PROP_X
case|:
name|g_value_set_int
argument_list|(
name|value
argument_list|,
name|drawable_undo
operator|->
name|x
argument_list|)
expr_stmt|;
break|break;
case|case
name|PROP_Y
case|:
name|g_value_set_int
argument_list|(
name|value
argument_list|,
name|drawable_undo
operator|->
name|y
argument_list|)
expr_stmt|;
break|break;
case|case
name|PROP_WIDTH
case|:
name|g_value_set_int
argument_list|(
name|value
argument_list|,
name|drawable_undo
operator|->
name|width
argument_list|)
expr_stmt|;
break|break;
case|case
name|PROP_HEIGHT
case|:
name|g_value_set_int
argument_list|(
name|value
argument_list|,
name|drawable_undo
operator|->
name|height
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
DECL|function|gimp_drawable_undo_pop (GimpUndo * undo,GimpUndoMode undo_mode,GimpUndoAccumulator * accum)
name|gimp_drawable_undo_pop
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
name|GimpDrawableUndo
modifier|*
name|drawable_undo
init|=
name|GIMP_DRAWABLE_UNDO
argument_list|(
name|undo
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
name|undo
operator|->
name|size
operator|-=
name|tile_manager_get_memsize
argument_list|(
name|drawable_undo
operator|->
name|tiles
argument_list|,
name|drawable_undo
operator|->
name|sparse
argument_list|)
expr_stmt|;
name|gimp_drawable_swap_pixels
argument_list|(
name|GIMP_DRAWABLE
argument_list|(
name|GIMP_ITEM_UNDO
argument_list|(
name|undo
argument_list|)
operator|->
name|item
argument_list|)
argument_list|,
name|drawable_undo
operator|->
name|tiles
argument_list|,
name|drawable_undo
operator|->
name|sparse
argument_list|,
name|drawable_undo
operator|->
name|x
argument_list|,
name|drawable_undo
operator|->
name|y
argument_list|,
name|drawable_undo
operator|->
name|width
argument_list|,
name|drawable_undo
operator|->
name|height
argument_list|)
expr_stmt|;
name|undo
operator|->
name|size
operator|+=
name|tile_manager_get_memsize
argument_list|(
name|drawable_undo
operator|->
name|tiles
argument_list|,
name|drawable_undo
operator|->
name|sparse
argument_list|)
expr_stmt|;
block|}
end_function

begin_function
specifier|static
name|void
DECL|function|gimp_drawable_undo_free (GimpUndo * undo,GimpUndoMode undo_mode)
name|gimp_drawable_undo_free
parameter_list|(
name|GimpUndo
modifier|*
name|undo
parameter_list|,
name|GimpUndoMode
name|undo_mode
parameter_list|)
block|{
name|GimpDrawableUndo
modifier|*
name|drawable_undo
init|=
name|GIMP_DRAWABLE_UNDO
argument_list|(
name|undo
argument_list|)
decl_stmt|;
if|if
condition|(
name|drawable_undo
operator|->
name|tiles
condition|)
block|{
name|tile_manager_unref
argument_list|(
name|drawable_undo
operator|->
name|tiles
argument_list|)
expr_stmt|;
name|drawable_undo
operator|->
name|tiles
operator|=
name|NULL
expr_stmt|;
block|}
if|if
condition|(
name|drawable_undo
operator|->
name|src2_tiles
condition|)
block|{
name|tile_manager_unref
argument_list|(
name|drawable_undo
operator|->
name|src2_tiles
argument_list|)
expr_stmt|;
name|drawable_undo
operator|->
name|src2_tiles
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

