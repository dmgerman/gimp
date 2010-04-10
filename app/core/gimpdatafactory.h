begin_unit|revision:0.9.5;language:C;cregit-version:0.0.1
begin_comment
comment|/* GIMP - The GNU Image Manipulation Program  * Copyright (C) 1995 Spencer Kimball and Peter Mattis  *  * gimpdatafactory.h  * Copyright (C) 2001 Michael Natterer<mitch@gimp.org>  *  * This program is free software: you can redistribute it and/or modify  * it under the terms of the GNU General Public License as published by  * the Free Software Foundation; either version 3 of the License, or  * (at your option) any later version.  *  * This program is distributed in the hope that it will be useful,  * but WITHOUT ANY WARRANTY; without even the implied warranty of  * MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the  * GNU General Public License for more details.  *  * You should have received a copy of the GNU General Public License  * along with this program.  If not, see<http://www.gnu.org/licenses/>.  */
end_comment

begin_ifndef
ifndef|#
directive|ifndef
name|__GIMP_DATA_FACTORY_H__
end_ifndef

begin_define
DECL|macro|__GIMP_DATA_FACTORY_H__
define|#
directive|define
name|__GIMP_DATA_FACTORY_H__
end_define

begin_include
include|#
directive|include
file|"gimpobject.h"
end_include

begin_typedef
DECL|typedef|GimpDataNewFunc
typedef|typedef
name|GimpData
modifier|*
function_decl|(
modifier|*
name|GimpDataNewFunc
function_decl|)
parameter_list|(
name|GimpContext
modifier|*
name|context
parameter_list|,
specifier|const
name|gchar
modifier|*
name|name
parameter_list|)
function_decl|;
end_typedef

begin_typedef
DECL|typedef|GimpDataLoadFunc
typedef|typedef
name|GList
modifier|*
function_decl|(
modifier|*
name|GimpDataLoadFunc
function_decl|)
parameter_list|(
specifier|const
name|gchar
modifier|*
name|filename
parameter_list|,
name|GError
modifier|*
modifier|*
name|error
parameter_list|)
function_decl|;
end_typedef

begin_typedef
DECL|typedef|GimpDataGetStandardFunc
typedef|typedef
name|GimpData
modifier|*
function_decl|(
modifier|*
name|GimpDataGetStandardFunc
function_decl|)
parameter_list|(
name|GimpContext
modifier|*
name|context
parameter_list|)
function_decl|;
end_typedef

begin_typedef
DECL|typedef|GimpDataFactoryLoaderEntry
typedef|typedef
name|struct
name|_GimpDataFactoryLoaderEntry
name|GimpDataFactoryLoaderEntry
typedef|;
end_typedef

begin_struct
DECL|struct|_GimpDataFactoryLoaderEntry
struct|struct
name|_GimpDataFactoryLoaderEntry
block|{
DECL|member|load_func
name|GimpDataLoadFunc
name|load_func
decl_stmt|;
DECL|member|extension
specifier|const
name|gchar
modifier|*
name|extension
decl_stmt|;
DECL|member|writable
name|gboolean
name|writable
decl_stmt|;
block|}
struct|;
end_struct

begin_define
DECL|macro|GIMP_TYPE_DATA_FACTORY
define|#
directive|define
name|GIMP_TYPE_DATA_FACTORY
value|(gimp_data_factory_get_type ())
end_define

begin_define
DECL|macro|GIMP_DATA_FACTORY (obj)
define|#
directive|define
name|GIMP_DATA_FACTORY
parameter_list|(
name|obj
parameter_list|)
value|(G_TYPE_CHECK_INSTANCE_CAST ((obj), GIMP_TYPE_DATA_FACTORY, GimpDataFactory))
end_define

begin_define
DECL|macro|GIMP_DATA_FACTORY_CLASS (klass)
define|#
directive|define
name|GIMP_DATA_FACTORY_CLASS
parameter_list|(
name|klass
parameter_list|)
value|(G_TYPE_CHECK_CLASS_CAST ((klass), GIMP_TYPE_DATA_FACTORY, GimpDataFactoryClass))
end_define

begin_define
DECL|macro|GIMP_IS_DATA_FACTORY (obj)
define|#
directive|define
name|GIMP_IS_DATA_FACTORY
parameter_list|(
name|obj
parameter_list|)
value|(G_TYPE_CHECK_INSTANCE_TYPE ((obj), GIMP_TYPE_DATA_FACTORY))
end_define

begin_define
DECL|macro|GIMP_IS_DATA_FACTORY_CLASS (klass)
define|#
directive|define
name|GIMP_IS_DATA_FACTORY_CLASS
parameter_list|(
name|klass
parameter_list|)
value|(G_TYPE_CHECK_CLASS_TYPE ((klass), GIMP_TYPE_DATA_FACTORY))
end_define

begin_define
DECL|macro|GIMP_DATA_FACTORY_GET_CLASS (obj)
define|#
directive|define
name|GIMP_DATA_FACTORY_GET_CLASS
parameter_list|(
name|obj
parameter_list|)
value|(G_TYPE_INSTANCE_GET_CLASS ((obj), GIMP_TYPE_DATA_FACTORY, GimpDataFactoryClass))
end_define

begin_typedef
DECL|typedef|GimpDataFactoryClass
typedef|typedef
name|struct
name|_GimpDataFactoryClass
name|GimpDataFactoryClass
typedef|;
end_typedef

