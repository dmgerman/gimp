begin_unit|revision:0.9.5;language:C;cregit-version:0.0.1
begin_comment
comment|/* LIBGIMP - The GIMP Library   * Copyright (C) 1995-1997 Peter Mattis and Spencer Kimball                  *  * This library is free software; you can redistribute it and/or  * modify it under the terms of the GNU Lesser General Public  * License as published by the Free Software Foundation; either  * version 2 of the License, or (at your option) any later version.  *   * This library is distributed in the hope that it will be useful,   * but WITHOUT ANY WARRANTY; without even the implied warranty of   * MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the GNU    * Library General Public License for more details.  *  * You should have received a copy of the GNU Lesser General Public  * License along with this library; if not, write to the  * Free Software Foundation, Inc., 59 Temple Place - Suite 330,  * Boston, MA 02111-1307, USA.  */
end_comment

begin_include
include|#
directive|include
file|<glib.h>
end_include

begin_include
include|#
directive|include
file|<libgimp/gimpcolorspace.h>
end_include

begin_comment
comment|/*********************************  *   color conversion routines   *  *********************************/
end_comment

begin_function
name|void
DECL|function|gimp_rgb_to_hsv (gint * r,gint * g,gint * b)
name|gimp_rgb_to_hsv
parameter_list|(
name|gint
modifier|*
name|r
parameter_list|,
name|gint
modifier|*
name|g
parameter_list|,
name|gint
modifier|*
name|b
parameter_list|)
block|{
name|gint
name|red
decl_stmt|,
name|green
decl_stmt|,
name|blue
decl_stmt|;
name|gdouble
name|h
decl_stmt|,
name|s
decl_stmt|,
name|v
decl_stmt|;
name|gint
name|min
decl_stmt|,
name|max
decl_stmt|;
name|gint
name|delta
decl_stmt|;
name|h
operator|=
literal|0.0
expr_stmt|;
name|red
operator|=
operator|*
name|r
expr_stmt|;
name|green
operator|=
operator|*
name|g
expr_stmt|;
name|blue
operator|=
operator|*
name|b
expr_stmt|;
if|if
condition|(
name|red
operator|>
name|green
condition|)
block|{
name|max
operator|=
name|MAX
argument_list|(
name|red
argument_list|,
name|blue
argument_list|)
expr_stmt|;
name|min
operator|=
name|MIN
argument_list|(
name|green
argument_list|,
name|blue
argument_list|)
expr_stmt|;
block|}
else|else
block|{
name|max
operator|=
name|MAX
argument_list|(
name|green
argument_list|,
name|blue
argument_list|)
expr_stmt|;
name|min
operator|=
name|MIN
argument_list|(
name|red
argument_list|,
name|blue
argument_list|)
expr_stmt|;
block|}
name|v
operator|=
name|max
expr_stmt|;
if|if
condition|(
name|max
operator|!=
literal|0
condition|)
name|s
operator|=
operator|(
operator|(
name|max
operator|-
name|min
operator|)
operator|*
literal|255
operator|)
operator|/
operator|(
name|gdouble
operator|)
name|max
expr_stmt|;
else|else
name|s
operator|=
literal|0
expr_stmt|;
if|if
condition|(
name|s
operator|==
literal|0
condition|)
name|h
operator|=
literal|0
expr_stmt|;
else|else
block|{
name|delta
operator|=
name|max
operator|-
name|min
expr_stmt|;
if|if
condition|(
name|red
operator|==
name|max
condition|)
name|h
operator|=
operator|(
name|green
operator|-
name|blue
operator|)
operator|/
operator|(
name|gdouble
operator|)
name|delta
expr_stmt|;
elseif|else
if|if
condition|(
name|green
operator|==
name|max
condition|)
name|h
operator|=
literal|2
operator|+
operator|(
name|blue
operator|-
name|red
operator|)
operator|/
operator|(
name|gdouble
operator|)
name|delta
expr_stmt|;
elseif|else
if|if
condition|(
name|blue
operator|==
name|max
condition|)
name|h
operator|=
literal|4
operator|+
operator|(
name|red
operator|-
name|green
operator|)
operator|/
operator|(
name|gdouble
operator|)
name|delta
expr_stmt|;
name|h
operator|*=
literal|42.5
expr_stmt|;
if|if
condition|(
name|h
operator|<
literal|0
condition|)
name|h
operator|+=
literal|255
expr_stmt|;
if|if
condition|(
name|h
operator|>
literal|255
condition|)
name|h
operator|-=
literal|255
expr_stmt|;
block|}
operator|*
name|r
operator|=
name|h
expr_stmt|;
operator|*
name|g
operator|=
name|s
expr_stmt|;
operator|*
name|b
operator|=
name|v
expr_stmt|;
block|}
end_function

