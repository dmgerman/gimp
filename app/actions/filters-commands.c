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
file|"core/gimptoolinfo.h"
end_include

begin_include
include|#
directive|include
file|"pdb/gimpprocedure.h"
end_include

begin_comment
comment|/* FIXME history */
end_comment

begin_include
include|#
directive|include
file|"tools/gimpoperationtool.h"
end_include

begin_include
include|#
directive|include
file|"tools/tool_manager.h"
end_include

begin_include
include|#
directive|include
file|"actions.h"
end_include

begin_include
include|#
directive|include
file|"filters-commands.h"
end_include

begin_include
include|#
directive|include
file|"plug-in-commands.h"
end_include

begin_comment
comment|/* FIXME history */
end_comment

begin_include
include|#
directive|include
file|"gimp-intl.h"
end_include

begin_comment
comment|/*  public functions  */
end_comment

begin_function
name|void
DECL|function|filters_filter_cmd_callback (GtkAction * action,const gchar * operation,gpointer data)
name|filters_filter_cmd_callback
parameter_list|(
name|GtkAction
modifier|*
name|action
parameter_list|,
specifier|const
name|gchar
modifier|*
name|operation
parameter_list|,
name|gpointer
name|data
parameter_list|)
block|{
name|GimpImage
modifier|*
name|image
decl_stmt|;
name|GimpDrawable
modifier|*
name|drawable
decl_stmt|;
name|GimpDisplay
modifier|*
name|display
decl_stmt|;
name|GimpTool
modifier|*
name|active_tool
decl_stmt|;
name|return_if_no_drawable
argument_list|(
name|image
argument_list|,
name|drawable
argument_list|,
name|data
argument_list|)
expr_stmt|;
name|return_if_no_display
argument_list|(
name|display
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
name|G_TYPE_FROM_INSTANCE
argument_list|(
name|active_tool
argument_list|)
operator|!=
name|GIMP_TYPE_OPERATION_TOOL
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
literal|"gimp-operation-tool"
argument_list|)
decl_stmt|;
if|if
condition|(
name|GIMP_IS_TOOL_INFO
argument_list|(
name|tool_info
argument_list|)
condition|)
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
block|}
else|else
block|{
name|gimp_context_tool_changed
argument_list|(
name|action_data_get_context
argument_list|(
name|data
argument_list|)
argument_list|)
expr_stmt|;
block|}
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
name|GIMP_IS_OPERATION_TOOL
argument_list|(
name|active_tool
argument_list|)
condition|)
block|{
name|gchar
modifier|*
name|label
init|=
name|gimp_strip_uline
argument_list|(
name|gtk_action_get_label
argument_list|(
name|action
argument_list|)
argument_list|)
decl_stmt|;
specifier|const
name|gchar
modifier|*
name|ellipsis
init|=
name|_
argument_list|(
literal|"..."
argument_list|)
decl_stmt|;
name|gint
name|label_len
decl_stmt|;
name|gint
name|ellipsis_len
decl_stmt|;
name|label_len
operator|=
name|strlen
argument_list|(
name|label
argument_list|)
expr_stmt|;
name|ellipsis_len
operator|=
name|strlen
argument_list|(
name|ellipsis
argument_list|)
expr_stmt|;
if|if
condition|(
name|label_len
operator|>
name|ellipsis_len
operator|&&
name|strcmp
argument_list|(
name|label
operator|+
name|label_len
operator|-
name|ellipsis_len
argument_list|,
name|ellipsis
argument_list|)
operator|==
literal|0
condition|)
block|{
name|label
index|[
name|label_len
operator|-
name|ellipsis_len
index|]
operator|=
literal|'\0'
expr_stmt|;
block|}
name|gimp_operation_tool_set_operation
argument_list|(
name|GIMP_OPERATION_TOOL
argument_list|(
name|active_tool
argument_list|)
argument_list|,
name|operation
argument_list|,
name|label
argument_list|,
name|gtk_action_get_icon_name
argument_list|(
name|action
argument_list|)
argument_list|)
expr_stmt|;
name|tool_manager_initialize_active
argument_list|(
name|image
operator|->
name|gimp
argument_list|,
name|display
argument_list|)
expr_stmt|;
name|g_free
argument_list|(
name|label
argument_list|)
expr_stmt|;
block|}
block|}
end_function

