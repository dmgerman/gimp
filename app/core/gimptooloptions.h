begin_unit|revision:0.9.5;language:C;cregit-version:0.0.1
begin_comment
comment|/* GIMP - The GNU Image Manipulation Program  * Copyright (C) 1995-1999 Spencer Kimball and Peter Mattis  *  * This program is free software; you can redistribute it and/or modify  * it under the terms of the GNU General Public License as published by  * the Free Software Foundation; either version 2 of the License, or  * (at your option) any later version.  *  * This program is distributed in the hope that it will be useful,  * but WITHOUT ANY WARRANTY; without even the implied warranty of  * MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the  * GNU General Public License for more details.  *  * You should have received a copy of the GNU General Public License  * along with this program; if not, write to the Free Software  * Foundation, Inc., 59 Temple Place - Suite 330, Boston, MA 02111-1307, USA.  */
end_comment

begin_ifndef
ifndef|#
directive|ifndef
name|__GIMP_TOOL_OPTIONS_H__
end_ifndef

begin_define
DECL|macro|__GIMP_TOOL_OPTIONS_H__
define|#
directive|define
name|__GIMP_TOOL_OPTIONS_H__
end_define

begin_include
include|#
directive|include
file|"gimpcontext.h"
end_include

begin_define
DECL|macro|GIMP_TYPE_TOOL_OPTIONS
define|#
directive|define
name|GIMP_TYPE_TOOL_OPTIONS
value|(gimp_tool_options_get_type ())
end_define

begin_define
DECL|macro|GIMP_TOOL_OPTIONS (obj)
define|#
directive|define
name|GIMP_TOOL_OPTIONS
parameter_list|(
name|obj
parameter_list|)
value|(G_TYPE_CHECK_INSTANCE_CAST ((obj), GIMP_TYPE_TOOL_OPTIONS, GimpToolOptions))
end_define

begin_define
DECL|macro|GIMP_TOOL_OPTIONS_CLASS (klass)
define|#
directive|define
name|GIMP_TOOL_OPTIONS_CLASS
parameter_list|(
name|klass
parameter_list|)
value|(G_TYPE_CHECK_CLASS_CAST ((klass), GIMP_TYPE_TOOL_OPTIONS, GimpToolOptionsClass))
end_define

begin_define
DECL|macro|GIMP_IS_TOOL_OPTIONS (obj)
define|#
directive|define
name|GIMP_IS_TOOL_OPTIONS
parameter_list|(
name|obj
parameter_list|)
value|(G_TYPE_CHECK_INSTANCE_TYPE ((obj), GIMP_TYPE_TOOL_OPTIONS))
end_define

begin_define
DECL|macro|GIMP_IS_TOOL_OPTIONS_CLASS (klass)
define|#
directive|define
name|GIMP_IS_TOOL_OPTIONS_CLASS
parameter_list|(
name|klass
parameter_list|)
value|(G_TYPE_CHECK_CLASS_TYPE ((klass), GIMP_TYPE_TOOL_OPTIONS))
end_define

begin_define
DECL|macro|GIMP_TOOL_OPTIONS_GET_CLASS (obj)
define|#
directive|define
name|GIMP_TOOL_OPTIONS_GET_CLASS
parameter_list|(
name|obj
parameter_list|)
value|(G_TYPE_INSTANCE_GET_CLASS ((obj), GIMP_TYPE_TOOL_OPTIONS, GimpToolOptionsClass))
end_define

begin_typedef
DECL|typedef|GimpToolOptionsClass
typedef|typedef
name|struct
name|_GimpToolOptionsClass
name|GimpToolOptionsClass
typedef|;
end_typedef

begin_struct
DECL|struct|_GimpToolOptions
struct|struct
name|_GimpToolOptions
block|{
DECL|member|parent_instance
name|GimpContext
name|parent_instance
decl_stmt|;
DECL|member|tool_info
name|GimpToolInfo
modifier|*
name|tool_info
decl_stmt|;
block|}
struct|;
end_struct

begin_struct
DECL|struct|_GimpToolOptionsClass
struct|struct
name|_GimpToolOptionsClass
block|{
DECL|member|parent_class
name|GimpContextClass
name|parent_class
decl_stmt|;
DECL|member|reset
name|void
function_decl|(
modifier|*
name|reset
function_decl|)
parameter_list|(
name|GimpToolOptions
modifier|*
name|tool_options
parameter_list|)
function_decl|;
block|}
struct|;
end_struct

begin_decl_stmt
name|GType
name|gimp_tool_options_get_type
argument_list|(
name|void
argument_list|)
name|G_GNUC_CONST
decl_stmt|;
end_decl_stmt

begin_function_decl
name|void
name|gimp_tool_options_reset
parameter_list|(
name|GimpToolOptions
modifier|*
name|tool_options
parameter_list|)
function_decl|;
end_function_decl

begin_function_decl
name|gboolean
name|gimp_tool_options_serialize
parameter_list|(
name|GimpToolOptions
modifier|*
name|tool_options
parameter_list|,
name|GError
modifier|*
modifier|*
name|error
parameter_list|)
function_decl|;
end_function_decl

begin_function_decl
name|gboolean
name|gimp_tool_options_deserialize
parameter_list|(
name|GimpToolOptions
modifier|*
name|tool_options
parameter_list|,
name|GError
modifier|*
modifier|*
name|error
parameter_list|)
function_decl|;
end_function_decl

begin_function_decl
name|gboolean
name|gimp_tool_options_delete
parameter_list|(
name|GimpToolOptions
modifier|*
name|tool_options
parameter_list|,
name|GError
modifier|*
modifier|*
name|error
parameter_list|)
function_decl|;
end_function_decl

begin_function_decl
name|void
name|gimp_tool_options_create_folder
parameter_list|(
name|void
parameter_list|)
function_decl|;
end_function_decl

begin_endif
endif|#
directive|endif
end_endif

begin_comment
comment|/*  __GIMP_TOOL_OPTIONS_H__  */
end_comment

end_unit

