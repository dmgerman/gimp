begin_unit|revision:0.9.5;language:C;cregit-version:0.0.1
begin_comment
comment|/* The GIMP -- an image manipulation program  * Copyright (C) 1995 Spencer Kimball and Peter Mattis  *  * GimpText  * Copyright (C) 2003  Sven Neumann<sven@gimp.org>  *  * This program is free software; you can redistribute it and/or modify  * it under the terms of the GNU General Public License as published by  * the Free Software Foundation; either version 2 of the License, or  * (at your option) any later version.  *  * This program is distributed in the hope that it will be useful,  * but WITHOUT ANY WARRANTY; without even the implied warranty of  * MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the  * GNU General Public License for more details.  *  * You should have received a copy of the GNU General Public License  * along with this program; if not, write to the Free Software  * Foundation, Inc., 59 Temple Place - Suite 330, Boston, MA 02111-1307, USA.  */
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
file|"text-types.h"
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
file|"core/gimpparasitelist.h"
end_include

begin_include
include|#
directive|include
file|"gimptext.h"
end_include

begin_include
include|#
directive|include
file|"gimptext-parasite.h"
end_include

begin_include
include|#
directive|include
file|"gimptextlayer.h"
end_include

begin_include
include|#
directive|include
file|"gimptextlayer-xcf.h"
end_include

begin_include
include|#
directive|include
file|"gimp-intl.h"
end_include

begin_enum
enum|enum
DECL|enum|__anon29b6ac1e0103
block|{
DECL|enumerator|TEXT_LAYER_XCF_NONE
name|TEXT_LAYER_XCF_NONE
init|=
literal|0
block|,
DECL|enumerator|TEXT_LAYER_XCF_DONT_AUTO_RENAME
name|TEXT_LAYER_XCF_DONT_AUTO_RENAME
init|=
literal|1
operator|<<
literal|0
block|,
DECL|enumerator|TEXT_LAYER_XCF_MODIFIED
name|TEXT_LAYER_XCF_MODIFIED
init|=
literal|1
operator|<<
literal|1
block|}
enum|;
end_enum

begin_function_decl
specifier|static
name|GimpLayer
modifier|*
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
function_decl|;
end_function_decl

begin_function
name|gboolean
DECL|function|gimp_text_layer_xcf_load_hack (GimpLayer ** layer)
name|gimp_text_layer_xcf_load_hack
parameter_list|(
name|GimpLayer
modifier|*
modifier|*
name|layer
parameter_list|)
block|{
specifier|const
name|gchar
modifier|*
name|name
decl_stmt|;
name|GimpText
modifier|*
name|text
init|=
name|NULL
decl_stmt|;
name|GimpParasite
modifier|*
name|parasite
decl_stmt|;
name|g_return_val_if_fail
argument_list|(
name|layer
operator|!=
name|NULL
argument_list|,
name|FALSE
argument_list|)
expr_stmt|;
name|g_return_val_if_fail
argument_list|(
name|GIMP_IS_LAYER
argument_list|(
operator|*
name|layer
argument_list|)
argument_list|,
name|FALSE
argument_list|)
expr_stmt|;
name|name
operator|=
name|gimp_text_parasite_name
argument_list|()
expr_stmt|;
name|parasite
operator|=
name|gimp_item_parasite_find
argument_list|(
name|GIMP_ITEM
argument_list|(
operator|*
name|layer
argument_list|)
argument_list|,
name|name
argument_list|)
expr_stmt|;
if|if
condition|(
name|parasite
condition|)
block|{
name|GError
modifier|*
name|error
init|=
name|NULL
decl_stmt|;
name|text
operator|=
name|gimp_text_from_parasite
argument_list|(
name|parasite
argument_list|,
operator|&
name|error
argument_list|)
expr_stmt|;
if|if
condition|(
name|error
condition|)
block|{
name|g_message
argument_list|(
name|_
argument_list|(
literal|"Problems parsing the text parasite for layer '%s':\n"
literal|"%s\n\n"
literal|"Some text properties may be wrong. "
literal|"Unless you want to edit the text layer, "
literal|"you don't need to worry about this."
argument_list|)
argument_list|,
name|gimp_object_get_name
argument_list|(
name|GIMP_OBJECT
argument_list|(
operator|*
name|layer
argument_list|)
argument_list|)
argument_list|,
name|error
operator|->
name|message
argument_list|)
expr_stmt|;
name|g_error_free
argument_list|(
name|error
argument_list|)
expr_stmt|;
block|}
block|}
else|else
block|{
name|name
operator|=
name|gimp_text_gdyntext_parasite_name
argument_list|()
expr_stmt|;
name|parasite
operator|=
name|gimp_item_parasite_find
argument_list|(
name|GIMP_ITEM
argument_list|(
operator|*
name|layer
argument_list|)
argument_list|,
name|name
argument_list|)
expr_stmt|;
if|if
condition|(
name|parasite
condition|)
name|text
operator|=
name|gimp_text_from_gdyntext_parasite
argument_list|(
name|parasite
argument_list|)
expr_stmt|;
block|}
if|if
condition|(
name|text
condition|)
block|{
operator|*
name|layer
operator|=
name|gimp_text_layer_from_layer
argument_list|(
operator|*
name|layer
argument_list|,
name|text
argument_list|)
expr_stmt|;
comment|/*  let the text layer know what parasite was used to create it  */
name|GIMP_TEXT_LAYER
argument_list|(
operator|*
name|layer
argument_list|)
operator|->
name|text_parasite
operator|=
name|name
expr_stmt|;
block|}
return|return
operator|(
name|text
operator|!=
name|NULL
operator|)
return|;
block|}
end_function

