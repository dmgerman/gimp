begin_unit|revision:0.9.5;language:C;cregit-version:0.0.1
begin_comment
comment|/*  * DDS GIMP plugin  *  * Copyright (C) 2004-2012 Shawn Kirst<skirst@gmail.com>,  * with parts (C) 2003 Arne Reuter<homepage@arnereuter.de> where specified.  *  * This program is free software: you can redistribute it and/or modify  * it under the terms of the GNU General Public License as published by  * the Free Software Foundation; either version 3 of the License, or  * (at your option) any later version.  *  * This program is distributed in the hope that it will be useful,  * but WITHOUT ANY WARRANTY; without even the implied warranty of  * MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the  * GNU General Public License for more details.  *  * You should have received a copy of the GNU General Public License  * along with this program.  If not, see<https://www.gnu.org/licenses/>.  */
end_comment

begin_ifndef
ifndef|#
directive|ifndef
name|__MIPMAP_H__
end_ifndef

begin_define
DECL|macro|__MIPMAP_H__
define|#
directive|define
name|__MIPMAP_H__
end_define

begin_function_decl
name|int
name|get_num_mipmaps
parameter_list|(
name|int
name|width
parameter_list|,
name|int
name|height
parameter_list|)
function_decl|;
end_function_decl

begin_function_decl
name|unsigned
name|int
name|get_mipmapped_size
parameter_list|(
name|int
name|width
parameter_list|,
name|int
name|height
parameter_list|,
name|int
name|bpp
parameter_list|,
name|int
name|level
parameter_list|,
name|int
name|num
parameter_list|,
name|int
name|format
parameter_list|)
function_decl|;
end_function_decl

begin_function_decl
name|unsigned
name|int
name|get_volume_mipmapped_size
parameter_list|(
name|int
name|width
parameter_list|,
name|int
name|height
parameter_list|,
name|int
name|depth
parameter_list|,
name|int
name|bpp
parameter_list|,
name|int
name|level
parameter_list|,
name|int
name|num
parameter_list|,
name|int
name|format
parameter_list|)
function_decl|;
end_function_decl

begin_function_decl
name|int
name|get_next_mipmap_dimensions
parameter_list|(
name|int
modifier|*
name|next_w
parameter_list|,
name|int
modifier|*
name|next_h
parameter_list|,
name|int
name|curr_w
parameter_list|,
name|int
name|curr_h
parameter_list|)
function_decl|;
end_function_decl

begin_function_decl
name|float
name|cubic_interpolate
parameter_list|(
name|float
name|a
parameter_list|,
name|float
name|b
parameter_list|,
name|float
name|c
parameter_list|,
name|float
name|d
parameter_list|,
name|float
name|x
parameter_list|)
function_decl|;
end_function_decl

begin_function_decl
name|int
name|generate_mipmaps
parameter_list|(
name|unsigned
name|char
modifier|*
name|dst
parameter_list|,
name|unsigned
name|char
modifier|*
name|src
parameter_list|,
name|unsigned
name|int
name|width
parameter_list|,
name|unsigned
name|int
name|height
parameter_list|,
name|int
name|bpp
parameter_list|,
name|int
name|indexed
parameter_list|,
name|int
name|mipmaps
parameter_list|,
name|int
name|filter
parameter_list|,
name|int
name|wrap
parameter_list|,
name|int
name|gamma_correct
parameter_list|,
name|float
name|gamma
parameter_list|,
name|int
name|preserve_alpha_test_coverage
parameter_list|,
name|float
name|alpha_test_threshold
parameter_list|)
function_decl|;
end_function_decl

begin_function_decl
name|int
name|generate_volume_mipmaps
parameter_list|(
name|unsigned
name|char
modifier|*
name|dst
parameter_list|,
name|unsigned
name|char
modifier|*
name|src
parameter_list|,
name|unsigned
name|int
name|width
parameter_list|,
name|unsigned
name|int
name|height
parameter_list|,
name|unsigned
name|int
name|depth
parameter_list|,
name|int
name|bpp
parameter_list|,
name|int
name|indexed
parameter_list|,
name|int
name|mipmaps
parameter_list|,
name|int
name|filter
parameter_list|,
name|int
name|wrap
parameter_list|,
name|int
name|gamma_correct
parameter_list|,
name|float
name|gamma
parameter_list|)
function_decl|;
end_function_decl

begin_endif
endif|#
directive|endif
end_endif

begin_comment
comment|/* __MIPMAP_H__ */
end_comment

end_unit

