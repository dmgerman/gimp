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
file|"vectors-types.h"
end_include

begin_include
include|#
directive|include
file|"libgimpbase/gimpbase.h"
end_include

begin_include
include|#
directive|include
file|"core/gimpimage.h"
end_include

begin_include
include|#
directive|include
file|"gimpvectors.h"
end_include

begin_include
include|#
directive|include
file|"gimpvectorsundo.h"
end_include

begin_enum
enum|enum
DECL|enum|__anon2b657dda0103
block|{
DECL|enumerator|PROP_0
name|PROP_0
block|,
DECL|enumerator|PROP_PREV_PARENT
name|PROP_PREV_PARENT
block|,
DECL|enumerator|PROP_PREV_POSITION
name|PROP_PREV_POSITION
block|,
DECL|enumerator|PROP_PREV_VECTORS
name|PROP_PREV_VECTORS
block|}
enum|;
end_enum

begin_function_decl
specifier|static
name|void
name|gimp_vectors_undo_constructed
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
name|gimp_vectors_undo_set_property
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
name|gimp_vectors_undo_get_property
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
name|gimp_vectors_undo_get_memsize
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
name|gimp_vectors_undo_pop
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

begin_macro
DECL|function|G_DEFINE_TYPE (GimpVectorsUndo,gimp_vectors_undo,GIMP_TYPE_ITEM_UNDO)
name|G_DEFINE_TYPE
argument_list|(
argument|GimpVectorsUndo
argument_list|,
argument|gimp_vectors_undo
argument_list|,
argument|GIMP_TYPE_ITEM_UNDO
argument_list|)
end_macro

begin_define
DECL|macro|parent_class
define|#
directive|define
name|parent_class
value|gimp_vectors_undo_parent_class
end_define

