begin_unit|revision:0.9.5;language:C;cregit-version:0.0.1
begin_comment
comment|/* LIBGIMP - The GIMP Library   * Copyright (C) 1995-1997 Peter Mattis and Spencer Kimball                  *  * gimpchainbutton.c  * Copyright (C) 1999-2000 Sven Neumann<sven@gimp.org>   *  * This library is free software; you can redistribute it and/or  * modify it under the terms of the GNU Lesser General Public  * License as published by the Free Software Foundation; either  * version 2 of the License, or (at your option) any later version.  *   * This library is distributed in the hope that it will be useful,   * but WITHOUT ANY WARRANTY; without even the implied warranty of   * MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the GNU    * Library General Public License for more details.  *  * You should have received a copy of the GNU Lesser General Public  * License along with this library; if not, write to the  * Free Software Foundation, Inc., 59 Temple Place - Suite 330,  * Boston, MA 02111-1307, USA.  */
end_comment

begin_include
include|#
directive|include
file|<gtk/gtk.h>
end_include

begin_include
include|#
directive|include
file|"gimpchainbutton.h"
end_include

begin_include
include|#
directive|include
file|"pixmaps/chain.xpm"
end_include

begin_decl_stmt
DECL|variable|gimp_chain_xpm
specifier|static
name|gchar
modifier|*
modifier|*
name|gimp_chain_xpm
index|[]
init|=
block|{
name|chain_hor_xpm
block|,
name|chain_ver_xpm
block|}
decl_stmt|;
end_decl_stmt

begin_decl_stmt
DECL|variable|gimp_chain_broken_xpm
specifier|static
name|gchar
modifier|*
modifier|*
name|gimp_chain_broken_xpm
index|[]
init|=
block|{
name|chain_broken_hor_xpm
block|,
name|chain_broken_ver_xpm
block|}
decl_stmt|;
end_decl_stmt

begin_decl_stmt
DECL|variable|gimp_chain_width
specifier|static
name|guint
name|gimp_chain_width
index|[]
init|=
block|{
literal|24
block|,
literal|9
block|}
decl_stmt|;
end_decl_stmt

begin_decl_stmt
DECL|variable|gimp_chain_height
specifier|static
name|guint
name|gimp_chain_height
index|[]
init|=
block|{
literal|9
block|,
literal|24
block|}
decl_stmt|;
end_decl_stmt

begin_function_decl
specifier|static
name|void
name|gimp_chain_button_destroy
parameter_list|(
name|GtkObject
modifier|*
name|object
parameter_list|)
function_decl|;
end_function_decl

begin_function_decl
specifier|static
name|void
name|gimp_chain_button_realize
parameter_list|(
name|GtkWidget
modifier|*
name|widget
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
name|gcb
parameter_list|)
function_decl|;
end_function_decl

begin_function_decl
specifier|static
name|gint
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
name|gcb
parameter_list|)
function_decl|;
end_function_decl

begin_enum
enum|enum
DECL|enum|__anon2b64be910103
block|{
DECL|enumerator|TOGGLED
name|TOGGLED
block|,
DECL|enumerator|LAST_SIGNAL
name|LAST_SIGNAL
block|}
enum|;
end_enum

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
specifier|static
name|void
DECL|function|gimp_chain_button_destroy (GtkObject * object)
name|gimp_chain_button_destroy
parameter_list|(
name|GtkObject
modifier|*
name|object
parameter_list|)
block|{
name|GimpChainButton
modifier|*
name|gcb
init|=
name|GIMP_CHAIN_BUTTON
argument_list|(
name|object
argument_list|)
decl_stmt|;
name|g_return_if_fail
argument_list|(
name|gcb
operator|!=
name|NULL
argument_list|)
expr_stmt|;
if|if
condition|(
name|gcb
operator|->
name|broken
condition|)
name|gdk_pixmap_unref
argument_list|(
name|gcb
operator|->
name|broken
argument_list|)
expr_stmt|;
if|if
condition|(
name|gcb
operator|->
name|broken_mask
condition|)
name|gdk_bitmap_unref
argument_list|(
name|gcb
operator|->
name|broken_mask
argument_list|)
expr_stmt|;
if|if
condition|(
name|gcb
operator|->
name|chain
condition|)
name|gdk_pixmap_unref
argument_list|(
name|gcb
operator|->
name|chain
argument_list|)
expr_stmt|;
if|if
condition|(
name|gcb
operator|->
name|chain_mask
condition|)
name|gdk_bitmap_unref
argument_list|(
name|gcb
operator|->
name|chain_mask
argument_list|)
expr_stmt|;
if|if
condition|(
name|GTK_OBJECT_CLASS
argument_list|(
name|parent_class
argument_list|)
operator|->
name|destroy
condition|)
operator|(
operator|*
name|GTK_OBJECT_CLASS
argument_list|(
name|parent_class
argument_list|)
operator|->
name|destroy
operator|)
operator|(
name|object
operator|)
expr_stmt|;
block|}
end_function

