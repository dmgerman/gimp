begin_unit|revision:0.9.5;language:C;cregit-version:0.0.1
begin_comment
comment|/* GIMP - The GNU Image Manipulation Program  * Copyright (C) 2010 Ãyvind KolÃ¥s<pippin@gimp.org>  *               2012 Ville Sokk<ville.sokk@gmail.com>  *  * This program is free software: you can redistribute it and/or modify  * it under the terms of the GNU General Public License as published by  * the Free Software Foundation; either version 3 of the License, or  * (at your option) any later version.  *  * This program is distributed in the hope that it will be useful,  * but WITHOUT ANY WARRANTY; without even the implied warranty of  * MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the  * GNU General Public License for more details.  *  * You should have received a copy of the GNU General Public License  * along with this program.  If not, see<http://www.gnu.org/licenses/>.  */
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
file|<gegl-plugin.h>
end_include

begin_include
include|#
directive|include
file|"libgimpmath/gimpmath.h"
end_include

begin_include
include|#
directive|include
file|"app/operations/gimp-operations.h"
end_include

begin_define
DECL|macro|DATA_DIR
define|#
directive|define
name|DATA_DIR
value|"data"
end_define

begin_define
DECL|macro|OUTPUT_DIR
define|#
directive|define
name|OUTPUT_DIR
value|"output"
end_define

begin_function
specifier|static
specifier|inline
name|gdouble
DECL|function|square (gdouble x)
name|square
parameter_list|(
name|gdouble
name|x
parameter_list|)
block|{
return|return
name|x
operator|*
name|x
return|;
block|}
end_function

begin_function
specifier|static
name|gdouble
DECL|function|cie76 (gfloat * src1,gfloat * src2)
name|cie76
parameter_list|(
name|gfloat
modifier|*
name|src1
parameter_list|,
name|gfloat
modifier|*
name|src2
parameter_list|)
block|{
return|return
name|sqrt
argument_list|(
name|square
argument_list|(
name|src1
index|[
literal|0
index|]
operator|-
name|src2
index|[
literal|0
index|]
argument_list|)
operator|+
name|square
argument_list|(
name|src1
index|[
literal|1
index|]
operator|-
name|src2
index|[
literal|1
index|]
argument_list|)
operator|+
name|square
argument_list|(
name|src1
index|[
literal|2
index|]
operator|-
name|src2
index|[
literal|2
index|]
argument_list|)
argument_list|)
return|;
block|}
end_function

begin_function
specifier|static
name|gdouble
DECL|function|cie94 (gfloat * src1,gfloat * src2)
name|cie94
parameter_list|(
name|gfloat
modifier|*
name|src1
parameter_list|,
name|gfloat
modifier|*
name|src2
parameter_list|)
block|{
name|gdouble
name|L1
decl_stmt|,
name|L2
decl_stmt|,
name|a1
decl_stmt|,
name|b1
decl_stmt|,
name|a2
decl_stmt|,
name|b2
decl_stmt|,
name|C1
decl_stmt|,
name|C2
decl_stmt|,
name|dL
decl_stmt|,
name|dC
decl_stmt|,
name|dH
decl_stmt|,
name|dE
decl_stmt|;
name|L1
operator|=
name|src1
index|[
literal|0
index|]
expr_stmt|;
name|a1
operator|=
name|src1
index|[
literal|1
index|]
expr_stmt|;
name|b1
operator|=
name|src1
index|[
literal|2
index|]
expr_stmt|;
name|L2
operator|=
name|src2
index|[
literal|0
index|]
expr_stmt|;
name|a2
operator|=
name|src2
index|[
literal|1
index|]
expr_stmt|;
name|b2
operator|=
name|src2
index|[
literal|2
index|]
expr_stmt|;
name|dL
operator|=
name|L1
operator|-
name|L2
expr_stmt|;
name|C1
operator|=
name|sqrt
argument_list|(
name|square
argument_list|(
name|a1
argument_list|)
operator|+
name|square
argument_list|(
name|b1
argument_list|)
argument_list|)
expr_stmt|;
name|C2
operator|=
name|sqrt
argument_list|(
name|square
argument_list|(
name|a2
argument_list|)
operator|+
name|square
argument_list|(
name|b2
argument_list|)
argument_list|)
expr_stmt|;
name|dC
operator|=
name|C1
operator|-
name|C2
expr_stmt|;
name|dH
operator|=
name|sqrt
argument_list|(
name|square
argument_list|(
name|a1
operator|-
name|a2
argument_list|)
operator|+
name|square
argument_list|(
name|b1
operator|-
name|b2
argument_list|)
operator|-
name|square
argument_list|(
name|dC
argument_list|)
argument_list|)
expr_stmt|;
name|dE
operator|=
name|sqrt
argument_list|(
name|square
argument_list|(
name|dL
argument_list|)
operator|+
name|square
argument_list|(
name|dC
operator|/
operator|(
literal|1
operator|+
literal|0.045
operator|*
name|C1
operator|)
argument_list|)
operator|+
name|square
argument_list|(
name|dH
operator|/
operator|(
literal|1
operator|+
literal|0.015
operator|*
name|C1
operator|)
argument_list|)
argument_list|)
expr_stmt|;
return|return
name|dE
return|;
block|}
end_function

