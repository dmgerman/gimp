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
file|"libgimpwidgets/gimpwidgets.h"
end_include

begin_include
include|#
directive|include
file|"apptypes.h"
end_include

begin_include
include|#
directive|include
file|"dialog_handler.h"
end_include

begin_include
include|#
directive|include
file|"gimpcontext.h"
end_include

begin_include
include|#
directive|include
file|"gimpdnd.h"
end_include

begin_include
include|#
directive|include
file|"gimplist.h"
end_include

begin_include
include|#
directive|include
file|"gimppreview.h"
end_include

begin_include
include|#
directive|include
file|"gimpui.h"
end_include

begin_include
include|#
directive|include
file|"session.h"
end_include

begin_include
include|#
directive|include
file|"gimptoolinfo.h"
end_include

begin_include
include|#
directive|include
file|"tool_options.h"
end_include

begin_include
include|#
directive|include
file|"tool_options_dialog.h"
end_include

begin_include
include|#
directive|include
file|"tool.h"
end_include

begin_include
include|#
directive|include
file|"tool_manager.h"
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
name|GimpViewable
modifier|*
name|tool_options_dialog_drag_tool
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
name|tool_options_dialog_reset_callback
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
name|tool_options_dialog_close_callback
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
DECL|variable|options_label
specifier|static
name|GtkWidget
modifier|*
name|options_label
init|=
name|NULL
decl_stmt|;
end_decl_stmt

begin_decl_stmt
DECL|variable|options_preview
specifier|static
name|GtkWidget
modifier|*
name|options_preview
init|=
name|NULL
decl_stmt|;
end_decl_stmt

