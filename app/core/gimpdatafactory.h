begin_unit|revision:0.9.5;language:C;cregit-version:0.0.1
begin_comment
comment|/* The GIMP -- an image manipulation program  * Copyright (C) 1995 Spencer Kimball and Peter Mattis  *  * This program is free software; you can redistribute it and/or modify  * it under the terms of the GNU General Public License as published by  * the Free Software Foundation; either version 2 of the License, or  * (at your option) any later version.  *  * This program is distributed in the hope that it will be useful,  * but WITHOUT ANY WARRANTY; without even the implied warranty of  * MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the  * GNU General Public License for more details.  *  * You should have received a copy of the GNU General Public License  * along with this program; if not, write to the Free Software  * Foundation, Inc., 59 Temple Place - Suite 330, Boston, MA 02111-1307, USA.  */
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
DECL|typedef|GimpDataNewDefaultFunc
typedef|typedef
name|GimpData
modifier|*
function_decl|(
modifier|*
name|GimpDataNewDefaultFunc
function_decl|)
parameter_list|(
specifier|const
name|gchar
modifier|*
name|name
parameter_list|)
function_decl|;
end_typedef

begin_typedef
DECL|typedef|GimpDataNewStandardFunc
typedef|typedef
name|GimpData
modifier|*
function_decl|(
modifier|*
name|GimpDataNewStandardFunc
function_decl|)
parameter_list|(
name|void
parameter_list|)
function_decl|;
end_typedef

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
value|(GTK_CHECK_CAST ((obj), GIMP_TYPE_DATA_FACTORY, GimpDataFactory))
end_define

begin_define
DECL|macro|GIMP_DATA_FACTORY_CLASS (klass)
define|#
directive|define
name|GIMP_DATA_FACTORY_CLASS
parameter_list|(
name|klass
parameter_list|)
value|(GTK_CHECK_CLASS_CAST ((klass), GIMP_TYPE_DATA_FACTORY, GimpDataFactoryClass))
end_define

begin_define
DECL|macro|GIMP_IS_DATA_FACTORY (obj)
define|#
directive|define
name|GIMP_IS_DATA_FACTORY
parameter_list|(
name|obj
parameter_list|)
value|(GTK_CHECK_TYPE ((obj), GIMP_TYPE_DATA_FACTORY))
end_define

begin_define
DECL|macro|GIMP_IS_DATA_FACTORY_CLASS (klass)
define|#
directive|define
name|GIMP_IS_DATA_FACTORY_CLASS
parameter_list|(
name|klass
parameter_list|)
value|(GTK_CHECK_CLASS_TYPE ((klass), GIMP_TYPE_DATA_FACTORY))
end_define

begin_typedef
DECL|typedef|GimpDataFactoryClass
typedef|typedef
name|struct
name|_GimpDataFactoryClass
name|GimpDataFactoryClass
typedef|;
end_typedef

begin_struct
DECL|struct|_GimpDataFactory
struct|struct
name|_GimpDataFactory
block|{
DECL|member|object
name|GimpObject
modifier|*
name|object
decl_stmt|;
DECL|member|container
name|GimpContainer
modifier|*
name|container
decl_stmt|;
DECL|member|data_path
specifier|const
name|gchar
modifier|*
modifier|*
name|data_path
decl_stmt|;
DECL|member|new_default_data_func
name|GimpDataNewDefaultFunc
name|new_default_data_func
decl_stmt|;
DECL|member|new_standard_data_func
name|GimpDataNewStandardFunc
name|new_standard_data_func
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

begin_function_decl
name|GtkType
name|gimp_data_factory_get_type
parameter_list|(
name|void
parameter_list|)
function_decl|;
end_function_decl

begin_function_decl
name|GimpDataFactory
modifier|*
name|gimp_data_factory_new
parameter_list|(
name|GtkType
name|data_type
parameter_list|,
specifier|const
name|gchar
modifier|*
modifier|*
name|data_path
parameter_list|,
name|GimpDataNewDefaultFunc
name|default_func
parameter_list|,
name|GimpDataNewStandardFunc
name|standard_func
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

begin_endif
endif|#
directive|endif
end_endif

begin_comment
comment|/*  __GIMP_DATA_FACTORY_H__  */
end_comment

end_unit

