begin_unit|revision:0.9.5;language:C;cregit-version:0.0.1
begin_comment
comment|/* The GIMP -- an image manipulation program  * Copyright (C) 1995 Spencer Kimball and Peter Mattis  *  * This program is free software; you can redistribute it and/or modify  * it under the terms of the GNU General Public License as published by  * the Free Software Foundation; either version 2 of the License, or  * (at your option) any later version.  *  * This program is distributed in the hope that it will be useful,  * but WITHOUT ANY WARRANTY; without even the implied warranty of  * MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the  * GNU General Public License for more details.  *  * You should have received a copy of the GNU General Public License  * along with this program; if not, write to the Free Software  * Foundation, Inc., 59 Temple Place - Suite 330, Boston, MA 02111-1307, USA.  */
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
file|"gui-types.h"
end_include

begin_include
include|#
directive|include
file|"core/gimpcontainer.h"
end_include

begin_include
include|#
directive|include
file|"core/gimpcontext.h"
end_include

begin_include
include|#
directive|include
file|"core/gimpimage.h"
end_include

begin_include
include|#
directive|include
file|"widgets/gimpcontainerlistview.h"
end_include

begin_include
include|#
directive|include
file|"widgets/gimpimageview.h"
end_include

begin_include
include|#
directive|include
file|"widgets/gimpitemfactory.h"
end_include

begin_include
include|#
directive|include
file|"widgets/gimpwidgets-utils.h"
end_include

begin_include
include|#
directive|include
file|"images-commands.h"
end_include

begin_include
include|#
directive|include
file|"libgimp/gimpintl.h"
end_include

begin_comment
comment|/*  public functionss */
end_comment

begin_function
name|void
DECL|function|images_raise_displays_cmd_callback (GtkWidget * widget,gpointer data)
name|images_raise_displays_cmd_callback
parameter_list|(
name|GtkWidget
modifier|*
name|widget
parameter_list|,
name|gpointer
name|data
parameter_list|)
block|{
name|GimpImageView
modifier|*
name|view
decl_stmt|;
name|view
operator|=
operator|(
name|GimpImageView
operator|*
operator|)
name|gimp_widget_get_callback_context
argument_list|(
name|widget
argument_list|)
expr_stmt|;
if|if
condition|(
operator|!
name|view
condition|)
return|return;
name|gtk_button_clicked
argument_list|(
name|GTK_BUTTON
argument_list|(
name|view
operator|->
name|raise_button
argument_list|)
argument_list|)
expr_stmt|;
block|}
end_function

begin_function
name|void
DECL|function|images_new_display_cmd_callback (GtkWidget * widget,gpointer data)
name|images_new_display_cmd_callback
parameter_list|(
name|GtkWidget
modifier|*
name|widget
parameter_list|,
name|gpointer
name|data
parameter_list|)
block|{
name|GimpImageView
modifier|*
name|view
decl_stmt|;
name|view
operator|=
operator|(
name|GimpImageView
operator|*
operator|)
name|gimp_widget_get_callback_context
argument_list|(
name|widget
argument_list|)
expr_stmt|;
if|if
condition|(
operator|!
name|view
condition|)
return|return;
name|gtk_button_clicked
argument_list|(
name|GTK_BUTTON
argument_list|(
name|view
operator|->
name|new_button
argument_list|)
argument_list|)
expr_stmt|;
block|}
end_function

begin_function
name|void
DECL|function|images_delete_image_cmd_callback (GtkWidget * widget,gpointer data)
name|images_delete_image_cmd_callback
parameter_list|(
name|GtkWidget
modifier|*
name|widget
parameter_list|,
name|gpointer
name|data
parameter_list|)
block|{
name|GimpImageView
modifier|*
name|view
decl_stmt|;
name|view
operator|=
operator|(
name|GimpImageView
operator|*
operator|)
name|gimp_widget_get_callback_context
argument_list|(
name|widget
argument_list|)
expr_stmt|;
if|if
condition|(
operator|!
name|view
condition|)
return|return;
name|gtk_button_clicked
argument_list|(
name|GTK_BUTTON
argument_list|(
name|view
operator|->
name|delete_button
argument_list|)
argument_list|)
expr_stmt|;
block|}
end_function

begin_function
name|void
DECL|function|images_menu_update (GtkItemFactory * factory,gpointer data)
name|images_menu_update
parameter_list|(
name|GtkItemFactory
modifier|*
name|factory
parameter_list|,
name|gpointer
name|data
parameter_list|)
block|{
name|GimpContainerEditor
modifier|*
name|editor
decl_stmt|;
name|GimpImage
modifier|*
name|image
decl_stmt|;
name|editor
operator|=
name|GIMP_CONTAINER_EDITOR
argument_list|(
name|data
argument_list|)
expr_stmt|;
name|image
operator|=
name|gimp_context_get_image
argument_list|(
name|editor
operator|->
name|view
operator|->
name|context
argument_list|)
expr_stmt|;
DECL|macro|SET_SENSITIVE (menu,condition)
define|#
directive|define
name|SET_SENSITIVE
parameter_list|(
name|menu
parameter_list|,
name|condition
parameter_list|)
define|\
value|gimp_item_factory_set_sensitive (factory, menu, (condition) != 0)
name|SET_SENSITIVE
argument_list|(
literal|"/Raise Displays"
argument_list|,
name|image
argument_list|)
expr_stmt|;
name|SET_SENSITIVE
argument_list|(
literal|"/New Display"
argument_list|,
name|image
argument_list|)
expr_stmt|;
name|SET_SENSITIVE
argument_list|(
literal|"/Delete Image"
argument_list|,
name|image
operator|&&
name|image
operator|->
name|disp_count
operator|==
literal|0
argument_list|)
expr_stmt|;
undef|#
directive|undef
name|SET_SENSITIVE
block|}
end_function

end_unit

