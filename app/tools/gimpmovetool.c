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
file|"core/gimpimage.h"
end_include

begin_include
include|#
directive|include
file|"core/gimpimage-guides.h"
end_include

begin_include
include|#
directive|include
file|"core/gimpimage-mask.h"
end_include

begin_include
include|#
directive|include
file|"core/gimpimage-undo-push.h"
end_include

begin_include
include|#
directive|include
file|"core/gimplayer.h"
end_include

begin_include
include|#
directive|include
file|"core/gimplayer-floating-sel.h"
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
file|"display/gimpdisplay-foreach.h"
end_include

begin_include
include|#
directive|include
file|"display/gimpdisplayshell.h"
end_include

begin_include
include|#
directive|include
file|"display/gimpdisplayshell-appearance.h"
end_include

begin_include
include|#
directive|include
file|"display/gimpdisplayshell-transform.h"
end_include

begin_include
include|#
directive|include
file|"widgets/gimpwidgets-utils.h"
end_include

begin_include
include|#
directive|include
file|"gimpeditselectiontool.h"
end_include

begin_include
include|#
directive|include
file|"gimpmoveoptions.h"
end_include

begin_include
include|#
directive|include
file|"gimpmovetool.h"
end_include

begin_include
include|#
directive|include
file|"gimp-intl.h"
end_include

begin_comment
comment|/*  local function prototypes  */
end_comment

begin_function_decl
specifier|static
name|void
name|gimp_move_tool_class_init
parameter_list|(
name|GimpMoveToolClass
modifier|*
name|klass
parameter_list|)
function_decl|;
end_function_decl

begin_function_decl
specifier|static
name|void
name|gimp_move_tool_init
parameter_list|(
name|GimpMoveTool
modifier|*
name|move_tool
parameter_list|)
function_decl|;
end_function_decl

begin_function_decl
specifier|static
name|void
name|gimp_move_tool_control
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
name|gdisp
parameter_list|)
function_decl|;
end_function_decl

begin_function_decl
specifier|static
name|void
name|gimp_move_tool_button_press
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
name|gimp_move_tool_button_release
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
name|gimp_move_tool_motion
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
name|gimp_move_tool_modifier_key
parameter_list|(
name|GimpTool
modifier|*
name|tool
parameter_list|,
name|GdkModifierType
name|key
parameter_list|,
name|gboolean
name|press
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
name|gimp_move_tool_cursor_update
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
name|gimp_move_tool_draw
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
name|gimp_move_tool_start_guide
parameter_list|(
name|GimpTool
modifier|*
name|tool
parameter_list|,
name|GimpDisplay
modifier|*
name|gdisp
parameter_list|,
name|GimpOrientationType
name|orientation
parameter_list|)
function_decl|;
end_function_decl

begin_decl_stmt
DECL|variable|parent_class
specifier|static
name|GimpDrawToolClass
modifier|*
name|parent_class
init|=
name|NULL
decl_stmt|;
end_decl_stmt

begin_function
name|void
DECL|function|gimp_move_tool_register (GimpToolRegisterCallback callback,gpointer data)
name|gimp_move_tool_register
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
name|GIMP_TYPE_MOVE_TOOL
argument_list|,
name|GIMP_TYPE_MOVE_OPTIONS
argument_list|,
name|gimp_move_options_gui
argument_list|,
name|FALSE
argument_list|,
literal|"gimp-move-tool"
argument_list|,
name|_
argument_list|(
literal|"Move"
argument_list|)
argument_list|,
name|_
argument_list|(
literal|"Move layers& selections"
argument_list|)
argument_list|,
name|N_
argument_list|(
literal|"/Tools/Transform Tools/Move"
argument_list|)
argument_list|,
literal|"M"
argument_list|,
name|NULL
argument_list|,
literal|"tools/move.html"
argument_list|,
name|GIMP_STOCK_TOOL_MOVE
argument_list|,
name|data
argument_list|)
expr_stmt|;
block|}
end_function

