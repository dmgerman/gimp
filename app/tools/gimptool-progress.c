begin_unit|revision:0.9.5;language:C;cregit-version:0.0.1
begin_comment
comment|/* GIMP - The GNU Image Manipulation Program  * Copyright (C) 1995 Spencer Kimball and Peter Mattis  *  * gimptool-progress.c  * Copyright (C) 2011 Michael Natterer<mitch@gimp.org>  *  * This program is free software: you can redistribute it and/or modify  * it under the terms of the GNU General Public License as published by  * the Free Software Foundation; either version 3 of the License, or  * (at your option) any later version.  *  * This program is distributed in the hope that it will be useful,  * but WITHOUT ANY WARRANTY; without even the implied warranty of  * MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the  * GNU General Public License for more details.  *  * You should have received a copy of the GNU General Public License  * along with this program.  If not, see<http://www.gnu.org/licenses/>.  */
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
file|<gdk/gdkkeysyms.h>
end_include

begin_include
include|#
directive|include
file|"tools-types.h"
end_include

begin_include
include|#
directive|include
file|"core/gimpprogress.h"
end_include

begin_include
include|#
directive|include
file|"widgets/gimpwidgets-utils.h"
end_include

begin_include
include|#
directive|include
file|"display/gimpcanvasprogress.h"
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
file|"display/gimpdisplayshell-items.h"
end_include

begin_include
include|#
directive|include
file|"display/gimpdisplayshell-transform.h"
end_include

begin_include
include|#
directive|include
file|"gimptool.h"
end_include

begin_include
include|#
directive|include
file|"gimptool-progress.h"
end_include

begin_comment
comment|/*  local function prototypes  */
end_comment

begin_function_decl
specifier|static
name|GimpProgress
modifier|*
name|gimp_tool_progress_start
parameter_list|(
name|GimpProgress
modifier|*
name|progress
parameter_list|,
specifier|const
name|gchar
modifier|*
name|message
parameter_list|,
name|gboolean
name|cancelable
parameter_list|)
function_decl|;
end_function_decl

begin_function_decl
specifier|static
name|void
name|gimp_tool_progress_end
parameter_list|(
name|GimpProgress
modifier|*
name|progress
parameter_list|)
function_decl|;
end_function_decl

begin_function_decl
specifier|static
name|gboolean
name|gimp_tool_progress_is_active
parameter_list|(
name|GimpProgress
modifier|*
name|progress
parameter_list|)
function_decl|;
end_function_decl

begin_function_decl
specifier|static
name|void
name|gimp_tool_progress_set_text
parameter_list|(
name|GimpProgress
modifier|*
name|progress
parameter_list|,
specifier|const
name|gchar
modifier|*
name|message
parameter_list|)
function_decl|;
end_function_decl

begin_function_decl
specifier|static
name|void
name|gimp_tool_progress_set_value
parameter_list|(
name|GimpProgress
modifier|*
name|progress
parameter_list|,
name|gdouble
name|percentage
parameter_list|)
function_decl|;
end_function_decl

begin_function_decl
specifier|static
name|gdouble
name|gimp_tool_progress_get_value
parameter_list|(
name|GimpProgress
modifier|*
name|progress
parameter_list|)
function_decl|;
end_function_decl

begin_function_decl
specifier|static
name|void
name|gimp_tool_progress_pulse
parameter_list|(
name|GimpProgress
modifier|*
name|progress
parameter_list|)
function_decl|;
end_function_decl

begin_function_decl
specifier|static
name|gboolean
name|gimp_tool_progress_message
parameter_list|(
name|GimpProgress
modifier|*
name|progress
parameter_list|,
name|Gimp
modifier|*
name|gimp
parameter_list|,
name|GimpMessageSeverity
name|severity
parameter_list|,
specifier|const
name|gchar
modifier|*
name|domain
parameter_list|,
specifier|const
name|gchar
modifier|*
name|message
parameter_list|)
function_decl|;
end_function_decl

begin_comment
comment|/*  public functions  */
end_comment

