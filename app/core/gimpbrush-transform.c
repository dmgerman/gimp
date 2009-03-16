begin_unit|revision:0.9.5;language:C;cregit-version:0.0.1
begin_comment
comment|/* GIMP - The GNU Image Manipulation Program  * Copyright (C) 1995 Spencer Kimball and Peter Mattis  *  * gimpbrush-transform.c  *  * This program is free software: you can redistribute it and/or modify  * it under the terms of the GNU General Public License as published by  * the Free Software Foundation; either version 3 of the License, or  * (at your option) any later version.  *  * This program is distributed in the hope that it will be useful,  * but WITHOUT ANY WARRANTY; without even the implied warranty of  * MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the  * GNU General Public License for more details.  *  * You should have received a copy of the GNU General Public License  * along with this program.  If not, see<http://www.gnu.org/licenses/>.  */
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
file|"core-types.h"
end_include

begin_include
include|#
directive|include
file|"libgimpmath/gimpmath.h"
end_include

begin_include
include|#
directive|include
file|"gimpbrush.h"
end_include

begin_include
include|#
directive|include
file|"gimpbrush-transform.h"
end_include

begin_include
include|#
directive|include
file|"base/temp-buf.h"
end_include

begin_comment
comment|/*  local function prototypes  */
end_comment

begin_function_decl
specifier|static
name|void
name|gimp_brush_transform_matrix
parameter_list|(
name|GimpBrush
modifier|*
name|brush
parameter_list|,
name|gdouble
name|scale_x
parameter_list|,
name|gdouble
name|scale_y
parameter_list|,
name|gdouble
name|angle
parameter_list|,
name|GimpMatrix3
modifier|*
name|matrix
parameter_list|)
function_decl|;
end_function_decl

begin_function_decl
specifier|static
name|void
name|gimp_brush_transform_bounding_box
parameter_list|(
name|GimpBrush
modifier|*
name|brush
parameter_list|,
specifier|const
name|GimpMatrix3
modifier|*
name|matrix
parameter_list|,
name|gint
modifier|*
name|x
parameter_list|,
name|gint
modifier|*
name|y
parameter_list|,
name|gint
modifier|*
name|width
parameter_list|,
name|gint
modifier|*
name|height
parameter_list|)
function_decl|;
end_function_decl

begin_comment
comment|/*  public functions  */
end_comment

begin_function
name|void
DECL|function|gimp_brush_real_transform_size (GimpBrush * brush,gdouble scale_x,gdouble scale_y,gdouble angle,gint * width,gint * height)
name|gimp_brush_real_transform_size
parameter_list|(
name|GimpBrush
modifier|*
name|brush
parameter_list|,
name|gdouble
name|scale_x
parameter_list|,
name|gdouble
name|scale_y
parameter_list|,
name|gdouble
name|angle
parameter_list|,
name|gint
modifier|*
name|width
parameter_list|,
name|gint
modifier|*
name|height
parameter_list|)
block|{
name|GimpMatrix3
name|matrix
decl_stmt|;
name|gint
name|x
decl_stmt|,
name|y
decl_stmt|;
name|gimp_brush_transform_matrix
argument_list|(
name|brush
argument_list|,
name|scale_x
argument_list|,
name|scale_y
argument_list|,
name|angle
argument_list|,
operator|&
name|matrix
argument_list|)
expr_stmt|;
name|gimp_brush_transform_bounding_box
argument_list|(
name|brush
argument_list|,
operator|&
name|matrix
argument_list|,
operator|&
name|x
argument_list|,
operator|&
name|y
argument_list|,
name|width
argument_list|,
name|height
argument_list|)
expr_stmt|;
block|}
end_function

begin_comment
comment|/*  * Transforms the brush mask with bilinear interpolation.  *  * Rather than calculating the inverse transform for each point in the  * transformed image, this algorithm uses the inverse transformed corner  * points of the destination image to work out the starting position in the  * source image and the U and V deltas in the source image space.  * It then uses a scan-line approach, looping through rows and colummns  * in the transformed (destination) image while walking along the corresponding  * rows and columns (named U and V) in the source image.  *  * The horizontal in destination space (transform result) is reverse transformed  * into source image space to get U.  * The vertical in destination space (transform result) is reverse transformed  * into source image space to get V.  *  * The strength of this particular algorithm is that calculation work should  * depend more upon the final transformed brush size rather than the input brush size.  *  * There are no floating point calculations in the inner loop for speed.  */
end_comment

