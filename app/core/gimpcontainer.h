begin_unit|revision:0.9.5;language:C;cregit-version:0.0.1
begin_comment
comment|/* The GIMP -- an image manipulation program  * Copyright (C) 1995-1997 Spencer Kimball and Peter Mattis  *  * gimpcontainer.h  * Copyright (C) 2001 Michael Natterer<mitch@gimp.org>  *  * This program is free software; you can redistribute it and/or modify  * it under the terms of the GNU General Public License as published by  * the Free Software Foundation; either version 2 of the License, or  * (at your option) any later version.  *  * This program is distributed in the hope that it will be useful,  * but WITHOUT ANY WARRANTY; without even the implied warranty of  * MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the  * GNU General Public License for more details.  *  * You should have received a copy of the GNU General Public License  * along with this program; if not, write to the Free Software  * Foundation, Inc., 59 Temple Place - Suite 330, Boston, MA 02111-1307, USA.  */
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
DECL|enum|__anon2c18667d0103
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
DECL|macro|GIMP_TYPE_CONTAINER_POLICY
define|#
directive|define
name|GIMP_TYPE_CONTAINER_POLICY
value|(gimp_container_policy_get_type ())
end_define

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
value|(G_TYPE_CHECK_INSTANCE_CAST ((obj), GIMP_TYPE_CONTAINER, GimpContainer))
end_define

begin_define
DECL|macro|GIMP_CONTAINER_CLASS (klass)
define|#
directive|define
name|GIMP_CONTAINER_CLASS
parameter_list|(
name|klass
parameter_list|)
value|(G_TYPE_CHECK_CLASS_CAST ((klass), GIMP_TYPE_CONTAINER, GimpContainerClass))
end_define

begin_define
DECL|macro|GIMP_IS_CONTAINER (obj)
define|#
directive|define
name|GIMP_IS_CONTAINER
parameter_list|(
name|obj
parameter_list|)
value|(G_TYPE_CHECK_INSTANCE_TYPE ((obj), GIMP_TYPE_CONTAINER))
end_define

begin_define
DECL|macro|GIMP_IS_CONTAINER_CLASS (klass)
define|#
directive|define
name|GIMP_IS_CONTAINER_CLASS
parameter_list|(
name|klass
parameter_list|)
value|(G_TYPE_CHECK_CLASS_TYPE ((klass), GIMP_TYPE_CONTAINER))
end_define

begin_define
DECL|macro|GIMP_CONTAINER_GET_CLASS (obj)
define|#
directive|define
name|GIMP_CONTAINER_GET_CLASS
parameter_list|(
name|obj
parameter_list|)
value|(G_TYPE_INSTANCE_GET_CLASS ((obj), GIMP_TYPE_CONTAINER, GimpContainerClass))
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
name|GType
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
comment|/*  private  */
DECL|member|handlers
name|GList
modifier|*
name|handlers
decl_stmt|;
DECL|member|freeze_count
name|gint
name|freeze_count
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
comment|/*  signals  */
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
DECL|member|reorder
name|void
function_decl|(
modifier|*
name|reorder
function_decl|)
parameter_list|(
name|GimpContainer
modifier|*
name|container
parameter_list|,
name|GimpObject
modifier|*
name|object
parameter_list|,
name|gint
name|new_index
parameter_list|)
function_decl|;
DECL|member|freeze
name|void
function_decl|(
modifier|*
name|freeze
function_decl|)
parameter_list|(
name|GimpContainer
modifier|*
name|container
parameter_list|)
function_decl|;
DECL|member|thaw
name|void
function_decl|(
modifier|*
name|thaw
function_decl|)
parameter_list|(
name|GimpContainer
modifier|*
name|container
parameter_list|)
function_decl|;
comment|/*  virtual functions  */
DECL|member|have
name|gboolean
function_decl|(
modifier|*
name|have
function_decl|)
parameter_list|(
specifier|const
name|GimpContainer
modifier|*
name|container
parameter_list|,
specifier|const
name|GimpObject
modifier|*
name|object
parameter_list|)
function_decl|;
DECL|member|foreach
name|void
function_decl|(
modifier|*
name|foreach
function_decl|)
parameter_list|(
specifier|const
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
DECL|member|get_child_by_name
name|GimpObject
modifier|*
function_decl|(
modifier|*
name|get_child_by_name
function_decl|)
parameter_list|(
specifier|const
name|GimpContainer
modifier|*
name|container
parameter_list|,
specifier|const
name|gchar
modifier|*
name|name
parameter_list|)
function_decl|;
DECL|member|get_child_by_index
name|GimpObject
modifier|*
function_decl|(
modifier|*
name|get_child_by_index
function_decl|)
parameter_list|(
specifier|const
name|GimpContainer
modifier|*
name|container
parameter_list|,
name|gint
name|index
parameter_list|)
function_decl|;
DECL|member|get_child_index
name|gint
function_decl|(
modifier|*
name|get_child_index
function_decl|)
parameter_list|(
specifier|const
name|GimpContainer
modifier|*
name|container
parameter_list|,
specifier|const
name|GimpObject
modifier|*
name|object
parameter_list|)
function_decl|;
block|}
struct|;
end_struct

