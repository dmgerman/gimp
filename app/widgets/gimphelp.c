begin_unit|revision:0.9.5;language:C;cregit-version:0.0.1
begin_comment
comment|/* The GIMP -- an image manipulation program  * Copyright (C) 1995 Spencer Kimball and Peter Mattis  *  * gimphelp.c  * Copyright (C) 1999 Michael Natterer<mitch@gimp.org>  *  * This program is free software; you can redistribute it and/or modify  * it under the terms of the GNU General Public License as published by  * the Free Software Foundation; either version 2 of the License, or  * (at your option) any later version.  *  * This program is distributed in the hope that it will be useful,  * but WITHOUT ANY WARRANTY; without even the implied warranty of  * MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the  * GNU General Public License for more details.  *  * You should have received a copy of the GNU General Public License  * along with this program; if not, write to the Free Software  * Foundation, Inc., 59 Temple Place - Suite 330, Boston, MA 02111-1307, USA.  */
end_comment

begin_include
include|#
directive|include
file|<gdk/gdkkeysyms.h>
end_include

begin_include
include|#
directive|include
file|<gtk/gtk.h>
end_include

begin_include
include|#
directive|include
file|"gimphelp.h"
end_include

begin_include
include|#
directive|include
file|"gimprc.h"
end_include

begin_include
include|#
directive|include
file|"plug_in.h"
end_include

begin_include
include|#
directive|include
file|"procedural_db.h"
end_include

begin_include
include|#
directive|include
file|"libgimp/gimpintl.h"
end_include

begin_define
DECL|macro|DEBUG_HELP
define|#
directive|define
name|DEBUG_HELP
end_define

begin_comment
comment|/*  local function prototypes  */
end_comment

begin_function_decl
specifier|static
name|void
name|gimp_help_callback
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
name|gint
name|gimp_help_tips_query_idle_show_help
parameter_list|(
name|gpointer
name|data
parameter_list|)
function_decl|;
end_function_decl

begin_function_decl
specifier|static
name|gint
name|gimp_help_tips_query_widget_selected
parameter_list|(
name|GtkWidget
modifier|*
name|tips_query
parameter_list|,
name|GtkWidget
modifier|*
name|widget
parameter_list|,
specifier|const
name|gchar
modifier|*
name|tip_text
parameter_list|,
specifier|const
name|gchar
modifier|*
name|tip_private
parameter_list|,
name|GdkEventButton
modifier|*
name|event
parameter_list|,
name|gpointer
name|func_data
parameter_list|)
function_decl|;
end_function_decl

begin_function_decl
specifier|static
name|gint
name|gimp_help_tips_query_idle_start
parameter_list|(
name|gpointer
name|tips_query
parameter_list|)
function_decl|;
end_function_decl

begin_function_decl
specifier|static
name|void
name|gimp_help_tips_query_start
parameter_list|(
name|GtkWidget
modifier|*
name|widget
parameter_list|,
name|gpointer
name|tips_query
parameter_list|)
function_decl|;
end_function_decl

begin_comment
comment|/*  local variables  */
end_comment

begin_decl_stmt
DECL|variable|tool_tips
specifier|static
name|GtkTooltips
modifier|*
name|tool_tips
init|=
name|NULL
decl_stmt|;
end_decl_stmt

begin_decl_stmt
DECL|variable|tips_query
specifier|static
name|GtkWidget
modifier|*
name|tips_query
init|=
name|NULL
decl_stmt|;
end_decl_stmt

begin_comment
comment|/**********************/
end_comment

begin_comment
comment|/*  public functions  */
end_comment

begin_comment
comment|/**********************/
end_comment

begin_function
name|void
DECL|function|gimp_help_init (void)
name|gimp_help_init
parameter_list|(
name|void
parameter_list|)
block|{
name|tool_tips
operator|=
name|gtk_tooltips_new
argument_list|()
expr_stmt|;
block|}
end_function