begin_function
name|void
DECL|function|filters_repeat_cmd_callback (GtkAction * action,gint value,gpointer data)
name|filters_repeat_cmd_callback
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
name|GimpPlugInProcedure
modifier|*
name|procedure
decl_stmt|;
name|Gimp
modifier|*
name|gimp
decl_stmt|;
name|GimpDisplay
modifier|*
name|display
decl_stmt|;
name|GimpRunMode
name|run_mode
decl_stmt|;
name|return_if_no_gimp
argument_list|(
name|gimp
argument_list|,
name|data
argument_list|)
expr_stmt|;
name|return_if_no_display
argument_list|(
name|display
argument_list|,
name|data
argument_list|)
expr_stmt|;
name|run_mode
operator|=
operator|(
name|GimpRunMode
operator|)
name|value
expr_stmt|;
name|procedure
operator|=
name|gimp_filter_history_nth
argument_list|(
name|gimp
argument_list|,
literal|0
argument_list|)
expr_stmt|;
if|if
condition|(
name|procedure
condition|)
block|{
name|GimpValueArray
modifier|*
name|args
decl_stmt|;
name|gint
name|n_args
decl_stmt|;
name|args
operator|=
name|gimp_procedure_get_arguments
argument_list|(
name|GIMP_PROCEDURE
argument_list|(
name|procedure
argument_list|)
argument_list|)
expr_stmt|;
name|g_value_set_int
argument_list|(
name|gimp_value_array_index
argument_list|(
name|args
argument_list|,
literal|0
argument_list|)
argument_list|,
name|run_mode
argument_list|)
expr_stmt|;
name|n_args
operator|=
name|plug_in_collect_display_args
argument_list|(
name|action
argument_list|,
name|display
argument_list|,
name|GIMP_PROCEDURE
argument_list|(
name|procedure
argument_list|)
operator|->
name|args
argument_list|,
name|args
argument_list|,
literal|1
argument_list|)
expr_stmt|;
name|plug_in_procedure_execute
argument_list|(
name|procedure
argument_list|,
name|gimp
argument_list|,
name|display
argument_list|,
name|args
argument_list|,
name|n_args
argument_list|)
expr_stmt|;
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
DECL|function|filters_history_cmd_callback (GtkAction * action,GimpPlugInProcedure * procedure,gpointer data)
name|filters_history_cmd_callback
parameter_list|(
name|GtkAction
modifier|*
name|action
parameter_list|,
name|GimpPlugInProcedure
modifier|*
name|procedure
parameter_list|,
name|gpointer
name|data
parameter_list|)
block|{
name|Gimp
modifier|*
name|gimp
decl_stmt|;
name|GimpDisplay
modifier|*
name|display
decl_stmt|;
name|GimpValueArray
modifier|*
name|args
decl_stmt|;
name|gint
name|n_args
decl_stmt|;
name|return_if_no_gimp
argument_list|(
name|gimp
argument_list|,
name|data
argument_list|)
expr_stmt|;
name|return_if_no_display
argument_list|(
name|display
argument_list|,
name|data
argument_list|)
expr_stmt|;
name|args
operator|=
name|gimp_procedure_get_arguments
argument_list|(
name|GIMP_PROCEDURE
argument_list|(
name|procedure
argument_list|)
argument_list|)
expr_stmt|;
name|g_value_set_int
argument_list|(
name|gimp_value_array_index
argument_list|(
name|args
argument_list|,
literal|0
argument_list|)
argument_list|,
name|GIMP_RUN_INTERACTIVE
argument_list|)
expr_stmt|;
name|n_args
operator|=
name|plug_in_collect_display_args
argument_list|(
name|action
argument_list|,
name|display
argument_list|,
name|GIMP_PROCEDURE
argument_list|(
name|procedure
argument_list|)
operator|->
name|args
argument_list|,
name|args
argument_list|,
literal|1
argument_list|)
expr_stmt|;
name|plug_in_procedure_execute
argument_list|(
name|procedure
argument_list|,
name|gimp
argument_list|,
name|display
argument_list|,
name|args
argument_list|,
name|n_args
argument_list|)
expr_stmt|;
name|gimp_value_array_unref
argument_list|(
name|args
argument_list|)
expr_stmt|;
block|}
end_function

end_unit

