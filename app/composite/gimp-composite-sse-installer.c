begin_unit|revision:0.9.5;language:C;cregit-version:0.0.1
begin_comment
comment|/* THIS FILE IS AUTOMATICALLY GENERATED.  DO NOT EDIT */
end_comment

begin_comment
comment|/* REGENERATE BY USING make-installer.py */
end_comment

begin_include
include|#
directive|include
file|"config.h"
end_include

begin_include
include|#
directive|include
file|<glib-object.h>
end_include

begin_include
include|#
directive|include
file|<stdlib.h>
end_include

begin_include
include|#
directive|include
file|<stdio.h>
end_include

begin_include
include|#
directive|include
file|"base/base-types.h"
end_include

begin_include
include|#
directive|include
file|"base/cpu-accel.h"
end_include

begin_include
include|#
directive|include
file|"gimp-composite.h"
end_include

begin_include
include|#
directive|include
file|"gimp-composite-sse.h"
end_include

begin_struct
DECL|struct|install_table
specifier|static
struct|struct
name|install_table
block|{
DECL|member|mode
name|GimpCompositeOperation
name|mode
decl_stmt|;
DECL|member|A
name|GimpPixelFormat
name|A
decl_stmt|;
DECL|member|B
name|GimpPixelFormat
name|B
decl_stmt|;
DECL|member|D
name|GimpPixelFormat
name|D
decl_stmt|;
DECL|member|function
name|void
function_decl|(
modifier|*
name|function
function_decl|)
parameter_list|(
name|GimpCompositeContext
modifier|*
parameter_list|)
function_decl|;
DECL|variable|_gimp_composite_sse
block|}
name|_gimp_composite_sse
index|[]
init|=
block|{
if|#
directive|if
name|defined
argument_list|(
name|COMPILE_SSE_IS_OKAY
argument_list|)
block|{
name|GIMP_COMPOSITE_MULTIPLY
block|,
name|GIMP_PIXELFORMAT_RGBA8
block|,
name|GIMP_PIXELFORMAT_RGBA8
block|,
name|GIMP_PIXELFORMAT_RGBA8
block|,
name|gimp_composite_multiply_rgba8_rgba8_rgba8_sse
block|}
block|,
block|{
name|GIMP_COMPOSITE_SCREEN
block|,
name|GIMP_PIXELFORMAT_RGBA8
block|,
name|GIMP_PIXELFORMAT_RGBA8
block|,
name|GIMP_PIXELFORMAT_RGBA8
block|,
name|gimp_composite_screen_rgba8_rgba8_rgba8_sse
block|}
block|,
block|{
name|GIMP_COMPOSITE_DIFFERENCE
block|,
name|GIMP_PIXELFORMAT_RGBA8
block|,
name|GIMP_PIXELFORMAT_RGBA8
block|,
name|GIMP_PIXELFORMAT_RGBA8
block|,
name|gimp_composite_difference_rgba8_rgba8_rgba8_sse
block|}
block|,
block|{
name|GIMP_COMPOSITE_ADDITION
block|,
name|GIMP_PIXELFORMAT_RGBA8
block|,
name|GIMP_PIXELFORMAT_RGBA8
block|,
name|GIMP_PIXELFORMAT_RGBA8
block|,
name|gimp_composite_addition_rgba8_rgba8_rgba8_sse
block|}
block|,
block|{
name|GIMP_COMPOSITE_SUBTRACT
block|,
name|GIMP_PIXELFORMAT_RGBA8
block|,
name|GIMP_PIXELFORMAT_RGBA8
block|,
name|GIMP_PIXELFORMAT_RGBA8
block|,
name|gimp_composite_subtract_rgba8_rgba8_rgba8_sse
block|}
block|,
block|{
name|GIMP_COMPOSITE_DARKEN
block|,
name|GIMP_PIXELFORMAT_RGBA8
block|,
name|GIMP_PIXELFORMAT_RGBA8
block|,
name|GIMP_PIXELFORMAT_RGBA8
block|,
name|gimp_composite_darken_rgba8_rgba8_rgba8_sse
block|}
block|,
block|{
name|GIMP_COMPOSITE_LIGHTEN
block|,
name|GIMP_PIXELFORMAT_RGBA8
block|,
name|GIMP_PIXELFORMAT_RGBA8
block|,
name|GIMP_PIXELFORMAT_RGBA8
block|,
name|gimp_composite_lighten_rgba8_rgba8_rgba8_sse
block|}
block|,
block|{
name|GIMP_COMPOSITE_GRAIN_EXTRACT
block|,
name|GIMP_PIXELFORMAT_RGBA8
block|,
name|GIMP_PIXELFORMAT_RGBA8
block|,
name|GIMP_PIXELFORMAT_RGBA8
block|,
name|gimp_composite_grain_extract_rgba8_rgba8_rgba8_sse
block|}
block|,
block|{
name|GIMP_COMPOSITE_GRAIN_MERGE
block|,
name|GIMP_PIXELFORMAT_RGBA8
block|,
name|GIMP_PIXELFORMAT_RGBA8
block|,
name|GIMP_PIXELFORMAT_RGBA8
block|,
name|gimp_composite_grain_merge_rgba8_rgba8_rgba8_sse
block|}
block|,
block|{
name|GIMP_COMPOSITE_SWAP
block|,
name|GIMP_PIXELFORMAT_RGBA8
block|,
name|GIMP_PIXELFORMAT_RGBA8
block|,
name|GIMP_PIXELFORMAT_RGBA8
block|,
name|gimp_composite_swap_rgba8_rgba8_rgba8_sse
block|}
block|,
block|{
name|GIMP_COMPOSITE_SCALE
block|,
name|GIMP_PIXELFORMAT_RGBA8
block|,
name|GIMP_PIXELFORMAT_RGBA8
block|,
name|GIMP_PIXELFORMAT_RGBA8
block|,
name|gimp_composite_scale_rgba8_rgba8_rgba8_sse
block|}
block|,
endif|#
directive|endif
block|{
literal|0
block|,
literal|0
block|,
literal|0
block|,
literal|0
block|,
name|NULL
block|}
block|}
struct|;
end_struct

