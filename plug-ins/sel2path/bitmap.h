begin_unit|revision:0.9.5;language:C;cregit-version:0.0.1
begin_comment
comment|/* bitmap.h: definition for a bitmap type.  No packing is done by    default; each pixel is represented by an entire byte.  Among other    things, this means the type can be used for both grayscale and binary    images.  Copyright (C) 1992 Free Software Foundation, Inc.  This program is free software; you can redistribute it and/or modify it under the terms of the GNU General Public License as published by the Free Software Foundation; either version 2, or (at your option) any later version.  This program is distributed in the hope that it will be useful, but WITHOUT ANY WARRANTY; without even the implied warranty of MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the GNU General Public License for more details.  You should have received a copy of the GNU General Public License along with this program; if not, write to the Free Software Foundation, Inc., 675 Mass Ave, Cambridge, MA 02139, USA.  */
end_comment

begin_ifndef
ifndef|#
directive|ifndef
name|BITMAP_H
end_ifndef

begin_define
DECL|macro|BITMAP_H
define|#
directive|define
name|BITMAP_H
end_define

begin_include
include|#
directive|include
file|<stdio.h>
end_include

begin_include
include|#
directive|include
file|"bounding-box.h"
end_include

begin_include
include|#
directive|include
file|"types.h"
end_include

begin_comment
comment|/* If the bitmap holds 8-bit values, rather than one-bit, the    definition of BLACK here is wrong.  So don't use it in that case!  */
end_comment

begin_define
DECL|macro|WHITE
define|#
directive|define
name|WHITE
value|0
end_define

begin_define
DECL|macro|BLACK
define|#
directive|define
name|BLACK
value|1
end_define

begin_comment
comment|/* The basic structure and macros to access it.  */
end_comment

begin_typedef
typedef|typedef
struct|struct
DECL|struct|__anon28890b7b0108
block|{
DECL|member|dimensions
name|dimensions_type
name|dimensions
decl_stmt|;
DECL|member|bitmap
name|one_byte
modifier|*
name|bitmap
decl_stmt|;
DECL|typedef|bitmap_type
block|}
name|bitmap_type
typedef|;
end_typedef

begin_comment
comment|/* The dimensions of the bitmap, in pixels.  */
end_comment

begin_define
DECL|macro|BITMAP_DIMENSIONS (b)
define|#
directive|define
name|BITMAP_DIMENSIONS
parameter_list|(
name|b
parameter_list|)
value|((b).dimensions)
end_define

begin_comment
comment|/* The pixels, represented as an array of bytes (in contiguous storage).    Each pixel is a single byte, even for binary fonts.  */
end_comment

begin_define
DECL|macro|BITMAP_BITS (b)
define|#
directive|define
name|BITMAP_BITS
parameter_list|(
name|b
parameter_list|)
value|((b).bitmap)
end_define

begin_comment
comment|/* These are convenient abbreviations for geting inside the members.  */
end_comment

begin_define
DECL|macro|BITMAP_WIDTH (b)
define|#
directive|define
name|BITMAP_WIDTH
parameter_list|(
name|b
parameter_list|)
value|DIMENSIONS_WIDTH (BITMAP_DIMENSIONS (b))
end_define

begin_define
DECL|macro|BITMAP_HEIGHT (b)
define|#
directive|define
name|BITMAP_HEIGHT
parameter_list|(
name|b
parameter_list|)
value|DIMENSIONS_HEIGHT (BITMAP_DIMENSIONS (b))
end_define

begin_comment
comment|/* This is the address of the first pixel in the row ROW.  */
end_comment

begin_define
DECL|macro|BITMAP_ROW (b,row)
define|#
directive|define
name|BITMAP_ROW
parameter_list|(
name|b
parameter_list|,
name|row
parameter_list|)
value|(BITMAP_BITS (b) + (row) * BITMAP_WIDTH (b))
end_define

begin_comment
comment|/* This is the pixel at [ROW,COL].  */
end_comment

begin_define
DECL|macro|BITMAP_PIXEL (b,row,col)
define|#
directive|define
name|BITMAP_PIXEL
parameter_list|(
name|b
parameter_list|,
name|row
parameter_list|,
name|col
parameter_list|)
define|\
value|(*(BITMAP_BITS (b) + (row) * BITMAP_WIDTH (b) + (col)))
end_define

begin_define
DECL|macro|BITMAP_VALID_PIXEL (b,row,col)
define|#
directive|define
name|BITMAP_VALID_PIXEL
parameter_list|(
name|b
parameter_list|,
name|row
parameter_list|,
name|col
parameter_list|)
define|\
value|(0<= (row)&& (row)< BITMAP_HEIGHT (b) 			\&& 0<= (col)&& (col)< BITMAP_WIDTH (b))
end_define

