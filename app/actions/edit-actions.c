begin_unit|revision:0.9.5;language:C;cregit-version:0.0.1
begin_comment
comment|/* GIMP - The GNU Image Manipulation Program  * Copyright (C) 1995 Spencer Kimball and Peter Mattis  *  * This program is free software: you can redistribute it and/or modify  * it under the terms of the GNU General Public License as published by  * the Free Software Foundation; either version 3 of the License, or  * (at your option) any later version.  *  * This program is distributed in the hope that it will be useful,  * but WITHOUT ANY WARRANTY; without even the implied warranty of  * MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the  * GNU General Public License for more details.  *  * You should have received a copy of the GNU General Public License  * along with this program.  If not, see<https://www.gnu.org/licenses/>.  */
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
file|"core/gimpchannel.h"
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
file|"core/gimpimage-undo.h"
end_include

begin_include
include|#
directive|include
file|"core/gimplayer.h"
end_include

begin_include
include|#
directive|include
file|"core/gimplist.h"
end_include

begin_include
include|#
directive|include
file|"core/gimptoolinfo.h"
end_include

begin_include
include|#
directive|include
file|"core/gimpundostack.h"
end_include

begin_include
include|#
directive|include
file|"widgets/gimpaction.h"
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
file|"tools/tool_manager.h"
end_include

begin_include
include|#
directive|include
file|"actions.h"
end_include

begin_include
include|#
directive|include
file|"edit-actions.h"
end_include

begin_include
include|#
directive|include
file|"edit-commands.h"
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
name|edit_actions_foreground_changed
parameter_list|(
name|GimpContext
modifier|*
name|context
parameter_list|,
specifier|const
name|GimpRGB
modifier|*
name|color
parameter_list|,
name|GimpActionGroup
modifier|*
name|group
parameter_list|)
function_decl|;
end_function_decl

begin_function_decl
specifier|static
name|void
name|edit_actions_background_changed
parameter_list|(
name|GimpContext
modifier|*
name|context
parameter_list|,
specifier|const
name|GimpRGB
modifier|*
name|color
parameter_list|,
name|GimpActionGroup
modifier|*
name|group
parameter_list|)
function_decl|;
end_function_decl

begin_function_decl
specifier|static
name|void
name|edit_actions_pattern_changed
parameter_list|(
name|GimpContext
modifier|*
name|context
parameter_list|,
name|GimpPattern
modifier|*
name|pattern
parameter_list|,
name|GimpActionGroup
modifier|*
name|group
parameter_list|)
function_decl|;
end_function_decl

