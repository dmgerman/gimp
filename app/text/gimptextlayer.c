begin_unit|revision:0.9.5;language:C;cregit-version:0.0.1
begin_comment
comment|/* The GIMP -- an image manipulation program  * Copyright (C) 1995 Spencer Kimball and Peter Mattis  *  * GimpText  * Copyright (C) 2002-2003  Sven Neumann<sven@gimp.org>  *  * This program is free software; you can redistribute it and/or modify  * it under the terms of the GNU General Public License as published by  * the Free Software Foundation; either version 2 of the License, or  * (at your option) any later version.  *  * This program is distributed in the hope that it will be useful,  * but WITHOUT ANY WARRANTY; without even the implied warranty of  * MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the  * GNU General Public License for more details.  *  * You should have received a copy of the GNU General Public License  * along with this program; if not, write to the Free Software  * Foundation, Inc., 59 Temple Place - Suite 330, Boston, MA 02111-1307, USA.  */
end_comment

begin_include
include|#
directive|include
file|"config.h"
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
file|"text-types.h"
end_include

begin_include
include|#
directive|include
file|"base/pixel-region.h"
end_include

begin_include
include|#
directive|include
file|"base/tile-manager.h"
end_include

begin_include
include|#
directive|include
file|"paint-funcs/paint-funcs.h"
end_include

begin_include
include|#
directive|include
file|"core/gimpimage.h"
end_include

begin_include
include|#
directive|include
file|"gimptext.h"
end_include

begin_include
include|#
directive|include
file|"gimptextlayer.h"
end_include

begin_include
include|#
directive|include
file|"gimptextlayout.h"
end_include

begin_function_decl
specifier|static
name|void
name|gimp_text_layer_class_init
parameter_list|(
name|GimpTextLayerClass
modifier|*
name|klass
parameter_list|)
function_decl|;
end_function_decl

begin_function_decl
specifier|static
name|void
name|gimp_text_layer_init
parameter_list|(
name|GimpTextLayer
modifier|*
name|layer
parameter_list|)
function_decl|;
end_function_decl

begin_function_decl
specifier|static
name|void
name|gimp_text_layer_dispose
parameter_list|(
name|GObject
modifier|*
name|object
parameter_list|)
function_decl|;
end_function_decl

begin_function_decl
specifier|static
name|gsize
name|gimp_text_layer_get_memsize
parameter_list|(
name|GimpObject
modifier|*
name|object
parameter_list|)
function_decl|;
end_function_decl

begin_function_decl
specifier|static
name|TempBuf
modifier|*
name|gimp_text_layer_get_preview
parameter_list|(
name|GimpViewable
modifier|*
name|viewable
parameter_list|,
name|gint
name|width
parameter_list|,
name|gint
name|height
parameter_list|)
function_decl|;
end_function_decl

begin_function_decl
specifier|static
name|void
name|gimp_text_layer_notify_text
parameter_list|(
name|GimpTextLayer
modifier|*
name|layer
parameter_list|)
function_decl|;
end_function_decl

begin_function_decl
specifier|static
name|gboolean
name|gimp_text_layer_idle_render
parameter_list|(
name|GimpTextLayer
modifier|*
name|layer
parameter_list|)
function_decl|;
end_function_decl

begin_function_decl
specifier|static
name|gboolean
name|gimp_text_layer_render
parameter_list|(
name|GimpTextLayer
modifier|*
name|layer
parameter_list|)
function_decl|;
end_function_decl

begin_function_decl
specifier|static
name|void
name|gimp_text_layer_render_layout
parameter_list|(
name|GimpTextLayer
modifier|*
name|layer
parameter_list|,
name|GimpTextLayout
modifier|*
name|layout
parameter_list|)
function_decl|;
end_function_decl

begin_decl_stmt
DECL|variable|parent_class
specifier|static
name|GimpLayerClass
modifier|*
name|parent_class
init|=
name|NULL
decl_stmt|;
end_decl_stmt

