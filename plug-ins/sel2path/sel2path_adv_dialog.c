begin_unit|revision:0.9.5;language:C;cregit-version:0.0.1
begin_comment
comment|/*  * Copyright (C) 1995 Spencer Kimball and Peter Mattis  *  * This is a plug-in for the GIMP.  *  * Plugin to convert a selection to a path.  *  * Copyright (C) 1999 Andy Thomas  alt@gimp.org  *  * This program is free software; you can redistribute it and/or modify  * it under the terms of the GNU General Public License as published by  * the Free Software Foundation; either version 2 of the License, or  * (at your option) any later version.  *  * This program is distributed in the hope that it will be useful,  * but WITHOUT ANY WARRANTY; without even the implied warranty of  * MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the  * GNU General Public License for more details.  *  * You should have received a copy of the GNU General Public License  * along with this program; if not, write to the Free Software  * Foundation, Inc., 59 Temple Place - Suite 330, Boston, MA 02111-1307, USA.  *  */
end_comment

begin_comment
comment|/* Change log:-  * 0.1 First version.  */
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
file|<stdlib.h>
end_include

begin_include
include|#
directive|include
file|<types.h>
end_include

begin_include
include|#
directive|include
file|<libgimp/gimp.h>
end_include

begin_include
include|#
directive|include
file|<libgimp/gimpui.h>
end_include

begin_define
DECL|macro|SCALE_WIDTH
define|#
directive|define
name|SCALE_WIDTH
value|100
end_define

begin_define
DECL|macro|SCALE_DIGITS
define|#
directive|define
name|SCALE_DIGITS
value|8
end_define

begin_decl_stmt
DECL|variable|adjust_widgets
specifier|static
name|GSList
modifier|*
name|adjust_widgets
init|=
name|NULL
decl_stmt|;
end_decl_stmt

begin_comment
comment|/* Reset to recommended defaults */
end_comment

begin_function
name|void
DECL|function|reset_adv_dialog (void)
name|reset_adv_dialog
parameter_list|(
name|void
parameter_list|)
block|{
name|GSList
modifier|*
name|list
decl_stmt|;
name|GtkObject
modifier|*
name|widget
decl_stmt|;
name|gdouble
modifier|*
name|value
decl_stmt|;
for|for
control|(
name|list
operator|=
name|adjust_widgets
init|;
name|list
condition|;
name|list
operator|=
name|g_slist_next
argument_list|(
name|list
argument_list|)
control|)
block|{
name|widget
operator|=
name|GTK_OBJECT
argument_list|(
name|list
operator|->
name|data
argument_list|)
expr_stmt|;
name|value
operator|=
operator|(
name|gdouble
operator|*
operator|)
name|g_object_get_data
argument_list|(
name|G_OBJECT
argument_list|(
name|widget
argument_list|)
argument_list|,
literal|"default_value"
argument_list|)
expr_stmt|;
if|if
condition|(
name|GTK_IS_ADJUSTMENT
argument_list|(
name|widget
argument_list|)
condition|)
block|{
name|gtk_adjustment_set_value
argument_list|(
name|GTK_ADJUSTMENT
argument_list|(
name|widget
argument_list|)
argument_list|,
operator|*
name|value
argument_list|)
expr_stmt|;
block|}
elseif|else
if|if
condition|(
name|GTK_IS_TOGGLE_BUTTON
argument_list|(
name|widget
argument_list|)
condition|)
block|{
name|gtk_toggle_button_set_active
argument_list|(
name|GTK_TOGGLE_BUTTON
argument_list|(
name|widget
argument_list|)
argument_list|,
call|(
name|gboolean
call|)
argument_list|(
operator|*
name|value
argument_list|)
argument_list|)
expr_stmt|;
block|}
else|else
name|g_warning
argument_list|(
literal|"Internal widget list error"
argument_list|)
expr_stmt|;
block|}
block|}
end_function

begin_function
name|gpointer
DECL|function|def_val (gdouble default_value)
name|def_val
parameter_list|(
name|gdouble
name|default_value
parameter_list|)
block|{
name|gdouble
modifier|*
name|value
init|=
name|g_new0
argument_list|(
name|gdouble
argument_list|,
literal|1
argument_list|)
decl_stmt|;
operator|*
name|value
operator|=
name|default_value
expr_stmt|;
return|return
operator|(
name|value
operator|)
return|;
block|}
end_function

