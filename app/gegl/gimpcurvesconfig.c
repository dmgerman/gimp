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
file|<glib/gstdio.h>
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
file|"core/gimpcurve.h"
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
DECL|enum|__anon29200ee50103
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
name|gimp_curves_config_iface_init
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

begin_function_decl
specifier|static
name|gboolean
name|gimp_curves_config_equal
parameter_list|(
name|GimpConfig
modifier|*
name|a
parameter_list|,
name|GimpConfig
modifier|*
name|b
parameter_list|)
function_decl|;
end_function_decl

begin_function_decl
specifier|static
name|void
name|gimp_curves_config_reset
parameter_list|(
name|GimpConfig
modifier|*
name|config
parameter_list|)
function_decl|;
end_function_decl

begin_function_decl
specifier|static
name|gboolean
name|gimp_curves_config_copy
parameter_list|(
name|GimpConfig
modifier|*
name|src
parameter_list|,
name|GimpConfig
modifier|*
name|dest
parameter_list|,
name|GParamFlags
name|flags
parameter_list|)
function_decl|;
end_function_decl

begin_function_decl
specifier|static
name|void
name|gimp_curves_config_curve_dirty
parameter_list|(
name|GimpCurve
modifier|*
name|curve
parameter_list|,
name|GimpCurvesConfig
modifier|*
name|config
parameter_list|)
function_decl|;
end_function_decl

begin_macro
DECL|function|G_DEFINE_TYPE_WITH_CODE (GimpCurvesConfig,gimp_curves_config,GIMP_TYPE_VIEWABLE,G_IMPLEMENT_INTERFACE (GIMP_TYPE_CONFIG,gimp_curves_config_iface_init))
name|G_DEFINE_TYPE_WITH_CODE
argument_list|(
argument|GimpCurvesConfig
argument_list|,
argument|gimp_curves_config
argument_list|,
argument|GIMP_TYPE_VIEWABLE
argument_list|,
argument|G_IMPLEMENT_INTERFACE (GIMP_TYPE_CONFIG,                                                 gimp_curves_config_iface_init)
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
name|viewable_class
operator|->
name|default_stock_id
operator|=
literal|"gimp-tool-curves"
expr_stmt|;
name|GIMP_CONFIG_INSTALL_PROP_ENUM
argument_list|(
name|object_class
argument_list|,
name|PROP_CHANNEL
argument_list|,
literal|"channel"
argument_list|,
literal|"The affected channel"
argument_list|,
name|GIMP_TYPE_HISTOGRAM_CHANNEL
argument_list|,
name|GIMP_HISTOGRAM_VALUE
argument_list|,
literal|0
argument_list|)
expr_stmt|;
name|GIMP_CONFIG_INSTALL_PROP_OBJECT
argument_list|(
name|object_class
argument_list|,
name|PROP_CURVE
argument_list|,
literal|"curve"
argument_list|,
literal|"Curve"
argument_list|,
name|GIMP_TYPE_CURVE
argument_list|,
name|GIMP_CONFIG_PARAM_AGGREGATE
argument_list|)
expr_stmt|;
block|}
end_function