begin_decl_stmt
DECL|variable|edit_actions
specifier|static
specifier|const
name|GimpActionEntry
name|edit_actions
index|[]
init|=
block|{
block|{
literal|"edit-menu"
block|,
name|NULL
block|,
name|NC_
argument_list|(
literal|"edit-action"
argument_list|,
literal|"_Edit"
argument_list|)
block|}
block|,
block|{
literal|"edit-paste-as-menu"
block|,
name|NULL
block|,
name|NC_
argument_list|(
literal|"edit-action"
argument_list|,
literal|"Paste _as"
argument_list|)
block|}
block|,
block|{
literal|"edit-buffer-menu"
block|,
name|NULL
block|,
name|NC_
argument_list|(
literal|"edit-action"
argument_list|,
literal|"_Buffer"
argument_list|)
block|}
block|,
block|{
literal|"undo-popup"
block|,
literal|"edit-undo"
block|,
name|NC_
argument_list|(
literal|"edit-action"
argument_list|,
literal|"Undo History Menu"
argument_list|)
block|,
name|NULL
block|,
name|NULL
block|,
name|NULL
block|,
name|GIMP_HELP_UNDO_DIALOG
block|}
block|,
block|{
literal|"edit-undo"
block|,
name|GIMP_ICON_EDIT_UNDO
block|,
name|NC_
argument_list|(
literal|"edit-action"
argument_list|,
literal|"_Undo"
argument_list|)
block|,
literal|"<primary>Z"
block|,
name|NC_
argument_list|(
literal|"edit-action"
argument_list|,
literal|"Undo the last operation"
argument_list|)
block|,
name|edit_undo_cmd_callback
block|,
name|GIMP_HELP_EDIT_UNDO
block|}
block|,
block|{
literal|"edit-redo"
block|,
name|GIMP_ICON_EDIT_REDO
block|,
name|NC_
argument_list|(
literal|"edit-action"
argument_list|,
literal|"_Redo"
argument_list|)
block|,
literal|"<primary>Y"
block|,
name|NC_
argument_list|(
literal|"edit-action"
argument_list|,
literal|"Redo the last operation that was undone"
argument_list|)
block|,
name|edit_redo_cmd_callback
block|,
name|GIMP_HELP_EDIT_REDO
block|}
block|,
block|{
literal|"edit-strong-undo"
block|,
name|GIMP_ICON_EDIT_UNDO
block|,
name|NC_
argument_list|(
literal|"edit-action"
argument_list|,
literal|"Strong Undo"
argument_list|)
block|,
literal|"<primary><shift>Z"
block|,
name|NC_
argument_list|(
literal|"edit-action"
argument_list|,
literal|"Undo the last operation, skipping visibility changes"
argument_list|)
block|,
name|edit_strong_undo_cmd_callback
block|,
name|GIMP_HELP_EDIT_STRONG_UNDO
block|}
block|,
block|{
literal|"edit-strong-redo"
block|,
name|GIMP_ICON_EDIT_REDO
block|,
name|NC_
argument_list|(
literal|"edit-action"
argument_list|,
literal|"Strong Redo"
argument_list|)
block|,
literal|"<primary><shift>Y"
block|,
name|NC_
argument_list|(
literal|"edit-action"
argument_list|,
literal|"Redo the last operation that was undone, skipping visibility changes"
argument_list|)
block|,
name|edit_strong_redo_cmd_callback
block|,
name|GIMP_HELP_EDIT_STRONG_REDO
block|}
block|,
block|{
literal|"edit-undo-clear"
block|,
name|GIMP_ICON_SHRED
block|,
name|NC_
argument_list|(
literal|"edit-action"
argument_list|,
literal|"_Clear Undo History"
argument_list|)
block|,
name|NULL
block|,
name|NC_
argument_list|(
literal|"edit-action"
argument_list|,
literal|"Remove all operations from the undo history"
argument_list|)
block|,
name|edit_undo_clear_cmd_callback
block|,
name|GIMP_HELP_EDIT_UNDO_CLEAR
block|}
block|,
block|{
literal|"edit-cut"
block|,
name|GIMP_ICON_EDIT_CUT
block|,
name|NC_
argument_list|(
literal|"edit-action"
argument_list|,
literal|"Cu_t"
argument_list|)
block|,
literal|"<primary>X"
block|,
name|NC_
argument_list|(
literal|"edit-action"
argument_list|,
literal|"Move the selected pixels to the clipboard"
argument_list|)
block|,
name|edit_cut_cmd_callback
block|,
name|GIMP_HELP_EDIT_CUT
block|}
block|,
block|{
literal|"edit-copy"
block|,
name|GIMP_ICON_EDIT_COPY
block|,
name|NC_
argument_list|(
literal|"edit-action"
argument_list|,
literal|"_Copy"
argument_list|)
block|,
literal|"<primary>C"
block|,
name|NC_
argument_list|(
literal|"edit-action"
argument_list|,
literal|"Copy the selected pixels to the clipboard"
argument_list|)
block|,
name|edit_copy_cmd_callback
block|,
name|GIMP_HELP_EDIT_COPY
block|}
block|,
block|{
literal|"edit-copy-visible"
block|,
name|NULL
block|,
comment|/* GIMP_ICON_COPY_VISIBLE, */
name|NC_
argument_list|(
literal|"edit-action"
argument_list|,
literal|"Copy _Visible"
argument_list|)
block|,
literal|"<primary><shift>C"
block|,
name|NC_
argument_list|(
literal|"edit-action"
argument_list|,
literal|"Copy what is visible in the selected region"
argument_list|)
block|,
name|edit_copy_visible_cmd_callback
block|,
name|GIMP_HELP_EDIT_COPY_VISIBLE
block|}
block|,
block|{
literal|"edit-paste-as-new-image"
block|,
name|GIMP_ICON_EDIT_PASTE_AS_NEW
block|,
name|NC_
argument_list|(
literal|"edit-action"
argument_list|,
literal|"From _Clipboard"
argument_list|)
block|,
literal|"<primary><shift>V"
block|,
name|NC_
argument_list|(
literal|"edit-action"
argument_list|,
literal|"Create a new image from the content of the clipboard"
argument_list|)
block|,
name|edit_paste_as_new_image_cmd_callback
block|,
name|GIMP_HELP_EDIT_PASTE_AS_NEW_IMAGE
block|}
block|,
block|{
literal|"edit-paste-as-new-image-short"
block|,
name|GIMP_ICON_EDIT_PASTE_AS_NEW
block|,
name|NC_
argument_list|(
literal|"edit-action"
argument_list|,
literal|"_New Image"
argument_list|)
block|,
name|NULL
block|,
name|NC_
argument_list|(
literal|"edit-action"
argument_list|,
literal|"Create a new image from the content of the clipboard"
argument_list|)
block|,
name|edit_paste_as_new_image_cmd_callback
block|,
name|GIMP_HELP_EDIT_PASTE_AS_NEW_IMAGE
block|}
block|,
block|{
literal|"edit-named-cut"
block|,
name|GIMP_ICON_EDIT_CUT
block|,
name|NC_
argument_list|(
literal|"edit-action"
argument_list|,
literal|"Cu_t Named..."
argument_list|)
block|,
name|NULL
block|,
name|NC_
argument_list|(
literal|"edit-action"
argument_list|,
literal|"Move the selected pixels to a named buffer"
argument_list|)
block|,
name|edit_named_cut_cmd_callback
block|,
name|GIMP_HELP_BUFFER_CUT
block|}
block|,
block|{
literal|"edit-named-copy"
block|,
name|GIMP_ICON_EDIT_COPY
block|,
name|NC_
argument_list|(
literal|"edit-action"
argument_list|,
literal|"_Copy Named..."
argument_list|)
block|,
name|NULL
block|,
name|NC_
argument_list|(
literal|"edit-action"
argument_list|,
literal|"Copy the selected pixels to a named buffer"
argument_list|)
block|,
name|edit_named_copy_cmd_callback
block|,
name|GIMP_HELP_BUFFER_COPY
block|}
block|,
block|{
literal|"edit-named-copy-visible"
block|,
name|NULL
block|,
comment|/* GIMP_ICON_COPY_VISIBLE, */
name|NC_
argument_list|(
literal|"edit-action"
argument_list|,
literal|"Copy _Visible Named..."
argument_list|)
block|,
literal|""
block|,
name|NC_
argument_list|(
literal|"edit-action"
argument_list|,
literal|"Copy what is visible in the selected region to a named buffer"
argument_list|)
block|,
name|edit_named_copy_visible_cmd_callback
block|,
name|GIMP_HELP_BUFFER_COPY
block|}
block|,
block|{
literal|"edit-named-paste"
block|,
name|GIMP_ICON_EDIT_PASTE
block|,
name|NC_
argument_list|(
literal|"edit-action"
argument_list|,
literal|"_Paste Named..."
argument_list|)
block|,
name|NULL
block|,
name|NC_
argument_list|(
literal|"edit-action"
argument_list|,
literal|"Paste the content of a named buffer"
argument_list|)
block|,
name|edit_named_paste_cmd_callback
block|,
name|GIMP_HELP_BUFFER_PASTE
block|}
block|,
block|{
literal|"edit-clear"
block|,
name|GIMP_ICON_EDIT_CLEAR
block|,
name|NC_
argument_list|(
literal|"edit-action"
argument_list|,
literal|"Cl_ear"
argument_list|)
block|,
literal|"Delete"
block|,
name|NC_
argument_list|(
literal|"edit-action"
argument_list|,
literal|"Clear the selected pixels"
argument_list|)
block|,
name|edit_clear_cmd_callback
block|,
name|GIMP_HELP_EDIT_CLEAR
block|}
block|}
decl_stmt|;
end_decl_stmt

