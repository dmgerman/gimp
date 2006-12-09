begin_unit|revision:0.9.5;language:C;cregit-version:0.0.1
begin_comment
comment|/* LIBGIMP - The GIMP Library  * Copyright (C) 1995-1997 Peter Mattis and Spencer Kimball  *  * gimpcontrollerinfo.h  * Copyright (C) 2004-2005 Michael Natterer<mitch@gimp.org>  *  * This program is free software; you can redistribute it and/or modify  * it under the terms of the GNU General Public License as published by  * the Free Software Foundation; either version 2 of the License, or  * (at your option) any later version.  *  * This program is distributed in the hope that it will be useful,  * but WITHOUT ANY WARRANTY; without even the implied warranty of  * MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the  * GNU General Public License for more details.  *  * You should have received a copy of the GNU General Public License  * along with this program; if not, write to the Free Software  * Foundation, Inc., 59 Temple Place - Suite 330, Boston, MA 02111-1307, USA.  */
end_comment

begin_ifndef
ifndef|#
directive|ifndef
name|__GIMP_CONTROLLER_INFO_H__
end_ifndef

begin_define
DECL|macro|__GIMP_CONTROLLER_INFO_H__
define|#
directive|define
name|__GIMP_CONTROLLER_INFO_H__
end_define

begin_include
include|#
directive|include
file|"core/gimpviewable.h"
end_include

begin_typedef
DECL|typedef|GimpControllerEventSnooper
typedef|typedef
name|gboolean
function_decl|(
modifier|*
name|GimpControllerEventSnooper
function_decl|)
parameter_list|(
name|GimpControllerInfo
modifier|*
name|info
parameter_list|,
name|GimpController
modifier|*
name|controller
parameter_list|,
specifier|const
name|GimpControllerEvent
modifier|*
name|event
parameter_list|,
name|gpointer
name|user_data
parameter_list|)
function_decl|;
end_typedef

begin_define
DECL|macro|GIMP_TYPE_CONTROLLER_INFO
define|#
directive|define
name|GIMP_TYPE_CONTROLLER_INFO
value|(gimp_controller_info_get_type ())
end_define

begin_define
DECL|macro|GIMP_CONTROLLER_INFO (obj)
define|#
directive|define
name|GIMP_CONTROLLER_INFO
parameter_list|(
name|obj
parameter_list|)
value|(G_TYPE_CHECK_INSTANCE_CAST ((obj), GIMP_TYPE_CONTROLLER_INFO, GimpControllerInfo))
end_define

begin_define
DECL|macro|GIMP_CONTROLLER_INFO_CLASS (klass)
define|#
directive|define
name|GIMP_CONTROLLER_INFO_CLASS
parameter_list|(
name|klass
parameter_list|)
value|(G_TYPE_CHECK_CLASS_CAST ((klass), GIMP_TYPE_CONTROLLER_INFO, GimpControllerInfoClass))
end_define

begin_define
DECL|macro|GIMP_IS_CONTROLLER_INFO (obj)
define|#
directive|define
name|GIMP_IS_CONTROLLER_INFO
parameter_list|(
name|obj
parameter_list|)
value|(G_TYPE_CHECK_INSTANCE_TYPE ((obj), GIMP_TYPE_CONTROLLER_INFO))
end_define

begin_define
DECL|macro|GIMP_IS_CONTROLLER_INFO_CLASS (klass)
define|#
directive|define
name|GIMP_IS_CONTROLLER_INFO_CLASS
parameter_list|(
name|klass
parameter_list|)
value|(G_TYPE_CHECK_CLASS_TYPE ((klass), GIMP_TYPE_CONTROLLER_INFO))
end_define

begin_define
DECL|macro|GIMP_CONTROLLER_INFO_GET_CLASS (obj)
define|#
directive|define
name|GIMP_CONTROLLER_INFO_GET_CLASS
parameter_list|(
name|obj
parameter_list|)
value|(G_TYPE_INSTANCE_GET_CLASS ((obj), GIMP_TYPE_CONTROLLER_INFO, GimpControllerInfoClass))
end_define

begin_typedef
DECL|typedef|GimpControllerInfoClass
typedef|typedef
name|struct
name|_GimpControllerInfoClass
name|GimpControllerInfoClass
typedef|;
end_typedef

begin_struct
DECL|struct|_GimpControllerInfo
struct|struct
name|_GimpControllerInfo
block|{
DECL|member|parent_instance
name|GimpViewable
name|parent_instance
decl_stmt|;
DECL|member|enabled
name|gboolean
name|enabled
decl_stmt|;
DECL|member|debug_events
name|gboolean
name|debug_events
decl_stmt|;
DECL|member|controller
name|GimpController
modifier|*
name|controller
decl_stmt|;
DECL|member|mapping
name|GHashTable
modifier|*
name|mapping
decl_stmt|;
DECL|member|snooper
name|GimpControllerEventSnooper
name|snooper
decl_stmt|;
DECL|member|snooper_data
name|gpointer
name|snooper_data
decl_stmt|;
block|}
struct|;
end_struct

begin_struct
DECL|struct|_GimpControllerInfoClass
struct|struct
name|_GimpControllerInfoClass
block|{
DECL|member|parent_class
name|GimpViewableClass
name|parent_class
decl_stmt|;
DECL|member|event_mapped
name|gboolean
function_decl|(
modifier|*
name|event_mapped
function_decl|)
parameter_list|(
name|GimpControllerInfo
modifier|*
name|info
parameter_list|,
name|GimpController
modifier|*
name|controller
parameter_list|,
specifier|const
name|GimpControllerEvent
modifier|*
name|event
parameter_list|,
specifier|const
name|gchar
modifier|*
name|action_name
parameter_list|)
function_decl|;
block|}
struct|;
end_struct

begin_decl_stmt
name|GType
name|gimp_controller_info_get_type
argument_list|(
name|void
argument_list|)
name|G_GNUC_CONST
decl_stmt|;
end_decl_stmt

begin_function_decl
name|GimpControllerInfo
modifier|*
name|gimp_controller_info_new
parameter_list|(
name|GType
name|type
parameter_list|)
function_decl|;
end_function_decl

begin_function_decl
name|void
name|gimp_controller_info_set_enabled
parameter_list|(
name|GimpControllerInfo
modifier|*
name|info
parameter_list|,
name|gboolean
name|enabled
parameter_list|)
function_decl|;
end_function_decl

begin_function_decl
name|gboolean
name|gimp_controller_info_get_enabled
parameter_list|(
name|GimpControllerInfo
modifier|*
name|info
parameter_list|)
function_decl|;
end_function_decl

begin_function_decl
name|void
name|gimp_controller_info_set_event_snooper
parameter_list|(
name|GimpControllerInfo
modifier|*
name|info
parameter_list|,
name|GimpControllerEventSnooper
name|snooper
parameter_list|,
name|gpointer
name|snooper_data
parameter_list|)
function_decl|;
end_function_decl

begin_endif
endif|#
directive|endif
end_endif

begin_comment
comment|/* __GIMP_CONTROLLER_INFO_H__ */
end_comment

end_unit

