begin_unit|revision:0.9.5;language:C;cregit-version:0.0.1
begin_comment
comment|/* -*- mode: c tab-width: 2; c-basic-indent: 2; indent-tabs-mode: nil -*-  *  * The GIMP -- an image manipulation program  * Copyright (C) 1995 Spencer Kimball and Peter Mattis  *  * -*- mode: c tab-width: 2; c-basic-indent: 2; indent-tabs-mode: nil -*-  *  * This program is free software; you can redistribute it and/or modify  * it under the terms of the GNU General Public License as published by  * the Free Software Foundation; either version 2 of the License, or  * (at your option) any later version.  *  * Gimp image compositing  * Copyright (C) 2003  Helvetix Victorinox, a pseudonym,<helvetix@gimp.org>  *  * This program is distributed in the hope that it will be useful,  * but WITHOUT ANY WARRANTY; without even the implied warranty of  * MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the  * GNU General Public License for more details.  *  * You should have received a copy of the GNU General Public License  * along with this program; if not, write to the Free Software  * Foundation, Inc., 59 Temple Place - Suite 330, Boston, MA 02111-1307, USA.  */
end_comment

begin_include
include|#
directive|include
file|"config.h"
end_include

begin_include
include|#
directive|include
file|<stdio.h>
end_include

begin_include
include|#
directive|include
file|<glib-object.h>
end_include

begin_include
include|#
directive|include
file|"base/base-types.h"
end_include

begin_include
include|#
directive|include
file|"gimp-composite.h"
end_include

begin_include
include|#
directive|include
file|"gimp-composite-sse2.h"
end_include

begin_ifdef
ifdef|#
directive|ifdef
name|COMPILE_SSE2_IS_OKAY
end_ifdef

begin_include
include|#
directive|include
file|"gimp-composite-x86.h"
end_include

begin_decl_stmt
DECL|variable|rgba8_alpha_mask_128
specifier|static
specifier|const
name|guint32
name|rgba8_alpha_mask_128
index|[
literal|4
index|]
init|=
block|{
literal|0xFF000000
block|,
literal|0xFF000000
block|,
literal|0xFF000000
block|,
literal|0xFF000000
block|}
decl_stmt|;
end_decl_stmt

begin_decl_stmt
DECL|variable|rgba8_b1_128
specifier|static
specifier|const
name|guint32
name|rgba8_b1_128
index|[
literal|4
index|]
init|=
block|{
literal|0x01010101
block|,
literal|0x01010101
block|,
literal|0x01010101
block|,
literal|0x01010101
block|}
decl_stmt|;
end_decl_stmt

begin_decl_stmt
DECL|variable|rgba8_b255_128
specifier|static
specifier|const
name|guint32
name|rgba8_b255_128
index|[
literal|4
index|]
init|=
block|{
literal|0xFFFFFFFF
block|,
literal|0xFFFFFFFF
block|,
literal|0xFFFFFFFF
block|,
literal|0xFFFFFFFF
block|}
decl_stmt|;
end_decl_stmt

begin_decl_stmt
DECL|variable|rgba8_w1_128
specifier|static
specifier|const
name|guint32
name|rgba8_w1_128
index|[
literal|4
index|]
init|=
block|{
literal|0x00010001
block|,
literal|0x00010001
block|,
literal|0x00010001
block|,
literal|0x00010001
block|}
decl_stmt|;
end_decl_stmt

begin_decl_stmt
DECL|variable|rgba8_w2_128
specifier|static
specifier|const
name|guint32
name|rgba8_w2_128
index|[
literal|4
index|]
init|=
block|{
literal|0x00020002
block|,
literal|0x00020002
block|,
literal|0x00020002
block|,
literal|0x00020002
block|}
decl_stmt|;
end_decl_stmt

begin_decl_stmt
DECL|variable|rgba8_w128_128
specifier|static
specifier|const
name|guint32
name|rgba8_w128_128
index|[
literal|4
index|]
init|=
block|{
literal|0x00800080
block|,
literal|0x00800080
block|,
literal|0x00800080
block|,
literal|0x00800080
block|}
decl_stmt|;
end_decl_stmt

begin_decl_stmt
DECL|variable|rgba8_w256_128
specifier|static
specifier|const
name|guint32
name|rgba8_w256_128
index|[
literal|4
index|]
init|=
block|{
literal|0x01000100
block|,
literal|0x01000100
block|,
literal|0x01000100
block|,
literal|0x01000100
block|}
decl_stmt|;
end_decl_stmt

begin_decl_stmt
DECL|variable|rgba8_w255_128
specifier|static
specifier|const
name|guint32
name|rgba8_w255_128
index|[
literal|4
index|]
init|=
block|{
literal|0X00FF00FF
block|,
literal|0X00FF00FF
block|,
literal|0X00FF00FF
block|,
literal|0X00FF00FF
block|}
decl_stmt|;
end_decl_stmt

begin_decl_stmt
DECL|variable|va8_alpha_mask_128
specifier|static
specifier|const
name|guint32
name|va8_alpha_mask_128
index|[
literal|4
index|]
init|=
block|{
literal|0xFF00FF00
block|,
literal|0xFF00FF00
block|,
literal|0xFF00FF00
block|,
literal|0xFF00FF00
block|}
decl_stmt|;
end_decl_stmt

begin_decl_stmt
DECL|variable|va8_b255_128
specifier|static
specifier|const
name|guint32
name|va8_b255_128
index|[
literal|4
index|]
init|=
block|{
literal|0xFFFFFFFF
block|,
literal|0xFFFFFFFF
block|,
literal|0xFFFFFFFF
block|,
literal|0xFFFFFFFF
block|}
decl_stmt|;
end_decl_stmt

begin_decl_stmt
DECL|variable|va8_w1_128
specifier|static
specifier|const
name|guint32
name|va8_w1_128
index|[
literal|4
index|]
init|=
block|{
literal|0x00010001
block|,
literal|0x00010001
block|,
literal|0x00010001
block|,
literal|0x00010001
block|}
decl_stmt|;
end_decl_stmt

