begin_unit|revision:0.9.5;language:C;cregit-version:0.0.1
begin_comment
comment|/* The GIMP -- an image manipulation program  * Copyright (C) 1995 Spencer Kimball and Peter Mattis  *  * This program is free software; you can redistribute it and/or modify  * it under the terms of the GNU General Public License as published by  * the Free Software Foundation; either version 2 of the License, or  * (at your option) any later version.  *  * This program is distributed in the hope that it will be useful,  * but WITHOUT ANY WARRANTY; without even the implied warranty of  * MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the  * GNU General Public License for more details.  *  * You should have received a copy of the GNU General Public License  * along with this program; if not, write to the Free Software  * Foundation, Inc., 59 Temple Place - Suite 330, Boston, MA 02111-1307, USA.  */
end_comment

begin_ifndef
ifndef|#
directive|ifndef
name|__GIMPLISTP_H__
end_ifndef

begin_define
DECL|macro|__GIMPLISTP_H__
define|#
directive|define
name|__GIMPLISTP_H__
end_define

begin_include
include|#
directive|include
file|"gimpobjectP.h"
end_include

begin_include
include|#
directive|include
file|"gimplist.h"
end_include

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

begin_endif
endif|#
directive|endif
end_endif

end_unit

