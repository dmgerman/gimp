begin_unit|revision:0.9.5;language:C;cregit-version:0.0.1
begin_comment
comment|/* The GIMP -- an image manipulation program  * Copyright (C) 1995 Spencer Kimball and Peter Mattis  *  * gimpbycolorselecttool.c  *  * This program is free software; you can redistribute it and/or modify  * it under the terms of the GNU General Public License as published by  * the Free Software Foundation; either version 2 of the License, or  * (at your option) any later version.  *  * This program is distributed in the hope that it will be useful,  * but WITHOUT ANY WARRANTY; without even the implied warranty of  * MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the  * GNU General Public License for more details.  *  * You should have received a copy of the GNU General Public License  * along with this program; if not, write to the Free Software  * Foundation, Inc., 59 Temple Place - Suite 330, Boston, MA 02111-1307, USA.  */
end_comment

begin_include
include|#
directive|include
file|"config.h"
end_include

begin_include
include|#
directive|include
file|<gtk/gtk.h>
end_include

begin_include
include|#
directive|include
file|"libgimpcolor/gimpcolor.h"
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
file|"core/gimpimage.h"
end_include

begin_include
include|#
directive|include
file|"core/gimpimage-contiguous-region.h"
end_include

begin_include
include|#
directive|include
file|"core/gimpitem.h"
end_include

begin_include
include|#
directive|include
file|"core/gimppickable.h"
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
file|"gimpbycolorselecttool.h"
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
name|GimpChannel
modifier|*
name|gimp_by_color_select_tool_get_mask
parameter_list|(
name|GimpRegionSelectTool
modifier|*
name|region_select
parameter_list|,
name|GimpDisplay
modifier|*
name|display
parameter_list|)
function_decl|;
end_function_decl

begin_macro
DECL|function|G_DEFINE_TYPE (GimpByColorSelectTool,gimp_by_color_select_tool,GIMP_TYPE_REGION_SELECT_TOOL)
name|G_DEFINE_TYPE
argument_list|(
argument|GimpByColorSelectTool
argument_list|,
argument|gimp_by_color_select_tool
argument_list|,
argument|GIMP_TYPE_REGION_SELECT_TOOL
argument_list|)
end_macro

begin_define
DECL|macro|parent_class
define|#
directive|define
name|parent_class
value|gimp_by_color_select_tool_parent_class
end_define

begin_function
name|void
name|gimp_by_color_select_tool_register
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
name|GIMP_TYPE_BY_COLOR_SELECT_TOOL
argument_list|,
name|GIMP_TYPE_SELECTION_OPTIONS
argument_list|,
name|gimp_selection_options_gui
argument_list|,
literal|0
argument_list|,
literal|"gimp-by-color-select-tool"
argument_list|,
name|_
argument_list|(
literal|"Select by Color"
argument_list|)
argument_list|,
name|_
argument_list|(
literal|"Select regions by color"
argument_list|)
argument_list|,
name|N_
argument_list|(
literal|"_By Color Select"
argument_list|)
argument_list|,
literal|"<shift>O"
argument_list|,
name|NULL
argument_list|,
name|GIMP_HELP_TOOL_BY_COLOR_SELECT
argument_list|,
name|GIMP_STOCK_TOOL_BY_COLOR_SELECT
argument_list|,
name|data
argument_list|)
expr_stmt|;
block|}
end_function

begin_function
specifier|static
name|void
DECL|function|gimp_by_color_select_tool_class_init (GimpByColorSelectToolClass * klass)
name|gimp_by_color_select_tool_class_init
parameter_list|(
name|GimpByColorSelectToolClass
modifier|*
name|klass
parameter_list|)
block|{
name|GimpRegionSelectToolClass
modifier|*
name|region_class
decl_stmt|;
name|region_class
operator|=
name|GIMP_REGION_SELECT_TOOL_CLASS
argument_list|(
name|klass
argument_list|)
expr_stmt|;
name|region_class
operator|->
name|undo_desc
operator|=
name|Q_
argument_list|(
literal|"command|Select by Color"
argument_list|)
expr_stmt|;
name|region_class
operator|->
name|get_mask
operator|=
name|gimp_by_color_select_tool_get_mask
expr_stmt|;
block|}
end_function

