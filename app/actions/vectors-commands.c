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
file|<string.h>
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
file|"core/gimp-utils.h"
end_include

begin_include
include|#
directive|include
file|"core/gimpchannel.h"
end_include

begin_include
include|#
directive|include
file|"core/gimpchannel-select.h"
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
file|"core/gimpimage-merge.h"
end_include

begin_include
include|#
directive|include
file|"core/gimpimage-undo.h"
end_include

begin_include
include|#
directive|include
file|"core/gimpitemundo.h"
end_include

begin_include
include|#
directive|include
file|"core/gimpparamspecs.h"
end_include

begin_include
include|#
directive|include
file|"core/gimpprogress.h"
end_include

begin_include
include|#
directive|include
file|"core/gimpstrokedesc.h"
end_include

begin_include
include|#
directive|include
file|"core/gimptoolinfo.h"
end_include

begin_include
include|#
directive|include
file|"pdb/gimppdb.h"
end_include

begin_include
include|#
directive|include
file|"pdb/gimpprocedure.h"
end_include

begin_include
include|#
directive|include
file|"vectors/gimpvectors.h"
end_include

begin_include
include|#
directive|include
file|"vectors/gimpvectors-export.h"
end_include

begin_include
include|#
directive|include
file|"vectors/gimpvectors-import.h"
end_include

begin_include
include|#
directive|include
file|"widgets/gimpaction.h"
end_include

begin_include
include|#
directive|include
file|"widgets/gimpclipboard.h"
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
file|"tools/gimpvectortool.h"
end_include

begin_include
include|#
directive|include
file|"tools/tool_manager.h"
end_include

begin_include
include|#
directive|include
file|"dialogs/stroke-dialog.h"
end_include

begin_include
include|#
directive|include
file|"dialogs/vectors-export-dialog.h"
end_include

begin_include
include|#
directive|include
file|"dialogs/vectors-import-dialog.h"
end_include

begin_include
include|#
directive|include
file|"dialogs/vectors-options-dialog.h"
end_include

begin_include
include|#
directive|include
file|"actions.h"
end_include

begin_include
include|#
directive|include
file|"vectors-commands.h"
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
name|vectors_new_vectors_response
parameter_list|(
name|GtkWidget
modifier|*
name|widget
parameter_list|,
name|gint
name|response_id
parameter_list|,
name|VectorsOptionsDialog
modifier|*
name|options
parameter_list|)
function_decl|;
end_function_decl

begin_function_decl
specifier|static
name|void
name|vectors_edit_vectors_response
parameter_list|(
name|GtkWidget
modifier|*
name|widget
parameter_list|,
name|gint
name|response_id
parameter_list|,
name|VectorsOptionsDialog
modifier|*
name|options
parameter_list|)
function_decl|;
end_function_decl

begin_function_decl
specifier|static
name|void
name|vectors_import_response
parameter_list|(
name|GtkWidget
modifier|*
name|widget
parameter_list|,
name|gint
name|response_id
parameter_list|,
name|VectorsImportDialog
modifier|*
name|dialog
parameter_list|)
function_decl|;
end_function_decl

begin_function_decl
specifier|static
name|void
name|vectors_export_response
parameter_list|(
name|GtkWidget
modifier|*
name|widget
parameter_list|,
name|gint
name|response_id
parameter_list|,
name|VectorsExportDialog
modifier|*
name|dialog
parameter_list|)
function_decl|;
end_function_decl

begin_comment
comment|/*  private variables  */
end_comment

begin_decl_stmt
DECL|variable|vectors_name
specifier|static
name|gchar
modifier|*
name|vectors_name
init|=
name|NULL
decl_stmt|;
end_decl_stmt

begin_decl_stmt
DECL|variable|vectors_import_merge
specifier|static
name|gboolean
name|vectors_import_merge
init|=
name|FALSE
decl_stmt|;
end_decl_stmt

begin_decl_stmt
DECL|variable|vectors_import_scale
specifier|static
name|gboolean
name|vectors_import_scale
init|=
name|FALSE
decl_stmt|;
end_decl_stmt

begin_decl_stmt
DECL|variable|vectors_export_active_only
specifier|static
name|gboolean
name|vectors_export_active_only
init|=
name|TRUE
decl_stmt|;
end_decl_stmt

begin_comment
comment|/*  public functions  */
end_comment

begin_function
name|void
DECL|function|vectors_vectors_tool_cmd_callback (GtkAction * action,gpointer data)
name|vectors_vectors_tool_cmd_callback
parameter_list|(
name|GtkAction
modifier|*
name|action
parameter_list|,
name|gpointer
name|data
parameter_list|)
block|{
name|GimpImage
modifier|*
name|image
decl_stmt|;
name|GimpVectors
modifier|*
name|vectors
decl_stmt|;
name|GimpTool
modifier|*
name|active_tool
decl_stmt|;
name|return_if_no_vectors
argument_list|(
name|image
argument_list|,
name|vectors
argument_list|,
name|data
argument_list|)
expr_stmt|;
name|active_tool
operator|=
name|tool_manager_get_active
argument_list|(
name|image
operator|->
name|gimp
argument_list|)
expr_stmt|;
if|if
condition|(
operator|!
name|GIMP_IS_VECTOR_TOOL
argument_list|(
name|active_tool
argument_list|)
condition|)
block|{
name|GimpToolInfo
modifier|*
name|tool_info
init|=
name|gimp_get_tool_info
argument_list|(
name|image
operator|->
name|gimp
argument_list|,
literal|"gimp-vector-tool"
argument_list|)
decl_stmt|;
if|if
condition|(
name|GIMP_IS_TOOL_INFO
argument_list|(
name|tool_info
argument_list|)
condition|)
block|{
name|gimp_context_set_tool
argument_list|(
name|action_data_get_context
argument_list|(
name|data
argument_list|)
argument_list|,
name|tool_info
argument_list|)
expr_stmt|;
name|active_tool
operator|=
name|tool_manager_get_active
argument_list|(
name|image
operator|->
name|gimp
argument_list|)
expr_stmt|;
block|}
block|}
if|if
condition|(
name|GIMP_IS_VECTOR_TOOL
argument_list|(
name|active_tool
argument_list|)
condition|)
name|gimp_vector_tool_set_vectors
argument_list|(
name|GIMP_VECTOR_TOOL
argument_list|(
name|active_tool
argument_list|)
argument_list|,
name|vectors
argument_list|)
expr_stmt|;
block|}
end_function