begin_function
name|void
DECL|function|gimp_tool_progress_iface_init (GimpProgressInterface * iface)
name|gimp_tool_progress_iface_init
parameter_list|(
name|GimpProgressInterface
modifier|*
name|iface
parameter_list|)
block|{
name|iface
operator|->
name|start
operator|=
name|gimp_tool_progress_start
expr_stmt|;
name|iface
operator|->
name|end
operator|=
name|gimp_tool_progress_end
expr_stmt|;
name|iface
operator|->
name|is_active
operator|=
name|gimp_tool_progress_is_active
expr_stmt|;
name|iface
operator|->
name|set_text
operator|=
name|gimp_tool_progress_set_text
expr_stmt|;
name|iface
operator|->
name|set_value
operator|=
name|gimp_tool_progress_set_value
expr_stmt|;
name|iface
operator|->
name|get_value
operator|=
name|gimp_tool_progress_get_value
expr_stmt|;
name|iface
operator|->
name|pulse
operator|=
name|gimp_tool_progress_pulse
expr_stmt|;
name|iface
operator|->
name|message
operator|=
name|gimp_tool_progress_message
expr_stmt|;
block|}
end_function

begin_comment
comment|/*  private functions  */
end_comment

begin_function
specifier|static
name|gboolean
DECL|function|gimp_tool_progress_key_event (GtkWidget * widget,const GdkEventKey * kevent,GimpTool * tool)
name|gimp_tool_progress_key_event
parameter_list|(
name|GtkWidget
modifier|*
name|widget
parameter_list|,
specifier|const
name|GdkEventKey
modifier|*
name|kevent
parameter_list|,
name|GimpTool
modifier|*
name|tool
parameter_list|)
block|{
if|if
condition|(
name|kevent
operator|->
name|keyval
operator|==
name|GDK_KEY_Escape
condition|)
block|{
name|gimp_progress_cancel
argument_list|(
name|GIMP_PROGRESS
argument_list|(
name|tool
argument_list|)
argument_list|)
expr_stmt|;
block|}
return|return
name|TRUE
return|;
block|}
end_function

begin_function
specifier|static
name|GimpProgress
modifier|*
DECL|function|gimp_tool_progress_start (GimpProgress * progress,const gchar * message,gboolean cancelable)
name|gimp_tool_progress_start
parameter_list|(
name|GimpProgress
modifier|*
name|progress
parameter_list|,
specifier|const
name|gchar
modifier|*
name|message
parameter_list|,
name|gboolean
name|cancelable
parameter_list|)
block|{
name|GimpTool
modifier|*
name|tool
init|=
name|GIMP_TOOL
argument_list|(
name|progress
argument_list|)
decl_stmt|;
name|GimpDisplayShell
modifier|*
name|shell
decl_stmt|;
name|gint
name|x
decl_stmt|,
name|y
decl_stmt|;
name|g_return_val_if_fail
argument_list|(
name|GIMP_IS_DISPLAY
argument_list|(
name|tool
operator|->
name|display
argument_list|)
argument_list|,
name|NULL
argument_list|)
expr_stmt|;
name|g_return_val_if_fail
argument_list|(
name|tool
operator|->
name|progress
operator|==
name|NULL
argument_list|,
name|NULL
argument_list|)
expr_stmt|;
name|shell
operator|=
name|gimp_display_get_shell
argument_list|(
name|tool
operator|->
name|display
argument_list|)
expr_stmt|;
name|x
operator|=
name|shell
operator|->
name|disp_width
operator|/
literal|2
expr_stmt|;
name|y
operator|=
name|shell
operator|->
name|disp_height
operator|/
literal|2
expr_stmt|;
name|gimp_display_shell_unzoom_xy
argument_list|(
name|shell
argument_list|,
name|x
argument_list|,
name|y
argument_list|,
operator|&
name|x
argument_list|,
operator|&
name|y
argument_list|,
name|FALSE
argument_list|)
expr_stmt|;
name|tool
operator|->
name|progress
operator|=
name|gimp_canvas_progress_new
argument_list|(
name|shell
argument_list|,
name|GIMP_HANDLE_ANCHOR_CENTER
argument_list|,
name|x
argument_list|,
name|y
argument_list|)
expr_stmt|;
name|gimp_display_shell_add_unrotated_item
argument_list|(
name|shell
argument_list|,
name|tool
operator|->
name|progress
argument_list|)
expr_stmt|;
name|g_object_unref
argument_list|(
name|tool
operator|->
name|progress
argument_list|)
expr_stmt|;
name|gimp_progress_start
argument_list|(
name|GIMP_PROGRESS
argument_list|(
name|tool
operator|->
name|progress
argument_list|)
argument_list|,
name|message
argument_list|,
name|FALSE
argument_list|)
expr_stmt|;
name|gimp_widget_flush_expose
argument_list|(
name|shell
operator|->
name|canvas
argument_list|)
expr_stmt|;
name|tool
operator|->
name|progress_display
operator|=
name|tool
operator|->
name|display
expr_stmt|;
if|if
condition|(
name|cancelable
condition|)
block|{
name|tool
operator|->
name|progress_grab_widget
operator|=
name|gtk_invisible_new
argument_list|()
expr_stmt|;
name|gtk_widget_show
argument_list|(
name|tool
operator|->
name|progress_grab_widget
argument_list|)
expr_stmt|;
name|gtk_grab_add
argument_list|(
name|tool
operator|->
name|progress_grab_widget
argument_list|)
expr_stmt|;
name|g_signal_connect
argument_list|(
name|tool
operator|->
name|progress_grab_widget
argument_list|,
literal|"key-press-event"
argument_list|,
name|G_CALLBACK
argument_list|(
name|gimp_tool_progress_key_event
argument_list|)
argument_list|,
name|tool
argument_list|)
expr_stmt|;
block|}
return|return
name|progress
return|;
block|}
end_function

