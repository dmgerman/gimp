begin_unit|revision:0.9.5;language:C;cregit-version:0.0.1
begin_comment
comment|/* bounding-box.h: operations on both real- and integer-valued bounding boxes.  Copyright (C) 1992 Free Software Foundation, Inc.  This program is free software; you can redistribute it and/or modify it under the terms of the GNU General Public License as published by the Free Software Foundation; either version 2, or (at your option) any later version.  This program is distributed in the hope that it will be useful, but WITHOUT ANY WARRANTY; without even the implied warranty of MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the GNU General Public License for more details.  You should have received a copy of the GNU General Public License along with this program; if not, write to the Free Software Foundation, Inc., 675 Mass Ave, Cambridge, MA 02139, USA.  */
end_comment

begin_ifndef
ifndef|#
directive|ifndef
name|BOUNDING_BOX_H
end_ifndef

begin_define
DECL|macro|BOUNDING_BOX_H
define|#
directive|define
name|BOUNDING_BOX_H
end_define

begin_include
include|#
directive|include
file|"types.h"
end_include

begin_comment
comment|/* The bounding box's numbers are usually in Cartesian/Metafont    coordinates: (0,0) is towards the lower left.  */
end_comment

begin_typedef
typedef|typedef
struct|struct
DECL|struct|__anon2c776be60108
block|{
DECL|member|min_row
DECL|member|max_row
name|signed_4_bytes
name|min_row
decl_stmt|,
name|max_row
decl_stmt|;
DECL|member|min_col
DECL|member|max_col
name|signed_4_bytes
name|min_col
decl_stmt|,
name|max_col
decl_stmt|;
DECL|typedef|bounding_box_type
block|}
name|bounding_box_type
typedef|;
end_typedef

begin_typedef
typedef|typedef
struct|struct
DECL|struct|__anon2c776be60208
block|{
DECL|member|min_row
DECL|member|max_row
name|real
name|min_row
decl_stmt|,
name|max_row
decl_stmt|;
DECL|member|min_col
DECL|member|max_col
name|real
name|min_col
decl_stmt|,
name|max_col
decl_stmt|;
DECL|typedef|real_bounding_box_type
block|}
name|real_bounding_box_type
typedef|;
end_typedef

begin_comment
comment|/* These accessing macros work for both types of bounding boxes, since    the member names are the same.  */
end_comment

begin_define
DECL|macro|MIN_ROW (bb)
define|#
directive|define
name|MIN_ROW
parameter_list|(
name|bb
parameter_list|)
value|((bb).min_row)
end_define

begin_define
DECL|macro|MAX_ROW (bb)
define|#
directive|define
name|MAX_ROW
parameter_list|(
name|bb
parameter_list|)
value|((bb).max_row)
end_define

begin_define
DECL|macro|MIN_COL (bb)
define|#
directive|define
name|MIN_COL
parameter_list|(
name|bb
parameter_list|)
value|((bb).min_col)
end_define

begin_define
DECL|macro|MAX_COL (bb)
define|#
directive|define
name|MAX_COL
parameter_list|(
name|bb
parameter_list|)
value|((bb).max_col)
end_define

begin_comment
comment|/* See the comments at `get_character_bitmap' in gf_input.c for why the    width and height are treated asymetrically.  */
end_comment

begin_define
DECL|macro|BB_WIDTH (bb)
define|#
directive|define
name|BB_WIDTH
parameter_list|(
name|bb
parameter_list|)
value|(MAX_COL (bb) - MIN_COL (bb))
end_define

begin_define
DECL|macro|BB_HEIGHT (bb)
define|#
directive|define
name|BB_HEIGHT
parameter_list|(
name|bb
parameter_list|)
value|(MAX_ROW (bb) - MIN_ROW (bb) + 1)
end_define

begin_comment
comment|/* Convert a dimensions structure to an integer bounding box, and vice    versa.  */
end_comment

begin_function_decl
specifier|extern
specifier|const
name|bounding_box_type
name|dimensions_to_bb
parameter_list|(
name|dimensions_type
parameter_list|)
function_decl|;
end_function_decl

begin_function_decl
specifier|extern
specifier|const
name|dimensions_type
name|bb_to_dimensions
parameter_list|(
name|bounding_box_type
parameter_list|)
function_decl|;
end_function_decl

begin_comment
comment|/* Update the bounding box BB from the point P.  */
end_comment

begin_function_decl
specifier|extern
name|void
name|update_real_bounding_box
parameter_list|(
name|real_bounding_box_type
modifier|*
name|bb
parameter_list|,
name|real_coordinate_type
name|p
parameter_list|)
function_decl|;
end_function_decl

begin_function_decl
specifier|extern
name|void
name|update_bounding_box
parameter_list|(
name|bounding_box_type
modifier|*
name|bb
parameter_list|,
name|coordinate_type
name|p
parameter_list|)
function_decl|;
end_function_decl

begin_endif
endif|#
directive|endif
end_endif

begin_comment
comment|/* not BOUNDING_BOX_H */
end_comment

end_unit

