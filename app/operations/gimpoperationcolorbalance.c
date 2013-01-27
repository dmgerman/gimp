begin_unit|revision:0.9.5;language:C;cregit-version:0.0.1
begin_comment
comment|/* GIMP - The GNU Image Manipulation Program  * Copyright (C) 1995 Spencer Kimball and Peter Mattis  *  * gimpoperationcolorbalance.c  * Copyright (C) 2007 Michael Natterer<mitch@gimp.org>  *  * This program is free software: you can redistribute it and/or modify  * it under the terms of the GNU General Public License as published by  * the Free Software Foundation; either version 3 of the License, or  * (at your option) any later version.  *  * This program is distributed in the hope that it will be useful,  * but WITHOUT ANY WARRANTY; without even the implied warranty of  * MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the  * GNU General Public License for more details.  *  * You should have received a copy of the GNU General Public License  * along with this program.  If not, see<http://www.gnu.org/licenses/>.  */
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
file|"operations-types.h"
end_include

begin_include
include|#
directive|include
file|"gimpcolorbalanceconfig.h"
end_include

begin_include
include|#
directive|include
file|"gimpoperationcolorbalance.h"
end_include

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
parameter_list|,
specifier|const
name|GeglRectangle
modifier|*
name|roi
parameter_list|,
name|gint
name|level
parameter_list|)
function_decl|;
end_function_decl