begin_function
name|void
DECL|function|vectors_edit_attributes_cmd_callback (GtkAction * action,gpointer data)
name|vectors_edit_attributes_cmd_callback
parameter_list|(
name|GtkAction
modifier|*
name|action
parameter_list|,
name|gpointer
name|data
parameter_list|)
block|{
name|VectorsOptionsDialog
modifier|*
name|options
decl_stmt|;
name|GimpImage
modifier|*
name|image
decl_stmt|;
name|GimpVectors
modifier|*
name|vectors
decl_stmt|;
name|GtkWidget
modifier|*
name|widget
decl_stmt|;
name|return_if_no_vectors
argument_list|(
name|image
argument_list|,
name|vectors
argument_list|,
name|data
argument_list|)
expr_stmt|;
name|return_if_no_widget
argument_list|(
name|widget
argument_list|,
name|data
argument_list|)
expr_stmt|;
name|options
operator|=
name|vectors_options_dialog_new
argument_list|(
name|image
argument_list|,
name|vectors
argument_list|,
name|action_data_get_context
argument_list|(
name|data
argument_list|)
argument_list|,
name|widget
argument_list|,
name|gimp_object_get_name
argument_list|(
name|GIMP_OBJECT
argument_list|(
name|vectors
argument_list|)
argument_list|)
argument_list|,
name|_
argument_list|(
literal|"Path Attributes"
argument_list|)
argument_list|,
literal|"gimp-vectors-edit"
argument_list|,
name|GTK_STOCK_EDIT
argument_list|,
name|_
argument_list|(
literal|"Edit Path Attributes"
argument_list|)
argument_list|,
name|GIMP_HELP_PATH_EDIT
argument_list|)
expr_stmt|;
name|g_signal_connect
argument_list|(
name|options
operator|->
name|dialog
argument_list|,
literal|"response"
argument_list|,
name|G_CALLBACK
argument_list|(
name|vectors_edit_vectors_response
argument_list|)
argument_list|,
name|options
argument_list|)
expr_stmt|;
name|gtk_widget_show
argument_list|(
name|options
operator|->
name|dialog
argument_list|)
expr_stmt|;
block|}
end_function

begin_function
name|void
DECL|function|vectors_new_cmd_callback (GtkAction * action,gpointer data)
name|vectors_new_cmd_callback
parameter_list|(
name|GtkAction
modifier|*
name|action
parameter_list|,
name|gpointer
name|data
parameter_list|)
block|{
name|VectorsOptionsDialog
modifier|*
name|options
decl_stmt|;
name|GimpImage
modifier|*
name|image
decl_stmt|;
name|GtkWidget
modifier|*
name|widget
decl_stmt|;
name|return_if_no_image
argument_list|(
name|image
argument_list|,
name|data
argument_list|)
expr_stmt|;
name|return_if_no_widget
argument_list|(
name|widget
argument_list|,
name|data
argument_list|)
expr_stmt|;
name|options
operator|=
name|vectors_options_dialog_new
argument_list|(
name|image
argument_list|,
name|NULL
argument_list|,
name|action_data_get_context
argument_list|(
name|data
argument_list|)
argument_list|,
name|widget
argument_list|,
name|vectors_name
condition|?
name|vectors_name
else|:
name|_
argument_list|(
literal|"New Path"
argument_list|)
argument_list|,
name|_
argument_list|(
literal|"New Path"
argument_list|)
argument_list|,
literal|"gimp-vectors-new"
argument_list|,
name|GIMP_STOCK_PATH
argument_list|,
name|_
argument_list|(
literal|"New Path Options"
argument_list|)
argument_list|,
name|GIMP_HELP_PATH_NEW
argument_list|)
expr_stmt|;
name|g_signal_connect
argument_list|(
name|options
operator|->
name|dialog
argument_list|,
literal|"response"
argument_list|,
name|G_CALLBACK
argument_list|(
name|vectors_new_vectors_response
argument_list|)
argument_list|,
name|options
argument_list|)
expr_stmt|;
name|gtk_widget_show
argument_list|(
name|options
operator|->
name|dialog
argument_list|)
expr_stmt|;
block|}
end_function

begin_function
name|void
DECL|function|vectors_new_last_vals_cmd_callback (GtkAction * action,gpointer data)
name|vectors_new_last_vals_cmd_callback
parameter_list|(
name|GtkAction
modifier|*
name|action
parameter_list|,
name|gpointer
name|data
parameter_list|)
block|{
name|GimpImage
modifier|*
name|image
decl_stmt|;
name|GimpVectors
modifier|*
name|new_vectors
decl_stmt|;
name|return_if_no_image
argument_list|(
name|image
argument_list|,
name|data
argument_list|)
expr_stmt|;
name|new_vectors
operator|=
name|gimp_vectors_new
argument_list|(
name|image
argument_list|,
name|vectors_name
condition|?
name|vectors_name
else|:
name|_
argument_list|(
literal|"New Path"
argument_list|)
argument_list|)
expr_stmt|;
name|gimp_image_add_vectors
argument_list|(
name|image
argument_list|,
name|new_vectors
argument_list|,
operator|-
literal|1
argument_list|)
expr_stmt|;
name|gimp_image_flush
argument_list|(
name|image
argument_list|)
expr_stmt|;
block|}
end_function

