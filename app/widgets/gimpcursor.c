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
file|<gtk/gtk.h>
end_include

begin_include
include|#
directive|include
file|"widgets-types.h"
end_include

begin_include
include|#
directive|include
file|"gimpcursor.h"
end_include

begin_comment
comment|/*  standard gimp cursors  */
end_comment

begin_include
include|#
directive|include
file|"cursors/mouse.xbm"
end_include

begin_include
include|#
directive|include
file|"cursors/mouse_mask.xbm"
end_include

begin_include
include|#
directive|include
file|"cursors/crosshair.xbm"
end_include

begin_include
include|#
directive|include
file|"cursors/crosshair_mask.xbm"
end_include

begin_include
include|#
directive|include
file|"cursors/crosshair_small.xbm"
end_include

begin_include
include|#
directive|include
file|"cursors/crosshair_small_mask.xbm"
end_include

begin_include
include|#
directive|include
file|"cursors/bad.xbm"
end_include

begin_include
include|#
directive|include
file|"cursors/bad_mask.xbm"
end_include

begin_include
include|#
directive|include
file|"cursors/zoom.xbm"
end_include

begin_include
include|#
directive|include
file|"cursors/zoom_mask.xbm"
end_include

begin_include
include|#
directive|include
file|"cursors/dropper.xbm"
end_include

begin_include
include|#
directive|include
file|"cursors/dropper_mask.xbm"
end_include

begin_comment
comment|/*  stock tool cursors  */
end_comment

begin_include
include|#
directive|include
file|"cursors/rect_select_small.xbm"
end_include

begin_include
include|#
directive|include
file|"cursors/rect_select_small_mask.xbm"
end_include

begin_include
include|#
directive|include
file|"cursors/ellipse_select_small.xbm"
end_include

begin_include
include|#
directive|include
file|"cursors/ellipse_select_small_mask.xbm"
end_include

begin_include
include|#
directive|include
file|"cursors/free_select_small.xbm"
end_include

begin_include
include|#
directive|include
file|"cursors/free_select_small_mask.xbm"
end_include

begin_include
include|#
directive|include
file|"cursors/fuzzy_select_small.xbm"
end_include

begin_include
include|#
directive|include
file|"cursors/fuzzy_select_small_mask.xbm"
end_include

begin_include
include|#
directive|include
file|"cursors/bezier_select_small.xbm"
end_include

begin_include
include|#
directive|include
file|"cursors/bezier_select_small_mask.xbm"
end_include

begin_include
include|#
directive|include
file|"cursors/scissors_small.xbm"
end_include

begin_include
include|#
directive|include
file|"cursors/scissors_small_mask.xbm"
end_include

begin_include
include|#
directive|include
file|"cursors/move_small.xbm"
end_include

begin_include
include|#
directive|include
file|"cursors/move_small_mask.xbm"
end_include

begin_include
include|#
directive|include
file|"cursors/zoom_small.xbm"
end_include

begin_include
include|#
directive|include
file|"cursors/zoom_small_mask.xbm"
end_include

begin_include
include|#
directive|include
file|"cursors/crop_small.xbm"
end_include

begin_include
include|#
directive|include
file|"cursors/crop_small_mask.xbm"
end_include

begin_include
include|#
directive|include
file|"cursors/resize_small.xbm"
end_include

begin_include
include|#
directive|include
file|"cursors/resize_small_mask.xbm"
end_include

begin_include
include|#
directive|include
file|"cursors/rotate_small.xbm"
end_include

begin_include
include|#
directive|include
file|"cursors/rotate_small_mask.xbm"
end_include

begin_include
include|#
directive|include
file|"cursors/shear_small.xbm"
end_include

begin_include
include|#
directive|include
file|"cursors/shear_small_mask.xbm"
end_include

begin_include
include|#
directive|include
file|"cursors/perspective_small.xbm"
end_include

begin_include
include|#
directive|include
file|"cursors/perspective_small_mask.xbm"
end_include

begin_include
include|#
directive|include
file|"cursors/flip_horizontal_small.xbm"
end_include

begin_include
include|#
directive|include
file|"cursors/flip_horizontal_small_mask.xbm"
end_include

begin_include
include|#
directive|include
file|"cursors/flip_vertical_small.xbm"
end_include

begin_include
include|#
directive|include
file|"cursors/flip_vertical_small_mask.xbm"
end_include

begin_include
include|#
directive|include
file|"cursors/text_small.xbm"
end_include

begin_include
include|#
directive|include
file|"cursors/text_small_mask.xbm"
end_include

begin_include
include|#
directive|include
file|"cursors/dropper_small.xbm"
end_include

begin_include
include|#
directive|include
file|"cursors/dropper_small_mask.xbm"
end_include

begin_include
include|#
directive|include
file|"cursors/bucket_fill_small.xbm"
end_include

begin_include
include|#
directive|include
file|"cursors/bucket_fill_small_mask.xbm"
end_include

