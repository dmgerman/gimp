begin_unit|revision:0.9.5;language:C;cregit-version:0.0.1
begin_comment
comment|/* GIMP - The GNU Image Manipulation Program  * Copyright (C) 1995 Spencer Kimball and Peter Mattis  *  * GimpTextTag  * Copyright (C) 2010  Michael Natterer<mitch@gimp.org>  *  * This program is free software: you can redistribute it and/or modify  * it under the terms of the GNU General Public License as published by  * the Free Software Foundation; either version 3 of the License, or  * (at your option) any later version.  *  * This program is distributed in the hope that it will be useful,  * but WITHOUT ANY WARRANTY; without even the implied warranty of  * MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the  * GNU General Public License for more details.  *  * You should have received a copy of the GNU General Public License  * along with this program.  If not, see<http://www.gnu.org/licenses/>.  */
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
file|<gtk/gtk.h>
end_include

begin_include
include|#
directive|include
file|"libgimpcolor/gimpcolor.h"
end_include

begin_include
include|#
directive|include
file|"widgets-types.h"
end_include

begin_include
include|#
directive|include
file|"gimptexttag.h"
end_include

begin_function
name|gint
DECL|function|gimp_text_tag_get_size (GtkTextTag * tag)
name|gimp_text_tag_get_size
parameter_list|(
name|GtkTextTag
modifier|*
name|tag
parameter_list|)
block|{
name|gint
name|size
decl_stmt|;
name|g_return_val_if_fail
argument_list|(
name|GTK_IS_TEXT_TAG
argument_list|(
name|tag
argument_list|)
argument_list|,
literal|0
argument_list|)
expr_stmt|;
name|g_object_get
argument_list|(
name|tag
argument_list|,
name|GIMP_TEXT_PROP_NAME_SIZE
argument_list|,
operator|&
name|size
argument_list|,
name|NULL
argument_list|)
expr_stmt|;
return|return
name|size
return|;
block|}
end_function

begin_function
name|gint
DECL|function|gimp_text_tag_get_baseline (GtkTextTag * tag)
name|gimp_text_tag_get_baseline
parameter_list|(
name|GtkTextTag
modifier|*
name|tag
parameter_list|)
block|{
name|gint
name|baseline
decl_stmt|;
name|g_object_get
argument_list|(
name|tag
argument_list|,
name|GIMP_TEXT_PROP_NAME_BASELINE
argument_list|,
operator|&
name|baseline
argument_list|,
name|NULL
argument_list|)
expr_stmt|;
return|return
name|baseline
return|;
block|}
end_function

begin_function
name|gint
DECL|function|gimp_text_tag_get_kerning (GtkTextTag * tag)
name|gimp_text_tag_get_kerning
parameter_list|(
name|GtkTextTag
modifier|*
name|tag
parameter_list|)
block|{
name|gint
name|kerning
decl_stmt|;
name|g_object_get
argument_list|(
name|tag
argument_list|,
name|GIMP_TEXT_PROP_NAME_KERNING
argument_list|,
operator|&
name|kerning
argument_list|,
name|NULL
argument_list|)
expr_stmt|;
return|return
name|kerning
return|;
block|}
end_function

begin_function
name|gchar
modifier|*
DECL|function|gimp_text_tag_get_font (GtkTextTag * tag)
name|gimp_text_tag_get_font
parameter_list|(
name|GtkTextTag
modifier|*
name|tag
parameter_list|)
block|{
name|gchar
modifier|*
name|font
decl_stmt|;
name|g_object_get
argument_list|(
name|tag
argument_list|,
name|GIMP_TEXT_PROP_NAME_FONT
argument_list|,
operator|&
name|font
argument_list|,
name|NULL
argument_list|)
expr_stmt|;
return|return
name|font
return|;
block|}
end_function

begin_function
name|gboolean
DECL|function|gimp_text_tag_get_fg_color (GtkTextTag * tag,GimpRGB * color)
name|gimp_text_tag_get_fg_color
parameter_list|(
name|GtkTextTag
modifier|*
name|tag
parameter_list|,
name|GimpRGB
modifier|*
name|color
parameter_list|)
block|{
name|GdkRGBA
modifier|*
name|rgba
decl_stmt|;
name|gboolean
name|set
decl_stmt|;
name|g_object_get
argument_list|(
name|tag
argument_list|,
literal|"foreground-set"
argument_list|,
operator|&
name|set
argument_list|,
name|GIMP_TEXT_PROP_NAME_FG_COLOR
argument_list|,
operator|&
name|rgba
argument_list|,
name|NULL
argument_list|)
expr_stmt|;
name|gimp_rgb_set
argument_list|(
name|color
argument_list|,
name|rgba
operator|->
name|red
argument_list|,
name|rgba
operator|->
name|green
argument_list|,
name|rgba
operator|->
name|blue
argument_list|)
expr_stmt|;
name|gdk_rgba_free
argument_list|(
name|rgba
argument_list|)
expr_stmt|;
return|return
name|set
return|;
block|}
end_function

begin_function
name|gboolean
DECL|function|gimp_text_tag_get_bg_color (GtkTextTag * tag,GimpRGB * color)
name|gimp_text_tag_get_bg_color
parameter_list|(
name|GtkTextTag
modifier|*
name|tag
parameter_list|,
name|GimpRGB
modifier|*
name|color
parameter_list|)
block|{
name|GdkRGBA
modifier|*
name|rgba
decl_stmt|;
name|gboolean
name|set
decl_stmt|;
name|g_object_get
argument_list|(
name|tag
argument_list|,
literal|"background-set"
argument_list|,
operator|&
name|set
argument_list|,
name|GIMP_TEXT_PROP_NAME_BG_COLOR
argument_list|,
operator|&
name|rgba
argument_list|,
name|NULL
argument_list|)
expr_stmt|;
name|gimp_rgb_set
argument_list|(
name|color
argument_list|,
name|rgba
operator|->
name|red
argument_list|,
name|rgba
operator|->
name|green
argument_list|,
name|rgba
operator|->
name|blue
argument_list|)
expr_stmt|;
name|gdk_rgba_free
argument_list|(
name|rgba
argument_list|)
expr_stmt|;
return|return
name|set
return|;
block|}
end_function

end_unit

