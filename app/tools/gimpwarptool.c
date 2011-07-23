begin_unit|revision:0.9.5;language:C;cregit-version:0.0.1
begin_comment
comment|/* GIMP - The GNU Image Manipulation Program  *  * gimpwarptool.c  * Copyright (C) 2011 Michael MurÃ©<batolettre@gmail.com>  *  * This program is free software: you can redistribute it and/or modify  * it under the terms of the GNU General Public License as published by  * the Free Software Foundation; either version 3 of the License, or  * (at your option) any later version.  *  * This program is distributed in the hope that it will be useful,  * but WITHOUT ANY WARRANTY; without even the implied warranty of  * MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the  * GNU General Public License for more details.  *  * You should have received a copy of the GNU General Public License  * along with this program.  If not, see<http://www.gnu.org/licenses/>.  */
end_comment

begin_include
include|#
directive|include
file|"config.h"
end_include

begin_include
include|#
directive|include
file|<string.h>
end_include

begin_include
include|#
directive|include
file|<stdlib.h>
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
file|<gdk/gdkkeysyms.h>
end_include

begin_include
include|#
directive|include
file|"libgimpbase/gimpbase.h"
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
file|"core/gimpdrawable-shadow.h"
end_include

begin_include
include|#
directive|include
file|"core/gimpimage.h"
end_include

begin_include
include|#
directive|include
file|"core/gimpimagemap.h"
end_include

begin_include
include|#
directive|include
file|"core/gimplayer.h"
end_include

begin_include
include|#
directive|include
file|"core/gimpprogress.h"
end_include

begin_include
include|#
directive|include
file|"core/gimpprojection.h"
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
file|"display/gimpdisplayshell.h"
end_include

begin_include
include|#
directive|include
file|"display/gimpdisplayshell-transform.h"
end_include

begin_include
include|#
directive|include
file|"gimpwarptool.h"
end_include

begin_include
include|#
directive|include
file|"gimpwarpoptions.h"
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
name|gimp_warp_tool_start
parameter_list|(
name|GimpWarpTool
modifier|*
name|wt
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
name|gimp_warp_tool_button_press
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
name|gimp_warp_tool_button_release
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
name|gboolean
name|gimp_warp_tool_key_press
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
name|gimp_warp_tool_motion
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
name|gimp_warp_tool_control
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
name|gimp_warp_tool_cursor_update
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
name|gimp_warp_tool_oper_update
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
name|gboolean
name|gimp_warp_tool_stroke_timer
parameter_list|(
name|gpointer
name|data
parameter_list|)
function_decl|;
end_function_decl

begin_function_decl
specifier|static
name|gboolean
name|gimp_warp_tool_preview_timer
parameter_list|(
name|gpointer
name|data
parameter_list|)
function_decl|;
end_function_decl

begin_function_decl
specifier|static
name|void
name|gimp_warp_tool_draw
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
name|gimp_warp_tool_create_graph
parameter_list|(
name|GimpWarpTool
modifier|*
name|wt
parameter_list|)
function_decl|;
end_function_decl

begin_function_decl
specifier|static
name|void
name|gimp_warp_tool_create_image_map
parameter_list|(
name|GimpWarpTool
modifier|*
name|wt
parameter_list|,
name|GimpDrawable
modifier|*
name|drawable
parameter_list|)
function_decl|;
end_function_decl

begin_function_decl
specifier|static
name|void
name|gimp_warp_tool_image_map_update
parameter_list|(
name|GimpWarpTool
modifier|*
name|wt
parameter_list|)
function_decl|;
end_function_decl

begin_function_decl
specifier|static
name|void
name|gimp_warp_tool_image_map_flush
parameter_list|(
name|GimpImageMap
modifier|*
name|image_map
parameter_list|,
name|GimpTool
modifier|*
name|tool
parameter_list|)
function_decl|;
end_function_decl

begin_function_decl
specifier|static
name|void
name|gimp_warp_tool_add_op
parameter_list|(
name|GimpWarpTool
modifier|*
name|wt
parameter_list|)
function_decl|;
end_function_decl

begin_function_decl
specifier|static
name|void
name|gimp_warp_tool_undo
parameter_list|(
name|GimpWarpTool
modifier|*
name|wt
parameter_list|)
function_decl|;
end_function_decl

begin_macro
DECL|function|G_DEFINE_TYPE (GimpWarpTool,gimp_warp_tool,GIMP_TYPE_DRAW_TOOL)
name|G_DEFINE_TYPE
argument_list|(
argument|GimpWarpTool
argument_list|,
argument|gimp_warp_tool
argument_list|,
argument|GIMP_TYPE_DRAW_TOOL
argument_list|)
end_macro

begin_define
DECL|macro|parent_class
define|#
directive|define
name|parent_class
value|gimp_warp_tool_parent_class
end_define

begin_define
DECL|macro|STROKE_PERIOD
define|#
directive|define
name|STROKE_PERIOD
value|100
end_define

begin_define
DECL|macro|PREVIEW_PERIOD
define|#
directive|define
name|PREVIEW_PERIOD
value|1000
end_define

begin_function
name|void
name|gimp_warp_tool_register
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
name|GIMP_TYPE_WARP_TOOL
argument_list|,
name|GIMP_TYPE_WARP_OPTIONS
argument_list|,
name|gimp_warp_options_gui
argument_list|,
literal|0
argument_list|,
literal|"gimp-warp-tool"
argument_list|,
name|_
argument_list|(
literal|"Warp Transform"
argument_list|)
argument_list|,
name|_
argument_list|(
literal|"Warp Transform: Deform with different tools"
argument_list|)
argument_list|,
name|N_
argument_list|(
literal|"_Warp Transform"
argument_list|)
argument_list|,
literal|"W"
argument_list|,
name|NULL
argument_list|,
name|GIMP_HELP_TOOL_WARP
argument_list|,
name|GIMP_STOCK_TOOL_WARP
argument_list|,
name|data
argument_list|)
expr_stmt|;
block|}
end_function

