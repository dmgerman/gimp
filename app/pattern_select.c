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
file|"apptypes.h"
end_include

begin_include
include|#
directive|include
file|"appenv.h"
end_include

begin_include
include|#
directive|include
file|"context_manager.h"
end_include

begin_include
include|#
directive|include
file|"dialog_handler.h"
end_include

begin_include
include|#
directive|include
file|"gimpcontainer.h"
end_include

begin_include
include|#
directive|include
file|"gimpcontext.h"
end_include

begin_include
include|#
directive|include
file|"gimpdatafactoryview.h"
end_include

begin_include
include|#
directive|include
file|"gimpdatafactory.h"
end_include

begin_include
include|#
directive|include
file|"gimppattern.h"
end_include

begin_include
include|#
directive|include
file|"pattern_select.h"
end_include

begin_include
include|#
directive|include
file|"session.h"
end_include

begin_include
include|#
directive|include
file|"temp_buf.h"
end_include

begin_include
include|#
directive|include
file|"pdb/procedural_db.h"
end_include

begin_include
include|#
directive|include
file|"libgimp/gimpintl.h"
end_include

begin_define
DECL|macro|MIN_CELL_SIZE
define|#
directive|define
name|MIN_CELL_SIZE
value|32
end_define

begin_define
DECL|macro|STD_PATTERN_COLUMNS
define|#
directive|define
name|STD_PATTERN_COLUMNS
value|6
end_define

begin_define
DECL|macro|STD_PATTERN_ROWS
define|#
directive|define
name|STD_PATTERN_ROWS
value|5
end_define

begin_comment
comment|/*  local function prototypes  */
end_comment

begin_function_decl
specifier|static
name|void
name|pattern_select_change_callbacks
parameter_list|(
name|PatternSelect
modifier|*
name|psp
parameter_list|,
name|gboolean
name|closing
parameter_list|)
function_decl|;
end_function_decl

begin_function_decl
specifier|static
name|void
name|pattern_select_pattern_changed
parameter_list|(
name|GimpContext
modifier|*
name|context
parameter_list|,
name|GimpPattern
modifier|*
name|pattern
parameter_list|,
name|PatternSelect
modifier|*
name|psp
parameter_list|)
function_decl|;
end_function_decl

begin_function_decl
specifier|static
name|void
name|pattern_select_pattern_dirty_callback
parameter_list|(
name|GimpPattern
modifier|*
name|brush
parameter_list|,
name|PatternSelect
modifier|*
name|psp
parameter_list|)
function_decl|;
end_function_decl

begin_function_decl
specifier|static
name|void
name|pattern_select_update_active_pattern_field
parameter_list|(
name|PatternSelect
modifier|*
name|psp
parameter_list|)
function_decl|;
end_function_decl

begin_function_decl
specifier|static
name|void
name|pattern_select_close_callback
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
comment|/*  The main pattern selection dialog  */
end_comment

begin_decl_stmt
DECL|variable|pattern_select_dialog
name|PatternSelect
modifier|*
name|pattern_select_dialog
init|=
name|NULL
decl_stmt|;
end_decl_stmt

begin_comment
comment|/*  local variables  */
end_comment

begin_comment
comment|/*  List of active dialogs  */
end_comment

begin_decl_stmt
DECL|variable|pattern_active_dialogs
name|GSList
modifier|*
name|pattern_active_dialogs
init|=
name|NULL
decl_stmt|;
end_decl_stmt

begin_function
name|void
DECL|function|pattern_dialog_create (void)
name|pattern_dialog_create
parameter_list|(
name|void
parameter_list|)
block|{
if|if
condition|(
operator|!
name|pattern_select_dialog
condition|)
block|{
name|pattern_select_dialog
operator|=
name|pattern_select_new
argument_list|(
name|NULL
argument_list|,
name|NULL
argument_list|)
expr_stmt|;
block|}
else|else
block|{
if|if
condition|(
operator|!
name|GTK_WIDGET_VISIBLE
argument_list|(
name|pattern_select_dialog
operator|->
name|shell
argument_list|)
condition|)
name|gtk_widget_show
argument_list|(
name|pattern_select_dialog
operator|->
name|shell
argument_list|)
expr_stmt|;
else|else
name|gdk_window_raise
argument_list|(
name|pattern_select_dialog
operator|->
name|shell
operator|->
name|window
argument_list|)
expr_stmt|;
block|}
block|}
end_function

