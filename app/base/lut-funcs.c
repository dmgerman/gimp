begin_unit|revision:0.9.5;language:C;cregit-version:0.0.1
begin_comment
comment|/* The GIMP -- an image manipulation program  * Copyright (C) 1995 Spencer Kimball and Peter Mattis  *  * This program is free software; you can redistribute it and/or modify  * it under the terms of the GNU General Public License as published by  * the Free Software Foundation; either version 2 of the License, or  * (at your option) any later version.  *  * This program is distributed in the hope that it will be useful,  * but WITHOUT ANY WARRANTY; without even the implied warranty of  * MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the  * GNU General Public License for more details.  *  * You should have received a copy of the GNU General Public License  * along with this program; if not, write to the Free Software  * Foundation, Inc., 59 Temple Place - Suite 330, Boston, MA 02111-1307, USA.  */
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
file|<glib.h>
end_include

begin_include
include|#
directive|include
file|"appenv.h"
end_include

begin_include
include|#
directive|include
file|"gimplut.h"
end_include

begin_include
include|#
directive|include
file|"gimphistogram.h"
end_include

begin_include
include|#
directive|include
file|"libgimp/gimpmath.h"
end_include

begin_comment
comment|/* ---------- Brightness/Contrast -----------*/
end_comment

begin_typedef
DECL|struct|B_C_struct
typedef|typedef
struct|struct
name|B_C_struct
block|{
DECL|member|brightness
name|double
name|brightness
decl_stmt|;
DECL|member|contrast
name|double
name|contrast
decl_stmt|;
DECL|typedef|B_C_struct
block|}
name|B_C_struct
typedef|;
end_typedef

begin_function
specifier|static
name|float
DECL|function|brightness_contrast_lut_func (B_C_struct * data,int nchannels,int channel,float value)
name|brightness_contrast_lut_func
parameter_list|(
name|B_C_struct
modifier|*
name|data
parameter_list|,
name|int
name|nchannels
parameter_list|,
name|int
name|channel
parameter_list|,
name|float
name|value
parameter_list|)
block|{
name|float
name|nvalue
decl_stmt|;
name|double
name|power
decl_stmt|;
comment|/* return the original value for the alpha channel */
if|if
condition|(
operator|(
name|nchannels
operator|==
literal|2
operator|||
name|nchannels
operator|==
literal|4
operator|)
operator|&&
name|channel
operator|==
name|nchannels
operator|-
literal|1
condition|)
return|return
name|value
return|;
comment|/* apply brightness */
if|if
condition|(
name|data
operator|->
name|brightness
operator|<
literal|0.0
condition|)
name|value
operator|=
name|value
operator|*
operator|(
literal|1.0
operator|+
name|data
operator|->
name|brightness
operator|)
expr_stmt|;
else|else
name|value
operator|=
name|value
operator|+
operator|(
operator|(
literal|1.0
operator|-
name|value
operator|)
operator|*
name|data
operator|->
name|brightness
operator|)
expr_stmt|;
comment|/* apply contrast */
if|if
condition|(
name|data
operator|->
name|contrast
operator|<
literal|0.0
condition|)
block|{
if|if
condition|(
name|value
operator|>
literal|0.5
condition|)
name|nvalue
operator|=
literal|1.0
operator|-
name|value
expr_stmt|;
else|else
name|nvalue
operator|=
name|value
expr_stmt|;
if|if
condition|(
name|nvalue
operator|<
literal|0.0
condition|)
name|nvalue
operator|=
literal|0.0
expr_stmt|;
name|nvalue
operator|=
literal|0.5
operator|*
name|pow
argument_list|(
name|nvalue
operator|*
literal|2.0
argument_list|,
call|(
name|double
call|)
argument_list|(
literal|1.0
operator|+
name|data
operator|->
name|contrast
argument_list|)
argument_list|)
expr_stmt|;
if|if
condition|(
name|value
operator|>
literal|0.5
condition|)
name|value
operator|=
literal|1.0
operator|-
name|nvalue
expr_stmt|;
else|else
name|value
operator|=
name|nvalue
expr_stmt|;
block|}
else|else
block|{
if|if
condition|(
name|value
operator|>
literal|0.5
condition|)
name|nvalue
operator|=
literal|1.0
operator|-
name|value
expr_stmt|;
else|else
name|nvalue
operator|=
name|value
expr_stmt|;
if|if
condition|(
name|nvalue
operator|<
literal|0.0
condition|)
name|nvalue
operator|=
literal|0.0
expr_stmt|;
name|power
operator|=
operator|(
name|data
operator|->
name|contrast
operator|==
literal|1.0
operator|)
condition|?
literal|127
else|:
literal|1.0
operator|/
operator|(
literal|1.0
operator|-
name|data
operator|->
name|contrast
operator|)
expr_stmt|;
name|nvalue
operator|=
literal|0.5
operator|*
name|pow
argument_list|(
literal|2.0
operator|*
name|nvalue
argument_list|,
name|power
argument_list|)
expr_stmt|;
if|if
condition|(
name|value
operator|>
literal|0.5
condition|)
name|value
operator|=
literal|1.0
operator|-
name|nvalue
expr_stmt|;
else|else
name|value
operator|=
name|nvalue
expr_stmt|;
block|}
return|return
name|value
return|;
block|}
end_function