begin_function
specifier|static
name|void
DECL|function|gimp_chain_button_class_init (GimpChainButtonClass * class)
name|gimp_chain_button_class_init
parameter_list|(
name|GimpChainButtonClass
modifier|*
name|class
parameter_list|)
block|{
name|GtkObjectClass
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
name|GtkObjectClass
operator|*
operator|)
name|class
expr_stmt|;
name|widget_class
operator|=
operator|(
name|GtkWidgetClass
operator|*
operator|)
name|class
expr_stmt|;
name|parent_class
operator|=
name|gtk_type_class
argument_list|(
name|gtk_table_get_type
argument_list|()
argument_list|)
expr_stmt|;
name|object_class
operator|->
name|destroy
operator|=
name|gimp_chain_button_destroy
expr_stmt|;
name|gimp_chain_button_signals
index|[
name|TOGGLED
index|]
operator|=
name|gtk_signal_new
argument_list|(
literal|"toggled"
argument_list|,
name|GTK_RUN_FIRST
argument_list|,
name|object_class
operator|->
name|type
argument_list|,
name|GTK_SIGNAL_OFFSET
argument_list|(
name|GimpChainButtonClass
argument_list|,
name|toggled
argument_list|)
argument_list|,
name|gtk_signal_default_marshaller
argument_list|,
name|GTK_TYPE_NONE
argument_list|,
literal|0
argument_list|)
expr_stmt|;
name|gtk_object_class_add_signals
argument_list|(
name|object_class
argument_list|,
name|gimp_chain_button_signals
argument_list|,
name|LAST_SIGNAL
argument_list|)
expr_stmt|;
name|class
operator|->
name|toggled
operator|=
name|NULL
expr_stmt|;
name|widget_class
operator|->
name|realize
operator|=
name|gimp_chain_button_realize
expr_stmt|;
block|}
end_function