begin_function
name|void
DECL|function|pattern_dialog_free (void)
name|pattern_dialog_free
parameter_list|(
name|void
parameter_list|)
block|{
if|if
condition|(
name|pattern_select_dialog
condition|)
block|{
name|session_get_window_info
argument_list|(
name|pattern_select_dialog
operator|->
name|shell
argument_list|,
operator|&
name|pattern_select_session_info
argument_list|)
expr_stmt|;
name|pattern_select_free
argument_list|(
name|pattern_select_dialog
argument_list|)
expr_stmt|;
name|pattern_select_dialog
operator|=
name|NULL
expr_stmt|;
block|}
block|}
end_function

begin_comment
comment|/*  If title == NULL then it is the main pattern dialog  */
end_comment

begin_function
name|PatternSelect
modifier|*
DECL|function|pattern_select_new (gchar * title,gchar * initial_pattern)
name|pattern_select_new
parameter_list|(
name|gchar
modifier|*
name|title
parameter_list|,
name|gchar
modifier|*
name|initial_pattern
parameter_list|)
block|{
name|PatternSelect
modifier|*
name|psp
decl_stmt|;
name|GtkWidget
modifier|*
name|vbox
decl_stmt|;
name|GtkWidget
modifier|*
name|label_box
decl_stmt|;
name|GimpPattern
modifier|*
name|active
init|=
name|NULL
decl_stmt|;
specifier|static
name|gboolean
name|first_call
init|=
name|TRUE
decl_stmt|;
name|psp
operator|=
name|g_new0
argument_list|(
name|PatternSelect
argument_list|,
literal|1
argument_list|)
expr_stmt|;
comment|/*  The shell  */
name|psp
operator|->
name|shell
operator|=
name|gimp_dialog_new
argument_list|(
name|title
condition|?
name|title
else|:
name|_
argument_list|(
literal|"Pattern Selection"
argument_list|)
argument_list|,
literal|"pattern_selection"
argument_list|,
name|gimp_standard_help_func
argument_list|,
literal|"dialogs/pattern_selection.html"
argument_list|,
name|title
condition|?
name|GTK_WIN_POS_MOUSE
else|:
name|GTK_WIN_POS_NONE
argument_list|,
name|FALSE
argument_list|,
name|TRUE
argument_list|,
name|FALSE
argument_list|,
literal|"_delete_event_"
argument_list|,
name|pattern_select_close_callback
argument_list|,
name|psp
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
name|GTK_DIALOG
argument_list|(
name|psp
operator|->
name|shell
argument_list|)
operator|->
name|vbox
argument_list|)
argument_list|)
argument_list|,
literal|0
argument_list|)
argument_list|)
argument_list|)
expr_stmt|;
name|gtk_widget_hide
argument_list|(
name|GTK_DIALOG
argument_list|(
name|psp
operator|->
name|shell
argument_list|)
operator|->
name|action_area
argument_list|)
expr_stmt|;
if|if
condition|(
name|title
condition|)
block|{
name|psp
operator|->
name|context
operator|=
name|gimp_context_new
argument_list|(
name|title
argument_list|,
name|NULL
argument_list|)
expr_stmt|;
block|}
else|else
block|{
name|psp
operator|->
name|context
operator|=
name|gimp_context_get_user
argument_list|()
expr_stmt|;
name|session_set_window_geometry
argument_list|(
name|psp
operator|->
name|shell
argument_list|,
operator|&
name|pattern_select_session_info
argument_list|,
name|TRUE
argument_list|)
expr_stmt|;
name|dialog_register
argument_list|(
name|psp
operator|->
name|shell
argument_list|)
expr_stmt|;
block|}
if|if
condition|(
name|no_data
operator|&&
name|first_call
condition|)
name|gimp_data_factory_data_init
argument_list|(
name|global_pattern_factory
argument_list|,
name|FALSE
argument_list|)
expr_stmt|;
name|first_call
operator|=
name|FALSE
expr_stmt|;
if|if
condition|(
name|title
operator|&&
name|initial_pattern
operator|&&
name|strlen
argument_list|(
name|initial_pattern
argument_list|)
condition|)
block|{
name|active
operator|=
operator|(
name|GimpPattern
operator|*
operator|)
name|gimp_container_get_child_by_name
argument_list|(
name|global_pattern_factory
operator|->
name|container
argument_list|,
name|initial_pattern
argument_list|)
expr_stmt|;
block|}
else|else
block|{
name|active
operator|=
name|gimp_context_get_pattern
argument_list|(
name|gimp_context_get_user
argument_list|()
argument_list|)
expr_stmt|;
block|}
if|if
condition|(
operator|!
name|active
condition|)
name|active
operator|=
name|gimp_context_get_pattern
argument_list|(
name|gimp_context_get_standard
argument_list|()
argument_list|)
expr_stmt|;
if|if
condition|(
name|title
condition|)
name|gimp_context_set_pattern
argument_list|(
name|psp
operator|->
name|context
argument_list|,
name|active
argument_list|)
expr_stmt|;
comment|/*  The main vbox  */
name|vbox
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
name|vbox
argument_list|)
argument_list|,
literal|2
argument_list|)
expr_stmt|;
name|gtk_container_add
argument_list|(
name|GTK_CONTAINER
argument_list|(
name|GTK_DIALOG
argument_list|(
name|psp
operator|->
name|shell
argument_list|)
operator|->
name|vbox
argument_list|)
argument_list|,
name|vbox
argument_list|)
expr_stmt|;
comment|/*  Options box  */
name|psp
operator|->
name|options_box
operator|=
name|gtk_vbox_new
argument_list|(
name|FALSE
argument_list|,
literal|0
argument_list|)
expr_stmt|;
name|gtk_box_pack_start
argument_list|(
name|GTK_BOX
argument_list|(
name|vbox
argument_list|)
argument_list|,
name|psp
operator|->
name|options_box
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
name|psp
operator|->
name|options_box
argument_list|)
expr_stmt|;
comment|/*  Create the active pattern label  */
name|label_box
operator|=
name|gtk_hbox_new
argument_list|(
name|FALSE
argument_list|,
literal|0
argument_list|)
expr_stmt|;
name|gtk_box_pack_start
argument_list|(
name|GTK_BOX
argument_list|(
name|psp
operator|->
name|options_box
argument_list|)
argument_list|,
name|label_box
argument_list|,
name|FALSE
argument_list|,
name|FALSE
argument_list|,
literal|2
argument_list|)
expr_stmt|;
name|gtk_widget_show
argument_list|(
name|label_box
argument_list|)
expr_stmt|;
name|psp
operator|->
name|pattern_name
operator|=
name|gtk_label_new
argument_list|(
name|_
argument_list|(
literal|"No Patterns available"
argument_list|)
argument_list|)
expr_stmt|;
name|gtk_box_pack_start
argument_list|(
name|GTK_BOX
argument_list|(
name|label_box
argument_list|)
argument_list|,
name|psp
operator|->
name|pattern_name
argument_list|,
name|FALSE
argument_list|,
name|FALSE
argument_list|,
literal|4
argument_list|)
expr_stmt|;
name|psp
operator|->
name|pattern_size
operator|=
name|gtk_label_new
argument_list|(
literal|"(0 X 0)"
argument_list|)
expr_stmt|;
name|gtk_box_pack_start
argument_list|(
name|GTK_BOX
argument_list|(
name|label_box
argument_list|)
argument_list|,
name|psp
operator|->
name|pattern_size
argument_list|,
name|FALSE
argument_list|,
name|FALSE
argument_list|,
literal|2
argument_list|)
expr_stmt|;
name|gtk_widget_show
argument_list|(
name|psp
operator|->
name|pattern_name
argument_list|)
expr_stmt|;
name|gtk_widget_show
argument_list|(
name|psp
operator|->
name|pattern_size
argument_list|)
expr_stmt|;
comment|/*  The Brush Grid  */
name|psp
operator|->
name|view
operator|=
name|gimp_data_factory_view_new
argument_list|(
name|GIMP_VIEW_TYPE_GRID
argument_list|,
name|global_pattern_factory
argument_list|,
name|NULL
argument_list|,
name|psp
operator|->
name|context
argument_list|,
name|MIN_CELL_SIZE
argument_list|,
name|STD_PATTERN_COLUMNS
argument_list|,
name|STD_PATTERN_ROWS
argument_list|)
expr_stmt|;
name|gtk_box_pack_start
argument_list|(
name|GTK_BOX
argument_list|(
name|vbox
argument_list|)
argument_list|,
name|psp
operator|->
name|view
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
name|psp
operator|->
name|view
argument_list|)
expr_stmt|;
name|gtk_widget_show
argument_list|(
name|vbox
argument_list|)
expr_stmt|;
comment|/*  add callbacks to keep the display area current  */
name|psp
operator|->
name|name_changed_handler_id
operator|=
name|gimp_container_add_handler
argument_list|(
name|global_pattern_factory
operator|->
name|container
argument_list|,
literal|"name_changed"
argument_list|,
name|GTK_SIGNAL_FUNC
argument_list|(
name|pattern_select_pattern_dirty_callback
argument_list|)
argument_list|,
name|psp
argument_list|)
expr_stmt|;
name|gtk_widget_show
argument_list|(
name|psp
operator|->
name|shell
argument_list|)
expr_stmt|;
name|gtk_signal_connect
argument_list|(
name|GTK_OBJECT
argument_list|(
name|psp
operator|->
name|context
argument_list|)
argument_list|,
literal|"pattern_changed"
argument_list|,
name|GTK_SIGNAL_FUNC
argument_list|(
name|pattern_select_pattern_changed
argument_list|)
argument_list|,
name|psp
argument_list|)
expr_stmt|;
if|if
condition|(
name|active
condition|)
name|pattern_select_update_active_pattern_field
argument_list|(
name|psp
argument_list|)
expr_stmt|;
comment|/*  Add to active pattern dialogs list  */
name|pattern_active_dialogs
operator|=
name|g_slist_append
argument_list|(
name|pattern_active_dialogs
argument_list|,
name|psp
argument_list|)
expr_stmt|;
return|return
name|psp
return|;
block|}
end_function

