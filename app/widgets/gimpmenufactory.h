begin_unit|revision:0.9.5;language:C;cregit-version:0.0.1
begin_comment
comment|/* The GIMP -- an image manipulation program  * Copyright (C) 1995 Spencer Kimball and Peter Mattis  *  * gimpmenufactory.h  * Copyright (C) 2003 Michael Natterer<mitch@gimp.org>  *  * This program is free software; you can redistribute it and/or modify  * it under the terms of the GNU General Public License as published by  * the Free Software Foundation; either version 2 of the License, or  * (at your option) any later version.  *  * This program is distributed in the hope that it will be useful,  * but WITHOUT ANY WARRANTY; without even the implied warranty of  * MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the  * GNU General Public License for more details.  *  * You should have received a copy of the GNU General Public License  * along with this program; if not, write to the Free Software  * Foundation, Inc., 59 Temple Place - Suite 330, Boston, MA 02111-1307, USA.  */
end_comment

begin_ifndef
ifndef|#
directive|ifndef
name|__GIMP_MENU_FACTORY_H__
end_ifndef

begin_define
DECL|macro|__GIMP_MENU_FACTORY_H__
define|#
directive|define
name|__GIMP_MENU_FACTORY_H__
end_define

begin_include
include|#
directive|include
file|"core/gimpobject.h"
end_include

begin_typedef
DECL|typedef|GimpMenuFactoryEntry
typedef|typedef
name|struct
name|_GimpMenuFactoryEntry
name|GimpMenuFactoryEntry
typedef|;
end_typedef

begin_struct
DECL|struct|_GimpMenuFactoryEntry
struct|struct
name|_GimpMenuFactoryEntry
block|{
DECL|member|identifier
name|gchar
modifier|*
name|identifier
decl_stmt|;
DECL|member|help_id
name|gchar
modifier|*
name|help_id
decl_stmt|;
DECL|member|setup_func
name|GimpItemFactorySetupFunc
name|setup_func
decl_stmt|;
DECL|member|update_func
name|GimpItemFactoryUpdateFunc
name|update_func
decl_stmt|;
DECL|member|update_on_popup
name|gboolean
name|update_on_popup
decl_stmt|;
DECL|member|n_entries
name|guint
name|n_entries
decl_stmt|;
DECL|member|entries
name|GimpItemFactoryEntry
modifier|*
name|entries
decl_stmt|;
block|}
struct|;
end_struct

begin_define
DECL|macro|GIMP_TYPE_MENU_FACTORY
define|#
directive|define
name|GIMP_TYPE_MENU_FACTORY
value|(gimp_menu_factory_get_type ())
end_define

begin_define
DECL|macro|GIMP_MENU_FACTORY (obj)
define|#
directive|define
name|GIMP_MENU_FACTORY
parameter_list|(
name|obj
parameter_list|)
value|(G_TYPE_CHECK_INSTANCE_CAST ((obj), GIMP_TYPE_MENU_FACTORY, GimpMenuFactory))
end_define

begin_define
DECL|macro|GIMP_MENU_FACTORY_CLASS (klass)
define|#
directive|define
name|GIMP_MENU_FACTORY_CLASS
parameter_list|(
name|klass
parameter_list|)
value|(G_TYPE_CHECK_CLASS_CAST ((klass), GIMP_TYPE_MENU_FACTORY, GimpMenuFactoryClass))
end_define

begin_define
DECL|macro|GIMP_IS_MENU_FACTORY (obj)
define|#
directive|define
name|GIMP_IS_MENU_FACTORY
parameter_list|(
name|obj
parameter_list|)
value|(G_TYPE_CHECK_INSTANCE_TYPE ((obj), GIMP_TYPE_MENU_FACTORY))
end_define

begin_define
DECL|macro|GIMP_IS_MENU_FACTORY_CLASS (klass)
define|#
directive|define
name|GIMP_IS_MENU_FACTORY_CLASS
parameter_list|(
name|klass
parameter_list|)
value|(G_TYPE_CHECK_CLASS_TYPE ((klass), GIMP_TYPE_MENU_FACTORY))
end_define

begin_define
DECL|macro|GIMP_MENU_FACTORY_GET_CLASS (obj)
define|#
directive|define
name|GIMP_MENU_FACTORY_GET_CLASS
parameter_list|(
name|obj
parameter_list|)
value|(G_TYPE_INSTANCE_GET_CLASS ((obj), GIMP_TYPE_MENU_FACTORY, GimpMenuFactoryClass))
end_define

begin_typedef
DECL|typedef|GimpMenuFactoryClass
typedef|typedef
name|struct
name|_GimpMenuFactoryClass
name|GimpMenuFactoryClass
typedef|;
end_typedef

begin_struct
DECL|struct|_GimpMenuFactory
struct|struct
name|_GimpMenuFactory
block|{
DECL|member|parent_instance
name|GimpObject
name|parent_instance
decl_stmt|;
DECL|member|gimp
name|Gimp
modifier|*
name|gimp
decl_stmt|;
DECL|member|registered_menus
name|GList
modifier|*
name|registered_menus
decl_stmt|;
block|}
struct|;
end_struct

begin_struct
DECL|struct|_GimpMenuFactoryClass
struct|struct
name|_GimpMenuFactoryClass
block|{
DECL|member|parent_class
name|GimpObjectClass
name|parent_class
decl_stmt|;
block|}
struct|;
end_struct

begin_decl_stmt
name|GType
name|gimp_menu_factory_get_type
argument_list|(
name|void
argument_list|)
name|G_GNUC_CONST
decl_stmt|;
end_decl_stmt

begin_function_decl
name|GimpMenuFactory
modifier|*
name|gimp_menu_factory_new
parameter_list|(
name|Gimp
modifier|*
name|gimp
parameter_list|)
function_decl|;
end_function_decl

begin_function_decl
name|void
name|gimp_menu_factory_menu_register
parameter_list|(
name|GimpMenuFactory
modifier|*
name|factory
parameter_list|,
specifier|const
name|gchar
modifier|*
name|identifier
parameter_list|,
specifier|const
name|gchar
modifier|*
name|help_id
parameter_list|,
name|GimpItemFactorySetupFunc
name|setup_func
parameter_list|,
name|GimpItemFactoryUpdateFunc
name|update_func
parameter_list|,
name|gboolean
name|update_on_popup
parameter_list|,
name|guint
name|n_entries
parameter_list|,
name|GimpItemFactoryEntry
modifier|*
name|entries
parameter_list|)
function_decl|;
end_function_decl

begin_function_decl
name|GimpItemFactory
modifier|*
name|gimp_menu_factory_menu_new
parameter_list|(
name|GimpMenuFactory
modifier|*
name|factory
parameter_list|,
specifier|const
name|gchar
modifier|*
name|identifier
parameter_list|,
name|GType
name|container_type
parameter_list|,
name|gpointer
name|callback_data
parameter_list|,
name|gboolean
name|create_tearoff
parameter_list|)
function_decl|;
end_function_decl

begin_endif
endif|#
directive|endif
end_endif

begin_comment
comment|/*  __GIMP_MENU_FACTORY_H__  */
end_comment

end_unit

