begin_unit|revision:0.9.5;language:C;cregit-version:0.0.1
begin_comment
comment|/* GIMP - The GNU Image Manipulation Program  *  * A polygonal selection tool for GIMP  * Copyright (C) 2007 Martin Nordholts  *  * Based on gimpfreeselecttool.c which is  * Copyright (C) 1995 Spencer Kimball and Peter Mattis  *  * This program is free software; you can redistribute it and/or modify  * it under the terms of the GNU General Public License as published by  * the Free Software Foundation; either version 2 of the License, or  * (at your option) any later version.  *  * This program is distributed in the hope that it will be useful,  * but WITHOUT ANY WARRANTY; without even the implied warranty of  * MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the  * GNU General Public License for more details.  *  * You should have received a copy of the GNU General Public License  * along with this program; if not, write to the Free Software  * Foundation, Inc., 59 Temple Place - Suite 330, Boston, MA 02111-1307, USA.  */
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
file|<gdk/gdkkeysyms.h>
end_include

begin_include
include|#
directive|include
file|"libgimpmath/gimpmath.h"
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
file|"gimppolygonselecttool.h"
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

begin_define
DECL|macro|POINT_GRAB_THRESHOLD_SQ
define|#
directive|define
name|POINT_GRAB_THRESHOLD_SQ
value|100
end_define

begin_struct
DECL|struct|_GimpPolygonSelectTool
struct|struct
name|_GimpPolygonSelectTool
block|{
DECL|member|parent_instance
name|GimpSelectionTool
name|parent_instance
decl_stmt|;
comment|/* Point which is part of he polygon already. */
DECL|member|grabbed_point
name|GimpVector2
modifier|*
name|grabbed_point
decl_stmt|;
comment|/* Save the grabbed point state so we can cancel a movement    * operation.    */
DECL|member|saved_grabbed_point
name|GimpVector2
name|saved_grabbed_point
decl_stmt|;
comment|/* Point which is used to draw the polygon but which is not part of    * it yet.    */
DECL|member|pending_point
name|GimpVector2
name|pending_point
decl_stmt|;
DECL|member|show_pending_point
name|gboolean
name|show_pending_point
decl_stmt|;
comment|/* The points of the polygon. */
DECL|member|points
name|GimpVector2
modifier|*
name|points
decl_stmt|;
comment|/* The number of points used for the actual selection. */
DECL|member|num_points
name|gint
name|num_points
decl_stmt|;
DECL|member|max_segs
name|gint
name|max_segs
decl_stmt|;
block|}
struct|;
end_struct

