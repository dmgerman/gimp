begin_unit|revision:0.9.5;language:C;cregit-version:0.0.1
begin_comment
comment|/* The GIMP -- an image manipulation program  * Copyright (C) 1995 Spencer Kimball and Peter Mattis  *  * This program is free software; you can redistribute it and/or modify  * it under the terms of the GNU General Public License as published by  * the Free Software Foundation; either version 2 of the License, or  * (at your option) any later version.  *  * This program is distributed in the hope that it will be useful,  * but WITHOUT ANY WARRANTY; without even the implied warranty of  * MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the  * GNU General Public License for more details.  *  * You should have received a copy of the GNU General Public License  * along with this program; if not, write to the Free Software  * Foundation, Inc., 59 Temple Place - Suite 330, Boston, MA 02111-1307, USA.  */
end_comment

begin_include
include|#
directive|include
file|"config.h"
end_include

begin_include
include|#
directive|include
file|<stdlib.h>
end_include

begin_include
include|#
directive|include
file|<string.h>
end_include

begin_include
include|#
directive|include
file|<glib-object.h>
end_include

begin_include
include|#
directive|include
file|"libgimpmath/gimpmath.h"
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
file|"gimpmarshal.h"
end_include

begin_include
include|#
directive|include
file|"gimp-intl.h"
end_include

begin_enum
enum|enum
DECL|enum|__anon2b7678500103
block|{
DECL|enumerator|APPLY_CHANGED
name|APPLY_CHANGED
block|,
DECL|enumerator|EDIT_CHANGED
name|EDIT_CHANGED
block|,
DECL|enumerator|SHOW_CHANGED
name|SHOW_CHANGED
block|,
DECL|enumerator|LAST_SIGNAL
name|LAST_SIGNAL
block|}
enum|;
end_enum

begin_function_decl
specifier|static
name|void
name|gimp_layer_mask_class_init
parameter_list|(
name|GimpLayerMaskClass
modifier|*
name|klass
parameter_list|)
function_decl|;
end_function_decl

begin_function_decl
specifier|static
name|void
name|gimp_layer_mask_init
parameter_list|(
name|GimpLayerMask
modifier|*
name|layer_mask
parameter_list|)
function_decl|;
end_function_decl

begin_function_decl
specifier|static
name|gboolean
name|gimp_layer_mask_is_attached
parameter_list|(
name|GimpItem
modifier|*
name|item
parameter_list|)
function_decl|;
end_function_decl

begin_function_decl
specifier|static
name|GimpItem
modifier|*
name|gimp_layer_mask_duplicate
parameter_list|(
name|GimpItem
modifier|*
name|item
parameter_list|,
name|GType
name|new_type
parameter_list|,
name|gboolean
name|add_alpha
parameter_list|)
function_decl|;
end_function_decl

begin_function_decl
specifier|static
name|gboolean
name|gimp_layer_mask_rename
parameter_list|(
name|GimpItem
modifier|*
name|item
parameter_list|,
specifier|const
name|gchar
modifier|*
name|new_name
parameter_list|,
specifier|const
name|gchar
modifier|*
name|undo_desc
parameter_list|)
function_decl|;
end_function_decl

begin_decl_stmt
DECL|variable|layer_mask_signals
specifier|static
name|guint
name|layer_mask_signals
index|[
name|LAST_SIGNAL
index|]
init|=
block|{
literal|0
block|}
decl_stmt|;
end_decl_stmt

begin_decl_stmt
DECL|variable|parent_class
specifier|static
name|GimpChannelClass
modifier|*
name|parent_class
init|=
name|NULL
decl_stmt|;
end_decl_stmt

