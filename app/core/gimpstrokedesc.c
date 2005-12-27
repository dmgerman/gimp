begin_unit|revision:0.9.5;language:C;cregit-version:0.0.1
begin_comment
comment|/* The GIMP -- an image manipulation program  * Copyright (C) 1995-1999 Spencer Kimball and Peter Mattis  *  * gimpstrokedesc.c  * Copyright (C) 2004 Michael Natterer<mitch@gimp.org>  *  * This program is free software; you can redistribute it and/or modify  * it under the terms of the GNU General Public License as published by  * the Free Software Foundation; either version 2 of the License, or  * (at your option) any later version.  *  * This program is distributed in the hope that it will be useful,  * but WITHOUT ANY WARRANTY; without even the implied warranty of  * MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the  * GNU General Public License for more details.  *  * You should have received a copy of the GNU General Public License  * along with this program; if not, write to the Free Software  * Foundation, Inc., 59 Temple Place - Suite 330, Boston, MA 02111-1307, USA.  */
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
file|"libgimpbase/gimpbase.h"
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
file|"config/gimpcoreconfig.h"
end_include

begin_include
include|#
directive|include
file|"gimp.h"
end_include

begin_include
include|#
directive|include
file|"gimpcontainer.h"
end_include

begin_include
include|#
directive|include
file|"gimpcontext.h"
end_include

begin_include
include|#
directive|include
file|"gimppaintinfo.h"
end_include

begin_include
include|#
directive|include
file|"gimpstrokedesc.h"
end_include

begin_include
include|#
directive|include
file|"gimpstrokeoptions.h"
end_include

begin_include
include|#
directive|include
file|"paint/gimppaintoptions.h"
end_include

begin_enum
enum|enum
DECL|enum|__anon2c4003cd0103
block|{
DECL|enumerator|PROP_0
name|PROP_0
block|,
DECL|enumerator|PROP_GIMP
name|PROP_GIMP
block|,
DECL|enumerator|PROP_METHOD
name|PROP_METHOD
block|,
DECL|enumerator|PROP_STROKE_OPTIONS
name|PROP_STROKE_OPTIONS
block|,
DECL|enumerator|PROP_PAINT_INFO
name|PROP_PAINT_INFO
block|,
DECL|enumerator|PROP_PAINT_OPTIONS
name|PROP_PAINT_OPTIONS
block|}
enum|;
end_enum

begin_function_decl
specifier|static
name|GObject
modifier|*
name|gimp_stroke_desc_constructor
parameter_list|(
name|GType
name|type
parameter_list|,
name|guint
name|n_params
parameter_list|,
name|GObjectConstructParam
modifier|*
name|params
parameter_list|)
function_decl|;
end_function_decl

begin_function_decl
specifier|static
name|void
name|gimp_stroke_desc_finalize
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
name|gimp_stroke_desc_set_property
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
name|gimp_stroke_desc_get_property
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

begin_expr_stmt
name|G_DEFINE_TYPE_WITH_CODE
argument_list|(
name|GimpStrokeDesc
argument_list|,
name|gimp_stroke_desc
argument_list|,
name|GIMP_TYPE_OBJECT
argument_list|,
name|G_IMPLEMENT_INTERFACE
argument_list|(
name|GIMP_TYPE_CONFIG
argument_list|,
name|NULL
argument_list|)
argument_list|)
expr_stmt|;
end_expr_stmt

begin_define
DECL|macro|parent_class
define|#
directive|define
name|parent_class
value|gimp_stroke_desc_parent_class
end_define

