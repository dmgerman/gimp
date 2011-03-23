begin_unit|revision:0.9.5;language:C;cregit-version:0.0.1
begin_comment
comment|/* GIMP - The GNU Image Manipulation Program  * Copyright (C) 1995-1997 Spencer Kimball and Peter Mattis  *  * gimptaggedcontainer.h  * Copyright (C) 2008 Aurimas JuÅ¡ka<aurisj@svn.gnome.org>  *  * This program is free software: you can redistribute it and/or modify  * it under the terms of the GNU General Public License as published by  * the Free Software Foundation; either version 3 of the License, or  * (at your option) any later version.  *  * This program is distributed in the hope that it will be useful,  * but WITHOUT ANY WARRANTY; without even the implied warranty of  * MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the  * GNU General Public License for more details.  *  * You should have received a copy of the GNU General Public License  * along with this program.  If not, see<http://www.gnu.org/licenses/>.  */
end_comment

begin_ifndef
ifndef|#
directive|ifndef
name|__GIMP_TAGGED_CONTAINER_H__
end_ifndef

begin_define
DECL|macro|__GIMP_TAGGED_CONTAINER_H__
define|#
directive|define
name|__GIMP_TAGGED_CONTAINER_H__
end_define

begin_include
include|#
directive|include
file|"gimpfilteredcontainer.h"
end_include

begin_define
DECL|macro|GIMP_TYPE_TAGGED_CONTAINER
define|#
directive|define
name|GIMP_TYPE_TAGGED_CONTAINER
value|(gimp_tagged_container_get_type ())
end_define

begin_define
DECL|macro|GIMP_TAGGED_CONTAINER (obj)
define|#
directive|define
name|GIMP_TAGGED_CONTAINER
parameter_list|(
name|obj
parameter_list|)
value|(G_TYPE_CHECK_INSTANCE_CAST ((obj), GIMP_TYPE_TAGGED_CONTAINER, GimpTaggedContainer))
end_define

begin_define
DECL|macro|GIMP_TAGGED_CONTAINER_CLASS (klass)
define|#
directive|define
name|GIMP_TAGGED_CONTAINER_CLASS
parameter_list|(
name|klass
parameter_list|)
value|(G_TYPE_CHECK_CLASS_CAST ((klass), GIMP_TYPE_TAGGED_CONTAINER, GimpTaggedContainerClass))
end_define

begin_define
DECL|macro|GIMP_IS_TAGGED_CONTAINER (obj)
define|#
directive|define
name|GIMP_IS_TAGGED_CONTAINER
parameter_list|(
name|obj
parameter_list|)
value|(G_TYPE_CHECK_INSTANCE_TYPE ((obj), GIMP_TYPE_TAGGED_CONTAINER))
end_define

begin_define
DECL|macro|GIMP_IS_TAGGED_CONTAINER_CLASS (class)
define|#
directive|define
name|GIMP_IS_TAGGED_CONTAINER_CLASS
parameter_list|(
name|class
parameter_list|)
value|(G_TYPE_CHECK_CLASS_TYPE ((class), GIMP_TYPE_TAGGED_CONTAINER))
end_define

begin_define
DECL|macro|GIMP_TAGGED_CONTAINER_GET_CLASS (obj)
define|#
directive|define
name|GIMP_TAGGED_CONTAINER_GET_CLASS
parameter_list|(
name|obj
parameter_list|)
value|(G_TYPE_INSTANCE_GET_CLASS ((obj), GIMP_TYPE_TAGGED_CONTAINER, GimpTaggedContainerClass))
end_define

begin_typedef
DECL|typedef|GimpTaggedContainerClass
typedef|typedef
name|struct
name|_GimpTaggedContainerClass
name|GimpTaggedContainerClass
typedef|;
end_typedef

begin_struct
DECL|struct|_GimpTaggedContainer
struct|struct
name|_GimpTaggedContainer
block|{
DECL|member|parent_instance
name|GimpFilteredContainer
name|parent_instance
decl_stmt|;
DECL|member|src_container
name|GimpContainer
modifier|*
name|src_container
decl_stmt|;
DECL|member|filter
name|GList
modifier|*
name|filter
decl_stmt|;
DECL|member|tag_ref_counts
name|GHashTable
modifier|*
name|tag_ref_counts
decl_stmt|;
DECL|member|tag_count
name|gint
name|tag_count
decl_stmt|;
block|}
struct|;
end_struct

begin_struct
DECL|struct|_GimpTaggedContainerClass
struct|struct
name|_GimpTaggedContainerClass
block|{
DECL|member|parent_class
name|GimpFilteredContainerClass
name|parent_class
decl_stmt|;
DECL|member|tag_count_changed
name|void
function_decl|(
modifier|*
name|tag_count_changed
function_decl|)
parameter_list|(
name|GimpTaggedContainer
modifier|*
name|container
parameter_list|,
name|gint
name|count
parameter_list|)
function_decl|;
block|}
struct|;
end_struct

begin_decl_stmt
name|GType
name|gimp_tagged_container_get_type
argument_list|(
name|void
argument_list|)
name|G_GNUC_CONST
decl_stmt|;
end_decl_stmt

begin_function_decl
name|GimpContainer
modifier|*
name|gimp_tagged_container_new
parameter_list|(
name|GimpContainer
modifier|*
name|src_container
parameter_list|)
function_decl|;
end_function_decl

begin_function_decl
name|void
name|gimp_tagged_container_set_filter
parameter_list|(
name|GimpTaggedContainer
modifier|*
name|tagged_container
parameter_list|,
name|GList
modifier|*
name|tags
parameter_list|)
function_decl|;
end_function_decl

begin_function_decl
specifier|const
name|GList
modifier|*
name|gimp_tagged_container_get_filter
parameter_list|(
name|GimpTaggedContainer
modifier|*
name|tagged_container
parameter_list|)
function_decl|;
end_function_decl

begin_function_decl
name|gint
name|gimp_tagged_container_get_tag_count
parameter_list|(
name|GimpTaggedContainer
modifier|*
name|container
parameter_list|)
function_decl|;
end_function_decl

begin_endif
endif|#
directive|endif
end_endif

begin_comment
comment|/* __GIMP_TAGGED_CONTAINER_H__ */
end_comment

end_unit