begin_function
name|void
DECL|function|vectors_raise_cmd_callback (GtkAction * action,gpointer data)
name|vectors_raise_cmd_callback
parameter_list|(
name|GtkAction
modifier|*
name|action
parameter_list|,
name|gpointer
name|data
parameter_list|)
block|{
name|GimpImage
modifier|*
name|image
decl_stmt|;
name|GimpVectors
modifier|*
name|vectors
decl_stmt|;
name|return_if_no_vectors
argument_list|(
name|image
argument_list|,
name|vectors
argument_list|,
name|data
argument_list|)
expr_stmt|;
name|gimp_image_raise_vectors
argument_list|(
name|image
argument_list|,
name|vectors
argument_list|)
expr_stmt|;
name|gimp_image_flush
argument_list|(
name|image
argument_list|)
expr_stmt|;
block|}
end_function

begin_function
name|void
DECL|function|vectors_raise_to_top_cmd_callback (GtkAction * action,gpointer data)
name|vectors_raise_to_top_cmd_callback
parameter_list|(
name|GtkAction
modifier|*
name|action
parameter_list|,
name|gpointer
name|data
parameter_list|)
block|{
name|GimpImage
modifier|*
name|image
decl_stmt|;
name|GimpVectors
modifier|*
name|vectors
decl_stmt|;
name|return_if_no_vectors
argument_list|(
name|image
argument_list|,
name|vectors
argument_list|,
name|data
argument_list|)
expr_stmt|;
name|gimp_image_raise_vectors_to_top
argument_list|(
name|image
argument_list|,
name|vectors
argument_list|)
expr_stmt|;
name|gimp_image_flush
argument_list|(
name|image
argument_list|)
expr_stmt|;
block|}
end_function

begin_function
name|void
DECL|function|vectors_lower_cmd_callback (GtkAction * action,gpointer data)
name|vectors_lower_cmd_callback
parameter_list|(
name|GtkAction
modifier|*
name|action
parameter_list|,
name|gpointer
name|data
parameter_list|)
block|{
name|GimpImage
modifier|*
name|image
decl_stmt|;
name|GimpVectors
modifier|*
name|vectors
decl_stmt|;
name|return_if_no_vectors
argument_list|(
name|image
argument_list|,
name|vectors
argument_list|,
name|data
argument_list|)
expr_stmt|;
name|gimp_image_lower_vectors
argument_list|(
name|image
argument_list|,
name|vectors
argument_list|)
expr_stmt|;
name|gimp_image_flush
argument_list|(
name|image
argument_list|)
expr_stmt|;
block|}
end_function

begin_function
name|void
DECL|function|vectors_lower_to_bottom_cmd_callback (GtkAction * action,gpointer data)
name|vectors_lower_to_bottom_cmd_callback
parameter_list|(
name|GtkAction
modifier|*
name|action
parameter_list|,
name|gpointer
name|data
parameter_list|)
block|{
name|GimpImage
modifier|*
name|image
decl_stmt|;
name|GimpVectors
modifier|*
name|vectors
decl_stmt|;
name|return_if_no_vectors
argument_list|(
name|image
argument_list|,
name|vectors
argument_list|,
name|data
argument_list|)
expr_stmt|;
name|gimp_image_lower_vectors_to_bottom
argument_list|(
name|image
argument_list|,
name|vectors
argument_list|)
expr_stmt|;
name|gimp_image_flush
argument_list|(
name|image
argument_list|)
expr_stmt|;
block|}
end_function

begin_function
name|void
DECL|function|vectors_duplicate_cmd_callback (GtkAction * action,gpointer data)
name|vectors_duplicate_cmd_callback
parameter_list|(
name|GtkAction
modifier|*
name|action
parameter_list|,
name|gpointer
name|data
parameter_list|)
block|{
name|GimpImage
modifier|*
name|image
decl_stmt|;
name|GimpVectors
modifier|*
name|vectors
decl_stmt|;
name|GimpVectors
modifier|*
name|new_vectors
decl_stmt|;
name|return_if_no_vectors
argument_list|(
name|image
argument_list|,
name|vectors
argument_list|,
name|data
argument_list|)
expr_stmt|;
name|new_vectors
operator|=
name|GIMP_VECTORS
argument_list|(
name|gimp_item_duplicate
argument_list|(
name|GIMP_ITEM
argument_list|(
name|vectors
argument_list|)
argument_list|,
name|G_TYPE_FROM_INSTANCE
argument_list|(
name|vectors
argument_list|)
argument_list|,
name|TRUE
argument_list|)
argument_list|)
expr_stmt|;
name|gimp_image_add_vectors
argument_list|(
name|image
argument_list|,
name|new_vectors
argument_list|,
operator|-
literal|1
argument_list|)
expr_stmt|;
name|gimp_image_flush
argument_list|(
name|image
argument_list|)
expr_stmt|;
block|}
end_function

