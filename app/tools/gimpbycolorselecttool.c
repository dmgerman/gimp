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
file|"core/gimpdrawable.h"
end_include

begin_include
include|#
directive|include
file|"core/gimpimage.h"
end_include

begin_include
include|#
directive|include
file|"core/gimpimage-mask-select.h"
end_include

begin_include
include|#
directive|include
file|"core/gimpimage-projection.h"
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
name|void
name|gimp_by_color_select_tool_class_init
parameter_list|(
name|GimpByColorSelectToolClass
modifier|*
name|klass
parameter_list|)
function_decl|;
end_function_decl

begin_function_decl
specifier|static
name|void
name|gimp_by_color_select_tool_init
parameter_list|(
name|GimpByColorSelectTool
modifier|*
name|by_color_select
parameter_list|)
function_decl|;
end_function_decl

begin_function_decl
specifier|static
name|void
name|gimp_by_color_select_tool_button_press
parameter_list|(
name|GimpTool
modifier|*
name|tool
parameter_list|,
name|GimpCoords
modifier|*
name|coords
parameter_list|,
name|guint32
name|time
parameter_list|,
name|GdkModifierType
name|state
parameter_list|,
name|GimpDisplay
modifier|*
name|gdisp
parameter_list|)
function_decl|;
end_function_decl

begin_function_decl
specifier|static
name|void
name|gimp_by_color_select_tool_button_release
parameter_list|(
name|GimpTool
modifier|*
name|tool
parameter_list|,
name|GimpCoords
modifier|*
name|coords
parameter_list|,
name|guint32
name|time
parameter_list|,
name|GdkModifierType
name|state
parameter_list|,
name|GimpDisplay
modifier|*
name|gdisp
parameter_list|)
function_decl|;
end_function_decl

begin_function_decl
specifier|static
name|void
name|gimp_by_color_select_tool_oper_update
parameter_list|(
name|GimpTool
modifier|*
name|tool
parameter_list|,
name|GimpCoords
modifier|*
name|coords
parameter_list|,
name|GdkModifierType
name|state
parameter_list|,
name|GimpDisplay
modifier|*
name|gdisp
parameter_list|)
function_decl|;
end_function_decl

begin_function_decl
specifier|static
name|void
name|gimp_by_color_select_tool_cursor_update
parameter_list|(
name|GimpTool
modifier|*
name|tool
parameter_list|,
name|GimpCoords
modifier|*
name|coords
parameter_list|,
name|GdkModifierType
name|state
parameter_list|,
name|GimpDisplay
modifier|*
name|gdisp
parameter_list|)
function_decl|;
end_function_decl

begin_decl_stmt
DECL|variable|parent_class
specifier|static
name|GimpSelectionToolClass
modifier|*
name|parent_class
init|=
name|NULL
decl_stmt|;
end_decl_stmt

begin_comment
comment|/* public functions */
end_comment

begin_function
name|void
DECL|function|gimp_by_color_select_tool_register (GimpToolRegisterCallback callback,gpointer data)
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
name|FALSE
argument_list|,
literal|"gimp-by-color-select-tool"
argument_list|,
name|_
argument_list|(
literal|"Select By Color"
argument_list|)
argument_list|,
name|_
argument_list|(
literal|"Select regions by color"
argument_list|)
argument_list|,
name|N_
argument_list|(
literal|"/Tools/Selection Tools/By Color Select"
argument_list|)
argument_list|,
literal|"<shift>O"
argument_list|,
name|NULL
argument_list|,
literal|"tools/by_color_select.html"
argument_list|,
name|GIMP_STOCK_TOOL_BY_COLOR_SELECT
argument_list|,
name|data
argument_list|)
expr_stmt|;
block|}
end_function

