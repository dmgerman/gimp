begin_unit|revision:0.9.5;language:C;cregit-version:0.0.1
begin_comment
comment|/* LIBGIMP - The GIMP Library                                                     * Copyright (C) 1995-1997 Peter Mattis and Spencer Kimball                  *  * This library is free software; you can redistribute it and/or  * modify it under the terms of the GNU Library General Public  * License as published by the Free Software Foundation; either  * version 2 of the License, or (at your option) any later version.               *                                                                                * This library is distributed in the hope that it will be useful,                * but WITHOUT ANY WARRANTY; without even the implied warranty of                 * MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the GNU              * Library General Public License for more details.  *  * You should have received a copy of the GNU Library General Public  * License along with this library; if not, write to the Free  * Software Foundation, Inc., 675 Mass Ave, Cambridge, MA 02139, USA.  */
end_comment

begin_include
include|#
directive|include
file|<stdio.h>
end_include

begin_include
include|#
directive|include
file|<string.h>
end_include

begin_include
include|#
directive|include
file|"gimp.h"
end_include

begin_include
include|#
directive|include
file|"gimpui.h"
end_include

begin_function_decl
specifier|static
name|char
modifier|*
name|gimp_base_name
parameter_list|(
name|char
modifier|*
name|str
parameter_list|)
function_decl|;
end_function_decl

begin_function_decl
specifier|static
name|void
name|gimp_menu_callback
parameter_list|(
name|GtkWidget
modifier|*
name|w
parameter_list|,
name|gint32
modifier|*
name|id
parameter_list|)
function_decl|;
end_function_decl

