begin_unit|revision:0.9.5;language:C;cregit-version:0.0.1
begin_comment
comment|/* GIMP - The GNU Image Manipulation Program  * Copyright (C) 1995 Spencer Kimball and Peter Mattis  *  * This program is free software: you can redistribute it and/or modify  * it under the terms of the GNU General Public License as published by  * the Free Software Foundation; either version 3 of the License, or  * (at your option) any later version.  *  * This program is distributed in the hope that it will be useful,  * but WITHOUT ANY WARRANTY; without even the implied warranty of  * MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the  * GNU General Public License for more details.  *  * You should have received a copy of the GNU General Public License  * along with this program.  If not, see<http://www.gnu.org/licenses/>.  */
end_comment

begin_ifndef
ifndef|#
directive|ifndef
name|__GIMP_MEASURE_TOOL_H__
end_ifndef

begin_define
DECL|macro|__GIMP_MEASURE_TOOL_H__
define|#
directive|define
name|__GIMP_MEASURE_TOOL_H__
end_define

begin_include
include|#
directive|include
file|"gimpdrawtool.h"
end_include

begin_comment
comment|/*  possible measure functions  */
end_comment

begin_typedef
typedef|typedef
enum|enum
DECL|enum|__anon2beee42a0103
block|{
DECL|enumerator|CREATING
name|CREATING
block|,
DECL|enumerator|ADDING
name|ADDING
block|,
DECL|enumerator|MOVING
name|MOVING
block|,
DECL|enumerator|MOVING_ALL
name|MOVING_ALL
block|,
DECL|enumerator|GUIDING
name|GUIDING
block|,
DECL|enumerator|FINISHED
name|FINISHED
DECL|typedef|MeasureFunction
block|}
name|MeasureFunction
typedef|;
end_typedef

begin_define
DECL|macro|GIMP_TYPE_MEASURE_TOOL
define|#
directive|define
name|GIMP_TYPE_MEASURE_TOOL
value|(gimp_measure_tool_get_type ())
end_define

begin_define
DECL|macro|GIMP_MEASURE_TOOL (obj)
define|#
directive|define
name|GIMP_MEASURE_TOOL
parameter_list|(
name|obj
parameter_list|)
value|(G_TYPE_CHECK_INSTANCE_CAST ((obj), GIMP_TYPE_MEASURE_TOOL, GimpMeasureTool))
end_define

begin_define
DECL|macro|GIMP_MEASURE_TOOL_CLASS (klass)
define|#
directive|define
name|GIMP_MEASURE_TOOL_CLASS
parameter_list|(
name|klass
parameter_list|)
value|(G_TYPE_CHECK_CLASS_CAST ((klass), GIMP_TYPE_MEASURE_TOOL, GimpMeasureToolClass))
end_define

begin_define
DECL|macro|GIMP_IS_MEASURE_TOOL (obj)
define|#
directive|define
name|GIMP_IS_MEASURE_TOOL
parameter_list|(
name|obj
parameter_list|)
value|(G_TYPE_CHECK_INSTANCE_TYPE ((obj), GIMP_TYPE_MEASURE_TOOL))
end_define

begin_define
DECL|macro|GIMP_IS_MEASURE_TOOL_CLASS (klass)
define|#
directive|define
name|GIMP_IS_MEASURE_TOOL_CLASS
parameter_list|(
name|klass
parameter_list|)
value|(G_TYPE_CHECK_CLASS_TYPE ((klass), GIMP_TYPE_MEASURE_TOOL))
end_define

begin_define
DECL|macro|GIMP_MEASURE_TOOL_GET_CLASS (obj)
define|#
directive|define
name|GIMP_MEASURE_TOOL_GET_CLASS
parameter_list|(
name|obj
parameter_list|)
value|(G_TYPE_INSTANCE_GET_CLASS ((obj), GIMP_TYPE_MEASURE_TOOL, GimpMeasureToolClass))
end_define

begin_define
DECL|macro|GIMP_MEASURE_TOOL_GET_OPTIONS (t)
define|#
directive|define
name|GIMP_MEASURE_TOOL_GET_OPTIONS
parameter_list|(
name|t
parameter_list|)
value|(GIMP_MEASURE_OPTIONS (gimp_tool_get_options (GIMP_TOOL (t))))
end_define

begin_typedef
DECL|typedef|GimpMeasureTool
typedef|typedef
name|struct
name|_GimpMeasureTool
name|GimpMeasureTool
typedef|;
end_typedef

begin_typedef
DECL|typedef|GimpMeasureToolClass
typedef|typedef
name|struct
name|_GimpMeasureToolClass
name|GimpMeasureToolClass
typedef|;
end_typedef

begin_struct
DECL|struct|_GimpMeasureTool
struct|struct
name|_GimpMeasureTool
block|{
DECL|member|parent_instance
name|GimpDrawTool
name|parent_instance
decl_stmt|;
DECL|member|function
name|MeasureFunction
name|function
decl_stmt|;
comment|/*  function we're performing  */
DECL|member|mouse_x
name|gdouble
name|mouse_x
decl_stmt|;
comment|/*  pointer x coordinate       */
DECL|member|mouse_y
name|gdouble
name|mouse_y
decl_stmt|;
comment|/*  pointer y coordinate       */
DECL|member|last_x
name|gint
name|last_x
decl_stmt|;
comment|/*  last x coordinate          */
DECL|member|last_y
name|gint
name|last_y
decl_stmt|;
comment|/*  last y coordinate          */
DECL|member|point
name|gint
name|point
decl_stmt|;
comment|/*  what are we manipulating?  */
DECL|member|num_points
name|gint
name|num_points
decl_stmt|;
comment|/*  how many points?           */
DECL|member|x
name|gint
name|x
index|[
literal|3
index|]
decl_stmt|;
comment|/*  three x coordinates        */
DECL|member|y
name|gint
name|y
index|[
literal|3
index|]
decl_stmt|;
comment|/*  three y coordinates        */
DECL|member|angle1
name|gdouble
name|angle1
decl_stmt|;
comment|/*  first angle                */
DECL|member|angle2
name|gdouble
name|angle2
decl_stmt|;
comment|/*  second angle               */
DECL|member|status_help
name|gboolean
name|status_help
decl_stmt|;
comment|/*  help is currently in s.bar */
DECL|member|handles
name|GimpCanvasItem
modifier|*
name|handles
index|[
literal|3
index|]
decl_stmt|;
DECL|member|dialog
name|GtkWidget
modifier|*
name|dialog
decl_stmt|;
DECL|member|distance_label
name|GtkWidget
modifier|*
name|distance_label
index|[
literal|2
index|]
decl_stmt|;
DECL|member|angle_label
name|GtkWidget
modifier|*
name|angle_label
index|[
literal|2
index|]
decl_stmt|;
DECL|member|width_label
name|GtkWidget
modifier|*
name|width_label
index|[
literal|2
index|]
decl_stmt|;
DECL|member|height_label
name|GtkWidget
modifier|*
name|height_label
index|[
literal|2
index|]
decl_stmt|;
DECL|member|unit_label
name|GtkWidget
modifier|*
name|unit_label
index|[
literal|4
index|]
decl_stmt|;
block|}
struct|;
end_struct

begin_struct
DECL|struct|_GimpMeasureToolClass
struct|struct
name|_GimpMeasureToolClass
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
name|gimp_measure_tool_register
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
name|gimp_measure_tool_get_type
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
comment|/*  __GIMP_MEASURE_TOOL_H__  */
end_comment

end_unit

