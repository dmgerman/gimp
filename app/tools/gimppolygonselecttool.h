begin_unit|revision:0.9.5;language:C;cregit-version:0.0.1
begin_comment
comment|/* GIMP - The GNU Image Manipulation Program  *  * A polygonal selection tool for GIMP  * Copyright (C) 2007 Martin Nordholts  *  * Based on gimpfreeselecttool.h which is  * Copyright (C) 1995 Spencer Kimball and Peter Mattis  *  * This program is free software; you can redistribute it and/or modify  * it under the terms of the GNU General Public License as published by  * the Free Software Foundation; either version 2 of the License, or  * (at your option) any later version.  *  * This program is distributed in the hope that it will be useful,  * but WITHOUT ANY WARRANTY; without even the implied warranty of  * MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the  * GNU General Public License for more details.  *  * You should have received a copy of the GNU General Public License  * along with this program; if not, write to the Free Software  * Foundation, Inc., 59 Temple Place - Suite 330, Boston, MA 02111-1307, USA.  */
end_comment

begin_ifndef
ifndef|#
directive|ifndef
name|GIMP_POLYGON_SELECT_TOOL_H
end_ifndef

begin_define
DECL|macro|GIMP_POLYGON_SELECT_TOOL_H
define|#
directive|define
name|GIMP_POLYGON_SELECT_TOOL_H
end_define

begin_include
include|#
directive|include
file|"gimpselectiontool.h"
end_include

begin_define
DECL|macro|GIMP_TYPE_POLYGON_SELECT_TOOL
define|#
directive|define
name|GIMP_TYPE_POLYGON_SELECT_TOOL
value|(gimp_polygon_select_tool_get_type ())
end_define

begin_define
DECL|macro|GIMP_POLYGON_SELECT_TOOL (obj)
define|#
directive|define
name|GIMP_POLYGON_SELECT_TOOL
parameter_list|(
name|obj
parameter_list|)
value|(G_TYPE_CHECK_INSTANCE_CAST ((obj), GIMP_TYPE_POLYGON_SELECT_TOOL, GimpPolygonSelectTool))
end_define

begin_define
DECL|macro|GIMP_POLYGON_SELECT_TOOL_CLASS (klass)
define|#
directive|define
name|GIMP_POLYGON_SELECT_TOOL_CLASS
parameter_list|(
name|klass
parameter_list|)
value|(G_TYPE_CHECK_CLASS_CAST ((klass), GIMP_TYPE_POLYGON_SELECT_TOOL, GimpPolygonSelectToolClass))
end_define

begin_define
DECL|macro|GIMP_IS_POLYGON_SELECT_TOOL (obj)
define|#
directive|define
name|GIMP_IS_POLYGON_SELECT_TOOL
parameter_list|(
name|obj
parameter_list|)
value|(G_TYPE_CHECK_INSTANCE_TYPE ((obj), GIMP_TYPE_POLYGON_SELECT_TOOL))
end_define

begin_define
DECL|macro|GIMP_IS_POLYGON_SELECT_TOOL_CLASS (klass)
define|#
directive|define
name|GIMP_IS_POLYGON_SELECT_TOOL_CLASS
parameter_list|(
name|klass
parameter_list|)
value|(G_TYPE_CHECK_CLASS_TYPE ((klass), GIMP_TYPE_POLYGON_SELECT_TOOL))
end_define

begin_define
DECL|macro|GIMP_POLYGON_SELECT_TOOL_GET_CLASS (obj)
define|#
directive|define
name|GIMP_POLYGON_SELECT_TOOL_GET_CLASS
parameter_list|(
name|obj
parameter_list|)
value|(G_TYPE_INSTANCE_GET_CLASS ((obj), GIMP_TYPE_POLYGON_SELECT_TOOL, GimpPolygonSelectToolClass))
end_define

begin_typedef
DECL|typedef|GimpPolygonSelectTool
typedef|typedef
name|struct
name|_GimpPolygonSelectTool
name|GimpPolygonSelectTool
typedef|;
end_typedef

begin_typedef
DECL|typedef|GimpPolygonSelectToolPrivate
typedef|typedef
name|struct
name|_GimpPolygonSelectToolPrivate
name|GimpPolygonSelectToolPrivate
typedef|;
end_typedef

begin_typedef
DECL|typedef|GimpPolygonSelectToolClass
typedef|typedef
name|struct
name|_GimpPolygonSelectToolClass
name|GimpPolygonSelectToolClass
typedef|;
end_typedef

begin_struct
DECL|struct|_GimpPolygonSelectTool
struct|struct
name|_GimpPolygonSelectTool
block|{
DECL|member|parent_instance
name|GimpSelectionTool
name|parent_instance
decl_stmt|;
DECL|member|priv
name|GimpPolygonSelectToolPrivate
modifier|*
name|priv
decl_stmt|;
block|}
struct|;
end_struct

begin_struct
DECL|struct|_GimpPolygonSelectToolClass
struct|struct
name|_GimpPolygonSelectToolClass
block|{
DECL|member|parent_class
name|GimpSelectionToolClass
name|parent_class
decl_stmt|;
comment|/*  virtual function  */
DECL|member|select
name|void
function_decl|(
modifier|*
name|select
function_decl|)
parameter_list|(
name|GimpPolygonSelectTool
modifier|*
name|poly_select_tool
parameter_list|,
name|GimpDisplay
modifier|*
name|display
parameter_list|)
function_decl|;
block|}
struct|;
end_struct

begin_function_decl
name|void
name|gimp_polygon_select_tool_register
parameter_list|(
name|GimpToolRegisterCallback
name|callback
parameter_list|,
name|gpointer
name|data
parameter_list|)
function_decl|;
end_function_decl

begin_decl_stmt
name|GType
name|gimp_polygon_select_tool_get_type
argument_list|(
name|void
argument_list|)
name|G_GNUC_CONST
decl_stmt|;
end_decl_stmt

begin_function_decl
name|void
name|gimp_polygon_select_tool_select
parameter_list|(
name|GimpPolygonSelectTool
modifier|*
name|poly_sel
parameter_list|,
name|GimpDisplay
modifier|*
name|display
parameter_list|)
function_decl|;
end_function_decl

begin_endif
endif|#
directive|endif
end_endif

begin_comment
comment|/* GIMP_POLYGON_SELECT_TOOL_H */
end_comment

end_unit

