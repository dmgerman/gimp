begin_unit|revision:0.9.5;language:C;cregit-version:0.0.1
begin_comment
comment|/* LIBGIMP - The GIMP Library                                                     * Copyright (C) 1995-1997 Peter Mattis and Spencer Kimball                  *  * This library is free software; you can redistribute it and/or  * modify it under the terms of the GNU Lesser General Public  * License as published by the Free Software Foundation; either  * version 2 of the License, or (at your option) any later version.               *                                                                                * This library is distributed in the hope that it will be useful,                * but WITHOUT ANY WARRANTY; without even the implied warranty of                 * MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the GNU              * Lesser General Public License for more details.  *  * You should have received a copy of the GNU Lesser General Public  * License along with this library; if not, write to the  * Free Software Foundation, Inc., 59 Temple Place - Suite 330,  * Boston, MA 02111-1307, USA.  */
end_comment

begin_include
include|#
directive|include
file|"gimpquerybox.h"
end_include

begin_include
include|#
directive|include
file|"gimpdialog.h"
end_include

begin_include
include|#
directive|include
file|"gimpsizeentry.h"
end_include

begin_include
include|#
directive|include
file|"gimpwidgets.h"
end_include

begin_include
include|#
directive|include
file|"libgimp-intl.h"
end_include

begin_include
include|#
directive|include
file|"pixmaps/eek.xpm"
end_include

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
name|GtkSignalFunc
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
name|GtkSignalFunc
name|cancel_callback
parameter_list|,
name|gchar
modifier|*
name|message
parameter_list|,
name|gchar
modifier|*
name|ok_button
parameter_list|,
name|gchar
modifier|*
name|cancel_button
parameter_list|,
name|GtkObject
modifier|*
name|object
parameter_list|,
name|gchar
modifier|*
name|signal
parameter_list|,
name|GtkSignalFunc
name|callback
parameter_list|,
name|gpointer
name|data
parameter_list|)
function_decl|;
end_function_decl

