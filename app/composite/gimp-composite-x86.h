begin_unit|revision:0.9.5;language:C;cregit-version:0.0.1
begin_comment
comment|/* GIMP - The GNU Image Manipulation Program  * Copyright (C) 1995 Spencer Kimball and Peter Mattis  *  * This program is free software; you can redistribute it and/or modify  * it under the terms of the GNU General Public License as published by  * the Free Software Foundation; either version 2 of the License, or  * (at your option) any later version.  *  * This program is distributed in the hope that it will be useful,  * but WITHOUT ANY WARRANTY; without even the implied warranty of  * MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the  * GNU General Public License for more details.  *  * You should have received a copy of the GNU General Public License  * along with this program; if not, write to the Free Software  * Foundation, Inc., 59 Temple Place - Suite 330, Boston, MA 02111-1307, USA.  */
end_comment

begin_if
if|#
directive|if
name|__GNUC__
operator|>=
literal|3
end_if

begin_comment
comment|/*  * Convert the low 8bit byte of the src to 16bit words in dst.  */
end_comment

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
value|"\tmovq      %%"#src", %%"#dst"\n" \          "\tpunpcklbw %%"#zero", %%"#dst"\n"
end_define

begin_comment
comment|/*  * Convert the high 8bit byte of the src to 16bit words in dst.  */
end_comment

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
value|"\tmovq      %%"#src", %%"#dst"\n" \          "\tpunpckhbw %%"#zero", %%"#dst"\n"
end_define

begin_define
DECL|macro|xmm_low_bytes_to_words (src,dst,zero)
define|#
directive|define
name|xmm_low_bytes_to_words
parameter_list|(
name|src
parameter_list|,
name|dst
parameter_list|,
name|zero
parameter_list|)
define|\
value|"\tmovdqu     %%"#src", %%"#dst"; " \          "\tpunpcklbw %%"#zero", %%"#dst"\n"
end_define

begin_define
DECL|macro|xmm_high_bytes_to_words (src,dst,zero)
define|#
directive|define
name|xmm_high_bytes_to_words
parameter_list|(
name|src
parameter_list|,
name|dst
parameter_list|,
name|zero
parameter_list|)
define|\
value|"\tmovdqu     %%"#src", %%"#dst"; " \          "\tpunpckhbw %%"#zero", %%"#dst"\n"
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
DECL|macro|sse2_int_mult (a,b,w128)
define|#
directive|define
name|sse2_int_mult
parameter_list|(
name|a
parameter_list|,
name|b
parameter_list|,
name|w128
parameter_list|)
define|\
value|"\tpmullw    %%"#b",    %%"#a"; " \                   "\tpaddw     %%"#w128", %%"#a"; " \                   "\tmovdqu    %%"#a",    %%"#b"; " \                   "\tpsrlw     $8,        %%"#b"; " \                   "\tpaddw     %%"#a",    %%"#b"; " \                   "\tpsrlw     $8,        %%"#b"\n"
end_define

begin_comment
comment|/*  * Double-word divide.  Adjusted for subsequent unsigned packing  * (high-order bit of each word is cleared)  * Clobbers eax, ecx edx  */
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
value|"movd %%" #dividend ",%%eax\n" \                                           "movd %%" #divisor  ",%%ecx\n" \                                           "xorl %%edx,%%edx\n"           \                                           "divw %%cx\n"                  \                                           "roll $16, %%eax\n"            \                                           "roll $16, %%ecx\n"            \                                           "xorl %%edx,%%edx\n"           \                                           "divw %%cx\n"                  \                                           "btr $15, %%eax\n"             \                                           "roll $16, %%eax\n"            \                                           "btr $15, %%eax\n"             \                                           "movd %%eax,%%" #quotient "\n"
end_define

begin_comment
comment|/*  * Quadword divide.  No adjustment for subsequent unsigned packing  * (high-order bit of each word is left alone)  * clobber list must include: "%eax", "%ecx", "%edx", divisor quotient  */
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

