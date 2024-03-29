begin_unit|revision:0.9.5;language:C;cregit-version:0.0.1
begin_comment
comment|/* GIMP - The GNU Image Manipulation Program  * Copyright (C) 1995 Spencer Kimball and Peter Mattis  *  * kernelgen -- Copyright (C) 2000 Sven Neumann<sven@gimp.org>  *  *    Simple hack to create brush subsampling kernels.  If you want to  *    play with it, change some of the #defines at the top and copy  *    the output to app/paint/gimpbrushcore-kernels.h.  *  * This program is free software: you can redistribute it and/or modify  * it under the terms of the GNU General Public License as published by  * the Free Software Foundation; either version 3 of the License, or  * (at your option) any later version.  *  * This program is distributed in the hope that it will be useful,  * but WITHOUT ANY WARRANTY; without even the implied warranty of  * MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the  * GNU General Public License for more details.  *  * You should have received a copy of the GNU General Public License  * along with this program.  If not, see<https://www.gnu.org/licenses/>.  */
end_comment

begin_include
include|#
directive|include
file|<math.h>
end_include

begin_include
include|#
directive|include
file|<stdio.h>
end_include

begin_include
include|#
directive|include
file|<string.h>
end_include

begin_define
DECL|macro|STEPS
define|#
directive|define
name|STEPS
value|64
end_define

begin_define
DECL|macro|KERNEL_WIDTH
define|#
directive|define
name|KERNEL_WIDTH
value|3
end_define

begin_comment
DECL|macro|KERNEL_WIDTH
comment|/*  changing these makes no sense  */
end_comment

begin_define
DECL|macro|KERNEL_HEIGHT
define|#
directive|define
name|KERNEL_HEIGHT
value|3
end_define

begin_comment
DECL|macro|KERNEL_HEIGHT
comment|/*  changing these makes no sense  */
end_comment

begin_define
DECL|macro|KERNEL_SUM
define|#
directive|define
name|KERNEL_SUM
value|256
end_define

begin_define
DECL|macro|SUBSAMPLE
define|#
directive|define
name|SUBSAMPLE
value|4
end_define

begin_define
DECL|macro|THRESHOLD
define|#
directive|define
name|THRESHOLD
value|0.25
end_define

begin_comment
DECL|macro|THRESHOLD
comment|/*  try to change this one         */
end_comment

begin_define
DECL|macro|SQR (x)
define|#
directive|define
name|SQR
parameter_list|(
name|x
parameter_list|)
value|((x) * (x))
end_define

begin_function
specifier|static
name|void
DECL|function|create_kernel (double x,double y)
name|create_kernel
parameter_list|(
name|double
name|x
parameter_list|,
name|double
name|y
parameter_list|)
block|{
name|double
name|value
index|[
name|KERNEL_WIDTH
index|]
index|[
name|KERNEL_HEIGHT
index|]
decl_stmt|;
name|double
name|dist_x
decl_stmt|;
name|double
name|dist_y
decl_stmt|;
name|double
name|sum
decl_stmt|;
name|double
name|w
decl_stmt|;
name|int
name|i
decl_stmt|,
name|j
decl_stmt|;
name|memset
argument_list|(
name|value
argument_list|,
literal|0
argument_list|,
name|KERNEL_WIDTH
operator|*
name|KERNEL_HEIGHT
operator|*
sizeof|sizeof
argument_list|(
name|double
argument_list|)
argument_list|)
expr_stmt|;
name|sum
operator|=
literal|0.0
expr_stmt|;
name|x
operator|+=
literal|1.0
expr_stmt|;
name|y
operator|+=
literal|1.0
expr_stmt|;
for|for
control|(
name|j
operator|=
literal|0
init|;
name|j
operator|<
name|STEPS
operator|*
name|KERNEL_HEIGHT
condition|;
name|j
operator|++
control|)
block|{
name|dist_y
operator|=
name|y
operator|-
operator|(
operator|(
operator|(
name|double
operator|)
name|j
operator|+
literal|0.5
operator|)
operator|/
operator|(
name|double
operator|)
name|STEPS
operator|)
expr_stmt|;
for|for
control|(
name|i
operator|=
literal|0
init|;
name|i
operator|<
name|STEPS
operator|*
name|KERNEL_WIDTH
condition|;
name|i
operator|++
control|)
block|{
name|dist_x
operator|=
name|x
operator|-
operator|(
operator|(
operator|(
name|double
operator|)
name|i
operator|+
literal|0.5
operator|)
operator|/
operator|(
name|double
operator|)
name|STEPS
operator|)
expr_stmt|;
comment|/*  I've tried to use a gauss function here instead of a               threshold, but the result was not that impressive.    */
name|w
operator|=
operator|(
name|SQR
argument_list|(
name|dist_x
argument_list|)
operator|+
name|SQR
argument_list|(
name|dist_y
argument_list|)
operator|)
operator|<
name|THRESHOLD
condition|?
literal|1.0
else|:
literal|0.0
expr_stmt|;
name|value
index|[
name|i
operator|/
name|STEPS
index|]
index|[
name|j
operator|/
name|STEPS
index|]
operator|+=
name|w
expr_stmt|;
name|sum
operator|+=
name|w
expr_stmt|;
block|}
block|}
for|for
control|(
name|j
operator|=
literal|0
init|;
name|j
operator|<
name|KERNEL_HEIGHT
condition|;
name|j
operator|++
control|)
block|{
for|for
control|(
name|i
operator|=
literal|0
init|;
name|i
operator|<
name|KERNEL_WIDTH
condition|;
name|i
operator|++
control|)
block|{
name|w
operator|=
operator|(
name|double
operator|)
name|KERNEL_SUM
operator|*
name|value
index|[
name|i
index|]
index|[
name|j
index|]
operator|/
name|sum
expr_stmt|;
name|printf
argument_list|(
literal|" %3d,"
argument_list|,
call|(
name|int
call|)
argument_list|(
name|w
operator|+
literal|0.5
argument_list|)
argument_list|)
expr_stmt|;
block|}
block|}
block|}
end_function