begin_function_decl
specifier|static
name|QueryBox
modifier|*
name|query_box_disconnect
parameter_list|(
name|gpointer
name|data
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
name|int_query_box_ok_callback
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
name|double_query_box_ok_callback
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
name|size_query_box_ok_callback
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
name|query_box_cancel_callback
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
name|boolean_query_box_true_callback
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
name|boolean_query_box_false_callback
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
comment|/*  create a generic query box without any entry widget  */
end_comment

begin_function
specifier|static
name|QueryBox
modifier|*
DECL|function|create_query_box (gchar * title,GimpHelpFunc help_func,gchar * help_data,GtkSignalFunc ok_callback,GtkSignalFunc cancel_callback,gchar * message,gchar * ok_button,gchar * cancel_button,GtkObject * object,gchar * signal,GtkSignalFunc callback,gpointer data)
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
name|GtkSignalFunc
name|cancel_callback
parameter_list|,
name|gchar
modifier|*
name|message
parameter_list|,
name|gchar
modifier|*
name|ok_button
parameter_list|,
name|gchar
modifier|*
name|cancel_button
parameter_list|,
name|GtkObject
modifier|*
name|object
parameter_list|,
name|gchar
modifier|*
name|signal
parameter_list|,
name|GtkSignalFunc
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
init|=
name|NULL
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
name|ok_button
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
name|cancel_button
argument_list|,
name|cancel_callback
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
name|GTK_SIGNAL_FUNC
argument_list|(
name|query_box_cancel_callback
argument_list|)
argument_list|,
name|query_box
argument_list|)
expr_stmt|;
else|else
name|object
operator|=
name|NULL
expr_stmt|;
if|if
condition|(
name|message
condition|)
block|{
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
literal|6
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
block|}
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
DECL|function|gimp_query_string_box (gchar * title,GimpHelpFunc help_func,gchar * help_data,gchar * message,gchar * initial,GtkObject * object,gchar * signal,GimpQueryStringCallback callback,gpointer data)
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
name|GimpQueryStringCallback
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
name|query_box_cancel_callback
argument_list|,
name|message
argument_list|,
name|_
argument_list|(
literal|"OK"
argument_list|)
argument_list|,
name|_
argument_list|(
literal|"Cancel"
argument_list|)
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
DECL|function|gimp_query_int_box (gchar * title,GimpHelpFunc help_func,gchar * help_data,gchar * message,gint initial,gint lower,gint upper,GtkObject * object,gchar * signal,GimpQueryIntCallback callback,gpointer data)
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
name|GimpQueryIntCallback
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
name|spinbutton
decl_stmt|;
name|GtkObject
modifier|*
name|adjustment
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
name|query_box_cancel_callback
argument_list|,
name|message
argument_list|,
name|_
argument_list|(
literal|"OK"
argument_list|)
argument_list|,
name|_
argument_list|(
literal|"Cancel"
argument_list|)
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
name|spinbutton
operator|=
name|gimp_spin_button_new
argument_list|(
operator|&
name|adjustment
argument_list|,
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
argument_list|,
literal|1
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
DECL|function|gimp_query_double_box (gchar * title,GimpHelpFunc help_func,gchar * help_data,gchar * message,gdouble initial,gdouble lower,gdouble upper,gint digits,GtkObject * object,gchar * signal,GimpQueryDoubleCallback callback,gpointer data)
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
name|GimpQueryDoubleCallback
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
name|spinbutton
decl_stmt|;
name|GtkObject
modifier|*
name|adjustment
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
name|query_box_cancel_callback
argument_list|,
name|message
argument_list|,
name|_
argument_list|(
literal|"OK"
argument_list|)
argument_list|,
name|_
argument_list|(
literal|"Cancel"
argument_list|)
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
name|spinbutton
operator|=
name|gimp_spin_button_new
argument_list|(
operator|&
name|adjustment
argument_list|,
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
argument_list|,
literal|1
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
DECL|function|gimp_query_size_box (gchar * title,GimpHelpFunc help_func,gchar * help_data,gchar * message,gdouble initial,gdouble lower,gdouble upper,gint digits,GimpUnit unit,gdouble resolution,gboolean dot_for_dot,GtkObject * object,gchar * signal,GimpQuerySizeCallback callback,gpointer data)
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
name|GimpQuerySizeCallback
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
name|query_box_cancel_callback
argument_list|,
name|message
argument_list|,
name|_
argument_list|(
literal|"OK"
argument_list|)
argument_list|,
name|_
argument_list|(
literal|"Cancel"
argument_list|)
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
name|GtkWidget
modifier|*
DECL|function|gimp_query_boolean_box (gchar * title,GimpHelpFunc help_func,gchar * help_data,gboolean eek,gchar * message,gchar * true_button,gchar * false_button,GtkObject * object,gchar * signal,GimpQueryBooleanCallback callback,gpointer data)
name|gimp_query_boolean_box
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
name|gboolean
name|eek
parameter_list|,
name|gchar
modifier|*
name|message
parameter_list|,
name|gchar
modifier|*
name|true_button
parameter_list|,
name|gchar
modifier|*
name|false_button
parameter_list|,
name|GtkObject
modifier|*
name|object
parameter_list|,
name|gchar
modifier|*
name|signal
parameter_list|,
name|GimpQueryBooleanCallback
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
name|hbox
decl_stmt|;
name|GtkWidget
modifier|*
name|pixmap_widget
decl_stmt|;
name|GtkWidget
modifier|*
name|label
decl_stmt|;
specifier|static
name|GdkPixmap
modifier|*
name|eek_pixmap
init|=
name|NULL
decl_stmt|;
specifier|static
name|GdkBitmap
modifier|*
name|eek_mask
init|=
name|NULL
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
name|boolean_query_box_true_callback
argument_list|,
name|boolean_query_box_false_callback
argument_list|,
name|eek
condition|?
name|NULL
else|:
name|message
argument_list|,
name|true_button
argument_list|,
name|false_button
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
if|if
condition|(
operator|!
name|eek
condition|)
return|return
name|query_box
operator|->
name|qbox
return|;
name|hbox
operator|=
name|gtk_hbox_new
argument_list|(
name|FALSE
argument_list|,
literal|10
argument_list|)
expr_stmt|;
name|gtk_container_set_border_width
argument_list|(
name|GTK_CONTAINER
argument_list|(
name|hbox
argument_list|)
argument_list|,
literal|10
argument_list|)
expr_stmt|;
name|gtk_container_add
argument_list|(
name|GTK_CONTAINER
argument_list|(
name|GTK_DIALOG
argument_list|(
name|query_box
operator|->
name|qbox
argument_list|)
operator|->
name|vbox
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
if|if
condition|(
operator|!
name|eek_pixmap
condition|)
block|{
name|GtkStyle
modifier|*
name|style
decl_stmt|;
name|gtk_widget_realize
argument_list|(
name|query_box
operator|->
name|qbox
argument_list|)
expr_stmt|;
name|style
operator|=
name|gtk_widget_get_style
argument_list|(
name|query_box
operator|->
name|qbox
argument_list|)
expr_stmt|;
name|eek_pixmap
operator|=
name|gdk_pixmap_create_from_xpm_d
argument_list|(
name|query_box
operator|->
name|qbox
operator|->
name|window
argument_list|,
operator|&
name|eek_mask
argument_list|,
operator|&
name|style
operator|->
name|bg
index|[
name|GTK_STATE_NORMAL
index|]
argument_list|,
name|eek_xpm
argument_list|)
expr_stmt|;
block|}
name|pixmap_widget
operator|=
name|gtk_pixmap_new
argument_list|(
name|eek_pixmap
argument_list|,
name|eek_mask
argument_list|)
expr_stmt|;
name|gtk_box_pack_start
argument_list|(
name|GTK_BOX
argument_list|(
name|hbox
argument_list|)
argument_list|,
name|pixmap_widget
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
name|pixmap_widget
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
return|return
name|query_box
operator|->
name|qbox
return|;
block|}
end_function

begin_function
specifier|static
name|QueryBox
modifier|*
DECL|function|query_box_disconnect (gpointer data)
name|query_box_disconnect
parameter_list|(
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
return|return
name|query_box
return|;
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
name|query_box_disconnect
argument_list|(
name|data
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
name|string
argument_list|,
name|query_box
operator|->
name|data
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
name|value
decl_stmt|;
name|query_box
operator|=
name|query_box_disconnect
argument_list|(
name|data
argument_list|)
expr_stmt|;
comment|/*  Get the spinbutton data  */
name|value
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
name|value
argument_list|,
name|query_box
operator|->
name|data
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
name|value
decl_stmt|;
name|query_box
operator|=
name|query_box_disconnect
argument_list|(
name|data
argument_list|)
expr_stmt|;
comment|/*  Get the spinbutton data  */
name|value
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
name|value
argument_list|,
name|query_box
operator|->
name|data
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
name|size
decl_stmt|;
name|GimpUnit
name|unit
decl_stmt|;
name|query_box
operator|=
name|query_box_disconnect
argument_list|(
name|data
argument_list|)
expr_stmt|;
comment|/*  Get the sizeentry data  */
name|size
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
name|unit
operator|=
name|gimp_size_entry_get_unit
argument_list|(
name|GIMP_SIZE_ENTRY
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
name|size
argument_list|,
name|unit
argument_list|,
name|query_box
operator|->
name|data
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
name|query_box_disconnect
argument_list|(
name|data
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
DECL|function|boolean_query_box_true_callback (GtkWidget * widget,gpointer data)
name|boolean_query_box_true_callback
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
name|query_box_disconnect
argument_list|(
name|data
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
name|TRUE
argument_list|,
name|query_box
operator|->
name|data
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
DECL|function|boolean_query_box_false_callback (GtkWidget * widget,gpointer data)
name|boolean_query_box_false_callback
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
name|query_box_disconnect
argument_list|(
name|data
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
name|FALSE
argument_list|,
name|query_box
operator|->
name|data
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

end_unit

