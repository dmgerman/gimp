begin_unit|revision:0.9.5;language:C;cregit-version:0.0.1
begin_comment
comment|/* LIBGIMP - The GIMP Library  * Copyright (C) 1995-1997 Peter Mattis and Spencer Kimball  *  * gimpscaleentry.c  * Copyright (C) 2000 Michael Natterer<mitch@gimp.org>  *  * This library is free software: you can redistribute it and/or  * modify it under the terms of the GNU Lesser General Public  * License as published by the Free Software Foundation; either  * version 3 of the License, or (at your option) any later version.  *  * This library is distributed in the hope that it will be useful,  * but WITHOUT ANY WARRANTY; without even the implied warranty of  * MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the GNU  * Library General Public License for more details.  *  * You should have received a copy of the GNU Lesser General Public  * License along with this library.  If not, see  *<https://www.gnu.org/licenses/>.  */
end_comment

begin_include
include|#
directive|include
file|"config.h"
end_include

begin_include
include|#
directive|include
file|<gegl.h>
end_include

begin_include
include|#
directive|include
file|<gtk/gtk.h>
end_include

begin_include
include|#
directive|include
file|"libgimpcolor/gimpcolor.h"
end_include

begin_include
include|#
directive|include
file|"libgimpmath/gimpmath.h"
end_include

begin_include
include|#
directive|include
file|"libgimpbase/gimpbase.h"
end_include

begin_include
include|#
directive|include
file|"gimpwidgets.h"
end_include

begin_function_decl
specifier|static
name|gboolean
name|gimp_scale_entry_linear_to_log
parameter_list|(
name|GBinding
modifier|*
name|binding
parameter_list|,
specifier|const
name|GValue
modifier|*
name|from_value
parameter_list|,
name|GValue
modifier|*
name|to_value
parameter_list|,
name|gpointer
name|user_data
parameter_list|)
function_decl|;
end_function_decl

begin_function_decl
specifier|static
name|gboolean
name|gimp_scale_entry_log_to_linear
parameter_list|(
name|GBinding
modifier|*
name|binding
parameter_list|,
specifier|const
name|GValue
modifier|*
name|from_value
parameter_list|,
name|GValue
modifier|*
name|to_value
parameter_list|,
name|gpointer
name|user_data
parameter_list|)
function_decl|;
end_function_decl

begin_function_decl
specifier|static
name|GtkAdjustment
modifier|*
name|gimp_scale_entry_new_internal
parameter_list|(
name|gboolean
name|color_scale
parameter_list|,
name|GtkGrid
modifier|*
name|grid
parameter_list|,
name|gint
name|column
parameter_list|,
name|gint
name|row
parameter_list|,
specifier|const
name|gchar
modifier|*
name|text
parameter_list|,
name|gint
name|scale_width
parameter_list|,
name|gint
name|spinbutton_width
parameter_list|,
name|gdouble
name|value
parameter_list|,
name|gdouble
name|lower
parameter_list|,
name|gdouble
name|upper
parameter_list|,
name|gdouble
name|step_increment
parameter_list|,
name|gdouble
name|page_increment
parameter_list|,
name|guint
name|digits
parameter_list|,
name|gboolean
name|constrain
parameter_list|,
name|gdouble
name|unconstrained_lower
parameter_list|,
name|gdouble
name|unconstrained_upper
parameter_list|,
specifier|const
name|gchar
modifier|*
name|tooltip
parameter_list|,
specifier|const
name|gchar
modifier|*
name|help_id
parameter_list|)
function_decl|;
end_function_decl