begin_function
name|GType
DECL|function|gimp_layer_mask_get_type (void)
name|gimp_layer_mask_get_type
parameter_list|(
name|void
parameter_list|)
block|{
specifier|static
name|GType
name|layer_mask_type
init|=
literal|0
decl_stmt|;
if|if
condition|(
operator|!
name|layer_mask_type
condition|)
block|{
specifier|static
specifier|const
name|GTypeInfo
name|layer_mask_info
init|=
block|{
sizeof|sizeof
argument_list|(
name|GimpLayerMaskClass
argument_list|)
block|,
operator|(
name|GBaseInitFunc
operator|)
name|NULL
block|,
operator|(
name|GBaseFinalizeFunc
operator|)
name|NULL
block|,
operator|(
name|GClassInitFunc
operator|)
name|gimp_layer_mask_class_init
block|,
name|NULL
block|,
comment|/* class_finalize */
name|NULL
block|,
comment|/* class_data     */
sizeof|sizeof
argument_list|(
name|GimpLayerMask
argument_list|)
block|,
literal|0
block|,
comment|/* n_preallocs    */
operator|(
name|GInstanceInitFunc
operator|)
name|gimp_layer_mask_init
block|,       }
decl_stmt|;
name|layer_mask_type
operator|=
name|g_type_register_static
argument_list|(
name|GIMP_TYPE_CHANNEL
argument_list|,
literal|"GimpLayerMask"
argument_list|,
operator|&
name|layer_mask_info
argument_list|,
literal|0
argument_list|)
expr_stmt|;
block|}
return|return
name|layer_mask_type
return|;
block|}
end_function

begin_function
specifier|static
name|void
DECL|function|gimp_layer_mask_class_init (GimpLayerMaskClass * klass)
name|gimp_layer_mask_class_init
parameter_list|(
name|GimpLayerMaskClass
modifier|*
name|klass
parameter_list|)
block|{
name|GimpViewableClass
modifier|*
name|viewable_class
init|=
name|GIMP_VIEWABLE_CLASS
argument_list|(
name|klass
argument_list|)
decl_stmt|;
name|GimpItemClass
modifier|*
name|item_class
init|=
name|GIMP_ITEM_CLASS
argument_list|(
name|klass
argument_list|)
decl_stmt|;
name|parent_class
operator|=
name|g_type_class_peek_parent
argument_list|(
name|klass
argument_list|)
expr_stmt|;
name|layer_mask_signals
index|[
name|APPLY_CHANGED
index|]
operator|=
name|g_signal_new
argument_list|(
literal|"apply_changed"
argument_list|,
name|G_TYPE_FROM_CLASS
argument_list|(
name|klass
argument_list|)
argument_list|,
name|G_SIGNAL_RUN_FIRST
argument_list|,
name|G_STRUCT_OFFSET
argument_list|(
name|GimpLayerMaskClass
argument_list|,
name|apply_changed
argument_list|)
argument_list|,
name|NULL
argument_list|,
name|NULL
argument_list|,
name|gimp_marshal_VOID__VOID
argument_list|,
name|G_TYPE_NONE
argument_list|,
literal|0
argument_list|)
expr_stmt|;
name|layer_mask_signals
index|[
name|EDIT_CHANGED
index|]
operator|=
name|g_signal_new
argument_list|(
literal|"edit_changed"
argument_list|,
name|G_TYPE_FROM_CLASS
argument_list|(
name|klass
argument_list|)
argument_list|,
name|G_SIGNAL_RUN_FIRST
argument_list|,
name|G_STRUCT_OFFSET
argument_list|(
name|GimpLayerMaskClass
argument_list|,
name|edit_changed
argument_list|)
argument_list|,
name|NULL
argument_list|,
name|NULL
argument_list|,
name|gimp_marshal_VOID__VOID
argument_list|,
name|G_TYPE_NONE
argument_list|,
literal|0
argument_list|)
expr_stmt|;
name|layer_mask_signals
index|[
name|SHOW_CHANGED
index|]
operator|=
name|g_signal_new
argument_list|(
literal|"show_changed"
argument_list|,
name|G_TYPE_FROM_CLASS
argument_list|(
name|klass
argument_list|)
argument_list|,
name|G_SIGNAL_RUN_FIRST
argument_list|,
name|G_STRUCT_OFFSET
argument_list|(
name|GimpLayerMaskClass
argument_list|,
name|show_changed
argument_list|)
argument_list|,
name|NULL
argument_list|,
name|NULL
argument_list|,
name|gimp_marshal_VOID__VOID
argument_list|,
name|G_TYPE_NONE
argument_list|,
literal|0
argument_list|)
expr_stmt|;
name|viewable_class
operator|->
name|default_stock_id
operator|=
literal|"gimp-layer-mask"
expr_stmt|;
name|item_class
operator|->
name|is_attached
operator|=
name|gimp_layer_mask_is_attached
expr_stmt|;
name|item_class
operator|->
name|duplicate
operator|=
name|gimp_layer_mask_duplicate
expr_stmt|;
name|item_class
operator|->
name|rename
operator|=
name|gimp_layer_mask_rename
expr_stmt|;
name|item_class
operator|->
name|translate_desc
operator|=
name|_
argument_list|(
literal|"Move Layer Mask"
argument_list|)
expr_stmt|;
block|}
end_function

