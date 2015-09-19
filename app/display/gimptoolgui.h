begin_unit|revision:0.9.5;language:C;cregit-version:0.0.1
begin_comment
comment|/* GIMP - The GNU Image Manipulation Program  * Copyright (C) 1995 Spencer Kimball and Peter Mattis  *  * gimptoolgui.h  * Copyright (C) 2013  Michael Natterer<mitch@gimp.org>  *  * This program is free software: you can redistribute it and/or modify  * it under the terms of the GNU General Public License as published by  * the Free Software Foundation; either version 3 of the License, or  * (at your option) any later version.  *  * This program is distributed in the hope that it will be useful,  * but WITHOUT ANY WARRANTY; without even the implied warranty of  * MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the  * GNU General Public License for more details.  *  * You should have received a copy of the GNU General Public License  * along with this program.  If not, see<http://www.gnu.org/licenses/>.  */
end_comment

begin_ifndef
ifndef|#
directive|ifndef
name|__GIMP_TOOL_GUI_H__
end_ifndef

begin_define
DECL|macro|__GIMP_TOOL_GUI_H__
define|#
directive|define
name|__GIMP_TOOL_GUI_H__
end_define

begin_include
include|#
directive|include
file|"core/gimpobject.h"
end_include

begin_define
DECL|macro|GIMP_TYPE_TOOL_GUI
define|#
directive|define
name|GIMP_TYPE_TOOL_GUI
value|(gimp_tool_gui_get_type ())
end_define

begin_define
DECL|macro|GIMP_TOOL_GUI (obj)
define|#
directive|define
name|GIMP_TOOL_GUI
parameter_list|(
name|obj
parameter_list|)
value|(G_TYPE_CHECK_INSTANCE_CAST ((obj), GIMP_TYPE_TOOL_GUI, GimpToolGui))
end_define

begin_define
DECL|macro|GIMP_TOOL_GUI_CLASS (klass)
define|#
directive|define
name|GIMP_TOOL_GUI_CLASS
parameter_list|(
name|klass
parameter_list|)
value|(G_TYPE_CHECK_CLASS_CAST ((klass), GIMP_TYPE_TOOL_GUI, GimpToolGuiClass))
end_define

begin_define
DECL|macro|GIMP_IS_TOOL_GUI (obj)
define|#
directive|define
name|GIMP_IS_TOOL_GUI
parameter_list|(
name|obj
parameter_list|)
value|(G_TYPE_CHECK_INSTANCE_TYPE ((obj), GIMP_TYPE_TOOL_GUI))
end_define

begin_define
DECL|macro|GIMP_IS_TOOL_GUI_CLASS (klass)
define|#
directive|define
name|GIMP_IS_TOOL_GUI_CLASS
parameter_list|(
name|klass
parameter_list|)
value|(G_TYPE_CHECK_CLASS_TYPE ((klass), GIMP_TYPE_TOOL_GUI))
end_define

begin_define
DECL|macro|GIMP_TOOL_GUI_GET_CLASS (obj)
define|#
directive|define
name|GIMP_TOOL_GUI_GET_CLASS
parameter_list|(
name|obj
parameter_list|)
value|(G_TYPE_INSTANCE_GET_CLASS ((obj), GIMP_TYPE_TOOL_GUI, GimpToolGuiClass))
end_define

begin_typedef
DECL|typedef|GimpToolGuiClass
typedef|typedef
name|struct
name|_GimpToolGuiClass
name|GimpToolGuiClass
typedef|;
end_typedef

begin_struct
DECL|struct|_GimpToolGui
struct|struct
name|_GimpToolGui
block|{
DECL|member|parent_instance
name|GimpObject
name|parent_instance
decl_stmt|;
block|}
struct|;
end_struct

begin_struct
DECL|struct|_GimpToolGuiClass
struct|struct
name|_GimpToolGuiClass
block|{
DECL|member|parent_instance
name|GimpObjectClass
name|parent_instance
decl_stmt|;
DECL|member|response
name|void
function_decl|(
modifier|*
name|response
function_decl|)
parameter_list|(
name|GimpToolGui
modifier|*
name|gui
parameter_list|,
name|gint
name|response_id
parameter_list|)
function_decl|;
block|}
struct|;
end_struct

begin_decl_stmt
name|GType
name|gimp_tool_gui_get_type
argument_list|(
name|void
argument_list|)
name|G_GNUC_CONST
decl_stmt|;
end_decl_stmt

begin_decl_stmt
name|GimpToolGui
modifier|*
name|gimp_tool_gui_new
argument_list|(
name|GimpToolInfo
operator|*
name|tool_info
argument_list|,
specifier|const
name|gchar
operator|*
name|description
argument_list|,
name|GdkScreen
operator|*
name|screen
argument_list|,
name|gint
name|monitor
argument_list|,
name|gboolean
name|overlay
argument_list|,
operator|...
argument_list|)
name|G_GNUC_NULL_TERMINATED
decl_stmt|;
end_decl_stmt

