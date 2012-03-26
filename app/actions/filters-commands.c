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
operator|!
name|GIMP_IS_OPERATION_TOOL
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
name|tool_manager_control_active
argument_list|(
name|image
operator|->
name|gimp
argument_list|,
name|GIMP_TOOL_ACTION_HALT
argument_list|,
name|display
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

end_unit