begin_function
name|GType
DECL|function|gimp_move_tool_get_type (void)
name|gimp_move_tool_get_type
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
name|GimpMoveToolClass
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
name|gimp_move_tool_class_init
block|,
name|NULL
block|,
comment|/* class_finalize */
name|NULL
block|,
comment|/* class_data     */
sizeof|sizeof
argument_list|(
name|GimpMoveTool
argument_list|)
block|,
literal|0
block|,
comment|/* n_preallocs    */
operator|(
name|GInstanceInitFunc
operator|)
name|gimp_move_tool_init
block|,       }
decl_stmt|;
name|tool_type
operator|=
name|g_type_register_static
argument_list|(
name|GIMP_TYPE_DRAW_TOOL
argument_list|,
literal|"GimpMoveTool"
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

begin_function
specifier|static
name|void
DECL|function|gimp_move_tool_class_init (GimpMoveToolClass * klass)
name|gimp_move_tool_class_init
parameter_list|(
name|GimpMoveToolClass
modifier|*
name|klass
parameter_list|)
block|{
name|GimpToolClass
modifier|*
name|tool_class
decl_stmt|;
name|GimpDrawToolClass
modifier|*
name|draw_tool_class
decl_stmt|;
name|tool_class
operator|=
name|GIMP_TOOL_CLASS
argument_list|(
name|klass
argument_list|)
expr_stmt|;
name|draw_tool_class
operator|=
name|GIMP_DRAW_TOOL_CLASS
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
name|control
operator|=
name|gimp_move_tool_control
expr_stmt|;
name|tool_class
operator|->
name|button_press
operator|=
name|gimp_move_tool_button_press
expr_stmt|;
name|tool_class
operator|->
name|button_release
operator|=
name|gimp_move_tool_button_release
expr_stmt|;
name|tool_class
operator|->
name|motion
operator|=
name|gimp_move_tool_motion
expr_stmt|;
name|tool_class
operator|->
name|arrow_key
operator|=
name|gimp_edit_selection_tool_arrow_key
expr_stmt|;
name|tool_class
operator|->
name|modifier_key
operator|=
name|gimp_move_tool_modifier_key
expr_stmt|;
name|tool_class
operator|->
name|cursor_update
operator|=
name|gimp_move_tool_cursor_update
expr_stmt|;
name|draw_tool_class
operator|->
name|draw
operator|=
name|gimp_move_tool_draw
expr_stmt|;
block|}
end_function

begin_function
specifier|static
name|void
DECL|function|gimp_move_tool_init (GimpMoveTool * move_tool)
name|gimp_move_tool_init
parameter_list|(
name|GimpMoveTool
modifier|*
name|move_tool
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
name|move_tool
argument_list|)
expr_stmt|;
name|move_tool
operator|->
name|layer
operator|=
name|NULL
expr_stmt|;
name|move_tool
operator|->
name|guide
operator|=
name|NULL
expr_stmt|;
name|move_tool
operator|->
name|guide_disp
operator|=
name|NULL
expr_stmt|;
name|move_tool
operator|->
name|moving_guide
operator|=
name|FALSE
expr_stmt|;
name|move_tool
operator|->
name|guide_position
operator|=
operator|-
literal|1
expr_stmt|;
name|move_tool
operator|->
name|guide_orientation
operator|=
name|GIMP_ORIENTATION_UNKNOWN
expr_stmt|;
name|gimp_tool_control_set_snap_to
argument_list|(
name|tool
operator|->
name|control
argument_list|,
name|FALSE
argument_list|)
expr_stmt|;
name|gimp_tool_control_set_handles_empty_image
argument_list|(
name|tool
operator|->
name|control
argument_list|,
name|TRUE
argument_list|)
expr_stmt|;
name|gimp_tool_control_set_tool_cursor
argument_list|(
name|tool
operator|->
name|control
argument_list|,
name|GIMP_MOVE_TOOL_CURSOR
argument_list|)
expr_stmt|;
block|}
end_function

begin_function
specifier|static
name|void
DECL|function|gimp_move_tool_control (GimpTool * tool,GimpToolAction action,GimpDisplay * gdisp)
name|gimp_move_tool_control
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
name|gdisp
parameter_list|)
block|{
name|GimpMoveTool
modifier|*
name|move_tool
decl_stmt|;
name|move_tool
operator|=
name|GIMP_MOVE_TOOL
argument_list|(
name|tool
argument_list|)
expr_stmt|;
switch|switch
condition|(
name|action
condition|)
block|{
case|case
name|PAUSE
case|:
break|break;
case|case
name|RESUME
case|:
if|if
condition|(
name|move_tool
operator|->
name|guide
condition|)
name|gimp_display_shell_draw_guide
argument_list|(
name|GIMP_DISPLAY_SHELL
argument_list|(
name|gdisp
operator|->
name|shell
argument_list|)
argument_list|,
name|move_tool
operator|->
name|guide
argument_list|,
name|TRUE
argument_list|)
expr_stmt|;
break|break;
case|case
name|HALT
case|:
if|if
condition|(
name|move_tool
operator|->
name|guide
condition|)
name|gimp_display_shell_draw_guide
argument_list|(
name|GIMP_DISPLAY_SHELL
argument_list|(
name|gdisp
operator|->
name|shell
argument_list|)
argument_list|,
name|move_tool
operator|->
name|guide
argument_list|,
name|FALSE
argument_list|)
expr_stmt|;
break|break;
default|default:
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
name|gdisp
argument_list|)
expr_stmt|;
block|}
end_function

