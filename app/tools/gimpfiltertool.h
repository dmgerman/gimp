begin_unit|revision:0.9.5;language:C;cregit-version:0.0.1
begin_comment
comment|/* GIMP - The GNU Image Manipulation Program  * Copyright (C) 1995 Spencer Kimball and Peter Mattis  *  * This program is free software: you can redistribute it and/or modify  * it under the terms of the GNU General Public License as published by  * the Free Software Foundation; either version 3 of the License, or  * (at your option) any later version.  *  * This program is distributed in the hope that it will be useful,  * but WITHOUT ANY WARRANTY; without even the implied warranty of  * MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the  * GNU General Public License for more details.  *  * You should have received a copy of the GNU General Public License  * along with this program.  If not, see<https://www.gnu.org/licenses/>.  */
end_comment

begin_ifndef
ifndef|#
directive|ifndef
name|__GIMP_FILTER_TOOL_H__
end_ifndef

begin_define
DECL|macro|__GIMP_FILTER_TOOL_H__
define|#
directive|define
name|__GIMP_FILTER_TOOL_H__
end_define

begin_include
include|#
directive|include
file|"gimpcolortool.h"
end_include

begin_define
DECL|macro|GIMP_TYPE_FILTER_TOOL
define|#
directive|define
name|GIMP_TYPE_FILTER_TOOL
value|(gimp_filter_tool_get_type ())
end_define

begin_define
DECL|macro|GIMP_FILTER_TOOL (obj)
define|#
directive|define
name|GIMP_FILTER_TOOL
parameter_list|(
name|obj
parameter_list|)
value|(G_TYPE_CHECK_INSTANCE_CAST ((obj), GIMP_TYPE_FILTER_TOOL, GimpFilterTool))
end_define

begin_define
DECL|macro|GIMP_FILTER_TOOL_CLASS (klass)
define|#
directive|define
name|GIMP_FILTER_TOOL_CLASS
parameter_list|(
name|klass
parameter_list|)
value|(G_TYPE_CHECK_CLASS_CAST ((klass), GIMP_TYPE_FILTER_TOOL, GimpFilterToolClass))
end_define

begin_define
DECL|macro|GIMP_IS_FILTER_TOOL (obj)
define|#
directive|define
name|GIMP_IS_FILTER_TOOL
parameter_list|(
name|obj
parameter_list|)
value|(G_TYPE_CHECK_INSTANCE_TYPE ((obj), GIMP_TYPE_FILTER_TOOL))
end_define

begin_define
DECL|macro|GIMP_IS_FILTER_TOOL_CLASS (klass)
define|#
directive|define
name|GIMP_IS_FILTER_TOOL_CLASS
parameter_list|(
name|klass
parameter_list|)
value|(G_TYPE_CHECK_CLASS_TYPE ((klass), GIMP_TYPE_FILTER_TOOL))
end_define

begin_define
DECL|macro|GIMP_FILTER_TOOL_GET_CLASS (obj)
define|#
directive|define
name|GIMP_FILTER_TOOL_GET_CLASS
parameter_list|(
name|obj
parameter_list|)
value|(G_TYPE_INSTANCE_GET_CLASS ((obj), GIMP_TYPE_FILTER_TOOL, GimpFilterToolClass))
end_define

begin_define
DECL|macro|GIMP_FILTER_TOOL_GET_OPTIONS (t)
define|#
directive|define
name|GIMP_FILTER_TOOL_GET_OPTIONS
parameter_list|(
name|t
parameter_list|)
value|(GIMP_FILTER_OPTIONS (gimp_tool_get_options (GIMP_TOOL (t))))
end_define

begin_typedef
DECL|typedef|GimpFilterToolClass
typedef|typedef
name|struct
name|_GimpFilterToolClass
name|GimpFilterToolClass
typedef|;
end_typedef

