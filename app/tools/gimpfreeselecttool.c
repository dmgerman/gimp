begin_unit|revision:0.9.5;language:C;cregit-version:0.0.1
begin_comment
comment|/* The GIMP -- an image manipulation program  * Copyright (C) 1995 Spencer Kimball and Peter Mattis  *  * This program is free software; you can redistribute it and/or modify  * it under the terms of the GNU General Public License as published by  * the Free Software Foundation; either version 2 of the License, or  * (at your option) any later version.  *  * This program is distributed in the hope that it will be useful,  * but WITHOUT ANY WARRANTY; without even the implied warranty of  * MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the  * GNU General Public License for more details.  *  * You should have received a copy of the GNU General Public License  * along with this program; if not, write to the Free Software  * Foundation, Inc., 675 Mass Ave, Cambridge, MA 02139, USA.  */
end_comment

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
file|"appenv.h"
end_include

begin_include
include|#
directive|include
file|"draw_core.h"
end_include

begin_include
include|#
directive|include
file|"edit_selection.h"
end_include

begin_include
include|#
directive|include
file|"errors.h"
end_include

begin_include
include|#
directive|include
file|"free_select.h"
end_include

begin_include
include|#
directive|include
file|"gimage_mask.h"
end_include

begin_include
include|#
directive|include
file|"gdisplay.h"
end_include

begin_include
include|#
directive|include
file|"linked.h"
end_include

begin_include
include|#
directive|include
file|"rect_select.h"
end_include

begin_typedef
DECL|typedef|FreeSelect
typedef|typedef
name|struct
name|_free_select
name|FreeSelect
typedef|;
end_typedef

begin_struct
DECL|struct|_free_select
struct|struct
name|_free_select
block|{
DECL|member|core
name|DrawCore
modifier|*
name|core
decl_stmt|;
comment|/*  Core select object                      */
DECL|member|num_pts
name|int
name|num_pts
decl_stmt|;
comment|/*  Number of points in the polygon         */
DECL|member|op
name|int
name|op
decl_stmt|;
comment|/*  selection operation (ADD, SUB, etc)     */
block|}
struct|;
end_struct

begin_typedef
DECL|typedef|FreeSelectPoint
typedef|typedef
name|struct
name|_FreeSelectPoint
name|FreeSelectPoint
typedef|;
end_typedef

begin_struct
DECL|struct|_FreeSelectPoint
struct|struct
name|_FreeSelectPoint
block|{
DECL|member|x
DECL|member|y
name|double
name|x
decl_stmt|,
name|y
decl_stmt|;
block|}
struct|;
end_struct

begin_define
DECL|macro|DEFAULT_MAX_INC
define|#
directive|define
name|DEFAULT_MAX_INC
value|1024
end_define

begin_define
DECL|macro|ROUND (x)
define|#
directive|define
name|ROUND
parameter_list|(
name|x
parameter_list|)
value|((int) (x + 0.5))
end_define

begin_define
DECL|macro|SUPERSAMPLE
define|#
directive|define
name|SUPERSAMPLE
value|3
end_define

begin_define
DECL|macro|SUPERSAMPLE2
define|#
directive|define
name|SUPERSAMPLE2
value|9
end_define

begin_define
DECL|macro|NO
define|#
directive|define
name|NO
value|0
end_define

begin_define
DECL|macro|YES
define|#
directive|define
name|YES
value|1
end_define

begin_comment
comment|/*  The global array of XPoints for drawing the polygon...  */
end_comment

begin_decl_stmt
DECL|variable|global_pts
specifier|static
name|GdkPoint
modifier|*
name|global_pts
init|=
name|NULL
decl_stmt|;
end_decl_stmt

begin_decl_stmt
DECL|variable|max_segs
specifier|static
name|int
name|max_segs
init|=
literal|0
decl_stmt|;
end_decl_stmt

begin_decl_stmt
DECL|variable|free_options
specifier|static
name|SelectionOptions
modifier|*
name|free_options
init|=
name|NULL
decl_stmt|;
end_decl_stmt

begin_function_decl
specifier|static
name|Argument
modifier|*
name|free_select_invoker
parameter_list|(
name|Argument
modifier|*
parameter_list|)
function_decl|;
end_function_decl

begin_function
specifier|static
name|int
DECL|function|add_point (int num_pts,int x,int y)
name|add_point
parameter_list|(
name|int
name|num_pts
parameter_list|,
name|int
name|x
parameter_list|,
name|int
name|y
parameter_list|)
block|{
if|if
condition|(
name|num_pts
operator|>=
name|max_segs
condition|)
block|{
name|max_segs
operator|+=
name|DEFAULT_MAX_INC
expr_stmt|;
name|global_pts
operator|=
operator|(
name|GdkPoint
operator|*
operator|)
name|g_realloc
argument_list|(
operator|(
name|void
operator|*
operator|)
name|global_pts
argument_list|,
sizeof|sizeof
argument_list|(
name|GdkPoint
argument_list|)
operator|*
name|max_segs
argument_list|)
expr_stmt|;
if|if
condition|(
operator|!
name|global_pts
condition|)
name|fatal_error
argument_list|(
literal|"Unable to reallocate points array in free_select."
argument_list|)
expr_stmt|;
block|}
name|global_pts
index|[
name|num_pts
index|]
operator|.
name|x
operator|=
name|x
expr_stmt|;
name|global_pts
index|[
name|num_pts
index|]
operator|.
name|y
operator|=
name|y
expr_stmt|;
return|return
literal|1
return|;
block|}
end_function

begin_comment
comment|/*  Routines to scan convert the polygon  */
end_comment

