begin_unit|revision:0.9.5;language:C;cregit-version:0.0.1
begin_comment
comment|/* The GIMP -- an image manipulation program  * Copyright (C) 1995 Spencer Kimball and Peter Mattis  *  * -*- mode: c tab-width: 2; c-basic-indent: 2; indent-tabs-mode: nil -*-  *  * This program is free software; you can redistribute it and/or modify  * it under the terms of the GNU General Public License as published by  * the Free Software Foundation; either version 2 of the License, or  * (at your option) any later version.  *  * This program is distributed in the hope that it will be useful,  * but WITHOUT ANY WARRANTY; without even the implied warranty of  * MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the  * GNU General Public License for more details.  *  * You should have received a copy of the GNU General Public License  * along with this program; if not, write to the Free Software  * Foundation, Inc., 59 Temple Place - Suite 330, Boston, MA 02111-1307, USA.  */
end_comment

begin_comment
comment|/* Much of the content of this file are derivative works of David  * Monniaux which are Copyright (C) 1999, 2001 David Monniaux  * Tip-o-the-hat to David for pioneering this effort.  *  * All of these functions use the mmx registers and expect them to  * remain intact across multiple asm() constructs.  This may not work  * in the future, if the compiler allocates mmx registers for it's own  * use. XXX  */
end_comment

begin_include
include|#
directive|include
file|"config.h"
end_include

begin_ifdef
ifdef|#
directive|ifdef
name|USE_MMX
end_ifdef

begin_if
if|#
directive|if
name|__GNUC__
operator|>=
literal|3
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
file|"gimp-composite-mmx.h"
end_include

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
value|"\tmovq %%" #dst ", %%" #tmp ";" "psubusb %%" #src ", %%" #tmp ";" "psubb %%" #tmp ", %%" #dst "\n"
end_define

begin_define
DECL|macro|pmaxub (a,b,tmp)
define|#
directive|define
name|pmaxub
parameter_list|(
name|a
parameter_list|,
name|b
parameter_list|,
name|tmp
parameter_list|)
value|"\tmovq %%" #a ", %%" #tmp ";" "psubusb %%" #b ", %%" #tmp ";" "paddb %%" #tmp ", %%" #b "\n"
end_define

begin_comment
comment|/*  * Clobbers eax, ecx edx  */
end_comment

begin_comment
comment|/*  * Double-word divide.  Adjusted for subsequent unsigned packing  * (high-order bit of each word is cleared)  */
end_comment

begin_define
DECL|macro|pdivwX (dividend,divisor,quotient)
define|#
directive|define
name|pdivwX
parameter_list|(
name|dividend
parameter_list|,
name|divisor
parameter_list|,
name|quotient
parameter_list|)
value|"movd %%" #dividend ",%%eax; " \                                           "movd %%" #divisor  ",%%ecx; " \                                           "xorl %%edx,%%edx; "           \                                           "divw %%cx; "                  \                                           "roll $16, %%eax; "            \                                           "roll $16, %%ecx; "            \                                           "xorl %%edx,%%edx; "           \                                           "divw %%cx; "                  \                                           "btr $15, %%eax; "             \                                           "roll $16, %%eax; "            \                                           "btr $15, %%eax; "             \                                           "movd %%eax,%%" #quotient ";"
end_define

begin_comment
comment|/*  * Quadword divide.  No adjustment for subsequent unsigned packing  * (high-order bit of each word is left alone)  */
end_comment

begin_define
DECL|macro|pdivwqX (dividend,divisor,quotient)
define|#
directive|define
name|pdivwqX
parameter_list|(
name|dividend
parameter_list|,
name|divisor
parameter_list|,
name|quotient
parameter_list|)
value|"movd   %%" #dividend ",%%eax; " \                                           "movd   %%" #divisor  ",%%ecx; " \                                           "xorl   %%edx,%%edx; "           \                                           "divw   %%cx; "                  \                                           "roll   $16, %%eax; "            \                                           "roll   $16, %%ecx; "            \                                           "xorl   %%edx,%%edx; "           \                                           "divw   %%cx; "                  \                                           "roll   $16, %%eax; "            \                                           "movd   %%eax,%%" #quotient "; " \                                           "psrlq $32,%%" #dividend ";"     \                                           "psrlq $32,%%" #divisor ";"      \                                           "movd   %%" #dividend ",%%eax; " \                                           "movd   %%" #divisor  ",%%ecx; " \                                           "xorl   %%edx,%%edx; "           \                                           "divw   %%cx; "                  \                                           "roll   $16, %%eax; "            \                                           "roll   $16, %%ecx; "            \                                           "xorl   %%edx,%%edx; "           \                                           "divw   %%cx; "                  \                                           "roll   $16, %%eax; "            \                                           "movd   %%eax,%%" #divisor ";"   \                                           "psllq  $32,%%" #divisor ";"     \                                           "por    %%" #divisor ",%%" #quotient ";"
end_define

begin_comment
comment|/*  * Quadword divide.  Adjusted for subsequent unsigned packing  * (high-order bit of each word is cleared)  */
end_comment

begin_define
DECL|macro|pdivwuqX (dividend,divisor,quotient)
define|#
directive|define
name|pdivwuqX
parameter_list|(
name|dividend
parameter_list|,
name|divisor
parameter_list|,
name|quotient
parameter_list|)
define|\
value|pdivwX(dividend,divisor,quotient) \                                             "psrlq  $32,%%" #dividend ";"   \                                             "psrlq  $32,%%" #divisor ";"    \                                           pdivwX(dividend,divisor,quotient) \                                           "movd   %%eax,%%" #divisor ";"    \                                             "psllq  $32,%%" #divisor ";"    \                                             "por    %%" #divisor ",%%" #quotient ";"
end_define

begin_comment
comment|/* equivalent to the INT_MULT() macro in gimp-composite-generic.c */
end_comment

begin_comment
comment|/*  * opr2 = INT_MULT(opr1, opr2, t)  *  * Operates across quad-words using x86 word (16bit) value.  * Result is left in opr2  *  * opr1 = opr1 * opr2 + w128  * opr2 = opr1  * opr2 = ((opr2>> 8) + opr1)>> 8  */
end_comment

begin_define
DECL|macro|pmulwX (opr1,opr2,w128)
define|#
directive|define
name|pmulwX
parameter_list|(
name|opr1
parameter_list|,
name|opr2
parameter_list|,
name|w128
parameter_list|)
define|\
value|"\tpmullw    %%"#opr2", %%"#opr1"; " \                   "\tpaddw     %%"#w128", %%"#opr1"; " \                   "\tmovq      %%"#opr1", %%"#opr2"; " \                   "\tpsrlw     $8,        %%"#opr2"; " \                   "\tpaddw     %%"#opr1", %%"#opr2"; " \                   "\tpsrlw     $8,        %%"#opr2"\n"
end_define

begin_comment
comment|/* a = INT_MULT(a,b) */
end_comment

begin_define
DECL|macro|mmx_int_mult (a,b,w128)
define|#
directive|define
name|mmx_int_mult
parameter_list|(
name|a
parameter_list|,
name|b
parameter_list|,
name|w128
parameter_list|)
define|\
value|"\tpmullw    %%"#b",    %%"#a"; " \                   "\tpaddw     %%"#w128", %%"#a"; " \                   "\tmovq      %%"#a",    %%"#b"; " \                   "\tpsrlw     $8,        %%"#b"; " \                   "\tpaddw     %%"#a",    %%"#b"; " \                   "\tpsrlw     $8,        %%"#b"\n"
end_define

begin_define
DECL|macro|mmx_low_bytes_to_words (src,dst,zero)
define|#
directive|define
name|mmx_low_bytes_to_words
parameter_list|(
name|src
parameter_list|,
name|dst
parameter_list|,
name|zero
parameter_list|)
define|\
value|"\tmovq      %%"#src", %%"#dst"; " \          "\tpunpcklbw %%"#zero", %%"#dst"\n"
end_define

begin_define
DECL|macro|mmx_high_bytes_to_words (src,dst,zero)
define|#
directive|define
name|mmx_high_bytes_to_words
parameter_list|(
name|src
parameter_list|,
name|dst
parameter_list|,
name|zero
parameter_list|)
define|\
value|"\tmovq      %%"#src", %%"#dst"; " \          "\tpunpckhbw %%"#zero", %%"#dst"\n"
end_define

