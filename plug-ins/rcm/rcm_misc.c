begin_unit|revision:0.9.5;language:C;cregit-version:0.0.1
begin_comment
comment|/*  * Copyright (C) 1995 Spencer Kimball and Peter Mattis  *  * This is a plug-in for the GIMP.  *  * Colormap-Rotation plug-in. Exchanges two color ranges.  *  * Copyright (C) 1999 Sven Anders (anderss@fmi.uni-passau.de)  *                    Based on code from Pavel Grinfeld (pavel@ml.com)  *  *  * This program is free software; you can redistribute it and/or modify  * it under the terms of the GNU General Public License as published by  * the Free Software Foundation; either version 2 of the License, or  * (at your option) any later version.  *  * This program is distributed in the hope that it will be useful,  * but WITHOUT ANY WARRANTY; without even the implied warranty of  * MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the  * GNU General Public License for more details.  *  * You should have received a copy of the GNU General Public License  * along with this program; if not, write to the Free Software  * Foundation, Inc., 59 Temple Place - Suite 330, Boston, MA 02111-1307, USA.  */
end_comment

begin_comment
comment|/*----------------------------------------------------------------------------  * Change log:  *  * Version 2.0, 04 April 1999.  *  Nearly complete rewrite, made plug-in stable.  *  (Works with GIMP 1.1 and GTK+ 1.2)  *  * Version 1.0, 27 March 1997.  *  Initial (unstable) release by Pavel Grinfeld  *  *----------------------------------------------------------------------------*/
end_comment

begin_include
include|#
directive|include
file|"config.h"
end_include

begin_include
include|#
directive|include
file|"libgimp/gimp.h"
end_include

begin_include
include|#
directive|include
file|"libgimp/gimpui.h"
end_include

begin_include
include|#
directive|include
file|"rcm.h"
end_include

begin_include
include|#
directive|include
file|"rcm_misc.h"
end_include

begin_include
include|#
directive|include
file|"rcm_gdk.h"
end_include

begin_function
name|float
DECL|function|arctg (float y,float x)
name|arctg
parameter_list|(
name|float
name|y
parameter_list|,
name|float
name|x
parameter_list|)
block|{
name|float
name|temp
init|=
name|atan2
argument_list|(
name|y
argument_list|,
name|x
argument_list|)
decl_stmt|;
return|return
operator|(
name|temp
operator|<
literal|0
operator|)
condition|?
operator|(
name|temp
operator|+
name|TP
operator|)
else|:
name|temp
return|;
block|}
end_function

begin_function
name|float
DECL|function|min_prox (float alpha,float beta,float angle)
name|min_prox
parameter_list|(
name|float
name|alpha
parameter_list|,
name|float
name|beta
parameter_list|,
name|float
name|angle
parameter_list|)
block|{
name|gfloat
name|temp1
init|=
name|MIN
argument_list|(
name|angle_mod_2PI
argument_list|(
name|alpha
operator|-
name|angle
argument_list|)
argument_list|,
name|TP
operator|-
name|angle_mod_2PI
argument_list|(
name|alpha
operator|-
name|angle
argument_list|)
argument_list|)
decl_stmt|;
name|gfloat
name|temp2
init|=
name|MIN
argument_list|(
name|angle_mod_2PI
argument_list|(
name|beta
operator|-
name|angle
argument_list|)
argument_list|,
name|TP
operator|-
name|angle_mod_2PI
argument_list|(
name|beta
operator|-
name|angle
argument_list|)
argument_list|)
decl_stmt|;
return|return
name|MIN
argument_list|(
name|temp1
argument_list|,
name|temp2
argument_list|)
return|;
block|}
end_function

begin_function
name|float
modifier|*
DECL|function|closest (float * alpha,float * beta,float angle)
name|closest
parameter_list|(
name|float
modifier|*
name|alpha
parameter_list|,
name|float
modifier|*
name|beta
parameter_list|,
name|float
name|angle
parameter_list|)
block|{
name|gfloat
name|temp_alpha
init|=
name|MIN
argument_list|(
name|angle_mod_2PI
argument_list|(
operator|*
name|alpha
operator|-
name|angle
argument_list|)
argument_list|,
name|TP
operator|-
name|angle_mod_2PI
argument_list|(
operator|*
name|alpha
operator|-
name|angle
argument_list|)
argument_list|)
decl_stmt|;
name|gfloat
name|temp_beta
init|=
name|MIN
argument_list|(
name|angle_mod_2PI
argument_list|(
operator|*
name|beta
operator|-
name|angle
argument_list|)
argument_list|,
name|TP
operator|-
name|angle_mod_2PI
argument_list|(
operator|*
name|beta
operator|-
name|angle
argument_list|)
argument_list|)
decl_stmt|;
if|if
condition|(
name|temp_alpha
operator|-
name|temp_beta
operator|<
literal|0
condition|)
return|return
name|alpha
return|;
else|else
return|return
name|beta
return|;
block|}
end_function

