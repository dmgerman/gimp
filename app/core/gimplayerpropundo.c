begin_unit|revision:0.9.5;language:C;cregit-version:0.0.1
begin_comment
comment|/* Gimp - The GNU Image Manipulation Program  * Copyright (C) 1995 Spencer Kimball and Peter Mattis  *  * This program is free software; you can redistribute it and/or modify  * it under the terms of the GNU General Public License as published by  * the Free Software Foundation; either version 2 of the License, or  * (at your option) any later version.  *  * This program is distributed in the hope that it will be useful,  * but WITHOUT ANY WARRANTY; without even the implied warranty of  * MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the  * GNU General Public License for more details.  *  * You should have received a copy of the GNU General Public License  * along with this program; if not, write to the Free Software  * Foundation, Inc., 59 Temple Place - Suite 330, Boston, MA 02111-1307, USA.  */
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
file|"gimplayerpropundo.h"
end_include

begin_function_decl
specifier|static
name|GObject
modifier|*
name|gimp_layer_prop_undo_constructor
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
name|gimp_layer_prop_undo_pop
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
DECL|function|G_DEFINE_TYPE (GimpLayerPropUndo,gimp_layer_prop_undo,GIMP_TYPE_ITEM_UNDO)
name|G_DEFINE_TYPE
argument_list|(
argument|GimpLayerPropUndo
argument_list|,
argument|gimp_layer_prop_undo
argument_list|,
argument|GIMP_TYPE_ITEM_UNDO
argument_list|)
end_macro

begin_define
DECL|macro|parent_class
define|#
directive|define
name|parent_class
value|gimp_layer_prop_undo_parent_class
end_define

begin_function
specifier|static
name|void
name|gimp_layer_prop_undo_class_init
parameter_list|(
name|GimpLayerPropUndoClass
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
name|gimp_layer_prop_undo_constructor
expr_stmt|;
name|undo_class
operator|->
name|pop
operator|=
name|gimp_layer_prop_undo_pop
expr_stmt|;
block|}
end_function

begin_function
specifier|static
name|void
DECL|function|gimp_layer_prop_undo_init (GimpLayerPropUndo * undo)
name|gimp_layer_prop_undo_init
parameter_list|(
name|GimpLayerPropUndo
modifier|*
name|undo
parameter_list|)
block|{ }
end_function

begin_function
specifier|static
name|GObject
modifier|*
DECL|function|gimp_layer_prop_undo_constructor (GType type,guint n_params,GObjectConstructParam * params)
name|gimp_layer_prop_undo_constructor
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
name|GimpLayerPropUndo
modifier|*
name|layer_prop_undo
decl_stmt|;
name|GimpImage
modifier|*
name|image
decl_stmt|;
name|GimpLayer
modifier|*
name|layer
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
name|layer_prop_undo
operator|=
name|GIMP_LAYER_PROP_UNDO
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
name|image
operator|=
name|GIMP_UNDO
argument_list|(
name|object
argument_list|)
operator|->
name|image
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
name|layer_prop_undo
operator|->
name|position
operator|=
name|gimp_image_get_layer_index
argument_list|(
name|image
argument_list|,
name|layer
argument_list|)
expr_stmt|;
name|layer_prop_undo
operator|->
name|mode
operator|=
name|gimp_layer_get_mode
argument_list|(
name|layer
argument_list|)
expr_stmt|;
name|layer_prop_undo
operator|->
name|opacity
operator|=
name|gimp_layer_get_opacity
argument_list|(
name|layer
argument_list|)
expr_stmt|;
name|layer_prop_undo
operator|->
name|lock_alpha
operator|=
name|gimp_layer_get_lock_alpha
argument_list|(
name|layer
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
DECL|function|gimp_layer_prop_undo_pop (GimpUndo * undo,GimpUndoMode undo_mode,GimpUndoAccumulator * accum)
name|gimp_layer_prop_undo_pop
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
name|GimpLayerPropUndo
modifier|*
name|layer_prop_undo
init|=
name|GIMP_LAYER_PROP_UNDO
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
name|undo
operator|->
name|undo_type
operator|==
name|GIMP_UNDO_LAYER_REPOSITION
condition|)
block|{
name|gint
name|position
decl_stmt|;
name|position
operator|=
name|gimp_image_get_layer_index
argument_list|(
name|undo
operator|->
name|image
argument_list|,
name|layer
argument_list|)
expr_stmt|;
name|gimp_image_position_layer
argument_list|(
name|undo
operator|->
name|image
argument_list|,
name|layer
argument_list|,
name|layer_prop_undo
operator|->
name|position
argument_list|,
name|FALSE
argument_list|,
name|NULL
argument_list|)
expr_stmt|;
name|layer_prop_undo
operator|->
name|position
operator|=
name|position
expr_stmt|;
block|}
elseif|else
if|if
condition|(
name|undo
operator|->
name|undo_type
operator|==
name|GIMP_UNDO_LAYER_MODE
condition|)
block|{
name|GimpLayerModeEffects
name|mode
decl_stmt|;
name|mode
operator|=
name|gimp_layer_get_mode
argument_list|(
name|layer
argument_list|)
expr_stmt|;
name|gimp_layer_set_mode
argument_list|(
name|layer
argument_list|,
name|layer_prop_undo
operator|->
name|mode
argument_list|,
name|FALSE
argument_list|)
expr_stmt|;
name|layer_prop_undo
operator|->
name|mode
operator|=
name|mode
expr_stmt|;
block|}
elseif|else
if|if
condition|(
name|undo
operator|->
name|undo_type
operator|==
name|GIMP_UNDO_LAYER_OPACITY
condition|)
block|{
name|gdouble
name|opacity
decl_stmt|;
name|opacity
operator|=
name|gimp_layer_get_opacity
argument_list|(
name|layer
argument_list|)
expr_stmt|;
name|gimp_layer_set_opacity
argument_list|(
name|layer
argument_list|,
name|layer_prop_undo
operator|->
name|opacity
argument_list|,
name|FALSE
argument_list|)
expr_stmt|;
name|layer_prop_undo
operator|->
name|opacity
operator|=
name|opacity
expr_stmt|;
block|}
elseif|else
if|if
condition|(
name|undo
operator|->
name|undo_type
operator|==
name|GIMP_UNDO_LAYER_LOCK_ALPHA
condition|)
block|{
name|gboolean
name|lock_alpha
decl_stmt|;
name|lock_alpha
operator|=
name|gimp_layer_get_lock_alpha
argument_list|(
name|layer
argument_list|)
expr_stmt|;
name|gimp_layer_set_lock_alpha
argument_list|(
name|layer
argument_list|,
name|layer_prop_undo
operator|->
name|lock_alpha
argument_list|,
name|FALSE
argument_list|)
expr_stmt|;
name|layer_prop_undo
operator|->
name|lock_alpha
operator|=
name|lock_alpha
expr_stmt|;
block|}
else|else
block|{
name|g_assert_not_reached
argument_list|()
expr_stmt|;
block|}
block|}
end_function

end_unit