begin_comment
comment|/*  * CIE 2000 delta E colour comparison  */
end_comment

begin_function
specifier|static
name|gdouble
DECL|function|delta_e (gfloat * src1,gfloat * src2)
name|delta_e
parameter_list|(
name|gfloat
modifier|*
name|src1
parameter_list|,
name|gfloat
modifier|*
name|src2
parameter_list|)
block|{
name|gdouble
name|L1
decl_stmt|,
name|L2
decl_stmt|,
name|a1
decl_stmt|,
name|a2
decl_stmt|,
name|b1
decl_stmt|,
name|b2
decl_stmt|,
name|La_
decl_stmt|,
name|C1
decl_stmt|,
name|C2
decl_stmt|,
name|Ca
decl_stmt|,
name|G
decl_stmt|,
name|a1_
decl_stmt|,
name|a2_
decl_stmt|,
name|C1_
decl_stmt|,
name|C2_
decl_stmt|,
name|Ca_
decl_stmt|,
name|h1_
decl_stmt|,
name|h2_
decl_stmt|,
name|Ha_
decl_stmt|,
name|T
decl_stmt|,
name|dh_
decl_stmt|,
name|dL_
decl_stmt|,
name|dC_
decl_stmt|,
name|dH_
decl_stmt|,
name|Sl
decl_stmt|,
name|Sc
decl_stmt|,
name|Sh
decl_stmt|,
name|dPhi
decl_stmt|,
name|Rc
decl_stmt|,
name|Rt
decl_stmt|,
name|dE
decl_stmt|,
name|tmp
decl_stmt|;
name|L1
operator|=
name|src1
index|[
literal|0
index|]
expr_stmt|;
name|L2
operator|=
name|src2
index|[
literal|0
index|]
expr_stmt|;
name|a1
operator|=
name|src1
index|[
literal|1
index|]
expr_stmt|;
name|a2
operator|=
name|src2
index|[
literal|1
index|]
expr_stmt|;
name|b1
operator|=
name|src1
index|[
literal|2
index|]
expr_stmt|;
name|b2
operator|=
name|src2
index|[
literal|2
index|]
expr_stmt|;
name|La_
operator|=
operator|(
name|L1
operator|+
name|L2
operator|)
operator|/
literal|2.0
expr_stmt|;
name|C1
operator|=
name|sqrt
argument_list|(
name|square
argument_list|(
name|a1
argument_list|)
operator|+
name|square
argument_list|(
name|b1
argument_list|)
argument_list|)
expr_stmt|;
name|C2
operator|=
name|sqrt
argument_list|(
name|square
argument_list|(
name|a2
argument_list|)
operator|+
name|square
argument_list|(
name|b2
argument_list|)
argument_list|)
expr_stmt|;
name|Ca
operator|=
operator|(
name|C1
operator|+
name|C2
operator|)
operator|/
literal|2.0
expr_stmt|;
name|tmp
operator|=
name|pow
argument_list|(
name|Ca
argument_list|,
literal|7
argument_list|)
expr_stmt|;
name|G
operator|=
operator|(
literal|1
operator|-
name|sqrt
argument_list|(
name|tmp
operator|/
operator|(
name|tmp
operator|+
name|pow
argument_list|(
literal|25
argument_list|,
literal|7
argument_list|)
operator|)
argument_list|)
operator|)
operator|/
literal|2.0
expr_stmt|;
name|a1_
operator|=
name|a1
operator|*
operator|(
literal|1
operator|+
name|G
operator|)
expr_stmt|;
name|a2_
operator|=
name|a2
operator|*
operator|(
literal|1
operator|+
name|G
operator|)
expr_stmt|;
name|C1_
operator|=
name|sqrt
argument_list|(
name|square
argument_list|(
name|a1_
argument_list|)
operator|+
name|square
argument_list|(
name|b1
argument_list|)
argument_list|)
expr_stmt|;
name|C2_
operator|=
name|sqrt
argument_list|(
name|square
argument_list|(
name|a2_
argument_list|)
operator|+
name|square
argument_list|(
name|b2
argument_list|)
argument_list|)
expr_stmt|;
name|Ca_
operator|=
operator|(
name|C1_
operator|+
name|C2_
operator|)
operator|/
literal|2.0
expr_stmt|;
name|tmp
operator|=
name|atan2
argument_list|(
name|b1
argument_list|,
name|a1_
argument_list|)
operator|*
literal|180
operator|/
name|G_PI
expr_stmt|;
name|h1_
operator|=
operator|(
name|tmp
operator|>=
literal|0.0
operator|)
condition|?
name|tmp
else|:
name|tmp
operator|+
literal|360
expr_stmt|;
name|tmp
operator|=
name|atan2
argument_list|(
name|b2
argument_list|,
name|a2_
argument_list|)
operator|*
literal|180
operator|/
name|G_PI
expr_stmt|;
name|h2_
operator|=
operator|(
name|tmp
operator|>=
literal|0
operator|)
condition|?
name|tmp
else|:
name|tmp
operator|+
literal|360
expr_stmt|;
name|tmp
operator|=
name|abs
argument_list|(
name|h1_
operator|-
name|h2_
argument_list|)
expr_stmt|;
name|Ha_
operator|=
operator|(
name|tmp
operator|>
literal|180
operator|)
condition|?
operator|(
name|h1_
operator|+
name|h2_
operator|+
literal|360
operator|)
operator|/
literal|2.0
else|:
operator|(
name|h1_
operator|+
name|h2_
operator|)
operator|/
literal|2.0
expr_stmt|;
name|T
operator|=
literal|1
operator|-
literal|0.17
operator|*
name|cos
argument_list|(
operator|(
name|Ha_
operator|-
literal|30
operator|)
operator|*
name|G_PI
operator|/
literal|180
argument_list|)
operator|+
literal|0.24
operator|*
name|cos
argument_list|(
operator|(
name|Ha_
operator|*
literal|2
operator|)
operator|*
name|G_PI
operator|/
literal|180
argument_list|)
operator|+
literal|0.32
operator|*
name|cos
argument_list|(
operator|(
name|Ha_
operator|*
literal|3
operator|+
literal|6
operator|)
operator|*
name|G_PI
operator|/
literal|180
argument_list|)
operator|-
literal|0.2
operator|*
name|cos
argument_list|(
operator|(
name|Ha_
operator|*
literal|4
operator|-
literal|63
operator|)
operator|*
name|G_PI
operator|/
literal|180
argument_list|)
expr_stmt|;
if|if
condition|(
name|tmp
operator|<=
literal|180
condition|)
name|dh_
operator|=
name|h2_
operator|-
name|h1_
expr_stmt|;
elseif|else
if|if
condition|(
name|tmp
operator|>
literal|180
operator|&&
name|h2_
operator|<=
name|h1_
condition|)
name|dh_
operator|=
name|h2_
operator|-
name|h1_
operator|+
literal|360
expr_stmt|;
else|else
name|dh_
operator|=
name|h2_
operator|-
name|h1_
operator|-
literal|360
expr_stmt|;
name|dL_
operator|=
name|L2
operator|-
name|L1
expr_stmt|;
name|dC_
operator|=
name|C2_
operator|-
name|C1_
expr_stmt|;
name|dH_
operator|=
literal|2
operator|*
name|sqrt
argument_list|(
name|C1_
operator|*
name|C2_
argument_list|)
operator|*
name|sin
argument_list|(
name|dh_
operator|/
literal|2.0
operator|*
name|G_PI
operator|/
literal|180
argument_list|)
expr_stmt|;
name|tmp
operator|=
name|square
argument_list|(
name|La_
operator|-
literal|50
argument_list|)
expr_stmt|;
name|Sl
operator|=
literal|1
operator|+
literal|0.015
operator|*
name|tmp
operator|/
name|sqrt
argument_list|(
literal|20
operator|+
name|tmp
argument_list|)
expr_stmt|;
name|Sc
operator|=
literal|1
operator|+
literal|0.045
operator|*
name|Ca_
expr_stmt|;
name|Sh
operator|=
literal|1
operator|+
literal|0.015
operator|*
name|Ca_
operator|*
name|T
expr_stmt|;
name|dPhi
operator|=
literal|30
operator|*
name|exp
argument_list|(
operator|-
name|square
argument_list|(
operator|(
name|Ha_
operator|-
literal|275
operator|)
operator|/
literal|25.0
argument_list|)
argument_list|)
expr_stmt|;
name|tmp
operator|=
name|pow
argument_list|(
name|Ca_
argument_list|,
literal|7
argument_list|)
expr_stmt|;
name|Rc
operator|=
literal|2
operator|*
name|sqrt
argument_list|(
name|tmp
operator|/
operator|(
name|tmp
operator|+
name|pow
argument_list|(
literal|25
argument_list|,
literal|7
argument_list|)
operator|)
argument_list|)
expr_stmt|;
name|Rt
operator|=
operator|-
name|Rc
operator|*
name|sin
argument_list|(
literal|2
operator|*
name|dPhi
operator|*
name|G_PI
operator|/
literal|180
argument_list|)
expr_stmt|;
name|dE
operator|=
name|sqrt
argument_list|(
name|square
argument_list|(
name|dL_
operator|/
name|Sl
argument_list|)
operator|+
name|square
argument_list|(
name|dC_
operator|/
name|Sc
argument_list|)
operator|+
name|square
argument_list|(
name|dH_
operator|/
name|Sh
argument_list|)
operator|+
name|Rt
operator|*
name|dC_
operator|*
name|dH_
operator|/
name|Sc
operator|/
name|Sh
argument_list|)
expr_stmt|;
return|return
name|dE
return|;
block|}
end_function

