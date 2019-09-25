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
file|"core/gimptoolinfo.h"
end_include

begin_include
include|#
directive|include
file|"core/gimptooloptions.h"
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

begin_struct
DECL|struct|_GimpToolPresetEditorPrivate
struct|struct
name|_GimpToolPresetEditorPrivate
block|{
DECL|member|tool_preset_model
name|GimpToolPreset
modifier|*
name|tool_preset_model
decl_stmt|;
DECL|member|tool_icon
name|GtkWidget
modifier|*
name|tool_icon
decl_stmt|;
DECL|member|tool_label
name|GtkWidget
modifier|*
name|tool_label
decl_stmt|;
DECL|member|fg_bg_toggle
name|GtkWidget
modifier|*
name|fg_bg_toggle
decl_stmt|;
DECL|member|brush_toggle
name|GtkWidget
modifier|*
name|brush_toggle
decl_stmt|;
DECL|member|dynamics_toggle
name|GtkWidget
modifier|*
name|dynamics_toggle
decl_stmt|;
DECL|member|mybrush_toggle
name|GtkWidget
modifier|*
name|mybrush_toggle
decl_stmt|;
DECL|member|gradient_toggle
name|GtkWidget
modifier|*
name|gradient_toggle
decl_stmt|;
DECL|member|pattern_toggle
name|GtkWidget
modifier|*
name|pattern_toggle
decl_stmt|;
DECL|member|palette_toggle
name|GtkWidget
modifier|*
name|palette_toggle
decl_stmt|;
DECL|member|font_toggle
name|GtkWidget
modifier|*
name|font_toggle
decl_stmt|;
block|}
struct|;
end_struct

begin_comment
comment|/*  local function prototypes  */
end_comment

begin_function_decl
specifier|static
name|void
name|gimp_tool_preset_editor_constructed
parameter_list|(
name|GObject
modifier|*
name|object
parameter_list|)
function_decl|;
end_function_decl

