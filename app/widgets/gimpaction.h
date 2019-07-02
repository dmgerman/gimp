begin_unit|revision:0.9.5;language:C;cregit-version:0.0.1
begin_comment
comment|/* GIMP - The GNU Image Manipulation Program  * Copyright (C) 1995 Spencer Kimball and Peter Mattis  *  * gimpaction.h  * Copyright (C) 2004-2019 Michael Natterer<mitch@gimp.org>  *  * This program is free software: you can redistribute it and/or modify  * it under the terms of the GNU General Public License as published by  * the Free Software Foundation; either version 3 of the License, or  * (at your option) any later version.  *  * This program is distributed in the hope that it will be useful,  * but WITHOUT ANY WARRANTY; without even the implied warranty of  * MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the  * GNU General Public License for more details.  *  * You should have received a copy of the GNU General Public License  * along with this program.  If not, see<https://www.gnu.org/licenses/>.  */
end_comment

begin_ifndef
ifndef|#
directive|ifndef
name|__GIMP_ACTION_H__
end_ifndef

begin_define
DECL|macro|__GIMP_ACTION_H__
define|#
directive|define
name|__GIMP_ACTION_H__
end_define

begin_define
DECL|macro|GIMP_TYPE_ACTION
define|#
directive|define
name|GIMP_TYPE_ACTION
value|(gimp_action_get_type ())
end_define

begin_define
DECL|macro|GIMP_ACTION (obj)
define|#
directive|define
name|GIMP_ACTION
parameter_list|(
name|obj
parameter_list|)
value|(G_TYPE_CHECK_INSTANCE_CAST ((obj), GIMP_TYPE_ACTION, GimpAction))
end_define

begin_define
DECL|macro|GIMP_IS_ACTION (obj)
define|#
directive|define
name|GIMP_IS_ACTION
parameter_list|(
name|obj
parameter_list|)
value|(G_TYPE_CHECK_INSTANCE_TYPE ((obj), GIMP_TYPE_ACTION))
end_define

begin_define
DECL|macro|GIMP_ACTION_GET_INTERFACE (obj)
define|#
directive|define
name|GIMP_ACTION_GET_INTERFACE
parameter_list|(
name|obj
parameter_list|)
value|(G_TYPE_INSTANCE_GET_INTERFACE((obj), GIMP_TYPE_ACTION, GimpActionInterface))
end_define

begin_typedef
DECL|typedef|GimpActionInterface
typedef|typedef
name|struct
name|_GimpActionInterface
name|GimpActionInterface
typedef|;
end_typedef

begin_struct
DECL|struct|_GimpActionInterface
struct|struct
name|_GimpActionInterface
block|{
DECL|member|base_interface
name|GTypeInterface
name|base_interface
decl_stmt|;
block|}
struct|;
end_struct

begin_decl_stmt
name|GType
name|gimp_action_get_type
argument_list|(
name|void
argument_list|)
name|G_GNUC_CONST
decl_stmt|;
end_decl_stmt

begin_function_decl
name|void
name|gimp_action_init
parameter_list|(
name|GimpAction
modifier|*
name|action
parameter_list|)
function_decl|;
end_function_decl

begin_function_decl
name|void
name|gimp_action_set_proxy
parameter_list|(
name|GimpAction
modifier|*
name|action
parameter_list|,
name|GtkWidget
modifier|*
name|proxy
parameter_list|)
function_decl|;
end_function_decl

begin_function_decl
specifier|const
name|gchar
modifier|*
name|gimp_action_get_name
parameter_list|(
name|GimpAction
modifier|*
name|action
parameter_list|)
function_decl|;
end_function_decl

begin_function_decl
name|void
name|gimp_action_set_label
parameter_list|(
name|GimpAction
modifier|*
name|action
parameter_list|,
specifier|const
name|gchar
modifier|*
name|label
parameter_list|)
function_decl|;
end_function_decl

begin_function_decl
specifier|const
name|gchar
modifier|*
name|gimp_action_get_label
parameter_list|(
name|GimpAction
modifier|*
name|action
parameter_list|)
function_decl|;
end_function_decl

begin_function_decl
name|void
name|gimp_action_set_tooltip
parameter_list|(
name|GimpAction
modifier|*
name|action
parameter_list|,
specifier|const
name|gchar
modifier|*
name|tooltip
parameter_list|)
function_decl|;
end_function_decl

