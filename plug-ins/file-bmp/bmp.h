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

begin_function_decl
name|gint32
name|ReadBMP
parameter_list|(
specifier|const
name|gchar
modifier|*
name|filename
parameter_list|,
name|GError
modifier|*
modifier|*
name|error
parameter_list|)
function_decl|;
end_function_decl

begin_function_decl
name|GimpPDBStatusType
name|WriteBMP
parameter_list|(
specifier|const
name|gchar
modifier|*
name|filename
parameter_list|,
name|gint32
name|image
parameter_list|,
name|gint32
name|drawable_ID
parameter_list|,
name|GError
modifier|*
modifier|*
name|error
parameter_list|)
function_decl|;
end_function_decl

begin_decl_stmt
specifier|extern
name|gboolean
name|interactive
decl_stmt|;
end_decl_stmt

begin_decl_stmt
specifier|extern
name|gboolean
name|lastvals
decl_stmt|;
end_decl_stmt

begin_decl_stmt
specifier|extern
specifier|const
name|gchar
modifier|*
name|filename
decl_stmt|;
end_decl_stmt

begin_struct
DECL|struct|Bitmap_File_Head_Struct
specifier|extern
struct|struct
name|Bitmap_File_Head_Struct
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
name|gulong
name|bfSize
decl_stmt|;
comment|/* 02 */
DECL|member|zzHotX
name|gushort
name|zzHotX
decl_stmt|;
comment|/* 06 */
DECL|member|zzHotY
name|gushort
name|zzHotY
decl_stmt|;
comment|/* 08 */
DECL|member|bfOffs
name|gulong
name|bfOffs
decl_stmt|;
comment|/* 0A */
DECL|member|biSize
name|gulong
name|biSize
decl_stmt|;
comment|/* 0E */
DECL|variable|Bitmap_File_Head
block|}
name|Bitmap_File_Head
struct|;
end_struct

begin_struct
DECL|struct|Bitmap_Head_Struct
specifier|extern
struct|struct
name|Bitmap_Head_Struct
block|{
DECL|member|biWidth
name|glong
name|biWidth
decl_stmt|;
comment|/* 12 */
DECL|member|biHeight
name|glong
name|biHeight
decl_stmt|;
comment|/* 16 */
DECL|member|biPlanes
name|gushort
name|biPlanes
decl_stmt|;
comment|/* 1A */
DECL|member|biBitCnt
name|gushort
name|biBitCnt
decl_stmt|;
comment|/* 1C */
DECL|member|biCompr
name|gulong
name|biCompr
decl_stmt|;
comment|/* 1E */
DECL|member|biSizeIm
name|gulong
name|biSizeIm
decl_stmt|;
comment|/* 22 */
DECL|member|biXPels
name|gulong
name|biXPels
decl_stmt|;
comment|/* 26 */
DECL|member|biYPels
name|gulong
name|biYPels
decl_stmt|;
comment|/* 2A */
DECL|member|biClrUsed
name|gulong
name|biClrUsed
decl_stmt|;
comment|/* 2E */
DECL|member|biClrImp
name|gulong
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
DECL|variable|Bitmap_Head
block|}
name|Bitmap_Head
struct|;
end_struct

begin_typedef
DECL|struct|_Bitmap_Channel
typedef|typedef
struct|struct
name|_Bitmap_Channel
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
DECL|typedef|Bitmap_Channel
block|}
name|Bitmap_Channel
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

