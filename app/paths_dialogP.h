begin_unit|revision:0.9.5;language:C;cregit-version:0.0.1
begin_comment
comment|/* The GIMP -- an image manipulation program  * Copyright (C) 1999 Andy Thomas alt@picnic.demon.co.uk  *  * This program is free software; you can redistribute it and/or modify  * it under the terms of the GNU General Public License as published by  * the Free Software Foundation; either version 2 of the License, or  * (at your option) any later version.  *  * This program is distributed in the hope that it will be useful,  * but WITHOUT ANY WARRANTY; without even the implied warranty of  * MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the  * GNU General Public License for more details.  *  * You should have received a copy of the GNU General Public License  * along with this program; if not, write to the Free Software  * Foundation, Inc., 59 Temple Place - Suite 330, Boston, MA 02111-1307, USA.  */
end_comment

begin_ifndef
ifndef|#
directive|ifndef
name|__PATHS_DIALOG_P_H__
end_ifndef

begin_define
DECL|macro|__PATHS_DIALOG_P_H__
define|#
directive|define
name|__PATHS_DIALOG_P_H__
end_define

begin_include
include|#
directive|include
file|"bezier_selectP.h"
end_include

begin_function_decl
name|void
name|paths_newpoint_current
parameter_list|(
name|BezierSelect
modifier|*
parameter_list|,
name|GDisplay
modifier|*
parameter_list|)
function_decl|;
end_function_decl

begin_function_decl
name|void
name|paths_first_button_press
parameter_list|(
name|BezierSelect
modifier|*
parameter_list|,
name|GDisplay
modifier|*
parameter_list|)
function_decl|;
end_function_decl

begin_function_decl
name|void
name|paths_new_bezier_select_tool
parameter_list|(
name|void
parameter_list|)
function_decl|;
end_function_decl

begin_function_decl
name|PATHP
name|paths_get_bzpaths
parameter_list|(
name|void
parameter_list|)
function_decl|;
end_function_decl

begin_function_decl
name|void
name|paths_set_bzpaths
parameter_list|(
name|GImage
modifier|*
parameter_list|,
name|PATHP
parameter_list|)
function_decl|;
end_function_decl

begin_function_decl
name|void
name|paths_dialog_set_default_op
parameter_list|(
name|void
parameter_list|)
function_decl|;
end_function_decl

begin_function_decl
name|void
name|paths_transform_flip_horz
parameter_list|(
name|GImage
modifier|*
parameter_list|)
function_decl|;
end_function_decl

begin_function_decl
name|void
name|paths_transform_flip_vert
parameter_list|(
name|GImage
modifier|*
parameter_list|)
function_decl|;
end_function_decl

begin_function_decl
name|void
name|paths_transform_xy
parameter_list|(
name|GImage
modifier|*
parameter_list|,
name|gint
parameter_list|,
name|gint
parameter_list|)
function_decl|;
end_function_decl

begin_endif
endif|#
directive|endif
end_endif

begin_comment
comment|/*  __PATHS_DIALOG_P_H__  */
end_comment

end_unit

