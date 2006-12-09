begin_unit|revision:0.9.5;language:C;cregit-version:0.0.1
begin_comment
comment|/* GIMP - The GNU Image Manipulation Program  * Copyright (C) 1995 Spencer Kimball and Peter Mattis  *  * This program is free software; you can redistribute it and/or modify  * it under the terms of the GNU General Public License as published by  * the Free Software Foundation; either version 2 of the License, or  * (at your option) any later version.  *  * This program is distributed in the hope that it will be useful,  * but WITHOUT ANY WARRANTY; without even the implied warranty of  * MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the  * GNU General Public License for more details.  *  * You should have received a copy of the GNU General Public License  * along with this program; if not, write to the Free Software  * Foundation, Inc., 59 Temple Place - Suite 330, Boston, MA 02111-1307, USA.  */
end_comment

begin_ifndef
ifndef|#
directive|ifndef
name|__GIMP_MOVE_TOOL_H__
end_ifndef

begin_define
DECL|macro|__GIMP_MOVE_TOOL_H__
define|#
directive|define
name|__GIMP_MOVE_TOOL_H__
end_define

begin_include
include|#
directive|include
file|"gimpdrawtool.h"
end_include

begin_define
DECL|macro|GIMP_TYPE_MOVE_TOOL
define|#
directive|define
name|GIMP_TYPE_MOVE_TOOL
value|(gimp_move_tool_get_type ())
end_define

begin_define
DECL|macro|GIMP_MOVE_TOOL (obj)
define|#
directive|define
name|GIMP_MOVE_TOOL
parameter_list|(
name|obj
parameter_list|)
value|(G_TYPE_CHECK_INSTANCE_CAST ((obj), GIMP_TYPE_MOVE_TOOL, GimpMoveTool))
end_define

begin_define
DECL|macro|GIMP_MOVE_TOOL_CLASS (klass)
define|#
directive|define
name|GIMP_MOVE_TOOL_CLASS
parameter_list|(
name|klass
parameter_list|)
value|(G_TYPE_CHECK_CLASS_CAST ((klass), GIMP_TYPE_MOVE_TOOL, GimpMoveToolClass))
end_define

begin_define
DECL|macro|GIMP_IS_MOVE_TOOL (obj)
define|#
directive|define
name|GIMP_IS_MOVE_TOOL
parameter_list|(
name|obj
parameter_list|)
value|(G_TYPE_CHECK_INSTANCE_TYPE ((obj), GIMP_TYPE_MOVE_TOOL))
end_define

begin_define
DECL|macro|GIMP_IS_MOVE_TOOL_CLASS (klass)
define|#
directive|define
name|GIMP_IS_MOVE_TOOL_CLASS
parameter_list|(
name|klass
parameter_list|)
value|(G_TYPE_CHECK_CLASS_TYPE ((klass), GIMP_TYPE_MOVE_TOOL))
end_define

begin_define
DECL|macro|GIMP_MOVE_TOOL_GET_CLASS (obj)
define|#
directive|define
name|GIMP_MOVE_TOOL_GET_CLASS
parameter_list|(
name|obj
parameter_list|)
value|(G_TYPE_INSTANCE_GET_CLASS ((obj), GIMP_TYPE_MOVE_TOOL, GimpMoveToolClass))
end_define

begin_define
DECL|macro|GIMP_MOVE_TOOL_GET_OPTIONS (t)
define|#
directive|define
name|GIMP_MOVE_TOOL_GET_OPTIONS
parameter_list|(
name|t
parameter_list|)
value|(GIMP_MOVE_OPTIONS (gimp_tool_get_options (GIMP_TOOL (t))))
end_define

begin_typedef
DECL|typedef|GimpMoveTool
typedef|typedef
name|struct
name|_GimpMoveTool
name|GimpMoveTool
typedef|;
end_typedef

begin_typedef
DECL|typedef|GimpMoveToolClass
typedef|typedef
name|struct
name|_GimpMoveToolClass
name|GimpMoveToolClass
typedef|;
end_typedef

begin_struct
DECL|struct|_GimpMoveTool
struct|struct
name|_GimpMoveTool
block|{
DECL|member|parent_instance
name|GimpDrawTool
name|parent_instance
decl_stmt|;
DECL|member|floating_layer
name|GimpLayer
modifier|*
name|floating_layer
decl_stmt|;
DECL|member|guide
name|GimpGuide
modifier|*
name|guide
decl_stmt|;
DECL|member|moving_guide
name|gboolean
name|moving_guide
decl_stmt|;
DECL|member|guide_position
name|gint
name|guide_position
decl_stmt|;
DECL|member|guide_orientation
name|GimpOrientationType
name|guide_orientation
decl_stmt|;
DECL|member|saved_type
name|GimpTransformType
name|saved_type
decl_stmt|;
DECL|member|old_active_layer
name|GimpLayer
modifier|*
name|old_active_layer
decl_stmt|;
DECL|member|old_active_vectors
name|GimpVectors
modifier|*
name|old_active_vectors
decl_stmt|;
block|}
struct|;
end_struct

begin_struct
DECL|struct|_GimpMoveToolClass
struct|struct
name|_GimpMoveToolClass
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
name|gimp_move_tool_register
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
name|gimp_move_tool_get_type
argument_list|(
name|void
argument_list|)
name|G_GNUC_CONST
decl_stmt|;
end_decl_stmt

begin_function_decl
name|void
name|gimp_move_tool_start_hguide
parameter_list|(
name|GimpTool
modifier|*
name|tool
parameter_list|,
name|GimpDisplay
modifier|*
name|display
parameter_list|)
function_decl|;
end_function_decl

begin_function_decl
name|void
name|gimp_move_tool_start_vguide
parameter_list|(
name|GimpTool
modifier|*
name|tool
parameter_list|,
name|GimpDisplay
modifier|*
name|display
parameter_list|)
function_decl|;
end_function_decl

begin_endif
endif|#
directive|endif
end_endif

begin_comment
comment|/*  __GIMP_MOVE_TOOL_H__  */
end_comment

end_unit

