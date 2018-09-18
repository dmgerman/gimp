begin_unit|revision:0.9.5;language:C;cregit-version:0.0.1
begin_comment
comment|/* The GIMP -- an image manipulation program  * Copyright (C) 1995-1999 Spencer Kimball and Peter Mattis  *  * gimpfilloptions.c  * Copyright (C) 2003 Simon Budig  *  * This program is free software: you can redistribute it and/or modify  * it under the terms of the GNU General Public License as published by  * the Free Software Foundation; either version 3 of the License, or  * (at your option) any later version.  *  * This program is distributed in the hope that it will be useful,  * but WITHOUT ANY WARRANTY; without even the implied warranty of  * MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the  * GNU General Public License for more details.  *  * You should have received a copy of the GNU General Public License  * along with this program.  If not, see<https://www.gnu.org/licenses/>.  */
end_comment

begin_include
include|#
directive|include
file|"config.h"
end_include

begin_include
include|#
directive|include
file|<cairo.h>
end_include

begin_include
include|#
directive|include
file|<gdk-pixbuf/gdk-pixbuf.h>
end_include

begin_include
include|#
directive|include
file|<gegl.h>
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
file|"core-types.h"
end_include

begin_include
include|#
directive|include
file|"gimp.h"
end_include

begin_include
include|#
directive|include
file|"gimp-palettes.h"
end_include

begin_include
include|#
directive|include
file|"gimpdrawable.h"
end_include

begin_include
include|#
directive|include
file|"gimpdrawable-fill.h"
end_include

begin_include
include|#
directive|include
file|"gimperror.h"
end_include

begin_include
include|#
directive|include
file|"gimpfilloptions.h"
end_include

begin_include
include|#
directive|include
file|"gimppattern.h"
end_include

begin_include
include|#
directive|include
file|"gimp-intl.h"
end_include

begin_enum
enum|enum
DECL|enum|__anon2c2f186b0103
block|{
DECL|enumerator|PROP_0
name|PROP_0
block|,
DECL|enumerator|PROP_STYLE
name|PROP_STYLE
block|,
DECL|enumerator|PROP_ANTIALIAS
name|PROP_ANTIALIAS
block|,
DECL|enumerator|PROP_PATTERN_VIEW_TYPE
name|PROP_PATTERN_VIEW_TYPE
block|,
DECL|enumerator|PROP_PATTERN_VIEW_SIZE
name|PROP_PATTERN_VIEW_SIZE
block|}
enum|;
end_enum

begin_typedef
DECL|typedef|GimpFillOptionsPrivate
typedef|typedef
name|struct
name|_GimpFillOptionsPrivate
name|GimpFillOptionsPrivate
typedef|;
end_typedef

begin_struct
DECL|struct|_GimpFillOptionsPrivate
struct|struct
name|_GimpFillOptionsPrivate
block|{
DECL|member|style
name|GimpFillStyle
name|style
decl_stmt|;
DECL|member|antialias
name|gboolean
name|antialias
decl_stmt|;
DECL|member|pattern_view_type
name|GimpViewType
name|pattern_view_type
decl_stmt|;
DECL|member|pattern_view_size
name|GimpViewSize
name|pattern_view_size
decl_stmt|;
DECL|member|undo_desc
specifier|const
name|gchar
modifier|*
name|undo_desc
decl_stmt|;
block|}
struct|;
end_struct

begin_define
DECL|macro|GET_PRIVATE (options)
define|#
directive|define
name|GET_PRIVATE
parameter_list|(
name|options
parameter_list|)
define|\
value|((GimpFillOptionsPrivate *) gimp_fill_options_get_instance_private ((GimpFillOptions *) (options)))
end_define

begin_function_decl
specifier|static
name|void
name|gimp_fill_options_config_init
parameter_list|(
name|GimpConfigInterface
modifier|*
name|iface
parameter_list|)
function_decl|;
end_function_decl

begin_function_decl
specifier|static
name|void
name|gimp_fill_options_set_property
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
name|gimp_fill_options_get_property
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
name|gboolean
name|gimp_fill_options_serialize
parameter_list|(
name|GimpConfig
modifier|*
name|config
parameter_list|,
name|GimpConfigWriter
modifier|*
name|writer
parameter_list|,
name|gpointer
name|data
parameter_list|)
function_decl|;
end_function_decl