begin_function
specifier|static
name|void
DECL|function|gimp_chain_button_init (GimpChainButton * gcb)
name|gimp_chain_button_init
parameter_list|(
name|GimpChainButton
modifier|*
name|gcb
parameter_list|)
block|{
name|gcb
operator|->
name|position
operator|=
name|GIMP_CHAIN_TOP
expr_stmt|;
name|gcb
operator|->
name|line1
operator|=
name|gtk_drawing_area_new
argument_list|()
expr_stmt|;
name|gcb
operator|->
name|line2
operator|=
name|gtk_drawing_area_new
argument_list|()
expr_stmt|;
name|gcb
operator|->
name|pixmap
operator|=
name|NULL
expr_stmt|;
name|gcb
operator|->
name|broken
operator|=
name|NULL
expr_stmt|;
name|gcb
operator|->
name|broken_mask
operator|=
name|NULL
expr_stmt|;
name|gcb
operator|->
name|chain
operator|=
name|NULL
expr_stmt|;
name|gcb
operator|->
name|chain_mask
operator|=
name|NULL
expr_stmt|;
name|gcb
operator|->
name|active
operator|=
name|FALSE
expr_stmt|;
name|gcb
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
name|gcb
operator|->
name|button
argument_list|)
argument_list|,
name|GTK_RELIEF_NONE
argument_list|)
expr_stmt|;
name|gcb
operator|->
name|pixmap
operator|=
name|gtk_type_new
argument_list|(
name|gtk_pixmap_get_type
argument_list|()
argument_list|)
expr_stmt|;
name|gtk_pixmap_set_build_insensitive
argument_list|(
name|GTK_PIXMAP
argument_list|(
name|gcb
operator|->
name|pixmap
argument_list|)
argument_list|,
name|TRUE
argument_list|)
expr_stmt|;
name|gtk_signal_connect
argument_list|(
name|GTK_OBJECT
argument_list|(
name|gcb
operator|->
name|button
argument_list|)
argument_list|,
literal|"clicked"
argument_list|,
name|GTK_SIGNAL_FUNC
argument_list|(
name|gimp_chain_button_clicked_callback
argument_list|)
argument_list|,
name|gcb
argument_list|)
expr_stmt|;
name|gtk_signal_connect
argument_list|(
name|GTK_OBJECT
argument_list|(
name|gcb
operator|->
name|line1
argument_list|)
argument_list|,
literal|"expose_event"
argument_list|,
name|GTK_SIGNAL_FUNC
argument_list|(
name|gimp_chain_button_draw_lines
argument_list|)
argument_list|,
name|gcb
argument_list|)
expr_stmt|;
name|gtk_signal_connect
argument_list|(
name|GTK_OBJECT
argument_list|(
name|gcb
operator|->
name|line2
argument_list|)
argument_list|,
literal|"expose_event"
argument_list|,
name|GTK_SIGNAL_FUNC
argument_list|(
name|gimp_chain_button_draw_lines
argument_list|)
argument_list|,
name|gcb
argument_list|)
expr_stmt|;
block|}
end_function

