begin_unit|revision:0.9.5;language:C;cregit-version:0.0.1
begin_comment
comment|/* LIBGIMP - The GIMP Library   * Copyright (C) 1995-1997 Peter Mattis and Spencer Kimball  *  * gimpcolorbutton.c  * Copyright (C) 1999-2001 Sven Neumann  *  * This library is free software; you can redistribute it and/or  * modify it under the terms of the GNU Lesser General Public  * License as published by the Free Software Foundation; either  * version 2 of the License, or (at your option) any later version.  *   * This library is distributed in the hope that it will be useful,   * but WITHOUT ANY WARRANTY; without even the implied warranty of   * MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the GNU    * Library General Public License for more details.  *  * You should have received a copy of the GNU Lesser General Public  * License along with this library; if not, write to the  * Free Software Foundation, Inc., 59 Temple Place - Suite 330,  * Boston, MA 02111-1307, USA.  */
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
file|"libgimpcolor/gimpcolor.h"
end_include

begin_include
include|#
directive|include
file|"gimpwidgetstypes.h"
end_include

begin_include
include|#
directive|include
file|"gimpcolorarea.h"
end_include

begin_include
include|#
directive|include
file|"gimpcolorbutton.h"
end_include

begin_include
include|#
directive|include
file|"libgimp/gimppalette_pdb.h"
end_include

begin_include
include|#
directive|include
file|"libgimp/libgimp-intl.h"
end_include

begin_define
DECL|macro|TODOUBLE (i)
define|#
directive|define
name|TODOUBLE
parameter_list|(
name|i
parameter_list|)
value|(i / 65535.0)
end_define

begin_define
DECL|macro|TOUINT16 (d)
define|#
directive|define
name|TOUINT16
parameter_list|(
name|d
parameter_list|)
value|((guint16) (d * 65535 + 0.5))
end_define

begin_typedef
typedef|typedef
enum|enum
DECL|enum|__anon2bdf9b890103
block|{
DECL|enumerator|GIMP_COLOR_BUTTON_COLOR_FG
name|GIMP_COLOR_BUTTON_COLOR_FG
block|,
DECL|enumerator|GIMP_COLOR_BUTTON_COLOR_BG
name|GIMP_COLOR_BUTTON_COLOR_BG
block|,
DECL|enumerator|GIMP_COLOR_BUTTON_COLOR_BLACK
name|GIMP_COLOR_BUTTON_COLOR_BLACK
block|,
DECL|enumerator|GIMP_COLOR_BUTTON_COLOR_WHITE
name|GIMP_COLOR_BUTTON_COLOR_WHITE
block|, }
DECL|typedef|GimpColorButtonColor
name|GimpColorButtonColor
typedef|;
end_typedef

begin_enum
enum|enum
DECL|enum|__anon2bdf9b890203
block|{
DECL|enumerator|COLOR_CHANGED
name|COLOR_CHANGED
block|,
DECL|enumerator|LAST_SIGNAL
name|LAST_SIGNAL
block|}
enum|;
end_enum

begin_function_decl
specifier|static
name|void
name|gimp_color_button_class_init
parameter_list|(
name|GimpColorButtonClass
modifier|*
name|klass
parameter_list|)
function_decl|;
end_function_decl

begin_function_decl
specifier|static
name|void
name|gimp_color_button_init
parameter_list|(
name|GimpColorButton
modifier|*
name|button
parameter_list|)
function_decl|;
end_function_decl

begin_function_decl
specifier|static
name|void
name|gimp_color_button_destroy
parameter_list|(
name|GtkObject
modifier|*
name|object
parameter_list|)
function_decl|;
end_function_decl

begin_function_decl
specifier|static
name|gboolean
name|gimp_color_button_button_press
parameter_list|(
name|GtkWidget
modifier|*
name|widget
parameter_list|,
name|GdkEventButton
modifier|*
name|bevent
parameter_list|)
function_decl|;
end_function_decl

begin_function_decl
specifier|static
name|void
name|gimp_color_button_state_changed
parameter_list|(
name|GtkWidget
modifier|*
name|widget
parameter_list|,
name|GtkStateType
name|prev_state
parameter_list|)
function_decl|;
end_function_decl

begin_function_decl
specifier|static
name|void
name|gimp_color_button_clicked
parameter_list|(
name|GtkButton
modifier|*
name|button
parameter_list|)
function_decl|;
end_function_decl

begin_function_decl
specifier|static
name|void
name|gimp_color_button_dialog_ok
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
name|gimp_color_button_dialog_cancel
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
name|gimp_color_button_use_color
parameter_list|(
name|gpointer
name|callback_data
parameter_list|,
name|guint
name|callback_action
parameter_list|,
name|GtkWidget
modifier|*
name|widget
parameter_list|)
function_decl|;
end_function_decl

