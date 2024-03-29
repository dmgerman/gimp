begin_unit|revision:0.9.5;language:C;cregit-version:0.0.1
begin_comment
comment|/* GIMP - The GNU Image Manipulation Program  * Copyright (C) 1995 Spencer Kimball and Peter Mattis  *  * GimpText  * Copyright (C) 2002-2003  Sven Neumann<sven@gimp.org>  *  * This program is free software: you can redistribute it and/or modify  * it under the terms of the GNU General Public License as published by  * the Free Software Foundation; either version 3 of the License, or  * (at your option) any later version.  *  * This program is distributed in the hope that it will be useful,  * but WITHOUT ANY WARRANTY; without even the implied warranty of  * MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the  * GNU General Public License for more details.  *  * You should have received a copy of the GNU General Public License  * along with this program.  If not, see<https://www.gnu.org/licenses/>.  */
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
file|<cairo.h>
end_include

begin_include
include|#
directive|include
file|<gegl.h>
end_include

begin_include
include|#
directive|include
file|<gdk-pixbuf/gdk-pixbuf.h>
end_include

begin_include
include|#
directive|include
file|<pango/pango.h>
end_include

begin_include
include|#
directive|include
file|"libgimpbase/gimpbase.h"
end_include

begin_include
include|#
directive|include
file|"libgimpmath/gimpmath.h"
end_include

begin_include
include|#
directive|include
file|"libgimpcolor/gimpcolor.h"
end_include

begin_include
include|#
directive|include
file|"libgimpconfig/gimpconfig.h"
end_include

begin_include
include|#
directive|include
file|"text-types.h"
end_include

begin_include
include|#
directive|include
file|"core/gimp-memsize.h"
end_include

begin_include
include|#
directive|include
file|"core/gimp-utils.h"
end_include

begin_include
include|#
directive|include
file|"core/gimpmarshal.h"
end_include

begin_include
include|#
directive|include
file|"core/gimpstrokeoptions.h"
end_include

begin_include
include|#
directive|include
file|"gimptext.h"
end_include

begin_enum
enum|enum
DECL|enum|__anon2c107c4e0103
block|{
DECL|enumerator|PROP_0
name|PROP_0
block|,
DECL|enumerator|PROP_TEXT
name|PROP_TEXT
block|,
DECL|enumerator|PROP_MARKUP
name|PROP_MARKUP
block|,
DECL|enumerator|PROP_FONT
name|PROP_FONT
block|,
DECL|enumerator|PROP_FONT_SIZE
name|PROP_FONT_SIZE
block|,
DECL|enumerator|PROP_UNIT
name|PROP_UNIT
block|,
DECL|enumerator|PROP_ANTIALIAS
name|PROP_ANTIALIAS
block|,
DECL|enumerator|PROP_HINT_STYLE
name|PROP_HINT_STYLE
block|,
DECL|enumerator|PROP_KERNING
name|PROP_KERNING
block|,
DECL|enumerator|PROP_LANGUAGE
name|PROP_LANGUAGE
block|,
DECL|enumerator|PROP_BASE_DIR
name|PROP_BASE_DIR
block|,
DECL|enumerator|PROP_COLOR
name|PROP_COLOR
block|,
DECL|enumerator|PROP_OUTLINE
name|PROP_OUTLINE
block|,
DECL|enumerator|PROP_JUSTIFICATION
name|PROP_JUSTIFICATION
block|,
DECL|enumerator|PROP_INDENTATION
name|PROP_INDENTATION
block|,
DECL|enumerator|PROP_LINE_SPACING
name|PROP_LINE_SPACING
block|,
DECL|enumerator|PROP_LETTER_SPACING
name|PROP_LETTER_SPACING
block|,
DECL|enumerator|PROP_BOX_MODE
name|PROP_BOX_MODE
block|,
DECL|enumerator|PROP_BOX_WIDTH
name|PROP_BOX_WIDTH
block|,
DECL|enumerator|PROP_BOX_HEIGHT
name|PROP_BOX_HEIGHT
block|,
DECL|enumerator|PROP_BOX_UNIT
name|PROP_BOX_UNIT
block|,
DECL|enumerator|PROP_TRANSFORMATION
name|PROP_TRANSFORMATION
block|,
DECL|enumerator|PROP_OFFSET_X
name|PROP_OFFSET_X
block|,
DECL|enumerator|PROP_OFFSET_Y
name|PROP_OFFSET_Y
block|,
DECL|enumerator|PROP_BORDER
name|PROP_BORDER
block|,
comment|/* for backward compatibility */
DECL|enumerator|PROP_HINTING
name|PROP_HINTING
block|}
enum|;
end_enum

begin_enum
enum|enum
DECL|enum|__anon2c107c4e0203
block|{
DECL|enumerator|CHANGED
name|CHANGED
block|,
DECL|enumerator|LAST_SIGNAL
name|LAST_SIGNAL
block|}
enum|;
end_enum

