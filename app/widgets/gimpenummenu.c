begin_unit|revision:0.9.5;language:C;cregit-version:0.0.1
begin_comment
comment|/* The GIMP -- an image manipulation program  * Copyright (C) 1995 Spencer Kimball and Peter Mattis  *  * gimpenummenu.c  * Copyright (C) 2002  Sven Neumann<sven@gimp.org>  *  * This program is free software; you can redistribute it and/or modify  * it under the terms of the GNU General Public License as published by  * the Free Software Foundation; either version 2 of the License, or  * (at your option) any later version.  *  * This program is distributed in the hope that it will be useful,  * but WITHOUT ANY WARRANTY; without even the implied warranty of  * MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the  * GNU General Public License for more details.  *  * You should have received a copy of the GNU General Public License  * along with this program; if not, write to the Free Software  * Foundation, Inc., 59 Temple Place - Suite 330, Boston, MA 02111-1307, USA.  */
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
file|"libgimpwidgets/gimpwidgets.h"
end_include

begin_include
include|#
directive|include
file|"widgets-types.h"
end_include

begin_include
include|#
directive|include
file|"gimpenummenu.h"
end_include

begin_include
include|#
directive|include
file|"libgimp/gimpintl.h"
end_include

begin_function_decl
specifier|static
name|void
name|gimp_enum_menu_class_init
parameter_list|(
name|GimpEnumMenuClass
modifier|*
name|klass
parameter_list|)
function_decl|;
end_function_decl

begin_function_decl
specifier|static
name|void
name|gimp_enum_menu_init
parameter_list|(
name|GimpEnumMenu
modifier|*
name|enum_menu
parameter_list|)
function_decl|;
end_function_decl

begin_function_decl
specifier|static
name|void
name|gimp_enum_menu_finalize
parameter_list|(
name|GObject
modifier|*
name|object
parameter_list|)
function_decl|;
end_function_decl

begin_decl_stmt
DECL|variable|parent_class
specifier|static
name|GtkMenuClass
modifier|*
name|parent_class
init|=
name|NULL
decl_stmt|;
end_decl_stmt

begin_function
name|GType
DECL|function|gimp_enum_menu_get_type (void)
name|gimp_enum_menu_get_type
parameter_list|(
name|void
parameter_list|)
block|{
specifier|static
name|GType
name|enum_menu_type
init|=
literal|0
decl_stmt|;
if|if
condition|(
operator|!
name|enum_menu_type
condition|)
block|{
specifier|static
specifier|const
name|GTypeInfo
name|enum_menu_info
init|=
block|{
sizeof|sizeof
argument_list|(
name|GimpEnumMenuClass
argument_list|)
block|,
name|NULL
block|,
comment|/* base_init */
name|NULL
block|,
comment|/* base_finalize */
operator|(
name|GClassInitFunc
operator|)
name|gimp_enum_menu_class_init
block|,
name|NULL
block|,
comment|/* class_finalize */
name|NULL
block|,
comment|/* class_data */
sizeof|sizeof
argument_list|(
name|GimpEnumMenu
argument_list|)
block|,
literal|0
block|,
comment|/* n_preallocs */
operator|(
name|GInstanceInitFunc
operator|)
name|gimp_enum_menu_init
block|,       }
decl_stmt|;
name|enum_menu_type
operator|=
name|g_type_register_static
argument_list|(
name|GTK_TYPE_MENU
argument_list|,
literal|"GimpEnumMenu"
argument_list|,
operator|&
name|enum_menu_info
argument_list|,
literal|0
argument_list|)
expr_stmt|;
block|}
return|return
name|enum_menu_type
return|;
block|}
end_function

begin_function
specifier|static
name|void
DECL|function|gimp_enum_menu_class_init (GimpEnumMenuClass * klass)
name|gimp_enum_menu_class_init
parameter_list|(
name|GimpEnumMenuClass
modifier|*
name|klass
parameter_list|)
block|{
name|GObjectClass
modifier|*
name|object_class
decl_stmt|;
name|parent_class
operator|=
name|g_type_class_peek_parent
argument_list|(
name|klass
argument_list|)
expr_stmt|;
name|object_class
operator|=
name|G_OBJECT_CLASS
argument_list|(
name|klass
argument_list|)
expr_stmt|;
name|object_class
operator|->
name|finalize
operator|=
name|gimp_enum_menu_finalize
expr_stmt|;
block|}
end_function

begin_function
specifier|static
name|void
DECL|function|gimp_enum_menu_init (GimpEnumMenu * enum_menu)
name|gimp_enum_menu_init
parameter_list|(
name|GimpEnumMenu
modifier|*
name|enum_menu
parameter_list|)
block|{
name|enum_menu
operator|->
name|enum_class
operator|=
name|NULL
expr_stmt|;
block|}
end_function

