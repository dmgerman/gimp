begin_unit|revision:0.9.5;language:C;cregit-version:0.0.1
begin_comment
comment|/* The GIMP -- an image manipulation program  * Copyright (C) 1995 Spencer Kimball and Peter Mattis  *  * This program is free software; you can redistribute it and/or modify  * it under the terms of the GNU General Public License as published by  * the Free Software Foundation; either version 2 of the License, or  * (at your option) any later version.  *  * This program is distributed in the hope that it will be useful,  * but WITHOUT ANY WARRANTY; without even the implied warranty of  * MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the  * GNU General Public License for more details.  *  * You should have received a copy of the GNU General Public License  * along with this program; if not, write to the Free Software  * Foundation, Inc., 59 Temple Place - Suite 330, Boston, MA 02111-1307, USA.  */
end_comment

begin_ifndef
ifndef|#
directive|ifndef
name|__PIXMAPBRUSH_H__
end_ifndef

begin_define
DECL|macro|__PIXMAPBRUSH_H__
define|#
directive|define
name|__PIXMAPBRUSH_H__
end_define

begin_include
include|#
directive|include
file|"tools.h"
end_include

begin_include
include|#
directive|include
file|"paint_core.h"
end_include

begin_include
include|#
directive|include
file|"procedural_db.h"
end_include

begin_include
include|#
directive|include
file|"gimpbrush.h"
end_include

begin_include
include|#
directive|include
file|"gimpbrushpixmap.h"
end_include

begin_include
include|#
directive|include
file|"temp_buf.h"
end_include

begin_function_decl
name|void
modifier|*
name|pixmap_paint_func
parameter_list|(
name|PaintCore
modifier|*
parameter_list|,
name|GimpDrawable
modifier|*
parameter_list|,
name|int
parameter_list|)
function_decl|;
end_function_decl

begin_function_decl
name|Tool
modifier|*
name|tools_new_pixmapbrush
parameter_list|(
name|void
parameter_list|)
function_decl|;
end_function_decl

begin_function_decl
name|void
name|tools_free_pixmapbrush
parameter_list|(
name|Tool
modifier|*
parameter_list|)
function_decl|;
end_function_decl

begin_function_decl
name|void
name|paint_line_pixmap_mask
parameter_list|(
name|GImage
modifier|*
name|dest
parameter_list|,
name|GimpDrawable
modifier|*
name|drawable
parameter_list|,
name|GimpBrushPixmap
modifier|*
name|brush
parameter_list|,
name|unsigned
name|char
modifier|*
name|d
parameter_list|,
name|int
name|x
parameter_list|,
name|int
name|offset_x
parameter_list|,
name|int
name|y
parameter_list|,
name|int
name|offset_y
parameter_list|,
name|int
name|bytes
parameter_list|,
name|int
name|width
parameter_list|)
function_decl|;
end_function_decl

begin_function_decl
name|void
name|color_area_with_pixmap
parameter_list|(
name|GImage
modifier|*
name|dest
parameter_list|,
name|GimpDrawable
modifier|*
name|drawable
parameter_list|,
name|TempBuf
modifier|*
name|area
parameter_list|,
name|GimpBrush
modifier|*
name|brush
parameter_list|)
function_decl|;
end_function_decl

begin_comment
comment|/*  Procedure definition and marshalling function  */
end_comment

begin_comment
comment|/* extern ProcRecord pixmapbrush_proc; */
end_comment

begin_comment
comment|/* extern ProcRecord pixmapbrush_extended_proc; */
end_comment

begin_comment
comment|/* extern ProcRecord pixmapbrush_extended_gradient_proc; */
end_comment

begin_endif
endif|#
directive|endif
end_endif

begin_comment
comment|/*  __PIXMAPBRUSH_H__  */
end_comment

end_unit

