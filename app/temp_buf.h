begin_unit|revision:0.9.5;language:C;cregit-version:0.0.1
begin_comment
comment|/* The GIMP -- an image manipulation program  * Copyright (C) 1995 Spencer Kimball and Peter Mattis  *  * This program is free software; you can redistribute it and/or modify  * it under the terms of the GNU General Public License as published by  * the Free Software Foundation; either version 2 of the License, or  * (at your option) any later version.  *  * This program is distributed in the hope that it will be useful,  * but WITHOUT ANY WARRANTY; without even the implied warranty of  * MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the  * GNU General Public License for more details.  *  * You should have received a copy of the GNU General Public License  * along with this program; if not, write to the Free Software  * Foundation, Inc., 59 Temple Place - Suite 330, Boston, MA 02111-1307, USA.  */
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

begin_typedef
DECL|typedef|TempBuf
typedef|typedef
name|struct
name|_TempBuf
name|TempBuf
typedef|;
end_typedef

begin_typedef
DECL|typedef|MaskBuf
typedef|typedef
name|struct
name|_TempBuf
name|MaskBuf
typedef|;
end_typedef

begin_struct
DECL|struct|_TempBuf
struct|struct
name|_TempBuf
block|{
DECL|member|bytes
name|gint
name|bytes
decl_stmt|;
comment|/*  The necessary info  */
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
comment|/*  origin of data source  */
DECL|member|swapped
name|gboolean
name|swapped
decl_stmt|;
comment|/*  flag indicating whether buf is cached to disk  */
DECL|member|filename
name|gchar
modifier|*
name|filename
decl_stmt|;
comment|/*  filename of cached information  */
DECL|member|data
name|guchar
modifier|*
name|data
decl_stmt|;
comment|/*  The data buffer     */
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
parameter_list|,
name|gint
parameter_list|,
name|gint
parameter_list|,
name|gint
parameter_list|,
name|gint
parameter_list|,
name|guchar
modifier|*
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
parameter_list|,
name|TempBuf
modifier|*
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
parameter_list|,
name|gint
parameter_list|,
name|gint
parameter_list|,
name|gint
parameter_list|,
name|gint
parameter_list|,
name|gint
parameter_list|)
function_decl|;
end_function_decl

begin_function_decl
name|TempBuf
modifier|*
name|temp_buf_copy_area
parameter_list|(
name|TempBuf
modifier|*
parameter_list|,
name|TempBuf
modifier|*
parameter_list|,
name|gint
parameter_list|,
name|gint
parameter_list|,
name|gint
parameter_list|,
name|gint
parameter_list|,
name|gint
parameter_list|)
function_decl|;
end_function_decl

begin_function_decl
name|void
name|temp_buf_free
parameter_list|(
name|TempBuf
modifier|*
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
parameter_list|,
name|gint
parameter_list|)
function_decl|;
end_function_decl

begin_function_decl
name|void
name|mask_buf_free
parameter_list|(
name|MaskBuf
modifier|*
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
parameter_list|)
function_decl|;
end_function_decl

begin_comment
comment|/*  The disk caching functions  */
end_comment

begin_function_decl
name|void
name|temp_buf_swap
parameter_list|(
name|TempBuf
modifier|*
parameter_list|)
function_decl|;
end_function_decl

begin_function_decl
name|void
name|temp_buf_unswap
parameter_list|(
name|TempBuf
modifier|*
parameter_list|)
function_decl|;
end_function_decl

begin_function_decl
name|void
name|temp_buf_swap_free
parameter_list|(
name|TempBuf
modifier|*
parameter_list|)
function_decl|;
end_function_decl

begin_comment
comment|/*  Called by app_procs:exit() to free up the cached undo buffer  */
end_comment

begin_function_decl
name|void
name|swapping_free
parameter_list|(
name|void
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