begin_function
name|GtkType
DECL|function|gimp_chain_button_get_type (void)
name|gimp_chain_button_get_type
parameter_list|(
name|void
parameter_list|)
block|{
specifier|static
name|guint
name|gcb_type
init|=
literal|0
decl_stmt|;
if|if
condition|(
operator|!
name|gcb_type
condition|)
block|{
name|GtkTypeInfo
name|gcb_info
init|=
block|{
literal|"GimpChainButton"
block|,
sizeof|sizeof
argument_list|(
name|GimpChainButton
argument_list|)
block|,
sizeof|sizeof
argument_list|(
name|GimpChainButtonClass
argument_list|)
block|,
operator|(
name|GtkClassInitFunc
operator|)
name|gimp_chain_button_class_init
block|,
operator|(
name|GtkObjectInitFunc
operator|)
name|gimp_chain_button_init
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
name|gcb_type
operator|=
name|gtk_type_unique
argument_list|(
name|gtk_table_get_type
argument_list|()
argument_list|,
operator|&
name|gcb_info
argument_list|)
expr_stmt|;
block|}
return|return
name|gcb_type
return|;
block|}
end_function

begin_comment
comment|/**  * gimp_chain_button_new:  * @position: The position you are going to use for the button  *            with respect to the widgets you want to chain.  *   * Creates a new #GimpChainButton widget.  *  * This returns a button showing either a broken or a linked chain and  * small clamps attached to both sides that visually group the two widgets   * you want to connect. This widget looks best when attached  * to a table taking up two columns (or rows respectively) next  * to the widgets that it is supposed to connect. It may work  * for more than two widgets, but the look is optimized for two.  *  * Returns: Pointer to the new #GimpChainButton, which is inactive  *          by default. Use gimp_chain_button_set_active() to   *          change its state.  */
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
name|gcb
decl_stmt|;
name|gcb
operator|=
name|gtk_type_new
argument_list|(
name|gimp_chain_button_get_type
argument_list|()
argument_list|)
expr_stmt|;
name|gcb
operator|->
name|position
operator|=
name|position
expr_stmt|;
name|gcb
operator|->
name|pixmap
operator|->
name|requisition
operator|.
name|width
operator|=
name|gimp_chain_width
index|[
name|position
operator|%
literal|2
index|]
operator|+
name|GTK_MISC
argument_list|(
name|gcb
operator|->
name|pixmap
argument_list|)
operator|->
name|xpad
operator|*
literal|2
expr_stmt|;
name|gcb
operator|->
name|pixmap
operator|->
name|requisition
operator|.
name|height
operator|=
name|gimp_chain_height
index|[
name|position
operator|%
literal|2
index|]
operator|+
name|GTK_MISC
argument_list|(
name|gcb
operator|->
name|pixmap
argument_list|)
operator|->
name|ypad
operator|*
literal|2
expr_stmt|;
name|gtk_container_add
argument_list|(
name|GTK_CONTAINER
argument_list|(
name|gcb
operator|->
name|button
argument_list|)
argument_list|,
name|gcb
operator|->
name|pixmap
argument_list|)
expr_stmt|;
name|gtk_widget_show
argument_list|(
name|gcb
operator|->
name|pixmap
argument_list|)
expr_stmt|;
name|gtk_widget_show
argument_list|(
name|gcb
operator|->
name|button
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
name|gcb
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
name|gcb
argument_list|)
argument_list|,
name|gcb
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
name|gcb
argument_list|)
argument_list|,
name|gcb
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
name|gcb
argument_list|)
argument_list|,
name|gcb
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
name|gcb
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
name|gcb
argument_list|)
argument_list|,
name|gcb
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
name|gcb
argument_list|)
argument_list|,
name|gcb
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
name|gcb
argument_list|)
argument_list|,
name|gcb
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
name|gcb
operator|->
name|line1
argument_list|)
expr_stmt|;
name|gtk_widget_show
argument_list|(
name|gcb
operator|->
name|line2
argument_list|)
expr_stmt|;
return|return
name|GTK_WIDGET
argument_list|(
name|gcb
argument_list|)
return|;
block|}
end_function

begin_comment
comment|/**   * gimp_chain_button_set_active:  * @gcb: Pointer to a #GimpChainButton.  * @is_active: The new state.  *   * Sets the state of the #GimpChainButton to be either locked (TRUE) or   * unlocked (FALSE) and changes the showed pixmap to reflect the new state.  */
end_comment

begin_function
name|void
DECL|function|gimp_chain_button_set_active (GimpChainButton * gcb,gboolean is_active)
name|gimp_chain_button_set_active
parameter_list|(
name|GimpChainButton
modifier|*
name|gcb
parameter_list|,
name|gboolean
name|is_active
parameter_list|)
block|{
name|g_return_if_fail
argument_list|(
name|GIMP_IS_CHAIN_BUTTON
argument_list|(
name|gcb
argument_list|)
argument_list|)
expr_stmt|;
if|if
condition|(
name|gcb
operator|->
name|active
operator|!=
name|is_active
condition|)
block|{
name|gcb
operator|->
name|active
operator|=
name|is_active
expr_stmt|;
if|if
condition|(
operator|!
name|GTK_WIDGET_REALIZED
argument_list|(
name|GTK_WIDGET
argument_list|(
name|gcb
argument_list|)
argument_list|)
condition|)
return|return;
if|if
condition|(
name|gcb
operator|->
name|active
condition|)
name|gtk_pixmap_set
argument_list|(
name|GTK_PIXMAP
argument_list|(
name|gcb
operator|->
name|pixmap
argument_list|)
argument_list|,
name|gcb
operator|->
name|chain
argument_list|,
name|gcb
operator|->
name|chain_mask
argument_list|)
expr_stmt|;
else|else
name|gtk_pixmap_set
argument_list|(
name|GTK_PIXMAP
argument_list|(
name|gcb
operator|->
name|pixmap
argument_list|)
argument_list|,
name|gcb
operator|->
name|broken
argument_list|,
name|gcb
operator|->
name|broken_mask
argument_list|)
expr_stmt|;
block|}
block|}
end_function

