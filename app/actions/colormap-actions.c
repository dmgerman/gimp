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
file|"core/gimpimage.h"
end_include

begin_include
include|#
directive|include
file|"widgets/gimpactiongroup.h"
end_include

begin_include
include|#
directive|include
file|"widgets/gimpcolormapeditor.h"
end_include

begin_include
include|#
directive|include
file|"widgets/gimphelp-ids.h"
end_include

begin_include
include|#
directive|include
file|"colormap-editor-actions.h"
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

begin_decl_stmt
DECL|variable|colormap_editor_actions
specifier|static
name|GimpActionEntry
name|colormap_editor_actions
index|[]
init|=
block|{
block|{
literal|"colormap-editor-popup"
block|,
name|GIMP_STOCK_INDEXED_PALETTE
block|,
name|N_
argument_list|(
literal|"Indexed Palette Menu"
argument_list|)
block|}
block|,
block|{
literal|"colormap-editor-edit-color"
block|,
name|GIMP_STOCK_EDIT
block|,
name|N_
argument_list|(
literal|"_Edit Color..."
argument_list|)
block|,
name|NULL
block|,
name|NULL
block|,
name|G_CALLBACK
argument_list|(
name|colormap_editor_edit_color_cmd_callback
argument_list|)
block|,
name|GIMP_HELP_INDEXED_PALETTE_EDIT
block|}
block|}
decl_stmt|;
end_decl_stmt

begin_decl_stmt
DECL|variable|colormap_editor_add_color_actions
specifier|static
name|GimpEnumActionEntry
name|colormap_editor_add_color_actions
index|[]
init|=
block|{
block|{
literal|"colormap-editor-add-color-from-fg"
block|,
name|GTK_STOCK_ADD
block|,
name|N_
argument_list|(
literal|"_Add Color from FG"
argument_list|)
block|,
literal|""
block|,
name|NULL
block|,
name|FALSE
block|,
name|GIMP_HELP_INDEXED_PALETTE_ADD
block|}
block|,
block|{
literal|"colormap-editor-add-color-from-bg"
block|,
name|GTK_STOCK_ADD
block|,
name|N_
argument_list|(
literal|"_Add Color from BG"
argument_list|)
block|,
literal|""
block|,
name|NULL
block|,
name|TRUE
block|,
name|GIMP_HELP_INDEXED_PALETTE_ADD
block|}
block|}
decl_stmt|;
end_decl_stmt

begin_function
name|void
DECL|function|colormap_editor_actions_setup (GimpActionGroup * group)
name|colormap_editor_actions_setup
parameter_list|(
name|GimpActionGroup
modifier|*
name|group
parameter_list|)
block|{
name|gimp_action_group_add_actions
argument_list|(
name|group
argument_list|,
name|colormap_editor_actions
argument_list|,
name|G_N_ELEMENTS
argument_list|(
name|colormap_editor_actions
argument_list|)
argument_list|)
expr_stmt|;
name|gimp_action_group_add_enum_actions
argument_list|(
name|group
argument_list|,
name|colormap_editor_add_color_actions
argument_list|,
name|G_N_ELEMENTS
argument_list|(
name|colormap_editor_add_color_actions
argument_list|)
argument_list|,
name|G_CALLBACK
argument_list|(
name|colormap_editor_add_color_cmd_callback
argument_list|)
argument_list|)
expr_stmt|;
block|}
end_function

begin_function
name|void
DECL|function|colormap_editor_actions_update (GimpActionGroup * group,gpointer data)
name|colormap_editor_actions_update
parameter_list|(
name|GimpActionGroup
modifier|*
name|group
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
name|gboolean
name|indexed
init|=
name|FALSE
decl_stmt|;
name|gint
name|num_colors
init|=
literal|0
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
condition|)
block|{
name|indexed
operator|=
name|gimp_image_base_type
argument_list|(
name|gimage
argument_list|)
operator|==
name|GIMP_INDEXED
expr_stmt|;
name|num_colors
operator|=
name|gimage
operator|->
name|num_cols
expr_stmt|;
block|}
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
literal|"colormap-editor-edit-color"
argument_list|,
name|gimage
operator|&&
name|indexed
argument_list|)
expr_stmt|;
name|SET_SENSITIVE
argument_list|(
literal|"colormap-editor-add-color-from-fg"
argument_list|,
name|gimage
operator|&&
name|indexed
operator|&&
name|num_colors
operator|<
literal|256
argument_list|)
expr_stmt|;
name|SET_SENSITIVE
argument_list|(
literal|"colormap-editor-add-color-from-bg"
argument_list|,
name|gimage
operator|&&
name|indexed
operator|&&
name|num_colors
operator|<
literal|256
argument_list|)
expr_stmt|;
undef|#
directive|undef
name|SET_SENSITIVE
block|}
end_function

end_unit

