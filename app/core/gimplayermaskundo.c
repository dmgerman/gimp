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
file|"core-types.h"
end_include

begin_include
include|#
directive|include
file|"gimpimage.h"
end_include

begin_include
include|#
directive|include
file|"gimplayer.h"
end_include

begin_include
include|#
directive|include
file|"gimplayermask.h"
end_include

begin_include
include|#
directive|include
file|"gimplayermaskundo.h"
end_include

begin_enum
enum|enum
DECL|enum|__anon28a591a10103
block|{
DECL|enumerator|PROP_0
name|PROP_0
block|,
DECL|enumerator|PROP_LAYER_MASK
name|PROP_LAYER_MASK
block|}
enum|;
end_enum

begin_function_decl
specifier|static
name|GObject
modifier|*
name|gimp_layer_mask_undo_constructor
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
name|gimp_layer_mask_undo_set_property
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
name|gimp_layer_mask_undo_get_property
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
name|gimp_layer_mask_undo_get_memsize
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
name|gimp_layer_mask_undo_pop
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
name|gimp_layer_mask_undo_free
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
DECL|function|G_DEFINE_TYPE (GimpLayerMaskUndo,gimp_layer_mask_undo,GIMP_TYPE_ITEM_UNDO)
name|G_DEFINE_TYPE
argument_list|(
argument|GimpLayerMaskUndo
argument_list|,
argument|gimp_layer_mask_undo
argument_list|,
argument|GIMP_TYPE_ITEM_UNDO
argument_list|)
end_macro

begin_define
DECL|macro|parent_class
define|#
directive|define
name|parent_class
value|gimp_layer_mask_undo_parent_class
end_define