begin_function
specifier|static
name|void
DECL|function|gimp_layer_mask_init (GimpLayerMask * layer_mask)
name|gimp_layer_mask_init
parameter_list|(
name|GimpLayerMask
modifier|*
name|layer_mask
parameter_list|)
block|{
name|layer_mask
operator|->
name|layer
operator|=
name|NULL
expr_stmt|;
name|layer_mask
operator|->
name|apply_mask
operator|=
name|TRUE
expr_stmt|;
name|layer_mask
operator|->
name|edit_mask
operator|=
name|TRUE
expr_stmt|;
name|layer_mask
operator|->
name|show_mask
operator|=
name|FALSE
expr_stmt|;
block|}
end_function

begin_function
specifier|static
name|gboolean
DECL|function|gimp_layer_mask_is_attached (GimpItem * item)
name|gimp_layer_mask_is_attached
parameter_list|(
name|GimpItem
modifier|*
name|item
parameter_list|)
block|{
name|GimpLayerMask
modifier|*
name|mask
init|=
name|GIMP_LAYER_MASK
argument_list|(
name|item
argument_list|)
decl_stmt|;
name|GimpLayer
modifier|*
name|layer
init|=
name|gimp_layer_mask_get_layer
argument_list|(
name|mask
argument_list|)
decl_stmt|;
return|return
operator|(
name|GIMP_IS_IMAGE
argument_list|(
name|item
operator|->
name|gimage
argument_list|)
operator|&&
name|GIMP_IS_LAYER
argument_list|(
name|layer
argument_list|)
operator|&&
name|gimp_layer_get_mask
argument_list|(
name|layer
argument_list|)
operator|==
name|mask
operator|&&
name|gimp_item_is_attached
argument_list|(
name|GIMP_ITEM
argument_list|(
name|layer
argument_list|)
argument_list|)
operator|)
return|;
block|}
end_function

begin_function
specifier|static
name|GimpItem
modifier|*
DECL|function|gimp_layer_mask_duplicate (GimpItem * item,GType new_type,gboolean add_alpha)
name|gimp_layer_mask_duplicate
parameter_list|(
name|GimpItem
modifier|*
name|item
parameter_list|,
name|GType
name|new_type
parameter_list|,
name|gboolean
name|add_alpha
parameter_list|)
block|{
name|GimpLayerMask
modifier|*
name|layer_mask
decl_stmt|;
name|GimpItem
modifier|*
name|new_item
decl_stmt|;
name|GimpLayerMask
modifier|*
name|new_layer_mask
decl_stmt|;
name|g_return_val_if_fail
argument_list|(
name|g_type_is_a
argument_list|(
name|new_type
argument_list|,
name|GIMP_TYPE_DRAWABLE
argument_list|)
argument_list|,
name|NULL
argument_list|)
expr_stmt|;
name|new_item
operator|=
name|GIMP_ITEM_CLASS
argument_list|(
name|parent_class
argument_list|)
operator|->
name|duplicate
argument_list|(
name|item
argument_list|,
name|new_type
argument_list|,
name|add_alpha
argument_list|)
expr_stmt|;
if|if
condition|(
operator|!
name|GIMP_IS_LAYER_MASK
argument_list|(
name|new_item
argument_list|)
condition|)
return|return
name|new_item
return|;
name|layer_mask
operator|=
name|GIMP_LAYER_MASK
argument_list|(
name|item
argument_list|)
expr_stmt|;
name|new_layer_mask
operator|=
name|GIMP_LAYER_MASK
argument_list|(
name|new_item
argument_list|)
expr_stmt|;
name|new_layer_mask
operator|->
name|apply_mask
operator|=
name|layer_mask
operator|->
name|apply_mask
expr_stmt|;
name|new_layer_mask
operator|->
name|edit_mask
operator|=
name|layer_mask
operator|->
name|edit_mask
expr_stmt|;
name|new_layer_mask
operator|->
name|show_mask
operator|=
name|layer_mask
operator|->
name|show_mask
expr_stmt|;
return|return
name|new_item
return|;
block|}
end_function