begin_function
specifier|static
name|void
DECL|function|gimp_enum_menu_finalize (GObject * object)
name|gimp_enum_menu_finalize
parameter_list|(
name|GObject
modifier|*
name|object
parameter_list|)
block|{
name|GimpEnumMenu
modifier|*
name|enum_menu
init|=
name|GIMP_ENUM_MENU
argument_list|(
name|object
argument_list|)
decl_stmt|;
if|if
condition|(
name|enum_menu
operator|->
name|enum_class
condition|)
name|g_type_class_unref
argument_list|(
name|enum_menu
operator|->
name|enum_class
argument_list|)
expr_stmt|;
name|G_OBJECT_CLASS
argument_list|(
name|parent_class
argument_list|)
operator|->
name|finalize
argument_list|(
name|object
argument_list|)
expr_stmt|;
block|}
end_function

begin_comment
comment|/**  * gimp_enum_menu_new:  * @enum_type: the #GType of an enum.  * @callback: a callback to connect to the "activate" signal of each  *            #GtkMenuItem that is created.  * @callback_data: data to pass to the @callback.   *   * Creates a new #GimpEnumMenu, derived from #GtkMenu with menu items  * for each of the enum values. The enum needs to be registered to the  * type system and should have translatable value names.  *  * To each menu item it's enum value is attached as "gimp-item-data".  * Therefore you can use gimp_menu_item_update() from libgimpwidgets  * as @callback function.  *   * Return value: a new #GimpEnumMenu.  **/
end_comment

begin_function
name|GtkWidget
modifier|*
DECL|function|gimp_enum_menu_new (GType enum_type,GCallback callback,gpointer callback_data)
name|gimp_enum_menu_new
parameter_list|(
name|GType
name|enum_type
parameter_list|,
name|GCallback
name|callback
parameter_list|,
name|gpointer
name|callback_data
parameter_list|)
block|{
name|GEnumClass
modifier|*
name|enum_class
decl_stmt|;
name|GtkWidget
modifier|*
name|menu
decl_stmt|;
name|g_return_val_if_fail
argument_list|(
name|G_TYPE_IS_ENUM
argument_list|(
name|enum_type
argument_list|)
argument_list|,
name|NULL
argument_list|)
expr_stmt|;
name|enum_class
operator|=
name|g_type_class_ref
argument_list|(
name|enum_type
argument_list|)
expr_stmt|;
name|menu
operator|=
name|gimp_enum_menu_new_with_range
argument_list|(
name|enum_type
argument_list|,
name|enum_class
operator|->
name|minimum
argument_list|,
name|enum_class
operator|->
name|maximum
argument_list|,
name|callback
argument_list|,
name|callback_data
argument_list|)
expr_stmt|;
name|g_type_class_unref
argument_list|(
name|enum_class
argument_list|)
expr_stmt|;
return|return
name|menu
return|;
block|}
end_function

begin_function
name|GtkWidget
modifier|*
DECL|function|gimp_enum_menu_new_with_range (GType enum_type,gint minimum,gint maximum,GCallback callback,gpointer callback_data)
name|gimp_enum_menu_new_with_range
parameter_list|(
name|GType
name|enum_type
parameter_list|,
name|gint
name|minimum
parameter_list|,
name|gint
name|maximum
parameter_list|,
name|GCallback
name|callback
parameter_list|,
name|gpointer
name|callback_data
parameter_list|)
block|{
name|GimpEnumMenu
modifier|*
name|menu
decl_stmt|;
name|GtkWidget
modifier|*
name|menu_item
decl_stmt|;
name|GEnumValue
modifier|*
name|value
decl_stmt|;
name|g_return_val_if_fail
argument_list|(
name|G_TYPE_IS_ENUM
argument_list|(
name|enum_type
argument_list|)
argument_list|,
name|NULL
argument_list|)
expr_stmt|;
name|menu
operator|=
name|g_object_new
argument_list|(
name|GIMP_TYPE_ENUM_MENU
argument_list|,
name|NULL
argument_list|)
expr_stmt|;
name|menu
operator|->
name|enum_class
operator|=
name|g_type_class_ref
argument_list|(
name|enum_type
argument_list|)
expr_stmt|;
for|for
control|(
name|value
operator|=
name|menu
operator|->
name|enum_class
operator|->
name|values
init|;
name|value
operator|->
name|value_name
condition|;
name|value
operator|++
control|)
block|{
if|if
condition|(
name|value
operator|->
name|value
operator|<
name|minimum
operator|||
name|value
operator|->
name|value
operator|>
name|maximum
condition|)
continue|continue;
name|menu_item
operator|=
name|gtk_menu_item_new_with_label
argument_list|(
name|gettext
argument_list|(
name|value
operator|->
name|value_name
argument_list|)
argument_list|)
expr_stmt|;
name|gtk_menu_shell_append
argument_list|(
name|GTK_MENU_SHELL
argument_list|(
name|menu
argument_list|)
argument_list|,
name|menu_item
argument_list|)
expr_stmt|;
name|gtk_widget_show
argument_list|(
name|menu_item
argument_list|)
expr_stmt|;
name|g_object_set_data
argument_list|(
name|G_OBJECT
argument_list|(
name|menu_item
argument_list|)
argument_list|,
literal|"gimp-item-data"
argument_list|,
name|GINT_TO_POINTER
argument_list|(
name|value
operator|->
name|value
argument_list|)
argument_list|)
expr_stmt|;
if|if
condition|(
name|callback
condition|)
name|g_signal_connect
argument_list|(
name|menu_item
argument_list|,
literal|"activate"
argument_list|,
name|callback
argument_list|,
name|callback_data
argument_list|)
expr_stmt|;
block|}
return|return
name|GTK_WIDGET
argument_list|(
name|menu
argument_list|)
return|;
block|}
end_function