begin_function
name|GType
DECL|function|gimp_text_layer_get_type (void)
name|gimp_text_layer_get_type
parameter_list|(
name|void
parameter_list|)
block|{
specifier|static
name|GType
name|layer_type
init|=
literal|0
decl_stmt|;
if|if
condition|(
operator|!
name|layer_type
condition|)
block|{
specifier|static
specifier|const
name|GTypeInfo
name|layer_info
init|=
block|{
sizeof|sizeof
argument_list|(
name|GimpTextLayerClass
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
name|gimp_text_layer_class_init
block|,
name|NULL
block|,
comment|/* class_finalize */
name|NULL
block|,
comment|/* class_data     */
sizeof|sizeof
argument_list|(
name|GimpTextLayer
argument_list|)
block|,
literal|0
block|,
comment|/* n_preallocs    */
operator|(
name|GInstanceInitFunc
operator|)
name|gimp_text_layer_init
block|,       }
decl_stmt|;
name|layer_type
operator|=
name|g_type_register_static
argument_list|(
name|GIMP_TYPE_LAYER
argument_list|,
literal|"GimpTextLayer"
argument_list|,
operator|&
name|layer_info
argument_list|,
literal|0
argument_list|)
expr_stmt|;
block|}
return|return
name|layer_type
return|;
block|}
end_function

begin_function
specifier|static
name|void
DECL|function|gimp_text_layer_class_init (GimpTextLayerClass * klass)
name|gimp_text_layer_class_init
parameter_list|(
name|GimpTextLayerClass
modifier|*
name|klass
parameter_list|)
block|{
name|GObjectClass
modifier|*
name|object_class
decl_stmt|;
name|GimpObjectClass
modifier|*
name|gimp_object_class
decl_stmt|;
name|GimpViewableClass
modifier|*
name|viewable_class
decl_stmt|;
name|object_class
operator|=
name|G_OBJECT_CLASS
argument_list|(
name|klass
argument_list|)
expr_stmt|;
name|gimp_object_class
operator|=
name|GIMP_OBJECT_CLASS
argument_list|(
name|klass
argument_list|)
expr_stmt|;
name|viewable_class
operator|=
name|GIMP_VIEWABLE_CLASS
argument_list|(
name|klass
argument_list|)
expr_stmt|;
name|parent_class
operator|=
name|g_type_class_peek_parent
argument_list|(
name|klass
argument_list|)
expr_stmt|;
name|object_class
operator|->
name|dispose
operator|=
name|gimp_text_layer_dispose
expr_stmt|;
name|gimp_object_class
operator|->
name|get_memsize
operator|=
name|gimp_text_layer_get_memsize
expr_stmt|;
name|viewable_class
operator|->
name|get_preview
operator|=
name|gimp_text_layer_get_preview
expr_stmt|;
block|}
end_function

begin_function
specifier|static
name|void
DECL|function|gimp_text_layer_init (GimpTextLayer * layer)
name|gimp_text_layer_init
parameter_list|(
name|GimpTextLayer
modifier|*
name|layer
parameter_list|)
block|{
name|layer
operator|->
name|text
operator|=
name|NULL
expr_stmt|;
block|}
end_function

begin_function
specifier|static
name|void
DECL|function|gimp_text_layer_dispose (GObject * object)
name|gimp_text_layer_dispose
parameter_list|(
name|GObject
modifier|*
name|object
parameter_list|)
block|{
name|GimpTextLayer
modifier|*
name|layer
decl_stmt|;
name|layer
operator|=
name|GIMP_TEXT_LAYER
argument_list|(
name|object
argument_list|)
expr_stmt|;
if|if
condition|(
name|layer
operator|->
name|idle_render_id
condition|)
block|{
name|g_source_remove
argument_list|(
name|layer
operator|->
name|idle_render_id
argument_list|)
expr_stmt|;
name|layer
operator|->
name|idle_render_id
operator|=
literal|0
expr_stmt|;
block|}
if|if
condition|(
name|layer
operator|->
name|text
condition|)
block|{
name|g_object_unref
argument_list|(
name|layer
operator|->
name|text
argument_list|)
expr_stmt|;
name|layer
operator|->
name|text
operator|=
name|NULL
expr_stmt|;
block|}
name|G_OBJECT_CLASS
argument_list|(
name|parent_class
argument_list|)
operator|->
name|dispose
argument_list|(
name|object
argument_list|)
expr_stmt|;
block|}
end_function

begin_function
name|GimpLayer
modifier|*
DECL|function|gimp_text_layer_new (GimpImage * image,GimpText * text)
name|gimp_text_layer_new
parameter_list|(
name|GimpImage
modifier|*
name|image
parameter_list|,
name|GimpText
modifier|*
name|text
parameter_list|)
block|{
name|GimpTextLayer
modifier|*
name|layer
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
name|GIMP_IS_TEXT
argument_list|(
name|text
argument_list|)
argument_list|,
name|NULL
argument_list|)
expr_stmt|;
if|if
condition|(
operator|!
name|text
operator|->
name|text
condition|)
return|return
name|NULL
return|;
name|layer
operator|=
name|g_object_new
argument_list|(
name|GIMP_TYPE_TEXT_LAYER
argument_list|,
name|NULL
argument_list|)
expr_stmt|;
name|gimp_drawable_configure
argument_list|(
name|GIMP_DRAWABLE
argument_list|(
name|layer
argument_list|)
argument_list|,
name|image
argument_list|,
literal|0
argument_list|,
literal|0
argument_list|,
literal|0
argument_list|,
literal|0
argument_list|,
name|gimp_image_base_type_with_alpha
argument_list|(
name|image
argument_list|)
argument_list|,
name|NULL
argument_list|)
expr_stmt|;
name|layer
operator|->
name|text
operator|=
name|g_object_ref
argument_list|(
name|text
argument_list|)
expr_stmt|;
if|if
condition|(
operator|!
name|gimp_text_layer_render
argument_list|(
name|layer
argument_list|)
condition|)
block|{
name|g_object_unref
argument_list|(
name|layer
argument_list|)
expr_stmt|;
return|return
name|NULL
return|;
block|}
name|g_signal_connect_object
argument_list|(
name|text
argument_list|,
literal|"notify"
argument_list|,
name|G_CALLBACK
argument_list|(
name|gimp_text_layer_notify_text
argument_list|)
argument_list|,
name|layer
argument_list|,
name|G_CONNECT_SWAPPED
argument_list|)
expr_stmt|;
return|return
name|GIMP_LAYER
argument_list|(
name|layer
argument_list|)
return|;
block|}
end_function