begin_decl_stmt
name|GType
name|gimp_container_policy_get_type
argument_list|(
name|void
argument_list|)
name|G_GNUC_CONST
decl_stmt|;
end_decl_stmt

begin_decl_stmt
name|GType
name|gimp_container_get_type
argument_list|(
name|void
argument_list|)
name|G_GNUC_CONST
decl_stmt|;
end_decl_stmt

begin_function_decl
name|GType
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
name|gboolean
name|gimp_container_insert
parameter_list|(
name|GimpContainer
modifier|*
name|container
parameter_list|,
name|GimpObject
modifier|*
name|object
parameter_list|,
name|gint
name|new_index
parameter_list|)
function_decl|;
end_function_decl

begin_function_decl
name|gboolean
name|gimp_container_reorder
parameter_list|(
name|GimpContainer
modifier|*
name|container
parameter_list|,
name|GimpObject
modifier|*
name|object
parameter_list|,
name|gint
name|new_index
parameter_list|)
function_decl|;
end_function_decl

begin_function_decl
name|void
name|gimp_container_freeze
parameter_list|(
name|GimpContainer
modifier|*
name|container
parameter_list|)
function_decl|;
end_function_decl

begin_function_decl
name|void
name|gimp_container_thaw
parameter_list|(
name|GimpContainer
modifier|*
name|container
parameter_list|)
function_decl|;
end_function_decl

begin_function_decl
name|gboolean
name|gimp_container_frozen
parameter_list|(
name|GimpContainer
modifier|*
name|container
parameter_list|)
function_decl|;
end_function_decl

begin_function_decl
name|gboolean
name|gimp_container_have
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
name|GimpObject
modifier|*
name|gimp_container_get_child_by_name
parameter_list|(
specifier|const
name|GimpContainer
modifier|*
name|container
parameter_list|,
specifier|const
name|gchar
modifier|*
name|name
parameter_list|)
function_decl|;
end_function_decl

begin_function_decl
name|GimpObject
modifier|*
name|gimp_container_get_child_by_index
parameter_list|(
specifier|const
name|GimpContainer
modifier|*
name|container
parameter_list|,
name|gint
name|index
parameter_list|)
function_decl|;
end_function_decl

begin_function_decl
name|gint
name|gimp_container_get_child_index
parameter_list|(
specifier|const
name|GimpContainer
modifier|*
name|container
parameter_list|,
specifier|const
name|GimpObject
modifier|*
name|object
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
name|GCallback
name|callback
parameter_list|,
name|gpointer
name|callback_data
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

