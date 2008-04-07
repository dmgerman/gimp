begin_unit|revision:0.9.5;language:C;cregit-version:0.0.1
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
file|<string.h>
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
file|"gimp-composite-regression.h"
end_include

begin_include
include|#
directive|include
file|"gimp-composite-util.h"
end_include

begin_include
include|#
directive|include
file|"gimp-composite-generic.h"
end_include

begin_include
include|#
directive|include
file|"gimp-composite-altivec.h"
end_include

begin_function
name|int
DECL|function|gimp_composite_altivec_test (int iterations,int n_pixels)
name|gimp_composite_altivec_test
parameter_list|(
name|int
name|iterations
parameter_list|,
name|int
name|n_pixels
parameter_list|)
block|{
if|#
directive|if
name|defined
argument_list|(
name|COMPILE_ALTIVEC_IS_OKAY
argument_list|)
name|GimpCompositeContext
name|generic_ctx
decl_stmt|;
name|GimpCompositeContext
name|special_ctx
decl_stmt|;
name|double
name|ft0
decl_stmt|;
name|double
name|ft1
decl_stmt|;
name|gimp_rgba8_t
modifier|*
name|rgba8D1
decl_stmt|;
name|gimp_rgba8_t
modifier|*
name|rgba8D2
decl_stmt|;
name|gimp_rgba8_t
modifier|*
name|rgba8A
decl_stmt|;
name|gimp_rgba8_t
modifier|*
name|rgba8B
decl_stmt|;
name|gimp_rgba8_t
modifier|*
name|rgba8M
decl_stmt|;
name|gimp_va8_t
modifier|*
name|va8A
decl_stmt|;
name|gimp_va8_t
modifier|*
name|va8B
decl_stmt|;
name|gimp_va8_t
modifier|*
name|va8M
decl_stmt|;
name|gimp_va8_t
modifier|*
name|va8D1
decl_stmt|;
name|gimp_va8_t
modifier|*
name|va8D2
decl_stmt|;
name|int
name|i
decl_stmt|;
if|if
condition|(
name|gimp_composite_altivec_init
argument_list|()
operator|==
literal|0
condition|)
block|{
name|g_print
argument_list|(
literal|"\ngimp_composite_altivec: Instruction set is not available.\n"
argument_list|)
expr_stmt|;
return|return
name|EXIT_SUCCESS
return|;
block|}
name|g_print
argument_list|(
literal|"\nRunning gimp_composite_altivec tests...\n"
argument_list|)
expr_stmt|;
name|rgba8A
operator|=
name|gimp_composite_regression_random_rgba8
argument_list|(
name|n_pixels
operator|+
literal|1
argument_list|)
expr_stmt|;
name|rgba8B
operator|=
name|gimp_composite_regression_random_rgba8
argument_list|(
name|n_pixels
operator|+
literal|1
argument_list|)
expr_stmt|;
name|rgba8M
operator|=
name|gimp_composite_regression_random_rgba8
argument_list|(
name|n_pixels
operator|+
literal|1
argument_list|)
expr_stmt|;
name|rgba8D1
operator|=
operator|(
name|gimp_rgba8_t
operator|*
operator|)
name|calloc
argument_list|(
sizeof|sizeof
argument_list|(
name|gimp_rgba8_t
argument_list|)
argument_list|,
name|n_pixels
operator|+
literal|1
argument_list|)
expr_stmt|;
name|rgba8D2
operator|=
operator|(
name|gimp_rgba8_t
operator|*
operator|)
name|calloc
argument_list|(
sizeof|sizeof
argument_list|(
name|gimp_rgba8_t
argument_list|)
argument_list|,
name|n_pixels
operator|+
literal|1
argument_list|)
expr_stmt|;
name|va8A
operator|=
operator|(
name|gimp_va8_t
operator|*
operator|)
name|calloc
argument_list|(
sizeof|sizeof
argument_list|(
name|gimp_va8_t
argument_list|)
argument_list|,
name|n_pixels
operator|+
literal|1
argument_list|)
expr_stmt|;
name|va8B
operator|=
operator|(
name|gimp_va8_t
operator|*
operator|)
name|calloc
argument_list|(
sizeof|sizeof
argument_list|(
name|gimp_va8_t
argument_list|)
argument_list|,
name|n_pixels
operator|+
literal|1
argument_list|)
expr_stmt|;
name|va8M
operator|=
operator|(
name|gimp_va8_t
operator|*
operator|)
name|calloc
argument_list|(
sizeof|sizeof
argument_list|(
name|gimp_va8_t
argument_list|)
argument_list|,
name|n_pixels
operator|+
literal|1
argument_list|)
expr_stmt|;
name|va8D1
operator|=
operator|(
name|gimp_va8_t
operator|*
operator|)
name|calloc
argument_list|(
sizeof|sizeof
argument_list|(
name|gimp_va8_t
argument_list|)
argument_list|,
name|n_pixels
operator|+
literal|1
argument_list|)
expr_stmt|;
name|va8D2
operator|=
operator|(
name|gimp_va8_t
operator|*
operator|)
name|calloc
argument_list|(
sizeof|sizeof
argument_list|(
name|gimp_va8_t
argument_list|)
argument_list|,
name|n_pixels
operator|+
literal|1
argument_list|)
expr_stmt|;
for|for
control|(
name|i
operator|=
literal|0
init|;
name|i
operator|<
name|n_pixels
condition|;
name|i
operator|++
control|)
block|{
name|va8A
index|[
name|i
index|]
operator|.
name|v
operator|=
name|i
expr_stmt|;
name|va8A
index|[
name|i
index|]
operator|.
name|a
operator|=
literal|255
operator|-
name|i
expr_stmt|;
name|va8B
index|[
name|i
index|]
operator|.
name|v
operator|=
name|i
expr_stmt|;
name|va8B
index|[
name|i
index|]
operator|.
name|a
operator|=
name|i
expr_stmt|;
name|va8M
index|[
name|i
index|]
operator|.
name|v
operator|=
name|i
expr_stmt|;
name|va8M
index|[
name|i
index|]
operator|.
name|a
operator|=
name|i
expr_stmt|;
block|}
endif|#
directive|endif
return|return
name|EXIT_SUCCESS
return|;
block|}
end_function