begin_decl_stmt
DECL|variable|edit_paste_actions
specifier|static
specifier|const
name|GimpEnumActionEntry
name|edit_paste_actions
index|[]
init|=
block|{
block|{
literal|"edit-paste"
block|,
name|GIMP_ICON_EDIT_PASTE
block|,
name|NC_
argument_list|(
literal|"edit-action"
argument_list|,
literal|"_Paste"
argument_list|)
block|,
literal|"<primary>V"
block|,
name|NC_
argument_list|(
literal|"edit-action"
argument_list|,
literal|"Paste the content of the clipboard"
argument_list|)
block|,
name|GIMP_PASTE_TYPE_FLOATING
block|,
name|FALSE
block|,
name|GIMP_HELP_EDIT_PASTE
block|}
block|,
block|{
literal|"edit-paste-in-place"
block|,
name|GIMP_ICON_EDIT_PASTE
block|,
name|NC_
argument_list|(
literal|"edit-action"
argument_list|,
literal|"Paste In Place"
argument_list|)
block|,
literal|"<primary><alt>V"
block|,
name|NC_
argument_list|(
literal|"edit-action"
argument_list|,
literal|"Paste the content of the clipboard at its original position"
argument_list|)
block|,
name|GIMP_PASTE_TYPE_FLOATING_IN_PLACE
block|,
name|FALSE
block|,
name|GIMP_HELP_EDIT_PASTE_IN_PLACE
block|}
block|,
block|{
literal|"edit-paste-into"
block|,
name|GIMP_ICON_EDIT_PASTE_INTO
block|,
name|NC_
argument_list|(
literal|"edit-action"
argument_list|,
literal|"Paste _Into Selection"
argument_list|)
block|,
name|NULL
block|,
name|NC_
argument_list|(
literal|"edit-action"
argument_list|,
literal|"Paste the content of the clipboard into the current selection"
argument_list|)
block|,
name|GIMP_PASTE_TYPE_FLOATING_INTO
block|,
name|FALSE
block|,
name|GIMP_HELP_EDIT_PASTE_INTO
block|}
block|,
block|{
literal|"edit-paste-into-in-place"
block|,
name|GIMP_ICON_EDIT_PASTE_INTO
block|,
name|NC_
argument_list|(
literal|"edit-action"
argument_list|,
literal|"Paste Into Selection In Place"
argument_list|)
block|,
name|NULL
block|,
name|NC_
argument_list|(
literal|"edit-action"
argument_list|,
literal|"Paste the content of the clipboard into the current selection "
literal|"at its original position"
argument_list|)
block|,
name|GIMP_PASTE_TYPE_FLOATING_INTO_IN_PLACE
block|,
name|FALSE
block|,
name|GIMP_HELP_EDIT_PASTE_INTO_IN_PLACE
block|}
block|,
block|{
literal|"edit-paste-as-new-layer"
block|,
name|GIMP_ICON_EDIT_PASTE_AS_NEW
block|,
name|NC_
argument_list|(
literal|"edit-action"
argument_list|,
literal|"New _Layer"
argument_list|)
block|,
name|NULL
block|,
name|NC_
argument_list|(
literal|"edit-action"
argument_list|,
literal|"Create a new layer from the content of the clipboard"
argument_list|)
block|,
name|GIMP_PASTE_TYPE_NEW_LAYER
block|,
name|FALSE
block|,
name|GIMP_HELP_EDIT_PASTE_AS_NEW_LAYER
block|}
block|,
block|{
literal|"edit-paste-as-new-layer-in-place"
block|,
name|GIMP_ICON_EDIT_PASTE_AS_NEW
block|,
name|NC_
argument_list|(
literal|"edit-action"
argument_list|,
literal|"New Layer In _Place"
argument_list|)
block|,
name|NULL
block|,
name|NC_
argument_list|(
literal|"edit-action"
argument_list|,
literal|"Create a new layer from the content of the clipboard "
literal|"and place it at its original position"
argument_list|)
block|,
name|GIMP_PASTE_TYPE_NEW_LAYER_IN_PLACE
block|,
name|FALSE
block|,
name|GIMP_HELP_EDIT_PASTE_AS_NEW_LAYER_IN_PLACE
block|}
block|}
decl_stmt|;
end_decl_stmt

