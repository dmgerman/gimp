begin_unit|revision:0.9.5;language:C;cregit-version:0.0.1
begin_comment
comment|/* LIBGIMP - The GIMP Library  * Copyright (C) 1995-1997 Peter Mattis and Spencer Kimball  *  * gimpchainbutton.c  * Copyright (C) 1999-2000 Sven Neumann<sven@gimp.org>  *  * This library is free software; you can redistribute it and/or  * modify it under the terms of the GNU Lesser General Public  * License as published by the Free Software Foundation; either  * version 2 of the License, or (at your option) any later version.  *  * This library is distributed in the hope that it will be useful,  * but WITHOUT ANY WARRANTY; without even the implied warranty of  * MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the GNU  * Library General Public License for more details.  *  * You should have received a copy of the GNU Lesser General Public  * License along with this library; if not, write to the  * Free Software Foundation, Inc., 59 Temple Place - Suite 330,  * Boston, MA 02111-1307, USA.  */
end_comment

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
file|"gimpchainbutton.h"
end_include

begin_include
include|#
directive|include
file|"gimpstock.h"
end_include

begin_enum
enum|enum
DECL|enum|__anon2b885caf0103
block|{
DECL|enumerator|TOGGLED
name|TOGGLED
block|,
DECL|enumerator|LAST_SIGNAL
name|LAST_SIGNAL
block|}
enum|;
end_enum

begin_function_decl
specifier|static
name|void
name|gimp_chain_button_class_init
parameter_list|(
name|GimpChainButtonClass
modifier|*
name|klass
parameter_list|)
function_decl|;
end_function_decl

begin_function_decl
specifier|static
name|void
name|gimp_chain_button_init
parameter_list|(
name|GimpChainButton
modifier|*
name|button
parameter_list|)
function_decl|;
end_function_decl

begin_function_decl
specifier|static
name|void
name|gimp_chain_button_clicked_callback
parameter_list|(
name|GtkWidget
modifier|*
name|widget
parameter_list|,
name|GimpChainButton
modifier|*
name|button
parameter_list|)
function_decl|;
end_function_decl

begin_function_decl
specifier|static
name|gboolean
name|gimp_chain_button_draw_lines
parameter_list|(
name|GtkWidget
modifier|*
name|widget
parameter_list|,
name|GdkEventExpose
modifier|*
name|eevent
parameter_list|,
name|GimpChainButton
modifier|*
name|button
parameter_list|)
function_decl|;
end_function_decl

begin_decl_stmt
DECL|variable|gimp_chain_stock_items
specifier|static
specifier|const
name|gchar
modifier|*
name|gimp_chain_stock_items
index|[]
init|=
block|{
name|GIMP_STOCK_HCHAIN
block|,
name|GIMP_STOCK_HCHAIN_BROKEN
block|,
name|GIMP_STOCK_VCHAIN
block|,
name|GIMP_STOCK_VCHAIN_BROKEN
block|}
decl_stmt|;
end_decl_stmt

begin_decl_stmt
DECL|variable|gimp_chain_button_signals
specifier|static
name|guint
name|gimp_chain_button_signals
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
name|GtkTableClass
modifier|*
name|parent_class
init|=
name|NULL
decl_stmt|;
end_decl_stmt