begin_function
name|GType
DECL|function|gimp_by_color_select_tool_get_type (void)
name|gimp_by_color_select_tool_get_type
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
name|GimpByColorSelectToolClass
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
name|gimp_by_color_select_tool_class_init
block|,
name|NULL
block|,
comment|/* class_finalize */
name|NULL
block|,
comment|/* class_data     */
sizeof|sizeof
argument_list|(
name|GimpByColorSelectTool
argument_list|)
block|,
literal|0
block|,
comment|/* n_preallocs    */
operator|(
name|GInstanceInitFunc
operator|)
name|gimp_by_color_select_tool_init
block|,       }
decl_stmt|;
name|tool_type
operator|=
name|g_type_register_static
argument_list|(
name|GIMP_TYPE_SELECTION_TOOL
argument_list|,
literal|"GimpByColorSelectTool"
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
comment|/* private functions */
end_comment

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
name|GimpToolClass
modifier|*
name|tool_class
decl_stmt|;
name|tool_class
operator|=
name|GIMP_TOOL_CLASS
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
name|tool_class
operator|->
name|button_press
operator|=
name|gimp_by_color_select_tool_button_press
expr_stmt|;
name|tool_class
operator|->
name|button_release
operator|=
name|gimp_by_color_select_tool_button_release
expr_stmt|;
name|tool_class
operator|->
name|oper_update
operator|=
name|gimp_by_color_select_tool_oper_update
expr_stmt|;
name|tool_class
operator|->
name|cursor_update
operator|=
name|gimp_by_color_select_tool_cursor_update
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
decl_stmt|;
name|tool
operator|=
name|GIMP_TOOL
argument_list|(
name|by_color_select
argument_list|)
expr_stmt|;
name|gimp_tool_control_set_preserve
argument_list|(
name|tool
operator|->
name|control
argument_list|,
name|FALSE
argument_list|)
expr_stmt|;
name|gimp_tool_control_set_preserve
argument_list|(
name|tool
operator|->
name|control
argument_list|,
name|GIMP_RECT_SELECT_TOOL_CURSOR
argument_list|)
expr_stmt|;
name|by_color_select
operator|->
name|x
operator|=
literal|0
expr_stmt|;
name|by_color_select
operator|->
name|y
operator|=
literal|0
expr_stmt|;
block|}
end_function

begin_function
specifier|static
name|void
DECL|function|gimp_by_color_select_tool_button_press (GimpTool * tool,GimpCoords * coords,guint32 time,GdkModifierType state,GimpDisplay * gdisp)
name|gimp_by_color_select_tool_button_press
parameter_list|(
name|GimpTool
modifier|*
name|tool
parameter_list|,
name|GimpCoords
modifier|*
name|coords
parameter_list|,
name|guint32
name|time
parameter_list|,
name|GdkModifierType
name|state
parameter_list|,
name|GimpDisplay
modifier|*
name|gdisp
parameter_list|)
block|{
name|GimpByColorSelectTool
modifier|*
name|by_color_sel
decl_stmt|;
name|GimpSelectionOptions
modifier|*
name|options
decl_stmt|;
name|by_color_sel
operator|=
name|GIMP_BY_COLOR_SELECT_TOOL
argument_list|(
name|tool
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
name|tool
operator|->
name|drawable
operator|=
name|gimp_image_active_drawable
argument_list|(
name|gdisp
operator|->
name|gimage
argument_list|)
expr_stmt|;
name|gimp_tool_control_activate
argument_list|(
name|tool
operator|->
name|control
argument_list|)
expr_stmt|;
name|tool
operator|->
name|gdisp
operator|=
name|gdisp
expr_stmt|;
name|by_color_sel
operator|->
name|x
operator|=
name|coords
operator|->
name|x
expr_stmt|;
name|by_color_sel
operator|->
name|y
operator|=
name|coords
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
name|gimp_drawable_offsets
argument_list|(
name|gimp_image_active_drawable
argument_list|(
name|gdisp
operator|->
name|gimage
argument_list|)
argument_list|,
operator|&
name|off_x
argument_list|,
operator|&
name|off_y
argument_list|)
expr_stmt|;
name|by_color_sel
operator|->
name|x
operator|-=
name|off_x
expr_stmt|;
name|by_color_sel
operator|->
name|y
operator|-=
name|off_y
expr_stmt|;
block|}
block|}
end_function