begin_function_decl
specifier|static
name|void
name|gimp_text_finalize
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
name|gimp_text_get_property
parameter_list|(
name|GObject
modifier|*
name|object
parameter_list|,
name|guint
name|property_id
parameter_list|,
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
name|gimp_text_set_property
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
name|gimp_text_dispatch_properties_changed
parameter_list|(
name|GObject
modifier|*
name|object
parameter_list|,
name|guint
name|n_pspecs
parameter_list|,
name|GParamSpec
modifier|*
modifier|*
name|pspecs
parameter_list|)
function_decl|;
end_function_decl

begin_function_decl
specifier|static
name|gint64
name|gimp_text_get_memsize
parameter_list|(
name|GimpObject
modifier|*
name|object
parameter_list|,
name|gint64
modifier|*
name|gui_size
parameter_list|)
function_decl|;
end_function_decl

begin_macro
name|G_DEFINE_TYPE_WITH_CODE
argument_list|(
argument|GimpText
argument_list|,
argument|gimp_text
argument_list|,
argument|GIMP_TYPE_OBJECT
argument_list|,
argument|G_IMPLEMENT_INTERFACE (GIMP_TYPE_CONFIG, NULL)
argument_list|)
end_macro

begin_define
DECL|macro|parent_class
define|#
directive|define
name|parent_class
value|gimp_text_parent_class
end_define

begin_decl_stmt
specifier|static
name|guint
name|text_signals
index|[
name|LAST_SIGNAL
index|]
init|=
block|{
literal|0
block|}
decl_stmt|;
end_decl_stmt

begin_function
specifier|static
name|void
DECL|function|gimp_text_class_init (GimpTextClass * klass)
name|gimp_text_class_init
parameter_list|(
name|GimpTextClass
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
name|GimpObjectClass
modifier|*
name|gimp_object_class
init|=
name|GIMP_OBJECT_CLASS
argument_list|(
name|klass
argument_list|)
decl_stmt|;
name|GimpRGB
name|black
decl_stmt|;
name|GimpMatrix2
name|identity
decl_stmt|;
name|gchar
modifier|*
name|language
decl_stmt|;
name|text_signals
index|[
name|CHANGED
index|]
operator|=
name|g_signal_new
argument_list|(
literal|"changed"
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
name|GimpTextClass
argument_list|,
name|changed
argument_list|)
argument_list|,
name|NULL
argument_list|,
name|NULL
argument_list|,
name|gimp_marshal_VOID__VOID
argument_list|,
name|G_TYPE_NONE
argument_list|,
literal|0
argument_list|)
expr_stmt|;
name|object_class
operator|->
name|finalize
operator|=
name|gimp_text_finalize
expr_stmt|;
name|object_class
operator|->
name|get_property
operator|=
name|gimp_text_get_property
expr_stmt|;
name|object_class
operator|->
name|set_property
operator|=
name|gimp_text_set_property
expr_stmt|;
name|object_class
operator|->
name|dispatch_properties_changed
operator|=
name|gimp_text_dispatch_properties_changed
expr_stmt|;
name|gimp_object_class
operator|->
name|get_memsize
operator|=
name|gimp_text_get_memsize
expr_stmt|;
name|gimp_rgba_set
argument_list|(
operator|&
name|black
argument_list|,
literal|0.0
argument_list|,
literal|0.0
argument_list|,
literal|0.0
argument_list|,
name|GIMP_OPACITY_OPAQUE
argument_list|)
expr_stmt|;
name|gimp_matrix2_identity
argument_list|(
operator|&
name|identity
argument_list|)
expr_stmt|;
name|GIMP_CONFIG_PROP_STRING
argument_list|(
name|object_class
argument_list|,
name|PROP_TEXT
argument_list|,
literal|"text"
argument_list|,
name|NULL
argument_list|,
name|NULL
argument_list|,
name|NULL
argument_list|,
name|GIMP_PARAM_STATIC_STRINGS
argument_list|)
expr_stmt|;
name|GIMP_CONFIG_PROP_STRING
argument_list|(
name|object_class
argument_list|,
name|PROP_MARKUP
argument_list|,
literal|"markup"
argument_list|,
name|NULL
argument_list|,
name|NULL
argument_list|,
name|NULL
argument_list|,
name|GIMP_PARAM_STATIC_STRINGS
argument_list|)
expr_stmt|;
name|GIMP_CONFIG_PROP_STRING
argument_list|(
name|object_class
argument_list|,
name|PROP_FONT
argument_list|,
literal|"font"
argument_list|,
name|NULL
argument_list|,
name|NULL
argument_list|,
literal|"Sans-serif"
argument_list|,
name|GIMP_PARAM_STATIC_STRINGS
argument_list|)
expr_stmt|;
name|GIMP_CONFIG_PROP_DOUBLE
argument_list|(
name|object_class
argument_list|,
name|PROP_FONT_SIZE
argument_list|,
literal|"font-size"
argument_list|,
name|NULL
argument_list|,
name|NULL
argument_list|,
literal|0.0
argument_list|,
literal|8192.0
argument_list|,
literal|24.0
argument_list|,
name|GIMP_PARAM_STATIC_STRINGS
argument_list|)
expr_stmt|;
comment|/*  We use the name "font-size-unit" for backward compatibility.    *  The unit is also used for other sizes in the text object.    */
name|GIMP_CONFIG_PROP_UNIT
argument_list|(
name|object_class
argument_list|,
name|PROP_UNIT
argument_list|,
literal|"font-size-unit"
argument_list|,
name|NULL
argument_list|,
name|NULL
argument_list|,
name|TRUE
argument_list|,
name|FALSE
argument_list|,
name|GIMP_UNIT_PIXEL
argument_list|,
name|GIMP_PARAM_STATIC_STRINGS
argument_list|)
expr_stmt|;
name|GIMP_CONFIG_PROP_BOOLEAN
argument_list|(
name|object_class
argument_list|,
name|PROP_ANTIALIAS
argument_list|,
literal|"antialias"
argument_list|,
name|NULL
argument_list|,
name|NULL
argument_list|,
name|TRUE
argument_list|,
name|GIMP_PARAM_STATIC_STRINGS
argument_list|)
expr_stmt|;
name|GIMP_CONFIG_PROP_ENUM
argument_list|(
name|object_class
argument_list|,
name|PROP_HINT_STYLE
argument_list|,
literal|"hint-style"
argument_list|,
name|NULL
argument_list|,
name|NULL
argument_list|,
name|GIMP_TYPE_TEXT_HINT_STYLE
argument_list|,
name|GIMP_TEXT_HINT_STYLE_MEDIUM
argument_list|,
name|GIMP_PARAM_STATIC_STRINGS
operator||
name|GIMP_CONFIG_PARAM_DEFAULTS
argument_list|)
expr_stmt|;
name|GIMP_CONFIG_PROP_BOOLEAN
argument_list|(
name|object_class
argument_list|,
name|PROP_KERNING
argument_list|,
literal|"kerning"
argument_list|,
name|NULL
argument_list|,
name|NULL
argument_list|,
name|FALSE
argument_list|,
name|GIMP_PARAM_STATIC_STRINGS
operator||
name|GIMP_CONFIG_PARAM_DEFAULTS
argument_list|)
expr_stmt|;
name|language
operator|=
name|gimp_get_default_language
argument_list|(
name|NULL
argument_list|)
expr_stmt|;
name|GIMP_CONFIG_PROP_STRING
argument_list|(
name|object_class
argument_list|,
name|PROP_LANGUAGE
argument_list|,
literal|"language"
argument_list|,
name|NULL
argument_list|,
name|NULL
argument_list|,
name|language
argument_list|,
name|GIMP_PARAM_STATIC_STRINGS
argument_list|)
expr_stmt|;
name|g_free
argument_list|(
name|language
argument_list|)
expr_stmt|;
name|GIMP_CONFIG_PROP_ENUM
argument_list|(
name|object_class
argument_list|,
name|PROP_BASE_DIR
argument_list|,
literal|"base-direction"
argument_list|,
name|NULL
argument_list|,
name|NULL
argument_list|,
name|GIMP_TYPE_TEXT_DIRECTION
argument_list|,
name|GIMP_TEXT_DIRECTION_LTR
argument_list|,
name|GIMP_PARAM_STATIC_STRINGS
argument_list|)
expr_stmt|;
name|GIMP_CONFIG_PROP_RGB
argument_list|(
name|object_class
argument_list|,
name|PROP_COLOR
argument_list|,
literal|"color"
argument_list|,
name|NULL
argument_list|,
name|NULL
argument_list|,
name|FALSE
argument_list|,
operator|&
name|black
argument_list|,
name|GIMP_PARAM_STATIC_STRINGS
argument_list|)
expr_stmt|;
name|GIMP_CONFIG_PROP_ENUM
argument_list|(
name|object_class
argument_list|,
name|PROP_OUTLINE
argument_list|,
literal|"outline"
argument_list|,
name|NULL
argument_list|,
name|NULL
argument_list|,
name|GIMP_TYPE_TEXT_OUTLINE
argument_list|,
name|GIMP_TEXT_OUTLINE_NONE
argument_list|,
name|GIMP_PARAM_STATIC_STRINGS
operator||
name|GIMP_CONFIG_PARAM_DEFAULTS
argument_list|)
expr_stmt|;
name|GIMP_CONFIG_PROP_ENUM
argument_list|(
name|object_class
argument_list|,
name|PROP_JUSTIFICATION
argument_list|,
literal|"justify"
argument_list|,
name|NULL
argument_list|,
name|NULL
argument_list|,
name|GIMP_TYPE_TEXT_JUSTIFICATION
argument_list|,
name|GIMP_TEXT_JUSTIFY_LEFT
argument_list|,
name|GIMP_PARAM_STATIC_STRINGS
argument_list|)
expr_stmt|;
name|GIMP_CONFIG_PROP_DOUBLE
argument_list|(
name|object_class
argument_list|,
name|PROP_INDENTATION
argument_list|,
literal|"indent"
argument_list|,
name|NULL
argument_list|,
name|NULL
argument_list|,
operator|-
literal|8192.0
argument_list|,
literal|8192.0
argument_list|,
literal|0.0
argument_list|,
name|GIMP_PARAM_STATIC_STRINGS
operator||
name|GIMP_CONFIG_PARAM_DEFAULTS
argument_list|)
expr_stmt|;
name|GIMP_CONFIG_PROP_DOUBLE
argument_list|(
name|object_class
argument_list|,
name|PROP_LINE_SPACING
argument_list|,
literal|"line-spacing"
argument_list|,
name|NULL
argument_list|,
name|NULL
argument_list|,
operator|-
literal|8192.0
argument_list|,
literal|8192.0
argument_list|,
literal|0.0
argument_list|,
name|GIMP_PARAM_STATIC_STRINGS
operator||
name|GIMP_CONFIG_PARAM_DEFAULTS
argument_list|)
expr_stmt|;
name|GIMP_CONFIG_PROP_DOUBLE
argument_list|(
name|object_class
argument_list|,
name|PROP_LETTER_SPACING
argument_list|,
literal|"letter-spacing"
argument_list|,
name|NULL
argument_list|,
name|NULL
argument_list|,
operator|-
literal|8192.0
argument_list|,
literal|8192.0
argument_list|,
literal|0.0
argument_list|,
name|GIMP_PARAM_STATIC_STRINGS
operator||
name|GIMP_CONFIG_PARAM_DEFAULTS
argument_list|)
expr_stmt|;
name|GIMP_CONFIG_PROP_ENUM
argument_list|(
name|object_class
argument_list|,
name|PROP_BOX_MODE
argument_list|,
literal|"box-mode"
argument_list|,
name|NULL
argument_list|,
name|NULL
argument_list|,
name|GIMP_TYPE_TEXT_BOX_MODE
argument_list|,
name|GIMP_TEXT_BOX_DYNAMIC
argument_list|,
name|GIMP_PARAM_STATIC_STRINGS
argument_list|)
expr_stmt|;
name|GIMP_CONFIG_PROP_DOUBLE
argument_list|(
name|object_class
argument_list|,
name|PROP_BOX_WIDTH
argument_list|,
literal|"box-width"
argument_list|,
name|NULL
argument_list|,
name|NULL
argument_list|,
literal|0.0
argument_list|,
name|GIMP_MAX_IMAGE_SIZE
argument_list|,
literal|0.0
argument_list|,
name|GIMP_PARAM_STATIC_STRINGS
operator||
name|GIMP_CONFIG_PARAM_DEFAULTS
argument_list|)
expr_stmt|;
name|GIMP_CONFIG_PROP_DOUBLE
argument_list|(
name|object_class
argument_list|,
name|PROP_BOX_HEIGHT
argument_list|,
literal|"box-height"
argument_list|,
name|NULL
argument_list|,
name|NULL
argument_list|,
literal|0.0
argument_list|,
name|GIMP_MAX_IMAGE_SIZE
argument_list|,
literal|0.0
argument_list|,
name|GIMP_PARAM_STATIC_STRINGS
operator||
name|GIMP_CONFIG_PARAM_DEFAULTS
argument_list|)
expr_stmt|;
name|GIMP_CONFIG_PROP_UNIT
argument_list|(
name|object_class
argument_list|,
name|PROP_BOX_UNIT
argument_list|,
literal|"box-unit"
argument_list|,
name|NULL
argument_list|,
name|NULL
argument_list|,
name|TRUE
argument_list|,
name|FALSE
argument_list|,
name|GIMP_UNIT_PIXEL
argument_list|,
name|GIMP_PARAM_STATIC_STRINGS
argument_list|)
expr_stmt|;
name|GIMP_CONFIG_PROP_MATRIX2
argument_list|(
name|object_class
argument_list|,
name|PROP_TRANSFORMATION
argument_list|,
literal|"transformation"
argument_list|,
name|NULL
argument_list|,
name|NULL
argument_list|,
operator|&
name|identity
argument_list|,
name|GIMP_PARAM_STATIC_STRINGS
operator||
name|GIMP_CONFIG_PARAM_DEFAULTS
argument_list|)
expr_stmt|;
name|GIMP_CONFIG_PROP_DOUBLE
argument_list|(
name|object_class
argument_list|,
name|PROP_OFFSET_X
argument_list|,
literal|"offset-x"
argument_list|,
name|NULL
argument_list|,
name|NULL
argument_list|,
operator|-
name|G_MAXDOUBLE
argument_list|,
name|G_MAXDOUBLE
argument_list|,
literal|0.0
argument_list|,
name|GIMP_PARAM_STATIC_STRINGS
operator||
name|GIMP_CONFIG_PARAM_DEFAULTS
argument_list|)
expr_stmt|;
name|GIMP_CONFIG_PROP_DOUBLE
argument_list|(
name|object_class
argument_list|,
name|PROP_OFFSET_Y
argument_list|,
literal|"offset-y"
argument_list|,
name|NULL
argument_list|,
name|NULL
argument_list|,
operator|-
name|G_MAXDOUBLE
argument_list|,
name|G_MAXDOUBLE
argument_list|,
literal|0.0
argument_list|,
name|GIMP_PARAM_STATIC_STRINGS
operator||
name|GIMP_CONFIG_PARAM_DEFAULTS
argument_list|)
expr_stmt|;
comment|/*  border does only exist to implement the old text API  */
name|g_object_class_install_property
argument_list|(
name|object_class
argument_list|,
name|PROP_BORDER
argument_list|,
name|g_param_spec_int
argument_list|(
literal|"border"
argument_list|,
name|NULL
argument_list|,
name|NULL
argument_list|,
literal|0
argument_list|,
name|GIMP_MAX_IMAGE_SIZE
argument_list|,
literal|0
argument_list|,
name|G_PARAM_CONSTRUCT
operator||
name|GIMP_PARAM_WRITABLE
argument_list|)
argument_list|)
expr_stmt|;
comment|/*  the old hinting options have been replaced by 'hint-style'  */
name|GIMP_CONFIG_PROP_BOOLEAN
argument_list|(
name|object_class
argument_list|,
name|PROP_HINTING
argument_list|,
literal|"hinting"
argument_list|,
name|NULL
argument_list|,
name|NULL
argument_list|,
name|TRUE
argument_list|,
name|GIMP_PARAM_STATIC_STRINGS
argument_list|)
expr_stmt|;
block|}
end_function

