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
file|"base/boundary.h"
end_include

begin_include
include|#
directive|include
file|"base/pixel-region.h"
end_include

begin_include
include|#
directive|include
file|"base/tile-manager.h"
end_include

begin_include
include|#
directive|include
file|"base/tile.h"
end_include

begin_include
include|#
directive|include
file|"core/gimp.h"
end_include

begin_include
include|#
directive|include
file|"core/gimpchannel.h"
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
file|"core/gimpimage-contiguous-region.h"
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
file|"gimpeditselectiontool.h"
end_include

begin_include
include|#
directive|include
file|"gimpfuzzyselecttool.h"
end_include

begin_include
include|#
directive|include
file|"gimptool.h"
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
file|"gimprc.h"
end_include

begin_include
include|#
directive|include
file|"libgimp/gimpintl.h"
end_include

begin_function_decl
specifier|static
name|void
name|gimp_fuzzy_select_tool_class_init
parameter_list|(
name|GimpFuzzySelectToolClass
modifier|*
name|klass
parameter_list|)
function_decl|;
end_function_decl

begin_function_decl
specifier|static
name|void
name|gimp_fuzzy_select_tool_init
parameter_list|(
name|GimpFuzzySelectTool
modifier|*
name|fuzzy_select
parameter_list|)
function_decl|;
end_function_decl

begin_function_decl
specifier|static
name|void
name|gimp_fuzzy_select_tool_finalize
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
name|gimp_fuzzy_select_tool_button_press
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
name|gimp_fuzzy_select_tool_button_release
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
name|gimp_fuzzy_select_tool_motion
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
name|gimp_fuzzy_select_tool_draw
parameter_list|(
name|GimpDrawTool
modifier|*
name|draw_tool
parameter_list|)
function_decl|;
end_function_decl