begin_function
name|GimpText
modifier|*
DECL|function|gimp_text_layer_get_text (GimpTextLayer * layer)
name|gimp_text_layer_get_text
parameter_list|(
name|GimpTextLayer
modifier|*
name|layer
parameter_list|)
block|{
name|g_return_val_if_fail
argument_list|(
name|GIMP_IS_TEXT_LAYER
argument_list|(
name|layer
argument_list|)
argument_list|,
name|NULL
argument_list|)
expr_stmt|;
return|return
name|layer
operator|->
name|text
return|;
block|}
end_function

begin_function
specifier|static
name|gsize
DECL|function|gimp_text_layer_get_memsize (GimpObject * object)
name|gimp_text_layer_get_memsize
parameter_list|(
name|GimpObject
modifier|*
name|object
parameter_list|)
block|{
name|GimpTextLayer
modifier|*
name|text_layer
decl_stmt|;
name|gsize
name|memsize
init|=
literal|0
decl_stmt|;
name|text_layer
operator|=
name|GIMP_TEXT_LAYER
argument_list|(
name|object
argument_list|)
expr_stmt|;
if|if
condition|(
name|text_layer
operator|->
name|text
condition|)
block|{
name|memsize
operator|+=
sizeof|sizeof
argument_list|(
name|GimpText
argument_list|)
expr_stmt|;
if|if
condition|(
name|text_layer
operator|->
name|text
operator|->
name|text
condition|)
name|memsize
operator|+=
name|strlen
argument_list|(
name|text_layer
operator|->
name|text
operator|->
name|text
argument_list|)
expr_stmt|;
block|}
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
argument_list|)
return|;
block|}
end_function

