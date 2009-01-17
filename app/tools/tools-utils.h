begin_unit|revision:0.9.5;language:C;cregit-version:0.0.1
begin_comment
comment|/* GIMP - The GNU Image Manipulation Program  * Copyright (C) 1995 Spencer Kimball and Peter Mattis  *  * This program is free software: you can redistribute it and/or modify  * it under the terms of the GNU General Public License as published by  * the Free Software Foundation; either version 3 of the License, or  * (at your option) any later version.  *  * This program is distributed in the hope that it will be useful,  * but WITHOUT ANY WARRANTY; without even the implied warranty of  * MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the  * GNU General Public License for more details.  *  * You should have received a copy of the GNU General Public License  * along with this program.  If not, see<http://www.gnu.org/licenses/>.  */
end_comment

begin_ifndef
ifndef|#
directive|ifndef
name|__TOOLS_UTILS_H__
end_ifndef

begin_define
DECL|macro|__TOOLS_UTILS_H__
define|#
directive|define
name|__TOOLS_UTILS_H__
end_define

begin_comment
comment|/*  * Common values for the n_snap_lines parameter of  * gimp_tool_motion_constrain.  */
end_comment

begin_define
DECL|macro|GIMP_TOOL_CONSTRAIN_90_DEGREES
define|#
directive|define
name|GIMP_TOOL_CONSTRAIN_90_DEGREES
value|2
end_define

begin_define
DECL|macro|GIMP_TOOL_CONSTRAIN_45_DEGREES
define|#
directive|define
name|GIMP_TOOL_CONSTRAIN_45_DEGREES
value|4
end_define

begin_define
DECL|macro|GIMP_TOOL_CONSTRAIN_15_DEGREES
define|#
directive|define
name|GIMP_TOOL_CONSTRAIN_15_DEGREES
value|12
end_define

begin_function_decl
name|void
name|gimp_tool_motion_constrain
parameter_list|(
name|gdouble
name|start_x
parameter_list|,
name|gdouble
name|start_y
parameter_list|,
name|gdouble
modifier|*
name|end_x
parameter_list|,
name|gdouble
modifier|*
name|end_y
parameter_list|,
name|gint
name|n_snap_lines
parameter_list|)
function_decl|;
end_function_decl

begin_endif
endif|#
directive|endif
end_endif

begin_comment
comment|/*  __TOOLS_UTILS_H__  */
end_comment

end_unit

