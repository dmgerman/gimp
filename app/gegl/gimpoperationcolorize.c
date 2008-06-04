begin_unit|revision:0.9.5;language:C;cregit-version:0.0.1
begin_comment
comment|/* GIMP - The GNU Image Manipulation Program  * Copyright (C) 1995 Spencer Kimball and Peter Mattis  *  * gimpoperationcolorize.c  * Copyright (C) 2007 Michael Natterer<mitch@gimp.org>  *  * This program is free software; you can redistribute it and/or modify  * it under the terms of the GNU General Public License as published by  * the Free Software Foundation; either version 2 of the License, or  * (at your option) any later version.  *  * This program is distributed in the hope that it will be useful,  * but WITHOUT ANY WARRANTY; without even the implied warranty of  * MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the  * GNU General Public License for more details.  *  * You should have received a copy of the GNU General Public License  * along with this program; if not, write to the Free Software  * Foundation, Inc., 59 Temple Place - Suite 330, Boston, MA 02111-1307, USA.  */
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
file|"libgimpcolor/gimpcolor.h"
end_include

begin_include
include|#
directive|include
file|"gegl-types.h"
end_include

begin_include
include|#
directive|include
file|"gimpcolorizeconfig.h"
end_include

begin_include
include|#
directive|include
file|"gimpoperationcolorize.h"
end_include

begin_function_decl
specifier|static
name|gboolean
name|gimp_operation_colorize_process
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
name|GeglRectangle
modifier|*
name|roi
parameter_list|)
function_decl|;
end_function_decl

begin_macro
DECL|function|G_DEFINE_TYPE (GimpOperationColorize,gimp_operation_colorize,GIMP_TYPE_OPERATION_POINT_FILTER)
name|G_DEFINE_TYPE
argument_list|(
argument|GimpOperationColorize
argument_list|,
argument|gimp_operation_colorize
argument_list|,
argument|GIMP_TYPE_OPERATION_POINT_FILTER
argument_list|)
end_macro

begin_define
DECL|macro|parent_class
define|#
directive|define
name|parent_class
value|gimp_operation_colorize_parent_class
end_define

begin_function
specifier|static
name|void
name|gimp_operation_colorize_class_init
parameter_list|(
name|GimpOperationColorizeClass
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
name|operation_class
operator|->
name|name
operator|=
literal|"gimp-colorize"
expr_stmt|;
name|operation_class
operator|->
name|categories
operator|=
literal|"color"
expr_stmt|;
name|operation_class
operator|->
name|description
operator|=
literal|"GIMP Colorize operation"
expr_stmt|;
name|point_class
operator|->
name|process
operator|=
name|gimp_operation_colorize_process
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
name|GIMP_TYPE_COLORIZE_CONFIG
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
DECL|function|gimp_operation_colorize_init (GimpOperationColorize * self)
name|gimp_operation_colorize_init
parameter_list|(
name|GimpOperationColorize
modifier|*
name|self
parameter_list|)
block|{ }
end_function

begin_function
specifier|static
name|gboolean
DECL|function|gimp_operation_colorize_process (GeglOperation * operation,void * in_buf,void * out_buf,glong samples,GeglRectangle * roi)
name|gimp_operation_colorize_process
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
name|GeglRectangle
modifier|*
name|roi
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
name|GimpColorizeConfig
modifier|*
name|config
init|=
name|GIMP_COLORIZE_CONFIG
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
name|GimpHSL
name|hsl
decl_stmt|;
if|if
condition|(
operator|!
name|config
condition|)
return|return
name|FALSE
return|;
name|hsl
operator|.
name|h
operator|=
name|config
operator|->
name|hue
expr_stmt|;
name|hsl
operator|.
name|s
operator|=
name|config
operator|->
name|saturation
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
name|gfloat
name|lum
init|=
name|GIMP_RGB_LUMINANCE
argument_list|(
name|src
index|[
name|RED_PIX
index|]
argument_list|,
name|src
index|[
name|GREEN_PIX
index|]
argument_list|,
name|src
index|[
name|BLUE_PIX
index|]
argument_list|)
decl_stmt|;
if|if
condition|(
name|config
operator|->
name|lightness
operator|>
literal|0
condition|)
block|{
name|lum
operator|=
name|lum
operator|*
operator|(
literal|1.0
operator|-
name|config
operator|->
name|lightness
operator|)
expr_stmt|;
name|lum
operator|+=
literal|1.0
operator|-
operator|(
literal|1.0
operator|-
name|config
operator|->
name|lightness
operator|)
expr_stmt|;
block|}
elseif|else
if|if
condition|(
name|config
operator|->
name|lightness
operator|<
literal|0
condition|)
block|{
name|lum
operator|=
name|lum
operator|*
operator|(
name|config
operator|->
name|lightness
operator|+
literal|1.0
operator|)
expr_stmt|;
block|}
name|hsl
operator|.
name|l
operator|=
name|lum
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
comment|/*  the code in base/colorize.c would multiply r,b,g with lum,        *  but this is a bug since it should multiply with 255. We        *  don't repeat this bug here (this is the reason why the gegl        *  colorize is brighter than the legacy one).        */
name|dest
index|[
name|RED_PIX
index|]
operator|=
name|rgb
operator|.
name|r
expr_stmt|;
comment|/* * lum; */
name|dest
index|[
name|GREEN_PIX
index|]
operator|=
name|rgb
operator|.
name|g
expr_stmt|;
comment|/* * lum; */
name|dest
index|[
name|BLUE_PIX
index|]
operator|=
name|rgb
operator|.
name|b
expr_stmt|;
comment|/* * lum */
empty_stmt|;
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