begin_function
specifier|static
name|gboolean
DECL|function|gimp_layer_mask_rename (GimpItem * item,const gchar * new_name,const gchar * undo_desc)
name|gimp_layer_mask_rename
parameter_list|(
name|GimpItem
modifier|*
name|item
parameter_list|,
specifier|const
name|gchar
modifier|*
name|new_name
parameter_list|,
specifier|const
name|gchar
modifier|*
name|undo_desc
parameter_list|)
block|{
comment|/* reject renaming, layer masks are always named "<layer name> mask"  */
return|return
name|FALSE
return|;
block|}
end_function

begin_function
name|GimpLayerMask
modifier|*
DECL|function|gimp_layer_mask_new (GimpImage * gimage,gint width,gint height,const gchar * name,const GimpRGB * color)
name|gimp_layer_mask_new
parameter_list|(
name|GimpImage
modifier|*
name|gimage
parameter_list|,
name|gint
name|width
parameter_list|,
name|gint
name|height
parameter_list|,
specifier|const
name|gchar
modifier|*
name|name
parameter_list|,
specifier|const
name|GimpRGB
modifier|*
name|color
parameter_list|)
block|{
name|GimpLayerMask
modifier|*
name|layer_mask
decl_stmt|;
name|layer_mask
operator|=
name|g_object_new
argument_list|(
name|GIMP_TYPE_LAYER_MASK
argument_list|,
name|NULL
argument_list|)
expr_stmt|;
name|gimp_drawable_configure
argument_list|(
name|GIMP_DRAWABLE
argument_list|(
name|layer_mask
argument_list|)
argument_list|,
name|gimage
argument_list|,
literal|0
argument_list|,
literal|0
argument_list|,
name|width
argument_list|,
name|height
argument_list|,
name|GIMP_GRAY_IMAGE
argument_list|,
name|name
argument_list|)
expr_stmt|;
comment|/*  set the layer_mask color and opacity  */
name|GIMP_CHANNEL
argument_list|(
name|layer_mask
argument_list|)
operator|->
name|color
operator|=
operator|*
name|color
expr_stmt|;
name|GIMP_CHANNEL
argument_list|(
name|layer_mask
argument_list|)
operator|->
name|show_masked
operator|=
name|TRUE
expr_stmt|;
comment|/*  selection mask variables  */
name|GIMP_CHANNEL
argument_list|(
name|layer_mask
argument_list|)
operator|->
name|x2
operator|=
name|width
expr_stmt|;
name|GIMP_CHANNEL
argument_list|(
name|layer_mask
argument_list|)
operator|->
name|y2
operator|=
name|height
expr_stmt|;
return|return
name|layer_mask
return|;
block|}
end_function

