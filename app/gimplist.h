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
file|"gimpobject.h"
end_include

begin_comment
comment|/* GimpList - a typed list of objects with signals for adding and  * removing of stuff. If it is weak, destroyed objects get removed  * automatically. If it is not, it refs them so they won't be freed  * till they are removed. (Though they can be destroyed, of course)  */
end_comment

begin_define
DECL|macro|GIMP_TYPE_LIST
define|#
directive|define
name|GIMP_TYPE_LIST
value|gimp_list_get_type ()
end_define

begin_define
DECL|macro|GIMP_LIST (obj)
define|#
directive|define
name|GIMP_LIST
parameter_list|(
name|obj
parameter_list|)
value|GTK_CHECK_CAST (obj, GIMP_TYPE_LIST, GimpList)
end_define

begin_define
DECL|macro|GIMP_IS_LIST (obj)
define|#
directive|define
name|GIMP_IS_LIST
parameter_list|(
name|obj
parameter_list|)
value|GTK_CHECK_TYPE (obj, gimp_list_get_type())
end_define

begin_define
DECL|macro|GIMP_LIST_CLASS (klass)
define|#
directive|define
name|GIMP_LIST_CLASS
parameter_list|(
name|klass
parameter_list|)
value|GTK_CHECK_CLASS_CAST (klass, gimp_list_get_type(), GimpListClass)
end_define

begin_struct
DECL|struct|_GimpList
struct|struct
name|_GimpList
block|{
DECL|member|gobject
name|GimpObject
name|gobject
decl_stmt|;
DECL|member|type
name|GtkType
name|type
decl_stmt|;
DECL|member|list
name|GSList
modifier|*
name|list
decl_stmt|;
DECL|member|weak
name|gboolean
name|weak
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
name|GimpList
modifier|*
name|list
parameter_list|,
name|void
modifier|*
name|data
parameter_list|)
function_decl|;
DECL|member|remove
name|void
function_decl|(
modifier|*
name|remove
function_decl|)
parameter_list|(
name|GimpList
modifier|*
name|list
parameter_list|,
name|void
modifier|*
name|data
parameter_list|)
function_decl|;
block|}
struct|;
end_struct

begin_typedef
DECL|typedef|GimpListClass
typedef|typedef
name|struct
name|_GimpListClass
name|GimpListClass
typedef|;
end_typedef

begin_comment
comment|/* Signals:    add    remove */
end_comment

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
name|type
parameter_list|,
name|gboolean
name|weak
parameter_list|)
function_decl|;
end_function_decl

begin_function_decl
name|GtkType
name|gimp_list_type
parameter_list|(
name|GimpList
modifier|*
name|list
parameter_list|)
function_decl|;
end_function_decl

begin_function_decl
name|gboolean
name|gimp_list_add
parameter_list|(
name|GimpList
modifier|*
name|list
parameter_list|,
name|gpointer
name|object
parameter_list|)
function_decl|;
end_function_decl

begin_function_decl
name|gboolean
name|gimp_list_remove
parameter_list|(
name|GimpList
modifier|*
name|list
parameter_list|,
name|gpointer
name|object
parameter_list|)
function_decl|;
end_function_decl

begin_function_decl
name|gboolean
name|gimp_list_have
parameter_list|(
name|GimpList
modifier|*
name|list
parameter_list|,
name|gpointer
name|object
parameter_list|)
function_decl|;
end_function_decl

begin_function_decl
name|void
name|gimp_list_foreach
parameter_list|(
name|GimpList
modifier|*
name|list
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
name|gint
name|gimp_list_size
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