begin_function
name|void
DECL|function|pattern_select_free (PatternSelect * psp)
name|pattern_select_free
parameter_list|(
name|PatternSelect
modifier|*
name|psp
parameter_list|)
block|{
if|if
condition|(
operator|!
name|psp
condition|)
return|return;
comment|/* remove from active list */
name|pattern_active_dialogs
operator|=
name|g_slist_remove
argument_list|(
name|pattern_active_dialogs
argument_list|,
name|psp
argument_list|)
expr_stmt|;
name|gtk_signal_disconnect_by_data
argument_list|(
name|GTK_OBJECT
argument_list|(
name|psp
operator|->
name|context
argument_list|)
argument_list|,
name|psp
argument_list|)
expr_stmt|;
if|if
condition|(
name|psp
operator|->
name|callback_name
condition|)
block|{
name|g_free
argument_list|(
name|psp
operator|->
name|callback_name
argument_list|)
expr_stmt|;
name|gtk_object_unref
argument_list|(
name|GTK_OBJECT
argument_list|(
name|psp
operator|->
name|context
argument_list|)
argument_list|)
expr_stmt|;
block|}
name|gimp_container_remove_handler
argument_list|(
name|global_pattern_factory
operator|->
name|container
argument_list|,
name|psp
operator|->
name|name_changed_handler_id
argument_list|)
expr_stmt|;
name|g_free
argument_list|(
name|psp
argument_list|)
expr_stmt|;
block|}
end_function

