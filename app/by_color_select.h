begin_unit|revision:0.9.5;language:C;cregit-version:0.0.1
begin_comment
comment|/* The GIMP -- an image manipulation program  * Copyright (C) 1995 Spencer Kimball and Peter Mattis  *  * This program is free software; you can redistribute it and/or modify  * it under the terms of the GNU General Public License as published by  * the Free Software Foundation; either version 2 of the License, or  * (at your option) any later version.  *  * This program is distributed in the hope that it will be useful,  * but WITHOUT ANY WARRANTY; without even the implied warranty of  * MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the  * GNU General Public License for more details.  *  * You should have received a copy of the GNU General Public License  * along with this program; if not, write to the Free Software  * Foundation, Inc., 59 Temple Place - Suite 330, Boston, MA 02111-1307, USA.  */
end_comment

begin_ifndef
ifndef|#
directive|ifndef
name|__BY_COLOR_SELECT_H__
end_ifndef

begin_define
DECL|macro|__BY_COLOR_SELECT_H__
define|#
directive|define
name|__BY_COLOR_SELECT_H__
end_define

begin_include
include|#
directive|include
file|"tools.h"
end_include

begin_include
include|#
directive|include
file|"gdisplayF.h"
end_include

begin_include
include|#
directive|include
file|"gimage.h"
end_include

begin_function_decl
name|Tool
modifier|*
name|tools_new_by_color_select
parameter_list|(
name|void
parameter_list|)
function_decl|;
end_function_decl

begin_function_decl
name|void
name|tools_free_by_color_select
parameter_list|(
name|Tool
modifier|*
name|tool
parameter_list|)
function_decl|;
end_function_decl

begin_function_decl
name|void
name|by_color_select_initialize
parameter_list|(
name|GDisplay
modifier|*
name|gdisp
parameter_list|)
function_decl|;
end_function_decl

begin_function_decl
name|void
name|by_color_select_initialize_by_image
parameter_list|(
name|GImage
modifier|*
name|gimage
parameter_list|)
function_decl|;
end_function_decl

begin_function_decl
name|void
name|by_color_select
parameter_list|(
name|GimpImage
modifier|*
name|gimage
parameter_list|,
name|GimpDrawable
modifier|*
name|drawable
parameter_list|,
name|guchar
modifier|*
name|color
parameter_list|,
name|gint
name|threshold
parameter_list|,
name|gint
name|op
parameter_list|,
name|gint
name|antialias
parameter_list|,
name|gint
name|feather
parameter_list|,
name|gdouble
name|feather_radius
parameter_list|,
name|gint
name|sample_merged
parameter_list|)
function_decl|;
end_function_decl

begin_endif
endif|#
directive|endif
end_endif

begin_comment
comment|/*  __BY_COLOR_SELECT_H__  */
end_comment

end_unit

