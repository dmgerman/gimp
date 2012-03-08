begin_unit|revision:0.9.5;language:C;cregit-version:0.0.1
begin_comment
comment|/* GIMP - The GNU Image Manipulation Program  * Copyright (C) 1995 Spencer Kimball and Peter Mattis  *  * This program is free software: you can redistribute it and/or modify  * it under the terms of the GNU General Public License as published by  * the Free Software Foundation; either version 3 of the License, or  * (at your option) any later version.  *  * This program is distributed in the hope that it will be useful,  * but WITHOUT ANY WARRANTY; without even the implied warranty of  * MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the  * GNU General Public License for more details.  *  * You should have received a copy of the GNU General Public License  * along with this program.  If not, see<http://www.gnu.org/licenses/>.  */
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
file|"libgimpmath/gimpmath.h"
end_include

begin_include
include|#
directive|include
file|"base-types.h"
end_include

begin_include
include|#
directive|include
file|"gimphistogram.h"
end_include

begin_include
include|#
directive|include
file|"gimplut.h"
end_include

begin_include
include|#
directive|include
file|"lut-funcs.h"
end_include

begin_comment
comment|/* ---------- Brightness/Contrast -----------*/
end_comment

begin_typedef
typedef|typedef
struct|struct
DECL|struct|__anon28c8657d0108
block|{
DECL|member|brightness
name|gdouble
name|brightness
decl_stmt|;
DECL|member|contrast
name|gdouble
name|contrast
decl_stmt|;
DECL|typedef|BrightnessContrastLutData
block|}
name|BrightnessContrastLutData
typedef|;
end_typedef

begin_function
specifier|static
name|gfloat
DECL|function|brightness_contrast_lut_func (BrightnessContrastLutData * data,gint nchannels,gint channel,gfloat value)
name|brightness_contrast_lut_func
parameter_list|(
name|BrightnessContrastLutData
modifier|*
name|data
parameter_list|,
name|gint
name|nchannels
parameter_list|,
name|gint
name|channel
parameter_list|,
name|gfloat
name|value
parameter_list|)
block|{
name|gdouble
name|slant
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
name|slant
operator|=
name|tan
argument_list|(
operator|(
name|data
operator|->
name|contrast
operator|+
literal|1
operator|)
operator|*
name|G_PI_4
argument_list|)
expr_stmt|;
name|value
operator|=
operator|(
name|value
operator|-
literal|0.5
operator|)
operator|*
name|slant
operator|+
literal|0.5
expr_stmt|;
return|return
name|value
return|;
block|}
end_function

begin_function
name|void
DECL|function|brightness_contrast_lut_setup (GimpLut * lut,gdouble brightness,gdouble contrast,gint n_channels)
name|brightness_contrast_lut_setup
parameter_list|(
name|GimpLut
modifier|*
name|lut
parameter_list|,
name|gdouble
name|brightness
parameter_list|,
name|gdouble
name|contrast
parameter_list|,
name|gint
name|n_channels
parameter_list|)
block|{
name|BrightnessContrastLutData
name|data
decl_stmt|;
name|g_return_if_fail
argument_list|(
name|lut
operator|!=
name|NULL
argument_list|)
expr_stmt|;
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
operator|&
name|data
argument_list|,
name|n_channels
argument_list|)
expr_stmt|;
block|}
end_function