begin_comment
comment|/*  Call this dialog's PDB callback  */
end_comment

begin_function
specifier|static
name|void
DECL|function|pattern_select_change_callbacks (PatternSelect * psp,gboolean closing)
name|pattern_select_change_callbacks
parameter_list|(
name|PatternSelect
modifier|*
name|psp
parameter_list|,
name|gboolean
name|closing
parameter_list|)
block|{
name|gchar
modifier|*
name|name
decl_stmt|;
name|ProcRecord
modifier|*
name|prec
init|=
name|NULL
decl_stmt|;
name|GimpPattern
modifier|*
name|pattern
decl_stmt|;
name|gint
name|nreturn_vals
decl_stmt|;
specifier|static
name|gboolean
name|busy
init|=
name|FALSE
decl_stmt|;
comment|/* Any procs registered to callback? */
name|Argument
modifier|*
name|return_vals
decl_stmt|;
if|if
condition|(
operator|!
name|psp
operator|||
operator|!
name|psp
operator|->
name|callback_name
operator|||
name|busy
condition|)
return|return;
name|busy
operator|=
name|TRUE
expr_stmt|;
name|name
operator|=
name|psp
operator|->
name|callback_name
expr_stmt|;
name|pattern
operator|=
name|gimp_context_get_pattern
argument_list|(
name|psp
operator|->
name|context
argument_list|)
expr_stmt|;
comment|/* If its still registered run it */
name|prec
operator|=
name|procedural_db_lookup
argument_list|(
name|name
argument_list|)
expr_stmt|;
if|if
condition|(
name|prec
operator|&&
name|pattern
condition|)
block|{
name|return_vals
operator|=
name|procedural_db_run_proc
argument_list|(
name|name
argument_list|,
operator|&
name|nreturn_vals
argument_list|,
name|PDB_STRING
argument_list|,
name|GIMP_OBJECT
argument_list|(
name|pattern
argument_list|)
operator|->
name|name
argument_list|,
name|PDB_INT32
argument_list|,
name|pattern
operator|->
name|mask
operator|->
name|width
argument_list|,
name|PDB_INT32
argument_list|,
name|pattern
operator|->
name|mask
operator|->
name|height
argument_list|,
name|PDB_INT32
argument_list|,
name|pattern
operator|->
name|mask
operator|->
name|bytes
argument_list|,
name|PDB_INT32
argument_list|,
operator|(
name|pattern
operator|->
name|mask
operator|->
name|bytes
operator|*
name|pattern
operator|->
name|mask
operator|->
name|height
operator|*
name|pattern
operator|->
name|mask
operator|->
name|width
operator|)
argument_list|,
name|PDB_INT8ARRAY
argument_list|,
name|temp_buf_data
argument_list|(
name|pattern
operator|->
name|mask
argument_list|)
argument_list|,
name|PDB_INT32
argument_list|,
operator|(
name|gint
operator|)
name|closing
argument_list|,
name|PDB_END
argument_list|)
expr_stmt|;
if|if
condition|(
operator|!
name|return_vals
operator|||
name|return_vals
index|[
literal|0
index|]
operator|.
name|value
operator|.
name|pdb_int
operator|!=
name|PDB_SUCCESS
condition|)
name|g_warning
argument_list|(
literal|"failed to run pattern callback function"
argument_list|)
expr_stmt|;
name|procedural_db_destroy_args
argument_list|(
name|return_vals
argument_list|,
name|nreturn_vals
argument_list|)
expr_stmt|;
block|}
name|busy
operator|=
name|FALSE
expr_stmt|;
block|}
end_function