begin_function
specifier|static
name|void
DECL|function|gimp_warp_tool_class_init (GimpWarpToolClass * klass)
name|gimp_warp_tool_class_init
parameter_list|(
name|GimpWarpToolClass
modifier|*
name|klass
parameter_list|)
block|{
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
name|tool_class
operator|->
name|button_press
operator|=
name|gimp_warp_tool_button_press
expr_stmt|;
name|tool_class
operator|->
name|button_release
operator|=
name|gimp_warp_tool_button_release
expr_stmt|;
name|tool_class
operator|->
name|key_press
operator|=
name|gimp_warp_tool_key_press
expr_stmt|;
name|tool_class
operator|->
name|motion
operator|=
name|gimp_warp_tool_motion
expr_stmt|;
name|tool_class
operator|->
name|control
operator|=
name|gimp_warp_tool_control
expr_stmt|;
name|tool_class
operator|->
name|cursor_update
operator|=
name|gimp_warp_tool_cursor_update
expr_stmt|;
name|tool_class
operator|->
name|oper_update
operator|=
name|gimp_warp_tool_oper_update
expr_stmt|;
name|draw_tool_class
operator|->
name|draw
operator|=
name|gimp_warp_tool_draw
expr_stmt|;
block|}
end_function

begin_function
specifier|static
name|void
DECL|function|gimp_warp_tool_init (GimpWarpTool * self)
name|gimp_warp_tool_init
parameter_list|(
name|GimpWarpTool
modifier|*
name|self
parameter_list|)
block|{
name|GimpTool
modifier|*
name|tool
init|=
name|GIMP_TOOL
argument_list|(
name|self
argument_list|)
decl_stmt|;
name|gimp_tool_control_set_motion_mode
argument_list|(
name|tool
operator|->
name|control
argument_list|,
name|GIMP_MOTION_MODE_EXACT
argument_list|)
expr_stmt|;
name|gimp_tool_control_set_dirty_mask
argument_list|(
name|tool
operator|->
name|control
argument_list|,
name|GIMP_DIRTY_IMAGE
operator||
name|GIMP_DIRTY_IMAGE_STRUCTURE
operator||
name|GIMP_DIRTY_DRAWABLE
operator||
name|GIMP_DIRTY_SELECTION
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
name|GIMP_TOOL_CURSOR_PERSPECTIVE
argument_list|)
expr_stmt|;
name|self
operator|->
name|coords_buffer
operator|=
name|NULL
expr_stmt|;
name|self
operator|->
name|render_node
operator|=
name|NULL
expr_stmt|;
name|self
operator|->
name|image_map
operator|=
name|NULL
expr_stmt|;
block|}
end_function