begin_function
name|void
DECL|function|gimp_help_free (void)
name|gimp_help_free
parameter_list|(
name|void
parameter_list|)
block|{
name|gtk_object_destroy
argument_list|(
name|GTK_OBJECT
argument_list|(
name|tool_tips
argument_list|)
argument_list|)
expr_stmt|;
name|gtk_object_unref
argument_list|(
name|GTK_OBJECT
argument_list|(
name|tool_tips
argument_list|)
argument_list|)
expr_stmt|;
block|}
end_function

begin_function
name|void
DECL|function|gimp_help_enable_tooltips (void)
name|gimp_help_enable_tooltips
parameter_list|(
name|void
parameter_list|)
block|{
name|gtk_tooltips_enable
argument_list|(
name|tool_tips
argument_list|)
expr_stmt|;
block|}
end_function

begin_function
name|void
DECL|function|gimp_help_disable_tooltips (void)
name|gimp_help_disable_tooltips
parameter_list|(
name|void
parameter_list|)
block|{
name|gtk_tooltips_disable
argument_list|(
name|tool_tips
argument_list|)
expr_stmt|;
block|}
end_function

begin_comment
comment|/*  The standard help function  */
end_comment

begin_function
name|void
DECL|function|gimp_standard_help_func (gchar * help_data)
name|gimp_standard_help_func
parameter_list|(
name|gchar
modifier|*
name|help_data
parameter_list|)
block|{
name|gimp_help
argument_list|(
name|help_data
argument_list|)
expr_stmt|;
block|}
end_function