begin_comment
comment|/*  Close active dialogs that no longer have PDB registered for them  */
end_comment

begin_function
name|void
DECL|function|pattern_select_dialogs_check (void)
name|pattern_select_dialogs_check
parameter_list|(
name|void
parameter_list|)
block|{
name|PatternSelect
modifier|*
name|psp
decl_stmt|;
name|GSList
modifier|*
name|list
decl_stmt|;
name|gchar
modifier|*
name|name
decl_stmt|;
name|ProcRecord
modifier|*
name|prec
init|=
name|NULL
decl_stmt|;
name|list
operator|=
name|pattern_active_dialogs
expr_stmt|;
while|while
condition|(
name|list
condition|)
block|{
name|psp
operator|=
operator|(
name|PatternSelect
operator|*
operator|)
name|list
operator|->
name|data
expr_stmt|;
name|list
operator|=
name|g_slist_next
argument_list|(
name|list
argument_list|)
expr_stmt|;
name|name
operator|=
name|psp
operator|->
name|callback_name
expr_stmt|;
if|if
condition|(
name|name
condition|)
block|{
name|prec
operator|=
name|procedural_db_lookup
argument_list|(
name|name
argument_list|)
expr_stmt|;
if|if
condition|(
operator|!
name|prec
condition|)
block|{
comment|/*  Can alter pattern_active_dialogs list  */
name|pattern_select_close_callback
argument_list|(
name|NULL
argument_list|,
name|psp
argument_list|)
expr_stmt|;
block|}
block|}
block|}
block|}
end_function

begin_comment
comment|/*  *  Local functions  */
end_comment