begin_function
specifier|static
name|void
DECL|function|gimp_curves_config_iface_init (GimpConfigInterface * iface)
name|gimp_curves_config_iface_init
parameter_list|(
name|GimpConfigInterface
modifier|*
name|iface
parameter_list|)
block|{
name|iface
operator|->
name|equal
operator|=
name|gimp_curves_config_equal
expr_stmt|;
name|iface
operator|->
name|reset
operator|=
name|gimp_curves_config_reset
expr_stmt|;
name|iface
operator|->
name|copy
operator|=
name|gimp_curves_config_copy
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
name|g_signal_connect_object
argument_list|(
name|self
operator|->
name|curve
index|[
name|channel
index|]
argument_list|,
literal|"dirty"
argument_list|,
name|G_CALLBACK
argument_list|(
name|gimp_curves_config_curve_dirty
argument_list|)
argument_list|,
name|self
argument_list|,
literal|0
argument_list|)
expr_stmt|;
block|}
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
name|g_object_notify
argument_list|(
name|object
argument_list|,
literal|"curve"
argument_list|)
expr_stmt|;
break|break;
case|case
name|PROP_CURVE
case|:
block|{
name|GimpCurve
modifier|*
name|src_curve
init|=
name|g_value_get_object
argument_list|(
name|value
argument_list|)
decl_stmt|;
name|GimpCurve
modifier|*
name|dest_curve
init|=
name|self
operator|->
name|curve
index|[
name|self
operator|->
name|channel
index|]
decl_stmt|;
if|if
condition|(
name|src_curve
operator|&&
name|dest_curve
condition|)
block|{
name|gimp_config_sync
argument_list|(
name|G_OBJECT
argument_list|(
name|src_curve
argument_list|)
argument_list|,
name|G_OBJECT
argument_list|(
name|dest_curve
argument_list|)
argument_list|,
literal|0
argument_list|)
expr_stmt|;
name|memcpy
argument_list|(
name|dest_curve
operator|->
name|points
argument_list|,
name|src_curve
operator|->
name|points
argument_list|,
sizeof|sizeof
argument_list|(
name|GimpVector2
argument_list|)
operator|*
name|src_curve
operator|->
name|n_points
argument_list|)
expr_stmt|;
name|memcpy
argument_list|(
name|dest_curve
operator|->
name|samples
argument_list|,
name|src_curve
operator|->
name|samples
argument_list|,
sizeof|sizeof
argument_list|(
name|gdouble
argument_list|)
operator|*
name|src_curve
operator|->
name|n_samples
argument_list|)
expr_stmt|;
name|dest_curve
operator|->
name|identity
operator|=
name|src_curve
operator|->
name|identity
expr_stmt|;
block|}
block|}
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
DECL|function|gimp_curves_config_equal (GimpConfig * a,GimpConfig * b)
name|gimp_curves_config_equal
parameter_list|(
name|GimpConfig
modifier|*
name|a
parameter_list|,
name|GimpConfig
modifier|*
name|b
parameter_list|)
block|{
name|GimpCurvesConfig
modifier|*
name|a_config
init|=
name|GIMP_CURVES_CONFIG
argument_list|(
name|a
argument_list|)
decl_stmt|;
name|GimpCurvesConfig
modifier|*
name|b_config
init|=
name|GIMP_CURVES_CONFIG
argument_list|(
name|b
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
name|GimpCurve
modifier|*
name|a_curve
init|=
name|a_config
operator|->
name|curve
index|[
name|channel
index|]
decl_stmt|;
name|GimpCurve
modifier|*
name|b_curve
init|=
name|b_config
operator|->
name|curve
index|[
name|channel
index|]
decl_stmt|;
if|if
condition|(
name|a_curve
operator|&&
name|b_curve
condition|)
block|{
if|if
condition|(
name|a_curve
operator|->
name|curve_type
operator|!=
name|b_curve
operator|->
name|curve_type
condition|)
return|return
name|FALSE
return|;
if|if
condition|(
name|memcmp
argument_list|(
name|a_curve
operator|->
name|points
argument_list|,
name|b_curve
operator|->
name|points
argument_list|,
sizeof|sizeof
argument_list|(
name|GimpVector2
argument_list|)
operator|*
name|b_curve
operator|->
name|n_points
argument_list|)
operator|||
name|memcmp
argument_list|(
name|a_curve
operator|->
name|samples
argument_list|,
name|b_curve
operator|->
name|samples
argument_list|,
sizeof|sizeof
argument_list|(
name|gdouble
argument_list|)
operator|*
name|b_curve
operator|->
name|n_samples
argument_list|)
condition|)
return|return
name|FALSE
return|;
block|}
elseif|else
if|if
condition|(
name|a_curve
operator|||
name|b_curve
condition|)
block|{
return|return
name|FALSE
return|;
block|}
block|}
comment|/* don't compare "channel" */
return|return
name|TRUE
return|;
block|}
end_function

