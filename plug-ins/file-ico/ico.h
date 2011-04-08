begin_unit|revision:0.9.5;language:C;cregit-version:0.0.1
begin_comment
comment|/* GIMP - The GNU Image Manipulation Program  * Copyright (C) 1995-1997 Spencer Kimball and Peter Mattis  *  * GIMP Plug-in for Windows Icon files.  * Copyright (C) 2002 Christian Kreibich<christian@whoop.org>.  *  * This program is free software: you can redistribute it and/or modify  * it under the terms of the GNU General Public License as published by  * the Free Software Foundation; either version 3 of the License, or  * (at your option) any later version.  *  * This program is distributed in the hope that it will be useful,  * but WITHOUT ANY WARRANTY; without even the implied warranty of  * MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the  * GNU General Public License for more details.  *  * You should have received a copy of the GNU General Public License  * along with this program.  If not, see<http://www.gnu.org/licenses/>.  */
end_comment

begin_ifndef
ifndef|#
directive|ifndef
name|__ICO_H__
end_ifndef

begin_define
DECL|macro|__ICO_H__
define|#
directive|define
name|__ICO_H__
end_define

begin_ifdef
ifdef|#
directive|ifdef
name|ICO_DBG
end_ifdef

begin_define
DECL|macro|D (x)
define|#
directive|define
name|D
parameter_list|(
name|x
parameter_list|)
define|\
value|{ \   printf("ICO plugin: "); \   printf x; \ }
end_define

begin_else
else|#
directive|else
end_else

begin_define
DECL|macro|D (x)
define|#
directive|define
name|D
parameter_list|(
name|x
parameter_list|)
end_define

begin_endif
endif|#
directive|endif
end_endif

begin_define
DECL|macro|PLUG_IN_BINARY
define|#
directive|define
name|PLUG_IN_BINARY
value|"file-ico"
end_define

begin_define
DECL|macro|PLUG_IN_ROLE
define|#
directive|define
name|PLUG_IN_ROLE
value|"gimp-file-ico"
end_define

begin_define
DECL|macro|ICO_PNG_MAGIC
define|#
directive|define
name|ICO_PNG_MAGIC
value|0x474e5089
end_define

begin_define
DECL|macro|ICO_ALPHA_THRESHOLD
define|#
directive|define
name|ICO_ALPHA_THRESHOLD
value|127
end_define

begin_define
DECL|macro|ICO_MAXBUF
define|#
directive|define
name|ICO_MAXBUF
value|4096
end_define

begin_typedef
DECL|struct|_IcoFileHeader
typedef|typedef
struct|struct
name|_IcoFileHeader
block|{
DECL|member|reserved
name|guint16
name|reserved
decl_stmt|;
DECL|member|resource_type
name|guint16
name|resource_type
decl_stmt|;
DECL|member|icon_count
name|guint16
name|icon_count
decl_stmt|;
DECL|typedef|IcoFileHeader
block|}
name|IcoFileHeader
typedef|;
end_typedef

begin_typedef
DECL|struct|_IcoFileEntry
typedef|typedef
struct|struct
name|_IcoFileEntry
block|{
DECL|member|width
name|guint8
name|width
decl_stmt|;
comment|/* Width of icon in pixels */
DECL|member|height
name|guint8
name|height
decl_stmt|;
comment|/* Height of icon in pixels */
DECL|member|num_colors
name|guint8
name|num_colors
decl_stmt|;
comment|/* Number of colors of paletted image */
DECL|member|reserved
name|guint8
name|reserved
decl_stmt|;
comment|/* Must be 0 */
DECL|member|planes
name|guint16
name|planes
decl_stmt|;
comment|/* Must be 1 */
DECL|member|bpp
name|guint16
name|bpp
decl_stmt|;
comment|/* 1, 4, 8, 24 or 32 bits per pixel */
DECL|member|size
name|guint32
name|size
decl_stmt|;
comment|/* Size of icon (including data header) */
DECL|member|offset
name|guint32
name|offset
decl_stmt|;
comment|/* Absolute offset of data in a file */
DECL|typedef|IcoFileEntry
block|}
name|IcoFileEntry
typedef|;
end_typedef

begin_typedef
DECL|struct|_IcoFileDataHeader
typedef|typedef
struct|struct
name|_IcoFileDataHeader
block|{
DECL|member|header_size
name|guint32
name|header_size
decl_stmt|;
comment|/* 40 bytes */
DECL|member|width
name|guint32
name|width
decl_stmt|;
comment|/* Width of image in pixels */
DECL|member|height
name|guint32
name|height
decl_stmt|;
comment|/* Height of image in pixels */
DECL|member|planes
name|guint16
name|planes
decl_stmt|;
comment|/* Must be 1 */
DECL|member|bpp
name|guint16
name|bpp
decl_stmt|;
DECL|member|compression
name|guint32
name|compression
decl_stmt|;
comment|/* Not used for icons */
DECL|member|image_size
name|guint32
name|image_size
decl_stmt|;
comment|/* Size of image (without this header) */
DECL|member|x_res
name|guint32
name|x_res
decl_stmt|;
DECL|member|y_res
name|guint32
name|y_res
decl_stmt|;
DECL|member|used_clrs
name|guint32
name|used_clrs
decl_stmt|;
DECL|member|important_clrs
name|guint32
name|important_clrs
decl_stmt|;
DECL|typedef|IcoFileDataHeader
block|}
name|IcoFileDataHeader
typedef|;
end_typedef

begin_typedef
DECL|struct|_IcoLoadInfo
typedef|typedef
struct|struct
name|_IcoLoadInfo
block|{
DECL|member|width
name|guint
name|width
decl_stmt|;
DECL|member|height
name|guint
name|height
decl_stmt|;
DECL|member|bpp
name|gint
name|bpp
decl_stmt|;
DECL|member|offset
name|gint
name|offset
decl_stmt|;
DECL|member|size
name|gint
name|size
decl_stmt|;
DECL|typedef|IcoLoadInfo
block|}
name|IcoLoadInfo
typedef|;
end_typedef

begin_typedef
DECL|struct|_IcoSaveInfo
typedef|typedef
struct|struct
name|_IcoSaveInfo
block|{
DECL|member|depths
name|gint
modifier|*
name|depths
decl_stmt|;
DECL|member|default_depths
name|gint
modifier|*
name|default_depths
decl_stmt|;
DECL|member|compress
name|gboolean
modifier|*
name|compress
decl_stmt|;
DECL|member|layers
name|gint
modifier|*
name|layers
decl_stmt|;
DECL|member|num_icons
name|gint
name|num_icons
decl_stmt|;
DECL|typedef|IcoSaveInfo
block|}
name|IcoSaveInfo
typedef|;
end_typedef

begin_comment
comment|/* Miscellaneous helper functions below: */
end_comment

begin_function_decl
name|gint
name|ico_rowstride
parameter_list|(
name|gint
name|width
parameter_list|,
name|gint
name|bpp
parameter_list|)
function_decl|;
end_function_decl

begin_comment
comment|/* Allocates a 32-bit padded bitmap for various color depths.    Returns the allocated array directly, and the length of the    array in the len pointer */
end_comment

begin_function_decl
name|guint8
modifier|*
name|ico_alloc_map
parameter_list|(
name|gint
name|width
parameter_list|,
name|gint
name|height
parameter_list|,
name|gint
name|bpp
parameter_list|,
name|gint
modifier|*
name|len
parameter_list|)
function_decl|;
end_function_decl

begin_endif
endif|#
directive|endif
end_endif

begin_comment
comment|/* __ICO_H__ */
end_comment

end_unit