begin_function
specifier|static
name|void
DECL|function|gimp_tool_progress_end (GimpProgress * progress)
name|gimp_tool_progress_end
parameter_list|(
name|GimpProgress
modifier|*
name|progress
parameter_list|)
block|{
name|GimpTool
modifier|*
name|tool
init|=
name|GIMP_TOOL
argument_list|(
name|progress
argument_list|)
decl_stmt|;
if|if
condition|(
name|tool
operator|->
name|progress
condition|)
block|{
name|GimpDisplayShell
modifier|*
name|shell
init|=
name|gimp_display_get_shell
argument_list|(
name|tool
operator|->
name|progress_display
argument_list|)
decl_stmt|;
name|gimp_progress_end
argument_list|(
name|GIMP_PROGRESS
argument_list|(
name|tool
operator|->
name|progress
argument_list|)
argument_list|)
expr_stmt|;
name|gimp_display_shell_remove_unrotated_item
argument_list|(
name|shell
argument_list|,
name|tool
operator|->
name|progress
argument_list|)
expr_stmt|;
name|tool
operator|->
name|progress
operator|=
name|NULL
expr_stmt|;
name|tool
operator|->
name|progress_display
operator|=
name|NULL
expr_stmt|;
if|if
condition|(
name|tool
operator|->
name|progress_grab_widget
condition|)
block|{
name|gtk_grab_remove
argument_list|(
name|tool
operator|->
name|progress_grab_widget
argument_list|)
expr_stmt|;
name|gtk_widget_destroy
argument_list|(
name|tool
operator|->
name|progress_grab_widget
argument_list|)
expr_stmt|;
name|tool
operator|->
name|progress_grab_widget
operator|=
name|NULL
expr_stmt|;
block|}
block|}
block|}
end_function

begin_function
specifier|static
name|gboolean
DECL|function|gimp_tool_progress_is_active (GimpProgress * progress)
name|gimp_tool_progress_is_active
parameter_list|(
name|GimpProgress
modifier|*
name|progress
parameter_list|)
block|{
name|GimpTool
modifier|*
name|tool
init|=
name|GIMP_TOOL
argument_list|(
name|progress
argument_list|)
decl_stmt|;
return|return
name|tool
operator|->
name|progress
operator|!=
name|NULL
return|;
block|}
end_function

