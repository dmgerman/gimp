begin_unit|revision:0.9.5;language:C;cregit-version:0.0.1
begin_comment
comment|/* GIMP - The GNU Image Manipulation Program  * Copyright (C) 1995 Spencer Kimball and Peter Mattis  *  * gimpcurvesconfig.c  * Copyright (C) 2007 Michael Natterer<mitch@gimp.org>  *  * This program is free software; you can redistribute it and/or modify  * it under the terms of the GNU General Public License as published by  * the Free Software Foundation; either version 2 of the License, or  * (at your option) any later version.  *  * This program is distributed in the hope that it will be useful,  * but WITHOUT ANY WARRANTY; without even the implied warranty of  * MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the  * GNU General Public License for more details.  *  * You should have received a copy of the GNU General Public License  * along with this program; if not, write to the Free Software  * Foundation, Inc., 59 Temple Place - Suite 330, Boston, MA 02111-1307, USA.  */
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
file|"gegl-types.h"
end_include

begin_include
include|#
directive|include
file|"base/gimphistogram.h"
end_include

begin_comment
comment|/*  temp cruft  */
end_comment

begin_include
include|#
directive|include
file|"base/curves.h"
end_include

begin_include
include|#
directive|include
file|"gimpcurvesconfig.h"
end_include

begin_include
include|#
directive|include
file|"gimp-intl.h"
end_include

begin_enum
enum|enum
DECL|enum|__anon2c62b7200103
block|{
DECL|enumerator|PROP_0
name|PROP_0
block|,
DECL|enumerator|PROP_CHANNEL
name|PROP_CHANNEL
block|,
DECL|enumerator|PROP_CURVE
name|PROP_CURVE
block|}
enum|;
end_enum

begin_function_decl
specifier|static
name|void
name|gimp_curves_config_finalize
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
name|gimp_curves_config_get_property
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
name|gimp_curves_config_set_property
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

begin_macro
DECL|function|G_DEFINE_TYPE (GimpCurvesConfig,gimp_curves_config,G_TYPE_OBJECT)
name|G_DEFINE_TYPE
argument_list|(
argument|GimpCurvesConfig
argument_list|,
argument|gimp_curves_config
argument_list|,
argument|G_TYPE_OBJECT
argument_list|)
end_macro

begin_define
DECL|macro|parent_class
define|#
directive|define
name|parent_class
value|gimp_curves_config_parent_class
end_define

