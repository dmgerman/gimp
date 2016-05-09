begin_unit|revision:0.9.5;language:C;cregit-version:0.0.1
begin_comment
comment|/* GIMP - The GNU Image Manipulation Program  * Copyright (C) 1995 Spencer Kimball and Peter Mattis  *  * This program is free software: you can redistribute it and/or modify  * it under the terms of the GNU General Public License as published by  * the Free Software Foundation; either version 3 of the License, or  * (at your option) any later version.  *  * This program is distributed in the hope that it will be useful,  * but WITHOUT ANY WARRANTY; without even the implied warranty of  * MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the  * GNU General Public License for more details.  *  * You should have received a copy of the GNU General Public License  * along with this program.  If not, see<http://www.gnu.org/licenses/>.  */
end_comment

begin_ifndef
ifndef|#
directive|ifndef
name|__GIMP_CURVES_TOOL_H__
end_ifndef

begin_define
DECL|macro|__GIMP_CURVES_TOOL_H__
define|#
directive|define
name|__GIMP_CURVES_TOOL_H__
end_define

begin_include
include|#
directive|include
file|"gimpfiltertool.h"
end_include

begin_define
DECL|macro|GIMP_TYPE_CURVES_TOOL
define|#
directive|define
name|GIMP_TYPE_CURVES_TOOL
value|(gimp_curves_tool_get_type ())
end_define

begin_define
DECL|macro|GIMP_CURVES_TOOL (obj)
define|#
directive|define
name|GIMP_CURVES_TOOL
parameter_list|(
name|obj
parameter_list|)
value|(G_TYPE_CHECK_INSTANCE_CAST ((obj), GIMP_TYPE_CURVES_TOOL, GimpCurvesTool))
end_define

begin_define
DECL|macro|GIMP_IS_CURVES_TOOL (obj)
define|#
directive|define
name|GIMP_IS_CURVES_TOOL
parameter_list|(
name|obj
parameter_list|)
value|(G_TYPE_CHECK_INSTANCE_TYPE ((obj), GIMP_TYPE_CURVES_TOOL))
end_define

begin_define
DECL|macro|GIMP_CURVES_TOOL_CLASS (klass)
define|#
directive|define
name|GIMP_CURVES_TOOL_CLASS
parameter_list|(
name|klass
parameter_list|)
value|(G_TYPE_CHECK_CLASS_CAST ((klass), GIMP_TYPE_CURVES_TOOL, GimpCurvesToolClass))
end_define

begin_define
DECL|macro|GIMP_IS_CURVES_TOOL_CLASS (klass)
define|#
directive|define
name|GIMP_IS_CURVES_TOOL_CLASS
parameter_list|(
name|klass
parameter_list|)
value|(G_TYPE_CHECK_CLASS_TYPE ((klass), GIMP_TYPE_CURVES_TOOL))
end_define

begin_typedef
DECL|typedef|GimpCurvesTool
typedef|typedef
name|struct
name|_GimpCurvesTool
name|GimpCurvesTool
typedef|;
end_typedef

begin_typedef
DECL|typedef|GimpCurvesToolClass
typedef|typedef
name|struct
name|_GimpCurvesToolClass
name|GimpCurvesToolClass
typedef|;
end_typedef

begin_struct
DECL|struct|_GimpCurvesTool
struct|struct
name|_GimpCurvesTool
block|{
DECL|member|parent_instance
name|GimpFilterTool
name|parent_instance
decl_stmt|;
comment|/* dialog */
DECL|member|picked_color
name|gdouble
name|picked_color
index|[
literal|5
index|]
decl_stmt|;
DECL|member|channel_menu
name|GtkWidget
modifier|*
name|channel_menu
decl_stmt|;
DECL|member|xrange
name|GtkWidget
modifier|*
name|xrange
decl_stmt|;
DECL|member|yrange
name|GtkWidget
modifier|*
name|yrange
decl_stmt|;
DECL|member|graph
name|GtkWidget
modifier|*
name|graph
decl_stmt|;
DECL|member|curve_type
name|GtkWidget
modifier|*
name|curve_type
decl_stmt|;
comment|/* export dialog */
DECL|member|export_old_format
name|gboolean
name|export_old_format
decl_stmt|;
block|}
struct|;
end_struct

begin_struct
DECL|struct|_GimpCurvesToolClass
struct|struct
name|_GimpCurvesToolClass
block|{
DECL|member|parent_class
name|GimpFilterToolClass
name|parent_class
decl_stmt|;
block|}
struct|;
end_struct

begin_function_decl
name|void
name|gimp_curves_tool_register
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
name|gimp_curves_tool_get_type
argument_list|(
name|void
argument_list|)
name|G_GNUC_CONST
decl_stmt|;
end_decl_stmt

begin_endif
endif|#
directive|endif
end_endif

begin_comment
comment|/*  __GIMP_CURVES_TOOL_H__  */
end_comment

end_unit

