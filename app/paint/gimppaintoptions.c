begin_unit|revision:0.9.5;language:C;cregit-version:0.0.1
begin_comment
comment|/* GIMP - The GNU Image Manipulation Program  * Copyright (C) 1995-1999 Spencer Kimball and Peter Mattis  *  * This program is free software: you can redistribute it and/or modify  * it under the terms of the GNU General Public License as published by  * the Free Software Foundation; either version 3 of the License, or  * (at your option) any later version.  *  * This program is distributed in the hope that it will be useful,  * but WITHOUT ANY WARRANTY; without even the implied warranty of  * MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the  * GNU General Public License for more details.  *  * You should have received a copy of the GNU General Public License  * along with this program.  If not, see<http://www.gnu.org/licenses/>.  */
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
file|"libgimpconfig/gimpconfig.h"
end_include

begin_include
include|#
directive|include
file|"paint-types.h"
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
file|"core/gimpdynamics.h"
end_include

begin_include
include|#
directive|include
file|"core/gimpdynamicsoutput.h"
end_include

begin_include
include|#
directive|include
file|"core/gimpgradient.h"
end_include

begin_include
include|#
directive|include
file|"core/gimppaintinfo.h"
end_include

begin_include
include|#
directive|include
file|"gimppaintoptions.h"
end_include

begin_include
include|#
directive|include
file|"gimp-intl.h"
end_include

begin_define
DECL|macro|DEFAULT_BRUSH_SCALE
define|#
directive|define
name|DEFAULT_BRUSH_SCALE
value|1.0
end_define

begin_define
DECL|macro|DEFAULT_BRUSH_ASPECT_RATIO
define|#
directive|define
name|DEFAULT_BRUSH_ASPECT_RATIO
value|1.0
end_define

begin_define
DECL|macro|DEFAULT_BRUSH_ANGLE
define|#
directive|define
name|DEFAULT_BRUSH_ANGLE
value|0.0
end_define

begin_define
DECL|macro|DEFAULT_APPLICATION_MODE
define|#
directive|define
name|DEFAULT_APPLICATION_MODE
value|GIMP_PAINT_CONSTANT
end_define

begin_define
DECL|macro|DEFAULT_HARD
define|#
directive|define
name|DEFAULT_HARD
value|FALSE
end_define

begin_define
DECL|macro|DEFAULT_USE_FADE
define|#
directive|define
name|DEFAULT_USE_FADE
value|FALSE
end_define

begin_define
DECL|macro|DEFAULT_FADE_LENGTH
define|#
directive|define
name|DEFAULT_FADE_LENGTH
value|100.0
end_define

begin_define
DECL|macro|DEFAULT_FADE_REVERSE
define|#
directive|define
name|DEFAULT_FADE_REVERSE
value|FALSE
end_define

begin_define
DECL|macro|DEFAULT_FADE_REPEAT
define|#
directive|define
name|DEFAULT_FADE_REPEAT
value|GIMP_REPEAT_NONE
end_define

begin_define
DECL|macro|DEFAULT_FADE_UNIT
define|#
directive|define
name|DEFAULT_FADE_UNIT
value|GIMP_UNIT_PIXEL
end_define

begin_define
DECL|macro|DEFAULT_USE_JITTER
define|#
directive|define
name|DEFAULT_USE_JITTER
value|FALSE
end_define

begin_define
DECL|macro|DEFAULT_JITTER_AMOUNT
define|#
directive|define
name|DEFAULT_JITTER_AMOUNT
value|0.2
end_define

begin_define
DECL|macro|DEFAULT_USE_GRADIENT
define|#
directive|define
name|DEFAULT_USE_GRADIENT
value|FALSE
end_define

begin_define
DECL|macro|DEFAULT_GRADIENT_REVERSE
define|#
directive|define
name|DEFAULT_GRADIENT_REVERSE
value|FALSE
end_define

begin_define
DECL|macro|DEFAULT_GRADIENT_REPEAT
define|#
directive|define
name|DEFAULT_GRADIENT_REPEAT
value|GIMP_REPEAT_TRIANGULAR
end_define

begin_define
DECL|macro|DEFAULT_GRADIENT_LENGTH
define|#
directive|define
name|DEFAULT_GRADIENT_LENGTH
value|100.0
end_define

begin_define
DECL|macro|DEFAULT_GRADIENT_UNIT
define|#
directive|define
name|DEFAULT_GRADIENT_UNIT
value|GIMP_UNIT_PIXEL
end_define

begin_define
DECL|macro|DYNAMIC_MAX_VALUE
define|#
directive|define
name|DYNAMIC_MAX_VALUE
value|1.0
end_define

begin_define
DECL|macro|DYNAMIC_MIN_VALUE
define|#
directive|define
name|DYNAMIC_MIN_VALUE
value|0.0
end_define

