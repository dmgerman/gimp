begin_unit|revision:0.9.5;language:C;cregit-version:0.0.1
begin_comment
comment|/* GIMP - The GNU Image Manipulation Program  * Copyright (C) 1995 Spencer Kimball and Peter Mattis  *  * This program is free software: you can redistribute it and/or modify  * it under the terms of the GNU General Public License as published by  * the Free Software Foundation; either version 3 of the License, or  * (at your option) any later version.  *  * This program is distributed in the hope that it will be useful,  * but WITHOUT ANY WARRANTY; without even the implied warranty of  * MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the  * GNU General Public License for more details.  *  * You should have received a copy of the GNU General Public License  * along with this program.  If not, see<http://www.gnu.org/licenses/>.  */
end_comment

begin_include
include|#
directive|include
file|"config.h"
end_include

begin_include
include|#
directive|include
file|<gegl.h>
end_include

begin_include
include|#
directive|include
file|<gtk/gtk.h>
end_include

begin_include
include|#
directive|include
file|"libgimpmath/gimpmath.h"
end_include

begin_include
include|#
directive|include
file|"libgimpwidgets/gimpwidgets.h"
end_include

begin_include
include|#
directive|include
file|"tools-types.h"
end_include

begin_include
include|#
directive|include
file|"paint/gimpmybrushoptions.h"
end_include

begin_include
include|#
directive|include
file|"widgets/gimphelp-ids.h"
end_include

begin_include
include|#
directive|include
file|"gimpmybrushoptions-gui.h"
end_include

begin_include
include|#
directive|include
file|"gimpmybrushtool.h"
end_include

begin_include
include|#
directive|include
file|"gimptoolcontrol.h"
end_include

begin_include
include|#
directive|include
file|"gimp-intl.h"
end_include

begin_macro
name|G_DEFINE_TYPE
argument_list|(
argument|GimpMybrushTool
argument_list|,
argument|gimp_mybrush_tool
argument_list|,
argument|GIMP_TYPE_PAINT_TOOL
argument_list|)
end_macro

begin_define
DECL|macro|parent_class
define|#
directive|define
name|parent_class
value|gimp_mybrush_tool_parent_class
end_define

begin_function_decl
specifier|static
name|GimpCanvasItem
modifier|*
name|gimp_mybrush_tool_get_outline
parameter_list|(
name|GimpPaintTool
modifier|*
name|paint_tool
parameter_list|,
name|GimpDisplay
modifier|*
name|display
parameter_list|,
name|gdouble
name|x
parameter_list|,
name|gdouble
name|y
parameter_list|)
function_decl|;
end_function_decl

begin_function
name|void
DECL|function|gimp_mybrush_tool_register (GimpToolRegisterCallback callback,gpointer data)
name|gimp_mybrush_tool_register
parameter_list|(
name|GimpToolRegisterCallback
name|callback
parameter_list|,
name|gpointer
name|data
parameter_list|)
block|{
call|(
modifier|*
name|callback
call|)
argument_list|(
name|GIMP_TYPE_MYBRUSH_TOOL
argument_list|,
name|GIMP_TYPE_MYBRUSH_OPTIONS
argument_list|,
name|gimp_mybrush_options_gui
argument_list|,
name|GIMP_CONTEXT_FOREGROUND_MASK
operator||
name|GIMP_CONTEXT_BACKGROUND_MASK
operator||
name|GIMP_CONTEXT_OPACITY_MASK
operator||
name|GIMP_CONTEXT_PAINT_MODE_MASK
argument_list|,
literal|"gimp-mybrush-tool"
argument_list|,
name|_
argument_list|(
literal|"MyPaint Brush"
argument_list|)
argument_list|,
name|_
argument_list|(
literal|"MyPaint Brush Tool: Use MyPaint brushes in GIMP"
argument_list|)
argument_list|,
name|N_
argument_list|(
literal|"M_yPaint Brush"
argument_list|)
argument_list|,
literal|"Y"
argument_list|,
name|NULL
argument_list|,
name|GIMP_HELP_TOOL_MYBRUSH
argument_list|,
name|GIMP_STOCK_TOOL_MYBRUSH
argument_list|,
name|data
argument_list|)
expr_stmt|;
block|}
end_function

begin_function
specifier|static
name|void
DECL|function|gimp_mybrush_tool_class_init (GimpMybrushToolClass * klass)
name|gimp_mybrush_tool_class_init
parameter_list|(
name|GimpMybrushToolClass
modifier|*
name|klass
parameter_list|)
block|{
name|GimpPaintToolClass
modifier|*
name|paint_tool_class
init|=
name|GIMP_PAINT_TOOL_CLASS
argument_list|(
name|klass
argument_list|)
decl_stmt|;
name|paint_tool_class
operator|->
name|get_outline
operator|=
name|gimp_mybrush_tool_get_outline
expr_stmt|;
block|}
end_function

begin_function
specifier|static
name|void
DECL|function|gimp_mybrush_tool_init (GimpMybrushTool * mybrush_tool)
name|gimp_mybrush_tool_init
parameter_list|(
name|GimpMybrushTool
modifier|*
name|mybrush_tool
parameter_list|)
block|{
name|GimpTool
modifier|*
name|tool
init|=
name|GIMP_TOOL
argument_list|(
name|mybrush_tool
argument_list|)
decl_stmt|;
name|gimp_tool_control_set_tool_cursor
argument_list|(
name|tool
operator|->
name|control
argument_list|,
name|GIMP_TOOL_CURSOR_INK
argument_list|)
expr_stmt|;
name|gimp_paint_tool_enable_color_picker
argument_list|(
name|GIMP_PAINT_TOOL
argument_list|(
name|mybrush_tool
argument_list|)
argument_list|,
name|GIMP_COLOR_PICK_MODE_FOREGROUND
argument_list|)
expr_stmt|;
block|}
end_function

begin_function
specifier|static
name|GimpCanvasItem
modifier|*
DECL|function|gimp_mybrush_tool_get_outline (GimpPaintTool * paint_tool,GimpDisplay * display,gdouble x,gdouble y)
name|gimp_mybrush_tool_get_outline
parameter_list|(
name|GimpPaintTool
modifier|*
name|paint_tool
parameter_list|,
name|GimpDisplay
modifier|*
name|display
parameter_list|,
name|gdouble
name|x
parameter_list|,
name|gdouble
name|y
parameter_list|)
block|{
name|GimpMybrushOptions
modifier|*
name|options
init|=
name|GIMP_MYBRUSH_TOOL_GET_OPTIONS
argument_list|(
name|paint_tool
argument_list|)
decl_stmt|;
name|gimp_paint_tool_set_draw_circle
argument_list|(
name|paint_tool
argument_list|,
name|TRUE
argument_list|,
name|exp
argument_list|(
name|options
operator|->
name|radius
argument_list|)
argument_list|)
expr_stmt|;
return|return
name|NULL
return|;
block|}
end_function

end_unit

