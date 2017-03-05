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
file|"templates-actions.h"
end_include

begin_include
include|#
directive|include
file|"templates-commands.h"
end_include

begin_include
include|#
directive|include
file|"gimp-intl.h"
end_include

begin_decl_stmt
DECL|variable|templates_actions
specifier|static
specifier|const
name|GimpActionEntry
name|templates_actions
index|[]
init|=
block|{
block|{
literal|"templates-popup"
block|,
name|GIMP_ICON_TEMPLATE
block|,
name|NC_
argument_list|(
literal|"templates-action"
argument_list|,
literal|"Templates Menu"
argument_list|)
block|,
name|NULL
block|,
name|NULL
block|,
name|NULL
block|,
name|GIMP_HELP_TEMPLATE_DIALOG
block|}
block|,
block|{
literal|"templates-create-image"
block|,
name|GIMP_ICON_IMAGE
block|,
name|NC_
argument_list|(
literal|"templates-action"
argument_list|,
literal|"_Create Image from Template"
argument_list|)
block|,
literal|""
block|,
name|NC_
argument_list|(
literal|"templates-action"
argument_list|,
literal|"Create a new image from the selected template"
argument_list|)
block|,
name|G_CALLBACK
argument_list|(
name|templates_create_image_cmd_callback
argument_list|)
block|,
name|GIMP_HELP_TEMPLATE_IMAGE_NEW
block|}
block|,
block|{
literal|"templates-new"
block|,
name|GIMP_ICON_DOCUMENT_NEW
block|,
name|NC_
argument_list|(
literal|"templates-action"
argument_list|,
literal|"_New Template..."
argument_list|)
block|,
name|NULL
block|,
name|NC_
argument_list|(
literal|"templates-action"
argument_list|,
literal|"Create a new template"
argument_list|)
block|,
name|G_CALLBACK
argument_list|(
name|templates_new_cmd_callback
argument_list|)
block|,
name|GIMP_HELP_TEMPLATE_NEW
block|}
block|,
block|{
literal|"templates-duplicate"
block|,
name|GIMP_ICON_OBJECT_DUPLICATE
block|,
name|NC_
argument_list|(
literal|"templates-action"
argument_list|,
literal|"D_uplicate Template..."
argument_list|)
block|,
literal|""
block|,
name|NC_
argument_list|(
literal|"templates-action"
argument_list|,
literal|"Duplicate this template"
argument_list|)
block|,
name|G_CALLBACK
argument_list|(
name|templates_duplicate_cmd_callback
argument_list|)
block|,
name|GIMP_HELP_TEMPLATE_DUPLICATE
block|}
block|,
block|{
literal|"templates-edit"
block|,
name|GIMP_ICON_EDIT
block|,
name|NC_
argument_list|(
literal|"templates-action"
argument_list|,
literal|"_Edit Template..."
argument_list|)
block|,
name|NULL
block|,
name|NC_
argument_list|(
literal|"templates-action"
argument_list|,
literal|"Edit this template"
argument_list|)
block|,
name|G_CALLBACK
argument_list|(
name|templates_edit_cmd_callback
argument_list|)
block|,
name|GIMP_HELP_TEMPLATE_EDIT
block|}
block|,
block|{
literal|"templates-delete"
block|,
name|GIMP_ICON_EDIT_DELETE
block|,
name|NC_
argument_list|(
literal|"templates-action"
argument_list|,
literal|"_Delete Template"
argument_list|)
block|,
name|NULL
block|,
name|NC_
argument_list|(
literal|"templates-action"
argument_list|,
literal|"Delete this template"
argument_list|)
block|,
name|G_CALLBACK
argument_list|(
name|templates_delete_cmd_callback
argument_list|)
block|,
name|GIMP_HELP_TEMPLATE_DELETE
block|}
block|}
decl_stmt|;
end_decl_stmt

begin_function
name|void
DECL|function|templates_actions_setup (GimpActionGroup * group)
name|templates_actions_setup
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
literal|"templates-action"
argument_list|,
name|templates_actions
argument_list|,
name|G_N_ELEMENTS
argument_list|(
name|templates_actions
argument_list|)
argument_list|)
expr_stmt|;
block|}
end_function

begin_function
name|void
DECL|function|templates_actions_update (GimpActionGroup * group,gpointer data)
name|templates_actions_update
parameter_list|(
name|GimpActionGroup
modifier|*
name|group
parameter_list|,
name|gpointer
name|data
parameter_list|)
block|{
name|GimpContext
modifier|*
name|context
init|=
name|action_data_get_context
argument_list|(
name|data
argument_list|)
decl_stmt|;
name|GimpTemplate
modifier|*
name|template
init|=
name|NULL
decl_stmt|;
if|if
condition|(
name|context
condition|)
name|template
operator|=
name|gimp_context_get_template
argument_list|(
name|context
argument_list|)
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
literal|"templates-create-image"
argument_list|,
name|template
argument_list|)
expr_stmt|;
name|SET_SENSITIVE
argument_list|(
literal|"templates-new"
argument_list|,
name|context
argument_list|)
expr_stmt|;
name|SET_SENSITIVE
argument_list|(
literal|"templates-duplicate"
argument_list|,
name|template
argument_list|)
expr_stmt|;
name|SET_SENSITIVE
argument_list|(
literal|"templates-edit"
argument_list|,
name|template
argument_list|)
expr_stmt|;
name|SET_SENSITIVE
argument_list|(
literal|"templates-delete"
argument_list|,
name|template
argument_list|)
expr_stmt|;
undef|#
directive|undef
name|SET_SENSITIVE
block|}
end_function

end_unit