begin_decl_stmt
DECL|variable|edit_fill_actions
specifier|static
specifier|const
name|GimpEnumActionEntry
name|edit_fill_actions
index|[]
init|=
block|{
block|{
literal|"edit-fill-fg"
block|,
name|GIMP_ICON_TOOL_BUCKET_FILL
block|,
name|NC_
argument_list|(
literal|"edit-action"
argument_list|,
literal|"Fill with _FG Color"
argument_list|)
block|,
literal|"<primary>comma"
block|,
name|NC_
argument_list|(
literal|"edit-action"
argument_list|,
literal|"Fill the selection using the foreground color"
argument_list|)
block|,
name|GIMP_FILL_FOREGROUND
block|,
name|FALSE
block|,
name|GIMP_HELP_EDIT_FILL_FG
block|}
block|,
block|{
literal|"edit-fill-bg"
block|,
name|GIMP_ICON_TOOL_BUCKET_FILL
block|,
name|NC_
argument_list|(
literal|"edit-action"
argument_list|,
literal|"Fill with B_G Color"
argument_list|)
block|,
literal|"<primary>period"
block|,
name|NC_
argument_list|(
literal|"edit-action"
argument_list|,
literal|"Fill the selection using the background color"
argument_list|)
block|,
name|GIMP_FILL_BACKGROUND
block|,
name|FALSE
block|,
name|GIMP_HELP_EDIT_FILL_BG
block|}
block|,
block|{
literal|"edit-fill-pattern"
block|,
name|GIMP_ICON_PATTERN
block|,
name|NC_
argument_list|(
literal|"edit-action"
argument_list|,
literal|"Fill _with Pattern"
argument_list|)
block|,
literal|"<primary>semicolon"
block|,
name|NC_
argument_list|(
literal|"edit-action"
argument_list|,
literal|"Fill the selection using the active pattern"
argument_list|)
block|,
name|GIMP_FILL_PATTERN
block|,
name|FALSE
block|,
name|GIMP_HELP_EDIT_FILL_PATTERN
block|}
block|}
decl_stmt|;
end_decl_stmt