begin_enum
enum|enum
DECL|enum|__anon2b9990e10103
block|{
DECL|enumerator|PROP_0
name|PROP_0
block|,
DECL|enumerator|PROP_PAINT_INFO
name|PROP_PAINT_INFO
block|,
DECL|enumerator|PROP_BRUSH_SCALE
name|PROP_BRUSH_SCALE
block|,
DECL|enumerator|PROP_BRUSH_ASPECT_RATIO
name|PROP_BRUSH_ASPECT_RATIO
block|,
DECL|enumerator|PROP_BRUSH_ANGLE
name|PROP_BRUSH_ANGLE
block|,
DECL|enumerator|PROP_APPLICATION_MODE
name|PROP_APPLICATION_MODE
block|,
DECL|enumerator|PROP_HARD
name|PROP_HARD
block|,
DECL|enumerator|PROP_USE_FADE
name|PROP_USE_FADE
block|,
DECL|enumerator|PROP_FADE_LENGTH
name|PROP_FADE_LENGTH
block|,
DECL|enumerator|PROP_FADE_REVERSE
name|PROP_FADE_REVERSE
block|,
DECL|enumerator|PROP_FADE_REPEAT
name|PROP_FADE_REPEAT
block|,
DECL|enumerator|PROP_FADE_UNIT
name|PROP_FADE_UNIT
block|,
DECL|enumerator|PROP_USE_JITTER
name|PROP_USE_JITTER
block|,
DECL|enumerator|PROP_JITTER_AMOUNT
name|PROP_JITTER_AMOUNT
block|,
DECL|enumerator|PROP_USE_GRADIENT
name|PROP_USE_GRADIENT
block|,
DECL|enumerator|PROP_GRADIENT_REVERSE
name|PROP_GRADIENT_REVERSE
block|,
DECL|enumerator|PROP_BRUSH_VIEW_TYPE
name|PROP_BRUSH_VIEW_TYPE
block|,
DECL|enumerator|PROP_BRUSH_VIEW_SIZE
name|PROP_BRUSH_VIEW_SIZE
block|,
DECL|enumerator|PROP_PATTERN_VIEW_TYPE
name|PROP_PATTERN_VIEW_TYPE
block|,
DECL|enumerator|PROP_PATTERN_VIEW_SIZE
name|PROP_PATTERN_VIEW_SIZE
block|,
DECL|enumerator|PROP_GRADIENT_VIEW_TYPE
name|PROP_GRADIENT_VIEW_TYPE
block|,
DECL|enumerator|PROP_GRADIENT_VIEW_SIZE
name|PROP_GRADIENT_VIEW_SIZE
block|}
enum|;
end_enum

begin_function_decl
specifier|static
name|void
name|gimp_paint_options_finalize
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
name|gimp_paint_options_set_property
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
name|gimp_paint_options_get_property
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
name|gimp_paint_options_notify
parameter_list|(
name|GObject
modifier|*
name|object
parameter_list|,
name|GParamSpec
modifier|*
name|pspec
parameter_list|)
function_decl|;
end_function_decl

begin_macro
DECL|function|G_DEFINE_TYPE (GimpPaintOptions,gimp_paint_options,GIMP_TYPE_TOOL_OPTIONS)
name|G_DEFINE_TYPE
argument_list|(
argument|GimpPaintOptions
argument_list|,
argument|gimp_paint_options
argument_list|,
argument|GIMP_TYPE_TOOL_OPTIONS
argument_list|)
end_macro

begin_define
DECL|macro|parent_class
define|#
directive|define
name|parent_class
value|gimp_paint_options_parent_class
end_define

