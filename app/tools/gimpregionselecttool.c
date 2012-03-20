begin_unit|revision:0.9.5;language:C;cregit-version:0.0.1
begin_comment
comment|/* GIMP - The GNU Image Manipulation Program  * Copyright (C) 1995 Spencer Kimball and Peter Mattis  *  * gimpregionselecttool.c  *  * This program is free software: you can redistribute it and/or modify  * it under the terms of the GNU General Public License as published by  * the Free Software Foundation; either version 3 of the License, or  * (at your option) any later version.  *  * This program is distributed in the hope that it will be useful,  * but WITHOUT ANY WARRANTY; without even the implied warranty of  * MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the  * GNU General Public License for more details.  *  * You should have received a copy of the GNU General Public License  * along with this program.  If not, see<http://www.gnu.org/licenses/>.  */
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
file|"core/gimpboundary.h"
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
file|"display/gimpdisplay.h"
end_include

begin_include
include|#
directive|include
file|"display/gimpdisplayshell.h"
end_include

begin_include
include|#
directive|include
file|"display/gimpdisplayshell-cursor.h"
end_include

begin_include
include|#
directive|include
file|"gimpregionselectoptions.h"
end_include

begin_include
include|#
directive|include
file|"gimpregionselecttool.h"
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
name|gimp_region_select_tool_finalize
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
name|gimp_region_select_tool_button_press
parameter_list|(
name|GimpTool
modifier|*
name|tool
parameter_list|,
specifier|const
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
name|GimpButtonPressType
name|press_type
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
name|gimp_region_select_tool_button_release
parameter_list|(
name|GimpTool
modifier|*
name|tool
parameter_list|,
specifier|const
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
name|gimp_region_select_tool_motion
parameter_list|(
name|GimpTool
modifier|*
name|tool
parameter_list|,
specifier|const
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
name|gimp_region_select_tool_cursor_update
parameter_list|(
name|GimpTool
modifier|*
name|tool
parameter_list|,
specifier|const
name|GimpCoords
modifier|*
name|coords
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
name|gimp_region_select_tool_draw
parameter_list|(
name|GimpDrawTool
modifier|*
name|draw_tool
parameter_list|)
function_decl|;
end_function_decl

begin_function_decl
specifier|static
name|GimpBoundSeg
modifier|*
name|gimp_region_select_tool_calculate
parameter_list|(
name|GimpRegionSelectTool
modifier|*
name|region_sel
parameter_list|,
name|GimpDisplay
modifier|*
name|display
parameter_list|,
name|gint
modifier|*
name|n_segs
parameter_list|)
function_decl|;
end_function_decl

begin_macro
DECL|function|G_DEFINE_TYPE (GimpRegionSelectTool,gimp_region_select_tool,GIMP_TYPE_SELECTION_TOOL)
name|G_DEFINE_TYPE
argument_list|(
argument|GimpRegionSelectTool
argument_list|,
argument|gimp_region_select_tool
argument_list|,
argument|GIMP_TYPE_SELECTION_TOOL
argument_list|)
end_macro

begin_define
DECL|macro|parent_class
define|#
directive|define
name|parent_class
value|gimp_region_select_tool_parent_class
end_define

begin_function
specifier|static
name|void
name|gimp_region_select_tool_class_init
parameter_list|(
name|GimpRegionSelectToolClass
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
name|gimp_region_select_tool_finalize
expr_stmt|;
name|tool_class
operator|->
name|button_press
operator|=
name|gimp_region_select_tool_button_press
expr_stmt|;
name|tool_class
operator|->
name|button_release
operator|=
name|gimp_region_select_tool_button_release
expr_stmt|;
name|tool_class
operator|->
name|motion
operator|=
name|gimp_region_select_tool_motion
expr_stmt|;
name|tool_class
operator|->
name|cursor_update
operator|=
name|gimp_region_select_tool_cursor_update
expr_stmt|;
name|draw_tool_class
operator|->
name|draw
operator|=
name|gimp_region_select_tool_draw
expr_stmt|;
block|}
end_function

begin_function
specifier|static
name|void
DECL|function|gimp_region_select_tool_init (GimpRegionSelectTool * region_select)
name|gimp_region_select_tool_init
parameter_list|(
name|GimpRegionSelectTool
modifier|*
name|region_select
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
name|gimp_tool_control_set_scroll_lock
argument_list|(
name|tool
operator|->
name|control
argument_list|,
name|TRUE
argument_list|)
expr_stmt|;
name|gimp_tool_control_set_motion_mode
argument_list|(
name|tool
operator|->
name|control
argument_list|,
name|GIMP_MOTION_MODE_COMPRESS
argument_list|)
expr_stmt|;
name|region_select
operator|->
name|x
operator|=
literal|0
expr_stmt|;
name|region_select
operator|->
name|y
operator|=
literal|0
expr_stmt|;
name|region_select
operator|->
name|saved_threshold
operator|=
literal|0.0
expr_stmt|;
name|region_select
operator|->
name|region_mask
operator|=
name|NULL
expr_stmt|;
name|region_select
operator|->
name|segs
operator|=
name|NULL
expr_stmt|;
name|region_select
operator|->
name|n_segs
operator|=
literal|0
expr_stmt|;
block|}
end_function

begin_function
specifier|static
name|void
DECL|function|gimp_region_select_tool_finalize (GObject * object)
name|gimp_region_select_tool_finalize
parameter_list|(
name|GObject
modifier|*
name|object
parameter_list|)
block|{
name|GimpRegionSelectTool
modifier|*
name|region_sel
init|=
name|GIMP_REGION_SELECT_TOOL
argument_list|(
name|object
argument_list|)
decl_stmt|;
if|if
condition|(
name|region_sel
operator|->
name|region_mask
condition|)
block|{
name|g_object_unref
argument_list|(
name|region_sel
operator|->
name|region_mask
argument_list|)
expr_stmt|;
name|region_sel
operator|->
name|region_mask
operator|=
name|NULL
expr_stmt|;
block|}
if|if
condition|(
name|region_sel
operator|->
name|segs
condition|)
block|{
name|g_free
argument_list|(
name|region_sel
operator|->
name|segs
argument_list|)
expr_stmt|;
name|region_sel
operator|->
name|segs
operator|=
name|NULL
expr_stmt|;
name|region_sel
operator|->
name|n_segs
operator|=
literal|0
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
DECL|function|gimp_region_select_tool_button_press (GimpTool * tool,const GimpCoords * coords,guint32 time,GdkModifierType state,GimpButtonPressType press_type,GimpDisplay * display)
name|gimp_region_select_tool_button_press
parameter_list|(
name|GimpTool
modifier|*
name|tool
parameter_list|,
specifier|const
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
name|GimpButtonPressType
name|press_type
parameter_list|,
name|GimpDisplay
modifier|*
name|display
parameter_list|)
block|{
name|GimpRegionSelectTool
modifier|*
name|region_sel
init|=
name|GIMP_REGION_SELECT_TOOL
argument_list|(
name|tool
argument_list|)
decl_stmt|;
name|GimpRegionSelectOptions
modifier|*
name|options
init|=
name|GIMP_REGION_SELECT_TOOL_GET_OPTIONS
argument_list|(
name|tool
argument_list|)
decl_stmt|;
name|region_sel
operator|->
name|x
operator|=
name|coords
operator|->
name|x
expr_stmt|;
name|region_sel
operator|->
name|y
operator|=
name|coords
operator|->
name|y
expr_stmt|;
name|region_sel
operator|->
name|saved_threshold
operator|=
name|options
operator|->
name|threshold
expr_stmt|;
if|if
condition|(
name|gimp_selection_tool_start_edit
argument_list|(
name|GIMP_SELECTION_TOOL
argument_list|(
name|region_sel
argument_list|)
argument_list|,
name|display
argument_list|,
name|coords
argument_list|)
condition|)
block|{
return|return;
block|}
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
name|gimp_tool_push_status
argument_list|(
name|tool
argument_list|,
name|display
argument_list|,
name|_
argument_list|(
literal|"Move the mouse to change threshold"
argument_list|)
argument_list|)
expr_stmt|;
comment|/*  calculate the region boundary  */
name|region_sel
operator|->
name|segs
operator|=
name|gimp_region_select_tool_calculate
argument_list|(
name|region_sel
argument_list|,
name|display
argument_list|,
operator|&
name|region_sel
operator|->
name|n_segs
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
DECL|function|gimp_region_select_tool_button_release (GimpTool * tool,const GimpCoords * coords,guint32 time,GdkModifierType state,GimpButtonReleaseType release_type,GimpDisplay * display)
name|gimp_region_select_tool_button_release
parameter_list|(
name|GimpTool
modifier|*
name|tool
parameter_list|,
specifier|const
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
name|GimpRegionSelectTool
modifier|*
name|region_sel
init|=
name|GIMP_REGION_SELECT_TOOL
argument_list|(
name|tool
argument_list|)
decl_stmt|;
name|GimpSelectionOptions
modifier|*
name|sel_options
init|=
name|GIMP_SELECTION_TOOL_GET_OPTIONS
argument_list|(
name|tool
argument_list|)
decl_stmt|;
name|GimpRegionSelectOptions
modifier|*
name|options
init|=
name|GIMP_REGION_SELECT_TOOL_GET_OPTIONS
argument_list|(
name|tool
argument_list|)
decl_stmt|;
name|GimpImage
modifier|*
name|image
init|=
name|gimp_display_get_image
argument_list|(
name|display
argument_list|)
decl_stmt|;
name|gimp_tool_pop_status
argument_list|(
name|tool
argument_list|,
name|display
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
operator|!=
name|GIMP_BUTTON_RELEASE_CANCEL
condition|)
block|{
if|if
condition|(
name|GIMP_SELECTION_TOOL
argument_list|(
name|tool
argument_list|)
operator|->
name|function
operator|==
name|SELECTION_ANCHOR
condition|)
block|{
if|if
condition|(
name|gimp_image_get_floating_selection
argument_list|(
name|image
argument_list|)
condition|)
block|{
comment|/*  If there is a floating selection, anchor it  */
name|floating_sel_anchor
argument_list|(
name|gimp_image_get_floating_selection
argument_list|(
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
name|image
argument_list|)
argument_list|,
name|NULL
argument_list|,
name|TRUE
argument_list|)
expr_stmt|;
block|}
name|gimp_image_flush
argument_list|(
name|image
argument_list|)
expr_stmt|;
block|}
elseif|else
if|if
condition|(
name|region_sel
operator|->
name|region_mask
condition|)
block|{
name|gint
name|off_x
init|=
literal|0
decl_stmt|;
name|gint
name|off_y
init|=
literal|0
decl_stmt|;
if|if
condition|(
operator|!
name|options
operator|->
name|sample_merged
condition|)
block|{
name|GimpDrawable
modifier|*
name|drawable
init|=
name|gimp_image_get_active_drawable
argument_list|(
name|image
argument_list|)
decl_stmt|;
name|gimp_item_get_offset
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
block|}
name|gimp_channel_select_channel
argument_list|(
name|gimp_image_get_mask
argument_list|(
name|image
argument_list|)
argument_list|,
name|GIMP_REGION_SELECT_TOOL_GET_CLASS
argument_list|(
name|tool
argument_list|)
operator|->
name|undo_desc
argument_list|,
name|region_sel
operator|->
name|region_mask
argument_list|,
name|off_x
argument_list|,
name|off_y
argument_list|,
name|sel_options
operator|->
name|operation
argument_list|,
name|sel_options
operator|->
name|feather
argument_list|,
name|sel_options
operator|->
name|feather_radius
argument_list|,
name|sel_options
operator|->
name|feather_radius
argument_list|)
expr_stmt|;
name|gimp_image_flush
argument_list|(
name|image
argument_list|)
expr_stmt|;
block|}
block|}
if|if
condition|(
name|region_sel
operator|->
name|region_mask
condition|)
block|{
name|g_object_unref
argument_list|(
name|region_sel
operator|->
name|region_mask
argument_list|)
expr_stmt|;
name|region_sel
operator|->
name|region_mask
operator|=
name|NULL
expr_stmt|;
block|}
if|if
condition|(
name|region_sel
operator|->
name|segs
condition|)
block|{
name|g_free
argument_list|(
name|region_sel
operator|->
name|segs
argument_list|)
expr_stmt|;
name|region_sel
operator|->
name|segs
operator|=
name|NULL
expr_stmt|;
name|region_sel
operator|->
name|n_segs
operator|=
literal|0
expr_stmt|;
block|}
comment|/*  Restore the original threshold  */
name|g_object_set
argument_list|(
name|options
argument_list|,
literal|"threshold"
argument_list|,
name|region_sel
operator|->
name|saved_threshold
argument_list|,
name|NULL
argument_list|)
expr_stmt|;
block|}
end_function

begin_function
specifier|static
name|void
DECL|function|gimp_region_select_tool_motion (GimpTool * tool,const GimpCoords * coords,guint32 time,GdkModifierType state,GimpDisplay * display)
name|gimp_region_select_tool_motion
parameter_list|(
name|GimpTool
modifier|*
name|tool
parameter_list|,
specifier|const
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
name|GimpRegionSelectTool
modifier|*
name|region_sel
init|=
name|GIMP_REGION_SELECT_TOOL
argument_list|(
name|tool
argument_list|)
decl_stmt|;
name|GimpRegionSelectOptions
modifier|*
name|options
init|=
name|GIMP_REGION_SELECT_TOOL_GET_OPTIONS
argument_list|(
name|tool
argument_list|)
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
comment|/* don't let the events come in too fast, ignore below a delay of 100 ms */
if|if
condition|(
name|time
operator|-
name|last_time
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
name|region_sel
operator|->
name|x
expr_stmt|;
name|diff_y
operator|=
name|coords
operator|->
name|y
operator|-
name|region_sel
operator|->
name|y
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
name|g_object_set
argument_list|(
name|options
argument_list|,
literal|"threshold"
argument_list|,
name|CLAMP
argument_list|(
name|region_sel
operator|->
name|saved_threshold
operator|+
name|diff
argument_list|,
literal|0
argument_list|,
literal|255
argument_list|)
argument_list|,
name|NULL
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
if|if
condition|(
name|region_sel
operator|->
name|segs
condition|)
name|g_free
argument_list|(
name|region_sel
operator|->
name|segs
argument_list|)
expr_stmt|;
name|region_sel
operator|->
name|segs
operator|=
name|gimp_region_select_tool_calculate
argument_list|(
name|region_sel
argument_list|,
name|display
argument_list|,
operator|&
name|region_sel
operator|->
name|n_segs
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
end_function

begin_function
specifier|static
name|void
DECL|function|gimp_region_select_tool_cursor_update (GimpTool * tool,const GimpCoords * coords,GdkModifierType state,GimpDisplay * display)
name|gimp_region_select_tool_cursor_update
parameter_list|(
name|GimpTool
modifier|*
name|tool
parameter_list|,
specifier|const
name|GimpCoords
modifier|*
name|coords
parameter_list|,
name|GdkModifierType
name|state
parameter_list|,
name|GimpDisplay
modifier|*
name|display
parameter_list|)
block|{
name|GimpRegionSelectOptions
modifier|*
name|options
init|=
name|GIMP_REGION_SELECT_TOOL_GET_OPTIONS
argument_list|(
name|tool
argument_list|)
decl_stmt|;
name|GimpCursorModifier
name|modifier
init|=
name|GIMP_CURSOR_MODIFIER_NONE
decl_stmt|;
name|GimpImage
modifier|*
name|image
init|=
name|gimp_display_get_image
argument_list|(
name|display
argument_list|)
decl_stmt|;
if|if
condition|(
operator|!
name|gimp_image_coords_in_active_pickable
argument_list|(
name|image
argument_list|,
name|coords
argument_list|,
name|options
operator|->
name|sample_merged
argument_list|,
name|FALSE
argument_list|)
condition|)
name|modifier
operator|=
name|GIMP_CURSOR_MODIFIER_BAD
expr_stmt|;
name|gimp_tool_control_set_cursor_modifier
argument_list|(
name|tool
operator|->
name|control
argument_list|,
name|modifier
argument_list|)
expr_stmt|;
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
name|display
argument_list|)
expr_stmt|;
block|}
end_function

begin_function
specifier|static
name|void
DECL|function|gimp_region_select_tool_draw (GimpDrawTool * draw_tool)
name|gimp_region_select_tool_draw
parameter_list|(
name|GimpDrawTool
modifier|*
name|draw_tool
parameter_list|)
block|{
name|GimpRegionSelectTool
modifier|*
name|region_sel
init|=
name|GIMP_REGION_SELECT_TOOL
argument_list|(
name|draw_tool
argument_list|)
decl_stmt|;
name|GimpRegionSelectOptions
modifier|*
name|options
init|=
name|GIMP_REGION_SELECT_TOOL_GET_OPTIONS
argument_list|(
name|draw_tool
argument_list|)
decl_stmt|;
if|if
condition|(
name|region_sel
operator|->
name|segs
condition|)
block|{
name|gint
name|off_x
init|=
literal|0
decl_stmt|;
name|gint
name|off_y
init|=
literal|0
decl_stmt|;
if|if
condition|(
operator|!
name|options
operator|->
name|sample_merged
condition|)
block|{
name|GimpImage
modifier|*
name|image
init|=
name|gimp_display_get_image
argument_list|(
name|draw_tool
operator|->
name|display
argument_list|)
decl_stmt|;
name|GimpDrawable
modifier|*
name|drawable
init|=
name|gimp_image_get_active_drawable
argument_list|(
name|image
argument_list|)
decl_stmt|;
name|gimp_item_get_offset
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
block|}
name|gimp_draw_tool_add_boundary
argument_list|(
name|draw_tool
argument_list|,
name|region_sel
operator|->
name|segs
argument_list|,
name|region_sel
operator|->
name|n_segs
argument_list|,
name|NULL
argument_list|,
name|off_x
argument_list|,
name|off_y
argument_list|)
expr_stmt|;
block|}
block|}
end_function

begin_function
specifier|static
name|GimpBoundSeg
modifier|*
DECL|function|gimp_region_select_tool_calculate (GimpRegionSelectTool * region_sel,GimpDisplay * display,gint * n_segs)
name|gimp_region_select_tool_calculate
parameter_list|(
name|GimpRegionSelectTool
modifier|*
name|region_sel
parameter_list|,
name|GimpDisplay
modifier|*
name|display
parameter_list|,
name|gint
modifier|*
name|n_segs
parameter_list|)
block|{
name|GimpDisplayShell
modifier|*
name|shell
init|=
name|gimp_display_get_shell
argument_list|(
name|display
argument_list|)
decl_stmt|;
name|GeglBuffer
modifier|*
name|buffer
decl_stmt|;
name|GimpBoundSeg
modifier|*
name|segs
decl_stmt|;
name|gimp_display_shell_set_override_cursor
argument_list|(
name|shell
argument_list|,
name|GDK_WATCH
argument_list|)
expr_stmt|;
if|if
condition|(
name|region_sel
operator|->
name|region_mask
condition|)
name|g_object_unref
argument_list|(
name|region_sel
operator|->
name|region_mask
argument_list|)
expr_stmt|;
name|region_sel
operator|->
name|region_mask
operator|=
name|GIMP_REGION_SELECT_TOOL_GET_CLASS
argument_list|(
name|region_sel
argument_list|)
operator|->
name|get_mask
argument_list|(
name|region_sel
argument_list|,
name|display
argument_list|)
expr_stmt|;
if|if
condition|(
operator|!
name|region_sel
operator|->
name|region_mask
condition|)
block|{
name|gimp_display_shell_unset_override_cursor
argument_list|(
name|shell
argument_list|)
expr_stmt|;
operator|*
name|n_segs
operator|=
literal|0
expr_stmt|;
return|return
name|NULL
return|;
block|}
comment|/*  calculate and allocate a new segment array which represents the    *  boundary of the contiguous region    */
name|buffer
operator|=
name|gimp_drawable_get_read_buffer
argument_list|(
name|GIMP_DRAWABLE
argument_list|(
name|region_sel
operator|->
name|region_mask
argument_list|)
argument_list|)
expr_stmt|;
name|segs
operator|=
name|gimp_boundary_find
argument_list|(
name|buffer
argument_list|,
name|NULL
argument_list|,
name|GIMP_BOUNDARY_WITHIN_BOUNDS
argument_list|,
literal|0
argument_list|,
literal|0
argument_list|,
name|gimp_item_get_width
argument_list|(
name|GIMP_ITEM
argument_list|(
name|region_sel
operator|->
name|region_mask
argument_list|)
argument_list|)
argument_list|,
name|gimp_item_get_height
argument_list|(
name|GIMP_ITEM
argument_list|(
name|region_sel
operator|->
name|region_mask
argument_list|)
argument_list|)
argument_list|,
name|GIMP_BOUNDARY_HALF_WAY
argument_list|,
name|n_segs
argument_list|)
expr_stmt|;
name|gimp_display_shell_unset_override_cursor
argument_list|(
name|shell
argument_list|)
expr_stmt|;
return|return
name|segs
return|;
block|}
end_function

end_unit