begin_function
specifier|static
name|link_ptr
DECL|function|insert_into_sorted_list (link_ptr list,int x)
name|insert_into_sorted_list
parameter_list|(
name|link_ptr
name|list
parameter_list|,
name|int
name|x
parameter_list|)
block|{
name|link_ptr
name|orig
init|=
name|list
decl_stmt|;
name|link_ptr
name|rest
decl_stmt|;
if|if
condition|(
operator|!
name|list
condition|)
return|return
name|add_to_list
argument_list|(
name|list
argument_list|,
call|(
name|gpointer
call|)
argument_list|(
operator|(
name|long
operator|)
name|x
argument_list|)
argument_list|)
return|;
while|while
condition|(
name|list
condition|)
block|{
name|rest
operator|=
name|next_item
argument_list|(
name|list
argument_list|)
expr_stmt|;
if|if
condition|(
name|x
operator|<
operator|(
name|long
operator|)
name|list
operator|->
name|data
condition|)
block|{
name|rest
operator|=
name|add_to_list
argument_list|(
name|rest
argument_list|,
name|list
operator|->
name|data
argument_list|)
expr_stmt|;
name|list
operator|->
name|next
operator|=
name|rest
expr_stmt|;
name|list
operator|->
name|data
operator|=
call|(
name|gpointer
call|)
argument_list|(
operator|(
name|long
operator|)
name|x
argument_list|)
expr_stmt|;
return|return
name|orig
return|;
block|}
elseif|else
if|if
condition|(
operator|!
name|rest
condition|)
block|{
name|append_to_list
argument_list|(
name|list
argument_list|,
call|(
name|gpointer
call|)
argument_list|(
operator|(
name|long
operator|)
name|x
argument_list|)
argument_list|)
expr_stmt|;
return|return
name|orig
return|;
block|}
name|list
operator|=
name|next_item
argument_list|(
name|list
argument_list|)
expr_stmt|;
block|}
return|return
name|orig
return|;
block|}
end_function

begin_function
specifier|static
name|void
DECL|function|convert_segment (link_ptr * scanlines,int width,int height,int x1,int y1,int x2,int y2)
name|convert_segment
parameter_list|(
name|link_ptr
modifier|*
name|scanlines
parameter_list|,
name|int
name|width
parameter_list|,
name|int
name|height
parameter_list|,
name|int
name|x1
parameter_list|,
name|int
name|y1
parameter_list|,
name|int
name|x2
parameter_list|,
name|int
name|y2
parameter_list|)
block|{
name|int
name|ydiff
decl_stmt|,
name|y
decl_stmt|,
name|tmp
decl_stmt|;
name|float
name|xinc
decl_stmt|,
name|xstart
decl_stmt|;
if|if
condition|(
name|y1
operator|>
name|y2
condition|)
block|{
name|tmp
operator|=
name|y2
expr_stmt|;
name|y2
operator|=
name|y1
expr_stmt|;
name|y1
operator|=
name|tmp
expr_stmt|;
name|tmp
operator|=
name|x2
expr_stmt|;
name|x2
operator|=
name|x1
expr_stmt|;
name|x1
operator|=
name|tmp
expr_stmt|;
block|}
name|ydiff
operator|=
operator|(
name|y2
operator|-
name|y1
operator|)
expr_stmt|;
if|if
condition|(
name|ydiff
condition|)
block|{
name|xinc
operator|=
call|(
name|float
call|)
argument_list|(
name|x2
operator|-
name|x1
argument_list|)
operator|/
operator|(
name|float
operator|)
name|ydiff
expr_stmt|;
name|xstart
operator|=
name|x1
operator|+
literal|0.5
operator|*
name|xinc
expr_stmt|;
for|for
control|(
name|y
operator|=
name|y1
init|;
name|y
operator|<
name|y2
condition|;
name|y
operator|++
control|)
block|{
if|if
condition|(
name|y
operator|>=
literal|0
operator|&&
name|y
operator|<
name|height
condition|)
name|scanlines
index|[
name|y
index|]
operator|=
name|insert_into_sorted_list
argument_list|(
name|scanlines
index|[
name|y
index|]
argument_list|,
name|ROUND
argument_list|(
name|xstart
argument_list|)
argument_list|)
expr_stmt|;
name|xstart
operator|+=
name|xinc
expr_stmt|;
block|}
block|}
block|}
end_function

