begin_unit|revision:0.9.5;language:C;cregit-version:0.0.1
begin_comment
comment|/* The GIMP -- an image manipulation program  * Copyright (C) 1995 Spencer Kimball and Peter Mattis  *  * -*- mode: c tab-width: 2; c-basic-indent: 2; indent-tabs-mode: nil -*-  *  * This program is free software; you can redistribute it and/or modify  * it under the terms of the GNU General Public License as published by  * the Free Software Foundation; either version 2 of the License, or  * (at your option) any later version.  *  * Gimp image compositing  * Copyright (C) 2003  Helvetix Victorinox, a pseudonym,<helvetix@gimp.org>  *  * This program is distributed in the hope that it will be useful,  * but WITHOUT ANY WARRANTY; without even the implied warranty of  * MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the  * GNU General Public License for more details.  *  * You should have received a copy of the GNU General Public License  * along with this program; if not, write to the Free Software  * Foundation, Inc., 59 Temple Place - Suite 330, Boston, MA 02111-1307, USA.  */
end_comment

begin_include
include|#
directive|include
file|"config.h"
end_include

begin_if
if|#
directive|if
name|defined
argument_list|(
name|USE_SSE
argument_list|)
end_if

begin_if
if|#
directive|if
name|defined
argument_list|(
name|ARCH_X86
argument_list|)
end_if

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

begin_if
if|#
directive|if
name|__GNUC__
operator|>=
literal|3
end_if

begin_define
DECL|macro|pminub (src,dst,tmp)
define|#
directive|define
name|pminub
parameter_list|(
name|src
parameter_list|,
name|dst
parameter_list|,
name|tmp
parameter_list|)
value|"pminub " "%%" #src ", %%" #dst
end_define

begin_define
DECL|macro|pmaxub (src,dst,tmp)
define|#
directive|define
name|pmaxub
parameter_list|(
name|src
parameter_list|,
name|dst
parameter_list|,
name|tmp
parameter_list|)
value|"pmaxub " "%%" #src ", %%" #dst
end_define

