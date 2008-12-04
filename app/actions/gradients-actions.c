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
file|"core/gimpcontext.h"
end_include

begin_include
include|#
directive|include
file|"core/gimpdata.h"
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
file|"data-commands.h"
end_include

begin_include
include|#
directive|include
file|"gradients-actions.h"
end_include

begin_include
include|#
directive|include
file|"gradients-commands.h"
end_include

begin_include
include|#
directive|include
file|"gimp-intl.h"
end_include

begin_decl_stmt
DECL|variable|gradients_actions
specifier|static
specifier|const
name|GimpActionEntry
name|gradients_actions
index|[]
init|=
block|{
block|{
literal|"gradients-popup"
block|,
name|GIMP_STOCK_GRADIENT
block|,
name|NC_
argument_list|(
literal|"gradients-action"
argument_list|,
literal|"Gradients Menu"
argument_list|)
block|,
name|NULL
block|,
name|NULL
block|,
name|NULL
block|,
name|GIMP_HELP_GRADIENT_DIALOG
block|}
block|,
block|{
literal|"gradients-new"
block|,
name|GTK_STOCK_NEW
block|,
name|NC_
argument_list|(
literal|"gradients-action"
argument_list|,
literal|"_New Gradient"
argument_list|)
block|,
literal|""
block|,
name|NC_
argument_list|(
literal|"gradients-action"
argument_list|,
literal|"Create a new gradient"
argument_list|)
block|,
name|G_CALLBACK
argument_list|(
name|data_new_cmd_callback
argument_list|)
block|,
name|GIMP_HELP_GRADIENT_NEW
block|}
block|,
block|{
literal|"gradients-duplicate"
block|,
name|GIMP_STOCK_DUPLICATE
block|,
name|NC_
argument_list|(
literal|"gradients-action"
argument_list|,
literal|"D_uplicate Gradient"
argument_list|)
block|,
name|NULL
block|,
name|NC_
argument_list|(
literal|"gradients-action"
argument_list|,
literal|"Duplicate this gradient"
argument_list|)
block|,
name|G_CALLBACK
argument_list|(
name|data_duplicate_cmd_callback
argument_list|)
block|,
name|GIMP_HELP_GRADIENT_DUPLICATE
block|}
block|,
block|{
literal|"gradients-copy-location"
block|,
name|GTK_STOCK_COPY
block|,
name|NC_
argument_list|(
literal|"gradients-action"
argument_list|,
literal|"Copy Gradient _Location"
argument_list|)
block|,
literal|""
block|,
name|NC_
argument_list|(
literal|"gradients-action"
argument_list|,
literal|"Copy gradient file location to clipboard"
argument_list|)
block|,
name|G_CALLBACK
argument_list|(
name|data_copy_location_cmd_callback
argument_list|)
block|,
name|GIMP_HELP_GRADIENT_COPY_LOCATION
block|}
block|,
block|{
literal|"gradients-save-as-pov"
block|,
name|GTK_STOCK_SAVE_AS
block|,
name|NC_
argument_list|(
literal|"gradients-action"
argument_list|,
literal|"Save as _POV-Ray..."
argument_list|)
block|,
literal|""
block|,
name|NC_
argument_list|(
literal|"gradients-action"
argument_list|,
literal|"Save gradient as POV-Ray"
argument_list|)
block|,
name|G_CALLBACK
argument_list|(
name|gradients_save_as_pov_ray_cmd_callback
argument_list|)
block|,
name|GIMP_HELP_GRADIENT_SAVE_AS_POV
block|}
block|,
block|{
literal|"gradients-delete"
block|,
name|GTK_STOCK_DELETE
block|,
name|NC_
argument_list|(
literal|"gradients-action"
argument_list|,
literal|"_Delete Gradient"
argument_list|)
block|,
literal|""
block|,
name|NC_
argument_list|(
literal|"gradients-action"
argument_list|,
literal|"Delete this gradient"
argument_list|)
block|,
name|G_CALLBACK
argument_list|(
name|data_delete_cmd_callback
argument_list|)
block|,
name|GIMP_HELP_GRADIENT_DELETE
block|}
block|,
block|{
literal|"gradients-refresh"
block|,
name|GTK_STOCK_REFRESH
block|,
name|NC_
argument_list|(
literal|"gradients-action"
argument_list|,
literal|"_Refresh Gradients"
argument_list|)
block|,
literal|""
block|,
name|NC_
argument_list|(
literal|"gradients-action"
argument_list|,
literal|"Refresh gradients"
argument_list|)
block|,
name|G_CALLBACK
argument_list|(
name|data_refresh_cmd_callback
argument_list|)
block|,
name|GIMP_HELP_GRADIENT_REFRESH
block|}
block|}
decl_stmt|;
end_decl_stmt