begin_function
specifier|static
name|Channel
modifier|*
DECL|function|scan_convert (int gimage_ID,int num_pts,FreeSelectPoint * pts,int width,int height,int antialias)
name|scan_convert
parameter_list|(
name|int
name|gimage_ID
parameter_list|,
name|int
name|num_pts
parameter_list|,
name|FreeSelectPoint
modifier|*
name|pts
parameter_list|,
name|int
name|width
parameter_list|,
name|int
name|height
parameter_list|,
name|int
name|antialias
parameter_list|)
block|{
name|PixelRegion
name|maskPR
decl_stmt|;
name|Channel
modifier|*
name|mask
decl_stmt|;
name|link_ptr
modifier|*
name|scanlines
decl_stmt|;
name|link_ptr
name|list
decl_stmt|;
name|unsigned
name|char
modifier|*
name|buf
decl_stmt|,
modifier|*
name|b
decl_stmt|;
name|int
modifier|*
name|vals
decl_stmt|,
name|val
decl_stmt|;
name|int
name|start
decl_stmt|,
name|end
decl_stmt|;
name|int
name|x
decl_stmt|,
name|x2
decl_stmt|,
name|w
decl_stmt|;
name|int
name|i
decl_stmt|,
name|j
decl_stmt|;
name|buf
operator|=
name|NULL
expr_stmt|;
name|vals
operator|=
name|NULL
expr_stmt|;
if|if
condition|(
name|num_pts
operator|<
literal|3
condition|)
return|return
name|NULL
return|;
name|mask
operator|=
name|channel_new_mask
argument_list|(
name|gimage_ID
argument_list|,
name|width
argument_list|,
name|height
argument_list|)
expr_stmt|;
if|if
condition|(
name|antialias
condition|)
block|{
name|buf
operator|=
operator|(
name|unsigned
name|char
operator|*
operator|)
name|g_malloc
argument_list|(
name|width
argument_list|)
expr_stmt|;
name|width
operator|*=
name|SUPERSAMPLE
expr_stmt|;
name|height
operator|*=
name|SUPERSAMPLE
expr_stmt|;
comment|/* allocate value array  */
name|vals
operator|=
operator|(
name|int
operator|*
operator|)
name|g_malloc
argument_list|(
sizeof|sizeof
argument_list|(
name|int
argument_list|)
operator|*
name|width
argument_list|)
expr_stmt|;
block|}
name|scanlines
operator|=
operator|(
name|link_ptr
operator|*
operator|)
name|g_malloc
argument_list|(
sizeof|sizeof
argument_list|(
name|link_ptr
argument_list|)
operator|*
name|height
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
name|height
condition|;
name|i
operator|++
control|)
name|scanlines
index|[
name|i
index|]
operator|=
name|NULL
expr_stmt|;
for|for
control|(
name|i
operator|=
literal|0
init|;
name|i
operator|<
operator|(
name|num_pts
operator|-
literal|1
operator|)
condition|;
name|i
operator|++
control|)
block|{
if|if
condition|(
name|antialias
condition|)
name|convert_segment
argument_list|(
name|scanlines
argument_list|,
name|width
argument_list|,
name|height
argument_list|,
operator|(
name|int
operator|)
name|pts
index|[
name|i
index|]
operator|.
name|x
operator|*
name|SUPERSAMPLE
argument_list|,
operator|(
name|int
operator|)
name|pts
index|[
name|i
index|]
operator|.
name|y
operator|*
name|SUPERSAMPLE
argument_list|,
operator|(
name|int
operator|)
name|pts
index|[
name|i
operator|+
literal|1
index|]
operator|.
name|x
operator|*
name|SUPERSAMPLE
argument_list|,
operator|(
name|int
operator|)
name|pts
index|[
name|i
operator|+
literal|1
index|]
operator|.
name|y
operator|*
name|SUPERSAMPLE
argument_list|)
expr_stmt|;
else|else
name|convert_segment
argument_list|(
name|scanlines
argument_list|,
name|width
argument_list|,
name|height
argument_list|,
operator|(
name|int
operator|)
name|pts
index|[
name|i
index|]
operator|.
name|x
argument_list|,
operator|(
name|int
operator|)
name|pts
index|[
name|i
index|]
operator|.
name|y
argument_list|,
operator|(
name|int
operator|)
name|pts
index|[
name|i
operator|+
literal|1
index|]
operator|.
name|x
argument_list|,
operator|(
name|int
operator|)
name|pts
index|[
name|i
operator|+
literal|1
index|]
operator|.
name|y
argument_list|)
expr_stmt|;
block|}
comment|/*  check for a connecting Point  */
if|if
condition|(
name|pts
index|[
name|num_pts
operator|-
literal|1
index|]
operator|.
name|x
operator|!=
name|pts
index|[
literal|0
index|]
operator|.
name|x
operator|||
name|pts
index|[
name|num_pts
operator|-
literal|1
index|]
operator|.
name|y
operator|!=
name|pts
index|[
literal|0
index|]
operator|.
name|y
condition|)
block|{
if|if
condition|(
name|antialias
condition|)
name|convert_segment
argument_list|(
name|scanlines
argument_list|,
name|width
argument_list|,
name|height
argument_list|,
operator|(
name|int
operator|)
name|pts
index|[
name|num_pts
operator|-
literal|1
index|]
operator|.
name|x
operator|*
name|SUPERSAMPLE
argument_list|,
operator|(
name|int
operator|)
name|pts
index|[
name|num_pts
operator|-
literal|1
index|]
operator|.
name|y
operator|*
name|SUPERSAMPLE
argument_list|,
operator|(
name|int
operator|)
name|pts
index|[
literal|0
index|]
operator|.
name|x
operator|*
name|SUPERSAMPLE
argument_list|,
operator|(
name|int
operator|)
name|pts
index|[
literal|0
index|]
operator|.
name|y
operator|*
name|SUPERSAMPLE
argument_list|)
expr_stmt|;
else|else
name|convert_segment
argument_list|(
name|scanlines
argument_list|,
name|width
argument_list|,
name|height
argument_list|,
operator|(
name|int
operator|)
name|pts
index|[
name|num_pts
operator|-
literal|1
index|]
operator|.
name|x
argument_list|,
operator|(
name|int
operator|)
name|pts
index|[
name|num_pts
operator|-
literal|1
index|]
operator|.
name|y
argument_list|,
operator|(
name|int
operator|)
name|pts
index|[
literal|0
index|]
operator|.
name|x
argument_list|,
operator|(
name|int
operator|)
name|pts
index|[
literal|0
index|]
operator|.
name|y
argument_list|)
expr_stmt|;
block|}
name|pixel_region_init
argument_list|(
operator|&
name|maskPR
argument_list|,
name|drawable_data
argument_list|(
name|GIMP_DRAWABLE
argument_list|(
name|mask
argument_list|)
argument_list|)
argument_list|,
literal|0
argument_list|,
literal|0
argument_list|,
name|drawable_width
argument_list|(
name|GIMP_DRAWABLE
argument_list|(
name|mask
argument_list|)
argument_list|)
argument_list|,
name|drawable_height
argument_list|(
name|GIMP_DRAWABLE
argument_list|(
name|mask
argument_list|)
argument_list|)
argument_list|,
name|TRUE
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
name|height
condition|;
name|i
operator|++
control|)
block|{
name|list
operator|=
name|scanlines
index|[
name|i
index|]
expr_stmt|;
comment|/*  zero the vals array  */
if|if
condition|(
name|antialias
operator|&&
operator|!
operator|(
name|i
operator|%
name|SUPERSAMPLE
operator|)
condition|)
name|memset
argument_list|(
name|vals
argument_list|,
literal|0
argument_list|,
name|width
operator|*
sizeof|sizeof
argument_list|(
name|int
argument_list|)
argument_list|)
expr_stmt|;
while|while
condition|(
name|list
condition|)
block|{
name|x
operator|=
operator|(
name|long
operator|)
name|list
operator|->
name|data
expr_stmt|;
name|list
operator|=
name|next_item
argument_list|(
name|list
argument_list|)
expr_stmt|;
if|if
condition|(
operator|!
name|list
condition|)
name|warning
argument_list|(
literal|"Cannot properly scanline convert polygon!\n"
argument_list|)
expr_stmt|;
else|else
block|{
comment|/*  bounds checking  */
name|x
operator|=
name|BOUNDS
argument_list|(
name|x
argument_list|,
literal|0
argument_list|,
name|width
argument_list|)
expr_stmt|;
name|x2
operator|=
name|BOUNDS
argument_list|(
operator|(
name|long
operator|)
name|list
operator|->
name|data
argument_list|,
literal|0
argument_list|,
name|width
argument_list|)
expr_stmt|;
name|w
operator|=
name|x2
operator|-
name|x
expr_stmt|;
if|if
condition|(
name|w
operator|>
literal|0
condition|)
block|{
if|if
condition|(
operator|!
name|antialias
condition|)
name|channel_add_segment
argument_list|(
name|mask
argument_list|,
name|x
argument_list|,
name|i
argument_list|,
name|w
argument_list|,
literal|255
argument_list|)
expr_stmt|;
else|else
for|for
control|(
name|j
operator|=
literal|0
init|;
name|j
operator|<
name|w
condition|;
name|j
operator|++
control|)
name|vals
index|[
name|j
operator|+
name|x
index|]
operator|+=
literal|255
expr_stmt|;
block|}
name|list
operator|=
name|next_item
argument_list|(
name|list
argument_list|)
expr_stmt|;
block|}
block|}
if|if
condition|(
name|antialias
operator|&&
operator|!
operator|(
operator|(
name|i
operator|+
literal|1
operator|)
operator|%
name|SUPERSAMPLE
operator|)
condition|)
block|{
name|b
operator|=
name|buf
expr_stmt|;
name|start
operator|=
literal|0
expr_stmt|;
name|end
operator|=
name|width
expr_stmt|;
for|for
control|(
name|j
operator|=
name|start
init|;
name|j
operator|<
name|end
condition|;
name|j
operator|+=
name|SUPERSAMPLE
control|)
block|{
name|val
operator|=
literal|0
expr_stmt|;
for|for
control|(
name|x
operator|=
literal|0
init|;
name|x
operator|<
name|SUPERSAMPLE
condition|;
name|x
operator|++
control|)
name|val
operator|+=
name|vals
index|[
name|j
operator|+
name|x
index|]
expr_stmt|;
operator|*
name|b
operator|++
operator|=
call|(
name|unsigned
name|char
call|)
argument_list|(
name|val
operator|/
name|SUPERSAMPLE2
argument_list|)
expr_stmt|;
block|}
name|pixel_region_set_row
argument_list|(
operator|&
name|maskPR
argument_list|,
literal|0
argument_list|,
operator|(
name|i
operator|/
name|SUPERSAMPLE
operator|)
argument_list|,
name|drawable_width
argument_list|(
name|GIMP_DRAWABLE
argument_list|(
name|mask
argument_list|)
argument_list|)
argument_list|,
name|buf
argument_list|)
expr_stmt|;
block|}
name|free_list
argument_list|(
name|scanlines
index|[
name|i
index|]
argument_list|)
expr_stmt|;
block|}
if|if
condition|(
name|antialias
condition|)
block|{
name|g_free
argument_list|(
name|vals
argument_list|)
expr_stmt|;
name|g_free
argument_list|(
name|buf
argument_list|)
expr_stmt|;
block|}
name|g_free
argument_list|(
name|scanlines
argument_list|)
expr_stmt|;
return|return
name|mask
return|;
block|}
end_function

