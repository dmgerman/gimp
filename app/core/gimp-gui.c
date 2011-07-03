begin_unit|revision:0.9.5;language:C;cregit-version:0.0.1
begin_comment
comment|/* GIMP - The GNU Image Manipulation Program  * Copyright (C) 1995-2002 Spencer Kimball, Peter Mattis, and others  *  * This program is free software: you can redistribute it and/or modify  * it under the terms of the GNU General Public License as published by  * the Free Software Foundation; either version 3 of the License, or  * (at your option) any later version.  *  * This program is distributed in the hope that it will be useful,  * but WITHOUT ANY WARRANTY; without even the implied warranty of  * MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the  * GNU General Public License for more details.  *  * You should have received a copy of the GNU General Public License  * along with this program.  If not, see<http://www.gnu.org/licenses/>.  */
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
file|"libgimpbase/gimpbase.h"
end_include

begin_include
include|#
directive|include
file|"core-types.h"
end_include

begin_include
include|#
directive|include
file|"gimp.h"
end_include

begin_include
include|#
directive|include
file|"gimp-gui.h"
end_include

begin_include
include|#
directive|include
file|"gimpcontainer.h"
end_include

begin_include
include|#
directive|include
file|"gimpcontext.h"
end_include

begin_include
include|#
directive|include
file|"gimpimage.h"
end_include

begin_include
include|#
directive|include
file|"gimpprogress.h"
end_include

begin_include
include|#
directive|include
file|"about.h"
end_include

begin_include
include|#
directive|include
file|"gimp-intl.h"
end_include

begin_function
name|void
DECL|function|gimp_gui_init (Gimp * gimp)
name|gimp_gui_init
parameter_list|(
name|Gimp
modifier|*
name|gimp
parameter_list|)
block|{
name|g_return_if_fail
argument_list|(
name|GIMP_IS_GIMP
argument_list|(
name|gimp
argument_list|)
argument_list|)
expr_stmt|;
name|gimp
operator|->
name|gui
operator|.
name|ungrab
operator|=
name|NULL
expr_stmt|;
name|gimp
operator|->
name|gui
operator|.
name|threads_enter
operator|=
name|NULL
expr_stmt|;
name|gimp
operator|->
name|gui
operator|.
name|threads_leave
operator|=
name|NULL
expr_stmt|;
name|gimp
operator|->
name|gui
operator|.
name|set_busy
operator|=
name|NULL
expr_stmt|;
name|gimp
operator|->
name|gui
operator|.
name|unset_busy
operator|=
name|NULL
expr_stmt|;
name|gimp
operator|->
name|gui
operator|.
name|show_message
operator|=
name|NULL
expr_stmt|;
name|gimp
operator|->
name|gui
operator|.
name|help
operator|=
name|NULL
expr_stmt|;
name|gimp
operator|->
name|gui
operator|.
name|get_program_class
operator|=
name|NULL
expr_stmt|;
name|gimp
operator|->
name|gui
operator|.
name|get_display_name
operator|=
name|NULL
expr_stmt|;
name|gimp
operator|->
name|gui
operator|.
name|get_user_time
operator|=
name|NULL
expr_stmt|;
name|gimp
operator|->
name|gui
operator|.
name|get_theme_dir
operator|=
name|NULL
expr_stmt|;
name|gimp
operator|->
name|gui
operator|.
name|display_get_by_id
operator|=
name|NULL
expr_stmt|;
name|gimp
operator|->
name|gui
operator|.
name|display_get_id
operator|=
name|NULL
expr_stmt|;
name|gimp
operator|->
name|gui
operator|.
name|display_get_window_id
operator|=
name|NULL
expr_stmt|;
name|gimp
operator|->
name|gui
operator|.
name|display_create
operator|=
name|NULL
expr_stmt|;
name|gimp
operator|->
name|gui
operator|.
name|display_delete
operator|=
name|NULL
expr_stmt|;
name|gimp
operator|->
name|gui
operator|.
name|displays_reconnect
operator|=
name|NULL
expr_stmt|;
name|gimp
operator|->
name|gui
operator|.
name|progress_new
operator|=
name|NULL
expr_stmt|;
name|gimp
operator|->
name|gui
operator|.
name|progress_free
operator|=
name|NULL
expr_stmt|;
name|gimp
operator|->
name|gui
operator|.
name|pdb_dialog_set
operator|=
name|NULL
expr_stmt|;
name|gimp
operator|->
name|gui
operator|.
name|pdb_dialog_close
operator|=
name|NULL
expr_stmt|;
name|gimp
operator|->
name|gui
operator|.
name|recent_list_add_uri
operator|=
name|NULL
expr_stmt|;
name|gimp
operator|->
name|gui
operator|.
name|recent_list_load
operator|=
name|NULL
expr_stmt|;
block|}
end_function