begin_define
DECL|macro|pdivwqX_clobber
define|#
directive|define
name|pdivwqX_clobber
value|"%eax", "%ecx", "%edx", "%cc"
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

begin_define
DECL|macro|pdivwuqX_clobber
define|#
directive|define
name|pdivwuqX_clobber
value|pdivwqX_clobber
end_define

begin_define
DECL|macro|xmm_pdivwqX (dividend,divisor,quotient,scratch)
define|#
directive|define
name|xmm_pdivwqX
parameter_list|(
name|dividend
parameter_list|,
name|divisor
parameter_list|,
name|quotient
parameter_list|,
name|scratch
parameter_list|)
value|"movd   %%" #dividend ",%%eax; " \                                                        "movd   %%" #divisor  ",%%ecx; " \                                                        "xorl   %%edx,%%edx; "           \                                                        "divw   %%cx; "                  \                                                        "roll   $16, %%eax; "            \                                                        "roll   $16, %%ecx; "            \                                                        "xorl   %%edx,%%edx; "           \                                                        "divw   %%cx; "                  \                                                        "roll   $16, %%eax; "            \                                                        "movd   %%eax,%%" #quotient "; " \                                                        "psrlq $32,%%" #divisor ";"      \                                                        "psrlq $32,%%" #dividend ";"     \                                                        "movd   %%" #dividend ",%%eax; " \                                                        "movd   %%" #divisor  ",%%ecx; " \                                                        "xorl   %%edx,%%edx; "           \                                                        "divw   %%cx; "                  \                                                        "roll   $16, %%eax; "            \                                                        "roll   $16, %%ecx; "            \                                                        "xorl   %%edx,%%edx; "           \                                                        "divw   %%cx; "                  \                                                        "roll   $16, %%eax; "            \                                                        "movd   %%eax,%%" #scratch ";"   \                                                        "psllq  $32,%%" #scratch ";"     \                                                        "psrlq $32,%%" #divisor ";"      \                                                        "psrlq $32,%%" #dividend ";"     \                                                        "movd   %%" #dividend ",%%eax; " \                                                        "movd   %%" #divisor  ",%%ecx; " \                                                        "xorl   %%edx,%%edx; "           \                                                        "divw   %%cx; "                  \                                                        "roll   $16, %%eax; "            \                                                        "roll   $16, %%ecx; "            \                                                        "xorl   %%edx,%%edx; "           \                                                        "divw   %%cx; "                  \                                                        "roll   $16, %%eax; "            \                                                        "movd   %%eax,%%" #scratch ";"   \                                                        "psllq  $64,%%" #scratch ";"     \                                                        "psrlq $32,%%" #divisor ";"      \                                                        "psrlq $32,%%" #dividend ";"     \                                                        "movd   %%" #dividend ",%%eax; " \                                                        "movd   %%" #divisor  ",%%ecx; " \                                                        "xorl   %%edx,%%edx; "           \                                                        "divw   %%cx; "                  \                                                        "roll   $16, %%eax; "            \                                                        "roll   $16, %%ecx; "            \                                                        "xorl   %%edx,%%edx; "           \                                                        "divw   %%cx; "                  \                                                        "roll   $16, %%eax; "            \                                                        "movd   %%eax,%%" #scratch ";"   \                                                        "psllq  $96,%%" #scratch ";"     \                                                        "por    %%" #scratch ",%%" #quotient ";"
end_define

begin_define
DECL|macro|xmm_pdivwX (dividend,divisor,quotient)
define|#
directive|define
name|xmm_pdivwX
parameter_list|(
name|dividend
parameter_list|,
name|divisor
parameter_list|,
name|quotient
parameter_list|)
value|"movd %%" #dividend ",%%eax; " \                                               "movd %%" #divisor  ",%%ecx; " \                                               "xorl %%edx,%%edx; "           \                                               "divw %%cx; "                  \                                               "roll $16, %%eax; "            \                                               "roll $16, %%ecx; "            \                                               "xorl %%edx,%%edx; "           \                                               "divw %%cx; "                  \                                               "btr $15, %%eax; "             \                                               "roll $16, %%eax; "            \                                               "btr $15, %%eax; "             \                                               "movd %%eax,%%" #quotient ";"
end_define

