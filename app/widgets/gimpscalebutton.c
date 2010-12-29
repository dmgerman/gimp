begin_unit|revision:0.9.5;language:C;cregit-version:0.0.1
begin_comment
comment|/* GIMP - The GNU Image Manipulation Program  * Copyright (C) 1995 Spencer Kimball and Peter Mattis  *  * gimpscalebutton.c  * Copyright (C) 2008 Sven Neumann<sven@gimp.org>  *  * This program is free software: you can redistribute it and/or modify  * it under the terms of the GNU General Public License as published by  * the Free Software Foundation; either version 3 of the License, or  * (at your option) any later version.  *  * This program is distributed in the hope that it will be useful,  * but WITHOUT ANY WARRANTY; without even the implied warranty of  * MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the  * GNU General Public License for more details.  *  * You should have received a copy of the GNU General Public License  * along with this program.  If not, see<http://www.gnu.org/licenses/>.  */
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
file|"widgets-types.h"
end_include

begin_include
include|#
directive|include
file|"gimpscalebutton.h"
end_include

begin_function_decl
specifier|static
name|void
name|gimp_scale_button_value_changed
parameter_list|(
name|GtkScaleButton
modifier|*
name|button
parameter_list|,
name|gdouble
name|value
parameter_list|)
function_decl|;
end_function_decl

begin_function_decl
specifier|static
name|void
name|gimp_scale_button_update_tooltip
parameter_list|(
name|GimpScaleButton
modifier|*
name|button
parameter_list|)
function_decl|;
end_function_decl

begin_function_decl
specifier|static
name|gboolean
name|gimp_scale_button_image_draw
parameter_list|(
name|GtkWidget
modifier|*
name|widget
parameter_list|,
name|cairo_t
modifier|*
name|cr
parameter_list|,
name|GimpScaleButton
modifier|*
name|button
parameter_list|)
function_decl|;
end_function_decl

begin_macro
DECL|function|G_DEFINE_TYPE (GimpScaleButton,gimp_scale_button,GTK_TYPE_SCALE_BUTTON)
name|G_DEFINE_TYPE
argument_list|(
argument|GimpScaleButton
argument_list|,
argument|gimp_scale_button
argument_list|,
argument|GTK_TYPE_SCALE_BUTTON
argument_list|)
end_macro

begin_define
DECL|macro|parent_class
define|#
directive|define
name|parent_class
value|gimp_scale_button_parent_class
end_define

begin_function
specifier|static
name|void
name|gimp_scale_button_class_init
parameter_list|(
name|GimpScaleButtonClass
modifier|*
name|klass
parameter_list|)
block|{
name|GtkScaleButtonClass
modifier|*
name|button_class
init|=
name|GTK_SCALE_BUTTON_CLASS
argument_list|(
name|klass
argument_list|)
decl_stmt|;
name|button_class
operator|->
name|value_changed
operator|=
name|gimp_scale_button_value_changed
expr_stmt|;
block|}
end_function

begin_function
specifier|static
name|void
DECL|function|gimp_scale_button_init (GimpScaleButton * button)
name|gimp_scale_button_init
parameter_list|(
name|GimpScaleButton
modifier|*
name|button
parameter_list|)
block|{
name|GtkWidget
modifier|*
name|image
init|=
name|gtk_bin_get_child
argument_list|(
name|GTK_BIN
argument_list|(
name|button
argument_list|)
argument_list|)
decl_stmt|;
name|GtkWidget
modifier|*
name|plusminus
decl_stmt|;
name|plusminus
operator|=
name|gtk_scale_button_get_plus_button
argument_list|(
name|GTK_SCALE_BUTTON
argument_list|(
name|button
argument_list|)
argument_list|)
expr_stmt|;
name|gtk_widget_hide
argument_list|(
name|plusminus
argument_list|)
expr_stmt|;
name|gtk_widget_set_no_show_all
argument_list|(
name|plusminus
argument_list|,
name|TRUE
argument_list|)
expr_stmt|;
name|plusminus
operator|=
name|gtk_scale_button_get_minus_button
argument_list|(
name|GTK_SCALE_BUTTON
argument_list|(
name|button
argument_list|)
argument_list|)
expr_stmt|;
name|gtk_widget_hide
argument_list|(
name|plusminus
argument_list|)
expr_stmt|;
name|gtk_widget_set_no_show_all
argument_list|(
name|plusminus
argument_list|,
name|TRUE
argument_list|)
expr_stmt|;
name|g_signal_connect
argument_list|(
name|image
argument_list|,
literal|"draw"
argument_list|,
name|G_CALLBACK
argument_list|(
name|gimp_scale_button_image_draw
argument_list|)
argument_list|,
name|button
argument_list|)
expr_stmt|;
comment|/* GtkScaleButton doesn't emit "value-changed" when the adjustment changes */
name|g_signal_connect
argument_list|(
name|button
argument_list|,
literal|"notify::adjustment"
argument_list|,
name|G_CALLBACK
argument_list|(
name|gimp_scale_button_update_tooltip
argument_list|)
argument_list|,
name|NULL
argument_list|)
expr_stmt|;
name|gimp_scale_button_update_tooltip
argument_list|(
name|button
argument_list|)
expr_stmt|;
block|}
end_function

