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
file|"text-editor-actions.h"
end_include

begin_include
include|#
directive|include
file|"text-editor-commands.h"
end_include

begin_include
include|#
directive|include
file|"gimp-intl.h"
end_include

begin_decl_stmt
DECL|variable|text_editor_actions
specifier|static
specifier|const
name|GimpActionEntry
name|text_editor_actions
index|[]
init|=
block|{
block|{
literal|"text-editor-toolbar"
block|,
name|GIMP_ICON_EDIT
block|,
literal|"Text Editor Toolbar"
block|,
name|NULL
block|,
name|NULL
block|,
name|NULL
block|,
name|GIMP_HELP_TEXT_EDITOR_DIALOG
block|}
block|,
block|{
literal|"text-editor-load"
block|,
name|GIMP_ICON_DOCUMENT_OPEN
block|,
name|NC_
argument_list|(
literal|"text-editor-action"
argument_list|,
literal|"Open"
argument_list|)
block|,
name|NULL
block|,
name|NC_
argument_list|(
literal|"text-editor-action"
argument_list|,
literal|"Load text from file"
argument_list|)
block|,
name|text_editor_load_cmd_callback
block|,
name|NULL
block|}
block|,
block|{
literal|"text-editor-clear"
block|,
name|GIMP_ICON_EDIT_CLEAR
block|,
name|NC_
argument_list|(
literal|"text-editor-action"
argument_list|,
literal|"Clear"
argument_list|)
block|,
name|NULL
block|,
name|NC_
argument_list|(
literal|"text-editor-action"
argument_list|,
literal|"Clear all text"
argument_list|)
block|,
name|text_editor_clear_cmd_callback
block|,
name|NULL
block|}
block|}
decl_stmt|;
end_decl_stmt

begin_decl_stmt
DECL|variable|text_editor_direction_actions
specifier|static
specifier|const
name|GimpRadioActionEntry
name|text_editor_direction_actions
index|[]
init|=
block|{
block|{
literal|"text-editor-direction-ltr"
block|,
name|GIMP_ICON_FORMAT_TEXT_DIRECTION_LTR
block|,
name|NC_
argument_list|(
literal|"text-editor-action"
argument_list|,
literal|"LTR"
argument_list|)
block|,
name|NULL
block|,
name|NC_
argument_list|(
literal|"text-editor-action"
argument_list|,
literal|"From left to right"
argument_list|)
block|,
name|GIMP_TEXT_DIRECTION_LTR
block|,
name|NULL
block|}
block|,
block|{
literal|"text-editor-direction-rtl"
block|,
name|GIMP_ICON_FORMAT_TEXT_DIRECTION_RTL
block|,
name|NC_
argument_list|(
literal|"text-editor-action"
argument_list|,
literal|"RTL"
argument_list|)
block|,
name|NULL
block|,
name|NC_
argument_list|(
literal|"text-editor-action"
argument_list|,
literal|"From right to left"
argument_list|)
block|,
name|GIMP_TEXT_DIRECTION_RTL
block|,
name|NULL
block|}
block|,
block|{
literal|"text-editor-direction-ttb-rtl"
block|,
name|GIMP_ICON_FORMAT_TEXT_DIRECTION_TTB_RTL
block|,
name|NC_
argument_list|(
literal|"text-editor-action"
argument_list|,
literal|"TTB-RTL"
argument_list|)
block|,
name|NULL
block|,
name|NC_
argument_list|(
literal|"text-editor-action"
argument_list|,
literal|"Vertical, right to left (mixed orientation)"
argument_list|)
block|,
name|GIMP_TEXT_DIRECTION_TTB_RTL
block|,
name|NULL
block|}
block|,
block|{
literal|"text-editor-direction-ttb-rtl-upright"
block|,
name|GIMP_ICON_FORMAT_TEXT_DIRECTION_TTB_RTL_UPRIGHT
block|,
name|NC_
argument_list|(
literal|"text-editor-action"
argument_list|,
literal|"TTB-RTL-UPRIGHT"
argument_list|)
block|,
name|NULL
block|,
name|NC_
argument_list|(
literal|"text-editor-action"
argument_list|,
literal|"Vertical, right to left (upright orientation)"
argument_list|)
block|,
name|GIMP_TEXT_DIRECTION_TTB_RTL_UPRIGHT
block|,
name|NULL
block|}
block|,
block|{
literal|"text-editor-direction-ttb-ltr"
block|,
name|GIMP_ICON_FORMAT_TEXT_DIRECTION_TTB_LTR
block|,
name|NC_
argument_list|(
literal|"text-editor-action"
argument_list|,
literal|"TTB-LTR"
argument_list|)
block|,
name|NULL
block|,
name|NC_
argument_list|(
literal|"text-editor-action"
argument_list|,
literal|"Vertical, left to right (mixed orientation)"
argument_list|)
block|,
name|GIMP_TEXT_DIRECTION_TTB_LTR
block|,
name|NULL
block|}
block|,
block|{
literal|"text-editor-direction-ttb-ltr-upright"
block|,
name|GIMP_ICON_FORMAT_TEXT_DIRECTION_TTB_LTR_UPRIGHT
block|,
name|NC_
argument_list|(
literal|"text-editor-action"
argument_list|,
literal|"TTB-LTR-UPRIGHT"
argument_list|)
block|,
name|NULL
block|,
name|NC_
argument_list|(
literal|"text-editor-action"
argument_list|,
literal|"Vertical, left to right (upright orientation)"
argument_list|)
block|,
name|GIMP_TEXT_DIRECTION_TTB_LTR_UPRIGHT
block|,
name|NULL
block|}
block|, }
decl_stmt|;
end_decl_stmt

