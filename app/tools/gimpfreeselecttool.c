begin_unit|revision:0.9.5;language:C;cregit-version:0.0.1
begin_comment
comment|/* GIMP - The GNU Image Manipulation Program  * Copyright (C) 1995 Spencer Kimball and Peter Mattis  *  * This program is free software; you can redistribute it and/or modify  * it under the terms of the GNU General Public License as published by  * the Free Software Foundation; either version 2 of the License, or  * (at your option) any later version.  *  * This program is distributed in the hope that it will be useful,  * but WITHOUT ANY WARRANTY; without even the implied warranty of  * MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the  * GNU General Public License for more details.  *  * You should have received a copy of the GNU General Public License  * along with this program; if not, write to the Free Software  * Foundation, Inc., 59 Temple Place - Suite 330, Boston, MA 02111-1307, USA.  */
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
file|"core/gimplayer-floating-sel.h"
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
file|"gimpfreeselecttool.h"
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

begin_define
DECL|macro|DEFAULT_MAX_INC
define|#
directive|define
name|DEFAULT_MAX_INC
value|1024
end_define

begin_function_decl
specifier|static
name|void
name|gimp_free_select_tool_finalize
parameter_list|(
name|GObject
modifier|*
name|object
parameter_list|)
function_decl|;
end_function_decl

begin_function_decl
specifier|static
name|void
name|gimp_free_select_tool_control
parameter_list|(
name|GimpTool
modifier|*
name|tool
parameter_list|,
name|GimpToolAction
name|action
parameter_list|,
name|GimpDisplay
modifier|*
name|display
parameter_list|)
function_decl|;
end_function_decl

begin_function_decl
specifier|static
name|void
name|gimp_free_select_tool_button_press
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
name|display
parameter_list|)
function_decl|;
end_function_decl

begin_function_decl
specifier|static
name|void
name|gimp_free_select_tool_button_release
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
name|GimpButtonReleaseType
name|release_type
parameter_list|,
name|GimpDisplay
modifier|*
name|display
parameter_list|)
function_decl|;
end_function_decl

begin_function_decl
specifier|static
name|void
name|gimp_free_select_tool_motion
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
name|display
parameter_list|)
function_decl|;
end_function_decl

begin_function_decl
specifier|static
name|void
name|gimp_free_select_tool_draw
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
name|gimp_free_select_tool_real_select
parameter_list|(
name|GimpFreeSelectTool
modifier|*
name|free_sel
parameter_list|,
name|GimpDisplay
modifier|*
name|display
parameter_list|)
function_decl|;
end_function_decl

begin_function_decl
specifier|static
name|void
name|gimp_free_select_tool_add_point
parameter_list|(
name|GimpFreeSelectTool
modifier|*
name|free_sel
parameter_list|,
name|gdouble
name|x
parameter_list|,
name|gdouble
name|y
parameter_list|)
function_decl|;
end_function_decl

begin_function_decl
specifier|static
name|void
name|gimp_free_select_tool_move_points
parameter_list|(
name|GimpFreeSelectTool
modifier|*
name|free_sel
parameter_list|,
name|gdouble
name|dx
parameter_list|,
name|gdouble
name|dy
parameter_list|)
function_decl|;
end_function_decl

begin_expr_stmt
name|G_DEFINE_TYPE
argument_list|(
name|GimpFreeSelectTool
argument_list|,
name|gimp_free_select_tool
argument_list|,
name|GIMP_TYPE_SELECTION_TOOL
argument_list|)
expr_stmt|;
end_expr_stmt

begin_define
DECL|macro|parent_class
define|#
directive|define
name|parent_class
value|gimp_free_select_tool_parent_class
end_define

begin_function
name|void
DECL|function|gimp_free_select_tool_register (GimpToolRegisterCallback callback,gpointer data)
name|gimp_free_select_tool_register
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
name|GIMP_TYPE_FREE_SELECT_TOOL
argument_list|,
name|GIMP_TYPE_SELECTION_OPTIONS
argument_list|,
name|gimp_selection_options_gui
argument_list|,
literal|0
argument_list|,
literal|"gimp-free-select-tool"
argument_list|,
name|_
argument_list|(
literal|"Free Select"
argument_list|)
argument_list|,
name|_
argument_list|(
literal|"Free Select Tool: Select a hand-drawn region"
argument_list|)
argument_list|,
name|N_
argument_list|(
literal|"_Free Select"
argument_list|)
argument_list|,
literal|"F"
argument_list|,
name|NULL
argument_list|,
name|GIMP_HELP_TOOL_FREE_SELECT
argument_list|,
name|GIMP_STOCK_TOOL_FREE_SELECT
argument_list|,
name|data
argument_list|)
expr_stmt|;
block|}
end_function

