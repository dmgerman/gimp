begin_unit|revision:0.9.5;language:C;cregit-version:0.0.1
begin_comment
comment|/* GIMP - The GNU Image Manipulation Program  * Copyright (C) 1995 Spencer Kimball and Peter Mattis  *  * This program is free software; you can redistribute it and/or modify  * it under the terms of the GNU General Public License as published by  * the Free Software Foundation; either version 2 of the License, or  * (at your option) any later version.  *  * This program is distributed in the hope that it will be useful,  * but WITHOUT ANY WARRANTY; without even the implied warranty of  * MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the  * GNU General Public License for more details.  *  * You should have received a copy of the GNU General Public License  * along with this program; if not, write to the Free Software  * Foundation, Inc., 59 Temple Place - Suite 330, Boston, MA 02111-1307, USA.  */
end_comment

begin_ifndef
ifndef|#
directive|ifndef
name|__GIMP_THRESHOLD_TOOL_H__
end_ifndef

begin_define
DECL|macro|__GIMP_THRESHOLD_TOOL_H__
define|#
directive|define
name|__GIMP_THRESHOLD_TOOL_H__
end_define

begin_include
include|#
directive|include
file|"gimpimagemaptool.h"
end_include

begin_define
DECL|macro|GIMP_TYPE_THRESHOLD_TOOL
define|#
directive|define
name|GIMP_TYPE_THRESHOLD_TOOL
value|(gimp_threshold_tool_get_type ())
end_define

begin_define
DECL|macro|GIMP_THRESHOLD_TOOL (obj)
define|#
directive|define
name|GIMP_THRESHOLD_TOOL
parameter_list|(
name|obj
parameter_list|)
value|(G_TYPE_CHECK_INSTANCE_CAST ((obj), GIMP_TYPE_THRESHOLD_TOOL, GimpThresholdTool))
end_define

begin_define
DECL|macro|GIMP_THRESHOLD_TOOL_CLASS (klass)
define|#
directive|define
name|GIMP_THRESHOLD_TOOL_CLASS
parameter_list|(
name|klass
parameter_list|)
value|(G_TYPE_CHECK_CLASS_CAST ((klass), GIMP_TYPE_THRESHOLD_TOOL, GimpThresholdToolClass))
end_define

begin_define
DECL|macro|GIMP_IS_THRESHOLD_TOOL (obj)
define|#
directive|define
name|GIMP_IS_THRESHOLD_TOOL
parameter_list|(
name|obj
parameter_list|)
value|(G_TYPE_CHECK_INSTANCE_TYPE ((obj), GIMP_TYPE_THRESHOLD_TOOL))
end_define

begin_define
DECL|macro|GIMP_IS_THRESHOLD_TOOL_CLASS (klass)
define|#
directive|define
name|GIMP_IS_THRESHOLD_TOOL_CLASS
parameter_list|(
name|klass
parameter_list|)
value|(G_TYPE_CHECK_CLASS_TYPE ((klass), GIMP_TYPE_THRESHOLD_TOOL))
end_define

begin_define
DECL|macro|GIMP_THRESHOLD_TOOL_GET_CLASS (obj)
define|#
directive|define
name|GIMP_THRESHOLD_TOOL_GET_CLASS
parameter_list|(
name|obj
parameter_list|)
value|(G_TYPE_INSTANCE_GET_CLASS ((obj), GIMP_TYPE_THRESHOLD_TOOL, GimpThresholdToolClass))
end_define

begin_typedef
DECL|typedef|GimpThresholdTool
typedef|typedef
name|struct
name|_GimpThresholdTool
name|GimpThresholdTool
typedef|;
end_typedef

begin_typedef
DECL|typedef|GimpThresholdToolClass
typedef|typedef
name|struct
name|_GimpThresholdToolClass
name|GimpThresholdToolClass
typedef|;
end_typedef

begin_struct
DECL|struct|_GimpThresholdTool
struct|struct
name|_GimpThresholdTool
block|{
DECL|member|parent_instance
name|GimpImageMapTool
name|parent_instance
decl_stmt|;
DECL|member|threshold
name|Threshold
modifier|*
name|threshold
decl_stmt|;
comment|/*  dialog  */
DECL|member|hist
name|GimpHistogram
modifier|*
name|hist
decl_stmt|;
DECL|member|histogram_box
name|GimpHistogramBox
modifier|*
name|histogram_box
decl_stmt|;
block|}
struct|;
end_struct

begin_struct
DECL|struct|_GimpThresholdToolClass
struct|struct
name|_GimpThresholdToolClass
block|{
DECL|member|parent_class
name|GimpImageMapToolClass
name|parent_class
decl_stmt|;
block|}
struct|;
end_struct

begin_function_decl
name|void
name|gimp_threshold_tool_register
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
name|gimp_threshold_tool_get_type
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
comment|/*  __GIMP_THRESHOLD_TOOL_H__  */
end_comment

end_unit

