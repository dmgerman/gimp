begin_unit|revision:0.9.5;language:C;cregit-version:0.0.1
begin_comment
comment|/* pxl-outline.c: find the edges of the bitmap image; we call each such  *   edge an ``outline''; each outline is made up of one or more pixels;  *   and each pixel participates via one or more edges.  *  * Copyright (C) 1992 Free Software Foundation, Inc.  *  * This program is free software; you can redistribute it and/or modify  * it under the terms of the GNU General Public License as published by  * the Free Software Foundation; either version 2, or (at your option)  * any later version.  *  * This program is distributed in the hope that it will be useful,  * but WITHOUT ANY WARRANTY; without even the implied warranty of  * MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the  * GNU General Public License for more details.  *  * You should have received a copy of the GNU General Public License  * along with this program; if not, write to the Free Software  * Foundation, Inc., 59 Temple Place - Suite 330, Boston, MA 02111-1307, USA.  */
end_comment

begin_include
include|#
directive|include
file|"config.h"
end_include

begin_include
include|#
directive|include
file|<stdlib.h>
end_include

begin_include
include|#
directive|include
file|"global.h"
end_include

begin_include
include|#
directive|include
file|"selection-to-path.h"
end_include

begin_include
include|#
directive|include
file|"bitmap.h"
end_include

begin_include
include|#
directive|include
file|"edge.h"
end_include

begin_include
include|#
directive|include
file|"pxl-outline.h"
end_include

begin_include
include|#
directive|include
file|"libgimp/stdplugins-intl.h"
end_include

begin_function_decl
specifier|static
name|pixel_outline_type
name|find_one_outline
parameter_list|(
name|edge_type
parameter_list|,
name|unsigned
parameter_list|,
name|unsigned
parameter_list|,
name|bitmap_type
modifier|*
parameter_list|)
function_decl|;
end_function_decl

begin_function_decl
specifier|static
name|void
name|append_pixel_outline
parameter_list|(
name|pixel_outline_list_type
modifier|*
parameter_list|,
name|pixel_outline_type
parameter_list|)
function_decl|;
end_function_decl

begin_function_decl
specifier|static
name|pixel_outline_type
name|new_pixel_outline
parameter_list|(
name|void
parameter_list|)
function_decl|;
end_function_decl

begin_function_decl
specifier|static
name|void
name|append_outline_pixel
parameter_list|(
name|pixel_outline_type
modifier|*
parameter_list|,
name|coordinate_type
parameter_list|)
function_decl|;
end_function_decl

begin_function_decl
specifier|static
name|void
name|append_coordinate
parameter_list|(
name|pixel_outline_type
modifier|*
parameter_list|,
name|int
parameter_list|,
name|int
parameter_list|,
name|edge_type
parameter_list|)
function_decl|;
end_function_decl

begin_function
specifier|static
name|bitmap_type
DECL|function|local_new_bitmap (unsigned width,unsigned height)
name|local_new_bitmap
parameter_list|(
name|unsigned
name|width
parameter_list|,
name|unsigned
name|height
parameter_list|)
block|{
name|bitmap_type
name|answer
decl_stmt|;
name|unsigned
name|size
init|=
name|width
operator|*
name|height
decl_stmt|;
name|BITMAP_HEIGHT
argument_list|(
name|answer
argument_list|)
operator|=
name|height
expr_stmt|;
name|BITMAP_WIDTH
argument_list|(
name|answer
argument_list|)
operator|=
name|width
expr_stmt|;
name|BITMAP_BITS
argument_list|(
name|answer
argument_list|)
operator|=
name|g_new0
argument_list|(
name|one_byte
argument_list|,
name|size
argument_list|)
expr_stmt|;
comment|/* g_new returns NULL if size == 0 */
comment|/*   printf("local_new_bitmap size = %d @[%p]\n",size,BITMAP_BITS (answer)); */
return|return
name|answer
return|;
block|}
end_function

begin_function
specifier|static
name|void
DECL|function|local_free_bitmap (bitmap_type * b)
name|local_free_bitmap
parameter_list|(
name|bitmap_type
modifier|*
name|b
parameter_list|)
block|{
if|if
condition|(
name|BITMAP_BITS
argument_list|(
operator|*
name|b
argument_list|)
operator|!=
name|NULL
condition|)
name|safe_free
argument_list|(
operator|(
name|address
operator|*
operator|)
operator|&
name|BITMAP_BITS
argument_list|(
operator|*
name|b
argument_list|)
argument_list|)
expr_stmt|;
block|}
end_function