begin_function
name|void
DECL|function|brightness_contrast_lut_setup (GimpLut * lut,double brightness,double contrast,int nchannels)
name|brightness_contrast_lut_setup
parameter_list|(
name|GimpLut
modifier|*
name|lut
parameter_list|,
name|double
name|brightness
parameter_list|,
name|double
name|contrast
parameter_list|,
name|int
name|nchannels
parameter_list|)
block|{
name|B_C_struct
name|data
decl_stmt|;
name|data
operator|.
name|brightness
operator|=
name|brightness
expr_stmt|;
name|data
operator|.
name|contrast
operator|=
name|contrast
expr_stmt|;
name|gimp_lut_setup
argument_list|(
name|lut
argument_list|,
operator|(
name|GimpLutFunc
operator|)
name|brightness_contrast_lut_func
argument_list|,
operator|(
name|void
operator|*
operator|)
operator|&
name|data
argument_list|,
name|nchannels
argument_list|)
expr_stmt|;
block|}
end_function

begin_function
name|GimpLut
modifier|*
DECL|function|brightness_contrast_lut_new (double brightness,double contrast,int nchannels)
name|brightness_contrast_lut_new
parameter_list|(
name|double
name|brightness
parameter_list|,
name|double
name|contrast
parameter_list|,
name|int
name|nchannels
parameter_list|)
block|{
name|GimpLut
modifier|*
name|lut
decl_stmt|;
name|lut
operator|=
name|gimp_lut_new
argument_list|()
expr_stmt|;
name|brightness_contrast_lut_setup
argument_list|(
name|lut
argument_list|,
name|brightness
argument_list|,
name|contrast
argument_list|,
name|nchannels
argument_list|)
expr_stmt|;
return|return
name|lut
return|;
block|}
end_function

begin_comment
comment|/* ---------------- invert ------------------ */
end_comment

begin_function
specifier|static
name|float
DECL|function|invert_lut_func (void * unused,int nchannels,int channel,float value)
name|invert_lut_func
parameter_list|(
name|void
modifier|*
name|unused
parameter_list|,
name|int
name|nchannels
parameter_list|,
name|int
name|channel
parameter_list|,
name|float
name|value
parameter_list|)
block|{
comment|/* don't invert the alpha channel */
if|if
condition|(
operator|(
name|nchannels
operator|==
literal|2
operator|||
name|nchannels
operator|==
literal|4
operator|)
operator|&&
name|channel
operator|==
name|nchannels
operator|-
literal|1
condition|)
return|return
name|value
return|;
return|return
literal|1.0
operator|-
name|value
return|;
block|}
end_function

