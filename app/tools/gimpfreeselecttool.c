begin_unit|revision:0.9.5;language:C;cregit-version:0.0.1
begin_comment
comment|/* The GIMP -- an image manipulation program  * Copyright (C) 1995 Spencer Kimball and Peter Mattis  *  * This program is free software; you can redistribute it and/or modify  * it under the terms of the GNU General Public License as published by  * the Free Software Foundation; either version 2 of the License, or  * (at your option) any later version.  *  * This program is distributed in the hope that it will be useful,  * but WITHOUT ANY WARRANTY; without even the implied warranty of  * MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the  * GNU General Public License for more details.  *  * You should have received a copy of the GNU General Public License  * along with this program; if not, write to the Free Software  * Foundation, Inc., 59 Temple Place - Suite 330, Boston, MA 02111-1307, USA.  */
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
file|"rect_select.h"
end_include

begin_include
include|#
directive|include
file|"selection_options.h"
end_include

begin_include
include|#
directive|include
file|"libgimp/gimpintl.h"
end_include

begin_include
include|#
directive|include
file|"libgimp/gimpmath.h"
end_include

begin_define
DECL|macro|DEFAULT_MAX_INC
define|#
directive|define
name|DEFAULT_MAX_INC
value|1024
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

begin_comment
comment|/*  the free selection structures  */
end_comment

begin_typedef
DECL|typedef|FreeSelect
typedef|typedef
name|struct
name|_FreeSelect
name|FreeSelect
typedef|;
end_typedef

begin_struct
DECL|struct|_FreeSelect
struct|struct
name|_FreeSelect
block|{
DECL|member|core
name|DrawCore
modifier|*
name|core
decl_stmt|;
comment|/*  Core select object                      */
DECL|member|op
name|int
name|op
decl_stmt|;
comment|/*  selection operation (ADD, SUB, etc)     */
DECL|member|num_pts
name|int
name|num_pts
decl_stmt|;
comment|/*  Number of points in the polygon         */
block|}
struct|;
end_struct

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

begin_comment
comment|/*  the free selection tool options  */
end_comment

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

begin_comment
comment|/*  functions  */
end_comment

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
name|gimp_fatal_error
argument_list|(
name|_
argument_list|(
literal|"add_point(): Unable to reallocate points array in free_select."
argument_list|)
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
name|GSList
modifier|*
DECL|function|insert_into_sorted_list (GSList * list,int x)
name|insert_into_sorted_list
parameter_list|(
name|GSList
modifier|*
name|list
parameter_list|,
name|int
name|x
parameter_list|)
block|{
name|GSList
modifier|*
name|orig
init|=
name|list
decl_stmt|;
name|GSList
modifier|*
name|rest
decl_stmt|;
if|if
condition|(
operator|!
name|list
condition|)
return|return
name|g_slist_prepend
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
name|g_slist_next
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
name|g_slist_prepend
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
name|g_slist_append
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
name|g_slist_next
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
DECL|function|convert_segment (GSList ** scanlines,int width,int height,int x1,int y1,int x2,int y2)
name|convert_segment
parameter_list|(
name|GSList
modifier|*
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
DECL|function|scan_convert (GimpImage * gimage,int num_pts,FreeSelectPoint * pts,int width,int height,int antialias)
name|scan_convert
parameter_list|(
name|GimpImage
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
name|GSList
modifier|*
modifier|*
name|scanlines
decl_stmt|;
name|GSList
modifier|*
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
name|gimage
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
name|GSList
operator|*
operator|*
operator|)
name|g_malloc
argument_list|(
sizeof|sizeof
argument_list|(
name|GSList
operator|*
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
name|g_slist_next
argument_list|(
name|list
argument_list|)
expr_stmt|;
if|if
condition|(
operator|!
name|list
condition|)
name|g_message
argument_list|(
name|_
argument_list|(
literal|"Cannot properly scanline convert polygon!\n"
argument_list|)
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
name|g_slist_next
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
name|g_slist_free
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
comment|/*  Polygonal selection apparatus    */
end_comment

begin_function
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
switch|switch
condition|(
name|free_sel
operator|->
name|op
condition|)
block|{
case|case
name|SELECTION_MOVE_MASK
case|:
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
case|case
name|SELECTION_MOVE
case|:
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
DECL|function|free_select_control (Tool * tool,ToolAction action,gpointer gdisp_ptr)
name|free_select_control
parameter_list|(
name|Tool
modifier|*
name|tool
parameter_list|,
name|ToolAction
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
default|default:
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
specifier|static
name|void
DECL|function|free_select_options_reset ()
name|free_select_options_reset
parameter_list|()
block|{
name|selection_options_reset
argument_list|(
name|free_options
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
block|{
name|free_options
operator|=
name|selection_options_new
argument_list|(
name|FREE_SELECT
argument_list|,
name|free_select_options_reset
argument_list|)
expr_stmt|;
name|tools_register
argument_list|(
name|FREE_SELECT
argument_list|,
operator|(
name|ToolOptions
operator|*
operator|)
name|free_options
argument_list|)
expr_stmt|;
block|}
name|tool
operator|=
name|tools_new_tool
argument_list|(
name|FREE_SELECT
argument_list|)
expr_stmt|;
name|private
operator|=
name|g_new
argument_list|(
name|FreeSelect
argument_list|,
literal|1
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
name|private
operator|->
name|op
operator|=
name|SELECTION_REPLACE
expr_stmt|;
name|tool
operator|->
name|scroll_lock
operator|=
name|TRUE
expr_stmt|;
comment|/*  Do not allow scrolling  */
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

end_unit

