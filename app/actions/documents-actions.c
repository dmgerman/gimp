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
file|"documents-actions.h"
end_include

begin_include
include|#
directive|include
file|"documents-commands.h"
end_include

begin_include
include|#
directive|include
file|"gimp-intl.h"
end_include

begin_decl_stmt
DECL|variable|documents_actions
specifier|static
specifier|const
name|GimpActionEntry
name|documents_actions
index|[]
init|=
block|{
block|{
literal|"documents-popup"
block|,
literal|"document-open-recent"
block|,
name|NC_
argument_list|(
literal|"documents-action"
argument_list|,
literal|"Documents Menu"
argument_list|)
block|,
name|NULL
block|,
name|NULL
block|,
name|NULL
block|,
name|GIMP_HELP_DOCUMENT_DIALOG
block|}
block|,
block|{
literal|"documents-open"
block|,
literal|"document-open"
block|,
name|NC_
argument_list|(
literal|"documents-action"
argument_list|,
literal|"_Open Image"
argument_list|)
block|,
name|NULL
block|,
name|NC_
argument_list|(
literal|"documents-action"
argument_list|,
literal|"Open the selected entry"
argument_list|)
block|,
name|G_CALLBACK
argument_list|(
name|documents_open_cmd_callback
argument_list|)
block|,
name|GIMP_HELP_DOCUMENT_OPEN
block|}
block|,
block|{
literal|"documents-raise-or-open"
block|,
name|NULL
block|,
name|NC_
argument_list|(
literal|"documents-action"
argument_list|,
literal|"_Raise or Open Image"
argument_list|)
block|,
name|NULL
block|,
name|NC_
argument_list|(
literal|"documents-action"
argument_list|,
literal|"Raise window if already open"
argument_list|)
block|,
name|G_CALLBACK
argument_list|(
name|documents_raise_or_open_cmd_callback
argument_list|)
block|,
name|GIMP_HELP_DOCUMENT_OPEN
block|}
block|,
block|{
literal|"documents-file-open-dialog"
block|,
name|NULL
block|,
name|NC_
argument_list|(
literal|"documents-action"
argument_list|,
literal|"File Open _Dialog"
argument_list|)
block|,
name|NULL
block|,
name|NC_
argument_list|(
literal|"documents-action"
argument_list|,
literal|"Open image dialog"
argument_list|)
block|,
name|G_CALLBACK
argument_list|(
name|documents_file_open_dialog_cmd_callback
argument_list|)
block|,
name|GIMP_HELP_DOCUMENT_OPEN
block|}
block|,
block|{
literal|"documents-copy-location"
block|,
literal|"edit-copy"
block|,
name|NC_
argument_list|(
literal|"documents-action"
argument_list|,
literal|"Copy Image _Location"
argument_list|)
block|,
name|NULL
block|,
name|NC_
argument_list|(
literal|"documents-action"
argument_list|,
literal|"Copy image location to clipboard"
argument_list|)
block|,
name|G_CALLBACK
argument_list|(
name|documents_copy_location_cmd_callback
argument_list|)
block|,
name|GIMP_HELP_DOCUMENT_COPY_LOCATION
block|}
block|,
block|{
literal|"documents-show-in-file-manager"
block|,
name|GIMP_STOCK_FILE_MANAGER
block|,
name|NC_
argument_list|(
literal|"documents-action"
argument_list|,
literal|"Show in _File Manager"
argument_list|)
block|,
name|NULL
block|,
name|NC_
argument_list|(
literal|"documents-action"
argument_list|,
literal|"Show image location in the file manager"
argument_list|)
block|,
name|G_CALLBACK
argument_list|(
name|documents_show_in_file_manager_cmd_callback
argument_list|)
block|,
name|GIMP_HELP_DOCUMENT_SHOW_IN_FILE_MANAGER
block|}
block|,
block|{
literal|"documents-remove"
block|,
literal|"list-remove"
block|,
name|NC_
argument_list|(
literal|"documents-action"
argument_list|,
literal|"Remove _Entry"
argument_list|)
block|,
name|NULL
block|,
name|NC_
argument_list|(
literal|"documents-action"
argument_list|,
literal|"Remove the selected entry"
argument_list|)
block|,
name|G_CALLBACK
argument_list|(
name|documents_remove_cmd_callback
argument_list|)
block|,
name|GIMP_HELP_DOCUMENT_REMOVE
block|}
block|,
block|{
literal|"documents-clear"
block|,
name|GIMP_STOCK_SHRED
block|,
name|NC_
argument_list|(
literal|"documents-action"
argument_list|,
literal|"_Clear History"
argument_list|)
block|,
name|NULL
block|,
name|NC_
argument_list|(
literal|"documents-action"
argument_list|,
literal|"Clear the entire document history"
argument_list|)
block|,
name|G_CALLBACK
argument_list|(
name|documents_clear_cmd_callback
argument_list|)
block|,
name|GIMP_HELP_DOCUMENT_CLEAR
block|}
block|,
block|{
literal|"documents-recreate-preview"
block|,
literal|"view-refresh"
block|,
name|NC_
argument_list|(
literal|"documents-action"
argument_list|,
literal|"Recreate _Preview"
argument_list|)
block|,
name|NULL
block|,
name|NC_
argument_list|(
literal|"documents-action"
argument_list|,
literal|"Recreate preview"
argument_list|)
block|,
name|G_CALLBACK
argument_list|(
name|documents_recreate_preview_cmd_callback
argument_list|)
block|,
name|GIMP_HELP_DOCUMENT_REFRESH
block|}
block|,
block|{
literal|"documents-reload-previews"
block|,
name|NULL
block|,
name|NC_
argument_list|(
literal|"documents-action"
argument_list|,
literal|"Reload _all Previews"
argument_list|)
block|,
name|NULL
block|,
name|NC_
argument_list|(
literal|"documents-action"
argument_list|,
literal|"Reload all previews"
argument_list|)
block|,
name|G_CALLBACK
argument_list|(
name|documents_reload_previews_cmd_callback
argument_list|)
block|,
name|GIMP_HELP_DOCUMENT_REFRESH
block|}
block|,
block|{
literal|"documents-remove-dangling"
block|,
name|NULL
block|,
name|NC_
argument_list|(
literal|"documents-action"
argument_list|,
literal|"Remove Dangling E_ntries"
argument_list|)
block|,
name|NULL
block|,
name|NC_
argument_list|(
literal|"documents-action"
argument_list|,
literal|"Remove entries for which the corresponding file is not available"
argument_list|)
block|,
name|G_CALLBACK
argument_list|(
name|documents_remove_dangling_cmd_callback
argument_list|)
block|,
name|GIMP_HELP_DOCUMENT_REFRESH
block|}
block|}
decl_stmt|;
end_decl_stmt

