begin_unit|revision:0.9.5;language:C;cregit-version:0.0.1
begin_comment
comment|/* LIBGIMP - The GIMP Library   * Copyright (C) 1995-1997 Peter Mattis and Spencer Kimball   *  * gimpbutton.c  * Copyright (C) 2000 Michael Natterer<mitch@gimp.org>  *  * This library is free software; you can redistribute it and/or  * modify it under the terms of the GNU Lesser General Public  * License as published by the Free Software Foundation; either  * version 2 of the License, or (at your option) any later version.  *   * This library is distributed in the hope that it will be useful,  * but WITHOUT ANY WARRANTY; without even the implied warranty of  * MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the GNU  * Lesser General Public License for more details.  *  * You should have received a copy of the GNU Lesser General Public  * License along with this library; if not, write to the  * Free Software Foundation, Inc., 59 Temple Place - Suite 330,  * Boston, MA 02111-1307, USA.  */
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
DECL|enum|__anon2acd67880103
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
name|void
name|gimp_button_class_init
parameter_list|(
name|GimpButtonClass
modifier|*
name|klass
parameter_list|)
function_decl|;
end_function_decl

begin_function_decl
specifier|static
name|void
name|gimp_button_init
parameter_list|(
name|GimpButton
modifier|*
name|button
parameter_list|)
function_decl|;
end_function_decl

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
name|gboolean
name|gimp_button_button_release
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

begin_decl_stmt
DECL|variable|button_signals
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

begin_decl_stmt
DECL|variable|parent_class
specifier|static
name|GtkButtonClass
modifier|*
name|parent_class
init|=
name|NULL
decl_stmt|;
end_decl_stmt

begin_function
name|GtkType
DECL|function|gimp_button_get_type (void)
name|gimp_button_get_type
parameter_list|(
name|void
parameter_list|)
block|{
specifier|static
name|guint
name|button_type
init|=
literal|0
decl_stmt|;
if|if
condition|(
operator|!
name|button_type
condition|)
block|{
name|GtkTypeInfo
name|button_info
init|=
block|{
literal|"GimpButton"
block|,
sizeof|sizeof
argument_list|(
name|GimpButton
argument_list|)
block|,
sizeof|sizeof
argument_list|(
name|GimpButtonClass
argument_list|)
block|,
operator|(
name|GtkClassInitFunc
operator|)
name|gimp_button_class_init
block|,
operator|(
name|GtkObjectInitFunc
operator|)
name|gimp_button_init
block|,
comment|/* reserved_1 */
name|NULL
block|,
comment|/* reserved_2 */
name|NULL
block|,
operator|(
name|GtkClassInitFunc
operator|)
name|NULL
block|}
decl_stmt|;
name|button_type
operator|=
name|gtk_type_unique
argument_list|(
name|GTK_TYPE_BUTTON
argument_list|,
operator|&
name|button_info
argument_list|)
expr_stmt|;
block|}
return|return
name|button_type
return|;
block|}
end_function

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
name|GObjectClass
modifier|*
name|object_class
decl_stmt|;
name|GtkWidgetClass
modifier|*
name|widget_class
decl_stmt|;
name|object_class
operator|=
operator|(
name|GObjectClass
operator|*
operator|)
name|klass
expr_stmt|;
name|widget_class
operator|=
operator|(
name|GtkWidgetClass
operator|*
operator|)
name|klass
expr_stmt|;
name|parent_class
operator|=
name|g_type_class_peek_parent
argument_list|(
name|klass
argument_list|)
expr_stmt|;
name|button_signals
index|[
name|EXTENDED_CLICKED
index|]
operator|=
name|g_signal_new
argument_list|(
literal|"extended_clicked"
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
name|g_cclosure_marshal_VOID__UINT
argument_list|,
name|G_TYPE_NONE
argument_list|,
literal|1
argument_list|,
name|G_TYPE_UINT
argument_list|)
expr_stmt|;
name|widget_class
operator|->
name|button_press_event
operator|=
name|gimp_button_button_press
expr_stmt|;
name|widget_class
operator|->
name|button_release_event
operator|=
name|gimp_button_button_release
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
name|GimpButton
modifier|*
name|button
decl_stmt|;
name|button
operator|=
name|gtk_type_new
argument_list|(
name|GIMP_TYPE_BUTTON
argument_list|)
expr_stmt|;
return|return
name|GTK_WIDGET
argument_list|(
name|button
argument_list|)
return|;
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
name|g_return_val_if_fail
argument_list|(
name|widget
operator|!=
name|NULL
argument_list|,
name|FALSE
argument_list|)
expr_stmt|;
name|g_return_val_if_fail
argument_list|(
name|GIMP_IS_BUTTON
argument_list|(
name|widget
argument_list|)
argument_list|,
name|FALSE
argument_list|)
expr_stmt|;
name|g_return_val_if_fail
argument_list|(
name|bevent
operator|!=
name|NULL
argument_list|,
name|FALSE
argument_list|)
expr_stmt|;
if|if
condition|(
name|bevent
operator|->
name|type
operator|==
name|GDK_BUTTON_PRESS
operator|&&
name|bevent
operator|->
name|button
operator|==
literal|1
condition|)
block|{
name|GimpButton
modifier|*
name|button
decl_stmt|;
name|button
operator|=
name|GIMP_BUTTON
argument_list|(
name|widget
argument_list|)
expr_stmt|;
name|button
operator|->
name|press_state
operator|=
name|bevent
operator|->
name|state
expr_stmt|;
block|}
if|if
condition|(
name|GTK_WIDGET_CLASS
argument_list|(
name|parent_class
argument_list|)
operator|->
name|button_press_event
condition|)
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
return|return
name|TRUE
return|;
block|}
end_function