begin_function_decl
specifier|const
name|gchar
modifier|*
name|gimp_action_get_tooltip
parameter_list|(
name|GimpAction
modifier|*
name|action
parameter_list|)
function_decl|;
end_function_decl

begin_function_decl
name|void
name|gimp_action_set_icon_name
parameter_list|(
name|GimpAction
modifier|*
name|action
parameter_list|,
specifier|const
name|gchar
modifier|*
name|icon_name
parameter_list|)
function_decl|;
end_function_decl

begin_function_decl
specifier|const
name|gchar
modifier|*
name|gimp_action_get_icon_name
parameter_list|(
name|GimpAction
modifier|*
name|action
parameter_list|)
function_decl|;
end_function_decl

begin_function_decl
name|void
name|gimp_action_set_help_id
parameter_list|(
name|GimpAction
modifier|*
name|action
parameter_list|,
specifier|const
name|gchar
modifier|*
name|help_id
parameter_list|)
function_decl|;
end_function_decl

begin_function_decl
specifier|const
name|gchar
modifier|*
name|gimp_action_get_help_id
parameter_list|(
name|GimpAction
modifier|*
name|action
parameter_list|)
function_decl|;
end_function_decl

begin_function_decl
name|void
name|gimp_action_set_visible
parameter_list|(
name|GimpAction
modifier|*
name|action
parameter_list|,
name|gboolean
name|visible
parameter_list|)
function_decl|;
end_function_decl

begin_function_decl
name|gboolean
name|gimp_action_get_visible
parameter_list|(
name|GimpAction
modifier|*
name|action
parameter_list|)
function_decl|;
end_function_decl

begin_function_decl
name|gboolean
name|gimp_action_is_visible
parameter_list|(
name|GimpAction
modifier|*
name|action
parameter_list|)
function_decl|;
end_function_decl

begin_function_decl
name|void
name|gimp_action_set_sensitive
parameter_list|(
name|GimpAction
modifier|*
name|action
parameter_list|,
name|gboolean
name|sensitive
parameter_list|)
function_decl|;
end_function_decl

begin_function_decl
name|gboolean
name|gimp_action_get_sensitive
parameter_list|(
name|GimpAction
modifier|*
name|action
parameter_list|)
function_decl|;
end_function_decl

begin_function_decl
name|gboolean
name|gimp_action_is_sensitive
parameter_list|(
name|GimpAction
modifier|*
name|action
parameter_list|)
function_decl|;
end_function_decl

begin_function_decl
name|GClosure
modifier|*
name|gimp_action_get_accel_closure
parameter_list|(
name|GimpAction
modifier|*
name|action
parameter_list|)
function_decl|;
end_function_decl

begin_function_decl
name|void
name|gimp_action_set_accel_path
parameter_list|(
name|GimpAction
modifier|*
name|action
parameter_list|,
specifier|const
name|gchar
modifier|*
name|accel_path
parameter_list|)
function_decl|;
end_function_decl

begin_function_decl
specifier|const
name|gchar
modifier|*
name|gimp_action_get_accel_path
parameter_list|(
name|GimpAction
modifier|*
name|action
parameter_list|)
function_decl|;
end_function_decl

begin_function_decl
name|void
name|gimp_action_set_accel_group
parameter_list|(
name|GimpAction
modifier|*
name|action
parameter_list|,
name|GtkAccelGroup
modifier|*
name|accel_group
parameter_list|)
function_decl|;
end_function_decl

begin_function_decl
name|void
name|gimp_action_connect_accelerator
parameter_list|(
name|GimpAction
modifier|*
name|action
parameter_list|)
function_decl|;
end_function_decl

begin_function_decl
name|void
name|gimp_action_activate
parameter_list|(
name|GimpAction
modifier|*
name|action
parameter_list|)
function_decl|;
end_function_decl

begin_function_decl
name|gint
name|gimp_action_name_compare
parameter_list|(
name|GimpAction
modifier|*
name|action1
parameter_list|,
name|GimpAction
modifier|*
name|action2
parameter_list|)
function_decl|;
end_function_decl

begin_function_decl
name|gboolean
name|gimp_action_is_gui_blacklisted
parameter_list|(
specifier|const
name|gchar
modifier|*
name|action_name
parameter_list|)
function_decl|;
end_function_decl

begin_endif
endif|#
directive|endif
end_endif

begin_comment
comment|/* __GIMP_ACTION_H__ */
end_comment

end_unit