begin_struct
DECL|struct|_GimpFilterTool
struct|struct
name|_GimpFilterTool
block|{
DECL|member|parent_instance
name|GimpColorTool
name|parent_instance
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
DECL|member|settings
name|GimpContainer
modifier|*
name|settings
decl_stmt|;
DECL|member|description
name|gchar
modifier|*
name|description
decl_stmt|;
DECL|member|has_settings
name|gboolean
name|has_settings
decl_stmt|;
DECL|member|filter
name|GimpDrawableFilter
modifier|*
name|filter
decl_stmt|;
DECL|member|preview_guide
name|GimpGuide
modifier|*
name|preview_guide
decl_stmt|;
DECL|member|pick_identifier
name|gpointer
name|pick_identifier
decl_stmt|;
DECL|member|pick_abyss
name|gboolean
name|pick_abyss
decl_stmt|;
comment|/* dialog */
DECL|member|overlay
name|gboolean
name|overlay
decl_stmt|;
DECL|member|gui
name|GimpToolGui
modifier|*
name|gui
decl_stmt|;
DECL|member|settings_box
name|GtkWidget
modifier|*
name|settings_box
decl_stmt|;
DECL|member|controller_toggle
name|GtkWidget
modifier|*
name|controller_toggle
decl_stmt|;
DECL|member|region_combo
name|GtkWidget
modifier|*
name|region_combo
decl_stmt|;
DECL|member|active_picker
name|GtkWidget
modifier|*
name|active_picker
decl_stmt|;
comment|/* widget */
DECL|member|widget
name|GimpToolWidget
modifier|*
name|widget
decl_stmt|;
DECL|member|grab_widget
name|GimpToolWidget
modifier|*
name|grab_widget
decl_stmt|;
block|}
struct|;
end_struct

begin_struct
DECL|struct|_GimpFilterToolClass
struct|struct
name|_GimpFilterToolClass
block|{
DECL|member|parent_class
name|GimpColorToolClass
name|parent_class
decl_stmt|;
comment|/* virtual functions */
DECL|member|get_operation
name|gchar
modifier|*
function_decl|(
modifier|*
name|get_operation
function_decl|)
parameter_list|(
name|GimpFilterTool
modifier|*
name|filter_tool
parameter_list|,
name|gchar
modifier|*
modifier|*
name|description
parameter_list|)
function_decl|;
DECL|member|dialog
name|void
function_decl|(
modifier|*
name|dialog
function_decl|)
parameter_list|(
name|GimpFilterTool
modifier|*
name|filter_tool
parameter_list|)
function_decl|;
DECL|member|reset
name|void
function_decl|(
modifier|*
name|reset
function_decl|)
parameter_list|(
name|GimpFilterTool
modifier|*
name|filter_tool
parameter_list|)
function_decl|;
DECL|member|set_config
name|void
function_decl|(
modifier|*
name|set_config
function_decl|)
parameter_list|(
name|GimpFilterTool
modifier|*
name|filter_tool
parameter_list|,
name|GimpConfig
modifier|*
name|config
parameter_list|)
function_decl|;
DECL|member|config_notify
name|void
function_decl|(
modifier|*
name|config_notify
function_decl|)
parameter_list|(
name|GimpFilterTool
modifier|*
name|filter_tool
parameter_list|,
name|GimpConfig
modifier|*
name|config
parameter_list|,
specifier|const
name|GParamSpec
modifier|*
name|pspec
parameter_list|)
function_decl|;
DECL|member|settings_import
name|gboolean
function_decl|(
modifier|*
name|settings_import
function_decl|)
parameter_list|(
name|GimpFilterTool
modifier|*
name|filter_tool
parameter_list|,
name|GInputStream
modifier|*
name|input
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
name|GimpFilterTool
modifier|*
name|filter_tool
parameter_list|,
name|GOutputStream
modifier|*
name|output
parameter_list|,
name|GError
modifier|*
modifier|*
name|error
parameter_list|)
function_decl|;
DECL|member|region_changed
name|void
function_decl|(
modifier|*
name|region_changed
function_decl|)
parameter_list|(
name|GimpFilterTool
modifier|*
name|filter_tool
parameter_list|)
function_decl|;
DECL|member|color_picked
name|void
function_decl|(
modifier|*
name|color_picked
function_decl|)
parameter_list|(
name|GimpFilterTool
modifier|*
name|filter_tool
parameter_list|,
name|gpointer
name|identifier
parameter_list|,
name|gdouble
name|x
parameter_list|,
name|gdouble
name|y
parameter_list|,
specifier|const
name|Babl
modifier|*
name|sample_format
parameter_list|,
specifier|const
name|GimpRGB
modifier|*
name|color
parameter_list|)
function_decl|;
block|}
struct|;
end_struct