begin_comment
comment|/*  * image comparison function from GEGL  */
end_comment

begin_function
specifier|static
name|gboolean
DECL|function|image_compare (gchar * composition_path,gchar * reference_path)
name|image_compare
parameter_list|(
name|gchar
modifier|*
name|composition_path
parameter_list|,
name|gchar
modifier|*
name|reference_path
parameter_list|)
block|{
name|GeglBuffer
modifier|*
name|bufferA
init|=
name|NULL
decl_stmt|;
name|GeglBuffer
modifier|*
name|bufferB
init|=
name|NULL
decl_stmt|;
name|GeglBuffer
modifier|*
name|debug_buf
init|=
name|NULL
decl_stmt|;
name|gboolean
name|result
init|=
name|TRUE
decl_stmt|;
block|{
name|GeglNode
modifier|*
name|graph
decl_stmt|,
modifier|*
name|sink
decl_stmt|;
name|graph
operator|=
name|gegl_graph
argument_list|(
name|sink
operator|=
name|gegl_node
argument_list|(
literal|"gegl:buffer-sink"
argument_list|,
literal|"buffer"
argument_list|,
operator|&
name|bufferA
argument_list|,
name|NULL
argument_list|,
name|gegl_node
argument_list|(
literal|"gegl:load"
argument_list|,
literal|"path"
argument_list|,
name|composition_path
argument_list|,
name|NULL
argument_list|)
argument_list|)
argument_list|)
expr_stmt|;
name|gegl_node_process
argument_list|(
name|sink
argument_list|)
expr_stmt|;
name|g_object_unref
argument_list|(
name|graph
argument_list|)
expr_stmt|;
if|if
condition|(
operator|!
name|bufferA
condition|)
block|{
name|g_printerr
argument_list|(
literal|"\nFailed to open %s\n"
argument_list|,
name|composition_path
argument_list|)
expr_stmt|;
return|return
name|FALSE
return|;
block|}
name|graph
operator|=
name|gegl_graph
argument_list|(
name|sink
operator|=
name|gegl_node
argument_list|(
literal|"gegl:buffer-sink"
argument_list|,
literal|"buffer"
argument_list|,
operator|&
name|bufferB
argument_list|,
name|NULL
argument_list|,
name|gegl_node
argument_list|(
literal|"gegl:load"
argument_list|,
literal|"path"
argument_list|,
name|reference_path
argument_list|,
name|NULL
argument_list|)
argument_list|)
argument_list|)
expr_stmt|;
name|gegl_node_process
argument_list|(
name|sink
argument_list|)
expr_stmt|;
name|g_object_unref
argument_list|(
name|graph
argument_list|)
expr_stmt|;
if|if
condition|(
operator|!
name|bufferB
condition|)
block|{
name|g_printerr
argument_list|(
literal|"\nFailed to open %s\n"
argument_list|,
name|reference_path
argument_list|)
expr_stmt|;
return|return
name|FALSE
return|;
block|}
block|}
if|if
condition|(
name|gegl_buffer_get_width
argument_list|(
name|bufferA
argument_list|)
operator|!=
name|gegl_buffer_get_width
argument_list|(
name|bufferB
argument_list|)
operator|||
name|gegl_buffer_get_height
argument_list|(
name|bufferA
argument_list|)
operator|!=
name|gegl_buffer_get_height
argument_list|(
name|bufferB
argument_list|)
condition|)
block|{
name|g_printerr
argument_list|(
literal|"\nBuffers differ in size\n"
argument_list|)
expr_stmt|;
name|g_printerr
argument_list|(
literal|"  %ix%i vs %ix%i\n"
argument_list|,
name|gegl_buffer_get_width
argument_list|(
name|bufferA
argument_list|)
argument_list|,
name|gegl_buffer_get_height
argument_list|(
name|bufferA
argument_list|)
argument_list|,
name|gegl_buffer_get_width
argument_list|(
name|bufferB
argument_list|)
argument_list|,
name|gegl_buffer_get_height
argument_list|(
name|bufferB
argument_list|)
argument_list|)
expr_stmt|;
return|return
name|FALSE
return|;
block|}
name|debug_buf
operator|=
name|gegl_buffer_new
argument_list|(
name|gegl_buffer_get_extent
argument_list|(
name|bufferA
argument_list|)
argument_list|,
name|babl_format
argument_list|(
literal|"R'G'B' u8"
argument_list|)
argument_list|)
expr_stmt|;
block|{
name|gfloat
modifier|*
name|bufA
decl_stmt|,
modifier|*
name|bufB
decl_stmt|;
name|gfloat
modifier|*
name|a
decl_stmt|,
modifier|*
name|b
decl_stmt|;
name|guchar
modifier|*
name|debug
decl_stmt|,
modifier|*
name|d
decl_stmt|;
name|gint
name|rowstrideA
decl_stmt|,
name|rowstrideB
decl_stmt|,
name|dRowstride
decl_stmt|;
name|gint
name|pixels
decl_stmt|;
name|gint
name|wrong_pixels
init|=
literal|0
decl_stmt|;
name|gint
name|i
decl_stmt|;
name|gdouble
name|diffsum
init|=
literal|0.0
decl_stmt|;
name|gdouble
name|max_diff
init|=
literal|0.0
decl_stmt|;
name|pixels
operator|=
name|gegl_buffer_get_pixel_count
argument_list|(
name|bufferA
argument_list|)
expr_stmt|;
name|bufA
operator|=
operator|(
name|void
operator|*
operator|)
name|gegl_buffer_linear_open
argument_list|(
name|bufferA
argument_list|,
name|NULL
argument_list|,
operator|&
name|rowstrideA
argument_list|,
name|babl_format
argument_list|(
literal|"CIE Lab float"
argument_list|)
argument_list|)
expr_stmt|;
name|bufB
operator|=
operator|(
name|void
operator|*
operator|)
name|gegl_buffer_linear_open
argument_list|(
name|bufferB
argument_list|,
name|NULL
argument_list|,
operator|&
name|rowstrideB
argument_list|,
name|babl_format
argument_list|(
literal|"CIE Lab float"
argument_list|)
argument_list|)
expr_stmt|;
name|debug
operator|=
operator|(
name|void
operator|*
operator|)
name|gegl_buffer_linear_open
argument_list|(
name|debug_buf
argument_list|,
name|NULL
argument_list|,
operator|&
name|dRowstride
argument_list|,
name|babl_format
argument_list|(
literal|"R'G'B' u8"
argument_list|)
argument_list|)
expr_stmt|;
name|a
operator|=
name|bufA
expr_stmt|;
name|b
operator|=
name|bufB
expr_stmt|;
name|d
operator|=
name|debug
expr_stmt|;
for|for
control|(
name|i
operator|=
literal|0
init|;
name|i
operator|<
name|pixels
condition|;
name|i
operator|++
control|)
block|{
name|gdouble
name|diff
init|=
name|delta_e
argument_list|(
name|a
argument_list|,
name|b
argument_list|)
decl_stmt|;
if|if
condition|(
name|diff
operator|>=
literal|0.1
condition|)
block|{
name|wrong_pixels
operator|++
expr_stmt|;
name|diffsum
operator|+=
name|diff
expr_stmt|;
if|if
condition|(
name|diff
operator|>
name|max_diff
condition|)
name|max_diff
operator|=
name|diff
expr_stmt|;
name|d
index|[
literal|0
index|]
operator|=
operator|(
name|diff
operator|/
literal|100.0
operator|*
literal|255
operator|)
expr_stmt|;
name|d
index|[
literal|1
index|]
operator|=
literal|0
expr_stmt|;
name|d
index|[
literal|2
index|]
operator|=
name|a
index|[
literal|0
index|]
operator|/
literal|100.0
operator|*
literal|255
expr_stmt|;
block|}
else|else
block|{
name|d
index|[
literal|0
index|]
operator|=
name|a
index|[
literal|0
index|]
operator|/
literal|100.0
operator|*
literal|255
expr_stmt|;
name|d
index|[
literal|1
index|]
operator|=
name|a
index|[
literal|0
index|]
operator|/
literal|100.0
operator|*
literal|255
expr_stmt|;
name|d
index|[
literal|2
index|]
operator|=
name|a
index|[
literal|0
index|]
operator|/
literal|100.0
operator|*
literal|255
expr_stmt|;
block|}
name|a
operator|+=
literal|3
expr_stmt|;
name|b
operator|+=
literal|3
expr_stmt|;
name|d
operator|+=
literal|3
expr_stmt|;
block|}
name|a
operator|=
name|bufA
expr_stmt|;
name|b
operator|=
name|bufB
expr_stmt|;
name|d
operator|=
name|debug
expr_stmt|;
if|if
condition|(
name|wrong_pixels
condition|)
for|for
control|(
name|i
operator|=
literal|0
init|;
name|i
operator|<
name|pixels
condition|;
name|i
operator|++
control|)
block|{
name|gdouble
name|diff
init|=
name|delta_e
argument_list|(
name|a
argument_list|,
name|b
argument_list|)
decl_stmt|;
if|if
condition|(
name|diff
operator|>=
literal|0.1
condition|)
block|{
name|d
index|[
literal|0
index|]
operator|=
operator|(
literal|100
operator|-
name|a
index|[
literal|0
index|]
operator|)
operator|/
literal|100.0
operator|*
literal|64
operator|+
literal|32
expr_stmt|;
name|d
index|[
literal|1
index|]
operator|=
operator|(
name|diff
operator|/
name|max_diff
operator|*
literal|255
operator|)
expr_stmt|;
name|d
index|[
literal|2
index|]
operator|=
literal|0
expr_stmt|;
block|}
else|else
block|{
name|d
index|[
literal|0
index|]
operator|=
name|a
index|[
literal|0
index|]
operator|/
literal|100.0
operator|*
literal|255
expr_stmt|;
name|d
index|[
literal|1
index|]
operator|=
name|a
index|[
literal|0
index|]
operator|/
literal|100.0
operator|*
literal|255
expr_stmt|;
name|d
index|[
literal|2
index|]
operator|=
name|a
index|[
literal|0
index|]
operator|/
literal|100.0
operator|*
literal|255
expr_stmt|;
block|}
name|a
operator|+=
literal|3
expr_stmt|;
name|b
operator|+=
literal|3
expr_stmt|;
name|d
operator|+=
literal|3
expr_stmt|;
block|}
name|gegl_buffer_linear_close
argument_list|(
name|bufferA
argument_list|,
name|bufA
argument_list|)
expr_stmt|;
name|gegl_buffer_linear_close
argument_list|(
name|bufferB
argument_list|,
name|bufB
argument_list|)
expr_stmt|;
name|gegl_buffer_linear_close
argument_list|(
name|debug_buf
argument_list|,
name|debug
argument_list|)
expr_stmt|;
if|if
condition|(
name|max_diff
operator|>
literal|1.5
condition|)
block|{
name|GeglNode
modifier|*
name|graph
decl_stmt|,
modifier|*
name|sink
decl_stmt|;
name|gchar
modifier|*
name|debug_path
decl_stmt|;
name|gint
name|ext_length
decl_stmt|;
name|g_print
argument_list|(
literal|"\nBuffers differ\n"
literal|"  wrong pixels   : %i/%i (%2.2f%%)\n"
literal|"  max Îe         : %2.3f\n"
literal|"  avg Îe (wrong) : %2.3f(wrong) %2.3f(total)\n"
argument_list|,
name|wrong_pixels
argument_list|,
name|pixels
argument_list|,
operator|(
name|wrong_pixels
operator|*
literal|100.0
operator|/
name|pixels
operator|)
argument_list|,
name|max_diff
argument_list|,
name|diffsum
operator|/
name|wrong_pixels
argument_list|,
name|diffsum
operator|/
name|pixels
argument_list|)
expr_stmt|;
name|debug_path
operator|=
name|g_malloc
argument_list|(
name|strlen
argument_list|(
name|composition_path
argument_list|)
operator|+
literal|16
argument_list|)
expr_stmt|;
name|ext_length
operator|=
name|strlen
argument_list|(
name|strrchr
argument_list|(
name|composition_path
argument_list|,
literal|'.'
argument_list|)
argument_list|)
expr_stmt|;
name|memcpy
argument_list|(
name|debug_path
argument_list|,
name|composition_path
argument_list|,
name|strlen
argument_list|(
name|composition_path
argument_list|)
operator|+
literal|1
argument_list|)
expr_stmt|;
name|memcpy
argument_list|(
name|debug_path
operator|+
name|strlen
argument_list|(
name|composition_path
argument_list|)
operator|-
name|ext_length
argument_list|,
literal|"-diff.png"
argument_list|,
literal|11
argument_list|)
expr_stmt|;
name|graph
operator|=
name|gegl_graph
argument_list|(
name|sink
operator|=
name|gegl_node
argument_list|(
literal|"gegl:png-save"
argument_list|,
literal|"path"
argument_list|,
name|debug_path
argument_list|,
name|NULL
argument_list|,
name|gegl_node
argument_list|(
literal|"gegl:buffer-source"
argument_list|,
literal|"buffer"
argument_list|,
name|debug_buf
argument_list|,
name|NULL
argument_list|)
argument_list|)
argument_list|)
expr_stmt|;
name|gegl_node_process
argument_list|(
name|sink
argument_list|)
expr_stmt|;
name|g_object_unref
argument_list|(
name|graph
argument_list|)
expr_stmt|;
name|g_object_unref
argument_list|(
name|debug_buf
argument_list|)
expr_stmt|;
name|result
operator|=
name|FALSE
expr_stmt|;
block|}
block|}
name|g_object_unref
argument_list|(
name|debug_buf
argument_list|)
expr_stmt|;
name|g_object_unref
argument_list|(
name|bufferA
argument_list|)
expr_stmt|;
name|g_object_unref
argument_list|(
name|bufferB
argument_list|)
expr_stmt|;
return|return
name|result
return|;
block|}
end_function