begin_include
include|#
directive|include
file|"cursors/blend_small.xbm"
end_include

begin_include
include|#
directive|include
file|"cursors/blend_small_mask.xbm"
end_include

begin_include
include|#
directive|include
file|"cursors/pencil_small.xbm"
end_include

begin_include
include|#
directive|include
file|"cursors/pencil_small_mask.xbm"
end_include

begin_include
include|#
directive|include
file|"cursors/paintbrush_small.xbm"
end_include

begin_include
include|#
directive|include
file|"cursors/paintbrush_small_mask.xbm"
end_include

begin_include
include|#
directive|include
file|"cursors/eraser_small.xbm"
end_include

begin_include
include|#
directive|include
file|"cursors/eraser_small_mask.xbm"
end_include

begin_include
include|#
directive|include
file|"cursors/airbrush_small.xbm"
end_include

begin_include
include|#
directive|include
file|"cursors/airbrush_small_mask.xbm"
end_include

begin_include
include|#
directive|include
file|"cursors/clone_small.xbm"
end_include

begin_include
include|#
directive|include
file|"cursors/clone_small_mask.xbm"
end_include

begin_include
include|#
directive|include
file|"cursors/blur_small.xbm"
end_include

begin_include
include|#
directive|include
file|"cursors/blur_small_mask.xbm"
end_include

begin_include
include|#
directive|include
file|"cursors/ink_small.xbm"
end_include

begin_include
include|#
directive|include
file|"cursors/ink_small_mask.xbm"
end_include

begin_include
include|#
directive|include
file|"cursors/dodge_small.xbm"
end_include

begin_include
include|#
directive|include
file|"cursors/dodge_small_mask.xbm"
end_include

begin_include
include|#
directive|include
file|"cursors/burn_small.xbm"
end_include

begin_include
include|#
directive|include
file|"cursors/burn_small_mask.xbm"
end_include

begin_include
include|#
directive|include
file|"cursors/smudge_small.xbm"
end_include

begin_include
include|#
directive|include
file|"cursors/smudge_small_mask.xbm"
end_include

begin_include
include|#
directive|include
file|"cursors/measure_small.xbm"
end_include

begin_include
include|#
directive|include
file|"cursors/measure_small_mask.xbm"
end_include

begin_comment
comment|/*  modifiers  */
end_comment

begin_include
include|#
directive|include
file|"cursors/plus.xbm"
end_include

begin_include
include|#
directive|include
file|"cursors/plus_mask.xbm"
end_include

begin_include
include|#
directive|include
file|"cursors/minus.xbm"
end_include

begin_include
include|#
directive|include
file|"cursors/minus_mask.xbm"
end_include

begin_include
include|#
directive|include
file|"cursors/intersect.xbm"
end_include

begin_include
include|#
directive|include
file|"cursors/intersect_mask.xbm"
end_include

begin_include
include|#
directive|include
file|"cursors/move.xbm"
end_include

begin_include
include|#
directive|include
file|"cursors/move_mask.xbm"
end_include

begin_include
include|#
directive|include
file|"cursors/resize.xbm"
end_include

begin_include
include|#
directive|include
file|"cursors/resize_mask.xbm"
end_include

begin_include
include|#
directive|include
file|"cursors/control.xbm"
end_include

begin_include
include|#
directive|include
file|"cursors/control_mask.xbm"
end_include

begin_include
include|#
directive|include
file|"cursors/anchor.xbm"
end_include

begin_include
include|#
directive|include
file|"cursors/anchor_mask.xbm"
end_include

begin_include
include|#
directive|include
file|"cursors/foreground.xbm"
end_include

begin_include
include|#
directive|include
file|"cursors/foreground_mask.xbm"
end_include

begin_include
include|#
directive|include
file|"cursors/background.xbm"
end_include

begin_include
include|#
directive|include
file|"cursors/background_mask.xbm"
end_include

begin_include
include|#
directive|include
file|"cursors/pattern.xbm"
end_include

begin_include
include|#
directive|include
file|"cursors/pattern_mask.xbm"
end_include

begin_include
include|#
directive|include
file|"cursors/hand.xbm"
end_include

begin_include
include|#
directive|include
file|"cursors/hand_mask.xbm"
end_include

begin_typedef
DECL|typedef|GimpBitmapCursor
typedef|typedef
name|struct
name|_GimpBitmapCursor
name|GimpBitmapCursor
typedef|;
end_typedef

begin_struct
DECL|struct|_GimpBitmapCursor
struct|struct
name|_GimpBitmapCursor
block|{
DECL|member|bits
name|guchar
modifier|*
name|bits
decl_stmt|;
DECL|member|mask_bits
name|guchar
modifier|*
name|mask_bits
decl_stmt|;
DECL|member|width
DECL|member|height
name|gint
name|width
decl_stmt|,
name|height
decl_stmt|;
DECL|member|x_hot
DECL|member|y_hot
name|gint
name|x_hot
decl_stmt|,
name|y_hot
decl_stmt|;
DECL|member|bitmap
name|GdkBitmap
modifier|*
name|bitmap
decl_stmt|;
DECL|member|mask
name|GdkBitmap
modifier|*
name|mask
decl_stmt|;
DECL|member|cursor
name|GdkCursor
modifier|*
name|cursor
decl_stmt|;
block|}
struct|;
end_struct

