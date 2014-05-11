begin_unit|revision:0.9.5;language:C;cregit-version:0.0.1
begin_comment
comment|/* GIMP - The GNU Image Manipulation Program  * Copyright (C) 1995 Spencer Kimball and Peter Mattis  *  * image-properties-dialog.c  * Copyright (C) 2005 Michael Natterer<mitch@gimp.org>  *  * This program is free software: you can redistribute it and/or modify  * it under the terms of the GNU General Public License as published by  * the Free Software Foundation; either version 3 of the License, or  * (at your option) any later version.  *  * This program is distributed in the hope that it will be useful,  * but WITHOUT ANY WARRANTY; without even the implied warranty of  * MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the  * GNU General Public License for more details.  *  * You should have received a copy of the GNU General Public License  * along with this program.  If not, see<http://www.gnu.org/licenses/>.  */
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

begin_include
include|#
directive|include
file|<gegl.h>
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
file|"dialogs-types.h"
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
file|"widgets/gimphelp-ids.h"
end_include

begin_include
include|#
directive|include
file|"widgets/gimpimagecommenteditor.h"
end_include

begin_include
include|#
directive|include
file|"widgets/gimpimagepropview.h"
end_include

begin_include
include|#
directive|include
file|"widgets/gimpimageprofileview.h"
end_include

begin_include
include|#
directive|include
file|"widgets/gimpviewabledialog.h"
end_include

begin_include
include|#
directive|include
file|"image-properties-dialog.h"
end_include

begin_include
include|#
directive|include
file|"gimp-intl.h"
end_include

begin_function
name|GtkWidget
modifier|*
DECL|function|image_properties_dialog_new (GimpImage * image,GimpContext * context,GtkWidget * parent)
name|image_properties_dialog_new
parameter_list|(
name|GimpImage
modifier|*
name|image
parameter_list|,
name|GimpContext
modifier|*
name|context
parameter_list|,
name|GtkWidget
modifier|*
name|parent
parameter_list|)
block|{
name|GtkWidget
modifier|*
name|dialog
decl_stmt|;
name|GtkWidget
modifier|*
name|notebook
decl_stmt|;
name|GtkWidget
modifier|*
name|view
decl_stmt|;
name|g_return_val_if_fail
argument_list|(
name|GIMP_IS_IMAGE
argument_list|(
name|image
argument_list|)
argument_list|,
name|NULL
argument_list|)
expr_stmt|;
name|g_return_val_if_fail
argument_list|(
name|GIMP_IS_CONTEXT
argument_list|(
name|context
argument_list|)
argument_list|,
name|NULL
argument_list|)
expr_stmt|;
name|g_return_val_if_fail
argument_list|(
name|parent
operator|==
name|NULL
operator|||
name|GTK_IS_WIDGET
argument_list|(
name|parent
argument_list|)
argument_list|,
name|NULL
argument_list|)
expr_stmt|;
name|dialog
operator|=
name|gimp_viewable_dialog_new
argument_list|(
name|GIMP_VIEWABLE
argument_list|(
name|image
argument_list|)
argument_list|,
name|context
argument_list|,
name|_
argument_list|(
literal|"Image Properties"
argument_list|)
argument_list|,
literal|"gimp-image-properties"
argument_list|,
literal|"dialog-information"
argument_list|,
name|_
argument_list|(
literal|"Image Properties"
argument_list|)
argument_list|,
name|parent
argument_list|,
name|gimp_standard_help_func
argument_list|,
name|GIMP_HELP_IMAGE_PROPERTIES
argument_list|,
name|GTK_STOCK_CLOSE
argument_list|,
name|GTK_RESPONSE_OK
argument_list|,
name|NULL
argument_list|)
expr_stmt|;
name|g_signal_connect
argument_list|(
name|dialog
argument_list|,
literal|"response"
argument_list|,
name|G_CALLBACK
argument_list|(
name|gtk_widget_destroy
argument_list|)
argument_list|,
name|NULL
argument_list|)
expr_stmt|;
name|notebook
operator|=
name|gtk_notebook_new
argument_list|()
expr_stmt|;
name|gtk_box_pack_start
argument_list|(
name|GTK_BOX
argument_list|(
name|gtk_dialog_get_content_area
argument_list|(
name|GTK_DIALOG
argument_list|(
name|dialog
argument_list|)
argument_list|)
argument_list|)
argument_list|,
name|notebook
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
name|notebook
argument_list|)
expr_stmt|;
name|view
operator|=
name|gimp_image_prop_view_new
argument_list|(
name|image
argument_list|)
expr_stmt|;
name|gtk_container_set_border_width
argument_list|(
name|GTK_CONTAINER
argument_list|(
name|view
argument_list|)
argument_list|,
literal|12
argument_list|)
expr_stmt|;
name|gtk_notebook_append_page
argument_list|(
name|GTK_NOTEBOOK
argument_list|(
name|notebook
argument_list|)
argument_list|,
name|view
argument_list|,
name|gtk_label_new
argument_list|(
name|_
argument_list|(
literal|"Properties"
argument_list|)
argument_list|)
argument_list|)
expr_stmt|;
name|gtk_widget_show
argument_list|(
name|view
argument_list|)
expr_stmt|;
name|view
operator|=
name|gimp_image_profile_view_new
argument_list|(
name|image
argument_list|)
expr_stmt|;
name|gtk_notebook_append_page
argument_list|(
name|GTK_NOTEBOOK
argument_list|(
name|notebook
argument_list|)
argument_list|,
name|view
argument_list|,
name|gtk_label_new
argument_list|(
name|_
argument_list|(
literal|"Color Profile"
argument_list|)
argument_list|)
argument_list|)
expr_stmt|;
name|gtk_widget_show
argument_list|(
name|view
argument_list|)
expr_stmt|;
name|view
operator|=
name|gimp_image_comment_editor_new
argument_list|(
name|image
argument_list|)
expr_stmt|;
name|gtk_notebook_append_page
argument_list|(
name|GTK_NOTEBOOK
argument_list|(
name|notebook
argument_list|)
argument_list|,
name|view
argument_list|,
name|gtk_label_new
argument_list|(
name|_
argument_list|(
literal|"Comment"
argument_list|)
argument_list|)
argument_list|)
expr_stmt|;
name|gtk_widget_show
argument_list|(
name|view
argument_list|)
expr_stmt|;
name|gtk_notebook_set_current_page
argument_list|(
name|GTK_NOTEBOOK
argument_list|(
name|notebook
argument_list|)
argument_list|,
literal|0
argument_list|)
expr_stmt|;
return|return
name|dialog
return|;
block|}
end_function

end_unit

