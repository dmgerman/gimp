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
file|"widgets/gimpdnd.h"
end_include

begin_include
include|#
directive|include
file|"widgets/gimpeditor.h"
end_include

begin_include
include|#
directive|include
file|"widgets/gimppreview.h"
end_include

begin_include
include|#
directive|include
file|"widgets/gimpwidgets-utils.h"
end_include

begin_include
include|#
directive|include
file|"tools/tool_options.h"
end_include

begin_include
include|#
directive|include
file|"tool-options-dialog.h"
end_include

begin_include
include|#
directive|include
file|"libgimp/gimpintl.h"
end_include

begin_comment
comment|/*  local function prototypes  */
end_comment

begin_function_decl
specifier|static
name|void
name|tool_options_dialog_destroy
parameter_list|(
name|GtkWidget
modifier|*
name|widget
parameter_list|,
name|gpointer
name|data
parameter_list|)
function_decl|;
end_function_decl

begin_function_decl
specifier|static
name|void
name|tool_options_dialog_tool_changed
parameter_list|(
name|GimpContext
modifier|*
name|context
parameter_list|,
name|GimpToolInfo
modifier|*
name|tool_info
parameter_list|,
name|gpointer
name|data
parameter_list|)
function_decl|;
end_function_decl

begin_function_decl
specifier|static
name|void
name|tool_options_dialog_drop_tool
parameter_list|(
name|GtkWidget
modifier|*
name|widget
parameter_list|,
name|GimpViewable
modifier|*
name|viewable
parameter_list|,
name|gpointer
name|data
parameter_list|)
function_decl|;
end_function_decl

begin_function_decl
specifier|static
name|void
name|tool_options_dialog_save_callback
parameter_list|(
name|GtkWidget
modifier|*
name|widget
parameter_list|,
name|GimpContext
modifier|*
name|context
parameter_list|)
function_decl|;
end_function_decl

begin_function_decl
specifier|static
name|void
name|tool_options_dialog_restore_callback
parameter_list|(
name|GtkWidget
modifier|*
name|widget
parameter_list|,
name|GimpContext
modifier|*
name|context
parameter_list|)
function_decl|;
end_function_decl

begin_function_decl
specifier|static
name|void
name|tool_options_dialog_reset_callback
parameter_list|(
name|GtkWidget
modifier|*
name|widget
parameter_list|,
name|GimpContext
modifier|*
name|context
parameter_list|)
function_decl|;
end_function_decl

begin_comment
comment|/*  private variables  */
end_comment

begin_decl_stmt
DECL|variable|options_shell
specifier|static
name|GtkWidget
modifier|*
name|options_shell
init|=
name|NULL
decl_stmt|;
end_decl_stmt

begin_decl_stmt
DECL|variable|options_vbox
specifier|static
name|GtkWidget
modifier|*
name|options_vbox
init|=
name|NULL
decl_stmt|;
end_decl_stmt

begin_decl_stmt
DECL|variable|options_save_button
specifier|static
name|GtkWidget
modifier|*
name|options_save_button
init|=
name|NULL
decl_stmt|;
end_decl_stmt

begin_decl_stmt
DECL|variable|options_revert_button
specifier|static
name|GtkWidget
modifier|*
name|options_revert_button
init|=
name|NULL
decl_stmt|;
end_decl_stmt

begin_decl_stmt
DECL|variable|options_reset_button
specifier|static
name|GtkWidget
modifier|*
name|options_reset_button
init|=
name|NULL
decl_stmt|;
end_decl_stmt

begin_decl_stmt
DECL|variable|visible_tool_options
specifier|static
name|GimpToolOptions
modifier|*
name|visible_tool_options
init|=
name|NULL
decl_stmt|;
end_decl_stmt

begin_comment
comment|/*  public functions  */
end_comment

