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
file|<string.h>
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
file|"errors.h"
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
file|"scan_convert.h"
end_include

begin_include
include|#
directive|include
file|"gimpeditselectiontool.h"
end_include

begin_include
include|#
directive|include
file|"gimpfreeselecttool.h"
end_include

begin_include
include|#
directive|include
file|"selection_options.h"
end_include

begin_include
include|#
directive|include
file|"tool_options.h"
end_include

begin_include
include|#
directive|include
file|"tool_manager.h"
end_include

begin_include
include|#
directive|include
file|"libgimp/gimpintl.h"
end_include

begin_define
DECL|macro|WANT_FREE_SELECT_BITS
define|#
directive|define
name|WANT_FREE_SELECT_BITS
end_define

begin_include
include|#
directive|include
file|"icons.h"
end_include

begin_define
DECL|macro|DEFAULT_MAX_INC
define|#
directive|define
name|DEFAULT_MAX_INC
value|1024
end_define

begin_define
DECL|macro|SUPERSAMPLE
define|#
directive|define
name|SUPERSAMPLE
value|3
end_define

begin_define
DECL|macro|SUPERSAMPLE2
define|#
directive|define
name|SUPERSAMPLE2
value|9
end_define

begin_function_decl
specifier|static
name|void
name|gimp_free_select_tool_class_init
parameter_list|(
name|GimpFreeSelectToolClass
modifier|*
name|klass
parameter_list|)
function_decl|;
end_function_decl

begin_function_decl
specifier|static
name|void
name|gimp_free_select_tool_init
parameter_list|(
name|GimpFreeSelectTool
modifier|*
name|free_select
parameter_list|)
function_decl|;
end_function_decl

begin_function_decl
specifier|static
name|void
name|gimp_free_select_tool_destroy
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
name|gimp_free_select_tool_button_press
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
name|gimp_free_select_tool_button_release
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
name|gimp_free_select_tool_motion
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
name|gimp_free_select_tool_add_point
parameter_list|(
name|GimpFreeSelectTool
modifier|*
name|free_sel
parameter_list|,
name|gint
name|x
parameter_list|,
name|gint
name|y
parameter_list|)
function_decl|;
end_function_decl