begin_function
name|void
DECL|function|gimp_hsv_to_rgb (gint * h,gint * s,gint * v)
name|gimp_hsv_to_rgb
parameter_list|(
name|gint
modifier|*
name|h
parameter_list|,
name|gint
modifier|*
name|s
parameter_list|,
name|gint
modifier|*
name|v
parameter_list|)
block|{
name|gdouble
name|hue
decl_stmt|,
name|saturation
decl_stmt|,
name|value
decl_stmt|;
name|gdouble
name|f
decl_stmt|,
name|p
decl_stmt|,
name|q
decl_stmt|,
name|t
decl_stmt|;
if|if
condition|(
operator|*
name|s
operator|==
literal|0
condition|)
block|{
operator|*
name|h
operator|=
operator|*
name|v
expr_stmt|;
operator|*
name|s
operator|=
operator|*
name|v
expr_stmt|;
operator|*
name|v
operator|=
operator|*
name|v
expr_stmt|;
block|}
else|else
block|{
name|hue
operator|=
operator|*
name|h
operator|*
literal|6.0
operator|/
literal|255.0
expr_stmt|;
name|saturation
operator|=
operator|*
name|s
operator|/
literal|255.0
expr_stmt|;
name|value
operator|=
operator|*
name|v
operator|/
literal|255.0
expr_stmt|;
name|f
operator|=
name|hue
operator|-
operator|(
name|int
operator|)
name|hue
expr_stmt|;
name|p
operator|=
name|value
operator|*
operator|(
literal|1.0
operator|-
name|saturation
operator|)
expr_stmt|;
name|q
operator|=
name|value
operator|*
operator|(
literal|1.0
operator|-
operator|(
name|saturation
operator|*
name|f
operator|)
operator|)
expr_stmt|;
name|t
operator|=
name|value
operator|*
operator|(
literal|1.0
operator|-
operator|(
name|saturation
operator|*
operator|(
literal|1.0
operator|-
name|f
operator|)
operator|)
operator|)
expr_stmt|;
switch|switch
condition|(
operator|(
name|int
operator|)
name|hue
condition|)
block|{
case|case
literal|0
case|:
operator|*
name|h
operator|=
name|value
operator|*
literal|255
expr_stmt|;
operator|*
name|s
operator|=
name|t
operator|*
literal|255
expr_stmt|;
operator|*
name|v
operator|=
name|p
operator|*
literal|255
expr_stmt|;
break|break;
case|case
literal|1
case|:
operator|*
name|h
operator|=
name|q
operator|*
literal|255
expr_stmt|;
operator|*
name|s
operator|=
name|value
operator|*
literal|255
expr_stmt|;
operator|*
name|v
operator|=
name|p
operator|*
literal|255
expr_stmt|;
break|break;
case|case
literal|2
case|:
operator|*
name|h
operator|=
name|p
operator|*
literal|255
expr_stmt|;
operator|*
name|s
operator|=
name|value
operator|*
literal|255
expr_stmt|;
operator|*
name|v
operator|=
name|t
operator|*
literal|255
expr_stmt|;
break|break;
case|case
literal|3
case|:
operator|*
name|h
operator|=
name|p
operator|*
literal|255
expr_stmt|;
operator|*
name|s
operator|=
name|q
operator|*
literal|255
expr_stmt|;
operator|*
name|v
operator|=
name|value
operator|*
literal|255
expr_stmt|;
break|break;
case|case
literal|4
case|:
operator|*
name|h
operator|=
name|t
operator|*
literal|255
expr_stmt|;
operator|*
name|s
operator|=
name|p
operator|*
literal|255
expr_stmt|;
operator|*
name|v
operator|=
name|value
operator|*
literal|255
expr_stmt|;
break|break;
case|case
literal|5
case|:
operator|*
name|h
operator|=
name|value
operator|*
literal|255
expr_stmt|;
operator|*
name|s
operator|=
name|p
operator|*
literal|255
expr_stmt|;
operator|*
name|v
operator|=
name|q
operator|*
literal|255
expr_stmt|;
break|break;
block|}
block|}
block|}
end_function

