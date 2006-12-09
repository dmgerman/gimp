begin_unit|revision:0.9.5;language:C;cregit-version:0.0.1
begin_comment
comment|/* GIMP - The GNU Image Manipulation Program  * Copyright (C) 1995 Spencer Kimball and Peter Mattis  *  * This program is free software; you can redistribute it and/or modify  * it under the terms of the GNU General Public License as published by  * the Free Software Foundation; either version 2 of the License, or  * (at your option) any later version.  *  * This program is distributed in the hope that it will be useful,  * but WITHOUT ANY WARRANTY; without even the implied warranty of  * MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the  * GNU General Public License for more details.  *  * You should have received a copy of the GNU General Public License  * along with this program; if not, write to the Free Software  * Foundation, Inc., 59 Temple Place - Suite 330, Boston, MA 02111-1307, USA.  */
end_comment

begin_ifndef
ifndef|#
directive|ifndef
name|__GIMP_CURVES_TOOL_H__
end_ifndef

begin_define
DECL|macro|__GIMP_CURVES_TOOL_H__
define|#
directive|define
name|__GIMP_CURVES_TOOL_H__
end_define

begin_include
include|#
directive|include
file|"gimpimagemaptool.h"
end_include

begin_define
DECL|macro|GIMP_TYPE_CURVES_TOOL
define|#
directive|define
name|GIMP_TYPE_CURVES_TOOL
value|(gimp_curves_tool_get_type ())
end_define

begin_define
DECL|macro|GIMP_CURVES_TOOL (obj)
define|#
directive|define
name|GIMP_CURVES_TOOL
parameter_list|(
name|obj
parameter_list|)
value|(G_TYPE_CHECK_INSTANCE_CAST ((obj), GIMP_TYPE_CURVES_TOOL, GimpCurvesTool))
end_define

begin_define
DECL|macro|GIMP_IS_CURVES_TOOL (obj)
define|#
directive|define
name|GIMP_IS_CURVES_TOOL
parameter_list|(
name|obj
parameter_list|)
value|(G_TYPE_CHECK_INSTANCE_TYPE ((obj), GIMP_TYPE_CURVES_TOOL))
end_define

begin_define
DECL|macro|GIMP_CURVES_TOOL_CLASS (klass)
define|#
directive|define
name|GIMP_CURVES_TOOL_CLASS
parameter_list|(
name|klass
parameter_list|)
value|(G_TYPE_CHECK_CLASS_CAST ((klass), GIMP_TYPE_CURVES_TOOL, GimpCurvesToolClass))
end_define

begin_define
DECL|macro|GIMP_IS_CURVES_TOOL_CLASS (klass)
define|#
directive|define
name|GIMP_IS_CURVES_TOOL_CLASS
parameter_list|(
name|klass
parameter_list|)
value|(G_TYPE_CHECK_CLASS_TYPE ((klass), GIMP_TYPE_CURVES_TOOL))
end_define

begin_typedef
DECL|typedef|GimpCurvesTool
typedef|typedef
name|struct
name|_GimpCurvesTool
name|GimpCurvesTool
typedef|;
end_typedef

begin_typedef
DECL|typedef|GimpCurvesToolClass
typedef|typedef
name|struct
name|_GimpCurvesToolClass
name|GimpCurvesToolClass
typedef|;
end_typedef

begin_struct
DECL|struct|_GimpCurvesTool
struct|struct
name|_GimpCurvesTool
block|{
DECL|member|parent_instance
name|GimpImageMapTool
name|parent_instance
decl_stmt|;
DECL|member|curves
name|Curves
modifier|*
name|curves
decl_stmt|;
DECL|member|lut
name|GimpLut
modifier|*
name|lut
decl_stmt|;
comment|/* dialog */
DECL|member|color
name|gboolean
name|color
decl_stmt|;
DECL|member|alpha
name|gboolean
name|alpha
decl_stmt|;
DECL|member|channel
name|GimpHistogramChannel
name|channel
decl_stmt|;
DECL|member|selected
name|gint
name|selected
decl_stmt|;
DECL|member|last
name|gint
name|last
decl_stmt|;
DECL|member|leftmost
name|gint
name|leftmost
decl_stmt|;
DECL|member|rightmost
name|gint
name|rightmost
decl_stmt|;
DECL|member|col_value
name|gint
name|col_value
index|[
literal|5
index|]
decl_stmt|;
DECL|member|grabbed
name|gboolean
name|grabbed
decl_stmt|;
DECL|member|hist
name|GimpHistogram
modifier|*
name|hist
decl_stmt|;
DECL|member|channel_menu
name|GtkWidget
modifier|*
name|channel_menu
decl_stmt|;
DECL|member|xrange
name|GtkWidget
modifier|*
name|xrange
decl_stmt|;
DECL|member|yrange
name|GtkWidget
modifier|*
name|yrange
decl_stmt|;
DECL|member|graph
name|GtkWidget
modifier|*
name|graph
decl_stmt|;
DECL|member|curve_type
name|GtkWidget
modifier|*
name|curve_type
decl_stmt|;
DECL|member|cursor_x
name|gint
name|cursor_x
decl_stmt|;
DECL|member|cursor_y
name|gint
name|cursor_y
decl_stmt|;
DECL|member|xpos_layout
name|PangoLayout
modifier|*
name|xpos_layout
decl_stmt|;
DECL|member|cursor_layout
name|PangoLayout
modifier|*
name|cursor_layout
decl_stmt|;
DECL|member|cursor_rect
name|PangoRectangle
name|cursor_rect
decl_stmt|;
block|}
struct|;
end_struct

begin_struct
DECL|struct|_GimpCurvesToolClass
struct|struct
name|_GimpCurvesToolClass
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
name|gimp_curves_tool_register
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
name|gimp_curves_tool_get_type
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
comment|/*  __CURVES_H__  */
end_comment

end_unit

