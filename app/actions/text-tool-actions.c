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
file|"core/gimpimage.h"
end_include

begin_include
include|#
directive|include
file|"text/gimptextlayer.h"
end_include

begin_include
include|#
directive|include
file|"widgets/gimpactiongroup.h"
end_include

begin_include
include|#
directive|include
file|"widgets/gimptexteditor.h"
end_include

begin_include
include|#
directive|include
file|"widgets/gimphelp-ids.h"
end_include

begin_include
include|#
directive|include
file|"display/gimpdisplay.h"
end_include

begin_include
include|#
directive|include
file|"display/gimpdisplayshell.h"
end_include

begin_include
include|#
directive|include
file|"tools/gimptool.h"
end_include

begin_include
include|#
directive|include
file|"tools/gimptexttool.h"
end_include

begin_include
include|#
directive|include
file|"text-tool-actions.h"
end_include

begin_include
include|#
directive|include
file|"text-tool-commands.h"
end_include

begin_include
include|#
directive|include
file|"gimp-intl.h"
end_include

begin_decl_stmt
DECL|variable|text_tool_actions
specifier|static
specifier|const
name|GimpActionEntry
name|text_tool_actions
index|[]
init|=
block|{
block|{
literal|"text-tool-popup"
block|,
name|NULL
block|,
name|NC_
argument_list|(
literal|"text-tool-action"
argument_list|,
literal|"Text Tool Menu"
argument_list|)
block|,
name|NULL
block|,
name|NULL
block|,
name|NULL
block|,
name|NULL
block|}
block|,
block|{
literal|"text-tool-input-methods-menu"
block|,
name|NULL
block|,
name|NC_
argument_list|(
literal|"text-tool-action"
argument_list|,
literal|"Input _Methods"
argument_list|)
block|,
name|NULL
block|,
name|NULL
block|,
name|NULL
block|,
name|NULL
block|}
block|,
block|{
literal|"text-tool-cut"
block|,
name|GIMP_ICON_EDIT_CUT
block|,
name|NC_
argument_list|(
literal|"text-tool-action"
argument_list|,
literal|"Cu_t"
argument_list|)
block|,
name|NULL
block|,
literal|"<primary>X"
block|,
name|G_CALLBACK
argument_list|(
name|text_tool_cut_cmd_callback
argument_list|)
block|,
name|NULL
block|}
block|,
block|{
literal|"text-tool-copy"
block|,
name|GIMP_ICON_EDIT_COPY
block|,
name|NC_
argument_list|(
literal|"text-tool-action"
argument_list|,
literal|"_Copy"
argument_list|)
block|,
name|NULL
block|,
literal|"<primary>C"
block|,
name|G_CALLBACK
argument_list|(
name|text_tool_copy_cmd_callback
argument_list|)
block|,
name|NULL
block|}
block|,
block|{
literal|"text-tool-paste"
block|,
name|GIMP_ICON_EDIT_PASTE
block|,
name|NC_
argument_list|(
literal|"text-tool-action"
argument_list|,
literal|"_Paste"
argument_list|)
block|,
name|NULL
block|,
literal|"<primary>V"
block|,
name|G_CALLBACK
argument_list|(
name|text_tool_paste_cmd_callback
argument_list|)
block|,
name|NULL
block|}
block|,
block|{
literal|"text-tool-delete"
block|,
name|GIMP_ICON_EDIT_DELETE
block|,
name|NC_
argument_list|(
literal|"text-tool-action"
argument_list|,
literal|"_Delete"
argument_list|)
block|,
name|NULL
block|,
name|NULL
block|,
name|G_CALLBACK
argument_list|(
name|text_tool_delete_cmd_callback
argument_list|)
block|,
name|NULL
block|}
block|,
block|{
literal|"text-tool-load"
block|,
name|GIMP_ICON_DOCUMENT_OPEN
block|,
name|NC_
argument_list|(
literal|"text-tool-action"
argument_list|,
literal|"_Open text file..."
argument_list|)
block|,
name|NULL
block|,
name|NULL
block|,
name|G_CALLBACK
argument_list|(
name|text_tool_load_cmd_callback
argument_list|)
block|,
name|NULL
block|}
block|,
block|{
literal|"text-tool-clear"
block|,
name|GIMP_ICON_EDIT_CLEAR
block|,
name|NC_
argument_list|(
literal|"text-tool-action"
argument_list|,
literal|"Cl_ear"
argument_list|)
block|,
name|NULL
block|,
name|NC_
argument_list|(
literal|"text-tool-action"
argument_list|,
literal|"Clear all text"
argument_list|)
block|,
name|G_CALLBACK
argument_list|(
name|text_tool_clear_cmd_callback
argument_list|)
block|,
name|NULL
block|}
block|,
block|{
literal|"text-tool-text-to-path"
block|,
name|GIMP_ICON_PATH
block|,
name|NC_
argument_list|(
literal|"text-tool-action"
argument_list|,
literal|"_Path from Text"
argument_list|)
block|,
literal|""
block|,
name|NC_
argument_list|(
literal|"text-tool-action"
argument_list|,
literal|"Create a path from the outlines of the current text"
argument_list|)
block|,
name|G_CALLBACK
argument_list|(
name|text_tool_text_to_path_cmd_callback
argument_list|)
block|,
name|NULL
block|}
block|,
block|{
literal|"text-tool-text-along-path"
block|,
name|GIMP_ICON_PATH
block|,
name|NC_
argument_list|(
literal|"text-tool-action"
argument_list|,
literal|"Text _along Path"
argument_list|)
block|,
literal|""
block|,
name|NC_
argument_list|(
literal|"text-tool-action"
argument_list|,
literal|"Bend the text along the currently active path"
argument_list|)
block|,
name|G_CALLBACK
argument_list|(
name|text_tool_text_along_path_cmd_callback
argument_list|)
block|,
name|NULL
block|}
block|}
decl_stmt|;
end_decl_stmt