begin_function
specifier|static
name|void
DECL|function|gimp_free_select_tool_class_init (GimpFreeSelectToolClass * klass)
name|gimp_free_select_tool_class_init
parameter_list|(
name|GimpFreeSelectToolClass
modifier|*
name|klass
parameter_list|)
block|{
name|GObjectClass
modifier|*
name|object_class
init|=
name|G_OBJECT_CLASS
argument_list|(
name|klass
argument_list|)
decl_stmt|;
name|GimpToolClass
modifier|*
name|tool_class
init|=
name|GIMP_TOOL_CLASS
argument_list|(
name|klass
argument_list|)
decl_stmt|;
name|GimpDrawToolClass
modifier|*
name|draw_tool_class
init|=
name|GIMP_DRAW_TOOL_CLASS
argument_list|(
name|klass
argument_list|)
decl_stmt|;
name|object_class
operator|->
name|finalize
operator|=
name|gimp_free_select_tool_finalize
expr_stmt|;
name|tool_class
operator|->
name|control
operator|=
name|gimp_free_select_tool_control
expr_stmt|;
name|tool_class
operator|->
name|button_press
operator|=
name|gimp_free_select_tool_button_press
expr_stmt|;
name|tool_class
operator|->
name|button_release
operator|=
name|gimp_free_select_tool_button_release
expr_stmt|;
name|tool_class
operator|->
name|motion
operator|=
name|gimp_free_select_tool_motion
expr_stmt|;
name|draw_tool_class
operator|->
name|draw
operator|=
name|gimp_free_select_tool_draw
expr_stmt|;
name|klass
operator|->
name|select
operator|=
name|gimp_free_select_tool_real_select
expr_stmt|;
block|}
end_function

begin_function
specifier|static
name|void
DECL|function|gimp_free_select_tool_init (GimpFreeSelectTool * free_select)
name|gimp_free_select_tool_init
parameter_list|(
name|GimpFreeSelectTool
modifier|*
name|free_select
parameter_list|)
block|{
name|GimpTool
modifier|*
name|tool
init|=
name|GIMP_TOOL
argument_list|(
name|free_select
argument_list|)
decl_stmt|;
name|gimp_tool_control_set_scroll_lock
argument_list|(
name|tool
operator|->
name|control
argument_list|,
name|FALSE
argument_list|)
expr_stmt|;
name|gimp_tool_control_set_tool_cursor
argument_list|(
name|tool
operator|->
name|control
argument_list|,
name|GIMP_TOOL_CURSOR_FREE_SELECT
argument_list|)
expr_stmt|;
name|free_select
operator|->
name|points
operator|=
name|NULL
expr_stmt|;
name|free_select
operator|->
name|num_points
operator|=
literal|0
expr_stmt|;
name|free_select
operator|->
name|max_segs
operator|=
literal|0
expr_stmt|;
block|}
end_function

begin_function
specifier|static
name|void
DECL|function|gimp_free_select_tool_finalize (GObject * object)
name|gimp_free_select_tool_finalize
parameter_list|(
name|GObject
modifier|*
name|object
parameter_list|)
block|{
name|GimpFreeSelectTool
modifier|*
name|free_sel
init|=
name|GIMP_FREE_SELECT_TOOL
argument_list|(
name|object
argument_list|)
decl_stmt|;
if|if
condition|(
name|free_sel
operator|->
name|points
condition|)
block|{
name|g_free
argument_list|(
name|free_sel
operator|->
name|points
argument_list|)
expr_stmt|;
name|free_sel
operator|->
name|points
operator|=
name|NULL
expr_stmt|;
block|}
name|G_OBJECT_CLASS
argument_list|(
name|parent_class
argument_list|)
operator|->
name|finalize
argument_list|(
name|object
argument_list|)
expr_stmt|;
block|}
end_function