begin_function
name|void
DECL|function|gimp_text_layer_xcf_save_prepare (GimpTextLayer * layer)
name|gimp_text_layer_xcf_save_prepare
parameter_list|(
name|GimpTextLayer
modifier|*
name|layer
parameter_list|)
block|{
name|GimpText
modifier|*
name|text
decl_stmt|;
name|g_return_if_fail
argument_list|(
name|GIMP_IS_TEXT_LAYER
argument_list|(
name|layer
argument_list|)
argument_list|)
expr_stmt|;
comment|/*  If the layer has a text parasite already, it wasn't changed and we    *  can simply save the original parasite back which is still attached.    */
if|if
condition|(
name|layer
operator|->
name|text_parasite
condition|)
return|return;
name|text
operator|=
name|gimp_text_layer_get_text
argument_list|(
name|layer
argument_list|)
expr_stmt|;
if|if
condition|(
name|text
condition|)
block|{
name|GimpParasite
modifier|*
name|parasite
init|=
name|gimp_text_to_parasite
argument_list|(
name|text
argument_list|)
decl_stmt|;
name|gimp_parasite_list_add
argument_list|(
name|GIMP_ITEM
argument_list|(
name|layer
argument_list|)
operator|->
name|parasites
argument_list|,
name|parasite
argument_list|)
expr_stmt|;
block|}
block|}
end_function

begin_function
name|guint32
DECL|function|gimp_text_layer_get_xcf_flags (GimpTextLayer * text_layer)
name|gimp_text_layer_get_xcf_flags
parameter_list|(
name|GimpTextLayer
modifier|*
name|text_layer
parameter_list|)
block|{
name|guint
name|flags
init|=
literal|0
decl_stmt|;
name|g_return_val_if_fail
argument_list|(
name|GIMP_IS_TEXT_LAYER
argument_list|(
name|text_layer
argument_list|)
argument_list|,
literal|0
argument_list|)
expr_stmt|;
if|if
condition|(
operator|!
name|text_layer
operator|->
name|auto_rename
condition|)
name|flags
operator||=
name|TEXT_LAYER_XCF_DONT_AUTO_RENAME
expr_stmt|;
if|if
condition|(
name|text_layer
operator|->
name|modified
condition|)
name|flags
operator||=
name|TEXT_LAYER_XCF_MODIFIED
expr_stmt|;
return|return
name|flags
return|;
block|}
end_function

begin_function
name|void
DECL|function|gimp_text_layer_set_xcf_flags (GimpTextLayer * text_layer,guint32 flags)
name|gimp_text_layer_set_xcf_flags
parameter_list|(
name|GimpTextLayer
modifier|*
name|text_layer
parameter_list|,
name|guint32
name|flags
parameter_list|)
block|{
name|g_return_if_fail
argument_list|(
name|GIMP_IS_TEXT_LAYER
argument_list|(
name|text_layer
argument_list|)
argument_list|)
expr_stmt|;
name|g_object_set
argument_list|(
name|text_layer
argument_list|,
literal|"auto-rename"
argument_list|,
operator|(
name|flags
operator|&
name|TEXT_LAYER_XCF_DONT_AUTO_RENAME
operator|)
operator|==
literal|0
argument_list|,
literal|"modified"
argument_list|,
operator|(
name|flags
operator|&
name|TEXT_LAYER_XCF_MODIFIED
operator|)
operator|!=
literal|0
argument_list|,
name|NULL
argument_list|)
expr_stmt|;
block|}
end_function

begin_comment
comment|/**  * gimp_text_layer_from_layer:  * @layer: a #GimpLayer object  * @text: a #GimpText object  *  * Converts a standard #GimpLayer and a #GimpText object into a  * #GimpTextLayer. The new text layer takes ownership of the @text and  * @layer objects.  The @layer object is rendered unusable by this  * function. Don't even try to use if afterwards!  *  * This is a gross hack that is needed in order to load text layers  * from XCF files in a backwards-compatible way. Please don't use it  * for anything else!  *  * Return value: a newly allocated #GimpTextLayer object  **/
end_comment

begin_function
specifier|static
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
name|visible
operator|=
name|gimp_item_get_visible
argument_list|(
name|GIMP_ITEM
argument_list|(
name|layer
argument_list|)
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
name|lock_alpha
operator|=
name|gimp_layer_get_lock_alpha
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
name|text
argument_list|)
expr_stmt|;
name|g_object_unref
argument_list|(
name|layer
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

end_unit

