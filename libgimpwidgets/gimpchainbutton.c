begin_unit|revision:0.9.5;language:C;cregit-version:0.0.1
begin_comment
comment|/* LIBGIMP - The GIMP Library  * Copyright (C) 1995-1997 Peter Mattis and Spencer Kimball  *  * gimpchainbutton.c  * Copyright (C) 1999-2000 Sven Neumann<sven@gimp.org>  *  * This library is free software: you can redistribute it and/or  * modify it under the terms of the GNU Lesser General Public  * License as published by the Free Software Foundation; either  * version 3 of the License, or (at your option) any later version.  *  * This library is distributed in the hope that it will be useful,  * but WITHOUT ANY WARRANTY; without even the implied warranty of  * MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the GNU  * Library General Public License for more details.  *  * You should have received a copy of the GNU Lesser General Public  * License along with this library.  If not, see  *<http://www.gnu.org/licenses/>.  */
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
file|"gimpchainbutton.h"
end_include

begin_include
include|#
directive|include
file|"gimpstock.h"
end_include

begin_comment
comment|/**  * SECTION: gimpchainbutton  * @title: GimpChainButton  * @short_description: Widget to visually connect two entry widgets.  * @see_also: You may want to use the convenience function  *            gimp_coordinates_new() to set up two GimpSizeEntries  *            (see #GimpSizeEntry) linked with a #GimpChainButton.  *  * This widget provides a button showing either a linked or a broken  * chain that can be used to link two entries, spinbuttons, colors or  * other GUI elements and show that they may be locked. Use it for  * example to connect X and Y ratios to provide the possibility of a  * constrained aspect ratio.  *  * The #GimpChainButton only gives visual feedback, it does not really  * connect widgets. You have to take care of locking the values  * yourself by checking the state of the #GimpChainButton whenever a  * value changes in one of the connected widgets and adjusting the  * other value if necessary.  **/
end_comment

begin_enum
enum|enum
DECL|enum|__anon2b15258b0103
block|{
DECL|enumerator|PROP_0
name|PROP_0
block|,
DECL|enumerator|PROP_POSITION
name|PROP_POSITION
block|}
enum|;
end_enum

begin_enum
enum|enum
DECL|enum|__anon2b15258b0203
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
name|GObject
modifier|*
name|gimp_chain_button_constructor
parameter_list|(
name|GType
name|type
parameter_list|,
name|guint
name|n_params
parameter_list|,
name|GObjectConstructParam
modifier|*
name|params
parameter_list|)
function_decl|;
end_function_decl

begin_function_decl
specifier|static
name|void
name|gimp_chain_button_set_property
parameter_list|(
name|GObject
modifier|*
name|object
parameter_list|,
name|guint
name|property_id
parameter_list|,
specifier|const
name|GValue
modifier|*
name|value
parameter_list|,
name|GParamSpec
modifier|*
name|pspec
parameter_list|)
function_decl|;
end_function_decl

begin_function_decl
specifier|static
name|void
name|gimp_chain_button_get_property
parameter_list|(
name|GObject
modifier|*
name|object
parameter_list|,
name|guint
name|property_id
parameter_list|,
name|GValue
modifier|*
name|value
parameter_list|,
name|GParamSpec
modifier|*
name|pspec
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
name|void
name|gimp_chain_button_update_image
parameter_list|(
name|GimpChainButton
modifier|*
name|button
parameter_list|)
function_decl|;
end_function_decl

begin_function_decl
specifier|static
name|GtkWidget
modifier|*
name|gimp_chain_line_new
parameter_list|(
name|GimpChainPosition
name|position
parameter_list|,
name|gint
name|which
parameter_list|)
function_decl|;
end_function_decl

begin_macro
name|G_DEFINE_TYPE
argument_list|(
argument|GimpChainButton
argument_list|,
argument|gimp_chain_button
argument_list|,
argument|GTK_TYPE_TABLE
argument_list|)
end_macro

begin_define
DECL|macro|parent_class
define|#
directive|define
name|parent_class
value|gimp_chain_button_parent_class
end_define

begin_decl_stmt
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
DECL|variable|gimp_chain_stock_items
specifier|static
specifier|const
name|gchar
modifier|*
specifier|const
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
name|GObjectClass
modifier|*
name|object_class
init|=
name|G_OBJECT_CLASS
argument_list|(
name|klass
argument_list|)
decl_stmt|;
name|object_class
operator|->
name|constructor
operator|=
name|gimp_chain_button_constructor
expr_stmt|;
name|object_class
operator|->
name|set_property
operator|=
name|gimp_chain_button_set_property
expr_stmt|;
name|object_class
operator|->
name|get_property
operator|=
name|gimp_chain_button_get_property
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
comment|/**    * GimpChainButton:position:    *    * The position in which the chain button will be used.    *    * Since: GIMP 2.4    */
name|g_object_class_install_property
argument_list|(
name|object_class
argument_list|,
name|PROP_POSITION
argument_list|,
name|g_param_spec_enum
argument_list|(
literal|"position"
argument_list|,
name|NULL
argument_list|,
name|NULL
argument_list|,
name|GIMP_TYPE_CHAIN_POSITION
argument_list|,
name|GIMP_CHAIN_TOP
argument_list|,
name|G_PARAM_CONSTRUCT_ONLY
operator||
name|GIMP_PARAM_READWRITE
argument_list|)
argument_list|)
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
block|}
end_function

