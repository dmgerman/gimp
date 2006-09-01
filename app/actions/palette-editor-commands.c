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
file|"core/gimp.h"
end_include

begin_include
include|#
directive|include
file|"core/gimpcontext.h"
end_include

begin_include
include|#
directive|include
file|"core/gimpdatafactory.h"
end_include

begin_include
include|#
directive|include
file|"core/gimppalette.h"
end_include

begin_include
include|#
directive|include
file|"widgets/gimpcolordialog.h"
end_include

begin_include
include|#
directive|include
file|"widgets/gimpdialogfactory.h"
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

begin_include
include|#
directive|include
file|"gimp-intl.h"
end_include

begin_comment
comment|/*  local function prototypes  */
end_comment

begin_function_decl
specifier|static
name|void
name|palette_editor_edit_color_update
parameter_list|(
name|GimpColorDialog
modifier|*
name|dialog
parameter_list|,
specifier|const
name|GimpRGB
modifier|*
name|color
parameter_list|,
name|GimpColorDialogState
name|state
parameter_list|,
name|GimpPaletteEditor
modifier|*
name|editor
parameter_list|)
function_decl|;
end_function_decl

begin_comment
comment|/*  public functions  */
end_comment

begin_function
name|void
DECL|function|palette_editor_edit_color_cmd_callback (GtkAction * action,gpointer data)
name|palette_editor_edit_color_cmd_callback
parameter_list|(
name|GtkAction
modifier|*
name|action
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
name|GimpDataEditor
modifier|*
name|data_editor
init|=
name|GIMP_DATA_EDITOR
argument_list|(
name|data
argument_list|)
decl_stmt|;
name|GimpPalette
modifier|*
name|palette
decl_stmt|;
if|if
condition|(
operator|!
operator|(
name|data_editor
operator|->
name|data_editable
operator|&&
name|editor
operator|->
name|color
operator|)
condition|)
return|return;
name|palette
operator|=
name|GIMP_PALETTE
argument_list|(
name|data_editor
operator|->
name|data
argument_list|)
expr_stmt|;
if|if
condition|(
operator|!
name|editor
operator|->
name|color_dialog
condition|)
block|{
name|editor
operator|->
name|color_dialog
operator|=
name|gimp_color_dialog_new
argument_list|(
name|GIMP_VIEWABLE
argument_list|(
name|palette
argument_list|)
argument_list|,
name|data_editor
operator|->
name|context
argument_list|,
name|_
argument_list|(
literal|"Edit Palette Color"
argument_list|)
argument_list|,
name|GIMP_STOCK_PALETTE
argument_list|,
name|_
argument_list|(
literal|"Edit Color Palette Entry"
argument_list|)
argument_list|,
name|GTK_WIDGET
argument_list|(
name|editor
argument_list|)
argument_list|,
name|gimp_dialog_factory_from_name
argument_list|(
literal|"toplevel"
argument_list|)
argument_list|,
literal|"gimp-palette-editor-color-dialog"
argument_list|,
operator|&
name|editor
operator|->
name|color
operator|->
name|color
argument_list|,
name|FALSE
argument_list|,
name|FALSE
argument_list|)
expr_stmt|;
name|g_signal_connect
argument_list|(
name|editor
operator|->
name|color_dialog
argument_list|,
literal|"destroy"
argument_list|,
name|G_CALLBACK
argument_list|(
name|gtk_widget_destroyed
argument_list|)
argument_list|,
operator|&
name|editor
operator|->
name|color_dialog
argument_list|)
expr_stmt|;
name|g_signal_connect
argument_list|(
name|editor
operator|->
name|color_dialog
argument_list|,
literal|"update"
argument_list|,
name|G_CALLBACK
argument_list|(
name|palette_editor_edit_color_update
argument_list|)
argument_list|,
name|editor
argument_list|)
expr_stmt|;
block|}
else|else
block|{
name|gimp_viewable_dialog_set_viewable
argument_list|(
name|GIMP_VIEWABLE_DIALOG
argument_list|(
name|editor
operator|->
name|color_dialog
argument_list|)
argument_list|,
name|GIMP_VIEWABLE
argument_list|(
name|palette
argument_list|)
argument_list|,
name|data_editor
operator|->
name|context
argument_list|)
expr_stmt|;
name|gimp_color_dialog_set_color
argument_list|(
name|GIMP_COLOR_DIALOG
argument_list|(
name|editor
operator|->
name|color_dialog
argument_list|)
argument_list|,
operator|&
name|editor
operator|->
name|color
operator|->
name|color
argument_list|)
expr_stmt|;
block|}
name|gtk_window_present
argument_list|(
name|GTK_WINDOW
argument_list|(
name|editor
operator|->
name|color_dialog
argument_list|)
argument_list|)
expr_stmt|;
block|}
end_function

