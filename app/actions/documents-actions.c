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
file|"widgets/gimpcontainereditor.h"
end_include

begin_include
include|#
directive|include
file|"widgets/gimpcontainerview.h"
end_include

begin_include
include|#
directive|include
file|"widgets/gimphelp-ids.h"
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
name|GimpActionEntry
name|documents_actions
index|[]
init|=
block|{
block|{
literal|"ducuments-popup"
block|,
name|NULL
block|,
name|N_
argument_list|(
literal|"Documents Menu"
argument_list|)
block|}
block|,
block|{
literal|"documents-open"
block|,
name|GTK_STOCK_OPEN
block|,
name|N_
argument_list|(
literal|"_Open Image"
argument_list|)
block|,
literal|""
block|,
name|NULL
block|,
name|G_CALLBACK
argument_list|(
name|documents_open_document_cmd_callback
argument_list|)
block|,
name|GIMP_HELP_DOCUMENT_OPEN
block|}
block|,
block|{
literal|"documents-raise-or-open"
block|,
name|GTK_STOCK_OPEN
block|,
name|N_
argument_list|(
literal|"_Raise or Open Image"
argument_list|)
block|,
literal|""
block|,
name|NULL
block|,
name|G_CALLBACK
argument_list|(
name|documents_raise_or_open_document_cmd_callback
argument_list|)
block|,
name|GIMP_HELP_DOCUMENT_OPEN
block|}
block|,
block|{
literal|"documents-file-open-dialog"
block|,
name|GTK_STOCK_OPEN
block|,
name|N_
argument_list|(
literal|"File Open _Dialog"
argument_list|)
block|,
literal|""
block|,
name|NULL
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
literal|"documents-remove"
block|,
name|GTK_STOCK_REMOVE
block|,
name|N_
argument_list|(
literal|"Remove _Entry"
argument_list|)
block|,
literal|""
block|,
name|NULL
block|,
name|G_CALLBACK
argument_list|(
name|documents_remove_document_cmd_callback
argument_list|)
block|,
name|GIMP_HELP_DOCUMENT_REMOVE
block|}
block|,
block|{
literal|"documents-recreate-preview"
block|,
name|GTK_STOCK_REFRESH
block|,
name|N_
argument_list|(
literal|"Recreate _Preview"
argument_list|)
block|,
literal|""
block|,
name|NULL
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
name|GTK_STOCK_REFRESH
block|,
name|N_
argument_list|(
literal|"Reload _all Previews"
argument_list|)
block|,
literal|""
block|,
name|NULL
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
name|GTK_STOCK_REFRESH
block|,
name|N_
argument_list|(
literal|"Remove Dangling E_ntries"
argument_list|)
block|,
literal|""
block|,
name|NULL
block|,
name|G_CALLBACK
argument_list|(
name|documents_delete_dangling_documents_cmd_callback
argument_list|)
block|,
name|GIMP_HELP_DOCUMENT_REFRESH
block|}
block|}
decl_stmt|;
end_decl_stmt

begin_function
name|void
DECL|function|documents_actions_setup (GimpActionGroup * group,gpointer data)
name|documents_actions_setup
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
name|documents_actions
argument_list|,
name|G_N_ELEMENTS
argument_list|(
name|documents_actions
argument_list|)
argument_list|,
name|data
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
name|GimpContainerEditor
modifier|*
name|editor
decl_stmt|;
name|GimpImagefile
modifier|*
name|imagefile
decl_stmt|;
name|editor
operator|=
name|GIMP_CONTAINER_EDITOR
argument_list|(
name|data
argument_list|)
expr_stmt|;
name|imagefile
operator|=
name|gimp_context_get_imagefile
argument_list|(
name|editor
operator|->
name|view
operator|->
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
literal|"documents-remove"
argument_list|,
name|imagefile
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

