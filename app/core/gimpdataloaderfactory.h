begin_unit|revision:0.9.5;language:C;cregit-version:0.0.1
begin_comment
comment|/* GIMP - The GNU Image Manipulation Program  * Copyright (C) 1995 Spencer Kimball and Peter Mattis  *  * gimpdataloaderfactory.h  * Copyright (C) 2001-2018 Michael Natterer<mitch@gimp.org>  *  * This program is free software: you can redistribute it and/or modify  * it under the terms of the GNU General Public License as published by  * the Free Software Foundation; either version 3 of the License, or  * (at your option) any later version.  *  * This program is distributed in the hope that it will be useful,  * but WITHOUT ANY WARRANTY; without even the implied warranty of  * MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the  * GNU General Public License for more details.  *  * You should have received a copy of the GNU General Public License  * along with this program.  If not, see<http://www.gnu.org/licenses/>.  */
end_comment

begin_ifndef
ifndef|#
directive|ifndef
name|__GIMP_DATA_LOADER_FACTORY_H__
end_ifndef

begin_define
DECL|macro|__GIMP_DATA_LOADER_FACTORY_H__
define|#
directive|define
name|__GIMP_DATA_LOADER_FACTORY_H__
end_define

begin_include
include|#
directive|include
file|"gimpdatafactory.h"
end_include

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
name|GimpContext
modifier|*
name|context
parameter_list|,
name|GFile
modifier|*
name|file
parameter_list|,
name|GInputStream
modifier|*
name|input
parameter_list|,
name|GError
modifier|*
modifier|*
name|error
parameter_list|)
function_decl|;
end_typedef

begin_define
DECL|macro|GIMP_TYPE_DATA_LOADER_FACTORY
define|#
directive|define
name|GIMP_TYPE_DATA_LOADER_FACTORY
value|(gimp_data_loader_factory_get_type ())
end_define

begin_define
DECL|macro|GIMP_DATA_LOADER_FACTORY (obj)
define|#
directive|define
name|GIMP_DATA_LOADER_FACTORY
parameter_list|(
name|obj
parameter_list|)
value|(G_TYPE_CHECK_INSTANCE_CAST ((obj), GIMP_TYPE_DATA_LOADER_FACTORY, GimpDataLoaderFactory))
end_define

begin_define
DECL|macro|GIMP_DATA_LOADER_FACTORY_CLASS (klass)
define|#
directive|define
name|GIMP_DATA_LOADER_FACTORY_CLASS
parameter_list|(
name|klass
parameter_list|)
value|(G_TYPE_CHECK_CLASS_CAST ((klass), GIMP_TYPE_DATA_LOADER_FACTORY, GimpDataLoaderFactoryClass))
end_define

begin_define
DECL|macro|GIMP_IS_DATA_LOADER_FACTORY (obj)
define|#
directive|define
name|GIMP_IS_DATA_LOADER_FACTORY
parameter_list|(
name|obj
parameter_list|)
value|(G_TYPE_CHECK_INSTANCE_TYPE ((obj), GIMP_TYPE_DATA_LOADER_FACTORY))
end_define

begin_define
DECL|macro|GIMP_IS_DATA_LOADER_FACTORY_CLASS (klass)
define|#
directive|define
name|GIMP_IS_DATA_LOADER_FACTORY_CLASS
parameter_list|(
name|klass
parameter_list|)
value|(G_TYPE_CHECK_CLASS_TYPE ((klass), GIMP_TYPE_DATA_LOADER_FACTORY))
end_define

begin_define
DECL|macro|GIMP_DATA_LOADER_FACTORY_GET_CLASS (obj)
define|#
directive|define
name|GIMP_DATA_LOADER_FACTORY_GET_CLASS
parameter_list|(
name|obj
parameter_list|)
value|(G_TYPE_INSTANCE_GET_CLASS ((obj), GIMP_TYPE_DATA_LOADER_FACTORY, GimpDataLoaderFactoryClass))
end_define

begin_typedef
DECL|typedef|GimpDataLoaderFactoryPrivate
typedef|typedef
name|struct
name|_GimpDataLoaderFactoryPrivate
name|GimpDataLoaderFactoryPrivate
typedef|;
end_typedef

begin_typedef
DECL|typedef|GimpDataLoaderFactoryClass
typedef|typedef
name|struct
name|_GimpDataLoaderFactoryClass
name|GimpDataLoaderFactoryClass
typedef|;
end_typedef

begin_struct
DECL|struct|_GimpDataLoaderFactory
struct|struct
name|_GimpDataLoaderFactory
block|{
DECL|member|parent_instance
name|GimpDataFactory
name|parent_instance
decl_stmt|;
DECL|member|priv
name|GimpDataLoaderFactoryPrivate
modifier|*
name|priv
decl_stmt|;
block|}
struct|;
end_struct

begin_struct
DECL|struct|_GimpDataLoaderFactoryClass
struct|struct
name|_GimpDataLoaderFactoryClass
block|{
DECL|member|parent_class
name|GimpDataFactoryClass
name|parent_class
decl_stmt|;
block|}
struct|;
end_struct

begin_decl_stmt
name|GType
name|gimp_data_loader_factory_get_type
argument_list|(
name|void
argument_list|)
name|G_GNUC_CONST
decl_stmt|;
end_decl_stmt

begin_function_decl
name|GimpDataFactory
modifier|*
name|gimp_data_loader_factory_new
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
name|gimp_data_loader_factory_add_loader
parameter_list|(
name|GimpDataFactory
modifier|*
name|factory
parameter_list|,
specifier|const
name|gchar
modifier|*
name|name
parameter_list|,
name|GimpDataLoadFunc
name|load_func
parameter_list|,
specifier|const
name|gchar
modifier|*
name|extension
parameter_list|,
name|gboolean
name|writable
parameter_list|)
function_decl|;
end_function_decl

begin_function_decl
name|void
name|gimp_data_loader_factory_add_fallback
parameter_list|(
name|GimpDataFactory
modifier|*
name|factory
parameter_list|,
specifier|const
name|gchar
modifier|*
name|name
parameter_list|,
name|GimpDataLoadFunc
name|load_func
parameter_list|)
function_decl|;
end_function_decl

begin_endif
endif|#
directive|endif
end_endif

begin_comment
comment|/*  __GIMP_DATA_LOADER_FACTORY_H__  */
end_comment

end_unit

