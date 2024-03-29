begin_unit|revision:0.9.5;language:C;cregit-version:0.0.1
begin_comment
comment|/* GIMP - The GNU Image Manipulation Program  *  * gimpcagetool.h  * Copyright (C) 2010 Michael MurÃ©<batolettre@gmail.com>  *  * This program is free software: you can redistribute it and/or modify  * it under the terms of the GNU General Public License as published by  * the Free Software Foundation; either version 3 of the License, or  * (at your option) any later version.  *  * This program is distributed in the hope that it will be useful,  * but WITHOUT ANY WARRANTY; without even the implied warranty of  * MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the  * GNU General Public License for more details.  *  * You should have received a copy of the GNU General Public License  * along with this program.  If not, see<https://www.gnu.org/licenses/>.  */
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
DECL|member|offset_x
name|gint
name|offset_x
decl_stmt|;
comment|/* used to convert the cage point coords */
DECL|member|offset_y
name|gint
name|offset_y
decl_stmt|;
comment|/* to drawable coords */
DECL|member|cursor_x
name|gdouble
name|cursor_x
decl_stmt|;
comment|/* Hold the cursor x position */
DECL|member|cursor_y
name|gdouble
name|cursor_y
decl_stmt|;
comment|/* Hold the cursor y position */
DECL|member|movement_start_x
name|gdouble
name|movement_start_x
decl_stmt|;
comment|/* Where the movement started */
DECL|member|movement_start_y
name|gdouble
name|movement_start_y
decl_stmt|;
comment|/* Where the movement started */
DECL|member|selection_start_x
name|gdouble
name|selection_start_x
decl_stmt|;
comment|/* Where the selection started */
DECL|member|selection_start_y
name|gdouble
name|selection_start_y
decl_stmt|;
comment|/* Where the selection started */
DECL|member|hovering_handle
name|gint
name|hovering_handle
decl_stmt|;
comment|/* Handle which the cursor is above */
DECL|member|hovering_edge
name|gint
name|hovering_edge
decl_stmt|;
comment|/* Edge which the cursor is above */
DECL|member|coef
name|GeglBuffer
modifier|*
name|coef
decl_stmt|;
comment|/* Gegl buffer where the coefficient of the transformation are stored */
DECL|member|dirty_coef
name|gboolean
name|dirty_coef
decl_stmt|;
comment|/* Indicate if the coef are still valid */
DECL|member|render_node
name|GeglNode
modifier|*
name|render_node
decl_stmt|;
comment|/* Gegl node graph to render the transformation */
DECL|member|cage_node
name|GeglNode
modifier|*
name|cage_node
decl_stmt|;
comment|/* Gegl node that compute the cage transform */
DECL|member|coef_node
name|GeglNode
modifier|*
name|coef_node
decl_stmt|;
comment|/* Gegl node that read in the coef buffer */
DECL|member|tool_state
name|gint
name|tool_state
decl_stmt|;
comment|/* Current state in statemachine */
DECL|member|filter
name|GimpDrawableFilter
modifier|*
name|filter
decl_stmt|;
comment|/* For preview */
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

