begin_unit|revision:0.9.5;language:C;cregit-version:0.0.1
begin_comment
comment|/* GIMP - The GNU Image Manipulation Program  * Copyright (C) 1995 Spencer Kimball and Peter Mattis  *  * gimpoperationhuesaturation.c  * Copyright (C) 2007 Michael Natterer<mitch@gimp.org>  *  * This program is free software: you can redistribute it and/or modify  * it under the terms of the GNU General Public License as published by  * the Free Software Foundation; either version 3 of the License, or  * (at your option) any later version.  *  * This program is distributed in the hope that it will be useful,  * but WITHOUT ANY WARRANTY; without even the implied warranty of  * MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the  * GNU General Public License for more details.  *  * You should have received a copy of the GNU General Public License  * along with this program.  If not, see<http://www.gnu.org/licenses/>.  */
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
file|"gimphuesaturationconfig.h"
end_include

begin_include
include|#
directive|include
file|"gimpoperationhuesaturation.h"
end_include

begin_include
include|#
directive|include
file|"gimp-intl.h"
end_include

begin_function_decl
specifier|static
name|gboolean
name|gimp_operation_hue_saturation_process
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
DECL|function|G_DEFINE_TYPE (GimpOperationHueSaturation,gimp_operation_hue_saturation,GIMP_TYPE_OPERATION_POINT_FILTER)
name|G_DEFINE_TYPE
argument_list|(
argument|GimpOperationHueSaturation
argument_list|,
argument|gimp_operation_hue_saturation
argument_list|,
argument|GIMP_TYPE_OPERATION_POINT_FILTER
argument_list|)
end_macro

begin_define
DECL|macro|parent_class
define|#
directive|define
name|parent_class
value|gimp_operation_hue_saturation_parent_class
end_define

begin_function
specifier|static
name|void
name|gimp_operation_hue_saturation_class_init
parameter_list|(
name|GimpOperationHueSaturationClass
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
literal|"gimp:hue-saturation"
argument_list|,
literal|"categories"
argument_list|,
literal|"color"
argument_list|,
literal|"description"
argument_list|,
name|_
argument_list|(
literal|"Adjust hue, saturation, and lightness"
argument_list|)
argument_list|,
name|NULL
argument_list|)
expr_stmt|;
name|point_class
operator|->
name|process
operator|=
name|gimp_operation_hue_saturation_process
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
name|GIMP_TYPE_HUE_SATURATION_CONFIG
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
DECL|function|gimp_operation_hue_saturation_init (GimpOperationHueSaturation * self)
name|gimp_operation_hue_saturation_init
parameter_list|(
name|GimpOperationHueSaturation
modifier|*
name|self
parameter_list|)
block|{ }
end_function

begin_function
specifier|static
specifier|inline
name|gdouble
DECL|function|map_hue (GimpHueSaturationConfig * config,GimpHueRange range,gdouble value)
name|map_hue
parameter_list|(
name|GimpHueSaturationConfig
modifier|*
name|config
parameter_list|,
name|GimpHueRange
name|range
parameter_list|,
name|gdouble
name|value
parameter_list|)
block|{
name|value
operator|+=
operator|(
name|config
operator|->
name|hue
index|[
name|GIMP_HUE_RANGE_ALL
index|]
operator|+
name|config
operator|->
name|hue
index|[
name|range
index|]
operator|)
operator|/
literal|2.0
expr_stmt|;
if|if
condition|(
name|value
operator|<
literal|0
condition|)
return|return
name|value
operator|+
literal|1.0
return|;
elseif|else
if|if
condition|(
name|value
operator|>
literal|1.0
condition|)
return|return
name|value
operator|-
literal|1.0
return|;
else|else
return|return
name|value
return|;
block|}
end_function