begin_function
name|void
DECL|function|vectors_delete_cmd_callback (GtkAction * action,gpointer data)
name|vectors_delete_cmd_callback
parameter_list|(
name|GtkAction
modifier|*
name|action
parameter_list|,
name|gpointer
name|data
parameter_list|)
block|{
name|GimpImage
modifier|*
name|image
decl_stmt|;
name|GimpVectors
modifier|*
name|vectors
decl_stmt|;
name|return_if_no_vectors
argument_list|(
name|image
argument_list|,
name|vectors
argument_list|,
name|data
argument_list|)
expr_stmt|;
name|gimp_image_remove_vectors
argument_list|(
name|image
argument_list|,
name|vectors
argument_list|)
expr_stmt|;
name|gimp_image_flush
argument_list|(
name|image
argument_list|)
expr_stmt|;
block|}
end_function

begin_function
name|void
DECL|function|vectors_merge_visible_cmd_callback (GtkAction * action,gpointer data)
name|vectors_merge_visible_cmd_callback
parameter_list|(
name|GtkAction
modifier|*
name|action
parameter_list|,
name|gpointer
name|data
parameter_list|)
block|{
name|GimpImage
modifier|*
name|image
decl_stmt|;
name|GimpVectors
modifier|*
name|vectors
decl_stmt|;
name|return_if_no_vectors
argument_list|(
name|image
argument_list|,
name|vectors
argument_list|,
name|data
argument_list|)
expr_stmt|;
name|gimp_image_merge_visible_vectors
argument_list|(
name|image
argument_list|)
expr_stmt|;
name|gimp_image_flush
argument_list|(
name|image
argument_list|)
expr_stmt|;
block|}
end_function

begin_function
name|void
DECL|function|vectors_to_selection_cmd_callback (GtkAction * action,gint value,gpointer data)
name|vectors_to_selection_cmd_callback
parameter_list|(
name|GtkAction
modifier|*
name|action
parameter_list|,
name|gint
name|value
parameter_list|,
name|gpointer
name|data
parameter_list|)
block|{
name|GimpChannelOps
name|op
decl_stmt|;
name|GimpImage
modifier|*
name|image
decl_stmt|;
name|GimpVectors
modifier|*
name|vectors
decl_stmt|;
name|return_if_no_vectors
argument_list|(
name|image
argument_list|,
name|vectors
argument_list|,
name|data
argument_list|)
expr_stmt|;
name|op
operator|=
operator|(
name|GimpChannelOps
operator|)
name|value
expr_stmt|;
name|gimp_channel_select_vectors
argument_list|(
name|gimp_image_get_mask
argument_list|(
name|image
argument_list|)
argument_list|,
name|_
argument_list|(
literal|"Path to Selection"
argument_list|)
argument_list|,
name|vectors
argument_list|,
name|op
argument_list|,
name|TRUE
argument_list|,
name|FALSE
argument_list|,
literal|0
argument_list|,
literal|0
argument_list|,
name|TRUE
argument_list|)
expr_stmt|;
name|gimp_image_flush
argument_list|(
name|image
argument_list|)
expr_stmt|;
block|}
end_function

begin_function
name|void
DECL|function|vectors_selection_to_vectors_cmd_callback (GtkAction * action,gint value,gpointer data)
name|vectors_selection_to_vectors_cmd_callback
parameter_list|(
name|GtkAction
modifier|*
name|action
parameter_list|,
name|gint
name|value
parameter_list|,
name|gpointer
name|data
parameter_list|)
block|{
name|GimpImage
modifier|*
name|image
decl_stmt|;
name|GimpProcedure
modifier|*
name|procedure
decl_stmt|;
name|GValueArray
modifier|*
name|args
decl_stmt|;
name|GimpDisplay
modifier|*
name|display
decl_stmt|;
name|return_if_no_image
argument_list|(
name|image
argument_list|,
name|data
argument_list|)
expr_stmt|;
if|if
condition|(
name|value
condition|)
name|procedure
operator|=
name|gimp_pdb_lookup_procedure
argument_list|(
name|image
operator|->
name|gimp
operator|->
name|pdb
argument_list|,
literal|"plug-in-sel2path-advanced"
argument_list|)
expr_stmt|;
else|else
name|procedure
operator|=
name|gimp_pdb_lookup_procedure
argument_list|(
name|image
operator|->
name|gimp
operator|->
name|pdb
argument_list|,
literal|"plug-in-sel2path"
argument_list|)
expr_stmt|;
if|if
condition|(
operator|!
name|procedure
condition|)
block|{
name|g_message
argument_list|(
literal|"Selection to path procedure lookup failed."
argument_list|)
expr_stmt|;
return|return;
block|}
name|display
operator|=
name|gimp_context_get_display
argument_list|(
name|action_data_get_context
argument_list|(
name|data
argument_list|)
argument_list|)
expr_stmt|;
name|args
operator|=
name|gimp_procedure_get_arguments
argument_list|(
name|procedure
argument_list|)
expr_stmt|;
name|gimp_value_array_truncate
argument_list|(
name|args
argument_list|,
literal|2
argument_list|)
expr_stmt|;
name|g_value_set_int
argument_list|(
operator|&
name|args
operator|->
name|values
index|[
literal|0
index|]
argument_list|,
name|GIMP_RUN_INTERACTIVE
argument_list|)
expr_stmt|;
name|gimp_value_set_image
argument_list|(
operator|&
name|args
operator|->
name|values
index|[
literal|1
index|]
argument_list|,
name|image
argument_list|)
expr_stmt|;
name|gimp_procedure_execute_async
argument_list|(
name|procedure
argument_list|,
name|image
operator|->
name|gimp
argument_list|,
name|action_data_get_context
argument_list|(
name|data
argument_list|)
argument_list|,
name|GIMP_PROGRESS
argument_list|(
name|display
argument_list|)
argument_list|,
name|args
argument_list|,
name|GIMP_OBJECT
argument_list|(
name|display
argument_list|)
argument_list|)
expr_stmt|;
name|g_value_array_free
argument_list|(
name|args
argument_list|)
expr_stmt|;
block|}
end_function