begin_decl_stmt
DECL|variable|options_eventbox
specifier|static
name|GtkWidget
modifier|*
name|options_eventbox
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
name|ToolOptions
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
name|void
DECL|function|tool_options_dialog_new (void)
name|tool_options_dialog_new
parameter_list|(
name|void
parameter_list|)
block|{
name|GimpToolInfo
modifier|*
name|tool_info
decl_stmt|;
name|GtkWidget
modifier|*
name|frame
decl_stmt|;
name|GtkWidget
modifier|*
name|hbox
decl_stmt|;
name|GtkWidget
modifier|*
name|vbox
decl_stmt|;
name|GList
modifier|*
name|list
decl_stmt|;
name|tool_info
operator|=
name|gimp_context_get_tool
argument_list|(
name|gimp_context_get_user
argument_list|()
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
comment|/*  The shell and main vbox  */
name|options_shell
operator|=
name|gimp_dialog_new
argument_list|(
name|_
argument_list|(
literal|"Tool Options"
argument_list|)
argument_list|,
literal|"tool_options"
argument_list|,
name|tool_manager_help_func
argument_list|,
literal|"dialogs/tool_options.html"
argument_list|,
name|GTK_WIN_POS_NONE
argument_list|,
name|FALSE
argument_list|,
name|TRUE
argument_list|,
name|TRUE
argument_list|,
name|_
argument_list|(
literal|"Reset"
argument_list|)
argument_list|,
name|tool_options_dialog_reset_callback
argument_list|,
name|NULL
argument_list|,
name|NULL
argument_list|,
operator|&
name|options_reset_button
argument_list|,
name|FALSE
argument_list|,
name|FALSE
argument_list|,
name|_
argument_list|(
literal|"Close"
argument_list|)
argument_list|,
name|tool_options_dialog_close_callback
argument_list|,
name|NULL
argument_list|,
name|NULL
argument_list|,
name|NULL
argument_list|,
name|TRUE
argument_list|,
name|TRUE
argument_list|,
name|NULL
argument_list|)
expr_stmt|;
comment|/*  hide the separator between the dialog's vbox and the action area  */
name|gtk_widget_hide
argument_list|(
name|GTK_WIDGET
argument_list|(
name|g_list_nth_data
argument_list|(
name|gtk_container_children
argument_list|(
name|GTK_CONTAINER
argument_list|(
name|GTK_BIN
argument_list|(
name|options_shell
argument_list|)
operator|->
name|child
argument_list|)
argument_list|)
argument_list|,
literal|0
argument_list|)
argument_list|)
argument_list|)
expr_stmt|;
comment|/*  Register dialog  */
name|dialog_register
argument_list|(
name|options_shell
argument_list|)
expr_stmt|;
name|session_set_window_geometry
argument_list|(
name|options_shell
argument_list|,
operator|&
name|tool_options_session_info
argument_list|,
name|FALSE
argument_list|)
expr_stmt|;
comment|/*  The outer frame  */
name|frame
operator|=
name|gtk_frame_new
argument_list|(
name|NULL
argument_list|)
expr_stmt|;
name|gtk_frame_set_shadow_type
argument_list|(
name|GTK_FRAME
argument_list|(
name|frame
argument_list|)
argument_list|,
name|GTK_SHADOW_IN
argument_list|)
expr_stmt|;
name|gtk_container_add
argument_list|(
name|GTK_CONTAINER
argument_list|(
name|GTK_DIALOG
argument_list|(
name|options_shell
argument_list|)
operator|->
name|vbox
argument_list|)
argument_list|,
name|frame
argument_list|)
expr_stmt|;
name|gtk_widget_show
argument_list|(
name|frame
argument_list|)
expr_stmt|;
comment|/*  The vbox containing the title frame and the options vbox  */
name|vbox
operator|=
name|gtk_vbox_new
argument_list|(
name|FALSE
argument_list|,
literal|0
argument_list|)
expr_stmt|;
name|gtk_container_add
argument_list|(
name|GTK_CONTAINER
argument_list|(
name|frame
argument_list|)
argument_list|,
name|vbox
argument_list|)
expr_stmt|;
name|gtk_widget_show
argument_list|(
name|vbox
argument_list|)
expr_stmt|;
comment|/*  The title frame  */
name|frame
operator|=
name|gtk_frame_new
argument_list|(
name|NULL
argument_list|)
expr_stmt|;
name|gtk_frame_set_shadow_type
argument_list|(
name|GTK_FRAME
argument_list|(
name|frame
argument_list|)
argument_list|,
name|GTK_SHADOW_OUT
argument_list|)
expr_stmt|;
name|gtk_box_pack_start
argument_list|(
name|GTK_BOX
argument_list|(
name|vbox
argument_list|)
argument_list|,
name|frame
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
name|frame
argument_list|)
expr_stmt|;
name|options_eventbox
operator|=
name|gtk_event_box_new
argument_list|()
expr_stmt|;
name|gtk_container_add
argument_list|(
name|GTK_CONTAINER
argument_list|(
name|frame
argument_list|)
argument_list|,
name|options_eventbox
argument_list|)
expr_stmt|;
name|gtk_widget_show
argument_list|(
name|options_eventbox
argument_list|)
expr_stmt|;
name|hbox
operator|=
name|gtk_hbox_new
argument_list|(
name|FALSE
argument_list|,
literal|4
argument_list|)
expr_stmt|;
name|gtk_container_add
argument_list|(
name|GTK_CONTAINER
argument_list|(
name|options_eventbox
argument_list|)
argument_list|,
name|hbox
argument_list|)
expr_stmt|;
name|gtk_widget_show
argument_list|(
name|hbox
argument_list|)
expr_stmt|;
name|options_preview
operator|=
name|gimp_preview_new
argument_list|(
name|GIMP_VIEWABLE
argument_list|(
name|tool_info
argument_list|)
argument_list|,
literal|22
argument_list|,
literal|0
argument_list|,
name|FALSE
argument_list|)
expr_stmt|;
name|gtk_box_pack_start
argument_list|(
name|GTK_BOX
argument_list|(
name|hbox
argument_list|)
argument_list|,
name|options_preview
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
name|options_preview
argument_list|)
expr_stmt|;
name|options_label
operator|=
name|gtk_label_new
argument_list|(
literal|""
argument_list|)
expr_stmt|;
name|gtk_box_pack_start
argument_list|(
name|GTK_BOX
argument_list|(
name|hbox
argument_list|)
argument_list|,
name|options_label
argument_list|,
name|FALSE
argument_list|,
name|FALSE
argument_list|,
literal|1
argument_list|)
expr_stmt|;
name|gtk_widget_show
argument_list|(
name|options_label
argument_list|)
expr_stmt|;
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
name|gtk_box_pack_start
argument_list|(
name|GTK_BOX
argument_list|(
name|vbox
argument_list|)
argument_list|,
name|options_vbox
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
name|options_vbox
argument_list|)
expr_stmt|;
comment|/*  dnd stuff  */
name|gimp_gtk_drag_dest_set_by_type
argument_list|(
name|options_shell
argument_list|,
name|GTK_DEST_DEFAULT_HIGHLIGHT
operator||
name|GTK_DEST_DEFAULT_MOTION
operator||
name|GTK_DEST_DEFAULT_DROP
argument_list|,
name|GIMP_TYPE_TOOL_INFO
argument_list|,
name|GDK_ACTION_COPY
argument_list|)
expr_stmt|;
name|gimp_dnd_viewable_dest_set
argument_list|(
name|options_shell
argument_list|,
name|GIMP_TYPE_TOOL_INFO
argument_list|,
name|tool_options_dialog_drop_tool
argument_list|,
name|NULL
argument_list|)
expr_stmt|;
name|gimp_gtk_drag_source_set_by_type
argument_list|(
name|options_eventbox
argument_list|,
name|GDK_BUTTON1_MASK
operator||
name|GDK_BUTTON2_MASK
argument_list|,
name|GIMP_TYPE_TOOL_INFO
argument_list|,
name|GDK_ACTION_COPY
argument_list|)
expr_stmt|;
name|gimp_dnd_viewable_source_set
argument_list|(
name|options_eventbox
argument_list|,
name|GIMP_TYPE_TOOL_INFO
argument_list|,
name|tool_options_dialog_drag_tool
argument_list|,
name|NULL
argument_list|)
expr_stmt|;
for|for
control|(
name|list
operator|=
name|GIMP_LIST
argument_list|(
name|global_tool_info_list
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
name|tool_info
operator|=
name|GIMP_TOOL_INFO
argument_list|(
name|list
operator|->
name|data
argument_list|)
expr_stmt|;
if|if
condition|(
name|tool_info
operator|->
name|tool_options
condition|)
name|tool_options_dialog_add
argument_list|(
name|tool_info
operator|->
name|tool_options
argument_list|)
expr_stmt|;
block|}
name|gtk_signal_connect_while_alive
argument_list|(
name|GTK_OBJECT
argument_list|(
name|gimp_context_get_user
argument_list|()
argument_list|)
argument_list|,
literal|"tool_changed"
argument_list|,
name|GTK_SIGNAL_FUNC
argument_list|(
name|tool_options_dialog_tool_changed
argument_list|)
argument_list|,
name|NULL
argument_list|,
name|GTK_OBJECT
argument_list|(
name|options_shell
argument_list|)
argument_list|)
expr_stmt|;
name|tool_info
operator|=
name|gimp_context_get_tool
argument_list|(
name|gimp_context_get_user
argument_list|()
argument_list|)
expr_stmt|;
name|tool_options_dialog_tool_changed
argument_list|(
name|gimp_context_get_user
argument_list|()
argument_list|,
name|tool_info
argument_list|,
name|NULL
argument_list|)
expr_stmt|;
block|}
end_function

begin_function
name|void
DECL|function|tool_options_dialog_show (void)
name|tool_options_dialog_show
parameter_list|(
name|void
parameter_list|)
block|{
if|if
condition|(
operator|!
name|GTK_WIDGET_VISIBLE
argument_list|(
name|options_shell
argument_list|)
condition|)
block|{
name|gtk_widget_show
argument_list|(
name|options_shell
argument_list|)
expr_stmt|;
block|}
else|else
block|{
name|gdk_window_raise
argument_list|(
name|options_shell
operator|->
name|window
argument_list|)
expr_stmt|;
block|}
block|}
end_function

begin_function
name|void
DECL|function|tool_options_dialog_free (void)
name|tool_options_dialog_free
parameter_list|(
name|void
parameter_list|)
block|{
name|session_get_window_info
argument_list|(
name|options_shell
argument_list|,
operator|&
name|tool_options_session_info
argument_list|)
expr_stmt|;
name|gtk_widget_destroy
argument_list|(
name|options_shell
argument_list|)
expr_stmt|;
block|}
end_function

begin_function
name|void
DECL|function|tool_options_dialog_add (ToolOptions * tool_options)
name|tool_options_dialog_add
parameter_list|(
name|ToolOptions
modifier|*
name|tool_options
parameter_list|)
block|{
name|g_return_if_fail
argument_list|(
name|tool_options
operator|!=
name|NULL
argument_list|)
expr_stmt|;
if|if
condition|(
name|options_vbox
condition|)
block|{
if|if
condition|(
operator|!
name|GTK_WIDGET_VISIBLE
argument_list|(
name|tool_options
operator|->
name|main_vbox
argument_list|)
condition|)
block|{
name|gtk_box_pack_start
argument_list|(
name|GTK_BOX
argument_list|(
name|options_vbox
argument_list|)
argument_list|,
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
block|}
block|}
block|}
end_function

begin_comment
comment|/*  private functions  */
end_comment

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
name|gtk_label_set_text
argument_list|(
name|GTK_LABEL
argument_list|(
name|options_label
argument_list|)
argument_list|,
name|tool_info
operator|->
name|blurb
argument_list|)
expr_stmt|;
if|if
condition|(
name|tool_info
operator|->
name|tool_options
operator|->
name|reset_func
condition|)
name|gtk_widget_set_sensitive
argument_list|(
name|options_reset_button
argument_list|,
name|TRUE
argument_list|)
expr_stmt|;
else|else
name|gtk_widget_set_sensitive
argument_list|(
name|options_reset_button
argument_list|,
name|FALSE
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
name|gimp_preview_set_viewable
argument_list|(
name|GIMP_PREVIEW
argument_list|(
name|options_preview
argument_list|)
argument_list|,
name|GIMP_VIEWABLE
argument_list|(
name|tool_info
argument_list|)
argument_list|)
expr_stmt|;
name|gimp_help_set_help_data
argument_list|(
name|options_label
operator|->
name|parent
operator|->
name|parent
argument_list|,
name|tool_info
operator|->
name|help
argument_list|,
name|tool_info
operator|->
name|help_data
argument_list|)
expr_stmt|;
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
name|gimp_context_set_tool
argument_list|(
name|gimp_context_get_user
argument_list|()
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
name|GimpViewable
modifier|*
DECL|function|tool_options_dialog_drag_tool (GtkWidget * widget,gpointer data)
name|tool_options_dialog_drag_tool
parameter_list|(
name|GtkWidget
modifier|*
name|widget
parameter_list|,
name|gpointer
name|data
parameter_list|)
block|{
return|return
operator|(
name|GimpViewable
operator|*
operator|)
name|gimp_context_get_tool
argument_list|(
name|gimp_context_get_user
argument_list|()
argument_list|)
return|;
block|}
end_function

begin_function
specifier|static
name|void
DECL|function|tool_options_dialog_close_callback (GtkWidget * widget,gpointer data)
name|tool_options_dialog_close_callback
parameter_list|(
name|GtkWidget
modifier|*
name|widget
parameter_list|,
name|gpointer
name|data
parameter_list|)
block|{
name|GtkWidget
modifier|*
name|shell
decl_stmt|;
name|shell
operator|=
operator|(
name|GtkWidget
operator|*
operator|)
name|data
expr_stmt|;
name|gimp_dialog_hide
argument_list|(
name|shell
argument_list|)
expr_stmt|;
block|}
end_function

begin_function
specifier|static
name|void
DECL|function|tool_options_dialog_reset_callback (GtkWidget * widget,gpointer data)
name|tool_options_dialog_reset_callback
parameter_list|(
name|GtkWidget
modifier|*
name|widget
parameter_list|,
name|gpointer
name|data
parameter_list|)
block|{
name|GimpToolInfo
modifier|*
name|tool_info
decl_stmt|;
name|GtkWidget
modifier|*
name|shell
decl_stmt|;
name|shell
operator|=
operator|(
name|GtkWidget
operator|*
operator|)
name|data
expr_stmt|;
if|if
condition|(
operator|!
name|active_tool
condition|)
return|return;
name|tool_info
operator|=
name|tool_manager_get_info_by_tool
argument_list|(
name|active_tool
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
literal|"%s(): no tool info registered for %s"
argument_list|,
name|G_GNUC_FUNCTION
argument_list|,
name|gtk_type_name
argument_list|(
name|GTK_OBJECT
argument_list|(
name|active_tool
argument_list|)
operator|->
name|klass
operator|->
name|type
argument_list|)
argument_list|)
expr_stmt|;
block|}
if|if
condition|(
name|tool_info
operator|->
name|tool_options
operator|->
name|reset_func
condition|)
name|tool_info
operator|->
name|tool_options
operator|->
name|reset_func
argument_list|()
expr_stmt|;
block|}
end_function

end_unit