begin_function
name|void
DECL|function|gimp_rgb_to_hls (gint * r,gint * g,gint * b)
name|gimp_rgb_to_hls
parameter_list|(
name|gint
modifier|*
name|r
parameter_list|,
name|gint
modifier|*
name|g
parameter_list|,
name|gint
modifier|*
name|b
parameter_list|)
block|{
name|gint
name|red
decl_stmt|,
name|green
decl_stmt|,
name|blue
decl_stmt|;
name|gdouble
name|h
decl_stmt|,
name|l
decl_stmt|,
name|s
decl_stmt|;
name|gint
name|min
decl_stmt|,
name|max
decl_stmt|;
name|gint
name|delta
decl_stmt|;
name|red
operator|=
operator|*
name|r
expr_stmt|;
name|green
operator|=
operator|*
name|g
expr_stmt|;
name|blue
operator|=
operator|*
name|b
expr_stmt|;
if|if
condition|(
name|red
operator|>
name|green
condition|)
block|{
name|max
operator|=
name|MAX
argument_list|(
name|red
argument_list|,
name|blue
argument_list|)
expr_stmt|;
name|min
operator|=
name|MIN
argument_list|(
name|green
argument_list|,
name|blue
argument_list|)
expr_stmt|;
block|}
else|else
block|{
name|max
operator|=
name|MAX
argument_list|(
name|green
argument_list|,
name|blue
argument_list|)
expr_stmt|;
name|min
operator|=
name|MIN
argument_list|(
name|red
argument_list|,
name|blue
argument_list|)
expr_stmt|;
block|}
name|l
operator|=
operator|(
name|max
operator|+
name|min
operator|)
operator|/
literal|2.0
expr_stmt|;
if|if
condition|(
name|max
operator|==
name|min
condition|)
block|{
name|s
operator|=
literal|0.0
expr_stmt|;
name|h
operator|=
literal|0.0
expr_stmt|;
block|}
else|else
block|{
name|delta
operator|=
operator|(
name|max
operator|-
name|min
operator|)
expr_stmt|;
if|if
condition|(
name|l
operator|<
literal|128
condition|)
name|s
operator|=
literal|255
operator|*
operator|(
name|gdouble
operator|)
name|delta
operator|/
call|(
name|gdouble
call|)
argument_list|(
name|max
operator|+
name|min
argument_list|)
expr_stmt|;
else|else
name|s
operator|=
literal|255
operator|*
operator|(
name|gdouble
operator|)
name|delta
operator|/
call|(
name|gdouble
call|)
argument_list|(
literal|511
operator|-
name|max
operator|-
name|min
argument_list|)
expr_stmt|;
if|if
condition|(
name|red
operator|==
name|max
condition|)
name|h
operator|=
operator|(
name|green
operator|-
name|blue
operator|)
operator|/
operator|(
name|gdouble
operator|)
name|delta
expr_stmt|;
elseif|else
if|if
condition|(
name|green
operator|==
name|max
condition|)
name|h
operator|=
literal|2
operator|+
operator|(
name|blue
operator|-
name|red
operator|)
operator|/
operator|(
name|gdouble
operator|)
name|delta
expr_stmt|;
else|else
name|h
operator|=
literal|4
operator|+
operator|(
name|red
operator|-
name|green
operator|)
operator|/
operator|(
name|gdouble
operator|)
name|delta
expr_stmt|;
name|h
operator|=
name|h
operator|*
literal|42.5
expr_stmt|;
if|if
condition|(
name|h
operator|<
literal|0
condition|)
name|h
operator|+=
literal|255
expr_stmt|;
elseif|else
if|if
condition|(
name|h
operator|>
literal|255
condition|)
name|h
operator|-=
literal|255
expr_stmt|;
block|}
operator|*
name|r
operator|=
name|h
expr_stmt|;
operator|*
name|g
operator|=
name|l
expr_stmt|;
operator|*
name|b
operator|=
name|s
expr_stmt|;
block|}
end_function

