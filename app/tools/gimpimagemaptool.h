begin_unit|revision:0.9.5;language:C;cregit-version:0.0.1
begin_comment
comment|/* GIMP - The GNU Image Manipulation Program  * Copyright (C) 1995 Spencer Kimball and Peter Mattis  *  * This program is free software: you can redistribute it and/or modify  * it under the terms of the GNU General Public License as published by  * the Free Software Foundation; either version 3 of the License, or  * (at your option) any later version.  *  * This program is distributed in the hope that it will be useful,  * but WITHOUT ANY WARRANTY; without even the implied warranty of  * MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the  * GNU General Public License for more details.  *  * You should have received a copy of the GNU General Public License  * along with this program.  If not, see<http://www.gnu.org/licenses/>.  */
end_comment

begin_ifndef
ifndef|#
directive|ifndef
name|__GIMP_IMAGE_MAP_TOOL_H__
end_ifndef

begin_define
DECL|macro|__GIMP_IMAGE_MAP_TOOL_H__
define|#
directive|define
name|__GIMP_IMAGE_MAP_TOOL_H__
end_define

begin_include
include|#
directive|include
file|"gimpcolortool.h"
end_include

begin_define
DECL|macro|GIMP_TYPE_IMAGE_MAP_TOOL
define|#
directive|define
name|GIMP_TYPE_IMAGE_MAP_TOOL
value|(gimp_image_map_tool_get_type ())
end_define

begin_define
DECL|macro|GIMP_IMAGE_MAP_TOOL (obj)
define|#
directive|define
name|GIMP_IMAGE_MAP_TOOL
parameter_list|(
name|obj
parameter_list|)
value|(G_TYPE_CHECK_INSTANCE_CAST ((obj), GIMP_TYPE_IMAGE_MAP_TOOL, GimpImageMapTool))
end_define

begin_define
DECL|macro|GIMP_IMAGE_MAP_TOOL_CLASS (klass)
define|#
directive|define
name|GIMP_IMAGE_MAP_TOOL_CLASS
parameter_list|(
name|klass
parameter_list|)
value|(G_TYPE_CHECK_CLASS_CAST ((klass), GIMP_TYPE_IMAGE_MAP_TOOL, GimpImageMapToolClass))
end_define

begin_define
DECL|macro|GIMP_IS_IMAGE_MAP_TOOL (obj)
define|#
directive|define
name|GIMP_IS_IMAGE_MAP_TOOL
parameter_list|(
name|obj
parameter_list|)
value|(G_TYPE_CHECK_INSTANCE_TYPE ((obj), GIMP_TYPE_IMAGE_MAP_TOOL))
end_define

begin_define
DECL|macro|GIMP_IS_IMAGE_MAP_TOOL_CLASS (klass)
define|#
directive|define
name|GIMP_IS_IMAGE_MAP_TOOL_CLASS
parameter_list|(
name|klass
parameter_list|)
value|(G_TYPE_CHECK_CLASS_TYPE ((klass), GIMP_TYPE_IMAGE_MAP_TOOL))
end_define

begin_define
DECL|macro|GIMP_IMAGE_MAP_TOOL_GET_CLASS (obj)
define|#
directive|define
name|GIMP_IMAGE_MAP_TOOL_GET_CLASS
parameter_list|(
name|obj
parameter_list|)
value|(G_TYPE_INSTANCE_GET_CLASS ((obj), GIMP_TYPE_IMAGE_MAP_TOOL, GimpImageMapToolClass))
end_define

begin_define
DECL|macro|GIMP_IMAGE_MAP_TOOL_GET_OPTIONS (t)
define|#
directive|define
name|GIMP_IMAGE_MAP_TOOL_GET_OPTIONS
parameter_list|(
name|t
parameter_list|)
value|(GIMP_IMAGE_MAP_OPTIONS (gimp_tool_get_options (GIMP_TOOL (t))))
end_define

begin_typedef
DECL|typedef|GimpImageMapToolClass
typedef|typedef
name|struct
name|_GimpImageMapToolClass
name|GimpImageMapToolClass
typedef|;
end_typedef

begin_struct
DECL|struct|_GimpImageMapTool
struct|struct
name|_GimpImageMapTool
block|{
DECL|member|parent_instance
name|GimpColorTool
name|parent_instance
decl_stmt|;
DECL|member|drawable
name|GimpDrawable
modifier|*
name|drawable
decl_stmt|;
DECL|member|operation
name|GeglNode
modifier|*
name|operation
decl_stmt|;
DECL|member|config
name|GObject
modifier|*
name|config
decl_stmt|;
DECL|member|default_config
name|GObject
modifier|*
name|default_config
decl_stmt|;
DECL|member|apply_func
name|GimpImageMapApplyFunc
name|apply_func
decl_stmt|;
DECL|member|apply_data
name|gpointer
name|apply_data
decl_stmt|;
DECL|member|image_map
name|GimpImageMap
modifier|*
name|image_map
decl_stmt|;
comment|/* dialog */
DECL|member|overlay
name|gboolean
name|overlay
decl_stmt|;
DECL|member|shell
name|GtkWidget
modifier|*
name|shell
decl_stmt|;
DECL|member|main_vbox
name|GtkWidget
modifier|*
name|main_vbox
decl_stmt|;
DECL|member|settings_box
name|GtkWidget
modifier|*
name|settings_box
decl_stmt|;
DECL|member|label_group
name|GtkSizeGroup
modifier|*
name|label_group
decl_stmt|;
block|}
struct|;
end_struct