begin_function
name|void
DECL|function|invert_lut_setup (GimpLut * lut,int nchannels)
name|invert_lut_setup
parameter_list|(
name|GimpLut
modifier|*
name|lut
parameter_list|,
name|int
name|nchannels
parameter_list|)
block|{
name|gimp_lut_setup_exact
argument_list|(
name|lut
argument_list|,
operator|(
name|GimpLutFunc
operator|)
name|invert_lut_func
argument_list|,
name|NULL
argument_list|,
name|nchannels
argument_list|)
expr_stmt|;
block|}
end_function

begin_function
name|GimpLut
modifier|*
DECL|function|invert_lut_new (int nchannels)
name|invert_lut_new
parameter_list|(
name|int
name|nchannels
parameter_list|)
block|{
name|GimpLut
modifier|*
name|lut
decl_stmt|;
name|lut
operator|=
name|gimp_lut_new
argument_list|()
expr_stmt|;
name|invert_lut_setup
argument_list|(
name|lut
argument_list|,
name|nchannels
argument_list|)
expr_stmt|;
return|return
name|lut
return|;
block|}
end_function

begin_comment
comment|/* ---------------- add (or subract)------------------ */
end_comment

begin_function
specifier|static
name|float
DECL|function|add_lut_func (double * ammount,int nchannels,int channel,float value)
name|add_lut_func
parameter_list|(
name|double
modifier|*
name|ammount
parameter_list|,
name|int
name|nchannels
parameter_list|,
name|int
name|channel
parameter_list|,
name|float
name|value
parameter_list|)
block|{
comment|/* don't change the alpha channel */
if|if
condition|(
operator|(
name|nchannels
operator|==
literal|2
operator|||
name|nchannels
operator|==
literal|4
operator|)
operator|&&
name|channel
operator|==
name|nchannels
operator|-
literal|1
condition|)
return|return
name|value
return|;
return|return
operator|(
name|value
operator|+
operator|*
name|ammount
operator|)
return|;
block|}
end_function

begin_function
name|void
DECL|function|add_lut_setup (GimpLut * lut,double ammount,int nchannels)
name|add_lut_setup
parameter_list|(
name|GimpLut
modifier|*
name|lut
parameter_list|,
name|double
name|ammount
parameter_list|,
name|int
name|nchannels
parameter_list|)
block|{
name|gimp_lut_setup
argument_list|(
name|lut
argument_list|,
operator|(
name|GimpLutFunc
operator|)
name|add_lut_func
argument_list|,
operator|(
name|void
operator|*
operator|)
operator|&
name|ammount
argument_list|,
name|nchannels
argument_list|)
expr_stmt|;
block|}
end_function

begin_function
name|GimpLut
modifier|*
DECL|function|add_lut_new (double ammount,int nchannels)
name|add_lut_new
parameter_list|(
name|double
name|ammount
parameter_list|,
name|int
name|nchannels
parameter_list|)
block|{
name|GimpLut
modifier|*
name|lut
decl_stmt|;
name|lut
operator|=
name|gimp_lut_new
argument_list|()
expr_stmt|;
name|add_lut_setup
argument_list|(
name|lut
argument_list|,
name|ammount
argument_list|,
name|nchannels
argument_list|)
expr_stmt|;
return|return
name|lut
return|;
block|}
end_function

begin_comment
comment|/* ---------------- intersect (MINIMUM(pixel, value)) ------------------ */
end_comment

begin_function
specifier|static
name|float
DECL|function|intersect_lut_func (double * min,int nchannels,int channel,float value)
name|intersect_lut_func
parameter_list|(
name|double
modifier|*
name|min
parameter_list|,
name|int
name|nchannels
parameter_list|,
name|int
name|channel
parameter_list|,
name|float
name|value
parameter_list|)
block|{
comment|/* don't change the alpha channel */
if|if
condition|(
operator|(
name|nchannels
operator|==
literal|2
operator|||
name|nchannels
operator|==
literal|4
operator|)
operator|&&
name|channel
operator|==
name|nchannels
operator|-
literal|1
condition|)
return|return
name|value
return|;
return|return
name|MIN
argument_list|(
name|value
argument_list|,
operator|*
name|min
argument_list|)
return|;
block|}
end_function

