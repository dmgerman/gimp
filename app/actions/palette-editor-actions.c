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
file|"widgets/gimpactiongroup.h"
end_include

begin_include
include|#
directive|include
file|"widgets/gimphelp-ids.h"
end_include

begin_include
include|#
directive|include
file|"widgets/gimppaletteeditor.h"
end_include

begin_include
include|#
directive|include
file|"palette-editor-actions.h"
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

begin_decl_stmt
DECL|variable|palette_editor_actions
specifier|static
name|GimpActionEntry
name|palette_editor_actions
index|[]
init|=
block|{
block|{
literal|"palette-editor-edit-color"
block|,
name|GIMP_STOCK_EDIT
block|,
name|N_
argument_list|(
literal|"_Edit Color..."
argument_list|)
block|,
literal|""
block|,
name|NULL
block|,
name|G_CALLBACK
argument_list|(
name|palette_editor_edit_color_cmd_callback
argument_list|)
block|,
name|GIMP_HELP_PALETTE_EDITOR_EDIT
block|}
block|,
block|{
literal|"palette-editor-new-color-fg"
block|,
name|GTK_STOCK_NEW
block|,
name|N_
argument_list|(
literal|"New Color from _FG"
argument_list|)
block|,
literal|""
block|,
name|NULL
block|,
name|G_CALLBACK
argument_list|(
name|palette_editor_new_color_fg_cmd_callback
argument_list|)
block|,
name|GIMP_HELP_PALETTE_EDITOR_NEW
block|}
block|,
block|{
literal|"palette-editor-new-color-bg"
block|,
name|GTK_STOCK_NEW
block|,
name|N_
argument_list|(
literal|"New Color from _BG"
argument_list|)
block|,
literal|""
block|,
name|NULL
block|,
name|G_CALLBACK
argument_list|(
name|palette_editor_new_color_bg_cmd_callback
argument_list|)
block|,
name|GIMP_HELP_PALETTE_EDITOR_NEW
block|}
block|,
block|{
literal|"palette-editor-delete-color"
block|,
name|GTK_STOCK_DELETE
block|,
name|N_
argument_list|(
literal|"_Delete Color"
argument_list|)
block|,
literal|""
block|,
name|NULL
block|,
name|G_CALLBACK
argument_list|(
name|palette_editor_delete_color_cmd_callback
argument_list|)
block|,
name|GIMP_HELP_PALETTE_EDITOR_DELETE
block|}
block|,
block|{
literal|"palette-editor-zoom-out"
block|,
name|GTK_STOCK_ZOOM_OUT
block|,
name|N_
argument_list|(
literal|"Zoom _Out"
argument_list|)
block|,
literal|""
block|,
name|NULL
block|,
name|G_CALLBACK
argument_list|(
name|palette_editor_zoom_out_cmd_callback
argument_list|)
block|,
name|GIMP_HELP_PALETTE_EDITOR_ZOOM_OUT
block|}
block|,
block|{
literal|"palette-editor-zoom-in"
block|,
name|GTK_STOCK_ZOOM_IN
block|,
name|N_
argument_list|(
literal|"Zoom _In"
argument_list|)
block|,
literal|""
block|,
name|NULL
block|,
name|G_CALLBACK
argument_list|(
name|palette_editor_zoom_in_cmd_callback
argument_list|)
block|,
name|GIMP_HELP_PALETTE_EDITOR_ZOOM_IN
block|}
block|,
block|{
literal|"palette-editor-zoom-all"
block|,
name|GTK_STOCK_ZOOM_FIT
block|,
name|N_
argument_list|(
literal|"Zoom _All"
argument_list|)
block|,
literal|""
block|,
name|NULL
block|,
name|G_CALLBACK
argument_list|(
name|palette_editor_zoom_all_cmd_callback
argument_list|)
block|,
name|GIMP_HELP_PALETTE_EDITOR_ZOOM_ALL
block|}
block|}
decl_stmt|;
end_decl_stmt

begin_function
name|void
DECL|function|palette_editor_actions_setup (GimpActionGroup * group,gpointer data)
name|palette_editor_actions_setup
parameter_list|(
name|GimpActionGroup
modifier|*
name|group
parameter_list|,
name|gpointer
name|data
parameter_list|)
block|{
name|gimp_action_group_add_actions
argument_list|(
name|group
argument_list|,
name|palette_editor_actions
argument_list|,
name|G_N_ELEMENTS
argument_list|(
name|palette_editor_actions
argument_list|)
argument_list|,
name|data
argument_list|)
expr_stmt|;
block|}
end_function

begin_function
name|void
DECL|function|palette_editor_actions_update (GimpActionGroup * group,gpointer data)
name|palette_editor_actions_update
parameter_list|(
name|GimpActionGroup
modifier|*
name|group
parameter_list|,
name|gpointer
name|data
parameter_list|)
block|{
name|GimpPaletteEditor
modifier|*
name|editor
decl_stmt|;
name|GimpDataEditor
modifier|*
name|data_editor
decl_stmt|;
name|gboolean
name|editable
init|=
name|FALSE
decl_stmt|;
name|editor
operator|=
name|GIMP_PALETTE_EDITOR
argument_list|(
name|data
argument_list|)
expr_stmt|;
name|data_editor
operator|=
name|GIMP_DATA_EDITOR
argument_list|(
name|data
argument_list|)
expr_stmt|;
if|if
condition|(
name|data_editor
operator|->
name|data
operator|&&
name|data_editor
operator|->
name|data_editable
condition|)
name|editable
operator|=
name|TRUE
expr_stmt|;
DECL|macro|SET_SENSITIVE (action,condition)
define|#
directive|define
name|SET_SENSITIVE
parameter_list|(
name|action
parameter_list|,
name|condition
parameter_list|)
define|\
value|gimp_action_group_set_action_sensitive (group, action, (condition) != 0)
name|SET_SENSITIVE
argument_list|(
literal|"palette-editor-edit-color"
argument_list|,
name|editable
operator|&&
name|editor
operator|->
name|color
argument_list|)
expr_stmt|;
name|SET_SENSITIVE
argument_list|(
literal|"palette-editor-new-color-fg"
argument_list|,
name|editable
argument_list|)
expr_stmt|;
name|SET_SENSITIVE
argument_list|(
literal|"palette-editor-new-color-bg"
argument_list|,
name|editable
argument_list|)
expr_stmt|;
name|SET_SENSITIVE
argument_list|(
literal|"palette-editor-delete-color"
argument_list|,
name|editable
operator|&&
name|editor
operator|->
name|color
argument_list|)
expr_stmt|;
name|SET_SENSITIVE
argument_list|(
literal|"palette-editor-zoom-out"
argument_list|,
name|data_editor
operator|->
name|data
argument_list|)
expr_stmt|;
name|SET_SENSITIVE
argument_list|(
literal|"palette-editor-zoom-in"
argument_list|,
name|data_editor
operator|->
name|data
argument_list|)
expr_stmt|;
name|SET_SENSITIVE
argument_list|(
literal|"palette-editor-zoom-all"
argument_list|,
name|data_editor
operator|->
name|data
argument_list|)
expr_stmt|;
undef|#
directive|undef
name|SET_SENSITIVE
block|}
end_function

end_unit

