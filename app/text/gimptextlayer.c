begin_unit|revision:0.9.5;language:C;cregit-version:0.0.1
begin_comment
comment|/* The GIMP -- an image manipulation program  * Copyright (C) 1995 Spencer Kimball and Peter Mattis  *  * GimpTextLayer  * Copyright (C) 2002-2003  Sven Neumann<sven@gimp.org>  *  * This program is free software; you can redistribute it and/or modify  * it under the terms of the GNU General Public License as published by  * the Free Software Foundation; either version 2 of the License, or  * (at your option) any later version.  *  * This program is distributed in the hope that it will be useful,  * but WITHOUT ANY WARRANTY; without even the implied warranty of  * MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the  * GNU General Public License for more details.  *  * You should have received a copy of the GNU General Public License  * along with this program; if not, write to the Free Software  * Foundation, Inc., 59 Temple Place - Suite 330, Boston, MA 02111-1307, USA.  */
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
file|<pango/pangoft2.h>
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
file|"config/gimpconfig.h"
end_include

begin_include
include|#
directive|include
file|"core/gimp.h"
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
file|"gimptext-bitmap.h"
end_include

begin_include
include|#
directive|include
file|"gimptext-private.h"
end_include

begin_include
include|#
directive|include
file|"gimptextlayer.h"
end_include

begin_include
include|#
directive|include
file|"gimptextlayer-transform.h"
end_include

begin_include
include|#
directive|include
file|"gimptextlayout.h"
end_include

begin_include
include|#
directive|include
file|"gimptextlayout-render.h"
end_include

begin_include
include|#
directive|include
file|"gimp-intl.h"
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
parameter_list|,
name|gsize
modifier|*
name|gui_size
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
name|GimpItem
modifier|*
name|gimp_text_layer_duplicate
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
name|void
name|gimp_text_layer_rename
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