begin_function
specifier|static
name|gboolean
DECL|function|gimp_scale_entry_linear_to_log (GBinding * binding,const GValue * from_value,GValue * to_value,gpointer user_data)
name|gimp_scale_entry_linear_to_log
parameter_list|(
name|GBinding
modifier|*
name|binding
parameter_list|,
specifier|const
name|GValue
modifier|*
name|from_value
parameter_list|,
name|GValue
modifier|*
name|to_value
parameter_list|,
name|gpointer
name|user_data
parameter_list|)
block|{
name|GtkAdjustment
modifier|*
name|spin_adjustment
decl_stmt|;
name|gdouble
name|value
init|=
name|g_value_get_double
argument_list|(
name|from_value
argument_list|)
decl_stmt|;
name|spin_adjustment
operator|=
name|GTK_ADJUSTMENT
argument_list|(
name|g_binding_get_source
argument_list|(
name|binding
argument_list|)
argument_list|)
expr_stmt|;
if|if
condition|(
name|gtk_adjustment_get_lower
argument_list|(
name|spin_adjustment
argument_list|)
operator|<=
literal|0.0
condition|)
name|value
operator|=
name|log
argument_list|(
name|value
operator|-
name|gtk_adjustment_get_lower
argument_list|(
name|spin_adjustment
argument_list|)
operator|+
literal|0.1
argument_list|)
expr_stmt|;
else|else
name|value
operator|=
name|log
argument_list|(
name|value
argument_list|)
expr_stmt|;
name|g_value_set_double
argument_list|(
name|to_value
argument_list|,
name|value
argument_list|)
expr_stmt|;
return|return
name|TRUE
return|;
block|}
end_function

begin_function
specifier|static
name|gboolean
DECL|function|gimp_scale_entry_log_to_linear (GBinding * binding,const GValue * from_value,GValue * to_value,gpointer user_data)
name|gimp_scale_entry_log_to_linear
parameter_list|(
name|GBinding
modifier|*
name|binding
parameter_list|,
specifier|const
name|GValue
modifier|*
name|from_value
parameter_list|,
name|GValue
modifier|*
name|to_value
parameter_list|,
name|gpointer
name|user_data
parameter_list|)
block|{
name|GtkAdjustment
modifier|*
name|spin_adjustment
decl_stmt|;
name|gdouble
name|value
init|=
name|g_value_get_double
argument_list|(
name|from_value
argument_list|)
decl_stmt|;
name|spin_adjustment
operator|=
name|GTK_ADJUSTMENT
argument_list|(
name|g_binding_get_target
argument_list|(
name|binding
argument_list|)
argument_list|)
expr_stmt|;
name|value
operator|=
name|exp
argument_list|(
name|value
argument_list|)
expr_stmt|;
if|if
condition|(
name|gtk_adjustment_get_lower
argument_list|(
name|spin_adjustment
argument_list|)
operator|<=
literal|0.0
condition|)
name|value
operator|+=
name|gtk_adjustment_get_lower
argument_list|(
name|spin_adjustment
argument_list|)
operator|-
literal|0.1
expr_stmt|;
name|g_value_set_double
argument_list|(
name|to_value
argument_list|,
name|value
argument_list|)
expr_stmt|;
return|return
name|TRUE
return|;
block|}
end_function

