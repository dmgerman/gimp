begin_unit|revision:0.9.5;language:C;cregit-version:0.0.1
begin_comment
comment|/* LIBGIMP - The GIMP Library  * Copyright (C) 1995-1997 Peter Mattis and Spencer Kimball  *  * This library is free software: you can redistribute it and/or  * modify it under the terms of the GNU Lesser General Public  * License as published by the Free Software Foundation; either  * version 3 of the License, or (at your option) any later version.  *  * This library is distributed in the hope that it will be useful,  * but WITHOUT ANY WARRANTY; without even the implied warranty of  * MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the GNU  * Lesser General Public License for more details.  *  * You should have received a copy of the GNU Lesser General Public  * License along with this library.  If not, see  *<https://www.gnu.org/licenses/>.  */
end_comment

begin_comment
comment|/*  * x86 bits Copyright (C) Manish Singh<yosh@gimp.org>  */
end_comment

begin_comment
comment|/*  * PPC CPU acceleration detection was taken from DirectFB but seems to be  * originating from mpeg2dec with the following copyright:  *  * Copyright (C) 1999-2001 Aaron Holtzman<aholtzma@ess.engr.uvic.ca>  */
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
file|"gimpcpuaccel.h"
end_include

begin_comment
comment|/**  * SECTION: gimpcpuaccel  * @title: gimpcpuaccel  * @short_description: Functions to query and configure CPU acceleration.  *  * Functions to query and configure CPU acceleration.  **/
end_comment

begin_decl_stmt
specifier|static
name|GimpCpuAccelFlags
name|cpu_accel
argument_list|(
name|void
argument_list|)
name|G_GNUC_CONST
decl_stmt|;
end_decl_stmt

begin_decl_stmt
DECL|variable|use_cpu_accel
specifier|static
name|gboolean
name|use_cpu_accel
init|=
name|TRUE
decl_stmt|;
end_decl_stmt

begin_comment
comment|/**  * gimp_cpu_accel_get_support:  *  * Query for CPU acceleration support.  *  * Return value: #GimpCpuAccelFlags as supported by the CPU.  *  * Since: 2.4  */
end_comment

begin_function
name|GimpCpuAccelFlags
DECL|function|gimp_cpu_accel_get_support (void)
name|gimp_cpu_accel_get_support
parameter_list|(
name|void
parameter_list|)
block|{
return|return
name|use_cpu_accel
condition|?
name|cpu_accel
argument_list|()
else|:
name|GIMP_CPU_ACCEL_NONE
return|;
block|}
end_function

begin_comment
comment|/**  * gimp_cpu_accel_set_use:  * @use:  whether to use CPU acceleration features or not  *  * This function is for internal use only.  *  * Since: 2.4  */
end_comment

begin_function
name|void
DECL|function|gimp_cpu_accel_set_use (gboolean use)
name|gimp_cpu_accel_set_use
parameter_list|(
name|gboolean
name|use
parameter_list|)
block|{
name|use_cpu_accel
operator|=
name|use
condition|?
name|TRUE
else|:
name|FALSE
expr_stmt|;
block|}
end_function

begin_if
if|#
directive|if
name|defined
argument_list|(
name|ARCH_X86
argument_list|)
operator|&&
name|defined
argument_list|(
name|USE_MMX
argument_list|)
operator|&&
name|defined
argument_list|(
name|__GNUC__
argument_list|)
end_if

begin_define
DECL|macro|HAVE_ACCEL
define|#
directive|define
name|HAVE_ACCEL
value|1
end_define