begin_function
specifier|static
name|TempBuf
modifier|*
DECL|function|gimp_text_layer_get_preview (GimpViewable * viewable,gint width,gint height)
name|gimp_text_layer_get_preview
parameter_list|(
name|GimpViewable
modifier|*
name|viewable
parameter_list|,
name|gint
name|width
parameter_list|,
name|gint
name|height
parameter_list|)
block|{
return|return
name|GIMP_VIEWABLE_CLASS
argument_list|(
name|parent_class
argument_list|)
operator|->
name|get_preview
argument_list|(
name|viewable
argument_list|,
name|width
argument_list|,
name|height
argument_list|)
return|;
block|}
end_function

begin_function
specifier|static
name|void
DECL|function|gimp_text_layer_notify_text (GimpTextLayer * layer)
name|gimp_text_layer_notify_text
parameter_list|(
name|GimpTextLayer
modifier|*
name|layer
parameter_list|)
block|{
if|if
condition|(
name|layer
operator|->
name|idle_render_id
condition|)
name|g_source_remove
argument_list|(
name|layer
operator|->
name|idle_render_id
argument_list|)
expr_stmt|;
name|layer
operator|->
name|idle_render_id
operator|=
name|g_idle_add_full
argument_list|(
name|G_PRIORITY_LOW
argument_list|,
operator|(
name|GSourceFunc
operator|)
name|gimp_text_layer_idle_render
argument_list|,
name|layer
argument_list|,
name|NULL
argument_list|)
expr_stmt|;
block|}
end_function

begin_function
specifier|static
name|gboolean
DECL|function|gimp_text_layer_idle_render (GimpTextLayer * layer)
name|gimp_text_layer_idle_render
parameter_list|(
name|GimpTextLayer
modifier|*
name|layer
parameter_list|)
block|{
name|layer
operator|->
name|idle_render_id
operator|=
literal|0
expr_stmt|;
name|gimp_text_layer_render
argument_list|(
name|layer
argument_list|)
expr_stmt|;
return|return
name|FALSE
return|;
block|}
end_function

begin_function
specifier|static
name|gboolean
DECL|function|gimp_text_layer_render (GimpTextLayer * layer)
name|gimp_text_layer_render
parameter_list|(
name|GimpTextLayer
modifier|*
name|layer
parameter_list|)
block|{
name|GimpImage
modifier|*
name|image
decl_stmt|;
name|GimpDrawable
modifier|*
name|drawable
decl_stmt|;
name|GimpTextLayout
modifier|*
name|layout
decl_stmt|;
name|gint
name|width
decl_stmt|;
name|gint
name|height
decl_stmt|;
name|image
operator|=
name|gimp_item_get_image
argument_list|(
name|GIMP_ITEM
argument_list|(
name|layer
argument_list|)
argument_list|)
expr_stmt|;
name|drawable
operator|=
name|GIMP_DRAWABLE
argument_list|(
name|layer
argument_list|)
expr_stmt|;
name|layout
operator|=
name|gimp_text_layout_new
argument_list|(
name|layer
operator|->
name|text
argument_list|,
name|image
argument_list|)
expr_stmt|;
name|gimp_text_layout_get_size
argument_list|(
name|layout
argument_list|,
operator|&
name|width
argument_list|,
operator|&
name|height
argument_list|)
expr_stmt|;
if|if
condition|(
name|gimp_text_layout_get_size
argument_list|(
name|layout
argument_list|,
operator|&
name|width
argument_list|,
operator|&
name|height
argument_list|)
condition|)
block|{
if|if
condition|(
name|width
operator|!=
name|gimp_drawable_width
argument_list|(
name|drawable
argument_list|)
operator|||
name|height
operator|!=
name|gimp_drawable_height
argument_list|(
name|drawable
argument_list|)
condition|)
block|{
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
name|drawable
operator|->
name|width
operator|=
name|width
expr_stmt|;
name|drawable
operator|->
name|height
operator|=
name|height
expr_stmt|;
if|if
condition|(
name|drawable
operator|->
name|tiles
condition|)
name|tile_manager_destroy
argument_list|(
name|drawable
operator|->
name|tiles
argument_list|)
expr_stmt|;
name|drawable
operator|->
name|tiles
operator|=
name|tile_manager_new
argument_list|(
name|width
argument_list|,
name|height
argument_list|,
name|drawable
operator|->
name|bytes
argument_list|)
expr_stmt|;
name|gimp_viewable_size_changed
argument_list|(
name|GIMP_VIEWABLE
argument_list|(
name|layer
argument_list|)
argument_list|)
expr_stmt|;
block|}
block|}
name|gimp_object_set_name_safe
argument_list|(
name|GIMP_OBJECT
argument_list|(
name|layer
argument_list|)
argument_list|,
name|layer
operator|->
name|text
operator|->
name|text
argument_list|)
expr_stmt|;
name|gimp_text_layer_render_layout
argument_list|(
name|layer
argument_list|,
name|layout
argument_list|)
expr_stmt|;
name|g_object_unref
argument_list|(
name|layout
argument_list|)
expr_stmt|;
name|gimp_image_flush
argument_list|(
name|image
argument_list|)
expr_stmt|;
return|return
operator|(
name|width
operator|>
literal|0
operator|&&
name|height
operator|>
literal|0
operator|)
return|;
block|}
end_function

