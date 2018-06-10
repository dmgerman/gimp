begin_unit|revision:0.9.5;language:C;cregit-version:0.0.1
begin_comment
comment|/* GIMP - The GNU Image Manipulation Program  * Copyright (C) 1995-2001 Spencer Kimball, Peter Mattis, and others  *  * This program is free software: you can redistribute it and/or modify  * it under the terms of the GNU General Public License as published by  * the Free Software Foundation; either version 3 of the License, or  * (at your option) any later version.  *  * This program is distributed in the hope that it will be useful,  * but WITHOUT ANY WARRANTY; without even the implied warranty of  * MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the  * GNU General Public License for more details.  *  * You should have received a copy of the GNU General Public License  * along with this program.  If not, see<http://www.gnu.org/licenses/>.  */
end_comment

begin_ifndef
ifndef|#
directive|ifndef
name|__GIMP_TRANSFORM_TOOL_H__
end_ifndef

begin_define
DECL|macro|__GIMP_TRANSFORM_TOOL_H__
define|#
directive|define
name|__GIMP_TRANSFORM_TOOL_H__
end_define

begin_include
include|#
directive|include
file|"gimpdrawtool.h"
end_include

begin_comment
comment|/* This is not the number of items in the enum above, but the max size  * of the enums at the top of each transformation tool, stored in  * trans_info and related  */
end_comment

begin_define
DECL|macro|TRANS_INFO_SIZE
define|#
directive|define
name|TRANS_INFO_SIZE
value|17
end_define

begin_typedef
DECL|typedef|TransInfo
typedef|typedef
name|gdouble
name|TransInfo
index|[
name|TRANS_INFO_SIZE
index|]
typedef|;
end_typedef

begin_define
DECL|macro|GIMP_TYPE_TRANSFORM_TOOL
define|#
directive|define
name|GIMP_TYPE_TRANSFORM_TOOL
value|(gimp_transform_tool_get_type ())
end_define

begin_define
DECL|macro|GIMP_TRANSFORM_TOOL (obj)
define|#
directive|define
name|GIMP_TRANSFORM_TOOL
parameter_list|(
name|obj
parameter_list|)
value|(G_TYPE_CHECK_INSTANCE_CAST ((obj), GIMP_TYPE_TRANSFORM_TOOL, GimpTransformTool))
end_define

begin_define
DECL|macro|GIMP_TRANSFORM_TOOL_CLASS (klass)
define|#
directive|define
name|GIMP_TRANSFORM_TOOL_CLASS
parameter_list|(
name|klass
parameter_list|)
value|(G_TYPE_CHECK_CLASS_CAST ((klass), GIMP_TYPE_TRANSFORM_TOOL, GimpTransformToolClass))
end_define

begin_define
DECL|macro|GIMP_IS_TRANSFORM_TOOL (obj)
define|#
directive|define
name|GIMP_IS_TRANSFORM_TOOL
parameter_list|(
name|obj
parameter_list|)
value|(G_TYPE_CHECK_INSTANCE_TYPE ((obj), GIMP_TYPE_TRANSFORM_TOOL))
end_define

begin_define
DECL|macro|GIMP_IS_TRANSFORM_TOOL_CLASS (klass)
define|#
directive|define
name|GIMP_IS_TRANSFORM_TOOL_CLASS
parameter_list|(
name|klass
parameter_list|)
value|(G_TYPE_CHECK_CLASS_TYPE ((klass), GIMP_TYPE_TRANSFORM_TOOL))
end_define

begin_define
DECL|macro|GIMP_TRANSFORM_TOOL_GET_CLASS (obj)
define|#
directive|define
name|GIMP_TRANSFORM_TOOL_GET_CLASS
parameter_list|(
name|obj
parameter_list|)
value|(G_TYPE_INSTANCE_GET_CLASS ((obj), GIMP_TYPE_TRANSFORM_TOOL, GimpTransformToolClass))
end_define

begin_define
DECL|macro|GIMP_TRANSFORM_TOOL_GET_OPTIONS (t)
define|#
directive|define
name|GIMP_TRANSFORM_TOOL_GET_OPTIONS
parameter_list|(
name|t
parameter_list|)
value|(GIMP_TRANSFORM_OPTIONS (gimp_tool_get_options (GIMP_TOOL (t))))
end_define

