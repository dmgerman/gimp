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
file|"core-types.h"
end_include

begin_include
include|#
directive|include
file|"gegl/gimp-babl.h"
end_include

begin_include
include|#
directive|include
file|"gimperror.h"
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
file|"gimp-intl.h"
end_include

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
name|gboolean
name|gimp_layer_mask_is_content_locked
parameter_list|(
name|GimpItem
modifier|*
name|item
parameter_list|)
function_decl|;
end_function_decl

begin_function_decl
specifier|static
name|gboolean
name|gimp_layer_mask_is_position_locked
parameter_list|(
name|GimpItem
modifier|*
name|item
parameter_list|)
function_decl|;
end_function_decl

begin_function_decl
specifier|static
name|GimpItemTree
modifier|*
name|gimp_layer_mask_get_tree
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
parameter_list|,
name|GError
modifier|*
modifier|*
name|error
parameter_list|)
function_decl|;
end_function_decl

begin_function_decl
specifier|static
name|void
name|gimp_layer_mask_convert_type
parameter_list|(
name|GimpDrawable
modifier|*
name|drawable
parameter_list|,
name|GimpImage
modifier|*
name|dest_image
parameter_list|,
specifier|const
name|Babl
modifier|*
name|new_format
parameter_list|,
name|GimpColorProfile
modifier|*
name|dest_profile
parameter_list|,
name|GeglDitherMethod
name|layer_dither_type
parameter_list|,
name|GeglDitherMethod
name|mask_dither_type
parameter_list|,
name|gboolean
name|push_undo
parameter_list|,
name|GimpProgress
modifier|*
name|progress
parameter_list|)
function_decl|;
end_function_decl

begin_macro
DECL|function|G_DEFINE_TYPE (GimpLayerMask,gimp_layer_mask,GIMP_TYPE_CHANNEL)
name|G_DEFINE_TYPE
argument_list|(
argument|GimpLayerMask
argument_list|,
argument|gimp_layer_mask
argument_list|,
argument|GIMP_TYPE_CHANNEL
argument_list|)
end_macro

begin_define
DECL|macro|parent_class
define|#
directive|define
name|parent_class
value|gimp_layer_mask_parent_class
end_define

begin_function
specifier|static
name|void
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
name|GimpDrawableClass
modifier|*
name|drawable_class
init|=
name|GIMP_DRAWABLE_CLASS
argument_list|(
name|klass
argument_list|)
decl_stmt|;
name|viewable_class
operator|->
name|default_icon_name
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
name|is_content_locked
operator|=
name|gimp_layer_mask_is_content_locked
expr_stmt|;
name|item_class
operator|->
name|is_position_locked
operator|=
name|gimp_layer_mask_is_position_locked
expr_stmt|;
name|item_class
operator|->
name|get_tree
operator|=
name|gimp_layer_mask_get_tree
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
name|C_
argument_list|(
literal|"undo-type"
argument_list|,
literal|"Move Layer Mask"
argument_list|)
expr_stmt|;
name|item_class
operator|->
name|to_selection_desc
operator|=
name|C_
argument_list|(
literal|"undo-type"
argument_list|,
literal|"Layer Mask to Selection"
argument_list|)
expr_stmt|;
name|drawable_class
operator|->
name|convert_type
operator|=
name|gimp_layer_mask_convert_type
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
block|}
end_function

begin_function
specifier|static
name|gboolean
DECL|function|gimp_layer_mask_is_content_locked (GimpItem * item)
name|gimp_layer_mask_is_content_locked
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
if|if
condition|(
name|layer
condition|)
return|return
name|gimp_item_is_content_locked
argument_list|(
name|GIMP_ITEM
argument_list|(
name|layer
argument_list|)
argument_list|)
return|;
return|return
name|FALSE
return|;
block|}
end_function

begin_function
specifier|static
name|gboolean
DECL|function|gimp_layer_mask_is_position_locked (GimpItem * item)
name|gimp_layer_mask_is_position_locked
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
if|if
condition|(
name|layer
condition|)
return|return
name|gimp_item_is_position_locked
argument_list|(
name|GIMP_ITEM
argument_list|(
name|layer
argument_list|)
argument_list|)
return|;
return|return
name|FALSE
return|;
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
name|gimp_item_get_image
argument_list|(
name|item
argument_list|)
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
name|GimpItemTree
modifier|*
DECL|function|gimp_layer_mask_get_tree (GimpItem * item)
name|gimp_layer_mask_get_tree
parameter_list|(
name|GimpItem
modifier|*
name|item
parameter_list|)
block|{
return|return
name|NULL
return|;
block|}
end_function

begin_function
specifier|static
name|GimpItem
modifier|*
DECL|function|gimp_layer_mask_duplicate (GimpItem * item,GType new_type)
name|gimp_layer_mask_duplicate
parameter_list|(
name|GimpItem
modifier|*
name|item
parameter_list|,
name|GType
name|new_type
parameter_list|)
block|{
name|GimpItem
modifier|*
name|new_item
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
argument_list|)
expr_stmt|;
return|return
name|new_item
return|;
block|}
end_function

