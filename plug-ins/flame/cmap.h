begin_unit|revision:0.9.5;language:C;cregit-version:0.0.1
begin_comment
comment|/*     flame - cosmic recursive fractal flames     Copyright (C) 1992  Scott Draves<spot@cs.cmu.edu>      This program is free software; you can redistribute it and/or modify     it under the terms of the GNU General Public License as published by     the Free Software Foundation; either version 2 of the License, or     (at your option) any later version.      This program is distributed in the hope that it will be useful,     but WITHOUT ANY WARRANTY; without even the implied warranty of     MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the     GNU General Public License for more details.      You should have received a copy of the GNU General Public License     along with this program; if not, write to the Free Software     Foundation, Inc., 675 Mass Ave, Cambridge, MA 02139, USA. */
end_comment

begin_ifndef
ifndef|#
directive|ifndef
name|cmap_included
end_ifndef

begin_define
DECL|macro|cmap_included
define|#
directive|define
name|cmap_included
end_define

begin_define
DECL|macro|cmap_random
define|#
directive|define
name|cmap_random
value|(-1)
end_define

begin_define
DECL|macro|vlen (x)
define|#
directive|define
name|vlen
parameter_list|(
name|x
parameter_list|)
value|(sizeof(x)/sizeof(*x))
end_define

begin_typedef
DECL|typedef|clrmap
typedef|typedef
name|double
name|clrmap
index|[
literal|256
index|]
index|[
literal|3
index|]
typedef|;
end_typedef

begin_function_decl
specifier|extern
name|void
name|rgb2hsv
parameter_list|(
name|double
modifier|*
name|rgb
parameter_list|,
name|double
modifier|*
name|hsv
parameter_list|)
function_decl|;
end_function_decl

begin_function_decl
specifier|extern
name|void
name|hsv2rgb
parameter_list|(
name|double
modifier|*
name|hsv
parameter_list|,
name|double
modifier|*
name|rgb
parameter_list|)
function_decl|;
end_function_decl

begin_function_decl
specifier|extern
name|int
name|get_cmap
parameter_list|(
name|int
name|n
parameter_list|,
name|clrmap
name|c
parameter_list|,
name|int
name|cmap_len
parameter_list|)
function_decl|;
end_function_decl

begin_endif
endif|#
directive|endif
end_endif

end_unit

