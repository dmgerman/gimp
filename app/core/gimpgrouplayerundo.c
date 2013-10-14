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
file|"gimpimage.h"
end_include

begin_include
include|#
directive|include
file|"gimpgrouplayer.h"
end_include

begin_include
include|#
directive|include
file|"gimpgrouplayerundo.h"
end_include

begin_function_decl
specifier|static
name|void
name|gimp_group_layer_undo_constructed
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
name|gimp_group_layer_undo_pop
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
DECL|function|G_DEFINE_TYPE (GimpGroupLayerUndo,gimp_group_layer_undo,GIMP_TYPE_ITEM_UNDO)
name|G_DEFINE_TYPE
argument_list|(
argument|GimpGroupLayerUndo
argument_list|,
argument|gimp_group_layer_undo
argument_list|,
argument|GIMP_TYPE_ITEM_UNDO
argument_list|)
end_macro

begin_define
DECL|macro|parent_class
define|#
directive|define
name|parent_class
value|gimp_group_layer_undo_parent_class
end_define

begin_function
specifier|static
name|void
name|gimp_group_layer_undo_class_init
parameter_list|(
name|GimpGroupLayerUndoClass
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
name|constructed
operator|=
name|gimp_group_layer_undo_constructed
expr_stmt|;
name|undo_class
operator|->
name|pop
operator|=
name|gimp_group_layer_undo_pop
expr_stmt|;
block|}
end_function

begin_function
specifier|static
name|void
DECL|function|gimp_group_layer_undo_init (GimpGroupLayerUndo * undo)
name|gimp_group_layer_undo_init
parameter_list|(
name|GimpGroupLayerUndo
modifier|*
name|undo
parameter_list|)
block|{ }
end_function

begin_function
specifier|static
name|void
DECL|function|gimp_group_layer_undo_constructed (GObject * object)
name|gimp_group_layer_undo_constructed
parameter_list|(
name|GObject
modifier|*
name|object
parameter_list|)
block|{
name|GimpGroupLayerUndo
modifier|*
name|group_layer_undo
init|=
name|GIMP_GROUP_LAYER_UNDO
argument_list|(
name|object
argument_list|)
decl_stmt|;
name|GimpGroupLayer
modifier|*
name|group
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
name|g_assert
argument_list|(
name|GIMP_IS_GROUP_LAYER
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
name|group
operator|=
name|GIMP_GROUP_LAYER
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
name|GIMP_UNDO_GROUP_LAYER_SUSPEND
case|:
case|case
name|GIMP_UNDO_GROUP_LAYER_RESUME
case|:
break|break;
case|case
name|GIMP_UNDO_GROUP_LAYER_CONVERT
case|:
name|group_layer_undo
operator|->
name|prev_type
operator|=
name|gimp_drawable_get_base_type
argument_list|(
name|GIMP_DRAWABLE
argument_list|(
name|group
argument_list|)
argument_list|)
expr_stmt|;
name|group_layer_undo
operator|->
name|prev_precision
operator|=
name|gimp_drawable_get_precision
argument_list|(
name|GIMP_DRAWABLE
argument_list|(
name|group
argument_list|)
argument_list|)
expr_stmt|;
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
DECL|function|gimp_group_layer_undo_pop (GimpUndo * undo,GimpUndoMode undo_mode,GimpUndoAccumulator * accum)
name|gimp_group_layer_undo_pop
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
name|GimpGroupLayerUndo
modifier|*
name|group_layer_undo
init|=
name|GIMP_GROUP_LAYER_UNDO
argument_list|(
name|undo
argument_list|)
decl_stmt|;
name|GimpGroupLayer
modifier|*
name|group
decl_stmt|;
name|group
operator|=
name|GIMP_GROUP_LAYER
argument_list|(
name|GIMP_ITEM_UNDO
argument_list|(
name|undo
argument_list|)
operator|->
name|item
argument_list|)
expr_stmt|;
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
name|GIMP_UNDO_GROUP_LAYER_SUSPEND
case|:
case|case
name|GIMP_UNDO_GROUP_LAYER_RESUME
case|:
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
name|GIMP_UNDO_GROUP_LAYER_SUSPEND
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
name|GIMP_UNDO_GROUP_LAYER_RESUME
operator|)
condition|)
block|{
comment|/*  resume group layer auto-resizing  */
name|gimp_group_layer_resume_resize
argument_list|(
name|group
argument_list|,
name|FALSE
argument_list|)
expr_stmt|;
block|}
else|else
block|{
comment|/*  suspend group layer auto-resizing  */
name|gimp_group_layer_suspend_resize
argument_list|(
name|group
argument_list|,
name|FALSE
argument_list|)
expr_stmt|;
block|}
break|break;
case|case
name|GIMP_UNDO_GROUP_LAYER_CONVERT
case|:
block|{
name|GimpImageBaseType
name|type
decl_stmt|;
name|GimpPrecision
name|precision
decl_stmt|;
name|type
operator|=
name|gimp_drawable_get_base_type
argument_list|(
name|GIMP_DRAWABLE
argument_list|(
name|group
argument_list|)
argument_list|)
expr_stmt|;
name|precision
operator|=
name|gimp_drawable_get_precision
argument_list|(
name|GIMP_DRAWABLE
argument_list|(
name|group
argument_list|)
argument_list|)
expr_stmt|;
name|gimp_drawable_convert_type
argument_list|(
name|GIMP_DRAWABLE
argument_list|(
name|group
argument_list|)
argument_list|,
name|gimp_item_get_image
argument_list|(
name|GIMP_ITEM
argument_list|(
name|group
argument_list|)
argument_list|)
argument_list|,
name|group_layer_undo
operator|->
name|prev_type
argument_list|,
name|group_layer_undo
operator|->
name|prev_precision
argument_list|,
literal|0
argument_list|,
literal|0
argument_list|,
name|FALSE
argument_list|)
expr_stmt|;
name|group_layer_undo
operator|->
name|prev_type
operator|=
name|type
expr_stmt|;
name|group_layer_undo
operator|->
name|prev_precision
operator|=
name|precision
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