begin_function
name|gint
DECL|function|gimp_rgb_to_l (gint red,gint green,gint blue)
name|gimp_rgb_to_l
parameter_list|(
name|gint
name|red
parameter_list|,
name|gint
name|green
parameter_list|,
name|gint
name|blue
parameter_list|)
block|{
name|gint
name|min
decl_stmt|,
name|max
decl_stmt|;
if|if
condition|(
name|red
operator|>
name|green
condition|)
block|{
name|max
operator|=
name|MAX
argument_list|(
name|red
argument_list|,
name|blue
argument_list|)
expr_stmt|;
name|min
operator|=
name|MIN
argument_list|(
name|green
argument_list|,
name|blue
argument_list|)
expr_stmt|;
block|}
else|else
block|{
name|max
operator|=
name|MAX
argument_list|(
name|green
argument_list|,
name|blue
argument_list|)
expr_stmt|;
name|min
operator|=
name|MIN
argument_list|(
name|red
argument_list|,
name|blue
argument_list|)
expr_stmt|;
block|}
return|return
operator|(
name|max
operator|+
name|min
operator|)
operator|/
literal|2.0
return|;
block|}
end_function

begin_function
specifier|static
name|gint
DECL|function|gimp_hls_value (gdouble n1,gdouble n2,gdouble hue)
name|gimp_hls_value
parameter_list|(
name|gdouble
name|n1
parameter_list|,
name|gdouble
name|n2
parameter_list|,
name|gdouble
name|hue
parameter_list|)
block|{
name|gdouble
name|value
decl_stmt|;
if|if
condition|(
name|hue
operator|>
literal|255
condition|)
name|hue
operator|-=
literal|255
expr_stmt|;
elseif|else
if|if
condition|(
name|hue
operator|<
literal|0
condition|)
name|hue
operator|+=
literal|255
expr_stmt|;
if|if
condition|(
name|hue
operator|<
literal|42.5
condition|)
name|value
operator|=
name|n1
operator|+
operator|(
name|n2
operator|-
name|n1
operator|)
operator|*
operator|(
name|hue
operator|/
literal|42.5
operator|)
expr_stmt|;
elseif|else
if|if
condition|(
name|hue
operator|<
literal|127.5
condition|)
name|value
operator|=
name|n2
expr_stmt|;
elseif|else
if|if
condition|(
name|hue
operator|<
literal|170
condition|)
name|value
operator|=
name|n1
operator|+
operator|(
name|n2
operator|-
name|n1
operator|)
operator|*
operator|(
operator|(
literal|170
operator|-
name|hue
operator|)
operator|/
literal|42.5
operator|)
expr_stmt|;
else|else
name|value
operator|=
name|n1
expr_stmt|;
return|return
call|(
name|gint
call|)
argument_list|(
name|value
operator|*
literal|255
argument_list|)
return|;
block|}
end_function