begin_function_decl
specifier|static
name|gchar
modifier|*
name|gimp_color_button_menu_translate
parameter_list|(
specifier|const
name|gchar
modifier|*
name|path
parameter_list|,
name|gpointer
name|func_data
parameter_list|)
function_decl|;
end_function_decl

begin_function_decl
specifier|static
name|void
name|gimp_color_button_color_changed
parameter_list|(
name|GtkObject
modifier|*
name|object
parameter_list|,
name|gpointer
name|data
parameter_list|)
function_decl|;
end_function_decl

begin_decl_stmt
DECL|variable|menu_items
specifier|static
name|GtkItemFactoryEntry
name|menu_items
index|[]
init|=
block|{
block|{
name|N_
argument_list|(
literal|"/Foreground Color"
argument_list|)
block|,
name|NULL
block|,
name|gimp_color_button_use_color
block|,
name|GIMP_COLOR_BUTTON_COLOR_FG
block|,
name|NULL
block|}
block|,
block|{
name|N_
argument_list|(
literal|"/Background Color"
argument_list|)
block|,
name|NULL
block|,
name|gimp_color_button_use_color
block|,
name|GIMP_COLOR_BUTTON_COLOR_BG
block|,
name|NULL
block|}
block|,
block|{
literal|"/fg-bg-separator"
block|,
name|NULL
block|,
name|NULL
block|,
literal|0
block|,
literal|"<Separator>"
block|}
block|,
block|{
name|N_
argument_list|(
literal|"/Black"
argument_list|)
block|,
name|NULL
block|,
name|gimp_color_button_use_color
block|,
name|GIMP_COLOR_BUTTON_COLOR_BLACK
block|,
name|NULL
block|}
block|,
block|{
name|N_
argument_list|(
literal|"/White"
argument_list|)
block|,
name|NULL
block|,
name|gimp_color_button_use_color
block|,
name|GIMP_COLOR_BUTTON_COLOR_WHITE
block|,
name|NULL
block|}
block|, }
decl_stmt|;
end_decl_stmt

begin_decl_stmt
DECL|variable|gimp_color_button_signals
specifier|static
name|guint
name|gimp_color_button_signals
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
name|GimpButtonClass
modifier|*
name|parent_class
init|=
name|NULL
decl_stmt|;
end_decl_stmt

