begin_unit|revision:0.9.5;language:C;cregit-version:0.0.1
begin_comment
comment|/* The GIMP -- an image manipulation program  * Copyright (C) 1995 Spencer Kimball and Peter Mattis  *  * This program is free software; you can redistribute it and/or modify  * it under the terms of the GNU General Public License as published by  * the Free Software Foundation; either version 2 of the License, or  * (at your option) any later version.  *  * This program is distributed in the hope that it will be useful,  * but WITHOUT ANY WARRANTY; without even the implied warranty of  * MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the  * GNU General Public License for more details.  *  * You should have received a copy of the GNU General Public License  * along with this program; if not, write to the Free Software  * Foundation, Inc., 59 Temple Place - Suite 330, Boston, MA 02111-1307, USA.  */
end_comment

begin_ifndef
ifndef|#
directive|ifndef
name|__BRUSH_HEADER_H__
end_ifndef

begin_define
DECL|macro|__BRUSH_HEADER_H__
define|#
directive|define
name|__BRUSH_HEADER_H__
end_define

begin_typedef
DECL|typedef|BrushHeader
typedef|typedef
name|struct
name|_BrushHeader
name|BrushHeader
typedef|;
end_typedef

begin_define
DECL|macro|FILE_VERSION
define|#
directive|define
name|FILE_VERSION
value|2
end_define

begin_define
DECL|macro|GBRUSH_MAGIC
define|#
directive|define
name|GBRUSH_MAGIC
value|(('G'<< 24) + ('I'<< 16) + ('M'<< 8) + ('P'<< 0))
end_define

begin_define
DECL|macro|sz_BrushHeader
define|#
directive|define
name|sz_BrushHeader
value|(sizeof (BrushHeader))
end_define

begin_comment
comment|/*  All field entries are MSB  */
end_comment

begin_struct
DECL|struct|_BrushHeader
struct|struct
name|_BrushHeader
block|{
DECL|member|header_size
name|unsigned
name|int
name|header_size
decl_stmt|;
comment|/*  header_size = sz_BrushHeader + brush name  */
DECL|member|version
name|unsigned
name|int
name|version
decl_stmt|;
comment|/*  brush file version #  */
DECL|member|width
name|unsigned
name|int
name|width
decl_stmt|;
comment|/*  width of brush  */
DECL|member|height
name|unsigned
name|int
name|height
decl_stmt|;
comment|/*  height of brush  */
DECL|member|bytes
name|unsigned
name|int
name|bytes
decl_stmt|;
comment|/*  depth of brush in bytes--always 1 */
DECL|member|magic_number
name|unsigned
name|int
name|magic_number
decl_stmt|;
comment|/*  GIMP brush magic number  */
DECL|member|spacing
name|unsigned
name|int
name|spacing
decl_stmt|;
comment|/*  brush spacing  */
block|}
struct|;
end_struct

begin_comment
comment|/*  In a brush file, next comes the brush name, null-terminated.  After that  *  comes the brush data--width * height * bytes bytes of it...  */
end_comment

begin_endif
endif|#
directive|endif
end_endif

begin_comment
comment|/*  __BRUSH_HEADER_H__  */
end_comment

end_unit

