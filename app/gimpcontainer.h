begin_unit|revision:0.9.5;language:C;cregit-version:0.0.1
begin_comment
comment|/* The GIMP -- an image manipulation program  * Copyright (C) 1995-1997 Spencer Kimball and Peter Mattis  *  * This program is free software; you can redistribute it and/or modify  * it under the terms of the GNU General Public License as published by  * the Free Software Foundation; either version 2 of the License, or  * (at your option) any later version.  *  * This program is distributed in the hope that it will be useful,  * but WITHOUT ANY WARRANTY; without even the implied warranty of  * MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the  * GNU General Public License for more details.  *  * You should have received a copy of the GNU General Public License  * along with this program; if not, write to the Free Software  * Foundation, Inc., 59 Temple Place - Suite 330, Boston, MA 02111-1307, USA.  */
end_comment

begin_ifndef
ifndef|#
directive|ifndef
name|__GIMP_CONTAINER_H__
end_ifndef

begin_define
DECL|macro|__GIMP_CONTAINER_H__
define|#
directive|define
name|__GIMP_CONTAINER_H__
end_define

begin_include
include|#
directive|include
file|"gimpobject.h"
end_include

begin_typedef
typedef|typedef
enum|enum
DECL|enum|__anon2c10f3600103
block|{
DECL|enumerator|GIMP_CONTAINER_POLICY_STRONG
name|GIMP_CONTAINER_POLICY_STRONG
block|,
DECL|enumerator|GIMP_CONTAINER_POLICY_WEAK
name|GIMP_CONTAINER_POLICY_WEAK
DECL|typedef|GimpContainerPolicy
block|}
name|GimpContainerPolicy
typedef|;
end_typedef

begin_define
DECL|macro|GIMP_TYPE_CONTAINER
define|#
directive|define
name|GIMP_TYPE_CONTAINER
value|(gimp_container_get_type ())
end_define

begin_define
DECL|macro|GIMP_CONTAINER (obj)
define|#
directive|define
name|GIMP_CONTAINER
parameter_list|(
name|obj
parameter_list|)
value|(GTK_CHECK_CAST ((obj), GIMP_TYPE_CONTAINER, GimpContainer))
end_define

begin_define
DECL|macro|GIMP_CONTAINER_CLASS (klass)
define|#
directive|define
name|GIMP_CONTAINER_CLASS
parameter_list|(
name|klass
parameter_list|)
value|(GTK_CHECK_CLASS_CAST ((klass), GIMP_TYPE_CONTAINER, GimpContainerClass))
end_define

begin_define
DECL|macro|GIMP_IS_CONTAINER (obj)
define|#
directive|define
name|GIMP_IS_CONTAINER
parameter_list|(
name|obj
parameter_list|)
value|(GTK_CHECK_TYPE ((obj), GIMP_TYPE_CONTAINER))
end_define

begin_define
DECL|macro|GIMP_IS_CONTAINER_CLASS (klass)
define|#
directive|define
name|GIMP_IS_CONTAINER_CLASS
parameter_list|(
name|klass
parameter_list|)
value|(GTK_CHECK_CLASS_TYPE ((klass), GIMP_TYPE_CONTAINER))
end_define

begin_typedef
DECL|typedef|GimpContainerClass
typedef|typedef
name|struct
name|_GimpContainerClass
name|GimpContainerClass
typedef|;
end_typedef

begin_struct
DECL|struct|_GimpContainer
struct|struct
name|_GimpContainer
block|{
DECL|member|parent_instance
name|GimpObject
name|parent_instance
decl_stmt|;
comment|/*  public, read-only  */
DECL|member|children_type
name|GtkType
name|children_type
decl_stmt|;
DECL|member|policy
name|GimpContainerPolicy
name|policy
decl_stmt|;
DECL|member|num_children
name|gint
name|num_children
decl_stmt|;
DECL|member|children
name|GList
modifier|*
name|children
decl_stmt|;
comment|/*  private  */
DECL|member|handlers
name|GList
modifier|*
name|handlers
decl_stmt|;
block|}
struct|;
end_struct