begin_decl_stmt
DECL|variable|rgba8_alpha_mask_128
specifier|const
specifier|static
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
specifier|const
specifier|static
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
specifier|const
specifier|static
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
specifier|const
specifier|static
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
specifier|const
specifier|static
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
specifier|const
specifier|static
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
specifier|const
specifier|static
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
specifier|const
specifier|static
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
specifier|const
specifier|static
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
specifier|const
specifier|static
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
specifier|const
specifier|static
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
specifier|const
specifier|static
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
specifier|const
specifier|static
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
specifier|const
specifier|static
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
specifier|const
specifier|static
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
specifier|const
specifier|static
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
specifier|const
specifier|static
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
specifier|const
specifier|static
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
specifier|const
specifier|static
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
specifier|const
specifier|static
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
specifier|const
specifier|static
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
specifier|const
specifier|static
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
specifier|const
specifier|static
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
specifier|const
specifier|static
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
name|GimpCompositeContext
name|op
init|=
operator|*
name|_op
decl_stmt|;
asm|asm
specifier|volatile
asm|("movdqu    %0,%%xmm0"                 :
comment|/* empty */
asm|: "m" (*rgba8_alpha_mask_128)                 : "%xmm0");
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
asm|asm ("  movdqu  %0, %%xmm2\n"            "\tmovdqu  %1, %%xmm3\n"            "\tmovdqu  %%xmm2, %%xmm4\n"            "\tpaddusb %%xmm3, %%xmm4\n"             "\tmovdqu  %%xmm0, %%xmm1\n"            "\tpandn   %%xmm4, %%xmm1\n"            "\t" pminub(xmm3, xmm2, xmm4) "\n"            "\tpand    %%xmm0, %%xmm2\n"            "\tpor     %%xmm2, %%xmm1\n"            "\tmovdqu  %%xmm1, %2\n"            :
comment|/* empty */
asm|: "m" (*op.A), "m" (*op.B), "m" (*op.D)            : "0", "1", "2", "%xmm0", "%xmm1", "%xmm2", "%xmm3", "%xmm4", "%xmm5", "%xmm6", "%xmm7");
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
name|op
operator|.
name|D
operator|+=
literal|16
expr_stmt|;
block|}
asm|asm
specifier|volatile
asm|("movq    %0,%%mm0"                     :
comment|/* empty */
asm|: "m" (*rgba8_alpha_mask_64)                 : "%mm0");
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
asm|asm ("  movq       %0, %%mm2\n"            "\tmovq       %1, %%mm3\n"            "\tmovq    %%mm2, %%mm4\n"            "\tpaddusb %%mm3, %%mm4\n"            "\tmovq    %%mm0, %%mm1\n"            "\tpandn   %%mm4, %%mm1\n"            "\t" pminub(mm3, mm2, mm4) "\n"            "\tpand    %%mm0, %%mm2\n"            "\tpor     %%mm2, %%mm1\n"            "\tmovq    %%mm1, %2\n"            :
comment|/* empty */
asm|: "m" (*op.A), "m" (*op.B), "m" (*op.D)            : "0", "1", "2", "%mm0", "%mm1", "%mm2", "%mm3", "%mm4", "%mm5", "%mm6", "%mm7");
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
name|op
operator|.
name|D
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
asm|("  movd    (%0), %%mm2;\n"                     "\tmovd    (%1), %%mm3;\n"                     "\tmovq    %%mm2, %%mm4\n"                     "\tpaddusb %%mm3, %%mm4\n"                     "\tmovq    %%mm0, %%mm1\n"                     "\tpandn   %%mm4, %%mm1\n"                     "\t" pminub(mm3, mm2, mm4) "\n"                     "\tpand    %%mm0, %%mm2\n"                     "\tpor     %%mm2, %%mm1\n"                     "\tmovd    %%mm1, (%2);\n"                     :
comment|/* empty */
asm|: "r" (op.A), "r" (op.B), "r" (op.D)                     : "0", "1", "2", "%mm0", "%mm1", "%mm2", "%mm3", "%mm4", "%mm5", "%mm6", "%mm7");
block|}
asm|asm("emms");
block|}
end_function

begin_function
name|void
DECL|function|xxxgimp_composite_burn_rgba8_rgba8_rgba8_sse2 (GimpCompositeContext * _op)
name|xxxgimp_composite_burn_rgba8_rgba8_rgba8_sse2
parameter_list|(
name|GimpCompositeContext
modifier|*
name|_op
parameter_list|)
block|{  }
end_function

