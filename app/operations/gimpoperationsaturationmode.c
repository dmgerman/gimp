begin_unit|revision:0.9.5;language:C;cregit-version:0.0.1
begin_comment
comment|/* GIMP - The GNU Image Manipulation Program  * Copyright (C) 1995 Spencer Kimball and Peter Mattis  *  * gimpoperationsaturationmode.c  * Copyright (C) 2008 Michael Natterer<mitch@gimp.org>  *               2012 Ville Sokk<ville.sokk@gmail.com>  *  * This program is free software: you can redistribute it and/or modify  * it under the terms of the GNU General Public License as published by  * the Free Software Foundation; either version 3 of the License, or  * (at your option) any later version.  *  * This program is distributed in the hope that it will be useful,  * but WITHOUT ANY WARRANTY; without even the implied warranty of  * MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the  * GNU General Public License for more details.  *  * You should have received a copy of the GNU General Public License  * along with this program.  If not, see<http://www.gnu.org/licenses/>.  */
end_comment

begin_include
include|#
directive|include
file|"config.h"
end_include

begin_include
include|#
directive|include
file|<gegl-plugin.h>
end_include

begin_include
include|#
directive|include
file|<cairo.h>
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
file|"operations-types.h"
end_include

begin_include
include|#
directive|include
file|"gimpoperationsaturationmode.h"
end_include

begin_function_decl
specifier|static
name|gboolean
name|gimp_operation_saturation_mode_process
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
name|aux_buf
parameter_list|,
name|void
modifier|*
name|aux2_buf
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
DECL|function|G_DEFINE_TYPE (GimpOperationSaturationMode,gimp_operation_saturation_mode,GIMP_TYPE_OPERATION_POINT_LAYER_MODE)
name|G_DEFINE_TYPE
argument_list|(
argument|GimpOperationSaturationMode
argument_list|,
argument|gimp_operation_saturation_mode
argument_list|,
argument|GIMP_TYPE_OPERATION_POINT_LAYER_MODE
argument_list|)
end_macro

begin_function
specifier|static
name|void
name|gimp_operation_saturation_mode_class_init
parameter_list|(
name|GimpOperationSaturationModeClass
modifier|*
name|klass
parameter_list|)
block|{
name|GeglOperationClass
modifier|*
name|operation_class
decl_stmt|;
name|GeglOperationPointComposer3Class
modifier|*
name|point_class
decl_stmt|;
name|operation_class
operator|=
name|GEGL_OPERATION_CLASS
argument_list|(
name|klass
argument_list|)
expr_stmt|;
name|point_class
operator|=
name|GEGL_OPERATION_POINT_COMPOSER3_CLASS
argument_list|(
name|klass
argument_list|)
expr_stmt|;
name|gegl_operation_class_set_keys
argument_list|(
name|operation_class
argument_list|,
literal|"name"
argument_list|,
literal|"gimp:saturation-mode"
argument_list|,
literal|"description"
argument_list|,
literal|"GIMP saturation mode operation"
argument_list|,
name|NULL
argument_list|)
expr_stmt|;
name|point_class
operator|->
name|process
operator|=
name|gimp_operation_saturation_mode_process
expr_stmt|;
block|}
end_function

begin_function
specifier|static
name|void
DECL|function|gimp_operation_saturation_mode_init (GimpOperationSaturationMode * self)
name|gimp_operation_saturation_mode_init
parameter_list|(
name|GimpOperationSaturationMode
modifier|*
name|self
parameter_list|)
block|{ }
end_function

begin_function
specifier|static
name|gboolean
DECL|function|gimp_operation_saturation_mode_process (GeglOperation * operation,void * in_buf,void * aux_buf,void * aux2_buf,void * out_buf,glong samples,const GeglRectangle * roi,gint level)
name|gimp_operation_saturation_mode_process
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
name|aux_buf
parameter_list|,
name|void
modifier|*
name|aux2_buf
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
name|gfloat
name|opacity
init|=
name|GIMP_OPERATION_POINT_LAYER_MODE
argument_list|(
name|operation
argument_list|)
operator|->
name|opacity
decl_stmt|;
return|return
name|gimp_operation_saturation_mode_process_pixels
argument_list|(
name|in_buf
argument_list|,
name|aux_buf
argument_list|,
name|aux2_buf
argument_list|,
name|out_buf
argument_list|,
name|opacity
argument_list|,
name|samples
argument_list|,
name|roi
argument_list|,
name|level
argument_list|)
return|;
block|}
end_function

