begin_unit|revision:0.9.5;language:C;cregit-version:0.0.1
begin_comment
comment|/* LIBGIMP - The GIMP Library  * Copyright (C) 1995-1997 Peter Mattis and Spencer Kimball  *  * gimpoldwidgets.c  * Copyright (C) 2000 Michael Natterer<mitch@gimp.org>  *  * This library is free software: you can redistribute it and/or  * modify it under the terms of the GNU Lesser General Public  * License as published by the Free Software Foundation; either  * version 3 of the License, or (at your option) any later version.  *  * This library is distributed in the hope that it will be useful,  * but WITHOUT ANY WARRANTY; without even the implied warranty of  * MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the GNU  * Library General Public License for more details.  *  * You should have received a copy of the GNU Lesser General Public  * License along with this library.  If not, see  *<http://www.gnu.org/licenses/>.  */
end_comment

begin_include
include|#
directive|include
file|"config.h"
end_include

begin_include
include|#
directive|include
file|<string.h>
end_include

begin_comment
comment|/* FIXME: #undef GTK_DISABLE_DEPRECATED */
end_comment

begin_undef
undef|#
directive|undef
name|GTK_DISABLE_DEPRECATED
end_undef

begin_include
include|#
directive|include
file|<gtk/gtk.h>
end_include

begin_include
include|#
directive|include
file|"libgimpbase/gimpbase.h"
end_include

begin_include
include|#
directive|include
file|"gimpwidgetstypes.h"
end_include

begin_undef
undef|#
directive|undef
name|GIMP_DISABLE_DEPRECATED
end_undef

begin_include
include|#
directive|include
file|"gimpoldwidgets.h"
end_include

begin_include
include|#
directive|include
file|"gimppixmap.h"
end_include

begin_include
include|#
directive|include
file|"gimpunitmenu.h"
end_include

begin_comment
comment|/**  * SECTION: gimpoldwidgets  * @title: GimpOldWidgets  * @short_description: Old API that is still available but declared  *                     as deprecated.  * @see_also: #GimpIntComboBox  *  * These functions are not defined if you #define GIMP_DISABLE_DEPRECATED.  **/
end_comment

begin_comment
comment|/*  *  Widget Constructors  */
end_comment

begin_comment
comment|/**  * gimp_option_menu_new:  * @menu_only: %TRUE if the function should return a #GtkMenu only.  * @...:       A %NULL-terminated @va_list describing the menu items.  *  * Convenience function to create a #GtkOptionMenu or a #GtkMenu.  *  * Returns: A #GtkOptionMenu or a #GtkMenu (depending on @menu_only).  **/
end_comment

