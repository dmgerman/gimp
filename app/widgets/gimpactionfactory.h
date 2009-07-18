begin_unit|revision:0.9.5;language:C;cregit-version:0.0.1
begin_comment
comment|/* GIMP - The GNU Image Manipulation Program  * Copyright (C) 1995 Spencer Kimball and Peter Mattis  *  * gimpactionfactory.h  * Copyright (C) 2004 Michael Natterer<mitch@gimp.org>  *  * This program is free software: you can redistribute it and/or modify  * it under the terms of the GNU General Public License as published by  * the Free Software Foundation; either version 3 of the License, or  * (at your option) any later version.  *  * This program is distributed in the hope that it will be useful,  * but WITHOUT ANY WARRANTY; without even the implied warranty of  * MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the  * GNU General Public License for more details.  *  * You should have received a copy of the GNU General Public License  * along with this program.  If not, see<http://www.gnu.org/licenses/>.  */
end_comment

begin_ifndef
ifndef|#
directive|ifndef
name|__GIMP_ACTION_FACTORY_H__
end_ifndef

begin_define
DECL|macro|__GIMP_ACTION_FACTORY_H__
define|#
directive|define
name|__GIMP_ACTION_FACTORY_H__
end_define

begin_include
include|#
directive|include
file|"core/gimpobject.h"
end_include

begin_typedef
DECL|typedef|GimpActionFactoryEntry
typedef|typedef
name|struct
name|_GimpActionFactoryEntry
name|GimpActionFactoryEntry
typedef|;
end_typedef

begin_struct
DECL|struct|_GimpActionFactoryEntry
struct|struct
name|_GimpActionFactoryEntry
block|{
DECL|member|identifier
name|gchar
modifier|*
name|identifier
decl_stmt|;
DECL|member|label
name|gchar
modifier|*
name|label
decl_stmt|;
DECL|member|stock_id
name|gchar
modifier|*
name|stock_id
decl_stmt|;
DECL|member|setup_func
name|GimpActionGroupSetupFunc
name|setup_func
decl_stmt|;
DECL|member|update_func
name|GimpActionGroupUpdateFunc
name|update_func
decl_stmt|;
block|}
struct|;
end_struct

begin_define
DECL|macro|GIMP_TYPE_ACTION_FACTORY
define|#
directive|define
name|GIMP_TYPE_ACTION_FACTORY
value|(gimp_action_factory_get_type ())
end_define

begin_define
DECL|macro|GIMP_ACTION_FACTORY (obj)
define|#
directive|define
name|GIMP_ACTION_FACTORY
parameter_list|(
name|obj
parameter_list|)
value|(G_TYPE_CHECK_INSTANCE_CAST ((obj), GIMP_TYPE_ACTION_FACTORY, GimpActionFactory))
end_define

begin_define
DECL|macro|GIMP_ACTION_FACTORY_CLASS (klass)
define|#
directive|define
name|GIMP_ACTION_FACTORY_CLASS
parameter_list|(
name|klass
parameter_list|)
value|(G_TYPE_CHECK_CLASS_CAST ((klass), GIMP_TYPE_ACTION_FACTORY, GimpActionFactoryClass))
end_define

begin_define
DECL|macro|GIMP_IS_ACTION_FACTORY (obj)
define|#
directive|define
name|GIMP_IS_ACTION_FACTORY
parameter_list|(
name|obj
parameter_list|)
value|(G_TYPE_CHECK_INSTANCE_TYPE ((obj), GIMP_TYPE_ACTION_FACTORY))
end_define

begin_define
DECL|macro|GIMP_IS_ACTION_FACTORY_CLASS (klass)
define|#
directive|define
name|GIMP_IS_ACTION_FACTORY_CLASS
parameter_list|(
name|klass
parameter_list|)
value|(G_TYPE_CHECK_CLASS_TYPE ((klass), GIMP_TYPE_ACTION_FACTORY))
end_define

begin_define
DECL|macro|GIMP_ACTION_FACTORY_GET_CLASS (obj)
define|#
directive|define
name|GIMP_ACTION_FACTORY_GET_CLASS
parameter_list|(
name|obj
parameter_list|)
value|(G_TYPE_INSTANCE_GET_CLASS ((obj), GIMP_TYPE_ACTION_FACTORY, GimpActionFactoryClass))
end_define

begin_typedef
DECL|typedef|GimpActionFactoryClass
typedef|typedef
name|struct
name|_GimpActionFactoryClass
name|GimpActionFactoryClass
typedef|;
end_typedef

begin_struct
DECL|struct|_GimpActionFactory
struct|struct
name|_GimpActionFactory
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
DECL|member|registered_groups
name|GList
modifier|*
name|registered_groups
decl_stmt|;
block|}
struct|;
end_struct

begin_struct
DECL|struct|_GimpActionFactoryClass
struct|struct
name|_GimpActionFactoryClass
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
name|gimp_action_factory_get_type
argument_list|(
name|void
argument_list|)
name|G_GNUC_CONST
decl_stmt|;
end_decl_stmt

begin_function_decl
name|GimpActionFactory
modifier|*
name|gimp_action_factory_new
parameter_list|(
name|Gimp
modifier|*
name|gimp
parameter_list|)
function_decl|;
end_function_decl

begin_function_decl
name|void
name|gimp_action_factory_group_register
parameter_list|(
name|GimpActionFactory
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
name|label
parameter_list|,
specifier|const
name|gchar
modifier|*
name|stock_id
parameter_list|,
name|GimpActionGroupSetupFunc
name|setup_func
parameter_list|,
name|GimpActionGroupUpdateFunc
name|update_func
parameter_list|)
function_decl|;
end_function_decl

begin_function_decl
name|GimpActionGroup
modifier|*
name|gimp_action_factory_group_new
parameter_list|(
name|GimpActionFactory
modifier|*
name|factory
parameter_list|,
specifier|const
name|gchar
modifier|*
name|identifier
parameter_list|,
name|gpointer
name|user_data
parameter_list|)
function_decl|;
end_function_decl

begin_endif
endif|#
directive|endif
end_endif

begin_comment
comment|/*  __GIMP_ACTION_FACTORY_H__  */
end_comment

end_unit

