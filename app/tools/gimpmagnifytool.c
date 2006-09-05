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
file|<gdk/gdkkeysyms.h>
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
file|"config/gimpdisplayconfig.h"
end_include

begin_include
include|#
directive|include
file|"core/gimp.h"
end_include

begin_include
include|#
directive|include
file|"core/gimpimage.h"
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
file|"display/gimpdisplayshell-scale.h"
end_include

begin_include
include|#
directive|include
file|"widgets/gimphelp-ids.h"
end_include

begin_include
include|#
directive|include
file|"widgets/gimpwidgets-utils.h"
end_include

begin_include
include|#
directive|include
file|"gimpmagnifyoptions.h"
end_include

begin_include
include|#
directive|include
file|"gimpmagnifytool.h"
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
name|gimp_magnify_tool_button_press
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
name|gimp_magnify_tool_button_release
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
name|gimp_magnify_tool_motion
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
name|gimp_magnify_tool_modifier_key
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
name|display
parameter_list|)
function_decl|;
end_function_decl

begin_function_decl
specifier|static
name|void
name|gimp_magnify_tool_cursor_update
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
name|display
parameter_list|)
function_decl|;
end_function_decl

begin_function_decl
specifier|static
name|void
name|gimp_magnify_tool_draw
parameter_list|(
name|GimpDrawTool
modifier|*
name|draw_tool
parameter_list|)
function_decl|;
end_function_decl

begin_macro
DECL|function|G_DEFINE_TYPE (GimpMagnifyTool,gimp_magnify_tool,GIMP_TYPE_DRAW_TOOL)
name|G_DEFINE_TYPE
argument_list|(
argument|GimpMagnifyTool
argument_list|,
argument|gimp_magnify_tool
argument_list|,
argument|GIMP_TYPE_DRAW_TOOL
argument_list|)
end_macro

begin_define
DECL|macro|parent_class
define|#
directive|define
name|parent_class
value|gimp_magnify_tool_parent_class
end_define

begin_function
name|void
name|gimp_magnify_tool_register
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
name|GIMP_TYPE_MAGNIFY_TOOL
argument_list|,
name|GIMP_TYPE_MAGNIFY_OPTIONS
argument_list|,
name|gimp_magnify_options_gui
argument_list|,
literal|0
argument_list|,
literal|"gimp-zoom-tool"
argument_list|,
name|_
argument_list|(
literal|"Zoom"
argument_list|)
argument_list|,
name|_
argument_list|(
literal|"Zoom in& out"
argument_list|)
argument_list|,
name|N_
argument_list|(
literal|"tool|_Zoom"
argument_list|)
argument_list|,
literal|"Z"
argument_list|,
name|NULL
argument_list|,
name|GIMP_HELP_TOOL_ZOOM
argument_list|,
name|GIMP_STOCK_TOOL_ZOOM
argument_list|,
name|data
argument_list|)
expr_stmt|;
block|}
end_function

begin_function
specifier|static
name|void
DECL|function|gimp_magnify_tool_class_init (GimpMagnifyToolClass * klass)
name|gimp_magnify_tool_class_init
parameter_list|(
name|GimpMagnifyToolClass
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
name|gimp_magnify_tool_button_press
expr_stmt|;
name|tool_class
operator|->
name|button_release
operator|=
name|gimp_magnify_tool_button_release
expr_stmt|;
name|tool_class
operator|->
name|motion
operator|=
name|gimp_magnify_tool_motion
expr_stmt|;
name|tool_class
operator|->
name|modifier_key
operator|=
name|gimp_magnify_tool_modifier_key
expr_stmt|;
name|tool_class
operator|->
name|cursor_update
operator|=
name|gimp_magnify_tool_cursor_update
expr_stmt|;
name|draw_tool_class
operator|->
name|draw
operator|=
name|gimp_magnify_tool_draw
expr_stmt|;
block|}
end_function