begin_function
specifier|static
name|void
DECL|function|gimp_move_tool_button_press (GimpTool * tool,GimpCoords * coords,guint32 time,GdkModifierType state,GimpDisplay * gdisp)
name|gimp_move_tool_button_press
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
name|GimpDisplayShell
modifier|*
name|shell
decl_stmt|;
name|GimpMoveTool
modifier|*
name|move
decl_stmt|;
name|GimpMoveOptions
modifier|*
name|options
decl_stmt|;
name|GimpLayer
modifier|*
name|layer
decl_stmt|;
name|GimpGuide
modifier|*
name|guide
decl_stmt|;
name|shell
operator|=
name|GIMP_DISPLAY_SHELL
argument_list|(
name|gdisp
operator|->
name|shell
argument_list|)
expr_stmt|;
name|move
operator|=
name|GIMP_MOVE_TOOL
argument_list|(
name|tool
argument_list|)
expr_stmt|;
name|options
operator|=
name|GIMP_MOVE_OPTIONS
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
name|gdisp
operator|=
name|gdisp
expr_stmt|;
name|move
operator|->
name|layer
operator|=
name|NULL
expr_stmt|;
name|move
operator|->
name|guide
operator|=
name|NULL
expr_stmt|;
name|move
operator|->
name|guide_disp
operator|=
name|NULL
expr_stmt|;
name|move
operator|->
name|moving_guide
operator|=
name|FALSE
expr_stmt|;
if|if
condition|(
name|options
operator|->
name|move_mask
operator|&&
operator|!
name|gimp_image_mask_is_empty
argument_list|(
name|gdisp
operator|->
name|gimage
argument_list|)
condition|)
block|{
name|init_edit_selection
argument_list|(
name|tool
argument_list|,
name|gdisp
argument_list|,
name|coords
argument_list|,
name|EDIT_MASK_TRANSLATE
argument_list|)
expr_stmt|;
name|gimp_tool_control_activate
argument_list|(
name|tool
operator|->
name|control
argument_list|)
expr_stmt|;
block|}
elseif|else
if|if
condition|(
name|options
operator|->
name|move_current
condition|)
block|{
name|init_edit_selection
argument_list|(
name|tool
argument_list|,
name|gdisp
argument_list|,
name|coords
argument_list|,
name|EDIT_LAYER_TRANSLATE
argument_list|)
expr_stmt|;
name|gimp_tool_control_activate
argument_list|(
name|tool
operator|->
name|control
argument_list|)
expr_stmt|;
block|}
else|else
block|{
if|if
condition|(
name|gimp_display_shell_get_show_guides
argument_list|(
name|shell
argument_list|)
operator|&&
operator|(
name|guide
operator|=
name|gimp_image_find_guide
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
operator|)
condition|)
block|{
name|move
operator|->
name|guide
operator|=
name|guide
expr_stmt|;
name|move
operator|->
name|guide_disp
operator|=
name|gdisp
expr_stmt|;
name|move
operator|->
name|moving_guide
operator|=
name|TRUE
expr_stmt|;
name|move
operator|->
name|guide_position
operator|=
name|guide
operator|->
name|position
expr_stmt|;
name|move
operator|->
name|guide_orientation
operator|=
name|guide
operator|->
name|orientation
expr_stmt|;
name|gimp_tool_control_set_scroll_lock
argument_list|(
name|tool
operator|->
name|control
argument_list|,
name|TRUE
argument_list|)
expr_stmt|;
name|gimp_tool_control_activate
argument_list|(
name|tool
operator|->
name|control
argument_list|)
expr_stmt|;
name|gimp_draw_tool_start
argument_list|(
name|GIMP_DRAW_TOOL
argument_list|(
name|tool
argument_list|)
argument_list|,
name|gdisp
argument_list|)
expr_stmt|;
block|}
elseif|else
if|if
condition|(
operator|(
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
operator|)
condition|)
block|{
comment|/*  If there is a floating selection, and this aint it, 	   *  use the move tool 	   */
if|if
condition|(
name|gimp_image_floating_sel
argument_list|(
name|gdisp
operator|->
name|gimage
argument_list|)
operator|&&
operator|!
name|gimp_layer_is_floating_sel
argument_list|(
name|layer
argument_list|)
condition|)
block|{
name|move
operator|->
name|layer
operator|=
name|gimp_image_floating_sel
argument_list|(
name|gdisp
operator|->
name|gimage
argument_list|)
expr_stmt|;
block|}
comment|/*  Otherwise, init the edit selection  */
else|else
block|{
name|gimp_image_set_active_layer
argument_list|(
name|gdisp
operator|->
name|gimage
argument_list|,
name|layer
argument_list|)
expr_stmt|;
ifdef|#
directive|ifdef
name|__GNUC__
warning|#
directive|warning
warning|FIXME: gimp_layer_set_linked()
endif|#
directive|endif
if|#
directive|if
literal|0
block|if (state& GDK_SHIFT_MASK)                 gimp_layer_set_linked (layer, ! gimp_layer_get_linked (layer));
endif|#
directive|endif
name|init_edit_selection
argument_list|(
name|tool
argument_list|,
name|gdisp
argument_list|,
name|coords
argument_list|,
name|EDIT_LAYER_TRANSLATE
argument_list|)
expr_stmt|;
block|}
name|gimp_tool_control_activate
argument_list|(
name|tool
operator|->
name|control
argument_list|)
expr_stmt|;
block|}
block|}
block|}
end_function

