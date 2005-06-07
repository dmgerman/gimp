begin_unit|revision:0.9.5;language:C;cregit-version:0.0.1
begin_comment
comment|/* The GIMP -- an image manipulation program  * Copyright (C) 1995 Spencer Kimball and Peter Mattis  *  * This program is free software; you can redistribute it and/or modify  * it under the terms of the GNU General Public License as published by  * the Free Software Foundation; either version 2 of the License, or  * (at your option) any later version.  *  * This program is distributed in the hope that it will be useful,  * but WITHOUT ANY WARRANTY; without even the implied warranty of  * MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the  * GNU General Public License for more details.  *  * You should have received a copy of the GNU General Public License  * along with this program; if not, write to the Free Software  * Foundation, Inc., 59 Temple Place - Suite 330, Boston, MA 02111-1307, USA.  */
end_comment

begin_comment
comment|/*  * CPU acceleration detection was taken from DirectFB but seems to be  * originating from mpeg2dec with the following copyright:  *  * Copyright (C) 1999-2001 Aaron Holtzman<aholtzma@ess.engr.uvic.ca>  */
end_comment

begin_ifndef
ifndef|#
directive|ifndef
name|__CPU_ACCEL_H__
end_ifndef

begin_define
DECL|macro|__CPU_ACCEL_H__
define|#
directive|define
name|__CPU_ACCEL_H__
end_define

begin_comment
comment|/* x86 accelerations */
end_comment

begin_define
DECL|macro|CPU_ACCEL_X86_MMX
define|#
directive|define
name|CPU_ACCEL_X86_MMX
value|0x80000000
end_define

begin_define
DECL|macro|CPU_ACCEL_X86_3DNOW
define|#
directive|define
name|CPU_ACCEL_X86_3DNOW
value|0x40000000
end_define

begin_define
DECL|macro|CPU_ACCEL_X86_MMXEXT
define|#
directive|define
name|CPU_ACCEL_X86_MMXEXT
value|0x20000000
end_define

begin_define
DECL|macro|CPU_ACCEL_X86_SSE
define|#
directive|define
name|CPU_ACCEL_X86_SSE
value|0x10000000
end_define

begin_define
DECL|macro|CPU_ACCEL_X86_SSE2
define|#
directive|define
name|CPU_ACCEL_X86_SSE2
value|0x08000000
end_define

begin_define
DECL|macro|CPU_ACCEL_X86_SSE3
define|#
directive|define
name|CPU_ACCEL_X86_SSE3
value|0x02000000
end_define

begin_comment
comment|/* powerpc accelerations */
end_comment

begin_define
DECL|macro|CPU_ACCEL_PPC_ALTIVEC
define|#
directive|define
name|CPU_ACCEL_PPC_ALTIVEC
value|0x04000000
end_define

begin_decl_stmt
name|guint32
name|cpu_accel
argument_list|(
name|void
argument_list|)
name|G_GNUC_CONST
decl_stmt|;
end_decl_stmt

begin_function_decl
name|void
name|cpu_accel_print_results
parameter_list|(
name|void
parameter_list|)
function_decl|;
end_function_decl

begin_endif
endif|#
directive|endif
end_endif

begin_comment
comment|/* __CPU_ACCEL_H__ */
end_comment

end_unit

