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
file|"gimpfloatingselundo.h"
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
file|"gimplayer-floating-sel.h"
end_include

begin_function_decl
specifier|static
name|void
name|gimp_floating_sel_undo_constructed
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
name|gimp_floating_sel_undo_pop
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
DECL|function|G_DEFINE_TYPE (GimpFloatingSelUndo,gimp_floating_sel_undo,GIMP_TYPE_ITEM_UNDO)
name|G_DEFINE_TYPE
argument_list|(
argument|GimpFloatingSelUndo
argument_list|,
argument|gimp_floating_sel_undo
argument_list|,
argument|GIMP_TYPE_ITEM_UNDO
argument_list|)
end_macro

begin_define
DECL|macro|parent_class
define|#
directive|define
name|parent_class
value|gimp_floating_sel_undo_parent_class
end_define

begin_function
specifier|static
name|void
name|gimp_floating_sel_undo_class_init
parameter_list|(
name|GimpFloatingSelUndoClass
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
name|gimp_floating_sel_undo_constructed
expr_stmt|;
name|undo_class
operator|->
name|pop
operator|=
name|gimp_floating_sel_undo_pop
expr_stmt|;
block|}
end_function

begin_function
specifier|static
name|void
DECL|function|gimp_floating_sel_undo_init (GimpFloatingSelUndo * undo)
name|gimp_floating_sel_undo_init
parameter_list|(
name|GimpFloatingSelUndo
modifier|*
name|undo
parameter_list|)
block|{ }
end_function

begin_function
specifier|static
name|void
DECL|function|gimp_floating_sel_undo_constructed (GObject * object)
name|gimp_floating_sel_undo_constructed
parameter_list|(
name|GObject
modifier|*
name|object
parameter_list|)
block|{
name|GimpFloatingSelUndo
modifier|*
name|floating_sel_undo
init|=
name|GIMP_FLOATING_SEL_UNDO
argument_list|(
name|object
argument_list|)
decl_stmt|;
name|GimpLayer
modifier|*
name|layer
decl_stmt|;
if|if
condition|(
name|G_OBJECT_CLASS
argument_list|(
name|parent_class
argument_list|)
operator|->
name|constructed
condition|)
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
name|layer
operator|=
name|GIMP_LAYER
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
name|GIMP_UNDO_FS_TO_LAYER
case|:
name|floating_sel_undo
operator|->
name|drawable
operator|=
name|gimp_layer_get_floating_sel_drawable
argument_list|(
name|layer
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
DECL|function|gimp_floating_sel_undo_pop (GimpUndo * undo,GimpUndoMode undo_mode,GimpUndoAccumulator * accum)
name|gimp_floating_sel_undo_pop
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
name|GimpFloatingSelUndo
modifier|*
name|floating_sel_undo
init|=
name|GIMP_FLOATING_SEL_UNDO
argument_list|(
name|undo
argument_list|)
decl_stmt|;
name|GimpLayer
modifier|*
name|floating_layer
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
switch|switch
condition|(
name|undo
operator|->
name|undo_type
condition|)
block|{
case|case
name|GIMP_UNDO_FS_TO_LAYER
case|:
if|if
condition|(
name|undo_mode
operator|==
name|GIMP_UNDO_MODE_UNDO
condition|)
block|{
comment|/*  Update the preview for the floating sel  */
name|gimp_viewable_invalidate_preview
argument_list|(
name|GIMP_VIEWABLE
argument_list|(
name|floating_layer
argument_list|)
argument_list|)
expr_stmt|;
name|gimp_layer_set_floating_sel_drawable
argument_list|(
name|floating_layer
argument_list|,
name|floating_sel_undo
operator|->
name|drawable
argument_list|)
expr_stmt|;
name|gimp_image_set_active_layer
argument_list|(
name|undo
operator|->
name|image
argument_list|,
name|floating_layer
argument_list|)
expr_stmt|;
name|gimp_drawable_attach_floating_sel
argument_list|(
name|gimp_layer_get_floating_sel_drawable
argument_list|(
name|floating_layer
argument_list|)
argument_list|,
name|floating_layer
argument_list|)
expr_stmt|;
block|}
else|else
block|{
name|gimp_drawable_detach_floating_sel
argument_list|(
name|gimp_layer_get_floating_sel_drawable
argument_list|(
name|floating_layer
argument_list|)
argument_list|)
expr_stmt|;
name|gimp_layer_set_floating_sel_drawable
argument_list|(
name|floating_layer
argument_list|,
name|NULL
argument_list|)
expr_stmt|;
block|}
comment|/* When the floating selection is converted to/from a normal        * layer it does something resembling a name change, so emit the        * "name-changed" signal        */
name|gimp_object_name_changed
argument_list|(
name|GIMP_OBJECT
argument_list|(
name|floating_layer
argument_list|)
argument_list|)
expr_stmt|;
name|gimp_drawable_update
argument_list|(
name|GIMP_DRAWABLE
argument_list|(
name|floating_layer
argument_list|)
argument_list|,
literal|0
argument_list|,
literal|0
argument_list|,
name|gimp_item_get_width
argument_list|(
name|GIMP_ITEM
argument_list|(
name|floating_layer
argument_list|)
argument_list|)
argument_list|,
name|gimp_item_get_height
argument_list|(
name|GIMP_ITEM
argument_list|(
name|floating_layer
argument_list|)
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

end_unit