begin_function
name|GType
DECL|function|gimp_chain_button_get_type (void)
name|gimp_chain_button_get_type
parameter_list|(
name|void
parameter_list|)
block|{
specifier|static
name|GType
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
specifier|static
specifier|const
name|GTypeInfo
name|button_info
init|=
block|{
sizeof|sizeof
argument_list|(
name|GimpChainButtonClass
argument_list|)
block|,
name|NULL
block|,
comment|/* base_init      */
name|NULL
block|,
comment|/* base_finalize  */
operator|(
name|GClassInitFunc
operator|)
name|gimp_chain_button_class_init
block|,
name|NULL
block|,
comment|/* class_finalize */
name|NULL
block|,
comment|/* class_data     */
sizeof|sizeof
argument_list|(
name|GimpChainButton
argument_list|)
block|,
literal|0
block|,
comment|/* n_preallocs    */
operator|(
name|GInstanceInitFunc
operator|)
name|gimp_chain_button_init
block|,       }
decl_stmt|;
name|button_type
operator|=
name|g_type_register_static
argument_list|(
name|GTK_TYPE_TABLE
argument_list|,
literal|"GimpChainButton"
argument_list|,
operator|&
name|button_info
argument_list|,
literal|0
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
DECL|function|gimp_chain_button_class_init (GimpChainButtonClass * klass)
name|gimp_chain_button_class_init
parameter_list|(
name|GimpChainButtonClass
modifier|*
name|klass
parameter_list|)
block|{
name|parent_class
operator|=
name|g_type_class_peek_parent
argument_list|(
name|klass
argument_list|)
expr_stmt|;
name|gimp_chain_button_signals
index|[
name|TOGGLED
index|]
operator|=
name|g_signal_new
argument_list|(
literal|"toggled"
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
name|GimpChainButtonClass
argument_list|,
name|toggled
argument_list|)
argument_list|,
name|NULL
argument_list|,
name|NULL
argument_list|,
name|g_cclosure_marshal_VOID__VOID
argument_list|,
name|G_TYPE_NONE
argument_list|,
literal|0
argument_list|)
expr_stmt|;
name|klass
operator|->
name|toggled
operator|=
name|NULL
expr_stmt|;
block|}
end_function

begin_function
specifier|static
name|void
DECL|function|gimp_chain_button_init (GimpChainButton * button)
name|gimp_chain_button_init
parameter_list|(
name|GimpChainButton
modifier|*
name|button
parameter_list|)
block|{
name|button
operator|->
name|position
operator|=
name|GIMP_CHAIN_TOP
expr_stmt|;
name|button
operator|->
name|active
operator|=
name|FALSE
expr_stmt|;
name|button
operator|->
name|line1
operator|=
name|gtk_drawing_area_new
argument_list|()
expr_stmt|;
name|button
operator|->
name|line2
operator|=
name|gtk_drawing_area_new
argument_list|()
expr_stmt|;
name|button
operator|->
name|image
operator|=
name|gtk_image_new
argument_list|()
expr_stmt|;
name|button
operator|->
name|button
operator|=
name|gtk_button_new
argument_list|()
expr_stmt|;
name|gtk_button_set_relief
argument_list|(
name|GTK_BUTTON
argument_list|(
name|button
operator|->
name|button
argument_list|)
argument_list|,
name|GTK_RELIEF_NONE
argument_list|)
expr_stmt|;
name|gtk_container_add
argument_list|(
name|GTK_CONTAINER
argument_list|(
name|button
operator|->
name|button
argument_list|)
argument_list|,
name|button
operator|->
name|image
argument_list|)
expr_stmt|;
name|gtk_widget_show
argument_list|(
name|button
operator|->
name|image
argument_list|)
expr_stmt|;
name|g_signal_connect
argument_list|(
name|button
operator|->
name|button
argument_list|,
literal|"clicked"
argument_list|,
name|G_CALLBACK
argument_list|(
name|gimp_chain_button_clicked_callback
argument_list|)
argument_list|,
name|button
argument_list|)
expr_stmt|;
name|g_signal_connect
argument_list|(
name|button
operator|->
name|line1
argument_list|,
literal|"expose-event"
argument_list|,
name|G_CALLBACK
argument_list|(
name|gimp_chain_button_draw_lines
argument_list|)
argument_list|,
name|button
argument_list|)
expr_stmt|;
name|g_signal_connect
argument_list|(
name|button
operator|->
name|line2
argument_list|,
literal|"expose-event"
argument_list|,
name|G_CALLBACK
argument_list|(
name|gimp_chain_button_draw_lines
argument_list|)
argument_list|,
name|button
argument_list|)
expr_stmt|;
block|}
end_function

begin_comment
comment|/**  * gimp_chain_button_new:  * @position: The position you are going to use for the button  *            with respect to the widgets you want to chain.  *  * Creates a new #GimpChainButton widget.  *  * This returns a button showing either a broken or a linked chain and  * small clamps attached to both sides that visually group the two widgets  * you want to connect. This widget looks best when attached  * to a table taking up two columns (or rows respectively) next  * to the widgets that it is supposed to connect. It may work  * for more than two widgets, but the look is optimized for two.  *  * Returns: Pointer to the new #GimpChainButton, which is inactive  *          by default. Use gimp_chain_button_set_active() to  *          change its state.  */
end_comment

begin_function
name|GtkWidget
modifier|*
DECL|function|gimp_chain_button_new (GimpChainPosition position)
name|gimp_chain_button_new
parameter_list|(
name|GimpChainPosition
name|position
parameter_list|)
block|{
name|GimpChainButton
modifier|*
name|button
decl_stmt|;
name|button
operator|=
name|g_object_new
argument_list|(
name|GIMP_TYPE_CHAIN_BUTTON
argument_list|,
name|NULL
argument_list|)
expr_stmt|;
name|button
operator|->
name|position
operator|=
name|position
expr_stmt|;
name|gtk_image_set_from_stock
argument_list|(
name|GTK_IMAGE
argument_list|(
name|button
operator|->
name|image
argument_list|)
argument_list|,
name|gimp_chain_stock_items
index|[
operator|(
operator|(
name|position
operator|&
name|GIMP_CHAIN_LEFT
operator|)
operator|<<
literal|1
operator|)
operator|+
operator|!
name|button
operator|->
name|active
index|]
argument_list|,
name|GTK_ICON_SIZE_BUTTON
argument_list|)
expr_stmt|;
if|if
condition|(
name|position
operator|&
name|GIMP_CHAIN_LEFT
condition|)
comment|/* are we a vertical chainbutton? */
block|{
name|gtk_table_resize
argument_list|(
name|GTK_TABLE
argument_list|(
name|button
argument_list|)
argument_list|,
literal|3
argument_list|,
literal|1
argument_list|)
expr_stmt|;
name|gtk_table_attach
argument_list|(
name|GTK_TABLE
argument_list|(
name|button
argument_list|)
argument_list|,
name|button
operator|->
name|button
argument_list|,
literal|0
argument_list|,
literal|1
argument_list|,
literal|1
argument_list|,
literal|2
argument_list|,
name|GTK_SHRINK
argument_list|,
name|GTK_SHRINK
argument_list|,
literal|0
argument_list|,
literal|0
argument_list|)
expr_stmt|;
name|gtk_table_attach_defaults
argument_list|(
name|GTK_TABLE
argument_list|(
name|button
argument_list|)
argument_list|,
name|button
operator|->
name|line1
argument_list|,
literal|0
argument_list|,
literal|1
argument_list|,
literal|0
argument_list|,
literal|1
argument_list|)
expr_stmt|;
name|gtk_table_attach_defaults
argument_list|(
name|GTK_TABLE
argument_list|(
name|button
argument_list|)
argument_list|,
name|button
operator|->
name|line2
argument_list|,
literal|0
argument_list|,
literal|1
argument_list|,
literal|2
argument_list|,
literal|3
argument_list|)
expr_stmt|;
block|}
else|else
block|{
name|gtk_table_resize
argument_list|(
name|GTK_TABLE
argument_list|(
name|button
argument_list|)
argument_list|,
literal|1
argument_list|,
literal|3
argument_list|)
expr_stmt|;
name|gtk_table_attach
argument_list|(
name|GTK_TABLE
argument_list|(
name|button
argument_list|)
argument_list|,
name|button
operator|->
name|button
argument_list|,
literal|1
argument_list|,
literal|2
argument_list|,
literal|0
argument_list|,
literal|1
argument_list|,
name|GTK_SHRINK
argument_list|,
name|GTK_SHRINK
argument_list|,
literal|0
argument_list|,
literal|0
argument_list|)
expr_stmt|;
name|gtk_table_attach_defaults
argument_list|(
name|GTK_TABLE
argument_list|(
name|button
argument_list|)
argument_list|,
name|button
operator|->
name|line1
argument_list|,
literal|0
argument_list|,
literal|1
argument_list|,
literal|0
argument_list|,
literal|1
argument_list|)
expr_stmt|;
name|gtk_table_attach_defaults
argument_list|(
name|GTK_TABLE
argument_list|(
name|button
argument_list|)
argument_list|,
name|button
operator|->
name|line2
argument_list|,
literal|2
argument_list|,
literal|3
argument_list|,
literal|0
argument_list|,
literal|1
argument_list|)
expr_stmt|;
block|}
name|gtk_widget_show
argument_list|(
name|button
operator|->
name|button
argument_list|)
expr_stmt|;
name|gtk_widget_show
argument_list|(
name|button
operator|->
name|line1
argument_list|)
expr_stmt|;
name|gtk_widget_show
argument_list|(
name|button
operator|->
name|line2
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

begin_comment
comment|/**  * gimp_chain_button_set_active:  * @button: Pointer to a #GimpChainButton.  * @active: The new state.  *  * Sets the state of the #GimpChainButton to be either locked (%TRUE) or  * unlocked (%FALSE) and changes the showed pixmap to reflect the new state.  */
end_comment

begin_function
name|void
DECL|function|gimp_chain_button_set_active (GimpChainButton * button,gboolean active)
name|gimp_chain_button_set_active
parameter_list|(
name|GimpChainButton
modifier|*
name|button
parameter_list|,
name|gboolean
name|active
parameter_list|)
block|{
name|g_return_if_fail
argument_list|(
name|GIMP_IS_CHAIN_BUTTON
argument_list|(
name|button
argument_list|)
argument_list|)
expr_stmt|;
if|if
condition|(
name|button
operator|->
name|active
operator|!=
name|active
condition|)
block|{
name|guint
name|num
decl_stmt|;
name|button
operator|->
name|active
operator|=
name|active
condition|?
name|TRUE
else|:
name|FALSE
expr_stmt|;
name|num
operator|=
operator|(
operator|(
name|button
operator|->
name|position
operator|&
name|GIMP_CHAIN_LEFT
operator|)
operator|<<
literal|1
operator|)
operator|+
operator|(
name|active
condition|?
literal|0
else|:
literal|1
operator|)
expr_stmt|;
name|gtk_image_set_from_stock
argument_list|(
name|GTK_IMAGE
argument_list|(
name|button
operator|->
name|image
argument_list|)
argument_list|,
name|gimp_chain_stock_items
index|[
name|num
index|]
argument_list|,
name|GTK_ICON_SIZE_BUTTON
argument_list|)
expr_stmt|;
block|}
block|}
end_function

begin_comment
comment|/**  * gimp_chain_button_get_active  * @button: Pointer to a #GimpChainButton.  *  * Checks the state of the #GimpChainButton.  *  * Returns: %TRUE if the #GimpChainButton is active (locked).  */
end_comment

begin_function
name|gboolean
DECL|function|gimp_chain_button_get_active (GimpChainButton * button)
name|gimp_chain_button_get_active
parameter_list|(
name|GimpChainButton
modifier|*
name|button
parameter_list|)
block|{
name|g_return_val_if_fail
argument_list|(
name|GIMP_IS_CHAIN_BUTTON
argument_list|(
name|button
argument_list|)
argument_list|,
name|FALSE
argument_list|)
expr_stmt|;
return|return
name|button
operator|->
name|active
return|;
block|}
end_function

begin_function
specifier|static
name|void
DECL|function|gimp_chain_button_clicked_callback (GtkWidget * widget,GimpChainButton * button)
name|gimp_chain_button_clicked_callback
parameter_list|(
name|GtkWidget
modifier|*
name|widget
parameter_list|,
name|GimpChainButton
modifier|*
name|button
parameter_list|)
block|{
name|g_return_if_fail
argument_list|(
name|GIMP_IS_CHAIN_BUTTON
argument_list|(
name|button
argument_list|)
argument_list|)
expr_stmt|;
name|gimp_chain_button_set_active
argument_list|(
name|button
argument_list|,
operator|!
name|button
operator|->
name|active
argument_list|)
expr_stmt|;
name|g_signal_emit
argument_list|(
name|button
argument_list|,
name|gimp_chain_button_signals
index|[
name|TOGGLED
index|]
argument_list|,
literal|0
argument_list|)
expr_stmt|;
block|}
end_function

begin_function
specifier|static
name|gboolean
DECL|function|gimp_chain_button_draw_lines (GtkWidget * widget,GdkEventExpose * eevent,GimpChainButton * button)
name|gimp_chain_button_draw_lines
parameter_list|(
name|GtkWidget
modifier|*
name|widget
parameter_list|,
name|GdkEventExpose
modifier|*
name|eevent
parameter_list|,
name|GimpChainButton
modifier|*
name|button
parameter_list|)
block|{
name|GdkPoint
name|points
index|[
literal|3
index|]
decl_stmt|;
name|GdkPoint
name|buf
decl_stmt|;
name|GtkShadowType
name|shadow
decl_stmt|;
name|GimpChainPosition
name|position
decl_stmt|;
name|gint
name|which_line
decl_stmt|;
DECL|macro|SHORT_LINE
define|#
directive|define
name|SHORT_LINE
value|4
comment|/* don't set this too high, there's no check against drawing outside      the widgets bounds yet (and probably never will be) */
name|g_return_val_if_fail
argument_list|(
name|GIMP_IS_CHAIN_BUTTON
argument_list|(
name|button
argument_list|)
argument_list|,
name|FALSE
argument_list|)
expr_stmt|;
name|points
index|[
literal|0
index|]
operator|.
name|x
operator|=
name|widget
operator|->
name|allocation
operator|.
name|width
operator|/
literal|2
expr_stmt|;
name|points
index|[
literal|0
index|]
operator|.
name|y
operator|=
name|widget
operator|->
name|allocation
operator|.
name|height
operator|/
literal|2
expr_stmt|;
name|which_line
operator|=
operator|(
name|widget
operator|==
name|button
operator|->
name|line1
operator|)
condition|?
literal|1
else|:
operator|-
literal|1
expr_stmt|;
name|position
operator|=
name|button
operator|->
name|position
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
switch|switch
condition|(
name|position
condition|)
block|{
case|case
name|GIMP_CHAIN_LEFT
case|:
name|position
operator|=
name|GIMP_CHAIN_RIGHT
expr_stmt|;
break|break;
case|case
name|GIMP_CHAIN_RIGHT
case|:
name|position
operator|=
name|GIMP_CHAIN_LEFT
expr_stmt|;
break|break;
default|default:
break|break;
block|}
switch|switch
condition|(
name|position
condition|)
block|{
case|case
name|GIMP_CHAIN_LEFT
case|:
name|points
index|[
literal|0
index|]
operator|.
name|x
operator|+=
name|SHORT_LINE
expr_stmt|;
name|points
index|[
literal|1
index|]
operator|.
name|x
operator|=
name|points
index|[
literal|0
index|]
operator|.
name|x
operator|-
name|SHORT_LINE
expr_stmt|;
name|points
index|[
literal|1
index|]
operator|.
name|y
operator|=
name|points
index|[
literal|0
index|]
operator|.
name|y
expr_stmt|;
name|points
index|[
literal|2
index|]
operator|.
name|x
operator|=
name|points
index|[
literal|1
index|]
operator|.
name|x
expr_stmt|;
name|points
index|[
literal|2
index|]
operator|.
name|y
operator|=
operator|(
name|which_line
operator|==
literal|1
operator|)
condition|?
name|widget
operator|->
name|allocation
operator|.
name|height
operator|-
literal|1
else|:
literal|0
expr_stmt|;
name|shadow
operator|=
name|GTK_SHADOW_ETCHED_IN
expr_stmt|;
break|break;
case|case
name|GIMP_CHAIN_RIGHT
case|:
name|points
index|[
literal|0
index|]
operator|.
name|x
operator|-=
name|SHORT_LINE
expr_stmt|;
name|points
index|[
literal|1
index|]
operator|.
name|x
operator|=
name|points
index|[
literal|0
index|]
operator|.
name|x
operator|+
name|SHORT_LINE
expr_stmt|;
name|points
index|[
literal|1
index|]
operator|.
name|y
operator|=
name|points
index|[
literal|0
index|]
operator|.
name|y
expr_stmt|;
name|points
index|[
literal|2
index|]
operator|.
name|x
operator|=
name|points
index|[
literal|1
index|]
operator|.
name|x
expr_stmt|;
name|points
index|[
literal|2
index|]
operator|.
name|y
operator|=
operator|(
name|which_line
operator|==
literal|1
operator|)
condition|?
name|widget
operator|->
name|allocation
operator|.
name|height
operator|-
literal|1
else|:
literal|0
expr_stmt|;
name|shadow
operator|=
name|GTK_SHADOW_ETCHED_OUT
expr_stmt|;
break|break;
case|case
name|GIMP_CHAIN_TOP
case|:
name|points
index|[
literal|0
index|]
operator|.
name|y
operator|+=
name|SHORT_LINE
expr_stmt|;
name|points
index|[
literal|1
index|]
operator|.
name|x
operator|=
name|points
index|[
literal|0
index|]
operator|.
name|x
expr_stmt|;
name|points
index|[
literal|1
index|]
operator|.
name|y
operator|=
name|points
index|[
literal|0
index|]
operator|.
name|y
operator|-
name|SHORT_LINE
expr_stmt|;
name|points
index|[
literal|2
index|]
operator|.
name|x
operator|=
operator|(
name|which_line
operator|==
literal|1
operator|)
condition|?
name|widget
operator|->
name|allocation
operator|.
name|width
operator|-
literal|1
else|:
literal|0
expr_stmt|;
name|points
index|[
literal|2
index|]
operator|.
name|y
operator|=
name|points
index|[
literal|1
index|]
operator|.
name|y
expr_stmt|;
name|shadow
operator|=
name|GTK_SHADOW_ETCHED_OUT
expr_stmt|;
break|break;
case|case
name|GIMP_CHAIN_BOTTOM
case|:
name|points
index|[
literal|0
index|]
operator|.
name|y
operator|-=
name|SHORT_LINE
expr_stmt|;
name|points
index|[
literal|1
index|]
operator|.
name|x
operator|=
name|points
index|[
literal|0
index|]
operator|.
name|x
expr_stmt|;
name|points
index|[
literal|1
index|]
operator|.
name|y
operator|=
name|points
index|[
literal|0
index|]
operator|.
name|y
operator|+
name|SHORT_LINE
expr_stmt|;
name|points
index|[
literal|2
index|]
operator|.
name|x
operator|=
operator|(
name|which_line
operator|==
literal|1
operator|)
condition|?
name|widget
operator|->
name|allocation
operator|.
name|width
operator|-
literal|1
else|:
literal|0
expr_stmt|;
name|points
index|[
literal|2
index|]
operator|.
name|y
operator|=
name|points
index|[
literal|1
index|]
operator|.
name|y
expr_stmt|;
name|shadow
operator|=
name|GTK_SHADOW_ETCHED_IN
expr_stmt|;
break|break;
default|default:
return|return
name|FALSE
return|;
block|}
if|if
condition|(
operator|(
operator|(
name|shadow
operator|==
name|GTK_SHADOW_ETCHED_OUT
operator|)
operator|&&
operator|(
name|which_line
operator|==
operator|-
literal|1
operator|)
operator|)
operator|||
operator|(
operator|(
name|shadow
operator|==
name|GTK_SHADOW_ETCHED_IN
operator|)
operator|&&
operator|(
name|which_line
operator|==
literal|1
operator|)
operator|)
condition|)
block|{
name|buf
operator|=
name|points
index|[
literal|0
index|]
expr_stmt|;
name|points
index|[
literal|0
index|]
operator|=
name|points
index|[
literal|2
index|]
expr_stmt|;
name|points
index|[
literal|2
index|]
operator|=
name|buf
expr_stmt|;
block|}
name|gtk_paint_polygon
argument_list|(
name|widget
operator|->
name|style
argument_list|,
name|widget
operator|->
name|window
argument_list|,
name|GTK_STATE_NORMAL
argument_list|,
name|shadow
argument_list|,
operator|&
name|eevent
operator|->
name|area
argument_list|,
name|widget
argument_list|,
literal|"chainbutton"
argument_list|,
name|points
argument_list|,
literal|3
argument_list|,
name|FALSE
argument_list|)
expr_stmt|;
return|return
name|TRUE
return|;
block|}
end_function

end_unit