begin_function
specifier|static
name|void
name|gimp_vectors_undo_class_init
parameter_list|(
name|GimpVectorsUndoClass
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
name|gimp_vectors_undo_constructed
expr_stmt|;
name|object_class
operator|->
name|set_property
operator|=
name|gimp_vectors_undo_set_property
expr_stmt|;
name|object_class
operator|->
name|get_property
operator|=
name|gimp_vectors_undo_get_property
expr_stmt|;
name|gimp_object_class
operator|->
name|get_memsize
operator|=
name|gimp_vectors_undo_get_memsize
expr_stmt|;
name|undo_class
operator|->
name|pop
operator|=
name|gimp_vectors_undo_pop
expr_stmt|;
name|g_object_class_install_property
argument_list|(
name|object_class
argument_list|,
name|PROP_PREV_PARENT
argument_list|,
name|g_param_spec_object
argument_list|(
literal|"prev-parent"
argument_list|,
name|NULL
argument_list|,
name|NULL
argument_list|,
name|GIMP_TYPE_VECTORS
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
name|PROP_PREV_POSITION
argument_list|,
name|g_param_spec_int
argument_list|(
literal|"prev-position"
argument_list|,
name|NULL
argument_list|,
name|NULL
argument_list|,
literal|0
argument_list|,
name|G_MAXINT
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
name|PROP_PREV_VECTORS
argument_list|,
name|g_param_spec_object
argument_list|(
literal|"prev-vectors"
argument_list|,
name|NULL
argument_list|,
name|NULL
argument_list|,
name|GIMP_TYPE_VECTORS
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
DECL|function|gimp_vectors_undo_init (GimpVectorsUndo * undo)
name|gimp_vectors_undo_init
parameter_list|(
name|GimpVectorsUndo
modifier|*
name|undo
parameter_list|)
block|{ }
end_function

begin_function
specifier|static
name|void
DECL|function|gimp_vectors_undo_constructed (GObject * object)
name|gimp_vectors_undo_constructed
parameter_list|(
name|GObject
modifier|*
name|object
parameter_list|)
block|{
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
name|gimp_assert
argument_list|(
name|GIMP_IS_VECTORS
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
block|}
end_function

begin_function
specifier|static
name|void
DECL|function|gimp_vectors_undo_set_property (GObject * object,guint property_id,const GValue * value,GParamSpec * pspec)
name|gimp_vectors_undo_set_property
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
name|GimpVectorsUndo
modifier|*
name|vectors_undo
init|=
name|GIMP_VECTORS_UNDO
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
name|PROP_PREV_PARENT
case|:
name|vectors_undo
operator|->
name|prev_parent
operator|=
name|g_value_get_object
argument_list|(
name|value
argument_list|)
expr_stmt|;
break|break;
case|case
name|PROP_PREV_POSITION
case|:
name|vectors_undo
operator|->
name|prev_position
operator|=
name|g_value_get_int
argument_list|(
name|value
argument_list|)
expr_stmt|;
break|break;
case|case
name|PROP_PREV_VECTORS
case|:
name|vectors_undo
operator|->
name|prev_vectors
operator|=
name|g_value_get_object
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
DECL|function|gimp_vectors_undo_get_property (GObject * object,guint property_id,GValue * value,GParamSpec * pspec)
name|gimp_vectors_undo_get_property
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
name|GimpVectorsUndo
modifier|*
name|vectors_undo
init|=
name|GIMP_VECTORS_UNDO
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
name|PROP_PREV_PARENT
case|:
name|g_value_set_object
argument_list|(
name|value
argument_list|,
name|vectors_undo
operator|->
name|prev_parent
argument_list|)
expr_stmt|;
break|break;
case|case
name|PROP_PREV_POSITION
case|:
name|g_value_set_int
argument_list|(
name|value
argument_list|,
name|vectors_undo
operator|->
name|prev_position
argument_list|)
expr_stmt|;
break|break;
case|case
name|PROP_PREV_VECTORS
case|:
name|g_value_set_object
argument_list|(
name|value
argument_list|,
name|vectors_undo
operator|->
name|prev_vectors
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
DECL|function|gimp_vectors_undo_get_memsize (GimpObject * object,gint64 * gui_size)
name|gimp_vectors_undo_get_memsize
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
name|GimpItemUndo
modifier|*
name|item_undo
init|=
name|GIMP_ITEM_UNDO
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
operator|!
name|gimp_item_is_attached
argument_list|(
name|item_undo
operator|->
name|item
argument_list|)
condition|)
name|memsize
operator|+=
name|gimp_object_get_memsize
argument_list|(
name|GIMP_OBJECT
argument_list|(
name|item_undo
operator|->
name|item
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
DECL|function|gimp_vectors_undo_pop (GimpUndo * undo,GimpUndoMode undo_mode,GimpUndoAccumulator * accum)
name|gimp_vectors_undo_pop
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
name|GimpVectorsUndo
modifier|*
name|vectors_undo
init|=
name|GIMP_VECTORS_UNDO
argument_list|(
name|undo
argument_list|)
decl_stmt|;
name|GimpVectors
modifier|*
name|vectors
init|=
name|GIMP_VECTORS
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
name|GIMP_UNDO_VECTORS_ADD
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
name|GIMP_UNDO_VECTORS_REMOVE
operator|)
condition|)
block|{
comment|/*  remove vectors  */
comment|/*  record the current parent and position  */
name|vectors_undo
operator|->
name|prev_parent
operator|=
name|gimp_vectors_get_parent
argument_list|(
name|vectors
argument_list|)
expr_stmt|;
name|vectors_undo
operator|->
name|prev_position
operator|=
name|gimp_item_get_index
argument_list|(
name|GIMP_ITEM
argument_list|(
name|vectors
argument_list|)
argument_list|)
expr_stmt|;
name|gimp_image_remove_vectors
argument_list|(
name|undo
operator|->
name|image
argument_list|,
name|vectors
argument_list|,
name|FALSE
argument_list|,
name|vectors_undo
operator|->
name|prev_vectors
argument_list|)
expr_stmt|;
block|}
else|else
block|{
comment|/*  restore vectors  */
comment|/*  record the active vectors  */
name|vectors_undo
operator|->
name|prev_vectors
operator|=
name|gimp_image_get_active_vectors
argument_list|(
name|undo
operator|->
name|image
argument_list|)
expr_stmt|;
name|gimp_image_add_vectors
argument_list|(
name|undo
operator|->
name|image
argument_list|,
name|vectors
argument_list|,
name|vectors_undo
operator|->
name|prev_parent
argument_list|,
name|vectors_undo
operator|->
name|prev_position
argument_list|,
name|FALSE
argument_list|)
expr_stmt|;
block|}
block|}
end_function

end_unit

