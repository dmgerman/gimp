begin_unit|revision:0.9.5;language:C;cregit-version:0.0.1
begin_comment
comment|/* The GIMP -- an image manipulation program  * Copyright (C) 1995-1997 Spencer Kimball and Peter Mattis  *  * GIMP Plug-in for Windows Icon files.  * Copyright (C) 2002 Christian Kreibich<christian@whoop.org>.  *  * This program is free software; you can redistribute it and/or modify  * it under the terms of the GNU General Public License as published by  * the Free Software Foundation; either version 2 of the License, or  * (at your option) any later version.  *  * This program is distributed in the hope that it will be useful,  * but WITHOUT ANY WARRANTY; without even the implied warranty of  * MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the  * GNU General Public License for more details.  *  * You should have received a copy of the GNU General Public License  * along with this program; if not, write to the Free Software  * Foundation, Inc., 59 Temple Place - Suite 330, Boston, MA 02111-1307, USA.  */
end_comment

begin_ifndef
ifndef|#
directive|ifndef
name|__MAIN_H__
end_ifndef

begin_define
DECL|macro|__MAIN_H__
define|#
directive|define
name|__MAIN_H__
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
DECL|macro|MAXLEN
define|#
directive|define
name|MAXLEN
value|4096
end_define

begin_typedef
DECL|struct|_MsIconEntry
typedef|typedef
struct|struct
name|_MsIconEntry
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
comment|/* Maximum number of colors */
DECL|member|reserved
name|guint8
name|reserved
decl_stmt|;
comment|/* Not used */
DECL|member|num_planes
name|guint16
name|num_planes
decl_stmt|;
comment|/* Not used */
DECL|member|bpp
name|guint16
name|bpp
decl_stmt|;
DECL|member|size
name|guint32
name|size
decl_stmt|;
comment|/* Length of icon bitmap in bytes */
DECL|member|offset
name|guint32
name|offset
decl_stmt|;
comment|/* Offset position of icon bitmap in file */
DECL|typedef|MsIconEntry
block|}
name|MsIconEntry
typedef|;
end_typedef

begin_typedef
DECL|struct|_MsIconData
typedef|typedef
struct|struct
name|_MsIconData
block|{
comment|/* Bitmap header data */
DECL|member|header_size
name|guint32
name|header_size
decl_stmt|;
comment|/* = 40 Bytes */
DECL|member|width
name|guint32
name|width
decl_stmt|;
DECL|member|height
name|guint32
name|height
decl_stmt|;
DECL|member|planes
name|guint16
name|planes
decl_stmt|;
DECL|member|bpp
name|guint16
name|bpp
decl_stmt|;
DECL|member|compression
name|guint32
name|compression
decl_stmt|;
comment|/* not used for icons */
DECL|member|image_size
name|guint32
name|image_size
decl_stmt|;
comment|/* size of image */
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
DECL|member|palette
name|guint32
modifier|*
name|palette
decl_stmt|;
comment|/* Color palette, only if bpp<= 8. */
DECL|member|xor_map
name|guint8
modifier|*
name|xor_map
decl_stmt|;
comment|/* Icon bitmap */
DECL|member|and_map
name|guint8
modifier|*
name|and_map
decl_stmt|;
comment|/* Display bit mask */
comment|/* Only used when saving: */
DECL|member|palette_len
name|gint
name|palette_len
decl_stmt|;
DECL|member|xor_len
name|gint
name|xor_len
decl_stmt|;
DECL|member|and_len
name|gint
name|and_len
decl_stmt|;
DECL|typedef|MsIconData
block|}
name|MsIconData
typedef|;
end_typedef

begin_typedef
DECL|struct|_MsIcon
typedef|typedef
struct|struct
name|_MsIcon
block|{
DECL|member|fp
name|FILE
modifier|*
name|fp
decl_stmt|;
DECL|member|cp
name|guint
name|cp
decl_stmt|;
DECL|member|filename
specifier|const
name|gchar
modifier|*
name|filename
decl_stmt|;
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
DECL|member|icon_dir
name|MsIconEntry
modifier|*
name|icon_dir
decl_stmt|;
DECL|member|icon_data
name|MsIconData
modifier|*
name|icon_data
decl_stmt|;
DECL|typedef|MsIcon
block|}
name|MsIcon
typedef|;
end_typedef

begin_comment
comment|/* Miscellaneous helper functions below: */
end_comment

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

begin_function_decl
name|void
name|ico_cleanup
parameter_list|(
name|MsIcon
modifier|*
name|ico
parameter_list|)
function_decl|;
end_function_decl

begin_endif
endif|#
directive|endif
end_endif

begin_comment
comment|/* __MAIN_H__ */
end_comment

end_unit

