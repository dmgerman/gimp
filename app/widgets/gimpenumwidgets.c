begin_unit|revision:0.9.5;language:C;cregit-version:0.0.1
begin_comment
comment|/* The GIMP -- an image manipulation program  * Copyright (C) 1995 Spencer Kimball and Peter Mattis  *  * gimpenumwidgets.c  * Copyright (C) 2002-2004  Sven Neumann<sven@gimp.org>  *  * This program is free software; you can redistribute it and/or modify  * it under the terms of the GNU General Public License as published by  * the Free Software Foundation; either version 2 of the License, or  * (at your option) any later version.  *  * This program is distributed in the hope that it will be useful,  * but WITHOUT ANY WARRANTY; without even the implied warranty of  * MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the  * GNU General Public License for more details.  *  * You should have received a copy of the GNU General Public License  * along with this program; if not, write to the Free Software  * Foundation, Inc., 59 Temple Place - Suite 330, Boston, MA 02111-1307, USA.  */
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
file|"gimpenumwidgets.h"
end_include

begin_include
include|#
directive|include
file|"gimp-intl.h"
end_include

begin_comment
comment|/**  * gimp_enum_radio_box_new:  * @enum_type: the #GType of an enum.  * @callback: a callback to connect to the "toggled" signal of each  *            #GtkRadioButton that is created.  * @callback_data: data to pass to the @callback.  * @first_button: returns the first button in the created group.  *  * Creates a new group of #GtkRadioButtons representing the enum values.  * This is very similar to gimp_enum_menu_new().  *  * Return value: a new #GtkVBox holding a group of #GtkRadioButtons.  **/
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
name|gtk_radio_button_new_with_mnemonic
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
comment|/**  * gimp_enum_radio_frame_new:  * @enum_type: the #GType of an enum.  * @label_widget: a widget to put into the frame that will hold the radio box.  * @border_width: the border_width of the vbox inside the frame.  * @callback: a callback to connect to the "toggled" signal of each  *            #GtkRadioButton that is created.  * @callback_data: data to pass to the @callback.  * @first_button: returns the first button in the created group.  *  * Calls gimp_enum_radio_box_new() and puts the resulting vbox into a  * #GtkFrame.  *  * Return value: a new #GtkFrame holding a group of #GtkRadioButtons.  **/
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
name|gimp_frame_new
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
name|gimp_frame_new
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
comment|/**  * gimp_enum_stock_box_new:  * @enum_type: the #GType of an enum.  * @stock_prefix: the prefix of the group of stock ids to use.  * @icon_size:  * @callback: a callback to connect to the "toggled" signal of each  *            #GtkRadioButton that is created.  * @callback_data: data to pass to the @callback.  * @first_button: returns the first button in the created group.  *  * Creates a horizontal box of radio buttons with stock icons.  The  * stock_id for each icon is created by appending the enum_value's  * nick to the given @stock_prefix.  *  * Return value: a new #GtkHbox holding a group of #GtkRadioButtons.  **/
end_comment

begin_function
name|GtkWidget
modifier|*
DECL|function|gimp_enum_stock_box_new (GType enum_type,const gchar * stock_prefix,GtkIconSize icon_size,GCallback callback,gpointer callback_data,GtkWidget ** first_button)
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
name|GtkIconSize
name|icon_size
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
name|icon_size
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
DECL|function|gimp_enum_stock_box_new_with_range (GType enum_type,gint minimum,gint maximum,const gchar * stock_prefix,GtkIconSize icon_size,GCallback callback,gpointer callback_data,GtkWidget ** first_button)
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
name|GtkIconSize
name|icon_size
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
name|icon_size
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

begin_function
name|void
DECL|function|gimp_enum_stock_box_set_child_padding (GtkWidget * stock_box,gint xpad,gint ypad)
name|gimp_enum_stock_box_set_child_padding
parameter_list|(
name|GtkWidget
modifier|*
name|stock_box
parameter_list|,
name|gint
name|xpad
parameter_list|,
name|gint
name|ypad
parameter_list|)
block|{
name|GList
modifier|*
name|list
decl_stmt|;
name|g_return_if_fail
argument_list|(
name|GTK_IS_CONTAINER
argument_list|(
name|stock_box
argument_list|)
argument_list|)
expr_stmt|;
for|for
control|(
name|list
operator|=
name|gtk_container_get_children
argument_list|(
name|GTK_CONTAINER
argument_list|(
name|stock_box
argument_list|)
argument_list|)
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
name|GtkBin
modifier|*
name|bin
init|=
name|list
operator|->
name|data
decl_stmt|;
name|GtkMisc
modifier|*
name|misc
init|=
name|GTK_MISC
argument_list|(
name|bin
operator|->
name|child
argument_list|)
decl_stmt|;
name|gtk_misc_set_padding
argument_list|(
name|misc
argument_list|,
name|xpad
operator|<
literal|0
condition|?
name|misc
operator|->
name|xpad
else|:
name|xpad
argument_list|,
name|ypad
operator|<
literal|0
condition|?
name|misc
operator|->
name|ypad
else|:
name|ypad
argument_list|)
expr_stmt|;
block|}
block|}
end_function

end_unit