begin_comment
comment|/*************************************/
end_comment

begin_comment
comment|/*  Polygonal selection apparatus  */
end_comment

begin_function
specifier|static
name|void
DECL|function|free_select (GImage * gimage,int num_pts,FreeSelectPoint * pts,int op,int antialias,int feather,double feather_radius)
name|free_select
parameter_list|(
name|GImage
modifier|*
name|gimage
parameter_list|,
name|int
name|num_pts
parameter_list|,
name|FreeSelectPoint
modifier|*
name|pts
parameter_list|,
name|int
name|op
parameter_list|,
name|int
name|antialias
parameter_list|,
name|int
name|feather
parameter_list|,
name|double
name|feather_radius
parameter_list|)
block|{
name|Channel
modifier|*
name|mask
decl_stmt|;
comment|/*  if applicable, replace the current selection  */
comment|/*  or insure that a floating selection is anchored down...  */
if|if
condition|(
name|op
operator|==
name|REPLACE
condition|)
name|gimage_mask_clear
argument_list|(
name|gimage
argument_list|)
expr_stmt|;
else|else
name|gimage_mask_undo
argument_list|(
name|gimage
argument_list|)
expr_stmt|;
name|mask
operator|=
name|scan_convert
argument_list|(
name|gimage
operator|->
name|ID
argument_list|,
name|num_pts
argument_list|,
name|pts
argument_list|,
name|gimage
operator|->
name|width
argument_list|,
name|gimage
operator|->
name|height
argument_list|,
name|antialias
argument_list|)
expr_stmt|;
if|if
condition|(
name|mask
condition|)
block|{
if|if
condition|(
name|feather
condition|)
name|channel_feather
argument_list|(
name|mask
argument_list|,
name|gimage_get_mask
argument_list|(
name|gimage
argument_list|)
argument_list|,
name|feather_radius
argument_list|,
name|op
argument_list|,
literal|0
argument_list|,
literal|0
argument_list|)
expr_stmt|;
else|else
name|channel_combine_mask
argument_list|(
name|gimage_get_mask
argument_list|(
name|gimage
argument_list|)
argument_list|,
name|mask
argument_list|,
name|op
argument_list|,
literal|0
argument_list|,
literal|0
argument_list|)
expr_stmt|;
name|channel_delete
argument_list|(
name|mask
argument_list|)
expr_stmt|;
block|}
block|}
end_function