begin_function
name|void
DECL|function|gimp_gui_ungrab (Gimp * gimp)
name|gimp_gui_ungrab
parameter_list|(
name|Gimp
modifier|*
name|gimp
parameter_list|)
block|{
name|g_return_if_fail
argument_list|(
name|GIMP_IS_GIMP
argument_list|(
name|gimp
argument_list|)
argument_list|)
expr_stmt|;
if|if
condition|(
name|gimp
operator|->
name|gui
operator|.
name|ungrab
condition|)
name|gimp
operator|->
name|gui
operator|.
name|ungrab
argument_list|(
name|gimp
argument_list|)
expr_stmt|;
block|}
end_function

begin_function
name|void
DECL|function|gimp_threads_enter (Gimp * gimp)
name|gimp_threads_enter
parameter_list|(
name|Gimp
modifier|*
name|gimp
parameter_list|)
block|{
name|g_return_if_fail
argument_list|(
name|GIMP_IS_GIMP
argument_list|(
name|gimp
argument_list|)
argument_list|)
expr_stmt|;
if|if
condition|(
name|gimp
operator|->
name|gui
operator|.
name|threads_enter
condition|)
name|gimp
operator|->
name|gui
operator|.
name|threads_enter
argument_list|(
name|gimp
argument_list|)
expr_stmt|;
block|}
end_function

begin_function
name|void
DECL|function|gimp_threads_leave (Gimp * gimp)
name|gimp_threads_leave
parameter_list|(
name|Gimp
modifier|*
name|gimp
parameter_list|)
block|{
name|g_return_if_fail
argument_list|(
name|GIMP_IS_GIMP
argument_list|(
name|gimp
argument_list|)
argument_list|)
expr_stmt|;
if|if
condition|(
name|gimp
operator|->
name|gui
operator|.
name|threads_leave
condition|)
name|gimp
operator|->
name|gui
operator|.
name|threads_leave
argument_list|(
name|gimp
argument_list|)
expr_stmt|;
block|}
end_function

begin_function
name|void
DECL|function|gimp_set_busy (Gimp * gimp)
name|gimp_set_busy
parameter_list|(
name|Gimp
modifier|*
name|gimp
parameter_list|)
block|{
name|g_return_if_fail
argument_list|(
name|GIMP_IS_GIMP
argument_list|(
name|gimp
argument_list|)
argument_list|)
expr_stmt|;
comment|/* FIXME: gimp_busy HACK */
name|gimp
operator|->
name|busy
operator|++
expr_stmt|;
if|if
condition|(
name|gimp
operator|->
name|busy
operator|==
literal|1
condition|)
block|{
if|if
condition|(
name|gimp
operator|->
name|gui
operator|.
name|set_busy
condition|)
name|gimp
operator|->
name|gui
operator|.
name|set_busy
argument_list|(
name|gimp
argument_list|)
expr_stmt|;
block|}
block|}
end_function

begin_function
specifier|static
name|gboolean
DECL|function|gimp_idle_unset_busy (gpointer data)
name|gimp_idle_unset_busy
parameter_list|(
name|gpointer
name|data
parameter_list|)
block|{
name|Gimp
modifier|*
name|gimp
init|=
name|data
decl_stmt|;
name|gimp_unset_busy
argument_list|(
name|gimp
argument_list|)
expr_stmt|;
name|gimp
operator|->
name|busy_idle_id
operator|=
literal|0
expr_stmt|;
return|return
name|FALSE
return|;
block|}
end_function

begin_function
name|void
DECL|function|gimp_set_busy_until_idle (Gimp * gimp)
name|gimp_set_busy_until_idle
parameter_list|(
name|Gimp
modifier|*
name|gimp
parameter_list|)
block|{
name|g_return_if_fail
argument_list|(
name|GIMP_IS_GIMP
argument_list|(
name|gimp
argument_list|)
argument_list|)
expr_stmt|;
if|if
condition|(
operator|!
name|gimp
operator|->
name|busy_idle_id
condition|)
block|{
name|gimp_set_busy
argument_list|(
name|gimp
argument_list|)
expr_stmt|;
name|gimp
operator|->
name|busy_idle_id
operator|=
name|g_idle_add_full
argument_list|(
name|G_PRIORITY_HIGH
argument_list|,
name|gimp_idle_unset_busy
argument_list|,
name|gimp
argument_list|,
name|NULL
argument_list|)
expr_stmt|;
block|}
block|}
end_function