begin_function
name|TempBuf
modifier|*
DECL|function|gimp_brush_real_transform_mask (GimpBrush * brush,gdouble scale_x,gdouble scale_y,gdouble angle)
name|gimp_brush_real_transform_mask
parameter_list|(
name|GimpBrush
modifier|*
name|brush
parameter_list|,
name|gdouble
name|scale_x
parameter_list|,
name|gdouble
name|scale_y
parameter_list|,
name|gdouble
name|angle
parameter_list|)
block|{
name|TempBuf
modifier|*
name|result
decl_stmt|;
name|guchar
modifier|*
name|dest
decl_stmt|;
specifier|const
name|guchar
modifier|*
name|src
decl_stmt|;
name|GimpMatrix3
name|matrix
decl_stmt|;
name|gint
name|src_width
decl_stmt|;
name|gint
name|src_height
decl_stmt|;
name|gint
name|dest_width
decl_stmt|;
name|gint
name|dest_height
decl_stmt|;
name|gint
name|x
decl_stmt|,
name|y
decl_stmt|;
name|gdouble
name|blx
decl_stmt|,
name|brx
decl_stmt|,
name|tlx
decl_stmt|,
name|trx
decl_stmt|;
name|gdouble
name|bly
decl_stmt|,
name|bry
decl_stmt|,
name|tly
decl_stmt|,
name|try
decl_stmt|;
name|gdouble
name|src_tl_to_tr_delta_x
decl_stmt|;
name|gdouble
name|src_tl_to_tr_delta_y
decl_stmt|;
name|gdouble
name|src_tl_to_bl_delta_x
decl_stmt|;
name|gdouble
name|src_tl_to_bl_delta_y
decl_stmt|;
name|gint
name|src_walk_ux
decl_stmt|;
name|gint
name|src_walk_uy
decl_stmt|;
name|gint
name|src_walk_vx
decl_stmt|;
name|gint
name|src_walk_vy
decl_stmt|;
name|gint
name|src_space_cur_pos_x
decl_stmt|;
name|gint
name|src_space_cur_pos_y
decl_stmt|;
name|gint
name|src_space_row_start_x
decl_stmt|;
name|gint
name|src_space_row_start_y
decl_stmt|;
specifier|const
name|guchar
modifier|*
name|src_walker
decl_stmt|;
specifier|const
name|guchar
modifier|*
name|pixel_next
decl_stmt|;
specifier|const
name|guchar
modifier|*
name|pixel_below
decl_stmt|;
specifier|const
name|guchar
modifier|*
name|pixel_below_next
decl_stmt|;
name|gint
name|opposite_x
decl_stmt|,
name|distance_from_true_x
decl_stmt|;
name|gint
name|opposite_y
decl_stmt|,
name|distance_from_true_y
decl_stmt|;
name|gint
name|src_height_times_int_multiple
decl_stmt|;
name|gint
name|src_width_times_int_multiple
decl_stmt|;
name|gint
name|src_heightm1_times_int_multiple
decl_stmt|;
name|gint
name|src_widthm1_times_int_multiple
decl_stmt|;
comment|/*    * tl, tr etc are used because it is easier to visualize top left, top right etc    * corners of the forward transformed source image rectangle.    */
specifier|const
name|gint
name|fraction_bits
init|=
literal|12
decl_stmt|;
specifier|const
name|gint
name|int_multiple
init|=
name|pow
argument_list|(
literal|2
argument_list|,
name|fraction_bits
argument_list|)
decl_stmt|;
comment|/* In inner loop's bilinear calculation, two numbers that were each previously multiplied by    * int_multiple are multiplied together.    * To get back the right result, the multiplication result must be    * divided *twice* by 2^fraction_bits, equivalent to    * bit shift right by 2 * fraction_bits    */
specifier|const
name|gint
name|recovery_bits
init|=
literal|2
operator|*
name|fraction_bits
decl_stmt|;
comment|/*    * example: suppose fraction_bits = 9    * a 9-bit mask looks like this: 0001 1111 1111    * and is given by:  2^fraction_bits - 1    * demonstration:    * 2^0     = 0000 0000 0001    * 2^1     = 0000 0000 0010    * :    * 2^8     = 0001 0000 0000    * 2^9     = 0010 0000 0000    * 2^9 - 1 = 0001 1111 1111    */
specifier|const
name|guint
name|fraction_bitmask
init|=
name|pow
argument_list|(
literal|2
argument_list|,
name|fraction_bits
argument_list|)
operator|-
literal|1
decl_stmt|;
name|gimp_brush_transform_matrix
argument_list|(
name|brush
argument_list|,
name|scale_x
argument_list|,
name|scale_y
argument_list|,
name|angle
argument_list|,
operator|&
name|matrix
argument_list|)
expr_stmt|;
if|if
condition|(
name|gimp_matrix3_is_identity
argument_list|(
operator|&
name|matrix
argument_list|)
condition|)
return|return
name|temp_buf_copy
argument_list|(
name|brush
operator|->
name|mask
argument_list|,
name|NULL
argument_list|)
return|;
name|src_width
operator|=
name|brush
operator|->
name|mask
operator|->
name|width
expr_stmt|;
name|src_height
operator|=
name|brush
operator|->
name|mask
operator|->
name|height
expr_stmt|;
name|gimp_brush_transform_bounding_box
argument_list|(
name|brush
argument_list|,
operator|&
name|matrix
argument_list|,
operator|&
name|x
argument_list|,
operator|&
name|y
argument_list|,
operator|&
name|dest_width
argument_list|,
operator|&
name|dest_height
argument_list|)
expr_stmt|;
name|gimp_matrix3_translate
argument_list|(
operator|&
name|matrix
argument_list|,
operator|-
name|x
argument_list|,
operator|-
name|y
argument_list|)
expr_stmt|;
name|gimp_matrix3_invert
argument_list|(
operator|&
name|matrix
argument_list|)
expr_stmt|;
name|result
operator|=
name|temp_buf_new
argument_list|(
name|dest_width
argument_list|,
name|dest_height
argument_list|,
literal|1
argument_list|,
literal|0
argument_list|,
literal|0
argument_list|,
name|NULL
argument_list|)
expr_stmt|;
name|dest
operator|=
name|temp_buf_get_data
argument_list|(
name|result
argument_list|)
expr_stmt|;
name|src
operator|=
name|temp_buf_get_data
argument_list|(
name|brush
operator|->
name|mask
argument_list|)
expr_stmt|;
comment|/* prevent disappearance of 1x1 pixel brush at some rotations when      scaling< 1 */
comment|/*   if (src_width == 1&& src_height == 1&& scale_x< 1&& scale_y< 1 )     {       *dest = src[0];       return result;     }*/
name|gimp_matrix3_transform_point
argument_list|(
operator|&
name|matrix
argument_list|,
literal|0
argument_list|,
literal|0
argument_list|,
operator|&
name|tlx
argument_list|,
operator|&
name|tly
argument_list|)
expr_stmt|;
name|gimp_matrix3_transform_point
argument_list|(
operator|&
name|matrix
argument_list|,
name|dest_width
argument_list|,
literal|0
argument_list|,
operator|&
name|trx
argument_list|,
operator|&
name|try
argument_list|)
expr_stmt|;
name|gimp_matrix3_transform_point
argument_list|(
operator|&
name|matrix
argument_list|,
literal|0
argument_list|,
name|dest_height
argument_list|,
operator|&
name|blx
argument_list|,
operator|&
name|bly
argument_list|)
expr_stmt|;
name|gimp_matrix3_transform_point
argument_list|(
operator|&
name|matrix
argument_list|,
name|dest_width
argument_list|,
name|dest_height
argument_list|,
operator|&
name|brx
argument_list|,
operator|&
name|bry
argument_list|)
expr_stmt|;
comment|/* in image space, calc U (what was horizontal originally)    * note: double precision    */
name|src_tl_to_tr_delta_x
operator|=
name|trx
operator|-
name|tlx
expr_stmt|;
name|src_tl_to_tr_delta_y
operator|=
name|try
operator|-
name|tly
expr_stmt|;
comment|/* in image space, calc V (what was vertical originally)    * note: double precision    */
name|src_tl_to_bl_delta_x
operator|=
name|blx
operator|-
name|tlx
expr_stmt|;
name|src_tl_to_bl_delta_y
operator|=
name|bly
operator|-
name|tly
expr_stmt|;
comment|/* speed optimized, note conversion to int precision */
name|src_walk_ux
operator|=
call|(
name|gint
call|)
argument_list|(
operator|(
name|src_tl_to_tr_delta_x
operator|/
name|dest_width
operator|)
operator|*
name|int_multiple
argument_list|)
expr_stmt|;
name|src_walk_uy
operator|=
call|(
name|gint
call|)
argument_list|(
operator|(
name|src_tl_to_tr_delta_y
operator|/
name|dest_width
operator|)
operator|*
name|int_multiple
argument_list|)
expr_stmt|;
name|src_walk_vx
operator|=
call|(
name|gint
call|)
argument_list|(
operator|(
name|src_tl_to_bl_delta_x
operator|/
name|dest_height
operator|)
operator|*
name|int_multiple
argument_list|)
expr_stmt|;
name|src_walk_vy
operator|=
call|(
name|gint
call|)
argument_list|(
operator|(
name|src_tl_to_bl_delta_y
operator|/
name|dest_height
operator|)
operator|*
name|int_multiple
argument_list|)
expr_stmt|;
comment|/* initialize current position in source space to the start position (tl)    * speed optimized, note conversion to int precision    */
name|src_space_cur_pos_x
operator|=
call|(
name|gint
call|)
argument_list|(
name|tlx
operator|*
name|int_multiple
argument_list|)
expr_stmt|;
name|src_space_cur_pos_y
operator|=
call|(
name|gint
call|)
argument_list|(
name|tly
operator|*
name|int_multiple
argument_list|)
expr_stmt|;
name|src_space_row_start_x
operator|=
call|(
name|gint
call|)
argument_list|(
name|tlx
operator|*
name|int_multiple
argument_list|)
expr_stmt|;
name|src_space_row_start_y
operator|=
call|(
name|gint
call|)
argument_list|(
name|tly
operator|*
name|int_multiple
argument_list|)
expr_stmt|;
name|src_walker
operator|=
name|src
expr_stmt|;
name|src_height_times_int_multiple
operator|=
name|src_height
operator|<<
name|fraction_bits
expr_stmt|;
comment|/* mult by int_multiple */
name|src_width_times_int_multiple
operator|=
name|src_width
operator|<<
name|fraction_bits
expr_stmt|;
comment|/* mult by int_multiple */
name|src_heightm1_times_int_multiple
operator|=
name|src_height_times_int_multiple
operator|-
name|int_multiple
expr_stmt|;
name|src_widthm1_times_int_multiple
operator|=
name|src_width_times_int_multiple
operator|-
name|int_multiple
expr_stmt|;
for|for
control|(
name|y
operator|=
literal|0
init|;
name|y
operator|<
name|dest_height
condition|;
name|y
operator|++
control|)
block|{
for|for
control|(
name|x
operator|=
literal|0
init|;
name|x
operator|<
name|dest_width
condition|;
name|x
operator|++
control|)
block|{
if|if
condition|(
name|src_space_cur_pos_x
operator|>
name|src_width_times_int_multiple
operator|||
name|src_space_cur_pos_x
operator|<
literal|0
operator|||
name|src_space_cur_pos_y
operator|>
name|src_height_times_int_multiple
operator|||
name|src_space_cur_pos_y
operator|<
literal|0
condition|)
comment|/* no corresponding pixel in source space */
block|{
operator|*
name|dest
operator|=
literal|0
expr_stmt|;
block|}
else|else
comment|/* reverse transformed point hits source pixel */
block|{
name|src_walker
operator|=
name|src
operator|+
operator|(
name|src_space_cur_pos_y
operator|>>
name|fraction_bits
operator|)
operator|*
name|src_width
operator|+
operator|(
name|src_space_cur_pos_x
operator|>>
name|fraction_bits
operator|)
expr_stmt|;
comment|/* bottom right corner                * no pixel below, reuse current pixel instead                * no next pixel to the right so reuse current pixel instead                */
if|if
condition|(
name|src_space_cur_pos_y
operator|>
operator|(
name|src_heightm1_times_int_multiple
operator|)
operator|&&
name|src_space_cur_pos_x
operator|>
operator|(
name|src_widthm1_times_int_multiple
operator|)
condition|)
block|{
name|pixel_next
operator|=
name|src_walker
expr_stmt|;
name|pixel_below
operator|=
name|src_walker
expr_stmt|;
name|pixel_below_next
operator|=
name|src_walker
expr_stmt|;
block|}
comment|/* bottom edge pixel row, except rightmost corner                * no pixel below, reuse current pixel instead  */
elseif|else
if|if
condition|(
name|src_space_cur_pos_y
operator|>
operator|(
name|src_heightm1_times_int_multiple
operator|)
condition|)
block|{
name|pixel_next
operator|=
name|src_walker
operator|+
literal|1
expr_stmt|;
name|pixel_below
operator|=
name|src_walker
expr_stmt|;
name|pixel_below_next
operator|=
name|src_walker
operator|+
literal|1
expr_stmt|;
block|}
comment|/* right edge pixel column, except bottom corner                * no next pixel to the right so reuse current pixel instead */
elseif|else
if|if
condition|(
name|src_space_cur_pos_x
operator|>
operator|(
name|src_widthm1_times_int_multiple
operator|)
condition|)
block|{
name|pixel_next
operator|=
name|src_walker
expr_stmt|;
name|pixel_below
operator|=
name|src_walker
operator|+
name|src_width
expr_stmt|;
name|pixel_below_next
operator|=
name|pixel_below
expr_stmt|;
block|}
comment|/* neither on bottom edge nor on right edge */
else|else
block|{
name|pixel_next
operator|=
name|src_walker
operator|+
literal|1
expr_stmt|;
name|pixel_below
operator|=
name|src_walker
operator|+
name|src_width
expr_stmt|;
name|pixel_below_next
operator|=
name|pixel_below
operator|+
literal|1
expr_stmt|;
block|}
name|distance_from_true_x
operator|=
name|src_space_cur_pos_x
operator|&
name|fraction_bitmask
expr_stmt|;
name|distance_from_true_y
operator|=
name|src_space_cur_pos_y
operator|&
name|fraction_bitmask
expr_stmt|;
name|opposite_x
operator|=
name|int_multiple
operator|-
name|distance_from_true_x
expr_stmt|;
name|opposite_y
operator|=
name|int_multiple
operator|-
name|distance_from_true_y
expr_stmt|;
operator|*
name|dest
operator|=
operator|(
operator|(
name|src_walker
index|[
literal|0
index|]
operator|*
name|opposite_x
operator|+
name|pixel_next
index|[
literal|0
index|]
operator|*
name|distance_from_true_x
operator|)
operator|*
name|opposite_y
operator|+
operator|(
name|pixel_below
index|[
literal|0
index|]
operator|*
name|opposite_x
operator|+
name|pixel_below_next
index|[
literal|0
index|]
operator|*
name|distance_from_true_x
operator|)
operator|*
name|distance_from_true_y
operator|)
operator|>>
name|recovery_bits
expr_stmt|;
block|}
name|src_space_cur_pos_x
operator|+=
name|src_walk_ux
expr_stmt|;
name|src_space_cur_pos_y
operator|+=
name|src_walk_uy
expr_stmt|;
name|dest
operator|++
expr_stmt|;
block|}
comment|/* end for x */
name|src_space_row_start_x
operator|+=
name|src_walk_vx
expr_stmt|;
name|src_space_row_start_y
operator|+=
name|src_walk_vy
expr_stmt|;
name|src_space_cur_pos_x
operator|=
name|src_space_row_start_x
expr_stmt|;
name|src_space_cur_pos_y
operator|=
name|src_space_row_start_y
expr_stmt|;
block|}
comment|/* end for y */
return|return
name|result
return|;
block|}
end_function