begin_typedef
typedef|typedef
enum|enum
DECL|enum|__anon2a32d9c40103
block|{
DECL|enumerator|ARCH_X86_VENDOR_NONE
name|ARCH_X86_VENDOR_NONE
block|,
DECL|enumerator|ARCH_X86_VENDOR_INTEL
name|ARCH_X86_VENDOR_INTEL
block|,
DECL|enumerator|ARCH_X86_VENDOR_AMD
name|ARCH_X86_VENDOR_AMD
block|,
DECL|enumerator|ARCH_X86_VENDOR_CENTAUR
name|ARCH_X86_VENDOR_CENTAUR
block|,
DECL|enumerator|ARCH_X86_VENDOR_CYRIX
name|ARCH_X86_VENDOR_CYRIX
block|,
DECL|enumerator|ARCH_X86_VENDOR_NSC
name|ARCH_X86_VENDOR_NSC
block|,
DECL|enumerator|ARCH_X86_VENDOR_TRANSMETA
name|ARCH_X86_VENDOR_TRANSMETA
block|,
DECL|enumerator|ARCH_X86_VENDOR_NEXGEN
name|ARCH_X86_VENDOR_NEXGEN
block|,
DECL|enumerator|ARCH_X86_VENDOR_RISE
name|ARCH_X86_VENDOR_RISE
block|,
DECL|enumerator|ARCH_X86_VENDOR_UMC
name|ARCH_X86_VENDOR_UMC
block|,
DECL|enumerator|ARCH_X86_VENDOR_SIS
name|ARCH_X86_VENDOR_SIS
block|,
DECL|enumerator|ARCH_X86_VENDOR_HYGON
name|ARCH_X86_VENDOR_HYGON
block|,
DECL|enumerator|ARCH_X86_VENDOR_UNKNOWN
name|ARCH_X86_VENDOR_UNKNOWN
init|=
literal|0xff
DECL|typedef|X86Vendor
block|}
name|X86Vendor
typedef|;
end_typedef

begin_enum
enum|enum
DECL|enum|__anon2a32d9c40203
block|{
DECL|enumerator|ARCH_X86_INTEL_FEATURE_MMX
name|ARCH_X86_INTEL_FEATURE_MMX
init|=
literal|1
operator|<<
literal|23
block|,
DECL|enumerator|ARCH_X86_INTEL_FEATURE_XMM
name|ARCH_X86_INTEL_FEATURE_XMM
init|=
literal|1
operator|<<
literal|25
block|,
DECL|enumerator|ARCH_X86_INTEL_FEATURE_XMM2
name|ARCH_X86_INTEL_FEATURE_XMM2
init|=
literal|1
operator|<<
literal|26
block|,
DECL|enumerator|ARCH_X86_AMD_FEATURE_MMXEXT
name|ARCH_X86_AMD_FEATURE_MMXEXT
init|=
literal|1
operator|<<
literal|22
block|,
DECL|enumerator|ARCH_X86_AMD_FEATURE_3DNOW
name|ARCH_X86_AMD_FEATURE_3DNOW
init|=
literal|1
operator|<<
literal|31
block|,
DECL|enumerator|ARCH_X86_CENTAUR_FEATURE_MMX
name|ARCH_X86_CENTAUR_FEATURE_MMX
init|=
literal|1
operator|<<
literal|23
block|,
DECL|enumerator|ARCH_X86_CENTAUR_FEATURE_MMXEXT
name|ARCH_X86_CENTAUR_FEATURE_MMXEXT
init|=
literal|1
operator|<<
literal|24
block|,
DECL|enumerator|ARCH_X86_CENTAUR_FEATURE_3DNOW
name|ARCH_X86_CENTAUR_FEATURE_3DNOW
init|=
literal|1
operator|<<
literal|31
block|,
DECL|enumerator|ARCH_X86_CYRIX_FEATURE_MMX
name|ARCH_X86_CYRIX_FEATURE_MMX
init|=
literal|1
operator|<<
literal|23
block|,
DECL|enumerator|ARCH_X86_CYRIX_FEATURE_MMXEXT
name|ARCH_X86_CYRIX_FEATURE_MMXEXT
init|=
literal|1
operator|<<
literal|24
block|}
enum|;
end_enum