begin_comment
comment|/* Assume that the pixel at [ROW,COL] itself is black.  */
end_comment

begin_define
DECL|macro|BITMAP_INTERIOR_PIXEL (b,row,col)
define|#
directive|define
name|BITMAP_INTERIOR_PIXEL
parameter_list|(
name|b
parameter_list|,
name|row
parameter_list|,
name|col
parameter_list|)
define|\
value|(0 != (row)&& (row) != BITMAP_HEIGHT (b) - 1 			\&& 0 != (col)&& (col) != BITMAP_WIDTH (b) - 1			\&& BITMAP_PIXEL (b, row - 1, col - 1) == BLACK			\&& BITMAP_PIXEL (b, row - 1, col) == BLACK			\&& BITMAP_PIXEL (b, row - 1, col + 1) == BLACK			\&& BITMAP_PIXEL (b, row, col - 1) == BLACK			\&& BITMAP_PIXEL (b, row, col + 1) == BLACK			\&& BITMAP_PIXEL (b, row + 1, col - 1) == BLACK			\&& BITMAP_PIXEL (b, row + 1, col) == BLACK			\&& BITMAP_PIXEL (b, row + 1, col + 1) == BLACK)
end_define

begin_escape
end_escape

begin_comment
comment|/* Allocate storage for the bits, set them all to white, and return an    initialized structure.  */
end_comment

begin_function_decl
specifier|extern
name|bitmap_type
name|new_bitmap
parameter_list|(
name|dimensions_type
parameter_list|)
function_decl|;
end_function_decl

begin_comment
comment|/* Free that storage.  */
end_comment

begin_function_decl
specifier|extern
name|void
name|free_bitmap
parameter_list|(
name|bitmap_type
modifier|*
parameter_list|)
function_decl|;
end_function_decl

begin_comment
comment|/* Make a fresh copy of BITMAP in a new structure, and return it.  */
end_comment

begin_function_decl
specifier|extern
name|bitmap_type
name|copy_bitmap
parameter_list|(
name|bitmap_type
name|bitmap
parameter_list|)
function_decl|;
end_function_decl

begin_comment
comment|/* Return the pixels in the bitmap B enclosed by the bounding box BB.     The result is put in newly allocated storage.  */
end_comment

begin_function_decl
specifier|extern
name|bitmap_type
name|extract_subbitmap
parameter_list|(
name|bitmap_type
name|b
parameter_list|,
name|bounding_box_type
name|bb
parameter_list|)
function_decl|;
end_function_decl

begin_comment
comment|/* Consider the dimensions of a bitmap as a bounding box.  The bounding    box returned is in bitmap coordinates, rather than Cartesian, and    refers to pixels, rather than edges.  Specifically, this means that    the maximum column is one less than results from `dimensions_to_bb    (BITMAP_DIMENSIONS ())'.  */
end_comment

begin_function_decl
specifier|extern
specifier|const
name|bounding_box_type
name|bitmap_to_bb
parameter_list|(
specifier|const
name|bitmap_type
parameter_list|)
function_decl|;
end_function_decl

begin_comment
comment|/* Return a vector of zero-based column numbers marking transitions from    black to white or white to black in ROW, which is of length WIDTH.    The end of the vector is marked with an element of length WIDTH + 1.    The first element always marks a white-to-black transition (or it's    0, if the first pixel in ROW is black).  */
end_comment

begin_function_decl
specifier|extern
name|unsigned
modifier|*
name|bitmap_find_transitions
parameter_list|(
specifier|const
name|one_byte
modifier|*
name|row
parameter_list|,
name|unsigned
name|width
parameter_list|)
function_decl|;
end_function_decl

begin_comment
comment|/* Print part of or all of a bitmap.  */
end_comment

begin_function_decl
specifier|extern
name|void
name|print_bounded_bitmap
parameter_list|(
name|FILE
modifier|*
parameter_list|,
name|bitmap_type
parameter_list|,
name|bounding_box_type
parameter_list|)
function_decl|;
end_function_decl

begin_function_decl
specifier|extern
name|void
name|print_bitmap
parameter_list|(
name|FILE
modifier|*
parameter_list|,
name|bitmap_type
parameter_list|)
function_decl|;
end_function_decl

begin_endif
endif|#
directive|endif
end_endif

begin_comment
comment|/* not BITMAP_H */
end_comment

end_unit

