begin_unit|revision:0.9.5;language:C;cregit-version:0.0.1
begin_comment
comment|/* The GIMP -- an image manipulation program  * Copyright (C) 1995 Spencer Kimball and Peter Mattis  *  * This program is free software; you can redistribute it and/or modify  * it under the terms of the GNU General Public License as published by  * the Free Software Foundation; either version 2 of the License, or  * (at your option) any later version.  *  * This program is distributed in the hope that it will be useful,  * but WITHOUT ANY WARRANTY; without even the implied warranty of  * MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the  * GNU General Public License for more details.  *  * You should have received a copy of the GNU General Public License  * along with this program; if not, write to the Free Software  * Foundation, Inc., 675 Mass Ave, Cambridge, MA 02139, USA.  */
end_comment

begin_ifndef
ifndef|#
directive|ifndef
name|__BRUSHES_H__
end_ifndef

begin_define
DECL|macro|__BRUSHES_H__
define|#
directive|define
name|__BRUSHES_H__
end_define

begin_include
include|#
directive|include
file|<glib.h>
end_include

begin_include
include|#
directive|include
file|"procedural_db.h"
end_include

begin_include
include|#
directive|include
file|"temp_buf.h"
end_include

begin_typedef
DECL|typedef|GBrush
DECL|typedef|GBrushP
typedef|typedef
name|struct
name|_GBrush
name|GBrush
typedef|,
modifier|*
name|GBrushP
typedef|;
end_typedef

begin_struct
DECL|struct|_GBrush
struct|struct
name|_GBrush
block|{
DECL|member|filename
name|char
modifier|*
name|filename
decl_stmt|;
comment|/*  actual filename--brush's location on disk  */
DECL|member|name
name|char
modifier|*
name|name
decl_stmt|;
comment|/*  brush's name--for brush selection dialog   */
DECL|member|spacing
name|int
name|spacing
decl_stmt|;
comment|/*  brush's spacing                            */
DECL|member|index
name|int
name|index
decl_stmt|;
comment|/*  brush's index...                           */
DECL|member|mask
name|TempBuf
modifier|*
name|mask
decl_stmt|;
comment|/*  the actual mask...                         */
block|}
struct|;
end_struct

begin_comment
comment|/*  global variables  */
end_comment

begin_decl_stmt
specifier|extern
name|GSList
modifier|*
name|brush_list
decl_stmt|;
end_decl_stmt

begin_decl_stmt
specifier|extern
name|int
name|num_brushes
decl_stmt|;
end_decl_stmt

begin_comment
comment|/*  function declarations  */
end_comment

begin_function_decl
name|void
name|brushes_init
parameter_list|(
name|void
parameter_list|)
function_decl|;
end_function_decl

begin_function_decl
name|void
name|brushes_free
parameter_list|(
name|void
parameter_list|)
function_decl|;
end_function_decl

begin_function_decl
name|void
name|brush_select_dialog_free
parameter_list|(
name|void
parameter_list|)
function_decl|;
end_function_decl

begin_function_decl
name|void
name|select_brush
parameter_list|(
name|GBrushP
parameter_list|)
function_decl|;
end_function_decl

begin_function_decl
name|GBrushP
name|get_brush_by_index
parameter_list|(
name|int
parameter_list|)
function_decl|;
end_function_decl

begin_function_decl
name|GBrushP
name|get_active_brush
parameter_list|(
name|void
parameter_list|)
function_decl|;
end_function_decl

begin_function_decl
name|void
name|create_brush_dialog
parameter_list|(
name|void
parameter_list|)
function_decl|;
end_function_decl

begin_comment
comment|/*  access functions  */
end_comment

begin_function_decl
name|double
name|get_brush_opacity
parameter_list|(
name|void
parameter_list|)
function_decl|;
end_function_decl

begin_function_decl
name|int
name|get_brush_spacing
parameter_list|(
name|void
parameter_list|)
function_decl|;
end_function_decl

begin_function_decl
name|int
name|get_brush_paint_mode
parameter_list|(
name|void
parameter_list|)
function_decl|;
end_function_decl

begin_function_decl
name|void
name|set_brush_opacity
parameter_list|(
name|double
parameter_list|)
function_decl|;
end_function_decl

begin_function_decl
name|void
name|set_brush_spacing
parameter_list|(
name|int
parameter_list|)
function_decl|;
end_function_decl

begin_function_decl
name|void
name|set_brush_paint_mode
parameter_list|(
name|int
parameter_list|)
function_decl|;
end_function_decl

begin_comment
comment|/*  Brush procedures  */
end_comment

begin_decl_stmt
specifier|extern
name|ProcRecord
name|brushes_get_brush_proc
decl_stmt|;
end_decl_stmt

begin_decl_stmt
specifier|extern
name|ProcRecord
name|brushes_set_brush_proc
decl_stmt|;
end_decl_stmt

begin_decl_stmt
specifier|extern
name|ProcRecord
name|brushes_get_opacity_proc
decl_stmt|;
end_decl_stmt

begin_decl_stmt
specifier|extern
name|ProcRecord
name|brushes_set_opacity_proc
decl_stmt|;
end_decl_stmt

begin_decl_stmt
specifier|extern
name|ProcRecord
name|brushes_get_spacing_proc
decl_stmt|;
end_decl_stmt

begin_decl_stmt
specifier|extern
name|ProcRecord
name|brushes_set_spacing_proc
decl_stmt|;
end_decl_stmt

begin_decl_stmt
specifier|extern
name|ProcRecord
name|brushes_get_paint_mode_proc
decl_stmt|;
end_decl_stmt

begin_decl_stmt
specifier|extern
name|ProcRecord
name|brushes_set_paint_mode_proc
decl_stmt|;
end_decl_stmt

begin_decl_stmt
specifier|extern
name|ProcRecord
name|brushes_list_proc
decl_stmt|;
end_decl_stmt

begin_decl_stmt
specifier|extern
name|ProcRecord
name|brushes_refresh_brush_proc
decl_stmt|;
end_decl_stmt

begin_endif
endif|#
directive|endif
end_endif

begin_comment
comment|/*  __BRUSHES_H__  */
end_comment

end_unit

