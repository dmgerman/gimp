begin_unit|revision:0.9.5;language:C;cregit-version:0.0.1
begin_comment
comment|/* GIMP - The GNU Image Manipulation Program  * Copyright (C) 1995 Spencer Kimball and Peter Mattis  *  * gimpimagemaptool-settings.c  *  * This program is free software: you can redistribute it and/or modify  * it under the terms of the GNU General Public License as published by  * the Free Software Foundation; either version 3 of the License, or  * (at your option) any later version.  *  * This program is distributed in the hope that it will be useful,  * but WITHOUT ANY WARRANTY; without even the implied warranty of  * MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the  * GNU General Public License for more details.  *  * You should have received a copy of the GNU General Public License  * along with this program.  If not, see<http://www.gnu.org/licenses/>.  */
end_comment

begin_include
include|#
directive|include
file|"config.h"
end_include

begin_include
include|#
directive|include
file|<errno.h>
end_include

begin_include
include|#
directive|include
file|<glib/gstdio.h>
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
file|"tools-types.h"
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
file|"core/gimplist.h"
end_include

begin_include
include|#
directive|include
file|"core/gimptoolinfo.h"
end_include

begin_include
include|#
directive|include
file|"widgets/gimpsettingsbox.h"
end_include

begin_include
include|#
directive|include
file|"display/gimptoolgui.h"
end_include

begin_include
include|#
directive|include
file|"gimpimagemapoptions.h"
end_include

begin_include
include|#
directive|include
file|"gimpimagemaptool.h"
end_include

begin_include
include|#
directive|include
file|"gimpimagemaptool-settings.h"
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
name|gboolean
name|gimp_image_map_tool_settings_import
parameter_list|(
name|GimpSettingsBox
modifier|*
name|box
parameter_list|,
name|GFile
modifier|*
name|file
parameter_list|,
name|GimpImageMapTool
modifier|*
name|im_tool
parameter_list|)
function_decl|;
end_function_decl

begin_function_decl
specifier|static
name|gboolean
name|gimp_image_map_tool_settings_export
parameter_list|(
name|GimpSettingsBox
modifier|*
name|box
parameter_list|,
name|GFile
modifier|*
name|file
parameter_list|,
name|GimpImageMapTool
modifier|*
name|im_tool
parameter_list|)
function_decl|;
end_function_decl

begin_comment
comment|/*  public functions  */
end_comment

