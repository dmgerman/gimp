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
file|<gdk/gdkkeysyms.h>
end_include

begin_include
include|#
directive|include
file|"libgimp/gimp.h"
end_include

begin_include
include|#
directive|include
file|"libgimp/gimpui.h"
end_include

begin_include
include|#
directive|include
file|"script-fu-intl.h"
end_include

begin_include
include|#
directive|include
file|"siod-wrapper.h"
end_include

begin_include
include|#
directive|include
file|"script-fu-console.h"
end_include

begin_define
DECL|macro|TEXT_WIDTH
define|#
directive|define
name|TEXT_WIDTH
value|480
end_define

begin_define
DECL|macro|TEXT_HEIGHT
define|#
directive|define
name|TEXT_HEIGHT
value|400
end_define

begin_define
DECL|macro|BUFSIZE
define|#
directive|define
name|BUFSIZE
value|256
end_define

begin_typedef
typedef|typedef
struct|struct
DECL|struct|__anon289d03420108
block|{
DECL|member|dialog
name|GtkWidget
modifier|*
name|dialog
decl_stmt|;
DECL|member|console
name|GtkTextBuffer
modifier|*
name|console
decl_stmt|;
DECL|member|cc
name|GtkWidget
modifier|*
name|cc
decl_stmt|;
DECL|member|text_view
name|GtkWidget
modifier|*
name|text_view
decl_stmt|;
DECL|member|proc_browser
name|GtkWidget
modifier|*
name|proc_browser
decl_stmt|;
DECL|member|input_id
name|gint32
name|input_id
decl_stmt|;
DECL|member|history
name|GList
modifier|*
name|history
decl_stmt|;
DECL|member|history_len
name|gint
name|history_len
decl_stmt|;
DECL|member|history_cur
name|gint
name|history_cur
decl_stmt|;
DECL|member|history_max
name|gint
name|history_max
decl_stmt|;
DECL|typedef|ConsoleInterface
block|}
name|ConsoleInterface
typedef|;
end_typedef

begin_comment
comment|/*  *  Local Functions  */
end_comment

begin_function_decl
specifier|static
name|void
name|script_fu_console_interface
parameter_list|(
name|void
parameter_list|)
function_decl|;
end_function_decl

begin_function_decl
specifier|static
name|void
name|script_fu_response
parameter_list|(
name|GtkWidget
modifier|*
name|widget
parameter_list|,
name|gint
name|response_id
parameter_list|,
name|ConsoleInterface
modifier|*
name|console
parameter_list|)
function_decl|;
end_function_decl

begin_function_decl
specifier|static
name|void
name|script_fu_browse_callback
parameter_list|(
name|GtkWidget
modifier|*
name|widget
parameter_list|,
name|ConsoleInterface
modifier|*
name|console
parameter_list|)
function_decl|;
end_function_decl

begin_function_decl
specifier|static
name|void
name|script_fu_browse_response
parameter_list|(
name|GtkWidget
modifier|*
name|widget
parameter_list|,
name|gint
name|response_id
parameter_list|,
name|ConsoleInterface
modifier|*
name|console
parameter_list|)
function_decl|;
end_function_decl

begin_function_decl
specifier|static
name|void
name|script_fu_browse_row_activated
parameter_list|(
name|GtkDialog
modifier|*
name|dialog
parameter_list|)
function_decl|;
end_function_decl

begin_function_decl
specifier|static
name|gboolean
name|script_fu_cc_is_empty
parameter_list|(
name|ConsoleInterface
modifier|*
name|console
parameter_list|)
function_decl|;
end_function_decl

begin_function_decl
specifier|static
name|gboolean
name|script_fu_cc_key_function
parameter_list|(
name|GtkWidget
modifier|*
name|widget
parameter_list|,
name|GdkEventKey
modifier|*
name|event
parameter_list|,
name|ConsoleInterface
modifier|*
name|console
parameter_list|)
function_decl|;
end_function_decl

begin_function_decl
specifier|static
name|void
name|script_fu_open_siod_console
parameter_list|(
name|void
parameter_list|)
function_decl|;
end_function_decl

begin_function_decl
specifier|static
name|void
name|script_fu_close_siod_console
parameter_list|(
name|void
parameter_list|)
function_decl|;
end_function_decl

begin_comment
comment|/*  *  Local variables  */
end_comment

begin_decl_stmt
DECL|variable|cint
specifier|static
name|ConsoleInterface
name|cint
init|=
block|{
name|NULL
block|,
comment|/*  dialog  */
name|NULL
block|,
comment|/*  console  */
name|NULL
block|,
comment|/*  current command  */
name|NULL
block|,
comment|/*  text view  */
name|NULL
block|,
comment|/*  proc browser  */
operator|-
literal|1
block|,
comment|/*  input id  */
name|NULL
block|,
literal|0
block|,
literal|0
block|,
literal|50
block|}
decl_stmt|;
end_decl_stmt

begin_comment
comment|/*  *  Function definitions  */
end_comment

