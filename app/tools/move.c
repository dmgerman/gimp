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
file|"apptypes.h"
end_include

begin_include
include|#
directive|include
file|"cursorutil.h"
end_include

begin_include
include|#
directive|include
file|"draw_core.h"
end_include

begin_include
include|#
directive|include
file|"floating_sel.h"
end_include

begin_include
include|#
directive|include
file|"gdisplay.h"
end_include

begin_include
include|#
directive|include
file|"gdisplay_ops.h"
end_include

begin_include
include|#
directive|include
file|"gimage_mask.h"
end_include

begin_include
include|#
directive|include
file|"gimplayer.h"
end_include

begin_include
include|#
directive|include
file|"gimpimage.h"
end_include

begin_include
include|#
directive|include
file|"selection.h"
end_include

begin_include
include|#
directive|include
file|"undo.h"
end_include

begin_include
include|#
directive|include
file|"edit_selection.h"
end_include

begin_include
include|#
directive|include
file|"move.h"
end_include

begin_include
include|#
directive|include
file|"tool.h"
end_include

begin_include
include|#
directive|include
file|"tool_manager.h"
end_include

begin_include
include|#
directive|include
file|"tool_options.h"
end_include

begin_include
include|#
directive|include
file|"libgimp/gimpintl.h"
end_include

begin_include
include|#
directive|include
file|"pixmaps2.h"
end_include

begin_include
include|#
directive|include
file|"cursors/move_small.xbm"
end_include

begin_include
include|#
directive|include
file|"cursors/move_small_mask.xbm"
end_include

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
name|gimp_move_tool_destroy
parameter_list|(
name|GtkObject
modifier|*
name|object
parameter_list|)
function_decl|;
end_function_decl

begin_function_decl
specifier|static
name|void
name|move_tool_button_press
parameter_list|(
name|GimpTool
modifier|*
name|tool
parameter_list|,
name|GdkEventButton
modifier|*
name|bevent
parameter_list|,
name|GDisplay
modifier|*
name|gdisp
parameter_list|)
function_decl|;
end_function_decl

begin_function_decl
specifier|static
name|void
name|move_tool_button_release
parameter_list|(
name|GimpTool
modifier|*
name|tool
parameter_list|,
name|GdkEventButton
modifier|*
name|bevent
parameter_list|,
name|GDisplay
modifier|*
name|gdisp
parameter_list|)
function_decl|;
end_function_decl

begin_function_decl
specifier|static
name|void
name|move_tool_motion
parameter_list|(
name|GimpTool
modifier|*
name|tool
parameter_list|,
name|GdkEventMotion
modifier|*
name|mevent
parameter_list|,
name|GDisplay
modifier|*
name|gdisp
parameter_list|)
function_decl|;
end_function_decl

begin_function_decl
specifier|static
name|void
name|move_tool_cursor_update
parameter_list|(
name|GimpTool
modifier|*
name|tool
parameter_list|,
name|GdkEventMotion
modifier|*
name|mevent
parameter_list|,
name|GDisplay
modifier|*
name|gdisp
parameter_list|)
function_decl|;
end_function_decl

begin_function_decl
specifier|static
name|void
name|move_tool_control
parameter_list|(
name|GimpTool
modifier|*
name|tool
parameter_list|,
name|ToolAction
name|tool_action
parameter_list|,
name|GDisplay
modifier|*
name|gdisp
parameter_list|)
function_decl|;
end_function_decl

begin_function_decl
specifier|static
name|void
name|move_create_gc
parameter_list|(
name|GDisplay
modifier|*
name|gdisp
parameter_list|)
function_decl|;
end_function_decl

begin_comment
comment|/*  the move tool options  */
end_comment

begin_decl_stmt
DECL|variable|move_options
specifier|static
name|ToolOptions
modifier|*
name|move_options
init|=
name|NULL
decl_stmt|;
end_decl_stmt

begin_comment
comment|/*  local variables  */
end_comment

begin_decl_stmt
DECL|variable|move_gc
specifier|static
name|GdkGC
modifier|*
name|move_gc
init|=
name|NULL
decl_stmt|;
end_decl_stmt