begin_function_decl
specifier|static
name|GdkSegment
modifier|*
name|fuzzy_select_calculate
parameter_list|(
name|GimpFuzzySelectTool
modifier|*
name|fuzzy_sel
parameter_list|,
name|GimpDisplay
modifier|*
name|gdisp
parameter_list|,
name|gint
modifier|*
name|nsegs
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
comment|/*  the fuzzy selection tool options  */
end_comment

begin_decl_stmt
DECL|variable|fuzzy_options
specifier|static
name|SelectionOptions
modifier|*
name|fuzzy_options
init|=
name|NULL
decl_stmt|;
end_decl_stmt

begin_comment
comment|/*  XSegments which make up the fuzzy selection boundary  */
end_comment

begin_decl_stmt
DECL|variable|segs
specifier|static
name|GdkSegment
modifier|*
name|segs
init|=
name|NULL
decl_stmt|;
end_decl_stmt

begin_decl_stmt
DECL|variable|num_segs
specifier|static
name|gint
name|num_segs
init|=
literal|0
decl_stmt|;
end_decl_stmt

begin_comment
comment|/*  public functions  */
end_comment

begin_function
name|void
DECL|function|gimp_fuzzy_select_tool_register (Gimp * gimp)
name|gimp_fuzzy_select_tool_register
parameter_list|(
name|Gimp
modifier|*
name|gimp
parameter_list|)
block|{
name|tool_manager_register_tool
argument_list|(
name|gimp
argument_list|,
name|GIMP_TYPE_FUZZY_SELECT_TOOL
argument_list|,
name|FALSE
argument_list|,
literal|"gimp:fuzzy_select_tool"
argument_list|,
name|_
argument_list|(
literal|"Fuzzy Select"
argument_list|)
argument_list|,
name|_
argument_list|(
literal|"Select contiguous regions"
argument_list|)
argument_list|,
name|_
argument_list|(
literal|"/Tools/Selection Tools/Fuzzy Select"
argument_list|)
argument_list|,
literal|"Z"
argument_list|,
name|NULL
argument_list|,
literal|"tools/fuzzy_select.html"
argument_list|,
name|GIMP_STOCK_TOOL_FUZZY_SELECT
argument_list|)
expr_stmt|;
block|}
end_function

begin_function
name|GType
DECL|function|gimp_fuzzy_select_tool_get_type (void)
name|gimp_fuzzy_select_tool_get_type
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
name|GimpFuzzySelectToolClass
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
name|gimp_fuzzy_select_tool_class_init
block|,
name|NULL
block|,
comment|/* class_finalize */
name|NULL
block|,
comment|/* class_data     */
sizeof|sizeof
argument_list|(
name|GimpFuzzySelectTool
argument_list|)
block|,
literal|0
block|,
comment|/* n_preallocs    */
operator|(
name|GInstanceInitFunc
operator|)
name|gimp_fuzzy_select_tool_init
block|,       }
decl_stmt|;
name|tool_type
operator|=
name|g_type_register_static
argument_list|(
name|GIMP_TYPE_SELECTION_TOOL
argument_list|,
literal|"GimpFuzzySelectTool"
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
DECL|function|gimp_fuzzy_select_tool_class_init (GimpFuzzySelectToolClass * klass)
name|gimp_fuzzy_select_tool_class_init
parameter_list|(
name|GimpFuzzySelectToolClass
modifier|*
name|klass
parameter_list|)
block|{
name|GObjectClass
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
name|G_OBJECT_CLASS
argument_list|(
name|klass
argument_list|)
expr_stmt|;
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
name|object_class
operator|->
name|finalize
operator|=
name|gimp_fuzzy_select_tool_finalize
expr_stmt|;
name|tool_class
operator|->
name|button_press
operator|=
name|gimp_fuzzy_select_tool_button_press
expr_stmt|;
name|tool_class
operator|->
name|button_release
operator|=
name|gimp_fuzzy_select_tool_button_release
expr_stmt|;
name|tool_class
operator|->
name|motion
operator|=
name|gimp_fuzzy_select_tool_motion
expr_stmt|;
name|draw_tool_class
operator|->
name|draw
operator|=
name|gimp_fuzzy_select_tool_draw
expr_stmt|;
block|}
end_function

begin_function
specifier|static
name|void
DECL|function|gimp_fuzzy_select_tool_init (GimpFuzzySelectTool * fuzzy_select)
name|gimp_fuzzy_select_tool_init
parameter_list|(
name|GimpFuzzySelectTool
modifier|*
name|fuzzy_select
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
name|fuzzy_select
argument_list|)
expr_stmt|;
name|select_tool
operator|=
name|GIMP_SELECTION_TOOL
argument_list|(
name|fuzzy_select
argument_list|)
expr_stmt|;
if|if
condition|(
operator|!
name|fuzzy_options
condition|)
block|{
name|fuzzy_options
operator|=
name|selection_options_new
argument_list|(
name|GIMP_TYPE_FUZZY_SELECT_TOOL
argument_list|,
name|selection_options_reset
argument_list|)
expr_stmt|;
name|tool_manager_register_tool_options
argument_list|(
name|GIMP_TYPE_FUZZY_SELECT_TOOL
argument_list|,
operator|(
name|GimpToolOptions
operator|*
operator|)
name|fuzzy_options
argument_list|)
expr_stmt|;
block|}
name|tool
operator|->
name|tool_cursor
operator|=
name|GIMP_FUZZY_SELECT_TOOL_CURSOR
expr_stmt|;
name|tool
operator|->
name|scroll_lock
operator|=
name|TRUE
expr_stmt|;
comment|/*  Do not allow scrolling  */
name|fuzzy_select
operator|->
name|fuzzy_mask
operator|=
name|NULL
expr_stmt|;
name|fuzzy_select
operator|->
name|x
operator|=
literal|0
expr_stmt|;
name|fuzzy_select
operator|->
name|y
operator|=
literal|0
expr_stmt|;
name|fuzzy_select
operator|->
name|first_x
operator|=
literal|0
expr_stmt|;
name|fuzzy_select
operator|->
name|first_y
operator|=
literal|0
expr_stmt|;
name|fuzzy_select
operator|->
name|first_threshold
operator|=
literal|0.0
expr_stmt|;
block|}
end_function