begin_function
name|GtkWidget
modifier|*
DECL|function|gimp_option_menu_new (gboolean menu_only,...)
name|gimp_option_menu_new
parameter_list|(
name|gboolean
name|menu_only
parameter_list|,
comment|/* specify menu items as va_list:                        *  const gchar    *label,                        *  GCallback       callback,                        *  gpointer        callback_data,                        *  gpointer        item_data,                        *  GtkWidget     **widget_ptr,                        *  gboolean        active                        */
modifier|...
parameter_list|)
block|{
name|GtkWidget
modifier|*
name|menu
decl_stmt|;
name|GtkWidget
modifier|*
name|menuitem
decl_stmt|;
comment|/*  menu item variables  */
specifier|const
name|gchar
modifier|*
name|label
decl_stmt|;
name|GCallback
name|callback
decl_stmt|;
name|gpointer
name|callback_data
decl_stmt|;
name|gpointer
name|item_data
decl_stmt|;
name|GtkWidget
modifier|*
modifier|*
name|widget_ptr
decl_stmt|;
name|gboolean
name|active
decl_stmt|;
name|va_list
name|args
decl_stmt|;
name|gint
name|i
decl_stmt|;
name|gint
name|initial_index
decl_stmt|;
name|menu
operator|=
name|gtk_menu_new
argument_list|()
expr_stmt|;
comment|/*  create the menu items  */
name|initial_index
operator|=
literal|0
expr_stmt|;
name|va_start
argument_list|(
name|args
argument_list|,
name|menu_only
argument_list|)
expr_stmt|;
name|label
operator|=
name|va_arg
argument_list|(
name|args
argument_list|,
specifier|const
name|gchar
operator|*
argument_list|)
expr_stmt|;
for|for
control|(
name|i
operator|=
literal|0
init|;
name|label
condition|;
name|i
operator|++
control|)
block|{
name|callback
operator|=
name|va_arg
argument_list|(
name|args
argument_list|,
name|GCallback
argument_list|)
expr_stmt|;
name|callback_data
operator|=
name|va_arg
argument_list|(
name|args
argument_list|,
name|gpointer
argument_list|)
expr_stmt|;
name|item_data
operator|=
name|va_arg
argument_list|(
name|args
argument_list|,
name|gpointer
argument_list|)
expr_stmt|;
name|widget_ptr
operator|=
name|va_arg
argument_list|(
name|args
argument_list|,
name|GtkWidget
operator|*
operator|*
argument_list|)
expr_stmt|;
name|active
operator|=
name|va_arg
argument_list|(
name|args
argument_list|,
name|gboolean
argument_list|)
expr_stmt|;
if|if
condition|(
name|strcmp
argument_list|(
name|label
argument_list|,
literal|"---"
argument_list|)
condition|)
block|{
name|menuitem
operator|=
name|gtk_menu_item_new_with_label
argument_list|(
name|label
argument_list|)
expr_stmt|;
name|g_signal_connect
argument_list|(
name|menuitem
argument_list|,
literal|"activate"
argument_list|,
name|callback
argument_list|,
name|callback_data
argument_list|)
expr_stmt|;
if|if
condition|(
name|item_data
condition|)
block|{
name|g_object_set_data
argument_list|(
name|G_OBJECT
argument_list|(
name|menuitem
argument_list|)
argument_list|,
literal|"gimp-item-data"
argument_list|,
name|item_data
argument_list|)
expr_stmt|;
comment|/*  backward compat  */
name|g_object_set_data
argument_list|(
name|G_OBJECT
argument_list|(
name|menuitem
argument_list|)
argument_list|,
literal|"user_data"
argument_list|,
name|item_data
argument_list|)
expr_stmt|;
block|}
block|}
else|else
block|{
name|menuitem
operator|=
name|gtk_menu_item_new
argument_list|()
expr_stmt|;
name|gtk_widget_set_sensitive
argument_list|(
name|menuitem
argument_list|,
name|FALSE
argument_list|)
expr_stmt|;
block|}
name|gtk_menu_shell_append
argument_list|(
name|GTK_MENU_SHELL
argument_list|(
name|menu
argument_list|)
argument_list|,
name|menuitem
argument_list|)
expr_stmt|;
if|if
condition|(
name|widget_ptr
condition|)
operator|*
name|widget_ptr
operator|=
name|menuitem
expr_stmt|;
name|gtk_widget_show
argument_list|(
name|menuitem
argument_list|)
expr_stmt|;
comment|/*  remember the initial menu item  */
if|if
condition|(
name|active
condition|)
name|initial_index
operator|=
name|i
expr_stmt|;
name|label
operator|=
name|va_arg
argument_list|(
name|args
argument_list|,
specifier|const
name|gchar
operator|*
argument_list|)
expr_stmt|;
block|}
name|va_end
argument_list|(
name|args
argument_list|)
expr_stmt|;
if|if
condition|(
operator|!
name|menu_only
condition|)
block|{
name|GtkWidget
modifier|*
name|optionmenu
decl_stmt|;
name|optionmenu
operator|=
name|gtk_option_menu_new
argument_list|()
expr_stmt|;
name|gtk_option_menu_set_menu
argument_list|(
name|GTK_OPTION_MENU
argument_list|(
name|optionmenu
argument_list|)
argument_list|,
name|menu
argument_list|)
expr_stmt|;
comment|/*  select the initial menu item  */
name|gtk_option_menu_set_history
argument_list|(
name|GTK_OPTION_MENU
argument_list|(
name|optionmenu
argument_list|)
argument_list|,
name|initial_index
argument_list|)
expr_stmt|;
return|return
name|optionmenu
return|;
block|}
return|return
name|menu
return|;
block|}
end_function

begin_comment
comment|/**  * gimp_option_menu_new2:  * @menu_only:          %TRUE if the function should return a #GtkMenu only.  * @menu_item_callback: The callback each menu item's "activate" signal will  *                      be connected with.  * @menu_item_callback_data:  *                      The data which will be passed to g_signal_connect().  * @initial:            The @item_data of the initially selected menu item.  * @...:                A %NULL-terminated @va_list describing the menu items.  *  * Convenience function to create a #GtkOptionMenu or a #GtkMenu.  *  * Returns: A #GtkOptionMenu or a #GtkMenu (depending on @menu_only).  **/
end_comment