begin_decl_stmt
DECL|variable|gradients_edit_actions
specifier|static
specifier|const
name|GimpStringActionEntry
name|gradients_edit_actions
index|[]
init|=
block|{
block|{
literal|"gradients-edit"
block|,
name|GTK_STOCK_EDIT
block|,
name|NC_
argument_list|(
literal|"gradients-action"
argument_list|,
literal|"_Edit Gradient..."
argument_list|)
block|,
name|NULL
block|,
name|NC_
argument_list|(
literal|"gradients-action"
argument_list|,
literal|"Edit gradient"
argument_list|)
block|,
literal|"gimp-gradient-editor"
block|,
name|GIMP_HELP_GRADIENT_EDIT
block|}
block|}
decl_stmt|;
end_decl_stmt

begin_function
name|void
DECL|function|gradients_actions_setup (GimpActionGroup * group)
name|gradients_actions_setup
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
literal|"gradients-action"
argument_list|,
name|gradients_actions
argument_list|,
name|G_N_ELEMENTS
argument_list|(
name|gradients_actions
argument_list|)
argument_list|)
expr_stmt|;
name|gimp_action_group_add_string_actions
argument_list|(
name|group
argument_list|,
literal|"gradients-action"
argument_list|,
name|gradients_edit_actions
argument_list|,
name|G_N_ELEMENTS
argument_list|(
name|gradients_edit_actions
argument_list|)
argument_list|,
name|G_CALLBACK
argument_list|(
name|data_edit_cmd_callback
argument_list|)
argument_list|)
expr_stmt|;
block|}
end_function

begin_function
name|void
DECL|function|gradients_actions_update (GimpActionGroup * group,gpointer user_data)
name|gradients_actions_update
parameter_list|(
name|GimpActionGroup
modifier|*
name|group
parameter_list|,
name|gpointer
name|user_data
parameter_list|)
block|{
name|GimpContext
modifier|*
name|context
init|=
name|action_data_get_context
argument_list|(
name|user_data
argument_list|)
decl_stmt|;
name|GimpGradient
modifier|*
name|gradient
init|=
name|NULL
decl_stmt|;
name|GimpData
modifier|*
name|data
init|=
name|NULL
decl_stmt|;
if|if
condition|(
name|context
condition|)
block|{
name|gradient
operator|=
name|gimp_context_get_gradient
argument_list|(
name|context
argument_list|)
expr_stmt|;
if|if
condition|(
name|gradient
condition|)
name|data
operator|=
name|GIMP_DATA
argument_list|(
name|gradient
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
literal|"gradients-edit"
argument_list|,
name|gradient
argument_list|)
expr_stmt|;
name|SET_SENSITIVE
argument_list|(
literal|"gradients-duplicate"
argument_list|,
name|gradient
argument_list|)
expr_stmt|;
name|SET_SENSITIVE
argument_list|(
literal|"gradients-save-as-pov"
argument_list|,
name|gradient
argument_list|)
expr_stmt|;
name|SET_SENSITIVE
argument_list|(
literal|"gradients-copy-location"
argument_list|,
name|gradient
operator|&&
name|data
operator|->
name|filename
argument_list|)
expr_stmt|;
name|SET_SENSITIVE
argument_list|(
literal|"gradients-delete"
argument_list|,
name|gradient
operator|&&
name|data
operator|->
name|deletable
argument_list|)
expr_stmt|;
undef|#
directive|undef
name|SET_SENSITIVE
block|}
end_function

end_unit

