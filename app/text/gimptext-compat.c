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
file|"libgimpcolor/gimpcolor.h"
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
file|"core/gimpchannel.h"
end_include

begin_include
include|#
directive|include
file|"core/gimpcontext.h"
end_include

begin_include
include|#
directive|include
file|"core/gimpimage.h"
end_include

begin_include
include|#
directive|include
file|"core/gimpcontext.h"
end_include

begin_include
include|#
directive|include
file|"core/gimpdrawable.h"
end_include

begin_include
include|#
directive|include
file|"core/gimpimage.h"
end_include

begin_include
include|#
directive|include
file|"core/gimpimage-undo.h"
end_include

begin_include
include|#
directive|include
file|"core/gimplayer-floating-sel.h"
end_include

begin_include
include|#
directive|include
file|"gimptext.h"
end_include

begin_include
include|#
directive|include
file|"gimptext-compat.h"
end_include

begin_include
include|#
directive|include
file|"gimptextlayer.h"
end_include

begin_include
include|#
directive|include
file|"gimp-intl.h"
end_include

begin_function
name|GimpLayer
modifier|*
DECL|function|text_render (GimpImage * gimage,GimpDrawable * drawable,gint text_x,gint text_y,const gchar * fontname,const gchar * text,gint border,gboolean antialias)
name|text_render
parameter_list|(
name|GimpImage
modifier|*
name|gimage
parameter_list|,
name|GimpDrawable
modifier|*
name|drawable
parameter_list|,
name|gint
name|text_x
parameter_list|,
name|gint
name|text_y
parameter_list|,
specifier|const
name|gchar
modifier|*
name|fontname
parameter_list|,
specifier|const
name|gchar
modifier|*
name|text
parameter_list|,
name|gint
name|border
parameter_list|,
name|gboolean
name|antialias
parameter_list|)
block|{
name|PangoFontDescription
modifier|*
name|desc
decl_stmt|;
name|GimpText
modifier|*
name|gtext
decl_stmt|;
name|GimpLayer
modifier|*
name|layer
decl_stmt|;
name|GimpRGB
name|color
decl_stmt|;
name|gchar
modifier|*
name|font
decl_stmt|;
name|gdouble
name|size
decl_stmt|;
name|g_return_val_if_fail
argument_list|(
name|GIMP_IS_IMAGE
argument_list|(
name|gimage
argument_list|)
argument_list|,
name|FALSE
argument_list|)
expr_stmt|;
name|g_return_val_if_fail
argument_list|(
name|drawable
operator|==
name|NULL
operator|||
name|GIMP_IS_DRAWABLE
argument_list|(
name|drawable
argument_list|)
argument_list|,
name|FALSE
argument_list|)
expr_stmt|;
name|g_return_val_if_fail
argument_list|(
name|drawable
operator|==
name|NULL
operator|||
name|gimp_item_is_attached
argument_list|(
name|GIMP_ITEM
argument_list|(
name|drawable
argument_list|)
argument_list|)
argument_list|,
name|FALSE
argument_list|)
expr_stmt|;
name|g_return_val_if_fail
argument_list|(
name|fontname
operator|!=
name|NULL
argument_list|,
name|FALSE
argument_list|)
expr_stmt|;
name|g_return_val_if_fail
argument_list|(
name|text
operator|!=
name|NULL
argument_list|,
name|FALSE
argument_list|)
expr_stmt|;
if|if
condition|(
name|border
operator|<
literal|0
condition|)
name|border
operator|=
literal|0
expr_stmt|;
name|desc
operator|=
name|pango_font_description_from_string
argument_list|(
name|fontname
argument_list|)
expr_stmt|;
name|size
operator|=
name|PANGO_PIXELS
argument_list|(
name|pango_font_description_get_size
argument_list|(
name|desc
argument_list|)
argument_list|)
expr_stmt|;
name|pango_font_description_unset_fields
argument_list|(
name|desc
argument_list|,
name|PANGO_FONT_MASK_SIZE
argument_list|)
expr_stmt|;
name|font
operator|=
name|pango_font_description_to_string
argument_list|(
name|desc
argument_list|)
expr_stmt|;
name|pango_font_description_free
argument_list|(
name|desc
argument_list|)
expr_stmt|;
name|gimp_context_get_foreground
argument_list|(
name|gimp_get_current_context
argument_list|(
name|gimage
operator|->
name|gimp
argument_list|)
argument_list|,
operator|&
name|color
argument_list|)
expr_stmt|;
name|gtext
operator|=
name|g_object_new
argument_list|(
name|GIMP_TYPE_TEXT
argument_list|,
literal|"text"
argument_list|,
name|text
argument_list|,
literal|"font"
argument_list|,
name|font
argument_list|,
literal|"font-size"
argument_list|,
name|size
argument_list|,
literal|"antialias"
argument_list|,
name|antialias
argument_list|,
literal|"border"
argument_list|,
name|border
argument_list|,
literal|"color"
argument_list|,
operator|&
name|color
argument_list|,
name|NULL
argument_list|)
expr_stmt|;
name|g_free
argument_list|(
name|font
argument_list|)
expr_stmt|;
name|layer
operator|=
name|gimp_text_layer_new
argument_list|(
name|gimage
argument_list|,
name|gtext
argument_list|)
expr_stmt|;
name|g_object_unref
argument_list|(
name|gtext
argument_list|)
expr_stmt|;
if|if
condition|(
operator|!
name|layer
condition|)
return|return
name|NULL
return|;
comment|/*  Start a group undo  */
name|gimp_image_undo_group_start
argument_list|(
name|gimage
argument_list|,
name|GIMP_UNDO_GROUP_TEXT
argument_list|,
name|_
argument_list|(
literal|"Add Text Layer"
argument_list|)
argument_list|)
expr_stmt|;
comment|/*  Set the layer offsets  */
name|GIMP_ITEM
argument_list|(
name|layer
argument_list|)
operator|->
name|offset_x
operator|=
name|text_x
expr_stmt|;
name|GIMP_ITEM
argument_list|(
name|layer
argument_list|)
operator|->
name|offset_y
operator|=
name|text_y
expr_stmt|;
comment|/*  If there is a selection mask clear it--    *  this might not always be desired, but in general,    *  it seems like the correct behavior.    */
if|if
condition|(
operator|!
name|gimp_channel_is_empty
argument_list|(
name|gimp_image_get_mask
argument_list|(
name|gimage
argument_list|)
argument_list|)
condition|)
name|gimp_channel_clear
argument_list|(
name|gimp_image_get_mask
argument_list|(
name|gimage
argument_list|)
argument_list|,
name|NULL
argument_list|,
name|TRUE
argument_list|)
expr_stmt|;
comment|/*  If the drawable is NULL, create a new layer  */
if|if
condition|(
name|drawable
operator|==
name|NULL
condition|)
name|gimp_image_add_layer
argument_list|(
name|gimage
argument_list|,
name|layer
argument_list|,
operator|-
literal|1
argument_list|)
expr_stmt|;
comment|/*  Otherwise, instantiate the text as the new floating selection */
else|else
name|floating_sel_attach
argument_list|(
name|layer
argument_list|,
name|drawable
argument_list|)
expr_stmt|;
comment|/*  end the group undo  */
name|gimp_image_undo_group_end
argument_list|(
name|gimage
argument_list|)
expr_stmt|;
return|return
name|layer
return|;
block|}
end_function

