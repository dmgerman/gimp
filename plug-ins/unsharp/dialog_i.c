begin_unit|revision:0.9.5;language:C;cregit-version:0.0.1
begin_comment
comment|/* $Id$  * dialog_i.c -- functions for creating a GTK int slider/value input.  *  * Copyright (C) 1999 Winston Chang  *<wchang3@students.wisc.edu>  *<winston@steppe.com>  *  * This program is free software; you can redistribute it and/or modify  * it under the terms of the GNU General Public License as published by  * the Free Software Foundation; either version 2 of the License, or  * (at your option) any later version.  *  * This program is distributed in the hope that it will be useful,  * but WITHOUT ANY WARRANTY; without even the implied warranty of  * MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the  * GNU General Public License for more details.  *  * You should have received a copy of the GNU General Public License  * along with this program; if not, write to the Free Software  * Foundation, Inc., 59 Temple Place - Suite 330, Boston, MA 02111-1307, USA.  */
end_comment

begin_include
include|#
directive|include
file|<gtk/gtk.h>
end_include

begin_include
include|#
directive|include
file|<stdlib.h>
end_include

begin_include
include|#
directive|include
file|<stdio.h>
end_include

begin_include
include|#
directive|include
file|<string.h>
end_include

begin_include
include|#
directive|include
file|"dialog_i.h"
end_include

begin_comment
comment|/*  * 'dialog_create_value_i()' - Create an gint value control...  */
end_comment

