begin_unit|revision:0.9.5;language:C;cregit-version:0.0.1
begin_comment
comment|/* The GIMP -- an image manipulation program  * Copyright (C) 1995 Spencer Kimball and Peter Mattis  *  * gimplut.c: Copyright (C) 1999 Jay Cox<jaycox@earthlink.net>  *  * This program is free software; you can redistribute it and/or modify  * it under the terms of the GNU General Public License as published by  * the Free Software Foundation; either version 2 of the License, or  * (at your option) any later version.  *  * This program is distributed in the hope that it will be useful,  * but WITHOUT ANY WARRANTY; without even the implied warranty of  * MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the  * GNU General Public License for more details.  *  * You should have received a copy of the GNU General Public License  * along with this program; if not, write to the Free Software  * Foundation, Inc., 59 Temple Place - Suite 330, Boston, MA 02111-1307, USA.  */
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
file|<gtk/gtk.h>
end_include

begin_include
include|#
directive|include
file|"apptypes.h"
end_include

begin_include
include|#
directive|include
file|"gimplutP.h"
end_include

begin_include
include|#
directive|include
file|"gimplut.h"
end_include

begin_function
name|GimpLut
modifier|*
DECL|function|gimp_lut_new ()
name|gimp_lut_new
parameter_list|()
block|{
name|GimpLut
modifier|*
name|lut
decl_stmt|;
name|lut
operator|=
name|g_new
argument_list|(
name|GimpLut
argument_list|,
literal|1
argument_list|)
expr_stmt|;
name|lut
operator|->
name|luts
operator|=
name|NULL
expr_stmt|;
name|lut
operator|->
name|nchannels
operator|=
literal|0
expr_stmt|;
return|return
name|lut
return|;
block|}
end_function

begin_function
name|void
DECL|function|gimp_lut_free (GimpLut * lut)
name|gimp_lut_free
parameter_list|(
name|GimpLut
modifier|*
name|lut
parameter_list|)
block|{
name|int
name|i
decl_stmt|;
for|for
control|(
name|i
operator|=
literal|0
init|;
name|i
operator|<
name|lut
operator|->
name|nchannels
condition|;
name|i
operator|++
control|)
name|g_free
argument_list|(
name|lut
operator|->
name|luts
index|[
name|i
index|]
argument_list|)
expr_stmt|;
if|if
condition|(
name|lut
operator|->
name|luts
condition|)
name|g_free
argument_list|(
name|lut
operator|->
name|luts
argument_list|)
expr_stmt|;
block|}
end_function

begin_function
name|void
DECL|function|gimp_lut_setup (GimpLut * lut,GimpLutFunc func,void * user_data,int nchannels)
name|gimp_lut_setup
parameter_list|(
name|GimpLut
modifier|*
name|lut
parameter_list|,
name|GimpLutFunc
name|func
parameter_list|,
name|void
modifier|*
name|user_data
parameter_list|,
name|int
name|nchannels
parameter_list|)
block|{
name|int
name|i
decl_stmt|,
name|v
decl_stmt|;
name|double
name|val
decl_stmt|;
if|if
condition|(
name|lut
operator|->
name|luts
condition|)
block|{
for|for
control|(
name|i
operator|=
literal|0
init|;
name|i
operator|<
name|lut
operator|->
name|nchannels
condition|;
name|i
operator|++
control|)
name|g_free
argument_list|(
name|lut
operator|->
name|luts
index|[
name|i
index|]
argument_list|)
expr_stmt|;
name|g_free
argument_list|(
name|lut
operator|->
name|luts
argument_list|)
expr_stmt|;
block|}
name|lut
operator|->
name|nchannels
operator|=
name|nchannels
expr_stmt|;
name|lut
operator|->
name|luts
operator|=
name|g_new
argument_list|(
argument|unsigned char*
argument_list|,
argument|lut->nchannels
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
name|lut
operator|->
name|nchannels
condition|;
name|i
operator|++
control|)
block|{
name|lut
operator|->
name|luts
index|[
name|i
index|]
operator|=
name|g_new
argument_list|(
argument|unsigned char
argument_list|,
literal|256
argument_list|)
expr_stmt|;
for|for
control|(
name|v
operator|=
literal|0
init|;
name|v
operator|<
literal|256
condition|;
name|v
operator|++
control|)
block|{
comment|/* to add gamma correction use func(v ^ g) ^ 1/g instead. */
name|val
operator|=
literal|255.0
operator|*
name|func
argument_list|(
name|user_data
argument_list|,
name|lut
operator|->
name|nchannels
argument_list|,
name|i
argument_list|,
name|v
operator|/
literal|255.0
argument_list|)
operator|+
literal|0.5
expr_stmt|;
if|if
condition|(
name|val
operator|<
literal|0.0
condition|)
name|lut
operator|->
name|luts
index|[
name|i
index|]
index|[
name|v
index|]
operator|=
literal|0
expr_stmt|;
elseif|else
if|if
condition|(
name|val
operator|>=
literal|255.0
condition|)
name|lut
operator|->
name|luts
index|[
name|i
index|]
index|[
name|v
index|]
operator|=
literal|255
expr_stmt|;
else|else
name|lut
operator|->
name|luts
index|[
name|i
index|]
index|[
name|v
index|]
operator|=
name|val
expr_stmt|;
block|}
block|}
block|}
end_function