begin_function
specifier|static
name|void
DECL|function|gimp_stroke_desc_class_init (GimpStrokeDescClass * klass)
name|gimp_stroke_desc_class_init
parameter_list|(
name|GimpStrokeDescClass
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
name|constructor
operator|=
name|gimp_stroke_desc_constructor
expr_stmt|;
name|object_class
operator|->
name|finalize
operator|=
name|gimp_stroke_desc_finalize
expr_stmt|;
name|object_class
operator|->
name|set_property
operator|=
name|gimp_stroke_desc_set_property
expr_stmt|;
name|object_class
operator|->
name|get_property
operator|=
name|gimp_stroke_desc_get_property
expr_stmt|;
name|g_object_class_install_property
argument_list|(
name|object_class
argument_list|,
name|PROP_GIMP
argument_list|,
name|g_param_spec_object
argument_list|(
literal|"gimp"
argument_list|,
name|NULL
argument_list|,
name|NULL
argument_list|,
name|GIMP_TYPE_GIMP
argument_list|,
name|G_PARAM_READWRITE
operator||
name|G_PARAM_CONSTRUCT_ONLY
argument_list|)
argument_list|)
expr_stmt|;
name|GIMP_CONFIG_INSTALL_PROP_ENUM
argument_list|(
name|object_class
argument_list|,
name|PROP_METHOD
argument_list|,
literal|"method"
argument_list|,
name|NULL
argument_list|,
name|GIMP_TYPE_STROKE_METHOD
argument_list|,
name|GIMP_STROKE_METHOD_LIBART
argument_list|,
literal|0
argument_list|)
expr_stmt|;
name|GIMP_CONFIG_INSTALL_PROP_OBJECT
argument_list|(
name|object_class
argument_list|,
name|PROP_STROKE_OPTIONS
argument_list|,
literal|"stroke-options"
argument_list|,
name|NULL
argument_list|,
name|GIMP_TYPE_STROKE_OPTIONS
argument_list|,
name|GIMP_CONFIG_PARAM_AGGREGATE
argument_list|)
expr_stmt|;
name|GIMP_CONFIG_INSTALL_PROP_OBJECT
argument_list|(
name|object_class
argument_list|,
name|PROP_PAINT_INFO
argument_list|,
literal|"paint-info"
argument_list|,
name|NULL
argument_list|,
name|GIMP_TYPE_PAINT_INFO
argument_list|,
literal|0
argument_list|)
expr_stmt|;
name|GIMP_CONFIG_INSTALL_PROP_OBJECT
argument_list|(
name|object_class
argument_list|,
name|PROP_PAINT_OPTIONS
argument_list|,
literal|"paint-options"
argument_list|,
name|NULL
argument_list|,
name|GIMP_TYPE_PAINT_OPTIONS
argument_list|,
literal|0
argument_list|)
expr_stmt|;
block|}
end_function

begin_function
specifier|static
name|void
DECL|function|gimp_stroke_desc_init (GimpStrokeDesc * desc)
name|gimp_stroke_desc_init
parameter_list|(
name|GimpStrokeDesc
modifier|*
name|desc
parameter_list|)
block|{ }
end_function

begin_function
specifier|static
name|GObject
modifier|*
DECL|function|gimp_stroke_desc_constructor (GType type,guint n_params,GObjectConstructParam * params)
name|gimp_stroke_desc_constructor
parameter_list|(
name|GType
name|type
parameter_list|,
name|guint
name|n_params
parameter_list|,
name|GObjectConstructParam
modifier|*
name|params
parameter_list|)
block|{
name|GObject
modifier|*
name|object
decl_stmt|;
name|GimpStrokeDesc
modifier|*
name|desc
decl_stmt|;
name|object
operator|=
name|G_OBJECT_CLASS
argument_list|(
name|parent_class
argument_list|)
operator|->
name|constructor
argument_list|(
name|type
argument_list|,
name|n_params
argument_list|,
name|params
argument_list|)
expr_stmt|;
name|desc
operator|=
name|GIMP_STROKE_DESC
argument_list|(
name|object
argument_list|)
expr_stmt|;
name|g_assert
argument_list|(
name|GIMP_IS_GIMP
argument_list|(
name|desc
operator|->
name|gimp
argument_list|)
argument_list|)
expr_stmt|;
name|desc
operator|->
name|stroke_options
operator|=
name|g_object_new
argument_list|(
name|GIMP_TYPE_STROKE_OPTIONS
argument_list|,
literal|"gimp"
argument_list|,
name|desc
operator|->
name|gimp
argument_list|,
name|NULL
argument_list|)
expr_stmt|;
return|return
name|object
return|;
block|}
end_function