begin_function
name|void
DECL|function|intersect_lut_setup (GimpLut * lut,double value,int nchannels)
name|intersect_lut_setup
parameter_list|(
name|GimpLut
modifier|*
name|lut
parameter_list|,
name|double
name|value
parameter_list|,
name|int
name|nchannels
parameter_list|)
block|{
name|gimp_lut_setup_exact
argument_list|(
name|lut
argument_list|,
operator|(
name|GimpLutFunc
operator|)
name|intersect_lut_func
argument_list|,
operator|(
name|void
operator|*
operator|)
operator|&
name|value
argument_list|,
name|nchannels
argument_list|)
expr_stmt|;
block|}
end_function

begin_function
name|GimpLut
modifier|*
DECL|function|intersect_lut_new (double value,int nchannels)
name|intersect_lut_new
parameter_list|(
name|double
name|value
parameter_list|,
name|int
name|nchannels
parameter_list|)
block|{
name|GimpLut
modifier|*
name|lut
decl_stmt|;
name|lut
operator|=
name|gimp_lut_new
argument_list|()
expr_stmt|;
name|intersect_lut_setup
argument_list|(
name|lut
argument_list|,
name|value
argument_list|,
name|nchannels
argument_list|)
expr_stmt|;
return|return
name|lut
return|;
block|}
end_function

begin_comment
comment|/* ---------------- Threshold ------------------ */
end_comment

begin_function
specifier|static
name|float
DECL|function|threshold_lut_func (double * min,int nchannels,int channel,float value)
name|threshold_lut_func
parameter_list|(
name|double
modifier|*
name|min
parameter_list|,
name|int
name|nchannels
parameter_list|,
name|int
name|channel
parameter_list|,
name|float
name|value
parameter_list|)
block|{
comment|/* don't change the alpha channel */
if|if
condition|(
operator|(
name|nchannels
operator|==
literal|2
operator|||
name|nchannels
operator|==
literal|4
operator|)
operator|&&
name|channel
operator|==
name|nchannels
operator|-
literal|1
condition|)
return|return
name|value
return|;
if|if
condition|(
name|value
operator|<
operator|*
name|min
condition|)
return|return
literal|0.0
return|;
return|return
literal|1.0
return|;
block|}
end_function

begin_function
name|void
DECL|function|threshold_lut_setup (GimpLut * lut,double value,int nchannels)
name|threshold_lut_setup
parameter_list|(
name|GimpLut
modifier|*
name|lut
parameter_list|,
name|double
name|value
parameter_list|,
name|int
name|nchannels
parameter_list|)
block|{
name|gimp_lut_setup_exact
argument_list|(
name|lut
argument_list|,
operator|(
name|GimpLutFunc
operator|)
name|threshold_lut_func
argument_list|,
operator|(
name|void
operator|*
operator|)
operator|&
name|value
argument_list|,
name|nchannels
argument_list|)
expr_stmt|;
block|}
end_function

begin_function
name|GimpLut
modifier|*
DECL|function|threshold_lut_new (double value,int nchannels)
name|threshold_lut_new
parameter_list|(
name|double
name|value
parameter_list|,
name|int
name|nchannels
parameter_list|)
block|{
name|GimpLut
modifier|*
name|lut
decl_stmt|;
name|lut
operator|=
name|gimp_lut_new
argument_list|()
expr_stmt|;
name|threshold_lut_setup
argument_list|(
name|lut
argument_list|,
name|value
argument_list|,
name|nchannels
argument_list|)
expr_stmt|;
return|return
name|lut
return|;
block|}
end_function

begin_comment
comment|/* ------------- levels ------------ */
end_comment

