begin_unit|revision:0.9.5;language:C;cregit-version:0.0.1
begin_comment
comment|/* The GIMP -- an image manipulation program  * Copyright (C) 1995 Spencer Kimball and Peter Mattis  *  * This program is free software; you can redistribute it and/or modify  * it under the terms of the GNU General Public License as published by  * the Free Software Foundation; either version 2 of the License, or  * (at your option) any later version.  *  * This program is distributed in the hope that it will be useful,  * but WITHOUT ANY WARRANTY; without even the implied warranty of  * MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the  * GNU General Public License for more details.  *  * You should have received a copy of the GNU General Public License  * along with this program; if not, write to the Free Software  * Foundation, Inc., 59 Temple Place - Suite 330, Boston, MA 02111-1307, USA.  */
end_comment

begin_include
include|#
directive|include
file|"config.h"
end_include

begin_include
include|#
directive|include
file|<stdlib.h>
end_include

begin_include
include|#
directive|include
file|<gtk/gtk.h>
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
file|"core/gimpchannel.h"
end_include

begin_include
include|#
directive|include
file|"core/gimpchannel-select.h"
end_include

begin_include
include|#
directive|include
file|"core/gimpimage.h"
end_include

begin_include
include|#
directive|include
file|"core/gimptoolinfo.h"
end_include

begin_include
include|#
directive|include
file|"widgets/gimphelp-ids.h"
end_include

begin_include
include|#
directive|include
file|"display/gimpdisplay.h"
end_include

begin_include
include|#
directive|include
file|"gimprectangletool.h"
end_include

begin_include
include|#
directive|include
file|"gimpellipseselecttool.h"
end_include

begin_include
include|#
directive|include
file|"gimprectangleselectoptions.h"
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

begin_function_decl
specifier|static
name|void
name|gimp_ellipse_select_tool_draw
parameter_list|(
name|GimpDrawTool
modifier|*
name|draw_tool
parameter_list|)
function_decl|;
end_function_decl

begin_function_decl
specifier|static
name|void
name|gimp_ellipse_select_tool_select
parameter_list|(
name|GimpRectSelectTool
modifier|*
name|rect_tool
parameter_list|,
name|SelectOps
name|operation
parameter_list|,
name|gint
name|x
parameter_list|,
name|gint
name|y
parameter_list|,
name|gint
name|w
parameter_list|,
name|gint
name|h
parameter_list|)
function_decl|;
end_function_decl

begin_macro
DECL|function|G_DEFINE_TYPE (GimpEllipseSelectTool,gimp_ellipse_select_tool,GIMP_TYPE_RECT_SELECT_TOOL)
name|G_DEFINE_TYPE
argument_list|(
argument|GimpEllipseSelectTool
argument_list|,
argument|gimp_ellipse_select_tool
argument_list|,
argument|GIMP_TYPE_RECT_SELECT_TOOL
argument_list|)
end_macro

begin_define
DECL|macro|parent_class
define|#
directive|define
name|parent_class
value|gimp_ellipse_select_tool_parent_class
end_define

begin_comment
comment|/*  public functions  */
end_comment

begin_function
name|void
name|gimp_ellipse_select_tool_register
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
name|GIMP_TYPE_ELLIPSE_SELECT_TOOL
argument_list|,
name|GIMP_TYPE_RECT_SELECT_OPTIONS
argument_list|,
name|gimp_rect_select_options_gui
argument_list|,
literal|0
argument_list|,
literal|"gimp-ellipse-select-tool"
argument_list|,
name|_
argument_list|(
literal|"Ellipse Select"
argument_list|)
argument_list|,
name|_
argument_list|(
literal|"Select elliptical regions"
argument_list|)
argument_list|,
name|N_
argument_list|(
literal|"_Ellipse Select"
argument_list|)
argument_list|,
literal|"E"
argument_list|,
name|NULL
argument_list|,
name|GIMP_HELP_TOOL_ELLIPSE_SELECT
argument_list|,
name|GIMP_STOCK_TOOL_ELLIPSE_SELECT
argument_list|,
name|data
argument_list|)
expr_stmt|;
block|}
end_function

begin_comment
comment|/*  private functions  */
end_comment

begin_function
specifier|static
name|void
DECL|function|gimp_ellipse_select_tool_class_init (GimpEllipseSelectToolClass * klass)
name|gimp_ellipse_select_tool_class_init
parameter_list|(
name|GimpEllipseSelectToolClass
modifier|*
name|klass
parameter_list|)
block|{
name|GimpDrawToolClass
modifier|*
name|draw_tool_class
decl_stmt|;
name|GimpRectSelectToolClass
modifier|*
name|rect_tool_class
decl_stmt|;
name|draw_tool_class
operator|=
name|GIMP_DRAW_TOOL_CLASS
argument_list|(
name|klass
argument_list|)
expr_stmt|;
name|rect_tool_class
operator|=
name|GIMP_RECT_SELECT_TOOL_CLASS
argument_list|(
name|klass
argument_list|)
expr_stmt|;
name|draw_tool_class
operator|->
name|draw
operator|=
name|gimp_ellipse_select_tool_draw
expr_stmt|;
name|rect_tool_class
operator|->
name|select
operator|=
name|gimp_ellipse_select_tool_select
expr_stmt|;
block|}
end_function

