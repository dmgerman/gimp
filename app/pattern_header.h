begin_unit|revision:0.9.5;language:C;cregit-version:0.0.1
begin_comment
comment|/* The GIMP -- an image manipulation program  * Copyright (C) 1995 Spencer Kimball and Peter Mattis  *  * This program is free software; you can redistribute it and/or modify  * it under the terms of the GNU General Public License as published by  * the Free Software Foundation; either version 2 of the License, or  * (at your option) any later version.  *  * This program is distributed in the hope that it will be useful,  * but WITHOUT ANY WARRANTY; without even the implied warranty of  * MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the  * GNU General Public License for more details.  *  * You should have received a copy of the GNU General Public License  * along with this program; if not, write to the Free Software  * Foundation, Inc., 675 Mass Ave, Cambridge, MA 02139, USA.  */
end_comment

begin_ifndef
ifndef|#
directive|ifndef
name|__PATTERN_HEADER_H__
end_ifndef

begin_define
DECL|macro|__PATTERN_HEADER_H__
define|#
directive|define
name|__PATTERN_HEADER_H__
end_define

begin_typedef
DECL|typedef|PatternHeader
typedef|typedef
name|struct
name|_PatternHeader
name|PatternHeader
typedef|;
end_typedef

begin_define
DECL|macro|FILE_VERSION
define|#
directive|define
name|FILE_VERSION
value|1
end_define

begin_define
DECL|macro|GPATTERN_MAGIC
define|#
directive|define
name|GPATTERN_MAGIC
value|(('G'<< 24) + ('P'<< 16) + ('A'<< 8) + ('T'<< 0))
end_define

begin_define
DECL|macro|sz_PatternHeader
define|#
directive|define
name|sz_PatternHeader
value|(sizeof (PatternHeader))
end_define

begin_comment
comment|/*  All field entries are MSB  */
end_comment

begin_struct
DECL|struct|_PatternHeader
struct|struct
name|_PatternHeader
block|{
DECL|member|header_size
name|unsigned
name|int
name|header_size
decl_stmt|;
comment|/*  header_size = sz_PatternHeader + pattern name  */
DECL|member|version
name|unsigned
name|int
name|version
decl_stmt|;
comment|/*  pattern file version #  */
DECL|member|width
name|unsigned
name|int
name|width
decl_stmt|;
comment|/*  width of pattern  */
DECL|member|height
name|unsigned
name|int
name|height
decl_stmt|;
comment|/*  height of pattern  */
DECL|member|bytes
name|unsigned
name|int
name|bytes
decl_stmt|;
comment|/*  depth of pattern in bytes  */
DECL|member|magic_number
name|unsigned
name|int
name|magic_number
decl_stmt|;
comment|/*  GIMP pattern magic number  */
block|}
struct|;
end_struct

begin_comment
comment|/*  In a pattern file, next comes the pattern name, null-terminated.  After that  *  comes the pattern data--width * height * bytes bytes of it...  */
end_comment

begin_endif
endif|#
directive|endif
end_endif

begin_comment
comment|/*  __PATTERN_HEADER_H__  */
end_comment

end_unit

