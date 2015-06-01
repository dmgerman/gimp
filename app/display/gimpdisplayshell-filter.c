begin_unit|revision:0.9.5;language:C;cregit-version:0.0.1
begin_comment
comment|/* GIMP - The GNU Image Manipulation Program  * Copyright (C) 1999 Manish Singh  *  * This program is free software: you can redistribute it and/or modify  * it under the terms of the GNU General Public License as published by  * the Free Software Foundation; either version 3 of the License, or  * (at your option) any later version.  *  * This program is distributed in the hope that it will be useful,  * but WITHOUT ANY WARRANTY; without even the implied warranty of  * MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the  * GNU General Public License for more details.  *  * You should have received a copy of the GNU General Public License  * along with this program.  If not, see<http://www.gnu.org/licenses/>.  */
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
file|"libgimpconfig/gimpconfig.h"
end_include

begin_include
include|#
directive|include
file|"libgimpwidgets/gimpwidgets.h"
end_include

begin_include
include|#
directive|include
file|"display-types.h"
end_include

begin_include
include|#
directive|include
file|"config/gimpcoreconfig.h"
end_include

begin_include
include|#
directive|include
file|"gimpdisplayshell.h"
end_include

begin_include
include|#
directive|include
file|"gimpdisplayshell-expose.h"
end_include

begin_include
include|#
directive|include
file|"gimpdisplayshell-filter.h"
end_include

begin_include
include|#
directive|include
file|"gimpdisplayshell-profile.h"
end_include

begin_comment
comment|/*  local function prototypes  */
end_comment

begin_function_decl
specifier|static
name|void
name|gimp_display_shell_filter_changed
parameter_list|(
name|GimpColorDisplayStack
modifier|*
name|stack
parameter_list|,
name|GimpDisplayShell
modifier|*
name|shell
parameter_list|)
function_decl|;
end_function_decl

begin_comment
comment|/*  public functions  */
end_comment

begin_function
name|void
DECL|function|gimp_display_shell_filter_set (GimpDisplayShell * shell,GimpColorDisplayStack * stack)
name|gimp_display_shell_filter_set
parameter_list|(
name|GimpDisplayShell
modifier|*
name|shell
parameter_list|,
name|GimpColorDisplayStack
modifier|*
name|stack
parameter_list|)
block|{
name|g_return_if_fail
argument_list|(
name|GIMP_IS_DISPLAY_SHELL
argument_list|(
name|shell
argument_list|)
argument_list|)
expr_stmt|;
name|g_return_if_fail
argument_list|(
name|stack
operator|==
name|NULL
operator|||
name|GIMP_IS_COLOR_DISPLAY_STACK
argument_list|(
name|stack
argument_list|)
argument_list|)
expr_stmt|;
if|if
condition|(
name|stack
operator|==
name|shell
operator|->
name|filter_stack
condition|)
return|return;
if|if
condition|(
name|shell
operator|->
name|filter_stack
condition|)
block|{
name|g_signal_handlers_disconnect_by_func
argument_list|(
name|shell
operator|->
name|filter_stack
argument_list|,
name|gimp_display_shell_filter_changed
argument_list|,
name|shell
argument_list|)
expr_stmt|;
name|g_object_unref
argument_list|(
name|shell
operator|->
name|filter_stack
argument_list|)
expr_stmt|;
block|}
name|shell
operator|->
name|filter_stack
operator|=
name|stack
expr_stmt|;
if|if
condition|(
name|shell
operator|->
name|filter_stack
condition|)
block|{
name|g_object_ref
argument_list|(
name|shell
operator|->
name|filter_stack
argument_list|)
expr_stmt|;
name|g_signal_connect
argument_list|(
name|shell
operator|->
name|filter_stack
argument_list|,
literal|"changed"
argument_list|,
name|G_CALLBACK
argument_list|(
name|gimp_display_shell_filter_changed
argument_list|)
argument_list|,
name|shell
argument_list|)
expr_stmt|;
block|}
name|gimp_display_shell_filter_changed
argument_list|(
name|NULL
argument_list|,
name|shell
argument_list|)
expr_stmt|;
block|}
end_function

