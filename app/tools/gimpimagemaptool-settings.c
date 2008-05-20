begin_unit|revision:0.9.5;language:C;cregit-version:0.0.1
begin_comment
comment|/* GIMP - The GNU Image Manipulation Program  * Copyright (C) 1995 Spencer Kimball and Peter Mattis  *  * gimpimagemaptool-settings.c  *  * This program is free software; you can redistribute it and/or modify  * it under the terms of the GNU General Public License as published by  * the Free Software Foundation; either version 2 of the License, or  * (at your option) any later version.  *  * This program is distributed in the hope that it will be useful,  * but WITHOUT ANY WARRANTY; without even the implied warranty of  * MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the  * GNU General Public License for more details.  *  * You should have received a copy of the GNU General Public License  * along with this program; if not, write to the Free Software  * Foundation, Inc., 59 Temple Place - Suite 330, Boston, MA 02111-1307, USA.  */
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
file|"widgets/gimpcontainercombobox.h"
end_include

begin_include
include|#
directive|include
file|"widgets/gimpcontainerview.h"
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
name|void
name|gimp_image_map_tool_recent_selected
parameter_list|(
name|GimpContainerView
modifier|*
name|view
parameter_list|,
name|GimpViewable
modifier|*
name|object
parameter_list|,
name|gpointer
name|insert_data
parameter_list|,
name|GimpImageMapTool
modifier|*
name|tool
parameter_list|)
function_decl|;
end_function_decl

begin_function_decl
specifier|static
name|void
name|gimp_image_map_tool_favorite_clicked
parameter_list|(
name|GtkWidget
modifier|*
name|widget
parameter_list|,
name|GimpImageMapTool
modifier|*
name|tool
parameter_list|)
function_decl|;
end_function_decl

begin_function_decl
specifier|static
name|void
name|gimp_image_map_tool_load_clicked
parameter_list|(
name|GtkWidget
modifier|*
name|widget
parameter_list|,
name|GimpImageMapTool
modifier|*
name|tool
parameter_list|)
function_decl|;
end_function_decl

begin_function_decl
specifier|static
name|void
name|gimp_image_map_tool_save_clicked
parameter_list|(
name|GtkWidget
modifier|*
name|widget
parameter_list|,
name|GimpImageMapTool
modifier|*
name|tool
parameter_list|)
function_decl|;
end_function_decl

begin_function_decl
specifier|static
name|void
name|gimp_image_map_tool_settings_dialog
parameter_list|(
name|GimpImageMapTool
modifier|*
name|im_tool
parameter_list|,
specifier|const
name|gchar
modifier|*
name|title
parameter_list|,
name|gboolean
name|save
parameter_list|)
function_decl|;
end_function_decl

begin_function_decl
specifier|static
name|void
name|gimp_image_map_tool_favorite_callback
parameter_list|(
name|GtkWidget
modifier|*
name|query_box
parameter_list|,
specifier|const
name|gchar
modifier|*
name|string
parameter_list|,
name|gpointer
name|data
parameter_list|)
function_decl|;
end_function_decl

begin_function_decl
specifier|static
name|gboolean
name|gimp_image_map_tool_settings_load
parameter_list|(
name|GimpImageMapTool
modifier|*
name|tool
parameter_list|,
specifier|const
name|gchar
modifier|*
name|filename
parameter_list|)
function_decl|;
end_function_decl

begin_function_decl
specifier|static
name|gboolean
name|gimp_image_map_tool_settings_save
parameter_list|(
name|GimpImageMapTool
modifier|*
name|tool
parameter_list|,
specifier|const
name|gchar
modifier|*
name|filename
parameter_list|)
function_decl|;
end_function_decl

begin_comment
comment|/*  public functions  */
end_comment