begin_function
name|GimpLut
modifier|*
DECL|function|brightness_contrast_lut_new (gdouble brightness,gdouble contrast,gint n_channels)
name|brightness_contrast_lut_new
parameter_list|(
name|gdouble
name|brightness
parameter_list|,
name|gdouble
name|contrast
parameter_list|,
name|gint
name|n_channels
parameter_list|)
block|{
name|GimpLut
modifier|*
name|lut
init|=
name|gimp_lut_new
argument_list|()
decl_stmt|;
name|brightness_contrast_lut_setup
argument_list|(
name|lut
argument_list|,
name|brightness
argument_list|,
name|contrast
argument_list|,
name|n_channels
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
name|gfloat
DECL|function|invert_lut_func (gpointer unused,gint n_channels,gint channel,gfloat value)
name|invert_lut_func
parameter_list|(
name|gpointer
name|unused
parameter_list|,
name|gint
name|n_channels
parameter_list|,
name|gint
name|channel
parameter_list|,
name|gfloat
name|value
parameter_list|)
block|{
comment|/* don't invert the alpha channel */
if|if
condition|(
operator|(
name|n_channels
operator|==
literal|2
operator|||
name|n_channels
operator|==
literal|4
operator|)
operator|&&
name|channel
operator|==
name|n_channels
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
specifier|static
name|void
DECL|function|invert_lut_setup (GimpLut * lut,gint n_channels)
name|invert_lut_setup
parameter_list|(
name|GimpLut
modifier|*
name|lut
parameter_list|,
name|gint
name|n_channels
parameter_list|)
block|{
name|g_return_if_fail
argument_list|(
name|lut
operator|!=
name|NULL
argument_list|)
expr_stmt|;
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
name|n_channels
argument_list|)
expr_stmt|;
block|}
end_function

begin_function
name|GimpLut
modifier|*
DECL|function|invert_lut_new (gint n_channels)
name|invert_lut_new
parameter_list|(
name|gint
name|n_channels
parameter_list|)
block|{
name|GimpLut
modifier|*
name|lut
init|=
name|gimp_lut_new
argument_list|()
decl_stmt|;
name|invert_lut_setup
argument_list|(
name|lut
argument_list|,
name|n_channels
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
name|gfloat
DECL|function|add_lut_func (gdouble * amount,gint n_channels,gint channel,gfloat value)
name|add_lut_func
parameter_list|(
name|gdouble
modifier|*
name|amount
parameter_list|,
name|gint
name|n_channels
parameter_list|,
name|gint
name|channel
parameter_list|,
name|gfloat
name|value
parameter_list|)
block|{
comment|/* don't change the alpha channel */
if|if
condition|(
operator|(
name|n_channels
operator|==
literal|2
operator|||
name|n_channels
operator|==
literal|4
operator|)
operator|&&
name|channel
operator|==
name|n_channels
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
name|amount
operator|)
return|;
block|}
end_function

begin_function
specifier|static
name|void
DECL|function|add_lut_setup (GimpLut * lut,gdouble amount,gint n_channels)
name|add_lut_setup
parameter_list|(
name|GimpLut
modifier|*
name|lut
parameter_list|,
name|gdouble
name|amount
parameter_list|,
name|gint
name|n_channels
parameter_list|)
block|{
name|g_return_if_fail
argument_list|(
name|lut
operator|!=
name|NULL
argument_list|)
expr_stmt|;
name|gimp_lut_setup
argument_list|(
name|lut
argument_list|,
operator|(
name|GimpLutFunc
operator|)
name|add_lut_func
argument_list|,
operator|&
name|amount
argument_list|,
name|n_channels
argument_list|)
expr_stmt|;
block|}
end_function

begin_function
name|GimpLut
modifier|*
DECL|function|add_lut_new (gdouble amount,gint n_channels)
name|add_lut_new
parameter_list|(
name|gdouble
name|amount
parameter_list|,
name|gint
name|n_channels
parameter_list|)
block|{
name|GimpLut
modifier|*
name|lut
init|=
name|gimp_lut_new
argument_list|()
decl_stmt|;
name|add_lut_setup
argument_list|(
name|lut
argument_list|,
name|amount
argument_list|,
name|n_channels
argument_list|)
expr_stmt|;
return|return
name|lut
return|;
block|}
end_function

begin_comment
comment|/* ---------------- intersect (MIN (pixel, value)) ------------------ */
end_comment

begin_function
specifier|static
name|gfloat
DECL|function|intersect_lut_func (gdouble * min,gint n_channels,gint channel,gfloat value)
name|intersect_lut_func
parameter_list|(
name|gdouble
modifier|*
name|min
parameter_list|,
name|gint
name|n_channels
parameter_list|,
name|gint
name|channel
parameter_list|,
name|gfloat
name|value
parameter_list|)
block|{
comment|/* don't change the alpha channel */
if|if
condition|(
operator|(
name|n_channels
operator|==
literal|2
operator|||
name|n_channels
operator|==
literal|4
operator|)
operator|&&
name|channel
operator|==
name|n_channels
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
specifier|static
name|void
DECL|function|intersect_lut_setup (GimpLut * lut,gdouble value,gint n_channels)
name|intersect_lut_setup
parameter_list|(
name|GimpLut
modifier|*
name|lut
parameter_list|,
name|gdouble
name|value
parameter_list|,
name|gint
name|n_channels
parameter_list|)
block|{
name|g_return_if_fail
argument_list|(
name|lut
operator|!=
name|NULL
argument_list|)
expr_stmt|;
name|gimp_lut_setup_exact
argument_list|(
name|lut
argument_list|,
operator|(
name|GimpLutFunc
operator|)
name|intersect_lut_func
argument_list|,
operator|&
name|value
argument_list|,
name|n_channels
argument_list|)
expr_stmt|;
block|}
end_function

begin_function
name|GimpLut
modifier|*
DECL|function|intersect_lut_new (gdouble value,gint n_channels)
name|intersect_lut_new
parameter_list|(
name|gdouble
name|value
parameter_list|,
name|gint
name|n_channels
parameter_list|)
block|{
name|GimpLut
modifier|*
name|lut
init|=
name|gimp_lut_new
argument_list|()
decl_stmt|;
name|intersect_lut_setup
argument_list|(
name|lut
argument_list|,
name|value
argument_list|,
name|n_channels
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
name|gfloat
DECL|function|threshold_lut_func (gdouble * min,gint n_channels,gint channel,gfloat value)
name|threshold_lut_func
parameter_list|(
name|gdouble
modifier|*
name|min
parameter_list|,
name|gint
name|n_channels
parameter_list|,
name|gint
name|channel
parameter_list|,
name|gfloat
name|value
parameter_list|)
block|{
comment|/* don't change the alpha channel */
if|if
condition|(
operator|(
name|n_channels
operator|==
literal|2
operator|||
name|n_channels
operator|==
literal|4
operator|)
operator|&&
name|channel
operator|==
name|n_channels
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
specifier|static
name|void
DECL|function|threshold_lut_setup (GimpLut * lut,gdouble value,gint n_channels)
name|threshold_lut_setup
parameter_list|(
name|GimpLut
modifier|*
name|lut
parameter_list|,
name|gdouble
name|value
parameter_list|,
name|gint
name|n_channels
parameter_list|)
block|{
name|g_return_if_fail
argument_list|(
name|lut
operator|!=
name|NULL
argument_list|)
expr_stmt|;
name|gimp_lut_setup_exact
argument_list|(
name|lut
argument_list|,
operator|(
name|GimpLutFunc
operator|)
name|threshold_lut_func
argument_list|,
operator|&
name|value
argument_list|,
name|n_channels
argument_list|)
expr_stmt|;
block|}
end_function

begin_function
name|GimpLut
modifier|*
DECL|function|threshold_lut_new (gdouble value,gint n_channels)
name|threshold_lut_new
parameter_list|(
name|gdouble
name|value
parameter_list|,
name|gint
name|n_channels
parameter_list|)
block|{
name|GimpLut
modifier|*
name|lut
init|=
name|gimp_lut_new
argument_list|()
decl_stmt|;
name|threshold_lut_setup
argument_list|(
name|lut
argument_list|,
name|value
argument_list|,
name|n_channels
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
name|gfloat
DECL|function|posterize_lut_func (gint * ilevels,gint n_channels,gint channel,gfloat value)
name|posterize_lut_func
parameter_list|(
name|gint
modifier|*
name|ilevels
parameter_list|,
name|gint
name|n_channels
parameter_list|,
name|gint
name|channel
parameter_list|,
name|gfloat
name|value
parameter_list|)
block|{
name|gint
name|levels
decl_stmt|;
comment|/* don't posterize the alpha channel */
if|if
condition|(
operator|(
name|n_channels
operator|==
literal|2
operator|||
name|n_channels
operator|==
literal|4
operator|)
operator|&&
name|channel
operator|==
name|n_channels
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
DECL|function|posterize_lut_setup (GimpLut * lut,gint levels,gint n_channels)
name|posterize_lut_setup
parameter_list|(
name|GimpLut
modifier|*
name|lut
parameter_list|,
name|gint
name|levels
parameter_list|,
name|gint
name|n_channels
parameter_list|)
block|{
name|g_return_if_fail
argument_list|(
name|lut
operator|!=
name|NULL
argument_list|)
expr_stmt|;
name|gimp_lut_setup_exact
argument_list|(
name|lut
argument_list|,
operator|(
name|GimpLutFunc
operator|)
name|posterize_lut_func
argument_list|,
operator|&
name|levels
argument_list|,
name|n_channels
argument_list|)
expr_stmt|;
block|}
end_function

begin_function
name|GimpLut
modifier|*
DECL|function|posterize_lut_new (gint levels,gint n_channels)
name|posterize_lut_new
parameter_list|(
name|gint
name|levels
parameter_list|,
name|gint
name|n_channels
parameter_list|)
block|{
name|GimpLut
modifier|*
name|lut
init|=
name|gimp_lut_new
argument_list|()
decl_stmt|;
name|posterize_lut_setup
argument_list|(
name|lut
argument_list|,
name|levels
argument_list|,
name|n_channels
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

begin_typedef
typedef|typedef
struct|struct
DECL|struct|__anon28c8657d0208
block|{
DECL|member|histogram
name|GimpHistogram
modifier|*
name|histogram
decl_stmt|;
DECL|member|part
name|gint
name|part
index|[
literal|5
index|]
index|[
literal|256
index|]
decl_stmt|;
DECL|typedef|hist_lut_struct
block|}
name|hist_lut_struct
typedef|;
end_typedef

begin_function
specifier|static
name|gfloat
DECL|function|equalize_lut_func (hist_lut_struct * hlut,gint nchannels,gint channel,gfloat value)
name|equalize_lut_func
parameter_list|(
name|hist_lut_struct
modifier|*
name|hlut
parameter_list|,
name|gint
name|nchannels
parameter_list|,
name|gint
name|channel
parameter_list|,
name|gfloat
name|value
parameter_list|)
block|{
name|gint
name|j
decl_stmt|;
comment|/* don't equalize the alpha channel */
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
name|j
operator|=
name|RINT
argument_list|(
name|CLAMP
argument_list|(
name|value
operator|*
literal|255.0
argument_list|,
literal|0
argument_list|,
literal|255
argument_list|)
argument_list|)
expr_stmt|;
return|return
name|hlut
operator|->
name|part
index|[
name|channel
index|]
index|[
name|j
index|]
operator|/
literal|255.
return|;
block|}
end_function

begin_function
specifier|static
name|void
DECL|function|equalize_lut_setup (GimpLut * lut,GimpHistogram * hist,gint n_channels)
name|equalize_lut_setup
parameter_list|(
name|GimpLut
modifier|*
name|lut
parameter_list|,
name|GimpHistogram
modifier|*
name|hist
parameter_list|,
name|gint
name|n_channels
parameter_list|)
block|{
name|gint
name|i
decl_stmt|,
name|k
decl_stmt|;
name|hist_lut_struct
name|hlut
decl_stmt|;
name|gdouble
name|pixels
decl_stmt|;
name|g_return_if_fail
argument_list|(
name|lut
operator|!=
name|NULL
argument_list|)
expr_stmt|;
name|g_return_if_fail
argument_list|(
name|hist
operator|!=
name|NULL
argument_list|)
expr_stmt|;
comment|/* Find partition points */
name|pixels
operator|=
name|gimp_histogram_get_count
argument_list|(
name|hist
argument_list|,
name|GIMP_HISTOGRAM_VALUE
argument_list|,
literal|0
argument_list|,
literal|255
argument_list|)
expr_stmt|;
for|for
control|(
name|k
operator|=
literal|0
init|;
name|k
operator|<
name|n_channels
condition|;
name|k
operator|++
control|)
block|{
name|gdouble
name|sum
init|=
literal|0
decl_stmt|;
for|for
control|(
name|i
operator|=
literal|0
init|;
name|i
operator|<
literal|256
condition|;
name|i
operator|++
control|)
block|{
name|gdouble
name|histi
init|=
name|gimp_histogram_get_channel
argument_list|(
name|hist
argument_list|,
name|k
argument_list|,
name|i
argument_list|)
decl_stmt|;
name|sum
operator|+=
name|histi
expr_stmt|;
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
name|RINT
argument_list|(
name|sum
operator|*
literal|255.
operator|/
name|pixels
argument_list|)
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
operator|&
name|hlut
argument_list|,
name|n_channels
argument_list|)
expr_stmt|;
block|}
end_function

begin_function
name|GimpLut
modifier|*
DECL|function|equalize_lut_new (GimpHistogram * histogram,gint n_channels)
name|equalize_lut_new
parameter_list|(
name|GimpHistogram
modifier|*
name|histogram
parameter_list|,
name|gint
name|n_channels
parameter_list|)
block|{
name|GimpLut
modifier|*
name|lut
decl_stmt|;
name|g_return_val_if_fail
argument_list|(
name|histogram
operator|!=
name|NULL
argument_list|,
name|NULL
argument_list|)
expr_stmt|;
name|lut
operator|=
name|gimp_lut_new
argument_list|()
expr_stmt|;
name|equalize_lut_setup
argument_list|(
name|lut
argument_list|,
name|histogram
argument_list|,
name|n_channels
argument_list|)
expr_stmt|;
return|return
name|lut
return|;
block|}
end_function

end_unit

