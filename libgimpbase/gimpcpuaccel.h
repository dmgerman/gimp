begin_unit|revision:0.9.5;language:C;cregit-version:0.0.1
begin_comment
comment|/* LIBGIMP - The GIMP Library  * Copyright (C) 1995-1997 Peter Mattis and Spencer Kimball  *  * This library is free software: you can redistribute it and/or  * modify it under the terms of the GNU Lesser General Public  * License as published by the Free Software Foundation; either  * version 3 of the License, or (at your option) any later version.  *  * This library is distributed in the hope that it will be useful,  * but WITHOUT ANY WARRANTY; without even the implied warranty of  * MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the GNU  * Library General Public License for more details.  *  * You should have received a copy of the GNU Lesser General Public  * License along with this library.  If not, see  *<http://www.gnu.org/licenses/>.  */
end_comment

begin_if
if|#
directive|if
operator|!
name|defined
argument_list|(
name|__GIMP_BASE_H_INSIDE__
argument_list|)
operator|&&
operator|!
name|defined
argument_list|(
name|GIMP_BASE_COMPILATION
argument_list|)
end_if

begin_error
error|#
directive|error
literal|"Only<libgimpbase/gimpbase.h> can be included directly."
end_error

begin_endif
endif|#
directive|endif
end_endif

begin_ifndef
ifndef|#
directive|ifndef
name|__GIMP_CPU_ACCEL_H__
end_ifndef

begin_define
DECL|macro|__GIMP_CPU_ACCEL_H__
define|#
directive|define
name|__GIMP_CPU_ACCEL_H__
end_define

begin_macro
name|G_BEGIN_DECLS
end_macro

begin_typedef
typedef|typedef
enum|enum
DECL|enum|__anon2b1642b70103
block|{
DECL|enumerator|GIMP_CPU_ACCEL_NONE
name|GIMP_CPU_ACCEL_NONE
init|=
literal|0x0
block|,
comment|/* x86 accelerations */
DECL|enumerator|GIMP_CPU_ACCEL_X86_MMX
name|GIMP_CPU_ACCEL_X86_MMX
init|=
literal|0x80000000
block|,
DECL|enumerator|GIMP_CPU_ACCEL_X86_3DNOW
name|GIMP_CPU_ACCEL_X86_3DNOW
init|=
literal|0x40000000
block|,
DECL|enumerator|GIMP_CPU_ACCEL_X86_MMXEXT
name|GIMP_CPU_ACCEL_X86_MMXEXT
init|=
literal|0x20000000
block|,
DECL|enumerator|GIMP_CPU_ACCEL_X86_SSE
name|GIMP_CPU_ACCEL_X86_SSE
init|=
literal|0x10000000
block|,
DECL|enumerator|GIMP_CPU_ACCEL_X86_SSE2
name|GIMP_CPU_ACCEL_X86_SSE2
init|=
literal|0x08000000
block|,
DECL|enumerator|GIMP_CPU_ACCEL_X86_SSE3
name|GIMP_CPU_ACCEL_X86_SSE3
init|=
literal|0x02000000
block|,
comment|/* powerpc accelerations */
DECL|enumerator|GIMP_CPU_ACCEL_PPC_ALTIVEC
name|GIMP_CPU_ACCEL_PPC_ALTIVEC
init|=
literal|0x04000000
DECL|typedef|GimpCpuAccelFlags
block|}
name|GimpCpuAccelFlags
typedef|;
end_typedef

begin_function_decl
name|GimpCpuAccelFlags
name|gimp_cpu_accel_get_support
parameter_list|(
name|void
parameter_list|)
function_decl|;
end_function_decl

begin_comment
comment|/* for internal use only */
end_comment

begin_function_decl
name|void
name|gimp_cpu_accel_set_use
parameter_list|(
name|gboolean
name|use
parameter_list|)
function_decl|;
end_function_decl

begin_macro
name|G_END_DECLS
end_macro

begin_endif
endif|#
directive|endif
end_endif

begin_comment
comment|/* __GIMP_CPU_ACCEL_H__ */
end_comment

end_unit