begin_function
name|float
DECL|function|angle_mod_2PI (float angle)
name|angle_mod_2PI
parameter_list|(
name|float
name|angle
parameter_list|)
block|{
if|if
condition|(
name|angle
operator|<
literal|0
condition|)
return|return
name|angle
operator|+
name|TP
return|;
elseif|else
if|if
condition|(
name|angle
operator|>
name|TP
condition|)
return|return
name|angle
operator|-
name|TP
return|;
else|else
return|return
name|angle
return|;
block|}
end_function

begin_comment
comment|/* supporting routines  */
end_comment

begin_function
name|float
DECL|function|rcm_linear (float A,float B,float C,float D,float x)
name|rcm_linear
parameter_list|(
name|float
name|A
parameter_list|,
name|float
name|B
parameter_list|,
name|float
name|C
parameter_list|,
name|float
name|D
parameter_list|,
name|float
name|x
parameter_list|)
block|{
if|if
condition|(
name|B
operator|>
name|A
condition|)
block|{
if|if
condition|(
name|A
operator|<=
name|x
operator|&&
name|x
operator|<=
name|B
condition|)
return|return
name|C
operator|+
operator|(
name|D
operator|-
name|C
operator|)
operator|/
operator|(
name|B
operator|-
name|A
operator|)
operator|*
operator|(
name|x
operator|-
name|A
operator|)
return|;
elseif|else
if|if
condition|(
name|A
operator|<=
name|x
operator|+
name|TP
operator|&&
name|x
operator|+
name|TP
operator|<=
name|B
condition|)
return|return
name|C
operator|+
operator|(
name|D
operator|-
name|C
operator|)
operator|/
operator|(
name|B
operator|-
name|A
operator|)
operator|*
operator|(
name|x
operator|+
name|TP
operator|-
name|A
operator|)
return|;
else|else
return|return
name|x
return|;
block|}
else|else
block|{
if|if
condition|(
name|B
operator|<=
name|x
operator|&&
name|x
operator|<=
name|A
condition|)
return|return
name|C
operator|+
operator|(
name|D
operator|-
name|C
operator|)
operator|/
operator|(
name|B
operator|-
name|A
operator|)
operator|*
operator|(
name|x
operator|-
name|A
operator|)
return|;
elseif|else
if|if
condition|(
name|B
operator|<=
name|x
operator|+
name|TP
operator|&&
name|x
operator|+
name|TP
operator|<=
name|A
condition|)
return|return
name|C
operator|+
operator|(
name|D
operator|-
name|C
operator|)
operator|/
operator|(
name|B
operator|-
name|A
operator|)
operator|*
operator|(
name|x
operator|+
name|TP
operator|-
name|A
operator|)
return|;
else|else
return|return
name|x
return|;
block|}
block|}
end_function

begin_function
name|float
DECL|function|rcm_left_end (RcmAngle * angle)
name|rcm_left_end
parameter_list|(
name|RcmAngle
modifier|*
name|angle
parameter_list|)
block|{
name|gfloat
name|alpha
init|=
name|angle
operator|->
name|alpha
decl_stmt|;
name|gfloat
name|beta
init|=
name|angle
operator|->
name|beta
decl_stmt|;
name|gint
name|cw_ccw
init|=
name|angle
operator|->
name|cw_ccw
decl_stmt|;
switch|switch
condition|(
name|cw_ccw
condition|)
block|{
case|case
operator|(
operator|-
literal|1
operator|)
case|:
if|if
condition|(
name|alpha
operator|<
name|beta
condition|)
return|return
name|alpha
operator|+
name|TP
return|;
default|default:
return|return
name|alpha
return|;
comment|/* 1 */
block|}
block|}
end_function

begin_function
name|float
DECL|function|rcm_right_end (RcmAngle * angle)
name|rcm_right_end
parameter_list|(
name|RcmAngle
modifier|*
name|angle
parameter_list|)
block|{
name|gfloat
name|alpha
init|=
name|angle
operator|->
name|alpha
decl_stmt|;
name|gfloat
name|beta
init|=
name|angle
operator|->
name|beta
decl_stmt|;
name|gint
name|cw_ccw
init|=
name|angle
operator|->
name|cw_ccw
decl_stmt|;
switch|switch
condition|(
name|cw_ccw
condition|)
block|{
case|case
literal|1
case|:
if|if
condition|(
name|beta
operator|<
name|alpha
condition|)
return|return
name|beta
operator|+
name|TP
return|;
default|default:
return|return
name|beta
return|;
comment|/* -1 */
block|}
block|}
end_function