begin_function
specifier|static
name|gboolean
DECL|function|gimp_layer_mask_rename (GimpItem * item,const gchar * new_name,const gchar * undo_desc,GError ** error)
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
parameter_list|,
name|GError
modifier|*
modifier|*
name|error
parameter_list|)
block|{
comment|/* reject renaming, layer masks are always named "<layer name> mask"  */
name|g_set_error
argument_list|(
name|error
argument_list|,
name|GIMP_ERROR
argument_list|,
name|GIMP_FAILED
argument_list|,
name|_
argument_list|(
literal|"Cannot rename layer masks."
argument_list|)
argument_list|)
expr_stmt|;
return|return
name|FALSE
return|;
block|}
end_function

begin_function
specifier|static
name|void
DECL|function|gimp_layer_mask_convert_type (GimpDrawable * drawable,GimpImage * dest_image,const Babl * new_format,GimpColorProfile * dest_profile,GeglDitherMethod layer_dither_type,GeglDitherMethod mask_dither_type,gboolean push_undo,GimpProgress * progress)
name|gimp_layer_mask_convert_type
parameter_list|(
name|GimpDrawable
modifier|*
name|drawable
parameter_list|,
name|GimpImage
modifier|*
name|dest_image
parameter_list|,
specifier|const
name|Babl
modifier|*
name|new_format
parameter_list|,
name|GimpColorProfile
modifier|*
name|dest_profile
parameter_list|,
name|GeglDitherMethod
name|layer_dither_type
parameter_list|,
name|GeglDitherMethod
name|mask_dither_type
parameter_list|,
name|gboolean
name|push_undo
parameter_list|,
name|GimpProgress
modifier|*
name|progress
parameter_list|)
block|{
name|new_format
operator|=
name|gimp_babl_mask_format
argument_list|(
name|gimp_babl_format_get_precision
argument_list|(
name|new_format
argument_list|)
argument_list|)
expr_stmt|;
name|GIMP_DRAWABLE_CLASS
argument_list|(
name|parent_class
argument_list|)
operator|->
name|convert_type
argument_list|(
name|drawable
argument_list|,
name|dest_image
argument_list|,
name|new_format
argument_list|,
name|dest_profile
argument_list|,
name|layer_dither_type
argument_list|,
name|mask_dither_type
argument_list|,
name|push_undo
argument_list|,
name|progress
argument_list|)
expr_stmt|;
block|}
end_function

begin_function
name|GimpLayerMask
modifier|*
DECL|function|gimp_layer_mask_new (GimpImage * image,gint width,gint height,const gchar * name,const GimpRGB * color)
name|gimp_layer_mask_new
parameter_list|(
name|GimpImage
modifier|*
name|image
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
name|g_return_val_if_fail
argument_list|(
name|GIMP_IS_IMAGE
argument_list|(
name|image
argument_list|)
argument_list|,
name|NULL
argument_list|)
expr_stmt|;
name|g_return_val_if_fail
argument_list|(
name|width
operator|>
literal|0
argument_list|,
name|NULL
argument_list|)
expr_stmt|;
name|g_return_val_if_fail
argument_list|(
name|height
operator|>
literal|0
argument_list|,
name|NULL
argument_list|)
expr_stmt|;
name|g_return_val_if_fail
argument_list|(
name|color
operator|!=
name|NULL
argument_list|,
name|NULL
argument_list|)
expr_stmt|;
name|layer_mask
operator|=
name|GIMP_LAYER_MASK
argument_list|(
name|gimp_drawable_new
argument_list|(
name|GIMP_TYPE_LAYER_MASK
argument_list|,
name|image
argument_list|,
name|name
argument_list|,
literal|0
argument_list|,
literal|0
argument_list|,
name|width
argument_list|,
name|height
argument_list|,
name|gimp_image_get_mask_format
argument_list|(
name|image
argument_list|)
argument_list|)
argument_list|)
expr_stmt|;
comment|/*  set the layer_mask color and opacity  */
name|gimp_channel_set_color
argument_list|(
name|GIMP_CHANNEL
argument_list|(
name|layer_mask
argument_list|)
argument_list|,
name|color
argument_list|,
name|FALSE
argument_list|)
expr_stmt|;
name|gimp_channel_set_show_masked
argument_list|(
name|GIMP_CHANNEL
argument_list|(
name|layer_mask
argument_list|)
argument_list|,
name|TRUE
argument_list|)
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
name|gint
name|offset_x
decl_stmt|;
name|gint
name|offset_y
decl_stmt|;
name|gimp_item_get_offset
argument_list|(
name|GIMP_ITEM
argument_list|(
name|layer
argument_list|)
argument_list|,
operator|&
name|offset_x
argument_list|,
operator|&
name|offset_y
argument_list|)
expr_stmt|;
name|gimp_item_set_offset
argument_list|(
name|GIMP_ITEM
argument_list|(
name|layer_mask
argument_list|)
argument_list|,
name|offset_x
argument_list|,
name|offset_y
argument_list|)
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
name|layer
argument_list|)
argument_list|)
expr_stmt|;
name|gimp_object_take_name
argument_list|(
name|GIMP_OBJECT
argument_list|(
name|layer_mask
argument_list|)
argument_list|,
name|mask_name
argument_list|)
expr_stmt|;
block|}
block|}
end_function

begin_function
name|GimpLayer
modifier|*
DECL|function|gimp_layer_mask_get_layer (GimpLayerMask * layer_mask)
name|gimp_layer_mask_get_layer
parameter_list|(
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

end_unit