begin_function
name|void
DECL|function|xxxgimp_composite_darken_rgba8_rgba8_rgba8_sse2 (GimpCompositeContext * _op)
name|xxxgimp_composite_darken_rgba8_rgba8_rgba8_sse2
parameter_list|(
name|GimpCompositeContext
modifier|*
name|_op
parameter_list|)
block|{  }
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
name|GimpCompositeContext
name|op
init|=
operator|*
name|_op
decl_stmt|;
asm|asm
specifier|volatile
asm|("  movq   %0,%%mm0\n"                 "\tmovdqu %1,%%xmm0"                 :                 : "m" (*rgba8_alpha_mask_64), "m" (*rgba8_alpha_mask_128)                 : "%mm0");
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
asm|("  movdqu        %0,%%xmm2\n"                     "\tmovdqu        %1,%%xmm3\n"                     "\tmovdqu    %%xmm2,%%xmm4\n"                     "\tmovdqu    %%xmm3,%%xmm5\n"                     "\tpsubusb   %%xmm3,%%xmm4\n"                     "\tpsubusb   %%xmm2,%%xmm5\n"                     "\tpaddb     %%xmm5,%%xmm4\n"                     "\tmovdqu    %%xmm0,%%xmm1\n"                     "\tpandn     %%xmm4,%%xmm1\n"                     "\tpminub    %%xmm3,%%xmm2\n"                     "\tpand      %%xmm0,%%xmm2\n"                     "\tpor       %%xmm2,%%xmm1\n"                     "\tmovdqu    %%xmm1,%2\n"                     :
comment|/* empty */
asm|: "m" (*op.A), "m" (*op.B), "m" (*op.D)                     : "0", "1", "2", "%xmm1", "%xmm2", "%xmm3", "%xmm4", "%xmm5");
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
name|op
operator|.
name|D
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
asm|("  movq       %0, %%mm2\n"                     "\tmovq       %1, %%mm3\n"                     "\tmovq    %%mm2, %%mm4\n"                     "\tmovq    %%mm3, %%mm5\n"                     "\tpsubusb %%mm3, %%mm4\n"                     "\tpsubusb %%mm2, %%mm5\n"                     "\tpaddb   %%mm5, %%mm4\n"                     "\tmovq    %%mm0, %%mm1\n"                     "\tpandn   %%mm4, %%mm1\n"                     "\tpminub  %%mm3, %%mm2\n"                     "\tpand    %%mm0, %%mm2\n"                     "\tpor     %%mm2, %%mm1\n"                     "\tmovq    %%mm1, %2\n"                     :
comment|/* empty */
asm|: "m" (*op.A), "m" (*op.B), "m" (*op.D)                     : "0", "1", "2", "%mm1", "%mm2", "%mm3", "%mm4", "%mm5");
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
name|op
operator|.
name|D
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
asm|("  movd       %0, %%mm2\n"                     "\tmovd       %1, %%mm3\n"                     "\tmovq    %%mm2, %%mm4\n"                     "\tmovq    %%mm3, %%mm5\n"                     "\tpsubusb %%mm3, %%mm4\n"                     "\tpsubusb %%mm2, %%mm5\n"                     "\tpaddb   %%mm5, %%mm4\n"                     "\tmovq    %%mm0, %%mm1\n"                     "\tpandn   %%mm4, %%mm1\n"                     "\tpminub  %%mm3, %%mm2\n"                     "\tpand    %%mm0, %%mm2\n"                     "\tpor     %%mm2, %%mm1\n"                     "\tmovd    %%mm1, %2\n"                     :
comment|/* empty */
asm|: "m" (*op.A), "m" (*op.B), "m" (*op.D)                     : "0", "1", "2", "%mm1", "%mm2", "%mm3", "%mm4");
block|}
asm|asm("emms");
block|}
end_function

begin_function
name|void
DECL|function|xxxgimp_composite_divide_rgba8_rgba8_rgba8_sse2 (GimpCompositeContext * _op)
name|xxxgimp_composite_divide_rgba8_rgba8_rgba8_sse2
parameter_list|(
name|GimpCompositeContext
modifier|*
name|_op
parameter_list|)
block|{ }
end_function

begin_function
name|void
DECL|function|xxxgimp_composite_dodge_rgba8_rgba8_rgba8_sse2 (GimpCompositeContext * _op)
name|xxxgimp_composite_dodge_rgba8_rgba8_rgba8_sse2
parameter_list|(
name|GimpCompositeContext
modifier|*
name|_op
parameter_list|)
block|{ }
end_function

begin_function
name|void
DECL|function|xxxgimp_composite_grain_extract_rgba8_rgba8_rgba8_sse2 (GimpCompositeContext * _op)
name|xxxgimp_composite_grain_extract_rgba8_rgba8_rgba8_sse2
parameter_list|(
name|GimpCompositeContext
modifier|*
name|_op
parameter_list|)
block|{  }
end_function

begin_function
name|void
DECL|function|xxxgimp_composite_grain_merge_rgba8_rgba8_rgba8_sse2 (GimpCompositeContext * _op)
name|xxxgimp_composite_grain_merge_rgba8_rgba8_rgba8_sse2
parameter_list|(
name|GimpCompositeContext
modifier|*
name|_op
parameter_list|)
block|{  }
end_function