begin_function
name|void
DECL|function|gimp_unset_busy (Gimp * gimp)
name|gimp_unset_busy
parameter_list|(
name|Gimp
modifier|*
name|gimp
parameter_list|)
block|{
name|g_return_if_fail
argument_list|(
name|GIMP_IS_GIMP
argument_list|(
name|gimp
argument_list|)
argument_list|)
expr_stmt|;
name|g_return_if_fail
argument_list|(
name|gimp
operator|->
name|busy
operator|>
literal|0
argument_list|)
expr_stmt|;
comment|/* FIXME: gimp_busy HACK */
name|gimp
operator|->
name|busy
operator|--
expr_stmt|;
if|if
condition|(
name|gimp
operator|->
name|busy
operator|==
literal|0
condition|)
block|{
if|if
condition|(
name|gimp
operator|->
name|gui
operator|.
name|unset_busy
condition|)
name|gimp
operator|->
name|gui
operator|.
name|unset_busy
argument_list|(
name|gimp
argument_list|)
expr_stmt|;
block|}
block|}
end_function

begin_function
name|void
DECL|function|gimp_show_message (Gimp * gimp,GObject * handler,GimpMessageSeverity severity,const gchar * domain,const gchar * message)
name|gimp_show_message
parameter_list|(
name|Gimp
modifier|*
name|gimp
parameter_list|,
name|GObject
modifier|*
name|handler
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
specifier|const
name|gchar
modifier|*
name|desc
init|=
literal|"Message"
decl_stmt|;
name|g_return_if_fail
argument_list|(
name|GIMP_IS_GIMP
argument_list|(
name|gimp
argument_list|)
argument_list|)
expr_stmt|;
name|g_return_if_fail
argument_list|(
name|handler
operator|==
name|NULL
operator|||
name|G_IS_OBJECT
argument_list|(
name|handler
argument_list|)
argument_list|)
expr_stmt|;
name|g_return_if_fail
argument_list|(
name|message
operator|!=
name|NULL
argument_list|)
expr_stmt|;
if|if
condition|(
operator|!
name|domain
condition|)
name|domain
operator|=
name|GIMP_ACRONYM
expr_stmt|;
if|if
condition|(
operator|!
name|gimp
operator|->
name|console_messages
condition|)
block|{
if|if
condition|(
name|gimp
operator|->
name|gui
operator|.
name|show_message
condition|)
block|{
name|gimp
operator|->
name|gui
operator|.
name|show_message
argument_list|(
name|gimp
argument_list|,
name|handler
argument_list|,
name|severity
argument_list|,
name|domain
argument_list|,
name|message
argument_list|)
expr_stmt|;
return|return;
block|}
elseif|else
if|if
condition|(
name|GIMP_IS_PROGRESS
argument_list|(
name|handler
argument_list|)
operator|&&
name|gimp_progress_message
argument_list|(
name|GIMP_PROGRESS
argument_list|(
name|handler
argument_list|)
argument_list|,
name|gimp
argument_list|,
name|severity
argument_list|,
name|domain
argument_list|,
name|message
argument_list|)
condition|)
block|{
comment|/* message has been handled by GimpProgress */
return|return;
block|}
block|}
name|gimp_enum_get_value
argument_list|(
name|GIMP_TYPE_MESSAGE_SEVERITY
argument_list|,
name|severity
argument_list|,
name|NULL
argument_list|,
name|NULL
argument_list|,
operator|&
name|desc
argument_list|,
name|NULL
argument_list|)
expr_stmt|;
name|g_printerr
argument_list|(
literal|"%s-%s: %s\n\n"
argument_list|,
name|domain
argument_list|,
name|desc
argument_list|,
name|message
argument_list|)
expr_stmt|;
block|}
end_function

begin_function
name|void
DECL|function|gimp_help (Gimp * gimp,GimpProgress * progress,const gchar * help_domain,const gchar * help_id)
name|gimp_help
parameter_list|(
name|Gimp
modifier|*
name|gimp
parameter_list|,
name|GimpProgress
modifier|*
name|progress
parameter_list|,
specifier|const
name|gchar
modifier|*
name|help_domain
parameter_list|,
specifier|const
name|gchar
modifier|*
name|help_id
parameter_list|)
block|{
name|g_return_if_fail
argument_list|(
name|GIMP_IS_GIMP
argument_list|(
name|gimp
argument_list|)
argument_list|)
expr_stmt|;
name|g_return_if_fail
argument_list|(
name|progress
operator|==
name|NULL
operator|||
name|GIMP_IS_PROGRESS
argument_list|(
name|progress
argument_list|)
argument_list|)
expr_stmt|;
if|if
condition|(
name|gimp
operator|->
name|gui
operator|.
name|help
condition|)
name|gimp
operator|->
name|gui
operator|.
name|help
argument_list|(
name|gimp
argument_list|,
name|progress
argument_list|,
name|help_domain
argument_list|,
name|help_id
argument_list|)
expr_stmt|;
block|}
end_function