begin_function
specifier|static
name|void
DECL|function|gimp_move_tool_button_release (GimpTool * tool,GimpCoords * coords,guint32 time,GdkModifierType state,GimpDisplay * gdisp)
name|gimp_move_tool_button_release
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
name|GimpMoveTool
modifier|*
name|move
decl_stmt|;
name|GimpDisplayShell
modifier|*
name|shell
decl_stmt|;
name|move
operator|=
name|GIMP_MOVE_TOOL
argument_list|(
name|tool
argument_list|)
expr_stmt|;
name|shell
operator|=
name|GIMP_DISPLAY_SHELL
argument_list|(
name|gdisp
operator|->
name|shell
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
name|move
operator|->
name|moving_guide
condition|)
block|{
name|gboolean
name|delete_guide
init|=
name|FALSE
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
name|gimp_tool_control_set_scroll_lock
argument_list|(
name|tool
operator|->
name|control
argument_list|,
name|FALSE
argument_list|)
expr_stmt|;
name|gimp_draw_tool_stop
argument_list|(
name|GIMP_DRAW_TOOL
argument_list|(
name|tool
argument_list|)
argument_list|)
expr_stmt|;
if|if
condition|(
name|state
operator|&
name|GDK_BUTTON3_MASK
condition|)
block|{
name|move
operator|->
name|moving_guide
operator|=
name|FALSE
expr_stmt|;
name|move
operator|->
name|guide_position
operator|=
operator|-
literal|1
expr_stmt|;
name|move
operator|->
name|guide_orientation
operator|=
name|GIMP_ORIENTATION_UNKNOWN
expr_stmt|;
return|return;
block|}
name|gimp_display_shell_untransform_xy
argument_list|(
name|shell
argument_list|,
literal|0
argument_list|,
literal|0
argument_list|,
operator|&
name|x1
argument_list|,
operator|&
name|y1
argument_list|,
name|FALSE
argument_list|,
name|FALSE
argument_list|)
expr_stmt|;
name|gimp_display_shell_untransform_xy
argument_list|(
name|shell
argument_list|,
name|shell
operator|->
name|disp_width
argument_list|,
name|shell
operator|->
name|disp_height
argument_list|,
operator|&
name|x2
argument_list|,
operator|&
name|y2
argument_list|,
name|FALSE
argument_list|,
name|FALSE
argument_list|)
expr_stmt|;
if|if
condition|(
name|x1
operator|<
literal|0
condition|)
name|x1
operator|=
literal|0
expr_stmt|;
if|if
condition|(
name|y1
operator|<
literal|0
condition|)
name|y1
operator|=
literal|0
expr_stmt|;
if|if
condition|(
name|x2
operator|>
name|gdisp
operator|->
name|gimage
operator|->
name|width
condition|)
name|x2
operator|=
name|gdisp
operator|->
name|gimage
operator|->
name|width
expr_stmt|;
if|if
condition|(
name|y2
operator|>
name|gdisp
operator|->
name|gimage
operator|->
name|height
condition|)
name|y2
operator|=
name|gdisp
operator|->
name|gimage
operator|->
name|height
expr_stmt|;
switch|switch
condition|(
name|move
operator|->
name|guide_orientation
condition|)
block|{
case|case
name|GIMP_ORIENTATION_HORIZONTAL
case|:
if|if
condition|(
operator|(
name|move
operator|->
name|guide_position
operator|<
name|y1
operator|)
operator|||
operator|(
name|move
operator|->
name|guide_position
operator|>
name|y2
operator|)
condition|)
name|delete_guide
operator|=
name|TRUE
expr_stmt|;
break|break;
case|case
name|GIMP_ORIENTATION_VERTICAL
case|:
if|if
condition|(
operator|(
name|move
operator|->
name|guide_position
operator|<
name|x1
operator|)
operator|||
operator|(
name|move
operator|->
name|guide_position
operator|>
name|x2
operator|)
condition|)
name|delete_guide
operator|=
name|TRUE
expr_stmt|;
break|break;
default|default:
break|break;
block|}
if|if
condition|(
name|delete_guide
condition|)
block|{
if|if
condition|(
name|move
operator|->
name|guide
condition|)
block|{
name|gimp_image_remove_guide
argument_list|(
name|gdisp
operator|->
name|gimage
argument_list|,
name|move
operator|->
name|guide
argument_list|,
name|TRUE
argument_list|)
expr_stmt|;
name|move
operator|->
name|guide
operator|=
name|NULL
expr_stmt|;
name|move
operator|->
name|guide_disp
operator|=
name|NULL
expr_stmt|;
block|}
block|}
else|else
block|{
if|if
condition|(
name|move
operator|->
name|guide
condition|)
block|{
name|gimp_image_move_guide
argument_list|(
name|gdisp
operator|->
name|gimage
argument_list|,
name|move
operator|->
name|guide
argument_list|,
name|move
operator|->
name|guide_position
argument_list|,
name|TRUE
argument_list|)
expr_stmt|;
block|}
else|else
block|{
switch|switch
condition|(
name|move
operator|->
name|guide_orientation
condition|)
block|{
case|case
name|GIMP_ORIENTATION_HORIZONTAL
case|:
name|move
operator|->
name|guide
operator|=
name|gimp_image_add_hguide
argument_list|(
name|gdisp
operator|->
name|gimage
argument_list|,
name|move
operator|->
name|guide_position
argument_list|,
name|TRUE
argument_list|)
expr_stmt|;
break|break;
case|case
name|GIMP_ORIENTATION_VERTICAL
case|:
name|move
operator|->
name|guide
operator|=
name|gimp_image_add_vguide
argument_list|(
name|gdisp
operator|->
name|gimage
argument_list|,
name|move
operator|->
name|guide_position
argument_list|,
name|TRUE
argument_list|)
expr_stmt|;
break|break;
default|default:
name|g_assert_not_reached
argument_list|()
expr_stmt|;
block|}
name|move
operator|->
name|guide_disp
operator|=
name|gdisp
expr_stmt|;
block|}
block|}
name|gimp_display_shell_selection_visibility
argument_list|(
name|shell
argument_list|,
name|GIMP_SELECTION_RESUME
argument_list|)
expr_stmt|;
name|gimp_image_flush
argument_list|(
name|gdisp
operator|->
name|gimage
argument_list|)
expr_stmt|;
if|if
condition|(
name|move
operator|->
name|guide
condition|)
name|gimp_display_shell_draw_guide
argument_list|(
name|shell
argument_list|,
name|move
operator|->
name|guide
argument_list|,
name|TRUE
argument_list|)
expr_stmt|;
name|move
operator|->
name|moving_guide
operator|=
name|FALSE
expr_stmt|;
name|move
operator|->
name|guide_position
operator|=
operator|-
literal|1
expr_stmt|;
name|move
operator|->
name|guide_orientation
operator|=
name|GIMP_ORIENTATION_UNKNOWN
expr_stmt|;
block|}
else|else
block|{
comment|/*  Take care of the case where the user "cancels" the action  */
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
name|move
operator|->
name|layer
condition|)
block|{
name|floating_sel_anchor
argument_list|(
name|move
operator|->
name|layer
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
block|}
end_function

begin_function
specifier|static
name|void
DECL|function|gimp_move_tool_motion (GimpTool * tool,GimpCoords * coords,guint32 time,GdkModifierType state,GimpDisplay * gdisp)
name|gimp_move_tool_motion
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
name|GimpMoveTool
modifier|*
name|move
decl_stmt|;
name|GimpDisplayShell
modifier|*
name|shell
decl_stmt|;
name|move
operator|=
name|GIMP_MOVE_TOOL
argument_list|(
name|tool
argument_list|)
expr_stmt|;
name|shell
operator|=
name|GIMP_DISPLAY_SHELL
argument_list|(
name|gdisp
operator|->
name|shell
argument_list|)
expr_stmt|;
if|if
condition|(
name|move
operator|->
name|moving_guide
condition|)
block|{
name|gint
name|tx
decl_stmt|,
name|ty
decl_stmt|;
name|gimp_draw_tool_pause
argument_list|(
name|GIMP_DRAW_TOOL
argument_list|(
name|tool
argument_list|)
argument_list|)
expr_stmt|;
name|gimp_display_shell_transform_xy
argument_list|(
name|shell
argument_list|,
name|coords
operator|->
name|x
argument_list|,
name|coords
operator|->
name|y
argument_list|,
operator|&
name|tx
argument_list|,
operator|&
name|ty
argument_list|,
name|FALSE
argument_list|)
expr_stmt|;
if|if
condition|(
name|tx
operator|<
literal|0
operator|||
name|tx
operator|>=
name|shell
operator|->
name|disp_width
operator|||
name|ty
operator|<
literal|0
operator|||
name|ty
operator|>=
name|shell
operator|->
name|disp_height
condition|)
block|{
name|move
operator|->
name|guide_position
operator|=
operator|-
literal|1
expr_stmt|;
block|}
else|else
block|{
if|if
condition|(
name|move
operator|->
name|guide_orientation
operator|==
name|GIMP_ORIENTATION_HORIZONTAL
condition|)
name|move
operator|->
name|guide_position
operator|=
name|ROUND
argument_list|(
name|coords
operator|->
name|y
argument_list|)
expr_stmt|;
else|else
name|move
operator|->
name|guide_position
operator|=
name|ROUND
argument_list|(
name|coords
operator|->
name|x
argument_list|)
expr_stmt|;
block|}
name|gimp_draw_tool_resume
argument_list|(
name|GIMP_DRAW_TOOL
argument_list|(
name|tool
argument_list|)
argument_list|)
expr_stmt|;
block|}
block|}
end_function

