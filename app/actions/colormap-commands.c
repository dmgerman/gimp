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
file|"widgets/gimpcolormapeditor.h"
end_include

begin_include
include|#
directive|include
file|"colormap-editor-commands.h"
end_include

begin_comment
comment|/*  public functions  */
end_comment

begin_function
name|void
DECL|function|colormap_editor_edit_color_cmd_callback (GtkWidget * widget,gpointer data)
name|colormap_editor_edit_color_cmd_callback
parameter_list|(
name|GtkWidget
modifier|*
name|widget
parameter_list|,
name|gpointer
name|data
parameter_list|)
block|{
name|GimpColormapEditor
modifier|*
name|editor
init|=
name|GIMP_COLORMAP_EDITOR
argument_list|(
name|data
argument_list|)
decl_stmt|;
if|if
condition|(
name|GTK_WIDGET_SENSITIVE
argument_list|(
name|editor
operator|->
name|edit_button
argument_list|)
condition|)
name|gtk_button_clicked
argument_list|(
name|GTK_BUTTON
argument_list|(
name|editor
operator|->
name|edit_button
argument_list|)
argument_list|)
expr_stmt|;
block|}
end_function

begin_function
name|void
DECL|function|colormap_editor_add_color_cmd_callback (GtkWidget * widget,gpointer data,guint action)
name|colormap_editor_add_color_cmd_callback
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
name|GimpColormapEditor
modifier|*
name|editor
init|=
name|GIMP_COLORMAP_EDITOR
argument_list|(
name|data
argument_list|)
decl_stmt|;
if|if
condition|(
name|GTK_WIDGET_SENSITIVE
argument_list|(
name|editor
operator|->
name|add_button
argument_list|)
condition|)
name|gimp_button_extended_clicked
argument_list|(
name|GIMP_BUTTON
argument_list|(
name|editor
operator|->
name|add_button
argument_list|)
argument_list|,
name|action
condition|?
name|GDK_CONTROL_MASK
else|:
literal|0
argument_list|)
expr_stmt|;
block|}
end_function

end_unit