begin_function
name|float
DECL|function|rcm_angle_inside_slice (float angle,RcmAngle * slice)
name|rcm_angle_inside_slice
parameter_list|(
name|float
name|angle
parameter_list|,
name|RcmAngle
modifier|*
name|slice
parameter_list|)
block|{
return|return
name|angle_mod_2PI
argument_list|(
name|slice
operator|->
name|cw_ccw
operator|*
operator|(
name|slice
operator|->
name|beta
operator|-
name|angle
operator|)
argument_list|)
operator|/
name|angle_mod_2PI
argument_list|(
name|slice
operator|->
name|cw_ccw
operator|*
operator|(
name|slice
operator|->
name|beta
operator|-
name|slice
operator|->
name|alpha
operator|)
argument_list|)
return|;
block|}
end_function

begin_function
name|gboolean
DECL|function|rcm_is_gray (float s)
name|rcm_is_gray
parameter_list|(
name|float
name|s
parameter_list|)
block|{
return|return
operator|(
name|s
operator|<=
name|Current
operator|.
name|Gray
operator|->
name|gray_sat
operator|)
return|;
block|}
end_function

begin_comment
comment|/* reduce image/selection for preview */
end_comment

begin_function
name|ReducedImage
modifier|*
DECL|function|rcm_reduce_image (GimpDrawable * drawable,GimpDrawable * mask,gint LongerSize,gint Slctn)
name|rcm_reduce_image
parameter_list|(
name|GimpDrawable
modifier|*
name|drawable
parameter_list|,
name|GimpDrawable
modifier|*
name|mask
parameter_list|,
name|gint
name|LongerSize
parameter_list|,
name|gint
name|Slctn
parameter_list|)
block|{
name|guint32
name|gimage
decl_stmt|;
name|GimpPixelRgn
name|srcPR
decl_stmt|,
name|srcMask
decl_stmt|;
name|ReducedImage
modifier|*
name|temp
decl_stmt|;
name|guchar
modifier|*
name|tempRGB
decl_stmt|,
modifier|*
name|src_row
decl_stmt|,
modifier|*
name|tempmask
decl_stmt|,
modifier|*
name|src_mask_row
decl_stmt|;
name|gint
name|i
decl_stmt|,
name|j
decl_stmt|,
name|whichcol
decl_stmt|,
name|whichrow
decl_stmt|,
name|x1
decl_stmt|,
name|x2
decl_stmt|,
name|y1
decl_stmt|,
name|y2
decl_stmt|;
name|gint
name|RH
decl_stmt|,
name|RW
decl_stmt|,
name|width
decl_stmt|,
name|height
decl_stmt|,
name|bytes
decl_stmt|;
name|gint
name|NoSelectionMade
decl_stmt|;
name|gint
name|offx
decl_stmt|,
name|offy
decl_stmt|;
name|gdouble
modifier|*
name|tempHSV
decl_stmt|,
name|H
decl_stmt|,
name|S
decl_stmt|,
name|V
decl_stmt|;
name|bytes
operator|=
name|drawable
operator|->
name|bpp
expr_stmt|;
name|temp
operator|=
name|g_new0
argument_list|(
name|ReducedImage
argument_list|,
literal|1
argument_list|)
expr_stmt|;
comment|/* get bounds of image or selection */
name|gimp_drawable_mask_bounds
argument_list|(
name|drawable
operator|->
name|drawable_id
argument_list|,
operator|&
name|x1
argument_list|,
operator|&
name|y1
argument_list|,
operator|&
name|x2
argument_list|,
operator|&
name|y2
argument_list|)
expr_stmt|;
if|if
condition|(
operator|(
operator|(
name|x2
operator|-
name|x1
operator|)
operator|!=
name|drawable
operator|->
name|width
operator|)
operator|||
operator|(
operator|(
name|y2
operator|-
name|y1
operator|)
operator|!=
name|drawable
operator|->
name|height
operator|)
condition|)
name|NoSelectionMade
operator|=
name|FALSE
expr_stmt|;
else|else
name|NoSelectionMade
operator|=
name|TRUE
expr_stmt|;
switch|switch
condition|(
name|Slctn
condition|)
block|{
case|case
name|ENTIRE_IMAGE
case|:
name|x1
operator|=
literal|0
expr_stmt|;
name|x2
operator|=
name|drawable
operator|->
name|width
expr_stmt|;
name|y1
operator|=
literal|0
expr_stmt|;
name|y2
operator|=
name|drawable
operator|->
name|height
expr_stmt|;
break|break;
case|case
name|SELECTION_IN_CONTEXT
case|:
name|x1
operator|=
name|MAX
argument_list|(
literal|0
argument_list|,
name|x1
operator|-
operator|(
name|x2
operator|-
name|x1
operator|)
operator|/
literal|2.0
argument_list|)
expr_stmt|;
name|x2
operator|=
name|MIN
argument_list|(
name|drawable
operator|->
name|width
argument_list|,
name|x2
operator|+
operator|(
name|x2
operator|-
name|x1
operator|)
operator|/
literal|2.0
argument_list|)
expr_stmt|;
name|y1
operator|=
name|MAX
argument_list|(
literal|0
argument_list|,
name|y1
operator|-
operator|(
name|y2
operator|-
name|y1
operator|)
operator|/
literal|2.0
argument_list|)
expr_stmt|;
name|y2
operator|=
name|MIN
argument_list|(
name|drawable
operator|->
name|height
argument_list|,
name|y2
operator|+
operator|(
name|y2
operator|-
name|y1
operator|)
operator|/
literal|2.0
argument_list|)
expr_stmt|;
break|break;
default|default:
break|break;
comment|/* take selection dimensions */
block|}
comment|/* clamp to image size since this is the size of the mask */
name|gimp_drawable_offsets
argument_list|(
name|drawable
operator|->
name|drawable_id
argument_list|,
operator|&
name|offx
argument_list|,
operator|&
name|offy
argument_list|)
expr_stmt|;
name|gimage
operator|=
name|gimp_drawable_get_image
argument_list|(
name|drawable
operator|->
name|drawable_id
argument_list|)
expr_stmt|;
name|x1
operator|=
name|CLAMP
argument_list|(
name|x1
argument_list|,
operator|-
name|offx
argument_list|,
name|gimp_image_width
argument_list|(
name|gimage
argument_list|)
operator|-
name|offx
argument_list|)
expr_stmt|;
name|x2
operator|=
name|CLAMP
argument_list|(
name|x2
argument_list|,
operator|-
name|offx
argument_list|,
name|gimp_image_width
argument_list|(
name|gimage
argument_list|)
operator|-
name|offx
argument_list|)
expr_stmt|;
name|y1
operator|=
name|CLAMP
argument_list|(
name|y1
argument_list|,
operator|-
name|offy
argument_list|,
name|gimp_image_height
argument_list|(
name|gimage
argument_list|)
operator|-
name|offy
argument_list|)
expr_stmt|;
name|y2
operator|=
name|CLAMP
argument_list|(
name|y2
argument_list|,
operator|-
name|offy
argument_list|,
name|gimp_image_height
argument_list|(
name|gimage
argument_list|)
operator|-
name|offy
argument_list|)
expr_stmt|;
comment|/* calculate size of preview */
name|width
operator|=
name|x2
operator|-
name|x1
expr_stmt|;
name|height
operator|=
name|y2
operator|-
name|y1
expr_stmt|;
if|if
condition|(
name|width
operator|<
literal|1
operator|||
name|height
operator|<
literal|1
condition|)
return|return
name|temp
return|;
if|if
condition|(
name|width
operator|>
name|height
condition|)
block|{
name|RW
operator|=
name|LongerSize
expr_stmt|;
name|RH
operator|=
operator|(
name|float
operator|)
name|height
operator|*
operator|(
name|float
operator|)
name|LongerSize
operator|/
operator|(
name|float
operator|)
name|width
expr_stmt|;
block|}
else|else
block|{
name|RH
operator|=
name|LongerSize
expr_stmt|;
name|RW
operator|=
operator|(
name|float
operator|)
name|width
operator|*
operator|(
name|float
operator|)
name|LongerSize
operator|/
operator|(
name|float
operator|)
name|height
expr_stmt|;
block|}
comment|/* allocate memory */
name|tempRGB
operator|=
name|g_new
argument_list|(
name|guchar
argument_list|,
name|RW
operator|*
name|RH
operator|*
name|bytes
argument_list|)
expr_stmt|;
name|tempHSV
operator|=
name|g_new
argument_list|(
name|gdouble
argument_list|,
name|RW
operator|*
name|RH
operator|*
name|bytes
argument_list|)
expr_stmt|;
name|tempmask
operator|=
name|g_new
argument_list|(
name|guchar
argument_list|,
name|RW
operator|*
name|RH
argument_list|)
expr_stmt|;
name|gimp_pixel_rgn_init
argument_list|(
operator|&
name|srcPR
argument_list|,
name|drawable
argument_list|,
name|x1
argument_list|,
name|y1
argument_list|,
name|width
argument_list|,
name|height
argument_list|,
name|FALSE
argument_list|,
name|FALSE
argument_list|)
expr_stmt|;
name|gimp_pixel_rgn_init
argument_list|(
operator|&
name|srcMask
argument_list|,
name|mask
argument_list|,
name|x1
operator|+
name|offx
argument_list|,
name|y1
operator|+
name|offy
argument_list|,
name|width
argument_list|,
name|height
argument_list|,
name|FALSE
argument_list|,
name|FALSE
argument_list|)
expr_stmt|;
name|src_row
operator|=
name|g_new
argument_list|(
name|guchar
argument_list|,
name|width
operator|*
name|bytes
argument_list|)
expr_stmt|;
name|src_mask_row
operator|=
name|g_new
argument_list|(
name|guchar
argument_list|,
name|width
operator|*
name|bytes
argument_list|)
expr_stmt|;
comment|/* reduce image */
for|for
control|(
name|i
operator|=
literal|0
init|;
name|i
operator|<
name|RH
condition|;
name|i
operator|++
control|)
block|{
name|whichrow
operator|=
operator|(
name|float
operator|)
name|i
operator|*
operator|(
name|float
operator|)
name|height
operator|/
operator|(
name|float
operator|)
name|RH
expr_stmt|;
name|gimp_pixel_rgn_get_row
argument_list|(
operator|&
name|srcPR
argument_list|,
name|src_row
argument_list|,
name|x1
argument_list|,
name|y1
operator|+
name|whichrow
argument_list|,
name|width
argument_list|)
expr_stmt|;
name|gimp_pixel_rgn_get_row
argument_list|(
operator|&
name|srcMask
argument_list|,
name|src_mask_row
argument_list|,
name|x1
operator|+
name|offx
argument_list|,
name|y1
operator|+
name|offy
operator|+
name|whichrow
argument_list|,
name|width
argument_list|)
expr_stmt|;
for|for
control|(
name|j
operator|=
literal|0
init|;
name|j
operator|<
name|RW
condition|;
name|j
operator|++
control|)
block|{
name|whichcol
operator|=
operator|(
name|float
operator|)
name|j
operator|*
operator|(
name|float
operator|)
name|width
operator|/
operator|(
name|float
operator|)
name|RW
expr_stmt|;
if|if
condition|(
name|NoSelectionMade
condition|)
name|tempmask
index|[
name|i
operator|*
name|RW
operator|+
name|j
index|]
operator|=
literal|255
expr_stmt|;
else|else
name|tempmask
index|[
name|i
operator|*
name|RW
operator|+
name|j
index|]
operator|=
name|src_mask_row
index|[
name|whichcol
index|]
expr_stmt|;
name|gimp_rgb_to_hsv4
argument_list|(
operator|&
name|src_row
index|[
name|whichcol
operator|*
name|bytes
index|]
argument_list|,
operator|&
name|H
argument_list|,
operator|&
name|S
argument_list|,
operator|&
name|V
argument_list|)
expr_stmt|;
name|tempRGB
index|[
name|i
operator|*
name|RW
operator|*
name|bytes
operator|+
name|j
operator|*
name|bytes
operator|+
literal|0
index|]
operator|=
name|src_row
index|[
name|whichcol
operator|*
name|bytes
operator|+
literal|0
index|]
expr_stmt|;
name|tempRGB
index|[
name|i
operator|*
name|RW
operator|*
name|bytes
operator|+
name|j
operator|*
name|bytes
operator|+
literal|1
index|]
operator|=
name|src_row
index|[
name|whichcol
operator|*
name|bytes
operator|+
literal|1
index|]
expr_stmt|;
name|tempRGB
index|[
name|i
operator|*
name|RW
operator|*
name|bytes
operator|+
name|j
operator|*
name|bytes
operator|+
literal|2
index|]
operator|=
name|src_row
index|[
name|whichcol
operator|*
name|bytes
operator|+
literal|2
index|]
expr_stmt|;
name|tempHSV
index|[
name|i
operator|*
name|RW
operator|*
name|bytes
operator|+
name|j
operator|*
name|bytes
operator|+
literal|0
index|]
operator|=
name|H
expr_stmt|;
name|tempHSV
index|[
name|i
operator|*
name|RW
operator|*
name|bytes
operator|+
name|j
operator|*
name|bytes
operator|+
literal|1
index|]
operator|=
name|S
expr_stmt|;
name|tempHSV
index|[
name|i
operator|*
name|RW
operator|*
name|bytes
operator|+
name|j
operator|*
name|bytes
operator|+
literal|2
index|]
operator|=
name|V
expr_stmt|;
if|if
condition|(
name|bytes
operator|==
literal|4
condition|)
name|tempRGB
index|[
name|i
operator|*
name|RW
operator|*
name|bytes
operator|+
name|j
operator|*
name|bytes
operator|+
literal|3
index|]
operator|=
name|src_row
index|[
name|whichcol
operator|*
name|bytes
operator|+
literal|3
index|]
expr_stmt|;
block|}
block|}
comment|/* return values */
name|temp
operator|->
name|width
operator|=
name|RW
expr_stmt|;
name|temp
operator|->
name|height
operator|=
name|RH
expr_stmt|;
name|temp
operator|->
name|rgb
operator|=
name|tempRGB
expr_stmt|;
name|temp
operator|->
name|hsv
operator|=
name|tempHSV
expr_stmt|;
name|temp
operator|->
name|mask
operator|=
name|tempmask
expr_stmt|;
return|return
name|temp
return|;
block|}
end_function

