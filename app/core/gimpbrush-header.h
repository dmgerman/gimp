begin_unit|revision:0.9.5;language:C;cregit-version:0.0.1
begin_comment
comment|/* GIMP - The GNU Image Manipulation Program  * Copyright (C) 1995 Spencer Kimball and Peter Mattis  *  * This program is free software: you can redistribute it and/or modify  * it under the terms of the GNU General Public License as published by  * the Free Software Foundation; either version 3 of the License, or  * (at your option) any later version.  *  * This program is distributed in the hope that it will be useful,  * but WITHOUT ANY WARRANTY; without even the implied warranty of  * MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the  * GNU General Public License for more details.  *  * You should have received a copy of the GNU General Public License  * along with this program.  If not, see<http://www.gnu.org/licenses/>.  */
end_comment

begin_ifndef
ifndef|#
directive|ifndef
name|__GIMP_BRUSH_HEADER_H__
end_ifndef

begin_define
DECL|macro|__GIMP_BRUSH_HEADER_H__
define|#
directive|define
name|__GIMP_BRUSH_HEADER_H__
end_define

begin_define
DECL|macro|GIMP_BRUSH_FILE_VERSION
define|#
directive|define
name|GIMP_BRUSH_FILE_VERSION
value|2
end_define

begin_define
DECL|macro|GIMP_BRUSH_MAGIC
define|#
directive|define
name|GIMP_BRUSH_MAGIC
value|(('G'<< 24) + ('I'<< 16) + \                                   ('M'<< 8)  + ('P'<< 0))
end_define

begin_comment
comment|/*  All field entries are MSB  */
end_comment

begin_typedef
DECL|typedef|GimpBrushHeader
typedef|typedef
name|struct
name|_GimpBrushHeader
name|GimpBrushHeader
typedef|;
end_typedef

begin_struct
DECL|struct|_GimpBrushHeader
struct|struct
name|_GimpBrushHeader
block|{
DECL|member|header_size
name|guint32
name|header_size
decl_stmt|;
comment|/*  = sizeof (GimpBrushHeader) + brush name  */
DECL|member|version
name|guint32
name|version
decl_stmt|;
comment|/*  brush file version #  */
DECL|member|width
name|guint32
name|width
decl_stmt|;
comment|/*  width of brush  */
DECL|member|height
name|guint32
name|height
decl_stmt|;
comment|/*  height of brush  */
DECL|member|bytes
name|guint32
name|bytes
decl_stmt|;
comment|/*  depth of brush in bytes--always 1 */
DECL|member|magic_number
name|guint32
name|magic_number
decl_stmt|;
comment|/*  GIMP brush magic number  */
DECL|member|spacing
name|guint32
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
comment|/*  __GIMP_BRUSH_HEADER_H__  */
end_comment

end_unit