begin_function
name|gboolean
DECL|function|gimp_composite_sse_install (void)
name|gimp_composite_sse_install
parameter_list|(
name|void
parameter_list|)
block|{
specifier|static
name|struct
name|install_table
modifier|*
name|t
init|=
name|_gimp_composite_sse
decl_stmt|;
if|if
condition|(
name|gimp_composite_sse_init
argument_list|()
condition|)
block|{
for|for
control|(
name|t
operator|=
operator|&
name|_gimp_composite_sse
index|[
literal|0
index|]
init|;
name|t
operator|->
name|function
operator|!=
name|NULL
condition|;
name|t
operator|++
control|)
block|{
name|gimp_composite_function
index|[
name|t
operator|->
name|mode
index|]
index|[
name|t
operator|->
name|A
index|]
index|[
name|t
operator|->
name|B
index|]
index|[
name|t
operator|->
name|D
index|]
operator|=
name|t
operator|->
name|function
expr_stmt|;
block|}
return|return
operator|(
name|TRUE
operator|)
return|;
block|}
return|return
operator|(
name|FALSE
operator|)
return|;
block|}
end_function

begin_function
name|gboolean
DECL|function|gimp_composite_sse_init (void)
name|gimp_composite_sse_init
parameter_list|(
name|void
parameter_list|)
block|{
if|#
directive|if
name|defined
argument_list|(
name|COMPILE_SSE_IS_OKAY
argument_list|)
name|guint32
name|cpu
init|=
name|cpu_accel
argument_list|()
decl_stmt|;
if|if
condition|(
name|cpu
operator|&
name|CPU_ACCEL_X86_SSE
operator|||
name|cpu
operator|&
name|CPU_ACCEL_X86_MMXEXT
condition|)
block|{
return|return
operator|(
name|TRUE
operator|)
return|;
block|}
endif|#
directive|endif
return|return
operator|(
name|FALSE
operator|)
return|;
block|}
end_function

end_unit

