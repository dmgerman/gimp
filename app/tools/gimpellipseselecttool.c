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
file|"core/gimpimage.h"
end_include

begin_include
include|#
directive|include
file|"core/gimpimage-mask.h"
end_include

begin_include
include|#
directive|include
file|"core/gimpimage-mask-select.h"
end_include

begin_include
include|#
directive|include
file|"core/gimptoolinfo.h"
end_include

begin_include
include|#
directive|include
file|"display/gimpdisplay.h"
end_include

begin_include
include|#
directive|include
file|"gimpellipseselecttool.h"
end_include

begin_include
include|#
directive|include
file|"gimpselectionoptions.h"
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
name|gimp_ellipse_select_tool_class_init
parameter_list|(
name|GimpEllipseSelectToolClass
modifier|*
name|klass
parameter_list|)
function_decl|;
end_function_decl

begin_function_decl
specifier|static
name|void
name|gimp_ellipse_select_tool_init
parameter_list|(
name|GimpEllipseSelectTool
modifier|*
name|ellipse_select
parameter_list|)
function_decl|;
end_function_decl

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
name|gimp_ellipse_select_tool_rect_select
parameter_list|(
name|GimpRectSelectTool
modifier|*
name|rect_tool
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

begin_decl_stmt
DECL|variable|parent_class
specifier|static
name|GimpRectSelectToolClass
modifier|*
name|parent_class
init|=
name|NULL
decl_stmt|;
end_decl_stmt

begin_comment
comment|/*  public functions  */
end_comment

begin_function
name|void
DECL|function|gimp_ellipse_select_tool_register (GimpToolRegisterCallback callback,gpointer data)
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
name|GIMP_TYPE_SELECTION_OPTIONS
argument_list|,
name|gimp_selection_options_gui
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
literal|"/Tools/Selection Tools/_Ellipse Select"
argument_list|)
argument_list|,
literal|"E"
argument_list|,
name|NULL
argument_list|,
literal|"tools/ellipse_select.html"
argument_list|,
name|GIMP_STOCK_TOOL_ELLIPSE_SELECT
argument_list|,
name|data
argument_list|)
expr_stmt|;
block|}
end_function

begin_function
name|GType
DECL|function|gimp_ellipse_select_tool_get_type (void)
name|gimp_ellipse_select_tool_get_type
parameter_list|(
name|void
parameter_list|)
block|{
specifier|static
name|GType
name|tool_type
init|=
literal|0
decl_stmt|;
if|if
condition|(
operator|!
name|tool_type
condition|)
block|{
specifier|static
specifier|const
name|GTypeInfo
name|tool_info
init|=
block|{
sizeof|sizeof
argument_list|(
name|GimpEllipseSelectToolClass
argument_list|)
block|,
operator|(
name|GBaseInitFunc
operator|)
name|NULL
block|,
operator|(
name|GBaseFinalizeFunc
operator|)
name|NULL
block|,
operator|(
name|GClassInitFunc
operator|)
name|gimp_ellipse_select_tool_class_init
block|,
name|NULL
block|,
comment|/* class_finalize */
name|NULL
block|,
comment|/* class_data     */
sizeof|sizeof
argument_list|(
name|GimpEllipseSelectTool
argument_list|)
block|,
literal|0
block|,
comment|/* n_preallocs    */
operator|(
name|GInstanceInitFunc
operator|)
name|gimp_ellipse_select_tool_init
block|,       }
decl_stmt|;
name|tool_type
operator|=
name|g_type_register_static
argument_list|(
name|GIMP_TYPE_RECT_SELECT_TOOL
argument_list|,
literal|"GimpEllipseSelectTool"
argument_list|,
operator|&
name|tool_info
argument_list|,
literal|0
argument_list|)
expr_stmt|;
block|}
return|return
name|tool_type
return|;
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
name|parent_class
operator|=
name|g_type_class_peek_parent
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
name|rect_select
operator|=
name|gimp_ellipse_select_tool_rect_select
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
decl_stmt|;
name|tool
operator|=
name|GIMP_TOOL
argument_list|(
name|ellipse_select
argument_list|)
expr_stmt|;
name|gimp_tool_control_set_tool_cursor
argument_list|(
name|tool
operator|->
name|control
argument_list|,
name|GIMP_ELLIPSE_SELECT_TOOL_CURSOR
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
decl_stmt|;
name|rect_sel
operator|=
name|GIMP_RECT_SELECT_TOOL
argument_list|(
name|draw_tool
argument_list|)
expr_stmt|;
name|gimp_draw_tool_draw_arc
argument_list|(
name|draw_tool
argument_list|,
name|FALSE
argument_list|,
name|rect_sel
operator|->
name|x
argument_list|,
name|rect_sel
operator|->
name|y
argument_list|,
name|rect_sel
operator|->
name|w
argument_list|,
name|rect_sel
operator|->
name|h
argument_list|,
literal|0
argument_list|,
literal|23040
argument_list|,
name|FALSE
argument_list|)
expr_stmt|;
block|}
end_function

begin_function
specifier|static
name|void
DECL|function|gimp_ellipse_select_tool_rect_select (GimpRectSelectTool * rect_tool,gint x,gint y,gint w,gint h)
name|gimp_ellipse_select_tool_rect_select
parameter_list|(
name|GimpRectSelectTool
modifier|*
name|rect_tool
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
name|GimpSelectionTool
modifier|*
name|sel_tool
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
name|sel_tool
operator|=
name|GIMP_SELECTION_TOOL
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
name|gimp_image_mask_select_ellipse
argument_list|(
name|tool
operator|->
name|gdisp
operator|->
name|gimage
argument_list|,
name|x
argument_list|,
name|y
argument_list|,
name|w
argument_list|,
name|h
argument_list|,
name|sel_tool
operator|->
name|op
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
argument_list|)
expr_stmt|;
block|}
end_function

end_unit