begin_function_decl
specifier|static
name|void
name|gimp_text_layer_set_text
parameter_list|(
name|GimpTextLayer
modifier|*
name|layer
parameter_list|,
name|GimpText
modifier|*
name|text
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
name|gimp_text_layer_render_now
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
name|GimpItemClass
modifier|*
name|item_class
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
name|item_class
operator|=
name|GIMP_ITEM_CLASS
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
name|default_stock_id
operator|=
literal|"gimp-text-layer"
expr_stmt|;
name|viewable_class
operator|->
name|get_preview
operator|=
name|gimp_text_layer_get_preview
expr_stmt|;
name|item_class
operator|->
name|default_name
operator|=
name|_
argument_list|(
literal|"Text Layer"
argument_list|)
expr_stmt|;
name|item_class
operator|->
name|duplicate
operator|=
name|gimp_text_layer_duplicate
expr_stmt|;
name|item_class
operator|->
name|rename
operator|=
name|gimp_text_layer_rename
expr_stmt|;
if|#
directive|if
literal|0
block|item_class->scale                = gimp_text_layer_scale;   item_class->flip                 = gimp_text_layer_flip;   item_class->rotate               = gimp_text_layer_rotate;   item_class->transform            = gimp_text_layer_transform;
endif|#
directive|endif
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
name|layer
operator|->
name|idle_render_id
operator|=
literal|0
expr_stmt|;
name|layer
operator|->
name|auto_rename
operator|=
name|TRUE
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
specifier|static
name|gsize
DECL|function|gimp_text_layer_get_memsize (GimpObject * object,gsize * gui_size)
name|gimp_text_layer_get_memsize
parameter_list|(
name|GimpObject
modifier|*
name|object
parameter_list|,
name|gsize
modifier|*
name|gui_size
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
name|memsize
operator|+=
name|gimp_object_get_memsize
argument_list|(
name|GIMP_OBJECT
argument_list|(
name|text_layer
operator|->
name|text
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
name|GimpItem
modifier|*
DECL|function|gimp_text_layer_duplicate (GimpItem * item,GType new_type,gboolean add_alpha)
name|gimp_text_layer_duplicate
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
name|GimpTextLayer
modifier|*
name|text_layer
decl_stmt|;
name|GimpItem
modifier|*
name|new_item
decl_stmt|;
name|GimpTextLayer
modifier|*
name|new_text_layer
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
name|GIMP_IS_TEXT_LAYER
argument_list|(
name|new_item
argument_list|)
condition|)
return|return
name|new_item
return|;
name|text_layer
operator|=
name|GIMP_TEXT_LAYER
argument_list|(
name|item
argument_list|)
expr_stmt|;
name|new_text_layer
operator|=
name|GIMP_TEXT_LAYER
argument_list|(
name|new_item
argument_list|)
expr_stmt|;
name|new_text_layer
operator|->
name|text
operator|=
name|GIMP_TEXT
argument_list|(
name|gimp_config_duplicate
argument_list|(
name|G_OBJECT
argument_list|(
name|text_layer
operator|->
name|text
argument_list|)
argument_list|)
argument_list|)
expr_stmt|;
name|g_signal_connect_object
argument_list|(
name|new_text_layer
operator|->
name|text
argument_list|,
literal|"notify"
argument_list|,
name|G_CALLBACK
argument_list|(
name|gimp_text_layer_notify_text
argument_list|)
argument_list|,
name|new_text_layer
argument_list|,
name|G_CONNECT_SWAPPED
argument_list|)
expr_stmt|;
return|return
name|new_item
return|;
block|}
end_function

begin_function
specifier|static
name|void
DECL|function|gimp_text_layer_rename (GimpItem * item,const gchar * new_name,const gchar * undo_desc)
name|gimp_text_layer_rename
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
name|GIMP_TEXT_LAYER
argument_list|(
name|item
argument_list|)
operator|->
name|auto_rename
operator|=
name|FALSE
expr_stmt|;
name|GIMP_ITEM_CLASS
argument_list|(
name|parent_class
argument_list|)
operator|->
name|rename
argument_list|(
name|item
argument_list|,
name|new_name
argument_list|,
name|undo_desc
argument_list|)
expr_stmt|;
block|}
end_function

begin_comment
comment|/**  * gimp_text_layer_new:  * @image: the #GimpImage the layer should belong to  * @text: a #GimpText object  *  * Creates a new text layer.  *  * Return value: a new #GimpTextLayer or %NULL in case of a problem  **/
end_comment

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
name|gimp_text_layer_set_text
argument_list|(
name|layer
argument_list|,
name|text
argument_list|)
expr_stmt|;
if|if
condition|(
operator|!
name|gimp_text_layer_render_now
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
return|return
name|GIMP_LAYER
argument_list|(
name|layer
argument_list|)
return|;
block|}
end_function

begin_comment
comment|/**  * gimp_text_layer_from_layer:  * @layer: a #GimpLayer object  * @text: a #GimpText object  *  * Converts a standard #GimpLayer and a #GimpText object into a  * #GimpTextLayer. The new text layer takes ownership of the @text and  * @layer objects.  The @layer object is rendered unusable by this  * function. Don't even try to use if afterwards!  *  * This is a gross hack that is needed in order to load text layers  * from XCF files in a backwards-compatible way. Please don't use it  * for anything else!  *  * Return value: a newly allocated #GimpTextLayer object  **/
end_comment

begin_function
name|GimpLayer
modifier|*
DECL|function|gimp_text_layer_from_layer (GimpLayer * layer,GimpText * text)
name|gimp_text_layer_from_layer
parameter_list|(
name|GimpLayer
modifier|*
name|layer
parameter_list|,
name|GimpText
modifier|*
name|text
parameter_list|)
block|{
name|GimpTextLayer
modifier|*
name|text_layer
decl_stmt|;
name|GimpItem
modifier|*
name|item
decl_stmt|;
name|GimpDrawable
modifier|*
name|drawable
decl_stmt|;
name|g_return_val_if_fail
argument_list|(
name|GIMP_IS_LAYER
argument_list|(
name|layer
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
name|text_layer
operator|=
name|g_object_new
argument_list|(
name|GIMP_TYPE_TEXT_LAYER
argument_list|,
name|NULL
argument_list|)
expr_stmt|;
name|item
operator|=
name|GIMP_ITEM
argument_list|(
name|text_layer
argument_list|)
expr_stmt|;
name|drawable
operator|=
name|GIMP_DRAWABLE
argument_list|(
name|text_layer
argument_list|)
expr_stmt|;
name|gimp_object_set_name
argument_list|(
name|GIMP_OBJECT
argument_list|(
name|text_layer
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
name|item
operator|->
name|ID
operator|=
name|gimp_item_get_ID
argument_list|(
name|GIMP_ITEM
argument_list|(
name|layer
argument_list|)
argument_list|)
expr_stmt|;
name|item
operator|->
name|tattoo
operator|=
name|gimp_item_get_tattoo
argument_list|(
name|GIMP_ITEM
argument_list|(
name|layer
argument_list|)
argument_list|)
expr_stmt|;
name|item
operator|->
name|gimage
operator|=
name|gimp_item_get_image
argument_list|(
name|GIMP_ITEM
argument_list|(
name|layer
argument_list|)
argument_list|)
expr_stmt|;
name|gimp_item_set_image
argument_list|(
name|GIMP_ITEM
argument_list|(
name|layer
argument_list|)
argument_list|,
name|NULL
argument_list|)
expr_stmt|;
name|g_hash_table_replace
argument_list|(
name|item
operator|->
name|gimage
operator|->
name|gimp
operator|->
name|item_table
argument_list|,
name|GINT_TO_POINTER
argument_list|(
name|item
operator|->
name|ID
argument_list|)
argument_list|,
name|item
argument_list|)
expr_stmt|;
name|item
operator|->
name|parasites
operator|=
name|GIMP_ITEM
argument_list|(
name|layer
argument_list|)
operator|->
name|parasites
expr_stmt|;
name|GIMP_ITEM
argument_list|(
name|layer
argument_list|)
operator|->
name|parasites
operator|=
name|NULL
expr_stmt|;
name|item
operator|->
name|width
operator|=
name|gimp_item_width
argument_list|(
name|GIMP_ITEM
argument_list|(
name|layer
argument_list|)
argument_list|)
expr_stmt|;
name|item
operator|->
name|height
operator|=
name|gimp_item_height
argument_list|(
name|GIMP_ITEM
argument_list|(
name|layer
argument_list|)
argument_list|)
expr_stmt|;
name|gimp_item_offsets
argument_list|(
name|GIMP_ITEM
argument_list|(
name|layer
argument_list|)
argument_list|,
operator|&
name|item
operator|->
name|offset_x
argument_list|,
operator|&
name|item
operator|->
name|offset_y
argument_list|)
expr_stmt|;
name|item
operator|->
name|linked
operator|=
name|gimp_item_get_linked
argument_list|(
name|GIMP_ITEM
argument_list|(
name|layer
argument_list|)
argument_list|)
expr_stmt|;
name|drawable
operator|->
name|tiles
operator|=
name|GIMP_DRAWABLE
argument_list|(
name|layer
argument_list|)
operator|->
name|tiles
expr_stmt|;
name|GIMP_DRAWABLE
argument_list|(
name|layer
argument_list|)
operator|->
name|tiles
operator|=
name|NULL
expr_stmt|;
name|drawable
operator|->
name|visible
operator|=
name|gimp_drawable_get_visible
argument_list|(
name|GIMP_DRAWABLE
argument_list|(
name|layer
argument_list|)
argument_list|)
expr_stmt|;
name|drawable
operator|->
name|bytes
operator|=
name|gimp_drawable_bytes
argument_list|(
name|GIMP_DRAWABLE
argument_list|(
name|layer
argument_list|)
argument_list|)
expr_stmt|;
name|drawable
operator|->
name|type
operator|=
name|gimp_drawable_type
argument_list|(
name|GIMP_DRAWABLE
argument_list|(
name|layer
argument_list|)
argument_list|)
expr_stmt|;
name|drawable
operator|->
name|has_alpha
operator|=
name|gimp_drawable_has_alpha
argument_list|(
name|GIMP_DRAWABLE
argument_list|(
name|layer
argument_list|)
argument_list|)
expr_stmt|;
name|GIMP_LAYER
argument_list|(
name|text_layer
argument_list|)
operator|->
name|opacity
operator|=
name|gimp_layer_get_opacity
argument_list|(
name|layer
argument_list|)
expr_stmt|;
name|GIMP_LAYER
argument_list|(
name|text_layer
argument_list|)
operator|->
name|mode
operator|=
name|gimp_layer_get_mode
argument_list|(
name|layer
argument_list|)
expr_stmt|;
name|GIMP_LAYER
argument_list|(
name|text_layer
argument_list|)
operator|->
name|preserve_trans
operator|=
name|gimp_layer_get_preserve_trans
argument_list|(
name|layer
argument_list|)
expr_stmt|;
name|gimp_text_layer_set_text
argument_list|(
name|text_layer
argument_list|,
name|text
argument_list|)
expr_stmt|;
name|g_object_unref
argument_list|(
name|layer
argument_list|)
expr_stmt|;
name|g_object_unref
argument_list|(
name|text
argument_list|)
expr_stmt|;
return|return
name|GIMP_LAYER
argument_list|(
name|text_layer
argument_list|)
return|;
block|}
end_function

begin_function
specifier|static
name|void
DECL|function|gimp_text_layer_set_text (GimpTextLayer * layer,GimpText * text)
name|gimp_text_layer_set_text
parameter_list|(
name|GimpTextLayer
modifier|*
name|layer
parameter_list|,
name|GimpText
modifier|*
name|text
parameter_list|)
block|{
name|g_return_if_fail
argument_list|(
name|GIMP_IS_TEXT_LAYER
argument_list|(
name|layer
argument_list|)
argument_list|)
expr_stmt|;
name|g_return_if_fail
argument_list|(
name|GIMP_IS_TEXT
argument_list|(
name|text
argument_list|)
argument_list|)
expr_stmt|;
name|g_return_if_fail
argument_list|(
name|layer
operator|->
name|text
operator|==
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
name|void
DECL|function|gimp_text_layer_render (GimpTextLayer * layer)
name|gimp_text_layer_render
parameter_list|(
name|GimpTextLayer
modifier|*
name|layer
parameter_list|)
block|{
name|g_return_if_fail
argument_list|(
name|GIMP_IS_TEXT_LAYER
argument_list|(
name|layer
argument_list|)
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
name|gimp_text_layer_render_now
argument_list|(
name|layer
argument_list|)
expr_stmt|;
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
name|gimp_text_layer_render_now
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
DECL|function|gimp_text_layer_render_now (GimpTextLayer * layer)
name|gimp_text_layer_render_now
parameter_list|(
name|GimpTextLayer
modifier|*
name|layer
parameter_list|)
block|{
name|GimpDrawable
modifier|*
name|drawable
decl_stmt|;
name|GimpItem
modifier|*
name|item
decl_stmt|;
name|GimpImage
modifier|*
name|image
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
name|drawable
operator|=
name|GIMP_DRAWABLE
argument_list|(
name|layer
argument_list|)
expr_stmt|;
name|item
operator|=
name|GIMP_ITEM
argument_list|(
name|layer
argument_list|)
expr_stmt|;
name|image
operator|=
name|gimp_item_get_image
argument_list|(
name|item
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
name|gimp_item_width
argument_list|(
name|item
argument_list|)
operator|||
name|height
operator|!=
name|gimp_item_height
argument_list|(
name|item
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
name|gimp_item_width
argument_list|(
name|item
argument_list|)
argument_list|,
name|gimp_item_height
argument_list|(
name|item
argument_list|)
argument_list|)
expr_stmt|;
comment|/*  Make sure we're not caching any old selection info  */
name|gimp_drawable_invalidate_boundary
argument_list|(
name|GIMP_DRAWABLE
argument_list|(
name|layer
argument_list|)
argument_list|)
expr_stmt|;
name|GIMP_ITEM
argument_list|(
name|drawable
argument_list|)
operator|->
name|width
operator|=
name|width
expr_stmt|;
name|GIMP_ITEM
argument_list|(
name|drawable
argument_list|)
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
name|tile_manager_unref
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
if|if
condition|(
name|layer
operator|->
name|auto_rename
condition|)
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
condition|?
name|layer
operator|->
name|text
operator|->
name|text
else|:
name|_
argument_list|(
literal|"Empty Text Layer"
argument_list|)
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
decl_stmt|;
name|GimpItem
modifier|*
name|item
decl_stmt|;
name|TileManager
modifier|*
name|mask
decl_stmt|;
name|FT_Bitmap
name|bitmap
decl_stmt|;
name|PixelRegion
name|textPR
decl_stmt|;
name|PixelRegion
name|maskPR
decl_stmt|;
name|gint
name|i
decl_stmt|;
name|drawable
operator|=
name|GIMP_DRAWABLE
argument_list|(
name|layer
argument_list|)
expr_stmt|;
name|item
operator|=
name|GIMP_ITEM
argument_list|(
name|layer
argument_list|)
expr_stmt|;
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
name|bitmap
operator|.
name|width
operator|=
name|gimp_item_width
argument_list|(
name|item
argument_list|)
expr_stmt|;
name|bitmap
operator|.
name|rows
operator|=
name|gimp_item_height
argument_list|(
name|item
argument_list|)
expr_stmt|;
name|bitmap
operator|.
name|pitch
operator|=
name|bitmap
operator|.
name|width
expr_stmt|;
if|if
condition|(
name|bitmap
operator|.
name|pitch
operator|&
literal|3
condition|)
name|bitmap
operator|.
name|pitch
operator|+=
literal|4
operator|-
operator|(
name|bitmap
operator|.
name|pitch
operator|&
literal|3
operator|)
expr_stmt|;
name|bitmap
operator|.
name|buffer
operator|=
name|g_malloc0
argument_list|(
name|bitmap
operator|.
name|rows
operator|*
name|bitmap
operator|.
name|pitch
argument_list|)
expr_stmt|;
name|gimp_text_layout_render
argument_list|(
name|layout
argument_list|,
operator|(
name|GimpTextRenderFunc
operator|)
name|gimp_text_render_bitmap
argument_list|,
operator|&
name|bitmap
argument_list|)
expr_stmt|;
name|mask
operator|=
name|tile_manager_new
argument_list|(
name|bitmap
operator|.
name|width
argument_list|,
name|bitmap
operator|.
name|rows
argument_list|,
literal|1
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
name|bitmap
operator|.
name|width
argument_list|,
name|bitmap
operator|.
name|rows
argument_list|,
name|TRUE
argument_list|)
expr_stmt|;
for|for
control|(
name|i
operator|=
literal|0
init|;
name|i
operator|<
name|bitmap
operator|.
name|rows
condition|;
name|i
operator|++
control|)
name|pixel_region_set_row
argument_list|(
operator|&
name|maskPR
argument_list|,
literal|0
argument_list|,
name|i
argument_list|,
name|bitmap
operator|.
name|width
argument_list|,
name|bitmap
operator|.
name|buffer
operator|+
name|i
operator|*
name|bitmap
operator|.
name|pitch
argument_list|)
expr_stmt|;
name|g_free
argument_list|(
name|bitmap
operator|.
name|buffer
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
name|bitmap
operator|.
name|width
argument_list|,
name|bitmap
operator|.
name|rows
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
name|bitmap
operator|.
name|width
argument_list|,
name|bitmap
operator|.
name|rows
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
name|tile_manager_unref
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
name|bitmap
operator|.
name|width
argument_list|,
name|bitmap
operator|.
name|rows
argument_list|)
expr_stmt|;
block|}
end_function

end_unit