begin_function
name|void
DECL|function|script_fu_console_run (const gchar * name,gint nparams,const GimpParam * params,gint * nreturn_vals,GimpParam ** return_vals)
name|script_fu_console_run
parameter_list|(
specifier|const
name|gchar
modifier|*
name|name
parameter_list|,
name|gint
name|nparams
parameter_list|,
specifier|const
name|GimpParam
modifier|*
name|params
parameter_list|,
name|gint
modifier|*
name|nreturn_vals
parameter_list|,
name|GimpParam
modifier|*
modifier|*
name|return_vals
parameter_list|)
block|{
specifier|static
name|GimpParam
name|values
index|[
literal|1
index|]
decl_stmt|;
name|GimpPDBStatusType
name|status
init|=
name|GIMP_PDB_SUCCESS
decl_stmt|;
name|GimpRunMode
name|run_mode
decl_stmt|;
name|run_mode
operator|=
name|params
index|[
literal|0
index|]
operator|.
name|data
operator|.
name|d_int32
expr_stmt|;
switch|switch
condition|(
name|run_mode
condition|)
block|{
case|case
name|GIMP_RUN_INTERACTIVE
case|:
comment|/*  Enable SIOD output  */
name|script_fu_open_siod_console
argument_list|()
expr_stmt|;
comment|/*  Run the interface  */
name|script_fu_console_interface
argument_list|()
expr_stmt|;
comment|/*  Clean up  */
name|script_fu_close_siod_console
argument_list|()
expr_stmt|;
break|break;
case|case
name|GIMP_RUN_WITH_LAST_VALS
case|:
case|case
name|GIMP_RUN_NONINTERACTIVE
case|:
name|status
operator|=
name|GIMP_PDB_CALLING_ERROR
expr_stmt|;
name|g_message
argument_list|(
name|_
argument_list|(
literal|"Script-Fu console mode allows only interactive invocation"
argument_list|)
argument_list|)
expr_stmt|;
break|break;
default|default:
break|break;
block|}
operator|*
name|nreturn_vals
operator|=
literal|1
expr_stmt|;
operator|*
name|return_vals
operator|=
name|values
expr_stmt|;
name|values
index|[
literal|0
index|]
operator|.
name|type
operator|=
name|GIMP_PDB_STATUS
expr_stmt|;
name|values
index|[
literal|0
index|]
operator|.
name|data
operator|.
name|d_status
operator|=
name|status
expr_stmt|;
block|}
end_function

