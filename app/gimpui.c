begin_unit|revision:0.9.5;language:C;cregit-version:0.0.1
begin_comment
comment|/* The GIMP -- an image manipulation program  * Copyright (C) 1995 Spencer Kimball and Peter Mattis  *  * gimpui.c  * Copyright (C) 1999 Michael Natterer<mitch@gimp.org>  *  * This program is free software; you can redistribute it and/or modify  * it under the terms of the GNU General Public License as published by  * the Free Software Foundation; either version 2 of the License, or  * (at your option) any later version.  *  * This program is distributed in the hope that it will be useful,  * but WITHOUT ANY WARRANTY; without even the implied warranty of  * MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the  * GNU General Public License for more details.  *  * You should have received a copy of the GNU General Public License  * along with this program; if not, write to the Free Software  * Foundation, Inc., 59 Temple Place - Suite 330, Boston, MA 02111-1307, USA.  */
end_comment

begin_include
include|#
directive|include
file|"config.h"
end_include

begin_include
include|#
directive|include
file|<stdio.h>
end_include

begin_include
include|#
directive|include
file|"gimpui.h"
end_include

begin_include
include|#
directive|include
file|"libgimp/gimpsizeentry.h"
end_include

begin_include
include|#
directive|include
file|"libgimp/gimpintl.h"
end_include

begin_decl_stmt
specifier|extern
name|gchar
modifier|*
name|prog_name
decl_stmt|;
end_decl_stmt

begin_function_decl
specifier|static
name|void
name|gimp_message_box_close_callback
parameter_list|(
name|GtkWidget
modifier|*
parameter_list|,
name|gpointer
parameter_list|)
function_decl|;
end_function_decl

begin_comment
comment|/*  *  String, integer, double and size query boxes  */
end_comment

begin_typedef
DECL|typedef|QueryBox
typedef|typedef
name|struct
name|_QueryBox
name|QueryBox
typedef|;
end_typedef

begin_struct
DECL|struct|_QueryBox
struct|struct
name|_QueryBox
block|{
DECL|member|qbox
name|GtkWidget
modifier|*
name|qbox
decl_stmt|;
DECL|member|vbox
name|GtkWidget
modifier|*
name|vbox
decl_stmt|;
DECL|member|entry
name|GtkWidget
modifier|*
name|entry
decl_stmt|;
DECL|member|object
name|GtkObject
modifier|*
name|object
decl_stmt|;
DECL|member|callback
name|GimpQueryFunc
name|callback
decl_stmt|;
DECL|member|data
name|gpointer
name|data
decl_stmt|;
block|}
struct|;
end_struct

begin_function_decl
specifier|static
name|QueryBox
modifier|*
name|create_query_box
parameter_list|(
name|gchar
modifier|*
parameter_list|,
name|GimpHelpFunc
parameter_list|,
name|gchar
modifier|*
parameter_list|,
name|GtkSignalFunc
parameter_list|,
name|gchar
modifier|*
parameter_list|,
name|GtkObject
modifier|*
parameter_list|,
name|gchar
modifier|*
parameter_list|,
name|GimpQueryFunc
parameter_list|,
name|gpointer
parameter_list|)
function_decl|;
end_function_decl

begin_function_decl
specifier|static
name|void
name|query_box_cancel_callback
parameter_list|(
name|GtkWidget
modifier|*
parameter_list|,
name|gpointer
parameter_list|)
function_decl|;
end_function_decl

begin_function_decl
specifier|static
name|void
name|string_query_box_ok_callback
parameter_list|(
name|GtkWidget
modifier|*
parameter_list|,
name|gpointer
parameter_list|)
function_decl|;
end_function_decl

begin_function_decl
specifier|static
name|void
name|int_query_box_ok_callback
parameter_list|(
name|GtkWidget
modifier|*
parameter_list|,
name|gpointer
parameter_list|)
function_decl|;
end_function_decl

begin_function_decl
specifier|static
name|void
name|double_query_box_ok_callback
parameter_list|(
name|GtkWidget
modifier|*
parameter_list|,
name|gpointer
parameter_list|)
function_decl|;
end_function_decl

begin_function_decl
specifier|static
name|void
name|size_query_box_ok_callback
parameter_list|(
name|GtkWidget
modifier|*
parameter_list|,
name|gpointer
parameter_list|)
function_decl|;
end_function_decl

begin_comment
comment|/*  create a generic query box without any entry widget  */
end_comment

