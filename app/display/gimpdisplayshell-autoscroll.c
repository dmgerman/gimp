begin_unit|revision:0.9.5;language:C;cregit-version:0.0.1
begin_comment
comment|/* GIMP - The GNU Image Manipulation Program  * Copyright (C) 1995 Spencer Kimball and Peter Mattis  *  * This program is free software: you can redistribute it and/or modify  * it under the terms of the GNU General Public License as published by  * the Free Software Foundation; either version 3 of the License, or  * (at your option) any later version.  *  * This program is distributed in the hope that it will be useful,  * but WITHOUT ANY WARRANTY; without even the implied warranty of  * MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the  * GNU General Public License for more details.  *  * You should have received a copy of the GNU General Public License  * along with this program.  If not, see<http://www.gnu.org/licenses/>.  */
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
file|"display-types.h"
end_include

begin_include
include|#
directive|include
file|"widgets/gimpdeviceinfo.h"
end_include

begin_include
include|#
directive|include
file|"widgets/gimpdeviceinfo-coords.h"
end_include

begin_include
include|#
directive|include
file|"gimpdisplay.h"
end_include

begin_include
include|#
directive|include
file|"gimpdisplayshell.h"
end_include

begin_include
include|#
directive|include
file|"gimpdisplayshell-autoscroll.h"
end_include

begin_include
include|#
directive|include
file|"gimpdisplayshell-scroll.h"
end_include

begin_include
include|#
directive|include
file|"gimpdisplayshell-transform.h"
end_include

begin_include
include|#
directive|include
file|"tools/tools-types.h"
end_include

begin_include
include|#
directive|include
file|"tools/tool_manager.h"
end_include

begin_include
include|#
directive|include
file|"tools/gimptool.h"
end_include

begin_include
include|#
directive|include
file|"tools/gimptoolcontrol.h"
end_include

begin_define
DECL|macro|AUTOSCROLL_DT
define|#
directive|define
name|AUTOSCROLL_DT
value|20
end_define

begin_define
DECL|macro|AUTOSCROLL_DX
define|#
directive|define
name|AUTOSCROLL_DX
value|0.1
end_define

begin_typedef
typedef|typedef
struct|struct
DECL|struct|__anon2c11953e0108
block|{
DECL|member|mevent
name|GdkEventMotion
modifier|*
name|mevent
decl_stmt|;
DECL|member|device
name|GimpDeviceInfo
modifier|*
name|device
decl_stmt|;
DECL|member|time
name|guint32
name|time
decl_stmt|;
DECL|member|state
name|GdkModifierType
name|state
decl_stmt|;
DECL|member|timeout_id
name|guint
name|timeout_id
decl_stmt|;
DECL|typedef|ScrollInfo
block|}
name|ScrollInfo
typedef|;
end_typedef

begin_comment
comment|/*  local function prototypes  */
end_comment

begin_function_decl
specifier|static
name|gboolean
name|gimp_display_shell_autoscroll_timeout
parameter_list|(
name|gpointer
name|data
parameter_list|)
function_decl|;
end_function_decl

begin_comment
comment|/*  public functions  */
end_comment

begin_function
name|void
DECL|function|gimp_display_shell_autoscroll_start (GimpDisplayShell * shell,GdkModifierType state,GdkEventMotion * mevent)
name|gimp_display_shell_autoscroll_start
parameter_list|(
name|GimpDisplayShell
modifier|*
name|shell
parameter_list|,
name|GdkModifierType
name|state
parameter_list|,
name|GdkEventMotion
modifier|*
name|mevent
parameter_list|)
block|{
name|ScrollInfo
modifier|*
name|info
decl_stmt|;
name|g_return_if_fail
argument_list|(
name|GIMP_IS_DISPLAY_SHELL
argument_list|(
name|shell
argument_list|)
argument_list|)
expr_stmt|;
if|if
condition|(
name|shell
operator|->
name|scroll_info
condition|)
return|return;
name|info
operator|=
name|g_slice_new0
argument_list|(
name|ScrollInfo
argument_list|)
expr_stmt|;
name|info
operator|->
name|mevent
operator|=
name|mevent
expr_stmt|;
name|info
operator|->
name|device
operator|=
name|gimp_device_info_get_by_device
argument_list|(
name|mevent
operator|->
name|device
argument_list|)
expr_stmt|;
name|info
operator|->
name|time
operator|=
name|gdk_event_get_time
argument_list|(
operator|(
name|GdkEvent
operator|*
operator|)
name|mevent
argument_list|)
expr_stmt|;
name|info
operator|->
name|state
operator|=
name|state
expr_stmt|;
name|info
operator|->
name|timeout_id
operator|=
name|g_timeout_add
argument_list|(
name|AUTOSCROLL_DT
argument_list|,
name|gimp_display_shell_autoscroll_timeout
argument_list|,
name|shell
argument_list|)
expr_stmt|;
name|shell
operator|->
name|scroll_info
operator|=
name|info
expr_stmt|;
block|}
end_function

begin_function
name|void
DECL|function|gimp_display_shell_autoscroll_stop (GimpDisplayShell * shell)
name|gimp_display_shell_autoscroll_stop
parameter_list|(
name|GimpDisplayShell
modifier|*
name|shell
parameter_list|)
block|{
name|ScrollInfo
modifier|*
name|info
decl_stmt|;
name|g_return_if_fail
argument_list|(
name|GIMP_IS_DISPLAY_SHELL
argument_list|(
name|shell
argument_list|)
argument_list|)
expr_stmt|;
if|if
condition|(
operator|!
name|shell
operator|->
name|scroll_info
condition|)
return|return;
name|info
operator|=
name|shell
operator|->
name|scroll_info
expr_stmt|;
if|if
condition|(
name|info
operator|->
name|timeout_id
condition|)
block|{
name|g_source_remove
argument_list|(
name|info
operator|->
name|timeout_id
argument_list|)
expr_stmt|;
name|info
operator|->
name|timeout_id
operator|=
literal|0
expr_stmt|;
block|}
name|g_slice_free
argument_list|(
name|ScrollInfo
argument_list|,
name|info
argument_list|)
expr_stmt|;
name|shell
operator|->
name|scroll_info
operator|=
name|NULL
expr_stmt|;
block|}
end_function

