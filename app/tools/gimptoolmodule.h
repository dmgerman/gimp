begin_unit|revision:0.9.5;language:C;cregit-version:0.0.1
begin_comment
comment|/* The GIMP -- an image manipulation program  * Copyright (C) 1995-2002 Spencer Kimball, Peter Mattis and others  *  * This program is free software; you can redistribute it and/or modify  * it under the terms of the GNU General Public License as published by  * the Free Software Foundation; either version 2 of the License, or  * (at your option) any later version.  *  * This program is distributed in the hope that it will be useful,  * but WITHOUT ANY WARRANTY; without even the implied warranty of  * MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the  * GNU General Public License for more details.  *  * You should have received a copy of the GNU General Public License  * along with this program; if not, write to the Free Software  * Foundation, Inc., 59 Temple Place - Suite 330, Boston, MA 02111-1307, USA.  */
end_comment

begin_ifndef
ifndef|#
directive|ifndef
name|__GIMP_TOOL_MODULE_H__
end_ifndef

begin_define
DECL|macro|__GIMP_TOOL_MODULE_H__
define|#
directive|define
name|__GIMP_TOOL_MODULE_H__
end_define

begin_include
include|#
directive|include
file|<gmodule.h>
end_include

begin_include
include|#
directive|include
file|<glib-object.h>
end_include

begin_include
include|#
directive|include
file|<gtk/gtk.h>
end_include

begin_comment
comment|/* for tools-types.h.  This is truly sick */
end_comment

begin_include
include|#
directive|include
file|"config.h"
end_include

begin_include
include|#
directive|include
file|"tools-types.h"
end_include

begin_include
include|#
directive|include
file|"core/gimp.h"
end_include

begin_define
DECL|macro|GIMP_TYPE_TOOL_MODULE
define|#
directive|define
name|GIMP_TYPE_TOOL_MODULE
value|(gimp_tool_module_get_type ())
end_define

begin_define
DECL|macro|GIMP_TOOL_MODULE (obj)
define|#
directive|define
name|GIMP_TOOL_MODULE
parameter_list|(
name|obj
parameter_list|)
value|(G_TYPE_CHECK_INSTANCE_CAST ((obj), GIMP_TYPE_TOOL_MODULE, GimpToolModule))
end_define

begin_define
DECL|macro|GIMP_TOOL_MODULE_CLASS (klass)
define|#
directive|define
name|GIMP_TOOL_MODULE_CLASS
parameter_list|(
name|klass
parameter_list|)
value|(G_TYPE_CHECK_CLASS_CAST ((klass), GIMP_TYPE_TOOL_MODULE, GimpToolModuleClass))
end_define

begin_define
DECL|macro|GIMP_IS_TOOL_MODULE (obj)
define|#
directive|define
name|GIMP_IS_TOOL_MODULE
parameter_list|(
name|obj
parameter_list|)
value|(G_TYPE_CHECK_INSTANCE_TYPE ((obj), GIMP_TYPE_TOOL_MODULE))
end_define

begin_define
DECL|macro|GIMP_IS_TOOL_MODULE_CLASS (klass)
define|#
directive|define
name|GIMP_IS_TOOL_MODULE_CLASS
parameter_list|(
name|klass
parameter_list|)
value|(G_TYPE_CHECK_CLASS_TYPE ((klass), GIMP_TYPE_TOOL_MODULE))
end_define

begin_define
DECL|macro|GIMP_TOOL_MODULE_GET_CLASS (obj)
define|#
directive|define
name|GIMP_TOOL_MODULE_GET_CLASS
parameter_list|(
name|obj
parameter_list|)
value|(G_TYPE_INSTANCE_GET_CLASS ((obj), GIMP_TYPE_TOOL_MODULE, GimpToolModuleClass))
end_define

begin_typedef
DECL|typedef|GimpToolModuleClass
typedef|typedef
name|struct
name|_GimpToolModuleClass
name|GimpToolModuleClass
typedef|;
end_typedef

begin_typedef
DECL|typedef|GimpToolModule
typedef|typedef
name|struct
name|_GimpToolModule
name|GimpToolModule
typedef|;
end_typedef

begin_struct
DECL|struct|_GimpToolModule
struct|struct
name|_GimpToolModule
block|{
DECL|member|parent_instance
name|GTypeModule
name|parent_instance
decl_stmt|;
DECL|member|module
name|GModule
modifier|*
name|module
decl_stmt|;
DECL|member|filename
name|gchar
modifier|*
name|filename
decl_stmt|;
DECL|member|register_tool
name|void
function_decl|(
modifier|*
name|register_tool
function_decl|)
parameter_list|(
name|Gimp
modifier|*
name|gimp
parameter_list|,
name|GimpToolRegisterCallback
name|callback
parameter_list|)
function_decl|;
DECL|member|register_type
name|gboolean
function_decl|(
modifier|*
name|register_type
function_decl|)
parameter_list|(
name|GTypeModule
modifier|*
name|module
parameter_list|)
function_decl|;
block|}
struct|;
end_struct

begin_struct
DECL|struct|_GimpToolModuleClass
struct|struct
name|_GimpToolModuleClass
block|{
DECL|member|parent_class
name|GTypeModuleClass
name|parent_class
decl_stmt|;
block|}
struct|;
end_struct

begin_decl_stmt
name|GType
name|gimp_tool_module_get_type
argument_list|(
name|void
argument_list|)
name|G_GNUC_CONST
decl_stmt|;
end_decl_stmt

begin_function_decl
name|GimpToolModule
modifier|*
name|gimp_tool_module_new
parameter_list|(
name|gchar
modifier|*
name|filename
parameter_list|,
name|Gimp
modifier|*
name|gimp
parameter_list|,
name|GimpToolRegisterCallback
name|callback
parameter_list|)
function_decl|;
end_function_decl

begin_endif
endif|#
directive|endif
end_endif

begin_comment
comment|/*  __GIMP_TOOL_MODULE_H__  */
end_comment

end_unit