begin_function
specifier|static
name|void
DECL|function|script_fu_console_interface (void)
name|script_fu_console_interface
parameter_list|(
name|void
parameter_list|)
block|{
name|ConsoleInterface
modifier|*
name|console
decl_stmt|;
name|GtkWidget
modifier|*
name|vbox
decl_stmt|;
name|GtkWidget
modifier|*
name|button
decl_stmt|;
name|GtkWidget
modifier|*
name|scrolled_window
decl_stmt|;
name|GtkWidget
modifier|*
name|hbox
decl_stmt|;
name|gimp_ui_init
argument_list|(
literal|"script-fu"
argument_list|,
name|FALSE
argument_list|)
expr_stmt|;
name|console
operator|=
operator|&
name|cint
expr_stmt|;
name|console
operator|->
name|input_id
operator|=
operator|-
literal|1
expr_stmt|;
name|console
operator|->
name|history
operator|=
name|NULL
expr_stmt|;
name|console
operator|->
name|history_len
operator|=
literal|0
expr_stmt|;
name|console
operator|->
name|history_cur
operator|=
literal|0
expr_stmt|;
name|console
operator|->
name|history_max
operator|=
literal|50
expr_stmt|;
name|console
operator|->
name|dialog
operator|=
name|gimp_dialog_new
argument_list|(
name|_
argument_list|(
literal|"Script-Fu Console"
argument_list|)
argument_list|,
literal|"script-fu-console"
argument_list|,
name|NULL
argument_list|,
literal|0
argument_list|,
name|gimp_standard_help_func
argument_list|,
literal|"plug-in-script-fu-console"
argument_list|,
name|GTK_STOCK_CLOSE
argument_list|,
name|GTK_RESPONSE_CLOSE
argument_list|,
name|NULL
argument_list|)
expr_stmt|;
name|g_signal_connect
argument_list|(
name|console
operator|->
name|dialog
argument_list|,
literal|"response"
argument_list|,
name|G_CALLBACK
argument_list|(
name|script_fu_response
argument_list|)
argument_list|,
name|console
argument_list|)
expr_stmt|;
name|g_signal_connect
argument_list|(
name|console
operator|->
name|dialog
argument_list|,
literal|"destroy"
argument_list|,
name|G_CALLBACK
argument_list|(
name|gtk_widget_destroyed
argument_list|)
argument_list|,
operator|&
name|console
operator|->
name|dialog
argument_list|)
expr_stmt|;
comment|/*  The main vbox  */
name|vbox
operator|=
name|gtk_vbox_new
argument_list|(
name|FALSE
argument_list|,
literal|12
argument_list|)
expr_stmt|;
name|gtk_container_set_border_width
argument_list|(
name|GTK_CONTAINER
argument_list|(
name|vbox
argument_list|)
argument_list|,
literal|12
argument_list|)
expr_stmt|;
name|gtk_box_pack_start
argument_list|(
name|GTK_BOX
argument_list|(
name|GTK_DIALOG
argument_list|(
name|console
operator|->
name|dialog
argument_list|)
operator|->
name|vbox
argument_list|)
argument_list|,
name|vbox
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
name|vbox
argument_list|)
expr_stmt|;
comment|/*  The output text widget  */
name|scrolled_window
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
name|scrolled_window
argument_list|)
argument_list|,
name|GTK_POLICY_AUTOMATIC
argument_list|,
name|GTK_POLICY_ALWAYS
argument_list|)
expr_stmt|;
name|gtk_box_pack_start
argument_list|(
name|GTK_BOX
argument_list|(
name|vbox
argument_list|)
argument_list|,
name|scrolled_window
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
name|scrolled_window
argument_list|)
expr_stmt|;
name|console
operator|->
name|console
operator|=
name|gtk_text_buffer_new
argument_list|(
name|NULL
argument_list|)
expr_stmt|;
name|console
operator|->
name|text_view
operator|=
name|gtk_text_view_new_with_buffer
argument_list|(
name|console
operator|->
name|console
argument_list|)
expr_stmt|;
name|g_object_unref
argument_list|(
name|console
operator|->
name|console
argument_list|)
expr_stmt|;
name|gtk_text_view_set_editable
argument_list|(
name|GTK_TEXT_VIEW
argument_list|(
name|console
operator|->
name|text_view
argument_list|)
argument_list|,
name|FALSE
argument_list|)
expr_stmt|;
name|gtk_text_view_set_left_margin
argument_list|(
name|GTK_TEXT_VIEW
argument_list|(
name|console
operator|->
name|text_view
argument_list|)
argument_list|,
literal|12
argument_list|)
expr_stmt|;
name|gtk_text_view_set_right_margin
argument_list|(
name|GTK_TEXT_VIEW
argument_list|(
name|console
operator|->
name|text_view
argument_list|)
argument_list|,
literal|12
argument_list|)
expr_stmt|;
name|gtk_widget_set_size_request
argument_list|(
name|console
operator|->
name|text_view
argument_list|,
name|TEXT_WIDTH
argument_list|,
name|TEXT_HEIGHT
argument_list|)
expr_stmt|;
name|gtk_container_add
argument_list|(
name|GTK_CONTAINER
argument_list|(
name|scrolled_window
argument_list|)
argument_list|,
name|console
operator|->
name|text_view
argument_list|)
expr_stmt|;
name|gtk_widget_show
argument_list|(
name|console
operator|->
name|text_view
argument_list|)
expr_stmt|;
name|gtk_text_buffer_create_tag
argument_list|(
name|console
operator|->
name|console
argument_list|,
literal|"strong"
argument_list|,
literal|"weight"
argument_list|,
name|PANGO_WEIGHT_BOLD
argument_list|,
literal|"size"
argument_list|,
literal|12
operator|*
name|PANGO_SCALE
argument_list|,
name|NULL
argument_list|)
expr_stmt|;
name|gtk_text_buffer_create_tag
argument_list|(
name|console
operator|->
name|console
argument_list|,
literal|"emphasis"
argument_list|,
literal|"style"
argument_list|,
name|PANGO_STYLE_OBLIQUE
argument_list|,
literal|"size"
argument_list|,
literal|10
operator|*
name|PANGO_SCALE
argument_list|,
name|NULL
argument_list|)
expr_stmt|;
name|gtk_text_buffer_create_tag
argument_list|(
name|console
operator|->
name|console
argument_list|,
literal|"weak"
argument_list|,
literal|"size"
argument_list|,
literal|10
operator|*
name|PANGO_SCALE
argument_list|,
name|NULL
argument_list|)
expr_stmt|;
block|{
specifier|const
name|gchar
modifier|*
name|greeting_texts
index|[]
init|=
block|{
literal|"weak"
block|,
literal|"\n"
block|,
literal|"strong"
block|,
literal|"Welcome to SIOD, Scheme In One Defun\n"
block|,
literal|"weak"
block|,
literal|"(C) Copyright 1988-1994 Paradigm Associates Inc.\n\n"
block|,
literal|"strong"
block|,
literal|"Script-Fu Console - "
block|,
literal|"emphasis"
block|,
literal|"Interactive Scheme Development\n"
block|,
name|NULL
block|}
decl_stmt|;
name|GtkTextIter
name|cursor
decl_stmt|;
name|gint
name|i
decl_stmt|;
name|gtk_text_buffer_get_end_iter
argument_list|(
name|console
operator|->
name|console
argument_list|,
operator|&
name|cursor
argument_list|)
expr_stmt|;
for|for
control|(
name|i
operator|=
literal|0
init|;
name|greeting_texts
index|[
name|i
index|]
condition|;
name|i
operator|+=
literal|2
control|)
block|{
name|gtk_text_buffer_insert_with_tags_by_name
argument_list|(
name|console
operator|->
name|console
argument_list|,
operator|&
name|cursor
argument_list|,
name|greeting_texts
index|[
name|i
operator|+
literal|1
index|]
argument_list|,
operator|-
literal|1
argument_list|,
name|greeting_texts
index|[
name|i
index|]
argument_list|,
name|NULL
argument_list|)
expr_stmt|;
block|}
block|}
comment|/*  The current command  */
name|hbox
operator|=
name|gtk_hbox_new
argument_list|(
name|FALSE
argument_list|,
literal|6
argument_list|)
expr_stmt|;
name|gtk_box_pack_start
argument_list|(
name|GTK_BOX
argument_list|(
name|vbox
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
name|console
operator|->
name|cc
operator|=
name|gtk_entry_new
argument_list|()
expr_stmt|;
name|gtk_box_pack_start
argument_list|(
name|GTK_BOX
argument_list|(
name|hbox
argument_list|)
argument_list|,
name|console
operator|->
name|cc
argument_list|,
name|TRUE
argument_list|,
name|TRUE
argument_list|,
literal|0
argument_list|)
expr_stmt|;
name|gtk_widget_grab_focus
argument_list|(
name|console
operator|->
name|cc
argument_list|)
expr_stmt|;
name|gtk_widget_show
argument_list|(
name|console
operator|->
name|cc
argument_list|)
expr_stmt|;
name|g_signal_connect
argument_list|(
name|console
operator|->
name|cc
argument_list|,
literal|"key-press-event"
argument_list|,
name|G_CALLBACK
argument_list|(
name|script_fu_cc_key_function
argument_list|)
argument_list|,
name|console
argument_list|)
expr_stmt|;
name|button
operator|=
name|gtk_button_new_with_mnemonic
argument_list|(
name|_
argument_list|(
literal|"_Browse..."
argument_list|)
argument_list|)
expr_stmt|;
name|gtk_misc_set_padding
argument_list|(
name|GTK_MISC
argument_list|(
name|GTK_BIN
argument_list|(
name|button
argument_list|)
operator|->
name|child
argument_list|)
argument_list|,
literal|2
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
name|button
argument_list|,
name|FALSE
argument_list|,
name|TRUE
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
name|script_fu_browse_callback
argument_list|)
argument_list|,
name|console
argument_list|)
expr_stmt|;
comment|/*  Initialize the history  */
name|console
operator|->
name|history
operator|=
name|g_list_append
argument_list|(
name|console
operator|->
name|history
argument_list|,
name|NULL
argument_list|)
expr_stmt|;
name|console
operator|->
name|history_len
operator|=
literal|1
expr_stmt|;
name|gtk_widget_show
argument_list|(
name|console
operator|->
name|dialog
argument_list|)
expr_stmt|;
name|gtk_main
argument_list|()
expr_stmt|;
name|g_source_remove
argument_list|(
name|console
operator|->
name|input_id
argument_list|)
expr_stmt|;
if|if
condition|(
name|console
operator|->
name|dialog
condition|)
name|gtk_widget_destroy
argument_list|(
name|console
operator|->
name|dialog
argument_list|)
expr_stmt|;
block|}
end_function

