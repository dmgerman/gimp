begin_unit|revision:0.9.5;language:C;cregit-version:0.0.1
begin_comment
comment|/* The GIMP -- an image manipulation program  * Copyright (C) 1995 Spencer Kimball and Peter Mattis  *  * gimpuimanager.h  * Copyright (C) 2004 Michael Natterer<mitch@gimp.org>  *  * This program is free software; you can redistribute it and/or modify  * it under the terms of the GNU General Public License as published by  * the Free Software Foundation; either version 2 of the License, or  * (at your option) any later version.  *  * This program is distributed in the hope that it will be useful,  * but WITHOUT ANY WARRANTY; without even the implied warranty of  * MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the  * GNU General Public License for more details.  *  * You should have received a copy of the GNU General Public License  * along with this program; if not, write to the Free Software  * Foundation, Inc., 59 Temple Place - Suite 330, Boston, MA 02111-1307, USA.  */
end_comment

begin_ifndef
ifndef|#
directive|ifndef
name|__GIMP_UI_MANAGER_H__
end_ifndef

begin_define
DECL|macro|__GIMP_UI_MANAGER_H__
define|#
directive|define
name|__GIMP_UI_MANAGER_H__
end_define

begin_include
include|#
directive|include
file|<gtk/gtkuimanager.h>
end_include

begin_typedef
DECL|typedef|GimpUIManagerUIEntry
typedef|typedef
name|struct
name|_GimpUIManagerUIEntry
name|GimpUIManagerUIEntry
typedef|;
end_typedef

begin_struct
DECL|struct|_GimpUIManagerUIEntry
struct|struct
name|_GimpUIManagerUIEntry
block|{
DECL|member|identifier
name|gchar
modifier|*
name|identifier
decl_stmt|;
DECL|member|basename
name|gchar
modifier|*
name|basename
decl_stmt|;
DECL|member|merge_id
name|guint
name|merge_id
decl_stmt|;
block|}
struct|;
end_struct

begin_define
DECL|macro|GIMP_TYPE_UI_MANAGER
define|#
directive|define
name|GIMP_TYPE_UI_MANAGER
value|(gimp_ui_manager_get_type ())
end_define

begin_define
DECL|macro|GIMP_UI_MANAGER (obj)
define|#
directive|define
name|GIMP_UI_MANAGER
parameter_list|(
name|obj
parameter_list|)
value|(G_TYPE_CHECK_INSTANCE_CAST ((obj), GIMP_TYPE_UI_MANAGER, GimpUIManager))
end_define

begin_define
DECL|macro|GIMP_UI_MANAGER_CLASS (vtable)
define|#
directive|define
name|GIMP_UI_MANAGER_CLASS
parameter_list|(
name|vtable
parameter_list|)
value|(G_TYPE_CHECK_CLASS_CAST ((vtable), GIMP_TYPE_UI_MANAGER, GimpUIManagerClass))
end_define

begin_define
DECL|macro|GIMP_IS_UI_MANAGER (obj)
define|#
directive|define
name|GIMP_IS_UI_MANAGER
parameter_list|(
name|obj
parameter_list|)
value|(G_TYPE_CHECK_INSTANCE_TYPE ((obj), GIMP_TYPE_UI_MANAGER))
end_define

begin_define
DECL|macro|GIMP_IS_UI_MANAGER_CLASS (vtable)
define|#
directive|define
name|GIMP_IS_UI_MANAGER_CLASS
parameter_list|(
name|vtable
parameter_list|)
value|(G_TYPE_CHECK_CLASS_TYPE ((vtable), GIMP_TYPE_UI_MANAGER))
end_define

begin_define
DECL|macro|GIMP_UI_MANAGER_GET_CLASS (inst)
define|#
directive|define
name|GIMP_UI_MANAGER_GET_CLASS
parameter_list|(
name|inst
parameter_list|)
value|(G_TYPE_INSTANCE_GET_CLASS ((inst), GIMP_TYPE_UI_MANAGER, GimpUIManagerClass))
end_define

begin_typedef
DECL|typedef|GimpUIManagerClass
typedef|typedef
name|struct
name|_GimpUIManagerClass
name|GimpUIManagerClass
typedef|;
end_typedef

begin_struct
DECL|struct|_GimpUIManager
struct|struct
name|_GimpUIManager
block|{
DECL|member|parent_instance
name|GtkUIManager
name|parent_instance
decl_stmt|;
DECL|member|gimp
name|Gimp
modifier|*
name|gimp
decl_stmt|;
DECL|member|registered_uis
name|GList
modifier|*
name|registered_uis
decl_stmt|;
block|}
struct|;
end_struct

begin_struct
DECL|struct|_GimpUIManagerClass
struct|struct
name|_GimpUIManagerClass
block|{
DECL|member|parent_class
name|GtkUIManagerClass
name|parent_class
decl_stmt|;
block|}
struct|;
end_struct

begin_function_decl
name|GType
name|gimp_ui_manager_get_type
parameter_list|(
name|void
parameter_list|)
function_decl|;
end_function_decl

begin_function_decl
name|GimpUIManager
modifier|*
name|gimp_ui_manager_new
parameter_list|(
name|Gimp
modifier|*
name|gimp
parameter_list|)
function_decl|;
end_function_decl

begin_function_decl
name|void
name|gimp_ui_manager_update
parameter_list|(
name|GimpUIManager
modifier|*
name|manager
parameter_list|,
name|gpointer
name|update_data
parameter_list|)
function_decl|;
end_function_decl

begin_function_decl
name|void
name|gimp_ui_manager_ui_register
parameter_list|(
name|GimpUIManager
modifier|*
name|manager
parameter_list|,
specifier|const
name|gchar
modifier|*
name|identifier
parameter_list|,
specifier|const
name|gchar
modifier|*
name|basename
parameter_list|)
function_decl|;
end_function_decl

begin_function_decl
name|GtkWidget
modifier|*
name|gimp_ui_manager_ui_create
parameter_list|(
name|GimpUIManager
modifier|*
name|manager
parameter_list|,
specifier|const
name|gchar
modifier|*
name|identifier
parameter_list|)
function_decl|;
end_function_decl

begin_endif
endif|#
directive|endif
end_endif

begin_comment
comment|/* __GIMP_UI_MANAGER_H__ */
end_comment

end_unit