begin_macro
DECL|function|G_DEFINE_TYPE (GimpOperationColorBalance,gimp_operation_color_balance,GIMP_TYPE_OPERATION_POINT_FILTER)
name|G_DEFINE_TYPE
argument_list|(
argument|GimpOperationColorBalance
argument_list|,
argument|gimp_operation_color_balance
argument_list|,
argument|GIMP_TYPE_OPERATION_POINT_FILTER
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
name|gimp_operation_point_filter_set_property
expr_stmt|;
name|object_class
operator|->
name|get_property
operator|=
name|gimp_operation_point_filter_get_property
expr_stmt|;
name|gegl_operation_class_set_keys
argument_list|(
name|operation_class
argument_list|,
literal|"name"
argument_list|,
literal|"gimp:color-balance"
argument_list|,
literal|"categories"
argument_list|,
literal|"color"
argument_list|,
literal|"description"
argument_list|,
literal|"GIMP Color Balance operation"
argument_list|,
name|NULL
argument_list|)
expr_stmt|;
name|point_class
operator|->
name|process
operator|=
name|gimp_operation_color_balance_process
expr_stmt|;
name|g_object_class_install_property
argument_list|(
name|object_class
argument_list|,
name|GIMP_OPERATION_POINT_FILTER_PROP_CONFIG
argument_list|,
name|g_param_spec_object
argument_list|(
literal|"config"
argument_list|,
literal|"Config"
argument_list|,
literal|"The config object"
argument_list|,
name|GIMP_TYPE_COLOR_BALANCE_CONFIG
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
block|{ }
end_function

begin_function
specifier|static
specifier|inline
name|gfloat
DECL|function|gimp_operation_color_balance_map (gfloat value,gdouble lightness,gdouble shadows,gdouble midtones,gdouble highlights)
name|gimp_operation_color_balance_map
parameter_list|(
name|gfloat
name|value
parameter_list|,
name|gdouble
name|lightness
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
comment|/* Apply masks to the corrections for shadows, midtones and    * highlights so that each correction affects only one range.    * Those masks look like this:    *     â¾\___    *     _/â¾\_    *     ___/â¾    * with ramps of width a at x = b and x = 1 - b.    *    * The sum of these masks equals 1 for x in 0..1, so applying the    * same correction in the shadows and in the midtones is equivalent    * to applying this correction on a virtual shadows_and_midtones    * range.    */
specifier|static
specifier|const
name|gdouble
name|a
init|=
literal|0.25
decl_stmt|,
name|b
init|=
literal|0.333
decl_stmt|,
name|scale
init|=
literal|0.7
decl_stmt|;
name|shadows
operator|*=
name|CLAMP
argument_list|(
operator|(
name|lightness
operator|-
name|b
operator|)
operator|/
operator|-
name|a
operator|+
literal|0.5
argument_list|,
literal|0
argument_list|,
literal|1
argument_list|)
operator|*
name|scale
expr_stmt|;
name|midtones
operator|*=
name|CLAMP
argument_list|(
operator|(
name|lightness
operator|-
name|b
operator|)
operator|/
name|a
operator|+
literal|0.5
argument_list|,
literal|0
argument_list|,
literal|1
argument_list|)
operator|*
name|CLAMP
argument_list|(
operator|(
name|lightness
operator|+
name|b
operator|-
literal|1
operator|)
operator|/
operator|-
name|a
operator|+
literal|0.5
argument_list|,
literal|0
argument_list|,
literal|1
argument_list|)
operator|*
name|scale
expr_stmt|;
name|highlights
operator|*=
name|CLAMP
argument_list|(
operator|(
name|lightness
operator|+
name|b
operator|-
literal|1
operator|)
operator|/
name|a
operator|+
literal|0.5
argument_list|,
literal|0
argument_list|,
literal|1
argument_list|)
operator|*
name|scale
expr_stmt|;
name|value
operator|+=
name|shadows
expr_stmt|;
name|value
operator|+=
name|midtones
expr_stmt|;
name|value
operator|+=
name|highlights
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
DECL|function|gimp_operation_color_balance_process (GeglOperation * operation,void * in_buf,void * out_buf,glong samples,const GeglRectangle * roi,gint level)
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
parameter_list|,
specifier|const
name|GeglRectangle
modifier|*
name|roi
parameter_list|,
name|gint
name|level
parameter_list|)
block|{
name|GimpOperationPointFilter
modifier|*
name|point
init|=
name|GIMP_OPERATION_POINT_FILTER
argument_list|(
name|operation
argument_list|)
decl_stmt|;
name|GimpColorBalanceConfig
modifier|*
name|config
init|=
name|GIMP_COLOR_BALANCE_CONFIG
argument_list|(
name|point
operator|->
name|config
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
if|if
condition|(
operator|!
name|config
condition|)
return|return
name|FALSE
return|;
while|while
condition|(
name|samples
operator|--
condition|)
block|{
name|gfloat
name|r
init|=
name|src
index|[
name|RED
index|]
decl_stmt|;
name|gfloat
name|g
init|=
name|src
index|[
name|GREEN
index|]
decl_stmt|;
name|gfloat
name|b
init|=
name|src
index|[
name|BLUE
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
name|GimpRGB
name|rgb
init|=
block|{
name|r
block|,
name|g
block|,
name|b
block|}
decl_stmt|;
name|GimpHSL
name|hsl
decl_stmt|;
name|gimp_rgb_to_hsl
argument_list|(
operator|&
name|rgb
argument_list|,
operator|&
name|hsl
argument_list|)
expr_stmt|;
name|r_n
operator|=
name|gimp_operation_color_balance_map
argument_list|(
name|r
argument_list|,
name|hsl
operator|.
name|l
argument_list|,
name|config
operator|->
name|cyan_red
index|[
name|GIMP_SHADOWS
index|]
argument_list|,
name|config
operator|->
name|cyan_red
index|[
name|GIMP_MIDTONES
index|]
argument_list|,
name|config
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
name|hsl
operator|.
name|l
argument_list|,
name|config
operator|->
name|magenta_green
index|[
name|GIMP_SHADOWS
index|]
argument_list|,
name|config
operator|->
name|magenta_green
index|[
name|GIMP_MIDTONES
index|]
argument_list|,
name|config
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
name|hsl
operator|.
name|l
argument_list|,
name|config
operator|->
name|yellow_blue
index|[
name|GIMP_SHADOWS
index|]
argument_list|,
name|config
operator|->
name|yellow_blue
index|[
name|GIMP_MIDTONES
index|]
argument_list|,
name|config
operator|->
name|yellow_blue
index|[
name|GIMP_HIGHLIGHTS
index|]
argument_list|)
expr_stmt|;
if|if
condition|(
name|config
operator|->
name|preserve_luminosity
condition|)
block|{
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
name|RED
index|]
operator|=
name|r_n
expr_stmt|;
name|dest
index|[
name|GREEN
index|]
operator|=
name|g_n
expr_stmt|;
name|dest
index|[
name|BLUE
index|]
operator|=
name|b_n
expr_stmt|;
name|dest
index|[
name|ALPHA
index|]
operator|=
name|src
index|[
name|ALPHA
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