begin_function
name|GtkWidget
modifier|*
DECL|function|gimp_option_menu_new2 (gboolean menu_only,GCallback menu_item_callback,gpointer callback_data,gpointer initial,...)
name|gimp_option_menu_new2
parameter_list|(
name|gboolean
name|menu_only
parameter_list|,
name|GCallback
name|menu_item_callback
parameter_list|,
name|gpointer
name|callback_data
parameter_list|,
name|gpointer
name|initial
parameter_list|,
comment|/* item_data */
comment|/* specify menu items as va_list:                         *  const gchar *label,                         *  gpointer     item_data,                         *  GtkWidget  **widget_ptr,                         */
modifier|...
parameter_list|)
block|{
name|GtkWidget
modifier|*
name|menu
decl_stmt|;
name|GtkWidget
modifier|*
name|menuitem
decl_stmt|;
comment|/*  menu item variables  */
specifier|const
name|gchar
modifier|*
name|label
decl_stmt|;
name|gpointer
name|item_data
decl_stmt|;
name|GtkWidget
modifier|*
modifier|*
name|widget_ptr
decl_stmt|;
name|va_list
name|args
decl_stmt|;
name|gint
name|i
decl_stmt|;
name|gint
name|initial_index
decl_stmt|;
name|menu
operator|=
name|gtk_menu_new
argument_list|()
expr_stmt|;
comment|/*  create the menu items  */
name|initial_index
operator|=
literal|0
expr_stmt|;
name|va_start
argument_list|(
name|args
argument_list|,
name|initial
argument_list|)
expr_stmt|;
name|label
operator|=
name|va_arg
argument_list|(
name|args
argument_list|,
specifier|const
name|gchar
operator|*
argument_list|)
expr_stmt|;
for|for
control|(
name|i
operator|=
literal|0
init|;
name|label
condition|;
name|i
operator|++
control|)
block|{
name|item_data
operator|=
name|va_arg
argument_list|(
name|args
argument_list|,
name|gpointer
argument_list|)
expr_stmt|;
name|widget_ptr
operator|=
name|va_arg
argument_list|(
name|args
argument_list|,
name|GtkWidget
operator|*
operator|*
argument_list|)
expr_stmt|;
if|if
condition|(
name|strcmp
argument_list|(
name|label
argument_list|,
literal|"---"
argument_list|)
condition|)
block|{
name|menuitem
operator|=
name|gtk_menu_item_new_with_label
argument_list|(
name|label
argument_list|)
expr_stmt|;
name|g_signal_connect
argument_list|(
name|menuitem
argument_list|,
literal|"activate"
argument_list|,
name|menu_item_callback
argument_list|,
name|callback_data
argument_list|)
expr_stmt|;
if|if
condition|(
name|item_data
condition|)
block|{
name|g_object_set_data
argument_list|(
name|G_OBJECT
argument_list|(
name|menuitem
argument_list|)
argument_list|,
literal|"gimp-item-data"
argument_list|,
name|item_data
argument_list|)
expr_stmt|;
comment|/*  backward compat  */
name|g_object_set_data
argument_list|(
name|G_OBJECT
argument_list|(
name|menuitem
argument_list|)
argument_list|,
literal|"user_data"
argument_list|,
name|item_data
argument_list|)
expr_stmt|;
block|}
block|}
else|else
block|{
name|menuitem
operator|=
name|gtk_menu_item_new
argument_list|()
expr_stmt|;
name|gtk_widget_set_sensitive
argument_list|(
name|menuitem
argument_list|,
name|FALSE
argument_list|)
expr_stmt|;
block|}
name|gtk_menu_shell_append
argument_list|(
name|GTK_MENU_SHELL
argument_list|(
name|menu
argument_list|)
argument_list|,
name|menuitem
argument_list|)
expr_stmt|;
if|if
condition|(
name|widget_ptr
condition|)
operator|*
name|widget_ptr
operator|=
name|menuitem
expr_stmt|;
name|gtk_widget_show
argument_list|(
name|menuitem
argument_list|)
expr_stmt|;
comment|/*  remember the initial menu item  */
if|if
condition|(
name|item_data
operator|==
name|initial
condition|)
name|initial_index
operator|=
name|i
expr_stmt|;
name|label
operator|=
name|va_arg
argument_list|(
name|args
argument_list|,
specifier|const
name|gchar
operator|*
argument_list|)
expr_stmt|;
block|}
name|va_end
argument_list|(
name|args
argument_list|)
expr_stmt|;
if|if
condition|(
operator|!
name|menu_only
condition|)
block|{
name|GtkWidget
modifier|*
name|optionmenu
decl_stmt|;
name|optionmenu
operator|=
name|gtk_option_menu_new
argument_list|()
expr_stmt|;
name|gtk_option_menu_set_menu
argument_list|(
name|GTK_OPTION_MENU
argument_list|(
name|optionmenu
argument_list|)
argument_list|,
name|menu
argument_list|)
expr_stmt|;
comment|/*  select the initial menu item  */
name|gtk_option_menu_set_history
argument_list|(
name|GTK_OPTION_MENU
argument_list|(
name|optionmenu
argument_list|)
argument_list|,
name|initial_index
argument_list|)
expr_stmt|;
return|return
name|optionmenu
return|;
block|}
return|return
name|menu
return|;
block|}
end_function