begin_function
specifier|static
name|void
DECL|function|pattern_select_pattern_changed (GimpContext * context,GimpPattern * pattern,PatternSelect * psp)
name|pattern_select_pattern_changed
parameter_list|(
name|GimpContext
modifier|*
name|context
parameter_list|,
name|GimpPattern
modifier|*
name|pattern
parameter_list|,
name|PatternSelect
modifier|*
name|psp
parameter_list|)
block|{
if|if
condition|(
name|pattern
condition|)
block|{
name|pattern_select_update_active_pattern_field
argument_list|(
name|psp
argument_list|)
expr_stmt|;
if|if
condition|(
name|psp
operator|->
name|callback_name
condition|)
name|pattern_select_change_callbacks
argument_list|(
name|psp
argument_list|,
name|FALSE
argument_list|)
expr_stmt|;
block|}
block|}
end_function

begin_function
specifier|static
name|void
DECL|function|pattern_select_pattern_dirty_callback (GimpPattern * pattern,PatternSelect * psp)
name|pattern_select_pattern_dirty_callback
parameter_list|(
name|GimpPattern
modifier|*
name|pattern
parameter_list|,
name|PatternSelect
modifier|*
name|psp
parameter_list|)
block|{
name|pattern_select_update_active_pattern_field
argument_list|(
name|psp
argument_list|)
expr_stmt|;
block|}
end_function

begin_function
specifier|static
name|void
DECL|function|pattern_select_update_active_pattern_field (PatternSelect * psp)
name|pattern_select_update_active_pattern_field
parameter_list|(
name|PatternSelect
modifier|*
name|psp
parameter_list|)
block|{
name|GimpPattern
modifier|*
name|pattern
decl_stmt|;
name|gchar
name|buf
index|[
literal|32
index|]
decl_stmt|;
name|pattern
operator|=
name|gimp_context_get_pattern
argument_list|(
name|psp
operator|->
name|context
argument_list|)
expr_stmt|;
if|if
condition|(
operator|!
name|pattern
condition|)
return|return;
comment|/*  Set pattern name  */
name|gtk_label_set_text
argument_list|(
name|GTK_LABEL
argument_list|(
name|psp
operator|->
name|pattern_name
argument_list|)
argument_list|,
name|GIMP_OBJECT
argument_list|(
name|pattern
argument_list|)
operator|->
name|name
argument_list|)
expr_stmt|;
comment|/*  Set pattern size  */
name|g_snprintf
argument_list|(
name|buf
argument_list|,
sizeof|sizeof
argument_list|(
name|buf
argument_list|)
argument_list|,
literal|"(%d X %d)"
argument_list|,
name|pattern
operator|->
name|mask
operator|->
name|width
argument_list|,
name|pattern
operator|->
name|mask
operator|->
name|height
argument_list|)
expr_stmt|;
name|gtk_label_set_text
argument_list|(
name|GTK_LABEL
argument_list|(
name|psp
operator|->
name|pattern_size
argument_list|)
argument_list|,
name|buf
argument_list|)
expr_stmt|;
block|}
end_function

begin_function
specifier|static
name|void
DECL|function|pattern_select_close_callback (GtkWidget * widget,gpointer data)
name|pattern_select_close_callback
parameter_list|(
name|GtkWidget
modifier|*
name|widget
parameter_list|,
name|gpointer
name|data
parameter_list|)
block|{
name|PatternSelect
modifier|*
name|psp
decl_stmt|;
name|psp
operator|=
operator|(
name|PatternSelect
operator|*
operator|)
name|data
expr_stmt|;
if|if
condition|(
name|GTK_WIDGET_VISIBLE
argument_list|(
name|psp
operator|->
name|shell
argument_list|)
condition|)
name|gtk_widget_hide
argument_list|(
name|psp
operator|->
name|shell
argument_list|)
expr_stmt|;
comment|/* Free memory if poping down dialog which is not the main one */
if|if
condition|(
name|psp
operator|!=
name|pattern_select_dialog
condition|)
block|{
comment|/* Send data back */
name|pattern_select_change_callbacks
argument_list|(
name|psp
argument_list|,
name|TRUE
argument_list|)
expr_stmt|;
name|gtk_widget_destroy
argument_list|(
name|psp
operator|->
name|shell
argument_list|)
expr_stmt|;
name|pattern_select_free
argument_list|(
name|psp
argument_list|)
expr_stmt|;
block|}
block|}
end_function

end_unit

