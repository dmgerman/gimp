begin_unit|revision:0.9.5;language:C;cregit-version:0.0.1
begin_comment
comment|/* The GIMP -- an image manipulation program  * Copyright (C) 1995 Spencer Kimball and Peter Mattis  * Copyright (C) 1999 Adrian Likins and Tor Lillqvist  *  * This program is free software; you can redistribute it and/or modify  * it under the terms of the GNU General Public License as published by  * the Free Software Foundation; either version 2 of the License, or  * (at your option) any later version.  *  * This program is distributed in the hope that it will be useful,  * but WITHOUT ANY WARRANTY; without even the implied warranty of  * MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the  * GNU General Public License for more details.  *  * You should have received a copy of the GNU General Public License  * along with this program; if not, write to the Free Software  * Foundation, Inc., 59 Temple Place - Suite 330, Boston, MA 02111-1307, USA.  */
end_comment

begin_ifndef
ifndef|#
directive|ifndef
name|__GIMPBRUSHPIPE_H__
end_ifndef

begin_define
DECL|macro|__GIMPBRUSHPIPE_H__
define|#
directive|define
name|__GIMPBRUSHPIPE_H__
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
file|"gimpbrush.h"
end_include

begin_include
include|#
directive|include
file|"temp_buf.h"
end_include

begin_typedef
DECL|typedef|GimpBrushPixmap
typedef|typedef
name|struct
name|_GimpBrushPixmap
name|GimpBrushPixmap
typedef|;
end_typedef

begin_typedef
DECL|typedef|GimpBrushPipe
typedef|typedef
name|struct
name|_GimpBrushPipe
name|GimpBrushPipe
typedef|;
end_typedef

begin_define
DECL|macro|GIMP_TYPE_BRUSH_PIXMAP
define|#
directive|define
name|GIMP_TYPE_BRUSH_PIXMAP
value|(gimp_brush_pixmap_get_type ())
end_define

begin_define
DECL|macro|GIMP_BRUSH_PIXMAP (obj)
define|#
directive|define
name|GIMP_BRUSH_PIXMAP
parameter_list|(
name|obj
parameter_list|)
value|(GIMP_CHECK_CAST ((obj), GIMP_TYPE_BRUSH_PIXMAP, GimpBrushPixmap))
end_define

begin_define
DECL|macro|GIMP_IS_BRUSH_PIXMAP (obj)
define|#
directive|define
name|GIMP_IS_BRUSH_PIXMAP
parameter_list|(
name|obj
parameter_list|)
value|(GIMP_CHECK_TYPE ((obj), GIMP_TYPE_BRUSH_PIXMAP))
end_define

begin_define
DECL|macro|GIMP_TYPE_BRUSH_PIPE
define|#
directive|define
name|GIMP_TYPE_BRUSH_PIPE
value|(gimp_brush_pipe_get_type ())
end_define

begin_define
DECL|macro|GIMP_BRUSH_PIPE (obj)
define|#
directive|define
name|GIMP_BRUSH_PIPE
parameter_list|(
name|obj
parameter_list|)
value|(GIMP_CHECK_CAST ((obj), GIMP_TYPE_BRUSH_PIPE, GimpBrushPipe))
end_define

begin_define
DECL|macro|GIMP_IS_BRUSH_PIPE (obj)
define|#
directive|define
name|GIMP_IS_BRUSH_PIPE
parameter_list|(
name|obj
parameter_list|)
value|(GIMP_CHECK_TYPE ((obj), GIMP_TYPE_BRUSH_PIPE))
end_define

begin_function_decl
name|GtkType
name|gimp_brush_pixmap_get_type
parameter_list|(
name|void
parameter_list|)
function_decl|;
end_function_decl

begin_function_decl
name|GtkType
name|gimp_brush_pipe_get_type
parameter_list|(
name|void
parameter_list|)
function_decl|;
end_function_decl

begin_function_decl
name|GimpBrushPipe
modifier|*
name|gimp_brush_pipe_load
parameter_list|(
name|char
modifier|*
name|filename
parameter_list|)
function_decl|;
end_function_decl

begin_function_decl
name|GimpBrushPipe
modifier|*
name|gimp_brush_pixmap_load
parameter_list|(
name|char
modifier|*
name|filename
parameter_list|)
function_decl|;
end_function_decl

begin_function_decl
name|TempBuf
modifier|*
name|gimp_brush_pixmap_pixmap
parameter_list|(
name|GimpBrushPixmap
modifier|*
parameter_list|)
function_decl|;
end_function_decl

begin_function_decl
name|void
name|color_area_with_pixmap
parameter_list|(
name|PaintCore
modifier|*
name|paint_core
parameter_list|,
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
parameter_list|)
function_decl|;
end_function_decl

begin_endif
endif|#
directive|endif
end_endif

begin_comment
comment|/* __GIMPBRUSHPIPE_H__ */
end_comment

end_unit