begin_struct
DECL|struct|_GimpImageMapToolClass
struct|struct
name|_GimpImageMapToolClass
block|{
DECL|member|parent_class
name|GimpColorToolClass
name|parent_class
decl_stmt|;
DECL|member|shell_desc
specifier|const
name|gchar
modifier|*
name|shell_desc
decl_stmt|;
DECL|member|settings_name
specifier|const
name|gchar
modifier|*
name|settings_name
decl_stmt|;
DECL|member|import_dialog_title
specifier|const
name|gchar
modifier|*
name|import_dialog_title
decl_stmt|;
DECL|member|export_dialog_title
specifier|const
name|gchar
modifier|*
name|export_dialog_title
decl_stmt|;
DECL|member|recent_settings
name|GimpContainer
modifier|*
name|recent_settings
decl_stmt|;
comment|/* virtual functions */
DECL|member|get_operation
name|GeglNode
modifier|*
function_decl|(
modifier|*
name|get_operation
function_decl|)
parameter_list|(
name|GimpImageMapTool
modifier|*
name|image_map_tool
parameter_list|,
name|GObject
modifier|*
modifier|*
name|config
parameter_list|)
function_decl|;
DECL|member|map
name|void
function_decl|(
modifier|*
name|map
function_decl|)
parameter_list|(
name|GimpImageMapTool
modifier|*
name|image_map_tool
parameter_list|)
function_decl|;
DECL|member|dialog
name|void
function_decl|(
modifier|*
name|dialog
function_decl|)
parameter_list|(
name|GimpImageMapTool
modifier|*
name|image_map_tool
parameter_list|)
function_decl|;
DECL|member|reset
name|void
function_decl|(
modifier|*
name|reset
function_decl|)
parameter_list|(
name|GimpImageMapTool
modifier|*
name|image_map_tool
parameter_list|)
function_decl|;
DECL|member|settings_import
name|gboolean
function_decl|(
modifier|*
name|settings_import
function_decl|)
parameter_list|(
name|GimpImageMapTool
modifier|*
name|image_map_tool
parameter_list|,
specifier|const
name|gchar
modifier|*
name|filename
parameter_list|,
name|GError
modifier|*
modifier|*
name|error
parameter_list|)
function_decl|;
DECL|member|settings_export
name|gboolean
function_decl|(
modifier|*
name|settings_export
function_decl|)
parameter_list|(
name|GimpImageMapTool
modifier|*
name|image_map_tool
parameter_list|,
specifier|const
name|gchar
modifier|*
name|filename
parameter_list|,
name|GError
modifier|*
modifier|*
name|error
parameter_list|)
function_decl|;
block|}
struct|;
end_struct

begin_decl_stmt
name|GType
name|gimp_image_map_tool_get_type
argument_list|(
name|void
argument_list|)
name|G_GNUC_CONST
decl_stmt|;
end_decl_stmt

begin_function_decl
name|void
name|gimp_image_map_tool_preview
parameter_list|(
name|GimpImageMapTool
modifier|*
name|image_map_tool
parameter_list|)
function_decl|;
end_function_decl

begin_comment
comment|/* temp hack for the gegl tool */
end_comment

begin_function_decl
name|void
name|gimp_image_map_tool_create_map
parameter_list|(
name|GimpImageMapTool
modifier|*
name|image_map_tool
parameter_list|)
function_decl|;
end_function_decl

begin_function_decl
name|void
name|gimp_image_map_tool_edit_as
parameter_list|(
name|GimpImageMapTool
modifier|*
name|image_map_tool
parameter_list|,
specifier|const
name|gchar
modifier|*
name|new_tool_id
parameter_list|,
name|GimpConfig
modifier|*
name|config
parameter_list|)
function_decl|;
end_function_decl

begin_comment
comment|/* accessors for derived classes */
end_comment

begin_function_decl
name|GtkWidget
modifier|*
name|gimp_image_map_tool_dialog_get_vbox
parameter_list|(
name|GimpImageMapTool
modifier|*
name|tool
parameter_list|)
function_decl|;
end_function_decl

begin_function_decl
name|GtkSizeGroup
modifier|*
name|gimp_image_map_tool_dialog_get_label_group
parameter_list|(
name|GimpImageMapTool
modifier|*
name|tool
parameter_list|)
function_decl|;
end_function_decl

begin_endif
endif|#
directive|endif
end_endif

begin_comment
comment|/*  __GIMP_IMAGE_MAP_TOOL_H__  */
end_comment

end_unit

