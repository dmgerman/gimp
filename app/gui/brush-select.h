begin_unit|revision:0.9.5;language:C;cregit-version:0.0.1
begin_comment
comment|/* The GIMP -- an image manipulation program  * Copyright (C) 1995 Spencer Kimball and Peter Mattis  *  * This program is free software; you can redistribute it and/or modify  * it under the terms of the GNU General Public License as published by  * the Free Software Foundation; either version 2 of the License, or  * (at your option) any later version.  *  * This program is distributed in the hope that it will be useful,  * but WITHOUT ANY WARRANTY; without even the implied warranty of  * MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the  * GNU General Public License for more details.  *  * You should have received a copy of the GNU General Public License  * along with this program; if not, write to the Free Software  * Foundation, Inc., 59 Temple Place - Suite 330, Boston, MA 02111-1307, USA.  */
end_comment

begin_ifndef
ifndef|#
directive|ifndef
name|__BRUSH_SELECT_H__
end_ifndef

begin_define
DECL|macro|__BRUSH_SELECT_H__
define|#
directive|define
name|__BRUSH_SELECT_H__
end_define

begin_include
include|#
directive|include
file|"buildmenu.h"
end_include

begin_typedef
DECL|typedef|_BrushSelect
DECL|typedef|BrushSelectP
typedef|typedef
name|struct
name|_BrushSelect
name|_BrushSelect
typedef|,
modifier|*
name|BrushSelectP
typedef|;
end_typedef

begin_struct
DECL|struct|_BrushSelect
struct|struct
name|_BrushSelect
block|{
DECL|member|shell
name|GtkWidget
modifier|*
name|shell
decl_stmt|;
DECL|member|frame
name|GtkWidget
modifier|*
name|frame
decl_stmt|;
DECL|member|preview
name|GtkWidget
modifier|*
name|preview
decl_stmt|;
DECL|member|brush_name
name|GtkWidget
modifier|*
name|brush_name
decl_stmt|;
DECL|member|brush_size
name|GtkWidget
modifier|*
name|brush_size
decl_stmt|;
DECL|member|options_box
name|GtkWidget
modifier|*
name|options_box
decl_stmt|;
DECL|member|opacity_data
name|GtkAdjustment
modifier|*
name|opacity_data
decl_stmt|;
DECL|member|spacing_data
name|GtkAdjustment
modifier|*
name|spacing_data
decl_stmt|;
DECL|member|sbar_data
name|GtkAdjustment
modifier|*
name|sbar_data
decl_stmt|;
DECL|member|width
DECL|member|height
name|int
name|width
decl_stmt|,
name|height
decl_stmt|;
DECL|member|cell_width
DECL|member|cell_height
name|int
name|cell_width
decl_stmt|,
name|cell_height
decl_stmt|;
DECL|member|scroll_offset
name|int
name|scroll_offset
decl_stmt|;
DECL|member|redraw
name|int
name|redraw
decl_stmt|;
comment|/*  Brush preview  */
DECL|member|brush_popup
name|GtkWidget
modifier|*
name|brush_popup
decl_stmt|;
DECL|member|brush_preview
name|GtkWidget
modifier|*
name|brush_preview
decl_stmt|;
block|}
struct|;
end_struct

begin_function_decl
name|BrushSelectP
name|brush_select_new
parameter_list|(
name|void
parameter_list|)
function_decl|;
end_function_decl

begin_function_decl
name|void
name|brush_select_select
parameter_list|(
name|BrushSelectP
parameter_list|,
name|int
parameter_list|)
function_decl|;
end_function_decl

begin_function_decl
name|void
name|brush_select_free
parameter_list|(
name|BrushSelectP
parameter_list|)
function_decl|;
end_function_decl

begin_comment
comment|/*  An interface to other dialogs which need to create a paint mode menu  */
end_comment

begin_function_decl
name|GtkWidget
modifier|*
name|create_paint_mode_menu
parameter_list|(
name|MenuItemCallback
parameter_list|)
function_decl|;
end_function_decl

begin_endif
endif|#
directive|endif
end_endif

begin_comment
comment|/*  __BRUSH_SELECT_H__  */
end_comment

end_unit

