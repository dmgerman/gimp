begin_unit|revision:0.9.5;language:C;cregit-version:0.0.1
begin_comment
comment|/* GIMP - The GNU Image Manipulation Program  * Copyright (C) 1995 Spencer Kimball and Peter Mattis  *  * gimptoolpath.h  * Copyright (C) 2017 Michael Natterer<mitch@gimp.org>  *  * This program is free software: you can redistribute it and/or modify  * it under the terms of the GNU General Public License as published by  * the Free Software Foundation; either version 3 of the License, or  * (at your option) any later version.  *  * This program is distributed in the hope that it will be useful,  * but WITHOUT ANY WARRANTY; without even the implied warranty of  * MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the  * GNU General Public License for more details.  *  * You should have received a copy of the GNU General Public License  * along with this program.  If not, see<https://www.gnu.org/licenses/>.  */
end_comment

begin_ifndef
ifndef|#
directive|ifndef
name|__GIMP_TOOL_PATH_H__
end_ifndef

begin_define
DECL|macro|__GIMP_TOOL_PATH_H__
define|#
directive|define
name|__GIMP_TOOL_PATH_H__
end_define

begin_include
include|#
directive|include
file|"gimptoolwidget.h"
end_include

begin_define
DECL|macro|GIMP_TYPE_TOOL_PATH
define|#
directive|define
name|GIMP_TYPE_TOOL_PATH
value|(gimp_tool_path_get_type ())
end_define

begin_define
DECL|macro|GIMP_TOOL_PATH (obj)
define|#
directive|define
name|GIMP_TOOL_PATH
parameter_list|(
name|obj
parameter_list|)
value|(G_TYPE_CHECK_INSTANCE_CAST ((obj), GIMP_TYPE_TOOL_PATH, GimpToolPath))
end_define

begin_define
DECL|macro|GIMP_TOOL_PATH_CLASS (klass)
define|#
directive|define
name|GIMP_TOOL_PATH_CLASS
parameter_list|(
name|klass
parameter_list|)
value|(G_TYPE_CHECK_CLASS_CAST ((klass), GIMP_TYPE_TOOL_PATH, GimpToolPathClass))
end_define

begin_define
DECL|macro|GIMP_IS_TOOL_PATH (obj)
define|#
directive|define
name|GIMP_IS_TOOL_PATH
parameter_list|(
name|obj
parameter_list|)
value|(G_TYPE_CHECK_INSTANCE_TYPE ((obj), GIMP_TYPE_TOOL_PATH))
end_define

begin_define
DECL|macro|GIMP_IS_TOOL_PATH_CLASS (klass)
define|#
directive|define
name|GIMP_IS_TOOL_PATH_CLASS
parameter_list|(
name|klass
parameter_list|)
value|(G_TYPE_CHECK_CLASS_TYPE ((klass), GIMP_TYPE_TOOL_PATH))
end_define

begin_define
DECL|macro|GIMP_TOOL_PATH_GET_CLASS (obj)
define|#
directive|define
name|GIMP_TOOL_PATH_GET_CLASS
parameter_list|(
name|obj
parameter_list|)
value|(G_TYPE_INSTANCE_GET_CLASS ((obj), GIMP_TYPE_TOOL_PATH, GimpToolPathClass))
end_define

begin_typedef
DECL|typedef|GimpToolPath
typedef|typedef
name|struct
name|_GimpToolPath
name|GimpToolPath
typedef|;
end_typedef

begin_typedef
DECL|typedef|GimpToolPathPrivate
typedef|typedef
name|struct
name|_GimpToolPathPrivate
name|GimpToolPathPrivate
typedef|;
end_typedef

begin_typedef
DECL|typedef|GimpToolPathClass
typedef|typedef
name|struct
name|_GimpToolPathClass
name|GimpToolPathClass
typedef|;
end_typedef

begin_struct
DECL|struct|_GimpToolPath
struct|struct
name|_GimpToolPath
block|{
DECL|member|parent_instance
name|GimpToolWidget
name|parent_instance
decl_stmt|;
DECL|member|private
name|GimpToolPathPrivate
modifier|*
name|private
decl_stmt|;
block|}
struct|;
end_struct

begin_struct
DECL|struct|_GimpToolPathClass
struct|struct
name|_GimpToolPathClass
block|{
DECL|member|parent_class
name|GimpToolWidgetClass
name|parent_class
decl_stmt|;
DECL|member|begin_change
name|void
function_decl|(
modifier|*
name|begin_change
function_decl|)
parameter_list|(
name|GimpToolPath
modifier|*
name|path
parameter_list|,
specifier|const
name|gchar
modifier|*
name|desc
parameter_list|)
function_decl|;
DECL|member|end_change
name|void
function_decl|(
modifier|*
name|end_change
function_decl|)
parameter_list|(
name|GimpToolPath
modifier|*
name|path
parameter_list|,
name|gboolean
name|success
parameter_list|)
function_decl|;
DECL|member|activate
name|void
function_decl|(
modifier|*
name|activate
function_decl|)
parameter_list|(
name|GimpToolPath
modifier|*
name|path
parameter_list|,
name|GdkModifierType
name|state
parameter_list|)
function_decl|;
block|}
struct|;
end_struct

begin_decl_stmt
name|GType
name|gimp_tool_path_get_type
argument_list|(
name|void
argument_list|)
name|G_GNUC_CONST
decl_stmt|;
end_decl_stmt

begin_function_decl
name|GimpToolWidget
modifier|*
name|gimp_tool_path_new
parameter_list|(
name|GimpDisplayShell
modifier|*
name|shell
parameter_list|)
function_decl|;
end_function_decl

begin_function_decl
name|void
name|gimp_tool_path_set_vectors
parameter_list|(
name|GimpToolPath
modifier|*
name|path
parameter_list|,
name|GimpVectors
modifier|*
name|vectors
parameter_list|)
function_decl|;
end_function_decl

begin_endif
endif|#
directive|endif
end_endif

begin_comment
comment|/* __GIMP_TOOL_PATH_H__ */
end_comment

end_unit

