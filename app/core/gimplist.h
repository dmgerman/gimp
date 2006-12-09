begin_unit|revision:0.9.5;language:C;cregit-version:0.0.1
begin_comment
comment|/* GIMP - The GNU Image Manipulation Program  * Copyright (C) 1995-1997 Spencer Kimball and Peter Mattis  *  * gimplist.h  * Copyright (C) 2001 Michael Natterer<mitch@gimp.org>  *  * This program is free software; you can redistribute it and/or modify  * it under the terms of the GNU General Public License as published by  * the Free Software Foundation; either version 2 of the License, or  * (at your option) any later version.  *  * This program is distributed in the hope that it will be useful,  * but WITHOUT ANY WARRANTY; without even the implied warranty of  * MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the  * GNU General Public License for more details.  *  * You should have received a copy of the GNU General Public License  * along with this program; if not, write to the Free Software  * Foundation, Inc., 59 Temple Place - Suite 330, Boston, MA 02111-1307, USA.  */
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
value|(G_TYPE_CHECK_INSTANCE_CAST ((obj), GIMP_TYPE_LIST, GimpList))
end_define

begin_define
DECL|macro|GIMP_LIST_CLASS (klass)
define|#
directive|define
name|GIMP_LIST_CLASS
parameter_list|(
name|klass
parameter_list|)
value|(G_TYPE_CHECK_CLASS_CAST ((klass), GIMP_TYPE_LIST, GimpListClass))
end_define

begin_define
DECL|macro|GIMP_IS_LIST (obj)
define|#
directive|define
name|GIMP_IS_LIST
parameter_list|(
name|obj
parameter_list|)
value|(G_TYPE_CHECK_INSTANCE_TYPE ((obj), GIMP_TYPE_LIST))
end_define

begin_define
DECL|macro|GIMP_IS_LIST_CLASS (klass)
define|#
directive|define
name|GIMP_IS_LIST_CLASS
parameter_list|(
name|klass
parameter_list|)
value|(G_TYPE_CHECK_CLASS_TYPE ((klass), GIMP_TYPE_LIST))
end_define

begin_define
DECL|macro|GIMP_LIST_GET_CLASS (obj)
define|#
directive|define
name|GIMP_LIST_GET_CLASS
parameter_list|(
name|obj
parameter_list|)
value|(G_TYPE_INSTANCE_GET_CLASS ((obj), GIMP_TYPE_LIST, GimpListClass))
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
DECL|member|unique_names
name|gboolean
name|unique_names
decl_stmt|;
DECL|member|sort_func
name|GCompareFunc
name|sort_func
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

begin_decl_stmt
name|GType
name|gimp_list_get_type
argument_list|(
name|void
argument_list|)
name|G_GNUC_CONST
decl_stmt|;
end_decl_stmt

begin_function_decl
name|GimpContainer
modifier|*
name|gimp_list_new
parameter_list|(
name|GType
name|children_type
parameter_list|,
name|gboolean
name|unique_names
parameter_list|)
function_decl|;
end_function_decl

begin_function_decl
name|GimpContainer
modifier|*
name|gimp_list_new_weak
parameter_list|(
name|GType
name|children_type
parameter_list|,
name|gboolean
name|unique_names
parameter_list|)
function_decl|;
end_function_decl

begin_function_decl
name|void
name|gimp_list_reverse
parameter_list|(
name|GimpList
modifier|*
name|list
parameter_list|)
function_decl|;
end_function_decl

begin_function_decl
name|void
name|gimp_list_set_sort_func
parameter_list|(
name|GimpList
modifier|*
name|list
parameter_list|,
name|GCompareFunc
name|sort_func
parameter_list|)
function_decl|;
end_function_decl

begin_function_decl
name|void
name|gimp_list_sort
parameter_list|(
name|GimpList
modifier|*
name|list
parameter_list|,
name|GCompareFunc
name|sort_func
parameter_list|)
function_decl|;
end_function_decl

begin_function_decl
name|void
name|gimp_list_sort_by_name
parameter_list|(
name|GimpList
modifier|*
name|list
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