begin_macro
DECL|function|G_DEFINE_TYPE_WITH_CODE (GimpFillOptions,gimp_fill_options,GIMP_TYPE_CONTEXT,G_ADD_PRIVATE (GimpFillOptions)G_IMPLEMENT_INTERFACE (GIMP_TYPE_CONFIG,gimp_fill_options_config_init))
name|G_DEFINE_TYPE_WITH_CODE
argument_list|(
argument|GimpFillOptions
argument_list|,
argument|gimp_fill_options
argument_list|,
argument|GIMP_TYPE_CONTEXT
argument_list|,
argument|G_ADD_PRIVATE (GimpFillOptions)                          G_IMPLEMENT_INTERFACE (GIMP_TYPE_CONFIG,                                                 gimp_fill_options_config_init)
argument_list|)
end_macro

begin_function
specifier|static
name|void
name|gimp_fill_options_class_init
parameter_list|(
name|GimpFillOptionsClass
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
name|object_class
operator|->
name|set_property
operator|=
name|gimp_fill_options_set_property
expr_stmt|;
name|object_class
operator|->
name|get_property
operator|=
name|gimp_fill_options_get_property
expr_stmt|;
name|GIMP_CONFIG_PROP_ENUM
argument_list|(
name|object_class
argument_list|,
name|PROP_STYLE
argument_list|,
literal|"style"
argument_list|,
name|_
argument_list|(
literal|"Style"
argument_list|)
argument_list|,
name|NULL
argument_list|,
name|GIMP_TYPE_FILL_STYLE
argument_list|,
name|GIMP_FILL_STYLE_SOLID
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
name|_
argument_list|(
literal|"Antialiasing"
argument_list|)
argument_list|,
name|NULL
argument_list|,
name|TRUE
argument_list|,
name|GIMP_PARAM_STATIC_STRINGS
argument_list|)
expr_stmt|;
name|g_object_class_install_property
argument_list|(
name|object_class
argument_list|,
name|PROP_PATTERN_VIEW_TYPE
argument_list|,
name|g_param_spec_enum
argument_list|(
literal|"pattern-view-type"
argument_list|,
name|NULL
argument_list|,
name|NULL
argument_list|,
name|GIMP_TYPE_VIEW_TYPE
argument_list|,
name|GIMP_VIEW_TYPE_GRID
argument_list|,
name|G_PARAM_CONSTRUCT
operator||
name|GIMP_PARAM_READWRITE
argument_list|)
argument_list|)
expr_stmt|;
name|g_object_class_install_property
argument_list|(
name|object_class
argument_list|,
name|PROP_PATTERN_VIEW_SIZE
argument_list|,
name|g_param_spec_int
argument_list|(
literal|"pattern-view-size"
argument_list|,
name|NULL
argument_list|,
name|NULL
argument_list|,
name|GIMP_VIEW_SIZE_TINY
argument_list|,
name|GIMP_VIEWABLE_MAX_BUTTON_SIZE
argument_list|,
name|GIMP_VIEW_SIZE_SMALL
argument_list|,
name|G_PARAM_CONSTRUCT
operator||
name|GIMP_PARAM_READWRITE
argument_list|)
argument_list|)
expr_stmt|;
block|}
end_function

begin_function
specifier|static
name|void
DECL|function|gimp_fill_options_config_init (GimpConfigInterface * iface)
name|gimp_fill_options_config_init
parameter_list|(
name|GimpConfigInterface
modifier|*
name|iface
parameter_list|)
block|{
name|iface
operator|->
name|serialize
operator|=
name|gimp_fill_options_serialize
expr_stmt|;
block|}
end_function

begin_function
specifier|static
name|void
DECL|function|gimp_fill_options_init (GimpFillOptions * options)
name|gimp_fill_options_init
parameter_list|(
name|GimpFillOptions
modifier|*
name|options
parameter_list|)
block|{ }
end_function

