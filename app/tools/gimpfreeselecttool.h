begin_unit|revision:0.9.5;language:C;cregit-version:0.0.1
begin_comment
comment|/* The GIMP -- an image manipulation program  * Copyright (C) 1995 Spencer Kimball and Peter Mattis  *  * This program is free software; you can redistribute it and/or modify  * it under the terms of the GNU General Public License as published by  * the Free Software Foundation; either version 2 of the License, or  * (at your option) any later version.  *  * This program is distributed in the hope that it will be useful,  * but WITHOUT ANY WARRANTY; without even the implied warranty of  * MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the  * GNU General Public License for more details.  *  * You should have received a copy of the GNU General Public License  * along with this program; if not, write to the Free Software  * Foundation, Inc., 59 Temple Place - Suite 330, Boston, MA 02111-1307, USA.  */
end_comment

begin_ifndef
ifndef|#
directive|ifndef
name|__FREE_SELECT_H__
end_ifndef

begin_define
DECL|macro|__FREE_SELECT_H__
define|#
directive|define
name|__FREE_SELECT_H__
end_define

begin_comment
comment|/*  free select action functions  */
end_comment

begin_function_decl
name|void
name|free_select_button_press
parameter_list|(
name|Tool
modifier|*
name|tool
parameter_list|,
name|GdkEventButton
modifier|*
name|bevent
parameter_list|,
name|gpointer
name|gdisp_ptr
parameter_list|)
function_decl|;
end_function_decl

begin_function_decl
name|void
name|free_select_button_release
parameter_list|(
name|Tool
modifier|*
name|tool
parameter_list|,
name|GdkEventButton
modifier|*
name|bevent
parameter_list|,
name|gpointer
name|gdisp_ptr
parameter_list|)
function_decl|;
end_function_decl

begin_function_decl
name|void
name|free_select_motion
parameter_list|(
name|Tool
modifier|*
name|tool
parameter_list|,
name|GdkEventMotion
modifier|*
name|mevent
parameter_list|,
name|gpointer
name|gdisp_ptr
parameter_list|)
function_decl|;
end_function_decl

begin_comment
comment|/*  free select functions  */
end_comment

begin_function_decl
name|void
name|free_select
parameter_list|(
name|GimpImage
modifier|*
name|gimage
parameter_list|,
name|gint
name|num_pts
parameter_list|,
name|ScanConvertPoint
modifier|*
name|pts
parameter_list|,
name|SelectOps
name|op
parameter_list|,
name|gboolean
name|antialias
parameter_list|,
name|gboolean
name|feather
parameter_list|,
name|gdouble
name|feather_radius
parameter_list|)
function_decl|;
end_function_decl

begin_function_decl
name|void
name|free_select_draw
parameter_list|(
name|Tool
modifier|*
name|tool
parameter_list|)
function_decl|;
end_function_decl

begin_function_decl
name|Tool
modifier|*
name|tools_new_free_select
parameter_list|(
name|void
parameter_list|)
function_decl|;
end_function_decl

begin_function_decl
name|void
name|tools_free_free_select
parameter_list|(
name|Tool
modifier|*
name|tool
parameter_list|)
function_decl|;
end_function_decl

begin_endif
endif|#
directive|endif
end_endif

begin_comment
comment|/*  __FREE_SELECT_H__  */
end_comment

end_unit