begin_function
specifier|const
name|gchar
modifier|*
DECL|function|gimp_get_program_class (Gimp * gimp)
name|gimp_get_program_class
parameter_list|(
name|Gimp
modifier|*
name|gimp
parameter_list|)
block|{
name|g_return_val_if_fail
argument_list|(
name|GIMP_IS_GIMP
argument_list|(
name|gimp
argument_list|)
argument_list|,
name|NULL
argument_list|)
expr_stmt|;
if|if
condition|(
name|gimp
operator|->
name|gui
operator|.
name|get_program_class
condition|)
return|return
name|gimp
operator|->
name|gui
operator|.
name|get_program_class
argument_list|(
name|gimp
argument_list|)
return|;
return|return
name|NULL
return|;
block|}
end_function

begin_function
name|gchar
modifier|*
DECL|function|gimp_get_display_name (Gimp * gimp,gint display_ID,gint * monitor_number)
name|gimp_get_display_name
parameter_list|(
name|Gimp
modifier|*
name|gimp
parameter_list|,
name|gint
name|display_ID
parameter_list|,
name|gint
modifier|*
name|monitor_number
parameter_list|)
block|{
name|g_return_val_if_fail
argument_list|(
name|GIMP_IS_GIMP
argument_list|(
name|gimp
argument_list|)
argument_list|,
name|NULL
argument_list|)
expr_stmt|;
name|g_return_val_if_fail
argument_list|(
name|monitor_number
operator|!=
name|NULL
argument_list|,
name|NULL
argument_list|)
expr_stmt|;
if|if
condition|(
name|gimp
operator|->
name|gui
operator|.
name|get_display_name
condition|)
return|return
name|gimp
operator|->
name|gui
operator|.
name|get_display_name
argument_list|(
name|gimp
argument_list|,
name|display_ID
argument_list|,
name|monitor_number
argument_list|)
return|;
operator|*
name|monitor_number
operator|=
literal|0
expr_stmt|;
return|return
name|NULL
return|;
block|}
end_function

begin_comment
comment|/**  * gimp_get_user_time:  * @gimp:  *  * Returns the timestamp of the last user interaction. The timestamp is  * taken from events caused by user interaction such as key presses or  * pointer movements. See gdk_x11_display_get_user_time().  *  * Return value: the timestamp of the last user interaction  */
end_comment

begin_function
name|guint32
DECL|function|gimp_get_user_time (Gimp * gimp)
name|gimp_get_user_time
parameter_list|(
name|Gimp
modifier|*
name|gimp
parameter_list|)
block|{
name|g_return_val_if_fail
argument_list|(
name|GIMP_IS_GIMP
argument_list|(
name|gimp
argument_list|)
argument_list|,
literal|0
argument_list|)
expr_stmt|;
if|if
condition|(
name|gimp
operator|->
name|gui
operator|.
name|get_user_time
condition|)
return|return
name|gimp
operator|->
name|gui
operator|.
name|get_user_time
argument_list|(
name|gimp
argument_list|)
return|;
return|return
literal|0
return|;
block|}
end_function

begin_function
specifier|const
name|gchar
modifier|*
DECL|function|gimp_get_theme_dir (Gimp * gimp)
name|gimp_get_theme_dir
parameter_list|(
name|Gimp
modifier|*
name|gimp
parameter_list|)
block|{
name|g_return_val_if_fail
argument_list|(
name|GIMP_IS_GIMP
argument_list|(
name|gimp
argument_list|)
argument_list|,
name|NULL
argument_list|)
expr_stmt|;
if|if
condition|(
name|gimp
operator|->
name|gui
operator|.
name|get_theme_dir
condition|)
return|return
name|gimp
operator|->
name|gui
operator|.
name|get_theme_dir
argument_list|(
name|gimp
argument_list|)
return|;
return|return
name|NULL
return|;
block|}
end_function