begin_function
name|void
DECL|function|debug_display_mmx (void)
name|debug_display_mmx
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
DECL|macro|print64 (reg)
define|#
directive|define
name|print64
parameter_list|(
name|reg
parameter_list|)
value|{ unsigned long long reg; asm("movq %%" #reg ",%0" : "=m" (reg)); printf(#reg"=%08llx %08llx", mask32(reg>>32), mask32(reg)); }
name|printf
argument_list|(
literal|"--------------------------------------------\n"
argument_list|)
expr_stmt|;
name|print64
argument_list|(
name|mm0
argument_list|)
expr_stmt|;
name|printf
argument_list|(
literal|"  "
argument_list|)
expr_stmt|;
name|print64
argument_list|(
name|mm1
argument_list|)
expr_stmt|;
name|printf
argument_list|(
literal|"\n"
argument_list|)
expr_stmt|;
name|print64
argument_list|(
name|mm2
argument_list|)
expr_stmt|;
name|printf
argument_list|(
literal|"  "
argument_list|)
expr_stmt|;
name|print64
argument_list|(
name|mm3
argument_list|)
expr_stmt|;
name|printf
argument_list|(
literal|"\n"
argument_list|)
expr_stmt|;
name|print64
argument_list|(
name|mm4
argument_list|)
expr_stmt|;
name|printf
argument_list|(
literal|"  "
argument_list|)
expr_stmt|;
name|print64
argument_list|(
name|mm5
argument_list|)
expr_stmt|;
name|printf
argument_list|(
literal|"\n"
argument_list|)
expr_stmt|;
name|print64
argument_list|(
name|mm6
argument_list|)
expr_stmt|;
name|printf
argument_list|(
literal|"  "
argument_list|)
expr_stmt|;
name|print64
argument_list|(
name|mm7
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

begin_decl_stmt
DECL|variable|rgba8_alpha_mask
specifier|const
specifier|static
name|unsigned
name|long
name|rgba8_alpha_mask
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
DECL|variable|rgba8_b1
specifier|const
specifier|static
name|unsigned
name|long
name|rgba8_b1
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
DECL|variable|rgba8_b255
specifier|const
specifier|static
name|unsigned
name|long
name|rgba8_b255
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
DECL|variable|rgba8_w1
specifier|const
specifier|static
name|unsigned
name|long
name|rgba8_w1
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
DECL|variable|rgba8_w2
specifier|const
specifier|static
name|unsigned
name|long
name|rgba8_w2
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
DECL|variable|rgba8_w128
specifier|const
specifier|static
name|unsigned
name|long
name|rgba8_w128
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
DECL|variable|rgba8_w256
specifier|const
specifier|static
name|unsigned
name|long
name|rgba8_w256
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
DECL|variable|rgba8_w255
specifier|const
specifier|static
name|unsigned
name|long
name|rgba8_w255
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
DECL|variable|va8_alpha_mask
specifier|const
specifier|static
name|unsigned
name|long
name|va8_alpha_mask
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
DECL|variable|va8_b255
specifier|const
specifier|static
name|unsigned
name|long
name|va8_b255
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
DECL|variable|va8_w1
specifier|const
specifier|static
name|unsigned
name|long
name|va8_w1
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
DECL|variable|va8_w255
specifier|const
specifier|static
name|unsigned
name|long
name|va8_w255
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

begin_comment
comment|/*  *  */
end_comment

begin_function
name|void
DECL|function|gimp_composite_addition_rgba8_rgba8_rgba8_mmx (GimpCompositeContext * _op)
name|gimp_composite_addition_rgba8_rgba8_rgba8_mmx
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
asm|("movq    %0,%%mm0"                     :
comment|/* empty */
asm|: "m" (*rgba8_alpha_mask)                 : "%mm0");
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
asm|asm ("  movq    (%0), %%mm2; addl $8, %0\n" 											"\tmovq    (%1), %%mm3; addl $8, %1\n" 											"\tmovq    %%mm2, %%mm4\n" 											"\tpaddusb %%mm3, %%mm4\n"  											"\tmovq    %%mm0, %%mm1\n" 											"\tpandn   %%mm4, %%mm1\n" 											"\t" pminub(mm3, mm2, mm4) "\n" 											"\tpand    %%mm0, %%mm2\n" 											"\tpor     %%mm2, %%mm1\n" 											"\tmovq    %%mm1, (%2); addl $8, %2\n" 											: "+r" (op.A), "+r" (op.B), "+r" (op.D) 											:
comment|/* empty */
asm|: "0", "1", "2", "%mm0", "%mm1", "%mm2", "%mm3", "%mm4", "%mm5", "%mm6", "%mm7");
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
asm|("  movd    (%0), %%mm2;\n"                     "\tmovd    (%1), %%mm3;\n" 																				"\tmovq    %%mm2, %%mm4\n" 																				"\tpaddusb %%mm3, %%mm4\n" 																				"\tmovq    %%mm0, %%mm1\n" 																				"\tpandn   %%mm4, %%mm1\n" 																				"\t" pminub(mm3, mm2, mm4) "\n" 																				"\tpand    %%mm0, %%mm2\n" 																				"\tpor     %%mm2, %%mm1\n" 																				"\tmovd    %%mm1, (%2);\n" 																				:
comment|/* empty */
asm|: "r" (op.A), "r" (op.B), "r" (op.D) 																				: "0", "1", "2", "%mm0", "%mm1", "%mm2", "%mm3", "%mm4", "%mm5", "%mm6", "%mm7");
block|}
asm|asm("emms");
block|}
end_function

begin_function
name|void
DECL|function|gimp_composite_burn_rgba8_rgba8_rgba8_mmx (GimpCompositeContext * _op)
name|gimp_composite_burn_rgba8_rgba8_rgba8_mmx
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
asm|("movq   %0,%%mm1" 																:
comment|/* empty */
asm|: "m" (*rgba8_alpha_mask) 																: "%mm1");
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
asm|asm ("  movq      (%0),%%mm0; addl $8,%0\n" 											"\tmovq      (%1),%%mm1; addl $8,%1\n"           											"\tmovq      %3,%%mm2\n" 											"\tpsubb     %%mm0,%%mm2\n"
comment|/* mm2 = 255 - A */
asm|"\tpxor      %%mm4,%%mm4\n" 											"\tpunpcklbw %%mm2,%%mm4\n"
comment|/* mm4 = (255- A) * 256  */
asm|"\tmovq      %%mm1,%%mm3\n" 											"\tpxor      %%mm5,%%mm5\n" 											"\tpunpcklbw %%mm5,%%mm3\n" 											"\tmovq      %4,%%mm5\n" 											"\tpaddusw   %%mm3,%%mm5\n"
comment|/* mm5 = B + 1 */
asm|"\t" pdivwqX(mm4,mm5,mm7) "\n"  											"\tmovq      %3,%%mm2\n" 											"\tpsubb     %%mm0,%%mm2\n"
comment|/* mm2 = 255 - A */
asm|"\tpxor      %%mm4,%%mm4\n" 											"\tpunpckhbw %%mm2,%%mm4\n"
comment|/* mm4 = (255- A) * 256  */
asm|"\tmovq      %%mm1,%%mm3\n" 											"\tpxor      %%mm5,%%mm5\n" 											"\tpunpckhbw %%mm5,%%mm3\n" 											"\tmovq      %4,%%mm5\n" 											"\tpaddusw   %%mm3,%%mm5\n"
comment|/* mm5 = B + 1 */
asm|"\t" pdivwqX(mm4,mm5,mm6) "\n"  											"\tmovq      %5,%%mm4\n" 											"\tmovq      %%mm4,%%mm5\n" 											"\tpsubusw     %%mm6,%%mm4\n" 											"\tpsubusw     %%mm7,%%mm5\n"                    											"\tpackuswb  %%mm4,%%mm5\n"  											"\t" pminub(mm0,mm1,mm3) "\n"
comment|/* mm1 = min(mm0,mm1) clobber mm3 */
asm|"\tmovq      %6,%%mm7\n" 											"\tpand      %%mm7,%%mm1\n"
comment|/* mm1 = mm7& alpha_mask */
asm|"\tpandn     %%mm5,%%mm7\n"
comment|/* mm7 = ~mm7& mm5 */
asm|"\tpor       %%mm1,%%mm7\n"
comment|/* mm7 = mm7 | mm1 */
asm|"\tmovq      %%mm7,(%2); addl $8,%2\n" 											: "+r" (op.A), "+r" (op.B), "+r" (op.D) 											: "m" (*rgba8_b255), "m" (*rgba8_w1), "m" (*rgba8_w255), "m" (*rgba8_alpha_mask) 											: "0", "1", "2", "%mm1", "%mm2", "%mm3", "%mm4");
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
asm|("  movd      (%0),%%mm0\n" 																				"\tmovd      (%1),%%mm1\n"  																				"\tmovq      %3,%%mm2\n" 																				"\tpsubb     %%mm0,%%mm2\n"
comment|/* mm2 = 255 - A */
asm|"\tpxor      %%mm4,%%mm4\n" 																				"\tpunpcklbw %%mm2,%%mm4\n"
comment|/* mm4 = (255- A) * 256  */
asm|"\tmovq      %%mm1,%%mm3\n" 																				"\tpxor      %%mm5,%%mm5\n" 																				"\tpunpcklbw %%mm5,%%mm3\n" 																				"\tmovq      %4,%%mm5\n" 																				"\tpaddusw   %%mm3,%%mm5\n"
comment|/* mm5 = B + 1 */
asm|"\t" pdivwqX(mm4,mm5,mm7) "\n"  																				"\tmovq      %3,%%mm2\n" 																				"\tpsubb   %%mm0,%%mm2\n"
comment|/* mm2 = 255 - A */
asm|"\tpxor      %%mm4,%%mm4\n" 																				"\tpunpckhbw %%mm2,%%mm4\n"
comment|/* mm4 = (255- A) * 256  */
asm|"\tmovq      %%mm1,%%mm3\n" 																				"\tpxor      %%mm5,%%mm5\n" 																				"\tpunpckhbw %%mm5,%%mm3\n" 																				"\tmovq      %4,%%mm5\n" 																				"\tpaddusw   %%mm3,%%mm5\n"
comment|/* mm5 = B + 1 */
asm|"\t" pdivwqX(mm4,mm5,mm6) "\n"  																				"\tmovq      %5,%%mm4\n" 																				"\tmovq      %%mm4,%%mm5\n" 																				"\tpsubusw     %%mm6,%%mm4\n" 																				"\tpsubusw     %%mm7,%%mm5\n"                    																				"\tpackuswb  %%mm4,%%mm5\n"  																				"\t" pminub(mm0,mm1,mm3) "\n"
comment|/* mm1 = min(mm0,mm1) clobber mm3 */
asm|"\tmovq      %6,%%mm7\n" 																				"\tpand      %%mm7,%%mm1\n"
comment|/* mm1 = mm7& alpha_mask */
asm|"\tpandn     %%mm5,%%mm7\n"
comment|/* mm7 = ~mm7& mm5 */
asm|"\tpor       %%mm1,%%mm7\n"
comment|/* mm7 = mm7 | mm1 */
asm|"\tmovd      %%mm7,(%2)\n" 																				:
comment|/* empty */
asm|: "r" (op.A), "r" (op.B), "r" (op.D), "m" (*rgba8_b255), "m" (*rgba8_w1), "m" (*rgba8_w255), "m" (*rgba8_alpha_mask) 																				: "0", "1", "2", "%mm0", "%mm1", "%mm2", "%mm3", "%mm4", "%mm5", "%mm6", "%mm7");
block|}
asm|asm("emms");
block|}
end_function

begin_function
name|void
DECL|function|gimp_composite_darken_rgba8_rgba8_rgba8_mmx (GimpCompositeContext * _op)
name|gimp_composite_darken_rgba8_rgba8_rgba8_mmx
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
asm|asm ("movq    (%0), %%mm2; addl  $8, %0\n"          "\tmovq    (%1), %%mm3; addl  $8, %1\n"          "\t" pminub(mm3, mm2, mm4) "\n"          "\tmovq    %%mm2, (%2); addl  $8, %2\n"          : "+r" (op.A), "+S" (op.B), "+D" (op.D)          :
comment|/* empty */
asm|: "0", "1", "2", "%mm1", "%mm2", "%mm3", "%mm4");
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
asm|("  movd    (%0), %%mm2;\n"                   "\tmovd    (%1), %%mm3;\n"                   "\t" pminub(mm3, mm2, mm4) "\n"                   "\tmovd    %%mm2, (%2);\n"                   :
comment|/* empty */
asm|: "r" (op.A), "r" (op.B), "r" (op.D)                   : "0", "1", "2", "%mm2", "%mm3", "%mm4");
block|}
asm|asm("emms");
block|}
end_function

begin_function
name|void
DECL|function|gimp_composite_difference_rgba8_rgba8_rgba8_mmx (GimpCompositeContext * _op)
name|gimp_composite_difference_rgba8_rgba8_rgba8_mmx
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
asm|asm("movq    %0,%%mm0"     :  : "m" (*rgba8_alpha_mask) : "%mm0");
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
asm|asm ("  movq    (%0), %%mm2; addl $8, %0\n"          "\tmovq    (%1), %%mm3; addl $8, %1\n"          "\tmovq    %%mm2, %%mm4\n"          "\tmovq    %%mm3, %%mm5\n"          "\tpsubusb %%mm3, %%mm4\n"          "\tpsubusb %%mm2, %%mm5\n"          "\tpaddb   %%mm5, %%mm4\n"          "\tmovq    %%mm0, %%mm1\n"          "\tpandn   %%mm4, %%mm1\n"          "\tpminub  %%mm3, %%mm2\n"          "\tpand    %%mm0, %%mm2\n"          "\tpor     %%mm2, %%mm1\n"          "\tmovq    %%mm1, (%2); addl $8, %2\n"          : "+r" (op.A), "+r" (op.B), "+r" (op.D)          :
comment|/* empty */
asm|: "0", "1", "2", "%mm1", "%mm2", "%mm3", "%mm4");
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
asm|("  movd    (%0), %%mm2;\n"                   "\tmovd    (%1), %%mm3;\n"                   "\tmovq    %%mm2, %%mm4\n"                   "\tmovq    %%mm3, %%mm5\n"                   "\tpsubusb %%mm3, %%mm4\n"                   "\tpsubusb %%mm2, %%mm5\n"                   "\tpaddb   %%mm5, %%mm4\n"                   "\tmovq    %%mm0, %%mm1\n"                   "\tpandn   %%mm4, %%mm1\n"                   "\tpminub  %%mm3, %%mm2\n"                   "\tpand    %%mm0, %%mm2\n"                   "\tpor     %%mm2, %%mm1\n"                   "\tmovd    %%mm1, (%2);\n"                   :
comment|/* empty */
asm|: "r" (op.A), "r" (op.B), "r" (op.D)                   : "0", "1", "2", "%mm1", "%mm2", "%mm3", "%mm4");
block|}
asm|asm("emms");
block|}
end_function

