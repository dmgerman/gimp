begin_unit|revision:0.9.5;language:C;cregit-version:0.0.1
begin_comment
comment|/* The GIMP -- an image manipulation program  * Copyright (C) 1995 Spencer Kimball and Peter Mattis  *  * gimpfont.c  * Copyright (C) 2003 Michael Natterer<mitch@gimp.org>  *                    Sven Neumann<sven@gimp.org>  *  * This program is free software; you can redistribute it and/or modify  * it under the terms of the GNU General Public License as published by  * the Free Software Foundation; either version 2 of the License, or  * (at your option) any later version.  *  * This program is distributed in the hope that it will be useful,  * but WITHOUT ANY WARRANTY; without even the implied warranty of  * MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the  * GNU General Public License for more details.  *  * You should have received a copy of the GNU General Public License  * along with this program; if not, write to the Free Software  * Foundation, Inc., 59 Temple Place - Suite 330, Boston, MA 02111-1307, USA.  */
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
file|"text-types.h"
end_include

begin_include
include|#
directive|include
file|"base/temp-buf.h"
end_include

begin_include
include|#
directive|include
file|"gimpfont.h"
end_include

begin_include
include|#
directive|include
file|"gimp-intl.h"
end_include

begin_comment
comment|/* This is a so-called pangram; it's supposed to    contain all characters found in the alphabet. */
end_comment

begin_define
DECL|macro|GIMP_TEXT_PANGRAM
define|#
directive|define
name|GIMP_TEXT_PANGRAM
value|N_("Pack my box with\nfive dozen liquor jugs.")
end_define

begin_enum
enum|enum
DECL|enum|__anon2c7f32460103
block|{
DECL|enumerator|PROP_0
name|PROP_0
block|,
DECL|enumerator|PROP_PANGO_CONTEXT
name|PROP_PANGO_CONTEXT
block|}
enum|;
end_enum

begin_struct
DECL|struct|_GimpFont
struct|struct
name|_GimpFont
block|{
DECL|member|parent_instance
name|GimpViewable
name|parent_instance
decl_stmt|;
DECL|member|pango_context
name|PangoContext
modifier|*
name|pango_context
decl_stmt|;
DECL|member|popup_layout
name|PangoLayout
modifier|*
name|popup_layout
decl_stmt|;
DECL|member|popup_width
name|gint
name|popup_width
decl_stmt|;
DECL|member|popup_height
name|gint
name|popup_height
decl_stmt|;
block|}
struct|;
end_struct

begin_struct
DECL|struct|_GimpFontClass
struct|struct
name|_GimpFontClass
block|{
DECL|member|parent_class
name|GimpViewableClass
name|parent_class
decl_stmt|;
block|}
struct|;
end_struct

begin_function_decl
specifier|static
name|void
name|gimp_font_class_init
parameter_list|(
name|GimpFontClass
modifier|*
name|klass
parameter_list|)
function_decl|;
end_function_decl

begin_function_decl
specifier|static
name|void
name|gimp_font_init
parameter_list|(
name|GimpFont
modifier|*
name|font
parameter_list|)
function_decl|;
end_function_decl

begin_function_decl
specifier|static
name|void
name|gimp_font_finalize
parameter_list|(
name|GObject
modifier|*
name|object
parameter_list|)
function_decl|;
end_function_decl

begin_function_decl
specifier|static
name|void
name|gimp_font_set_property
parameter_list|(
name|GObject
modifier|*
name|object
parameter_list|,
name|guint
name|property_id
parameter_list|,
specifier|const
name|GValue
modifier|*
name|value
parameter_list|,
name|GParamSpec
modifier|*
name|pspec
parameter_list|)
function_decl|;
end_function_decl

begin_function_decl
specifier|static
name|void
name|gimp_font_get_preview_size
parameter_list|(
name|GimpViewable
modifier|*
name|viewable
parameter_list|,
name|gint
name|size
parameter_list|,
name|gboolean
name|popup
parameter_list|,
name|gboolean
name|dot_for_dot
parameter_list|,
name|gint
modifier|*
name|width
parameter_list|,
name|gint
modifier|*
name|height
parameter_list|)
function_decl|;
end_function_decl