begin_function
name|void
DECL|function|dialog_create_value_i (char * title,GtkTable * table,int row,gint * value,gint increment,int left,int right)
name|dialog_create_value_i
parameter_list|(
name|char
modifier|*
name|title
parameter_list|,
comment|/* Label for control */
name|GtkTable
modifier|*
name|table
parameter_list|,
comment|/* Table container to use */
name|int
name|row
parameter_list|,
comment|/* Row # for container */
name|gint
modifier|*
name|value
parameter_list|,
comment|/* Value holder */
name|gint
name|increment
parameter_list|,
comment|/* Size of mouse-click and                                             keyboard increment */
name|int
name|left
parameter_list|,
comment|/* Minimum value for slider */
name|int
name|right
parameter_list|)
comment|/* Maximum value for slider */
block|{
name|GtkWidget
modifier|*
name|label
decl_stmt|;
comment|/* Control label */
name|GtkWidget
modifier|*
name|scale
decl_stmt|;
comment|/* Scale widget */
name|GtkWidget
modifier|*
name|entry
decl_stmt|;
comment|/* Text widget */
name|GtkObject
modifier|*
name|scale_data
decl_stmt|;
comment|/* Scale data */
name|char
name|buf
index|[
literal|256
index|]
decl_stmt|;
comment|/* String buffer */
comment|/* Create label... */
name|label
operator|=
name|gtk_label_new
argument_list|(
name|title
argument_list|)
expr_stmt|;
name|gtk_misc_set_alignment
argument_list|(
name|GTK_MISC
argument_list|(
name|label
argument_list|)
argument_list|,
literal|0.0
argument_list|,
literal|1.0
argument_list|)
expr_stmt|;
name|gtk_table_attach
argument_list|(
name|table
argument_list|,
name|label
argument_list|,
literal|0
argument_list|,
literal|1
argument_list|,
name|row
argument_list|,
name|row
operator|+
literal|1
argument_list|,
name|GTK_FILL
argument_list|,
name|GTK_FILL
argument_list|,
literal|4
argument_list|,
literal|0
argument_list|)
expr_stmt|;
name|gtk_widget_show
argument_list|(
name|label
argument_list|)
expr_stmt|;
comment|/* 	* Scale... 	*/
comment|/* the "right+increment" is necessary to make it stop on 5.0 instead      of 4.9.   I think this is a shortcoming of GTK's adjustments */
name|scale_data
operator|=
name|gtk_adjustment_new
argument_list|(
operator|(
name|gfloat
operator|)
operator|*
name|value
argument_list|,
name|left
argument_list|,
name|right
operator|+
name|increment
argument_list|,
name|increment
argument_list|,
name|increment
argument_list|,
name|increment
argument_list|)
expr_stmt|;
name|gtk_signal_connect
argument_list|(
name|GTK_OBJECT
argument_list|(
name|scale_data
argument_list|)
argument_list|,
literal|"value_changed"
argument_list|,
operator|(
name|GtkSignalFunc
operator|)
name|dialog_iscale_update
argument_list|,
name|value
argument_list|)
expr_stmt|;
name|scale
operator|=
name|gtk_hscale_new
argument_list|(
name|GTK_ADJUSTMENT
argument_list|(
name|scale_data
argument_list|)
argument_list|)
expr_stmt|;
name|gtk_scale_set_digits
argument_list|(
name|GTK_SCALE
argument_list|(
name|scale
argument_list|)
argument_list|,
literal|0
argument_list|)
expr_stmt|;
name|gtk_widget_set_usize
argument_list|(
name|scale
argument_list|,
name|SCALE_WIDTH
argument_list|,
literal|0
argument_list|)
expr_stmt|;
name|gtk_table_attach
argument_list|(
name|table
argument_list|,
name|scale
argument_list|,
literal|1
argument_list|,
literal|2
argument_list|,
name|row
argument_list|,
name|row
operator|+
literal|1
argument_list|,
name|GTK_EXPAND
operator||
name|GTK_FILL
argument_list|,
name|GTK_FILL
argument_list|,
literal|0
argument_list|,
literal|0
argument_list|)
expr_stmt|;
name|gtk_scale_set_draw_value
argument_list|(
name|GTK_SCALE
argument_list|(
name|scale
argument_list|)
argument_list|,
name|FALSE
argument_list|)
expr_stmt|;
name|gtk_range_set_update_policy
argument_list|(
name|GTK_RANGE
argument_list|(
name|scale
argument_list|)
argument_list|,
name|GTK_UPDATE_CONTINUOUS
argument_list|)
expr_stmt|;
name|gtk_widget_show
argument_list|(
name|scale
argument_list|)
expr_stmt|;
comment|/* 	* Text entry... 	*/
name|entry
operator|=
name|gtk_entry_new
argument_list|()
expr_stmt|;
name|gtk_object_set_user_data
argument_list|(
name|GTK_OBJECT
argument_list|(
name|entry
argument_list|)
argument_list|,
name|scale_data
argument_list|)
expr_stmt|;
name|gtk_object_set_user_data
argument_list|(
name|scale_data
argument_list|,
name|entry
argument_list|)
expr_stmt|;
name|gtk_widget_set_usize
argument_list|(
name|entry
argument_list|,
name|ENTRY_WIDTH
argument_list|,
literal|0
argument_list|)
expr_stmt|;
name|sprintf
argument_list|(
name|buf
argument_list|,
literal|"%d"
argument_list|,
operator|*
name|value
argument_list|)
expr_stmt|;
name|gtk_entry_set_text
argument_list|(
name|GTK_ENTRY
argument_list|(
name|entry
argument_list|)
argument_list|,
name|buf
argument_list|)
expr_stmt|;
name|gtk_signal_connect
argument_list|(
name|GTK_OBJECT
argument_list|(
name|entry
argument_list|)
argument_list|,
literal|"changed"
argument_list|,
operator|(
name|GtkSignalFunc
operator|)
name|dialog_ientry_update
argument_list|,
name|value
argument_list|)
expr_stmt|;
name|gtk_table_attach
argument_list|(
name|GTK_TABLE
argument_list|(
name|table
argument_list|)
argument_list|,
name|entry
argument_list|,
literal|2
argument_list|,
literal|3
argument_list|,
name|row
argument_list|,
name|row
operator|+
literal|1
argument_list|,
name|GTK_FILL
argument_list|,
name|GTK_FILL
argument_list|,
literal|4
argument_list|,
literal|0
argument_list|)
expr_stmt|;
name|gtk_widget_show
argument_list|(
name|entry
argument_list|)
expr_stmt|;
block|}
end_function

