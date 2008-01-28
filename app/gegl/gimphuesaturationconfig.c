begin_unit|revision:0.9.5;language:C;cregit-version:0.0.1
begin_comment
comment|/* GIMP - The GNU Image Manipulation Program  * Copyright (C) 1995 Spencer Kimball and Peter Mattis  *  * gimphuesaturationconfig.c  * Copyright (C) 2007 Michael Natterer<mitch@gimp.org>  *  * This program is free software; you can redistribute it and/or modify  * it under the terms of the GNU General Public License as published by  * the Free Software Foundation; either version 2 of the License, or  * (at your option) any later version.  *  * This program is distributed in the hope that it will be useful,  * but WITHOUT ANY WARRANTY; without even the implied warranty of  * MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the  * GNU General Public License for more details.  *  * You should have received a copy of the GNU General Public License  * along with this program; if not, write to the Free Software  * Foundation, Inc., 59 Temple Place - Suite 330, Boston, MA 02111-1307, USA.  */
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
file|"libgimpconfig/gimpconfig.h"
end_include

begin_include
include|#
directive|include
file|"gegl-types.h"
end_include

begin_comment
comment|/*  temp cruft  */
end_comment

begin_include
include|#
directive|include
file|"base/hue-saturation.h"
end_include

begin_include
include|#
directive|include
file|"gimphuesaturationconfig.h"
end_include

begin_enum
enum|enum
DECL|enum|__anon2ab19f860103
block|{
DECL|enumerator|PROP_0
name|PROP_0
block|,
DECL|enumerator|PROP_RANGE
name|PROP_RANGE
block|,
DECL|enumerator|PROP_HUE
name|PROP_HUE
block|,
DECL|enumerator|PROP_SATURATION
name|PROP_SATURATION
block|,
DECL|enumerator|PROP_LIGHTNESS
name|PROP_LIGHTNESS
block|,
DECL|enumerator|PROP_OVERLAP
name|PROP_OVERLAP
block|}
enum|;
end_enum

begin_function_decl
specifier|static
name|void
name|gimp_hue_saturation_config_iface_init
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
name|gimp_hue_saturation_config_get_property
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
name|gimp_hue_saturation_config_set_property
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
name|gimp_hue_saturation_config_reset
parameter_list|(
name|GimpConfig
modifier|*
name|config
parameter_list|)
function_decl|;
end_function_decl

begin_macro
DECL|function|G_DEFINE_TYPE_WITH_CODE (GimpHueSaturationConfig,gimp_hue_saturation_config,G_TYPE_OBJECT,G_IMPLEMENT_INTERFACE (GIMP_TYPE_CONFIG,gimp_hue_saturation_config_iface_init))
name|G_DEFINE_TYPE_WITH_CODE
argument_list|(
argument|GimpHueSaturationConfig
argument_list|,
argument|gimp_hue_saturation_config
argument_list|,
argument|G_TYPE_OBJECT
argument_list|,
argument|G_IMPLEMENT_INTERFACE (GIMP_TYPE_CONFIG,                                                 gimp_hue_saturation_config_iface_init)
argument_list|)
end_macro

begin_define
DECL|macro|parent_class
define|#
directive|define
name|parent_class
value|gimp_hue_saturation_config_parent_class
end_define