begin_enum
enum|enum
DECL|enum|__anon2a32d9c40303
block|{
DECL|enumerator|ARCH_X86_INTEL_FEATURE_PNI
name|ARCH_X86_INTEL_FEATURE_PNI
init|=
literal|1
operator|<<
literal|0
block|,
DECL|enumerator|ARCH_X86_INTEL_FEATURE_SSSE3
name|ARCH_X86_INTEL_FEATURE_SSSE3
init|=
literal|1
operator|<<
literal|9
block|,
DECL|enumerator|ARCH_X86_INTEL_FEATURE_SSE4_1
name|ARCH_X86_INTEL_FEATURE_SSE4_1
init|=
literal|1
operator|<<
literal|19
block|,
DECL|enumerator|ARCH_X86_INTEL_FEATURE_SSE4_2
name|ARCH_X86_INTEL_FEATURE_SSE4_2
init|=
literal|1
operator|<<
literal|20
block|,
DECL|enumerator|ARCH_X86_INTEL_FEATURE_AVX
name|ARCH_X86_INTEL_FEATURE_AVX
init|=
literal|1
operator|<<
literal|28
block|}
enum|;
end_enum

begin_if
if|#
directive|if
operator|!
name|defined
argument_list|(
name|ARCH_X86_64
argument_list|)
operator|&&
operator|(
name|defined
argument_list|(
name|PIC
argument_list|)
operator|||
name|defined
argument_list|(
name|__PIC__
argument_list|)
operator|)
end_if

begin_define
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
value|__asm__ ("movl %%ebx, %%esi\n\t" \            "cpuid\n\t"             \            "xchgl %%ebx,%%esi"     \            : "=a" (eax),           \              "=S" (ebx),           \              "=c" (ecx),           \              "=d" (edx)            \            : "0" (op))
end_define

begin_else
else|#
directive|else
end_else

begin_define
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
value|__asm__ ("cpuid"                 \            : "=a" (eax),           \              "=b" (ebx),           \              "=c" (ecx),           \              "=d" (edx)            \            : "0" (op))
end_define

begin_endif
endif|#
directive|endif
end_endif

