begin_unit|revision:0.9.5;language:C;cregit-version:0.0.1
begin_comment
comment|/* GIMP - The GNU Image Manipulation Program  * Copyright (C) 1995 Spencer Kimball and Peter Mattis  *  * gimpsessioninfo.h  * Copyright (C) 2001-2008 Michael Natterer<mitch@gimp.org>  *  * This program is free software: you can redistribute it and/or modify  * it under the terms of the GNU General Public License as published by  * the Free Software Foundation; either version 3 of the License, or  * (at your option) any later version.  *  * This program is distributed in the hope that it will be useful,  * but WITHOUT ANY WARRANTY; without even the implied warranty of  * MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the  * GNU General Public License for more details.  *  * You should have received a copy of the GNU General Public License  * along with this program.  If not, see<http://www.gnu.org/licenses/>.  */
end_comment

begin_ifndef
ifndef|#
directive|ifndef
name|__GIMP_SESSION_INFO_H__
end_ifndef

begin_define
DECL|macro|__GIMP_SESSION_INFO_H__
define|#
directive|define
name|__GIMP_SESSION_INFO_H__
end_define

begin_include
include|#
directive|include
file|"core/gimpobject.h"
end_include

begin_define
DECL|macro|GIMP_TYPE_SESSION_INFO
define|#
directive|define
name|GIMP_TYPE_SESSION_INFO
value|(gimp_session_info_get_type ())
end_define

begin_define
DECL|macro|GIMP_SESSION_INFO (obj)
define|#
directive|define
name|GIMP_SESSION_INFO
parameter_list|(
name|obj
parameter_list|)
value|(G_TYPE_CHECK_INSTANCE_CAST ((obj), GIMP_TYPE_SESSION_INFO, GimpSessionInfo))
end_define

begin_define
DECL|macro|GIMP_SESSION_INFO_CLASS (klass)
define|#
directive|define
name|GIMP_SESSION_INFO_CLASS
parameter_list|(
name|klass
parameter_list|)
value|(G_TYPE_CHECK_CLASS_CAST ((klass), GIMP_TYPE_SESSION_INFO, GimpSessionInfoClass))
end_define

begin_define
DECL|macro|GIMP_IS_SESSION_INFO (obj)
define|#
directive|define
name|GIMP_IS_SESSION_INFO
parameter_list|(
name|obj
parameter_list|)
value|(G_TYPE_CHECK_INSTANCE_TYPE ((obj), GIMP_TYPE_SESSION_INFO))
end_define

begin_define
DECL|macro|GIMP_IS_SESSION_INFO_CLASS (klass)
define|#
directive|define
name|GIMP_IS_SESSION_INFO_CLASS
parameter_list|(
name|klass
parameter_list|)
value|(G_TYPE_CHECK_CLASS_TYPE ((klass), GIMP_TYPE_SESSION_INFO))
end_define

begin_define
DECL|macro|GIMP_SESSION_INFO_GET_CLASS (obj)
define|#
directive|define
name|GIMP_SESSION_INFO_GET_CLASS
parameter_list|(
name|obj
parameter_list|)
value|(G_TYPE_INSTANCE_GET_CLASS ((obj), GIMP_TYPE_SESSION_INFO, GimpSessionInfoClass))
end_define

begin_typedef
DECL|typedef|GimpSessionInfoPrivate
typedef|typedef
name|struct
name|_GimpSessionInfoPrivate
name|GimpSessionInfoPrivate
typedef|;
end_typedef

begin_typedef
DECL|typedef|GimpSessionInfoClass
typedef|typedef
name|struct
name|_GimpSessionInfoClass
name|GimpSessionInfoClass
typedef|;
end_typedef

begin_comment
comment|/**  * GimpSessionInfo:  *  * Contains session info for one toplevel window in the interface such  * as a dock, the empty-image-window, or the open/save dialog.  */
end_comment

begin_struct
DECL|struct|_GimpSessionInfo
struct|struct
name|_GimpSessionInfo
block|{
DECL|member|parent_instance
name|GimpObject
name|parent_instance
decl_stmt|;
DECL|member|p
name|GimpSessionInfoPrivate
modifier|*
name|p
decl_stmt|;
block|}
struct|;
end_struct

begin_struct
DECL|struct|_GimpSessionInfoClass
struct|struct
name|_GimpSessionInfoClass
block|{
DECL|member|parent_class
name|GimpObjectClass
name|parent_class
decl_stmt|;
DECL|member|position_accuracy
name|gint
name|position_accuracy
decl_stmt|;
block|}
struct|;
end_struct

begin_decl_stmt
name|GType
name|gimp_session_info_get_type
argument_list|(
name|void
argument_list|)
name|G_GNUC_CONST
decl_stmt|;
end_decl_stmt

begin_function_decl
name|GimpSessionInfo
modifier|*
name|gimp_session_info_new
parameter_list|(
name|void
parameter_list|)
function_decl|;
end_function_decl