begin_function
name|void
DECL|function|vectors_stroke_cmd_callback (GtkAction * action,gpointer data)
name|vectors_stroke_cmd_callback
parameter_list|(
name|GtkAction
modifier|*
name|action
parameter_list|,
name|gpointer
name|data
parameter_list|)
block|{
name|GimpImage
modifier|*
name|image
decl_stmt|;
name|GimpVectors
modifier|*
name|vectors
decl_stmt|;
name|GimpDrawable
modifier|*
name|drawable
decl_stmt|;
name|GtkWidget
modifier|*
name|widget
decl_stmt|;
name|GtkWidget
modifier|*
name|dialog
decl_stmt|;
name|return_if_no_vectors
argument_list|(
name|image
argument_list|,
name|vectors
argument_list|,
name|data
argument_list|)
expr_stmt|;
name|return_if_no_widget
argument_list|(
name|widget
argument_list|,
name|data
argument_list|)
expr_stmt|;
name|drawable
operator|=
name|gimp_image_active_drawable
argument_list|(
name|image
argument_list|)
expr_stmt|;
if|if
condition|(
operator|!
name|drawable
condition|)
block|{
name|g_message
argument_list|(
name|_
argument_list|(
literal|"There is no active layer or channel to stroke to."
argument_list|)
argument_list|)
expr_stmt|;
return|return;
block|}
name|dialog
operator|=
name|stroke_dialog_new
argument_list|(
name|GIMP_ITEM
argument_list|(
name|vectors
argument_list|)
argument_list|,
name|action_data_get_context
argument_list|(
name|data
argument_list|)
argument_list|,
name|_
argument_list|(
literal|"Stroke Path"
argument_list|)
argument_list|,
name|GIMP_STOCK_PATH_STROKE
argument_list|,
name|GIMP_HELP_PATH_STROKE
argument_list|,
name|widget
argument_list|)
expr_stmt|;
name|gtk_widget_show
argument_list|(
name|dialog
argument_list|)
expr_stmt|;
block|}
end_function

begin_function
name|void
DECL|function|vectors_stroke_last_vals_cmd_callback (GtkAction * action,gpointer data)
name|vectors_stroke_last_vals_cmd_callback
parameter_list|(
name|GtkAction
modifier|*
name|action
parameter_list|,
name|gpointer
name|data
parameter_list|)
block|{
name|GimpImage
modifier|*
name|image
decl_stmt|;
name|GimpVectors
modifier|*
name|vectors
decl_stmt|;
name|GimpDrawable
modifier|*
name|drawable
decl_stmt|;
name|GimpContext
modifier|*
name|context
decl_stmt|;
name|GimpStrokeDesc
modifier|*
name|desc
decl_stmt|;
name|return_if_no_vectors
argument_list|(
name|image
argument_list|,
name|vectors
argument_list|,
name|data
argument_list|)
expr_stmt|;
name|return_if_no_context
argument_list|(
name|context
argument_list|,
name|data
argument_list|)
expr_stmt|;
name|drawable
operator|=
name|gimp_image_active_drawable
argument_list|(
name|image
argument_list|)
expr_stmt|;
if|if
condition|(
operator|!
name|drawable
condition|)
block|{
name|g_message
argument_list|(
name|_
argument_list|(
literal|"There is no active layer or channel to stroke to."
argument_list|)
argument_list|)
expr_stmt|;
return|return;
block|}
name|desc
operator|=
name|g_object_get_data
argument_list|(
name|G_OBJECT
argument_list|(
name|image
operator|->
name|gimp
argument_list|)
argument_list|,
literal|"saved-stroke-desc"
argument_list|)
expr_stmt|;
if|if
condition|(
name|desc
condition|)
name|g_object_ref
argument_list|(
name|desc
argument_list|)
expr_stmt|;
else|else
name|desc
operator|=
name|gimp_stroke_desc_new
argument_list|(
name|image
operator|->
name|gimp
argument_list|,
name|context
argument_list|)
expr_stmt|;
name|gimp_item_stroke
argument_list|(
name|GIMP_ITEM
argument_list|(
name|vectors
argument_list|)
argument_list|,
name|drawable
argument_list|,
name|context
argument_list|,
name|desc
argument_list|,
name|FALSE
argument_list|)
expr_stmt|;
name|g_object_unref
argument_list|(
name|desc
argument_list|)
expr_stmt|;
name|gimp_image_flush
argument_list|(
name|image
argument_list|)
expr_stmt|;
block|}
end_function

begin_function
name|void
DECL|function|vectors_copy_cmd_callback (GtkAction * action,gpointer data)
name|vectors_copy_cmd_callback
parameter_list|(
name|GtkAction
modifier|*
name|action
parameter_list|,
name|gpointer
name|data
parameter_list|)
block|{
name|GimpImage
modifier|*
name|image
decl_stmt|;
name|GimpVectors
modifier|*
name|vectors
decl_stmt|;
name|gchar
modifier|*
name|svg
decl_stmt|;
name|return_if_no_vectors
argument_list|(
name|image
argument_list|,
name|vectors
argument_list|,
name|data
argument_list|)
expr_stmt|;
name|svg
operator|=
name|gimp_vectors_export_string
argument_list|(
name|image
argument_list|,
name|vectors
argument_list|)
expr_stmt|;
if|if
condition|(
name|svg
condition|)
block|{
name|gimp_clipboard_set_svg
argument_list|(
name|image
operator|->
name|gimp
argument_list|,
name|svg
argument_list|)
expr_stmt|;
name|g_free
argument_list|(
name|svg
argument_list|)
expr_stmt|;
block|}
block|}
end_function