begin_function
name|GtkWidget
modifier|*
DECL|function|gimp_enum_menu_new_with_values (GType enum_type,GCallback callback,gpointer callback_data,gint n_values,...)
name|gimp_enum_menu_new_with_values
parameter_list|(
name|GType
name|enum_type
parameter_list|,
name|GCallback
name|callback
parameter_list|,
name|gpointer
name|callback_data
parameter_list|,
name|gint
name|n_values
parameter_list|,
modifier|...
parameter_list|)
block|{
name|GtkWidget
modifier|*
name|menu
decl_stmt|;
name|va_list
name|args
decl_stmt|;
name|va_start
argument_list|(
name|args
argument_list|,
name|n_values
argument_list|)
expr_stmt|;
name|menu
operator|=
name|gimp_enum_menu_new_with_values_valist
argument_list|(
name|enum_type
argument_list|,
name|callback
argument_list|,
name|callback_data
argument_list|,
name|n_values
argument_list|,
name|args
argument_list|)
expr_stmt|;
name|va_end
argument_list|(
name|args
argument_list|)
expr_stmt|;
return|return
name|menu
return|;
block|}
end_function

begin_function
name|GtkWidget
modifier|*
DECL|function|gimp_enum_menu_new_with_values_valist (GType enum_type,GCallback callback,gpointer callback_data,gint n_values,va_list args)
name|gimp_enum_menu_new_with_values_valist
parameter_list|(
name|GType
name|enum_type
parameter_list|,
name|GCallback
name|callback
parameter_list|,
name|gpointer
name|callback_data
parameter_list|,
name|gint
name|n_values
parameter_list|,
name|va_list
name|args
parameter_list|)
block|{
name|GimpEnumMenu
modifier|*
name|menu
decl_stmt|;
name|GtkWidget
modifier|*
name|menu_item
decl_stmt|;
name|GEnumValue
modifier|*
name|value
decl_stmt|;
name|gint
name|i
decl_stmt|;
name|g_return_val_if_fail
argument_list|(
name|G_TYPE_IS_ENUM
argument_list|(
name|enum_type
argument_list|)
argument_list|,
name|NULL
argument_list|)
expr_stmt|;
name|g_return_val_if_fail
argument_list|(
name|n_values
operator|>
literal|1
argument_list|,
name|NULL
argument_list|)
expr_stmt|;
name|menu
operator|=
name|g_object_new
argument_list|(
name|GIMP_TYPE_ENUM_MENU
argument_list|,
name|NULL
argument_list|)
expr_stmt|;
name|menu
operator|->
name|enum_class
operator|=
name|g_type_class_ref
argument_list|(
name|enum_type
argument_list|)
expr_stmt|;
for|for
control|(
name|i
operator|=
literal|0
init|;
name|i
operator|<
name|n_values
condition|;
name|i
operator|++
control|)
block|{
name|value
operator|=
name|g_enum_get_value
argument_list|(
name|menu
operator|->
name|enum_class
argument_list|,
name|va_arg
argument_list|(
name|args
argument_list|,
name|gint
argument_list|)
argument_list|)
expr_stmt|;
if|if
condition|(
name|value
condition|)
block|{
name|menu_item
operator|=
name|gtk_menu_item_new_with_label
argument_list|(
name|gettext
argument_list|(
name|value
operator|->
name|value_name
argument_list|)
argument_list|)
expr_stmt|;
name|gtk_menu_shell_append
argument_list|(
name|GTK_MENU_SHELL
argument_list|(
name|menu
argument_list|)
argument_list|,
name|menu_item
argument_list|)
expr_stmt|;
name|gtk_widget_show
argument_list|(
name|menu_item
argument_list|)
expr_stmt|;
name|g_object_set_data
argument_list|(
name|G_OBJECT
argument_list|(
name|menu_item
argument_list|)
argument_list|,
literal|"gimp-item-data"
argument_list|,
name|GINT_TO_POINTER
argument_list|(
name|value
operator|->
name|value
argument_list|)
argument_list|)
expr_stmt|;
if|if
condition|(
name|callback
condition|)
name|g_signal_connect
argument_list|(
name|menu_item
argument_list|,
literal|"activate"
argument_list|,
name|callback
argument_list|,
name|callback_data
argument_list|)
expr_stmt|;
block|}
block|}
return|return
name|GTK_WIDGET
argument_list|(
name|menu
argument_list|)
return|;
block|}
end_function

begin_comment
comment|/**  * gimp_enum_option_menu_new:  * @enum_type: the #GType of an enum.  * @callback: a callback to connect to the "activate" signal of each  *            #GtkMenuItem that is created.  * @callback_data: data to pass to the @callback.   *   * This function calls gimp_enum_menu_new() for you and attaches  * the resulting @GtkMenu to a newly created #GtkOptionMenu.  *  * Return value: a new #GtkOptionMenu.  **/
end_comment

