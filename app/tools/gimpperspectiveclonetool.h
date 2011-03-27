begin_unit|revision:0.9.5;language:C;cregit-version:0.0.1
begin_comment
comment|/* GIMP - The GNU Image Manipulation Program  * Copyright (C) 1995 Spencer Kimball and Peter Mattis  *  * This program is free software: you can redistribute it and/or modify  * it under the terms of the GNU General Public License as published by  * the Free Software Foundation; either version 3 of the License, or  * (at your option) any later version.  *  * This program is distributed in the hope that it will be useful,  * but WITHOUT ANY WARRANTY; without even the implied warranty of  * MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the  * GNU General Public License for more details.  *  * You should have received a copy of the GNU General Public License  * along with this program.  If not, see<http://www.gnu.org/licenses/>.  */
end_comment

begin_ifndef
ifndef|#
directive|ifndef
name|__GIMP_PERSPECTIVE_CLONE_TOOL_H__
end_ifndef

begin_define
DECL|macro|__GIMP_PERSPECTIVE_CLONE_TOOL_H__
define|#
directive|define
name|__GIMP_PERSPECTIVE_CLONE_TOOL_H__
end_define

begin_include
include|#
directive|include
file|"gimpbrushtool.h"
end_include

begin_include
include|#
directive|include
file|"gimptransformtool.h"
end_include

begin_comment
comment|/* for TransInfo */
end_comment

begin_define
DECL|macro|GIMP_TYPE_PERSPECTIVE_CLONE_TOOL
define|#
directive|define
name|GIMP_TYPE_PERSPECTIVE_CLONE_TOOL
value|(gimp_perspective_clone_tool_get_type ())
end_define

begin_define
DECL|macro|GIMP_PERSPECTIVE_CLONE_TOOL (obj)
define|#
directive|define
name|GIMP_PERSPECTIVE_CLONE_TOOL
parameter_list|(
name|obj
parameter_list|)
value|(G_TYPE_CHECK_INSTANCE_CAST ((obj), GIMP_TYPE_PERSPECTIVE_CLONE_TOOL, GimpPerspectiveCloneTool))
end_define

begin_define
DECL|macro|GIMP_PERSPECTIVE_CLONE_TOOL_CLASS (klass)
define|#
directive|define
name|GIMP_PERSPECTIVE_CLONE_TOOL_CLASS
parameter_list|(
name|klass
parameter_list|)
value|(G_TYPE_CHECK_CLASS_CAST ((klass), GIMP_TYPE_PERSPECTIVE_CLONE_TOOL, GimpPerspectiveCloneToolClass))
end_define

begin_define
DECL|macro|GIMP_IS_PERSPECTIVE_CLONE_TOOL (obj)
define|#
directive|define
name|GIMP_IS_PERSPECTIVE_CLONE_TOOL
parameter_list|(
name|obj
parameter_list|)
value|(G_TYPE_CHECK_INSTANCE_TYPE ((obj), GIMP_TYPE_PERSPECTIVE_CLONE_TOOL))
end_define

begin_define
DECL|macro|GIMP_IS_PERSPECTIVE_CLONE_TOOL_CLASS (klass)
define|#
directive|define
name|GIMP_IS_PERSPECTIVE_CLONE_TOOL_CLASS
parameter_list|(
name|klass
parameter_list|)
value|(G_TYPE_CHECK_CLASS_TYPE ((klass), GIMP_TYPE_PERSPECTIVE_CLONE_TOOL))
end_define

begin_define
DECL|macro|GIMP_PERSPECTIVE_CLONE_TOOL_GET_CLASS (obj)
define|#
directive|define
name|GIMP_PERSPECTIVE_CLONE_TOOL_GET_CLASS
parameter_list|(
name|obj
parameter_list|)
value|(G_TYPE_INSTANCE_GET_CLASS ((obj), GIMP_TYPE_PERSPECTIVE_CLONE_TOOL, GimpPerspectiveCloneToolClass))
end_define