begin_decl_stmt
DECL|variable|gimp_cursors
specifier|static
name|GimpBitmapCursor
name|gimp_cursors
index|[]
init|=
comment|/* these have to match up with the enum in cursorutil.h */
block|{
block|{
name|mouse_bits
block|,
name|mouse_mask_bits
block|,
name|mouse_width
block|,
name|mouse_height
block|,
name|mouse_x_hot
block|,
name|mouse_y_hot
block|,
name|NULL
block|,
name|NULL
block|,
name|NULL
block|}
block|,
block|{
name|crosshair_bits
block|,
name|crosshair_mask_bits
block|,
name|crosshair_width
block|,
name|crosshair_height
block|,
name|crosshair_x_hot
block|,
name|crosshair_y_hot
block|,
name|NULL
block|,
name|NULL
block|,
name|NULL
block|}
block|,
block|{
name|crosshair_small_bits
block|,
name|crosshair_small_mask_bits
block|,
name|crosshair_small_width
block|,
name|crosshair_small_height
block|,
name|crosshair_small_x_hot
block|,
name|crosshair_small_y_hot
block|,
name|NULL
block|,
name|NULL
block|,
name|NULL
block|}
block|,
block|{
name|bad_bits
block|,
name|bad_mask_bits
block|,
name|bad_width
block|,
name|bad_height
block|,
name|bad_x_hot
block|,
name|bad_y_hot
block|,
name|NULL
block|,
name|NULL
block|,
name|NULL
block|}
block|,
block|{
name|zoom_bits
block|,
name|zoom_mask_bits
block|,
name|zoom_width
block|,
name|zoom_height
block|,
name|zoom_x_hot
block|,
name|zoom_y_hot
block|,
name|NULL
block|,
name|NULL
block|,
name|NULL
block|}
block|,
block|{
name|dropper_bits
block|,
name|dropper_mask_bits
block|,
name|dropper_width
block|,
name|dropper_height
block|,
name|dropper_x_hot
block|,
name|dropper_y_hot
block|,
name|NULL
block|,
name|NULL
block|,
name|NULL
block|}
block|}
decl_stmt|;
end_decl_stmt