begin_function
name|void
DECL|function|gimp_hls_to_rgb (gint * h,gint * l,gint * s)
name|gimp_hls_to_rgb
parameter_list|(
name|gint
modifier|*
name|h
parameter_list|,
name|gint
modifier|*
name|l
parameter_list|,
name|gint
modifier|*
name|s
parameter_list|)
block|{
name|gdouble
name|hue
decl_stmt|,
name|lightness
decl_stmt|,
name|saturation
decl_stmt|;
name|gdouble
name|m1
decl_stmt|,
name|m2
decl_stmt|;
name|hue
operator|=
operator|*
name|h
expr_stmt|;
name|lightness
operator|=
operator|*
name|l
expr_stmt|;
name|saturation
operator|=
operator|*
name|s
expr_stmt|;
if|if
condition|(
name|saturation
operator|==
literal|0
condition|)
block|{
comment|/*  achromatic case  */
operator|*
name|h
operator|=
name|lightness
expr_stmt|;
operator|*
name|l
operator|=
name|lightness
expr_stmt|;
operator|*
name|s
operator|=
name|lightness
expr_stmt|;
block|}
else|else
block|{
if|if
condition|(
name|lightness
operator|<
literal|128
condition|)
name|m2
operator|=
operator|(
name|lightness
operator|*
operator|(
literal|255
operator|+
name|saturation
operator|)
operator|)
operator|/
literal|65025.0
expr_stmt|;
else|else
name|m2
operator|=
operator|(
name|lightness
operator|+
name|saturation
operator|-
operator|(
name|lightness
operator|*
name|saturation
operator|)
operator|/
literal|255.0
operator|)
operator|/
literal|255.0
expr_stmt|;
name|m1
operator|=
operator|(
name|lightness
operator|/
literal|127.5
operator|)
operator|-
name|m2
expr_stmt|;
comment|/*  chromatic case  */
operator|*
name|h
operator|=
name|gimp_hls_value
argument_list|(
name|m1
argument_list|,
name|m2
argument_list|,
name|hue
operator|+
literal|85
argument_list|)
expr_stmt|;
operator|*
name|l
operator|=
name|gimp_hls_value
argument_list|(
name|m1
argument_list|,
name|m2
argument_list|,
name|hue
argument_list|)
expr_stmt|;
operator|*
name|s
operator|=
name|gimp_hls_value
argument_list|(
name|m1
argument_list|,
name|m2
argument_list|,
name|hue
operator|-
literal|85
argument_list|)
expr_stmt|;
block|}
block|}
end_function

begin_function
name|void
DECL|function|gimp_rgb_to_hsv_double (gdouble * r,gdouble * g,gdouble * b)
name|gimp_rgb_to_hsv_double
parameter_list|(
name|gdouble
modifier|*
name|r
parameter_list|,
name|gdouble
modifier|*
name|g
parameter_list|,
name|gdouble
modifier|*
name|b
parameter_list|)
block|{
name|gdouble
name|red
decl_stmt|,
name|green
decl_stmt|,
name|blue
decl_stmt|;
name|gdouble
name|h
decl_stmt|,
name|s
decl_stmt|,
name|v
decl_stmt|;
name|gdouble
name|min
decl_stmt|,
name|max
decl_stmt|;
name|gdouble
name|delta
decl_stmt|;
name|red
operator|=
operator|*
name|r
expr_stmt|;
name|green
operator|=
operator|*
name|g
expr_stmt|;
name|blue
operator|=
operator|*
name|b
expr_stmt|;
name|h
operator|=
literal|0.0
expr_stmt|;
comment|/* Shut up -Wall */
if|if
condition|(
name|red
operator|>
name|green
condition|)
block|{
name|max
operator|=
name|MAX
argument_list|(
name|red
argument_list|,
name|blue
argument_list|)
expr_stmt|;
name|min
operator|=
name|MIN
argument_list|(
name|green
argument_list|,
name|blue
argument_list|)
expr_stmt|;
block|}
else|else
block|{
name|max
operator|=
name|MAX
argument_list|(
name|green
argument_list|,
name|blue
argument_list|)
expr_stmt|;
name|min
operator|=
name|MIN
argument_list|(
name|red
argument_list|,
name|blue
argument_list|)
expr_stmt|;
block|}
name|v
operator|=
name|max
expr_stmt|;
if|if
condition|(
name|max
operator|!=
literal|0.0
condition|)
name|s
operator|=
operator|(
name|max
operator|-
name|min
operator|)
operator|/
name|max
expr_stmt|;
else|else
name|s
operator|=
literal|0.0
expr_stmt|;
if|if
condition|(
name|s
operator|==
literal|0.0
condition|)
block|{
name|h
operator|=
literal|0.0
expr_stmt|;
block|}
else|else
block|{
name|delta
operator|=
name|max
operator|-
name|min
expr_stmt|;
if|if
condition|(
name|red
operator|==
name|max
condition|)
name|h
operator|=
operator|(
name|green
operator|-
name|blue
operator|)
operator|/
name|delta
expr_stmt|;
elseif|else
if|if
condition|(
name|green
operator|==
name|max
condition|)
name|h
operator|=
literal|2
operator|+
operator|(
name|blue
operator|-
name|red
operator|)
operator|/
name|delta
expr_stmt|;
elseif|else
if|if
condition|(
name|blue
operator|==
name|max
condition|)
name|h
operator|=
literal|4
operator|+
operator|(
name|red
operator|-
name|green
operator|)
operator|/
name|delta
expr_stmt|;
name|h
operator|/=
literal|6.0
expr_stmt|;
if|if
condition|(
name|h
operator|<
literal|0.0
condition|)
name|h
operator|+=
literal|1.0
expr_stmt|;
elseif|else
if|if
condition|(
name|h
operator|>
literal|1.0
condition|)
name|h
operator|-=
literal|1.0
expr_stmt|;
block|}
operator|*
name|r
operator|=
name|h
expr_stmt|;
operator|*
name|g
operator|=
name|s
expr_stmt|;
operator|*
name|b
operator|=
name|v
expr_stmt|;
block|}
end_function