begin_function
name|gboolean
DECL|function|text_get_extents (const gchar * fontname,const gchar * text,gint * width,gint * height,gint * ascent,gint * descent)
name|text_get_extents
parameter_list|(
specifier|const
name|gchar
modifier|*
name|fontname
parameter_list|,
specifier|const
name|gchar
modifier|*
name|text
parameter_list|,
name|gint
modifier|*
name|width
parameter_list|,
name|gint
modifier|*
name|height
parameter_list|,
name|gint
modifier|*
name|ascent
parameter_list|,
name|gint
modifier|*
name|descent
parameter_list|)
block|{
name|PangoFontDescription
modifier|*
name|font_desc
decl_stmt|;
name|PangoContext
modifier|*
name|context
decl_stmt|;
name|PangoLayout
modifier|*
name|layout
decl_stmt|;
name|PangoFontMap
modifier|*
name|fontmap
decl_stmt|;
name|PangoRectangle
name|rect
decl_stmt|;
name|g_return_val_if_fail
argument_list|(
name|fontname
operator|!=
name|NULL
argument_list|,
name|FALSE
argument_list|)
expr_stmt|;
name|g_return_val_if_fail
argument_list|(
name|text
operator|!=
name|NULL
argument_list|,
name|FALSE
argument_list|)
expr_stmt|;
comment|/* FIXME: resolution */
name|fontmap
operator|=
name|pango_ft2_font_map_new
argument_list|()
expr_stmt|;
name|pango_ft2_font_map_set_resolution
argument_list|(
name|PANGO_FT2_FONT_MAP
argument_list|(
name|fontmap
argument_list|)
argument_list|,
literal|72.0
argument_list|,
literal|72.0
argument_list|)
expr_stmt|;
name|context
operator|=
name|pango_ft2_font_map_create_context
argument_list|(
name|PANGO_FT2_FONT_MAP
argument_list|(
name|fontmap
argument_list|)
argument_list|)
expr_stmt|;
name|g_object_unref
argument_list|(
name|fontmap
argument_list|)
expr_stmt|;
name|layout
operator|=
name|pango_layout_new
argument_list|(
name|context
argument_list|)
expr_stmt|;
name|g_object_unref
argument_list|(
name|context
argument_list|)
expr_stmt|;
name|font_desc
operator|=
name|pango_font_description_from_string
argument_list|(
name|fontname
argument_list|)
expr_stmt|;
name|pango_layout_set_font_description
argument_list|(
name|layout
argument_list|,
name|font_desc
argument_list|)
expr_stmt|;
name|pango_font_description_free
argument_list|(
name|font_desc
argument_list|)
expr_stmt|;
name|pango_layout_set_text
argument_list|(
name|layout
argument_list|,
name|text
argument_list|,
operator|-
literal|1
argument_list|)
expr_stmt|;
name|pango_layout_get_pixel_extents
argument_list|(
name|layout
argument_list|,
name|NULL
argument_list|,
operator|&
name|rect
argument_list|)
expr_stmt|;
if|if
condition|(
name|width
condition|)
operator|*
name|width
operator|=
name|rect
operator|.
name|width
expr_stmt|;
if|if
condition|(
name|height
condition|)
operator|*
name|height
operator|=
name|rect
operator|.
name|height
expr_stmt|;
if|if
condition|(
name|ascent
operator|||
name|descent
condition|)
block|{
name|PangoLayoutIter
modifier|*
name|iter
decl_stmt|;
name|PangoLayoutLine
modifier|*
name|line
decl_stmt|;
name|iter
operator|=
name|pango_layout_get_iter
argument_list|(
name|layout
argument_list|)
expr_stmt|;
name|line
operator|=
name|pango_layout_iter_get_line
argument_list|(
name|iter
argument_list|)
expr_stmt|;
name|pango_layout_iter_free
argument_list|(
name|iter
argument_list|)
expr_stmt|;
name|pango_layout_line_get_pixel_extents
argument_list|(
name|line
argument_list|,
name|NULL
argument_list|,
operator|&
name|rect
argument_list|)
expr_stmt|;
if|if
condition|(
name|ascent
condition|)
operator|*
name|ascent
operator|=
name|PANGO_ASCENT
argument_list|(
name|rect
argument_list|)
expr_stmt|;
if|if
condition|(
name|descent
condition|)
operator|*
name|descent
operator|=
operator|-
name|PANGO_DESCENT
argument_list|(
name|rect
argument_list|)
expr_stmt|;
block|}
name|g_object_unref
argument_list|(
name|layout
argument_list|)
expr_stmt|;
return|return
name|TRUE
return|;
block|}
end_function

end_unit