begin_function
specifier|static
name|gboolean
DECL|function|process_operations (GType type)
name|process_operations
parameter_list|(
name|GType
name|type
parameter_list|)
block|{
name|GType
modifier|*
name|operations
decl_stmt|;
name|gboolean
name|result
init|=
name|TRUE
decl_stmt|;
name|guint
name|count
decl_stmt|;
name|gint
name|i
decl_stmt|;
name|operations
operator|=
name|g_type_children
argument_list|(
name|type
argument_list|,
operator|&
name|count
argument_list|)
expr_stmt|;
if|if
condition|(
operator|!
name|operations
condition|)
block|{
name|g_free
argument_list|(
name|operations
argument_list|)
expr_stmt|;
return|return
name|TRUE
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
name|count
condition|;
name|i
operator|++
control|)
block|{
name|GeglOperationClass
modifier|*
name|operation_class
decl_stmt|;
specifier|const
name|gchar
modifier|*
name|image
decl_stmt|,
modifier|*
name|xml
decl_stmt|;
name|operation_class
operator|=
name|g_type_class_ref
argument_list|(
name|operations
index|[
name|i
index|]
argument_list|)
expr_stmt|;
name|image
operator|=
name|gegl_operation_class_get_key
argument_list|(
name|operation_class
argument_list|,
literal|"reference-image"
argument_list|)
expr_stmt|;
name|xml
operator|=
name|gegl_operation_class_get_key
argument_list|(
name|operation_class
argument_list|,
literal|"reference-composition"
argument_list|)
expr_stmt|;
if|if
condition|(
name|image
operator|&&
name|xml
condition|)
block|{
name|gchar
modifier|*
name|root
init|=
name|g_get_current_dir
argument_list|()
decl_stmt|;
name|gchar
modifier|*
name|xml_root
init|=
name|g_build_path
argument_list|(
name|G_DIR_SEPARATOR_S
argument_list|,
name|root
argument_list|,
name|DATA_DIR
argument_list|,
name|NULL
argument_list|)
decl_stmt|;
name|gchar
modifier|*
name|image_path
init|=
name|g_build_path
argument_list|(
name|G_DIR_SEPARATOR_S
argument_list|,
name|root
argument_list|,
name|DATA_DIR
argument_list|,
name|image
argument_list|,
name|NULL
argument_list|)
decl_stmt|;
name|gchar
modifier|*
name|output_path
init|=
name|g_build_path
argument_list|(
name|G_DIR_SEPARATOR_S
argument_list|,
name|root
argument_list|,
name|OUTPUT_DIR
argument_list|,
name|image
argument_list|,
name|NULL
argument_list|)
decl_stmt|;
name|GeglNode
modifier|*
name|composition
decl_stmt|,
modifier|*
name|output
decl_stmt|;
name|g_printf
argument_list|(
literal|"%s: "
argument_list|,
name|gegl_operation_class_get_key
argument_list|(
name|operation_class
argument_list|,
literal|"name"
argument_list|)
argument_list|)
expr_stmt|;
name|composition
operator|=
name|gegl_node_new_from_xml
argument_list|(
name|xml
argument_list|,
name|xml_root
argument_list|)
expr_stmt|;
if|if
condition|(
operator|!
name|composition
condition|)
block|{
name|g_printerr
argument_list|(
literal|"\nComposition graph is flawed\n"
argument_list|)
expr_stmt|;
name|result
operator|=
name|FALSE
expr_stmt|;
block|}
else|else
block|{
name|output
operator|=
name|gegl_node_new_child
argument_list|(
name|composition
argument_list|,
literal|"operation"
argument_list|,
literal|"gegl:save"
argument_list|,
literal|"path"
argument_list|,
name|output_path
argument_list|,
name|NULL
argument_list|)
expr_stmt|;
name|gegl_node_connect_to
argument_list|(
name|composition
argument_list|,
literal|"output"
argument_list|,
name|output
argument_list|,
literal|"input"
argument_list|)
expr_stmt|;
name|gegl_node_process
argument_list|(
name|output
argument_list|)
expr_stmt|;
if|if
condition|(
name|image_compare
argument_list|(
name|output_path
argument_list|,
name|image_path
argument_list|)
condition|)
block|{
name|g_printf
argument_list|(
literal|"PASS\n"
argument_list|)
expr_stmt|;
name|result
operator|=
name|result
operator|&&
name|TRUE
expr_stmt|;
block|}
else|else
block|{
name|g_printf
argument_list|(
literal|"FAIL\n"
argument_list|)
expr_stmt|;
name|result
operator|=
name|result
operator|&&
name|FALSE
expr_stmt|;
block|}
block|}
name|g_object_unref
argument_list|(
name|composition
argument_list|)
expr_stmt|;
name|g_free
argument_list|(
name|root
argument_list|)
expr_stmt|;
name|g_free
argument_list|(
name|xml_root
argument_list|)
expr_stmt|;
name|g_free
argument_list|(
name|image_path
argument_list|)
expr_stmt|;
name|g_free
argument_list|(
name|output_path
argument_list|)
expr_stmt|;
block|}
name|result
operator|=
name|result
operator|&&
name|process_operations
argument_list|(
name|operations
index|[
name|i
index|]
argument_list|)
expr_stmt|;
block|}
name|g_free
argument_list|(
name|operations
argument_list|)
expr_stmt|;
return|return
name|result
return|;
block|}
end_function