begin_comment
comment|/*  * 'dialog_iscale_update()' - Update the value field using the scale.  */
end_comment

begin_function
name|void
DECL|function|dialog_iscale_update (GtkAdjustment * adjustment,gint * value)
name|dialog_iscale_update
parameter_list|(
name|GtkAdjustment
modifier|*
name|adjustment
parameter_list|,
comment|/* I - New value */
name|gint
modifier|*
name|value
parameter_list|)
comment|/* I - Current value */
block|{
name|GtkWidget
modifier|*
name|entry
decl_stmt|;
comment|/* Text entry widget */
name|char
name|buf
index|[
literal|256
index|]
decl_stmt|;
comment|/* Text buffer */
if|if
condition|(
operator|*
name|value
operator|!=
operator|(
name|int
operator|)
name|adjustment
operator|->
name|value
condition|)
block|{
operator|*
name|value
operator|=
operator|(
name|int
operator|)
name|adjustment
operator|->
name|value
expr_stmt|;
name|sprintf
argument_list|(
name|buf
argument_list|,
literal|"%d"
argument_list|,
operator|*
name|value
argument_list|)
expr_stmt|;
name|entry
operator|=
name|gtk_object_get_user_data
argument_list|(
name|GTK_OBJECT
argument_list|(
name|adjustment
argument_list|)
argument_list|)
expr_stmt|;
comment|/* assign the text value to the entry */
name|gtk_signal_handler_block_by_data
argument_list|(
name|GTK_OBJECT
argument_list|(
name|entry
argument_list|)
argument_list|,
name|value
argument_list|)
expr_stmt|;
name|gtk_entry_set_text
argument_list|(
name|GTK_ENTRY
argument_list|(
name|entry
argument_list|)
argument_list|,
name|buf
argument_list|)
expr_stmt|;
name|gtk_signal_handler_unblock_by_data
argument_list|(
name|GTK_OBJECT
argument_list|(
name|entry
argument_list|)
argument_list|,
name|value
argument_list|)
expr_stmt|;
comment|/* assign the rounded value back the adjustment */
name|adjustment
operator|->
name|value
operator|=
operator|(
name|gdouble
operator|)
operator|*
name|value
expr_stmt|;
block|}
block|}
end_function

begin_comment
comment|/*  * 'dialog_ientry_update()' - Update the value field using the text entry.  */
end_comment