begin_function
specifier|static
name|void
name|gimp_paint_options_class_init
parameter_list|(
name|GimpPaintOptionsClass
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
name|finalize
operator|=
name|gimp_paint_options_finalize
expr_stmt|;
name|object_class
operator|->
name|set_property
operator|=
name|gimp_paint_options_set_property
expr_stmt|;
name|object_class
operator|->
name|get_property
operator|=
name|gimp_paint_options_get_property
expr_stmt|;
name|object_class
operator|->
name|notify
operator|=
name|gimp_paint_options_notify
expr_stmt|;
name|g_object_class_install_property
argument_list|(
name|object_class
argument_list|,
name|PROP_PAINT_INFO
argument_list|,
name|g_param_spec_object
argument_list|(
literal|"paint-info"
argument_list|,
name|NULL
argument_list|,
name|NULL
argument_list|,
name|GIMP_TYPE_PAINT_INFO
argument_list|,
name|GIMP_PARAM_READWRITE
operator||
name|G_PARAM_CONSTRUCT_ONLY
argument_list|)
argument_list|)
expr_stmt|;
name|GIMP_CONFIG_INSTALL_PROP_DOUBLE
argument_list|(
name|object_class
argument_list|,
name|PROP_BRUSH_SCALE
argument_list|,
literal|"brush-scale"
argument_list|,
name|_
argument_list|(
literal|"Brush Scale"
argument_list|)
argument_list|,
literal|0.01
argument_list|,
literal|10.0
argument_list|,
name|DEFAULT_BRUSH_SCALE
argument_list|,
name|GIMP_PARAM_STATIC_STRINGS
argument_list|)
expr_stmt|;
name|GIMP_CONFIG_INSTALL_PROP_DOUBLE
argument_list|(
name|object_class
argument_list|,
name|PROP_BRUSH_ASPECT_RATIO
argument_list|,
literal|"brush-aspect-ratio"
argument_list|,
name|_
argument_list|(
literal|"Brush Aspect Ratio"
argument_list|)
argument_list|,
literal|0.01
argument_list|,
literal|10.0
argument_list|,
name|DEFAULT_BRUSH_ASPECT_RATIO
argument_list|,
name|GIMP_PARAM_STATIC_STRINGS
argument_list|)
expr_stmt|;
name|GIMP_CONFIG_INSTALL_PROP_DOUBLE
argument_list|(
name|object_class
argument_list|,
name|PROP_BRUSH_ANGLE
argument_list|,
literal|"brush-angle"
argument_list|,
name|_
argument_list|(
literal|"Brush Angle"
argument_list|)
argument_list|,
operator|-
literal|180.0
argument_list|,
literal|180.0
argument_list|,
name|DEFAULT_BRUSH_ANGLE
argument_list|,
name|GIMP_PARAM_STATIC_STRINGS
argument_list|)
expr_stmt|;
name|GIMP_CONFIG_INSTALL_PROP_ENUM
argument_list|(
name|object_class
argument_list|,
name|PROP_APPLICATION_MODE
argument_list|,
literal|"application-mode"
argument_list|,
name|NULL
argument_list|,
name|GIMP_TYPE_PAINT_APPLICATION_MODE
argument_list|,
name|DEFAULT_APPLICATION_MODE
argument_list|,
name|GIMP_PARAM_STATIC_STRINGS
argument_list|)
expr_stmt|;
name|GIMP_CONFIG_INSTALL_PROP_BOOLEAN
argument_list|(
name|object_class
argument_list|,
name|PROP_HARD
argument_list|,
literal|"hard"
argument_list|,
name|NULL
argument_list|,
name|DEFAULT_HARD
argument_list|,
name|GIMP_PARAM_STATIC_STRINGS
argument_list|)
expr_stmt|;
name|GIMP_CONFIG_INSTALL_PROP_BOOLEAN
argument_list|(
name|object_class
argument_list|,
name|PROP_USE_FADE
argument_list|,
literal|"use-fade"
argument_list|,
name|NULL
argument_list|,
name|DEFAULT_USE_FADE
argument_list|,
name|GIMP_PARAM_STATIC_STRINGS
argument_list|)
expr_stmt|;
name|GIMP_CONFIG_INSTALL_PROP_DOUBLE
argument_list|(
name|object_class
argument_list|,
name|PROP_FADE_LENGTH
argument_list|,
literal|"fade-length"
argument_list|,
name|NULL
argument_list|,
literal|0.0
argument_list|,
literal|32767.0
argument_list|,
name|DEFAULT_FADE_LENGTH
argument_list|,
name|GIMP_PARAM_STATIC_STRINGS
argument_list|)
expr_stmt|;
name|GIMP_CONFIG_INSTALL_PROP_UNIT
argument_list|(
name|object_class
argument_list|,
name|PROP_FADE_UNIT
argument_list|,
literal|"fade-unit"
argument_list|,
name|NULL
argument_list|,
name|TRUE
argument_list|,
name|TRUE
argument_list|,
name|DEFAULT_FADE_UNIT
argument_list|,
name|GIMP_PARAM_STATIC_STRINGS
argument_list|)
expr_stmt|;
name|GIMP_CONFIG_INSTALL_PROP_BOOLEAN
argument_list|(
name|object_class
argument_list|,
name|PROP_FADE_REVERSE
argument_list|,
literal|"fade-reverse"
argument_list|,
name|NULL
argument_list|,
name|DEFAULT_FADE_REVERSE
argument_list|,
name|GIMP_PARAM_STATIC_STRINGS
argument_list|)
expr_stmt|;
name|GIMP_CONFIG_INSTALL_PROP_ENUM
argument_list|(
name|object_class
argument_list|,
name|PROP_FADE_REPEAT
argument_list|,
literal|"fade-repeat"
argument_list|,
name|NULL
argument_list|,
name|GIMP_TYPE_REPEAT_MODE
argument_list|,
name|DEFAULT_FADE_REPEAT
argument_list|,
name|GIMP_PARAM_STATIC_STRINGS
argument_list|)
expr_stmt|;
name|GIMP_CONFIG_INSTALL_PROP_BOOLEAN
argument_list|(
name|object_class
argument_list|,
name|PROP_USE_JITTER
argument_list|,
literal|"use-jitter"
argument_list|,
name|NULL
argument_list|,
name|DEFAULT_USE_JITTER
argument_list|,
name|GIMP_PARAM_STATIC_STRINGS
argument_list|)
expr_stmt|;
name|GIMP_CONFIG_INSTALL_PROP_DOUBLE
argument_list|(
name|object_class
argument_list|,
name|PROP_JITTER_AMOUNT
argument_list|,
literal|"jitter-amount"
argument_list|,
name|NULL
argument_list|,
literal|0.0
argument_list|,
literal|50.0
argument_list|,
name|DEFAULT_JITTER_AMOUNT
argument_list|,
name|GIMP_PARAM_STATIC_STRINGS
argument_list|)
expr_stmt|;
name|GIMP_CONFIG_INSTALL_PROP_BOOLEAN
argument_list|(
name|object_class
argument_list|,
name|PROP_USE_GRADIENT
argument_list|,
literal|"use-gradient"
argument_list|,
name|NULL
argument_list|,
name|DEFAULT_USE_GRADIENT
argument_list|,
name|GIMP_PARAM_STATIC_STRINGS
argument_list|)
expr_stmt|;
name|GIMP_CONFIG_INSTALL_PROP_BOOLEAN
argument_list|(
name|object_class
argument_list|,
name|PROP_GRADIENT_REVERSE
argument_list|,
literal|"gradient-reverse"
argument_list|,
name|NULL
argument_list|,
name|DEFAULT_GRADIENT_REVERSE
argument_list|,
name|GIMP_PARAM_STATIC_STRINGS
argument_list|)
expr_stmt|;
name|GIMP_CONFIG_INSTALL_PROP_ENUM
argument_list|(
name|object_class
argument_list|,
name|PROP_BRUSH_VIEW_TYPE
argument_list|,
literal|"brush-view-type"
argument_list|,
name|NULL
argument_list|,
name|GIMP_TYPE_VIEW_TYPE
argument_list|,
name|GIMP_VIEW_TYPE_GRID
argument_list|,
name|GIMP_PARAM_STATIC_STRINGS
argument_list|)
expr_stmt|;
name|GIMP_CONFIG_INSTALL_PROP_INT
argument_list|(
name|object_class
argument_list|,
name|PROP_BRUSH_VIEW_SIZE
argument_list|,
literal|"brush-view-size"
argument_list|,
name|NULL
argument_list|,
name|GIMP_VIEW_SIZE_TINY
argument_list|,
name|GIMP_VIEWABLE_MAX_BUTTON_SIZE
argument_list|,
name|GIMP_VIEW_SIZE_SMALL
argument_list|,
name|GIMP_PARAM_STATIC_STRINGS
argument_list|)
expr_stmt|;
name|GIMP_CONFIG_INSTALL_PROP_ENUM
argument_list|(
name|object_class
argument_list|,
name|PROP_PATTERN_VIEW_TYPE
argument_list|,
literal|"pattern-view-type"
argument_list|,
name|NULL
argument_list|,
name|GIMP_TYPE_VIEW_TYPE
argument_list|,
name|GIMP_VIEW_TYPE_GRID
argument_list|,
name|GIMP_PARAM_STATIC_STRINGS
argument_list|)
expr_stmt|;
name|GIMP_CONFIG_INSTALL_PROP_INT
argument_list|(
name|object_class
argument_list|,
name|PROP_PATTERN_VIEW_SIZE
argument_list|,
literal|"pattern-view-size"
argument_list|,
name|NULL
argument_list|,
name|GIMP_VIEW_SIZE_TINY
argument_list|,
name|GIMP_VIEWABLE_MAX_BUTTON_SIZE
argument_list|,
name|GIMP_VIEW_SIZE_SMALL
argument_list|,
name|GIMP_PARAM_STATIC_STRINGS
argument_list|)
expr_stmt|;
name|GIMP_CONFIG_INSTALL_PROP_ENUM
argument_list|(
name|object_class
argument_list|,
name|PROP_GRADIENT_VIEW_TYPE
argument_list|,
literal|"gradient-view-type"
argument_list|,
name|NULL
argument_list|,
name|GIMP_TYPE_VIEW_TYPE
argument_list|,
name|GIMP_VIEW_TYPE_LIST
argument_list|,
name|GIMP_PARAM_STATIC_STRINGS
argument_list|)
expr_stmt|;
name|GIMP_CONFIG_INSTALL_PROP_INT
argument_list|(
name|object_class
argument_list|,
name|PROP_GRADIENT_VIEW_SIZE
argument_list|,
literal|"gradient-view-size"
argument_list|,
name|NULL
argument_list|,
name|GIMP_VIEW_SIZE_TINY
argument_list|,
name|GIMP_VIEWABLE_MAX_BUTTON_SIZE
argument_list|,
name|GIMP_VIEW_SIZE_LARGE
argument_list|,
name|GIMP_PARAM_STATIC_STRINGS
argument_list|)
expr_stmt|;
block|}
end_function

