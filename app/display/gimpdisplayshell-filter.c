begin_unit|revision:0.9.5;language:C;cregit-version:0.0.1
begin_comment
comment|/* The GIMP -- an image manipulation program  * Copyright (C) 1999 Manish Singh  *  * This program is free software; you can redistribute it and/or modify  * it under the terms of the GNU General Public License as published by  * the Free Software Foundation; either version 2 of the License, or  * (at your option) any later version.  *  * This program is distributed in the hope that it will be useful,  * but WITHOUT ANY WARRANTY; without even the implied warranty of  * MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the  * GNU General Public License for more details.  *  * You should have received a copy of the GNU General Public License  * along with this program; if not, write to the Free Software  * Foundation, Inc., 59 Temple Place - Suite 330, Boston, MA 02111-1307, USA.  */
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
file|<gmodule.h>
end_include

begin_include
include|#
directive|include
file|<gtk/gtk.h>
end_include

begin_include
include|#
directive|include
file|"libgimpbase/gimpbase.h"
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
file|"core/gimpimage.h"
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
file|"gimpdisplayshell-filter.h"
end_include

begin_function
name|GimpColorDisplay
modifier|*
DECL|function|gimp_display_shell_filter_attach (GimpDisplayShell * shell,GType type)
name|gimp_display_shell_filter_attach
parameter_list|(
name|GimpDisplayShell
modifier|*
name|shell
parameter_list|,
name|GType
name|type
parameter_list|)
block|{
name|GimpColorDisplay
modifier|*
name|filter
decl_stmt|;
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
name|g_type_is_a
argument_list|(
name|type
argument_list|,
name|GIMP_TYPE_COLOR_DISPLAY
argument_list|)
argument_list|,
name|NULL
argument_list|)
expr_stmt|;
name|filter
operator|=
name|gimp_color_display_new
argument_list|(
name|type
argument_list|)
expr_stmt|;
if|if
condition|(
name|filter
condition|)
block|{
name|shell
operator|->
name|filters
operator|=
name|g_list_append
argument_list|(
name|shell
operator|->
name|filters
argument_list|,
name|filter
argument_list|)
expr_stmt|;
return|return
name|filter
return|;
block|}
else|else
name|g_warning
argument_list|(
literal|"Tried to attach a nonexistant color display"
argument_list|)
expr_stmt|;
return|return
name|NULL
return|;
block|}
end_function

begin_function
name|GimpColorDisplay
modifier|*
DECL|function|gimp_display_shell_filter_attach_clone (GimpDisplayShell * shell,GimpColorDisplay * filter)
name|gimp_display_shell_filter_attach_clone
parameter_list|(
name|GimpDisplayShell
modifier|*
name|shell
parameter_list|,
name|GimpColorDisplay
modifier|*
name|filter
parameter_list|)
block|{
name|GimpColorDisplay
modifier|*
name|clone
decl_stmt|;
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
name|GIMP_IS_COLOR_DISPLAY
argument_list|(
name|filter
argument_list|)
argument_list|,
name|NULL
argument_list|)
expr_stmt|;
name|clone
operator|=
name|gimp_color_display_clone
argument_list|(
name|filter
argument_list|)
expr_stmt|;
if|if
condition|(
name|clone
condition|)
block|{
name|shell
operator|->
name|filters
operator|=
name|g_list_append
argument_list|(
name|shell
operator|->
name|filters
argument_list|,
name|clone
argument_list|)
expr_stmt|;
return|return
name|clone
return|;
block|}
else|else
name|g_warning
argument_list|(
literal|"Tried to clone a nonexistant color display"
argument_list|)
expr_stmt|;
return|return
name|NULL
return|;
block|}
end_function

begin_function
name|void
DECL|function|gimp_display_shell_filter_detach (GimpDisplayShell * shell,GimpColorDisplay * filter)
name|gimp_display_shell_filter_detach
parameter_list|(
name|GimpDisplayShell
modifier|*
name|shell
parameter_list|,
name|GimpColorDisplay
modifier|*
name|filter
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
name|GIMP_IS_COLOR_DISPLAY
argument_list|(
name|filter
argument_list|)
argument_list|)
expr_stmt|;
name|shell
operator|->
name|filters
operator|=
name|g_list_remove
argument_list|(
name|shell
operator|->
name|filters
argument_list|,
name|filter
argument_list|)
expr_stmt|;
block|}
end_function