begin_define
DECL|macro|xmm_pdivwuqX (dividend,divisor,quotient,scratch)
define|#
directive|define
name|xmm_pdivwuqX
parameter_list|(
name|dividend
parameter_list|,
name|divisor
parameter_list|,
name|quotient
parameter_list|,
name|scratch
parameter_list|)
define|\
value|xmm_pdivwX(dividend,divisor,scratch)      \                                             "movd   %%"#scratch ",%%"#quotient  ";" \                                           "psrlq  $32,%%"#dividend              ";" \                                           "psrlq  $32,%%"#divisor               ";" \                                           xmm_pdivwX(dividend,divisor,scratch)      \                                             "psllq  $32,%%"#scratch             ";" \                                             "por    %%"#scratch ",%%"#quotient  ";" \                                           "psrlq  $32,%%"#dividend              ";" \                                           "psrlq  $32,%%"#divisor               ";" \                                           xmm_pdivwX(dividend,divisor,scratch)      \                                             "psllq  $64,%%"#scratch             ";" \                                             "por    %%"#scratch ",%%"#quotient  ";" \                                           "psrlq  $32,%%"#dividend              ";" \                                           "psrlq  $32,%%"#divisor               ";" \                                           xmm_pdivwX(dividend,divisor,scratch)      \                                                                                                                                                                                                                                                                                                                                                   "psllq  $96,%%"#scratch             ";" \                                             "por    %%"#scratch ",%%"#quotient
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

begin_define
DECL|macro|xmm_pmulwX (opr1,opr2,w128)
define|#
directive|define
name|xmm_pmulwX
parameter_list|(
name|opr1
parameter_list|,
name|opr2
parameter_list|,
name|w128
parameter_list|)
define|\
value|"\tpmullw    %%"#opr2", %%"#opr1"; " \                   "\tpaddw     %%"#w128", %%"#opr1"; " \                   "\tmovdqu    %%"#opr1", %%"#opr2"; " \                   "\tpsrlw     $8,        %%"#opr2"; " \                   "\tpaddw     %%"#opr1", %%"#opr2"; " \                   "\tpsrlw     $8,        %%"#opr2"\n"
end_define

begin_typedef
DECL|typedef|uint8
typedef|typedef
name|unsigned
name|char
name|uint8
typedef|;
end_typedef

begin_typedef
DECL|typedef|uint16
typedef|typedef
name|unsigned
name|short
name|uint16
typedef|;
end_typedef

begin_typedef
DECL|typedef|uint32
typedef|typedef
name|unsigned
name|long
name|uint32
typedef|;
end_typedef

begin_typedef
DECL|typedef|uint64
typedef|typedef
name|unsigned
name|long
name|long
name|uint64
typedef|;
end_typedef

begin_typedef
DECL|struct|__anon29aadc820108
DECL|member|__uint64
DECL|typedef|uint128
typedef|typedef
struct|struct
block|{
name|uint64
name|__uint64
index|[
literal|2
index|]
decl_stmt|;
block|}
name|uint128
typedef|;
end_typedef

begin_decl_stmt
specifier|extern
specifier|const
name|guint32
name|va8_alpha_mask
index|[
literal|2
index|]
decl_stmt|;
end_decl_stmt

begin_decl_stmt
specifier|extern
specifier|const
name|guint32
name|va8_b255
index|[
literal|2
index|]
decl_stmt|;
end_decl_stmt

begin_decl_stmt
specifier|extern
specifier|const
name|guint32
name|va8_w1
index|[
literal|2
index|]
decl_stmt|;
end_decl_stmt

begin_decl_stmt
specifier|extern
specifier|const
name|guint32
name|va8_w255
index|[
literal|2
index|]
decl_stmt|;
end_decl_stmt

begin_endif
endif|#
directive|endif
end_endif

begin_comment
comment|/* __GNUC__>= 3 */
end_comment

end_unit

