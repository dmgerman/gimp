begin_unit|revision:0.9.5;language:C;cregit-version:0.0.1
begin_comment
comment|/* LIBGIMP - The GIMP Library  * Copyright (C) 1995-1997 Peter Mattis and Spencer Kimball  *  * gimpimagecombobox.c  * Copyright (C) 2004 Sven Neumann<sven@gimp.org>  *  * This library is free software; you can redistribute it and/or  * modify it under the terms of the GNU Lesser General Public  * License as published by the Free Software Foundation; either  * version 2 of the License, or (at your option) any later version.  *  * This library is distributed in the hope that it will be useful,  * but WITHOUT ANY WARRANTY; without even the implied warranty of  * MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the GNU  * Lesser General Public License for more details.  *  * You should have received a copy of the GNU Lesser General Public  * License along with this library; if not, write to the  * Free Software Foundation, Inc., 59 Temple Place - Suite 330,  * Boston, MA 02111-1307, USA.  */
end_comment

begin_include
include|#
directive|include
file|"config.h"
end_include

begin_include
include|#
directive|include
file|<stdlib.h>
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
file|"gimp.h"
end_include

begin_include
include|#
directive|include
file|"gimpimagecombobox.h"
end_include

begin_include
include|#
directive|include
file|"gimppixbuf.h"
end_include

begin_define
DECL|macro|THUMBNAIL_SIZE
define|#
directive|define
name|THUMBNAIL_SIZE
value|24
end_define

begin_define
DECL|macro|WIDTH_REQUEST
define|#
directive|define
name|WIDTH_REQUEST
value|200
end_define

begin_function_decl
specifier|static
name|void
name|gimp_image_combo_box_model_add
parameter_list|(
name|GtkListStore
modifier|*
name|store
parameter_list|,
name|gint
name|num_images
parameter_list|,
name|gint32
modifier|*
name|images
parameter_list|,
name|GimpImageConstraintFunc
name|constraint
parameter_list|,
name|gpointer
name|data
parameter_list|)
function_decl|;
end_function_decl

begin_function_decl
specifier|static
name|void
name|gimp_image_combo_box_drag_data_received
parameter_list|(
name|GtkWidget
modifier|*
name|widget
parameter_list|,
name|GdkDragContext
modifier|*
name|context
parameter_list|,
name|gint
name|x
parameter_list|,
name|gint
name|y
parameter_list|,
name|GtkSelectionData
modifier|*
name|selection
parameter_list|,
name|guint
name|info
parameter_list|,
name|guint
name|time
parameter_list|)
function_decl|;
end_function_decl

begin_decl_stmt
DECL|variable|target
specifier|static
specifier|const
name|GtkTargetEntry
name|target
init|=
block|{
literal|"application/x-gimp-image-id"
block|,
literal|0
block|}
decl_stmt|;
end_decl_stmt

begin_comment
comment|/**  * gimp_image_combo_box_new:  * @constraint: a #GimpImageConstraintFunc or %NULL  * @data:       a pointer that is passed to @constraint  *  * Creates a new #GimpIntComboBox filled with all currently opened  * images. If a @constraint function is specified, it is called for  * each image and only if the function returns %TRUE, the image is  * added to the combobox.  *  * You should use gimp_int_combo_connect() to initialize and connect  * the combo. Use gimp_int_combo_box_set_active() to get the active  * image ID and gimp_int_combo_box_get_active() to retrieve the ID of  * the selected image.  *  * Return value: a new #GimpIntComboBox.  *  * Since: GIMP 2.2  **/
end_comment

begin_function
name|GtkWidget
modifier|*
DECL|function|gimp_image_combo_box_new (GimpImageConstraintFunc constraint,gpointer data)
name|gimp_image_combo_box_new
parameter_list|(
name|GimpImageConstraintFunc
name|constraint
parameter_list|,
name|gpointer
name|data
parameter_list|)
block|{
name|GtkWidget
modifier|*
name|combo_box
decl_stmt|;
name|GtkTreeModel
modifier|*
name|model
decl_stmt|;
name|GtkTreeIter
name|iter
decl_stmt|;
name|gint32
modifier|*
name|images
decl_stmt|;
name|gint
name|num_images
decl_stmt|;
name|combo_box
operator|=
name|g_object_new
argument_list|(
name|GIMP_TYPE_INT_COMBO_BOX
argument_list|,
literal|"width-request"
argument_list|,
name|WIDTH_REQUEST
argument_list|,
literal|"ellipsize"
argument_list|,
name|PANGO_ELLIPSIZE_MIDDLE
argument_list|,
name|NULL
argument_list|)
expr_stmt|;
name|model
operator|=
name|gtk_combo_box_get_model
argument_list|(
name|GTK_COMBO_BOX
argument_list|(
name|combo_box
argument_list|)
argument_list|)
expr_stmt|;
name|images
operator|=
name|gimp_image_list
argument_list|(
operator|&
name|num_images
argument_list|)
expr_stmt|;
name|gimp_image_combo_box_model_add
argument_list|(
name|GTK_LIST_STORE
argument_list|(
name|model
argument_list|)
argument_list|,
name|num_images
argument_list|,
name|images
argument_list|,
name|constraint
argument_list|,
name|data
argument_list|)
expr_stmt|;
name|g_free
argument_list|(
name|images
argument_list|)
expr_stmt|;
if|if
condition|(
name|gtk_tree_model_get_iter_first
argument_list|(
name|model
argument_list|,
operator|&
name|iter
argument_list|)
condition|)
name|gtk_combo_box_set_active_iter
argument_list|(
name|GTK_COMBO_BOX
argument_list|(
name|combo_box
argument_list|)
argument_list|,
operator|&
name|iter
argument_list|)
expr_stmt|;
name|gtk_drag_dest_set
argument_list|(
name|combo_box
argument_list|,
name|GTK_DEST_DEFAULT_HIGHLIGHT
operator||
name|GTK_DEST_DEFAULT_MOTION
operator||
name|GTK_DEST_DEFAULT_DROP
argument_list|,
operator|&
name|target
argument_list|,
literal|1
argument_list|,
name|GDK_ACTION_COPY
argument_list|)
expr_stmt|;
name|g_signal_connect
argument_list|(
name|combo_box
argument_list|,
literal|"drag-data-received"
argument_list|,
name|G_CALLBACK
argument_list|(
name|gimp_image_combo_box_drag_data_received
argument_list|)
argument_list|,
name|NULL
argument_list|)
expr_stmt|;
return|return
name|combo_box
return|;
block|}
end_function