begin_function
specifier|static
name|void
DECL|function|gimp_move_tool_modifier_key (GimpTool * tool,GdkModifierType key,gboolean press,GdkModifierType state,GimpDisplay * gdisp)
name|gimp_move_tool_modifier_key
parameter_list|(
name|GimpTool
modifier|*
name|tool
parameter_list|,
name|GdkModifierType
name|key
parameter_list|,
name|gboolean
name|press
parameter_list|,
name|GdkModifierType
name|state
parameter_list|,
name|GimpDisplay
modifier|*
name|gdisp
parameter_list|)
block|{
name|GimpMoveOptions
modifier|*
name|options
decl_stmt|;
name|options
operator|=
name|GIMP_MOVE_OPTIONS
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
name|key
operator|==
name|GDK_CONTROL_MASK
condition|)
block|{
name|g_object_set
argument_list|(
name|options
argument_list|,
literal|"move-current"
argument_list|,
operator|!
name|options
operator|->
name|move_current
argument_list|,
name|NULL
argument_list|)
expr_stmt|;
block|}
elseif|else
if|if
condition|(
name|key
operator|==
name|GDK_MOD1_MASK
condition|)
block|{
name|g_object_set
argument_list|(
name|options
argument_list|,
literal|"move-mask"
argument_list|,
operator|!
name|options
operator|->
name|move_mask
argument_list|,
name|NULL
argument_list|)
expr_stmt|;
block|}
block|}
end_function

