begin_unit|revision:0.9.5;language:C;cregit-version:0.0.1
begin_comment
comment|/* The GIMP -- an image manipulation program  * Copyright (C) 1995 Spencer Kimball and Peter Mattis  *  * This program is free software; you can redistribute it and/or modify  * it under the terms of the GNU General Public License as published by  * the Free Software Foundation; either version 2 of the License, or  * (at your option) any later version.  *  * This program is distributed in the hope that it will be useful,  * but WITHOUT ANY WARRANTY; without even the implied warranty of  * MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the  * GNU General Public License for more details.  *  * You should have received a copy of the GNU General Public License  * along with this program; if not, write to the Free Software  * Foundation, Inc., 59 Temple Place - Suite 330, Boston, MA 02111-1307, USA.  */
end_comment

begin_ifndef
ifndef|#
directive|ifndef
name|__SESSION_H__
end_ifndef

begin_define
DECL|macro|__SESSION_H__
define|#
directive|define
name|__SESSION_H__
end_define

begin_include
include|#
directive|include
file|<glib.h>
end_include

begin_comment
comment|/* Structures */
end_comment

begin_typedef
DECL|typedef|SessionGeometry
typedef|typedef
name|struct
name|_SessionGeometry
name|SessionGeometry
typedef|;
end_typedef

begin_struct
DECL|struct|_SessionGeometry
struct|struct
name|_SessionGeometry
block|{
DECL|member|name
name|char
name|name
index|[
literal|16
index|]
decl_stmt|;
DECL|member|x
name|int
name|x
decl_stmt|;
DECL|member|y
name|int
name|y
decl_stmt|;
DECL|member|width
name|int
name|width
decl_stmt|;
DECL|member|height
name|int
name|height
decl_stmt|;
block|}
struct|;
end_struct

begin_comment
comment|/*  global session variables  */
end_comment

begin_decl_stmt
specifier|extern
name|SessionGeometry
name|toolbox_geometry
decl_stmt|;
end_decl_stmt

begin_decl_stmt
specifier|extern
name|SessionGeometry
name|lc_dialog_geometry
decl_stmt|;
end_decl_stmt

begin_decl_stmt
specifier|extern
name|SessionGeometry
name|info_dialog_geometry
decl_stmt|;
end_decl_stmt

begin_decl_stmt
specifier|extern
name|SessionGeometry
name|tool_options_geometry
decl_stmt|;
end_decl_stmt

begin_decl_stmt
specifier|extern
name|SessionGeometry
name|palette_geometry
decl_stmt|;
end_decl_stmt

begin_decl_stmt
specifier|extern
name|SessionGeometry
name|brush_select_geometry
decl_stmt|;
end_decl_stmt

begin_decl_stmt
specifier|extern
name|SessionGeometry
name|pattern_select_geometry
decl_stmt|;
end_decl_stmt

begin_decl_stmt
specifier|extern
name|SessionGeometry
name|gradient_editor_geometry
decl_stmt|;
end_decl_stmt

begin_decl_stmt
specifier|extern
name|GList
modifier|*
name|session_geometry_updates
decl_stmt|;
end_decl_stmt

begin_comment
comment|/* This list holds all geometries 					    that should be written to the 					    sessionrc on exit.             */
end_comment

begin_comment
comment|/*  function prototypes  */
end_comment

begin_function_decl
name|void
name|session_get_window_geometry
parameter_list|(
name|GtkWidget
modifier|*
name|window
parameter_list|,
name|SessionGeometry
modifier|*
name|geometry
parameter_list|)
function_decl|;
end_function_decl

begin_function_decl
name|void
name|session_set_window_geometry
parameter_list|(
name|GtkWidget
modifier|*
name|window
parameter_list|,
name|SessionGeometry
modifier|*
name|geometry
parameter_list|,
name|int
name|set_size
parameter_list|)
function_decl|;
end_function_decl

begin_function_decl
name|void
name|session_init
parameter_list|(
name|void
parameter_list|)
function_decl|;
end_function_decl

begin_function_decl
name|void
name|save_sessionrc
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
comment|/*  __SESSION_H__  */
end_comment

end_unit

