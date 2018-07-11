begin_unit|revision:0.9.5;language:C;cregit-version:0.0.1
begin_comment
comment|/* GIMP - The GNU Image Manipulation Program  * Copyright (C) 1995 Spencer Kimball and Peter Mattis  *  * gimpextensionlist.h  * Copyright (C) 2018 Jehan<jehan@gimp.org>  *  * This program is free software: you can redistribute it and/or modify  * it under the terms of the GNU General Public License as published by  * the Free Software Foundation; either version 3 of the License, or  * (at your option) any later version.  *  * This program is distributed in the hope that it will be useful,  * but WITHOUT ANY WARRANTY; without even the implied warranty of  * MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the  * GNU General Public License for more details.  *  * You should have received a copy of the GNU General Public License  * along with this program.  If not, see<https://www.gnu.org/licenses/>.  */
end_comment

begin_ifndef
ifndef|#
directive|ifndef
name|__GIMP_EXTENSION_LIST_H__
end_ifndef

begin_define
DECL|macro|__GIMP_EXTENSION_LIST_H__
define|#
directive|define
name|__GIMP_EXTENSION_LIST_H__
end_define

begin_define
DECL|macro|GIMP_TYPE_EXTENSION_LIST
define|#
directive|define
name|GIMP_TYPE_EXTENSION_LIST
value|(gimp_extension_list_get_type ())
end_define

begin_define
DECL|macro|GIMP_EXTENSION_LIST (obj)
define|#
directive|define
name|GIMP_EXTENSION_LIST
parameter_list|(
name|obj
parameter_list|)
value|(G_TYPE_CHECK_INSTANCE_CAST ((obj), GIMP_TYPE_EXTENSION_LIST, GimpExtensionList))
end_define

begin_define
DECL|macro|GIMP_EXTENSION_LIST_CLASS (klass)
define|#
directive|define
name|GIMP_EXTENSION_LIST_CLASS
parameter_list|(
name|klass
parameter_list|)
value|(G_TYPE_CHECK_CLASS_CAST ((klass), GIMP_TYPE_EXTENSION_LIST, GimpExtensionListClass))
end_define

begin_define
DECL|macro|GIMP_IS_EXTENSION_LIST (obj)
define|#
directive|define
name|GIMP_IS_EXTENSION_LIST
parameter_list|(
name|obj
parameter_list|)
value|(G_TYPE_CHECK_INSTANCE_TYPE ((obj), GIMP_TYPE_EXTENSION_LIST))
end_define

begin_define
DECL|macro|GIMP_IS_EXTENSION_LIST_CLASS (klass)
define|#
directive|define
name|GIMP_IS_EXTENSION_LIST_CLASS
parameter_list|(
name|klass
parameter_list|)
value|(G_TYPE_CHECK_CLASS_TYPE ((klass), GIMP_TYPE_EXTENSION_LIST))
end_define

begin_define
DECL|macro|GIMP_EXTENSION_LIST_GET_CLASS (obj)
define|#
directive|define
name|GIMP_EXTENSION_LIST_GET_CLASS
parameter_list|(
name|obj
parameter_list|)
value|(G_TYPE_INSTANCE_GET_CLASS ((obj), GIMP_TYPE_EXTENSION_LIST, GimpExtensionListClass))
end_define

begin_typedef
DECL|typedef|GimpExtensionListClass
typedef|typedef
name|struct
name|_GimpExtensionListClass
name|GimpExtensionListClass
typedef|;
end_typedef

begin_typedef
DECL|typedef|GimpExtensionListPrivate
typedef|typedef
name|struct
name|_GimpExtensionListPrivate
name|GimpExtensionListPrivate
typedef|;
end_typedef

begin_struct
DECL|struct|_GimpExtensionList
struct|struct
name|_GimpExtensionList
block|{
DECL|member|parent_instance
name|GtkListBox
name|parent_instance
decl_stmt|;
DECL|member|p
name|GimpExtensionListPrivate
modifier|*
name|p
decl_stmt|;
block|}
struct|;
end_struct

begin_struct
DECL|struct|_GimpExtensionListClass
struct|struct
name|_GimpExtensionListClass
block|{
DECL|member|parent_class
name|GtkListBoxClass
name|parent_class
decl_stmt|;
DECL|member|extension_activated
name|void
function_decl|(
modifier|*
name|extension_activated
function_decl|)
parameter_list|(
name|GimpExtensionList
modifier|*
name|list
parameter_list|,
name|GimpExtension
modifier|*
name|extension
parameter_list|)
function_decl|;
block|}
struct|;
end_struct

begin_decl_stmt
name|GType
name|gimp_extension_list_get_type
argument_list|(
name|void
argument_list|)
name|G_GNUC_CONST
decl_stmt|;
end_decl_stmt

begin_function_decl
name|GtkWidget
modifier|*
name|gimp_extension_list_new
parameter_list|(
name|GimpExtensionManager
modifier|*
name|manager
parameter_list|)
function_decl|;
end_function_decl

begin_function_decl
name|void
name|gimp_extension_list_show_system
parameter_list|(
name|GimpExtensionList
modifier|*
name|list
parameter_list|)
function_decl|;
end_function_decl

begin_function_decl
name|void
name|gimp_extension_list_show_user
parameter_list|(
name|GimpExtensionList
modifier|*
name|list
parameter_list|)
function_decl|;
end_function_decl

begin_function_decl
name|void
name|gimp_extension_list_show_search
parameter_list|(
name|GimpExtensionList
modifier|*
name|list
parameter_list|,
specifier|const
name|gchar
modifier|*
name|search_terms
parameter_list|)
function_decl|;
end_function_decl

begin_endif
endif|#
directive|endif
end_endif

begin_comment
comment|/* __GIMP_EXTENSION_LIST_H__ */
end_comment

end_unit