begin_comment
comment|/*  private functions  */
end_comment

begin_function
specifier|static
name|gboolean
DECL|function|gimp_display_shell_autoscroll_timeout (gpointer data)
name|gimp_display_shell_autoscroll_timeout
parameter_list|(
name|gpointer
name|data
parameter_list|)
block|{
name|GimpDisplayShell
modifier|*
name|shell
init|=
name|GIMP_DISPLAY_SHELL
argument_list|(
name|data
argument_list|)
decl_stmt|;
name|ScrollInfo
modifier|*
name|info
init|=
name|shell
operator|->
name|scroll_info
decl_stmt|;
name|GimpCoords
name|device_coords
decl_stmt|;
name|GimpCoords
name|image_coords
decl_stmt|;
name|gint
name|dx
init|=
literal|0
decl_stmt|;
name|gint
name|dy
init|=
literal|0
decl_stmt|;
name|gimp_device_info_get_device_coords
argument_list|(
name|info
operator|->
name|device
argument_list|,
name|gtk_widget_get_window
argument_list|(
name|shell
operator|->
name|canvas
argument_list|)
argument_list|,
operator|&
name|device_coords
argument_list|)
expr_stmt|;
if|if
condition|(
name|device_coords
operator|.
name|x
operator|<
literal|0
condition|)
name|dx
operator|=
name|device_coords
operator|.
name|x
expr_stmt|;
elseif|else
if|if
condition|(
name|device_coords
operator|.
name|x
operator|>
name|shell
operator|->
name|disp_width
condition|)
name|dx
operator|=
name|device_coords
operator|.
name|x
operator|-
name|shell
operator|->
name|disp_width
expr_stmt|;
if|if
condition|(
name|device_coords
operator|.
name|y
operator|<
literal|0
condition|)
name|dy
operator|=
name|device_coords
operator|.
name|y
expr_stmt|;
elseif|else
if|if
condition|(
name|device_coords
operator|.
name|y
operator|>
name|shell
operator|->
name|disp_height
condition|)
name|dy
operator|=
name|device_coords
operator|.
name|y
operator|-
name|shell
operator|->
name|disp_height
expr_stmt|;
if|if
condition|(
name|dx
operator|||
name|dy
condition|)
block|{
name|GimpDisplay
modifier|*
name|display
init|=
name|shell
operator|->
name|display
decl_stmt|;
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
name|gint
name|scroll_amount_x
init|=
name|AUTOSCROLL_DX
operator|*
name|dx
decl_stmt|;
name|gint
name|scroll_amount_y
init|=
name|AUTOSCROLL_DX
operator|*
name|dy
decl_stmt|;
name|info
operator|->
name|time
operator|+=
name|AUTOSCROLL_DT
expr_stmt|;
name|gimp_display_shell_scroll_unoverscrollify
argument_list|(
name|shell
argument_list|,
name|scroll_amount_x
argument_list|,
name|scroll_amount_y
argument_list|,
operator|&
name|scroll_amount_x
argument_list|,
operator|&
name|scroll_amount_y
argument_list|)
expr_stmt|;
name|gimp_display_shell_scroll
argument_list|(
name|shell
argument_list|,
name|scroll_amount_x
argument_list|,
name|scroll_amount_y
argument_list|)
expr_stmt|;
name|gimp_display_shell_untransform_coords
argument_list|(
name|shell
argument_list|,
operator|&
name|device_coords
argument_list|,
operator|&
name|image_coords
argument_list|)
expr_stmt|;
if|if
condition|(
name|gimp_tool_control_get_snap_to
argument_list|(
name|active_tool
operator|->
name|control
argument_list|)
condition|)
block|{
name|gint
name|x
decl_stmt|,
name|y
decl_stmt|,
name|width
decl_stmt|,
name|height
decl_stmt|;
name|gimp_tool_control_get_snap_offsets
argument_list|(
name|active_tool
operator|->
name|control
argument_list|,
operator|&
name|x
argument_list|,
operator|&
name|y
argument_list|,
operator|&
name|width
argument_list|,
operator|&
name|height
argument_list|)
expr_stmt|;
name|gimp_display_shell_snap_coords
argument_list|(
name|shell
argument_list|,
operator|&
name|image_coords
argument_list|,
name|x
argument_list|,
name|y
argument_list|,
name|width
argument_list|,
name|height
argument_list|)
expr_stmt|;
block|}
name|tool_manager_motion_active
argument_list|(
name|display
operator|->
name|gimp
argument_list|,
operator|&
name|image_coords
argument_list|,
name|info
operator|->
name|time
argument_list|,
name|info
operator|->
name|state
argument_list|,
name|display
argument_list|)
expr_stmt|;
return|return
name|TRUE
return|;
block|}
else|else
block|{
name|g_slice_free
argument_list|(
name|ScrollInfo
argument_list|,
name|info
argument_list|)
expr_stmt|;
name|shell
operator|->
name|scroll_info
operator|=
name|NULL
expr_stmt|;
return|return
name|FALSE
return|;
block|}
block|}
end_function

end_unit