begin_function
specifier|static
name|void
DECL|function|script_fu_response (GtkWidget * widget,gint response_id,ConsoleInterface * console)
name|script_fu_response
parameter_list|(
name|GtkWidget
modifier|*
name|widget
parameter_list|,
name|gint
name|response_id
parameter_list|,
name|ConsoleInterface
modifier|*
name|console
parameter_list|)
block|{
name|gtk_main_quit
argument_list|()
expr_stmt|;
block|}
end_function

begin_function
specifier|static
name|void
DECL|function|script_fu_browse_callback (GtkWidget * widget,ConsoleInterface * console)
name|script_fu_browse_callback
parameter_list|(
name|GtkWidget
modifier|*
name|widget
parameter_list|,
name|ConsoleInterface
modifier|*
name|console
parameter_list|)
block|{
if|if
condition|(
operator|!
name|console
operator|->
name|proc_browser
condition|)
block|{
name|console
operator|->
name|proc_browser
operator|=
name|gimp_proc_browser_dialog_new
argument_list|()
expr_stmt|;
name|gtk_dialog_add_buttons
argument_list|(
name|GTK_DIALOG
argument_list|(
name|console
operator|->
name|proc_browser
argument_list|)
argument_list|,
name|GTK_STOCK_APPLY
argument_list|,
name|GTK_RESPONSE_APPLY
argument_list|,
name|GTK_STOCK_CLOSE
argument_list|,
name|GTK_RESPONSE_CLOSE
argument_list|,
name|NULL
argument_list|)
expr_stmt|;
name|gtk_dialog_set_default_response
argument_list|(
name|GTK_DIALOG
argument_list|(
name|console
operator|->
name|proc_browser
argument_list|)
argument_list|,
name|GTK_RESPONSE_APPLY
argument_list|)
expr_stmt|;
name|g_object_add_weak_pointer
argument_list|(
name|G_OBJECT
argument_list|(
name|console
operator|->
name|proc_browser
argument_list|)
argument_list|,
operator|(
name|gpointer
operator|)
operator|&
name|console
operator|->
name|proc_browser
argument_list|)
expr_stmt|;
name|gtk_window_set_transient_for
argument_list|(
name|GTK_WINDOW
argument_list|(
name|console
operator|->
name|proc_browser
argument_list|)
argument_list|,
name|GTK_WINDOW
argument_list|(
name|console
operator|->
name|dialog
argument_list|)
argument_list|)
expr_stmt|;
name|g_signal_connect
argument_list|(
name|console
operator|->
name|proc_browser
argument_list|,
literal|"response"
argument_list|,
name|G_CALLBACK
argument_list|(
name|script_fu_browse_response
argument_list|)
argument_list|,
name|console
argument_list|)
expr_stmt|;
name|g_signal_connect
argument_list|(
name|console
operator|->
name|proc_browser
argument_list|,
literal|"row-activated"
argument_list|,
name|G_CALLBACK
argument_list|(
name|script_fu_browse_row_activated
argument_list|)
argument_list|,
name|console
argument_list|)
expr_stmt|;
block|}
name|gtk_window_present
argument_list|(
name|GTK_WINDOW
argument_list|(
name|console
operator|->
name|proc_browser
argument_list|)
argument_list|)
expr_stmt|;
block|}
end_function