begin_function
specifier|static
name|void
DECL|function|gimp_by_color_select_tool_init (GimpByColorSelectTool * by_color_select)
name|gimp_by_color_select_tool_init
parameter_list|(
name|GimpByColorSelectTool
modifier|*
name|by_color_select
parameter_list|)
block|{
name|GimpTool
modifier|*
name|tool
init|=
name|GIMP_TOOL
argument_list|(
name|by_color_select
argument_list|)
decl_stmt|;
name|gimp_tool_control_set_tool_cursor
argument_list|(
name|tool
operator|->
name|control
argument_list|,
name|GIMP_TOOL_CURSOR_HAND
argument_list|)
expr_stmt|;
block|}
end_function

begin_function
specifier|static
name|GimpChannel
modifier|*
DECL|function|gimp_by_color_select_tool_get_mask (GimpRegionSelectTool * region_select,GimpDisplay * display)
name|gimp_by_color_select_tool_get_mask
parameter_list|(
name|GimpRegionSelectTool
modifier|*
name|region_select
parameter_list|,
name|GimpDisplay
modifier|*
name|display
parameter_list|)
block|{
name|GimpTool
modifier|*
name|tool
init|=
name|GIMP_TOOL
argument_list|(
name|region_select
argument_list|)
decl_stmt|;
name|GimpSelectionOptions
modifier|*
name|options
init|=
name|GIMP_SELECTION_TOOL_GET_OPTIONS
argument_list|(
name|tool
argument_list|)
decl_stmt|;
name|GimpDrawable
modifier|*
name|drawable
decl_stmt|;
name|GimpPickable
modifier|*
name|pickable
decl_stmt|;
name|guchar
modifier|*
name|col
decl_stmt|;
name|gint
name|x
decl_stmt|,
name|y
decl_stmt|;
name|drawable
operator|=
name|gimp_image_active_drawable
argument_list|(
name|display
operator|->
name|image
argument_list|)
expr_stmt|;
name|x
operator|=
name|region_select
operator|->
name|x
expr_stmt|;
name|y
operator|=
name|region_select
operator|->
name|y
expr_stmt|;
if|if
condition|(
operator|!
name|options
operator|->
name|sample_merged
condition|)
block|{
name|gint
name|off_x
decl_stmt|,
name|off_y
decl_stmt|;
name|gimp_item_offsets
argument_list|(
name|GIMP_ITEM
argument_list|(
name|drawable
argument_list|)
argument_list|,
operator|&
name|off_x
argument_list|,
operator|&
name|off_y
argument_list|)
expr_stmt|;
name|x
operator|-=
name|off_x
expr_stmt|;
name|y
operator|-=
name|off_y
expr_stmt|;
name|pickable
operator|=
name|GIMP_PICKABLE
argument_list|(
name|drawable
argument_list|)
expr_stmt|;
block|}
else|else
block|{
name|pickable
operator|=
name|GIMP_PICKABLE
argument_list|(
name|display
operator|->
name|image
operator|->
name|projection
argument_list|)
expr_stmt|;
block|}
name|gimp_pickable_flush
argument_list|(
name|pickable
argument_list|)
expr_stmt|;
name|col
operator|=
name|gimp_pickable_get_color_at
argument_list|(
name|pickable
argument_list|,
name|x
argument_list|,
name|y
argument_list|)
expr_stmt|;
if|if
condition|(
name|col
condition|)
block|{
name|GimpRGB
name|color
decl_stmt|;
name|gimp_rgba_set_uchar
argument_list|(
operator|&
name|color
argument_list|,
name|col
index|[
literal|0
index|]
argument_list|,
name|col
index|[
literal|1
index|]
argument_list|,
name|col
index|[
literal|2
index|]
argument_list|,
name|col
index|[
literal|3
index|]
argument_list|)
expr_stmt|;
name|g_free
argument_list|(
name|col
argument_list|)
expr_stmt|;
return|return
name|gimp_image_contiguous_region_by_color
argument_list|(
name|display
operator|->
name|image
argument_list|,
name|drawable
argument_list|,
name|options
operator|->
name|sample_merged
argument_list|,
name|options
operator|->
name|antialias
argument_list|,
name|options
operator|->
name|threshold
argument_list|,
name|options
operator|->
name|select_transparent
argument_list|,
name|options
operator|->
name|select_criterion
argument_list|,
operator|&
name|color
argument_list|)
return|;
block|}
return|return
name|NULL
return|;
block|}
end_function

end_unit