begin_function
name|GtkWidget
modifier|*
DECL|function|gimp_enum_option_menu_new (GType enum_type,GCallback callback,gpointer callback_data)
name|gimp_enum_option_menu_new
parameter_list|(
name|GType
name|enum_type
parameter_list|,
name|GCallback
name|callback
parameter_list|,
name|gpointer
name|callback_data
parameter_list|)
block|{
name|GtkWidget
modifier|*
name|option_menu
decl_stmt|;
name|GtkWidget
modifier|*
name|menu
decl_stmt|;
name|g_return_val_if_fail
argument_list|(
name|G_TYPE_IS_ENUM
argument_list|(
name|enum_type
argument_list|)
argument_list|,
name|NULL
argument_list|)
expr_stmt|;
name|menu
operator|=
name|gimp_enum_menu_new
argument_list|(
name|enum_type
argument_list|,
name|callback
argument_list|,
name|callback_data
argument_list|)
expr_stmt|;
name|option_menu
operator|=
name|gtk_option_menu_new
argument_list|()
expr_stmt|;
name|gtk_option_menu_set_menu
argument_list|(
name|GTK_OPTION_MENU
argument_list|(
name|option_menu
argument_list|)
argument_list|,
name|menu
argument_list|)
expr_stmt|;
return|return
name|option_menu
return|;
block|}
end_function

begin_function
name|GtkWidget
modifier|*
DECL|function|gimp_enum_option_menu_new_with_range (GType enum_type,gint minimum,gint maximum,GCallback callback,gpointer callback_data)
name|gimp_enum_option_menu_new_with_range
parameter_list|(
name|GType
name|enum_type
parameter_list|,
name|gint
name|minimum
parameter_list|,
name|gint
name|maximum
parameter_list|,
name|GCallback
name|callback
parameter_list|,
name|gpointer
name|callback_data
parameter_list|)
block|{
name|GtkWidget
modifier|*
name|option_menu
decl_stmt|;
name|GtkWidget
modifier|*
name|menu
decl_stmt|;
name|g_return_val_if_fail
argument_list|(
name|G_TYPE_IS_ENUM
argument_list|(
name|enum_type
argument_list|)
argument_list|,
name|NULL
argument_list|)
expr_stmt|;
name|menu
operator|=
name|gimp_enum_menu_new_with_range
argument_list|(
name|enum_type
argument_list|,
name|minimum
argument_list|,
name|maximum
argument_list|,
name|callback
argument_list|,
name|callback_data
argument_list|)
expr_stmt|;
name|option_menu
operator|=
name|gtk_option_menu_new
argument_list|()
expr_stmt|;
name|gtk_option_menu_set_menu
argument_list|(
name|GTK_OPTION_MENU
argument_list|(
name|option_menu
argument_list|)
argument_list|,
name|menu
argument_list|)
expr_stmt|;
return|return
name|option_menu
return|;
block|}
end_function

begin_function
name|GtkWidget
modifier|*
DECL|function|gimp_enum_option_menu_new_with_values (GType enum_type,GCallback callback,gpointer callback_data,gint n_values,...)
name|gimp_enum_option_menu_new_with_values
parameter_list|(
name|GType
name|enum_type
parameter_list|,
name|GCallback
name|callback
parameter_list|,
name|gpointer
name|callback_data
parameter_list|,
name|gint
name|n_values
parameter_list|,
modifier|...
parameter_list|)
block|{
name|GtkWidget
modifier|*
name|option_menu
decl_stmt|;
name|va_list
name|args
decl_stmt|;
name|va_start
argument_list|(
name|args
argument_list|,
name|n_values
argument_list|)
expr_stmt|;
name|option_menu
operator|=
name|gimp_enum_option_menu_new_with_values_valist
argument_list|(
name|enum_type
argument_list|,
name|callback
argument_list|,
name|callback_data
argument_list|,
name|n_values
argument_list|,
name|args
argument_list|)
expr_stmt|;
name|va_end
argument_list|(
name|args
argument_list|)
expr_stmt|;
return|return
name|option_menu
return|;
block|}
end_function

begin_function
name|GtkWidget
modifier|*
DECL|function|gimp_enum_option_menu_new_with_values_valist (GType enum_type,GCallback callback,gpointer callback_data,gint n_values,va_list args)
name|gimp_enum_option_menu_new_with_values_valist
parameter_list|(
name|GType
name|enum_type
parameter_list|,
name|GCallback
name|callback
parameter_list|,
name|gpointer
name|callback_data
parameter_list|,
name|gint
name|n_values
parameter_list|,
name|va_list
name|args
parameter_list|)
block|{
name|GtkWidget
modifier|*
name|option_menu
init|=
name|NULL
decl_stmt|;
name|GtkWidget
modifier|*
name|menu
decl_stmt|;
name|menu
operator|=
name|gimp_enum_menu_new_with_values_valist
argument_list|(
name|enum_type
argument_list|,
name|callback
argument_list|,
name|callback_data
argument_list|,
name|n_values
argument_list|,
name|args
argument_list|)
expr_stmt|;
if|if
condition|(
name|menu
condition|)
block|{
name|option_menu
operator|=
name|gtk_option_menu_new
argument_list|()
expr_stmt|;
name|gtk_option_menu_set_menu
argument_list|(
name|GTK_OPTION_MENU
argument_list|(
name|option_menu
argument_list|)
argument_list|,
name|menu
argument_list|)
expr_stmt|;
block|}
return|return
name|option_menu
return|;
block|}
end_function

