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
file|"core/gimp.h"
end_include

begin_include
include|#
directive|include
file|"core/gimp-filter-history.h"
end_include

begin_include
include|#
directive|include
file|"core/gimpcontainer.h"
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
file|"core/gimpitem.h"
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
file|"pdb/gimpprocedure.h"
end_include

begin_include
include|#
directive|include
file|"plug-in/gimppluginmanager.h"
end_include

begin_include
include|#
directive|include
file|"plug-in/gimppluginmanager-data.h"
end_include

begin_include
include|#
directive|include
file|"widgets/gimpbufferview.h"
end_include

begin_include
include|#
directive|include
file|"widgets/gimpcontainerview.h"
end_include

begin_include
include|#
directive|include
file|"widgets/gimpdatafactoryview.h"
end_include

begin_include
include|#
directive|include
file|"widgets/gimphelp-ids.h"
end_include

begin_include
include|#
directive|include
file|"widgets/gimpimageeditor.h"
end_include

begin_include
include|#
directive|include
file|"widgets/gimpitemtreeview.h"
end_include

begin_include
include|#
directive|include
file|"widgets/gimpmessagebox.h"
end_include

begin_include
include|#
directive|include
file|"widgets/gimpmessagedialog.h"
end_include

begin_include
include|#
directive|include
file|"dialogs/dialogs.h"
end_include

begin_include
include|#
directive|include
file|"actions.h"
end_include

begin_include
include|#
directive|include
file|"plug-in-commands.h"
end_include

begin_include
include|#
directive|include
file|"procedure-commands.h"
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
name|plug_in_reset_all_response
parameter_list|(
name|GtkWidget
modifier|*
name|dialog
parameter_list|,
name|gint
name|response_id
parameter_list|,
name|Gimp
modifier|*
name|gimp
parameter_list|)
function_decl|;
end_function_decl

begin_comment
comment|/*  public functions  */
end_comment