begin_decl_stmt
DECL|variable|gimp_stock_tool_cursors
specifier|static
name|GimpBitmapCursor
name|gimp_stock_tool_cursors
index|[]
init|=
comment|/* these have to match up with the enum in widgets-types.h */
block|{
block|{
name|NULL
block|,
name|NULL
block|,
literal|0
block|,
literal|0
block|,
literal|0
block|,
literal|0
block|,
name|NULL
block|,
name|NULL
block|,
name|NULL
block|}
block|,
block|{
name|rect_select_small_bits
block|,
name|rect_select_small_mask_bits
block|,
name|rect_select_small_width
block|,
name|rect_select_small_height
block|,
literal|0
block|,
literal|0
block|,
name|NULL
block|,
name|NULL
block|,
name|NULL
block|}
block|,
block|{
name|ellipse_select_small_bits
block|,
name|ellipse_select_small_mask_bits
block|,
name|ellipse_select_small_width
block|,
name|ellipse_select_small_height
block|,
literal|0
block|,
literal|0
block|,
name|NULL
block|,
name|NULL
block|,
name|NULL
block|}
block|,
block|{
name|free_select_small_bits
block|,
name|free_select_small_mask_bits
block|,
name|free_select_small_width
block|,
name|free_select_small_height
block|,
literal|0
block|,
literal|0
block|,
name|NULL
block|,
name|NULL
block|,
name|NULL
block|}
block|,
block|{
name|fuzzy_select_small_bits
block|,
name|fuzzy_select_small_mask_bits
block|,
name|fuzzy_select_small_width
block|,
name|fuzzy_select_small_height
block|,
literal|0
block|,
literal|0
block|,
name|NULL
block|,
name|NULL
block|,
name|NULL
block|}
block|,
block|{
name|bezier_select_small_bits
block|,
name|bezier_select_small_mask_bits
block|,
name|bezier_select_small_width
block|,
name|bezier_select_small_height
block|,
literal|0
block|,
literal|0
block|,
name|NULL
block|,
name|NULL
block|,
name|NULL
block|}
block|,
block|{
name|scissors_small_bits
block|,
name|scissors_small_mask_bits
block|,
name|scissors_small_width
block|,
name|scissors_small_height
block|,
literal|0
block|,
literal|0
block|,
name|NULL
block|,
name|NULL
block|,
name|NULL
block|}
block|,
block|{
name|move_small_bits
block|,
name|move_small_mask_bits
block|,
name|move_small_width
block|,
name|move_small_height
block|,
literal|0
block|,
literal|0
block|,
name|NULL
block|,
name|NULL
block|,
name|NULL
block|}
block|,
block|{
name|zoom_small_bits
block|,
name|zoom_small_mask_bits
block|,
name|zoom_small_width
block|,
name|zoom_small_height
block|,
literal|0
block|,
literal|0
block|,
name|NULL
block|,
name|NULL
block|,
name|NULL
block|}
block|,
block|{
name|crop_small_bits
block|,
name|crop_small_mask_bits
block|,
name|crop_small_width
block|,
name|crop_small_height
block|,
literal|0
block|,
literal|0
block|,
name|NULL
block|,
name|NULL
block|,
name|NULL
block|}
block|,
block|{
name|resize_small_bits
block|,
name|resize_small_mask_bits
block|,
name|resize_small_width
block|,
name|resize_small_height
block|,
literal|0
block|,
literal|0
block|,
name|NULL
block|,
name|NULL
block|,
name|NULL
block|}
block|,
block|{
name|rotate_small_bits
block|,
name|rotate_small_mask_bits
block|,
name|rotate_small_width
block|,
name|rotate_small_height
block|,
literal|0
block|,
literal|0
block|,
name|NULL
block|,
name|NULL
block|,
name|NULL
block|}
block|,
block|{
name|shear_small_bits
block|,
name|shear_small_mask_bits
block|,
name|shear_small_width
block|,
name|shear_small_height
block|,
literal|0
block|,
literal|0
block|,
name|NULL
block|,
name|NULL
block|,
name|NULL
block|}
block|,
block|{
name|perspective_small_bits
block|,
name|perspective_small_mask_bits
block|,
name|perspective_small_width
block|,
name|perspective_small_height
block|,
literal|0
block|,
literal|0
block|,
name|NULL
block|,
name|NULL
block|,
name|NULL
block|}
block|,
block|{
name|flip_horizontal_small_bits
block|,
name|flip_horizontal_small_mask_bits
block|,
name|flip_horizontal_small_width
block|,
name|flip_horizontal_small_height
block|,
literal|0
block|,
literal|0
block|,
name|NULL
block|,
name|NULL
block|,
name|NULL
block|}
block|,
block|{
name|flip_vertical_small_bits
block|,
name|flip_vertical_small_mask_bits
block|,
name|flip_vertical_small_width
block|,
name|flip_vertical_small_height
block|,
literal|0
block|,
literal|0
block|,
name|NULL
block|,
name|NULL
block|,
name|NULL
block|}
block|,
block|{
name|text_small_bits
block|,
name|text_small_mask_bits
block|,
name|text_small_width
block|,
name|text_small_height
block|,
literal|0
block|,
literal|0
block|,
name|NULL
block|,
name|NULL
block|,
name|NULL
block|}
block|,
block|{
name|dropper_small_bits
block|,
name|dropper_small_mask_bits
block|,
name|dropper_small_width
block|,
name|dropper_small_height
block|,
literal|0
block|,
literal|0
block|,
name|NULL
block|,
name|NULL
block|,
name|NULL
block|}
block|,
block|{
name|bucket_fill_small_bits
block|,
name|bucket_fill_small_mask_bits
block|,
name|bucket_fill_small_width
block|,
name|bucket_fill_small_height
block|,
literal|0
block|,
literal|0
block|,
name|NULL
block|,
name|NULL
block|,
name|NULL
block|}
block|,
block|{
name|blend_small_bits
block|,
name|blend_small_mask_bits
block|,
name|blend_small_width
block|,
name|blend_small_height
block|,
literal|0
block|,
literal|0
block|,
name|NULL
block|,
name|NULL
block|,
name|NULL
block|}
block|,
block|{
name|pencil_small_bits
block|,
name|pencil_small_mask_bits
block|,
name|pencil_small_width
block|,
name|pencil_small_height
block|,
literal|0
block|,
literal|0
block|,
name|NULL
block|,
name|NULL
block|,
name|NULL
block|}
block|,
block|{
name|paintbrush_small_bits
block|,
name|paintbrush_small_mask_bits
block|,
name|paintbrush_small_width
block|,
name|paintbrush_small_height
block|,
literal|0
block|,
literal|0
block|,
name|NULL
block|,
name|NULL
block|,
name|NULL
block|}
block|,
block|{
name|airbrush_small_bits
block|,
name|airbrush_small_mask_bits
block|,
name|airbrush_small_width
block|,
name|airbrush_small_height
block|,
literal|0
block|,
literal|0
block|,
name|NULL
block|,
name|NULL
block|,
name|NULL
block|}
block|,
block|{
name|ink_small_bits
block|,
name|ink_small_mask_bits
block|,
name|ink_small_width
block|,
name|ink_small_height
block|,
literal|0
block|,
literal|0
block|,
name|NULL
block|,
name|NULL
block|,
name|NULL
block|}
block|,
block|{
name|clone_small_bits
block|,
name|clone_small_mask_bits
block|,
name|clone_small_width
block|,
name|clone_small_height
block|,
literal|0
block|,
literal|0
block|,
name|NULL
block|,
name|NULL
block|,
name|NULL
block|}
block|,
block|{
name|eraser_small_bits
block|,
name|eraser_small_mask_bits
block|,
name|eraser_small_width
block|,
name|eraser_small_height
block|,
literal|0
block|,
literal|0
block|,
name|NULL
block|,
name|NULL
block|,
name|NULL
block|}
block|,
block|{
name|smudge_small_bits
block|,
name|smudge_small_mask_bits
block|,
name|smudge_small_width
block|,
name|smudge_small_height
block|,
literal|0
block|,
literal|0
block|,
name|NULL
block|,
name|NULL
block|,
name|NULL
block|}
block|,
block|{
name|blur_small_bits
block|,
name|blur_small_mask_bits
block|,
name|blur_small_width
block|,
name|blur_small_height
block|,
literal|0
block|,
literal|0
block|,
name|NULL
block|,
name|NULL
block|,
name|NULL
block|}
block|,
block|{
name|dodge_small_bits
block|,
name|dodge_small_mask_bits
block|,
name|dodge_small_width
block|,
name|dodge_small_height
block|,
literal|0
block|,
literal|0
block|,
name|NULL
block|,
name|NULL
block|,
name|NULL
block|}
block|,
block|{
name|burn_small_bits
block|,
name|burn_small_mask_bits
block|,
name|burn_small_width
block|,
name|burn_small_height
block|,
literal|0
block|,
literal|0
block|,
name|NULL
block|,
name|NULL
block|,
name|NULL
block|}
block|,
block|{
name|measure_small_bits
block|,
name|measure_small_mask_bits
block|,
name|measure_small_width
block|,
name|measure_small_height
block|,
literal|0
block|,
literal|0
block|,
name|NULL
block|,
name|NULL
block|,
name|NULL
block|}
block|}
decl_stmt|;
end_decl_stmt

