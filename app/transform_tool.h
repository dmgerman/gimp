begin_unit|revision:0.9.5;language:C;cregit-version:0.0.1
begin_comment
comment|/* The GIMP -- an image manipulation program  * Copyright (C) 1995 Spencer Kimball and Peter Mattis  *  * This program is free software; you can redistribute it and/or modify  * it under the terms of the GNU General Public License as published by  * the Free Software Foundation; either version 2 of the License, or  * (at your option) any later version.  *  * This program is distributed in the hope that it will be useful,  * but WITHOUT ANY WARRANTY; without even the implied warranty of  * MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the  * GNU General Public License for more details.  *  * You should have received a copy of the GNU General Public License  * along with this program; if not, write to the Free Software  * Foundation, Inc., 59 Temple Place - Suite 330, Boston, MA 02111-1307, USA.  */
end_comment

begin_ifndef
ifndef|#
directive|ifndef
name|__TRANSFORM_TOOL_H__
end_ifndef

begin_define
DECL|macro|__TRANSFORM_TOOL_H__
define|#
directive|define
name|__TRANSFORM_TOOL_H__
end_define

begin_comment
comment|/*  tool functions  */
end_comment

begin_function_decl
name|Tool
modifier|*
name|tools_new_transform_tool
parameter_list|(
name|void
parameter_list|)
function_decl|;
end_function_decl

begin_function_decl
name|void
name|tools_free_transform_tool
parameter_list|(
name|Tool
modifier|*
parameter_list|)
function_decl|;
end_function_decl

begin_function_decl
name|int
name|transform_tool_smoothing
parameter_list|(
name|void
parameter_list|)
function_decl|;
end_function_decl

begin_function_decl
name|int
name|transform_tool_showpath
parameter_list|(
name|void
parameter_list|)
function_decl|;
end_function_decl

begin_function_decl
name|int
name|transform_tool_clip
parameter_list|(
name|void
parameter_list|)
function_decl|;
end_function_decl

begin_function_decl
name|int
name|transform_tool_direction
parameter_list|(
name|void
parameter_list|)
function_decl|;
end_function_decl

begin_function_decl
name|int
name|transform_tool_grid_size
parameter_list|(
name|void
parameter_list|)
function_decl|;
end_function_decl

begin_function_decl
name|int
name|transform_tool_show_grid
parameter_list|(
name|void
parameter_list|)
function_decl|;
end_function_decl

begin_comment
comment|/*  transform directions  */
end_comment

begin_define
DECL|macro|TRANSFORM_TRADITIONAL
define|#
directive|define
name|TRANSFORM_TRADITIONAL
value|0
end_define

begin_define
DECL|macro|TRANSFORM_CORRECTIVE
define|#
directive|define
name|TRANSFORM_CORRECTIVE
value|1
end_define

begin_endif
endif|#
directive|endif
end_endif

begin_comment
comment|/*  __TRANSFORM_TOOL_H__  */
end_comment

end_unit