begin_comment
comment|/**  * gimp_int_option_menu_new:  * @menu_only:          %TRUE if the function should return a #GtkMenu only.  * @menu_item_callback: The callback each menu item's "activate" signal will  *                      be connected with.  * @menu_item_callback_data:  *                      The data which will be passed to g_signal_connect().  * @initial:            The @item_data of the initially selected menu item.  * @...:                A %NULL-terminated @va_list describing the menu items.  *  * Convenience function to create a #GtkOptionMenu or a #GtkMenu. This  * function does the same thing as the deprecated function  * gimp_option_menu_new2(), but it takes integers as @item_data  * instead of pointers, since that is a very common case (mapping an  * enum to a menu).  *  * Returns: A #GtkOptionMenu or a #GtkMenu (depending on @menu_only).  **/
end_comment

begin_function
name|GtkWidget
modifier|*
DECL|function|gimp_int_option_menu_new (gboolean menu_only,GCallback menu_item_callback,gpointer callback_data,gint initial,...)
name|gimp_int_option_menu_new
parameter_list|(
name|gboolean
name|menu_only
parameter_list|,
name|GCallback
name|menu_item_callback
parameter_list|,
name|gpointer
name|callback_data
parameter_list|,
name|gint
name|initial
parameter_list|,
comment|/* item_data */
comment|/* specify menu items as va_list:                            *  const gchar *label,                            *  gint         item_data,                            *  GtkWidget  **widget_ptr,                            */
modifier|...
parameter_list|)
block|{
name|GtkWidget
modifier|*
name|menu
decl_stmt|;
name|GtkWidget
modifier|*
name|menuitem
decl_stmt|;
comment|/*  menu item variables  */
specifier|const
name|gchar
modifier|*
name|label
decl_stmt|;
name|gint
name|item_data
decl_stmt|;
name|gpointer
name|item_ptr
decl_stmt|;
name|GtkWidget
modifier|*
modifier|*
name|widget_ptr
decl_stmt|;
name|va_list
name|args
decl_stmt|;
name|gint
name|i
decl_stmt|;
name|gint
name|initial_index
decl_stmt|;
name|menu
operator|=
name|gtk_menu_new
argument_list|()
expr_stmt|;
comment|/*  create the menu items  */
name|initial_index
operator|=
literal|0
expr_stmt|;
name|va_start
argument_list|(
name|args
argument_list|,
name|initial
argument_list|)
expr_stmt|;
name|label
operator|=
name|va_arg
argument_list|(
name|args
argument_list|,
specifier|const
name|gchar
operator|*
argument_list|)
expr_stmt|;
for|for
control|(
name|i
operator|=
literal|0
init|;
name|label
condition|;
name|i
operator|++
control|)
block|{
name|item_data
operator|=
name|va_arg
argument_list|(
name|args
argument_list|,
name|gint
argument_list|)
expr_stmt|;
name|widget_ptr
operator|=
name|va_arg
argument_list|(
name|args
argument_list|,
name|GtkWidget
operator|*
operator|*
argument_list|)
expr_stmt|;
name|item_ptr
operator|=
name|GINT_TO_POINTER
argument_list|(
name|item_data
argument_list|)
expr_stmt|;
if|if
condition|(
name|strcmp
argument_list|(
name|label
argument_list|,
literal|"---"
argument_list|)
condition|)
block|{
name|menuitem
operator|=
name|gtk_menu_item_new_with_label
argument_list|(
name|label
argument_list|)
expr_stmt|;
name|g_signal_connect
argument_list|(
name|menuitem
argument_list|,
literal|"activate"
argument_list|,
name|menu_item_callback
argument_list|,
name|callback_data
argument_list|)
expr_stmt|;
if|if
condition|(
name|item_data
condition|)
block|{
name|g_object_set_data
argument_list|(
name|G_OBJECT
argument_list|(
name|menuitem
argument_list|)
argument_list|,
literal|"gimp-item-data"
argument_list|,
name|item_ptr
argument_list|)
expr_stmt|;
comment|/*  backward compat  */
name|g_object_set_data
argument_list|(
name|G_OBJECT
argument_list|(
name|menuitem
argument_list|)
argument_list|,
literal|"user_data"
argument_list|,
name|item_ptr
argument_list|)
expr_stmt|;
block|}
block|}
else|else
block|{
name|menuitem
operator|=
name|gtk_menu_item_new
argument_list|()
expr_stmt|;
name|gtk_widget_set_sensitive
argument_list|(
name|menuitem
argument_list|,
name|FALSE
argument_list|)
expr_stmt|;
block|}
name|gtk_menu_shell_append
argument_list|(
name|GTK_MENU_SHELL
argument_list|(
name|menu
argument_list|)
argument_list|,
name|menuitem
argument_list|)
expr_stmt|;
if|if
condition|(
name|widget_ptr
condition|)
operator|*
name|widget_ptr
operator|=
name|menuitem
expr_stmt|;
name|gtk_widget_show
argument_list|(
name|menuitem
argument_list|)
expr_stmt|;
comment|/*  remember the initial menu item  */
if|if
condition|(
name|item_data
operator|==
name|initial
condition|)
name|initial_index
operator|=
name|i
expr_stmt|;
name|label
operator|=
name|va_arg
argument_list|(
name|args
argument_list|,
specifier|const
name|gchar
operator|*
argument_list|)
expr_stmt|;
block|}
name|va_end
argument_list|(
name|args
argument_list|)
expr_stmt|;
if|if
condition|(
operator|!
name|menu_only
condition|)
block|{
name|GtkWidget
modifier|*
name|optionmenu
decl_stmt|;
name|optionmenu
operator|=
name|gtk_option_menu_new
argument_list|()
expr_stmt|;
name|gtk_option_menu_set_menu
argument_list|(
name|GTK_OPTION_MENU
argument_list|(
name|optionmenu
argument_list|)
argument_list|,
name|menu
argument_list|)
expr_stmt|;
comment|/*  select the initial menu item  */
name|gtk_option_menu_set_history
argument_list|(
name|GTK_OPTION_MENU
argument_list|(
name|optionmenu
argument_list|)
argument_list|,
name|initial_index
argument_list|)
expr_stmt|;
return|return
name|optionmenu
return|;
block|}
return|return
name|menu
return|;
block|}
end_function