begin_function
name|void
DECL|function|free_select_button_press (Tool * tool,GdkEventButton * bevent,gpointer gdisp_ptr)
name|free_select_button_press
parameter_list|(
name|Tool
modifier|*
name|tool
parameter_list|,
name|GdkEventButton
modifier|*
name|bevent
parameter_list|,
name|gpointer
name|gdisp_ptr
parameter_list|)
block|{
name|GDisplay
modifier|*
name|gdisp
decl_stmt|;
name|FreeSelect
modifier|*
name|free_sel
decl_stmt|;
name|gdisp
operator|=
operator|(
name|GDisplay
operator|*
operator|)
name|gdisp_ptr
expr_stmt|;
name|free_sel
operator|=
operator|(
name|FreeSelect
operator|*
operator|)
name|tool
operator|->
name|private
expr_stmt|;
name|gdk_pointer_grab
argument_list|(
name|gdisp
operator|->
name|canvas
operator|->
name|window
argument_list|,
name|FALSE
argument_list|,
name|GDK_POINTER_MOTION_HINT_MASK
operator||
name|GDK_BUTTON1_MOTION_MASK
operator||
name|GDK_BUTTON_RELEASE_MASK
argument_list|,
name|NULL
argument_list|,
name|NULL
argument_list|,
name|bevent
operator|->
name|time
argument_list|)
expr_stmt|;
name|tool
operator|->
name|state
operator|=
name|ACTIVE
expr_stmt|;
name|tool
operator|->
name|gdisp_ptr
operator|=
name|gdisp_ptr
expr_stmt|;
if|if
condition|(
name|bevent
operator|->
name|state
operator|&
name|GDK_MOD1_MASK
condition|)
block|{
name|init_edit_selection
argument_list|(
name|tool
argument_list|,
name|gdisp_ptr
argument_list|,
name|bevent
argument_list|,
name|MaskTranslate
argument_list|)
expr_stmt|;
return|return;
block|}
elseif|else
if|if
condition|(
operator|(
name|bevent
operator|->
name|state
operator|&
name|GDK_SHIFT_MASK
operator|)
operator|&&
operator|!
operator|(
name|bevent
operator|->
name|state
operator|&
name|GDK_CONTROL_MASK
operator|)
condition|)
name|free_sel
operator|->
name|op
operator|=
name|ADD
expr_stmt|;
elseif|else
if|if
condition|(
operator|(
name|bevent
operator|->
name|state
operator|&
name|GDK_CONTROL_MASK
operator|)
operator|&&
operator|!
operator|(
name|bevent
operator|->
name|state
operator|&
name|GDK_SHIFT_MASK
operator|)
condition|)
name|free_sel
operator|->
name|op
operator|=
name|SUB
expr_stmt|;
elseif|else
if|if
condition|(
operator|(
name|bevent
operator|->
name|state
operator|&
name|GDK_CONTROL_MASK
operator|)
operator|&&
operator|(
name|bevent
operator|->
name|state
operator|&
name|GDK_SHIFT_MASK
operator|)
condition|)
name|free_sel
operator|->
name|op
operator|=
name|INTERSECT
expr_stmt|;
else|else
block|{
if|if
condition|(
operator|!
operator|(
name|layer_is_floating_sel
argument_list|(
name|gimage_get_active_layer
argument_list|(
name|gdisp
operator|->
name|gimage
argument_list|)
argument_list|)
operator|)
operator|&&
name|gdisplay_mask_value
argument_list|(
name|gdisp
argument_list|,
name|bevent
operator|->
name|x
argument_list|,
name|bevent
operator|->
name|y
argument_list|)
operator|>
name|HALF_WAY
condition|)
block|{
name|init_edit_selection
argument_list|(
name|tool
argument_list|,
name|gdisp_ptr
argument_list|,
name|bevent
argument_list|,
name|MaskToLayerTranslate
argument_list|)
expr_stmt|;
return|return;
block|}
name|free_sel
operator|->
name|op
operator|=
name|REPLACE
expr_stmt|;
block|}
name|add_point
argument_list|(
literal|0
argument_list|,
name|bevent
operator|->
name|x
argument_list|,
name|bevent
operator|->
name|y
argument_list|)
expr_stmt|;
name|free_sel
operator|->
name|num_pts
operator|=
literal|1
expr_stmt|;
name|draw_core_start
argument_list|(
name|free_sel
operator|->
name|core
argument_list|,
name|gdisp
operator|->
name|canvas
operator|->
name|window
argument_list|,
name|tool
argument_list|)
expr_stmt|;
block|}
end_function