begin_function
name|void
DECL|function|plug_in_run_cmd_callback (GimpAction * action,GVariant * value,gpointer data)
name|plug_in_run_cmd_callback
parameter_list|(
name|GimpAction
modifier|*
name|action
parameter_list|,
name|GVariant
modifier|*
name|value
parameter_list|,
name|gpointer
name|data
parameter_list|)
block|{
name|Gimp
modifier|*
name|gimp
decl_stmt|;
name|GimpValueArray
modifier|*
name|args
init|=
name|NULL
decl_stmt|;
name|GimpDisplay
modifier|*
name|display
init|=
name|NULL
decl_stmt|;
name|GimpProcedure
modifier|*
name|procedure
decl_stmt|;
name|gsize
name|hack
decl_stmt|;
name|return_if_no_gimp
argument_list|(
name|gimp
argument_list|,
name|data
argument_list|)
expr_stmt|;
name|hack
operator|=
name|g_variant_get_uint64
argument_list|(
name|value
argument_list|)
expr_stmt|;
name|procedure
operator|=
name|GSIZE_TO_POINTER
argument_list|(
name|hack
argument_list|)
expr_stmt|;
switch|switch
condition|(
name|procedure
operator|->
name|proc_type
condition|)
block|{
case|case
name|GIMP_EXTENSION
case|:
name|args
operator|=
name|procedure_commands_get_run_mode_arg
argument_list|(
name|procedure
argument_list|)
expr_stmt|;
break|break;
case|case
name|GIMP_PLUGIN
case|:
case|case
name|GIMP_TEMPORARY
case|:
if|if
condition|(
name|GIMP_IS_DATA_FACTORY_VIEW
argument_list|(
name|data
argument_list|)
operator|||
name|GIMP_IS_BUFFER_VIEW
argument_list|(
name|data
argument_list|)
condition|)
block|{
name|GimpContainerEditor
modifier|*
name|editor
init|=
name|GIMP_CONTAINER_EDITOR
argument_list|(
name|data
argument_list|)
decl_stmt|;
name|GimpContainer
modifier|*
name|container
decl_stmt|;
name|GimpContext
modifier|*
name|context
decl_stmt|;
name|GimpObject
modifier|*
name|object
decl_stmt|;
name|container
operator|=
name|gimp_container_view_get_container
argument_list|(
name|editor
operator|->
name|view
argument_list|)
expr_stmt|;
name|context
operator|=
name|gimp_container_view_get_context
argument_list|(
name|editor
operator|->
name|view
argument_list|)
expr_stmt|;
name|object
operator|=
name|gimp_context_get_by_type
argument_list|(
name|context
argument_list|,
name|gimp_container_get_children_type
argument_list|(
name|container
argument_list|)
argument_list|)
expr_stmt|;
name|args
operator|=
name|procedure_commands_get_data_args
argument_list|(
name|procedure
argument_list|,
name|object
argument_list|)
expr_stmt|;
block|}
elseif|else
if|if
condition|(
name|GIMP_IS_IMAGE_EDITOR
argument_list|(
name|data
argument_list|)
condition|)
block|{
name|GimpImageEditor
modifier|*
name|editor
init|=
name|GIMP_IMAGE_EDITOR
argument_list|(
name|data
argument_list|)
decl_stmt|;
name|GimpImage
modifier|*
name|image
decl_stmt|;
name|image
operator|=
name|gimp_image_editor_get_image
argument_list|(
name|editor
argument_list|)
expr_stmt|;
name|args
operator|=
name|procedure_commands_get_image_args
argument_list|(
name|procedure
argument_list|,
name|image
argument_list|)
expr_stmt|;
block|}
elseif|else
if|if
condition|(
name|GIMP_IS_ITEM_TREE_VIEW
argument_list|(
name|data
argument_list|)
condition|)
block|{
name|GimpItemTreeView
modifier|*
name|view
init|=
name|GIMP_ITEM_TREE_VIEW
argument_list|(
name|data
argument_list|)
decl_stmt|;
name|GimpImage
modifier|*
name|image
decl_stmt|;
name|GimpItem
modifier|*
name|item
decl_stmt|;
name|image
operator|=
name|gimp_item_tree_view_get_image
argument_list|(
name|view
argument_list|)
expr_stmt|;
if|if
condition|(
name|image
condition|)
name|item
operator|=
name|GIMP_ITEM_TREE_VIEW_GET_CLASS
argument_list|(
name|view
argument_list|)
operator|->
name|get_active_item
argument_list|(
name|image
argument_list|)
expr_stmt|;
else|else
name|item
operator|=
name|NULL
expr_stmt|;
name|args
operator|=
name|procedure_commands_get_item_args
argument_list|(
name|procedure
argument_list|,
name|image
argument_list|,
name|item
argument_list|)
expr_stmt|;
block|}
else|else
block|{
name|display
operator|=
name|action_data_get_display
argument_list|(
name|data
argument_list|)
expr_stmt|;
name|args
operator|=
name|procedure_commands_get_display_args
argument_list|(
name|procedure
argument_list|,
name|display
argument_list|,
name|NULL
argument_list|)
expr_stmt|;
block|}
break|break;
case|case
name|GIMP_INTERNAL
case|:
name|g_warning
argument_list|(
literal|"Unhandled procedure type."
argument_list|)
expr_stmt|;
break|break;
block|}
if|if
condition|(
name|args
condition|)
block|{
if|if
condition|(
name|procedure_commands_run_procedure_async
argument_list|(
name|procedure
argument_list|,
name|gimp
argument_list|,
name|GIMP_PROGRESS
argument_list|(
name|display
argument_list|)
argument_list|,
name|GIMP_RUN_INTERACTIVE
argument_list|,
name|args
argument_list|,
name|display
argument_list|)
condition|)
block|{
comment|/* remember only image plug-ins */
if|if
condition|(
name|procedure
operator|->
name|num_args
operator|>=
literal|2
operator|&&
name|GIMP_IS_PARAM_SPEC_IMAGE
argument_list|(
name|procedure
operator|->
name|args
index|[
literal|1
index|]
argument_list|)
condition|)
block|{
name|gimp_filter_history_add
argument_list|(
name|gimp
argument_list|,
name|procedure
argument_list|)
expr_stmt|;
block|}
block|}
name|gimp_value_array_unref
argument_list|(
name|args
argument_list|)
expr_stmt|;
block|}
block|}
end_function