begin_function
name|void
DECL|function|vectors_paste_cmd_callback (GtkAction * action,gpointer data)
name|vectors_paste_cmd_callback
parameter_list|(
name|GtkAction
modifier|*
name|action
parameter_list|,
name|gpointer
name|data
parameter_list|)
block|{
name|GimpImage
modifier|*
name|image
decl_stmt|;
name|gchar
modifier|*
name|svg
decl_stmt|;
name|gsize
name|svg_size
decl_stmt|;
name|return_if_no_image
argument_list|(
name|image
argument_list|,
name|data
argument_list|)
expr_stmt|;
name|svg
operator|=
name|gimp_clipboard_get_svg
argument_list|(
name|image
operator|->
name|gimp
argument_list|,
operator|&
name|svg_size
argument_list|)
expr_stmt|;
if|if
condition|(
name|svg
condition|)
block|{
name|GError
modifier|*
name|error
init|=
name|NULL
decl_stmt|;
if|if
condition|(
operator|!
name|gimp_vectors_import_buffer
argument_list|(
name|image
argument_list|,
name|svg
argument_list|,
name|svg_size
argument_list|,
name|TRUE
argument_list|,
name|TRUE
argument_list|,
operator|-
literal|1
argument_list|,
operator|&
name|error
argument_list|)
condition|)
block|{
name|g_message
argument_list|(
name|error
operator|->
name|message
argument_list|)
expr_stmt|;
name|g_clear_error
argument_list|(
operator|&
name|error
argument_list|)
expr_stmt|;
block|}
else|else
block|{
name|gimp_image_flush
argument_list|(
name|image
argument_list|)
expr_stmt|;
block|}
name|g_free
argument_list|(
name|svg
argument_list|)
expr_stmt|;
block|}
block|}
end_function

begin_function
name|void
DECL|function|vectors_export_cmd_callback (GtkAction * action,gpointer data)
name|vectors_export_cmd_callback
parameter_list|(
name|GtkAction
modifier|*
name|action
parameter_list|,
name|gpointer
name|data
parameter_list|)
block|{
name|VectorsExportDialog
modifier|*
name|dialog
decl_stmt|;
name|GimpImage
modifier|*
name|image
decl_stmt|;
name|GimpVectors
modifier|*
name|vectors
decl_stmt|;
name|GtkWidget
modifier|*
name|widget
decl_stmt|;
name|return_if_no_vectors
argument_list|(
name|image
argument_list|,
name|vectors
argument_list|,
name|data
argument_list|)
expr_stmt|;
name|return_if_no_widget
argument_list|(
name|widget
argument_list|,
name|data
argument_list|)
expr_stmt|;
name|dialog
operator|=
name|vectors_export_dialog_new
argument_list|(
name|image
argument_list|,
name|widget
argument_list|,
name|vectors_export_active_only
argument_list|)
expr_stmt|;
name|g_signal_connect
argument_list|(
name|dialog
operator|->
name|dialog
argument_list|,
literal|"response"
argument_list|,
name|G_CALLBACK
argument_list|(
name|vectors_export_response
argument_list|)
argument_list|,
name|dialog
argument_list|)
expr_stmt|;
name|gtk_widget_show
argument_list|(
name|dialog
operator|->
name|dialog
argument_list|)
expr_stmt|;
block|}
end_function

begin_function
name|void
DECL|function|vectors_import_cmd_callback (GtkAction * action,gpointer data)
name|vectors_import_cmd_callback
parameter_list|(
name|GtkAction
modifier|*
name|action
parameter_list|,
name|gpointer
name|data
parameter_list|)
block|{
name|VectorsImportDialog
modifier|*
name|dialog
decl_stmt|;
name|GimpImage
modifier|*
name|image
decl_stmt|;
name|GtkWidget
modifier|*
name|widget
decl_stmt|;
name|return_if_no_image
argument_list|(
name|image
argument_list|,
name|data
argument_list|)
expr_stmt|;
name|return_if_no_widget
argument_list|(
name|widget
argument_list|,
name|data
argument_list|)
expr_stmt|;
name|dialog
operator|=
name|vectors_import_dialog_new
argument_list|(
name|image
argument_list|,
name|widget
argument_list|,
name|vectors_import_merge
argument_list|,
name|vectors_import_scale
argument_list|)
expr_stmt|;
name|g_signal_connect
argument_list|(
name|dialog
operator|->
name|dialog
argument_list|,
literal|"response"
argument_list|,
name|G_CALLBACK
argument_list|(
name|vectors_import_response
argument_list|)
argument_list|,
name|dialog
argument_list|)
expr_stmt|;
name|gtk_widget_show
argument_list|(
name|dialog
operator|->
name|dialog
argument_list|)
expr_stmt|;
block|}
end_function