begin_function
name|void
DECL|function|gimp_layer_mask_set_layer (GimpLayerMask * layer_mask,GimpLayer * layer)
name|gimp_layer_mask_set_layer
parameter_list|(
name|GimpLayerMask
modifier|*
name|layer_mask
parameter_list|,
name|GimpLayer
modifier|*
name|layer
parameter_list|)
block|{
name|g_return_if_fail
argument_list|(
name|GIMP_IS_LAYER_MASK
argument_list|(
name|layer_mask
argument_list|)
argument_list|)
expr_stmt|;
name|g_return_if_fail
argument_list|(
name|layer
operator|==
name|NULL
operator|||
name|GIMP_IS_LAYER
argument_list|(
name|layer
argument_list|)
argument_list|)
expr_stmt|;
name|layer_mask
operator|->
name|layer
operator|=
name|layer
expr_stmt|;
if|if
condition|(
name|layer
condition|)
block|{
name|gchar
modifier|*
name|mask_name
decl_stmt|;
name|GIMP_ITEM
argument_list|(
name|layer_mask
argument_list|)
operator|->
name|offset_x
operator|=
name|GIMP_ITEM
argument_list|(
name|layer
argument_list|)
operator|->
name|offset_x
expr_stmt|;
name|GIMP_ITEM
argument_list|(
name|layer_mask
argument_list|)
operator|->
name|offset_y
operator|=
name|GIMP_ITEM
argument_list|(
name|layer
argument_list|)
operator|->
name|offset_y
expr_stmt|;
name|mask_name
operator|=
name|g_strdup_printf
argument_list|(
name|_
argument_list|(
literal|"%s mask"
argument_list|)
argument_list|,
name|gimp_object_get_name
argument_list|(
name|GIMP_OBJECT
argument_list|(
name|layer
argument_list|)
argument_list|)
argument_list|)
expr_stmt|;
name|gimp_object_set_name
argument_list|(
name|GIMP_OBJECT
argument_list|(
name|layer_mask
argument_list|)
argument_list|,
name|mask_name
argument_list|)
expr_stmt|;
name|g_free
argument_list|(
name|mask_name
argument_list|)
expr_stmt|;
block|}
block|}
end_function

begin_function
name|GimpLayer
modifier|*
DECL|function|gimp_layer_mask_get_layer (const GimpLayerMask * layer_mask)
name|gimp_layer_mask_get_layer
parameter_list|(
specifier|const
name|GimpLayerMask
modifier|*
name|layer_mask
parameter_list|)
block|{
name|g_return_val_if_fail
argument_list|(
name|GIMP_IS_LAYER_MASK
argument_list|(
name|layer_mask
argument_list|)
argument_list|,
name|NULL
argument_list|)
expr_stmt|;
return|return
name|layer_mask
operator|->
name|layer
return|;
block|}
end_function

begin_function
name|void
DECL|function|gimp_layer_mask_set_apply (GimpLayerMask * layer_mask,gboolean apply)
name|gimp_layer_mask_set_apply
parameter_list|(
name|GimpLayerMask
modifier|*
name|layer_mask
parameter_list|,
name|gboolean
name|apply
parameter_list|)
block|{
name|g_return_if_fail
argument_list|(
name|GIMP_IS_LAYER_MASK
argument_list|(
name|layer_mask
argument_list|)
argument_list|)
expr_stmt|;
if|if
condition|(
name|layer_mask
operator|->
name|apply_mask
operator|!=
name|apply
condition|)
block|{
name|layer_mask
operator|->
name|apply_mask
operator|=
name|apply
condition|?
name|TRUE
else|:
name|FALSE
expr_stmt|;
if|if
condition|(
name|layer_mask
operator|->
name|layer
condition|)
block|{
name|GimpDrawable
modifier|*
name|drawable
init|=
name|GIMP_DRAWABLE
argument_list|(
name|layer_mask
operator|->
name|layer
argument_list|)
decl_stmt|;
name|gimp_drawable_update
argument_list|(
name|drawable
argument_list|,
literal|0
argument_list|,
literal|0
argument_list|,
name|gimp_item_width
argument_list|(
name|GIMP_ITEM
argument_list|(
name|drawable
argument_list|)
argument_list|)
argument_list|,
name|gimp_item_height
argument_list|(
name|GIMP_ITEM
argument_list|(
name|drawable
argument_list|)
argument_list|)
argument_list|)
expr_stmt|;
block|}
name|g_signal_emit
argument_list|(
name|layer_mask
argument_list|,
name|layer_mask_signals
index|[
name|APPLY_CHANGED
index|]
argument_list|,
literal|0
argument_list|)
expr_stmt|;
block|}
block|}
end_function

begin_function
name|gboolean
DECL|function|gimp_layer_mask_get_apply (const GimpLayerMask * layer_mask)
name|gimp_layer_mask_get_apply
parameter_list|(
specifier|const
name|GimpLayerMask
modifier|*
name|layer_mask
parameter_list|)
block|{
name|g_return_val_if_fail
argument_list|(
name|GIMP_IS_LAYER_MASK
argument_list|(
name|layer_mask
argument_list|)
argument_list|,
name|FALSE
argument_list|)
expr_stmt|;
return|return
name|layer_mask
operator|->
name|apply_mask
return|;
block|}
end_function

