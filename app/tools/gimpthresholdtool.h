begin_unit|revision:0.9.5;language:C;cregit-version:0.0.1
begin_comment
comment|/* The GIMP -- an image manipulation program  * Copyright (C) 1995 Spencer Kimball and Peter Mattis  *  * This program is free software; you can redistribute it and/or modify  * it under the terms of the GNU General Public License as published by  * the Free Software Foundation; either version 2 of the License, or  * (at your option) any later version.  *  * This program is distributed in the hope that it will be useful,  * but WITHOUT ANY WARRANTY; without even the implied warranty of  * MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the  * GNU General Public License for more details.  *  * You should have received a copy of the GNU General Public License  * along with this program; if not, write to the Free Software  * Foundation, Inc., 59 Temple Place - Suite 330, Boston, MA 02111-1307, USA.  */
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
DECL|macro|GIMP_IS_THRESHOLD_TOOL_CLASS (klass)
define|#
directive|define
name|GIMP_IS_THRESHOLD_TOOL_CLASS
parameter_list|(
name|klass
parameter_list|)
value|(G_TYPE_CHECK_CLASS_TYPE ((klass), GIMP_TYPE_THRESHOLD_TOOL))
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

begin_typedef
DECL|typedef|ThresholdDialog
typedef|typedef
name|struct
name|_ThresholdDialog
name|ThresholdDialog
typedef|;
end_typedef

begin_struct
DECL|struct|_ThresholdDialog
struct|struct
name|_ThresholdDialog
block|{
DECL|member|shell
name|GtkWidget
modifier|*
name|shell
decl_stmt|;
DECL|member|low_threshold_data
name|GtkAdjustment
modifier|*
name|low_threshold_data
decl_stmt|;
DECL|member|high_threshold_data
name|GtkAdjustment
modifier|*
name|high_threshold_data
decl_stmt|;
DECL|member|histogram
name|HistogramWidget
modifier|*
name|histogram
decl_stmt|;
DECL|member|hist
name|GimpHistogram
modifier|*
name|hist
decl_stmt|;
DECL|member|drawable
name|GimpDrawable
modifier|*
name|drawable
decl_stmt|;
DECL|member|image_map
name|ImageMap
modifier|*
name|image_map
decl_stmt|;
DECL|member|color
name|gint
name|color
decl_stmt|;
DECL|member|low_threshold
name|gint
name|low_threshold
decl_stmt|;
DECL|member|high_threshold
name|gint
name|high_threshold
decl_stmt|;
DECL|member|preview
name|gboolean
name|preview
decl_stmt|;
block|}
struct|;
end_struct

begin_function_decl
name|void
name|gimp_threshold_tool_register
parameter_list|(
name|Gimp
modifier|*
name|gimp
parameter_list|)
function_decl|;
end_function_decl

begin_function_decl
name|GtkType
name|gimp_threshold_tool_get_type
parameter_list|(
name|void
parameter_list|)
function_decl|;
end_function_decl

begin_function_decl
name|void
name|threshold_dialog_hide
parameter_list|(
name|void
parameter_list|)
function_decl|;
end_function_decl

begin_function_decl
name|void
name|threshold_2
parameter_list|(
name|gpointer
name|data
parameter_list|,
name|PixelRegion
modifier|*
name|srcPR
parameter_list|,
name|PixelRegion
modifier|*
name|destPR
parameter_list|)
function_decl|;
end_function_decl

begin_endif
endif|#
directive|endif
end_endif

begin_comment
comment|/*  __GIMP_THRESHOLD_TOOL_H__  */
end_comment

end_unit