begin_typedef
DECL|typedef|GimpDataFactoryPriv
typedef|typedef
name|struct
name|_GimpDataFactoryPriv
name|GimpDataFactoryPriv
typedef|;
end_typedef

begin_struct
DECL|struct|_GimpDataFactory
struct|struct
name|_GimpDataFactory
block|{
DECL|member|parent_instance
name|GimpObject
name|parent_instance
decl_stmt|;
DECL|member|priv
name|GimpDataFactoryPriv
modifier|*
name|priv
decl_stmt|;
block|}
struct|;
end_struct

begin_struct
DECL|struct|_GimpDataFactoryClass
struct|struct
name|_GimpDataFactoryClass
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
name|gimp_data_factory_get_type
argument_list|(
name|void
argument_list|)
name|G_GNUC_CONST
decl_stmt|;
end_decl_stmt

begin_function_decl
name|GimpDataFactory
modifier|*
name|gimp_data_factory_new
parameter_list|(
name|Gimp
modifier|*
name|gimp
parameter_list|,
name|GType
name|data_type
parameter_list|,
specifier|const
name|gchar
modifier|*
name|path_property_name
parameter_list|,
specifier|const
name|gchar
modifier|*
name|writable_property_name
parameter_list|,
specifier|const
name|GimpDataFactoryLoaderEntry
modifier|*
name|loader_entries
parameter_list|,
name|gint
name|n_loader_entries
parameter_list|,
name|GimpDataNewFunc
name|new_func
parameter_list|,
name|GimpDataGetStandardFunc
name|get_standard_func
parameter_list|)
function_decl|;
end_function_decl

begin_function_decl
name|void
name|gimp_data_factory_data_init
parameter_list|(
name|GimpDataFactory
modifier|*
name|factory
parameter_list|,
name|gboolean
name|no_data
parameter_list|)
function_decl|;
end_function_decl

begin_function_decl
name|void
name|gimp_data_factory_data_refresh
parameter_list|(
name|GimpDataFactory
modifier|*
name|factory
parameter_list|)
function_decl|;
end_function_decl

begin_function_decl
name|void
name|gimp_data_factory_data_save
parameter_list|(
name|GimpDataFactory
modifier|*
name|factory
parameter_list|)
function_decl|;
end_function_decl

begin_function_decl
name|void
name|gimp_data_factory_data_free
parameter_list|(
name|GimpDataFactory
modifier|*
name|factory
parameter_list|)
function_decl|;
end_function_decl

begin_function_decl
name|GimpData
modifier|*
name|gimp_data_factory_data_new
parameter_list|(
name|GimpDataFactory
modifier|*
name|factory
parameter_list|,
name|GimpContext
modifier|*
name|context
parameter_list|,
specifier|const
name|gchar
modifier|*
name|name
parameter_list|)
function_decl|;
end_function_decl

begin_function_decl
name|GimpData
modifier|*
name|gimp_data_factory_data_duplicate
parameter_list|(
name|GimpDataFactory
modifier|*
name|factory
parameter_list|,
name|GimpData
modifier|*
name|data
parameter_list|)
function_decl|;
end_function_decl

begin_function_decl
name|gboolean
name|gimp_data_factory_data_delete
parameter_list|(
name|GimpDataFactory
modifier|*
name|factory
parameter_list|,
name|GimpData
modifier|*
name|data
parameter_list|,
name|gboolean
name|delete_from_disk
parameter_list|,
name|GError
modifier|*
modifier|*
name|error
parameter_list|)
function_decl|;
end_function_decl

begin_function_decl
name|GimpData
modifier|*
name|gimp_data_factory_data_get_standard
parameter_list|(
name|GimpDataFactory
modifier|*
name|factory
parameter_list|,
name|GimpContext
modifier|*
name|context
parameter_list|)
function_decl|;
end_function_decl

begin_function_decl
name|gboolean
name|gimp_data_factory_data_save_single
parameter_list|(
name|GimpDataFactory
modifier|*
name|factory
parameter_list|,
name|GimpData
modifier|*
name|data
parameter_list|,
name|GError
modifier|*
modifier|*
name|error
parameter_list|)
function_decl|;
end_function_decl

begin_function_decl
name|GimpContainer
modifier|*
name|gimp_data_factory_get_container
parameter_list|(
name|GimpDataFactory
modifier|*
name|factory
parameter_list|)
function_decl|;
end_function_decl

begin_function_decl
name|GimpContainer
modifier|*
name|gimp_data_factory_get_container_obsolete
parameter_list|(
name|GimpDataFactory
modifier|*
name|factory
parameter_list|)
function_decl|;
end_function_decl

begin_function_decl
name|Gimp
modifier|*
name|gimp_data_factory_get_gimp
parameter_list|(
name|GimpDataFactory
modifier|*
name|factory
parameter_list|)
function_decl|;
end_function_decl

begin_function_decl
name|gboolean
name|gimp_data_factory_has_data_new_func
parameter_list|(
name|GimpDataFactory
modifier|*
name|factory
parameter_list|)
function_decl|;
end_function_decl

begin_endif
endif|#
directive|endif
end_endif

begin_comment
comment|/*  __GIMP_DATA_FACTORY_H__  */
end_comment

end_unit