begin_function
specifier|static
name|void
DECL|function|script_fu_browse_response (GtkWidget * widget,gint response_id,ConsoleInterface * console)
name|script_fu_browse_response
parameter_list|(
name|GtkWidget
modifier|*
name|widget
parameter_list|,
name|gint
name|response_id
parameter_list|,
name|ConsoleInterface
modifier|*
name|console
parameter_list|)
block|{
name|GimpProcBrowserDialog
modifier|*
name|dialog
init|=
name|GIMP_PROC_BROWSER_DIALOG
argument_list|(
name|widget
argument_list|)
decl_stmt|;
name|gchar
modifier|*
name|proc_name
decl_stmt|;
name|gchar
modifier|*
name|proc_blurb
decl_stmt|;
name|gchar
modifier|*
name|proc_help
decl_stmt|;
name|gchar
modifier|*
name|proc_author
decl_stmt|;
name|gchar
modifier|*
name|proc_copyright
decl_stmt|;
name|gchar
modifier|*
name|proc_date
decl_stmt|;
name|GimpPDBProcType
name|proc_type
decl_stmt|;
name|gint
name|n_params
decl_stmt|;
name|gint
name|n_return_vals
decl_stmt|;
name|GimpParamDef
modifier|*
name|params
decl_stmt|;
name|GimpParamDef
modifier|*
name|return_vals
decl_stmt|;
name|gint
name|i
decl_stmt|;
name|GString
modifier|*
name|text
decl_stmt|;
if|if
condition|(
name|response_id
operator|!=
name|GTK_RESPONSE_APPLY
condition|)
block|{
name|gtk_widget_destroy
argument_list|(
name|widget
argument_list|)
expr_stmt|;
return|return;
block|}
name|proc_name
operator|=
name|gimp_proc_browser_dialog_get_selected
argument_list|(
name|dialog
argument_list|)
expr_stmt|;
if|if
condition|(
name|proc_name
operator|==
name|NULL
condition|)
return|return;
name|gimp_procedural_db_proc_info
argument_list|(
name|proc_name
argument_list|,
operator|&
name|proc_blurb
argument_list|,
operator|&
name|proc_help
argument_list|,
operator|&
name|proc_author
argument_list|,
operator|&
name|proc_copyright
argument_list|,
operator|&
name|proc_date
argument_list|,
operator|&
name|proc_type
argument_list|,
operator|&
name|n_params
argument_list|,
operator|&
name|n_return_vals
argument_list|,
operator|&
name|params
argument_list|,
operator|&
name|return_vals
argument_list|)
expr_stmt|;
name|text
operator|=
name|g_string_new
argument_list|(
literal|"("
argument_list|)
expr_stmt|;
name|text
operator|=
name|g_string_append
argument_list|(
name|text
argument_list|,
name|proc_name
argument_list|)
expr_stmt|;
for|for
control|(
name|i
operator|=
literal|0
init|;
name|i
operator|<
name|n_params
condition|;
name|i
operator|++
control|)
block|{
name|text
operator|=
name|g_string_append_c
argument_list|(
name|text
argument_list|,
literal|' '
argument_list|)
expr_stmt|;
name|text
operator|=
name|g_string_append
argument_list|(
name|text
argument_list|,
name|params
index|[
name|i
index|]
operator|.
name|name
argument_list|)
expr_stmt|;
block|}
name|text
operator|=
name|g_string_append_c
argument_list|(
name|text
argument_list|,
literal|')'
argument_list|)
expr_stmt|;
name|gtk_entry_set_text
argument_list|(
name|GTK_ENTRY
argument_list|(
name|console
operator|->
name|cc
argument_list|)
argument_list|,
name|text
operator|->
name|str
argument_list|)
expr_stmt|;
name|g_string_free
argument_list|(
name|text
argument_list|,
name|TRUE
argument_list|)
expr_stmt|;
name|g_free
argument_list|(
name|proc_name
argument_list|)
expr_stmt|;
name|g_free
argument_list|(
name|proc_blurb
argument_list|)
expr_stmt|;
name|g_free
argument_list|(
name|proc_help
argument_list|)
expr_stmt|;
name|g_free
argument_list|(
name|proc_author
argument_list|)
expr_stmt|;
name|g_free
argument_list|(
name|proc_copyright
argument_list|)
expr_stmt|;
name|g_free
argument_list|(
name|proc_date
argument_list|)
expr_stmt|;
name|gimp_destroy_paramdefs
argument_list|(
name|params
argument_list|,
name|n_params
argument_list|)
expr_stmt|;
name|gimp_destroy_paramdefs
argument_list|(
name|return_vals
argument_list|,
name|n_return_vals
argument_list|)
expr_stmt|;
block|}
end_function