begin_function
specifier|static
name|X86Vendor
DECL|function|arch_get_vendor (void)
name|arch_get_vendor
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
DECL|union|__anon2a32d9c4040a
union|union
block|{
DECL|member|idaschar
name|gchar
name|idaschar
index|[
literal|16
index|]
decl_stmt|;
DECL|member|idasint
name|int
name|idasint
index|[
literal|4
index|]
decl_stmt|;
block|}
name|id
union|;
ifndef|#
directive|ifndef
name|ARCH_X86_64
comment|/* Only need to check this on ia32 */
asm|__asm__ ("pushfl\n\t"            "pushfl\n\t"            "popl %0\n\t"            "movl %0,%1\n\t"            "xorl $0x200000,%0\n\t"            "pushl %0\n\t"            "popfl\n\t"            "pushfl\n\t"            "popl %0\n\t"            "popfl"            : "=a" (eax),              "=c" (ecx)            :            : "cc");
if|if
condition|(
name|eax
operator|==
name|ecx
condition|)
return|return
name|ARCH_X86_VENDOR_NONE
return|;
endif|#
directive|endif
name|cpuid
argument_list|(
literal|0
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
operator|==
literal|0
condition|)
return|return
name|ARCH_X86_VENDOR_NONE
return|;
name|id
operator|.
name|idasint
index|[
literal|0
index|]
operator|=
name|ebx
expr_stmt|;
name|id
operator|.
name|idasint
index|[
literal|1
index|]
operator|=
name|edx
expr_stmt|;
name|id
operator|.
name|idasint
index|[
literal|2
index|]
operator|=
name|ecx
expr_stmt|;
name|id
operator|.
name|idaschar
index|[
literal|12
index|]
operator|=
literal|'\0'
expr_stmt|;
ifdef|#
directive|ifdef
name|ARCH_X86_64
if|if
condition|(
name|strcmp
argument_list|(
name|id
operator|.
name|idaschar
argument_list|,
literal|"AuthenticAMD"
argument_list|)
operator|==
literal|0
condition|)
return|return
name|ARCH_X86_VENDOR_AMD
return|;
elseif|else
if|if
condition|(
name|strcmp
argument_list|(
name|id
operator|.
name|idaschar
argument_list|,
literal|"HygonGenuine"
argument_list|)
operator|==
literal|0
condition|)
return|return
name|ARCH_X86_VENDOR_HYGON
return|;
elseif|else
if|if
condition|(
name|strcmp
argument_list|(
name|id
operator|.
name|idaschar
argument_list|,
literal|"GenuineIntel"
argument_list|)
operator|==
literal|0
condition|)
return|return
name|ARCH_X86_VENDOR_INTEL
return|;
else|#
directive|else
if|if
condition|(
name|strcmp
argument_list|(
name|id
operator|.
name|idaschar
argument_list|,
literal|"GenuineIntel"
argument_list|)
operator|==
literal|0
condition|)
return|return
name|ARCH_X86_VENDOR_INTEL
return|;
elseif|else
if|if
condition|(
name|strcmp
argument_list|(
name|id
operator|.
name|idaschar
argument_list|,
literal|"AuthenticAMD"
argument_list|)
operator|==
literal|0
condition|)
return|return
name|ARCH_X86_VENDOR_AMD
return|;
elseif|else
if|if
condition|(
name|strcmp
argument_list|(
name|id
operator|.
name|idaschar
argument_list|,
literal|"HygonGenuine"
argument_list|)
operator|==
literal|0
condition|)
return|return
name|ARCH_X86_VENDOR_HYGON
return|;
elseif|else
if|if
condition|(
name|strcmp
argument_list|(
name|id
operator|.
name|idaschar
argument_list|,
literal|"CentaurHauls"
argument_list|)
operator|==
literal|0
condition|)
return|return
name|ARCH_X86_VENDOR_CENTAUR
return|;
elseif|else
if|if
condition|(
name|strcmp
argument_list|(
name|id
operator|.
name|idaschar
argument_list|,
literal|"CyrixInstead"
argument_list|)
operator|==
literal|0
condition|)
return|return
name|ARCH_X86_VENDOR_CYRIX
return|;
elseif|else
if|if
condition|(
name|strcmp
argument_list|(
name|id
operator|.
name|idaschar
argument_list|,
literal|"Geode by NSC"
argument_list|)
operator|==
literal|0
condition|)
return|return
name|ARCH_X86_VENDOR_NSC
return|;
elseif|else
if|if
condition|(
name|strcmp
argument_list|(
name|id
operator|.
name|idaschar
argument_list|,
literal|"GenuineTMx86"
argument_list|)
operator|==
literal|0
operator|||
name|strcmp
argument_list|(
name|id
operator|.
name|idaschar
argument_list|,
literal|"TransmetaCPU"
argument_list|)
operator|==
literal|0
condition|)
return|return
name|ARCH_X86_VENDOR_TRANSMETA
return|;
elseif|else
if|if
condition|(
name|strcmp
argument_list|(
name|id
operator|.
name|idaschar
argument_list|,
literal|"NexGenDriven"
argument_list|)
operator|==
literal|0
condition|)
return|return
name|ARCH_X86_VENDOR_NEXGEN
return|;
elseif|else
if|if
condition|(
name|strcmp
argument_list|(
name|id
operator|.
name|idaschar
argument_list|,
literal|"RiseRiseRise"
argument_list|)
operator|==
literal|0
condition|)
return|return
name|ARCH_X86_VENDOR_RISE
return|;
elseif|else
if|if
condition|(
name|strcmp
argument_list|(
name|id
operator|.
name|idaschar
argument_list|,
literal|"UMC UMC UMC "
argument_list|)
operator|==
literal|0
condition|)
return|return
name|ARCH_X86_VENDOR_UMC
return|;
elseif|else
if|if
condition|(
name|strcmp
argument_list|(
name|id
operator|.
name|idaschar
argument_list|,
literal|"SiS SiS SiS "
argument_list|)
operator|==
literal|0
condition|)
return|return
name|ARCH_X86_VENDOR_SIS
return|;
endif|#
directive|endif
return|return
name|ARCH_X86_VENDOR_UNKNOWN
return|;
block|}
end_function

