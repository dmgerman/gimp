begin_unit|revision:0.9.5;language:C;cregit-version:0.0.1
begin_comment
comment|/* GIMP - The GNU Image Manipulation Program  * Copyright (C) 1995-1999 Spencer Kimball and Peter Mattis  *  * This program is free software: you can redistribute it and/or modify  * it under the terms of the GNU General Public License as published by  * the Free Software Foundation; either version 3 of the License, or  * (at your option) any later version.  *  * This program is distributed in the hope that it will be useful,  * but WITHOUT ANY WARRANTY; without even the implied warranty of  * MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the  * GNU General Public License for more details.  *  * You should have received a copy of the GNU General Public License  * along with this program.  If not, see<http://www.gnu.org/licenses/>.  */
end_comment

begin_ifndef
ifndef|#
directive|ifndef
name|__GIMP_TOOL_PRESET_H__
end_ifndef

begin_define
DECL|macro|__GIMP_TOOL_PRESET_H__
define|#
directive|define
name|__GIMP_TOOL_PRESET_H__
end_define

begin_include
include|#
directive|include
file|"gimpdata.h"
end_include

begin_define
DECL|macro|GIMP_TYPE_TOOL_PRESET
define|#
directive|define
name|GIMP_TYPE_TOOL_PRESET
value|(gimp_tool_preset_get_type ())
end_define

begin_define
DECL|macro|GIMP_TOOL_PRESET (obj)
define|#
directive|define
name|GIMP_TOOL_PRESET
parameter_list|(
name|obj
parameter_list|)
value|(G_TYPE_CHECK_INSTANCE_CAST ((obj), GIMP_TYPE_TOOL_PRESET, GimpToolPreset))
end_define

begin_define
DECL|macro|GIMP_TOOL_PRESET_CLASS (klass)
define|#
directive|define
name|GIMP_TOOL_PRESET_CLASS
parameter_list|(
name|klass
parameter_list|)
value|(G_TYPE_CHECK_CLASS_CAST ((klass), GIMP_TYPE_TOOL_PRESET, GimpToolPresetClass))
end_define

begin_define
DECL|macro|GIMP_IS_TOOL_PRESET (obj)
define|#
directive|define
name|GIMP_IS_TOOL_PRESET
parameter_list|(
name|obj
parameter_list|)
value|(G_TYPE_CHECK_INSTANCE_TYPE ((obj), GIMP_TYPE_TOOL_PRESET))
end_define

begin_define
DECL|macro|GIMP_IS_TOOL_PRESET_CLASS (klass)
define|#
directive|define
name|GIMP_IS_TOOL_PRESET_CLASS
parameter_list|(
name|klass
parameter_list|)
value|(G_TYPE_CHECK_CLASS_TYPE ((klass), GIMP_TYPE_TOOL_PRESET))
end_define

begin_define
DECL|macro|GIMP_TOOL_PRESET_GET_CLASS (obj)
define|#
directive|define
name|GIMP_TOOL_PRESET_GET_CLASS
parameter_list|(
name|obj
parameter_list|)
value|(G_TYPE_INSTANCE_GET_CLASS ((obj), GIMP_TYPE_TOOL_PRESET, GimpToolPresetClass))
end_define

begin_typedef
DECL|typedef|GimpToolPresetClass
typedef|typedef
name|struct
name|_GimpToolPresetClass
name|GimpToolPresetClass
typedef|;
end_typedef

begin_struct
DECL|struct|_GimpToolPreset
struct|struct
name|_GimpToolPreset
block|{
DECL|member|parent_instance
name|GimpData
name|parent_instance
decl_stmt|;
DECL|member|gimp
name|Gimp
modifier|*
name|gimp
decl_stmt|;
DECL|member|tool_options
name|GimpToolOptions
modifier|*
name|tool_options
decl_stmt|;
DECL|member|use_fg_bg
name|gboolean
name|use_fg_bg
decl_stmt|;
DECL|member|use_brush
name|gboolean
name|use_brush
decl_stmt|;
DECL|member|use_dynamics
name|gboolean
name|use_dynamics
decl_stmt|;
DECL|member|use_gradient
name|gboolean
name|use_gradient
decl_stmt|;
DECL|member|use_pattern
name|gboolean
name|use_pattern
decl_stmt|;
DECL|member|use_palette
name|gboolean
name|use_palette
decl_stmt|;
DECL|member|use_font
name|gboolean
name|use_font
decl_stmt|;
block|}
struct|;
end_struct

begin_struct
DECL|struct|_GimpToolPresetClass
struct|struct
name|_GimpToolPresetClass
block|{
DECL|member|parent_class
name|GimpDataClass
name|parent_class
decl_stmt|;
block|}
struct|;
end_struct

begin_decl_stmt
name|GType
name|gimp_tool_preset_get_type
argument_list|(
name|void
argument_list|)
name|G_GNUC_CONST
decl_stmt|;
end_decl_stmt

begin_function_decl
name|GimpData
modifier|*
name|gimp_tool_preset_new
parameter_list|(
name|GimpContext
modifier|*
name|context
parameter_list|,
specifier|const
name|gchar
modifier|*
name|name
parameter_list|)
function_decl|;
end_function_decl

begin_function_decl
name|GimpContextPropMask
name|gimp_tool_preset_get_prop_mask
parameter_list|(
name|GimpToolPreset
modifier|*
name|preset
parameter_list|)
function_decl|;
end_function_decl

begin_endif
endif|#
directive|endif
end_endif

begin_comment
comment|/*  __GIMP_TOOL_PRESET_H__  */
end_comment

end_unit