begin_function
name|gboolean
DECL|function|gimp_image_map_tool_add_settings_gui (GimpImageMapTool * image_map_tool)
name|gimp_image_map_tool_add_settings_gui
parameter_list|(
name|GimpImageMapTool
modifier|*
name|image_map_tool
parameter_list|)
block|{
name|GimpImageMapToolClass
modifier|*
name|klass
decl_stmt|;
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
name|combo
decl_stmt|;
name|GtkWidget
modifier|*
name|button
decl_stmt|;
name|klass
operator|=
name|GIMP_IMAGE_MAP_TOOL_GET_CLASS
argument_list|(
name|image_map_tool
argument_list|)
expr_stmt|;
name|tool_info
operator|=
name|GIMP_TOOL
argument_list|(
name|image_map_tool
argument_list|)
operator|->
name|tool_info
expr_stmt|;
if|if
condition|(
name|gimp_container_num_children
argument_list|(
name|klass
operator|->
name|recent_settings
argument_list|)
operator|==
literal|0
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
name|filename
operator|=
name|gimp_tool_info_build_options_filename
argument_list|(
name|tool_info
argument_list|,
literal|".settings"
argument_list|)
expr_stmt|;
if|if
condition|(
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
name|gimp_filename_to_utf8
argument_list|(
name|filename
argument_list|)
argument_list|)
expr_stmt|;
if|if
condition|(
operator|!
name|gimp_config_deserialize_file
argument_list|(
name|GIMP_CONFIG
argument_list|(
name|klass
operator|->
name|recent_settings
argument_list|)
argument_list|,
name|filename
argument_list|,
name|NULL
argument_list|,
operator|&
name|error
argument_list|)
condition|)
block|{
if|if
condition|(
name|error
operator|->
name|code
operator|!=
name|GIMP_CONFIG_ERROR_OPEN_ENOENT
condition|)
name|gimp_message
argument_list|(
name|tool_info
operator|->
name|gimp
argument_list|,
name|NULL
argument_list|,
name|GIMP_MESSAGE_ERROR
argument_list|,
literal|"%s"
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
block|}
name|gimp_list_reverse
argument_list|(
name|GIMP_LIST
argument_list|(
name|klass
operator|->
name|recent_settings
argument_list|)
argument_list|)
expr_stmt|;
name|g_free
argument_list|(
name|filename
argument_list|)
expr_stmt|;
block|}
name|hbox
operator|=
name|gtk_hbox_new
argument_list|(
name|FALSE
argument_list|,
literal|4
argument_list|)
expr_stmt|;
name|gtk_box_pack_start
argument_list|(
name|GTK_BOX
argument_list|(
name|image_map_tool
operator|->
name|main_vbox
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
literal|"Recent Settings:"
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
name|combo
operator|=
name|gimp_container_combo_box_new
argument_list|(
name|klass
operator|->
name|recent_settings
argument_list|,
name|GIMP_CONTEXT
argument_list|(
name|tool_info
operator|->
name|tool_options
argument_list|)
argument_list|,
literal|16
argument_list|,
literal|0
argument_list|)
expr_stmt|;
name|gtk_box_pack_start
argument_list|(
name|GTK_BOX
argument_list|(
name|hbox
argument_list|)
argument_list|,
name|combo
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
name|combo
argument_list|)
expr_stmt|;
name|gimp_help_set_help_data
argument_list|(
name|combo
argument_list|,
name|_
argument_list|(
literal|"Pick a setting from the list"
argument_list|)
argument_list|,
name|NULL
argument_list|)
expr_stmt|;
name|g_signal_connect_after
argument_list|(
name|combo
argument_list|,
literal|"select-item"
argument_list|,
name|G_CALLBACK
argument_list|(
name|gimp_image_map_tool_recent_selected
argument_list|)
argument_list|,
name|image_map_tool
argument_list|)
expr_stmt|;
comment|/*  The load/save hbox  */
name|hbox
operator|=
name|gtk_hbox_new
argument_list|(
name|FALSE
argument_list|,
literal|4
argument_list|)
expr_stmt|;
name|gtk_box_pack_start
argument_list|(
name|GTK_BOX
argument_list|(
name|image_map_tool
operator|->
name|main_vbox
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
name|button
operator|=
name|gtk_button_new_with_mnemonic
argument_list|(
name|_
argument_list|(
literal|"Save to _Favorites"
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
name|button
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
name|button
argument_list|)
expr_stmt|;
name|g_signal_connect
argument_list|(
name|button
argument_list|,
literal|"clicked"
argument_list|,
name|G_CALLBACK
argument_list|(
name|gimp_image_map_tool_favorite_clicked
argument_list|)
argument_list|,
name|image_map_tool
argument_list|)
expr_stmt|;
name|image_map_tool
operator|->
name|load_button
operator|=
name|g_object_new
argument_list|(
name|GIMP_TYPE_BUTTON
argument_list|,
literal|"label"
argument_list|,
name|GTK_STOCK_OPEN
argument_list|,
literal|"use-stock"
argument_list|,
name|TRUE
argument_list|,
literal|"use-underline"
argument_list|,
name|TRUE
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
name|image_map_tool
operator|->
name|load_button
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
name|image_map_tool
operator|->
name|load_button
argument_list|)
expr_stmt|;
name|g_signal_connect
argument_list|(
name|image_map_tool
operator|->
name|load_button
argument_list|,
literal|"clicked"
argument_list|,
name|G_CALLBACK
argument_list|(
name|gimp_image_map_tool_load_clicked
argument_list|)
argument_list|,
name|image_map_tool
argument_list|)
expr_stmt|;
if|if
condition|(
name|klass
operator|->
name|load_button_tip
condition|)
name|gimp_help_set_help_data
argument_list|(
name|image_map_tool
operator|->
name|load_button
argument_list|,
name|klass
operator|->
name|load_button_tip
argument_list|,
name|NULL
argument_list|)
expr_stmt|;
name|image_map_tool
operator|->
name|save_button
operator|=
name|g_object_new
argument_list|(
name|GIMP_TYPE_BUTTON
argument_list|,
literal|"label"
argument_list|,
name|GTK_STOCK_SAVE
argument_list|,
literal|"use-stock"
argument_list|,
name|TRUE
argument_list|,
literal|"use-underline"
argument_list|,
name|TRUE
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
name|image_map_tool
operator|->
name|save_button
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
name|image_map_tool
operator|->
name|save_button
argument_list|)
expr_stmt|;
name|g_signal_connect
argument_list|(
name|image_map_tool
operator|->
name|save_button
argument_list|,
literal|"clicked"
argument_list|,
name|G_CALLBACK
argument_list|(
name|gimp_image_map_tool_save_clicked
argument_list|)
argument_list|,
name|image_map_tool
argument_list|)
expr_stmt|;
if|if
condition|(
name|klass
operator|->
name|save_button_tip
condition|)
name|gimp_help_set_help_data
argument_list|(
name|image_map_tool
operator|->
name|save_button
argument_list|,
name|klass
operator|->
name|save_button_tip
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
name|void
DECL|function|gimp_image_map_tool_add_recent_settings (GimpImageMapTool * image_map_tool)
name|gimp_image_map_tool_add_recent_settings
parameter_list|(
name|GimpImageMapTool
modifier|*
name|image_map_tool
parameter_list|)
block|{
name|GimpTool
modifier|*
name|tool
init|=
name|GIMP_TOOL
argument_list|(
name|image_map_tool
argument_list|)
decl_stmt|;
name|GimpContainer
modifier|*
name|recent
decl_stmt|;
name|GimpConfig
modifier|*
name|current
decl_stmt|;
name|GimpConfig
modifier|*
name|config
init|=
name|NULL
decl_stmt|;
name|GList
modifier|*
name|list
decl_stmt|;
name|time_t
name|now
decl_stmt|;
name|struct
name|tm
name|tm
decl_stmt|;
name|gchar
name|buf
index|[
literal|64
index|]
decl_stmt|;
name|gchar
modifier|*
name|name
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
name|recent
operator|=
name|GIMP_IMAGE_MAP_TOOL_GET_CLASS
argument_list|(
name|image_map_tool
argument_list|)
operator|->
name|recent_settings
expr_stmt|;
name|current
operator|=
name|GIMP_CONFIG
argument_list|(
name|image_map_tool
operator|->
name|config
argument_list|)
expr_stmt|;
for|for
control|(
name|list
operator|=
name|GIMP_LIST
argument_list|(
name|recent
argument_list|)
operator|->
name|list
init|;
name|list
condition|;
name|list
operator|=
name|g_list_next
argument_list|(
name|list
argument_list|)
control|)
block|{
name|config
operator|=
name|list
operator|->
name|data
expr_stmt|;
if|if
condition|(
name|gimp_config_is_equal_to
argument_list|(
name|config
argument_list|,
name|current
argument_list|)
condition|)
block|{
name|gimp_container_reorder
argument_list|(
name|recent
argument_list|,
name|GIMP_OBJECT
argument_list|(
name|config
argument_list|)
argument_list|,
literal|0
argument_list|)
expr_stmt|;
break|break;
block|}
name|config
operator|=
name|NULL
expr_stmt|;
block|}
if|if
condition|(
operator|!
name|config
condition|)
block|{
name|config
operator|=
name|gimp_config_duplicate
argument_list|(
name|current
argument_list|)
expr_stmt|;
name|gimp_container_insert
argument_list|(
name|recent
argument_list|,
name|GIMP_OBJECT
argument_list|(
name|config
argument_list|)
argument_list|,
literal|0
argument_list|)
expr_stmt|;
name|g_object_unref
argument_list|(
name|config
argument_list|)
expr_stmt|;
block|}
name|now
operator|=
name|time
argument_list|(
name|NULL
argument_list|)
expr_stmt|;
name|tm
operator|=
operator|*
name|localtime
argument_list|(
operator|&
name|now
argument_list|)
expr_stmt|;
name|strftime
argument_list|(
name|buf
argument_list|,
sizeof|sizeof
argument_list|(
name|buf
argument_list|)
argument_list|,
literal|"%Y-%m-%d %T"
argument_list|,
operator|&
name|tm
argument_list|)
expr_stmt|;
name|name
operator|=
name|g_locale_to_utf8
argument_list|(
name|buf
argument_list|,
operator|-
literal|1
argument_list|,
name|NULL
argument_list|,
name|NULL
argument_list|,
name|NULL
argument_list|)
expr_stmt|;
name|gimp_object_set_name
argument_list|(
name|GIMP_OBJECT
argument_list|(
name|config
argument_list|)
argument_list|,
name|name
argument_list|)
expr_stmt|;
name|g_free
argument_list|(
name|name
argument_list|)
expr_stmt|;
name|filename
operator|=
name|gimp_tool_info_build_options_filename
argument_list|(
name|tool
operator|->
name|tool_info
argument_list|,
literal|".settings"
argument_list|)
expr_stmt|;
if|if
condition|(
name|tool
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
name|gimp_filename_to_utf8
argument_list|(
name|filename
argument_list|)
argument_list|)
expr_stmt|;
if|if
condition|(
operator|!
name|gimp_config_serialize_to_file
argument_list|(
name|GIMP_CONFIG
argument_list|(
name|recent
argument_list|)
argument_list|,
name|filename
argument_list|,
literal|"tool settings"
argument_list|,
literal|"end of tool settings"
argument_list|,
name|NULL
argument_list|,
operator|&
name|error
argument_list|)
condition|)
block|{
name|gimp_message
argument_list|(
name|tool
operator|->
name|tool_info
operator|->
name|gimp
argument_list|,
name|NULL
argument_list|,
name|GIMP_MESSAGE_ERROR
argument_list|,
literal|"%s"
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
block|}
name|g_free
argument_list|(
name|filename
argument_list|)
expr_stmt|;
block|}
end_function

begin_function
name|gboolean
DECL|function|gimp_image_map_tool_real_settings_load (GimpImageMapTool * tool,const gchar * filename,GError ** error)
name|gimp_image_map_tool_real_settings_load
parameter_list|(
name|GimpImageMapTool
modifier|*
name|tool
parameter_list|,
specifier|const
name|gchar
modifier|*
name|filename
parameter_list|,
name|GError
modifier|*
modifier|*
name|error
parameter_list|)
block|{
name|gboolean
name|success
decl_stmt|;
if|if
condition|(
name|GIMP_TOOL
argument_list|(
name|tool
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
name|gimp_filename_to_utf8
argument_list|(
name|filename
argument_list|)
argument_list|)
expr_stmt|;
name|success
operator|=
name|gimp_config_deserialize_file
argument_list|(
name|GIMP_CONFIG
argument_list|(
name|tool
operator|->
name|config
argument_list|)
argument_list|,
name|filename
argument_list|,
name|NULL
argument_list|,
name|error
argument_list|)
expr_stmt|;
return|return
name|success
return|;
block|}
end_function

begin_function
name|gboolean
DECL|function|gimp_image_map_tool_real_settings_save (GimpImageMapTool * tool,const gchar * filename,GError ** error)
name|gimp_image_map_tool_real_settings_save
parameter_list|(
name|GimpImageMapTool
modifier|*
name|tool
parameter_list|,
specifier|const
name|gchar
modifier|*
name|filename
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
name|tool
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
if|if
condition|(
name|GIMP_TOOL
argument_list|(
name|tool
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
name|gimp_filename_to_utf8
argument_list|(
name|filename
argument_list|)
argument_list|)
expr_stmt|;
name|success
operator|=
name|gimp_config_serialize_to_file
argument_list|(
name|GIMP_CONFIG
argument_list|(
name|tool
operator|->
name|config
argument_list|)
argument_list|,
name|filename
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
name|void
DECL|function|gimp_image_map_tool_recent_selected (GimpContainerView * view,GimpViewable * object,gpointer insert_data,GimpImageMapTool * tool)
name|gimp_image_map_tool_recent_selected
parameter_list|(
name|GimpContainerView
modifier|*
name|view
parameter_list|,
name|GimpViewable
modifier|*
name|object
parameter_list|,
name|gpointer
name|insert_data
parameter_list|,
name|GimpImageMapTool
modifier|*
name|tool
parameter_list|)
block|{
if|if
condition|(
name|object
condition|)
block|{
name|gimp_config_copy
argument_list|(
name|GIMP_CONFIG
argument_list|(
name|object
argument_list|)
argument_list|,
name|GIMP_CONFIG
argument_list|(
name|tool
operator|->
name|config
argument_list|)
argument_list|,
literal|0
argument_list|)
expr_stmt|;
name|gimp_container_view_select_item
argument_list|(
name|view
argument_list|,
name|NULL
argument_list|)
expr_stmt|;
block|}
block|}
end_function

begin_function
specifier|static
name|void
DECL|function|gimp_image_map_tool_favorite_clicked (GtkWidget * widget,GimpImageMapTool * tool)
name|gimp_image_map_tool_favorite_clicked
parameter_list|(
name|GtkWidget
modifier|*
name|widget
parameter_list|,
name|GimpImageMapTool
modifier|*
name|tool
parameter_list|)
block|{
name|GtkWidget
modifier|*
name|dialog
decl_stmt|;
name|dialog
operator|=
name|gimp_query_string_box
argument_list|(
name|_
argument_list|(
literal|"Save Settings to Favorites"
argument_list|)
argument_list|,
name|tool
operator|->
name|shell
argument_list|,
name|gimp_standard_help_func
argument_list|,
name|NULL
argument_list|,
comment|/*GIMP_HELP_TOOL_OPTIONS_DIALOG, */
name|_
argument_list|(
literal|"Enter a name for the saved settings"
argument_list|)
argument_list|,
name|_
argument_list|(
literal|"Saved Settings"
argument_list|)
argument_list|,
name|G_OBJECT
argument_list|(
name|tool
operator|->
name|shell
argument_list|)
argument_list|,
literal|"hide"
argument_list|,
name|gimp_image_map_tool_favorite_callback
argument_list|,
name|tool
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
specifier|static
name|void
DECL|function|gimp_image_map_tool_load_clicked (GtkWidget * widget,GimpImageMapTool * tool)
name|gimp_image_map_tool_load_clicked
parameter_list|(
name|GtkWidget
modifier|*
name|widget
parameter_list|,
name|GimpImageMapTool
modifier|*
name|tool
parameter_list|)
block|{
name|GimpImageMapToolClass
modifier|*
name|klass
init|=
name|GIMP_IMAGE_MAP_TOOL_GET_CLASS
argument_list|(
name|tool
argument_list|)
decl_stmt|;
name|gimp_image_map_tool_settings_dialog
argument_list|(
name|tool
argument_list|,
name|klass
operator|->
name|load_dialog_title
argument_list|,
name|FALSE
argument_list|)
expr_stmt|;
block|}
end_function

begin_function
specifier|static
name|void
DECL|function|gimp_image_map_tool_save_clicked (GtkWidget * widget,GimpImageMapTool * tool)
name|gimp_image_map_tool_save_clicked
parameter_list|(
name|GtkWidget
modifier|*
name|widget
parameter_list|,
name|GimpImageMapTool
modifier|*
name|tool
parameter_list|)
block|{
name|GimpImageMapToolClass
modifier|*
name|klass
init|=
name|GIMP_IMAGE_MAP_TOOL_GET_CLASS
argument_list|(
name|tool
argument_list|)
decl_stmt|;
name|gimp_image_map_tool_settings_dialog
argument_list|(
name|tool
argument_list|,
name|klass
operator|->
name|save_dialog_title
argument_list|,
name|TRUE
argument_list|)
expr_stmt|;
block|}
end_function

begin_function
specifier|static
name|void
DECL|function|settings_dialog_response (GtkWidget * dialog,gint response_id,GimpImageMapTool * tool)
name|settings_dialog_response
parameter_list|(
name|GtkWidget
modifier|*
name|dialog
parameter_list|,
name|gint
name|response_id
parameter_list|,
name|GimpImageMapTool
modifier|*
name|tool
parameter_list|)
block|{
name|gboolean
name|save
decl_stmt|;
name|save
operator|=
name|GPOINTER_TO_INT
argument_list|(
name|g_object_get_data
argument_list|(
name|G_OBJECT
argument_list|(
name|dialog
argument_list|)
argument_list|,
literal|"save"
argument_list|)
argument_list|)
expr_stmt|;
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
name|filename
operator|=
name|gtk_file_chooser_get_filename
argument_list|(
name|GTK_FILE_CHOOSER
argument_list|(
name|dialog
argument_list|)
argument_list|)
expr_stmt|;
if|if
condition|(
name|save
condition|)
name|gimp_image_map_tool_settings_save
argument_list|(
name|tool
argument_list|,
name|filename
argument_list|)
expr_stmt|;
else|else
name|gimp_image_map_tool_settings_load
argument_list|(
name|tool
argument_list|,
name|filename
argument_list|)
expr_stmt|;
name|g_free
argument_list|(
name|filename
argument_list|)
expr_stmt|;
block|}
if|if
condition|(
name|save
condition|)
name|gtk_widget_set_sensitive
argument_list|(
name|tool
operator|->
name|load_button
argument_list|,
name|TRUE
argument_list|)
expr_stmt|;
else|else
name|gtk_widget_set_sensitive
argument_list|(
name|tool
operator|->
name|save_button
argument_list|,
name|TRUE
argument_list|)
expr_stmt|;
name|gtk_widget_destroy
argument_list|(
name|dialog
argument_list|)
expr_stmt|;
block|}
end_function

begin_function
specifier|static
name|void
DECL|function|gimp_image_map_tool_settings_dialog (GimpImageMapTool * tool,const gchar * title,gboolean save)
name|gimp_image_map_tool_settings_dialog
parameter_list|(
name|GimpImageMapTool
modifier|*
name|tool
parameter_list|,
specifier|const
name|gchar
modifier|*
name|title
parameter_list|,
name|gboolean
name|save
parameter_list|)
block|{
name|GimpImageMapOptions
modifier|*
name|options
init|=
name|GIMP_IMAGE_MAP_TOOL_GET_OPTIONS
argument_list|(
name|tool
argument_list|)
decl_stmt|;
name|GtkFileChooser
modifier|*
name|chooser
decl_stmt|;
specifier|const
name|gchar
modifier|*
name|settings_name
decl_stmt|;
name|gchar
modifier|*
name|folder
decl_stmt|;
name|settings_name
operator|=
name|GIMP_IMAGE_MAP_TOOL_GET_CLASS
argument_list|(
name|tool
argument_list|)
operator|->
name|settings_name
expr_stmt|;
name|g_return_if_fail
argument_list|(
name|settings_name
operator|!=
name|NULL
argument_list|)
expr_stmt|;
if|if
condition|(
name|tool
operator|->
name|settings_dialog
condition|)
block|{
name|gtk_window_present
argument_list|(
name|GTK_WINDOW
argument_list|(
name|tool
operator|->
name|settings_dialog
argument_list|)
argument_list|)
expr_stmt|;
return|return;
block|}
if|if
condition|(
name|save
condition|)
name|gtk_widget_set_sensitive
argument_list|(
name|tool
operator|->
name|load_button
argument_list|,
name|FALSE
argument_list|)
expr_stmt|;
else|else
name|gtk_widget_set_sensitive
argument_list|(
name|tool
operator|->
name|save_button
argument_list|,
name|FALSE
argument_list|)
expr_stmt|;
name|tool
operator|->
name|settings_dialog
operator|=
name|gtk_file_chooser_dialog_new
argument_list|(
name|title
argument_list|,
name|GTK_WINDOW
argument_list|(
name|tool
operator|->
name|shell
argument_list|)
argument_list|,
name|save
condition|?
name|GTK_FILE_CHOOSER_ACTION_SAVE
else|:
name|GTK_FILE_CHOOSER_ACTION_OPEN
argument_list|,
name|GTK_STOCK_CANCEL
argument_list|,
name|GTK_RESPONSE_CANCEL
argument_list|,
name|save
condition|?
name|GTK_STOCK_SAVE
else|:
name|GTK_STOCK_OPEN
argument_list|,
name|GTK_RESPONSE_OK
argument_list|,
name|NULL
argument_list|)
expr_stmt|;
name|chooser
operator|=
name|GTK_FILE_CHOOSER
argument_list|(
name|tool
operator|->
name|settings_dialog
argument_list|)
expr_stmt|;
name|g_object_set_data
argument_list|(
name|G_OBJECT
argument_list|(
name|chooser
argument_list|)
argument_list|,
literal|"save"
argument_list|,
name|GINT_TO_POINTER
argument_list|(
name|save
argument_list|)
argument_list|)
expr_stmt|;
name|gtk_window_set_role
argument_list|(
name|GTK_WINDOW
argument_list|(
name|chooser
argument_list|)
argument_list|,
literal|"gimp-load-save-settings"
argument_list|)
expr_stmt|;
name|gtk_window_set_position
argument_list|(
name|GTK_WINDOW
argument_list|(
name|chooser
argument_list|)
argument_list|,
name|GTK_WIN_POS_MOUSE
argument_list|)
expr_stmt|;
name|g_object_add_weak_pointer
argument_list|(
name|G_OBJECT
argument_list|(
name|chooser
argument_list|)
argument_list|,
operator|(
name|gpointer
operator|)
operator|&
name|tool
operator|->
name|settings_dialog
argument_list|)
expr_stmt|;
name|gtk_window_set_destroy_with_parent
argument_list|(
name|GTK_WINDOW
argument_list|(
name|chooser
argument_list|)
argument_list|,
name|TRUE
argument_list|)
expr_stmt|;
name|gtk_dialog_set_default_response
argument_list|(
name|GTK_DIALOG
argument_list|(
name|chooser
argument_list|)
argument_list|,
name|GTK_RESPONSE_OK
argument_list|)
expr_stmt|;
if|if
condition|(
name|save
condition|)
name|gtk_file_chooser_set_do_overwrite_confirmation
argument_list|(
name|chooser
argument_list|,
name|TRUE
argument_list|)
expr_stmt|;
name|g_signal_connect
argument_list|(
name|chooser
argument_list|,
literal|"response"
argument_list|,
name|G_CALLBACK
argument_list|(
name|settings_dialog_response
argument_list|)
argument_list|,
name|tool
argument_list|)
expr_stmt|;
name|g_signal_connect
argument_list|(
name|chooser
argument_list|,
literal|"delete-event"
argument_list|,
name|G_CALLBACK
argument_list|(
name|gtk_true
argument_list|)
argument_list|,
name|NULL
argument_list|)
expr_stmt|;
name|folder
operator|=
name|g_build_filename
argument_list|(
name|gimp_directory
argument_list|()
argument_list|,
name|settings_name
argument_list|,
name|NULL
argument_list|)
expr_stmt|;
if|if
condition|(
name|g_file_test
argument_list|(
name|folder
argument_list|,
name|G_FILE_TEST_IS_DIR
argument_list|)
condition|)
block|{
name|gtk_file_chooser_add_shortcut_folder
argument_list|(
name|chooser
argument_list|,
name|folder
argument_list|,
name|NULL
argument_list|)
expr_stmt|;
block|}
else|else
block|{
name|g_free
argument_list|(
name|folder
argument_list|)
expr_stmt|;
name|folder
operator|=
name|g_strdup
argument_list|(
name|g_get_home_dir
argument_list|()
argument_list|)
expr_stmt|;
block|}
if|if
condition|(
name|options
operator|->
name|settings
condition|)
name|gtk_file_chooser_set_filename
argument_list|(
name|chooser
argument_list|,
name|options
operator|->
name|settings
argument_list|)
expr_stmt|;
else|else
name|gtk_file_chooser_set_current_folder
argument_list|(
name|chooser
argument_list|,
name|folder
argument_list|)
expr_stmt|;
name|g_free
argument_list|(
name|folder
argument_list|)
expr_stmt|;
name|gimp_help_connect
argument_list|(
name|tool
operator|->
name|settings_dialog
argument_list|,
name|gimp_standard_help_func
argument_list|,
name|GIMP_TOOL
argument_list|(
name|tool
argument_list|)
operator|->
name|tool_info
operator|->
name|help_id
argument_list|,
name|NULL
argument_list|)
expr_stmt|;
name|gtk_widget_show
argument_list|(
name|tool
operator|->
name|settings_dialog
argument_list|)
expr_stmt|;
block|}
end_function

begin_function
specifier|static
name|void
DECL|function|gimp_image_map_tool_favorite_callback (GtkWidget * query_box,const gchar * string,gpointer data)
name|gimp_image_map_tool_favorite_callback
parameter_list|(
name|GtkWidget
modifier|*
name|query_box
parameter_list|,
specifier|const
name|gchar
modifier|*
name|string
parameter_list|,
name|gpointer
name|data
parameter_list|)
block|{
name|GimpImageMapTool
modifier|*
name|tool
init|=
name|GIMP_IMAGE_MAP_TOOL
argument_list|(
name|data
argument_list|)
decl_stmt|;
name|GimpConfig
modifier|*
name|config
decl_stmt|;
name|config
operator|=
name|gimp_config_duplicate
argument_list|(
name|GIMP_CONFIG
argument_list|(
name|tool
operator|->
name|config
argument_list|)
argument_list|)
expr_stmt|;
name|gimp_object_set_name
argument_list|(
name|GIMP_OBJECT
argument_list|(
name|config
argument_list|)
argument_list|,
name|string
argument_list|)
expr_stmt|;
name|gimp_container_insert
argument_list|(
name|GIMP_IMAGE_MAP_TOOL_GET_CLASS
argument_list|(
name|tool
argument_list|)
operator|->
name|recent_settings
argument_list|,
name|GIMP_OBJECT
argument_list|(
name|config
argument_list|)
argument_list|,
literal|0
argument_list|)
expr_stmt|;
name|g_object_unref
argument_list|(
name|config
argument_list|)
expr_stmt|;
block|}
end_function

begin_function
specifier|static
name|gboolean
DECL|function|gimp_image_map_tool_settings_load (GimpImageMapTool * tool,const gchar * filename)
name|gimp_image_map_tool_settings_load
parameter_list|(
name|GimpImageMapTool
modifier|*
name|tool
parameter_list|,
specifier|const
name|gchar
modifier|*
name|filename
parameter_list|)
block|{
name|GimpImageMapToolClass
modifier|*
name|tool_class
init|=
name|GIMP_IMAGE_MAP_TOOL_GET_CLASS
argument_list|(
name|tool
argument_list|)
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
name|settings_load
operator|!=
name|NULL
argument_list|,
name|FALSE
argument_list|)
expr_stmt|;
if|if
condition|(
operator|!
name|tool_class
operator|->
name|settings_load
argument_list|(
name|tool
argument_list|,
name|filename
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
name|tool
argument_list|)
operator|->
name|tool_info
operator|->
name|gimp
argument_list|,
name|G_OBJECT
argument_list|(
name|tool
operator|->
name|shell
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
name|gimp_image_map_tool_preview
argument_list|(
name|tool
argument_list|)
expr_stmt|;
name|g_object_set
argument_list|(
name|GIMP_TOOL_GET_OPTIONS
argument_list|(
name|tool
argument_list|)
argument_list|,
literal|"settings"
argument_list|,
name|filename
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
DECL|function|gimp_image_map_tool_settings_save (GimpImageMapTool * tool,const gchar * filename)
name|gimp_image_map_tool_settings_save
parameter_list|(
name|GimpImageMapTool
modifier|*
name|tool
parameter_list|,
specifier|const
name|gchar
modifier|*
name|filename
parameter_list|)
block|{
name|GimpImageMapToolClass
modifier|*
name|tool_class
init|=
name|GIMP_IMAGE_MAP_TOOL_GET_CLASS
argument_list|(
name|tool
argument_list|)
decl_stmt|;
name|GError
modifier|*
name|error
init|=
name|NULL
decl_stmt|;
name|gchar
modifier|*
name|display_name
decl_stmt|;
name|g_return_val_if_fail
argument_list|(
name|tool_class
operator|->
name|settings_save
operator|!=
name|NULL
argument_list|,
name|FALSE
argument_list|)
expr_stmt|;
if|if
condition|(
operator|!
name|tool_class
operator|->
name|settings_save
argument_list|(
name|tool
argument_list|,
name|filename
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
name|tool
argument_list|)
operator|->
name|tool_info
operator|->
name|gimp
argument_list|,
name|G_OBJECT
argument_list|(
name|tool
operator|->
name|shell
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
name|display_name
operator|=
name|g_filename_display_name
argument_list|(
name|filename
argument_list|)
expr_stmt|;
name|gimp_message
argument_list|(
name|GIMP_TOOL
argument_list|(
name|tool
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
name|tool
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
name|display_name
argument_list|)
expr_stmt|;
name|g_free
argument_list|(
name|display_name
argument_list|)
expr_stmt|;
name|g_object_set
argument_list|(
name|GIMP_TOOL_GET_OPTIONS
argument_list|(
name|tool
argument_list|)
argument_list|,
literal|"settings"
argument_list|,
name|filename
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

