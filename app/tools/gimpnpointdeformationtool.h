begin_unit|revision:0.9.5;language:C;cregit-version:0.0.1
begin_comment
comment|/* GIMP - The GNU Image Manipulation Program  *  * gimpnpointdeformationtool.h  * Copyright (C) 2013 Marek Dvoroznak<dvoromar@gmail.com>  *  * This program is free software: you can redistribute it and/or modify  * it under the terms of the GNU General Public License as published by  * the Free Software Foundation; either version 3 of the License, or  * (at your option) any later version.  *  * This program is distributed in the hope that it will be useful,  * but WITHOUT ANY WARRANTY; without even the implied warranty of  * MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the  * GNU General Public License for more details.  *  * You should have received a copy of the GNU General Public License  * along with this program.  If not, see<http://www.gnu.org/licenses/>.  */
end_comment

begin_ifndef
ifndef|#
directive|ifndef
name|__GIMP_N_POINT_DEFORMATION_TOOL_H__
end_ifndef

begin_define
DECL|macro|__GIMP_N_POINT_DEFORMATION_TOOL_H__
define|#
directive|define
name|__GIMP_N_POINT_DEFORMATION_TOOL_H__
end_define

begin_include
include|#
directive|include
file|"gimpdrawtool.h"
end_include

begin_include
include|#
directive|include
file|"libgimpmath/gimpmath.h"
end_include

begin_include
include|#
directive|include
file|<npd/npd_common.h>
end_include

begin_define
DECL|macro|GIMP_TYPE_N_POINT_DEFORMATION_TOOL
define|#
directive|define
name|GIMP_TYPE_N_POINT_DEFORMATION_TOOL
value|(gimp_n_point_deformation_tool_get_type ())
end_define

begin_define
DECL|macro|GIMP_N_POINT_DEFORMATION_TOOL (obj)
define|#
directive|define
name|GIMP_N_POINT_DEFORMATION_TOOL
parameter_list|(
name|obj
parameter_list|)
value|(G_TYPE_CHECK_INSTANCE_CAST ((obj), GIMP_TYPE_N_POINT_DEFORMATION_TOOL, GimpNPointDeformationTool))
end_define

begin_define
DECL|macro|GIMP_N_POINT_DEFORMATION_TOOL_CLASS (klass)
define|#
directive|define
name|GIMP_N_POINT_DEFORMATION_TOOL_CLASS
parameter_list|(
name|klass
parameter_list|)
value|(G_TYPE_CHECK_CLASS_CAST ((klass), GIMP_TYPE_N_POINT_DEFORMATION_TOOL, GimpNPointDeformationToolClass))
end_define

begin_define
DECL|macro|GIMP_IS_N_POINT_DEFORMATION_TOOL (obj)
define|#
directive|define
name|GIMP_IS_N_POINT_DEFORMATION_TOOL
parameter_list|(
name|obj
parameter_list|)
value|(G_TYPE_CHECK_INSTANCE_TYPE ((obj), GIMP_TYPE_N_POINT_DEFORMATION_TOOL))
end_define

begin_define
DECL|macro|GIMP_IS_N_POINT_DEFORMATION_TOOL_CLASS (klass)
define|#
directive|define
name|GIMP_IS_N_POINT_DEFORMATION_TOOL_CLASS
parameter_list|(
name|klass
parameter_list|)
value|(G_TYPE_CHECK_CLASS_TYPE ((klass), GIMP_TYPE_N_POINT_DEFORMATION_TOOL))
end_define

begin_define
DECL|macro|GIMP_N_POINT_DEFORMATION_TOOL_GET_CLASS (obj)
define|#
directive|define
name|GIMP_N_POINT_DEFORMATION_TOOL_GET_CLASS
parameter_list|(
name|obj
parameter_list|)
value|(G_TYPE_INSTANCE_GET_CLASS ((obj), GIMP_TYPE_N_POINT_DEFORMATION_TOOL, GimpNPointDeformationToolClass))
end_define