begin_function
specifier|static
name|void
DECL|function|gimp_move_tool_cursor_update (GimpTool * tool,GimpCoords * coords,GdkModifierType state,GimpDisplay * gdisp)
name|gimp_move_tool_cursor_update
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
name|GimpDisplayShell
modifier|*
name|shell
decl_stmt|;
name|GimpMoveTool
modifier|*
name|move
decl_stmt|;
name|GimpMoveOptions
modifier|*
name|options
decl_stmt|;
name|GimpLayer
modifier|*
name|layer
decl_stmt|;
name|GimpGuide
modifier|*
name|guide
decl_stmt|;
name|shell
operator|=
name|GIMP_DISPLAY_SHELL
argument_list|(
name|gdisp
operator|->
name|shell
argument_list|)
expr_stmt|;
name|move
operator|=
name|GIMP_MOVE_TOOL
argument_list|(
name|tool
argument_list|)
expr_stmt|;
name|options
operator|=
name|GIMP_MOVE_OPTIONS
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
name|options
operator|->
name|move_mask
operator|&&
operator|!
name|gimp_image_mask_is_empty
argument_list|(
name|gdisp
operator|->
name|gimage
argument_list|)
condition|)
block|{
name|gimp_tool_set_cursor
argument_list|(
name|tool
argument_list|,
name|gdisp
argument_list|,
name|GIMP_MOUSE_CURSOR
argument_list|,
name|GIMP_RECT_SELECT_TOOL_CURSOR
argument_list|,
name|GIMP_CURSOR_MODIFIER_MOVE
argument_list|)
expr_stmt|;
block|}
elseif|else
if|if
condition|(
name|options
operator|->
name|move_current
condition|)
block|{
name|gimp_tool_set_cursor
argument_list|(
name|tool
argument_list|,
name|gdisp
argument_list|,
name|GIMP_MOUSE_CURSOR
argument_list|,
name|GIMP_MOVE_TOOL_CURSOR
argument_list|,
name|GIMP_CURSOR_MODIFIER_NONE
argument_list|)
expr_stmt|;
block|}
else|else
block|{
if|if
condition|(
name|gimp_display_shell_get_show_guides
argument_list|(
name|shell
argument_list|)
operator|&&
operator|(
name|guide
operator|=
name|gimp_image_find_guide
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
operator|)
condition|)
block|{
name|gimp_tool_set_cursor
argument_list|(
name|tool
argument_list|,
name|gdisp
argument_list|,
name|GDK_HAND2
argument_list|,
name|GIMP_TOOL_CURSOR_NONE
argument_list|,
name|GIMP_CURSOR_MODIFIER_HAND
argument_list|)
expr_stmt|;
if|if
condition|(
operator|!
name|gimp_tool_control_is_active
argument_list|(
name|tool
operator|->
name|control
argument_list|)
condition|)
block|{
if|if
condition|(
name|move
operator|->
name|guide
condition|)
block|{
name|GimpDisplay
modifier|*
name|old_guide_gdisp
decl_stmt|;
name|old_guide_gdisp
operator|=
name|gdisplays_check_valid
argument_list|(
name|move
operator|->
name|guide_disp
argument_list|,
name|move
operator|->
name|guide_disp
operator|->
name|gimage
argument_list|)
expr_stmt|;
if|if
condition|(
name|old_guide_gdisp
condition|)
block|{
name|GimpDisplayShell
modifier|*
name|shell
decl_stmt|;
name|shell
operator|=
name|GIMP_DISPLAY_SHELL
argument_list|(
name|old_guide_gdisp
operator|->
name|shell
argument_list|)
expr_stmt|;
name|gimp_display_shell_draw_guide
argument_list|(
name|shell
argument_list|,
name|move
operator|->
name|guide
argument_list|,
name|FALSE
argument_list|)
expr_stmt|;
block|}
block|}
name|gimp_display_shell_draw_guide
argument_list|(
name|GIMP_DISPLAY_SHELL
argument_list|(
name|gdisp
operator|->
name|shell
argument_list|)
argument_list|,
name|guide
argument_list|,
name|TRUE
argument_list|)
expr_stmt|;
name|move
operator|->
name|guide
operator|=
name|guide
expr_stmt|;
name|move
operator|->
name|guide_disp
operator|=
name|gdisp
expr_stmt|;
block|}
block|}
elseif|else
if|if
condition|(
operator|(
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
operator|)
condition|)
block|{
comment|/*  if there is a floating selection, and this aint it...  */
if|if
condition|(
name|gimp_image_floating_sel
argument_list|(
name|gdisp
operator|->
name|gimage
argument_list|)
operator|&&
operator|!
name|gimp_layer_is_floating_sel
argument_list|(
name|layer
argument_list|)
condition|)
block|{
name|gimp_tool_set_cursor
argument_list|(
name|tool
argument_list|,
name|gdisp
argument_list|,
name|GIMP_MOUSE_CURSOR
argument_list|,
name|GIMP_RECT_SELECT_TOOL_CURSOR
argument_list|,
name|GIMP_CURSOR_MODIFIER_ANCHOR
argument_list|)
expr_stmt|;
block|}
elseif|else
if|if
condition|(
name|layer
operator|==
name|gimp_image_get_active_layer
argument_list|(
name|gdisp
operator|->
name|gimage
argument_list|)
condition|)
block|{
name|gimp_tool_set_cursor
argument_list|(
name|tool
argument_list|,
name|gdisp
argument_list|,
name|GIMP_MOUSE_CURSOR
argument_list|,
name|GIMP_MOVE_TOOL_CURSOR
argument_list|,
name|GIMP_CURSOR_MODIFIER_NONE
argument_list|)
expr_stmt|;
block|}
else|else
block|{
name|gimp_tool_set_cursor
argument_list|(
name|tool
argument_list|,
name|gdisp
argument_list|,
name|GDK_HAND2
argument_list|,
name|GIMP_TOOL_CURSOR_NONE
argument_list|,
name|GIMP_CURSOR_MODIFIER_HAND
argument_list|)
expr_stmt|;
block|}
block|}
else|else
block|{
name|gimp_tool_set_cursor
argument_list|(
name|tool
argument_list|,
name|gdisp
argument_list|,
name|GIMP_BAD_CURSOR
argument_list|,
name|GIMP_MOVE_TOOL_CURSOR
argument_list|,
name|GIMP_CURSOR_MODIFIER_NONE
argument_list|)
expr_stmt|;
block|}
block|}
block|}
end_function