begin_comment
comment|/**  * gimp_enum_radio_box_new:  * @enum_type: the #GType of an enum.  * @callback: a callback to connect to the "toggled" signal of each  *            #GtkRadioButton that is created.  * @callback_data: data to pass to the @callback.   * @first_button: returns the first button in the created group.  *   * Creates a new group of #GtkRadioButtons representing the enum values.  * This is very similar to gimp_enum_menu_new().  *   * Return value: a new #GtkVBox holding a group of #GtkRadioButtons.  **/
end_comment

begin_function
name|GtkWidget
modifier|*
DECL|function|gimp_enum_radio_box_new (GType enum_type,GCallback callback,gpointer callback_data,GtkWidget ** first_button)
name|gimp_enum_radio_box_new
parameter_list|(
name|GType
name|enum_type
parameter_list|,
name|GCallback
name|callback
parameter_list|,
name|gpointer
name|callback_data
parameter_list|,
name|GtkWidget
modifier|*
modifier|*
name|first_button
parameter_list|)
block|{
name|GEnumClass
modifier|*
name|enum_class
decl_stmt|;
name|GtkWidget
modifier|*
name|vbox
decl_stmt|;
name|g_return_val_if_fail
argument_list|(
name|G_TYPE_IS_ENUM
argument_list|(
name|enum_type
argument_list|)
argument_list|,
name|NULL
argument_list|)
expr_stmt|;
name|enum_class
operator|=
name|g_type_class_ref
argument_list|(
name|enum_type
argument_list|)
expr_stmt|;
name|vbox
operator|=
name|gimp_enum_radio_box_new_with_range
argument_list|(
name|enum_type
argument_list|,
name|enum_class
operator|->
name|minimum
argument_list|,
name|enum_class
operator|->
name|maximum
argument_list|,
name|callback
argument_list|,
name|callback_data
argument_list|,
name|first_button
argument_list|)
expr_stmt|;
name|g_type_class_unref
argument_list|(
name|enum_class
argument_list|)
expr_stmt|;
return|return
name|vbox
return|;
block|}
end_function

begin_function
name|GtkWidget
modifier|*
DECL|function|gimp_enum_radio_box_new_with_range (GType enum_type,gint minimum,gint maximum,GCallback callback,gpointer callback_data,GtkWidget ** first_button)
name|gimp_enum_radio_box_new_with_range
parameter_list|(
name|GType
name|enum_type
parameter_list|,
name|gint
name|minimum
parameter_list|,
name|gint
name|maximum
parameter_list|,
name|GCallback
name|callback
parameter_list|,
name|gpointer
name|callback_data
parameter_list|,
name|GtkWidget
modifier|*
modifier|*
name|first_button
parameter_list|)
block|{
name|GtkWidget
modifier|*
name|vbox
decl_stmt|;
name|GtkWidget
modifier|*
name|button
decl_stmt|;
name|GEnumClass
modifier|*
name|enum_class
decl_stmt|;
name|GEnumValue
modifier|*
name|value
decl_stmt|;
name|GSList
modifier|*
name|group
init|=
name|NULL
decl_stmt|;
name|g_return_val_if_fail
argument_list|(
name|G_TYPE_IS_ENUM
argument_list|(
name|enum_type
argument_list|)
argument_list|,
name|NULL
argument_list|)
expr_stmt|;
name|enum_class
operator|=
name|g_type_class_ref
argument_list|(
name|enum_type
argument_list|)
expr_stmt|;
name|vbox
operator|=
name|gtk_vbox_new
argument_list|(
name|FALSE
argument_list|,
literal|1
argument_list|)
expr_stmt|;
name|g_object_weak_ref
argument_list|(
name|G_OBJECT
argument_list|(
name|vbox
argument_list|)
argument_list|,
operator|(
name|GWeakNotify
operator|)
name|g_type_class_unref
argument_list|,
name|enum_class
argument_list|)
expr_stmt|;
if|if
condition|(
name|first_button
condition|)
operator|*
name|first_button
operator|=
name|NULL
expr_stmt|;
for|for
control|(
name|value
operator|=
name|enum_class
operator|->
name|values
init|;
name|value
operator|->
name|value_name
condition|;
name|value
operator|++
control|)
block|{
if|if
condition|(
name|value
operator|->
name|value
operator|<
name|minimum
operator|||
name|value
operator|->
name|value
operator|>
name|maximum
condition|)
continue|continue;
name|button
operator|=
name|gtk_radio_button_new_with_label
argument_list|(
name|group
argument_list|,
name|gettext
argument_list|(
name|value
operator|->
name|value_name
argument_list|)
argument_list|)
expr_stmt|;
if|if
condition|(
name|first_button
operator|&&
operator|*
name|first_button
operator|==
name|NULL
condition|)
operator|*
name|first_button
operator|=
name|button
expr_stmt|;
name|group
operator|=
name|gtk_radio_button_get_group
argument_list|(
name|GTK_RADIO_BUTTON
argument_list|(
name|button
argument_list|)
argument_list|)
expr_stmt|;
name|gtk_box_pack_start
argument_list|(
name|GTK_BOX
argument_list|(
name|vbox
argument_list|)
argument_list|,
name|button
argument_list|,
name|FALSE
argument_list|,
name|FALSE
argument_list|,
literal|0
argument_list|)
expr_stmt|;
name|gtk_widget_show
argument_list|(
name|button
argument_list|)
expr_stmt|;
name|g_object_set_data
argument_list|(
name|G_OBJECT
argument_list|(
name|button
argument_list|)
argument_list|,
literal|"gimp-item-data"
argument_list|,
name|GINT_TO_POINTER
argument_list|(
name|value
operator|->
name|value
argument_list|)
argument_list|)
expr_stmt|;
if|if
condition|(
name|callback
condition|)
name|g_signal_connect
argument_list|(
name|button
argument_list|,
literal|"toggled"
argument_list|,
name|callback
argument_list|,
name|callback_data
argument_list|)
expr_stmt|;
block|}
return|return
name|vbox
return|;
block|}
end_function