begin_function
name|gboolean
DECL|function|gimp_operation_saturation_mode_process_pixels (gfloat * in,gfloat * layer,gfloat * mask,gfloat * out,gfloat opacity,glong samples,const GeglRectangle * roi,gint level)
name|gimp_operation_saturation_mode_process_pixels
parameter_list|(
name|gfloat
modifier|*
name|in
parameter_list|,
name|gfloat
modifier|*
name|layer
parameter_list|,
name|gfloat
modifier|*
name|mask
parameter_list|,
name|gfloat
modifier|*
name|out
parameter_list|,
name|gfloat
name|opacity
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
specifier|const
name|gboolean
name|has_mask
init|=
name|mask
operator|!=
name|NULL
decl_stmt|;
while|while
condition|(
name|samples
operator|--
condition|)
block|{
name|GimpHSV
name|layer_hsv
decl_stmt|,
name|out_hsv
decl_stmt|;
name|GimpRGB
name|layer_rgb
init|=
block|{
name|layer
index|[
literal|0
index|]
block|,
name|layer
index|[
literal|1
index|]
block|,
name|layer
index|[
literal|2
index|]
block|}
decl_stmt|;
name|GimpRGB
name|out_rgb
init|=
block|{
name|in
index|[
literal|0
index|]
block|,
name|in
index|[
literal|1
index|]
block|,
name|in
index|[
literal|2
index|]
block|}
decl_stmt|;
name|gfloat
name|comp_alpha
decl_stmt|,
name|new_alpha
decl_stmt|;
name|comp_alpha
operator|=
name|MIN
argument_list|(
name|in
index|[
name|ALPHA
index|]
argument_list|,
name|layer
index|[
name|ALPHA
index|]
argument_list|)
operator|*
name|opacity
expr_stmt|;
if|if
condition|(
name|has_mask
condition|)
name|comp_alpha
operator|*=
operator|*
name|mask
expr_stmt|;
name|new_alpha
operator|=
name|in
index|[
name|ALPHA
index|]
operator|+
operator|(
literal|1.0
operator|-
name|in
index|[
name|ALPHA
index|]
operator|)
operator|*
name|comp_alpha
expr_stmt|;
if|if
condition|(
name|comp_alpha
operator|&&
name|new_alpha
condition|)
block|{
name|gint
name|b
decl_stmt|;
name|gfloat
name|out_tmp
index|[
literal|3
index|]
decl_stmt|;
name|gfloat
name|ratio
init|=
name|comp_alpha
operator|/
name|new_alpha
decl_stmt|;
name|gimp_rgb_to_hsv
argument_list|(
operator|&
name|layer_rgb
argument_list|,
operator|&
name|layer_hsv
argument_list|)
expr_stmt|;
name|gimp_rgb_to_hsv
argument_list|(
operator|&
name|out_rgb
argument_list|,
operator|&
name|out_hsv
argument_list|)
expr_stmt|;
name|out_hsv
operator|.
name|s
operator|=
name|layer_hsv
operator|.
name|s
expr_stmt|;
name|gimp_hsv_to_rgb
argument_list|(
operator|&
name|out_hsv
argument_list|,
operator|&
name|out_rgb
argument_list|)
expr_stmt|;
name|out_tmp
index|[
literal|0
index|]
operator|=
name|out_rgb
operator|.
name|r
expr_stmt|;
name|out_tmp
index|[
literal|1
index|]
operator|=
name|out_rgb
operator|.
name|g
expr_stmt|;
name|out_tmp
index|[
literal|2
index|]
operator|=
name|out_rgb
operator|.
name|b
expr_stmt|;
for|for
control|(
name|b
operator|=
name|RED
init|;
name|b
operator|<
name|ALPHA
condition|;
name|b
operator|++
control|)
block|{
name|out
index|[
name|b
index|]
operator|=
name|out_tmp
index|[
name|b
index|]
operator|*
name|ratio
operator|+
name|in
index|[
name|b
index|]
operator|*
operator|(
literal|1.0
operator|-
name|ratio
operator|)
expr_stmt|;
block|}
block|}
else|else
block|{
name|gint
name|b
decl_stmt|;
for|for
control|(
name|b
operator|=
name|RED
init|;
name|b
operator|<
name|ALPHA
condition|;
name|b
operator|++
control|)
block|{
name|out
index|[
name|b
index|]
operator|=
name|in
index|[
name|b
index|]
expr_stmt|;
block|}
block|}
name|out
index|[
name|ALPHA
index|]
operator|=
name|in
index|[
name|ALPHA
index|]
expr_stmt|;
name|in
operator|+=
literal|4
expr_stmt|;
name|layer
operator|+=
literal|4
expr_stmt|;
name|out
operator|+=
literal|4
expr_stmt|;
if|if
condition|(
name|has_mask
condition|)
name|mask
operator|++
expr_stmt|;
block|}
return|return
name|TRUE
return|;
block|}
end_function

end_unit