begin_function
name|void
DECL|function|free_select_button_release (Tool * tool,GdkEventButton * bevent,gpointer gdisp_ptr)
name|free_select_button_release
parameter_list|(
name|Tool
modifier|*
name|tool
parameter_list|,
name|GdkEventButton
modifier|*
name|bevent
parameter_list|,
name|gpointer
name|gdisp_ptr
parameter_list|)
block|{
name|FreeSelect
modifier|*
name|free_sel
decl_stmt|;
name|FreeSelectPoint
modifier|*
name|pts
decl_stmt|;
name|GDisplay
modifier|*
name|gdisp
decl_stmt|;
name|int
name|i
decl_stmt|;
name|gdisp
operator|=
operator|(
name|GDisplay
operator|*
operator|)
name|gdisp_ptr
expr_stmt|;
name|free_sel
operator|=
operator|(
name|FreeSelect
operator|*
operator|)
name|tool
operator|->
name|private
expr_stmt|;
name|gdk_pointer_ungrab
argument_list|(
name|bevent
operator|->
name|time
argument_list|)
expr_stmt|;
name|gdk_flush
argument_list|()
expr_stmt|;
name|draw_core_stop
argument_list|(
name|free_sel
operator|->
name|core
argument_list|,
name|tool
argument_list|)
expr_stmt|;
name|tool
operator|->
name|state
operator|=
name|INACTIVE
expr_stmt|;
comment|/*  First take care of the case where the user "cancels" the action  */
if|if
condition|(
operator|!
operator|(
name|bevent
operator|->
name|state
operator|&
name|GDK_BUTTON3_MASK
operator|)
condition|)
block|{
name|pts
operator|=
operator|(
name|FreeSelectPoint
operator|*
operator|)
name|g_malloc
argument_list|(
sizeof|sizeof
argument_list|(
name|FreeSelectPoint
argument_list|)
operator|*
name|free_sel
operator|->
name|num_pts
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
name|free_sel
operator|->
name|num_pts
condition|;
name|i
operator|++
control|)
block|{
name|gdisplay_untransform_coords_f
argument_list|(
name|gdisp
argument_list|,
name|global_pts
index|[
name|i
index|]
operator|.
name|x
argument_list|,
name|global_pts
index|[
name|i
index|]
operator|.
name|y
argument_list|,
operator|&
name|pts
index|[
name|i
index|]
operator|.
name|x
argument_list|,
operator|&
name|pts
index|[
name|i
index|]
operator|.
name|y
argument_list|,
name|FALSE
argument_list|)
expr_stmt|;
block|}
name|free_select
argument_list|(
name|gdisp
operator|->
name|gimage
argument_list|,
name|free_sel
operator|->
name|num_pts
argument_list|,
name|pts
argument_list|,
name|free_sel
operator|->
name|op
argument_list|,
name|free_options
operator|->
name|antialias
argument_list|,
name|free_options
operator|->
name|feather
argument_list|,
name|free_options
operator|->
name|feather_radius
argument_list|)
expr_stmt|;
name|g_free
argument_list|(
name|pts
argument_list|)
expr_stmt|;
name|gdisplays_flush
argument_list|()
expr_stmt|;
block|}
block|}
end_function

begin_function
name|void
DECL|function|free_select_motion (Tool * tool,GdkEventMotion * mevent,gpointer gdisp_ptr)
name|free_select_motion
parameter_list|(
name|Tool
modifier|*
name|tool
parameter_list|,
name|GdkEventMotion
modifier|*
name|mevent
parameter_list|,
name|gpointer
name|gdisp_ptr
parameter_list|)
block|{
name|FreeSelect
modifier|*
name|free_sel
decl_stmt|;
name|GDisplay
modifier|*
name|gdisp
decl_stmt|;
if|if
condition|(
name|tool
operator|->
name|state
operator|!=
name|ACTIVE
condition|)
return|return;
name|gdisp
operator|=
operator|(
name|GDisplay
operator|*
operator|)
name|gdisp_ptr
expr_stmt|;
name|free_sel
operator|=
operator|(
name|FreeSelect
operator|*
operator|)
name|tool
operator|->
name|private
expr_stmt|;
if|if
condition|(
name|add_point
argument_list|(
name|free_sel
operator|->
name|num_pts
argument_list|,
name|mevent
operator|->
name|x
argument_list|,
name|mevent
operator|->
name|y
argument_list|)
condition|)
block|{
name|gdk_draw_line
argument_list|(
name|free_sel
operator|->
name|core
operator|->
name|win
argument_list|,
name|free_sel
operator|->
name|core
operator|->
name|gc
argument_list|,
name|global_pts
index|[
name|free_sel
operator|->
name|num_pts
operator|-
literal|1
index|]
operator|.
name|x
argument_list|,
name|global_pts
index|[
name|free_sel
operator|->
name|num_pts
operator|-
literal|1
index|]
operator|.
name|y
argument_list|,
name|global_pts
index|[
name|free_sel
operator|->
name|num_pts
index|]
operator|.
name|x
argument_list|,
name|global_pts
index|[
name|free_sel
operator|->
name|num_pts
index|]
operator|.
name|y
argument_list|)
expr_stmt|;
name|free_sel
operator|->
name|num_pts
operator|++
expr_stmt|;
block|}
block|}
end_function

begin_function
specifier|static
name|void
DECL|function|free_select_control (Tool * tool,int action,gpointer gdisp_ptr)
name|free_select_control
parameter_list|(
name|Tool
modifier|*
name|tool
parameter_list|,
name|int
name|action
parameter_list|,
name|gpointer
name|gdisp_ptr
parameter_list|)
block|{
name|FreeSelect
modifier|*
name|free_sel
decl_stmt|;
name|free_sel
operator|=
operator|(
name|FreeSelect
operator|*
operator|)
name|tool
operator|->
name|private
expr_stmt|;
switch|switch
condition|(
name|action
condition|)
block|{
case|case
name|PAUSE
case|:
name|draw_core_pause
argument_list|(
name|free_sel
operator|->
name|core
argument_list|,
name|tool
argument_list|)
expr_stmt|;
break|break;
case|case
name|RESUME
case|:
name|draw_core_resume
argument_list|(
name|free_sel
operator|->
name|core
argument_list|,
name|tool
argument_list|)
expr_stmt|;
break|break;
case|case
name|HALT
case|:
name|draw_core_stop
argument_list|(
name|free_sel
operator|->
name|core
argument_list|,
name|tool
argument_list|)
expr_stmt|;
break|break;
block|}
block|}
end_function