begin_function
name|void
DECL|function|documents_actions_setup (GimpActionGroup * group)
name|documents_actions_setup
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
literal|"documents-action"
argument_list|,
name|documents_actions
argument_list|,
name|G_N_ELEMENTS
argument_list|(
name|documents_actions
argument_list|)
argument_list|)
expr_stmt|;
block|}
end_function

begin_function
name|void
DECL|function|documents_actions_update (GimpActionGroup * group,gpointer data)
name|documents_actions_update
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
decl_stmt|;
name|GimpImagefile
modifier|*
name|imagefile
init|=
name|NULL
decl_stmt|;
name|context
operator|=
name|action_data_get_context
argument_list|(
name|data
argument_list|)
expr_stmt|;
if|if
condition|(
name|context
condition|)
name|imagefile
operator|=
name|gimp_context_get_imagefile
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
literal|"documents-open"
argument_list|,
name|imagefile
argument_list|)
expr_stmt|;
name|SET_SENSITIVE
argument_list|(
literal|"documents-raise-or-open"
argument_list|,
name|imagefile
argument_list|)
expr_stmt|;
name|SET_SENSITIVE
argument_list|(
literal|"documents-file-open-dialog"
argument_list|,
name|TRUE
argument_list|)
expr_stmt|;
name|SET_SENSITIVE
argument_list|(
literal|"documents-copy-location"
argument_list|,
name|imagefile
argument_list|)
expr_stmt|;
name|SET_SENSITIVE
argument_list|(
literal|"documents-show-in-file-manager"
argument_list|,
name|imagefile
argument_list|)
expr_stmt|;
name|SET_SENSITIVE
argument_list|(
literal|"documents-remove"
argument_list|,
name|imagefile
argument_list|)
expr_stmt|;
name|SET_SENSITIVE
argument_list|(
literal|"documents-clear"
argument_list|,
name|TRUE
argument_list|)
expr_stmt|;
name|SET_SENSITIVE
argument_list|(
literal|"documents-recreate-preview"
argument_list|,
name|imagefile
argument_list|)
expr_stmt|;
name|SET_SENSITIVE
argument_list|(
literal|"documents-reload-previews"
argument_list|,
name|imagefile
argument_list|)
expr_stmt|;
name|SET_SENSITIVE
argument_list|(
literal|"documents-remove-dangling"
argument_list|,
name|imagefile
argument_list|)
expr_stmt|;
undef|#
directive|undef
name|SET_SENSITIVE
block|}
end_function

end_unit

