begin_unit|revision:0.9.5;language:C;cregit-version:0.0.1
begin_comment
comment|/* GIMP - The GNU Image Manipulation Program  * Copyright (C) 1995 Spencer Kimball and Peter Mattis  *  * This program is free software; you can redistribute it and/or modify  * it under the terms of the GNU General Public License as published by  * the Free Software Foundation; either version 2 of the License, or  * (at your option) any later version.  *  * This program is distributed in the hope that it will be useful,  * but WITHOUT ANY WARRANTY; without even the implied warranty of  * MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the  * GNU General Public License for more details.  *  * You should have received a copy of the GNU General Public License  * along with this program; if not, write to the Free Software  * Foundation, Inc., 59 Temple Place - Suite 330, Boston, MA 02111-1307, USA.  */
end_comment

begin_ifndef
ifndef|#
directive|ifndef
name|__GIMP_FREE_SELECT_TOOL_H__
end_ifndef

begin_define
DECL|macro|__GIMP_FREE_SELECT_TOOL_H__
define|#
directive|define
name|__GIMP_FREE_SELECT_TOOL_H__
end_define

begin_include
include|#
directive|include
file|"libgimpmath/gimpmath.h"
end_include

begin_include
include|#
directive|include
file|"gimpselectiontool.h"
end_include

begin_define
DECL|macro|GIMP_TYPE_FREE_SELECT_TOOL
define|#
directive|define
name|GIMP_TYPE_FREE_SELECT_TOOL
value|(gimp_free_select_tool_get_type ())
end_define

begin_define
DECL|macro|GIMP_FREE_SELECT_TOOL (obj)
define|#
directive|define
name|GIMP_FREE_SELECT_TOOL
parameter_list|(
name|obj
parameter_list|)
value|(G_TYPE_CHECK_INSTANCE_CAST ((obj), GIMP_TYPE_FREE_SELECT_TOOL, GimpFreeSelectTool))
end_define

begin_define
DECL|macro|GIMP_FREE_SELECT_TOOL_CLASS (klass)
define|#
directive|define
name|GIMP_FREE_SELECT_TOOL_CLASS
parameter_list|(
name|klass
parameter_list|)
value|(G_TYPE_CHECK_CLASS_CAST ((klass), GIMP_TYPE_FREE_SELECT_TOOL, GimpFreeSelectToolClass))
end_define

begin_define
DECL|macro|GIMP_IS_FREE_SELECT_TOOL (obj)
define|#
directive|define
name|GIMP_IS_FREE_SELECT_TOOL
parameter_list|(
name|obj
parameter_list|)
value|(G_TYPE_CHECK_INSTANCE_TYPE ((obj), GIMP_TYPE_FREE_SELECT_TOOL))
end_define

begin_define
DECL|macro|GIMP_IS_FREE_SELECT_TOOL_CLASS (klass)
define|#
directive|define
name|GIMP_IS_FREE_SELECT_TOOL_CLASS
parameter_list|(
name|klass
parameter_list|)
value|(G_TYPE_CHECK_CLASS_TYPE ((klass), GIMP_TYPE_FREE_SELECT_TOOL))
end_define

begin_define
DECL|macro|GIMP_FREE_SELECT_TOOL_GET_CLASS (obj)
define|#
directive|define
name|GIMP_FREE_SELECT_TOOL_GET_CLASS
parameter_list|(
name|obj
parameter_list|)
value|(G_TYPE_INSTANCE_GET_CLASS ((obj), GIMP_TYPE_FREE_SELECT_TOOL, GimpFreeSelectToolClass))
end_define

begin_typedef
DECL|typedef|GimpFreeSelectTool
typedef|typedef
name|struct
name|_GimpFreeSelectTool
name|GimpFreeSelectTool
typedef|;
end_typedef

begin_typedef
DECL|typedef|GimpFreeSelectToolClass
typedef|typedef
name|struct
name|_GimpFreeSelectToolClass
name|GimpFreeSelectToolClass
typedef|;
end_typedef

begin_struct
DECL|struct|_GimpFreeSelectTool
struct|struct
name|_GimpFreeSelectTool
block|{
DECL|member|parent_instance
name|GimpSelectionTool
name|parent_instance
decl_stmt|;
comment|/* Index of grabbed segment index. */
DECL|member|grabbed_segment_index
name|gint
name|grabbed_segment_index
decl_stmt|;
DECL|member|button1_down
name|gboolean
name|button1_down
decl_stmt|;
comment|/* We need to keep track of a number of points when we move a    * segment vertex    */
DECL|member|saved_points_lower_segment
name|GimpVector2
modifier|*
name|saved_points_lower_segment
decl_stmt|;
DECL|member|saved_points_higher_segment
name|GimpVector2
modifier|*
name|saved_points_higher_segment
decl_stmt|;
DECL|member|n_saved_points_lower_segment
name|gint
name|n_saved_points_lower_segment
decl_stmt|;
DECL|member|n_saved_points_higher_segment
name|gint
name|n_saved_points_higher_segment
decl_stmt|;
comment|/* Keeps track wether or not a modification of the polygon has been    * made between _button_press and _button_release    */
DECL|member|polygon_modified
name|gboolean
name|polygon_modified
decl_stmt|;
comment|/* Point which is used to draw the polygon but which is not part of    * it yet    */
DECL|member|pending_point
name|GimpVector2
name|pending_point
decl_stmt|;
DECL|member|show_pending_point
name|gboolean
name|show_pending_point
decl_stmt|;
comment|/* The points of the polygon */
DECL|member|points
name|GimpVector2
modifier|*
name|points
decl_stmt|;
DECL|member|max_n_points
name|gint
name|max_n_points
decl_stmt|;
comment|/* The number of points actually in use */
DECL|member|n_points
name|gint
name|n_points
decl_stmt|;
comment|/* Any int array containing the indices for the points in the    * polygon that connects different segments together    */
DECL|member|segment_indices
name|gint
modifier|*
name|segment_indices
decl_stmt|;
DECL|member|max_n_segment_indices
name|gint
name|max_n_segment_indices
decl_stmt|;
comment|/* The number of segment indices actually in use */
DECL|member|n_segment_indices
name|gint
name|n_segment_indices
decl_stmt|;
block|}
struct|;
end_struct

begin_struct
DECL|struct|_GimpFreeSelectToolClass
struct|struct
name|_GimpFreeSelectToolClass
block|{
DECL|member|parent_class
name|GimpSelectionToolClass
name|parent_class
decl_stmt|;
comment|/*  virtual function  */
DECL|member|select
name|void
function_decl|(
modifier|*
name|select
function_decl|)
parameter_list|(
name|GimpFreeSelectTool
modifier|*
name|free_select_tool
parameter_list|,
name|GimpDisplay
modifier|*
name|display
parameter_list|)
function_decl|;
block|}
struct|;
end_struct

begin_function_decl
name|void
name|gimp_free_select_tool_register
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
name|gimp_free_select_tool_get_type
argument_list|(
name|void
argument_list|)
name|G_GNUC_CONST
decl_stmt|;
end_decl_stmt

begin_function_decl
name|void
name|gimp_free_select_tool_select
parameter_list|(
name|GimpFreeSelectTool
modifier|*
name|free_sel
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
comment|/*  __GIMP_FREE_SELECT_TOOL_H__  */
end_comment

end_unit