begin_function
name|void
DECL|function|free_select_draw (Tool * tool)
name|free_select_draw
parameter_list|(
name|Tool
modifier|*
name|tool
parameter_list|)
block|{
name|FreeSelect
modifier|*
name|free_sel
decl_stmt|;
name|int
name|i
decl_stmt|;
name|free_sel
operator|=
operator|(
name|FreeSelect
operator|*
operator|)
name|tool
operator|->
name|private
expr_stmt|;
for|for
control|(
name|i
operator|=
literal|1
init|;
name|i
operator|<
name|free_sel
operator|->
name|num_pts
condition|;
name|i
operator|++
control|)
name|gdk_draw_line
argument_list|(
name|free_sel
operator|->
name|core
operator|->
name|win
argument_list|,
name|free_sel
operator|->
name|core
operator|->
name|gc
argument_list|,
name|global_pts
index|[
name|i
operator|-
literal|1
index|]
operator|.
name|x
argument_list|,
name|global_pts
index|[
name|i
operator|-
literal|1
index|]
operator|.
name|y
argument_list|,
name|global_pts
index|[
name|i
index|]
operator|.
name|x
argument_list|,
name|global_pts
index|[
name|i
index|]
operator|.
name|y
argument_list|)
expr_stmt|;
block|}
end_function

begin_function
name|Tool
modifier|*
DECL|function|tools_new_free_select (void)
name|tools_new_free_select
parameter_list|(
name|void
parameter_list|)
block|{
name|Tool
modifier|*
name|tool
decl_stmt|;
name|FreeSelect
modifier|*
name|private
decl_stmt|;
comment|/*  The tool options  */
if|if
condition|(
operator|!
name|free_options
condition|)
name|free_options
operator|=
name|create_selection_options
argument_list|(
name|FREE_SELECT
argument_list|)
expr_stmt|;
name|tool
operator|=
operator|(
name|Tool
operator|*
operator|)
name|g_malloc
argument_list|(
sizeof|sizeof
argument_list|(
name|Tool
argument_list|)
argument_list|)
expr_stmt|;
name|private
operator|=
operator|(
name|FreeSelect
operator|*
operator|)
name|g_malloc
argument_list|(
sizeof|sizeof
argument_list|(
name|FreeSelect
argument_list|)
argument_list|)
expr_stmt|;
name|private
operator|->
name|core
operator|=
name|draw_core_new
argument_list|(
name|free_select_draw
argument_list|)
expr_stmt|;
name|private
operator|->
name|num_pts
operator|=
literal|0
expr_stmt|;
name|tool
operator|->
name|type
operator|=
name|FREE_SELECT
expr_stmt|;
name|tool
operator|->
name|state
operator|=
name|INACTIVE
expr_stmt|;
name|tool
operator|->
name|scroll_lock
operator|=
literal|1
expr_stmt|;
comment|/*  Do not allow scrolling  */
name|tool
operator|->
name|auto_snap_to
operator|=
name|TRUE
expr_stmt|;
name|tool
operator|->
name|private
operator|=
operator|(
name|void
operator|*
operator|)
name|private
expr_stmt|;
name|tool
operator|->
name|button_press_func
operator|=
name|free_select_button_press
expr_stmt|;
name|tool
operator|->
name|button_release_func
operator|=
name|free_select_button_release
expr_stmt|;
name|tool
operator|->
name|motion_func
operator|=
name|free_select_motion
expr_stmt|;
name|tool
operator|->
name|arrow_keys_func
operator|=
name|standard_arrow_keys_func
expr_stmt|;
name|tool
operator|->
name|cursor_update_func
operator|=
name|rect_select_cursor_update
expr_stmt|;
name|tool
operator|->
name|control_func
operator|=
name|free_select_control
expr_stmt|;
return|return
name|tool
return|;
block|}
end_function

begin_function
name|void
DECL|function|tools_free_free_select (Tool * tool)
name|tools_free_free_select
parameter_list|(
name|Tool
modifier|*
name|tool
parameter_list|)
block|{
name|FreeSelect
modifier|*
name|free_sel
decl_stmt|;
name|free_sel
operator|=
operator|(
name|FreeSelect
operator|*
operator|)
name|tool
operator|->
name|private
expr_stmt|;
name|draw_core_free
argument_list|(
name|free_sel
operator|->
name|core
argument_list|)
expr_stmt|;
name|g_free
argument_list|(
name|free_sel
argument_list|)
expr_stmt|;
block|}
end_function

begin_comment
comment|/*  The free_select procedure definition  */
end_comment

begin_decl_stmt
DECL|variable|free_select_args
name|ProcArg
name|free_select_args
index|[]
init|=
block|{
block|{
name|PDB_IMAGE
block|,
literal|"image"
block|,
literal|"The image"
block|}
block|,
block|{
name|PDB_INT32
block|,
literal|"num_pts"
block|,
literal|"number of points (count 1 coordinate as two points)"
block|}
block|,
block|{
name|PDB_FLOATARRAY
block|,
literal|"segs"
block|,
literal|"array of points: { p1.x, p1.y, p2.x, p2.y, ..., pn.x, pn.y}"
block|}
block|,
block|{
name|PDB_INT32
block|,
literal|"operation"
block|,
literal|"the selection operation: { ADD (0), SUB (1), REPLACE (2), INTERSECT (3) }"
block|}
block|,
block|{
name|PDB_INT32
block|,
literal|"antialias"
block|,
literal|"antialiasing option for selections"
block|}
block|,
block|{
name|PDB_INT32
block|,
literal|"feather"
block|,
literal|"feather option for selections"
block|}
block|,
block|{
name|PDB_FLOAT
block|,
literal|"feather_radius"
block|,
literal|"radius for feather operation"
block|}
block|}
decl_stmt|;
end_decl_stmt

