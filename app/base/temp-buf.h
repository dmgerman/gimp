begin_unit|revision:0.9.5;language:C;cregit-version:0.0.1
begin_comment
comment|/* GIMP - The GNU Image Manipulation Program  * Copyright (C) 1995 Spencer Kimball and Peter Mattis  *  * This program is free software; you can redistribute it and/or modify  * it under the terms of the GNU General Public License as published by  * the Free Software Foundation; either version 2 of the License, or  * (at your option) any later version.  *  * This program is distributed in the hope that it will be useful,  * but WITHOUT ANY WARRANTY; without even the implied warranty of  * MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the  * GNU General Public License for more details.  *  * You should have received a copy of the GNU General Public License  * along with this program; if not, write to the Free Software  * Foundation, Inc., 59 Temple Place - Suite 330, Boston, MA 02111-1307, USA.  */
end_comment

begin_ifndef
ifndef|#
directive|ifndef
name|__TEMP_BUF_H__
end_ifndef

begin_define
DECL|macro|__TEMP_BUF_H__
define|#
directive|define
name|__TEMP_BUF_H__
end_define

begin_struct
DECL|struct|_TempBuf
struct|struct
name|_TempBuf
block|{
DECL|member|bytes
name|gint
name|bytes
decl_stmt|;
comment|/*  the necessary info                             */
DECL|member|width
name|gint
name|width
decl_stmt|;
DECL|member|height
name|gint
name|height
decl_stmt|;
DECL|member|x
DECL|member|y
name|gint
name|x
decl_stmt|,
name|y
decl_stmt|;
comment|/*  origin of data source                          */
DECL|member|data
name|guchar
modifier|*
name|data
decl_stmt|;
comment|/*  The data buffer. Do never access this field                           directly, use temp_buf_data() instead !!       */
block|}
struct|;
end_struct

begin_comment
comment|/*  The temp buffer functions  */
end_comment

begin_function_decl
name|TempBuf
modifier|*
name|temp_buf_new
parameter_list|(
name|gint
name|width
parameter_list|,
name|gint
name|height
parameter_list|,
name|gint
name|bytes
parameter_list|,
name|gint
name|x
parameter_list|,
name|gint
name|y
parameter_list|,
specifier|const
name|guchar
modifier|*
name|color
parameter_list|)
function_decl|;
end_function_decl

begin_function_decl
name|TempBuf
modifier|*
name|temp_buf_new_check
parameter_list|(
name|gint
name|width
parameter_list|,
name|gint
name|height
parameter_list|,
name|GimpCheckType
name|check_type
parameter_list|,
name|GimpCheckSize
name|check_size
parameter_list|)
function_decl|;
end_function_decl

begin_function_decl
name|TempBuf
modifier|*
name|temp_buf_copy
parameter_list|(
name|TempBuf
modifier|*
name|src
parameter_list|,
name|TempBuf
modifier|*
name|dest
parameter_list|)
function_decl|;
end_function_decl

begin_function_decl
name|TempBuf
modifier|*
name|temp_buf_resize
parameter_list|(
name|TempBuf
modifier|*
name|buf
parameter_list|,
name|gint
name|bytes
parameter_list|,
name|gint
name|x
parameter_list|,
name|gint
name|y
parameter_list|,
name|gint
name|width
parameter_list|,
name|gint
name|height
parameter_list|)
function_decl|;
end_function_decl

begin_decl_stmt
name|TempBuf
modifier|*
name|temp_buf_scale
argument_list|(
name|TempBuf
operator|*
name|buf
argument_list|,
name|gint
name|width
argument_list|,
name|gint
name|height
argument_list|)
name|G_GNUC_WARN_UNUSED_RESULT
decl_stmt|;
end_decl_stmt

begin_function_decl
name|TempBuf
modifier|*
name|temp_buf_copy_area
parameter_list|(
name|TempBuf
modifier|*
name|src
parameter_list|,
name|TempBuf
modifier|*
name|dest
parameter_list|,
name|gint
name|x
parameter_list|,
name|gint
name|y
parameter_list|,
name|gint
name|width
parameter_list|,
name|gint
name|height
parameter_list|,
name|gint
name|dest_x
parameter_list|,
name|gint
name|dest_y
parameter_list|)
function_decl|;
end_function_decl

begin_function_decl
name|void
name|temp_buf_free
parameter_list|(
name|TempBuf
modifier|*
name|buf
parameter_list|)
function_decl|;
end_function_decl

begin_function_decl
name|guchar
modifier|*
name|temp_buf_data
parameter_list|(
name|TempBuf
modifier|*
name|buf
parameter_list|)
function_decl|;
end_function_decl

begin_function_decl
name|guchar
modifier|*
name|temp_buf_data_clear
parameter_list|(
name|TempBuf
modifier|*
name|buf
parameter_list|)
function_decl|;
end_function_decl

begin_function_decl
name|gsize
name|temp_buf_get_memsize
parameter_list|(
name|TempBuf
modifier|*
name|buf
parameter_list|)
function_decl|;
end_function_decl

begin_comment
comment|/* The mask buffer functions  */
end_comment

begin_function_decl
name|MaskBuf
modifier|*
name|mask_buf_new
parameter_list|(
name|gint
name|width
parameter_list|,
name|gint
name|height
parameter_list|,
name|gint
name|bpp
parameter_list|)
function_decl|;
end_function_decl

begin_function_decl
name|void
name|mask_buf_free
parameter_list|(
name|MaskBuf
modifier|*
name|mask_buf
parameter_list|)
function_decl|;
end_function_decl

begin_function_decl
name|guchar
modifier|*
name|mask_buf_data
parameter_list|(
name|MaskBuf
modifier|*
name|mask_buf
parameter_list|)
function_decl|;
end_function_decl

begin_function_decl
name|guchar
modifier|*
name|mask_buf_data_clear
parameter_list|(
name|MaskBuf
modifier|*
name|mask_buf
parameter_list|)
function_decl|;
end_function_decl

begin_endif
endif|#
directive|endif
end_endif

begin_comment
comment|/*  __TEMP_BUF_H__  */
end_comment

end_unit