begin_function
name|GtkWidget
modifier|*
DECL|function|tool_options_dialog_create (Gimp * gimp)
name|tool_options_dialog_create
parameter_list|(
name|Gimp
modifier|*
name|gimp
parameter_list|)
block|{
name|GimpContext
modifier|*
name|user_context
decl_stmt|;
name|GimpToolInfo
modifier|*
name|tool_info
decl_stmt|;
name|GtkWidget
modifier|*
name|editor
decl_stmt|;
name|GtkWidget
modifier|*
name|scrolled_win
decl_stmt|;
name|g_return_val_if_fail
argument_list|(
name|GIMP_IS_GIMP
argument_list|(
name|gimp
argument_list|)
argument_list|,
name|NULL
argument_list|)
expr_stmt|;
if|if
condition|(
name|options_shell
condition|)
return|return
name|options_shell
return|;
name|user_context
operator|=
name|gimp_get_user_context
argument_list|(
name|gimp
argument_list|)
expr_stmt|;
name|tool_info
operator|=
name|gimp_context_get_tool
argument_list|(
name|user_context
argument_list|)
expr_stmt|;
if|if
condition|(
operator|!
name|tool_info
condition|)
block|{
name|g_warning
argument_list|(
literal|"%s(): no tool info registered for active tool"
argument_list|,
name|G_GNUC_FUNCTION
argument_list|)
expr_stmt|;
block|}
name|editor
operator|=
name|g_object_new
argument_list|(
name|GIMP_TYPE_EDITOR
argument_list|,
name|NULL
argument_list|)
expr_stmt|;
name|gtk_widget_set_size_request
argument_list|(
name|editor
argument_list|,
operator|-
literal|1
argument_list|,
literal|200
argument_list|)
expr_stmt|;
name|options_shell
operator|=
name|editor
expr_stmt|;
name|g_signal_connect
argument_list|(
name|options_shell
argument_list|,
literal|"destroy"
argument_list|,
name|G_CALLBACK
argument_list|(
name|tool_options_dialog_destroy
argument_list|)
argument_list|,
name|NULL
argument_list|)
expr_stmt|;
name|options_save_button
operator|=
name|gimp_editor_add_button
argument_list|(
name|GIMP_EDITOR
argument_list|(
name|editor
argument_list|)
argument_list|,
name|GTK_STOCK_SAVE
argument_list|,
name|_
argument_list|(
literal|"Save current settings to disk"
argument_list|)
argument_list|,
name|NULL
argument_list|,
name|G_CALLBACK
argument_list|(
name|tool_options_dialog_save_callback
argument_list|)
argument_list|,
name|NULL
argument_list|,
name|user_context
argument_list|)
expr_stmt|;
name|options_revert_button
operator|=
name|gimp_editor_add_button
argument_list|(
name|GIMP_EDITOR
argument_list|(
name|editor
argument_list|)
argument_list|,
name|GTK_STOCK_REVERT_TO_SAVED
argument_list|,
name|_
argument_list|(
literal|"Restore saved settings"
argument_list|)
argument_list|,
name|NULL
argument_list|,
name|G_CALLBACK
argument_list|(
name|tool_options_dialog_restore_callback
argument_list|)
argument_list|,
name|NULL
argument_list|,
name|user_context
argument_list|)
expr_stmt|;
name|options_reset_button
operator|=
name|gimp_editor_add_button
argument_list|(
name|GIMP_EDITOR
argument_list|(
name|editor
argument_list|)
argument_list|,
name|GIMP_STOCK_RESET
argument_list|,
name|_
argument_list|(
literal|"Reset"
argument_list|)
argument_list|,
name|NULL
argument_list|,
name|G_CALLBACK
argument_list|(
name|tool_options_dialog_reset_callback
argument_list|)
argument_list|,
name|NULL
argument_list|,
name|user_context
argument_list|)
expr_stmt|;
name|scrolled_win
operator|=
name|gtk_scrolled_window_new
argument_list|(
name|NULL
argument_list|,
name|NULL
argument_list|)
expr_stmt|;
name|gtk_scrolled_window_set_policy
argument_list|(
name|GTK_SCROLLED_WINDOW
argument_list|(
name|scrolled_win
argument_list|)
argument_list|,
name|GTK_POLICY_NEVER
argument_list|,
name|GTK_POLICY_AUTOMATIC
argument_list|)
expr_stmt|;
name|gtk_container_add
argument_list|(
name|GTK_CONTAINER
argument_list|(
name|editor
argument_list|)
argument_list|,
name|scrolled_win
argument_list|)
expr_stmt|;
name|gtk_widget_show
argument_list|(
name|scrolled_win
argument_list|)
expr_stmt|;
comment|/*  The vbox containing the tool options  */
name|options_vbox
operator|=
name|gtk_vbox_new
argument_list|(
name|FALSE
argument_list|,
literal|0
argument_list|)
expr_stmt|;
name|gtk_container_set_border_width
argument_list|(
name|GTK_CONTAINER
argument_list|(
name|options_vbox
argument_list|)
argument_list|,
literal|2
argument_list|)
expr_stmt|;
name|gtk_scrolled_window_add_with_viewport
argument_list|(
name|GTK_SCROLLED_WINDOW
argument_list|(
name|scrolled_win
argument_list|)
argument_list|,
name|options_vbox
argument_list|)
expr_stmt|;
name|gtk_widget_show
argument_list|(
name|options_vbox
argument_list|)
expr_stmt|;
comment|/*  dnd stuff  */
name|gtk_drag_dest_set
argument_list|(
name|options_shell
argument_list|,
name|GTK_DEST_DEFAULT_ALL
argument_list|,
name|NULL
argument_list|,
literal|0
argument_list|,
name|GDK_ACTION_COPY
argument_list|)
expr_stmt|;
name|gimp_dnd_viewable_dest_add
argument_list|(
name|options_shell
argument_list|,
name|GIMP_TYPE_TOOL_INFO
argument_list|,
name|tool_options_dialog_drop_tool
argument_list|,
name|user_context
argument_list|)
expr_stmt|;
name|g_signal_connect_object
argument_list|(
name|user_context
argument_list|,
literal|"tool_changed"
argument_list|,
name|G_CALLBACK
argument_list|(
name|tool_options_dialog_tool_changed
argument_list|)
argument_list|,
name|options_shell
argument_list|,
literal|0
argument_list|)
expr_stmt|;
name|tool_options_dialog_tool_changed
argument_list|(
name|user_context
argument_list|,
name|tool_info
argument_list|,
name|options_shell
argument_list|)
expr_stmt|;
return|return
name|editor
return|;
block|}
end_function