begin_function
specifier|static
name|void
DECL|function|script_fu_browse_row_activated (GtkDialog * dialog)
name|script_fu_browse_row_activated
parameter_list|(
name|GtkDialog
modifier|*
name|dialog
parameter_list|)
block|{
name|gtk_dialog_response
argument_list|(
name|dialog
argument_list|,
name|GTK_RESPONSE_APPLY
argument_list|)
expr_stmt|;
block|}
end_function

begin_function
specifier|static
name|gboolean
DECL|function|script_fu_console_idle_scroll_end (ConsoleInterface * console)
name|script_fu_console_idle_scroll_end
parameter_list|(
name|ConsoleInterface
modifier|*
name|console
parameter_list|)
block|{
name|GtkAdjustment
modifier|*
name|adj
init|=
name|GTK_TEXT_VIEW
argument_list|(
name|console
operator|->
name|text_view
argument_list|)
operator|->
name|vadjustment
decl_stmt|;
name|gtk_adjustment_set_value
argument_list|(
name|adj
argument_list|,
name|adj
operator|->
name|upper
operator|-
name|adj
operator|->
name|page_size
argument_list|)
expr_stmt|;
return|return
name|FALSE
return|;
block|}
end_function

begin_function
specifier|static
name|void
DECL|function|script_fu_console_scroll_end (ConsoleInterface * console)
name|script_fu_console_scroll_end
parameter_list|(
name|ConsoleInterface
modifier|*
name|console
parameter_list|)
block|{
comment|/*  the text view idle updates so we need to idle scroll too    */
name|g_idle_add
argument_list|(
operator|(
name|GSourceFunc
operator|)
name|script_fu_console_idle_scroll_end
argument_list|,
name|console
argument_list|)
expr_stmt|;
block|}
end_function

begin_function
name|void
DECL|function|script_fu_output_to_console (gchar * text)
name|script_fu_output_to_console
parameter_list|(
name|gchar
modifier|*
name|text
parameter_list|)
block|{
name|GtkTextIter
name|cursor
decl_stmt|;
name|gtk_text_buffer_get_end_iter
argument_list|(
name|cint
operator|.
name|console
argument_list|,
operator|&
name|cursor
argument_list|)
expr_stmt|;
name|gtk_text_buffer_insert_with_tags_by_name
argument_list|(
name|cint
operator|.
name|console
argument_list|,
operator|&
name|cursor
argument_list|,
name|text
argument_list|,
operator|-
literal|1
argument_list|,
literal|"weak"
argument_list|,
name|NULL
argument_list|)
expr_stmt|;
name|script_fu_console_scroll_end
argument_list|(
operator|&
name|cint
argument_list|)
expr_stmt|;
block|}
end_function

begin_function
specifier|static
name|gboolean
DECL|function|script_fu_cc_is_empty (ConsoleInterface * console)
name|script_fu_cc_is_empty
parameter_list|(
name|ConsoleInterface
modifier|*
name|console
parameter_list|)
block|{
specifier|const
name|gchar
modifier|*
name|str
decl_stmt|;
if|if
condition|(
operator|(
name|str
operator|=
name|gtk_entry_get_text
argument_list|(
name|GTK_ENTRY
argument_list|(
name|console
operator|->
name|cc
argument_list|)
argument_list|)
operator|)
operator|==
name|NULL
condition|)
return|return
name|TRUE
return|;
while|while
condition|(
operator|*
name|str
condition|)
block|{
if|if
condition|(
operator|*
name|str
operator|!=
literal|' '
operator|&&
operator|*
name|str
operator|!=
literal|'\t'
operator|&&
operator|*
name|str
operator|!=
literal|'\n'
condition|)
return|return
name|FALSE
return|;
name|str
operator|++
expr_stmt|;
block|}
return|return
name|TRUE
return|;
block|}
end_function

