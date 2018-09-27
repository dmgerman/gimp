begin_unit|revision:0.9.5;language:C;cregit-version:0.0.1
begin_comment
comment|/* GIMP - The GNU Image Manipulation Program  * Copyright (C) 1995 Spencer Kimball and Peter Mattis  *  * This program is free software: you can redistribute it and/or modify  * it under the terms of the GNU General Public License as published by  * the Free Software Foundation; either version 3 of the License, or  * (at your option) any later version.  *  * This program is distributed in the hope that it will be useful,  * but WITHOUT ANY WARRANTY; without even the implied warranty of  * MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the  * GNU General Public License for more details.  *  * You should have received a copy of the GNU General Public License  * along with this program.  If not, see<https://www.gnu.org/licenses/>.  */
end_comment

begin_ifndef
ifndef|#
directive|ifndef
name|__TOOLS_TYPES_H__
end_ifndef

begin_define
DECL|macro|__TOOLS_TYPES_H__
define|#
directive|define
name|__TOOLS_TYPES_H__
end_define

begin_include
include|#
directive|include
file|"paint/paint-types.h"
end_include

begin_include
include|#
directive|include
file|"display/display-types.h"
end_include

begin_include
include|#
directive|include
file|"tools/tools-enums.h"
end_include

begin_macro
name|G_BEGIN_DECLS
end_macro

begin_typedef
DECL|typedef|GimpTool
typedef|typedef
name|struct
name|_GimpTool
name|GimpTool
typedef|;
end_typedef

begin_typedef
DECL|typedef|GimpToolControl
typedef|typedef
name|struct
name|_GimpToolControl
name|GimpToolControl
typedef|;
end_typedef

begin_typedef
DECL|typedef|GimpBrushTool
typedef|typedef
name|struct
name|_GimpBrushTool
name|GimpBrushTool
typedef|;
end_typedef

begin_typedef
DECL|typedef|GimpColorTool
typedef|typedef
name|struct
name|_GimpColorTool
name|GimpColorTool
typedef|;
end_typedef

begin_typedef
DECL|typedef|GimpDrawTool
typedef|typedef
name|struct
name|_GimpDrawTool
name|GimpDrawTool
typedef|;
end_typedef

begin_typedef
DECL|typedef|GimpFilterTool
typedef|typedef
name|struct
name|_GimpFilterTool
name|GimpFilterTool
typedef|;
end_typedef

begin_typedef
DECL|typedef|GimpGenericTransformTool
typedef|typedef
name|struct
name|_GimpGenericTransformTool
name|GimpGenericTransformTool
typedef|;
end_typedef

begin_typedef
DECL|typedef|GimpPaintTool
typedef|typedef
name|struct
name|_GimpPaintTool
name|GimpPaintTool
typedef|;
end_typedef

begin_typedef
DECL|typedef|GimpTransformGridTool
typedef|typedef
name|struct
name|_GimpTransformGridTool
name|GimpTransformGridTool
typedef|;
end_typedef

begin_typedef
DECL|typedef|GimpTransformTool
typedef|typedef
name|struct
name|_GimpTransformTool
name|GimpTransformTool
typedef|;
end_typedef

begin_typedef
DECL|typedef|GimpColorOptions
typedef|typedef
name|struct
name|_GimpColorOptions
name|GimpColorOptions
typedef|;
end_typedef

begin_typedef
DECL|typedef|GimpFilterOptions
typedef|typedef
name|struct
name|_GimpFilterOptions
name|GimpFilterOptions
typedef|;
end_typedef

begin_comment
comment|/*  functions  */
end_comment

begin_typedef
DECL|typedef|GimpToolRegisterCallback
typedef|typedef
name|void
function_decl|(
modifier|*
name|GimpToolRegisterCallback
function_decl|)
parameter_list|(
name|GType
name|tool_type
parameter_list|,
name|GType
name|tool_option_type
parameter_list|,
name|GimpToolOptionsGUIFunc
name|options_gui_func
parameter_list|,
name|GimpContextPropMask
name|context_props
parameter_list|,
specifier|const
name|gchar
modifier|*
name|identifier
parameter_list|,
specifier|const
name|gchar
modifier|*
name|label
parameter_list|,
specifier|const
name|gchar
modifier|*
name|tooltip
parameter_list|,
specifier|const
name|gchar
modifier|*
name|menu_path
parameter_list|,
specifier|const
name|gchar
modifier|*
name|menu_accel
parameter_list|,
specifier|const
name|gchar
modifier|*
name|help_domain
parameter_list|,
specifier|const
name|gchar
modifier|*
name|help_data
parameter_list|,
specifier|const
name|gchar
modifier|*
name|icon_name
parameter_list|,
name|gpointer
name|register_data
parameter_list|)
function_decl|;
end_typedef

begin_typedef
DECL|typedef|GimpToolRegisterFunc
typedef|typedef
name|void
function_decl|(
modifier|*
name|GimpToolRegisterFunc
function_decl|)
parameter_list|(
name|GimpToolRegisterCallback
name|callback
parameter_list|,
name|gpointer
name|register_data
parameter_list|)
function_decl|;
end_typedef

begin_macro
name|G_END_DECLS
end_macro

begin_endif
endif|#
directive|endif
end_endif

begin_comment
comment|/* __TOOLS_TYPES_H__ */
end_comment

end_unit

