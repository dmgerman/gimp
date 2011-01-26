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
file|"core/gimpviewable.h"
end_include

begin_include
include|#
directive|include
file|"file/file-utils.h"
end_include

begin_include
include|#
directive|include
file|"file/gimp-file.h"
end_include

begin_include
include|#
directive|include
file|"plug-in/gimppluginmanager-file.h"
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
file|"display/gimpdisplay.h"
end_include

begin_include
include|#
directive|include
file|"actions.h"
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

begin_function_decl
specifier|static
name|void
name|file_actions_close_all_update
parameter_list|(
name|GimpContainer
modifier|*
name|images
parameter_list|,
name|GimpObject
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
name|gchar
modifier|*
name|file_actions_create_label
parameter_list|(
specifier|const
name|gchar
modifier|*
name|format
parameter_list|,
specifier|const
name|gchar
modifier|*
name|uri
parameter_list|)
function_decl|;
end_function_decl

begin_decl_stmt
DECL|variable|file_actions
specifier|static
specifier|const
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
name|NC_
argument_list|(
literal|"file-action"
argument_list|,
literal|"_File"
argument_list|)
block|}
block|,
block|{
literal|"file-create-menu"
block|,
name|NULL
block|,
name|NC_
argument_list|(
literal|"file-action"
argument_list|,
literal|"Crea_te"
argument_list|)
block|}
block|,
block|{
literal|"file-open-recent-menu"
block|,
name|NULL
block|,
name|NC_
argument_list|(
literal|"file-action"
argument_list|,
literal|"Open _Recent"
argument_list|)
block|}
block|,
block|{
literal|"file-open"
block|,
name|GTK_STOCK_OPEN
block|,
name|NC_
argument_list|(
literal|"file-action"
argument_list|,
literal|"_Open..."
argument_list|)
block|,
name|NULL
block|,
name|NC_
argument_list|(
literal|"file-action"
argument_list|,
literal|"Open an image file"
argument_list|)
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
literal|"file-open-as-layers"
block|,
name|GIMP_STOCK_LAYER
block|,
name|NC_
argument_list|(
literal|"file-action"
argument_list|,
literal|"Op_en as Layers..."
argument_list|)
block|,
literal|"<control><alt>O"
block|,
name|NC_
argument_list|(
literal|"file-action"
argument_list|,
literal|"Open an image file as layers"
argument_list|)
block|,
name|G_CALLBACK
argument_list|(
name|file_open_as_layers_cmd_callback
argument_list|)
block|,
name|GIMP_HELP_FILE_OPEN_AS_LAYER
block|}
block|,
block|{
literal|"file-open-location"
block|,
name|GIMP_STOCK_WEB
block|,
name|NC_
argument_list|(
literal|"file-action"
argument_list|,
literal|"Open _Location..."
argument_list|)
block|,
name|NULL
block|,
name|NC_
argument_list|(
literal|"file-action"
argument_list|,
literal|"Open an image file from a specified location"
argument_list|)
block|,
name|G_CALLBACK
argument_list|(
name|file_open_location_cmd_callback
argument_list|)
block|,
name|GIMP_HELP_FILE_OPEN_LOCATION
block|}
block|,
block|{
literal|"file-create-template"
block|,
name|NULL
block|,
name|NC_
argument_list|(
literal|"file-action"
argument_list|,
literal|"Create Template..."
argument_list|)
block|,
name|NULL
block|,
name|NC_
argument_list|(
literal|"file-action"
argument_list|,
literal|"Create a new template from this image"
argument_list|)
block|,
name|G_CALLBACK
argument_list|(
name|file_create_template_cmd_callback
argument_list|)
block|,
name|GIMP_HELP_FILE_CREATE_TEMPLATE
block|}
block|,
block|{
literal|"file-revert"
block|,
name|GTK_STOCK_REVERT_TO_SAVED
block|,
name|NC_
argument_list|(
literal|"file-action"
argument_list|,
literal|"Re_vert"
argument_list|)
block|,
name|NULL
block|,
name|NC_
argument_list|(
literal|"file-action"
argument_list|,
literal|"Reload the image file from disk"
argument_list|)
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
literal|"file-close-all"
block|,
name|GTK_STOCK_CLOSE
block|,
name|NC_
argument_list|(
literal|"file-action"
argument_list|,
literal|"Close all"
argument_list|)
block|,
literal|"<shift><control>W"
block|,
name|NC_
argument_list|(
literal|"file-action"
argument_list|,
literal|"Close all opened images"
argument_list|)
block|,
name|G_CALLBACK
argument_list|(
name|file_close_all_cmd_callback
argument_list|)
block|,
name|GIMP_HELP_FILE_CLOSE_ALL
block|}
block|,
block|{
literal|"file-quit"
block|,
name|GTK_STOCK_QUIT
block|,
name|NC_
argument_list|(
literal|"file-action"
argument_list|,
literal|"_Quit"
argument_list|)
block|,
literal|"<control>Q"
block|,
name|NC_
argument_list|(
literal|"file-action"
argument_list|,
literal|"Quit the GNU Image Manipulation Program"
argument_list|)
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

begin_decl_stmt
DECL|variable|file_save_actions
specifier|static
specifier|const
name|GimpEnumActionEntry
name|file_save_actions
index|[]
init|=
block|{
block|{
literal|"file-save"
block|,
name|GTK_STOCK_SAVE
block|,
name|NC_
argument_list|(
literal|"file-action"
argument_list|,
literal|"_Save"
argument_list|)
block|,
literal|"<control>S"
block|,
name|NC_
argument_list|(
literal|"file-action"
argument_list|,
literal|"Save this image"
argument_list|)
block|,
name|GIMP_SAVE_MODE_SAVE
block|,
name|FALSE
block|,
name|GIMP_HELP_FILE_SAVE
block|}
block|,
block|{
literal|"file-save-as"
block|,
name|GTK_STOCK_SAVE_AS
block|,
name|NC_
argument_list|(
literal|"file-action"
argument_list|,
literal|"Save _As..."
argument_list|)
block|,
literal|"<control><shift>S"
block|,
name|NC_
argument_list|(
literal|"file-action"
argument_list|,
literal|"Save this image with a different name"
argument_list|)
block|,
name|GIMP_SAVE_MODE_SAVE_AS
block|,
name|FALSE
block|,
name|GIMP_HELP_FILE_SAVE_AS
block|}
block|,
block|{
literal|"file-save-a-copy"
block|,
name|NULL
block|,
name|NC_
argument_list|(
literal|"file-action"
argument_list|,
literal|"Save a Cop_y..."
argument_list|)
block|,
name|NULL
block|,
name|NC_
argument_list|(
literal|"file-action"
argument_list|,
literal|"Save a copy of this image, without affecting the source file (if any) or the current state of the image"
argument_list|)
block|,
name|GIMP_SAVE_MODE_SAVE_A_COPY
block|,
name|FALSE
block|,
name|GIMP_HELP_FILE_SAVE_A_COPY
block|}
block|,
block|{
literal|"file-save-and-close"
block|,
name|NULL
block|,
name|NC_
argument_list|(
literal|"file-action"
argument_list|,
literal|"Save and Close..."
argument_list|)
block|,
name|NULL
block|,
name|NC_
argument_list|(
literal|"file-action"
argument_list|,
literal|"Save this image and close its window"
argument_list|)
block|,
name|GIMP_SAVE_MODE_SAVE_AND_CLOSE
block|,
name|FALSE
block|,
name|GIMP_HELP_FILE_SAVE
block|}
block|,
block|{
literal|"file-export-to"
block|,
name|NULL
block|,
name|NC_
argument_list|(
literal|"file-action"
argument_list|,
literal|"Export to"
argument_list|)
block|,
literal|"<control>E"
block|,
name|NC_
argument_list|(
literal|"file-action"
argument_list|,
literal|"Export the image again"
argument_list|)
block|,
name|GIMP_SAVE_MODE_EXPORT_TO
block|,
name|FALSE
block|,
name|GIMP_HELP_FILE_EXPORT_TO
block|}
block|,
block|{
literal|"file-overwrite"
block|,
name|NULL
block|,
name|NC_
argument_list|(
literal|"file-action"
argument_list|,
literal|"Overwrite"
argument_list|)
block|,
literal|""
block|,
name|NC_
argument_list|(
literal|"file-action"
argument_list|,
literal|"Export the image back to the imported file in the import format"
argument_list|)
block|,
name|GIMP_SAVE_MODE_EXPORT_TO
block|,
name|FALSE
block|,
name|GIMP_HELP_FILE_OVERWRITE
block|}
block|,
block|{
literal|"file-export"
block|,
name|NULL
block|,
name|NC_
argument_list|(
literal|"file-action"
argument_list|,
literal|"Export..."
argument_list|)
block|,
literal|"<control><shift>E"
block|,
name|NC_
argument_list|(
literal|"file-action"
argument_list|,
literal|"Export the image to various file formats such as PNG or JPEG"
argument_list|)
block|,
name|GIMP_SAVE_MODE_EXPORT
block|,
name|FALSE
block|,
name|GIMP_HELP_FILE_EXPORT
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
literal|"file-action"
argument_list|,
name|file_actions
argument_list|,
name|G_N_ELEMENTS
argument_list|(
name|file_actions
argument_list|)
argument_list|)
expr_stmt|;
name|gimp_action_group_add_enum_actions
argument_list|(
name|group
argument_list|,
literal|"file-action"
argument_list|,
name|file_save_actions
argument_list|,
name|G_N_ELEMENTS
argument_list|(
name|file_save_actions
argument_list|)
argument_list|,
name|G_CALLBACK
argument_list|(
name|file_save_cmd_callback
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
name|entries
index|[
name|i
index|]
operator|.
name|name
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
name|value_variable
operator|=
name|FALSE
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
name|NULL
argument_list|,
name|entries
argument_list|,
name|n_entries
argument_list|,
name|G_CALLBACK
argument_list|(
name|file_open_recent_cmd_callback
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
name|GtkAction
modifier|*
name|action
decl_stmt|;
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
name|action
operator|=
name|gtk_action_group_get_action
argument_list|(
name|GTK_ACTION_GROUP
argument_list|(
name|group
argument_list|)
argument_list|,
name|entries
index|[
name|i
index|]
operator|.
name|name
argument_list|)
expr_stmt|;
name|g_object_set
argument_list|(
name|action
argument_list|,
literal|"context"
argument_list|,
name|gimp_get_user_context
argument_list|(
name|group
operator|->
name|gimp
argument_list|)
argument_list|,
name|NULL
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
comment|/*  also listen to image adding/removal so we catch the case where    *  the last image is closed but its display stays open.    */
name|g_signal_connect_object
argument_list|(
name|group
operator|->
name|gimp
operator|->
name|images
argument_list|,
literal|"add"
argument_list|,
name|G_CALLBACK
argument_list|(
name|file_actions_close_all_update
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
name|images
argument_list|,
literal|"remove"
argument_list|,
name|G_CALLBACK
argument_list|(
name|file_actions_close_all_update
argument_list|)
argument_list|,
name|group
argument_list|,
literal|0
argument_list|)
expr_stmt|;
name|file_actions_close_all_update
argument_list|(
name|group
operator|->
name|gimp
operator|->
name|displays
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
name|Gimp
modifier|*
name|gimp
init|=
name|action_data_get_gimp
argument_list|(
name|data
argument_list|)
decl_stmt|;
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
specifier|const
name|gchar
modifier|*
name|source
init|=
name|NULL
decl_stmt|;
specifier|const
name|gchar
modifier|*
name|export_to
init|=
name|NULL
decl_stmt|;
name|gboolean
name|show_overwrite
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
name|source
operator|=
name|g_object_get_data
argument_list|(
name|G_OBJECT
argument_list|(
name|image
argument_list|)
argument_list|,
name|GIMP_FILE_IMPORT_SOURCE_URI_KEY
argument_list|)
expr_stmt|;
name|export_to
operator|=
name|g_object_get_data
argument_list|(
name|G_OBJECT
argument_list|(
name|image
argument_list|)
argument_list|,
name|GIMP_FILE_EXPORT_TO_URI_KEY
argument_list|)
expr_stmt|;
block|}
name|show_overwrite
operator|=
operator|(
name|source
operator|&&
name|gimp_plug_in_manager_uri_has_exporter
argument_list|(
name|gimp
operator|->
name|plug_in_manager
argument_list|,
name|source
argument_list|)
operator|)
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
name|SET_SENSITIVE
argument_list|(
literal|"file-save"
argument_list|,
name|image
operator|&&
name|drawable
argument_list|)
expr_stmt|;
name|SET_SENSITIVE
argument_list|(
literal|"file-save-as"
argument_list|,
name|image
operator|&&
name|drawable
argument_list|)
expr_stmt|;
name|SET_SENSITIVE
argument_list|(
literal|"file-save-a-copy"
argument_list|,
name|image
operator|&&
name|drawable
argument_list|)
expr_stmt|;
name|SET_SENSITIVE
argument_list|(
literal|"file-revert"
argument_list|,
name|image
operator|&&
operator|(
name|gimp_image_get_uri
argument_list|(
name|image
argument_list|)
operator|||
name|source
operator|)
argument_list|)
expr_stmt|;
name|SET_SENSITIVE
argument_list|(
literal|"file-export-to"
argument_list|,
name|export_to
argument_list|)
expr_stmt|;
name|SET_VISIBLE
argument_list|(
literal|"file-export-to"
argument_list|,
name|export_to
operator|||
operator|!
name|show_overwrite
argument_list|)
expr_stmt|;
name|SET_SENSITIVE
argument_list|(
literal|"file-overwrite"
argument_list|,
name|show_overwrite
argument_list|)
expr_stmt|;
name|SET_VISIBLE
argument_list|(
literal|"file-overwrite"
argument_list|,
name|show_overwrite
argument_list|)
expr_stmt|;
name|SET_SENSITIVE
argument_list|(
literal|"file-export"
argument_list|,
name|image
operator|&&
name|drawable
argument_list|)
expr_stmt|;
name|SET_SENSITIVE
argument_list|(
literal|"file-create-template"
argument_list|,
name|image
argument_list|)
expr_stmt|;
if|if
condition|(
name|export_to
condition|)
block|{
name|gchar
modifier|*
name|label
init|=
name|file_actions_create_label
argument_list|(
name|_
argument_list|(
literal|"Export to %s"
argument_list|)
argument_list|,
name|export_to
argument_list|)
decl_stmt|;
name|gimp_action_group_set_action_label
argument_list|(
name|group
argument_list|,
literal|"file-export-to"
argument_list|,
name|label
argument_list|)
expr_stmt|;
name|g_free
argument_list|(
name|label
argument_list|)
expr_stmt|;
block|}
elseif|else
if|if
condition|(
name|show_overwrite
condition|)
block|{
name|gchar
modifier|*
name|label
init|=
name|file_actions_create_label
argument_list|(
name|_
argument_list|(
literal|"Overwrite %s"
argument_list|)
argument_list|,
name|source
argument_list|)
decl_stmt|;
name|gimp_action_group_set_action_label
argument_list|(
name|group
argument_list|,
literal|"file-overwrite"
argument_list|,
name|label
argument_list|)
expr_stmt|;
name|g_free
argument_list|(
name|label
argument_list|)
expr_stmt|;
block|}
else|else
block|{
name|gimp_action_group_set_action_label
argument_list|(
name|group
argument_list|,
literal|"file-export-to"
argument_list|,
name|_
argument_list|(
literal|"Export to"
argument_list|)
argument_list|)
expr_stmt|;
block|}
comment|/*  needed for the empty display  */
name|SET_SENSITIVE
argument_list|(
literal|"file-close-all"
argument_list|,
name|image
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
name|gimp_container_get_n_children
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
name|GIMP_ACTION
argument_list|(
name|action
argument_list|)
operator|->
name|viewable
operator|!=
operator|(
name|GimpViewable
operator|*
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
name|imagefile
argument_list|)
expr_stmt|;
name|filename
operator|=
name|file_utils_uri_display_name
argument_list|(
name|uri
argument_list|)
expr_stmt|;
name|basename
operator|=
name|file_utils_uri_display_basename
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
name|action
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
literal|"viewable"
argument_list|,
name|imagefile
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
block|}
block|}
else|else
block|{
name|g_object_set
argument_list|(
name|action
argument_list|,
literal|"label"
argument_list|,
name|name
argument_list|,
literal|"tooltip"
argument_list|,
name|NULL
argument_list|,
literal|"visible"
argument_list|,
name|FALSE
argument_list|,
literal|"viewable"
argument_list|,
name|NULL
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

begin_function
specifier|static
name|void
DECL|function|file_actions_close_all_update (GimpContainer * images,GimpObject * unused,GimpActionGroup * group)
name|file_actions_close_all_update
parameter_list|(
name|GimpContainer
modifier|*
name|images
parameter_list|,
name|GimpObject
modifier|*
name|unused
parameter_list|,
name|GimpActionGroup
modifier|*
name|group
parameter_list|)
block|{
name|GimpContainer
modifier|*
name|container
init|=
name|group
operator|->
name|gimp
operator|->
name|displays
decl_stmt|;
name|gint
name|n_displays
init|=
name|gimp_container_get_n_children
argument_list|(
name|container
argument_list|)
decl_stmt|;
name|gboolean
name|sensitive
init|=
operator|(
name|n_displays
operator|>
literal|0
operator|)
decl_stmt|;
if|if
condition|(
name|n_displays
operator|==
literal|1
condition|)
block|{
name|GimpDisplay
modifier|*
name|display
decl_stmt|;
name|display
operator|=
name|GIMP_DISPLAY
argument_list|(
name|gimp_container_get_first_child
argument_list|(
name|container
argument_list|)
argument_list|)
expr_stmt|;
if|if
condition|(
operator|!
name|gimp_display_get_image
argument_list|(
name|display
argument_list|)
condition|)
name|sensitive
operator|=
name|FALSE
expr_stmt|;
block|}
name|gimp_action_group_set_action_sensitive
argument_list|(
name|group
argument_list|,
literal|"file-close-all"
argument_list|,
name|sensitive
argument_list|)
expr_stmt|;
block|}
end_function

begin_function
specifier|static
name|gchar
modifier|*
DECL|function|file_actions_create_label (const gchar * format,const gchar * uri)
name|file_actions_create_label
parameter_list|(
specifier|const
name|gchar
modifier|*
name|format
parameter_list|,
specifier|const
name|gchar
modifier|*
name|uri
parameter_list|)
block|{
name|gchar
modifier|*
name|basename
init|=
name|file_utils_uri_display_basename
argument_list|(
name|uri
argument_list|)
decl_stmt|;
name|gchar
modifier|*
name|escaped_basename
init|=
name|gimp_escape_uline
argument_list|(
name|basename
argument_list|)
decl_stmt|;
name|gchar
modifier|*
name|label
init|=
name|g_strdup_printf
argument_list|(
name|format
argument_list|,
name|escaped_basename
argument_list|)
decl_stmt|;
name|g_free
argument_list|(
name|escaped_basename
argument_list|)
expr_stmt|;
name|g_free
argument_list|(
name|basename
argument_list|)
expr_stmt|;
return|return
name|label
return|;
block|}
end_function

end_unit