begin_function
specifier|static
name|void
DECL|function|gimp_image_combo_box_model_add (GtkListStore * store,gint num_images,gint32 * images,GimpImageConstraintFunc constraint,gpointer data)
name|gimp_image_combo_box_model_add
parameter_list|(
name|GtkListStore
modifier|*
name|store
parameter_list|,
name|gint
name|num_images
parameter_list|,
name|gint32
modifier|*
name|images
parameter_list|,
name|GimpImageConstraintFunc
name|constraint
parameter_list|,
name|gpointer
name|data
parameter_list|)
block|{
name|GtkTreeIter
name|iter
decl_stmt|;
name|gint
name|i
decl_stmt|;
for|for
control|(
name|i
operator|=
literal|0
init|;
name|i
operator|<
name|num_images
condition|;
name|i
operator|++
control|)
block|{
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
name|data
argument_list|)
condition|)
block|{
name|gchar
modifier|*
name|image_name
init|=
name|gimp_image_get_name
argument_list|(
name|images
index|[
name|i
index|]
argument_list|)
decl_stmt|;
name|gchar
modifier|*
name|label
decl_stmt|;
name|GdkPixbuf
modifier|*
name|thumb
decl_stmt|;
name|label
operator|=
name|g_strdup_printf
argument_list|(
literal|"%s-%d"
argument_list|,
name|image_name
argument_list|,
name|images
index|[
name|i
index|]
argument_list|)
expr_stmt|;
name|g_free
argument_list|(
name|image_name
argument_list|)
expr_stmt|;
name|thumb
operator|=
name|gimp_image_get_thumbnail
argument_list|(
name|images
index|[
name|i
index|]
argument_list|,
name|THUMBNAIL_SIZE
argument_list|,
name|THUMBNAIL_SIZE
argument_list|,
name|GIMP_PIXBUF_SMALL_CHECKS
argument_list|)
expr_stmt|;
name|gtk_list_store_append
argument_list|(
name|store
argument_list|,
operator|&
name|iter
argument_list|)
expr_stmt|;
name|gtk_list_store_set
argument_list|(
name|store
argument_list|,
operator|&
name|iter
argument_list|,
name|GIMP_INT_STORE_VALUE
argument_list|,
name|images
index|[
name|i
index|]
argument_list|,
name|GIMP_INT_STORE_LABEL
argument_list|,
name|label
argument_list|,
name|GIMP_INT_STORE_PIXBUF
argument_list|,
name|thumb
argument_list|,
operator|-
literal|1
argument_list|)
expr_stmt|;
if|if
condition|(
name|thumb
condition|)
name|g_object_unref
argument_list|(
name|thumb
argument_list|)
expr_stmt|;
name|g_free
argument_list|(
name|label
argument_list|)
expr_stmt|;
block|}
block|}
block|}
end_function

begin_function
specifier|static
name|void
DECL|function|gimp_image_combo_box_drag_data_received (GtkWidget * widget,GdkDragContext * context,gint x,gint y,GtkSelectionData * selection,guint info,guint time)
name|gimp_image_combo_box_drag_data_received
parameter_list|(
name|GtkWidget
modifier|*
name|widget
parameter_list|,
name|GdkDragContext
modifier|*
name|context
parameter_list|,
name|gint
name|x
parameter_list|,
name|gint
name|y
parameter_list|,
name|GtkSelectionData
modifier|*
name|selection
parameter_list|,
name|guint
name|info
parameter_list|,
name|guint
name|time
parameter_list|)
block|{
name|gchar
modifier|*
name|id
decl_stmt|;
name|gint
name|ID
decl_stmt|;
if|if
condition|(
operator|(
name|selection
operator|->
name|format
operator|!=
literal|8
operator|)
operator|||
operator|(
name|selection
operator|->
name|length
operator|<
literal|1
operator|)
condition|)
block|{
name|g_warning
argument_list|(
literal|"Received invalid image ID data!"
argument_list|)
expr_stmt|;
return|return;
block|}
name|id
operator|=
name|g_strndup
argument_list|(
name|selection
operator|->
name|data
argument_list|,
name|selection
operator|->
name|length
argument_list|)
expr_stmt|;
name|ID
operator|=
name|atoi
argument_list|(
name|id
argument_list|)
expr_stmt|;
name|g_free
argument_list|(
name|id
argument_list|)
expr_stmt|;
name|gimp_int_combo_box_set_active
argument_list|(
name|GIMP_INT_COMBO_BOX
argument_list|(
name|widget
argument_list|)
argument_list|,
name|ID
argument_list|)
expr_stmt|;
block|}
end_function

end_unit