begin_function_decl
specifier|static
name|GimpChannel
modifier|*
name|scan_convert
parameter_list|(
name|GimpImage
modifier|*
name|gimage
parameter_list|,
name|gint
name|num_pts
parameter_list|,
name|ScanConvertPoint
modifier|*
name|pts
parameter_list|,
name|gint
name|width
parameter_list|,
name|gint
name|height
parameter_list|,
name|gboolean
name|antialias
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

begin_decl_stmt
DECL|variable|free_options
specifier|static
name|SelectionOptions
modifier|*
name|free_options
init|=
name|NULL
decl_stmt|;
end_decl_stmt

begin_comment
comment|/*  public functions  */
end_comment

begin_function
name|void
DECL|function|gimp_free_select_tool_register (void)
name|gimp_free_select_tool_register
parameter_list|(
name|void
parameter_list|)
block|{
name|tool_manager_register_tool
argument_list|(
name|GIMP_TYPE_FREE_SELECT_TOOL
argument_list|,
name|FALSE
argument_list|,
literal|"gimp:free_select_tool"
argument_list|,
name|_
argument_list|(
literal|"Free Select"
argument_list|)
argument_list|,
name|_
argument_list|(
literal|"Select hand-drawn regions"
argument_list|)
argument_list|,
name|_
argument_list|(
literal|"/Tools/Selection Tools/Free Select"
argument_list|)
argument_list|,
literal|"F"
argument_list|,
name|NULL
argument_list|,
literal|"tools/free_select.html"
argument_list|,
operator|(
specifier|const
name|gchar
operator|*
operator|*
operator|)
name|free_select_bits
argument_list|)
expr_stmt|;
block|}
end_function

begin_function
name|GtkType
DECL|function|gimp_free_select_tool_get_type (void)
name|gimp_free_select_tool_get_type
parameter_list|(
name|void
parameter_list|)
block|{
specifier|static
name|GtkType
name|free_select_type
init|=
literal|0
decl_stmt|;
if|if
condition|(
operator|!
name|free_select_type
condition|)
block|{
name|GtkTypeInfo
name|free_select_info
init|=
block|{
literal|"GimpFreeSelectTool"
block|,
sizeof|sizeof
argument_list|(
name|GimpFreeSelectTool
argument_list|)
block|,
sizeof|sizeof
argument_list|(
name|GimpFreeSelectToolClass
argument_list|)
block|,
operator|(
name|GtkClassInitFunc
operator|)
name|gimp_free_select_tool_class_init
block|,
operator|(
name|GtkObjectInitFunc
operator|)
name|gimp_free_select_tool_init
block|,
comment|/* reserved_1 */
name|NULL
block|,
comment|/* reserved_2 */
name|NULL
block|}
decl_stmt|;
name|free_select_type
operator|=
name|gtk_type_unique
argument_list|(
name|GIMP_TYPE_SELECTION_TOOL
argument_list|,
operator|&
name|free_select_info
argument_list|)
expr_stmt|;
block|}
return|return
name|free_select_type
return|;
block|}
end_function

begin_function
name|void
DECL|function|free_select (GimpImage * gimage,gint num_pts,ScanConvertPoint * pts,SelectOps op,gboolean antialias,gboolean feather,gdouble feather_radius)
name|free_select
parameter_list|(
name|GimpImage
modifier|*
name|gimage
parameter_list|,
name|gint
name|num_pts
parameter_list|,
name|ScanConvertPoint
modifier|*
name|pts
parameter_list|,
name|SelectOps
name|op
parameter_list|,
name|gboolean
name|antialias
parameter_list|,
name|gboolean
name|feather
parameter_list|,
name|gdouble
name|feather_radius
parameter_list|)
block|{
name|GimpChannel
modifier|*
name|mask
decl_stmt|;
comment|/*  if applicable, replace the current selection  */
comment|/*  or insure that a floating selection is anchored down...  */
if|if
condition|(
name|op
operator|==
name|SELECTION_REPLACE
condition|)
name|gimage_mask_clear
argument_list|(
name|gimage
argument_list|)
expr_stmt|;
else|else
name|gimage_mask_undo
argument_list|(
name|gimage
argument_list|)
expr_stmt|;
name|mask
operator|=
name|scan_convert
argument_list|(
name|gimage
argument_list|,
name|num_pts
argument_list|,
name|pts
argument_list|,
name|gimage
operator|->
name|width
argument_list|,
name|gimage
operator|->
name|height
argument_list|,
name|antialias
argument_list|)
expr_stmt|;
if|if
condition|(
name|mask
condition|)
block|{
if|if
condition|(
name|feather
condition|)
name|gimp_channel_feather
argument_list|(
name|mask
argument_list|,
name|gimp_image_get_mask
argument_list|(
name|gimage
argument_list|)
argument_list|,
name|feather_radius
argument_list|,
name|feather_radius
argument_list|,
name|op
argument_list|,
literal|0
argument_list|,
literal|0
argument_list|)
expr_stmt|;
else|else
name|gimp_channel_combine_mask
argument_list|(
name|gimp_image_get_mask
argument_list|(
name|gimage
argument_list|)
argument_list|,
name|mask
argument_list|,
name|op
argument_list|,
literal|0
argument_list|,
literal|0
argument_list|)
expr_stmt|;
name|gtk_object_unref
argument_list|(
name|GTK_OBJECT
argument_list|(
name|mask
argument_list|)
argument_list|)
expr_stmt|;
block|}
block|}
end_function

begin_comment
comment|/*  private functions  */
end_comment

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
name|GtkObjectClass
modifier|*
name|object_class
decl_stmt|;
name|GimpToolClass
modifier|*
name|tool_class
decl_stmt|;
name|GimpDrawToolClass
modifier|*
name|draw_tool_class
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
name|draw_tool_class
operator|=
operator|(
name|GimpDrawToolClass
operator|*
operator|)
name|klass
expr_stmt|;
name|parent_class
operator|=
name|gtk_type_class
argument_list|(
name|GIMP_TYPE_SELECTION_TOOL
argument_list|)
expr_stmt|;
name|object_class
operator|->
name|destroy
operator|=
name|gimp_free_select_tool_destroy
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
decl_stmt|;
name|GimpSelectionTool
modifier|*
name|select_tool
decl_stmt|;
name|tool
operator|=
name|GIMP_TOOL
argument_list|(
name|free_select
argument_list|)
expr_stmt|;
name|select_tool
operator|=
name|GIMP_SELECTION_TOOL
argument_list|(
name|free_select
argument_list|)
expr_stmt|;
if|if
condition|(
operator|!
name|free_options
condition|)
block|{
name|free_options
operator|=
name|selection_options_new
argument_list|(
name|GIMP_TYPE_FREE_SELECT_TOOL
argument_list|,
name|selection_options_reset
argument_list|)
expr_stmt|;
name|tool_manager_register_tool_options
argument_list|(
name|GIMP_TYPE_FREE_SELECT_TOOL
argument_list|,
operator|(
name|ToolOptions
operator|*
operator|)
name|free_options
argument_list|)
expr_stmt|;
block|}
name|tool
operator|->
name|tool_cursor
operator|=
name|GIMP_FREE_SELECT_TOOL_CURSOR
expr_stmt|;
name|tool
operator|->
name|scroll_lock
operator|=
name|TRUE
expr_stmt|;
comment|/*  Do not allow scrolling  */
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
DECL|function|gimp_free_select_tool_destroy (GtkObject * object)
name|gimp_free_select_tool_destroy
parameter_list|(
name|GtkObject
modifier|*
name|object
parameter_list|)
block|{
name|GimpFreeSelectTool
modifier|*
name|free_sel
decl_stmt|;
name|free_sel
operator|=
name|GIMP_FREE_SELECT_TOOL
argument_list|(
name|object
argument_list|)
expr_stmt|;
name|g_free
argument_list|(
name|free_sel
operator|->
name|points
argument_list|)
expr_stmt|;
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

begin_function
specifier|static
name|void
DECL|function|gimp_free_select_tool_button_press (GimpTool * tool,GdkEventButton * bevent,GDisplay * gdisp)
name|gimp_free_select_tool_button_press
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
name|GimpFreeSelectTool
modifier|*
name|free_sel
decl_stmt|;
name|free_sel
operator|=
name|GIMP_FREE_SELECT_TOOL
argument_list|(
name|tool
argument_list|)
expr_stmt|;
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
name|tool
operator|->
name|state
operator|=
name|ACTIVE
expr_stmt|;
name|tool
operator|->
name|gdisp
operator|=
name|gdisp
expr_stmt|;
switch|switch
condition|(
name|GIMP_SELECTION_TOOL
argument_list|(
name|tool
argument_list|)
operator|->
name|op
condition|)
block|{
case|case
name|SELECTION_MOVE_MASK
case|:
name|init_edit_selection
argument_list|(
name|tool
argument_list|,
name|gdisp
argument_list|,
name|bevent
argument_list|,
name|EDIT_MASK_TRANSLATE
argument_list|)
expr_stmt|;
return|return;
case|case
name|SELECTION_MOVE
case|:
name|init_edit_selection
argument_list|(
name|tool
argument_list|,
name|gdisp
argument_list|,
name|bevent
argument_list|,
name|EDIT_MASK_TO_LAYER_TRANSLATE
argument_list|)
expr_stmt|;
return|return;
default|default:
break|break;
block|}
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
name|bevent
operator|->
name|x
argument_list|,
name|bevent
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
name|gdisp
operator|->
name|canvas
operator|->
name|window
argument_list|)
expr_stmt|;
block|}
end_function

