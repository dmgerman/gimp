begin_unit|revision:0.9.5;language:C;cregit-version:0.0.1
begin_comment
comment|/* GIMP - The GNU Image Manipulation Program  * Copyright (C) 1995 Spencer Kimball and Peter Mattis  *  * gimpoperationbrightnesscontrast.c  * Copyright (C) 2012 Michael Natterer<mitch@gimp.org>  *  * This program is free software: you can redistribute it and/or modify  * it under the terms of the GNU General Public License as published by  * the Free Software Foundation; either version 3 of the License, or  * (at your option) any later version.  *  * This program is distributed in the hope that it will be useful,  * but WITHOUT ANY WARRANTY; without even the implied warranty of  * MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the  * GNU General Public License for more details.  *  * You should have received a copy of the GNU General Public License  * along with this program.  If not, see<http://www.gnu.org/licenses/>.  */
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
file|"gimpbrightnesscontrastconfig.h"
end_include

begin_include
include|#
directive|include
file|"gimpoperationbrightnesscontrast.h"
end_include

begin_function_decl
specifier|static
name|gboolean
name|gimp_operation_brightness_contrast_process
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
DECL|function|G_DEFINE_TYPE (GimpOperationBrightnessContrast,gimp_operation_brightness_contrast,GIMP_TYPE_OPERATION_POINT_FILTER)
name|G_DEFINE_TYPE
argument_list|(
argument|GimpOperationBrightnessContrast
argument_list|,
argument|gimp_operation_brightness_contrast
argument_list|,
argument|GIMP_TYPE_OPERATION_POINT_FILTER
argument_list|)
end_macro

begin_define
DECL|macro|parent_class
define|#
directive|define
name|parent_class
value|gimp_operation_brightness_contrast_parent_class
end_define

begin_function
specifier|static
name|void
name|gimp_operation_brightness_contrast_class_init
parameter_list|(
name|GimpOperationBrightnessContrastClass
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
literal|"gimp:brightness-contrast"
argument_list|,
literal|"categories"
argument_list|,
literal|"color"
argument_list|,
literal|"description"
argument_list|,
literal|"GIMP Brightness-Contrast operation"
argument_list|,
name|NULL
argument_list|)
expr_stmt|;
name|point_class
operator|->
name|process
operator|=
name|gimp_operation_brightness_contrast_process
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
name|GIMP_TYPE_BRIGHTNESS_CONTRAST_CONFIG
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
DECL|function|gimp_operation_brightness_contrast_init (GimpOperationBrightnessContrast * self)
name|gimp_operation_brightness_contrast_init
parameter_list|(
name|GimpOperationBrightnessContrast
modifier|*
name|self
parameter_list|)
block|{ }
end_function

begin_function
specifier|static
specifier|inline
name|gfloat
DECL|function|gimp_operation_brightness_contrast_map (gfloat value,gdouble brightness,gdouble slant)
name|gimp_operation_brightness_contrast_map
parameter_list|(
name|gfloat
name|value
parameter_list|,
name|gdouble
name|brightness
parameter_list|,
name|gdouble
name|slant
parameter_list|)
block|{
comment|/* apply brightness */
if|if
condition|(
name|brightness
operator|<
literal|0.0
condition|)
name|value
operator|=
name|value
operator|*
operator|(
literal|1.0
operator|+
name|brightness
operator|)
expr_stmt|;
else|else
name|value
operator|=
name|value
operator|+
operator|(
operator|(
literal|1.0
operator|-
name|value
operator|)
operator|*
name|brightness
operator|)
expr_stmt|;
name|value
operator|=
operator|(
name|value
operator|-
literal|0.5
operator|)
operator|*
name|slant
operator|+
literal|0.5
expr_stmt|;
return|return
name|value
return|;
block|}
end_function

begin_function
specifier|static
name|gboolean
DECL|function|gimp_operation_brightness_contrast_process (GeglOperation * operation,void * in_buf,void * out_buf,glong samples,const GeglRectangle * roi,gint level)
name|gimp_operation_brightness_contrast_process
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
name|GimpBrightnessContrastConfig
modifier|*
name|config
init|=
name|GIMP_BRIGHTNESS_CONTRAST_CONFIG
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
name|gdouble
name|brightness
decl_stmt|;
name|gdouble
name|slant
decl_stmt|;
if|if
condition|(
operator|!
name|config
condition|)
return|return
name|FALSE
return|;
name|brightness
operator|=
name|config
operator|->
name|brightness
operator|/
literal|2.0
expr_stmt|;
name|slant
operator|=
name|tan
argument_list|(
operator|(
name|config
operator|->
name|contrast
operator|+
literal|1
operator|)
operator|*
name|G_PI_4
argument_list|)
expr_stmt|;
while|while
condition|(
name|samples
operator|--
condition|)
block|{
name|dest
index|[
name|RED
index|]
operator|=
name|gimp_operation_brightness_contrast_map
argument_list|(
name|src
index|[
name|RED
index|]
argument_list|,
name|brightness
argument_list|,
name|slant
argument_list|)
expr_stmt|;
name|dest
index|[
name|GREEN
index|]
operator|=
name|gimp_operation_brightness_contrast_map
argument_list|(
name|src
index|[
name|GREEN
index|]
argument_list|,
name|brightness
argument_list|,
name|slant
argument_list|)
expr_stmt|;
name|dest
index|[
name|BLUE
index|]
operator|=
name|gimp_operation_brightness_contrast_map
argument_list|(
name|src
index|[
name|BLUE
index|]
argument_list|,
name|brightness
argument_list|,
name|slant
argument_list|)
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