begin_decl_stmt
DECL|variable|move_cursor
name|BitmapCursor
name|move_cursor
init|=
block|{
name|move_small_bits
block|,
name|move_small_mask_bits
block|,
name|move_small_width
block|,
name|move_small_height
block|,
literal|0
block|,
literal|0
block|,
name|NULL
block|,
name|NULL
block|,
name|NULL
block|}
decl_stmt|;
end_decl_stmt

begin_decl_stmt
DECL|variable|parent_class
specifier|static
name|GimpToolClass
modifier|*
name|parent_class
init|=
name|NULL
decl_stmt|;
end_decl_stmt

begin_function
name|void
DECL|function|gimp_move_tool_register (void)
name|gimp_move_tool_register
parameter_list|(
name|void
parameter_list|)
block|{
name|tool_manager_register_tool
argument_list|(
name|GIMP_TYPE_MOVE_TOOL
argument_list|,
literal|"gimp:move_tool"
argument_list|,
name|_
argument_list|(
literal|"Move Tool"
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
operator|(
specifier|const
name|gchar
operator|*
operator|*
operator|)
name|move_bits
argument_list|)
expr_stmt|;
block|}
end_function

begin_function
name|GtkType
DECL|function|gimp_move_tool_get_type (void)
name|gimp_move_tool_get_type
parameter_list|(
name|void
parameter_list|)
block|{
specifier|static
name|GtkType
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
name|GtkTypeInfo
name|tool_info
init|=
block|{
literal|"GimpMoveTool"
block|,
sizeof|sizeof
argument_list|(
name|GimpMoveTool
argument_list|)
block|,
sizeof|sizeof
argument_list|(
name|GimpMoveToolClass
argument_list|)
block|,
operator|(
name|GtkClassInitFunc
operator|)
name|gimp_move_tool_class_init
block|,
operator|(
name|GtkObjectInitFunc
operator|)
name|gimp_move_tool_init
block|,
comment|/* reserved_1 */
name|NULL
block|,
comment|/* reserved_2 */
name|NULL
block|,
operator|(
name|GtkClassInitFunc
operator|)
name|NULL
block|,       }
decl_stmt|;
name|tool_type
operator|=
name|gtk_type_unique
argument_list|(
name|GIMP_TYPE_TOOL
argument_list|,
operator|&
name|tool_info
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
name|GtkObjectClass
modifier|*
name|object_class
decl_stmt|;
name|GimpToolClass
modifier|*
name|tool_class
decl_stmt|;
name|object_class
operator|=
operator|(
name|GtkObjectClass
operator|*
operator|)
name|klass
expr_stmt|;
name|tool_class
operator|=
operator|(
name|GimpToolClass
operator|*
operator|)
name|klass
expr_stmt|;
name|parent_class
operator|=
name|gtk_type_class
argument_list|(
name|GIMP_TYPE_TOOL
argument_list|)
expr_stmt|;
name|object_class
operator|->
name|destroy
operator|=
name|gimp_move_tool_destroy
expr_stmt|;
name|tool_class
operator|->
name|tool_cursor
operator|=
operator|&
name|move_cursor
expr_stmt|;
name|tool_class
operator|->
name|control
operator|=
name|move_tool_control
expr_stmt|;
name|tool_class
operator|->
name|button_press
operator|=
name|move_tool_button_press
expr_stmt|;
name|tool_class
operator|->
name|button_release
operator|=
name|move_tool_button_release
expr_stmt|;
name|tool_class
operator|->
name|motion
operator|=
name|move_tool_motion
expr_stmt|;
name|tool_class
operator|->
name|cursor_update
operator|=
name|move_tool_cursor_update
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
comment|/*  The tool options  */
if|if
condition|(
operator|!
name|move_options
condition|)
block|{
name|move_options
operator|=
name|tool_options_new
argument_list|()
expr_stmt|;
name|tool_manager_register_tool_options
argument_list|(
name|GIMP_TYPE_MOVE_TOOL
argument_list|,
operator|(
name|ToolOptions
operator|*
operator|)
name|move_options
argument_list|)
expr_stmt|;
block|}
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
name|disp
operator|=
name|NULL
expr_stmt|;
name|tool
operator|->
name|auto_snap_to
operator|=
name|FALSE
expr_stmt|;
comment|/*  Don't snap to guides  */
block|}
end_function

begin_function
specifier|static
name|void
DECL|function|gimp_move_tool_destroy (GtkObject * object)
name|gimp_move_tool_destroy
parameter_list|(
name|GtkObject
modifier|*
name|object
parameter_list|)
block|{
name|GimpMoveTool
modifier|*
name|move_tool
decl_stmt|;
name|GimpTool
modifier|*
name|tool
decl_stmt|;
name|move_tool
operator|=
name|GIMP_MOVE_TOOL
argument_list|(
name|object
argument_list|)
expr_stmt|;
name|tool
operator|=
name|GIMP_TOOL
argument_list|(
name|move_tool
argument_list|)
expr_stmt|;
if|if
condition|(
name|tool
operator|->
name|gdisp
condition|)
block|{
if|if
condition|(
name|move_tool
operator|->
name|guide
condition|)
name|gdisplay_draw_guide
argument_list|(
name|tool
operator|->
name|gdisp
argument_list|,
name|move_tool
operator|->
name|guide
argument_list|,
name|FALSE
argument_list|)
expr_stmt|;
block|}
if|if
condition|(
name|GTK_OBJECT_CLASS
argument_list|(
name|parent_class
argument_list|)
operator|->
name|destroy
condition|)
name|GTK_OBJECT_CLASS
argument_list|(
name|parent_class
argument_list|)
operator|->
name|destroy
argument_list|(
name|object
argument_list|)
expr_stmt|;
block|}
end_function

begin_comment
comment|/*  move action functions  */
end_comment

begin_function
specifier|static
name|void
DECL|function|move_tool_button_press (GimpTool * tool,GdkEventButton * bevent,GDisplay * gdisp)
name|move_tool_button_press
parameter_list|(
name|GimpTool
modifier|*
name|tool
parameter_list|,
name|GdkEventButton
modifier|*
name|bevent
parameter_list|,
name|GDisplay
modifier|*
name|gdisp
parameter_list|)
block|{
name|GimpMoveTool
modifier|*
name|move
decl_stmt|;
name|GimpLayer
modifier|*
name|layer
decl_stmt|;
name|Guide
modifier|*
name|guide
decl_stmt|;
name|gint
name|x
decl_stmt|,
name|y
decl_stmt|;
name|move
operator|=
name|GIMP_MOVE_TOOL
argument_list|(
name|tool
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
name|disp
operator|=
name|NULL
expr_stmt|;
name|gdisplay_untransform_coords
argument_list|(
name|gdisp
argument_list|,
name|bevent
operator|->
name|x
argument_list|,
name|bevent
operator|->
name|y
argument_list|,
operator|&
name|x
argument_list|,
operator|&
name|y
argument_list|,
name|FALSE
argument_list|,
name|FALSE
argument_list|)
expr_stmt|;
warning|#
directive|warning
warning|FIXME fix edit_selection (allow pushing of temp tools)
if|#
directive|if
literal|0
block|if (bevent->state& GDK_MOD1_MASK&&       !gimage_mask_is_empty (gdisp->gimage))     {       init_edit_selection (tool, gdisp, bevent, EDIT_MASK_TRANSLATE);       tool->state = ACTIVE;     }   else if (bevent->state& GDK_SHIFT_MASK)     {       init_edit_selection (tool, gdisp, bevent, EDIT_LAYER_TRANSLATE);       tool->state = ACTIVE;     }   else     {
endif|#
directive|endif
if|if
condition|(
name|gdisp
operator|->
name|draw_guides
operator|&&
operator|(
name|guide
operator|=
name|gdisplay_find_guide
argument_list|(
name|gdisp
argument_list|,
name|bevent
operator|->
name|x
argument_list|,
name|bevent
operator|->
name|y
argument_list|)
operator|)
condition|)
block|{
name|undo_push_guide
argument_list|(
name|gdisp
operator|->
name|gimage
argument_list|,
name|guide
argument_list|)
expr_stmt|;
name|gdisplays_expose_guide
argument_list|(
name|gdisp
operator|->
name|gimage
argument_list|,
name|guide
argument_list|)
expr_stmt|;
name|gimp_image_remove_guide
argument_list|(
name|gdisp
operator|->
name|gimage
argument_list|,
name|guide
argument_list|)
expr_stmt|;
name|gdisplay_flush
argument_list|(
name|gdisp
argument_list|)
expr_stmt|;
name|gimp_image_add_guide
argument_list|(
name|gdisp
operator|->
name|gimage
argument_list|,
name|guide
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
name|disp
operator|=
name|gdisp
expr_stmt|;
name|tool
operator|->
name|scroll_lock
operator|=
name|TRUE
expr_stmt|;
name|tool
operator|->
name|state
operator|=
name|ACTIVE
expr_stmt|;
name|move_tool_motion
argument_list|(
name|tool
argument_list|,
name|NULL
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
name|x
argument_list|,
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
if|#
directive|if
literal|0
comment|/*  Otherwise, init the edit selection  */
block|else 	    { 	      gimp_image_set_active_layer (gdisp->gimage, layer); 	      init_edit_selection (tool, gdisp, bevent, EDIT_LAYER_TRANSLATE); 	    }
endif|#
directive|endif
name|tool
operator|->
name|state
operator|=
name|ACTIVE
expr_stmt|;
if|#
directive|if
literal|0
block|}
endif|#
directive|endif
block|}
comment|/* if we've got an active tool grab the pointer */
if|if
condition|(
name|tool
operator|->
name|state
operator|==
name|ACTIVE
condition|)
block|{
name|gdk_pointer_grab
argument_list|(
name|gdisp
operator|->
name|canvas
operator|->
name|window
argument_list|,
name|FALSE
argument_list|,
name|GDK_POINTER_MOTION_HINT_MASK
operator||
name|GDK_BUTTON1_MOTION_MASK
operator||
name|GDK_BUTTON_RELEASE_MASK
argument_list|,
name|NULL
argument_list|,
name|NULL
argument_list|,
name|bevent
operator|->
name|time
argument_list|)
expr_stmt|;
block|}
block|}
end_function

begin_function
specifier|static
name|void
DECL|function|move_draw_guide (GDisplay * gdisp,Guide * guide)
name|move_draw_guide
parameter_list|(
name|GDisplay
modifier|*
name|gdisp
parameter_list|,
name|Guide
modifier|*
name|guide
parameter_list|)
block|{
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
name|gint
name|w
decl_stmt|,
name|h
decl_stmt|;
name|gint
name|x
decl_stmt|,
name|y
decl_stmt|;
if|if
condition|(
operator|!
name|move_gc
condition|)
name|move_create_gc
argument_list|(
name|gdisp
argument_list|)
expr_stmt|;
if|if
condition|(
name|guide
operator|->
name|position
operator|==
operator|-
literal|1
condition|)
return|return;
name|gdisplay_transform_coords
argument_list|(
name|gdisp
argument_list|,
name|gdisp
operator|->
name|gimage
operator|->
name|width
argument_list|,
name|gdisp
operator|->
name|gimage
operator|->
name|height
argument_list|,
operator|&
name|x2
argument_list|,
operator|&
name|y2
argument_list|,
name|FALSE
argument_list|)
expr_stmt|;
name|gdk_window_get_size
argument_list|(
name|gdisp
operator|->
name|canvas
operator|->
name|window
argument_list|,
operator|&
name|w
argument_list|,
operator|&
name|h
argument_list|)
expr_stmt|;
switch|switch
condition|(
name|guide
operator|->
name|orientation
condition|)
block|{
case|case
name|ORIENTATION_HORIZONTAL
case|:
name|gdisplay_transform_coords
argument_list|(
name|gdisp
argument_list|,
literal|0
argument_list|,
name|guide
operator|->
name|position
argument_list|,
operator|&
name|x1
argument_list|,
operator|&
name|y
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
name|x2
operator|>
name|w
condition|)
name|x2
operator|=
name|w
expr_stmt|;
name|gdk_draw_line
argument_list|(
name|gdisp
operator|->
name|canvas
operator|->
name|window
argument_list|,
name|move_gc
argument_list|,
name|x1
argument_list|,
name|y
argument_list|,
name|x2
argument_list|,
name|y
argument_list|)
expr_stmt|;
break|break;
case|case
name|ORIENTATION_VERTICAL
case|:
name|gdisplay_transform_coords
argument_list|(
name|gdisp
argument_list|,
name|guide
operator|->
name|position
argument_list|,
literal|0
argument_list|,
operator|&
name|x
argument_list|,
operator|&
name|y1
argument_list|,
name|FALSE
argument_list|)
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
name|y2
operator|>
name|h
condition|)
name|y2
operator|=
name|h
expr_stmt|;
name|gdk_draw_line
argument_list|(
name|gdisp
operator|->
name|canvas
operator|->
name|window
argument_list|,
name|move_gc
argument_list|,
name|x
argument_list|,
name|y1
argument_list|,
name|x
argument_list|,
name|y2
argument_list|)
expr_stmt|;
break|break;
default|default:
name|g_warning
argument_list|(
literal|"mdg / BAD FALLTHROUGH"
argument_list|)
expr_stmt|;
break|break;
block|}
block|}
end_function

begin_function
specifier|static
name|void
DECL|function|move_tool_button_release (GimpTool * tool,GdkEventButton * bevent,GDisplay * gdisp)
name|move_tool_button_release
parameter_list|(
name|GimpTool
modifier|*
name|tool
parameter_list|,
name|GdkEventButton
modifier|*
name|bevent
parameter_list|,
name|GDisplay
modifier|*
name|gdisp
parameter_list|)
block|{
name|GimpMoveTool
modifier|*
name|move
decl_stmt|;
name|gboolean
name|delete_guide
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
name|move
operator|=
name|GIMP_MOVE_TOOL
argument_list|(
name|tool
argument_list|)
expr_stmt|;
name|gdk_flush
argument_list|()
expr_stmt|;
name|tool
operator|->
name|state
operator|=
name|INACTIVE
expr_stmt|;
name|gdk_pointer_ungrab
argument_list|(
name|bevent
operator|->
name|time
argument_list|)
expr_stmt|;
if|if
condition|(
name|move
operator|->
name|guide
condition|)
block|{
name|tool
operator|->
name|scroll_lock
operator|=
name|FALSE
expr_stmt|;
name|delete_guide
operator|=
name|FALSE
expr_stmt|;
name|gdisplay_untransform_coords
argument_list|(
name|gdisp
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
name|gdisplay_untransform_coords
argument_list|(
name|gdisp
argument_list|,
name|gdisp
operator|->
name|disp_width
argument_list|,
name|gdisp
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
name|guide
operator|->
name|orientation
condition|)
block|{
case|case
name|ORIENTATION_HORIZONTAL
case|:
if|if
condition|(
operator|(
name|move
operator|->
name|guide
operator|->
name|position
operator|<
name|y1
operator|)
operator|||
operator|(
name|move
operator|->
name|guide
operator|->
name|position
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
name|ORIENTATION_VERTICAL
case|:
if|if
condition|(
operator|(
name|move
operator|->
name|guide
operator|->
name|position
operator|<
name|x1
operator|)
operator|||
operator|(
name|move
operator|->
name|guide
operator|->
name|position
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
name|gdisplays_expose_guide
argument_list|(
name|gdisp
operator|->
name|gimage
argument_list|,
name|move
operator|->
name|guide
argument_list|)
expr_stmt|;
if|if
condition|(
name|delete_guide
condition|)
block|{
name|move_draw_guide
argument_list|(
name|gdisp
argument_list|,
name|move
operator|->
name|guide
argument_list|)
expr_stmt|;
name|gimp_image_delete_guide
argument_list|(
name|gdisp
operator|->
name|gimage
argument_list|,
name|move
operator|->
name|guide
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
name|disp
operator|=
name|NULL
expr_stmt|;
block|}
else|else
block|{
name|move_tool_motion
argument_list|(
name|tool
argument_list|,
name|NULL
argument_list|,
name|gdisp
argument_list|)
expr_stmt|;
block|}
name|selection_resume
argument_list|(
name|gdisp
operator|->
name|select
argument_list|)
expr_stmt|;
name|gdisplays_flush
argument_list|()
expr_stmt|;
if|if
condition|(
name|move
operator|->
name|guide
condition|)
name|gdisplay_draw_guide
argument_list|(
name|gdisp
argument_list|,
name|move
operator|->
name|guide
argument_list|,
name|TRUE
argument_list|)
expr_stmt|;
block|}
else|else
block|{
comment|/*  Take care of the case where the user "cancels" the action  */
if|if
condition|(
operator|!
operator|(
name|bevent
operator|->
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
name|gdisplays_flush
argument_list|()
expr_stmt|;
block|}
block|}
block|}
block|}
end_function

begin_function
specifier|static
name|void
DECL|function|move_tool_motion (GimpTool * tool,GdkEventMotion * mevent,GDisplay * gdisp)
name|move_tool_motion
parameter_list|(
name|GimpTool
modifier|*
name|tool
parameter_list|,
name|GdkEventMotion
modifier|*
name|mevent
parameter_list|,
name|GDisplay
modifier|*
name|gdisp
parameter_list|)
block|{
name|GimpMoveTool
modifier|*
name|move
decl_stmt|;
name|gint
name|x
decl_stmt|,
name|y
decl_stmt|;
name|move
operator|=
name|GIMP_MOVE_TOOL
argument_list|(
name|tool
argument_list|)
expr_stmt|;
if|if
condition|(
name|move
operator|->
name|guide
condition|)
block|{
name|move_draw_guide
argument_list|(
name|gdisp
argument_list|,
name|move
operator|->
name|guide
argument_list|)
expr_stmt|;
if|if
condition|(
name|mevent
operator|&&
name|mevent
operator|->
name|window
operator|!=
name|gdisp
operator|->
name|canvas
operator|->
name|window
condition|)
block|{
name|move
operator|->
name|guide
operator|->
name|position
operator|=
operator|-
literal|1
expr_stmt|;
return|return;
block|}
if|if
condition|(
name|mevent
condition|)
block|{
name|gdisplay_untransform_coords
argument_list|(
name|gdisp
argument_list|,
name|mevent
operator|->
name|x
argument_list|,
name|mevent
operator|->
name|y
argument_list|,
operator|&
name|x
argument_list|,
operator|&
name|y
argument_list|,
name|TRUE
argument_list|,
name|FALSE
argument_list|)
expr_stmt|;
if|if
condition|(
name|move
operator|->
name|guide
operator|->
name|orientation
operator|==
name|ORIENTATION_HORIZONTAL
condition|)
name|move
operator|->
name|guide
operator|->
name|position
operator|=
name|y
expr_stmt|;
else|else
name|move
operator|->
name|guide
operator|->
name|position
operator|=
name|x
expr_stmt|;
name|move_draw_guide
argument_list|(
name|gdisp
argument_list|,
name|move
operator|->
name|guide
argument_list|)
expr_stmt|;
block|}
block|}
block|}
end_function

begin_function
specifier|static
name|void
DECL|function|move_tool_cursor_update (GimpTool * tool,GdkEventMotion * mevent,GDisplay * gdisp)
name|move_tool_cursor_update
parameter_list|(
name|GimpTool
modifier|*
name|tool
parameter_list|,
name|GdkEventMotion
modifier|*
name|mevent
parameter_list|,
name|GDisplay
modifier|*
name|gdisp
parameter_list|)
block|{
name|GimpMoveTool
modifier|*
name|move
decl_stmt|;
name|Guide
modifier|*
name|guide
decl_stmt|;
name|GimpLayer
modifier|*
name|layer
decl_stmt|;
name|gint
name|x
decl_stmt|,
name|y
decl_stmt|;
name|move
operator|=
name|GIMP_MOVE_TOOL
argument_list|(
name|tool
argument_list|)
expr_stmt|;
name|gdisplay_untransform_coords
argument_list|(
name|gdisp
argument_list|,
name|mevent
operator|->
name|x
argument_list|,
name|mevent
operator|->
name|y
argument_list|,
operator|&
name|x
argument_list|,
operator|&
name|y
argument_list|,
name|FALSE
argument_list|,
name|FALSE
argument_list|)
expr_stmt|;
if|if
condition|(
name|mevent
operator|->
name|state
operator|&
name|GDK_MOD1_MASK
operator|&&
operator|!
name|gimage_mask_is_empty
argument_list|(
name|gdisp
operator|->
name|gimage
argument_list|)
condition|)
block|{
name|gdisplay_install_tool_cursor
argument_list|(
name|gdisp
argument_list|,
name|GIMP_MOUSE_CURSOR
argument_list|,
name|RECT_SELECT
argument_list|,
name|CURSOR_MODIFIER_MOVE
argument_list|,
name|FALSE
argument_list|)
expr_stmt|;
block|}
elseif|else
if|if
condition|(
name|mevent
operator|->
name|state
operator|&
name|GDK_SHIFT_MASK
condition|)
block|{
name|gdisplay_install_tool_cursor
argument_list|(
name|gdisp
argument_list|,
name|GIMP_MOUSE_CURSOR
argument_list|,
name|MOVE
argument_list|,
name|CURSOR_MODIFIER_NONE
argument_list|,
name|FALSE
argument_list|)
expr_stmt|;
block|}
else|else
block|{
if|if
condition|(
name|gdisp
operator|->
name|draw_guides
operator|&&
operator|(
name|guide
operator|=
name|gdisplay_find_guide
argument_list|(
name|gdisp
argument_list|,
name|mevent
operator|->
name|x
argument_list|,
name|mevent
operator|->
name|y
argument_list|)
operator|)
condition|)
block|{
name|tool
operator|->
name|gdisp
operator|=
name|gdisp
expr_stmt|;
name|gdisplay_install_tool_cursor
argument_list|(
name|gdisp
argument_list|,
name|GDK_HAND2
argument_list|,
name|TOOL_TYPE_NONE
argument_list|,
name|CURSOR_MODIFIER_HAND
argument_list|,
name|FALSE
argument_list|)
expr_stmt|;
if|if
condition|(
name|tool
operator|->
name|state
operator|!=
name|ACTIVE
condition|)
block|{
if|if
condition|(
name|move
operator|->
name|guide
condition|)
block|{
name|gdisp
operator|=
name|gdisplays_check_valid
argument_list|(
name|move
operator|->
name|disp
argument_list|,
name|move
operator|->
name|disp
operator|->
name|gimage
argument_list|)
expr_stmt|;
if|if
condition|(
name|gdisp
condition|)
name|gdisplay_draw_guide
argument_list|(
name|gdisp
argument_list|,
name|move
operator|->
name|guide
argument_list|,
name|FALSE
argument_list|)
expr_stmt|;
block|}
name|gdisp
operator|=
name|gdisp
expr_stmt|;
name|gdisplay_draw_guide
argument_list|(
name|gdisp
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
name|disp
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
name|x
argument_list|,
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
name|gdisplay_install_tool_cursor
argument_list|(
name|gdisp
argument_list|,
name|GIMP_MOUSE_CURSOR
argument_list|,
name|RECT_SELECT
argument_list|,
name|CURSOR_MODIFIER_ANCHOR
argument_list|,
name|FALSE
argument_list|)
expr_stmt|;
elseif|else
if|if
condition|(
name|layer
operator|==
name|gdisp
operator|->
name|gimage
operator|->
name|active_layer
condition|)
name|gdisplay_install_tool_cursor
argument_list|(
name|gdisp
argument_list|,
name|GIMP_MOUSE_CURSOR
argument_list|,
name|MOVE
argument_list|,
name|CURSOR_MODIFIER_NONE
argument_list|,
name|FALSE
argument_list|)
expr_stmt|;
else|else
name|gdisplay_install_tool_cursor
argument_list|(
name|gdisp
argument_list|,
name|GDK_HAND2
argument_list|,
name|TOOL_TYPE_NONE
argument_list|,
name|CURSOR_MODIFIER_HAND
argument_list|,
name|FALSE
argument_list|)
expr_stmt|;
block|}
else|else
block|{
name|gdisplay_install_tool_cursor
argument_list|(
name|gdisp
argument_list|,
name|GIMP_BAD_CURSOR
argument_list|,
name|MOVE
argument_list|,
name|CURSOR_MODIFIER_NONE
argument_list|,
name|FALSE
argument_list|)
expr_stmt|;
block|}
block|}
block|}
end_function

begin_function
specifier|static
name|void
DECL|function|move_tool_control (GimpTool * tool,ToolAction action,GDisplay * gdisp)
name|move_tool_control
parameter_list|(
name|GimpTool
modifier|*
name|tool
parameter_list|,
name|ToolAction
name|action
parameter_list|,
name|GDisplay
modifier|*
name|gdisp
parameter_list|)
block|{
name|GimpMoveTool
modifier|*
name|move
decl_stmt|;
name|move
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
name|move
operator|->
name|guide
condition|)
name|gdisplay_draw_guide
argument_list|(
name|gdisp
argument_list|,
name|move
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
break|break;
default|default:
break|break;
block|}
block|}
end_function

begin_function
specifier|static
name|void
DECL|function|move_create_gc (GDisplay * gdisp)
name|move_create_gc
parameter_list|(
name|GDisplay
modifier|*
name|gdisp
parameter_list|)
block|{
if|if
condition|(
operator|!
name|move_gc
condition|)
block|{
name|GdkGCValues
name|values
decl_stmt|;
name|values
operator|.
name|foreground
operator|.
name|pixel
operator|=
name|gdisplay_white_pixel
argument_list|(
name|gdisp
argument_list|)
expr_stmt|;
name|values
operator|.
name|function
operator|=
name|GDK_INVERT
expr_stmt|;
name|move_gc
operator|=
name|gdk_gc_new_with_values
argument_list|(
name|gdisp
operator|->
name|canvas
operator|->
name|window
argument_list|,
operator|&
name|values
argument_list|,
name|GDK_GC_FUNCTION
argument_list|)
expr_stmt|;
block|}
block|}
end_function

begin_function
name|void
DECL|function|gimp_move_tool_start_hguide (GimpTool * tool,GDisplay * gdisp)
name|gimp_move_tool_start_hguide
parameter_list|(
name|GimpTool
modifier|*
name|tool
parameter_list|,
name|GDisplay
modifier|*
name|gdisp
parameter_list|)
block|{
name|GimpMoveTool
modifier|*
name|move
decl_stmt|;
name|move
operator|=
name|GIMP_MOVE_TOOL
argument_list|(
name|tool
argument_list|)
expr_stmt|;
name|selection_pause
argument_list|(
name|gdisp
operator|->
name|select
argument_list|)
expr_stmt|;
name|tool
operator|->
name|gdisp
operator|=
name|gdisp
expr_stmt|;
name|tool
operator|->
name|scroll_lock
operator|=
name|TRUE
expr_stmt|;
if|if
condition|(
name|move
operator|->
name|guide
operator|&&
name|move
operator|->
name|disp
operator|&&
name|move
operator|->
name|disp
operator|->
name|gimage
condition|)
name|gdisplay_draw_guide
argument_list|(
name|move
operator|->
name|disp
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
name|gimp_image_add_hguide
argument_list|(
name|gdisp
operator|->
name|gimage
argument_list|)
expr_stmt|;
name|move
operator|->
name|disp
operator|=
name|gdisp
expr_stmt|;
name|tool
operator|->
name|state
operator|=
name|ACTIVE
expr_stmt|;
name|undo_push_guide
argument_list|(
name|gdisp
operator|->
name|gimage
argument_list|,
name|move
operator|->
name|guide
argument_list|)
expr_stmt|;
block|}
end_function

begin_function
name|void
DECL|function|gimp_move_tool_start_vguide (GimpTool * tool,GDisplay * gdisp)
name|gimp_move_tool_start_vguide
parameter_list|(
name|GimpTool
modifier|*
name|tool
parameter_list|,
name|GDisplay
modifier|*
name|gdisp
parameter_list|)
block|{
name|GimpMoveTool
modifier|*
name|move
decl_stmt|;
name|move
operator|=
name|GIMP_MOVE_TOOL
argument_list|(
name|tool
argument_list|)
expr_stmt|;
name|selection_pause
argument_list|(
name|gdisp
operator|->
name|select
argument_list|)
expr_stmt|;
name|tool
operator|->
name|gdisp
operator|=
name|gdisp
expr_stmt|;
name|tool
operator|->
name|scroll_lock
operator|=
name|TRUE
expr_stmt|;
if|if
condition|(
name|move
operator|->
name|guide
operator|&&
name|move
operator|->
name|disp
operator|&&
name|move
operator|->
name|disp
operator|->
name|gimage
condition|)
name|gdisplay_draw_guide
argument_list|(
name|move
operator|->
name|disp
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
name|gimp_image_add_vguide
argument_list|(
name|gdisp
operator|->
name|gimage
argument_list|)
expr_stmt|;
name|move
operator|->
name|disp
operator|=
name|gdisp
expr_stmt|;
name|tool
operator|->
name|state
operator|=
name|ACTIVE
expr_stmt|;
name|undo_push_guide
argument_list|(
name|gdisp
operator|->
name|gimage
argument_list|,
name|move
operator|->
name|guide
argument_list|)
expr_stmt|;
block|}
end_function

end_unit

