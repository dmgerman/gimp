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
file|"libgimpcolor/gimpcolor.h"
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
file|"core/gimpcontext.h"
end_include

begin_include
include|#
directive|include
file|"core/gimpimage.h"
end_include

begin_include
include|#
directive|include
file|"core/gimpimage-colormap.h"
end_include

begin_include
include|#
directive|include
file|"widgets/gimpcolordialog.h"
end_include

begin_include
include|#
directive|include
file|"widgets/gimpcolormapeditor.h"
end_include

begin_include
include|#
directive|include
file|"widgets/gimpdialogfactory.h"
end_include

begin_include
include|#
directive|include
file|"actions.h"
end_include

begin_include
include|#
directive|include
file|"colormap-commands.h"
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
name|colormap_edit_color_update
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
name|GimpColormapEditor
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
DECL|function|colormap_edit_color_cmd_callback (GtkAction * action,gpointer data)
name|colormap_edit_color_cmd_callback
parameter_list|(
name|GtkAction
modifier|*
name|action
parameter_list|,
name|gpointer
name|data
parameter_list|)
block|{
name|GimpColormapEditor
modifier|*
name|editor
decl_stmt|;
name|GimpImage
modifier|*
name|image
decl_stmt|;
specifier|const
name|guchar
modifier|*
name|colormap
decl_stmt|;
name|GimpRGB
name|color
decl_stmt|;
name|gchar
modifier|*
name|desc
decl_stmt|;
name|return_if_no_image
argument_list|(
name|image
argument_list|,
name|data
argument_list|)
expr_stmt|;
name|editor
operator|=
name|GIMP_COLORMAP_EDITOR
argument_list|(
name|data
argument_list|)
expr_stmt|;
name|colormap
operator|=
name|gimp_image_get_colormap
argument_list|(
name|image
argument_list|)
expr_stmt|;
name|gimp_rgba_set_uchar
argument_list|(
operator|&
name|color
argument_list|,
name|colormap
index|[
name|editor
operator|->
name|col_index
operator|*
literal|3
index|]
argument_list|,
name|colormap
index|[
name|editor
operator|->
name|col_index
operator|*
literal|3
operator|+
literal|1
index|]
argument_list|,
name|colormap
index|[
name|editor
operator|->
name|col_index
operator|*
literal|3
operator|+
literal|2
index|]
argument_list|,
literal|255
argument_list|)
expr_stmt|;
name|desc
operator|=
name|g_strdup_printf
argument_list|(
name|_
argument_list|(
literal|"Edit colormap entry #%d"
argument_list|)
argument_list|,
name|editor
operator|->
name|col_index
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
name|image
argument_list|)
argument_list|,
name|action_data_get_context
argument_list|(
name|data
argument_list|)
argument_list|,
name|_
argument_list|(
literal|"Edit Colormap Entry"
argument_list|)
argument_list|,
name|GIMP_STOCK_COLORMAP
argument_list|,
name|desc
argument_list|,
name|GTK_WIDGET
argument_list|(
name|editor
argument_list|)
argument_list|,
name|gimp_dialog_factory_get_singleton
argument_list|()
argument_list|,
literal|"gimp-colormap-editor-color-dialog"
argument_list|,
operator|(
specifier|const
name|GimpRGB
operator|*
operator|)
operator|&
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
name|colormap_edit_color_update
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
name|image
argument_list|)
argument_list|,
name|action_data_get_context
argument_list|(
name|data
argument_list|)
argument_list|)
expr_stmt|;
name|g_object_set
argument_list|(
name|editor
operator|->
name|color_dialog
argument_list|,
literal|"description"
argument_list|,
name|desc
argument_list|,
name|NULL
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
name|color
argument_list|)
expr_stmt|;
block|}
name|g_free
argument_list|(
name|desc
argument_list|)
expr_stmt|;
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
DECL|function|colormap_add_color_cmd_callback (GtkAction * action,gint value,gpointer data)
name|colormap_add_color_cmd_callback
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
name|GimpContext
modifier|*
name|context
decl_stmt|;
name|GimpImage
modifier|*
name|image
decl_stmt|;
name|return_if_no_context
argument_list|(
name|context
argument_list|,
name|data
argument_list|)
expr_stmt|;
name|return_if_no_image
argument_list|(
name|image
argument_list|,
name|data
argument_list|)
expr_stmt|;
if|if
condition|(
name|gimp_image_get_colormap_size
argument_list|(
name|image
argument_list|)
operator|<
literal|256
condition|)
block|{
name|GimpRGB
name|color
decl_stmt|;
if|if
condition|(
name|value
condition|)
name|gimp_context_get_background
argument_list|(
name|context
argument_list|,
operator|&
name|color
argument_list|)
expr_stmt|;
else|else
name|gimp_context_get_foreground
argument_list|(
name|context
argument_list|,
operator|&
name|color
argument_list|)
expr_stmt|;
name|gimp_image_add_colormap_entry
argument_list|(
name|image
argument_list|,
operator|&
name|color
argument_list|)
expr_stmt|;
name|gimp_image_flush
argument_list|(
name|image
argument_list|)
expr_stmt|;
block|}
block|}
end_function

begin_comment
comment|/*  private functions  */
end_comment

begin_function
specifier|static
name|void
DECL|function|colormap_edit_color_update (GimpColorDialog * dialog,const GimpRGB * color,GimpColorDialogState state,GimpColormapEditor * editor)
name|colormap_edit_color_update
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
name|GimpColormapEditor
modifier|*
name|editor
parameter_list|)
block|{
name|GimpImage
modifier|*
name|image
init|=
name|GIMP_IMAGE_EDITOR
argument_list|(
name|editor
argument_list|)
operator|->
name|image
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
name|gimp_image_set_colormap_entry
argument_list|(
name|image
argument_list|,
name|editor
operator|->
name|col_index
argument_list|,
name|color
argument_list|,
name|TRUE
argument_list|)
expr_stmt|;
name|gimp_image_flush
argument_list|(
name|image
argument_list|)
expr_stmt|;
comment|/* Fall through */
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