begin_typedef
typedef|typedef
struct|struct
DECL|struct|__anon2a1149b40108
block|{
DECL|member|gamma
name|double
modifier|*
name|gamma
decl_stmt|;
DECL|member|low_input
name|int
modifier|*
name|low_input
decl_stmt|;
DECL|member|high_input
name|int
modifier|*
name|high_input
decl_stmt|;
DECL|member|low_output
name|int
modifier|*
name|low_output
decl_stmt|;
DECL|member|high_output
name|int
modifier|*
name|high_output
decl_stmt|;
DECL|typedef|levels_struct
block|}
name|levels_struct
typedef|;
end_typedef

begin_function
specifier|static
name|float
DECL|function|levels_lut_func (levels_struct * data,int nchannels,int channel,float value)
name|levels_lut_func
parameter_list|(
name|levels_struct
modifier|*
name|data
parameter_list|,
name|int
name|nchannels
parameter_list|,
name|int
name|channel
parameter_list|,
name|float
name|value
parameter_list|)
block|{
name|double
name|inten
decl_stmt|;
name|int
name|j
decl_stmt|;
if|if
condition|(
name|nchannels
operator|==
literal|1
condition|)
name|j
operator|=
literal|0
expr_stmt|;
else|else
name|j
operator|=
name|channel
operator|+
literal|1
expr_stmt|;
name|inten
operator|=
name|value
expr_stmt|;
comment|/* For color  images this runs through the loop with j = channel +1      the first time and j = 0 the second time */
comment|/* For bw images this runs through the loop with j = 0 the first and      only time  */
for|for
control|(
init|;
name|j
operator|>=
literal|0
condition|;
name|j
operator|-=
operator|(
name|channel
operator|+
literal|1
operator|)
control|)
block|{
comment|/* don't apply the overall curve to the alpha channel */
if|if
condition|(
name|j
operator|==
literal|0
operator|&&
operator|(
name|nchannels
operator|==
literal|2
operator|||
name|nchannels
operator|==
literal|4
operator|)
operator|&&
name|channel
operator|==
name|nchannels
operator|-
literal|1
condition|)
return|return
name|inten
return|;
comment|/*  determine input intensity  */
if|if
condition|(
name|data
operator|->
name|high_input
index|[
name|j
index|]
operator|!=
name|data
operator|->
name|low_input
index|[
name|j
index|]
condition|)
name|inten
operator|=
call|(
name|double
call|)
argument_list|(
literal|255.0
operator|*
name|inten
operator|-
name|data
operator|->
name|low_input
index|[
name|j
index|]
argument_list|)
operator|/
call|(
name|double
call|)
argument_list|(
name|data
operator|->
name|high_input
index|[
name|j
index|]
operator|-
name|data
operator|->
name|low_input
index|[
name|j
index|]
argument_list|)
expr_stmt|;
else|else
name|inten
operator|=
call|(
name|double
call|)
argument_list|(
literal|255.0
operator|*
name|inten
operator|-
name|data
operator|->
name|low_input
index|[
name|j
index|]
argument_list|)
expr_stmt|;
if|if
condition|(
name|data
operator|->
name|gamma
index|[
name|j
index|]
operator|!=
literal|0.0
condition|)
block|{
if|if
condition|(
name|inten
operator|>=
literal|0.0
condition|)
name|inten
operator|=
name|pow
argument_list|(
name|inten
argument_list|,
operator|(
literal|1.0
operator|/
name|data
operator|->
name|gamma
index|[
name|j
index|]
operator|)
argument_list|)
expr_stmt|;
else|else
name|inten
operator|=
operator|-
name|pow
argument_list|(
operator|-
name|inten
argument_list|,
operator|(
literal|1.0
operator|/
name|data
operator|->
name|gamma
index|[
name|j
index|]
operator|)
argument_list|)
expr_stmt|;
block|}
comment|/*  determine the output intensity  */
if|if
condition|(
name|data
operator|->
name|high_output
index|[
name|j
index|]
operator|>=
name|data
operator|->
name|low_output
index|[
name|j
index|]
condition|)
name|inten
operator|=
call|(
name|double
call|)
argument_list|(
name|inten
operator|*
operator|(
name|data
operator|->
name|high_output
index|[
name|j
index|]
operator|-
name|data
operator|->
name|low_output
index|[
name|j
index|]
operator|)
operator|+
name|data
operator|->
name|low_output
index|[
name|j
index|]
argument_list|)
expr_stmt|;
elseif|else
if|if
condition|(
name|data
operator|->
name|high_output
index|[
name|j
index|]
operator|<
name|data
operator|->
name|low_output
index|[
name|j
index|]
condition|)
name|inten
operator|=
call|(
name|double
call|)
argument_list|(
name|data
operator|->
name|low_output
index|[
name|j
index|]
operator|-
name|inten
operator|*
operator|(
name|data
operator|->
name|low_output
index|[
name|j
index|]
operator|-
name|data
operator|->
name|high_output
index|[
name|j
index|]
operator|)
argument_list|)
expr_stmt|;
name|inten
operator|/=
literal|255.0
expr_stmt|;
block|}
return|return
name|inten
return|;
block|}
end_function

