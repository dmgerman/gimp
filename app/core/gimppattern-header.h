begin_unit|revision:0.9.5;language:C;cregit-version:0.0.1
begin_comment
comment|/* GIMP - The GNU Image Manipulation Program  * Copyright (C) 1995 Spencer Kimball and Peter Mattis  *  * This program is free software: you can redistribute it and/or modify  * it under the terms of the GNU General Public License as published by  * the Free Software Foundation; either version 3 of the License, or  * (at your option) any later version.  *  * This program is distributed in the hope that it will be useful,  * but WITHOUT ANY WARRANTY; without even the implied warranty of  * MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the  * GNU General Public License for more details.  *  * You should have received a copy of the GNU General Public License  * along with this program.  If not, see<https://www.gnu.org/licenses/>.  */
end_comment

begin_ifndef
ifndef|#
directive|ifndef
name|__GIMP_PATTERN_HEADER_H__
end_ifndef

begin_define
DECL|macro|__GIMP_PATTERN_HEADER_H__
define|#
directive|define
name|__GIMP_PATTERN_HEADER_H__
end_define

begin_define
DECL|macro|GIMP_PATTERN_MAGIC
define|#
directive|define
name|GIMP_PATTERN_MAGIC
value|(('G'<< 24) + ('P'<< 16) + \                                ('A'<< 8)  + ('T'<< 0))
end_define

begin_define
DECL|macro|GIMP_PATTERN_MAX_SIZE
define|#
directive|define
name|GIMP_PATTERN_MAX_SIZE
value|10000
end_define

begin_comment
DECL|macro|GIMP_PATTERN_MAX_SIZE
comment|/* Max size in either dimension in px */
end_comment

begin_define
DECL|macro|GIMP_PATTERN_MAX_NAME
define|#
directive|define
name|GIMP_PATTERN_MAX_NAME
value|256
end_define

begin_comment
DECL|macro|GIMP_PATTERN_MAX_NAME
comment|/* Max length of the pattern's name   */
end_comment

begin_comment
comment|/*  All field entries are MSB  */
end_comment

begin_typedef
DECL|typedef|GimpPatternHeader
typedef|typedef
name|struct
name|_GimpPatternHeader
name|GimpPatternHeader
typedef|;
end_typedef

begin_struct
DECL|struct|_GimpPatternHeader
struct|struct
name|_GimpPatternHeader
block|{
DECL|member|header_size
name|guint32
name|header_size
decl_stmt|;
comment|/*  = sizeof (GimpPatternHeader) + pattern name  */
DECL|member|version
name|guint32
name|version
decl_stmt|;
comment|/*  pattern file version #  */
DECL|member|width
name|guint32
name|width
decl_stmt|;
comment|/*  width of pattern  */
DECL|member|height
name|guint32
name|height
decl_stmt|;
comment|/*  height of pattern  */
DECL|member|bytes
name|guint32
name|bytes
decl_stmt|;
comment|/*  depth of pattern in bytes  */
DECL|member|magic_number
name|guint32
name|magic_number
decl_stmt|;
comment|/*  GIMP pattern magic number  */
block|}
struct|;
end_struct

begin_comment
comment|/*  In a pattern file, next comes the pattern name, null-terminated.  *  After that comes the pattern data -- width * height * bytes bytes  *  of it...  */
end_comment

begin_endif
endif|#
directive|endif
end_endif

begin_comment
comment|/* __GIMP_PATTERN_HEADER_H__ */
end_comment

end_unit

