begin_unit|revision:0.9.5;language:C;cregit-version:0.0.1
begin_comment
comment|/* The GIMP -- an image manipulation program  * Copyright (C) 1995 Spencer Kimball and Peter Mattis  *  * This program is free software; you can redistribute it and/or modify  * it under the terms of the GNU General Public License as published by  * the Free Software Foundation; either version 2 of the License, or  * (at your option) any later version.  *  * This program is distributed in the hope that it will be useful,  * but WITHOUT ANY WARRANTY; without even the implied warranty of  * MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the  * GNU General Public License for more details.  *  * You should have received a copy of the GNU General Public License  * along with this program; if not, write to the Free Software  * Foundation, Inc., 59 Temple Place - Suite 330, Boston, MA 02111-1307, USA.  */
end_comment

begin_comment
comment|/*  * CPU acceleration detection was taken from DirectFB but seems to be  * originating from mpeg2dec with the following copyright:  *  * Copyright (C) 1999-2001 Aaron Holtzman<aholtzma@ess.engr.uvic.ca>  */
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
file|<signal.h>
end_include

begin_include
include|#
directive|include
file|<setjmp.h>
end_include

begin_include
include|#
directive|include
file|<glib.h>
end_include

begin_include
include|#
directive|include
file|"cpu-accel.h"
end_include

begin_ifdef
ifdef|#
directive|ifdef
name|ARCH_X86
end_ifdef

begin_function
specifier|static
name|guint32
DECL|function|arch_accel (void)
name|arch_accel
parameter_list|(
name|void
parameter_list|)
block|{
name|guint32
name|eax
decl_stmt|,
name|ebx
decl_stmt|,
name|ecx
decl_stmt|,
name|edx
decl_stmt|;
name|gint
name|AMD
decl_stmt|;
name|guint32
name|caps
init|=
literal|0
decl_stmt|;
DECL|macro|cpuid (op,eax,ebx,ecx,edx)
define|#
directive|define
name|cpuid
parameter_list|(
name|op
parameter_list|,
name|eax
parameter_list|,
name|ebx
parameter_list|,
name|ecx
parameter_list|,
name|edx
parameter_list|)
define|\
value|asm ("pushl %%ebx\n\t"        \           "cpuid\n\t"              \           "movl %%ebx,%1\n\t"      \           "popl %%ebx"             \           : "=a" (eax),            \             "=r" (ebx),            \             "=c" (ecx),            \             "=d" (edx)             \           : "a" (op)               \           : "cc")
asm|asm ("pushfl\n\t"        "pushfl\n\t"        "popl %0\n\t"        "movl %0,%1\n\t"        "xorl $0x200000,%0\n\t"        "pushl %0\n\t"        "popfl\n\t"        "pushfl\n\t"        "popl %0\n\t"        "popfl"        : "=r" (eax),        "=r" (ebx)        :        : "cc");
if|if
condition|(
name|eax
operator|==
name|ebx
condition|)
comment|/* no cpuid */
return|return
literal|0
return|;
name|cpuid
argument_list|(
literal|0x00000000
argument_list|,
name|eax
argument_list|,
name|ebx
argument_list|,
name|ecx
argument_list|,
name|edx
argument_list|)
expr_stmt|;
if|if
condition|(
operator|!
name|eax
condition|)
comment|/* vendor string only */
return|return
literal|0
return|;
name|AMD
operator|=
operator|(
name|ebx
operator|==
literal|0x68747541
operator|)
operator|&&
operator|(
name|ecx
operator|==
literal|0x444d4163
operator|)
operator|&&
operator|(
name|edx
operator|==
literal|0x69746e65
operator|)
expr_stmt|;
name|cpuid
argument_list|(
literal|0x00000001
argument_list|,
name|eax
argument_list|,
name|ebx
argument_list|,
name|ecx
argument_list|,
name|edx
argument_list|)
expr_stmt|;
if|if
condition|(
operator|!
operator|(
name|edx
operator|&
literal|0x00800000
operator|)
condition|)
comment|/* no MMX */
return|return
literal|0
return|;
ifdef|#
directive|ifdef
name|USE_MMX
name|caps
operator|=
name|CPU_ACCEL_X86_MMX
expr_stmt|;
ifdef|#
directive|ifdef
name|USE_SSE
if|if
condition|(
name|edx
operator|&
literal|0x02000000
condition|)
comment|/* SSE - identical to AMD MMX extensions */
name|caps
operator||=
name|CPU_ACCEL_X86_SSE
operator||
name|CPU_ACCEL_X86_MMXEXT
expr_stmt|;
if|if
condition|(
name|edx
operator|&
literal|0x04000000
condition|)
comment|/* SSE2 */
name|caps
operator||=
name|CPU_ACCEL_X86_SSE2
expr_stmt|;
name|cpuid
argument_list|(
literal|0x80000000
argument_list|,
name|eax
argument_list|,
name|ebx
argument_list|,
name|ecx
argument_list|,
name|edx
argument_list|)
expr_stmt|;
if|if
condition|(
name|eax
operator|<
literal|0x80000001
condition|)
comment|/* no extended capabilities */
return|return
name|caps
return|;
name|cpuid
argument_list|(
literal|0x80000001
argument_list|,
name|eax
argument_list|,
name|ebx
argument_list|,
name|ecx
argument_list|,
name|edx
argument_list|)
expr_stmt|;
if|if
condition|(
name|edx
operator|&
literal|0x80000000
condition|)
name|caps
operator||=
name|CPU_ACCEL_X86_3DNOW
expr_stmt|;
if|if
condition|(
name|AMD
operator|&&
operator|(
name|edx
operator|&
literal|0x00400000
operator|)
condition|)
comment|/* AMD MMX extensions */
name|caps
operator||=
name|CPU_ACCEL_X86_MMXEXT
expr_stmt|;
endif|#
directive|endif
comment|/* USE_SSE */
endif|#
directive|endif
comment|/* USE_MMX */
return|return
name|caps
return|;
block|}
end_function

