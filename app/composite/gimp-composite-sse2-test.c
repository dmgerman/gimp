begin_unit|revision:0.9.5;language:C;cregit-version:0.0.1
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
file|<sys/time.h>
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
file|"gimp-composite-sse2.h"
end_include

begin_function
name|int
DECL|function|gimp_composite_sse2_test (int iterations,int n_pixels)
name|gimp_composite_sse2_test
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
operator|(
name|__GNUC__
operator|>=
literal|3
operator|)
operator|&&
name|defined
argument_list|(
name|USE_SSE
argument_list|)
operator|&&
name|defined
argument_list|(
name|ARCH_X86
argument_list|)
operator|&&
operator|(
name|defined
argument_list|(
name|ARCH_X86_64
argument_list|)
operator|||
operator|!
name|defined
argument_list|(
name|PIC
argument_list|)
operator|)
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
name|printf
argument_list|(
literal|"\nRunning gimp_composite_sse2 tests...\n"
argument_list|)
expr_stmt|;
if|if
condition|(
name|gimp_composite_sse2_init
argument_list|()
operator|==
literal|0
condition|)
block|{
name|printf
argument_list|(
literal|"gimp_composite_sse2: Instruction set is not available.\n"
argument_list|)
expr_stmt|;
return|return
operator|(
literal|0
operator|)
return|;
block|}
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
name|gimp_composite_context_init
argument_list|(
operator|&
name|special_ctx
argument_list|,
name|GIMP_COMPOSITE_ADDITION
argument_list|,
name|GIMP_PIXELFORMAT_RGBA8
argument_list|,
name|GIMP_PIXELFORMAT_RGBA8
argument_list|,
name|GIMP_PIXELFORMAT_RGBA8
argument_list|,
name|GIMP_PIXELFORMAT_RGBA8
argument_list|,
name|n_pixels
argument_list|,
operator|(
name|unsigned
name|char
operator|*
operator|)
name|rgba8A
argument_list|,
operator|(
name|unsigned
name|char
operator|*
operator|)
name|rgba8B
argument_list|,
operator|(
name|unsigned
name|char
operator|*
operator|)
name|rgba8B
argument_list|,
operator|(
name|unsigned
name|char
operator|*
operator|)
name|rgba8D2
argument_list|)
expr_stmt|;
name|gimp_composite_context_init
argument_list|(
operator|&
name|generic_ctx
argument_list|,
name|GIMP_COMPOSITE_ADDITION
argument_list|,
name|GIMP_PIXELFORMAT_RGBA8
argument_list|,
name|GIMP_PIXELFORMAT_RGBA8
argument_list|,
name|GIMP_PIXELFORMAT_RGBA8
argument_list|,
name|GIMP_PIXELFORMAT_RGBA8
argument_list|,
name|n_pixels
argument_list|,
operator|(
name|unsigned
name|char
operator|*
operator|)
name|rgba8A
argument_list|,
operator|(
name|unsigned
name|char
operator|*
operator|)
name|rgba8B
argument_list|,
operator|(
name|unsigned
name|char
operator|*
operator|)
name|rgba8B
argument_list|,
operator|(
name|unsigned
name|char
operator|*
operator|)
name|rgba8D1
argument_list|)
expr_stmt|;
name|ft0
operator|=
name|gimp_composite_regression_time_function
argument_list|(
name|iterations
argument_list|,
name|gimp_composite_dispatch
argument_list|,
operator|&
name|generic_ctx
argument_list|)
expr_stmt|;
name|ft1
operator|=
name|gimp_composite_regression_time_function
argument_list|(
name|iterations
argument_list|,
name|gimp_composite_addition_rgba8_rgba8_rgba8_sse2
argument_list|,
operator|&
name|special_ctx
argument_list|)
expr_stmt|;
if|if
condition|(
name|gimp_composite_regression_compare_contexts
argument_list|(
literal|"addition"
argument_list|,
operator|&
name|generic_ctx
argument_list|,
operator|&
name|special_ctx
argument_list|)
condition|)
block|{
name|printf
argument_list|(
literal|"addition failed\n"
argument_list|)
expr_stmt|;
return|return
operator|(
literal|1
operator|)
return|;
block|}
name|gimp_composite_regression_timer_report
argument_list|(
literal|"addition"
argument_list|,
name|ft0
argument_list|,
name|ft1
argument_list|)
expr_stmt|;
name|gimp_composite_context_init
argument_list|(
operator|&
name|special_ctx
argument_list|,
name|GIMP_COMPOSITE_DARKEN
argument_list|,
name|GIMP_PIXELFORMAT_RGBA8
argument_list|,
name|GIMP_PIXELFORMAT_RGBA8
argument_list|,
name|GIMP_PIXELFORMAT_RGBA8
argument_list|,
name|GIMP_PIXELFORMAT_RGBA8
argument_list|,
name|n_pixels
argument_list|,
operator|(
name|unsigned
name|char
operator|*
operator|)
name|rgba8A
argument_list|,
operator|(
name|unsigned
name|char
operator|*
operator|)
name|rgba8B
argument_list|,
operator|(
name|unsigned
name|char
operator|*
operator|)
name|rgba8B
argument_list|,
operator|(
name|unsigned
name|char
operator|*
operator|)
name|rgba8D2
argument_list|)
expr_stmt|;
name|gimp_composite_context_init
argument_list|(
operator|&
name|generic_ctx
argument_list|,
name|GIMP_COMPOSITE_DARKEN
argument_list|,
name|GIMP_PIXELFORMAT_RGBA8
argument_list|,
name|GIMP_PIXELFORMAT_RGBA8
argument_list|,
name|GIMP_PIXELFORMAT_RGBA8
argument_list|,
name|GIMP_PIXELFORMAT_RGBA8
argument_list|,
name|n_pixels
argument_list|,
operator|(
name|unsigned
name|char
operator|*
operator|)
name|rgba8A
argument_list|,
operator|(
name|unsigned
name|char
operator|*
operator|)
name|rgba8B
argument_list|,
operator|(
name|unsigned
name|char
operator|*
operator|)
name|rgba8B
argument_list|,
operator|(
name|unsigned
name|char
operator|*
operator|)
name|rgba8D1
argument_list|)
expr_stmt|;
name|ft0
operator|=
name|gimp_composite_regression_time_function
argument_list|(
name|iterations
argument_list|,
name|gimp_composite_dispatch
argument_list|,
operator|&
name|generic_ctx
argument_list|)
expr_stmt|;
name|ft1
operator|=
name|gimp_composite_regression_time_function
argument_list|(
name|iterations
argument_list|,
name|gimp_composite_darken_rgba8_rgba8_rgba8_sse2
argument_list|,
operator|&
name|special_ctx
argument_list|)
expr_stmt|;
if|if
condition|(
name|gimp_composite_regression_compare_contexts
argument_list|(
literal|"darken"
argument_list|,
operator|&
name|generic_ctx
argument_list|,
operator|&
name|special_ctx
argument_list|)
condition|)
block|{
name|printf
argument_list|(
literal|"darken failed\n"
argument_list|)
expr_stmt|;
return|return
operator|(
literal|1
operator|)
return|;
block|}
name|gimp_composite_regression_timer_report
argument_list|(
literal|"darken"
argument_list|,
name|ft0
argument_list|,
name|ft1
argument_list|)
expr_stmt|;
name|gimp_composite_context_init
argument_list|(
operator|&
name|special_ctx
argument_list|,
name|GIMP_COMPOSITE_DIFFERENCE
argument_list|,
name|GIMP_PIXELFORMAT_RGBA8
argument_list|,
name|GIMP_PIXELFORMAT_RGBA8
argument_list|,
name|GIMP_PIXELFORMAT_RGBA8
argument_list|,
name|GIMP_PIXELFORMAT_RGBA8
argument_list|,
name|n_pixels
argument_list|,
operator|(
name|unsigned
name|char
operator|*
operator|)
name|rgba8A
argument_list|,
operator|(
name|unsigned
name|char
operator|*
operator|)
name|rgba8B
argument_list|,
operator|(
name|unsigned
name|char
operator|*
operator|)
name|rgba8B
argument_list|,
operator|(
name|unsigned
name|char
operator|*
operator|)
name|rgba8D2
argument_list|)
expr_stmt|;
name|gimp_composite_context_init
argument_list|(
operator|&
name|generic_ctx
argument_list|,
name|GIMP_COMPOSITE_DIFFERENCE
argument_list|,
name|GIMP_PIXELFORMAT_RGBA8
argument_list|,
name|GIMP_PIXELFORMAT_RGBA8
argument_list|,
name|GIMP_PIXELFORMAT_RGBA8
argument_list|,
name|GIMP_PIXELFORMAT_RGBA8
argument_list|,
name|n_pixels
argument_list|,
operator|(
name|unsigned
name|char
operator|*
operator|)
name|rgba8A
argument_list|,
operator|(
name|unsigned
name|char
operator|*
operator|)
name|rgba8B
argument_list|,
operator|(
name|unsigned
name|char
operator|*
operator|)
name|rgba8B
argument_list|,
operator|(
name|unsigned
name|char
operator|*
operator|)
name|rgba8D1
argument_list|)
expr_stmt|;
name|ft0
operator|=
name|gimp_composite_regression_time_function
argument_list|(
name|iterations
argument_list|,
name|gimp_composite_dispatch
argument_list|,
operator|&
name|generic_ctx
argument_list|)
expr_stmt|;
name|ft1
operator|=
name|gimp_composite_regression_time_function
argument_list|(
name|iterations
argument_list|,
name|gimp_composite_difference_rgba8_rgba8_rgba8_sse2
argument_list|,
operator|&
name|special_ctx
argument_list|)
expr_stmt|;
if|if
condition|(
name|gimp_composite_regression_compare_contexts
argument_list|(
literal|"difference"
argument_list|,
operator|&
name|generic_ctx
argument_list|,
operator|&
name|special_ctx
argument_list|)
condition|)
block|{
name|printf
argument_list|(
literal|"difference failed\n"
argument_list|)
expr_stmt|;
return|return
operator|(
literal|1
operator|)
return|;
block|}
name|gimp_composite_regression_timer_report
argument_list|(
literal|"difference"
argument_list|,
name|ft0
argument_list|,
name|ft1
argument_list|)
expr_stmt|;
name|gimp_composite_context_init
argument_list|(
operator|&
name|special_ctx
argument_list|,
name|GIMP_COMPOSITE_GRAIN_EXTRACT
argument_list|,
name|GIMP_PIXELFORMAT_RGBA8
argument_list|,
name|GIMP_PIXELFORMAT_RGBA8
argument_list|,
name|GIMP_PIXELFORMAT_RGBA8
argument_list|,
name|GIMP_PIXELFORMAT_RGBA8
argument_list|,
name|n_pixels
argument_list|,
operator|(
name|unsigned
name|char
operator|*
operator|)
name|rgba8A
argument_list|,
operator|(
name|unsigned
name|char
operator|*
operator|)
name|rgba8B
argument_list|,
operator|(
name|unsigned
name|char
operator|*
operator|)
name|rgba8B
argument_list|,
operator|(
name|unsigned
name|char
operator|*
operator|)
name|rgba8D2
argument_list|)
expr_stmt|;
name|gimp_composite_context_init
argument_list|(
operator|&
name|generic_ctx
argument_list|,
name|GIMP_COMPOSITE_GRAIN_EXTRACT
argument_list|,
name|GIMP_PIXELFORMAT_RGBA8
argument_list|,
name|GIMP_PIXELFORMAT_RGBA8
argument_list|,
name|GIMP_PIXELFORMAT_RGBA8
argument_list|,
name|GIMP_PIXELFORMAT_RGBA8
argument_list|,
name|n_pixels
argument_list|,
operator|(
name|unsigned
name|char
operator|*
operator|)
name|rgba8A
argument_list|,
operator|(
name|unsigned
name|char
operator|*
operator|)
name|rgba8B
argument_list|,
operator|(
name|unsigned
name|char
operator|*
operator|)
name|rgba8B
argument_list|,
operator|(
name|unsigned
name|char
operator|*
operator|)
name|rgba8D1
argument_list|)
expr_stmt|;
name|ft0
operator|=
name|gimp_composite_regression_time_function
argument_list|(
name|iterations
argument_list|,
name|gimp_composite_dispatch
argument_list|,
operator|&
name|generic_ctx
argument_list|)
expr_stmt|;
name|ft1
operator|=
name|gimp_composite_regression_time_function
argument_list|(
name|iterations
argument_list|,
name|gimp_composite_grain_extract_rgba8_rgba8_rgba8_sse2
argument_list|,
operator|&
name|special_ctx
argument_list|)
expr_stmt|;
if|if
condition|(
name|gimp_composite_regression_compare_contexts
argument_list|(
literal|"grain_extract"
argument_list|,
operator|&
name|generic_ctx
argument_list|,
operator|&
name|special_ctx
argument_list|)
condition|)
block|{
name|printf
argument_list|(
literal|"grain_extract failed\n"
argument_list|)
expr_stmt|;
return|return
operator|(
literal|1
operator|)
return|;
block|}
name|gimp_composite_regression_timer_report
argument_list|(
literal|"grain_extract"
argument_list|,
name|ft0
argument_list|,
name|ft1
argument_list|)
expr_stmt|;
name|gimp_composite_context_init
argument_list|(
operator|&
name|special_ctx
argument_list|,
name|GIMP_COMPOSITE_LIGHTEN
argument_list|,
name|GIMP_PIXELFORMAT_RGBA8
argument_list|,
name|GIMP_PIXELFORMAT_RGBA8
argument_list|,
name|GIMP_PIXELFORMAT_RGBA8
argument_list|,
name|GIMP_PIXELFORMAT_RGBA8
argument_list|,
name|n_pixels
argument_list|,
operator|(
name|unsigned
name|char
operator|*
operator|)
name|rgba8A
argument_list|,
operator|(
name|unsigned
name|char
operator|*
operator|)
name|rgba8B
argument_list|,
operator|(
name|unsigned
name|char
operator|*
operator|)
name|rgba8B
argument_list|,
operator|(
name|unsigned
name|char
operator|*
operator|)
name|rgba8D2
argument_list|)
expr_stmt|;
name|gimp_composite_context_init
argument_list|(
operator|&
name|generic_ctx
argument_list|,
name|GIMP_COMPOSITE_LIGHTEN
argument_list|,
name|GIMP_PIXELFORMAT_RGBA8
argument_list|,
name|GIMP_PIXELFORMAT_RGBA8
argument_list|,
name|GIMP_PIXELFORMAT_RGBA8
argument_list|,
name|GIMP_PIXELFORMAT_RGBA8
argument_list|,
name|n_pixels
argument_list|,
operator|(
name|unsigned
name|char
operator|*
operator|)
name|rgba8A
argument_list|,
operator|(
name|unsigned
name|char
operator|*
operator|)
name|rgba8B
argument_list|,
operator|(
name|unsigned
name|char
operator|*
operator|)
name|rgba8B
argument_list|,
operator|(
name|unsigned
name|char
operator|*
operator|)
name|rgba8D1
argument_list|)
expr_stmt|;
name|ft0
operator|=
name|gimp_composite_regression_time_function
argument_list|(
name|iterations
argument_list|,
name|gimp_composite_dispatch
argument_list|,
operator|&
name|generic_ctx
argument_list|)
expr_stmt|;
name|ft1
operator|=
name|gimp_composite_regression_time_function
argument_list|(
name|iterations
argument_list|,
name|gimp_composite_lighten_rgba8_rgba8_rgba8_sse2
argument_list|,
operator|&
name|special_ctx
argument_list|)
expr_stmt|;
if|if
condition|(
name|gimp_composite_regression_compare_contexts
argument_list|(
literal|"lighten"
argument_list|,
operator|&
name|generic_ctx
argument_list|,
operator|&
name|special_ctx
argument_list|)
condition|)
block|{
name|printf
argument_list|(
literal|"lighten failed\n"
argument_list|)
expr_stmt|;
return|return
operator|(
literal|1
operator|)
return|;
block|}
name|gimp_composite_regression_timer_report
argument_list|(
literal|"lighten"
argument_list|,
name|ft0
argument_list|,
name|ft1
argument_list|)
expr_stmt|;
name|gimp_composite_context_init
argument_list|(
operator|&
name|special_ctx
argument_list|,
name|GIMP_COMPOSITE_SUBTRACT
argument_list|,
name|GIMP_PIXELFORMAT_RGBA8
argument_list|,
name|GIMP_PIXELFORMAT_RGBA8
argument_list|,
name|GIMP_PIXELFORMAT_RGBA8
argument_list|,
name|GIMP_PIXELFORMAT_RGBA8
argument_list|,
name|n_pixels
argument_list|,
operator|(
name|unsigned
name|char
operator|*
operator|)
name|rgba8A
argument_list|,
operator|(
name|unsigned
name|char
operator|*
operator|)
name|rgba8B
argument_list|,
operator|(
name|unsigned
name|char
operator|*
operator|)
name|rgba8B
argument_list|,
operator|(
name|unsigned
name|char
operator|*
operator|)
name|rgba8D2
argument_list|)
expr_stmt|;
name|gimp_composite_context_init
argument_list|(
operator|&
name|generic_ctx
argument_list|,
name|GIMP_COMPOSITE_SUBTRACT
argument_list|,
name|GIMP_PIXELFORMAT_RGBA8
argument_list|,
name|GIMP_PIXELFORMAT_RGBA8
argument_list|,
name|GIMP_PIXELFORMAT_RGBA8
argument_list|,
name|GIMP_PIXELFORMAT_RGBA8
argument_list|,
name|n_pixels
argument_list|,
operator|(
name|unsigned
name|char
operator|*
operator|)
name|rgba8A
argument_list|,
operator|(
name|unsigned
name|char
operator|*
operator|)
name|rgba8B
argument_list|,
operator|(
name|unsigned
name|char
operator|*
operator|)
name|rgba8B
argument_list|,
operator|(
name|unsigned
name|char
operator|*
operator|)
name|rgba8D1
argument_list|)
expr_stmt|;
name|ft0
operator|=
name|gimp_composite_regression_time_function
argument_list|(
name|iterations
argument_list|,
name|gimp_composite_dispatch
argument_list|,
operator|&
name|generic_ctx
argument_list|)
expr_stmt|;
name|ft1
operator|=
name|gimp_composite_regression_time_function
argument_list|(
name|iterations
argument_list|,
name|gimp_composite_subtract_rgba8_rgba8_rgba8_sse2
argument_list|,
operator|&
name|special_ctx
argument_list|)
expr_stmt|;
if|if
condition|(
name|gimp_composite_regression_compare_contexts
argument_list|(
literal|"subtract"
argument_list|,
operator|&
name|generic_ctx
argument_list|,
operator|&
name|special_ctx
argument_list|)
condition|)
block|{
name|printf
argument_list|(
literal|"subtract failed\n"
argument_list|)
expr_stmt|;
return|return
operator|(
literal|1
operator|)
return|;
block|}
name|gimp_composite_regression_timer_report
argument_list|(
literal|"subtract"
argument_list|,
name|ft0
argument_list|,
name|ft1
argument_list|)
expr_stmt|;
name|gimp_composite_context_init
argument_list|(
operator|&
name|special_ctx
argument_list|,
name|GIMP_COMPOSITE_SWAP
argument_list|,
name|GIMP_PIXELFORMAT_RGBA8
argument_list|,
name|GIMP_PIXELFORMAT_RGBA8
argument_list|,
name|GIMP_PIXELFORMAT_RGBA8
argument_list|,
name|GIMP_PIXELFORMAT_RGBA8
argument_list|,
name|n_pixels
argument_list|,
operator|(
name|unsigned
name|char
operator|*
operator|)
name|rgba8A
argument_list|,
operator|(
name|unsigned
name|char
operator|*
operator|)
name|rgba8B
argument_list|,
operator|(
name|unsigned
name|char
operator|*
operator|)
name|rgba8B
argument_list|,
operator|(
name|unsigned
name|char
operator|*
operator|)
name|rgba8D2
argument_list|)
expr_stmt|;
name|gimp_composite_context_init
argument_list|(
operator|&
name|generic_ctx
argument_list|,
name|GIMP_COMPOSITE_SWAP
argument_list|,
name|GIMP_PIXELFORMAT_RGBA8
argument_list|,
name|GIMP_PIXELFORMAT_RGBA8
argument_list|,
name|GIMP_PIXELFORMAT_RGBA8
argument_list|,
name|GIMP_PIXELFORMAT_RGBA8
argument_list|,
name|n_pixels
argument_list|,
operator|(
name|unsigned
name|char
operator|*
operator|)
name|rgba8A
argument_list|,
operator|(
name|unsigned
name|char
operator|*
operator|)
name|rgba8B
argument_list|,
operator|(
name|unsigned
name|char
operator|*
operator|)
name|rgba8B
argument_list|,
operator|(
name|unsigned
name|char
operator|*
operator|)
name|rgba8D1
argument_list|)
expr_stmt|;
name|ft0
operator|=
name|gimp_composite_regression_time_function
argument_list|(
name|iterations
argument_list|,
name|gimp_composite_dispatch
argument_list|,
operator|&
name|generic_ctx
argument_list|)
expr_stmt|;
name|ft1
operator|=
name|gimp_composite_regression_time_function
argument_list|(
name|iterations
argument_list|,
name|gimp_composite_swap_rgba8_rgba8_rgba8_sse2
argument_list|,
operator|&
name|special_ctx
argument_list|)
expr_stmt|;
if|if
condition|(
name|gimp_composite_regression_compare_contexts
argument_list|(
literal|"swap"
argument_list|,
operator|&
name|generic_ctx
argument_list|,
operator|&
name|special_ctx
argument_list|)
condition|)
block|{
name|printf
argument_list|(
literal|"swap failed\n"
argument_list|)
expr_stmt|;
return|return
operator|(
literal|1
operator|)
return|;
block|}
name|gimp_composite_regression_timer_report
argument_list|(
literal|"swap"
argument_list|,
name|ft0
argument_list|,
name|ft1
argument_list|)
expr_stmt|;
endif|#
directive|endif
return|return
operator|(
literal|0
operator|)
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
name|putenv
argument_list|(
literal|"GIMP_COMPOSITE=0x1"
argument_list|)
expr_stmt|;
name|iterations
operator|=
literal|1
expr_stmt|;
name|n_pixels
operator|=
literal|1048593
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
name|printf
argument_list|(
literal|"Usage: gimp-composites-*-test [-i|--iterations n] [-n|--n-pixels n]"
argument_list|)
expr_stmt|;
name|exit
argument_list|(
literal|1
argument_list|)
expr_stmt|;
block|}
block|}
name|gimp_composite_generic_install
argument_list|()
expr_stmt|;
return|return
operator|(
name|gimp_composite_sse2_test
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