begin_function
specifier|static
name|void
DECL|function|gimp_magnify_tool_init (GimpMagnifyTool * magnify_tool)
name|gimp_magnify_tool_init
parameter_list|(
name|GimpMagnifyTool
modifier|*
name|magnify_tool
parameter_list|)
block|{
name|GimpTool
modifier|*
name|tool
init|=
name|GIMP_TOOL
argument_list|(
name|magnify_tool
argument_list|)
decl_stmt|;
name|magnify_tool
operator|->
name|x
operator|=
literal|0
expr_stmt|;
name|magnify_tool
operator|->
name|y
operator|=
literal|0
expr_stmt|;
name|magnify_tool
operator|->
name|w
operator|=
literal|0
expr_stmt|;
name|magnify_tool
operator|->
name|h
operator|=
literal|0
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
name|gimp_tool_control_set_handle_empty_image
argument_list|(
name|tool
operator|->
name|control
argument_list|,
name|TRUE
argument_list|)
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
name|gimp_tool_control_set_cursor
argument_list|(
name|tool
operator|->
name|control
argument_list|,
name|GIMP_CURSOR_MOUSE
argument_list|)
expr_stmt|;
name|gimp_tool_control_set_tool_cursor
argument_list|(
name|tool
operator|->
name|control
argument_list|,
name|GIMP_TOOL_CURSOR_ZOOM
argument_list|)
expr_stmt|;
name|gimp_tool_control_set_cursor_modifier
argument_list|(
name|tool
operator|->
name|control
argument_list|,
name|GIMP_CURSOR_MODIFIER_PLUS
argument_list|)
expr_stmt|;
name|gimp_tool_control_set_toggle_cursor_modifier
argument_list|(
name|tool
operator|->
name|control
argument_list|,
name|GIMP_CURSOR_MODIFIER_MINUS
argument_list|)
expr_stmt|;
block|}
end_function