begin_function
name|GType
DECL|function|gimp_color_button_get_type (void)
name|gimp_color_button_get_type
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
name|GimpColorButtonClass
argument_list|)
block|,
operator|(
name|GBaseInitFunc
operator|)
name|NULL
block|,
operator|(
name|GBaseFinalizeFunc
operator|)
name|NULL
block|,
operator|(
name|GClassInitFunc
operator|)
name|gimp_color_button_class_init
block|,
name|NULL
block|,
comment|/* class_finalize */
name|NULL
block|,
comment|/* class_data     */
sizeof|sizeof
argument_list|(
name|GimpColorButton
argument_list|)
block|,
literal|0
block|,
comment|/* n_preallocs    */
operator|(
name|GInstanceInitFunc
operator|)
name|gimp_color_button_init
block|,       }
decl_stmt|;
name|button_type
operator|=
name|g_type_register_static
argument_list|(
name|GIMP_TYPE_BUTTON
argument_list|,
literal|"GimpColorButton"
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
DECL|function|gimp_color_button_class_init (GimpColorButtonClass * klass)
name|gimp_color_button_class_init
parameter_list|(
name|GimpColorButtonClass
modifier|*
name|klass
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
name|GtkButtonClass
modifier|*
name|button_class
decl_stmt|;
name|object_class
operator|=
name|GTK_OBJECT_CLASS
argument_list|(
name|klass
argument_list|)
expr_stmt|;
name|widget_class
operator|=
name|GTK_WIDGET_CLASS
argument_list|(
name|klass
argument_list|)
expr_stmt|;
name|button_class
operator|=
name|GTK_BUTTON_CLASS
argument_list|(
name|klass
argument_list|)
expr_stmt|;
name|parent_class
operator|=
name|g_type_class_peek_parent
argument_list|(
name|klass
argument_list|)
expr_stmt|;
name|gimp_color_button_signals
index|[
name|COLOR_CHANGED
index|]
operator|=
name|g_signal_new
argument_list|(
literal|"color_changed"
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
name|GimpColorButtonClass
argument_list|,
name|color_changed
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
name|object_class
operator|->
name|destroy
operator|=
name|gimp_color_button_destroy
expr_stmt|;
name|widget_class
operator|->
name|button_press_event
operator|=
name|gimp_color_button_button_press
expr_stmt|;
name|widget_class
operator|->
name|state_changed
operator|=
name|gimp_color_button_state_changed
expr_stmt|;
name|button_class
operator|->
name|clicked
operator|=
name|gimp_color_button_clicked
expr_stmt|;
name|klass
operator|->
name|color_changed
operator|=
name|NULL
expr_stmt|;
block|}
end_function

begin_function
specifier|static
name|void
DECL|function|gimp_color_button_init (GimpColorButton * button)
name|gimp_color_button_init
parameter_list|(
name|GimpColorButton
modifier|*
name|button
parameter_list|)
block|{
name|GimpRGB
name|color
decl_stmt|;
name|button
operator|->
name|title
operator|=
name|NULL
expr_stmt|;
name|button
operator|->
name|dialog
operator|=
name|NULL
expr_stmt|;
name|gimp_rgba_set
argument_list|(
operator|&
name|color
argument_list|,
literal|0.0
argument_list|,
literal|0.0
argument_list|,
literal|0.0
argument_list|,
literal|1.0
argument_list|)
expr_stmt|;
name|button
operator|->
name|color_area
operator|=
name|gimp_color_area_new
argument_list|(
operator|&
name|color
argument_list|,
name|FALSE
argument_list|,
name|GDK_BUTTON2_MASK
argument_list|)
expr_stmt|;
name|g_signal_connect
argument_list|(
name|button
operator|->
name|color_area
argument_list|,
literal|"color_changed"
argument_list|,
name|G_CALLBACK
argument_list|(
name|gimp_color_button_color_changed
argument_list|)
argument_list|,
name|button
argument_list|)
expr_stmt|;
name|gtk_container_add
argument_list|(
name|GTK_CONTAINER
argument_list|(
name|button
argument_list|)
argument_list|,
name|button
operator|->
name|color_area
argument_list|)
expr_stmt|;
name|gtk_widget_show
argument_list|(
name|button
operator|->
name|color_area
argument_list|)
expr_stmt|;
comment|/* right-click opens a popup */
name|button
operator|->
name|item_factory
operator|=
name|gtk_item_factory_new
argument_list|(
name|GTK_TYPE_MENU
argument_list|,
literal|"<popup>"
argument_list|,
name|NULL
argument_list|)
expr_stmt|;
name|gtk_item_factory_set_translate_func
argument_list|(
name|button
operator|->
name|item_factory
argument_list|,
name|gimp_color_button_menu_translate
argument_list|,
name|NULL
argument_list|,
name|NULL
argument_list|)
expr_stmt|;
name|gtk_item_factory_create_items
argument_list|(
name|button
operator|->
name|item_factory
argument_list|,
name|G_N_ELEMENTS
argument_list|(
name|menu_items
argument_list|)
argument_list|,
name|menu_items
argument_list|,
name|button
argument_list|)
expr_stmt|;
block|}
end_function

begin_function
specifier|static
name|void
DECL|function|gimp_color_button_destroy (GtkObject * object)
name|gimp_color_button_destroy
parameter_list|(
name|GtkObject
modifier|*
name|object
parameter_list|)
block|{
name|GimpColorButton
modifier|*
name|button
decl_stmt|;
name|button
operator|=
name|GIMP_COLOR_BUTTON
argument_list|(
name|object
argument_list|)
expr_stmt|;
if|if
condition|(
name|button
operator|->
name|title
condition|)
block|{
name|g_free
argument_list|(
name|button
operator|->
name|title
argument_list|)
expr_stmt|;
name|button
operator|->
name|title
operator|=
name|NULL
expr_stmt|;
block|}
if|if
condition|(
name|button
operator|->
name|dialog
condition|)
block|{
name|gtk_widget_destroy
argument_list|(
name|button
operator|->
name|dialog
argument_list|)
expr_stmt|;
name|button
operator|->
name|dialog
operator|=
name|NULL
expr_stmt|;
block|}
if|if
condition|(
name|button
operator|->
name|color_area
condition|)
block|{
name|gtk_widget_destroy
argument_list|(
name|button
operator|->
name|color_area
argument_list|)
expr_stmt|;
name|button
operator|->
name|color_area
operator|=
name|NULL
expr_stmt|;
block|}
if|if
condition|(
name|GTK_OBJECT_CLASS
argument_list|(
name|parent_class
argument_list|)
operator|->
name|destroy
condition|)
name|GTK_OBJECT_CLASS
argument_list|(
name|parent_class
argument_list|)
operator|->
name|destroy
argument_list|(
name|object
argument_list|)
expr_stmt|;
block|}
end_function

begin_function
specifier|static
name|gboolean
DECL|function|gimp_color_button_button_press (GtkWidget * widget,GdkEventButton * bevent)
name|gimp_color_button_button_press
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
name|GimpColorButton
modifier|*
name|button
decl_stmt|;
name|gint
name|x
decl_stmt|;
name|gint
name|y
decl_stmt|;
name|button
operator|=
name|GIMP_COLOR_BUTTON
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
literal|3
condition|)
block|{
name|gdk_window_get_origin
argument_list|(
name|GTK_WIDGET
argument_list|(
name|widget
argument_list|)
operator|->
name|window
argument_list|,
operator|&
name|x
argument_list|,
operator|&
name|y
argument_list|)
expr_stmt|;
name|x
operator|+=
name|widget
operator|->
name|allocation
operator|.
name|x
expr_stmt|;
name|y
operator|+=
name|widget
operator|->
name|allocation
operator|.
name|y
expr_stmt|;
name|gtk_item_factory_popup
argument_list|(
name|button
operator|->
name|item_factory
argument_list|,
name|x
operator|+
name|bevent
operator|->
name|x
argument_list|,
name|y
operator|+
name|bevent
operator|->
name|y
argument_list|,
name|bevent
operator|->
name|button
argument_list|,
name|bevent
operator|->
name|time
argument_list|)
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
name|FALSE
return|;
block|}
end_function

begin_function
specifier|static
name|void
DECL|function|gimp_color_button_state_changed (GtkWidget * widget,GtkStateType prev_state)
name|gimp_color_button_state_changed
parameter_list|(
name|GtkWidget
modifier|*
name|widget
parameter_list|,
name|GtkStateType
name|prev_state
parameter_list|)
block|{
name|g_return_if_fail
argument_list|(
name|GIMP_IS_COLOR_BUTTON
argument_list|(
name|widget
argument_list|)
argument_list|)
expr_stmt|;
if|if
condition|(
operator|!
name|GTK_WIDGET_IS_SENSITIVE
argument_list|(
name|widget
argument_list|)
operator|&&
name|GIMP_COLOR_BUTTON
argument_list|(
name|widget
argument_list|)
operator|->
name|dialog
condition|)
name|gtk_widget_hide
argument_list|(
name|GIMP_COLOR_BUTTON
argument_list|(
name|widget
argument_list|)
operator|->
name|dialog
argument_list|)
expr_stmt|;
if|if
condition|(
name|GTK_WIDGET_CLASS
argument_list|(
name|parent_class
argument_list|)
operator|->
name|state_changed
condition|)
name|GTK_WIDGET_CLASS
argument_list|(
name|parent_class
argument_list|)
operator|->
name|state_changed
argument_list|(
name|widget
argument_list|,
name|prev_state
argument_list|)
expr_stmt|;
block|}
end_function

begin_comment
comment|/**  * gimp_color_button_new:  * @title: String that will be used as title for the color_selector.  * @width: Width of the colorpreview in pixels.  * @height: Height of the colorpreview in pixels.  * @color: A pointer to a #GimpRGB color.  * @type:   *   * Creates a new #GimpColorButton widget.  *  * This returns a button with a preview showing the color.  * When the button is clicked a GtkColorSelectionDialog is opened.  * If the user changes the color the new color is written into the  * array that was used to pass the initial color and the "color_changed"  * signal is emitted.  *   * Returns: Pointer to the new #GimpColorButton widget.  **/
end_comment

begin_function
name|GtkWidget
modifier|*
DECL|function|gimp_color_button_new (const gchar * title,gint width,gint height,const GimpRGB * color,GimpColorAreaType type)
name|gimp_color_button_new
parameter_list|(
specifier|const
name|gchar
modifier|*
name|title
parameter_list|,
name|gint
name|width
parameter_list|,
name|gint
name|height
parameter_list|,
specifier|const
name|GimpRGB
modifier|*
name|color
parameter_list|,
name|GimpColorAreaType
name|type
parameter_list|)
block|{
name|GimpColorButton
modifier|*
name|button
decl_stmt|;
name|g_return_val_if_fail
argument_list|(
name|color
operator|!=
name|NULL
argument_list|,
name|NULL
argument_list|)
expr_stmt|;
name|button
operator|=
name|g_object_new
argument_list|(
name|GIMP_TYPE_COLOR_BUTTON
argument_list|,
name|NULL
argument_list|)
expr_stmt|;
name|button
operator|->
name|title
operator|=
name|g_strdup
argument_list|(
name|title
argument_list|)
expr_stmt|;
name|gtk_widget_set_size_request
argument_list|(
name|GTK_WIDGET
argument_list|(
name|button
operator|->
name|color_area
argument_list|)
argument_list|,
name|width
argument_list|,
name|height
argument_list|)
expr_stmt|;
name|gimp_color_area_set_color
argument_list|(
name|GIMP_COLOR_AREA
argument_list|(
name|button
operator|->
name|color_area
argument_list|)
argument_list|,
name|color
argument_list|)
expr_stmt|;
name|gimp_color_area_set_type
argument_list|(
name|GIMP_COLOR_AREA
argument_list|(
name|button
operator|->
name|color_area
argument_list|)
argument_list|,
name|type
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
comment|/**  * gimp_color_button_set_color:  * @button: Pointer to a #GimpColorButton.  * @color: Pointer to the new #GimpRGB color.  *   * Sets the @button to the given @color.  **/
end_comment

begin_function
name|void
DECL|function|gimp_color_button_set_color (GimpColorButton * button,const GimpRGB * color)
name|gimp_color_button_set_color
parameter_list|(
name|GimpColorButton
modifier|*
name|button
parameter_list|,
specifier|const
name|GimpRGB
modifier|*
name|color
parameter_list|)
block|{
name|g_return_if_fail
argument_list|(
name|GIMP_IS_COLOR_BUTTON
argument_list|(
name|button
argument_list|)
argument_list|)
expr_stmt|;
name|g_return_if_fail
argument_list|(
name|color
operator|!=
name|NULL
argument_list|)
expr_stmt|;
name|gimp_color_area_set_color
argument_list|(
name|GIMP_COLOR_AREA
argument_list|(
name|button
operator|->
name|color_area
argument_list|)
argument_list|,
name|color
argument_list|)
expr_stmt|;
block|}
end_function

begin_comment
comment|/**  * gimp_color_button_get_color:  * @button: Pointer to a #GimpColorButton.  * @color: Pointer to a #GimpRGB struct used to return the color.  *   * Retrieves the currently set color from the @button.  **/
end_comment

begin_function
name|void
DECL|function|gimp_color_button_get_color (GimpColorButton * button,GimpRGB * color)
name|gimp_color_button_get_color
parameter_list|(
name|GimpColorButton
modifier|*
name|button
parameter_list|,
name|GimpRGB
modifier|*
name|color
parameter_list|)
block|{
name|g_return_if_fail
argument_list|(
name|GIMP_IS_COLOR_BUTTON
argument_list|(
name|button
argument_list|)
argument_list|)
expr_stmt|;
name|g_return_if_fail
argument_list|(
name|color
operator|!=
name|NULL
argument_list|)
expr_stmt|;
name|gimp_color_area_get_color
argument_list|(
name|GIMP_COLOR_AREA
argument_list|(
name|button
operator|->
name|color_area
argument_list|)
argument_list|,
name|color
argument_list|)
expr_stmt|;
block|}
end_function

begin_comment
comment|/**  * gimp_color_button_has_alpha:  * @button: Pointer to a #GimpColorButton.  *  * Checks whether the @buttons shows transparency information.  *  * Returns: %TRUE if the @button shows transparency information, %FALSE  * otherwise.  **/
end_comment

begin_function
name|gboolean
DECL|function|gimp_color_button_has_alpha (GimpColorButton * button)
name|gimp_color_button_has_alpha
parameter_list|(
name|GimpColorButton
modifier|*
name|button
parameter_list|)
block|{
name|g_return_val_if_fail
argument_list|(
name|GIMP_IS_COLOR_BUTTON
argument_list|(
name|button
argument_list|)
argument_list|,
name|FALSE
argument_list|)
expr_stmt|;
return|return
name|gimp_color_area_has_alpha
argument_list|(
name|GIMP_COLOR_AREA
argument_list|(
name|button
operator|->
name|color_area
argument_list|)
argument_list|)
return|;
block|}
end_function

begin_comment
comment|/**  * gimp_color_button_set_type:  * @button: Pointer to a #GimpColorButton.  * @type: the new #GimpColorAreaType  *  * Sets the @button to the given @type. See also gimp_color_area_set_type().  **/
end_comment

begin_function
name|void
DECL|function|gimp_color_button_set_type (GimpColorButton * button,GimpColorAreaType type)
name|gimp_color_button_set_type
parameter_list|(
name|GimpColorButton
modifier|*
name|button
parameter_list|,
name|GimpColorAreaType
name|type
parameter_list|)
block|{
name|g_return_if_fail
argument_list|(
name|GIMP_IS_COLOR_BUTTON
argument_list|(
name|button
argument_list|)
argument_list|)
expr_stmt|;
name|gimp_color_area_set_type
argument_list|(
name|GIMP_COLOR_AREA
argument_list|(
name|button
operator|->
name|color_area
argument_list|)
argument_list|,
name|type
argument_list|)
expr_stmt|;
block|}
end_function

begin_function
specifier|static
name|void
DECL|function|gimp_color_button_clicked (GtkButton * button)
name|gimp_color_button_clicked
parameter_list|(
name|GtkButton
modifier|*
name|button
parameter_list|)
block|{
name|GimpColorButton
modifier|*
name|color_button
decl_stmt|;
name|GtkWidget
modifier|*
name|dialog
decl_stmt|;
name|GimpRGB
name|color
decl_stmt|;
name|GdkColor
name|gdk_color
decl_stmt|;
name|guint16
name|alpha
decl_stmt|;
name|g_return_if_fail
argument_list|(
name|GIMP_IS_COLOR_BUTTON
argument_list|(
name|button
argument_list|)
argument_list|)
expr_stmt|;
name|color_button
operator|=
name|GIMP_COLOR_BUTTON
argument_list|(
name|button
argument_list|)
expr_stmt|;
name|gimp_color_button_get_color
argument_list|(
name|color_button
argument_list|,
operator|&
name|color
argument_list|)
expr_stmt|;
name|gdk_color
operator|.
name|red
operator|=
name|TOUINT16
argument_list|(
name|color
operator|.
name|r
argument_list|)
expr_stmt|;
name|gdk_color
operator|.
name|green
operator|=
name|TOUINT16
argument_list|(
name|color
operator|.
name|g
argument_list|)
expr_stmt|;
name|gdk_color
operator|.
name|blue
operator|=
name|TOUINT16
argument_list|(
name|color
operator|.
name|b
argument_list|)
expr_stmt|;
name|alpha
operator|=
name|TOUINT16
argument_list|(
name|color
operator|.
name|a
argument_list|)
expr_stmt|;
name|dialog
operator|=
name|color_button
operator|->
name|dialog
expr_stmt|;
if|if
condition|(
operator|!
name|dialog
condition|)
block|{
name|dialog
operator|=
name|gtk_color_selection_dialog_new
argument_list|(
name|color_button
operator|->
name|title
argument_list|)
expr_stmt|;
name|gtk_color_selection_set_has_opacity_control
argument_list|(
name|GTK_COLOR_SELECTION
argument_list|(
name|GTK_COLOR_SELECTION_DIALOG
argument_list|(
name|dialog
argument_list|)
operator|->
name|colorsel
argument_list|)
argument_list|,
name|gimp_color_button_has_alpha
argument_list|(
name|color_button
argument_list|)
argument_list|)
expr_stmt|;
name|gtk_widget_destroy
argument_list|(
name|GTK_COLOR_SELECTION_DIALOG
argument_list|(
name|dialog
argument_list|)
operator|->
name|help_button
argument_list|)
expr_stmt|;
name|gtk_container_set_border_width
argument_list|(
name|GTK_CONTAINER
argument_list|(
name|dialog
argument_list|)
argument_list|,
literal|2
argument_list|)
expr_stmt|;
name|g_signal_connect
argument_list|(
name|dialog
argument_list|,
literal|"destroy"
argument_list|,
name|G_CALLBACK
argument_list|(
name|gtk_widget_destroyed
argument_list|)
argument_list|,
operator|&
name|color_button
operator|->
name|dialog
argument_list|)
expr_stmt|;
name|g_signal_connect
argument_list|(
name|GTK_COLOR_SELECTION_DIALOG
argument_list|(
name|dialog
argument_list|)
operator|->
name|ok_button
argument_list|,
literal|"clicked"
argument_list|,
name|G_CALLBACK
argument_list|(
name|gimp_color_button_dialog_ok
argument_list|)
argument_list|,
name|color_button
argument_list|)
expr_stmt|;
name|g_signal_connect
argument_list|(
name|GTK_COLOR_SELECTION_DIALOG
argument_list|(
name|dialog
argument_list|)
operator|->
name|cancel_button
argument_list|,
literal|"clicked"
argument_list|,
name|G_CALLBACK
argument_list|(
name|gimp_color_button_dialog_cancel
argument_list|)
argument_list|,
name|color_button
argument_list|)
expr_stmt|;
name|gtk_window_set_position
argument_list|(
name|GTK_WINDOW
argument_list|(
name|dialog
argument_list|)
argument_list|,
name|GTK_WIN_POS_MOUSE
argument_list|)
expr_stmt|;
name|color_button
operator|->
name|dialog
operator|=
name|dialog
expr_stmt|;
block|}
name|gtk_color_selection_set_current_color
argument_list|(
name|GTK_COLOR_SELECTION
argument_list|(
name|GTK_COLOR_SELECTION_DIALOG
argument_list|(
name|dialog
argument_list|)
operator|->
name|colorsel
argument_list|)
argument_list|,
operator|&
name|gdk_color
argument_list|)
expr_stmt|;
name|gtk_color_selection_set_current_alpha
argument_list|(
name|GTK_COLOR_SELECTION
argument_list|(
name|GTK_COLOR_SELECTION_DIALOG
argument_list|(
name|dialog
argument_list|)
operator|->
name|colorsel
argument_list|)
argument_list|,
name|alpha
argument_list|)
expr_stmt|;
name|gtk_widget_show
argument_list|(
name|dialog
argument_list|)
expr_stmt|;
block|}
end_function

begin_function
specifier|static
name|void
DECL|function|gimp_color_button_dialog_ok (GtkWidget * widget,gpointer data)
name|gimp_color_button_dialog_ok
parameter_list|(
name|GtkWidget
modifier|*
name|widget
parameter_list|,
name|gpointer
name|data
parameter_list|)
block|{
name|GimpColorButton
modifier|*
name|button
decl_stmt|;
name|GimpRGB
name|color
decl_stmt|;
name|GdkColor
name|gdk_color
decl_stmt|;
name|guint16
name|alpha
decl_stmt|;
name|g_return_if_fail
argument_list|(
name|GIMP_IS_COLOR_BUTTON
argument_list|(
name|data
argument_list|)
argument_list|)
expr_stmt|;
name|button
operator|=
name|GIMP_COLOR_BUTTON
argument_list|(
name|data
argument_list|)
expr_stmt|;
name|gtk_color_selection_get_current_color
argument_list|(
name|GTK_COLOR_SELECTION
argument_list|(
name|GTK_COLOR_SELECTION_DIALOG
argument_list|(
name|button
operator|->
name|dialog
argument_list|)
operator|->
name|colorsel
argument_list|)
argument_list|,
operator|&
name|gdk_color
argument_list|)
expr_stmt|;
name|alpha
operator|=
name|gtk_color_selection_get_current_alpha
argument_list|(
name|GTK_COLOR_SELECTION
argument_list|(
name|GTK_COLOR_SELECTION_DIALOG
argument_list|(
name|button
operator|->
name|dialog
argument_list|)
operator|->
name|colorsel
argument_list|)
argument_list|)
expr_stmt|;
name|color
operator|.
name|r
operator|=
name|TODOUBLE
argument_list|(
name|gdk_color
operator|.
name|red
argument_list|)
expr_stmt|;
name|color
operator|.
name|g
operator|=
name|TODOUBLE
argument_list|(
name|gdk_color
operator|.
name|green
argument_list|)
expr_stmt|;
name|color
operator|.
name|b
operator|=
name|TODOUBLE
argument_list|(
name|gdk_color
operator|.
name|blue
argument_list|)
expr_stmt|;
name|color
operator|.
name|a
operator|=
name|TODOUBLE
argument_list|(
name|alpha
argument_list|)
expr_stmt|;
name|gimp_color_button_set_color
argument_list|(
name|button
argument_list|,
operator|&
name|color
argument_list|)
expr_stmt|;
name|gtk_widget_hide
argument_list|(
name|button
operator|->
name|dialog
argument_list|)
expr_stmt|;
block|}
end_function

begin_function
specifier|static
name|void
DECL|function|gimp_color_button_dialog_cancel (GtkWidget * widget,gpointer data)
name|gimp_color_button_dialog_cancel
parameter_list|(
name|GtkWidget
modifier|*
name|widget
parameter_list|,
name|gpointer
name|data
parameter_list|)
block|{
name|g_return_if_fail
argument_list|(
name|GIMP_IS_COLOR_BUTTON
argument_list|(
name|data
argument_list|)
argument_list|)
expr_stmt|;
name|gtk_widget_hide
argument_list|(
name|GIMP_COLOR_BUTTON
argument_list|(
name|data
argument_list|)
operator|->
name|dialog
argument_list|)
expr_stmt|;
block|}
end_function

begin_function
specifier|static
name|void
DECL|function|gimp_color_button_use_color (gpointer callback_data,guint callback_action,GtkWidget * widget)
name|gimp_color_button_use_color
parameter_list|(
name|gpointer
name|callback_data
parameter_list|,
name|guint
name|callback_action
parameter_list|,
name|GtkWidget
modifier|*
name|widget
parameter_list|)
block|{
name|GimpRGB
name|color
decl_stmt|;
name|GimpColorButtonColor
name|type
decl_stmt|;
name|type
operator|=
operator|(
name|GimpColorButtonColor
operator|)
name|callback_action
expr_stmt|;
name|gimp_color_button_get_color
argument_list|(
name|GIMP_COLOR_BUTTON
argument_list|(
name|callback_data
argument_list|)
argument_list|,
operator|&
name|color
argument_list|)
expr_stmt|;
switch|switch
condition|(
name|type
condition|)
block|{
case|case
name|GIMP_COLOR_BUTTON_COLOR_FG
case|:
name|gimp_palette_get_foreground
argument_list|(
operator|&
name|color
argument_list|)
expr_stmt|;
break|break;
case|case
name|GIMP_COLOR_BUTTON_COLOR_BG
case|:
name|gimp_palette_get_background
argument_list|(
operator|&
name|color
argument_list|)
expr_stmt|;
break|break;
case|case
name|GIMP_COLOR_BUTTON_COLOR_BLACK
case|:
name|gimp_rgb_set
argument_list|(
operator|&
name|color
argument_list|,
literal|0.0
argument_list|,
literal|0.0
argument_list|,
literal|0.0
argument_list|)
expr_stmt|;
break|break;
case|case
name|GIMP_COLOR_BUTTON_COLOR_WHITE
case|:
name|gimp_rgb_set
argument_list|(
operator|&
name|color
argument_list|,
literal|1.0
argument_list|,
literal|1.0
argument_list|,
literal|1.0
argument_list|)
expr_stmt|;
break|break;
block|}
name|gimp_color_button_set_color
argument_list|(
name|GIMP_COLOR_BUTTON
argument_list|(
name|callback_data
argument_list|)
argument_list|,
operator|&
name|color
argument_list|)
expr_stmt|;
block|}
end_function

begin_function
specifier|static
name|void
DECL|function|gimp_color_button_color_changed (GtkObject * object,gpointer data)
name|gimp_color_button_color_changed
parameter_list|(
name|GtkObject
modifier|*
name|object
parameter_list|,
name|gpointer
name|data
parameter_list|)
block|{
name|GimpColorButton
modifier|*
name|button
init|=
name|GIMP_COLOR_BUTTON
argument_list|(
name|data
argument_list|)
decl_stmt|;
if|if
condition|(
name|button
operator|->
name|dialog
condition|)
block|{
name|GimpRGB
name|color
decl_stmt|;
name|GdkColor
name|gdk_color
decl_stmt|;
name|guint16
name|alpha
decl_stmt|;
name|gimp_color_button_get_color
argument_list|(
name|GIMP_COLOR_BUTTON
argument_list|(
name|data
argument_list|)
argument_list|,
operator|&
name|color
argument_list|)
expr_stmt|;
name|gdk_color
operator|.
name|red
operator|=
name|TOUINT16
argument_list|(
name|color
operator|.
name|r
argument_list|)
expr_stmt|;
name|gdk_color
operator|.
name|green
operator|=
name|TOUINT16
argument_list|(
name|color
operator|.
name|g
argument_list|)
expr_stmt|;
name|gdk_color
operator|.
name|blue
operator|=
name|TOUINT16
argument_list|(
name|color
operator|.
name|b
argument_list|)
expr_stmt|;
name|alpha
operator|=
name|TOUINT16
argument_list|(
name|color
operator|.
name|a
argument_list|)
expr_stmt|;
name|gtk_color_selection_set_current_color
argument_list|(
name|GTK_COLOR_SELECTION
argument_list|(
name|GTK_COLOR_SELECTION_DIALOG
argument_list|(
name|button
operator|->
name|dialog
argument_list|)
operator|->
name|colorsel
argument_list|)
argument_list|,
operator|&
name|gdk_color
argument_list|)
expr_stmt|;
name|gtk_color_selection_set_current_alpha
argument_list|(
name|GTK_COLOR_SELECTION
argument_list|(
name|GTK_COLOR_SELECTION_DIALOG
argument_list|(
name|button
operator|->
name|dialog
argument_list|)
operator|->
name|colorsel
argument_list|)
argument_list|,
name|alpha
argument_list|)
expr_stmt|;
block|}
name|g_signal_emit
argument_list|(
name|button
argument_list|,
name|gimp_color_button_signals
index|[
name|COLOR_CHANGED
index|]
argument_list|,
literal|0
argument_list|)
expr_stmt|;
block|}
end_function

begin_function
specifier|static
name|gchar
modifier|*
DECL|function|gimp_color_button_menu_translate (const gchar * path,gpointer func_data)
name|gimp_color_button_menu_translate
parameter_list|(
specifier|const
name|gchar
modifier|*
name|path
parameter_list|,
name|gpointer
name|func_data
parameter_list|)
block|{
return|return
operator|(
name|gettext
argument_list|(
name|path
argument_list|)
operator|)
return|;
block|}
end_function

end_unit