begin_function
specifier|static
name|void
name|gimp_layer_mask_undo_class_init
parameter_list|(
name|GimpLayerMaskUndoClass
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
name|gimp_layer_mask_undo_constructor
expr_stmt|;
name|object_class
operator|->
name|set_property
operator|=
name|gimp_layer_mask_undo_set_property
expr_stmt|;
name|object_class
operator|->
name|get_property
operator|=
name|gimp_layer_mask_undo_get_property
expr_stmt|;
name|gimp_object_class
operator|->
name|get_memsize
operator|=
name|gimp_layer_mask_undo_get_memsize
expr_stmt|;
name|undo_class
operator|->
name|pop
operator|=
name|gimp_layer_mask_undo_pop
expr_stmt|;
name|undo_class
operator|->
name|free
operator|=
name|gimp_layer_mask_undo_free
expr_stmt|;
name|g_object_class_install_property
argument_list|(
name|object_class
argument_list|,
name|PROP_LAYER_MASK
argument_list|,
name|g_param_spec_object
argument_list|(
literal|"layer-mask"
argument_list|,
name|NULL
argument_list|,
name|NULL
argument_list|,
name|GIMP_TYPE_LAYER_MASK
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
DECL|function|gimp_layer_mask_undo_init (GimpLayerMaskUndo * undo)
name|gimp_layer_mask_undo_init
parameter_list|(
name|GimpLayerMaskUndo
modifier|*
name|undo
parameter_list|)
block|{ }
end_function

begin_function
specifier|static
name|GObject
modifier|*
DECL|function|gimp_layer_mask_undo_constructor (GType type,guint n_params,GObjectConstructParam * params)
name|gimp_layer_mask_undo_constructor
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
name|GimpLayerMaskUndo
modifier|*
name|layer_mask_undo
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
name|layer_mask_undo
operator|=
name|GIMP_LAYER_MASK_UNDO
argument_list|(
name|object
argument_list|)
expr_stmt|;
name|g_assert
argument_list|(
name|GIMP_IS_LAYER
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
name|GIMP_IS_LAYER_MASK
argument_list|(
name|layer_mask_undo
operator|->
name|layer_mask
argument_list|)
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
DECL|function|gimp_layer_mask_undo_set_property (GObject * object,guint property_id,const GValue * value,GParamSpec * pspec)
name|gimp_layer_mask_undo_set_property
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
name|GimpLayerMaskUndo
modifier|*
name|layer_mask_undo
init|=
name|GIMP_LAYER_MASK_UNDO
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
name|PROP_LAYER_MASK
case|:
name|layer_mask_undo
operator|->
name|layer_mask
operator|=
name|g_value_dup_object
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
DECL|function|gimp_layer_mask_undo_get_property (GObject * object,guint property_id,GValue * value,GParamSpec * pspec)
name|gimp_layer_mask_undo_get_property
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
name|GimpLayerMaskUndo
modifier|*
name|layer_mask_undo
init|=
name|GIMP_LAYER_MASK_UNDO
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
name|PROP_LAYER_MASK
case|:
name|g_value_set_object
argument_list|(
name|value
argument_list|,
name|layer_mask_undo
operator|->
name|layer_mask
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
DECL|function|gimp_layer_mask_undo_get_memsize (GimpObject * object,gint64 * gui_size)
name|gimp_layer_mask_undo_get_memsize
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
name|GimpLayerMaskUndo
modifier|*
name|layer_mask_undo
init|=
name|GIMP_LAYER_MASK_UNDO
argument_list|(
name|object
argument_list|)
decl_stmt|;
name|GimpLayer
modifier|*
name|layer
init|=
name|GIMP_LAYER
argument_list|(
name|GIMP_ITEM_UNDO
argument_list|(
name|object
argument_list|)
operator|->
name|item
argument_list|)
decl_stmt|;
name|gint64
name|memsize
init|=
literal|0
decl_stmt|;
comment|/* don't use !gimp_item_is_attached() here */
if|if
condition|(
name|gimp_layer_get_mask
argument_list|(
name|layer
argument_list|)
operator|!=
name|layer_mask_undo
operator|->
name|layer_mask
condition|)
name|memsize
operator|+=
name|gimp_object_get_memsize
argument_list|(
name|GIMP_OBJECT
argument_list|(
name|layer_mask_undo
operator|->
name|layer_mask
argument_list|)
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
DECL|function|gimp_layer_mask_undo_pop (GimpUndo * undo,GimpUndoMode undo_mode,GimpUndoAccumulator * accum)
name|gimp_layer_mask_undo_pop
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
name|GimpLayerMaskUndo
modifier|*
name|layer_mask_undo
init|=
name|GIMP_LAYER_MASK_UNDO
argument_list|(
name|undo
argument_list|)
decl_stmt|;
name|GimpLayer
modifier|*
name|layer
init|=
name|GIMP_LAYER
argument_list|(
name|GIMP_ITEM_UNDO
argument_list|(
name|undo
argument_list|)
operator|->
name|item
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
if|if
condition|(
operator|(
name|undo_mode
operator|==
name|GIMP_UNDO_MODE_UNDO
operator|&&
name|undo
operator|->
name|undo_type
operator|==
name|GIMP_UNDO_LAYER_MASK_ADD
operator|)
operator|||
operator|(
name|undo_mode
operator|==
name|GIMP_UNDO_MODE_REDO
operator|&&
name|undo
operator|->
name|undo_type
operator|==
name|GIMP_UNDO_LAYER_MASK_REMOVE
operator|)
condition|)
block|{
comment|/*  remove layer mask  */
name|gimp_layer_apply_mask
argument_list|(
name|layer
argument_list|,
name|GIMP_MASK_DISCARD
argument_list|,
name|FALSE
argument_list|)
expr_stmt|;
block|}
else|else
block|{
comment|/*  restore layer mask  */
name|gimp_layer_add_mask
argument_list|(
name|layer
argument_list|,
name|layer_mask_undo
operator|->
name|layer_mask
argument_list|,
name|FALSE
argument_list|,
name|NULL
argument_list|)
expr_stmt|;
name|GIMP_ITEM
argument_list|(
name|layer_mask_undo
operator|->
name|layer_mask
argument_list|)
operator|->
name|removed
operator|=
name|FALSE
expr_stmt|;
block|}
block|}
end_function

begin_function
specifier|static
name|void
DECL|function|gimp_layer_mask_undo_free (GimpUndo * undo,GimpUndoMode undo_mode)
name|gimp_layer_mask_undo_free
parameter_list|(
name|GimpUndo
modifier|*
name|undo
parameter_list|,
name|GimpUndoMode
name|undo_mode
parameter_list|)
block|{
name|GimpLayerMaskUndo
modifier|*
name|layer_mask_undo
init|=
name|GIMP_LAYER_MASK_UNDO
argument_list|(
name|undo
argument_list|)
decl_stmt|;
if|if
condition|(
name|layer_mask_undo
operator|->
name|layer_mask
condition|)
block|{
name|g_object_unref
argument_list|(
name|layer_mask_undo
operator|->
name|layer_mask
argument_list|)
expr_stmt|;
name|layer_mask_undo
operator|->
name|layer_mask
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

