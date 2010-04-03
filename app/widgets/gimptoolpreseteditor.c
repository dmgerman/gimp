begin_unit|revision:0.9.5;language:C;cregit-version:0.0.1
begin_comment
comment|/* GIMP - The GNU Image Manipulation Program  * Copyright (C) 1995 Spencer Kimball and Peter Mattis  *  *  * This program is free software: you can redistribute it and/or modify  * it under the terms of the GNU General Public License as published by  * the Free Software Foundation; either version 3 of the License, or  * (at your option) any later version.  *  * This program is distributed in the hope that it will be useful,  * but WITHOUT ANY WARRANTY; without even the implied warranty of  * MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the  * GNU General Public License for more details.  *  * You should have received a copy of the GNU General Public License  * along with this program.  If not, see<http://www.gnu.org/licenses/>.  */
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
file|"widgets-types.h"
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
file|"core/gimptoolpreset.h"
end_include

begin_include
include|#
directive|include
file|"gimpdocked.h"
end_include

begin_include
include|#
directive|include
file|"gimptoolpreseteditor.h"
end_include

begin_include
include|#
directive|include
file|"gimpmenufactory.h"
end_include

begin_include
include|#
directive|include
file|"gimppropwidgets.h"
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
name|GObject
modifier|*
name|gimp_tool_preset_editor_constructor
parameter_list|(
name|GType
name|type
parameter_list|,
name|guint
name|n_params
parameter_list|,
name|GObjectConstructParam
modifier|*
name|params
parameter_list|)
function_decl|;
end_function_decl

begin_function_decl
specifier|static
name|void
name|gimp_tool_preset_editor_set_data
parameter_list|(
name|GimpDataEditor
modifier|*
name|editor
parameter_list|,
name|GimpData
modifier|*
name|data
parameter_list|)
function_decl|;
end_function_decl

begin_function_decl
specifier|static
name|void
name|gimp_tool_preset_editor_notify_model
parameter_list|(
name|GimpToolPreset
modifier|*
name|options
parameter_list|,
specifier|const
name|GParamSpec
modifier|*
name|pspec
parameter_list|,
name|GimpToolPresetEditor
modifier|*
name|editor
parameter_list|)
function_decl|;
end_function_decl

begin_function_decl
specifier|static
name|void
name|gimp_tool_preset_editor_notify_data
parameter_list|(
name|GimpToolPreset
modifier|*
name|options
parameter_list|,
specifier|const
name|GParamSpec
modifier|*
name|pspec
parameter_list|,
name|GimpToolPresetEditor
modifier|*
name|editor
parameter_list|)
function_decl|;
end_function_decl

begin_macro
DECL|function|G_DEFINE_TYPE_WITH_CODE (GimpToolPresetEditor,gimp_tool_preset_editor,GIMP_TYPE_DATA_EDITOR,G_IMPLEMENT_INTERFACE (GIMP_TYPE_DOCKED,NULL))
name|G_DEFINE_TYPE_WITH_CODE
argument_list|(
argument|GimpToolPresetEditor
argument_list|,
argument|gimp_tool_preset_editor
argument_list|,
argument|GIMP_TYPE_DATA_EDITOR
argument_list|,
argument|G_IMPLEMENT_INTERFACE (GIMP_TYPE_DOCKED, NULL)
argument_list|)
end_macro

begin_define
DECL|macro|parent_class
define|#
directive|define
name|parent_class
value|gimp_tool_preset_editor_parent_class
end_define

begin_function
specifier|static
name|void
name|gimp_tool_preset_editor_class_init
parameter_list|(
name|GimpToolPresetEditorClass
modifier|*
name|klass
parameter_list|)
block|{
name|GObjectClass
modifier|*
name|object_class
init|=
name|G_OBJECT_CLASS
argument_list|(
name|klass
argument_list|)
decl_stmt|;
name|GimpDataEditorClass
modifier|*
name|editor_class
init|=
name|GIMP_DATA_EDITOR_CLASS
argument_list|(
name|klass
argument_list|)
decl_stmt|;
name|object_class
operator|->
name|constructor
operator|=
name|gimp_tool_preset_editor_constructor
expr_stmt|;
name|editor_class
operator|->
name|set_data
operator|=
name|gimp_tool_preset_editor_set_data
expr_stmt|;
name|editor_class
operator|->
name|title
operator|=
name|_
argument_list|(
literal|"Tool Preset Editor"
argument_list|)
expr_stmt|;
block|}
end_function