begin_function
name|void
DECL|function|edit_actions_setup (GimpActionGroup * group)
name|edit_actions_setup
parameter_list|(
name|GimpActionGroup
modifier|*
name|group
parameter_list|)
block|{
name|GimpContext
modifier|*
name|context
init|=
name|gimp_get_user_context
argument_list|(
name|group
operator|->
name|gimp
argument_list|)
decl_stmt|;
name|GimpRGB
name|color
decl_stmt|;
name|GimpPattern
modifier|*
name|pattern
decl_stmt|;
name|GimpAction
modifier|*
name|action
decl_stmt|;
name|gimp_action_group_add_actions
argument_list|(
name|group
argument_list|,
literal|"edit-action"
argument_list|,
name|edit_actions
argument_list|,
name|G_N_ELEMENTS
argument_list|(
name|edit_actions
argument_list|)
argument_list|)
expr_stmt|;
name|gimp_action_group_add_enum_actions
argument_list|(
name|group
argument_list|,
literal|"edit-action"
argument_list|,
name|edit_paste_actions
argument_list|,
name|G_N_ELEMENTS
argument_list|(
name|edit_paste_actions
argument_list|)
argument_list|,
name|edit_paste_cmd_callback
argument_list|)
expr_stmt|;
name|gimp_action_group_add_enum_actions
argument_list|(
name|group
argument_list|,
literal|"edit-action"
argument_list|,
name|edit_fill_actions
argument_list|,
name|G_N_ELEMENTS
argument_list|(
name|edit_fill_actions
argument_list|)
argument_list|,
name|edit_fill_cmd_callback
argument_list|)
expr_stmt|;
name|action
operator|=
name|gimp_action_group_get_action
argument_list|(
name|group
argument_list|,
literal|"edit-paste-as-new-image-short"
argument_list|)
expr_stmt|;
name|gimp_action_set_accel_path
argument_list|(
name|action
argument_list|,
literal|"<Actions>/edit/edit-paste-as-new-image"
argument_list|)
expr_stmt|;
name|gimp_action_group_set_action_context
argument_list|(
name|group
argument_list|,
literal|"edit-fill-fg"
argument_list|,
name|context
argument_list|)
expr_stmt|;
name|gimp_action_group_set_action_context
argument_list|(
name|group
argument_list|,
literal|"edit-fill-bg"
argument_list|,
name|context
argument_list|)
expr_stmt|;
name|gimp_action_group_set_action_context
argument_list|(
name|group
argument_list|,
literal|"edit-fill-pattern"
argument_list|,
name|context
argument_list|)
expr_stmt|;
name|g_signal_connect_object
argument_list|(
name|context
argument_list|,
literal|"foreground-changed"
argument_list|,
name|G_CALLBACK
argument_list|(
name|edit_actions_foreground_changed
argument_list|)
argument_list|,
name|group
argument_list|,
literal|0
argument_list|)
expr_stmt|;
name|g_signal_connect_object
argument_list|(
name|context
argument_list|,
literal|"background-changed"
argument_list|,
name|G_CALLBACK
argument_list|(
name|edit_actions_background_changed
argument_list|)
argument_list|,
name|group
argument_list|,
literal|0
argument_list|)
expr_stmt|;
name|g_signal_connect_object
argument_list|(
name|context
argument_list|,
literal|"pattern-changed"
argument_list|,
name|G_CALLBACK
argument_list|(
name|edit_actions_pattern_changed
argument_list|)
argument_list|,
name|group
argument_list|,
literal|0
argument_list|)
expr_stmt|;
name|gimp_context_get_foreground
argument_list|(
name|context
argument_list|,
operator|&
name|color
argument_list|)
expr_stmt|;
name|edit_actions_foreground_changed
argument_list|(
name|context
argument_list|,
operator|&
name|color
argument_list|,
name|group
argument_list|)
expr_stmt|;
name|gimp_context_get_background
argument_list|(
name|context
argument_list|,
operator|&
name|color
argument_list|)
expr_stmt|;
name|edit_actions_background_changed
argument_list|(
name|context
argument_list|,
operator|&
name|color
argument_list|,
name|group
argument_list|)
expr_stmt|;
name|pattern
operator|=
name|gimp_context_get_pattern
argument_list|(
name|context
argument_list|)
expr_stmt|;
name|edit_actions_pattern_changed
argument_list|(
name|context
argument_list|,
name|pattern
argument_list|,
name|group
argument_list|)
expr_stmt|;
block|}
end_function