begin_function
specifier|static
name|QueryBox
modifier|*
DECL|function|create_query_box (gchar * title,GimpHelpFunc help_func,gchar * help_data,GtkSignalFunc ok_callback,gchar * message,GtkObject * object,gchar * signal,GimpQueryFunc callback,gpointer data)
name|create_query_box
parameter_list|(
name|gchar
modifier|*
name|title
parameter_list|,
name|GimpHelpFunc
name|help_func
parameter_list|,
name|gchar
modifier|*
name|help_data
parameter_list|,
name|GtkSignalFunc
name|ok_callback
parameter_list|,
name|gchar
modifier|*
name|message
parameter_list|,
name|GtkObject
modifier|*
name|object
parameter_list|,
name|gchar
modifier|*
name|signal
parameter_list|,
name|GimpQueryFunc
name|callback
parameter_list|,
name|gpointer
name|data
parameter_list|)
block|{
name|QueryBox
modifier|*
name|query_box
decl_stmt|;
name|GtkWidget
modifier|*
name|qbox
decl_stmt|;
name|GtkWidget
modifier|*
name|vbox
decl_stmt|;
name|GtkWidget
modifier|*
name|label
decl_stmt|;
name|query_box
operator|=
name|g_new
argument_list|(
name|QueryBox
argument_list|,
literal|1
argument_list|)
expr_stmt|;
name|qbox
operator|=
name|gimp_dialog_new
argument_list|(
name|title
argument_list|,
literal|"query_box"
argument_list|,
name|help_func
argument_list|,
name|help_data
argument_list|,
name|GTK_WIN_POS_MOUSE
argument_list|,
name|FALSE
argument_list|,
name|TRUE
argument_list|,
name|FALSE
argument_list|,
name|_
argument_list|(
literal|"OK"
argument_list|)
argument_list|,
name|ok_callback
argument_list|,
name|query_box
argument_list|,
name|NULL
argument_list|,
name|NULL
argument_list|,
name|TRUE
argument_list|,
name|FALSE
argument_list|,
name|_
argument_list|(
literal|"Cancel"
argument_list|)
argument_list|,
name|query_box_cancel_callback
argument_list|,
name|query_box
argument_list|,
name|NULL
argument_list|,
name|NULL
argument_list|,
name|FALSE
argument_list|,
name|TRUE
argument_list|,
name|NULL
argument_list|)
expr_stmt|;
comment|/*  if we are associated with an object, connect to the provided signal  */
if|if
condition|(
name|object
operator|&&
name|GTK_IS_OBJECT
argument_list|(
name|object
argument_list|)
operator|&&
name|signal
condition|)
name|gtk_signal_connect
argument_list|(
name|GTK_OBJECT
argument_list|(
name|object
argument_list|)
argument_list|,
name|signal
argument_list|,
operator|(
name|GtkSignalFunc
operator|)
name|query_box_cancel_callback
argument_list|,
name|query_box
argument_list|)
expr_stmt|;
else|else
name|object
operator|=
name|NULL
expr_stmt|;
name|vbox
operator|=
name|gtk_vbox_new
argument_list|(
name|FALSE
argument_list|,
literal|2
argument_list|)
expr_stmt|;
name|gtk_container_set_border_width
argument_list|(
name|GTK_CONTAINER
argument_list|(
name|vbox
argument_list|)
argument_list|,
literal|4
argument_list|)
expr_stmt|;
name|gtk_container_add
argument_list|(
name|GTK_CONTAINER
argument_list|(
name|GTK_DIALOG
argument_list|(
name|qbox
argument_list|)
operator|->
name|vbox
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
name|label
operator|=
name|gtk_label_new
argument_list|(
name|message
argument_list|)
expr_stmt|;
name|gtk_box_pack_start
argument_list|(
name|GTK_BOX
argument_list|(
name|vbox
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
name|query_box
operator|->
name|qbox
operator|=
name|qbox
expr_stmt|;
name|query_box
operator|->
name|vbox
operator|=
name|vbox
expr_stmt|;
name|query_box
operator|->
name|entry
operator|=
name|NULL
expr_stmt|;
name|query_box
operator|->
name|object
operator|=
name|object
expr_stmt|;
name|query_box
operator|->
name|callback
operator|=
name|callback
expr_stmt|;
name|query_box
operator|->
name|data
operator|=
name|data
expr_stmt|;
return|return
name|query_box
return|;
block|}
end_function

begin_function
name|GtkWidget
modifier|*
DECL|function|gimp_query_string_box (gchar * title,GimpHelpFunc help_func,gchar * help_data,gchar * message,gchar * initial,GtkObject * object,gchar * signal,GimpQueryFunc callback,gpointer data)
name|gimp_query_string_box
parameter_list|(
name|gchar
modifier|*
name|title
parameter_list|,
name|GimpHelpFunc
name|help_func
parameter_list|,
name|gchar
modifier|*
name|help_data
parameter_list|,
name|gchar
modifier|*
name|message
parameter_list|,
name|gchar
modifier|*
name|initial
parameter_list|,
name|GtkObject
modifier|*
name|object
parameter_list|,
name|gchar
modifier|*
name|signal
parameter_list|,
name|GimpQueryFunc
name|callback
parameter_list|,
name|gpointer
name|data
parameter_list|)
block|{
name|QueryBox
modifier|*
name|query_box
decl_stmt|;
name|GtkWidget
modifier|*
name|entry
decl_stmt|;
name|query_box
operator|=
name|create_query_box
argument_list|(
name|title
argument_list|,
name|help_func
argument_list|,
name|help_data
argument_list|,
name|string_query_box_ok_callback
argument_list|,
name|message
argument_list|,
name|object
argument_list|,
name|signal
argument_list|,
name|callback
argument_list|,
name|data
argument_list|)
expr_stmt|;
name|entry
operator|=
name|gtk_entry_new
argument_list|()
expr_stmt|;
name|gtk_box_pack_start
argument_list|(
name|GTK_BOX
argument_list|(
name|query_box
operator|->
name|vbox
argument_list|)
argument_list|,
name|entry
argument_list|,
name|FALSE
argument_list|,
name|FALSE
argument_list|,
literal|0
argument_list|)
expr_stmt|;
if|if
condition|(
name|initial
condition|)
name|gtk_entry_set_text
argument_list|(
name|GTK_ENTRY
argument_list|(
name|entry
argument_list|)
argument_list|,
name|initial
argument_list|)
expr_stmt|;
name|gtk_widget_grab_focus
argument_list|(
name|entry
argument_list|)
expr_stmt|;
name|gtk_widget_show
argument_list|(
name|entry
argument_list|)
expr_stmt|;
name|query_box
operator|->
name|entry
operator|=
name|entry
expr_stmt|;
return|return
name|query_box
operator|->
name|qbox
return|;
block|}
end_function

begin_function
name|GtkWidget
modifier|*
DECL|function|gimp_query_int_box (gchar * title,GimpHelpFunc help_func,gchar * help_data,gchar * message,gint initial,gint lower,gint upper,GtkObject * object,gchar * signal,GimpQueryFunc callback,gpointer data)
name|gimp_query_int_box
parameter_list|(
name|gchar
modifier|*
name|title
parameter_list|,
name|GimpHelpFunc
name|help_func
parameter_list|,
name|gchar
modifier|*
name|help_data
parameter_list|,
name|gchar
modifier|*
name|message
parameter_list|,
name|gint
name|initial
parameter_list|,
name|gint
name|lower
parameter_list|,
name|gint
name|upper
parameter_list|,
name|GtkObject
modifier|*
name|object
parameter_list|,
name|gchar
modifier|*
name|signal
parameter_list|,
name|GimpQueryFunc
name|callback
parameter_list|,
name|gpointer
name|data
parameter_list|)
block|{
name|QueryBox
modifier|*
name|query_box
decl_stmt|;
name|GtkAdjustment
modifier|*
name|adjustment
decl_stmt|;
name|GtkWidget
modifier|*
name|spinbutton
decl_stmt|;
name|query_box
operator|=
name|create_query_box
argument_list|(
name|title
argument_list|,
name|help_func
argument_list|,
name|help_data
argument_list|,
name|int_query_box_ok_callback
argument_list|,
name|message
argument_list|,
name|object
argument_list|,
name|signal
argument_list|,
name|callback
argument_list|,
name|data
argument_list|)
expr_stmt|;
name|adjustment
operator|=
name|GTK_ADJUSTMENT
argument_list|(
name|gtk_adjustment_new
argument_list|(
name|initial
argument_list|,
name|lower
argument_list|,
name|upper
argument_list|,
literal|1
argument_list|,
literal|10
argument_list|,
literal|0
argument_list|)
argument_list|)
expr_stmt|;
name|spinbutton
operator|=
name|gtk_spin_button_new
argument_list|(
name|adjustment
argument_list|,
literal|1.0
argument_list|,
literal|0
argument_list|)
expr_stmt|;
name|gtk_box_pack_start
argument_list|(
name|GTK_BOX
argument_list|(
name|query_box
operator|->
name|vbox
argument_list|)
argument_list|,
name|spinbutton
argument_list|,
name|FALSE
argument_list|,
name|FALSE
argument_list|,
literal|0
argument_list|)
expr_stmt|;
name|gtk_widget_grab_focus
argument_list|(
name|spinbutton
argument_list|)
expr_stmt|;
name|gtk_widget_show
argument_list|(
name|spinbutton
argument_list|)
expr_stmt|;
name|query_box
operator|->
name|entry
operator|=
name|spinbutton
expr_stmt|;
return|return
name|query_box
operator|->
name|qbox
return|;
block|}
end_function

begin_function
name|GtkWidget
modifier|*
DECL|function|gimp_query_double_box (gchar * title,GimpHelpFunc help_func,gchar * help_data,gchar * message,gdouble initial,gdouble lower,gdouble upper,gint digits,GtkObject * object,gchar * signal,GimpQueryFunc callback,gpointer data)
name|gimp_query_double_box
parameter_list|(
name|gchar
modifier|*
name|title
parameter_list|,
name|GimpHelpFunc
name|help_func
parameter_list|,
name|gchar
modifier|*
name|help_data
parameter_list|,
name|gchar
modifier|*
name|message
parameter_list|,
name|gdouble
name|initial
parameter_list|,
name|gdouble
name|lower
parameter_list|,
name|gdouble
name|upper
parameter_list|,
name|gint
name|digits
parameter_list|,
name|GtkObject
modifier|*
name|object
parameter_list|,
name|gchar
modifier|*
name|signal
parameter_list|,
name|GimpQueryFunc
name|callback
parameter_list|,
name|gpointer
name|data
parameter_list|)
block|{
name|QueryBox
modifier|*
name|query_box
decl_stmt|;
name|GtkAdjustment
modifier|*
name|adjustment
decl_stmt|;
name|GtkWidget
modifier|*
name|spinbutton
decl_stmt|;
name|query_box
operator|=
name|create_query_box
argument_list|(
name|title
argument_list|,
name|help_func
argument_list|,
name|help_data
argument_list|,
name|double_query_box_ok_callback
argument_list|,
name|message
argument_list|,
name|object
argument_list|,
name|signal
argument_list|,
name|callback
argument_list|,
name|data
argument_list|)
expr_stmt|;
name|adjustment
operator|=
name|GTK_ADJUSTMENT
argument_list|(
name|gtk_adjustment_new
argument_list|(
name|initial
argument_list|,
name|lower
argument_list|,
name|upper
argument_list|,
literal|1
argument_list|,
literal|10
argument_list|,
literal|0
argument_list|)
argument_list|)
expr_stmt|;
name|spinbutton
operator|=
name|gtk_spin_button_new
argument_list|(
name|adjustment
argument_list|,
literal|1.0
argument_list|,
name|digits
argument_list|)
expr_stmt|;
name|gtk_box_pack_start
argument_list|(
name|GTK_BOX
argument_list|(
name|query_box
operator|->
name|vbox
argument_list|)
argument_list|,
name|spinbutton
argument_list|,
name|FALSE
argument_list|,
name|FALSE
argument_list|,
literal|0
argument_list|)
expr_stmt|;
name|gtk_widget_grab_focus
argument_list|(
name|spinbutton
argument_list|)
expr_stmt|;
name|gtk_widget_show
argument_list|(
name|spinbutton
argument_list|)
expr_stmt|;
name|query_box
operator|->
name|entry
operator|=
name|spinbutton
expr_stmt|;
return|return
name|query_box
operator|->
name|qbox
return|;
block|}
end_function

begin_function
name|GtkWidget
modifier|*
DECL|function|gimp_query_size_box (gchar * title,GimpHelpFunc help_func,gchar * help_data,gchar * message,gdouble initial,gdouble lower,gdouble upper,gint digits,GimpUnit unit,gdouble resolution,gboolean dot_for_dot,GtkObject * object,gchar * signal,GimpQueryFunc callback,gpointer data)
name|gimp_query_size_box
parameter_list|(
name|gchar
modifier|*
name|title
parameter_list|,
name|GimpHelpFunc
name|help_func
parameter_list|,
name|gchar
modifier|*
name|help_data
parameter_list|,
name|gchar
modifier|*
name|message
parameter_list|,
name|gdouble
name|initial
parameter_list|,
name|gdouble
name|lower
parameter_list|,
name|gdouble
name|upper
parameter_list|,
name|gint
name|digits
parameter_list|,
name|GimpUnit
name|unit
parameter_list|,
name|gdouble
name|resolution
parameter_list|,
name|gboolean
name|dot_for_dot
parameter_list|,
name|GtkObject
modifier|*
name|object
parameter_list|,
name|gchar
modifier|*
name|signal
parameter_list|,
name|GimpQueryFunc
name|callback
parameter_list|,
name|gpointer
name|data
parameter_list|)
block|{
name|QueryBox
modifier|*
name|query_box
decl_stmt|;
name|GtkWidget
modifier|*
name|sizeentry
decl_stmt|;
name|query_box
operator|=
name|create_query_box
argument_list|(
name|title
argument_list|,
name|help_func
argument_list|,
name|help_data
argument_list|,
name|size_query_box_ok_callback
argument_list|,
name|message
argument_list|,
name|object
argument_list|,
name|signal
argument_list|,
name|callback
argument_list|,
name|data
argument_list|)
expr_stmt|;
name|sizeentry
operator|=
name|gimp_size_entry_new
argument_list|(
literal|1
argument_list|,
name|unit
argument_list|,
literal|"%p"
argument_list|,
name|TRUE
argument_list|,
name|FALSE
argument_list|,
name|FALSE
argument_list|,
literal|100
argument_list|,
name|GIMP_SIZE_ENTRY_UPDATE_SIZE
argument_list|)
expr_stmt|;
if|if
condition|(
name|dot_for_dot
condition|)
name|gimp_size_entry_set_unit
argument_list|(
name|GIMP_SIZE_ENTRY
argument_list|(
name|sizeentry
argument_list|)
argument_list|,
name|GIMP_UNIT_PIXEL
argument_list|)
expr_stmt|;
name|gimp_size_entry_set_resolution
argument_list|(
name|GIMP_SIZE_ENTRY
argument_list|(
name|sizeentry
argument_list|)
argument_list|,
literal|0
argument_list|,
name|resolution
argument_list|,
name|FALSE
argument_list|)
expr_stmt|;
name|gimp_size_entry_set_refval_digits
argument_list|(
name|GIMP_SIZE_ENTRY
argument_list|(
name|sizeentry
argument_list|)
argument_list|,
literal|0
argument_list|,
name|digits
argument_list|)
expr_stmt|;
name|gimp_size_entry_set_refval_boundaries
argument_list|(
name|GIMP_SIZE_ENTRY
argument_list|(
name|sizeentry
argument_list|)
argument_list|,
literal|0
argument_list|,
name|lower
argument_list|,
name|upper
argument_list|)
expr_stmt|;
name|gimp_size_entry_set_refval
argument_list|(
name|GIMP_SIZE_ENTRY
argument_list|(
name|sizeentry
argument_list|)
argument_list|,
literal|0
argument_list|,
name|initial
argument_list|)
expr_stmt|;
name|gtk_box_pack_start
argument_list|(
name|GTK_BOX
argument_list|(
name|query_box
operator|->
name|vbox
argument_list|)
argument_list|,
name|sizeentry
argument_list|,
name|FALSE
argument_list|,
name|FALSE
argument_list|,
literal|0
argument_list|)
expr_stmt|;
name|gimp_size_entry_grab_focus
argument_list|(
name|GIMP_SIZE_ENTRY
argument_list|(
name|sizeentry
argument_list|)
argument_list|)
expr_stmt|;
name|gtk_widget_show
argument_list|(
name|sizeentry
argument_list|)
expr_stmt|;
name|query_box
operator|->
name|entry
operator|=
name|sizeentry
expr_stmt|;
return|return
name|query_box
operator|->
name|qbox
return|;
block|}
end_function

begin_function
specifier|static
name|void
DECL|function|query_box_cancel_callback (GtkWidget * widget,gpointer data)
name|query_box_cancel_callback
parameter_list|(
name|GtkWidget
modifier|*
name|widget
parameter_list|,
name|gpointer
name|data
parameter_list|)
block|{
name|QueryBox
modifier|*
name|query_box
decl_stmt|;
name|query_box
operator|=
operator|(
name|QueryBox
operator|*
operator|)
name|data
expr_stmt|;
comment|/*  disconnect, if we are connected to some signal  */
if|if
condition|(
name|query_box
operator|->
name|object
condition|)
name|gtk_signal_disconnect_by_data
argument_list|(
name|query_box
operator|->
name|object
argument_list|,
name|query_box
argument_list|)
expr_stmt|;
comment|/*  Destroy the box  */
name|gtk_widget_destroy
argument_list|(
name|query_box
operator|->
name|qbox
argument_list|)
expr_stmt|;
name|g_free
argument_list|(
name|query_box
argument_list|)
expr_stmt|;
block|}
end_function

begin_function
specifier|static
name|void
DECL|function|string_query_box_ok_callback (GtkWidget * widget,gpointer data)
name|string_query_box_ok_callback
parameter_list|(
name|GtkWidget
modifier|*
name|widget
parameter_list|,
name|gpointer
name|data
parameter_list|)
block|{
name|QueryBox
modifier|*
name|query_box
decl_stmt|;
name|gchar
modifier|*
name|string
decl_stmt|;
name|query_box
operator|=
operator|(
name|QueryBox
operator|*
operator|)
name|data
expr_stmt|;
name|gtk_widget_set_sensitive
argument_list|(
name|query_box
operator|->
name|qbox
argument_list|,
name|FALSE
argument_list|)
expr_stmt|;
comment|/*  disconnect, if we are connected to some signal  */
if|if
condition|(
name|query_box
operator|->
name|object
condition|)
name|gtk_signal_disconnect_by_data
argument_list|(
name|query_box
operator|->
name|object
argument_list|,
name|query_box
argument_list|)
expr_stmt|;
comment|/*  Get the entry data  */
name|string
operator|=
name|g_strdup
argument_list|(
name|gtk_entry_get_text
argument_list|(
name|GTK_ENTRY
argument_list|(
name|query_box
operator|->
name|entry
argument_list|)
argument_list|)
argument_list|)
expr_stmt|;
comment|/*  Call the user defined callback  */
call|(
modifier|*
name|query_box
operator|->
name|callback
call|)
argument_list|(
name|query_box
operator|->
name|qbox
argument_list|,
name|query_box
operator|->
name|data
argument_list|,
operator|(
name|gpointer
operator|)
name|string
argument_list|)
expr_stmt|;
comment|/*  Destroy the box  */
name|gtk_widget_destroy
argument_list|(
name|query_box
operator|->
name|qbox
argument_list|)
expr_stmt|;
name|g_free
argument_list|(
name|query_box
argument_list|)
expr_stmt|;
block|}
end_function

begin_function
specifier|static
name|void
DECL|function|int_query_box_ok_callback (GtkWidget * widget,gpointer data)
name|int_query_box_ok_callback
parameter_list|(
name|GtkWidget
modifier|*
name|widget
parameter_list|,
name|gpointer
name|data
parameter_list|)
block|{
name|QueryBox
modifier|*
name|query_box
decl_stmt|;
name|gint
modifier|*
name|integer_value
decl_stmt|;
name|query_box
operator|=
operator|(
name|QueryBox
operator|*
operator|)
name|data
expr_stmt|;
name|gtk_widget_set_sensitive
argument_list|(
name|query_box
operator|->
name|qbox
argument_list|,
name|FALSE
argument_list|)
expr_stmt|;
comment|/*  disconnect, if we are connected to some signal  */
if|if
condition|(
name|query_box
operator|->
name|object
condition|)
name|gtk_signal_disconnect_by_data
argument_list|(
name|query_box
operator|->
name|object
argument_list|,
name|query_box
argument_list|)
expr_stmt|;
comment|/*  Get the spinbutton data  */
name|integer_value
operator|=
name|g_malloc
argument_list|(
sizeof|sizeof
argument_list|(
name|gint
argument_list|)
argument_list|)
expr_stmt|;
operator|*
name|integer_value
operator|=
name|gtk_spin_button_get_value_as_int
argument_list|(
name|GTK_SPIN_BUTTON
argument_list|(
name|query_box
operator|->
name|entry
argument_list|)
argument_list|)
expr_stmt|;
comment|/*  Call the user defined callback  */
call|(
modifier|*
name|query_box
operator|->
name|callback
call|)
argument_list|(
name|query_box
operator|->
name|qbox
argument_list|,
name|query_box
operator|->
name|data
argument_list|,
operator|(
name|gpointer
operator|)
name|integer_value
argument_list|)
expr_stmt|;
comment|/*  Destroy the box  */
name|gtk_widget_destroy
argument_list|(
name|query_box
operator|->
name|qbox
argument_list|)
expr_stmt|;
name|g_free
argument_list|(
name|query_box
argument_list|)
expr_stmt|;
block|}
end_function

begin_function
specifier|static
name|void
DECL|function|double_query_box_ok_callback (GtkWidget * widget,gpointer data)
name|double_query_box_ok_callback
parameter_list|(
name|GtkWidget
modifier|*
name|widget
parameter_list|,
name|gpointer
name|data
parameter_list|)
block|{
name|QueryBox
modifier|*
name|query_box
decl_stmt|;
name|gdouble
modifier|*
name|double_value
decl_stmt|;
name|query_box
operator|=
operator|(
name|QueryBox
operator|*
operator|)
name|data
expr_stmt|;
name|gtk_widget_set_sensitive
argument_list|(
name|query_box
operator|->
name|qbox
argument_list|,
name|FALSE
argument_list|)
expr_stmt|;
comment|/*  disconnect, if we are connected to some signal  */
if|if
condition|(
name|query_box
operator|->
name|object
condition|)
name|gtk_signal_disconnect_by_data
argument_list|(
name|query_box
operator|->
name|object
argument_list|,
name|query_box
argument_list|)
expr_stmt|;
comment|/*  Get the spinbutton data  */
name|double_value
operator|=
name|g_malloc
argument_list|(
sizeof|sizeof
argument_list|(
name|gdouble
argument_list|)
argument_list|)
expr_stmt|;
operator|*
name|double_value
operator|=
name|gtk_spin_button_get_value_as_float
argument_list|(
name|GTK_SPIN_BUTTON
argument_list|(
name|query_box
operator|->
name|entry
argument_list|)
argument_list|)
expr_stmt|;
comment|/*  Call the user defined callback  */
call|(
modifier|*
name|query_box
operator|->
name|callback
call|)
argument_list|(
name|query_box
operator|->
name|qbox
argument_list|,
name|query_box
operator|->
name|data
argument_list|,
operator|(
name|gpointer
operator|)
name|double_value
argument_list|)
expr_stmt|;
comment|/*  Destroy the box  */
name|gtk_widget_destroy
argument_list|(
name|query_box
operator|->
name|qbox
argument_list|)
expr_stmt|;
name|g_free
argument_list|(
name|query_box
argument_list|)
expr_stmt|;
block|}
end_function

begin_function
specifier|static
name|void
DECL|function|size_query_box_ok_callback (GtkWidget * widget,gpointer data)
name|size_query_box_ok_callback
parameter_list|(
name|GtkWidget
modifier|*
name|widget
parameter_list|,
name|gpointer
name|data
parameter_list|)
block|{
name|QueryBox
modifier|*
name|query_box
decl_stmt|;
name|gdouble
modifier|*
name|double_value
decl_stmt|;
name|query_box
operator|=
operator|(
name|QueryBox
operator|*
operator|)
name|data
expr_stmt|;
name|gtk_widget_set_sensitive
argument_list|(
name|query_box
operator|->
name|qbox
argument_list|,
name|FALSE
argument_list|)
expr_stmt|;
comment|/*  disconnect, if we are connected to some signal  */
if|if
condition|(
name|query_box
operator|->
name|object
condition|)
name|gtk_signal_disconnect_by_data
argument_list|(
name|query_box
operator|->
name|object
argument_list|,
name|query_box
argument_list|)
expr_stmt|;
comment|/*  Get the sizeentry data  */
name|double_value
operator|=
name|g_malloc
argument_list|(
sizeof|sizeof
argument_list|(
name|gdouble
argument_list|)
argument_list|)
expr_stmt|;
operator|*
name|double_value
operator|=
name|gimp_size_entry_get_refval
argument_list|(
name|GIMP_SIZE_ENTRY
argument_list|(
name|query_box
operator|->
name|entry
argument_list|)
argument_list|,
literal|0
argument_list|)
expr_stmt|;
comment|/*  Pass the selected unit to the callback  */
name|gtk_object_set_data
argument_list|(
name|GTK_OBJECT
argument_list|(
name|widget
argument_list|)
argument_list|,
literal|"size_query_unit"
argument_list|,
operator|(
name|gpointer
operator|)
name|gimp_size_entry_get_unit
argument_list|(
name|GIMP_SIZE_ENTRY
argument_list|(
name|query_box
operator|->
name|entry
argument_list|)
argument_list|)
argument_list|)
expr_stmt|;
comment|/*  Call the user defined callback  */
call|(
modifier|*
name|query_box
operator|->
name|callback
call|)
argument_list|(
name|query_box
operator|->
name|qbox
argument_list|,
name|query_box
operator|->
name|data
argument_list|,
operator|(
name|gpointer
operator|)
name|double_value
argument_list|)
expr_stmt|;
comment|/*  Destroy the box  */
name|gtk_widget_destroy
argument_list|(
name|query_box
operator|->
name|qbox
argument_list|)
expr_stmt|;
name|g_free
argument_list|(
name|query_box
argument_list|)
expr_stmt|;
block|}
end_function

begin_comment
comment|/*  *  Message Boxes...  */
end_comment

begin_typedef
DECL|typedef|MessageBox
typedef|typedef
name|struct
name|_MessageBox
name|MessageBox
typedef|;
end_typedef

begin_struct
DECL|struct|_MessageBox
struct|struct
name|_MessageBox
block|{
DECL|member|mbox
name|GtkWidget
modifier|*
name|mbox
decl_stmt|;
DECL|member|repeat_label
name|GtkWidget
modifier|*
name|repeat_label
decl_stmt|;
DECL|member|message
name|gchar
modifier|*
name|message
decl_stmt|;
DECL|member|repeat_count
name|gint
name|repeat_count
decl_stmt|;
DECL|member|callback
name|GtkCallback
name|callback
decl_stmt|;
DECL|member|data
name|gpointer
name|data
decl_stmt|;
block|}
struct|;
end_struct

begin_comment
comment|/*  the maximum number of concucrrent dialog boxes */
end_comment

begin_define
DECL|macro|MESSAGE_BOX_MAXIMUM
define|#
directive|define
name|MESSAGE_BOX_MAXIMUM
value|4
end_define

begin_decl_stmt
DECL|variable|message_boxes
specifier|static
name|GList
modifier|*
name|message_boxes
init|=
name|NULL
decl_stmt|;
end_decl_stmt

begin_function
name|void
DECL|function|gimp_message_box (gchar * message,GtkCallback callback,gpointer data)
name|gimp_message_box
parameter_list|(
name|gchar
modifier|*
name|message
parameter_list|,
name|GtkCallback
name|callback
parameter_list|,
name|gpointer
name|data
parameter_list|)
block|{
name|MessageBox
modifier|*
name|msg_box
decl_stmt|;
name|GtkWidget
modifier|*
name|mbox
decl_stmt|;
name|GtkWidget
modifier|*
name|vbox
decl_stmt|;
name|GtkWidget
modifier|*
name|label
decl_stmt|;
name|GList
modifier|*
name|list
decl_stmt|;
if|if
condition|(
operator|!
name|message
condition|)
return|return;
if|if
condition|(
name|g_list_length
argument_list|(
name|message_boxes
argument_list|)
operator|>
name|MESSAGE_BOX_MAXIMUM
condition|)
block|{
name|fprintf
argument_list|(
name|stderr
argument_list|,
literal|"%s: %s\n"
argument_list|,
name|prog_name
argument_list|,
name|message
argument_list|)
expr_stmt|;
return|return;
block|}
for|for
control|(
name|list
operator|=
name|message_boxes
init|;
name|list
condition|;
name|list
operator|=
name|list
operator|->
name|next
control|)
block|{
name|msg_box
operator|=
name|list
operator|->
name|data
expr_stmt|;
if|if
condition|(
name|strcmp
argument_list|(
name|msg_box
operator|->
name|message
argument_list|,
name|message
argument_list|)
operator|==
literal|0
condition|)
block|{
name|msg_box
operator|->
name|repeat_count
operator|++
expr_stmt|;
if|if
condition|(
name|msg_box
operator|->
name|repeat_count
operator|>
literal|1
condition|)
block|{
name|gchar
modifier|*
name|text
init|=
name|g_strdup_printf
argument_list|(
name|_
argument_list|(
literal|"Message repeated %d times"
argument_list|)
argument_list|,
name|msg_box
operator|->
name|repeat_count
argument_list|)
decl_stmt|;
name|gtk_label_set_text
argument_list|(
name|GTK_LABEL
argument_list|(
name|msg_box
operator|->
name|repeat_label
argument_list|)
argument_list|,
name|text
argument_list|)
expr_stmt|;
name|g_free
argument_list|(
name|text
argument_list|)
expr_stmt|;
name|gdk_window_raise
argument_list|(
name|msg_box
operator|->
name|mbox
operator|->
name|window
argument_list|)
expr_stmt|;
block|}
else|else
block|{
name|GtkWidget
modifier|*
name|hbox
decl_stmt|;
name|hbox
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
name|GTK_DIALOG
argument_list|(
name|msg_box
operator|->
name|mbox
argument_list|)
operator|->
name|action_area
argument_list|)
argument_list|,
name|hbox
argument_list|,
name|TRUE
argument_list|,
name|FALSE
argument_list|,
literal|4
argument_list|)
expr_stmt|;
name|msg_box
operator|->
name|repeat_label
operator|=
name|gtk_label_new
argument_list|(
name|_
argument_list|(
literal|"Message repeated once"
argument_list|)
argument_list|)
expr_stmt|;
name|gtk_container_add
argument_list|(
name|GTK_CONTAINER
argument_list|(
name|hbox
argument_list|)
argument_list|,
name|msg_box
operator|->
name|repeat_label
argument_list|)
expr_stmt|;
name|gtk_widget_show
argument_list|(
name|msg_box
operator|->
name|repeat_label
argument_list|)
expr_stmt|;
name|gtk_widget_show
argument_list|(
name|hbox
argument_list|)
expr_stmt|;
name|gdk_window_raise
argument_list|(
name|msg_box
operator|->
name|mbox
operator|->
name|window
argument_list|)
expr_stmt|;
block|}
return|return;
block|}
block|}
if|if
condition|(
name|g_list_length
argument_list|(
name|message_boxes
argument_list|)
operator|==
name|MESSAGE_BOX_MAXIMUM
condition|)
block|{
name|fprintf
argument_list|(
name|stderr
argument_list|,
literal|"%s: %s\n"
argument_list|,
name|prog_name
argument_list|,
name|message
argument_list|)
expr_stmt|;
name|message
operator|=
name|_
argument_list|(
literal|"WARNING:\n"
literal|"Too many open message dialogs.\n"
literal|"Messages are redirected to stderr.\n"
argument_list|)
expr_stmt|;
block|}
name|msg_box
operator|=
name|g_new0
argument_list|(
name|MessageBox
argument_list|,
literal|1
argument_list|)
expr_stmt|;
name|mbox
operator|=
name|gimp_dialog_new
argument_list|(
name|_
argument_list|(
literal|"GIMP Message"
argument_list|)
argument_list|,
literal|"gimp_message"
argument_list|,
name|NULL
argument_list|,
name|NULL
argument_list|,
name|GTK_WIN_POS_MOUSE
argument_list|,
name|FALSE
argument_list|,
name|FALSE
argument_list|,
name|FALSE
argument_list|,
name|_
argument_list|(
literal|"OK"
argument_list|)
argument_list|,
name|gimp_message_box_close_callback
argument_list|,
name|msg_box
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
literal|6
argument_list|)
expr_stmt|;
name|gtk_container_add
argument_list|(
name|GTK_CONTAINER
argument_list|(
name|GTK_DIALOG
argument_list|(
name|mbox
argument_list|)
operator|->
name|vbox
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
name|label
operator|=
name|gtk_label_new
argument_list|(
name|message
argument_list|)
expr_stmt|;
name|gtk_label_set_justify
argument_list|(
name|GTK_LABEL
argument_list|(
name|label
argument_list|)
argument_list|,
name|GTK_JUSTIFY_LEFT
argument_list|)
expr_stmt|;
name|gtk_box_pack_start
argument_list|(
name|GTK_BOX
argument_list|(
name|vbox
argument_list|)
argument_list|,
name|label
argument_list|,
name|TRUE
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
name|msg_box
operator|->
name|mbox
operator|=
name|mbox
expr_stmt|;
name|msg_box
operator|->
name|message
operator|=
name|g_strdup
argument_list|(
name|message
argument_list|)
expr_stmt|;
name|msg_box
operator|->
name|callback
operator|=
name|callback
expr_stmt|;
name|msg_box
operator|->
name|data
operator|=
name|data
expr_stmt|;
name|message_boxes
operator|=
name|g_list_append
argument_list|(
name|message_boxes
argument_list|,
name|msg_box
argument_list|)
expr_stmt|;
name|gtk_widget_show
argument_list|(
name|mbox
argument_list|)
expr_stmt|;
block|}
end_function

begin_function
specifier|static
name|void
DECL|function|gimp_message_box_close_callback (GtkWidget * widget,gpointer data)
name|gimp_message_box_close_callback
parameter_list|(
name|GtkWidget
modifier|*
name|widget
parameter_list|,
name|gpointer
name|data
parameter_list|)
block|{
name|MessageBox
modifier|*
name|msg_box
decl_stmt|;
name|msg_box
operator|=
operator|(
name|MessageBox
operator|*
operator|)
name|data
expr_stmt|;
comment|/*  If there is a valid callback, invoke it  */
if|if
condition|(
name|msg_box
operator|->
name|callback
condition|)
call|(
modifier|*
name|msg_box
operator|->
name|callback
call|)
argument_list|(
name|widget
argument_list|,
name|msg_box
operator|->
name|data
argument_list|)
expr_stmt|;
comment|/*  Destroy the box  */
name|gtk_widget_destroy
argument_list|(
name|msg_box
operator|->
name|mbox
argument_list|)
expr_stmt|;
comment|/* make this box available again */
name|message_boxes
operator|=
name|g_list_remove
argument_list|(
name|message_boxes
argument_list|,
name|msg_box
argument_list|)
expr_stmt|;
name|g_free
argument_list|(
name|msg_box
operator|->
name|message
argument_list|)
expr_stmt|;
name|g_free
argument_list|(
name|msg_box
argument_list|)
expr_stmt|;
block|}
end_function

end_unit