begin_function
name|int
DECL|function|main (int argc,char ** argv)
name|main
parameter_list|(
name|int
name|argc
parameter_list|,
name|char
modifier|*
modifier|*
name|argv
parameter_list|)
block|{
name|int
name|i
decl_stmt|,
name|j
decl_stmt|;
name|double
name|x
decl_stmt|,
name|y
decl_stmt|;
name|printf
argument_list|(
literal|"/* gimpbrushcore-kernels.h\n"
literal|" *\n"
literal|" *   This file was generated using kernelgen as found in the tools dir.\n"
argument_list|)
expr_stmt|;
name|printf
argument_list|(
literal|" *   (threshold = %g)\n"
argument_list|,
name|THRESHOLD
argument_list|)
expr_stmt|;
name|printf
argument_list|(
literal|" */\n\n"
argument_list|)
expr_stmt|;
name|printf
argument_list|(
literal|"#ifndef __GIMP_BRUSH_CORE_KERNELS_H__\n"
argument_list|)
expr_stmt|;
name|printf
argument_list|(
literal|"#define __GIMP_BRUSH_CORE_KERNELS_H__\n\n"
argument_list|)
expr_stmt|;
name|printf
argument_list|(
literal|"#define KERNEL_WIDTH     %d\n"
argument_list|,
name|KERNEL_WIDTH
argument_list|)
expr_stmt|;
name|printf
argument_list|(
literal|"#define KERNEL_HEIGHT    %d\n"
argument_list|,
name|KERNEL_HEIGHT
argument_list|)
expr_stmt|;
name|printf
argument_list|(
literal|"#define KERNEL_SUBSAMPLE %d\n"
argument_list|,
name|SUBSAMPLE
argument_list|)
expr_stmt|;
name|printf
argument_list|(
literal|"#define KERNEL_SUM       %d\n"
argument_list|,
name|KERNEL_SUM
argument_list|)
expr_stmt|;
name|printf
argument_list|(
literal|"\n\n"
argument_list|)
expr_stmt|;
name|printf
argument_list|(
literal|"/*  Brush pixel subsampling kernels  */\n"
argument_list|)
expr_stmt|;
name|printf
argument_list|(
literal|"static const int subsample[%d][%d][%d] =\n{\n"
argument_list|,
name|SUBSAMPLE
operator|+
literal|1
argument_list|,
name|SUBSAMPLE
operator|+
literal|1
argument_list|,
name|KERNEL_WIDTH
operator|*
name|KERNEL_HEIGHT
argument_list|)
expr_stmt|;
for|for
control|(
name|j
operator|=
literal|0
init|;
name|j
operator|<=
name|SUBSAMPLE
condition|;
name|j
operator|++
control|)
block|{
name|y
operator|=
operator|(
name|double
operator|)
name|j
operator|/
operator|(
name|double
operator|)
name|SUBSAMPLE
expr_stmt|;
name|printf
argument_list|(
literal|"  {\n"
argument_list|)
expr_stmt|;
for|for
control|(
name|i
operator|=
literal|0
init|;
name|i
operator|<=
name|SUBSAMPLE
condition|;
name|i
operator|++
control|)
block|{
name|x
operator|=
operator|(
name|double
operator|)
name|i
operator|/
operator|(
name|double
operator|)
name|SUBSAMPLE
expr_stmt|;
name|printf
argument_list|(
literal|"    {"
argument_list|)
expr_stmt|;
name|create_kernel
argument_list|(
name|x
argument_list|,
name|y
argument_list|)
expr_stmt|;
name|printf
argument_list|(
literal|" }%s"
argument_list|,
name|i
operator|<
name|SUBSAMPLE
condition|?
literal|",\n"
else|:
literal|"\n"
argument_list|)
expr_stmt|;
block|}
name|printf
argument_list|(
literal|"  }%s"
argument_list|,
name|j
operator|<
name|SUBSAMPLE
condition|?
literal|",\n"
else|:
literal|"\n"
argument_list|)
expr_stmt|;
block|}
name|printf
argument_list|(
literal|"};\n\n"
argument_list|)
expr_stmt|;
name|printf
argument_list|(
literal|"#endif /* __GIMP_BRUSH_CORE_KERNELS_H__ */\n"
argument_list|)
expr_stmt|;
return|return
literal|0
return|;
block|}
end_function

end_unit

