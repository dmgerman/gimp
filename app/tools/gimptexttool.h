begin_unit|revision:0.9.5;language:C;cregit-version:0.0.1
begin_comment
comment|/* The GIMP -- an image manipulation program  * Copyright (C) 1995 Spencer Kimball and Peter Mattis  *  * This program is free software; you can redistribute it and/or modify  * it under the terms of the GNU General Public License as published by  * the Free Software Foundation; either version 2 of the License, or  * (at your option) any later version.  *  * This program is distributed in the hope that it will be useful,  * but WITHOUT ANY WARRANTY; without even the implied warranty of  * MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the  * GNU General Public License for more details.  *  * You should have received a copy of the GNU General Public License  * along with this program; if not, write to the Free Software  * Foundation, Inc., 59 Temple Place - Suite 330, Boston, MA 02111-1307, USA.  */
end_comment

begin_ifndef
ifndef|#
directive|ifndef
name|__GIMP_TEXT_TOOL_H__
end_ifndef

begin_define
DECL|macro|__GIMP_TEXT_TOOL_H__
define|#
directive|define
name|__GIMP_TEXT_TOOL_H__
end_define

begin_include
include|#
directive|include
file|"gimptool.h"
end_include

begin_define
DECL|macro|SUPERSAMPLE
define|#
directive|define
name|SUPERSAMPLE
value|3
end_define

begin_typedef
typedef|typedef
enum|enum
DECL|enum|__anon2bb7e1bb0103
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
DECL|macro|GIMP_TYPE_TEXT_TOOL
define|#
directive|define
name|GIMP_TYPE_TEXT_TOOL
value|(gimp_text_tool_get_type ())
end_define

begin_define
DECL|macro|GIMP_TEXT_TOOL (obj)
define|#
directive|define
name|GIMP_TEXT_TOOL
parameter_list|(
name|obj
parameter_list|)
value|(G_TYPE_CHECK_INSTANCE_CAST ((obj), GIMP_TYPE_TEXT_TOOL, GimpTextTool))
end_define

begin_define
DECL|macro|GIMP_IS_TEXT_TOOL (obj)
define|#
directive|define
name|GIMP_IS_TEXT_TOOL
parameter_list|(
name|obj
parameter_list|)
value|(G_TYPE_CHECK_INSTANCE_TYPE ((obj), GIMP_TYPE_TEXT_TOOL))
end_define

begin_define
DECL|macro|GIMP_TEXT_TOOL_CLASS (klass)
define|#
directive|define
name|GIMP_TEXT_TOOL_CLASS
parameter_list|(
name|klass
parameter_list|)
value|(G_TYPE_CHECK_CLASS_CAST ((klass), GIMP_TYPE_TEXT_TOOL, GimpTextToolClass))
end_define

begin_define
DECL|macro|GIMP_IS_TEXT_TOOL_CLASS (klass)
define|#
directive|define
name|GIMP_IS_TEXT_TOOL_CLASS
parameter_list|(
name|klass
parameter_list|)
value|(G_TYPE_CHECK_CLASS_TYPE ((klass), GIMP_TYPE_TEXT_TOOL))
end_define

begin_typedef
DECL|typedef|GimpTextTool
typedef|typedef
name|struct
name|_GimpTextTool
name|GimpTextTool
typedef|;
end_typedef

begin_typedef
DECL|typedef|GimpTextToolClass
typedef|typedef
name|struct
name|_GimpTextToolClass
name|GimpTextToolClass
typedef|;
end_typedef

begin_struct
DECL|struct|_GimpTextTool
struct|struct
name|_GimpTextTool
block|{
DECL|member|parent_instance
name|GimpTool
name|parent_instance
decl_stmt|;
DECL|member|click_x
name|gint
name|click_x
decl_stmt|;
DECL|member|click_y
name|gint
name|click_y
decl_stmt|;
DECL|member|gdisp
name|GimpDisplay
modifier|*
name|gdisp
decl_stmt|;
DECL|member|pango_context
name|PangoContext
modifier|*
name|pango_context
decl_stmt|;
block|}
struct|;
end_struct

begin_struct
DECL|struct|_GimpTextToolClass
struct|struct
name|_GimpTextToolClass
block|{
DECL|member|parent_class
name|GimpToolClass
name|parent_class
decl_stmt|;
block|}
struct|;
end_struct

begin_function_decl
name|void
name|gimp_text_tool_register
parameter_list|(
name|Gimp
modifier|*
name|gimp
parameter_list|)
function_decl|;
end_function_decl

begin_function_decl
name|GType
name|gimp_text_tool_get_type
parameter_list|(
name|void
parameter_list|)
function_decl|;
end_function_decl

begin_function_decl
name|gboolean
name|text_get_extents
parameter_list|(
specifier|const
name|gchar
modifier|*
name|fontname
parameter_list|,
specifier|const
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
specifier|const
name|gchar
modifier|*
name|fontname
parameter_list|,
specifier|const
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
comment|/* __GIMP_TEXT_TOOL_H__ */
end_comment

end_unit

