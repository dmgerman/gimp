begin_unit|revision:0.9.5;language:C;cregit-version:0.0.1
begin_comment
comment|/* GIMP - The GNU Image Manipulation Program  *  * gimpseamlessclonetool.h  * Copyright (C) 2011 Barak Itkin<lightningismyname@gmail.com>  *  * This program is free software: you can redistribute it and/or modify  * it under the terms of the GNU General Public License as published by  * the Free Software Foundation; either version 3 of the License, or  * (at your option) any later version.  *  * This program is distributed in the hope that it will be useful,  * but WITHOUT ANY WARRANTY; without even the implied warranty of  * MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the  * GNU General Public License for more details.  *  * You should have received a copy of the GNU General Public License  * along with this program.  If not, see<http://www.gnu.org/licenses/>.  */
end_comment

begin_ifndef
ifndef|#
directive|ifndef
name|__GIMP_SEAMLESS_CLONE_TOOL_H__
end_ifndef

begin_define
DECL|macro|__GIMP_SEAMLESS_CLONE_TOOL_H__
define|#
directive|define
name|__GIMP_SEAMLESS_CLONE_TOOL_H__
end_define

begin_include
include|#
directive|include
file|"gimpdrawtool.h"
end_include

begin_define
DECL|macro|GIMP_TYPE_SEAMLESS_CLONE_TOOL
define|#
directive|define
name|GIMP_TYPE_SEAMLESS_CLONE_TOOL
value|(gimp_seamless_clone_tool_get_type ())
end_define

begin_define
DECL|macro|GIMP_SEAMLESS_CLONE_TOOL (obj)
define|#
directive|define
name|GIMP_SEAMLESS_CLONE_TOOL
parameter_list|(
name|obj
parameter_list|)
value|(G_TYPE_CHECK_INSTANCE_CAST ((obj), GIMP_TYPE_SEAMLESS_CLONE_TOOL, GimpSeamlessCloneTool))
end_define

begin_define
DECL|macro|GIMP_SEAMLESS_CLONE_TOOL_CLASS (klass)
define|#
directive|define
name|GIMP_SEAMLESS_CLONE_TOOL_CLASS
parameter_list|(
name|klass
parameter_list|)
value|(G_TYPE_CHECK_CLASS_CAST ((klass), GIMP_TYPE_SEAMLESS_CLONE_TOOL, GimpSeamlessCloneToolClass))
end_define

begin_define
DECL|macro|GIMP_IS_SEAMLESS_CLONE_TOOL (obj)
define|#
directive|define
name|GIMP_IS_SEAMLESS_CLONE_TOOL
parameter_list|(
name|obj
parameter_list|)
value|(G_TYPE_CHECK_INSTANCE_TYPE ((obj), GIMP_TYPE_SEAMLESS_CLONE_TOOL))
end_define

begin_define
DECL|macro|GIMP_IS_SEAMLESS_CLONE_TOOL_CLASS (klass)
define|#
directive|define
name|GIMP_IS_SEAMLESS_CLONE_TOOL_CLASS
parameter_list|(
name|klass
parameter_list|)
value|(G_TYPE_CHECK_CLASS_TYPE ((klass), GIMP_TYPE_SEAMLESS_CLONE_TOOL))
end_define

begin_define
DECL|macro|GIMP_SEAMLESS_CLONE_TOOL_GET_CLASS (obj)
define|#
directive|define
name|GIMP_SEAMLESS_CLONE_TOOL_GET_CLASS
parameter_list|(
name|obj
parameter_list|)
value|(G_TYPE_INSTANCE_GET_CLASS ((obj), GIMP_TYPE_SEAMLESS_CLONE_TOOL, GimpSeamlessCloneToolClass))
end_define

begin_define
DECL|macro|GIMP_SEAMLESS_CLONE_TOOL_GET_OPTIONS (t)
define|#
directive|define
name|GIMP_SEAMLESS_CLONE_TOOL_GET_OPTIONS
parameter_list|(
name|t
parameter_list|)
value|(GIMP_SEAMLESS_CLONE_OPTIONS (gimp_tool_get_options (GIMP_TOOL (t))))
end_define

begin_typedef
DECL|typedef|GimpSeamlessCloneTool
typedef|typedef
name|struct
name|_GimpSeamlessCloneTool
name|GimpSeamlessCloneTool
typedef|;
end_typedef

begin_typedef
DECL|typedef|GimpSeamlessCloneToolClass
typedef|typedef
name|struct
name|_GimpSeamlessCloneToolClass
name|GimpSeamlessCloneToolClass
typedef|;
end_typedef

begin_struct
DECL|struct|_GimpSeamlessCloneTool
struct|struct
name|_GimpSeamlessCloneTool
block|{
DECL|member|parent_instance
name|GimpDrawTool
name|parent_instance
decl_stmt|;
DECL|member|paste
name|GeglBuffer
modifier|*
name|paste
decl_stmt|;
comment|/* A buffer containing the original                                   * paste that will be used in the                                   * rendering process */
DECL|member|tricache
name|GeglBuffer
modifier|*
name|tricache
decl_stmt|;
comment|/* Gegl buffer where each pixel contains                                   * information to associate it with a                                   * triangle of the mesh */
DECL|member|mesh_cache
name|gpointer
name|mesh_cache
decl_stmt|;
comment|/* The interpolation mesh, and sampling                                   * lists - an abstract data structure                                   * returned by the preprocessing GEGL                                   * operation */
DECL|member|render_node
name|GeglNode
modifier|*
name|render_node
decl_stmt|;
comment|/* The parent of the Gegl graph that                                    * renders the seamless cloning */
DECL|member|translate_node
name|GeglNode
modifier|*
name|translate_node
decl_stmt|;
comment|/* A Gegl node to translate the paste                                    * when the user moves it */
DECL|member|tool_state
name|gint
name|tool_state
decl_stmt|;
comment|/* The current state in the tool's                                    * state machine */
DECL|member|image_map
name|GimpImageMap
modifier|*
name|image_map
decl_stmt|;
comment|/* The image map object which renders                                    * the live preview, and commits it                                    * when at the end */
block|}
struct|;
end_struct

begin_struct
DECL|struct|_GimpSeamlessCloneToolClass
struct|struct
name|_GimpSeamlessCloneToolClass
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
name|gimp_seamless_clone_tool_register
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
name|gimp_seamless_clone_tool_get_type
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
comment|/*  __GIMP_SEAMLESS_CLONE_TOOL_H__  */
end_comment

end_unit

