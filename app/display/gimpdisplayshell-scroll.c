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
file|"display-types.h"
end_include

begin_include
include|#
directive|include
file|"core/gimpimage.h"
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
file|"gimpdisplay.h"
end_include

begin_include
include|#
directive|include
file|"gimpdisplay-foreach.h"
end_include

begin_include
include|#
directive|include
file|"gimpdisplayshell.h"
end_include

begin_include
include|#
directive|include
file|"gimpdisplayshell-scale.h"
end_include

begin_include
include|#
directive|include
file|"gimpdisplayshell-scroll.h"
end_include

begin_function
name|gboolean
DECL|function|gimp_display_shell_scroll (GimpDisplayShell * shell,gint x_offset,gint y_offset)
name|gimp_display_shell_scroll
parameter_list|(
name|GimpDisplayShell
modifier|*
name|shell
parameter_list|,
name|gint
name|x_offset
parameter_list|,
name|gint
name|y_offset
parameter_list|)
block|{
name|gint
name|old_x
decl_stmt|;
name|gint
name|old_y
decl_stmt|;
name|g_return_val_if_fail
argument_list|(
name|GIMP_IS_DISPLAY_SHELL
argument_list|(
name|shell
argument_list|)
argument_list|,
name|FALSE
argument_list|)
expr_stmt|;
name|old_x
operator|=
name|shell
operator|->
name|offset_x
expr_stmt|;
name|old_y
operator|=
name|shell
operator|->
name|offset_y
expr_stmt|;
name|shell
operator|->
name|offset_x
operator|+=
name|x_offset
expr_stmt|;
name|shell
operator|->
name|offset_y
operator|+=
name|y_offset
expr_stmt|;
name|gimp_display_shell_scroll_clamp_offsets
argument_list|(
name|shell
argument_list|)
expr_stmt|;
comment|/*  the actual changes in offset  */
name|x_offset
operator|=
operator|(
name|shell
operator|->
name|offset_x
operator|-
name|old_x
operator|)
expr_stmt|;
name|y_offset
operator|=
operator|(
name|shell
operator|->
name|offset_y
operator|-
name|old_y
operator|)
expr_stmt|;
if|if
condition|(
name|x_offset
operator|||
name|y_offset
condition|)
block|{
comment|/* The call to gimp_display_shell_scale_setup() shouldn't be needed          here if all other places are correct.           gimp_display_shell_scale_setup (shell);       */
comment|/*  reset the old values so that the tool can accurately redraw  */
name|shell
operator|->
name|offset_x
operator|=
name|old_x
expr_stmt|;
name|shell
operator|->
name|offset_y
operator|=
name|old_y
expr_stmt|;
name|tool_manager_control_active
argument_list|(
name|shell
operator|->
name|gdisp
operator|->
name|gimage
operator|->
name|gimp
argument_list|,
name|PAUSE
argument_list|,
name|shell
operator|->
name|gdisp
argument_list|)
expr_stmt|;
name|gdk_window_scroll
argument_list|(
name|shell
operator|->
name|canvas
operator|->
name|window
argument_list|,
operator|-
name|x_offset
argument_list|,
operator|-
name|y_offset
argument_list|)
expr_stmt|;
comment|/*  set the offsets back to the new values  */
name|shell
operator|->
name|offset_x
operator|+=
name|x_offset
expr_stmt|;
name|shell
operator|->
name|offset_y
operator|+=
name|y_offset
expr_stmt|;
name|tool_manager_control_active
argument_list|(
name|shell
operator|->
name|gdisp
operator|->
name|gimage
operator|->
name|gimp
argument_list|,
name|RESUME
argument_list|,
name|shell
operator|->
name|gdisp
argument_list|)
expr_stmt|;
comment|/*  Make sure expose events are processed before scrolling again  */
name|gdk_window_process_updates
argument_list|(
name|shell
operator|->
name|canvas
operator|->
name|window
argument_list|,
name|FALSE
argument_list|)
expr_stmt|;
name|gimp_display_shell_scrolled
argument_list|(
name|shell
argument_list|)
expr_stmt|;
return|return
name|TRUE
return|;
block|}
return|return
name|FALSE
return|;
block|}
end_function

begin_function
name|void
DECL|function|gimp_display_shell_scroll_clamp_offsets (GimpDisplayShell * shell)
name|gimp_display_shell_scroll_clamp_offsets
parameter_list|(
name|GimpDisplayShell
modifier|*
name|shell
parameter_list|)
block|{
name|gint
name|sx
decl_stmt|,
name|sy
decl_stmt|;
name|g_return_if_fail
argument_list|(
name|GIMP_IS_DISPLAY_SHELL
argument_list|(
name|shell
argument_list|)
argument_list|)
expr_stmt|;
name|sx
operator|=
name|SCALEX
argument_list|(
name|shell
argument_list|,
name|shell
operator|->
name|gdisp
operator|->
name|gimage
operator|->
name|width
argument_list|)
expr_stmt|;
name|sy
operator|=
name|SCALEY
argument_list|(
name|shell
argument_list|,
name|shell
operator|->
name|gdisp
operator|->
name|gimage
operator|->
name|height
argument_list|)
expr_stmt|;
name|shell
operator|->
name|offset_x
operator|=
name|CLAMP
argument_list|(
name|shell
operator|->
name|offset_x
argument_list|,
literal|0
argument_list|,
name|MAX
argument_list|(
name|sx
operator|-
name|shell
operator|->
name|disp_width
argument_list|,
literal|0
argument_list|)
argument_list|)
expr_stmt|;
name|shell
operator|->
name|offset_y
operator|=
name|CLAMP
argument_list|(
name|shell
operator|->
name|offset_y
argument_list|,
literal|0
argument_list|,
name|MAX
argument_list|(
name|sy
operator|-
name|shell
operator|->
name|disp_height
argument_list|,
literal|0
argument_list|)
argument_list|)
expr_stmt|;
block|}
end_function

end_unit