begin_function
specifier|static
name|void
DECL|function|gimp_tool_preset_editor_init (GimpToolPresetEditor * editor)
name|gimp_tool_preset_editor_init
parameter_list|(
name|GimpToolPresetEditor
modifier|*
name|editor
parameter_list|)
block|{
name|GimpDataEditor
modifier|*
name|data_editor
init|=
name|GIMP_DATA_EDITOR
argument_list|(
name|editor
argument_list|)
decl_stmt|;
comment|/*Nuffink*/
block|}
end_function

begin_function
specifier|static
name|GObject
modifier|*
DECL|function|gimp_tool_preset_editor_constructor (GType type,guint n_params,GObjectConstructParam * params)
name|gimp_tool_preset_editor_constructor
parameter_list|(
name|GType
name|type
parameter_list|,
name|guint
name|n_params
parameter_list|,
name|GObjectConstructParam
modifier|*
name|params
parameter_list|)
block|{
name|GObject
modifier|*
name|object
decl_stmt|;
name|object
operator|=
name|G_OBJECT_CLASS
argument_list|(
name|parent_class
argument_list|)
operator|->
name|constructor
argument_list|(
name|type
argument_list|,
name|n_params
argument_list|,
name|params
argument_list|)
expr_stmt|;
name|gimp_docked_set_show_button_bar
argument_list|(
name|GIMP_DOCKED
argument_list|(
name|object
argument_list|)
argument_list|,
name|FALSE
argument_list|)
expr_stmt|;
return|return
name|object
return|;
block|}
end_function

begin_function
specifier|static
name|void
DECL|function|gimp_tool_preset_editor_set_data (GimpDataEditor * editor,GimpData * data)
name|gimp_tool_preset_editor_set_data
parameter_list|(
name|GimpDataEditor
modifier|*
name|editor
parameter_list|,
name|GimpData
modifier|*
name|data
parameter_list|)
block|{
name|GimpToolPresetEditor
modifier|*
name|tool_preset_editor
init|=
name|GIMP_TOOL_PRESET_EDITOR
argument_list|(
name|editor
argument_list|)
decl_stmt|;
if|if
condition|(
name|editor
operator|->
name|data
condition|)
name|g_signal_handlers_disconnect_by_func
argument_list|(
name|editor
operator|->
name|data
argument_list|,
name|gimp_tool_preset_editor_notify_data
argument_list|,
name|editor
argument_list|)
expr_stmt|;
name|GIMP_DATA_EDITOR_CLASS
argument_list|(
name|parent_class
argument_list|)
operator|->
name|set_data
argument_list|(
name|editor
argument_list|,
name|data
argument_list|)
expr_stmt|;
if|if
condition|(
name|editor
operator|->
name|data
condition|)
block|{
name|g_signal_handlers_block_by_func
argument_list|(
name|tool_preset_editor
operator|->
name|tool_preset_model
argument_list|,
name|gimp_tool_preset_editor_notify_model
argument_list|,
name|editor
argument_list|)
expr_stmt|;
name|gimp_config_copy
argument_list|(
name|GIMP_CONFIG
argument_list|(
name|editor
operator|->
name|data
argument_list|)
argument_list|,
name|GIMP_CONFIG
argument_list|(
name|tool_preset_editor
operator|->
name|tool_preset_model
argument_list|)
argument_list|,
name|GIMP_CONFIG_PARAM_SERIALIZE
argument_list|)
expr_stmt|;
name|g_signal_handlers_unblock_by_func
argument_list|(
name|tool_preset_editor
operator|->
name|tool_preset_model
argument_list|,
name|gimp_tool_preset_editor_notify_model
argument_list|,
name|editor
argument_list|)
expr_stmt|;
name|g_signal_connect
argument_list|(
name|editor
operator|->
name|data
argument_list|,
literal|"notify"
argument_list|,
name|G_CALLBACK
argument_list|(
name|gimp_tool_preset_editor_notify_data
argument_list|)
argument_list|,
name|editor
argument_list|)
expr_stmt|;
block|}
block|}
end_function

begin_comment
comment|/*  public functions  */
end_comment