begin_typedef
DECL|typedef|GimpTransformToolClass
typedef|typedef
name|struct
name|_GimpTransformToolClass
name|GimpTransformToolClass
typedef|;
end_typedef

begin_struct
DECL|struct|_GimpTransformTool
struct|struct
name|_GimpTransformTool
block|{
DECL|member|parent_instance
name|GimpDrawTool
name|parent_instance
decl_stmt|;
DECL|member|drawable
name|GimpDrawable
modifier|*
name|drawable
decl_stmt|;
DECL|member|x1
DECL|member|y1
name|gint
name|x1
decl_stmt|,
name|y1
decl_stmt|;
comment|/*  upper left hand coordinate         */
DECL|member|x2
DECL|member|y2
name|gint
name|x2
decl_stmt|,
name|y2
decl_stmt|;
comment|/*  lower right hand coords            */
DECL|member|transform
name|GimpMatrix3
name|transform
decl_stmt|;
comment|/*  transformation matrix              */
DECL|member|transform_valid
name|gboolean
name|transform_valid
decl_stmt|;
comment|/*  whether the matrix is valid        */
block|}
struct|;
end_struct

begin_struct
DECL|struct|_GimpTransformToolClass
struct|struct
name|_GimpTransformToolClass
block|{
DECL|member|parent_class
name|GimpDrawToolClass
name|parent_class
decl_stmt|;
comment|/*  virtual functions  */
DECL|member|recalc_matrix
name|void
function_decl|(
modifier|*
name|recalc_matrix
function_decl|)
parameter_list|(
name|GimpTransformTool
modifier|*
name|tr_tool
parameter_list|)
function_decl|;
DECL|member|get_undo_desc
name|gchar
modifier|*
function_decl|(
modifier|*
name|get_undo_desc
function_decl|)
parameter_list|(
name|GimpTransformTool
modifier|*
name|tr_tool
parameter_list|)
function_decl|;
DECL|member|transform
name|GeglBuffer
modifier|*
function_decl|(
modifier|*
name|transform
function_decl|)
parameter_list|(
name|GimpTransformTool
modifier|*
name|tr_tool
parameter_list|,
name|GimpItem
modifier|*
name|item
parameter_list|,
name|GeglBuffer
modifier|*
name|orig_buffer
parameter_list|,
name|gint
name|orig_offset_x
parameter_list|,
name|gint
name|orig_offset_y
parameter_list|,
name|GimpColorProfile
modifier|*
modifier|*
name|buffer_profile
parameter_list|,
name|gint
modifier|*
name|new_offset_x
parameter_list|,
name|gint
modifier|*
name|new_offset_y
parameter_list|)
function_decl|;
DECL|member|progress_text
specifier|const
name|gchar
modifier|*
name|progress_text
decl_stmt|;
block|}
struct|;
end_struct

begin_decl_stmt
name|GType
name|gimp_transform_tool_get_type
argument_list|(
name|void
argument_list|)
name|G_GNUC_CONST
decl_stmt|;
end_decl_stmt

begin_function_decl
name|GimpItem
modifier|*
name|gimp_transform_tool_get_active_item
parameter_list|(
name|GimpTransformTool
modifier|*
name|tr_tool
parameter_list|,
name|GimpDisplay
modifier|*
name|display
parameter_list|)
function_decl|;
end_function_decl

begin_function_decl
name|GimpItem
modifier|*
name|gimp_transform_tool_check_active_item
parameter_list|(
name|GimpTransformTool
modifier|*
name|tr_tool
parameter_list|,
name|GimpDisplay
modifier|*
name|display
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
name|gimp_transform_tool_bounds
parameter_list|(
name|GimpTransformTool
modifier|*
name|tr_tool
parameter_list|,
name|GimpDisplay
modifier|*
name|display
parameter_list|)
function_decl|;
end_function_decl

begin_function_decl
name|void
name|gimp_transform_tool_recalc_matrix
parameter_list|(
name|GimpTransformTool
modifier|*
name|tr_tool
parameter_list|,
name|GimpDisplay
modifier|*
name|display
parameter_list|)
function_decl|;
end_function_decl

begin_function_decl
name|gboolean
name|gimp_transform_tool_transform
parameter_list|(
name|GimpTransformTool
modifier|*
name|tr_tool
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
comment|/*  __GIMP_TRANSFORM_TOOL_H__  */
end_comment

end_unit