begin_function
specifier|static
name|void
DECL|function|gimp_fill_options_set_property (GObject * object,guint property_id,const GValue * value,GParamSpec * pspec)
name|gimp_fill_options_set_property
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
name|GimpFillOptionsPrivate
modifier|*
name|private
init|=
name|GET_PRIVATE
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
name|PROP_STYLE
case|:
name|private
operator|->
name|style
operator|=
name|g_value_get_enum
argument_list|(
name|value
argument_list|)
expr_stmt|;
name|private
operator|->
name|undo_desc
operator|=
name|NULL
expr_stmt|;
break|break;
case|case
name|PROP_ANTIALIAS
case|:
name|private
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
name|PROP_PATTERN_VIEW_TYPE
case|:
name|private
operator|->
name|pattern_view_type
operator|=
name|g_value_get_enum
argument_list|(
name|value
argument_list|)
expr_stmt|;
break|break;
case|case
name|PROP_PATTERN_VIEW_SIZE
case|:
name|private
operator|->
name|pattern_view_size
operator|=
name|g_value_get_int
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
DECL|function|gimp_fill_options_get_property (GObject * object,guint property_id,GValue * value,GParamSpec * pspec)
name|gimp_fill_options_get_property
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
name|GimpFillOptionsPrivate
modifier|*
name|private
init|=
name|GET_PRIVATE
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
name|PROP_STYLE
case|:
name|g_value_set_enum
argument_list|(
name|value
argument_list|,
name|private
operator|->
name|style
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
name|private
operator|->
name|antialias
argument_list|)
expr_stmt|;
break|break;
case|case
name|PROP_PATTERN_VIEW_TYPE
case|:
name|g_value_set_enum
argument_list|(
name|value
argument_list|,
name|private
operator|->
name|pattern_view_type
argument_list|)
expr_stmt|;
break|break;
case|case
name|PROP_PATTERN_VIEW_SIZE
case|:
name|g_value_set_int
argument_list|(
name|value
argument_list|,
name|private
operator|->
name|pattern_view_size
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
name|gboolean
DECL|function|gimp_fill_options_serialize (GimpConfig * config,GimpConfigWriter * writer,gpointer data)
name|gimp_fill_options_serialize
parameter_list|(
name|GimpConfig
modifier|*
name|config
parameter_list|,
name|GimpConfigWriter
modifier|*
name|writer
parameter_list|,
name|gpointer
name|data
parameter_list|)
block|{
return|return
name|gimp_config_serialize_properties
argument_list|(
name|config
argument_list|,
name|writer
argument_list|)
return|;
block|}
end_function

begin_comment
comment|/*  public functions  */
end_comment

begin_function
name|GimpFillOptions
modifier|*
DECL|function|gimp_fill_options_new (Gimp * gimp,GimpContext * context,gboolean use_context_color)
name|gimp_fill_options_new
parameter_list|(
name|Gimp
modifier|*
name|gimp
parameter_list|,
name|GimpContext
modifier|*
name|context
parameter_list|,
name|gboolean
name|use_context_color
parameter_list|)
block|{
name|GimpFillOptions
modifier|*
name|options
decl_stmt|;
name|g_return_val_if_fail
argument_list|(
name|GIMP_IS_GIMP
argument_list|(
name|gimp
argument_list|)
argument_list|,
name|NULL
argument_list|)
expr_stmt|;
name|g_return_val_if_fail
argument_list|(
name|context
operator|==
name|NULL
operator|||
name|GIMP_IS_CONTEXT
argument_list|(
name|context
argument_list|)
argument_list|,
name|NULL
argument_list|)
expr_stmt|;
name|g_return_val_if_fail
argument_list|(
name|use_context_color
operator|==
name|FALSE
operator|||
name|context
operator|!=
name|NULL
argument_list|,
name|NULL
argument_list|)
expr_stmt|;
name|options
operator|=
name|g_object_new
argument_list|(
name|GIMP_TYPE_FILL_OPTIONS
argument_list|,
literal|"gimp"
argument_list|,
name|gimp
argument_list|,
name|NULL
argument_list|)
expr_stmt|;
if|if
condition|(
name|use_context_color
condition|)
block|{
name|gimp_context_define_properties
argument_list|(
name|GIMP_CONTEXT
argument_list|(
name|options
argument_list|)
argument_list|,
name|GIMP_CONTEXT_PROP_MASK_FOREGROUND
operator||
name|GIMP_CONTEXT_PROP_MASK_PATTERN
argument_list|,
name|FALSE
argument_list|)
expr_stmt|;
name|gimp_context_set_parent
argument_list|(
name|GIMP_CONTEXT
argument_list|(
name|options
argument_list|)
argument_list|,
name|context
argument_list|)
expr_stmt|;
block|}
return|return
name|options
return|;
block|}
end_function

begin_function
name|GimpFillStyle
DECL|function|gimp_fill_options_get_style (GimpFillOptions * options)
name|gimp_fill_options_get_style
parameter_list|(
name|GimpFillOptions
modifier|*
name|options
parameter_list|)
block|{
name|g_return_val_if_fail
argument_list|(
name|GIMP_IS_FILL_OPTIONS
argument_list|(
name|options
argument_list|)
argument_list|,
name|GIMP_FILL_STYLE_SOLID
argument_list|)
expr_stmt|;
return|return
name|GET_PRIVATE
argument_list|(
name|options
argument_list|)
operator|->
name|style
return|;
block|}
end_function

begin_function
name|void
DECL|function|gimp_fill_options_set_style (GimpFillOptions * options,GimpFillStyle style)
name|gimp_fill_options_set_style
parameter_list|(
name|GimpFillOptions
modifier|*
name|options
parameter_list|,
name|GimpFillStyle
name|style
parameter_list|)
block|{
name|g_return_if_fail
argument_list|(
name|GIMP_IS_FILL_OPTIONS
argument_list|(
name|options
argument_list|)
argument_list|)
expr_stmt|;
name|g_object_set
argument_list|(
name|options
argument_list|,
literal|"style"
argument_list|,
name|style
argument_list|,
name|NULL
argument_list|)
expr_stmt|;
block|}
end_function

begin_function
name|gboolean
DECL|function|gimp_fill_options_get_antialias (GimpFillOptions * options)
name|gimp_fill_options_get_antialias
parameter_list|(
name|GimpFillOptions
modifier|*
name|options
parameter_list|)
block|{
name|g_return_val_if_fail
argument_list|(
name|GIMP_IS_FILL_OPTIONS
argument_list|(
name|options
argument_list|)
argument_list|,
name|FALSE
argument_list|)
expr_stmt|;
return|return
name|GET_PRIVATE
argument_list|(
name|options
argument_list|)
operator|->
name|antialias
return|;
block|}
end_function

begin_function
name|void
DECL|function|gimp_fill_options_set_antialias (GimpFillOptions * options,gboolean antialias)
name|gimp_fill_options_set_antialias
parameter_list|(
name|GimpFillOptions
modifier|*
name|options
parameter_list|,
name|gboolean
name|antialias
parameter_list|)
block|{
name|g_return_if_fail
argument_list|(
name|GIMP_IS_FILL_OPTIONS
argument_list|(
name|options
argument_list|)
argument_list|)
expr_stmt|;
name|g_object_set
argument_list|(
name|options
argument_list|,
literal|"antialias"
argument_list|,
name|antialias
argument_list|,
name|NULL
argument_list|)
expr_stmt|;
block|}
end_function

begin_function
name|gboolean
DECL|function|gimp_fill_options_set_by_fill_type (GimpFillOptions * options,GimpContext * context,GimpFillType fill_type,GError ** error)
name|gimp_fill_options_set_by_fill_type
parameter_list|(
name|GimpFillOptions
modifier|*
name|options
parameter_list|,
name|GimpContext
modifier|*
name|context
parameter_list|,
name|GimpFillType
name|fill_type
parameter_list|,
name|GError
modifier|*
modifier|*
name|error
parameter_list|)
block|{
name|GimpFillOptionsPrivate
modifier|*
name|private
decl_stmt|;
name|GimpRGB
name|color
decl_stmt|;
specifier|const
name|gchar
modifier|*
name|undo_desc
decl_stmt|;
name|g_return_val_if_fail
argument_list|(
name|GIMP_IS_FILL_OPTIONS
argument_list|(
name|options
argument_list|)
argument_list|,
name|FALSE
argument_list|)
expr_stmt|;
name|g_return_val_if_fail
argument_list|(
name|GIMP_IS_CONTEXT
argument_list|(
name|context
argument_list|)
argument_list|,
name|FALSE
argument_list|)
expr_stmt|;
name|g_return_val_if_fail
argument_list|(
name|error
operator|==
name|NULL
operator|||
operator|*
name|error
operator|==
name|NULL
argument_list|,
name|FALSE
argument_list|)
expr_stmt|;
name|private
operator|=
name|GET_PRIVATE
argument_list|(
name|options
argument_list|)
expr_stmt|;
name|private
operator|->
name|undo_desc
operator|=
name|NULL
expr_stmt|;
switch|switch
condition|(
name|fill_type
condition|)
block|{
case|case
name|GIMP_FILL_FOREGROUND
case|:
name|gimp_context_get_foreground
argument_list|(
name|context
argument_list|,
operator|&
name|color
argument_list|)
expr_stmt|;
name|undo_desc
operator|=
name|C_
argument_list|(
literal|"undo-type"
argument_list|,
literal|"Fill with Foreground Color"
argument_list|)
expr_stmt|;
break|break;
case|case
name|GIMP_FILL_BACKGROUND
case|:
name|gimp_context_get_background
argument_list|(
name|context
argument_list|,
operator|&
name|color
argument_list|)
expr_stmt|;
name|undo_desc
operator|=
name|C_
argument_list|(
literal|"undo-type"
argument_list|,
literal|"Fill with Background Color"
argument_list|)
expr_stmt|;
break|break;
case|case
name|GIMP_FILL_WHITE
case|:
name|gimp_rgba_set
argument_list|(
operator|&
name|color
argument_list|,
literal|1.0
argument_list|,
literal|1.0
argument_list|,
literal|1.0
argument_list|,
name|GIMP_OPACITY_OPAQUE
argument_list|)
expr_stmt|;
name|undo_desc
operator|=
name|C_
argument_list|(
literal|"undo-type"
argument_list|,
literal|"Fill with White"
argument_list|)
expr_stmt|;
break|break;
case|case
name|GIMP_FILL_TRANSPARENT
case|:
name|gimp_context_get_background
argument_list|(
name|context
argument_list|,
operator|&
name|color
argument_list|)
expr_stmt|;
name|gimp_context_set_paint_mode
argument_list|(
name|GIMP_CONTEXT
argument_list|(
name|options
argument_list|)
argument_list|,
name|GIMP_LAYER_MODE_ERASE
argument_list|)
expr_stmt|;
name|undo_desc
operator|=
name|C_
argument_list|(
literal|"undo-type"
argument_list|,
literal|"Fill with Transparency"
argument_list|)
expr_stmt|;
break|break;
case|case
name|GIMP_FILL_PATTERN
case|:
block|{
name|GimpPattern
modifier|*
name|pattern
init|=
name|gimp_context_get_pattern
argument_list|(
name|context
argument_list|)
decl_stmt|;
if|if
condition|(
operator|!
name|pattern
condition|)
block|{
name|g_set_error_literal
argument_list|(
name|error
argument_list|,
name|GIMP_ERROR
argument_list|,
name|GIMP_FAILED
argument_list|,
name|_
argument_list|(
literal|"No patterns available for this operation."
argument_list|)
argument_list|)
expr_stmt|;
return|return
name|FALSE
return|;
block|}
name|gimp_fill_options_set_style
argument_list|(
name|options
argument_list|,
name|GIMP_FILL_STYLE_PATTERN
argument_list|)
expr_stmt|;
name|gimp_context_set_pattern
argument_list|(
name|GIMP_CONTEXT
argument_list|(
name|options
argument_list|)
argument_list|,
name|pattern
argument_list|)
expr_stmt|;
name|private
operator|->
name|undo_desc
operator|=
name|C_
argument_list|(
literal|"undo-type"
argument_list|,
literal|"Fill with Pattern"
argument_list|)
expr_stmt|;
return|return
name|TRUE
return|;
block|}
break|break;
default|default:
name|g_warning
argument_list|(
literal|"%s: invalid fill_type %d"
argument_list|,
name|G_STRFUNC
argument_list|,
name|fill_type
argument_list|)
expr_stmt|;
return|return
name|FALSE
return|;
block|}
name|gimp_fill_options_set_style
argument_list|(
name|options
argument_list|,
name|GIMP_FILL_STYLE_SOLID
argument_list|)
expr_stmt|;
name|gimp_context_set_foreground
argument_list|(
name|GIMP_CONTEXT
argument_list|(
name|options
argument_list|)
argument_list|,
operator|&
name|color
argument_list|)
expr_stmt|;
name|private
operator|->
name|undo_desc
operator|=
name|undo_desc
expr_stmt|;
return|return
name|TRUE
return|;
block|}
end_function

begin_function
name|gboolean
DECL|function|gimp_fill_options_set_by_fill_mode (GimpFillOptions * options,GimpContext * context,GimpBucketFillMode fill_mode,GError ** error)
name|gimp_fill_options_set_by_fill_mode
parameter_list|(
name|GimpFillOptions
modifier|*
name|options
parameter_list|,
name|GimpContext
modifier|*
name|context
parameter_list|,
name|GimpBucketFillMode
name|fill_mode
parameter_list|,
name|GError
modifier|*
modifier|*
name|error
parameter_list|)
block|{
name|GimpFillType
name|fill_type
decl_stmt|;
name|g_return_val_if_fail
argument_list|(
name|GIMP_IS_FILL_OPTIONS
argument_list|(
name|options
argument_list|)
argument_list|,
name|FALSE
argument_list|)
expr_stmt|;
name|g_return_val_if_fail
argument_list|(
name|GIMP_IS_CONTEXT
argument_list|(
name|context
argument_list|)
argument_list|,
name|FALSE
argument_list|)
expr_stmt|;
name|g_return_val_if_fail
argument_list|(
name|error
operator|==
name|NULL
operator|||
operator|*
name|error
operator|==
name|NULL
argument_list|,
name|FALSE
argument_list|)
expr_stmt|;
switch|switch
condition|(
name|fill_mode
condition|)
block|{
default|default:
case|case
name|GIMP_BUCKET_FILL_FG
case|:
name|fill_type
operator|=
name|GIMP_FILL_FOREGROUND
expr_stmt|;
break|break;
case|case
name|GIMP_BUCKET_FILL_BG
case|:
name|fill_type
operator|=
name|GIMP_FILL_BACKGROUND
expr_stmt|;
break|break;
case|case
name|GIMP_BUCKET_FILL_PATTERN
case|:
name|fill_type
operator|=
name|GIMP_FILL_PATTERN
expr_stmt|;
break|break;
block|}
return|return
name|gimp_fill_options_set_by_fill_type
argument_list|(
name|options
argument_list|,
name|context
argument_list|,
name|fill_type
argument_list|,
name|error
argument_list|)
return|;
block|}
end_function

begin_function
specifier|const
name|gchar
modifier|*
DECL|function|gimp_fill_options_get_undo_desc (GimpFillOptions * options)
name|gimp_fill_options_get_undo_desc
parameter_list|(
name|GimpFillOptions
modifier|*
name|options
parameter_list|)
block|{
name|GimpFillOptionsPrivate
modifier|*
name|private
decl_stmt|;
name|g_return_val_if_fail
argument_list|(
name|GIMP_IS_FILL_OPTIONS
argument_list|(
name|options
argument_list|)
argument_list|,
name|NULL
argument_list|)
expr_stmt|;
name|private
operator|=
name|GET_PRIVATE
argument_list|(
name|options
argument_list|)
expr_stmt|;
if|if
condition|(
name|private
operator|->
name|undo_desc
condition|)
return|return
name|private
operator|->
name|undo_desc
return|;
switch|switch
condition|(
name|private
operator|->
name|style
condition|)
block|{
case|case
name|GIMP_FILL_STYLE_SOLID
case|:
return|return
name|C_
argument_list|(
literal|"undo-type"
argument_list|,
literal|"Fill with Solid Color"
argument_list|)
return|;
case|case
name|GIMP_FILL_STYLE_PATTERN
case|:
return|return
name|C_
argument_list|(
literal|"undo-type"
argument_list|,
literal|"Fill with Pattern"
argument_list|)
return|;
block|}
name|g_return_val_if_reached
argument_list|(
name|NULL
argument_list|)
expr_stmt|;
block|}
end_function

begin_function
name|GeglBuffer
modifier|*
DECL|function|gimp_fill_options_create_buffer (GimpFillOptions * options,GimpDrawable * drawable,const GeglRectangle * rect)
name|gimp_fill_options_create_buffer
parameter_list|(
name|GimpFillOptions
modifier|*
name|options
parameter_list|,
name|GimpDrawable
modifier|*
name|drawable
parameter_list|,
specifier|const
name|GeglRectangle
modifier|*
name|rect
parameter_list|)
block|{
name|GeglBuffer
modifier|*
name|buffer
decl_stmt|;
name|g_return_val_if_fail
argument_list|(
name|GIMP_IS_FILL_OPTIONS
argument_list|(
name|options
argument_list|)
argument_list|,
name|NULL
argument_list|)
expr_stmt|;
name|g_return_val_if_fail
argument_list|(
name|gimp_fill_options_get_style
argument_list|(
name|options
argument_list|)
operator|!=
name|GIMP_FILL_STYLE_PATTERN
operator|||
name|gimp_context_get_pattern
argument_list|(
name|GIMP_CONTEXT
argument_list|(
name|options
argument_list|)
argument_list|)
operator|!=
name|NULL
argument_list|,
name|NULL
argument_list|)
expr_stmt|;
name|g_return_val_if_fail
argument_list|(
name|GIMP_IS_DRAWABLE
argument_list|(
name|drawable
argument_list|)
argument_list|,
name|NULL
argument_list|)
expr_stmt|;
name|g_return_val_if_fail
argument_list|(
name|rect
operator|!=
name|NULL
argument_list|,
name|NULL
argument_list|)
expr_stmt|;
name|buffer
operator|=
name|gegl_buffer_new
argument_list|(
name|rect
argument_list|,
name|gimp_drawable_get_format_with_alpha
argument_list|(
name|drawable
argument_list|)
argument_list|)
expr_stmt|;
switch|switch
condition|(
name|gimp_fill_options_get_style
argument_list|(
name|options
argument_list|)
condition|)
block|{
case|case
name|GIMP_FILL_STYLE_SOLID
case|:
block|{
name|GimpRGB
name|color
decl_stmt|;
name|gimp_context_get_foreground
argument_list|(
name|GIMP_CONTEXT
argument_list|(
name|options
argument_list|)
argument_list|,
operator|&
name|color
argument_list|)
expr_stmt|;
name|gimp_palettes_add_color_history
argument_list|(
name|GIMP_CONTEXT
argument_list|(
name|options
argument_list|)
operator|->
name|gimp
argument_list|,
operator|&
name|color
argument_list|)
expr_stmt|;
name|gimp_drawable_fill_buffer
argument_list|(
name|drawable
argument_list|,
name|buffer
argument_list|,
operator|&
name|color
argument_list|,
name|NULL
argument_list|,
literal|0
argument_list|,
literal|0
argument_list|)
expr_stmt|;
block|}
break|break;
case|case
name|GIMP_FILL_STYLE_PATTERN
case|:
block|{
name|GimpPattern
modifier|*
name|pattern
decl_stmt|;
name|pattern
operator|=
name|gimp_context_get_pattern
argument_list|(
name|GIMP_CONTEXT
argument_list|(
name|options
argument_list|)
argument_list|)
expr_stmt|;
name|gimp_drawable_fill_buffer
argument_list|(
name|drawable
argument_list|,
name|buffer
argument_list|,
name|NULL
argument_list|,
name|pattern
argument_list|,
literal|0
argument_list|,
literal|0
argument_list|)
expr_stmt|;
block|}
break|break;
block|}
return|return
name|buffer
return|;
block|}
end_function

end_unit

