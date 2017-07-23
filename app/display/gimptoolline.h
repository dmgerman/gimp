begin_unit|revision:0.9.5;language:C;cregit-version:0.0.1
begin_comment
comment|/* GIMP - The GNU Image Manipulation Program  * Copyright (C) 1995 Spencer Kimball and Peter Mattis  *  * gimptoolline.h  * Copyright (C) 2017 Michael Natterer<mitch@gimp.org>  *  * This program is free software: you can redistribute it and/or modify  * it under the terms of the GNU General Public License as published by  * the Free Software Foundation; either version 3 of the License, or  * (at your option) any later version.  *  * This program is distributed in the hope that it will be useful,  * but WITHOUT ANY WARRANTY; without even the implied warranty of  * MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the  * GNU General Public License for more details.  *  * You should have received a copy of the GNU General Public License  * along with this program.  If not, see<http://www.gnu.org/licenses/>.  */
end_comment

begin_ifndef
ifndef|#
directive|ifndef
name|__GIMP_TOOL_LINE_H__
end_ifndef

begin_define
DECL|macro|__GIMP_TOOL_LINE_H__
define|#
directive|define
name|__GIMP_TOOL_LINE_H__
end_define

begin_include
include|#
directive|include
file|"gimptoolwidget.h"
end_include

begin_comment
comment|/* in the context of GimpToolLine, "handle" is a collective term for either an  * endpoint or a slider.  a handle value may be either a (nonnegative) slider  * index, or one of the values below:  */
end_comment

begin_define
DECL|macro|GIMP_TOOL_LINE_HANDLE_NONE
define|#
directive|define
name|GIMP_TOOL_LINE_HANDLE_NONE
value|(-3)
end_define

begin_define
DECL|macro|GIMP_TOOL_LINE_HANDLE_START
define|#
directive|define
name|GIMP_TOOL_LINE_HANDLE_START
value|(-2)
end_define

begin_define
DECL|macro|GIMP_TOOL_LINE_HANDLE_END
define|#
directive|define
name|GIMP_TOOL_LINE_HANDLE_END
value|(-1)
end_define

begin_define
DECL|macro|GIMP_TOOL_LINE_HANDLE_IS_SLIDER (handle)
define|#
directive|define
name|GIMP_TOOL_LINE_HANDLE_IS_SLIDER
parameter_list|(
name|handle
parameter_list|)
value|((handle)>= 0)
end_define

begin_define
DECL|macro|GIMP_TYPE_TOOL_LINE
define|#
directive|define
name|GIMP_TYPE_TOOL_LINE
value|(gimp_tool_line_get_type ())
end_define

begin_define
DECL|macro|GIMP_TOOL_LINE (obj)
define|#
directive|define
name|GIMP_TOOL_LINE
parameter_list|(
name|obj
parameter_list|)
value|(G_TYPE_CHECK_INSTANCE_CAST ((obj), GIMP_TYPE_TOOL_LINE, GimpToolLine))
end_define

begin_define
DECL|macro|GIMP_TOOL_LINE_CLASS (klass)
define|#
directive|define
name|GIMP_TOOL_LINE_CLASS
parameter_list|(
name|klass
parameter_list|)
value|(G_TYPE_CHECK_CLASS_CAST ((klass), GIMP_TYPE_TOOL_LINE, GimpToolLineClass))
end_define

begin_define
DECL|macro|GIMP_IS_TOOL_LINE (obj)
define|#
directive|define
name|GIMP_IS_TOOL_LINE
parameter_list|(
name|obj
parameter_list|)
value|(G_TYPE_CHECK_INSTANCE_TYPE ((obj), GIMP_TYPE_TOOL_LINE))
end_define

begin_define
DECL|macro|GIMP_IS_TOOL_LINE_CLASS (klass)
define|#
directive|define
name|GIMP_IS_TOOL_LINE_CLASS
parameter_list|(
name|klass
parameter_list|)
value|(G_TYPE_CHECK_CLASS_TYPE ((klass), GIMP_TYPE_TOOL_LINE))
end_define

begin_define
DECL|macro|GIMP_TOOL_LINE_GET_CLASS (obj)
define|#
directive|define
name|GIMP_TOOL_LINE_GET_CLASS
parameter_list|(
name|obj
parameter_list|)
value|(G_TYPE_INSTANCE_GET_CLASS ((obj), GIMP_TYPE_TOOL_LINE, GimpToolLineClass))
end_define