begin_comment
comment|/* A character is made up of a list of one or more outlines.  Here, we    go through a character's bitmap top to bottom, left to right, looking    for the next pixel with an unmarked edge also on the character's outline.    Each one of these we find is the starting place for one outline.  We    find these outlines and put them in a list to return.  */
end_comment

begin_function
name|pixel_outline_list_type
DECL|function|find_outline_pixels (void)
name|find_outline_pixels
parameter_list|(
name|void
parameter_list|)
block|{
name|pixel_outline_list_type
name|outline_list
decl_stmt|;
name|unsigned
name|row
decl_stmt|,
name|col
decl_stmt|;
name|gint
name|height
decl_stmt|;
name|gint
name|width
decl_stmt|;
name|bitmap_type
name|marked
init|=
name|local_new_bitmap
argument_list|(
name|sel_get_width
argument_list|()
argument_list|,
name|sel_get_height
argument_list|()
argument_list|)
decl_stmt|;
comment|/*   printf("width = %d, height = %d\n",BITMAP_WIDTH(marked),BITMAP_HEIGHT(marked)); */
name|gimp_progress_init
argument_list|(
name|_
argument_list|(
literal|"Selection to Path"
argument_list|)
argument_list|)
expr_stmt|;
name|O_LIST_LENGTH
argument_list|(
name|outline_list
argument_list|)
operator|=
literal|0
expr_stmt|;
name|outline_list
operator|.
name|data
operator|=
name|NULL
expr_stmt|;
name|height
operator|=
name|sel_get_height
argument_list|()
expr_stmt|;
name|width
operator|=
name|sel_get_width
argument_list|()
expr_stmt|;
for|for
control|(
name|row
operator|=
literal|0
init|;
name|row
operator|<
name|height
condition|;
name|row
operator|++
control|)
block|{
for|for
control|(
name|col
operator|=
literal|0
init|;
name|col
operator|<
name|width
condition|;
name|col
operator|++
control|)
block|{
name|edge_type
name|edge
decl_stmt|;
if|if
condition|(
name|sel_pixel_is_white
argument_list|(
name|row
argument_list|,
name|col
argument_list|)
condition|)
continue|continue;
name|edge
operator|=
name|next_unmarked_outline_edge
argument_list|(
name|row
argument_list|,
name|col
argument_list|,
name|START_EDGE
argument_list|,
name|marked
argument_list|)
expr_stmt|;
if|if
condition|(
name|edge
operator|!=
name|no_edge
condition|)
block|{
name|pixel_outline_type
name|outline
decl_stmt|;
name|boolean
name|clockwise
init|=
name|edge
operator|==
name|bottom
decl_stmt|;
name|outline
operator|=
name|find_one_outline
argument_list|(
name|edge
argument_list|,
name|row
argument_list|,
name|col
argument_list|,
operator|&
name|marked
argument_list|)
expr_stmt|;
comment|/* Outside outlines will start at a top edge, and move                counterclockwise, and inside outlines will start at a                bottom edge, and move clockwise.  This happens because of                the order in which we look at the edges.  */
name|O_CLOCKWISE
argument_list|(
name|outline
argument_list|)
operator|=
name|clockwise
expr_stmt|;
name|append_pixel_outline
argument_list|(
operator|&
name|outline_list
argument_list|,
name|outline
argument_list|)
expr_stmt|;
block|}
block|}
if|if
condition|(
operator|(
name|row
operator|&
literal|0xf
operator|)
operator|==
literal|0
condition|)
name|gimp_progress_update
argument_list|(
operator|(
operator|(
name|gdouble
operator|)
name|row
operator|)
operator|/
name|height
argument_list|)
expr_stmt|;
block|}
name|local_free_bitmap
argument_list|(
operator|&
name|marked
argument_list|)
expr_stmt|;
return|return
name|outline_list
return|;
block|}
end_function