begin_function_decl
name|void
name|gimp_session_info_restore
parameter_list|(
name|GimpSessionInfo
modifier|*
name|info
parameter_list|,
name|GimpDialogFactory
modifier|*
name|factory
parameter_list|)
function_decl|;
end_function_decl

begin_function_decl
name|void
name|gimp_session_info_apply_geometry
parameter_list|(
name|GimpSessionInfo
modifier|*
name|info
parameter_list|)
function_decl|;
end_function_decl

begin_function_decl
name|void
name|gimp_session_info_read_geometry
parameter_list|(
name|GimpSessionInfo
modifier|*
name|info
parameter_list|)
function_decl|;
end_function_decl

begin_function_decl
name|void
name|gimp_session_info_get_info
parameter_list|(
name|GimpSessionInfo
modifier|*
name|info
parameter_list|)
function_decl|;
end_function_decl

begin_function_decl
name|void
name|gimp_session_info_get_info_with_widget
parameter_list|(
name|GimpSessionInfo
modifier|*
name|info
parameter_list|,
name|GtkWidget
modifier|*
name|widget
parameter_list|)
function_decl|;
end_function_decl

begin_function_decl
name|void
name|gimp_session_info_clear_info
parameter_list|(
name|GimpSessionInfo
modifier|*
name|info
parameter_list|)
function_decl|;
end_function_decl

begin_function_decl
name|gboolean
name|gimp_session_info_is_singleton
parameter_list|(
name|GimpSessionInfo
modifier|*
name|info
parameter_list|)
function_decl|;
end_function_decl

begin_function_decl
name|gboolean
name|gimp_session_info_is_session_managed
parameter_list|(
name|GimpSessionInfo
modifier|*
name|info
parameter_list|)
function_decl|;
end_function_decl

begin_function_decl
name|gboolean
name|gimp_session_info_get_remember_size
parameter_list|(
name|GimpSessionInfo
modifier|*
name|info
parameter_list|)
function_decl|;
end_function_decl

begin_function_decl
name|gboolean
name|gimp_session_info_get_remember_if_open
parameter_list|(
name|GimpSessionInfo
modifier|*
name|info
parameter_list|)
function_decl|;
end_function_decl

begin_function_decl
name|GtkWidget
modifier|*
name|gimp_session_info_get_widget
parameter_list|(
name|GimpSessionInfo
modifier|*
name|info
parameter_list|)
function_decl|;
end_function_decl

begin_function_decl
name|void
name|gimp_session_info_set_widget
parameter_list|(
name|GimpSessionInfo
modifier|*
name|info
parameter_list|,
name|GtkWidget
modifier|*
name|widget
parameter_list|)
function_decl|;
end_function_decl

begin_function_decl
name|GimpDialogFactoryEntry
modifier|*
name|gimp_session_info_get_factory_entry
parameter_list|(
name|GimpSessionInfo
modifier|*
name|info
parameter_list|)
function_decl|;
end_function_decl

begin_function_decl
name|void
name|gimp_session_info_set_factory_entry
parameter_list|(
name|GimpSessionInfo
modifier|*
name|info
parameter_list|,
name|GimpDialogFactoryEntry
modifier|*
name|entry
parameter_list|)
function_decl|;
end_function_decl

begin_function_decl
name|gboolean
name|gimp_session_info_get_open
parameter_list|(
name|GimpSessionInfo
modifier|*
name|info
parameter_list|)
function_decl|;
end_function_decl

begin_function_decl
name|void
name|gimp_session_info_append_book
parameter_list|(
name|GimpSessionInfo
modifier|*
name|info
parameter_list|,
name|GimpSessionInfoBook
modifier|*
name|book
parameter_list|)
function_decl|;
end_function_decl

begin_function_decl
name|gint
name|gimp_session_info_get_x
parameter_list|(
name|GimpSessionInfo
modifier|*
name|info
parameter_list|)
function_decl|;
end_function_decl

begin_function_decl
name|gint
name|gimp_session_info_get_y
parameter_list|(
name|GimpSessionInfo
modifier|*
name|info
parameter_list|)
function_decl|;
end_function_decl

begin_function_decl
name|gint
name|gimp_session_info_get_width
parameter_list|(
name|GimpSessionInfo
modifier|*
name|info
parameter_list|)
function_decl|;
end_function_decl

begin_function_decl
name|gint
name|gimp_session_info_get_height
parameter_list|(
name|GimpSessionInfo
modifier|*
name|info
parameter_list|)
function_decl|;
end_function_decl

begin_function_decl
name|void
name|gimp_session_info_class_set_position_accuracy
parameter_list|(
name|GimpSessionInfoClass
modifier|*
name|klass
parameter_list|,
name|gint
name|accuracy
parameter_list|)
function_decl|;
end_function_decl

begin_function_decl
name|gint
name|gimp_session_info_class_apply_position_accuracy
parameter_list|(
name|GimpSessionInfoClass
modifier|*
name|klass
parameter_list|,
name|gint
name|position
parameter_list|)
function_decl|;
end_function_decl

begin_endif
endif|#
directive|endif
end_endif

begin_comment
comment|/* __GIMP_SESSION_INFO_H__ */
end_comment

end_unit