begin_function
name|void
DECL|function|dialog_ientry_update (GtkWidget * widget,gint * value)
name|dialog_ientry_update
parameter_list|(
name|GtkWidget
modifier|*
name|widget
parameter_list|,
comment|/* I - Entry widget */
name|gint
modifier|*
name|value
parameter_list|)
comment|/* I - Current value */
block|{
name|GtkAdjustment
modifier|*
name|adjustment
decl_stmt|;
name|gint
name|new_value
decl_stmt|;
name|gint
name|shift
decl_stmt|;
name|gchar
modifier|*
name|textvalue
decl_stmt|;
name|gchar
name|newtextvalue
index|[
name|MAX_ENTRY_LENGTH
operator|+
literal|1
index|]
decl_stmt|;
name|gint
name|oldtextlength
decl_stmt|;
name|gint
name|i
decl_stmt|;
name|textvalue
operator|=
name|gtk_entry_get_text
argument_list|(
name|GTK_ENTRY
argument_list|(
name|widget
argument_list|)
argument_list|)
expr_stmt|;
name|strncpy
argument_list|(
name|newtextvalue
argument_list|,
name|textvalue
argument_list|,
name|MAX_ENTRY_LENGTH
argument_list|)
expr_stmt|;
comment|/* clean up new value so that it only has one digit after decimal 	   and no weird chars */
name|newtextvalue
index|[
name|MAX_ENTRY_LENGTH
index|]
operator|=
literal|'\0'
expr_stmt|;
name|oldtextlength
operator|=
name|strlen
argument_list|(
name|newtextvalue
argument_list|)
expr_stmt|;
name|fprintf
argument_list|(
name|stderr
argument_list|,
literal|"%d\n"
argument_list|,
operator|*
name|value
argument_list|)
expr_stmt|;
comment|/* this stuff cleans up non-numeric chars */
name|shift
operator|=
literal|0
expr_stmt|;
for|for
control|(
name|i
operator|=
literal|0
init|;
name|i
operator|+
name|shift
operator|<
name|oldtextlength
condition|;
name|i
operator|++
control|)
block|{
if|if
condition|(
operator|!
operator|(
name|newtextvalue
index|[
name|i
index|]
operator|>=
literal|'0'
operator|&&
name|newtextvalue
index|[
name|i
index|]
operator|<=
literal|'9'
operator|)
condition|)
name|shift
operator|++
expr_stmt|;
comment|/* ignore non-numeric chars */
comment|/* copy shifted value back, making sure we don't run off end */
if|if
condition|(
name|i
operator|+
name|shift
operator|>=
name|MAX_ENTRY_LENGTH
condition|)
name|newtextvalue
index|[
name|i
index|]
operator|=
literal|'\0'
expr_stmt|;
else|else
name|newtextvalue
index|[
name|i
index|]
operator|=
name|newtextvalue
index|[
name|i
operator|+
name|shift
index|]
expr_stmt|;
block|}
name|newtextvalue
index|[
name|i
index|]
operator|=
literal|'\0'
expr_stmt|;
comment|/* write the cleaned-up value into the entry box */
comment|/* block the signal handler so we don't go into an infinite recursion */
name|gtk_signal_handler_block_by_data
argument_list|(
name|GTK_OBJECT
argument_list|(
name|widget
argument_list|)
argument_list|,
name|value
argument_list|)
expr_stmt|;
comment|/* update the entry text */
name|gtk_entry_set_text
argument_list|(
name|GTK_ENTRY
argument_list|(
name|widget
argument_list|)
argument_list|,
name|newtextvalue
argument_list|)
expr_stmt|;
comment|/* gtk_entry_set_position( GTK_ENTRY(widget), i); */
comment|/* doesn't seem to work */
comment|/* unblock signal handler */
name|gtk_signal_handler_unblock_by_data
argument_list|(
name|GTK_OBJECT
argument_list|(
name|widget
argument_list|)
argument_list|,
name|value
argument_list|)
expr_stmt|;
comment|/* set the adjustment thingy */
name|new_value
operator|=
name|atoi
argument_list|(
name|newtextvalue
argument_list|)
expr_stmt|;
comment|/* set the new value */
if|if
condition|(
operator|*
name|value
operator|!=
name|new_value
condition|)
block|{
name|adjustment
operator|=
name|gtk_object_get_user_data
argument_list|(
name|GTK_OBJECT
argument_list|(
name|widget
argument_list|)
argument_list|)
expr_stmt|;
if|if
condition|(
operator|(
name|new_value
operator|>=
name|adjustment
operator|->
name|lower
operator|)
operator|&&
operator|(
name|new_value
operator|<=
name|adjustment
operator|->
name|upper
operator|)
condition|)
block|{
operator|*
name|value
operator|=
name|new_value
expr_stmt|;
name|adjustment
operator|->
name|value
operator|=
name|new_value
expr_stmt|;
name|gtk_signal_emit_by_name
argument_list|(
name|GTK_OBJECT
argument_list|(
name|adjustment
argument_list|)
argument_list|,
literal|"value_changed"
argument_list|)
expr_stmt|;
block|}
block|}
block|}
end_function

end_unit