begin_define
DECL|macro|GIMP_N_POINT_DEFORMATION_TOOL_GET_OPTIONS (t)
define|#
directive|define
name|GIMP_N_POINT_DEFORMATION_TOOL_GET_OPTIONS
parameter_list|(
name|t
parameter_list|)
value|(GIMP_N_POINT_DEFORMATION_OPTIONS (gimp_tool_get_options (GIMP_TOOL (t))))
end_define

begin_typedef
DECL|typedef|GimpNPointDeformationTool
typedef|typedef
name|struct
name|_GimpNPointDeformationTool
name|GimpNPointDeformationTool
typedef|;
end_typedef

begin_typedef
DECL|typedef|GimpNPointDeformationToolClass
typedef|typedef
name|struct
name|_GimpNPointDeformationToolClass
name|GimpNPointDeformationToolClass
typedef|;
end_typedef

begin_struct
DECL|struct|_GimpNPointDeformationTool
struct|struct
name|_GimpNPointDeformationTool
block|{
DECL|member|parent_instance
name|GimpDrawTool
name|parent_instance
decl_stmt|;
DECL|member|draw_timeout_id
name|guint
name|draw_timeout_id
decl_stmt|;
DECL|member|deform_thread
name|GThread
modifier|*
name|deform_thread
decl_stmt|;
DECL|member|graph
name|GeglNode
modifier|*
name|graph
decl_stmt|;
DECL|member|source
name|GeglNode
modifier|*
name|source
decl_stmt|;
DECL|member|npd_node
name|GeglNode
modifier|*
name|npd_node
decl_stmt|;
DECL|member|sink
name|GeglNode
modifier|*
name|sink
decl_stmt|;
DECL|member|preview_buffer
name|GeglBuffer
modifier|*
name|preview_buffer
decl_stmt|;
DECL|member|model
name|NPDModel
modifier|*
name|model
decl_stmt|;
DECL|member|selected_cp
name|NPDControlPoint
modifier|*
name|selected_cp
decl_stmt|;
comment|/* last selected control point     */
DECL|member|selected_cps
name|GList
modifier|*
name|selected_cps
decl_stmt|;
comment|/* list of selected control points */
DECL|member|hovering_cp
name|NPDControlPoint
modifier|*
name|hovering_cp
decl_stmt|;
DECL|member|lattice_points
name|GimpVector2
modifier|*
name|lattice_points
decl_stmt|;
DECL|member|cursor_x
name|gdouble
name|cursor_x
decl_stmt|;
DECL|member|cursor_y
name|gdouble
name|cursor_y
decl_stmt|;
DECL|member|offset_x
name|gint
name|offset_x
decl_stmt|;
DECL|member|offset_y
name|gint
name|offset_y
decl_stmt|;
DECL|member|movement_start_x
name|gdouble
name|movement_start_x
decl_stmt|;
DECL|member|movement_start_y
name|gdouble
name|movement_start_y
decl_stmt|;
DECL|member|cp_scaled_radius
name|gfloat
name|cp_scaled_radius
decl_stmt|;
comment|/* radius of a control point scaled                                              * according to display shell's scale                                              */
DECL|member|previous_cps_positions
name|GList
modifier|*
name|previous_cps_positions
decl_stmt|;
comment|/* list of NPDPoints holding previous                                              * positions of control points                                              */
DECL|member|active
name|gboolean
name|active
decl_stmt|;
DECL|member|deformation_active
specifier|volatile
name|gboolean
name|deformation_active
decl_stmt|;
DECL|member|rubber_band
name|gboolean
name|rubber_band
decl_stmt|;
block|}
struct|;
end_struct

begin_struct
DECL|struct|_GimpNPointDeformationToolClass
struct|struct
name|_GimpNPointDeformationToolClass
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
name|gimp_n_point_deformation_tool_register
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
name|gimp_n_point_deformation_tool_get_type
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
comment|/*  __GIMP_N_POINT_DEFORMATION_TOOL_H__  */
end_comment

end_unit