begin_comment
comment|/*  private functions  */
end_comment

begin_function
specifier|static
name|void
DECL|function|tool_options_dialog_destroy (GtkWidget * widget,gpointer data)
name|tool_options_dialog_destroy
parameter_list|(
name|GtkWidget
modifier|*
name|widget
parameter_list|,
name|gpointer
name|data
parameter_list|)
block|{
name|GList
modifier|*
name|options
decl_stmt|;
name|GList
modifier|*
name|list
decl_stmt|;
name|options
operator|=
name|gtk_container_get_children
argument_list|(
name|GTK_CONTAINER
argument_list|(
name|options_vbox
argument_list|)
argument_list|)
expr_stmt|;
for|for
control|(
name|list
operator|=
name|options
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
name|g_object_ref
argument_list|(
name|list
operator|->
name|data
argument_list|)
expr_stmt|;
name|gtk_container_remove
argument_list|(
name|GTK_CONTAINER
argument_list|(
name|options_vbox
argument_list|)
argument_list|,
name|GTK_WIDGET
argument_list|(
name|list
operator|->
name|data
argument_list|)
argument_list|)
expr_stmt|;
block|}
name|g_list_free
argument_list|(
name|options
argument_list|)
expr_stmt|;
name|options_shell
operator|=
name|NULL
expr_stmt|;
block|}
end_function

begin_function
specifier|static
name|void
DECL|function|tool_options_dialog_tool_changed (GimpContext * context,GimpToolInfo * tool_info,gpointer data)
name|tool_options_dialog_tool_changed
parameter_list|(
name|GimpContext
modifier|*
name|context
parameter_list|,
name|GimpToolInfo
modifier|*
name|tool_info
parameter_list|,
name|gpointer
name|data
parameter_list|)
block|{
if|if
condition|(
name|visible_tool_options
operator|&&
operator|(
operator|!
name|tool_info
operator|||
name|tool_info
operator|->
name|tool_options
operator|!=
name|visible_tool_options
operator|)
condition|)
block|{
name|gtk_widget_hide
argument_list|(
name|visible_tool_options
operator|->
name|main_vbox
argument_list|)
expr_stmt|;
name|visible_tool_options
operator|=
name|NULL
expr_stmt|;
block|}
if|if
condition|(
name|tool_info
condition|)
block|{
if|if
condition|(
name|tool_info
operator|->
name|tool_options
condition|)
block|{
if|if
condition|(
operator|!
name|GTK_WIDGET
argument_list|(
name|tool_info
operator|->
name|tool_options
operator|->
name|main_vbox
argument_list|)
operator|->
name|parent
condition|)
name|gtk_box_pack_start
argument_list|(
name|GTK_BOX
argument_list|(
name|options_vbox
argument_list|)
argument_list|,
name|tool_info
operator|->
name|tool_options
operator|->
name|main_vbox
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
name|tool_info
operator|->
name|tool_options
operator|->
name|main_vbox
argument_list|)
expr_stmt|;
name|visible_tool_options
operator|=
name|tool_info
operator|->
name|tool_options
expr_stmt|;
name|gtk_widget_set_sensitive
argument_list|(
name|options_reset_button
argument_list|,
name|TRUE
argument_list|)
expr_stmt|;
block|}
else|else
block|{
name|gtk_widget_set_sensitive
argument_list|(
name|options_reset_button
argument_list|,
name|FALSE
argument_list|)
expr_stmt|;
block|}
block|}
block|}
end_function