begin_comment
comment|/**  * gimp_option_menu_set_history:  * @option_menu: A #GtkOptionMenu as returned by gimp_option_menu_new() or  *               gimp_option_menu_new2().  * @item_data:   The @item_data of the menu item you want to select.  *  * Iterates over all entries in a #GtkOptionMenu and selects the one  * with the matching @item_data. Probably only makes sense to use with  * a #GtkOptionMenu that was created using gimp_option_menu_new() or  * gimp_option_menu_new2().  **/
end_comment

begin_function
name|void
DECL|function|gimp_option_menu_set_history (GtkOptionMenu * option_menu,gpointer item_data)
name|gimp_option_menu_set_history
parameter_list|(
name|GtkOptionMenu
modifier|*
name|option_menu
parameter_list|,
name|gpointer
name|item_data
parameter_list|)
block|{
name|GList
modifier|*
name|children
decl_stmt|;
name|GList
modifier|*
name|list
decl_stmt|;
name|gint
name|history
init|=
literal|0
decl_stmt|;
name|g_return_if_fail
argument_list|(
name|GTK_IS_OPTION_MENU
argument_list|(
name|option_menu
argument_list|)
argument_list|)
expr_stmt|;
name|children
operator|=
name|gtk_container_get_children
argument_list|(
name|GTK_CONTAINER
argument_list|(
name|option_menu
operator|->
name|menu
argument_list|)
argument_list|)
expr_stmt|;
for|for
control|(
name|list
operator|=
name|children
init|;
name|list
condition|;
name|list
operator|=
name|g_list_next
argument_list|(
name|list
argument_list|)
control|)
block|{
name|GtkWidget
modifier|*
name|menu_item
init|=
name|GTK_WIDGET
argument_list|(
name|list
operator|->
name|data
argument_list|)
decl_stmt|;
if|if
condition|(
name|GTK_IS_LABEL
argument_list|(
name|gtk_bin_get_child
argument_list|(
name|GTK_BIN
argument_list|(
name|menu_item
argument_list|)
argument_list|)
argument_list|)
operator|&&
name|g_object_get_data
argument_list|(
name|G_OBJECT
argument_list|(
name|menu_item
argument_list|)
argument_list|,
literal|"gimp-item-data"
argument_list|)
operator|==
name|item_data
condition|)
block|{
break|break;
block|}
name|history
operator|++
expr_stmt|;
block|}
if|if
condition|(
name|list
condition|)
name|gtk_option_menu_set_history
argument_list|(
name|option_menu
argument_list|,
name|history
argument_list|)
expr_stmt|;
name|g_list_free
argument_list|(
name|children
argument_list|)
expr_stmt|;
block|}
end_function

begin_comment
comment|/**  * gimp_int_option_menu_set_history:  * @option_menu: A #GtkOptionMenu as returned by gimp_int_option_menu_new().  * @item_data:   The @item_data of the menu item you want to select.  *  * Iterates over all entries in a #GtkOptionMenu and selects the one with the  * matching @item_data. Probably only makes sense to use with a #GtkOptionMenu  * that was created using gimp_int_option_menu_new(). This function does the  * same thing as gimp_option_menu_set_history(), but takes integers as  * @item_data instead of pointers.  **/
end_comment

begin_function
name|void
DECL|function|gimp_int_option_menu_set_history (GtkOptionMenu * option_menu,gint item_data)
name|gimp_int_option_menu_set_history
parameter_list|(
name|GtkOptionMenu
modifier|*
name|option_menu
parameter_list|,
name|gint
name|item_data
parameter_list|)
block|{
name|g_return_if_fail
argument_list|(
name|GTK_IS_OPTION_MENU
argument_list|(
name|option_menu
argument_list|)
argument_list|)
expr_stmt|;
name|gimp_option_menu_set_history
argument_list|(
name|option_menu
argument_list|,
name|GINT_TO_POINTER
argument_list|(
name|item_data
argument_list|)
argument_list|)
expr_stmt|;
block|}
end_function