begin_comment
comment|/* render before/after preview */
end_comment

begin_function
name|void
DECL|function|rcm_render_preview (GtkWidget * preview,gint version)
name|rcm_render_preview
parameter_list|(
name|GtkWidget
modifier|*
name|preview
parameter_list|,
name|gint
name|version
parameter_list|)
block|{
name|ReducedImage
modifier|*
name|reduced
decl_stmt|;
name|gint
name|RW
decl_stmt|,
name|RH
decl_stmt|,
name|bytes
decl_stmt|,
name|i
decl_stmt|,
name|j
decl_stmt|,
name|unchanged
decl_stmt|,
name|skip
decl_stmt|;
name|guchar
modifier|*
name|rgb_array
decl_stmt|,
modifier|*
name|a
decl_stmt|;
name|gdouble
name|H
decl_stmt|,
name|S
decl_stmt|,
name|V
decl_stmt|;
name|gdouble
modifier|*
name|hsv_array
decl_stmt|;
name|guchar
name|rgb
index|[
literal|3
index|]
decl_stmt|;
name|gfloat
name|degree
decl_stmt|;
comment|/* init some variables */
name|g_return_if_fail
argument_list|(
name|preview
operator|!=
name|NULL
argument_list|)
expr_stmt|;
name|reduced
operator|=
name|Current
operator|.
name|reduced
expr_stmt|;
name|RW
operator|=
name|reduced
operator|->
name|width
expr_stmt|;
name|RH
operator|=
name|reduced
operator|->
name|height
expr_stmt|;
name|bytes
operator|=
name|Current
operator|.
name|drawable
operator|->
name|bpp
expr_stmt|;
name|hsv_array
operator|=
name|reduced
operator|->
name|hsv
expr_stmt|;
name|rgb_array
operator|=
name|reduced
operator|->
name|rgb
expr_stmt|;
name|a
operator|=
name|g_new
argument_list|(
name|guchar
argument_list|,
literal|4
operator|*
name|RW
operator|*
name|RH
argument_list|)
expr_stmt|;
if|if
condition|(
name|version
operator|==
name|CURRENT
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
name|RH
condition|;
name|i
operator|++
control|)
block|{
for|for
control|(
name|j
operator|=
literal|0
init|;
name|j
operator|<
name|RW
condition|;
name|j
operator|++
control|)
block|{
name|unchanged
operator|=
literal|1
expr_stmt|;
comment|/* TRUE */
name|skip
operator|=
literal|0
expr_stmt|;
comment|/* FALSE */
name|H
operator|=
name|hsv_array
index|[
name|i
operator|*
name|RW
operator|*
name|bytes
operator|+
name|j
operator|*
name|bytes
operator|+
literal|0
index|]
expr_stmt|;
name|S
operator|=
name|hsv_array
index|[
name|i
operator|*
name|RW
operator|*
name|bytes
operator|+
name|j
operator|*
name|bytes
operator|+
literal|1
index|]
expr_stmt|;
name|V
operator|=
name|hsv_array
index|[
name|i
operator|*
name|RW
operator|*
name|bytes
operator|+
name|j
operator|*
name|bytes
operator|+
literal|2
index|]
expr_stmt|;
if|if
condition|(
name|rcm_is_gray
argument_list|(
name|S
argument_list|)
operator|&&
operator|(
name|reduced
operator|->
name|mask
index|[
name|i
operator|*
name|RW
operator|+
name|j
index|]
operator|!=
literal|0
operator|)
condition|)
block|{
switch|switch
condition|(
name|Current
operator|.
name|Gray_to_from
condition|)
block|{
case|case
name|GRAY_FROM
case|:
if|if
condition|(
name|rcm_angle_inside_slice
argument_list|(
name|Current
operator|.
name|Gray
operator|->
name|hue
argument_list|,
name|Current
operator|.
name|From
operator|->
name|angle
argument_list|)
operator|<=
literal|1
condition|)
block|{
name|H
operator|=
name|Current
operator|.
name|Gray
operator|->
name|hue
operator|/
name|TP
expr_stmt|;
name|S
operator|=
name|Current
operator|.
name|Gray
operator|->
name|satur
expr_stmt|;
block|}
else|else
name|skip
operator|=
literal|1
expr_stmt|;
break|break;
case|case
name|GRAY_TO
case|:
name|unchanged
operator|=
literal|0
expr_stmt|;
name|skip
operator|=
literal|1
expr_stmt|;
name|gimp_hsv_to_rgb4
argument_list|(
name|rgb
argument_list|,
name|Current
operator|.
name|Gray
operator|->
name|hue
operator|/
name|TP
argument_list|,
name|Current
operator|.
name|Gray
operator|->
name|satur
argument_list|,
name|V
argument_list|)
expr_stmt|;
break|break;
default|default:
break|break;
block|}
block|}
if|if
condition|(
operator|!
name|skip
condition|)
block|{
name|unchanged
operator|=
literal|0
expr_stmt|;
name|H
operator|=
name|rcm_linear
argument_list|(
name|rcm_left_end
argument_list|(
name|Current
operator|.
name|From
operator|->
name|angle
argument_list|)
argument_list|,
name|rcm_right_end
argument_list|(
name|Current
operator|.
name|From
operator|->
name|angle
argument_list|)
argument_list|,
name|rcm_left_end
argument_list|(
name|Current
operator|.
name|To
operator|->
name|angle
argument_list|)
argument_list|,
name|rcm_right_end
argument_list|(
name|Current
operator|.
name|To
operator|->
name|angle
argument_list|)
argument_list|,
name|H
operator|*
name|TP
argument_list|)
expr_stmt|;
name|H
operator|=
name|angle_mod_2PI
argument_list|(
name|H
argument_list|)
operator|/
name|TP
expr_stmt|;
name|gimp_hsv_to_rgb4
argument_list|(
name|rgb
argument_list|,
name|H
argument_list|,
name|S
argument_list|,
name|V
argument_list|)
expr_stmt|;
block|}
if|if
condition|(
name|unchanged
condition|)
name|degree
operator|=
literal|0
expr_stmt|;
else|else
name|degree
operator|=
name|reduced
operator|->
name|mask
index|[
name|i
operator|*
name|RW
operator|+
name|j
index|]
operator|/
literal|255.0
expr_stmt|;
name|a
index|[
operator|(
name|i
operator|*
name|RW
operator|+
name|j
operator|)
operator|*
literal|4
operator|+
literal|0
index|]
operator|=
operator|(
literal|1
operator|-
name|degree
operator|)
operator|*
name|rgb_array
index|[
name|i
operator|*
name|RW
operator|*
name|bytes
operator|+
name|j
operator|*
name|bytes
operator|+
literal|0
index|]
operator|+
name|degree
operator|*
name|rgb
index|[
literal|0
index|]
expr_stmt|;
name|a
index|[
operator|(
name|i
operator|*
name|RW
operator|+
name|j
operator|)
operator|*
literal|4
operator|+
literal|1
index|]
operator|=
operator|(
literal|1
operator|-
name|degree
operator|)
operator|*
name|rgb_array
index|[
name|i
operator|*
name|RW
operator|*
name|bytes
operator|+
name|j
operator|*
name|bytes
operator|+
literal|1
index|]
operator|+
name|degree
operator|*
name|rgb
index|[
literal|1
index|]
expr_stmt|;
name|a
index|[
operator|(
name|i
operator|*
name|RW
operator|+
name|j
operator|)
operator|*
literal|4
operator|+
literal|2
index|]
operator|=
operator|(
literal|1
operator|-
name|degree
operator|)
operator|*
name|rgb_array
index|[
name|i
operator|*
name|RW
operator|*
name|bytes
operator|+
name|j
operator|*
name|bytes
operator|+
literal|2
index|]
operator|+
name|degree
operator|*
name|rgb
index|[
literal|2
index|]
expr_stmt|;
comment|/* apply transparency */
if|if
condition|(
name|bytes
operator|==
literal|4
condition|)
name|a
index|[
operator|(
name|i
operator|*
name|RW
operator|+
name|j
operator|)
operator|*
literal|4
operator|+
literal|3
index|]
operator|=
name|rgb_array
index|[
name|i
operator|*
name|RW
operator|*
name|bytes
operator|+
name|j
operator|*
name|bytes
operator|+
literal|3
index|]
expr_stmt|;
else|else
name|a
index|[
operator|(
name|i
operator|*
name|RW
operator|+
name|j
operator|)
operator|*
literal|4
operator|+
literal|3
index|]
operator|=
literal|255
expr_stmt|;
block|}
block|}
block|}
else|else
comment|/* ORIGINAL */
block|{
for|for
control|(
name|i
operator|=
literal|0
init|;
name|i
operator|<
name|RH
condition|;
name|i
operator|++
control|)
block|{
for|for
control|(
name|j
operator|=
literal|0
init|;
name|j
operator|<
name|RW
condition|;
name|j
operator|++
control|)
block|{
name|a
index|[
operator|(
name|i
operator|*
name|RW
operator|+
name|j
operator|)
operator|*
literal|4
operator|+
literal|0
index|]
operator|=
name|rgb_array
index|[
name|i
operator|*
name|RW
operator|*
name|bytes
operator|+
name|j
operator|*
name|bytes
operator|+
literal|0
index|]
expr_stmt|;
name|a
index|[
operator|(
name|i
operator|*
name|RW
operator|+
name|j
operator|)
operator|*
literal|4
operator|+
literal|1
index|]
operator|=
name|rgb_array
index|[
name|i
operator|*
name|RW
operator|*
name|bytes
operator|+
name|j
operator|*
name|bytes
operator|+
literal|1
index|]
expr_stmt|;
name|a
index|[
operator|(
name|i
operator|*
name|RW
operator|+
name|j
operator|)
operator|*
literal|4
operator|+
literal|2
index|]
operator|=
name|rgb_array
index|[
name|i
operator|*
name|RW
operator|*
name|bytes
operator|+
name|j
operator|*
name|bytes
operator|+
literal|2
index|]
expr_stmt|;
if|if
condition|(
name|bytes
operator|==
literal|4
condition|)
name|a
index|[
operator|(
name|i
operator|*
name|RW
operator|+
name|j
operator|)
operator|*
literal|4
operator|+
literal|3
index|]
operator|=
name|rgb_array
index|[
name|i
operator|*
name|RW
operator|*
name|bytes
operator|+
name|j
operator|*
name|bytes
operator|+
literal|3
index|]
expr_stmt|;
else|else
name|a
index|[
operator|(
name|i
operator|*
name|RW
operator|+
name|j
operator|)
operator|*
literal|4
operator|+
literal|3
index|]
operator|=
literal|255
expr_stmt|;
block|}
block|}
block|}
name|gimp_preview_area_draw
argument_list|(
name|GIMP_PREVIEW_AREA
argument_list|(
name|preview
argument_list|)
argument_list|,
literal|0
argument_list|,
literal|0
argument_list|,
name|RW
argument_list|,
name|RH
argument_list|,
name|GIMP_RGBA_IMAGE
argument_list|,
name|a
argument_list|,
name|RW
operator|*
literal|4
argument_list|)
expr_stmt|;
name|g_free
argument_list|(
name|a
argument_list|)
expr_stmt|;
block|}
end_function

