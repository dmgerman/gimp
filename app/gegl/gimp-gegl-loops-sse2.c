begin_unit|revision:0.9.5;language:C;cregit-version:0.0.1
begin_comment
comment|/* GIMP - The GNU Image Manipulation Program  * Copyright (C) 1995 Spencer Kimball and Peter Mattis  *  * gimp-gegl-loops-sse2.c  * Copyright (C) 2012 Michael Natterer<mitch@gimp.org>  *  * This program is free software: you can redistribute it and/or modify  * it under the terms of the GNU General Public License as published by  * the Free Software Foundation; either version 3 of the License, or  * (at your option) any later version.  *  * This program is distributed in the hope that it will be useful,  * but WITHOUT ANY WARRANTY; without even the implied warranty of  * MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the  * GNU General Public License for more details.  *  * You should have received a copy of the GNU General Public License  * along with this program.  If not, see<http://www.gnu.org/licenses/>.  */
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
file|<gegl.h>
end_include

begin_include
include|#
directive|include
file|"gimp-gegl-types.h"
end_include

begin_include
include|#
directive|include
file|"gimp-gegl-loops-sse2.h"
end_include

begin_if
if|#
directive|if
name|COMPILE_SSE2_INTRINISICS
end_if

begin_include
include|#
directive|include
file|<emmintrin.h>
end_include

begin_comment
comment|/* helper function of gimp_gegl_smudge_with_paint_process_sse2()  * src and dest can be the same address  */
end_comment

begin_function
specifier|static
specifier|inline
name|void
DECL|function|gimp_gegl_smudge_with_paint_blend_sse2 (const gfloat * src1,gfloat src1_rate,const gfloat * src2,gfloat src2_rate,gfloat * dest,gboolean no_erasing_src2)
name|gimp_gegl_smudge_with_paint_blend_sse2
parameter_list|(
specifier|const
name|gfloat
modifier|*
name|src1
parameter_list|,
name|gfloat
name|src1_rate
parameter_list|,
specifier|const
name|gfloat
modifier|*
name|src2
parameter_list|,
name|gfloat
name|src2_rate
parameter_list|,
name|gfloat
modifier|*
name|dest
parameter_list|,
name|gboolean
name|no_erasing_src2
parameter_list|)
block|{
comment|/* 2017/4/13 shark0r : According to my test, SSE decreases about 25%    * execution time    */
name|__m128
name|v_src1
init|=
name|_mm_loadu_ps
argument_list|(
name|src1
argument_list|)
decl_stmt|;
name|__m128
name|v_src2
init|=
name|_mm_loadu_ps
argument_list|(
name|src2
argument_list|)
decl_stmt|;
name|__m128
modifier|*
name|v_dest
init|=
operator|(
name|__v4sf
operator|*
operator|)
name|dest
decl_stmt|;
name|gfloat
name|orginal_src2_alpha
decl_stmt|;
name|gfloat
name|src1_alpha
decl_stmt|;
name|gfloat
name|src2_alpha
decl_stmt|;
name|gfloat
name|result_alpha
decl_stmt|;
name|orginal_src2_alpha
operator|=
name|v_src2
index|[
literal|3
index|]
expr_stmt|;
name|src1_alpha
operator|=
name|src1_rate
operator|*
name|v_src1
index|[
literal|3
index|]
expr_stmt|;
name|src2_alpha
operator|=
name|src2_rate
operator|*
name|orginal_src2_alpha
expr_stmt|;
name|result_alpha
operator|=
name|src1_alpha
operator|+
name|src2_alpha
expr_stmt|;
if|if
condition|(
name|result_alpha
operator|==
literal|0
condition|)
block|{
operator|*
name|v_dest
operator|=
name|_mm_set1_ps
argument_list|(
literal|0
argument_list|)
expr_stmt|;
return|return;
block|}
operator|*
name|v_dest
operator|=
operator|(
name|v_src1
operator|*
name|_mm_set1_ps
argument_list|(
name|src1_alpha
argument_list|)
operator|+
name|v_src2
operator|*
name|_mm_set1_ps
argument_list|(
name|src2_alpha
argument_list|)
operator|)
operator|/
name|_mm_set1_ps
argument_list|(
name|result_alpha
argument_list|)
expr_stmt|;
if|if
condition|(
name|no_erasing_src2
condition|)
block|{
name|result_alpha
operator|=
name|MAX
argument_list|(
name|result_alpha
argument_list|,
name|orginal_src2_alpha
argument_list|)
expr_stmt|;
block|}
name|dest
index|[
literal|3
index|]
operator|=
name|result_alpha
expr_stmt|;
block|}
end_function

begin_comment
comment|/* helper function of gimp_gegl_smudge_with_paint()  *  * note that it's the caller's responsibility to verify that the buffers are  * properly aligned  */
end_comment

begin_function
name|void
DECL|function|gimp_gegl_smudge_with_paint_process_sse2 (gfloat * accum,const gfloat * canvas,gfloat * paint,gint count,const gfloat * brush_color,gfloat brush_a,gboolean no_erasing,gfloat flow,gfloat rate)
name|gimp_gegl_smudge_with_paint_process_sse2
parameter_list|(
name|gfloat
modifier|*
name|accum
parameter_list|,
specifier|const
name|gfloat
modifier|*
name|canvas
parameter_list|,
name|gfloat
modifier|*
name|paint
parameter_list|,
name|gint
name|count
parameter_list|,
specifier|const
name|gfloat
modifier|*
name|brush_color
parameter_list|,
name|gfloat
name|brush_a
parameter_list|,
name|gboolean
name|no_erasing
parameter_list|,
name|gfloat
name|flow
parameter_list|,
name|gfloat
name|rate
parameter_list|)
block|{
while|while
condition|(
name|count
operator|--
condition|)
block|{
comment|/* blend accum_buffer and canvas_buffer to accum_buffer */
name|gimp_gegl_smudge_with_paint_blend_sse2
argument_list|(
name|accum
argument_list|,
name|rate
argument_list|,
name|canvas
argument_list|,
literal|1
operator|-
name|rate
argument_list|,
name|accum
argument_list|,
name|no_erasing
argument_list|)
expr_stmt|;
comment|/* blend accum_buffer and brush color/pixmap to paint_buffer */
if|if
condition|(
name|brush_a
operator|==
literal|0
condition|)
comment|/* pure smudge */
block|{
name|memcpy
argument_list|(
name|paint
argument_list|,
name|accum
argument_list|,
sizeof|sizeof
argument_list|(
name|gfloat
argument_list|)
operator|*
literal|4
argument_list|)
expr_stmt|;
block|}
else|else
block|{
specifier|const
name|gfloat
modifier|*
name|src1
init|=
name|brush_color
condition|?
name|brush_color
else|:
name|paint
decl_stmt|;
name|gimp_gegl_smudge_with_paint_blend_sse2
argument_list|(
name|src1
argument_list|,
name|flow
argument_list|,
name|accum
argument_list|,
literal|1
operator|-
name|flow
argument_list|,
name|paint
argument_list|,
name|no_erasing
argument_list|)
expr_stmt|;
block|}
name|accum
operator|+=
literal|4
expr_stmt|;
name|canvas
operator|+=
literal|4
expr_stmt|;
name|paint
operator|+=
literal|4
expr_stmt|;
block|}
block|}
end_function

begin_endif
endif|#
directive|endif
end_endif

begin_comment
comment|/* COMPILE_SSE2_INTRINISICS */
end_comment

end_unit
