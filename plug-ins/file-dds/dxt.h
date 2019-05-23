begin_unit|revision:0.9.5;language:C;cregit-version:0.0.1
begin_comment
comment|/*  * DDS GIMP plugin  *  * Copyright (C) 2004-2012 Shawn Kirst<skirst@gmail.com>,  * with parts (C) 2003 Arne Reuter<homepage@arnereuter.de> where specified.  *  * This program is free software: you can redistribute it and/or modify  * it under the terms of the GNU General Public License as published by  * the Free Software Foundation; either version 3 of the License, or  * (at your option) any later version.  *  * This program is distributed in the hope that it will be useful,  * but WITHOUT ANY WARRANTY; without even the implied warranty of  * MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the  * GNU General Public License for more details.  *  * You should have received a copy of the GNU General Public License  * along with this program.  If not, see<https://www.gnu.org/licenses/>.  */
end_comment

begin_ifndef
ifndef|#
directive|ifndef
name|__DXT_H__
end_ifndef

begin_define
DECL|macro|__DXT_H__
define|#
directive|define
name|__DXT_H__
end_define

begin_typedef
DECL|enum|dxt_flags_e
typedef|typedef
enum|enum
name|dxt_flags_e
block|{
DECL|enumerator|DXT_BC1
name|DXT_BC1
init|=
literal|1
operator|<<
literal|0
block|,
DECL|enumerator|DXT_BC2
name|DXT_BC2
init|=
literal|1
operator|<<
literal|1
block|,
DECL|enumerator|DXT_BC3
name|DXT_BC3
init|=
literal|1
operator|<<
literal|2
block|,
DECL|enumerator|DXT_PERCEPTUAL
name|DXT_PERCEPTUAL
init|=
literal|1
operator|<<
literal|3
block|, }
DECL|typedef|dxt_flags_t
name|dxt_flags_t
typedef|;
end_typedef

begin_function_decl
name|int
name|dxt_compress
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
name|int
name|format
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
name|mipmaps
parameter_list|,
name|int
name|flags
parameter_list|)
function_decl|;
end_function_decl

begin_function_decl
name|int
name|dxt_decompress
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
name|int
name|format
parameter_list|,
name|unsigned
name|int
name|size
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
name|normals
parameter_list|)
function_decl|;
end_function_decl

begin_endif
endif|#
directive|endif
end_endif

begin_comment
comment|/* __DXT_H__ */
end_comment

end_unit

