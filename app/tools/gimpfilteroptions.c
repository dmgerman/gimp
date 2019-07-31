begin_unit|revision:0.9.5;language:C;cregit-version:0.0.1
begin_comment
comment|/* GIMP - The GNU Image Manipulation Program  * Copyright (C) 1995-2001 Spencer Kimball, Peter Mattis, and others  *  * This program is free software: you can redistribute it and/or modify  * it under the terms of the GNU General Public License as published by  * the Free Software Foundation; either version 3 of the License, or  * (at your option) any later version.  *  * This program is distributed in the hope that it will be useful,  * but WITHOUT ANY WARRANTY; without even the implied warranty of  * MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the  * GNU General Public License for more details.  *  * You should have received a copy of the GNU General Public License  * along with this program.  If not, see<https://www.gnu.org/licenses/>.  */
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
file|"tools-types.h"
end_include

begin_include
include|#
directive|include
file|"gimpfilteroptions.h"
end_include

begin_include
include|#
directive|include
file|"gimp-intl.h"
end_include

begin_enum
enum|enum
DECL|enum|__anon2b9db38d0103
block|{
DECL|enumerator|PROP_0
name|PROP_0
block|,
DECL|enumerator|PROP_PREVIEW
name|PROP_PREVIEW
block|,
DECL|enumerator|PROP_PREVIEW_SPLIT
name|PROP_PREVIEW_SPLIT
block|,
DECL|enumerator|PROP_PREVIEW_ALIGNMENT
name|PROP_PREVIEW_ALIGNMENT
block|,
DECL|enumerator|PROP_PREVIEW_POSITION
name|PROP_PREVIEW_POSITION
block|,
DECL|enumerator|PROP_CONTROLLER
name|PROP_CONTROLLER
block|,
DECL|enumerator|PROP_REGION
name|PROP_REGION
block|,
DECL|enumerator|PROP_GAMMA_HACK
name|PROP_GAMMA_HACK
block|}
enum|;
end_enum

begin_function_decl
specifier|static
name|void
name|gimp_filter_options_set_property
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
name|gimp_filter_options_get_property
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

begin_macro
DECL|function|G_DEFINE_TYPE (GimpFilterOptions,gimp_filter_options,GIMP_TYPE_COLOR_OPTIONS)
name|G_DEFINE_TYPE
argument_list|(
argument|GimpFilterOptions
argument_list|,
argument|gimp_filter_options
argument_list|,
argument|GIMP_TYPE_COLOR_OPTIONS
argument_list|)
end_macro

begin_define
DECL|macro|parent_class
define|#
directive|define
name|parent_class
value|gimp_filter_options_parent_class
end_define

