begin_unit|revision:0.9.5;language:C;cregit-version:0.0.1
begin_comment
comment|/* The GIMP -- an image manipulation program  * Copyright (C) 1995-1997 Spencer Kimball and Peter Mattis  *  * This program is free software; you can redistribute it and/or modify  * it under the terms of the GNU General Public License as published by  * the Free Software Foundation; either version 2 of the License, or  * (at your option) any later version.  *  * This program is distributed in the hope that it will be useful,  * but WITHOUT ANY WARRANTY; without even the implied warranty of  * MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the  * GNU General Public License for more details.  *  * You should have received a copy of the GNU General Public License  * along with this program; if not, write to the Free Software  * Foundation, Inc., 59 Temple Place - Suite 330, Boston, MA 02111-1307, USA.  */
end_comment

begin_ifndef
ifndef|#
directive|ifndef
name|__GIMP_LIST_H__
end_ifndef

begin_define
DECL|macro|__GIMP_LIST_H__
define|#
directive|define
name|__GIMP_LIST_H__
end_define

begin_include
include|#
directive|include
file|"gimpcontainer.h"
end_include

begin_define
DECL|macro|GIMP_TYPE_LIST
define|#
directive|define
name|GIMP_TYPE_LIST
value|(gimp_list_get_type ())
end_define

begin_define
DECL|macro|GIMP_LIST (obj)
define|#
directive|define
name|GIMP_LIST
parameter_list|(
name|obj
parameter_list|)
value|(GTK_CHECK_CAST ((obj), GIMP_TYPE_LIST, GimpList))
end_define

begin_define
DECL|macro|GIMP_LIST_CLASS (klass)
define|#
directive|define
name|GIMP_LIST_CLASS
parameter_list|(
name|klass
parameter_list|)
value|(GTK_CHECK_CLASS_CAST ((klass), GIMP_TYPE_LIST, GimpListClass))
end_define

begin_define
DECL|macro|GIMP_IS_LIST (obj)
define|#
directive|define
name|GIMP_IS_LIST
parameter_list|(
name|obj
parameter_list|)
value|(GTK_CHECK_TYPE ((obj), GIMP_TYPE_LIST))
end_define

begin_define
DECL|macro|GIMP_IS_LIST_CLASS (klass)
define|#
directive|define
name|GIMP_IS_LIST_CLASS
parameter_list|(
name|klass
parameter_list|)
value|(GTK_CHECK_CLASS_TYPE ((klass), GIMP_TYPE_LIST))
end_define

begin_typedef
DECL|typedef|GimpListClass
typedef|typedef
name|struct
name|_GimpListClass
name|GimpListClass
typedef|;
end_typedef

begin_struct
DECL|struct|_GimpList
struct|struct
name|_GimpList
block|{
DECL|member|parent_instance
name|GimpContainer
name|parent_instance
decl_stmt|;
DECL|member|list
name|GList
modifier|*
name|list
decl_stmt|;
block|}
struct|;
end_struct

begin_struct
DECL|struct|_GimpListClass
struct|struct
name|_GimpListClass
block|{
DECL|member|parent_class
name|GimpContainerClass
name|parent_class
decl_stmt|;
block|}
struct|;
end_struct

begin_function_decl
name|GtkType
name|gimp_list_get_type
parameter_list|(
name|void
parameter_list|)
function_decl|;
end_function_decl

begin_function_decl
name|GimpList
modifier|*
name|gimp_list_new
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
name|GimpObject
modifier|*
name|gimp_list_get_child_by_name
parameter_list|(
specifier|const
name|GimpList
modifier|*
name|list
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
name|gimp_list_get_child_by_index
parameter_list|(
specifier|const
name|GimpList
modifier|*
name|list
parameter_list|,
name|gint
name|index
parameter_list|)
function_decl|;
end_function_decl

begin_function_decl
name|gint
name|gimp_list_get_child_index
parameter_list|(
specifier|const
name|GimpList
modifier|*
name|list
parameter_list|,
specifier|const
name|GimpObject
modifier|*
name|object
parameter_list|)
function_decl|;
end_function_decl

begin_endif
endif|#
directive|endif
end_endif

begin_comment
comment|/* __GIMP_LIST_H__ */
end_comment

end_unit