begin_function
name|void
DECL|function|gimp_hsv_to_rgb_double (gdouble * h,gdouble * s,gdouble * v)
name|gimp_hsv_to_rgb_double
parameter_list|(
name|gdouble
modifier|*
name|h
parameter_list|,
name|gdouble
modifier|*
name|s
parameter_list|,
name|gdouble
modifier|*
name|v
parameter_list|)
block|{
name|gdouble
name|hue
decl_stmt|,
name|saturation
decl_stmt|,
name|value
decl_stmt|;
name|gdouble
name|f
decl_stmt|,
name|p
decl_stmt|,
name|q
decl_stmt|,
name|t
decl_stmt|;
if|if
condition|(
operator|*
name|s
operator|==
literal|0.0
condition|)
block|{
operator|*
name|h
operator|=
operator|*
name|v
expr_stmt|;
operator|*
name|s
operator|=
operator|*
name|v
expr_stmt|;
operator|*
name|v
operator|=
operator|*
name|v
expr_stmt|;
comment|/* heh */
block|}
else|else
block|{
name|hue
operator|=
operator|*
name|h
operator|*
literal|6.0
expr_stmt|;
name|saturation
operator|=
operator|*
name|s
expr_stmt|;
name|value
operator|=
operator|*
name|v
expr_stmt|;
if|if
condition|(
name|hue
operator|==
literal|6.0
condition|)
name|hue
operator|=
literal|0.0
expr_stmt|;
name|f
operator|=
name|hue
operator|-
operator|(
name|gint
operator|)
name|hue
expr_stmt|;
name|p
operator|=
name|value
operator|*
operator|(
literal|1.0
operator|-
name|saturation
operator|)
expr_stmt|;
name|q
operator|=
name|value
operator|*
operator|(
literal|1.0
operator|-
name|saturation
operator|*
name|f
operator|)
expr_stmt|;
name|t
operator|=
name|value
operator|*
operator|(
literal|1.0
operator|-
name|saturation
operator|*
operator|(
literal|1.0
operator|-
name|f
operator|)
operator|)
expr_stmt|;
switch|switch
condition|(
operator|(
name|gint
operator|)
name|hue
condition|)
block|{
case|case
literal|0
case|:
operator|*
name|h
operator|=
name|value
expr_stmt|;
operator|*
name|s
operator|=
name|t
expr_stmt|;
operator|*
name|v
operator|=
name|p
expr_stmt|;
break|break;
case|case
literal|1
case|:
operator|*
name|h
operator|=
name|q
expr_stmt|;
operator|*
name|s
operator|=
name|value
expr_stmt|;
operator|*
name|v
operator|=
name|p
expr_stmt|;
break|break;
case|case
literal|2
case|:
operator|*
name|h
operator|=
name|p
expr_stmt|;
operator|*
name|s
operator|=
name|value
expr_stmt|;
operator|*
name|v
operator|=
name|t
expr_stmt|;
break|break;
case|case
literal|3
case|:
operator|*
name|h
operator|=
name|p
expr_stmt|;
operator|*
name|s
operator|=
name|q
expr_stmt|;
operator|*
name|v
operator|=
name|value
expr_stmt|;
break|break;
case|case
literal|4
case|:
operator|*
name|h
operator|=
name|t
expr_stmt|;
operator|*
name|s
operator|=
name|p
expr_stmt|;
operator|*
name|v
operator|=
name|value
expr_stmt|;
break|break;
case|case
literal|5
case|:
operator|*
name|h
operator|=
name|value
expr_stmt|;
operator|*
name|s
operator|=
name|p
expr_stmt|;
operator|*
name|v
operator|=
name|q
expr_stmt|;
break|break;
block|}
block|}
block|}
end_function