begin_function
name|GtkWidget
modifier|*
DECL|function|gimp_image_menu_new (GimpConstraintFunc constraint,GimpMenuCallback callback,gpointer data,gint32 active_image)
name|gimp_image_menu_new
parameter_list|(
name|GimpConstraintFunc
name|constraint
parameter_list|,
name|GimpMenuCallback
name|callback
parameter_list|,
name|gpointer
name|data
parameter_list|,
name|gint32
name|active_image
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
name|char
modifier|*
name|filename
decl_stmt|;
name|char
modifier|*
name|label
decl_stmt|;
name|gint32
modifier|*
name|images
decl_stmt|;
name|int
name|nimages
decl_stmt|;
name|int
name|i
decl_stmt|,
name|k
decl_stmt|;
name|menu
operator|=
name|gtk_menu_new
argument_list|()
expr_stmt|;
name|gtk_object_set_user_data
argument_list|(
name|GTK_OBJECT
argument_list|(
name|menu
argument_list|)
argument_list|,
operator|(
name|gpointer
operator|)
name|callback
argument_list|)
expr_stmt|;
name|gtk_object_set_data
argument_list|(
name|GTK_OBJECT
argument_list|(
name|menu
argument_list|)
argument_list|,
literal|"gimp_callback_data"
argument_list|,
name|data
argument_list|)
expr_stmt|;
name|images
operator|=
name|gimp_query_images
argument_list|(
operator|&
name|nimages
argument_list|)
expr_stmt|;
for|for
control|(
name|i
operator|=
literal|0
operator|,
name|k
operator|=
literal|0
init|;
name|i
operator|<
name|nimages
condition|;
name|i
operator|++
control|)
if|if
condition|(
operator|!
name|constraint
operator|||
call|(
modifier|*
name|constraint
call|)
argument_list|(
name|images
index|[
name|i
index|]
argument_list|,
operator|-
literal|1
argument_list|,
name|data
argument_list|)
condition|)
block|{
name|filename
operator|=
name|gimp_image_get_filename
argument_list|(
name|images
index|[
name|i
index|]
argument_list|)
expr_stmt|;
name|label
operator|=
name|g_new
argument_list|(
name|char
argument_list|,
name|strlen
argument_list|(
name|filename
argument_list|)
operator|+
literal|16
argument_list|)
expr_stmt|;
name|sprintf
argument_list|(
name|label
argument_list|,
literal|"%s-%d"
argument_list|,
name|gimp_base_name
argument_list|(
name|filename
argument_list|)
argument_list|,
name|images
index|[
name|i
index|]
argument_list|)
expr_stmt|;
name|g_free
argument_list|(
name|filename
argument_list|)
expr_stmt|;
name|menuitem
operator|=
name|gtk_menu_item_new_with_label
argument_list|(
name|label
argument_list|)
expr_stmt|;
name|gtk_signal_connect
argument_list|(
name|GTK_OBJECT
argument_list|(
name|menuitem
argument_list|)
argument_list|,
literal|"activate"
argument_list|,
operator|(
name|GtkSignalFunc
operator|)
name|gimp_menu_callback
argument_list|,
operator|&
name|images
index|[
name|i
index|]
argument_list|)
expr_stmt|;
name|gtk_menu_append
argument_list|(
name|GTK_MENU
argument_list|(
name|menu
argument_list|)
argument_list|,
name|menuitem
argument_list|)
expr_stmt|;
name|gtk_widget_show
argument_list|(
name|menuitem
argument_list|)
expr_stmt|;
name|g_free
argument_list|(
name|label
argument_list|)
expr_stmt|;
if|if
condition|(
name|images
index|[
name|i
index|]
operator|==
name|active_image
condition|)
name|gtk_menu_set_active
argument_list|(
name|GTK_MENU
argument_list|(
name|menu
argument_list|)
argument_list|,
name|k
argument_list|)
expr_stmt|;
name|k
operator|+=
literal|1
expr_stmt|;
block|}
if|if
condition|(
name|k
operator|==
literal|0
condition|)
block|{
name|menuitem
operator|=
name|gtk_menu_item_new_with_label
argument_list|(
literal|"none"
argument_list|)
expr_stmt|;
name|gtk_widget_set_sensitive
argument_list|(
name|menuitem
argument_list|,
name|FALSE
argument_list|)
expr_stmt|;
name|gtk_menu_append
argument_list|(
name|GTK_MENU
argument_list|(
name|menu
argument_list|)
argument_list|,
name|menuitem
argument_list|)
expr_stmt|;
name|gtk_widget_show
argument_list|(
name|menuitem
argument_list|)
expr_stmt|;
block|}
if|if
condition|(
name|images
condition|)
block|{
if|if
condition|(
name|active_image
operator|==
operator|-
literal|1
condition|)
name|active_image
operator|=
name|images
index|[
literal|0
index|]
expr_stmt|;
call|(
modifier|*
name|callback
call|)
argument_list|(
name|active_image
argument_list|,
name|data
argument_list|)
expr_stmt|;
block|}
return|return
name|menu
return|;
block|}
end_function