begin_comment
comment|/*  * Transforms the brush pixmap with bilinear interpolation.  *  * The algorithm used is exactly the same as for the brush mask  * (gimp_brush_real_transform_mask) except it accounts for 3 color channels  *  instead of 1 greyscale channel.  *  * Rather than calculating the inverse transform for each point in the  * transformed image, this algorithm uses the inverse transformed  * corner points of the destination image to work out the starting  * position in the source image and the U and V deltas in the source  * image space.  It then uses a scan-line approach, looping through  * rows and colummns in the transformed (destination) image while  * walking along the corresponding rows and columns (named U and V) in  * the source image.  *  * The horizontal in destination space (transform result) is reverse  * transformed into source image space to get U.  The vertical in  * destination space (transform result) is reverse transformed into  * source image space to get V.  *  * The strength of this particular algorithm is that calculation work  * should depend more upon the final transformed brush size rather  * than the input brush size.  *  * There are no floating point calculations in the inner loop for speed.  */
end_comment

begin_function
name|TempBuf
modifier|*
DECL|function|gimp_brush_real_transform_pixmap (GimpBrush * brush,gdouble scale_x,gdouble scale_y,gdouble angle)
name|gimp_brush_real_transform_pixmap
parameter_list|(
name|GimpBrush
modifier|*
name|brush
parameter_list|,
name|gdouble
name|scale_x
parameter_list|,
name|gdouble
name|scale_y
parameter_list|,
name|gdouble
name|angle
parameter_list|)
block|{
name|TempBuf
modifier|*
name|result
decl_stmt|;
name|guchar
modifier|*
name|dest
decl_stmt|;
specifier|const
name|guchar
modifier|*
name|src
decl_stmt|;
name|GimpMatrix3
name|matrix
decl_stmt|;
name|gint
name|src_width
decl_stmt|;
name|gint
name|src_height
decl_stmt|;
name|gint
name|dest_width
decl_stmt|;
name|gint
name|dest_height
decl_stmt|;
name|gint
name|x
decl_stmt|,
name|y
decl_stmt|;
name|gdouble
name|blx
decl_stmt|,
name|brx
decl_stmt|,
name|tlx
decl_stmt|,
name|trx
decl_stmt|;
name|gdouble
name|bly
decl_stmt|,
name|bry
decl_stmt|,
name|tly
decl_stmt|,
name|try
decl_stmt|;
name|gdouble
name|src_tl_to_tr_delta_x
decl_stmt|;
name|gdouble
name|src_tl_to_tr_delta_y
decl_stmt|;
name|gdouble
name|src_tl_to_bl_delta_x
decl_stmt|;
name|gdouble
name|src_tl_to_bl_delta_y
decl_stmt|;
name|gint
name|src_walk_ux
decl_stmt|;
name|gint
name|src_walk_uy
decl_stmt|;
name|gint
name|src_walk_vx
decl_stmt|;
name|gint
name|src_walk_vy
decl_stmt|;
name|gint
name|src_space_cur_pos_x
decl_stmt|;
name|gint
name|src_space_cur_pos_y
decl_stmt|;
name|gint
name|src_space_row_start_x
decl_stmt|;
name|gint
name|src_space_row_start_y
decl_stmt|;
specifier|const
name|guchar
modifier|*
name|src_walker
decl_stmt|;
specifier|const
name|guchar
modifier|*
name|pixel_next
decl_stmt|;
specifier|const
name|guchar
modifier|*
name|pixel_below
decl_stmt|;
specifier|const
name|guchar
modifier|*
name|pixel_below_next
decl_stmt|;
name|gint
name|opposite_x
decl_stmt|,
name|distance_from_true_x
decl_stmt|;
name|gint
name|opposite_y
decl_stmt|,
name|distance_from_true_y
decl_stmt|;
name|gint
name|src_height_times_int_multiple
decl_stmt|;
name|gint
name|src_width_times_int_multiple
decl_stmt|;
name|gint
name|src_heightm1_times_int_multiple
decl_stmt|;
name|gint
name|src_widthm1_times_int_multiple
decl_stmt|;
comment|/*    * tl, tr etc are used because it is easier to visualize top left, top right etc    * corners of the forward transformed source image rectangle.    */
specifier|const
name|gint
name|fraction_bits
init|=
literal|12
decl_stmt|;
specifier|const
name|gint
name|int_multiple
init|=
name|pow
argument_list|(
literal|2
argument_list|,
name|fraction_bits
argument_list|)
decl_stmt|;
comment|/* In inner loop's bilinear calculation, two numbers that were each previously multiplied by    * int_multiple are multiplied together.    * To get back the right result, the multiplication result must be    * divided *twice* by 2^fraction_bits, equivalent to    * bit shift right by 2 * fraction_bits    */
specifier|const
name|gint
name|recovery_bits
init|=
literal|2
operator|*
name|fraction_bits
decl_stmt|;
comment|/*    * example: suppose fraction_bits = 9    * a 9-bit mask looks like this: 0001 1111 1111    * and is given by:  2^fraction_bits - 1    * demonstration:    * 2^0     = 0000 0000 0001    * 2^1     = 0000 0000 0010    * :    * 2^8     = 0001 0000 0000    * 2^9     = 0010 0000 0000    * 2^9 - 1 = 0001 1111 1111    */
specifier|const
name|guint
name|fraction_bitmask
init|=
name|pow
argument_list|(
literal|2
argument_list|,
name|fraction_bits
argument_list|)
operator|-
literal|1
decl_stmt|;
name|gimp_brush_transform_matrix
argument_list|(
name|brush
argument_list|,
name|scale_x
argument_list|,
name|scale_y
argument_list|,
name|angle
argument_list|,
operator|&
name|matrix
argument_list|)
expr_stmt|;
if|if
condition|(
name|gimp_matrix3_is_identity
argument_list|(
operator|&
name|matrix
argument_list|)
condition|)
return|return
name|temp_buf_copy
argument_list|(
name|brush
operator|->
name|pixmap
argument_list|,
name|NULL
argument_list|)
return|;
name|src_width
operator|=
name|brush
operator|->
name|pixmap
operator|->
name|width
expr_stmt|;
name|src_height
operator|=
name|brush
operator|->
name|pixmap
operator|->
name|height
expr_stmt|;
name|gimp_brush_transform_bounding_box
argument_list|(
name|brush
argument_list|,
operator|&
name|matrix
argument_list|,
operator|&
name|x
argument_list|,
operator|&
name|y
argument_list|,
operator|&
name|dest_width
argument_list|,
operator|&
name|dest_height
argument_list|)
expr_stmt|;
name|gimp_matrix3_translate
argument_list|(
operator|&
name|matrix
argument_list|,
operator|-
name|x
argument_list|,
operator|-
name|y
argument_list|)
expr_stmt|;
name|gimp_matrix3_invert
argument_list|(
operator|&
name|matrix
argument_list|)
expr_stmt|;
name|result
operator|=
name|temp_buf_new
argument_list|(
name|dest_width
argument_list|,
name|dest_height
argument_list|,
literal|3
argument_list|,
literal|0
argument_list|,
literal|0
argument_list|,
name|NULL
argument_list|)
expr_stmt|;
name|dest
operator|=
name|temp_buf_get_data
argument_list|(
name|result
argument_list|)
expr_stmt|;
name|src
operator|=
name|temp_buf_get_data
argument_list|(
name|brush
operator|->
name|pixmap
argument_list|)
expr_stmt|;
name|gimp_matrix3_transform_point
argument_list|(
operator|&
name|matrix
argument_list|,
literal|0
argument_list|,
literal|0
argument_list|,
operator|&
name|tlx
argument_list|,
operator|&
name|tly
argument_list|)
expr_stmt|;
name|gimp_matrix3_transform_point
argument_list|(
operator|&
name|matrix
argument_list|,
name|dest_width
argument_list|,
literal|0
argument_list|,
operator|&
name|trx
argument_list|,
operator|&
name|try
argument_list|)
expr_stmt|;
name|gimp_matrix3_transform_point
argument_list|(
operator|&
name|matrix
argument_list|,
literal|0
argument_list|,
name|dest_height
argument_list|,
operator|&
name|blx
argument_list|,
operator|&
name|bly
argument_list|)
expr_stmt|;
name|gimp_matrix3_transform_point
argument_list|(
operator|&
name|matrix
argument_list|,
name|dest_width
argument_list|,
name|dest_height
argument_list|,
operator|&
name|brx
argument_list|,
operator|&
name|bry
argument_list|)
expr_stmt|;
comment|/* in image space, calc U (what was horizontal originally)    * note: double precision    */
name|src_tl_to_tr_delta_x
operator|=
name|trx
operator|-
name|tlx
expr_stmt|;
name|src_tl_to_tr_delta_y
operator|=
name|try
operator|-
name|tly
expr_stmt|;
comment|/* in image space, calc V (what was vertical originally)    * note: double precision    */
name|src_tl_to_bl_delta_x
operator|=
name|blx
operator|-
name|tlx
expr_stmt|;
name|src_tl_to_bl_delta_y
operator|=
name|bly
operator|-
name|tly
expr_stmt|;
comment|/* speed optimized, note conversion to int precision */
name|src_walk_ux
operator|=
call|(
name|gint
call|)
argument_list|(
operator|(
name|src_tl_to_tr_delta_x
operator|/
name|dest_width
operator|)
operator|*
name|int_multiple
argument_list|)
expr_stmt|;
name|src_walk_uy
operator|=
call|(
name|gint
call|)
argument_list|(
operator|(
name|src_tl_to_tr_delta_y
operator|/
name|dest_width
operator|)
operator|*
name|int_multiple
argument_list|)
expr_stmt|;
name|src_walk_vx
operator|=
call|(
name|gint
call|)
argument_list|(
operator|(
name|src_tl_to_bl_delta_x
operator|/
name|dest_height
operator|)
operator|*
name|int_multiple
argument_list|)
expr_stmt|;
name|src_walk_vy
operator|=
call|(
name|gint
call|)
argument_list|(
operator|(
name|src_tl_to_bl_delta_y
operator|/
name|dest_height
operator|)
operator|*
name|int_multiple
argument_list|)
expr_stmt|;
comment|/* initialize current position in source space to the start position (tl)    * speed optimized, note conversion to int precision    */
name|src_space_cur_pos_x
operator|=
call|(
name|gint
call|)
argument_list|(
name|tlx
operator|*
name|int_multiple
argument_list|)
expr_stmt|;
name|src_space_cur_pos_y
operator|=
call|(
name|gint
call|)
argument_list|(
name|tly
operator|*
name|int_multiple
argument_list|)
expr_stmt|;
name|src_space_row_start_x
operator|=
call|(
name|gint
call|)
argument_list|(
name|tlx
operator|*
name|int_multiple
argument_list|)
expr_stmt|;
name|src_space_row_start_y
operator|=
call|(
name|gint
call|)
argument_list|(
name|tly
operator|*
name|int_multiple
argument_list|)
expr_stmt|;
name|src_walker
operator|=
name|src
expr_stmt|;
name|src_height_times_int_multiple
operator|=
name|src_height
operator|<<
name|fraction_bits
expr_stmt|;
comment|/* mult by int_multiple */
name|src_width_times_int_multiple
operator|=
name|src_width
operator|<<
name|fraction_bits
expr_stmt|;
comment|/* mult by int_multiple */
name|src_heightm1_times_int_multiple
operator|=
name|src_height_times_int_multiple
operator|-
name|int_multiple
expr_stmt|;
name|src_widthm1_times_int_multiple
operator|=
name|src_width_times_int_multiple
operator|-
name|int_multiple
expr_stmt|;
for|for
control|(
name|y
operator|=
literal|0
init|;
name|y
operator|<
name|dest_height
condition|;
name|y
operator|++
control|)
block|{
for|for
control|(
name|x
operator|=
literal|0
init|;
name|x
operator|<
name|dest_width
condition|;
name|x
operator|++
control|)
block|{
if|if
condition|(
name|src_space_cur_pos_x
operator|>
name|src_width_times_int_multiple
operator|||
name|src_space_cur_pos_x
operator|<
literal|0
operator|||
name|src_space_cur_pos_y
operator|>
name|src_height_times_int_multiple
operator|||
name|src_space_cur_pos_y
operator|<
literal|0
condition|)
comment|/* no corresponding pixel in source space */
block|{
name|dest
index|[
literal|0
index|]
operator|=
literal|0
expr_stmt|;
name|dest
index|[
literal|1
index|]
operator|=
literal|0
expr_stmt|;
name|dest
index|[
literal|2
index|]
operator|=
literal|0
expr_stmt|;
block|}
else|else
comment|/* reverse transformed point hits source pixel */
block|{
name|src_walker
operator|=
name|src
operator|+
literal|3
operator|*
operator|(
operator|(
name|src_space_cur_pos_y
operator|>>
name|fraction_bits
operator|)
operator|*
name|src_width
operator|+
operator|(
name|src_space_cur_pos_x
operator|>>
name|fraction_bits
operator|)
operator|)
expr_stmt|;
comment|/* bottom right corner                * no pixel below, reuse current pixel instead                * no next pixel to the right so reuse current pixel instead                */
if|if
condition|(
name|src_space_cur_pos_y
operator|>
operator|(
name|src_heightm1_times_int_multiple
operator|)
operator|&&
name|src_space_cur_pos_x
operator|>
operator|(
name|src_widthm1_times_int_multiple
operator|)
condition|)
block|{
name|pixel_next
operator|=
name|src_walker
expr_stmt|;
name|pixel_below
operator|=
name|src_walker
expr_stmt|;
name|pixel_below_next
operator|=
name|src_walker
expr_stmt|;
block|}
comment|/* bottom edge pixel row, except rightmost corner                * no pixel below, reuse current pixel instead  */
elseif|else
if|if
condition|(
name|src_space_cur_pos_y
operator|>
operator|(
name|src_heightm1_times_int_multiple
operator|)
condition|)
block|{
name|pixel_next
operator|=
name|src_walker
operator|+
literal|3
expr_stmt|;
name|pixel_below
operator|=
name|src_walker
expr_stmt|;
name|pixel_below_next
operator|=
name|src_walker
operator|+
literal|3
expr_stmt|;
block|}
comment|/* right edge pixel column, except bottom corner                * no next pixel to the right so reuse current pixel instead */
elseif|else
if|if
condition|(
name|src_space_cur_pos_x
operator|>
operator|(
name|src_widthm1_times_int_multiple
operator|)
condition|)
block|{
name|pixel_next
operator|=
name|src_walker
expr_stmt|;
name|pixel_below
operator|=
name|src_walker
operator|+
name|src_width
operator|*
literal|3
expr_stmt|;
name|pixel_below_next
operator|=
name|pixel_below
expr_stmt|;
block|}
comment|/* neither on bottom edge nor on right edge */
else|else
block|{
name|pixel_next
operator|=
name|src_walker
operator|+
literal|3
expr_stmt|;
name|pixel_below
operator|=
name|src_walker
operator|+
name|src_width
operator|*
literal|3
expr_stmt|;
name|pixel_below_next
operator|=
name|pixel_below
operator|+
literal|3
expr_stmt|;
block|}
name|distance_from_true_x
operator|=
name|src_space_cur_pos_x
operator|&
name|fraction_bitmask
expr_stmt|;
name|distance_from_true_y
operator|=
name|src_space_cur_pos_y
operator|&
name|fraction_bitmask
expr_stmt|;
name|opposite_x
operator|=
name|int_multiple
operator|-
name|distance_from_true_x
expr_stmt|;
name|opposite_y
operator|=
name|int_multiple
operator|-
name|distance_from_true_y
expr_stmt|;
name|dest
index|[
literal|0
index|]
operator|=
operator|(
operator|(
name|src_walker
index|[
literal|0
index|]
operator|*
name|opposite_x
operator|+
name|pixel_next
index|[
literal|0
index|]
operator|*
name|distance_from_true_x
operator|)
operator|*
name|opposite_y
operator|+
operator|(
name|pixel_below
index|[
literal|0
index|]
operator|*
name|opposite_x
operator|+
name|pixel_below_next
index|[
literal|0
index|]
operator|*
name|distance_from_true_x
operator|)
operator|*
name|distance_from_true_y
operator|)
operator|>>
name|recovery_bits
expr_stmt|;
name|dest
index|[
literal|1
index|]
operator|=
operator|(
operator|(
name|src_walker
index|[
literal|1
index|]
operator|*
name|opposite_x
operator|+
name|pixel_next
index|[
literal|1
index|]
operator|*
name|distance_from_true_x
operator|)
operator|*
name|opposite_y
operator|+
operator|(
name|pixel_below
index|[
literal|1
index|]
operator|*
name|opposite_x
operator|+
name|pixel_below_next
index|[
literal|1
index|]
operator|*
name|distance_from_true_x
operator|)
operator|*
name|distance_from_true_y
operator|)
operator|>>
name|recovery_bits
expr_stmt|;
name|dest
index|[
literal|2
index|]
operator|=
operator|(
operator|(
name|src_walker
index|[
literal|2
index|]
operator|*
name|opposite_x
operator|+
name|pixel_next
index|[
literal|2
index|]
operator|*
name|distance_from_true_x
operator|)
operator|*
name|opposite_y
operator|+
operator|(
name|pixel_below
index|[
literal|2
index|]
operator|*
name|opposite_x
operator|+
name|pixel_below_next
index|[
literal|2
index|]
operator|*
name|distance_from_true_x
operator|)
operator|*
name|distance_from_true_y
operator|)
operator|>>
name|recovery_bits
expr_stmt|;
block|}
name|src_space_cur_pos_x
operator|+=
name|src_walk_ux
expr_stmt|;
name|src_space_cur_pos_y
operator|+=
name|src_walk_uy
expr_stmt|;
name|dest
operator|+=
literal|3
expr_stmt|;
block|}
comment|/* end for x */
name|src_space_row_start_x
operator|+=
name|src_walk_vx
expr_stmt|;
name|src_space_row_start_y
operator|+=
name|src_walk_vy
expr_stmt|;
name|src_space_cur_pos_x
operator|=
name|src_space_row_start_x
expr_stmt|;
name|src_space_cur_pos_y
operator|=
name|src_space_row_start_y
expr_stmt|;
block|}
comment|/* end for y */
return|return
name|result
return|;
block|}
end_function

