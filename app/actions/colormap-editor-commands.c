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
file|<string.h>
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
file|"gui-types.h"
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
file|"widgets/gimpcolormapeditor.h"
end_include

begin_include
include|#
directive|include
file|"color-notebook.h"
end_include

begin_include
include|#
directive|include
file|"colormap-editor-commands.h"
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
name|colormap_editor_color_notebook_callback
parameter_list|(
name|ColorNotebook
modifier|*
name|cnb
parameter_list|,
specifier|const
name|GimpRGB
modifier|*
name|color
parameter_list|,
name|ColorNotebookState
name|state
parameter_list|,
name|gpointer
name|data
parameter_list|)
function_decl|;
end_function_decl

begin_comment
comment|/*  public functions  */
end_comment

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
decl_stmt|;
name|GimpImage
modifier|*
name|gimage
decl_stmt|;
name|editor
operator|=
name|GIMP_COLORMAP_EDITOR
argument_list|(
name|data
argument_list|)
expr_stmt|;
name|gimage
operator|=
name|GIMP_IMAGE_EDITOR
argument_list|(
name|editor
argument_list|)
operator|->
name|gimage
expr_stmt|;
if|if
condition|(
name|gimage
operator|&&
name|gimage
operator|->
name|num_cols
operator|<
literal|256
condition|)
block|{
name|GimpRGB
name|color
decl_stmt|;
name|gimp_rgb_set_uchar
argument_list|(
operator|&
name|color
argument_list|,
name|gimage
operator|->
name|cmap
index|[
name|editor
operator|->
name|col_index
operator|*
literal|3
index|]
argument_list|,
name|gimage
operator|->
name|cmap
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
name|gimage
operator|->
name|cmap
index|[
name|editor
operator|->
name|col_index
operator|*
literal|3
operator|+
literal|2
index|]
argument_list|)
expr_stmt|;
name|gimp_image_add_colormap_entry
argument_list|(
name|gimage
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
DECL|function|colormap_editor_edit_color_cmd_callback (GtkWidget * widget,gpointer data,guint action)
name|colormap_editor_edit_color_cmd_callback
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
decl_stmt|;
name|GimpImage
modifier|*
name|gimage
decl_stmt|;
name|GimpRGB
name|color
decl_stmt|;
name|editor
operator|=
name|GIMP_COLORMAP_EDITOR
argument_list|(
name|data
argument_list|)
expr_stmt|;
name|gimage
operator|=
name|GIMP_IMAGE_EDITOR
argument_list|(
name|editor
argument_list|)
operator|->
name|gimage
expr_stmt|;
if|if
condition|(
operator|!
name|gimage
condition|)
return|return;
name|gimp_rgba_set_uchar
argument_list|(
operator|&
name|color
argument_list|,
name|gimage
operator|->
name|cmap
index|[
name|editor
operator|->
name|col_index
operator|*
literal|3
index|]
argument_list|,
name|gimage
operator|->
name|cmap
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
name|gimage
operator|->
name|cmap
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
name|OPAQUE_OPACITY
argument_list|)
expr_stmt|;
if|if
condition|(
operator|!
name|editor
operator|->
name|color_notebook
condition|)
block|{
name|editor
operator|->
name|color_notebook
operator|=
name|color_notebook_viewable_new
argument_list|(
name|GIMP_VIEWABLE
argument_list|(
name|gimage
argument_list|)
argument_list|,
name|_
argument_list|(
literal|"Edit Indexed Color"
argument_list|)
argument_list|,
name|GIMP_STOCK_CONVERT_INDEXED
argument_list|,
name|_
argument_list|(
literal|"Edit Indexed Image Palette Color"
argument_list|)
argument_list|,
operator|(
specifier|const
name|GimpRGB
operator|*
operator|)
operator|&
name|color
argument_list|,
name|colormap_editor_color_notebook_callback
argument_list|,
name|editor
argument_list|,
name|FALSE
argument_list|,
name|FALSE
argument_list|)
expr_stmt|;
block|}
else|else
block|{
name|color_notebook_set_viewable
argument_list|(
name|editor
operator|->
name|color_notebook
argument_list|,
name|GIMP_VIEWABLE
argument_list|(
name|gimage
argument_list|)
argument_list|)
expr_stmt|;
name|color_notebook_show
argument_list|(
name|editor
operator|->
name|color_notebook
argument_list|)
expr_stmt|;
name|color_notebook_set_color
argument_list|(
name|editor
operator|->
name|color_notebook
argument_list|,
operator|&
name|color
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
DECL|function|colormap_editor_color_notebook_callback (ColorNotebook * color_notebook,const GimpRGB * color,ColorNotebookState state,gpointer data)
name|colormap_editor_color_notebook_callback
parameter_list|(
name|ColorNotebook
modifier|*
name|color_notebook
parameter_list|,
specifier|const
name|GimpRGB
modifier|*
name|color
parameter_list|,
name|ColorNotebookState
name|state
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
name|gimage
decl_stmt|;
name|editor
operator|=
name|GIMP_COLORMAP_EDITOR
argument_list|(
name|data
argument_list|)
expr_stmt|;
name|gimage
operator|=
name|GIMP_IMAGE_EDITOR
argument_list|(
name|editor
argument_list|)
operator|->
name|gimage
expr_stmt|;
switch|switch
condition|(
name|state
condition|)
block|{
case|case
name|COLOR_NOTEBOOK_UPDATE
case|:
break|break;
case|case
name|COLOR_NOTEBOOK_OK
case|:
name|gimp_image_set_colormap_entry
argument_list|(
name|gimage
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
name|gimage
argument_list|)
expr_stmt|;
comment|/* Fall through */
case|case
name|COLOR_NOTEBOOK_CANCEL
case|:
name|color_notebook_hide
argument_list|(
name|editor
operator|->
name|color_notebook
argument_list|)
expr_stmt|;
break|break;
block|}
block|}
end_function

end_unit