begin_decl_stmt
DECL|variable|gimp_modifier_cursors
specifier|static
name|GimpBitmapCursor
name|gimp_modifier_cursors
index|[]
init|=
comment|/* these have to match up with the enum in widgets-types.h */
block|{
block|{
name|NULL
block|,
name|NULL
block|,
literal|0
block|,
literal|0
block|,
literal|0
block|,
literal|0
block|,
name|NULL
block|,
name|NULL
block|,
name|NULL
block|}
block|,
block|{
name|plus_bits
block|,
name|plus_mask_bits
block|,
name|plus_width
block|,
name|plus_height
block|,
name|plus_x_hot
block|,
name|plus_y_hot
block|,
name|NULL
block|,
name|NULL
block|,
name|NULL
block|}
block|,
block|{
name|minus_bits
block|,
name|minus_mask_bits
block|,
name|minus_width
block|,
name|minus_height
block|,
name|minus_x_hot
block|,
name|minus_y_hot
block|,
name|NULL
block|,
name|NULL
block|,
name|NULL
block|}
block|,
block|{
name|intersect_bits
block|,
name|intersect_mask_bits
block|,
name|intersect_width
block|,
name|intersect_height
block|,
name|intersect_x_hot
block|,
name|intersect_y_hot
block|,
name|NULL
block|,
name|NULL
block|,
name|NULL
block|}
block|,
block|{
name|move_bits
block|,
name|move_mask_bits
block|,
name|move_width
block|,
name|move_height
block|,
name|move_x_hot
block|,
name|move_y_hot
block|,
name|NULL
block|,
name|NULL
block|,
name|NULL
block|}
block|,
block|{
name|resize_bits
block|,
name|resize_mask_bits
block|,
name|resize_width
block|,
name|resize_height
block|,
name|resize_x_hot
block|,
name|resize_y_hot
block|,
name|NULL
block|,
name|NULL
block|,
name|NULL
block|}
block|,
block|{
name|control_bits
block|,
name|control_mask_bits
block|,
name|control_width
block|,
name|control_height
block|,
name|control_x_hot
block|,
name|control_y_hot
block|,
name|NULL
block|,
name|NULL
block|,
name|NULL
block|}
block|,
block|{
name|anchor_bits
block|,
name|anchor_mask_bits
block|,
name|anchor_width
block|,
name|anchor_height
block|,
name|anchor_x_hot
block|,
name|anchor_y_hot
block|,
name|NULL
block|,
name|NULL
block|,
name|NULL
block|}
block|,
block|{
name|foreground_bits
block|,
name|foreground_mask_bits
block|,
name|foreground_width
block|,
name|foreground_height
block|,
name|foreground_x_hot
block|,
name|foreground_y_hot
block|,
name|NULL
block|,
name|NULL
block|,
name|NULL
block|}
block|,
block|{
name|background_bits
block|,
name|background_mask_bits
block|,
name|background_width
block|,
name|background_height
block|,
name|background_x_hot
block|,
name|background_y_hot
block|,
name|NULL
block|,
name|NULL
block|,
name|NULL
block|}
block|,
block|{
name|pattern_bits
block|,
name|pattern_mask_bits
block|,
name|pattern_width
block|,
name|pattern_height
block|,
name|pattern_x_hot
block|,
name|pattern_y_hot
block|,
name|NULL
block|,
name|NULL
block|,
name|NULL
block|}
block|,
block|{
name|hand_bits
block|,
name|hand_mask_bits
block|,
name|hand_width
block|,
name|hand_height
block|,
name|hand_x_hot
block|,
name|hand_y_hot
block|,
name|NULL
block|,
name|NULL
block|,
name|NULL
block|}
block|}
decl_stmt|;
end_decl_stmt

