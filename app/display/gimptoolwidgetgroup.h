begin_unit|revision:0.9.5;language:C;cregit-version:0.0.1
begin_comment
comment|/* GIMP - The GNU Image Manipulation Program  * Copyright (C) 1995 Spencer Kimball and Peter Mattis  *  * gimptoolwidgetgroup.h  * Copyright (C) 2018 Ell  *  * This program is free software: you can redistribute it and/or modify  * it under the terms of the GNU General Public License as published by  * the Free Software Foundation; either version 3 of the License, or  * (at your option) any later version.  *  * This program is distributed in the hope that it will be useful,  * but WITHOUT ANY WARRANTY; without even the implied warranty of  * MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the  * GNU General Public License for more details.  *  * You should have received a copy of the GNU General Public License  * along with this program.  If not, see<https://www.gnu.org/licenses/>.  */
end_comment

begin_ifndef
ifndef|#
directive|ifndef
name|__GIMP_TOOL_WIDGET_GROUP_H__
end_ifndef

begin_define
DECL|macro|__GIMP_TOOL_WIDGET_GROUP_H__
define|#
directive|define
name|__GIMP_TOOL_WIDGET_GROUP_H__
end_define

begin_include
include|#
directive|include
file|"gimptoolwidget.h"
end_include

begin_define
DECL|macro|GIMP_TYPE_TOOL_WIDGET_GROUP
define|#
directive|define
name|GIMP_TYPE_TOOL_WIDGET_GROUP
value|(gimp_tool_widget_group_get_type ())
end_define

begin_define
DECL|macro|GIMP_TOOL_WIDGET_GROUP (obj)
define|#
directive|define
name|GIMP_TOOL_WIDGET_GROUP
parameter_list|(
name|obj
parameter_list|)
value|(G_TYPE_CHECK_INSTANCE_CAST ((obj), GIMP_TYPE_TOOL_WIDGET_GROUP, GimpToolWidgetGroup))
end_define

begin_define
DECL|macro|GIMP_TOOL_WIDGET_GROUP_CLASS (klass)
define|#
directive|define
name|GIMP_TOOL_WIDGET_GROUP_CLASS
parameter_list|(
name|klass
parameter_list|)
value|(G_TYPE_CHECK_CLASS_CAST ((klass), GIMP_TYPE_TOOL_WIDGET_GROUP, GimpToolWidgetGroupClass))
end_define

begin_define
DECL|macro|GIMP_IS_TOOL_WIDGET_GROUP (obj)
define|#
directive|define
name|GIMP_IS_TOOL_WIDGET_GROUP
parameter_list|(
name|obj
parameter_list|)
value|(G_TYPE_CHECK_INSTANCE_TYPE ((obj), GIMP_TYPE_TOOL_WIDGET_GROUP))
end_define

begin_define
DECL|macro|GIMP_IS_TOOL_WIDGET_GROUP_CLASS (klass)
define|#
directive|define
name|GIMP_IS_TOOL_WIDGET_GROUP_CLASS
parameter_list|(
name|klass
parameter_list|)
value|(G_TYPE_CHECK_CLASS_TYPE ((klass), GIMP_TYPE_TOOL_WIDGET_GROUP))
end_define

begin_define
DECL|macro|GIMP_TOOL_WIDGET_GROUP_GET_CLASS (obj)
define|#
directive|define
name|GIMP_TOOL_WIDGET_GROUP_GET_CLASS
parameter_list|(
name|obj
parameter_list|)
value|(G_TYPE_INSTANCE_GET_CLASS ((obj), GIMP_TYPE_TOOL_WIDGET_GROUP, GimpToolWidgetGroupClass))
end_define

begin_typedef
DECL|typedef|GimpToolWidgetGroupPrivate
typedef|typedef
name|struct
name|_GimpToolWidgetGroupPrivate
name|GimpToolWidgetGroupPrivate
typedef|;
end_typedef

begin_typedef
DECL|typedef|GimpToolWidgetGroupClass
typedef|typedef
name|struct
name|_GimpToolWidgetGroupClass
name|GimpToolWidgetGroupClass
typedef|;
end_typedef

begin_struct
DECL|struct|_GimpToolWidgetGroup
struct|struct
name|_GimpToolWidgetGroup
block|{
DECL|member|parent_instance
name|GimpToolWidget
name|parent_instance
decl_stmt|;
DECL|member|priv
name|GimpToolWidgetGroupPrivate
modifier|*
name|priv
decl_stmt|;
block|}
struct|;
end_struct

begin_struct
DECL|struct|_GimpToolWidgetGroupClass
struct|struct
name|_GimpToolWidgetGroupClass
block|{
DECL|member|parent_class
name|GimpToolWidgetClass
name|parent_class
decl_stmt|;
block|}
struct|;
end_struct

begin_decl_stmt
name|GType
name|gimp_tool_widget_group_get_type
argument_list|(
name|void
argument_list|)
name|G_GNUC_CONST
decl_stmt|;
end_decl_stmt

begin_function_decl
name|GimpToolWidget
modifier|*
name|gimp_tool_widget_group_new
parameter_list|(
name|GimpDisplayShell
modifier|*
name|shell
parameter_list|)
function_decl|;
end_function_decl

begin_function_decl
name|GimpContainer
modifier|*
name|gimp_tool_widget_group_get_children
parameter_list|(
name|GimpToolWidgetGroup
modifier|*
name|group
parameter_list|)
function_decl|;
end_function_decl

begin_function_decl
name|GimpToolWidget
modifier|*
name|gimp_tool_widget_group_get_focus_widget
parameter_list|(
name|GimpToolWidgetGroup
modifier|*
name|group
parameter_list|)
function_decl|;
end_function_decl

begin_function_decl
name|void
name|gimp_tool_widget_group_set_auto_raise
parameter_list|(
name|GimpToolWidgetGroup
modifier|*
name|group
parameter_list|,
name|gboolean
name|auto_raise
parameter_list|)
function_decl|;
end_function_decl

begin_function_decl
name|gboolean
name|gimp_tool_widget_group_get_auto_raise
parameter_list|(
name|GimpToolWidgetGroup
modifier|*
name|group
parameter_list|)
function_decl|;
end_function_decl

begin_endif
endif|#
directive|endif
end_endif

begin_comment
comment|/* __GIMP_TOOL_WIDGET_GROUP_H__ */
end_comment

end_unit

