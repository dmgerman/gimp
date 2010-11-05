begin_unit|revision:0.9.5;language:C;cregit-version:0.0.1
begin_comment
comment|/* GIMP - The GNU Image Manipulation Program  *  * gimpcagetool.h  * Copyright (C) 2010 Michael MurÃ©<batolettre@gmail.com>  *  * This program is free software: you can redistribute it and/or modify  * it under the terms of the GNU General Public License as published by  * the Free Software Foundation; either version 3 of the License, or  * (at your option) any later version.  *  * This program is distributed in the hope that it will be useful,  * but WITHOUT ANY WARRANTY; without even the implied warranty of  * MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the  * GNU General Public License for more details.  *  * You should have received a copy of the GNU General Public License  * along with this program.  If not, see<http://www.gnu.org/licenses/>.  */
end_comment

begin_ifndef
ifndef|#
directive|ifndef
name|__GIMP_CAGE_TOOL_H__
end_ifndef

begin_define
DECL|macro|__GIMP_CAGE_TOOL_H__
define|#
directive|define
name|__GIMP_CAGE_TOOL_H__
end_define

begin_include
include|#
directive|include
file|"gimpdrawtool.h"
end_include

begin_include
include|#
directive|include
file|"libgimpmath/gimpvector.h"
end_include

begin_define
DECL|macro|GIMP_TYPE_CAGE_TOOL
define|#
directive|define
name|GIMP_TYPE_CAGE_TOOL
value|(gimp_cage_tool_get_type ())
end_define

begin_define
DECL|macro|GIMP_CAGE_TOOL (obj)
define|#
directive|define
name|GIMP_CAGE_TOOL
parameter_list|(
name|obj
parameter_list|)
value|(G_TYPE_CHECK_INSTANCE_CAST ((obj), GIMP_TYPE_CAGE_TOOL, GimpCageTool))
end_define

begin_define
DECL|macro|GIMP_CAGE_TOOL_CLASS (klass)
define|#
directive|define
name|GIMP_CAGE_TOOL_CLASS
parameter_list|(
name|klass
parameter_list|)
value|(G_TYPE_CHECK_CLASS_CAST ((klass), GIMP_TYPE_CAGE_TOOL, GimpCageToolClass))
end_define

begin_define
DECL|macro|GIMP_IS_CAGE_TOOL (obj)
define|#
directive|define
name|GIMP_IS_CAGE_TOOL
parameter_list|(
name|obj
parameter_list|)
value|(G_TYPE_CHECK_INSTANCE_TYPE ((obj), GIMP_TYPE_CAGE_TOOL))
end_define

begin_define
DECL|macro|GIMP_IS_CAGE_TOOL_CLASS (klass)
define|#
directive|define
name|GIMP_IS_CAGE_TOOL_CLASS
parameter_list|(
name|klass
parameter_list|)
value|(G_TYPE_CHECK_CLASS_TYPE ((klass), GIMP_TYPE_CAGE_TOOL))
end_define

begin_define
DECL|macro|GIMP_CAGE_TOOL_GET_CLASS (obj)
define|#
directive|define
name|GIMP_CAGE_TOOL_GET_CLASS
parameter_list|(
name|obj
parameter_list|)
value|(G_TYPE_INSTANCE_GET_CLASS ((obj), GIMP_TYPE_CAGE_TOOL, GimpCageToolClass))
end_define

begin_define
DECL|macro|GIMP_CAGE_TOOL_GET_OPTIONS (t)
define|#
directive|define
name|GIMP_CAGE_TOOL_GET_OPTIONS
parameter_list|(
name|t
parameter_list|)
value|(GIMP_CAGE_OPTIONS (gimp_tool_get_options (GIMP_TOOL (t))))
end_define

begin_typedef
DECL|typedef|GimpCageTool
typedef|typedef
name|struct
name|_GimpCageTool
name|GimpCageTool
typedef|;
end_typedef

begin_typedef
DECL|typedef|GimpCageToolClass
typedef|typedef
name|struct
name|_GimpCageToolClass
name|GimpCageToolClass
typedef|;
end_typedef

begin_struct
DECL|struct|_GimpCageTool
struct|struct
name|_GimpCageTool
block|{
DECL|member|parent_instance
name|GimpDrawTool
name|parent_instance
decl_stmt|;
DECL|member|config
name|GimpCageConfig
modifier|*
name|config
decl_stmt|;
DECL|member|cursor_position
name|GimpVector2
name|cursor_position
decl_stmt|;
DECL|member|handle_moved
name|gint
name|handle_moved
decl_stmt|;
DECL|member|cage_complete
name|gboolean
name|cage_complete
decl_stmt|;
DECL|member|coef
name|GeglBuffer
modifier|*
name|coef
decl_stmt|;
DECL|member|image_map
name|GimpImageMap
modifier|*
name|image_map
decl_stmt|;
block|}
struct|;
end_struct

begin_struct
DECL|struct|_GimpCageToolClass
struct|struct
name|_GimpCageToolClass
block|{
DECL|member|parent_class
name|GimpDrawToolClass
name|parent_class
decl_stmt|;
block|}
struct|;
end_struct

begin_function_decl
name|void
name|gimp_cage_tool_register
parameter_list|(
name|GimpToolRegisterCallback
name|callback
parameter_list|,
name|gpointer
name|data
parameter_list|)
function_decl|;
end_function_decl

begin_decl_stmt
name|GType
name|gimp_cage_tool_get_type
argument_list|(
name|void
argument_list|)
name|G_GNUC_CONST
decl_stmt|;
end_decl_stmt

begin_endif
endif|#
directive|endif
end_endif

begin_comment
comment|/*  __GIMP_CAGE_TOOL_H__  */
end_comment

end_unit

