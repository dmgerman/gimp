begin_unit|revision:0.9.5;language:C;cregit-version:0.0.1
begin_comment
comment|/* edge.h: declarations for edge traversing.  Copyright (C) 1992 Free Software Foundation, Inc.  This program is free software; you can redistribute it and/or modify it under the terms of the GNU General Public License as published by the Free Software Foundation; either version 2, or (at your option) any later version.  This program is distributed in the hope that it will be useful, but WITHOUT ANY WARRANTY; without even the implied warranty of MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the GNU General Public License for more details.  You should have received a copy of the GNU General Public License along with this program; if not, write to the Free Software Foundation, Inc., 675 Mass Ave, Cambridge, MA 02139, USA.  */
end_comment

begin_ifndef
ifndef|#
directive|ifndef
name|EDGE_H
end_ifndef

begin_define
DECL|macro|EDGE_H
define|#
directive|define
name|EDGE_H
end_define

begin_include
include|#
directive|include
file|"bitmap.h"
end_include

begin_comment
comment|/* We consider each pixel to consist of four edges, and we travel along    edges, instead of through pixel centers.  This is necessary for those    unfortunate times when a single pixel is on both an inside and an    outside outline.        The numbers chosen here are not arbitrary; the code that figures out    which edge to move to depends on particular values.  See the    `TRY_PIXEL' macro in `edge.c'.  To emphasize this, I've written in the    numbers we need for each edge value.  */
end_comment

begin_typedef
typedef|typedef
enum|enum
DECL|enum|__anon29e12c360103
block|{
DECL|enumerator|top
DECL|enumerator|left
DECL|enumerator|bottom
DECL|enumerator|right
DECL|enumerator|no_edge
name|top
init|=
literal|1
block|,
name|left
init|=
literal|2
block|,
name|bottom
init|=
literal|3
block|,
name|right
init|=
literal|0
block|,
name|no_edge
init|=
literal|4
DECL|typedef|edge_type
block|}
name|edge_type
typedef|;
end_typedef

begin_comment
comment|/* This choice is also not arbitrary: starting at the top edge makes the    code find outside outlines before inside ones, which is certainly    what we want.  */
end_comment

begin_define
DECL|macro|START_EDGE
define|#
directive|define
name|START_EDGE
value|top
end_define

begin_comment
comment|/* Return the next outline edge on B in EDGE, ROW, and COL.  */
end_comment

begin_function_decl
specifier|extern
name|void
name|next_outline_edge
parameter_list|(
name|edge_type
modifier|*
name|edge
parameter_list|,
name|unsigned
modifier|*
name|row
parameter_list|,
name|unsigned
modifier|*
name|col
parameter_list|)
function_decl|;
end_function_decl

begin_comment
comment|/* Return the next edge after START on the pixel ROW/COL in B that is    unmarked, according to the MARKED array.  */
end_comment

begin_function_decl
specifier|extern
name|edge_type
name|next_unmarked_outline_edge
parameter_list|(
name|unsigned
name|row
parameter_list|,
name|unsigned
name|col
parameter_list|,
name|edge_type
name|start
parameter_list|,
name|bitmap_type
name|marked
parameter_list|)
function_decl|;
end_function_decl

begin_comment
comment|/* Mark the edge E at the pixel ROW/COL in MARKED.  */
end_comment

begin_function_decl
specifier|extern
name|void
name|mark_edge
parameter_list|(
name|edge_type
name|e
parameter_list|,
name|unsigned
name|row
parameter_list|,
name|unsigned
name|col
parameter_list|,
name|bitmap_type
modifier|*
name|marked
parameter_list|)
function_decl|;
end_function_decl

begin_endif
endif|#
directive|endif
end_endif

begin_comment
comment|/* not EDGE_H */
end_comment

end_unit

