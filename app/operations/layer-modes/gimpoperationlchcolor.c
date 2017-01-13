begin_unit|revision:0.9.5;language:C;cregit-version:0.0.1
begin_comment
comment|/* GIMP - The GNU Image Manipulation Program  * Copyright (C) 1995 Spencer Kimball and Peter Mattis  *  * gimpoperationlchcolor.c  * Copyright (C) 2015 Elle Stone<ellestone@ninedegreesbelow.com>  *                    Massimo Valentini<mvalentini@src.gnome.org>  *                    Thomas Manni<thomas.manni@free.fr>  *               2017 Ãyvind KolÃ¥s<pippin@gimp.org>  *  * This program is free software: you can redistribute it and/or modify  * it under the terms of the GNU General Public License as published by  * the Free Software Foundation; either version 3 of the License, or  * (at your option) any later version.  *  * This program is distributed in the hope that it will be useful,  * but WITHOUT ANY WARRANTY; without even the implied warranty of  * MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the  * GNU General Public License for more details.  *  * You should have received a copy of the GNU General Public License  * along with this program.  If not, see<http://www.gnu.org/licenses/>.  */
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
file|"../operations-types.h"
end_include

begin_include
include|#
directive|include
file|"gimpoperationlchcolor.h"
end_include

begin_function_decl
specifier|static
name|gboolean
name|gimp_operation_lch_color_process
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
DECL|function|G_DEFINE_TYPE (GimpOperationLchColor,gimp_operation_lch_color,GIMP_TYPE_OPERATION_POINT_LAYER_MODE)
name|G_DEFINE_TYPE
argument_list|(
argument|GimpOperationLchColor
argument_list|,
argument|gimp_operation_lch_color
argument_list|,
argument|GIMP_TYPE_OPERATION_POINT_LAYER_MODE
argument_list|)
end_macro

begin_define
DECL|macro|parent_class
define|#
directive|define
name|parent_class
value|gimp_operation_lch_color_parent_class
end_define

begin_function
specifier|static
name|void
name|gimp_operation_lch_color_class_init
parameter_list|(
name|GimpOperationLchColorClass
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
name|operation_class
operator|->
name|want_in_place
operator|=
name|FALSE
expr_stmt|;
name|gegl_operation_class_set_keys
argument_list|(
name|operation_class
argument_list|,
literal|"name"
argument_list|,
literal|"gimp:lch-color"
argument_list|,
literal|"description"
argument_list|,
literal|"GIMP LCH color mode operation"
argument_list|,
name|NULL
argument_list|)
expr_stmt|;
name|point_class
operator|->
name|process
operator|=
name|gimp_operation_lch_color_process
expr_stmt|;
block|}
end_function

begin_function
specifier|static
name|void
DECL|function|gimp_operation_lch_color_init (GimpOperationLchColor * self)
name|gimp_operation_lch_color_init
parameter_list|(
name|GimpOperationLchColor
modifier|*
name|self
parameter_list|)
block|{ }
end_function

begin_function
specifier|static
name|gboolean
DECL|function|gimp_operation_lch_color_process (GeglOperation * operation,void * in_buf,void * aux_buf,void * aux2_buf,void * out_buf,glong samples,const GeglRectangle * roi,gint level)
name|gimp_operation_lch_color_process
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
name|GimpOperationPointLayerMode
modifier|*
name|gimp_op
init|=
name|GIMP_OPERATION_POINT_LAYER_MODE
argument_list|(
name|operation
argument_list|)
decl_stmt|;
name|gfloat
name|opacity
init|=
name|gimp_op
operator|->
name|opacity
decl_stmt|;
name|gboolean
name|linear
init|=
name|gimp_op
operator|->
name|linear
decl_stmt|;
return|return
operator|(
name|linear
condition|?
name|gimp_operation_lch_color_process_pixels_linear
else|:
name|gimp_operation_lch_color_process_pixels
operator|)
operator|(
name|in_buf
operator|,
name|aux_buf
operator|,
name|aux2_buf
operator|,
name|out_buf
operator|,
name|opacity
operator|,
name|samples
operator|,
name|roi
operator|,
name|level
operator|)
return|;
block|}
end_function

