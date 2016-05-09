begin_unit|revision:0.9.5;language:C;cregit-version:0.0.1
begin_comment
comment|/* GIMP - The GNU Image Manipulation Program  * Copyright (C) 1995 Spencer Kimball and Peter Mattis  *  * This program is free software: you can redistribute it and/or modify  * it under the terms of the GNU General Public License as published by  * the Free Software Foundation; either version 3 of the License, or  * (at your option) any later version.  *  * This program is distributed in the hope that it will be useful,  * but WITHOUT ANY WARRANTY; without even the implied warranty of  * MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the  * GNU General Public License for more details.  *  * You should have received a copy of the GNU General Public License  * along with this program.  If not, see<http://www.gnu.org/licenses/>.  */
end_comment

begin_ifndef
ifndef|#
directive|ifndef
name|__GIMP_LEVELS_TOOL_H__
end_ifndef

begin_define
DECL|macro|__GIMP_LEVELS_TOOL_H__
define|#
directive|define
name|__GIMP_LEVELS_TOOL_H__
end_define

begin_include
include|#
directive|include
file|"gimpfiltertool.h"
end_include

begin_define
DECL|macro|GIMP_TYPE_LEVELS_TOOL
define|#
directive|define
name|GIMP_TYPE_LEVELS_TOOL
value|(gimp_levels_tool_get_type ())
end_define

begin_define
DECL|macro|GIMP_LEVELS_TOOL (obj)
define|#
directive|define
name|GIMP_LEVELS_TOOL
parameter_list|(
name|obj
parameter_list|)
value|(G_TYPE_CHECK_INSTANCE_CAST ((obj), GIMP_TYPE_LEVELS_TOOL, GimpLevelsTool))
end_define

begin_define
DECL|macro|GIMP_LEVELS_TOOL_CLASS (klass)
define|#
directive|define
name|GIMP_LEVELS_TOOL_CLASS
parameter_list|(
name|klass
parameter_list|)
value|(G_TYPE_CHECK_CLASS_CAST ((klass), GIMP_TYPE_LEVELS_TOOL, GimpLevelsToolClass))
end_define

begin_define
DECL|macro|GIMP_IS_LEVELS_TOOL (obj)
define|#
directive|define
name|GIMP_IS_LEVELS_TOOL
parameter_list|(
name|obj
parameter_list|)
value|(G_TYPE_CHECK_INSTANCE_TYPE ((obj), GIMP_TYPE_LEVELS_TOOL))
end_define

begin_define
DECL|macro|GIMP_IS_LEVELS_TOOL_CLASS (klass)
define|#
directive|define
name|GIMP_IS_LEVELS_TOOL_CLASS
parameter_list|(
name|klass
parameter_list|)
value|(G_TYPE_CHECK_CLASS_TYPE ((klass), GIMP_TYPE_LEVELS_TOOL))
end_define

begin_define
DECL|macro|GIMP_LEVELS_TOOL_GET_CLASS (obj)
define|#
directive|define
name|GIMP_LEVELS_TOOL_GET_CLASS
parameter_list|(
name|obj
parameter_list|)
value|(G_TYPE_INSTANCE_GET_CLASS ((obj), GIMP_TYPE_LEVELS_TOOL, GimpLevelsToolClass))
end_define

begin_typedef
DECL|typedef|GimpLevelsTool
typedef|typedef
name|struct
name|_GimpLevelsTool
name|GimpLevelsTool
typedef|;
end_typedef

begin_typedef
DECL|typedef|GimpLevelsToolClass
typedef|typedef
name|struct
name|_GimpLevelsToolClass
name|GimpLevelsToolClass
typedef|;
end_typedef

begin_struct
DECL|struct|_GimpLevelsTool
struct|struct
name|_GimpLevelsTool
block|{
DECL|member|parent_instance
name|GimpFilterTool
name|parent_instance
decl_stmt|;
comment|/* dialog */
DECL|member|histogram
name|GimpHistogram
modifier|*
name|histogram
decl_stmt|;
DECL|member|channel_menu
name|GtkWidget
modifier|*
name|channel_menu
decl_stmt|;
DECL|member|histogram_view
name|GtkWidget
modifier|*
name|histogram_view
decl_stmt|;
DECL|member|input_bar
name|GtkWidget
modifier|*
name|input_bar
decl_stmt|;
DECL|member|low_input_spinbutton
name|GtkWidget
modifier|*
name|low_input_spinbutton
decl_stmt|;
DECL|member|high_input_spinbutton
name|GtkWidget
modifier|*
name|high_input_spinbutton
decl_stmt|;
DECL|member|low_output_spinbutton
name|GtkWidget
modifier|*
name|low_output_spinbutton
decl_stmt|;
DECL|member|high_output_spinbutton
name|GtkWidget
modifier|*
name|high_output_spinbutton
decl_stmt|;
DECL|member|low_input
name|GtkAdjustment
modifier|*
name|low_input
decl_stmt|;
DECL|member|gamma
name|GtkAdjustment
modifier|*
name|gamma
decl_stmt|;
DECL|member|gamma_linear
name|GtkAdjustment
modifier|*
name|gamma_linear
decl_stmt|;
DECL|member|high_input
name|GtkAdjustment
modifier|*
name|high_input
decl_stmt|;
DECL|member|output_bar
name|GtkWidget
modifier|*
name|output_bar
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
DECL|struct|_GimpLevelsToolClass
struct|struct
name|_GimpLevelsToolClass
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
name|gimp_levels_tool_register
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
name|gimp_levels_tool_get_type
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
comment|/*  __GIMP_LEVELS_TOOL_H__  */
end_comment

end_unit

