begin_unit|revision:0.9.5;language:C;cregit-version:0.0.1
begin_comment
comment|/* GIMP - The GNU Image Manipulation Program  * Copyright (C) 1995 Spencer Kimball and Peter Mattis  *  * This program is free software; you can redistribute it and/or modify  * it under the terms of the GNU General Public License as published by  * the Free Software Foundation; either version 2 of the License, or  * (at your option) any later version.  *  * This program is distributed in the hope that it will be useful,  * but WITHOUT ANY WARRANTY; without even the implied warranty of  * MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the  * GNU General Public License for more details.  *  * You should have received a copy of the GNU General Public License  * along with this program; if not, write to the Free Software  * Foundation, Inc., 59 Temple Place - Suite 330, Boston, MA 02111-1307, USA.  */
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
file|"core/gimpchannel.h"
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
file|"widgets/gimphelp-ids.h"
end_include

begin_include
include|#
directive|include
file|"actions.h"
end_include

begin_include
include|#
directive|include
file|"select-actions.h"
end_include

begin_include
include|#
directive|include
file|"select-commands.h"
end_include

begin_include
include|#
directive|include
file|"gimp-intl.h"
end_include

begin_decl_stmt
DECL|variable|select_actions
specifier|static
specifier|const
name|GimpActionEntry
name|select_actions
index|[]
init|=
block|{
block|{
literal|"selection-popup"
block|,
name|GIMP_STOCK_TOOL_RECT_SELECT
block|,
name|N_
argument_list|(
literal|"Selection Editor Menu"
argument_list|)
block|,
name|NULL
block|,
name|NULL
block|,
name|NULL
block|,
name|GIMP_HELP_SELECTION_DIALOG
block|}
block|,
block|{
literal|"select-menu"
block|,
name|NULL
block|,
name|N_
argument_list|(
literal|"_Select"
argument_list|)
block|}
block|,
block|{
literal|"select-all"
block|,
name|GIMP_STOCK_SELECTION_ALL
block|,
name|N_
argument_list|(
literal|"select|_All"
argument_list|)
block|,
literal|"<control>A"
block|,
name|N_
argument_list|(
literal|"Select everything"
argument_list|)
block|,
name|G_CALLBACK
argument_list|(
name|select_all_cmd_callback
argument_list|)
block|,
name|GIMP_HELP_SELECTION_ALL
block|}
block|,
block|{
literal|"select-none"
block|,
name|GIMP_STOCK_SELECTION_NONE
block|,
name|N_
argument_list|(
literal|"select|_None"
argument_list|)
block|,
literal|"<control><shift>A"
block|,
name|N_
argument_list|(
literal|"Dismiss the selection"
argument_list|)
block|,
name|G_CALLBACK
argument_list|(
name|select_none_cmd_callback
argument_list|)
block|,
name|GIMP_HELP_SELECTION_NONE
block|}
block|,
block|{
literal|"select-invert"
block|,
name|GIMP_STOCK_INVERT
block|,
name|N_
argument_list|(
literal|"_Invert"
argument_list|)
block|,
literal|"<control>I"
block|,
name|N_
argument_list|(
literal|"Invert the selection"
argument_list|)
block|,
name|G_CALLBACK
argument_list|(
name|select_invert_cmd_callback
argument_list|)
block|,
name|GIMP_HELP_SELECTION_INVERT
block|}
block|,
block|{
literal|"select-float"
block|,
name|GIMP_STOCK_FLOATING_SELECTION
block|,
name|N_
argument_list|(
literal|"_Float"
argument_list|)
block|,
literal|"<control><shift>L"
block|,
name|N_
argument_list|(
literal|"Create a floating selection"
argument_list|)
block|,
name|G_CALLBACK
argument_list|(
name|select_float_cmd_callback
argument_list|)
block|,
name|GIMP_HELP_SELECTION_FLOAT
block|}
block|,
block|{
literal|"select-feather"
block|,
name|NULL
block|,
name|N_
argument_list|(
literal|"Fea_ther..."
argument_list|)
block|,
name|NULL
block|,
name|N_
argument_list|(
literal|"Blur the selection border so that it fades out smoothly"
argument_list|)
block|,
name|G_CALLBACK
argument_list|(
name|select_feather_cmd_callback
argument_list|)
block|,
name|GIMP_HELP_SELECTION_FEATHER
block|}
block|,
block|{
literal|"select-sharpen"
block|,
name|NULL
block|,
name|N_
argument_list|(
literal|"_Sharpen"
argument_list|)
block|,
name|NULL
block|,
name|N_
argument_list|(
literal|"Remove fuzzyness from the selection"
argument_list|)
block|,
name|G_CALLBACK
argument_list|(
name|select_sharpen_cmd_callback
argument_list|)
block|,
name|GIMP_HELP_SELECTION_SHARPEN
block|}
block|,
block|{
literal|"select-shrink"
block|,
name|GIMP_STOCK_SELECTION_SHRINK
block|,
name|N_
argument_list|(
literal|"S_hrink..."
argument_list|)
block|,
name|NULL
block|,
name|N_
argument_list|(
literal|"Contract the selection"
argument_list|)
block|,
name|G_CALLBACK
argument_list|(
name|select_shrink_cmd_callback
argument_list|)
block|,
name|GIMP_HELP_SELECTION_SHRINK
block|}
block|,
block|{
literal|"select-grow"
block|,
name|GIMP_STOCK_SELECTION_GROW
block|,
name|N_
argument_list|(
literal|"_Grow..."
argument_list|)
block|,
name|NULL
block|,
name|N_
argument_list|(
literal|"Enlarge the selection"
argument_list|)
block|,
name|G_CALLBACK
argument_list|(
name|select_grow_cmd_callback
argument_list|)
block|,
name|GIMP_HELP_SELECTION_GROW
block|}
block|,
block|{
literal|"select-border"
block|,
name|GIMP_STOCK_SELECTION_BORDER
block|,
name|N_
argument_list|(
literal|"Bo_rder..."
argument_list|)
block|,
name|NULL
block|,
name|N_
argument_list|(
literal|"Replace the selection by its border"
argument_list|)
block|,
name|G_CALLBACK
argument_list|(
name|select_border_cmd_callback
argument_list|)
block|,
name|GIMP_HELP_SELECTION_BORDER
block|}
block|,
block|{
literal|"select-save"
block|,
name|GIMP_STOCK_SELECTION_TO_CHANNEL
block|,
name|N_
argument_list|(
literal|"Save to _Channel"
argument_list|)
block|,
name|NULL
block|,
name|N_
argument_list|(
literal|"Save the selection to a channel"
argument_list|)
block|,
name|G_CALLBACK
argument_list|(
name|select_save_cmd_callback
argument_list|)
block|,
name|GIMP_HELP_SELECTION_TO_CHANNEL
block|}
block|,
block|{
literal|"select-stroke"
block|,
name|GIMP_STOCK_SELECTION_STROKE
block|,
name|N_
argument_list|(
literal|"_Stroke Selection..."
argument_list|)
block|,
name|NULL
block|,
name|N_
argument_list|(
literal|"Paint along the selection outline"
argument_list|)
block|,
name|G_CALLBACK
argument_list|(
name|select_stroke_cmd_callback
argument_list|)
block|,
name|GIMP_HELP_SELECTION_STROKE
block|}
block|,
block|{
literal|"select-stroke-last-values"
block|,
name|GIMP_STOCK_SELECTION_STROKE
block|,
name|N_
argument_list|(
literal|"_Stroke Selection"
argument_list|)
block|,
name|NULL
block|,
name|N_
argument_list|(
literal|"Stroke the selection with last used values"
argument_list|)
block|,
name|G_CALLBACK
argument_list|(
name|select_stroke_last_vals_cmd_callback
argument_list|)
block|,
name|GIMP_HELP_SELECTION_STROKE
block|}
block|}
decl_stmt|;
end_decl_stmt