begin_comment
comment|/**  * gimp_enum_radio_frame_new:  * @enum_type: the #GType of an enum.  * @label_widget: a widget to put into the frame that will hold the radio box.  * @border_width: the border_width of the vbox inside the frame.  * @callback: a callback to connect to the "toggled" signal of each  *            #GtkRadioButton that is created.  * @callback_data: data to pass to the @callback.  * @first_button: returns the first button in the created group.  *  * Calls gimp_enum_radio_box_new() and puts the resulting vbox into a  * #GtkFrame.  *   * Return value: a new #GtkFrame holding a group of #GtkRadioButtons.  **/
end_comment

begin_function
name|GtkWidget
modifier|*
DECL|function|gimp_enum_radio_frame_new (GType enum_type,GtkWidget * label_widget,gint border_width,GCallback callback,gpointer callback_data,GtkWidget ** first_button)
name|gimp_enum_radio_frame_new
parameter_list|(
name|GType
name|enum_type
parameter_list|,
name|GtkWidget
modifier|*
name|label_widget
parameter_list|,
name|gint
name|border_width
parameter_list|,
name|GCallback
name|callback
parameter_list|,
name|gpointer
name|callback_data
parameter_list|,
name|GtkWidget
modifier|*
modifier|*
name|first_button
parameter_list|)
block|{
name|GtkWidget
modifier|*
name|frame
decl_stmt|;
name|GtkWidget
modifier|*
name|radio_box
decl_stmt|;
name|g_return_val_if_fail
argument_list|(
name|G_TYPE_IS_ENUM
argument_list|(
name|enum_type
argument_list|)
argument_list|,
name|NULL
argument_list|)
expr_stmt|;
name|g_return_val_if_fail
argument_list|(
name|label_widget
operator|==
name|NULL
operator|||
name|GTK_IS_WIDGET
argument_list|(
name|label_widget
argument_list|)
argument_list|,
name|NULL
argument_list|)
expr_stmt|;
name|frame
operator|=
name|gtk_frame_new
argument_list|(
name|NULL
argument_list|)
expr_stmt|;
if|if
condition|(
name|label_widget
condition|)
block|{
name|gtk_frame_set_label_widget
argument_list|(
name|GTK_FRAME
argument_list|(
name|frame
argument_list|)
argument_list|,
name|label_widget
argument_list|)
expr_stmt|;
name|gtk_widget_show
argument_list|(
name|label_widget
argument_list|)
expr_stmt|;
block|}
name|radio_box
operator|=
name|gimp_enum_radio_box_new
argument_list|(
name|enum_type
argument_list|,
name|callback
argument_list|,
name|callback_data
argument_list|,
name|first_button
argument_list|)
expr_stmt|;
name|gtk_container_set_border_width
argument_list|(
name|GTK_CONTAINER
argument_list|(
name|radio_box
argument_list|)
argument_list|,
name|border_width
argument_list|)
expr_stmt|;
name|gtk_container_add
argument_list|(
name|GTK_CONTAINER
argument_list|(
name|frame
argument_list|)
argument_list|,
name|radio_box
argument_list|)
expr_stmt|;
name|gtk_widget_show
argument_list|(
name|radio_box
argument_list|)
expr_stmt|;
return|return
name|frame
return|;
block|}
end_function