begin_decl_stmt
DECL|variable|free_select_proc
name|ProcRecord
name|free_select_proc
init|=
block|{
literal|"gimp_free_select"
block|,
literal|"Create a polygonal selection over the specified image"
block|,
literal|"This tool creates a polygonal selection over the specified image.  The polygonal region can be either added to, subtracted from, or replace the contents of the previous selection mask.  The polygon is specified through an array of floating point numbers and its length.  The length of array must be 2n, where n is the number of points.  Each point is defined by 2 floating point values which correspond to the x and y coordinates.  If the final point does not connect to the starting point, a connecting segment is automatically added.  If the feather option is enabled, the resulting selection is blurred before combining.  The blur is a gaussian blur with the specified feather radius."
block|,
literal|"Spencer Kimball& Peter Mattis"
block|,
literal|"Spencer Kimball& Peter Mattis"
block|,
literal|"1995-1996"
block|,
name|PDB_INTERNAL
block|,
comment|/*  Input arguments  */
literal|7
block|,
name|free_select_args
block|,
comment|/*  Output arguments  */
literal|0
block|,
name|NULL
block|,
comment|/*  Exec method  */
block|{
block|{
name|free_select_invoker
block|}
block|}
block|, }
decl_stmt|;
end_decl_stmt

begin_function
specifier|static
name|Argument
modifier|*
DECL|function|free_select_invoker (Argument * args)
name|free_select_invoker
parameter_list|(
name|Argument
modifier|*
name|args
parameter_list|)
block|{
name|int
name|success
init|=
name|TRUE
decl_stmt|;
name|GImage
modifier|*
name|gimage
decl_stmt|;
name|int
name|op
decl_stmt|;
name|int
name|antialias
decl_stmt|;
name|int
name|feather
decl_stmt|;
name|int
name|num_pts
decl_stmt|;
name|FreeSelectPoint
modifier|*
name|pt_array
decl_stmt|;
name|double
name|feather_radius
decl_stmt|;
name|int
name|int_value
decl_stmt|;
name|op
operator|=
name|REPLACE
expr_stmt|;
name|num_pts
operator|=
literal|0
expr_stmt|;
comment|/*  the gimage  */
if|if
condition|(
name|success
condition|)
block|{
name|int_value
operator|=
name|args
index|[
literal|0
index|]
operator|.
name|value
operator|.
name|pdb_int
expr_stmt|;
if|if
condition|(
operator|!
operator|(
name|gimage
operator|=
name|gimage_get_ID
argument_list|(
name|int_value
argument_list|)
operator|)
condition|)
name|success
operator|=
name|FALSE
expr_stmt|;
block|}
comment|/*  num pts  */
if|if
condition|(
name|success
condition|)
block|{
name|int_value
operator|=
name|args
index|[
literal|1
index|]
operator|.
name|value
operator|.
name|pdb_int
expr_stmt|;
if|if
condition|(
name|int_value
operator|>=
literal|2
condition|)
name|num_pts
operator|=
name|int_value
operator|/
literal|2
expr_stmt|;
else|else
name|success
operator|=
name|FALSE
expr_stmt|;
block|}
comment|/*  point array  */
if|if
condition|(
name|success
condition|)
name|pt_array
operator|=
operator|(
name|FreeSelectPoint
operator|*
operator|)
name|args
index|[
literal|2
index|]
operator|.
name|value
operator|.
name|pdb_pointer
expr_stmt|;
comment|/*  operation  */
if|if
condition|(
name|success
condition|)
block|{
name|int_value
operator|=
name|args
index|[
literal|3
index|]
operator|.
name|value
operator|.
name|pdb_int
expr_stmt|;
switch|switch
condition|(
name|int_value
condition|)
block|{
case|case
literal|0
case|:
name|op
operator|=
name|ADD
expr_stmt|;
break|break;
case|case
literal|1
case|:
name|op
operator|=
name|SUB
expr_stmt|;
break|break;
case|case
literal|2
case|:
name|op
operator|=
name|REPLACE
expr_stmt|;
break|break;
case|case
literal|3
case|:
name|op
operator|=
name|INTERSECT
expr_stmt|;
break|break;
default|default:
name|success
operator|=
name|FALSE
expr_stmt|;
block|}
block|}
comment|/*  antialiasing  */
if|if
condition|(
name|success
condition|)
block|{
name|int_value
operator|=
name|args
index|[
literal|4
index|]
operator|.
name|value
operator|.
name|pdb_int
expr_stmt|;
name|antialias
operator|=
operator|(
name|int_value
operator|)
condition|?
name|TRUE
else|:
name|FALSE
expr_stmt|;
block|}
comment|/*  feathering  */
if|if
condition|(
name|success
condition|)
block|{
name|int_value
operator|=
name|args
index|[
literal|5
index|]
operator|.
name|value
operator|.
name|pdb_int
expr_stmt|;
name|feather
operator|=
operator|(
name|int_value
operator|)
condition|?
name|TRUE
else|:
name|FALSE
expr_stmt|;
block|}
comment|/*  feather radius  */
if|if
condition|(
name|success
condition|)
block|{
name|feather_radius
operator|=
name|args
index|[
literal|6
index|]
operator|.
name|value
operator|.
name|pdb_float
expr_stmt|;
block|}
comment|/*  call the free_select procedure  */
if|if
condition|(
name|success
condition|)
name|free_select
argument_list|(
name|gimage
argument_list|,
name|num_pts
argument_list|,
name|pt_array
argument_list|,
name|op
argument_list|,
name|antialias
argument_list|,
name|feather
argument_list|,
name|feather_radius
argument_list|)
expr_stmt|;
return|return
name|procedural_db_return_args
argument_list|(
operator|&
name|free_select_proc
argument_list|,
name|success
argument_list|)
return|;
block|}
end_function

end_unit