begin_comment
comment|/**  * gimp_option_menu_set_sensitive:  * @option_menu: a #GtkOptionMenu as returned by gimp_option_menu_new() or  *            gimp_option_menu_new2().  * @callback: a function called for each item in the menu to determine the  *            the sensitivity state.  * @callback_data: data to pass to the @callback function.  *  * Calls the given @callback for each item in the menu and passes it the  * item_data and the @callback_data. The menu item's sensitivity is set  * according to the return value of this function.  **/
end_comment

begin_function
name|void
DECL|function|gimp_option_menu_set_sensitive (GtkOptionMenu * option_menu,GimpOptionMenuSensitivityCallback callback,gpointer callback_data)
name|gimp_option_menu_set_sensitive
parameter_list|(
name|GtkOptionMenu
modifier|*
name|option_menu
parameter_list|,
name|GimpOptionMenuSensitivityCallback
name|callback
parameter_list|,
name|gpointer
name|callback_data
parameter_list|)
block|{
name|GList
modifier|*
name|children
decl_stmt|;
name|GList
modifier|*
name|list
decl_stmt|;
name|g_return_if_fail
argument_list|(
name|GTK_IS_OPTION_MENU
argument_list|(
name|option_menu
argument_list|)
argument_list|)
expr_stmt|;
name|g_return_if_fail
argument_list|(
name|callback
operator|!=
name|NULL
argument_list|)
expr_stmt|;
name|children
operator|=
name|gtk_container_get_children
argument_list|(
name|GTK_CONTAINER
argument_list|(
name|option_menu
operator|->
name|menu
argument_list|)
argument_list|)
expr_stmt|;
for|for
control|(
name|list
operator|=
name|children
init|;
name|list
condition|;
name|list
operator|=
name|g_list_next
argument_list|(
name|list
argument_list|)
control|)
block|{
name|GtkWidget
modifier|*
name|menu_item
init|=
name|GTK_WIDGET
argument_list|(
name|list
operator|->
name|data
argument_list|)
decl_stmt|;
if|if
condition|(
name|GTK_IS_LABEL
argument_list|(
name|gtk_bin_get_child
argument_list|(
name|GTK_BIN
argument_list|(
name|menu_item
argument_list|)
argument_list|)
argument_list|)
condition|)
block|{
name|gpointer
name|item_data
decl_stmt|;
name|gboolean
name|sensitive
decl_stmt|;
name|item_data
operator|=
name|g_object_get_data
argument_list|(
name|G_OBJECT
argument_list|(
name|menu_item
argument_list|)
argument_list|,
literal|"gimp-item-data"
argument_list|)
expr_stmt|;
name|sensitive
operator|=
name|callback
argument_list|(
name|item_data
argument_list|,
name|callback_data
argument_list|)
expr_stmt|;
name|gtk_widget_set_sensitive
argument_list|(
name|menu_item
argument_list|,
name|sensitive
argument_list|)
expr_stmt|;
block|}
block|}
name|g_list_free
argument_list|(
name|children
argument_list|)
expr_stmt|;
block|}
end_function

begin_comment
comment|/**  * gimp_int_option_menu_set_sensitive:  * @option_menu: a #GtkOptionMenu as returned by gimp_option_menu_new() or  *            gimp_option_menu_new2().  * @callback: a function called for each item in the menu to determine the  *            the sensitivity state.  * @callback_data: data to pass to the @callback function.  *  * Calls the given @callback for each item in the menu and passes it the  * item_data and the @callback_data. The menu item's sensitivity is set  * according to the return value of this function. This function does the  * same thing as gimp_option_menu_set_sensitive(), but takes integers as  * @item_data instead of pointers.  **/
end_comment