begin_comment
comment|/*  private functions  */
end_comment

begin_function
specifier|static
name|void
DECL|function|gimp_brush_transform_matrix (GimpBrush * brush,gdouble scale_x,gdouble scale_y,gdouble angle,GimpMatrix3 * matrix)
name|gimp_brush_transform_matrix
parameter_list|(
name|GimpBrush
modifier|*
name|brush
parameter_list|,
name|gdouble
name|scale_x
parameter_list|,
name|gdouble
name|scale_y
parameter_list|,
name|gdouble
name|angle
parameter_list|,
name|GimpMatrix3
modifier|*
name|matrix
parameter_list|)
block|{
specifier|const
name|gdouble
name|center_x
init|=
name|brush
operator|->
name|mask
operator|->
name|width
operator|/
literal|2
decl_stmt|;
specifier|const
name|gdouble
name|center_y
init|=
name|brush
operator|->
name|mask
operator|->
name|height
operator|/
literal|2
decl_stmt|;
name|gimp_matrix3_identity
argument_list|(
name|matrix
argument_list|)
expr_stmt|;
name|gimp_matrix3_translate
argument_list|(
name|matrix
argument_list|,
operator|-
name|center_x
argument_list|,
operator|-
name|center_y
argument_list|)
expr_stmt|;
name|gimp_matrix3_rotate
argument_list|(
name|matrix
argument_list|,
operator|-
literal|2
operator|*
name|G_PI
operator|*
name|angle
argument_list|)
expr_stmt|;
name|gimp_matrix3_translate
argument_list|(
name|matrix
argument_list|,
name|center_x
argument_list|,
name|center_y
argument_list|)
expr_stmt|;
name|gimp_matrix3_scale
argument_list|(
name|matrix
argument_list|,
name|scale_x
argument_list|,
name|scale_y
argument_list|)
expr_stmt|;
block|}
end_function