begin_function
specifier|static
name|guint32
DECL|function|arch_accel_intel (void)
name|arch_accel_intel
parameter_list|(
name|void
parameter_list|)
block|{
name|guint32
name|caps
init|=
literal|0
decl_stmt|;
ifdef|#
directive|ifdef
name|USE_MMX
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
name|cpuid
argument_list|(
literal|1
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
operator|(
name|edx
operator|&
name|ARCH_X86_INTEL_FEATURE_MMX
operator|)
operator|==
literal|0
condition|)
return|return
literal|0
return|;
name|caps
operator|=
name|GIMP_CPU_ACCEL_X86_MMX
expr_stmt|;
ifdef|#
directive|ifdef
name|USE_SSE
if|if
condition|(
name|edx
operator|&
name|ARCH_X86_INTEL_FEATURE_XMM
condition|)
name|caps
operator||=
name|GIMP_CPU_ACCEL_X86_SSE
operator||
name|GIMP_CPU_ACCEL_X86_MMXEXT
expr_stmt|;
if|if
condition|(
name|edx
operator|&
name|ARCH_X86_INTEL_FEATURE_XMM2
condition|)
name|caps
operator||=
name|GIMP_CPU_ACCEL_X86_SSE2
expr_stmt|;
if|if
condition|(
name|ecx
operator|&
name|ARCH_X86_INTEL_FEATURE_PNI
condition|)
name|caps
operator||=
name|GIMP_CPU_ACCEL_X86_SSE3
expr_stmt|;
if|if
condition|(
name|ecx
operator|&
name|ARCH_X86_INTEL_FEATURE_SSSE3
condition|)
name|caps
operator||=
name|GIMP_CPU_ACCEL_X86_SSSE3
expr_stmt|;
if|if
condition|(
name|ecx
operator|&
name|ARCH_X86_INTEL_FEATURE_SSE4_1
condition|)
name|caps
operator||=
name|GIMP_CPU_ACCEL_X86_SSE4_1
expr_stmt|;
if|if
condition|(
name|ecx
operator|&
name|ARCH_X86_INTEL_FEATURE_SSE4_2
condition|)
name|caps
operator||=
name|GIMP_CPU_ACCEL_X86_SSE4_2
expr_stmt|;
if|if
condition|(
name|ecx
operator|&
name|ARCH_X86_INTEL_FEATURE_AVX
condition|)
name|caps
operator||=
name|GIMP_CPU_ACCEL_X86_AVX
expr_stmt|;
endif|#
directive|endif
comment|/* USE_SSE */
block|}
endif|#
directive|endif
comment|/* USE_MMX */
return|return
name|caps
return|;
block|}
end_function

begin_function
specifier|static
name|guint32
DECL|function|arch_accel_amd (void)
name|arch_accel_amd
parameter_list|(
name|void
parameter_list|)
block|{
name|guint32
name|caps
decl_stmt|;
name|caps
operator|=
name|arch_accel_intel
argument_list|()
expr_stmt|;
ifdef|#
directive|ifdef
name|USE_MMX
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
return|return
name|caps
return|;
ifdef|#
directive|ifdef
name|USE_SSE
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
name|ARCH_X86_AMD_FEATURE_3DNOW
condition|)
name|caps
operator||=
name|GIMP_CPU_ACCEL_X86_3DNOW
expr_stmt|;
if|if
condition|(
name|edx
operator|&
name|ARCH_X86_AMD_FEATURE_MMXEXT
condition|)
name|caps
operator||=
name|GIMP_CPU_ACCEL_X86_MMXEXT
expr_stmt|;
endif|#
directive|endif
comment|/* USE_SSE */
block|}
endif|#
directive|endif
comment|/* USE_MMX */
return|return
name|caps
return|;
block|}
end_function