begin_decl_stmt
DECL|variable|text_tool_direction_actions
specifier|static
specifier|const
name|GimpRadioActionEntry
name|text_tool_direction_actions
index|[]
init|=
block|{
block|{
literal|"text-tool-direction-ltr"
block|,
name|GIMP_ICON_FORMAT_TEXT_DIRECTION_LTR
block|,
name|NC_
argument_list|(
literal|"text-tool-action"
argument_list|,
literal|"From left to right"
argument_list|)
block|,
name|NULL
block|,
name|NULL
block|,
name|GIMP_TEXT_DIRECTION_LTR
block|,
name|NULL
block|}
block|,
block|{
literal|"text-tool-direction-rtl"
block|,
name|GIMP_ICON_FORMAT_TEXT_DIRECTION_RTL
block|,
name|NC_
argument_list|(
literal|"text-tool-action"
argument_list|,
literal|"From right to left"
argument_list|)
block|,
name|NULL
block|,
name|NULL
block|,
name|GIMP_TEXT_DIRECTION_RTL
block|,
name|NULL
block|}
block|,
block|{
literal|"text-tool-direction-ttb-rtl"
block|,
name|GIMP_ICON_FORMAT_TEXT_DIRECTION_TTB_RTL
block|,
name|NC_
argument_list|(
literal|"text-tool-action"
argument_list|,
literal|"Characters are from top to bottom, Lines are from right to left"
argument_list|)
block|,
name|NULL
block|,
name|NULL
block|,
name|GIMP_TEXT_DIRECTION_TTB_RTL
block|,
name|NULL
block|}
block|,
block|{
literal|"text-tool-direction-ttb-rtl-upright"
block|,
name|GIMP_ICON_FORMAT_TEXT_DIRECTION_TTB_RTL_UPRIGHT
block|,
name|NC_
argument_list|(
literal|"text-tool-action"
argument_list|,
literal|"Upright characters are from top to bottom, Lines are from right to left"
argument_list|)
block|,
name|NULL
block|,
name|NULL
block|,
name|GIMP_TEXT_DIRECTION_TTB_RTL_UPRIGHT
block|,
name|NULL
block|}
block|,
block|{
literal|"text-tool-direction-ttb-ltr"
block|,
name|GIMP_ICON_FORMAT_TEXT_DIRECTION_TTB_LTR
block|,
name|NC_
argument_list|(
literal|"text-tool-action"
argument_list|,
literal|"Characters are from top to bottom, Lines are from left to right"
argument_list|)
block|,
name|NULL
block|,
name|NULL
block|,
name|GIMP_TEXT_DIRECTION_TTB_LTR
block|,
name|NULL
block|}
block|,
block|{
literal|"text-tool-direction-ttb-ltr-upright"
block|,
name|GIMP_ICON_FORMAT_TEXT_DIRECTION_TTB_LTR_UPRIGHT
block|,
name|NC_
argument_list|(
literal|"text-tool-action"
argument_list|,
literal|"Upright characters are from top to bottom, Lines are from left to right"
argument_list|)
block|,
name|NULL
block|,
name|NULL
block|,
name|GIMP_TEXT_DIRECTION_TTB_LTR_UPRIGHT
block|,
name|NULL
block|}
block|}
decl_stmt|;
end_decl_stmt

