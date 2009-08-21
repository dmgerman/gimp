begin_unit|revision:0.9.5;language:C;cregit-version:0.0.1
begin_comment
comment|/* GIMP - The GNU Image Manipulation Program  * Copyright (C) 1995 Spencer Kimball and Peter Mattis  *  * GimpTreeHandler  * Copyright (C) 2009  Michael Natterer<mitch@gimp.org>  *  * This program is free software: you can redistribute it and/or modify  * it under the terms of the GNU General Public License as published by  * the Free Software Foundation; either version 3 of the License, or  * (at your option) any later version.  *  * This program is distributed in the hope that it will be useful,  * but WITHOUT ANY WARRANTY; without even the implied warranty of  * MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the  * GNU General Public License for more details.  *  * You should have received a copy of the GNU General Public License  * along with this program.  If not, see<http://www.gnu.org/licenses/>.  */
end_comment

begin_ifndef
ifndef|#
directive|ifndef
name|__GIMP_TREE_HANDLER_H__
end_ifndef

begin_define
DECL|macro|__GIMP_TREE_HANDLER_H__
define|#
directive|define
name|__GIMP_TREE_HANDLER_H__
end_define

begin_include
include|#
directive|include
file|"core/gimpobject.h"
end_include

begin_define
DECL|macro|GIMP_TYPE_TREE_HANDLER
define|#
directive|define
name|GIMP_TYPE_TREE_HANDLER
value|(gimp_tree_handler_get_type ())
end_define

begin_define
DECL|macro|GIMP_TREE_HANDLER (obj)
define|#
directive|define
name|GIMP_TREE_HANDLER
parameter_list|(
name|obj
parameter_list|)
value|(G_TYPE_CHECK_INSTANCE_CAST ((obj), GIMP_TYPE_TREE_HANDLER, GimpTreeHandler))
end_define

begin_define
DECL|macro|GIMP_TREE_HANDLER_CLASS (klass)
define|#
directive|define
name|GIMP_TREE_HANDLER_CLASS
parameter_list|(
name|klass
parameter_list|)
value|(G_TYPE_CHECK_CLASS_CAST ((klass), GIMP_TYPE_TREE_HANDLER, GimpTreeHandlerClass))
end_define

begin_define
DECL|macro|GIMP_IS_TREE_HANDLER (obj)
define|#
directive|define
name|GIMP_IS_TREE_HANDLER
parameter_list|(
name|obj
parameter_list|)
value|(G_TYPE_CHECK_INSTANCE_TYPE ((obj), GIMP_TYPE_TREE_HANDLER))
end_define

begin_define
DECL|macro|GIMP_IS_TREE_HANDLER_CLASS (klass)
define|#
directive|define
name|GIMP_IS_TREE_HANDLER_CLASS
parameter_list|(
name|klass
parameter_list|)
value|(G_TYPE_CHECK_CLASS_TYPE ((klass), GIMP_TYPE_TREE_HANDLER))
end_define

begin_define
DECL|macro|GIMP_TREE_HANDLER_GET_CLASS (obj)
define|#
directive|define
name|GIMP_TREE_HANDLER_GET_CLASS
parameter_list|(
name|obj
parameter_list|)
value|(G_TYPE_INSTANCE_GET_CLASS ((obj), GIMP_TYPE_TREE_HANDLER, GimpTreeHandlerClass))
end_define

begin_typedef
DECL|typedef|GimpTreeHandlerClass
typedef|typedef
name|struct
name|_GimpTreeHandlerClass
name|GimpTreeHandlerClass
typedef|;
end_typedef

begin_struct
DECL|struct|_GimpTreeHandler
struct|struct
name|_GimpTreeHandler
block|{
DECL|member|parent_instance
name|GimpObject
name|parent_instance
decl_stmt|;
DECL|member|container
name|GimpContainer
modifier|*
name|container
decl_stmt|;
DECL|member|signal_name
name|gchar
modifier|*
name|signal_name
decl_stmt|;
DECL|member|callback
name|GCallback
name|callback
decl_stmt|;
DECL|member|user_data
name|gpointer
name|user_data
decl_stmt|;
block|}
struct|;
end_struct

begin_struct
DECL|struct|_GimpTreeHandlerClass
struct|struct
name|_GimpTreeHandlerClass
block|{
DECL|member|parent_class
name|GimpObjectClass
name|parent_class
decl_stmt|;
block|}
struct|;
end_struct

begin_decl_stmt
name|GType
name|gimp_tree_handler_get_type
argument_list|(
name|void
argument_list|)
name|G_GNUC_CONST
decl_stmt|;
end_decl_stmt

begin_function_decl
name|GimpTreeHandler
modifier|*
name|gimp_tree_handler_connect
parameter_list|(
name|GimpContainer
modifier|*
name|container
parameter_list|,
specifier|const
name|gchar
modifier|*
name|signal_name
parameter_list|,
name|GCallback
name|callback
parameter_list|,
name|gpointer
name|user_data
parameter_list|)
function_decl|;
end_function_decl

begin_function_decl
name|void
name|gimp_tree_handler_disconnect
parameter_list|(
name|GimpTreeHandler
modifier|*
name|handler
parameter_list|)
function_decl|;
end_function_decl

begin_endif
endif|#
directive|endif
end_endif

begin_comment
comment|/* __GIMP_TREE_HANDLER_H__ */
end_comment

end_unit