begin_function
specifier|static
name|void
DECL|function|gimp_move_tool_draw (GimpDrawTool * draw_tool)
name|gimp_move_tool_draw
parameter_list|(
name|GimpDrawTool
modifier|*
name|draw_tool
parameter_list|)
block|{
name|GimpMoveTool
modifier|*
name|move
decl_stmt|;
name|GimpTool
modifier|*
name|tool
decl_stmt|;
name|move
operator|=
name|GIMP_MOVE_TOOL
argument_list|(
name|draw_tool
argument_list|)
expr_stmt|;
name|tool
operator|=
name|GIMP_TOOL
argument_list|(
name|draw_tool
argument_list|)
expr_stmt|;
if|if
condition|(
name|move
operator|->
name|moving_guide
operator|&&
name|move
operator|->
name|guide_position
operator|!=
operator|-
literal|1
condition|)
block|{
switch|switch
condition|(
name|move
operator|->
name|guide_orientation
condition|)
block|{
case|case
name|GIMP_ORIENTATION_HORIZONTAL
case|:
name|gimp_draw_tool_draw_line
argument_list|(
name|draw_tool
argument_list|,
literal|0
argument_list|,
name|move
operator|->
name|guide_position
argument_list|,
name|draw_tool
operator|->
name|gdisp
operator|->
name|gimage
operator|->
name|width
argument_list|,
name|move
operator|->
name|guide_position
argument_list|,
name|FALSE
argument_list|)
expr_stmt|;
break|break;
case|case
name|GIMP_ORIENTATION_VERTICAL
case|:
name|gimp_draw_tool_draw_line
argument_list|(
name|draw_tool
argument_list|,
name|move
operator|->
name|guide_position
argument_list|,
literal|0
argument_list|,
name|move
operator|->
name|guide_position
argument_list|,
name|draw_tool
operator|->
name|gdisp
operator|->
name|gimage
operator|->
name|height
argument_list|,
name|FALSE
argument_list|)
expr_stmt|;
break|break;
default|default:
name|g_assert_not_reached
argument_list|()
expr_stmt|;
block|}
block|}
block|}
end_function