begin_decl_stmt
DECL|variable|va8_w255_128
specifier|static
specifier|const
name|guint32
name|va8_w255_128
index|[
literal|4
index|]
init|=
block|{
literal|0x00FF00FF
block|,
literal|0x00FF00FF
block|,
literal|0x00FF00FF
block|,
literal|0x00FF00FF
block|}
decl_stmt|;
end_decl_stmt

begin_decl_stmt
DECL|variable|rgba8_alpha_mask_64
specifier|static
specifier|const
name|guint32
name|rgba8_alpha_mask_64
index|[
literal|2
index|]
init|=
block|{
literal|0xFF000000
block|,
literal|0xFF000000
block|}
decl_stmt|;
end_decl_stmt

begin_decl_stmt
DECL|variable|rgba8_b1_64
specifier|static
specifier|const
name|guint32
name|rgba8_b1_64
index|[
literal|2
index|]
init|=
block|{
literal|0x01010101
block|,
literal|0x01010101
block|}
decl_stmt|;
end_decl_stmt

begin_decl_stmt
DECL|variable|rgba8_b255_64
specifier|static
specifier|const
name|guint32
name|rgba8_b255_64
index|[
literal|2
index|]
init|=
block|{
literal|0xFFFFFFFF
block|,
literal|0xFFFFFFFF
block|}
decl_stmt|;
end_decl_stmt

begin_decl_stmt
DECL|variable|rgba8_w1_64
specifier|static
specifier|const
name|guint32
name|rgba8_w1_64
index|[
literal|2
index|]
init|=
block|{
literal|0x00010001
block|,
literal|0x00010001
block|}
decl_stmt|;
end_decl_stmt

begin_decl_stmt
DECL|variable|rgba8_w2_64
specifier|static
specifier|const
name|guint32
name|rgba8_w2_64
index|[
literal|2
index|]
init|=
block|{
literal|0x00020002
block|,
literal|0x00020002
block|}
decl_stmt|;
end_decl_stmt

begin_decl_stmt
DECL|variable|rgba8_w128_64
specifier|static
specifier|const
name|guint32
name|rgba8_w128_64
index|[
literal|2
index|]
init|=
block|{
literal|0x00800080
block|,
literal|0x00800080
block|}
decl_stmt|;
end_decl_stmt

begin_decl_stmt
DECL|variable|rgba8_w256_64
specifier|static
specifier|const
name|guint32
name|rgba8_w256_64
index|[
literal|2
index|]
init|=
block|{
literal|0x01000100
block|,
literal|0x01000100
block|}
decl_stmt|;
end_decl_stmt

begin_decl_stmt
DECL|variable|rgba8_w255_64
specifier|static
specifier|const
name|guint32
name|rgba8_w255_64
index|[
literal|2
index|]
init|=
block|{
literal|0X00FF00FF
block|,
literal|0X00FF00FF
block|}
decl_stmt|;
end_decl_stmt

begin_decl_stmt
DECL|variable|va8_alpha_mask_64
specifier|static
specifier|const
name|guint32
name|va8_alpha_mask_64
index|[
literal|2
index|]
init|=
block|{
literal|0xFF00FF00
block|,
literal|0xFF00FF00
block|}
decl_stmt|;
end_decl_stmt

begin_decl_stmt
DECL|variable|va8_b255_64
specifier|static
specifier|const
name|guint32
name|va8_b255_64
index|[
literal|2
index|]
init|=
block|{
literal|0xFFFFFFFF
block|,
literal|0xFFFFFFFF
block|}
decl_stmt|;
end_decl_stmt

begin_decl_stmt
DECL|variable|va8_w1_64
specifier|static
specifier|const
name|guint32
name|va8_w1_64
index|[
literal|2
index|]
init|=
block|{
literal|0x00010001
block|,
literal|0x00010001
block|}
decl_stmt|;
end_decl_stmt

begin_decl_stmt
DECL|variable|va8_w255_64
specifier|static
specifier|const
name|guint32
name|va8_w255_64
index|[
literal|2
index|]
init|=
block|{
literal|0x00FF00FF
block|,
literal|0x00FF00FF
block|}
decl_stmt|;
end_decl_stmt

