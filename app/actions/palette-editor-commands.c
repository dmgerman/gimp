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
file|"gui-types.h"
end_include

begin_include
include|#
directive|include
file|"widgets/gimppaletteeditor.h"
end_include

begin_include
include|#
directive|include
file|"palette-editor-commands.h"
end_include

begin_comment
comment|/*  public functions  */
end_comment

begin_function
name|void
DECL|function|palette_editor_edit_color_cmd_callback (GtkWidget * widget,gpointer data)
name|palette_editor_edit_color_cmd_callback
parameter_list|(
name|GtkWidget
modifier|*
name|widget
parameter_list|,
name|gpointer
name|data
parameter_list|)
block|{
name|GimpPaletteEditor
modifier|*
name|editor
init|=
name|GIMP_PALETTE_EDITOR
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
DECL|function|palette_editor_new_color_fg_cmd_callback (GtkWidget * widget,gpointer data)
name|palette_editor_new_color_fg_cmd_callback
parameter_list|(
name|GtkWidget
modifier|*
name|widget
parameter_list|,
name|gpointer
name|data
parameter_list|)
block|{
name|GimpPaletteEditor
modifier|*
name|editor
init|=
name|GIMP_PALETTE_EDITOR
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
name|new_button
argument_list|)
condition|)
name|gimp_button_extended_clicked
argument_list|(
name|GIMP_BUTTON
argument_list|(
name|editor
operator|->
name|new_button
argument_list|)
argument_list|,
literal|0
argument_list|)
expr_stmt|;
block|}
end_function

begin_function
name|void
DECL|function|palette_editor_new_color_bg_cmd_callback (GtkWidget * widget,gpointer data)
name|palette_editor_new_color_bg_cmd_callback
parameter_list|(
name|GtkWidget
modifier|*
name|widget
parameter_list|,
name|gpointer
name|data
parameter_list|)
block|{
name|GimpPaletteEditor
modifier|*
name|editor
init|=
name|GIMP_PALETTE_EDITOR
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
name|new_button
argument_list|)
condition|)
name|gimp_button_extended_clicked
argument_list|(
name|GIMP_BUTTON
argument_list|(
name|editor
operator|->
name|new_button
argument_list|)
argument_list|,
name|GDK_CONTROL_MASK
argument_list|)
expr_stmt|;
block|}
end_function

begin_function
name|void
DECL|function|palette_editor_delete_color_cmd_callback (GtkWidget * widget,gpointer data)
name|palette_editor_delete_color_cmd_callback
parameter_list|(
name|GtkWidget
modifier|*
name|widget
parameter_list|,
name|gpointer
name|data
parameter_list|)
block|{
name|GimpPaletteEditor
modifier|*
name|editor
init|=
name|GIMP_PALETTE_EDITOR
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
name|delete_button
argument_list|)
condition|)
name|gtk_button_clicked
argument_list|(
name|GTK_BUTTON
argument_list|(
name|editor
operator|->
name|delete_button
argument_list|)
argument_list|)
expr_stmt|;
block|}
end_function

begin_function
name|void
DECL|function|palette_editor_zoom_in_cmd_callback (GtkWidget * widget,gpointer data)
name|palette_editor_zoom_in_cmd_callback
parameter_list|(
name|GtkWidget
modifier|*
name|widget
parameter_list|,
name|gpointer
name|data
parameter_list|)
block|{
name|GimpPaletteEditor
modifier|*
name|editor
init|=
name|GIMP_PALETTE_EDITOR
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
name|zoom_in_button
argument_list|)
condition|)
name|gtk_button_clicked
argument_list|(
name|GTK_BUTTON
argument_list|(
name|editor
operator|->
name|zoom_in_button
argument_list|)
argument_list|)
expr_stmt|;
block|}
end_function

begin_function
name|void
DECL|function|palette_editor_zoom_out_cmd_callback (GtkWidget * widget,gpointer data)
name|palette_editor_zoom_out_cmd_callback
parameter_list|(
name|GtkWidget
modifier|*
name|widget
parameter_list|,
name|gpointer
name|data
parameter_list|)
block|{
name|GimpPaletteEditor
modifier|*
name|editor
init|=
name|GIMP_PALETTE_EDITOR
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
name|zoom_out_button
argument_list|)
condition|)
name|gtk_button_clicked
argument_list|(
name|GTK_BUTTON
argument_list|(
name|editor
operator|->
name|zoom_out_button
argument_list|)
argument_list|)
expr_stmt|;
block|}
end_function

begin_function
name|void
DECL|function|palette_editor_zoom_all_cmd_callback (GtkWidget * widget,gpointer data)
name|palette_editor_zoom_all_cmd_callback
parameter_list|(
name|GtkWidget
modifier|*
name|widget
parameter_list|,
name|gpointer
name|data
parameter_list|)
block|{
name|GimpPaletteEditor
modifier|*
name|editor
init|=
name|GIMP_PALETTE_EDITOR
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
name|zoom_all_button
argument_list|)
condition|)
name|gtk_button_clicked
argument_list|(
name|GTK_BUTTON
argument_list|(
name|editor
operator|->
name|zoom_all_button
argument_list|)
argument_list|)
expr_stmt|;
block|}
end_function

end_unit