begin_function
name|GtkWidget
modifier|*
DECL|function|gimp_tool_preset_editor_new (GimpContext * context,GimpMenuFactory * menu_factory)
name|gimp_tool_preset_editor_new
parameter_list|(
name|GimpContext
modifier|*
name|context
parameter_list|,
name|GimpMenuFactory
modifier|*
name|menu_factory
parameter_list|)
block|{
name|g_return_val_if_fail
argument_list|(
name|GIMP_IS_MENU_FACTORY
argument_list|(
name|menu_factory
argument_list|)
argument_list|,
name|NULL
argument_list|)
expr_stmt|;
name|g_return_val_if_fail
argument_list|(
name|GIMP_IS_CONTEXT
argument_list|(
name|context
argument_list|)
argument_list|,
name|NULL
argument_list|)
expr_stmt|;
return|return
name|g_object_new
argument_list|(
name|GIMP_TYPE_TOOL_PRESET_EDITOR
argument_list|,
literal|"menu-factory"
argument_list|,
name|menu_factory
argument_list|,
literal|"menu-identifier"
argument_list|,
literal|"<ToolPresetEditor>"
argument_list|,
literal|"ui-path"
argument_list|,
literal|"/tool_preset-editor-popup"
argument_list|,
literal|"data-factory"
argument_list|,
name|context
operator|->
name|gimp
operator|->
name|tool_preset_factory
argument_list|,
literal|"context"
argument_list|,
name|context
argument_list|,
literal|"data"
argument_list|,
name|gimp_context_get_tool_preset
argument_list|(
name|context
argument_list|)
argument_list|,
name|NULL
argument_list|)
return|;
block|}
end_function

begin_comment
comment|/*  private functions  */
end_comment

begin_function
specifier|static
name|void
DECL|function|gimp_tool_preset_editor_notify_model (GimpToolPreset * options,const GParamSpec * pspec,GimpToolPresetEditor * editor)
name|gimp_tool_preset_editor_notify_model
parameter_list|(
name|GimpToolPreset
modifier|*
name|options
parameter_list|,
specifier|const
name|GParamSpec
modifier|*
name|pspec
parameter_list|,
name|GimpToolPresetEditor
modifier|*
name|editor
parameter_list|)
block|{
name|GimpDataEditor
modifier|*
name|data_editor
init|=
name|GIMP_DATA_EDITOR
argument_list|(
name|editor
argument_list|)
decl_stmt|;
if|if
condition|(
name|data_editor
operator|->
name|data
condition|)
block|{
name|g_signal_handlers_block_by_func
argument_list|(
name|data_editor
operator|->
name|data
argument_list|,
name|gimp_tool_preset_editor_notify_data
argument_list|,
name|editor
argument_list|)
expr_stmt|;
name|gimp_config_copy
argument_list|(
name|GIMP_CONFIG
argument_list|(
name|editor
operator|->
name|tool_preset_model
argument_list|)
argument_list|,
name|GIMP_CONFIG
argument_list|(
name|data_editor
operator|->
name|data
argument_list|)
argument_list|,
name|GIMP_CONFIG_PARAM_SERIALIZE
argument_list|)
expr_stmt|;
name|g_signal_handlers_unblock_by_func
argument_list|(
name|data_editor
operator|->
name|data
argument_list|,
name|gimp_tool_preset_editor_notify_data
argument_list|,
name|editor
argument_list|)
expr_stmt|;
block|}
block|}
end_function

begin_function
specifier|static
name|void
DECL|function|gimp_tool_preset_editor_notify_data (GimpToolPreset * options,const GParamSpec * pspec,GimpToolPresetEditor * editor)
name|gimp_tool_preset_editor_notify_data
parameter_list|(
name|GimpToolPreset
modifier|*
name|options
parameter_list|,
specifier|const
name|GParamSpec
modifier|*
name|pspec
parameter_list|,
name|GimpToolPresetEditor
modifier|*
name|editor
parameter_list|)
block|{
name|GimpDataEditor
modifier|*
name|data_editor
init|=
name|GIMP_DATA_EDITOR
argument_list|(
name|editor
argument_list|)
decl_stmt|;
name|g_signal_handlers_block_by_func
argument_list|(
name|editor
operator|->
name|tool_preset_model
argument_list|,
name|gimp_tool_preset_editor_notify_model
argument_list|,
name|editor
argument_list|)
expr_stmt|;
name|gimp_config_copy
argument_list|(
name|GIMP_CONFIG
argument_list|(
name|data_editor
operator|->
name|data
argument_list|)
argument_list|,
name|GIMP_CONFIG
argument_list|(
name|editor
operator|->
name|tool_preset_model
argument_list|)
argument_list|,
name|GIMP_CONFIG_PARAM_SERIALIZE
argument_list|)
expr_stmt|;
name|g_signal_handlers_unblock_by_func
argument_list|(
name|editor
operator|->
name|tool_preset_model
argument_list|,
name|gimp_tool_preset_editor_notify_model
argument_list|,
name|editor
argument_list|)
expr_stmt|;
block|}
end_function

end_unit