begin_function
specifier|static
name|void
DECL|function|gimp_fuzzy_select_tool_finalize (GObject * object)
name|gimp_fuzzy_select_tool_finalize
parameter_list|(
name|GObject
modifier|*
name|object
parameter_list|)
block|{
name|GimpFuzzySelectTool
modifier|*
name|fuzzy_sel
decl_stmt|;
name|fuzzy_sel
operator|=
name|GIMP_FUZZY_SELECT_TOOL
argument_list|(
name|object
argument_list|)
expr_stmt|;
if|if
condition|(
name|fuzzy_sel
operator|->
name|fuzzy_mask
condition|)
block|{
name|g_object_unref
argument_list|(
name|G_OBJECT
argument_list|(
name|fuzzy_sel
operator|->
name|fuzzy_mask
argument_list|)
argument_list|)
expr_stmt|;
name|fuzzy_sel
operator|->
name|fuzzy_mask
operator|=
name|NULL
expr_stmt|;
block|}
block|}
end_function

begin_function
specifier|static
name|void
DECL|function|gimp_fuzzy_select_tool_button_press (GimpTool * tool,GimpCoords * coords,guint32 time,GdkModifierType state,GimpDisplay * gdisp)
name|gimp_fuzzy_select_tool_button_press
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
name|GimpFuzzySelectTool
modifier|*
name|fuzzy_sel
decl_stmt|;
name|GimpDisplayShell
modifier|*
name|shell
decl_stmt|;
name|fuzzy_sel
operator|=
name|GIMP_FUZZY_SELECT_TOOL
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
name|fuzzy_sel
operator|->
name|x
operator|=
name|coords
operator|->
name|x
expr_stmt|;
name|fuzzy_sel
operator|->
name|y
operator|=
name|coords
operator|->
name|y
expr_stmt|;
name|fuzzy_sel
operator|->
name|first_x
operator|=
name|fuzzy_sel
operator|->
name|x
expr_stmt|;
name|fuzzy_sel
operator|->
name|first_y
operator|=
name|fuzzy_sel
operator|->
name|y
expr_stmt|;
name|fuzzy_sel
operator|->
name|first_threshold
operator|=
name|fuzzy_options
operator|->
name|threshold
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
name|gdk_pointer_grab
argument_list|(
name|shell
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
name|time
argument_list|)
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
name|coords
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
name|coords
argument_list|,
name|EDIT_MASK_TO_LAYER_TRANSLATE
argument_list|)
expr_stmt|;
return|return;
default|default:
break|break;
block|}
comment|/*  calculate the region boundary  */
name|segs
operator|=
name|fuzzy_select_calculate
argument_list|(
name|fuzzy_sel
argument_list|,
name|gdisp
argument_list|,
operator|&
name|num_segs
argument_list|)
expr_stmt|;
name|gimp_draw_tool_start
argument_list|(
name|GIMP_DRAW_TOOL
argument_list|(
name|tool
argument_list|)
argument_list|,
name|shell
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
DECL|function|gimp_fuzzy_select_tool_button_release (GimpTool * tool,GimpCoords * coords,guint32 time,GdkModifierType state,GimpDisplay * gdisp)
name|gimp_fuzzy_select_tool_button_release
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
name|GimpFuzzySelectTool
modifier|*
name|fuzzy_sel
decl_stmt|;
name|GimpDrawable
modifier|*
name|drawable
decl_stmt|;
name|fuzzy_sel
operator|=
name|GIMP_FUZZY_SELECT_TOOL
argument_list|(
name|tool
argument_list|)
expr_stmt|;
name|gdk_pointer_ungrab
argument_list|(
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
name|state
operator|&
name|GDK_BUTTON3_MASK
operator|)
condition|)
block|{
name|drawable
operator|=
name|gimp_image_active_drawable
argument_list|(
name|gdisp
operator|->
name|gimage
argument_list|)
expr_stmt|;
name|gimp_image_mask_select_channel
argument_list|(
name|gdisp
operator|->
name|gimage
argument_list|,
name|drawable
argument_list|,
name|fuzzy_options
operator|->
name|sample_merged
argument_list|,
name|fuzzy_sel
operator|->
name|fuzzy_mask
argument_list|,
name|GIMP_SELECTION_TOOL
argument_list|(
name|tool
argument_list|)
operator|->
name|op
argument_list|,
name|fuzzy_options
operator|->
name|feather
argument_list|,
name|fuzzy_options
operator|->
name|feather_radius
argument_list|,
name|fuzzy_options
operator|->
name|feather_radius
argument_list|)
expr_stmt|;
name|g_object_unref
argument_list|(
name|G_OBJECT
argument_list|(
name|fuzzy_sel
operator|->
name|fuzzy_mask
argument_list|)
argument_list|)
expr_stmt|;
name|fuzzy_sel
operator|->
name|fuzzy_mask
operator|=
name|NULL
expr_stmt|;
name|gdisplays_flush
argument_list|()
expr_stmt|;
block|}
comment|/*  If the segment array is allocated, free it  */
if|if
condition|(
name|segs
condition|)
block|{
name|g_free
argument_list|(
name|segs
argument_list|)
expr_stmt|;
name|segs
operator|=
name|NULL
expr_stmt|;
block|}
block|}
end_function