begin_function
specifier|static
name|void
DECL|function|gimp_warp_tool_control (GimpTool * tool,GimpToolAction action,GimpDisplay * display)
name|gimp_warp_tool_control
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
name|GimpWarpTool
modifier|*
name|wt
init|=
name|GIMP_WARP_TOOL
argument_list|(
name|tool
argument_list|)
decl_stmt|;
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
if|if
condition|(
name|wt
operator|->
name|coords_buffer
condition|)
block|{
name|gegl_buffer_destroy
argument_list|(
name|wt
operator|->
name|coords_buffer
argument_list|)
expr_stmt|;
name|wt
operator|->
name|coords_buffer
operator|=
name|NULL
expr_stmt|;
block|}
if|if
condition|(
name|wt
operator|->
name|graph
condition|)
block|{
name|g_object_unref
argument_list|(
name|wt
operator|->
name|graph
argument_list|)
expr_stmt|;
name|wt
operator|->
name|graph
operator|=
name|NULL
expr_stmt|;
block|}
if|if
condition|(
name|wt
operator|->
name|image_map
condition|)
block|{
name|gimp_tool_control_set_preserve
argument_list|(
name|tool
operator|->
name|control
argument_list|,
name|TRUE
argument_list|)
expr_stmt|;
name|gimp_image_map_abort
argument_list|(
name|wt
operator|->
name|image_map
argument_list|)
expr_stmt|;
name|g_object_unref
argument_list|(
name|wt
operator|->
name|image_map
argument_list|)
expr_stmt|;
name|wt
operator|->
name|image_map
operator|=
name|NULL
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
name|gimp_image_flush
argument_list|(
name|gimp_display_get_image
argument_list|(
name|tool
operator|->
name|display
argument_list|)
argument_list|)
expr_stmt|;
block|}
name|tool
operator|->
name|display
operator|=
name|NULL
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
DECL|function|gimp_warp_tool_start (GimpWarpTool * wt,GimpDisplay * display)
name|gimp_warp_tool_start
parameter_list|(
name|GimpWarpTool
modifier|*
name|wt
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
name|wt
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
name|GimpDrawable
modifier|*
name|drawable
init|=
name|gimp_image_get_active_drawable
argument_list|(
name|image
argument_list|)
decl_stmt|;
name|Babl
modifier|*
name|format
decl_stmt|;
name|gint
name|x1
decl_stmt|,
name|x2
decl_stmt|,
name|y1
decl_stmt|,
name|y2
decl_stmt|;
name|GeglRectangle
name|bbox
decl_stmt|;
name|gimp_tool_control
argument_list|(
name|tool
argument_list|,
name|GIMP_TOOL_ACTION_HALT
argument_list|,
name|display
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
name|wt
operator|->
name|coords_buffer
condition|)
block|{
name|gegl_buffer_destroy
argument_list|(
name|wt
operator|->
name|coords_buffer
argument_list|)
expr_stmt|;
name|wt
operator|->
name|coords_buffer
operator|=
name|NULL
expr_stmt|;
block|}
if|if
condition|(
name|wt
operator|->
name|graph
condition|)
block|{
name|g_object_unref
argument_list|(
name|wt
operator|->
name|graph
argument_list|)
expr_stmt|;
name|wt
operator|->
name|graph
operator|=
name|NULL
expr_stmt|;
block|}
if|if
condition|(
name|wt
operator|->
name|image_map
condition|)
block|{
name|gimp_image_map_abort
argument_list|(
name|wt
operator|->
name|image_map
argument_list|)
expr_stmt|;
name|g_object_unref
argument_list|(
name|wt
operator|->
name|image_map
argument_list|)
expr_stmt|;
name|wt
operator|->
name|image_map
operator|=
name|NULL
expr_stmt|;
block|}
comment|/* Create the coords buffer, with the size of the selection */
name|format
operator|=
name|babl_format_n
argument_list|(
name|babl_type
argument_list|(
literal|"float"
argument_list|)
argument_list|,
literal|2
argument_list|)
expr_stmt|;
name|gimp_channel_bounds
argument_list|(
name|gimp_image_get_mask
argument_list|(
name|image
argument_list|)
argument_list|,
operator|&
name|x1
argument_list|,
operator|&
name|y1
argument_list|,
operator|&
name|x2
argument_list|,
operator|&
name|y2
argument_list|)
expr_stmt|;
name|bbox
operator|.
name|x
operator|=
name|MIN
argument_list|(
name|x1
argument_list|,
name|x2
argument_list|)
expr_stmt|;
name|bbox
operator|.
name|y
operator|=
name|MIN
argument_list|(
name|y1
argument_list|,
name|y2
argument_list|)
expr_stmt|;
name|bbox
operator|.
name|width
operator|=
name|ABS
argument_list|(
name|x1
operator|-
name|x2
argument_list|)
expr_stmt|;
name|bbox
operator|.
name|height
operator|=
name|ABS
argument_list|(
name|y1
operator|-
name|y2
argument_list|)
expr_stmt|;
name|printf
argument_list|(
literal|"Initialize coordinate buffer (%d,%d) at %d,%d\n"
argument_list|,
name|bbox
operator|.
name|width
argument_list|,
name|bbox
operator|.
name|height
argument_list|,
name|bbox
operator|.
name|x
argument_list|,
name|bbox
operator|.
name|y
argument_list|)
expr_stmt|;
name|wt
operator|->
name|coords_buffer
operator|=
name|gegl_buffer_new
argument_list|(
operator|&
name|bbox
argument_list|,
name|format
argument_list|)
expr_stmt|;
name|gimp_warp_tool_create_image_map
argument_list|(
name|wt
argument_list|,
name|drawable
argument_list|)
expr_stmt|;
name|gimp_draw_tool_start
argument_list|(
name|GIMP_DRAW_TOOL
argument_list|(
name|wt
argument_list|)
argument_list|,
name|display
argument_list|)
expr_stmt|;
block|}
end_function