begin_function
name|GtkWidget
modifier|*
DECL|function|gimp_layer_menu_new (GimpConstraintFunc constraint,GimpMenuCallback callback,gpointer data,gint32 active_layer)
name|gimp_layer_menu_new
parameter_list|(
name|GimpConstraintFunc
name|constraint
parameter_list|,
name|GimpMenuCallback
name|callback
parameter_list|,
name|gpointer
name|data
parameter_list|,
name|gint32
name|active_layer
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
name|char
modifier|*
name|name
decl_stmt|;
name|char
modifier|*
name|image_label
decl_stmt|;
name|char
modifier|*
name|label
decl_stmt|;
name|gint32
modifier|*
name|images
decl_stmt|;
name|gint32
modifier|*
name|layers
decl_stmt|;
name|gint32
name|layer
decl_stmt|;
name|int
name|nimages
decl_stmt|;
name|int
name|nlayers
decl_stmt|;
name|int
name|i
decl_stmt|,
name|j
decl_stmt|,
name|k
decl_stmt|;
name|menu
operator|=
name|gtk_menu_new
argument_list|()
expr_stmt|;
name|gtk_object_set_user_data
argument_list|(
name|GTK_OBJECT
argument_list|(
name|menu
argument_list|)
argument_list|,
operator|(
name|gpointer
operator|)
name|callback
argument_list|)
expr_stmt|;
name|gtk_object_set_data
argument_list|(
name|GTK_OBJECT
argument_list|(
name|menu
argument_list|)
argument_list|,
literal|"gimp_callback_data"
argument_list|,
name|data
argument_list|)
expr_stmt|;
name|layer
operator|=
operator|-
literal|1
expr_stmt|;
name|images
operator|=
name|gimp_query_images
argument_list|(
operator|&
name|nimages
argument_list|)
expr_stmt|;
for|for
control|(
name|i
operator|=
literal|0
operator|,
name|k
operator|=
literal|0
init|;
name|i
operator|<
name|nimages
condition|;
name|i
operator|++
control|)
if|if
condition|(
operator|!
name|constraint
operator|||
call|(
modifier|*
name|constraint
call|)
argument_list|(
name|images
index|[
name|i
index|]
argument_list|,
operator|-
literal|1
argument_list|,
name|data
argument_list|)
condition|)
block|{
name|name
operator|=
name|gimp_image_get_filename
argument_list|(
name|images
index|[
name|i
index|]
argument_list|)
expr_stmt|;
name|image_label
operator|=
name|g_new
argument_list|(
name|char
argument_list|,
name|strlen
argument_list|(
name|name
argument_list|)
operator|+
literal|16
argument_list|)
expr_stmt|;
name|sprintf
argument_list|(
name|image_label
argument_list|,
literal|"%s-%d"
argument_list|,
name|gimp_base_name
argument_list|(
name|name
argument_list|)
argument_list|,
name|images
index|[
name|i
index|]
argument_list|)
expr_stmt|;
name|g_free
argument_list|(
name|name
argument_list|)
expr_stmt|;
name|layers
operator|=
name|gimp_image_get_layers
argument_list|(
name|images
index|[
name|i
index|]
argument_list|,
operator|&
name|nlayers
argument_list|)
expr_stmt|;
for|for
control|(
name|j
operator|=
literal|0
init|;
name|j
operator|<
name|nlayers
condition|;
name|j
operator|++
control|)
if|if
condition|(
operator|!
name|constraint
operator|||
call|(
modifier|*
name|constraint
call|)
argument_list|(
name|images
index|[
name|i
index|]
argument_list|,
name|layers
index|[
name|j
index|]
argument_list|,
name|data
argument_list|)
condition|)
block|{
name|name
operator|=
name|gimp_layer_get_name
argument_list|(
name|layers
index|[
name|j
index|]
argument_list|)
expr_stmt|;
name|label
operator|=
name|g_new
argument_list|(
name|char
argument_list|,
name|strlen
argument_list|(
name|image_label
argument_list|)
operator|+
name|strlen
argument_list|(
name|name
argument_list|)
operator|+
literal|2
argument_list|)
expr_stmt|;
name|sprintf
argument_list|(
name|label
argument_list|,
literal|"%s/%s"
argument_list|,
name|image_label
argument_list|,
name|name
argument_list|)
expr_stmt|;
name|g_free
argument_list|(
name|name
argument_list|)
expr_stmt|;
name|menuitem
operator|=
name|gtk_menu_item_new_with_label
argument_list|(
name|label
argument_list|)
expr_stmt|;
name|gtk_signal_connect
argument_list|(
name|GTK_OBJECT
argument_list|(
name|menuitem
argument_list|)
argument_list|,
literal|"activate"
argument_list|,
operator|(
name|GtkSignalFunc
operator|)
name|gimp_menu_callback
argument_list|,
operator|&
name|layers
index|[
name|j
index|]
argument_list|)
expr_stmt|;
name|gtk_menu_append
argument_list|(
name|GTK_MENU
argument_list|(
name|menu
argument_list|)
argument_list|,
name|menuitem
argument_list|)
expr_stmt|;
name|gtk_widget_show
argument_list|(
name|menuitem
argument_list|)
expr_stmt|;
name|g_free
argument_list|(
name|label
argument_list|)
expr_stmt|;
if|if
condition|(
name|layers
index|[
name|j
index|]
operator|==
name|active_layer
condition|)
block|{
name|layer
operator|=
name|active_layer
expr_stmt|;
name|gtk_menu_set_active
argument_list|(
name|GTK_MENU
argument_list|(
name|menu
argument_list|)
argument_list|,
name|k
argument_list|)
expr_stmt|;
block|}
elseif|else
if|if
condition|(
name|layer
operator|==
operator|-
literal|1
condition|)
name|layer
operator|=
name|layers
index|[
name|j
index|]
expr_stmt|;
name|k
operator|+=
literal|1
expr_stmt|;
block|}
name|g_free
argument_list|(
name|image_label
argument_list|)
expr_stmt|;
block|}
name|g_free
argument_list|(
name|images
argument_list|)
expr_stmt|;
if|if
condition|(
name|k
operator|==
literal|0
condition|)
block|{
name|menuitem
operator|=
name|gtk_menu_item_new_with_label
argument_list|(
literal|"none"
argument_list|)
expr_stmt|;
name|gtk_widget_set_sensitive
argument_list|(
name|menuitem
argument_list|,
name|FALSE
argument_list|)
expr_stmt|;
name|gtk_menu_append
argument_list|(
name|GTK_MENU
argument_list|(
name|menu
argument_list|)
argument_list|,
name|menuitem
argument_list|)
expr_stmt|;
name|gtk_widget_show
argument_list|(
name|menuitem
argument_list|)
expr_stmt|;
block|}
if|if
condition|(
name|layer
operator|!=
operator|-
literal|1
condition|)
call|(
modifier|*
name|callback
call|)
argument_list|(
name|layer
argument_list|,
name|data
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
DECL|function|gimp_channel_menu_new (GimpConstraintFunc constraint,GimpMenuCallback callback,gpointer data,gint32 active_channel)
name|gimp_channel_menu_new
parameter_list|(
name|GimpConstraintFunc
name|constraint
parameter_list|,
name|GimpMenuCallback
name|callback
parameter_list|,
name|gpointer
name|data
parameter_list|,
name|gint32
name|active_channel
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
name|char
modifier|*
name|name
decl_stmt|;
name|char
modifier|*
name|image_label
decl_stmt|;
name|char
modifier|*
name|label
decl_stmt|;
name|gint32
modifier|*
name|images
decl_stmt|;
name|gint32
modifier|*
name|channels
decl_stmt|;
name|gint32
name|channel
decl_stmt|;
name|int
name|nimages
decl_stmt|;
name|int
name|nchannels
decl_stmt|;
name|int
name|i
decl_stmt|,
name|j
decl_stmt|,
name|k
decl_stmt|;
name|menu
operator|=
name|gtk_menu_new
argument_list|()
expr_stmt|;
name|gtk_object_set_user_data
argument_list|(
name|GTK_OBJECT
argument_list|(
name|menu
argument_list|)
argument_list|,
operator|(
name|gpointer
operator|)
name|callback
argument_list|)
expr_stmt|;
name|gtk_object_set_data
argument_list|(
name|GTK_OBJECT
argument_list|(
name|menu
argument_list|)
argument_list|,
literal|"gimp_callback_data"
argument_list|,
name|data
argument_list|)
expr_stmt|;
name|channel
operator|=
operator|-
literal|1
expr_stmt|;
name|images
operator|=
name|gimp_query_images
argument_list|(
operator|&
name|nimages
argument_list|)
expr_stmt|;
for|for
control|(
name|i
operator|=
literal|0
operator|,
name|k
operator|=
literal|0
init|;
name|i
operator|<
name|nimages
condition|;
name|i
operator|++
control|)
if|if
condition|(
operator|!
name|constraint
operator|||
call|(
modifier|*
name|constraint
call|)
argument_list|(
name|images
index|[
name|i
index|]
argument_list|,
operator|-
literal|1
argument_list|,
name|data
argument_list|)
condition|)
block|{
name|name
operator|=
name|gimp_image_get_filename
argument_list|(
name|images
index|[
name|i
index|]
argument_list|)
expr_stmt|;
name|image_label
operator|=
name|g_new
argument_list|(
name|char
argument_list|,
name|strlen
argument_list|(
name|name
argument_list|)
operator|+
literal|16
argument_list|)
expr_stmt|;
name|sprintf
argument_list|(
name|image_label
argument_list|,
literal|"%s-%d"
argument_list|,
name|gimp_base_name
argument_list|(
name|name
argument_list|)
argument_list|,
name|images
index|[
name|i
index|]
argument_list|)
expr_stmt|;
name|g_free
argument_list|(
name|name
argument_list|)
expr_stmt|;
name|channels
operator|=
name|gimp_image_get_channels
argument_list|(
name|images
index|[
name|i
index|]
argument_list|,
operator|&
name|nchannels
argument_list|)
expr_stmt|;
for|for
control|(
name|j
operator|=
literal|0
init|;
name|j
operator|<
name|nchannels
condition|;
name|j
operator|++
control|)
if|if
condition|(
operator|!
name|constraint
operator|||
call|(
modifier|*
name|constraint
call|)
argument_list|(
name|images
index|[
name|i
index|]
argument_list|,
name|channels
index|[
name|j
index|]
argument_list|,
name|data
argument_list|)
condition|)
block|{
name|name
operator|=
name|gimp_channel_get_name
argument_list|(
name|channels
index|[
name|j
index|]
argument_list|)
expr_stmt|;
name|label
operator|=
name|g_new
argument_list|(
name|char
argument_list|,
name|strlen
argument_list|(
name|image_label
argument_list|)
operator|+
name|strlen
argument_list|(
name|name
argument_list|)
operator|+
literal|2
argument_list|)
expr_stmt|;
name|sprintf
argument_list|(
name|label
argument_list|,
literal|"%s/%s"
argument_list|,
name|image_label
argument_list|,
name|name
argument_list|)
expr_stmt|;
name|g_free
argument_list|(
name|name
argument_list|)
expr_stmt|;
name|menuitem
operator|=
name|gtk_menu_item_new_with_label
argument_list|(
name|label
argument_list|)
expr_stmt|;
name|gtk_signal_connect
argument_list|(
name|GTK_OBJECT
argument_list|(
name|menuitem
argument_list|)
argument_list|,
literal|"activate"
argument_list|,
operator|(
name|GtkSignalFunc
operator|)
name|gimp_menu_callback
argument_list|,
operator|&
name|channels
index|[
name|j
index|]
argument_list|)
expr_stmt|;
name|gtk_menu_append
argument_list|(
name|GTK_MENU
argument_list|(
name|menu
argument_list|)
argument_list|,
name|menuitem
argument_list|)
expr_stmt|;
name|gtk_widget_show
argument_list|(
name|menuitem
argument_list|)
expr_stmt|;
name|g_free
argument_list|(
name|label
argument_list|)
expr_stmt|;
if|if
condition|(
name|channels
index|[
name|j
index|]
operator|==
name|active_channel
condition|)
block|{
name|channel
operator|=
name|active_channel
expr_stmt|;
name|gtk_menu_set_active
argument_list|(
name|GTK_MENU
argument_list|(
name|menu
argument_list|)
argument_list|,
name|k
argument_list|)
expr_stmt|;
block|}
elseif|else
if|if
condition|(
name|channel
operator|==
operator|-
literal|1
condition|)
name|channel
operator|=
name|channels
index|[
name|j
index|]
expr_stmt|;
name|k
operator|+=
literal|1
expr_stmt|;
block|}
name|g_free
argument_list|(
name|image_label
argument_list|)
expr_stmt|;
block|}
name|g_free
argument_list|(
name|images
argument_list|)
expr_stmt|;
if|if
condition|(
name|k
operator|==
literal|0
condition|)
block|{
name|menuitem
operator|=
name|gtk_menu_item_new_with_label
argument_list|(
literal|"none"
argument_list|)
expr_stmt|;
name|gtk_widget_set_sensitive
argument_list|(
name|menuitem
argument_list|,
name|FALSE
argument_list|)
expr_stmt|;
name|gtk_menu_append
argument_list|(
name|GTK_MENU
argument_list|(
name|menu
argument_list|)
argument_list|,
name|menuitem
argument_list|)
expr_stmt|;
name|gtk_widget_show
argument_list|(
name|menuitem
argument_list|)
expr_stmt|;
block|}
if|if
condition|(
name|channel
operator|!=
operator|-
literal|1
condition|)
call|(
modifier|*
name|callback
call|)
argument_list|(
name|channel
argument_list|,
name|data
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
DECL|function|gimp_drawable_menu_new (GimpConstraintFunc constraint,GimpMenuCallback callback,gpointer data,gint32 active_drawable)
name|gimp_drawable_menu_new
parameter_list|(
name|GimpConstraintFunc
name|constraint
parameter_list|,
name|GimpMenuCallback
name|callback
parameter_list|,
name|gpointer
name|data
parameter_list|,
name|gint32
name|active_drawable
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
name|char
modifier|*
name|name
decl_stmt|;
name|char
modifier|*
name|image_label
decl_stmt|;
name|char
modifier|*
name|label
decl_stmt|;
name|gint32
modifier|*
name|images
decl_stmt|;
name|gint32
modifier|*
name|layers
decl_stmt|;
name|gint32
modifier|*
name|channels
decl_stmt|;
name|gint32
name|drawable
decl_stmt|;
name|int
name|nimages
decl_stmt|;
name|int
name|nlayers
decl_stmt|;
name|int
name|nchannels
decl_stmt|;
name|int
name|i
decl_stmt|,
name|j
decl_stmt|,
name|k
decl_stmt|;
name|menu
operator|=
name|gtk_menu_new
argument_list|()
expr_stmt|;
name|gtk_object_set_user_data
argument_list|(
name|GTK_OBJECT
argument_list|(
name|menu
argument_list|)
argument_list|,
operator|(
name|gpointer
operator|)
name|callback
argument_list|)
expr_stmt|;
name|gtk_object_set_data
argument_list|(
name|GTK_OBJECT
argument_list|(
name|menu
argument_list|)
argument_list|,
literal|"gimp_callback_data"
argument_list|,
name|data
argument_list|)
expr_stmt|;
name|drawable
operator|=
operator|-
literal|1
expr_stmt|;
name|images
operator|=
name|gimp_query_images
argument_list|(
operator|&
name|nimages
argument_list|)
expr_stmt|;
for|for
control|(
name|i
operator|=
literal|0
operator|,
name|k
operator|=
literal|0
init|;
name|i
operator|<
name|nimages
condition|;
name|i
operator|++
control|)
if|if
condition|(
operator|!
name|constraint
operator|||
call|(
modifier|*
name|constraint
call|)
argument_list|(
name|images
index|[
name|i
index|]
argument_list|,
operator|-
literal|1
argument_list|,
name|data
argument_list|)
condition|)
block|{
name|name
operator|=
name|gimp_image_get_filename
argument_list|(
name|images
index|[
name|i
index|]
argument_list|)
expr_stmt|;
name|image_label
operator|=
name|g_new
argument_list|(
name|char
argument_list|,
name|strlen
argument_list|(
name|name
argument_list|)
operator|+
literal|16
argument_list|)
expr_stmt|;
name|sprintf
argument_list|(
name|image_label
argument_list|,
literal|"%s-%d"
argument_list|,
name|gimp_base_name
argument_list|(
name|name
argument_list|)
argument_list|,
name|images
index|[
name|i
index|]
argument_list|)
expr_stmt|;
name|g_free
argument_list|(
name|name
argument_list|)
expr_stmt|;
name|layers
operator|=
name|gimp_image_get_layers
argument_list|(
name|images
index|[
name|i
index|]
argument_list|,
operator|&
name|nlayers
argument_list|)
expr_stmt|;
for|for
control|(
name|j
operator|=
literal|0
init|;
name|j
operator|<
name|nlayers
condition|;
name|j
operator|++
control|)
if|if
condition|(
operator|!
name|constraint
operator|||
call|(
modifier|*
name|constraint
call|)
argument_list|(
name|images
index|[
name|i
index|]
argument_list|,
name|layers
index|[
name|j
index|]
argument_list|,
name|data
argument_list|)
condition|)
block|{
name|name
operator|=
name|gimp_layer_get_name
argument_list|(
name|layers
index|[
name|j
index|]
argument_list|)
expr_stmt|;
name|label
operator|=
name|g_new
argument_list|(
name|char
argument_list|,
name|strlen
argument_list|(
name|image_label
argument_list|)
operator|+
name|strlen
argument_list|(
name|name
argument_list|)
operator|+
literal|2
argument_list|)
expr_stmt|;
name|sprintf
argument_list|(
name|label
argument_list|,
literal|"%s/%s"
argument_list|,
name|image_label
argument_list|,
name|name
argument_list|)
expr_stmt|;
name|g_free
argument_list|(
name|name
argument_list|)
expr_stmt|;
name|menuitem
operator|=
name|gtk_menu_item_new_with_label
argument_list|(
name|label
argument_list|)
expr_stmt|;
name|gtk_signal_connect
argument_list|(
name|GTK_OBJECT
argument_list|(
name|menuitem
argument_list|)
argument_list|,
literal|"activate"
argument_list|,
operator|(
name|GtkSignalFunc
operator|)
name|gimp_menu_callback
argument_list|,
operator|&
name|layers
index|[
name|j
index|]
argument_list|)
expr_stmt|;
name|gtk_menu_append
argument_list|(
name|GTK_MENU
argument_list|(
name|menu
argument_list|)
argument_list|,
name|menuitem
argument_list|)
expr_stmt|;
name|gtk_widget_show
argument_list|(
name|menuitem
argument_list|)
expr_stmt|;
name|g_free
argument_list|(
name|label
argument_list|)
expr_stmt|;
if|if
condition|(
name|layers
index|[
name|j
index|]
operator|==
name|active_drawable
condition|)
block|{
name|drawable
operator|=
name|active_drawable
expr_stmt|;
name|gtk_menu_set_active
argument_list|(
name|GTK_MENU
argument_list|(
name|menu
argument_list|)
argument_list|,
name|k
argument_list|)
expr_stmt|;
block|}
elseif|else
if|if
condition|(
name|drawable
operator|==
operator|-
literal|1
condition|)
name|drawable
operator|=
name|layers
index|[
name|j
index|]
expr_stmt|;
name|k
operator|+=
literal|1
expr_stmt|;
block|}
name|channels
operator|=
name|gimp_image_get_channels
argument_list|(
name|images
index|[
name|i
index|]
argument_list|,
operator|&
name|nchannels
argument_list|)
expr_stmt|;
for|for
control|(
name|j
operator|=
literal|0
init|;
name|j
operator|<
name|nchannels
condition|;
name|j
operator|++
control|)
if|if
condition|(
operator|!
name|constraint
operator|||
call|(
modifier|*
name|constraint
call|)
argument_list|(
name|images
index|[
name|i
index|]
argument_list|,
name|channels
index|[
name|j
index|]
argument_list|,
name|data
argument_list|)
condition|)
block|{
name|name
operator|=
name|gimp_channel_get_name
argument_list|(
name|channels
index|[
name|j
index|]
argument_list|)
expr_stmt|;
name|label
operator|=
name|g_new
argument_list|(
name|char
argument_list|,
name|strlen
argument_list|(
name|image_label
argument_list|)
operator|+
name|strlen
argument_list|(
name|name
argument_list|)
operator|+
literal|2
argument_list|)
expr_stmt|;
name|sprintf
argument_list|(
name|label
argument_list|,
literal|"%s/%s"
argument_list|,
name|image_label
argument_list|,
name|name
argument_list|)
expr_stmt|;
name|g_free
argument_list|(
name|name
argument_list|)
expr_stmt|;
name|menuitem
operator|=
name|gtk_menu_item_new_with_label
argument_list|(
name|label
argument_list|)
expr_stmt|;
name|gtk_signal_connect
argument_list|(
name|GTK_OBJECT
argument_list|(
name|menuitem
argument_list|)
argument_list|,
literal|"activate"
argument_list|,
operator|(
name|GtkSignalFunc
operator|)
name|gimp_menu_callback
argument_list|,
operator|&
name|channels
index|[
name|j
index|]
argument_list|)
expr_stmt|;
name|gtk_menu_append
argument_list|(
name|GTK_MENU
argument_list|(
name|menu
argument_list|)
argument_list|,
name|menuitem
argument_list|)
expr_stmt|;
name|gtk_widget_show
argument_list|(
name|menuitem
argument_list|)
expr_stmt|;
name|g_free
argument_list|(
name|label
argument_list|)
expr_stmt|;
if|if
condition|(
name|channels
index|[
name|j
index|]
operator|==
name|active_drawable
condition|)
block|{
name|drawable
operator|=
name|active_drawable
expr_stmt|;
name|gtk_menu_set_active
argument_list|(
name|GTK_MENU
argument_list|(
name|menu
argument_list|)
argument_list|,
name|k
argument_list|)
expr_stmt|;
block|}
elseif|else
if|if
condition|(
name|drawable
operator|==
operator|-
literal|1
condition|)
name|drawable
operator|=
name|channels
index|[
name|j
index|]
expr_stmt|;
name|k
operator|+=
literal|1
expr_stmt|;
block|}
name|g_free
argument_list|(
name|image_label
argument_list|)
expr_stmt|;
block|}
name|g_free
argument_list|(
name|images
argument_list|)
expr_stmt|;
if|if
condition|(
name|k
operator|==
literal|0
condition|)
block|{
name|menuitem
operator|=
name|gtk_menu_item_new_with_label
argument_list|(
literal|"none"
argument_list|)
expr_stmt|;
name|gtk_widget_set_sensitive
argument_list|(
name|menuitem
argument_list|,
name|FALSE
argument_list|)
expr_stmt|;
name|gtk_menu_append
argument_list|(
name|GTK_MENU
argument_list|(
name|menu
argument_list|)
argument_list|,
name|menuitem
argument_list|)
expr_stmt|;
name|gtk_widget_show
argument_list|(
name|menuitem
argument_list|)
expr_stmt|;
block|}
if|if
condition|(
name|drawable
operator|!=
operator|-
literal|1
condition|)
call|(
modifier|*
name|callback
call|)
argument_list|(
name|drawable
argument_list|,
name|data
argument_list|)
expr_stmt|;
return|return
name|menu
return|;
block|}
end_function

begin_function
specifier|static
name|char
modifier|*
DECL|function|gimp_base_name (char * str)
name|gimp_base_name
parameter_list|(
name|char
modifier|*
name|str
parameter_list|)
block|{
name|char
modifier|*
name|t
decl_stmt|;
name|t
operator|=
name|strrchr
argument_list|(
name|str
argument_list|,
literal|'/'
argument_list|)
expr_stmt|;
if|if
condition|(
operator|!
name|t
condition|)
return|return
name|str
return|;
return|return
name|t
operator|+
literal|1
return|;
block|}
end_function

begin_function
specifier|static
name|void
DECL|function|gimp_menu_callback (GtkWidget * w,gint32 * id)
name|gimp_menu_callback
parameter_list|(
name|GtkWidget
modifier|*
name|w
parameter_list|,
name|gint32
modifier|*
name|id
parameter_list|)
block|{
name|GimpMenuCallback
name|callback
decl_stmt|;
name|gpointer
name|callback_data
decl_stmt|;
name|callback
operator|=
operator|(
name|GimpMenuCallback
operator|)
name|gtk_object_get_user_data
argument_list|(
name|GTK_OBJECT
argument_list|(
name|w
operator|->
name|parent
argument_list|)
argument_list|)
expr_stmt|;
name|callback_data
operator|=
name|gtk_object_get_data
argument_list|(
name|GTK_OBJECT
argument_list|(
name|w
operator|->
name|parent
argument_list|)
argument_list|,
literal|"gimp_callback_data"
argument_list|)
expr_stmt|;
call|(
modifier|*
name|callback
call|)
argument_list|(
operator|*
name|id
argument_list|,
name|callback_data
argument_list|)
expr_stmt|;
block|}
end_function

end_unit

