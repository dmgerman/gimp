begin_unit|revision:0.9.5;language:C;cregit-version:0.0.1
begin_comment
comment|/* GIMP - The GNU Image Manipulation Program  * Copyright (C) 1995 Spencer Kimball and Peter Mattis  *  * gimpoperationcolorbalance.c  * Copyright (C) 2007 Michael Natterer<mitch@gimp.org>  *  * This program is free software; you can redistribute it and/or modify  * it under the terms of the GNU General Public License as published by  * the Free Software Foundation; either version 2 of the License, or  * (at your option) any later version.  *  * This program is distributed in the hope that it will be useful,  * but WITHOUT ANY WARRANTY; without even the implied warranty of  * MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the  * GNU General Public License for more details.  *  * You should have received a copy of the GNU General Public License  * along with this program; if not, write to the Free Software  * Foundation, Inc., 59 Temple Place - Suite 330, Boston, MA 02111-1307, USA.  */
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
file|"gegl-types.h"
end_include

begin_include
include|#
directive|include
file|"gimpoperationcolorbalance.h"
end_include

begin_enum
enum|enum
DECL|enum|__anon2a4214f30103
block|{
DECL|enumerator|PROP_0
name|PROP_0
block|,
DECL|enumerator|PROP_RANGE
name|PROP_RANGE
block|,
DECL|enumerator|PROP_CYAN_RED
name|PROP_CYAN_RED
block|,
DECL|enumerator|PROP_MAGENTA_GREEN
name|PROP_MAGENTA_GREEN
block|,
DECL|enumerator|PROP_YELLOW_BLUE
name|PROP_YELLOW_BLUE
block|,
DECL|enumerator|PROP_PRESERVE_LUMINOSITY
name|PROP_PRESERVE_LUMINOSITY
block|}
enum|;
end_enum

begin_function_decl
specifier|static
name|void
name|gimp_operation_color_balance_get_property
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
name|gimp_operation_color_balance_set_property
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
name|gimp_operation_color_balance_process
parameter_list|(
name|GeglOperation
modifier|*
name|operation
parameter_list|,
name|void
modifier|*
name|in_buf
parameter_list|,
name|void
modifier|*
name|out_buf
parameter_list|,
name|glong
name|samples
parameter_list|)
function_decl|;
end_function_decl

begin_macro
DECL|function|G_DEFINE_TYPE (GimpOperationColorBalance,gimp_operation_color_balance,GEGL_TYPE_OPERATION_POINT_FILTER)
name|G_DEFINE_TYPE
argument_list|(
argument|GimpOperationColorBalance
argument_list|,
argument|gimp_operation_color_balance
argument_list|,
argument|GEGL_TYPE_OPERATION_POINT_FILTER
argument_list|)
end_macro

begin_define
DECL|macro|parent_class
define|#
directive|define
name|parent_class
value|gimp_operation_color_balance_parent_class
end_define