begin_function
name|void
DECL|function|vectors_visible_cmd_callback (GtkAction * action,gpointer data)
name|vectors_visible_cmd_callback
parameter_list|(
name|GtkAction
modifier|*
name|action
parameter_list|,
name|gpointer
name|data
parameter_list|)
block|{
name|GimpImage
modifier|*
name|image
decl_stmt|;
name|GimpVectors
modifier|*
name|vectors
decl_stmt|;
name|gboolean
name|visible
decl_stmt|;
name|return_if_no_vectors
argument_list|(
name|image
argument_list|,
name|vectors
argument_list|,
name|data
argument_list|)
expr_stmt|;
name|visible
operator|=
name|gtk_toggle_action_get_active
argument_list|(
name|GTK_TOGGLE_ACTION
argument_list|(
name|action
argument_list|)
argument_list|)
expr_stmt|;
if|if
condition|(
name|visible
operator|!=
name|gimp_item_get_visible
argument_list|(
name|GIMP_ITEM
argument_list|(
name|vectors
argument_list|)
argument_list|)
condition|)
block|{
name|GimpUndo
modifier|*
name|undo
decl_stmt|;
name|gboolean
name|push_undo
init|=
name|TRUE
decl_stmt|;
name|undo
operator|=
name|gimp_image_undo_can_compress
argument_list|(
name|image
argument_list|,
name|GIMP_TYPE_ITEM_UNDO
argument_list|,
name|GIMP_UNDO_ITEM_VISIBILITY
argument_list|)
expr_stmt|;
if|if
condition|(
name|undo
operator|&&
name|GIMP_ITEM_UNDO
argument_list|(
name|undo
argument_list|)
operator|->
name|item
operator|==
name|GIMP_ITEM
argument_list|(
name|vectors
argument_list|)
condition|)
name|push_undo
operator|=
name|FALSE
expr_stmt|;
name|gimp_item_set_visible
argument_list|(
name|GIMP_ITEM
argument_list|(
name|vectors
argument_list|)
argument_list|,
name|visible
argument_list|,
name|push_undo
argument_list|)
expr_stmt|;
name|gimp_image_flush
argument_list|(
name|image
argument_list|)
expr_stmt|;
block|}
block|}
end_function

begin_function
name|void
DECL|function|vectors_linked_cmd_callback (GtkAction * action,gpointer data)
name|vectors_linked_cmd_callback
parameter_list|(
name|GtkAction
modifier|*
name|action
parameter_list|,
name|gpointer
name|data
parameter_list|)
block|{
name|GimpImage
modifier|*
name|image
decl_stmt|;
name|GimpVectors
modifier|*
name|vectors
decl_stmt|;
name|gboolean
name|linked
decl_stmt|;
name|return_if_no_vectors
argument_list|(
name|image
argument_list|,
name|vectors
argument_list|,
name|data
argument_list|)
expr_stmt|;
name|linked
operator|=
name|gtk_toggle_action_get_active
argument_list|(
name|GTK_TOGGLE_ACTION
argument_list|(
name|action
argument_list|)
argument_list|)
expr_stmt|;
if|if
condition|(
name|linked
operator|!=
name|gimp_item_get_linked
argument_list|(
name|GIMP_ITEM
argument_list|(
name|vectors
argument_list|)
argument_list|)
condition|)
block|{
name|GimpUndo
modifier|*
name|undo
decl_stmt|;
name|gboolean
name|push_undo
init|=
name|TRUE
decl_stmt|;
name|undo
operator|=
name|gimp_image_undo_can_compress
argument_list|(
name|image
argument_list|,
name|GIMP_TYPE_ITEM_UNDO
argument_list|,
name|GIMP_UNDO_ITEM_LINKED
argument_list|)
expr_stmt|;
if|if
condition|(
name|undo
operator|&&
name|GIMP_ITEM_UNDO
argument_list|(
name|undo
argument_list|)
operator|->
name|item
operator|==
name|GIMP_ITEM
argument_list|(
name|vectors
argument_list|)
condition|)
name|push_undo
operator|=
name|FALSE
expr_stmt|;
name|gimp_item_set_linked
argument_list|(
name|GIMP_ITEM
argument_list|(
name|vectors
argument_list|)
argument_list|,
name|linked
argument_list|,
name|push_undo
argument_list|)
expr_stmt|;
name|gimp_image_flush
argument_list|(
name|image
argument_list|)
expr_stmt|;
block|}
block|}
end_function

begin_comment
comment|/*  private functions  */
end_comment

begin_function
specifier|static
name|void
DECL|function|vectors_new_vectors_response (GtkWidget * widget,gint response_id,VectorsOptionsDialog * options)
name|vectors_new_vectors_response
parameter_list|(
name|GtkWidget
modifier|*
name|widget
parameter_list|,
name|gint
name|response_id
parameter_list|,
name|VectorsOptionsDialog
modifier|*
name|options
parameter_list|)
block|{
if|if
condition|(
name|response_id
operator|==
name|GTK_RESPONSE_OK
condition|)
block|{
name|GimpVectors
modifier|*
name|new_vectors
decl_stmt|;
if|if
condition|(
name|vectors_name
condition|)
name|g_free
argument_list|(
name|vectors_name
argument_list|)
expr_stmt|;
name|vectors_name
operator|=
name|g_strdup
argument_list|(
name|gtk_entry_get_text
argument_list|(
name|GTK_ENTRY
argument_list|(
name|options
operator|->
name|name_entry
argument_list|)
argument_list|)
argument_list|)
expr_stmt|;
name|new_vectors
operator|=
name|gimp_vectors_new
argument_list|(
name|options
operator|->
name|image
argument_list|,
name|vectors_name
argument_list|)
expr_stmt|;
name|gimp_image_add_vectors
argument_list|(
name|options
operator|->
name|image
argument_list|,
name|new_vectors
argument_list|,
operator|-
literal|1
argument_list|)
expr_stmt|;
name|gimp_image_flush
argument_list|(
name|options
operator|->
name|image
argument_list|)
expr_stmt|;
block|}
name|gtk_widget_destroy
argument_list|(
name|options
operator|->
name|dialog
argument_list|)
expr_stmt|;
block|}
end_function