begin_function
name|void
DECL|function|levels_lut_setup (GimpLut * lut,double * gamma,int * low_input,int * high_input,int * low_output,int * high_output,int nchannels)
name|levels_lut_setup
parameter_list|(
name|GimpLut
modifier|*
name|lut
parameter_list|,
name|double
modifier|*
name|gamma
parameter_list|,
name|int
modifier|*
name|low_input
parameter_list|,
name|int
modifier|*
name|high_input
parameter_list|,
name|int
modifier|*
name|low_output
parameter_list|,
name|int
modifier|*
name|high_output
parameter_list|,
name|int
name|nchannels
parameter_list|)
block|{
name|levels_struct
name|data
decl_stmt|;
name|data
operator|.
name|gamma
operator|=
name|gamma
expr_stmt|;
name|data
operator|.
name|low_input
operator|=
name|low_input
expr_stmt|;
name|data
operator|.
name|high_input
operator|=
name|high_input
expr_stmt|;
name|data
operator|.
name|low_output
operator|=
name|low_output
expr_stmt|;
name|data
operator|.
name|high_output
operator|=
name|high_output
expr_stmt|;
name|gimp_lut_setup
argument_list|(
name|lut
argument_list|,
operator|(
name|GimpLutFunc
operator|)
name|levels_lut_func
argument_list|,
operator|(
name|void
operator|*
operator|)
operator|&
name|data
argument_list|,
name|nchannels
argument_list|)
expr_stmt|;
block|}
end_function

begin_function
name|GimpLut
modifier|*
DECL|function|levels_lut_new (double * gamma,int * low_input,int * high_input,int * low_output,int * high_output,int nchannels)
name|levels_lut_new
parameter_list|(
name|double
modifier|*
name|gamma
parameter_list|,
name|int
modifier|*
name|low_input
parameter_list|,
name|int
modifier|*
name|high_input
parameter_list|,
name|int
modifier|*
name|low_output
parameter_list|,
name|int
modifier|*
name|high_output
parameter_list|,
name|int
name|nchannels
parameter_list|)
block|{
name|GimpLut
modifier|*
name|lut
decl_stmt|;
name|lut
operator|=
name|gimp_lut_new
argument_list|()
expr_stmt|;
name|levels_lut_setup
argument_list|(
name|lut
argument_list|,
name|gamma
argument_list|,
name|low_input
argument_list|,
name|high_input
argument_list|,
name|low_output
argument_list|,
name|high_output
argument_list|,
name|nchannels
argument_list|)
expr_stmt|;
return|return
name|lut
return|;
block|}
end_function

begin_comment
comment|/* --------------- posterize ---------------- */
end_comment