begin_function
specifier|static
name|guint32
DECL|function|arch_accel_centaur (void)
name|arch_accel_centaur
parameter_list|(
name|void
parameter_list|)
block|{
name|guint32
name|caps
decl_stmt|;
name|caps
operator|=
name|arch_accel_intel
argument_list|()
expr_stmt|;
ifdef|#
directive|ifdef
name|USE_MMX
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
name|ARCH_X86_CENTAUR_FEATURE_MMX
condition|)
name|caps
operator||=
name|GIMP_CPU_ACCEL_X86_MMX
expr_stmt|;
ifdef|#
directive|ifdef
name|USE_SSE
if|if
condition|(
name|edx
operator|&
name|ARCH_X86_CENTAUR_FEATURE_3DNOW
condition|)
name|caps
operator||=
name|GIMP_CPU_ACCEL_X86_3DNOW
expr_stmt|;
if|if
condition|(
name|edx
operator|&
name|ARCH_X86_CENTAUR_FEATURE_MMXEXT
condition|)
name|caps
operator||=
name|GIMP_CPU_ACCEL_X86_MMXEXT
expr_stmt|;
endif|#
directive|endif
comment|/* USE_SSE */
block|}
endif|#
directive|endif
comment|/* USE_MMX */
return|return
name|caps
return|;
block|}
end_function

begin_function
specifier|static
name|guint32
DECL|function|arch_accel_cyrix (void)
name|arch_accel_cyrix
parameter_list|(
name|void
parameter_list|)
block|{
name|guint32
name|caps
decl_stmt|;
name|caps
operator|=
name|arch_accel_intel
argument_list|()
expr_stmt|;
ifdef|#
directive|ifdef
name|USE_MMX
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
name|cpuid
argument_list|(
literal|0
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
operator|!=
literal|2
condition|)
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
name|ARCH_X86_CYRIX_FEATURE_MMX
condition|)
name|caps
operator||=
name|GIMP_CPU_ACCEL_X86_MMX
expr_stmt|;
ifdef|#
directive|ifdef
name|USE_SSE
if|if
condition|(
name|edx
operator|&
name|ARCH_X86_CYRIX_FEATURE_MMXEXT
condition|)
name|caps
operator||=
name|GIMP_CPU_ACCEL_X86_MMXEXT
expr_stmt|;
endif|#
directive|endif
comment|/* USE_SSE */
block|}
endif|#
directive|endif
comment|/* USE_MMX */
return|return
name|caps
return|;
block|}
end_function

begin_ifdef
ifdef|#
directive|ifdef
name|USE_SSE
end_ifdef

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
name|longjmp
argument_list|(
name|sigill_return
argument_list|,
literal|1
argument_list|)
expr_stmt|;
block|}
end_function