begin_function
specifier|static
name|void
DECL|function|gimp_paint_options_init (GimpPaintOptions * options)
name|gimp_paint_options_init
parameter_list|(
name|GimpPaintOptions
modifier|*
name|options
parameter_list|)
block|{
name|options
operator|->
name|application_mode_save
operator|=
name|DEFAULT_APPLICATION_MODE
expr_stmt|;
name|options
operator|->
name|fade_options
operator|=
name|g_slice_new0
argument_list|(
name|GimpFadeOptions
argument_list|)
expr_stmt|;
name|options
operator|->
name|jitter_options
operator|=
name|g_slice_new0
argument_list|(
name|GimpJitterOptions
argument_list|)
expr_stmt|;
name|options
operator|->
name|gradient_options
operator|=
name|g_slice_new0
argument_list|(
name|GimpGradientOptions
argument_list|)
expr_stmt|;
block|}
end_function

begin_function
specifier|static
name|void
DECL|function|gimp_paint_options_finalize (GObject * object)
name|gimp_paint_options_finalize
parameter_list|(
name|GObject
modifier|*
name|object
parameter_list|)
block|{
name|GimpPaintOptions
modifier|*
name|options
init|=
name|GIMP_PAINT_OPTIONS
argument_list|(
name|object
argument_list|)
decl_stmt|;
if|if
condition|(
name|options
operator|->
name|paint_info
condition|)
name|g_object_unref
argument_list|(
name|options
operator|->
name|paint_info
argument_list|)
expr_stmt|;
name|g_slice_free
argument_list|(
name|GimpFadeOptions
argument_list|,
name|options
operator|->
name|fade_options
argument_list|)
expr_stmt|;
name|g_slice_free
argument_list|(
name|GimpJitterOptions
argument_list|,
name|options
operator|->
name|jitter_options
argument_list|)
expr_stmt|;
name|g_slice_free
argument_list|(
name|GimpGradientOptions
argument_list|,
name|options
operator|->
name|gradient_options
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
DECL|function|gimp_paint_options_set_property (GObject * object,guint property_id,const GValue * value,GParamSpec * pspec)
name|gimp_paint_options_set_property
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
name|GimpPaintOptions
modifier|*
name|options
init|=
name|GIMP_PAINT_OPTIONS
argument_list|(
name|object
argument_list|)
decl_stmt|;
name|GimpFadeOptions
modifier|*
name|fade_options
init|=
name|options
operator|->
name|fade_options
decl_stmt|;
name|GimpJitterOptions
modifier|*
name|jitter_options
init|=
name|options
operator|->
name|jitter_options
decl_stmt|;
name|GimpGradientOptions
modifier|*
name|gradient_options
init|=
name|options
operator|->
name|gradient_options
decl_stmt|;
switch|switch
condition|(
name|property_id
condition|)
block|{
case|case
name|PROP_PAINT_INFO
case|:
name|options
operator|->
name|paint_info
operator|=
name|g_value_dup_object
argument_list|(
name|value
argument_list|)
expr_stmt|;
break|break;
case|case
name|PROP_BRUSH_SCALE
case|:
name|options
operator|->
name|brush_scale
operator|=
name|g_value_get_double
argument_list|(
name|value
argument_list|)
expr_stmt|;
break|break;
case|case
name|PROP_BRUSH_ASPECT_RATIO
case|:
name|options
operator|->
name|brush_aspect_ratio
operator|=
name|g_value_get_double
argument_list|(
name|value
argument_list|)
expr_stmt|;
break|break;
case|case
name|PROP_BRUSH_ANGLE
case|:
name|options
operator|->
name|brush_angle
operator|=
operator|-
literal|1.0
operator|*
name|g_value_get_double
argument_list|(
name|value
argument_list|)
operator|/
literal|360.0
expr_stmt|;
comment|/* let's make the angle mathematically correct */
break|break;
case|case
name|PROP_APPLICATION_MODE
case|:
name|options
operator|->
name|application_mode
operator|=
name|g_value_get_enum
argument_list|(
name|value
argument_list|)
expr_stmt|;
break|break;
case|case
name|PROP_HARD
case|:
name|options
operator|->
name|hard
operator|=
name|g_value_get_boolean
argument_list|(
name|value
argument_list|)
expr_stmt|;
break|break;
case|case
name|PROP_USE_FADE
case|:
name|fade_options
operator|->
name|use_fade
operator|=
name|g_value_get_boolean
argument_list|(
name|value
argument_list|)
expr_stmt|;
break|break;
case|case
name|PROP_FADE_LENGTH
case|:
name|fade_options
operator|->
name|fade_length
operator|=
name|g_value_get_double
argument_list|(
name|value
argument_list|)
expr_stmt|;
break|break;
case|case
name|PROP_FADE_REVERSE
case|:
name|fade_options
operator|->
name|fade_reverse
operator|=
name|g_value_get_boolean
argument_list|(
name|value
argument_list|)
expr_stmt|;
break|break;
case|case
name|PROP_FADE_REPEAT
case|:
name|fade_options
operator|->
name|fade_repeat
operator|=
name|g_value_get_enum
argument_list|(
name|value
argument_list|)
expr_stmt|;
break|break;
case|case
name|PROP_FADE_UNIT
case|:
name|fade_options
operator|->
name|fade_unit
operator|=
name|g_value_get_int
argument_list|(
name|value
argument_list|)
expr_stmt|;
break|break;
case|case
name|PROP_USE_JITTER
case|:
name|jitter_options
operator|->
name|use_jitter
operator|=
name|g_value_get_boolean
argument_list|(
name|value
argument_list|)
expr_stmt|;
break|break;
case|case
name|PROP_JITTER_AMOUNT
case|:
name|jitter_options
operator|->
name|jitter_amount
operator|=
name|g_value_get_double
argument_list|(
name|value
argument_list|)
expr_stmt|;
break|break;
case|case
name|PROP_USE_GRADIENT
case|:
name|gradient_options
operator|->
name|use_gradient
operator|=
name|g_value_get_boolean
argument_list|(
name|value
argument_list|)
expr_stmt|;
break|break;
case|case
name|PROP_GRADIENT_REVERSE
case|:
name|gradient_options
operator|->
name|gradient_reverse
operator|=
name|g_value_get_boolean
argument_list|(
name|value
argument_list|)
expr_stmt|;
break|break;
case|case
name|PROP_BRUSH_VIEW_TYPE
case|:
name|options
operator|->
name|brush_view_type
operator|=
name|g_value_get_enum
argument_list|(
name|value
argument_list|)
expr_stmt|;
break|break;
case|case
name|PROP_BRUSH_VIEW_SIZE
case|:
name|options
operator|->
name|brush_view_size
operator|=
name|g_value_get_int
argument_list|(
name|value
argument_list|)
expr_stmt|;
break|break;
case|case
name|PROP_PATTERN_VIEW_TYPE
case|:
name|options
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
name|options
operator|->
name|pattern_view_size
operator|=
name|g_value_get_int
argument_list|(
name|value
argument_list|)
expr_stmt|;
break|break;
case|case
name|PROP_GRADIENT_VIEW_TYPE
case|:
name|options
operator|->
name|gradient_view_type
operator|=
name|g_value_get_enum
argument_list|(
name|value
argument_list|)
expr_stmt|;
break|break;
case|case
name|PROP_GRADIENT_VIEW_SIZE
case|:
name|options
operator|->
name|gradient_view_size
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
DECL|function|gimp_paint_options_get_property (GObject * object,guint property_id,GValue * value,GParamSpec * pspec)
name|gimp_paint_options_get_property
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
name|GimpPaintOptions
modifier|*
name|options
init|=
name|GIMP_PAINT_OPTIONS
argument_list|(
name|object
argument_list|)
decl_stmt|;
name|GimpFadeOptions
modifier|*
name|fade_options
init|=
name|options
operator|->
name|fade_options
decl_stmt|;
name|GimpJitterOptions
modifier|*
name|jitter_options
init|=
name|options
operator|->
name|jitter_options
decl_stmt|;
name|GimpGradientOptions
modifier|*
name|gradient_options
init|=
name|options
operator|->
name|gradient_options
decl_stmt|;
switch|switch
condition|(
name|property_id
condition|)
block|{
case|case
name|PROP_PAINT_INFO
case|:
name|g_value_set_object
argument_list|(
name|value
argument_list|,
name|options
operator|->
name|paint_info
argument_list|)
expr_stmt|;
break|break;
case|case
name|PROP_BRUSH_SCALE
case|:
name|g_value_set_double
argument_list|(
name|value
argument_list|,
name|options
operator|->
name|brush_scale
argument_list|)
expr_stmt|;
break|break;
case|case
name|PROP_BRUSH_ASPECT_RATIO
case|:
name|g_value_set_double
argument_list|(
name|value
argument_list|,
name|options
operator|->
name|brush_aspect_ratio
argument_list|)
expr_stmt|;
break|break;
case|case
name|PROP_BRUSH_ANGLE
case|:
name|g_value_set_double
argument_list|(
name|value
argument_list|,
operator|-
literal|1.0
operator|*
name|options
operator|->
name|brush_angle
operator|*
literal|360.0
argument_list|)
expr_stmt|;
comment|/* mathematically correct -> intuitively correct */
break|break;
case|case
name|PROP_APPLICATION_MODE
case|:
name|g_value_set_enum
argument_list|(
name|value
argument_list|,
name|options
operator|->
name|application_mode
argument_list|)
expr_stmt|;
break|break;
case|case
name|PROP_HARD
case|:
name|g_value_set_boolean
argument_list|(
name|value
argument_list|,
name|options
operator|->
name|hard
argument_list|)
expr_stmt|;
break|break;
case|case
name|PROP_USE_FADE
case|:
name|g_value_set_boolean
argument_list|(
name|value
argument_list|,
name|fade_options
operator|->
name|use_fade
argument_list|)
expr_stmt|;
break|break;
case|case
name|PROP_FADE_LENGTH
case|:
name|g_value_set_double
argument_list|(
name|value
argument_list|,
name|fade_options
operator|->
name|fade_length
argument_list|)
expr_stmt|;
break|break;
case|case
name|PROP_FADE_REVERSE
case|:
name|g_value_set_boolean
argument_list|(
name|value
argument_list|,
name|fade_options
operator|->
name|fade_reverse
argument_list|)
expr_stmt|;
break|break;
case|case
name|PROP_FADE_REPEAT
case|:
name|g_value_set_enum
argument_list|(
name|value
argument_list|,
name|fade_options
operator|->
name|fade_repeat
argument_list|)
expr_stmt|;
break|break;
case|case
name|PROP_FADE_UNIT
case|:
name|g_value_set_int
argument_list|(
name|value
argument_list|,
name|fade_options
operator|->
name|fade_unit
argument_list|)
expr_stmt|;
break|break;
case|case
name|PROP_USE_JITTER
case|:
name|g_value_set_boolean
argument_list|(
name|value
argument_list|,
name|jitter_options
operator|->
name|use_jitter
argument_list|)
expr_stmt|;
break|break;
case|case
name|PROP_JITTER_AMOUNT
case|:
name|g_value_set_double
argument_list|(
name|value
argument_list|,
name|jitter_options
operator|->
name|jitter_amount
argument_list|)
expr_stmt|;
break|break;
case|case
name|PROP_USE_GRADIENT
case|:
name|g_value_set_boolean
argument_list|(
name|value
argument_list|,
name|gradient_options
operator|->
name|use_gradient
argument_list|)
expr_stmt|;
break|break;
case|case
name|PROP_GRADIENT_REVERSE
case|:
name|g_value_set_boolean
argument_list|(
name|value
argument_list|,
name|gradient_options
operator|->
name|gradient_reverse
argument_list|)
expr_stmt|;
break|break;
case|case
name|PROP_BRUSH_VIEW_TYPE
case|:
name|g_value_set_enum
argument_list|(
name|value
argument_list|,
name|options
operator|->
name|brush_view_type
argument_list|)
expr_stmt|;
break|break;
case|case
name|PROP_BRUSH_VIEW_SIZE
case|:
name|g_value_set_int
argument_list|(
name|value
argument_list|,
name|options
operator|->
name|brush_view_size
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
name|options
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
name|options
operator|->
name|pattern_view_size
argument_list|)
expr_stmt|;
break|break;
case|case
name|PROP_GRADIENT_VIEW_TYPE
case|:
name|g_value_set_enum
argument_list|(
name|value
argument_list|,
name|options
operator|->
name|gradient_view_type
argument_list|)
expr_stmt|;
break|break;
case|case
name|PROP_GRADIENT_VIEW_SIZE
case|:
name|g_value_set_int
argument_list|(
name|value
argument_list|,
name|options
operator|->
name|gradient_view_size
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
DECL|function|gimp_paint_options_notify (GObject * object,GParamSpec * pspec)
name|gimp_paint_options_notify
parameter_list|(
name|GObject
modifier|*
name|object
parameter_list|,
name|GParamSpec
modifier|*
name|pspec
parameter_list|)
block|{
name|GimpPaintOptions
modifier|*
name|options
init|=
name|GIMP_PAINT_OPTIONS
argument_list|(
name|object
argument_list|)
decl_stmt|;
if|if
condition|(
name|pspec
operator|->
name|param_id
operator|==
name|PROP_USE_GRADIENT
condition|)
block|{
if|if
condition|(
name|options
operator|->
name|gradient_options
operator|->
name|use_gradient
condition|)
block|{
name|options
operator|->
name|application_mode_save
operator|=
name|options
operator|->
name|application_mode
expr_stmt|;
name|options
operator|->
name|application_mode
operator|=
name|GIMP_PAINT_INCREMENTAL
expr_stmt|;
block|}
else|else
block|{
name|options
operator|->
name|application_mode
operator|=
name|options
operator|->
name|application_mode_save
expr_stmt|;
block|}
name|g_object_notify
argument_list|(
name|object
argument_list|,
literal|"application-mode"
argument_list|)
expr_stmt|;
block|}
if|if
condition|(
name|G_OBJECT_CLASS
argument_list|(
name|parent_class
argument_list|)
operator|->
name|notify
condition|)
name|G_OBJECT_CLASS
argument_list|(
name|parent_class
argument_list|)
operator|->
name|notify
argument_list|(
name|object
argument_list|,
name|pspec
argument_list|)
expr_stmt|;
block|}
end_function

begin_function
name|GimpPaintOptions
modifier|*
DECL|function|gimp_paint_options_new (GimpPaintInfo * paint_info)
name|gimp_paint_options_new
parameter_list|(
name|GimpPaintInfo
modifier|*
name|paint_info
parameter_list|)
block|{
name|GimpPaintOptions
modifier|*
name|options
decl_stmt|;
name|g_return_val_if_fail
argument_list|(
name|GIMP_IS_PAINT_INFO
argument_list|(
name|paint_info
argument_list|)
argument_list|,
name|NULL
argument_list|)
expr_stmt|;
name|options
operator|=
name|g_object_new
argument_list|(
name|paint_info
operator|->
name|paint_options_type
argument_list|,
literal|"gimp"
argument_list|,
name|paint_info
operator|->
name|gimp
argument_list|,
literal|"name"
argument_list|,
name|gimp_object_get_name
argument_list|(
name|paint_info
argument_list|)
argument_list|,
literal|"paint-info"
argument_list|,
name|paint_info
argument_list|,
name|NULL
argument_list|)
expr_stmt|;
return|return
name|options
return|;
block|}
end_function

begin_function
name|gdouble
DECL|function|gimp_paint_options_get_fade (GimpPaintOptions * paint_options,GimpImage * image,gdouble pixel_dist)
name|gimp_paint_options_get_fade
parameter_list|(
name|GimpPaintOptions
modifier|*
name|paint_options
parameter_list|,
name|GimpImage
modifier|*
name|image
parameter_list|,
name|gdouble
name|pixel_dist
parameter_list|)
block|{
name|GimpFadeOptions
modifier|*
name|fade_options
decl_stmt|;
name|gdouble
name|z
init|=
operator|-
literal|1.0
decl_stmt|;
name|g_return_val_if_fail
argument_list|(
name|GIMP_IS_PAINT_OPTIONS
argument_list|(
name|paint_options
argument_list|)
argument_list|,
name|DYNAMIC_MAX_VALUE
argument_list|)
expr_stmt|;
name|g_return_val_if_fail
argument_list|(
name|GIMP_IS_IMAGE
argument_list|(
name|image
argument_list|)
argument_list|,
name|DYNAMIC_MAX_VALUE
argument_list|)
expr_stmt|;
name|fade_options
operator|=
name|paint_options
operator|->
name|fade_options
expr_stmt|;
if|if
condition|(
name|fade_options
operator|->
name|use_fade
condition|)
block|{
name|gdouble
name|fade_out
init|=
literal|0.0
decl_stmt|;
name|gdouble
name|unit_factor
decl_stmt|;
name|gdouble
name|pos
decl_stmt|;
switch|switch
condition|(
name|fade_options
operator|->
name|fade_unit
condition|)
block|{
case|case
name|GIMP_UNIT_PIXEL
case|:
name|fade_out
operator|=
name|fade_options
operator|->
name|fade_length
expr_stmt|;
break|break;
case|case
name|GIMP_UNIT_PERCENT
case|:
name|fade_out
operator|=
operator|(
name|MAX
argument_list|(
name|gimp_image_get_width
argument_list|(
name|image
argument_list|)
argument_list|,
name|gimp_image_get_height
argument_list|(
name|image
argument_list|)
argument_list|)
operator|*
name|fade_options
operator|->
name|fade_length
operator|/
literal|100
operator|)
expr_stmt|;
break|break;
default|default:
block|{
name|gdouble
name|xres
decl_stmt|;
name|gdouble
name|yres
decl_stmt|;
name|gimp_image_get_resolution
argument_list|(
name|image
argument_list|,
operator|&
name|xres
argument_list|,
operator|&
name|yres
argument_list|)
expr_stmt|;
name|unit_factor
operator|=
name|gimp_unit_get_factor
argument_list|(
name|fade_options
operator|->
name|fade_unit
argument_list|)
expr_stmt|;
name|fade_out
operator|=
operator|(
name|fade_options
operator|->
name|fade_length
operator|*
name|MAX
argument_list|(
name|xres
argument_list|,
name|yres
argument_list|)
operator|/
name|unit_factor
operator|)
expr_stmt|;
block|}
break|break;
block|}
comment|/*  factor in the fade out value  */
if|if
condition|(
name|fade_out
operator|>
literal|0.0
condition|)
block|{
name|pos
operator|=
name|pixel_dist
operator|/
name|fade_out
expr_stmt|;
block|}
else|else
name|pos
operator|=
name|DYNAMIC_MAX_VALUE
expr_stmt|;
comment|/*  for no repeat, set pos close to 1.0 after the first chunk  */
if|if
condition|(
name|fade_options
operator|->
name|fade_repeat
operator|==
name|GIMP_REPEAT_NONE
operator|&&
name|pos
operator|>=
name|DYNAMIC_MAX_VALUE
condition|)
name|pos
operator|=
name|DYNAMIC_MAX_VALUE
operator|-
literal|0.0000001
expr_stmt|;
if|if
condition|(
operator|(
operator|(
name|gint
operator|)
name|pos
operator|&
literal|1
operator|)
operator|&&
name|fade_options
operator|->
name|fade_repeat
operator|!=
name|GIMP_REPEAT_SAWTOOTH
condition|)
name|pos
operator|=
name|DYNAMIC_MAX_VALUE
operator|-
operator|(
name|pos
operator|-
operator|(
name|gint
operator|)
name|pos
operator|)
expr_stmt|;
else|else
name|pos
operator|=
name|pos
operator|-
operator|(
name|gint
operator|)
name|pos
expr_stmt|;
comment|/*  Model the amount of paint left as a gaussian curve  */
name|z
operator|=
name|exp
argument_list|(
operator|-
name|pos
operator|*
name|pos
operator|*
literal|5.541
argument_list|)
expr_stmt|;
if|if
condition|(
name|fade_options
operator|->
name|fade_reverse
condition|)
name|z
operator|=
literal|1.0
operator|-
name|z
expr_stmt|;
return|return
name|z
return|;
comment|/*  ln (1/255)  */
block|}
return|return
name|DYNAMIC_MIN_VALUE
return|;
block|}
end_function

begin_function
name|gdouble
DECL|function|gimp_paint_options_get_jitter (GimpPaintOptions * paint_options,GimpImage * image)
name|gimp_paint_options_get_jitter
parameter_list|(
name|GimpPaintOptions
modifier|*
name|paint_options
parameter_list|,
name|GimpImage
modifier|*
name|image
parameter_list|)
block|{
name|GimpJitterOptions
modifier|*
name|jitter_options
decl_stmt|;
name|g_return_val_if_fail
argument_list|(
name|GIMP_IS_PAINT_OPTIONS
argument_list|(
name|paint_options
argument_list|)
argument_list|,
literal|0.0
argument_list|)
expr_stmt|;
name|jitter_options
operator|=
name|paint_options
operator|->
name|jitter_options
expr_stmt|;
if|if
condition|(
name|jitter_options
operator|->
name|use_jitter
condition|)
block|{
return|return
name|jitter_options
operator|->
name|jitter_amount
return|;
block|}
return|return
literal|0.0
return|;
block|}
end_function

begin_function
name|gboolean
DECL|function|gimp_paint_options_get_gradient_color (GimpPaintOptions * paint_options,GimpImage * image,gdouble grad_point,gdouble pixel_dist,GimpRGB * color)
name|gimp_paint_options_get_gradient_color
parameter_list|(
name|GimpPaintOptions
modifier|*
name|paint_options
parameter_list|,
name|GimpImage
modifier|*
name|image
parameter_list|,
name|gdouble
name|grad_point
parameter_list|,
name|gdouble
name|pixel_dist
parameter_list|,
name|GimpRGB
modifier|*
name|color
parameter_list|)
block|{
name|GimpGradientOptions
modifier|*
name|gradient_options
decl_stmt|;
name|GimpGradient
modifier|*
name|gradient
decl_stmt|;
name|GimpDynamics
modifier|*
name|dynamics
decl_stmt|;
name|g_return_val_if_fail
argument_list|(
name|GIMP_IS_PAINT_OPTIONS
argument_list|(
name|paint_options
argument_list|)
argument_list|,
name|FALSE
argument_list|)
expr_stmt|;
name|g_return_val_if_fail
argument_list|(
name|GIMP_IS_IMAGE
argument_list|(
name|image
argument_list|)
argument_list|,
name|FALSE
argument_list|)
expr_stmt|;
name|g_return_val_if_fail
argument_list|(
name|color
operator|!=
name|NULL
argument_list|,
name|FALSE
argument_list|)
expr_stmt|;
name|gradient_options
operator|=
name|paint_options
operator|->
name|gradient_options
expr_stmt|;
name|gradient
operator|=
name|gimp_context_get_gradient
argument_list|(
name|GIMP_CONTEXT
argument_list|(
name|paint_options
argument_list|)
argument_list|)
expr_stmt|;
name|dynamics
operator|=
name|gimp_context_get_dynamics
argument_list|(
name|GIMP_CONTEXT
argument_list|(
name|paint_options
argument_list|)
argument_list|)
expr_stmt|;
if|if
condition|(
name|gimp_dynamics_output_is_enabled
argument_list|(
name|dynamics
operator|->
name|color_output
argument_list|)
operator|&&
name|gradient_options
operator|->
name|use_gradient
condition|)
block|{
name|gimp_gradient_get_color_at
argument_list|(
name|gradient
argument_list|,
name|GIMP_CONTEXT
argument_list|(
name|paint_options
argument_list|)
argument_list|,
name|NULL
argument_list|,
name|grad_point
argument_list|,
name|gradient_options
operator|->
name|gradient_reverse
argument_list|,
name|color
argument_list|)
expr_stmt|;
return|return
name|TRUE
return|;
block|}
return|return
name|FALSE
return|;
block|}
end_function

begin_function
name|GimpBrushApplicationMode
DECL|function|gimp_paint_options_get_brush_mode (GimpPaintOptions * paint_options)
name|gimp_paint_options_get_brush_mode
parameter_list|(
name|GimpPaintOptions
modifier|*
name|paint_options
parameter_list|)
block|{
name|GimpDynamics
modifier|*
name|dynamics
decl_stmt|;
name|g_return_val_if_fail
argument_list|(
name|GIMP_IS_PAINT_OPTIONS
argument_list|(
name|paint_options
argument_list|)
argument_list|,
name|GIMP_BRUSH_SOFT
argument_list|)
expr_stmt|;
if|if
condition|(
name|paint_options
operator|->
name|hard
condition|)
return|return
name|GIMP_BRUSH_HARD
return|;
name|dynamics
operator|=
name|gimp_context_get_dynamics
argument_list|(
name|GIMP_CONTEXT
argument_list|(
name|paint_options
argument_list|)
argument_list|)
expr_stmt|;
comment|/*  Im leaving the pressurize code in here, but Im not sure how,  *  or if at all it should be used. Not as hardness anyway.  *   *  if (gimp_dynamics_output_is_enabled(dynamics->hardness_output))  *    return GIMP_BRUSH_PRESSURE; */
return|return
name|GIMP_BRUSH_SOFT
return|;
block|}
end_function

end_unit