begin_function
name|GtkWidget
modifier|*
DECL|function|gimp_enum_radio_frame_new_with_range (GType enum_type,gint minimum,gint maximum,GtkWidget * label_widget,gint border_width,GCallback callback,gpointer callback_data,GtkWidget ** first_button)
name|gimp_enum_radio_frame_new_with_range
parameter_list|(
name|GType
name|enum_type
parameter_list|,
name|gint
name|minimum
parameter_list|,
name|gint
name|maximum
parameter_list|,
name|GtkWidget
modifier|*
name|label_widget
parameter_list|,
name|gint
name|border_width
parameter_list|,
name|GCallback
name|callback
parameter_list|,
name|gpointer
name|callback_data
parameter_list|,
name|GtkWidget
modifier|*
modifier|*
name|first_button
parameter_list|)
block|{
name|GtkWidget
modifier|*
name|frame
decl_stmt|;
name|GtkWidget
modifier|*
name|radio_box
decl_stmt|;
name|g_return_val_if_fail
argument_list|(
name|G_TYPE_IS_ENUM
argument_list|(
name|enum_type
argument_list|)
argument_list|,
name|NULL
argument_list|)
expr_stmt|;
name|g_return_val_if_fail
argument_list|(
name|label_widget
operator|==
name|NULL
operator|||
name|GTK_IS_WIDGET
argument_list|(
name|label_widget
argument_list|)
argument_list|,
name|NULL
argument_list|)
expr_stmt|;
name|frame
operator|=
name|gtk_frame_new
argument_list|(
name|NULL
argument_list|)
expr_stmt|;
if|if
condition|(
name|label_widget
condition|)
block|{
name|gtk_frame_set_label_widget
argument_list|(
name|GTK_FRAME
argument_list|(
name|frame
argument_list|)
argument_list|,
name|label_widget
argument_list|)
expr_stmt|;
name|gtk_widget_show
argument_list|(
name|label_widget
argument_list|)
expr_stmt|;
block|}
name|radio_box
operator|=
name|gimp_enum_radio_box_new_with_range
argument_list|(
name|enum_type
argument_list|,
name|minimum
argument_list|,
name|maximum
argument_list|,
name|callback
argument_list|,
name|callback_data
argument_list|,
name|first_button
argument_list|)
expr_stmt|;
name|gtk_container_set_border_width
argument_list|(
name|GTK_CONTAINER
argument_list|(
name|radio_box
argument_list|)
argument_list|,
name|border_width
argument_list|)
expr_stmt|;
name|gtk_container_add
argument_list|(
name|GTK_CONTAINER
argument_list|(
name|frame
argument_list|)
argument_list|,
name|radio_box
argument_list|)
expr_stmt|;
name|gtk_widget_show
argument_list|(
name|radio_box
argument_list|)
expr_stmt|;
return|return
name|frame
return|;
block|}
end_function

begin_comment
comment|/**  * gimp_enum_stock_box_new:  * @enum_type: the #GType of an enum.  * @stock_prefix: the prefix of the group of stock ids to use.  * @callback: a callback to connect to the "toggled" signal of each  *            #GtkRadioButton that is created.  * @callback_data: data to pass to the @callback.  * @first_button: returns the first button in the created group.  *  * Creates a horizontal box of radio buttons with stock icons.  The  * stock_id for each icon is created by appending the enum_value's  * nick to the given @stock_prefix.  *   * Return value: a new #GtkHbox holding a group of #GtkRadioButtons.  **/
end_comment

begin_function
name|GtkWidget
modifier|*
DECL|function|gimp_enum_stock_box_new (GType enum_type,const gchar * stock_prefix,GCallback callback,gpointer callback_data,GtkWidget ** first_button)
name|gimp_enum_stock_box_new
parameter_list|(
name|GType
name|enum_type
parameter_list|,
specifier|const
name|gchar
modifier|*
name|stock_prefix
parameter_list|,
name|GCallback
name|callback
parameter_list|,
name|gpointer
name|callback_data
parameter_list|,
name|GtkWidget
modifier|*
modifier|*
name|first_button
parameter_list|)
block|{
name|GEnumClass
modifier|*
name|enum_class
decl_stmt|;
name|GtkWidget
modifier|*
name|box
decl_stmt|;
name|g_return_val_if_fail
argument_list|(
name|G_TYPE_IS_ENUM
argument_list|(
name|enum_type
argument_list|)
argument_list|,
name|NULL
argument_list|)
expr_stmt|;
name|enum_class
operator|=
name|g_type_class_ref
argument_list|(
name|enum_type
argument_list|)
expr_stmt|;
name|box
operator|=
name|gimp_enum_stock_box_new_with_range
argument_list|(
name|enum_type
argument_list|,
name|enum_class
operator|->
name|minimum
argument_list|,
name|enum_class
operator|->
name|maximum
argument_list|,
name|stock_prefix
argument_list|,
name|callback
argument_list|,
name|callback_data
argument_list|,
name|first_button
argument_list|)
expr_stmt|;
name|g_type_class_unref
argument_list|(
name|enum_class
argument_list|)
expr_stmt|;
return|return
name|box
return|;
block|}
end_function