begin_decl_stmt
name|GType
name|gimp_filter_tool_get_type
argument_list|(
name|void
argument_list|)
name|G_GNUC_CONST
decl_stmt|;
end_decl_stmt

begin_function_decl
name|void
name|gimp_filter_tool_get_operation
parameter_list|(
name|GimpFilterTool
modifier|*
name|filter_tool
parameter_list|)
function_decl|;
end_function_decl

begin_function_decl
name|void
name|gimp_filter_tool_set_config
parameter_list|(
name|GimpFilterTool
modifier|*
name|filter_tool
parameter_list|,
name|GimpConfig
modifier|*
name|config
parameter_list|)
function_decl|;
end_function_decl

begin_function_decl
name|void
name|gimp_filter_tool_edit_as
parameter_list|(
name|GimpFilterTool
modifier|*
name|filter_tool
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

begin_function_decl
name|gboolean
name|gimp_filter_tool_on_guide
parameter_list|(
name|GimpFilterTool
modifier|*
name|filter_tool
parameter_list|,
specifier|const
name|GimpCoords
modifier|*
name|coords
parameter_list|,
name|GimpDisplay
modifier|*
name|display
parameter_list|)
function_decl|;
end_function_decl

begin_function_decl
name|GtkWidget
modifier|*
name|gimp_filter_tool_dialog_get_vbox
parameter_list|(
name|GimpFilterTool
modifier|*
name|filter_tool
parameter_list|)
function_decl|;
end_function_decl

begin_function_decl
name|void
name|gimp_filter_tool_enable_color_picking
parameter_list|(
name|GimpFilterTool
modifier|*
name|filter_tool
parameter_list|,
name|gpointer
name|identifier
parameter_list|,
name|gboolean
name|pick_abyss
parameter_list|)
function_decl|;
end_function_decl

begin_function_decl
name|void
name|gimp_filter_tool_disable_color_picking
parameter_list|(
name|GimpFilterTool
modifier|*
name|filter_tool
parameter_list|)
function_decl|;
end_function_decl

begin_function_decl
name|GtkWidget
modifier|*
name|gimp_filter_tool_add_color_picker
parameter_list|(
name|GimpFilterTool
modifier|*
name|filter_tool
parameter_list|,
name|gpointer
name|identifier
parameter_list|,
specifier|const
name|gchar
modifier|*
name|icon_name
parameter_list|,
specifier|const
name|gchar
modifier|*
name|tooltip
parameter_list|,
name|gboolean
name|pick_abyss
parameter_list|,
name|GimpPickerCallback
name|callback
parameter_list|,
name|gpointer
name|callback_data
parameter_list|)
function_decl|;
end_function_decl

begin_function_decl
name|GCallback
name|gimp_filter_tool_add_controller
parameter_list|(
name|GimpFilterTool
modifier|*
name|filter_tool
parameter_list|,
name|GimpControllerType
name|controller_type
parameter_list|,
specifier|const
name|gchar
modifier|*
name|status_title
parameter_list|,
name|GCallback
name|callback
parameter_list|,
name|gpointer
name|callback_data
parameter_list|,
name|gpointer
modifier|*
name|set_func_data
parameter_list|)
function_decl|;
end_function_decl

begin_function_decl
name|void
name|gimp_filter_tool_set_widget
parameter_list|(
name|GimpFilterTool
modifier|*
name|filter_tool
parameter_list|,
name|GimpToolWidget
modifier|*
name|widget
parameter_list|)
function_decl|;
end_function_decl

begin_function_decl
name|gboolean
name|gimp_filter_tool_get_drawable_area
parameter_list|(
name|GimpFilterTool
modifier|*
name|filter_tool
parameter_list|,
name|gint
modifier|*
name|drawable_offset_x
parameter_list|,
name|gint
modifier|*
name|drawable_offset_y
parameter_list|,
name|GeglRectangle
modifier|*
name|drawable_area
parameter_list|)
function_decl|;
end_function_decl

begin_endif
endif|#
directive|endif
end_endif

begin_comment
comment|/* __GIMP_FILTER_TOOL_H__ */
end_comment

end_unit

