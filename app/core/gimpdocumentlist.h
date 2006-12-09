begin_unit|revision:0.9.5;language:C;cregit-version:0.0.1
begin_comment
comment|/* GIMP - The GNU Image Manipulation Program  * Copyright (C) 1995-1997 Spencer Kimball and Peter Mattis  *  * This program is free software; you can redistribute it and/or modify  * it under the terms of the GNU General Public License as published by  * the Free Software Foundation; either version 2 of the License, or  * (at your option) any later version.  *  * This program is distributed in the hope that it will be useful,  * but WITHOUT ANY WARRANTY; without even the implied warranty of  * MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the  * GNU General Public License for more details.  *  * You should have received a copy of the GNU General Public License  * along with this program; if not, write to the Free Software  * Foundation, Inc., 59 Temple Place - Suite 330, Boston, MA 02111-1307, USA.  */
end_comment

begin_ifndef
ifndef|#
directive|ifndef
name|__GIMP_DOCUMENT_LIST_H__
end_ifndef

begin_define
DECL|macro|__GIMP_DOCUMENT_LIST_H__
define|#
directive|define
name|__GIMP_DOCUMENT_LIST_H__
end_define

begin_include
include|#
directive|include
file|"core/gimplist.h"
end_include

begin_define
DECL|macro|GIMP_TYPE_DOCUMENT_LIST
define|#
directive|define
name|GIMP_TYPE_DOCUMENT_LIST
value|(gimp_document_list_get_type ())
end_define

begin_define
DECL|macro|GIMP_DOCUMENT_LIST (obj)
define|#
directive|define
name|GIMP_DOCUMENT_LIST
parameter_list|(
name|obj
parameter_list|)
value|(G_TYPE_CHECK_INSTANCE_CAST ((obj), GIMP_TYPE_DOCUMENT_LIST, GimpDocumentList))
end_define

begin_define
DECL|macro|GIMP_DOCUMENT_LIST_CLASS (klass)
define|#
directive|define
name|GIMP_DOCUMENT_LIST_CLASS
parameter_list|(
name|klass
parameter_list|)
value|(G_TYPE_CHECK_CLASS_CAST ((klass), GIMP_TYPE_DOCUMENT_LIST, GimpDocumentListClass))
end_define

begin_define
DECL|macro|GIMP_IS_DOCUMENT_LIST (obj)
define|#
directive|define
name|GIMP_IS_DOCUMENT_LIST
parameter_list|(
name|obj
parameter_list|)
value|(G_TYPE_CHECK_INSTANCE_TYPE ((obj), GIMP_TYPE_DOCUMENT_LIST))
end_define

begin_define
DECL|macro|GIMP_IS_DOCUMENT_LIST_CLASS (klass)
define|#
directive|define
name|GIMP_IS_DOCUMENT_LIST_CLASS
parameter_list|(
name|klass
parameter_list|)
value|(G_TYPE_CHECK_CLASS_TYPE ((klass), GIMP_TYPE_DOCUMENT_LIST))
end_define

begin_typedef
DECL|typedef|GimpDocumentListClass
typedef|typedef
name|struct
name|_GimpDocumentListClass
name|GimpDocumentListClass
typedef|;
end_typedef

begin_struct
DECL|struct|_GimpDocumentList
struct|struct
name|_GimpDocumentList
block|{
DECL|member|parent_instance
name|GimpList
name|parent_instance
decl_stmt|;
DECL|member|gimp
name|Gimp
modifier|*
name|gimp
decl_stmt|;
block|}
struct|;
end_struct

begin_struct
DECL|struct|_GimpDocumentListClass
struct|struct
name|_GimpDocumentListClass
block|{
DECL|member|parent_class
name|GimpListClass
name|parent_class
decl_stmt|;
block|}
struct|;
end_struct

begin_decl_stmt
name|GType
name|gimp_document_list_get_type
argument_list|(
name|void
argument_list|)
name|G_GNUC_CONST
decl_stmt|;
end_decl_stmt

begin_function_decl
name|GimpContainer
modifier|*
name|gimp_document_list_new
parameter_list|(
name|Gimp
modifier|*
name|gimp
parameter_list|)
function_decl|;
end_function_decl

begin_function_decl
name|GimpImagefile
modifier|*
name|gimp_document_list_add_uri
parameter_list|(
name|GimpDocumentList
modifier|*
name|document_list
parameter_list|,
specifier|const
name|gchar
modifier|*
name|uri
parameter_list|,
specifier|const
name|gchar
modifier|*
name|mime_type
parameter_list|)
function_decl|;
end_function_decl

begin_endif
endif|#
directive|endif
end_endif

begin_comment
comment|/*  __GIMP_DOCUMENT_LIST_H__  */
end_comment

end_unit