begin_function
name|void
DECL|function|edit_actions_update (GimpActionGroup * group,gpointer data)
name|edit_actions_update
parameter_list|(
name|GimpActionGroup
modifier|*
name|group
parameter_list|,
name|gpointer
name|data
parameter_list|)
block|{
name|GimpImage
modifier|*
name|image
init|=
name|action_data_get_image
argument_list|(
name|data
argument_list|)
decl_stmt|;
name|GimpDisplay
modifier|*
name|display
init|=
name|action_data_get_display
argument_list|(
name|data
argument_list|)
decl_stmt|;
name|GimpDrawable
modifier|*
name|drawable
init|=
name|NULL
decl_stmt|;
name|gchar
modifier|*
name|undo_name
init|=
name|NULL
decl_stmt|;
name|gchar
modifier|*
name|redo_name
init|=
name|NULL
decl_stmt|;
name|gboolean
name|writable
init|=
name|FALSE
decl_stmt|;
name|gboolean
name|children
init|=
name|FALSE
decl_stmt|;
name|gboolean
name|undo_enabled
init|=
name|FALSE
decl_stmt|;
if|if
condition|(
name|image
condition|)
block|{
name|drawable
operator|=
name|gimp_image_get_active_drawable
argument_list|(
name|image
argument_list|)
expr_stmt|;
if|if
condition|(
name|drawable
condition|)
block|{
name|writable
operator|=
operator|!
name|gimp_item_is_content_locked
argument_list|(
name|GIMP_ITEM
argument_list|(
name|drawable
argument_list|)
argument_list|)
expr_stmt|;
if|if
condition|(
name|gimp_viewable_get_children
argument_list|(
name|GIMP_VIEWABLE
argument_list|(
name|drawable
argument_list|)
argument_list|)
condition|)
name|children
operator|=
name|TRUE
expr_stmt|;
block|}
name|undo_enabled
operator|=
name|gimp_image_undo_is_enabled
argument_list|(
name|image
argument_list|)
expr_stmt|;
if|if
condition|(
name|undo_enabled
condition|)
block|{
name|GimpUndoStack
modifier|*
name|undo_stack
init|=
name|gimp_image_get_undo_stack
argument_list|(
name|image
argument_list|)
decl_stmt|;
name|GimpUndoStack
modifier|*
name|redo_stack
init|=
name|gimp_image_get_redo_stack
argument_list|(
name|image
argument_list|)
decl_stmt|;
name|GimpUndo
modifier|*
name|undo
init|=
name|gimp_undo_stack_peek
argument_list|(
name|undo_stack
argument_list|)
decl_stmt|;
name|GimpUndo
modifier|*
name|redo
init|=
name|gimp_undo_stack_peek
argument_list|(
name|redo_stack
argument_list|)
decl_stmt|;
specifier|const
name|gchar
modifier|*
name|tool_undo
init|=
name|NULL
decl_stmt|;
specifier|const
name|gchar
modifier|*
name|tool_redo
init|=
name|NULL
decl_stmt|;
if|if
condition|(
name|display
condition|)
block|{
name|tool_undo
operator|=
name|tool_manager_can_undo_active
argument_list|(
name|image
operator|->
name|gimp
argument_list|,
name|display
argument_list|)
expr_stmt|;
name|tool_redo
operator|=
name|tool_manager_can_redo_active
argument_list|(
name|image
operator|->
name|gimp
argument_list|,
name|display
argument_list|)
expr_stmt|;
block|}
if|if
condition|(
name|tool_undo
condition|)
name|undo_name
operator|=
name|g_strdup_printf
argument_list|(
name|_
argument_list|(
literal|"_Undo %s"
argument_list|)
argument_list|,
name|tool_undo
argument_list|)
expr_stmt|;
elseif|else
if|if
condition|(
name|undo
condition|)
name|undo_name
operator|=
name|g_strdup_printf
argument_list|(
name|_
argument_list|(
literal|"_Undo %s"
argument_list|)
argument_list|,
name|gimp_object_get_name
argument_list|(
name|undo
argument_list|)
argument_list|)
expr_stmt|;
if|if
condition|(
name|tool_redo
condition|)
name|redo_name
operator|=
name|g_strdup_printf
argument_list|(
name|_
argument_list|(
literal|"_Redo %s"
argument_list|)
argument_list|,
name|tool_redo
argument_list|)
expr_stmt|;
elseif|else
if|if
condition|(
name|redo
condition|)
name|redo_name
operator|=
name|g_strdup_printf
argument_list|(
name|_
argument_list|(
literal|"_Redo %s"
argument_list|)
argument_list|,
name|gimp_object_get_name
argument_list|(
name|redo
argument_list|)
argument_list|)
expr_stmt|;
block|}
block|}
DECL|macro|SET_LABEL (action,label)
define|#
directive|define
name|SET_LABEL
parameter_list|(
name|action
parameter_list|,
name|label
parameter_list|)
define|\
value|gimp_action_group_set_action_label (group, action, (label))
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
name|SET_LABEL
argument_list|(
literal|"edit-undo"
argument_list|,
name|undo_name
condition|?
name|undo_name
else|:
name|_
argument_list|(
literal|"_Undo"
argument_list|)
argument_list|)
expr_stmt|;
name|SET_LABEL
argument_list|(
literal|"edit-redo"
argument_list|,
name|redo_name
condition|?
name|redo_name
else|:
name|_
argument_list|(
literal|"_Redo"
argument_list|)
argument_list|)
expr_stmt|;
name|SET_SENSITIVE
argument_list|(
literal|"edit-undo"
argument_list|,
name|undo_enabled
operator|&&
name|undo_name
argument_list|)
expr_stmt|;
name|SET_SENSITIVE
argument_list|(
literal|"edit-redo"
argument_list|,
name|undo_enabled
operator|&&
name|redo_name
argument_list|)
expr_stmt|;
name|SET_SENSITIVE
argument_list|(
literal|"edit-strong-undo"
argument_list|,
name|undo_enabled
operator|&&
name|undo_name
argument_list|)
expr_stmt|;
name|SET_SENSITIVE
argument_list|(
literal|"edit-strong-redo"
argument_list|,
name|undo_enabled
operator|&&
name|redo_name
argument_list|)
expr_stmt|;
name|SET_SENSITIVE
argument_list|(
literal|"edit-undo-clear"
argument_list|,
name|undo_enabled
operator|&&
operator|(
name|undo_name
operator|||
name|redo_name
operator|)
argument_list|)
expr_stmt|;
name|g_free
argument_list|(
name|undo_name
argument_list|)
expr_stmt|;
name|g_free
argument_list|(
name|redo_name
argument_list|)
expr_stmt|;
name|SET_SENSITIVE
argument_list|(
literal|"edit-cut"
argument_list|,
name|writable
operator|&&
operator|!
name|children
argument_list|)
expr_stmt|;
name|SET_SENSITIVE
argument_list|(
literal|"edit-copy"
argument_list|,
name|drawable
argument_list|)
expr_stmt|;
name|SET_SENSITIVE
argument_list|(
literal|"edit-copy-visible"
argument_list|,
name|image
argument_list|)
expr_stmt|;
comment|/*             "edit-paste" is always active */
name|SET_SENSITIVE
argument_list|(
literal|"edit-paste-in-place"
argument_list|,
name|image
argument_list|)
expr_stmt|;
name|SET_SENSITIVE
argument_list|(
literal|"edit-paste-into"
argument_list|,
name|image
argument_list|)
expr_stmt|;
name|SET_SENSITIVE
argument_list|(
literal|"edit-paste-into-in-place"
argument_list|,
name|image
argument_list|)
expr_stmt|;
name|SET_SENSITIVE
argument_list|(
literal|"edit-paste-as-new-layer"
argument_list|,
name|image
argument_list|)
expr_stmt|;
name|SET_SENSITIVE
argument_list|(
literal|"edit-paste-as-new-layer-in-place"
argument_list|,
name|image
argument_list|)
expr_stmt|;
name|SET_SENSITIVE
argument_list|(
literal|"edit-named-cut"
argument_list|,
name|writable
operator|&&
operator|!
name|children
argument_list|)
expr_stmt|;
name|SET_SENSITIVE
argument_list|(
literal|"edit-named-copy"
argument_list|,
name|drawable
argument_list|)
expr_stmt|;
name|SET_SENSITIVE
argument_list|(
literal|"edit-named-copy-visible"
argument_list|,
name|drawable
argument_list|)
expr_stmt|;
comment|/*             "edit-named-paste" is always active */
name|SET_SENSITIVE
argument_list|(
literal|"edit-clear"
argument_list|,
name|writable
operator|&&
operator|!
name|children
argument_list|)
expr_stmt|;
name|SET_SENSITIVE
argument_list|(
literal|"edit-fill-fg"
argument_list|,
name|writable
operator|&&
operator|!
name|children
argument_list|)
expr_stmt|;
name|SET_SENSITIVE
argument_list|(
literal|"edit-fill-bg"
argument_list|,
name|writable
operator|&&
operator|!
name|children
argument_list|)
expr_stmt|;
name|SET_SENSITIVE
argument_list|(
literal|"edit-fill-pattern"
argument_list|,
name|writable
operator|&&
operator|!
name|children
argument_list|)
expr_stmt|;
undef|#
directive|undef
name|SET_LABEL
undef|#
directive|undef
name|SET_SENSITIVE
block|}
end_function