begin_function
specifier|static
name|gboolean
DECL|function|script_fu_cc_key_function (GtkWidget * widget,GdkEventKey * event,ConsoleInterface * console)
name|script_fu_cc_key_function
parameter_list|(
name|GtkWidget
modifier|*
name|widget
parameter_list|,
name|GdkEventKey
modifier|*
name|event
parameter_list|,
name|ConsoleInterface
modifier|*
name|console
parameter_list|)
block|{
name|GList
modifier|*
name|list
decl_stmt|;
name|gint
name|direction
init|=
literal|0
decl_stmt|;
name|GtkTextIter
name|cursor
decl_stmt|;
switch|switch
condition|(
name|event
operator|->
name|keyval
condition|)
block|{
case|case
name|GDK_Return
case|:
if|if
condition|(
name|script_fu_cc_is_empty
argument_list|(
name|console
argument_list|)
condition|)
return|return
name|TRUE
return|;
name|list
operator|=
name|g_list_nth
argument_list|(
name|console
operator|->
name|history
argument_list|,
operator|(
name|g_list_length
argument_list|(
name|console
operator|->
name|history
argument_list|)
operator|-
literal|1
operator|)
argument_list|)
expr_stmt|;
if|if
condition|(
name|list
operator|->
name|data
condition|)
name|g_free
argument_list|(
name|list
operator|->
name|data
argument_list|)
expr_stmt|;
name|list
operator|->
name|data
operator|=
name|g_strdup
argument_list|(
name|gtk_entry_get_text
argument_list|(
name|GTK_ENTRY
argument_list|(
name|console
operator|->
name|cc
argument_list|)
argument_list|)
argument_list|)
expr_stmt|;
name|gtk_text_buffer_get_end_iter
argument_list|(
name|console
operator|->
name|console
argument_list|,
operator|&
name|cursor
argument_list|)
expr_stmt|;
name|gtk_text_buffer_insert_with_tags_by_name
argument_list|(
name|console
operator|->
name|console
argument_list|,
operator|&
name|cursor
argument_list|,
literal|"\n=> "
argument_list|,
operator|-
literal|1
argument_list|,
literal|"strong"
argument_list|,
name|NULL
argument_list|)
expr_stmt|;
name|gtk_text_buffer_insert_with_tags_by_name
argument_list|(
name|console
operator|->
name|console
argument_list|,
operator|&
name|cursor
argument_list|,
name|gtk_entry_get_text
argument_list|(
name|GTK_ENTRY
argument_list|(
name|console
operator|->
name|cc
argument_list|)
argument_list|)
argument_list|,
operator|-
literal|1
argument_list|,
literal|"weak"
argument_list|,
name|NULL
argument_list|)
expr_stmt|;
name|gtk_text_buffer_insert_with_tags_by_name
argument_list|(
name|console
operator|->
name|console
argument_list|,
operator|&
name|cursor
argument_list|,
literal|"\n"
argument_list|,
operator|-
literal|1
argument_list|,
literal|"weak"
argument_list|,
name|NULL
argument_list|)
expr_stmt|;
name|script_fu_console_scroll_end
argument_list|(
name|console
argument_list|)
expr_stmt|;
name|gtk_entry_set_text
argument_list|(
name|GTK_ENTRY
argument_list|(
name|console
operator|->
name|cc
argument_list|)
argument_list|,
literal|""
argument_list|)
expr_stmt|;
name|siod_interpret_string
argument_list|(
operator|(
name|char
operator|*
operator|)
name|list
operator|->
name|data
argument_list|)
expr_stmt|;
name|gimp_displays_flush
argument_list|()
expr_stmt|;
name|console
operator|->
name|history
operator|=
name|g_list_append
argument_list|(
name|console
operator|->
name|history
argument_list|,
name|NULL
argument_list|)
expr_stmt|;
if|if
condition|(
name|console
operator|->
name|history_len
operator|==
name|console
operator|->
name|history_max
condition|)
block|{
name|console
operator|->
name|history
operator|=
name|g_list_remove
argument_list|(
name|console
operator|->
name|history
argument_list|,
name|console
operator|->
name|history
operator|->
name|data
argument_list|)
expr_stmt|;
if|if
condition|(
name|console
operator|->
name|history
operator|->
name|data
condition|)
name|g_free
argument_list|(
name|console
operator|->
name|history
operator|->
name|data
argument_list|)
expr_stmt|;
block|}
else|else
name|console
operator|->
name|history_len
operator|++
expr_stmt|;
name|console
operator|->
name|history_cur
operator|=
name|g_list_length
argument_list|(
name|console
operator|->
name|history
argument_list|)
operator|-
literal|1
expr_stmt|;
return|return
name|TRUE
return|;
break|break;
case|case
name|GDK_KP_Up
case|:
case|case
name|GDK_Up
case|:
name|direction
operator|=
operator|-
literal|1
expr_stmt|;
break|break;
case|case
name|GDK_KP_Down
case|:
case|case
name|GDK_Down
case|:
name|direction
operator|=
literal|1
expr_stmt|;
break|break;
case|case
name|GDK_P
case|:
case|case
name|GDK_p
case|:
if|if
condition|(
name|event
operator|->
name|state
operator|&
name|GDK_CONTROL_MASK
condition|)
name|direction
operator|=
operator|-
literal|1
expr_stmt|;
break|break;
case|case
name|GDK_N
case|:
case|case
name|GDK_n
case|:
if|if
condition|(
name|event
operator|->
name|state
operator|&
name|GDK_CONTROL_MASK
condition|)
name|direction
operator|=
literal|1
expr_stmt|;
break|break;
default|default:
break|break;
block|}
if|if
condition|(
name|direction
condition|)
block|{
comment|/*  Make sure we keep track of the current one  */
if|if
condition|(
name|console
operator|->
name|history_cur
operator|==
name|g_list_length
argument_list|(
name|console
operator|->
name|history
argument_list|)
operator|-
literal|1
condition|)
block|{
name|list
operator|=
name|g_list_nth
argument_list|(
name|console
operator|->
name|history
argument_list|,
name|console
operator|->
name|history_cur
argument_list|)
expr_stmt|;
if|if
condition|(
name|list
operator|->
name|data
condition|)
name|g_free
argument_list|(
name|list
operator|->
name|data
argument_list|)
expr_stmt|;
name|list
operator|->
name|data
operator|=
name|g_strdup
argument_list|(
name|gtk_entry_get_text
argument_list|(
name|GTK_ENTRY
argument_list|(
name|console
operator|->
name|cc
argument_list|)
argument_list|)
argument_list|)
expr_stmt|;
block|}
name|console
operator|->
name|history_cur
operator|+=
name|direction
expr_stmt|;
if|if
condition|(
name|console
operator|->
name|history_cur
operator|<
literal|0
condition|)
name|console
operator|->
name|history_cur
operator|=
literal|0
expr_stmt|;
if|if
condition|(
name|console
operator|->
name|history_cur
operator|>=
name|console
operator|->
name|history_len
condition|)
name|console
operator|->
name|history_cur
operator|=
name|console
operator|->
name|history_len
operator|-
literal|1
expr_stmt|;
name|gtk_entry_set_text
argument_list|(
name|GTK_ENTRY
argument_list|(
name|console
operator|->
name|cc
argument_list|)
argument_list|,
operator|(
name|gchar
operator|*
operator|)
operator|(
name|g_list_nth
argument_list|(
name|console
operator|->
name|history
argument_list|,
name|console
operator|->
name|history_cur
argument_list|)
operator|)
operator|->
name|data
argument_list|)
expr_stmt|;
name|gtk_editable_set_position
argument_list|(
name|GTK_EDITABLE
argument_list|(
name|console
operator|->
name|cc
argument_list|)
argument_list|,
operator|-
literal|1
argument_list|)
expr_stmt|;
return|return
name|TRUE
return|;
block|}
return|return
name|FALSE
return|;
block|}
end_function