begin_function
specifier|static
name|gboolean
DECL|function|gimp_warp_tool_key_press (GimpTool * tool,GdkEventKey * kevent,GimpDisplay * display)
name|gimp_warp_tool_key_press
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
name|GimpWarpTool
modifier|*
name|wt
init|=
name|GIMP_WARP_TOOL
argument_list|(
name|tool
argument_list|)
decl_stmt|;
switch|switch
condition|(
name|kevent
operator|->
name|keyval
condition|)
block|{
case|case
name|GDK_KEY_BackSpace
case|:
case|case
name|GDK_KEY_Return
case|:
return|return
name|TRUE
return|;
case|case
name|GDK_KEY_KP_Enter
case|:
case|case
name|GDK_KEY_ISO_Enter
case|:
name|gimp_tool_control_set_preserve
argument_list|(
name|tool
operator|->
name|control
argument_list|,
name|TRUE
argument_list|)
expr_stmt|;
name|gimp_image_map_commit
argument_list|(
name|wt
operator|->
name|image_map
argument_list|)
expr_stmt|;
name|g_object_unref
argument_list|(
name|wt
operator|->
name|image_map
argument_list|)
expr_stmt|;
name|wt
operator|->
name|image_map
operator|=
name|NULL
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
name|gimp_image_flush
argument_list|(
name|gimp_display_get_image
argument_list|(
name|display
argument_list|)
argument_list|)
expr_stmt|;
name|gimp_tool_control
argument_list|(
name|tool
argument_list|,
name|GIMP_TOOL_ACTION_HALT
argument_list|,
name|display
argument_list|)
expr_stmt|;
return|return
name|TRUE
return|;
case|case
name|GDK_KEY_Escape
case|:
name|gimp_tool_control
argument_list|(
name|tool
argument_list|,
name|GIMP_TOOL_ACTION_HALT
argument_list|,
name|display
argument_list|)
expr_stmt|;
return|return
name|TRUE
return|;
default|default:
break|break;
block|}
return|return
name|FALSE
return|;
block|}
end_function

begin_function
specifier|static
name|void
DECL|function|gimp_warp_tool_motion (GimpTool * tool,const GimpCoords * coords,guint32 time,GdkModifierType state,GimpDisplay * display)
name|gimp_warp_tool_motion
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
name|GimpWarpTool
modifier|*
name|wt
init|=
name|GIMP_WARP_TOOL
argument_list|(
name|tool
argument_list|)
decl_stmt|;
name|wt
operator|->
name|cursor_x
operator|=
name|coords
operator|->
name|x
expr_stmt|;
name|wt
operator|->
name|cursor_y
operator|=
name|coords
operator|->
name|y
expr_stmt|;
block|}
end_function

begin_function
specifier|static
name|void
DECL|function|gimp_warp_tool_oper_update (GimpTool * tool,const GimpCoords * coords,GdkModifierType state,gboolean proximity,GimpDisplay * display)
name|gimp_warp_tool_oper_update
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
name|gboolean
name|proximity
parameter_list|,
name|GimpDisplay
modifier|*
name|display
parameter_list|)
block|{
name|GimpWarpTool
modifier|*
name|wt
init|=
name|GIMP_WARP_TOOL
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
if|if
condition|(
operator|!
name|gimp_draw_tool_is_active
argument_list|(
name|draw_tool
argument_list|)
condition|)
block|{
name|gimp_warp_tool_start
argument_list|(
name|wt
argument_list|,
name|display
argument_list|)
expr_stmt|;
block|}
else|else
block|{
if|if
condition|(
name|display
operator|==
name|tool
operator|->
name|display
condition|)
block|{
name|gimp_draw_tool_pause
argument_list|(
name|draw_tool
argument_list|)
expr_stmt|;
name|wt
operator|->
name|cursor_x
operator|=
name|coords
operator|->
name|x
expr_stmt|;
name|wt
operator|->
name|cursor_y
operator|=
name|coords
operator|->
name|y
expr_stmt|;
name|gimp_draw_tool_resume
argument_list|(
name|draw_tool
argument_list|)
expr_stmt|;
block|}
block|}
block|}
end_function