begin_function
name|void
DECL|function|gimp_rgb_to_hsv4 (guchar * rgb,gdouble * hue,gdouble * sat,gdouble * val)
name|gimp_rgb_to_hsv4
parameter_list|(
name|guchar
modifier|*
name|rgb
parameter_list|,
name|gdouble
modifier|*
name|hue
parameter_list|,
name|gdouble
modifier|*
name|sat
parameter_list|,
name|gdouble
modifier|*
name|val
parameter_list|)
block|{
name|gdouble
name|red
decl_stmt|,
name|green
decl_stmt|,
name|blue
decl_stmt|;
name|gdouble
name|h
decl_stmt|,
name|s
decl_stmt|,
name|v
decl_stmt|;
name|gdouble
name|min
decl_stmt|,
name|max
decl_stmt|;
name|gdouble
name|delta
decl_stmt|;
name|red
operator|=
name|rgb
index|[
literal|0
index|]
operator|/
literal|255.0
expr_stmt|;
name|green
operator|=
name|rgb
index|[
literal|1
index|]
operator|/
literal|255.0
expr_stmt|;
name|blue
operator|=
name|rgb
index|[
literal|2
index|]
operator|/
literal|255.0
expr_stmt|;
name|h
operator|=
literal|0.0
expr_stmt|;
comment|/* Shut up -Wall */
if|if
condition|(
name|red
operator|>
name|green
condition|)
block|{
if|if
condition|(
name|red
operator|>
name|blue
condition|)
name|max
operator|=
name|red
expr_stmt|;
else|else
name|max
operator|=
name|blue
expr_stmt|;
if|if
condition|(
name|green
operator|<
name|blue
condition|)
name|min
operator|=
name|green
expr_stmt|;
else|else
name|min
operator|=
name|blue
expr_stmt|;
block|}
else|else
block|{
if|if
condition|(
name|green
operator|>
name|blue
condition|)
name|max
operator|=
name|green
expr_stmt|;
else|else
name|max
operator|=
name|blue
expr_stmt|;
if|if
condition|(
name|red
operator|<
name|blue
condition|)
name|min
operator|=
name|red
expr_stmt|;
else|else
name|min
operator|=
name|blue
expr_stmt|;
block|}
name|v
operator|=
name|max
expr_stmt|;
if|if
condition|(
name|max
operator|!=
literal|0.0
condition|)
name|s
operator|=
operator|(
name|max
operator|-
name|min
operator|)
operator|/
name|max
expr_stmt|;
else|else
name|s
operator|=
literal|0.0
expr_stmt|;
if|if
condition|(
name|s
operator|==
literal|0.0
condition|)
name|h
operator|=
literal|0.0
expr_stmt|;
else|else
block|{
name|delta
operator|=
name|max
operator|-
name|min
expr_stmt|;
if|if
condition|(
name|red
operator|==
name|max
condition|)
name|h
operator|=
operator|(
name|green
operator|-
name|blue
operator|)
operator|/
name|delta
expr_stmt|;
elseif|else
if|if
condition|(
name|green
operator|==
name|max
condition|)
name|h
operator|=
literal|2
operator|+
operator|(
name|blue
operator|-
name|red
operator|)
operator|/
name|delta
expr_stmt|;
elseif|else
if|if
condition|(
name|blue
operator|==
name|max
condition|)
name|h
operator|=
literal|4
operator|+
operator|(
name|red
operator|-
name|green
operator|)
operator|/
name|delta
expr_stmt|;
name|h
operator|/=
literal|6.0
expr_stmt|;
if|if
condition|(
name|h
operator|<
literal|0.0
condition|)
name|h
operator|+=
literal|1.0
expr_stmt|;
elseif|else
if|if
condition|(
name|h
operator|>
literal|1.0
condition|)
name|h
operator|-=
literal|1.0
expr_stmt|;
block|}
operator|*
name|hue
operator|=
name|h
expr_stmt|;
operator|*
name|sat
operator|=
name|s
expr_stmt|;
operator|*
name|val
operator|=
name|v
expr_stmt|;
block|}
end_function