begin_function
name|void
DECL|function|xxxgimp_composite_lighten_rgba8_rgba8_rgba8_sse2 (GimpCompositeContext * _op)
name|xxxgimp_composite_lighten_rgba8_rgba8_rgba8_sse2
parameter_list|(
name|GimpCompositeContext
modifier|*
name|_op
parameter_list|)
block|{ }
end_function

begin_function
name|void
DECL|function|xxxgimp_composite_multiply_rgba8_rgba8_rgba8_sse2 (GimpCompositeContext * _op)
name|xxxgimp_composite_multiply_rgba8_rgba8_rgba8_sse2
parameter_list|(
name|GimpCompositeContext
modifier|*
name|_op
parameter_list|)
block|{ }
end_function

begin_function
name|void
DECL|function|xxxgimp_composite_overlay_rgba8_rgba8_rgba8_sse2 (GimpCompositeContext * _op)
name|xxxgimp_composite_overlay_rgba8_rgba8_rgba8_sse2
parameter_list|(
name|GimpCompositeContext
modifier|*
name|_op
parameter_list|)
block|{ }
end_function

begin_function
name|void
DECL|function|xxxgimp_composite_scale_rgba8_rgba8_rgba8_sse2 (GimpCompositeContext * _op)
name|xxxgimp_composite_scale_rgba8_rgba8_rgba8_sse2
parameter_list|(
name|GimpCompositeContext
modifier|*
name|_op
parameter_list|)
block|{ }
end_function