begin_function
name|void
DECL|function|gimp_composite_divide_rgba8_rgba8_rgba8_mmx (GimpCompositeContext * _op)
name|gimp_composite_divide_rgba8_rgba8_rgba8_mmx
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
asm|asm("movq    %0, %%mm0\n"       "\tmovq    %1, %%mm7\n"       :       : "m" (*rgba8_alpha_mask), "m" (*rgba8_w1)       : "%mm0", "%mm7");
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
asm|("  movq    (%0), %%mm0; addl $8, %0\n"                   "\tmovq    (%1), %%mm1; addl $8, %1\n"                    "\tpxor      %%mm2,%%mm2\n"                   "\tpunpcklbw %%mm0,%%mm2\n"
comment|/* mm2 = A*256 */
asm|"\tmovq      %%mm1,%%mm3\n"                   "\tpxor      %%mm5,%%mm5\n"                   "\tpunpcklbw %%mm5,%%mm3\n"                   "\tpaddw     %%mm7,%%mm3\n"
comment|/* mm3 = B+1 */
asm|"\t" pdivwuqX(mm2,mm3,mm5) "\n"
comment|/* mm5 = (A*256)/(B+1) */
asm|"\tpxor      %%mm2,%%mm2\n"                   "\tpunpckhbw %%mm0,%%mm2\n"
comment|/* mm2 = A*256 */
asm|"\tmovq      %%mm1,%%mm3\n"                   "\tpxor      %%mm6,%%mm6\n"                   "\tpunpckhbw %%mm6,%%mm3\n"                   "\tpaddw     %%mm7,%%mm3\n"
comment|/* mm3 = B+1 */
asm|"\t" pdivwuqX(mm2,mm3,mm4) "\n"
comment|/* mm4 = (A*256)/(B+1) */
asm|"\tpackuswb  %%mm4,%%mm5\n"
comment|/* expects mm4 and mm5 to be signed values */
asm|"\t" pminub(mm0,mm1,mm3) "\n"                   "\tmovq      %3,%%mm3\n"                   "\tmovq      %%mm3,%%mm2\n"                    "\tpandn     %%mm5,%%mm3\n"                    "\tpand      %%mm2,%%mm1\n"                   "\tpor       %%mm1,%%mm3\n"                    "\tmovq      %%mm3,(%2); addl $8, %2\n"                   : "+r" (op.A), "+r" (op.B), "+r" (op.D)                   : "m" (*rgba8_alpha_mask)                   : "%eax", "%ecx", "%edx", "0", "1", "2", "%mm1", "%mm2", "%mm3", "%mm4", "%mm5");
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
asm|("  movd    (%0), %%mm0; addl $8, %0\n"                   "\tmovd    (%1), %%mm1; addl $8, %1\n"                    "\tpxor      %%mm2,%%mm2\n"                   "\tpunpcklbw %%mm0,%%mm2\n"
comment|/* mm2 = A*256 */
asm|"\tmovq      %%mm1,%%mm3\n"                   "\tpxor      %%mm5,%%mm5\n"                   "\tpunpcklbw %%mm5,%%mm3\n"                   "\tpaddw     %%mm7,%%mm3\n"
comment|/* mm3 = B+1 */
asm|"\t" pdivwuqX(mm2,mm3,mm5) "\n"
comment|/* mm5 = (A*256)/(B+1) */
asm|"\tpxor      %%mm2,%%mm2\n"                   "\tpunpckhbw %%mm0,%%mm2\n"
comment|/* mm2 = A*256 */
asm|"\tmovq      %%mm1,%%mm3\n"                   "\tpxor      %%mm6,%%mm6\n"                   "\tpunpckhbw %%mm6,%%mm3\n"                   "\tpaddw     %%mm7,%%mm3\n"
comment|/* mm3 = B+1 */
asm|"\t" pdivwuqX(mm2,mm3,mm4) "\n"
comment|/* mm4 = (A*256)/(B+1) */
asm|"\tpackuswb  %%mm4,%%mm5\n"
comment|/* expects mm4 and mm5 to be signed values */
asm|"\t" pminub(mm0,mm1,mm3) "\n"                   "\tmovq      %3,%%mm3\n"                   "\tmovq      %%mm3,%%mm2\n"                    "\tpandn     %%mm5,%%mm3\n"                    "\tpand      %%mm2,%%mm1\n"                   "\tpor       %%mm1,%%mm3\n"                    "\tmovd      %%mm3,(%2); addl $8, %2\n"                   :
comment|/* empty */
asm|: "r" (op.A), "r" (op.B), "r" (op.D), "m" (*rgba8_alpha_mask)                   : "%eax", "%ecx", "%edx", "0", "1", "2", "%mm1", "%mm2", "%mm3", "%mm4", "%mm5");
block|}
asm|asm("emms");
block|}
end_function

begin_function
name|void
DECL|function|gimp_composite_dodge_rgba8_rgba8_rgba8_mmx (GimpCompositeContext * _op)
name|gimp_composite_dodge_rgba8_rgba8_rgba8_mmx
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
asm|("  movq     (%0), %%mm0; addl $8, %0\n"                   "\tmovq     (%1), %%mm1; addl $8, %1\n"                   "\tmovq      %%mm1, %%mm3\n"                   "\tpxor      %%mm2, %%mm2\n"                   "\tpunpcklbw %%mm2, %%mm3\n"                   "\tpunpcklbw %%mm0, %%mm2\n"                    "\tmovq      rgba8_w256, %%mm4\n"                   "\tpsubw     %%mm3, %%mm4\n"                    "\t" pdivwuqX(mm2,mm4,mm5) "\n"                    "\tmovq      %%mm1, %%mm3\n"                   "\tpxor      %%mm2, %%mm2\n"                   "\tpunpckhbw %%mm2, %%mm3\n"                   "\tpunpckhbw %%mm0, %%mm2\n"                    "\tmovq      rgba8_w256, %%mm4\n"                   "\tpsubw     %%mm3, %%mm4\n"                    "\t" pdivwuqX(mm2,mm4,mm6) "\n"                    "\tpackuswb  %%mm6, %%mm5\n"                    "\tmovq      rgba8_alpha_mask, %%mm6\n"                   "\tmovq      %%mm1,%%mm7\n"                   "\t" pminub(mm0,mm7,mm2) "\n"                   "\tpand      %%mm6, %%mm7\n"                   "\tpandn     %%mm5, %%mm6\n"                    "\tpor       %%mm6, %%mm7\n"                    "\tmovq    %%mm7, (%2); addl $8, %2\n"                   : "+r" (op.A), "+r" (op.B), "+r" (op.D)                   :
comment|/* empty */
asm|: "0", "1", "2", "%mm0", "%mm1", "%mm2", "%mm3", "%mm4", "%mm5", "%mm6", "%mm7");
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
asm|("  movd     (%0), %%mm0;\n"                   "\tmovq     (%1), %%mm1;\n"                   "\tmovq      %%mm1, %%mm3\n"                   "\tpxor      %%mm2, %%mm2\n"                   "\tpunpcklbw %%mm2, %%mm3\n"                   "\tpunpcklbw %%mm0, %%mm2\n"                    "\tmovq      rgba8_w256, %%mm4\n"                   "\tpsubw     %%mm3, %%mm4\n"                    "\t" pdivwuqX(mm2,mm4,mm5) "\n"                    "\tmovq      %%mm1, %%mm3\n"                   "\tpxor      %%mm2, %%mm2\n"                   "\tpunpckhbw %%mm2, %%mm3\n"                   "\tpunpckhbw %%mm0, %%mm2\n"                    "\tmovq      rgba8_w256, %%mm4\n"                   "\tpsubw     %%mm3, %%mm4\n"                    "\t" pdivwuqX(mm2,mm4,mm6) "\n"                    "\tpackuswb  %%mm6, %%mm5\n"                    "\tmovq      rgba8_alpha_mask, %%mm6\n"                   "\tmovq      %%mm1,%%mm7\n"                   "\t" pminub(mm0,mm7,mm2) "\n"                   "\tpand      %%mm6, %%mm7\n"                   "\tpandn     %%mm5, %%mm6\n"                    "\tpor       %%mm6, %%mm7\n"                    "\tmovd    %%mm7, (%2);\n"                   :
comment|/* empty */
asm|: "r" (op.A), "r" (op.B), "r" (op.D)                   : "0", "1", "2", "%mm1", "%mm2", "%mm3", "%mm4", "%mm5");
block|}
asm|asm("emms");
block|}
end_function

begin_function
name|void
DECL|function|gimp_composite_grain_extract_rgba8_rgba8_rgba8_mmx (GimpCompositeContext * _op)
name|gimp_composite_grain_extract_rgba8_rgba8_rgba8_mmx
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
asm|("movq    %0,%%mm0"     :  : "m" (*rgba8_alpha_mask) : "%mm0");
asm|asm
specifier|volatile
asm|("pxor    %%mm6,%%mm6"  :  :                        : "%mm6");
asm|asm
specifier|volatile
asm|("movq    %0,%%mm7"     :  : "m" (*rgba8_w128)       : "%mm7");
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
asm|asm ("  movq    (%0), %%mm2; addl $8, %0\n"          "\tmovq    (%1), %%mm3; addl $8, %1\n"           mmx_low_bytes_to_words(mm2,mm4,mm6)          mmx_low_bytes_to_words(mm3,mm5,mm6)           "\tpsubw     %%mm5, %%mm4\n"          "\tpaddw     %%mm7, %%mm4\n"          "\tmovq      %%mm4, %%mm1\n"           mmx_high_bytes_to_words(mm2,mm4,mm6)          mmx_high_bytes_to_words(mm3,mm5,mm6)           "\tpsubw     %%mm5, %%mm4\n"          "\tpaddw     %%mm7, %%mm4\n"           "\tpackuswb  %%mm4, %%mm1\n"          "\tmovq      %%mm1, %%mm4\n"           "\tmovq      %%mm0, %%mm1; pandn     %%mm4, %%mm1\n"           "\t" pminub(mm3,mm2,mm4) "\n"          "\tpand      %%mm0, %%mm2\n"           "\tpor       %%mm2, %%mm1\n"          "\tmovq      %%mm1, (%2); addl $8, %2\n"          : "+r" (op.A), "+r" (op.B), "+r" (op.D)          :
comment|/* empty */
asm|: "0", "1", "2", "%mm1", "%mm2", "%mm3", "%mm4");
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
asm|("  movd    (%0), %%mm2;\n"                   "\tmovd    (%1), %%mm3;\n"                    mmx_low_bytes_to_words(mm2,mm4,mm6)                   mmx_low_bytes_to_words(mm3,mm5,mm6)                    "\tpsubw     %%mm5, %%mm4\n"                   "\tpaddw     %%mm7, %%mm4\n"                   "\tmovq      %%mm4, %%mm1\n"                    "\tpackuswb  %%mm6, %%mm1\n"                    "\tmovq      %%mm1, %%mm4\n"                    "\tmovq      %%mm0, %%mm1; pandn     %%mm4, %%mm1\n"                    "\t" pminub(mm3,mm2,mm4) "\n"                   "\tpand      %%mm0, %%mm2\n"                    "\tpor       %%mm2, %%mm1\n"                   "\tmovd      %%mm1, (%2);\n"                   :
comment|/* empty */
asm|: "r" (op.A), "r" (op.B), "r" (op.D)                   : "0", "1", "2", "%mm1", "%mm2", "%mm3", "%mm4");
block|}
asm|asm("emms");
block|}
end_function

begin_function
name|void
DECL|function|gimp_composite_grain_merge_rgba8_rgba8_rgba8_mmx (GimpCompositeContext * _op)
name|gimp_composite_grain_merge_rgba8_rgba8_rgba8_mmx
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
asm|("movq    %0, %%mm0\n"                 "pxor    %%mm6, %%mm6\n"                 "movq    %1, %%mm7\n"                 :
comment|/* empty */
asm|: "m" (*rgba8_alpha_mask), "m" (*rgba8_w128)                 : "%mm0", "%mm6", "%mm7");
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
asm|asm ("  movq    (%0), %%mm2; addl $8, %0\n"          "\tmovq    (%1), %%mm3; addl $8, %1\n"           mmx_low_bytes_to_words(mm2,mm4,mm6)          mmx_low_bytes_to_words(mm3,mm5,mm6)          "\tpaddw     %%mm5, %%mm4\n"          "\tpsubw     %%mm7, %%mm4\n"           mmx_high_bytes_to_words(mm2,mm1,mm6)          mmx_high_bytes_to_words(mm3,mm5,mm6)          "\tpaddw     %%mm5, %%mm1\n"          "\tpsubw     %%mm7, %%mm1\n"           "\tpackuswb  %%mm1, %%mm4\n"                    pminub(mm3,mm2,mm5)          "\tpand      %%mm0, %%mm2\n"           "\tmovq      %%mm0, %%mm1;\n"          "\tpandn     %%mm4, %%mm1\n"          "\tpor       %%mm2, %%mm1\n"          "\tmovq      %%mm1, (%2); addl $8, %2\n"          : "+r" (op.A), "+r" (op.B), "+r" (op.D)          :
comment|/* empty */
asm|: "0", "1", "2", "%mm1", "%mm2", "%mm3", "%mm4");
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
asm|("  movd    (%0), %%mm2;\n"                   "\tmovd    (%1), %%mm3;\n"                    mmx_low_bytes_to_words(mm2,mm4,mm6)                   mmx_low_bytes_to_words(mm3,mm5,mm6)                    "\tpaddw     %%mm5, %%mm4\n"                   "\tpsubw     %%mm7, %%mm4\n"                   "\tmovq      %%mm4, %%mm1\n"                   "\tpackuswb  %%mm6, %%mm1\n"                    "\tmovq      %%mm1, %%mm4\n"                    "\tmovq      %%mm0, %%mm1; pandn     %%mm4, %%mm1\n"                    "\t" pminub(mm3,mm2,mm4) "\n"                   "\tpand      %%mm0, %%mm2\n"                    "\tpor       %%mm2, %%mm1\n"                   "\tmovd      %%mm1, (%2);\n"                   :
comment|/* empty */
asm|: "r" (op.A), "r" (op.B), "r" (op.D)                   : "0", "1", "2", "%mm1", "%mm2", "%mm3", "%mm4");
block|}
asm|asm("emms");
block|}
end_function