begin_function
specifier|static
name|void
DECL|function|create_cursor_bitmaps (GimpBitmapCursor * bmcursor)
name|create_cursor_bitmaps
parameter_list|(
name|GimpBitmapCursor
modifier|*
name|bmcursor
parameter_list|)
block|{
if|if
condition|(
name|bmcursor
operator|->
name|bitmap
operator|==
name|NULL
condition|)
name|bmcursor
operator|->
name|bitmap
operator|=
name|gdk_bitmap_create_from_data
argument_list|(
name|NULL
argument_list|,
name|bmcursor
operator|->
name|bits
argument_list|,
name|bmcursor
operator|->
name|width
argument_list|,
name|bmcursor
operator|->
name|height
argument_list|)
expr_stmt|;
name|g_return_if_fail
argument_list|(
name|bmcursor
operator|->
name|bitmap
operator|!=
name|NULL
argument_list|)
expr_stmt|;
if|if
condition|(
name|bmcursor
operator|->
name|mask
operator|==
name|NULL
condition|)
name|bmcursor
operator|->
name|mask
operator|=
name|gdk_bitmap_create_from_data
argument_list|(
name|NULL
argument_list|,
name|bmcursor
operator|->
name|mask_bits
argument_list|,
name|bmcursor
operator|->
name|width
argument_list|,
name|bmcursor
operator|->
name|height
argument_list|)
expr_stmt|;
name|g_return_if_fail
argument_list|(
name|bmcursor
operator|->
name|mask
operator|!=
name|NULL
argument_list|)
expr_stmt|;
block|}
end_function

begin_comment
comment|/* static void create_cursor (GimpBitmapCursor *bmcursor) {   if (bmcursor->bitmap == NULL ||       bmcursor->mask == NULL)     create_cursor_bitmaps (bmcursor);    if (bmcursor->cursor == NULL)     {       GdkColor fg, bg;        * should have a way to configure the mouse colors *       gdk_color_parse ("#FFFFFF",&bg);       gdk_color_parse ("#000000",&fg);        bmcursor->cursor = gdk_cursor_new_from_pixmap (bmcursor->bitmap, 						     bmcursor->mask,&fg,&bg, 						     bmcursor->x_hot, 						     bmcursor->y_hot);     }    g_return_if_fail (bmcursor->cursor != NULL); } */
end_comment