begin_function
specifier|static
name|float
DECL|function|posterize_lut_func (int * ilevels,int nchannels,int channel,float value)
name|posterize_lut_func
parameter_list|(
name|int
modifier|*
name|ilevels
parameter_list|,
name|int
name|nchannels
parameter_list|,
name|int
name|channel
parameter_list|,
name|float
name|value
parameter_list|)
block|{
name|int
name|levels
decl_stmt|;
comment|/* don't posterize the alpha channel */
if|if
condition|(
operator|(
name|nchannels
operator|==
literal|2
operator|||
name|nchannels
operator|==
literal|4
operator|)
operator|&&
name|channel
operator|==
name|nchannels
operator|-
literal|1
condition|)
return|return
name|value
return|;
if|if
condition|(
operator|*
name|ilevels
operator|<
literal|2
condition|)
name|levels
operator|=
literal|2
expr_stmt|;
else|else
name|levels
operator|=
operator|*
name|ilevels
expr_stmt|;
name|value
operator|=
name|RINT
argument_list|(
name|value
operator|*
operator|(
name|levels
operator|-
literal|1.0
operator|)
argument_list|)
operator|/
operator|(
name|levels
operator|-
literal|1.0
operator|)
expr_stmt|;
return|return
name|value
return|;
block|}
end_function

begin_function
name|void
DECL|function|posterize_lut_setup (GimpLut * lut,int levels,int nchannels)
name|posterize_lut_setup
parameter_list|(
name|GimpLut
modifier|*
name|lut
parameter_list|,
name|int
name|levels
parameter_list|,
name|int
name|nchannels
parameter_list|)
block|{
name|gimp_lut_setup_exact
argument_list|(
name|lut
argument_list|,
operator|(
name|GimpLutFunc
operator|)
name|posterize_lut_func
argument_list|,
operator|(
name|void
operator|*
operator|)
operator|&
name|levels
argument_list|,
name|nchannels
argument_list|)
expr_stmt|;
block|}
end_function

begin_function
name|GimpLut
modifier|*
DECL|function|posterize_lut_new (int levels,int nchannels)
name|posterize_lut_new
parameter_list|(
name|int
name|levels
parameter_list|,
name|int
name|nchannels
parameter_list|)
block|{
name|GimpLut
modifier|*
name|lut
decl_stmt|;
name|lut
operator|=
name|gimp_lut_new
argument_list|()
expr_stmt|;
name|posterize_lut_setup
argument_list|(
name|lut
argument_list|,
name|levels
argument_list|,
name|nchannels
argument_list|)
expr_stmt|;
return|return
name|lut
return|;
block|}
end_function

begin_comment
comment|/* --------------- equalize ------------- */
end_comment

begin_struct
DECL|struct|hist_lut_struct
struct|struct
name|hist_lut_struct
block|{
DECL|member|histogram
name|GimpHistogram
modifier|*
name|histogram
decl_stmt|;
DECL|member|part
name|int
name|part
index|[
literal|5
index|]
index|[
literal|257
index|]
decl_stmt|;
block|}
struct|;
end_struct

begin_function
specifier|static
name|float
DECL|function|equalize_lut_func (struct hist_lut_struct * hlut,int nchannels,int channel,float value)
name|equalize_lut_func
parameter_list|(
name|struct
name|hist_lut_struct
modifier|*
name|hlut
parameter_list|,
name|int
name|nchannels
parameter_list|,
name|int
name|channel
parameter_list|,
name|float
name|value
parameter_list|)
block|{
name|int
name|i
init|=
literal|0
decl_stmt|,
name|j
decl_stmt|;
name|j
operator|=
call|(
name|int
call|)
argument_list|(
name|value
operator|*
literal|255.0
operator|+
literal|0.5
argument_list|)
expr_stmt|;
while|while
condition|(
name|hlut
operator|->
name|part
index|[
name|channel
index|]
index|[
name|i
operator|+
literal|1
index|]
operator|<=
name|j
condition|)
name|i
operator|++
expr_stmt|;
return|return
name|i
operator|/
literal|255.0
return|;
block|}
end_function