begin_function
name|void
DECL|function|gimp_help_connect_help_accel (GtkWidget * widget,GimpHelpFunc help_func,gchar * help_data)
name|gimp_help_connect_help_accel
parameter_list|(
name|GtkWidget
modifier|*
name|widget
parameter_list|,
name|GimpHelpFunc
name|help_func
parameter_list|,
name|gchar
modifier|*
name|help_data
parameter_list|)
block|{
name|GtkAccelGroup
modifier|*
name|accel_group
decl_stmt|;
if|if
condition|(
operator|!
name|help_func
condition|)
return|return;
comment|/*  set up the help signals and tips query widget  */
if|if
condition|(
operator|!
name|tips_query
condition|)
block|{
name|tips_query
operator|=
name|gtk_tips_query_new
argument_list|()
expr_stmt|;
name|gtk_widget_set
argument_list|(
name|tips_query
argument_list|,
literal|"GtkTipsQuery::emit_always"
argument_list|,
name|TRUE
argument_list|,
name|NULL
argument_list|)
expr_stmt|;
name|gtk_signal_connect
argument_list|(
name|GTK_OBJECT
argument_list|(
name|tips_query
argument_list|)
argument_list|,
literal|"widget_selected"
argument_list|,
name|GTK_SIGNAL_FUNC
argument_list|(
name|gimp_help_tips_query_widget_selected
argument_list|)
argument_list|,
name|NULL
argument_list|)
expr_stmt|;
comment|/*  FIXME: EEEEEEEEEEEEEEEEEEEEK, this is very ugly and forbidden...        *  does anyone know a way to do this tips query stuff without        *  having to attach to some parent widget???        */
name|tips_query
operator|->
name|parent
operator|=
name|widget
expr_stmt|;
name|gtk_widget_realize
argument_list|(
name|tips_query
argument_list|)
expr_stmt|;
name|gtk_object_class_user_signal_new
argument_list|(
name|GTK_OBJECT
argument_list|(
name|widget
argument_list|)
operator|->
name|klass
argument_list|,
literal|"tips_query"
argument_list|,
name|GTK_RUN_LAST
argument_list|,
name|gtk_signal_default_marshaller
argument_list|,
name|GTK_TYPE_NONE
argument_list|,
literal|0
argument_list|,
name|NULL
argument_list|)
expr_stmt|;
name|gtk_object_class_user_signal_new
argument_list|(
name|GTK_OBJECT
argument_list|(
name|widget
argument_list|)
operator|->
name|klass
argument_list|,
literal|"help"
argument_list|,
name|GTK_RUN_LAST
argument_list|,
name|gtk_signal_default_marshaller
argument_list|,
name|GTK_TYPE_NONE
argument_list|,
literal|0
argument_list|,
name|NULL
argument_list|)
expr_stmt|;
block|}
name|gimp_help_set_help_data
argument_list|(
name|widget
argument_list|,
name|NULL
argument_list|,
name|help_data
argument_list|)
expr_stmt|;
name|gtk_signal_connect
argument_list|(
name|GTK_OBJECT
argument_list|(
name|widget
argument_list|)
argument_list|,
literal|"help"
argument_list|,
name|GTK_SIGNAL_FUNC
argument_list|(
name|gimp_help_callback
argument_list|)
argument_list|,
operator|(
name|gpointer
operator|)
name|help_func
argument_list|)
expr_stmt|;
name|gtk_signal_connect
argument_list|(
name|GTK_OBJECT
argument_list|(
name|widget
argument_list|)
argument_list|,
literal|"tips_query"
argument_list|,
name|GTK_SIGNAL_FUNC
argument_list|(
name|gimp_help_tips_query_start
argument_list|)
argument_list|,
operator|(
name|gpointer
operator|)
name|tips_query
argument_list|)
expr_stmt|;
name|gtk_widget_add_events
argument_list|(
name|widget
argument_list|,
name|GDK_BUTTON_PRESS_MASK
argument_list|)
expr_stmt|;
comment|/*  a new accelerator group for this widget  */
name|accel_group
operator|=
name|gtk_accel_group_new
argument_list|()
expr_stmt|;
comment|/*  FIXME: does not work for some reason...   gtk_widget_add_accelerator (widget, "help", accel_group, 			      GDK_F1, 0, GTK_ACCEL_LOCKED);   gtk_widget_add_accelerator (widget, "tips_query", accel_group, 			      GDK_F1, GDK_SHIFT_MASK, GTK_ACCEL_LOCKED);   */
comment|/*  ...while using this internal stuff works  */
name|gtk_accel_group_add
argument_list|(
name|accel_group
argument_list|,
name|GDK_F1
argument_list|,
literal|0
argument_list|,
literal|0
argument_list|,
name|GTK_OBJECT
argument_list|(
name|widget
argument_list|)
argument_list|,
literal|"help"
argument_list|)
expr_stmt|;
name|gtk_accel_group_add
argument_list|(
name|accel_group
argument_list|,
name|GDK_F1
argument_list|,
name|GDK_SHIFT_MASK
argument_list|,
literal|0
argument_list|,
name|GTK_OBJECT
argument_list|(
name|widget
argument_list|)
argument_list|,
literal|"tips_query"
argument_list|)
expr_stmt|;
name|gtk_accel_group_attach
argument_list|(
name|accel_group
argument_list|,
name|GTK_OBJECT
argument_list|(
name|widget
argument_list|)
argument_list|)
expr_stmt|;
block|}
end_function

begin_function
name|void
DECL|function|gimp_help_set_help_data (GtkWidget * widget,gchar * tooltip,gchar * help_data)
name|gimp_help_set_help_data
parameter_list|(
name|GtkWidget
modifier|*
name|widget
parameter_list|,
name|gchar
modifier|*
name|tooltip
parameter_list|,
name|gchar
modifier|*
name|help_data
parameter_list|)
block|{
name|g_return_if_fail
argument_list|(
name|widget
operator|!=
name|NULL
argument_list|)
expr_stmt|;
name|g_return_if_fail
argument_list|(
name|GTK_IS_WIDGET
argument_list|(
name|widget
argument_list|)
argument_list|)
expr_stmt|;
if|if
condition|(
name|tooltip
condition|)
name|gtk_tooltips_set_tip
argument_list|(
name|tool_tips
argument_list|,
name|widget
argument_list|,
name|tooltip
argument_list|,
name|help_data
argument_list|)
expr_stmt|;
elseif|else
if|if
condition|(
name|help_data
condition|)
name|gtk_object_set_data
argument_list|(
name|GTK_OBJECT
argument_list|(
name|widget
argument_list|)
argument_list|,
literal|"gimp_help_data"
argument_list|,
name|help_data
argument_list|)
expr_stmt|;
block|}
end_function

