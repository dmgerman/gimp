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
file|<string.h>
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
file|"libgimpconfig/gimpconfig.h"
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
file|"operations/gimp-operation-config.h"
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
file|"core/gimpimage.h"
end_include

begin_include
include|#
directive|include
file|"core/gimpprogress.h"
end_include

begin_include
include|#
directive|include
file|"core/gimpsettings.h"
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
file|"gimpgeglprocedure.h"
end_include

begin_include
include|#
directive|include
file|"procedure-commands.h"
end_include

begin_comment
comment|/*  local function prototypes  */
end_comment

begin_function_decl
specifier|static
name|gchar
modifier|*
name|filters_parse_operation
parameter_list|(
name|Gimp
modifier|*
name|gimp
parameter_list|,
specifier|const
name|gchar
modifier|*
name|operation_str
parameter_list|,
specifier|const
name|gchar
modifier|*
name|icon_name
parameter_list|,
name|GimpObject
modifier|*
modifier|*
name|settings
parameter_list|)
function_decl|;
end_function_decl

begin_function_decl
specifier|static
name|void
name|filters_run_procedure
parameter_list|(
name|Gimp
modifier|*
name|gimp
parameter_list|,
name|GimpDisplay
modifier|*
name|display
parameter_list|,
name|GimpProcedure
modifier|*
name|procedure
parameter_list|,
name|GimpRunMode
name|run_mode
parameter_list|)
function_decl|;
end_function_decl

begin_comment
comment|/*  public functions  */
end_comment

begin_function
name|void
DECL|function|filters_apply_cmd_callback (GtkAction * action,const gchar * operation_str,gpointer data)
name|filters_apply_cmd_callback
parameter_list|(
name|GtkAction
modifier|*
name|action
parameter_list|,
specifier|const
name|gchar
modifier|*
name|operation_str
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
name|gchar
modifier|*
name|operation
decl_stmt|;
name|GimpObject
modifier|*
name|settings
decl_stmt|;
name|GimpProcedure
modifier|*
name|procedure
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
name|operation
operator|=
name|filters_parse_operation
argument_list|(
name|image
operator|->
name|gimp
argument_list|,
name|operation_str
argument_list|,
name|gtk_action_get_icon_name
argument_list|(
name|action
argument_list|)
argument_list|,
operator|&
name|settings
argument_list|)
expr_stmt|;
name|procedure
operator|=
name|gimp_gegl_procedure_new
argument_list|(
name|image
operator|->
name|gimp
argument_list|,
name|GIMP_RUN_NONINTERACTIVE
argument_list|,
name|settings
argument_list|,
name|operation
argument_list|,
name|gtk_action_get_name
argument_list|(
name|action
argument_list|)
argument_list|,
name|gtk_action_get_label
argument_list|(
name|action
argument_list|)
argument_list|,
name|gtk_action_get_tooltip
argument_list|(
name|action
argument_list|)
argument_list|,
name|gtk_action_get_icon_name
argument_list|(
name|action
argument_list|)
argument_list|,
name|g_object_get_qdata
argument_list|(
name|G_OBJECT
argument_list|(
name|action
argument_list|)
argument_list|,
name|GIMP_HELP_ID
argument_list|)
argument_list|)
expr_stmt|;
name|g_free
argument_list|(
name|operation
argument_list|)
expr_stmt|;
if|if
condition|(
name|settings
condition|)
name|g_object_unref
argument_list|(
name|settings
argument_list|)
expr_stmt|;
name|gimp_filter_history_add
argument_list|(
name|image
operator|->
name|gimp
argument_list|,
name|procedure
argument_list|)
expr_stmt|;
name|filters_history_cmd_callback
argument_list|(
name|NULL
argument_list|,
name|procedure
argument_list|,
name|data
argument_list|)
expr_stmt|;
name|g_object_unref
argument_list|(
name|procedure
argument_list|)
expr_stmt|;
block|}
end_function