begin_function
specifier|static
name|void
DECL|function|gimp_free_select_tool_control (GimpTool * tool,GimpToolAction action,GimpDisplay * display)
name|gimp_free_select_tool_control
parameter_list|(
name|GimpTool
modifier|*
name|tool
parameter_list|,
name|GimpToolAction
name|action
parameter_list|,
name|GimpDisplay
modifier|*
name|display
parameter_list|)
block|{
switch|switch
condition|(
name|action
condition|)
block|{
case|case
name|GIMP_TOOL_ACTION_PAUSE
case|:
case|case
name|GIMP_TOOL_ACTION_RESUME
case|:
break|break;
case|case
name|GIMP_TOOL_ACTION_HALT
case|:
name|GIMP_FREE_SELECT_TOOL
argument_list|(
name|tool
argument_list|)
operator|->
name|num_points
operator|=
literal|0
expr_stmt|;
break|break;
block|}
name|GIMP_TOOL_CLASS
argument_list|(
name|parent_class
argument_list|)
operator|->
name|control
argument_list|(
name|tool
argument_list|,
name|action
argument_list|,
name|display
argument_list|)
expr_stmt|;
block|}
end_function

begin_function
specifier|static
name|void
DECL|function|gimp_free_select_tool_button_press (GimpTool * tool,GimpCoords * coords,guint32 time,GdkModifierType state,GimpDisplay * display)
name|gimp_free_select_tool_button_press
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
name|display
parameter_list|)
block|{
name|GimpFreeSelectTool
modifier|*
name|free_sel
init|=
name|GIMP_FREE_SELECT_TOOL
argument_list|(
name|tool
argument_list|)
decl_stmt|;
name|gimp_tool_control_activate
argument_list|(
name|tool
operator|->
name|control
argument_list|)
expr_stmt|;
name|tool
operator|->
name|display
operator|=
name|display
expr_stmt|;
if|if
condition|(
name|gimp_selection_tool_start_edit
argument_list|(
name|GIMP_SELECTION_TOOL
argument_list|(
name|free_sel
argument_list|)
argument_list|,
name|coords
argument_list|)
condition|)
return|return;
name|free_sel
operator|->
name|last_coords
operator|=
operator|*
name|coords
expr_stmt|;
name|free_sel
operator|->
name|num_points
operator|=
literal|0
expr_stmt|;
name|gimp_free_select_tool_add_point
argument_list|(
name|free_sel
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
name|gimp_draw_tool_start
argument_list|(
name|GIMP_DRAW_TOOL
argument_list|(
name|tool
argument_list|)
argument_list|,
name|display
argument_list|)
expr_stmt|;
block|}
end_function

begin_function
specifier|static
name|void
DECL|function|gimp_free_select_tool_button_release (GimpTool * tool,GimpCoords * coords,guint32 time,GdkModifierType state,GimpButtonReleaseType release_type,GimpDisplay * display)
name|gimp_free_select_tool_button_release
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
name|GimpButtonReleaseType
name|release_type
parameter_list|,
name|GimpDisplay
modifier|*
name|display
parameter_list|)
block|{
name|GimpFreeSelectTool
modifier|*
name|free_sel
init|=
name|GIMP_FREE_SELECT_TOOL
argument_list|(
name|tool
argument_list|)
decl_stmt|;
name|gimp_draw_tool_stop
argument_list|(
name|GIMP_DRAW_TOOL
argument_list|(
name|tool
argument_list|)
argument_list|)
expr_stmt|;
name|gimp_tool_control_halt
argument_list|(
name|tool
operator|->
name|control
argument_list|)
expr_stmt|;
if|if
condition|(
name|release_type
operator|==
name|GIMP_BUTTON_RELEASE_CANCEL
condition|)
return|return;
if|if
condition|(
name|free_sel
operator|->
name|num_points
operator|==
literal|1
condition|)
block|{
if|if
condition|(
name|gimp_image_floating_sel
argument_list|(
name|display
operator|->
name|image
argument_list|)
condition|)
block|{
comment|/*  If there is a floating selection, anchor it  */
name|floating_sel_anchor
argument_list|(
name|gimp_image_floating_sel
argument_list|(
name|display
operator|->
name|image
argument_list|)
argument_list|)
expr_stmt|;
block|}
else|else
block|{
comment|/*  Otherwise, clear the selection mask  */
name|gimp_channel_clear
argument_list|(
name|gimp_image_get_mask
argument_list|(
name|display
operator|->
name|image
argument_list|)
argument_list|,
name|NULL
argument_list|,
name|TRUE
argument_list|)
expr_stmt|;
block|}
block|}
else|else
block|{
name|GIMP_FREE_SELECT_TOOL_GET_CLASS
argument_list|(
name|free_sel
argument_list|)
operator|->
name|select
argument_list|(
name|free_sel
argument_list|,
name|display
argument_list|)
expr_stmt|;
block|}
name|gimp_image_flush
argument_list|(
name|display
operator|->
name|image
argument_list|)
expr_stmt|;
block|}
end_function