begin_comment
comment|/*  the main help function  */
end_comment

begin_function
name|void
DECL|function|gimp_help (gchar * help_data)
name|gimp_help
parameter_list|(
name|gchar
modifier|*
name|help_data
parameter_list|)
block|{
name|ProcRecord
modifier|*
name|proc_rec
decl_stmt|;
specifier|static
name|gchar
modifier|*
name|current_locale
init|=
literal|"C"
decl_stmt|;
ifdef|#
directive|ifdef
name|DEBUG_HELP
name|g_print
argument_list|(
literal|"Help Page: %s\n"
argument_list|,
name|help_data
argument_list|)
expr_stmt|;
endif|#
directive|endif
comment|/*  DEBUG_HELP  */
comment|/*  Check if a help browser is already running  */
name|proc_rec
operator|=
name|procedural_db_lookup
argument_list|(
literal|"extension_gimp_help_browser_temp"
argument_list|)
expr_stmt|;
if|if
condition|(
name|proc_rec
operator|==
name|NULL
condition|)
block|{
name|Argument
modifier|*
name|args
init|=
name|NULL
decl_stmt|;
name|proc_rec
operator|=
name|procedural_db_lookup
argument_list|(
literal|"extension_gimp_help_browser"
argument_list|)
expr_stmt|;
if|if
condition|(
name|proc_rec
operator|==
name|NULL
condition|)
block|{
name|g_message
argument_list|(
name|_
argument_list|(
literal|"Could not find the GIMP Help Browser procedure.\n"
literal|"It probably was not compiled because\n"
literal|"you don't have GtkXmHTML installed."
argument_list|)
argument_list|)
expr_stmt|;
return|return;
block|}
name|args
operator|=
name|g_new
argument_list|(
name|Argument
argument_list|,
literal|3
argument_list|)
expr_stmt|;
name|args
index|[
literal|0
index|]
operator|.
name|arg_type
operator|=
name|PDB_INT32
expr_stmt|;
name|args
index|[
literal|0
index|]
operator|.
name|value
operator|.
name|pdb_int
operator|=
name|RUN_INTERACTIVE
expr_stmt|;
name|args
index|[
literal|1
index|]
operator|.
name|arg_type
operator|=
name|PDB_STRING
expr_stmt|;
name|args
index|[
literal|1
index|]
operator|.
name|value
operator|.
name|pdb_pointer
operator|=
name|current_locale
expr_stmt|;
name|args
index|[
literal|2
index|]
operator|.
name|arg_type
operator|=
name|PDB_STRING
expr_stmt|;
name|args
index|[
literal|2
index|]
operator|.
name|value
operator|.
name|pdb_pointer
operator|=
name|help_data
expr_stmt|;
name|plug_in_run
argument_list|(
name|proc_rec
argument_list|,
name|args
argument_list|,
literal|3
argument_list|,
name|FALSE
argument_list|,
name|TRUE
argument_list|,
literal|0
argument_list|)
expr_stmt|;
name|g_free
argument_list|(
name|args
argument_list|)
expr_stmt|;
block|}
else|else
block|{
name|Argument
modifier|*
name|return_vals
decl_stmt|;
name|gint
name|nreturn_vals
decl_stmt|;
name|return_vals
operator|=
name|procedural_db_run_proc
argument_list|(
literal|"extension_gimp_help_browser_temp"
argument_list|,
operator|&
name|nreturn_vals
argument_list|,
name|PDB_STRING
argument_list|,
name|current_locale
argument_list|,
name|PDB_STRING
argument_list|,
name|help_data
argument_list|,
name|PDB_END
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
block|}
end_function

begin_function
name|void
DECL|function|gimp_context_help (void)
name|gimp_context_help
parameter_list|(
name|void
parameter_list|)
block|{
if|if
condition|(
name|tips_query
condition|)
name|gimp_help_tips_query_start
argument_list|(
name|NULL
argument_list|,
name|tips_query
argument_list|)
expr_stmt|;
block|}
end_function

begin_comment
comment|/*********************/
end_comment

begin_comment
comment|/*  local functions  */
end_comment

begin_comment
comment|/*********************/
end_comment

begin_function
specifier|static
name|void
DECL|function|gimp_help_callback (GtkWidget * widget,gpointer data)
name|gimp_help_callback
parameter_list|(
name|GtkWidget
modifier|*
name|widget
parameter_list|,
name|gpointer
name|data
parameter_list|)
block|{
name|GimpHelpFunc
name|help_function
decl_stmt|;
name|gchar
modifier|*
name|help_data
decl_stmt|;
name|help_function
operator|=
operator|(
name|GimpHelpFunc
operator|)
name|data
expr_stmt|;
name|help_data
operator|=
operator|(
name|gchar
operator|*
operator|)
name|gtk_object_get_data
argument_list|(
name|GTK_OBJECT
argument_list|(
name|widget
argument_list|)
argument_list|,
literal|"gimp_help_data"
argument_list|)
expr_stmt|;
if|if
condition|(
name|help_function
operator|&&
name|use_help
condition|)
call|(
modifier|*
name|help_function
call|)
argument_list|(
name|help_data
argument_list|)
expr_stmt|;
block|}
end_function

begin_comment
comment|/*  Do all the actual GtkTipsQuery calls in idle functions and check for  *  some widget holding a grab before starting the query because strange  *  things happen if (1) the help browser pops up while the query has  *  grabbed the pointer or (2) the query grabs the pointer while some  *  other part of the gimp has grabbed it (e.g. a tool, eek)  */
end_comment

begin_function
specifier|static
name|gint
DECL|function|gimp_help_tips_query_idle_show_help (gpointer data)
name|gimp_help_tips_query_idle_show_help
parameter_list|(
name|gpointer
name|data
parameter_list|)
block|{
name|GtkWidget
modifier|*
name|event_widget
decl_stmt|;
name|GtkWidget
modifier|*
name|toplevel_widget
decl_stmt|;
name|GtkWidget
modifier|*
name|widget
decl_stmt|;
name|GtkTooltipsData
modifier|*
name|tooltips_data
decl_stmt|;
name|gchar
modifier|*
name|help_data
init|=
name|NULL
decl_stmt|;
name|event_widget
operator|=
name|GTK_WIDGET
argument_list|(
name|data
argument_list|)
expr_stmt|;
name|toplevel_widget
operator|=
name|gtk_widget_get_toplevel
argument_list|(
name|event_widget
argument_list|)
expr_stmt|;
comment|/*  search for help_data in this widget's parent containers  */
for|for
control|(
name|widget
operator|=
name|event_widget
init|;
name|widget
condition|;
name|widget
operator|=
name|widget
operator|->
name|parent
control|)
block|{
if|if
condition|(
operator|(
name|tooltips_data
operator|=
name|gtk_tooltips_data_get
argument_list|(
name|widget
argument_list|)
operator|)
operator|&&
name|tooltips_data
operator|->
name|tip_private
condition|)
block|{
name|help_data
operator|=
name|tooltips_data
operator|->
name|tip_private
expr_stmt|;
block|}
else|else
block|{
name|help_data
operator|=
operator|(
name|gchar
operator|*
operator|)
name|gtk_object_get_data
argument_list|(
name|GTK_OBJECT
argument_list|(
name|widget
argument_list|)
argument_list|,
literal|"gimp_help_data"
argument_list|)
expr_stmt|;
block|}
if|if
condition|(
name|help_data
operator|||
name|widget
operator|==
name|toplevel_widget
condition|)
break|break;
block|}
if|if
condition|(
operator|!
name|help_data
condition|)
return|return
name|FALSE
return|;
if|if
condition|(
name|help_data
index|[
literal|0
index|]
operator|==
literal|'#'
condition|)
block|{
name|gchar
modifier|*
name|help_index
decl_stmt|;
if|if
condition|(
name|widget
operator|==
name|toplevel_widget
condition|)
return|return
name|FALSE
return|;
name|help_index
operator|=
name|help_data
expr_stmt|;
name|help_data
operator|=
name|NULL
expr_stmt|;
for|for
control|(
name|widget
operator|=
name|widget
operator|->
name|parent
init|;
name|widget
condition|;
name|widget
operator|=
name|widget
operator|->
name|parent
control|)
block|{
if|if
condition|(
operator|(
name|tooltips_data
operator|=
name|gtk_tooltips_data_get
argument_list|(
name|widget
argument_list|)
operator|)
operator|&&
name|tooltips_data
operator|->
name|tip_private
condition|)
block|{
name|help_data
operator|=
name|tooltips_data
operator|->
name|tip_private
expr_stmt|;
block|}
else|else
block|{
name|help_data
operator|=
operator|(
name|gchar
operator|*
operator|)
name|gtk_object_get_data
argument_list|(
name|GTK_OBJECT
argument_list|(
name|widget
argument_list|)
argument_list|,
literal|"gimp_help_data"
argument_list|)
expr_stmt|;
block|}
if|if
condition|(
name|help_data
condition|)
break|break;
block|}
if|if
condition|(
name|help_data
condition|)
block|{
name|gchar
modifier|*
name|help_text
decl_stmt|;
name|help_text
operator|=
name|g_strconcat
argument_list|(
name|help_data
argument_list|,
name|help_index
argument_list|,
name|NULL
argument_list|)
expr_stmt|;
name|gimp_help
argument_list|(
name|help_text
argument_list|)
expr_stmt|;
name|g_free
argument_list|(
name|help_text
argument_list|)
expr_stmt|;
block|}
block|}
else|else
block|{
name|gimp_help
argument_list|(
name|help_data
argument_list|)
expr_stmt|;
block|}
return|return
name|FALSE
return|;
block|}
end_function

begin_function
specifier|static
name|gint
DECL|function|gimp_help_tips_query_widget_selected (GtkWidget * tips_query,GtkWidget * widget,const gchar * tip_text,const gchar * tip_private,GdkEventButton * event,gpointer func_data)
name|gimp_help_tips_query_widget_selected
parameter_list|(
name|GtkWidget
modifier|*
name|tips_query
parameter_list|,
name|GtkWidget
modifier|*
name|widget
parameter_list|,
specifier|const
name|gchar
modifier|*
name|tip_text
parameter_list|,
specifier|const
name|gchar
modifier|*
name|tip_private
parameter_list|,
name|GdkEventButton
modifier|*
name|event
parameter_list|,
name|gpointer
name|func_data
parameter_list|)
block|{
if|if
condition|(
name|use_help
operator|&&
name|widget
condition|)
name|gtk_idle_add
argument_list|(
operator|(
name|GtkFunction
operator|)
name|gimp_help_tips_query_idle_show_help
argument_list|,
operator|(
name|gpointer
operator|)
name|widget
argument_list|)
expr_stmt|;
return|return
name|TRUE
return|;
block|}
end_function

begin_function
specifier|static
name|gint
DECL|function|gimp_help_tips_query_idle_start (gpointer tips_query)
name|gimp_help_tips_query_idle_start
parameter_list|(
name|gpointer
name|tips_query
parameter_list|)
block|{
if|if
condition|(
operator|!
name|gtk_grab_get_current
argument_list|()
condition|)
name|gtk_tips_query_start_query
argument_list|(
name|GTK_TIPS_QUERY
argument_list|(
name|tips_query
argument_list|)
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
DECL|function|gimp_help_tips_query_start (GtkWidget * widget,gpointer tips_query)
name|gimp_help_tips_query_start
parameter_list|(
name|GtkWidget
modifier|*
name|widget
parameter_list|,
name|gpointer
name|tips_query
parameter_list|)
block|{
if|if
condition|(
name|use_help
operator|&&
operator|!
name|GTK_TIPS_QUERY
argument_list|(
name|tips_query
argument_list|)
operator|->
name|in_query
condition|)
name|gtk_idle_add
argument_list|(
operator|(
name|GtkFunction
operator|)
name|gimp_help_tips_query_idle_start
argument_list|,
name|tips_query
argument_list|)
expr_stmt|;
block|}
end_function

end_unit