begin_function
name|void
DECL|function|gimp_composite_lighten_rgba8_rgba8_rgba8_mmx (GimpCompositeContext * _op)
name|gimp_composite_lighten_rgba8_rgba8_rgba8_mmx
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
asm|("movq    %0,%%mm0"     :  : "m" (*rgba8_alpha_mask) : "%mm0");
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
asm|asm ("  movq     (%0), %%mm2; addl $8, %0\n"          "\tmovq     (%1), %%mm3; addl $8, %1\n"          "\tmovq    %%mm2, %%mm4\n"          "\t" pmaxub(mm3,mm4,mm5) "\n"          "\tmovq    %%mm0, %%mm1\n"          "\tpandn   %%mm4, %%mm1\n"          "\t" pminub(mm2,mm3,mm4) "\n"          "\tpand    %%mm0, %%mm3\n"          "\tpor     %%mm3, %%mm1\n"          "\tmovq    %%mm1, (%2); addl $8, %2\n"          : "+r" (op.A), "+r" (op.B), "+r" (op.D)          :
comment|/* empty */
asm|: "0", "1", "2", "%mm1", "%mm2", "%mm3", "%mm4", "%mm5");
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
asm|("  movd    (%0), %%mm2\n"                   "\tmovd    (%1), %%mm3\n"                   "\tmovq    %%mm2, %%mm4\n"                   "\t" pmaxub(mm3,mm4,mm5) "\n"                    "\tmovq    %%mm0, %%mm1\n"                   "\tpandn   %%mm4, %%mm1\n"                    "\t" pminub(mm2,mm3,mm4) "\n"                    "\tpand    %%mm0, %%mm3\n"                   "\tpor     %%mm3, %%mm1\n"                   "\tmovd    %%mm1, (%2)\n"                   :
comment|/* empty */
asm|: "r" (op.A), "r" (op.B), "r" (op.D)                   : "0", "1", "2", "%mm1", "%mm2", "%mm3", "%mm4", "%mm5");
block|}
asm|asm("emms");
block|}
end_function

begin_function
name|void
DECL|function|gimp_composite_multiply_rgba8_rgba8_rgba8_mmx (GimpCompositeContext * _op)
name|gimp_composite_multiply_rgba8_rgba8_rgba8_mmx
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
asm|("movq    %0,%%mm0"     :  : "m" (*rgba8_alpha_mask) : "%mm0");
asm|asm
specifier|volatile
asm|("movq    %0,%%mm7"     :  : "m" (*rgba8_w128) : "%mm7");
asm|asm
specifier|volatile
asm|("pxor    %%mm6,%%mm6"  :  :  : "%mm6");
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
asm|asm ("  movq     (%0), %%mm2; addl $8, %0\n"          "\tmovq     (%1), %%mm3; addl $8, %1\n"           mmx_low_bytes_to_words(mm2,mm1,mm6)          mmx_low_bytes_to_words(mm3,mm5,mm6)          mmx_int_mult(mm5,mm1,mm7)                     mmx_high_bytes_to_words(mm2,mm4,mm6)          mmx_high_bytes_to_words(mm3,mm5,mm6)          mmx_int_mult(mm5,mm4,mm7)                    "\tpackuswb  %%mm4, %%mm1\n"                    "\tmovq      %%mm0, %%mm4\n"          "\tpandn     %%mm1, %%mm4\n"          "\tmovq      %%mm4, %%mm1\n"          "\t" pminub(mm3,mm2,mm4) "\n"          "\tpand      %%mm0, %%mm2\n"          "\tpor       %%mm2, %%mm1\n"                    "\tmovq    %%mm1, (%2); addl $8, %2\n"          : "+r" (op.A), "+r" (op.B), "+r" (op.D)          :
comment|/* empty */
asm|: "0", "1", "2", "%mm1", "%mm2", "%mm3", "%mm4", "%mm5");
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
asm|("  movd     (%0), %%mm2\n"                   "\tmovd     (%1), %%mm3\n"                    mmx_low_bytes_to_words(mm2,mm1,mm6)                   mmx_low_bytes_to_words(mm3,mm5,mm6)                   pmulwX(mm5,mm1,mm7)                    "\tpackuswb  %%mm6, %%mm1\n"                    "\tmovq      %%mm0, %%mm4\n"                   "\tpandn     %%mm1, %%mm4\n"                   "\tmovq      %%mm4, %%mm1\n"                   "\t" pminub(mm3,mm2,mm4) "\n"                   "\tpand      %%mm0, %%mm2\n"                   "\tpor       %%mm2, %%mm1\n"                                      "\tmovd    %%mm1, (%2)\n"                   :
comment|/* empty */
asm|: "r" (op.A), "r" (op.B), "r" (op.D)                   : "0", "1", "2", "%mm1", "%mm2", "%mm3", "%mm4", "%mm5");
block|}
asm|asm("emms");
block|}
end_function

begin_function
specifier|static
name|void
DECL|function|mmx_op_overlay (void)
name|mmx_op_overlay
parameter_list|(
name|void
parameter_list|)
block|{
asm|asm
specifier|volatile
asm|(
comment|/* low bytes */
asm|mmx_low_bytes_to_words(mm3,mm5,mm0)                 "\tpcmpeqb   %%mm4, %%mm4\n"                 "\tpsubb     %%mm2, %%mm4\n"
comment|/* mm4 = 255 - A */
asm|"\tpunpcklbw %%mm0, %%mm4\n"
comment|/* mm4 = (low bytes as word) mm4 */
asm|"\tmovq      (%0), %%mm6\n"
comment|/* mm6 = words of value 2 */
asm|"\tpmullw    %%mm5, %%mm6\n"
comment|/* mm6 = 2 * low bytes of B */
asm|mmx_int_mult(mm6,mm4,mm7)
comment|/* mm4 = INT_MULT(mm6, mm4) */
comment|/* high bytes */
asm|mmx_high_bytes_to_words(mm3,mm5,mm0)                 "\tpcmpeqb   %%mm1, %%mm1\n"                 "\tpsubb     %%mm2, %%mm1\n"
comment|/* mm1 = 255 - A */
asm|"\tpunpckhbw %%mm0, %%mm1\n"
comment|/* mm1 = (high bytes as word) mm1 */
asm|"\tmovq      (%0), %%mm6\n"
comment|/* mm6 = words of value 2 */
asm|"\tpmullw    %%mm5, %%mm6\n"
comment|/* mm6 = 2 * high bytes of B */
asm|mmx_int_mult(mm6,mm1,mm7)
comment|/* mm1 = INT_MULT(mm6, mm1) */
asm|"\tpackuswb  %%mm1,%%mm4\n"
comment|/* mm4 = intermediate value */
asm|mmx_low_bytes_to_words(mm4,mm5,mm0)                 mmx_low_bytes_to_words(mm2,mm6,mm0)                 "\tpaddw     %%mm6,%%mm5\n"                 mmx_int_mult(mm6,mm5,mm7)
comment|/* mm5 = INT_MULT(mm6, mm5) low bytes */
asm|mmx_high_bytes_to_words(mm4,mm1,mm0)                 mmx_high_bytes_to_words(mm2,mm6,mm0)                 "\tpaddw     %%mm6,%%mm1\n"                 mmx_int_mult(mm6,mm1,mm7)
comment|/* mm1 = INT_MULT(mm6, mm1) high bytes */
asm|"\tpackuswb  %%mm1,%%mm5\n"                  "\tmovq      %1, %%mm0\n"                 "\tmovq      %%mm0, %%mm1\n"                 "\tpandn     %%mm5, %%mm1\n"                  "\t" pminub(mm2,mm3,mm4) "\n"                 "\tpand      %%mm0, %%mm3\n"                  "\tpor       %%mm3, %%mm1\n"                  :
comment|/* empty */
asm|: "m" (*rgba8_w2), "m" (*rgba8_alpha_mask)                 );
block|}
end_function

begin_function
name|void
DECL|function|xxxgimp_composite_overlay_rgba8_rgba8_rgba8_mmx (GimpCompositeContext * _op)
name|xxxgimp_composite_overlay_rgba8_rgba8_rgba8_mmx
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
asm|("pxor    %%mm0,%%mm0\n"                 "movq    (%0),%%mm7"                 :
comment|/* empty */
asm|: "m" (*rgba8_w128) : "%mm0");
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
asm|("  movq    (%0), %%mm2; addl  $8, %0\n" 																		"\tmovq    (%1), %%mm3; addl  $8, %1\n"
comment|/* low bytes */
asm|mmx_low_bytes_to_words(mm3,mm5,mm0) 																		"\tpcmpeqb   %%mm4, %%mm4\n" 																		"\tpsubb     %%mm2, %%mm4\n"
comment|/* mm4 = 255 - A */
asm|"\tpunpcklbw %%mm0, %%mm4\n"
comment|/* mm4 = (low bytes as word) mm4 */
asm|"\tmovq      (%3), %%mm6\n"
comment|/* mm6 = words of value 2 */
asm|"\tpmullw    %%mm5, %%mm6\n"
comment|/* mm6 = 2 * low bytes of B */
asm|mmx_int_mult(mm6,mm4,mm7)
comment|/* mm4 = INT_MULT(mm6, mm4) */
comment|/* high bytes */
asm|mmx_high_bytes_to_words(mm3,mm5,mm0) 																		"\tpcmpeqb   %%mm1, %%mm1\n" 																		"\tpsubb     %%mm2, %%mm1\n"
comment|/* mm1 = 255 - A */
asm|"\tpunpckhbw %%mm0, %%mm1\n"
comment|/* mm1 = (high bytes as word) mm1 */
asm|"\tmovq      (%3), %%mm6\n"
comment|/* mm6 = words of value 2 */
asm|"\tpmullw    %%mm5, %%mm6\n"
comment|/* mm6 = 2 * high bytes of B */
asm|mmx_int_mult(mm6,mm1,mm7)
comment|/* mm1 = INT_MULT(mm6, mm1) */
asm|"\tpackuswb  %%mm1,%%mm4\n"
comment|/* mm4 = intermediate value */
asm|mmx_low_bytes_to_words(mm4,mm5,mm0) 																		mmx_low_bytes_to_words(mm2,mm6,mm0) 																		"\tpaddw     %%mm6,%%mm5\n" 																		mmx_int_mult(mm6,mm5,mm7)
comment|/* mm5 = INT_MULT(mm6, mm5) low bytes */
asm|mmx_high_bytes_to_words(mm4,mm1,mm0) 																		mmx_high_bytes_to_words(mm2,mm6,mm0) 																		"\tpaddw     %%mm6,%%mm1\n" 																		mmx_int_mult(mm6,mm1,mm7)
comment|/* mm1 = INT_MULT(mm6, mm1) high bytes */
asm|"\tpackuswb  %%mm1,%%mm5\n"  																		"\tmovq      (%4), %%mm0\n" 																		"\tmovq      %%mm0, %%mm1\n" 																		"\tpandn     %%mm5, %%mm1\n"  																		"\t" pminub(mm2,mm3,mm4) "\n" 																		"\tpand      %%mm0, %%mm3\n"  																		"\tpor       %%mm3, %%mm1\n"  																		"\tmovq    %%mm1, (%2); addl  $8, %2\n" 																		: "+r" (op.A), "+r" (op.B), "+r" (op.D) 																		: "m" (*rgba8_w2), "m" (*rgba8_alpha_mask) 																		: "0", "1", "2", "%mm1", "%mm2", "%mm3", "%mm4");
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
asm|("  movd    (%0), %%mm2;\n"                   "\tmovd    (%1), %%mm3;\n"
comment|/* low bytes */
asm|mmx_low_bytes_to_words(mm3,mm5,mm0) 																		"\tpcmpeqb   %%mm4, %%mm4\n" 																		"\tpsubb     %%mm2, %%mm4\n"
comment|/* mm4 = 255 - A */
asm|"\tpunpcklbw %%mm0, %%mm4\n"
comment|/* mm4 = (low bytes as word) mm4 */
asm|"\tmovq      (%3), %%mm6\n"
comment|/* mm6 = words of value 2 */
asm|"\tpmullw    %%mm5, %%mm6\n"
comment|/* mm6 = 2 * low bytes of B */
asm|mmx_int_mult(mm6,mm4,mm7)
comment|/* mm4 = INT_MULT(mm6, mm4) */
comment|/* high bytes */
asm|mmx_high_bytes_to_words(mm3,mm5,mm0) 																		"\tpcmpeqb   %%mm1, %%mm1\n" 																		"\tpsubb     %%mm2, %%mm1\n"
comment|/* mm1 = 255 - A */
asm|"\tpunpckhbw %%mm0, %%mm1\n"
comment|/* mm1 = (high bytes as word) mm1 */
asm|"\tmovq      (%3), %%mm6\n"
comment|/* mm6 = words of value 2 */
asm|"\tpmullw    %%mm5, %%mm6\n"
comment|/* mm6 = 2 * high bytes of B */
asm|mmx_int_mult(mm6,mm1,mm7)
comment|/* mm1 = INT_MULT(mm6, mm1) */
asm|"\tpackuswb  %%mm1,%%mm4\n"
comment|/* mm4 = intermediate value */
asm|mmx_low_bytes_to_words(mm4,mm5,mm0) 																		mmx_low_bytes_to_words(mm2,mm6,mm0) 																		"\tpaddw     %%mm6,%%mm5\n" 																		mmx_int_mult(mm6,mm5,mm7)
comment|/* mm5 = INT_MULT(mm6, mm5) low bytes */
asm|mmx_high_bytes_to_words(mm4,mm1,mm0) 																		mmx_high_bytes_to_words(mm2,mm6,mm0) 																		"\tpaddw     %%mm6,%%mm1\n" 																		mmx_int_mult(mm6,mm1,mm7)
comment|/* mm1 = INT_MULT(mm6, mm1) high bytes */
asm|"\tpackuswb  %%mm1,%%mm5\n"  																		"\tmovq      (%4), %%mm0\n" 																		"\tmovq      %%mm0, %%mm1\n" 																		"\tpandn     %%mm5, %%mm1\n"  																		"\t" pminub(mm2,mm3,mm4) "\n" 																		"\tpand      %%mm0, %%mm3\n"  																		"\tpor       %%mm3, %%mm1\n"                    "\tmovd    %%mm1, (%2);\n"                   :
comment|/* empty */
asm|: "r" (op.A), "r" (op.B), "r" (op.D), "m" (*rgba8_w2), "m" (*rgba8_alpha_mask)                   : "0", "1", "2", "%mm1", "%mm2", "%mm3", "%mm4");
block|}
asm|asm("emms");
block|}
end_function