begin_struct
DECL|struct|_GimpContainerClass
struct|struct
name|_GimpContainerClass
block|{
DECL|member|parent_class
name|GimpObjectClass
name|parent_class
decl_stmt|;
DECL|member|add
name|void
function_decl|(
modifier|*
name|add
function_decl|)
parameter_list|(
name|GimpContainer
modifier|*
name|container
parameter_list|,
name|GimpObject
modifier|*
name|object
parameter_list|)
function_decl|;
DECL|member|remove
name|void
function_decl|(
modifier|*
name|remove
function_decl|)
parameter_list|(
name|GimpContainer
modifier|*
name|container
parameter_list|,
name|GimpObject
modifier|*
name|object
parameter_list|)
function_decl|;
block|}
struct|;
end_struct

begin_function_decl
name|GtkType
name|gimp_container_get_type
parameter_list|(
name|void
parameter_list|)
function_decl|;
end_function_decl

begin_function_decl
name|GimpContainer
modifier|*
name|gimp_container_new
parameter_list|(
name|GtkType
name|children_type
parameter_list|,
name|GimpContainerPolicy
name|policy
parameter_list|)
function_decl|;
end_function_decl

begin_function_decl
name|GtkType
name|gimp_container_children_type
parameter_list|(
specifier|const
name|GimpContainer
modifier|*
name|container
parameter_list|)
function_decl|;
end_function_decl

begin_function_decl
name|GimpContainerPolicy
name|gimp_container_policy
parameter_list|(
specifier|const
name|GimpContainer
modifier|*
name|container
parameter_list|)
function_decl|;
end_function_decl

begin_function_decl
name|gint
name|gimp_container_num_children
parameter_list|(
specifier|const
name|GimpContainer
modifier|*
name|container
parameter_list|)
function_decl|;
end_function_decl

begin_function_decl
name|gboolean
name|gimp_container_add
parameter_list|(
name|GimpContainer
modifier|*
name|container
parameter_list|,
name|GimpObject
modifier|*
name|object
parameter_list|)
function_decl|;
end_function_decl

begin_function_decl
name|gboolean
name|gimp_container_remove
parameter_list|(
name|GimpContainer
modifier|*
name|container
parameter_list|,
name|GimpObject
modifier|*
name|object
parameter_list|)
function_decl|;
end_function_decl

begin_function_decl
specifier|const
name|GList
modifier|*
name|gimp_container_lookup
parameter_list|(
name|GimpContainer
modifier|*
name|container
parameter_list|,
name|GimpObject
modifier|*
name|object
parameter_list|)
function_decl|;
end_function_decl

begin_function_decl
name|void
name|gimp_container_foreach
parameter_list|(
name|GimpContainer
modifier|*
name|container
parameter_list|,
name|GFunc
name|func
parameter_list|,
name|gpointer
name|user_data
parameter_list|)
function_decl|;
end_function_decl

begin_function_decl
name|GQuark
name|gimp_container_add_handler
parameter_list|(
name|GimpContainer
modifier|*
name|container
parameter_list|,
specifier|const
name|gchar
modifier|*
name|signame
parameter_list|,
name|GtkSignalFunc
name|handler
parameter_list|,
name|gpointer
name|user_data
parameter_list|)
function_decl|;
end_function_decl

begin_function_decl
name|void
name|gimp_container_remove_handler
parameter_list|(
name|GimpContainer
modifier|*
name|container
parameter_list|,
name|GQuark
name|id
parameter_list|)
function_decl|;
end_function_decl

begin_endif
endif|#
directive|endif
end_endif

begin_comment
comment|/* __GIMP_CONTAINER_H__ */
end_comment

end_unit