begin_function
specifier|static
name|void
DECL|function|gimp_free_select_tool_button_release (GimpTool * tool,GdkEventButton * bevent,GDisplay * gdisp)
name|gimp_free_select_tool_button_release
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
name|GimpFreeSelectTool
modifier|*
name|free_sel
decl_stmt|;
name|ScanConvertPoint
modifier|*
name|pts
decl_stmt|;
name|gint
name|i
decl_stmt|;
name|free_sel
operator|=
name|GIMP_FREE_SELECT_TOOL
argument_list|(
name|tool
argument_list|)
expr_stmt|;
name|gdk_pointer_ungrab
argument_list|(
name|bevent
operator|->
name|time
argument_list|)
expr_stmt|;
name|gdk_flush
argument_list|()
expr_stmt|;
name|gimp_draw_tool_stop
argument_list|(
name|GIMP_DRAW_TOOL
argument_list|(
name|tool
argument_list|)
argument_list|)
expr_stmt|;
name|tool
operator|->
name|state
operator|=
name|INACTIVE
expr_stmt|;
comment|/*  First take care of the case where the user "cancels" the action  */
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
name|free_sel
operator|->
name|num_points
operator|==
literal|1
condition|)
block|{
comment|/*  If there is a floating selection, anchor it  */
if|if
condition|(
name|gimp_image_floating_sel
argument_list|(
name|gdisp
operator|->
name|gimage
argument_list|)
condition|)
name|floating_sel_anchor
argument_list|(
name|gimp_image_floating_sel
argument_list|(
name|gdisp
operator|->
name|gimage
argument_list|)
argument_list|)
expr_stmt|;
comment|/*  Otherwise, clear the selection mask  */
else|else
name|gimage_mask_clear
argument_list|(
name|gdisp
operator|->
name|gimage
argument_list|)
expr_stmt|;
name|gdisplays_flush
argument_list|()
expr_stmt|;
return|return;
block|}
name|pts
operator|=
name|g_new
argument_list|(
name|ScanConvertPoint
argument_list|,
name|free_sel
operator|->
name|num_points
argument_list|)
expr_stmt|;
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
name|gdisplay_untransform_coords_f
argument_list|(
name|gdisp
argument_list|,
name|free_sel
operator|->
name|points
index|[
name|i
index|]
operator|.
name|x
argument_list|,
name|free_sel
operator|->
name|points
index|[
name|i
index|]
operator|.
name|y
argument_list|,
operator|&
name|pts
index|[
name|i
index|]
operator|.
name|x
argument_list|,
operator|&
name|pts
index|[
name|i
index|]
operator|.
name|y
argument_list|,
name|FALSE
argument_list|)
expr_stmt|;
block|}
name|free_select
argument_list|(
name|gdisp
operator|->
name|gimage
argument_list|,
name|free_sel
operator|->
name|num_points
argument_list|,
name|pts
argument_list|,
name|GIMP_SELECTION_TOOL
argument_list|(
name|tool
argument_list|)
operator|->
name|op
argument_list|,
name|free_options
operator|->
name|antialias
argument_list|,
name|free_options
operator|->
name|feather
argument_list|,
name|free_options
operator|->
name|feather_radius
argument_list|)
expr_stmt|;
name|g_free
argument_list|(
name|pts
argument_list|)
expr_stmt|;
name|gdisplays_flush
argument_list|()
expr_stmt|;
block|}
block|}
end_function