begin_function
specifier|static
name|void
DECL|function|gimp_warp_tool_button_press (GimpTool * tool,const GimpCoords * coords,guint32 time,GdkModifierType state,GimpButtonPressType press_type,GimpDisplay * display)
name|gimp_warp_tool_button_press
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
name|GimpWarpTool
modifier|*
name|wt
init|=
name|GIMP_WARP_TOOL
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
name|gimp_warp_tool_start
argument_list|(
name|wt
argument_list|,
name|display
argument_list|)
expr_stmt|;
name|wt
operator|->
name|current_stroke
operator|=
name|gegl_path_new
argument_list|()
expr_stmt|;
name|gegl_path_append
argument_list|(
name|wt
operator|->
name|current_stroke
argument_list|,
literal|'M'
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
name|gimp_warp_tool_add_op
argument_list|(
name|wt
argument_list|)
expr_stmt|;
name|wt
operator|->
name|stroke_timer
operator|=
name|g_timeout_add
argument_list|(
name|STROKE_PERIOD
argument_list|,
name|gimp_warp_tool_stroke_timer
argument_list|,
name|wt
argument_list|)
expr_stmt|;
name|wt
operator|->
name|preview_timer
operator|=
name|g_timeout_add
argument_list|(
name|PREVIEW_PERIOD
argument_list|,
name|gimp_warp_tool_preview_timer
argument_list|,
name|wt
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
end_function

begin_function
name|void
DECL|function|gimp_warp_tool_button_release (GimpTool * tool,const GimpCoords * coords,guint32 time,GdkModifierType state,GimpButtonReleaseType release_type,GimpDisplay * display)
name|gimp_warp_tool_button_release
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
name|GimpWarpTool
modifier|*
name|wt
init|=
name|GIMP_WARP_TOOL
argument_list|(
name|tool
argument_list|)
decl_stmt|;
name|gimp_draw_tool_pause
argument_list|(
name|GIMP_DRAW_TOOL
argument_list|(
name|wt
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
name|g_source_remove
argument_list|(
name|wt
operator|->
name|stroke_timer
argument_list|)
expr_stmt|;
name|g_source_remove
argument_list|(
name|wt
operator|->
name|preview_timer
argument_list|)
expr_stmt|;
name|printf
argument_list|(
literal|"%s\n"
argument_list|,
name|gegl_path_to_string
argument_list|(
name|wt
operator|->
name|current_stroke
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
name|gimp_warp_tool_undo
argument_list|(
name|wt
argument_list|)
expr_stmt|;
block|}
else|else
block|{
name|gimp_warp_tool_image_map_update
argument_list|(
name|wt
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
end_function

begin_function
specifier|static
name|void
DECL|function|gimp_warp_tool_cursor_update (GimpTool * tool,const GimpCoords * coords,GdkModifierType state,GimpDisplay * display)
name|gimp_warp_tool_cursor_update
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
name|GimpCursorModifier
name|modifier
init|=
name|GIMP_CURSOR_MODIFIER_PLUS
decl_stmt|;
if|if
condition|(
name|tool
operator|->
name|display
condition|)
block|{
name|modifier
operator|=
name|GIMP_CURSOR_MODIFIER_MOVE
expr_stmt|;
block|}
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
name|gboolean
DECL|function|gimp_warp_tool_stroke_timer (gpointer data)
name|gimp_warp_tool_stroke_timer
parameter_list|(
name|gpointer
name|data
parameter_list|)
block|{
name|GimpWarpTool
modifier|*
name|wt
init|=
name|GIMP_WARP_TOOL
argument_list|(
name|data
argument_list|)
decl_stmt|;
name|gegl_path_append
argument_list|(
name|wt
operator|->
name|current_stroke
argument_list|,
literal|'L'
argument_list|,
name|wt
operator|->
name|cursor_x
argument_list|,
name|wt
operator|->
name|cursor_y
argument_list|)
expr_stmt|;
return|return
name|TRUE
return|;
block|}
end_function

begin_function
specifier|static
name|gboolean
DECL|function|gimp_warp_tool_preview_timer (gpointer data)
name|gimp_warp_tool_preview_timer
parameter_list|(
name|gpointer
name|data
parameter_list|)
block|{
name|GimpWarpTool
modifier|*
name|wt
init|=
name|GIMP_WARP_TOOL
argument_list|(
name|data
argument_list|)
decl_stmt|;
name|gimp_warp_tool_image_map_update
argument_list|(
name|wt
argument_list|)
expr_stmt|;
return|return
name|TRUE
return|;
block|}
end_function

begin_function
specifier|static
name|void
DECL|function|gimp_warp_tool_draw (GimpDrawTool * draw_tool)
name|gimp_warp_tool_draw
parameter_list|(
name|GimpDrawTool
modifier|*
name|draw_tool
parameter_list|)
block|{
name|GimpWarpTool
modifier|*
name|wt
init|=
name|GIMP_WARP_TOOL
argument_list|(
name|draw_tool
argument_list|)
decl_stmt|;
name|GimpWarpOptions
modifier|*
name|options
init|=
name|GIMP_WARP_TOOL_GET_OPTIONS
argument_list|(
name|wt
argument_list|)
decl_stmt|;
name|gimp_draw_tool_add_arc
argument_list|(
name|draw_tool
argument_list|,
name|FALSE
argument_list|,
name|wt
operator|->
name|cursor_x
operator|-
name|options
operator|->
name|effect_size
operator|/
literal|2.0
argument_list|,
name|wt
operator|->
name|cursor_y
operator|-
name|options
operator|->
name|effect_size
operator|/
literal|2.0
argument_list|,
name|options
operator|->
name|effect_size
argument_list|,
name|options
operator|->
name|effect_size
argument_list|,
literal|0.0
argument_list|,
literal|2.0
operator|*
name|G_PI
argument_list|)
expr_stmt|;
block|}
end_function

begin_function
specifier|static
name|void
DECL|function|gimp_warp_tool_create_graph (GimpWarpTool * wt)
name|gimp_warp_tool_create_graph
parameter_list|(
name|GimpWarpTool
modifier|*
name|wt
parameter_list|)
block|{
name|GeglNode
modifier|*
name|coords
decl_stmt|,
modifier|*
name|render
decl_stmt|;
comment|/* Render nodes */
name|GeglNode
modifier|*
name|input
decl_stmt|,
modifier|*
name|output
decl_stmt|;
comment|/* Proxy nodes*/
name|GeglNode
modifier|*
name|graph
decl_stmt|;
comment|/* wraper to be returned */
name|g_return_if_fail
argument_list|(
name|wt
operator|->
name|graph
operator|==
name|NULL
argument_list|)
expr_stmt|;
comment|/* render_node is not supposed to be recreated */
name|graph
operator|=
name|gegl_node_new
argument_list|()
expr_stmt|;
name|input
operator|=
name|gegl_node_get_input_proxy
argument_list|(
name|graph
argument_list|,
literal|"input"
argument_list|)
expr_stmt|;
name|output
operator|=
name|gegl_node_get_output_proxy
argument_list|(
name|graph
argument_list|,
literal|"output"
argument_list|)
expr_stmt|;
name|coords
operator|=
name|gegl_node_new_child
argument_list|(
name|graph
argument_list|,
literal|"operation"
argument_list|,
literal|"gegl:buffer-source"
argument_list|,
literal|"buffer"
argument_list|,
name|wt
operator|->
name|coords_buffer
argument_list|,
name|NULL
argument_list|)
expr_stmt|;
name|render
operator|=
name|gegl_node_new_child
argument_list|(
name|graph
argument_list|,
literal|"operation"
argument_list|,
literal|"gegl:map-relative"
argument_list|,
name|NULL
argument_list|)
expr_stmt|;
name|gegl_node_connect_to
argument_list|(
name|input
argument_list|,
literal|"output"
argument_list|,
name|render
argument_list|,
literal|"input"
argument_list|)
expr_stmt|;
name|gegl_node_connect_to
argument_list|(
name|coords
argument_list|,
literal|"output"
argument_list|,
name|render
argument_list|,
literal|"aux"
argument_list|)
expr_stmt|;
name|gegl_node_connect_to
argument_list|(
name|render
argument_list|,
literal|"output"
argument_list|,
name|output
argument_list|,
literal|"input"
argument_list|)
expr_stmt|;
name|wt
operator|->
name|graph
operator|=
name|graph
expr_stmt|;
name|wt
operator|->
name|render_node
operator|=
name|render
expr_stmt|;
name|wt
operator|->
name|read_coords_buffer_node
operator|=
name|coords
expr_stmt|;
block|}
end_function

begin_function
specifier|static
name|void
DECL|function|gimp_warp_tool_create_image_map (GimpWarpTool * wt,GimpDrawable * drawable)
name|gimp_warp_tool_create_image_map
parameter_list|(
name|GimpWarpTool
modifier|*
name|wt
parameter_list|,
name|GimpDrawable
modifier|*
name|drawable
parameter_list|)
block|{
if|if
condition|(
operator|!
name|wt
operator|->
name|graph
condition|)
name|gimp_warp_tool_create_graph
argument_list|(
name|wt
argument_list|)
expr_stmt|;
name|wt
operator|->
name|image_map
operator|=
name|gimp_image_map_new
argument_list|(
name|drawable
argument_list|,
name|_
argument_list|(
literal|"Warp transform"
argument_list|)
argument_list|,
name|wt
operator|->
name|graph
argument_list|,
name|NULL
argument_list|,
name|NULL
argument_list|)
expr_stmt|;
name|g_object_set
argument_list|(
name|wt
operator|->
name|image_map
argument_list|,
literal|"gegl-caching"
argument_list|,
name|TRUE
argument_list|,
name|NULL
argument_list|)
expr_stmt|;
name|g_signal_connect
argument_list|(
name|wt
operator|->
name|image_map
argument_list|,
literal|"flush"
argument_list|,
name|G_CALLBACK
argument_list|(
name|gimp_warp_tool_image_map_flush
argument_list|)
argument_list|,
name|wt
argument_list|)
expr_stmt|;
block|}
end_function

begin_function
specifier|static
name|void
DECL|function|gimp_warp_tool_image_map_update (GimpWarpTool * wt)
name|gimp_warp_tool_image_map_update
parameter_list|(
name|GimpWarpTool
modifier|*
name|wt
parameter_list|)
block|{
name|GimpTool
modifier|*
name|tool
init|=
name|GIMP_TOOL
argument_list|(
name|wt
argument_list|)
decl_stmt|;
name|GimpDisplayShell
modifier|*
name|shell
init|=
name|gimp_display_get_shell
argument_list|(
name|tool
operator|->
name|display
argument_list|)
decl_stmt|;
name|GimpItem
modifier|*
name|item
init|=
name|GIMP_ITEM
argument_list|(
name|tool
operator|->
name|drawable
argument_list|)
decl_stmt|;
name|gint
name|x
decl_stmt|,
name|y
decl_stmt|;
name|gint
name|w
decl_stmt|,
name|h
decl_stmt|;
name|gint
name|off_x
decl_stmt|,
name|off_y
decl_stmt|;
name|GeglRectangle
name|visible
decl_stmt|;
name|gimp_display_shell_untransform_viewport
argument_list|(
name|shell
argument_list|,
operator|&
name|x
argument_list|,
operator|&
name|y
argument_list|,
operator|&
name|w
argument_list|,
operator|&
name|h
argument_list|)
expr_stmt|;
name|gimp_item_get_offset
argument_list|(
name|item
argument_list|,
operator|&
name|off_x
argument_list|,
operator|&
name|off_y
argument_list|)
expr_stmt|;
name|gimp_rectangle_intersect
argument_list|(
name|x
argument_list|,
name|y
argument_list|,
name|w
argument_list|,
name|h
argument_list|,
name|off_x
argument_list|,
name|off_y
argument_list|,
name|gimp_item_get_width
argument_list|(
name|item
argument_list|)
argument_list|,
name|gimp_item_get_height
argument_list|(
name|item
argument_list|)
argument_list|,
operator|&
name|visible
operator|.
name|x
argument_list|,
operator|&
name|visible
operator|.
name|y
argument_list|,
operator|&
name|visible
operator|.
name|width
argument_list|,
operator|&
name|visible
operator|.
name|height
argument_list|)
expr_stmt|;
name|visible
operator|.
name|x
operator|-=
name|off_x
expr_stmt|;
name|visible
operator|.
name|y
operator|-=
name|off_y
expr_stmt|;
name|gimp_image_map_apply
argument_list|(
name|wt
operator|->
name|image_map
argument_list|,
operator|&
name|visible
argument_list|)
expr_stmt|;
block|}
end_function

begin_function
specifier|static
name|void
DECL|function|gimp_warp_tool_image_map_flush (GimpImageMap * image_map,GimpTool * tool)
name|gimp_warp_tool_image_map_flush
parameter_list|(
name|GimpImageMap
modifier|*
name|image_map
parameter_list|,
name|GimpTool
modifier|*
name|tool
parameter_list|)
block|{
name|GimpImage
modifier|*
name|image
init|=
name|gimp_display_get_image
argument_list|(
name|tool
operator|->
name|display
argument_list|)
decl_stmt|;
name|gimp_projection_flush_now
argument_list|(
name|gimp_image_get_projection
argument_list|(
name|image
argument_list|)
argument_list|)
expr_stmt|;
name|gimp_display_flush_now
argument_list|(
name|tool
operator|->
name|display
argument_list|)
expr_stmt|;
block|}
end_function

begin_function
specifier|static
name|void
DECL|function|gimp_warp_tool_add_op (GimpWarpTool * wt)
name|gimp_warp_tool_add_op
parameter_list|(
name|GimpWarpTool
modifier|*
name|wt
parameter_list|)
block|{
name|GimpWarpOptions
modifier|*
name|options
init|=
name|GIMP_WARP_TOOL_GET_OPTIONS
argument_list|(
name|wt
argument_list|)
decl_stmt|;
name|GeglNode
modifier|*
name|new_op
decl_stmt|,
modifier|*
name|last_op
decl_stmt|;
name|g_return_if_fail
argument_list|(
name|GEGL_IS_NODE
argument_list|(
name|wt
operator|->
name|render_node
argument_list|)
argument_list|)
expr_stmt|;
name|new_op
operator|=
name|gegl_node_new_child
argument_list|(
name|wt
operator|->
name|graph
argument_list|,
literal|"operation"
argument_list|,
literal|"gegl:warp"
argument_list|,
literal|"behavior"
argument_list|,
name|options
operator|->
name|behavior
argument_list|,
literal|"strength"
argument_list|,
name|options
operator|->
name|effect_strength
argument_list|,
literal|"size"
argument_list|,
name|options
operator|->
name|effect_size
argument_list|,
literal|"hardness"
argument_list|,
name|options
operator|->
name|effect_hardness
argument_list|,
literal|"stroke"
argument_list|,
name|wt
operator|->
name|current_stroke
argument_list|,
name|NULL
argument_list|)
expr_stmt|;
name|last_op
operator|=
name|gegl_node_get_producer
argument_list|(
name|wt
operator|->
name|render_node
argument_list|,
literal|"aux"
argument_list|,
name|NULL
argument_list|)
expr_stmt|;
name|gegl_node_disconnect
argument_list|(
name|wt
operator|->
name|render_node
argument_list|,
literal|"aux"
argument_list|)
expr_stmt|;
name|gegl_node_connect_to
argument_list|(
name|last_op
argument_list|,
literal|"output"
argument_list|,
name|new_op
argument_list|,
literal|"input"
argument_list|)
expr_stmt|;
name|gegl_node_connect_to
argument_list|(
name|new_op
argument_list|,
literal|"output"
argument_list|,
name|wt
operator|->
name|render_node
argument_list|,
literal|"aux"
argument_list|)
expr_stmt|;
block|}
end_function

begin_function
specifier|static
name|void
DECL|function|gimp_warp_tool_undo (GimpWarpTool * wt)
name|gimp_warp_tool_undo
parameter_list|(
name|GimpWarpTool
modifier|*
name|wt
parameter_list|)
block|{
name|GeglNode
modifier|*
name|to_delete
decl_stmt|;
name|GeglNode
modifier|*
name|previous
decl_stmt|;
specifier|const
name|gchar
modifier|*
name|type
decl_stmt|;
name|to_delete
operator|=
name|gegl_node_get_producer
argument_list|(
name|wt
operator|->
name|render_node
argument_list|,
literal|"aux"
argument_list|,
name|NULL
argument_list|)
expr_stmt|;
name|type
operator|=
name|gegl_node_get_operation
argument_list|(
name|to_delete
argument_list|)
expr_stmt|;
if|if
condition|(
name|strcmp
argument_list|(
name|type
argument_list|,
literal|"gimp:warp"
argument_list|)
condition|)
return|return;
name|previous
operator|=
name|gegl_node_get_producer
argument_list|(
name|to_delete
argument_list|,
literal|"input"
argument_list|,
name|NULL
argument_list|)
expr_stmt|;
name|gegl_node_disconnect
argument_list|(
name|to_delete
argument_list|,
literal|"input"
argument_list|)
expr_stmt|;
name|gegl_node_connect_to
argument_list|(
name|previous
argument_list|,
literal|"output"
argument_list|,
name|wt
operator|->
name|render_node
argument_list|,
literal|"aux"
argument_list|)
expr_stmt|;
name|g_object_unref
argument_list|(
name|to_delete
argument_list|)
expr_stmt|;
name|gimp_warp_tool_image_map_update
argument_list|(
name|wt
argument_list|)
expr_stmt|;
block|}
end_function

end_unit