begin_function
name|GimpObject
modifier|*
DECL|function|gimp_get_window_strategy (Gimp * gimp)
name|gimp_get_window_strategy
parameter_list|(
name|Gimp
modifier|*
name|gimp
parameter_list|)
block|{
name|g_return_val_if_fail
argument_list|(
name|GIMP_IS_GIMP
argument_list|(
name|gimp
argument_list|)
argument_list|,
name|NULL
argument_list|)
expr_stmt|;
if|if
condition|(
name|gimp
operator|->
name|gui
operator|.
name|get_window_strategy
condition|)
return|return
name|gimp
operator|->
name|gui
operator|.
name|get_window_strategy
argument_list|(
name|gimp
argument_list|)
return|;
return|return
name|NULL
return|;
block|}
end_function

begin_function
name|GimpObject
modifier|*
DECL|function|gimp_get_empty_display (Gimp * gimp)
name|gimp_get_empty_display
parameter_list|(
name|Gimp
modifier|*
name|gimp
parameter_list|)
block|{
name|g_return_val_if_fail
argument_list|(
name|GIMP_IS_GIMP
argument_list|(
name|gimp
argument_list|)
argument_list|,
name|NULL
argument_list|)
expr_stmt|;
if|if
condition|(
name|gimp
operator|->
name|gui
operator|.
name|get_empty_display
condition|)
return|return
name|gimp
operator|->
name|gui
operator|.
name|get_empty_display
argument_list|(
name|gimp
argument_list|)
return|;
return|return
name|NULL
return|;
block|}
end_function

begin_function
name|GimpObject
modifier|*
DECL|function|gimp_get_display_by_ID (Gimp * gimp,gint ID)
name|gimp_get_display_by_ID
parameter_list|(
name|Gimp
modifier|*
name|gimp
parameter_list|,
name|gint
name|ID
parameter_list|)
block|{
name|g_return_val_if_fail
argument_list|(
name|GIMP_IS_GIMP
argument_list|(
name|gimp
argument_list|)
argument_list|,
name|NULL
argument_list|)
expr_stmt|;
if|if
condition|(
name|gimp
operator|->
name|gui
operator|.
name|display_get_by_id
condition|)
return|return
name|gimp
operator|->
name|gui
operator|.
name|display_get_by_id
argument_list|(
name|gimp
argument_list|,
name|ID
argument_list|)
return|;
return|return
name|NULL
return|;
block|}
end_function

begin_function
name|gint
DECL|function|gimp_get_display_ID (Gimp * gimp,GimpObject * display)
name|gimp_get_display_ID
parameter_list|(
name|Gimp
modifier|*
name|gimp
parameter_list|,
name|GimpObject
modifier|*
name|display
parameter_list|)
block|{
name|g_return_val_if_fail
argument_list|(
name|GIMP_IS_GIMP
argument_list|(
name|gimp
argument_list|)
argument_list|,
operator|-
literal|1
argument_list|)
expr_stmt|;
name|g_return_val_if_fail
argument_list|(
name|GIMP_IS_OBJECT
argument_list|(
name|display
argument_list|)
argument_list|,
operator|-
literal|1
argument_list|)
expr_stmt|;
if|if
condition|(
name|gimp
operator|->
name|gui
operator|.
name|display_get_id
condition|)
return|return
name|gimp
operator|->
name|gui
operator|.
name|display_get_id
argument_list|(
name|display
argument_list|)
return|;
return|return
operator|-
literal|1
return|;
block|}
end_function

begin_function
name|guint32
DECL|function|gimp_get_display_window_id (Gimp * gimp,GimpObject * display)
name|gimp_get_display_window_id
parameter_list|(
name|Gimp
modifier|*
name|gimp
parameter_list|,
name|GimpObject
modifier|*
name|display
parameter_list|)
block|{
name|g_return_val_if_fail
argument_list|(
name|GIMP_IS_GIMP
argument_list|(
name|gimp
argument_list|)
argument_list|,
operator|-
literal|1
argument_list|)
expr_stmt|;
name|g_return_val_if_fail
argument_list|(
name|GIMP_IS_OBJECT
argument_list|(
name|display
argument_list|)
argument_list|,
operator|-
literal|1
argument_list|)
expr_stmt|;
if|if
condition|(
name|gimp
operator|->
name|gui
operator|.
name|display_get_window_id
condition|)
return|return
name|gimp
operator|->
name|gui
operator|.
name|display_get_window_id
argument_list|(
name|display
argument_list|)
return|;
return|return
operator|-
literal|1
return|;
block|}
end_function