begin_function
specifier|static
name|gboolean
DECL|function|arch_accel_sse_os_support (void)
name|arch_accel_sse_os_support
parameter_list|(
name|void
parameter_list|)
block|{
if|if
condition|(
name|setjmp
argument_list|(
name|sigill_return
argument_list|)
condition|)
block|{
return|return
name|FALSE
return|;
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
asm|__asm__
specifier|__volatile__
asm|("xorps %xmm0, %xmm0");
name|signal
argument_list|(
name|SIGILL
argument_list|,
name|SIG_DFL
argument_list|)
expr_stmt|;
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
comment|/* USE_SSE */
end_comment

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
name|caps
decl_stmt|;
name|X86Vendor
name|vendor
decl_stmt|;
name|vendor
operator|=
name|arch_get_vendor
argument_list|()
expr_stmt|;
switch|switch
condition|(
name|vendor
condition|)
block|{
case|case
name|ARCH_X86_VENDOR_NONE
case|:
name|caps
operator|=
literal|0
expr_stmt|;
break|break;
case|case
name|ARCH_X86_VENDOR_AMD
case|:
case|case
name|ARCH_X86_VENDOR_HYGON
case|:
name|caps
operator|=
name|arch_accel_amd
argument_list|()
expr_stmt|;
break|break;
case|case
name|ARCH_X86_VENDOR_CENTAUR
case|:
name|caps
operator|=
name|arch_accel_centaur
argument_list|()
expr_stmt|;
break|break;
case|case
name|ARCH_X86_VENDOR_CYRIX
case|:
case|case
name|ARCH_X86_VENDOR_NSC
case|:
name|caps
operator|=
name|arch_accel_cyrix
argument_list|()
expr_stmt|;
break|break;
comment|/* check for what Intel speced, even if UNKNOWN */
default|default:
name|caps
operator|=
name|arch_accel_intel
argument_list|()
expr_stmt|;
break|break;
block|}
ifdef|#
directive|ifdef
name|USE_SSE
if|if
condition|(
operator|(
name|caps
operator|&
name|GIMP_CPU_ACCEL_X86_SSE
operator|)
operator|&&
operator|!
name|arch_accel_sse_os_support
argument_list|()
condition|)
name|caps
operator|&=
operator|~
operator|(
name|GIMP_CPU_ACCEL_X86_SSE
operator||
name|GIMP_CPU_ACCEL_X86_SSE2
operator|)
expr_stmt|;
endif|#
directive|endif
return|return
name|caps
return|;
block|}
end_function

begin_endif
endif|#
directive|endif
end_endif

begin_comment
comment|/* ARCH_X86&& USE_MMX&& __GNUC__ */
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

begin_if
if|#
directive|if
name|defined
argument_list|(
name|HAVE_ALTIVEC_SYSCTL
argument_list|)
end_if

begin_include
include|#
directive|include
file|<sys/sysctl.h>
end_include

begin_define
DECL|macro|HAVE_ACCEL
define|#
directive|define
name|HAVE_ACCEL
value|1
end_define

begin_function
specifier|static
name|guint32
DECL|function|arch_accel (void)
name|arch_accel
parameter_list|(
name|void
parameter_list|)
block|{
name|gint
name|sels
index|[
literal|2
index|]
init|=
block|{
name|CTL_HW
block|,
name|HW_VECTORUNIT
block|}
decl_stmt|;
name|gboolean
name|has_vu
init|=
name|FALSE
decl_stmt|;
name|gsize
name|length
init|=
sizeof|sizeof
argument_list|(
name|has_vu
argument_list|)
decl_stmt|;
name|gint
name|err
decl_stmt|;
name|err
operator|=
name|sysctl
argument_list|(
name|sels
argument_list|,
literal|2
argument_list|,
operator|&
name|has_vu
argument_list|,
operator|&
name|length
argument_list|,
name|NULL
argument_list|,
literal|0
argument_list|)
expr_stmt|;
if|if
condition|(
name|err
operator|==
literal|0
operator|&&
name|has_vu
condition|)
return|return
name|GIMP_CPU_ACCEL_PPC_ALTIVEC
return|;
return|return
literal|0
return|;
block|}
end_function

begin_elif
elif|#
directive|elif
name|defined
argument_list|(
name|__GNUC__
argument_list|)
end_elif

begin_define
DECL|macro|HAVE_ACCEL
define|#
directive|define
name|HAVE_ACCEL
value|1
end_define

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
asm|("mtspr 256, %0\n\t"                 "vand %%v0, %%v0, %%v0"                 :                 : "r" (-1));
name|signal
argument_list|(
name|SIGILL
argument_list|,
name|SIG_DFL
argument_list|)
expr_stmt|;
return|return
name|GIMP_CPU_ACCEL_PPC_ALTIVEC
return|;
block|}
end_function

begin_endif
endif|#
directive|endif
end_endif

begin_comment
comment|/* __GNUC__ */
end_comment

begin_endif
endif|#
directive|endif
end_endif

begin_comment
comment|/* ARCH_PPC&& USE_ALTIVEC */
end_comment

begin_function
specifier|static
name|GimpCpuAccelFlags
DECL|function|cpu_accel (void)
name|cpu_accel
parameter_list|(
name|void
parameter_list|)
block|{
ifdef|#
directive|ifdef
name|HAVE_ACCEL
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
return|return
operator|(
name|GimpCpuAccelFlags
operator|)
name|accel
return|;
else|#
directive|else
comment|/* !HAVE_ACCEL */
return|return
name|GIMP_CPU_ACCEL_NONE
return|;
endif|#
directive|endif
block|}
end_function

end_unit

