begin_unit|revision:0.9.5;language:C;cregit-version:0.0.1
begin_comment
comment|/* GIMP - The GNU Image Manipulation Program  * Copyright (C) 1995 Spencer Kimball and Peter Mattis  *  * gimpfont.c  * Copyright (C) 2003 Michael Natterer<mitch@gimp.org>  *                    Sven Neumann<sven@gimp.org>  *  * This program is free software: you can redistribute it and/or modify  * it under the terms of the GNU General Public License as published by  * the Free Software Foundation; either version 3 of the License, or  * (at your option) any later version.  *  * This program is distributed in the hope that it will be useful,  * but WITHOUT ANY WARRANTY; without even the implied warranty of  * MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the  * GNU General Public License for more details.  *  * You should have received a copy of the GNU General Public License  * along with this program.  If not, see<http://www.gnu.org/licenses/>.  */
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
file|<pango/pangocairo.h>
end_include

begin_define
DECL|macro|PANGO_ENABLE_ENGINE
define|#
directive|define
name|PANGO_ENABLE_ENGINE
value|1
end_define

begin_comment
DECL|macro|PANGO_ENABLE_ENGINE
comment|/* Argh */
end_comment

begin_include
include|#
directive|include
file|<pango/pango-ot.h>
end_include

begin_include
include|#
directive|include
file|<freetype/tttables.h>
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

begin_define
DECL|macro|GIMP_FONT_POPUP_SIZE
define|#
directive|define
name|GIMP_FONT_POPUP_SIZE
value|(PANGO_SCALE * 30)
end_define

begin_define
DECL|macro|DEBUGPRINT (x)
define|#
directive|define
name|DEBUGPRINT
parameter_list|(
name|x
parameter_list|)
end_define

begin_comment
DECL|macro|DEBUGPRINT (x)
comment|/* g_print x */
end_comment

begin_enum
enum|enum
DECL|enum|__anon278ce8660103
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
name|GimpContext
modifier|*
name|context
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
specifier|const
name|gchar
modifier|*
name|gimp_font_get_sample_string
parameter_list|(
name|PangoContext
modifier|*
name|context
parameter_list|,
name|PangoFontDescription
modifier|*
name|font_desc
parameter_list|)
function_decl|;
end_function_decl

begin_macro
DECL|function|G_DEFINE_TYPE (GimpFont,gimp_font,GIMP_TYPE_VIEWABLE)
name|G_DEFINE_TYPE
argument_list|(
argument|GimpFont
argument_list|,
argument|gimp_font
argument_list|,
argument|GIMP_TYPE_VIEWABLE
argument_list|)
end_macro

begin_define
DECL|macro|parent_class
define|#
directive|define
name|parent_class
value|gimp_font_parent_class
end_define