begin_function
name|void
DECL|function|gimp_lut_setup_exact (GimpLut * lut,GimpLutFunc func,void * user_data,int nchannels)
name|gimp_lut_setup_exact
parameter_list|(
name|GimpLut
modifier|*
name|lut
parameter_list|,
name|GimpLutFunc
name|func
parameter_list|,
name|void
modifier|*
name|user_data
parameter_list|,
name|int
name|nchannels
parameter_list|)
block|{
name|gimp_lut_setup
argument_list|(
name|lut
argument_list|,
name|func
argument_list|,
name|user_data
argument_list|,
name|nchannels
argument_list|)
expr_stmt|;
block|}
end_function

begin_function
name|void
DECL|function|gimp_lut_process (GimpLut * lut,PixelRegion * srcPR,PixelRegion * destPR)
name|gimp_lut_process
parameter_list|(
name|GimpLut
modifier|*
name|lut
parameter_list|,
name|PixelRegion
modifier|*
name|srcPR
parameter_list|,
name|PixelRegion
modifier|*
name|destPR
parameter_list|)
block|{
name|int
name|h
decl_stmt|,
name|width
decl_stmt|,
name|src_r_i
decl_stmt|,
name|dest_r_i
decl_stmt|;
name|unsigned
name|char
modifier|*
name|src
decl_stmt|,
modifier|*
name|dest
decl_stmt|;
name|unsigned
name|char
modifier|*
name|lut0
init|=
name|NULL
decl_stmt|,
modifier|*
name|lut1
init|=
name|NULL
decl_stmt|,
modifier|*
name|lut2
init|=
name|NULL
decl_stmt|,
modifier|*
name|lut3
init|=
name|NULL
decl_stmt|;
if|if
condition|(
name|lut
operator|->
name|nchannels
operator|>
literal|0
condition|)
name|lut0
operator|=
name|lut
operator|->
name|luts
index|[
literal|0
index|]
expr_stmt|;
if|if
condition|(
name|lut
operator|->
name|nchannels
operator|>
literal|1
condition|)
name|lut1
operator|=
name|lut
operator|->
name|luts
index|[
literal|1
index|]
expr_stmt|;
if|if
condition|(
name|lut
operator|->
name|nchannels
operator|>
literal|2
condition|)
name|lut2
operator|=
name|lut
operator|->
name|luts
index|[
literal|2
index|]
expr_stmt|;
if|if
condition|(
name|lut
operator|->
name|nchannels
operator|>
literal|3
condition|)
name|lut3
operator|=
name|lut
operator|->
name|luts
index|[
literal|3
index|]
expr_stmt|;
name|h
operator|=
name|srcPR
operator|->
name|h
expr_stmt|;
name|src
operator|=
name|srcPR
operator|->
name|data
expr_stmt|;
name|dest
operator|=
name|destPR
operator|->
name|data
expr_stmt|;
name|width
operator|=
name|srcPR
operator|->
name|w
expr_stmt|;
name|src_r_i
operator|=
name|srcPR
operator|->
name|rowstride
operator|-
operator|(
name|srcPR
operator|->
name|bytes
operator|*
name|srcPR
operator|->
name|w
operator|)
expr_stmt|;
name|dest_r_i
operator|=
name|destPR
operator|->
name|rowstride
operator|-
operator|(
name|destPR
operator|->
name|bytes
operator|*
name|srcPR
operator|->
name|w
operator|)
expr_stmt|;
if|if
condition|(
name|src_r_i
operator|==
literal|0
operator|&&
name|dest_r_i
operator|==
literal|0
condition|)
block|{
name|width
operator|*=
name|h
expr_stmt|;
name|h
operator|=
literal|1
expr_stmt|;
block|}
while|while
condition|(
name|h
operator|--
condition|)
block|{
switch|switch
condition|(
name|lut
operator|->
name|nchannels
condition|)
block|{
case|case
literal|1
case|:
while|while
condition|(
name|width
operator|--
condition|)
block|{
operator|*
name|dest
operator|=
name|lut0
index|[
operator|*
name|src
index|]
expr_stmt|;
name|src
operator|++
expr_stmt|;
name|dest
operator|++
expr_stmt|;
block|}
break|break;
case|case
literal|2
case|:
while|while
condition|(
name|width
operator|--
condition|)
block|{
name|dest
index|[
literal|0
index|]
operator|=
name|lut0
index|[
name|src
index|[
literal|0
index|]
index|]
expr_stmt|;
name|dest
index|[
literal|1
index|]
operator|=
name|lut1
index|[
name|src
index|[
literal|1
index|]
index|]
expr_stmt|;
name|src
operator|+=
literal|2
expr_stmt|;
name|dest
operator|+=
literal|2
expr_stmt|;
block|}
break|break;
case|case
literal|3
case|:
while|while
condition|(
name|width
operator|--
condition|)
block|{
name|dest
index|[
literal|0
index|]
operator|=
name|lut0
index|[
name|src
index|[
literal|0
index|]
index|]
expr_stmt|;
name|dest
index|[
literal|1
index|]
operator|=
name|lut1
index|[
name|src
index|[
literal|1
index|]
index|]
expr_stmt|;
name|dest
index|[
literal|2
index|]
operator|=
name|lut2
index|[
name|src
index|[
literal|2
index|]
index|]
expr_stmt|;
name|src
operator|+=
literal|3
expr_stmt|;
name|dest
operator|+=
literal|3
expr_stmt|;
block|}
break|break;
case|case
literal|4
case|:
while|while
condition|(
name|width
operator|--
condition|)
block|{
name|dest
index|[
literal|0
index|]
operator|=
name|lut0
index|[
name|src
index|[
literal|0
index|]
index|]
expr_stmt|;
name|dest
index|[
literal|1
index|]
operator|=
name|lut1
index|[
name|src
index|[
literal|1
index|]
index|]
expr_stmt|;
name|dest
index|[
literal|2
index|]
operator|=
name|lut2
index|[
name|src
index|[
literal|2
index|]
index|]
expr_stmt|;
name|dest
index|[
literal|3
index|]
operator|=
name|lut3
index|[
name|src
index|[
literal|3
index|]
index|]
expr_stmt|;
name|src
operator|+=
literal|4
expr_stmt|;
name|dest
operator|+=
literal|4
expr_stmt|;
block|}
break|break;
default|default:
name|fprintf
argument_list|(
name|stderr
argument_list|,
literal|"gimplut: Error: nchannels = %d\n"
argument_list|,
name|lut
operator|->
name|nchannels
argument_list|)
expr_stmt|;
block|}
name|width
operator|=
name|srcPR
operator|->
name|w
expr_stmt|;
name|src
operator|+=
name|src_r_i
expr_stmt|;
name|dest
operator|+=
name|dest_r_i
expr_stmt|;
block|}
block|}
end_function

