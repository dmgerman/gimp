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
file|"gui-types.h"
end_include

begin_include
include|#
directive|include
file|"config/gimpconfig.h"
end_include

begin_include
include|#
directive|include
file|"config/gimpconfig-utils.h"
end_include

begin_include
include|#
directive|include
file|"core/gimp.h"
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
file|"core/gimptooloptions.h"
end_include

begin_include
include|#
directive|include
file|"widgets/gimpeditor.h"
end_include

begin_include
include|#
directive|include
file|"widgets/gimphelp-ids.h"
end_include

begin_include
include|#
directive|include
file|"widgets/gimpitemfactory.h"
end_include

begin_include
include|#
directive|include
file|"widgets/gimptooloptionseditor.h"
end_include

begin_include
include|#
directive|include
file|"tool-options-commands.h"
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
name|tool_options_save_callback
parameter_list|(
name|GtkWidget
modifier|*
name|widget
parameter_list|,
specifier|const
name|gchar
modifier|*
name|name
parameter_list|,
name|gpointer
name|data
parameter_list|)
function_decl|;
end_function_decl

begin_function_decl
specifier|static
name|void
name|tool_options_rename_callback
parameter_list|(
name|GtkWidget
modifier|*
name|widget
parameter_list|,
specifier|const
name|gchar
modifier|*
name|name
parameter_list|,
name|gpointer
name|data
parameter_list|)
function_decl|;
end_function_decl

begin_comment
comment|/*  public functions  */
end_comment