begin_function
specifier|static
name|void
DECL|function|gimp_curves_config_reset (GimpConfig * config)
name|gimp_curves_config_reset
parameter_list|(
name|GimpConfig
modifier|*
name|config
parameter_list|)
block|{
name|GimpCurvesConfig
modifier|*
name|c_config
init|=
name|GIMP_CURVES_CONFIG
argument_list|(
name|config
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
name|c_config
operator|->
name|channel
operator|=
name|channel
expr_stmt|;
name|gimp_curves_config_reset_channel
argument_list|(
name|c_config
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
literal|"channel"
argument_list|)
expr_stmt|;
block|}
end_function

begin_function
specifier|static
name|gboolean
DECL|function|gimp_curves_config_copy (GimpConfig * src,GimpConfig * dest,GParamFlags flags)
name|gimp_curves_config_copy
parameter_list|(
name|GimpConfig
modifier|*
name|src
parameter_list|,
name|GimpConfig
modifier|*
name|dest
parameter_list|,
name|GParamFlags
name|flags
parameter_list|)
block|{
name|GimpCurvesConfig
modifier|*
name|src_config
init|=
name|GIMP_CURVES_CONFIG
argument_list|(
name|src
argument_list|)
decl_stmt|;
name|GimpCurvesConfig
modifier|*
name|dest_config
init|=
name|GIMP_CURVES_CONFIG
argument_list|(
name|dest
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
name|GimpCurve
modifier|*
name|src_curve
init|=
name|src_config
operator|->
name|curve
index|[
name|channel
index|]
decl_stmt|;
name|GimpCurve
modifier|*
name|dest_curve
init|=
name|dest_config
operator|->
name|curve
index|[
name|channel
index|]
decl_stmt|;
if|if
condition|(
name|src_curve
operator|&&
name|dest_curve
condition|)
block|{
name|gimp_config_sync
argument_list|(
name|G_OBJECT
argument_list|(
name|src_curve
argument_list|)
argument_list|,
name|G_OBJECT
argument_list|(
name|dest_curve
argument_list|)
argument_list|,
literal|0
argument_list|)
expr_stmt|;
name|memcpy
argument_list|(
name|dest_curve
operator|->
name|points
argument_list|,
name|src_curve
operator|->
name|points
argument_list|,
sizeof|sizeof
argument_list|(
name|GimpVector2
argument_list|)
operator|*
name|src_curve
operator|->
name|n_points
argument_list|)
expr_stmt|;
name|memcpy
argument_list|(
name|dest_curve
operator|->
name|samples
argument_list|,
name|src_curve
operator|->
name|samples
argument_list|,
sizeof|sizeof
argument_list|(
name|gdouble
argument_list|)
operator|*
name|src_curve
operator|->
name|n_samples
argument_list|)
expr_stmt|;
name|dest_curve
operator|->
name|identity
operator|=
name|src_curve
operator|->
name|identity
expr_stmt|;
block|}
block|}
name|g_object_notify
argument_list|(
name|G_OBJECT
argument_list|(
name|dest
argument_list|)
argument_list|,
literal|"curve"
argument_list|)
expr_stmt|;
name|dest_config
operator|->
name|channel
operator|=
name|src_config
operator|->
name|channel
expr_stmt|;
name|g_object_notify
argument_list|(
name|G_OBJECT
argument_list|(
name|dest
argument_list|)
argument_list|,
literal|"channel"
argument_list|)
expr_stmt|;
return|return
name|TRUE
return|;
block|}
end_function

begin_function
specifier|static
name|void
DECL|function|gimp_curves_config_curve_dirty (GimpCurve * curve,GimpCurvesConfig * config)
name|gimp_curves_config_curve_dirty
parameter_list|(
name|GimpCurve
modifier|*
name|curve
parameter_list|,
name|GimpCurvesConfig
modifier|*
name|config
parameter_list|)
block|{
name|g_object_notify
argument_list|(
name|G_OBJECT
argument_list|(
name|config
argument_list|)
argument_list|,
literal|"curve"
argument_list|)
expr_stmt|;
block|}
end_function

begin_comment
comment|/*  public functions  */
end_comment

begin_function
name|void
DECL|function|gimp_curves_config_reset_channel (GimpCurvesConfig * config)
name|gimp_curves_config_reset_channel
parameter_list|(
name|GimpCurvesConfig
modifier|*
name|config
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
name|config
operator|->
name|channel
index|]
argument_list|,
name|TRUE
argument_list|)
expr_stmt|;
block|}
end_function

