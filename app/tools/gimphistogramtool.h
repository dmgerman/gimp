begin_unit|revision:0.9.5;language:C;cregit-version:0.0.1
begin_comment
comment|/* The GIMP -- an image manipulation program  * Copyright (C) 1995 Spencer Kimball and Peter Mattis  *  * This program is free software; you can redistribute it and/or modify  * it under the terms of the GNU General Public License as published by  * the Free Software Foundation; either version 2 of the License, or  * (at your option) any later version.  *  * This program is distributed in the hope that it will be useful,  * but WITHOUT ANY WARRANTY; without even the implied warranty of  * MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the  * GNU General Public License for more details.  *  * You should have received a copy of the GNU General Public License  * along with this program; if not, write to the Free Software  * Foundation, Inc., 59 Temple Place - Suite 330, Boston, MA 02111-1307, USA.  */
end_comment

begin_ifndef
ifndef|#
directive|ifndef
name|__HISTOGRAM_TOOL_H__
end_ifndef

begin_define
DECL|macro|__HISTOGRAM_TOOL_H__
define|#
directive|define
name|__HISTOGRAM_TOOL_H__
end_define

begin_include
include|#
directive|include
file|"gimptool.h"
end_include

begin_comment
comment|/* FIXME: remove the dependency from pdb/color_cmds.c */
end_comment

begin_include
include|#
directive|include
file|"widgets/widgets-types.h"
end_include

begin_define
DECL|macro|HISTOGRAM_WIDTH
define|#
directive|define
name|HISTOGRAM_WIDTH
value|256
end_define

begin_define
DECL|macro|HISTOGRAM_HEIGHT
define|#
directive|define
name|HISTOGRAM_HEIGHT
value|150
end_define

begin_define
DECL|macro|GIMP_TYPE_HISTOGRAM_TOOL
define|#
directive|define
name|GIMP_TYPE_HISTOGRAM_TOOL
value|(gimp_histogram_tool_get_type ())
end_define

begin_define
DECL|macro|GIMP_HISTOGRAM_TOOL (obj)
define|#
directive|define
name|GIMP_HISTOGRAM_TOOL
parameter_list|(
name|obj
parameter_list|)
value|(GTK_CHECK_CAST ((obj), GIMP_TYPE_HISTOGRAM_TOOL, GimpHistogramTool))
end_define

begin_define
DECL|macro|GIMP_IS_HISTOGRAM_TOOL (obj)
define|#
directive|define
name|GIMP_IS_HISTOGRAM_TOOL
parameter_list|(
name|obj
parameter_list|)
value|(GTK_CHECK_TYPE ((obj), GIMP_TYPE_HISTOGRAM_TOOL))
end_define

begin_define
DECL|macro|GIMP_HISTOGRAM_TOOL_CLASS (klass)
define|#
directive|define
name|GIMP_HISTOGRAM_TOOL_CLASS
parameter_list|(
name|klass
parameter_list|)
value|(GTK_CHECK_CLASS_CAST ((klass), GIMP_TYPE_HISTOGRAM_TOOL, GimpHistogramToolClass))
end_define

begin_define
DECL|macro|GIMP_IS_HISTOGRAM_TOOL_CLASS (klass)
define|#
directive|define
name|GIMP_IS_HISTOGRAM_TOOL_CLASS
parameter_list|(
name|klass
parameter_list|)
value|(GTK_CHECK_CLASS_TYPE ((klass), GIMP_TYPE_HISTOGRAM_TOOL))
end_define

begin_typedef
DECL|typedef|GimpHistogramTool
typedef|typedef
name|struct
name|_GimpHistogramTool
name|GimpHistogramTool
typedef|;
end_typedef

begin_typedef
DECL|typedef|GimpHistogramToolClass
typedef|typedef
name|struct
name|_GimpHistogramToolClass
name|GimpHistogramToolClass
typedef|;
end_typedef

begin_struct
DECL|struct|_GimpHistogramTool
struct|struct
name|_GimpHistogramTool
block|{
DECL|member|parent_instance
name|GimpTool
name|parent_instance
decl_stmt|;
block|}
struct|;
end_struct

begin_struct
DECL|struct|_GimpHistogramToolClass
struct|struct
name|_GimpHistogramToolClass
block|{
DECL|member|parent_class
name|GimpToolClass
name|parent_class
decl_stmt|;
block|}
struct|;
end_struct

begin_typedef
DECL|typedef|HistogramToolDialog
typedef|typedef
name|struct
name|_HistogramToolDialog
name|HistogramToolDialog
typedef|;
end_typedef

begin_struct
DECL|struct|_HistogramToolDialog
struct|struct
name|_HistogramToolDialog
block|{
DECL|member|shell
name|GtkWidget
modifier|*
name|shell
decl_stmt|;
DECL|member|info_labels
name|GtkWidget
modifier|*
name|info_labels
index|[
literal|7
index|]
decl_stmt|;
DECL|member|channel_menu
name|GtkWidget
modifier|*
name|channel_menu
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
DECL|member|gradient
name|GtkWidget
modifier|*
name|gradient
decl_stmt|;
DECL|member|mean
name|gdouble
name|mean
decl_stmt|;
DECL|member|std_dev
name|gdouble
name|std_dev
decl_stmt|;
DECL|member|median
name|gdouble
name|median
decl_stmt|;
DECL|member|pixels
name|gdouble
name|pixels
decl_stmt|;
DECL|member|count
name|gdouble
name|count
decl_stmt|;
DECL|member|percentile
name|gdouble
name|percentile
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
DECL|member|channel
name|gint
name|channel
decl_stmt|;
DECL|member|color
name|gint
name|color
decl_stmt|;
block|}
struct|;
end_struct

begin_function_decl
name|void
name|gimp_histogram_tool_register
parameter_list|(
name|void
parameter_list|)
function_decl|;
end_function_decl

begin_function_decl
name|GtkType
name|gimp_histogram_tool_get_type
parameter_list|(
name|void
parameter_list|)
function_decl|;
end_function_decl

begin_function_decl
name|void
name|histogram_dialog_hide
parameter_list|(
name|void
parameter_list|)
function_decl|;
end_function_decl

begin_function_decl
name|void
name|histogram_tool_free
parameter_list|(
name|void
parameter_list|)
function_decl|;
end_function_decl

begin_function_decl
name|void
name|histogram_tool_histogram_range
parameter_list|(
name|HistogramWidget
modifier|*
name|hw
parameter_list|,
name|gint
name|start
parameter_list|,
name|gint
name|end
parameter_list|,
name|gpointer
name|data
parameter_list|)
function_decl|;
end_function_decl

begin_endif
endif|#
directive|endif
end_endif

begin_comment
comment|/* __HISTOGRAM_TOOL_H__ */
end_comment

end_unit

