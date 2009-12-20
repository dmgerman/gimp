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
file|"libgimpwidgets/gimpwidgets.h"
end_include

begin_include
include|#
directive|include
file|"actions-types.h"
end_include

begin_include
include|#
directive|include
file|"widgets/gimpdialogfactory.h"
end_include

begin_include
include|#
directive|include
file|"dialogs/dialogs.h"
end_include

begin_include
include|#
directive|include
file|"actions.h"
end_include

begin_include
include|#
directive|include
file|"dialogs-commands.h"
end_include

begin_comment
comment|/*  public functions  */
end_comment

begin_function
name|void
DECL|function|dialogs_create_toplevel_cmd_callback (GtkAction * action,const gchar * value,gpointer data)
name|dialogs_create_toplevel_cmd_callback
parameter_list|(
name|GtkAction
modifier|*
name|action
parameter_list|,
specifier|const
name|gchar
modifier|*
name|value
parameter_list|,
name|gpointer
name|data
parameter_list|)
block|{
name|GtkWidget
modifier|*
name|widget
decl_stmt|;
name|return_if_no_widget
argument_list|(
name|widget
argument_list|,
name|data
argument_list|)
expr_stmt|;
if|if
condition|(
name|value
condition|)
name|gimp_dialog_factory_dialog_new
argument_list|(
name|global_dialog_factory
argument_list|,
name|gtk_widget_get_screen
argument_list|(
name|widget
argument_list|)
argument_list|,
name|value
argument_list|,
operator|-
literal|1
argument_list|,
name|TRUE
argument_list|)
expr_stmt|;
block|}
end_function

begin_function
name|void
DECL|function|dialogs_create_dockable_cmd_callback (GtkAction * action,const gchar * value,gpointer data)
name|dialogs_create_dockable_cmd_callback
parameter_list|(
name|GtkAction
modifier|*
name|action
parameter_list|,
specifier|const
name|gchar
modifier|*
name|value
parameter_list|,
name|gpointer
name|data
parameter_list|)
block|{
name|GtkWidget
modifier|*
name|widget
decl_stmt|;
name|return_if_no_widget
argument_list|(
name|widget
argument_list|,
name|data
argument_list|)
expr_stmt|;
if|if
condition|(
name|value
condition|)
name|gimp_dialog_factory_dialog_raise
argument_list|(
name|global_dock_window_factory
argument_list|,
name|gtk_widget_get_screen
argument_list|(
name|widget
argument_list|)
argument_list|,
name|value
argument_list|,
operator|-
literal|1
argument_list|)
expr_stmt|;
block|}
end_function

end_unit