begin_function
name|void
DECL|function|eq_histogram_lut_setup (GimpLut * lut,GimpHistogram * hist,int bytes)
name|eq_histogram_lut_setup
parameter_list|(
name|GimpLut
modifier|*
name|lut
parameter_list|,
name|GimpHistogram
modifier|*
name|hist
parameter_list|,
name|int
name|bytes
parameter_list|)
block|{
name|int
name|i
decl_stmt|,
name|k
decl_stmt|,
name|j
decl_stmt|;
name|struct
name|hist_lut_struct
name|hlut
decl_stmt|;
name|double
name|pixels_per_value
decl_stmt|;
name|double
name|desired
decl_stmt|;
name|double
name|sum
decl_stmt|,
name|dif
decl_stmt|;
comment|/* Find partition points */
name|pixels_per_value
operator|=
name|gimp_histogram_get_count
argument_list|(
name|hist
argument_list|,
literal|0
argument_list|,
literal|255
argument_list|)
operator|/
literal|256.0
expr_stmt|;
for|for
control|(
name|k
operator|=
literal|0
init|;
name|k
operator|<
name|bytes
condition|;
name|k
operator|++
control|)
block|{
comment|/* First and last points in partition */
name|hlut
operator|.
name|part
index|[
name|k
index|]
index|[
literal|0
index|]
operator|=
literal|0
expr_stmt|;
name|hlut
operator|.
name|part
index|[
name|k
index|]
index|[
literal|256
index|]
operator|=
literal|256
expr_stmt|;
comment|/* Find intermediate points */
name|j
operator|=
literal|0
expr_stmt|;
name|sum
operator|=
name|gimp_histogram_get_channel
argument_list|(
name|hist
argument_list|,
name|k
argument_list|,
literal|0
argument_list|)
operator|+
name|gimp_histogram_get_channel
argument_list|(
name|hist
argument_list|,
name|k
argument_list|,
literal|1
argument_list|)
expr_stmt|;
for|for
control|(
name|i
operator|=
literal|1
init|;
name|i
operator|<
literal|256
condition|;
name|i
operator|++
control|)
block|{
name|desired
operator|=
name|i
operator|*
name|pixels_per_value
expr_stmt|;
while|while
condition|(
name|sum
operator|<=
name|desired
condition|)
block|{
name|j
operator|++
expr_stmt|;
name|sum
operator|+=
name|gimp_histogram_get_channel
argument_list|(
name|hist
argument_list|,
name|k
argument_list|,
name|j
operator|+
literal|1
argument_list|)
expr_stmt|;
block|}
comment|/* Nearest sum */
name|dif
operator|=
name|sum
operator|-
name|gimp_histogram_get_channel
argument_list|(
name|hist
argument_list|,
name|k
argument_list|,
name|j
argument_list|)
expr_stmt|;
if|if
condition|(
operator|(
name|sum
operator|-
name|desired
operator|)
operator|>
operator|(
name|dif
operator|/
literal|2.0
operator|)
condition|)
name|hlut
operator|.
name|part
index|[
name|k
index|]
index|[
name|i
index|]
operator|=
name|j
expr_stmt|;
else|else
name|hlut
operator|.
name|part
index|[
name|k
index|]
index|[
name|i
index|]
operator|=
name|j
operator|+
literal|1
expr_stmt|;
block|}
block|}
name|gimp_lut_setup
argument_list|(
name|lut
argument_list|,
operator|(
name|GimpLutFunc
operator|)
name|equalize_lut_func
argument_list|,
operator|(
name|void
operator|*
operator|)
operator|&
name|hlut
argument_list|,
name|bytes
argument_list|)
expr_stmt|;
block|}
end_function

begin_function
name|GimpLut
modifier|*
DECL|function|eq_histogram_lut_new (GimpHistogram * h,int nchannels)
name|eq_histogram_lut_new
parameter_list|(
name|GimpHistogram
modifier|*
name|h
parameter_list|,
name|int
name|nchannels
parameter_list|)
block|{
name|GimpLut
modifier|*
name|lut
decl_stmt|;
name|lut
operator|=
name|gimp_lut_new
argument_list|()
expr_stmt|;
name|eq_histogram_lut_setup
argument_list|(
name|lut
argument_list|,
name|h
argument_list|,
name|nchannels
argument_list|)
expr_stmt|;
return|return
name|lut
return|;
block|}
end_function

end_unit

