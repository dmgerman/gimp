begin_unit|revision:0.9.5;language:C;cregit-version:0.0.1
begin_comment
comment|/* GIMP - The GNU Image Manipulation Program  * Copyright (C) 1995 Spencer Kimball and Peter Mattis  *  * This program is free software: you can redistribute it and/or modify  * it under the terms of the GNU General Public License as published by  * the Free Software Foundation; either version 3 of the License, or  * (at your option) any later version.  *  * This program is distributed in the hope that it will be useful,  * but WITHOUT ANY WARRANTY; without even the implied warranty of  * MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the  * GNU General Public License for more details.  *  * You should have received a copy of the GNU General Public License  * along with this program.  If not, see<https://www.gnu.org/licenses/>.  */
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
file|"core/gimp.h"
end_include

begin_include
include|#
directive|include
file|"core/gimpguide.h"
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
file|"core/gimpimage-undo.h"
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
file|"display/gimpdisplayshell-selection.h"
end_include

begin_include
include|#
directive|include
file|"display/gimpdisplayshell-transform.h"
end_include

begin_include
include|#
directive|include
file|"gimpguidetool.h"
end_include

begin_include
include|#
directive|include
file|"gimptoolcontrol.h"
end_include

begin_include
include|#
directive|include
file|"tool_manager.h"
end_include

begin_include
include|#
directive|include
file|"gimp-intl.h"
end_include

begin_define
DECL|macro|SWAP_ORIENT (orient)
define|#
directive|define
name|SWAP_ORIENT
parameter_list|(
name|orient
parameter_list|)
value|((orient) == GIMP_ORIENTATION_HORIZONTAL ? \                              GIMP_ORIENTATION_VERTICAL : \                              GIMP_ORIENTATION_HORIZONTAL)
end_define

begin_comment
comment|/*  local function prototypes  */
end_comment

begin_function_decl
specifier|static
name|void
name|gimp_guide_tool_finalize
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
name|gimp_guide_tool_button_release
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
name|gimp_guide_tool_motion
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
name|gimp_guide_tool_draw
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
name|gimp_guide_tool_start
parameter_list|(
name|GimpTool
modifier|*
name|parent_tool
parameter_list|,
name|GimpDisplay
modifier|*
name|display
parameter_list|,
name|GList
modifier|*
name|guides
parameter_list|,
name|GimpOrientationType
name|orientation
parameter_list|)
function_decl|;
end_function_decl

begin_function_decl
specifier|static
name|void
name|gimp_guide_tool_push_status
parameter_list|(
name|GimpGuideTool
modifier|*
name|guide_tool
parameter_list|,
name|GimpDisplay
modifier|*
name|display
parameter_list|,
name|gboolean
name|remove_guides
parameter_list|)
function_decl|;
end_function_decl

begin_macro
DECL|function|G_DEFINE_TYPE (GimpGuideTool,gimp_guide_tool,GIMP_TYPE_DRAW_TOOL)
name|G_DEFINE_TYPE
argument_list|(
argument|GimpGuideTool
argument_list|,
argument|gimp_guide_tool
argument_list|,
argument|GIMP_TYPE_DRAW_TOOL
argument_list|)
end_macro

begin_define
DECL|macro|parent_class
define|#
directive|define
name|parent_class
value|gimp_guide_tool_parent_class
end_define

begin_function
specifier|static
name|void
name|gimp_guide_tool_class_init
parameter_list|(
name|GimpGuideToolClass
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
name|gimp_guide_tool_finalize
expr_stmt|;
name|tool_class
operator|->
name|button_release
operator|=
name|gimp_guide_tool_button_release
expr_stmt|;
name|tool_class
operator|->
name|motion
operator|=
name|gimp_guide_tool_motion
expr_stmt|;
name|draw_tool_class
operator|->
name|draw
operator|=
name|gimp_guide_tool_draw
expr_stmt|;
block|}
end_function

