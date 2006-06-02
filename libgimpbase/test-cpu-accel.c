begin_unit|revision:0.9.5;language:C;cregit-version:0.0.1
begin_comment
comment|/* A small test program for the CPU detection code */
end_comment

begin_include
include|#
directive|include
file|"config.h"
end_include

begin_include
include|#
directive|include
file|<stdlib.h>
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

begin_function
specifier|static
name|void
DECL|function|cpu_accel_print_results (void)
name|cpu_accel_print_results
parameter_list|(
name|void
parameter_list|)
block|{
name|GimpCpuAccelFlags
name|support
decl_stmt|;
name|g_printerr
argument_list|(
literal|"Testing CPU features...\n"
argument_list|)
expr_stmt|;
name|support
operator|=
name|gimp_cpu_accel_get_support
argument_list|()
expr_stmt|;
ifdef|#
directive|ifdef
name|ARCH_X86
name|g_printerr
argument_list|(
literal|"  mmx     : %s\n"
argument_list|,
operator|(
name|support
operator|&
name|GIMP_CPU_ACCEL_X86_MMX
operator|)
condition|?
literal|"yes"
else|:
literal|"no"
argument_list|)
expr_stmt|;
name|g_printerr
argument_list|(
literal|"  3dnow   : %s\n"
argument_list|,
operator|(
name|support
operator|&
name|GIMP_CPU_ACCEL_X86_3DNOW
operator|)
condition|?
literal|"yes"
else|:
literal|"no"
argument_list|)
expr_stmt|;
name|g_printerr
argument_list|(
literal|"  mmxext  : %s\n"
argument_list|,
operator|(
name|support
operator|&
name|GIMP_CPU_ACCEL_X86_MMXEXT
operator|)
condition|?
literal|"yes"
else|:
literal|"no"
argument_list|)
expr_stmt|;
name|g_printerr
argument_list|(
literal|"  sse     : %s\n"
argument_list|,
operator|(
name|support
operator|&
name|GIMP_CPU_ACCEL_X86_SSE
operator|)
condition|?
literal|"yes"
else|:
literal|"no"
argument_list|)
expr_stmt|;
name|g_printerr
argument_list|(
literal|"  sse2    : %s\n"
argument_list|,
operator|(
name|support
operator|&
name|GIMP_CPU_ACCEL_X86_SSE2
operator|)
condition|?
literal|"yes"
else|:
literal|"no"
argument_list|)
expr_stmt|;
name|g_printerr
argument_list|(
literal|"  sse3    : %s\n"
argument_list|,
operator|(
name|support
operator|&
name|GIMP_CPU_ACCEL_X86_SSE3
operator|)
condition|?
literal|"yes"
else|:
literal|"no"
argument_list|)
expr_stmt|;
endif|#
directive|endif
ifdef|#
directive|ifdef
name|ARCH_PPC
name|g_printerr
argument_list|(
literal|"  altivec : %s\n"
argument_list|,
operator|(
name|support
operator|&
name|GIMP_CPU_ACCEL_PPC_ALTIVEC
operator|)
condition|?
literal|"yes"
else|:
literal|"no"
argument_list|)
expr_stmt|;
endif|#
directive|endif
name|g_printerr
argument_list|(
literal|"\n"
argument_list|)
expr_stmt|;
block|}
end_function

begin_function
name|int
DECL|function|main (void)
name|main
parameter_list|(
name|void
parameter_list|)
block|{
name|cpu_accel_print_results
argument_list|()
expr_stmt|;
return|return
name|EXIT_SUCCESS
return|;
block|}
end_function

end_unit