begin_function
specifier|static
name|void
DECL|function|gimp_ellipse_select_tool_init (GimpEllipseSelectTool * ellipse_select)
name|gimp_ellipse_select_tool_init
parameter_list|(
name|GimpEllipseSelectTool
modifier|*
name|ellipse_select
parameter_list|)
block|{
name|GimpTool
modifier|*
name|tool
init|=
name|GIMP_TOOL
argument_list|(
name|ellipse_select
argument_list|)
decl_stmt|;
name|GimpRectangleTool
modifier|*
name|rect_tool
init|=
name|GIMP_RECTANGLE_TOOL
argument_list|(
name|ellipse_select
argument_list|)
decl_stmt|;
name|gimp_tool_control_set_tool_cursor
argument_list|(
name|tool
operator|->
name|control
argument_list|,
name|GIMP_TOOL_CURSOR_ELLIPSE_SELECT
argument_list|)
expr_stmt|;
name|gimp_rectangle_tool_set_constrain
argument_list|(
name|rect_tool
argument_list|,
name|FALSE
argument_list|)
expr_stmt|;
block|}
end_function

begin_function
specifier|static
name|void
DECL|function|gimp_ellipse_select_tool_draw (GimpDrawTool * draw_tool)
name|gimp_ellipse_select_tool_draw
parameter_list|(
name|GimpDrawTool
modifier|*
name|draw_tool
parameter_list|)
block|{
name|GimpRectSelectTool
modifier|*
name|rect_sel
init|=
name|GIMP_RECT_SELECT_TOOL
argument_list|(
name|draw_tool
argument_list|)
decl_stmt|;
name|gint
name|x1
decl_stmt|,
name|y1
decl_stmt|;
name|gint
name|x2
decl_stmt|,
name|y2
decl_stmt|;
name|g_object_get
argument_list|(
name|rect_sel
argument_list|,
literal|"x1"
argument_list|,
operator|&
name|x1
argument_list|,
literal|"y1"
argument_list|,
operator|&
name|y1
argument_list|,
literal|"x2"
argument_list|,
operator|&
name|x2
argument_list|,
literal|"y2"
argument_list|,
operator|&
name|y2
argument_list|,
name|NULL
argument_list|)
expr_stmt|;
name|gimp_draw_tool_draw_arc
argument_list|(
name|draw_tool
argument_list|,
name|FALSE
argument_list|,
name|x1
argument_list|,
name|y1
argument_list|,
name|x2
operator|-
name|x1
argument_list|,
name|y2
operator|-
name|y1
argument_list|,
literal|0
argument_list|,
literal|23040
argument_list|,
name|FALSE
argument_list|)
expr_stmt|;
name|gimp_rectangle_tool_draw
argument_list|(
name|draw_tool
argument_list|)
expr_stmt|;
block|}
end_function

begin_function
specifier|static
name|void
DECL|function|gimp_ellipse_select_tool_select (GimpRectSelectTool * rect_tool,SelectOps operation,gint x,gint y,gint w,gint h)
name|gimp_ellipse_select_tool_select
parameter_list|(
name|GimpRectSelectTool
modifier|*
name|rect_tool
parameter_list|,
name|SelectOps
name|operation
parameter_list|,
name|gint
name|x
parameter_list|,
name|gint
name|y
parameter_list|,
name|gint
name|w
parameter_list|,
name|gint
name|h
parameter_list|)
block|{
name|GimpTool
modifier|*
name|tool
decl_stmt|;
name|GimpSelectionOptions
modifier|*
name|options
decl_stmt|;
name|tool
operator|=
name|GIMP_TOOL
argument_list|(
name|rect_tool
argument_list|)
expr_stmt|;
name|options
operator|=
name|GIMP_SELECTION_OPTIONS
argument_list|(
name|tool
operator|->
name|tool_info
operator|->
name|tool_options
argument_list|)
expr_stmt|;
name|gimp_channel_select_ellipse
argument_list|(
name|gimp_image_get_mask
argument_list|(
name|tool
operator|->
name|display
operator|->
name|image
argument_list|)
argument_list|,
name|x
argument_list|,
name|y
argument_list|,
name|w
argument_list|,
name|h
argument_list|,
name|operation
argument_list|,
name|options
operator|->
name|antialias
argument_list|,
name|options
operator|->
name|feather
argument_list|,
name|options
operator|->
name|feather_radius
argument_list|,
name|options
operator|->
name|feather_radius
argument_list|,
name|TRUE
argument_list|)
expr_stmt|;
block|}
end_function

end_unit