begin_function
name|void
DECL|function|plug_in_reset_all_cmd_callback (GimpAction * action,GVariant * value,gpointer data)
name|plug_in_reset_all_cmd_callback
parameter_list|(
name|GimpAction
modifier|*
name|action
parameter_list|,
name|GVariant
modifier|*
name|value
parameter_list|,
name|gpointer
name|data
parameter_list|)
block|{
name|Gimp
modifier|*
name|gimp
decl_stmt|;
name|GtkWidget
modifier|*
name|dialog
decl_stmt|;
name|return_if_no_gimp
argument_list|(
name|gimp
argument_list|,
name|data
argument_list|)
expr_stmt|;
DECL|macro|RESET_FILTERS_DIALOG_KEY
define|#
directive|define
name|RESET_FILTERS_DIALOG_KEY
value|"gimp-reset-all-filters-dialog"
name|dialog
operator|=
name|dialogs_get_dialog
argument_list|(
name|G_OBJECT
argument_list|(
name|gimp
argument_list|)
argument_list|,
name|RESET_FILTERS_DIALOG_KEY
argument_list|)
expr_stmt|;
if|if
condition|(
operator|!
name|dialog
condition|)
block|{
name|dialog
operator|=
name|gimp_message_dialog_new
argument_list|(
name|_
argument_list|(
literal|"Reset all Filters"
argument_list|)
argument_list|,
name|GIMP_ICON_DIALOG_QUESTION
argument_list|,
name|NULL
argument_list|,
literal|0
argument_list|,
name|gimp_standard_help_func
argument_list|,
name|NULL
argument_list|,
name|_
argument_list|(
literal|"_Cancel"
argument_list|)
argument_list|,
name|GTK_RESPONSE_CANCEL
argument_list|,
name|_
argument_list|(
literal|"_Reset"
argument_list|)
argument_list|,
name|GTK_RESPONSE_OK
argument_list|,
name|NULL
argument_list|)
expr_stmt|;
name|gimp_dialog_set_alternative_button_order
argument_list|(
name|GTK_DIALOG
argument_list|(
name|dialog
argument_list|)
argument_list|,
name|GTK_RESPONSE_OK
argument_list|,
name|GTK_RESPONSE_CANCEL
argument_list|,
operator|-
literal|1
argument_list|)
expr_stmt|;
name|g_signal_connect
argument_list|(
name|dialog
argument_list|,
literal|"response"
argument_list|,
name|G_CALLBACK
argument_list|(
name|plug_in_reset_all_response
argument_list|)
argument_list|,
name|gimp
argument_list|)
expr_stmt|;
name|gimp_message_box_set_primary_text
argument_list|(
name|GIMP_MESSAGE_DIALOG
argument_list|(
name|dialog
argument_list|)
operator|->
name|box
argument_list|,
name|_
argument_list|(
literal|"Do you really want to reset all "
literal|"filters to default values?"
argument_list|)
argument_list|)
expr_stmt|;
name|dialogs_attach_dialog
argument_list|(
name|G_OBJECT
argument_list|(
name|gimp
argument_list|)
argument_list|,
name|RESET_FILTERS_DIALOG_KEY
argument_list|,
name|dialog
argument_list|)
expr_stmt|;
block|}
name|gtk_window_present
argument_list|(
name|GTK_WINDOW
argument_list|(
name|dialog
argument_list|)
argument_list|)
expr_stmt|;
block|}
end_function

begin_comment
comment|/*  private functions  */
end_comment

begin_function
specifier|static
name|void
DECL|function|plug_in_reset_all_response (GtkWidget * dialog,gint response_id,Gimp * gimp)
name|plug_in_reset_all_response
parameter_list|(
name|GtkWidget
modifier|*
name|dialog
parameter_list|,
name|gint
name|response_id
parameter_list|,
name|Gimp
modifier|*
name|gimp
parameter_list|)
block|{
name|gtk_widget_destroy
argument_list|(
name|dialog
argument_list|)
expr_stmt|;
if|if
condition|(
name|response_id
operator|==
name|GTK_RESPONSE_OK
condition|)
name|gimp_plug_in_manager_data_free
argument_list|(
name|gimp
operator|->
name|plug_in_manager
argument_list|)
expr_stmt|;
block|}
end_function

end_unit