begin_function_decl
specifier|static
name|void
name|gimp_tool_preset_editor_finalize
parameter_list|(
name|GObject
modifier|*
name|object
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
name|gimp_tool_preset_editor_sync_data
parameter_list|(
name|GimpToolPresetEditor
modifier|*
name|editor
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
DECL|function|G_DEFINE_TYPE_WITH_CODE (GimpToolPresetEditor,gimp_tool_preset_editor,GIMP_TYPE_DATA_EDITOR,G_ADD_PRIVATE (GimpToolPresetEditor)G_IMPLEMENT_INTERFACE (GIMP_TYPE_DOCKED,NULL))
name|G_DEFINE_TYPE_WITH_CODE
argument_list|(
argument|GimpToolPresetEditor
argument_list|,
argument|gimp_tool_preset_editor
argument_list|,
argument|GIMP_TYPE_DATA_EDITOR
argument_list|,
argument|G_ADD_PRIVATE (GimpToolPresetEditor)                          G_IMPLEMENT_INTERFACE (GIMP_TYPE_DOCKED, NULL)
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
name|constructed
operator|=
name|gimp_tool_preset_editor_constructed
expr_stmt|;
name|object_class
operator|->
name|finalize
operator|=
name|gimp_tool_preset_editor_finalize
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
name|editor
operator|->
name|priv
operator|=
name|gimp_tool_preset_editor_get_instance_private
argument_list|(
name|editor
argument_list|)
expr_stmt|;
block|}
end_function

begin_function
specifier|static
name|void
DECL|function|gimp_tool_preset_editor_constructed (GObject * object)
name|gimp_tool_preset_editor_constructed
parameter_list|(
name|GObject
modifier|*
name|object
parameter_list|)
block|{
name|GimpToolPresetEditor
modifier|*
name|editor
init|=
name|GIMP_TOOL_PRESET_EDITOR
argument_list|(
name|object
argument_list|)
decl_stmt|;
name|GimpDataEditor
modifier|*
name|data_editor
init|=
name|GIMP_DATA_EDITOR
argument_list|(
name|editor
argument_list|)
decl_stmt|;
name|GimpToolPreset
modifier|*
name|preset
decl_stmt|;
name|GtkWidget
modifier|*
name|hbox
decl_stmt|;
name|GtkWidget
modifier|*
name|label
decl_stmt|;
name|GtkWidget
modifier|*
name|button
decl_stmt|;
name|G_OBJECT_CLASS
argument_list|(
name|parent_class
argument_list|)
operator|->
name|constructed
argument_list|(
name|object
argument_list|)
expr_stmt|;
name|preset
operator|=
name|editor
operator|->
name|priv
operator|->
name|tool_preset_model
operator|=
name|g_object_new
argument_list|(
name|GIMP_TYPE_TOOL_PRESET
argument_list|,
literal|"gimp"
argument_list|,
name|data_editor
operator|->
name|context
operator|->
name|gimp
argument_list|,
name|NULL
argument_list|)
expr_stmt|;
name|g_signal_connect
argument_list|(
name|preset
argument_list|,
literal|"notify"
argument_list|,
name|G_CALLBACK
argument_list|(
name|gimp_tool_preset_editor_notify_model
argument_list|)
argument_list|,
name|editor
argument_list|)
expr_stmt|;
name|hbox
operator|=
name|gtk_box_new
argument_list|(
name|GTK_ORIENTATION_HORIZONTAL
argument_list|,
literal|2
argument_list|)
expr_stmt|;
name|gtk_box_pack_start
argument_list|(
name|GTK_BOX
argument_list|(
name|data_editor
argument_list|)
argument_list|,
name|hbox
argument_list|,
name|FALSE
argument_list|,
name|FALSE
argument_list|,
literal|0
argument_list|)
expr_stmt|;
name|gtk_widget_show
argument_list|(
name|hbox
argument_list|)
expr_stmt|;
name|editor
operator|->
name|priv
operator|->
name|tool_icon
operator|=
name|gtk_image_new
argument_list|()
expr_stmt|;
name|gtk_box_pack_start
argument_list|(
name|GTK_BOX
argument_list|(
name|hbox
argument_list|)
argument_list|,
name|editor
operator|->
name|priv
operator|->
name|tool_icon
argument_list|,
name|FALSE
argument_list|,
name|FALSE
argument_list|,
literal|0
argument_list|)
expr_stmt|;
name|gtk_widget_show
argument_list|(
name|editor
operator|->
name|priv
operator|->
name|tool_icon
argument_list|)
expr_stmt|;
name|editor
operator|->
name|priv
operator|->
name|tool_label
operator|=
name|gtk_label_new
argument_list|(
literal|""
argument_list|)
expr_stmt|;
name|gimp_label_set_attributes
argument_list|(
name|GTK_LABEL
argument_list|(
name|editor
operator|->
name|priv
operator|->
name|tool_label
argument_list|)
argument_list|,
name|PANGO_ATTR_STYLE
argument_list|,
name|PANGO_STYLE_ITALIC
argument_list|,
operator|-
literal|1
argument_list|)
expr_stmt|;
name|gtk_box_pack_start
argument_list|(
name|GTK_BOX
argument_list|(
name|hbox
argument_list|)
argument_list|,
name|editor
operator|->
name|priv
operator|->
name|tool_label
argument_list|,
name|FALSE
argument_list|,
name|FALSE
argument_list|,
literal|0
argument_list|)
expr_stmt|;
name|gtk_widget_show
argument_list|(
name|editor
operator|->
name|priv
operator|->
name|tool_label
argument_list|)
expr_stmt|;
name|hbox
operator|=
name|gtk_box_new
argument_list|(
name|GTK_ORIENTATION_HORIZONTAL
argument_list|,
literal|2
argument_list|)
expr_stmt|;
name|gtk_box_pack_start
argument_list|(
name|GTK_BOX
argument_list|(
name|data_editor
argument_list|)
argument_list|,
name|hbox
argument_list|,
name|FALSE
argument_list|,
name|FALSE
argument_list|,
literal|0
argument_list|)
expr_stmt|;
name|gtk_widget_show
argument_list|(
name|hbox
argument_list|)
expr_stmt|;
name|label
operator|=
name|gtk_label_new
argument_list|(
name|_
argument_list|(
literal|"Icon:"
argument_list|)
argument_list|)
expr_stmt|;
name|gtk_box_pack_start
argument_list|(
name|GTK_BOX
argument_list|(
name|hbox
argument_list|)
argument_list|,
name|label
argument_list|,
name|FALSE
argument_list|,
name|FALSE
argument_list|,
literal|0
argument_list|)
expr_stmt|;
name|gtk_widget_show
argument_list|(
name|label
argument_list|)
expr_stmt|;
name|button
operator|=
name|gimp_prop_icon_picker_new
argument_list|(
name|GIMP_VIEWABLE
argument_list|(
name|preset
argument_list|)
argument_list|,
name|data_editor
operator|->
name|context
operator|->
name|gimp
argument_list|)
expr_stmt|;
name|gtk_box_pack_start
argument_list|(
name|GTK_BOX
argument_list|(
name|hbox
argument_list|)
argument_list|,
name|button
argument_list|,
name|FALSE
argument_list|,
name|FALSE
argument_list|,
literal|0
argument_list|)
expr_stmt|;
name|button
operator|=
name|editor
operator|->
name|priv
operator|->
name|fg_bg_toggle
operator|=
name|gimp_prop_check_button_new
argument_list|(
name|G_OBJECT
argument_list|(
name|preset
argument_list|)
argument_list|,
literal|"use-fg-bg"
argument_list|,
name|NULL
argument_list|)
expr_stmt|;
name|gtk_box_pack_start
argument_list|(
name|GTK_BOX
argument_list|(
name|data_editor
argument_list|)
argument_list|,
name|button
argument_list|,
name|FALSE
argument_list|,
name|FALSE
argument_list|,
literal|0
argument_list|)
expr_stmt|;
name|button
operator|=
name|editor
operator|->
name|priv
operator|->
name|brush_toggle
operator|=
name|gimp_prop_check_button_new
argument_list|(
name|G_OBJECT
argument_list|(
name|preset
argument_list|)
argument_list|,
literal|"use-brush"
argument_list|,
name|NULL
argument_list|)
expr_stmt|;
name|gtk_box_pack_start
argument_list|(
name|GTK_BOX
argument_list|(
name|data_editor
argument_list|)
argument_list|,
name|button
argument_list|,
name|FALSE
argument_list|,
name|FALSE
argument_list|,
literal|0
argument_list|)
expr_stmt|;
name|button
operator|=
name|editor
operator|->
name|priv
operator|->
name|dynamics_toggle
operator|=
name|gimp_prop_check_button_new
argument_list|(
name|G_OBJECT
argument_list|(
name|preset
argument_list|)
argument_list|,
literal|"use-dynamics"
argument_list|,
name|NULL
argument_list|)
expr_stmt|;
name|gtk_box_pack_start
argument_list|(
name|GTK_BOX
argument_list|(
name|data_editor
argument_list|)
argument_list|,
name|button
argument_list|,
name|FALSE
argument_list|,
name|FALSE
argument_list|,
literal|0
argument_list|)
expr_stmt|;
name|button
operator|=
name|editor
operator|->
name|priv
operator|->
name|mybrush_toggle
operator|=
name|gimp_prop_check_button_new
argument_list|(
name|G_OBJECT
argument_list|(
name|preset
argument_list|)
argument_list|,
literal|"use-mypaint-brush"
argument_list|,
name|NULL
argument_list|)
expr_stmt|;
name|gtk_box_pack_start
argument_list|(
name|GTK_BOX
argument_list|(
name|data_editor
argument_list|)
argument_list|,
name|button
argument_list|,
name|FALSE
argument_list|,
name|FALSE
argument_list|,
literal|0
argument_list|)
expr_stmt|;
name|button
operator|=
name|editor
operator|->
name|priv
operator|->
name|gradient_toggle
operator|=
name|gimp_prop_check_button_new
argument_list|(
name|G_OBJECT
argument_list|(
name|preset
argument_list|)
argument_list|,
literal|"use-gradient"
argument_list|,
name|NULL
argument_list|)
expr_stmt|;
name|gtk_box_pack_start
argument_list|(
name|GTK_BOX
argument_list|(
name|data_editor
argument_list|)
argument_list|,
name|button
argument_list|,
name|FALSE
argument_list|,
name|FALSE
argument_list|,
literal|0
argument_list|)
expr_stmt|;
name|button
operator|=
name|editor
operator|->
name|priv
operator|->
name|pattern_toggle
operator|=
name|gimp_prop_check_button_new
argument_list|(
name|G_OBJECT
argument_list|(
name|preset
argument_list|)
argument_list|,
literal|"use-pattern"
argument_list|,
name|NULL
argument_list|)
expr_stmt|;
name|gtk_box_pack_start
argument_list|(
name|GTK_BOX
argument_list|(
name|data_editor
argument_list|)
argument_list|,
name|button
argument_list|,
name|FALSE
argument_list|,
name|FALSE
argument_list|,
literal|0
argument_list|)
expr_stmt|;
name|button
operator|=
name|editor
operator|->
name|priv
operator|->
name|palette_toggle
operator|=
name|gimp_prop_check_button_new
argument_list|(
name|G_OBJECT
argument_list|(
name|preset
argument_list|)
argument_list|,
literal|"use-palette"
argument_list|,
name|NULL
argument_list|)
expr_stmt|;
name|gtk_box_pack_start
argument_list|(
name|GTK_BOX
argument_list|(
name|data_editor
argument_list|)
argument_list|,
name|button
argument_list|,
name|FALSE
argument_list|,
name|FALSE
argument_list|,
literal|0
argument_list|)
expr_stmt|;
name|button
operator|=
name|editor
operator|->
name|priv
operator|->
name|font_toggle
operator|=
name|gimp_prop_check_button_new
argument_list|(
name|G_OBJECT
argument_list|(
name|preset
argument_list|)
argument_list|,
literal|"use-font"
argument_list|,
name|NULL
argument_list|)
expr_stmt|;
name|gtk_box_pack_start
argument_list|(
name|GTK_BOX
argument_list|(
name|data_editor
argument_list|)
argument_list|,
name|button
argument_list|,
name|FALSE
argument_list|,
name|FALSE
argument_list|,
literal|0
argument_list|)
expr_stmt|;
name|button
operator|=
name|gimp_editor_add_action_button
argument_list|(
name|GIMP_EDITOR
argument_list|(
name|editor
argument_list|)
argument_list|,
literal|"tool-preset-editor"
argument_list|,
literal|"tool-preset-editor-save"
argument_list|,
name|NULL
argument_list|)
expr_stmt|;
name|button
operator|=
name|gimp_editor_add_action_button
argument_list|(
name|GIMP_EDITOR
argument_list|(
name|editor
argument_list|)
argument_list|,
literal|"tool-preset-editor"
argument_list|,
literal|"tool-preset-editor-restore"
argument_list|,
name|NULL
argument_list|)
expr_stmt|;
if|if
condition|(
name|data_editor
operator|->
name|data
condition|)
name|gimp_tool_preset_editor_sync_data
argument_list|(
name|editor
argument_list|)
expr_stmt|;
block|}
end_function

begin_function
specifier|static
name|void
DECL|function|gimp_tool_preset_editor_finalize (GObject * object)
name|gimp_tool_preset_editor_finalize
parameter_list|(
name|GObject
modifier|*
name|object
parameter_list|)
block|{
name|GimpToolPresetEditor
modifier|*
name|editor
init|=
name|GIMP_TOOL_PRESET_EDITOR
argument_list|(
name|object
argument_list|)
decl_stmt|;
name|g_clear_object
argument_list|(
operator|&
name|editor
operator|->
name|priv
operator|->
name|tool_preset_model
argument_list|)
expr_stmt|;
name|G_OBJECT_CLASS
argument_list|(
name|parent_class
argument_list|)
operator|->
name|finalize
argument_list|(
name|object
argument_list|)
expr_stmt|;
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
name|preset_editor
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
if|if
condition|(
name|preset_editor
operator|->
name|priv
operator|->
name|tool_preset_model
condition|)
name|gimp_tool_preset_editor_sync_data
argument_list|(
name|preset_editor
argument_list|)
expr_stmt|;
block|}
name|gtk_widget_set_sensitive
argument_list|(
name|GTK_WIDGET
argument_list|(
name|editor
argument_list|)
argument_list|,
name|editor
operator|->
name|data_editable
argument_list|)
expr_stmt|;
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
literal|"/tool-preset-editor-popup"
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
DECL|function|gimp_tool_preset_editor_sync_data (GimpToolPresetEditor * editor)
name|gimp_tool_preset_editor_sync_data
parameter_list|(
name|GimpToolPresetEditor
modifier|*
name|editor
parameter_list|)
block|{
name|GimpToolPresetEditorPrivate
modifier|*
name|priv
init|=
name|editor
operator|->
name|priv
decl_stmt|;
name|GimpDataEditor
modifier|*
name|data_editor
init|=
name|GIMP_DATA_EDITOR
argument_list|(
name|editor
argument_list|)
decl_stmt|;
name|GimpToolPreset
modifier|*
name|preset
decl_stmt|;
name|GimpToolInfo
modifier|*
name|tool_info
decl_stmt|;
name|GimpContextPropMask
name|serialize_props
decl_stmt|;
specifier|const
name|gchar
modifier|*
name|icon_name
decl_stmt|;
name|gchar
modifier|*
name|label
decl_stmt|;
name|g_signal_handlers_block_by_func
argument_list|(
name|priv
operator|->
name|tool_preset_model
argument_list|,
name|gimp_tool_preset_editor_notify_model
argument_list|,
name|editor
argument_list|)
expr_stmt|;
name|gimp_config_sync
argument_list|(
name|G_OBJECT
argument_list|(
name|data_editor
operator|->
name|data
argument_list|)
argument_list|,
name|G_OBJECT
argument_list|(
name|priv
operator|->
name|tool_preset_model
argument_list|)
argument_list|,
name|GIMP_CONFIG_PARAM_SERIALIZE
argument_list|)
expr_stmt|;
name|g_signal_handlers_unblock_by_func
argument_list|(
name|priv
operator|->
name|tool_preset_model
argument_list|,
name|gimp_tool_preset_editor_notify_model
argument_list|,
name|editor
argument_list|)
expr_stmt|;
if|if
condition|(
operator|!
name|priv
operator|->
name|tool_preset_model
operator|->
name|tool_options
condition|)
return|return;
name|tool_info
operator|=
name|priv
operator|->
name|tool_preset_model
operator|->
name|tool_options
operator|->
name|tool_info
expr_stmt|;
name|icon_name
operator|=
name|gimp_viewable_get_icon_name
argument_list|(
name|GIMP_VIEWABLE
argument_list|(
name|tool_info
argument_list|)
argument_list|)
expr_stmt|;
name|label
operator|=
name|g_strdup_printf
argument_list|(
name|_
argument_list|(
literal|"%s Preset"
argument_list|)
argument_list|,
name|tool_info
operator|->
name|label
argument_list|)
expr_stmt|;
name|gtk_image_set_from_icon_name
argument_list|(
name|GTK_IMAGE
argument_list|(
name|priv
operator|->
name|tool_icon
argument_list|)
argument_list|,
name|icon_name
argument_list|,
name|GTK_ICON_SIZE_MENU
argument_list|)
expr_stmt|;
name|gtk_label_set_text
argument_list|(
name|GTK_LABEL
argument_list|(
name|priv
operator|->
name|tool_label
argument_list|)
argument_list|,
name|label
argument_list|)
expr_stmt|;
name|g_free
argument_list|(
name|label
argument_list|)
expr_stmt|;
name|preset
operator|=
name|GIMP_TOOL_PRESET
argument_list|(
name|data_editor
operator|->
name|data
argument_list|)
expr_stmt|;
name|serialize_props
operator|=
name|gimp_context_get_serialize_properties
argument_list|(
name|GIMP_CONTEXT
argument_list|(
name|preset
operator|->
name|tool_options
argument_list|)
argument_list|)
expr_stmt|;
name|gtk_widget_set_sensitive
argument_list|(
name|priv
operator|->
name|fg_bg_toggle
argument_list|,
operator|(
name|serialize_props
operator|&
operator|(
name|GIMP_CONTEXT_PROP_MASK_FOREGROUND
operator||
name|GIMP_CONTEXT_PROP_MASK_BACKGROUND
operator|)
operator|)
operator|!=
literal|0
argument_list|)
expr_stmt|;
name|gtk_widget_set_sensitive
argument_list|(
name|priv
operator|->
name|brush_toggle
argument_list|,
operator|(
name|serialize_props
operator|&
name|GIMP_CONTEXT_PROP_MASK_BRUSH
operator|)
operator|!=
literal|0
argument_list|)
expr_stmt|;
name|gtk_widget_set_sensitive
argument_list|(
name|priv
operator|->
name|dynamics_toggle
argument_list|,
operator|(
name|serialize_props
operator|&
name|GIMP_CONTEXT_PROP_MASK_DYNAMICS
operator|)
operator|!=
literal|0
argument_list|)
expr_stmt|;
name|gtk_widget_set_sensitive
argument_list|(
name|priv
operator|->
name|mybrush_toggle
argument_list|,
operator|(
name|serialize_props
operator|&
name|GIMP_CONTEXT_PROP_MASK_MYBRUSH
operator|)
operator|!=
literal|0
argument_list|)
expr_stmt|;
name|gtk_widget_set_sensitive
argument_list|(
name|priv
operator|->
name|gradient_toggle
argument_list|,
operator|(
name|serialize_props
operator|&
name|GIMP_CONTEXT_PROP_MASK_GRADIENT
operator|)
operator|!=
literal|0
argument_list|)
expr_stmt|;
name|gtk_widget_set_sensitive
argument_list|(
name|priv
operator|->
name|pattern_toggle
argument_list|,
operator|(
name|serialize_props
operator|&
name|GIMP_CONTEXT_PROP_MASK_PATTERN
operator|)
operator|!=
literal|0
argument_list|)
expr_stmt|;
name|gtk_widget_set_sensitive
argument_list|(
name|priv
operator|->
name|palette_toggle
argument_list|,
operator|(
name|serialize_props
operator|&
name|GIMP_CONTEXT_PROP_MASK_PALETTE
operator|)
operator|!=
literal|0
argument_list|)
expr_stmt|;
name|gtk_widget_set_sensitive
argument_list|(
name|priv
operator|->
name|font_toggle
argument_list|,
operator|(
name|serialize_props
operator|&
name|GIMP_CONTEXT_PROP_MASK_FONT
operator|)
operator|!=
literal|0
argument_list|)
expr_stmt|;
block|}
end_function

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
name|gimp_config_sync
argument_list|(
name|G_OBJECT
argument_list|(
name|editor
operator|->
name|priv
operator|->
name|tool_preset_model
argument_list|)
argument_list|,
name|G_OBJECT
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
name|priv
operator|->
name|tool_preset_model
argument_list|,
name|gimp_tool_preset_editor_notify_model
argument_list|,
name|editor
argument_list|)
expr_stmt|;
name|gimp_config_sync
argument_list|(
name|G_OBJECT
argument_list|(
name|data_editor
operator|->
name|data
argument_list|)
argument_list|,
name|G_OBJECT
argument_list|(
name|editor
operator|->
name|priv
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
name|priv
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