begin_function_decl
name|void
name|gimp_tool_gui_set_description
parameter_list|(
name|GimpToolGui
modifier|*
name|gui
parameter_list|,
specifier|const
name|gchar
modifier|*
name|description
parameter_list|)
function_decl|;
end_function_decl

begin_function_decl
name|void
name|gimp_tool_gui_set_icon_name
parameter_list|(
name|GimpToolGui
modifier|*
name|gui
parameter_list|,
specifier|const
name|gchar
modifier|*
name|icon_name
parameter_list|)
function_decl|;
end_function_decl

begin_function_decl
name|void
name|gimp_tool_gui_set_shell
parameter_list|(
name|GimpToolGui
modifier|*
name|gui
parameter_list|,
name|GimpDisplayShell
modifier|*
name|shell
parameter_list|)
function_decl|;
end_function_decl

begin_function_decl
name|void
name|gimp_tool_gui_set_viewable
parameter_list|(
name|GimpToolGui
modifier|*
name|gui
parameter_list|,
name|GimpViewable
modifier|*
name|viewable
parameter_list|)
function_decl|;
end_function_decl

begin_function_decl
name|GtkWidget
modifier|*
name|gimp_tool_gui_get_dialog
parameter_list|(
name|GimpToolGui
modifier|*
name|gui
parameter_list|)
function_decl|;
end_function_decl

begin_function_decl
name|GtkWidget
modifier|*
name|gimp_tool_gui_get_vbox
parameter_list|(
name|GimpToolGui
modifier|*
name|gui
parameter_list|)
function_decl|;
end_function_decl

begin_function_decl
name|gboolean
name|gimp_tool_gui_get_visible
parameter_list|(
name|GimpToolGui
modifier|*
name|gui
parameter_list|)
function_decl|;
end_function_decl

begin_function_decl
name|void
name|gimp_tool_gui_show
parameter_list|(
name|GimpToolGui
modifier|*
name|gui
parameter_list|)
function_decl|;
end_function_decl

begin_function_decl
name|void
name|gimp_tool_gui_hide
parameter_list|(
name|GimpToolGui
modifier|*
name|gui
parameter_list|)
function_decl|;
end_function_decl

begin_function_decl
name|void
name|gimp_tool_gui_set_overlay
parameter_list|(
name|GimpToolGui
modifier|*
name|gui
parameter_list|,
name|GdkScreen
modifier|*
name|screen
parameter_list|,
name|gint
name|monitor
parameter_list|,
name|gboolean
name|overlay
parameter_list|)
function_decl|;
end_function_decl

begin_function_decl
name|gboolean
name|gimp_tool_gui_get_overlay
parameter_list|(
name|GimpToolGui
modifier|*
name|gui
parameter_list|)
function_decl|;
end_function_decl

begin_function_decl
name|void
name|gimp_tool_gui_set_auto_overlay
parameter_list|(
name|GimpToolGui
modifier|*
name|gui
parameter_list|,
name|gboolean
name|auto_overlay
parameter_list|)
function_decl|;
end_function_decl

begin_function_decl
name|gboolean
name|gimp_tool_gui_get_auto_overlay
parameter_list|(
name|GimpToolGui
modifier|*
name|gui
parameter_list|)
function_decl|;
end_function_decl

begin_function_decl
name|void
name|gimp_tool_gui_set_focus_on_map
parameter_list|(
name|GimpToolGui
modifier|*
name|gui
parameter_list|,
name|gboolean
name|focus_on_map
parameter_list|)
function_decl|;
end_function_decl

begin_function_decl
name|gboolean
name|gimp_tool_gui_get_focus_on_map
parameter_list|(
name|GimpToolGui
modifier|*
name|gui
parameter_list|)
function_decl|;
end_function_decl

begin_function_decl
name|void
name|gimp_tool_gui_set_default_response
parameter_list|(
name|GimpToolGui
modifier|*
name|gui
parameter_list|,
name|gint
name|response_id
parameter_list|)
function_decl|;
end_function_decl

begin_function_decl
name|void
name|gimp_tool_gui_set_response_sensitive
parameter_list|(
name|GimpToolGui
modifier|*
name|gui
parameter_list|,
name|gint
name|response_id
parameter_list|,
name|gboolean
name|sensitive
parameter_list|)
function_decl|;
end_function_decl

begin_function_decl
name|void
name|gimp_tool_gui_set_alternative_button_order
parameter_list|(
name|GimpToolGui
modifier|*
name|gui
parameter_list|,
modifier|...
parameter_list|)
function_decl|;
end_function_decl

begin_endif
endif|#
directive|endif
end_endif

begin_comment
comment|/* __GIMP_TOOL_GUI_H__ */
end_comment

end_unit

