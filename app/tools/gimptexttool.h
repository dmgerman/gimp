begin_unit|revision:0.9.5;language:C;cregit-version:0.0.1
begin_comment
comment|/* The GIMP -- an image manipulation program  * Copyright (C) 1995 Spencer Kimball and Peter Mattis  *  * This program is free software; you can redistribute it and/or modify  * it under the terms of the GNU General Public License as published by  * the Free Software Foundation; either version 2 of the License, or  * (at your option) any later version.  *  * This program is distributed in the hope that it will be useful,  * but WITHOUT ANY WARRANTY; without even the implied warranty of  * MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the  * GNU General Public License for more details.  *  * You should have received a copy of the GNU General Public License  * along with this program; if not, write to the Free Software  * Foundation, Inc., 59 Temple Place - Suite 330, Boston, MA 02111-1307, USA.  */
end_comment

begin_ifndef
ifndef|#
directive|ifndef
name|__TEXT_TOOL_H__
end_ifndef

begin_define
DECL|macro|__TEXT_TOOL_H__
define|#
directive|define
name|__TEXT_TOOL_H__
end_define

begin_include
include|#
directive|include
file|"tools.h"
end_include

begin_include
include|#
directive|include
file|"layerF.h"
end_include

begin_include
include|#
directive|include
file|"gimpimageF.h"
end_include

begin_include
include|#
directive|include
file|"gimpdrawableF.h"
end_include

begin_typedef
DECL|enum|__anon28b6e99a0103
typedef|typedef
enum|enum
block|{
DECL|enumerator|PIXELS
name|PIXELS
block|,
DECL|enumerator|POINTS
name|POINTS
DECL|typedef|SizeType
block|}
name|SizeType
typedef|;
end_typedef

begin_define
DECL|macro|SUPERSAMPLE
define|#
directive|define
name|SUPERSAMPLE
value|3
end_define

begin_comment
comment|/*  text functions  */
end_comment

begin_function_decl
name|Tool
modifier|*
name|tools_new_text
parameter_list|(
name|void
parameter_list|)
function_decl|;
end_function_decl

begin_function_decl
name|void
name|tools_free_text
parameter_list|(
name|Tool
modifier|*
parameter_list|)
function_decl|;
end_function_decl

begin_function_decl
name|gboolean
name|text_get_extents
parameter_list|(
name|gchar
modifier|*
name|fontname
parameter_list|,
name|gchar
modifier|*
name|text
parameter_list|,
name|gint
modifier|*
name|width
parameter_list|,
name|gint
modifier|*
name|height
parameter_list|,
name|gint
modifier|*
name|ascent
parameter_list|,
name|gint
modifier|*
name|descent
parameter_list|)
function_decl|;
end_function_decl

begin_function_decl
name|GimpLayer
modifier|*
name|text_render
parameter_list|(
name|GimpImage
modifier|*
name|gimage
parameter_list|,
name|GimpDrawable
modifier|*
name|drawable
parameter_list|,
name|gint
name|text_x
parameter_list|,
name|gint
name|text_y
parameter_list|,
name|gchar
modifier|*
name|fontname
parameter_list|,
name|gchar
modifier|*
name|text
parameter_list|,
name|gint
name|border
parameter_list|,
name|gint
name|antialias
parameter_list|)
function_decl|;
end_function_decl

begin_endif
endif|#
directive|endif
end_endif

begin_comment
comment|/* __TEXT_TOOL_H__ */
end_comment

end_unit

