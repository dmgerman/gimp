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
file|<gtk/gtk.h>
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
file|"base/pixel-region.h"
end_include

begin_include
include|#
directive|include
file|"paint-funcs/paint-funcs.h"
end_include

begin_include
include|#
directive|include
file|"gimplayermask.h"
end_include

begin_include
include|#
directive|include
file|"undo.h"
end_include

begin_include
include|#
directive|include
file|"libgimp/gimpintl.h"
end_include

begin_enum
enum|enum
DECL|enum|__anon277042f60103
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
name|layermask
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
name|g_cclosure_marshal_VOID__VOID
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
name|g_cclosure_marshal_VOID__VOID
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
name|g_cclosure_marshal_VOID__VOID
argument_list|,
name|G_TYPE_NONE
argument_list|,
literal|0
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
name|width
argument_list|,
name|height
argument_list|,
name|GRAY_GIMAGE
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
name|empty
operator|=
name|TRUE
expr_stmt|;
name|GIMP_CHANNEL
argument_list|(
name|layer_mask
argument_list|)
operator|->
name|segs_in
operator|=
name|NULL
expr_stmt|;
name|GIMP_CHANNEL
argument_list|(
name|layer_mask
argument_list|)
operator|->
name|segs_out
operator|=
name|NULL
expr_stmt|;
name|GIMP_CHANNEL
argument_list|(
name|layer_mask
argument_list|)
operator|->
name|num_segs_in
operator|=
literal|0
expr_stmt|;
name|GIMP_CHANNEL
argument_list|(
name|layer_mask
argument_list|)
operator|->
name|num_segs_out
operator|=
literal|0
expr_stmt|;
name|GIMP_CHANNEL
argument_list|(
name|layer_mask
argument_list|)
operator|->
name|bounds_known
operator|=
name|TRUE
expr_stmt|;
name|GIMP_CHANNEL
argument_list|(
name|layer_mask
argument_list|)
operator|->
name|boundary_known
operator|=
name|TRUE
expr_stmt|;
name|GIMP_CHANNEL
argument_list|(
name|layer_mask
argument_list|)
operator|->
name|x1
operator|=
literal|0
expr_stmt|;
name|GIMP_CHANNEL
argument_list|(
name|layer_mask
argument_list|)
operator|->
name|y1
operator|=
literal|0
expr_stmt|;
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
name|GimpLayerMask
modifier|*
DECL|function|gimp_layer_mask_copy (GimpLayerMask * layer_mask)
name|gimp_layer_mask_copy
parameter_list|(
name|GimpLayerMask
modifier|*
name|layer_mask
parameter_list|)
block|{
name|gchar
modifier|*
name|layer_mask_name
decl_stmt|;
name|GimpLayerMask
modifier|*
name|new_layer_mask
decl_stmt|;
name|PixelRegion
name|srcPR
decl_stmt|,
name|destPR
decl_stmt|;
comment|/*  formulate the new layer_mask name  */
name|layer_mask_name
operator|=
name|g_strdup_printf
argument_list|(
name|_
argument_list|(
literal|"%s copy"
argument_list|)
argument_list|,
name|gimp_object_get_name
argument_list|(
name|GIMP_OBJECT
argument_list|(
name|layer_mask
argument_list|)
argument_list|)
argument_list|)
expr_stmt|;
comment|/*  allocate a new layer_mask object  */
name|new_layer_mask
operator|=
name|gimp_layer_mask_new
argument_list|(
name|GIMP_DRAWABLE
argument_list|(
name|layer_mask
argument_list|)
operator|->
name|gimage
argument_list|,
name|GIMP_DRAWABLE
argument_list|(
name|layer_mask
argument_list|)
operator|->
name|width
argument_list|,
name|GIMP_DRAWABLE
argument_list|(
name|layer_mask
argument_list|)
operator|->
name|height
argument_list|,
name|layer_mask_name
argument_list|,
operator|&
name|GIMP_CHANNEL
argument_list|(
name|layer_mask
argument_list|)
operator|->
name|color
argument_list|)
expr_stmt|;
name|GIMP_DRAWABLE
argument_list|(
name|new_layer_mask
argument_list|)
operator|->
name|visible
operator|=
name|GIMP_DRAWABLE
argument_list|(
name|layer_mask
argument_list|)
operator|->
name|visible
expr_stmt|;
name|GIMP_DRAWABLE
argument_list|(
name|new_layer_mask
argument_list|)
operator|->
name|offset_x
operator|=
name|GIMP_DRAWABLE
argument_list|(
name|layer_mask
argument_list|)
operator|->
name|offset_x
expr_stmt|;
name|GIMP_DRAWABLE
argument_list|(
name|new_layer_mask
argument_list|)
operator|->
name|offset_y
operator|=
name|GIMP_DRAWABLE
argument_list|(
name|layer_mask
argument_list|)
operator|->
name|offset_y
expr_stmt|;
name|GIMP_CHANNEL
argument_list|(
name|new_layer_mask
argument_list|)
operator|->
name|show_masked
operator|=
name|GIMP_CHANNEL
argument_list|(
name|layer_mask
argument_list|)
operator|->
name|show_masked
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
comment|/*  copy the contents across layer masks  */
name|pixel_region_init
argument_list|(
operator|&
name|srcPR
argument_list|,
name|GIMP_DRAWABLE
argument_list|(
name|layer_mask
argument_list|)
operator|->
name|tiles
argument_list|,
literal|0
argument_list|,
literal|0
argument_list|,
name|GIMP_DRAWABLE
argument_list|(
name|layer_mask
argument_list|)
operator|->
name|width
argument_list|,
name|GIMP_DRAWABLE
argument_list|(
name|layer_mask
argument_list|)
operator|->
name|height
argument_list|,
name|FALSE
argument_list|)
expr_stmt|;
name|pixel_region_init
argument_list|(
operator|&
name|destPR
argument_list|,
name|GIMP_DRAWABLE
argument_list|(
name|new_layer_mask
argument_list|)
operator|->
name|tiles
argument_list|,
literal|0
argument_list|,
literal|0
argument_list|,
name|GIMP_DRAWABLE
argument_list|(
name|layer_mask
argument_list|)
operator|->
name|width
argument_list|,
name|GIMP_DRAWABLE
argument_list|(
name|layer_mask
argument_list|)
operator|->
name|height
argument_list|,
name|TRUE
argument_list|)
expr_stmt|;
name|copy_region
argument_list|(
operator|&
name|srcPR
argument_list|,
operator|&
name|destPR
argument_list|)
expr_stmt|;
comment|/*  free up the layer_mask_name memory  */
name|g_free
argument_list|(
name|layer_mask_name
argument_list|)
expr_stmt|;
return|return
name|new_layer_mask
return|;
block|}
end_function

