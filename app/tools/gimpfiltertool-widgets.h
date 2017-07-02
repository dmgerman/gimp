begin_unit|revision:0.9.5;language:C;cregit-version:0.0.1
begin_comment
comment|/* GIMP - The GNU Image Manipulation Program  * Copyright (C) 1995 Spencer Kimball and Peter Mattis  *  * gimpfiltertool-widgets.h  *  * This program is free software: you can redistribute it and/or modify  * it under the terms of the GNU General Public License as published by  * the Free Software Foundation; either version 3 of the License, or  * (at your option) any later version.  *  * This program is distributed in the hope that it will be useful,  * but WITHOUT ANY WARRANTY; without even the implied warranty of  * MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the  * GNU General Public License for more details.  *  * You should have received a copy of the GNU General Public License  * along with this program.  If not, see<http://www.gnu.org/licenses/>.  */
end_comment

begin_ifndef
ifndef|#
directive|ifndef
name|__GIMP_FILTER_TOOL_WIDGETS_H__
end_ifndef

begin_define
DECL|macro|__GIMP_FILTER_TOOL_WIDGETS_H__
define|#
directive|define
name|__GIMP_FILTER_TOOL_WIDGETS_H__
end_define

begin_include
include|#
directive|include
file|"widgets/gimppropgui.h"
end_include

begin_comment
comment|/* FIXME remove */
end_comment

begin_function_decl
name|GimpToolWidget
modifier|*
name|gimp_filter_tool_create_widget
parameter_list|(
name|GimpFilterTool
modifier|*
name|filter_tool
parameter_list|,
name|GimpControllerType
name|controller_type
parameter_list|,
name|GCallback
name|callback
parameter_list|,
name|gpointer
name|callback_data
parameter_list|,
name|GCallback
modifier|*
name|set_func
parameter_list|,
name|gpointer
modifier|*
name|set_func_data
parameter_list|)
function_decl|;
end_function_decl

begin_endif
endif|#
directive|endif
end_endif

begin_comment
comment|/* __GIMP_FILTER_TOOL_WIDGETS_H__ */
end_comment

end_unit