begin_function
name|void
DECL|function|gimp_int_option_menu_set_sensitive (GtkOptionMenu * option_menu,GimpIntOptionMenuSensitivityCallback callback,gpointer callback_data)
name|gimp_int_option_menu_set_sensitive
parameter_list|(
name|GtkOptionMenu
modifier|*
name|option_menu
parameter_list|,
name|GimpIntOptionMenuSensitivityCallback
name|callback
parameter_list|,
name|gpointer
name|callback_data
parameter_list|)
block|{
name|GList
modifier|*
name|children
decl_stmt|;
name|GList
modifier|*
name|list
decl_stmt|;
name|g_return_if_fail
argument_list|(
name|GTK_IS_OPTION_MENU
argument_list|(
name|option_menu
argument_list|)
argument_list|)
expr_stmt|;
name|g_return_if_fail
argument_list|(
name|callback
operator|!=
name|NULL
argument_list|)
expr_stmt|;
name|children
operator|=
name|gtk_container_get_children
argument_list|(
name|GTK_CONTAINER
argument_list|(
name|option_menu
operator|->
name|menu
argument_list|)
argument_list|)
expr_stmt|;
for|for
control|(
name|list
operator|=
name|children
init|;
name|list
condition|;
name|list
operator|=
name|g_list_next
argument_list|(
name|list
argument_list|)
control|)
block|{
name|GtkWidget
modifier|*
name|menu_item
init|=
name|GTK_WIDGET
argument_list|(
name|list
operator|->
name|data
argument_list|)
decl_stmt|;
if|if
condition|(
name|GTK_IS_LABEL
argument_list|(
name|gtk_bin_get_child
argument_list|(
name|GTK_BIN
argument_list|(
name|menu_item
argument_list|)
argument_list|)
argument_list|)
condition|)
block|{
name|gint
name|item_data
decl_stmt|;
name|gboolean
name|sensitive
decl_stmt|;
name|item_data
operator|=
name|GPOINTER_TO_INT
argument_list|(
name|g_object_get_data
argument_list|(
name|G_OBJECT
argument_list|(
name|menu_item
argument_list|)
argument_list|,
literal|"gimp-item-data"
argument_list|)
argument_list|)
expr_stmt|;
name|sensitive
operator|=
name|callback
argument_list|(
name|item_data
argument_list|,
name|callback_data
argument_list|)
expr_stmt|;
name|gtk_widget_set_sensitive
argument_list|(
name|menu_item
argument_list|,
name|sensitive
argument_list|)
expr_stmt|;
block|}
block|}
name|g_list_free
argument_list|(
name|children
argument_list|)
expr_stmt|;
block|}
end_function

begin_comment
comment|/**  * gimp_menu_item_update:  * @widget: A #GtkMenuItem.  * @data:   A pointer to a #gint variable which will store the value of  *          GPOINTER_TO_INT (g_object_get_data (@widget, "gimp-item-data")).  **/
end_comment

begin_function
name|void
DECL|function|gimp_menu_item_update (GtkWidget * widget,gpointer data)
name|gimp_menu_item_update
parameter_list|(
name|GtkWidget
modifier|*
name|widget
parameter_list|,
name|gpointer
name|data
parameter_list|)
block|{
name|gint
modifier|*
name|item_val
init|=
operator|(
name|gint
operator|*
operator|)
name|data
decl_stmt|;
operator|*
name|item_val
operator|=
name|GPOINTER_TO_INT
argument_list|(
name|g_object_get_data
argument_list|(
name|G_OBJECT
argument_list|(
name|widget
argument_list|)
argument_list|,
literal|"gimp-item-data"
argument_list|)
argument_list|)
expr_stmt|;
block|}
end_function

begin_comment
comment|/**  * gimp_pixmap_button_new:  * @xpm_data: The XPM data which will be passed to gimp_pixmap_new().  * @text:     An optional text which will appear right of the pixmap.  *  * Convenience function that creates a #GtkButton with a #GimpPixmap  * and an optional #GtkLabel.  *  * Returns: The new #GtkButton.  **/
end_comment