begin_function
name|void
DECL|function|gimp_composite_scale_rgba8_rgba8_rgba8_mmx (GimpCompositeContext * _op)
name|gimp_composite_scale_rgba8_rgba8_rgba8_mmx
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
asm|("pxor    %%mm0,%%mm0\n"                 "\tmovl  %0,%%eax\n"                 "\tmovl  %%eax,%%ebx\n"                 "\tshl   $16,%%ebx\n"                 "\torl   %%ebx,%%eax\n"                 "\tmovd  %%eax,%%mm5\n"                 "\tmovd  %%eax,%%mm3\n"                 "\tpsllq $32,%%mm5\n"                 "\tpor   %%mm5,%%mm3\n"                 "\tmovq  %1,%%mm7\n"                 :
comment|/* empty */
asm|: "m" (op.scale.scale), "m" (*rgba8_w128)                 : "%eax", "%mm0", "%mm5", "%mm6", "%mm7");
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
asm|asm ("movq      (%0),%%mm2; addl $8,%0\n"          "\tmovq      %%mm2,%%mm1\n"           "\tpunpcklbw %%mm0,%%mm1\n"          "\tmovq      %%mm3,%%mm5\n"           "\t" pmulwX(mm5,mm1,mm7) "\n"           "\tmovq      %%mm2,%%mm4\n"          "\tpunpckhbw %%mm0,%%mm4\n"          "\tmovq      %%mm3,%%mm5\n"           "\t" pmulwX(mm5,mm4,mm7) "\n"           "\tpackuswb  %%mm4,%%mm1\n"           "\tmovq    %%mm1,(%1);  addl $8,%1\n"          : "+r" (op.A), "+r" (op.D)          :
comment|/* empty */
asm|: "0", "1", "%mm1", "%mm2", "%mm3", "%mm4", "%mm5", "%mm6", "%mm7");
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
asm|("movd      (%0), %%mm2\n"                   "\tmovq      %%mm2,%%mm1\n"                   "\tpunpcklbw %%mm0,%%mm1\n"                   "\tmovq      %%mm3,%%mm5\n"                    "\t" pmulwX(mm5,mm1,mm7) "\n"                    "\tpackuswb  %%mm0,%%mm1\n"                   "\tmovd    %%mm1,(%1)\n"                   :
comment|/* empty */
asm|: "r" (op.A), "r" (op.D)                   : "0", "1", "%mm1", "%mm2", "%mm3", "%mm4", "%mm5", "%mm6", "%mm7");
block|}
asm|asm("emms");
block|}
end_function

begin_function
name|void
DECL|function|gimp_composite_screen_rgba8_rgba8_rgba8_mmx (GimpCompositeContext * _op)
name|gimp_composite_screen_rgba8_rgba8_rgba8_mmx
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
asm|("movq    %0,%%mm0"     :  : "m" (*rgba8_alpha_mask) : "%mm0");
asm|asm
specifier|volatile
asm|("movq    %0,%%mm7"     :  : "m" (*rgba8_w128)  : "%mm7");
asm|asm
specifier|volatile
asm|("pxor    %mm6, %mm6");
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
asm|asm ("  movq     (%0), %%mm2; addl $8, %0\n"          "\tmovq     (%1), %%mm3; addl $8, %1\n"           "\tpcmpeqb   %%mm4, %%mm4\n"          "\tpsubb     %%mm2, %%mm4\n"          "\tpcmpeqb   %%mm5, %%mm5\n"          "\tpsubb     %%mm3, %%mm5\n"           "\tpunpcklbw %%mm6, %%mm4\n"          "\tpunpcklbw %%mm6, %%mm5\n"          "\tpmullw    %%mm4, %%mm5\n"          "\tpaddw     %%mm7, %%mm5\n"          "\tmovq      %%mm5, %%mm1\n"          "\tpsrlw     $ 8, %%mm1\n"          "\tpaddw     %%mm5, %%mm1\n"          "\tpsrlw     $ 8, %%mm1\n"           "\tpcmpeqb   %%mm4, %%mm4\n"          "\tpsubb     %%mm2, %%mm4\n"          "\tpcmpeqb   %%mm5, %%mm5\n"          "\tpsubb     %%mm3, %%mm5\n"           "\tpunpckhbw %%mm6, %%mm4\n"          "\tpunpckhbw %%mm6, %%mm5\n"          "\tpmullw    %%mm4, %%mm5\n"          "\tpaddw     %%mm7, %%mm5\n"          "\tmovq      %%mm5, %%mm4\n"          "\tpsrlw     $ 8, %%mm4\n"          "\tpaddw     %%mm5, %%mm4\n"          "\tpsrlw     $ 8, %%mm4\n"           "\tpackuswb  %%mm4, %%mm1\n"           "\tpcmpeqb   %%mm4, %%mm4\n"          "\tpsubb     %%mm1, %%mm4\n"           "\tmovq      %%mm0, %%mm1\n"          "\tpandn     %%mm4, %%mm1\n"           "\t" pminub(mm2,mm3,mm4) "\n"          "\tpand      %%mm0, %%mm3\n"           "\tpor       %%mm3, %%mm1\n"           "\tmovq    %%mm1, (%2); addl $8, %2\n"          : "+r" (op.A), "+r" (op.B), "+r" (op.D)          :
comment|/* empty */
asm|: "0", "1", "2", "%mm1", "%mm2", "%mm3", "%mm4", "%mm5");
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
asm|("  movd     (%0), %%mm2;\n"                   "\tmovd     (%1), %%mm3;\n"                    "\tpcmpeqb   %%mm4, %%mm4\n"                   "\tpsubb     %%mm2, %%mm4\n"                   "\tpcmpeqb   %%mm5, %%mm5\n"                   "\tpsubb     %%mm3, %%mm5\n"                    "\tpunpcklbw %%mm6, %%mm4\n"                   "\tpunpcklbw %%mm6, %%mm5\n"                   "\tpmullw    %%mm4, %%mm5\n"                   "\tpaddw     %%mm7, %%mm5\n"                   "\tmovq      %%mm5, %%mm1\n"                   "\tpsrlw     $ 8, %%mm1\n"                   "\tpaddw     %%mm5, %%mm1\n"                   "\tpsrlw     $ 8, %%mm1\n"                    "\tpcmpeqb   %%mm4, %%mm4\n"                   "\tpsubb     %%mm2, %%mm4\n"                   "\tpcmpeqb   %%mm5, %%mm5\n"                   "\tpsubb     %%mm3, %%mm5\n"                    "\tpunpckhbw %%mm6, %%mm4\n"                   "\tpunpckhbw %%mm6, %%mm5\n"                   "\tpmullw    %%mm4, %%mm5\n"                   "\tpaddw     %%mm7, %%mm5\n"                   "\tmovq      %%mm5, %%mm4\n"                   "\tpsrlw     $ 8, %%mm4\n"                   "\tpaddw     %%mm5, %%mm4\n"                   "\tpsrlw     $ 8, %%mm4\n"                    "\tpackuswb  %%mm4, %%mm1\n"                    "\tpcmpeqb   %%mm4, %%mm4\n"                   "\tpsubb     %%mm1, %%mm4\n"                    "\tmovq      %%mm0, %%mm1\n"                   "\tpandn     %%mm4, %%mm1\n"                    "\t" pminub(mm2,mm3,mm4) "\n"                   "\tpand      %%mm0, %%mm3\n"                    "\tpor       %%mm3, %%mm1\n"                    "\tmovd    %%mm1, (%2);\n"                   :
comment|/* empty */
asm|: "r" (op.A), "r" (op.B), "r" (op.D)                   : "0", "1", "2", "%mm1", "%mm2", "%mm3", "%mm4", "%mm5");
block|}
asm|asm("emms");
block|}
end_function

begin_function
name|void
DECL|function|gimp_composite_subtract_rgba8_rgba8_rgba8_mmx (GimpCompositeContext * _op)
name|gimp_composite_subtract_rgba8_rgba8_rgba8_mmx
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
asm|("movq    %0,%%mm0"     :  : "m" (*rgba8_alpha_mask) : "%mm0");
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
asm|asm ("  movq     (%0), %%mm2; addl $8, %0\n"          "\tmovq     (%1), %%mm3; addl $8, %1\n"           "\tmovq    %%mm2, %%mm4\n"          "\tpsubusb %%mm3, %%mm4\n"                             "\tmovq    %%mm0, %%mm1\n"          "\tpandn   %%mm4, %%mm1\n"                             "\t" pminub(mm3,mm2,mm4) "\n"           "\tpand    %%mm0, %%mm2\n"          "\tpor     %%mm2, %%mm1\n"          "\tmovq    %%mm1, (%2); addl $8, %2\n"          : "+r" (op.A), "+r" (op.B), "+r" (op.D)          :
comment|/* empty */
asm|: "0", "1", "2", "%mm1", "%mm2", "%mm3", "%mm4", "%mm5");
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
asm|("  movd     (%0), %%mm2;\n"                   "\tmovd     (%1), %%mm3;\n"                    "\tmovq    %%mm2, %%mm4\n"                   "\tpsubusb %%mm3, %%mm4\n"                                      "\tmovq    %%mm0, %%mm1\n"                   "\tpandn   %%mm4, %%mm1\n"                                      "\t" pminub(mm3,mm2,mm4) "\n"                    "\tpand    %%mm0, %%mm2\n"                   "\tpor     %%mm2, %%mm1\n"                   "\tmovd    %%mm1, (%2); addl $8, %2\n"                   :
comment|/* empty */
asm|: "r" (op.A), "r" (op.B), "r" (op.D)                   : "0", "1", "2", "%mm1", "%mm2", "%mm3", "%mm4", "%mm5");
block|}
asm|asm("emms");
block|}
end_function