begin_comment
comment|/* Here we find one of a character C's outlines.  We're passed the    position (ORIGINAL_ROW and ORIGINAL_COL) of a starting pixel and one    of its unmarked edges, ORIGINAL_EDGE.  We traverse the adjacent edges    of the outline pixels, appending to the coordinate list.  We keep    track of the marked edges in MARKED, so it should be initialized to    zeros when we first get it.  */
end_comment

begin_function
specifier|static
name|pixel_outline_type
DECL|function|find_one_outline (edge_type original_edge,unsigned original_row,unsigned original_col,bitmap_type * marked)
name|find_one_outline
parameter_list|(
name|edge_type
name|original_edge
parameter_list|,
name|unsigned
name|original_row
parameter_list|,
name|unsigned
name|original_col
parameter_list|,
name|bitmap_type
modifier|*
name|marked
parameter_list|)
block|{
name|pixel_outline_type
name|outline
init|=
name|new_pixel_outline
argument_list|()
decl_stmt|;
name|unsigned
name|row
init|=
name|original_row
decl_stmt|,
name|col
init|=
name|original_col
decl_stmt|;
name|edge_type
name|edge
init|=
name|original_edge
decl_stmt|;
do|do
block|{
comment|/* Put this edge on to the output list, changing to Cartesian, and          taking account of the side bearings.  */
name|append_coordinate
argument_list|(
operator|&
name|outline
argument_list|,
name|col
argument_list|,
name|sel_get_height
argument_list|()
operator|-
name|row
argument_list|,
name|edge
argument_list|)
expr_stmt|;
name|mark_edge
argument_list|(
name|edge
argument_list|,
name|row
argument_list|,
name|col
argument_list|,
name|marked
argument_list|)
expr_stmt|;
name|next_outline_edge
argument_list|(
operator|&
name|edge
argument_list|,
operator|&
name|row
argument_list|,
operator|&
name|col
argument_list|)
expr_stmt|;
block|}
do|while
condition|(
name|row
operator|!=
name|original_row
operator|||
name|col
operator|!=
name|original_col
operator|||
name|edge
operator|!=
name|original_edge
condition|)
do|;
return|return
name|outline
return|;
block|}
end_function

begin_comment
comment|/* Append an outline to an outline list.  This is called when we have    completed an entire pixel outline.  */
end_comment

begin_function
specifier|static
name|void
DECL|function|append_pixel_outline (pixel_outline_list_type * outline_list,pixel_outline_type outline)
name|append_pixel_outline
parameter_list|(
name|pixel_outline_list_type
modifier|*
name|outline_list
parameter_list|,
name|pixel_outline_type
name|outline
parameter_list|)
block|{
name|O_LIST_LENGTH
argument_list|(
operator|*
name|outline_list
argument_list|)
operator|++
expr_stmt|;
name|outline_list
operator|->
name|data
operator|=
operator|(
name|pixel_outline_type
operator|*
operator|)
name|g_realloc
argument_list|(
name|outline_list
operator|->
name|data
argument_list|,
name|outline_list
operator|->
name|length
operator|*
sizeof|sizeof
argument_list|(
name|pixel_outline_type
argument_list|)
argument_list|)
expr_stmt|;
name|O_LIST_OUTLINE
argument_list|(
operator|*
name|outline_list
argument_list|,
name|O_LIST_LENGTH
argument_list|(
operator|*
name|outline_list
argument_list|)
operator|-
literal|1
argument_list|)
operator|=
name|outline
expr_stmt|;
block|}
end_function

begin_comment
comment|/* Here is a routine that frees a list of such lists.  */
end_comment

begin_function
name|void
DECL|function|free_pixel_outline_list (pixel_outline_list_type * outline_list)
name|free_pixel_outline_list
parameter_list|(
name|pixel_outline_list_type
modifier|*
name|outline_list
parameter_list|)
block|{
name|unsigned
name|this_outline
decl_stmt|;
for|for
control|(
name|this_outline
operator|=
literal|0
init|;
name|this_outline
operator|<
name|outline_list
operator|->
name|length
condition|;
name|this_outline
operator|++
control|)
block|{
name|pixel_outline_type
name|o
init|=
name|outline_list
operator|->
name|data
index|[
name|this_outline
index|]
decl_stmt|;
name|safe_free
argument_list|(
operator|(
name|address
operator|*
operator|)
operator|&
operator|(
name|o
operator|.
name|data
operator|)
argument_list|)
expr_stmt|;
block|}
if|if
condition|(
name|outline_list
operator|->
name|data
operator|!=
name|NULL
condition|)
name|safe_free
argument_list|(
operator|(
name|address
operator|*
operator|)
operator|&
operator|(
name|outline_list
operator|->
name|data
operator|)
argument_list|)
expr_stmt|;
block|}
end_function