begin_function
name|void
DECL|function|xxxgimp_composite_screen_rgba8_rgba8_rgba8_sse2 (GimpCompositeContext * _op)
name|xxxgimp_composite_screen_rgba8_rgba8_rgba8_sse2
parameter_list|(
name|GimpCompositeContext
modifier|*
name|_op
parameter_list|)
block|{ }
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
name|GimpCompositeContext
name|op
init|=
operator|*
name|_op
decl_stmt|;
asm|asm
specifier|volatile
asm|("  movq    %0,%%mm0\n"                 "\tmovdqu  %1,%%xmm0\n"                 :
comment|/* empty */
asm|: "m" (*rgba8_alpha_mask_64), "m" (*rgba8_alpha_mask_128)                 : "%mm0", "%xmm0");
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
asm|("  movdqu       %0,%%xmm2\n"                     "\tmovdqu       %1,%%xmm3\n"                     "\tmovdqu   %%xmm2,%%xmm4\n"                     "\tpsubusb  %%xmm3,%%xmm4\n"                                        "\tmovdqu   %%xmm0,%%xmm1\n"                     "\tpandn    %%xmm4,%%xmm1\n"                     "\t" pminub(xmm3,xmm2,xmm4) "\n"                     "\tpand     %%xmm0,%%xmm2\n"                     "\tpor      %%xmm2,%%xmm1\n"                     "\tmovdqu   %%xmm1,%2\n"                     :
comment|/* empty */
asm|: "m" (*op.A), "m" (*op.B), "m" (*op.D)                     : "0", "1", "2", "%xmm1", "%xmm2", "%xmm3", "%xmm4", "%xmm5");
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
name|op
operator|.
name|D
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
asm|("  movq       %0,%%mm2\n"                     "\tmovq       %1,%%mm3\n"                      "\tmovq    %%mm2,%%mm4\n"                     "\tpsubusb %%mm3,%%mm4\n"                                        "\tmovq    %%mm0,%%mm1\n"                     "\tpandn   %%mm4,%%mm1\n"                                          "\t" pminub(mm3,mm2,mm4) "\n"                                          "\tpand    %%mm0,%%mm2\n"                     "\tpor     %%mm2,%%mm1\n"                     "\tmovq    %%mm1,%2\n"                     :
comment|/* empty */
asm|: "m" (*op.A), "m" (*op.B), "m" (*op.D)                     : "0", "1", "2", "%mm1", "%mm2", "%mm3", "%mm4", "%mm5");
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
name|op
operator|.
name|D
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
asm|("  movd       %0,%%mm2\n"                     "\tmovd       %1,%%mm3\n"                      "\tmovq    %%mm2,%%mm4\n"                     "\tpsubusb %%mm3,%%mm4\n"                                        "\tmovq    %%mm0,%%mm1\n"                     "\tpandn   %%mm4,%%mm1\n"                                        "\t" pminub(mm3,mm2,mm4) "\n"                      "\tpand    %%mm0,%%mm2\n"                     "\tpor     %%mm2,%%mm1\n"                     "\tmovd    %%mm1,%2\n"                     :
comment|/* empty */
asm|: "m" (*op.A), "m" (*op.B), "m" (*op.D)                     : "0", "1", "2", "%mm1", "%mm2", "%mm3", "%mm4", "%mm5");
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
comment|/*    * Inhale one whole i686 cache line at once. 64 bytes, 16 rgba8 pixels, 4 128 bit xmm registers.    */
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
asm|("  movdqu      %0,%%xmm0\n"                     "\tmovdqu      %1,%%xmm1\n"                     "\tmovdqu      %2,%%xmm2\n"                     "\tmovdqu      %3,%%xmm3\n"                     "\tmovdqu      %4,%%xmm4\n"                     "\tmovdqu      %5,%%xmm5\n"                     "\tmovdqu      %6,%%xmm6\n"                     "\tmovdqu      %7,%%xmm7\n"                      "\tmovdqu      %%xmm0,%1\n"                     "\tmovdqu      %%xmm1,%0\n"                     "\tmovdqu      %%xmm2,%3\n"                     "\tmovdqu      %%xmm3,%2\n"                     "\tmovdqu      %%xmm4,%5\n"                     "\tmovdqu      %%xmm5,%4\n"                     "\tmovdqu      %%xmm6,%7\n"                     "\tmovdqu      %%xmm7,%6\n"                     :
comment|/* empty */
asm|: "m" (op.A[0]), "m" (op.B[0]),                     "m" (op.A[1]), "m" (op.B[1]),                     "m" (op.A[2]), "m" (op.B[2]),                     "m" (op.A[3]), "m" (op.B[3]) 																				);
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
asm|("  movdqu      %0,%%xmm2\n"                   "\tmovdqu      %1,%%xmm3\n"                   "\tmovdqu  %%xmm3,%0\n"                   "\tmovdqu  %%xmm2,%1\n"                   :
comment|/* empty */
asm|: "m" (*op.A), "m" (*op.B)                   : "0", "1", "%xmm1", "%xmm2", "%xmm3", "%xmm4");
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
asm|("  movq      %0,%%mm2\n"                   "\tmovq      %1,%%mm3\n"                   "\tmovq   %%mm3,%0\n"                   "\tmovq   %%mm2,%1\n"                   :
comment|/* empty */
asm|: "m" (*op.A), "m" (*op.B)                   : "0", "1", "%mm1", "%mm2", "%mm3", "%mm4");
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
asm|("  movd      %0,%%mm2\n"                   "\tmovd      %1,%%mm3\n"                   "\tmovd   %%mm3,%0\n"                   "\tmovd   %%mm2,%1\n"                                     :
comment|/* empty */
asm|: "m" (*op.A), "m" (*op.B)                   : "0", "1", "%mm1", "%mm2", "%mm3", "%mm4");
block|}
asm|asm("emms");
block|}
end_function

begin_endif
endif|#
directive|endif
end_endif

begin_comment
comment|/* __GNUC__> 3 */
end_comment

begin_endif
endif|#
directive|endif
end_endif

begin_comment
comment|/* defined(ARCH_X86) */
end_comment

begin_endif
endif|#
directive|endif
end_endif

begin_comment
comment|/* defined(USE_SSE) */
end_comment

begin_function
name|void
DECL|function|gimp_composite_sse2_init (void)
name|gimp_composite_sse2_init
parameter_list|(
name|void
parameter_list|)
block|{ }
end_function

end_unit