begin_function
name|GtkWidget
modifier|*
DECL|function|dialog_create_selection_area (SELVALS * sels)
name|dialog_create_selection_area
parameter_list|(
name|SELVALS
modifier|*
name|sels
parameter_list|)
block|{
name|GtkWidget
modifier|*
name|table
decl_stmt|;
name|GtkWidget
modifier|*
name|check
decl_stmt|;
name|GtkObject
modifier|*
name|adj
decl_stmt|;
name|gint
name|row
decl_stmt|;
name|table
operator|=
name|gtk_table_new
argument_list|(
literal|20
argument_list|,
literal|3
argument_list|,
name|FALSE
argument_list|)
expr_stmt|;
name|gtk_table_set_row_spacings
argument_list|(
name|GTK_TABLE
argument_list|(
name|table
argument_list|)
argument_list|,
literal|2
argument_list|)
expr_stmt|;
name|gtk_table_set_col_spacings
argument_list|(
name|GTK_TABLE
argument_list|(
name|table
argument_list|)
argument_list|,
literal|2
argument_list|)
expr_stmt|;
name|row
operator|=
literal|0
expr_stmt|;
name|adj
operator|=
name|gimp_scale_entry_new
argument_list|(
name|GTK_TABLE
argument_list|(
name|table
argument_list|)
argument_list|,
literal|0
argument_list|,
name|row
operator|++
argument_list|,
literal|"Align Threshold:"
argument_list|,
name|SCALE_WIDTH
argument_list|,
name|SCALE_DIGITS
argument_list|,
name|sels
operator|->
name|align_threshold
argument_list|,
literal|0.2
argument_list|,
literal|2.0
argument_list|,
literal|0.1
argument_list|,
literal|0.1
argument_list|,
literal|2
argument_list|,
name|TRUE
argument_list|,
literal|0
argument_list|,
literal|0
argument_list|,
literal|"If two endpoints are closer than this,"
literal|"they are made to be equal."
argument_list|,
name|NULL
argument_list|)
expr_stmt|;
name|g_signal_connect
argument_list|(
name|adj
argument_list|,
literal|"value_changed"
argument_list|,
name|G_CALLBACK
argument_list|(
name|gimp_double_adjustment_update
argument_list|)
argument_list|,
operator|&
name|sels
operator|->
name|align_threshold
argument_list|)
expr_stmt|;
name|adjust_widgets
operator|=
name|g_slist_append
argument_list|(
name|adjust_widgets
argument_list|,
name|adj
argument_list|)
expr_stmt|;
name|g_object_set_data
argument_list|(
name|G_OBJECT
argument_list|(
name|adj
argument_list|)
argument_list|,
literal|"default_value"
argument_list|,
name|def_val
argument_list|(
literal|0.5
argument_list|)
argument_list|)
expr_stmt|;
name|adj
operator|=
name|gimp_scale_entry_new
argument_list|(
name|GTK_TABLE
argument_list|(
name|table
argument_list|)
argument_list|,
literal|0
argument_list|,
name|row
operator|++
argument_list|,
literal|"Corner Always Threshold:"
argument_list|,
name|SCALE_WIDTH
argument_list|,
name|SCALE_DIGITS
argument_list|,
name|sels
operator|->
name|corner_always_threshold
argument_list|,
literal|30
argument_list|,
literal|180
argument_list|,
literal|1
argument_list|,
literal|1
argument_list|,
literal|2
argument_list|,
name|TRUE
argument_list|,
literal|0
argument_list|,
literal|0
argument_list|,
literal|"If the angle defined by a point and its predecessors "
literal|"and successors is smaller than this, it's a corner, "
literal|"even if it's within `corner_surround' pixels of a "
literal|"point with a smaller angle."
argument_list|,
name|NULL
argument_list|)
expr_stmt|;
name|g_signal_connect
argument_list|(
name|adj
argument_list|,
literal|"value_changed"
argument_list|,
name|G_CALLBACK
argument_list|(
name|gimp_double_adjustment_update
argument_list|)
argument_list|,
operator|&
name|sels
operator|->
name|corner_always_threshold
argument_list|)
expr_stmt|;
name|adjust_widgets
operator|=
name|g_slist_append
argument_list|(
name|adjust_widgets
argument_list|,
name|adj
argument_list|)
expr_stmt|;
name|g_object_set_data
argument_list|(
name|G_OBJECT
argument_list|(
name|adj
argument_list|)
argument_list|,
literal|"default_value"
argument_list|,
name|def_val
argument_list|(
literal|60.0
argument_list|)
argument_list|)
expr_stmt|;
name|adj
operator|=
name|gimp_scale_entry_new
argument_list|(
name|GTK_TABLE
argument_list|(
name|table
argument_list|)
argument_list|,
literal|0
argument_list|,
name|row
operator|++
argument_list|,
literal|"Corner Surround:"
argument_list|,
name|SCALE_WIDTH
argument_list|,
name|SCALE_DIGITS
argument_list|,
name|sels
operator|->
name|corner_surround
argument_list|,
literal|3
argument_list|,
literal|8
argument_list|,
literal|1
argument_list|,
literal|1
argument_list|,
literal|0
argument_list|,
name|TRUE
argument_list|,
literal|0
argument_list|,
literal|0
argument_list|,
literal|"Number of points to consider when determining if a "
literal|"point is a corner or not."
argument_list|,
name|NULL
argument_list|)
expr_stmt|;
name|g_signal_connect
argument_list|(
name|adj
argument_list|,
literal|"value_changed"
argument_list|,
name|G_CALLBACK
argument_list|(
name|gimp_double_adjustment_update
argument_list|)
argument_list|,
operator|&
name|sels
operator|->
name|corner_surround
argument_list|)
expr_stmt|;
name|adjust_widgets
operator|=
name|g_slist_append
argument_list|(
name|adjust_widgets
argument_list|,
name|adj
argument_list|)
expr_stmt|;
name|g_object_set_data
argument_list|(
name|G_OBJECT
argument_list|(
name|adj
argument_list|)
argument_list|,
literal|"default_value"
argument_list|,
name|def_val
argument_list|(
literal|4.0
argument_list|)
argument_list|)
expr_stmt|;
name|adj
operator|=
name|gimp_scale_entry_new
argument_list|(
name|GTK_TABLE
argument_list|(
name|table
argument_list|)
argument_list|,
literal|0
argument_list|,
name|row
operator|++
argument_list|,
literal|"Corner Threshold:"
argument_list|,
name|SCALE_WIDTH
argument_list|,
name|SCALE_DIGITS
argument_list|,
name|sels
operator|->
name|corner_threshold
argument_list|,
literal|0
argument_list|,
literal|180
argument_list|,
literal|1
argument_list|,
literal|1
argument_list|,
literal|2
argument_list|,
name|TRUE
argument_list|,
literal|0
argument_list|,
literal|0
argument_list|,
literal|"If a point, its predecessors, and its successors "
literal|"define an angle smaller than this, it's a corner."
argument_list|,
name|NULL
argument_list|)
expr_stmt|;
name|g_signal_connect
argument_list|(
name|adj
argument_list|,
literal|"value_changed"
argument_list|,
name|G_CALLBACK
argument_list|(
name|gimp_double_adjustment_update
argument_list|)
argument_list|,
operator|&
name|sels
operator|->
name|corner_threshold
argument_list|)
expr_stmt|;
name|adjust_widgets
operator|=
name|g_slist_append
argument_list|(
name|adjust_widgets
argument_list|,
name|adj
argument_list|)
expr_stmt|;
name|g_object_set_data
argument_list|(
name|G_OBJECT
argument_list|(
name|adj
argument_list|)
argument_list|,
literal|"default_value"
argument_list|,
name|def_val
argument_list|(
literal|100.0
argument_list|)
argument_list|)
expr_stmt|;
name|adj
operator|=
name|gimp_scale_entry_new
argument_list|(
name|GTK_TABLE
argument_list|(
name|table
argument_list|)
argument_list|,
literal|0
argument_list|,
name|row
operator|++
argument_list|,
literal|"Error Threshold:"
argument_list|,
name|SCALE_WIDTH
argument_list|,
name|SCALE_DIGITS
argument_list|,
name|sels
operator|->
name|error_threshold
argument_list|,
literal|0.2
argument_list|,
literal|10
argument_list|,
literal|0.1
argument_list|,
literal|0.1
argument_list|,
literal|2
argument_list|,
name|TRUE
argument_list|,
literal|0
argument_list|,
literal|0
argument_list|,
literal|"Amount of error at which a fitted spline is "
literal|"unacceptable.  If any pixel is further away "
literal|"than this from the fitted curve, we try again."
argument_list|,
name|NULL
argument_list|)
expr_stmt|;
name|g_signal_connect
argument_list|(
name|adj
argument_list|,
literal|"value_changed"
argument_list|,
name|G_CALLBACK
argument_list|(
name|gimp_double_adjustment_update
argument_list|)
argument_list|,
operator|&
name|sels
operator|->
name|error_threshold
argument_list|)
expr_stmt|;
name|adjust_widgets
operator|=
name|g_slist_append
argument_list|(
name|adjust_widgets
argument_list|,
name|adj
argument_list|)
expr_stmt|;
name|g_object_set_data
argument_list|(
name|G_OBJECT
argument_list|(
name|adj
argument_list|)
argument_list|,
literal|"default_value"
argument_list|,
name|def_val
argument_list|(
literal|0.40
argument_list|)
argument_list|)
expr_stmt|;
name|adj
operator|=
name|gimp_scale_entry_new
argument_list|(
name|GTK_TABLE
argument_list|(
name|table
argument_list|)
argument_list|,
literal|0
argument_list|,
name|row
operator|++
argument_list|,
literal|"Filter Alternative Surround:"
argument_list|,
name|SCALE_WIDTH
argument_list|,
name|SCALE_DIGITS
argument_list|,
name|sels
operator|->
name|filter_alternative_surround
argument_list|,
literal|1
argument_list|,
literal|10
argument_list|,
literal|1
argument_list|,
literal|1
argument_list|,
literal|0
argument_list|,
name|TRUE
argument_list|,
literal|0
argument_list|,
literal|0
argument_list|,
literal|"A second number of adjacent points to consider "
literal|"when filtering."
argument_list|,
name|NULL
argument_list|)
expr_stmt|;
name|g_signal_connect
argument_list|(
name|adj
argument_list|,
literal|"value_changed"
argument_list|,
name|G_CALLBACK
argument_list|(
name|gimp_double_adjustment_update
argument_list|)
argument_list|,
operator|&
name|sels
operator|->
name|filter_alternative_surround
argument_list|)
expr_stmt|;
name|adjust_widgets
operator|=
name|g_slist_append
argument_list|(
name|adjust_widgets
argument_list|,
name|adj
argument_list|)
expr_stmt|;
name|g_object_set_data
argument_list|(
name|G_OBJECT
argument_list|(
name|adj
argument_list|)
argument_list|,
literal|"default_value"
argument_list|,
name|def_val
argument_list|(
literal|1.0
argument_list|)
argument_list|)
expr_stmt|;
name|adj
operator|=
name|gimp_scale_entry_new
argument_list|(
name|GTK_TABLE
argument_list|(
name|table
argument_list|)
argument_list|,
literal|0
argument_list|,
name|row
operator|++
argument_list|,
literal|"Filter Epsilon:"
argument_list|,
name|SCALE_WIDTH
argument_list|,
name|SCALE_DIGITS
argument_list|,
name|sels
operator|->
name|filter_epsilon
argument_list|,
literal|5
argument_list|,
literal|40
argument_list|,
literal|1
argument_list|,
literal|1
argument_list|,
literal|2
argument_list|,
name|TRUE
argument_list|,
literal|0
argument_list|,
literal|0
argument_list|,
literal|"If the angles between the vectors produced by "
literal|"filter_surround and filter_alternative_surround "
literal|"points differ by more than this, use the one from "
literal|"filter_alternative_surround."
argument_list|,
name|NULL
argument_list|)
expr_stmt|;
name|g_signal_connect
argument_list|(
name|adj
argument_list|,
literal|"value_changed"
argument_list|,
name|G_CALLBACK
argument_list|(
name|gimp_double_adjustment_update
argument_list|)
argument_list|,
operator|&
name|sels
operator|->
name|filter_epsilon
argument_list|)
expr_stmt|;
name|adjust_widgets
operator|=
name|g_slist_append
argument_list|(
name|adjust_widgets
argument_list|,
name|adj
argument_list|)
expr_stmt|;
name|g_object_set_data
argument_list|(
name|G_OBJECT
argument_list|(
name|adj
argument_list|)
argument_list|,
literal|"default_value"
argument_list|,
name|def_val
argument_list|(
literal|10.0
argument_list|)
argument_list|)
expr_stmt|;
name|adj
operator|=
name|gimp_scale_entry_new
argument_list|(
name|GTK_TABLE
argument_list|(
name|table
argument_list|)
argument_list|,
literal|0
argument_list|,
name|row
operator|++
argument_list|,
literal|"Filter Iteration Count:"
argument_list|,
name|SCALE_WIDTH
argument_list|,
name|SCALE_DIGITS
argument_list|,
name|sels
operator|->
name|filter_iteration_count
argument_list|,
literal|4
argument_list|,
literal|70
argument_list|,
literal|1
argument_list|,
literal|1
argument_list|,
literal|0
argument_list|,
name|TRUE
argument_list|,
literal|0
argument_list|,
literal|0
argument_list|,
literal|"Number of times to smooth original data points.  "
literal|"Increasing this number dramatically --- to 50 or "
literal|"so --- can produce vastly better results.  But if "
literal|"any points that ``should'' be corners aren't found, "
literal|"the curve goes to hell around that point."
argument_list|,
name|NULL
argument_list|)
expr_stmt|;
name|g_signal_connect
argument_list|(
name|adj
argument_list|,
literal|"value_changed"
argument_list|,
name|G_CALLBACK
argument_list|(
name|gimp_double_adjustment_update
argument_list|)
argument_list|,
operator|&
name|sels
operator|->
name|filter_iteration_count
argument_list|)
expr_stmt|;
name|adjust_widgets
operator|=
name|g_slist_append
argument_list|(
name|adjust_widgets
argument_list|,
name|adj
argument_list|)
expr_stmt|;
name|g_object_set_data
argument_list|(
name|G_OBJECT
argument_list|(
name|adj
argument_list|)
argument_list|,
literal|"default_value"
argument_list|,
name|def_val
argument_list|(
literal|4.0
argument_list|)
argument_list|)
expr_stmt|;
name|adj
operator|=
name|gimp_scale_entry_new
argument_list|(
name|GTK_TABLE
argument_list|(
name|table
argument_list|)
argument_list|,
literal|0
argument_list|,
name|row
operator|++
argument_list|,
literal|"Filter Percent:"
argument_list|,
name|SCALE_WIDTH
argument_list|,
name|SCALE_DIGITS
argument_list|,
name|sels
operator|->
name|filter_percent
argument_list|,
literal|0
argument_list|,
literal|1
argument_list|,
literal|0.05
argument_list|,
literal|0.01
argument_list|,
literal|2
argument_list|,
name|TRUE
argument_list|,
literal|0
argument_list|,
literal|0
argument_list|,
literal|"To produce the new point, use the old point plus "
literal|"this times the neighbors."
argument_list|,
name|NULL
argument_list|)
expr_stmt|;
name|g_signal_connect
argument_list|(
name|adj
argument_list|,
literal|"value_changed"
argument_list|,
name|G_CALLBACK
argument_list|(
name|gimp_double_adjustment_update
argument_list|)
argument_list|,
operator|&
name|sels
operator|->
name|filter_percent
argument_list|)
expr_stmt|;
name|adjust_widgets
operator|=
name|g_slist_append
argument_list|(
name|adjust_widgets
argument_list|,
name|adj
argument_list|)
expr_stmt|;
name|g_object_set_data
argument_list|(
name|G_OBJECT
argument_list|(
name|adj
argument_list|)
argument_list|,
literal|"default_value"
argument_list|,
name|def_val
argument_list|(
literal|0.33
argument_list|)
argument_list|)
expr_stmt|;
name|adj
operator|=
name|gimp_scale_entry_new
argument_list|(
name|GTK_TABLE
argument_list|(
name|table
argument_list|)
argument_list|,
literal|0
argument_list|,
name|row
operator|++
argument_list|,
literal|"Filter Secondary Surround:"
argument_list|,
name|SCALE_WIDTH
argument_list|,
name|SCALE_DIGITS
argument_list|,
name|sels
operator|->
name|filter_secondary_surround
argument_list|,
literal|3
argument_list|,
literal|10
argument_list|,
literal|1
argument_list|,
literal|1
argument_list|,
literal|0
argument_list|,
name|TRUE
argument_list|,
literal|0
argument_list|,
literal|0
argument_list|,
literal|"Number of adjacent points to consider if "
literal|"`filter_surround' points defines a straight line."
argument_list|,
name|NULL
argument_list|)
expr_stmt|;
name|g_signal_connect
argument_list|(
name|adj
argument_list|,
literal|"value_changed"
argument_list|,
name|G_CALLBACK
argument_list|(
name|gimp_double_adjustment_update
argument_list|)
argument_list|,
operator|&
name|sels
operator|->
name|filter_secondary_surround
argument_list|)
expr_stmt|;
name|adjust_widgets
operator|=
name|g_slist_append
argument_list|(
name|adjust_widgets
argument_list|,
name|adj
argument_list|)
expr_stmt|;
name|g_object_set_data
argument_list|(
name|G_OBJECT
argument_list|(
name|adj
argument_list|)
argument_list|,
literal|"default_value"
argument_list|,
name|def_val
argument_list|(
literal|3.0
argument_list|)
argument_list|)
expr_stmt|;
name|adj
operator|=
name|gimp_scale_entry_new
argument_list|(
name|GTK_TABLE
argument_list|(
name|table
argument_list|)
argument_list|,
literal|0
argument_list|,
name|row
operator|++
argument_list|,
literal|"Filter Surround:"
argument_list|,
name|SCALE_WIDTH
argument_list|,
name|SCALE_DIGITS
argument_list|,
name|sels
operator|->
name|filter_surround
argument_list|,
literal|2
argument_list|,
literal|10
argument_list|,
literal|1
argument_list|,
literal|1
argument_list|,
literal|0
argument_list|,
name|TRUE
argument_list|,
literal|0
argument_list|,
literal|0
argument_list|,
literal|"Number of adjacent points to consider when filtering."
argument_list|,
name|NULL
argument_list|)
expr_stmt|;
name|g_signal_connect
argument_list|(
name|adj
argument_list|,
literal|"value_changed"
argument_list|,
name|G_CALLBACK
argument_list|(
name|gimp_double_adjustment_update
argument_list|)
argument_list|,
operator|&
name|sels
operator|->
name|filter_surround
argument_list|)
expr_stmt|;
name|adjust_widgets
operator|=
name|g_slist_append
argument_list|(
name|adjust_widgets
argument_list|,
name|adj
argument_list|)
expr_stmt|;
name|g_object_set_data
argument_list|(
name|G_OBJECT
argument_list|(
name|adj
argument_list|)
argument_list|,
literal|"default_value"
argument_list|,
name|def_val
argument_list|(
literal|2.0
argument_list|)
argument_list|)
expr_stmt|;
name|check
operator|=
name|gtk_check_button_new_with_label
argument_list|(
literal|"Keep Knees"
argument_list|)
expr_stmt|;
name|gtk_toggle_button_set_active
argument_list|(
name|GTK_TOGGLE_BUTTON
argument_list|(
name|check
argument_list|)
argument_list|,
name|sels
operator|->
name|keep_knees
argument_list|)
expr_stmt|;
name|gtk_table_attach
argument_list|(
name|GTK_TABLE
argument_list|(
name|table
argument_list|)
argument_list|,
name|check
argument_list|,
literal|1
argument_list|,
literal|3
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
name|GTK_EXPAND
operator||
name|GTK_FILL
argument_list|,
literal|0
argument_list|,
literal|0
argument_list|)
expr_stmt|;
name|gimp_help_set_help_data
argument_list|(
name|GTK_WIDGET
argument_list|(
name|check
argument_list|)
argument_list|,
literal|"Says whether or not to remove ``knee'' "
literal|"points after finding the outline."
argument_list|,
name|NULL
argument_list|)
expr_stmt|;
name|g_signal_connect
argument_list|(
name|check
argument_list|,
literal|"toggled"
argument_list|,
name|G_CALLBACK
argument_list|(
name|gimp_toggle_button_update
argument_list|)
argument_list|,
operator|&
name|sels
operator|->
name|keep_knees
argument_list|)
expr_stmt|;
name|gtk_widget_show
argument_list|(
name|check
argument_list|)
expr_stmt|;
name|adjust_widgets
operator|=
name|g_slist_append
argument_list|(
name|adjust_widgets
argument_list|,
name|check
argument_list|)
expr_stmt|;
name|g_object_set_data
argument_list|(
name|G_OBJECT
argument_list|(
name|check
argument_list|)
argument_list|,
literal|"default_value"
argument_list|,
name|def_val
argument_list|(
operator|(
name|gdouble
operator|)
name|FALSE
argument_list|)
argument_list|)
expr_stmt|;
name|row
operator|++
expr_stmt|;
name|adj
operator|=
name|gimp_scale_entry_new
argument_list|(
name|GTK_TABLE
argument_list|(
name|table
argument_list|)
argument_list|,
literal|0
argument_list|,
name|row
operator|++
argument_list|,
literal|"Line Reversion Threshold:"
argument_list|,
name|SCALE_WIDTH
argument_list|,
name|SCALE_DIGITS
argument_list|,
name|sels
operator|->
name|line_reversion_threshold
argument_list|,
literal|0.01
argument_list|,
literal|0.2
argument_list|,
literal|0.01
argument_list|,
literal|0.01
argument_list|,
literal|3
argument_list|,
name|TRUE
argument_list|,
literal|0
argument_list|,
literal|0
argument_list|,
literal|"If a spline is closer to a straight line than this, "
literal|"it remains a straight line, even if it would otherwise "
literal|"be changed back to a curve. This is weighted by the "
literal|"square of the curve length, to make shorter curves "
literal|"more likely to be reverted."
argument_list|,
name|NULL
argument_list|)
expr_stmt|;
name|g_signal_connect
argument_list|(
name|adj
argument_list|,
literal|"value_changed"
argument_list|,
name|G_CALLBACK
argument_list|(
name|gimp_double_adjustment_update
argument_list|)
argument_list|,
operator|&
name|sels
operator|->
name|line_reversion_threshold
argument_list|)
expr_stmt|;
name|adjust_widgets
operator|=
name|g_slist_append
argument_list|(
name|adjust_widgets
argument_list|,
name|adj
argument_list|)
expr_stmt|;
name|g_object_set_data
argument_list|(
name|G_OBJECT
argument_list|(
name|adj
argument_list|)
argument_list|,
literal|"default_value"
argument_list|,
name|def_val
argument_list|(
literal|0.01
argument_list|)
argument_list|)
expr_stmt|;
name|adj
operator|=
name|gimp_scale_entry_new
argument_list|(
name|GTK_TABLE
argument_list|(
name|table
argument_list|)
argument_list|,
literal|0
argument_list|,
name|row
operator|++
argument_list|,
literal|"Line Threshold:"
argument_list|,
name|SCALE_WIDTH
argument_list|,
name|SCALE_DIGITS
argument_list|,
name|sels
operator|->
name|line_threshold
argument_list|,
literal|0.2
argument_list|,
literal|4
argument_list|,
literal|0.1
argument_list|,
literal|0.01
argument_list|,
literal|2
argument_list|,
name|TRUE
argument_list|,
literal|0
argument_list|,
literal|0
argument_list|,
literal|"How many pixels (on the average) a spline can "
literal|"diverge from the line determined by its endpoints "
literal|"before it is changed to a straight line."
argument_list|,
name|NULL
argument_list|)
expr_stmt|;
name|g_signal_connect
argument_list|(
name|adj
argument_list|,
literal|"value_changed"
argument_list|,
name|G_CALLBACK
argument_list|(
name|gimp_double_adjustment_update
argument_list|)
argument_list|,
operator|&
name|sels
operator|->
name|line_threshold
argument_list|)
expr_stmt|;
name|adjust_widgets
operator|=
name|g_slist_append
argument_list|(
name|adjust_widgets
argument_list|,
name|adj
argument_list|)
expr_stmt|;
name|g_object_set_data
argument_list|(
name|G_OBJECT
argument_list|(
name|adj
argument_list|)
argument_list|,
literal|"default_value"
argument_list|,
name|def_val
argument_list|(
literal|0.5
argument_list|)
argument_list|)
expr_stmt|;
name|adj
operator|=
name|gimp_scale_entry_new
argument_list|(
name|GTK_TABLE
argument_list|(
name|table
argument_list|)
argument_list|,
literal|0
argument_list|,
name|row
operator|++
argument_list|,
literal|"Reparametrize Improvement:"
argument_list|,
name|SCALE_WIDTH
argument_list|,
name|SCALE_DIGITS
argument_list|,
name|sels
operator|->
name|reparameterize_improvement
argument_list|,
literal|0
argument_list|,
literal|1
argument_list|,
literal|0.05
argument_list|,
literal|0.01
argument_list|,
literal|2
argument_list|,
name|TRUE
argument_list|,
literal|0
argument_list|,
literal|0
argument_list|,
literal|"If reparameterization doesn't improve the fit by this "
literal|"much percent, stop doing it. "
literal|"Amount of error at which "
literal|"it is pointless to reparameterize."
argument_list|,
name|NULL
argument_list|)
expr_stmt|;
name|g_signal_connect
argument_list|(
name|adj
argument_list|,
literal|"value_changed"
argument_list|,
name|G_CALLBACK
argument_list|(
name|gimp_double_adjustment_update
argument_list|)
argument_list|,
operator|&
name|sels
operator|->
name|reparameterize_improvement
argument_list|)
expr_stmt|;
name|adjust_widgets
operator|=
name|g_slist_append
argument_list|(
name|adjust_widgets
argument_list|,
name|adj
argument_list|)
expr_stmt|;
name|g_object_set_data
argument_list|(
name|G_OBJECT
argument_list|(
name|adj
argument_list|)
argument_list|,
literal|"default_value"
argument_list|,
name|def_val
argument_list|(
literal|0.01
argument_list|)
argument_list|)
expr_stmt|;
name|adj
operator|=
name|gimp_scale_entry_new
argument_list|(
name|GTK_TABLE
argument_list|(
name|table
argument_list|)
argument_list|,
literal|0
argument_list|,
name|row
operator|++
argument_list|,
literal|"Reparametrize Threshold:"
argument_list|,
name|SCALE_WIDTH
argument_list|,
name|SCALE_DIGITS
argument_list|,
name|sels
operator|->
name|reparameterize_threshold
argument_list|,
literal|1
argument_list|,
literal|50
argument_list|,
literal|0.5
argument_list|,
literal|0.5
argument_list|,
literal|2
argument_list|,
name|TRUE
argument_list|,
literal|0
argument_list|,
literal|0
argument_list|,
literal|"Amount of error at which it is pointless to reparameterize.  "
literal|"This happens, for example, when we are trying to fit the "
literal|"outline of the outside of an `O' with a single spline.  "
literal|"The initial fit is not good enough for the Newton-Raphson "
literal|"iteration to improve it.  It may be that it would be better "
literal|"to detect the cases where we didn't find any corners."
argument_list|,
name|NULL
argument_list|)
expr_stmt|;
name|g_signal_connect
argument_list|(
name|adj
argument_list|,
literal|"value_changed"
argument_list|,
name|G_CALLBACK
argument_list|(
name|gimp_double_adjustment_update
argument_list|)
argument_list|,
operator|&
name|sels
operator|->
name|reparameterize_threshold
argument_list|)
expr_stmt|;
name|adjust_widgets
operator|=
name|g_slist_append
argument_list|(
name|adjust_widgets
argument_list|,
name|adj
argument_list|)
expr_stmt|;
name|g_object_set_data
argument_list|(
name|G_OBJECT
argument_list|(
name|adj
argument_list|)
argument_list|,
literal|"default_value"
argument_list|,
name|def_val
argument_list|(
literal|1.0
argument_list|)
argument_list|)
expr_stmt|;
name|adj
operator|=
name|gimp_scale_entry_new
argument_list|(
name|GTK_TABLE
argument_list|(
name|table
argument_list|)
argument_list|,
literal|0
argument_list|,
name|row
operator|++
argument_list|,
literal|"Subdivide Search:"
argument_list|,
name|SCALE_WIDTH
argument_list|,
name|SCALE_DIGITS
argument_list|,
name|sels
operator|->
name|subdivide_search
argument_list|,
literal|0.05
argument_list|,
literal|1
argument_list|,
literal|0.05
argument_list|,
literal|0.01
argument_list|,
literal|2
argument_list|,
name|TRUE
argument_list|,
literal|0
argument_list|,
literal|0
argument_list|,
literal|"Percentage of the curve away from the worst point "
literal|"to look for a better place to subdivide."
argument_list|,
name|NULL
argument_list|)
expr_stmt|;
name|g_signal_connect
argument_list|(
name|adj
argument_list|,
literal|"value_changed"
argument_list|,
name|G_CALLBACK
argument_list|(
name|gimp_double_adjustment_update
argument_list|)
argument_list|,
operator|&
name|sels
operator|->
name|subdivide_search
argument_list|)
expr_stmt|;
name|adjust_widgets
operator|=
name|g_slist_append
argument_list|(
name|adjust_widgets
argument_list|,
name|adj
argument_list|)
expr_stmt|;
name|g_object_set_data
argument_list|(
name|G_OBJECT
argument_list|(
name|adj
argument_list|)
argument_list|,
literal|"default_value"
argument_list|,
name|def_val
argument_list|(
literal|0.1
argument_list|)
argument_list|)
expr_stmt|;
name|adj
operator|=
name|gimp_scale_entry_new
argument_list|(
name|GTK_TABLE
argument_list|(
name|table
argument_list|)
argument_list|,
literal|0
argument_list|,
name|row
operator|++
argument_list|,
literal|"Subdivide Surround:"
argument_list|,
name|SCALE_WIDTH
argument_list|,
name|SCALE_DIGITS
argument_list|,
name|sels
operator|->
name|subdivide_surround
argument_list|,
literal|2
argument_list|,
literal|10
argument_list|,
literal|1
argument_list|,
literal|1
argument_list|,
literal|0
argument_list|,
name|TRUE
argument_list|,
literal|0
argument_list|,
literal|0
argument_list|,
literal|"Number of points to consider when deciding whether "
literal|"a given point is a better place to subdivide."
argument_list|,
name|NULL
argument_list|)
expr_stmt|;
name|g_signal_connect
argument_list|(
name|adj
argument_list|,
literal|"value_changed"
argument_list|,
name|G_CALLBACK
argument_list|(
name|gimp_double_adjustment_update
argument_list|)
argument_list|,
operator|&
name|sels
operator|->
name|subdivide_surround
argument_list|)
expr_stmt|;
name|adjust_widgets
operator|=
name|g_slist_append
argument_list|(
name|adjust_widgets
argument_list|,
name|adj
argument_list|)
expr_stmt|;
name|g_object_set_data
argument_list|(
name|G_OBJECT
argument_list|(
name|adj
argument_list|)
argument_list|,
literal|"default_value"
argument_list|,
name|def_val
argument_list|(
literal|4.0
argument_list|)
argument_list|)
expr_stmt|;
name|adj
operator|=
name|gimp_scale_entry_new
argument_list|(
name|GTK_TABLE
argument_list|(
name|table
argument_list|)
argument_list|,
literal|0
argument_list|,
name|row
operator|++
argument_list|,
literal|"Subdivide Threshold:"
argument_list|,
name|SCALE_WIDTH
argument_list|,
name|SCALE_DIGITS
argument_list|,
name|sels
operator|->
name|subdivide_threshold
argument_list|,
literal|0.01
argument_list|,
literal|1
argument_list|,
literal|0.01
argument_list|,
literal|0.01
argument_list|,
literal|2
argument_list|,
name|TRUE
argument_list|,
literal|0
argument_list|,
literal|0
argument_list|,
literal|"How many pixels a point can diverge from a straight "
literal|"line and still be considered a better place to "
literal|"subdivide."
argument_list|,
name|NULL
argument_list|)
expr_stmt|;
name|g_signal_connect
argument_list|(
name|adj
argument_list|,
literal|"value_changed"
argument_list|,
name|G_CALLBACK
argument_list|(
name|gimp_double_adjustment_update
argument_list|)
argument_list|,
operator|&
name|sels
operator|->
name|subdivide_threshold
argument_list|)
expr_stmt|;
name|adjust_widgets
operator|=
name|g_slist_append
argument_list|(
name|adjust_widgets
argument_list|,
name|adj
argument_list|)
expr_stmt|;
name|g_object_set_data
argument_list|(
name|G_OBJECT
argument_list|(
name|adj
argument_list|)
argument_list|,
literal|"default_value"
argument_list|,
name|def_val
argument_list|(
literal|0.03
argument_list|)
argument_list|)
expr_stmt|;
name|adj
operator|=
name|gimp_scale_entry_new
argument_list|(
name|GTK_TABLE
argument_list|(
name|table
argument_list|)
argument_list|,
literal|0
argument_list|,
name|row
operator|++
argument_list|,
literal|"Tangent Surround:"
argument_list|,
name|SCALE_WIDTH
argument_list|,
name|SCALE_DIGITS
argument_list|,
name|sels
operator|->
name|tangent_surround
argument_list|,
literal|2
argument_list|,
literal|10
argument_list|,
literal|1
argument_list|,
literal|1
argument_list|,
literal|0
argument_list|,
name|TRUE
argument_list|,
literal|0
argument_list|,
literal|0
argument_list|,
literal|"Number of points to look at on either side of a "
literal|"point when computing the approximation to the "
literal|"tangent at that point."
argument_list|,
name|NULL
argument_list|)
expr_stmt|;
name|g_signal_connect
argument_list|(
name|adj
argument_list|,
literal|"value_changed"
argument_list|,
name|G_CALLBACK
argument_list|(
name|gimp_double_adjustment_update
argument_list|)
argument_list|,
operator|&
name|sels
operator|->
name|tangent_surround
argument_list|)
expr_stmt|;
name|adjust_widgets
operator|=
name|g_slist_append
argument_list|(
name|adjust_widgets
argument_list|,
name|adj
argument_list|)
expr_stmt|;
name|g_object_set_data
argument_list|(
name|G_OBJECT
argument_list|(
name|adj
argument_list|)
argument_list|,
literal|"default_value"
argument_list|,
name|def_val
argument_list|(
literal|3.0
argument_list|)
argument_list|)
expr_stmt|;
return|return
name|GTK_WIDGET
argument_list|(
name|table
argument_list|)
return|;
block|}
end_function

end_unit