begin_function
name|GtkWidget
modifier|*
DECL|function|gimp_enum_stock_box_new_with_range (GType enum_type,gint minimum,gint maximum,const gchar * stock_prefix,GCallback callback,gpointer callback_data,GtkWidget ** first_button)
name|gimp_enum_stock_box_new_with_range
parameter_list|(
name|GType
name|enum_type
parameter_list|,
name|gint
name|minimum
parameter_list|,
name|gint
name|maximum
parameter_list|,
specifier|const
name|gchar
modifier|*
name|stock_prefix
parameter_list|,
name|GCallback
name|callback
parameter_list|,
name|gpointer
name|callback_data
parameter_list|,
name|GtkWidget
modifier|*
modifier|*
name|first_button
parameter_list|)
block|{
name|GtkWidget
modifier|*
name|hbox
decl_stmt|;
name|GtkWidget
modifier|*
name|button
decl_stmt|;
name|GtkWidget
modifier|*
name|image
decl_stmt|;
name|GEnumClass
modifier|*
name|enum_class
decl_stmt|;
name|GEnumValue
modifier|*
name|value
decl_stmt|;
name|gchar
modifier|*
name|stock_id
decl_stmt|;
name|GSList
modifier|*
name|group
init|=
name|NULL
decl_stmt|;
name|g_return_val_if_fail
argument_list|(
name|G_TYPE_IS_ENUM
argument_list|(
name|enum_type
argument_list|)
argument_list|,
name|NULL
argument_list|)
expr_stmt|;
name|g_return_val_if_fail
argument_list|(
name|stock_prefix
operator|!=
name|NULL
argument_list|,
name|NULL
argument_list|)
expr_stmt|;
name|enum_class
operator|=
name|g_type_class_ref
argument_list|(
name|enum_type
argument_list|)
expr_stmt|;
name|hbox
operator|=
name|gtk_hbox_new
argument_list|(
name|FALSE
argument_list|,
literal|2
argument_list|)
expr_stmt|;
name|g_object_weak_ref
argument_list|(
name|G_OBJECT
argument_list|(
name|hbox
argument_list|)
argument_list|,
operator|(
name|GWeakNotify
operator|)
name|g_type_class_unref
argument_list|,
name|enum_class
argument_list|)
expr_stmt|;
if|if
condition|(
name|first_button
condition|)
operator|*
name|first_button
operator|=
name|NULL
expr_stmt|;
for|for
control|(
name|value
operator|=
name|enum_class
operator|->
name|values
init|;
name|value
operator|->
name|value_name
condition|;
name|value
operator|++
control|)
block|{
if|if
condition|(
name|value
operator|->
name|value
operator|<
name|minimum
operator|||
name|value
operator|->
name|value
operator|>
name|maximum
condition|)
continue|continue;
name|button
operator|=
name|gtk_radio_button_new
argument_list|(
name|group
argument_list|)
expr_stmt|;
name|gtk_toggle_button_set_mode
argument_list|(
name|GTK_TOGGLE_BUTTON
argument_list|(
name|button
argument_list|)
argument_list|,
name|FALSE
argument_list|)
expr_stmt|;
if|if
condition|(
name|first_button
operator|&&
operator|*
name|first_button
operator|==
name|NULL
condition|)
operator|*
name|first_button
operator|=
name|button
expr_stmt|;
name|stock_id
operator|=
name|g_strconcat
argument_list|(
name|stock_prefix
argument_list|,
literal|"-"
argument_list|,
name|value
operator|->
name|value_nick
argument_list|,
name|NULL
argument_list|)
expr_stmt|;
name|image
operator|=
name|gtk_image_new_from_stock
argument_list|(
name|stock_id
argument_list|,
name|GTK_ICON_SIZE_MENU
argument_list|)
expr_stmt|;
name|g_free
argument_list|(
name|stock_id
argument_list|)
expr_stmt|;
if|if
condition|(
name|image
condition|)
block|{
name|gtk_container_add
argument_list|(
name|GTK_CONTAINER
argument_list|(
name|button
argument_list|)
argument_list|,
name|image
argument_list|)
expr_stmt|;
name|gtk_widget_show
argument_list|(
name|image
argument_list|)
expr_stmt|;
block|}
if|if
condition|(
name|value
operator|->
name|value_name
condition|)
name|gimp_help_set_help_data
argument_list|(
name|button
argument_list|,
name|gettext
argument_list|(
name|value
operator|->
name|value_name
argument_list|)
argument_list|,
name|NULL
argument_list|)
expr_stmt|;
name|group
operator|=
name|gtk_radio_button_get_group
argument_list|(
name|GTK_RADIO_BUTTON
argument_list|(
name|button
argument_list|)
argument_list|)
expr_stmt|;
name|gtk_box_pack_start
argument_list|(
name|GTK_BOX
argument_list|(
name|hbox
argument_list|)
argument_list|,
name|button
argument_list|,
name|FALSE
argument_list|,
name|FALSE
argument_list|,
literal|0
argument_list|)
expr_stmt|;
name|gtk_widget_show
argument_list|(
name|button
argument_list|)
expr_stmt|;
name|g_object_set_data
argument_list|(
name|G_OBJECT
argument_list|(
name|button
argument_list|)
argument_list|,
literal|"gimp-item-data"
argument_list|,
name|GINT_TO_POINTER
argument_list|(
name|value
operator|->
name|value
argument_list|)
argument_list|)
expr_stmt|;
if|if
condition|(
name|callback
condition|)
name|g_signal_connect
argument_list|(
name|button
argument_list|,
literal|"toggled"
argument_list|,
name|callback
argument_list|,
name|callback_data
argument_list|)
expr_stmt|;
block|}
return|return
name|hbox
return|;
block|}
end_function

end_unit