begin_function
name|void
DECL|function|select_actions_setup (GimpActionGroup * group)
name|select_actions_setup
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
name|select_actions
argument_list|,
name|G_N_ELEMENTS
argument_list|(
name|select_actions
argument_list|)
argument_list|)
expr_stmt|;
block|}
end_function

begin_function
name|void
DECL|function|select_actions_update (GimpActionGroup * group,gpointer data)
name|select_actions_update
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
name|GimpDrawable
modifier|*
name|drawable
init|=
name|NULL
decl_stmt|;
name|gboolean
name|fs
init|=
name|FALSE
decl_stmt|;
name|gboolean
name|sel
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
name|fs
operator|=
operator|(
name|gimp_image_floating_sel
argument_list|(
name|image
argument_list|)
operator|!=
name|NULL
operator|)
expr_stmt|;
name|sel
operator|=
operator|!
name|gimp_channel_is_empty
argument_list|(
name|gimp_image_get_mask
argument_list|(
name|image
argument_list|)
argument_list|)
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
literal|"select-all"
argument_list|,
name|drawable
argument_list|)
expr_stmt|;
name|SET_SENSITIVE
argument_list|(
literal|"select-none"
argument_list|,
name|drawable
operator|&&
name|sel
argument_list|)
expr_stmt|;
name|SET_SENSITIVE
argument_list|(
literal|"select-invert"
argument_list|,
name|drawable
argument_list|)
expr_stmt|;
name|SET_SENSITIVE
argument_list|(
literal|"select-float"
argument_list|,
name|drawable
operator|&&
name|sel
argument_list|)
expr_stmt|;
name|SET_SENSITIVE
argument_list|(
literal|"select-feather"
argument_list|,
name|drawable
operator|&&
name|sel
argument_list|)
expr_stmt|;
name|SET_SENSITIVE
argument_list|(
literal|"select-sharpen"
argument_list|,
name|drawable
operator|&&
name|sel
argument_list|)
expr_stmt|;
name|SET_SENSITIVE
argument_list|(
literal|"select-shrink"
argument_list|,
name|drawable
operator|&&
name|sel
argument_list|)
expr_stmt|;
name|SET_SENSITIVE
argument_list|(
literal|"select-grow"
argument_list|,
name|drawable
operator|&&
name|sel
argument_list|)
expr_stmt|;
name|SET_SENSITIVE
argument_list|(
literal|"select-border"
argument_list|,
name|drawable
operator|&&
name|sel
argument_list|)
expr_stmt|;
name|SET_SENSITIVE
argument_list|(
literal|"select-save"
argument_list|,
name|drawable
operator|&&
operator|!
name|fs
argument_list|)
expr_stmt|;
name|SET_SENSITIVE
argument_list|(
literal|"select-stroke"
argument_list|,
name|drawable
operator|&&
name|sel
argument_list|)
expr_stmt|;
name|SET_SENSITIVE
argument_list|(
literal|"select-stroke-last-values"
argument_list|,
name|drawable
operator|&&
name|sel
argument_list|)
expr_stmt|;
undef|#
directive|undef
name|SET_SENSITIVE
block|}
end_function

end_unit