begin_define
DECL|macro|SET_HIDE_EMPTY (action,condition)
define|#
directive|define
name|SET_HIDE_EMPTY
parameter_list|(
name|action
parameter_list|,
name|condition
parameter_list|)
define|\
value|gimp_action_group_set_action_hide_empty (group, action, (condition) != 0)
end_define

begin_function
name|void
DECL|function|text_tool_actions_setup (GimpActionGroup * group)
name|text_tool_actions_setup
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
literal|"text-tool-action"
argument_list|,
name|text_tool_actions
argument_list|,
name|G_N_ELEMENTS
argument_list|(
name|text_tool_actions
argument_list|)
argument_list|)
expr_stmt|;
name|gimp_action_group_add_radio_actions
argument_list|(
name|group
argument_list|,
literal|"text-tool-action"
argument_list|,
name|text_tool_direction_actions
argument_list|,
name|G_N_ELEMENTS
argument_list|(
name|text_tool_direction_actions
argument_list|)
argument_list|,
name|NULL
argument_list|,
name|GIMP_TEXT_DIRECTION_LTR
argument_list|,
name|G_CALLBACK
argument_list|(
name|text_tool_direction_cmd_callback
argument_list|)
argument_list|)
expr_stmt|;
name|SET_HIDE_EMPTY
argument_list|(
literal|"text-tool-input-methods-menu"
argument_list|,
name|FALSE
argument_list|)
expr_stmt|;
block|}
end_function

begin_comment
comment|/* The following code is written on the assumption that this is for a  * context menu, activated by right-clicking in a text layer.  * Therefore, the tool must have a display.  If for any reason the  * code is adapted to a different situation, some existence testing  * will need to be added.  */
end_comment