begin_function
specifier|static
name|void
DECL|function|gimp_magnify_tool_button_press (GimpTool * tool,GimpCoords * coords,guint32 time,GdkModifierType state,GimpDisplay * display)
name|gimp_magnify_tool_button_press
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
name|GimpMagnifyTool
modifier|*
name|magnify
init|=
name|GIMP_MAGNIFY_TOOL
argument_list|(
name|tool
argument_list|)
decl_stmt|;
name|magnify
operator|->
name|x
operator|=
name|coords
operator|->
name|x
expr_stmt|;
name|magnify
operator|->
name|y
operator|=
name|coords
operator|->
name|y
expr_stmt|;
name|magnify
operator|->
name|w
operator|=
literal|0
expr_stmt|;
name|magnify
operator|->
name|h
operator|=
literal|0
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
DECL|function|gimp_magnify_tool_button_release (GimpTool * tool,GimpCoords * coords,guint32 time,GdkModifierType state,GimpDisplay * display)
name|gimp_magnify_tool_button_release
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
name|GimpMagnifyTool
modifier|*
name|magnify
init|=
name|GIMP_MAGNIFY_TOOL
argument_list|(
name|tool
argument_list|)
decl_stmt|;
name|GimpMagnifyOptions
modifier|*
name|options
init|=
name|GIMP_MAGNIFY_TOOL_GET_OPTIONS
argument_list|(
name|tool
argument_list|)
decl_stmt|;
name|GimpDisplayShell
modifier|*
name|shell
decl_stmt|;
name|gdouble
name|current
decl_stmt|;
name|shell
operator|=
name|GIMP_DISPLAY_SHELL
argument_list|(
name|tool
operator|->
name|display
operator|->
name|shell
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
name|gint
name|x1
decl_stmt|,
name|y1
decl_stmt|,
name|x2
decl_stmt|,
name|y2
decl_stmt|,
name|w
decl_stmt|,
name|h
decl_stmt|;
name|gint
name|win_width
decl_stmt|,
name|win_height
decl_stmt|;
name|gint
name|offset_x
decl_stmt|,
name|offset_y
decl_stmt|;
name|gdouble
name|new_scale
decl_stmt|;
name|x1
operator|=
operator|(
name|magnify
operator|->
name|w
operator|<
literal|0
operator|)
condition|?
name|magnify
operator|->
name|x
operator|+
name|magnify
operator|->
name|w
else|:
name|magnify
operator|->
name|x
expr_stmt|;
name|y1
operator|=
operator|(
name|magnify
operator|->
name|h
operator|<
literal|0
operator|)
condition|?
name|magnify
operator|->
name|y
operator|+
name|magnify
operator|->
name|h
else|:
name|magnify
operator|->
name|y
expr_stmt|;
name|w
operator|=
operator|(
name|magnify
operator|->
name|w
operator|<
literal|0
operator|)
condition|?
operator|-
name|magnify
operator|->
name|w
else|:
name|magnify
operator|->
name|w
expr_stmt|;
name|h
operator|=
operator|(
name|magnify
operator|->
name|h
operator|<
literal|0
operator|)
condition|?
operator|-
name|magnify
operator|->
name|h
else|:
name|magnify
operator|->
name|h
expr_stmt|;
name|x2
operator|=
name|x1
operator|+
name|w
expr_stmt|;
name|y2
operator|=
name|y1
operator|+
name|h
expr_stmt|;
name|win_width
operator|=
name|shell
operator|->
name|disp_width
expr_stmt|;
name|win_height
operator|=
name|shell
operator|->
name|disp_height
expr_stmt|;
name|current
operator|=
name|gimp_zoom_model_get_factor
argument_list|(
name|shell
operator|->
name|zoom
argument_list|)
expr_stmt|;
comment|/* we need to compute the mouse movement in screen coordinates */
if|if
condition|(
operator|(
name|SCALEX
argument_list|(
name|shell
argument_list|,
name|w
argument_list|)
operator|<
name|options
operator|->
name|threshold
operator|)
operator|||
operator|(
name|SCALEY
argument_list|(
name|shell
argument_list|,
name|h
argument_list|)
operator|<
name|options
operator|->
name|threshold
operator|)
condition|)
block|{
name|new_scale
operator|=
name|gimp_zoom_model_zoom_step
argument_list|(
name|options
operator|->
name|zoom_type
argument_list|,
name|current
argument_list|)
expr_stmt|;
block|}
else|else
block|{
name|gint
name|width
decl_stmt|,
name|height
decl_stmt|;
name|gdouble
name|scale
init|=
literal|1.0
decl_stmt|;
name|width
operator|=
name|UNSCALEX
argument_list|(
name|shell
argument_list|,
name|win_width
argument_list|)
expr_stmt|;
name|height
operator|=
name|UNSCALEY
argument_list|(
name|shell
argument_list|,
name|win_height
argument_list|)
expr_stmt|;
switch|switch
condition|(
name|options
operator|->
name|zoom_type
condition|)
block|{
case|case
name|GIMP_ZOOM_IN
case|:
name|scale
operator|=
name|MIN
argument_list|(
operator|(
operator|(
name|gdouble
operator|)
name|width
operator|/
operator|(
name|gdouble
operator|)
name|w
operator|)
argument_list|,
operator|(
operator|(
name|gdouble
operator|)
name|height
operator|/
operator|(
name|gdouble
operator|)
name|h
operator|)
argument_list|)
expr_stmt|;
break|break;
case|case
name|GIMP_ZOOM_OUT
case|:
name|scale
operator|=
name|MIN
argument_list|(
operator|(
operator|(
name|gdouble
operator|)
name|w
operator|/
operator|(
name|gdouble
operator|)
name|width
operator|)
argument_list|,
operator|(
operator|(
name|gdouble
operator|)
name|h
operator|/
operator|(
name|gdouble
operator|)
name|height
operator|)
argument_list|)
expr_stmt|;
break|break;
default|default:
break|break;
block|}
name|new_scale
operator|=
name|current
operator|*
name|scale
expr_stmt|;
block|}
name|offset_x
operator|=
operator|(
name|new_scale
operator|*
operator|(
operator|(
name|x1
operator|+
name|x2
operator|)
operator|/
literal|2
operator|)
operator|*
name|SCREEN_XRES
argument_list|(
name|shell
argument_list|)
operator|/
name|display
operator|->
name|image
operator|->
name|xresolution
operator|-
operator|(
name|win_width
operator|/
literal|2
operator|)
operator|)
expr_stmt|;
name|offset_y
operator|=
operator|(
name|new_scale
operator|*
operator|(
operator|(
name|y1
operator|+
name|y2
operator|)
operator|/
literal|2
operator|)
operator|*
name|SCREEN_YRES
argument_list|(
name|shell
argument_list|)
operator|/
name|display
operator|->
name|image
operator|->
name|yresolution
operator|-
operator|(
name|win_height
operator|/
literal|2
operator|)
operator|)
expr_stmt|;
name|gimp_display_shell_scale_by_values
argument_list|(
name|shell
argument_list|,
name|new_scale
argument_list|,
name|offset_x
argument_list|,
name|offset_y
argument_list|,
name|options
operator|->
name|auto_resize
argument_list|)
expr_stmt|;
block|}
block|}
end_function