begin_function
specifier|static
name|void
DECL|function|gimp_fuzzy_select_tool_motion (GimpTool * tool,GimpCoords * coords,guint32 time,GdkModifierType state,GimpDisplay * gdisp)
name|gimp_fuzzy_select_tool_motion
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
name|GimpFuzzySelectTool
modifier|*
name|fuzzy_sel
decl_stmt|;
name|GimpSelectionTool
modifier|*
name|sel_tool
decl_stmt|;
name|GdkSegment
modifier|*
name|new_segs
decl_stmt|;
name|gint
name|num_new_segs
decl_stmt|;
name|gint
name|diff_x
decl_stmt|,
name|diff_y
decl_stmt|;
name|gdouble
name|diff
decl_stmt|;
specifier|static
name|guint32
name|last_time
init|=
literal|0
decl_stmt|;
name|fuzzy_sel
operator|=
name|GIMP_FUZZY_SELECT_TOOL
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
if|if
condition|(
name|tool
operator|->
name|state
operator|!=
name|ACTIVE
condition|)
return|return;
comment|/* don't let the events come in too fast, ignore below a delay of 100 ms */
if|if
condition|(
name|ABS
argument_list|(
name|time
operator|-
name|last_time
argument_list|)
operator|<
literal|100
condition|)
return|return;
name|last_time
operator|=
name|time
expr_stmt|;
name|diff_x
operator|=
name|coords
operator|->
name|x
operator|-
name|fuzzy_sel
operator|->
name|first_x
expr_stmt|;
name|diff_y
operator|=
name|coords
operator|->
name|y
operator|-
name|fuzzy_sel
operator|->
name|first_y
expr_stmt|;
name|diff
operator|=
operator|(
operator|(
name|ABS
argument_list|(
name|diff_x
argument_list|)
operator|>
name|ABS
argument_list|(
name|diff_y
argument_list|)
operator|)
condition|?
name|diff_x
else|:
name|diff_y
operator|)
operator|/
literal|2.0
expr_stmt|;
name|gtk_adjustment_set_value
argument_list|(
name|GTK_ADJUSTMENT
argument_list|(
name|fuzzy_options
operator|->
name|threshold_w
argument_list|)
argument_list|,
name|fuzzy_sel
operator|->
name|first_threshold
operator|+
name|diff
argument_list|)
expr_stmt|;
comment|/*  calculate the new fuzzy boundary  */
name|new_segs
operator|=
name|fuzzy_select_calculate
argument_list|(
name|fuzzy_sel
argument_list|,
name|gdisp
argument_list|,
operator|&
name|num_new_segs
argument_list|)
expr_stmt|;
name|gimp_draw_tool_pause
argument_list|(
name|GIMP_DRAW_TOOL
argument_list|(
name|tool
argument_list|)
argument_list|)
expr_stmt|;
comment|/*  make sure the XSegment array is freed before we assign the new one  */
if|if
condition|(
name|segs
condition|)
name|g_free
argument_list|(
name|segs
argument_list|)
expr_stmt|;
name|segs
operator|=
name|new_segs
expr_stmt|;
name|num_segs
operator|=
name|num_new_segs
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
end_function