begin_function
specifier|static
name|void
DECL|function|gimp_stroke_desc_finalize (GObject * object)
name|gimp_stroke_desc_finalize
parameter_list|(
name|GObject
modifier|*
name|object
parameter_list|)
block|{
name|GimpStrokeDesc
modifier|*
name|desc
init|=
name|GIMP_STROKE_DESC
argument_list|(
name|object
argument_list|)
decl_stmt|;
if|if
condition|(
name|desc
operator|->
name|stroke_options
condition|)
block|{
name|g_object_unref
argument_list|(
name|desc
operator|->
name|stroke_options
argument_list|)
expr_stmt|;
name|desc
operator|->
name|stroke_options
operator|=
name|NULL
expr_stmt|;
block|}
if|if
condition|(
name|desc
operator|->
name|paint_info
condition|)
block|{
name|g_object_unref
argument_list|(
name|desc
operator|->
name|paint_info
argument_list|)
expr_stmt|;
name|desc
operator|->
name|paint_info
operator|=
name|NULL
expr_stmt|;
block|}
if|if
condition|(
name|desc
operator|->
name|paint_options
condition|)
block|{
name|g_object_unref
argument_list|(
name|desc
operator|->
name|paint_options
argument_list|)
expr_stmt|;
name|desc
operator|->
name|paint_options
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
DECL|function|gimp_stroke_desc_set_property (GObject * object,guint property_id,const GValue * value,GParamSpec * pspec)
name|gimp_stroke_desc_set_property
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
name|GimpStrokeDesc
modifier|*
name|desc
init|=
name|GIMP_STROKE_DESC
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
name|PROP_GIMP
case|:
name|desc
operator|->
name|gimp
operator|=
name|g_value_get_object
argument_list|(
name|value
argument_list|)
expr_stmt|;
break|break;
case|case
name|PROP_METHOD
case|:
name|desc
operator|->
name|method
operator|=
name|g_value_get_enum
argument_list|(
name|value
argument_list|)
expr_stmt|;
break|break;
case|case
name|PROP_STROKE_OPTIONS
case|:
if|if
condition|(
name|g_value_get_object
argument_list|(
name|value
argument_list|)
condition|)
name|gimp_config_sync
argument_list|(
name|g_value_get_object
argument_list|(
name|value
argument_list|)
argument_list|,
name|G_OBJECT
argument_list|(
name|desc
operator|->
name|stroke_options
argument_list|)
argument_list|,
literal|0
argument_list|)
expr_stmt|;
break|break;
case|case
name|PROP_PAINT_INFO
case|:
if|if
condition|(
name|desc
operator|->
name|paint_info
condition|)
name|g_object_unref
argument_list|(
name|desc
operator|->
name|paint_info
argument_list|)
expr_stmt|;
name|desc
operator|->
name|paint_info
operator|=
operator|(
name|GimpPaintInfo
operator|*
operator|)
name|g_value_dup_object
argument_list|(
name|value
argument_list|)
expr_stmt|;
break|break;
case|case
name|PROP_PAINT_OPTIONS
case|:
if|if
condition|(
name|desc
operator|->
name|paint_options
condition|)
name|g_object_unref
argument_list|(
name|desc
operator|->
name|paint_options
argument_list|)
expr_stmt|;
name|desc
operator|->
name|paint_options
operator|=
operator|(
name|GimpPaintOptions
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
DECL|function|gimp_stroke_desc_get_property (GObject * object,guint property_id,GValue * value,GParamSpec * pspec)
name|gimp_stroke_desc_get_property
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
name|GimpStrokeDesc
modifier|*
name|desc
init|=
name|GIMP_STROKE_DESC
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
name|PROP_GIMP
case|:
name|g_value_set_object
argument_list|(
name|value
argument_list|,
name|desc
operator|->
name|gimp
argument_list|)
expr_stmt|;
break|break;
case|case
name|PROP_METHOD
case|:
name|g_value_set_enum
argument_list|(
name|value
argument_list|,
name|desc
operator|->
name|method
argument_list|)
expr_stmt|;
break|break;
case|case
name|PROP_STROKE_OPTIONS
case|:
name|g_value_set_object
argument_list|(
name|value
argument_list|,
name|desc
operator|->
name|stroke_options
argument_list|)
expr_stmt|;
break|break;
case|case
name|PROP_PAINT_INFO
case|:
name|g_value_set_object
argument_list|(
name|value
argument_list|,
name|desc
operator|->
name|paint_info
argument_list|)
expr_stmt|;
break|break;
case|case
name|PROP_PAINT_OPTIONS
case|:
name|g_value_set_object
argument_list|(
name|value
argument_list|,
name|desc
operator|->
name|paint_options
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

begin_comment
comment|/*  public functions  */
end_comment

begin_function
name|GimpStrokeDesc
modifier|*
DECL|function|gimp_stroke_desc_new (Gimp * gimp,GimpContext * context)
name|gimp_stroke_desc_new
parameter_list|(
name|Gimp
modifier|*
name|gimp
parameter_list|,
name|GimpContext
modifier|*
name|context
parameter_list|)
block|{
name|GimpPaintInfo
modifier|*
name|paint_info
init|=
name|NULL
decl_stmt|;
name|GimpStrokeDesc
modifier|*
name|desc
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
if|if
condition|(
name|context
condition|)
block|{
name|paint_info
operator|=
name|gimp_context_get_paint_info
argument_list|(
name|context
argument_list|)
expr_stmt|;
if|if
condition|(
operator|!
name|paint_info
condition|)
name|paint_info
operator|=
name|gimp_paint_info_get_standard
argument_list|(
name|gimp
argument_list|)
expr_stmt|;
block|}
name|desc
operator|=
name|g_object_new
argument_list|(
name|GIMP_TYPE_STROKE_DESC
argument_list|,
literal|"gimp"
argument_list|,
name|gimp
argument_list|,
literal|"paint-info"
argument_list|,
name|paint_info
argument_list|,
name|NULL
argument_list|)
expr_stmt|;
name|gimp_context_define_properties
argument_list|(
name|GIMP_CONTEXT
argument_list|(
name|desc
operator|->
name|stroke_options
argument_list|)
argument_list|,
name|GIMP_CONTEXT_FOREGROUND_MASK
operator||
name|GIMP_CONTEXT_PATTERN_MASK
argument_list|,
name|FALSE
argument_list|)
expr_stmt|;
if|if
condition|(
name|context
condition|)
name|gimp_context_set_parent
argument_list|(
name|GIMP_CONTEXT
argument_list|(
name|desc
operator|->
name|stroke_options
argument_list|)
argument_list|,
name|context
argument_list|)
expr_stmt|;
return|return
name|desc
return|;
block|}
end_function

begin_function
name|GimpStrokeDesc
modifier|*
DECL|function|gimp_stroke_desc_duplicate (GimpStrokeDesc * desc)
name|gimp_stroke_desc_duplicate
parameter_list|(
name|GimpStrokeDesc
modifier|*
name|desc
parameter_list|)
block|{
name|GimpStrokeDesc
modifier|*
name|new_desc
decl_stmt|;
name|GimpStrokeOptions
modifier|*
name|stroke_options
init|=
name|NULL
decl_stmt|;
name|GimpPaintInfo
modifier|*
name|paint_info
init|=
name|NULL
decl_stmt|;
name|GimpPaintOptions
modifier|*
name|paint_options
init|=
name|NULL
decl_stmt|;
name|new_desc
operator|=
name|gimp_stroke_desc_new
argument_list|(
name|desc
operator|->
name|gimp
argument_list|,
name|GIMP_CONTEXT
argument_list|(
name|desc
operator|->
name|stroke_options
argument_list|)
argument_list|)
expr_stmt|;
name|new_desc
operator|->
name|method
operator|=
name|desc
operator|->
name|method
expr_stmt|;
name|g_object_get
argument_list|(
name|G_OBJECT
argument_list|(
name|desc
argument_list|)
argument_list|,
literal|"stroke-options"
argument_list|,
name|stroke_options
argument_list|,
literal|"paint-info"
argument_list|,
name|paint_info
argument_list|,
literal|"paint-options"
argument_list|,
name|paint_options
argument_list|,
name|NULL
argument_list|)
expr_stmt|;
name|g_object_set
argument_list|(
name|G_OBJECT
argument_list|(
name|new_desc
argument_list|)
argument_list|,
literal|"stroke-options"
argument_list|,
name|stroke_options
argument_list|,
literal|"paint-info"
argument_list|,
name|paint_info
argument_list|,
literal|"paint-options"
argument_list|,
name|paint_options
argument_list|,
name|NULL
argument_list|)
expr_stmt|;
return|return
name|new_desc
return|;
block|}
end_function

begin_function
name|void
DECL|function|gimp_stroke_desc_prepare (GimpStrokeDesc * desc,GimpContext * context,gboolean use_default_values)
name|gimp_stroke_desc_prepare
parameter_list|(
name|GimpStrokeDesc
modifier|*
name|desc
parameter_list|,
name|GimpContext
modifier|*
name|context
parameter_list|,
name|gboolean
name|use_default_values
parameter_list|)
block|{
name|g_return_if_fail
argument_list|(
name|GIMP_IS_STROKE_DESC
argument_list|(
name|desc
argument_list|)
argument_list|)
expr_stmt|;
name|g_return_if_fail
argument_list|(
name|GIMP_IS_CONTEXT
argument_list|(
name|context
argument_list|)
argument_list|)
expr_stmt|;
switch|switch
condition|(
name|desc
operator|->
name|method
condition|)
block|{
case|case
name|GIMP_STROKE_METHOD_LIBART
case|:
break|break;
case|case
name|GIMP_STROKE_METHOD_PAINT_CORE
case|:
block|{
name|GimpPaintInfo
modifier|*
name|paint_info
init|=
name|desc
operator|->
name|paint_info
decl_stmt|;
name|GimpPaintOptions
modifier|*
name|paint_options
decl_stmt|;
if|if
condition|(
name|use_default_values
condition|)
block|{
name|paint_options
operator|=
name|gimp_paint_options_new
argument_list|(
name|paint_info
argument_list|)
expr_stmt|;
comment|/*  undefine the paint-relevant context properties and get them              *  from the passed context              */
name|gimp_context_define_properties
argument_list|(
name|GIMP_CONTEXT
argument_list|(
name|paint_options
argument_list|)
argument_list|,
name|GIMP_CONTEXT_PAINT_PROPS_MASK
argument_list|,
name|FALSE
argument_list|)
expr_stmt|;
name|gimp_context_set_parent
argument_list|(
name|GIMP_CONTEXT
argument_list|(
name|paint_options
argument_list|)
argument_list|,
name|context
argument_list|)
expr_stmt|;
block|}
else|else
block|{
name|GimpCoreConfig
modifier|*
name|config
init|=
name|context
operator|->
name|gimp
operator|->
name|config
decl_stmt|;
name|GimpContextPropMask
name|global_props
init|=
literal|0
decl_stmt|;
name|paint_options
operator|=
name|gimp_config_duplicate
argument_list|(
name|GIMP_CONFIG
argument_list|(
name|paint_info
operator|->
name|paint_options
argument_list|)
argument_list|)
expr_stmt|;
comment|/*  FG and BG are always shared between all tools  */
name|global_props
operator||=
name|GIMP_CONTEXT_FOREGROUND_MASK
expr_stmt|;
name|global_props
operator||=
name|GIMP_CONTEXT_BACKGROUND_MASK
expr_stmt|;
if|if
condition|(
name|config
operator|->
name|global_brush
condition|)
name|global_props
operator||=
name|GIMP_CONTEXT_BRUSH_MASK
expr_stmt|;
if|if
condition|(
name|config
operator|->
name|global_pattern
condition|)
name|global_props
operator||=
name|GIMP_CONTEXT_PATTERN_MASK
expr_stmt|;
if|if
condition|(
name|config
operator|->
name|global_palette
condition|)
name|global_props
operator||=
name|GIMP_CONTEXT_PALETTE_MASK
expr_stmt|;
if|if
condition|(
name|config
operator|->
name|global_gradient
condition|)
name|global_props
operator||=
name|GIMP_CONTEXT_GRADIENT_MASK
expr_stmt|;
if|if
condition|(
name|config
operator|->
name|global_font
condition|)
name|global_props
operator||=
name|GIMP_CONTEXT_FONT_MASK
expr_stmt|;
name|gimp_context_copy_properties
argument_list|(
name|context
argument_list|,
name|GIMP_CONTEXT
argument_list|(
name|paint_options
argument_list|)
argument_list|,
name|global_props
argument_list|)
expr_stmt|;
block|}
name|g_object_set
argument_list|(
name|desc
argument_list|,
literal|"paint-options"
argument_list|,
name|paint_options
argument_list|,
name|NULL
argument_list|)
expr_stmt|;
name|g_object_unref
argument_list|(
name|paint_options
argument_list|)
expr_stmt|;
block|}
break|break;
default|default:
name|g_return_if_reached
argument_list|()
expr_stmt|;
block|}
block|}
end_function

begin_function
name|void
DECL|function|gimp_stroke_desc_finish (GimpStrokeDesc * desc)
name|gimp_stroke_desc_finish
parameter_list|(
name|GimpStrokeDesc
modifier|*
name|desc
parameter_list|)
block|{
name|g_return_if_fail
argument_list|(
name|GIMP_IS_STROKE_DESC
argument_list|(
name|desc
argument_list|)
argument_list|)
expr_stmt|;
name|g_object_set
argument_list|(
name|desc
argument_list|,
literal|"paint-options"
argument_list|,
name|NULL
argument_list|,
name|NULL
argument_list|)
expr_stmt|;
block|}
end_function

end_unit

