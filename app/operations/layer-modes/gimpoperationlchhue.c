begin_unit|revision:0.9.5;language:C;cregit-version:0.0.1
begin_comment
comment|/* GIMP - The GNU Image Manipulation Program  * Copyright (C) 1995 Spencer Kimball and Peter Mattis  *  * gimpoperationlchhue.c  * Copyright (C) 2015 Elle Stone<ellestone@ninedegreesbelow.com>  *                    Massimo Valentini<mvalentini@src.gnome.org>  *                    Thomas Manni<thomas.manni@free.fr>  *               2017 Ãyvind KolÃ¥s<pippin@gimp.org>  *  * This program is free software: you can redistribute it and/or modify  * it under the terms of the GNU General Public License as published by  * the Free Software Foundation; either version 3 of the License, or  * (at your option) any later version.  *  * This program is distributed in the hope that it will be useful,  * but WITHOUT ANY WARRANTY; without even the implied warranty of  * MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the  * GNU General Public License for more details.  *  * You should have received a copy of the GNU General Public License  * along with this program.  If not, see<http://www.gnu.org/licenses/>.  */
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
file|<math.h>
end_include

begin_include
include|#
directive|include
file|"../operations-types.h"
end_include

begin_include
include|#
directive|include
file|"gimpoperationlchhue.h"
end_include

begin_function_decl
specifier|static
name|gboolean
name|gimp_operation_lch_hue_process
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
DECL|function|G_DEFINE_TYPE (GimpOperationLchHue,gimp_operation_lch_hue,GIMP_TYPE_OPERATION_POINT_LAYER_MODE)
name|G_DEFINE_TYPE
argument_list|(
argument|GimpOperationLchHue
argument_list|,
argument|gimp_operation_lch_hue
argument_list|,
argument|GIMP_TYPE_OPERATION_POINT_LAYER_MODE
argument_list|)
end_macro

begin_define
DECL|macro|parent_class
define|#
directive|define
name|parent_class
value|gimp_operation_lch_hue_parent_class
end_define

begin_function
specifier|static
name|void
name|gimp_operation_lch_hue_class_init
parameter_list|(
name|GimpOperationLchHueClass
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
literal|"gimp:lch-hue"
argument_list|,
literal|"description"
argument_list|,
literal|"GIMP LCH hue mode operation"
argument_list|,
name|NULL
argument_list|)
expr_stmt|;
name|point_class
operator|->
name|process
operator|=
name|gimp_operation_lch_hue_process
expr_stmt|;
block|}
end_function

begin_function
specifier|static
name|void
DECL|function|gimp_operation_lch_hue_init (GimpOperationLchHue * self)
name|gimp_operation_lch_hue_init
parameter_list|(
name|GimpOperationLchHue
modifier|*
name|self
parameter_list|)
block|{ }
end_function

begin_function
specifier|static
name|gboolean
DECL|function|gimp_operation_lch_hue_process (GeglOperation * operation,void * in_buf,void * aux_buf,void * aux2_buf,void * out_buf,glong samples,const GeglRectangle * roi,gint level)
name|gimp_operation_lch_hue_process
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
name|gimp_operation_lch_hue_process_pixels_linear
else|:
name|gimp_operation_lch_hue_process_pixels
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
DECL|function|hue_pre_process (const Babl * format,const gfloat * in,const gfloat * layer,gfloat * out,glong samples)
name|hue_pre_process
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
name|gint
name|i
decl_stmt|;
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
name|babl_process
argument_list|(
name|babl_fish
argument_list|(
name|format
argument_list|,
literal|"CIE Lab alpha float"
argument_list|)
argument_list|,
name|in
argument_list|,
name|out
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
name|gfloat
name|A2
init|=
name|layer_lab
index|[
literal|4
operator|*
name|i
operator|+
literal|1
index|]
decl_stmt|;
name|gfloat
name|B2
init|=
name|layer_lab
index|[
literal|4
operator|*
name|i
operator|+
literal|2
index|]
decl_stmt|;
name|gfloat
name|c2
init|=
name|hypotf
argument_list|(
name|A2
argument_list|,
name|B2
argument_list|)
decl_stmt|;
if|if
condition|(
name|c2
operator|>
literal|0.1f
condition|)
block|{
name|gfloat
name|A1
init|=
name|out
index|[
literal|4
operator|*
name|i
operator|+
literal|1
index|]
decl_stmt|;
name|gfloat
name|B1
init|=
name|out
index|[
literal|4
operator|*
name|i
operator|+
literal|2
index|]
decl_stmt|;
name|gfloat
name|c1
init|=
name|hypotf
argument_list|(
name|A1
argument_list|,
name|B1
argument_list|)
decl_stmt|;
name|gfloat
name|A
init|=
name|c1
operator|*
name|A2
operator|/
name|c2
decl_stmt|;
name|gfloat
name|B
init|=
name|c1
operator|*
name|B2
operator|/
name|c2
decl_stmt|;
name|out
index|[
literal|4
operator|*
name|i
operator|+
literal|1
index|]
operator|=
name|A
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
name|B
expr_stmt|;
block|}
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
name|gboolean
DECL|function|gimp_operation_lch_hue_process_pixels_linear (gfloat * in,gfloat * layer,gfloat * mask,gfloat * out,gfloat opacity,glong samples,const GeglRectangle * roi,gint level)
name|gimp_operation_lch_hue_process_pixels_linear
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
specifier|static
specifier|const
name|Babl
modifier|*
name|from_fish
init|=
name|NULL
decl_stmt|;
specifier|static
specifier|const
name|Babl
modifier|*
name|to_fish
init|=
name|NULL
decl_stmt|;
if|if
condition|(
operator|!
name|from_fish
condition|)
name|from_fish
operator|=
name|babl_fish
argument_list|(
literal|"RGBA float"
argument_list|,
literal|"CIE Lab alpha float"
argument_list|)
expr_stmt|;
if|if
condition|(
operator|!
name|to_fish
condition|)
name|to_fish
operator|=
name|babl_fish
argument_list|(
literal|"CIE Lab alpha float"
argument_list|,
literal|"RGBA float"
argument_list|)
expr_stmt|;
name|hue_pre_process
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
name|gimp_operation_layer_composite
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
DECL|function|gimp_operation_lch_hue_process_pixels (gfloat * in,gfloat * layer,gfloat * mask,gfloat * out,gfloat opacity,glong samples,const GeglRectangle * roi,gint level)
name|gimp_operation_lch_hue_process_pixels
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
specifier|static
specifier|const
name|Babl
modifier|*
name|from_fish
init|=
name|NULL
decl_stmt|;
specifier|static
specifier|const
name|Babl
modifier|*
name|to_fish
init|=
name|NULL
decl_stmt|;
if|if
condition|(
operator|!
name|from_fish
condition|)
name|from_fish
operator|=
name|babl_fish
argument_list|(
literal|"R'G'B'A float"
argument_list|,
literal|"CIE Lab alpha float"
argument_list|)
expr_stmt|;
if|if
condition|(
operator|!
name|to_fish
condition|)
name|to_fish
operator|=
name|babl_fish
argument_list|(
literal|"CIE Lab alpha float"
argument_list|,
literal|"R'G'B'A float"
argument_list|)
expr_stmt|;
name|hue_pre_process
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
name|gimp_operation_layer_composite
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

