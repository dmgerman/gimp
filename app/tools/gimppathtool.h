begin_unit|revision:0.9.5;language:C;cregit-version:0.0.1
begin_comment
comment|/* The GIMP -- an image manipulation program  *   * This file Copyright (C) 1999 Simon Budig  *  * This program is free software; you can redistribute it and/or modify  * it under the terms of the GNU General Public License as published by  * the Free Software Foundation; either version 2 of the License, or  * (at your option) any later version.  *  * This program is distributed in the hope that it will be useful,  * but WITHOUT ANY WARRANTY; without even the implied warranty of  * MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the  * GNU General Public License for more details.  *  * You should have received a copy of the GNU General Public License  * along with this program; if not, write to the Free Software  * Foundation, Inc., 59 Temple Place - Suite 330, Boston, MA 02111-1307, USA.  */
end_comment

begin_ifndef
ifndef|#
directive|ifndef
name|__GIMP_PATH_TOOL_H__
end_ifndef

begin_define
DECL|macro|__GIMP_PATH_TOOL_H__
define|#
directive|define
name|__GIMP_PATH_TOOL_H__
end_define

begin_include
include|#
directive|include
file|"gimpdrawtool.h"
end_include

begin_include
include|#
directive|include
file|"path_curves.h"
end_include

begin_define
DECL|macro|GIMP_TYPE_PATH_TOOL
define|#
directive|define
name|GIMP_TYPE_PATH_TOOL
value|(gimp_path_tool_get_type ())
end_define

begin_define
DECL|macro|GIMP_PATH_TOOL (obj)
define|#
directive|define
name|GIMP_PATH_TOOL
parameter_list|(
name|obj
parameter_list|)
value|(G_TYPE_CHECK_INSTANCE_CAST ((obj), GIMP_TYPE_PATH_TOOL, GimpPathTool))
end_define

begin_define
DECL|macro|GIMP_PATH_TOOL_CLASS (klass)
define|#
directive|define
name|GIMP_PATH_TOOL_CLASS
parameter_list|(
name|klass
parameter_list|)
value|(G_TYPE_CHECK_CLASS_CAST ((klass), GIMP_TYPE_PATH_TOOL, GimpPathToolClass))
end_define

begin_define
DECL|macro|GIMP_IS_PATH_TOOL (obj)
define|#
directive|define
name|GIMP_IS_PATH_TOOL
parameter_list|(
name|obj
parameter_list|)
value|(G_TYPE_CHECK_INSTANCE_TYPE ((obj), GIMP_TYPE_PATH_TOOL))
end_define

begin_define
DECL|macro|GIMP_IS_PATH_TOOL_CLASS (klass)
define|#
directive|define
name|GIMP_IS_PATH_TOOL_CLASS
parameter_list|(
name|klass
parameter_list|)
value|(G_TYPE_CHECK_CLASS_TYPE ((klass), GIMP_TYPE_PATH_TOOL))
end_define

begin_define
DECL|macro|GIMP_PATH_TOOL_GET_CLASS (obj)
define|#
directive|define
name|GIMP_PATH_TOOL_GET_CLASS
parameter_list|(
name|obj
parameter_list|)
value|(G_TYPE_INSTANCE_GET_CLASS ((obj), GIMP_TYPE_PATH_TOOL, GimpPathToolClass))
end_define

begin_typedef
DECL|typedef|GimpPathToolClass
typedef|typedef
name|struct
name|_GimpPathToolClass
name|GimpPathToolClass
typedef|;
end_typedef

begin_struct
DECL|struct|_GimpPathTool
struct|struct
name|_GimpPathTool
block|{
DECL|member|parent_instance
name|GimpDrawTool
name|parent_instance
decl_stmt|;
DECL|member|click_type
name|gint
name|click_type
decl_stmt|;
comment|/* where did the user click?         */
DECL|member|click_x
name|gdouble
name|click_x
decl_stmt|;
comment|/* X-coordinate of the click         */
DECL|member|click_y
name|gdouble
name|click_y
decl_stmt|;
comment|/* Y-coordinate of the click         */
DECL|member|click_halfwidth
name|gint
name|click_halfwidth
decl_stmt|;
DECL|member|click_halfheight
name|gint
name|click_halfheight
decl_stmt|;
DECL|member|click_modifier
name|guint
name|click_modifier
decl_stmt|;
comment|/* what modifiers were pressed?      */
DECL|member|click_path
name|NPath
modifier|*
name|click_path
decl_stmt|;
comment|/* On which Path/Curve/Segment       */
DECL|member|click_curve
name|PathCurve
modifier|*
name|click_curve
decl_stmt|;
comment|/* was the click?                    */
DECL|member|click_segment
name|PathSegment
modifier|*
name|click_segment
decl_stmt|;
DECL|member|click_position
name|gdouble
name|click_position
decl_stmt|;
comment|/* The position on the segment       */
DECL|member|click_handle_id
name|gint
name|click_handle_id
decl_stmt|;
comment|/* The handle ID of the segment      */
DECL|member|active_count
name|gint
name|active_count
decl_stmt|;
comment|/* How many segments are active?     */
comment|/*    * WARNING: single_active_segment may contain non NULL Values    * which point to the nirvana. But they are important!    * The pointer is garantueed to be valid, when active_count==1    */
DECL|member|single_active_segment
name|PathSegment
modifier|*
name|single_active_segment
decl_stmt|;
comment|/* The only active segment    */
DECL|member|state
name|gint
name|state
decl_stmt|;
comment|/* state of tool                     */
DECL|member|draw
name|gint
name|draw
decl_stmt|;
comment|/* all or part                       */
DECL|member|cur_path
name|NPath
modifier|*
name|cur_path
decl_stmt|;
comment|/* the current active path           */
DECL|member|scanlines
name|GSList
modifier|*
modifier|*
name|scanlines
decl_stmt|;
comment|/* used in converting a path         */
block|}
struct|;
end_struct

begin_struct
DECL|struct|_GimpPathToolClass
struct|struct
name|_GimpPathToolClass
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
name|gimp_path_tool_register
parameter_list|(
name|GimpToolRegisterCallback
name|callback
parameter_list|,
name|Gimp
modifier|*
name|gimp
parameter_list|)
function_decl|;
end_function_decl

begin_decl_stmt
name|GType
name|gimp_path_tool_get_type
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
comment|/*  __GIMP_PATH_TOOL_H__  */
end_comment

end_unit

