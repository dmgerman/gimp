begin_unit|revision:0.9.5;language:C;cregit-version:0.0.1
begin_comment
comment|/* Gimp - The GNU Image Manipulation Program  * Copyright (C) 1995 Spencer Kimball and Peter Mattis  *  * This program is free software: you can redistribute it and/or modify  * it under the terms of the GNU General Public License as published by  * the Free Software Foundation; either version 3 of the License, or  * (at your option) any later version.  *  * This program is distributed in the hope that it will be useful,  * but WITHOUT ANY WARRANTY; without even the implied warranty of  * MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the  * GNU General Public License for more details.  *  * You should have received a copy of the GNU General Public License  * along with this program.  If not, see<http://www.gnu.org/licenses/>.  */
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
file|"vectors-types.h"
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
file|"gimpvectorspropundo.h"
end_include

begin_function_decl
specifier|static
name|GObject
modifier|*
name|gimp_vectors_prop_undo_constructor
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
name|gimp_vectors_prop_undo_pop
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
DECL|function|G_DEFINE_TYPE (GimpVectorsPropUndo,gimp_vectors_prop_undo,GIMP_TYPE_ITEM_UNDO)
name|G_DEFINE_TYPE
argument_list|(
argument|GimpVectorsPropUndo
argument_list|,
argument|gimp_vectors_prop_undo
argument_list|,
argument|GIMP_TYPE_ITEM_UNDO
argument_list|)
end_macro

begin_define
DECL|macro|parent_class
define|#
directive|define
name|parent_class
value|gimp_vectors_prop_undo_parent_class
end_define

begin_function
specifier|static
name|void
name|gimp_vectors_prop_undo_class_init
parameter_list|(
name|GimpVectorsPropUndoClass
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
name|gimp_vectors_prop_undo_constructor
expr_stmt|;
name|undo_class
operator|->
name|pop
operator|=
name|gimp_vectors_prop_undo_pop
expr_stmt|;
block|}
end_function

begin_function
specifier|static
name|void
DECL|function|gimp_vectors_prop_undo_init (GimpVectorsPropUndo * undo)
name|gimp_vectors_prop_undo_init
parameter_list|(
name|GimpVectorsPropUndo
modifier|*
name|undo
parameter_list|)
block|{ }
end_function

begin_function
specifier|static
name|GObject
modifier|*
DECL|function|gimp_vectors_prop_undo_constructor (GType type,guint n_params,GObjectConstructParam * params)
name|gimp_vectors_prop_undo_constructor
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
name|GimpVectorsPropUndo
modifier|*
name|vectors_prop_undo
decl_stmt|;
name|GimpImage
modifier|*
name|image
decl_stmt|;
name|GimpVectors
modifier|*
name|vectors
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
name|vectors_prop_undo
operator|=
name|GIMP_VECTORS_PROP_UNDO
argument_list|(
name|object
argument_list|)
expr_stmt|;
name|g_assert
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
name|image
operator|=
name|GIMP_UNDO
argument_list|(
name|object
argument_list|)
operator|->
name|image
expr_stmt|;
name|vectors
operator|=
name|GIMP_VECTORS
argument_list|(
name|GIMP_ITEM_UNDO
argument_list|(
name|object
argument_list|)
operator|->
name|item
argument_list|)
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
name|GIMP_UNDO_VECTORS_REORDER
case|:
name|vectors_prop_undo
operator|->
name|parent
operator|=
name|GIMP_VECTORS
argument_list|(
name|gimp_viewable_get_parent
argument_list|(
name|GIMP_VIEWABLE
argument_list|(
name|vectors
argument_list|)
argument_list|)
argument_list|)
expr_stmt|;
name|vectors_prop_undo
operator|->
name|position
operator|=
name|gimp_item_get_index
argument_list|(
name|GIMP_ITEM
argument_list|(
name|vectors
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
DECL|function|gimp_vectors_prop_undo_pop (GimpUndo * undo,GimpUndoMode undo_mode,GimpUndoAccumulator * accum)
name|gimp_vectors_prop_undo_pop
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
name|GimpVectorsPropUndo
modifier|*
name|vectors_prop_undo
init|=
name|GIMP_VECTORS_PROP_UNDO
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
switch|switch
condition|(
name|undo
operator|->
name|undo_type
condition|)
block|{
case|case
name|GIMP_UNDO_VECTORS_REORDER
case|:
block|{
name|GimpVectors
modifier|*
name|parent
decl_stmt|;
name|gint
name|position
decl_stmt|;
name|parent
operator|=
name|GIMP_VECTORS
argument_list|(
name|gimp_viewable_get_parent
argument_list|(
name|GIMP_VIEWABLE
argument_list|(
name|vectors
argument_list|)
argument_list|)
argument_list|)
expr_stmt|;
name|position
operator|=
name|gimp_item_get_index
argument_list|(
name|GIMP_ITEM
argument_list|(
name|vectors
argument_list|)
argument_list|)
expr_stmt|;
name|gimp_image_reorder_vectors
argument_list|(
name|undo
operator|->
name|image
argument_list|,
name|vectors
argument_list|,
name|vectors_prop_undo
operator|->
name|parent
argument_list|,
name|vectors_prop_undo
operator|->
name|position
argument_list|,
name|FALSE
argument_list|,
name|NULL
argument_list|)
expr_stmt|;
name|vectors_prop_undo
operator|->
name|parent
operator|=
name|parent
expr_stmt|;
name|vectors_prop_undo
operator|->
name|position
operator|=
name|position
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

end_unit