begin_function
specifier|static
name|GObject
modifier|*
DECL|function|gimp_chain_button_constructor (GType type,guint n_params,GObjectConstructParam * params)
name|gimp_chain_button_constructor
parameter_list|(
name|GType
name|type
parameter_list|,
name|guint
name|n_params
parameter_list|,
name|GObjectConstructParam
modifier|*
name|params
parameter_list|)
block|{
name|GObject
modifier|*
name|object
decl_stmt|;
name|GimpChainButton
modifier|*
name|button
decl_stmt|;
name|object
operator|=
name|G_OBJECT_CLASS
argument_list|(
name|parent_class
argument_list|)
operator|->
name|constructor
argument_list|(
name|type
argument_list|,
name|n_params
argument_list|,
name|params
argument_list|)
expr_stmt|;
name|button
operator|=
name|GIMP_CHAIN_BUTTON
argument_list|(
name|object
argument_list|)
expr_stmt|;
name|button
operator|->
name|line1
operator|=
name|gimp_chain_line_new
argument_list|(
name|button
operator|->
name|position
argument_list|,
literal|1
argument_list|)
expr_stmt|;
name|button
operator|->
name|line2
operator|=
name|gimp_chain_line_new
argument_list|(
name|button
operator|->
name|position
argument_list|,
operator|-
literal|1
argument_list|)
expr_stmt|;
name|gimp_chain_button_update_image
argument_list|(
name|button
argument_list|)
expr_stmt|;
if|if
condition|(
name|button
operator|->
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
name|object
return|;
block|}
end_function

begin_function
specifier|static
name|void
DECL|function|gimp_chain_button_set_property (GObject * object,guint property_id,const GValue * value,GParamSpec * pspec)
name|gimp_chain_button_set_property
parameter_list|(
name|GObject
modifier|*
name|object
parameter_list|,
name|guint
name|property_id
parameter_list|,
specifier|const
name|GValue
modifier|*
name|value
parameter_list|,
name|GParamSpec
modifier|*
name|pspec
parameter_list|)
block|{
name|GimpChainButton
modifier|*
name|button
init|=
name|GIMP_CHAIN_BUTTON
argument_list|(
name|object
argument_list|)
decl_stmt|;
switch|switch
condition|(
name|property_id
condition|)
block|{
case|case
name|PROP_POSITION
case|:
name|button
operator|->
name|position
operator|=
name|g_value_get_enum
argument_list|(
name|value
argument_list|)
expr_stmt|;
break|break;
default|default:
name|G_OBJECT_WARN_INVALID_PROPERTY_ID
argument_list|(
name|object
argument_list|,
name|property_id
argument_list|,
name|pspec
argument_list|)
expr_stmt|;
break|break;
block|}
block|}
end_function

begin_function
specifier|static
name|void
DECL|function|gimp_chain_button_get_property (GObject * object,guint property_id,GValue * value,GParamSpec * pspec)
name|gimp_chain_button_get_property
parameter_list|(
name|GObject
modifier|*
name|object
parameter_list|,
name|guint
name|property_id
parameter_list|,
name|GValue
modifier|*
name|value
parameter_list|,
name|GParamSpec
modifier|*
name|pspec
parameter_list|)
block|{
name|GimpChainButton
modifier|*
name|button
init|=
name|GIMP_CHAIN_BUTTON
argument_list|(
name|object
argument_list|)
decl_stmt|;
switch|switch
condition|(
name|property_id
condition|)
block|{
case|case
name|PROP_POSITION
case|:
name|g_value_set_enum
argument_list|(
name|value
argument_list|,
name|button
operator|->
name|position
argument_list|)
expr_stmt|;
break|break;
default|default:
name|G_OBJECT_WARN_INVALID_PROPERTY_ID
argument_list|(
name|object
argument_list|,
name|property_id
argument_list|,
name|pspec
argument_list|)
expr_stmt|;
break|break;
block|}
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
return|return
name|g_object_new
argument_list|(
name|GIMP_TYPE_CHAIN_BUTTON
argument_list|,
literal|"position"
argument_list|,
name|position
argument_list|,
name|NULL
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
name|gimp_chain_button_update_image
argument_list|(
name|button
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
name|void
DECL|function|gimp_chain_button_update_image (GimpChainButton * button)
name|gimp_chain_button_update_image
parameter_list|(
name|GimpChainButton
modifier|*
name|button
parameter_list|)
block|{
name|guint
name|i
decl_stmt|;
name|i
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
name|button
operator|->
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
name|i
index|]
argument_list|,
name|GTK_ICON_SIZE_BUTTON
argument_list|)
expr_stmt|;
block|}
end_function

begin_comment
comment|/* GimpChainLine is a simple no-window widget for drawing the lines.  *  * Originally this used to be a GtkDrawingArea but this turned out to  * be a bad idea. We don't need an extra window to draw on and we also  * don't need any input events.  */
end_comment

begin_decl_stmt
specifier|static
name|GType
name|gimp_chain_line_get_type
argument_list|(
name|void
argument_list|)
name|G_GNUC_CONST
decl_stmt|;
end_decl_stmt

begin_function_decl
specifier|static
name|gboolean
name|gimp_chain_line_expose_event
parameter_list|(
name|GtkWidget
modifier|*
name|widget
parameter_list|,
name|GdkEventExpose
modifier|*
name|event
parameter_list|)
function_decl|;
end_function_decl

begin_struct
DECL|struct|_GimpChainLine
struct|struct
name|_GimpChainLine
block|{
DECL|member|parent_instance
name|GtkWidget
name|parent_instance
decl_stmt|;
DECL|member|position
name|GimpChainPosition
name|position
decl_stmt|;
DECL|member|which
name|gint
name|which
decl_stmt|;
block|}
struct|;
end_struct

begin_typedef
DECL|typedef|GimpChainLine
typedef|typedef
name|struct
name|_GimpChainLine
name|GimpChainLine
typedef|;
end_typedef

begin_typedef
DECL|typedef|GimpChainLineClass
typedef|typedef
name|GtkWidgetClass
name|GimpChainLineClass
typedef|;
end_typedef

begin_macro
DECL|function|G_DEFINE_TYPE (GimpChainLine,gimp_chain_line,GTK_TYPE_WIDGET)
name|G_DEFINE_TYPE
argument_list|(
argument|GimpChainLine
argument_list|,
argument|gimp_chain_line
argument_list|,
argument|GTK_TYPE_WIDGET
argument_list|)
end_macro

begin_function
specifier|static
name|void
name|gimp_chain_line_class_init
parameter_list|(
name|GimpChainLineClass
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
name|widget_class
operator|->
name|expose_event
operator|=
name|gimp_chain_line_expose_event
expr_stmt|;
block|}
end_function

begin_function
specifier|static
name|void
DECL|function|gimp_chain_line_init (GimpChainLine * line)
name|gimp_chain_line_init
parameter_list|(
name|GimpChainLine
modifier|*
name|line
parameter_list|)
block|{
name|gtk_widget_set_has_window
argument_list|(
name|GTK_WIDGET
argument_list|(
name|line
argument_list|)
argument_list|,
name|FALSE
argument_list|)
expr_stmt|;
block|}
end_function

begin_function
specifier|static
name|GtkWidget
modifier|*
DECL|function|gimp_chain_line_new (GimpChainPosition position,gint which)
name|gimp_chain_line_new
parameter_list|(
name|GimpChainPosition
name|position
parameter_list|,
name|gint
name|which
parameter_list|)
block|{
name|GimpChainLine
modifier|*
name|line
init|=
name|g_object_new
argument_list|(
name|gimp_chain_line_get_type
argument_list|()
argument_list|,
name|NULL
argument_list|)
decl_stmt|;
name|line
operator|->
name|position
operator|=
name|position
expr_stmt|;
name|line
operator|->
name|which
operator|=
name|which
expr_stmt|;
return|return
name|GTK_WIDGET
argument_list|(
name|line
argument_list|)
return|;
block|}
end_function

begin_function
specifier|static
name|gboolean
DECL|function|gimp_chain_line_expose_event (GtkWidget * widget,GdkEventExpose * event)
name|gimp_chain_line_expose_event
parameter_list|(
name|GtkWidget
modifier|*
name|widget
parameter_list|,
name|GdkEventExpose
modifier|*
name|event
parameter_list|)
block|{
name|GtkStyle
modifier|*
name|style
init|=
name|gtk_widget_get_style
argument_list|(
name|widget
argument_list|)
decl_stmt|;
name|GimpChainLine
modifier|*
name|line
init|=
operator|(
operator|(
name|GimpChainLine
operator|*
operator|)
name|widget
operator|)
decl_stmt|;
name|GtkAllocation
name|allocation
decl_stmt|;
name|GdkPoint
name|points
index|[
literal|3
index|]
decl_stmt|;
name|GimpChainPosition
name|position
decl_stmt|;
name|cairo_t
modifier|*
name|cr
decl_stmt|;
name|gtk_widget_get_allocation
argument_list|(
name|widget
argument_list|,
operator|&
name|allocation
argument_list|)
expr_stmt|;
name|cr
operator|=
name|gdk_cairo_create
argument_list|(
name|gtk_widget_get_window
argument_list|(
name|widget
argument_list|)
argument_list|)
expr_stmt|;
name|gdk_cairo_region
argument_list|(
name|cr
argument_list|,
name|event
operator|->
name|region
argument_list|)
expr_stmt|;
name|cairo_translate
argument_list|(
name|cr
argument_list|,
name|allocation
operator|.
name|x
argument_list|,
name|allocation
operator|.
name|y
argument_list|)
expr_stmt|;
name|cairo_clip
argument_list|(
name|cr
argument_list|)
expr_stmt|;
DECL|macro|SHORT_LINE
define|#
directive|define
name|SHORT_LINE
value|4
name|points
index|[
literal|0
index|]
operator|.
name|x
operator|=
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
name|allocation
operator|.
name|height
operator|/
literal|2
expr_stmt|;
name|position
operator|=
name|line
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
block|{
switch|switch
condition|(
name|position
condition|)
block|{
case|case
name|GIMP_CHAIN_TOP
case|:
case|case
name|GIMP_CHAIN_BOTTOM
case|:
break|break;
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
block|}
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
name|line
operator|->
name|which
operator|==
literal|1
condition|?
name|allocation
operator|.
name|height
operator|-
literal|1
else|:
literal|0
operator|)
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
name|line
operator|->
name|which
operator|==
literal|1
condition|?
name|allocation
operator|.
name|height
operator|-
literal|1
else|:
literal|0
operator|)
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
name|line
operator|->
name|which
operator|==
literal|1
condition|?
name|allocation
operator|.
name|width
operator|-
literal|1
else|:
literal|0
operator|)
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
name|line
operator|->
name|which
operator|==
literal|1
condition|?
name|allocation
operator|.
name|width
operator|-
literal|1
else|:
literal|0
operator|)
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
break|break;
default|default:
return|return
name|FALSE
return|;
block|}
name|cairo_move_to
argument_list|(
name|cr
argument_list|,
name|points
index|[
literal|0
index|]
operator|.
name|x
argument_list|,
name|points
index|[
literal|0
index|]
operator|.
name|y
argument_list|)
expr_stmt|;
name|cairo_line_to
argument_list|(
name|cr
argument_list|,
name|points
index|[
literal|1
index|]
operator|.
name|x
argument_list|,
name|points
index|[
literal|1
index|]
operator|.
name|y
argument_list|)
expr_stmt|;
name|cairo_line_to
argument_list|(
name|cr
argument_list|,
name|points
index|[
literal|2
index|]
operator|.
name|x
argument_list|,
name|points
index|[
literal|2
index|]
operator|.
name|y
argument_list|)
expr_stmt|;
name|cairo_set_line_width
argument_list|(
name|cr
argument_list|,
literal|2.0
argument_list|)
expr_stmt|;
name|cairo_set_line_cap
argument_list|(
name|cr
argument_list|,
name|CAIRO_LINE_CAP_BUTT
argument_list|)
expr_stmt|;
name|gdk_cairo_set_source_color
argument_list|(
name|cr
argument_list|,
operator|&
name|style
operator|->
name|fg
index|[
name|GTK_STATE_NORMAL
index|]
argument_list|)
expr_stmt|;
name|cairo_stroke
argument_list|(
name|cr
argument_list|)
expr_stmt|;
name|cairo_destroy
argument_list|(
name|cr
argument_list|)
expr_stmt|;
return|return
name|TRUE
return|;
block|}
end_function

end_unit