begin_function
name|void
DECL|function|gimp_lut_process_inline (GimpLut * lut,PixelRegion * srcPR)
name|gimp_lut_process_inline
parameter_list|(
name|GimpLut
modifier|*
name|lut
parameter_list|,
name|PixelRegion
modifier|*
name|srcPR
parameter_list|)
block|{
name|int
name|h
decl_stmt|,
name|width
decl_stmt|,
name|src_r_i
decl_stmt|;
name|unsigned
name|char
modifier|*
name|src
decl_stmt|;
name|unsigned
name|char
modifier|*
name|lut0
init|=
name|NULL
decl_stmt|,
modifier|*
name|lut1
init|=
name|NULL
decl_stmt|,
modifier|*
name|lut2
init|=
name|NULL
decl_stmt|,
modifier|*
name|lut3
init|=
name|NULL
decl_stmt|;
if|if
condition|(
name|lut
operator|->
name|nchannels
operator|>
literal|0
condition|)
name|lut0
operator|=
name|lut
operator|->
name|luts
index|[
literal|0
index|]
expr_stmt|;
if|if
condition|(
name|lut
operator|->
name|nchannels
operator|>
literal|1
condition|)
name|lut1
operator|=
name|lut
operator|->
name|luts
index|[
literal|1
index|]
expr_stmt|;
if|if
condition|(
name|lut
operator|->
name|nchannels
operator|>
literal|2
condition|)
name|lut2
operator|=
name|lut
operator|->
name|luts
index|[
literal|2
index|]
expr_stmt|;
if|if
condition|(
name|lut
operator|->
name|nchannels
operator|>
literal|3
condition|)
name|lut3
operator|=
name|lut
operator|->
name|luts
index|[
literal|3
index|]
expr_stmt|;
name|h
operator|=
name|srcPR
operator|->
name|h
expr_stmt|;
name|src
operator|=
name|srcPR
operator|->
name|data
expr_stmt|;
name|width
operator|=
name|srcPR
operator|->
name|w
expr_stmt|;
name|src_r_i
operator|=
name|srcPR
operator|->
name|rowstride
operator|-
operator|(
name|srcPR
operator|->
name|bytes
operator|*
name|srcPR
operator|->
name|w
operator|)
expr_stmt|;
if|if
condition|(
name|src_r_i
operator|==
literal|0
condition|)
block|{
name|width
operator|*=
name|h
expr_stmt|;
name|h
operator|=
literal|1
expr_stmt|;
block|}
while|while
condition|(
name|h
operator|--
condition|)
block|{
switch|switch
condition|(
name|lut
operator|->
name|nchannels
condition|)
block|{
case|case
literal|1
case|:
while|while
condition|(
name|width
operator|--
condition|)
block|{
operator|*
name|src
operator|=
name|lut0
index|[
operator|*
name|src
index|]
expr_stmt|;
name|src
operator|++
expr_stmt|;
block|}
break|break;
case|case
literal|2
case|:
while|while
condition|(
name|width
operator|--
condition|)
block|{
name|src
index|[
literal|0
index|]
operator|=
name|lut0
index|[
name|src
index|[
literal|0
index|]
index|]
expr_stmt|;
name|src
index|[
literal|1
index|]
operator|=
name|lut1
index|[
name|src
index|[
literal|1
index|]
index|]
expr_stmt|;
name|src
operator|+=
literal|2
expr_stmt|;
block|}
break|break;
case|case
literal|3
case|:
while|while
condition|(
name|width
operator|--
condition|)
block|{
name|src
index|[
literal|0
index|]
operator|=
name|lut0
index|[
name|src
index|[
literal|0
index|]
index|]
expr_stmt|;
name|src
index|[
literal|1
index|]
operator|=
name|lut1
index|[
name|src
index|[
literal|1
index|]
index|]
expr_stmt|;
name|src
index|[
literal|2
index|]
operator|=
name|lut2
index|[
name|src
index|[
literal|2
index|]
index|]
expr_stmt|;
name|src
operator|+=
literal|3
expr_stmt|;
block|}
break|break;
case|case
literal|4
case|:
while|while
condition|(
name|width
operator|--
condition|)
block|{
name|src
index|[
literal|0
index|]
operator|=
name|lut0
index|[
name|src
index|[
literal|0
index|]
index|]
expr_stmt|;
name|src
index|[
literal|1
index|]
operator|=
name|lut1
index|[
name|src
index|[
literal|1
index|]
index|]
expr_stmt|;
name|src
index|[
literal|2
index|]
operator|=
name|lut2
index|[
name|src
index|[
literal|2
index|]
index|]
expr_stmt|;
name|src
index|[
literal|3
index|]
operator|=
name|lut3
index|[
name|src
index|[
literal|3
index|]
index|]
expr_stmt|;
name|src
operator|+=
literal|4
expr_stmt|;
block|}
break|break;
default|default:
name|fprintf
argument_list|(
name|stderr
argument_list|,
literal|"gimplut: Error: nchannels = %d\n"
argument_list|,
name|lut
operator|->
name|nchannels
argument_list|)
expr_stmt|;
block|}
name|width
operator|=
name|srcPR
operator|->
name|w
expr_stmt|;
name|src
operator|+=
name|src_r_i
expr_stmt|;
block|}
block|}
end_function

begin_function
name|void
DECL|function|gimp_lut_process_2 (PixelRegion * srcPR,PixelRegion * destPR,GimpLut * lut)
name|gimp_lut_process_2
parameter_list|(
name|PixelRegion
modifier|*
name|srcPR
parameter_list|,
name|PixelRegion
modifier|*
name|destPR
parameter_list|,
name|GimpLut
modifier|*
name|lut
parameter_list|)
block|{
name|gimp_lut_process
argument_list|(
name|lut
argument_list|,
name|srcPR
argument_list|,
name|destPR
argument_list|)
expr_stmt|;
block|}
end_function

end_unit