begin_function
specifier|static
name|void
DECL|function|gimp_guide_tool_init (GimpGuideTool * guide_tool)
name|gimp_guide_tool_init
parameter_list|(
name|GimpGuideTool
modifier|*
name|guide_tool
parameter_list|)
block|{
name|GimpTool
modifier|*
name|tool
init|=
name|GIMP_TOOL
argument_list|(
name|guide_tool
argument_list|)
decl_stmt|;
name|gimp_tool_control_set_snap_to
argument_list|(
name|tool
operator|->
name|control
argument_list|,
name|FALSE
argument_list|)
expr_stmt|;
name|gimp_tool_control_set_handle_empty_image
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
name|GIMP_TOOL_CURSOR_MOVE
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
name|gimp_tool_control_set_precision
argument_list|(
name|tool
operator|->
name|control
argument_list|,
name|GIMP_CURSOR_PRECISION_PIXEL_BORDER
argument_list|)
expr_stmt|;
name|guide_tool
operator|->
name|guides
operator|=
name|NULL
expr_stmt|;
name|guide_tool
operator|->
name|n_guides
operator|=
literal|0
expr_stmt|;
block|}
end_function

begin_function
specifier|static
name|void
DECL|function|gimp_guide_tool_finalize (GObject * object)
name|gimp_guide_tool_finalize
parameter_list|(
name|GObject
modifier|*
name|object
parameter_list|)
block|{
name|GimpGuideTool
modifier|*
name|guide_tool
init|=
name|GIMP_GUIDE_TOOL
argument_list|(
name|object
argument_list|)
decl_stmt|;
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
name|guide_tool
operator|->
name|n_guides
condition|;
name|i
operator|++
control|)
name|g_clear_object
argument_list|(
operator|&
name|guide_tool
operator|->
name|guides
index|[
name|i
index|]
operator|.
name|guide
argument_list|)
expr_stmt|;
name|g_free
argument_list|(
name|guide_tool
operator|->
name|guides
argument_list|)
expr_stmt|;
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
DECL|function|gimp_guide_tool_button_release (GimpTool * tool,const GimpCoords * coords,guint32 time,GdkModifierType state,GimpButtonReleaseType release_type,GimpDisplay * display)
name|gimp_guide_tool_button_release
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
name|GimpGuideTool
modifier|*
name|guide_tool
init|=
name|GIMP_GUIDE_TOOL
argument_list|(
name|tool
argument_list|)
decl_stmt|;
name|GimpDisplayShell
modifier|*
name|shell
init|=
name|gimp_display_get_shell
argument_list|(
name|display
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
name|gint
name|i
decl_stmt|;
name|gimp_tool_pop_status
argument_list|(
name|tool
argument_list|,
name|display
argument_list|)
expr_stmt|;
name|gimp_tool_control_halt
argument_list|(
name|tool
operator|->
name|control
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
name|release_type
operator|==
name|GIMP_BUTTON_RELEASE_CANCEL
condition|)
block|{
for|for
control|(
name|i
operator|=
literal|0
init|;
name|i
operator|<
name|guide_tool
operator|->
name|n_guides
condition|;
name|i
operator|++
control|)
block|{
name|GimpGuideToolGuide
modifier|*
name|guide
init|=
operator|&
name|guide_tool
operator|->
name|guides
index|[
name|i
index|]
decl_stmt|;
comment|/* custom guides are moved live */
if|if
condition|(
name|guide
operator|->
name|custom
condition|)
block|{
name|gimp_image_move_guide
argument_list|(
name|image
argument_list|,
name|guide
operator|->
name|guide
argument_list|,
name|guide
operator|->
name|old_position
argument_list|,
name|TRUE
argument_list|)
expr_stmt|;
block|}
block|}
block|}
else|else
block|{
name|gint
name|n_non_custom_guides
init|=
literal|0
decl_stmt|;
name|gboolean
name|remove_guides
init|=
name|FALSE
decl_stmt|;
for|for
control|(
name|i
operator|=
literal|0
init|;
name|i
operator|<
name|guide_tool
operator|->
name|n_guides
condition|;
name|i
operator|++
control|)
block|{
name|GimpGuideToolGuide
modifier|*
name|guide
init|=
operator|&
name|guide_tool
operator|->
name|guides
index|[
name|i
index|]
decl_stmt|;
name|gint
name|max_position
decl_stmt|;
if|if
condition|(
name|guide
operator|->
name|orientation
operator|==
name|GIMP_ORIENTATION_HORIZONTAL
condition|)
name|max_position
operator|=
name|gimp_image_get_height
argument_list|(
name|image
argument_list|)
expr_stmt|;
else|else
name|max_position
operator|=
name|gimp_image_get_width
argument_list|(
name|image
argument_list|)
expr_stmt|;
name|n_non_custom_guides
operator|+=
operator|!
name|guide
operator|->
name|custom
expr_stmt|;
if|if
condition|(
name|guide
operator|->
name|position
operator|==
name|GIMP_GUIDE_POSITION_UNDEFINED
operator|||
name|guide
operator|->
name|position
operator|<
literal|0
operator|||
name|guide
operator|->
name|position
operator|>
name|max_position
condition|)
block|{
name|remove_guides
operator|=
name|TRUE
expr_stmt|;
block|}
block|}
if|if
condition|(
name|n_non_custom_guides
operator|>
literal|1
condition|)
block|{
name|gimp_image_undo_group_start
argument_list|(
name|image
argument_list|,
name|GIMP_UNDO_GROUP_GUIDE
argument_list|,
name|remove_guides
condition|?
name|C_
argument_list|(
literal|"undo-type"
argument_list|,
literal|"Remove Guides"
argument_list|)
else|:
name|C_
argument_list|(
literal|"undo-type"
argument_list|,
literal|"Move Guides"
argument_list|)
argument_list|)
expr_stmt|;
block|}
for|for
control|(
name|i
operator|=
literal|0
init|;
name|i
operator|<
name|guide_tool
operator|->
name|n_guides
condition|;
name|i
operator|++
control|)
block|{
name|GimpGuideToolGuide
modifier|*
name|guide
init|=
operator|&
name|guide_tool
operator|->
name|guides
index|[
name|i
index|]
decl_stmt|;
if|if
condition|(
name|remove_guides
condition|)
block|{
comment|/* removing a guide can cause other guides to be removed as well                * (in particular, in case of symmetry guides).  these guides                * will be kept alive, since we hold a reference on them, but we                * need to make sure that they're still part of the image.                */
if|if
condition|(
name|g_list_find
argument_list|(
name|gimp_image_get_guides
argument_list|(
name|image
argument_list|)
argument_list|,
name|guide
operator|->
name|guide
argument_list|)
condition|)
name|gimp_image_remove_guide
argument_list|(
name|image
argument_list|,
name|guide
operator|->
name|guide
argument_list|,
name|TRUE
argument_list|)
expr_stmt|;
block|}
else|else
block|{
if|if
condition|(
name|guide
operator|->
name|guide
condition|)
block|{
comment|/* custom guides are moved live */
if|if
condition|(
operator|!
name|guide
operator|->
name|custom
condition|)
block|{
name|gimp_image_move_guide
argument_list|(
name|image
argument_list|,
name|guide
operator|->
name|guide
argument_list|,
name|guide
operator|->
name|position
argument_list|,
name|TRUE
argument_list|)
expr_stmt|;
block|}
block|}
else|else
block|{
switch|switch
condition|(
name|guide
operator|->
name|orientation
condition|)
block|{
case|case
name|GIMP_ORIENTATION_HORIZONTAL
case|:
name|gimp_image_add_hguide
argument_list|(
name|image
argument_list|,
name|guide
operator|->
name|position
argument_list|,
name|TRUE
argument_list|)
expr_stmt|;
break|break;
case|case
name|GIMP_ORIENTATION_VERTICAL
case|:
name|gimp_image_add_vguide
argument_list|(
name|image
argument_list|,
name|guide
operator|->
name|position
argument_list|,
name|TRUE
argument_list|)
expr_stmt|;
break|break;
default|default:
name|gimp_assert_not_reached
argument_list|()
expr_stmt|;
block|}
block|}
block|}
block|}
if|if
condition|(
name|n_non_custom_guides
operator|>
literal|1
condition|)
name|gimp_image_undo_group_end
argument_list|(
name|image
argument_list|)
expr_stmt|;
name|gimp_image_flush
argument_list|(
name|image
argument_list|)
expr_stmt|;
block|}
name|gimp_display_shell_selection_resume
argument_list|(
name|shell
argument_list|)
expr_stmt|;
name|tool_manager_pop_tool
argument_list|(
name|display
operator|->
name|gimp
argument_list|)
expr_stmt|;
name|g_object_unref
argument_list|(
name|guide_tool
argument_list|)
expr_stmt|;
block|{
name|GimpTool
modifier|*
name|active_tool
init|=
name|tool_manager_get_active
argument_list|(
name|display
operator|->
name|gimp
argument_list|)
decl_stmt|;
if|if
condition|(
name|GIMP_IS_DRAW_TOOL
argument_list|(
name|active_tool
argument_list|)
condition|)
name|gimp_draw_tool_pause
argument_list|(
name|GIMP_DRAW_TOOL
argument_list|(
name|active_tool
argument_list|)
argument_list|)
expr_stmt|;
name|tool_manager_oper_update_active
argument_list|(
name|display
operator|->
name|gimp
argument_list|,
name|coords
argument_list|,
name|state
argument_list|,
name|TRUE
argument_list|,
name|display
argument_list|)
expr_stmt|;
name|tool_manager_cursor_update_active
argument_list|(
name|display
operator|->
name|gimp
argument_list|,
name|coords
argument_list|,
name|state
argument_list|,
name|display
argument_list|)
expr_stmt|;
if|if
condition|(
name|GIMP_IS_DRAW_TOOL
argument_list|(
name|active_tool
argument_list|)
condition|)
name|gimp_draw_tool_resume
argument_list|(
name|GIMP_DRAW_TOOL
argument_list|(
name|active_tool
argument_list|)
argument_list|)
expr_stmt|;
block|}
block|}
end_function