begin_function
specifier|static
name|void
DECL|function|gimp_free_select_tool_motion (GimpTool * tool,GdkEventMotion * mevent,GDisplay * gdisp)
name|gimp_free_select_tool_motion
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
name|GimpFreeSelectTool
modifier|*
name|free_sel
decl_stmt|;
name|GimpSelectionTool
modifier|*
name|sel_tool
decl_stmt|;
name|GimpDrawTool
modifier|*
name|draw_tool
decl_stmt|;
name|free_sel
operator|=
name|GIMP_FREE_SELECT_TOOL
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
name|draw_tool
operator|=
name|GIMP_DRAW_TOOL
argument_list|(
name|tool
argument_list|)
expr_stmt|;
comment|/*  needed for immediate cursor update on modifier event  */
name|sel_tool
operator|->
name|current_x
operator|=
name|mevent
operator|->
name|x
expr_stmt|;
name|sel_tool
operator|->
name|current_y
operator|=
name|mevent
operator|->
name|y
expr_stmt|;
if|if
condition|(
name|tool
operator|->
name|state
operator|!=
name|ACTIVE
condition|)
return|return;
if|if
condition|(
name|sel_tool
operator|->
name|op
operator|==
name|SELECTION_ANCHOR
condition|)
block|{
name|sel_tool
operator|->
name|op
operator|=
name|SELECTION_REPLACE
expr_stmt|;
name|gimp_tool_cursor_update
argument_list|(
name|tool
argument_list|,
name|mevent
argument_list|,
name|gdisp
argument_list|)
expr_stmt|;
block|}
name|gimp_free_select_tool_add_point
argument_list|(
name|free_sel
argument_list|,
name|mevent
operator|->
name|x
argument_list|,
name|mevent
operator|->
name|y
argument_list|)
expr_stmt|;
name|gdk_draw_line
argument_list|(
name|draw_tool
operator|->
name|win
argument_list|,
name|draw_tool
operator|->
name|gc
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
argument_list|)
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
decl_stmt|;
name|gint
name|i
decl_stmt|;
name|free_sel
operator|=
name|GIMP_FREE_SELECT_TOOL
argument_list|(
name|draw_tool
argument_list|)
expr_stmt|;
for|for
control|(
name|i
operator|=
literal|1
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
name|gdk_draw_line
argument_list|(
name|draw_tool
operator|->
name|win
argument_list|,
name|draw_tool
operator|->
name|gc
argument_list|,
name|free_sel
operator|->
name|points
index|[
name|i
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
name|i
operator|-
literal|1
index|]
operator|.
name|y
argument_list|,
name|free_sel
operator|->
name|points
index|[
name|i
index|]
operator|.
name|x
argument_list|,
name|free_sel
operator|->
name|points
index|[
name|i
index|]
operator|.
name|y
argument_list|)
expr_stmt|;
block|}
block|}
end_function