begin_comment
comment|/* Return an empty list of pixels.  */
end_comment

begin_function
specifier|static
name|pixel_outline_type
DECL|function|new_pixel_outline (void)
name|new_pixel_outline
parameter_list|(
name|void
parameter_list|)
block|{
name|pixel_outline_type
name|pixel_outline
decl_stmt|;
name|O_LENGTH
argument_list|(
name|pixel_outline
argument_list|)
operator|=
literal|0
expr_stmt|;
name|pixel_outline
operator|.
name|data
operator|=
name|NULL
expr_stmt|;
return|return
name|pixel_outline
return|;
block|}
end_function

begin_comment
comment|/* Add the coordinate C to the pixel list O.  */
end_comment

begin_function
specifier|static
name|void
DECL|function|append_outline_pixel (pixel_outline_type * o,coordinate_type c)
name|append_outline_pixel
parameter_list|(
name|pixel_outline_type
modifier|*
name|o
parameter_list|,
name|coordinate_type
name|c
parameter_list|)
block|{
name|O_LENGTH
argument_list|(
operator|*
name|o
argument_list|)
operator|++
expr_stmt|;
name|o
operator|->
name|data
operator|=
operator|(
name|coordinate_type
operator|*
operator|)
name|g_realloc
argument_list|(
name|o
operator|->
name|data
argument_list|,
name|O_LENGTH
argument_list|(
operator|*
name|o
argument_list|)
operator|*
sizeof|sizeof
argument_list|(
name|coordinate_type
argument_list|)
argument_list|)
expr_stmt|;
name|O_COORDINATE
argument_list|(
operator|*
name|o
argument_list|,
name|O_LENGTH
argument_list|(
operator|*
name|o
argument_list|)
operator|-
literal|1
argument_list|)
operator|=
name|c
expr_stmt|;
block|}
end_function

begin_comment
comment|/* We are given an (X,Y) in Cartesian coordinates, and the edge of the pixel    we're on.  We append a corner of that pixel as our coordinate.    If we're on a top edge, we use the upper-left hand corner; right edge    => upper right; bottom edge => lower right; left edge => lower left.  */
end_comment

begin_function
specifier|static
name|void
DECL|function|append_coordinate (pixel_outline_type * o,int x,int y,edge_type edge)
name|append_coordinate
parameter_list|(
name|pixel_outline_type
modifier|*
name|o
parameter_list|,
name|int
name|x
parameter_list|,
name|int
name|y
parameter_list|,
name|edge_type
name|edge
parameter_list|)
block|{
name|coordinate_type
name|c
decl_stmt|;
name|char
modifier|*
name|str
decl_stmt|;
name|c
operator|.
name|x
operator|=
name|x
expr_stmt|;
name|c
operator|.
name|y
operator|=
name|y
expr_stmt|;
switch|switch
condition|(
name|edge
condition|)
block|{
case|case
name|top
case|:
name|c
operator|.
name|y
operator|++
expr_stmt|;
name|str
operator|=
literal|"top"
expr_stmt|;
break|break;
case|case
name|right
case|:
name|c
operator|.
name|x
operator|++
expr_stmt|;
name|c
operator|.
name|y
operator|++
expr_stmt|;
name|str
operator|=
literal|"right"
expr_stmt|;
break|break;
case|case
name|bottom
case|:
name|c
operator|.
name|x
operator|++
expr_stmt|;
name|str
operator|=
literal|"bottom"
expr_stmt|;
break|break;
case|case
name|left
case|:
name|str
operator|=
literal|"left"
expr_stmt|;
break|break;
default|default:
name|printf
argument_list|(
literal|"append_coordinate: Bad edge (%d)"
argument_list|,
name|edge
argument_list|)
expr_stmt|;
block|}
name|append_outline_pixel
argument_list|(
name|o
argument_list|,
name|c
argument_list|)
expr_stmt|;
block|}
end_function

end_unit