begin_comment
comment|/* render circle */
end_comment

begin_function
name|void
DECL|function|rcm_render_circle (GtkWidget * preview,int sum,int margin)
name|rcm_render_circle
parameter_list|(
name|GtkWidget
modifier|*
name|preview
parameter_list|,
name|int
name|sum
parameter_list|,
name|int
name|margin
parameter_list|)
block|{
name|gint
name|i
decl_stmt|,
name|j
decl_stmt|;
name|gdouble
name|h
decl_stmt|,
name|s
decl_stmt|,
name|v
decl_stmt|;
name|guchar
modifier|*
name|a
decl_stmt|;
if|if
condition|(
name|preview
operator|==
name|NULL
condition|)
return|return;
name|a
operator|=
name|g_new
argument_list|(
name|guchar
argument_list|,
literal|3
operator|*
name|sum
operator|*
name|sum
argument_list|)
expr_stmt|;
for|for
control|(
name|j
operator|=
literal|0
init|;
name|j
operator|<
name|sum
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
name|sum
condition|;
name|i
operator|++
control|)
block|{
name|s
operator|=
name|sqrt
argument_list|(
operator|(
name|SQR
argument_list|(
name|i
operator|-
name|sum
operator|/
literal|2.0
argument_list|)
operator|+
name|SQR
argument_list|(
name|j
operator|-
name|sum
operator|/
literal|2.0
argument_list|)
operator|)
operator|/
operator|(
name|float
operator|)
name|SQR
argument_list|(
name|sum
operator|/
literal|2.0
operator|-
name|margin
argument_list|)
argument_list|)
expr_stmt|;
if|if
condition|(
name|s
operator|>
literal|1
condition|)
block|{
name|a
index|[
operator|(
name|j
operator|*
name|sum
operator|+
name|i
operator|)
operator|*
literal|3
operator|+
literal|0
index|]
operator|=
literal|255
expr_stmt|;
name|a
index|[
operator|(
name|j
operator|*
name|sum
operator|+
name|i
operator|)
operator|*
literal|3
operator|+
literal|1
index|]
operator|=
literal|255
expr_stmt|;
name|a
index|[
operator|(
name|j
operator|*
name|sum
operator|+
name|i
operator|)
operator|*
literal|3
operator|+
literal|2
index|]
operator|=
literal|255
expr_stmt|;
block|}
else|else
block|{
name|h
operator|=
name|arctg
argument_list|(
name|sum
operator|/
literal|2.0
operator|-
name|j
argument_list|,
name|i
operator|-
name|sum
operator|/
literal|2.0
argument_list|)
operator|/
operator|(
literal|2
operator|*
name|G_PI
operator|)
expr_stmt|;
name|v
operator|=
literal|1
operator|-
name|sqrt
argument_list|(
name|s
argument_list|)
operator|/
literal|4
expr_stmt|;
name|gimp_hsv_to_rgb4
argument_list|(
operator|&
name|a
index|[
operator|(
name|j
operator|*
name|sum
operator|+
name|i
operator|)
operator|*
literal|3
index|]
argument_list|,
name|h
argument_list|,
name|s
argument_list|,
name|v
argument_list|)
expr_stmt|;
block|}
block|}
block|}
name|gimp_preview_area_draw
argument_list|(
name|GIMP_PREVIEW_AREA
argument_list|(
name|preview
argument_list|)
argument_list|,
literal|0
argument_list|,
literal|0
argument_list|,
name|sum
argument_list|,
name|sum
argument_list|,
name|GIMP_RGB_IMAGE
argument_list|,
name|a
argument_list|,
name|sum
operator|*
literal|3
argument_list|)
expr_stmt|;
name|g_free
argument_list|(
name|a
argument_list|)
expr_stmt|;
block|}
end_function

end_unit