begin_function
name|void
DECL|function|gimp_display_shell_filter_detach_destroy (GimpDisplayShell * shell,GimpColorDisplay * filter)
name|gimp_display_shell_filter_detach_destroy
parameter_list|(
name|GimpDisplayShell
modifier|*
name|shell
parameter_list|,
name|GimpColorDisplay
modifier|*
name|filter
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
name|GIMP_IS_COLOR_DISPLAY
argument_list|(
name|filter
argument_list|)
argument_list|)
expr_stmt|;
name|g_object_unref
argument_list|(
name|filter
argument_list|)
expr_stmt|;
name|shell
operator|->
name|filters
operator|=
name|g_list_remove
argument_list|(
name|shell
operator|->
name|filters
argument_list|,
name|filter
argument_list|)
expr_stmt|;
block|}
end_function

begin_function
name|void
DECL|function|gimp_display_shell_filter_detach_all (GimpDisplayShell * shell)
name|gimp_display_shell_filter_detach_all
parameter_list|(
name|GimpDisplayShell
modifier|*
name|shell
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
name|g_list_foreach
argument_list|(
name|shell
operator|->
name|filters
argument_list|,
operator|(
name|GFunc
operator|)
name|g_object_unref
argument_list|,
name|NULL
argument_list|)
expr_stmt|;
name|g_list_free
argument_list|(
name|shell
operator|->
name|filters
argument_list|)
expr_stmt|;
name|shell
operator|->
name|filters
operator|=
name|NULL
expr_stmt|;
block|}
end_function

begin_function
name|void
DECL|function|gimp_display_shell_filter_reorder_up (GimpDisplayShell * shell,GimpColorDisplay * filter)
name|gimp_display_shell_filter_reorder_up
parameter_list|(
name|GimpDisplayShell
modifier|*
name|shell
parameter_list|,
name|GimpColorDisplay
modifier|*
name|filter
parameter_list|)
block|{
name|GList
modifier|*
name|node_list
decl_stmt|;
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
name|GIMP_IS_COLOR_DISPLAY
argument_list|(
name|filter
argument_list|)
argument_list|)
expr_stmt|;
name|node_list
operator|=
name|g_list_find
argument_list|(
name|shell
operator|->
name|filters
argument_list|,
name|filter
argument_list|)
expr_stmt|;
if|if
condition|(
name|node_list
operator|->
name|prev
condition|)
block|{
name|node_list
operator|->
name|data
operator|=
name|node_list
operator|->
name|prev
operator|->
name|data
expr_stmt|;
name|node_list
operator|->
name|prev
operator|->
name|data
operator|=
name|filter
expr_stmt|;
block|}
block|}
end_function

begin_function
name|void
DECL|function|gimp_display_shell_filter_reorder_down (GimpDisplayShell * shell,GimpColorDisplay * filter)
name|gimp_display_shell_filter_reorder_down
parameter_list|(
name|GimpDisplayShell
modifier|*
name|shell
parameter_list|,
name|GimpColorDisplay
modifier|*
name|filter
parameter_list|)
block|{
name|GList
modifier|*
name|node_list
decl_stmt|;
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
name|GIMP_IS_COLOR_DISPLAY
argument_list|(
name|filter
argument_list|)
argument_list|)
expr_stmt|;
name|node_list
operator|=
name|g_list_find
argument_list|(
name|shell
operator|->
name|filters
argument_list|,
name|filter
argument_list|)
expr_stmt|;
if|if
condition|(
name|node_list
operator|->
name|next
condition|)
block|{
name|node_list
operator|->
name|data
operator|=
name|node_list
operator|->
name|next
operator|->
name|data
expr_stmt|;
name|node_list
operator|->
name|next
operator|->
name|data
operator|=
name|filter
expr_stmt|;
block|}
block|}
end_function

end_unit