begin_function
specifier|static
specifier|inline
name|gdouble
DECL|function|map_hue_overlap (GimpHueSaturationConfig * config,GimpHueRange primary_range,GimpHueRange secondary_range,gdouble value,gdouble primary_intensity,gdouble secondary_intensity)
name|map_hue_overlap
parameter_list|(
name|GimpHueSaturationConfig
modifier|*
name|config
parameter_list|,
name|GimpHueRange
name|primary_range
parameter_list|,
name|GimpHueRange
name|secondary_range
parameter_list|,
name|gdouble
name|value
parameter_list|,
name|gdouble
name|primary_intensity
parameter_list|,
name|gdouble
name|secondary_intensity
parameter_list|)
block|{
comment|/*  When calculating an overlap between two ranges, interpolate the    *  hue adjustment from config->hue[primary_range] and    *  config->hue[secondary_range] BEFORE mapping it to the input    *  value.  This fixes odd edge cases where only one of the ranges    *  crosses the red/magenta wraparound (bug #527085), or if    *  adjustments to different channels yield more than 180 degree    *  difference from each other. (Why anyone would do that is beyond    *  me, but still.)    *    *  See bugs #527085 and #644032 for examples of such cases.    */
name|gdouble
name|v
init|=
name|config
operator|->
name|hue
index|[
name|primary_range
index|]
operator|*
name|primary_intensity
operator|+
name|config
operator|->
name|hue
index|[
name|secondary_range
index|]
operator|*
name|secondary_intensity
decl_stmt|;
name|value
operator|+=
operator|(
name|config
operator|->
name|hue
index|[
name|GIMP_HUE_RANGE_ALL
index|]
operator|+
name|v
operator|)
operator|/
literal|2.0
expr_stmt|;
if|if
condition|(
name|value
operator|<
literal|0
condition|)
return|return
name|value
operator|+
literal|1.0
return|;
elseif|else
if|if
condition|(
name|value
operator|>
literal|1.0
condition|)
return|return
name|value
operator|-
literal|1.0
return|;
else|else
return|return
name|value
return|;
block|}
end_function

begin_function
specifier|static
specifier|inline
name|gdouble
DECL|function|map_saturation (GimpHueSaturationConfig * config,GimpHueRange range,gdouble value)
name|map_saturation
parameter_list|(
name|GimpHueSaturationConfig
modifier|*
name|config
parameter_list|,
name|GimpHueRange
name|range
parameter_list|,
name|gdouble
name|value
parameter_list|)
block|{
name|gdouble
name|v
init|=
name|config
operator|->
name|saturation
index|[
name|GIMP_HUE_RANGE_ALL
index|]
operator|+
name|config
operator|->
name|saturation
index|[
name|range
index|]
decl_stmt|;
comment|/* This change affects the way saturation is computed. With the old    * code (different code for value< 0), increasing the saturation    * affected muted colors very much, and bright colors less. With the    * new code, it affects muted colors and bright colors more or less    * evenly. For enhancing the color in photos, the new behavior is    * exactly what you want. It's hard for me to imagine a case in    * which the old behavior is better.   */
name|value
operator|*=
operator|(
name|v
operator|+
literal|1.0
operator|)
expr_stmt|;
return|return
name|CLAMP
argument_list|(
name|value
argument_list|,
literal|0.0
argument_list|,
literal|1.0
argument_list|)
return|;
block|}
end_function

begin_function
specifier|static
specifier|inline
name|gdouble
DECL|function|map_lightness (GimpHueSaturationConfig * config,GimpHueRange range,gdouble value)
name|map_lightness
parameter_list|(
name|GimpHueSaturationConfig
modifier|*
name|config
parameter_list|,
name|GimpHueRange
name|range
parameter_list|,
name|gdouble
name|value
parameter_list|)
block|{
name|gdouble
name|v
init|=
operator|(
name|config
operator|->
name|lightness
index|[
name|GIMP_HUE_RANGE_ALL
index|]
operator|+
name|config
operator|->
name|lightness
index|[
name|range
index|]
operator|)
operator|/
literal|2.0
decl_stmt|;
if|if
condition|(
name|v
operator|<
literal|0
condition|)
return|return
name|value
operator|*
operator|(
name|v
operator|+
literal|1.0
operator|)
return|;
else|else
return|return
name|value
operator|+
operator|(
name|v
operator|*
operator|(
literal|1.0
operator|-
name|value
operator|)
operator|)
return|;
block|}
end_function