begin_function
specifier|static
name|void
DECL|function|gimp_by_color_select_tool_button_release (GimpTool * tool,GimpCoords * coords,guint32 time,GdkModifierType state,GimpDisplay * gdisp)
name|gimp_by_color_select_tool_button_release
parameter_list|(
name|GimpTool
modifier|*
name|tool
parameter_list|,
name|GimpCoords
modifier|*
name|coords
parameter_list|,
name|guint32
name|time
parameter_list|,
name|GdkModifierType
name|state
parameter_list|,
name|GimpDisplay
modifier|*
name|gdisp
parameter_list|)
block|{
name|GimpByColorSelectTool
modifier|*
name|by_color_sel
decl_stmt|;
name|GimpSelectionTool
modifier|*
name|sel_tool
decl_stmt|;
name|GimpSelectionOptions
modifier|*
name|options
decl_stmt|;
name|GimpDrawable
modifier|*
name|drawable
decl_stmt|;
name|guchar
modifier|*
name|col
decl_stmt|;
name|GimpRGB
name|color
decl_stmt|;
name|by_color_sel
operator|=
name|GIMP_BY_COLOR_SELECT_TOOL
argument_list|(
name|tool
argument_list|)
expr_stmt|;
name|sel_tool
operator|=
name|GIMP_SELECTION_TOOL
argument_list|(
name|tool
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
name|drawable
operator|=
name|gimp_image_active_drawable
argument_list|(
name|gdisp
operator|->
name|gimage
argument_list|)
expr_stmt|;
name|gimp_tool_control_halt
argument_list|(
name|tool
operator|->
name|control
argument_list|)
expr_stmt|;
comment|/*  First take care of the case where the user "cancels" the action  */
if|if
condition|(
operator|!
operator|(
name|state
operator|&
name|GDK_BUTTON3_MASK
operator|)
condition|)
block|{
if|if
condition|(
name|by_color_sel
operator|->
name|x
operator|>=
literal|0
operator|&&
name|by_color_sel
operator|->
name|y
operator|>=
literal|0
operator|&&
name|by_color_sel
operator|->
name|x
operator|<
name|gimp_drawable_width
argument_list|(
name|drawable
argument_list|)
operator|&&
name|by_color_sel
operator|->
name|y
operator|<
name|gimp_drawable_height
argument_list|(
name|drawable
argument_list|)
condition|)
block|{
comment|/*  Get the start color  */
if|if
condition|(
name|options
operator|->
name|sample_merged
condition|)
block|{
if|if
condition|(
operator|!
operator|(
name|col
operator|=
name|gimp_image_projection_get_color_at
argument_list|(
name|gdisp
operator|->
name|gimage
argument_list|,
name|by_color_sel
operator|->
name|x
argument_list|,
name|by_color_sel
operator|->
name|y
argument_list|)
operator|)
condition|)
return|return;
block|}
else|else
block|{
if|if
condition|(
operator|!
operator|(
name|col
operator|=
name|gimp_drawable_get_color_at
argument_list|(
name|drawable
argument_list|,
name|by_color_sel
operator|->
name|x
argument_list|,
name|by_color_sel
operator|->
name|y
argument_list|)
operator|)
condition|)
return|return;
block|}
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
name|gimp_image_mask_select_by_color
argument_list|(
name|gdisp
operator|->
name|gimage
argument_list|,
name|drawable
argument_list|,
name|options
operator|->
name|sample_merged
argument_list|,
operator|&
name|color
argument_list|,
name|options
operator|->
name|threshold
argument_list|,
name|options
operator|->
name|select_transparent
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
name|gimp_image_flush
argument_list|(
name|gdisp
operator|->
name|gimage
argument_list|)
expr_stmt|;
block|}
block|}
block|}
end_function

begin_function
specifier|static
name|void
DECL|function|gimp_by_color_select_tool_oper_update (GimpTool * tool,GimpCoords * coords,GdkModifierType state,GimpDisplay * gdisp)
name|gimp_by_color_select_tool_oper_update
parameter_list|(
name|GimpTool
modifier|*
name|tool
parameter_list|,
name|GimpCoords
modifier|*
name|coords
parameter_list|,
name|GdkModifierType
name|state
parameter_list|,
name|GimpDisplay
modifier|*
name|gdisp
parameter_list|)
block|{
name|GimpSelectionTool
modifier|*
name|sel_tool
decl_stmt|;
name|GimpSelectionOptions
modifier|*
name|options
decl_stmt|;
if|if
condition|(
name|gimp_tool_control_is_active
argument_list|(
name|tool
operator|->
name|control
argument_list|)
condition|)
return|return;
name|sel_tool
operator|=
name|GIMP_SELECTION_TOOL
argument_list|(
name|tool
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
if|if
condition|(
operator|(
name|state
operator|&
name|GDK_CONTROL_MASK
operator|)
operator|&&
operator|(
name|state
operator|&
name|GDK_SHIFT_MASK
operator|)
condition|)
block|{
name|sel_tool
operator|->
name|op
operator|=
name|SELECTION_INTERSECT
expr_stmt|;
comment|/* intersect with selection */
block|}
elseif|else
if|if
condition|(
name|state
operator|&
name|GDK_SHIFT_MASK
condition|)
block|{
name|sel_tool
operator|->
name|op
operator|=
name|SELECTION_ADD
expr_stmt|;
comment|/* add to the selection */
block|}
elseif|else
if|if
condition|(
name|state
operator|&
name|GDK_CONTROL_MASK
condition|)
block|{
name|sel_tool
operator|->
name|op
operator|=
name|SELECTION_SUBTRACT
expr_stmt|;
comment|/* subtract from the selection */
block|}
else|else
block|{
name|sel_tool
operator|->
name|op
operator|=
name|options
operator|->
name|operation
expr_stmt|;
block|}
block|}
end_function

begin_function
specifier|static
name|void
DECL|function|gimp_by_color_select_tool_cursor_update (GimpTool * tool,GimpCoords * coords,GdkModifierType state,GimpDisplay * gdisp)
name|gimp_by_color_select_tool_cursor_update
parameter_list|(
name|GimpTool
modifier|*
name|tool
parameter_list|,
name|GimpCoords
modifier|*
name|coords
parameter_list|,
name|GdkModifierType
name|state
parameter_list|,
name|GimpDisplay
modifier|*
name|gdisp
parameter_list|)
block|{
name|GimpByColorSelectTool
modifier|*
name|by_col_sel
decl_stmt|;
name|GimpSelectionOptions
modifier|*
name|options
decl_stmt|;
name|GimpLayer
modifier|*
name|layer
decl_stmt|;
name|by_col_sel
operator|=
name|GIMP_BY_COLOR_SELECT_TOOL
argument_list|(
name|tool
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
name|layer
operator|=
name|gimp_image_pick_correlate_layer
argument_list|(
name|gdisp
operator|->
name|gimage
argument_list|,
name|coords
operator|->
name|x
argument_list|,
name|coords
operator|->
name|y
argument_list|)
expr_stmt|;
if|if
condition|(
operator|!
name|options
operator|->
name|sample_merged
operator|&&
name|layer
operator|&&
name|layer
operator|!=
name|gdisp
operator|->
name|gimage
operator|->
name|active_layer
condition|)
block|{
name|gimp_tool_control_set_cursor
argument_list|(
name|tool
operator|->
name|control
argument_list|,
name|GIMP_BAD_CURSOR
argument_list|)
expr_stmt|;
block|}
else|else
block|{
name|gimp_tool_control_set_cursor
argument_list|(
name|tool
operator|->
name|control
argument_list|,
name|GIMP_MOUSE_CURSOR
argument_list|)
expr_stmt|;
block|}
name|GIMP_TOOL_CLASS
argument_list|(
name|parent_class
argument_list|)
operator|->
name|cursor_update
argument_list|(
name|tool
argument_list|,
name|coords
argument_list|,
name|state
argument_list|,
name|gdisp
argument_list|)
expr_stmt|;
block|}
end_function

end_unit