begin_function
name|void
DECL|function|gimp_move_tool_start_hguide (GimpTool * tool,GimpDisplay * gdisp)
name|gimp_move_tool_start_hguide
parameter_list|(
name|GimpTool
modifier|*
name|tool
parameter_list|,
name|GimpDisplay
modifier|*
name|gdisp
parameter_list|)
block|{
name|gimp_move_tool_start_guide
argument_list|(
name|tool
argument_list|,
name|gdisp
argument_list|,
name|GIMP_ORIENTATION_HORIZONTAL
argument_list|)
expr_stmt|;
block|}
end_function

begin_function
name|void
DECL|function|gimp_move_tool_start_vguide (GimpTool * tool,GimpDisplay * gdisp)
name|gimp_move_tool_start_vguide
parameter_list|(
name|GimpTool
modifier|*
name|tool
parameter_list|,
name|GimpDisplay
modifier|*
name|gdisp
parameter_list|)
block|{
name|gimp_move_tool_start_guide
argument_list|(
name|tool
argument_list|,
name|gdisp
argument_list|,
name|GIMP_ORIENTATION_VERTICAL
argument_list|)
expr_stmt|;
block|}
end_function

begin_function
specifier|static
name|void
DECL|function|gimp_move_tool_start_guide (GimpTool * tool,GimpDisplay * gdisp,GimpOrientationType orientation)
name|gimp_move_tool_start_guide
parameter_list|(
name|GimpTool
modifier|*
name|tool
parameter_list|,
name|GimpDisplay
modifier|*
name|gdisp
parameter_list|,
name|GimpOrientationType
name|orientation
parameter_list|)
block|{
name|GimpMoveTool
modifier|*
name|move
decl_stmt|;
name|g_return_if_fail
argument_list|(
name|GIMP_IS_MOVE_TOOL
argument_list|(
name|tool
argument_list|)
argument_list|)
expr_stmt|;
name|g_return_if_fail
argument_list|(
name|GIMP_IS_DISPLAY
argument_list|(
name|gdisp
argument_list|)
argument_list|)
expr_stmt|;
name|move
operator|=
name|GIMP_MOVE_TOOL
argument_list|(
name|tool
argument_list|)
expr_stmt|;
name|gimp_display_shell_selection_visibility
argument_list|(
name|GIMP_DISPLAY_SHELL
argument_list|(
name|gdisp
operator|->
name|shell
argument_list|)
argument_list|,
name|GIMP_SELECTION_PAUSE
argument_list|)
expr_stmt|;
name|tool
operator|->
name|gdisp
operator|=
name|gdisp
expr_stmt|;
name|gimp_tool_control_activate
argument_list|(
name|tool
operator|->
name|control
argument_list|)
expr_stmt|;
name|gimp_tool_control_set_scroll_lock
argument_list|(
name|tool
operator|->
name|control
argument_list|,
name|TRUE
argument_list|)
expr_stmt|;
if|if
condition|(
name|move
operator|->
name|guide
operator|&&
name|move
operator|->
name|guide_disp
condition|)
name|gimp_display_shell_draw_guide
argument_list|(
name|GIMP_DISPLAY_SHELL
argument_list|(
name|move
operator|->
name|guide_disp
operator|->
name|shell
argument_list|)
argument_list|,
name|move
operator|->
name|guide
argument_list|,
name|FALSE
argument_list|)
expr_stmt|;
name|move
operator|->
name|guide
operator|=
name|NULL
expr_stmt|;
name|move
operator|->
name|guide_disp
operator|=
name|NULL
expr_stmt|;
name|move
operator|->
name|moving_guide
operator|=
name|TRUE
expr_stmt|;
name|move
operator|->
name|guide_position
operator|=
operator|-
literal|1
expr_stmt|;
name|move
operator|->
name|guide_orientation
operator|=
name|orientation
expr_stmt|;
name|gimp_tool_set_cursor
argument_list|(
name|tool
argument_list|,
name|gdisp
argument_list|,
name|GDK_HAND2
argument_list|,
name|GIMP_TOOL_CURSOR_NONE
argument_list|,
name|GIMP_CURSOR_MODIFIER_HAND
argument_list|)
expr_stmt|;
name|gimp_draw_tool_start
argument_list|(
name|GIMP_DRAW_TOOL
argument_list|(
name|tool
argument_list|)
argument_list|,
name|gdisp
argument_list|)
expr_stmt|;
block|}
end_function

end_unit