begin_function
name|GimpObject
modifier|*
DECL|function|gimp_create_display (Gimp * gimp,GimpImage * image,GimpUnit unit,gdouble scale)
name|gimp_create_display
parameter_list|(
name|Gimp
modifier|*
name|gimp
parameter_list|,
name|GimpImage
modifier|*
name|image
parameter_list|,
name|GimpUnit
name|unit
parameter_list|,
name|gdouble
name|scale
parameter_list|)
block|{
name|g_return_val_if_fail
argument_list|(
name|GIMP_IS_GIMP
argument_list|(
name|gimp
argument_list|)
argument_list|,
name|NULL
argument_list|)
expr_stmt|;
name|g_return_val_if_fail
argument_list|(
name|image
operator|==
name|NULL
operator|||
name|GIMP_IS_IMAGE
argument_list|(
name|image
argument_list|)
argument_list|,
name|NULL
argument_list|)
expr_stmt|;
if|if
condition|(
name|gimp
operator|->
name|gui
operator|.
name|display_create
condition|)
return|return
name|gimp
operator|->
name|gui
operator|.
name|display_create
argument_list|(
name|gimp
argument_list|,
name|image
argument_list|,
name|unit
argument_list|,
name|scale
argument_list|)
return|;
return|return
name|NULL
return|;
block|}
end_function

begin_function
name|void
DECL|function|gimp_delete_display (Gimp * gimp,GimpObject * display)
name|gimp_delete_display
parameter_list|(
name|Gimp
modifier|*
name|gimp
parameter_list|,
name|GimpObject
modifier|*
name|display
parameter_list|)
block|{
name|g_return_if_fail
argument_list|(
name|GIMP_IS_GIMP
argument_list|(
name|gimp
argument_list|)
argument_list|)
expr_stmt|;
name|g_return_if_fail
argument_list|(
name|GIMP_IS_OBJECT
argument_list|(
name|display
argument_list|)
argument_list|)
expr_stmt|;
if|if
condition|(
name|gimp
operator|->
name|gui
operator|.
name|display_delete
condition|)
name|gimp
operator|->
name|gui
operator|.
name|display_delete
argument_list|(
name|display
argument_list|)
expr_stmt|;
block|}
end_function

begin_function
name|void
DECL|function|gimp_reconnect_displays (Gimp * gimp,GimpImage * old_image,GimpImage * new_image)
name|gimp_reconnect_displays
parameter_list|(
name|Gimp
modifier|*
name|gimp
parameter_list|,
name|GimpImage
modifier|*
name|old_image
parameter_list|,
name|GimpImage
modifier|*
name|new_image
parameter_list|)
block|{
name|g_return_if_fail
argument_list|(
name|GIMP_IS_GIMP
argument_list|(
name|gimp
argument_list|)
argument_list|)
expr_stmt|;
name|g_return_if_fail
argument_list|(
name|GIMP_IS_IMAGE
argument_list|(
name|old_image
argument_list|)
argument_list|)
expr_stmt|;
name|g_return_if_fail
argument_list|(
name|GIMP_IS_IMAGE
argument_list|(
name|new_image
argument_list|)
argument_list|)
expr_stmt|;
if|if
condition|(
name|gimp
operator|->
name|gui
operator|.
name|displays_reconnect
condition|)
name|gimp
operator|->
name|gui
operator|.
name|displays_reconnect
argument_list|(
name|gimp
argument_list|,
name|old_image
argument_list|,
name|new_image
argument_list|)
expr_stmt|;
block|}
end_function

begin_function
name|GimpProgress
modifier|*
DECL|function|gimp_new_progress (Gimp * gimp,GimpObject * display)
name|gimp_new_progress
parameter_list|(
name|Gimp
modifier|*
name|gimp
parameter_list|,
name|GimpObject
modifier|*
name|display
parameter_list|)
block|{
name|g_return_val_if_fail
argument_list|(
name|GIMP_IS_GIMP
argument_list|(
name|gimp
argument_list|)
argument_list|,
name|NULL
argument_list|)
expr_stmt|;
name|g_return_val_if_fail
argument_list|(
name|display
operator|==
name|NULL
operator|||
name|GIMP_IS_OBJECT
argument_list|(
name|display
argument_list|)
argument_list|,
name|NULL
argument_list|)
expr_stmt|;
if|if
condition|(
name|gimp
operator|->
name|gui
operator|.
name|progress_new
condition|)
return|return
name|gimp
operator|->
name|gui
operator|.
name|progress_new
argument_list|(
name|gimp
argument_list|,
name|display
argument_list|)
return|;
return|return
name|NULL
return|;
block|}
end_function

