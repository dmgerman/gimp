begin_unit|revision:0.9.5;language:C;cregit-version:0.0.1
begin_comment
comment|/* The GIMP -- an image manipulation program  * Copyright (C) 1995 Spencer Kimball and Peter Mattis  *  * brush_edit module Copyright 1998 Jay Cox<jaycox@earthlink.net>  *  * This program is free software; you can redistribute it and/or modify  * it under the terms of the GNU General Public License as published by  * the Free Software Foundation; either version 2 of the License, or  * (at your option) any later version.  *  * This program is distributed in the hope that it will be useful,  * but WITHOUT ANY WARRANTY; without even the implied warranty of  * MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the  * GNU General Public License for more details.  *  * You should have received a copy of the GNU General Public License  * along with this program; if not, write to the Free Software  * Foundation, Inc., 59 Temple Place - Suite 330, Boston, MA 02111-1307, USA.  */
end_comment

begin_ifndef
ifndef|#
directive|ifndef
name|__BRUSH_EDIT_H__
end_ifndef

begin_define
DECL|macro|__BRUSH_EDIT_H__
define|#
directive|define
name|__BRUSH_EDIT_H__
end_define

begin_typedef
DECL|typedef|BrushEditGeneratedWindow
typedef|typedef
name|struct
name|_BrushEditGeneratedWindow
name|BrushEditGeneratedWindow
typedef|;
end_typedef

begin_struct
DECL|struct|_BrushEditGeneratedWindow
struct|struct
name|_BrushEditGeneratedWindow
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
DECL|member|scale_label
name|GtkWidget
modifier|*
name|scale_label
decl_stmt|;
DECL|member|options_box
name|GtkWidget
modifier|*
name|options_box
decl_stmt|;
DECL|member|name
name|GtkWidget
modifier|*
name|name
decl_stmt|;
DECL|member|radius_data
name|GtkAdjustment
modifier|*
name|radius_data
decl_stmt|;
DECL|member|hardness_data
name|GtkAdjustment
modifier|*
name|hardness_data
decl_stmt|;
DECL|member|angle_data
name|GtkAdjustment
modifier|*
name|angle_data
decl_stmt|;
DECL|member|aspect_ratio_data
name|GtkAdjustment
modifier|*
name|aspect_ratio_data
decl_stmt|;
comment|/*  Brush preview  */
DECL|member|brush_preview
name|GtkWidget
modifier|*
name|brush_preview
decl_stmt|;
DECL|member|brush
name|GimpBrushGenerated
modifier|*
name|brush
decl_stmt|;
DECL|member|scale
name|gint
name|scale
decl_stmt|;
block|}
struct|;
end_struct

begin_function_decl
name|BrushEditGeneratedWindow
modifier|*
name|brush_edit_generated_new
parameter_list|(
name|void
parameter_list|)
function_decl|;
end_function_decl

begin_function_decl
name|void
name|brush_edit_generated_set_brush
parameter_list|(
name|BrushEditGeneratedWindow
modifier|*
name|begw
parameter_list|,
name|GimpBrush
modifier|*
name|brush
parameter_list|)
function_decl|;
end_function_decl

begin_endif
endif|#
directive|endif
end_endif

begin_comment
comment|/*  __BRUSH_EDIT_H__  */
end_comment

end_unit