begin_function
specifier|static
name|void
DECL|function|gimp_magnify_tool_motion (GimpTool * tool,GimpCoords * coords,guint32 time,GdkModifierType state,GimpDisplay * display)
name|gimp_magnify_tool_motion
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
name|GimpMagnifyTool
modifier|*
name|magnify
init|=
name|GIMP_MAGNIFY_TOOL
argument_list|(
name|tool
argument_list|)
decl_stmt|;
name|gimp_draw_tool_pause
argument_list|(
name|GIMP_DRAW_TOOL
argument_list|(
name|tool
argument_list|)
argument_list|)
expr_stmt|;
name|magnify
operator|->
name|w
operator|=
operator|(
name|coords
operator|->
name|x
operator|-
name|magnify
operator|->
name|x
operator|)
expr_stmt|;
name|magnify
operator|->
name|h
operator|=
operator|(
name|coords
operator|->
name|y
operator|-
name|magnify
operator|->
name|y
operator|)
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
DECL|function|gimp_magnify_tool_modifier_key (GimpTool * tool,GdkModifierType key,gboolean press,GdkModifierType state,GimpDisplay * display)
name|gimp_magnify_tool_modifier_key
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
name|display
parameter_list|)
block|{
name|GimpMagnifyOptions
modifier|*
name|options
init|=
name|GIMP_MAGNIFY_TOOL_GET_OPTIONS
argument_list|(
name|tool
argument_list|)
decl_stmt|;
if|if
condition|(
name|key
operator|==
name|GDK_CONTROL_MASK
condition|)
block|{
switch|switch
condition|(
name|options
operator|->
name|zoom_type
condition|)
block|{
case|case
name|GIMP_ZOOM_IN
case|:
name|g_object_set
argument_list|(
name|options
argument_list|,
literal|"zoom-type"
argument_list|,
name|GIMP_ZOOM_OUT
argument_list|,
name|NULL
argument_list|)
expr_stmt|;
break|break;
case|case
name|GIMP_ZOOM_OUT
case|:
name|g_object_set
argument_list|(
name|options
argument_list|,
literal|"zoom-type"
argument_list|,
name|GIMP_ZOOM_IN
argument_list|,
name|NULL
argument_list|)
expr_stmt|;
break|break;
default|default:
break|break;
block|}
block|}
block|}
end_function

begin_function
specifier|static
name|void
DECL|function|gimp_magnify_tool_cursor_update (GimpTool * tool,GimpCoords * coords,GdkModifierType state,GimpDisplay * display)
name|gimp_magnify_tool_cursor_update
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
name|display
parameter_list|)
block|{
name|GimpMagnifyOptions
modifier|*
name|options
init|=
name|GIMP_MAGNIFY_TOOL_GET_OPTIONS
argument_list|(
name|tool
argument_list|)
decl_stmt|;
name|gimp_tool_control_set_toggled
argument_list|(
name|tool
operator|->
name|control
argument_list|,
name|options
operator|->
name|zoom_type
operator|==
name|GIMP_ZOOM_OUT
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
DECL|function|gimp_magnify_tool_draw (GimpDrawTool * draw_tool)
name|gimp_magnify_tool_draw
parameter_list|(
name|GimpDrawTool
modifier|*
name|draw_tool
parameter_list|)
block|{
name|GimpMagnifyTool
modifier|*
name|magnify
init|=
name|GIMP_MAGNIFY_TOOL
argument_list|(
name|draw_tool
argument_list|)
decl_stmt|;
name|gimp_draw_tool_draw_rectangle
argument_list|(
name|draw_tool
argument_list|,
name|FALSE
argument_list|,
name|magnify
operator|->
name|x
argument_list|,
name|magnify
operator|->
name|y
argument_list|,
name|magnify
operator|->
name|w
argument_list|,
name|magnify
operator|->
name|h
argument_list|,
name|FALSE
argument_list|)
expr_stmt|;
block|}
end_function

end_unit

