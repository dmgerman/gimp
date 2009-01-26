begin_unit|revision:0.9.5;language:C;cregit-version:0.0.1
begin_comment
comment|/* LIBGIMP - The GIMP Library  * Copyright (C) 1995-1997 Peter Mattis and Spencer Kimball  *  * gimpbutton.c  * Copyright (C) 2000-2008 Michael Natterer<mitch@gimp.org>  *  * This library is free software: you can redistribute it and/or  * modify it under the terms of the GNU Lesser General Public  * License as published by the Free Software Foundation; either  * version 3 of the License, or (at your option) any later version.  *  * This library is distributed in the hope that it will be useful,  * but WITHOUT ANY WARRANTY; without even the implied warranty of  * MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the GNU  * Lesser General Public License for more details.  *  * You should have received a copy of the GNU Lesser General Public  * License along with this library.  If not, see  *<http://www.gnu.org/licenses/>.  */
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
file|"gimpwidgetstypes.h"
end_include

begin_include
include|#
directive|include
file|"gimpbutton.h"
end_include

begin_enum
enum|enum
DECL|enum|__anon2ac055070103
block|{
DECL|enumerator|EXTENDED_CLICKED
name|EXTENDED_CLICKED
block|,
DECL|enumerator|LAST_SIGNAL
name|LAST_SIGNAL
block|}
enum|;
end_enum

begin_function_decl
specifier|static
name|gboolean
name|gimp_button_button_press
parameter_list|(
name|GtkWidget
modifier|*
name|widget
parameter_list|,
name|GdkEventButton
modifier|*
name|event
parameter_list|)
function_decl|;
end_function_decl

begin_function_decl
specifier|static
name|void
name|gimp_button_clicked
parameter_list|(
name|GtkButton
modifier|*
name|button
parameter_list|)
function_decl|;
end_function_decl

begin_macro
name|G_DEFINE_TYPE
argument_list|(
argument|GimpButton
argument_list|,
argument|gimp_button
argument_list|,
argument|GTK_TYPE_BUTTON
argument_list|)
end_macro

begin_define
DECL|macro|parent_class
define|#
directive|define
name|parent_class
value|gimp_button_parent_class
end_define

begin_decl_stmt
specifier|static
name|guint
name|button_signals
index|[
name|LAST_SIGNAL
index|]
init|=
block|{
literal|0
block|}
decl_stmt|;
end_decl_stmt

begin_function
specifier|static
name|void
DECL|function|gimp_button_class_init (GimpButtonClass * klass)
name|gimp_button_class_init
parameter_list|(
name|GimpButtonClass
modifier|*
name|klass
parameter_list|)
block|{
name|GtkWidgetClass
modifier|*
name|widget_class
init|=
name|GTK_WIDGET_CLASS
argument_list|(
name|klass
argument_list|)
decl_stmt|;
name|GtkButtonClass
modifier|*
name|button_class
init|=
name|GTK_BUTTON_CLASS
argument_list|(
name|klass
argument_list|)
decl_stmt|;
name|button_signals
index|[
name|EXTENDED_CLICKED
index|]
operator|=
name|g_signal_new
argument_list|(
literal|"extended-clicked"
argument_list|,
name|G_TYPE_FROM_CLASS
argument_list|(
name|klass
argument_list|)
argument_list|,
name|G_SIGNAL_RUN_FIRST
argument_list|,
name|G_STRUCT_OFFSET
argument_list|(
name|GimpButtonClass
argument_list|,
name|extended_clicked
argument_list|)
argument_list|,
name|NULL
argument_list|,
name|NULL
argument_list|,
name|g_cclosure_marshal_VOID__FLAGS
argument_list|,
name|G_TYPE_NONE
argument_list|,
literal|1
argument_list|,
name|GDK_TYPE_MODIFIER_TYPE
argument_list|)
expr_stmt|;
name|widget_class
operator|->
name|button_press_event
operator|=
name|gimp_button_button_press
expr_stmt|;
name|button_class
operator|->
name|clicked
operator|=
name|gimp_button_clicked
expr_stmt|;
block|}
end_function

