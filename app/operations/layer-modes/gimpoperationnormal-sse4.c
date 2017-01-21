begin_unit|revision:0.9.5;language:C;cregit-version:0.0.1
begin_comment
comment|/* GIMP - The GNU Image Manipulation Program  * Copyright (C) 1995 Spencer Kimball and Peter Mattis  *  * gimpoperationnormalmode-sse2.c  * Copyright (C) 2013 Daniel Sabo  *  * This program is free software: you can redistribute it and/or modify  * it under the terms of the GNU General Public License as published by  * the Free Software Foundation; either version 3 of the License, or  * (at your option) any later version.  *  * This program is distributed in the hope that it will be useful,  * but WITHOUT ANY WARRANTY; without even the implied warranty of  * MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the  * GNU General Public License for more details.  *  * You should have received a copy of the GNU General Public License  * along with this program.  If not, see<http://www.gnu.org/licenses/>.  */
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
file|"operations/operations-types.h"
end_include

begin_include
include|#
directive|include
file|"gimpoperationnormal.h"
end_include

begin_if
if|#
directive|if
name|COMPILE_SSE4_1_INTRINISICS
end_if

begin_comment
comment|/* SSE4 */
end_comment

begin_include
include|#
directive|include
file|<smmintrin.h>
end_include

begin_function
name|gboolean
DECL|function|gimp_operation_normal_process_sse4 (GeglOperation * operation,void * in,void * aux,void * mask_p,void * out,glong samples,const GeglRectangle * roi,gint level)
name|gimp_operation_normal_process_sse4
parameter_list|(
name|GeglOperation
modifier|*
name|operation
parameter_list|,
name|void
modifier|*
name|in
parameter_list|,
name|void
modifier|*
name|aux
parameter_list|,
name|void
modifier|*
name|mask_p
parameter_list|,
name|void
modifier|*
name|out
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
comment|/* check alignment */
if|if
condition|(
operator|(
operator|(
operator|(
name|uintptr_t
operator|)
name|in
operator|)
operator||
operator|(
operator|(
name|uintptr_t
operator|)
name|aux
operator|)
operator||
operator|(
operator|(
name|uintptr_t
operator|)
name|out
operator|)
operator|)
operator|&
literal|0x0F
condition|)
block|{
return|return
name|gimp_operation_normal_process_core
argument_list|(
name|operation
argument_list|,
name|in
argument_list|,
name|aux
argument_list|,
name|mask_p
argument_list|,
name|out
argument_list|,
name|samples
argument_list|,
name|roi
argument_list|,
name|level
argument_list|)
return|;
block|}
else|else
block|{
name|gfloat
name|opacity
init|=
operator|(
operator|(
name|GimpOperationPointLayerMode
operator|*
operator|)
operator|(
name|operation
operator|)
operator|)
operator|->
name|opacity
decl_stmt|;
name|gfloat
modifier|*
name|mask
init|=
name|mask_p
decl_stmt|;
specifier|const
name|__v4sf
modifier|*
name|v_in
init|=
operator|(
specifier|const
name|__v4sf
operator|*
operator|)
name|in
decl_stmt|;
specifier|const
name|__v4sf
modifier|*
name|v_aux
init|=
operator|(
specifier|const
name|__v4sf
operator|*
operator|)
name|aux
decl_stmt|;
name|__v4sf
modifier|*
name|v_out
init|=
operator|(
name|__v4sf
operator|*
operator|)
name|out
decl_stmt|;
specifier|const
name|__v4sf
name|one
init|=
name|_mm_set1_ps
argument_list|(
literal|1.0f
argument_list|)
decl_stmt|;
specifier|const
name|__v4sf
name|v_opacity
init|=
name|_mm_set1_ps
argument_list|(
name|opacity
argument_list|)
decl_stmt|;
while|while
condition|(
name|samples
operator|--
condition|)
block|{
name|__v4sf
name|rgba_in
decl_stmt|,
name|rgba_aux
decl_stmt|,
name|alpha
decl_stmt|;
name|rgba_in
operator|=
operator|*
name|v_in
operator|++
expr_stmt|;
name|rgba_aux
operator|=
operator|*
name|v_aux
operator|++
expr_stmt|;
comment|/* expand alpha */
name|alpha
operator|=
operator|(
name|__v4sf
operator|)
name|_mm_shuffle_epi32
argument_list|(
operator|(
name|__m128i
operator|)
name|rgba_aux
argument_list|,
name|_MM_SHUFFLE
argument_list|(
literal|3
argument_list|,
literal|3
argument_list|,
literal|3
argument_list|,
literal|3
argument_list|)
argument_list|)
expr_stmt|;
if|if
condition|(
name|mask
condition|)
block|{
name|__v4sf
name|mask_alpha
decl_stmt|;
comment|/* multiply aux's alpha by the mask */
name|mask_alpha
operator|=
name|_mm_set1_ps
argument_list|(
operator|*
name|mask
operator|++
argument_list|)
expr_stmt|;
name|alpha
operator|=
name|alpha
operator|*
name|mask_alpha
expr_stmt|;
block|}
name|alpha
operator|=
name|alpha
operator|*
name|v_opacity
expr_stmt|;
if|if
condition|(
name|_mm_ucomigt_ss
argument_list|(
name|alpha
argument_list|,
name|_mm_setzero_ps
argument_list|()
argument_list|)
condition|)
block|{
name|__v4sf
name|dst_alpha
decl_stmt|,
name|a_term
decl_stmt|,
name|out_pixel
decl_stmt|,
name|out_alpha
decl_stmt|;
comment|/* expand alpha */
name|dst_alpha
operator|=
operator|(
name|__v4sf
operator|)
name|_mm_shuffle_epi32
argument_list|(
operator|(
name|__m128i
operator|)
name|rgba_in
argument_list|,
name|_MM_SHUFFLE
argument_list|(
literal|3
argument_list|,
literal|3
argument_list|,
literal|3
argument_list|,
literal|3
argument_list|)
argument_list|)
expr_stmt|;
comment|/* a_term = dst_a * (1.0 - src_a) */
name|a_term
operator|=
name|dst_alpha
operator|*
operator|(
name|one
operator|-
name|alpha
operator|)
expr_stmt|;
comment|/* out(color) = src * src_a + dst * a_term */
name|out_pixel
operator|=
name|rgba_aux
operator|*
name|alpha
operator|+
name|rgba_in
operator|*
name|a_term
expr_stmt|;
comment|/* out(alpha) = 1.0 * src_a + 1.0 * a_term */
name|out_alpha
operator|=
name|alpha
operator|+
name|a_term
expr_stmt|;
comment|/* un-premultiply */
name|out_pixel
operator|=
name|out_pixel
operator|/
name|out_alpha
expr_stmt|;
comment|/* swap in the real alpha */
name|out_pixel
operator|=
name|_mm_blend_ps
argument_list|(
name|out_pixel
argument_list|,
name|out_alpha
argument_list|,
literal|0x08
argument_list|)
expr_stmt|;
operator|*
name|v_out
operator|++
operator|=
name|out_pixel
expr_stmt|;
block|}
else|else
block|{
operator|*
name|v_out
operator|++
operator|=
name|rgba_in
expr_stmt|;
block|}
block|}
block|}
return|return
name|TRUE
return|;
block|}
end_function

begin_endif
endif|#
directive|endif
end_endif

begin_comment
comment|/* COMPILE_SSE4_1_INTRINISICS */
end_comment

end_unit