begin_function
specifier|static
name|void
name|gimp_filter_options_class_init
parameter_list|(
name|GimpFilterOptionsClass
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
name|gimp_filter_options_set_property
expr_stmt|;
name|object_class
operator|->
name|get_property
operator|=
name|gimp_filter_options_get_property
expr_stmt|;
name|GIMP_CONFIG_PROP_BOOLEAN
argument_list|(
name|object_class
argument_list|,
name|PROP_PREVIEW
argument_list|,
literal|"preview"
argument_list|,
name|_
argument_list|(
literal|"_Preview"
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
name|PROP_PREVIEW_SPLIT
argument_list|,
name|g_param_spec_boolean
argument_list|(
literal|"preview-split"
argument_list|,
name|_
argument_list|(
literal|"Split _view"
argument_list|)
argument_list|,
name|NULL
argument_list|,
name|FALSE
argument_list|,
name|GIMP_PARAM_READWRITE
operator||
name|G_PARAM_CONSTRUCT
argument_list|)
argument_list|)
expr_stmt|;
name|g_object_class_install_property
argument_list|(
name|object_class
argument_list|,
name|PROP_PREVIEW_ALIGNMENT
argument_list|,
name|g_param_spec_enum
argument_list|(
literal|"preview-alignment"
argument_list|,
name|NULL
argument_list|,
name|NULL
argument_list|,
name|GIMP_TYPE_ALIGNMENT_TYPE
argument_list|,
name|GIMP_ALIGN_LEFT
argument_list|,
name|GIMP_PARAM_READWRITE
operator||
name|G_PARAM_CONSTRUCT
argument_list|)
argument_list|)
expr_stmt|;
name|g_object_class_install_property
argument_list|(
name|object_class
argument_list|,
name|PROP_PREVIEW_POSITION
argument_list|,
name|g_param_spec_double
argument_list|(
literal|"preview-position"
argument_list|,
name|NULL
argument_list|,
name|NULL
argument_list|,
literal|0.0
argument_list|,
literal|1.0
argument_list|,
literal|0.5
argument_list|,
name|GIMP_PARAM_READWRITE
operator||
name|G_PARAM_CONSTRUCT
argument_list|)
argument_list|)
expr_stmt|;
name|GIMP_CONFIG_PROP_BOOLEAN
argument_list|(
name|object_class
argument_list|,
name|PROP_CONTROLLER
argument_list|,
literal|"controller"
argument_list|,
name|_
argument_list|(
literal|"On-canvas con_trols"
argument_list|)
argument_list|,
name|_
argument_list|(
literal|"Show on-canvas filter controls"
argument_list|)
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
name|PROP_REGION
argument_list|,
name|g_param_spec_enum
argument_list|(
literal|"region"
argument_list|,
name|NULL
argument_list|,
name|NULL
argument_list|,
name|GIMP_TYPE_FILTER_REGION
argument_list|,
name|GIMP_FILTER_REGION_SELECTION
argument_list|,
name|GIMP_PARAM_READWRITE
operator||
name|G_PARAM_CONSTRUCT
argument_list|)
argument_list|)
expr_stmt|;
name|g_object_class_install_property
argument_list|(
name|object_class
argument_list|,
name|PROP_GAMMA_HACK
argument_list|,
name|g_param_spec_boolean
argument_list|(
literal|"gamma-hack"
argument_list|,
literal|"Gamma hack (temp hack, please ignore)"
argument_list|,
name|NULL
argument_list|,
name|FALSE
argument_list|,
name|GIMP_PARAM_READWRITE
operator||
name|G_PARAM_CONSTRUCT
argument_list|)
argument_list|)
expr_stmt|;
block|}
end_function

begin_function
specifier|static
name|void
DECL|function|gimp_filter_options_init (GimpFilterOptions * options)
name|gimp_filter_options_init
parameter_list|(
name|GimpFilterOptions
modifier|*
name|options
parameter_list|)
block|{ }
end_function

begin_function
specifier|static
name|void
DECL|function|gimp_filter_options_set_property (GObject * object,guint property_id,const GValue * value,GParamSpec * pspec)
name|gimp_filter_options_set_property
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
name|GimpFilterOptions
modifier|*
name|options
init|=
name|GIMP_FILTER_OPTIONS
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
name|PROP_PREVIEW
case|:
name|options
operator|->
name|preview
operator|=
name|g_value_get_boolean
argument_list|(
name|value
argument_list|)
expr_stmt|;
break|break;
case|case
name|PROP_PREVIEW_SPLIT
case|:
name|options
operator|->
name|preview_split
operator|=
name|g_value_get_boolean
argument_list|(
name|value
argument_list|)
expr_stmt|;
break|break;
case|case
name|PROP_PREVIEW_ALIGNMENT
case|:
name|options
operator|->
name|preview_alignment
operator|=
name|g_value_get_enum
argument_list|(
name|value
argument_list|)
expr_stmt|;
break|break;
case|case
name|PROP_PREVIEW_POSITION
case|:
name|options
operator|->
name|preview_position
operator|=
name|g_value_get_double
argument_list|(
name|value
argument_list|)
expr_stmt|;
break|break;
case|case
name|PROP_CONTROLLER
case|:
name|options
operator|->
name|controller
operator|=
name|g_value_get_boolean
argument_list|(
name|value
argument_list|)
expr_stmt|;
break|break;
case|case
name|PROP_REGION
case|:
name|options
operator|->
name|region
operator|=
name|g_value_get_enum
argument_list|(
name|value
argument_list|)
expr_stmt|;
break|break;
case|case
name|PROP_GAMMA_HACK
case|:
name|options
operator|->
name|gamma_hack
operator|=
name|g_value_get_boolean
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
DECL|function|gimp_filter_options_get_property (GObject * object,guint property_id,GValue * value,GParamSpec * pspec)
name|gimp_filter_options_get_property
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
name|GimpFilterOptions
modifier|*
name|options
init|=
name|GIMP_FILTER_OPTIONS
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
name|PROP_PREVIEW
case|:
name|g_value_set_boolean
argument_list|(
name|value
argument_list|,
name|options
operator|->
name|preview
argument_list|)
expr_stmt|;
break|break;
case|case
name|PROP_PREVIEW_SPLIT
case|:
name|g_value_set_boolean
argument_list|(
name|value
argument_list|,
name|options
operator|->
name|preview_split
argument_list|)
expr_stmt|;
break|break;
case|case
name|PROP_PREVIEW_ALIGNMENT
case|:
name|g_value_set_enum
argument_list|(
name|value
argument_list|,
name|options
operator|->
name|preview_alignment
argument_list|)
expr_stmt|;
break|break;
case|case
name|PROP_PREVIEW_POSITION
case|:
name|g_value_set_double
argument_list|(
name|value
argument_list|,
name|options
operator|->
name|preview_position
argument_list|)
expr_stmt|;
break|break;
case|case
name|PROP_CONTROLLER
case|:
name|g_value_set_boolean
argument_list|(
name|value
argument_list|,
name|options
operator|->
name|controller
argument_list|)
expr_stmt|;
break|break;
case|case
name|PROP_REGION
case|:
name|g_value_set_enum
argument_list|(
name|value
argument_list|,
name|options
operator|->
name|region
argument_list|)
expr_stmt|;
break|break;
case|case
name|PROP_GAMMA_HACK
case|:
name|g_value_set_boolean
argument_list|(
name|value
argument_list|,
name|options
operator|->
name|gamma_hack
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
name|void
DECL|function|gimp_filter_options_switch_preview_side (GimpFilterOptions * options)
name|gimp_filter_options_switch_preview_side
parameter_list|(
name|GimpFilterOptions
modifier|*
name|options
parameter_list|)
block|{
name|GimpAlignmentType
name|alignment
decl_stmt|;
name|g_return_if_fail
argument_list|(
name|GIMP_IS_FILTER_OPTIONS
argument_list|(
name|options
argument_list|)
argument_list|)
expr_stmt|;
switch|switch
condition|(
name|options
operator|->
name|preview_alignment
condition|)
block|{
case|case
name|GIMP_ALIGN_LEFT
case|:
name|alignment
operator|=
name|GIMP_ALIGN_RIGHT
expr_stmt|;
break|break;
case|case
name|GIMP_ALIGN_RIGHT
case|:
name|alignment
operator|=
name|GIMP_ALIGN_LEFT
expr_stmt|;
break|break;
case|case
name|GIMP_ALIGN_TOP
case|:
name|alignment
operator|=
name|GIMP_ALIGN_BOTTOM
expr_stmt|;
break|break;
case|case
name|GIMP_ALIGN_BOTTOM
case|:
name|alignment
operator|=
name|GIMP_ALIGN_TOP
expr_stmt|;
break|break;
default|default:
name|g_return_if_reached
argument_list|()
expr_stmt|;
block|}
name|g_object_set
argument_list|(
name|options
argument_list|,
literal|"preview-alignment"
argument_list|,
name|alignment
argument_list|,
name|NULL
argument_list|)
expr_stmt|;
block|}
end_function

begin_function
name|void
DECL|function|gimp_filter_options_switch_preview_orientation (GimpFilterOptions * options,gdouble position_x,gdouble position_y)
name|gimp_filter_options_switch_preview_orientation
parameter_list|(
name|GimpFilterOptions
modifier|*
name|options
parameter_list|,
name|gdouble
name|position_x
parameter_list|,
name|gdouble
name|position_y
parameter_list|)
block|{
name|GimpAlignmentType
name|alignment
decl_stmt|;
name|gdouble
name|position
decl_stmt|;
name|g_return_if_fail
argument_list|(
name|GIMP_IS_FILTER_OPTIONS
argument_list|(
name|options
argument_list|)
argument_list|)
expr_stmt|;
switch|switch
condition|(
name|options
operator|->
name|preview_alignment
condition|)
block|{
case|case
name|GIMP_ALIGN_LEFT
case|:
name|alignment
operator|=
name|GIMP_ALIGN_TOP
expr_stmt|;
break|break;
case|case
name|GIMP_ALIGN_RIGHT
case|:
name|alignment
operator|=
name|GIMP_ALIGN_BOTTOM
expr_stmt|;
break|break;
case|case
name|GIMP_ALIGN_TOP
case|:
name|alignment
operator|=
name|GIMP_ALIGN_LEFT
expr_stmt|;
break|break;
case|case
name|GIMP_ALIGN_BOTTOM
case|:
name|alignment
operator|=
name|GIMP_ALIGN_RIGHT
expr_stmt|;
break|break;
default|default:
name|g_return_if_reached
argument_list|()
expr_stmt|;
block|}
if|if
condition|(
name|alignment
operator|==
name|GIMP_ALIGN_LEFT
operator|||
name|alignment
operator|==
name|GIMP_ALIGN_RIGHT
condition|)
block|{
name|position
operator|=
name|position_x
expr_stmt|;
block|}
else|else
block|{
name|position
operator|=
name|position_y
expr_stmt|;
block|}
name|g_object_set
argument_list|(
name|options
argument_list|,
literal|"preview-alignment"
argument_list|,
name|alignment
argument_list|,
literal|"preview-position"
argument_list|,
name|CLAMP
argument_list|(
name|position
argument_list|,
literal|0.0
argument_list|,
literal|1.0
argument_list|)
argument_list|,
name|NULL
argument_list|)
expr_stmt|;
block|}
end_function

end_unit