begin_function
name|GtkWidget
modifier|*
DECL|function|gimp_pixmap_button_new (gchar ** xpm_data,const gchar * text)
name|gimp_pixmap_button_new
parameter_list|(
name|gchar
modifier|*
modifier|*
name|xpm_data
parameter_list|,
specifier|const
name|gchar
modifier|*
name|text
parameter_list|)
block|{
name|GtkWidget
modifier|*
name|button
decl_stmt|;
name|GtkWidget
modifier|*
name|pixmap
decl_stmt|;
name|button
operator|=
name|gtk_button_new
argument_list|()
expr_stmt|;
name|pixmap
operator|=
name|gimp_pixmap_new
argument_list|(
name|xpm_data
argument_list|)
expr_stmt|;
if|if
condition|(
name|text
condition|)
block|{
name|GtkWidget
modifier|*
name|abox
decl_stmt|;
name|GtkWidget
modifier|*
name|hbox
decl_stmt|;
name|GtkWidget
modifier|*
name|label
decl_stmt|;
name|abox
operator|=
name|gtk_alignment_new
argument_list|(
literal|0.5
argument_list|,
literal|0.5
argument_list|,
literal|0.0
argument_list|,
literal|0.0
argument_list|)
expr_stmt|;
name|gtk_container_add
argument_list|(
name|GTK_CONTAINER
argument_list|(
name|button
argument_list|)
argument_list|,
name|abox
argument_list|)
expr_stmt|;
name|gtk_widget_show
argument_list|(
name|abox
argument_list|)
expr_stmt|;
name|hbox
operator|=
name|gtk_hbox_new
argument_list|(
name|FALSE
argument_list|,
literal|0
argument_list|)
expr_stmt|;
name|gtk_container_add
argument_list|(
name|GTK_CONTAINER
argument_list|(
name|abox
argument_list|)
argument_list|,
name|hbox
argument_list|)
expr_stmt|;
name|gtk_widget_show
argument_list|(
name|hbox
argument_list|)
expr_stmt|;
name|gtk_box_pack_start
argument_list|(
name|GTK_BOX
argument_list|(
name|hbox
argument_list|)
argument_list|,
name|pixmap
argument_list|,
name|FALSE
argument_list|,
name|FALSE
argument_list|,
literal|4
argument_list|)
expr_stmt|;
name|gtk_widget_show
argument_list|(
name|pixmap
argument_list|)
expr_stmt|;
name|label
operator|=
name|gtk_label_new_with_mnemonic
argument_list|(
name|text
argument_list|)
expr_stmt|;
name|gtk_label_set_mnemonic_widget
argument_list|(
name|GTK_LABEL
argument_list|(
name|label
argument_list|)
argument_list|,
name|button
argument_list|)
expr_stmt|;
name|gtk_box_pack_start
argument_list|(
name|GTK_BOX
argument_list|(
name|hbox
argument_list|)
argument_list|,
name|label
argument_list|,
name|FALSE
argument_list|,
name|FALSE
argument_list|,
literal|4
argument_list|)
expr_stmt|;
name|gtk_widget_show
argument_list|(
name|label
argument_list|)
expr_stmt|;
block|}
else|else
block|{
name|gtk_container_add
argument_list|(
name|GTK_CONTAINER
argument_list|(
name|button
argument_list|)
argument_list|,
name|pixmap
argument_list|)
expr_stmt|;
name|gtk_widget_show
argument_list|(
name|pixmap
argument_list|)
expr_stmt|;
block|}
return|return
name|button
return|;
block|}
end_function

begin_comment
comment|/**  * gimp_unit_menu_update:  * @widget: A #GimpUnitMenu.  * @data:   A pointer to a #GimpUnit variable which will store the unit menu's  *          value.  *  * This callback can set the number of decimal digits of an arbitrary number  * of #GtkSpinButton's. To use this functionality, attach the spinbuttons  * as list of data pointers attached with g_object_set_data() with the  * "set_digits" key.  *  * See gimp_toggle_button_sensitive_update() for a description of how  * to set up the list.  **/
end_comment

begin_function
name|void
DECL|function|gimp_unit_menu_update (GtkWidget * widget,gpointer data)
name|gimp_unit_menu_update
parameter_list|(
name|GtkWidget
modifier|*
name|widget
parameter_list|,
name|gpointer
name|data
parameter_list|)
block|{
name|GimpUnit
modifier|*
name|val
init|=
operator|(
name|GimpUnit
operator|*
operator|)
name|data
decl_stmt|;
name|GtkWidget
modifier|*
name|spinbutton
decl_stmt|;
name|gint
name|digits
decl_stmt|;
operator|*
name|val
operator|=
name|gimp_unit_menu_get_unit
argument_list|(
name|GIMP_UNIT_MENU
argument_list|(
name|widget
argument_list|)
argument_list|)
expr_stmt|;
name|digits
operator|=
operator|(
operator|(
operator|*
name|val
operator|==
name|GIMP_UNIT_PIXEL
operator|)
condition|?
literal|0
else|:
operator|(
operator|(
operator|*
name|val
operator|==
name|GIMP_UNIT_PERCENT
operator|)
condition|?
literal|2
else|:
operator|(
name|MIN
argument_list|(
literal|6
argument_list|,
name|MAX
argument_list|(
literal|3
argument_list|,
name|gimp_unit_get_digits
argument_list|(
operator|*
name|val
argument_list|)
argument_list|)
argument_list|)
operator|)
operator|)
operator|)
expr_stmt|;
name|digits
operator|+=
name|gimp_unit_menu_get_pixel_digits
argument_list|(
name|GIMP_UNIT_MENU
argument_list|(
name|widget
argument_list|)
argument_list|)
expr_stmt|;
name|spinbutton
operator|=
name|g_object_get_data
argument_list|(
name|G_OBJECT
argument_list|(
name|widget
argument_list|)
argument_list|,
literal|"set_digits"
argument_list|)
expr_stmt|;
while|while
condition|(
name|spinbutton
condition|)
block|{
name|gtk_spin_button_set_digits
argument_list|(
name|GTK_SPIN_BUTTON
argument_list|(
name|spinbutton
argument_list|)
argument_list|,
name|digits
argument_list|)
expr_stmt|;
name|spinbutton
operator|=
name|g_object_get_data
argument_list|(
name|G_OBJECT
argument_list|(
name|spinbutton
argument_list|)
argument_list|,
literal|"set_digits"
argument_list|)
expr_stmt|;
block|}
block|}
end_function

end_unit