begin_function
specifier|static
name|gint
DECL|function|gimp_button_button_release (GtkWidget * widget,GdkEventButton * bevent)
name|gimp_button_button_release
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
name|GtkButton
modifier|*
name|button
decl_stmt|;
name|gboolean
name|extended_clicked
init|=
name|FALSE
decl_stmt|;
name|gboolean
name|retval
init|=
name|TRUE
decl_stmt|;
name|g_return_val_if_fail
argument_list|(
name|widget
operator|!=
name|NULL
argument_list|,
name|FALSE
argument_list|)
expr_stmt|;
name|g_return_val_if_fail
argument_list|(
name|GIMP_IS_BUTTON
argument_list|(
name|widget
argument_list|)
argument_list|,
name|FALSE
argument_list|)
expr_stmt|;
name|g_return_val_if_fail
argument_list|(
name|bevent
operator|!=
name|NULL
argument_list|,
name|FALSE
argument_list|)
expr_stmt|;
name|button
operator|=
name|GTK_BUTTON
argument_list|(
name|widget
argument_list|)
expr_stmt|;
if|if
condition|(
name|bevent
operator|->
name|button
operator|==
literal|1
condition|)
block|{
if|if
condition|(
name|button
operator|->
name|in_button
operator|&&
operator|(
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
operator|)
condition|)
block|{
name|gtk_signal_emit
argument_list|(
name|GTK_OBJECT
argument_list|(
name|widget
argument_list|)
argument_list|,
name|button_signals
index|[
name|EXTENDED_CLICKED
index|]
argument_list|,
name|GIMP_BUTTON
argument_list|(
name|button
argument_list|)
operator|->
name|press_state
argument_list|)
expr_stmt|;
name|extended_clicked
operator|=
name|TRUE
expr_stmt|;
comment|/* HACK: don't let GtkButton emit "clicked" by telling it that 	   * the mouse pointer is outside the widget 	   */
name|button
operator|->
name|in_button
operator|=
name|FALSE
expr_stmt|;
block|}
block|}
if|if
condition|(
name|GTK_WIDGET_CLASS
argument_list|(
name|parent_class
argument_list|)
operator|->
name|button_release_event
condition|)
name|retval
operator|=
name|GTK_WIDGET_CLASS
argument_list|(
name|parent_class
argument_list|)
operator|->
name|button_release_event
argument_list|(
name|widget
argument_list|,
name|bevent
argument_list|)
expr_stmt|;
if|if
condition|(
name|extended_clicked
condition|)
block|{
comment|/* revert the above HACK and let the button draw itself in the        * correct state, because upchaining with "in_button" == FALSE        * messed it up        */
name|button
operator|->
name|in_button
operator|=
name|TRUE
expr_stmt|;
name|gtk_widget_set_state
argument_list|(
name|widget
argument_list|,
name|GTK_STATE_PRELIGHT
argument_list|)
expr_stmt|;
name|gtk_widget_draw
argument_list|(
name|widget
argument_list|,
name|NULL
argument_list|)
expr_stmt|;
block|}
return|return
name|retval
return|;
block|}
end_function

end_unit