begin_define
DECL|macro|GIMP_CURVE_N_CRUFT_POINTS
define|#
directive|define
name|GIMP_CURVE_N_CRUFT_POINTS
value|17
end_define

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
name|GIMP_CURVE_N_CRUFT_POINTS
index|]
decl_stmt|;
name|gint
name|value
index|[
literal|5
index|]
index|[
name|GIMP_CURVE_N_CRUFT_POINTS
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
name|GIMP_CURVE_N_CRUFT_POINTS
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
name|GIMP_CURVE_N_CRUFT_POINTS
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
operator|(
name|gdouble
operator|)
name|index
index|[
name|i
index|]
index|[
name|j
index|]
operator|/
literal|255.0
argument_list|,
operator|(
name|gdouble
operator|)
name|value
index|[
name|i
index|]
index|[
name|j
index|]
operator|/
literal|255.0
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
name|g_object_thaw_notify
argument_list|(
name|G_OBJECT
argument_list|(
name|config
argument_list|)
argument_list|)
expr_stmt|;
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
name|gint
name|j
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
name|gint
name|n_points
decl_stmt|;
for|for
control|(
name|j
operator|=
literal|0
init|;
name|j
operator|<
name|curve
operator|->
name|n_points
condition|;
name|j
operator|++
control|)
block|{
name|curve
operator|->
name|points
index|[
name|j
index|]
operator|.
name|x
operator|=
operator|-
literal|1
expr_stmt|;
name|curve
operator|->
name|points
index|[
name|j
index|]
operator|.
name|y
operator|=
operator|-
literal|1
expr_stmt|;
block|}
comment|/* pick some points from the curve and make them control            * points            */
name|n_points
operator|=
name|CLAMP
argument_list|(
literal|9
argument_list|,
name|curve
operator|->
name|n_points
operator|/
literal|2
argument_list|,
name|curve
operator|->
name|n_points
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
name|n_points
condition|;
name|j
operator|++
control|)
block|{
name|gint
name|sample
init|=
name|j
operator|*
operator|(
name|curve
operator|->
name|n_samples
operator|-
literal|1
operator|)
operator|/
operator|(
name|n_points
operator|-
literal|1
operator|)
decl_stmt|;
name|gint
name|point
init|=
name|j
operator|*
operator|(
name|curve
operator|->
name|n_points
operator|-
literal|1
operator|)
operator|/
operator|(
name|n_points
operator|-
literal|1
operator|)
decl_stmt|;
name|curve
operator|->
name|points
index|[
name|point
index|]
operator|.
name|x
operator|=
operator|(
operator|(
name|gdouble
operator|)
name|sample
operator|/
call|(
name|gdouble
call|)
argument_list|(
name|curve
operator|->
name|n_samples
operator|-
literal|1
argument_list|)
operator|)
expr_stmt|;
name|curve
operator|->
name|points
index|[
name|point
index|]
operator|.
name|y
operator|=
name|curve
operator|->
name|samples
index|[
name|sample
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
name|curve
operator|->
name|n_points
condition|;
name|j
operator|++
control|)
block|{
name|gdouble
name|x
decl_stmt|,
name|y
decl_stmt|;
name|gimp_curve_get_point
argument_list|(
name|curve
argument_list|,
name|j
argument_list|,
operator|&
name|x
argument_list|,
operator|&
name|y
argument_list|)
expr_stmt|;
if|if
condition|(
name|x
operator|<
literal|0.0
operator|||
name|y
operator|<
literal|0.0
condition|)
block|{
name|fprintf
argument_list|(
name|file
argument_list|,
literal|"%d %d "
argument_list|,
operator|-
literal|1
argument_list|,
operator|-
literal|1
argument_list|)
expr_stmt|;
block|}
else|else
block|{
name|fprintf
argument_list|(
name|file
argument_list|,
literal|"%d %d "
argument_list|,
call|(
name|gint
call|)
argument_list|(
name|x
operator|*
literal|255.999
argument_list|)
argument_list|,
call|(
name|gint
call|)
argument_list|(
name|y
operator|*
literal|255.999
argument_list|)
argument_list|)
expr_stmt|;
block|}
block|}
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
sizeof|sizeof
argument_list|(
name|cruft
operator|->
name|curve
index|[
name|channel
index|]
argument_list|)
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
sizeof|sizeof
argument_list|(
name|cruft
operator|->
name|curve
index|[
literal|1
index|]
argument_list|)
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