begin_function
specifier|static
name|GdkSegment
modifier|*
DECL|function|fuzzy_select_calculate (GimpFuzzySelectTool * fuzzy_sel,GimpDisplay * gdisp,gint * nsegs)
name|fuzzy_select_calculate
parameter_list|(
name|GimpFuzzySelectTool
modifier|*
name|fuzzy_sel
parameter_list|,
name|GimpDisplay
modifier|*
name|gdisp
parameter_list|,
name|gint
modifier|*
name|nsegs
parameter_list|)
block|{
name|PixelRegion
name|maskPR
decl_stmt|;
name|GimpChannel
modifier|*
name|new
decl_stmt|;
name|GdkSegment
modifier|*
name|segs
decl_stmt|;
name|BoundSeg
modifier|*
name|bsegs
decl_stmt|;
name|GimpDrawable
modifier|*
name|drawable
decl_stmt|;
name|gint
name|i
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
name|gdisp
operator|->
name|gimage
argument_list|)
expr_stmt|;
name|gimp_set_busy
argument_list|(
name|gdisp
operator|->
name|gimage
operator|->
name|gimp
argument_list|)
expr_stmt|;
name|x
operator|=
name|fuzzy_sel
operator|->
name|x
expr_stmt|;
name|y
operator|=
name|fuzzy_sel
operator|->
name|y
expr_stmt|;
if|if
condition|(
operator|!
name|fuzzy_options
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
name|drawable
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
block|}
name|new
operator|=
name|gimp_image_contiguous_region_by_seed
argument_list|(
name|gdisp
operator|->
name|gimage
argument_list|,
name|drawable
argument_list|,
name|fuzzy_options
operator|->
name|sample_merged
argument_list|,
name|fuzzy_options
operator|->
name|antialias
argument_list|,
name|fuzzy_options
operator|->
name|threshold
argument_list|,
name|x
argument_list|,
name|y
argument_list|)
expr_stmt|;
if|if
condition|(
name|fuzzy_sel
operator|->
name|fuzzy_mask
condition|)
name|g_object_unref
argument_list|(
name|G_OBJECT
argument_list|(
name|fuzzy_sel
operator|->
name|fuzzy_mask
argument_list|)
argument_list|)
expr_stmt|;
name|fuzzy_sel
operator|->
name|fuzzy_mask
operator|=
name|new
expr_stmt|;
comment|/*  calculate and allocate a new XSegment array which represents the boundary    *  of the color-contiguous region    */
name|pixel_region_init
argument_list|(
operator|&
name|maskPR
argument_list|,
name|gimp_drawable_data
argument_list|(
name|GIMP_DRAWABLE
argument_list|(
name|fuzzy_sel
operator|->
name|fuzzy_mask
argument_list|)
argument_list|)
argument_list|,
literal|0
argument_list|,
literal|0
argument_list|,
name|gimp_drawable_width
argument_list|(
name|GIMP_DRAWABLE
argument_list|(
name|fuzzy_sel
operator|->
name|fuzzy_mask
argument_list|)
argument_list|)
argument_list|,
name|gimp_drawable_height
argument_list|(
name|GIMP_DRAWABLE
argument_list|(
name|fuzzy_sel
operator|->
name|fuzzy_mask
argument_list|)
argument_list|)
argument_list|,
name|FALSE
argument_list|)
expr_stmt|;
name|bsegs
operator|=
name|find_mask_boundary
argument_list|(
operator|&
name|maskPR
argument_list|,
name|nsegs
argument_list|,
name|WithinBounds
argument_list|,
literal|0
argument_list|,
literal|0
argument_list|,
name|gimp_drawable_width
argument_list|(
name|GIMP_DRAWABLE
argument_list|(
name|fuzzy_sel
operator|->
name|fuzzy_mask
argument_list|)
argument_list|)
argument_list|,
name|gimp_drawable_height
argument_list|(
name|GIMP_DRAWABLE
argument_list|(
name|fuzzy_sel
operator|->
name|fuzzy_mask
argument_list|)
argument_list|)
argument_list|)
expr_stmt|;
name|segs
operator|=
name|g_new
argument_list|(
name|GdkSegment
argument_list|,
operator|*
name|nsegs
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
operator|*
name|nsegs
condition|;
name|i
operator|++
control|)
block|{
name|gdisplay_transform_coords
argument_list|(
name|gdisp
argument_list|,
name|bsegs
index|[
name|i
index|]
operator|.
name|x1
argument_list|,
name|bsegs
index|[
name|i
index|]
operator|.
name|y1
argument_list|,
operator|&
name|x
argument_list|,
operator|&
name|y
argument_list|,
operator|!
name|fuzzy_options
operator|->
name|sample_merged
argument_list|)
expr_stmt|;
name|segs
index|[
name|i
index|]
operator|.
name|x1
operator|=
name|x
expr_stmt|;
name|segs
index|[
name|i
index|]
operator|.
name|y1
operator|=
name|y
expr_stmt|;
name|gdisplay_transform_coords
argument_list|(
name|gdisp
argument_list|,
name|bsegs
index|[
name|i
index|]
operator|.
name|x2
argument_list|,
name|bsegs
index|[
name|i
index|]
operator|.
name|y2
argument_list|,
operator|&
name|x
argument_list|,
operator|&
name|y
argument_list|,
operator|!
name|fuzzy_options
operator|->
name|sample_merged
argument_list|)
expr_stmt|;
name|segs
index|[
name|i
index|]
operator|.
name|x2
operator|=
name|x
expr_stmt|;
name|segs
index|[
name|i
index|]
operator|.
name|y2
operator|=
name|y
expr_stmt|;
block|}
comment|/*  free boundary segments  */
name|g_free
argument_list|(
name|bsegs
argument_list|)
expr_stmt|;
name|gimp_unset_busy
argument_list|(
name|gdisp
operator|->
name|gimage
operator|->
name|gimp
argument_list|)
expr_stmt|;
return|return
name|segs
return|;
block|}
end_function

begin_function
specifier|static
name|void
DECL|function|gimp_fuzzy_select_tool_draw (GimpDrawTool * draw_tool)
name|gimp_fuzzy_select_tool_draw
parameter_list|(
name|GimpDrawTool
modifier|*
name|draw_tool
parameter_list|)
block|{
name|GimpFuzzySelectTool
modifier|*
name|fuzzy_sel
decl_stmt|;
name|fuzzy_sel
operator|=
name|GIMP_FUZZY_SELECT_TOOL
argument_list|(
name|draw_tool
argument_list|)
expr_stmt|;
if|if
condition|(
name|segs
condition|)
name|gdk_draw_segments
argument_list|(
name|draw_tool
operator|->
name|win
argument_list|,
name|draw_tool
operator|->
name|gc
argument_list|,
name|segs
argument_list|,
name|num_segs
argument_list|)
expr_stmt|;
block|}
end_function

end_unit