begin_comment
comment|/*  private functions  */
end_comment

begin_function
specifier|static
name|void
DECL|function|edit_actions_foreground_changed (GimpContext * context,const GimpRGB * color,GimpActionGroup * group)
name|edit_actions_foreground_changed
parameter_list|(
name|GimpContext
modifier|*
name|context
parameter_list|,
specifier|const
name|GimpRGB
modifier|*
name|color
parameter_list|,
name|GimpActionGroup
modifier|*
name|group
parameter_list|)
block|{
name|gimp_action_group_set_action_color
argument_list|(
name|group
argument_list|,
literal|"edit-fill-fg"
argument_list|,
name|color
argument_list|,
name|FALSE
argument_list|)
expr_stmt|;
block|}
end_function

begin_function
specifier|static
name|void
DECL|function|edit_actions_background_changed (GimpContext * context,const GimpRGB * color,GimpActionGroup * group)
name|edit_actions_background_changed
parameter_list|(
name|GimpContext
modifier|*
name|context
parameter_list|,
specifier|const
name|GimpRGB
modifier|*
name|color
parameter_list|,
name|GimpActionGroup
modifier|*
name|group
parameter_list|)
block|{
name|gimp_action_group_set_action_color
argument_list|(
name|group
argument_list|,
literal|"edit-fill-bg"
argument_list|,
name|color
argument_list|,
name|FALSE
argument_list|)
expr_stmt|;
block|}
end_function

begin_function
specifier|static
name|void
DECL|function|edit_actions_pattern_changed (GimpContext * context,GimpPattern * pattern,GimpActionGroup * group)
name|edit_actions_pattern_changed
parameter_list|(
name|GimpContext
modifier|*
name|context
parameter_list|,
name|GimpPattern
modifier|*
name|pattern
parameter_list|,
name|GimpActionGroup
modifier|*
name|group
parameter_list|)
block|{
name|gimp_action_group_set_action_viewable
argument_list|(
name|group
argument_list|,
literal|"edit-fill-pattern"
argument_list|,
name|GIMP_VIEWABLE
argument_list|(
name|pattern
argument_list|)
argument_list|)
expr_stmt|;
block|}
end_function

end_unit

