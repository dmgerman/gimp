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
file|"gimpdrawable.h"
end_include

begin_include
include|#
directive|include
file|"gimpimage.h"
end_include

begin_include
include|#
directive|include
file|"gimpimage-mask.h"
end_include

begin_include
include|#
directive|include
file|"gimpimage-text.h"
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

begin_function
name|GimpLayer
modifier|*
DECL|function|text_render (GimpImage * gimage,GimpDrawable * drawable,gint text_x,gint text_y,const gchar * fontname,const gchar * text,gint border,gint antialias)
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
name|gint
name|antialias
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
name|PangoRectangle
name|ink
decl_stmt|;
name|PangoRectangle
name|logical
decl_stmt|;
name|GimpImageType
name|layer_type
decl_stmt|;
name|GimpLayer
modifier|*
name|layer
init|=
name|NULL
decl_stmt|;
name|gdouble
name|xres
decl_stmt|;
name|gdouble
name|yres
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
comment|/*  determine the layer type  */
if|if
condition|(
name|drawable
condition|)
name|layer_type
operator|=
name|gimp_drawable_type_with_alpha
argument_list|(
name|drawable
argument_list|)
expr_stmt|;
else|else
name|layer_type
operator|=
name|gimp_image_base_type_with_alpha
argument_list|(
name|gimage
argument_list|)
expr_stmt|;
name|font_desc
operator|=
name|pango_font_description_from_string
argument_list|(
name|fontname
argument_list|)
expr_stmt|;
name|g_return_val_if_fail
argument_list|(
name|font_desc
operator|!=
name|NULL
argument_list|,
name|NULL
argument_list|)
expr_stmt|;
if|if
condition|(
operator|!
name|font_desc
condition|)
return|return
name|NULL
return|;
name|gimp_image_get_resolution
argument_list|(
name|gimage
argument_list|,
operator|&
name|xres
argument_list|,
operator|&
name|yres
argument_list|)
expr_stmt|;
name|context
operator|=
name|pango_ft2_get_context
argument_list|(
name|xres
argument_list|,
name|yres
argument_list|)
expr_stmt|;
name|layout
operator|=
name|pango_layout_new
argument_list|(
name|context
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
operator|&
name|ink
argument_list|,
operator|&
name|logical
argument_list|)
expr_stmt|;
name|g_print
argument_list|(
literal|"ink rect: %d x %d @ %d, %d\n"
argument_list|,
name|ink
operator|.
name|width
argument_list|,
name|ink
operator|.
name|height
argument_list|,
name|ink
operator|.
name|x
argument_list|,
name|ink
operator|.
name|y
argument_list|)
expr_stmt|;
name|g_print
argument_list|(
literal|"logical rect: %d x %d @ %d, %d\n"
argument_list|,
name|logical
operator|.
name|width
argument_list|,
name|logical
operator|.
name|height
argument_list|,
name|logical
operator|.
name|x
argument_list|,
name|logical
operator|.
name|y
argument_list|)
expr_stmt|;
if|if
condition|(
name|ink
operator|.
name|width
operator|>
literal|0
operator|&&
name|ink
operator|.
name|height
operator|>
literal|0
condition|)
block|{
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
name|FT_Bitmap
name|bitmap
decl_stmt|;
name|guchar
modifier|*
name|black
init|=
name|NULL
decl_stmt|;
name|guchar
name|color
index|[
name|MAX_CHANNELS
index|]
decl_stmt|;
name|gint
name|width
decl_stmt|;
name|gint
name|height
decl_stmt|;
name|gint
name|y
decl_stmt|;
name|bitmap
operator|.
name|width
operator|=
name|ink
operator|.
name|width
expr_stmt|;
name|bitmap
operator|.
name|rows
operator|=
name|ink
operator|.
name|height
expr_stmt|;
name|bitmap
operator|.
name|pitch
operator|=
name|ink
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
name|pango_ft2_render_layout
argument_list|(
operator|&
name|bitmap
argument_list|,
name|layout
argument_list|,
operator|-
name|ink
operator|.
name|x
argument_list|,
operator|-
name|ink
operator|.
name|y
argument_list|)
expr_stmt|;
name|width
operator|=
name|ink
operator|.
name|width
operator|+
literal|2
operator|*
name|border
expr_stmt|;
name|height
operator|=
name|ink
operator|.
name|height
operator|+
literal|2
operator|*
name|border
expr_stmt|;
name|mask
operator|=
name|tile_manager_new
argument_list|(
name|width
argument_list|,
name|height
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
name|width
argument_list|,
name|height
argument_list|,
name|TRUE
argument_list|)
expr_stmt|;
if|if
condition|(
name|border
condition|)
name|black
operator|=
name|g_malloc0
argument_list|(
name|width
argument_list|)
expr_stmt|;
for|for
control|(
name|y
operator|=
literal|0
init|;
name|y
operator|<
name|border
condition|;
name|y
operator|++
control|)
name|pixel_region_set_row
argument_list|(
operator|&
name|maskPR
argument_list|,
literal|0
argument_list|,
name|y
argument_list|,
name|width
argument_list|,
name|black
argument_list|)
expr_stmt|;
for|for
control|(
init|;
name|y
operator|<
name|height
operator|-
name|border
condition|;
name|y
operator|++
control|)
block|{
if|if
condition|(
name|border
condition|)
block|{
name|pixel_region_set_row
argument_list|(
operator|&
name|maskPR
argument_list|,
literal|0
argument_list|,
name|y
argument_list|,
name|border
argument_list|,
name|black
argument_list|)
expr_stmt|;
name|pixel_region_set_row
argument_list|(
operator|&
name|maskPR
argument_list|,
name|width
operator|-
name|border
argument_list|,
name|y
argument_list|,
name|border
argument_list|,
name|black
argument_list|)
expr_stmt|;
block|}
name|pixel_region_set_row
argument_list|(
operator|&
name|maskPR
argument_list|,
name|border
argument_list|,
name|y
argument_list|,
name|bitmap
operator|.
name|width
argument_list|,
name|bitmap
operator|.
name|buffer
operator|+
operator|(
name|y
operator|-
name|border
operator|)
operator|*
name|bitmap
operator|.
name|pitch
argument_list|)
expr_stmt|;
block|}
for|for
control|(
init|;
name|y
operator|<
name|height
condition|;
name|y
operator|++
control|)
name|pixel_region_set_row
argument_list|(
operator|&
name|maskPR
argument_list|,
literal|0
argument_list|,
name|y
argument_list|,
name|width
argument_list|,
name|black
argument_list|)
expr_stmt|;
name|g_free
argument_list|(
name|black
argument_list|)
expr_stmt|;
name|g_free
argument_list|(
name|bitmap
operator|.
name|buffer
argument_list|)
expr_stmt|;
name|layer
operator|=
name|gimp_layer_new
argument_list|(
name|gimage
argument_list|,
name|width
argument_list|,
name|height
argument_list|,
name|layer_type
argument_list|,
name|_
argument_list|(
literal|"Text Layer"
argument_list|)
argument_list|,
name|GIMP_OPACITY_OPAQUE
argument_list|,
name|GIMP_NORMAL_MODE
argument_list|)
expr_stmt|;
comment|/*  color the layer buffer  */
name|gimp_image_get_foreground
argument_list|(
name|gimage
argument_list|,
name|drawable
argument_list|,
name|color
argument_list|)
expr_stmt|;
name|color
index|[
name|GIMP_DRAWABLE
argument_list|(
name|layer
argument_list|)
operator|->
name|bytes
operator|-
literal|1
index|]
operator|=
name|OPAQUE_OPACITY
expr_stmt|;
name|pixel_region_init
argument_list|(
operator|&
name|textPR
argument_list|,
name|GIMP_DRAWABLE
argument_list|(
name|layer
argument_list|)
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
name|color_region
argument_list|(
operator|&
name|textPR
argument_list|,
name|color
argument_list|)
expr_stmt|;
comment|/*  apply the text mask  */
name|pixel_region_init
argument_list|(
operator|&
name|textPR
argument_list|,
name|GIMP_DRAWABLE
argument_list|(
name|layer
argument_list|)
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
comment|/*  Start a group undo  */
name|undo_push_group_start
argument_list|(
name|gimage
argument_list|,
name|TEXT_UNDO_GROUP
argument_list|)
expr_stmt|;
comment|/*  Set the layer offsets  */
name|GIMP_DRAWABLE
argument_list|(
name|layer
argument_list|)
operator|->
name|offset_x
operator|=
name|text_x
expr_stmt|;
name|GIMP_DRAWABLE
argument_list|(
name|layer
argument_list|)
operator|->
name|offset_y
operator|=
name|text_y
expr_stmt|;
comment|/*  If there is a selection mask clear it--        *  this might not always be desired, but in general,        *  it seems like the correct behavior.        */
if|if
condition|(
operator|!
name|gimp_image_mask_is_empty
argument_list|(
name|gimage
argument_list|)
condition|)
name|gimp_image_mask_clear
argument_list|(
name|gimage
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
name|undo_push_group_end
argument_list|(
name|gimage
argument_list|)
expr_stmt|;
name|tile_manager_destroy
argument_list|(
name|mask
argument_list|)
expr_stmt|;
block|}
name|g_object_unref
argument_list|(
name|layout
argument_list|)
expr_stmt|;
name|g_object_unref
argument_list|(
name|context
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
name|font_desc
operator|=
name|pango_font_description_from_string
argument_list|(
name|fontname
argument_list|)
expr_stmt|;
if|if
condition|(
operator|!
name|font_desc
condition|)
return|return
name|FALSE
return|;
comment|/* FIXME: resolution */
name|context
operator|=
name|pango_ft2_get_context
argument_list|(
literal|72.0
argument_list|,
literal|72.0
argument_list|)
expr_stmt|;
name|layout
operator|=
name|pango_layout_new
argument_list|(
name|context
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
operator|&
name|rect
argument_list|,
name|NULL
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
condition|)
operator|*
name|ascent
operator|=
operator|-
name|rect
operator|.
name|y
expr_stmt|;
if|if
condition|(
name|descent
condition|)
operator|*
name|descent
operator|=
name|rect
operator|.
name|height
operator|+
name|rect
operator|.
name|y
expr_stmt|;
name|g_object_unref
argument_list|(
name|layout
argument_list|)
expr_stmt|;
name|g_object_unref
argument_list|(
name|context
argument_list|)
expr_stmt|;
return|return
name|TRUE
return|;
block|}
end_function

end_unit