begin_function
specifier|static
name|void
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
init|=
name|G_OBJECT_CLASS
argument_list|(
name|klass
argument_list|)
decl_stmt|;
name|GimpViewableClass
modifier|*
name|viewable_class
init|=
name|GIMP_VIEWABLE_CLASS
argument_list|(
name|klass
argument_list|)
decl_stmt|;
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
literal|"gtk-select-font"
expr_stmt|;
name|g_object_class_install_property
argument_list|(
name|object_class
argument_list|,
name|PROP_PANGO_CONTEXT
argument_list|,
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
name|GIMP_PARAM_WRITABLE
argument_list|)
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
init|=
name|GIMP_FONT
argument_list|(
name|viewable
argument_list|)
decl_stmt|;
name|PangoFontDescription
modifier|*
name|font_desc
decl_stmt|;
name|PangoRectangle
name|ink
decl_stmt|;
name|PangoRectangle
name|logical
decl_stmt|;
specifier|const
name|gchar
modifier|*
name|name
decl_stmt|;
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
name|font
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
name|FALSE
argument_list|)
expr_stmt|;
name|pango_font_description_set_size
argument_list|(
name|font_desc
argument_list|,
name|GIMP_FONT_POPUP_SIZE
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
operator|&
name|ink
argument_list|,
operator|&
name|logical
argument_list|)
expr_stmt|;
operator|*
name|popup_width
operator|=
name|MAX
argument_list|(
name|ink
operator|.
name|width
argument_list|,
name|logical
operator|.
name|width
argument_list|)
operator|+
literal|6
expr_stmt|;
operator|*
name|popup_height
operator|=
name|MAX
argument_list|(
name|ink
operator|.
name|height
argument_list|,
name|logical
operator|.
name|height
argument_list|)
operator|+
literal|6
expr_stmt|;
operator|*
name|popup_width
operator|=
name|cairo_format_stride_for_width
argument_list|(
name|CAIRO_FORMAT_A8
argument_list|,
operator|*
name|popup_width
argument_list|)
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
DECL|function|gimp_font_get_new_preview (GimpViewable * viewable,GimpContext * context,gint width,gint height)
name|gimp_font_get_new_preview
parameter_list|(
name|GimpViewable
modifier|*
name|viewable
parameter_list|,
name|GimpContext
modifier|*
name|context
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
init|=
name|GIMP_FONT
argument_list|(
name|viewable
argument_list|)
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
name|gint
name|layout_width
decl_stmt|;
name|gint
name|layout_height
decl_stmt|;
name|gint
name|layout_x
decl_stmt|;
name|gint
name|layout_y
decl_stmt|;
name|TempBuf
modifier|*
name|temp_buf
decl_stmt|;
name|cairo_t
modifier|*
name|cr
decl_stmt|;
name|cairo_surface_t
modifier|*
name|surface
decl_stmt|;
name|guchar
name|white
init|=
literal|255
decl_stmt|;
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
name|font
argument_list|)
expr_stmt|;
name|DEBUGPRINT
argument_list|(
operator|(
literal|"%s: "
operator|,
name|name
operator|)
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
name|pango_layout_set_text
argument_list|(
name|layout
argument_list|,
name|gimp_font_get_sample_string
argument_list|(
name|font
operator|->
name|pango_context
argument_list|,
name|font_desc
argument_list|)
argument_list|,
operator|-
literal|1
argument_list|)
expr_stmt|;
name|pango_font_description_free
argument_list|(
name|font_desc
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
name|width
operator|=
name|cairo_format_stride_for_width
argument_list|(
name|CAIRO_FORMAT_A8
argument_list|,
name|width
argument_list|)
expr_stmt|;
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
name|white
argument_list|)
expr_stmt|;
name|surface
operator|=
name|cairo_image_surface_create_for_data
argument_list|(
name|temp_buf_get_data
argument_list|(
name|temp_buf
argument_list|)
argument_list|,
name|CAIRO_FORMAT_A8
argument_list|,
name|width
argument_list|,
name|height
argument_list|,
name|width
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
name|layout_width
operator|=
name|MAX
argument_list|(
name|ink
operator|.
name|width
argument_list|,
name|logical
operator|.
name|width
argument_list|)
expr_stmt|;
name|layout_height
operator|=
name|MAX
argument_list|(
name|ink
operator|.
name|height
argument_list|,
name|logical
operator|.
name|height
argument_list|)
expr_stmt|;
name|layout_x
operator|=
operator|(
name|width
operator|-
name|layout_width
operator|)
operator|/
literal|2
expr_stmt|;
name|layout_y
operator|=
operator|(
name|height
operator|-
name|layout_height
operator|)
operator|/
literal|2
expr_stmt|;
if|if
condition|(
name|ink
operator|.
name|x
operator|<
name|logical
operator|.
name|x
condition|)
name|layout_x
operator|+=
name|logical
operator|.
name|x
operator|-
name|ink
operator|.
name|x
expr_stmt|;
if|if
condition|(
name|ink
operator|.
name|y
operator|<
name|logical
operator|.
name|y
condition|)
name|layout_y
operator|+=
name|logical
operator|.
name|y
operator|-
name|ink
operator|.
name|y
expr_stmt|;
name|cr
operator|=
name|cairo_create
argument_list|(
name|surface
argument_list|)
expr_stmt|;
name|cairo_translate
argument_list|(
name|cr
argument_list|,
name|layout_x
argument_list|,
name|layout_y
argument_list|)
expr_stmt|;
name|cairo_set_operator
argument_list|(
name|cr
argument_list|,
name|CAIRO_OPERATOR_CLEAR
argument_list|)
expr_stmt|;
name|pango_cairo_show_layout
argument_list|(
name|cr
argument_list|,
name|layout
argument_list|)
expr_stmt|;
name|cairo_destroy
argument_list|(
name|cr
argument_list|)
expr_stmt|;
name|cairo_surface_destroy
argument_list|(
name|surface
argument_list|)
expr_stmt|;
name|g_object_unref
argument_list|(
name|layout
argument_list|)
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

begin_function
specifier|static
specifier|inline
name|gboolean
DECL|function|gimp_font_covers_string (PangoFcFont * font,const gchar * sample)
name|gimp_font_covers_string
parameter_list|(
name|PangoFcFont
modifier|*
name|font
parameter_list|,
specifier|const
name|gchar
modifier|*
name|sample
parameter_list|)
block|{
specifier|const
name|gchar
modifier|*
name|p
decl_stmt|;
for|for
control|(
name|p
operator|=
name|sample
init|;
operator|*
name|p
condition|;
name|p
operator|=
name|g_utf8_next_char
argument_list|(
name|p
argument_list|)
control|)
block|{
if|if
condition|(
operator|!
name|pango_fc_font_has_char
argument_list|(
name|font
argument_list|,
name|g_utf8_get_char
argument_list|(
name|p
argument_list|)
argument_list|)
condition|)
return|return
name|FALSE
return|;
block|}
return|return
name|TRUE
return|;
block|}
end_function

begin_comment
comment|/* Guess a suitable short sample string for the font. */
end_comment

begin_function
specifier|static
specifier|const
name|gchar
modifier|*
DECL|function|gimp_font_get_sample_string (PangoContext * context,PangoFontDescription * font_desc)
name|gimp_font_get_sample_string
parameter_list|(
name|PangoContext
modifier|*
name|context
parameter_list|,
name|PangoFontDescription
modifier|*
name|font_desc
parameter_list|)
block|{
name|PangoFont
modifier|*
name|font
decl_stmt|;
name|PangoOTInfo
modifier|*
name|ot_info
decl_stmt|;
name|FT_Face
name|face
decl_stmt|;
name|TT_OS2
modifier|*
name|os2
decl_stmt|;
name|PangoOTTableType
name|tt
decl_stmt|;
name|gint
name|i
decl_stmt|;
comment|/* This is a table of scripts and corresponding short sample strings    * to be used instead of the Latin sample string Aa. The script    * codes are as in ISO15924 (see    * http://www.unicode.org/iso15924/iso15924-codes.html), but in    * lower case. The Unicode subrange bit numbers, as used in TrueType    * so-called OS/2 tables, are from    * http://www.microsoft.com/typography/otspec/os2.htm#ur .    *    * The table is mostly ordered by Unicode order. But as there are    * fonts that support several of these scripts, the ordering is    * be modified so that the script which such a font is more likely    * to be actually designed for comes first and matches.    *    * These sample strings are mostly just guesswork as for their    * usefulness. Usually they contain what I assume is the first    * letter in the corresponding alphabet, or two first letters if the    * first one happens to look too "trivial" to be recognizable by    * itself.    *    * This table is used to determine the primary script a font has    * been designed for.    *    * Very useful link: http://www.travelphrases.info/fonts.html    */
specifier|static
specifier|const
struct|struct
DECL|struct|__anon278ce8660208
block|{
DECL|member|script
specifier|const
name|gchar
name|script
index|[
literal|4
index|]
decl_stmt|;
DECL|member|bit
name|gint
name|bit
decl_stmt|;
DECL|member|sample
specifier|const
name|gchar
modifier|*
name|sample
decl_stmt|;
block|}
name|scripts
index|[]
init|=
block|{
comment|/* Han is first because fonts that support it presumably are primarily      * designed for it.      */
block|{
literal|"hani"
block|,
comment|/* Han Ideographic */
literal|59
block|,
literal|"\346\260\270"
comment|/* U+6C38 "forever". Ed Trager says                                  * this is a "pan-stroke" often used                                  * in teaching Chinese calligraphy. It                                  * contains the eight basic Chinese                                  * stroke forms.                                  */
block|}
block|,
block|{
literal|"copt"
block|,
comment|/* Coptic */
literal|7
block|,
literal|"\316\221\316\261"
comment|/* U+0410 GREEK CAPITAL LETTER ALPHA                                    U+0430 GREEK SMALL LETTER ALPHA                                  */
block|}
block|,
block|{
literal|"grek"
block|,
comment|/* Greek */
literal|7
block|,
literal|"\316\221\316\261"
comment|/* U+0410 GREEK CAPITAL LETTER ALPHA                                    U+0430 GREEK SMALL LETTER ALPHA                                  */
block|}
block|,
block|{
literal|"cyrl"
block|,
comment|/* Cyrillic */
literal|9
block|,
literal|"\320\220\325\260"
comment|/* U+0410 CYRILLIC CAPITAL LETTER A                                    U+0430 CYRILLIC SMALL LETTER A                                  */
block|}
block|,
block|{
literal|"armn"
block|,
comment|/* Armenian */
literal|10
block|,
literal|"\324\261\325\241"
comment|/* U+0531 ARMENIAN CAPITAL LETTER AYB                                    U+0561 ARMENIAN SMALL LETTER AYB                                  */
block|}
block|,
block|{
literal|"hebr"
block|,
comment|/* Hebrew */
literal|11
block|,
literal|"\327\220"
comment|/* U+05D0 HEBREW LETTER ALEF */
block|}
block|,
block|{
literal|"arab"
block|,
comment|/* Arabic */
literal|13
block|,
literal|"\330\247\330\250"
comment|/* U+0627 ARABIC LETTER ALEF                                  * U+0628 ARABIC LETTER BEH                                  */
block|}
block|,
block|{
literal|"syrc"
block|,
comment|/* Syriac */
literal|71
block|,
literal|"\334\220\334\222"
comment|/* U+0710 SYRIAC LETTER ALAPH                                  * U+0712 SYRIAC LETTER BETH                                  */
block|}
block|,
block|{
literal|"thaa"
block|,
comment|/* Thaana */
literal|72
block|,
literal|"\336\200\336\201"
comment|/* U+0780 THAANA LETTER HAA                                  * U+0781 THAANA LETTER SHAVIYANI                                  */
block|}
block|,
comment|/* Should really use some better sample strings for the complex      * scripts. Something that shows how well the font handles the      * complex processing for each script.      */
block|{
literal|"deva"
block|,
comment|/* Devanagari */
literal|15
block|,
literal|"\340\244\205"
comment|/* U+0905 DEVANAGARI LETTER A*/
block|}
block|,
block|{
literal|"beng"
block|,
comment|/* Bengali */
literal|16
block|,
literal|"\340\246\205"
comment|/* U+0985 BENGALI LETTER A */
block|}
block|,
block|{
literal|"guru"
block|,
comment|/* Gurmukhi */
literal|17
block|,
literal|"\340\250\205"
comment|/* U+0A05 GURMUKHI LETTER A */
block|}
block|,
block|{
literal|"gujr"
block|,
comment|/* Gujarati */
literal|18
block|,
literal|"\340\252\205"
comment|/* U+0A85 GUJARATI LETTER A */
block|}
block|,
block|{
literal|"orya"
block|,
comment|/* Oriya */
literal|19
block|,
literal|"\340\254\205"
comment|/* U+0B05 ORIYA LETTER A */
block|}
block|,
block|{
literal|"taml"
block|,
comment|/* Tamil */
literal|20
block|,
literal|"\340\256\205"
comment|/* U+0B85 TAMIL LETTER A */
block|}
block|,
block|{
literal|"telu"
block|,
comment|/* Telugu */
literal|21
block|,
literal|"\340\260\205"
comment|/* U+0C05 TELUGU LETTER A */
block|}
block|,
block|{
literal|"knda"
block|,
comment|/* Kannada */
literal|22
block|,
literal|"\340\262\205"
comment|/* U+0C85 KANNADA LETTER A */
block|}
block|,
block|{
literal|"mylm"
block|,
comment|/* Malayalam */
literal|23
block|,
literal|"\340\264\205"
comment|/* U+0D05 MALAYALAM LETTER A */
block|}
block|,
block|{
literal|"sinh"
block|,
comment|/* Sinhala */
literal|73
block|,
literal|"\340\266\205"
comment|/* U+0D85 SINHALA LETTER AYANNA */
block|}
block|,
block|{
literal|"thai"
block|,
comment|/* Thai */
literal|24
block|,
literal|"\340\270\201\340\270\264"
comment|/* U+0E01 THAI CHARACTER KO KAI                                  * U+0E34 THAI CHARACTER SARA I                                  */
block|}
block|,
block|{
literal|"laoo"
block|,
comment|/* Lao */
literal|25
block|,
literal|"\340\272\201\340\272\264"
comment|/* U+0E81 LAO LETTER KO                                  * U+0EB4 LAO VOWEL SIGN I                                  */
block|}
block|,
block|{
literal|"tibt"
block|,
comment|/* Tibetan */
literal|70
block|,
literal|"\340\274\200"
comment|/* U+0F00 TIBETAN SYLLABLE OM */
block|}
block|,
block|{
literal|"mymr"
block|,
comment|/* Myanmar */
literal|74
block|,
literal|"\341\200\200"
comment|/* U+1000 MYANMAR LETTER KA */
block|}
block|,
block|{
literal|"geor"
block|,
comment|/* Georgian */
literal|26
block|,
literal|"\341\202\240\341\203\200"
comment|/* U+10A0 GEORGIAN CAPITAL LETTER AN                                   * U+10D0 GEORGIAN LETTER AN                                   */
block|}
block|,
block|{
literal|"hang"
block|,
comment|/* Hangul */
literal|28
block|,
literal|"\341\204\200\341\204\201"
comment|/* U+1100 HANGUL CHOSEONG KIYEOK                                  * U+1101 HANGUL CHOSEONG SSANGKIYEOK                                  */
block|}
block|,
block|{
literal|"ethi"
block|,
comment|/* Ethiopic */
literal|75
block|,
literal|"\341\210\200"
comment|/* U+1200 ETHIOPIC SYLLABLE HA */
block|}
block|,
block|{
literal|"cher"
block|,
comment|/* Cherokee */
literal|76
block|,
literal|"\341\216\243"
comment|/* U+13A3 CHEROKEE LETTER O */
block|}
block|,
block|{
literal|"cans"
block|,
comment|/* Unified Canadian Aboriginal Syllabics */
literal|77
block|,
literal|"\341\220\201"
comment|/* U+1401 CANADIAN SYLLABICS E */
block|}
block|,
block|{
literal|"ogam"
block|,
comment|/* Ogham */
literal|78
block|,
literal|"\341\232\201"
comment|/* U+1681 OGHAM LETTER BEITH */
block|}
block|,
block|{
literal|"runr"
block|,
comment|/* Runic */
literal|79
block|,
literal|"\341\232\240"
comment|/* U+16A0 RUNIC LETTER FEHU FEOH FE F */
block|}
block|,
block|{
literal|"tglg"
block|,
comment|/* Tagalog */
literal|84
block|,
literal|"\341\234\200"
comment|/* U+1700 TAGALOG LETTER A */
block|}
block|,
block|{
literal|"hano"
block|,
comment|/* Hanunoo */
operator|-
literal|1
block|,
literal|"\341\234\240"
comment|/* U+1720 HANUNOO LETTER A */
block|}
block|,
block|{
literal|"buhd"
block|,
comment|/* Buhid */
operator|-
literal|1
block|,
literal|"\341\235\200"
comment|/* U+1740 BUHID LETTER A */
block|}
block|,
block|{
literal|"tagb"
block|,
comment|/* Tagbanwa */
operator|-
literal|1
block|,
literal|"\341\235\240"
comment|/* U+1760 TAGBANWA LETTER A */
block|}
block|,
block|{
literal|"khmr"
block|,
comment|/* Khmer */
literal|80
block|,
literal|"\341\236\201\341\237\222\341\236\211\341\236\273\341\237\206"
comment|/* U+1781 KHMER LETTER KHA                                  * U+17D2 KHMER LETTER SIGN COENG                                  * U+1789 KHMER LETTER NYO                                  * U+17BB KHMER VOWEL SIGN U                                  * U+17C6 KHMER SIGN NIKAHIT                                  * A common word meaning "I" that contains                                  * lots of complex processing.                                  */
block|}
block|,
block|{
literal|"mong"
block|,
comment|/* Mongolian */
literal|81
block|,
literal|"\341\240\240"
comment|/* U+1820 MONGOLIAN LETTER A */
block|}
block|,
block|{
literal|"limb"
block|,
comment|/* Limbu */
operator|-
literal|1
block|,
literal|"\341\244\201"
comment|/* U+1901 LIMBU LETTER KA */
block|}
block|,
block|{
literal|"tale"
block|,
comment|/* Tai Le */
operator|-
literal|1
block|,
literal|"\341\245\220"
comment|/* U+1950 TAI LE LETTER KA */
block|}
block|,
block|{
literal|"latn"
block|,
comment|/* Latin */
literal|0
block|,
literal|"Aa"
block|}
block|}
struct|;
name|gint
name|ot_alts
index|[
literal|4
index|]
decl_stmt|;
name|gint
name|n_ot_alts
init|=
literal|0
decl_stmt|;
name|gint
name|sr_alts
index|[
literal|20
index|]
decl_stmt|;
name|gint
name|n_sr_alts
init|=
literal|0
decl_stmt|;
name|font
operator|=
name|pango_context_load_font
argument_list|(
name|context
argument_list|,
name|font_desc
argument_list|)
expr_stmt|;
name|g_return_val_if_fail
argument_list|(
name|PANGO_IS_FC_FONT
argument_list|(
name|font
argument_list|)
argument_list|,
literal|"Aa"
argument_list|)
expr_stmt|;
name|face
operator|=
name|pango_fc_font_lock_face
argument_list|(
name|PANGO_FC_FONT
argument_list|(
name|font
argument_list|)
argument_list|)
expr_stmt|;
name|ot_info
operator|=
name|pango_ot_info_get
argument_list|(
name|face
argument_list|)
expr_stmt|;
comment|/* First check what script(s), if any, the font has GSUB or GPOS    * OpenType layout tables for.    */
for|for
control|(
name|tt
operator|=
name|PANGO_OT_TABLE_GSUB
init|;
name|n_ot_alts
operator|<
name|G_N_ELEMENTS
argument_list|(
name|ot_alts
argument_list|)
operator|&&
name|tt
operator|<=
name|PANGO_OT_TABLE_GPOS
condition|;
name|tt
operator|++
control|)
block|{
name|PangoOTTag
modifier|*
name|slist
init|=
name|pango_ot_info_list_scripts
argument_list|(
name|ot_info
argument_list|,
name|tt
argument_list|)
decl_stmt|;
if|if
condition|(
name|slist
condition|)
block|{
for|for
control|(
name|i
operator|=
literal|0
init|;
name|n_ot_alts
operator|<
name|G_N_ELEMENTS
argument_list|(
name|ot_alts
argument_list|)
operator|&&
name|i
operator|<
name|G_N_ELEMENTS
argument_list|(
name|scripts
argument_list|)
condition|;
name|i
operator|++
control|)
block|{
name|gint
name|j
decl_stmt|,
name|k
decl_stmt|;
for|for
control|(
name|k
operator|=
literal|0
init|;
name|k
operator|<
name|n_ot_alts
condition|;
name|k
operator|++
control|)
if|if
condition|(
name|ot_alts
index|[
name|k
index|]
operator|==
name|i
condition|)
break|break;
if|if
condition|(
name|k
operator|==
name|n_ot_alts
condition|)
for|for
control|(
name|j
operator|=
literal|0
init|;
name|n_ot_alts
operator|<
name|G_N_ELEMENTS
argument_list|(
name|ot_alts
argument_list|)
operator|&&
name|slist
index|[
name|j
index|]
condition|;
name|j
operator|++
control|)
block|{
DECL|macro|TAG (s)
define|#
directive|define
name|TAG
parameter_list|(
name|s
parameter_list|)
value|FT_MAKE_TAG (s[0], s[1], s[2], s[3])
if|if
condition|(
name|slist
index|[
name|j
index|]
operator|==
name|TAG
argument_list|(
name|scripts
index|[
name|i
index|]
operator|.
name|script
argument_list|)
operator|&&
name|gimp_font_covers_string
argument_list|(
name|PANGO_FC_FONT
argument_list|(
name|font
argument_list|)
argument_list|,
name|scripts
index|[
name|i
index|]
operator|.
name|sample
argument_list|)
condition|)
block|{
name|ot_alts
index|[
name|n_ot_alts
operator|++
index|]
operator|=
name|i
expr_stmt|;
name|DEBUGPRINT
argument_list|(
operator|(
literal|"%.4s "
operator|,
name|scripts
index|[
name|i
index|]
operator|.
name|script
operator|)
argument_list|)
expr_stmt|;
block|}
undef|#
directive|undef
name|TAG
block|}
block|}
name|g_free
argument_list|(
name|slist
argument_list|)
expr_stmt|;
block|}
block|}
name|DEBUGPRINT
argument_list|(
operator|(
literal|"; OS/2: "
operator|)
argument_list|)
expr_stmt|;
comment|/* Next check the OS/2 table for Unicode ranges the font claims    * to cover.    */
name|os2
operator|=
name|FT_Get_Sfnt_Table
argument_list|(
name|face
argument_list|,
name|ft_sfnt_os2
argument_list|)
expr_stmt|;
if|if
condition|(
name|os2
condition|)
block|{
for|for
control|(
name|i
operator|=
literal|0
init|;
name|n_sr_alts
operator|<
name|G_N_ELEMENTS
argument_list|(
name|sr_alts
argument_list|)
operator|&&
name|i
operator|<
name|G_N_ELEMENTS
argument_list|(
name|scripts
argument_list|)
condition|;
name|i
operator|++
control|)
block|{
if|if
condition|(
name|scripts
index|[
name|i
index|]
operator|.
name|bit
operator|>=
literal|0
operator|&&
operator|(
operator|&
name|os2
operator|->
name|ulUnicodeRange1
operator|)
index|[
name|scripts
index|[
name|i
index|]
operator|.
name|bit
operator|/
literal|32
index|]
operator|&
operator|(
literal|1
operator|<<
operator|(
name|scripts
index|[
name|i
index|]
operator|.
name|bit
operator|%
literal|32
operator|)
operator|)
operator|&&
name|gimp_font_covers_string
argument_list|(
name|PANGO_FC_FONT
argument_list|(
name|font
argument_list|)
argument_list|,
name|scripts
index|[
name|i
index|]
operator|.
name|sample
argument_list|)
condition|)
block|{
name|sr_alts
index|[
name|n_sr_alts
operator|++
index|]
operator|=
name|i
expr_stmt|;
name|DEBUGPRINT
argument_list|(
operator|(
literal|"%.4s "
operator|,
name|scripts
index|[
name|i
index|]
operator|.
name|script
operator|)
argument_list|)
expr_stmt|;
block|}
block|}
block|}
name|pango_fc_font_unlock_face
argument_list|(
name|PANGO_FC_FONT
argument_list|(
name|font
argument_list|)
argument_list|)
expr_stmt|;
name|g_object_unref
argument_list|(
name|font
argument_list|)
expr_stmt|;
if|if
condition|(
name|n_ot_alts
operator|>
literal|2
condition|)
block|{
comment|/* The font has OpenType tables for several scripts. If it        * support Basic Latin as well, use Aa.        */
name|gint
name|i
decl_stmt|;
for|for
control|(
name|i
operator|=
literal|0
init|;
name|i
operator|<
name|n_sr_alts
condition|;
name|i
operator|++
control|)
if|if
condition|(
name|scripts
index|[
name|sr_alts
index|[
name|i
index|]
index|]
operator|.
name|bit
operator|==
literal|0
condition|)
block|{
name|DEBUGPRINT
argument_list|(
operator|(
literal|"=> several OT, also latin, use Aa\n"
operator|)
argument_list|)
expr_stmt|;
return|return
literal|"Aa"
return|;
block|}
block|}
if|if
condition|(
name|n_ot_alts
operator|>
literal|0
operator|&&
name|n_sr_alts
operator|>=
name|n_ot_alts
operator|+
literal|3
condition|)
block|{
comment|/* At least one script with an OpenType table, but many more        * subranges than such scripts. If it supports Basic Latin,        * use Aa, else the highest priority subrange.        */
name|gint
name|i
decl_stmt|;
for|for
control|(
name|i
operator|=
literal|0
init|;
name|i
operator|<
name|n_sr_alts
condition|;
name|i
operator|++
control|)
if|if
condition|(
name|scripts
index|[
name|sr_alts
index|[
name|i
index|]
index|]
operator|.
name|bit
operator|==
literal|0
condition|)
block|{
name|DEBUGPRINT
argument_list|(
operator|(
literal|"=> several SR, also latin, use Aa\n"
operator|)
argument_list|)
expr_stmt|;
return|return
literal|"Aa"
return|;
block|}
name|DEBUGPRINT
argument_list|(
operator|(
literal|"=> several SR, use %.4s\n"
operator|,
name|scripts
index|[
name|sr_alts
index|[
literal|0
index|]
index|]
operator|.
name|script
operator|)
argument_list|)
expr_stmt|;
return|return
name|scripts
index|[
name|sr_alts
index|[
literal|0
index|]
index|]
operator|.
name|sample
return|;
block|}
if|if
condition|(
name|n_ot_alts
operator|>
literal|0
condition|)
block|{
comment|/* OpenType tables for at least one script, use the        * highest priority one        */
name|DEBUGPRINT
argument_list|(
operator|(
literal|"=> at least one OT, use %.4s\n"
operator|,
name|scripts
index|[
name|sr_alts
index|[
literal|0
index|]
index|]
operator|.
name|script
operator|)
argument_list|)
expr_stmt|;
return|return
name|scripts
index|[
name|ot_alts
index|[
literal|0
index|]
index|]
operator|.
name|sample
return|;
block|}
if|if
condition|(
name|n_sr_alts
operator|>
literal|0
condition|)
block|{
comment|/* Use the highest priority subrange.  This means that a        * font that supports Greek, Cyrillic and Latin (quite        * common), will get the Greek sample string. That is        * capital and lowercase alpha, which looks like capital A        * and lowercase alpha, so it's actually quite nice, and        * doesn't give a too strong impression that the font would        * be for Greek only.        */
name|DEBUGPRINT
argument_list|(
operator|(
literal|"=> at least one SR, use %.4s\n"
operator|,
name|scripts
index|[
name|sr_alts
index|[
literal|0
index|]
index|]
operator|.
name|script
operator|)
argument_list|)
expr_stmt|;
return|return
name|scripts
index|[
name|sr_alts
index|[
literal|0
index|]
index|]
operator|.
name|sample
return|;
block|}
comment|/* Final fallback */
name|DEBUGPRINT
argument_list|(
operator|(
literal|"=> fallback, use Aa\n"
operator|)
argument_list|)
expr_stmt|;
return|return
literal|"Aa"
return|;
block|}
end_function

end_unit