begin_function
specifier|static
name|void
DECL|function|gimp_free_select_tool_add_point (GimpFreeSelectTool * free_sel,gint x,gint y)
name|gimp_free_select_tool_add_point
parameter_list|(
name|GimpFreeSelectTool
modifier|*
name|free_sel
parameter_list|,
name|gint
name|x
parameter_list|,
name|gint
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
operator|(
name|GdkPoint
operator|*
operator|)
name|g_realloc
argument_list|(
operator|(
name|void
operator|*
operator|)
name|free_sel
operator|->
name|points
argument_list|,
sizeof|sizeof
argument_list|(
name|GdkPoint
argument_list|)
operator|*
name|free_sel
operator|->
name|max_segs
argument_list|)
expr_stmt|;
if|if
condition|(
operator|!
name|free_sel
operator|->
name|points
condition|)
name|gimp_fatal_error
argument_list|(
literal|"%s(): Unable to reallocate points array"
argument_list|,
name|G_GNUC_FUNCTION
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
name|GimpChannel
modifier|*
DECL|function|scan_convert (GimpImage * gimage,gint num_pts,ScanConvertPoint * pts,gint width,gint height,gboolean antialias)
name|scan_convert
parameter_list|(
name|GimpImage
modifier|*
name|gimage
parameter_list|,
name|gint
name|num_pts
parameter_list|,
name|ScanConvertPoint
modifier|*
name|pts
parameter_list|,
name|gint
name|width
parameter_list|,
name|gint
name|height
parameter_list|,
name|gboolean
name|antialias
parameter_list|)
block|{
name|GimpChannel
modifier|*
name|mask
decl_stmt|;
name|ScanConverter
modifier|*
name|sc
decl_stmt|;
name|sc
operator|=
name|scan_converter_new
argument_list|(
name|width
argument_list|,
name|height
argument_list|,
name|antialias
condition|?
name|SUPERSAMPLE
else|:
literal|1
argument_list|)
expr_stmt|;
name|scan_converter_add_points
argument_list|(
name|sc
argument_list|,
name|num_pts
argument_list|,
name|pts
argument_list|)
expr_stmt|;
name|mask
operator|=
name|scan_converter_to_channel
argument_list|(
name|sc
argument_list|,
name|gimage
argument_list|)
expr_stmt|;
name|scan_converter_free
argument_list|(
name|sc
argument_list|)
expr_stmt|;
return|return
name|mask
return|;
block|}
end_function

end_unit