begin_decl_stmt
DECL|variable|sigill_return
specifier|static
name|jmp_buf
name|sigill_return
decl_stmt|;
end_decl_stmt

begin_function
specifier|static
name|void
DECL|function|sigill_handler (gint n)
name|sigill_handler
parameter_list|(
name|gint
name|n
parameter_list|)
block|{
name|g_printerr
argument_list|(
literal|"OS lacks support for SSE instructions.\n"
argument_list|)
expr_stmt|;
name|longjmp
argument_list|(
name|sigill_return
argument_list|,
literal|1
argument_list|)
expr_stmt|;
block|}
end_function

begin_endif
endif|#
directive|endif
end_endif

begin_comment
comment|/* ARCH_X86 */
end_comment

begin_if
if|#
directive|if
name|defined
argument_list|(
name|ARCH_PPC
argument_list|)
operator|&&
name|defined
argument_list|(
name|USE_ALTIVEC
argument_list|)
end_if

begin_decl_stmt
DECL|variable|jmpbuf
specifier|static
name|sigjmp_buf
name|jmpbuf
decl_stmt|;
end_decl_stmt

begin_decl_stmt
DECL|variable|canjump
specifier|static
specifier|volatile
name|sig_atomic_t
name|canjump
init|=
literal|0
decl_stmt|;
end_decl_stmt

begin_function
specifier|static
name|void
DECL|function|sigill_handler (gint sig)
name|sigill_handler
parameter_list|(
name|gint
name|sig
parameter_list|)
block|{
if|if
condition|(
operator|!
name|canjump
condition|)
block|{
name|signal
argument_list|(
name|sig
argument_list|,
name|SIG_DFL
argument_list|)
expr_stmt|;
name|raise
argument_list|(
name|sig
argument_list|)
expr_stmt|;
block|}
name|canjump
operator|=
literal|0
expr_stmt|;
name|siglongjmp
argument_list|(
name|jmpbuf
argument_list|,
literal|1
argument_list|)
expr_stmt|;
block|}
end_function

begin_function
specifier|static
name|guint32
DECL|function|arch_accel (void)
name|arch_accel
parameter_list|(
name|void
parameter_list|)
block|{
name|signal
argument_list|(
name|SIGILL
argument_list|,
name|sigill_handler
argument_list|)
expr_stmt|;
if|if
condition|(
name|sigsetjmp
argument_list|(
name|jmpbuf
argument_list|,
literal|1
argument_list|)
condition|)
block|{
name|signal
argument_list|(
name|SIGILL
argument_list|,
name|SIG_DFL
argument_list|)
expr_stmt|;
return|return
literal|0
return|;
block|}
name|canjump
operator|=
literal|1
expr_stmt|;
asm|asm
specifier|volatile
asm|("mtspr 256, %0\n\t" 		"vand %%v0, %%v0, %%v0" 		: 		: "r" (-1));
name|signal
argument_list|(
name|SIGILL
argument_list|,
name|SIG_DFL
argument_list|)
expr_stmt|;
return|return
name|CPU_ACCEL_PPC_ALTIVEC
return|;
block|}
end_function

begin_endif
endif|#
directive|endif
end_endif

begin_comment
comment|/* ARCH_PPC */
end_comment

begin_function
name|guint32
DECL|function|cpu_accel (void)
name|cpu_accel
parameter_list|(
name|void
parameter_list|)
block|{
if|#
directive|if
name|defined
argument_list|(
name|ARCH_X86
argument_list|)
operator|||
operator|(
name|defined
argument_list|(
name|ARCH_PPC
argument_list|)
operator|&&
name|defined
argument_list|(
name|USE_ALTIVEC
argument_list|)
operator|)
specifier|static
name|guint32
name|accel
init|=
operator|~
literal|0U
decl_stmt|;
if|if
condition|(
name|accel
operator|!=
operator|~
literal|0U
condition|)
return|return
name|accel
return|;
name|accel
operator|=
name|arch_accel
argument_list|()
expr_stmt|;
ifdef|#
directive|ifdef
name|USE_SSE
comment|/* test OS support for SSE */
if|if
condition|(
name|accel
operator|&
name|CPU_ACCEL_X86_SSE
condition|)
block|{
if|if
condition|(
name|setjmp
argument_list|(
name|sigill_return
argument_list|)
condition|)
block|{
name|accel
operator|&=
operator|~
operator|(
name|CPU_ACCEL_X86_SSE
operator||
name|CPU_ACCEL_X86_SSE2
operator|)
expr_stmt|;
block|}
else|else
block|{
name|signal
argument_list|(
name|SIGILL
argument_list|,
name|sigill_handler
argument_list|)
expr_stmt|;
asm|__asm __volatile ("xorps %xmm0, %xmm0");
name|signal
argument_list|(
name|SIGILL
argument_list|,
name|SIG_DFL
argument_list|)
expr_stmt|;
block|}
block|}
endif|#
directive|endif
comment|/* USE_SSE */
return|return
name|accel
return|;
else|#
directive|else
comment|/* !ARCH_X86&& !ARCH_PPC/USE_ALTIVEC */
return|return
literal|0
return|;
endif|#
directive|endif
block|}
end_function

end_unit