begin_function_decl
specifier|static
name|gboolean
name|gimp_font_get_popup_size
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
parameter_list|,
name|gboolean
name|dot_for_dot
parameter_list|,
name|gint
modifier|*
name|popup_width
parameter_list|,
name|gint
modifier|*
name|popup_height
parameter_list|)
function_decl|;
end_function_decl

begin_function_decl
specifier|static
name|TempBuf
modifier|*
name|gimp_font_get_new_preview
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

begin_decl_stmt
DECL|variable|parent_class
specifier|static
name|GimpViewableClass
modifier|*
name|parent_class
init|=
name|NULL
decl_stmt|;
end_decl_stmt

begin_function
name|GType
DECL|function|gimp_font_get_type (void)
name|gimp_font_get_type
parameter_list|(
name|void
parameter_list|)
block|{
specifier|static
name|GType
name|font_type
init|=
literal|0
decl_stmt|;
if|if
condition|(
operator|!
name|font_type
condition|)
block|{
specifier|static
specifier|const
name|GTypeInfo
name|font_info
init|=
block|{
sizeof|sizeof
argument_list|(
name|GimpFontClass
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
name|gimp_font_class_init
block|,
name|NULL
block|,
comment|/* class_finalize */
name|NULL
block|,
comment|/* class_font     */
sizeof|sizeof
argument_list|(
name|GimpFont
argument_list|)
block|,
literal|0
block|,
comment|/* n_preallocs    */
operator|(
name|GInstanceInitFunc
operator|)
name|gimp_font_init
block|,       }
decl_stmt|;
name|font_type
operator|=
name|g_type_register_static
argument_list|(
name|GIMP_TYPE_VIEWABLE
argument_list|,
literal|"GimpFont"
argument_list|,
operator|&
name|font_info
argument_list|,
literal|0
argument_list|)
expr_stmt|;
block|}
return|return
name|font_type
return|;
block|}
end_function

begin_function
specifier|static
name|void
DECL|function|gimp_font_class_init (GimpFontClass * klass)
name|gimp_font_class_init
parameter_list|(
name|GimpFontClass
modifier|*
name|klass
parameter_list|)
block|{
name|GObjectClass
modifier|*
name|object_class
decl_stmt|;
name|GimpViewableClass
modifier|*
name|viewable_class
decl_stmt|;
name|GParamSpec
modifier|*
name|param_spec
decl_stmt|;
name|object_class
operator|=
name|G_OBJECT_CLASS
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
name|finalize
operator|=
name|gimp_font_finalize
expr_stmt|;
name|object_class
operator|->
name|set_property
operator|=
name|gimp_font_set_property
expr_stmt|;
name|viewable_class
operator|->
name|get_preview_size
operator|=
name|gimp_font_get_preview_size
expr_stmt|;
name|viewable_class
operator|->
name|get_popup_size
operator|=
name|gimp_font_get_popup_size
expr_stmt|;
name|viewable_class
operator|->
name|get_new_preview
operator|=
name|gimp_font_get_new_preview
expr_stmt|;
name|viewable_class
operator|->
name|default_stock_id
operator|=
literal|"gtk-font"
expr_stmt|;
name|param_spec
operator|=
name|g_param_spec_object
argument_list|(
literal|"pango-context"
argument_list|,
name|NULL
argument_list|,
name|NULL
argument_list|,
name|PANGO_TYPE_CONTEXT
argument_list|,
name|G_PARAM_WRITABLE
argument_list|)
expr_stmt|;
name|g_object_class_install_property
argument_list|(
name|object_class
argument_list|,
name|PROP_PANGO_CONTEXT
argument_list|,
name|param_spec
argument_list|)
expr_stmt|;
block|}
end_function

begin_function
specifier|static
name|void
DECL|function|gimp_font_init (GimpFont * font)
name|gimp_font_init
parameter_list|(
name|GimpFont
modifier|*
name|font
parameter_list|)
block|{
name|font
operator|->
name|pango_context
operator|=
name|NULL
expr_stmt|;
block|}
end_function

begin_function
specifier|static
name|void
DECL|function|gimp_font_finalize (GObject * object)
name|gimp_font_finalize
parameter_list|(
name|GObject
modifier|*
name|object
parameter_list|)
block|{
name|GimpFont
modifier|*
name|font
init|=
name|GIMP_FONT
argument_list|(
name|object
argument_list|)
decl_stmt|;
if|if
condition|(
name|font
operator|->
name|pango_context
condition|)
block|{
name|g_object_unref
argument_list|(
name|font
operator|->
name|pango_context
argument_list|)
expr_stmt|;
name|font
operator|->
name|pango_context
operator|=
name|NULL
expr_stmt|;
block|}
if|if
condition|(
name|font
operator|->
name|popup_layout
condition|)
block|{
name|g_object_unref
argument_list|(
name|font
operator|->
name|popup_layout
argument_list|)
expr_stmt|;
name|font
operator|->
name|popup_layout
operator|=
name|NULL
expr_stmt|;
block|}
name|G_OBJECT_CLASS
argument_list|(
name|parent_class
argument_list|)
operator|->
name|finalize
argument_list|(
name|object
argument_list|)
expr_stmt|;
block|}
end_function

begin_function
specifier|static
name|void
DECL|function|gimp_font_set_property (GObject * object,guint property_id,const GValue * value,GParamSpec * pspec)
name|gimp_font_set_property
parameter_list|(
name|GObject
modifier|*
name|object
parameter_list|,
name|guint
name|property_id
parameter_list|,
specifier|const
name|GValue
modifier|*
name|value
parameter_list|,
name|GParamSpec
modifier|*
name|pspec
parameter_list|)
block|{
name|GimpFont
modifier|*
name|font
init|=
name|GIMP_FONT
argument_list|(
name|object
argument_list|)
decl_stmt|;
switch|switch
condition|(
name|property_id
condition|)
block|{
case|case
name|PROP_PANGO_CONTEXT
case|:
if|if
condition|(
name|font
operator|->
name|pango_context
condition|)
name|g_object_unref
argument_list|(
name|font
operator|->
name|pango_context
argument_list|)
expr_stmt|;
name|font
operator|->
name|pango_context
operator|=
operator|(
name|PangoContext
operator|*
operator|)
name|g_value_dup_object
argument_list|(
name|value
argument_list|)
expr_stmt|;
break|break;
default|default:
name|G_OBJECT_WARN_INVALID_PROPERTY_ID
argument_list|(
name|object
argument_list|,
name|property_id
argument_list|,
name|pspec
argument_list|)
expr_stmt|;
break|break;
block|}
block|}
end_function

begin_function
specifier|static
name|void
DECL|function|gimp_font_get_preview_size (GimpViewable * viewable,gint size,gboolean popup,gboolean dot_for_dot,gint * width,gint * height)
name|gimp_font_get_preview_size
parameter_list|(
name|GimpViewable
modifier|*
name|viewable
parameter_list|,
name|gint
name|size
parameter_list|,
name|gboolean
name|popup
parameter_list|,
name|gboolean
name|dot_for_dot
parameter_list|,
name|gint
modifier|*
name|width
parameter_list|,
name|gint
modifier|*
name|height
parameter_list|)
block|{
operator|*
name|width
operator|=
name|size
expr_stmt|;
operator|*
name|height
operator|=
name|size
expr_stmt|;
block|}
end_function

begin_function
specifier|static
name|gboolean
DECL|function|gimp_font_get_popup_size (GimpViewable * viewable,gint width,gint height,gboolean dot_for_dot,gint * popup_width,gint * popup_height)
name|gimp_font_get_popup_size
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
parameter_list|,
name|gboolean
name|dot_for_dot
parameter_list|,
name|gint
modifier|*
name|popup_width
parameter_list|,
name|gint
modifier|*
name|popup_height
parameter_list|)
block|{
name|GimpFont
modifier|*
name|font
decl_stmt|;
name|PangoFontDescription
modifier|*
name|font_desc
decl_stmt|;
name|PangoRectangle
name|logical
decl_stmt|;
specifier|const
name|gchar
modifier|*
name|name
decl_stmt|;
name|font
operator|=
name|GIMP_FONT
argument_list|(
name|viewable
argument_list|)
expr_stmt|;
if|if
condition|(
operator|!
name|font
operator|->
name|pango_context
condition|)
return|return
name|FALSE
return|;
name|name
operator|=
name|gimp_object_get_name
argument_list|(
name|GIMP_OBJECT
argument_list|(
name|font
argument_list|)
argument_list|)
expr_stmt|;
name|font_desc
operator|=
name|pango_font_description_from_string
argument_list|(
name|name
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
name|height
operator|=
name|CLAMP
argument_list|(
name|height
argument_list|,
literal|12
argument_list|,
name|GIMP_VIEWABLE_MAX_POPUP_SIZE
operator|/
literal|4
argument_list|)
expr_stmt|;
name|pango_font_description_set_size
argument_list|(
name|font_desc
argument_list|,
name|PANGO_SCALE
operator|*
name|height
operator|*
literal|2.0
operator|/
literal|3.0
argument_list|)
expr_stmt|;
if|if
condition|(
name|font
operator|->
name|popup_layout
condition|)
name|g_object_unref
argument_list|(
name|font
operator|->
name|popup_layout
argument_list|)
expr_stmt|;
name|font
operator|->
name|popup_layout
operator|=
name|pango_layout_new
argument_list|(
name|font
operator|->
name|pango_context
argument_list|)
expr_stmt|;
name|pango_layout_set_font_description
argument_list|(
name|font
operator|->
name|popup_layout
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
name|font
operator|->
name|popup_layout
argument_list|,
name|gettext
argument_list|(
name|GIMP_TEXT_PANGRAM
argument_list|)
argument_list|,
operator|-
literal|1
argument_list|)
expr_stmt|;
name|pango_layout_get_pixel_extents
argument_list|(
name|font
operator|->
name|popup_layout
argument_list|,
name|NULL
argument_list|,
operator|&
name|logical
argument_list|)
expr_stmt|;
operator|*
name|popup_width
operator|=
name|logical
operator|.
name|width
operator|+
literal|6
expr_stmt|;
operator|*
name|popup_height
operator|=
name|logical
operator|.
name|height
operator|+
literal|6
expr_stmt|;
name|font
operator|->
name|popup_width
operator|=
operator|*
name|popup_width
expr_stmt|;
name|font
operator|->
name|popup_height
operator|=
operator|*
name|popup_height
expr_stmt|;
return|return
name|TRUE
return|;
block|}
end_function

begin_function
specifier|static
name|TempBuf
modifier|*
DECL|function|gimp_font_get_new_preview (GimpViewable * viewable,gint width,gint height)
name|gimp_font_get_new_preview
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
name|GimpFont
modifier|*
name|font
decl_stmt|;
name|PangoLayout
modifier|*
name|layout
decl_stmt|;
name|PangoRectangle
name|logical
decl_stmt|;
name|TempBuf
modifier|*
name|temp_buf
decl_stmt|;
name|FT_Bitmap
name|bitmap
decl_stmt|;
name|guchar
modifier|*
name|p
decl_stmt|;
name|guchar
name|black
init|=
literal|0
decl_stmt|;
name|font
operator|=
name|GIMP_FONT
argument_list|(
name|viewable
argument_list|)
expr_stmt|;
if|if
condition|(
operator|!
name|font
operator|->
name|pango_context
condition|)
return|return
name|NULL
return|;
if|if
condition|(
operator|!
name|font
operator|->
name|popup_layout
operator|||
name|font
operator|->
name|popup_width
operator|!=
name|width
operator|||
name|font
operator|->
name|popup_height
operator|!=
name|height
condition|)
block|{
name|PangoFontDescription
modifier|*
name|font_desc
decl_stmt|;
specifier|const
name|gchar
modifier|*
name|name
decl_stmt|;
name|name
operator|=
name|gimp_object_get_name
argument_list|(
name|GIMP_OBJECT
argument_list|(
name|font
argument_list|)
argument_list|)
expr_stmt|;
name|font_desc
operator|=
name|pango_font_description_from_string
argument_list|(
name|name
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
name|pango_font_description_set_size
argument_list|(
name|font_desc
argument_list|,
name|PANGO_SCALE
operator|*
name|height
operator|*
literal|2.0
operator|/
literal|3.0
argument_list|)
expr_stmt|;
name|layout
operator|=
name|pango_layout_new
argument_list|(
name|font
operator|->
name|pango_context
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
literal|"Aa"
argument_list|,
operator|-
literal|1
argument_list|)
expr_stmt|;
block|}
else|else
block|{
name|layout
operator|=
name|g_object_ref
argument_list|(
name|font
operator|->
name|popup_layout
argument_list|)
expr_stmt|;
block|}
name|temp_buf
operator|=
name|temp_buf_new
argument_list|(
name|width
argument_list|,
name|height
argument_list|,
literal|1
argument_list|,
literal|0
argument_list|,
literal|0
argument_list|,
operator|&
name|black
argument_list|)
expr_stmt|;
name|bitmap
operator|.
name|width
operator|=
name|temp_buf
operator|->
name|width
expr_stmt|;
name|bitmap
operator|.
name|rows
operator|=
name|temp_buf
operator|->
name|height
expr_stmt|;
name|bitmap
operator|.
name|pitch
operator|=
name|temp_buf
operator|->
name|width
expr_stmt|;
name|bitmap
operator|.
name|buffer
operator|=
name|temp_buf_data
argument_list|(
name|temp_buf
argument_list|)
expr_stmt|;
name|pango_layout_get_pixel_extents
argument_list|(
name|layout
argument_list|,
name|NULL
argument_list|,
operator|&
name|logical
argument_list|)
expr_stmt|;
name|pango_ft2_render_layout
argument_list|(
operator|&
name|bitmap
argument_list|,
name|layout
argument_list|,
operator|(
name|bitmap
operator|.
name|width
operator|-
name|logical
operator|.
name|width
operator|)
operator|/
literal|2
argument_list|,
operator|(
name|bitmap
operator|.
name|rows
operator|-
name|logical
operator|.
name|height
operator|)
operator|/
literal|2
argument_list|)
expr_stmt|;
name|g_object_unref
argument_list|(
name|layout
argument_list|)
expr_stmt|;
name|p
operator|=
name|temp_buf_data
argument_list|(
name|temp_buf
argument_list|)
expr_stmt|;
for|for
control|(
name|height
operator|=
name|temp_buf
operator|->
name|height
init|;
name|height
condition|;
name|height
operator|--
control|)
for|for
control|(
name|width
operator|=
name|temp_buf
operator|->
name|width
init|;
name|width
condition|;
name|width
operator|--
operator|,
name|p
operator|++
control|)
operator|*
name|p
operator|=
literal|255
operator|-
operator|*
name|p
expr_stmt|;
return|return
name|temp_buf
return|;
block|}
end_function

begin_function
name|GimpFont
modifier|*
DECL|function|gimp_font_get_standard (void)
name|gimp_font_get_standard
parameter_list|(
name|void
parameter_list|)
block|{
specifier|static
name|GimpFont
modifier|*
name|standard_font
init|=
name|NULL
decl_stmt|;
if|if
condition|(
operator|!
name|standard_font
condition|)
name|standard_font
operator|=
name|g_object_new
argument_list|(
name|GIMP_TYPE_FONT
argument_list|,
literal|"name"
argument_list|,
literal|"Sans"
argument_list|,
name|NULL
argument_list|)
expr_stmt|;
return|return
name|standard_font
return|;
block|}
end_function

end_unit