begin_function
specifier|static
name|void
DECL|function|gimp_scale_button_value_changed (GtkScaleButton * button,gdouble value)
name|gimp_scale_button_value_changed
parameter_list|(
name|GtkScaleButton
modifier|*
name|button
parameter_list|,
name|gdouble
name|value
parameter_list|)
block|{
if|if
condition|(
name|GTK_SCALE_BUTTON_CLASS
argument_list|(
name|parent_class
argument_list|)
operator|->
name|value_changed
condition|)
name|GTK_SCALE_BUTTON_CLASS
argument_list|(
name|parent_class
argument_list|)
operator|->
name|value_changed
argument_list|(
name|button
argument_list|,
name|value
argument_list|)
expr_stmt|;
name|gimp_scale_button_update_tooltip
argument_list|(
name|GIMP_SCALE_BUTTON
argument_list|(
name|button
argument_list|)
argument_list|)
expr_stmt|;
block|}
end_function

begin_function
specifier|static
name|void
DECL|function|gimp_scale_button_update_tooltip (GimpScaleButton * button)
name|gimp_scale_button_update_tooltip
parameter_list|(
name|GimpScaleButton
modifier|*
name|button
parameter_list|)
block|{
name|GtkAdjustment
modifier|*
name|adj
decl_stmt|;
name|gchar
modifier|*
name|text
decl_stmt|;
name|gdouble
name|value
decl_stmt|;
name|gdouble
name|lower
decl_stmt|;
name|gdouble
name|upper
decl_stmt|;
name|adj
operator|=
name|gtk_scale_button_get_adjustment
argument_list|(
name|GTK_SCALE_BUTTON
argument_list|(
name|button
argument_list|)
argument_list|)
expr_stmt|;
name|value
operator|=
name|gtk_adjustment_get_value
argument_list|(
name|adj
argument_list|)
expr_stmt|;
name|lower
operator|=
name|gtk_adjustment_get_lower
argument_list|(
name|adj
argument_list|)
expr_stmt|;
name|upper
operator|=
name|gtk_adjustment_get_upper
argument_list|(
name|adj
argument_list|)
expr_stmt|;
comment|/*  use U+2009 THIN SPACE to separate the percent sign from the number */
name|text
operator|=
name|g_strdup_printf
argument_list|(
literal|"%d\342\200\211%%"
argument_list|,
call|(
name|gint
call|)
argument_list|(
literal|0.5
operator|+
operator|(
operator|(
name|value
operator|-
name|lower
operator|)
operator|*
literal|100.0
operator|/
operator|(
name|upper
operator|-
name|lower
operator|)
operator|)
argument_list|)
argument_list|)
expr_stmt|;
name|gtk_widget_set_tooltip_text
argument_list|(
name|GTK_WIDGET
argument_list|(
name|button
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
block|}
end_function

begin_function
specifier|static
name|gboolean
DECL|function|gimp_scale_button_image_draw (GtkWidget * widget,cairo_t * cr,GimpScaleButton * button)
name|gimp_scale_button_image_draw
parameter_list|(
name|GtkWidget
modifier|*
name|widget
parameter_list|,
name|cairo_t
modifier|*
name|cr
parameter_list|,
name|GimpScaleButton
modifier|*
name|button
parameter_list|)
block|{
name|GtkStyleContext
modifier|*
name|style
init|=
name|gtk_widget_get_style_context
argument_list|(
name|widget
argument_list|)
decl_stmt|;
name|GtkAllocation
name|allocation
decl_stmt|;
name|GtkAdjustment
modifier|*
name|adj
decl_stmt|;
name|GdkRGBA
name|color
decl_stmt|;
name|gint
name|value
decl_stmt|;
name|gint
name|steps
decl_stmt|;
name|gint
name|i
decl_stmt|;
name|gtk_widget_get_allocation
argument_list|(
name|widget
argument_list|,
operator|&
name|allocation
argument_list|)
expr_stmt|;
name|steps
operator|=
name|MIN
argument_list|(
name|allocation
operator|.
name|width
argument_list|,
name|allocation
operator|.
name|height
argument_list|)
operator|/
literal|2
expr_stmt|;
name|adj
operator|=
name|gtk_scale_button_get_adjustment
argument_list|(
name|GTK_SCALE_BUTTON
argument_list|(
name|button
argument_list|)
argument_list|)
expr_stmt|;
if|if
condition|(
name|steps
operator|<
literal|1
condition|)
return|return
name|TRUE
return|;
name|value
operator|=
literal|0.5
operator|+
operator|(
operator|(
name|gtk_adjustment_get_value
argument_list|(
name|adj
argument_list|)
operator|-
name|gtk_adjustment_get_lower
argument_list|(
name|adj
argument_list|)
operator|)
operator|*
operator|(
name|gdouble
operator|)
name|steps
operator|/
operator|(
name|gtk_adjustment_get_upper
argument_list|(
name|adj
argument_list|)
operator|-
name|gtk_adjustment_get_lower
argument_list|(
name|adj
argument_list|)
operator|)
operator|)
expr_stmt|;
name|cairo_set_line_width
argument_list|(
name|cr
argument_list|,
literal|0.5
argument_list|)
expr_stmt|;
if|if
condition|(
name|gtk_widget_get_direction
argument_list|(
name|widget
argument_list|)
operator|==
name|GTK_TEXT_DIR_RTL
condition|)
block|{
name|cairo_translate
argument_list|(
name|cr
argument_list|,
name|allocation
operator|.
name|width
operator|-
literal|0.5
argument_list|,
name|allocation
operator|.
name|height
argument_list|)
expr_stmt|;
name|cairo_scale
argument_list|(
name|cr
argument_list|,
operator|-
literal|2.0
argument_list|,
operator|-
literal|2.0
argument_list|)
expr_stmt|;
block|}
else|else
block|{
name|cairo_translate
argument_list|(
name|cr
argument_list|,
literal|0.5
argument_list|,
name|allocation
operator|.
name|height
argument_list|)
expr_stmt|;
name|cairo_scale
argument_list|(
name|cr
argument_list|,
literal|2.0
argument_list|,
operator|-
literal|2.0
argument_list|)
expr_stmt|;
block|}
for|for
control|(
name|i
operator|=
literal|0
init|;
name|i
operator|<
name|value
condition|;
name|i
operator|++
control|)
block|{
name|cairo_move_to
argument_list|(
name|cr
argument_list|,
name|i
argument_list|,
literal|0
argument_list|)
expr_stmt|;
name|cairo_line_to
argument_list|(
name|cr
argument_list|,
name|i
argument_list|,
name|i
operator|+
literal|0.5
argument_list|)
expr_stmt|;
block|}
name|gtk_style_context_get_color
argument_list|(
name|style
argument_list|,
name|gtk_widget_get_state_flags
argument_list|(
name|widget
argument_list|)
argument_list|,
operator|&
name|color
argument_list|)
expr_stmt|;
name|gdk_cairo_set_source_rgba
argument_list|(
name|cr
argument_list|,
operator|&
name|color
argument_list|)
expr_stmt|;
name|cairo_stroke
argument_list|(
name|cr
argument_list|)
expr_stmt|;
for|for
control|(
init|;
name|i
operator|<
name|steps
condition|;
name|i
operator|++
control|)
block|{
name|cairo_move_to
argument_list|(
name|cr
argument_list|,
name|i
argument_list|,
literal|0
argument_list|)
expr_stmt|;
name|cairo_line_to
argument_list|(
name|cr
argument_list|,
name|i
argument_list|,
name|i
operator|+
literal|0.5
argument_list|)
expr_stmt|;
block|}
name|gtk_style_context_get_background_color
argument_list|(
name|style
argument_list|,
name|GTK_STATE_FLAG_INSENSITIVE
argument_list|,
operator|&
name|color
argument_list|)
expr_stmt|;
name|gdk_cairo_set_source_rgba
argument_list|(
name|cr
argument_list|,
operator|&
name|color
argument_list|)
expr_stmt|;
name|cairo_stroke
argument_list|(
name|cr
argument_list|)
expr_stmt|;
return|return
name|TRUE
return|;
block|}
end_function

begin_function
name|GtkWidget
modifier|*
DECL|function|gimp_scale_button_new (gdouble value,gdouble min,gdouble max)
name|gimp_scale_button_new
parameter_list|(
name|gdouble
name|value
parameter_list|,
name|gdouble
name|min
parameter_list|,
name|gdouble
name|max
parameter_list|)
block|{
name|GtkAdjustment
modifier|*
name|adj
decl_stmt|;
name|gdouble
name|step
decl_stmt|;
name|g_return_val_if_fail
argument_list|(
name|value
operator|>=
name|min
operator|&&
name|value
operator|<=
name|max
argument_list|,
name|NULL
argument_list|)
expr_stmt|;
name|step
operator|=
operator|(
name|max
operator|-
name|min
operator|)
operator|/
literal|10.0
expr_stmt|;
name|adj
operator|=
name|gtk_adjustment_new
argument_list|(
name|value
argument_list|,
name|min
argument_list|,
name|max
argument_list|,
name|step
argument_list|,
name|step
argument_list|,
literal|0
argument_list|)
expr_stmt|;
return|return
name|g_object_new
argument_list|(
name|GIMP_TYPE_SCALE_BUTTON
argument_list|,
literal|"orientation"
argument_list|,
name|GTK_ORIENTATION_HORIZONTAL
argument_list|,
literal|"adjustment"
argument_list|,
name|adj
argument_list|,
literal|"size"
argument_list|,
name|GTK_ICON_SIZE_MENU
argument_list|,
name|NULL
argument_list|)
return|;
block|}
end_function

end_unit