begin_function
name|int
DECL|function|main (int argc,char * argv[])
name|main
parameter_list|(
name|int
name|argc
parameter_list|,
name|char
modifier|*
name|argv
index|[]
parameter_list|)
block|{
name|int
name|iterations
decl_stmt|;
name|int
name|n_pixels
decl_stmt|;
name|srand
argument_list|(
literal|314159
argument_list|)
expr_stmt|;
name|g_setenv
argument_list|(
literal|"GIMP_COMPOSITE"
argument_list|,
literal|"0x1"
argument_list|,
name|TRUE
argument_list|)
expr_stmt|;
name|iterations
operator|=
literal|10
expr_stmt|;
name|n_pixels
operator|=
literal|8388625
expr_stmt|;
name|argv
operator|++
operator|,
name|argc
operator|--
expr_stmt|;
while|while
condition|(
name|argc
operator|>=
literal|2
condition|)
block|{
if|if
condition|(
name|argc
operator|>
literal|1
operator|&&
operator|(
name|strcmp
argument_list|(
name|argv
index|[
literal|0
index|]
argument_list|,
literal|"--iterations"
argument_list|)
operator|==
literal|0
operator|||
name|strcmp
argument_list|(
name|argv
index|[
literal|0
index|]
argument_list|,
literal|"-i"
argument_list|)
operator|==
literal|0
operator|)
condition|)
block|{
name|iterations
operator|=
name|atoi
argument_list|(
name|argv
index|[
literal|1
index|]
argument_list|)
expr_stmt|;
name|argc
operator|-=
literal|2
operator|,
name|argv
operator|++
expr_stmt|;
name|argv
operator|++
expr_stmt|;
block|}
elseif|else
if|if
condition|(
name|argc
operator|>
literal|1
operator|&&
operator|(
name|strcmp
argument_list|(
name|argv
index|[
literal|0
index|]
argument_list|,
literal|"--n-pixels"
argument_list|)
operator|==
literal|0
operator|||
name|strcmp
argument_list|(
name|argv
index|[
literal|0
index|]
argument_list|,
literal|"-n"
argument_list|)
operator|==
literal|0
operator|)
condition|)
block|{
name|n_pixels
operator|=
name|atoi
argument_list|(
name|argv
index|[
literal|1
index|]
argument_list|)
expr_stmt|;
name|argc
operator|-=
literal|2
operator|,
name|argv
operator|++
expr_stmt|;
name|argv
operator|++
expr_stmt|;
block|}
else|else
block|{
name|g_print
argument_list|(
literal|"Usage: gimp-composites-*-test [-i|--iterations n] [-n|--n-pixels n]"
argument_list|)
expr_stmt|;
return|return
name|EXIT_FAILURE
return|;
block|}
block|}
name|gimp_composite_generic_install
argument_list|()
expr_stmt|;
return|return
operator|(
name|gimp_composite_altivec_test
argument_list|(
name|iterations
argument_list|,
name|n_pixels
argument_list|)
operator|)
return|;
block|}
end_function

end_unit