begin_function
name|void
DECL|function|text_tool_actions_update (GimpActionGroup * group,gpointer data)
name|text_tool_actions_update
parameter_list|(
name|GimpActionGroup
modifier|*
name|group
parameter_list|,
name|gpointer
name|data
parameter_list|)
block|{
name|GimpTextTool
modifier|*
name|text_tool
init|=
name|GIMP_TEXT_TOOL
argument_list|(
name|data
argument_list|)
decl_stmt|;
name|GimpDisplay
modifier|*
name|display
init|=
name|GIMP_TOOL
argument_list|(
name|text_tool
argument_list|)
operator|->
name|display
decl_stmt|;
name|GimpImage
modifier|*
name|image
init|=
name|gimp_display_get_image
argument_list|(
name|display
argument_list|)
decl_stmt|;
name|GimpLayer
modifier|*
name|layer
decl_stmt|;
name|GimpVectors
modifier|*
name|vectors
decl_stmt|;
name|GimpDisplayShell
modifier|*
name|shell
decl_stmt|;
name|GtkClipboard
modifier|*
name|clipboard
decl_stmt|;
name|gboolean
name|text_layer
init|=
name|FALSE
decl_stmt|;
name|gboolean
name|text_sel
init|=
name|FALSE
decl_stmt|;
comment|/* some text is selected        */
name|gboolean
name|clip
init|=
name|FALSE
decl_stmt|;
comment|/* clipboard has text available */
name|gboolean
name|input_method_menu
decl_stmt|;
name|gboolean
name|unicode_menu
decl_stmt|;
name|layer
operator|=
name|gimp_image_get_active_layer
argument_list|(
name|image
argument_list|)
expr_stmt|;
if|if
condition|(
name|layer
condition|)
name|text_layer
operator|=
name|gimp_item_is_text_layer
argument_list|(
name|GIMP_ITEM
argument_list|(
name|layer
argument_list|)
argument_list|)
expr_stmt|;
name|vectors
operator|=
name|gimp_image_get_active_vectors
argument_list|(
name|image
argument_list|)
expr_stmt|;
name|text_sel
operator|=
name|gimp_text_tool_get_has_text_selection
argument_list|(
name|text_tool
argument_list|)
expr_stmt|;
comment|/* see whether there is text available for pasting */
name|shell
operator|=
name|gimp_display_get_shell
argument_list|(
name|display
argument_list|)
expr_stmt|;
name|clipboard
operator|=
name|gtk_widget_get_clipboard
argument_list|(
name|shell
operator|->
name|canvas
argument_list|,
name|GDK_SELECTION_CLIPBOARD
argument_list|)
expr_stmt|;
name|clip
operator|=
name|gtk_clipboard_wait_is_text_available
argument_list|(
name|clipboard
argument_list|)
expr_stmt|;
name|g_object_get
argument_list|(
name|gtk_widget_get_settings
argument_list|(
name|shell
operator|->
name|canvas
argument_list|)
argument_list|,
literal|"gtk-show-input-method-menu"
argument_list|,
operator|&
name|input_method_menu
argument_list|,
literal|"gtk-show-unicode-menu"
argument_list|,
operator|&
name|unicode_menu
argument_list|,
name|NULL
argument_list|)
expr_stmt|;
DECL|macro|SET_VISIBLE (action,condition)
define|#
directive|define
name|SET_VISIBLE
parameter_list|(
name|action
parameter_list|,
name|condition
parameter_list|)
define|\
value|gimp_action_group_set_action_visible (group, action, (condition) != 0)
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
DECL|macro|SET_ACTIVE (action,condition)
define|#
directive|define
name|SET_ACTIVE
parameter_list|(
name|action
parameter_list|,
name|condition
parameter_list|)
define|\
value|gimp_action_group_set_action_active (group, action, (condition) != 0)
name|SET_SENSITIVE
argument_list|(
literal|"text-tool-cut"
argument_list|,
name|text_sel
argument_list|)
expr_stmt|;
name|SET_SENSITIVE
argument_list|(
literal|"text-tool-copy"
argument_list|,
name|text_sel
argument_list|)
expr_stmt|;
name|SET_SENSITIVE
argument_list|(
literal|"text-tool-paste"
argument_list|,
name|clip
argument_list|)
expr_stmt|;
name|SET_SENSITIVE
argument_list|(
literal|"text-tool-delete"
argument_list|,
name|text_sel
argument_list|)
expr_stmt|;
name|SET_SENSITIVE
argument_list|(
literal|"text-tool-clear"
argument_list|,
name|text_layer
argument_list|)
expr_stmt|;
name|SET_SENSITIVE
argument_list|(
literal|"text-tool-load"
argument_list|,
name|image
argument_list|)
expr_stmt|;
name|SET_SENSITIVE
argument_list|(
literal|"text-tool-text-to-path"
argument_list|,
name|text_layer
argument_list|)
expr_stmt|;
name|SET_SENSITIVE
argument_list|(
literal|"text-tool-text-along-path"
argument_list|,
name|text_layer
operator|&&
name|vectors
argument_list|)
expr_stmt|;
name|SET_VISIBLE
argument_list|(
literal|"text-tool-input-methods-menu"
argument_list|,
name|input_method_menu
argument_list|)
expr_stmt|;
block|}
end_function

end_unit