begin_function
specifier|static
name|void
DECL|function|tool_options_dialog_drop_tool (GtkWidget * widget,GimpViewable * viewable,gpointer data)
name|tool_options_dialog_drop_tool
parameter_list|(
name|GtkWidget
modifier|*
name|widget
parameter_list|,
name|GimpViewable
modifier|*
name|viewable
parameter_list|,
name|gpointer
name|data
parameter_list|)
block|{
name|GimpContext
modifier|*
name|context
decl_stmt|;
name|context
operator|=
name|GIMP_CONTEXT
argument_list|(
name|data
argument_list|)
expr_stmt|;
name|gimp_context_set_tool
argument_list|(
name|context
argument_list|,
name|GIMP_TOOL_INFO
argument_list|(
name|viewable
argument_list|)
argument_list|)
expr_stmt|;
block|}
end_function

begin_function
specifier|static
name|void
DECL|function|tool_options_dialog_save_callback (GtkWidget * widget,GimpContext * context)
name|tool_options_dialog_save_callback
parameter_list|(
name|GtkWidget
modifier|*
name|widget
parameter_list|,
name|GimpContext
modifier|*
name|context
parameter_list|)
block|{
name|GimpToolInfo
modifier|*
name|tool_info
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
name|tool_info
operator|=
name|gimp_context_get_tool
argument_list|(
name|context
argument_list|)
expr_stmt|;
if|if
condition|(
operator|!
name|tool_info
condition|)
return|return;
name|filename
operator|=
name|g_build_filename
argument_list|(
name|gimp_directory
argument_list|()
argument_list|,
literal|"tool-options"
argument_list|,
name|gimp_object_get_name
argument_list|(
name|GIMP_OBJECT
argument_list|(
name|tool_info
argument_list|)
argument_list|)
argument_list|,
name|NULL
argument_list|)
expr_stmt|;
if|if
condition|(
operator|!
name|gimp_config_serialize
argument_list|(
name|G_OBJECT
argument_list|(
name|tool_info
operator|->
name|tool_options
argument_list|)
argument_list|,
name|filename
argument_list|,
literal|"# foo\n"
argument_list|,
literal|"# bar"
argument_list|,
name|NULL
argument_list|,
operator|&
name|error
argument_list|)
condition|)
block|{
name|g_message
argument_list|(
literal|"EEK: %s\n"
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
specifier|static
name|void
DECL|function|tool_options_dialog_restore_callback (GtkWidget * widget,GimpContext * context)
name|tool_options_dialog_restore_callback
parameter_list|(
name|GtkWidget
modifier|*
name|widget
parameter_list|,
name|GimpContext
modifier|*
name|context
parameter_list|)
block|{
name|GimpToolInfo
modifier|*
name|tool_info
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
name|tool_info
operator|=
name|gimp_context_get_tool
argument_list|(
name|context
argument_list|)
expr_stmt|;
if|if
condition|(
operator|!
name|tool_info
condition|)
return|return;
name|filename
operator|=
name|g_build_filename
argument_list|(
name|gimp_directory
argument_list|()
argument_list|,
literal|"tool-options"
argument_list|,
name|gimp_object_get_name
argument_list|(
name|GIMP_OBJECT
argument_list|(
name|tool_info
argument_list|)
argument_list|)
argument_list|,
name|NULL
argument_list|)
expr_stmt|;
if|if
condition|(
operator|!
name|gimp_config_deserialize
argument_list|(
name|G_OBJECT
argument_list|(
name|tool_info
operator|->
name|tool_options
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
name|g_message
argument_list|(
literal|"EEK: %s\n"
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
specifier|static
name|void
DECL|function|tool_options_dialog_reset_callback (GtkWidget * widget,GimpContext * context)
name|tool_options_dialog_reset_callback
parameter_list|(
name|GtkWidget
modifier|*
name|widget
parameter_list|,
name|GimpContext
modifier|*
name|context
parameter_list|)
block|{
name|GimpToolInfo
modifier|*
name|tool_info
decl_stmt|;
name|tool_info
operator|=
name|gimp_context_get_tool
argument_list|(
name|context
argument_list|)
expr_stmt|;
if|if
condition|(
operator|!
name|tool_info
condition|)
return|return;
name|gimp_tool_options_reset
argument_list|(
name|tool_info
operator|->
name|tool_options
argument_list|)
expr_stmt|;
block|}
end_function

end_unit