begin_function
specifier|static
name|void
name|gimp_operation_color_balance_class_init
parameter_list|(
name|GimpOperationColorBalanceClass
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
name|GeglOperationClass
modifier|*
name|operation_class
init|=
name|GEGL_OPERATION_CLASS
argument_list|(
name|klass
argument_list|)
decl_stmt|;
name|GeglOperationPointFilterClass
modifier|*
name|point_class
init|=
name|GEGL_OPERATION_POINT_FILTER_CLASS
argument_list|(
name|klass
argument_list|)
decl_stmt|;
name|object_class
operator|->
name|set_property
operator|=
name|gimp_operation_color_balance_set_property
expr_stmt|;
name|object_class
operator|->
name|get_property
operator|=
name|gimp_operation_color_balance_get_property
expr_stmt|;
name|point_class
operator|->
name|process
operator|=
name|gimp_operation_color_balance_process
expr_stmt|;
name|gegl_operation_class_set_name
argument_list|(
name|operation_class
argument_list|,
literal|"gimp-color-balance"
argument_list|)
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
name|GIMP_TYPE_TRANSFER_MODE
argument_list|,
name|GIMP_MIDTONES
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
name|PROP_CYAN_RED
argument_list|,
name|g_param_spec_double
argument_list|(
literal|"cyan-red"
argument_list|,
literal|"Cyan-Red"
argument_list|,
literal|"Cyan-Red"
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
name|PROP_MAGENTA_GREEN
argument_list|,
name|g_param_spec_double
argument_list|(
literal|"magenta-green"
argument_list|,
literal|"Magenta-Green"
argument_list|,
literal|"Magenta-Green"
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
name|PROP_YELLOW_BLUE
argument_list|,
name|g_param_spec_double
argument_list|(
literal|"yellow-blue"
argument_list|,
literal|"Yellow-Blue"
argument_list|,
literal|"Yellow-Blue"
argument_list|,
operator|-
literal|1.0
argument_list|,
literal|1.0
argument_list|,
literal|1.0
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
name|PROP_PRESERVE_LUMINOSITY
argument_list|,
name|g_param_spec_boolean
argument_list|(
literal|"preserve-luminosity"
argument_list|,
literal|"Preserve Luminosity"
argument_list|,
literal|"Preserve Luminosity"
argument_list|,
name|TRUE
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
DECL|function|gimp_operation_color_balance_init (GimpOperationColorBalance * self)
name|gimp_operation_color_balance_init
parameter_list|(
name|GimpOperationColorBalance
modifier|*
name|self
parameter_list|)
block|{
name|GimpTransferMode
name|range
decl_stmt|;
name|self
operator|->
name|range
operator|=
name|GIMP_MIDTONES
expr_stmt|;
for|for
control|(
name|range
operator|=
name|GIMP_SHADOWS
init|;
name|range
operator|<=
name|GIMP_HIGHLIGHTS
condition|;
name|range
operator|++
control|)
block|{
name|self
operator|->
name|cyan_red
index|[
name|range
index|]
operator|=
literal|0.0
expr_stmt|;
name|self
operator|->
name|magenta_green
index|[
name|range
index|]
operator|=
literal|0.0
expr_stmt|;
name|self
operator|->
name|yellow_blue
index|[
name|range
index|]
operator|=
literal|0.0
expr_stmt|;
block|}
name|self
operator|->
name|preserve_luminosity
operator|=
name|TRUE
expr_stmt|;
block|}
end_function

begin_function
specifier|static
name|void
DECL|function|gimp_operation_color_balance_get_property (GObject * object,guint property_id,GValue * value,GParamSpec * pspec)
name|gimp_operation_color_balance_get_property
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
name|GimpOperationColorBalance
modifier|*
name|self
init|=
name|GIMP_OPERATION_COLOR_BALANCE
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
name|PROP_CYAN_RED
case|:
name|g_value_set_double
argument_list|(
name|value
argument_list|,
name|self
operator|->
name|cyan_red
index|[
name|self
operator|->
name|range
index|]
argument_list|)
expr_stmt|;
break|break;
case|case
name|PROP_MAGENTA_GREEN
case|:
name|g_value_set_double
argument_list|(
name|value
argument_list|,
name|self
operator|->
name|magenta_green
index|[
name|self
operator|->
name|range
index|]
argument_list|)
expr_stmt|;
break|break;
case|case
name|PROP_YELLOW_BLUE
case|:
name|g_value_set_double
argument_list|(
name|value
argument_list|,
name|self
operator|->
name|yellow_blue
index|[
name|self
operator|->
name|range
index|]
argument_list|)
expr_stmt|;
break|break;
case|case
name|PROP_PRESERVE_LUMINOSITY
case|:
name|g_value_set_boolean
argument_list|(
name|value
argument_list|,
name|self
operator|->
name|preserve_luminosity
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
DECL|function|gimp_operation_color_balance_set_property (GObject * object,guint property_id,const GValue * value,GParamSpec * pspec)
name|gimp_operation_color_balance_set_property
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
name|GimpOperationColorBalance
modifier|*
name|self
init|=
name|GIMP_OPERATION_COLOR_BALANCE
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
name|PROP_CYAN_RED
case|:
name|self
operator|->
name|cyan_red
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
name|PROP_MAGENTA_GREEN
case|:
name|self
operator|->
name|magenta_green
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
name|PROP_YELLOW_BLUE
case|:
name|self
operator|->
name|yellow_blue
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
name|PROP_PRESERVE_LUMINOSITY
case|:
name|self
operator|->
name|preserve_luminosity
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
specifier|inline
name|gfloat
DECL|function|gimp_operation_color_balance_map (gfloat value,gdouble shadows,gdouble midtones,gdouble highlights)
name|gimp_operation_color_balance_map
parameter_list|(
name|gfloat
name|value
parameter_list|,
name|gdouble
name|shadows
parameter_list|,
name|gdouble
name|midtones
parameter_list|,
name|gdouble
name|highlights
parameter_list|)
block|{
name|gdouble
name|low
init|=
literal|1.075
operator|-
literal|1.0
operator|/
operator|(
name|value
operator|/
literal|16.0
operator|+
literal|1.0
operator|)
decl_stmt|;
name|gdouble
name|mid
init|=
literal|0.667
operator|*
operator|(
literal|1.0
operator|-
name|SQR
argument_list|(
name|value
operator|-
literal|0.5
argument_list|)
operator|)
decl_stmt|;
name|gdouble
name|shadows_add
decl_stmt|;
name|gdouble
name|shadows_sub
decl_stmt|;
name|gdouble
name|midtones_add
decl_stmt|;
name|gdouble
name|midtones_sub
decl_stmt|;
name|gdouble
name|highlights_add
decl_stmt|;
name|gdouble
name|highlights_sub
decl_stmt|;
name|shadows_add
operator|=
name|low
operator|+
literal|1.0
expr_stmt|;
name|shadows_sub
operator|=
literal|1.0
operator|-
name|low
expr_stmt|;
name|midtones_add
operator|=
name|mid
expr_stmt|;
name|midtones_sub
operator|=
name|mid
expr_stmt|;
name|highlights_add
operator|=
literal|1.0
operator|-
name|low
expr_stmt|;
name|highlights_sub
operator|=
name|low
operator|+
literal|1.0
expr_stmt|;
name|value
operator|+=
name|shadows
operator|*
operator|(
name|shadows
operator|>
literal|0
condition|?
name|shadows_add
else|:
name|shadows_sub
operator|)
expr_stmt|;
name|value
operator|=
name|CLAMP
argument_list|(
name|value
argument_list|,
literal|0.0
argument_list|,
literal|1.0
argument_list|)
expr_stmt|;
name|value
operator|+=
name|midtones
operator|*
operator|(
name|midtones
operator|>
literal|0
condition|?
name|midtones_add
else|:
name|midtones_sub
operator|)
expr_stmt|;
name|value
operator|=
name|CLAMP
argument_list|(
name|value
argument_list|,
literal|0.0
argument_list|,
literal|1.0
argument_list|)
expr_stmt|;
name|value
operator|+=
name|highlights
operator|*
operator|(
name|highlights
operator|>
literal|0
condition|?
name|highlights_add
else|:
name|highlights_sub
operator|)
expr_stmt|;
name|value
operator|=
name|CLAMP
argument_list|(
name|value
argument_list|,
literal|0.0
argument_list|,
literal|1.0
argument_list|)
expr_stmt|;
return|return
name|value
return|;
block|}
end_function

begin_function
specifier|static
name|gboolean
DECL|function|gimp_operation_color_balance_process (GeglOperation * operation,void * in_buf,void * out_buf,glong samples)
name|gimp_operation_color_balance_process
parameter_list|(
name|GeglOperation
modifier|*
name|operation
parameter_list|,
name|void
modifier|*
name|in_buf
parameter_list|,
name|void
modifier|*
name|out_buf
parameter_list|,
name|glong
name|samples
parameter_list|)
block|{
name|GimpOperationColorBalance
modifier|*
name|self
init|=
name|GIMP_OPERATION_COLOR_BALANCE
argument_list|(
name|operation
argument_list|)
decl_stmt|;
name|gfloat
modifier|*
name|src
init|=
name|in_buf
decl_stmt|;
name|gfloat
modifier|*
name|dest
init|=
name|out_buf
decl_stmt|;
name|glong
name|sample
decl_stmt|;
for|for
control|(
name|sample
operator|=
literal|0
init|;
name|sample
operator|<
name|samples
condition|;
name|sample
operator|++
control|)
block|{
name|gfloat
name|r
init|=
name|src
index|[
name|RED_PIX
index|]
decl_stmt|;
name|gfloat
name|g
init|=
name|src
index|[
name|GREEN_PIX
index|]
decl_stmt|;
name|gfloat
name|b
init|=
name|src
index|[
name|BLUE_PIX
index|]
decl_stmt|;
name|gfloat
name|r_n
decl_stmt|;
name|gfloat
name|g_n
decl_stmt|;
name|gfloat
name|b_n
decl_stmt|;
name|r_n
operator|=
name|gimp_operation_color_balance_map
argument_list|(
name|r
argument_list|,
name|self
operator|->
name|cyan_red
index|[
name|GIMP_SHADOWS
index|]
argument_list|,
name|self
operator|->
name|cyan_red
index|[
name|GIMP_MIDTONES
index|]
argument_list|,
name|self
operator|->
name|cyan_red
index|[
name|GIMP_HIGHLIGHTS
index|]
argument_list|)
expr_stmt|;
name|g_n
operator|=
name|gimp_operation_color_balance_map
argument_list|(
name|g
argument_list|,
name|self
operator|->
name|magenta_green
index|[
name|GIMP_SHADOWS
index|]
argument_list|,
name|self
operator|->
name|magenta_green
index|[
name|GIMP_MIDTONES
index|]
argument_list|,
name|self
operator|->
name|magenta_green
index|[
name|GIMP_HIGHLIGHTS
index|]
argument_list|)
expr_stmt|;
name|b_n
operator|=
name|gimp_operation_color_balance_map
argument_list|(
name|b
argument_list|,
name|self
operator|->
name|yellow_blue
index|[
name|GIMP_SHADOWS
index|]
argument_list|,
name|self
operator|->
name|yellow_blue
index|[
name|GIMP_MIDTONES
index|]
argument_list|,
name|self
operator|->
name|yellow_blue
index|[
name|GIMP_HIGHLIGHTS
index|]
argument_list|)
expr_stmt|;
if|if
condition|(
name|self
operator|->
name|preserve_luminosity
condition|)
block|{
name|GimpRGB
name|rgb
decl_stmt|;
name|GimpHSL
name|hsl
decl_stmt|;
name|GimpHSL
name|hsl2
decl_stmt|;
name|rgb
operator|.
name|r
operator|=
name|r_n
expr_stmt|;
name|rgb
operator|.
name|g
operator|=
name|g_n
expr_stmt|;
name|rgb
operator|.
name|b
operator|=
name|b_n
expr_stmt|;
name|gimp_rgb_to_hsl
argument_list|(
operator|&
name|rgb
argument_list|,
operator|&
name|hsl
argument_list|)
expr_stmt|;
name|rgb
operator|.
name|r
operator|=
name|r
expr_stmt|;
name|rgb
operator|.
name|g
operator|=
name|g
expr_stmt|;
name|rgb
operator|.
name|b
operator|=
name|b
expr_stmt|;
name|gimp_rgb_to_hsl
argument_list|(
operator|&
name|rgb
argument_list|,
operator|&
name|hsl2
argument_list|)
expr_stmt|;
name|hsl
operator|.
name|l
operator|=
name|hsl2
operator|.
name|l
expr_stmt|;
name|gimp_hsl_to_rgb
argument_list|(
operator|&
name|hsl
argument_list|,
operator|&
name|rgb
argument_list|)
expr_stmt|;
name|r_n
operator|=
name|rgb
operator|.
name|r
expr_stmt|;
name|g_n
operator|=
name|rgb
operator|.
name|g
expr_stmt|;
name|b_n
operator|=
name|rgb
operator|.
name|b
expr_stmt|;
block|}
name|dest
index|[
name|RED_PIX
index|]
operator|=
name|r_n
expr_stmt|;
name|dest
index|[
name|GREEN_PIX
index|]
operator|=
name|g_n
expr_stmt|;
name|dest
index|[
name|BLUE_PIX
index|]
operator|=
name|b_n
expr_stmt|;
name|dest
index|[
name|ALPHA_PIX
index|]
operator|=
name|src
index|[
name|ALPHA_PIX
index|]
expr_stmt|;
name|src
operator|+=
literal|4
expr_stmt|;
name|dest
operator|+=
literal|4
expr_stmt|;
block|}
return|return
name|TRUE
return|;
block|}
end_function

end_unit