begin_function
specifier|static
name|void
DECL|function|vectors_edit_vectors_response (GtkWidget * widget,gint response_id,VectorsOptionsDialog * options)
name|vectors_edit_vectors_response
parameter_list|(
name|GtkWidget
modifier|*
name|widget
parameter_list|,
name|gint
name|response_id
parameter_list|,
name|VectorsOptionsDialog
modifier|*
name|options
parameter_list|)
block|{
if|if
condition|(
name|response_id
operator|==
name|GTK_RESPONSE_OK
condition|)
block|{
name|GimpVectors
modifier|*
name|vectors
init|=
name|options
operator|->
name|vectors
decl_stmt|;
specifier|const
name|gchar
modifier|*
name|new_name
decl_stmt|;
name|new_name
operator|=
name|gtk_entry_get_text
argument_list|(
name|GTK_ENTRY
argument_list|(
name|options
operator|->
name|name_entry
argument_list|)
argument_list|)
expr_stmt|;
if|if
condition|(
name|strcmp
argument_list|(
name|new_name
argument_list|,
name|gimp_object_get_name
argument_list|(
name|GIMP_OBJECT
argument_list|(
name|vectors
argument_list|)
argument_list|)
argument_list|)
condition|)
block|{
name|gimp_item_rename
argument_list|(
name|GIMP_ITEM
argument_list|(
name|vectors
argument_list|)
argument_list|,
name|new_name
argument_list|)
expr_stmt|;
name|gimp_image_flush
argument_list|(
name|options
operator|->
name|image
argument_list|)
expr_stmt|;
block|}
block|}
name|gtk_widget_destroy
argument_list|(
name|options
operator|->
name|dialog
argument_list|)
expr_stmt|;
block|}
end_function

begin_function
specifier|static
name|void
DECL|function|vectors_import_response (GtkWidget * widget,gint response_id,VectorsImportDialog * dialog)
name|vectors_import_response
parameter_list|(
name|GtkWidget
modifier|*
name|widget
parameter_list|,
name|gint
name|response_id
parameter_list|,
name|VectorsImportDialog
modifier|*
name|dialog
parameter_list|)
block|{
if|if
condition|(
name|response_id
operator|==
name|GTK_RESPONSE_OK
condition|)
block|{
name|gchar
modifier|*
name|filename
decl_stmt|;
name|GError
modifier|*
name|error
init|=
name|NULL
decl_stmt|;
name|vectors_import_merge
operator|=
name|dialog
operator|->
name|merge_vectors
expr_stmt|;
name|vectors_import_scale
operator|=
name|dialog
operator|->
name|scale_vectors
expr_stmt|;
name|filename
operator|=
name|gtk_file_chooser_get_filename
argument_list|(
name|GTK_FILE_CHOOSER
argument_list|(
name|widget
argument_list|)
argument_list|)
expr_stmt|;
if|if
condition|(
name|gimp_vectors_import_file
argument_list|(
name|dialog
operator|->
name|image
argument_list|,
name|filename
argument_list|,
name|vectors_import_merge
argument_list|,
name|vectors_import_scale
argument_list|,
operator|-
literal|1
argument_list|,
operator|&
name|error
argument_list|)
condition|)
block|{
name|gimp_image_flush
argument_list|(
name|dialog
operator|->
name|image
argument_list|)
expr_stmt|;
block|}
else|else
block|{
name|g_message
argument_list|(
name|error
operator|->
name|message
argument_list|)
expr_stmt|;
name|g_error_free
argument_list|(
name|error
argument_list|)
expr_stmt|;
block|}
name|g_free
argument_list|(
name|filename
argument_list|)
expr_stmt|;
block|}
name|gtk_widget_destroy
argument_list|(
name|widget
argument_list|)
expr_stmt|;
block|}
end_function

begin_function
specifier|static
name|void
DECL|function|vectors_export_response (GtkWidget * widget,gint response_id,VectorsExportDialog * dialog)
name|vectors_export_response
parameter_list|(
name|GtkWidget
modifier|*
name|widget
parameter_list|,
name|gint
name|response_id
parameter_list|,
name|VectorsExportDialog
modifier|*
name|dialog
parameter_list|)
block|{
if|if
condition|(
name|response_id
operator|==
name|GTK_RESPONSE_OK
condition|)
block|{
name|GimpVectors
modifier|*
name|vectors
init|=
name|NULL
decl_stmt|;
name|gchar
modifier|*
name|filename
decl_stmt|;
name|GError
modifier|*
name|error
init|=
name|NULL
decl_stmt|;
name|vectors_export_active_only
operator|=
name|dialog
operator|->
name|active_only
expr_stmt|;
name|filename
operator|=
name|gtk_file_chooser_get_filename
argument_list|(
name|GTK_FILE_CHOOSER
argument_list|(
name|widget
argument_list|)
argument_list|)
expr_stmt|;
if|if
condition|(
name|vectors_export_active_only
condition|)
name|vectors
operator|=
name|gimp_image_get_active_vectors
argument_list|(
name|dialog
operator|->
name|image
argument_list|)
expr_stmt|;
if|if
condition|(
operator|!
name|gimp_vectors_export_file
argument_list|(
name|dialog
operator|->
name|image
argument_list|,
name|vectors
argument_list|,
name|filename
argument_list|,
operator|&
name|error
argument_list|)
condition|)
block|{
name|g_message
argument_list|(
name|error
operator|->
name|message
argument_list|)
expr_stmt|;
name|g_error_free
argument_list|(
name|error
argument_list|)
expr_stmt|;
block|}
name|g_free
argument_list|(
name|filename
argument_list|)
expr_stmt|;
block|}
name|gtk_widget_destroy
argument_list|(
name|widget
argument_list|)
expr_stmt|;
block|}
end_function

end_unit