begin_function
name|void
DECL|function|filters_apply_interactive_cmd_callback (GtkAction * action,const gchar * operation,gpointer data)
name|filters_apply_interactive_cmd_callback
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
name|GimpProcedure
modifier|*
name|procedure
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
name|procedure
operator|=
name|gimp_gegl_procedure_new
argument_list|(
name|image
operator|->
name|gimp
argument_list|,
name|GIMP_RUN_INTERACTIVE
argument_list|,
name|NULL
argument_list|,
name|operation
argument_list|,
name|gtk_action_get_name
argument_list|(
name|action
argument_list|)
argument_list|,
name|gtk_action_get_label
argument_list|(
name|action
argument_list|)
argument_list|,
name|gtk_action_get_tooltip
argument_list|(
name|action
argument_list|)
argument_list|,
name|gtk_action_get_icon_name
argument_list|(
name|action
argument_list|)
argument_list|,
name|g_object_get_qdata
argument_list|(
name|G_OBJECT
argument_list|(
name|action
argument_list|)
argument_list|,
name|GIMP_HELP_ID
argument_list|)
argument_list|)
expr_stmt|;
name|gimp_filter_history_add
argument_list|(
name|image
operator|->
name|gimp
argument_list|,
name|procedure
argument_list|)
expr_stmt|;
name|filters_history_cmd_callback
argument_list|(
name|NULL
argument_list|,
name|procedure
argument_list|,
name|data
argument_list|)
expr_stmt|;
name|g_object_unref
argument_list|(
name|procedure
argument_list|)
expr_stmt|;
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
name|GimpProcedure
modifier|*
name|procedure
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
name|procedure
operator|=
name|gimp_filter_history_nth
argument_list|(
name|image
operator|->
name|gimp
argument_list|,
literal|0
argument_list|)
expr_stmt|;
if|if
condition|(
name|procedure
condition|)
name|filters_run_procedure
argument_list|(
name|image
operator|->
name|gimp
argument_list|,
name|display
argument_list|,
name|procedure
argument_list|,
operator|(
name|GimpRunMode
operator|)
name|value
argument_list|)
expr_stmt|;
block|}
end_function

begin_function
name|void
DECL|function|filters_history_cmd_callback (GtkAction * action,GimpProcedure * procedure,gpointer data)
name|filters_history_cmd_callback
parameter_list|(
name|GtkAction
modifier|*
name|action
parameter_list|,
name|GimpProcedure
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
name|filters_run_procedure
argument_list|(
name|gimp
argument_list|,
name|display
argument_list|,
name|procedure
argument_list|,
name|GIMP_RUN_INTERACTIVE
argument_list|)
expr_stmt|;
block|}
end_function

begin_comment
comment|/*  private functions  */
end_comment