begin_comment
comment|/**  * gimp_chain_button_get_active  * @gcb: Pointer to a #GimpChainButton.  *   * Checks the state of the #GimpChainButton.   *  * Returns: TRUE if the #GimpChainButton is active (locked).  */
end_comment

begin_function
name|gboolean
DECL|function|gimp_chain_button_get_active (GimpChainButton * gcb)
name|gimp_chain_button_get_active
parameter_list|(
name|GimpChainButton
modifier|*
name|gcb
parameter_list|)
block|{
name|g_return_val_if_fail
argument_list|(
name|GIMP_IS_CHAIN_BUTTON
argument_list|(
name|gcb
argument_list|)
argument_list|,
name|FALSE
argument_list|)
expr_stmt|;
return|return
name|gcb
operator|->
name|active
return|;
block|}
end_function

begin_function
specifier|static
name|void
DECL|function|gimp_chain_button_realize (GtkWidget * widget)
name|gimp_chain_button_realize
parameter_list|(
name|GtkWidget
modifier|*
name|widget
parameter_list|)
block|{
name|GimpChainButton
modifier|*
name|gcb
decl_stmt|;
name|GtkStyle
modifier|*
name|style
decl_stmt|;
name|gcb
operator|=
name|GIMP_CHAIN_BUTTON
argument_list|(
name|widget
argument_list|)
expr_stmt|;
if|if
condition|(
name|GTK_WIDGET_CLASS
argument_list|(
name|parent_class
argument_list|)
operator|->
name|realize
condition|)
operator|(
operator|*
name|GTK_WIDGET_CLASS
argument_list|(
name|parent_class
argument_list|)
operator|->
name|realize
operator|)
operator|(
name|widget
operator|)
expr_stmt|;
name|style
operator|=
name|gtk_widget_get_style
argument_list|(
name|widget
argument_list|)
expr_stmt|;
name|gcb
operator|->
name|chain
operator|=
name|gdk_pixmap_create_from_xpm_d
argument_list|(
name|widget
operator|->
name|window
argument_list|,
operator|&
name|gcb
operator|->
name|chain_mask
argument_list|,
operator|&
name|style
operator|->
name|bg
index|[
name|GTK_STATE_NORMAL
index|]
argument_list|,
name|gimp_chain_xpm
index|[
name|gcb
operator|->
name|position
operator|%
literal|2
index|]
argument_list|)
expr_stmt|;
name|gcb
operator|->
name|broken
operator|=
name|gdk_pixmap_create_from_xpm_d
argument_list|(
name|widget
operator|->
name|window
argument_list|,
operator|&
name|gcb
operator|->
name|broken_mask
argument_list|,
operator|&
name|style
operator|->
name|bg
index|[
name|GTK_STATE_NORMAL
index|]
argument_list|,
name|gimp_chain_broken_xpm
index|[
name|gcb
operator|->
name|position
operator|%
literal|2
index|]
argument_list|)
expr_stmt|;
if|if
condition|(
name|gcb
operator|->
name|active
condition|)
name|gtk_pixmap_set
argument_list|(
name|GTK_PIXMAP
argument_list|(
name|gcb
operator|->
name|pixmap
argument_list|)
argument_list|,
name|gcb
operator|->
name|chain
argument_list|,
name|gcb
operator|->
name|chain_mask
argument_list|)
expr_stmt|;
else|else
name|gtk_pixmap_set
argument_list|(
name|GTK_PIXMAP
argument_list|(
name|gcb
operator|->
name|pixmap
argument_list|)
argument_list|,
name|gcb
operator|->
name|broken
argument_list|,
name|gcb
operator|->
name|broken_mask
argument_list|)
expr_stmt|;
name|gtk_widget_realize
argument_list|(
name|gcb
operator|->
name|line1
argument_list|)
expr_stmt|;
name|gtk_style_set_background
argument_list|(
name|widget
operator|->
name|style
argument_list|,
name|gcb
operator|->
name|line1
operator|->
name|window
argument_list|,
name|GTK_STATE_NORMAL
argument_list|)
expr_stmt|;
name|gdk_window_set_back_pixmap
argument_list|(
name|gcb
operator|->
name|line1
operator|->
name|window
argument_list|,
name|NULL
argument_list|,
name|TRUE
argument_list|)
expr_stmt|;
name|gtk_widget_realize
argument_list|(
name|gcb
operator|->
name|line2
argument_list|)
expr_stmt|;
name|gtk_style_set_background
argument_list|(
name|widget
operator|->
name|style
argument_list|,
name|gcb
operator|->
name|line2
operator|->
name|window
argument_list|,
name|GTK_STATE_NORMAL
argument_list|)
expr_stmt|;
name|gdk_window_set_back_pixmap
argument_list|(
name|gcb
operator|->
name|line2
operator|->
name|window
argument_list|,
name|NULL
argument_list|,
name|TRUE
argument_list|)
expr_stmt|;
block|}
end_function

