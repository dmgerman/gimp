begin_unit|revision:0.9.5;language:C;cregit-version:0.0.1
begin_comment
comment|/*     flame - cosmic recursive fractal flames     Copyright (C) 1992  Scott Draves<spot@cs.cmu.edu>      This program is free software; you can redistribute it and/or modify     it under the terms of the GNU General Public License as published by     the Free Software Foundation; either version 2 of the License, or     (at your option) any later version.      This program is distributed in the hope that it will be useful,     but WITHOUT ANY WARRANTY; without even the implied warranty of     MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the     GNU General Public License for more details.      You should have received a copy of the GNU General Public License     along with this program; if not, write to the Free Software     Foundation, Inc., 59 Temple Place - Suite 330, Boston, MA 02111-1307, USA. */
end_comment

begin_include
include|#
directive|include
file|"libifs.h"
end_include

begin_comment
comment|/* size of the cmap actually used. may be smaller than input cmap size */
end_comment

begin_define
DECL|macro|CMAP_SIZE
define|#
directive|define
name|CMAP_SIZE
value|256
end_define

begin_typedef
DECL|struct|__anon2bb913560108
typedef|typedef
struct|struct
block|{
DECL|member|temporal_filter_radius
name|double
name|temporal_filter_radius
decl_stmt|;
DECL|member|cps
name|control_point
modifier|*
name|cps
decl_stmt|;
DECL|member|ncps
name|int
name|ncps
decl_stmt|;
DECL|member|time
name|double
name|time
decl_stmt|;
DECL|typedef|frame_spec
block|}
name|frame_spec
typedef|;
end_typedef

begin_define
DECL|macro|field_both
define|#
directive|define
name|field_both
value|0
end_define

begin_define
DECL|macro|field_even
define|#
directive|define
name|field_even
value|1
end_define

begin_define
DECL|macro|field_odd
define|#
directive|define
name|field_odd
value|2
end_define

begin_function_decl
specifier|extern
name|void
name|render_rectangle
parameter_list|(
name|frame_spec
modifier|*
name|spec
parameter_list|,
name|unsigned
name|char
modifier|*
name|out
parameter_list|,
name|int
name|out_width
parameter_list|,
name|int
name|field
parameter_list|,
name|int
name|nchan
parameter_list|,
name|int
name|progress
parameter_list|(
name|double
parameter_list|)
parameter_list|)
function_decl|;
end_function_decl

end_unit