begin_function
specifier|static
name|void
DECL|function|gimp_button_init (GimpButton * button)
name|gimp_button_init
parameter_list|(
name|GimpButton
modifier|*
name|button
parameter_list|)
block|{
name|button
operator|->
name|press_state
operator|=
literal|0
expr_stmt|;
block|}
end_function

begin_comment
comment|/**  * gimp_button_new:  *  * Creates a new #GimpButton widget.  *  * Returns: A pointer to the new #GimpButton widget.  **/
end_comment

begin_function
name|GtkWidget
modifier|*
DECL|function|gimp_button_new (void)
name|gimp_button_new
parameter_list|(
name|void
parameter_list|)
block|{
return|return
name|g_object_new
argument_list|(
name|GIMP_TYPE_BUTTON
argument_list|,
name|NULL
argument_list|)
return|;
block|}
end_function

begin_comment
comment|/**  * gimp_button_extended_clicked:  * @button: a #GimpButton.  * @state:  a state as found in #GdkEventButton->state, e.g. #GDK_SHIFT_MASK.  *  * Emits the button's "extended_clicked" signal.  **/
end_comment

begin_function
name|void
DECL|function|gimp_button_extended_clicked (GimpButton * button,GdkModifierType state)
name|gimp_button_extended_clicked
parameter_list|(
name|GimpButton
modifier|*
name|button
parameter_list|,
name|GdkModifierType
name|state
parameter_list|)
block|{
name|g_return_if_fail
argument_list|(
name|GIMP_IS_BUTTON
argument_list|(
name|button
argument_list|)
argument_list|)
expr_stmt|;
name|g_signal_emit
argument_list|(
name|button
argument_list|,
name|button_signals
index|[
name|EXTENDED_CLICKED
index|]
argument_list|,
literal|0
argument_list|,
name|state
argument_list|)
expr_stmt|;
block|}
end_function

begin_function
specifier|static
name|gboolean
DECL|function|gimp_button_button_press (GtkWidget * widget,GdkEventButton * bevent)
name|gimp_button_button_press
parameter_list|(
name|GtkWidget
modifier|*
name|widget
parameter_list|,
name|GdkEventButton
modifier|*
name|bevent
parameter_list|)
block|{
name|GimpButton
modifier|*
name|button
init|=
name|GIMP_BUTTON
argument_list|(
name|widget
argument_list|)
decl_stmt|;
if|if
condition|(
name|bevent
operator|->
name|button
operator|==
literal|1
condition|)
block|{
name|button
operator|->
name|press_state
operator|=
name|bevent
operator|->
name|state
expr_stmt|;
block|}
else|else
block|{
name|button
operator|->
name|press_state
operator|=
literal|0
expr_stmt|;
block|}
return|return
name|GTK_WIDGET_CLASS
argument_list|(
name|parent_class
argument_list|)
operator|->
name|button_press_event
argument_list|(
name|widget
argument_list|,
name|bevent
argument_list|)
return|;
block|}
end_function

begin_function
specifier|static
name|void
DECL|function|gimp_button_clicked (GtkButton * button)
name|gimp_button_clicked
parameter_list|(
name|GtkButton
modifier|*
name|button
parameter_list|)
block|{
if|if
condition|(
name|GIMP_BUTTON
argument_list|(
name|button
argument_list|)
operator|->
name|press_state
operator|&
operator|(
name|GDK_SHIFT_MASK
operator||
name|GDK_CONTROL_MASK
operator||
name|GDK_MOD1_MASK
operator|)
condition|)
block|{
name|g_signal_stop_emission_by_name
argument_list|(
name|button
argument_list|,
literal|"clicked"
argument_list|)
expr_stmt|;
name|gimp_button_extended_clicked
argument_list|(
name|GIMP_BUTTON
argument_list|(
name|button
argument_list|)
argument_list|,
name|GIMP_BUTTON
argument_list|(
name|button
argument_list|)
operator|->
name|press_state
argument_list|)
expr_stmt|;
block|}
elseif|else
if|if
condition|(
name|GTK_BUTTON_CLASS
argument_list|(
name|parent_class
argument_list|)
operator|->
name|clicked
condition|)
block|{
name|GTK_BUTTON_CLASS
argument_list|(
name|parent_class
argument_list|)
operator|->
name|clicked
argument_list|(
name|button
argument_list|)
expr_stmt|;
block|}
block|}
end_function

end_unit