begin_function
specifier|static
name|void
DECL|function|gimp_guide_tool_motion (GimpTool * tool,const GimpCoords * coords,guint32 time,GdkModifierType state,GimpDisplay * display)
name|gimp_guide_tool_motion
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
name|GimpGuideTool
modifier|*
name|guide_tool
init|=
name|GIMP_GUIDE_TOOL
argument_list|(
name|tool
argument_list|)
decl_stmt|;
name|GimpDisplayShell
modifier|*
name|shell
init|=
name|gimp_display_get_shell
argument_list|(
name|display
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
name|gboolean
name|remove_guides
init|=
name|FALSE
decl_stmt|;
name|gint
name|tx
decl_stmt|,
name|ty
decl_stmt|;
name|gint
name|i
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
name|guide_tool
operator|->
name|n_guides
condition|;
name|i
operator|++
control|)
block|{
name|GimpGuideToolGuide
modifier|*
name|guide
init|=
operator|&
name|guide_tool
operator|->
name|guides
index|[
name|i
index|]
decl_stmt|;
name|gint
name|max_position
decl_stmt|;
if|if
condition|(
name|guide
operator|->
name|orientation
operator|==
name|GIMP_ORIENTATION_HORIZONTAL
condition|)
name|max_position
operator|=
name|gimp_image_get_height
argument_list|(
name|image
argument_list|)
expr_stmt|;
else|else
name|max_position
operator|=
name|gimp_image_get_width
argument_list|(
name|image
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
name|guide
operator|->
name|position
operator|=
name|GIMP_GUIDE_POSITION_UNDEFINED
expr_stmt|;
name|remove_guides
operator|=
name|TRUE
expr_stmt|;
block|}
else|else
block|{
if|if
condition|(
name|guide
operator|->
name|orientation
operator|==
name|GIMP_ORIENTATION_HORIZONTAL
condition|)
name|guide
operator|->
name|position
operator|=
name|RINT
argument_list|(
name|coords
operator|->
name|y
argument_list|)
expr_stmt|;
else|else
name|guide
operator|->
name|position
operator|=
name|RINT
argument_list|(
name|coords
operator|->
name|x
argument_list|)
expr_stmt|;
if|if
condition|(
name|guide
operator|->
name|position
operator|<
literal|0
operator|||
name|guide
operator|->
name|position
operator|>
name|max_position
condition|)
name|remove_guides
operator|=
name|TRUE
expr_stmt|;
comment|/* custom guides are moved live */
if|if
condition|(
name|guide
operator|->
name|custom
condition|)
block|{
name|gimp_image_move_guide
argument_list|(
name|image
argument_list|,
name|guide
operator|->
name|guide
argument_list|,
name|CLAMP
argument_list|(
name|guide
operator|->
name|position
argument_list|,
literal|0
argument_list|,
name|max_position
argument_list|)
argument_list|,
name|TRUE
argument_list|)
expr_stmt|;
block|}
block|}
block|}
name|gimp_draw_tool_resume
argument_list|(
name|GIMP_DRAW_TOOL
argument_list|(
name|tool
argument_list|)
argument_list|)
expr_stmt|;
name|gimp_tool_pop_status
argument_list|(
name|tool
argument_list|,
name|display
argument_list|)
expr_stmt|;
name|gimp_guide_tool_push_status
argument_list|(
name|guide_tool
argument_list|,
name|display
argument_list|,
name|remove_guides
argument_list|)
expr_stmt|;
block|}
end_function