begin_function
name|void
DECL|function|debug_display_sse (void)
name|debug_display_sse
parameter_list|(
name|void
parameter_list|)
block|{
DECL|macro|mask32 (x)
define|#
directive|define
name|mask32
parameter_list|(
name|x
parameter_list|)
value|((x)& (unsigned long long) 0xFFFFFFFF)
DECL|macro|print128 (reg)
define|#
directive|define
name|print128
parameter_list|(
name|reg
parameter_list|)
value|{ \   unsigned long long reg[2]; \   asm("movdqu %%" #reg ",%0" : "=m" (reg)); \   printf(#reg"=%08llx %08llx", mask32(reg[0]>>32), mask32(reg[0])); \   printf(" %08llx %08llx", mask32(reg[1]>>32), mask32(reg[1])); \  }
name|printf
argument_list|(
literal|"--------------------------------------------\n"
argument_list|)
expr_stmt|;
name|print128
argument_list|(
name|xmm0
argument_list|)
expr_stmt|;
name|printf
argument_list|(
literal|"  "
argument_list|)
expr_stmt|;
name|print128
argument_list|(
name|xmm1
argument_list|)
expr_stmt|;
name|printf
argument_list|(
literal|"\n"
argument_list|)
expr_stmt|;
name|print128
argument_list|(
name|xmm2
argument_list|)
expr_stmt|;
name|printf
argument_list|(
literal|"  "
argument_list|)
expr_stmt|;
name|print128
argument_list|(
name|xmm3
argument_list|)
expr_stmt|;
name|printf
argument_list|(
literal|"\n"
argument_list|)
expr_stmt|;
name|print128
argument_list|(
name|xmm4
argument_list|)
expr_stmt|;
name|printf
argument_list|(
literal|"  "
argument_list|)
expr_stmt|;
name|print128
argument_list|(
name|xmm5
argument_list|)
expr_stmt|;
name|printf
argument_list|(
literal|"\n"
argument_list|)
expr_stmt|;
name|print128
argument_list|(
name|xmm6
argument_list|)
expr_stmt|;
name|printf
argument_list|(
literal|"  "
argument_list|)
expr_stmt|;
name|print128
argument_list|(
name|xmm7
argument_list|)
expr_stmt|;
name|printf
argument_list|(
literal|"\n"
argument_list|)
expr_stmt|;
name|printf
argument_list|(
literal|"--------------------------------------------\n"
argument_list|)
expr_stmt|;
block|}
end_function

begin_function
name|void
DECL|function|gimp_composite_addition_rgba8_rgba8_rgba8_sse2 (GimpCompositeContext * _op)
name|gimp_composite_addition_rgba8_rgba8_rgba8_sse2
parameter_list|(
name|GimpCompositeContext
modifier|*
name|_op
parameter_list|)
block|{
name|uint64
modifier|*
name|d
decl_stmt|;
name|uint64
modifier|*
name|a
decl_stmt|;
name|uint64
modifier|*
name|b
decl_stmt|;
name|uint128
modifier|*
name|D
init|=
operator|(
name|uint128
operator|*
operator|)
name|_op
operator|->
name|D
decl_stmt|;
name|uint128
modifier|*
name|A
init|=
operator|(
name|uint128
operator|*
operator|)
name|_op
operator|->
name|A
decl_stmt|;
name|uint128
modifier|*
name|B
init|=
operator|(
name|uint128
operator|*
operator|)
name|_op
operator|->
name|B
decl_stmt|;
name|gulong
name|n_pixels
init|=
name|_op
operator|->
name|n_pixels
decl_stmt|;
asm|asm
specifier|volatile
asm|("  movdqu    %0,%%xmm0\n"                 "\tmovq      %1,%%mm0"                 :
comment|/* empty */
asm|: "m" (*rgba8_alpha_mask_128), "m" (*rgba8_alpha_mask_64)                 : "%xmm0", "%mm0");
for|for
control|(
init|;
name|n_pixels
operator|>=
literal|4
condition|;
name|n_pixels
operator|-=
literal|4
control|)
block|{
asm|asm
specifier|volatile
asm|("  movdqu      %1,%%xmm2\n"                     "\tmovdqu      %2,%%xmm3\n"                     "\tmovdqu  %%xmm2,%%xmm4\n"                     "\tpaddusb %%xmm3,%%xmm4\n"                                          "\tmovdqu  %%xmm0,%%xmm1\n"                     "\tpandn   %%xmm4,%%xmm1\n"                     "\tpminub  %%xmm3,%%xmm2\n"                     "\tpand    %%xmm0,%%xmm2\n"                     "\tpor     %%xmm2,%%xmm1\n"                     "\tmovdqu  %%xmm1,%0\n"                     : "=m" (*D)                     : "m" (*A), "m" (*B)                     : "%xmm0", "%xmm1", "%xmm2", "%xmm3", "%xmm4", "%xmm5", "%xmm6", "%xmm7");
name|A
operator|++
expr_stmt|;
name|B
operator|++
expr_stmt|;
name|D
operator|++
expr_stmt|;
block|}
name|a
operator|=
operator|(
name|uint64
operator|*
operator|)
name|A
expr_stmt|;
name|b
operator|=
operator|(
name|uint64
operator|*
operator|)
name|B
expr_stmt|;
name|d
operator|=
operator|(
name|uint64
operator|*
operator|)
name|D
expr_stmt|;
for|for
control|(
init|;
name|n_pixels
operator|>=
literal|2
condition|;
name|n_pixels
operator|-=
literal|2
control|)
block|{
asm|asm
specifier|volatile
asm|("  movq       %1,%%mm2\n"                     "\tmovq       %2,%%mm3\n"                     "\tmovq    %%mm2,%%mm4\n"                     "\tpaddusb %%mm3,%%mm4\n"                     "\tmovq    %%mm0,%%mm1\n"                     "\tpandn   %%mm4,%%mm1\n"                     "\tpminub  %%mm3,%%mm2\n"                     "\tpand    %%mm0,%%mm2\n"                     "\tpor     %%mm2,%%mm1\n"                     "\tmovntq  %%mm1,%0\n"                     : "=m" (*d)                     : "m" (*a), "m" (*b)                     : "%mm0", "%mm1", "%mm2", "%mm3", "%mm4", "%mm5", "%mm6", "%mm7");
name|a
operator|++
expr_stmt|;
name|b
operator|++
expr_stmt|;
name|d
operator|++
expr_stmt|;
block|}
if|if
condition|(
name|n_pixels
operator|>
literal|0
condition|)
block|{
asm|asm
specifier|volatile
asm|("  movd       %1,%%mm2\n"                     "\tmovd       %2,%%mm3\n"                     "\tmovq    %%mm2,%%mm4\n"                     "\tpaddusb %%mm3,%%mm4\n"                     "\tmovq    %%mm0,%%mm1\n"                     "\tpandn   %%mm4,%%mm1\n"                     "\tpminub  %%mm3,%%mm2\n"                     "\tpand    %%mm0,%%mm2\n"                     "\tpor     %%mm2,%%mm1\n"                     "\tmovd    %%mm1,%0\n"                     : "=m" (*d)                     : "m" (*a), "m" (*b)                     : "%mm0", "%mm1", "%mm2", "%mm3", "%mm4", "%mm5", "%mm6", "%mm7");
block|}
asm|asm("emms");
block|}
end_function

begin_function
name|void
DECL|function|gimp_composite_darken_rgba8_rgba8_rgba8_sse2 (GimpCompositeContext * _op)
name|gimp_composite_darken_rgba8_rgba8_rgba8_sse2
parameter_list|(
name|GimpCompositeContext
modifier|*
name|_op
parameter_list|)
block|{
name|uint64
modifier|*
name|d
decl_stmt|;
name|uint64
modifier|*
name|a
decl_stmt|;
name|uint64
modifier|*
name|b
decl_stmt|;
name|uint128
modifier|*
name|D
init|=
operator|(
name|uint128
operator|*
operator|)
name|_op
operator|->
name|D
decl_stmt|;
name|uint128
modifier|*
name|A
init|=
operator|(
name|uint128
operator|*
operator|)
name|_op
operator|->
name|A
decl_stmt|;
name|uint128
modifier|*
name|B
init|=
operator|(
name|uint128
operator|*
operator|)
name|_op
operator|->
name|B
decl_stmt|;
name|gulong
name|n_pixels
init|=
name|_op
operator|->
name|n_pixels
decl_stmt|;
for|for
control|(
init|;
name|n_pixels
operator|>=
literal|4
condition|;
name|n_pixels
operator|-=
literal|4
control|)
block|{
asm|asm
specifier|volatile
asm|("  movdqu          %1,%%xmm2\n"                     "\tmovdqu          %2,%%xmm3\n"                     "\tpminub      %%xmm3,%%xmm2\n"                     "\tmovdqu      %%xmm2,%0\n"                     : "=m" (*D)                     : "m" (*A), "m" (*B)                     : "%xmm2", "%xmm3");
name|A
operator|++
expr_stmt|;
name|B
operator|++
expr_stmt|;
name|D
operator|++
expr_stmt|;
block|}
name|a
operator|=
operator|(
name|uint64
operator|*
operator|)
name|A
expr_stmt|;
name|b
operator|=
operator|(
name|uint64
operator|*
operator|)
name|B
expr_stmt|;
name|d
operator|=
operator|(
name|uint64
operator|*
operator|)
name|D
expr_stmt|;
for|for
control|(
init|;
name|n_pixels
operator|>=
literal|2
condition|;
name|n_pixels
operator|-=
literal|2
control|)
block|{
asm|asm
specifier|volatile
asm|("  movq   %1,%%mm2\n"                     "\tmovq   %2,%%mm3\n"                     "\tpminub %%mm3,%%mm2\n"                     "\tmovntq %%mm2,%0\n"                     : "=m" (*d)                     : "m" (*a), "m" (*b)                     : "%mm2", "%mm3");
name|a
operator|++
expr_stmt|;
name|b
operator|++
expr_stmt|;
name|d
operator|++
expr_stmt|;
block|}
if|if
condition|(
name|n_pixels
operator|>
literal|0
condition|)
block|{
asm|asm
specifier|volatile
asm|("  movd       %1, %%mm2\n"                     "\tmovd       %2, %%mm3\n"                     "\tpminub  %%mm3, %%mm2\n"                     "\tmovd    %%mm2, %0\n"                     : "=m" (*d)                     : "m" (*a), "m" (*b)                     : "%mm2", "%mm3", "%mm4");
block|}
asm|asm("emms");
block|}
end_function

begin_function
name|void
DECL|function|gimp_composite_difference_rgba8_rgba8_rgba8_sse2 (GimpCompositeContext * _op)
name|gimp_composite_difference_rgba8_rgba8_rgba8_sse2
parameter_list|(
name|GimpCompositeContext
modifier|*
name|_op
parameter_list|)
block|{
name|uint64
modifier|*
name|d
decl_stmt|;
name|uint64
modifier|*
name|a
decl_stmt|;
name|uint64
modifier|*
name|b
decl_stmt|;
name|uint128
modifier|*
name|D
init|=
operator|(
name|uint128
operator|*
operator|)
name|_op
operator|->
name|D
decl_stmt|;
name|uint128
modifier|*
name|A
init|=
operator|(
name|uint128
operator|*
operator|)
name|_op
operator|->
name|A
decl_stmt|;
name|uint128
modifier|*
name|B
init|=
operator|(
name|uint128
operator|*
operator|)
name|_op
operator|->
name|B
decl_stmt|;
name|gulong
name|n_pixels
init|=
name|_op
operator|->
name|n_pixels
decl_stmt|;
asm|asm
specifier|volatile
asm|("  movq   %0,%%mm0\n"                 "\tmovdqu %1,%%xmm0"                 :
comment|/*  */
asm|: "m" (*rgba8_alpha_mask_64), "m" (*rgba8_alpha_mask_128)                 : "%mm0", "%xmm0");
for|for
control|(
init|;
name|n_pixels
operator|>=
literal|4
condition|;
name|n_pixels
operator|-=
literal|4
control|)
block|{
asm|asm
specifier|volatile
asm|("  movdqu        %1,%%xmm2\n"                     "\tmovdqu        %2,%%xmm3\n"                     "\tmovdqu    %%xmm2,%%xmm4\n"                     "\tmovdqu    %%xmm3,%%xmm5\n"                     "\tpsubusb   %%xmm3,%%xmm4\n"                     "\tpsubusb   %%xmm2,%%xmm5\n"                     "\tpaddb     %%xmm5,%%xmm4\n"                     "\tmovdqu    %%xmm0,%%xmm1\n"                     "\tpandn     %%xmm4,%%xmm1\n"                     "\tpminub    %%xmm3,%%xmm2\n"                     "\tpand      %%xmm0,%%xmm2\n"                     "\tpor       %%xmm2,%%xmm1\n"                     "\tmovdqu    %%xmm1,%0\n"                     : "=m" (*D)                     : "m" (*A), "m" (*B)                     : "%xmm1", "%xmm2", "%xmm3", "%xmm4", "%xmm5");
name|A
operator|++
expr_stmt|;
name|B
operator|++
expr_stmt|;
name|D
operator|++
expr_stmt|;
block|}
name|a
operator|=
operator|(
name|uint64
operator|*
operator|)
name|A
expr_stmt|;
name|b
operator|=
operator|(
name|uint64
operator|*
operator|)
name|B
expr_stmt|;
name|d
operator|=
operator|(
name|uint64
operator|*
operator|)
name|D
expr_stmt|;
for|for
control|(
init|;
name|n_pixels
operator|>=
literal|2
condition|;
name|n_pixels
operator|-=
literal|2
control|)
block|{
asm|asm
specifier|volatile
asm|("  movq       %1, %%mm2\n"                     "\tmovq       %2, %%mm3\n"                     "\tmovq    %%mm2, %%mm4\n"                     "\tmovq    %%mm3, %%mm5\n"                     "\tpsubusb %%mm3, %%mm4\n"                     "\tpsubusb %%mm2, %%mm5\n"                     "\tpaddb   %%mm5, %%mm4\n"                     "\tmovq    %%mm0, %%mm1\n"                     "\tpandn   %%mm4, %%mm1\n"                     "\tpminub  %%mm3, %%mm2\n"                     "\tpand    %%mm0, %%mm2\n"                     "\tpor     %%mm2, %%mm1\n"                     "\tmovntq  %%mm1, %0\n"                     : "=m" (*d)                     : "m" (*a), "m" (*b)                     : "%mm1", "%mm2", "%mm3", "%mm4", "%mm5");
name|a
operator|++
expr_stmt|;
name|b
operator|++
expr_stmt|;
name|d
operator|++
expr_stmt|;
block|}
if|if
condition|(
name|n_pixels
operator|>
literal|0
condition|)
block|{
asm|asm
specifier|volatile
asm|("  movd       %1, %%mm2\n"                     "\tmovd       %2, %%mm3\n"                     "\tmovq    %%mm2, %%mm4\n"                     "\tmovq    %%mm3, %%mm5\n"                     "\tpsubusb %%mm3, %%mm4\n"                     "\tpsubusb %%mm2, %%mm5\n"                     "\tpaddb   %%mm5, %%mm4\n"                     "\tmovq    %%mm0, %%mm1\n"                     "\tpandn   %%mm4, %%mm1\n"                     "\tpminub  %%mm3, %%mm2\n"                     "\tpand    %%mm0, %%mm2\n"                     "\tpor     %%mm2, %%mm1\n"                     "\tmovd    %%mm1, %0\n"                     : "=m" (*d)                     : "m" (*a), "m" (*b)                     : "%mm1", "%mm2", "%mm3", "%mm4", "%mm5");
block|}
asm|asm("emms");
block|}
end_function

begin_function
name|void
DECL|function|gimp_composite_grain_extract_rgba8_rgba8_rgba8_sse2 (GimpCompositeContext * _op)
name|gimp_composite_grain_extract_rgba8_rgba8_rgba8_sse2
parameter_list|(
name|GimpCompositeContext
modifier|*
name|_op
parameter_list|)
block|{
name|uint64
modifier|*
name|d
decl_stmt|;
name|uint64
modifier|*
name|a
decl_stmt|;
name|uint64
modifier|*
name|b
decl_stmt|;
name|uint128
modifier|*
name|D
init|=
operator|(
name|uint128
operator|*
operator|)
name|_op
operator|->
name|D
decl_stmt|;
name|uint128
modifier|*
name|A
init|=
operator|(
name|uint128
operator|*
operator|)
name|_op
operator|->
name|A
decl_stmt|;
name|uint128
modifier|*
name|B
init|=
operator|(
name|uint128
operator|*
operator|)
name|_op
operator|->
name|B
decl_stmt|;
name|gulong
name|n_pixels
init|=
name|_op
operator|->
name|n_pixels
decl_stmt|;
asm|asm
specifier|volatile
asm|("  movq       %0,%%mm0\n"                 "\tpxor    %%mm6,%%mm6\n"                 "\tmovq       %1,%%mm7\n" 								"\tmovdqu     %2,%%xmm0\n"                 "\tpxor   %%xmm6,%%xmm6\n"                 "\tmovdqu     %3,%%xmm7\n"                 :
comment|/* empty */
asm|: "m" (*rgba8_alpha_mask_64), "m" (*rgba8_w128_64), "m" (*rgba8_alpha_mask_128), "m" (*rgba8_w128_128)                 : "%mm0", "%mm6", "%mm7", "%xmm0", "%xmm6", "%xmm7");
for|for
control|(
init|;
name|n_pixels
operator|>=
literal|4
condition|;
name|n_pixels
operator|-=
literal|4
control|)
block|{
asm|asm
specifier|volatile
asm|("  movdqu       %1,%%xmm2\n"                     "\tmovdqu       %2,%%xmm3\n"                     xmm_low_bytes_to_words(xmm2,xmm4,xmm6)                     xmm_low_bytes_to_words(xmm3,xmm5,xmm6)                     "\tpsubw     %%xmm5,%%xmm4\n"                     "\tpaddw     %%xmm7,%%xmm4\n"                     "\tmovdqu    %%xmm4,%%xmm1\n"                      xmm_high_bytes_to_words(xmm2,xmm4,xmm6)                     xmm_high_bytes_to_words(xmm3,xmm5,xmm6)                      "\tpsubw     %%xmm5,%%xmm4\n"                     "\tpaddw     %%xmm7,%%xmm4\n"                      "\tpackuswb  %%xmm4,%%xmm1\n"                     "\tmovdqu    %%xmm1,%%xmm4\n"                      "\tmovdqu    %%xmm0,%%xmm1\n"                     "\tpandn     %%xmm4,%%xmm1\n"                      "\tpminub    %%xmm3,%%xmm2\n"                     "\tpand      %%xmm0,%%xmm2\n"                      "\tpor       %%xmm2,%%xmm1\n"                     "\tmovdqu    %%xmm1,%0\n"                     : "=m" (*D)                     : "m" (*A), "m" (*B)                     : "%xmm1", "%xmm2", "%xmm3", "%xmm4", "%xmm5");
name|A
operator|++
expr_stmt|;
name|B
operator|++
expr_stmt|;
name|D
operator|++
expr_stmt|;
block|}
name|a
operator|=
operator|(
name|uint64
operator|*
operator|)
name|A
expr_stmt|;
name|b
operator|=
operator|(
name|uint64
operator|*
operator|)
name|B
expr_stmt|;
name|d
operator|=
operator|(
name|uint64
operator|*
operator|)
name|D
expr_stmt|;
for|for
control|(
init|;
name|n_pixels
operator|>=
literal|2
condition|;
name|n_pixels
operator|-=
literal|2
control|)
block|{
asm|asm
specifier|volatile
asm|("  movq         %1,%%mm2\n"                     "\tmovq         %2,%%mm3\n"                     mmx_low_bytes_to_words(mm2,mm4,mm6)                     mmx_low_bytes_to_words(mm3,mm5,mm6)                     "\tpsubw     %%mm5,%%mm4\n"                     "\tpaddw     %%mm7,%%mm4\n"                     "\tmovq      %%mm4,%%mm1\n"                      mmx_high_bytes_to_words(mm2,mm4,mm6)                     mmx_high_bytes_to_words(mm3,mm5,mm6)                      "\tpsubw     %%mm5,%%mm4\n"                     "\tpaddw     %%mm7,%%mm4\n"                      "\tpackuswb  %%mm4,%%mm1\n"                     "\tmovq      %%mm1,%%mm4\n"                      "\tmovq      %%mm0,%%mm1\n"                     "\tpandn     %%mm4,%%mm1\n"                      "\tpminub    %%mm3,%%mm2\n"                     "\tpand      %%mm0,%%mm2\n"                      "\tpor       %%mm2,%%mm1\n"                     "\tmovntq    %%mm1,%0\n"                     : "=m" (*d)                     : "m" (*a), "m" (*b)                     : "%mm1", "%mm2", "%mm3", "%mm4", "%mm5");
name|a
operator|++
expr_stmt|;
name|b
operator|++
expr_stmt|;
name|d
operator|++
expr_stmt|;
block|}
if|if
condition|(
name|n_pixels
operator|>
literal|0
condition|)
block|{
asm|asm
specifier|volatile
asm|("  movd         %1, %%mm2\n"                     "\tmovd         %2, %%mm3\n"                     mmx_low_bytes_to_words(mm2,mm4,mm6)                     mmx_low_bytes_to_words(mm3,mm5,mm6)                     "\tpsubw     %%mm5, %%mm4\n"                     "\tpaddw     %%mm7, %%mm4\n"                     "\tmovq      %%mm4, %%mm1\n"                     "\tpackuswb  %%mm6, %%mm1\n"                     "\tmovq      %%mm1, %%mm4\n"                     "\tmovq      %%mm0, %%mm1\n"                     "\tpandn     %%mm4, %%mm1\n"                     "\tpminub    %%mm3, %%mm2\n"                     "\tpand      %%mm0, %%mm2\n"                     "\tpor       %%mm2, %%mm1\n"                     "\tmovd      %%mm1, %0\n"                     : "=m" (*d)                     : "m" (*a), "m" (*b)                     : "%mm1", "%mm2", "%mm3", "%mm4", "%mm5");
block|}
asm|asm("emms");
block|}
end_function

begin_function
name|void
DECL|function|gimp_composite_lighten_rgba8_rgba8_rgba8_sse2 (GimpCompositeContext * _op)
name|gimp_composite_lighten_rgba8_rgba8_rgba8_sse2
parameter_list|(
name|GimpCompositeContext
modifier|*
name|_op
parameter_list|)
block|{
name|uint64
modifier|*
name|d
decl_stmt|;
name|uint64
modifier|*
name|a
decl_stmt|;
name|uint64
modifier|*
name|b
decl_stmt|;
name|uint128
modifier|*
name|D
init|=
operator|(
name|uint128
operator|*
operator|)
name|_op
operator|->
name|D
decl_stmt|;
name|uint128
modifier|*
name|A
init|=
operator|(
name|uint128
operator|*
operator|)
name|_op
operator|->
name|A
decl_stmt|;
name|uint128
modifier|*
name|B
init|=
operator|(
name|uint128
operator|*
operator|)
name|_op
operator|->
name|B
decl_stmt|;
name|gulong
name|n_pixels
init|=
name|_op
operator|->
name|n_pixels
decl_stmt|;
asm|asm
specifier|volatile
asm|("  movdqu    %0,%%xmm0\n"                 "\tmovq      %1,%%mm0"                 :
comment|/* empty */
asm|: "m" (*rgba8_alpha_mask_128), "m" (*rgba8_alpha_mask_64)                 : "%xmm0", "%mm0");
for|for
control|(
init|;
name|n_pixels
operator|>=
literal|4
condition|;
name|n_pixels
operator|-=
literal|4
control|)
block|{
asm|asm
specifier|volatile
asm|("  movdqu      %1, %%xmm2\n"                     "\tmovdqu      %2, %%xmm3\n"                     "\tmovdqu  %%xmm2, %%xmm4\n"                     "\tpmaxub  %%xmm3, %%xmm4\n"                     "\tmovdqu  %%xmm0, %%xmm1\n"                     "\tpandn   %%xmm4, %%xmm1\n"                     "\tpminub  %%xmm2, %%xmm3\n"                     "\tpand    %%xmm0, %%xmm3\n"                     "\tpor     %%xmm3, %%xmm1\n"                     "\tmovdqu  %%xmm1, %0\n"                     : "=m" (*D)                     : "m" (*A), "m" (*B)                     : "%xmm1", "%xmm2", "%xmm3", "%xmm4");
name|A
operator|++
expr_stmt|;
name|B
operator|++
expr_stmt|;
name|D
operator|++
expr_stmt|;
block|}
name|a
operator|=
operator|(
name|uint64
operator|*
operator|)
name|A
expr_stmt|;
name|b
operator|=
operator|(
name|uint64
operator|*
operator|)
name|B
expr_stmt|;
name|d
operator|=
operator|(
name|uint64
operator|*
operator|)
name|D
expr_stmt|;
for|for
control|(
init|;
name|n_pixels
operator|>=
literal|2
condition|;
name|n_pixels
operator|-=
literal|2
control|)
block|{
asm|asm
specifier|volatile
asm|("  movq       %1, %%mm2\n"                     "\tmovq       %2, %%mm3\n"                     "\tmovq    %%mm2, %%mm4\n"                     "\tpmaxub  %%mm3, %%mm4\n"                     "\tmovq    %%mm0, %%mm1\n"                     "\tpandn   %%mm4, %%mm1\n"                     "\tpminub  %%mm2, %%mm3\n"                     "\tpand    %%mm0, %%mm3\n"                     "\tpor     %%mm3, %%mm1\n"                     "\tmovntq  %%mm1, %0\n"                     : "=m" (*d)                     : "m" (*a), "m" (*b)                     : "%mm1", "%mm2", "%mm3", "%mm4");
name|a
operator|++
expr_stmt|;
name|b
operator|++
expr_stmt|;
name|d
operator|++
expr_stmt|;
block|}
if|if
condition|(
name|n_pixels
operator|>
literal|0
condition|)
block|{
asm|asm
specifier|volatile
asm|("  movd       %1, %%mm2\n"                     "\tmovd       %2, %%mm3\n"                     "\tmovq    %%mm2, %%mm4\n"                     "\tpmaxub  %%mm3, %%mm4\n"                     "\tmovq    %%mm0, %%mm1\n"                     "\tpandn   %%mm4, %%mm1\n"                     "\tpminub  %%mm2, %%mm3\n"                     "\tpand    %%mm0, %%mm3\n"                     "\tpor     %%mm3, %%mm1\n"                     "\tmovd    %%mm1, %0\n"                     : "=m" (*d)                     : "m" (*a), "m" (*b)                     : "%mm1", "%mm2", "%mm3", "%mm4");
block|}
asm|asm("emms");
block|}
end_function

begin_function
name|void
DECL|function|gimp_composite_subtract_rgba8_rgba8_rgba8_sse2 (GimpCompositeContext * _op)
name|gimp_composite_subtract_rgba8_rgba8_rgba8_sse2
parameter_list|(
name|GimpCompositeContext
modifier|*
name|_op
parameter_list|)
block|{
name|uint64
modifier|*
name|d
decl_stmt|;
name|uint64
modifier|*
name|a
decl_stmt|;
name|uint64
modifier|*
name|b
decl_stmt|;
name|uint128
modifier|*
name|D
init|=
operator|(
name|uint128
operator|*
operator|)
name|_op
operator|->
name|D
decl_stmt|;
name|uint128
modifier|*
name|A
init|=
operator|(
name|uint128
operator|*
operator|)
name|_op
operator|->
name|A
decl_stmt|;
name|uint128
modifier|*
name|B
init|=
operator|(
name|uint128
operator|*
operator|)
name|_op
operator|->
name|B
decl_stmt|;
name|gulong
name|n_pixels
init|=
name|_op
operator|->
name|n_pixels
decl_stmt|;
asm|asm
specifier|volatile
asm|("  movq    %0,%%mm0\n"                 "\tmovdqu  %1,%%xmm0\n"                 :
comment|/* empty */
asm|: "m" (*rgba8_alpha_mask_64), "m" (*rgba8_alpha_mask_128)                 : "%mm0", "%xmm0");
for|for
control|(
init|;
name|n_pixels
operator|>=
literal|4
condition|;
name|n_pixels
operator|-=
literal|4
control|)
block|{
asm|asm
specifier|volatile
asm|("  movdqu       %1,%%xmm2\n"                     "\tmovdqu       %2,%%xmm3\n"                     "\tmovdqu   %%xmm2,%%xmm4\n"                     "\tpsubusb  %%xmm3,%%xmm4\n"                      "\tmovdqu   %%xmm0,%%xmm1\n"                     "\tpandn    %%xmm4,%%xmm1\n"                     "\tpminub   %%xmm3,%%xmm2\n"                     "\tpand     %%xmm0,%%xmm2\n"                     "\tpor      %%xmm2,%%xmm1\n"                     "\tmovdqu   %%xmm1,%0\n"                     : "=m" (*D)                     : "m" (*A), "m" (*B)                     : "%xmm1", "%xmm2", "%xmm3", "%xmm4");
name|A
operator|++
expr_stmt|;
name|B
operator|++
expr_stmt|;
name|D
operator|++
expr_stmt|;
block|}
name|a
operator|=
operator|(
name|uint64
operator|*
operator|)
name|A
expr_stmt|;
name|b
operator|=
operator|(
name|uint64
operator|*
operator|)
name|B
expr_stmt|;
name|d
operator|=
operator|(
name|uint64
operator|*
operator|)
name|D
expr_stmt|;
for|for
control|(
init|;
name|n_pixels
operator|>=
literal|2
condition|;
name|n_pixels
operator|-=
literal|2
control|)
block|{
asm|asm
specifier|volatile
asm|("  movq       %1,%%mm2\n"                     "\tmovq       %2,%%mm3\n"                     "\tmovq    %%mm2,%%mm4\n"                     "\tpsubusb %%mm3,%%mm4\n"                     "\tmovq    %%mm0,%%mm1\n"                     "\tpandn   %%mm4,%%mm1\n"                     "\tpminub  %%mm3,%%mm2\n"                     "\tpand    %%mm0,%%mm2\n"                     "\tpor     %%mm2,%%mm1\n"                     "\tmovntq  %%mm1,%0\n"                     : "=m" (*d)                     : "m" (*a), "m" (*b)                     : "%mm1", "%mm2", "%mm3", "%mm4");
name|a
operator|++
expr_stmt|;
name|b
operator|++
expr_stmt|;
name|d
operator|++
expr_stmt|;
block|}
if|if
condition|(
name|n_pixels
operator|>
literal|0
condition|)
block|{
asm|asm
specifier|volatile
asm|("  movd       %1,%%mm2\n"                     "\tmovd       %2,%%mm3\n"                     "\tmovq    %%mm2,%%mm4\n"                     "\tpsubusb %%mm3,%%mm4\n"                     "\tmovq    %%mm0,%%mm1\n"                     "\tpandn   %%mm4,%%mm1\n"                     "\tpminub  %%mm3,%%mm2\n"                     "\tpand    %%mm0,%%mm2\n"                     "\tpor     %%mm2,%%mm1\n"                     "\tmovd    %%mm1,%0\n"                     : "=m" (*d)                     : "m" (*a), "m" (*b)                     : "%mm1", "%mm2", "%mm3", "%mm4");
block|}
asm|asm("emms");
block|}
end_function

begin_function
name|void
DECL|function|gimp_composite_swap_rgba8_rgba8_rgba8_sse2 (GimpCompositeContext * _op)
name|gimp_composite_swap_rgba8_rgba8_rgba8_sse2
parameter_list|(
name|GimpCompositeContext
modifier|*
name|_op
parameter_list|)
block|{
name|GimpCompositeContext
name|op
init|=
operator|*
name|_op
decl_stmt|;
comment|/*    * Inhale one whole i686 cache line at once. 128 bytes == 32 rgba8    * pixels == 8 128 bit xmm registers.    */
for|for
control|(
init|;
name|op
operator|.
name|n_pixels
operator|>=
literal|16
condition|;
name|op
operator|.
name|n_pixels
operator|-=
literal|16
control|)
block|{
asm|asm
specifier|volatile
asm|("  movdqu      %0,%%xmm0\n" : :"m" (op.A[0]) : "%xmm0");
asm|asm
specifier|volatile
asm|("  movdqu      %0,%%xmm1\n" : :"m" (op.B[0]) : "%xmm1");
asm|asm
specifier|volatile
asm|("  movdqu      %0,%%xmm2\n" : :"m" (op.A[1]) : "%xmm2");
asm|asm
specifier|volatile
asm|("  movdqu      %0,%%xmm3\n" : :"m" (op.B[1]) : "%xmm3");
asm|asm
specifier|volatile
asm|("  movdqu      %0,%%xmm4\n" : :"m" (op.A[2]) : "%xmm4");
asm|asm
specifier|volatile
asm|("  movdqu      %0,%%xmm5\n" : :"m" (op.B[2]) : "%xmm5");
asm|asm
specifier|volatile
asm|("  movdqu      %0,%%xmm6\n" : :"m" (op.A[3]) : "%xmm6");
asm|asm
specifier|volatile
asm|("  movdqu      %0,%%xmm7\n" : :"m" (op.B[3]) : "%xmm7");
asm|asm
specifier|volatile
asm|("\tmovdqu      %%xmm0,%0\n" : "=m" (op.A[0]));
asm|asm
specifier|volatile
asm|("\tmovdqu      %%xmm1,%0\n" : "=m" (op.B[0]));
asm|asm
specifier|volatile
asm|("\tmovdqu      %%xmm2,%0\n" : "=m" (op.A[1]));
asm|asm
specifier|volatile
asm|("\tmovdqu      %%xmm3,%0\n" : "=m" (op.B[1]));
asm|asm
specifier|volatile
asm|("\tmovdqu      %%xmm4,%0\n" : "=m" (op.A[2]));
asm|asm
specifier|volatile
asm|("\tmovdqu      %%xmm5,%0\n" : "=m" (op.B[2]));
asm|asm
specifier|volatile
asm|("\tmovdqu      %%xmm6,%0\n" : "=m" (op.A[3]));
asm|asm
specifier|volatile
asm|("\tmovdqu      %%xmm7,%0\n" : "=m" (op.B[3]));
name|op
operator|.
name|A
operator|+=
literal|64
expr_stmt|;
name|op
operator|.
name|B
operator|+=
literal|64
expr_stmt|;
block|}
for|for
control|(
init|;
name|op
operator|.
name|n_pixels
operator|>=
literal|4
condition|;
name|op
operator|.
name|n_pixels
operator|-=
literal|4
control|)
block|{
asm|asm
specifier|volatile
asm|("  movdqu      %0,%%xmm2\n"                     "\tmovdqu      %1,%%xmm3\n"                     "\tmovdqu  %%xmm3,%0\n"                     "\tmovdqu  %%xmm2,%1\n"                     : "+m" (*op.A), "+m" (*op.B)                     :
comment|/* empty */
asm|: "%xmm2", "%xmm3");
name|op
operator|.
name|A
operator|+=
literal|16
expr_stmt|;
name|op
operator|.
name|B
operator|+=
literal|16
expr_stmt|;
block|}
for|for
control|(
init|;
name|op
operator|.
name|n_pixels
operator|>=
literal|2
condition|;
name|op
operator|.
name|n_pixels
operator|-=
literal|2
control|)
block|{
asm|asm
specifier|volatile
asm|("  movq      %0,%%mm2\n"                     "\tmovq      %1,%%mm3\n"                     "\tmovq   %%mm3,%0\n"                     "\tmovntq %%mm2,%1\n"                     : "+m" (*op.A), "+m" (*op.B)                     :
comment|/* empty */
asm|: "%mm2", "%mm3");
name|op
operator|.
name|A
operator|+=
literal|8
expr_stmt|;
name|op
operator|.
name|B
operator|+=
literal|8
expr_stmt|;
block|}
if|if
condition|(
name|op
operator|.
name|n_pixels
condition|)
block|{
asm|asm
specifier|volatile
asm|("  movd      %0,%%mm2\n"                     "\tmovd      %1,%%mm3\n"                     "\tmovd   %%mm3,%0\n"                     "\tmovd   %%mm2,%1\n"                     : "+m" (*op.A), "+m" (*op.B)                     :
comment|/* empty */
asm|: "%mm3", "%mm4");
block|}
asm|asm("emms");
block|}
end_function

begin_endif
endif|#
directive|endif
end_endif

begin_comment
comment|/* COMPILE_SSE2_IS_OKAY */
end_comment

end_unit