begin_function
name|void
DECL|function|palette_editor_new_color_cmd_callback (GtkAction * action,gint value,gpointer data)
name|palette_editor_new_color_cmd_callback
parameter_list|(
name|GtkAction
modifier|*
name|action
parameter_list|,
name|gint
name|value
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
name|GimpDataEditor
modifier|*
name|data_editor
init|=
name|GIMP_DATA_EDITOR
argument_list|(
name|data
argument_list|)
decl_stmt|;
if|if
condition|(
name|data_editor
operator|->
name|data_editable
condition|)
block|{
name|GimpPalette
modifier|*
name|palette
init|=
name|GIMP_PALETTE
argument_list|(
name|data_editor
operator|->
name|data
argument_list|)
decl_stmt|;
name|GimpRGB
name|color
decl_stmt|;
if|if
condition|(
name|value
condition|)
name|gimp_context_get_background
argument_list|(
name|data_editor
operator|->
name|context
argument_list|,
operator|&
name|color
argument_list|)
expr_stmt|;
else|else
name|gimp_context_get_foreground
argument_list|(
name|data_editor
operator|->
name|context
argument_list|,
operator|&
name|color
argument_list|)
expr_stmt|;
name|editor
operator|->
name|color
operator|=
name|gimp_palette_add_entry
argument_list|(
name|palette
argument_list|,
operator|-
literal|1
argument_list|,
name|NULL
argument_list|,
operator|&
name|color
argument_list|)
expr_stmt|;
block|}
block|}
end_function

begin_function
name|void
DECL|function|palette_editor_delete_color_cmd_callback (GtkAction * action,gpointer data)
name|palette_editor_delete_color_cmd_callback
parameter_list|(
name|GtkAction
modifier|*
name|action
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
name|GimpDataEditor
modifier|*
name|data_editor
init|=
name|GIMP_DATA_EDITOR
argument_list|(
name|data
argument_list|)
decl_stmt|;
if|if
condition|(
name|data_editor
operator|->
name|data_editable
operator|&&
name|editor
operator|->
name|color
condition|)
block|{
name|GimpPalette
modifier|*
name|palette
init|=
name|GIMP_PALETTE
argument_list|(
name|data_editor
operator|->
name|data
argument_list|)
decl_stmt|;
name|gimp_palette_delete_entry
argument_list|(
name|palette
argument_list|,
name|editor
operator|->
name|color
argument_list|)
expr_stmt|;
block|}
block|}
end_function

begin_function
name|void
DECL|function|palette_editor_zoom_cmd_callback (GtkAction * action,gint value,gpointer data)
name|palette_editor_zoom_cmd_callback
parameter_list|(
name|GtkAction
modifier|*
name|action
parameter_list|,
name|gint
name|value
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
name|gimp_palette_editor_zoom
argument_list|(
name|editor
argument_list|,
operator|(
name|GimpZoomType
operator|)
name|value
argument_list|)
expr_stmt|;
block|}
end_function

begin_comment
comment|/*  private functions  */
end_comment

begin_function
specifier|static
name|void
DECL|function|palette_editor_edit_color_update (GimpColorDialog * dialog,const GimpRGB * color,GimpColorDialogState state,GimpPaletteEditor * editor)
name|palette_editor_edit_color_update
parameter_list|(
name|GimpColorDialog
modifier|*
name|dialog
parameter_list|,
specifier|const
name|GimpRGB
modifier|*
name|color
parameter_list|,
name|GimpColorDialogState
name|state
parameter_list|,
name|GimpPaletteEditor
modifier|*
name|editor
parameter_list|)
block|{
name|GimpPalette
modifier|*
name|palette
init|=
name|GIMP_PALETTE
argument_list|(
name|GIMP_DATA_EDITOR
argument_list|(
name|editor
argument_list|)
operator|->
name|data
argument_list|)
decl_stmt|;
switch|switch
condition|(
name|state
condition|)
block|{
case|case
name|GIMP_COLOR_DIALOG_UPDATE
case|:
break|break;
case|case
name|GIMP_COLOR_DIALOG_OK
case|:
if|if
condition|(
name|editor
operator|->
name|color
condition|)
block|{
name|editor
operator|->
name|color
operator|->
name|color
operator|=
operator|*
name|color
expr_stmt|;
name|gimp_data_dirty
argument_list|(
name|GIMP_DATA
argument_list|(
name|palette
argument_list|)
argument_list|)
expr_stmt|;
block|}
comment|/* Fallthrough */
case|case
name|GIMP_COLOR_DIALOG_CANCEL
case|:
name|gtk_widget_hide
argument_list|(
name|editor
operator|->
name|color_dialog
argument_list|)
expr_stmt|;
break|break;
block|}
block|}
end_function

end_unit

