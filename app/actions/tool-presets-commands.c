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
file|"core/gimptoolinfo.h"
end_include

begin_include
include|#
directive|include
file|"core/gimptoolpreset.h"
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
file|"tool-presets-commands.h"
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
DECL|function|tool_presets_save_cmd_callback (GimpAction * action,GVariant * value,gpointer data)
name|tool_presets_save_cmd_callback
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
name|GimpContainerEditor
modifier|*
name|editor
init|=
name|GIMP_CONTAINER_EDITOR
argument_list|(
name|data
argument_list|)
decl_stmt|;
name|GimpContext
modifier|*
name|context
decl_stmt|;
name|GimpToolPreset
modifier|*
name|preset
decl_stmt|;
name|GimpToolInfo
modifier|*
name|tool_info
decl_stmt|;
name|context
operator|=
name|gimp_container_view_get_context
argument_list|(
name|editor
operator|->
name|view
argument_list|)
expr_stmt|;
name|preset
operator|=
name|gimp_context_get_tool_preset
argument_list|(
name|context
argument_list|)
expr_stmt|;
name|tool_info
operator|=
name|gimp_context_get_tool
argument_list|(
name|gimp_get_user_context
argument_list|(
name|context
operator|->
name|gimp
argument_list|)
argument_list|)
expr_stmt|;
if|if
condition|(
name|tool_info
operator|&&
name|preset
condition|)
block|{
name|GimpToolInfo
modifier|*
name|preset_tool
decl_stmt|;
name|preset_tool
operator|=
name|gimp_context_get_tool
argument_list|(
name|GIMP_CONTEXT
argument_list|(
name|preset
operator|->
name|tool_options
argument_list|)
argument_list|)
expr_stmt|;
if|if
condition|(
name|tool_info
operator|!=
name|preset_tool
condition|)
block|{
name|gimp_message
argument_list|(
name|context
operator|->
name|gimp
argument_list|,
name|G_OBJECT
argument_list|(
name|editor
argument_list|)
argument_list|,
name|GIMP_MESSAGE_WARNING
argument_list|,
name|_
argument_list|(
literal|"Can't save '%s' tool options to an "
literal|"existing '%s' tool preset."
argument_list|)
argument_list|,
name|tool_info
operator|->
name|label
argument_list|,
name|preset_tool
operator|->
name|label
argument_list|)
expr_stmt|;
return|return;
block|}
name|gimp_config_sync
argument_list|(
name|G_OBJECT
argument_list|(
name|tool_info
operator|->
name|tool_options
argument_list|)
argument_list|,
name|G_OBJECT
argument_list|(
name|preset
operator|->
name|tool_options
argument_list|)
argument_list|,
literal|0
argument_list|)
expr_stmt|;
block|}
block|}
end_function

begin_function
name|void
DECL|function|tool_presets_restore_cmd_callback (GimpAction * action,GVariant * value,gpointer data)
name|tool_presets_restore_cmd_callback
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
name|GimpContainerEditor
modifier|*
name|editor
init|=
name|GIMP_CONTAINER_EDITOR
argument_list|(
name|data
argument_list|)
decl_stmt|;
name|GimpContext
modifier|*
name|context
decl_stmt|;
name|GimpToolPreset
modifier|*
name|preset
decl_stmt|;
name|context
operator|=
name|gimp_container_view_get_context
argument_list|(
name|editor
operator|->
name|view
argument_list|)
expr_stmt|;
name|preset
operator|=
name|gimp_context_get_tool_preset
argument_list|(
name|context
argument_list|)
expr_stmt|;
if|if
condition|(
name|preset
condition|)
name|gimp_context_tool_preset_changed
argument_list|(
name|gimp_get_user_context
argument_list|(
name|context
operator|->
name|gimp
argument_list|)
argument_list|)
expr_stmt|;
block|}
end_function

end_unit