begin_function
name|void
DECL|function|gimp_composite_swap_rgba8_rgba8_rgba8_mmx (GimpCompositeContext * _op)
name|gimp_composite_swap_rgba8_rgba8_rgba8_mmx
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
asm|asm ("  movq    (%0), %%mm2\n"          "\tmovq    (%1), %%mm3\n"          "\tmovq    %%mm3, (%0)\n"          "\tmovq    %%mm2, (%1)\n"          "\taddl    $8, %0\n"          "\taddl    $8, %1\n"          : "+r" (op.A), "+r" (op.B)          :
comment|/* empty */
asm|: "0", "1", "%mm1", "%mm2", "%mm3", "%mm4");
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
asm|("  movd    (%0), %%mm2\n"                   "\tmovd    (%1), %%mm3\n"                   "\tmovd    %%mm3, (%0)\n"                   "\tmovd    %%mm2, (%1)\n"                                     :
comment|/* empty */
asm|: "r" (op.A), "r" (op.B)                   : "0", "1", "%mm1", "%mm2", "%mm3", "%mm4");
block|}
asm|asm("emms");
block|}
end_function

begin_decl_stmt
DECL|variable|v8_alpha_mask
specifier|const
specifier|static
name|unsigned
name|long
name|v8_alpha_mask
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
DECL|variable|v8_mul_shift
specifier|const
specifier|static
name|unsigned
name|long
name|v8_mul_shift
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

begin_if
if|#
directive|if
literal|0
end_if