begin_function
specifier|static
name|void
DECL|function|gimp_free_select_tool_motion (GimpTool * tool,GimpCoords * coords,guint32 time,GdkModifierType state,GimpDisplay * display)
name|gimp_free_select_tool_motion
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
name|display
parameter_list|)
block|{
name|GimpFreeSelectTool
modifier|*
name|free_sel
init|=
name|GIMP_FREE_SELECT_TOOL
argument_list|(
name|tool
argument_list|)
decl_stmt|;
name|GimpSelectionTool
modifier|*
name|sel_tool
init|=
name|GIMP_SELECTION_TOOL
argument_list|(
name|tool
argument_list|)
decl_stmt|;
if|if
condition|(
name|sel_tool
operator|->
name|function
operator|==
name|SELECTION_ANCHOR
condition|)
block|{
name|sel_tool
operator|->
name|function
operator|=
name|SELECTION_SELECT
expr_stmt|;
name|gimp_tool_cursor_update
argument_list|(
name|tool
argument_list|,
name|coords
argument_list|,
name|state
argument_list|,
name|display
argument_list|)
expr_stmt|;
block|}
if|if
condition|(
name|state
operator|&
name|GDK_MOD1_MASK
condition|)
block|{
name|gimp_draw_tool_pause
argument_list|(
name|GIMP_DRAW_TOOL
argument_list|(
name|tool
argument_list|)
argument_list|)
expr_stmt|;
name|gimp_free_select_tool_move_points
argument_list|(
name|free_sel
argument_list|,
name|coords
operator|->
name|x
operator|-
name|free_sel
operator|->
name|last_coords
operator|.
name|x
argument_list|,
name|coords
operator|->
name|y
operator|-
name|free_sel
operator|->
name|last_coords
operator|.
name|y
argument_list|)
expr_stmt|;
name|gimp_draw_tool_resume
argument_list|(
name|GIMP_DRAW_TOOL
argument_list|(
name|tool
argument_list|)
argument_list|)
expr_stmt|;
block|}
else|else
block|{
name|gimp_free_select_tool_add_point
argument_list|(
name|free_sel
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
name|gimp_draw_tool_draw_line
argument_list|(
name|GIMP_DRAW_TOOL
argument_list|(
name|tool
argument_list|)
argument_list|,
name|free_sel
operator|->
name|points
index|[
name|free_sel
operator|->
name|num_points
operator|-
literal|2
index|]
operator|.
name|x
argument_list|,
name|free_sel
operator|->
name|points
index|[
name|free_sel
operator|->
name|num_points
operator|-
literal|2
index|]
operator|.
name|y
argument_list|,
name|free_sel
operator|->
name|points
index|[
name|free_sel
operator|->
name|num_points
operator|-
literal|1
index|]
operator|.
name|x
argument_list|,
name|free_sel
operator|->
name|points
index|[
name|free_sel
operator|->
name|num_points
operator|-
literal|1
index|]
operator|.
name|y
argument_list|,
name|FALSE
argument_list|)
expr_stmt|;
block|}
name|free_sel
operator|->
name|last_coords
operator|=
operator|*
name|coords
expr_stmt|;
block|}
end_function

begin_function
specifier|static
name|void
DECL|function|gimp_free_select_tool_draw (GimpDrawTool * draw_tool)
name|gimp_free_select_tool_draw
parameter_list|(
name|GimpDrawTool
modifier|*
name|draw_tool
parameter_list|)
block|{
name|GimpFreeSelectTool
modifier|*
name|free_sel
init|=
name|GIMP_FREE_SELECT_TOOL
argument_list|(
name|draw_tool
argument_list|)
decl_stmt|;
name|gimp_draw_tool_draw_lines
argument_list|(
name|draw_tool
argument_list|,
operator|(
specifier|const
name|gdouble
operator|*
operator|)
name|free_sel
operator|->
name|points
argument_list|,
name|free_sel
operator|->
name|num_points
argument_list|,
name|FALSE
argument_list|,
name|FALSE
argument_list|)
expr_stmt|;
block|}
end_function

begin_comment
comment|/*  public functions  */
end_comment

begin_function
name|void
DECL|function|gimp_free_select_tool_select (GimpFreeSelectTool * free_sel,GimpDisplay * display)
name|gimp_free_select_tool_select
parameter_list|(
name|GimpFreeSelectTool
modifier|*
name|free_sel
parameter_list|,
name|GimpDisplay
modifier|*
name|display
parameter_list|)
block|{
name|g_return_if_fail
argument_list|(
name|GIMP_IS_FREE_SELECT_TOOL
argument_list|(
name|free_sel
argument_list|)
argument_list|)
expr_stmt|;
name|g_return_if_fail
argument_list|(
name|GIMP_IS_DISPLAY
argument_list|(
name|display
argument_list|)
argument_list|)
expr_stmt|;
name|GIMP_FREE_SELECT_TOOL_GET_CLASS
argument_list|(
name|free_sel
argument_list|)
operator|->
name|select
argument_list|(
name|free_sel
argument_list|,
name|display
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
DECL|function|gimp_free_select_tool_real_select (GimpFreeSelectTool * free_sel,GimpDisplay * display)
name|gimp_free_select_tool_real_select
parameter_list|(
name|GimpFreeSelectTool
modifier|*
name|free_sel
parameter_list|,
name|GimpDisplay
modifier|*
name|display
parameter_list|)
block|{
name|GimpSelectionOptions
modifier|*
name|options
init|=
name|GIMP_SELECTION_TOOL_GET_OPTIONS
argument_list|(
name|free_sel
argument_list|)
decl_stmt|;
name|gimp_channel_select_polygon
argument_list|(
name|gimp_image_get_mask
argument_list|(
name|display
operator|->
name|image
argument_list|)
argument_list|,
name|Q_
argument_list|(
literal|"command|Free Select"
argument_list|)
argument_list|,
name|free_sel
operator|->
name|num_points
argument_list|,
name|free_sel
operator|->
name|points
argument_list|,
name|options
operator|->
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

begin_function
specifier|static
name|void
DECL|function|gimp_free_select_tool_add_point (GimpFreeSelectTool * free_sel,gdouble x,gdouble y)
name|gimp_free_select_tool_add_point
parameter_list|(
name|GimpFreeSelectTool
modifier|*
name|free_sel
parameter_list|,
name|gdouble
name|x
parameter_list|,
name|gdouble
name|y
parameter_list|)
block|{
if|if
condition|(
name|free_sel
operator|->
name|num_points
operator|>=
name|free_sel
operator|->
name|max_segs
condition|)
block|{
name|free_sel
operator|->
name|max_segs
operator|+=
name|DEFAULT_MAX_INC
expr_stmt|;
name|free_sel
operator|->
name|points
operator|=
name|g_realloc
argument_list|(
name|free_sel
operator|->
name|points
argument_list|,
sizeof|sizeof
argument_list|(
name|GimpVector2
argument_list|)
operator|*
name|free_sel
operator|->
name|max_segs
argument_list|)
expr_stmt|;
block|}
name|free_sel
operator|->
name|points
index|[
name|free_sel
operator|->
name|num_points
index|]
operator|.
name|x
operator|=
name|x
expr_stmt|;
name|free_sel
operator|->
name|points
index|[
name|free_sel
operator|->
name|num_points
index|]
operator|.
name|y
operator|=
name|y
expr_stmt|;
name|free_sel
operator|->
name|num_points
operator|++
expr_stmt|;
block|}
end_function

begin_function
specifier|static
name|void
DECL|function|gimp_free_select_tool_move_points (GimpFreeSelectTool * free_sel,gdouble dx,gdouble dy)
name|gimp_free_select_tool_move_points
parameter_list|(
name|GimpFreeSelectTool
modifier|*
name|free_sel
parameter_list|,
name|gdouble
name|dx
parameter_list|,
name|gdouble
name|dy
parameter_list|)
block|{
name|gint
name|i
decl_stmt|;
for|for
control|(
name|i
operator|=
literal|0
init|;
name|i
operator|<
name|free_sel
operator|->
name|num_points
condition|;
name|i
operator|++
control|)
block|{
name|free_sel
operator|->
name|points
index|[
name|i
index|]
operator|.
name|x
operator|+=
name|dx
expr_stmt|;
name|free_sel
operator|->
name|points
index|[
name|i
index|]
operator|.
name|y
operator|+=
name|dy
expr_stmt|;
block|}
block|}
end_function

end_unit

