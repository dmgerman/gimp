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
file|<gtk/gtk.h>
end_include

begin_include
include|#
directive|include
file|"apptypes.h"
end_include

begin_include
include|#
directive|include
file|"widgets/gimpdialogfactory.h"
end_include

begin_include
include|#
directive|include
file|"widgets/gimpdock.h"
end_include

begin_include
include|#
directive|include
file|"widgets/gimpdockable.h"
end_include

begin_include
include|#
directive|include
file|"widgets/gimpdockbook.h"
end_include

begin_include
include|#
directive|include
file|"dialogs.h"
end_include

begin_include
include|#
directive|include
file|"dialogs-commands.h"
end_include

begin_function
name|void
DECL|function|dialogs_create_toplevel_cmd_callback (GtkWidget * widget,gpointer data,guint action)
name|dialogs_create_toplevel_cmd_callback
parameter_list|(
name|GtkWidget
modifier|*
name|widget
parameter_list|,
name|gpointer
name|data
parameter_list|,
name|guint
name|action
parameter_list|)
block|{
if|if
condition|(
name|action
condition|)
block|{
name|gimp_dialog_factory_dialog_new
argument_list|(
name|global_dialog_factory
argument_list|,
name|GUINT_TO_POINTER
argument_list|(
name|action
argument_list|)
argument_list|)
expr_stmt|;
block|}
block|}
end_function

begin_function
name|void
DECL|function|dialogs_add_tab_cmd_callback (GtkWidget * widget,gpointer data,guint action)
name|dialogs_add_tab_cmd_callback
parameter_list|(
name|GtkWidget
modifier|*
name|widget
parameter_list|,
name|gpointer
name|data
parameter_list|,
name|guint
name|action
parameter_list|)
block|{
name|GimpDockbook
modifier|*
name|dockbook
decl_stmt|;
name|dockbook
operator|=
operator|(
name|GimpDockbook
operator|*
operator|)
name|gtk_item_factory_popup_data_from_widget
argument_list|(
name|widget
argument_list|)
expr_stmt|;
if|if
condition|(
name|dockbook
operator|&&
name|action
condition|)
block|{
name|GtkWidget
modifier|*
name|dockable
decl_stmt|;
name|dockable
operator|=
name|gimp_dialog_factory_dockable_new
argument_list|(
name|dockbook
operator|->
name|dock
operator|->
name|factory
argument_list|,
name|dockbook
operator|->
name|dock
argument_list|,
name|GUINT_TO_POINTER
argument_list|(
name|action
argument_list|)
argument_list|)
expr_stmt|;
if|if
condition|(
name|dockable
condition|)
name|gimp_dockbook_add
argument_list|(
name|dockbook
argument_list|,
name|GIMP_DOCKABLE
argument_list|(
name|dockable
argument_list|)
argument_list|,
operator|-
literal|1
argument_list|)
expr_stmt|;
block|}
block|}
end_function

begin_function
name|void
DECL|function|dialogs_remove_tab_cmd_callback (GtkWidget * widget,gpointer data,guint action)
name|dialogs_remove_tab_cmd_callback
parameter_list|(
name|GtkWidget
modifier|*
name|widget
parameter_list|,
name|gpointer
name|data
parameter_list|,
name|guint
name|action
parameter_list|)
block|{
name|GimpDockbook
modifier|*
name|dockbook
decl_stmt|;
name|dockbook
operator|=
operator|(
name|GimpDockbook
operator|*
operator|)
name|gtk_item_factory_popup_data_from_widget
argument_list|(
name|widget
argument_list|)
expr_stmt|;
if|if
condition|(
name|dockbook
condition|)
block|{
name|GimpDockable
modifier|*
name|dockable
decl_stmt|;
name|gint
name|page_num
decl_stmt|;
name|page_num
operator|=
name|gtk_notebook_get_current_page
argument_list|(
name|GTK_NOTEBOOK
argument_list|(
name|dockbook
argument_list|)
argument_list|)
expr_stmt|;
name|dockable
operator|=
operator|(
name|GimpDockable
operator|*
operator|)
name|gtk_notebook_get_nth_page
argument_list|(
name|GTK_NOTEBOOK
argument_list|(
name|dockbook
argument_list|)
argument_list|,
name|page_num
argument_list|)
expr_stmt|;
if|if
condition|(
name|dockable
condition|)
name|gimp_dockbook_remove
argument_list|(
name|dockbook
argument_list|,
name|dockable
argument_list|)
expr_stmt|;
block|}
block|}
end_function

end_unit