begin_function
specifier|static
name|GtkAdjustment
modifier|*
DECL|function|gimp_scale_entry_new_internal (gboolean color_scale,GtkGrid * grid,gint column,gint row,const gchar * text,gint scale_width,gint spinbutton_width,gdouble value,gdouble lower,gdouble upper,gdouble step_increment,gdouble page_increment,guint digits,gboolean constrain,gdouble unconstrained_lower,gdouble unconstrained_upper,const gchar * tooltip,const gchar * help_id)
name|gimp_scale_entry_new_internal
parameter_list|(
name|gboolean
name|color_scale
parameter_list|,
name|GtkGrid
modifier|*
name|grid
parameter_list|,
name|gint
name|column
parameter_list|,
name|gint
name|row
parameter_list|,
specifier|const
name|gchar
modifier|*
name|text
parameter_list|,
name|gint
name|scale_width
parameter_list|,
name|gint
name|spinbutton_width
parameter_list|,
name|gdouble
name|value
parameter_list|,
name|gdouble
name|lower
parameter_list|,
name|gdouble
name|upper
parameter_list|,
name|gdouble
name|step_increment
parameter_list|,
name|gdouble
name|page_increment
parameter_list|,
name|guint
name|digits
parameter_list|,
name|gboolean
name|constrain
parameter_list|,
name|gdouble
name|unconstrained_lower
parameter_list|,
name|gdouble
name|unconstrained_upper
parameter_list|,
specifier|const
name|gchar
modifier|*
name|tooltip
parameter_list|,
specifier|const
name|gchar
modifier|*
name|help_id
parameter_list|)
block|{
name|GtkWidget
modifier|*
name|label
decl_stmt|;
name|GtkWidget
modifier|*
name|scale
decl_stmt|;
name|GtkWidget
modifier|*
name|spinbutton
decl_stmt|;
name|GtkAdjustment
modifier|*
name|scale_adjustment
decl_stmt|;
name|GtkAdjustment
modifier|*
name|spin_adjustment
decl_stmt|;
name|GBinding
modifier|*
name|binding
decl_stmt|;
name|label
operator|=
name|gtk_label_new_with_mnemonic
argument_list|(
name|text
argument_list|)
expr_stmt|;
name|gtk_label_set_xalign
argument_list|(
name|GTK_LABEL
argument_list|(
name|label
argument_list|)
argument_list|,
literal|0.0
argument_list|)
expr_stmt|;
name|gtk_widget_show
argument_list|(
name|label
argument_list|)
expr_stmt|;
name|scale_adjustment
operator|=
name|gtk_adjustment_new
argument_list|(
name|value
argument_list|,
name|lower
argument_list|,
name|upper
argument_list|,
name|step_increment
argument_list|,
name|page_increment
argument_list|,
literal|0.0
argument_list|)
expr_stmt|;
if|if
condition|(
operator|!
name|constrain
operator|&&
name|unconstrained_lower
operator|<=
name|lower
operator|&&
name|unconstrained_upper
operator|>=
name|upper
condition|)
block|{
name|spin_adjustment
operator|=
name|gtk_adjustment_new
argument_list|(
name|value
argument_list|,
name|unconstrained_lower
argument_list|,
name|unconstrained_upper
argument_list|,
name|step_increment
argument_list|,
name|page_increment
argument_list|,
literal|0.0
argument_list|)
expr_stmt|;
block|}
else|else
block|{
name|spin_adjustment
operator|=
name|gtk_adjustment_new
argument_list|(
name|value
argument_list|,
name|lower
argument_list|,
name|upper
argument_list|,
name|step_increment
argument_list|,
name|page_increment
argument_list|,
literal|0.0
argument_list|)
expr_stmt|;
block|}
name|binding
operator|=
name|g_object_bind_property
argument_list|(
name|G_OBJECT
argument_list|(
name|spin_adjustment
argument_list|)
argument_list|,
literal|"value"
argument_list|,
name|G_OBJECT
argument_list|(
name|scale_adjustment
argument_list|)
argument_list|,
literal|"value"
argument_list|,
name|G_BINDING_BIDIRECTIONAL
operator||
name|G_BINDING_SYNC_CREATE
argument_list|)
expr_stmt|;
name|spinbutton
operator|=
name|gimp_spin_button_new
argument_list|(
name|spin_adjustment
argument_list|,
name|step_increment
argument_list|,
name|digits
argument_list|)
expr_stmt|;
name|gtk_spin_button_set_numeric
argument_list|(
name|GTK_SPIN_BUTTON
argument_list|(
name|spinbutton
argument_list|)
argument_list|,
name|TRUE
argument_list|)
expr_stmt|;
name|gtk_widget_show
argument_list|(
name|spinbutton
argument_list|)
expr_stmt|;
name|gtk_label_set_mnemonic_widget
argument_list|(
name|GTK_LABEL
argument_list|(
name|label
argument_list|)
argument_list|,
name|spinbutton
argument_list|)
expr_stmt|;
if|if
condition|(
name|spinbutton_width
operator|>
literal|0
condition|)
block|{
if|if
condition|(
name|spinbutton_width
operator|<
literal|17
condition|)
name|gtk_entry_set_width_chars
argument_list|(
name|GTK_ENTRY
argument_list|(
name|spinbutton
argument_list|)
argument_list|,
name|spinbutton_width
argument_list|)
expr_stmt|;
else|else
name|gtk_widget_set_size_request
argument_list|(
name|spinbutton
argument_list|,
name|spinbutton_width
argument_list|,
operator|-
literal|1
argument_list|)
expr_stmt|;
block|}
if|if
condition|(
name|color_scale
condition|)
block|{
name|scale
operator|=
name|gimp_color_scale_new
argument_list|(
name|GTK_ORIENTATION_HORIZONTAL
argument_list|,
name|GIMP_COLOR_SELECTOR_VALUE
argument_list|)
expr_stmt|;
name|gtk_range_set_adjustment
argument_list|(
name|GTK_RANGE
argument_list|(
name|scale
argument_list|)
argument_list|,
name|scale_adjustment
argument_list|)
expr_stmt|;
block|}
else|else
block|{
name|scale
operator|=
name|gtk_scale_new
argument_list|(
name|GTK_ORIENTATION_HORIZONTAL
argument_list|,
name|scale_adjustment
argument_list|)
expr_stmt|;
name|gtk_scale_set_digits
argument_list|(
name|GTK_SCALE
argument_list|(
name|scale
argument_list|)
argument_list|,
name|digits
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
block|}
if|if
condition|(
name|scale_width
operator|>
literal|0
condition|)
name|gtk_widget_set_size_request
argument_list|(
name|scale
argument_list|,
name|scale_width
argument_list|,
operator|-
literal|1
argument_list|)
expr_stmt|;
name|gtk_widget_show
argument_list|(
name|scale
argument_list|)
expr_stmt|;
name|gtk_widget_set_hexpand
argument_list|(
name|scale
argument_list|,
name|TRUE
argument_list|)
expr_stmt|;
name|gtk_grid_attach
argument_list|(
name|grid
argument_list|,
name|label
argument_list|,
name|column
argument_list|,
name|row
argument_list|,
literal|1
argument_list|,
literal|1
argument_list|)
expr_stmt|;
name|gtk_grid_attach
argument_list|(
name|grid
argument_list|,
name|scale
argument_list|,
name|column
operator|+
literal|1
argument_list|,
name|row
argument_list|,
literal|1
argument_list|,
literal|1
argument_list|)
expr_stmt|;
name|gtk_grid_attach
argument_list|(
name|grid
argument_list|,
name|spinbutton
argument_list|,
name|column
operator|+
literal|2
argument_list|,
name|row
argument_list|,
literal|1
argument_list|,
literal|1
argument_list|)
expr_stmt|;
if|if
condition|(
name|tooltip
operator|||
name|help_id
condition|)
block|{
name|gimp_help_set_help_data
argument_list|(
name|label
argument_list|,
name|tooltip
argument_list|,
name|help_id
argument_list|)
expr_stmt|;
name|gimp_help_set_help_data
argument_list|(
name|scale
argument_list|,
name|tooltip
argument_list|,
name|help_id
argument_list|)
expr_stmt|;
name|gimp_help_set_help_data
argument_list|(
name|spinbutton
argument_list|,
name|tooltip
argument_list|,
name|help_id
argument_list|)
expr_stmt|;
block|}
name|g_object_set_data
argument_list|(
name|G_OBJECT
argument_list|(
name|spin_adjustment
argument_list|)
argument_list|,
literal|"label"
argument_list|,
name|label
argument_list|)
expr_stmt|;
name|g_object_set_data
argument_list|(
name|G_OBJECT
argument_list|(
name|spin_adjustment
argument_list|)
argument_list|,
literal|"scale"
argument_list|,
name|scale
argument_list|)
expr_stmt|;
name|g_object_set_data
argument_list|(
name|G_OBJECT
argument_list|(
name|spin_adjustment
argument_list|)
argument_list|,
literal|"spinbutton"
argument_list|,
name|spinbutton
argument_list|)
expr_stmt|;
name|g_object_set_data
argument_list|(
name|G_OBJECT
argument_list|(
name|spin_adjustment
argument_list|)
argument_list|,
literal|"binding"
argument_list|,
name|binding
argument_list|)
expr_stmt|;
return|return
name|spin_adjustment
return|;
block|}
end_function

begin_comment
comment|/**  * gimp_scale_entry_new:  * @grid:                The #GtkGrid the widgets will be attached to.  * @column:              The column to start with.  * @row:                 The row to attach the widgets.  * @text:                The text for the #GtkLabel which will appear  *                       left of the #GtkHScale.  * @scale_width:         The minimum horizontal size of the #GtkHScale.  * @spinbutton_width:    The minimum horizontal size of the #GtkSpinButton.  * @value:               The initial value.  * @lower:               The lower boundary.  * @upper:               The upper boundary.  * @step_increment:      The step increment.  * @page_increment:      The page increment.  * @digits:              The number of decimal digits.  * @constrain:           %TRUE if the range of possible values of the  *                       #GtkSpinButton should be the same as of the #GtkHScale.  * @unconstrained_lower: The spinbutton's lower boundary  *                       if @constrain == %FALSE.  * @unconstrained_upper: The spinbutton's upper boundary  *                       if @constrain == %FALSE.  * @tooltip:             A tooltip message for the scale and the spinbutton.  * @help_id:             The widgets' help_id (see gimp_help_set_help_data()).  *  * This function creates a #GtkLabel, a #GtkHScale and a #GtkSpinButton and  * attaches them to a 3-column #GtkGrid.  *  * Returns: (transfer none): The #GtkSpinButton's #GtkAdjustment.  **/
end_comment

begin_function
name|GtkAdjustment
modifier|*
DECL|function|gimp_scale_entry_new (GtkGrid * grid,gint column,gint row,const gchar * text,gint scale_width,gint spinbutton_width,gdouble value,gdouble lower,gdouble upper,gdouble step_increment,gdouble page_increment,guint digits,gboolean constrain,gdouble unconstrained_lower,gdouble unconstrained_upper,const gchar * tooltip,const gchar * help_id)
name|gimp_scale_entry_new
parameter_list|(
name|GtkGrid
modifier|*
name|grid
parameter_list|,
name|gint
name|column
parameter_list|,
name|gint
name|row
parameter_list|,
specifier|const
name|gchar
modifier|*
name|text
parameter_list|,
name|gint
name|scale_width
parameter_list|,
name|gint
name|spinbutton_width
parameter_list|,
name|gdouble
name|value
parameter_list|,
name|gdouble
name|lower
parameter_list|,
name|gdouble
name|upper
parameter_list|,
name|gdouble
name|step_increment
parameter_list|,
name|gdouble
name|page_increment
parameter_list|,
name|guint
name|digits
parameter_list|,
name|gboolean
name|constrain
parameter_list|,
name|gdouble
name|unconstrained_lower
parameter_list|,
name|gdouble
name|unconstrained_upper
parameter_list|,
specifier|const
name|gchar
modifier|*
name|tooltip
parameter_list|,
specifier|const
name|gchar
modifier|*
name|help_id
parameter_list|)
block|{
return|return
name|gimp_scale_entry_new_internal
argument_list|(
name|FALSE
argument_list|,
name|grid
argument_list|,
name|column
argument_list|,
name|row
argument_list|,
name|text
argument_list|,
name|scale_width
argument_list|,
name|spinbutton_width
argument_list|,
name|value
argument_list|,
name|lower
argument_list|,
name|upper
argument_list|,
name|step_increment
argument_list|,
name|page_increment
argument_list|,
name|digits
argument_list|,
name|constrain
argument_list|,
name|unconstrained_lower
argument_list|,
name|unconstrained_upper
argument_list|,
name|tooltip
argument_list|,
name|help_id
argument_list|)
return|;
block|}
end_function

begin_comment
comment|/**  * gimp_color_scale_entry_new:  * @grid:                The #GtkGrid the widgets will be attached to.  * @column:              The column to start with.  * @row:                 The row to attach the widgets.  * @text:                The text for the #GtkLabel which will appear  *                       left of the #GtkHScale.  * @scale_width:         The minimum horizontal size of the #GtkHScale.  * @spinbutton_width:    The minimum horizontal size of the #GtkSpinButton.  * @value:               The initial value.  * @lower:               The lower boundary.  * @upper:               The upper boundary.  * @step_increment:      The step increment.  * @page_increment:      The page increment.  * @digits:              The number of decimal digits.  * @tooltip:             A tooltip message for the scale and the spinbutton.  * @help_id:             The widgets' help_id (see gimp_help_set_help_data()).  *  * This function creates a #GtkLabel, a #GimpColorScale and a  * #GtkSpinButton and attaches them to a 3-column #GtkGrid.  *  * Returns: (transfer none): The #GtkSpinButton's #GtkAdjustment.  **/
end_comment

begin_function
name|GtkAdjustment
modifier|*
DECL|function|gimp_color_scale_entry_new (GtkGrid * grid,gint column,gint row,const gchar * text,gint scale_width,gint spinbutton_width,gdouble value,gdouble lower,gdouble upper,gdouble step_increment,gdouble page_increment,guint digits,const gchar * tooltip,const gchar * help_id)
name|gimp_color_scale_entry_new
parameter_list|(
name|GtkGrid
modifier|*
name|grid
parameter_list|,
name|gint
name|column
parameter_list|,
name|gint
name|row
parameter_list|,
specifier|const
name|gchar
modifier|*
name|text
parameter_list|,
name|gint
name|scale_width
parameter_list|,
name|gint
name|spinbutton_width
parameter_list|,
name|gdouble
name|value
parameter_list|,
name|gdouble
name|lower
parameter_list|,
name|gdouble
name|upper
parameter_list|,
name|gdouble
name|step_increment
parameter_list|,
name|gdouble
name|page_increment
parameter_list|,
name|guint
name|digits
parameter_list|,
specifier|const
name|gchar
modifier|*
name|tooltip
parameter_list|,
specifier|const
name|gchar
modifier|*
name|help_id
parameter_list|)
block|{
return|return
name|gimp_scale_entry_new_internal
argument_list|(
name|TRUE
argument_list|,
name|grid
argument_list|,
name|column
argument_list|,
name|row
argument_list|,
name|text
argument_list|,
name|scale_width
argument_list|,
name|spinbutton_width
argument_list|,
name|value
argument_list|,
name|lower
argument_list|,
name|upper
argument_list|,
name|step_increment
argument_list|,
name|page_increment
argument_list|,
name|digits
argument_list|,
name|TRUE
argument_list|,
literal|0.0
argument_list|,
literal|0.0
argument_list|,
name|tooltip
argument_list|,
name|help_id
argument_list|)
return|;
block|}
end_function

begin_comment
comment|/**  * gimp_scale_entry_set_logarithmic:  * @adjustment:  a  #GtkAdjustment as returned by gimp_scale_entry_new()  * @logarithmic: a boolean value to set or reset logarithmic behaviour  *               of the scale widget  *  * Sets whether the scale_entry's scale widget will behave in a linear  * or logarithmic fashion. Useful when an entry has to attend large  * ranges, but smaller selections on that range require a finer  * adjustment.  *  * Since: 2.2  **/
end_comment

begin_function
name|void
DECL|function|gimp_scale_entry_set_logarithmic (GtkAdjustment * adjustment,gboolean logarithmic)
name|gimp_scale_entry_set_logarithmic
parameter_list|(
name|GtkAdjustment
modifier|*
name|adjustment
parameter_list|,
name|gboolean
name|logarithmic
parameter_list|)
block|{
name|GtkAdjustment
modifier|*
name|spin_adj
decl_stmt|;
name|GtkAdjustment
modifier|*
name|scale_adj
decl_stmt|;
name|GBinding
modifier|*
name|binding
decl_stmt|;
name|g_return_if_fail
argument_list|(
name|GTK_IS_ADJUSTMENT
argument_list|(
name|adjustment
argument_list|)
argument_list|)
expr_stmt|;
name|spin_adj
operator|=
name|adjustment
expr_stmt|;
name|scale_adj
operator|=
name|GIMP_SCALE_ENTRY_SCALE_ADJ
argument_list|(
name|adjustment
argument_list|)
expr_stmt|;
name|binding
operator|=
name|g_object_get_data
argument_list|(
name|G_OBJECT
argument_list|(
name|adjustment
argument_list|)
argument_list|,
literal|"binding"
argument_list|)
expr_stmt|;
name|g_return_if_fail
argument_list|(
name|GTK_IS_ADJUSTMENT
argument_list|(
name|scale_adj
argument_list|)
argument_list|)
expr_stmt|;
name|g_return_if_fail
argument_list|(
name|G_IS_BINDING
argument_list|(
name|binding
argument_list|)
argument_list|)
expr_stmt|;
name|logarithmic
operator|=
name|logarithmic
condition|?
name|TRUE
else|:
name|FALSE
expr_stmt|;
if|if
condition|(
name|logarithmic
operator|==
name|gimp_scale_entry_get_logarithmic
argument_list|(
name|adjustment
argument_list|)
condition|)
return|return;
name|g_object_unref
argument_list|(
name|binding
argument_list|)
expr_stmt|;
if|if
condition|(
name|logarithmic
condition|)
block|{
name|gdouble
name|correction
decl_stmt|;
name|gdouble
name|log_value
decl_stmt|,
name|log_lower
decl_stmt|,
name|log_upper
decl_stmt|;
name|gdouble
name|log_step_increment
decl_stmt|,
name|log_page_increment
decl_stmt|;
name|correction
operator|=
operator|(
name|gtk_adjustment_get_lower
argument_list|(
name|scale_adj
argument_list|)
operator|>
literal|0
condition|?
literal|0
else|:
literal|0.1
operator|+
operator|-
name|gtk_adjustment_get_lower
argument_list|(
name|scale_adj
argument_list|)
operator|)
expr_stmt|;
name|log_value
operator|=
name|log
argument_list|(
name|gtk_adjustment_get_value
argument_list|(
name|scale_adj
argument_list|)
operator|+
name|correction
argument_list|)
expr_stmt|;
name|log_lower
operator|=
name|log
argument_list|(
name|gtk_adjustment_get_lower
argument_list|(
name|scale_adj
argument_list|)
operator|+
name|correction
argument_list|)
expr_stmt|;
name|log_upper
operator|=
name|log
argument_list|(
name|gtk_adjustment_get_upper
argument_list|(
name|scale_adj
argument_list|)
operator|+
name|correction
argument_list|)
expr_stmt|;
name|log_step_increment
operator|=
operator|(
name|log_upper
operator|-
name|log_lower
operator|)
operator|/
operator|(
operator|(
name|gtk_adjustment_get_upper
argument_list|(
name|scale_adj
argument_list|)
operator|-
name|gtk_adjustment_get_lower
argument_list|(
name|scale_adj
argument_list|)
operator|)
operator|/
name|gtk_adjustment_get_step_increment
argument_list|(
name|scale_adj
argument_list|)
operator|)
expr_stmt|;
name|log_page_increment
operator|=
operator|(
name|log_upper
operator|-
name|log_lower
operator|)
operator|/
operator|(
operator|(
name|gtk_adjustment_get_upper
argument_list|(
name|scale_adj
argument_list|)
operator|-
name|gtk_adjustment_get_lower
argument_list|(
name|scale_adj
argument_list|)
operator|)
operator|/
name|gtk_adjustment_get_page_increment
argument_list|(
name|scale_adj
argument_list|)
operator|)
expr_stmt|;
name|gtk_adjustment_configure
argument_list|(
name|scale_adj
argument_list|,
name|log_value
argument_list|,
name|log_lower
argument_list|,
name|log_upper
argument_list|,
name|log_step_increment
argument_list|,
name|log_page_increment
argument_list|,
literal|0.0
argument_list|)
expr_stmt|;
name|binding
operator|=
name|g_object_bind_property_full
argument_list|(
name|G_OBJECT
argument_list|(
name|spin_adj
argument_list|)
argument_list|,
literal|"value"
argument_list|,
name|G_OBJECT
argument_list|(
name|scale_adj
argument_list|)
argument_list|,
literal|"value"
argument_list|,
name|G_BINDING_BIDIRECTIONAL
operator||
name|G_BINDING_SYNC_CREATE
argument_list|,
name|gimp_scale_entry_linear_to_log
argument_list|,
name|gimp_scale_entry_log_to_linear
argument_list|,
name|NULL
argument_list|,
name|NULL
argument_list|)
expr_stmt|;
block|}
else|else
block|{
name|gdouble
name|lower
decl_stmt|,
name|upper
decl_stmt|;
name|lower
operator|=
name|exp
argument_list|(
name|gtk_adjustment_get_lower
argument_list|(
name|scale_adj
argument_list|)
argument_list|)
expr_stmt|;
name|upper
operator|=
name|exp
argument_list|(
name|gtk_adjustment_get_upper
argument_list|(
name|scale_adj
argument_list|)
argument_list|)
expr_stmt|;
if|if
condition|(
name|gtk_adjustment_get_lower
argument_list|(
name|spin_adj
argument_list|)
operator|<=
literal|0.0
condition|)
block|{
name|lower
operator|+=
operator|-
literal|0.1
operator|+
name|gtk_adjustment_get_lower
argument_list|(
name|spin_adj
argument_list|)
expr_stmt|;
name|upper
operator|+=
operator|-
literal|0.1
operator|+
name|gtk_adjustment_get_lower
argument_list|(
name|spin_adj
argument_list|)
expr_stmt|;
block|}
name|gtk_adjustment_configure
argument_list|(
name|scale_adj
argument_list|,
name|gtk_adjustment_get_value
argument_list|(
name|spin_adj
argument_list|)
argument_list|,
name|lower
argument_list|,
name|upper
argument_list|,
name|gtk_adjustment_get_step_increment
argument_list|(
name|spin_adj
argument_list|)
argument_list|,
name|gtk_adjustment_get_page_increment
argument_list|(
name|spin_adj
argument_list|)
argument_list|,
literal|0.0
argument_list|)
expr_stmt|;
name|binding
operator|=
name|g_object_bind_property
argument_list|(
name|G_OBJECT
argument_list|(
name|spin_adj
argument_list|)
argument_list|,
literal|"value"
argument_list|,
name|G_OBJECT
argument_list|(
name|scale_adj
argument_list|)
argument_list|,
literal|"value"
argument_list|,
name|G_BINDING_BIDIRECTIONAL
operator||
name|G_BINDING_SYNC_CREATE
argument_list|)
expr_stmt|;
block|}
name|g_object_set_data
argument_list|(
name|G_OBJECT
argument_list|(
name|spin_adj
argument_list|)
argument_list|,
literal|"binding"
argument_list|,
name|binding
argument_list|)
expr_stmt|;
name|g_object_set_data
argument_list|(
name|G_OBJECT
argument_list|(
name|adjustment
argument_list|)
argument_list|,
literal|"logarithmic"
argument_list|,
name|GINT_TO_POINTER
argument_list|(
name|logarithmic
argument_list|)
argument_list|)
expr_stmt|;
block|}
end_function

begin_comment
comment|/**  * gimp_scale_entry_get_logarithmic:  * @adjustment: a  #GtkAdjustment as returned by gimp_scale_entry_new()  *  * Returns: %TRUE if the the entry's scale widget will behave in  *          logarithmic fashion, %FALSE for linear behaviour.  *  * Since: 2.2  **/
end_comment

begin_function
name|gboolean
DECL|function|gimp_scale_entry_get_logarithmic (GtkAdjustment * adjustment)
name|gimp_scale_entry_get_logarithmic
parameter_list|(
name|GtkAdjustment
modifier|*
name|adjustment
parameter_list|)
block|{
return|return
name|GPOINTER_TO_INT
argument_list|(
name|g_object_get_data
argument_list|(
name|G_OBJECT
argument_list|(
name|adjustment
argument_list|)
argument_list|,
literal|"logarithmic"
argument_list|)
argument_list|)
return|;
block|}
end_function

begin_comment
comment|/**  * gimp_scale_entry_set_sensitive:  * @adjustment: a #GtkAdjustment returned by gimp_scale_entry_new()  * @sensitive:  a boolean value with the same semantics as the @sensitive  *              parameter of gtk_widget_set_sensitive()  *  * Sets the sensitivity of the scale_entry's #GtkLabel, #GtkHScale and  * #GtkSpinButton.  **/
end_comment

begin_function
name|void
DECL|function|gimp_scale_entry_set_sensitive (GtkAdjustment * adjustment,gboolean sensitive)
name|gimp_scale_entry_set_sensitive
parameter_list|(
name|GtkAdjustment
modifier|*
name|adjustment
parameter_list|,
name|gboolean
name|sensitive
parameter_list|)
block|{
name|GtkWidget
modifier|*
name|widget
decl_stmt|;
name|g_return_if_fail
argument_list|(
name|GTK_IS_ADJUSTMENT
argument_list|(
name|adjustment
argument_list|)
argument_list|)
expr_stmt|;
name|widget
operator|=
name|GIMP_SCALE_ENTRY_LABEL
argument_list|(
name|adjustment
argument_list|)
expr_stmt|;
if|if
condition|(
name|widget
condition|)
name|gtk_widget_set_sensitive
argument_list|(
name|widget
argument_list|,
name|sensitive
argument_list|)
expr_stmt|;
name|widget
operator|=
name|GIMP_SCALE_ENTRY_SCALE
argument_list|(
name|adjustment
argument_list|)
expr_stmt|;
if|if
condition|(
name|widget
condition|)
name|gtk_widget_set_sensitive
argument_list|(
name|widget
argument_list|,
name|sensitive
argument_list|)
expr_stmt|;
name|widget
operator|=
name|GIMP_SCALE_ENTRY_SPINBUTTON
argument_list|(
name|adjustment
argument_list|)
expr_stmt|;
if|if
condition|(
name|widget
condition|)
name|gtk_widget_set_sensitive
argument_list|(
name|widget
argument_list|,
name|sensitive
argument_list|)
expr_stmt|;
block|}
end_function

end_unit