begin_function
specifier|static
name|void
DECL|function|script_fu_open_siod_console (void)
name|script_fu_open_siod_console
parameter_list|(
name|void
parameter_list|)
block|{
name|siod_set_console_mode
argument_list|(
literal|1
argument_list|)
expr_stmt|;
name|siod_set_verbose_level
argument_list|(
literal|2
argument_list|)
expr_stmt|;
block|}
end_function

begin_function
specifier|static
name|void
DECL|function|script_fu_close_siod_console (void)
name|script_fu_close_siod_console
parameter_list|(
name|void
parameter_list|)
block|{
name|FILE
modifier|*
name|siod_output
decl_stmt|;
name|siod_output
operator|=
name|siod_get_output_file
argument_list|()
expr_stmt|;
if|if
condition|(
name|siod_output
operator|!=
name|stdout
condition|)
name|fclose
argument_list|(
name|siod_output
argument_list|)
expr_stmt|;
name|siod_set_console_mode
argument_list|(
literal|0
argument_list|)
expr_stmt|;
block|}
end_function

begin_function
name|void
DECL|function|script_fu_eval_run (const gchar * name,gint nparams,const GimpParam * params,gint * nreturn_vals,GimpParam ** return_vals)
name|script_fu_eval_run
parameter_list|(
specifier|const
name|gchar
modifier|*
name|name
parameter_list|,
name|gint
name|nparams
parameter_list|,
specifier|const
name|GimpParam
modifier|*
name|params
parameter_list|,
name|gint
modifier|*
name|nreturn_vals
parameter_list|,
name|GimpParam
modifier|*
modifier|*
name|return_vals
parameter_list|)
block|{
specifier|static
name|GimpParam
name|values
index|[
literal|1
index|]
decl_stmt|;
name|GimpPDBStatusType
name|status
init|=
name|GIMP_PDB_SUCCESS
decl_stmt|;
name|GimpRunMode
name|run_mode
decl_stmt|;
name|run_mode
operator|=
name|params
index|[
literal|0
index|]
operator|.
name|data
operator|.
name|d_int32
expr_stmt|;
switch|switch
condition|(
name|run_mode
condition|)
block|{
case|case
name|GIMP_RUN_NONINTERACTIVE
case|:
if|if
condition|(
name|siod_interpret_string
argument_list|(
name|params
index|[
literal|1
index|]
operator|.
name|data
operator|.
name|d_string
argument_list|)
operator|!=
literal|0
condition|)
name|status
operator|=
name|GIMP_PDB_EXECUTION_ERROR
expr_stmt|;
break|break;
case|case
name|GIMP_RUN_INTERACTIVE
case|:
case|case
name|GIMP_RUN_WITH_LAST_VALS
case|:
name|status
operator|=
name|GIMP_PDB_CALLING_ERROR
expr_stmt|;
name|g_message
argument_list|(
name|_
argument_list|(
literal|"Script-Fu evaluate mode allows only "
literal|"noninteractive invocation"
argument_list|)
argument_list|)
expr_stmt|;
break|break;
default|default:
break|break;
block|}
operator|*
name|nreturn_vals
operator|=
literal|1
expr_stmt|;
operator|*
name|return_vals
operator|=
name|values
expr_stmt|;
name|values
index|[
literal|0
index|]
operator|.
name|type
operator|=
name|GIMP_PDB_STATUS
expr_stmt|;
name|values
index|[
literal|0
index|]
operator|.
name|data
operator|.
name|d_status
operator|=
name|status
expr_stmt|;
block|}
end_function

end_unit