begin_function
specifier|static
name|void
name|gimp_hue_saturation_config_class_init
parameter_list|(
name|GimpHueSaturationConfigClass
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
name|gimp_hue_saturation_config_set_property
expr_stmt|;
name|object_class
operator|->
name|get_property
operator|=
name|gimp_hue_saturation_config_get_property
expr_stmt|;
name|g_object_class_install_property
argument_list|(
name|object_class
argument_list|,
name|PROP_RANGE
argument_list|,
name|g_param_spec_enum
argument_list|(
literal|"range"
argument_list|,
literal|"range"
argument_list|,
literal|"The affected range"
argument_list|,
name|GIMP_TYPE_HUE_RANGE
argument_list|,
name|GIMP_ALL_HUES
argument_list|,
name|G_PARAM_READWRITE
operator||
name|G_PARAM_CONSTRUCT
argument_list|)
argument_list|)
expr_stmt|;
name|g_object_class_install_property
argument_list|(
name|object_class
argument_list|,
name|PROP_HUE
argument_list|,
name|g_param_spec_double
argument_list|(
literal|"hue"
argument_list|,
literal|"Hue"
argument_list|,
literal|"Hue"
argument_list|,
operator|-
literal|1.0
argument_list|,
literal|1.0
argument_list|,
literal|0.0
argument_list|,
name|G_PARAM_READWRITE
operator||
name|G_PARAM_CONSTRUCT
argument_list|)
argument_list|)
expr_stmt|;
name|g_object_class_install_property
argument_list|(
name|object_class
argument_list|,
name|PROP_SATURATION
argument_list|,
name|g_param_spec_double
argument_list|(
literal|"saturation"
argument_list|,
literal|"Saturation"
argument_list|,
literal|"Saturation"
argument_list|,
operator|-
literal|1.0
argument_list|,
literal|1.0
argument_list|,
literal|0.0
argument_list|,
name|G_PARAM_READWRITE
operator||
name|G_PARAM_CONSTRUCT
argument_list|)
argument_list|)
expr_stmt|;
name|g_object_class_install_property
argument_list|(
name|object_class
argument_list|,
name|PROP_LIGHTNESS
argument_list|,
name|g_param_spec_double
argument_list|(
literal|"lightness"
argument_list|,
literal|"Lightness"
argument_list|,
literal|"Lightness"
argument_list|,
operator|-
literal|1.0
argument_list|,
literal|1.0
argument_list|,
literal|0.0
argument_list|,
name|G_PARAM_READWRITE
operator||
name|G_PARAM_CONSTRUCT
argument_list|)
argument_list|)
expr_stmt|;
name|g_object_class_install_property
argument_list|(
name|object_class
argument_list|,
name|PROP_OVERLAP
argument_list|,
name|g_param_spec_double
argument_list|(
literal|"overlap"
argument_list|,
literal|"Overlap"
argument_list|,
literal|"Overlap"
argument_list|,
literal|0.0
argument_list|,
literal|1.0
argument_list|,
literal|0.0
argument_list|,
name|G_PARAM_READWRITE
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
DECL|function|gimp_hue_saturation_config_iface_init (GimpConfigInterface * iface)
name|gimp_hue_saturation_config_iface_init
parameter_list|(
name|GimpConfigInterface
modifier|*
name|iface
parameter_list|)
block|{
name|iface
operator|->
name|reset
operator|=
name|gimp_hue_saturation_config_reset
expr_stmt|;
block|}
end_function

begin_function
specifier|static
name|void
DECL|function|gimp_hue_saturation_config_init (GimpHueSaturationConfig * self)
name|gimp_hue_saturation_config_init
parameter_list|(
name|GimpHueSaturationConfig
modifier|*
name|self
parameter_list|)
block|{
name|gimp_config_reset
argument_list|(
name|GIMP_CONFIG
argument_list|(
name|self
argument_list|)
argument_list|)
expr_stmt|;
block|}
end_function

begin_function
specifier|static
name|void
DECL|function|gimp_hue_saturation_config_get_property (GObject * object,guint property_id,GValue * value,GParamSpec * pspec)
name|gimp_hue_saturation_config_get_property
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
name|GimpHueSaturationConfig
modifier|*
name|self
init|=
name|GIMP_HUE_SATURATION_CONFIG
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
name|PROP_RANGE
case|:
name|g_value_set_enum
argument_list|(
name|value
argument_list|,
name|self
operator|->
name|range
argument_list|)
expr_stmt|;
break|break;
case|case
name|PROP_HUE
case|:
name|g_value_set_double
argument_list|(
name|value
argument_list|,
name|self
operator|->
name|hue
index|[
name|self
operator|->
name|range
index|]
argument_list|)
expr_stmt|;
break|break;
case|case
name|PROP_SATURATION
case|:
name|g_value_set_double
argument_list|(
name|value
argument_list|,
name|self
operator|->
name|saturation
index|[
name|self
operator|->
name|range
index|]
argument_list|)
expr_stmt|;
break|break;
case|case
name|PROP_LIGHTNESS
case|:
name|g_value_set_double
argument_list|(
name|value
argument_list|,
name|self
operator|->
name|lightness
index|[
name|self
operator|->
name|range
index|]
argument_list|)
expr_stmt|;
break|break;
case|case
name|PROP_OVERLAP
case|:
name|g_value_set_double
argument_list|(
name|value
argument_list|,
name|self
operator|->
name|overlap
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
DECL|function|gimp_hue_saturation_config_set_property (GObject * object,guint property_id,const GValue * value,GParamSpec * pspec)
name|gimp_hue_saturation_config_set_property
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
name|GimpHueSaturationConfig
modifier|*
name|self
init|=
name|GIMP_HUE_SATURATION_CONFIG
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
name|PROP_RANGE
case|:
name|self
operator|->
name|range
operator|=
name|g_value_get_enum
argument_list|(
name|value
argument_list|)
expr_stmt|;
break|break;
case|case
name|PROP_HUE
case|:
name|self
operator|->
name|hue
index|[
name|self
operator|->
name|range
index|]
operator|=
name|g_value_get_double
argument_list|(
name|value
argument_list|)
expr_stmt|;
break|break;
case|case
name|PROP_SATURATION
case|:
name|self
operator|->
name|saturation
index|[
name|self
operator|->
name|range
index|]
operator|=
name|g_value_get_double
argument_list|(
name|value
argument_list|)
expr_stmt|;
break|break;
case|case
name|PROP_LIGHTNESS
case|:
name|self
operator|->
name|lightness
index|[
name|self
operator|->
name|range
index|]
operator|=
name|g_value_get_double
argument_list|(
name|value
argument_list|)
expr_stmt|;
break|break;
case|case
name|PROP_OVERLAP
case|:
name|self
operator|->
name|overlap
operator|=
name|g_value_get_double
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
DECL|function|gimp_hue_saturation_config_reset (GimpConfig * config)
name|gimp_hue_saturation_config_reset
parameter_list|(
name|GimpConfig
modifier|*
name|config
parameter_list|)
block|{
name|GimpHueSaturationConfig
modifier|*
name|hs_config
init|=
name|GIMP_HUE_SATURATION_CONFIG
argument_list|(
name|config
argument_list|)
decl_stmt|;
name|GimpHueRange
name|range
decl_stmt|;
name|g_object_freeze_notify
argument_list|(
name|G_OBJECT
argument_list|(
name|config
argument_list|)
argument_list|)
expr_stmt|;
for|for
control|(
name|range
operator|=
name|GIMP_ALL_HUES
init|;
name|range
operator|<=
name|GIMP_MAGENTA_HUES
condition|;
name|range
operator|++
control|)
block|{
name|hs_config
operator|->
name|range
operator|=
name|range
expr_stmt|;
name|gimp_hue_saturation_config_reset_range
argument_list|(
name|hs_config
argument_list|)
expr_stmt|;
block|}
name|gimp_config_reset_property
argument_list|(
name|G_OBJECT
argument_list|(
name|config
argument_list|)
argument_list|,
literal|"range"
argument_list|)
expr_stmt|;
name|gimp_config_reset_property
argument_list|(
name|G_OBJECT
argument_list|(
name|config
argument_list|)
argument_list|,
literal|"overlap"
argument_list|)
expr_stmt|;
name|g_object_thaw_notify
argument_list|(
name|G_OBJECT
argument_list|(
name|config
argument_list|)
argument_list|)
expr_stmt|;
block|}
end_function

begin_comment
comment|/*  public functions  */
end_comment

begin_function
name|void
DECL|function|gimp_hue_saturation_config_reset_range (GimpHueSaturationConfig * config)
name|gimp_hue_saturation_config_reset_range
parameter_list|(
name|GimpHueSaturationConfig
modifier|*
name|config
parameter_list|)
block|{
name|g_return_if_fail
argument_list|(
name|GIMP_IS_HUE_SATURATION_CONFIG
argument_list|(
name|config
argument_list|)
argument_list|)
expr_stmt|;
name|g_object_freeze_notify
argument_list|(
name|G_OBJECT
argument_list|(
name|config
argument_list|)
argument_list|)
expr_stmt|;
name|gimp_config_reset_property
argument_list|(
name|G_OBJECT
argument_list|(
name|config
argument_list|)
argument_list|,
literal|"hue"
argument_list|)
expr_stmt|;
name|gimp_config_reset_property
argument_list|(
name|G_OBJECT
argument_list|(
name|config
argument_list|)
argument_list|,
literal|"saturation"
argument_list|)
expr_stmt|;
name|gimp_config_reset_property
argument_list|(
name|G_OBJECT
argument_list|(
name|config
argument_list|)
argument_list|,
literal|"lightness"
argument_list|)
expr_stmt|;
name|g_object_thaw_notify
argument_list|(
name|G_OBJECT
argument_list|(
name|config
argument_list|)
argument_list|)
expr_stmt|;
block|}
end_function

begin_comment
comment|/*  temp cruft  */
end_comment

begin_function
name|void
DECL|function|gimp_hue_saturation_config_to_cruft (GimpHueSaturationConfig * config,HueSaturation * cruft)
name|gimp_hue_saturation_config_to_cruft
parameter_list|(
name|GimpHueSaturationConfig
modifier|*
name|config
parameter_list|,
name|HueSaturation
modifier|*
name|cruft
parameter_list|)
block|{
name|GimpHueRange
name|range
decl_stmt|;
name|g_return_if_fail
argument_list|(
name|GIMP_IS_HUE_SATURATION_CONFIG
argument_list|(
name|config
argument_list|)
argument_list|)
expr_stmt|;
name|g_return_if_fail
argument_list|(
name|cruft
operator|!=
name|NULL
argument_list|)
expr_stmt|;
for|for
control|(
name|range
operator|=
name|GIMP_ALL_HUES
init|;
name|range
operator|<=
name|GIMP_MAGENTA_HUES
condition|;
name|range
operator|++
control|)
block|{
name|cruft
operator|->
name|hue
index|[
name|range
index|]
operator|=
name|config
operator|->
name|hue
index|[
name|range
index|]
operator|*
literal|180
expr_stmt|;
name|cruft
operator|->
name|saturation
index|[
name|range
index|]
operator|=
name|config
operator|->
name|saturation
index|[
name|range
index|]
operator|*
literal|100
expr_stmt|;
name|cruft
operator|->
name|lightness
index|[
name|range
index|]
operator|=
name|config
operator|->
name|lightness
index|[
name|range
index|]
operator|*
literal|100
expr_stmt|;
block|}
name|cruft
operator|->
name|overlap
operator|=
name|config
operator|->
name|overlap
operator|*
literal|100
expr_stmt|;
name|hue_saturation_calculate_transfers
argument_list|(
name|cruft
argument_list|)
expr_stmt|;
block|}
end_function

end_unit

