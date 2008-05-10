begin_unit|revision:0.9.5;language:C;cregit-version:0.0.1
begin_comment
comment|/* GIMP - The GNU Image Manipulation Program  * Copyright (C) 1995 Spencer Kimball and Peter Mattis  *  * This program is free software; you can redistribute it and/or modify  * it under the terms of the GNU General Public License as published by  * the Free Software Foundation; either version 2 of the License, or  * (at your option) any later version.  *  * This program is distributed in the hope that it will be useful,  * but WITHOUT ANY WARRANTY; without even the implied warranty of  * MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the  * GNU General Public License for more details.  *  * You should have received a copy of the GNU General Public License  * along with this program; if not, write to the Free Software  * Foundation, Inc., 59 Temple Place - Suite 330, Boston, MA 02111-1307, USA.  */
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
file|"display/gimpdisplay.h"
end_include

begin_include
include|#
directive|include
file|"dialogs/dialogs.h"
end_include

begin_include
include|#
directive|include
file|"windows-commands.h"
end_include

begin_comment
comment|/*  public functions  */
end_comment

begin_function
name|void
DECL|function|windows_show_toolbox_cmd_callback (GtkAction * action,gpointer data)
name|windows_show_toolbox_cmd_callback
parameter_list|(
name|GtkAction
modifier|*
name|action
parameter_list|,
name|gpointer
name|data
parameter_list|)
block|{
name|windows_show_toolbox
argument_list|()
expr_stmt|;
block|}
end_function

begin_function
name|void
DECL|function|windows_show_display_cmd_callback (GtkAction * action,gpointer data)
name|windows_show_display_cmd_callback
parameter_list|(
name|GtkAction
modifier|*
name|action
parameter_list|,
name|gpointer
name|data
parameter_list|)
block|{
name|GimpDisplay
modifier|*
name|display
init|=
name|g_object_get_data
argument_list|(
name|G_OBJECT
argument_list|(
name|action
argument_list|)
argument_list|,
literal|"display"
argument_list|)
decl_stmt|;
name|gtk_window_present
argument_list|(
name|GTK_WINDOW
argument_list|(
name|display
operator|->
name|shell
argument_list|)
argument_list|)
expr_stmt|;
block|}
end_function

begin_function
name|void
DECL|function|windows_show_toolbox (void)
name|windows_show_toolbox
parameter_list|(
name|void
parameter_list|)
block|{
if|if
condition|(
operator|!
name|global_toolbox_factory
operator|->
name|open_dialogs
condition|)
block|{
name|GtkWidget
modifier|*
name|toolbox
decl_stmt|;
name|toolbox
operator|=
name|gimp_dialog_factory_dock_new
argument_list|(
name|global_toolbox_factory
argument_list|,
name|gdk_screen_get_default
argument_list|()
argument_list|)
expr_stmt|;
name|gtk_widget_show
argument_list|(
name|toolbox
argument_list|)
expr_stmt|;
block|}
else|else
block|{
name|gimp_dialog_factory_show_toolbox
argument_list|(
name|global_toolbox_factory
argument_list|)
expr_stmt|;
block|}
block|}
end_function

end_unit