begin_function
name|void
DECL|function|gimp_free_progress (Gimp * gimp,GimpProgress * progress)
name|gimp_free_progress
parameter_list|(
name|Gimp
modifier|*
name|gimp
parameter_list|,
name|GimpProgress
modifier|*
name|progress
parameter_list|)
block|{
name|g_return_if_fail
argument_list|(
name|GIMP_IS_GIMP
argument_list|(
name|gimp
argument_list|)
argument_list|)
expr_stmt|;
name|g_return_if_fail
argument_list|(
name|GIMP_IS_PROGRESS
argument_list|(
name|progress
argument_list|)
argument_list|)
expr_stmt|;
if|if
condition|(
name|gimp
operator|->
name|gui
operator|.
name|progress_free
condition|)
name|gimp
operator|->
name|gui
operator|.
name|progress_free
argument_list|(
name|gimp
argument_list|,
name|progress
argument_list|)
expr_stmt|;
block|}
end_function

begin_function
name|gboolean
DECL|function|gimp_pdb_dialog_new (Gimp * gimp,GimpContext * context,GimpProgress * progress,GimpContainer * container,const gchar * title,const gchar * callback_name,const gchar * object_name,...)
name|gimp_pdb_dialog_new
parameter_list|(
name|Gimp
modifier|*
name|gimp
parameter_list|,
name|GimpContext
modifier|*
name|context
parameter_list|,
name|GimpProgress
modifier|*
name|progress
parameter_list|,
name|GimpContainer
modifier|*
name|container
parameter_list|,
specifier|const
name|gchar
modifier|*
name|title
parameter_list|,
specifier|const
name|gchar
modifier|*
name|callback_name
parameter_list|,
specifier|const
name|gchar
modifier|*
name|object_name
parameter_list|,
modifier|...
parameter_list|)
block|{
name|gboolean
name|retval
init|=
name|FALSE
decl_stmt|;
name|g_return_val_if_fail
argument_list|(
name|GIMP_IS_GIMP
argument_list|(
name|gimp
argument_list|)
argument_list|,
name|FALSE
argument_list|)
expr_stmt|;
name|g_return_val_if_fail
argument_list|(
name|GIMP_IS_CONTEXT
argument_list|(
name|context
argument_list|)
argument_list|,
name|FALSE
argument_list|)
expr_stmt|;
name|g_return_val_if_fail
argument_list|(
name|progress
operator|==
name|NULL
operator|||
name|GIMP_IS_PROGRESS
argument_list|(
name|progress
argument_list|)
argument_list|,
name|FALSE
argument_list|)
expr_stmt|;
name|g_return_val_if_fail
argument_list|(
name|GIMP_IS_CONTAINER
argument_list|(
name|container
argument_list|)
argument_list|,
name|FALSE
argument_list|)
expr_stmt|;
name|g_return_val_if_fail
argument_list|(
name|title
operator|!=
name|NULL
argument_list|,
name|FALSE
argument_list|)
expr_stmt|;
name|g_return_val_if_fail
argument_list|(
name|callback_name
operator|!=
name|NULL
argument_list|,
name|FALSE
argument_list|)
expr_stmt|;
if|if
condition|(
name|gimp
operator|->
name|gui
operator|.
name|pdb_dialog_new
condition|)
block|{
name|va_list
name|args
decl_stmt|;
name|va_start
argument_list|(
name|args
argument_list|,
name|object_name
argument_list|)
expr_stmt|;
name|retval
operator|=
name|gimp
operator|->
name|gui
operator|.
name|pdb_dialog_new
argument_list|(
name|gimp
argument_list|,
name|context
argument_list|,
name|progress
argument_list|,
name|container
argument_list|,
name|title
argument_list|,
name|callback_name
argument_list|,
name|object_name
argument_list|,
name|args
argument_list|)
expr_stmt|;
name|va_end
argument_list|(
name|args
argument_list|)
expr_stmt|;
block|}
return|return
name|retval
return|;
block|}
end_function