begin_function
name|void
DECL|function|gimp_layer_mask_set_layer (GimpLayerMask * mask,GimpLayer * layer)
name|gimp_layer_mask_set_layer
parameter_list|(
name|GimpLayerMask
modifier|*
name|mask
parameter_list|,
name|GimpLayer
modifier|*
name|layer
parameter_list|)
block|{
name|mask
operator|->
name|layer
operator|=
name|layer
expr_stmt|;
block|}
end_function

begin_function
name|GimpLayer
modifier|*
DECL|function|gimp_layer_mask_get_layer (GimpLayerMask * mask)
name|gimp_layer_mask_get_layer
parameter_list|(
name|GimpLayerMask
modifier|*
name|mask
parameter_list|)
block|{
return|return
name|mask
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
decl_stmt|;
name|drawable
operator|=
name|GIMP_DRAWABLE
argument_list|(
name|layer_mask
operator|->
name|layer
argument_list|)
expr_stmt|;
name|gimp_drawable_update
argument_list|(
name|drawable
argument_list|,
literal|0
argument_list|,
literal|0
argument_list|,
name|gimp_drawable_width
argument_list|(
name|drawable
argument_list|)
argument_list|,
name|gimp_drawable_height
argument_list|(
name|drawable
argument_list|)
argument_list|)
expr_stmt|;
block|}
name|g_signal_emit
argument_list|(
name|G_OBJECT
argument_list|(
name|layer_mask
argument_list|)
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
DECL|function|gimp_layer_mask_get_apply (GimpLayerMask * layer_mask)
name|gimp_layer_mask_get_apply
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
expr_stmt|;
name|g_signal_emit
argument_list|(
name|G_OBJECT
argument_list|(
name|layer_mask
argument_list|)
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
DECL|function|gimp_layer_mask_get_edit (GimpLayerMask * layer_mask)
name|gimp_layer_mask_get_edit
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
decl_stmt|;
name|drawable
operator|=
name|GIMP_DRAWABLE
argument_list|(
name|layer_mask
operator|->
name|layer
argument_list|)
expr_stmt|;
name|gimp_drawable_update
argument_list|(
name|drawable
argument_list|,
literal|0
argument_list|,
literal|0
argument_list|,
name|gimp_drawable_width
argument_list|(
name|drawable
argument_list|)
argument_list|,
name|gimp_drawable_height
argument_list|(
name|drawable
argument_list|)
argument_list|)
expr_stmt|;
block|}
name|g_signal_emit
argument_list|(
name|G_OBJECT
argument_list|(
name|layer_mask
argument_list|)
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
DECL|function|gimp_layer_mask_get_show (GimpLayerMask * layer_mask)
name|gimp_layer_mask_get_show
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