begin_function_decl
specifier|static
name|void
name|gimp_polygon_select_tool_finalize
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
name|gimp_polygon_select_tool_control
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
name|gimp_polygon_select_tool_oper_update
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
name|gboolean
name|proximity
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
name|gimp_polygon_select_tool_button_press
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
name|gimp_polygon_select_tool_motion
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
name|gimp_polygon_select_tool_button_release
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
name|gboolean
name|gimp_polygon_select_tool_key_press
parameter_list|(
name|GimpTool
modifier|*
name|tool
parameter_list|,
name|GdkEventKey
modifier|*
name|kevent
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
name|gimp_polygon_select_tool_start
parameter_list|(
name|GimpPolygonSelectTool
modifier|*
name|poly_sel_tool
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
name|gimp_polygon_select_tool_commit
parameter_list|(
name|GimpPolygonSelectTool
modifier|*
name|poly_sel_tool
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
name|gimp_polygon_select_tool_halt
parameter_list|(
name|GimpPolygonSelectTool
modifier|*
name|poly_sel_tool
parameter_list|)
function_decl|;
end_function_decl

begin_function_decl
specifier|static
name|void
name|gimp_polygon_select_tool_draw
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
name|gimp_polygon_select_tool_real_select
parameter_list|(
name|GimpPolygonSelectTool
modifier|*
name|poly_sel_tool
parameter_list|,
name|GimpDisplay
modifier|*
name|display
parameter_list|)
function_decl|;
end_function_decl

begin_function_decl
specifier|static
name|GimpVector2
modifier|*
name|gimp_polygon_select_tool_add_point
parameter_list|(
name|GimpPolygonSelectTool
modifier|*
name|poly_sel_tool
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
name|gimp_polygon_select_tool_remove_last
parameter_list|(
name|GimpPolygonSelectTool
modifier|*
name|poly_sel_tool
parameter_list|)
function_decl|;
end_function_decl

begin_function_decl
specifier|static
name|void
name|gimp_polygon_select_tool_select_closet_point
parameter_list|(
name|GimpPolygonSelectTool
modifier|*
name|poly_sel_tool
parameter_list|,
name|GimpDisplay
modifier|*
name|display
parameter_list|,
name|GimpCoords
modifier|*
name|coords
parameter_list|)
function_decl|;
end_function_decl

begin_function_decl
specifier|static
name|gboolean
name|gimp_polygon_select_tool_should_close
parameter_list|(
name|GimpPolygonSelectTool
modifier|*
name|poly_sel_tool
parameter_list|,
name|GimpDisplay
modifier|*
name|display
parameter_list|,
name|GimpCoords
modifier|*
name|coords
parameter_list|)
function_decl|;
end_function_decl

begin_expr_stmt
name|G_DEFINE_TYPE
argument_list|(
name|GimpPolygonSelectTool
argument_list|,
name|gimp_polygon_select_tool
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
value|gimp_polygon_select_tool_parent_class
end_define

begin_function
name|void
DECL|function|gimp_polygon_select_tool_register (GimpToolRegisterCallback callback,gpointer data)
name|gimp_polygon_select_tool_register
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
name|GIMP_TYPE_POLYGON_SELECT_TOOL
argument_list|,
name|GIMP_TYPE_SELECTION_OPTIONS
argument_list|,
name|gimp_selection_options_gui
argument_list|,
literal|0
argument_list|,
literal|"gimp-polygon-select-tool"
argument_list|,
name|_
argument_list|(
literal|"Polygon Select"
argument_list|)
argument_list|,
name|_
argument_list|(
literal|"Polygon Select Tool: Select a hand-drawn polygon"
argument_list|)
argument_list|,
name|N_
argument_list|(
literal|"_Polygon Select"
argument_list|)
argument_list|,
literal|"G"
argument_list|,
name|NULL
argument_list|,
name|GIMP_HELP_TOOL_POLYGON_SELECT
argument_list|,
name|GIMP_STOCK_TOOL_POLYGON_SELECT
argument_list|,
name|data
argument_list|)
expr_stmt|;
block|}
end_function

begin_function
specifier|static
name|void
DECL|function|gimp_polygon_select_tool_class_init (GimpPolygonSelectToolClass * klass)
name|gimp_polygon_select_tool_class_init
parameter_list|(
name|GimpPolygonSelectToolClass
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
name|gimp_polygon_select_tool_finalize
expr_stmt|;
name|tool_class
operator|->
name|control
operator|=
name|gimp_polygon_select_tool_control
expr_stmt|;
name|tool_class
operator|->
name|oper_update
operator|=
name|gimp_polygon_select_tool_oper_update
expr_stmt|;
name|tool_class
operator|->
name|button_press
operator|=
name|gimp_polygon_select_tool_button_press
expr_stmt|;
name|tool_class
operator|->
name|motion
operator|=
name|gimp_polygon_select_tool_motion
expr_stmt|;
name|tool_class
operator|->
name|button_release
operator|=
name|gimp_polygon_select_tool_button_release
expr_stmt|;
name|tool_class
operator|->
name|key_press
operator|=
name|gimp_polygon_select_tool_key_press
expr_stmt|;
name|draw_tool_class
operator|->
name|draw
operator|=
name|gimp_polygon_select_tool_draw
expr_stmt|;
name|klass
operator|->
name|select
operator|=
name|gimp_polygon_select_tool_real_select
expr_stmt|;
block|}
end_function

begin_function
specifier|static
name|void
DECL|function|gimp_polygon_select_tool_init (GimpPolygonSelectTool * poly_sel_tool)
name|gimp_polygon_select_tool_init
parameter_list|(
name|GimpPolygonSelectTool
modifier|*
name|poly_sel_tool
parameter_list|)
block|{
name|GimpTool
modifier|*
name|tool
init|=
name|GIMP_TOOL
argument_list|(
name|poly_sel_tool
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
name|gimp_tool_control_set_wants_click
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
name|GIMP_TOOL_CURSOR_FREE_SELECT
argument_list|)
expr_stmt|;
name|poly_sel_tool
operator|->
name|points
operator|=
name|NULL
expr_stmt|;
name|poly_sel_tool
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
DECL|function|gimp_polygon_select_tool_finalize (GObject * object)
name|gimp_polygon_select_tool_finalize
parameter_list|(
name|GObject
modifier|*
name|object
parameter_list|)
block|{
name|GimpPolygonSelectTool
modifier|*
name|poly_sel_tool
init|=
name|GIMP_POLYGON_SELECT_TOOL
argument_list|(
name|object
argument_list|)
decl_stmt|;
if|if
condition|(
name|poly_sel_tool
operator|->
name|points
condition|)
block|{
name|g_free
argument_list|(
name|poly_sel_tool
operator|->
name|points
argument_list|)
expr_stmt|;
name|poly_sel_tool
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
DECL|function|gimp_polygon_select_tool_control (GimpTool * tool,GimpToolAction action,GimpDisplay * display)
name|gimp_polygon_select_tool_control
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
name|gimp_polygon_select_tool_halt
argument_list|(
name|GIMP_POLYGON_SELECT_TOOL
argument_list|(
name|tool
argument_list|)
argument_list|)
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
DECL|function|gimp_polygon_select_tool_oper_update (GimpTool * tool,GimpCoords * coords,GdkModifierType state,gboolean proximity,GimpDisplay * display)
name|gimp_polygon_select_tool_oper_update
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
name|gboolean
name|proximity
parameter_list|,
name|GimpDisplay
modifier|*
name|display
parameter_list|)
block|{
name|GimpPolygonSelectTool
modifier|*
name|poly_sel_tool
init|=
name|GIMP_POLYGON_SELECT_TOOL
argument_list|(
name|tool
argument_list|)
decl_stmt|;
if|if
condition|(
name|tool
operator|->
name|display
operator|==
name|display
condition|)
block|{
name|gimp_polygon_select_tool_select_closet_point
argument_list|(
name|poly_sel_tool
argument_list|,
name|display
argument_list|,
name|coords
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
name|poly_sel_tool
operator|->
name|grabbed_point
operator|||
name|poly_sel_tool
operator|->
name|num_points
operator|==
literal|0
condition|)
block|{
name|poly_sel_tool
operator|->
name|show_pending_point
operator|=
name|FALSE
expr_stmt|;
block|}
else|else
block|{
name|poly_sel_tool
operator|->
name|show_pending_point
operator|=
name|TRUE
expr_stmt|;
name|poly_sel_tool
operator|->
name|pending_point
operator|.
name|x
operator|=
name|coords
operator|->
name|x
expr_stmt|;
name|poly_sel_tool
operator|->
name|pending_point
operator|.
name|y
operator|=
name|coords
operator|->
name|y
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
DECL|function|gimp_polygon_select_tool_button_press (GimpTool * tool,GimpCoords * coords,guint32 time,GdkModifierType state,GimpDisplay * display)
name|gimp_polygon_select_tool_button_press
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
name|GimpPolygonSelectTool
modifier|*
name|poly_sel_tool
init|=
name|GIMP_POLYGON_SELECT_TOOL
argument_list|(
name|tool
argument_list|)
decl_stmt|;
if|if
condition|(
name|display
operator|!=
name|tool
operator|->
name|display
condition|)
block|{
name|gimp_polygon_select_tool_start
argument_list|(
name|poly_sel_tool
argument_list|,
name|display
argument_list|)
expr_stmt|;
name|gimp_selection_tool_start_edit
argument_list|(
name|GIMP_SELECTION_TOOL
argument_list|(
name|poly_sel_tool
argument_list|)
argument_list|,
name|coords
argument_list|)
expr_stmt|;
block|}
if|if
condition|(
name|poly_sel_tool
operator|->
name|grabbed_point
condition|)
block|{
name|poly_sel_tool
operator|->
name|saved_grabbed_point
operator|=
operator|*
name|poly_sel_tool
operator|->
name|grabbed_point
expr_stmt|;
block|}
block|}
end_function

begin_function
specifier|static
name|void
DECL|function|gimp_polygon_select_tool_motion (GimpTool * tool,GimpCoords * coords,guint32 time,GdkModifierType state,GimpDisplay * display)
name|gimp_polygon_select_tool_motion
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
if|if
condition|(
name|tool
operator|->
name|display
operator|==
name|display
condition|)
block|{
name|GimpPolygonSelectTool
modifier|*
name|poly_sel_tool
init|=
name|GIMP_POLYGON_SELECT_TOOL
argument_list|(
name|tool
argument_list|)
decl_stmt|;
name|GimpDrawTool
modifier|*
name|draw_tool
init|=
name|GIMP_DRAW_TOOL
argument_list|(
name|tool
argument_list|)
decl_stmt|;
name|gimp_draw_tool_pause
argument_list|(
name|draw_tool
argument_list|)
expr_stmt|;
if|if
condition|(
name|poly_sel_tool
operator|->
name|grabbed_point
condition|)
block|{
name|poly_sel_tool
operator|->
name|grabbed_point
operator|->
name|x
operator|=
name|coords
operator|->
name|x
expr_stmt|;
name|poly_sel_tool
operator|->
name|grabbed_point
operator|->
name|y
operator|=
name|coords
operator|->
name|y
expr_stmt|;
block|}
else|else
block|{
name|poly_sel_tool
operator|->
name|pending_point
operator|.
name|x
operator|=
name|coords
operator|->
name|x
expr_stmt|;
name|poly_sel_tool
operator|->
name|pending_point
operator|.
name|y
operator|=
name|coords
operator|->
name|y
expr_stmt|;
block|}
name|gimp_draw_tool_resume
argument_list|(
name|draw_tool
argument_list|)
expr_stmt|;
block|}
block|}
end_function

begin_function
specifier|static
name|void
DECL|function|gimp_polygon_select_tool_button_release (GimpTool * tool,GimpCoords * coords,guint32 time,GdkModifierType state,GimpButtonReleaseType release_type,GimpDisplay * display)
name|gimp_polygon_select_tool_button_release
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
name|GimpPolygonSelectTool
modifier|*
name|poly_sel_tool
init|=
name|GIMP_POLYGON_SELECT_TOOL
argument_list|(
name|tool
argument_list|)
decl_stmt|;
switch|switch
condition|(
name|release_type
condition|)
block|{
case|case
name|GIMP_BUTTON_RELEASE_CLICK
case|:
if|if
condition|(
name|gimp_polygon_select_tool_should_close
argument_list|(
name|poly_sel_tool
argument_list|,
name|display
argument_list|,
name|coords
argument_list|)
condition|)
block|{
name|gimp_polygon_select_tool_commit
argument_list|(
name|poly_sel_tool
argument_list|,
name|display
argument_list|)
expr_stmt|;
break|break;
block|}
comment|/* Fall through */
case|case
name|GIMP_BUTTON_RELEASE_NORMAL
case|:
if|if
condition|(
operator|!
name|poly_sel_tool
operator|->
name|grabbed_point
condition|)
block|{
name|gimp_polygon_select_tool_add_point
argument_list|(
name|poly_sel_tool
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
block|}
else|else
block|{
comment|/* We don't need to do anything since the grabbed point have            * already been moved in _motion.            */
block|}
break|break;
case|case
name|GIMP_BUTTON_RELEASE_CANCEL
case|:
block|{
name|gimp_draw_tool_pause
argument_list|(
name|GIMP_DRAW_TOOL
argument_list|(
name|poly_sel_tool
argument_list|)
argument_list|)
expr_stmt|;
if|if
condition|(
name|poly_sel_tool
operator|->
name|grabbed_point
condition|)
block|{
operator|*
name|poly_sel_tool
operator|->
name|grabbed_point
operator|=
name|poly_sel_tool
operator|->
name|saved_grabbed_point
expr_stmt|;
block|}
name|gimp_draw_tool_resume
argument_list|(
name|GIMP_DRAW_TOOL
argument_list|(
name|poly_sel_tool
argument_list|)
argument_list|)
expr_stmt|;
block|}
break|break;
case|case
name|GIMP_BUTTON_RELEASE_NO_MOTION
case|:
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
break|break;
block|}
block|}
end_function

begin_function
specifier|static
name|gboolean
DECL|function|gimp_polygon_select_tool_key_press (GimpTool * tool,GdkEventKey * kevent,GimpDisplay * display)
name|gimp_polygon_select_tool_key_press
parameter_list|(
name|GimpTool
modifier|*
name|tool
parameter_list|,
name|GdkEventKey
modifier|*
name|kevent
parameter_list|,
name|GimpDisplay
modifier|*
name|display
parameter_list|)
block|{
name|GimpPolygonSelectTool
modifier|*
name|poly_sel_tool
init|=
name|GIMP_POLYGON_SELECT_TOOL
argument_list|(
name|tool
argument_list|)
decl_stmt|;
name|gboolean
name|handled_key
init|=
name|FALSE
decl_stmt|;
switch|switch
condition|(
name|kevent
operator|->
name|keyval
condition|)
block|{
case|case
name|GDK_BackSpace
case|:
name|gimp_polygon_select_tool_remove_last
argument_list|(
name|poly_sel_tool
argument_list|)
expr_stmt|;
name|handled_key
operator|=
name|TRUE
expr_stmt|;
break|break;
case|case
name|GDK_KP_Enter
case|:
case|case
name|GDK_Return
case|:
name|gimp_polygon_select_tool_commit
argument_list|(
name|poly_sel_tool
argument_list|,
name|display
argument_list|)
expr_stmt|;
name|handled_key
operator|=
name|TRUE
expr_stmt|;
break|break;
case|case
name|GDK_Escape
case|:
name|gimp_polygon_select_tool_halt
argument_list|(
name|poly_sel_tool
argument_list|)
expr_stmt|;
name|handled_key
operator|=
name|TRUE
expr_stmt|;
break|break;
default|default:
name|handled_key
operator|=
name|FALSE
expr_stmt|;
break|break;
block|}
return|return
name|handled_key
return|;
block|}
end_function

begin_function
specifier|static
name|void
DECL|function|gimp_polygon_select_tool_start (GimpPolygonSelectTool * poly_sel_tool,GimpDisplay * display)
name|gimp_polygon_select_tool_start
parameter_list|(
name|GimpPolygonSelectTool
modifier|*
name|poly_sel_tool
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
name|poly_sel_tool
argument_list|)
decl_stmt|;
name|GimpDrawTool
modifier|*
name|draw_tool
init|=
name|GIMP_DRAW_TOOL
argument_list|(
name|tool
argument_list|)
decl_stmt|;
name|gimp_polygon_select_tool_halt
argument_list|(
name|poly_sel_tool
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
name|display
operator|=
name|display
expr_stmt|;
name|poly_sel_tool
operator|->
name|num_points
operator|=
literal|0
expr_stmt|;
name|poly_sel_tool
operator|->
name|grabbed_point
operator|=
name|NULL
expr_stmt|;
name|poly_sel_tool
operator|->
name|show_pending_point
operator|=
name|FALSE
expr_stmt|;
name|gimp_draw_tool_start
argument_list|(
name|draw_tool
argument_list|,
name|display
argument_list|)
expr_stmt|;
block|}
end_function

begin_function
specifier|static
name|void
DECL|function|gimp_polygon_select_tool_commit (GimpPolygonSelectTool * poly_sel_tool,GimpDisplay * display)
name|gimp_polygon_select_tool_commit
parameter_list|(
name|GimpPolygonSelectTool
modifier|*
name|poly_sel_tool
parameter_list|,
name|GimpDisplay
modifier|*
name|display
parameter_list|)
block|{
name|gimp_polygon_select_tool_select
argument_list|(
name|poly_sel_tool
argument_list|,
name|display
argument_list|)
expr_stmt|;
name|gimp_polygon_select_tool_halt
argument_list|(
name|poly_sel_tool
argument_list|)
expr_stmt|;
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
DECL|function|gimp_polygon_select_tool_halt (GimpPolygonSelectTool * poly_sel_tool)
name|gimp_polygon_select_tool_halt
parameter_list|(
name|GimpPolygonSelectTool
modifier|*
name|poly_sel_tool
parameter_list|)
block|{
name|GimpTool
modifier|*
name|tool
init|=
name|GIMP_TOOL
argument_list|(
name|poly_sel_tool
argument_list|)
decl_stmt|;
name|GimpDrawTool
modifier|*
name|draw_tool
init|=
name|GIMP_DRAW_TOOL
argument_list|(
name|poly_sel_tool
argument_list|)
decl_stmt|;
if|if
condition|(
name|gimp_draw_tool_is_active
argument_list|(
name|draw_tool
argument_list|)
condition|)
name|gimp_draw_tool_stop
argument_list|(
name|draw_tool
argument_list|)
expr_stmt|;
if|if
condition|(
name|gimp_tool_control_is_active
argument_list|(
name|tool
operator|->
name|control
argument_list|)
condition|)
name|gimp_tool_control_halt
argument_list|(
name|tool
operator|->
name|control
argument_list|)
expr_stmt|;
name|poly_sel_tool
operator|->
name|grabbed_point
operator|=
name|NULL
expr_stmt|;
name|poly_sel_tool
operator|->
name|show_pending_point
operator|=
name|FALSE
expr_stmt|;
name|poly_sel_tool
operator|->
name|num_points
operator|=
literal|0
expr_stmt|;
name|tool
operator|->
name|display
operator|=
name|NULL
expr_stmt|;
block|}
end_function

begin_function
specifier|static
name|void
DECL|function|gimp_polygon_select_tool_draw (GimpDrawTool * draw_tool)
name|gimp_polygon_select_tool_draw
parameter_list|(
name|GimpDrawTool
modifier|*
name|draw_tool
parameter_list|)
block|{
name|GimpPolygonSelectTool
modifier|*
name|poly_sel_tool
init|=
name|GIMP_POLYGON_SELECT_TOOL
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
name|poly_sel_tool
operator|->
name|points
argument_list|,
name|poly_sel_tool
operator|->
name|num_points
argument_list|,
name|FALSE
argument_list|,
name|FALSE
argument_list|)
expr_stmt|;
if|if
condition|(
name|poly_sel_tool
operator|->
name|show_pending_point
condition|)
block|{
name|gimp_draw_tool_draw_line
argument_list|(
name|draw_tool
argument_list|,
name|poly_sel_tool
operator|->
name|points
index|[
name|poly_sel_tool
operator|->
name|num_points
operator|-
literal|1
index|]
operator|.
name|x
argument_list|,
name|poly_sel_tool
operator|->
name|points
index|[
name|poly_sel_tool
operator|->
name|num_points
operator|-
literal|1
index|]
operator|.
name|y
argument_list|,
name|poly_sel_tool
operator|->
name|pending_point
operator|.
name|x
argument_list|,
name|poly_sel_tool
operator|->
name|pending_point
operator|.
name|y
argument_list|,
name|FALSE
argument_list|)
expr_stmt|;
block|}
block|}
end_function

begin_function
name|void
DECL|function|gimp_polygon_select_tool_select (GimpPolygonSelectTool * poly_sel_tool,GimpDisplay * display)
name|gimp_polygon_select_tool_select
parameter_list|(
name|GimpPolygonSelectTool
modifier|*
name|poly_sel_tool
parameter_list|,
name|GimpDisplay
modifier|*
name|display
parameter_list|)
block|{
name|g_return_if_fail
argument_list|(
name|GIMP_IS_POLYGON_SELECT_TOOL
argument_list|(
name|poly_sel_tool
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
name|GIMP_POLYGON_SELECT_TOOL_GET_CLASS
argument_list|(
name|poly_sel_tool
argument_list|)
operator|->
name|select
argument_list|(
name|poly_sel_tool
argument_list|,
name|display
argument_list|)
expr_stmt|;
block|}
end_function

begin_function
specifier|static
name|void
DECL|function|gimp_polygon_select_tool_real_select (GimpPolygonSelectTool * poly_sel_tool,GimpDisplay * display)
name|gimp_polygon_select_tool_real_select
parameter_list|(
name|GimpPolygonSelectTool
modifier|*
name|poly_sel_tool
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
name|poly_sel_tool
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
literal|"command|Polygon Select"
argument_list|)
argument_list|,
name|poly_sel_tool
operator|->
name|num_points
argument_list|,
name|poly_sel_tool
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
name|GimpVector2
modifier|*
DECL|function|gimp_polygon_select_tool_add_point (GimpPolygonSelectTool * poly_sel_tool,gdouble x,gdouble y)
name|gimp_polygon_select_tool_add_point
parameter_list|(
name|GimpPolygonSelectTool
modifier|*
name|poly_sel_tool
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
name|poly_sel_tool
operator|->
name|num_points
operator|>=
name|poly_sel_tool
operator|->
name|max_segs
condition|)
block|{
name|poly_sel_tool
operator|->
name|max_segs
operator|+=
name|DEFAULT_MAX_INC
expr_stmt|;
name|poly_sel_tool
operator|->
name|points
operator|=
name|g_realloc
argument_list|(
name|poly_sel_tool
operator|->
name|points
argument_list|,
sizeof|sizeof
argument_list|(
name|GimpVector2
argument_list|)
operator|*
name|poly_sel_tool
operator|->
name|max_segs
argument_list|)
expr_stmt|;
block|}
name|poly_sel_tool
operator|->
name|points
index|[
name|poly_sel_tool
operator|->
name|num_points
index|]
operator|.
name|x
operator|=
name|x
expr_stmt|;
name|poly_sel_tool
operator|->
name|points
index|[
name|poly_sel_tool
operator|->
name|num_points
index|]
operator|.
name|y
operator|=
name|y
expr_stmt|;
return|return
operator|&
name|poly_sel_tool
operator|->
name|points
index|[
name|poly_sel_tool
operator|->
name|num_points
operator|++
index|]
return|;
block|}
end_function

begin_function
specifier|static
name|void
DECL|function|gimp_polygon_select_tool_remove_last (GimpPolygonSelectTool * poly_sel_tool)
name|gimp_polygon_select_tool_remove_last
parameter_list|(
name|GimpPolygonSelectTool
modifier|*
name|poly_sel_tool
parameter_list|)
block|{
name|GimpDrawTool
modifier|*
name|draw_tool
init|=
name|GIMP_DRAW_TOOL
argument_list|(
name|poly_sel_tool
argument_list|)
decl_stmt|;
name|gimp_draw_tool_pause
argument_list|(
name|draw_tool
argument_list|)
expr_stmt|;
if|if
condition|(
name|poly_sel_tool
operator|->
name|num_points
operator|==
literal|0
condition|)
block|{
name|gimp_polygon_select_tool_halt
argument_list|(
name|poly_sel_tool
argument_list|)
expr_stmt|;
block|}
else|else
block|{
name|poly_sel_tool
operator|->
name|num_points
operator|--
expr_stmt|;
block|}
name|gimp_draw_tool_resume
argument_list|(
name|draw_tool
argument_list|)
expr_stmt|;
block|}
end_function

begin_function
specifier|static
name|void
DECL|function|gimp_polygon_select_tool_select_closet_point (GimpPolygonSelectTool * poly_sel_tool,GimpDisplay * display,GimpCoords * coords)
name|gimp_polygon_select_tool_select_closet_point
parameter_list|(
name|GimpPolygonSelectTool
modifier|*
name|poly_sel_tool
parameter_list|,
name|GimpDisplay
modifier|*
name|display
parameter_list|,
name|GimpCoords
modifier|*
name|coords
parameter_list|)
block|{
name|GimpDrawTool
modifier|*
name|draw_tool
init|=
name|GIMP_DRAW_TOOL
argument_list|(
name|poly_sel_tool
argument_list|)
decl_stmt|;
name|gdouble
name|shortest_dist_sq
decl_stmt|;
name|int
name|i
decl_stmt|;
name|poly_sel_tool
operator|->
name|grabbed_point
operator|=
name|NULL
expr_stmt|;
name|shortest_dist_sq
operator|=
name|POINT_GRAB_THRESHOLD_SQ
expr_stmt|;
for|for
control|(
name|i
operator|=
literal|0
init|;
name|i
operator|<
name|poly_sel_tool
operator|->
name|num_points
condition|;
name|i
operator|++
control|)
block|{
name|gdouble
name|dist_sq
decl_stmt|;
name|dist_sq
operator|=
name|gimp_draw_tool_calc_distance_square
argument_list|(
name|draw_tool
argument_list|,
name|display
argument_list|,
name|coords
operator|->
name|x
argument_list|,
name|coords
operator|->
name|y
argument_list|,
name|poly_sel_tool
operator|->
name|points
index|[
name|i
index|]
operator|.
name|x
argument_list|,
name|poly_sel_tool
operator|->
name|points
index|[
name|i
index|]
operator|.
name|y
argument_list|)
expr_stmt|;
if|if
condition|(
name|dist_sq
operator|<
name|shortest_dist_sq
condition|)
block|{
name|poly_sel_tool
operator|->
name|grabbed_point
operator|=
operator|&
name|poly_sel_tool
operator|->
name|points
index|[
name|i
index|]
expr_stmt|;
block|}
block|}
block|}
end_function

begin_function
specifier|static
name|gboolean
DECL|function|gimp_polygon_select_tool_should_close (GimpPolygonSelectTool * poly_sel_tool,GimpDisplay * display,GimpCoords * coords)
name|gimp_polygon_select_tool_should_close
parameter_list|(
name|GimpPolygonSelectTool
modifier|*
name|poly_sel_tool
parameter_list|,
name|GimpDisplay
modifier|*
name|display
parameter_list|,
name|GimpCoords
modifier|*
name|coords
parameter_list|)
block|{
name|gboolean
name|should_close
init|=
name|FALSE
decl_stmt|;
if|if
condition|(
name|poly_sel_tool
operator|->
name|num_points
operator|>
literal|0
condition|)
block|{
name|gdouble
name|dist_sq
decl_stmt|;
name|dist_sq
operator|=
name|gimp_draw_tool_calc_distance_square
argument_list|(
name|GIMP_DRAW_TOOL
argument_list|(
name|poly_sel_tool
argument_list|)
argument_list|,
name|display
argument_list|,
name|coords
operator|->
name|x
argument_list|,
name|coords
operator|->
name|y
argument_list|,
name|poly_sel_tool
operator|->
name|points
index|[
literal|0
index|]
operator|.
name|x
argument_list|,
name|poly_sel_tool
operator|->
name|points
index|[
literal|0
index|]
operator|.
name|y
argument_list|)
expr_stmt|;
name|should_close
operator|=
name|dist_sq
operator|<
name|POINT_GRAB_THRESHOLD_SQ
expr_stmt|;
block|}
return|return
name|should_close
return|;
block|}
end_function

end_unit

