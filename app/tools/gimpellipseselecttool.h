begin_unit|revision:0.9.5;language:C;cregit-version:0.0.1
begin_comment
comment|/* The GIMP -- an image manipulation program  * Copyright (C) 1995 Spencer Kimball and Peter Mattis  *  * This program is free software; you can redistribute it and/or modify  * it under the terms of the GNU General Public License as published by  * the Free Software Foundation; either version 2 of the License, or  * (at your option) any later version.  *  * This program is distributed in the hope that it will be useful,  * but WITHOUT ANY WARRANTY; without even the implied warranty of  * MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the  * GNU General Public License for more details.  *  * You should have received a copy of the GNU General Public License  * along with this program; if not, write to the Free Software  * Foundation, Inc., 59 Temple Place - Suite 330, Boston, MA 02111-1307, USA.  */
end_comment

begin_ifndef
ifndef|#
directive|ifndef
name|__GIMP_ELLIPSE_SELECT_TOOL_H__
end_ifndef

begin_define
DECL|macro|__GIMP_ELLIPSE_SELECT_TOOL_H__
define|#
directive|define
name|__GIMP_ELLIPSE_SELECT_TOOL_H__
end_define

begin_include
include|#
directive|include
file|"gimprectselecttool.h"
end_include

begin_define
DECL|macro|GIMP_TYPE_ELLIPSE_SELECT_TOOL
define|#
directive|define
name|GIMP_TYPE_ELLIPSE_SELECT_TOOL
value|(gimp_ellipse_select_tool_get_type ())
end_define

begin_define
DECL|macro|GIMP_ELLIPSE_SELECT_TOOL (obj)
define|#
directive|define
name|GIMP_ELLIPSE_SELECT_TOOL
parameter_list|(
name|obj
parameter_list|)
value|(GTK_CHECK_CAST ((obj), GIMP_TYPE_ELLIPSE_SELECT_TOOL, GimpEllipseSelectTool))
end_define

begin_define
DECL|macro|GIMP_IS_ELLIPSE_SELECT_TOOL (obj)
define|#
directive|define
name|GIMP_IS_ELLIPSE_SELECT_TOOL
parameter_list|(
name|obj
parameter_list|)
value|(GTK_CHECK_TYPE ((obj), GIMP_TYPE_ELLIPSE_SELECT_TOOL))
end_define

begin_define
DECL|macro|GIMP_ELLIPSE_SELECT_TOOL_CLASS (klass)
define|#
directive|define
name|GIMP_ELLIPSE_SELECT_TOOL_CLASS
parameter_list|(
name|klass
parameter_list|)
value|(GTK_CHECK_CLASS_CAST ((klass), GIMP_TYPE_ELLIPSE_SELECT_TOOL, GimpEllipseSelectToolClass))
end_define

begin_define
DECL|macro|GIMP_IS_ELLIPSE_SELECT_TOOL_CLASS (klass)
define|#
directive|define
name|GIMP_IS_ELLIPSE_SELECT_TOOL_CLASS
parameter_list|(
name|klass
parameter_list|)
value|(GTK_CHECK_CLASS_TYPE ((klass), GIMP_TYPE_ELLIPSE_SELECT_TOOL))
end_define

begin_typedef
DECL|typedef|GimpEllipseSelectTool
typedef|typedef
name|struct
name|_GimpEllipseSelectTool
name|GimpEllipseSelectTool
typedef|;
end_typedef

begin_typedef
DECL|typedef|GimpEllipseSelectToolClass
typedef|typedef
name|struct
name|_GimpEllipseSelectToolClass
name|GimpEllipseSelectToolClass
typedef|;
end_typedef

begin_struct
DECL|struct|_GimpEllipseSelectTool
struct|struct
name|_GimpEllipseSelectTool
block|{
DECL|member|parent_instance
name|GimpRectSelectTool
name|parent_instance
decl_stmt|;
block|}
struct|;
end_struct

begin_struct
DECL|struct|_GimpEllipseSelectToolClass
struct|struct
name|_GimpEllipseSelectToolClass
block|{
DECL|member|parent_class
name|GimpRectSelectToolClass
name|parent_class
decl_stmt|;
block|}
struct|;
end_struct

begin_function_decl
name|void
name|gimp_ellipse_select_tool_register
parameter_list|(
name|Gimp
modifier|*
name|gimp
parameter_list|)
function_decl|;
end_function_decl

begin_function_decl
name|GtkType
name|gimp_ellipse_select_tool_get_type
parameter_list|(
name|void
parameter_list|)
function_decl|;
end_function_decl

begin_function_decl
name|void
name|ellipse_select
parameter_list|(
name|GimpImage
modifier|*
name|gimage
parameter_list|,
name|gint
name|x
parameter_list|,
name|gint
name|y
parameter_list|,
name|gint
name|w
parameter_list|,
name|gint
name|h
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

begin_endif
endif|#
directive|endif
end_endif

begin_comment
comment|/*  __GIMP_ELLIPSE_SELECT_TOOL_H__  */
end_comment

end_unit