begin_function
name|void
DECL|function|text_editor_actions_setup (GimpActionGroup * group)
name|text_editor_actions_setup
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
literal|"text-editor-action"
argument_list|,
name|text_editor_actions
argument_list|,
name|G_N_ELEMENTS
argument_list|(
name|text_editor_actions
argument_list|)
argument_list|)
expr_stmt|;
name|gimp_action_group_add_radio_actions
argument_list|(
name|group
argument_list|,
literal|"text-editor-action"
argument_list|,
name|text_editor_direction_actions
argument_list|,
name|G_N_ELEMENTS
argument_list|(
name|text_editor_direction_actions
argument_list|)
argument_list|,
name|NULL
argument_list|,
name|GIMP_TEXT_DIRECTION_LTR
argument_list|,
name|text_editor_direction_cmd_callback
argument_list|)
expr_stmt|;
block|}
end_function

begin_function
name|void
DECL|function|text_editor_actions_update (GimpActionGroup * group,gpointer data)
name|text_editor_actions_update
parameter_list|(
name|GimpActionGroup
modifier|*
name|group
parameter_list|,
name|gpointer
name|data
parameter_list|)
block|{
name|GimpTextEditor
modifier|*
name|editor
init|=
name|GIMP_TEXT_EDITOR
argument_list|(
name|data
argument_list|)
decl_stmt|;
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
switch|switch
condition|(
name|editor
operator|->
name|base_dir
condition|)
block|{
case|case
name|GIMP_TEXT_DIRECTION_LTR
case|:
name|SET_ACTIVE
argument_list|(
literal|"text-editor-direction-ltr"
argument_list|,
name|TRUE
argument_list|)
expr_stmt|;
break|break;
case|case
name|GIMP_TEXT_DIRECTION_RTL
case|:
name|SET_ACTIVE
argument_list|(
literal|"text-editor-direction-rtl"
argument_list|,
name|TRUE
argument_list|)
expr_stmt|;
break|break;
case|case
name|GIMP_TEXT_DIRECTION_TTB_RTL
case|:
name|SET_ACTIVE
argument_list|(
literal|"text-editor-direction-ttb-rtl"
argument_list|,
name|TRUE
argument_list|)
expr_stmt|;
break|break;
case|case
name|GIMP_TEXT_DIRECTION_TTB_RTL_UPRIGHT
case|:
name|SET_ACTIVE
argument_list|(
literal|"text-editor-direction-ttb-rtl-upright"
argument_list|,
name|TRUE
argument_list|)
expr_stmt|;
break|break;
case|case
name|GIMP_TEXT_DIRECTION_TTB_LTR
case|:
name|SET_ACTIVE
argument_list|(
literal|"text-editor-direction-ttb-ltr"
argument_list|,
name|TRUE
argument_list|)
expr_stmt|;
break|break;
case|case
name|GIMP_TEXT_DIRECTION_TTB_LTR_UPRIGHT
case|:
name|SET_ACTIVE
argument_list|(
literal|"text-editor-direction-ttb-ltr-upright"
argument_list|,
name|TRUE
argument_list|)
expr_stmt|;
break|break;
block|}
undef|#
directive|undef
name|SET_ACTIVE
block|}
end_function

end_unit