begin_function
specifier|static
name|gboolean
DECL|function|gimp_operation_hue_saturation_process (GeglOperation * operation,void * in_buf,void * out_buf,glong samples,const GeglRectangle * roi,gint level)
name|gimp_operation_hue_saturation_process
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
name|GimpHueSaturationConfig
modifier|*
name|config
init|=
name|GIMP_HUE_SATURATION_CONFIG
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
name|gfloat
name|overlap
decl_stmt|;
if|if
condition|(
operator|!
name|config
condition|)
return|return
name|FALSE
return|;
name|overlap
operator|=
name|config
operator|->
name|overlap
operator|/
literal|2.0
expr_stmt|;
while|while
condition|(
name|samples
operator|--
condition|)
block|{
name|GimpRGB
name|rgb
decl_stmt|;
name|GimpHSL
name|hsl
decl_stmt|;
name|gdouble
name|h
decl_stmt|;
name|gint
name|hue_counter
decl_stmt|;
name|gint
name|hue
init|=
literal|0
decl_stmt|;
name|gint
name|secondary_hue
init|=
literal|0
decl_stmt|;
name|gboolean
name|use_secondary_hue
init|=
name|FALSE
decl_stmt|;
name|gfloat
name|primary_intensity
init|=
literal|0.0
decl_stmt|;
name|gfloat
name|secondary_intensity
init|=
literal|0.0
decl_stmt|;
name|rgb
operator|.
name|r
operator|=
name|src
index|[
name|RED
index|]
expr_stmt|;
name|rgb
operator|.
name|g
operator|=
name|src
index|[
name|GREEN
index|]
expr_stmt|;
name|rgb
operator|.
name|b
operator|=
name|src
index|[
name|BLUE
index|]
expr_stmt|;
name|rgb
operator|.
name|a
operator|=
name|src
index|[
name|ALPHA
index|]
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
name|h
operator|=
name|hsl
operator|.
name|h
operator|*
literal|6.0
expr_stmt|;
for|for
control|(
name|hue_counter
operator|=
literal|0
init|;
name|hue_counter
operator|<
literal|7
condition|;
name|hue_counter
operator|++
control|)
block|{
name|gdouble
name|hue_threshold
init|=
operator|(
name|gdouble
operator|)
name|hue_counter
operator|+
literal|0.5
decl_stmt|;
if|if
condition|(
name|h
operator|<
operator|(
operator|(
name|gdouble
operator|)
name|hue_threshold
operator|+
name|overlap
operator|)
condition|)
block|{
name|hue
operator|=
name|hue_counter
expr_stmt|;
if|if
condition|(
name|overlap
operator|>
literal|0.0
operator|&&
name|h
operator|>
operator|(
operator|(
name|gdouble
operator|)
name|hue_threshold
operator|-
name|overlap
operator|)
condition|)
block|{
name|use_secondary_hue
operator|=
name|TRUE
expr_stmt|;
name|secondary_hue
operator|=
name|hue_counter
operator|+
literal|1
expr_stmt|;
name|secondary_intensity
operator|=
operator|(
name|h
operator|-
operator|(
name|gdouble
operator|)
name|hue_threshold
operator|+
name|overlap
operator|)
operator|/
operator|(
literal|2.0
operator|*
name|overlap
operator|)
expr_stmt|;
name|primary_intensity
operator|=
literal|1.0
operator|-
name|secondary_intensity
expr_stmt|;
block|}
else|else
block|{
name|use_secondary_hue
operator|=
name|FALSE
expr_stmt|;
block|}
break|break;
block|}
block|}
if|if
condition|(
name|hue
operator|>=
literal|6
condition|)
block|{
name|hue
operator|=
literal|0
expr_stmt|;
name|use_secondary_hue
operator|=
name|FALSE
expr_stmt|;
block|}
if|if
condition|(
name|secondary_hue
operator|>=
literal|6
condition|)
block|{
name|secondary_hue
operator|=
literal|0
expr_stmt|;
block|}
comment|/*  transform into GimpHueRange values  */
name|hue
operator|++
expr_stmt|;
name|secondary_hue
operator|++
expr_stmt|;
if|if
condition|(
name|use_secondary_hue
condition|)
block|{
name|hsl
operator|.
name|h
operator|=
name|map_hue_overlap
argument_list|(
name|config
argument_list|,
name|hue
argument_list|,
name|secondary_hue
argument_list|,
name|hsl
operator|.
name|h
argument_list|,
name|primary_intensity
argument_list|,
name|secondary_intensity
argument_list|)
expr_stmt|;
name|hsl
operator|.
name|s
operator|=
operator|(
name|map_saturation
argument_list|(
name|config
argument_list|,
name|hue
argument_list|,
name|hsl
operator|.
name|s
argument_list|)
operator|*
name|primary_intensity
operator|+
name|map_saturation
argument_list|(
name|config
argument_list|,
name|secondary_hue
argument_list|,
name|hsl
operator|.
name|s
argument_list|)
operator|*
name|secondary_intensity
operator|)
expr_stmt|;
name|hsl
operator|.
name|l
operator|=
operator|(
name|map_lightness
argument_list|(
name|config
argument_list|,
name|hue
argument_list|,
name|hsl
operator|.
name|l
argument_list|)
operator|*
name|primary_intensity
operator|+
name|map_lightness
argument_list|(
name|config
argument_list|,
name|secondary_hue
argument_list|,
name|hsl
operator|.
name|l
argument_list|)
operator|*
name|secondary_intensity
operator|)
expr_stmt|;
block|}
else|else
block|{
name|hsl
operator|.
name|h
operator|=
name|map_hue
argument_list|(
name|config
argument_list|,
name|hue
argument_list|,
name|hsl
operator|.
name|h
argument_list|)
expr_stmt|;
name|hsl
operator|.
name|s
operator|=
name|map_saturation
argument_list|(
name|config
argument_list|,
name|hue
argument_list|,
name|hsl
operator|.
name|s
argument_list|)
expr_stmt|;
name|hsl
operator|.
name|l
operator|=
name|map_lightness
argument_list|(
name|config
argument_list|,
name|hue
argument_list|,
name|hsl
operator|.
name|l
argument_list|)
expr_stmt|;
block|}
name|gimp_hsl_to_rgb
argument_list|(
operator|&
name|hsl
argument_list|,
operator|&
name|rgb
argument_list|)
expr_stmt|;
name|dest
index|[
name|RED
index|]
operator|=
name|rgb
operator|.
name|r
expr_stmt|;
name|dest
index|[
name|GREEN
index|]
operator|=
name|rgb
operator|.
name|g
expr_stmt|;
name|dest
index|[
name|BLUE
index|]
operator|=
name|rgb
operator|.
name|b
expr_stmt|;
name|dest
index|[
name|ALPHA
index|]
operator|=
name|rgb
operator|.
name|a
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

begin_comment
comment|/*  public functions  */
end_comment

begin_function
name|void
DECL|function|gimp_operation_hue_saturation_map (GimpHueSaturationConfig * config,const GimpRGB * color,GimpHueRange range,GimpRGB * result)
name|gimp_operation_hue_saturation_map
parameter_list|(
name|GimpHueSaturationConfig
modifier|*
name|config
parameter_list|,
specifier|const
name|GimpRGB
modifier|*
name|color
parameter_list|,
name|GimpHueRange
name|range
parameter_list|,
name|GimpRGB
modifier|*
name|result
parameter_list|)
block|{
name|GimpHSL
name|hsl
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
name|color
operator|!=
name|NULL
argument_list|)
expr_stmt|;
name|g_return_if_fail
argument_list|(
name|result
operator|!=
name|NULL
argument_list|)
expr_stmt|;
name|gimp_rgb_to_hsl
argument_list|(
name|color
argument_list|,
operator|&
name|hsl
argument_list|)
expr_stmt|;
name|hsl
operator|.
name|h
operator|=
name|map_hue
argument_list|(
name|config
argument_list|,
name|range
argument_list|,
name|hsl
operator|.
name|h
argument_list|)
expr_stmt|;
name|hsl
operator|.
name|s
operator|=
name|map_saturation
argument_list|(
name|config
argument_list|,
name|range
argument_list|,
name|hsl
operator|.
name|s
argument_list|)
expr_stmt|;
name|hsl
operator|.
name|l
operator|=
name|map_lightness
argument_list|(
name|config
argument_list|,
name|range
argument_list|,
name|hsl
operator|.
name|l
argument_list|)
expr_stmt|;
name|gimp_hsl_to_rgb
argument_list|(
operator|&
name|hsl
argument_list|,
name|result
argument_list|)
expr_stmt|;
block|}
end_function

end_unit