begin_function
specifier|static
name|void
name|gimp_curves_config_class_init
parameter_list|(
name|GimpCurvesConfigClass
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
name|gimp_curves_config_finalize
expr_stmt|;
name|object_class
operator|->
name|set_property
operator|=
name|gimp_curves_config_set_property
expr_stmt|;
name|object_class
operator|->
name|get_property
operator|=
name|gimp_curves_config_get_property
expr_stmt|;
name|g_object_class_install_property
argument_list|(
name|object_class
argument_list|,
name|PROP_CHANNEL
argument_list|,
name|g_param_spec_enum
argument_list|(
literal|"channel"
argument_list|,
literal|"Channel"
argument_list|,
literal|"The affected channel"
argument_list|,
name|GIMP_TYPE_HISTOGRAM_CHANNEL
argument_list|,
name|GIMP_HISTOGRAM_VALUE
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
name|PROP_CURVE
argument_list|,
name|g_param_spec_object
argument_list|(
literal|"curve"
argument_list|,
literal|"Curve"
argument_list|,
literal|"Curve"
argument_list|,
name|GIMP_TYPE_CURVE
argument_list|,
name|G_PARAM_READWRITE
argument_list|)
argument_list|)
expr_stmt|;
block|}
end_function

begin_function
specifier|static
name|void
DECL|function|gimp_curves_config_init (GimpCurvesConfig * self)
name|gimp_curves_config_init
parameter_list|(
name|GimpCurvesConfig
modifier|*
name|self
parameter_list|)
block|{
name|GimpHistogramChannel
name|channel
decl_stmt|;
for|for
control|(
name|channel
operator|=
name|GIMP_HISTOGRAM_VALUE
init|;
name|channel
operator|<=
name|GIMP_HISTOGRAM_ALPHA
condition|;
name|channel
operator|++
control|)
block|{
name|self
operator|->
name|curve
index|[
name|channel
index|]
operator|=
name|GIMP_CURVE
argument_list|(
name|gimp_curve_new
argument_list|(
literal|"curves config"
argument_list|)
argument_list|)
expr_stmt|;
block|}
name|gimp_curves_config_reset
argument_list|(
name|self
argument_list|)
expr_stmt|;
block|}
end_function

begin_function
specifier|static
name|void
DECL|function|gimp_curves_config_finalize (GObject * object)
name|gimp_curves_config_finalize
parameter_list|(
name|GObject
modifier|*
name|object
parameter_list|)
block|{
name|GimpCurvesConfig
modifier|*
name|self
init|=
name|GIMP_CURVES_CONFIG
argument_list|(
name|object
argument_list|)
decl_stmt|;
name|GimpHistogramChannel
name|channel
decl_stmt|;
for|for
control|(
name|channel
operator|=
name|GIMP_HISTOGRAM_VALUE
init|;
name|channel
operator|<=
name|GIMP_HISTOGRAM_ALPHA
condition|;
name|channel
operator|++
control|)
block|{
if|if
condition|(
name|self
operator|->
name|curve
index|[
name|channel
index|]
condition|)
block|{
name|g_object_unref
argument_list|(
name|self
operator|->
name|curve
index|[
name|channel
index|]
argument_list|)
expr_stmt|;
name|self
operator|->
name|curve
index|[
name|channel
index|]
operator|=
name|NULL
expr_stmt|;
block|}
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
DECL|function|gimp_curves_config_get_property (GObject * object,guint property_id,GValue * value,GParamSpec * pspec)
name|gimp_curves_config_get_property
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
name|GimpCurvesConfig
modifier|*
name|self
init|=
name|GIMP_CURVES_CONFIG
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
name|PROP_CHANNEL
case|:
name|g_value_set_enum
argument_list|(
name|value
argument_list|,
name|self
operator|->
name|channel
argument_list|)
expr_stmt|;
break|break;
case|case
name|PROP_CURVE
case|:
name|g_value_set_object
argument_list|(
name|value
argument_list|,
name|self
operator|->
name|curve
index|[
name|self
operator|->
name|channel
index|]
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
DECL|function|gimp_curves_config_set_property (GObject * object,guint property_id,const GValue * value,GParamSpec * pspec)
name|gimp_curves_config_set_property
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
name|GimpCurvesConfig
modifier|*
name|self
init|=
name|GIMP_CURVES_CONFIG
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
name|PROP_CHANNEL
case|:
name|self
operator|->
name|channel
operator|=
name|g_value_get_enum
argument_list|(
name|value
argument_list|)
expr_stmt|;
break|break;
case|case
name|PROP_CURVE
case|:
if|if
condition|(
name|self
operator|->
name|curve
index|[
name|self
operator|->
name|channel
index|]
condition|)
name|g_object_unref
argument_list|(
name|self
operator|->
name|curve
index|[
name|self
operator|->
name|channel
index|]
argument_list|)
expr_stmt|;
name|self
operator|->
name|curve
index|[
name|self
operator|->
name|channel
index|]
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

begin_comment
comment|/*  public functions  */
end_comment

begin_function
name|void
DECL|function|gimp_curves_config_reset (GimpCurvesConfig * config)
name|gimp_curves_config_reset
parameter_list|(
name|GimpCurvesConfig
modifier|*
name|config
parameter_list|)
block|{
name|GimpHistogramChannel
name|channel
decl_stmt|;
name|g_return_if_fail
argument_list|(
name|GIMP_IS_CURVES_CONFIG
argument_list|(
name|config
argument_list|)
argument_list|)
expr_stmt|;
name|config
operator|->
name|channel
operator|=
name|GIMP_HISTOGRAM_VALUE
expr_stmt|;
for|for
control|(
name|channel
operator|=
name|GIMP_HISTOGRAM_VALUE
init|;
name|channel
operator|<=
name|GIMP_HISTOGRAM_ALPHA
condition|;
name|channel
operator|++
control|)
block|{
name|gimp_curve_reset
argument_list|(
name|config
operator|->
name|curve
index|[
name|channel
index|]
argument_list|,
name|FALSE
argument_list|)
expr_stmt|;
block|}
block|}
end_function

begin_function
name|void
DECL|function|gimp_curves_config_reset_channel (GimpCurvesConfig * config,GimpHistogramChannel channel)
name|gimp_curves_config_reset_channel
parameter_list|(
name|GimpCurvesConfig
modifier|*
name|config
parameter_list|,
name|GimpHistogramChannel
name|channel
parameter_list|)
block|{
name|g_return_if_fail
argument_list|(
name|GIMP_IS_CURVES_CONFIG
argument_list|(
name|config
argument_list|)
argument_list|)
expr_stmt|;
name|gimp_curve_reset
argument_list|(
name|config
operator|->
name|curve
index|[
name|channel
index|]
argument_list|,
name|FALSE
argument_list|)
expr_stmt|;
block|}
end_function

begin_function
name|gboolean
DECL|function|gimp_curves_config_load_cruft (GimpCurvesConfig * config,gpointer fp,GError ** error)
name|gimp_curves_config_load_cruft
parameter_list|(
name|GimpCurvesConfig
modifier|*
name|config
parameter_list|,
name|gpointer
name|fp
parameter_list|,
name|GError
modifier|*
modifier|*
name|error
parameter_list|)
block|{
name|FILE
modifier|*
name|file
init|=
name|fp
decl_stmt|;
name|gint
name|i
decl_stmt|,
name|j
decl_stmt|;
name|gint
name|fields
decl_stmt|;
name|gchar
name|buf
index|[
literal|50
index|]
decl_stmt|;
name|gint
name|index
index|[
literal|5
index|]
index|[
name|GIMP_CURVE_NUM_POINTS
index|]
decl_stmt|;
name|gint
name|value
index|[
literal|5
index|]
index|[
name|GIMP_CURVE_NUM_POINTS
index|]
decl_stmt|;
name|g_return_val_if_fail
argument_list|(
name|GIMP_IS_CURVES_CONFIG
argument_list|(
name|config
argument_list|)
argument_list|,
name|FALSE
argument_list|)
expr_stmt|;
name|g_return_val_if_fail
argument_list|(
name|file
operator|!=
name|NULL
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
if|if
condition|(
operator|!
name|fgets
argument_list|(
name|buf
argument_list|,
sizeof|sizeof
argument_list|(
name|buf
argument_list|)
argument_list|,
name|file
argument_list|)
operator|||
name|strcmp
argument_list|(
name|buf
argument_list|,
literal|"# GIMP Curves File\n"
argument_list|)
operator|!=
literal|0
condition|)
block|{
name|g_set_error
argument_list|(
name|error
argument_list|,
name|GIMP_CONFIG_ERROR
argument_list|,
name|GIMP_CONFIG_ERROR_PARSE
argument_list|,
name|_
argument_list|(
literal|"not a GIMP Curves file"
argument_list|)
argument_list|)
expr_stmt|;
return|return
name|FALSE
return|;
block|}
for|for
control|(
name|i
operator|=
literal|0
init|;
name|i
operator|<
literal|5
condition|;
name|i
operator|++
control|)
block|{
for|for
control|(
name|j
operator|=
literal|0
init|;
name|j
operator|<
name|GIMP_CURVE_NUM_POINTS
condition|;
name|j
operator|++
control|)
block|{
name|fields
operator|=
name|fscanf
argument_list|(
name|file
argument_list|,
literal|"%d %d "
argument_list|,
operator|&
name|index
index|[
name|i
index|]
index|[
name|j
index|]
argument_list|,
operator|&
name|value
index|[
name|i
index|]
index|[
name|j
index|]
argument_list|)
expr_stmt|;
if|if
condition|(
name|fields
operator|!=
literal|2
condition|)
block|{
comment|/*  FIXME: should have a helpful error message here  */
name|g_printerr
argument_list|(
literal|"fields != 2"
argument_list|)
expr_stmt|;
name|g_set_error
argument_list|(
name|error
argument_list|,
name|GIMP_CONFIG_ERROR
argument_list|,
name|GIMP_CONFIG_ERROR_PARSE
argument_list|,
name|_
argument_list|(
literal|"parse error"
argument_list|)
argument_list|)
expr_stmt|;
return|return
name|FALSE
return|;
block|}
block|}
block|}
for|for
control|(
name|i
operator|=
literal|0
init|;
name|i
operator|<
literal|5
condition|;
name|i
operator|++
control|)
block|{
name|GimpCurve
modifier|*
name|curve
init|=
name|config
operator|->
name|curve
index|[
name|i
index|]
decl_stmt|;
name|gimp_data_freeze
argument_list|(
name|GIMP_DATA
argument_list|(
name|curve
argument_list|)
argument_list|)
expr_stmt|;
name|gimp_curve_set_curve_type
argument_list|(
name|curve
argument_list|,
name|GIMP_CURVE_SMOOTH
argument_list|)
expr_stmt|;
for|for
control|(
name|j
operator|=
literal|0
init|;
name|j
operator|<
name|GIMP_CURVE_NUM_POINTS
condition|;
name|j
operator|++
control|)
name|gimp_curve_set_point
argument_list|(
name|curve
argument_list|,
name|j
argument_list|,
name|index
index|[
name|i
index|]
index|[
name|j
index|]
argument_list|,
name|value
index|[
name|i
index|]
index|[
name|j
index|]
argument_list|)
expr_stmt|;
name|gimp_data_thaw
argument_list|(
name|GIMP_DATA
argument_list|(
name|curve
argument_list|)
argument_list|)
expr_stmt|;
block|}
return|return
name|TRUE
return|;
block|}
end_function

begin_function
name|gboolean
DECL|function|gimp_curves_config_save_cruft (GimpCurvesConfig * config,gpointer fp)
name|gimp_curves_config_save_cruft
parameter_list|(
name|GimpCurvesConfig
modifier|*
name|config
parameter_list|,
name|gpointer
name|fp
parameter_list|)
block|{
name|FILE
modifier|*
name|file
init|=
name|fp
decl_stmt|;
name|gint
name|i
decl_stmt|,
name|j
decl_stmt|;
name|gint32
name|index
decl_stmt|;
name|g_return_val_if_fail
argument_list|(
name|GIMP_IS_CURVES_CONFIG
argument_list|(
name|config
argument_list|)
argument_list|,
name|FALSE
argument_list|)
expr_stmt|;
name|g_return_val_if_fail
argument_list|(
name|file
operator|!=
name|NULL
argument_list|,
name|FALSE
argument_list|)
expr_stmt|;
name|fprintf
argument_list|(
name|file
argument_list|,
literal|"# GIMP Curves File\n"
argument_list|)
expr_stmt|;
for|for
control|(
name|i
operator|=
literal|0
init|;
name|i
operator|<
literal|5
condition|;
name|i
operator|++
control|)
block|{
name|GimpCurve
modifier|*
name|curve
init|=
name|config
operator|->
name|curve
index|[
name|i
index|]
decl_stmt|;
if|if
condition|(
name|curve
operator|->
name|curve_type
operator|==
name|GIMP_CURVE_FREE
condition|)
block|{
comment|/* pick representative points from the curve and make them            * control points            */
for|for
control|(
name|j
operator|=
literal|0
init|;
name|j
operator|<=
literal|8
condition|;
name|j
operator|++
control|)
block|{
name|index
operator|=
name|CLAMP0255
argument_list|(
name|j
operator|*
literal|32
argument_list|)
expr_stmt|;
name|curve
operator|->
name|points
index|[
name|j
operator|*
literal|2
index|]
index|[
literal|0
index|]
operator|=
name|index
expr_stmt|;
name|curve
operator|->
name|points
index|[
name|j
operator|*
literal|2
index|]
index|[
literal|1
index|]
operator|=
name|curve
operator|->
name|curve
index|[
name|index
index|]
expr_stmt|;
block|}
block|}
for|for
control|(
name|j
operator|=
literal|0
init|;
name|j
operator|<
name|GIMP_CURVE_NUM_POINTS
condition|;
name|j
operator|++
control|)
name|fprintf
argument_list|(
name|file
argument_list|,
literal|"%d %d "
argument_list|,
name|curve
operator|->
name|points
index|[
name|j
index|]
index|[
literal|0
index|]
argument_list|,
name|curve
operator|->
name|points
index|[
name|j
index|]
index|[
literal|1
index|]
argument_list|)
expr_stmt|;
name|fprintf
argument_list|(
name|file
argument_list|,
literal|"\n"
argument_list|)
expr_stmt|;
block|}
return|return
name|TRUE
return|;
block|}
end_function

begin_comment
comment|/*  temp cruft  */
end_comment

begin_function
name|void
DECL|function|gimp_curves_config_to_cruft (GimpCurvesConfig * config,Curves * cruft,gboolean is_color)
name|gimp_curves_config_to_cruft
parameter_list|(
name|GimpCurvesConfig
modifier|*
name|config
parameter_list|,
name|Curves
modifier|*
name|cruft
parameter_list|,
name|gboolean
name|is_color
parameter_list|)
block|{
name|GimpHistogramChannel
name|channel
decl_stmt|;
name|g_return_if_fail
argument_list|(
name|GIMP_IS_CURVES_CONFIG
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
name|channel
operator|=
name|GIMP_HISTOGRAM_VALUE
init|;
name|channel
operator|<=
name|GIMP_HISTOGRAM_ALPHA
condition|;
name|channel
operator|++
control|)
block|{
name|gimp_curve_get_uchar
argument_list|(
name|config
operator|->
name|curve
index|[
name|channel
index|]
argument_list|,
name|cruft
operator|->
name|curve
index|[
name|channel
index|]
argument_list|)
expr_stmt|;
block|}
if|if
condition|(
operator|!
name|is_color
condition|)
block|{
name|gimp_curve_get_uchar
argument_list|(
name|config
operator|->
name|curve
index|[
name|GIMP_HISTOGRAM_ALPHA
index|]
argument_list|,
name|cruft
operator|->
name|curve
index|[
literal|1
index|]
argument_list|)
expr_stmt|;
block|}
block|}
end_function

end_unit