begin_function
specifier|static
name|gchar
modifier|*
DECL|function|filters_parse_operation (Gimp * gimp,const gchar * operation_str,const gchar * icon_name,GimpObject ** settings)
name|filters_parse_operation
parameter_list|(
name|Gimp
modifier|*
name|gimp
parameter_list|,
specifier|const
name|gchar
modifier|*
name|operation_str
parameter_list|,
specifier|const
name|gchar
modifier|*
name|icon_name
parameter_list|,
name|GimpObject
modifier|*
modifier|*
name|settings
parameter_list|)
block|{
specifier|const
name|gchar
modifier|*
name|newline
init|=
name|strchr
argument_list|(
name|operation_str
argument_list|,
literal|'\n'
argument_list|)
decl_stmt|;
operator|*
name|settings
operator|=
name|NULL
expr_stmt|;
if|if
condition|(
name|newline
condition|)
block|{
name|gchar
modifier|*
name|operation
decl_stmt|;
specifier|const
name|gchar
modifier|*
name|serialized
decl_stmt|;
name|operation
operator|=
name|g_strndup
argument_list|(
name|operation_str
argument_list|,
name|newline
operator|-
name|operation_str
argument_list|)
expr_stmt|;
name|serialized
operator|=
name|newline
operator|+
literal|1
expr_stmt|;
if|if
condition|(
operator|*
name|serialized
condition|)
block|{
name|GError
modifier|*
name|error
init|=
name|NULL
decl_stmt|;
operator|*
name|settings
operator|=
name|g_object_new
argument_list|(
name|gimp_operation_config_get_type
argument_list|(
name|gimp
argument_list|,
name|operation
argument_list|,
name|icon_name
argument_list|,
name|GIMP_TYPE_SETTINGS
argument_list|)
argument_list|,
name|NULL
argument_list|)
expr_stmt|;
if|if
condition|(
operator|!
name|gimp_config_deserialize_string
argument_list|(
name|GIMP_CONFIG
argument_list|(
operator|*
name|settings
argument_list|)
argument_list|,
name|serialized
argument_list|,
operator|-
literal|1
argument_list|,
name|NULL
argument_list|,
operator|&
name|error
argument_list|)
condition|)
block|{
name|g_warning
argument_list|(
literal|"filters_parse_operation: deserializing hardcoded "
literal|"operation settings failed: %s"
argument_list|,
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
name|g_object_unref
argument_list|(
operator|*
name|settings
argument_list|)
expr_stmt|;
operator|*
name|settings
operator|=
name|NULL
expr_stmt|;
block|}
block|}
return|return
name|operation
return|;
block|}
return|return
name|g_strdup
argument_list|(
name|operation_str
argument_list|)
return|;
block|}
end_function

begin_function
specifier|static
name|void
DECL|function|filters_run_procedure (Gimp * gimp,GimpDisplay * display,GimpProcedure * procedure,GimpRunMode run_mode)
name|filters_run_procedure
parameter_list|(
name|Gimp
modifier|*
name|gimp
parameter_list|,
name|GimpDisplay
modifier|*
name|display
parameter_list|,
name|GimpProcedure
modifier|*
name|procedure
parameter_list|,
name|GimpRunMode
name|run_mode
parameter_list|)
block|{
name|GimpObject
modifier|*
name|settings
init|=
name|NULL
decl_stmt|;
name|GimpValueArray
modifier|*
name|args
decl_stmt|;
if|if
condition|(
name|GIMP_IS_GEGL_PROCEDURE
argument_list|(
name|procedure
argument_list|)
condition|)
block|{
name|GimpGeglProcedure
modifier|*
name|gegl_procedure
init|=
name|GIMP_GEGL_PROCEDURE
argument_list|(
name|procedure
argument_list|)
decl_stmt|;
if|if
condition|(
name|gegl_procedure
operator|->
name|default_run_mode
operator|==
name|GIMP_RUN_NONINTERACTIVE
condition|)
name|run_mode
operator|=
name|GIMP_RUN_NONINTERACTIVE
expr_stmt|;
name|settings
operator|=
name|gegl_procedure
operator|->
name|default_settings
expr_stmt|;
block|}
name|args
operator|=
name|procedure_commands_get_display_args
argument_list|(
name|procedure
argument_list|,
name|display
argument_list|,
name|settings
argument_list|)
expr_stmt|;
if|if
condition|(
name|args
condition|)
block|{
name|gboolean
name|success
init|=
name|FALSE
decl_stmt|;
if|if
condition|(
name|run_mode
operator|==
name|GIMP_RUN_NONINTERACTIVE
condition|)
block|{
name|success
operator|=
name|procedure_commands_run_procedure
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
name|args
argument_list|)
expr_stmt|;
block|}
else|else
block|{
name|success
operator|=
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
name|run_mode
argument_list|,
name|args
argument_list|,
name|display
argument_list|)
expr_stmt|;
block|}
if|if
condition|(
name|success
condition|)
name|gimp_filter_history_add
argument_list|(
name|gimp
argument_list|,
name|procedure
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

end_unit