begin_function
specifier|static
name|void
DECL|function|gimp_chain_button_clicked_callback (GtkWidget * widget,GimpChainButton * gcb)
name|gimp_chain_button_clicked_callback
parameter_list|(
name|GtkWidget
modifier|*
name|widget
parameter_list|,
name|GimpChainButton
modifier|*
name|gcb
parameter_list|)
block|{
name|g_return_if_fail
argument_list|(
name|GIMP_IS_CHAIN_BUTTON
argument_list|(
name|gcb
argument_list|)
argument_list|)
expr_stmt|;
name|gcb
operator|->
name|active
operator|=
operator|!
operator|(
name|gcb
operator|->
name|active
operator|)
expr_stmt|;
if|if
condition|(
operator|!
name|GTK_WIDGET_REALIZED
argument_list|(
name|GTK_WIDGET
argument_list|(
name|gcb
argument_list|)
argument_list|)
condition|)
return|return;
if|if
condition|(
name|gcb
operator|->
name|active
condition|)
name|gtk_pixmap_set
argument_list|(
name|GTK_PIXMAP
argument_list|(
name|gcb
operator|->
name|pixmap
argument_list|)
argument_list|,
name|gcb
operator|->
name|chain
argument_list|,
name|gcb
operator|->
name|chain_mask
argument_list|)
expr_stmt|;
else|else
name|gtk_pixmap_set
argument_list|(
name|GTK_PIXMAP
argument_list|(
name|gcb
operator|->
name|pixmap
argument_list|)
argument_list|,
name|gcb
operator|->
name|broken
argument_list|,
name|gcb
operator|->
name|broken_mask
argument_list|)
expr_stmt|;
name|gtk_signal_emit
argument_list|(
name|GTK_OBJECT
argument_list|(
name|gcb
argument_list|)
argument_list|,
name|gimp_chain_button_signals
index|[
name|TOGGLED
index|]
argument_list|)
expr_stmt|;
block|}
end_function

begin_function
specifier|static
name|gint
DECL|function|gimp_chain_button_draw_lines (GtkWidget * widget,GdkEventExpose * eevent,GimpChainButton * gcb)
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
name|gcb
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
name|gint
name|which_line
decl_stmt|;
DECL|macro|SHORT_LINE
define|#
directive|define
name|SHORT_LINE
value|4
comment|/* don't set this too high, there's no check against drawing outside       the widgets bounds yet (and probably never will be) */
name|g_return_val_if_fail
argument_list|(
name|GIMP_IS_CHAIN_BUTTON
argument_list|(
name|gcb
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
name|gcb
operator|->
name|line1
operator|)
condition|?
literal|1
else|:
operator|-
literal|1
expr_stmt|;
switch|switch
condition|(
name|gcb
operator|->
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

