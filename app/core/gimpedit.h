begin_unit|revision:0.9.5;language:C;cregit-version:0.0.1
begin_comment
comment|/* The GIMP -- an image manipulation program  * Copyright (C) 1995 Spencer Kimball and Peter Mattis  *  * This program is free software; you can redistribute it and/or modify  * it under the terms of the GNU General Public License as published by  * the Free Software Foundation; either version 2 of the License, or  * (at your option) any later version.  *  * This program is distributed in the hope that it will be useful,  * but WITHOUT ANY WARRANTY; without even the implied warranty of  * MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the  * GNU General Public License for more details.  *  * You should have received a copy of the GNU General Public License  * along with this program; if not, write to the Free Software  * Foundation, Inc., 59 Temple Place - Suite 330, Boston, MA 02111-1307, USA.  */
end_comment

begin_ifndef
ifndef|#
directive|ifndef
name|__GLOBAL_EDIT_H__
end_ifndef

begin_define
DECL|macro|__GLOBAL_EDIT_H__
define|#
directive|define
name|__GLOBAL_EDIT_H__
end_define

begin_include
include|#
directive|include
file|"gimage.h"
end_include

begin_function_decl
name|TileManager
modifier|*
name|crop_buffer
parameter_list|(
name|TileManager
modifier|*
name|tiles
parameter_list|,
name|gint
name|border
parameter_list|)
function_decl|;
end_function_decl

begin_function_decl
name|TileManager
modifier|*
name|edit_cut
parameter_list|(
name|GImage
modifier|*
name|gimage
parameter_list|,
name|GimpDrawable
modifier|*
name|drawable
parameter_list|)
function_decl|;
end_function_decl

begin_function_decl
name|TileManager
modifier|*
name|edit_copy
parameter_list|(
name|GImage
modifier|*
name|gimage
parameter_list|,
name|GimpDrawable
modifier|*
name|drawable
parameter_list|)
function_decl|;
end_function_decl

begin_function_decl
name|GimpLayer
modifier|*
name|edit_paste
parameter_list|(
name|GImage
modifier|*
name|gimage
parameter_list|,
name|GimpDrawable
modifier|*
name|drawable
parameter_list|,
name|TileManager
modifier|*
name|paste
parameter_list|,
name|gboolean
name|paste_into
parameter_list|)
function_decl|;
end_function_decl

begin_function_decl
name|gboolean
name|edit_paste_as_new
parameter_list|(
name|GImage
modifier|*
name|gimage
parameter_list|,
name|TileManager
modifier|*
name|tiles
parameter_list|)
function_decl|;
end_function_decl

begin_function_decl
name|gboolean
name|edit_clear
parameter_list|(
name|GImage
modifier|*
name|gimage
parameter_list|,
name|GimpDrawable
modifier|*
name|drawable
parameter_list|)
function_decl|;
end_function_decl

begin_function_decl
name|gboolean
name|edit_fill
parameter_list|(
name|GImage
modifier|*
name|gimage
parameter_list|,
name|GimpDrawable
modifier|*
name|drawable
parameter_list|,
name|GimpFillType
name|fill_type
parameter_list|)
function_decl|;
end_function_decl

begin_function_decl
name|gboolean
name|global_edit_cut
parameter_list|(
name|GDisplay
modifier|*
name|gdisp
parameter_list|)
function_decl|;
end_function_decl

begin_function_decl
name|gboolean
name|global_edit_copy
parameter_list|(
name|GDisplay
modifier|*
name|gdisp
parameter_list|)
function_decl|;
end_function_decl

begin_function_decl
name|gboolean
name|global_edit_paste
parameter_list|(
name|GDisplay
modifier|*
name|gdisp
parameter_list|,
name|gboolean
name|paste_into
parameter_list|)
function_decl|;
end_function_decl

begin_function_decl
name|gboolean
name|global_edit_paste_as_new
parameter_list|(
name|GDisplay
modifier|*
name|gdisp
parameter_list|)
function_decl|;
end_function_decl

begin_function_decl
name|void
name|global_edit_free
parameter_list|(
name|void
parameter_list|)
function_decl|;
end_function_decl

begin_function_decl
name|gboolean
name|named_edit_cut
parameter_list|(
name|GDisplay
modifier|*
name|gdisp
parameter_list|)
function_decl|;
end_function_decl

begin_function_decl
name|gboolean
name|named_edit_copy
parameter_list|(
name|GDisplay
modifier|*
name|gdisp
parameter_list|)
function_decl|;
end_function_decl

begin_function_decl
name|gboolean
name|named_edit_paste
parameter_list|(
name|GDisplay
modifier|*
name|gdisp
parameter_list|)
function_decl|;
end_function_decl

begin_function_decl
name|void
name|named_buffers_free
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
comment|/*  __GLOBAL_EDIT_H__  */
end_comment

end_unit

