begin_unit|revision:0.9.5;language:C;cregit-version:0.0.1
begin_comment
comment|/* The GIMP -- an image manipulation program  * Copyright (C) 1995 Spencer Kimball and Peter Mattis  *  * This program is free software; you can redistribute it and/or modify  * it under the terms of the GNU General Public License as published by  * the Free Software Foundation; either version 2 of the License, or  * (at your option) any later version.  *  * This program is distributed in the hope that it will be useful,  * but WITHOUT ANY WARRANTY; without even the implied warranty of  * MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the  * GNU General Public License for more details.  *  * You should have received a copy of the GNU General Public License  * along with this program; if not, write to the Free Software  * Foundation, Inc., 59 Temple Place - Suite 330, Boston, MA 02111-1307, USA.  */
end_comment

begin_ifndef
ifndef|#
directive|ifndef
name|__GIMP_BRUSH_LIST_H__
end_ifndef

begin_define
DECL|macro|__GIMP_BRUSH_LIST_H__
define|#
directive|define
name|__GIMP_BRUSH_LIST_H__
end_define

begin_include
include|#
directive|include
file|"gimpbrush.h"
end_include

begin_define
DECL|macro|GIMP_TYPE_BRUSH_LIST
define|#
directive|define
name|GIMP_TYPE_BRUSH_LIST
value|(gimp_brush_list_get_type ())
end_define

begin_define
DECL|macro|GIMP_BRUSH_LIST (obj)
define|#
directive|define
name|GIMP_BRUSH_LIST
parameter_list|(
name|obj
parameter_list|)
value|(GTK_CHECK_CAST ((obj), GIMP_TYPE_BRUSH_LIST, GimpBrushList))
end_define

begin_define
DECL|macro|GIMP_IS_BRUSH_LIST (obj)
define|#
directive|define
name|GIMP_IS_BRUSH_LIST
parameter_list|(
name|obj
parameter_list|)
value|(GTK_CHECK_TYPE ((obj), GIMP_TYPE_BRUSH_LIST))
end_define

begin_comment
comment|/*  global variables  */
end_comment

begin_decl_stmt
specifier|extern
name|GimpBrushList
modifier|*
name|brush_list
decl_stmt|;
end_decl_stmt

begin_comment
comment|/*  function declarations  */
end_comment

begin_function_decl
name|GimpBrushList
modifier|*
name|gimp_brush_list_new
parameter_list|(
name|void
parameter_list|)
function_decl|;
end_function_decl

begin_function_decl
name|GtkType
name|gimp_brush_list_get_type
parameter_list|(
name|void
parameter_list|)
function_decl|;
end_function_decl

begin_function_decl
name|gint
name|gimp_brush_list_length
parameter_list|(
name|GimpBrushList
modifier|*
name|list
parameter_list|)
function_decl|;
end_function_decl

begin_function_decl
name|void
name|gimp_brush_list_add
parameter_list|(
name|GimpBrushList
modifier|*
name|list
parameter_list|,
name|GimpBrush
modifier|*
name|brush
parameter_list|)
function_decl|;
end_function_decl

begin_function_decl
name|void
name|gimp_brush_list_remove
parameter_list|(
name|GimpBrushList
modifier|*
name|list
parameter_list|,
name|GimpBrush
modifier|*
name|brush
parameter_list|)
function_decl|;
end_function_decl

begin_function_decl
name|GimpBrush
modifier|*
name|gimp_brush_list_get_brush
parameter_list|(
name|GimpBrushList
modifier|*
name|list
parameter_list|,
name|gchar
modifier|*
name|name
parameter_list|)
function_decl|;
end_function_decl

begin_function_decl
name|GimpBrush
modifier|*
name|gimp_brush_list_get_brush_by_index
parameter_list|(
name|GimpBrushList
modifier|*
name|list
parameter_list|,
name|gint
name|index
parameter_list|)
function_decl|;
end_function_decl

begin_function_decl
name|gint
name|gimp_brush_list_get_brush_index
parameter_list|(
name|GimpBrushList
modifier|*
name|list
parameter_list|,
name|GimpBrush
modifier|*
name|brush
parameter_list|)
function_decl|;
end_function_decl

begin_function_decl
name|void
name|brushes_init
parameter_list|(
name|gboolean
name|no_data
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
name|GimpBrush
modifier|*
name|brushes_get_standard_brush
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
comment|/*  __GIMP_BRUSH_LIST_H__  */
end_comment

end_unit