begin_function
specifier|static
name|void
DECL|function|gimp_text_layer_render_layout (GimpTextLayer * layer,GimpTextLayout * layout)
name|gimp_text_layer_render_layout
parameter_list|(
name|GimpTextLayer
modifier|*
name|layer
parameter_list|,
name|GimpTextLayout
modifier|*
name|layout
parameter_list|)
block|{
name|GimpDrawable
modifier|*
name|drawable
init|=
name|GIMP_DRAWABLE
argument_list|(
name|layer
argument_list|)
decl_stmt|;
name|TileManager
modifier|*
name|mask
decl_stmt|;
name|PixelRegion
name|textPR
decl_stmt|;
name|PixelRegion
name|maskPR
decl_stmt|;
name|gint
name|width
decl_stmt|;
name|gint
name|height
decl_stmt|;
name|gimp_drawable_fill
argument_list|(
name|drawable
argument_list|,
operator|&
name|layer
operator|->
name|text
operator|->
name|color
argument_list|)
expr_stmt|;
name|width
operator|=
name|gimp_drawable_width
argument_list|(
name|drawable
argument_list|)
expr_stmt|;
name|height
operator|=
name|gimp_drawable_height
argument_list|(
name|drawable
argument_list|)
expr_stmt|;
name|mask
operator|=
name|gimp_text_layout_render
argument_list|(
name|layout
argument_list|,
name|width
argument_list|,
name|height
argument_list|)
expr_stmt|;
name|pixel_region_init
argument_list|(
operator|&
name|textPR
argument_list|,
name|drawable
operator|->
name|tiles
argument_list|,
literal|0
argument_list|,
literal|0
argument_list|,
name|width
argument_list|,
name|height
argument_list|,
name|TRUE
argument_list|)
expr_stmt|;
name|pixel_region_init
argument_list|(
operator|&
name|maskPR
argument_list|,
name|mask
argument_list|,
literal|0
argument_list|,
literal|0
argument_list|,
name|width
argument_list|,
name|height
argument_list|,
name|FALSE
argument_list|)
expr_stmt|;
name|apply_mask_to_region
argument_list|(
operator|&
name|textPR
argument_list|,
operator|&
name|maskPR
argument_list|,
name|OPAQUE_OPACITY
argument_list|)
expr_stmt|;
name|tile_manager_destroy
argument_list|(
name|mask
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
name|width
argument_list|,
name|height
argument_list|)
expr_stmt|;
block|}
end_function

end_unit