begin_function
name|gboolean
DECL|function|gimp_display_shell_has_filter (GimpDisplayShell * shell)
name|gimp_display_shell_has_filter
parameter_list|(
name|GimpDisplayShell
modifier|*
name|shell
parameter_list|)
block|{
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
return|return
name|shell
operator|->
name|filter_stack
operator|&&
name|shell
operator|->
name|filter_stack
operator|->
name|filters
return|;
block|}
end_function

begin_function
name|GimpColorDisplayStack
modifier|*
DECL|function|gimp_display_shell_filter_new (GimpDisplayShell * shell,GimpColorConfig * config)
name|gimp_display_shell_filter_new
parameter_list|(
name|GimpDisplayShell
modifier|*
name|shell
parameter_list|,
name|GimpColorConfig
modifier|*
name|config
parameter_list|)
block|{
name|g_return_val_if_fail
argument_list|(
name|GIMP_IS_DISPLAY_SHELL
argument_list|(
name|shell
argument_list|)
argument_list|,
name|NULL
argument_list|)
expr_stmt|;
name|g_return_val_if_fail
argument_list|(
name|GIMP_IS_COLOR_CONFIG
argument_list|(
name|config
argument_list|)
argument_list|,
name|NULL
argument_list|)
expr_stmt|;
if|if
condition|(
name|config
operator|->
name|display_module
condition|)
block|{
name|GType
name|type
init|=
name|g_type_from_name
argument_list|(
name|config
operator|->
name|display_module
argument_list|)
decl_stmt|;
if|if
condition|(
name|g_type_is_a
argument_list|(
name|type
argument_list|,
name|GIMP_TYPE_COLOR_DISPLAY
argument_list|)
condition|)
block|{
name|GimpColorDisplay
modifier|*
name|display
decl_stmt|;
name|GimpColorDisplayStack
modifier|*
name|stack
decl_stmt|;
name|display
operator|=
name|g_object_new
argument_list|(
name|type
argument_list|,
literal|"color-config"
argument_list|,
name|config
argument_list|,
literal|"color-managed"
argument_list|,
name|shell
argument_list|,
name|NULL
argument_list|)
expr_stmt|;
name|stack
operator|=
name|gimp_color_display_stack_new
argument_list|()
expr_stmt|;
name|gimp_color_display_stack_add
argument_list|(
name|stack
argument_list|,
name|display
argument_list|)
expr_stmt|;
name|g_object_unref
argument_list|(
name|display
argument_list|)
expr_stmt|;
return|return
name|stack
return|;
block|}
block|}
return|return
name|NULL
return|;
block|}
end_function

begin_comment
comment|/*  private functions  */
end_comment

begin_function
specifier|static
name|gboolean
DECL|function|gimp_display_shell_filter_changed_idle (gpointer data)
name|gimp_display_shell_filter_changed_idle
parameter_list|(
name|gpointer
name|data
parameter_list|)
block|{
name|GimpDisplayShell
modifier|*
name|shell
init|=
name|data
decl_stmt|;
name|gimp_display_shell_profile_update
argument_list|(
name|shell
argument_list|)
expr_stmt|;
name|gimp_display_shell_expose_full
argument_list|(
name|shell
argument_list|)
expr_stmt|;
name|shell
operator|->
name|filter_idle_id
operator|=
literal|0
expr_stmt|;
return|return
name|FALSE
return|;
block|}
end_function

begin_function
specifier|static
name|void
DECL|function|gimp_display_shell_filter_changed (GimpColorDisplayStack * stack,GimpDisplayShell * shell)
name|gimp_display_shell_filter_changed
parameter_list|(
name|GimpColorDisplayStack
modifier|*
name|stack
parameter_list|,
name|GimpDisplayShell
modifier|*
name|shell
parameter_list|)
block|{
if|if
condition|(
name|shell
operator|->
name|filter_idle_id
condition|)
name|g_source_remove
argument_list|(
name|shell
operator|->
name|filter_idle_id
argument_list|)
expr_stmt|;
name|shell
operator|->
name|filter_idle_id
operator|=
name|g_idle_add_full
argument_list|(
name|G_PRIORITY_LOW
argument_list|,
name|gimp_display_shell_filter_changed_idle
argument_list|,
name|shell
argument_list|,
name|NULL
argument_list|)
expr_stmt|;
block|}
end_function

end_unit

