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
file|"libgimpbase/gimpbase.h"
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
file|"config/gimpguiconfig.h"
end_include

begin_include
include|#
directive|include
file|"core/gimp.h"
end_include

begin_include
include|#
directive|include
file|"core/gimpcontainer.h"
end_include

begin_include
include|#
directive|include
file|"core/gimpimage.h"
end_include

begin_include
include|#
directive|include
file|"file/file-utils.h"
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
file|"file-actions.h"
end_include

begin_include
include|#
directive|include
file|"file-commands.h"
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
name|file_actions_last_opened_update
parameter_list|(
name|GimpContainer
modifier|*
name|container
parameter_list|,
name|GimpImagefile
modifier|*
name|unused
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
name|file_actions_last_opened_reorder
parameter_list|(
name|GimpContainer
modifier|*
name|container
parameter_list|,
name|GimpImagefile
modifier|*
name|unused1
parameter_list|,
name|gint
name|unused2
parameter_list|,
name|GimpActionGroup
modifier|*
name|group
parameter_list|)
function_decl|;
end_function_decl

begin_decl_stmt
DECL|variable|file_actions
specifier|static
name|GimpActionEntry
name|file_actions
index|[]
init|=
block|{
block|{
literal|"file-menu"
block|,
name|NULL
block|,
name|N_
argument_list|(
literal|"_File"
argument_list|)
block|}
block|,
block|{
literal|"file-open-recent-menu"
block|,
name|NULL
block|,
name|N_
argument_list|(
literal|"Open _Recent"
argument_list|)
block|}
block|,
block|{
literal|"file-acquire-menu"
block|,
name|NULL
block|,
name|N_
argument_list|(
literal|"_Acquire"
argument_list|)
block|}
block|,
block|{
literal|"file-new"
block|,
name|GTK_STOCK_NEW
block|,
name|N_
argument_list|(
literal|"_New..."
argument_list|)
block|,
literal|"<control>N"
block|,
name|NULL
block|,
name|G_CALLBACK
argument_list|(
name|file_new_cmd_callback
argument_list|)
block|,
name|GIMP_HELP_FILE_NEW
block|}
block|,
block|{
literal|"file-open"
block|,
name|GTK_STOCK_OPEN
block|,
name|N_
argument_list|(
literal|"_Open..."
argument_list|)
block|,
literal|"<control>O"
block|,
name|NULL
block|,
name|G_CALLBACK
argument_list|(
name|file_open_cmd_callback
argument_list|)
block|,
name|GIMP_HELP_FILE_OPEN
block|}
block|,
block|{
literal|"file-save"
block|,
name|GTK_STOCK_SAVE
block|,
name|N_
argument_list|(
literal|"_Save"
argument_list|)
block|,
literal|"<control>S"
block|,
name|NULL
block|,
name|G_CALLBACK
argument_list|(
name|file_save_cmd_callback
argument_list|)
block|,
name|GIMP_HELP_FILE_SAVE
block|}
block|,
block|{
literal|"file-save-as"
block|,
name|GTK_STOCK_SAVE_AS
block|,
name|N_
argument_list|(
literal|"Save _as..."
argument_list|)
block|,
literal|"<control><shift>S"
block|,
name|NULL
block|,
name|G_CALLBACK
argument_list|(
name|file_save_as_cmd_callback
argument_list|)
block|,
name|GIMP_HELP_FILE_SAVE_AS
block|}
block|,
block|{
literal|"file-save-a-copy"
block|,
name|NULL
block|,
name|N_
argument_list|(
literal|"Save a Cop_y..."
argument_list|)
block|,
name|NULL
block|,
name|NULL
block|,
name|G_CALLBACK
argument_list|(
name|file_save_a_copy_cmd_callback
argument_list|)
block|,
name|GIMP_HELP_FILE_SAVE_A_COPY
block|}
block|,
block|{
literal|"file-save-as-template"
block|,
name|NULL
block|,
name|N_
argument_list|(
literal|"Save as _Template..."
argument_list|)
block|,
name|NULL
block|,
name|NULL
block|,
name|G_CALLBACK
argument_list|(
name|file_save_template_cmd_callback
argument_list|)
block|,
name|GIMP_HELP_FILE_SAVE_AS_TEMPLATE
block|}
block|,
block|{
literal|"file-revert"
block|,
name|GTK_STOCK_REVERT_TO_SAVED
block|,
name|N_
argument_list|(
literal|"Re_vert"
argument_list|)
block|,
name|NULL
block|,
name|NULL
block|,
name|G_CALLBACK
argument_list|(
name|file_revert_cmd_callback
argument_list|)
block|,
name|GIMP_HELP_FILE_REVERT
block|}
block|,
block|{
literal|"file-close"
block|,
name|GTK_STOCK_CLOSE
block|,
name|N_
argument_list|(
literal|"_Close"
argument_list|)
block|,
literal|"<control>W"
block|,
name|NULL
block|,
name|G_CALLBACK
argument_list|(
name|file_close_cmd_callback
argument_list|)
block|,
name|GIMP_HELP_FILE_CLOSE
block|}
block|,
block|{
literal|"file-quit"
block|,
name|GTK_STOCK_QUIT
block|,
name|N_
argument_list|(
literal|"_Quit"
argument_list|)
block|,
literal|"<control>Q"
block|,
name|NULL
block|,
name|G_CALLBACK
argument_list|(
name|file_quit_cmd_callback
argument_list|)
block|,
name|GIMP_HELP_FILE_QUIT
block|}
block|}
decl_stmt|;
end_decl_stmt

begin_function
name|void
DECL|function|file_actions_setup (GimpActionGroup * group)
name|file_actions_setup
parameter_list|(
name|GimpActionGroup
modifier|*
name|group
parameter_list|)
block|{
name|GimpEnumActionEntry
modifier|*
name|entries
decl_stmt|;
name|gint
name|n_entries
decl_stmt|;
name|gint
name|i
decl_stmt|;
name|gimp_action_group_add_actions
argument_list|(
name|group
argument_list|,
name|file_actions
argument_list|,
name|G_N_ELEMENTS
argument_list|(
name|file_actions
argument_list|)
argument_list|)
expr_stmt|;
name|n_entries
operator|=
name|GIMP_GUI_CONFIG
argument_list|(
name|group
operator|->
name|gimp
operator|->
name|config
argument_list|)
operator|->
name|last_opened_size
expr_stmt|;
name|entries
operator|=
name|g_new0
argument_list|(
name|GimpEnumActionEntry
argument_list|,
name|n_entries
argument_list|)
expr_stmt|;
for|for
control|(
name|i
operator|=
literal|0
init|;
name|i
operator|<
name|n_entries
condition|;
name|i
operator|++
control|)
block|{
name|entries
index|[
name|i
index|]
operator|.
name|name
operator|=
name|g_strdup_printf
argument_list|(
literal|"file-open-recent-%02d"
argument_list|,
name|i
operator|+
literal|1
argument_list|)
expr_stmt|;
name|entries
index|[
name|i
index|]
operator|.
name|stock_id
operator|=
name|GTK_STOCK_OPEN
expr_stmt|;
name|entries
index|[
name|i
index|]
operator|.
name|label
operator|=
name|NULL
expr_stmt|;
name|entries
index|[
name|i
index|]
operator|.
name|tooltip
operator|=
name|NULL
expr_stmt|;
name|entries
index|[
name|i
index|]
operator|.
name|value
operator|=
name|i
expr_stmt|;
name|entries
index|[
name|i
index|]
operator|.
name|help_id
operator|=
name|GIMP_HELP_FILE_OPEN_RECENT
expr_stmt|;
if|if
condition|(
name|i
operator|<
literal|9
condition|)
name|entries
index|[
name|i
index|]
operator|.
name|accelerator
operator|=
name|g_strdup_printf
argument_list|(
literal|"<control>%d"
argument_list|,
name|i
operator|+
literal|1
argument_list|)
expr_stmt|;
elseif|else
if|if
condition|(
name|i
operator|==
literal|9
condition|)
name|entries
index|[
name|i
index|]
operator|.
name|accelerator
operator|=
literal|"<control>0"
expr_stmt|;
else|else
name|entries
index|[
name|i
index|]
operator|.
name|accelerator
operator|=
literal|""
expr_stmt|;
block|}
name|gimp_action_group_add_enum_actions
argument_list|(
name|group
argument_list|,
name|entries
argument_list|,
name|n_entries
argument_list|,
name|G_CALLBACK
argument_list|(
name|file_last_opened_cmd_callback
argument_list|)
argument_list|)
expr_stmt|;
for|for
control|(
name|i
operator|=
literal|0
init|;
name|i
operator|<
name|n_entries
condition|;
name|i
operator|++
control|)
block|{
name|gimp_action_group_set_action_visible
argument_list|(
name|group
argument_list|,
name|entries
index|[
name|i
index|]
operator|.
name|name
argument_list|,
name|FALSE
argument_list|)
expr_stmt|;
name|g_free
argument_list|(
operator|(
name|gchar
operator|*
operator|)
name|entries
index|[
name|i
index|]
operator|.
name|name
argument_list|)
expr_stmt|;
if|if
condition|(
name|i
operator|<
literal|9
condition|)
name|g_free
argument_list|(
operator|(
name|gchar
operator|*
operator|)
name|entries
index|[
name|i
index|]
operator|.
name|accelerator
argument_list|)
expr_stmt|;
block|}
name|g_free
argument_list|(
name|entries
argument_list|)
expr_stmt|;
name|g_signal_connect_object
argument_list|(
name|group
operator|->
name|gimp
operator|->
name|documents
argument_list|,
literal|"add"
argument_list|,
name|G_CALLBACK
argument_list|(
name|file_actions_last_opened_update
argument_list|)
argument_list|,
name|group
argument_list|,
literal|0
argument_list|)
expr_stmt|;
name|g_signal_connect_object
argument_list|(
name|group
operator|->
name|gimp
operator|->
name|documents
argument_list|,
literal|"remove"
argument_list|,
name|G_CALLBACK
argument_list|(
name|file_actions_last_opened_update
argument_list|)
argument_list|,
name|group
argument_list|,
literal|0
argument_list|)
expr_stmt|;
name|g_signal_connect_object
argument_list|(
name|group
operator|->
name|gimp
operator|->
name|documents
argument_list|,
literal|"reorder"
argument_list|,
name|G_CALLBACK
argument_list|(
name|file_actions_last_opened_reorder
argument_list|)
argument_list|,
name|group
argument_list|,
literal|0
argument_list|)
expr_stmt|;
name|file_actions_last_opened_update
argument_list|(
name|group
operator|->
name|gimp
operator|->
name|documents
argument_list|,
name|NULL
argument_list|,
name|group
argument_list|)
expr_stmt|;
block|}
end_function

begin_function
name|void
DECL|function|file_actions_update (GimpActionGroup * group,gpointer data)
name|file_actions_update
parameter_list|(
name|GimpActionGroup
modifier|*
name|group
parameter_list|,
name|gpointer
name|data
parameter_list|)
block|{
name|GimpDisplay
modifier|*
name|gdisp
init|=
name|NULL
decl_stmt|;
name|GimpDisplayShell
modifier|*
name|shell
init|=
name|NULL
decl_stmt|;
name|GimpImage
modifier|*
name|gimage
init|=
name|NULL
decl_stmt|;
name|GimpDrawable
modifier|*
name|drawable
init|=
name|NULL
decl_stmt|;
if|if
condition|(
name|GIMP_IS_DISPLAY_SHELL
argument_list|(
name|data
argument_list|)
condition|)
block|{
name|shell
operator|=
name|GIMP_DISPLAY_SHELL
argument_list|(
name|data
argument_list|)
expr_stmt|;
name|gdisp
operator|=
name|shell
operator|->
name|gdisp
expr_stmt|;
block|}
elseif|else
if|if
condition|(
name|GIMP_IS_DISPLAY
argument_list|(
name|data
argument_list|)
condition|)
block|{
name|gdisp
operator|=
name|GIMP_DISPLAY
argument_list|(
name|data
argument_list|)
expr_stmt|;
name|shell
operator|=
name|GIMP_DISPLAY_SHELL
argument_list|(
name|gdisp
operator|->
name|shell
argument_list|)
expr_stmt|;
block|}
if|if
condition|(
name|gdisp
condition|)
block|{
name|gimage
operator|=
name|gdisp
operator|->
name|gimage
expr_stmt|;
name|drawable
operator|=
name|gimp_image_active_drawable
argument_list|(
name|gimage
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
literal|"file-save"
argument_list|,
name|gdisp
operator|&&
name|drawable
argument_list|)
expr_stmt|;
name|SET_SENSITIVE
argument_list|(
literal|"file-save-as"
argument_list|,
name|gdisp
operator|&&
name|drawable
argument_list|)
expr_stmt|;
name|SET_SENSITIVE
argument_list|(
literal|"file-save-a-copy"
argument_list|,
name|gdisp
operator|&&
name|drawable
argument_list|)
expr_stmt|;
name|SET_SENSITIVE
argument_list|(
literal|"file-save-as-template"
argument_list|,
name|gdisp
argument_list|)
expr_stmt|;
name|SET_SENSITIVE
argument_list|(
literal|"file-revert"
argument_list|,
name|gdisp
operator|&&
name|GIMP_OBJECT
argument_list|(
name|gimage
argument_list|)
operator|->
name|name
argument_list|)
expr_stmt|;
name|SET_SENSITIVE
argument_list|(
literal|"file-close"
argument_list|,
name|gdisp
argument_list|)
expr_stmt|;
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
DECL|function|file_actions_last_opened_update (GimpContainer * container,GimpImagefile * unused,GimpActionGroup * group)
name|file_actions_last_opened_update
parameter_list|(
name|GimpContainer
modifier|*
name|container
parameter_list|,
name|GimpImagefile
modifier|*
name|unused
parameter_list|,
name|GimpActionGroup
modifier|*
name|group
parameter_list|)
block|{
name|gint
name|num_documents
decl_stmt|;
name|gint
name|i
decl_stmt|;
name|gint
name|n
init|=
name|GIMP_GUI_CONFIG
argument_list|(
name|group
operator|->
name|gimp
operator|->
name|config
argument_list|)
operator|->
name|last_opened_size
decl_stmt|;
name|num_documents
operator|=
name|gimp_container_num_children
argument_list|(
name|container
argument_list|)
expr_stmt|;
for|for
control|(
name|i
operator|=
literal|0
init|;
name|i
operator|<
name|n
condition|;
name|i
operator|++
control|)
block|{
name|GtkAction
modifier|*
name|action
decl_stmt|;
name|gchar
modifier|*
name|name
init|=
name|g_strdup_printf
argument_list|(
literal|"file-open-recent-%02d"
argument_list|,
name|i
operator|+
literal|1
argument_list|)
decl_stmt|;
name|action
operator|=
name|gtk_action_group_get_action
argument_list|(
name|GTK_ACTION_GROUP
argument_list|(
name|group
argument_list|)
argument_list|,
name|name
argument_list|)
expr_stmt|;
if|if
condition|(
name|i
operator|<
name|num_documents
condition|)
block|{
name|GimpImagefile
modifier|*
name|imagefile
init|=
operator|(
name|GimpImagefile
operator|*
operator|)
name|gimp_container_get_child_by_index
argument_list|(
name|container
argument_list|,
name|i
argument_list|)
decl_stmt|;
if|if
condition|(
name|g_object_get_data
argument_list|(
name|G_OBJECT
argument_list|(
name|action
argument_list|)
argument_list|,
literal|"gimp-imagefile"
argument_list|)
operator|!=
operator|(
name|gpointer
operator|)
name|imagefile
condition|)
block|{
specifier|const
name|gchar
modifier|*
name|uri
decl_stmt|;
name|gchar
modifier|*
name|filename
decl_stmt|;
name|gchar
modifier|*
name|basename
decl_stmt|;
name|gchar
modifier|*
name|escaped
decl_stmt|;
name|uri
operator|=
name|gimp_object_get_name
argument_list|(
name|GIMP_OBJECT
argument_list|(
name|imagefile
argument_list|)
argument_list|)
expr_stmt|;
name|filename
operator|=
name|file_utils_uri_to_utf8_filename
argument_list|(
name|uri
argument_list|)
expr_stmt|;
name|basename
operator|=
name|file_utils_uri_to_utf8_basename
argument_list|(
name|uri
argument_list|)
expr_stmt|;
name|escaped
operator|=
name|gimp_escape_uline
argument_list|(
name|basename
argument_list|)
expr_stmt|;
name|g_free
argument_list|(
name|basename
argument_list|)
expr_stmt|;
name|g_object_set
argument_list|(
name|G_OBJECT
argument_list|(
name|action
argument_list|)
argument_list|,
literal|"label"
argument_list|,
name|escaped
argument_list|,
literal|"tooltip"
argument_list|,
name|filename
argument_list|,
literal|"visible"
argument_list|,
name|TRUE
argument_list|,
name|NULL
argument_list|)
expr_stmt|;
name|g_free
argument_list|(
name|filename
argument_list|)
expr_stmt|;
name|g_free
argument_list|(
name|escaped
argument_list|)
expr_stmt|;
name|g_object_set_data
argument_list|(
name|G_OBJECT
argument_list|(
name|action
argument_list|)
argument_list|,
literal|"gimp-imagefile"
argument_list|,
name|imagefile
argument_list|)
expr_stmt|;
block|}
block|}
else|else
block|{
name|g_object_set_data
argument_list|(
name|G_OBJECT
argument_list|(
name|action
argument_list|)
argument_list|,
literal|"gimp-imagefile"
argument_list|,
name|NULL
argument_list|)
expr_stmt|;
name|g_object_set
argument_list|(
name|G_OBJECT
argument_list|(
name|action
argument_list|)
argument_list|,
literal|"visible"
argument_list|,
name|FALSE
argument_list|,
name|NULL
argument_list|)
expr_stmt|;
block|}
name|g_free
argument_list|(
name|name
argument_list|)
expr_stmt|;
block|}
block|}
end_function

begin_function
specifier|static
name|void
DECL|function|file_actions_last_opened_reorder (GimpContainer * container,GimpImagefile * unused1,gint unused2,GimpActionGroup * group)
name|file_actions_last_opened_reorder
parameter_list|(
name|GimpContainer
modifier|*
name|container
parameter_list|,
name|GimpImagefile
modifier|*
name|unused1
parameter_list|,
name|gint
name|unused2
parameter_list|,
name|GimpActionGroup
modifier|*
name|group
parameter_list|)
block|{
name|file_actions_last_opened_update
argument_list|(
name|container
argument_list|,
name|unused1
argument_list|,
name|group
argument_list|)
expr_stmt|;
block|}
end_function

end_unit

