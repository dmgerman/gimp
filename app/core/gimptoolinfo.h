begin_unit|revision:0.9.5;language:C;cregit-version:0.0.1
begin_comment
comment|/* GIMP - The GNU Image Manipulation Program  * Copyright (C) 1995 Spencer Kimball and Peter Mattis  *  * This program is free software: you can redistribute it and/or modify  * it under the terms of the GNU General Public License as published by  * the Free Software Foundation; either version 3 of the License, or  * (at your option) any later version.  *  * This program is distributed in the hope that it will be useful,  * but WITHOUT ANY WARRANTY; without even the implied warranty of  * MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the  * GNU General Public License for more details.  *  * You should have received a copy of the GNU General Public License  * along with this program.  If not, see<http://www.gnu.org/licenses/>.  */
end_comment

begin_ifndef
ifndef|#
directive|ifndef
name|__GIMP_TOOL_INFO_H__
end_ifndef

begin_define
DECL|macro|__GIMP_TOOL_INFO_H__
define|#
directive|define
name|__GIMP_TOOL_INFO_H__
end_define

begin_include
include|#
directive|include
file|"gimpdata.h"
end_include

begin_define
DECL|macro|GIMP_TYPE_TOOL_INFO
define|#
directive|define
name|GIMP_TYPE_TOOL_INFO
value|(gimp_tool_info_get_type ())
end_define

begin_define
DECL|macro|GIMP_TOOL_INFO (obj)
define|#
directive|define
name|GIMP_TOOL_INFO
parameter_list|(
name|obj
parameter_list|)
value|(G_TYPE_CHECK_INSTANCE_CAST ((obj), GIMP_TYPE_TOOL_INFO, GimpToolInfo))
end_define

begin_define
DECL|macro|GIMP_TOOL_INFO_CLASS (klass)
define|#
directive|define
name|GIMP_TOOL_INFO_CLASS
parameter_list|(
name|klass
parameter_list|)
value|(G_TYPE_CHECK_CLASS_CAST ((klass), GIMP_TYPE_TOOL_INFO, GimpToolInfoClass))
end_define

begin_define
DECL|macro|GIMP_IS_TOOL_INFO (obj)
define|#
directive|define
name|GIMP_IS_TOOL_INFO
parameter_list|(
name|obj
parameter_list|)
value|(G_TYPE_CHECK_INSTANCE_TYPE ((obj), GIMP_TYPE_TOOL_INFO))
end_define

begin_define
DECL|macro|GIMP_IS_TOOL_INFO_CLASS (klass)
define|#
directive|define
name|GIMP_IS_TOOL_INFO_CLASS
parameter_list|(
name|klass
parameter_list|)
value|(G_TYPE_CHECK_CLASS_TYPE ((klass), GIMP_TYPE_TOOL_INFO))
end_define

begin_define
DECL|macro|GIMP_TOOL_INFO_GET_CLASS (obj)
define|#
directive|define
name|GIMP_TOOL_INFO_GET_CLASS
parameter_list|(
name|obj
parameter_list|)
value|(G_TYPE_INSTANCE_GET_CLASS ((obj), GIMP_TYPE_TOOL_INFO, GimpToolInfoClass))
end_define

begin_typedef
DECL|typedef|GimpToolInfoClass
typedef|typedef
name|struct
name|_GimpToolInfoClass
name|GimpToolInfoClass
typedef|;
end_typedef

begin_struct
DECL|struct|_GimpToolInfo
struct|struct
name|_GimpToolInfo
block|{
DECL|member|parent_instance
name|GimpViewable
name|parent_instance
decl_stmt|;
DECL|member|gimp
name|Gimp
modifier|*
name|gimp
decl_stmt|;
DECL|member|tool_type
name|GType
name|tool_type
decl_stmt|;
DECL|member|tool_options_type
name|GType
name|tool_options_type
decl_stmt|;
DECL|member|context_props
name|GimpContextPropMask
name|context_props
decl_stmt|;
DECL|member|blurb
name|gchar
modifier|*
name|blurb
decl_stmt|;
DECL|member|help
name|gchar
modifier|*
name|help
decl_stmt|;
DECL|member|menu_path
name|gchar
modifier|*
name|menu_path
decl_stmt|;
DECL|member|menu_accel
name|gchar
modifier|*
name|menu_accel
decl_stmt|;
DECL|member|help_domain
name|gchar
modifier|*
name|help_domain
decl_stmt|;
DECL|member|help_id
name|gchar
modifier|*
name|help_id
decl_stmt|;
DECL|member|visible
name|gboolean
name|visible
decl_stmt|;
DECL|member|tool_options
name|GimpToolOptions
modifier|*
name|tool_options
decl_stmt|;
DECL|member|paint_info
name|GimpPaintInfo
modifier|*
name|paint_info
decl_stmt|;
DECL|member|presets
name|GimpContainer
modifier|*
name|presets
decl_stmt|;
block|}
struct|;
end_struct

begin_struct
DECL|struct|_GimpToolInfoClass
struct|struct
name|_GimpToolInfoClass
block|{
DECL|member|parent_class
name|GimpViewableClass
name|parent_class
decl_stmt|;
block|}
struct|;
end_struct

begin_decl_stmt
name|GType
name|gimp_tool_info_get_type
argument_list|(
name|void
argument_list|)
name|G_GNUC_CONST
decl_stmt|;
end_decl_stmt

begin_function_decl
name|GimpToolInfo
modifier|*
name|gimp_tool_info_new
parameter_list|(
name|Gimp
modifier|*
name|gimp
parameter_list|,
name|GType
name|tool_type
parameter_list|,
name|GType
name|tool_options_type
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
name|blurb
parameter_list|,
specifier|const
name|gchar
modifier|*
name|help
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
name|help_id
parameter_list|,
specifier|const
name|gchar
modifier|*
name|paint_core_name
parameter_list|,
specifier|const
name|gchar
modifier|*
name|stock_id
parameter_list|)
function_decl|;
end_function_decl

begin_function_decl
name|void
name|gimp_tool_info_set_standard
parameter_list|(
name|Gimp
modifier|*
name|gimp
parameter_list|,
name|GimpToolInfo
modifier|*
name|tool_info
parameter_list|)
function_decl|;
end_function_decl

begin_function_decl
name|GimpToolInfo
modifier|*
name|gimp_tool_info_get_standard
parameter_list|(
name|Gimp
modifier|*
name|gimp
parameter_list|)
function_decl|;
end_function_decl

begin_function_decl
name|gchar
modifier|*
name|gimp_tool_info_build_options_filename
parameter_list|(
name|GimpToolInfo
modifier|*
name|tool_info
parameter_list|,
specifier|const
name|gchar
modifier|*
name|suffix
parameter_list|)
function_decl|;
end_function_decl

begin_endif
endif|#
directive|endif
end_endif

begin_comment
comment|/*  __GIMP_TOOL_INFO_H__  */
end_comment

end_unit