begin_comment
unit|void gimp_composite_addition_va8_va8_va8_mmx (GimpCompositeContext *_op) {   GimpCompositeContext op = *_op;    asm("pushl %edi");   asm("pushl %ebx");   asm("movl 12(%esp), %edi");   asm("movq v8_alpha_mask, %mm0");    asm("subl $ 4, %ecx");   asm("jl .add_pixels_1a_1a_last3");   asm("movl $ 8, %ebx");   asm(".add_pixels_1a_1a_loop:");    asm("movq (%eax), %mm2");   asm("movq (%edx), %mm3");    asm("movq %mm2, %mm4");   asm("paddusb %mm3, %mm4");   asm("movq %mm0, %mm1");   asm("pandn %mm4, %mm1");   asm("movq %mm2, %mm4");   asm("psubusb %mm3, %mm4");   asm("psubb %mm4, %mm2");   asm("pand %mm0, %mm2");   asm("por %mm2, %mm1");   asm("movq %mm1, (%edi)");   asm("addl %ebx, %eax");   asm("addl %ebx, %edx");   asm("addl %ebx, %edi");   asm("subl $ 4, %ecx");   asm("jge .add_pixels_1a_1a_loop");    asm(".add_pixels_1a_1a_last3:");   asm("test $ 2, %ecx");   asm("jz .add_pixels_1a_1a_last1");   asm("movd (%eax), %mm2");   asm("movd (%edx), %mm3");    asm("movq %mm2, %mm4");   asm("paddusb %mm3, %mm4");   asm("movq %mm0, %mm1");   asm("pandn %mm4, %mm1");   asm("movq %mm2, %mm4");   asm("psubusb %mm3, %mm4");   asm("psubb %mm4, %mm2");   asm("pand %mm0, %mm2");   asm("por %mm2, %mm1");   asm("addl $ 4, %eax");   asm("addl $ 4, %edx");   asm("addl $ 4, %edi");    asm(".add_pixels_1a_1a_last1:");   asm("test $ 1, %ecx");   asm("jz .add_pixels_1a_1a_end");    asm("movw (%eax), %bx");   asm("movd %ebx, %mm2");   asm("movw (%edx), %bx");   asm("movd %ebx, %mm3");    asm("movq %mm2, %mm4");   asm("paddusb %mm3, %mm4");   asm("movq %mm0, %mm1");   asm("pandn %mm4, %mm1");   asm("movq %mm2, %mm4");   asm("psubusb %mm3, %mm4");   asm("psubb %mm4, %mm2");   asm("pand %mm0, %mm2");   asm("por %mm2, %mm1");   asm("movd %mm1, %ebx");   asm("movw %bx, (%edi)");    asm(".add_pixels_1a_1a_end:");    asm("emms");   asm("popl %ebx");   asm("popl %edi"); }  void gimp_composite_burn_va8_va8_va8_mmx (GimpCompositeContext *_op) {   GimpCompositeContext op = *_op;    asm("movq   %0,%%mm1"       :       : "m" (*va8_alpha_mask)       : "%mm1");    for (; op.n_pixels>= 4; op.n_pixels -= 4) {     asm volatile ("  movq      (%0),%%mm0; addl $8,%0\n"                   "\tmovq      (%1),%%mm1; addl $8,%1\n"                    "\tmovq      %3,%%mm2\n"                   "\tpsubb     %%mm0,%%mm2\n"
comment|/* mm2 = 255 - A */
end_comment

begin_comment
unit|"\tpxor      %%mm4,%%mm4\n"                   "\tpunpcklbw %%mm2,%%mm4\n"
comment|/* mm4 = (255- A) * 256  */
end_comment

begin_comment
unit|"\tmovq      %%mm1,%%mm3\n"                   "\tpxor      %%mm5,%%mm5\n"                   "\tpunpcklbw %%mm5,%%mm3\n"                   "\tmovq      %4,%%mm5\n"                   "\tpaddusw   %%mm3,%%mm5\n"
comment|/* mm5 = B + 1 */
end_comment

begin_comment
unit|"\t" pdivwqX(mm4,mm5,mm7) "\n"                    "\tmovq      %3,%%mm2\n"                   "\tpsubb     %%mm0,%%mm2\n"
comment|/* mm2 = 255 - A */
end_comment

begin_comment
unit|"\tpxor      %%mm4,%%mm4\n"                   "\tpunpckhbw %%mm2,%%mm4\n"
comment|/* mm4 = (255- A) * 256  */
end_comment

begin_comment
unit|"\tmovq      %%mm1,%%mm3\n"                   "\tpxor      %%mm5,%%mm5\n"                   "\tpunpckhbw %%mm5,%%mm3\n"                   "\tmovq      %4,%%mm5\n"                   "\tpaddusw   %%mm3,%%mm5\n"
comment|/* mm5 = B + 1 */
end_comment

begin_comment
unit|"\t" pdivwqX(mm4,mm5,mm6) "\n"                    "\tmovq      %5,%%mm4\n"                   "\tmovq      %%mm4,%%mm5\n"                   "\tpsubusw     %%mm6,%%mm4\n"                   "\tpsubusw     %%mm7,%%mm5\n"                                      "\tpackuswb  %%mm4,%%mm5\n"                    "\t" pminub(mm0,mm1,mm3) "\n"
comment|/* mm1 = min(mm0,mm1) clobber mm3 */
end_comment

begin_comment
unit|"\tmovq      %6,%%mm7\n"                   "\tpand      %%mm7,%%mm1\n"
comment|/* mm1 = mm7& alpha_mask */
end_comment

begin_comment
unit|"\tpandn     %%mm5,%%mm7\n"
comment|/* mm7 = ~mm7& mm5 */
end_comment

begin_comment
unit|"\tpor       %%mm1,%%mm7\n"
comment|/* mm7 = mm7 | mm1 */
end_comment

begin_comment
unit|"\tmovq      %%mm7,(%2); addl $8,%2\n"                   : "+r" (op.A), "+r" (op.B), "+r" (op.D)                   : "m" (*va8_b255), "m" (*va8_w1), "m" (*va8_w255), "m" (*va8_alpha_mask)                   : "0", "1", "2", "%mm1", "%mm2", "%mm3", "%mm4");   }    if (op.n_pixels) {     asm volatile ("  movd      (%0),%%mm0\n"                   "\tmovd      (%1),%%mm1\n"                    "\tmovq      %3,%%mm2\n"                   "\tpsubb     %%mm0,%%mm2\n"
comment|/* mm2 = 255 - A */
end_comment

begin_comment
unit|"\tpxor      %%mm4,%%mm4\n"                   "\tpunpcklbw %%mm2,%%mm4\n"
comment|/* mm4 = (255- A) * 256  */
end_comment

begin_comment
unit|"\tmovq      %%mm1,%%mm3\n"                   "\tpxor      %%mm5,%%mm5\n"                   "\tpunpcklbw %%mm5,%%mm3\n"                   "\tmovq      %4,%%mm5\n"                   "\tpaddusw   %%mm3,%%mm5\n"
comment|/* mm5 = B + 1 */
end_comment

begin_comment
unit|"\t" pdivwqX(mm4,mm5,mm7) "\n"                    "\tmovq      %3,%%mm2\n"                   "\tpsubb   %%mm0,%%mm2\n"
comment|/* mm2 = 255 - A */
end_comment

begin_comment
unit|"\tpxor      %%mm4,%%mm4\n"                   "\tpunpckhbw %%mm2,%%mm4\n"
comment|/* mm4 = (255- A) * 256  */
end_comment

begin_comment
unit|"\tmovq      %%mm1,%%mm3\n"                   "\tpxor      %%mm5,%%mm5\n"                   "\tpunpckhbw %%mm5,%%mm3\n"                   "\tmovq      %4,%%mm5\n"                   "\tpaddusw   %%mm3,%%mm5\n"
comment|/* mm5 = B + 1 */
end_comment

begin_comment
unit|"\t" pdivwqX(mm4,mm5,mm6) "\n"                    "\tmovq      %5,%%mm4\n"                   "\tmovq      %%mm4,%%mm5\n"                   "\tpsubusw     %%mm6,%%mm4\n"                   "\tpsubusw     %%mm7,%%mm5\n"                                      "\tpackuswb  %%mm4,%%mm5\n"                    "\t" pminub(mm0,mm1,mm3) "\n"
comment|/* mm1 = min(mm0,mm1) clobber mm3 */
end_comment

begin_comment
unit|"\tmovq      %6,%%mm7\n"                   "\tpand      %%mm7,%%mm1\n"
comment|/* mm1 = mm7& alpha_mask */
end_comment

begin_comment
unit|"\tpandn     %%mm5,%%mm7\n"
comment|/* mm7 = ~mm7& mm5 */
end_comment

begin_comment
unit|"\tpor       %%mm1,%%mm7\n"
comment|/* mm7 = mm7 | mm1 */
end_comment

begin_comment
unit|"\tmovd      %%mm7,(%2)\n"                   :
comment|/* empty */
end_comment

begin_endif
unit|: "r" (op.A), "r" (op.B), "r" (op.D), "m" (*va8_b255), "m" (*va8_w1), "m" (*va8_w255), "m" (*va8_alpha_mask)                   : "0", "1", "2", "%mm0", "%mm1", "%mm2", "%mm3", "%mm4", "%mm5", "%mm6", "%mm7");   }    asm("emms"); }  void xxxgimp_composite_coloronly_va8_va8_va8_mmx (GimpCompositeContext *_op) {   GimpCompositeContext op = *_op;  }  void gimp_composite_darken_va8_va8_va8_mmx (GimpCompositeContext *_op) {   GimpCompositeContext op = *_op;    asm("pushl %edi");   asm("pushl %ebx");   asm("movl 12(%esp), %edi");   asm("movq v8_alpha_mask, %mm0");   asm("subl $ 4, %ecx");   asm("jl .darken_pixels_1a_1a_last3");   asm("movl $ 8, %ebx");   asm(".darken_pixels_1a_1a_loop:");   asm("movq (%eax), %mm2");   asm("movq (%edx), %mm3");    asm("movq %mm2, %mm4");   asm("psubusb %mm3, %mm4");   asm("psubb %mm4, %mm2");   asm("movq %mm2, %mm1");   asm("movq %mm1, (%edi)");   asm("addl %ebx, %eax");   asm("addl %ebx, %edx");   asm("addl %ebx, %edi");   asm("subl $ 4, %ecx");   asm("jge .darken_pixels_1a_1a_loop");    asm(".darken_pixels_1a_1a_last3:");   asm("test $ 2, %ecx");   asm("jz .darken_pixels_1a_1a_last1");   asm("movd (%eax), %mm2");   asm("movd (%edx), %mm3");    asm("movq %mm2, %mm4");   asm("psubusb %mm3, %mm4");   asm("psubb %mm4, %mm2");   asm("movq %mm2, %mm1");   asm("addl $ 4, %eax");   asm("addl $ 4, %edx");   asm("addl $ 4, %edi");    asm(".darken_pixels_1a_1a_last1:");   asm("test $ 1, %ecx");   asm("jz .darken_pixels_1a_1a_end");    asm("movw (%eax), %bx");   asm("movd %ebx, %mm2");   asm("movw (%edx), %bx");   asm("movd %ebx, %mm3");    asm("movq %mm2, %mm4");   asm("psubusb %mm3, %mm4");   asm("psubb %mm4, %mm2");   asm("movq %mm2, %mm1");   asm("movd %mm1, %ebx");   asm("movw %bx, (%edi)");    asm(".darken_pixels_1a_1a_end:");    asm("emms");   asm("popl %ebx");   asm("popl %edi"); }  void gimp_composite_difference_va8_va8_va8_mmx (GimpCompositeContext *_op) {   GimpCompositeContext op = *_op;    asm("pushl %edi");   asm("pushl %ebx");   asm("movl 12(%esp), %edi");   asm("movq v8_alpha_mask, %mm0");   asm("subl $ 4, %ecx");   asm("jl .difference_pixels_1a_1a_last3");   asm("movl $ 8, %ebx");   asm(".difference_pixels_1a_1a_loop:");   asm("movq (%eax), %mm2");   asm("movq (%edx), %mm3");    asm("movq %mm2, %mm4");   asm("movq %mm3, %mm5");   asm("psubusb %mm3, %mm4");   asm("psubusb %mm2, %mm5");   asm("movq %mm0, %mm1");   asm("paddb %mm5, %mm4");   asm("pandn %mm4, %mm1");   asm("psubb %mm4, %mm2");   asm("pand %mm0, %mm2");   asm("por %mm2, %mm1");   asm("movq %mm1, (%edi)");   asm("addl %ebx, %eax");   asm("addl %ebx, %edx");   asm("addl %ebx, %edi");   asm("subl $ 4, %ecx");   asm("jge .difference_pixels_1a_1a_loop");    asm(".difference_pixels_1a_1a_last3:");   asm("test $ 2, %ecx");   asm("jz .difference_pixels_1a_1a_last1");   asm("movd (%eax), %mm2");   asm("movd (%edx), %mm3");    asm("movq %mm2, %mm4");   asm("movq %mm3, %mm5");   asm("psubusb %mm3, %mm4");   asm("psubusb %mm2, %mm5");   asm("movq %mm0, %mm1");   asm("paddb %mm5, %mm4");   asm("pandn %mm4, %mm1");   asm("psubb %mm4, %mm2");   asm("pand %mm0, %mm2");   asm("por %mm2, %mm1");   asm("addl $ 4, %eax");   asm("addl $ 4, %edx");   asm("addl $ 4, %edi");    asm(".difference_pixels_1a_1a_last1:");   asm("test $ 1, %ecx");   asm("jz .difference_pixels_1a_1a_end");    asm("movw (%eax), %bx");   asm("movd %ebx, %mm2");   asm("movw (%edx), %bx");   asm("movd %ebx, %mm3");    asm("movq %mm2, %mm4");   asm("movq %mm3, %mm5");   asm("psubusb %mm3, %mm4");   asm("psubusb %mm2, %mm5");   asm("movq %mm0, %mm1");   asm("paddb %mm5, %mm4");   asm("pandn %mm4, %mm1");   asm("psubb %mm4, %mm2");   asm("pand %mm0, %mm2");   asm("por %mm2, %mm1");   asm("movd %mm1, %ebx");   asm("movw %bx, (%edi)");    asm(".difference_pixels_1a_1a_end:");    asm("emms");   asm("popl %ebx");   asm("popl %edi"); }  void xxxgimp_composite_dissolve_va8_va8_va8_mmx (GimpCompositeContext *_op) {   GimpCompositeContext op = *_op;  }  void xxxgimp_composite_divide_va8_va8_va8_mmx (GimpCompositeContext *_op) {   GimpCompositeContext op = *_op;  }  void xxxgimp_composite_dodge_va8_va8_va8_mmx (GimpCompositeContext *_op) {   GimpCompositeContext op = *_op;  }  void xxxgimp_composite_grain_extract_va8_va8_va8_mmx (GimpCompositeContext *_op) {   GimpCompositeContext op = *_op;  }  void xxxgimp_composite_grain_merge_va8_va8_va8_mmx (GimpCompositeContext *_op) {   GimpCompositeContext op = *_op;  }  void xxxgimp_composite_hardlight_va8_va8_va8_mmx (GimpCompositeContext *_op) {   GimpCompositeContext op = *_op;  }  void xxxgimp_composite_hueonly_va8_va8_va8_mmx (GimpCompositeContext *_op) {   GimpCompositeContext op = *_op;  }  void xxxgimp_composite_lighten_va8_va8_va8_mmx (GimpCompositeContext *_op) {   GimpCompositeContext op = *_op;    asm("pushl %edi");   asm("pushl %ebx");   asm("movl 12(%esp), %edi");   asm("movq v8_alpha_mask, %mm0");   asm("subl $ 4, %ecx");   asm("jl .lighten_pixels_1a_1a_last3");   asm("movl $ 8, %ebx");   asm(".lighten_pixels_1a_1a_loop:");   asm("movq (%eax), %mm2");   asm("movq (%edx), %mm3");    asm("movq %mm2, %mm4");   asm("psubusb %mm3, %mm4");   asm("paddb %mm4, %mm3");   asm("movq %mm0, %mm1");   asm("pandn %mm3, %mm1");    asm("psubb %mm4, %mm2");   asm("pand %mm0, %mm2");   asm("por %mm2, %mm1");   asm("movq %mm1, (%edi)");   asm("addl %ebx, %eax");   asm("addl %ebx, %edx");   asm("addl %ebx, %edi");   asm("subl $ 4, %ecx");   asm("jge .lighten_pixels_1a_1a_loop");    asm(".lighten_pixels_1a_1a_last3:");   asm("test $ 2, %ecx");   asm("jz .lighten_pixels_1a_1a_last1");   asm("movd (%eax), %mm2");   asm("movd (%edx), %mm3");    asm("movq %mm2, %mm4");   asm("psubusb %mm3, %mm4");   asm("paddb %mm4, %mm3");   asm("movq %mm0, %mm1");   asm("pandn %mm3, %mm1");    asm("psubb %mm4, %mm2");   asm("pand %mm0, %mm2");   asm("por %mm2, %mm1");   asm("addl $ 4, %eax");   asm("addl $ 4, %edx");   asm("addl $ 4, %edi");    asm(".lighten_pixels_1a_1a_last1:");   asm("test $ 1, %ecx");   asm("jz .lighten_pixels_1a_1a_end");    asm("movw (%eax), %bx");   asm("movd %ebx, %mm2");   asm("movw (%edx), %bx");   asm("movd %ebx, %mm3");    asm("movq %mm2, %mm4");   asm("psubusb %mm3, %mm4");   asm("paddb %mm4, %mm3");   asm("movq %mm0, %mm1");   asm("pandn %mm3, %mm1");    asm("psubb %mm4, %mm2");   asm("pand %mm0, %mm2");   asm("por %mm2, %mm1");   asm("movd %mm1, %ebx");   asm("movw %bx, (%edi)");    asm(".lighten_pixels_1a_1a_end:");    asm("emms");   asm("popl %ebx");   asm("popl %edi"); }  void xxxgimp_composite_multiply_va8_va8_va8_mmx (GimpCompositeContext *_op) {   GimpCompositeContext op = *_op;    asm("pushl %edi");   asm("pushl %ebx");   asm("movl 12(%esp), %edi");   asm("movq v8_alpha_mask, %mm0");   asm("subl $ 4, %ecx");   asm("jl .multiply_pixels_1a_1a_last3");   asm("movl $ 8, %ebx");   asm(".multiply_pixels_1a_1a_loop:");   asm("movq (%eax), %mm2");   asm("movq (%edx), %mm3");     asm("movq %mm2, %mm1");   asm("punpcklbw %mm6, %mm1");   asm("movq %mm3, %mm5");   asm("punpcklbw %mm6, %mm5");   asm("pmullw %mm5, %mm1");   asm("paddw %mm7, %mm1");   asm("movq %mm1, %mm5");   asm("psrlw $ 8, %mm5");   asm("paddw %mm5, %mm1");   asm("psrlw $ 8, %mm1");    asm("movq %mm2, %mm4");   asm("punpckhbw %mm6, %mm4");   asm("movq %mm3, %mm5");   asm("punpckhbw %mm6, %mm5");   asm("pmullw %mm5, %mm4");   asm("paddw %mm7, %mm4");   asm("movq %mm4, %mm5");   asm("psrlw $ 8, %mm5");   asm("paddw %mm5, %mm4");   asm("psrlw $ 8, %mm4");    asm("packuswb %mm4, %mm1");    asm("movq %mm0, %mm4");   asm("pandn %mm1, %mm4");   asm("movq %mm4, %mm1");    asm("movq %mm2, %mm4");   asm("psubusb %mm3, %mm4");   asm("psubb %mm4, %mm2");   asm("pand %mm0, %mm2");   asm("por %mm2, %mm1");   asm("movq %mm1, (%edi)");   asm("addl %ebx, %eax");   asm("addl %ebx, %edx");   asm("addl %ebx, %edi");   asm("subl $ 4, %ecx");   asm("jge .multiply_pixels_1a_1a_loop");    asm(".multiply_pixels_1a_1a_last3:");   asm("test $ 2, %ecx");   asm("jz .multiply_pixels_1a_1a_last1");   asm("movd (%eax), %mm2");   asm("movd (%edx), %mm3");     asm("movq %mm2, %mm1");   asm("punpcklbw %mm6, %mm1");   asm("movq %mm3, %mm5");   asm("punpcklbw %mm6, %mm5");   asm("pmullw %mm5, %mm1");   asm("paddw %mm7, %mm1");   asm("movq %mm1, %mm5");   asm("psrlw $ 8, %mm5");   asm("paddw %mm5, %mm1");   asm("psrlw $ 8, %mm1");    asm("movq %mm2, %mm4");   asm("punpckhbw %mm6, %mm4");   asm("movq %mm3, %mm5");   asm("punpckhbw %mm6, %mm5");   asm("pmullw %mm5, %mm4");   asm("paddw %mm7, %mm4");   asm("movq %mm4, %mm5");   asm("psrlw $ 8, %mm5");   asm("paddw %mm5, %mm4");   asm("psrlw $ 8, %mm4");    asm("packuswb %mm4, %mm1");    asm("movq %mm0, %mm4");   asm("pandn %mm1, %mm4");   asm("movq %mm4, %mm1");    asm("movq %mm2, %mm4");   asm("psubusb %mm3, %mm4");   asm("psubb %mm4, %mm2");   asm("pand %mm0, %mm2");   asm("por %mm2, %mm1");   asm("addl $ 4, %eax");   asm("addl $ 4, %edx");   asm("addl $ 4, %edi");    asm(".multiply_pixels_1a_1a_last1:");   asm("test $ 1, %ecx");   asm("jz .multiply_pixels_1a_1a_end");    asm("movw (%eax), %bx");   asm("movd %ebx, %mm2");   asm("movw (%edx), %bx");   asm("movd %ebx, %mm3");     asm("movq %mm2, %mm1");   asm("punpcklbw %mm6, %mm1");   asm("movq %mm3, %mm5");   asm("punpcklbw %mm6, %mm5");   asm("pmullw %mm5, %mm1");   asm("paddw %mm7, %mm1");   asm("movq %mm1, %mm5");   asm("psrlw $ 8, %mm5");   asm("paddw %mm5, %mm1");   asm("psrlw $ 8, %mm1");    asm("movq %mm2, %mm4");   asm("punpckhbw %mm6, %mm4");   asm("movq %mm3, %mm5");   asm("punpckhbw %mm6, %mm5");   asm("pmullw %mm5, %mm4");   asm("paddw %mm7, %mm4");   asm("movq %mm4, %mm5");   asm("psrlw $ 8, %mm5");   asm("paddw %mm5, %mm4");   asm("psrlw $ 8, %mm4");    asm("packuswb %mm4, %mm1");    asm("movq %mm0, %mm4");   asm("pandn %mm1, %mm4");   asm("movq %mm4, %mm1");    asm("movq %mm2, %mm4");   asm("psubusb %mm3, %mm4");   asm("psubb %mm4, %mm2");   asm("pand %mm0, %mm2");   asm("por %mm2, %mm1");   asm("movd %mm1, %ebx");   asm("movw %bx, (%edi)");    asm(".multiply_pixels_1a_1a_end:");    asm("emms");   asm("popl %ebx");   asm("popl %edi"); }  void gimp_composite_overlay_va8_va8_va8_mmx (GimpCompositeContext *_op) {   GimpCompositeContext op = *_op;    asm("pushl %edi");   asm("pushl %ebx");   asm("movl 12(%esp), %edi");   asm("movq v8_alpha_mask, %mm0");   asm("subl $ 4, %ecx");   asm("jl .overlay_pixels_1a_1a_last3");   asm("movl $ 8, %ebx");   asm(".overlay_pixels_1a_1a_loop:");   asm("movq (%eax), %mm2");   asm("movq (%edx), %mm3");   asm("call op_overlay");   asm("movq %mm1, (%edi)");   asm("addl %ebx, %eax");   asm("addl %ebx, %edx");   asm("addl %ebx, %edi");   asm("subl $ 4, %ecx");   asm("jge .overlay_pixels_1a_1a_loop");    asm(".overlay_pixels_1a_1a_last3:");   asm("test $ 2, %ecx");   asm("jz .overlay_pixels_1a_1a_last1");   asm("movd (%eax), %mm2");   asm("movd (%edx), %mm3");   asm("call op_overlay");   asm("addl $ 4, %eax");   asm("addl $ 4, %edx");   asm("addl $ 4, %edi");    asm(".overlay_pixels_1a_1a_last1:");   asm("test $ 1, %ecx");   asm("jz .overlay_pixels_1a_1a_end");    asm("movw (%eax), %bx");   asm("movd %ebx, %mm2");   asm("movw (%edx), %bx");   asm("movd %ebx, %mm3");   asm("call op_overlay");   asm("movd %mm1, %ebx");   asm("movw %bx, (%edi)");    asm(".overlay_pixels_1a_1a_end:");    asm("emms");   asm("popl %ebx");   asm("popl %edi"); }  void xxxgimp_composite_replace_va8_va8_va8_mmx (GimpCompositeContext *_op) {   GimpCompositeContext op = *_op;  }  void xxxgimp_composite_saturationonly_va8_va8_va8_mmx (GimpCompositeContext *_op) {   GimpCompositeContext op = *_op;  }  void xxxgimp_composite_screen_va8_va8_va8_mmx (GimpCompositeContext *_op) {   GimpCompositeContext op = *_op;    asm("pushl %edi");   asm("pushl %ebx");   asm("movl 12(%esp), %edi");   asm("movq v8_alpha_mask, %mm0");   asm("subl $ 4, %ecx");   asm("jl .screen_pixels_1a_1a_last3");   asm("movl $ 8, %ebx");   asm(".screen_pixels_1a_1a_loop:");   asm("movq (%eax), %mm2");   asm("movq (%edx), %mm3");     asm("pcmpeqb %mm4, %mm4");   asm("psubb %mm2, %mm4");   asm("pcmpeqb %mm5, %mm5");   asm("psubb %mm3, %mm5");    asm("movq %mm4, %mm1");   asm("punpcklbw %mm6, %mm1");   asm("movq %mm5, %mm3");   asm("punpcklbw %mm6, %mm3");   asm("pmullw %mm3, %mm1");   asm("paddw %mm7, %mm1");   asm("movq %mm1, %mm3");   asm("psrlw $ 8, %mm3");   asm("paddw %mm3, %mm1");   asm("psrlw $ 8, %mm1");    asm("movq %mm4, %mm2");   asm("punpckhbw %mm6, %mm2");   asm("movq %mm5, %mm3");   asm("punpckhbw %mm6, %mm3");   asm("pmullw %mm3, %mm2");   asm("paddw %mm7, %mm2");   asm("movq %mm2, %mm3");   asm("psrlw $ 8, %mm3");   asm("paddw %mm3, %mm2");   asm("psrlw $ 8, %mm2");    asm("packuswb %mm2, %mm1");    asm("pcmpeqb %mm3, %mm3");   asm("psubb %mm1, %mm3");    asm("movq %mm0, %mm1");   asm("pandn %mm3, %mm1");    asm("movq %mm2, %mm4");   asm("psubusb %mm5, %mm2");   asm("paddb %mm2, %mm5");   asm("pcmpeqb %mm3, %mm3");   asm("psubb %mm5, %mm3");    asm("pand %mm0, %mm3");   asm("por %mm3, %mm1");   asm("movq %mm1, (%edi)");   asm("addl %ebx, %eax");   asm("addl %ebx, %edx");   asm("addl %ebx, %edi");   asm("subl $ 4, %ecx");   asm("jge .screen_pixels_1a_1a_loop");    asm(".screen_pixels_1a_1a_last3:");   asm("test $ 2, %ecx");   asm("jz .screen_pixels_1a_1a_last1");   asm("movd (%eax), %mm2");   asm("movd (%edx), %mm3");     asm("pcmpeqb %mm4, %mm4");   asm("psubb %mm2, %mm4");   asm("pcmpeqb %mm5, %mm5");   asm("psubb %mm3, %mm5");    asm("movq %mm4, %mm1");   asm("punpcklbw %mm6, %mm1");   asm("movq %mm5, %mm3");   asm("punpcklbw %mm6, %mm3");   asm("pmullw %mm3, %mm1");   asm("paddw %mm7, %mm1");   asm("movq %mm1, %mm3");   asm("psrlw $ 8, %mm3");   asm("paddw %mm3, %mm1");   asm("psrlw $ 8, %mm1");    asm("movq %mm4, %mm2");   asm("punpckhbw %mm6, %mm2");   asm("movq %mm5, %mm3");   asm("punpckhbw %mm6, %mm3");   asm("pmullw %mm3, %mm2");   asm("paddw %mm7, %mm2");   asm("movq %mm2, %mm3");   asm("psrlw $ 8, %mm3");   asm("paddw %mm3, %mm2");   asm("psrlw $ 8, %mm2");    asm("packuswb %mm2, %mm1");    asm("pcmpeqb %mm3, %mm3");   asm("psubb %mm1, %mm3");    asm("movq %mm0, %mm1");   asm("pandn %mm3, %mm1");    asm("movq %mm2, %mm4");   asm("psubusb %mm5, %mm2");   asm("paddb %mm2, %mm5");   asm("pcmpeqb %mm3, %mm3");   asm("psubb %mm5, %mm3");    asm("pand %mm0, %mm3");   asm("por %mm3, %mm1");   asm("addl $ 4, %eax");   asm("addl $ 4, %edx");   asm("addl $ 4, %edi");    asm(".screen_pixels_1a_1a_last1:");   asm("test $ 1, %ecx");   asm("jz .screen_pixels_1a_1a_end");    asm("movw (%eax), %bx");   asm("movd %ebx, %mm2");   asm("movw (%edx), %bx");   asm("movd %ebx, %mm3");     asm("pcmpeqb %mm4, %mm4");   asm("psubb %mm2, %mm4");   asm("pcmpeqb %mm5, %mm5");   asm("psubb %mm3, %mm5");    asm("movq %mm4, %mm1");   asm("punpcklbw %mm6, %mm1");   asm("movq %mm5, %mm3");   asm("punpcklbw %mm6, %mm3");   asm("pmullw %mm3, %mm1");   asm("paddw %mm7, %mm1");   asm("movq %mm1, %mm3");   asm("psrlw $ 8, %mm3");   asm("paddw %mm3, %mm1");   asm("psrlw $ 8, %mm1");    asm("movq %mm4, %mm2");   asm("punpckhbw %mm6, %mm2");   asm("movq %mm5, %mm3");   asm("punpckhbw %mm6, %mm3");   asm("pmullw %mm3, %mm2");   asm("paddw %mm7, %mm2");   asm("movq %mm2, %mm3");   asm("psrlw $ 8, %mm3");   asm("paddw %mm3, %mm2");   asm("psrlw $ 8, %mm2");    asm("packuswb %mm2, %mm1");    asm("pcmpeqb %mm3, %mm3");   asm("psubb %mm1, %mm3");    asm("movq %mm0, %mm1");   asm("pandn %mm3, %mm1");    asm("movq %mm2, %mm4");   asm("psubusb %mm5, %mm2");   asm("paddb %mm2, %mm5");   asm("pcmpeqb %mm3, %mm3");   asm("psubb %mm5, %mm3");    asm("pand %mm0, %mm3");   asm("por %mm3, %mm1");   asm("movd %mm1, %ebx");   asm("movw %bx, (%edi)");    asm(".screen_pixels_1a_1a_end:");    asm("emms");   asm("popl %ebx");   asm("popl %edi"); }  void xxxgimp_composite_softlight_va8_va8_va8_mmx (GimpCompositeContext *_op) {   GimpCompositeContext op = *_op;  }  void xxxgimp_composite_subtract_va8_va8_va8_mmx (GimpCompositeContext *_op) {   GimpCompositeContext op = *_op;    asm("pushl %edi");   asm("pushl %ebx");   asm("movl 12(%esp), %edi");   asm("movq v8_alpha_mask, %mm0");   asm("subl $ 4, %ecx");   asm("jl .substract_pixels_1a_1a_last3");   asm("movl $ 8, %ebx");   asm(".substract_pixels_1a_1a_loop:");   asm("movq (%eax), %mm2");   asm("movq (%edx), %mm3");    asm("movq %mm2, %mm4");   asm("psubusb %mm3, %mm4");   asm("movq %mm0, %mm1");   asm("pandn %mm4, %mm1");   asm("psubb %mm4, %mm2");   asm("pand %mm0, %mm2");   asm("por %mm2, %mm1");   asm("movq %mm1, (%edi)");   asm("addl %ebx, %eax");   asm("addl %ebx, %edx");   asm("addl %ebx, %edi");   asm("subl $ 4, %ecx");   asm("jge .substract_pixels_1a_1a_loop");    asm(".substract_pixels_1a_1a_last3:");   asm("test $ 2, %ecx");   asm("jz .substract_pixels_1a_1a_last1");   asm("movd (%eax), %mm2");   asm("movd (%edx), %mm3");    asm("movq %mm2, %mm4");   asm("psubusb %mm3, %mm4");   asm("movq %mm0, %mm1");   asm("pandn %mm4, %mm1");   asm("psubb %mm4, %mm2");   asm("pand %mm0, %mm2");   asm("por %mm2, %mm1");   asm("addl $ 4, %eax");   asm("addl $ 4, %edx");   asm("addl $ 4, %edi");    asm(".substract_pixels_1a_1a_last1:");   asm("test $ 1, %ecx");   asm("jz .substract_pixels_1a_1a_end");    asm("movw (%eax), %bx");   asm("movd %ebx, %mm2");   asm("movw (%edx), %bx");   asm("movd %ebx, %mm3");    asm("movq %mm2, %mm4");   asm("psubusb %mm3, %mm4");   asm("movq %mm0, %mm1");   asm("pandn %mm4, %mm1");   asm("psubb %mm4, %mm2");   asm("pand %mm0, %mm2");   asm("por %mm2, %mm1");   asm("movd %mm1, %ebx");   asm("movw %bx, (%edi)");    asm(".substract_pixels_1a_1a_end:");   asm("emms");   asm("popl %ebx");   asm("popl %edi"); }  void xxxgimp_composite_swap_va8_va8_va8_mmx (GimpCompositeContext *_op) {   GimpCompositeContext op = *_op;  }  void xxxgimp_composite_valueonly_va8_va8_va8_mmx (GimpCompositeContext *_op) {   GimpCompositeContext op = *_op;  }
endif|#
directive|endif
end_endif

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
comment|/* USE_MMX */
end_comment

begin_function
name|void
DECL|function|gimp_composite_mmx_init (void)
name|gimp_composite_mmx_init
parameter_list|(
name|void
parameter_list|)
block|{  }
end_function

end_unit