begin_function
specifier|static
name|void
DECL|function|gimp_guide_tool_draw (GimpDrawTool * draw_tool)
name|gimp_guide_tool_draw
parameter_list|(
name|GimpDrawTool
modifier|*
name|draw_tool
parameter_list|)
block|{
name|GimpGuideTool
modifier|*
name|guide_tool
init|=
name|GIMP_GUIDE_TOOL
argument_list|(
name|draw_tool
argument_list|)
decl_stmt|;
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
name|guide_tool
operator|->
name|n_guides
condition|;
name|i
operator|++
control|)
block|{
name|GimpGuideToolGuide
modifier|*
name|guide
init|=
operator|&
name|guide_tool
operator|->
name|guides
index|[
name|i
index|]
decl_stmt|;
if|if
condition|(
name|guide
operator|->
name|position
operator|!=
name|GIMP_GUIDE_POSITION_UNDEFINED
condition|)
block|{
comment|/* custom guides are moved live */
if|if
condition|(
operator|!
name|guide
operator|->
name|custom
condition|)
block|{
name|gimp_draw_tool_add_guide
argument_list|(
name|draw_tool
argument_list|,
name|guide
operator|->
name|orientation
argument_list|,
name|guide
operator|->
name|position
argument_list|,
name|GIMP_GUIDE_STYLE_NONE
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
DECL|function|gimp_guide_tool_start (GimpTool * parent_tool,GimpDisplay * display,GList * guides,GimpOrientationType orientation)
name|gimp_guide_tool_start
parameter_list|(
name|GimpTool
modifier|*
name|parent_tool
parameter_list|,
name|GimpDisplay
modifier|*
name|display
parameter_list|,
name|GList
modifier|*
name|guides
parameter_list|,
name|GimpOrientationType
name|orientation
parameter_list|)
block|{
name|GimpGuideTool
modifier|*
name|guide_tool
decl_stmt|;
name|GimpTool
modifier|*
name|tool
decl_stmt|;
name|guide_tool
operator|=
name|g_object_new
argument_list|(
name|GIMP_TYPE_GUIDE_TOOL
argument_list|,
literal|"tool-info"
argument_list|,
name|parent_tool
operator|->
name|tool_info
argument_list|,
name|NULL
argument_list|)
expr_stmt|;
name|tool
operator|=
name|GIMP_TOOL
argument_list|(
name|guide_tool
argument_list|)
expr_stmt|;
name|gimp_display_shell_selection_pause
argument_list|(
name|gimp_display_get_shell
argument_list|(
name|display
argument_list|)
argument_list|)
expr_stmt|;
if|if
condition|(
name|guides
condition|)
block|{
name|gint
name|i
decl_stmt|;
name|guide_tool
operator|->
name|n_guides
operator|=
name|g_list_length
argument_list|(
name|guides
argument_list|)
expr_stmt|;
name|guide_tool
operator|->
name|guides
operator|=
name|g_new
argument_list|(
name|GimpGuideToolGuide
argument_list|,
name|guide_tool
operator|->
name|n_guides
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
name|guide_tool
operator|->
name|n_guides
condition|;
name|i
operator|++
control|)
block|{
name|GimpGuide
modifier|*
name|guide
init|=
name|guides
operator|->
name|data
decl_stmt|;
name|guide_tool
operator|->
name|guides
index|[
name|i
index|]
operator|.
name|guide
operator|=
name|g_object_ref
argument_list|(
name|guide
argument_list|)
expr_stmt|;
name|guide_tool
operator|->
name|guides
index|[
name|i
index|]
operator|.
name|old_position
operator|=
name|gimp_guide_get_position
argument_list|(
name|guide
argument_list|)
expr_stmt|;
name|guide_tool
operator|->
name|guides
index|[
name|i
index|]
operator|.
name|position
operator|=
name|gimp_guide_get_position
argument_list|(
name|guide
argument_list|)
expr_stmt|;
name|guide_tool
operator|->
name|guides
index|[
name|i
index|]
operator|.
name|orientation
operator|=
name|gimp_guide_get_orientation
argument_list|(
name|guide
argument_list|)
expr_stmt|;
name|guide_tool
operator|->
name|guides
index|[
name|i
index|]
operator|.
name|custom
operator|=
name|gimp_guide_is_custom
argument_list|(
name|guide
argument_list|)
expr_stmt|;
name|guides
operator|=
name|g_list_next
argument_list|(
name|guides
argument_list|)
expr_stmt|;
block|}
block|}
else|else
block|{
name|guide_tool
operator|->
name|n_guides
operator|=
literal|1
expr_stmt|;
name|guide_tool
operator|->
name|guides
operator|=
name|g_new
argument_list|(
name|GimpGuideToolGuide
argument_list|,
literal|1
argument_list|)
expr_stmt|;
name|guide_tool
operator|->
name|guides
index|[
literal|0
index|]
operator|.
name|guide
operator|=
name|NULL
expr_stmt|;
name|guide_tool
operator|->
name|guides
index|[
literal|0
index|]
operator|.
name|old_position
operator|=
literal|0
expr_stmt|;
name|guide_tool
operator|->
name|guides
index|[
literal|0
index|]
operator|.
name|position
operator|=
name|GIMP_GUIDE_POSITION_UNDEFINED
expr_stmt|;
name|guide_tool
operator|->
name|guides
index|[
literal|0
index|]
operator|.
name|orientation
operator|=
name|orientation
expr_stmt|;
name|guide_tool
operator|->
name|guides
index|[
literal|0
index|]
operator|.
name|custom
operator|=
name|FALSE
expr_stmt|;
block|}
name|gimp_tool_set_cursor
argument_list|(
name|tool
argument_list|,
name|display
argument_list|,
name|GIMP_CURSOR_MOUSE
argument_list|,
name|GIMP_TOOL_CURSOR_HAND
argument_list|,
name|GIMP_CURSOR_MODIFIER_MOVE
argument_list|)
expr_stmt|;
name|tool_manager_push_tool
argument_list|(
name|display
operator|->
name|gimp
argument_list|,
name|tool
argument_list|)
expr_stmt|;
name|tool
operator|->
name|display
operator|=
name|display
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
name|guide_tool
argument_list|)
argument_list|,
name|display
argument_list|)
expr_stmt|;
name|gimp_guide_tool_push_status
argument_list|(
name|guide_tool
argument_list|,
name|display
argument_list|,
name|FALSE
argument_list|)
expr_stmt|;
block|}
end_function

begin_function
specifier|static
name|void
DECL|function|gimp_guide_tool_push_status (GimpGuideTool * guide_tool,GimpDisplay * display,gboolean remove_guides)
name|gimp_guide_tool_push_status
parameter_list|(
name|GimpGuideTool
modifier|*
name|guide_tool
parameter_list|,
name|GimpDisplay
modifier|*
name|display
parameter_list|,
name|gboolean
name|remove_guides
parameter_list|)
block|{
name|GimpTool
modifier|*
name|tool
init|=
name|GIMP_TOOL
argument_list|(
name|guide_tool
argument_list|)
decl_stmt|;
if|if
condition|(
name|remove_guides
condition|)
block|{
name|gimp_tool_push_status
argument_list|(
name|tool
argument_list|,
name|display
argument_list|,
name|guide_tool
operator|->
name|n_guides
operator|>
literal|1
condition|?
name|_
argument_list|(
literal|"Remove Guides"
argument_list|)
else|:
name|guide_tool
operator|->
name|guides
index|[
literal|0
index|]
operator|.
name|guide
condition|?
name|_
argument_list|(
literal|"Remove Guide"
argument_list|)
else|:
name|_
argument_list|(
literal|"Cancel Guide"
argument_list|)
argument_list|)
expr_stmt|;
block|}
else|else
block|{
name|GimpGuideToolGuide
modifier|*
name|guides
index|[
literal|2
index|]
decl_stmt|;
name|gint
name|n_guides
init|=
literal|0
decl_stmt|;
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
name|guide_tool
operator|->
name|n_guides
condition|;
name|i
operator|++
control|)
block|{
name|GimpGuideToolGuide
modifier|*
name|guide
init|=
operator|&
name|guide_tool
operator|->
name|guides
index|[
name|i
index|]
decl_stmt|;
if|if
condition|(
name|guide_tool
operator|->
name|guides
index|[
name|i
index|]
operator|.
name|guide
condition|)
block|{
if|if
condition|(
name|n_guides
operator|==
literal|0
operator|||
name|guide
operator|->
name|orientation
operator|!=
name|guides
index|[
literal|0
index|]
operator|->
name|orientation
condition|)
block|{
name|guides
index|[
name|n_guides
operator|++
index|]
operator|=
name|guide
expr_stmt|;
if|if
condition|(
name|n_guides
operator|==
literal|2
condition|)
break|break;
block|}
block|}
block|}
if|if
condition|(
name|n_guides
operator|==
literal|2
operator|&&
name|guides
index|[
literal|0
index|]
operator|->
name|orientation
operator|==
name|GIMP_ORIENTATION_HORIZONTAL
condition|)
block|{
name|GimpGuideToolGuide
modifier|*
name|temp
decl_stmt|;
name|temp
operator|=
name|guides
index|[
literal|0
index|]
expr_stmt|;
name|guides
index|[
literal|0
index|]
operator|=
name|guides
index|[
literal|1
index|]
expr_stmt|;
name|guides
index|[
literal|1
index|]
operator|=
name|temp
expr_stmt|;
block|}
if|if
condition|(
name|n_guides
operator|==
literal|1
condition|)
block|{
name|gimp_tool_push_status_length
argument_list|(
name|tool
argument_list|,
name|display
argument_list|,
name|_
argument_list|(
literal|"Move Guide: "
argument_list|)
argument_list|,
name|SWAP_ORIENT
argument_list|(
name|guides
index|[
literal|0
index|]
operator|->
name|orientation
argument_list|)
argument_list|,
name|guides
index|[
literal|0
index|]
operator|->
name|position
operator|-
name|guides
index|[
literal|0
index|]
operator|->
name|old_position
argument_list|,
name|NULL
argument_list|)
expr_stmt|;
block|}
elseif|else
if|if
condition|(
name|n_guides
operator|==
literal|2
condition|)
block|{
name|gimp_tool_push_status_coords
argument_list|(
name|tool
argument_list|,
name|display
argument_list|,
name|GIMP_CURSOR_PRECISION_PIXEL_BORDER
argument_list|,
name|_
argument_list|(
literal|"Move Guides: "
argument_list|)
argument_list|,
name|guides
index|[
literal|0
index|]
operator|->
name|position
operator|-
name|guides
index|[
literal|0
index|]
operator|->
name|old_position
argument_list|,
literal|", "
argument_list|,
name|guides
index|[
literal|1
index|]
operator|->
name|position
operator|-
name|guides
index|[
literal|1
index|]
operator|->
name|old_position
argument_list|,
name|NULL
argument_list|)
expr_stmt|;
block|}
else|else
block|{
name|gimp_tool_push_status_length
argument_list|(
name|tool
argument_list|,
name|display
argument_list|,
name|_
argument_list|(
literal|"Add Guide: "
argument_list|)
argument_list|,
name|SWAP_ORIENT
argument_list|(
name|guide_tool
operator|->
name|guides
index|[
literal|0
index|]
operator|.
name|orientation
argument_list|)
argument_list|,
name|guide_tool
operator|->
name|guides
index|[
literal|0
index|]
operator|.
name|position
argument_list|,
name|NULL
argument_list|)
expr_stmt|;
block|}
block|}
block|}
end_function

begin_comment
comment|/*  public functions  */
end_comment

begin_function
name|void
DECL|function|gimp_guide_tool_start_new (GimpTool * parent_tool,GimpDisplay * display,GimpOrientationType orientation)
name|gimp_guide_tool_start_new
parameter_list|(
name|GimpTool
modifier|*
name|parent_tool
parameter_list|,
name|GimpDisplay
modifier|*
name|display
parameter_list|,
name|GimpOrientationType
name|orientation
parameter_list|)
block|{
name|g_return_if_fail
argument_list|(
name|GIMP_IS_TOOL
argument_list|(
name|parent_tool
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
name|g_return_if_fail
argument_list|(
name|orientation
operator|!=
name|GIMP_ORIENTATION_UNKNOWN
argument_list|)
expr_stmt|;
name|gimp_guide_tool_start
argument_list|(
name|parent_tool
argument_list|,
name|display
argument_list|,
name|NULL
argument_list|,
name|orientation
argument_list|)
expr_stmt|;
block|}
end_function

begin_function
name|void
DECL|function|gimp_guide_tool_start_edit (GimpTool * parent_tool,GimpDisplay * display,GimpGuide * guide)
name|gimp_guide_tool_start_edit
parameter_list|(
name|GimpTool
modifier|*
name|parent_tool
parameter_list|,
name|GimpDisplay
modifier|*
name|display
parameter_list|,
name|GimpGuide
modifier|*
name|guide
parameter_list|)
block|{
name|GList
modifier|*
name|guides
init|=
name|NULL
decl_stmt|;
name|g_return_if_fail
argument_list|(
name|GIMP_IS_TOOL
argument_list|(
name|parent_tool
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
name|g_return_if_fail
argument_list|(
name|GIMP_IS_GUIDE
argument_list|(
name|guide
argument_list|)
argument_list|)
expr_stmt|;
name|guides
operator|=
name|g_list_append
argument_list|(
name|guides
argument_list|,
name|guide
argument_list|)
expr_stmt|;
name|gimp_guide_tool_start
argument_list|(
name|parent_tool
argument_list|,
name|display
argument_list|,
name|guides
argument_list|,
name|GIMP_ORIENTATION_UNKNOWN
argument_list|)
expr_stmt|;
name|g_list_free
argument_list|(
name|guides
argument_list|)
expr_stmt|;
block|}
end_function

begin_function
name|void
DECL|function|gimp_guide_tool_start_edit_many (GimpTool * parent_tool,GimpDisplay * display,GList * guides)
name|gimp_guide_tool_start_edit_many
parameter_list|(
name|GimpTool
modifier|*
name|parent_tool
parameter_list|,
name|GimpDisplay
modifier|*
name|display
parameter_list|,
name|GList
modifier|*
name|guides
parameter_list|)
block|{
name|g_return_if_fail
argument_list|(
name|GIMP_IS_TOOL
argument_list|(
name|parent_tool
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
name|g_return_if_fail
argument_list|(
name|guides
operator|!=
name|NULL
argument_list|)
expr_stmt|;
name|gimp_guide_tool_start
argument_list|(
name|parent_tool
argument_list|,
name|display
argument_list|,
name|guides
argument_list|,
name|GIMP_ORIENTATION_UNKNOWN
argument_list|)
expr_stmt|;
block|}
end_function

end_unit