begin_function
name|GtkWidget
modifier|*
DECL|function|gimp_image_map_tool_real_get_settings_ui (GimpImageMapTool * im_tool,GimpContainer * settings,GFile * settings_file,const gchar * import_dialog_title,const gchar * export_dialog_title,const gchar * file_dialog_help_id,GFile * default_folder,GtkWidget ** settings_box)
name|gimp_image_map_tool_real_get_settings_ui
parameter_list|(
name|GimpImageMapTool
modifier|*
name|im_tool
parameter_list|,
name|GimpContainer
modifier|*
name|settings
parameter_list|,
name|GFile
modifier|*
name|settings_file
parameter_list|,
specifier|const
name|gchar
modifier|*
name|import_dialog_title
parameter_list|,
specifier|const
name|gchar
modifier|*
name|export_dialog_title
parameter_list|,
specifier|const
name|gchar
modifier|*
name|file_dialog_help_id
parameter_list|,
name|GFile
modifier|*
name|default_folder
parameter_list|,
name|GtkWidget
modifier|*
modifier|*
name|settings_box
parameter_list|)
block|{
name|GimpToolInfo
modifier|*
name|tool_info
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
name|settings_combo
decl_stmt|;
name|tool_info
operator|=
name|GIMP_TOOL
argument_list|(
name|im_tool
argument_list|)
operator|->
name|tool_info
expr_stmt|;
name|hbox
operator|=
name|gtk_box_new
argument_list|(
name|GTK_ORIENTATION_HORIZONTAL
argument_list|,
literal|6
argument_list|)
expr_stmt|;
name|label
operator|=
name|gtk_label_new_with_mnemonic
argument_list|(
name|_
argument_list|(
literal|"Pre_sets:"
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
operator|*
name|settings_box
operator|=
name|gimp_settings_box_new
argument_list|(
name|tool_info
operator|->
name|gimp
argument_list|,
name|im_tool
operator|->
name|config
argument_list|,
name|settings
argument_list|,
name|settings_file
argument_list|,
name|import_dialog_title
argument_list|,
name|export_dialog_title
argument_list|,
name|file_dialog_help_id
argument_list|,
name|default_folder
argument_list|,
name|NULL
argument_list|)
expr_stmt|;
name|gtk_box_pack_start
argument_list|(
name|GTK_BOX
argument_list|(
name|hbox
argument_list|)
argument_list|,
operator|*
name|settings_box
argument_list|,
name|TRUE
argument_list|,
name|TRUE
argument_list|,
literal|0
argument_list|)
expr_stmt|;
name|gtk_widget_show
argument_list|(
operator|*
name|settings_box
argument_list|)
expr_stmt|;
name|settings_combo
operator|=
name|gimp_settings_box_get_combo
argument_list|(
name|GIMP_SETTINGS_BOX
argument_list|(
operator|*
name|settings_box
argument_list|)
argument_list|)
expr_stmt|;
name|gtk_label_set_mnemonic_widget
argument_list|(
name|GTK_LABEL
argument_list|(
name|label
argument_list|)
argument_list|,
name|settings_combo
argument_list|)
expr_stmt|;
name|g_signal_connect
argument_list|(
name|im_tool
operator|->
name|settings_box
argument_list|,
literal|"import"
argument_list|,
name|G_CALLBACK
argument_list|(
name|gimp_image_map_tool_settings_import
argument_list|)
argument_list|,
name|im_tool
argument_list|)
expr_stmt|;
name|g_signal_connect
argument_list|(
name|im_tool
operator|->
name|settings_box
argument_list|,
literal|"export"
argument_list|,
name|G_CALLBACK
argument_list|(
name|gimp_image_map_tool_settings_export
argument_list|)
argument_list|,
name|im_tool
argument_list|)
expr_stmt|;
return|return
name|hbox
return|;
block|}
end_function

begin_function
name|gboolean
DECL|function|gimp_image_map_tool_real_settings_import (GimpImageMapTool * im_tool,GInputStream * input,GError ** error)
name|gimp_image_map_tool_real_settings_import
parameter_list|(
name|GimpImageMapTool
modifier|*
name|im_tool
parameter_list|,
name|GInputStream
modifier|*
name|input
parameter_list|,
name|GError
modifier|*
modifier|*
name|error
parameter_list|)
block|{
return|return
name|gimp_config_deserialize_stream
argument_list|(
name|GIMP_CONFIG
argument_list|(
name|im_tool
operator|->
name|config
argument_list|)
argument_list|,
name|input
argument_list|,
name|NULL
argument_list|,
name|error
argument_list|)
return|;
block|}
end_function

begin_function
name|gboolean
DECL|function|gimp_image_map_tool_real_settings_export (GimpImageMapTool * im_tool,GOutputStream * output,GError ** error)
name|gimp_image_map_tool_real_settings_export
parameter_list|(
name|GimpImageMapTool
modifier|*
name|im_tool
parameter_list|,
name|GOutputStream
modifier|*
name|output
parameter_list|,
name|GError
modifier|*
modifier|*
name|error
parameter_list|)
block|{
name|GimpImageMapToolClass
modifier|*
name|klass
init|=
name|GIMP_IMAGE_MAP_TOOL_GET_CLASS
argument_list|(
name|im_tool
argument_list|)
decl_stmt|;
name|gchar
modifier|*
name|header
decl_stmt|;
name|gchar
modifier|*
name|footer
decl_stmt|;
name|gboolean
name|success
decl_stmt|;
name|header
operator|=
name|g_strdup_printf
argument_list|(
literal|"GIMP %s tool settings"
argument_list|,
name|klass
operator|->
name|settings_name
argument_list|)
expr_stmt|;
name|footer
operator|=
name|g_strdup_printf
argument_list|(
literal|"end of %s tool settings"
argument_list|,
name|klass
operator|->
name|settings_name
argument_list|)
expr_stmt|;
name|success
operator|=
name|gimp_config_serialize_to_stream
argument_list|(
name|GIMP_CONFIG
argument_list|(
name|im_tool
operator|->
name|config
argument_list|)
argument_list|,
name|output
argument_list|,
name|header
argument_list|,
name|footer
argument_list|,
name|NULL
argument_list|,
name|error
argument_list|)
expr_stmt|;
name|g_free
argument_list|(
name|header
argument_list|)
expr_stmt|;
name|g_free
argument_list|(
name|footer
argument_list|)
expr_stmt|;
return|return
name|success
return|;
block|}
end_function

begin_comment
comment|/*  private functions  */
end_comment

begin_function
specifier|static
name|gboolean
DECL|function|gimp_image_map_tool_settings_import (GimpSettingsBox * box,GFile * file,GimpImageMapTool * im_tool)
name|gimp_image_map_tool_settings_import
parameter_list|(
name|GimpSettingsBox
modifier|*
name|box
parameter_list|,
name|GFile
modifier|*
name|file
parameter_list|,
name|GimpImageMapTool
modifier|*
name|im_tool
parameter_list|)
block|{
name|GimpImageMapToolClass
modifier|*
name|tool_class
init|=
name|GIMP_IMAGE_MAP_TOOL_GET_CLASS
argument_list|(
name|im_tool
argument_list|)
decl_stmt|;
name|GInputStream
modifier|*
name|input
decl_stmt|;
name|GError
modifier|*
name|error
init|=
name|NULL
decl_stmt|;
name|g_return_val_if_fail
argument_list|(
name|tool_class
operator|->
name|settings_import
operator|!=
name|NULL
argument_list|,
name|FALSE
argument_list|)
expr_stmt|;
if|if
condition|(
name|GIMP_TOOL
argument_list|(
name|im_tool
argument_list|)
operator|->
name|tool_info
operator|->
name|gimp
operator|->
name|be_verbose
condition|)
name|g_print
argument_list|(
literal|"Parsing '%s'\n"
argument_list|,
name|gimp_file_get_utf8_name
argument_list|(
name|file
argument_list|)
argument_list|)
expr_stmt|;
name|input
operator|=
name|G_INPUT_STREAM
argument_list|(
name|g_file_read
argument_list|(
name|file
argument_list|,
name|NULL
argument_list|,
operator|&
name|error
argument_list|)
argument_list|)
expr_stmt|;
if|if
condition|(
operator|!
name|input
condition|)
block|{
name|gimp_message
argument_list|(
name|GIMP_TOOL
argument_list|(
name|im_tool
argument_list|)
operator|->
name|tool_info
operator|->
name|gimp
argument_list|,
name|G_OBJECT
argument_list|(
name|gimp_tool_gui_get_dialog
argument_list|(
name|im_tool
operator|->
name|gui
argument_list|)
argument_list|)
argument_list|,
name|GIMP_MESSAGE_ERROR
argument_list|,
name|_
argument_list|(
literal|"Could not open '%s' for reading: %s"
argument_list|)
argument_list|,
name|gimp_file_get_utf8_name
argument_list|(
name|file
argument_list|)
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
return|return
name|FALSE
return|;
block|}
if|if
condition|(
operator|!
name|tool_class
operator|->
name|settings_import
argument_list|(
name|im_tool
argument_list|,
name|input
argument_list|,
operator|&
name|error
argument_list|)
condition|)
block|{
name|gimp_message
argument_list|(
name|GIMP_TOOL
argument_list|(
name|im_tool
argument_list|)
operator|->
name|tool_info
operator|->
name|gimp
argument_list|,
name|G_OBJECT
argument_list|(
name|gimp_tool_gui_get_dialog
argument_list|(
name|im_tool
operator|->
name|gui
argument_list|)
argument_list|)
argument_list|,
name|GIMP_MESSAGE_ERROR
argument_list|,
name|_
argument_list|(
literal|"Error reading '%s': %s"
argument_list|)
argument_list|,
name|gimp_file_get_utf8_name
argument_list|(
name|file
argument_list|)
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
name|input
argument_list|)
expr_stmt|;
return|return
name|FALSE
return|;
block|}
name|g_object_unref
argument_list|(
name|input
argument_list|)
expr_stmt|;
name|g_object_set
argument_list|(
name|GIMP_TOOL_GET_OPTIONS
argument_list|(
name|im_tool
argument_list|)
argument_list|,
literal|"settings"
argument_list|,
name|file
argument_list|,
name|NULL
argument_list|)
expr_stmt|;
return|return
name|TRUE
return|;
block|}
end_function

begin_function
specifier|static
name|gboolean
DECL|function|gimp_image_map_tool_settings_export (GimpSettingsBox * box,GFile * file,GimpImageMapTool * im_tool)
name|gimp_image_map_tool_settings_export
parameter_list|(
name|GimpSettingsBox
modifier|*
name|box
parameter_list|,
name|GFile
modifier|*
name|file
parameter_list|,
name|GimpImageMapTool
modifier|*
name|im_tool
parameter_list|)
block|{
name|GimpImageMapToolClass
modifier|*
name|tool_class
init|=
name|GIMP_IMAGE_MAP_TOOL_GET_CLASS
argument_list|(
name|im_tool
argument_list|)
decl_stmt|;
name|GOutputStream
modifier|*
name|output
decl_stmt|;
name|GError
modifier|*
name|error
init|=
name|NULL
decl_stmt|;
name|g_return_val_if_fail
argument_list|(
name|tool_class
operator|->
name|settings_export
operator|!=
name|NULL
argument_list|,
name|FALSE
argument_list|)
expr_stmt|;
if|if
condition|(
name|GIMP_TOOL
argument_list|(
name|im_tool
argument_list|)
operator|->
name|tool_info
operator|->
name|gimp
operator|->
name|be_verbose
condition|)
name|g_print
argument_list|(
literal|"Writing '%s'\n"
argument_list|,
name|gimp_file_get_utf8_name
argument_list|(
name|file
argument_list|)
argument_list|)
expr_stmt|;
name|output
operator|=
name|G_OUTPUT_STREAM
argument_list|(
name|g_file_replace
argument_list|(
name|file
argument_list|,
name|NULL
argument_list|,
name|FALSE
argument_list|,
name|G_FILE_CREATE_NONE
argument_list|,
name|NULL
argument_list|,
operator|&
name|error
argument_list|)
argument_list|)
expr_stmt|;
if|if
condition|(
operator|!
name|output
condition|)
block|{
name|gimp_message_literal
argument_list|(
name|GIMP_TOOL
argument_list|(
name|im_tool
argument_list|)
operator|->
name|tool_info
operator|->
name|gimp
argument_list|,
name|G_OBJECT
argument_list|(
name|gimp_tool_gui_get_dialog
argument_list|(
name|im_tool
operator|->
name|gui
argument_list|)
argument_list|)
argument_list|,
name|GIMP_MESSAGE_ERROR
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
return|return
name|FALSE
return|;
block|}
if|if
condition|(
operator|!
name|tool_class
operator|->
name|settings_export
argument_list|(
name|im_tool
argument_list|,
name|output
argument_list|,
operator|&
name|error
argument_list|)
condition|)
block|{
name|gimp_message
argument_list|(
name|GIMP_TOOL
argument_list|(
name|im_tool
argument_list|)
operator|->
name|tool_info
operator|->
name|gimp
argument_list|,
name|G_OBJECT
argument_list|(
name|gimp_tool_gui_get_dialog
argument_list|(
name|im_tool
operator|->
name|gui
argument_list|)
argument_list|)
argument_list|,
name|GIMP_MESSAGE_ERROR
argument_list|,
name|_
argument_list|(
literal|"Error writing '%s': %s"
argument_list|)
argument_list|,
name|gimp_file_get_utf8_name
argument_list|(
name|file
argument_list|)
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
name|output
argument_list|)
expr_stmt|;
return|return
name|FALSE
return|;
block|}
name|g_object_unref
argument_list|(
name|output
argument_list|)
expr_stmt|;
name|gimp_message
argument_list|(
name|GIMP_TOOL
argument_list|(
name|im_tool
argument_list|)
operator|->
name|tool_info
operator|->
name|gimp
argument_list|,
name|G_OBJECT
argument_list|(
name|GIMP_TOOL
argument_list|(
name|im_tool
argument_list|)
operator|->
name|display
argument_list|)
argument_list|,
name|GIMP_MESSAGE_INFO
argument_list|,
name|_
argument_list|(
literal|"Settings saved to '%s'"
argument_list|)
argument_list|,
name|gimp_file_get_utf8_name
argument_list|(
name|file
argument_list|)
argument_list|)
expr_stmt|;
name|g_object_set
argument_list|(
name|GIMP_TOOL_GET_OPTIONS
argument_list|(
name|im_tool
argument_list|)
argument_list|,
literal|"settings"
argument_list|,
name|file
argument_list|,
name|NULL
argument_list|)
expr_stmt|;
return|return
name|TRUE
return|;
block|}
end_function

end_unit