begin_function
specifier|static
name|void
DECL|function|gimp_brush_transform_bounding_box (GimpBrush * brush,const GimpMatrix3 * matrix,gint * x,gint * y,gint * width,gint * height)
name|gimp_brush_transform_bounding_box
parameter_list|(
name|GimpBrush
modifier|*
name|brush
parameter_list|,
specifier|const
name|GimpMatrix3
modifier|*
name|matrix
parameter_list|,
name|gint
modifier|*
name|x
parameter_list|,
name|gint
modifier|*
name|y
parameter_list|,
name|gint
modifier|*
name|width
parameter_list|,
name|gint
modifier|*
name|height
parameter_list|)
block|{
specifier|const
name|gdouble
name|w
init|=
name|brush
operator|->
name|mask
operator|->
name|width
decl_stmt|;
specifier|const
name|gdouble
name|h
init|=
name|brush
operator|->
name|mask
operator|->
name|height
decl_stmt|;
name|gdouble
name|x1
decl_stmt|,
name|x2
decl_stmt|,
name|x3
decl_stmt|,
name|x4
decl_stmt|;
name|gdouble
name|y1
decl_stmt|,
name|y2
decl_stmt|,
name|y3
decl_stmt|,
name|y4
decl_stmt|;
name|gimp_matrix3_transform_point
argument_list|(
name|matrix
argument_list|,
literal|0
argument_list|,
literal|0
argument_list|,
operator|&
name|x1
argument_list|,
operator|&
name|y1
argument_list|)
expr_stmt|;
name|gimp_matrix3_transform_point
argument_list|(
name|matrix
argument_list|,
name|w
argument_list|,
literal|0
argument_list|,
operator|&
name|x2
argument_list|,
operator|&
name|y2
argument_list|)
expr_stmt|;
name|gimp_matrix3_transform_point
argument_list|(
name|matrix
argument_list|,
literal|0
argument_list|,
name|h
argument_list|,
operator|&
name|x3
argument_list|,
operator|&
name|y3
argument_list|)
expr_stmt|;
name|gimp_matrix3_transform_point
argument_list|(
name|matrix
argument_list|,
name|w
argument_list|,
name|h
argument_list|,
operator|&
name|x4
argument_list|,
operator|&
name|y4
argument_list|)
expr_stmt|;
operator|*
name|x
operator|=
name|floor
argument_list|(
name|MIN
argument_list|(
name|MIN
argument_list|(
name|x1
argument_list|,
name|x2
argument_list|)
argument_list|,
name|MIN
argument_list|(
name|x3
argument_list|,
name|x4
argument_list|)
argument_list|)
argument_list|)
expr_stmt|;
operator|*
name|y
operator|=
name|floor
argument_list|(
name|MIN
argument_list|(
name|MIN
argument_list|(
name|y1
argument_list|,
name|y2
argument_list|)
argument_list|,
name|MIN
argument_list|(
name|y3
argument_list|,
name|y4
argument_list|)
argument_list|)
argument_list|)
expr_stmt|;
operator|*
name|width
operator|=
call|(
name|gint
call|)
argument_list|(
name|ceil
argument_list|(
name|MAX
argument_list|(
name|MAX
argument_list|(
name|x1
argument_list|,
name|x2
argument_list|)
argument_list|,
name|MAX
argument_list|(
name|x3
argument_list|,
name|x4
argument_list|)
argument_list|)
argument_list|)
operator|-
operator|*
name|x
argument_list|)
expr_stmt|;
operator|*
name|height
operator|=
call|(
name|gint
call|)
argument_list|(
name|ceil
argument_list|(
name|MAX
argument_list|(
name|MAX
argument_list|(
name|y1
argument_list|,
name|y2
argument_list|)
argument_list|,
name|MAX
argument_list|(
name|y3
argument_list|,
name|y4
argument_list|)
argument_list|)
argument_list|)
operator|-
operator|*
name|y
argument_list|)
expr_stmt|;
block|}
end_function

end_unit