begin_function
specifier|static
name|void
DECL|function|gimp_text_init (GimpText * text)
name|gimp_text_init
parameter_list|(
name|GimpText
modifier|*
name|text
parameter_list|)
block|{ }
end_function

begin_function
specifier|static
name|void
DECL|function|gimp_text_finalize (GObject * object)
name|gimp_text_finalize
parameter_list|(
name|GObject
modifier|*
name|object
parameter_list|)
block|{
name|GimpText
modifier|*
name|text
init|=
name|GIMP_TEXT
argument_list|(
name|object
argument_list|)
decl_stmt|;
name|g_clear_pointer
argument_list|(
operator|&
name|text
operator|->
name|text
argument_list|,
name|g_free
argument_list|)
expr_stmt|;
name|g_clear_pointer
argument_list|(
operator|&
name|text
operator|->
name|markup
argument_list|,
name|g_free
argument_list|)
expr_stmt|;
name|g_clear_pointer
argument_list|(
operator|&
name|text
operator|->
name|font
argument_list|,
name|g_free
argument_list|)
expr_stmt|;
name|g_clear_pointer
argument_list|(
operator|&
name|text
operator|->
name|language
argument_list|,
name|g_free
argument_list|)
expr_stmt|;
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
DECL|function|gimp_text_get_property (GObject * object,guint property_id,GValue * value,GParamSpec * pspec)
name|gimp_text_get_property
parameter_list|(
name|GObject
modifier|*
name|object
parameter_list|,
name|guint
name|property_id
parameter_list|,
name|GValue
modifier|*
name|value
parameter_list|,
name|GParamSpec
modifier|*
name|pspec
parameter_list|)
block|{
name|GimpText
modifier|*
name|text
init|=
name|GIMP_TEXT
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
name|PROP_TEXT
case|:
name|g_value_set_string
argument_list|(
name|value
argument_list|,
name|text
operator|->
name|text
argument_list|)
expr_stmt|;
break|break;
case|case
name|PROP_MARKUP
case|:
name|g_value_set_string
argument_list|(
name|value
argument_list|,
name|text
operator|->
name|markup
argument_list|)
expr_stmt|;
break|break;
case|case
name|PROP_FONT
case|:
name|g_value_set_string
argument_list|(
name|value
argument_list|,
name|text
operator|->
name|font
argument_list|)
expr_stmt|;
break|break;
case|case
name|PROP_FONT_SIZE
case|:
name|g_value_set_double
argument_list|(
name|value
argument_list|,
name|text
operator|->
name|font_size
argument_list|)
expr_stmt|;
break|break;
case|case
name|PROP_UNIT
case|:
name|g_value_set_int
argument_list|(
name|value
argument_list|,
name|text
operator|->
name|unit
argument_list|)
expr_stmt|;
break|break;
case|case
name|PROP_ANTIALIAS
case|:
name|g_value_set_boolean
argument_list|(
name|value
argument_list|,
name|text
operator|->
name|antialias
argument_list|)
expr_stmt|;
break|break;
case|case
name|PROP_HINT_STYLE
case|:
name|g_value_set_enum
argument_list|(
name|value
argument_list|,
name|text
operator|->
name|hint_style
argument_list|)
expr_stmt|;
break|break;
case|case
name|PROP_KERNING
case|:
name|g_value_set_boolean
argument_list|(
name|value
argument_list|,
name|text
operator|->
name|kerning
argument_list|)
expr_stmt|;
break|break;
case|case
name|PROP_BASE_DIR
case|:
name|g_value_set_enum
argument_list|(
name|value
argument_list|,
name|text
operator|->
name|base_dir
argument_list|)
expr_stmt|;
break|break;
case|case
name|PROP_LANGUAGE
case|:
name|g_value_set_string
argument_list|(
name|value
argument_list|,
name|text
operator|->
name|language
argument_list|)
expr_stmt|;
break|break;
case|case
name|PROP_COLOR
case|:
name|g_value_set_boxed
argument_list|(
name|value
argument_list|,
operator|&
name|text
operator|->
name|color
argument_list|)
expr_stmt|;
break|break;
case|case
name|PROP_OUTLINE
case|:
name|g_value_set_enum
argument_list|(
name|value
argument_list|,
name|text
operator|->
name|outline
argument_list|)
expr_stmt|;
break|break;
case|case
name|PROP_JUSTIFICATION
case|:
name|g_value_set_enum
argument_list|(
name|value
argument_list|,
name|text
operator|->
name|justify
argument_list|)
expr_stmt|;
break|break;
case|case
name|PROP_INDENTATION
case|:
name|g_value_set_double
argument_list|(
name|value
argument_list|,
name|text
operator|->
name|indent
argument_list|)
expr_stmt|;
break|break;
case|case
name|PROP_LINE_SPACING
case|:
name|g_value_set_double
argument_list|(
name|value
argument_list|,
name|text
operator|->
name|line_spacing
argument_list|)
expr_stmt|;
break|break;
case|case
name|PROP_LETTER_SPACING
case|:
name|g_value_set_double
argument_list|(
name|value
argument_list|,
name|text
operator|->
name|letter_spacing
argument_list|)
expr_stmt|;
break|break;
case|case
name|PROP_BOX_MODE
case|:
name|g_value_set_enum
argument_list|(
name|value
argument_list|,
name|text
operator|->
name|box_mode
argument_list|)
expr_stmt|;
break|break;
case|case
name|PROP_BOX_WIDTH
case|:
name|g_value_set_double
argument_list|(
name|value
argument_list|,
name|text
operator|->
name|box_width
argument_list|)
expr_stmt|;
break|break;
case|case
name|PROP_BOX_HEIGHT
case|:
name|g_value_set_double
argument_list|(
name|value
argument_list|,
name|text
operator|->
name|box_height
argument_list|)
expr_stmt|;
break|break;
case|case
name|PROP_BOX_UNIT
case|:
name|g_value_set_int
argument_list|(
name|value
argument_list|,
name|text
operator|->
name|box_unit
argument_list|)
expr_stmt|;
break|break;
case|case
name|PROP_TRANSFORMATION
case|:
name|g_value_set_boxed
argument_list|(
name|value
argument_list|,
operator|&
name|text
operator|->
name|transformation
argument_list|)
expr_stmt|;
break|break;
case|case
name|PROP_OFFSET_X
case|:
name|g_value_set_double
argument_list|(
name|value
argument_list|,
name|text
operator|->
name|offset_x
argument_list|)
expr_stmt|;
break|break;
case|case
name|PROP_OFFSET_Y
case|:
name|g_value_set_double
argument_list|(
name|value
argument_list|,
name|text
operator|->
name|offset_y
argument_list|)
expr_stmt|;
break|break;
case|case
name|PROP_HINTING
case|:
name|g_value_set_boolean
argument_list|(
name|value
argument_list|,
name|text
operator|->
name|hint_style
operator|!=
name|GIMP_TEXT_HINT_STYLE_NONE
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
DECL|function|gimp_text_set_property (GObject * object,guint property_id,const GValue * value,GParamSpec * pspec)
name|gimp_text_set_property
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
name|GimpText
modifier|*
name|text
init|=
name|GIMP_TEXT
argument_list|(
name|object
argument_list|)
decl_stmt|;
name|GimpRGB
modifier|*
name|color
decl_stmt|;
name|GimpMatrix2
modifier|*
name|matrix
decl_stmt|;
switch|switch
condition|(
name|property_id
condition|)
block|{
case|case
name|PROP_TEXT
case|:
name|g_free
argument_list|(
name|text
operator|->
name|text
argument_list|)
expr_stmt|;
name|text
operator|->
name|text
operator|=
name|g_value_dup_string
argument_list|(
name|value
argument_list|)
expr_stmt|;
if|if
condition|(
name|text
operator|->
name|text
operator|&&
name|text
operator|->
name|markup
condition|)
block|{
name|g_clear_pointer
argument_list|(
operator|&
name|text
operator|->
name|markup
argument_list|,
name|g_free
argument_list|)
expr_stmt|;
name|g_object_notify
argument_list|(
name|object
argument_list|,
literal|"markup"
argument_list|)
expr_stmt|;
block|}
break|break;
case|case
name|PROP_MARKUP
case|:
name|g_free
argument_list|(
name|text
operator|->
name|markup
argument_list|)
expr_stmt|;
name|text
operator|->
name|markup
operator|=
name|g_value_dup_string
argument_list|(
name|value
argument_list|)
expr_stmt|;
if|if
condition|(
name|text
operator|->
name|markup
operator|&&
name|text
operator|->
name|text
condition|)
block|{
name|g_clear_pointer
argument_list|(
operator|&
name|text
operator|->
name|text
argument_list|,
name|g_free
argument_list|)
expr_stmt|;
name|g_object_notify
argument_list|(
name|object
argument_list|,
literal|"text"
argument_list|)
expr_stmt|;
block|}
break|break;
case|case
name|PROP_FONT
case|:
block|{
specifier|const
name|gchar
modifier|*
name|font
init|=
name|g_value_get_string
argument_list|(
name|value
argument_list|)
decl_stmt|;
name|g_free
argument_list|(
name|text
operator|->
name|font
argument_list|)
expr_stmt|;
if|if
condition|(
name|font
condition|)
block|{
name|gsize
name|len
init|=
name|strlen
argument_list|(
name|font
argument_list|)
decl_stmt|;
if|if
condition|(
name|g_str_has_suffix
argument_list|(
name|font
argument_list|,
literal|" Not-Rotated"
argument_list|)
condition|)
name|len
operator|-=
name|strlen
argument_list|(
literal|" Not-Rotated"
argument_list|)
expr_stmt|;
name|text
operator|->
name|font
operator|=
name|g_strndup
argument_list|(
name|font
argument_list|,
name|len
argument_list|)
expr_stmt|;
block|}
else|else
block|{
name|text
operator|->
name|font
operator|=
name|NULL
expr_stmt|;
block|}
block|}
break|break;
case|case
name|PROP_FONT_SIZE
case|:
name|text
operator|->
name|font_size
operator|=
name|g_value_get_double
argument_list|(
name|value
argument_list|)
expr_stmt|;
break|break;
case|case
name|PROP_UNIT
case|:
name|text
operator|->
name|unit
operator|=
name|g_value_get_int
argument_list|(
name|value
argument_list|)
expr_stmt|;
break|break;
case|case
name|PROP_ANTIALIAS
case|:
name|text
operator|->
name|antialias
operator|=
name|g_value_get_boolean
argument_list|(
name|value
argument_list|)
expr_stmt|;
break|break;
case|case
name|PROP_HINT_STYLE
case|:
name|text
operator|->
name|hint_style
operator|=
name|g_value_get_enum
argument_list|(
name|value
argument_list|)
expr_stmt|;
break|break;
case|case
name|PROP_KERNING
case|:
name|text
operator|->
name|kerning
operator|=
name|g_value_get_boolean
argument_list|(
name|value
argument_list|)
expr_stmt|;
break|break;
case|case
name|PROP_LANGUAGE
case|:
name|g_free
argument_list|(
name|text
operator|->
name|language
argument_list|)
expr_stmt|;
name|text
operator|->
name|language
operator|=
name|g_value_dup_string
argument_list|(
name|value
argument_list|)
expr_stmt|;
break|break;
case|case
name|PROP_BASE_DIR
case|:
name|text
operator|->
name|base_dir
operator|=
name|g_value_get_enum
argument_list|(
name|value
argument_list|)
expr_stmt|;
break|break;
case|case
name|PROP_COLOR
case|:
name|color
operator|=
name|g_value_get_boxed
argument_list|(
name|value
argument_list|)
expr_stmt|;
name|text
operator|->
name|color
operator|=
operator|*
name|color
expr_stmt|;
break|break;
case|case
name|PROP_OUTLINE
case|:
name|text
operator|->
name|outline
operator|=
name|g_value_get_enum
argument_list|(
name|value
argument_list|)
expr_stmt|;
break|break;
case|case
name|PROP_JUSTIFICATION
case|:
name|text
operator|->
name|justify
operator|=
name|g_value_get_enum
argument_list|(
name|value
argument_list|)
expr_stmt|;
break|break;
case|case
name|PROP_INDENTATION
case|:
name|text
operator|->
name|indent
operator|=
name|g_value_get_double
argument_list|(
name|value
argument_list|)
expr_stmt|;
break|break;
case|case
name|PROP_LINE_SPACING
case|:
name|text
operator|->
name|line_spacing
operator|=
name|g_value_get_double
argument_list|(
name|value
argument_list|)
expr_stmt|;
break|break;
case|case
name|PROP_LETTER_SPACING
case|:
name|text
operator|->
name|letter_spacing
operator|=
name|g_value_get_double
argument_list|(
name|value
argument_list|)
expr_stmt|;
break|break;
case|case
name|PROP_BOX_MODE
case|:
name|text
operator|->
name|box_mode
operator|=
name|g_value_get_enum
argument_list|(
name|value
argument_list|)
expr_stmt|;
break|break;
case|case
name|PROP_BOX_WIDTH
case|:
name|text
operator|->
name|box_width
operator|=
name|g_value_get_double
argument_list|(
name|value
argument_list|)
expr_stmt|;
break|break;
case|case
name|PROP_BOX_HEIGHT
case|:
name|text
operator|->
name|box_height
operator|=
name|g_value_get_double
argument_list|(
name|value
argument_list|)
expr_stmt|;
break|break;
case|case
name|PROP_BOX_UNIT
case|:
name|text
operator|->
name|box_unit
operator|=
name|g_value_get_int
argument_list|(
name|value
argument_list|)
expr_stmt|;
break|break;
case|case
name|PROP_TRANSFORMATION
case|:
name|matrix
operator|=
name|g_value_get_boxed
argument_list|(
name|value
argument_list|)
expr_stmt|;
name|text
operator|->
name|transformation
operator|=
operator|*
name|matrix
expr_stmt|;
break|break;
case|case
name|PROP_OFFSET_X
case|:
name|text
operator|->
name|offset_x
operator|=
name|g_value_get_double
argument_list|(
name|value
argument_list|)
expr_stmt|;
break|break;
case|case
name|PROP_OFFSET_Y
case|:
name|text
operator|->
name|offset_y
operator|=
name|g_value_get_double
argument_list|(
name|value
argument_list|)
expr_stmt|;
break|break;
case|case
name|PROP_BORDER
case|:
name|text
operator|->
name|border
operator|=
name|g_value_get_int
argument_list|(
name|value
argument_list|)
expr_stmt|;
break|break;
case|case
name|PROP_HINTING
case|:
comment|/* interpret "hinting" only if "hint-style" has its default        * value, so we don't overwrite a serialized new hint-style with        * a compat "hinting" that is only there for old GIMP versions        */
if|if
condition|(
name|text
operator|->
name|hint_style
operator|==
name|GIMP_TEXT_HINT_STYLE_MEDIUM
condition|)
name|text
operator|->
name|hint_style
operator|=
operator|(
name|g_value_get_boolean
argument_list|(
name|value
argument_list|)
condition|?
name|GIMP_TEXT_HINT_STYLE_MEDIUM
else|:
name|GIMP_TEXT_HINT_STYLE_NONE
operator|)
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
DECL|function|gimp_text_dispatch_properties_changed (GObject * object,guint n_pspecs,GParamSpec ** pspecs)
name|gimp_text_dispatch_properties_changed
parameter_list|(
name|GObject
modifier|*
name|object
parameter_list|,
name|guint
name|n_pspecs
parameter_list|,
name|GParamSpec
modifier|*
modifier|*
name|pspecs
parameter_list|)
block|{
name|G_OBJECT_CLASS
argument_list|(
name|parent_class
argument_list|)
operator|->
name|dispatch_properties_changed
argument_list|(
name|object
argument_list|,
name|n_pspecs
argument_list|,
name|pspecs
argument_list|)
expr_stmt|;
name|g_signal_emit
argument_list|(
name|object
argument_list|,
name|text_signals
index|[
name|CHANGED
index|]
argument_list|,
literal|0
argument_list|)
expr_stmt|;
block|}
end_function

begin_function
specifier|static
name|gint64
DECL|function|gimp_text_get_memsize (GimpObject * object,gint64 * gui_size)
name|gimp_text_get_memsize
parameter_list|(
name|GimpObject
modifier|*
name|object
parameter_list|,
name|gint64
modifier|*
name|gui_size
parameter_list|)
block|{
name|GimpText
modifier|*
name|text
init|=
name|GIMP_TEXT
argument_list|(
name|object
argument_list|)
decl_stmt|;
name|gint64
name|memsize
init|=
literal|0
decl_stmt|;
name|memsize
operator|+=
name|gimp_string_get_memsize
argument_list|(
name|text
operator|->
name|text
argument_list|)
expr_stmt|;
name|memsize
operator|+=
name|gimp_string_get_memsize
argument_list|(
name|text
operator|->
name|markup
argument_list|)
expr_stmt|;
name|memsize
operator|+=
name|gimp_string_get_memsize
argument_list|(
name|text
operator|->
name|font
argument_list|)
expr_stmt|;
name|memsize
operator|+=
name|gimp_string_get_memsize
argument_list|(
name|text
operator|->
name|language
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
name|void
DECL|function|gimp_text_get_transformation (GimpText * text,GimpMatrix3 * matrix)
name|gimp_text_get_transformation
parameter_list|(
name|GimpText
modifier|*
name|text
parameter_list|,
name|GimpMatrix3
modifier|*
name|matrix
parameter_list|)
block|{
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
name|matrix
operator|!=
name|NULL
argument_list|)
expr_stmt|;
name|matrix
operator|->
name|coeff
index|[
literal|0
index|]
index|[
literal|0
index|]
operator|=
name|text
operator|->
name|transformation
operator|.
name|coeff
index|[
literal|0
index|]
index|[
literal|0
index|]
expr_stmt|;
name|matrix
operator|->
name|coeff
index|[
literal|0
index|]
index|[
literal|1
index|]
operator|=
name|text
operator|->
name|transformation
operator|.
name|coeff
index|[
literal|0
index|]
index|[
literal|1
index|]
expr_stmt|;
name|matrix
operator|->
name|coeff
index|[
literal|0
index|]
index|[
literal|2
index|]
operator|=
name|text
operator|->
name|offset_x
expr_stmt|;
name|matrix
operator|->
name|coeff
index|[
literal|1
index|]
index|[
literal|0
index|]
operator|=
name|text
operator|->
name|transformation
operator|.
name|coeff
index|[
literal|1
index|]
index|[
literal|0
index|]
expr_stmt|;
name|matrix
operator|->
name|coeff
index|[
literal|1
index|]
index|[
literal|1
index|]
operator|=
name|text
operator|->
name|transformation
operator|.
name|coeff
index|[
literal|1
index|]
index|[
literal|1
index|]
expr_stmt|;
name|matrix
operator|->
name|coeff
index|[
literal|1
index|]
index|[
literal|2
index|]
operator|=
name|text
operator|->
name|offset_y
expr_stmt|;
name|matrix
operator|->
name|coeff
index|[
literal|2
index|]
index|[
literal|0
index|]
operator|=
literal|0.0
expr_stmt|;
name|matrix
operator|->
name|coeff
index|[
literal|2
index|]
index|[
literal|1
index|]
operator|=
literal|0.0
expr_stmt|;
name|matrix
operator|->
name|coeff
index|[
literal|2
index|]
index|[
literal|2
index|]
operator|=
literal|1.0
expr_stmt|;
block|}
end_function

end_unit