begin_typedef
DECL|typedef|GimpToolLine
typedef|typedef
name|struct
name|_GimpToolLine
name|GimpToolLine
typedef|;
end_typedef

begin_typedef
DECL|typedef|GimpToolLinePrivate
typedef|typedef
name|struct
name|_GimpToolLinePrivate
name|GimpToolLinePrivate
typedef|;
end_typedef

begin_typedef
DECL|typedef|GimpToolLineClass
typedef|typedef
name|struct
name|_GimpToolLineClass
name|GimpToolLineClass
typedef|;
end_typedef

begin_struct
DECL|struct|_GimpToolLine
struct|struct
name|_GimpToolLine
block|{
DECL|member|parent_instance
name|GimpToolWidget
name|parent_instance
decl_stmt|;
DECL|member|private
name|GimpToolLinePrivate
modifier|*
name|private
decl_stmt|;
block|}
struct|;
end_struct

begin_struct
DECL|struct|_GimpToolLineClass
struct|struct
name|_GimpToolLineClass
block|{
DECL|member|parent_class
name|GimpToolWidgetClass
name|parent_class
decl_stmt|;
comment|/*  signals  */
DECL|member|can_add_slider
name|gboolean
function_decl|(
modifier|*
name|can_add_slider
function_decl|)
parameter_list|(
name|GimpToolLine
modifier|*
name|line
parameter_list|,
name|gdouble
name|value
parameter_list|)
function_decl|;
DECL|member|add_slider
name|gint
function_decl|(
modifier|*
name|add_slider
function_decl|)
parameter_list|(
name|GimpToolLine
modifier|*
name|line
parameter_list|,
name|gdouble
name|value
parameter_list|)
function_decl|;
DECL|member|remove_slider
name|void
function_decl|(
modifier|*
name|remove_slider
function_decl|)
parameter_list|(
name|GimpToolLine
modifier|*
name|line
parameter_list|,
name|gint
name|slider
parameter_list|)
function_decl|;
DECL|member|selection_changed
name|void
function_decl|(
modifier|*
name|selection_changed
function_decl|)
parameter_list|(
name|GimpToolLine
modifier|*
name|line
parameter_list|)
function_decl|;
block|}
struct|;
end_struct

begin_decl_stmt
name|GType
name|gimp_tool_line_get_type
argument_list|(
name|void
argument_list|)
name|G_GNUC_CONST
decl_stmt|;
end_decl_stmt

begin_function_decl
name|GimpToolWidget
modifier|*
name|gimp_tool_line_new
parameter_list|(
name|GimpDisplayShell
modifier|*
name|shell
parameter_list|,
name|gdouble
name|x1
parameter_list|,
name|gdouble
name|y1
parameter_list|,
name|gdouble
name|x2
parameter_list|,
name|gdouble
name|y2
parameter_list|)
function_decl|;
end_function_decl

begin_function_decl
name|void
name|gimp_tool_line_set_sliders
parameter_list|(
name|GimpToolLine
modifier|*
name|line
parameter_list|,
specifier|const
name|GimpControllerSlider
modifier|*
name|sliders
parameter_list|,
name|gint
name|n_sliders
parameter_list|)
function_decl|;
end_function_decl

begin_function_decl
specifier|const
name|GimpControllerSlider
modifier|*
name|gimp_tool_line_get_sliders
parameter_list|(
name|GimpToolLine
modifier|*
name|line
parameter_list|,
name|gint
modifier|*
name|n_sliders
parameter_list|)
function_decl|;
end_function_decl

begin_function_decl
name|void
name|gimp_tool_line_set_selection
parameter_list|(
name|GimpToolLine
modifier|*
name|line
parameter_list|,
name|gint
name|handle
parameter_list|)
function_decl|;
end_function_decl

begin_function_decl
name|gint
name|gimp_tool_line_get_selection
parameter_list|(
name|GimpToolLine
modifier|*
name|line
parameter_list|)
function_decl|;
end_function_decl

begin_endif
endif|#
directive|endif
end_endif

begin_comment
comment|/* __GIMP_TOOL_LINE_H__ */
end_comment

end_unit

