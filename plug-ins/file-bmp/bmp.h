begin_unit|revision:0.9.5;language:C;cregit-version:0.0.1
begin_comment
comment|/*  * GIMP - The GNU Image Manipulation Program  * Copyright (C) 1995 Spencer Kimball and Peter Mattis  *  * This program is free software: you can redistribute it and/or modify  * it under the terms of the GNU General Public License as published by  * the Free Software Foundation; either version 3 of the License, or  * (at your option) any later version.  *  * This program is distributed in the hope that it will be useful,  * but WITHOUT ANY WARRANTY; without even the implied warranty of  * MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the  * GNU General Public License for more details.  *  * You should have received a copy of the GNU General Public License  * along with this program.  If not, see<http://www.gnu.org/licenses/>.  */
end_comment

begin_ifndef
ifndef|#
directive|ifndef
name|__BMP_H__
end_ifndef

begin_define
DECL|macro|__BMP_H__
define|#
directive|define
name|__BMP_H__
end_define

begin_define
DECL|macro|LOAD_PROC
define|#
directive|define
name|LOAD_PROC
value|"file-bmp-load"
end_define

begin_define
DECL|macro|SAVE_PROC
define|#
directive|define
name|SAVE_PROC
value|"file-bmp-save"
end_define

begin_define
DECL|macro|PLUG_IN_BINARY
define|#
directive|define
name|PLUG_IN_BINARY
value|"file-bmp"
end_define

begin_define
DECL|macro|PLUG_IN_ROLE
define|#
directive|define
name|PLUG_IN_ROLE
value|"gimp-file-bmp"
end_define

begin_define
DECL|macro|MAXCOLORS
define|#
directive|define
name|MAXCOLORS
value|256
end_define

begin_define
DECL|macro|BitSet (byte,bit)
define|#
directive|define
name|BitSet
parameter_list|(
name|byte
parameter_list|,
name|bit
parameter_list|)
value|(((byte)& (bit)) == (bit))
end_define

begin_define
DECL|macro|ReadOK (file,buffer,len)
define|#
directive|define
name|ReadOK
parameter_list|(
name|file
parameter_list|,
name|buffer
parameter_list|,
name|len
parameter_list|)
value|(fread(buffer, len, 1, file) != 0)
end_define

begin_define
DECL|macro|Write (file,buffer,len)
define|#
directive|define
name|Write
parameter_list|(
name|file
parameter_list|,
name|buffer
parameter_list|,
name|len
parameter_list|)
value|fwrite(buffer, len, 1, file)
end_define

begin_define
DECL|macro|WriteOK (file,buffer,len)
define|#
directive|define
name|WriteOK
parameter_list|(
name|file
parameter_list|,
name|buffer
parameter_list|,
name|len
parameter_list|)
value|(Write(buffer, len, file) != 0)
end_define

begin_typedef
typedef|typedef
struct|struct
DECL|struct|__anon2a33e1560108
block|{
DECL|member|zzMagic
name|gchar
name|zzMagic
index|[
literal|2
index|]
decl_stmt|;
comment|/* 00 "BM" */
DECL|member|bfSize
name|guint32
name|bfSize
decl_stmt|;
comment|/* 02 */
DECL|member|zzHotX
name|guint16
name|zzHotX
decl_stmt|;
comment|/* 06 */
DECL|member|zzHotY
name|guint16
name|zzHotY
decl_stmt|;
comment|/* 08 */
DECL|member|bfOffs
name|guint32
name|bfOffs
decl_stmt|;
comment|/* 0A */
DECL|member|biSize
name|guint32
name|biSize
decl_stmt|;
comment|/* 0E */
DECL|typedef|BitmapFileHead
block|}
name|BitmapFileHead
typedef|;
end_typedef

begin_typedef
typedef|typedef
struct|struct
DECL|struct|__anon2a33e1560208
block|{
DECL|member|biWidth
name|gint32
name|biWidth
decl_stmt|;
comment|/* 12 */
DECL|member|biHeight
name|gint32
name|biHeight
decl_stmt|;
comment|/* 16 */
DECL|member|biPlanes
name|guint16
name|biPlanes
decl_stmt|;
comment|/* 1A */
DECL|member|biBitCnt
name|guint16
name|biBitCnt
decl_stmt|;
comment|/* 1C */
DECL|member|biCompr
name|guint32
name|biCompr
decl_stmt|;
comment|/* 1E */
DECL|member|biSizeIm
name|guint32
name|biSizeIm
decl_stmt|;
comment|/* 22 */
DECL|member|biXPels
name|guint32
name|biXPels
decl_stmt|;
comment|/* 26 */
DECL|member|biYPels
name|guint32
name|biYPels
decl_stmt|;
comment|/* 2A */
DECL|member|biClrUsed
name|guint32
name|biClrUsed
decl_stmt|;
comment|/* 2E */
DECL|member|biClrImp
name|guint32
name|biClrImp
decl_stmt|;
comment|/* 32 */
DECL|member|masks
name|guint32
name|masks
index|[
literal|4
index|]
decl_stmt|;
comment|/* 36 */
DECL|typedef|BitmapHead
block|}
name|BitmapHead
typedef|;
end_typedef

begin_typedef
typedef|typedef
struct|struct
DECL|struct|__anon2a33e1560308
block|{
DECL|member|mask
name|guint32
name|mask
decl_stmt|;
DECL|member|shiftin
name|guint32
name|shiftin
decl_stmt|;
DECL|member|max_value
name|gfloat
name|max_value
decl_stmt|;
DECL|typedef|BitmapChannel
block|}
name|BitmapChannel
typedef|;
end_typedef

begin_endif
endif|#
directive|endif
end_endif

begin_comment
comment|/* __BMP_H__ */
end_comment

end_unit