begin_function
name|void
DECL|function|gimp_hsv_to_rgb4 (guchar * rgb,gdouble h,gdouble s,gdouble v)
name|gimp_hsv_to_rgb4
parameter_list|(
name|guchar
modifier|*
name|rgb
parameter_list|,
name|gdouble
name|h
parameter_list|,
name|gdouble
name|s
parameter_list|,
name|gdouble
name|v
parameter_list|)
block|{
name|gdouble
name|hue
decl_stmt|,
name|saturation
decl_stmt|,
name|value
decl_stmt|;
name|gdouble
name|f
decl_stmt|,
name|p
decl_stmt|,
name|q
decl_stmt|,
name|t
decl_stmt|;
if|if
condition|(
name|s
operator|==
literal|0.0
condition|)
block|{
name|h
operator|=
name|v
expr_stmt|;
name|s
operator|=
name|v
expr_stmt|;
name|v
operator|=
name|v
expr_stmt|;
comment|/* heh */
block|}
else|else
block|{
name|hue
operator|=
name|h
operator|*
literal|6.0
expr_stmt|;
name|saturation
operator|=
name|s
expr_stmt|;
name|value
operator|=
name|v
expr_stmt|;
if|if
condition|(
name|hue
operator|==
literal|6.0
condition|)
name|hue
operator|=
literal|0.0
expr_stmt|;
name|f
operator|=
name|hue
operator|-
operator|(
name|int
operator|)
name|hue
expr_stmt|;
name|p
operator|=
name|value
operator|*
operator|(
literal|1.0
operator|-
name|saturation
operator|)
expr_stmt|;
name|q
operator|=
name|value
operator|*
operator|(
literal|1.0
operator|-
name|saturation
operator|*
name|f
operator|)
expr_stmt|;
name|t
operator|=
name|value
operator|*
operator|(
literal|1.0
operator|-
name|saturation
operator|*
operator|(
literal|1.0
operator|-
name|f
operator|)
operator|)
expr_stmt|;
switch|switch
condition|(
operator|(
name|int
operator|)
name|hue
condition|)
block|{
case|case
literal|0
case|:
name|h
operator|=
name|value
expr_stmt|;
name|s
operator|=
name|t
expr_stmt|;
name|v
operator|=
name|p
expr_stmt|;
break|break;
case|case
literal|1
case|:
name|h
operator|=
name|q
expr_stmt|;
name|s
operator|=
name|value
expr_stmt|;
name|v
operator|=
name|p
expr_stmt|;
break|break;
case|case
literal|2
case|:
name|h
operator|=
name|p
expr_stmt|;
name|s
operator|=
name|value
expr_stmt|;
name|v
operator|=
name|t
expr_stmt|;
break|break;
case|case
literal|3
case|:
name|h
operator|=
name|p
expr_stmt|;
name|s
operator|=
name|q
expr_stmt|;
name|v
operator|=
name|value
expr_stmt|;
break|break;
case|case
literal|4
case|:
name|h
operator|=
name|t
expr_stmt|;
name|s
operator|=
name|p
expr_stmt|;
name|v
operator|=
name|value
expr_stmt|;
break|break;
case|case
literal|5
case|:
name|h
operator|=
name|value
expr_stmt|;
name|s
operator|=
name|p
expr_stmt|;
name|v
operator|=
name|q
expr_stmt|;
break|break;
block|}
block|}
name|rgb
index|[
literal|0
index|]
operator|=
name|h
operator|*
literal|255
expr_stmt|;
name|rgb
index|[
literal|1
index|]
operator|=
name|s
operator|*
literal|255
expr_stmt|;
name|rgb
index|[
literal|2
index|]
operator|=
name|v
operator|*
literal|255
expr_stmt|;
block|}
end_function

end_unit

