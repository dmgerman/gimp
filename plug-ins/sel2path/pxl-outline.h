begin_unit|revision:0.9.5;language:C;cregit-version:0.0.1
begin_comment
comment|/* pxl-outline.h: find a list of outlines which make up one character.  Copyright (C) 1992 Free Software Foundation, Inc.  This program is free software; you can redistribute it and/or modify it under the terms of the GNU General Public License as published by the Free Software Foundation; either version 2, or (at your option) any later version.  This program is distributed in the hope that it will be useful, but WITHOUT ANY WARRANTY; without even the implied warranty of MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the GNU General Public License for more details.  You should have received a copy of the GNU General Public License along with this program; if not, write to the Free Software Foundation, Inc., 675 Mass Ave, Cambridge, MA 02139, USA.  */
end_comment

begin_ifndef
ifndef|#
directive|ifndef
name|PXL_OUTLINE_H
end_ifndef

begin_define
DECL|macro|PXL_OUTLINE_H
define|#
directive|define
name|PXL_OUTLINE_H
end_define

begin_include
include|#
directive|include
file|"types.h"
end_include

begin_comment
comment|/* This is a list of contiguous points on the bitmap.  */
end_comment

begin_typedef
typedef|typedef
struct|struct
DECL|struct|__anon280455c00108
block|{
DECL|member|data
name|coordinate_type
modifier|*
name|data
decl_stmt|;
DECL|member|length
name|unsigned
name|length
decl_stmt|;
DECL|member|clockwise
name|boolean
name|clockwise
decl_stmt|;
DECL|typedef|pixel_outline_type
block|}
name|pixel_outline_type
typedef|;
end_typedef

begin_comment
comment|/* The Nth coordinate in the list.  */
end_comment

begin_define
DECL|macro|O_COORDINATE (p_o,n)
define|#
directive|define
name|O_COORDINATE
parameter_list|(
name|p_o
parameter_list|,
name|n
parameter_list|)
value|((p_o).data[n])
end_define

begin_comment
comment|/* The length of the list.  */
end_comment

begin_define
DECL|macro|O_LENGTH (p_o)
define|#
directive|define
name|O_LENGTH
parameter_list|(
name|p_o
parameter_list|)
value|((p_o).length)
end_define

begin_comment
comment|/* Whether the outline moves clockwise or counterclockwise.  */
end_comment

begin_define
DECL|macro|O_CLOCKWISE (p_o)
define|#
directive|define
name|O_CLOCKWISE
parameter_list|(
name|p_o
parameter_list|)
value|((p_o).clockwise)
end_define

begin_comment
comment|/* Since a pixel outline is cyclic, the index of thenext coordinate    after the last is the first, and the previous coordinate before the    first is the last.  */
end_comment

begin_define
DECL|macro|O_NEXT (p_o,n)
define|#
directive|define
name|O_NEXT
parameter_list|(
name|p_o
parameter_list|,
name|n
parameter_list|)
value|(((n) + 1) % O_LENGTH (p_o))
end_define

begin_define
DECL|macro|O_PREV (p_o,n)
define|#
directive|define
name|O_PREV
parameter_list|(
name|p_o
parameter_list|,
name|n
parameter_list|)
value|((n) == 0				\                          ? O_LENGTH (p_o) - 1			\                          : (n) - 1)
end_define

begin_comment
comment|/* And the character turns into a list of such lists.  */
end_comment

begin_typedef
typedef|typedef
struct|struct
DECL|struct|__anon280455c00208
block|{
DECL|member|data
name|pixel_outline_type
modifier|*
name|data
decl_stmt|;
DECL|member|length
name|unsigned
name|length
decl_stmt|;
DECL|typedef|pixel_outline_list_type
block|}
name|pixel_outline_list_type
typedef|;
end_typedef

begin_comment
comment|/* The Nth list in the list of lists.  */
end_comment

begin_define
DECL|macro|O_LIST_OUTLINE (p_o_l,n)
define|#
directive|define
name|O_LIST_OUTLINE
parameter_list|(
name|p_o_l
parameter_list|,
name|n
parameter_list|)
value|((p_o_l).data[n])
end_define

begin_comment
comment|/* The length of the list of lists.  */
end_comment

begin_define
DECL|macro|O_LIST_LENGTH (p_o_l)
define|#
directive|define
name|O_LIST_LENGTH
parameter_list|(
name|p_o_l
parameter_list|)
value|((p_o_l).length)
end_define

begin_comment
comment|/* Find all pixels on the outline in the character C.  */
end_comment

begin_function_decl
specifier|extern
name|pixel_outline_list_type
name|find_outline_pixels
parameter_list|()
function_decl|;
end_function_decl

begin_comment
comment|/* Free the memory in the list.  */
end_comment

begin_function_decl
specifier|extern
name|void
name|free_pixel_outline_list
parameter_list|(
name|pixel_outline_list_type
modifier|*
parameter_list|)
function_decl|;
end_function_decl

begin_endif
endif|#
directive|endif
end_endif

begin_comment
comment|/* not PXL_OUTLINE_H */
end_comment

end_unit