begin_function
specifier|static
name|void
DECL|function|color_pre_process (const Babl * format,const gfloat * in,const gfloat * layer,gfloat * out,glong samples)
name|color_pre_process
parameter_list|(
specifier|const
name|Babl
modifier|*
name|format
parameter_list|,
specifier|const
name|gfloat
modifier|*
name|in
parameter_list|,
specifier|const
name|gfloat
modifier|*
name|layer
parameter_list|,
name|gfloat
modifier|*
name|out
parameter_list|,
name|glong
name|samples
parameter_list|)
block|{
name|gfloat
name|tmp
index|[
literal|4
operator|*
name|samples
index|]
decl_stmt|,
modifier|*
name|layer_lab
init|=
name|tmp
decl_stmt|;
name|gint
name|i
decl_stmt|;
name|babl_process
argument_list|(
name|babl_fish
argument_list|(
name|format
argument_list|,
literal|"CIE L alpha float"
argument_list|)
argument_list|,
name|in
argument_list|,
operator|&
name|out
index|[
literal|2
operator|*
name|samples
index|]
argument_list|,
name|samples
argument_list|)
expr_stmt|;
name|babl_process
argument_list|(
name|babl_fish
argument_list|(
name|format
argument_list|,
literal|"CIE Lab alpha float"
argument_list|)
argument_list|,
name|layer
argument_list|,
name|layer_lab
argument_list|,
name|samples
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
name|samples
condition|;
operator|++
name|i
control|)
block|{
name|out
index|[
literal|4
operator|*
name|i
operator|+
literal|0
index|]
operator|=
name|out
index|[
literal|2
operator|*
name|samples
operator|+
literal|2
operator|*
name|i
operator|+
literal|0
index|]
expr_stmt|;
name|out
index|[
literal|4
operator|*
name|i
operator|+
literal|1
index|]
operator|=
name|layer_lab
index|[
literal|4
operator|*
name|i
operator|+
literal|1
index|]
expr_stmt|;
name|out
index|[
literal|4
operator|*
name|i
operator|+
literal|2
index|]
operator|=
name|layer_lab
index|[
literal|4
operator|*
name|i
operator|+
literal|2
index|]
expr_stmt|;
name|out
index|[
literal|4
operator|*
name|i
operator|+
literal|3
index|]
operator|=
name|out
index|[
literal|2
operator|*
name|samples
operator|+
literal|2
operator|*
name|i
operator|+
literal|1
index|]
expr_stmt|;
block|}
name|babl_process
argument_list|(
name|babl_fish
argument_list|(
literal|"CIE Lab alpha float"
argument_list|,
name|format
argument_list|)
argument_list|,
name|out
argument_list|,
name|out
argument_list|,
name|samples
argument_list|)
expr_stmt|;
block|}
end_function

begin_function
specifier|static
name|void
DECL|function|color_post_process (const gfloat * in,const gfloat * layer,const gfloat * mask,gfloat * out,gfloat opacity,glong samples)
name|color_post_process
parameter_list|(
specifier|const
name|gfloat
modifier|*
name|in
parameter_list|,
specifier|const
name|gfloat
modifier|*
name|layer
parameter_list|,
specifier|const
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
parameter_list|)
block|{
while|while
condition|(
name|samples
operator|--
condition|)
block|{
name|gfloat
name|comp_alpha
decl_stmt|,
name|new_alpha
decl_stmt|;
name|comp_alpha
operator|=
name|layer
index|[
name|ALPHA
index|]
operator|*
name|opacity
expr_stmt|;
if|if
condition|(
name|mask
condition|)
name|comp_alpha
operator|*=
operator|*
name|mask
operator|++
expr_stmt|;
name|new_alpha
operator|=
name|in
index|[
name|ALPHA
index|]
operator|+
operator|(
literal|1.0f
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
name|gfloat
name|ratio
init|=
name|comp_alpha
operator|/
name|new_alpha
decl_stmt|;
name|out
index|[
name|RED
index|]
operator|=
name|out
index|[
name|RED
index|]
operator|*
name|ratio
operator|+
name|in
index|[
name|RED
index|]
operator|*
operator|(
literal|1.0f
operator|-
name|ratio
operator|)
expr_stmt|;
name|out
index|[
name|GREEN
index|]
operator|=
name|out
index|[
name|GREEN
index|]
operator|*
name|ratio
operator|+
name|in
index|[
name|GREEN
index|]
operator|*
operator|(
literal|1.0f
operator|-
name|ratio
operator|)
expr_stmt|;
name|out
index|[
name|BLUE
index|]
operator|=
name|out
index|[
name|BLUE
index|]
operator|*
name|ratio
operator|+
name|in
index|[
name|BLUE
index|]
operator|*
operator|(
literal|1.0f
operator|-
name|ratio
operator|)
expr_stmt|;
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
block|}
block|}
end_function

begin_function
name|gboolean
DECL|function|gimp_operation_lch_color_process_pixels_linear (gfloat * in,gfloat * layer,gfloat * mask,gfloat * out,gfloat opacity,glong samples,const GeglRectangle * roi,gint level)
name|gimp_operation_lch_color_process_pixels_linear
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
name|color_pre_process
argument_list|(
name|babl_format
argument_list|(
literal|"RGBA float"
argument_list|)
argument_list|,
name|in
argument_list|,
name|layer
argument_list|,
name|out
argument_list|,
name|samples
argument_list|)
expr_stmt|;
name|color_post_process
argument_list|(
name|in
argument_list|,
name|layer
argument_list|,
name|mask
argument_list|,
name|out
argument_list|,
name|opacity
argument_list|,
name|samples
argument_list|)
expr_stmt|;
return|return
name|TRUE
return|;
block|}
end_function

begin_function
name|gboolean
DECL|function|gimp_operation_lch_color_process_pixels (gfloat * in,gfloat * layer,gfloat * mask,gfloat * out,gfloat opacity,glong samples,const GeglRectangle * roi,gint level)
name|gimp_operation_lch_color_process_pixels
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
name|color_pre_process
argument_list|(
name|babl_format
argument_list|(
literal|"R'G'B'A float"
argument_list|)
argument_list|,
name|in
argument_list|,
name|layer
argument_list|,
name|out
argument_list|,
name|samples
argument_list|)
expr_stmt|;
name|color_post_process
argument_list|(
name|in
argument_list|,
name|layer
argument_list|,
name|mask
argument_list|,
name|out
argument_list|,
name|opacity
argument_list|,
name|samples
argument_list|)
expr_stmt|;
return|return
name|TRUE
return|;
block|}
end_function

end_unit