begin_function
name|GdkCursor
modifier|*
DECL|function|gimp_cursor_new (GimpCursorType cursor_type,GimpToolCursorType tool_cursor,GimpCursorModifier modifier)
name|gimp_cursor_new
parameter_list|(
name|GimpCursorType
name|cursor_type
parameter_list|,
name|GimpToolCursorType
name|tool_cursor
parameter_list|,
name|GimpCursorModifier
name|modifier
parameter_list|)
block|{
name|GdkCursor
modifier|*
name|cursor
decl_stmt|;
name|GdkBitmap
modifier|*
name|bitmap
decl_stmt|;
name|GdkBitmap
modifier|*
name|mask
decl_stmt|;
name|GdkColor
name|color
decl_stmt|;
name|GdkColor
name|fg
decl_stmt|,
name|bg
decl_stmt|;
specifier|static
name|GdkGC
modifier|*
name|gc
init|=
name|NULL
decl_stmt|;
name|gint
name|width
decl_stmt|;
name|gint
name|height
decl_stmt|;
name|GimpBitmapCursor
modifier|*
name|bmcursor
init|=
name|NULL
decl_stmt|;
name|GimpBitmapCursor
modifier|*
name|bmmodifier
init|=
name|NULL
decl_stmt|;
name|GimpBitmapCursor
modifier|*
name|bmtool
init|=
name|NULL
decl_stmt|;
name|g_return_val_if_fail
argument_list|(
name|cursor_type
operator|<
name|GIMP_LAST_CURSOR_ENTRY
argument_list|,
name|NULL
argument_list|)
expr_stmt|;
if|if
condition|(
name|cursor_type
operator|<=
name|GDK_LAST_CURSOR
condition|)
block|{
return|return
name|gdk_cursor_new
argument_list|(
name|cursor_type
argument_list|)
return|;
block|}
comment|/*  allow the small tool cursor only with the standard mouse,    *  the small crosshair and the bad cursor    */
if|if
condition|(
name|cursor_type
operator|!=
name|GIMP_MOUSE_CURSOR
operator|&&
name|cursor_type
operator|!=
name|GIMP_CROSSHAIR_SMALL_CURSOR
operator|&&
name|cursor_type
operator|!=
name|GIMP_BAD_CURSOR
condition|)
block|{
name|tool_cursor
operator|=
name|GIMP_TOOL_CURSOR_NONE
expr_stmt|;
block|}
name|cursor_type
operator|-=
name|GIMP_MOUSE_CURSOR
expr_stmt|;
name|bmcursor
operator|=
operator|&
name|gimp_cursors
index|[
operator|(
name|gint
operator|)
name|cursor_type
index|]
expr_stmt|;
comment|/*  if there are no modifiers, we can show the cursor immediately    */
comment|/* FIXME: ref the cursor in gtk-2.0 before returning it   if (modifier    == GIMP_CURSOR_MODIFIER_NONE&&       tool_cursor == GIMP_TOOL_CURSOR_NONE)     {       if  (bmcursor->cursor == NULL) 	create_cursor (bmcursor);        gdk_window_set_cursor (window, bmcursor->cursor);        return;     }     else */
if|if
condition|(
name|bmcursor
operator|->
name|bitmap
operator|==
name|NULL
operator|||
name|bmcursor
operator|->
name|mask
operator|==
name|NULL
condition|)
block|{
name|create_cursor_bitmaps
argument_list|(
name|bmcursor
argument_list|)
expr_stmt|;
block|}
comment|/*  prepare the tool cursor  */
if|if
condition|(
name|tool_cursor
operator|<
name|GIMP_TOOL_CURSOR_NONE
operator|||
name|tool_cursor
operator|>=
name|GIMP_LAST_STOCK_TOOL_CURSOR_ENTRY
condition|)
block|{
name|tool_cursor
operator|=
name|GIMP_TOOL_CURSOR_NONE
expr_stmt|;
block|}
if|if
condition|(
name|tool_cursor
operator|!=
name|GIMP_TOOL_CURSOR_NONE
condition|)
block|{
name|bmtool
operator|=
operator|&
name|gimp_stock_tool_cursors
index|[
operator|(
name|gint
operator|)
name|tool_cursor
index|]
expr_stmt|;
if|if
condition|(
name|bmtool
operator|->
name|bitmap
operator|==
name|NULL
operator|||
name|bmtool
operator|->
name|mask
operator|==
name|NULL
condition|)
block|{
name|create_cursor_bitmaps
argument_list|(
name|bmtool
argument_list|)
expr_stmt|;
block|}
block|}
comment|/*  prepare the cursor modifier  */
if|if
condition|(
name|modifier
operator|<
name|GIMP_CURSOR_MODIFIER_NONE
operator|||
name|modifier
operator|>=
name|GIMP_LAST_CURSOR_MODIFIER_ENTRY
condition|)
block|{
name|modifier
operator|=
name|GIMP_CURSOR_MODIFIER_NONE
expr_stmt|;
block|}
if|if
condition|(
name|modifier
operator|!=
name|GIMP_CURSOR_MODIFIER_NONE
condition|)
block|{
name|bmmodifier
operator|=
operator|&
name|gimp_modifier_cursors
index|[
operator|(
name|gint
operator|)
name|modifier
index|]
expr_stmt|;
if|if
condition|(
name|bmmodifier
operator|->
name|bitmap
operator|==
name|NULL
operator|||
name|bmmodifier
operator|->
name|mask
operator|==
name|NULL
condition|)
block|{
name|create_cursor_bitmaps
argument_list|(
name|bmmodifier
argument_list|)
expr_stmt|;
block|}
block|}
if|if
condition|(
name|gc
operator|==
name|NULL
condition|)
name|gc
operator|=
name|gdk_gc_new
argument_list|(
name|bmcursor
operator|->
name|bitmap
argument_list|)
expr_stmt|;
name|gdk_drawable_get_size
argument_list|(
name|bmcursor
operator|->
name|bitmap
argument_list|,
operator|&
name|width
argument_list|,
operator|&
name|height
argument_list|)
expr_stmt|;
comment|/*  new bitmap and mask for on-the-fly cursor creation  */
name|bitmap
operator|=
name|gdk_pixmap_new
argument_list|(
name|NULL
argument_list|,
name|width
argument_list|,
name|height
argument_list|,
literal|1
argument_list|)
expr_stmt|;
name|mask
operator|=
name|gdk_pixmap_new
argument_list|(
name|NULL
argument_list|,
name|width
argument_list|,
name|height
argument_list|,
literal|1
argument_list|)
expr_stmt|;
name|color
operator|.
name|pixel
operator|=
literal|1
expr_stmt|;
name|gdk_gc_set_foreground
argument_list|(
name|gc
argument_list|,
operator|&
name|color
argument_list|)
expr_stmt|;
comment|/*  first draw the bitmap completely ... */
name|gdk_draw_drawable
argument_list|(
name|bitmap
argument_list|,
name|gc
argument_list|,
name|bmcursor
operator|->
name|bitmap
argument_list|,
literal|0
argument_list|,
literal|0
argument_list|,
literal|0
argument_list|,
literal|0
argument_list|,
name|width
argument_list|,
name|height
argument_list|)
expr_stmt|;
if|if
condition|(
name|bmmodifier
condition|)
block|{
name|gdk_gc_set_clip_mask
argument_list|(
name|gc
argument_list|,
name|bmmodifier
operator|->
name|bitmap
argument_list|)
expr_stmt|;
name|gdk_draw_drawable
argument_list|(
name|bitmap
argument_list|,
name|gc
argument_list|,
name|bmmodifier
operator|->
name|bitmap
argument_list|,
literal|0
argument_list|,
literal|0
argument_list|,
literal|0
argument_list|,
literal|0
argument_list|,
name|width
argument_list|,
name|height
argument_list|)
expr_stmt|;
name|gdk_gc_set_clip_mask
argument_list|(
name|gc
argument_list|,
name|NULL
argument_list|)
expr_stmt|;
block|}
if|if
condition|(
name|bmtool
condition|)
block|{
name|gdk_gc_set_clip_mask
argument_list|(
name|gc
argument_list|,
name|bmtool
operator|->
name|bitmap
argument_list|)
expr_stmt|;
name|gdk_draw_drawable
argument_list|(
name|bitmap
argument_list|,
name|gc
argument_list|,
name|bmtool
operator|->
name|bitmap
argument_list|,
literal|0
argument_list|,
literal|0
argument_list|,
literal|0
argument_list|,
literal|0
argument_list|,
name|width
argument_list|,
name|height
argument_list|)
expr_stmt|;
name|gdk_gc_set_clip_mask
argument_list|(
name|gc
argument_list|,
name|NULL
argument_list|)
expr_stmt|;
block|}
comment|/*  ... then the mask  */
name|gdk_draw_drawable
argument_list|(
name|mask
argument_list|,
name|gc
argument_list|,
name|bmcursor
operator|->
name|mask
argument_list|,
literal|0
argument_list|,
literal|0
argument_list|,
literal|0
argument_list|,
literal|0
argument_list|,
name|width
argument_list|,
name|height
argument_list|)
expr_stmt|;
if|if
condition|(
name|bmmodifier
condition|)
block|{
name|gdk_gc_set_clip_mask
argument_list|(
name|gc
argument_list|,
name|bmmodifier
operator|->
name|mask
argument_list|)
expr_stmt|;
name|gdk_draw_drawable
argument_list|(
name|mask
argument_list|,
name|gc
argument_list|,
name|bmmodifier
operator|->
name|mask
argument_list|,
literal|0
argument_list|,
literal|0
argument_list|,
literal|0
argument_list|,
literal|0
argument_list|,
name|width
argument_list|,
name|height
argument_list|)
expr_stmt|;
name|gdk_gc_set_clip_mask
argument_list|(
name|gc
argument_list|,
name|NULL
argument_list|)
expr_stmt|;
block|}
if|if
condition|(
name|bmtool
condition|)
block|{
name|gdk_gc_set_clip_mask
argument_list|(
name|gc
argument_list|,
name|bmtool
operator|->
name|mask
argument_list|)
expr_stmt|;
name|gdk_draw_drawable
argument_list|(
name|mask
argument_list|,
name|gc
argument_list|,
name|bmtool
operator|->
name|mask
argument_list|,
literal|0
argument_list|,
literal|0
argument_list|,
literal|0
argument_list|,
literal|0
argument_list|,
name|width
argument_list|,
name|height
argument_list|)
expr_stmt|;
name|gdk_gc_set_clip_mask
argument_list|(
name|gc
argument_list|,
name|NULL
argument_list|)
expr_stmt|;
block|}
comment|/* should have a way to configure the mouse colors */
name|gdk_color_parse
argument_list|(
literal|"#FFFFFF"
argument_list|,
operator|&
name|bg
argument_list|)
expr_stmt|;
name|gdk_color_parse
argument_list|(
literal|"#000000"
argument_list|,
operator|&
name|fg
argument_list|)
expr_stmt|;
name|cursor
operator|=
name|gdk_cursor_new_from_pixmap
argument_list|(
name|bitmap
argument_list|,
name|mask
argument_list|,
operator|&
name|fg
argument_list|,
operator|&
name|bg
argument_list|,
name|bmcursor
operator|->
name|x_hot
argument_list|,
name|bmcursor
operator|->
name|y_hot
argument_list|)
expr_stmt|;
name|g_object_unref
argument_list|(
name|bitmap
argument_list|)
expr_stmt|;
name|g_object_unref
argument_list|(
name|mask
argument_list|)
expr_stmt|;
return|return
name|cursor
return|;
block|}
end_function

end_unit