begin_function
name|gboolean
DECL|function|gimp_pdb_dialog_set (Gimp * gimp,GimpContainer * container,const gchar * callback_name,const gchar * object_name,...)
name|gimp_pdb_dialog_set
parameter_list|(
name|Gimp
modifier|*
name|gimp
parameter_list|,
name|GimpContainer
modifier|*
name|container
parameter_list|,
specifier|const
name|gchar
modifier|*
name|callback_name
parameter_list|,
specifier|const
name|gchar
modifier|*
name|object_name
parameter_list|,
modifier|...
parameter_list|)
block|{
name|gboolean
name|retval
init|=
name|FALSE
decl_stmt|;
name|g_return_val_if_fail
argument_list|(
name|GIMP_IS_GIMP
argument_list|(
name|gimp
argument_list|)
argument_list|,
name|FALSE
argument_list|)
expr_stmt|;
name|g_return_val_if_fail
argument_list|(
name|GIMP_IS_CONTAINER
argument_list|(
name|container
argument_list|)
argument_list|,
name|FALSE
argument_list|)
expr_stmt|;
name|g_return_val_if_fail
argument_list|(
name|callback_name
operator|!=
name|NULL
argument_list|,
name|FALSE
argument_list|)
expr_stmt|;
name|g_return_val_if_fail
argument_list|(
name|object_name
operator|!=
name|NULL
argument_list|,
name|FALSE
argument_list|)
expr_stmt|;
if|if
condition|(
name|gimp
operator|->
name|gui
operator|.
name|pdb_dialog_set
condition|)
block|{
name|va_list
name|args
decl_stmt|;
name|va_start
argument_list|(
name|args
argument_list|,
name|object_name
argument_list|)
expr_stmt|;
name|retval
operator|=
name|gimp
operator|->
name|gui
operator|.
name|pdb_dialog_set
argument_list|(
name|gimp
argument_list|,
name|container
argument_list|,
name|callback_name
argument_list|,
name|object_name
argument_list|,
name|args
argument_list|)
expr_stmt|;
name|va_end
argument_list|(
name|args
argument_list|)
expr_stmt|;
block|}
return|return
name|retval
return|;
block|}
end_function

begin_function
name|gboolean
DECL|function|gimp_pdb_dialog_close (Gimp * gimp,GimpContainer * container,const gchar * callback_name)
name|gimp_pdb_dialog_close
parameter_list|(
name|Gimp
modifier|*
name|gimp
parameter_list|,
name|GimpContainer
modifier|*
name|container
parameter_list|,
specifier|const
name|gchar
modifier|*
name|callback_name
parameter_list|)
block|{
name|g_return_val_if_fail
argument_list|(
name|GIMP_IS_GIMP
argument_list|(
name|gimp
argument_list|)
argument_list|,
name|FALSE
argument_list|)
expr_stmt|;
name|g_return_val_if_fail
argument_list|(
name|GIMP_IS_CONTAINER
argument_list|(
name|container
argument_list|)
argument_list|,
name|FALSE
argument_list|)
expr_stmt|;
name|g_return_val_if_fail
argument_list|(
name|callback_name
operator|!=
name|NULL
argument_list|,
name|FALSE
argument_list|)
expr_stmt|;
if|if
condition|(
name|gimp
operator|->
name|gui
operator|.
name|pdb_dialog_close
condition|)
return|return
name|gimp
operator|->
name|gui
operator|.
name|pdb_dialog_close
argument_list|(
name|gimp
argument_list|,
name|container
argument_list|,
name|callback_name
argument_list|)
return|;
return|return
name|FALSE
return|;
block|}
end_function

begin_function
name|gboolean
DECL|function|gimp_recent_list_add_uri (Gimp * gimp,const gchar * uri,const gchar * mime_type)
name|gimp_recent_list_add_uri
parameter_list|(
name|Gimp
modifier|*
name|gimp
parameter_list|,
specifier|const
name|gchar
modifier|*
name|uri
parameter_list|,
specifier|const
name|gchar
modifier|*
name|mime_type
parameter_list|)
block|{
name|g_return_val_if_fail
argument_list|(
name|GIMP_IS_GIMP
argument_list|(
name|gimp
argument_list|)
argument_list|,
name|FALSE
argument_list|)
expr_stmt|;
name|g_return_val_if_fail
argument_list|(
name|uri
operator|!=
name|NULL
argument_list|,
name|FALSE
argument_list|)
expr_stmt|;
if|if
condition|(
name|gimp
operator|->
name|gui
operator|.
name|recent_list_add_uri
condition|)
return|return
name|gimp
operator|->
name|gui
operator|.
name|recent_list_add_uri
argument_list|(
name|gimp
argument_list|,
name|uri
argument_list|,
name|mime_type
argument_list|)
return|;
return|return
name|FALSE
return|;
block|}
end_function

begin_function
name|void
DECL|function|gimp_recent_list_load (Gimp * gimp)
name|gimp_recent_list_load
parameter_list|(
name|Gimp
modifier|*
name|gimp
parameter_list|)
block|{
name|g_return_if_fail
argument_list|(
name|GIMP_IS_GIMP
argument_list|(
name|gimp
argument_list|)
argument_list|)
expr_stmt|;
if|if
condition|(
name|gimp
operator|->
name|gui
operator|.
name|recent_list_load
condition|)
name|gimp
operator|->
name|gui
operator|.
name|recent_list_load
argument_list|(
name|gimp
argument_list|)
expr_stmt|;
block|}
end_function

end_unit

