begin_unit|revision:0.9.5;language:C;cregit-version:0.0.1
begin_comment
comment|/* The GIMP -- an image manipulation program  * Copyright (C) 1995 Spencer Kimball and Peter Mattis  *  * This program is free software; you can redistribute it and/or modify  * it under the terms of the GNU General Public License as published by  * the Free Software Foundation; either version 2 of the License, or  * (at your option) any later version.  *  * This program is distributed in the hope that it will be useful,  * but WITHOUT ANY WARRANTY; without even the implied warranty of  * MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the  * GNU General Public License for more details.  *  * You should have received a copy of the GNU General Public License  * along with this program; if not, write to the Free Software  * Foundation, Inc., 59 Temple Place - Suite 330, Boston, MA 02111-1307, USA.  */
end_comment

begin_ifndef
ifndef|#
directive|ifndef
name|__GIMP_SET_P_H__
end_ifndef

begin_define
DECL|macro|__GIMP_SET_P_H__
define|#
directive|define
name|__GIMP_SET_P_H__
end_define

begin_include
include|#
directive|include
file|"gimpobjectP.h"
end_include

begin_include
include|#
directive|include
file|"gimpset.h"
end_include

begin_define
DECL|macro|GIMP_SET_CLASS (klass)
define|#
directive|define
name|GIMP_SET_CLASS
parameter_list|(
name|klass
parameter_list|)
value|GTK_CHECK_CLASS_CAST (klass, gimp_set_get_type(), GimpSetClass)
end_define

begin_typedef
DECL|typedef|GimpSetClass
typedef|typedef
name|struct
name|_GimpSetClass
name|GimpSetClass
typedef|;
end_typedef

begin_struct
DECL|struct|_GimpSet
struct|struct
name|_GimpSet
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
DECL|member|handlers
name|GArray
modifier|*
name|handlers
decl_stmt|;
DECL|member|weak
name|gboolean
name|weak
decl_stmt|;
DECL|member|active_element
name|gpointer
name|active_element
decl_stmt|;
block|}
struct|;
end_struct

begin_struct
DECL|struct|_GimpSetClass
struct|struct
name|_GimpSetClass
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
name|GimpSet
modifier|*
name|gimpset
parameter_list|,
name|gpointer
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
name|GimpSet
modifier|*
name|gimpset
parameter_list|,
name|gpointer
name|object
parameter_list|)
function_decl|;
DECL|member|active_changed
name|void
function_decl|(
modifier|*
name|active_changed
function_decl|)
parameter_list|(
name|GimpSet
modifier|*
name|gimpset
parameter_list|,
name|gpointer
name|object
parameter_list|)
function_decl|;
block|}
struct|;
end_struct

begin_endif
endif|#
directive|endif
end_endif

begin_comment
comment|/* __GIMP_SET_P_H__ */
end_comment

end_unit