begin_function
name|void
DECL|function|tool_options_save_to_cmd_callback (GtkWidget * widget,gpointer data,guint action)
name|tool_options_save_to_cmd_callback
parameter_list|(
name|GtkWidget
modifier|*
name|widget
parameter_list|,
name|gpointer
name|data
parameter_list|,
name|guint
name|action
parameter_list|)
block|{
name|GimpToolOptions
modifier|*
name|options
init|=
name|GIMP_TOOL_OPTIONS
argument_list|(
name|data
argument_list|)
decl_stmt|;
name|gchar
modifier|*
name|name
decl_stmt|;
name|name
operator|=
name|g_strdup
argument_list|(
name|gimp_object_get_name
argument_list|(
name|GIMP_OBJECT
argument_list|(
name|options
argument_list|)
argument_list|)
argument_list|)
expr_stmt|;
name|gimp_config_sync
argument_list|(
name|GIMP_CONFIG
argument_list|(
name|options
operator|->
name|tool_info
operator|->
name|tool_options
argument_list|)
argument_list|,
name|GIMP_CONFIG
argument_list|(
name|options
argument_list|)
argument_list|,
literal|0
argument_list|)
expr_stmt|;
name|gimp_object_set_name
argument_list|(
name|GIMP_OBJECT
argument_list|(
name|options
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
block|}
end_function

begin_function
name|void
DECL|function|tool_options_save_new_cmd_callback (GtkWidget * widget,gpointer data,guint action)
name|tool_options_save_new_cmd_callback
parameter_list|(
name|GtkWidget
modifier|*
name|widget
parameter_list|,
name|gpointer
name|data
parameter_list|,
name|guint
name|action
parameter_list|)
block|{
name|GimpEditor
modifier|*
name|editor
init|=
name|GIMP_EDITOR
argument_list|(
name|data
argument_list|)
decl_stmt|;
name|GimpContext
modifier|*
name|context
decl_stmt|;
name|GimpToolInfo
modifier|*
name|tool_info
decl_stmt|;
name|GtkWidget
modifier|*
name|qbox
decl_stmt|;
name|context
operator|=
name|gimp_get_user_context
argument_list|(
name|editor
operator|->
name|item_factory
operator|->
name|gimp
argument_list|)
expr_stmt|;
name|tool_info
operator|=
name|gimp_context_get_tool
argument_list|(
name|context
argument_list|)
expr_stmt|;
name|qbox
operator|=
name|gimp_query_string_box
argument_list|(
name|_
argument_list|(
literal|"Save Tool Options"
argument_list|)
argument_list|,
name|GTK_WIDGET
argument_list|(
name|editor
argument_list|)
argument_list|,
name|gimp_standard_help_func
argument_list|,
name|GIMP_HELP_TOOL_OPTIONS_DIALOG
argument_list|,
name|_
argument_list|(
literal|"Enter a name for the saved options"
argument_list|)
argument_list|,
name|_
argument_list|(
literal|"Saved Options"
argument_list|)
argument_list|,
name|NULL
argument_list|,
name|NULL
argument_list|,
name|tool_options_save_callback
argument_list|,
name|tool_info
argument_list|)
expr_stmt|;
name|gtk_widget_show
argument_list|(
name|qbox
argument_list|)
expr_stmt|;
block|}
end_function

begin_function
name|void
DECL|function|tool_options_restore_from_cmd_callback (GtkWidget * widget,gpointer data,guint action)
name|tool_options_restore_from_cmd_callback
parameter_list|(
name|GtkWidget
modifier|*
name|widget
parameter_list|,
name|gpointer
name|data
parameter_list|,
name|guint
name|action
parameter_list|)
block|{
name|GimpToolOptions
modifier|*
name|options
init|=
name|GIMP_TOOL_OPTIONS
argument_list|(
name|data
argument_list|)
decl_stmt|;
name|gimp_config_sync
argument_list|(
name|GIMP_CONFIG
argument_list|(
name|options
argument_list|)
argument_list|,
name|GIMP_CONFIG
argument_list|(
name|options
operator|->
name|tool_info
operator|->
name|tool_options
argument_list|)
argument_list|,
literal|0
argument_list|)
expr_stmt|;
block|}
end_function

begin_function
name|void
DECL|function|tool_options_rename_saved_cmd_callback (GtkWidget * widget,gpointer data,guint action)
name|tool_options_rename_saved_cmd_callback
parameter_list|(
name|GtkWidget
modifier|*
name|widget
parameter_list|,
name|gpointer
name|data
parameter_list|,
name|guint
name|action
parameter_list|)
block|{
name|GimpToolOptions
modifier|*
name|options
init|=
name|GIMP_TOOL_OPTIONS
argument_list|(
name|data
argument_list|)
decl_stmt|;
name|GtkWidget
modifier|*
name|qbox
decl_stmt|;
name|qbox
operator|=
name|gimp_query_string_box
argument_list|(
name|_
argument_list|(
literal|"Rename Saved Tool Options"
argument_list|)
argument_list|,
name|widget
argument_list|,
name|gimp_standard_help_func
argument_list|,
name|GIMP_HELP_TOOL_OPTIONS_DIALOG
argument_list|,
name|_
argument_list|(
literal|"Enter a new name for the saved options"
argument_list|)
argument_list|,
name|GIMP_OBJECT
argument_list|(
name|options
argument_list|)
operator|->
name|name
argument_list|,
name|NULL
argument_list|,
name|NULL
argument_list|,
name|tool_options_rename_callback
argument_list|,
name|options
argument_list|)
expr_stmt|;
name|gtk_widget_show
argument_list|(
name|qbox
argument_list|)
expr_stmt|;
block|}
end_function

begin_function
name|void
DECL|function|tool_options_delete_saved_cmd_callback (GtkWidget * widget,gpointer data,guint action)
name|tool_options_delete_saved_cmd_callback
parameter_list|(
name|GtkWidget
modifier|*
name|widget
parameter_list|,
name|gpointer
name|data
parameter_list|,
name|guint
name|action
parameter_list|)
block|{
name|GimpToolOptions
modifier|*
name|options
init|=
name|GIMP_TOOL_OPTIONS
argument_list|(
name|data
argument_list|)
decl_stmt|;
name|gimp_container_remove
argument_list|(
name|options
operator|->
name|tool_info
operator|->
name|options_presets
argument_list|,
name|GIMP_OBJECT
argument_list|(
name|options
argument_list|)
argument_list|)
expr_stmt|;
block|}
end_function

begin_function
name|void
DECL|function|tool_options_reset_cmd_callback (GtkWidget * widget,gpointer data,guint action)
name|tool_options_reset_cmd_callback
parameter_list|(
name|GtkWidget
modifier|*
name|widget
parameter_list|,
name|gpointer
name|data
parameter_list|,
name|guint
name|action
parameter_list|)
block|{
name|GimpToolOptionsEditor
modifier|*
name|editor
init|=
name|GIMP_TOOL_OPTIONS_EDITOR
argument_list|(
name|data
argument_list|)
decl_stmt|;
if|if
condition|(
name|GTK_WIDGET_SENSITIVE
argument_list|(
name|editor
operator|->
name|reset_button
argument_list|)
condition|)
name|gtk_button_clicked
argument_list|(
name|GTK_BUTTON
argument_list|(
name|editor
operator|->
name|reset_button
argument_list|)
argument_list|)
expr_stmt|;
block|}
end_function

begin_function
name|void
DECL|function|tool_options_reset_all_cmd_callback (GtkWidget * widget,gpointer data,guint action)
name|tool_options_reset_all_cmd_callback
parameter_list|(
name|GtkWidget
modifier|*
name|widget
parameter_list|,
name|gpointer
name|data
parameter_list|,
name|guint
name|action
parameter_list|)
block|{
name|GimpToolOptionsEditor
modifier|*
name|editor
init|=
name|GIMP_TOOL_OPTIONS_EDITOR
argument_list|(
name|data
argument_list|)
decl_stmt|;
if|if
condition|(
name|GTK_WIDGET_SENSITIVE
argument_list|(
name|editor
operator|->
name|reset_button
argument_list|)
condition|)
name|gimp_button_extended_clicked
argument_list|(
name|GIMP_BUTTON
argument_list|(
name|editor
operator|->
name|reset_button
argument_list|)
argument_list|,
name|GDK_SHIFT_MASK
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
DECL|function|tool_options_save_callback (GtkWidget * widget,const gchar * name,gpointer data)
name|tool_options_save_callback
parameter_list|(
name|GtkWidget
modifier|*
name|widget
parameter_list|,
specifier|const
name|gchar
modifier|*
name|name
parameter_list|,
name|gpointer
name|data
parameter_list|)
block|{
name|GimpToolInfo
modifier|*
name|tool_info
init|=
name|GIMP_TOOL_INFO
argument_list|(
name|data
argument_list|)
decl_stmt|;
name|GimpConfig
modifier|*
name|copy
decl_stmt|;
if|if
condition|(
operator|!
name|name
operator|||
operator|!
name|strlen
argument_list|(
name|name
argument_list|)
condition|)
name|name
operator|=
name|_
argument_list|(
literal|"Saved Options"
argument_list|)
expr_stmt|;
name|copy
operator|=
name|gimp_config_duplicate
argument_list|(
name|GIMP_CONFIG
argument_list|(
name|tool_info
operator|->
name|tool_options
argument_list|)
argument_list|)
expr_stmt|;
name|gimp_object_set_name
argument_list|(
name|GIMP_OBJECT
argument_list|(
name|copy
argument_list|)
argument_list|,
name|name
argument_list|)
expr_stmt|;
name|gimp_list_uniquefy_name
argument_list|(
name|GIMP_LIST
argument_list|(
name|tool_info
operator|->
name|options_presets
argument_list|)
argument_list|,
name|GIMP_OBJECT
argument_list|(
name|copy
argument_list|)
argument_list|,
name|TRUE
argument_list|)
expr_stmt|;
name|gimp_container_insert
argument_list|(
name|tool_info
operator|->
name|options_presets
argument_list|,
name|GIMP_OBJECT
argument_list|(
name|copy
argument_list|)
argument_list|,
operator|-
literal|1
argument_list|)
expr_stmt|;
name|g_object_unref
argument_list|(
name|copy
argument_list|)
expr_stmt|;
block|}
end_function

begin_function
specifier|static
name|void
DECL|function|tool_options_rename_callback (GtkWidget * widget,const gchar * name,gpointer data)
name|tool_options_rename_callback
parameter_list|(
name|GtkWidget
modifier|*
name|widget
parameter_list|,
specifier|const
name|gchar
modifier|*
name|name
parameter_list|,
name|gpointer
name|data
parameter_list|)
block|{
name|GimpToolOptions
modifier|*
name|options
init|=
name|GIMP_TOOL_OPTIONS
argument_list|(
name|data
argument_list|)
decl_stmt|;
if|if
condition|(
operator|!
name|name
operator|||
operator|!
name|strlen
argument_list|(
name|name
argument_list|)
condition|)
name|name
operator|=
name|_
argument_list|(
literal|"Saved Options"
argument_list|)
expr_stmt|;
name|gimp_object_set_name
argument_list|(
name|GIMP_OBJECT
argument_list|(
name|options
argument_list|)
argument_list|,
name|name
argument_list|)
expr_stmt|;
name|gimp_list_uniquefy_name
argument_list|(
name|GIMP_LIST
argument_list|(
name|options
operator|->
name|tool_info
operator|->
name|options_presets
argument_list|)
argument_list|,
name|GIMP_OBJECT
argument_list|(
name|options
argument_list|)
argument_list|,
name|TRUE
argument_list|)
expr_stmt|;
block|}
end_function

end_unit