begin_define
DECL|macro|GIMP_PERSPECTIVE_CLONE_TOOL_GET_OPTIONS (t)
define|#
directive|define
name|GIMP_PERSPECTIVE_CLONE_TOOL_GET_OPTIONS
parameter_list|(
name|t
parameter_list|)
value|(GIMP_PERSPECTIVE_CLONE_OPTIONS (gimp_tool_get_options (GIMP_TOOL (t))))
end_define

begin_typedef
DECL|typedef|GimpPerspectiveCloneTool
typedef|typedef
name|struct
name|_GimpPerspectiveCloneTool
name|GimpPerspectiveCloneTool
typedef|;
end_typedef

begin_typedef
DECL|typedef|GimpPerspectiveCloneToolClass
typedef|typedef
name|struct
name|_GimpPerspectiveCloneToolClass
name|GimpPerspectiveCloneToolClass
typedef|;
end_typedef

begin_struct
DECL|struct|_GimpPerspectiveCloneTool
struct|struct
name|_GimpPerspectiveCloneTool
block|{
DECL|member|parent_instance
name|GimpBrushTool
name|parent_instance
decl_stmt|;
DECL|member|src_display
name|GimpDisplay
modifier|*
name|src_display
decl_stmt|;
DECL|member|src_x
name|gint
name|src_x
decl_stmt|;
DECL|member|src_y
name|gint
name|src_y
decl_stmt|;
DECL|member|curx
name|gdouble
name|curx
decl_stmt|;
comment|/*  current x coord                  */
DECL|member|cury
name|gdouble
name|cury
decl_stmt|;
comment|/*  current y coord                  */
DECL|member|lastx
name|gdouble
name|lastx
decl_stmt|;
comment|/*  last x coord                     */
DECL|member|lasty
name|gdouble
name|lasty
decl_stmt|;
comment|/*  last y coord                     */
DECL|member|transform
name|GimpMatrix3
name|transform
decl_stmt|;
comment|/*  transformation matrix            */
DECL|member|trans_info
name|TransInfo
name|trans_info
decl_stmt|;
comment|/*  transformation info              */
DECL|member|old_trans_info
name|TransInfo
name|old_trans_info
decl_stmt|;
comment|/*  for cancelling a drag operation  */
DECL|member|x1
DECL|member|y1
name|gint
name|x1
decl_stmt|,
name|y1
decl_stmt|;
comment|/*  upper left hand coordinate       */
DECL|member|x2
DECL|member|y2
name|gint
name|x2
decl_stmt|,
name|y2
decl_stmt|;
comment|/*  lower right hand coords          */
DECL|member|tx1
DECL|member|ty1
name|gdouble
name|tx1
decl_stmt|,
name|ty1
decl_stmt|;
comment|/*  transformed coords               */
DECL|member|tx2
DECL|member|ty2
name|gdouble
name|tx2
decl_stmt|,
name|ty2
decl_stmt|;
DECL|member|tx3
DECL|member|ty3
name|gdouble
name|tx3
decl_stmt|,
name|ty3
decl_stmt|;
DECL|member|tx4
DECL|member|ty4
name|gdouble
name|tx4
decl_stmt|,
name|ty4
decl_stmt|;
DECL|member|tcx
DECL|member|tcy
name|gdouble
name|tcx
decl_stmt|,
name|tcy
decl_stmt|;
DECL|member|function
name|TransformAction
name|function
decl_stmt|;
comment|/*  current tool activity            */
block|}
struct|;
end_struct

begin_struct
DECL|struct|_GimpPerspectiveCloneToolClass
struct|struct
name|_GimpPerspectiveCloneToolClass
block|{
DECL|member|parent_class
name|GimpBrushToolClass
name|parent_class
decl_stmt|;
block|}
struct|;
end_struct

begin_function_decl
name|void
name|gimp_perspective_clone_tool_register
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
name|gimp_perspective_clone_tool_get_type
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
comment|/*  __GIMP_PERSPECTIVE_CLONE_TOOL_H__  */
end_comment

end_unit

