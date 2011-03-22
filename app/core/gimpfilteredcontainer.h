begin_unit|revision:0.9.5;language:C;cregit-version:0.0.1
begin_comment
comment|/* GIMP - The GNU Image Manipulation Program  * Copyright (C) 1995-1997 Spencer Kimball and Peter Mattis  *  * gimpfilteredcontainer.h  * Copyright (C) 2008 Aurimas JuÅ¡ka<aurisj@svn.gnome.org>  *               2011 Michael Natterer<mitch@gimp.org>  *  * This program is free software: you can redistribute it and/or modify  * it under the terms of the GNU General Public License as published by  * the Free Software Foundation; either version 3 of the License, or  * (at your option) any later version.  *  * This program is distributed in the hope that it will be useful,  * but WITHOUT ANY WARRANTY; without even the implied warranty of  * MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the  * GNU General Public License for more details.  *  * You should have received a copy of the GNU General Public License  * along with this program.  If not, see<http://www.gnu.org/licenses/>.  */
end_comment

begin_ifndef
ifndef|#
directive|ifndef
name|__GIMP_FILTERED_CONTAINER_H__
end_ifndef

begin_define
DECL|macro|__GIMP_FILTERED_CONTAINER_H__
define|#
directive|define
name|__GIMP_FILTERED_CONTAINER_H__
end_define

begin_include
include|#
directive|include
file|"gimplist.h"
end_include

begin_define
DECL|macro|GIMP_TYPE_FILTERED_CONTAINER
define|#
directive|define
name|GIMP_TYPE_FILTERED_CONTAINER
value|(gimp_filtered_container_get_type ())
end_define

begin_define
DECL|macro|GIMP_FILTERED_CONTAINER (obj)
define|#
directive|define
name|GIMP_FILTERED_CONTAINER
parameter_list|(
name|obj
parameter_list|)
value|(G_TYPE_CHECK_INSTANCE_CAST ((obj), GIMP_TYPE_FILTERED_CONTAINER, GimpFilteredContainer))
end_define

begin_define
DECL|macro|GIMP_FILTERED_CONTAINER_CLASS (klass)
define|#
directive|define
name|GIMP_FILTERED_CONTAINER_CLASS
parameter_list|(
name|klass
parameter_list|)
value|(G_TYPE_CHECK_CLASS_CAST ((klass), GIMP_TYPE_FILTERED_CONTAINER, GimpFilteredContainerClass))
end_define

begin_define
DECL|macro|GIMP_IS_FILTERED_CONTAINER (obj)
define|#
directive|define
name|GIMP_IS_FILTERED_CONTAINER
parameter_list|(
name|obj
parameter_list|)
value|(G_TYPE_CHECK_INSTANCE_TYPE ((obj), GIMP_TYPE_FILTERED_CONTAINER))
end_define

begin_define
DECL|macro|GIMP_IS_FILTERED_CONTAINER_CLASS (class)
define|#
directive|define
name|GIMP_IS_FILTERED_CONTAINER_CLASS
parameter_list|(
name|class
parameter_list|)
value|(G_TYPE_CHECK_CLASS_TYPE ((class), GIMP_TYPE_FILTERED_CONTAINER))
end_define

begin_define
DECL|macro|GIMP_FILTERED_CONTAINER_GET_CLASS (obj)
define|#
directive|define
name|GIMP_FILTERED_CONTAINER_GET_CLASS
parameter_list|(
name|obj
parameter_list|)
value|(G_TYPE_INSTANCE_GET_CLASS ((obj), GIMP_TYPE_FILTERED_CONTAINER, GimpFilteredContainerClass))
end_define

begin_typedef
DECL|typedef|GimpFilteredContainerClass
typedef|typedef
name|struct
name|_GimpFilteredContainerClass
name|GimpFilteredContainerClass
typedef|;
end_typedef

begin_struct
DECL|struct|_GimpFilteredContainer
struct|struct
name|_GimpFilteredContainer
block|{
DECL|member|parent_instance
name|GimpList
name|parent_instance
decl_stmt|;
DECL|member|src_container
name|GimpContainer
modifier|*
name|src_container
decl_stmt|;
DECL|member|filter_func
name|GimpObjectFilterFunc
name|filter_func
decl_stmt|;
DECL|member|filter_data
name|gpointer
name|filter_data
decl_stmt|;
block|}
struct|;
end_struct

begin_struct
DECL|struct|_GimpFilteredContainerClass
struct|struct
name|_GimpFilteredContainerClass
block|{
DECL|member|parent_class
name|GimpContainerClass
name|parent_class
decl_stmt|;
block|}
struct|;
end_struct

begin_decl_stmt
name|GType
name|gimp_filtered_container_get_type
argument_list|(
name|void
argument_list|)
name|G_GNUC_CONST
decl_stmt|;
end_decl_stmt

begin_function_decl
name|GimpContainer
modifier|*
name|gimp_filtered_container_new
parameter_list|(
name|GimpContainer
modifier|*
name|src_container
parameter_list|,
name|GimpObjectFilterFunc
name|filter_func
parameter_list|,
name|gpointer
name|filter_data
parameter_list|)
function_decl|;
end_function_decl

begin_endif
endif|#
directive|endif
end_endif

begin_comment
comment|/* __GIMP_FILTERED_CONTAINER_H__ */
end_comment

end_unit