begin_function
specifier|static
name|void
DECL|function|test_operations (void)
name|test_operations
parameter_list|(
name|void
parameter_list|)
block|{
name|gint
name|result
decl_stmt|;
name|putchar
argument_list|(
literal|'\n'
argument_list|)
expr_stmt|;
name|result
operator|=
name|process_operations
argument_list|(
name|GEGL_TYPE_OPERATION
argument_list|)
expr_stmt|;
name|g_assert_cmpint
argument_list|(
name|result
argument_list|,
operator|==
argument_list|,
name|TRUE
argument_list|)
expr_stmt|;
block|}
end_function

begin_function
name|gint
DECL|function|main (gint argc,gchar ** argv)
name|main
parameter_list|(
name|gint
name|argc
parameter_list|,
name|gchar
modifier|*
modifier|*
name|argv
parameter_list|)
block|{
name|gint
name|result
decl_stmt|;
name|gegl_init
argument_list|(
operator|&
name|argc
argument_list|,
operator|&
name|argv
argument_list|)
expr_stmt|;
name|gimp_operations_init
argument_list|()
expr_stmt|;
name|g_test_init
argument_list|(
operator|&
name|argc
argument_list|,
operator|&
name|argv
argument_list|,
name|NULL
argument_list|)
expr_stmt|;
name|g_test_add_func
argument_list|(
literal|"/gimp-operations"
argument_list|,
name|test_operations
argument_list|)
expr_stmt|;
name|result
operator|=
name|g_test_run
argument_list|()
expr_stmt|;
name|gegl_exit
argument_list|()
expr_stmt|;
return|return
name|result
return|;
block|}
end_function

end_unit