begin_function
name|void
DECL|function|gimp_layer_mask_set_edit (GimpLayerMask * layer_mask,gboolean edit)
name|gimp_layer_mask_set_edit
parameter_list|(
name|GimpLayerMask
modifier|*
name|layer_mask
parameter_list|,
name|gboolean
name|edit
parameter_list|)
block|{
name|g_return_if_fail
argument_list|(
name|GIMP_IS_LAYER_MASK
argument_list|(
name|layer_mask
argument_list|)
argument_list|)
expr_stmt|;
if|if
condition|(
name|layer_mask
operator|->
name|edit_mask
operator|!=
name|edit
condition|)
block|{
name|layer_mask
operator|->
name|edit_mask
operator|=
name|edit
condition|?
name|TRUE
else|:
name|FALSE
expr_stmt|;
name|g_signal_emit
argument_list|(
name|layer_mask
argument_list|,
name|layer_mask_signals
index|[
name|EDIT_CHANGED
index|]
argument_list|,
literal|0
argument_list|)
expr_stmt|;
block|}
block|}
end_function

begin_function
name|gboolean
DECL|function|gimp_layer_mask_get_edit (const GimpLayerMask * layer_mask)
name|gimp_layer_mask_get_edit
parameter_list|(
specifier|const
name|GimpLayerMask
modifier|*
name|layer_mask
parameter_list|)
block|{
name|g_return_val_if_fail
argument_list|(
name|GIMP_IS_LAYER_MASK
argument_list|(
name|layer_mask
argument_list|)
argument_list|,
name|FALSE
argument_list|)
expr_stmt|;
return|return
name|layer_mask
operator|->
name|edit_mask
return|;
block|}
end_function

begin_function
name|void
DECL|function|gimp_layer_mask_set_show (GimpLayerMask * layer_mask,gboolean show)
name|gimp_layer_mask_set_show
parameter_list|(
name|GimpLayerMask
modifier|*
name|layer_mask
parameter_list|,
name|gboolean
name|show
parameter_list|)
block|{
name|g_return_if_fail
argument_list|(
name|GIMP_IS_LAYER_MASK
argument_list|(
name|layer_mask
argument_list|)
argument_list|)
expr_stmt|;
if|if
condition|(
name|layer_mask
operator|->
name|show_mask
operator|!=
name|show
condition|)
block|{
name|layer_mask
operator|->
name|show_mask
operator|=
name|show
condition|?
name|TRUE
else|:
name|FALSE
expr_stmt|;
if|if
condition|(
name|layer_mask
operator|->
name|layer
condition|)
block|{
name|GimpDrawable
modifier|*
name|drawable
init|=
name|GIMP_DRAWABLE
argument_list|(
name|layer_mask
operator|->
name|layer
argument_list|)
decl_stmt|;
name|gimp_drawable_update
argument_list|(
name|drawable
argument_list|,
literal|0
argument_list|,
literal|0
argument_list|,
name|gimp_item_width
argument_list|(
name|GIMP_ITEM
argument_list|(
name|drawable
argument_list|)
argument_list|)
argument_list|,
name|gimp_item_height
argument_list|(
name|GIMP_ITEM
argument_list|(
name|drawable
argument_list|)
argument_list|)
argument_list|)
expr_stmt|;
block|}
name|g_signal_emit
argument_list|(
name|layer_mask
argument_list|,
name|layer_mask_signals
index|[
name|SHOW_CHANGED
index|]
argument_list|,
literal|0
argument_list|)
expr_stmt|;
block|}
block|}
end_function

begin_function
name|gboolean
DECL|function|gimp_layer_mask_get_show (const GimpLayerMask * layer_mask)
name|gimp_layer_mask_get_show
parameter_list|(
specifier|const
name|GimpLayerMask
modifier|*
name|layer_mask
parameter_list|)
block|{
name|g_return_val_if_fail
argument_list|(
name|GIMP_IS_LAYER_MASK
argument_list|(
name|layer_mask
argument_list|)
argument_list|,
name|FALSE
argument_list|)
expr_stmt|;
return|return
name|layer_mask
operator|->
name|show_mask
return|;
block|}
end_function

end_unit