begin_function
specifier|static
name|void
DECL|function|gimp_tool_progress_set_text (GimpProgress * progress,const gchar * message)
name|gimp_tool_progress_set_text
parameter_list|(
name|GimpProgress
modifier|*
name|progress
parameter_list|,
specifier|const
name|gchar
modifier|*
name|message
parameter_list|)
block|{
name|GimpTool
modifier|*
name|tool
init|=
name|GIMP_TOOL
argument_list|(
name|progress
argument_list|)
decl_stmt|;
if|if
condition|(
name|tool
operator|->
name|progress
condition|)
block|{
name|GimpDisplayShell
modifier|*
name|shell
init|=
name|gimp_display_get_shell
argument_list|(
name|tool
operator|->
name|progress_display
argument_list|)
decl_stmt|;
name|gimp_progress_set_text
argument_list|(
name|GIMP_PROGRESS
argument_list|(
name|tool
operator|->
name|progress
argument_list|)
argument_list|,
name|message
argument_list|)
expr_stmt|;
name|gimp_widget_flush_expose
argument_list|(
name|shell
operator|->
name|canvas
argument_list|)
expr_stmt|;
block|}
block|}
end_function

begin_function
specifier|static
name|void
DECL|function|gimp_tool_progress_set_value (GimpProgress * progress,gdouble percentage)
name|gimp_tool_progress_set_value
parameter_list|(
name|GimpProgress
modifier|*
name|progress
parameter_list|,
name|gdouble
name|percentage
parameter_list|)
block|{
name|GimpTool
modifier|*
name|tool
init|=
name|GIMP_TOOL
argument_list|(
name|progress
argument_list|)
decl_stmt|;
if|if
condition|(
name|tool
operator|->
name|progress
condition|)
block|{
name|GimpDisplayShell
modifier|*
name|shell
init|=
name|gimp_display_get_shell
argument_list|(
name|tool
operator|->
name|progress_display
argument_list|)
decl_stmt|;
name|gimp_progress_set_value
argument_list|(
name|GIMP_PROGRESS
argument_list|(
name|tool
operator|->
name|progress
argument_list|)
argument_list|,
name|percentage
argument_list|)
expr_stmt|;
name|gimp_widget_flush_expose
argument_list|(
name|shell
operator|->
name|canvas
argument_list|)
expr_stmt|;
block|}
block|}
end_function

begin_function
specifier|static
name|gdouble
DECL|function|gimp_tool_progress_get_value (GimpProgress * progress)
name|gimp_tool_progress_get_value
parameter_list|(
name|GimpProgress
modifier|*
name|progress
parameter_list|)
block|{
name|GimpTool
modifier|*
name|tool
init|=
name|GIMP_TOOL
argument_list|(
name|progress
argument_list|)
decl_stmt|;
if|if
condition|(
name|tool
operator|->
name|progress
condition|)
return|return
name|gimp_progress_get_value
argument_list|(
name|GIMP_PROGRESS
argument_list|(
name|tool
operator|->
name|progress
argument_list|)
argument_list|)
return|;
return|return
literal|0.0
return|;
block|}
end_function

begin_function
specifier|static
name|void
DECL|function|gimp_tool_progress_pulse (GimpProgress * progress)
name|gimp_tool_progress_pulse
parameter_list|(
name|GimpProgress
modifier|*
name|progress
parameter_list|)
block|{ }
end_function

begin_function
specifier|static
name|gboolean
DECL|function|gimp_tool_progress_message (GimpProgress * progress,Gimp * gimp,GimpMessageSeverity severity,const gchar * domain,const gchar * message)
name|gimp_tool_progress_message
parameter_list|(
name|GimpProgress
modifier|*
name|progress
parameter_list|,
name|Gimp
modifier|*
name|gimp
parameter_list|,
name|GimpMessageSeverity
name|severity
parameter_list|,
specifier|const
name|gchar
modifier|*
name|domain
parameter_list|,
specifier|const
name|gchar
modifier|*
name|message
parameter_list|)
block|{
return|return
name|FALSE
return|;
block|}
end_function

end_unit

